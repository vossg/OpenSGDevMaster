/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include "OSGFieldContainerUtils.h"
#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGAttachment.h"
#include "OSGAttachmentMapSFields.h"
#include "OSGNameAttachment.h"

#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <ostream>
#include <set>

OSG_BEGIN_NAMESPACE

namespace
{
    // anonymous namespace for implementation details of the compareContainer
    // function.

typedef std::set<const FieldContainer *> FCSet;

// forward declarations
bool comparePointerFields(
    GetFieldHandlePtr  lhsField,
    GetFieldHandlePtr  rhsField,
    FCSet             &lhsVisitedSet,
    FCSet             &rhsVisitedSet,
    bool               ignoreAttachments,
    bool               compareIdentity   );

/*! Implementation of \c compareContainerEqual. The two \c FCSet parameters
    keep track of visited fields in each hierarchy to avoid looping.
 */
bool compareContainerEqualImpl(
    const FieldContainer *lhs,
    const FieldContainer *rhs,
          FCSet          &lhsVisitedSet,
          FCSet          &rhsVisitedSet,
          bool            ignoreAttachments,
          bool            compareIdentity   )
{
    // compare pointers
    if(lhs == rhs)
        return true;

    if(lhs == NULL || rhs == NULL)
        return false;

    // different types ?
    if(lhs->getType() != rhs->getType())
        return false;

    UInt32 lhsFCount = lhs->getType().getNumFieldDescs();
    UInt32 rhsFCount = rhs->getType().getNumFieldDescs();

    // different number of (dynamic) fields ?
    if(lhsFCount != rhsFCount)
        return false;

    lhsVisitedSet.insert(lhs);
    rhsVisitedSet.insert(rhs);

    bool returnValue = true;

    for(UInt32 i = 1; i <= lhsFCount && returnValue == true; ++i)
    {
        GetFieldHandlePtr lhsField = lhs->getField(i);
        GetFieldHandlePtr rhsField = rhs->getField(i);

        // valid handles ?
        if(lhsField == NULL || lhsField->isValid() == false ||
           rhsField == NULL || rhsField->isValid() == false   )
            continue;

        if(lhsField->getType() != rhsField->getType())
        {
            returnValue = false;
            continue;
        }

        // skip internal and parent fields
        if(lhsField->isInternal()            == true                      ||
           lhsField->getType   ().getClass() == FieldType::ParentPtrField   )
            continue;

        if(compareIdentity == true)
        {
            if(lhsField->equal(rhsField) == false)
                returnValue = false;
        }
        else
        {
            if(lhsField->isPointerField() == true)
            {
                returnValue = comparePointerFields(
                    lhsField,          rhsField,
                    lhsVisitedSet,     rhsVisitedSet,
                    ignoreAttachments, compareIdentity);
            }
            else
            {
                if(lhsField->equal(rhsField) == false)
                    returnValue = false;
            }
        }
    }

    return returnValue;
}

/*! Compares two PointerFields \a lhsField and \a rhsField by recursively
    comparing the pointed-to containers.
    This function is only used in \c compareContainer below.
 */
bool comparePointerFields(
    GetFieldHandlePtr  lhsField,
    GetFieldHandlePtr  rhsField,
    FCSet             &lhsVisitedSet,
    FCSet             &rhsVisitedSet,
    bool               ignoreAttachments,
    bool               compareIdentity   )
{
    bool returnValue = true;

    if(lhsField->getCardinality() == FieldType::SingleField)
    {
        FieldContainerPtrSFieldBase::GetHandlePtr lhsSFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(lhsField);
        FieldContainerPtrSFieldBase::GetHandlePtr rhsSFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(rhsField);

        if(lhsSFHandle != NULL && lhsSFHandle->isValid() &&
           rhsSFHandle != NULL && rhsSFHandle->isValid()   )
        {
            if(lhsVisitedSet.count(lhsSFHandle->get()) == 0 ||
               rhsVisitedSet.count(rhsSFHandle->get()) == 0   )
            {
                returnValue = compareContainerEqualImpl(
                    lhsSFHandle->get(), rhsSFHandle->get(),
                    lhsVisitedSet,      rhsVisitedSet,
                    ignoreAttachments,  compareIdentity     );
            }
        }
        else
        {
            SFAttachmentPtrMap::GetHandlePtr  lhsAMHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                    lhsField);
            SFAttachmentPtrMap::GetHandlePtr  rhsAMHandle =
                boost::dynamic_pointer_cast<SFAttachmentPtrMap::GetHandle>(
                    rhsField);

            if(lhsAMHandle != NULL && lhsAMHandle->isValid() &&
            rhsAMHandle != NULL && rhsAMHandle->isValid()   )
            {
                const AttachmentMap &lhsAM = (*lhsAMHandle)->getValue();
                const AttachmentMap &rhsAM = (*rhsAMHandle)->getValue();

                // skip attachments, if the option is set
                if(ignoreAttachments)
                {
                    returnValue = true;
                }
                else if(lhsAM.size() != rhsAM.size())
                {
                    returnValue = false;
                }
                else
                {
                    AttachmentMap::const_iterator lhsAMIt  = lhsAM.begin();
                    AttachmentMap::const_iterator lhsAMEnd = lhsAM.end  ();

                    AttachmentMap::const_iterator rhsAMIt  = rhsAM.begin();
                    AttachmentMap::const_iterator rhsAMEnd = rhsAM.end  ();

                    for(; lhsAMIt != lhsAMEnd && returnValue == true;
                        ++lhsAMIt, ++rhsAMIt)
                    {
                        if(lhsVisitedSet.count(lhsAMIt->second) == 0 ||
                        rhsVisitedSet.count(rhsAMIt->second) == 0   )
                        {
                            returnValue = compareContainerEqualImpl(
                                lhsAMIt->second,   rhsAMIt->second,
                                lhsVisitedSet,     rhsVisitedSet,
                                ignoreAttachments, compareIdentity );
                        }
                    }
                }
            }
        }
    }
    else
    {
        FieldContainerPtrMFieldBase::GetHandlePtr lhsMFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(lhsField);
        FieldContainerPtrMFieldBase::GetHandlePtr rhsMFHandle =
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(rhsField);

        if(lhsMFHandle != NULL && lhsMFHandle->isValid() &&
                rhsMFHandle != NULL && rhsMFHandle->isValid()   )
        {
            if(lhsMFHandle->size() != rhsMFHandle->size())
            {
                returnValue = false;
            }
            else
            {
                for(UInt32 i = 0; i           <  lhsMFHandle->size() &&
                                  returnValue == true;                  ++i)
                {
                    if(lhsVisitedSet.count(lhsMFHandle->get(i)) == 0 ||
                       rhsVisitedSet.count(rhsMFHandle->get(i)) == 0   )
                    {
                        returnValue = compareContainerEqualImpl(
                            lhsMFHandle->get(i), rhsMFHandle->get(i),
                            lhsVisitedSet,       rhsVisitedSet,
                            ignoreAttachments,   compareIdentity     );
                    }
                }
            }
        }
    }

    return returnValue;
}

} // namespace

/*! Compares two FieldContainer \a lhs and \a rhs for equivalence. The meaning
    of this comparison can be tweaked with the additional arguments.
    If \a ignoreAttachments is \c true, Attachments are excluded from the
    comparison.
    If \a compareIdentity is \c true, pointers are compared by
    address otherwise the pointed-to objects are compared for equivalence.
 */
bool compareContainerEqual(
    const FieldContainer *lhs,
    const FieldContainer *rhs,
          bool            ignoreAttachments,
          bool            compareIdentity   )
{
    FCSet lhsVisitedSet;
    FCSet rhsVisitedSet;

    return compareContainerEqualImpl(
        lhs, rhs, lhsVisitedSet, rhsVisitedSet,
        ignoreAttachments, compareIdentity     );
}

//---------------------------------------------------------------------------
//  MemoryConsumption
//---------------------------------------------------------------------------

void MemoryConsumption::scan(void)
{
    UInt32 numCont = FieldContainerFactory::the()->getNumContainers();

    for(UInt32 i = 0; i < numCont; ++i)
    {
        FieldContainer *pFC = FieldContainerFactory::the()->getContainer(i);

        if(pFC == NULL)
            continue;

        TypeMemMapIt tmIt    = _memMap.find(pFC->getType().getId());
        UInt32       binSize = pFC->getBinSize(TypeTraits<BitVector>::BitsSet);

        if(tmIt != _memMap.end())
        {
            tmIt->second.first  += binSize;
            tmIt->second.second += 1;
        }
        else
        {
            _memMap[pFC->getType().getId()] = MemCountPair(binSize, 1);
        }
    }
}


void MemoryConsumption::print(std::ostream &os, bool ignoreProto) const
{
    TypeMemMapConstIt tmIt  = _memMap.begin();
    TypeMemMapConstIt tmEnd = _memMap.end  ();

    UInt32        totalMem   = 0;
    UInt32        totalCount = 0;
    boost::format formatter("%|1$-25| [%|2$8|] Byte [%|3$8.0f|] kByte [%|4$4|]\n");

    for(; tmIt != tmEnd; ++tmIt)
    {
        FieldContainerType *fcType =
            FieldContainerFactory::the()->findType(tmIt->first);

        if(fcType == NULL)
            continue;

        if(ignoreProto && tmIt->second.second == 1)
            continue;

        os << formatter % fcType->getCName()
                        % tmIt->second.first
                        % (tmIt->second.first / 1024.f)
                        % tmIt->second.second;

        totalMem   += tmIt->second.first;
        totalCount += tmIt->second.second;
    }

    os << "--------------------------------------------\n";
    os << formatter % "Total"
                    % totalMem
                    % (totalMem / 1024.f)
                    % totalCount;
}

MemoryConsumption::TypeMemMapConstIt MemoryConsumption::beginMap(void) const
{
    return _memMap.begin();
}

MemoryConsumption::TypeMemMapConstIt MemoryConsumption::endMap(void) const
{
    return _memMap.end();
}

//---------------------------------------------------------------------------
//  SceneGraphPrinter
//---------------------------------------------------------------------------

SceneGraphPrinter::SceneGraphPrinter(Node *root)
    : _pRoot  (root),
      _pStream(NULL),
      _indent (0)
{
    // nothing to do
}

void SceneGraphPrinter::printDownTree(std::ostream &os)
{
    _pStream = &os;
    _indent  = 0;

    traverse(_pRoot,
             boost::bind(&Self::traverseEnter, this, _1    ),
             boost::bind(&Self::traverseLeave, this, _1, _2) );

    os << std::flush;
}

void SceneGraphPrinter::printUpTree(std::ostream &os)
{
    _pStream = &os;
    _indent  = 0;

    Node *node = _pRoot;

    while(node != NULL)
    {
        NodeCore *core = node->getCore();

        os <<      "[" << node
           <<    "] [" << node->getId()
           <<    "] [" << (getName(node) ? getName(node) : "<unnamed>")
           << "] -- [" << core
           <<    "] [" << core->getId()
           <<    "] [" << core->getType().getCName()
           << "]\n";

        node = node->getParent();
    }

    os << std::flush;
}

void
SceneGraphPrinter::addPrintFunc(const FieldContainerType &fcType,
                                const CorePrintFunction  &printFunc)
{
    _printFuncMap[fcType.getId()] = printFunc;
}

void
SceneGraphPrinter::subPrintFunc(const FieldContainerType &fcType)
{
    PrintFuncMapIt pfIt = _printFuncMap.find(fcType.getId());

    if(pfIt != _printFuncMap.end())
        _printFuncMap.erase(pfIt);
}

void
SceneGraphPrinter::incIndent(void)
{
    _indent += 2;
}

void
SceneGraphPrinter::decIndent(void)
{
    _indent -= 2;
}

std::ostream &
SceneGraphPrinter::indentStream(void)
{
    for(UInt32 i = 0; i < _indent; ++i)
        (*_pStream) << " ";

    return *_pStream;
}

std::ostream &
SceneGraphPrinter::getStream(void)
{
    return *_pStream;
}

Action::ResultE SceneGraphPrinter::traverseEnter(Node *node)
{
    if(node == NULL)
        return Action::Continue;

    std::ostream &os = getStream();
    incIndent();

    indentStream()
            <<   "[" << node
            << "] [" << node->getId()
            << "] [" << (getName(node) ? getName(node) : "<unnamed>")
            << "]";

    NodeCore *core = node->getCore();

    if(core == NULL)
    {
        os << "\n";
        return Action::Continue;
    }

    os << " -- [" << core
       <<   "] [" << core->getId()
       <<   "] [" << core->getType().getCName()
       <<   "]";

    os << " [" << (getName(core) ? getName(core) : "<unnamed>")
       << "]";

    NodeCore::MFParentsType::const_iterator pIt  = core->getMFParents()->begin();
    NodeCore::MFParentsType::const_iterator pEnd = core->getMFParents()->end  ();

    if(core->getMFParents()->size() > 1)
    {
        os << " # parents [" << core->getMFParents()->size() << "] #";

        for(; pIt != pEnd; ++pIt)
        {
            Node *parent = dynamic_cast<Node *>(*pIt);

            os <<  " [" << *pIt
            << "] [" << (getName(parent) ? getName(parent) : "<unnamed>")
            << "]";
        }
    }

    os << "\n";

    // if there is a print function registered for this core type call it
    PrintFuncMapConstIt pfIt = _printFuncMap.find(core->getType().getId());

    if(pfIt != _printFuncMap.end())
    {
        incIndent();
        (pfIt->second)(this, core);
        decIndent();
    }

    return Action::Continue;
}

Action::ResultE SceneGraphPrinter::traverseLeave(
    Node *node, Action::ResultE res)
{
    if(node == NULL)
        return Action::Continue;

    decIndent();

    return Action::Continue;
}

/*! \nohierarchy
 */

struct FieldPathEntry
{
    std::string szName;
    Int32       iIndex;
};

void splitFieldPath(      std::vector<FieldPathEntry> &vSplitPath,
                    const Char8                       *szFieldPath)
{
    std::string tmpName(szFieldPath);

    std::string::size_type sStart    = 0;
    std::string::size_type sEnd      = 0;
    std::string::size_type sLength   = 0;
    std::string::size_type sLastChar = 0;
    FieldPathEntry         tmpEntry;

    std::string            szIdx;

    do
    {
        sEnd = tmpName.find("/", sStart);

        if(sEnd != std::string::npos)
        {
            sLength = sEnd - sStart;
        }
        else
        {
            sLength = tmpName.length() - sStart;
        }
 
        sLastChar = sStart + sLength - 1;

        vSplitPath.push_back(tmpEntry);

        vSplitPath.back().iIndex = -1;

        if(tmpName[sLastChar] == ')')
        {
            std::string::size_type sIdxStart = 
                tmpName.rfind('(', sLastChar); //, sLength);

            if(sIdxStart == std::string::npos)
            {
                vSplitPath.clear();

                return;
            }

            tmpName[sIdxStart] = '$';
            tmpName[sLastChar] = '$';

            sLength -= sLastChar - sIdxStart + 1;

            ++sIdxStart;

            szIdx.assign(tmpName,
                         sIdxStart,
                         sLastChar - sIdxStart);

            vSplitPath.back().iIndex = 
                TypeTraits<UInt32>::getFromCString(szIdx.c_str());
        }

        vSplitPath.back().szName.assign(tmpName, sStart, sLength);

        sStart = sEnd + 1;
    }
    while(sEnd != std::string::npos);
}

FieldContainer *resolveFieldPath(std::vector<FieldPathEntry> &vSplitPath, 
                                 FieldContainer              *pRoot     )
{
    if(pRoot == NULL)
        return NULL;

    FieldContainer *returnValue = pRoot;

    OSG::GetFieldHandlePtr fHandle;

    for(UInt32 i = 1; i < vSplitPath.size(); ++i)
    {
        fHandle = returnValue->getField(vSplitPath[i].szName.c_str());

        if(fHandle == NULL || fHandle->isValid() == false) 
        {
            FWARNING(("Unknown field '%s'\n", 
                      vSplitPath[i].szName.c_str()));

            returnValue = NULL;

            break;
        }

        OSG::FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
            boost::dynamic_pointer_cast<
              OSG::FieldContainerPtrSFieldBase::GetHandle>(fHandle);
            
        OSG::FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
            boost::dynamic_pointer_cast<
                OSG::FieldContainerPtrMFieldBase::GetHandle>(fHandle);

        if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
        {
            returnValue = (*sfFCPtr)->getValue();
        }
        else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
        {
            UInt32 uiIndex = 
                vSplitPath[i].iIndex == -1 ? 0 : vSplitPath[i].iIndex;

            if(uiIndex >= mfFCPtr->size())
            {
                FWARNING(("Unknown index %d to large for field '%s'\n", 
                          uiIndex,
                          vSplitPath[i].szName.c_str()));
                
                returnValue = NULL;
                
                break;
            }

            returnValue = (**mfFCPtr)[uiIndex];
        }
    }

    return returnValue;
}

FieldContainer *resolveFieldPath(const Char8             *szNodeName, 
                                       ContainerResolver  oResolver )
{
    std::vector<FieldPathEntry> vSplitPath;

    splitFieldPath(vSplitPath, szNodeName);

    if(vSplitPath.size() == 0)
        return NULL;

    FieldContainer *returnValue = oResolver(vSplitPath[0].szName.c_str());

    returnValue = resolveFieldPath(vSplitPath, returnValue);

    return returnValue;
}

OSG_END_NAMESPACE
