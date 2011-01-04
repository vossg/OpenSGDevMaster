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

#ifndef _OSGGEOVERTEXARRAYPUMPGROUP_H_
#define _OSGGEOVERTEXARRAYPUMPGROUP_H_
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

class OSG_DRAWABLE_DLLMAPPING GeoVertexArrayPumpGroup : 
    public GeoPumpGroup
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Con-/Destructors                             */
    /*! \{                                                                 */
    GeoVertexArrayPumpGroup(void);

    virtual ~GeoVertexArrayPumpGroup();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    GeoPump         getGeoPump        (DrawEnv                 *pEnv,
                                       PropertyCharacteristics  acset);

    PartialGeoPump  getPartialGeoPump (DrawEnv                 *pEnv, 
                                       PropertyCharacteristics  acset);

    ExtIndexGeoPump getExtIndexGeoPump(DrawEnv                 *pEnv, 
                                       PropertyCharacteristics  acset);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extension handling                      */
    /*! \{                                                                 */

    static bool             glextInitFunction(void);
    static InitFuncWrapper _glextInitFuncWrapper;
  
    /*! Extensions IDs */
    
    static UInt32 _extSecondaryColor;
    static UInt32 _extMultitexture;
    static UInt32 _arbVertexProgram;
    static UInt32 _extCompiledVertexArray;
    static UInt32 _extDrawRangeElements;

    /*! OpenGL extension function indices.
    */
    static UInt32 _funcglSecondaryColorPointer;
    static UInt32 _funcglClientActiveTextureARB;
    static UInt32 _funcglLockArraysEXT;
    static UInt32 _funcglUnlockArraysEXT;
    static UInt32 _funcglDrawRangeElementsEXT;
    static UInt32 _funcglVertexAttribPointerARB;
    static UInt32 _funcglEnableVertexAttribArrayARB;
    static UInt32 _funcglDisableVertexAttribArrayARB;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Pump functions                            */
    /*! \{                                                                 */
    
    static void masterGeoPump       (DrawEnv *pEnv, Geometry *geo);

    static void masterClassicGeoPump(DrawEnv *pEnv, Geometry *geo);
    static void masterAttribGeoPump (DrawEnv *pEnv, Geometry *geo);
    

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif /* _OSGGEOVERTEXARRAYPUMPGROUP_H_ */
