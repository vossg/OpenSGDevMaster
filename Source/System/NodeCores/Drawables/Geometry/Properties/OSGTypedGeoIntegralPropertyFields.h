/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGTYPEDGEOINTEGRALPROPERTYFIELDS_H_
#define _OSGTYPEDGEOINTEGRALPROPERTYFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoIntegralPropertyFields.h"
#include "OSGTypedGeoIntegralProperty.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoIntegralPropertyPtr

OSG_GEN_CONTAINERPTR(GeoUInt8Property);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoUInt8PropertyPtr> : 
    public FieldTraitsFCPtrBase<GeoUInt8PropertyPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoUInt8PropertyPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    static char     *getSName(void) { return "SFGeoUInt8PropertyPtr"; }
    static char     *getMName(void) { return "MFGeoUInt8PropertyPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GeoIntegralPropertyPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldSingle */

typedef FieldContainerPtrSField<GeoUInt8PropertyPtr> SFGeoUInt8PropertyPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef FieldContainerPtrMField<GeoUInt8PropertyPtr> MFGeoUInt8PropertyPtr;
#endif




#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoIntegralPropertyPtr

OSG_GEN_CONTAINERPTR(GeoUInt32Property);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoUInt32PropertyPtr> : 
    public FieldTraitsFCPtrBase<GeoUInt32PropertyPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoUInt32PropertyPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    static char     *getSName(void) { return "SFGeoUInt32PropertyPtr"; }
    static char     *getMName(void) { return "MFGeoUInt32PropertyPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GeoIntegralPropertyPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldSingle */

typedef FieldContainerPtrSField<GeoUInt32PropertyPtr> SFGeoUInt32PropertyPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef FieldContainerPtrMField<GeoUInt32PropertyPtr> MFGeoUInt32PropertyPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGTYPEDGEOINTEGRALPROPERTYFIELDS_H_ */
