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

#ifndef _OSGTYPEDGEOVECTORPROPERTYFIELDS_H_
#define _OSGTYPEDGEOVECTORPROPERTYFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoVectorPropertyFields.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoVectorPropertyPtr

OSG_GEN_CONTAINERPTR(GeoPnt3fProperty);

#endif

/*! \ingroup GrpDrawablesGeometryFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<GeoPnt3fProperty *> : 
    public FieldTraitsFCPtrBase<GeoPnt3fProperty *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoPnt3fProperty *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoPnt3fProperty *, GeoPnt3fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoPnt3fProperty *, 
                               GeoPnt3fPropertyPtr,
                               GrpDrawablesGeometry,
                               GrpLibOSGDrawables  );





#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoVectorPropertyPtr

OSG_GEN_CONTAINERPTR(GeoVec3fProperty);

#endif

/*! \ingroup GrpDrawablesGeometryFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<GeoVec3fProperty *> : 
    public FieldTraitsFCPtrBase<GeoVec3fProperty *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoVec3fProperty *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoVec3fProperty *, GeoVec3fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoVec3fProperty *, 
                               GeoVec3fPropertyPtr,
                               GrpDrawablesGeometry,
                               GrpLibOSGDrawables  );




#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoVectroPropertyPtr

OSG_GEN_CONTAINERPTR(GeoColor4fProperty);

#endif

/*! \ingroup GrpDrawablesGeometryFieldTraits
    \ingroup GrpLibOSGDrawables
 */

template <>
struct FieldTraits<GeoColor4fProperty *> : 
    public FieldTraitsFCPtrBase<GeoColor4fProperty *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoColor4fProperty *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoColor4fProperty *, GeoColor4fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoColor4fProperty *, 
                               GeoColor4fPropertyPtr,
                               GrpDrawablesGeometry,
                               GrpLibOSGDrawables   );

OSG_END_NAMESPACE

#endif /* _OSGTYPEDGEOVECTORPROPERTYFIELDS_H_ */
