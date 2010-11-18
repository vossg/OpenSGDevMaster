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

#include "OSGNavballEngine.h"
#include "OSGNavigator.h"
#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NavballEngine
    \ingroup GrpSystemWindowNavigators

The NavballEngine models a navigation model based on a rotating sphere,  
see \ref PageSystemWindowNavigatorsNavball for a description.

\dev 

\enddev

*/

/*! \var Real32 NavballEngine::_rRadius

    The size of the trackball, relative to the screen size. Per default it is 
    0.8.
*/

/*! \var Real32 NavballEngine::_rDistance
    
    The distance of the viewer from the target point.
*/
    
/*! \var Matrix NavballEngine::_tMatrix
    
    Temporary matrix for calculation.
*/
    
/*! \var Matrix NavballEngine::_finalMatrix

    The resulting matrix for the final transformation.
*/
    
/*! \var State NavballEngine::_currentState

    The current state of the trackball, whether it is currently rotating, 
    translating in xy or in z.
*/
    
/*! \var Pnt3f  NavballEngine::_pFrom

    The viewer position.
*/
    
/*! \var Pnt3f NavballEngine::_pAt 

    The target position.
*/
    
/*! \var Vec3f  NavballEngine::_vUp

    The Up direction.
*/

/*! \var Navigator::_ip
    
    Temporary hit point for intersection testing.
*/

/*! \var Navigator::_dir

    Temporary ray direction for intersection testing.
*/

NavballEngineTransitPtr
NavballEngine::create(Real32 rSize)
{
    return NavballEngineTransitPtr(new NavballEngine(rSize));
}

/*------------------------------ get --------------------------------------*/


/*! Get the viewer position. 
    The final matrix needs to be valid for this to work, if in doubt, call 
    updateFinalMatrix() beforehand.
*/
const Pnt3f& NavballEngine::getFrom(void)
{
    return _pFrom;
}

/*! Get the target position. 
    The final matrix needs to be valid for this to work, if in doubt, call 
    updateFinalMatrix() beforehand.
*/
const Pnt3f& NavballEngine::getAt(void)    
{
    return _pAt;
}

/*! Get the up direction. 
    The final matrix needs to be valid for this to work, if in doubt, call 
    updateFinalMatrix() beforehand.
*/
const Vec3f& NavballEngine::getUp(void)
{
    return _vUp;
}

/*! Get the current transformation matrix.
*/
const Matrix& NavballEngine::getMatrix(void)
{
    updateFinalMatrix();
    return _finalMatrix;
}

Real32 NavballEngine::getDistance(void)
{
    return _rDistance;
}

/*------------------------------ set --------------------------------------*/

/*! Sets the from point, i.e. the viewer position. 
*/
void NavballEngine::setFrom(Pnt3f new_from)
{
    set(new_from, getAt(), getUp());
}

/*! Sets the at point, the target point and center of the window.
*/
void NavballEngine::setAt(Pnt3f new_at)
{
    set(getFrom(),new_at,getUp());
}

/*! Sets the up vector.
*/
void NavballEngine::setUp(Vec3f new_up)
{
    set(getFrom(),getAt(),new_up);
}

/*! Set all viewer parameters of the navigator separately.
*/
void NavballEngine::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    bool b = MatrixLookAt(_finalMatrix, new_at, new_at+(new_at-new_from), new_up);
    if(!b)
    {
        _pFrom = new_from;
        _pAt = new_at;
        _vUp = new_up;
        _rDistance = (_pAt - _pFrom).length();
        updateFinalMatrix();
    }
    else
    {
        FNOTICE(("NavballEngine: set(.,.,.), failed")); 
    }
}

/*! Set all viewer parameters of the navigator with a single matrix.

    \note The matrix does not contain all information needed for
    the NavballNavigator, it is therefore preferable to use
    NavballNavigator::set(Pnt3f,Pnt3f,Vec3f) to set the values, especially
    when copying from one NavballNavigator to another one.
*/
void NavballEngine::set(const Matrix & new_matrix)
{
    // get distance
    Vec3f translation( new_matrix[3][0], new_matrix[3][1], new_matrix[3][2] );

    _rDistance = translation.length();

    _pFrom = Pnt3f(new_matrix[3]);
    _pAt   = Pnt3f(new_matrix[3] - (_rDistance * new_matrix[2]));
    _vUp   = Vec3f(new_matrix[1]);
    _vUp   = Vec3f(0.0f,1.0f,0.0f);
}

/*! Sets the distance from the target point in the view direction.
*/
void NavballEngine::setDistance(Real32 new_distance)
{
    _rDistance = new_distance;
    updateFinalMatrix();
}


/*--------------------  navigator engine callbacks ------------------------*/

void NavballEngine::buttonPress(Int16 button, Int16 x, Int16 y,
                                  Navigator* nav)
{
    switch (button)
    {
        case Navigator::LEFT_MOUSE  :  
            _currentState = Navigator::ROTATING;         
            break;
                            
        case Navigator::RIGHT_MOUSE :  
            _currentState = Navigator::TRANSLATING_Z;    
            break;
 
        case Navigator::MIDDLE_MOUSE:  
            _currentState = Navigator::TRANSLATING_XY;
            getIntersectionPoint(x,y, nav);      
            break;

        case Navigator::UP_MOUSE    :  
            _currentState = Navigator::IDLE;
            translateZ(-nav->getMotionFactor());
            break;

        case Navigator::DOWN_MOUSE  :  
            _currentState = Navigator::IDLE;
            translateZ(nav->getMotionFactor());
            break;

        default: 
            FNOTICE(("NavballEngine: buttonPress, unknown button\n"));
            break;
    }
}

void NavballEngine::buttonRelease(Int16, Int16 x, Int16 y, Navigator* nav)
{
   /* if (!nav->getMoved() && nav->getClickCenter())
    {
        Viewport        *vp  = nav->getViewport();   
        IntersectAction *act = IntersectAction::create();
        Line line;
        vp->getCamera()->calcViewRay(line, x, y, *vp);

        Pnt3f lp1 = line.getPosition();
        Vec3f ld1 = line.getDirection();

        act->setLine(line);
        act->apply(vp->getRoot());
        if (act->didHit())
        {
            Pnt3f p1 = act->getHitPoint();
            setAt(p1);
        }

        delete act;
    }*/
    _currentState = Navigator::IDLE;
}

void NavballEngine::keyPress(Int16 key, Int16 , Int16, Navigator* nav)
{
    switch (key)
    {
        case Navigator::LEFT:
            /*undefined*/ 
            break;
        case Navigator::RIGHT:
            /*undefined*/
            break;
        case Navigator::FORWARDS:
            translateZ(-nav->getMotionFactor());
            break;
        case Navigator::BACKWARDS:
            translateZ(nav->getMotionFactor());
            break;
        default: 
            FNOTICE(("NavballEngine: keyPress, unknown key\n"));
    }
}

void NavballEngine::moveTo(Int16 x, Int16 y, Navigator* nav)
{
    
    Real32 fromX, fromY, toX, toY;
    nav->calcFromTo(x, y, fromX, fromY, toX, toY);

    switch (_currentState)
    {
        case Navigator::ROTATING:
            rotate(fromX, fromY, toX, toY);
            break;

        case Navigator::TRANSLATING_XY:
        {
            Real32 distX = 0.0f;
            Real32 distY = 0.0f;
            Int16  lastX = nav->getLastX();
            Int16  lastY = nav->getLastY();

            calcDeltas(lastX, lastY, x, y, distX, distY, nav);
            translateXY(distX, distY);
        }
        break;

        case Navigator::TRANSLATING_Z:
        {
            Real32 distance = osgSgn(toY-fromY) * 100.f;

            distance *= osgPow(osgAbs(toY-fromY), 2.f);
            translateZ(distance * nav->getMotionFactor());
        }
        break;

        default:
            //IDLE
            break;
    }
}

void NavballEngine::idle(Int16 buttons, Int16 x, Int16 y, Navigator* nav)
{
    // nothing to do
}

/*-------------------- Navball Transformations --------------------------*/

/*! Rotate the trackball sphere for a mouse movement from \a fromX, \a fromY to 
    \a toX, \a toY.
*/
void NavballEngine::rotate(Real32 fromX, Real32 fromY, Real32 toX, Real32 toY)
{
    if(osgAbs(fromX - toX) > TypeTraits<Real32>::getDefaultEps() ||
       osgAbs(fromY - toY) > TypeTraits<Real32>::getDefaultEps()   )
    {
        
        Vec3f Up(0.0f,1.0f,0.0f);
        Vec3f Forward(_pAt - _pFrom);
        Forward.normalize();
        //Up.normalize();
        Vec3f Right = Forward.cross(Up);
        
        Quaternion YRot(_vUp,(fromX - toX)*0.8);
        Matrix YRotMat;
        YRot.getValue(YRotMat);

        Real32 XRotAngle((fromY - toY)*-0.5);
        Real32 CurAngle(osgACos(Forward.dot(Up)));
        if(CurAngle > 1.5707f)
        {
            if(osgSgn(XRotAngle) != osgSgn(CurAngle) &&
               osgAbs(3.141592f - CurAngle) < osgAbs(XRotAngle))
            {
                XRotAngle = 0.0f;
            }
        }
        else
        {
            if(osgSgn(XRotAngle) == osgSgn(CurAngle) &&
               osgAbs(CurAngle) < osgAbs(XRotAngle))
            {
                XRotAngle = 0.0f;
            }
        }
        Quaternion XRot(Right,XRotAngle);
        Matrix XRotMat;
        XRot.getValue(XRotMat);

        Pnt3f PrevFrom(_pFrom);
        Vec3f PrevForward(Forward);
        _pFrom -= _pAt.subZero();
        XRotMat.mult(_pFrom,_pFrom);
        YRotMat.mult(_pFrom,_pFrom);
        _pFrom += _pAt.subZero();
    }
}

/*! Translate in the XY plane.
*/
void NavballEngine::translateXY(Real32 distanceX, Real32 distanceY)
{
    Vec3f Up(0.0f,1.0f,0.0f);
    Vec3f Forward(_pAt - _pFrom);
    Forward.normalize();
    //Up.normalize();
    Vec3f Right = Forward.cross(Up);
    Up = Right.cross(Forward);

    Vec3f Displacement(Right*distanceX + Up*distanceY);
    _pFrom += Displacement;
    _pAt += Displacement;
}

/*! Translate along the Z-axis.
*/

void NavballEngine::translateZ(Real32 distance)
{
    Vec3f Up(_vUp);
    Vec3f Forward(_pAt - _pFrom);
    Forward.normalize();

    Vec3f Displacement(Forward*distance);
    _pFrom += Displacement;
    
    if(_pFrom.dist2(_pAt) < distance*distance)
    {
        _pAt += Displacement;
    }
}

/*------------------------- constructors ----------------------------------*/

NavballEngine::NavballEngine(Real32 rSize) : 
    Inherited(), 
    _ip(0,0,0),
    _dir(0,0,0)
{
    _finalMatrix.setIdentity();
    _pFrom.setValues(0,0,0);
    _pAt  .setValues(0,0,1);
    _vUp  .setValues(0,1,0);
    _rDistance=(_pAt-_pFrom).length();
}

/*-------------------------- destructors ----------------------------------*/

NavballEngine::~NavballEngine()
{
}

/*! Calculate the final matrix, the matrix that reflects the actual state of the 
    NavballEngine.
*/
void NavballEngine::updateFinalMatrix()
{
    MatrixLookAt(_finalMatrix,_pFrom,_pAt,_vUp);
}

static void myCalcCCtoWCMatrix(Matrix &cctowc, const Matrix &view,
                               Viewport * const port)
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
void NavballEngine::getIntersectionPoint(Int16 x, Int16 y, Navigator* nav)
{
    Viewport *vp  = nav->getViewport();
    Line line;
    
    vp->getCamera()->calcViewRay(line, x, y, *vp);
    
    if(nav->getClickNoIntersect())
    {
        Real32 u = (_dir.dot(Pnt3f(0.0f, 0.0f, 0.0f) - line.getPosition())) /
                   (_dir.dot(line.getDirection()));
        _ip = line.getPosition() + u * line.getDirection();
        return;
    }

    IntersectAction *act = IntersectAction::create();
    act->setLine(line);
    act->apply(vp->getRoot());

    Matrix cctowc,view;
    Int16 width  = vp->getPixelWidth();
    Int16 height = vp->getPixelHeight();

    vp->getCamera()->getViewing(view, width, height);

    myCalcCCtoWCMatrix(cctowc, view, vp);

    Pnt3f at,to;

    cctowc.multFull( Pnt3f( 0, 0, 0.5f ), to );
    cctowc.multFull( Pnt3f( 0, 0, 1    ), at );

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
void NavballEngine::calcDeltas(Int16 , Int16 , Int16 toX, Int16 toY,
                                 Real32 &distanceX, Real32 &distanceY,
                                 Navigator* nav)
{
    Matrix    view = getMatrix();
    Viewport *vp   = nav->getViewport();

    Pnt3f from( view[3][0], view[3][1], view[3][2] );

    view.invert();
    Matrix cctowc;
    myCalcCCtoWCMatrix(cctowc, view, vp);

    Real32 rx(0.f), ry(0.f);
    vp->getNormalizedCoordinates(rx, ry, toX, toY);

    Pnt3f at;
    cctowc.multFull( Pnt3f( rx, ry, 1 ), at );

    Line line2;
    line2.setValue(from, at-from);

    Real32 u = (_dir.dot(_ip-line2.getPosition())) /
               (_dir.dot(line2.getDirection()));

    Pnt3f p2 = line2.getPosition() + u * line2.getDirection();

    Vec3f transl;
    transl[0] = -p2[0] + _ip[0];
    transl[1] = -p2[1] + _ip[1];
    transl[2] = -p2[2] + _ip[2];

    view.mult(transl, transl);

    distanceX = transl[0];
    distanceY = transl[1];
}
