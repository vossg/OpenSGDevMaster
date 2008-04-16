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

#include "boost/shared_ptr.hpp"

#include <map>

//---------------------------------------------------------------------------
//  typedefs
//---------------------------------------------------------------------------

#define OLD_OSG_GEN_INTERNALPTR(CLASST)                     \
    typedef       CLASST *       ObjPtr;                    \
    typedef       CLASST * const ObjPtrConst;               \
    typedef const CLASST *       ObjConstPtr;               \
    typedef       CLASST * const ObjPtrConstArg

#if 0
    typedef const CLASST * const ObjConstPtrConst;          \
                                                            \
    typedef       CLASST *       ObjPtrArg;                 \
    typedef const CLASST *       ObjConstPtrArg
#endif

#define OLD_OSG_GEN_CONTAINERPTR(CLASST)                   \
    typedef       CLASST *       CLASST##Ptr;              \
    typedef       CLASST * const CLASST##PtrConst;         \
    typedef const CLASST *       CLASST##ConstPtrArg;      \
    typedef       CLASST * const CLASST##PtrConstArg;      \
    typedef const CLASST * const CLASST##ConstPtrConst;    \
    typedef       CLASST *       CLASST##PtrArg;           \
    typedef const CLASST *       CLASST##ConstPtr;

#define NEW_REFPTR


#define TMP_INTERNAL_PTR(CLASST)                                               \
    typedef       TransitPtr< CLASST                          > ObjTransitPtr; \
    typedef       RefCountPtr<CLASST, RecordedRefCountPolicy  > ObjRecPtr;     \
    typedef       RefCountPtr<CLASST, UnrecordedRefCountPolicy> ObjUnrecPtr;   \
    typedef       RefCountPtr<CLASST, WeakRefCountPolicy      > ObjWeakPtr;  

#define TMP_PTR(CLASST)                                                        \
    typedef       TransitPtr < CLASST                  > CLASST##TransitPtr;   \
    typedef       RefCountPtr< CLASST,                                         \
                               RecordedRefCountPolicy  > CLASST##RecPtr;       \
    typedef       RefCountPtr< CLASST,                                         \
                               UnrecordedRefCountPolicy> CLASST##UnrecPtr;     \
    typedef       RefCountPtr< CLASST,                                         \
                               WeakRefCountPolicy      > CLASST##WeakPtr;      \
    typedef       RefCountPtr< CLASST,                                         \
                               MTRecordedRefCountPolicy> CLASST##MTRecPtr;     \
    typedef       CLASST##RecPtr                         CLASST##RefPtr;


#define OSG_GEN_INTERNALPTR(CLASST)                         \
    typedef       CLASST *       ObjCPtr;                   \
    typedef       CLASST * const ObjCPtrConst;              \
    typedef const CLASST *       ObjConstCPtr;              \
    typedef const CLASST * const ObjConstCPtrConst;         \
                                                            \
    typedef       CLASST *       ObjCPtrArg;                \
    typedef       CLASST * const ObjCPtrConstArg;           \
    typedef const CLASST *       ObjConstCPtrArg;           \
                                                            \
    TMP_INTERNAL_PTR(CLASST)                                \
                                                            \
    OLD_OSG_GEN_INTERNALPTR(CLASST)



#define OSG_GEN_CONTAINERPTR(CLASST)                       \
    typedef       CLASST *       CLASST##CPtr;             \
    typedef       CLASST * const CLASST##CPtrConst;        \
    typedef const CLASST *       CLASST##ConstCPtr;        \
    typedef const CLASST * const CLASST##ConstCPtrConst;   \
                                                           \
    typedef       CLASST *       CLASST##CPtrArg;          \
    typedef       CLASST * const CLASST##CPtrConstArg;     \
    typedef const CLASST *       CLASST##ConstCPtrArg;     \
                                                           \
    TMP_PTR(CLASST)                                        \
                                                           \
    OLD_OSG_GEN_CONTAINERPTR(CLASST)


#define OSG_GEN_NAMED_PTR(CLASST, NAME)                     \
    typedef CLASST       *       NAME##Ptr;                 \
    typedef CLASST       * const NAME##PtrConst;            \
    typedef CLASST const *       NAME##ConstPtr;            \
    typedef CLASST const * const NAME##ConstPtrConst;       \
                                                            \
    typedef CLASST       *       NAME##PtrArg;              \
    typedef CLASST       * const NAME##PtrConstArg;         \
    typedef CLASST const *       NAME##ConstPtrArg




#define NullFC      NULL
#define OSGNullFC   NULL


OSG_BEGIN_NAMESPACE

class TypeBase;

class ReflexiveContainerType;
class FieldContainerType;

class FieldDescriptionBase;


class ReflexiveContainer;
class FieldContainer;

class AttachmentContainer;
class Node;
class NodeCore;

class FieldContainerAttachment;

class DrawEnv;

struct ContainerChangeEntry;

struct NoRefCountPolicy;
struct RecordedRefCountPolicy;
struct MTRecordedRefCountPolicy;
struct UnrecordedRefCountPolicy;
struct WeakRefCountPolicy;

template<class ObjT> 
class TransitPtr;

template<class ObjT, class RefCountPolicyT> 
class RefCountPtr;

OSG_GEN_CONTAINERPTR(FieldContainer);
OSG_GEN_CONTAINERPTR(FieldContainerAttachment);
OSG_GEN_CONTAINERPTR(AttachmentContainer);
OSG_GEN_CONTAINERPTR(Node);
OSG_GEN_CONTAINERPTR(NodeCore);

#if 0
template <class Core>
class CoredNodePtr;
#endif

template <class SingletonBaseT>
class SingletonHolder;

class FieldContainerFactoryBase;

typedef SingletonHolder<FieldContainerFactoryBase> FieldContainerFactory;

typedef boost::function<
              void (FieldContainerCPtrArg, ConstFieldMaskArg )> ChangedFunctor;

typedef boost::function<void (DrawEnv *)> RenderFunctor;

struct ChangedFunctorCallback
{
    ChangedFunctor _func;
    UInt32         _uiId;
    std::string    _createSymbol;

    typedef std::allocator<void> Alloc;
};

class GetFieldHandle;
class EditFieldHandle;

typedef boost::shared_ptr<GetFieldHandle > GetFieldHandlePtr;
typedef boost::shared_ptr<EditFieldHandle> EditFieldHandlePtr;

typedef EditFieldHandlePtr(ReflexiveContainer::*FieldEditMethod)(void  );
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldGetMethod )(void) const;

typedef EditFieldHandlePtr(ReflexiveContainer::*FieldIndexEditMethod)(UInt32);
typedef GetFieldHandlePtr (ReflexiveContainer::*FieldIndexGetMethod )(
    UInt32) const;

template<class TargetT, class SourceT>
TargetT *dynamic_pointer_cast(SourceT *pIn)
{
    return dynamic_cast<TargetT *>(pIn);
}

namespace FCLocal
{
    static const BitVector MT           = OSGLL(0x8000000000000000);
    static const BitVector Cluster      = OSGLL(0x7FFFFFFFFFFFFFFF);
    static const BitVector All          = (MT | Cluster);

    static const BitVector MTMask       = OSGLL(0x8000000000000000);
    static const BitVector NamspaceMask = ~MTMask;
}

template <class CoreT>
class CoredNodeMTRefPtr;

template <class CoreT>
class CoredNodeRefPtr;


OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFORWARDS_H_ */
