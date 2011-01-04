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

#ifndef _OSGCOLLADASCENE_H_
#define _OSGCOLLADASCENE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaScene.h
    \ingroup GrpLoader
 */
#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaElement.h"
#include "OSGColladaElementFactoryHelper.h"

OSG_BEGIN_NAMESPACE

// forward decl
class ColladaInstanceVisualScene;
OSG_GEN_MEMOBJPTR(ColladaInstanceVisualScene);

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaScene : public ColladaElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaElement  Inherited;
    typedef ColladaScene    Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaScene);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Craete                                                       */
    /*! \{                                                                 */

    static ColladaElementTransitPtr
        create(daeElement *elem, ColladaGlobal *global);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Reading                                                      */
    /*! \{                                                                 */

    virtual void read   (void);
    virtual void process(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaScene(daeElement *elem, ColladaGlobal *global);
    virtual ~ColladaScene(void                                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;

    ColladaInstanceVisualSceneRefPtr        _colInstVisScene;
};

OSG_GEN_MEMOBJPTR(ColladaScene);

OSG_END_NAMESPACE

// #include "OSGColladaScene.inl"
#include "OSGColladaInstanceVisualScene.h"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADASCENE_H_
