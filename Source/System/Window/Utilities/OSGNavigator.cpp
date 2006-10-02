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


/*! \enum OSG::Navigator::Mode

    The navigation mode, i.e. the actual active low-level navigator.
    The NONE case is also used for the purpose of matrix consistency.
*/


/*! \enum OSG::Navigator::State

    The navigation state, mainly needed for correct interpretation of mouse
    motions, which have to be interpreted differently for  different states. 
    Interpretation also depends on the currently active Navigator::Mode.
*/

/*! \var Navigator::State Navigator::IDLE

    Inactive state. 
*/

/*! \var Navigator::State Navigator::ROTATING

    State for in-place rotation. 
*/

/*! \var Navigator::State Navigator::TRANSLATING_XY

    State for x/y translation, used by the Trackball case. 
*/

/*! \var Navigator::State Navigator::TRANSLATING_Z

    State for z translation, used by the Trackball case. 
*/

/*! \var Navigator::State Navigator::TRANSLATING_ZPLUS

    State for rotation with automatic forward motion. The standard fly forward
    state. 
*/

/*! \var Navigator::State Navigator::TRANSLATING_ZMINUS

    State for rotation with automatic backwards motion. The standard fly
    backwards state. 
*/


/*! \enum OSG::Navigator::MouseButton

    Abstraction enumeration for mouse buttons, to keep the Navigator
    independent of the actual Window System.
*/

/*! \var Navigator::MouseButton Navigator::UP_MOUSE

    Mouse wheel up button. 
*/

/*! \var Navigator::MouseButton Navigator::DOWN_MOUSE

    Mouse wheel down button. 
*/


/*! \enum OSG::Navigator::Key

    Abstraction enumeration for keys, to keep the Navigator
    independent of the actual Window System.
*/



/*! \var Navigator::_rMotionFactor

    The motion factor, roughly equivalent to speed.
*/

/*! \var Navigator::_ip
    
    Temporary hit point for intersection testing.
*/

/*! \var Navigator::_dir

    Temporary ray direction for intersection testing.
*/

/*------------------------- constructors ----------------------------------*/

Navigator::Navigator() : 
    _rRotationAngle(0.04908739f),
    _rMotionFactor(1.f),
    _currentState(IDLE),
    _currentMode(TRACKBALL),
    _vp(NullFC),
    _cartN(NullFC),
    _moved(false),
    _clickCenter(true),
    _clickNoIntersect(false),
    _lastX(0),
    _lastY(0),
    _ip(0,0,0)
{
}

/*-------------------------- destructors ----------------------------------*/

Navigator::~Navigator()
{
}

/*-------------------------- Notificators ---------------------------------*/

/*! Mouse button press handler.
*/
void Navigator::buttonPress(Int16 button, Int16 x, Int16 y)
{
    _lastX = x; _lastY = y;
    _moved = false;

    switch (_currentMode)
    {
    case NONE:
        _currentState = IDLE;
        break;

    case TRACKBALL:

        switch (button)
        {
        case LEFT_MOUSE  :  _currentState = ROTATING;         
                            break;
                            
        case RIGHT_MOUSE :  _currentState = TRANSLATING_Z;    
                            break;
 
        case MIDDLE_MOUSE:  _currentState = TRANSLATING_XY;
                            getIntersectionPoint(x,y);      
                            break;

        case UP_MOUSE    :  _currentState = IDLE;
                            _trackball.translateZ(-_rMotionFactor);
                            break;

        case DOWN_MOUSE  :  _currentState = IDLE;
                            _trackball.translateZ(_rMotionFactor);
                            break;

        default:            FNOTICE(("Navigator: buttonPress, unknown button\n"));
                            break;
        }
        break;

    case FLY:

        switch (button)
        {
        case LEFT_MOUSE  :  _currentState = TRANSLATING_ZPLUS;  
                            break;
                            
        case MIDDLE_MOUSE:  _currentState = ROTATING;           
                            break;
                            
        case RIGHT_MOUSE :  _currentState = TRANSLATING_ZMINUS; 
                            break;
                            
        case UP_MOUSE    :  _currentState = IDLE;
                            _flyer.forward(-_rMotionFactor);
                            break;
                            
        case DOWN_MOUSE  :  _currentState = IDLE;
                            _flyer.forward(_rMotionFactor);
                            break;
                            
        default:            FNOTICE(("Navigator: buttonPress, unknown button\n"));
                            break;
        }
        break;

    case WALK:

        switch (button)
        {
        case LEFT_MOUSE  :  _currentState = TRANSLATING_ZPLUS;  
                            break;
                            
        case MIDDLE_MOUSE:  _currentState = ROTATING;           
                            break;
                            
        case RIGHT_MOUSE :  _currentState = TRANSLATING_ZMINUS; 
                            break;
                            
        case UP_MOUSE    :  _currentState = IDLE;
                            _walker.forward(-_rMotionFactor);
                            break;
                            
        case DOWN_MOUSE  :  _currentState = IDLE;
                            _walker.forward(_rMotionFactor);
                            break;
                            
        default:            FNOTICE(("Navigator: buttonPress, unknown button\n"));
                            break;
        }
        break;

    default: 
    
        FNOTICE(("Navigator: buttonPress, unknown mode\n"));
        break;
    }
}

/*! Mouse button release handler.
*/
void Navigator::buttonRelease(Int16 , Int16 x, Int16 y)
{
    switch (_currentMode)
    {
    case NONE:      break;

    case TRACKBALL: if (!_moved && _clickCenter)
                    {
                        IntersectAction * act  =  IntersectAction::create();
                        Line line;
                        _vp->getCamera()->calcViewRay(line, x, y, *_vp);

                        Pnt3f lp1 = line.getPosition();
                        Vec3f ld1 = line.getDirection();

                        act->setLine(line);
                        act->apply(_vp->getRoot());
                        if (act->didHit())
                        {
                            Pnt3f p1 = act->getHitPoint();
                            _trackball.setAt(p1);
                        }

                        delete act;
                    }
                    break;
        
    case FLY:       break;
    case WALK:      break;

    default:        FNOTICE(("Navigator: buttonRelease, unknown mode\n"));
                    break;
    }
    _currentState=IDLE;
}

/*! Key press handler.
*/
void Navigator::keyPress(Int16 key, Int16 , Int16 )
{
    switch (_currentMode)
    {
    case NONE:
        break;

    case TRACKBALL:

        switch (key)
        {
        case LEFT      : /*undefined*/ break;
        case RIGHT     : /*undefined*/ break;
        case FORWARDS  : _trackball.translateZ(-_rMotionFactor); break;
        case BACKWARDS : _trackball.translateZ(_rMotionFactor);  break;
        default        : FNOTICE(("Navigator: keyPress, unknown key\n"));
        }
        break;

    case FLY:       
    
        switch (key)
        {
        case LEFTROT   : _flyer.rotate(-_rRotationAngle, 0);  break;
        case RIGHTROT  : _flyer.rotate( _rRotationAngle, 0);  break;
        case LEFT      : _flyer.right( _rMotionFactor);  break;
        case RIGHT     : _flyer.right(-_rMotionFactor);  break;
        case FORWARDS  : _flyer.forward(-_rMotionFactor); break;
        case BACKWARDS : _flyer.forward( _rMotionFactor);  break;
        default        : FNOTICE(("Navigator: keyPress, unknown key\n"));
        }
        break;

    case WALK:      
    
        switch (key)
        {
        case LEFTROT   : _walker.rotate(-_rRotationAngle, 0);  break;
        case RIGHTROT  : _walker.rotate( _rRotationAngle, 0);  break;
        case LEFT      : _walker.right( _rMotionFactor);   break;
        case RIGHT     : _walker.right(-_rMotionFactor);   break;
        case FORWARDS  : _walker.forward(-_rMotionFactor); break;
        case BACKWARDS : _walker.forward( _rMotionFactor);  break;
        default        : FNOTICE(("Navigator: keyPress, unknown key\n"));
        }
        break;

    default:        
    
        FNOTICE(("Navigator: keyPress, unknown mode\n"));
        break;
    }
}

/*! Mouse motion handler.
*/
void Navigator::moveTo(Int16 x, Int16 y)
{
    _moved = true;

    Real32 width  = Real32(_vp->getPixelWidth());
    Real32 height = Real32(_vp->getPixelHeight());

    if(width <= 0 || height <= 0)
        return;

    WindowPtr par = _vp->getParent();
    Real32 winHeight;
    
    if(par != NullFC)
        winHeight = (Real32)par->getHeight();
    else
        winHeight = height;
        
    Real32 fromX = (2.0f * (_lastX - _vp->getPixelLeft())- width)/  width;
    Real32 fromY = (2.0f * (winHeight - _lastY - _vp->getPixelBottom()) 
                                - height)  / height;
    Real32 toX   = (2.0f * (x - _vp->getPixelLeft()) - width) / width;
    Real32 toY   = (2.0f * (winHeight - y - _vp->getPixelBottom()) 
                                - height)/height;
    switch (_currentMode)
    {
    case NONE:
        FNOTICE(("Navigator: moveTo NONE mode\n"));
        break;

    case TRACKBALL: 
    
        switch (_currentState)
        {
        case ROTATING      :_trackball.rotate(fromX, fromY, toX, toY);
                            break;

        case TRANSLATING_XY:{
                            Real32 distanceX = 0,distanceY = 0;
                            calcDeltas(Int16(_lastX), Int16(_lastY), x, y, 
                                       distanceX, distanceY);
                            _trackball.translateXY(distanceX, distanceY);
                            }
                            break;

        case TRANSLATING_Z: {
                            Real32 distance = osgSgn(toY-fromY)*
                                              100.f * 
                                              osgPow(osgAbs(toY-fromY),2.f);
                            _trackball.translateZ(distance * _rMotionFactor);
                            }
                            break;

        default            :;//IDLE                        
        }
        
        break;

    case FLY:
     
        {
        Real32 distanceX = -(fromX-toX);
        Real32 distanceY =  (fromY-toY);
        _flyer.rotate(distanceX, distanceY);

        switch (_currentState)
        {
        case TRANSLATING_ZPLUS:     _flyer.forward(-_rMotionFactor);
                                    break;
                                    
        case TRANSLATING_ZMINUS:    _flyer.forward(_rMotionFactor);
                                    break;
                                    
        case ROTATING:              break;
        
        default:                    ;//IDLE
        }
        }
        break;

    case WALK:
    
        {
        Real32 distanceX = -(fromX-toX);
        Real32 distanceY =  (fromY-toY);
        _walker.rotate(distanceX, distanceY);

        switch (_currentState)
        {
        case TRANSLATING_ZPLUS:     _walker.forward(-_rMotionFactor);
                                    break;
                                
        case TRANSLATING_ZMINUS:    _walker.forward(_rMotionFactor);
                                    break;
                                    
        case ROTATING:              break;
        
        default:                    ;//IDLE
        }
        }
        break;

    default: 

        FNOTICE(("Navigator: moveTo, unknown mode\n"));
        break;
    }
    _lastX = x;
    _lastY = y;
}

/*! Performs some idle operations, depending on the current navigation mode
 */
void Navigator::idle(Int16 buttons, Int16 x, Int16 y)
{
    switch (_currentMode)
    {
        case NONE:
        case TRACKBALL:
                        break;
        case FLY:
        case WALK:
                        if (buttons)
                            moveTo(x,y);
                        break;
    }
}

/*! Updates the camera transformation matrix directly in the node specified as
    the cart.
*/
void Navigator::updateCameraTransformation()
{
    theMatrix.setIdentity();
    if(_cartN != NullFC && _cartN->getParent() != NullFC)
    {
        _cartN->getParent()->getToWorld(theMatrix);
        theMatrix.inverse(theMatrix);
    }

    switch(_currentMode)
    {
    case NONE:      theMatrix.mult(_NoneMatrix);            break;
    case TRACKBALL: theMatrix.mult(_trackball.getMatrix()); break;
    case FLY:       theMatrix.mult(_flyer    .getMatrix()); break;
    case WALK:      theMatrix.mult(_walker   .getMatrix()); break;
    default:        FNOTICE(("Navigator: updateCamTrans, unknown mode\n"));
                    break;
    }

    if(_cartN != NullFC)
    {
        TransformPtr t = cast_dynamic<TransformPtr>(_cartN->getCore());
        if(t == NullFC)
        {
            FWARNING (("Navigator: updateCamTrans, core is not TransformPtr\n"));
        }
        else
        {
            t->setMatrix(theMatrix);
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
void Navigator::setMode(Navigator::Mode new_mode)
{
    if (_currentMode == new_mode) return;

    _currentMode = new_mode;
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
void Navigator::setViewport(ViewportPtr new_viewport)
{
    _vp=new_viewport;
    _walker.setGround(_vp->getRoot());
    _walker.setWorld (_vp->getRoot());
}

/*! Set the navigation parameters in case of NONE mode
*/
void Navigator::setNoneMatrix(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    bool b = MatrixLookAt(_NoneMatrix, new_at, new_at+(new_at-new_from), new_up);

    if (b) FNOTICE(("Navigator: set(.,.,.) failed\n"));
}

/*! Set the from point, i.e. the viewer position.
*/
void Navigator::setFrom(Pnt3f new_from)
{
    switch (_currentMode)
    {
    case NONE:
        setNoneMatrix( new_from,
                      (Pnt3f)(_NoneMatrix[3]-_NoneMatrix[2]),
                      (Vec3f) _NoneMatrix[1] );
        break;
    case TRACKBALL:     _trackball.setFrom(new_from);   break;
    case FLY:           _flyer    .setFrom(new_from);   break;
    case WALK:          _walker   .setFrom(new_from);   break;
    default:            FNOTICE(("Navigator: setFrom, unknown mode"));
                        break;
    }
}

/*! Set the at point, i.e. the target position for the viewer.
*/
void Navigator::setAt(Pnt3f new_at)
{
    switch (_currentMode)
    {
    case NONE:
        setNoneMatrix((Pnt3f)_NoneMatrix[3], new_at, (Vec3f)_NoneMatrix[1]);
        break;
    case TRACKBALL:     _trackball.setAt(new_at);   break;
    case FLY:           _flyer    .setAt(new_at);   break;
    case WALK:          _walker   .setAt(new_at);   break;
    default:            FNOTICE(("Navigator: setAt, unknown mode"));
                        break;
    }
}

/*! Set the distance from the target position.
*/
void Navigator::setDistance(Real32 new_distance)
{
    switch (_currentMode)
    {
    case NONE:          break;

    case TRACKBALL:     _trackball.setDistance(new_distance);
                        break;
                        
    case FLY:           _flyer.forward(new_distance);
                        break;
                        
    case WALK:          _walker.forward(new_distance);
                        break;
                                
    default:            FNOTICE(("Navigator: setDistance, unknown mode"));
                        break;
    }
}


/*! Set the up vector, i.e. the vertical direction on screen.
*/
void Navigator::setUp(Vec3f new_up)
{
    switch (_currentMode)
    {
    case NONE:
        setNoneMatrix((Pnt3f) _NoneMatrix[3],
                      (Pnt3f)(_NoneMatrix[3]-_NoneMatrix[2]),
                       new_up );
        break;

    case TRACKBALL:     _trackball.setUp(new_up);
                        break;
                        
    case FLY:           _flyer.setUp(new_up);
                        break;
                        
    case WALK:          _walker.setUp(new_up);
                        break;        

    default:            FNOTICE(("Navigator: setUp, unknown mode"));
                        break;
    }
}

/*! Set the full navigator parameters.
*/
void Navigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    switch (_currentMode)
    {
    case NONE:          setNoneMatrix(new_from, new_at, new_up);
                        break;

    case TRACKBALL:     _trackball.set(new_from, new_at, new_up);
                        break;
                        
    case FLY:           _flyer.set(new_from, new_at, new_up);
                        break;
                        
    case WALK:          _walker.set(new_from, new_at, new_up);
                        break; 
           
    default:            FNOTICE(("Navigator: set, unknown mode"));
                        break;
    }
}

/*! Set the full navigator parameters from a matrix.
*/
void Navigator::set(const Matrix & new_matrix)
{
    switch (_currentMode)
    {
    case NONE:          //setNoneMatrix((Pnt3f) new_matrix[3],
                        //              (Pnt3f)(new_matrix[3]-new_matrix[2]),
                        //              (Vec3f) new_matrix[1]);
                        _NoneMatrix = new_matrix;
                        break;

    case TRACKBALL:     _trackball.set(new_matrix);
                        break;
                        
    case FLY:           _flyer.set(new_matrix);
                        break;
                        
    case WALK:          _walker.set(new_matrix);
                        break;        
                        
    default:            FNOTICE(("Navigator: set(Matrix), unknown mode"));
                        break;
    }
}


/*! Set the camera transformation node.
*/
void Navigator::setCameraTransformation(const NodePtr & new_cartn)
{
    if (new_cartn == NullFC)
    {
        FWARNING (("Set _cartN in Navigator to NullFC\n"));
    }

    _cartN = new_cartn;
}

/*------------------------------ get --------------------------------------*/

/*! Get the transformation matrix.
*/
const Matrix &Navigator::getMatrix()
{
    switch (_currentMode)
    {
    case NONE:      return _NoneMatrix;
    case TRACKBALL: return _trackball.getMatrix();
    case FLY:       return _flyer    .getMatrix();
    case WALK:      return _walker   .getMatrix();        
    default:        FNOTICE(("Navigator: getMatrix, unknown mode"));
                    break;
    }

    return Matrix::identity();
}

/*! Get the from point, i.e. the viewer position.
*/
const Pnt3f  &Navigator::getFrom()
{
    static Pnt3f returnValue(0.f, 0.f, 0.f);
    returnValue = (Pnt3f)_NoneMatrix[3];

    switch (_currentMode)
    {
    case NONE:      return returnValue;
    case TRACKBALL: return _trackball.getFrom();
    case FLY:       return _flyer    .getFrom();
    case WALK:      return _walker   .getFrom();
    default:        FNOTICE(("Navigator: getFrom, unknown mode"));
                    break;
    }

    return returnValue;
}

/*! Get the at point, i.e. the target position.
*/
const Pnt3f  &Navigator::getAt()
{
    static Pnt3f returnValue(0.f, 0.f, 0.f);
    returnValue = (Pnt3f)(_NoneMatrix[3] - _NoneMatrix[2]);

    switch (_currentMode)
    {
    case NONE:      return returnValue;
    case TRACKBALL: return _trackball.getAt();
    case FLY:       return _flyer    .getAt();
    case WALK:      return _walker   .getAt();
    default:        FNOTICE(("Navigator: getAt, unknown mode"));
                    break;
    }

    return returnValue;
}

/*! Get the up vector.
*/
const Vec3f  &Navigator::getUp()
{
    static Vec3f returnValue(0.f, 0.f, 0.f);
    returnValue = (Vec3f)_NoneMatrix[1];

    switch (_currentMode)
    {
    case NONE:      return returnValue;
    case TRACKBALL: return _trackball.getUp();
    case FLY:       return _flyer    .getUp();
    case WALK:      return _walker   .getUp();
    default:        FNOTICE(("NavigUpor: getUp, unknown mode"));
                    break;
    }

    return returnValue;
}


/*! Get the distance from the target position.
*/
Real32 Navigator::getDistance()
{
    Real32 distance = 0.0f;
    switch (_currentMode)
    {
    case NONE:          break;

    case TRACKBALL:     distance = _trackball.getDistance();
                        break;
                        
    case FLY:           break;
                        
    case WALK:          break;
                                
    default:            FNOTICE(("Navigator: setDistance, unknown mode"));
                        break;
    }

    return distance;
}

/*! Get the navigator's current state.
*/
Navigator::State Navigator::getState()
{
    return _currentState;
}

/*! Get the navigator's current mode.
*/
Navigator::Mode Navigator::getMode()
{
    return _currentMode;
}

/*! Get the navigator's rotation angle.
*/
Real32 Navigator::getRotationAngle()
{
    return _rRotationAngle;
}

/*! Get the navigator's motion factor
*/
Real32 Navigator::getMotionFactor()
{
    return _rMotionFactor;
}

/*! Set the clickCenter current state.
*/
bool Navigator::setClickCenter(bool state)
{
    bool old = _clickCenter;

    _clickCenter = state;
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

/*! Calculates the transformation matrix from CC to WC using the actual view
    matrix.
*/
static void calcCCtoWCMatrix(Matrix &cctowc, const Matrix &view,
                             const ViewportPtr port)
{
    Matrix proj, projtrans;

    port->getCamera()->getProjection( proj, port->getPixelWidth(),
                                            port->getPixelHeight());
    port->getCamera()->getProjectionTranslation( projtrans,
                                                 port->getPixelWidth(),
                                                 port->getPixelHeight());

    Matrix wctocc = proj;
    wctocc.mult( projtrans );
    wctocc.mult( view );

    cctowc.invertFrom( wctocc );
}

/*! Calculates the intersection point of a ray that starts at from and goes
    through the position on the screen given by x,y with the world, if no
    intersection point exists the intersection is set to (0,0,0)
*/
void Navigator::getIntersectionPoint(Int16 x, Int16 y)
{
    IntersectAction * act = IntersectAction::create();
    Line line;
    
    _vp->getCamera()->calcViewRay(line, x, y, *_vp);
    
    if(_clickNoIntersect)
    {
        Real32 u = (_dir.dot(Pnt3f(0.0f, 0.0f, 0.0f) - line.getPosition())) /
                   (_dir.dot(line.getDirection()));
        _ip = line.getPosition() + u * line.getDirection();
        return;
    }

    act->setLine(line);
    act->apply(_vp->getRoot());

    Matrix cctowc,view;
    Int16 width  = _vp->getPixelWidth();
    Int16 height = _vp->getPixelHeight();

    _vp->getCamera()->getViewing(view, width, height);

    calcCCtoWCMatrix(cctowc, view, _vp);

    Pnt3f at,to;

    cctowc.multFullMatrixPnt( Pnt3f( 0, 0, 0.5f ), to );
    cctowc.multFullMatrixPnt( Pnt3f( 0, 0, 1    ), at );

    _dir = to - at;

    if (act->didHit())
    {
        _ip = act->getHitPoint();
    }
    else
    {
        Real32 u = (_dir.dot(Pnt3f(0.0f, 0.0f, 0.0f) - line.getPosition())) /
                   (_dir.dot(line.getDirection()));
        _ip = line.getPosition() + u * line.getDirection();
    }

    delete act;
}

/*! Calculate the real translation that has to be done, so that the
    trackball can actually drag the object in the plane parallel to the
    screen.
*/
void Navigator::calcDeltas(Int16 , Int16 , Int16 toX, Int16 toY,
                           Real32 &distanceX, Real32 &distanceY)
{
    Matrix view;

    view=_trackball.getMatrix();

    Pnt3f from( view[3][0], view[3][1], view[3][2] );

    view.invert();
    Matrix cctowc;
    calcCCtoWCMatrix(cctowc, view, _vp);

    Real32  rx = ( toX / (Real32) _vp->getPixelWidth() ) * 2.f - 1.f,
            ry = 1.f - ( toY / (Real32) _vp->getPixelHeight() ) * 2.f;

    Pnt3f at;
    cctowc.multFullMatrixPnt( Pnt3f( rx, ry, 1 ), at );

    Line line2;
    line2.setValue(from, at-from);

    Real32 u = (_dir.dot(_ip-line2.getPosition())) /
               (_dir.dot(line2.getDirection()));

    Pnt3f p2 = line2.getPosition() + u * line2.getDirection();

    Vec3f transl;
    transl[0] = -p2[0] + _ip[0];
    transl[1] = -p2[1] + _ip[1];
    transl[2] = -p2[2] + _ip[2];

    view.multMatrixVec(transl);

    distanceX = transl[0];
    distanceY = transl[1];
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: ";
    static Char8 cvsid_hpp       [] = OSGNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGNAVIGATOR_HEADER_CVSID;
}
