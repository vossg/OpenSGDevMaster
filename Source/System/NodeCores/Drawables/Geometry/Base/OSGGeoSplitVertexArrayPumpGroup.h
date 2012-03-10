/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGGEOSPLITVERTEXARRAYPUMPGROUP_H_
#define _OSGGEOSPLITVERTEXARRAYPUMPGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <utility>

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGGeometry.h"
#include "OSGGeoPumpGroup.h"

OSG_BEGIN_NAMESPACE

class Window;

/*! \brief Pump group using vertex arrays. Only works for non- and
     single-indexed geometry
    \ingroup GrpDrawablesGeometryHelpers
 */

class OSG_DRAWABLE_DLLMAPPING GeoSplitVertexArrayPumpGroup : 
    public GeoPumpGroup
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Con-/Destructors                             */
    /*! \{                                                                 */

    GeoSplitVertexArrayPumpGroup(void);

    virtual ~GeoSplitVertexArrayPumpGroup();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    virtual SplitGeoPump getSplitGeoPump(DrawEnv                 *pEnv,
                                         PropertyCharacteristics  acset);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    virtual GeoPump getGeoPump(DrawEnv                 *pEnv,
                               PropertyCharacteristics  acset);

    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extension handling                      */
    /*! \{                                                                 */

    static bool             glextInitFunction(void);
    static InitFuncWrapper _glextInitFuncWrapper;
  
    /*! Extensions IDs */
    
    static UInt32 _arbVertexProgram;
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    static UInt32 _extSecondaryColor;
    static UInt32 _extMultitexture;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Pump functions                            */
    /*! \{                                                                 */

#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    static bool masterClassicGeoSetupPump(
              DrawEnv                     *pEnv,
        const GeoIntegralProperty         *lengths,
        const GeoIntegralProperty         *types,
        const Geometry::MFPropertiesType  *prop,
        const Geometry::MFPropIndicesType *propIdx );

    static void masterClassicGeoDrawPump (
              DrawEnv                     *pEnv,
        const GeoIntegralProperty         *lengths,
        const GeoIntegralProperty         *types,
        const Geometry::MFPropertiesType  *prop,
        const Geometry::MFPropIndicesType *propIdx );
#endif

    static bool masterAttribGeoSetupPump(
              DrawEnv                     *pEnv,
        const GeoIntegralProperty         *lengths,
        const GeoIntegralProperty         *types,
        const Geometry::MFPropertiesType  *prop,
        const Geometry::MFPropIndicesType *propIdx );

    static void masterAttribGeoDrawPump (
              DrawEnv                     *pEnv,
        const GeoIntegralProperty         *lengths,
        const GeoIntegralProperty         *types,
        const Geometry::MFPropertiesType  *prop,
        const Geometry::MFPropIndicesType *propIdx );

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif /* _OSGGEOSPLITVERTEXARRAYPUMPGROUP_H_ */
