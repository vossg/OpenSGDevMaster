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


#ifndef _OSGCARBONWINDOWFIELDS_H_
#define _OSGCARBONWINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowCarbonDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class CarbonWindow;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! CarbonWindowPtr

OSG_GEN_CONTAINERPTR(CarbonWindow);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowCarbonFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<CarbonWindowPtr> :
    public FieldTraitsFCPtrBase<CarbonWindowPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CarbonWindowPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOWCARBON_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFCarbonWindowPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFCarbonWindowPtr"; }
};

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCarbonWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CarbonWindowPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCarbonWindowPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<CarbonWindowPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowCarbonFieldSingle */

typedef FieldContainerPtrSField<CarbonWindowPtr,
                                RecordedRefCountPolicy  > SFRecCarbonWindowPtr;
typedef FieldContainerPtrSField<CarbonWindowPtr,
                                UnrecordedRefCountPolicy> SFUnrecCarbonWindowPtr;
typedef FieldContainerPtrSField<CarbonWindowPtr,
                                WeakRefCountPolicy      > SFWeakCarbonWindowPtr;
typedef FieldContainerPtrSField<CarbonWindowPtr,
                                NoRefCountPolicy        > SFUncountedCarbonWindowPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowCarbonFieldMulti */

typedef FieldContainerPtrMField<CarbonWindowPtr,
                                RecordedRefCountPolicy  > MFRecCarbonWindowPtr;
typedef FieldContainerPtrMField<CarbonWindowPtr,
                                UnrecordedRefCountPolicy> MFUnrecCarbonWindowPtr;
typedef FieldContainerPtrMField<CarbonWindowPtr,
                                WeakRefCountPolicy      > MFWeakCarbonWindowPtr;
typedef FieldContainerPtrMField<CarbonWindowPtr,
                                NoRefCountPolicy        > MFUncountedCarbonWindowPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGCARBONWINDOWFIELDS_H_ */
