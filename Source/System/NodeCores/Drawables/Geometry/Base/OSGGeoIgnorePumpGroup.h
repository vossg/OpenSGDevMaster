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

#ifndef _OSGGEOIGNOREPUMPGROUP_H_
#define _OSGGEOIGNOREPUMPGROUP_H_
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

/*! \brief A dummy GeoPumpGroup that ignores all renders. Useful for
        debugging.
    \ingroup GrpDrawablesGeometryHelpers
 */

class OSG_DRAWABLE_DLLMAPPING GeoIgnorePumpGroup : 
    public GeoPumpGroup
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                 Con-/Destructors                             */
    /*! \{                                                                 */
    GeoIgnorePumpGroup(void);

    virtual ~GeoIgnorePumpGroup();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    GeoPump getGeoPump                (DrawEnv                 *pEnv,
                                       PropertyCharacteristics  acset);

    PartialGeoPump getPartialGeoPump  (DrawEnv                 *pEnv, 
                                       PropertyCharacteristics  acset);

    ExtIndexGeoPump getExtIndexGeoPump(DrawEnv                 *pEnv, 
                                       PropertyCharacteristics  acset);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                    Pump functions                            */
    /*! \{                                                                 */
    
    static void masterGeoPump        (DrawEnv  *pEnv, 
                                      Geometry *geo); 
                                         
    static void masterPartialGeoPump (DrawEnv  *pEnv,
                                      Geometry *geo,
                                      UInt32    primtype, 
                                      UInt32    firstvert, 
                                      UInt32    nvert   );

    static void masterExtIndexGeoPump(DrawEnv  *pEnv,
                                      Geometry *geo,
                                      UInt32   *indices, 
                                      UInt32    nvert);

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#endif /* _OSGGEOIgnorePUMPGROUP_H_ */
