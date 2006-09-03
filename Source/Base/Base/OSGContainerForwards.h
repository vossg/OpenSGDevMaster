/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef _OSGFIELDCONTAINERFORWARDS_H_
#define _OSGFIELDCONTAINERFORWARDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldForwards.h"

#include <map>

//---------------------------------------------------------------------------
//  typedefs
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

class TypeBase;

class FieldBundleType;
class FieldContainerType;

class FieldDescriptionBase;


class ReflexiveContainer;
class FieldBundle;
class FieldContainer;

class AttachmentContainer;
class Node;
class NodeCore;

class FieldBundleAttachment;
class FieldContainerAttachment;

struct ContainerChangeEntry;

typedef ReflexiveContainer    *ReflexiveContainerP;
typedef FieldBundleAttachment *FieldBundleAttachmentP;

typedef FieldBundle       *       FieldBundleP;
typedef FieldBundle       * const FieldBundlePConst;
typedef FieldBundle       * const FieldBundlePConstArg;
typedef FieldBundle const *       FieldBundleConstP;
typedef FieldBundle const * const FieldBundleConstPConst;

struct PointerFuncs;
struct CPointerFuncs;

template <class Object, class Ptr>
struct PtrWrapper
{
    typedef PtrWrapper<Object, Ptr> Self;
    typedef Ptr                     Pointer;
    typedef Object                  StoredObject;

    Ptr    _ptr;

    UInt16 _parentFPos;

    PtrWrapper(void) : 
        _ptr       (NULL),
        _parentFPos(0xFFFF)
      
    {
    }
    
    PtrWrapper(Ptr ptr) :
        _ptr(ptr),
        _parentFPos(0xFFFF)
    {
    } 

    ~PtrWrapper(void) 
    {
    }

    void setParentFieldPos(UInt16 parentFPos)
    {
        _parentFPos = parentFPos;
    }

    UInt16 getParentFieldPos(void)
    {
        return _parentFPos;
    }

    Ptr getCPtr(void)
    {
        return _ptr;
    }
    
    void addReference(void) const
    {
        _ptr->addReference();
    }

    void subReference(void) const
    {
        _ptr->subReference();
    }

    operator Ptr(void) const
    {
        return _ptr;
    }

    Object &operator *(void)
    {
        return *_ptr;
    }

    Object &operator *(void) const
    {
        return *_ptr;
    }

    Ptr operator->(void)
    {
        return _ptr;
    }

    Ptr operator->(void) const 
    {
        return _ptr;
    }

    bool operator ==(const Self &other) const
    {
        return _ptr == other._ptr;
    }

    bool operator ==(const Ptr other) const
    {
        return _ptr == other;
    }

/*
    bool operator ==(const int other) const
    {
        return _ptr == NULL;
    }

    bool operator !=(const int other) const
    {
        return _ptr != NULL;
    }
 */
};

#ifdef OSG_MT_FIELDCONTAINERPTR

class                      FieldContainerPtr;
class                      FieldContainerConstPtr;


//typedef ReflexiveContainer FieldContainerParent;

template <class ParentPtrTypeT, class FieldContainerTypeT> 
class FCPtr;

template <class ParentPtrTypeT, class FieldContainerTypeT> 
class FCConstPtr;

template<class ContainerT>
struct PointerBuilder
{
    typedef typename ContainerT::ParentContainer          Parent;
    typedef typename Parent    ::ObjPtr                   ParentPtr;
    typedef typename Parent    ::ObjConstPtr              ParentConstPtr;

    typedef FCPtr     <ParentPtr,      ContainerT>        ObjPtr;
    typedef FCConstPtr<ParentConstPtr, ContainerT>        ObjConstPtr;

    typedef FCPtr     <ParentPtr,      ContainerT> const  ObjPtrConst;
    typedef FCConstPtr<ParentPtr,      ContainerT> const  ObjConstPtrConst;

    typedef FCPtr     <ParentPtr,      ContainerT>       &ObjPtrArg;
    typedef FCPtr     <ParentPtr,      ContainerT> const &ObjPtrConstArg;
    typedef FCConstPtr<ParentConstPtr, ContainerT> const &ObjConstPtrArg;
};

template<class ParentPtr, class ParentConstPtr, class ContainerT>
struct PointerFwdBuilder
{
    typedef FCPtr     <ParentPtr,      ContainerT>        ObjPtr;
    typedef FCPtr     <ParentPtr,      ContainerT> const  ObjPtrConst;
    typedef FCPtr     <ParentPtr,      ContainerT> const &ObjPtrConstArg;

    typedef FCConstPtr<ParentConstPtr, ContainerT>        ObjConstPtr;

    typedef FCPtr     <ParentPtr,      ContainerT>       &ObjPtrArg;
    typedef FCConstPtr<ParentConstPtr, ContainerT> const &ObjConstPtrArg;
};

template<>
struct PointerBuilder<FieldContainer>
{
    typedef FieldContainerPtr             ObjPtr;
    typedef FieldContainerPtr      const  ObjPtrConst;
    typedef FieldContainerConstPtr        ObjConstPtr;
    typedef FieldContainerConstPtr const  ObjConstPtrConst;

    typedef FieldContainerPtr            &ObjPtrArg;
    typedef FieldContainerConstPtr       &ObjConstPtrArg;
    typedef FieldContainerPtr      const &ObjPtrConstArg;
};

typedef PointerBuilder<FieldContainer>::ObjPtrArg FieldContainerPtrArg;

template<>
struct PointerBuilder<FieldContainerAttachment>
{
    typedef FCPtr     <FieldContainerPtr, 
                       FieldContainerAttachment>        ObjPtr;
    typedef FCPtr     <FieldContainerPtr, 
                       FieldContainerAttachment> const  ObjPtrConst;
    typedef FCConstPtr<FieldContainerConstPtr, 
                       FieldContainerAttachment>        ObjConstPtr;
    typedef FCConstPtr<FieldContainerPtr, 
                       FieldContainerAttachment> const  ObjConstPtrConst;

    typedef FCPtr     <FieldContainerPtr, 
                       FieldContainerAttachment>       &ObjPtrArg;
    typedef FCConstPtr<FieldContainerConstPtr, 
                       FieldContainerAttachment>       &ObjConstPtrArg;
    typedef FCPtr     <FieldContainerPtr, 
                       FieldContainerAttachment> const &ObjPtrConstArg;
};

template<>
struct PointerBuilder<AttachmentContainer>
{
    typedef FCPtr     <FieldContainerPtr, 
                       AttachmentContainer>        ObjPtr;
    typedef FCPtr     <FieldContainerPtr, 
                       AttachmentContainer> const  ObjPtrConst;
    typedef FCConstPtr<FieldContainerPtr, 
                       AttachmentContainer>        ObjConstPtr;
    typedef FCConstPtr<FieldContainerPtr, 
                       AttachmentContainer> const  ObjConstPtrConst;

    typedef FCPtr     <FieldContainerPtr, 
                       AttachmentContainer>       &ObjPtrArg;
    typedef FCConstPtr<FieldContainerPtr, 
                       AttachmentContainer>       &ObjConstPtrArg;
    typedef FCPtr     <FieldContainerPtr, 
                       AttachmentContainer> const &ObjPtrConstArg;
};

typedef PointerBuilder<AttachmentContainer>::ObjPtr AttachmentContainerPtr;

template<>
struct PointerBuilder<Node>
{
    typedef FCPtr     <AttachmentContainerPtr, Node>        ObjPtr;
    typedef FCPtr     <AttachmentContainerPtr, Node> const  ObjPtrConst;
    typedef FCConstPtr<AttachmentContainerPtr, Node>        ObjConstPtr;
    typedef FCConstPtr<AttachmentContainerPtr, Node> const  ObjConstPtrConst;

    typedef FCPtr     <AttachmentContainerPtr, Node>       &ObjPtrArg;
    typedef FCConstPtr<AttachmentContainerPtr, Node>       &ObjConstPtrArg;
    typedef FCPtr     <AttachmentContainerPtr, Node> const &ObjPtrConstArg;
};

template<>
struct PointerBuilder<NodeCore>
{
    typedef FCPtr     <AttachmentContainerPtr, 
                       NodeCore              >        ObjPtr;
    typedef FCPtr     <AttachmentContainerPtr, 
                       NodeCore              > const  ObjPtrConst;
    typedef FCConstPtr<AttachmentContainerPtr,
                       NodeCore              >        ObjConstPtr;
    typedef FCConstPtr<AttachmentContainerPtr, 
                       NodeCore              > const  ObjConstPtrConst;

    typedef FCPtr     <AttachmentContainerPtr, 
                       NodeCore              >       &ObjPtrArg;
    typedef FCConstPtr<AttachmentContainerPtr,
                       NodeCore              >       &ObjConstPtrArg;
    typedef FCPtr     <AttachmentContainerPtr,
                       NodeCore              > const &ObjPtrConstArg;
};

#define OSGNullFC OSG::NullFC

#else


/*
template <class ObjectT> inline
void newPtr(ObjectT *&result)
{
    result = new ObjectT;
}

template <class ObjectT> inline
void newPtr(      ObjectT *&result,
            const ObjectT * pPrototype)
{
    result = new ObjectT(*pPrototype);
}
*/

template<class ContainerT>
struct PointerBuilder
{
    typedef ContainerT       *       ObjPtr;
    typedef ContainerT       * const ObjPtrConst;
    typedef ContainerT const *       ObjConstPtr;
    typedef ContainerT const * const ObjConstPtrConst;

    typedef ContainerT       *       ObjPtrArg;
    typedef ContainerT       * const ObjPtrConstArg;
    typedef ContainerT const *       ObjConstPtrArg;

    typedef ContainerT const * const ObjConstPtrConstArg;
};

template<class ParentPtr, class ParentConstPtr, class ContainerT>
struct PointerFwdBuilder
{
    typedef ContainerT       *       ObjPtr;
    typedef ContainerT       * const ObjPtrConst;
    typedef ContainerT const *       ObjConstPtr;

    typedef ContainerT       *       ObjPtrArg;

    typedef ContainerT       * const ObjPtrConstArg;
    typedef ContainerT const *       ObjConstPtrArg;
};

#endif

template<class ContainerT>
struct BundlePointerBuilder
{
    typedef       ContainerT *       ObjPtr;
    typedef       ContainerT * const ObjPtrConst;
    typedef const ContainerT *       ObjConstPtr;
};

typedef PointerBuilder<
          FieldContainer>::ObjPtr           FieldContainerPtr;
typedef PointerBuilder<
          FieldContainer>::ObjPtrArg        FieldContainerPtrArg;
typedef PointerBuilder<
          FieldContainer>::ObjPtrConst      FieldContainerPtrConst;
typedef PointerBuilder<
          FieldContainer>::ObjConstPtr      FieldContainerConstPtr;
typedef PointerBuilder<
          FieldContainer>::ObjConstPtrConst FieldContainerConstPtrConst;
typedef PointerBuilder<
          FieldContainer>::ObjPtrConstArg   FieldContainerPtrConstArg;

typedef PointerBuilder<
          FieldContainerAttachment>::ObjPtr FieldContainerAttachmentPtr;

typedef PointerBuilder<Node          >::ObjPtr           NodePtr;
typedef PointerBuilder<Node          >::ObjPtrConst      NodePtrConst;
typedef PointerBuilder<Node          >::ObjConstPtr      NodeConstPtr;
typedef PointerBuilder<Node          >::ObjConstPtrConst NodeConstPtrConst;

typedef PointerBuilder<Node          >::ObjPtrArg        NodePtrArg;
typedef PointerBuilder<Node          >::ObjPtrConstArg   NodePtrConstArg;

typedef PointerBuilder<NodeCore      >::ObjPtr           NodeCorePtr;
typedef PointerBuilder<NodeCore      >::ObjPtrConst      NodeCorePtrConst;
typedef PointerBuilder<NodeCore      >::ObjConstPtr      NodeCoreConstPtr;
typedef PointerBuilder<NodeCore      >::ObjConstPtrConst NodeCoreConstPtrConst;

typedef PointerBuilder<NodeCore      >::ObjPtrConstArg   NodeCorePtrConstArg;


typedef PointerBuilder<
    AttachmentContainer>::ObjPtr           AttachmentContainerPtr;

typedef PointerBuilder<
    AttachmentContainer>::ObjPtrConst      AttachmentContainerPtrConst;
typedef PointerBuilder<
    AttachmentContainer>::ObjConstPtr      AttachmentContainerConstPtr;
typedef PointerBuilder<
    AttachmentContainer>::ObjConstPtrConst AttachmentContainerConstPtrConst;

typedef PointerBuilder<
    AttachmentContainer>::ObjPtrConstArg   AttachmentContainerPtrConstArg;

#ifdef OSG_MT_FIELDCONTAINERPTR
typedef FieldContainerPtr         ParentFieldContainerPtr;
typedef FieldContainerPtrConstArg ParentFieldContainerPtrConstArg;
typedef FieldContainerPtrConst    ParentFieldContainerPtrConst;

typedef NodePtr                   ParentNodePtr;

typedef FieldContainerPtr NilFieldContainerReturnType;

#else

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr>        ParentFieldContainerPtr;

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr> const &ParentFieldContainerPtrConstArg;

typedef PtrWrapper<FieldContainer,
                   FieldContainerPtr> const  ParentFieldContainerPtrConst;

typedef PtrWrapper<Node,
                   NodePtr          > ParentNodePtr;

//static const void *NilPtr = NULL;

#define NullFC      NULL
#define OSGNullFC   NULL

typedef void *NilFieldContainerPtr ;

typedef FieldContainerPtr NilFieldContainerReturnType;

typedef FieldContainerAttachment *FieldContainerAttachmentPtr;

#endif

typedef PtrWrapper<FieldBundle,
                   FieldBundleP>        ParentFieldBundleP;

typedef PtrWrapper<FieldBundle,
                   FieldBundleP> const &ParentFieldBundlePConstArg;

typedef PtrWrapper<FieldBundle,
                   FieldBundleP> const  ParentFieldBundlePConst;



//static const ReflexiveContainerP NilP   = NULL;
#define NilP 0

typedef std::map<UInt32, 
                 FieldBundleAttachmentP     >  FieldBundleAttachmentMap;
typedef std::map<UInt32, 
                 FieldContainerAttachmentPtr>  FieldContainerAttachmentMap;

typedef SField  <FieldBundleAttachmentMap   ,
                 0                          > SFFieldBundleAttachmentPtrMap;
typedef SField  <FieldContainerAttachmentMap,
                 0                          > SFFieldContainerAttachmentPtrMap;

template <class DescT>
class ContainerMixinHead;

template<class ParentT>
class RefCountMixin;

template<class ParentT>
class ContainerIdMixin;

template <class DescT>
class FactoryMixinHead;

template <class ParentT>
class ContainerFactoryMixin;

template <class ParentT>
class PrototypeFactoryMixin;

template <class ParentT>
class ContainerStoreFactoryMixin;

template <class ParentT>
class HandledContainerStoreFactoryMixin;

template <class SingletonBaseT>
class SingletonHolder;

template <class Core>
class CoredNodePtr;

class FieldContainerFactoryBase;
class FieldBundleFactoryBase;

typedef SingletonHolder<FieldContainerFactoryBase> FieldContainerFactory;
typedef SingletonHolder<FieldBundleFactoryBase   > FieldBundleFactory;

#ifdef OSG_MT_CPTR_ASPECT
struct HandledFieldContainerFactoryDesc;

typedef HandledContainerStoreFactoryMixin<
          PrototypeFactoryMixin    <
              ContainerFactoryMixin <
                  FactoryMixinHead   <HandledFieldContainerFactoryDesc> > > > 
    FieldContainerFactoryParent;
#else
struct FieldContainerFactoryDesc;

typedef ContainerStoreFactoryMixin<
          PrototypeFactoryMixin    <
              ContainerFactoryMixin <
                  FactoryMixinHead   <FieldContainerFactoryDesc> > > > 
    FieldContainerFactoryParent;
#endif

struct FieldBundleFactoryDesc;

typedef ContainerStoreFactoryMixin<
          PrototypeFactoryMixin    <
              ContainerFactoryMixin <
                  FactoryMixinHead   <FieldBundleFactoryDesc> > > > 
    FieldBundleFactoryParent;

template <class ParentT>
class PtrCreateMixin;

struct FieldContainerDesc
{
    typedef ReflexiveContainer    ParentT;
    typedef FieldContainerType    TypeObject;
    typedef FieldContainerFactory ContainerFactoryT;
};

#ifdef OSG_MT_FIELDCONTAINERPTR

typedef PtrCreateMixin<
            ContainerMixinHead<FieldContainerDesc> > FieldContainerParent;

#else

typedef RefCountMixin<
         ContainerIdMixin<
          PtrCreateMixin<
            ContainerMixinHead<FieldContainerDesc> > > > FieldContainerParent;

#endif

struct FieldBundleDesc
{
    typedef ReflexiveContainer ParentT;
    typedef FieldBundleType    TypeObject;
    typedef FieldBundleFactory ContainerFactoryT;
};

typedef 
    RefCountMixin<
        ContainerIdMixin<
            ContainerMixinHead<FieldBundleDesc> > > FieldBundleParent;


typedef boost::function<
              void (FieldContainerPtrArg, ConstFieldMaskArg )> ChangedFunctor;

struct ChangedFunctorCallback
{
    ChangedFunctor _func;
    UInt32         _uiId;
    std::string    _createSymbol;

    typedef std::allocator<void> Alloc;
};

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFORWARDS_H_ */
