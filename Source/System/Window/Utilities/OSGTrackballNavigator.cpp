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

#include "OSGTrackballNavigator.h"

#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TrackballNavigator
    \ingroup GrpSystemWindowNavigators

The TrackballNavigator models a navigation model based on a rotating sphere,  
see \ref PageSystemWindowNavigatorsTrackball for a description.

\dev 

\enddev

*/

/*! \var Real32 TrackballNavigator::_rRadius

    The size of the trackball, relative to the screen size. Per default it is 
    0.8.
*/

/*! \var Real32 TrackballNavigator::_rDistance
	
	The distance of the viewer from the target point.
*/
    
/*! \var Matrix TrackballNavigator::_tMatrix
	
	Temporary matrix for calculation.
*/
    
/*! \var Matrix TrackballNavigator::_finalMatrix

	The resulting matrix for the final transformation.
*/
    
/*! \var State TrackballNavigator::_currentState

	The current state of the trackball, whether it is currently rotating, 
	translating in xy or in z.
*/
    
/*! \var Pnt3f  TrackballNavigator::_pFrom

	The viewer position.
*/
    
/*! \var Pnt3f TrackballNavigator::_pAt 

	The target position.
*/
    
/*! \var Vec3f  TrackballNavigator::_vUp

	The Up direction.
*/


/*------------------------- constructors ----------------------------------*/

TrackballNavigator::TrackballNavigator(Real32 rSize): _rRadius(rSize)
{
    _finalMatrix.setIdentity();
    _tMatrix.setIdentity();
    _pFrom.setValues(0,0,0);
    _pAt  .setValues(0,0,1);
    _vUp  .setValues(0,1,0);
    _rDistance=(_pAt-_pFrom).length();
}

/*-------------------------- destructors ----------------------------------*/

TrackballNavigator::~TrackballNavigator()
{
}

/*------------------------------ get --------------------------------------*/

/*! Get the current transformation matrix.
*/
Matrix &TrackballNavigator::getMatrix()
{
    updateFinalMatrix();
    return _finalMatrix;
}

/*! Get the viewer position. 
	The final matrix needs to be valid for this to work, if in doubt, call 
	updateFinalMatrix() beforehand.
*/
Pnt3f &TrackballNavigator::getFrom()
{
    _pFrom = (Pnt3f)_finalMatrix[3];
    return _pFrom;
}

/*! Get the target position. 
	The final matrix needs to be valid for this to work, if in doubt, call 
	updateFinalMatrix() beforehand.
*/
Pnt3f &TrackballNavigator::getAt()
{
    _pAt = (Pnt3f)(_finalMatrix[3] - (_rDistance*_finalMatrix[2]));
    return _pAt;
}

/*! Get the up direction. 
	The final matrix needs to be valid for this to work, if in doubt, call 
	updateFinalMatrix() beforehand.
*/
Vec3f &TrackballNavigator::getUp()
{
    _vUp = (Vec3f)_finalMatrix[1];
    return _vUp;
}

Real32 TrackballNavigator::getDistance()
{
    return _rDistance;
}

/*------------------------------ set --------------------------------------*/


/*! Sets the from point, i.e. the viewer position. 
*/
void TrackballNavigator::setFrom(Pnt3f new_from)
{
    set(new_from, getAt(), getUp());
}

/*! Sets the at point, the target point and center of the window.
*/
void TrackballNavigator::setAt(Pnt3f new_at)
{
    set(getFrom(),new_at,getUp());
}

/*! Sets the distance from the target point in the view direction.
*/
void TrackballNavigator::setDistance(Real32 new_distance)
{
    _rDistance = new_distance;
    updateFinalMatrix();
}

/*! Sets the up vector.
*/
void TrackballNavigator::setUp(Vec3f new_up)
{
    set(getFrom(),getAt(),new_up);
}

/*! Set all viewer parameters of the navigator separately.
*/
void TrackballNavigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    bool b = MatrixLookAt(_tMatrix, new_at, new_at+(new_at-new_from), new_up);
    if(!b)
    {
        _rDistance = (new_at - new_from).length();
        updateFinalMatrix();
    }
    else
    {
        FNOTICE(("TrackballNavigator: set(.,.,.), failed")); 
	}
}

/*! Set all viewer parameters of the navigator with a single matrix.
*/
void TrackballNavigator::set(Matrix new_matrix)
{
    _pFrom = (Pnt3f) new_matrix[3];
    _pAt   = (Pnt3f)(new_matrix[3] - (_rDistance * new_matrix[2]));
    _vUp   = (Vec3f) new_matrix[1];
    set(_pFrom, _pAt, _vUp);
}

/*-------------------- Trackball Transformations --------------------------*/

/*! Rotate the trackball sphere for a mouse movement from \a fromX, \a fromY to 
    \a toX, \a toY.
*/
void TrackballNavigator::rotate(Real32 fromX, Real32 fromY, Real32 toX, Real32 toY)
{
    Quaternion qCurrVal;

    Vec3f  vAxis;
    Real32 rPhi;

    Vec3f  vP1, vP2, vDiff;

    Real32 rTmp;

    if(osgabs(fromX - toX) > Eps || osgabs(fromY - toY) > Eps)
    {
        vP1.setValues(fromX, fromY, projectToSphere(_rRadius, fromX, fromY));
        vP2.setValues(toX, toY, projectToSphere(_rRadius, toX, toY));

        vAxis = vP2;
        vAxis.crossThis(vP1);

        vDiff  = vP1;
        vDiff -= vP2;

        rTmp = osgClamp(-1.0f, vDiff.length() / (2.0f * _rRadius), 1.0f);

        rPhi = 2.0f * osgasin(rTmp);
        qCurrVal.setValueAsAxisRad(vAxis, rPhi);

        Matrix temp;
        qCurrVal.getValue(temp);

        _tMatrix.mult(temp);
    }
}

/*! Translate in the XY plane.
*/
void TrackballNavigator::translateXY(Real32 distanceX, Real32 distanceY)
{
    Matrix temp;
    temp.setIdentity();
    temp.setTranslate(distanceX,distanceY,0);
    _tMatrix.mult(temp);
}

/*! Translate along the Z-axis.
*/

void TrackballNavigator::translateZ(Real32 distance)
{
    _rDistance+=distance;
    // don't navigate beyond the at point.
    //if(_rDistance < 0.0f)
    //    _rDistance = 0.0f;
}

/*! Project a point on the virtual trackball. 
	If it is inside the sphere, map it to the sphere, if it outside map it to a 
	hyperbola.
*/
Real32 TrackballNavigator::projectToSphere(Real32 rRadius, Real32 rX, Real32 rY)
{
    Real32 d, t, z;

    d = sqrt(rX * rX + rY * rY);

    if (d < rRadius * 0.70710678118654752440f)
    {    /* Inside sphere */
        z = sqrt(rRadius * rRadius - d * d);
    }
    else
    {    /* On hyperbola */
        t = rRadius / 1.41421356237309504880f;
        z = t * t / d;
    }

    return z;
}

/*! Calculate the final matrix, the matrix that reflects the actual state of the 
    TrackballNavigator.
*/
void TrackballNavigator::updateFinalMatrix()
{
    Matrix temp;
    _finalMatrix=_tMatrix;
    temp.setIdentity();
    temp.setTranslate(0,0,_rDistance);

    _finalMatrix.mult(temp);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
}
