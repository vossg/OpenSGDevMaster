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


#ifndef _OSGTILECAMERADECORATORFIELDS_H_
#define _OSGTILECAMERADECORATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class TileCameraDecorator;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! TileCameraDecoratorPtr

OSG_GEN_CONTAINERPTR(TileCameraDecorator);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<TileCameraDecoratorPtr> :
    public FieldTraitsFCPtrBase<TileCameraDecoratorPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<TileCameraDecoratorPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOW_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFTileCameraDecoratorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFTileCameraDecoratorPtr"; }
};

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakTileCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<TileCameraDecoratorPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdTileCameraDecoratorPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<TileCameraDecoratorPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldSingle */

typedef FieldContainerPtrSField<TileCameraDecoratorPtr,
                                RecordedRefCountPolicy  > SFRecTileCameraDecoratorPtr;
typedef FieldContainerPtrSField<TileCameraDecoratorPtr,
                                UnrecordedRefCountPolicy> SFUnrecTileCameraDecoratorPtr;
typedef FieldContainerPtrSField<TileCameraDecoratorPtr,
                                WeakRefCountPolicy      > SFWeakTileCameraDecoratorPtr;
typedef FieldContainerPtrSField<TileCameraDecoratorPtr,
                                NoRefCountPolicy        > SFUncountedTileCameraDecoratorPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowFieldMulti */

typedef FieldContainerPtrMField<TileCameraDecoratorPtr,
                                RecordedRefCountPolicy  > MFRecTileCameraDecoratorPtr;
typedef FieldContainerPtrMField<TileCameraDecoratorPtr,
                                UnrecordedRefCountPolicy> MFUnrecTileCameraDecoratorPtr;
typedef FieldContainerPtrMField<TileCameraDecoratorPtr,
                                WeakRefCountPolicy      > MFWeakTileCameraDecoratorPtr;
typedef FieldContainerPtrMField<TileCameraDecoratorPtr,
                                NoRefCountPolicy        > MFUncountedTileCameraDecoratorPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGTILECAMERADECORATORFIELDS_H_ */
