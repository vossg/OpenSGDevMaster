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

#ifndef _OSGOSBGEOPROPERTYCONVERSIONELEMENT_H_
#define _OSGOSBGEOPROPERTYCONVERSIONELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGFileIODef.h"

#include "OSGOSBCommonElement.h"
#include "OSGOSBRootElement.h"

OSG_BEGIN_NAMESPACE

/*! A specialization of this template is registered for each OpenSG 1 property
    type in order to convert it to the appropriate OpenSG 2 property type.
    \ingroup GrpFileIOOSB
    \nohierarchy
 */

template <class GeoPropertyTypeT>
class OSG_FILEIO_DLLMAPPING OSBGeoPropertyConversionElement
    : public OSBCommonElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef          GeoPropertyTypeT                  GeoPropertyType;
    typedef typename GeoPropertyType::ObjUnrecPtr      GeoPropertyUnrecPtrType;
    typedef typename GeoPropertyType::StoredFieldType  GeoPropertyFieldType;

    typedef OSBGeoPropertyConversionElement<GeoPropertyType> Self;
    typedef OSBCommonElement                                 Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructor                                                  */
    /*! \{                                                                 */

    OSBGeoPropertyConversionElement(OSBRootElement *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Destructor                                                   */
    /*! \{                                                                 */

    virtual ~OSBGeoPropertyConversionElement(void);

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
    /*==========================  PRIVATE  ================================*/
  private:
};

OSG_END_NAMESPACE

#include "OSGOSBGeoPropertyConversionElement.inl"

#endif /* _OSGOSBGEOPROPERTYCONVERSIONELEMENT_H_ */
