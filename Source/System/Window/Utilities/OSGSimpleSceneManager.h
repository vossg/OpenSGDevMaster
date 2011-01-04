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

#ifndef _OSGSIMPLESCENEMANAGER_H_
#define _OSGSIMPLESCENEMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGBaseTypes.h"

#include "OSGRenderAction.h"

#include "OSGNode.h"
#include "OSGImageForeground.h"
#include "OSGTransform.h"
#include "OSGGeometry.h"
#include "OSGSimpleMaterial.h"
#include "OSGCamera.h"
#include "OSGDirectionalLight.h"
#include "OSGNavigator.h"
#include "OSGStatisticsForeground.h"
#include "OSGNavigationManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief A helper class to simplify managing simple applications.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING SimpleSceneManager : public NavigationManager
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleSceneManager(void);

    SimpleSceneManager *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SimpleSceneManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    virtual Node                  *getRoot            ( void );
    virtual Node                  *getHighlight       ( void );
#ifdef OSG_OLD_RENDER_ACTION
    virtual DrawActionBase        *getAction          ( void );
#endif
    virtual RenderAction          *getRenderAction    ( void );
    virtual bool                   getHeadlightState  ( void );
    virtual DirectionalLight      *getHeadlight       ( void );
    virtual Camera                *getCamera          ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#ifdef OSG_OLD_RENDER_ACTION
    virtual void  setAction        (RenderAction *action    );
#endif

    virtual void  setAction        (RenderAction *action    );

    virtual void  setRoot          (Node         *root      );

    virtual void  setHighlight     (Node         *obj       );
    virtual void  setHeadlight     (bool          on        );
    virtual void  turnHeadlightOn  (void                    );
    virtual void  turnHeadlightOff (void                    );
    virtual void  setCamera        (Camera       *camera    );

    virtual void setUseTraversalAction(bool s               );
    virtual bool getUseTraversalAction(void                 );

    virtual void  showAll          (void                    );

    virtual void  useOpenSGLogo    (void                    );

    virtual void  setStatistics    (bool on                 );
    bool          getStatistics    (void                    );

    virtual void  addForeground    (Foreground * const fg  );
    virtual void  removeForeground (Foreground * const fg  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Interaction handling                           */
    /*! \{                                                                 */

            Line calcViewRay(Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    virtual void update( void );
    virtual void redraw( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator < (const SimpleSceneManager &other) const;

    //bool operator == (const SimpleSceneManager &other) const;
    //bool operator != (const SimpleSceneManager &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                     Updates                                  */
    /*! \{                                                                 */

            void  initialize      (void);
    virtual void  highlightChanged(void);
    virtual void  updateHighlight (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    NodeRecPtr                 _root;

    ImageForegroundRecPtr      _foreground;
    StatisticsForegroundRecPtr _statforeground;
    bool                       _statstate;

    NodeRecPtr                 _highlight;
    NodeRecPtr                 _highlightNode;
    //GeoPositions3fPtr            _highlightPoints;
    GeoPnt3fPropertyRecPtr     _highlightPoints;

    NodeRecPtr                 _internalRoot;
    DirectionalLightRecPtr     _headlight;
#ifdef OSG_OLD_RENDER_ACTION
    RenderAction *             _renderAction;   /**< The RenderAction to use if using RenderActions. */
    RenderAction *             _ownAction;
#endif

    /** The RenderAction to use if using render traversals. */
    RenderAction *             _rtaction;

    TransformRecPtr            _cart;
    CameraRecPtr               _camera;

    bool                       _traversalAction;

    SimpleMaterialRecPtr       _highlightMaterial;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /* prohibit default function (move to 'public' if needed) */

    SimpleSceneManager(const SimpleSceneManager &source);
    void operator =(const SimpleSceneManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef SimpleSceneManager *SimpleSceneManagerP;

OSG_END_NAMESPACE

#include "OSGSimpleSceneManager.inl"

#endif /* _OSGSIMPLESCENEMANAGER_H_ */
