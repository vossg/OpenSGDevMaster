/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSIMPLESHADOWMAPENGINEFIELDS_H_
#define _OSGSIMPLESHADOWMAPENGINEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class SimpleShadowMapEngine;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! SimpleShadowMapEnginePtr

OSG_GEN_CONTAINERPTR(SimpleShadowMapEngine);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpGroupFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<SimpleShadowMapEnginePtr> :
    public FieldTraitsFCPtrBase<SimpleShadowMapEnginePtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<SimpleShadowMapEnginePtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_GROUP_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFSimpleShadowMapEnginePtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFSimpleShadowMapEnginePtr"; }
};

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakSimpleShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleShadowMapEnginePtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdSimpleShadowMapEnginePtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<SimpleShadowMapEnginePtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpGroupFieldSingle */

typedef FieldContainerPtrSField<SimpleShadowMapEnginePtr,
                                RecordedRefCountPolicy  > SFRecSimpleShadowMapEnginePtr;
typedef FieldContainerPtrSField<SimpleShadowMapEnginePtr,
                                UnrecordedRefCountPolicy> SFUnrecSimpleShadowMapEnginePtr;
typedef FieldContainerPtrSField<SimpleShadowMapEnginePtr,
                                WeakRefCountPolicy      > SFWeakSimpleShadowMapEnginePtr;
typedef FieldContainerPtrSField<SimpleShadowMapEnginePtr,
                                NoRefCountPolicy        > SFUncountedSimpleShadowMapEnginePtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpGroupFieldMulti */

typedef FieldContainerPtrMField<SimpleShadowMapEnginePtr,
                                RecordedRefCountPolicy  > MFRecSimpleShadowMapEnginePtr;
typedef FieldContainerPtrMField<SimpleShadowMapEnginePtr,
                                UnrecordedRefCountPolicy> MFUnrecSimpleShadowMapEnginePtr;
typedef FieldContainerPtrMField<SimpleShadowMapEnginePtr,
                                WeakRefCountPolicy      > MFWeakSimpleShadowMapEnginePtr;
typedef FieldContainerPtrMField<SimpleShadowMapEnginePtr,
                                NoRefCountPolicy        > MFUncountedSimpleShadowMapEnginePtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGSIMPLESHADOWMAPENGINEFIELDS_H_ */
