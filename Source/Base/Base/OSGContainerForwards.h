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

#define OSG_GEN_INTERNALPTR(CLASST)                        \
    typedef       CLASST *       ObjPtr;                   \
    typedef       CLASST * const ObjPtrConst;              \
    typedef const CLASST *       ObjConstPtr;              \
    typedef const CLASST * const ObjConstPtrConst;         \
                                                           \
    typedef       CLASST *       ObjPtrArg;                \
    typedef       CLASST * const ObjPtrConstArg;           \
    typedef const CLASST *       ObjConstPtrArg

#define OSG_GEN_CONTAINERPTR(CLASST)                      \
    typedef       CLASST *       CLASST##Ptr;             \
    typedef       CLASST * const CLASST##PtrConst;        \
    typedef const CLASST *       CLASST##ConstPtr;        \
    typedef const CLASST * const CLASST##ConstPtrConst;   \
                                                          \
    typedef       CLASST *       CLASST##PtrArg;          \
    typedef       CLASST * const CLASST##PtrConstArg;     \
    typedef const CLASST *       CLASST##ConstPtrArg

#define OSG_GEN_BUNDLEP(CLASST)                           \
    typedef       CLASST *       CLASST##P;               \
    typedef       CLASST * const CLASST##PConst;          \
    typedef const CLASST *       CLASST##ConstP;          \
    typedef const CLASST * const CLASST##ConstPConst;     \
                                                          \
    typedef       CLASST *       CLASST##PArg;            \
    typedef       CLASST * const CLASST##PConstArg;       \
    typedef const CLASST *       CLASST##ConstPArg

#define NullFC      NULL
#define OSGNullFC   NULL
#define NilP        NULL


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


OSG_GEN_BUNDLEP(FieldBundle);

OSG_GEN_CONTAINERPTR(FieldContainer);
OSG_GEN_CONTAINERPTR(FieldContainerAttachment);
OSG_GEN_CONTAINERPTR(AttachmentContainer);
OSG_GEN_CONTAINERPTR(Node);
OSG_GEN_CONTAINERPTR(NodeCore);

#if 0
typedef FieldBundleAttachment *FieldBundleAttachmentP;

typedef FieldBundle       *       FieldBundleP;
typedef FieldBundle       * const FieldBundlePConst;
typedef FieldBundle       * const FieldBundlePConstArg;
typedef FieldBundle const *       FieldBundleConstP;
typedef FieldBundle const * const FieldBundleConstPConst;


typedef ReflexiveContainer       *       ReflexiveContainerPtr;
typedef ReflexiveContainer       * const ReflexiveContainerPtrConst;
typedef ReflexiveContainer       * const ReflexiveContainerPtrConstArg;
typedef ReflexiveContainer const *       ReflexiveContainerConstPtr;
typedef ReflexiveContainer const * const ReflexiveContainerConstPtrConst;

struct PointerFuncs;
struct CPointerFuncs;



#if 0

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


template<class ContainerT>
struct BundlePointerBuilder
{
    typedef       ContainerT *       ObjPtr;
    typedef       ContainerT * const ObjPtrConst;
    typedef const ContainerT *       ObjConstPtr;
    typedef const ContainerT * const ObjConstPtrConst;

    typedef       ContainerT *       ObjPtrArg;
    typedef       ContainerT * const ObjPtrConstArg;
    typedef const ContainerT *       ObjConstPtrArg;
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
#endif

#ifdef OSG_MT_FIELDCONTAINERPTR
typedef FieldContainerPtr         ParentFieldContainerPtr;
typedef FieldContainerPtrConstArg ParentFieldContainerPtrConstArg;
typedef FieldContainerPtrConst    ParentFieldContainerPtrConst;

typedef NodePtr                   ParentNodePtr;

typedef FieldContainerPtr NilFieldContainerReturnType;

#else

//static const void *NilPtr = NULL;


typedef void *NilFieldContainerPtr ;

typedef FieldContainerPtr NilFieldContainerReturnType;

typedef FieldContainerAttachment *FieldContainerAttachmentPtr;

#endif


//static const ReflexiveContainerP NilP   = NULL;

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


#endif

template <class Core>
class CoredNodePtr;

template <class SingletonBaseT>
class SingletonHolder;

class FieldContainerFactoryBase;
class FieldBundleFactoryBase;

typedef SingletonHolder<FieldContainerFactoryBase> FieldContainerFactory;
typedef SingletonHolder<FieldBundleFactoryBase   > FieldBundleFactory;

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
