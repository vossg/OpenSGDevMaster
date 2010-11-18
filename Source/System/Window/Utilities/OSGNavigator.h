/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSG_NAVIGATOR_H_
#define _OSG_NAVIGATOR_H_

#include "OSGConfig.h"
#include "OSGUtilDef.h"

#include "OSGNavigatorBase.h"
#include "OSGWindow.h"
#include "OSGViewport.h"
#include "OSGBaseTypes.h"
#include "OSGLine.h"
#include "OSGNode.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGIntersectAction.h"

#include "OSGNavigatorEngine.h"
#include "OSGFlyEngine.h"
#include "OSGNoneEngine.h"
#include "OSGTrackballEngine.h"
#include "OSGNavballEngine.h"
#include "OSGWalkEngine.h"

OSG_BEGIN_NAMESPACE

typedef NavballEngine   NavballNavigator;
typedef TrackballEngine TrackballNavigator;
typedef FlyEngine       FlyNavigator;
typedef WalkEngine      WalkNavigator;

/*! \brief General Navigator for wrapping simple navigators. See \ref 
           PageSystemWindowNavigatorsNavigator for a description.
    \ingroup GrpUtilNavigation
    \ingroup GrpLibOSGUtil
 */

class OSG_UTIL_DLLMAPPING Navigator : public NavigatorBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Navigator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Navigator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Notificators                              */
    /*! \{                                                                 */

    virtual void buttonPress  (Int16 button,  Int16 x, Int16 y);
    virtual void buttonRelease(Int16 button,  Int16 x, Int16 y);
    virtual void keyPress     (Int16 key   ,  Int16 x, Int16 y);
    virtual void moveTo       (               Int16 x, Int16 y);
    virtual void idle         (Int16 buttons, Int16 x, Int16 y);

    void updateCameraTransformation();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    void setMode         (Mode new_mode, bool copyViewParams=false);
    void setViewport     (Viewport     *new_viewport);
    void setRotationAngle(Real32        new_angle   );
    void setMotionFactor (Real32        new_factor  );
    void setFrom         (Pnt3f         new_from    );
    void setAt           (Pnt3f         new_at      );
    void setDistance     (Real32        new_distance);
    void setUp           (Vec3f         new_up      );
    void set             (Pnt3f         new_from, Pnt3f new_at, Vec3f new_up);
    void set             (const Matrix &new_matrix  );
    bool setAbsolute     (bool          state       );
    bool setClickCenter  (bool          state       );

    bool setClickNoIntersect (bool state);

    void setCameraTransformation(Node * const new_cartn);

    void setUserEngine(NavigatorEngine* userEngine);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    const Matrix &getMatrix();
    const Pnt3f  &getFrom();
    const Pnt3f  &getAt();
    const Vec3f  &getUp();
          Real32  getDistance();
          State   getState();
          Mode    getMode();
          Real32  getRotationAngle();
          Real32  getMotionFactor();
          bool    getAbsolute();
          bool    getClickCenter();
          bool    getClickNoIntersect();

          bool    getMoved(void);
          Int16   getLastX(void);
          Int16   getLastY(void);
    Viewport     *getViewport(void);

    NavballEngine&   getNavballEngine  (void);
    TrackballEngine& getTrackballEngine(void);
    FlyEngine&       getFlyEngine      (void);
    WalkEngine&      getWalkEngine     (void);
    NoneEngine&      getNoneEngine     (void);
    NavigatorEngine& getUserEngine     (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Fields                              */
    /*! \{                                                                 */

    NavigatorEngineRefPtr _engine;  // current engine

    TrackballEngineRefPtr _trackballEngine;
    FlyEngineRefPtr       _flyEngine;
    WalkEngineRefPtr      _walkEngine;
    NavballEngineRefPtr   _navballEngine;
    NoneEngineRefPtr      _noneEngine;
    NavigatorEngineRefPtr _userEngine;

    Real32             _rRotationAngle;
    Real32             _rMotionFactor;
    bool               _absolute;

    ViewportRecPtr     _vp;
    NodeRecPtr         _cartN;

    bool               _moved;
    bool               _clickCenter;
    bool               _clickNoIntersect;
    Int16              _lastX;
    Int16              _lastY;

    Matrix      theMatrix;

    /*! \}                                                                 */

 public:

    bool calcFromTo(Int16 x, Int16 y, Real32& fromX, Real32& fromY,
                    Real32& toX, Real32& toY);
};

OSG_END_NAMESPACE

#endif
