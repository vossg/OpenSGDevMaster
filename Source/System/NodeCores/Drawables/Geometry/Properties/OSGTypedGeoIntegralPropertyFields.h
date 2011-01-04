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

/*! \ingroup GrpDrawablesGeometryFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<GeoUInt8Property *> : 
    public FieldTraitsFCPtrBase<GeoUInt8Property *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoUInt8Property *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(GeoUInt8Property *, GeoUInt8PropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoUInt8Property *, 
                               GeoUInt8PropertyPtr,
                               GrpDrawablesGeometry, 
                               GrpLibOSGDrawables  );







#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoIntegralPropertyPtr

OSG_GEN_CONTAINERPTR(GeoUInt32Property);

#endif

/*! \ingroup GrpDrawablesGeometryFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<GeoUInt32Property *> : 
    public FieldTraitsFCPtrBase<GeoUInt32Property *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoUInt32Property *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoUInt32Property *, GeoUInt32PropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoUInt32Property *, 
                               GeoUInt32PropertyPtr,
                               GrpDrawablesGeometry,
                               GrpLibOSGDrawables);



OSG_END_NAMESPACE

#endif /* _OSGTYPEDGEOINTEGRALPROPERTYFIELDS_H_ */
