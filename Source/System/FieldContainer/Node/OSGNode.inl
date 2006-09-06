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

OSG_BEGIN_NAMESPACE

OSG_FIELD_CONTAINER_INL_DEF(Node)

inline
NodeCorePtr Node::getCore(void)
{
    return _sfCore.getValue();
}

inline
NodeCorePtr Node::getCore(void) const
{
    return _sfCore.getValue();
}

inline
NodePtr Node::getParent(void)
{
    return _sfParent.getValue();
}

inline
UInt32 Node::getNChildren(void) const
{
    return _mfChildren.size();
}

inline
NodePtr Node::getChild(UInt32 childIndex)
{
    OSG_ASSERT((childIndex < _mfChildren.size()));

    return _mfChildren[childIndex];
}


inline
UInt32 Node::getTravMask(void) const
{
    return _sfTravMask.getValue();
}

inline
void  Node::setTravMask(UInt32 val)
{
    editSField(TravMaskFieldMask);

    _sfTravMask.setValue(val);
}

#ifdef OSG_1_COMPAT
inline
bool Node::getActive(void) const
{
    return getTravMask() == TypeTraits<UInt32>::getMax();
}

inline
void  Node::setActive(bool val)
{
    editSField(TravMaskFieldMask);

    _sfTravMask.setValue(val ? TypeTraits<UInt32>::getMax()        :
                               TypeTraits<UInt32>::getZeroElement() );
}
#endif

inline
DynamicVolume &Node::editVolume(bool update)
{
    if(update == true)
    {
        updateVolume();
    }
    else
    {
        editSField(VolumeFieldMask);
    }

    return _sfVolume.getValue();
}

inline
const DynamicVolume &Node::getVolume(void) const
{
    return _sfVolume.getValue();
}


#ifdef OSG_1_COMPAT
inline
DynamicVolume &Node::getVolume(bool update)
{
    return this->editVolume();
}
#endif

inline
void Node::setParent(NodePtrConst &parent)
{
    editSField(ParentFieldMask);

    _sfParent.setValue(parent);
}

inline
NodePtr Node::getPtr(void)
{
    return Inherited::constructPtr<Node>(this);
}

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void Node::execSync(      Node              *pFrom,
                          ConstFieldMaskArg  whichField,
                          ConstFieldMaskArg  syncMode  ,
                    const UInt32             uiSyncInfo,
                          UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.syncWith(pFrom->_sfVolume);
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.syncWith(pFrom->_sfTravMask);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.syncWith(pFrom->_sfParent);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.syncWith(pFrom->_mfChildren, 
                             syncMode, 
                             uiSyncInfo,
                             uiCopyOffset);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.syncWith(pFrom->_sfCore);
    }
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void Node::execSync(      Node              *pFrom,
                          ConstFieldMaskArg  whichField,
                          AspectOffsetStore &oOffsets,
                          ConstFieldMaskArg  syncMode  ,
                    const UInt32             uiSyncInfo)
{
}
#endif

#if 0
inline
void Node::execBeginEdit(ConstFieldMaskArg whichField, 
                         UInt32            uiAspect,
                         UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.beginEdit(uiAspect, uiContainerSize);
    }
}
#endif

inline
Char8 *Node::getClassname(void)
{
    return "Node";
}

template <class Core> inline
NodePtr makeCoredNode(typename Core::ObjPtr *pCore)
{
             NodePtr      n = Node::create();
    typename Core::ObjPtr c = Core::create();

    n->setCore(c);

    if(pCore != NULL)
        *pCore = c;

    return n;
}

template <class CorePtr> inline
NodePtr makeNodeFor(CorePtr c)
{
    NodePtr n = Node::create();

    n->setCore(c);

    return n;
}

OSG_END_NAMESPACE

#define OSGNODE_INLINE_CVSID "@(#)$Id: $"

