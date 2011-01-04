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

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGCamera.h"
#include "OSGTransform.h"

#include "OSGNavigator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Navigator
    \ingroup GrpSystemWindowNavigators

    The general Navigator helper class, see \ref 
    PageSystemWindowNavigatorsNavigator for a description.
    
    
*/


/*! \enum OSG::NavigatorBase::Mode

    The navigation mode, i.e. the actual active low-level navigator.
    The NONE case is also used for the purpose of matrix consistency.
*/


/*! \enum OSG::NavigatorBase::State

    The navigation state, mainly needed for correct interpretation of mouse
    motions, which have to be interpreted differently for  different states. 
    Interpretation also depends on the currently active Navigator::Mode.
*/

/*! \var NavigatorBase::State NavigatorBase::IDLE

    Inactive state. 
*/

/*! \var NavigatorBase::State NavigatorBase::ROTATING

    State for in-place rotation. 
*/

/*! \var NavigatorBase::State NavigatorBase::TRANSLATING_XY

    State for x/y translation, used by the Trackball case. 
*/

/*! \var NavigatorBase::State NavigatorBase::TRANSLATING_Z

    State for z translation, used by the Trackball case. 
*/

/*! \var NavigatorBase::State NavigatorBase::TRANSLATING_ZPLUS

    State for rotation with automatic forward motion. The standard fly forward
    state. 
*/

/*! \var NavigatorBase::State NavigatorBase::TRANSLATING_ZMINUS

    State for rotation with automatic backwards motion. The standard fly
    backwards state. 
*/


/*! \enum OSG::NavigatorBase::MouseButton

    Abstraction enumeration for mouse buttons, to keep the Navigator
    independent of the actual Window System.
*/

/*! \var NavigatorBase::MouseButton NavigatorBase::UP_MOUSE

    Mouse wheel up button. 
*/

/*! \var NavigatorBase::MouseButton NavigatorBase::DOWN_MOUSE

    Mouse wheel down button. 
*/


/*! \enum OSG::NavigatorBase::Key

    Abstraction enumeration for keys, to keep the Navigator
    independent of the actual Window System.
*/



/*! \var Navigator::_rMotionFactor

    The motion factor, roughly equivalent to speed.
*/

/*------------------------- constructors ----------------------------------*/

Navigator::Navigator() :
    _engine(NULL), // pointer to current engine

    _trackballEngine(TrackballEngine::create()),
    _flyEngine      (FlyEngine      ::create()),
    _walkEngine     (WalkEngine     ::create()),
    _noneEngine     (NoneEngine     ::create()),
    _userEngine     (TrackballEngine::create()),

    _rRotationAngle(0.04908739f),
    _rMotionFactor(1.f),
    _absolute(true),
    _vp(NULL),
    _cartN(NULL),
    _moved(false),
    _clickCenter(true),
    _clickNoIntersect(false),
    _lastX(0),
    _lastY(0)
{
    setMode(TRACKBALL); // use trackball as default
}

/*-------------------------- destructors ----------------------------------*/

Navigator::~Navigator()
{
    _cartN = NULL;
    _vp    = NULL;

    _engine          = NULL;
    _trackballEngine = NULL;
    _flyEngine       = NULL;
    _walkEngine      = NULL;
    _noneEngine      = NULL;
    _userEngine      = NULL;
}

/*-------------------------- Notificators ---------------------------------*/

/*! Mouse button press handler.
*/
void Navigator::buttonPress(Int16 button, Int16 x, Int16 y)
{
    _lastX = x; _lastY = y;
    _moved = false;

    _engine->buttonPress(button, x, y, this);
}

/*! Mouse button release handler.
*/
void Navigator::buttonRelease(Int16 button, Int16 x, Int16 y)
{
    _engine->buttonRelease(button, x, y, this);
}

/*! Key press handler.
*/
void Navigator::keyPress(Int16 key, Int16 x, Int16 y)
{
    _engine->keyPress(key, x, y, this);
}

/*! Mouse motion handler.
*/
void Navigator::moveTo(Int16 x, Int16 y)
{
    _moved = true;

    Real32 fromX, fromY, toX, toY;
    if (!calcFromTo(x, y, fromX, fromY, toX, toY)) return;

    _engine->moveTo(x, y, this);

    _lastX = x;
    _lastY = y;
}

/*! Performs some idle operations, depending on the current navigation mode
 */
void Navigator::idle(Int16 buttons, Int16 x, Int16 y)
{
    _engine->idle(buttons, x, y, this);
}

/*! Updates the camera transformation matrix directly in the node specified as
    the cart.
*/
void Navigator::updateCameraTransformation()
{
    theMatrix.setIdentity();
    if(_absolute && _cartN != NULL && _cartN->getParent() != NULL)
    {
        _cartN->getParent()->getToWorld(theMatrix);
        theMatrix.inverse(theMatrix);
    }

    _engine->onUpdateCameraTransformation(this);
    theMatrix.mult(_engine->getMatrix());

    if(_cartN != NULL)
    {
        Transform *t = dynamic_cast<Transform *>(_cartN->getCore());
        if(t == NULL)
        {
            FWARNING (("Navigator: updateCamTrans, core is not TransformPtr\n"));
        }
        else
        {
            if(t->getMatrix() != theMatrix)
            {
                t->setMatrix(theMatrix);
            }
        }
    }
    else
    {
        FFATAL (("!_cartN in Navigator::updateCameraTrans\n"));
    }
}

/*------------------------------ set --------------------------------------*/

/*! Set the navigator mode (Trackball/Flyer/Walker).
*/
void Navigator::setMode(Navigator::Mode new_mode, bool copyViewParams)
{
    NavigatorEngine* engine = _trackballEngine;

    switch (new_mode) {
        case TRACKBALL: engine = _trackballEngine; break;
        case FLY:       engine = _flyEngine;       break;
        case WALK:      engine = _walkEngine;      break;
        case NONE:      engine = _noneEngine;      break;
        case USER:      engine = _userEngine;      break;
        default:
            FWARNING (("Navigator: unknown mode. Fallback to trackball.\n"));
    }

    assert(engine);

    if (engine != _engine)
    {
        if (copyViewParams && _engine)
            engine->set(_engine->getFrom(),_engine->getAt(),_engine->getUp());

        _engine = engine;
        _engine->onActivation(this);
    }
}

/*! Set the rotation angle.
*/
void Navigator::setRotationAngle(Real32 new_angle)
{
    _rRotationAngle = new_angle;
}

/*! Set the motion factor.
*/
void Navigator::setMotionFactor(Real32 new_factor)
{
    _rMotionFactor = new_factor;
}

/*! Set the viewport.
*/
void Navigator::setViewport(Viewport *new_viewport)
{
    _vp = new_viewport;
    _engine->onViewportChanged(this);
}

/*! Set the from point, i.e. the viewer position.
*/
void Navigator::setFrom(Pnt3f new_from)
{
    _engine->setFrom(new_from);
}

/*! Set the at point, i.e. the target position for the viewer.
*/
void Navigator::setAt(Pnt3f new_at)
{
    _engine->setAt(new_at);
}

/*! Set the distance from the target position.
*/
void Navigator::setDistance(Real32 new_distance)
{
    _engine->setDistance(new_distance);
}


/*! Set the up vector, i.e. the vertical direction on screen.
*/
void Navigator::setUp(Vec3f new_up)
{
    _engine->setUp(new_up);
}

/*! Set the full navigator parameters.
*/
void Navigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    _engine->set(new_from, new_at, new_up);
}

/*! Set the full navigator parameters from a matrix.
*/
void Navigator::set(const Matrix & new_matrix)
{
    _engine->set(new_matrix);
}


/*! Set the camera transformation node.
*/
void Navigator::setCameraTransformation(Node * const new_cartn)
{
    if (new_cartn == NULL)
    {
        FWARNING (("Set _cartN in Navigator to NULL\n"));
    }

    _cartN = new_cartn;
}

/*------------------------------ get --------------------------------------*/

/*! Get the transformation matrix.
*/
const Matrix &Navigator::getMatrix(void)
{
    return _engine->getMatrix();
}

/*! Get the from point, i.e. the viewer position.
*/
const Pnt3f  &Navigator::getFrom(void)
{
    return _engine->getFrom();
}

/*! Get the at point, i.e. the target position.
*/
const Pnt3f  &Navigator::getAt(void)
{
    return _engine->getAt();
}

/*! Get the up vector.
*/
const Vec3f  &Navigator::getUp(void)
{
    return _engine->getUp();
}


/*! Get the distance from the target position.
*/
Real32 Navigator::getDistance(void)
{
    return _engine->getDistance();
}

/*! Get the navigator's current state.
*/
Navigator::State Navigator::getState(void)
{
    return _engine->getState();
}

/*! Get the navigator's current mode.
*/
Navigator::Mode Navigator::getMode(void)
{
    if (_engine == _trackballEngine) return TRACKBALL;
    if (_engine == _flyEngine)       return FLY;
    if (_engine == _walkEngine)      return WALK;
    if (_engine == _noneEngine)      return NONE;

    return USER;
}

/*! Get the navigator's rotation angle.
*/
Real32 Navigator::getRotationAngle(void)
{
    return _rRotationAngle;
}

/*! Get the navigator's motion factor
*/
Real32 Navigator::getMotionFactor(void)
{
    return _rMotionFactor;
}

/*! Get the absolute current state.
*/
bool Navigator::getAbsolute(void)
{
    return _absolute;
}

/*! Get the clickCenter current state.
*/
bool Navigator::getClickCenter(void)
{
    return _clickCenter;
}

/*! Get the clickNoIntersect current state.
*/
bool Navigator::getClickNoIntersect(void)
{
    return _clickNoIntersect;
}


bool Navigator::getMoved(void)
{ 
    return _moved;
}

Viewport *Navigator::getViewport(void)
{
    return _vp;
}

Int16 Navigator::getLastX(void)
{
    return _lastX;
}

Int16 Navigator::getLastY(void)
{
    return _lastY;
}

TrackballEngine& Navigator::getTrackballEngine(void)
{ 
    return *_trackballEngine; 
}

FlyEngine& Navigator::getFlyEngine(void)
{ 
    return *_flyEngine;
}

WalkEngine& Navigator::getWalkEngine(void)
{ 
    return *_walkEngine;
}

NoneEngine &Navigator::getNoneEngine(void)
{
    return *_noneEngine;
}

NavigatorEngine& Navigator::getUserEngine(void)
{
    return *_userEngine;
}

void Navigator::setUserEngine(NavigatorEngine* userEngine)
{
    if (userEngine == NULL) return;

    if (userEngine != _userEngine)
    {
        _userEngine = userEngine;
    }

    if (getMode() == USER) setMode(USER); // assign userEngine to _engine
}


/*! Set the clickCenter current state.
*/
bool Navigator::setClickCenter(bool state)
{
    bool old = _clickCenter;

    _clickCenter = state;
    return old;
}

/*! Set absolute mode.
*/
bool Navigator::setAbsolute(bool state)
{
    bool old = _absolute;

    _absolute = state;
    return old;
}

/*! Set the clickCenter current state.
*/
bool Navigator::setClickNoIntersect(bool state)
{
    bool old = _clickNoIntersect;

    _clickNoIntersect = state;
    return old;
}

bool Navigator::calcFromTo(Int16   x,     Int16   y,
                           Real32& fromX, Real32& fromY,
                           Real32& toX,   Real32& toY)
{
    Real32 width  = Real32(_vp->getPixelWidth());
    Real32 height = Real32(_vp->getPixelHeight());

    if(width <= 0 || height <= 0) return false;

    Window *par = _vp->getParent();
    Real32 winHeight;
    
    if(par != NULL)
        winHeight = Real32(par->getHeight());
    else
        winHeight = height;
        
    fromX = (2.0f * (_lastX - _vp->getPixelLeft())- width) /  width;
    fromY = (2.0f * (winHeight-_lastY-_vp->getPixelBottom())-height) / height;

    toX   = (2.0f * (x - _vp->getPixelLeft()) - width) / width;
    toY   = (2.0f * (winHeight - y - _vp->getPixelBottom()) - height) / height;

    return true;
}

