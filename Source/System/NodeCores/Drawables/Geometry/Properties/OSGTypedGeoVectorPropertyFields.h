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

    static char     *getSName(void) { return "SFGeoPnt3fPropertyPtr"; }
    static char     *getMName(void) { return "MFGeoPnt3fPropertyPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GeoVectorPropertyPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldSingle */

typedef SFieldAdaptor<GeoPnt3fPropertyPtr, 
                      SFFieldContainerPtr> SFGeoPnt3fPropertyPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef MFieldAdaptor<GeoPnt3fPropertyPtr,
                      MFFieldContainerPtr> MFGeoPnt3fPropertyPtr;
#endif




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

    static char     *getSName(void) { return "SFGeoVec3fPropertyPtr"; }
    static char     *getMName(void) { return "MFGeoVec3fPropertyPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GeoVectorPropertyPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldSingle */

typedef SFieldAdaptor<GeoVec3fPropertyPtr, 
                      SFFieldContainerPtr> SFGeoVec3fPropertyPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef MFieldAdaptor<GeoVec3fPropertyPtr,
                      MFFieldContainerPtr> MFGeoVec3fPropertyPtr;
#endif






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

    static char     *getSName(void) { return "SFGeoColor4fPropertyPtr"; }
    static char     *getMName(void) { return "MFGeoColor4fPropertyPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GeoVectorPropertyPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldSingle */

typedef SFieldAdaptor<GeoColor4fPropertyPtr, 
                      SFFieldContainerPtr  > SFGeoColor4fPropertyPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef MFieldAdaptor<GeoColor4fPropertyPtr,
                      MFFieldContainerPtr  > MFGeoColor4fPropertyPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGTYPEDGEOVECTORPROPERTYFIELDS_H_ */
