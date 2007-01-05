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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGNodeCore.h"

OSG_USING_NAMESPACE

void NodeCore::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc;

    pDesc = new MFParentFieldContainerPtr::Description(
        MFParentFieldContainerPtr::getClassType(),
        "parents",
        "A list of parents for this core.",
        OSG_RC_FIELD_DESC(NodeCore::Parents),
        true,
        Field::SFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&NodeCore::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&NodeCore::getMFParents    ));

    oType.addInitialDesc(pDesc);
}

NodeCore::TypeObject NodeCore::_type(true,
    NodeCore ::getClassname(),
    Inherited::getClassname(),
    "NodeCores",
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &NodeCore::classDescInserter,
    false,
    "",
    "Base type for all objects that can be cores for a Node.");

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

NodeCore::NodeCore(void) :
     Inherited(),
    _mfParents()
{
}

NodeCore::NodeCore(const NodeCore &source) :
     Inherited(source           ),
    _mfParents(source._mfParents)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

NodeCore::~NodeCore(void)
{
}

void NodeCore::pushToField(      FieldContainerPtrConstArg pNewElement,
                           const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);
}

void NodeCore::insertIntoMField(const UInt32                    uiIndex,
                                      FieldContainerPtrConstArg pNewElement,
                                const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);
}

void NodeCore::replaceInMField(const UInt32                    uiIndex,
                                     FieldContainerPtrConstArg pNewElement,
                               const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);
}

void NodeCore::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                      FieldContainerPtrConstArg pNewElement,
                                const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);
}

void NodeCore::removeFromMField(const UInt32 uiIndex,
                                const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);
}

void NodeCore::removeFromMField(      FieldContainerPtrConstArg pElement,
                                const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);
}

void NodeCore::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);
}


/*------------------------------ access -----------------------------------*/

UInt32 NodeCore::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _mfParents.getBinSize();
    }

    return returnValue;
}

void NodeCore::copyToBin(BinaryDataHandler &pMem,
                         ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.copyToBin(pMem);
    }
}

void NodeCore::copyFromBin(BinaryDataHandler &pMem,
                           ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void NodeCore::invalidateVolume(void)
{
    for(UInt32 i = 0; i < _mfParents.size(); i++)
    {
        _mfParents[i]->invalidateVolume();
    }
}

const MFParentFieldContainerPtr &NodeCore::getParents(void) const
{
    return _mfParents;
}

const MFParentFieldContainerPtr *NodeCore::getMFParents(void) const
{
    return &_mfParents;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_ABSTR_FIELD_CONTAINER_DEF(NodeCore)

void NodeCore::accumulateMatrix(Matrixr &)
{
}

void NodeCore::adjustVolume(Volume &)
{
}

#ifdef OSG_MT_FIELDCONTAINERPTR
void NodeCore::execSyncV(      FieldContainer    &oFrom,
                               ConstFieldMaskArg  whichField,
                               ConstFieldMaskArg  syncMode  ,
                         const UInt32             uiSyncInfo,
                               UInt32             uiCopyOffset)
{
    this->execSync(static_cast<NodeCore *>(&oFrom),
                   whichField,
                   syncMode,
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void NodeCore::execSyncV(      FieldContainer    &oFrom,
                               ConstFieldMaskArg  whichField,
                               AspectOffsetStore &oOffsets,
                               ConstFieldMaskArg  syncMode  ,
                         const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<NodeCore *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#if 0
void NodeCore::execBeginEditV(ConstFieldMaskArg whichField,
                              UInt32            uiAspect,
                              UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

void NodeCore::dump(      UInt32    uiIndent,
                    const BitVector bvFlags ) const
{
    UInt32 i;

    ObjConstPtr thisP = Inherited::constructPtr<NodeCore>(this);

//    thisP.dump(0, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);

    PLOG << "Core"
         << "("
         << std::dec
         << getContainerId(thisP)
         << ") : "
         << getType().getName()
         << " "
//         << _attachmentMap.getValue().size()
         << " attachments | "
         << this
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << std::endl;

    for(i = 0; i < _mfParents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_mfParents[i])) << std::endl;
    }

    Inherited::dump(uiIndent + 4, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

#ifdef OSG_WINCE
ActionBase::ResultE NodeCore::defaultEnter(Action *)
{
    return ActionBase::Continue;
}

ActionBase::ResultE NodeCore::defaultLeave(Action *)
{
    return ActionBase::Continue;
}
#endif

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
    static Char8 cvsid_hpp[] = OSGNODECORE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGNODECORE_INLINE_CVSID;
}

