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
        static_cast<FieldEditMethodSig>(&NodeCore::invalidEditField),
        static_cast<FieldGetMethodSig >(&NodeCore::getHandleParents));

    oType.addInitialDesc(pDesc);
}

NodeCore::TypeObject NodeCore::_type(
    NodeCore ::getClassname(),
    Inherited::getClassname(),
    "NodeCores",
    0,
    NULL,
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(&NodeCore::classDescInserter),
    false,
    0,
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
     Inherited(source),
    _mfParents(      )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

NodeCore::~NodeCore(void)
{
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

void NodeCore::dump(      UInt32    uiIndent,
                    const BitVector bvFlags ) const
{
    UInt32 i;

//    thisP.dump(0, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);

    PLOG << "Core"
         << "("
         << std::dec
         << this->getId()
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

GetFieldHandlePtr NodeCore::getHandleParents(void) const
{
    MFParentFieldContainerPtr::GetHandlePtr returnValue(
        new  MFParentFieldContainerPtr::GetHandle(
             &_mfParents, 
             this->getType().getFieldDesc(ParentsFieldId)));

    return returnValue;
}

bool NodeCore::linkParent(FieldContainer * const pParent,
                          UInt16           const childFieldId,
                          UInt16           const parentFieldId)
{
    if(parentFieldId == ParentsFieldId)
    {       
        FieldContainer *pTypedParent = 
            dynamic_cast<FieldContainer *>(pParent);
        
        if(pTypedParent != NULL)
        {
            editMField(ParentsFieldMask, _mfParents);
            
            _mfParents.push_back(pParent, childFieldId);
            
            return true;
        }
            
        return false;
    }
    
    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool NodeCore::unlinkParent(FieldContainer * const pParent,
                            UInt16           const parentFieldId)
{
    if(parentFieldId == ParentsFieldId)
    {               
        FieldContainer *pTypedParent = 
            dynamic_cast<FieldContainer *>(pParent);
        
        if(pTypedParent != NULL)
        {
            Int32 iParentIdx = _mfParents.findIndex(pParent);

            if(iParentIdx != -1)
            {
                editMField(ParentsFieldMask, _mfParents);
            
                _mfParents.erase(iParentIdx);

                return true;
            }
            
            FWARNING(("NodeCore::unlinkParent: Child <-> Parent link "
                      "inconsistent.\n"));
                
            return false;            
        }
        
        return false;
    }
    
    return Inherited::unlinkParent(pParent, parentFieldId);
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
