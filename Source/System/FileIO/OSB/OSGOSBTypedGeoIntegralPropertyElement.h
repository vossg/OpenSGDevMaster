/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#ifndef _OSGOSBTYPEDGEOINTEGRALPROPERTYELEMENT_H_
#define _OSGOSBTYPEDGEOINTEGRALPROPERTYELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"

#include "OSGOSBGeoIntegralPropertyElement.h"
#include "OSGOSBGeometryHelper.h"
#include "OSGOSBRootElement.h"

OSG_BEGIN_NAMESPACE

/*! A specialization of this template is registered for each
    specialization of TypedGeoIntegralProperty.

    \ingroup GrpFileIOOSB
    \nohierarchy
 */

template <class GeoPropertyTypeT>
class OSG_FILEIO_DLLMAPPING OSBTypedGeoIntegralPropertyElement
    : public OSBGeoIntegralPropertyElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef          GeoPropertyTypeT                 GeoPropertyType;
    typedef typename GeoPropertyType::ObjCPtr         GeoPropertyPtrType;
    typedef typename GeoPropertyType::ObjUnrecPtr     GeoPropertyUnrecPtrType;
    typedef typename GeoPropertyType::StoredFieldType GeoPropertyFieldType;
    typedef typename GeoPropertyFieldType::StoredType IntegralType;

    typedef OSBTypedGeoIntegralPropertyElement<GeoPropertyType> Self;
    typedef OSBGeoIntegralPropertyElement                       Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBTypedGeoIntegralPropertyElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBTypedGeoIntegralPropertyElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read    (const std::string &typeName);
    virtual void postRead(      void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Writing                                                      */
    /*! \{                                                                 */

    virtual void preWrite(FieldContainer * const fc);
    virtual void write   (void                     );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
    static const UInt8 FlagPacked     = 0x01;
    static const UInt8 FlagPackedMask = 0x01;
};

OSG_END_NAMESPACE

#include "OSGOSBTypedGeoIntegralPropertyElement.inl"

#endif /* _OSGOSBTYPEDGEOINTEGRALPROPERTYELEMENT_H_ */
