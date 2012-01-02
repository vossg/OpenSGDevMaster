/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAEXTRAHANDLER_H_
#define _OSGCOLLADAEXTRAHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGFileIODef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"

#include "dom/domExtra.h"

OSG_BEGIN_NAMESPACE

class ColladaGeometry;
class ColladaTexture;
class ColladaEffect;

// forward declarations
//class ColladaGlobal;
//OSG_GEN_MEMOBJPTR(ColladaGlobal);


class OSG_FILEIO_DLLMAPPING ColladaExtraHandler : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject        Inherited;
    typedef ColladaExtraHandler Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaExtraHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void readTextureExtraElements(      ColladaTexture *texture,
                                          const domExtra       *extra  ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual void readTechniqueExtraElements(      ColladaEffect   *effect,
                                            const domExtra        *extra ) = 0;


    virtual void readGeometryExtraElements (      ColladaGeometry *effect,
                                            const domExtra        *extra ) = 0;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaExtraHandler(void);
    virtual ~ColladaExtraHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};


OSG_GEN_MEMOBJPTR(ColladaExtraHandler);

OSG_END_NAMESPACE

#include "OSGColladaExtraHandler.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAEXTRAHANDLER_H_
