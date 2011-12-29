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

#ifndef _OSGCOLLADAMAYAEXTRAHANDLER_H_
#define _OSGCOLLADAMAYAEXTRAHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaExtraHandler.h"
#include "OSGColladaHandlerFactoryHelper.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaMayaExtraHandler : public ColladaExtraHandler
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaExtraHandler     Inherited;
    typedef ColladaMayaExtraHandler Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaMayaExtraHandler);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual void readTextureExtraElements(      ColladaTexture *texture,
                                          const domExtra       *extra  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void readTechniqueExtraElements(      ColladaEffect   *effect,
                                            const domExtra        *extra   );

    virtual void readGeometryExtraElements (      ColladaGeometry *geometry,
                                            const domExtra        *extra   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    static ColladaExtraHandlerTransitPtr create(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaMayaExtraHandler(void);
    virtual ~ColladaMayaExtraHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    static ColladaExtraHandlerRegHelper _regHelper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

OSG_GEN_MEMOBJPTR(ColladaMayaExtraHandler);

OSG_END_NAMESPACE

//#include "OSGColladaElement.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAMAYAEXTRAHANDLER_H_
