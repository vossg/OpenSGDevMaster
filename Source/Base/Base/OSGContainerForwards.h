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

class ReflexiveContainerType;
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

class DrawEnv;

struct ContainerChangeEntry;


OSG_GEN_BUNDLEP(FieldBundle);

OSG_GEN_CONTAINERPTR(FieldContainer);
OSG_GEN_CONTAINERPTR(FieldContainerAttachment);
OSG_GEN_CONTAINERPTR(AttachmentContainer);
OSG_GEN_CONTAINERPTR(Node);
OSG_GEN_CONTAINERPTR(NodeCore);


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

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFORWARDS_H_ */
