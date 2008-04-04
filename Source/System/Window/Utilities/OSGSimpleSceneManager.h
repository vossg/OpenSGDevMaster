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
#include "OSGWindow.h"

#include "OSGRenderAction.h"

#include "OSGNode.h"
#include "OSGWindow.h"
#include "OSGImageForeground.h"
#include "OSGTransform.h"
#include "OSGGeometry.h"
#include "OSGSimpleMaterial.h"
#include "OSGCamera.h"
#include "OSGDirectionalLight.h"
#include "OSGNavigator.h"
#include "OSGStatisticsForeground.h"

OSG_BEGIN_NAMESPACE

/*! \brief A helper class to simplify managing simple applications.
    \ingroup GrpSystemLib
*/

class OSG_UTIL_DLLMAPPING SimpleSceneManager
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Enums                                   */
    /*! \{                                                                 */

    enum
    {
        MouseLeft   =  0,
        MouseMiddle =  1,
        MouseRight  =  2,
        MouseUp     =  3,
        MouseDown   =  4,
        NoButton    = -1
    };

    /*! \}                                                                 */
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

    virtual NodePtr                getRoot            ( void );
    virtual WindowPtr              getWindow          ( void );
    virtual NodePtr                getHighlight       ( void );
#ifdef OSG_OLD_RENDER_ACTION
    virtual DrawActionBase        *getAction          ( void );
#endif
    virtual RenderAction          *getRenderAction    ( void );
    virtual Navigator             *getNavigator       ( void );
    virtual bool                   getHeadlightState  ( void );
    virtual DirectionalLightPtr    getHeadlight       ( void );
    virtual CameraPtr              getCamera          ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

#ifdef OSG_OLD_RENDER_ACTION
    virtual void  setAction        (RenderAction *action    );
#endif

    virtual void  setAction        (RenderAction *action    );

    virtual void  setRoot          (NodePtr       root      );
    virtual void  setWindow        (WindowPtr     win       );
    virtual void  setHighlight     (NodePtr       obj       );
    virtual void  setHeadlight     (bool          on        );
    virtual void  turnHeadlightOn  (void                    );
    virtual void  turnHeadlightOff (void                    );
    virtual void  setCamera        (CameraPtr     camera    );

    virtual void setUseTraversalAction(bool s               );
    virtual bool getUseTraversalAction(void                 );

    virtual void  showAll          (void                    );

    virtual void  useOpenSGLogo    (void                    );

            void  setNavigationMode(Navigator::Mode new_mode);
    inline  bool  setClickCenter   (bool            mode    );

    virtual void  setStatistics    (bool on                 );
    bool          getStatistics    (void                    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Interaction handling                           */
    /*! \{                                                                 */

    virtual void resize(UInt16 width, UInt16 height);
    virtual void mouseMove(Int16 x, Int16 y);
    virtual void mouseButtonPress(UInt16 button, Int16 x, Int16 y);
    virtual void mouseButtonRelease(UInt16 button, Int16 x, Int16 y);
    virtual void key(UChar8 key, Int16 x, Int16 y);

            Line calcViewRay(Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    virtual void update( void );
    virtual void redraw( void );
    virtual void idle( void );

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

    WindowRecPtr               _win;
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

    Navigator                  _navigator;

    Int16                      _lastx;
    Int16                      _lasty;
    UInt16                     _mousebuttons;

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
