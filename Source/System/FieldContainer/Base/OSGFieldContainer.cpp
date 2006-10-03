/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGFieldContainer.h"
#include "OSGContainerPtrFuncs.h"

#include <algorithm>
#include <cctype>

#define SILENT

OSG_USING_NAMESPACE

void FieldContainer::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;

    pDesc = new MFChangedFunctorCallback::Description(
        MFChangedFunctorCallback::getClassType(),
        "changedCallbacks",
        "List of callback functors to notify of changes.",
        OSG_RC_FIELD_DESC(FieldContainer::ChangedCallbacks),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&FieldContainer::invalidEditField),
        static_cast<FieldGetMethodSig >(&FieldContainer::invalidGetField ));

    oType.addInitialDesc(pDesc);
}

FieldContainer::TypeObject FieldContainer::_type(true,
    FieldContainer::getClassname(),
    NULL,
    NULL,
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &FieldContainer::classDescInserter,
    false);


FieldContainer::TypeObject &FieldContainer::getType(void)
{
    return _type;
}

const FieldContainer::TypeObject &FieldContainer::getType(void) const
{
    return _type;
}

void FieldContainer::dump(      UInt32    uiIndent,
                          const BitVector bvFlags ) const
{
    indentLog(uiIndent, PLOG);

    PLOG << "FieldContainer : "
         << getType().getName()
         << std::endl;
}

void FieldContainer::pushToField(      FieldContainerPtrConstArg pNewElement,
                                 const UInt32                    uiFieldId  )
{

}

void FieldContainer::insertIntoMField(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId  )
{
}

void FieldContainer::replaceInMField(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId )
{
}

void FieldContainer::replaceInMField(
          FieldContainerPtrConstArg pOldElement,
          FieldContainerPtrConstArg pNewElement,
    const UInt32                    uiFieldId  )
{
}

void FieldContainer::removeFromMField(const UInt32 uiIndex,
                                      const UInt32 uiFieldId)
{
}

void FieldContainer::removeFromMField(
          FieldContainerPtrConstArg pElement,
    const UInt32                    uiFieldId)
{
}

void FieldContainer::clearField(const UInt32 uiFieldId)
{
}

void FieldContainer::copyFromBin(BinaryDataHandler  &,
                                 ConstFieldMaskArg   whichField)
{
    editSField(whichField);
}


void FieldContainer::invalidateVolume(void)
{
}

void FieldContainer::registerChangedContainer(void)
{
    FieldContainerPtr thisP = getPtr();

#ifndef SILENT
    fprintf(stderr, "reg changed %p 0x%016llx\n",
            _pContainerChanges, _bvChanged);
#endif

    if(_pContainerChanges == NULL)
    {
        _pContainerChanges =
            Thread::getCurrentChangeList()->getNewEntry(_bvChanged);

        _pContainerChanges->uiEntryDesc   = ContainerChangeEntry::Change;
        _pContainerChanges->pFieldFlags   = _pFieldFlags;
        _pContainerChanges->uiContainerId = getContainerId(thisP);
    }

    Thread::getCurrentChangeList()->addUncommited(_pContainerChanges);
}

void FieldContainer::registerChangedContainerV(void)
{
    registerChangedContainer();
}


bool FieldContainer::deregister(UInt32 uiContainerId)
{
    return FieldContainerFactory::the()->deregisterContainer(uiContainerId);
}

void FieldContainer::resolveLinks(void)
{
    callChangedFunctors(0);
}


void OSG::splitShareString(const std::string               &shareString,
                                 std::vector<std::string> &shareList  )
{
    shareList.clear();

    // parse comma separated names.
    std::string::const_iterator nextComma;
    std::string::const_iterator curPos = shareString.begin();

    while(curPos < shareString.end())
    {
        nextComma = std::find(curPos, shareString.end(), ',');

        // strip leading spaces
        curPos = std::find_if(curPos,
                              nextComma,
                              std::not1(std::ptr_fun(isspace)));

        shareList.push_back(std::string(curPos, nextComma));

        curPos = ++nextComma;
    }
}

void OSG::fillGroupShareList(const std::vector<UInt16     > &shareGroupIds,
                                   std::vector<std::string> &shareList    )
{
    shareList.clear  ();
    shareList.reserve(shareGroupIds.size());

    for(UInt32 i = 0; i < shareGroupIds.size(); ++i)
    {
        const Char8 *name =
            FieldContainerFactory::the()->findGroupName(shareGroupIds[i]);

        if(name != NULL)
            shareList.push_back(name);
    }
}

// deep clone of a fieldcontainer.
FieldContainerPtr OSG::deepClone(      FieldContainerPtrConstArg  src,
                                 const std::vector<std::string>  &share)
{
    if(src == NullFC)
        return NullFC;

    const FieldContainerType &type   = src->getType();

    //FDEBUG(("deepClone: fieldcontainertype = %s\n", type.getCName()));

    FieldContainerPtr dst =
        FieldContainerFactory::the()->createContainer(
            type.getName().str());

//          UInt32              fcount = type.getNumFieldDescs();
    UInt32 fcount = osgMin(     type     .getNumFieldDescs(),
                           dst->getType().getNumFieldDescs());

    for(UInt32 i = 1;i <= fcount;++i)
    {
        const FieldDescriptionBase *fdesc = type.getFieldDesc(i);

        if(fdesc->isInternal())
            continue;

        BitVector mask = fdesc->getFieldMask();

        const Field * srcField = src->getField (i);

              Field * dstField = dst->editField(i);
        const Field *cdstField = dst->getField (i);

        if(dstField != NULL)
        {
            fdesc->copyValues (srcField, dstField);
        }
        else
        {
            fdesc->cloneValuesV(srcField, mask, share, dst);
        }
    }

    return dst;
}

FieldContainerPtr OSG::deepClone(
           FieldContainerPtrConstArg  src,
     const std::vector<UInt16>       &shareGroupIds)
{
    std::vector<std::string> share;

    fillGroupShareList(shareGroupIds, share);

    return OSG::deepClone(src, share);
}

// shareString is a comma separated FieldContainer type list
// e.g. "Material, Geometry"
FieldContainerPtr OSG::deepClone(      FieldContainerPtrConstArg  src,
                                 const std::string               &shareString)
{
    std::vector<std::string> share;

    splitShareString(shareString, share);

    return OSG::deepClone(src, share);
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINER_INLINE_CVSID;
}

