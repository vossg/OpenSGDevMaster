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


#ifndef _OSGCOLORBUFFERVIEWPORTFIELDS_H_
#define _OSGCOLORBUFFERVIEWPORTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class ColorBufferViewport;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! ColorBufferViewportPtr

OSG_GEN_CONTAINERPTR(ColorBufferViewport);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ColorBufferViewportPtr> :
    public FieldTraitsFCPtrBase<ColorBufferViewportPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ColorBufferViewportPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOW_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFColorBufferViewportPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFColorBufferViewportPtr"; }
};

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakColorBufferViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<ColorBufferViewportPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdColorBufferViewportPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ColorBufferViewportPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldSingle */

typedef FieldContainerPtrSField<ColorBufferViewportPtr,
                                RecordedRefCountPolicy  > SFRecColorBufferViewportPtr;
typedef FieldContainerPtrSField<ColorBufferViewportPtr,
                                UnrecordedRefCountPolicy> SFUnrecColorBufferViewportPtr;
typedef FieldContainerPtrSField<ColorBufferViewportPtr,
                                WeakRefCountPolicy      > SFWeakColorBufferViewportPtr;
typedef FieldContainerPtrSField<ColorBufferViewportPtr,
                                NoRefCountPolicy        > SFUncountedColorBufferViewportPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldMulti */

typedef FieldContainerPtrMField<ColorBufferViewportPtr,
                                RecordedRefCountPolicy  > MFRecColorBufferViewportPtr;
typedef FieldContainerPtrMField<ColorBufferViewportPtr,
                                UnrecordedRefCountPolicy> MFUnrecColorBufferViewportPtr;
typedef FieldContainerPtrMField<ColorBufferViewportPtr,
                                WeakRefCountPolicy      > MFWeakColorBufferViewportPtr;
typedef FieldContainerPtrMField<ColorBufferViewportPtr,
                                NoRefCountPolicy        > MFUncountedColorBufferViewportPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGCOLORBUFFERVIEWPORTFIELDS_H_ */
