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

#include "OSGWindow.h"
#include "OSGViewport.h"
#include "OSGBaseTypes.h"
#include "OSGLine.h"
#include "OSGNode.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGIntersectAction.h"
#include "OSGTrackballNavigator.h"
#include "OSGFlyNavigator.h"
#include "OSGWalkNavigator.h"

OSG_BEGIN_NAMESPACE

/*! \brief General Navigator for wrapping simple navigators. See \ref 
    PageSystemWindowNavigatorsNavigator for a description.
*/
class OSG_UTIL_DLLMAPPING Navigator
{
    /*==========================  PUBLIC  =================================*/
  public:
  
    enum Mode
    {
        TRACKBALL=0,
        FLY,
        WALK,
        NONE
    };

    enum State
    {
        IDLE=0,
        ROTATING,
        TRANSLATING_XY,
        TRANSLATING_Z,

        TRANSLATING_ZPLUS=10,
        TRANSLATING_ZMINUS
    };

    enum MouseButton
    {
        LEFT_MOUSE=0,
        MIDDLE_MOUSE,
        RIGHT_MOUSE,
        UP_MOUSE,
        DOWN_MOUSE
    };

    enum Key
    {
        LEFT=0,
        RIGHT,
        FORWARDS,
        BACKWARDS,
        LEFTROT,
        RIGHTROT
    };


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Navigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Navigator();

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

    void setMode         (Mode          new_mode    );
    void setViewport     (ViewportPtr   new_viewport);
    void setRotationAngle(Real32        new_angle   );
    void setMotionFactor (Real32        new_factor  );
    void setFrom         (Pnt3f         new_from    );
    void setAt           (Pnt3f         new_at      );
    void setDistance     (Real32        new_distance);
    void setUp           (Vec3f         new_up      );
    void set             (Pnt3f         new_from, Pnt3f new_at, Vec3f new_up);
    void set             (const Matrix &new_matrix  );
    bool setClickCenter  (bool          state       );

    bool setClickNoIntersect (bool state);

    void setCameraTransformation(const NodePtr & new_cartn);

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
    
          WalkNavigator* getWalkNavigator() { return &_walker; }

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Fields                              */
    /*! \{                                                                 */

    TrackballNavigator _trackball;
    FlyNavigator       _flyer;
    WalkNavigator      _walker;

    Real32      _rRotationAngle;
    Real32      _rMotionFactor;
    State       _currentState;
    Mode        _currentMode;

    ViewportPtr _vp;
    NodePtr     _cartN;

    bool        _moved;
    bool        _clickCenter;
    bool        _clickNoIntersect;
    Real32      _lastX, _lastY;
    Pnt3f       _ip;
    Vec3f       _dir;
    Matrix      theMatrix;

    Matrix      _NoneMatrix;

    /*! \}                                                                 */

    void setNoneMatrix(Pnt3f new_from, Pnt3f new_at, Vec3f new_up);

    void getIntersectionPoint(Int16 x, Int16 y);
    void calcDeltas(Int16 fromX, Int16 fromY, Int16 toX, Int16 toY,
                          Real32 &distanceX, Real32 &distanceY);

};

OSG_END_NAMESPACE

#define OSGNAVIGATOR_HEADER_CVSID "@(#)$Id$"

#endif
