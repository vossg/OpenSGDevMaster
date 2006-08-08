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

#include "OSGWalkNavigator.h"

//#include "OSGSimpleGeometry.h"
#include "OSGNode.h"
#include "OSGNodeCore.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WalkNavigator
    \ingroup GrpSystemWindowNavigators


*/

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */

WalkNavigator::WalkNavigator(): FlyNavigator(),
    _ground(NullFC),
    _world(NullFC),
    _groundDistance(0.75),
    _wallDistance(0.1),
    _height(0.85),
    _width(0.5),
    _fatness(0.5)
{
    _act = IntersectAction::create();
}

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */

WalkNavigator::~WalkNavigator()
{
    delete _act;
}


/*------------------------------ get --------------------------------------*/


/*------------------------------ set --------------------------------------*/


void WalkNavigator::setGround(const NodePtr &new_ground)
{
    _ground=new_ground;
}

void WalkNavigator::setWorld(const NodePtr &new_world)
{
    _world=new_world;
}

void WalkNavigator::setGroundDistance(Real32 groundDistance)
{
    _groundDistance=groundDistance;
}

void WalkNavigator::setMinWallDistance (Real32 wallDistance)
{
    _wallDistance=wallDistance;
}
    
void WalkNavigator::setPersonDimensions(Real32 height,Real32 width,Real32 fatness)
{
    _height  = height;
    _width   = width;
    _fatness = fatness;
}

/*---------------------- Walker Transformations ----------------------------*/

/*! makes a rotation
 */

void WalkNavigator::rotate (Real32 deltaX, Real32 deltaY)
{
    FlyNavigator::rotate(deltaX, deltaY);
}
   
/*! "walks" forward
 */

Real32 WalkNavigator::forward(Real32 step)
{
    Vec3f lv = _rFrom - _rAt;
    lv.normalize();

    Vec3f upn = _vUp;
    upn.normalize();

    Vec3f mv = lv - upn.dot(lv)*upn;
    mv.normalize();

    //side vector symbolizes shoulders
    Vec3f sv = mv;
    sv.crossThis(upn);
    sv.normalize();

    Pnt3f rFrom = _rFrom + step*mv;
    Pnt3f rAt = _rAt + step*mv;

    Real32 dist;
    Line line(rFrom, -upn);

    //keep the walker at a constant distance from the ground
    _act->setLine(line);
    _act->apply(_ground);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist >= _height) {
            rFrom = rFrom + (_groundDistance-dist+_height)*upn;
            rAt = rAt + (_groundDistance-dist+_height)*upn;
        }
        else return 0.0f;    //can't jump so high
    }

    //finally check if the move is correct or not

    line.setValue(_rFrom, mv);
    _act->setLine(line);
    _act->apply(_world);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist <= (rFrom-_rFrom).length()+_fatness+_wallDistance)
            return 0.0;     //running against a wall
    }

    //move was ok, store new values
    _rFrom = rFrom;
    _rAt = rAt;

    return step;
}

/*! turns the viewer right or left
 */

Real32 WalkNavigator::right(Real32 step)
{
//    Int16 sign = (step >= 0) ? -1 : 1;
//    Real32 angle = 0.19634954f;
//
//    //rotate around the up vector
//    FlyNavigator::rotate(sign*angle, 0);
//    return step;

    Vec3f lv = _rFrom - _rAt;
    lv.normalize();

    Vec3f upn = _vUp;
    upn.normalize();

    Vec3f mv = lv - upn.dot(lv)*upn;
    mv.normalize();

    //side vector symbolizes shoulders
    Vec3f sv = mv;
    sv.crossThis(upn);
    sv.normalize();

    Pnt3f rFrom = _rFrom + step*sv;
    Pnt3f rAt = _rAt + step*sv;

    Real32 dist;
    Line line(rFrom, -upn);

    //keep the walker at a constant distance from the ground
    _act->setLine(line);
    _act->apply(_ground);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist >= _height) {
            rFrom = rFrom + (_groundDistance-dist+_height)*upn;
            rAt = rAt + (_groundDistance-dist+_height)*upn;
        }
        else return 0.0;    //can't jump so high
    }

    //finally check if the move is correct or not

    line.setValue(_rFrom, sv);
    _act->setLine(line);
    _act->apply(_world);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist <= (rFrom-_rFrom).length()+_fatness+_wallDistance)
            return 0.0;     //running against a wall
    }

    //move was ok, store new values
    _rFrom = rFrom;
    _rAt = rAt;
    return step;
}
