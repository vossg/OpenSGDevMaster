/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#ifndef _OSGGEOPROPERTYFACTORY_H_
#define _OSGGEOPROPERTYFACTORY_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/*! \brief Accessible via #GeoPropertyFactory
    \ingroup GrpDrawablesGeometryProperties
    \ingroup GrpLibOSGDrawables
 */

class GeoPropertyFactoryBase
{
  public:
  
    GeoIntegralPropertyTransitPtr create(UInt32 format                   );
    GeoVectorPropertyTransitPtr   create(UInt32 format,  UInt32 dim,
                                         UInt32 vecType, bool   normalize);
  
  protected:
    typedef GeoVectorPropertyTransitPtr (*CreatePropFuncP)(void);
    
    UInt32 mapFormat    (UInt32 format   ) const;
    UInt32 mapDimension (UInt32 dim      ) const;
    UInt32 mapVectorType(UInt32 vecType  ) const;
    UInt32 mapNormalize (bool   normalize) const;
    
    template <class PropertyTypeT>
    static GeoVectorPropertyTransitPtr createPropFunc       (void);
    static GeoVectorPropertyTransitPtr invalidCreatePropFunc(void);
    
    static CreatePropFuncP _createFuncMap[3][4][8][2];
};

/*! \typedef OSG::SingletonHolder<OSG::GeoPropertyFactoryBase> GeoPropertyFactory;
    \ingroup GrpDrawablesGeometryProperties
    \relatesalso OSG::GeoPropertyFactoryBase
 */

typedef SingletonHolder<GeoPropertyFactoryBase> GeoPropertyFactory;

OSG_END_NAMESPACE

#include "OSGGeoPropertyFactory.inl"

#endif // _OSGGEOPROPERTYFACTORY_H_
