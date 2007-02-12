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

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr, 
          GeoIntegralPropertyConstPtr, 
          GeoUInt8Property>::ObjPtr         GeoUInt8PropertyPtr;

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr,
          GeoIntegralPropertyConstPtr, 
          GeoUInt8Property>::ObjPtrConst    GeoUInt8PropertyPtrConst;

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr,
          GeoIntegralPropertyConstPtr, 
          GeoUInt8Property>::ObjPtrConstArg GeoUInt8PropertyPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoUInt8PropertyPtr> : 
    public FieldTraitsTemplateBase<GeoUInt8PropertyPtr>
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

typedef SFieldAdaptor<GeoUInt8PropertyPtr, 
                      SFFieldContainerPtr> SFGeoUInt8PropertyPtr;
#endif

#ifndef OSG_COMPILETYPEDGEOINTEGRALPROPERTYINST
OSG_FIELD_DLLEXPORT_DECL1(SField, 
                          GeoUInt8PropertyPtr, 
                          OSG_DRAWABLE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef MFieldAdaptor<GeoUInt8PropertyPtr,
                      MFFieldContainerPtr> MFGeoUInt8PropertyPtr;
#endif

#ifndef OSG_COMPILETYPEDGEOINTEGRALPROPERTYINST
OSG_FIELD_DLLEXPORT_DECL1(MField, 
                          GeoUInt8PropertyPtr, 
                          OSG_DRAWABLE_DLLTMPLMAPPING)
#endif



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GeoIntegralPropertyPtr

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr, 
          GeoIntegralPropertyConstPtr, 
          GeoUInt32Property>::ObjPtr         GeoUInt32PropertyPtr;

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr,
          GeoIntegralPropertyConstPtr, 
          GeoUInt32Property>::ObjPtrConst    GeoUInt32PropertyPtrConst;

typedef PointerFwdBuilder<
          GeoIntegralPropertyPtr,
          GeoIntegralPropertyConstPtr, 
          GeoUInt32Property>::ObjPtrConstArg GeoUInt32PropertyPtrConstArg;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpDrawableFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GeoUInt32PropertyPtr> : 
    public FieldTraitsTemplateBase<GeoUInt32PropertyPtr>
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

typedef SFieldAdaptor<GeoUInt32PropertyPtr, 
                      SFFieldContainerPtr> SFGeoUInt32PropertyPtr;
#endif

#ifndef OSG_COMPILETYPEDGEOINTEGRALPROPERTYINST
OSG_FIELD_DLLEXPORT_DECL1(SField, 
                          GeoUInt32PropertyPtr, 
                          OSG_DRAWABLE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpDrawableFieldMulti */

typedef MFieldAdaptor<GeoUInt32PropertyPtr,
                      MFFieldContainerPtr> MFGeoUInt32PropertyPtr;
#endif

#ifndef OSG_COMPILETYPEDGEOINTEGRALPROPERTYINST
OSG_FIELD_DLLEXPORT_DECL1(MField, 
                          GeoUInt32PropertyPtr, 
                          OSG_DRAWABLE_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGTYPEDGEOINTEGRALPROPERTYFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGTYPEDGEOINTEGRALPROPERTYFIELDS_H_ */
