/*---------------------------------------------------------------------------*\
*                                OpenSG                                     *
*                                                                           *
*                                                                           *
*             Copyright (C) 2000-2002 by the OpenSG Forum                   *
*                                                                           *
*                            www.opensg.org                                 *
*                                                                           *
*   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
*                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
*                                License                                    *
*                                                                           *
* This library is free software; you can redistribute it and/or modify it   *
* under the terms of the GNU Library General Public License as published    *
* by the Free Software Foundation, version 2.                               *
*                                                                           *
* This library is distributed in the hope that it will be useful, but       *
* WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
* Library General Public License for more details.                          *
*                                                                           *
* You should have received a copy of the GNU Library General Public         *
* License along with this library; if not, write to the Free Software       *
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
*                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
*                                Changes                                    *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
\*---------------------------------------------------------------------------*/

/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <functional>
#include <algorithm>
#include <sstream>

#include "OSGSharePtrGraphOp.h"

#include "OSGGraphOpFactory.h"
#include "OSGLog.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGVector.h"
#include "OSGFieldContainerUtils.h"
#include "OSGTypeFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

//! Register the GraphOp with the factory
static bool registerOp(void)
{
    GraphOpRefPtr newOp = SharePtrGraphOp::create();

    GraphOpFactory::the()->registerOp(newOp);
    return true;
}
static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

SharePtrGraphOp::SharePtrGraphOp(const char* name):
    GraphOp(name),
    _typeMap(),
    _includeSet(),
    _excludeSet()
{
}

SharePtrGraphOp::~SharePtrGraphOp(void)
{
}

SharePtrGraphOpTransitPtr
SharePtrGraphOp::create(void)
{
    return SharePtrGraphOpTransitPtr(new SharePtrGraphOp);
}

GraphOpTransitPtr SharePtrGraphOp::clone(void)
{
    return GraphOpTransitPtr(new SharePtrGraphOp);
}

bool SharePtrGraphOp::traverse(Node *root)
{
    if(!_includeSet.empty() && !_excludeSet.empty())
    {
        FFATAL(("SharePtrGraphOp : Setting both the includes and excludes"
                "is not allowed!\n"));
        return false;
    }

    _typeMap   .clear();
    _shareCount.clear();

    _totalTime   = 0.0f;
    _compareTime = 0.0f;

    Time startTime = getSystemTime();

    shareFC(root);

    _totalTime = getSystemTime() - startTime;

    // DEBUG
    SINFO << "SharePtrGraphOp::traverse: _totalTime: " << _totalTime
          << " _compareTime: " << _compareTime << "\n";
    SINFO << "SharePtrGraphOp::traverse: Unique containers by type:\n";

    FCTypeMapIt tmIt  = _typeMap.begin();
    FCTypeMapIt tmEnd = _typeMap.end  ();

    for(; tmIt != tmEnd; ++tmIt)
    {
        UInt32              typeId = tmIt->first;
        FieldContainerType *fcType = FieldContainerFactory::the()->findType(typeId);

        SINFO << "TypeId [" << typeId << "] [" << (fcType != NULL ? fcType->getCName() : "")
              << "] -- [" << tmIt->second.size() << "]\n";
    }

    SINFO << "SharePtrGraphOp::traverse: Shared containers by type:\n";

    ShareCountIt scIt  = _shareCount.begin();
    ShareCountIt scEnd = _shareCount.end  ();

    for(; scIt != scEnd; ++scIt)
    {
        UInt32              typeId = scIt->first;
        FieldContainerType *fcType = FieldContainerFactory::the()->findType(typeId);

        SINFO << "TypeId [" << typeId << "] [" << (fcType != NULL ? fcType->getCName() : "")
              << "] -- [" << scIt->second << "]\n";
    }

    SINFO << std::flush;

    return true;
}

void SharePtrGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);
    std::string incl, excl;

    ps("includes",  incl);
    ps("excludes",  excl);

    if(incl.length() && excl.length())
    {
        FWARNING(("SharePtrGraphOp: can't set includes and excludes\n"));
    }
    else
    {
        setIncludes(incl);
        setExcludes(excl);
    }

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("SharePtrGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string SharePtrGraphOp::usage(void)
{
    return
    "SharePtr: try to share FieldContainers in a subtree\n"
    "  Compares the values of all referenced FieldContainers in the\n"
    "  subtree and shares them if possible. Primarily useful for\n"
    "  Geometries and Materials, but works for everything.\n"
    "Params: name (type, default)\n"
    "  includes (string, ""): comma-separated list of types to share\n"
    "  excludes (string, ""): comma-separated list of types not to share\n"
    "  (Only one of the two can be used, not both at the same time)\n"
    ;
}

void SharePtrGraphOp::setIncludes(const std::string &includes)
{
    _includeSet.clear();

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos     = includes.begin();

    while(curPos < includes.end())
    {
        nextComma = std::find(curPos, includes.end(), ',');
        // strip leading spaces
        curPos = std::find_if(curPos, nextComma,
                              std::not1(std::ptr_fun(isspace)));

        std::string typeName(curPos, nextComma);

        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(typeName.c_str());

        if(fcType != NULL)
        {
            _includeSet.insert(fcType->getId());
        }
        else
        {
            SWARNING << "SharePtrGraphOp::setIncludes: Unrecognized type ["
                     << typeName << "]." << std::endl;
        }

        if(nextComma != includes.end())
            ++nextComma;

        curPos = nextComma;
    }
}

void SharePtrGraphOp::setExcludes(const std::string &excludes)
{
    _excludeSet.clear();

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos     = excludes.begin();

    while(curPos < excludes.end())
    {
        nextComma = std::find(curPos, excludes.end(), ',');
        // strip leading spaces
        curPos = std::find_if(curPos, nextComma,
                              std::not1(std::ptr_fun(isspace)));

        std::string typeName(curPos, nextComma);

        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(typeName.c_str());

        if(fcType != NULL)
        {
            _excludeSet.insert(fcType->getId());
        }
        else
        {
            SWARNING << "SharePtrGraphOp::setExcludes: Unrecognized type ["
                    << typeName << "]." << std::endl;
        }

        if(nextComma != excludes.end())
            ++nextComma;

        curPos = nextComma;
    }
}

Action::ResultE SharePtrGraphOp::traverseEnter(Node * const /*node*/)
{
    return Action::Skip;
}

Action::ResultE SharePtrGraphOp::traverseLeave(Node * const /*node*/,
                                               Action::ResultE /*res*/)
{
    return Action::Skip;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

FieldContainer *SharePtrGraphOp::shareFC(FieldContainer *fc)
{
    if(fc == NULL)
        return fc;

    bool   singleParent = false;
    UInt32 fcTypeId     = fc->getType().getId           ();
    UInt32 fCount       = fc->getType().getNumFieldDescs();


    FCTypeMapIt tmIt = _typeMap.find(fcTypeId);

    if(tmIt == _typeMap.end())
    {
        tmIt =
            _typeMap.insert(FCTypeMap::value_type(fcTypeId, FCSet())).first;
    }

    if(tmIt->second.count(fc) > 0)
        return fc;


    for(UInt32 i = 1; i <= fCount; ++i)
    {
        const FieldDescriptionBase *fDesc = fc->getFieldDescription(i);

        // skip parent fields
        if(fDesc->getFieldType().getClass() == FieldType::ParentPtrField)
        {
            if(fDesc->getFieldType().getCardinality() == FieldType::SingleField)
                singleParent = true;

            continue;
        }

        EditFieldHandlePtr fHandle = fc->editField(i);

        // skip non-pointer fields
#if 1
        if(fDesc->getFieldType().isPtrField() == false)
            continue;
#else
        if(fHandle != NULL)
        {
            if(fHandle->isPointerField() == false)
                continue;
        }
        else
        {
             if(fDesc->getFieldType().isPtrField() == false)
                 continue;
        }
#endif

        // skip internal fields
        if(fDesc->isInternal() == true)
            continue;

        FieldContainerPtrSFieldBase::EditHandlePtr sfPtrHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::EditHandle>(fHandle);

        FieldContainerPtrMFieldBase::EditHandlePtr mfPtrHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::EditHandle>(fHandle);

        if(sfPtrHandle != NULL && sfPtrHandle->isValid() == true)
        {
            FieldContainer *childFC    = sfPtrHandle->get();
            FieldContainer *childEquiv = shareFC(childFC);

            if(childEquiv != childFC)
            {
                sfPtrHandle->set(childEquiv);
            }
        }
        else if(mfPtrHandle != NULL && mfPtrHandle->isValid() == true)
        {
            for(UInt32 j = 0; j < mfPtrHandle->size(); ++j)
            {
                FieldContainer *childFC    = mfPtrHandle->get(j);
                FieldContainer *childEquiv = shareFC(childFC);

                if(childEquiv != childFC)
                {
                    mfPtrHandle->replace(j, childEquiv);
                }
            }
        }
#if 0
        else
        {
            SFAttachmentPtrMap::EditHandlePtr  amEditHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::EditHandle>(
                    fHandle);

            SFAttachmentPtrMap::GetHandlePtr  amGetHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                    fc->getField(i));

            if(amEditHandle != NULL && amEditHandle->isValid() == true)
            {
                 const AttachmentMap &oAttMap = (*amGetHandle)->getValue();

                 AttachmentMap::const_iterator amIt  = oAttMap.begin();
                 AttachmentMap::const_iterator amEnd = oAttMap.end  ();

                 for(; amIt != amEnd; ++amIt)
                 {
                     Attachment *att      = (*amIt).second;
                     Attachment *attEquiv =  
                         dynamic_cast<Attachment *>(shareFC(att));

                     if(attEquiv != att)
                     {
                         amEditHandle->replaceByObj(att, attEquiv);
                     }
                 }
            }
        }
#endif
    }

    if(checkIncludeSet(fcTypeId) == false)
        return fc;

    if(checkExcludeSet(fcTypeId) == true)
        return fc;

    // can not share a FC with single parents
    if(singleParent == true)
        return fc;

    FCSetIt fcsIt  = tmIt->second.begin();
    FCSetIt fcsEnd = tmIt->second.end  ();

    for(; fcsIt != fcsEnd; ++fcsIt)
    {
        Time compareStart = getSystemTime();

        bool compare      = compareContainerEqual(*fcsIt, fc, true, true);

        _compareTime += getSystemTime() - compareStart;

        if(compare)
        {
            if(*fcsIt != fc)
                _shareCount[fcTypeId] += 1;

            return *fcsIt;
        }
    }

    // no equivalent FC known, add to set of unique containers
    tmIt->second.insert(fc);

    return fc;
}

bool SharePtrGraphOp::checkInSet(UInt32 fcTypeId, const FCIdSet &idSet)
{
    bool returnValue = false;

    TypeBase *fcType = TypeFactory::the()->findType(fcTypeId);

    if(fcType != NULL && idSet.empty() == false)
    {
        FCIdSetConstIt isIt  = idSet.begin();
        FCIdSetConstIt isEnd = idSet.end  ();

        for(; isIt != isEnd; ++isIt)
        {
            TypeBase *isType = TypeFactory::the()->findType(*isIt);

            if(isType != NULL && fcType->isDerivedFrom(*isType))
            {
                returnValue = true;
                break;
            }
        }
    }

    return returnValue;
}

bool SharePtrGraphOp::checkIncludeSet(UInt32 fcTypeId)
{
    if(_includeSet.empty() == true)
        return true;

    if(checkInSet(fcTypeId, _includeSet) == true)
        return true;

    return false;
}

bool SharePtrGraphOp::checkExcludeSet(UInt32 fcTypeId)
{
    if(_excludeSet.empty() == true)
        return false;

    if(checkInSet(fcTypeId, _excludeSet) == true)
        return true;

    return false;
}

