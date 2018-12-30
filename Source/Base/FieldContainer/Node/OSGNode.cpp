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

#include "OSGTypeBasePredicates.h"
#include "OSGReflexiveContainerTypePredicates.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn of 'this' : used in base member initializer lits warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Node
    Node describe the hierarchical tree structure of the scenegraph. Every Node
    can have at most one parent and one core (something derived from
    NodeCore), but an arbitrary number of children.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var BoxVolume   Node::_sfVolume
    The bounding volume of this node. It contains all the nodes children and
    is described in this nodes coordinate system.
 */

/*! \var UInt32          Node::_sfTravMask
    The traversal mask is used to selectively exclude subtrees of the scenegraph
    from traversal operations (e.g. GraphOps, RenderAction). Only if
    the bitwise AND of the operation's and node's mask is non-zero the node
    (and it's subtree) considered.
 */

/*! \var NodeParentPtr   Node::_sfParent
    The node's single parent.
 */

/*! \var NodePtr         Node::_mfChildren
    The node's children.
 */

/*! \var NodeCorePtr     Node::_sfCore
 */

void Node::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;

    pDesc = new SFBoxVolume::Description(
        SFBoxVolume::getClassType(),
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


    pDesc = new SFParentNodePtr::Description(
        SFParentNodePtr::getClassType(),
        "parent",
        "This node's parent.",
        OSG_RC_FIELD_DESC(Node::Parent),
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Node::invalidEditField),
        static_cast<FieldGetMethodSig >(&Node::getHandleParent ));

    oType.addInitialDesc(pDesc);


    pDesc = new SFUnrecChildNodeCorePtr::Description(
        SFUnrecChildNodeCorePtr::getClassType(),
        "core",
        "The core to use for this node.",
        OSG_RC_FIELD_DESC(Node::Core),
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&Node::editHandleCore),
        static_cast<FieldGetMethodSig >(&Node::getHandleCore ));

    oType.addInitialDesc(pDesc);


    pDesc = new MFUnrecChildNodePtr::Description(
        MFUnrecChildNodePtr::getClassType(),
        "children",
        "A list of our children in the scene graph.",
        OSG_RC_FIELD_DESC(Node::Children),
        false,
        (Field::MFDefaultFlags | Field::FNullCheckAccess),
        static_cast<FieldEditMethodSig>(&Node::editHandleChildren),
        static_cast<FieldGetMethodSig >(&Node::getHandleChildren));

    oType.addInitialDesc(pDesc);
}

Node::TypeObject Node::_type(
    Node     ::getClassname(),
    Inherited::getClassname(),
    "Node",
    0,
    reinterpret_cast<PrototypeCreateF>(&Node::createEmptyLocal),
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&Node::classDescInserter)),
    false,
    0);


OSG_FIELD_CONTAINER_DEF(Node)



/*-------------------------------------------------------------------------*/
/*                             Children                                    */

void Node::addChild(Node * const childP)
{
    if(childP != NULL)
    {
        // do the ref early, to prevent destroys on getParent(a)->addChild(a)

        editMField(ChildrenFieldMask, _mfChildren);

        _mfChildren.push_back(childP);
    }
}

void Node::addChild(NodeTransitPtr childP)
{
    if(childP != NULL)
    {
        editMField(ChildrenFieldMask, _mfChildren);

        NodeUnrecPtr tmpChild = childP;

        _mfChildren.push_back(tmpChild);
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
void Node::insertChild(UInt32 childIndex, Node * const childP)
{
    OSG_ASSERT((childIndex <= getNChildren()) && "Child index out of range");

    if(childP != NULL)
    {
 
        editMField(ChildrenFieldMask, _mfChildren);

        MFUnrecChildNodePtr::iterator childIt = _mfChildren.begin_nc();

        childIt += childIndex;

        _mfChildren.insert(childIt, childP);
    }
}

void Node::replaceChild(UInt32 childIndex, Node * const childP)
{
    const Node *pThis = this;

    if(childP     != NULL                           && 
       childIndex <  pThis->_mfChildren.size()      && 
       childP     != pThis->_mfChildren[childIndex]  )
    {
        editMField(ChildrenFieldMask, _mfChildren);

        _mfChildren.replace(childIndex, childP);
    }
}

//! return true on success, false on child not found

bool Node::replaceChildBy(Node * const childP,
                          Node * const newChildP)
{
    if(newChildP != NULL && childP != newChildP)
    {
        Int32 childIdx = findChild(childP);

        if(childIdx != -1)
        {
            // do the ref early, to prevent destroys on
            editMField(ChildrenFieldMask, _mfChildren);

            _mfChildren.replace(childIdx, newChildP);

            return true;
        }
    }

    return false;
}

Int32 Node::findChild(Node * const childP) const
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

void Node::subChild(Node * const childP)
{
    Int32 childIdx = findChild(childP);

    if(childIdx != -1)
    {
        editMField(ChildrenFieldMask, _mfChildren);

//        MFUnrecChildNodePtr::iterator childIt = _mfChildren.begin_nc();

//        childIt += childIdx;

        _mfChildren.erase(childIdx);
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

//        MFUnrecChildNodePtr::iterator childIt = _mfChildren.begin_nc();

//        childIt += childIndex;

        _mfChildren.erase(childIndex);
    }
}

void Node::clearChildren(void)
{
    editMField(ChildrenFieldMask, _mfChildren);
    
    _mfChildren.clear();
}

SizeT Node::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

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

Matrix Node::getToWorld(void)
{
    Matrix tmp;

    getToWorld(tmp);

    return tmp;
}

void Node::getToWorld(Matrix &result)
{
    if(getParent() != NULL)
    {
        getParent()->getToWorld(result);
    }
    else
    {
        result.setIdentity();
    }

    if(getCore() != NULL)
        getCore()->accumulateMatrix(result);
}

/*-------------------------------------------------------------------------*/
/*                           Volume                                        */

void Node::getWorldVolume(BoxVolume &result)
{
    Matrix m;

    if(getParent() != NULL)
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
    // still valid or static, nothing to do
    if(_sfVolume.getValue().isValid () == true   ||
       _sfVolume.getValue().isStatic() == true   ||
       getTravMask()                   == 0x0000   )
    {
        return;
    }

    // be careful to not change the real volume. If two threads
    // are updating the same aspect this will lead to chaos

    BoxVolume vol = _sfVolume.getValue();

    MFUnrecChildNodePtr::const_iterator cIt  = 
        this->getMFChildren()->begin();
    MFUnrecChildNodePtr::const_iterator cEnd = 
        this->getMFChildren()->end();

    vol.setEmpty();

    for(; cIt != cEnd; ++cIt)
    {
        if(*cIt != NULL && (*cIt)->getTravMask())
        {
            (*cIt)->updateVolume();
            vol.extendBy((*cIt)->getVolume());
        }
    }

    // test for null core. Shouldn't happen, but just in case...
    if(getCore() != NULL)
    {
        getCore()->adjustVolume(vol);
    }

    // don't propagate the static flag from children
    vol.setStatic(false);

    editSField(VolumeFieldMask);

    _sfVolume.setValue(vol);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Node::Node(void) :
     Inherited (                            ),
    _sfVolume  (                            ),
    _sfParent  (NULL                        ),
    _mfChildren(this, 
                ChildrenFieldId, 
                Node::ParentFieldId         ),
    _sfCore    (NULL, 
                this, 
                CoreFieldId,
                NodeCore::ParentsFieldId    ),
    _sfTravMask(TypeTraits<UInt32>::getMax())
#ifdef OSG_1_COMPAT
   ,_occlusionMask(0)
#endif
{
}

Node::Node(const Node &source) :
     Inherited    (source                   ),
    _sfVolume     (                         ),

    _sfParent     (NULL                     ),
    _mfChildren   (this, 
                   ChildrenFieldId, 
                   Node::ParentFieldId      ),

    _sfCore       (NULL, 
                   this, 
                   CoreFieldId, 
                   NodeCore::ParentsFieldId ),

    _sfTravMask   (source._sfTravMask       )
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

bool Node::linkParent  (FieldContainer * const pParent,
                        UInt16           const childFieldId,
                        UInt16           const parentFieldId)
{
    if(parentFieldId == ParentFieldId)
    {    
        Node *pTypedParent = dynamic_cast<Node *>(pParent);
                
        if(pTypedParent != NULL)
        {
            Node *pOldParent      = _sfParent.getValue         ();
            
            if(pOldParent != NULL)
            {
                pOldParent->unlinkChild(this, ChildrenFieldId);
            }
            
            editSField(ParentFieldMask);

            _sfParent.setValue(pTypedParent, childFieldId);
            
            return true;
        }
        
        return false;
    }
    
    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool Node::unlinkParent(FieldContainer * const pParent,
                        UInt16           const parentFieldId)
{
    if(parentFieldId == ParentFieldId)
    {    
        Node *pTypedParent = dynamic_cast<Node *>(pParent);
                
        if(pTypedParent != NULL)
        {
            if(_sfParent.getValue() == pTypedParent)
            {
                editSField(ParentFieldMask);

                _sfParent.setValue(NULL, 0xFFFF);
            
                return true;
            }

            SWARNING << "Child (["          << this
                     << "] id ["            << this->getId()
                     << "] type ["          << this->getType().getCName()
                     << "] parentFieldId [" << parentFieldId
                     << "]) - Parent (["    << pParent
                     << "] id ["            << pParent->getId()
                     << "] type ["          << pParent->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;
        }

        return false;
    }
        
    return Inherited::unlinkParent(pParent, parentFieldId);
}
            
bool Node::unlinkChild (FieldContainer * const pChild,
                        UInt16           const childFieldId )
{
    if(childFieldId == ChildrenFieldId)
    {
        Node *pTypedChild = dynamic_cast<Node *>(pChild);
        
        if(pTypedChild != NULL)
        {
            Int32 iChildIdx = _mfChildren.findIndex(pTypedChild);

            if(iChildIdx != -1)
            {
                editMField(ParentFieldMask, _mfChildren);

                _mfChildren.erase(iChildIdx);
                
                return true;
            }

            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;
            
            return false;
        }
        
        return false;
    }
    
    if(childFieldId == CoreFieldId)
    {
        NodeCore *pTypedChild = dynamic_cast<NodeCore *>(pChild);
        
        if(pTypedChild != NULL)
        {
            if(_sfCore.getValue() == pTypedChild)
            {
                editSField(CoreFieldMask);

                _sfCore.setValue(NULL);
            
                return true;
            }
            
            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;
        
            return false;
        }
        
        return false;
    }
    
    return Inherited::unlinkChild(pChild, childFieldId);
}

void Node::invalidateVolume(void)
{
    BoxVolume &vol = _sfVolume.getValue();

    if(vol.isInvalidated() == false && vol.isStatic() == false)
    {
        editSField(VolumeFieldMask);

        vol.invalidate();

        if(getParent() != NULL)
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
        if(getParent() != NULL)
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
         << this->getId()
         << ") : "
         << _mfChildren.size()
         << " children | "
//         << _attachmentMap.getValue().size()
         << " attachments | "
         << "Parent : ";

    if(_sfParent.getValue() != NULL)
    {
        PLOG << _sfParent.getValue()->getId() << " | ";
    }
    else
    {
        PLOG << "NULL | ";
    }

    PLOG << std::hex << this << std::dec << std::endl;

    indentLog(uiIndent, PLOG);

    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);

    PLOG << "Box : " << _sfVolume.getValue() << std::endl;

    if(_sfCore.getValue() != NULL)
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

SFBoxVolume *Node::editSFVolume(void)
{
    editSField(VolumeFieldMask);

    return &_sfVolume;
}

const SFBoxVolume *Node::getSFVolume(void) const
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

const SFParentNodePtr *Node::getSFParent(void) const
{
    return &_sfParent;
}

const SFUnrecChildNodeCorePtr *Node::getSFCore(void) const
{
    return &_sfCore;
}

const MFUnrecChildNodePtr *Node::getMFChildren(void) const
{
    return &_mfChildren;
}

#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *Node::createAspectCopy(const FieldContainer *pRefAspect) const
{
    Node *returnValue = NULL;

    newAspectCopy(returnValue,
                  dynamic_cast<const Node *>(pRefAspect),
                  dynamic_cast<const Node *>(this));

    return returnValue;
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
void Node::execSyncV(       FieldContainer    &oFrom,
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
    SFBoxVolume::EditHandlePtr returnValue(
        new  SFBoxVolume::EditHandle(
             &_sfVolume, 
             this->getType().getFieldDesc(VolumeFieldId),
             this));

    editSField(VolumeFieldMask);

    return returnValue;
}

GetFieldHandlePtr  Node::getHandleVolume(void) const
{
    SFBoxVolume::GetHandlePtr returnValue(
        new  SFBoxVolume::GetHandle(
             &_sfVolume, 
             this->getType().getFieldDesc(VolumeFieldId),
             const_cast<Node *>(this)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleTravMask(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfTravMask, 
             this->getType().getFieldDesc(TravMaskFieldId),
             this));

    editSField(TravMaskFieldMask);

    return returnValue;
}

GetFieldHandlePtr Node::getHandleTravMask(void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfTravMask, 
             this->getType().getFieldDesc(TravMaskFieldId),
             const_cast<Node *>(this)));

    return returnValue;
}

GetFieldHandlePtr Node::getHandleParent(void) const
{
    SFParentNodePtr::GetHandlePtr returnValue(
        new SFParentNodePtr::GetHandle(
             &_sfParent, 
             this->getType().getFieldDesc(ParentFieldId),
             const_cast<Node *>(this)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleCore(void)
{
    SFUnrecChildNodeCorePtr::EditHandlePtr returnValue(
        new SFUnrecChildNodeCorePtr::EditHandle(
             &_sfCore, 
             this->getType().getFieldDesc(CoreFieldId),
             this));

    typedef void (Node::*SetCoreF)(NodeCore * const);
    
    SetCoreF fFunc = &Node::setCore;

    returnValue->setSetMethod(boost::bind(fFunc, this, _1));

    editSField(CoreFieldMask);

    return returnValue;
}

GetFieldHandlePtr Node::getHandleCore(void) const
{
    SFUnrecChildNodeCorePtr::GetHandlePtr returnValue(
        new SFUnrecChildNodeCorePtr::GetHandle(
             &_sfCore, 
             this->getType().getFieldDesc(CoreFieldId),
             const_cast<Node *>(this)));

    return returnValue;
}

EditFieldHandlePtr Node::editHandleChildren(void)
{
    MFUnrecChildNodePtr::EditHandlePtr returnValue(
        new  MFUnrecChildNodePtr::EditHandle(
             &_mfChildren, 
             this->getType().getFieldDesc(ChildrenFieldId),
             this));

    typedef void (Node::*AddChildF)(Node * const);

    AddChildF fFunc = &Node::addChild;

    returnValue->setAddMethod(boost::bind(fFunc, this, _1));

    editMField(ChildrenFieldMask, _mfChildren);

    return returnValue;
}

GetFieldHandlePtr  Node::getHandleChildren(void) const
{
    MFUnrecChildNodePtr::GetHandlePtr returnValue(
        new  MFUnrecChildNodePtr::GetHandle(
             &_mfChildren, 
             this->getType().getFieldDesc(ChildrenFieldId),
             const_cast<Node *>(this)));

    return returnValue;
}

void Node::resolveLinks(void)
{
    Inherited::resolveLinks();

    editSField(CoreFieldMask);
    _sfCore.setValue(NULL);

    editMField(ChildrenFieldMask, _mfChildren);
    _mfChildren.clear();
}

/*---------------------------------------------------------------------*/
/*! \name Node cloning                                                 */
/*! \{                                                                 */

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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr cloneTree(const OSG::Node                *rootNode,
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr cloneTree(const OSG::Node                *rootNode,
                         const std::vector<OSG::UInt16> &cloneGroupIds,
                         const std::vector<OSG::UInt16> &ignoreGroupIds)
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr cloneTree(const OSG::Node       *rootNode,
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr cloneTree(      
    const OSG::Node                                        *rootNode,
    const std::vector<const OSG::ReflexiveContainerType *> &cloneTypes,
    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes,
    const std::vector<OSG::UInt16>                         &cloneGroupIds,
    const std::vector<OSG::UInt16>                         &ignoreGroupIds)
{
    NodeUnrecPtr rootClone(NULL);

    if(rootNode != NULL)
    {
        NodeUnrecPtr  childClone;
        NodeCore     *core       = rootNode->getCore();

        rootClone = Node::create();
        rootClone->setTravMask(rootNode->getTravMask());

        cloneAttachments(rootNode,      rootClone,
                         cloneTypes,    ignoreTypes,
                         cloneGroupIds, ignoreGroupIds);

        if(core != NULL)
        {
                  NodeCoreUnrecPtr    coreClone  = NULL;
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr deepCloneTree(const OSG::Node                *rootNode,
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr deepCloneTree(const OSG::Node                *rootNode,
                             const std::vector<OSG::UInt16> &shareGroupIds,
                             const std::vector<OSG::UInt16> &ignoreGroupIds)
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr deepCloneTree(const Node            *rootNode,
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

    \ingroup GrpBaseFieldContainerNodes
    \relatesalso Node
 */

NodeTransitPtr deepCloneTree(      
    const OSG::Node                                        *rootNode,
    const std::vector<const OSG::ReflexiveContainerType *> &shareTypes,
    const std::vector<const OSG::ReflexiveContainerType *> &ignoreTypes,
    const std::vector<OSG::UInt16>                         &shareGroupIds,
    const std::vector<OSG::UInt16>                         &ignoreGroupIds)
{
    NodeUnrecPtr rootClone(NULL);

    if(rootNode != NULL)
    {
        NodeUnrecPtr  childClone;
        NodeCore     *core       = rootNode->getCore();

        rootClone = Node::create();
        rootClone->setTravMask(rootNode->getTravMask());

        deepCloneAttachments(rootNode,      rootClone,
                             shareTypes,    ignoreTypes,
                             shareGroupIds, ignoreGroupIds);

        if(core != NULL)
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

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
