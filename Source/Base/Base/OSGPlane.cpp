/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "math.h"

#include "OSGConfig.h"

#include <assert.h>

#include "OSGPlane.h"
#include "OSGLine.h"
#include "OSGMatrix.h"

OSG_USING_NAMESPACE

/*! \class OSG::Plane

    Oriented plane in 3D space defined by normal and distance.

    The plane is defined by a plane normal and a distance from the
    origin along that normal. Planes may be used to represent either 
    planes or half-spaces. In the latter case (as for the isInHalfSpace() 
    method), the half-space is defined to be all points on the plane or on
    the side of the plane in the direction of the plane normal.

    The 4 coefficients of the plane equation of an Plane can be
    obtained easily as the 3 coordinates of the plane normal and the
    distance, in that order. The normal is normalized.

    Note: Plane is all p such that normalVec . p - distance = 0

    \dev 

    Internally the plane keeps an additional OSG::Plane::_index, which is used
    to speed up volume checks.

    \enddev
*/


/*-------------------------- constructor ----------------------------------*/

Plane::Plane(void) : 
    _normalVec      (0.f, 0.f, 0.f), 
    _distance       (0.f          ),
    _directionIndex (0)
{
}


Plane::Plane(const Plane &obj) : 
    _normalVec      (obj._normalVec     ), 
    _distance       (obj._distance      ),
    _directionIndex (obj._directionIndex)
{
    updateDirectionIndex();
}


/*! Construct a plane given 3 points.
    Orientation is computed by taking (p1 - p0) x (p2 - p0) and
    pointing the normal in that direction.
 */

Plane::Plane(const Pnt3r &p0, 
             const Pnt3r &p1, 
             const Pnt3r &p2) :
    _normalVec(0.f, 0.f, 0.f),
    _distance (          0.f)
{
    Vec3r vec2(p2 - p0);

    _normalVec = p1 - p0;

    _normalVec.crossThis(vec2);
    _normalVec.normalize();
    
    _distance = _normalVec.dot(p0);

    updateDirectionIndex();
}


Plane::Plane(const Vec3r &normal, Real distance) : 
    _normalVec(normal  ), 
    _distance (distance)
{
    _normalVec.normalize();

    updateDirectionIndex();
}


Plane::Plane(const Vec3r &normal, const Pnt3r &point) :
    _normalVec(normal)
{
    _normalVec.normalize();

    _distance = _normalVec.dot(point);

    updateDirectionIndex();
}

/*--------------------------- destructor ----------------------------------*/

Plane::~Plane(void)
{
}


/*! Add offset to distance.
 */

void Plane::offset(Real d)
{
    _distance += d;
}

/*-------------------------- intersection ---------------------------------*/

/*! Intersect plane and plane, returning true if there is an intersection
    false if planes are parallel taken from Steve Baker's SG library, used 
    with permission. Algorithm explanation can be found at 
    http://geometryalgorithms.com/Archive/algorithm_0104/algorithm_0104.htm
 */

bool Plane::intersect(const Plane &pl, Line &is) const
{
    Vec3r dir = _normalVec.cross(pl.getNormal());
    Pnt3r pnt;

    Real len = dir.length();

    if(len < Eps) 
        return false;

    /* Determine intersection point with the best suited coordinate plane. */

    Real   abs;
    Real   maxabs = osgabs(dir[0]);
    UInt16 index  = 0;

    if((abs = osgabs(dir[1])) > maxabs) 
    { 
        maxabs = abs;
        index  = 1; 
    }

    if((abs = osgabs(dir[2])) > maxabs)
    {
        maxabs = abs; 
        index  = 2;
    }

    switch(index)
    {
        case 0: 
            pnt.setValues(
                0.f,
                (pl.getNormal            ()[2] * _distance     - 
                 pl.getDistanceFromOrigin()    * _normalVec[2]) / dir[0],
                (pl.getDistanceFromOrigin()    * _normalVec[1] -
                 pl.getNormal            ()[1] * _distance    ) / dir[0]);
            break;

        case 1:
            pnt.setValues(
                (pl.getDistanceFromOrigin()    * _normalVec[2] -
                 pl.getNormal            ()[2] * _distance    ) / dir[1],
                0.f,
                (pl.getNormal            ()[0] * _distance     -
                 pl.getDistanceFromOrigin()    * _normalVec[0]) / dir[1]);
            break;

        case 2: 
            pnt.setValues(
                (pl.getNormal            ()[1] * _distance     -
                 pl.getDistanceFromOrigin()    * _normalVec[1]) / dir[2],
                (pl.getDistanceFromOrigin()    * _normalVec[0] -
                 pl.getNormal            ()[0] * _distance)     / dir[2],
                0.f);
            break;

        default: 
            return false;  /* Impossible */
    }

    /* Normalize the direction */

    dir *= 1.f / len;

    is.setValue(pnt, dir);
    
    return true;
}

/*! Intersect line and plane, returning true if there is an intersection
    in the positive part of the line false if line is parallel to plane
 */

bool Plane::intersect(const Line &line, Pnt3r &point) const
{
    Real t;

    if(intersect(line, t) == true)
    {
        point = line.getPosition() + t * line.getDirection();

        return true;
    }
    else
    {
        return false;
    }
}

/*! Intersect line and plane, returning true if there is an intersection
    false if line is parallel to plane. t is the distance along the line.
 */

bool Plane::intersect(const Line &line, Real &t) const
{
    if(intersectInfinite(line, t) == false || t < 0.f)
    {
        return false;
    }

    return true;
}

/*! Intersect line and plane, returning true if there is an intersection
    false if line is parallel to plane. t is the distance along
    the line, which may be negative, i.e. the check is against a double
    infinite line. 
 */

bool Plane::intersectInfinite(const Line &line, Real &t) const
{
    Real a;

    a = _normalVec.dot(line.getDirection());

    if(a != 0.0f)
    {
        t = _normalVec.dot(
            Pnt3r(_normalVec * _distance) -  line.getPosition()) / a;

        return true;
    }
    else
    {
        if(_normalVec.dot(line.getPosition()) - _distance == 0.f)
        {
            t = 0.f;

            return true;
        }
    }

    return false;
}

/*! Intersect line and plane, returning true if there is an intersection
    false if line is parallel to plane
 */

bool Plane::intersectInfinite(const Line &line, Pnt3r &point) const
{
    Real t;

    if(intersectInfinite(line, t) == true)
    {
        point = line.getPosition() + t * line.getDirection();

        return true;
    }
    else
    {
        return false;
    }
}

/*! Clip Polygon, defined by count points through polyIn, at plane, 
	output is copied into polyOut; returns number of output points.
 */

int Plane::clip(Pnt3r *polyIn, Pnt3r *polyOut, int count) const
{
    Pnt3r i, s, p;
    int   j, n;
    
    n = 0;
    s = polyIn[count-1];
    
    for (j = 0; j < count; j++) {
        p = polyIn[j];
    
        if (isInHalfSpace(p)) {
            if (isInHalfSpace(s))
                polyOut[n++] = p;
            else {
                Line lp(s, p);
                if (intersectInfinite(lp, i)) {
                    polyOut[n++] = i;
                    polyOut[n++] = p;
                }
            }
        }
        else if (isInHalfSpace(s)) {
            Line ls(s, p);
            if (intersectInfinite(ls, i)) 
                polyOut[n++] = i;
        }
    
        s = p;
    }
    
    return n;
}

void Plane::transform(const Matrixr &matrix)
{
    matrix.mult(_normalVec);

    _normalVec.normalize();

    Vec3r trans;

    trans[0] = matrix[3][0];
    trans[1] = matrix[3][1];
    trans[2] = matrix[3][2];

    trans.projectTo(_normalVec);

    UInt32 uiValNorm  = getMaxIndexAbs3(_normalVec);
    UInt32 uiValPoint = getMaxIndexAbs3( trans);

    if(trans[uiValPoint] >  Eps || trans[uiValPoint] < -Eps)
    {
        if((_normalVec[uiValNorm ] < 0.f &&
             trans    [uiValPoint] < 0.f ) ||
           (_normalVec[uiValNorm ] > 0.f &&
             trans    [uiValPoint] > 0.f ))
        {
            _distance -= trans.length();
        }
        else
        {
            _distance += trans.length();
        }
    }

    updateDirectionIndex();
}

void Plane::updateDirectionIndex(void)
{
    UInt8 ind = 0;
    
    if(_normalVec[0] > 0.f)
        ind |= 0x1;
    if(_normalVec[1] > 0.f)
        ind |= 0x2;
    if(_normalVec[2] > 0.f)
        ind |= 0x4; 
    
    _directionIndex = ind;
}


OSG_BEGIN_NAMESPACE


OSG_BASE_DLLMAPPING
bool operator ==(const Plane &p1, const Plane &p2)
{
    return ((p1._distance  == p2._distance ) &&
            (p1._normalVec == p2._normalVec)   );
}

OSG_BASE_DLLMAPPING
std::ostream &operator <<(std::ostream &outStream, const Plane &obj)
{
    return outStream << obj.getNormal() << ":" << obj.getDistanceFromOrigin();
}

OSG_END_NAMESPACE

