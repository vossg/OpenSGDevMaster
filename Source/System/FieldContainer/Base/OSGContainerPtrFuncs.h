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

#ifndef _OSGCONTAINERPTRFUNCS_H_
#define _OSGCONTAINERPTRFUNCS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGContainerBase.h"

#ifdef OSG_FIELDBUNDLE
#include "OSGFieldBundle.h"
#endif

#include "OSGFieldContainer.h"
#include "OSGParentContainer.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainerFuncs
 */

struct PointerFuncs
{
    template <class PtrT> 
    static void addRef        (const PtrT objectP);

    template <class PtrT> 
    static void subRef        (const PtrT objectP);

    template <class PtrT> 
    static void subRefLocalVar(const PtrT objectP);

    template <class PtrT> 
    static void shallowSubRef (const PtrT objectP);

    template <class PtrT> 
    static void beginEdit(const PtrT      objectP,
                                BitVector whichField,
                                UInt32    origin    );

    template <class PtrT> 
    static void endEdit  (const PtrT      objectP,
                                BitVector whichField,
                                UInt32    origin    );

    template<class PtrT>
    static void executeSync(      PtrT              &pTarget,
                                  UInt32             uiFromAspect,
                                  UInt32             uiToAspect,
                                  ConstFieldMaskArg  whichField,
                                  ConstFieldMaskArg  syncMode,
                            const UInt32             uiSyncInfo  );

    template <class PtrT> 
    static UInt32 getContainerId(PtrT objectP);

    template <class PtrT> 
    static Int32  getRefCount   (PtrT objectP);

    template <class Ptr>
    static Ptr    getCPtr       (Ptr pObject );
};

struct CPointerFuncs
{
    template <class PtrT> 
    static void addRef (const PtrT objectP);

    template <class PtrT> 
    static void subRef (const PtrT objectP);

    template <class PtrT> 
    static void shallowSubRef (const PtrT objectP);

    template <class PtrT> 
    static void beginEdit(const PtrT      objectP,
                                BitVector whichField,
                                UInt32    origin    );

    template <class PtrT> 
    static void endEdit  (const PtrT      objectP,
                                BitVector whichField,
                                UInt32    origin    );

    template<class PtrT>
    static void executeSync(      PtrT              &pTarget,
                                  UInt32             uiFromAspect,
                                  UInt32             uiToAspect,
                                  ConstFieldMaskArg  whichField,
                                  ConstFieldMaskArg  syncMode,
                            const UInt32             uiSyncInfo  );

    template <class PtrT> 
    static UInt32 getContainerId(PtrT objectP);

    template <class PtrT> 
    static Int32  getRefCount   (PtrT objectP);

    template <class Ptr>
    static typename Ptr::StoredObject *getCPtr(Ptr pObject);
};

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef OSG_FIELDBUNDLE
inline
void addRef(FieldBundlePConst objectP);
#endif

inline
void addRef(FieldContainerPtrConst objectP);

#ifndef OSG_MT_FIELDCONTAINERPTR
inline 
void addRef(ParentFieldContainerPtrConst objectP);
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef OSG_FIELDBUNDLE
inline
void subRef(FieldBundlePConst objectP);
#endif

inline
void subRef(FieldContainerPtrConst objectP);

inline
void subRefLocalVar(FieldContainerPtrConst objectP);

#ifndef OSG_MT_FIELDCONTAINERPTR
inline 
void subRef(ParentFieldContainerPtrConst objectP);
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

#ifdef OSG_FIELDBUNDLE
inline
void shallowSubRef(FieldBundlePConst      objectP);
#endif

inline
void shallowSubRef(FieldContainerPtrConst objectP);


/*! \ingroup GrpSystemFieldContainerFuncs
 */

template <class StoreT, class SourceT> inline
void setRefd(StoreT  &pTarget,
             SourceT  pSource);

#ifndef OSG_DISABLE_DEPRECATED
template <class PtrT> inline
void beginEdit(const PtrT      objectP,
                     BitVector whichField = FieldBits    ::AllFields,
                     UInt32    origin     = ChangedOrigin::External);

template <class PtrT> inline
void endEdit  (const PtrT      objectP,
                     BitVector whichField = FieldBits    ::AllFields,
                     UInt32    origin     = ChangedOrigin::External);
#endif

inline
void executeSync(      FieldContainerPtrConst pTarget,
                       UInt32                 uiFromAspect,
                       UInt32                 uiToAspect,
                       ConstFieldMaskArg      whichField,
                       ConstFieldMaskArg      syncMode,
                 const UInt32                 uiSyncInfo  );

#ifdef OSG_FIELDBUNDLE
inline
UInt32 getContainerId(FieldBundleConstPConst      objectP);

inline
Int32  getRefCount   (FieldBundleConstPConst      objectP);
#endif

inline
UInt32 getContainerId(FieldContainerConstPtrConst objectP);

inline
Int32  getRefCount   (FieldContainerConstPtrConst objectP);

#ifdef OSG_FIELDBUNDLE
inline 
FieldBundleConstP getCPtr(FieldBundleConstPConst objectP);

inline 
FieldBundleP      getCPtr(FieldBundlePConst      objectP);
#endif


template <class Ptr> inline 
typename PtrStripper<Ptr>::Object      *getCPtr     (Ptr objectP);

template <class Ptr> inline 
typename PtrStripper<Ptr>::ConstObject *getConstCPtr(Ptr objectP);

//template <class Ptr> inline 
//typename PtrStripper<Ptr>::Object      *get_pointer (Ptr objectP);

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class B, class C> inline 
typename PtrStripper< FCPtr<B, C> >::Object *get_pointer( FCPtr<B,C> object);

template <typename FcPtrType>
inline typename RefPtr<FcPtrType>::Ref::StoredObject* get_pointer(RefPtr<FcPtrType> p);
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

template<class PointerT> inline
PointerT cast_dynamic(FieldContainer::ObjPtrConst in);

template<class PointerT> inline
PointerT cast_static (FieldContainer::ObjPtrConst in);

template<> inline
ParentFieldContainerPtr cast_dynamic(FieldContainer::ObjPtrConst pIn);

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

#ifdef OSG_1_COMPAT
inline
void addRefCP(FieldContainerPtrConst objectP)
{
    addRef(objectP);
}

inline
void subRefCP(FieldContainerPtrConst objectP)
{
    subRef(objectP);
}

template <class PtrT> inline
void beginEditCP(const PtrT      objectP,
                       BitVector whichField = FieldBits    ::AllFields,
                       UInt32    origin     = ChangedOrigin::External)
{
    beginEdit(objectP, whichField, origin);
}

template <class PtrT> inline
void endEditCP(const PtrT      objectP,
                     BitVector whichField = FieldBits    ::AllFields,
                     UInt32    origin     = ChangedOrigin::External)
{
    endEdit(objectP, whichField, origin);
}

template <class StoreT, class SourceT> inline
void setRefdCP(StoreT  &pTarget,
               SourceT  pSource)
{
    setRefd(pTarget, pSource);
}
#endif

OSG_END_NAMESPACE

#include "OSGContainerPtrFuncs.inl"
//#include "OSGContainerPtrFuncsObjDep.inl"

#endif /* _OSGCONTAINERPTRFUNCS_H_ */
