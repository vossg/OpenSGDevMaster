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
#include "OSGBaseRefCountPoliciesFwd.h"
#include "OSGContainerRefCountPoliciesFwd.h"

#include "boost/shared_ptr.hpp"

#include <map>

//---------------------------------------------------------------------------
//  typedefs
//---------------------------------------------------------------------------

#define OSG_GEN_INTERNALPTR(CLASST)                                         \
    typedef TransitPtr   < CLASST                          > ObjTransitPtr; \
    typedef RefCountPtr  < CLASST, RecordedRefCountPolicy  > ObjRecPtr;     \
    typedef MTRefCountPtr< CLASST, RecordedRefCountPolicy  > ObjMTRecPtr;   \
    typedef RefCountPtr  < CLASST, UnrecordedRefCountPolicy> ObjUnrecPtr;   \
    typedef RefCountPtr  < CLASST, WeakRefCountPolicy      > ObjWeakPtr;    \
    typedef MTRefCountPtr< CLASST, WeakRefCountPolicy      > ObjMTWeakPtr;  \
                                                                            \
    typedef CLASST       *                                ObjCPtr;          \
    typedef CLASST const *                                ConstObjCPtr;


#if defined(OSG_1_COMPAT)
#define OSG_GEN_COMPAT_CONTAINERPTR(CLASST)                                    \
    typedef CLASST##RecPtr                         CLASST##Ptr;
#else
#define OSG_GEN_COMPAT_CONTAINERPTR(CLASST)
#endif

#define OSG_GEN_CONTAINERPTR(CLASST)                                          \
    typedef TransitPtr   < CLASST                  > CLASST##TransitPtr;      \
    typedef MTRefCountPtr< CLASST,                                            \
                           NoRefCountPolicy        > CLASST##MTUncountedPtr;  \
    typedef RefCountPtr  < CLASST,                                            \
                           RecordedRefCountPolicy  > CLASST##RecPtr;          \
    typedef RefCountPtr  < CLASST,                                            \
                           UnrecordedRefCountPolicy> CLASST##UnrecPtr;        \
    typedef RefCountPtr  < CLASST,                                            \
                           WeakRefCountPolicy      > CLASST##WeakPtr;         \
    typedef MTRefCountPtr< CLASST,                                            \
                           RecordedRefCountPolicy  > CLASST##MTRecPtr;        \
    typedef MTRefCountPtr< CLASST,                                            \
                           WeakRefCountPolicy      > CLASST##MTWeakPtr;       \
    typedef CLASST##RecPtr                           CLASST##RefPtr;          \
    typedef CLASST##MTRecPtr                         CLASST##MTRefPtr;        \
                                                                              \
    OSG_GEN_COMPAT_CONTAINERPTR(CLASST)


#define OSG_FWDDECL_FC(CLASST)                          \
    OSG_BEGIN_NAMESPACE                                 \
    class CLASST;                                       \
    OSG_GEN_CONTAINERPTR(CLASST);                       \
    OSG_END_NAMESPACE


OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS
class TypeBase;
class ReflexiveContainerType;
class FieldContainerType;

class FieldDescriptionBase;

class ReflexiveContainer;

class DrawEnv;

template <class AttachmentDescT>
class DynFieldAttachment;

template <class AttachmentDescT>
class DynFieldContainer;

struct ContainerChangeEntry;

template<class ObjT> 
class TransitPtr;

template<class ObjT, class RefCountPolicyT> 
class RefCountPtr;

template<class ObjT, class RefCountPolicyT>
class MTRefCountPtr;

OSG_END_NAMESPACE

OSG_FWDDECL_FC(FieldContainer)
OSG_FWDDECL_FC(Attachment)
OSG_FWDDECL_FC(AttachmentContainer)
OSG_FWDDECL_FC(Node)
OSG_FWDDECL_FC(NodeCore)

OSG_BEGIN_NAMESPACE

template <class SingletonBaseT>
class SingletonHolder;

class FieldContainerFactoryBase;

typedef SingletonHolder<FieldContainerFactoryBase> FieldContainerFactory;

typedef boost::function<
    void (FieldContainer *, ConstFieldMaskArg, UInt32)> ChangedFunctor;

typedef boost::function<void (DrawEnv *)> RenderFunctor;

struct ChangedFunctorCallback
{
    ChangedFunctor _func;
    std::string    _createSymbol;

    typedef std::allocator<void> Alloc;
};

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

#if defined(OSG_1_COMPAT)

#define OSGNullFC NULL

struct NullFCType 
{ 
};


static const NullFCType NullFC = NullFCType();

template<class ObjectT> inline
bool operator ==(ObjectT * const pObj, const NullFCType)
{
    return pObj == NULL;
}

template<class ObjectT> inline
bool operator !=(ObjectT * const pObj, const NullFCType)
{
    return pObj != NULL;
}

#define osg OSG
#endif

#endif //DOXYGEN_SHOULD_SKIP_THIS

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFORWARDS_H_ */
