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

#ifndef _OSGCOLLADAINSTANCEVISUALSCENE_H_
#define _OSGCOLLADAINSTANCEVISUALSCENE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaInstanceElement.h"
#include "OSGColladaVisualScene.h"
#include "OSGColladaElementFactoryHelper.h"

#include <dom/domVisual_scene.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpFileIOCollada
    \nohierarchy
 */

class OSG_FILEIO_DLLMAPPING ColladaInstanceVisualScene
    : public ColladaInstanceElement
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef ColladaInstanceElement     Inherited;
    typedef ColladaInstanceVisualScene Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(ColladaInstanceVisualScene);

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

    virtual void            read   (void                  );
    virtual FieldContainer *process(ColladaElement *parent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Access                                                       */
    /*! \{                                                                 */

    virtual ColladaVisualScene *getTargetElem   (void) const;
    virtual domVisual_scene    *getTargetDOMElem(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */
    
             ColladaInstanceVisualScene(daeElement    *elem,
                                        ColladaGlobal *global);
    virtual ~ColladaInstanceVisualScene(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ColladaElementRegistrationHelper _regHelper;
};

OSG_GEN_MEMOBJPTR(ColladaInstanceVisualScene);

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEVISUALSCENE_H_
