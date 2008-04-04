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
    static void addRefX        (const PtrT objectP);

    template <class PtrT> 
    static void subRefX        (const PtrT objectP);

    template <class PtrT> 
    static void subRefLocalVarX(const PtrT objectP);

    template <class PtrT> 
    static void shallowSubRefX (const PtrT objectP);

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


/*! \ingroup GrpSystemFieldContainerFuncs
 */

inline
void addRefX(FieldBundlePConst objectP);

inline
void addRefX(FieldContainerPtrConst objectP);

inline 
void addRefX(ParentFieldContainerPtrConst objectP);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

inline
void subRefX(FieldBundlePConst objectP);

inline
void subRefX(FieldContainerPtrConst objectP);

inline
void subRefLocalVarX(FieldContainerPtrConst objectP);

inline 
void subRefX(ParentFieldContainerPtrConst objectP);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

inline
void shallowSubRefX(FieldBundlePConst      objectP);

inline
void shallowSubRefX(FieldContainerPtrConst objectP);


/*! \ingroup GrpSystemFieldContainerFuncs
 */

template <class StoreT, class SourceT> inline
void setRefdX(StoreT  &pTarget,
              SourceT  pSource);


inline
UInt32 getContainerId(FieldBundleConstPConst      objectP);

inline
Int32  getRefCount   (FieldBundleConstPConst      objectP);

inline
UInt32 getContainerId(FieldContainerConstPtrConst objectP);

inline
Int32  getRefCount   (FieldContainerConstPtrConst objectP);

inline 
FieldBundleConstP getCPtr(FieldBundleConstPConst objectP);

inline 
FieldBundleP      getCPtr(FieldBundlePConst      objectP);


template <class Ptr> inline 
typename PtrStripper<Ptr>::Object      *getCPtr     (Ptr objectP);

template <class Ptr> inline 
typename PtrStripper<Ptr>::ConstObject *getConstCPtr(Ptr objectP);




#ifdef OSG_1_COMPAT
inline
void addRefCPX(FieldContainerPtrConst objectP)
{
    addRefX(objectP);
}

inline
void subRefCPX(FieldContainerPtrConst objectP)
{
    subRefX(objectP);
}

template <class PtrT> inline
void beginEditCP(const PtrT      objectP,
                       BitVector whichField = FieldBits    ::AllFields,
                       UInt32    origin     = ChangedOrigin::External)
{
}

template <class PtrT> inline
void endEditCP(const PtrT      objectP,
                     BitVector whichField = FieldBits    ::AllFields,
                     UInt32    origin     = ChangedOrigin::External)
{
}

template <class StoreT, class SourceT> inline
void setRefdCPX(StoreT  &pTarget,
                SourceT  pSource)
{
    setRefdX(pTarget, pSource);
}

template <class OutPtrT> inline
OutPtrT dynamic_fcptr_cast(FieldContainerPtrConst pPtr)
{
    return dynamic_cast<OutPtrT>(pPtr);
}
#endif

OSG_END_NAMESPACE

#include "OSGContainerPtrFuncs.inl"

#endif /* _OSGCONTAINERPTRFUNCS_H_ */
