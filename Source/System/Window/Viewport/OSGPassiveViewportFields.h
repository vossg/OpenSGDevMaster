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


#ifndef _OSGPASSIVEVIEWPORTFIELDS_H_
#define _OSGPASSIVEVIEWPORTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class PassiveViewport;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! PassiveViewportPtr

OSG_GEN_CONTAINERPTR(PassiveViewport);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<PassiveViewportPtr> :
    public FieldTraitsFCPtrBase<PassiveViewportPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<PassiveViewportPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOW_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFPassiveViewportPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFPassiveViewportPtr"; }
};

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakPassiveViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<PassiveViewportPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdPassiveViewportPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<PassiveViewportPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldSingle */

typedef FieldContainerPtrSField<PassiveViewportPtr,
                                RecordedRefCountPolicy  > SFRecPassiveViewportPtr;
typedef FieldContainerPtrSField<PassiveViewportPtr,
                                UnrecordedRefCountPolicy> SFUnrecPassiveViewportPtr;
typedef FieldContainerPtrSField<PassiveViewportPtr,
                                WeakRefCountPolicy      > SFWeakPassiveViewportPtr;
typedef FieldContainerPtrSField<PassiveViewportPtr,
                                NoRefCountPolicy        > SFUncountedPassiveViewportPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldMulti */

typedef FieldContainerPtrMField<PassiveViewportPtr,
                                RecordedRefCountPolicy  > MFRecPassiveViewportPtr;
typedef FieldContainerPtrMField<PassiveViewportPtr,
                                UnrecordedRefCountPolicy> MFUnrecPassiveViewportPtr;
typedef FieldContainerPtrMField<PassiveViewportPtr,
                                WeakRefCountPolicy      > MFWeakPassiveViewportPtr;
typedef FieldContainerPtrMField<PassiveViewportPtr,
                                NoRefCountPolicy        > MFUncountedPassiveViewportPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGPASSIVEVIEWPORTFIELDS_H_ */
