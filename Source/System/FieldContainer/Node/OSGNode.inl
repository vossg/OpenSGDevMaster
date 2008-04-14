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

template<class ObjectT> inline
void Node::setCore(TransitPtr<ObjectT> core)
{
    editSField(CoreFieldMask);

//    addRef(core);

//    if(_sfCore.getValue() != NullFC)
//    {
//        _sfCore.getValue()->subParent(this);

//        subRef(_sfCore.getValue());
//    }

    NodeCoreUnrecPtr pCore = core;

    _sfCore.setValue(pCore);

//    if(_sfCore.getValue() != NullFC)
//    {
//        _sfCore.getValue()->addParent(this, CoreFieldId);
//    }
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

inline
void Node::setOcclusionMask(UInt8 val)
{
    _occlusionMask = val;
}

inline
UInt8 Node::getOcclusionMask(void) const
{
    return _occlusionMask;
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


#ifdef OSG_1_GET_COMPAT
inline
DynamicVolume &Node::getVolume(bool update)
{
    return this->editVolume();
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
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

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
                             oOffsets);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.syncWith(pFrom->_sfCore);
    }
}
#endif

inline
Char8 *Node::getClassname(void)
{
    return "Node";
}

template <class Core> inline
NodeTransitPtr makeCoredNode(typename Core::ObjRecPtr *pCore)
{
             NodeTransitPtr    n = Node::create();
    typename Core::ObjUnrecPtr c = Core::create();

    n->setCore(c);

    if(pCore != NULL)
        *pCore = c;

    return n;
}

template <class CorePtr> inline
NodeTransitPtr makeNodeFor(CorePtr c)
{
    NodeTransitPtr n = Node::create();

    n->setCore(c);

    return n;
}

OSG_END_NAMESPACE
