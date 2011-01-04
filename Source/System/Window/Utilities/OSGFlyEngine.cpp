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

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"

#include "OSGFlyEngine.h"
#include "OSGNavigator.h"
#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FlyEngine
    \ingroup GrpSystemWindowNavigators

The FlyEngine models a simple flying navigation model, see \ref 
PageSystemWindowNavigatorsFly for a description.

*/

/*! \var OSG::FlyEngine::_rFrom

    The from point, i.e. the viewer position.
*/

/*! \var OSG::FlyEngine::_rAt

    The at point, i.e. the target position.
*/

/*! \var OSG::FlyEngine::_vUp

    The up vector.
*/

/*! \var OSG::FlyEngine::_tMatrix

    The transformation matrix for this navigator.
*/

/*------------------------- constructors ----------------------------------*/

FlyEngineTransitPtr
FlyEngine::create(void)
{
    return FlyEngineTransitPtr(new FlyEngine);
}

/*------------------------------ get --------------------------------------*/

/*! Get the from point.
*/
const Pnt3f &FlyEngine::getFrom()
{
    return _rFrom;
}

/*! Get the at point.
*/
const Pnt3f &FlyEngine::getAt()
{
    return _rAt;
}

/*! Get the up vector.
*/
const Vec3f &FlyEngine::getUp()
{
    return _vUp;
}

/*! Get the current transformation matrix.
*/
const Matrix &FlyEngine::getMatrix()
{
    MatrixLookAt(_tMatrix,_rFrom,_rAt,_vUp);
    return _tMatrix;
}

/*! Not needed by FlyEngine!!!
*/
// FIXME: remove getDistance() from NavigatorEngine???
Real32 FlyEngine::getDistance()
{
    return 0.0f;
}

/*------------------------------ set --------------------------------------*/

/*! Set the from point, the point where the viewer is (i.e the center 
    of all transformations).
*/
void FlyEngine::setFrom(Pnt3f new_from)
{
    _rFrom=new_from;
}

/*! Sets the target point at which the viewer is looking.
*/
void FlyEngine::setAt(Pnt3f new_At)
{
    _rAt=new_At;
}

/*! Sets the up vector, i.e. the direction that point up on the screen.
*/
void FlyEngine::setUp(Vec3f new_up)
{
    _vUp=new_up;
}

/*! Set the position and the orientation at once.
*/
void FlyEngine::set(Pnt3f new_from,Pnt3f new_At,Vec3f new_up)
{
    _rFrom=new_from;
    _rAt=new_At;
    _vUp=new_up;
}

/*! Set the position and the orientation at once using a matrix.
*/
void FlyEngine::set(const Matrix& new_matrix)
{
    _rFrom= Pnt3f(new_matrix[3]);
    _rAt  = Pnt3f(new_matrix[3] - new_matrix[2]);
    _vUp  = Vec3f(new_matrix[1]);

    set(_rFrom, _rAt, _vUp);
}

/*! Moves dist steps forward
*/
void FlyEngine::setDistance(Real32 dist)
{
    forward(dist);
}

/*---------------------- navigator engine callbacks ------------------------*/

void FlyEngine::buttonPress(Int16 button, Int16 x, Int16 y, Navigator* nav)
{
    switch (button)
    {
        case Navigator::LEFT_MOUSE:  
            _currentState = Navigator::TRANSLATING_ZPLUS;
            break;                            
        case Navigator::MIDDLE_MOUSE:
            _currentState = Navigator::ROTATING;           
            break;          
        case Navigator::RIGHT_MOUSE:  
            _currentState = Navigator::TRANSLATING_ZMINUS; 
            break;
        case Navigator::UP_MOUSE:  
            _currentState = Navigator::IDLE;
            forward(-nav->getMotionFactor());
            break;
        case Navigator::DOWN_MOUSE:
            _currentState = Navigator::IDLE;
            forward(nav->getMotionFactor());
            break;
        default:
            FNOTICE(("FlyEngine: buttonPress, unknown button\n"));
            break;
    }
}

void FlyEngine::buttonRelease(Int16 button, Int16 x,Int16 y,Navigator* nav)
{
    _currentState = Navigator::IDLE;
}

void FlyEngine::keyPress(Int16 key, Int16 x,Int16 y,Navigator* nav)
{
    switch (key)
    {
        case Navigator::LEFTROT:
            rotate(-nav->getRotationAngle(), 0);
            break;
        case Navigator::RIGHTROT:
            rotate(nav->getRotationAngle(), 0);
            break;
        case Navigator::LEFT:
            right(nav->getMotionFactor());
            break;
        case Navigator::RIGHT:
            right(-nav->getMotionFactor());
            break;
        case Navigator::FORWARDS:
            forward(-nav->getMotionFactor());
            break;
        case Navigator::BACKWARDS:
            forward( nav->getMotionFactor());
            break;
        default:
            FNOTICE(("FlyEngine: keyPress, unknown key\n"));
            break;
    }
}

void FlyEngine::moveTo(Int16 x,Int16 y,Navigator* nav)
{
    Real32 fromX,fromY, toX,toY;  

    nav->calcFromTo(x,y, fromX,fromY, toX,toY);

    Real32 distanceX = -(fromX-toX);
    Real32 distanceY =  (fromY-toY);
    rotate(distanceX, distanceY);

    switch (_currentState)
    {
        case Navigator::TRANSLATING_ZPLUS:
            forward(-nav->getMotionFactor());
            break;
        case Navigator::TRANSLATING_ZMINUS:
            forward(nav->getMotionFactor());
            break;                                    
        case Navigator::ROTATING:
            break;
        default:
            //IDLE
            break;
    }
}

void FlyEngine::idle(Int16 buttons, Int16 x,Int16 y,Navigator* nav)
{
}

/*---------------------- Flyer Transformations ----------------------------*/

/*! Rotate the viewer \a deltaX around the up axis and deltaY around the 
    left/right axis. \a deltaX and \a deltaY should be between -Pi and Pi.
*/
void FlyEngine::rotate(Real32 deltaX, Real32 deltaY)
{
    // rotate around the up vector
    Matrix final,temp;
    Quaternion q;

    q.setValueAsAxisRad(_vUp,-deltaX);
    q.getValue(temp);

    final.setIdentity();
    final.setTranslate(_rFrom);
    final.mult(temp);

    temp.setIdentity();
    temp.setTranslate(-_rFrom[0],-_rFrom[1],-_rFrom[2]);

    final.mult(temp      );
    final.mult(_rAt, _rAt);

    // rotate around the side vector

    Vec3f lv = _rAt-_rFrom;
    lv.normalize();

    Vec3f sv = lv;
    sv.crossThis(_vUp);
    sv.normalize();
    q.setValueAsAxisRad(sv,-deltaY);
    q.getValue(temp);

    final.setIdentity();
    final.setTranslate(_rFrom);
    final.mult(temp);

    temp.setIdentity();
    temp.setTranslate(-_rFrom[0],-_rFrom[1],-_rFrom[2]);

    final.mult(temp);
    final.mult(_rAt, _rAt);
}

/*! Flies forward, i.e. translation \a step units along the view vector.
*/
Real32 FlyEngine::forward(Real32 step)
{
    Vec3f lv;
    lv = _rFrom-_rAt;
    lv.normalize();
    lv *= (step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(lv);
    transl.mult(_rAt,   _rAt  );
    transl.mult(_rFrom, _rFrom);
    return 0.0;
}

/*! Strafes to the right, i.e. translates along the side vector.
*/
Real32 FlyEngine::right(Real32 step)
{
    Vec3f sv;
    sv = _rFrom-_rAt;
    sv.crossThis(_vUp);
    sv.normalize();
    sv *= (step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(sv);
    transl.mult(_rAt,   _rAt  );
    transl.mult(_rFrom, _rFrom);
    return 0.0;
}

/*-------------------------- constructors ---------------------------------*/

FlyEngine::FlyEngine(void) : Inherited()
{
    _rFrom  .setValues(0,0,0);
    _rAt    .setValues(0,0,1);
    _vUp    .setValues(0,1,0);
    _tMatrix.setIdentity();
}

/*-------------------------- destructors ----------------------------------*/

FlyEngine::~FlyEngine()
{
}
