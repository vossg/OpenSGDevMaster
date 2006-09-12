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

#include "OSGFlyNavigator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FlyNavigator
    \ingroup GrpSystemWindowNavigators

The FlyNavigator models a simple flying navigation model, see \ref 
PageSystemWindowNavigatorsFly for a description.

*/

/*! \var OSG::FlyNavigator::_rFrom

    The from point, i.e. the viewer position.
*/

/*! \var OSG::FlyNavigator::_rAt

    The at point, i.e. the target position.
*/

/*! \var OSG::FlyNavigator::_vUp

    The up vector.
*/

/*! \var OSG::FlyNavigator::_tMatrix

    The transformation matrix for this navigator.
*/


/*------------------------- constructors ----------------------------------*/

FlyNavigator::FlyNavigator()
{
    _rFrom  .setValues(0,0,0);
    _rAt    .setValues(0,0,1);
    _vUp    .setValues(0,1,0);
    _tMatrix.setIdentity();
}


/*-------------------------- destructors ----------------------------------*/

FlyNavigator::~FlyNavigator()
{
}

/*------------------------------ get --------------------------------------*/

/*! Get the current transformation matrix.
*/
Matrix &FlyNavigator::getMatrix()
{
    MatrixLookAt(_tMatrix,_rFrom,_rAt,_vUp);
    return _tMatrix;
}

/*! Get the from point.
*/
Pnt3f &FlyNavigator::getFrom()
{
    return _rFrom;
}

/*! Get the at point.
*/
Pnt3f &FlyNavigator::getAt()
{
    return _rAt;
}

/*! Get the up vector.
*/
Vec3f &FlyNavigator::getUp()
{
    return _vUp;
}


/*------------------------------ set --------------------------------------*/

/*! Set the from point, the point where the viewer is (i.e the center 
    of all transformations).
*/
void FlyNavigator::setFrom(Pnt3f new_from)
{
    _rFrom=new_from;
}

/*! Sets the target point at which the viewer is looking.
*/
void FlyNavigator::setAt(Pnt3f new_At)
{
    _rAt=new_At;
}

/*! Sets the up vector, i.e. the direction that point up on the screen.
*/
void FlyNavigator::setUp(Vec3f new_up)
{
    _vUp=new_up;
}

/*! Set the position and the orientation at once.
*/
void FlyNavigator::set(Pnt3f new_from,Pnt3f new_At,Vec3f new_up)
{
    _rFrom=new_from;
    _rAt=new_At;
    _vUp=new_up;
}

/*! Set the position and the orientation at once using a matrix.
*/
void FlyNavigator::set(Matrix new_matrix)
{
    _rFrom= (Pnt3f) new_matrix[3];
    _rAt  = (Pnt3f)(new_matrix[3] - new_matrix[2]);
    _vUp  = (Vec3f) new_matrix[1];
    set(_rFrom, _rAt, _vUp);
}

/*---------------------- Flyer Transformations ----------------------------*/

/*! Rotate the viewer \a deltaX around the up axis and deltaY around the 
    left/right axis. \a deltaX and \a deltaY should be between -Pi and Pi.
*/
void FlyNavigator::rotate(Real32 deltaX, Real32 deltaY)
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

    final.mult(temp);
    final.multMatrixPnt(_rAt);

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
    final.multMatrixPnt(_rAt);
}

/*! Flies forward, i.e. translation \a step units along the view vector.
*/
Real32 FlyNavigator::forward(Real32 step)
{
    Vec3f lv;
    lv = _rFrom-_rAt;
    lv.normalize();
    lv *= (step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(lv);
    transl.multMatrixPnt(_rAt);
    transl.multMatrixPnt(_rFrom);
    return 0.0;
}

/*! Strafes to the right, i.e. translates along the side vector.
*/
Real32 FlyNavigator::right(Real32 step)
{
    Vec3f sv;
    sv = _rFrom-_rAt;
    sv.crossThis(_vUp);
    sv.normalize();
    sv *= (step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(sv);
    transl.multMatrixPnt(_rAt);
    transl.multMatrixPnt(_rFrom);
    return 0.0;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFlyNavigator.cpp,v 1.1.2.1 2005/08/12 11:24:20 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGFLYNAVIGATOR_HEADER_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFLYNAVIGATOR_HEADER_CVSID;
}
