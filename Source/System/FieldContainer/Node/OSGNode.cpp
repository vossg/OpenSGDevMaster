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

#include "OSGLog.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGContainerPtrFuncs.h"

#include "OSGTypeBasePredicates.h"
#include "OSGReflexiveContainerTypePredicates.h"

#include "boost/bind.hpp"

OSG_BEGIN_NAMESPACE

void Node::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;

    pDesc = new SFDynamicVolume::Description(
        SFDynamicVolume::getClassType(),
        "volume",
        "Bounding volume for the node.",
        OSG_RC_FIELD_DESC(Node::Volume),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::editHandleVolume),
        static_cast<FieldGetMethodSig >(&Node::getHandleVolume ));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "travMask",
        "Traversal mask for the node.",
        OSG_RC_FIELD_DESC(Node::TravMask),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::editHandleTravMask),
        static_cast<FieldGetMethodSig >(&Node::getHandleTravMask ));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUncountedNodePtr::Description(
        SFUncountedNodePtr::getClassType(),
        "parent",
        "This node's parent.",
        OSG_RC_FIELD_DESC(Node::Parent),
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::invalidEditField),
        static_cast<FieldGetMethodSig >(&Node::getHandleParent ));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUnrecNodeCorePtr::Description(
        SFUnrecNodeCorePtr::getClassType(),
        "core",
        "The core to use for this node.",
        OSG_RC_FIELD_DESC(Node::Core),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::editHandleCore),
        static_cast<FieldGetMethodSig >(&Node::getHandleCore ));

    oType.addInitialDesc(pDesc);


    pDesc = new MFUnrecNodePtr::Description(
        MFUnrecNodePtr::getClassType(),
        "children",
        "A list of our children in the scene graph.",
        OSG_RC_FIELD_DESC(Node::Children),
        false,
        Field::MFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::editHandleChildren),
        static_cast<FieldGetMethodSig >(&Node::getHandleChildren));

    oType.addInitialDesc(pDesc);
}

Node::TypeObject Node::_type(
    Node     ::getClassname(),
    Inherited::getClassname(),
    "Node",
    0,
    (PrototypeCreateF) &Node::createEmptyLocal,
    NULL,
    NULL,
    (InitalInsertDescFunc) &Node::classDescInserter,
    false,
    0);


OSG_FIELD_CONTAINER_DEF(Node)

/*-------------------------------------------------------------------------*/
/*                                Set                                      */
/** Set the core for this node.
* If core is NullFC, then clears the node core.
* @param core The new node core to use
*/
void Node::setCore(NodeCorePtrConstArg core)
{
    editSField(CoreFieldMask);

//    addRef(core);

    if(_sfCore.getValue() != NullFC)
    {
        _sfCore.getValue()->subParent(this);

//        subRef(_sfCore.getValue());
    }

    _sfCore.setValue(core);

    if(_sfCore.getValue() != NullFC)
    {
        _sfCore.getValue()->addParent(this, CoreFieldId);
    }
}


/*-------------------------------------------------------------------------*/
/*                             Children                                    */

void Node::addChild(NodePtrConstArg childP)
{
    if(childP != NullFC)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
//        addRef(childP);
        editMField(ChildrenFieldMask, _mfChildren);

        _mfChildren.push_back(childP);

        // already somebody else's child?
        if(childP->getParent() != NullFC)
        {
            childP->getParent()->subChild(childP);
        }

        childP->setParent(this);
    }
}

void Node::addChild(NodeTransitPtr childP)
{
    if(childP != NullFC)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
//        addRef(childP);
        editMField(ChildrenFieldMask, _mfChildren);

        NodeUnrecPtr tmpChild = childP;

        _mfChildren.push_back(tmpChild);

        // already somebody else's child?
        if(tmpChild->getParent() != NullFC)
        {
            tmpChild->getParent()->subChild(tmpChild);
        }

        tmpChild->setParent(this);
    }
}

/*! Insert child node into child list.
* Upon completion, getChild(childIndex) will return the new child.
* (ie. child is at childIndex pos in list)
* All other children after childIndex are moved back in list.
* If childP is Null, does nothing.
*
* \warning childP is not ranged checked.  Out of range values will have undefined behavior.
* \param childIndex  The location in the list to put the new child.
* \param childP  Pointer to the child to insert.
*/
void Node::insertChild(UInt32 childIndex, NodePtrConstArg childP)
{
    OSG_ASSERT((childIndex <= getNChildren()) && "Child index out of range");

    if(childP != NullFC)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
//        addRef(childP);

        editMField(ChildrenFieldMask, _mfChildren);

//        MFNodePtr::iterator childIt = _mfChildren.begin();

//        childIt += childIndex;

//        _mfChildren.insert(childIt, childP);

        _mfChildren.replace(childIndex, childP);

        // already somebody else's child?
        if(childP->getParent() != NullFC)
        {
            childP->getParent()->subChild(childP);
        }

        childP->setParent(this);
    }
}

void Node::replaceChild(UInt32 childIndex, NodePtrConstArg childP)
{
    if(childP     != NullFC                  && 
       childIndex <  _mfChildren.size()      && 
       childP     != _mfChildren[childIndex]  )
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)
//        addRef(childP);

        // remove the current child
        _mfChildren[childIndex]->setParent(NullFC);

//        subRef(_mfChildren[childIndex]);

        editMField(ChildrenFieldMask, _mfChildren);

        // set the new child
//        _mfChildren[childIndex] = childP;

        // already somebody else's child?
        if(childP->getParent() != NullFC)
        {
            childP->getParent()->subChild(childP);
        }

        childP->setParent(this);
    }
}

//! return true on success, false on child not found

bool Node::replaceChildBy(NodePtrConstArg childP,
                          NodePtrConstArg newChildP)
{
    if(newChildP != NullFC && childP != newChildP)
    {
        Int32 childIdx = findChild(childP);

        if(childIdx != -1)
        {
            // do the ref early, to prevent destroys on
            // getParent(a)->addChild(a)

//            addRef(newChildP);

            childP->setParent(NullFC);

//            subRef(childP);

            editMField(ChildrenFieldMask, _mfChildren);

//            _mfChildren[childIdx] = newChildP;

            _mfChildren.replace(childIdx, newChildP);

            // already somebody else's child?
            if(newChildP->getParent() != NullFC)
            {
                newChildP->getParent()->subChild(newChildP);
            }

            newChildP->setParent(this);

            return true;
        }
    }

    return false;
}

Int32 Node::findChild(NodePtrConstArg childP) const
{
    UInt32 index;

    for(index = 0; index < _mfChildren.size(); index++)
    {
        if( _mfChildren[index] == childP)
            break;
    }

    if(index < _mfChildren.size())
    {
        return index;
    }
    else
    {
        return -1;
    }
}

void Node::subChild(NodePtrConstArg childP)
{
    Int32 childIdx = findChild(childP);

    if(childIdx != -1)
    {
        editMField(ChildrenFieldMask, _mfChildren);

        MFUnrecNodePtr::iterator childIt = _mfChildren.begin();

        childIt += childIdx;

        childP->setParent(NullFC);

//        subRef(childP);

        _mfChildren.erase(childIt);
    }
    else
    {
        SWARNING << "Node(" << this << ")::subChild: " << childP
                 << " is not one of my children!" << std::endl;
    }
}

void Node::subChild(UInt32 childIndex)
{
    if(childIndex < _mfChildren.size())
    {
        editMField(ChildrenFieldMask, _mfChildren);

        MFUnrecNodePtr::iterator childIt = _mfChildren.begin();

        childIt += childIndex;

        (*childIt)->setParent(NullFC);

//        subRef(*childIt);

        _mfChildren.erase(childIt);
    }
}

void Node::clearChildren(void)
{
    while(getNChildren() != 0)
    {
        subChild(0u);
    }
}

#if 0
void Node::pushToField(      FieldContainerPtrConstArg pNewElement,
                       const UInt32                    uiFieldId  )
{
    Inherited::pushToField(pNewElement, uiFieldId);

    if(uiFieldId == CoreFieldId)
    {
        setCore(dynamic_cast<NodeCorePtr>(pNewElement));
    }
    else if(uiFieldId == ChildrenFieldId)
    {
        addChild(dynamic_cast<NodePtr>(pNewElement));
    }
}

void Node::insertIntoMField(const UInt32                    uiIndex,
                                  FieldContainerPtrConstArg pNewElement,
                            const UInt32                    uiFieldId  )
{
    Inherited::insertIntoMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId == ChildrenFieldId)
    {
        insertChild(uiIndex,
                    dynamic_cast<NodePtr>(pNewElement));
    }
}

void Node::replaceInMField(const UInt32                    uiIndex,
                                 FieldContainerPtrConstArg pNewElement,
                           const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(uiIndex, pNewElement, uiFieldId);

    if(uiFieldId & ChildrenFieldId)
    {
        replaceChild(uiIndex,
                    dynamic_cast<NodePtr>(pNewElement));
    }
}

void Node::replaceInMField (      FieldContainerPtrConstArg pOldElement,
                                  FieldContainerPtrConstArg pNewElement,
                            const UInt32                    uiFieldId  )
{
    Inherited::replaceInMField(pOldElement, pNewElement, uiFieldId);

    if(uiFieldId == ChildrenFieldId)
    {
        replaceChildBy(dynamic_cast<NodePtr>(pOldElement),
                       dynamic_cast<NodePtr>(pNewElement));
    }
}

void Node::removeFromMField(const UInt32 uiIndex,
                            const UInt32 uiFieldId)
{
    Inherited::removeFromMField(uiIndex, uiFieldId);

    if(uiFieldId == ChildrenFieldId)
    {
        subChild(uiIndex);
    }
}

void Node::removeFromMField(      FieldContainerPtrConstArg pElement,
                            const UInt32                    uiFieldId)
{
    Inherited::removeFromMField(pElement, uiFieldId);

    if(uiFieldId == ChildrenFieldId)
    {
        subChild(dynamic_cast<NodePtr>(pElement));
    }
}

void Node::clearField(const UInt32 uiFieldId)
{
    Inherited::clearField(uiFieldId);

    if(uiFieldId == CoreFieldId)
    {
        setCore(NullFC);
    }
    else if(uiFieldId == ChildrenFieldId)
    {
        while(getNChildren() != 0)
        {
            subChild(0u);
        }
    }
}
#endif

UInt32 Node::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        returnValue += _sfVolume.getBinSize();
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        returnValue += _sfTravMask.getBinSize();
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        returnValue += _sfParent.getBinSize();
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        returnValue += _mfChildren.getBinSize();
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        returnValue += _sfCore.getBinSize();
    }

    return returnValue;
}

void Node::copyToBin(BinaryDataHandler &pMem,
                     ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyToBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.copyToBin(pMem);
    }
}

void Node::copyFromBin(BinaryDataHandler &pMem,
                       ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                           Get Transformation                            */

Matrixr Node::getToWorld(void)
{
    Matrixr tmp;

    getToWorld(tmp);

    return tmp;
}

void Node::getToWorld(Matrixr &result)
{
    if(getParent() != NullFC)
    {
        getParent()->getToWorld(result);
    }
    else
    {
        result.setIdentity();
    }

    if(getCore() != NullFC)
        getCore()->accumulateMatrix(result);
}

/*-------------------------------------------------------------------------*/
/*                           Volume                                        */

void Node::getWorldVolume(DynamicVolume &result)
{
    Matrixr m;

    if(getParent() != NullFC)
    {
        getParent()->getToWorld(m);
    }
    else
    {
        m.setIdentity();
    }

    updateVolume();

    result = getVolume();
    result.transform(m);
}

void Node::updateVolume(void)
{
    // still valid, nothing to do
    if(_sfVolume.getValue().getInstance().isValid() == true ||
       getTravMask()                                == 0x0000)
    {
        return;
    }

    // be careful to not change the real volume. If two threads
    // are updating the same aspect this will lead to chaos

    DynamicVolume vol = _sfVolume.getValue();

    MFUnrecNodePtr::iterator it;

    vol.getInstance().setEmpty();

    for(it = _mfChildren.begin(); it != _mfChildren.end(); ++it)
    {
        if((*it)->getTravMask())
        {
            (*it)->updateVolume();
            vol.getInstance().extendBy((*it)->getVolume());
        }
    }

    // test for null core. Shouldn't happen, but just in case...
    if(getCore() != NullFC)
    {
        getCore()->adjustVolume(vol.getInstance());
    }

    editSField(VolumeFieldMask);

    vol.instanceChanged();

    _sfVolume.setValue(vol);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Node::Node(void) :
     Inherited (                            ),
    _sfVolume  (                            ),
    _sfTravMask(TypeTraits<UInt32>::getMax()),
    _sfParent  (NullFC                      ),
    _mfChildren(                            ),
    _sfCore    (NullFC                      )
#ifdef OSG_1_COMPAT
   ,_occlusionMask(0)
#endif
{
}

Node::Node(const Node &source) :
     Inherited    (source            ),
    _sfVolume     (                  ),

    _sfTravMask   (source._sfTravMask),

    _sfParent     (NullFC            ),
    _mfChildren   (                  ),

    _sfCore       (NullFC            )
#ifdef OSG_1_COMPAT
   ,_occlusionMask(source._occlusionMask)
#endif
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Node::~Node(void)
{
}

void Node::invalidateVolume(void)
{
    Volume &vol=_sfVolume.getValue().getInstance();

    if(vol.isValid() == true && vol.isStatic() == false)
    {
        editSField(VolumeFieldMask);

        vol.setValid(false);

        _sfVolume.getValue().instanceChanged();

        if(getParent() != NullFC)
        {
            getParent()->invalidateVolume();
        }
    }
}

void Node::changed(ConstFieldMaskArg whichField,
                   UInt32            origin,
                   BitVector         details    )
{
    Inherited::changed(whichField, origin, details);

    if(whichField & (CoreFieldMask | ChildrenFieldMask))
    {
        invalidateVolume();
    }

    if(whichField & TravMaskFieldMask)
    {
        if(getParent() != NullFC)
        {
            getParent()->invalidateVolume();
        }
        else
        {
            invalidateVolume();
        }
    }
}

void Node::dump(      UInt32    uiIndent,
                const BitVector bvFlags ) const
{
    UInt32 i;

    indentLog(uiIndent, PLOG);

    PLOG << "Node"
         << "("
         << getContainerId(this)
         << ") : "
         << _mfChildren.size()
         << " children | "
//         << _attachmentMap.getValue().size()
         << " attachments | "
         << "Parent : " << std::hex;

    if(_sfParent.getValue() != NullFC)
    {
        PLOG << getContainerId(_sfParent.getValue()) << " | ";
    }
    else
    {
        PLOG << "NULL | ";
    }

    PLOG << this << std::dec << std::endl;

    indentLog(uiIndent, PLOG);

    PLOG << "[" << std::endl;

    if(_sfCore.getValue() != NullFC)
    {
        _sfCore.getValue()->dump(uiIndent + 4, bvFlags);
    }
    else
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "Core : " << "NULL" << std::endl;
    }

    Inherited::dump(uiIndent + 4, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);

    PLOG << "{" << std::endl;

    for(i = 0; i < _mfChildren.size(); i++)
    {
        _mfChildren[i]->dump(uiIndent + 4, bvFlags);
        PLOG << std::endl;
    }


    indentLog(uiIndent, PLOG);

    PLOG << "}" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

SFDynamicVolume *Node::editSFVolume(void)
{
    editSField(VolumeFieldMask);

    return &_sfVolume;
}

const SFDynamicVolume *Node::getSFVolume(void) const
{
    return &_sfVolume;
}

SFUInt32 *Node::editSFTravMask(void)
{
    editSField(TravMaskFieldMask);

    return &_sfTravMask;
}

const SFUInt32 *Node::getSFTravMask(void) const
{
    return &_sfTravMask;
}

const SFUncountedNodePtr *Node::getSFParent(void) const
{
    return &_sfParent;
}

const SFUnrecNodeCorePtr *Node::getSFCore(void) const
{
    return &_sfCore;
}

const MFUnrecNodePtr *Node::getMFChildren(void) const
{
    return &_mfChildren;
}

#ifdef OSG_MT_CPTR_ASPECT
Node::ObjPtr Node::createAspectCopy(void) const
{
    NodePtr returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const Node *>(this));

    return returnValue;
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void Node::execSyncV(      FieldContainer     &oFrom,
                            ConstFieldMaskArg  whichField,
                            AspectOffsetStore &oOffsets,
                            ConstFieldMaskArg  syncMode  ,
                      const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<Node *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

EditFieldHandlePtr Node::editHandleVolume(void)
{
    SFDynamicVolume::EditHandlePtr returnValue(
        new  SFDynamicVolume::EditHandle(
             &_sfVolume, 
             this->getType().getFieldDesc(VolumeFieldId)));

    editSField(VolumeFieldMask);

    return returnValue;
}

GetFieldHandlePtr  Node::getHandleVolume(void) const
{
    SFDynamicVolume::GetHandlePtr returnValue(
        new  SFDynamicVolume::GetHandle(
             &_sfVolume, 
             this->getType().getFieldDesc(VolumeFieldId)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleTravMask(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfTravMask, 
             this->getType().getFieldDesc(TravMaskFieldId)));

    editSField(TravMaskFieldMask);

    return returnValue;
}

GetFieldHandlePtr Node::getHandleTravMask(void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfTravMask, 
             this->getType().getFieldDesc(TravMaskFieldId)));

    return returnValue;
}

GetFieldHandlePtr Node::getHandleParent(void) const
{
    SFUncountedNodePtr::GetHandlePtr returnValue(
        new SFUncountedNodePtr::GetHandle(
             &_sfParent, 
             this->getType().getFieldDesc(ParentFieldId)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleCore(void)
{
    SFUnrecNodeCorePtr::EditHandlePtr returnValue(
        new  SFUnrecNodeCorePtr::EditHandle(
             &_sfCore, 
             this->getType().getFieldDesc(CoreFieldId)));

    typedef void (Node::*SetCoreF)(NodeCorePtrConstArg);
    
    SetCoreF fFunc = &Node::setCore;

    returnValue->setSetMethod(boost::bind(fFunc, this, _1));

    editSField(CoreFieldMask);

    return returnValue;
}

GetFieldHandlePtr Node::getHandleCore(void) const
{
    SFUnrecNodeCorePtr::GetHandlePtr returnValue(
        new  SFUnrecNodeCorePtr::GetHandle(
             &_sfCore, 
             this->getType().getFieldDesc(CoreFieldId)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleChildren(void)
{
    MFUnrecNodePtr::EditHandlePtr returnValue(
        new  MFUnrecNodePtr::EditHandle(
             &_mfChildren, 
             this->getType().getFieldDesc(ChildrenFieldId)));

    typedef void (Node::*AddChildF)(NodePtrConstArg);

    AddChildF fFunc = &Node::addChild;

    returnValue->setAddMethod(boost::bind(fFunc, this, _1));

    editMField(ChildrenFieldMask, _mfChildren);

    return returnValue;
}

GetFieldHandlePtr  Node::getHandleChildren(void) const
{
    MFUnrecNodePtr::GetHandlePtr returnValue(
        new  MFUnrecNodePtr::GetHandle(
             &_mfChildren, 
             this->getType().getFieldDesc(ChildrenFieldId)));

    return returnValue;
}

void Node::resolveLinks(void)
{
    Inherited::resolveLinks();

    if(_sfCore.getValue() != NullFC)
    {
        _sfCore.getValue()->subParent(this);

//        subRef(_sfCore.getValue());
        _sfCore.setValue(NullFC);
    }

    MFUnrecNodePtr::iterator       vChildIt    = _mfChildren.begin();
    MFUnrecNodePtr::const_iterator endChildren = _mfChildren.end  ();

    while(vChildIt != endChildren)
    {
        (*vChildIt)->setParent(NullFC);

//        subRef(*vChildIt);
//        _mfChildren.replace(vChildIt, NullFC);

        ++vChildIt;
    }

    _mfChildren.clear();
}

/*-------------------------------------------------------------------------*/
/*                             Cloning                                     */

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are shared, only if a container's type name is in
    \a cloneTypeNames or if it belonfs to a group in \a cloneGroupNames it is
    cloned. If a container's type is in \a ignoreTypeNames or belongs to a 
    group in \a ignoreGroupNames it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] cloneTypeNames List of type names that are cloned.
    \param[in] ignoreTypeNames List of type names that are ignored.
    \param[in] cloneGroupNames List of group names that are cloned.
    \param[in] ignoreGroupNames LIst of group names that are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr cloneTree(      NodePtrConstArg           rootNode,
                         const std::vector<std::string> &cloneTypeNames,
                         const std::vector<std::string> &ignoreTypeNames,
                         const std::vector<std::string> &cloneGroupNames,
                         const std::vector<std::string> &ignoreGroupNames)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         cloneGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesVector (cloneTypeNames,   cloneTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(cloneGroupNames,  cloneGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    return cloneTree(rootNode, cloneTypes,    ignoreTypes,
                               cloneGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are shared, only if a container's group id is in
    \a cloneGroupIds it is cloned. If a container's group id is in
    \a ignoreGroupIds it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] cloneGroupIds List of group ids, whose members are cloned.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr cloneTree(      NodePtrConstArg      rootNode,
                         const std::vector<UInt16> &cloneGroupIds,
                         const std::vector<UInt16> &ignoreGroupIds)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;

    return cloneTree(rootNode, cloneTypes,    ignoreTypes,
                               cloneGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are shared, only if a container's type name is in
    \a cloneTypesString it is cloned. If a container's type is in
    \a ignoreTypesString it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] cloneTypesString Comma separated string of type names that are
        cloned instead of shared.
    \param[in] ignoreTypesString Comma separated string of type names that are
        ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr cloneTree(      NodePtrConstArg  rootNode,
                         const std::string     &cloneTypesString,
                         const std::string     &ignoreTypesString)
{
    std::vector<const ReflexiveContainerType *> cloneTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         cloneGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesString(cloneTypesString,  cloneTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    return cloneTree(rootNode, cloneTypes,    ignoreTypes,
                               cloneGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are shared, only if a container's type is in
    \a cloneTypes of belongs to a group in \a cloneGroupIds it is cloned.
    If a container's type is in \a ignoreTypes or belongs to a group in
    \a ignoreGroupIds it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] cloneTypes List of types to clone instead of share.
    \param[in] ignoreTypes List of types to ignore.
    \param[in] cloneGroupIds List of group ids, whose members are cloned.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr cloneTree(      
          NodePtrConstArg                              rootNode,
    const std::vector<const ReflexiveContainerType *> &cloneTypes,
    const std::vector<const ReflexiveContainerType *> &ignoreTypes,
    const std::vector<UInt16>                         &cloneGroupIds,
    const std::vector<UInt16>                         &ignoreGroupIds)
{
    NodeUnrecPtr rootClone(NULL);

    if(rootNode != NullFC)
    {
        NodeUnrecPtr childClone;
        NodeCorePtr  core       = rootNode->getCore();

        rootClone = Node::create();
        rootClone->setTravMask(rootNode->getTravMask());

        cloneAttachments(rootNode,      rootClone,
                         cloneTypes,    ignoreTypes,
                         cloneGroupIds, ignoreGroupIds);

        if(core != NullFC)
        {
                  NodeCoreUnrecPtr    coreClone  = NullFC;
            const FieldContainerType &coreType   = core->getType();

            // test if core type should NOT be ignored
            if(!TypePredicates::typeInGroupIds(
                    ignoreGroupIds.begin(),
                    ignoreGroupIds.end(), coreType) &&
               !TypePredicates::typeDerivedFrom(
                    ignoreTypes.begin(),
                    ignoreTypes.end(),    coreType)   )
            {
                // test if core should cloned
                if(TypePredicates::typeInGroupIds (
                       cloneGroupIds.begin(),
                       cloneGroupIds.end(), coreType) ||
                   TypePredicates::typeDerivedFrom(
                       cloneTypes.begin(),
                       cloneTypes.end(),    coreType)   )
                {
                    // clone core
                    coreClone = 
                        dynamic_pointer_cast<NodeCore>(
                            deepClone(core,
                                      cloneTypes,    ignoreTypes,
                                      cloneGroupIds, ignoreGroupIds));
                }
                else
                {
                    // share core
                    coreClone = core;
                }
            }

            rootClone->setCore(coreClone);
        }

        for(UInt32 i = 0; i < rootNode->getNChildren(); ++i)
        {
            childClone = cloneTree(rootNode->getChild(i),
                                   cloneTypes,    ignoreTypes,
                                   cloneGroupIds, ignoreGroupIds);

            rootClone->addChild(childClone);
        }
    }

    return NodeTransitPtr(rootClone);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are cloned, only if a container's type name is in
    \a shareTypeNames or if it belonfs to a group in \a shareGroupNames it is
    shared. If a container's type is in \a ignoreTypeNames or belongs to a
    group in \a ignoreGroupNames it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] shareTypeNames List of type names that are shared.
    \param[in] ignoreTypeNames List of type names that are ignored.
    \param[in] shareGroupNames List of group names that are shared.
    \param[in] ignoreGroupNames LIst of group names that are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr deepCloneTree(      NodePtrConstArg           rootNode,
                             const std::vector<std::string> &shareTypeNames,
                             const std::vector<std::string> &ignoreTypeNames,
                             const std::vector<std::string> &shareGroupNames,
                             const std::vector<std::string> &ignoreGroupNames)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesVector (shareTypeNames,   shareTypes    );
    appendTypesVector (ignoreTypeNames,  ignoreTypes   );
    appendGroupsVector(shareGroupNames,  shareGroupIds );
    appendGroupsVector(ignoreGroupNames, ignoreGroupIds);

    return deepCloneTree(rootNode, shareTypes,    ignoreTypes,
                                   shareGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are cloned, only if a container's group id is in
    \a shareGroupIds it is shared. If a container's group id is in
    \a ignoreGroupIds it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] shareGroupIds List of group ids, whose members are shared.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr deepCloneTree(      NodePtrConstArg      rootNode,
                             const std::vector<UInt16> &shareGroupIds,
                             const std::vector<UInt16> &ignoreGroupIds)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;

    return deepCloneTree(rootNode, shareTypes,    ignoreTypes,
                                   shareGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are cloned, only if a container's type name is in
    \a shareTypesString it is shared. If a container's type is in
    \a ignoreTypesString it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] shareTypesString Comma separated string of type names that are
        shared instead of cloned.
    \param[in] ignoreTypesString Comma separated string of type names that are
        ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr deepCloneTree(      NodePtrConstArg  rootNode,
                             const std::string     &shareTypesString,
                             const std::string     &ignoreTypesString)
{
    std::vector<const ReflexiveContainerType *> shareTypes;
    std::vector<const ReflexiveContainerType *> ignoreTypes;
    std::vector<UInt16>                         shareGroupIds;
    std::vector<UInt16>                         ignoreGroupIds;

    appendTypesString(shareTypesString,  shareTypes);
    appendTypesString(ignoreTypesString, ignoreTypes);

    return deepCloneTree(rootNode, shareTypes,    ignoreTypes,
                                   shareGroupIds, ignoreGroupIds);
}

/*! Clones the scene starting at \a rootNode. By default FieldContainers,
    especially NodeCores, are cloned, only if a container's type is in
    \a shareTypes of belongs to a group in \a shareGroupIds it is shared.
    If a container's type is in \a ignoreTypes or belongs to a group in
    \a ignoreGroupIds it is ignored altogether.

    \param[in] rootNode Root of the scene to clone.
    \param[in] shareTypes List of types to share instead of clone.
    \param[in] ignoreTypes List of types to ignore.
    \param[in] shareGroupIds List of group ids, whose members are shared.
    \param[in] ignoreGroupIds List of group ids, whose members are ignored.
    \return The root Node of the cloned scene.
 */

NodeTransitPtr deepCloneTree(      
          NodePtrConstArg                              rootNode,
    const std::vector<const ReflexiveContainerType *> &shareTypes,
    const std::vector<const ReflexiveContainerType *> &ignoreTypes,
    const std::vector<UInt16>                         &shareGroupIds,
    const std::vector<UInt16>                         &ignoreGroupIds)
{
    NodeUnrecPtr rootClone(NULL);

    if(rootNode != NullFC)
    {
        NodeUnrecPtr childClone;
        NodeCorePtr  core       = rootNode->getCore();

        rootClone = Node::create();
        rootClone->setTravMask(rootNode->getTravMask());

        deepCloneAttachments(rootNode,      rootClone,
                             shareTypes,    ignoreTypes,
                             shareGroupIds, ignoreGroupIds);

        if(core != NullFC)
        {
                  NodeCoreUnrecPtr    coreClone(NULL);
            const FieldContainerType &coreType   = core->getType();

            // test if core type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (
                    ignoreGroupIds.begin(),
                    ignoreGroupIds.end(), coreType) &&
               !TypePredicates::typeDerivedFrom(
                    ignoreTypes.begin(),
                    ignoreTypes.end(),    coreType)   )
            {
                // test if core should be shared
                if(TypePredicates::typeInGroupIds (
                       shareGroupIds.begin(),
                       shareGroupIds.end(), coreType) ||
                   TypePredicates::typeDerivedFrom(
                       shareTypes.begin(),
                       shareTypes.end(),    coreType)   )
                {
                    // share core
                    coreClone = core;
                }
                else
                {
                    // clone core
                    coreClone = 
                        dynamic_pointer_cast<NodeCore>(
                            deepClone(core,
                                      shareTypes,    ignoreTypes,
                                      shareGroupIds, ignoreGroupIds));
                }
            }

            rootClone->setCore(coreClone);
        }

        for(UInt32 i = 0; i < rootNode->getNChildren(); ++i)
        {
            childClone = deepCloneTree(rootNode->getChild(i),
                                       shareTypes,    ignoreTypes,
                                       shareGroupIds, ignoreGroupIds);

            rootClone->addChild(childClone);
        }
    }

    return NodeTransitPtr(rootClone);
}

OSG_END_NAMESPACE
