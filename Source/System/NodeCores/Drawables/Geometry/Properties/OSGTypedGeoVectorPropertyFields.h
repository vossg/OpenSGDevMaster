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

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoPnt3fPropertyPtr> : 
    public FieldTraitsFCPtrBase<GeoPnt3fPropertyPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoPnt3fPropertyPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoPnt3fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoPnt3fPropertyPtr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)




#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoVectorPropertyPtr

OSG_GEN_CONTAINERPTR(GeoVec3fProperty);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoVec3fPropertyPtr> : 
    public FieldTraitsFCPtrBase<GeoVec3fPropertyPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoVec3fPropertyPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_TRAITS_NAME_INST(GeoVec3fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoVec3fPropertyPtr);




#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoVectroPropertyPtr

OSG_GEN_CONTAINERPTR(GeoColor4fProperty);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoColor4fPropertyPtr> : 
    public FieldTraitsFCPtrBase<GeoColor4fPropertyPtr>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<GeoColor4fPropertyPtr>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DRAWABLE_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void);
 
    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void);
};

OSG_FIELD_TRAITS_NAME_INST(GeoColor4fPropertyPtr)

OSG_FIELDCONTAINER_FIELDS_INST(GeoColor4fPropertyPtr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)




OSG_END_NAMESPACE

#endif /* _OSGTYPEDGEOVECTORPROPERTYFIELDS_H_ */
