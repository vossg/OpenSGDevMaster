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

#include <cassert>

#include "OSGPlane.h"
#include "OSGLine.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

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
    _normal         (0.f, 0.f, 0.f), 
    _distance       (0.f          ),
    _directionIndex (0)
{
}


Plane::Plane(const Plane &obj) : 
    _normal         (obj._normal        ), 
    _distance       (obj._distance      ),
    _directionIndex (obj._directionIndex)
{
    updateDirectionIndex();
}


/*! Construct a plane given 3 points.
    Orientation is computed by taking (p1 - p0) x (p2 - p0) and
    pointing the normal in that direction.
 */

Plane::Plane(const Pnt3f &p0, 
             const Pnt3f &p1, 
             const Pnt3f &p2) :
    _normal        (0.f, 0.f, 0.f),
    _distance      (          0.f),
    _directionIndex(0            )
{
    Vec3f vec2(p2 - p0);

    _normal = p1 - p0;

    _normal.crossThis(vec2);
    _normal.normalize();
    
    _distance = _normal.dot(p0);

    updateDirectionIndex();
}

/*! Construct a plane given 3 points.
    Orientation is computed by taking either (p1 - p0) x (p2 - p0) 
    or (p2 - p0) x (p1 - p0) depending on the given vertex order
    and pointing the normal in that direction.
 */
Plane::Plane(const Pnt3f &p0, 
             const Pnt3f &p1, 
             const Pnt3f &p2,
             Polygon::VertexOrder order) :
    _normal        (0.f, 0.f, 0.f),
    _distance      (          0.f),
    _directionIndex(0            )
{
    Vec3f vec2;
    switch (order)
    {
        case Polygon::ccw:
            vec2    = p2 - p0;
            _normal = p1 - p0;
            break;
        case Polygon::cw:
            vec2    = p1 - p0;
            _normal = p2 - p0;
            break;
    }
    
    _normal.crossThis(vec2);
    _normal.normalize();
    
    _distance = _normal.dot(p0);

    updateDirectionIndex();
}
Plane::Plane(const Vec3f &normal, Real32 dist) : 
    _normal        (normal), 
    _distance      (dist  ),
    _directionIndex(0     )
    
{
    _normal.normalize();

    updateDirectionIndex();
}


Plane::Plane(const Vec3f &normal, const Pnt3f &point) :
    _normal        (normal),
    _distance      (   0.f),
    _directionIndex(0     )
{
    _normal.normalize();
    _distance = _normal.dot(point);

    updateDirectionIndex();
}

/*! This constructor initializes the Plane object by a homogenous
    plane equation represented by a Vec4f instance. The plane distance
    is therefore minus of the forth equation component.

    Plane: {q | n*(q - p) == 0, p,q,n element of R^3}
       <=> {q |  n*q + D  == 0 with D  := -n*p, D element of R}
       <=> {q | n0*q + D0 == 0 with D0 := -n0*p}
       <=> {q | n0*q - d  == 0 with d  := -D0, follows with p := d*n0}     Hesse normal form
       <=> {q | L*q'      == 0 with L  := (n0,D0) = (n0,-d) and q' := (q,1), L,q' element of R^4}
    
    Internally Plane stores and works with n0 and d not D0
 */
Plane::Plane(const Vec4f &equation) :
    _normal        ( equation   ),
    _distance      (-equation[3]),
    _directionIndex(0            )
{
    calcHessNorm();
    updateDirectionIndex();
}

/*--------------------------- destructor ----------------------------------*/

Plane::~Plane(void)
{
}


/*! Add offset to distance.
 */

void Plane::offset(Real32 d)
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
    Vec3f  dir = _normal.cross(pl.getNormal());
    Pnt3f  pnt;

    Real32 len = dir.length();

    if(len < TypeTraits<Real32>::getDefaultEps())
        return false;

    /* Determine intersection point with the best suited coordinate plane. */

    Real32 abs;
    Real32 maxabs = osgAbs(dir[0]);
    UInt16 index  = 0;

    if((abs = osgAbs(dir[1])) > maxabs) 
    { 
        maxabs = abs;
        index  = 1; 
    }

    if((abs = osgAbs(dir[2])) > maxabs)
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
                 pl.getDistanceFromOrigin()    * _normal[2]) / dir[0],
                (pl.getDistanceFromOrigin()    * _normal[1] -
                 pl.getNormal            ()[1] * _distance    ) / dir[0]);
            break;

        case 1:
            pnt.setValues(
                (pl.getDistanceFromOrigin()    * _normal[2] -
                 pl.getNormal            ()[2] * _distance    ) / dir[1],
                0.f,
                (pl.getNormal            ()[0] * _distance     -
                 pl.getDistanceFromOrigin()    * _normal[0]) / dir[1]);
            break;

        case 2: 
            pnt.setValues(
                (pl.getNormal            ()[1] * _distance     -
                 pl.getDistanceFromOrigin()    * _normal[1]) / dir[2],
                (pl.getDistanceFromOrigin()    * _normal[0] -
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

bool Plane::intersect(const Line &line, Pnt3f &point) const
{
    Real32 t;

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

bool Plane::intersect(const Line &line, Real32 &t) const
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

bool Plane::intersectInfinite(const Line &line, Real32 &t) const
{
    Real32 a;

    a = _normal.dot(line.getDirection());

    if(a != 0.0f)
    {
        t = _normal.dot(
            Pnt3f(_normal * _distance) -  line.getPosition()) / a;

        return true;
    }
    else
    {
        if(_normal.dot(line.getPosition()) - _distance == 0.f)
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

bool Plane::intersectInfinite(const Line &line, Pnt3f &point) const
{
    Real32 t;

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

/*! Intersect line segment with plane with respect to given tolerance. 
 */
bool Plane::intersect(
    const LineSegment& segment, 
    Real32&            t,
    Real32             tolerance) const
{
    Real32 a;

    a = _normal.dot(segment.getDirection());

    if(osgAbs(a) < tolerance)
    {
        t = 0.f;
        return false;
    }

    t = _normal.dot(
            Pnt3f(_normal * _distance) -  segment.getStartPoint()) / a;

    if (t < - tolerance || t > 1.f + tolerance)
    {
        t = 0.f;
        return false;
    }
    return true;
}

/*! Intersect line with plane with respect to given tolerance. The
    line does only intersect the plane in the provided interval.
 */
bool Plane::intersect(
    const LineSegment& segment, 
    Pnt3f&             intersection,
    Real32             tolerance) const
{
    Real32 t;
    if (intersect(segment, t, tolerance) == true)
    {
        intersection = segment.getPoint(t);
        return true;
    }

    return false;
}

/*! Clip Polygon, defined by count points through polyIn, at plane, 
	output is copied into polyOut; returns number of output points.
 */

int Plane::clip(Pnt3f *polyIn, Pnt3f *polyOut, int count) const
{
    Pnt3f i, s, p;
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

/*! Transform the plane. If flag ortho is true given matrix is
    expected to be orthogonal (i.e. M^-1 == M^T). If the flag is
    false the mathematical correct transposed inverve of the
    given matrix is used for transformation.
 */

void Plane::transform(const Matrix &matrix, bool ortho)
{
    // point in plane
    Pnt3f o(_normal[0] * _distance,
            _normal[1] * _distance,
            _normal[2] * _distance );
    
    matrix.multFull(o, o);

    if (ortho)
    {
        // This should use the inverse, transpose of matrix in order to work with
        // arbitrary matrices - as is matrix needs to be orthogonal
        matrix.mult(_normal, _normal);
    }
    else
    {
        Matrix F;
        matrix.inverse(F);
        F.transpose();

        F.mult(_normal, _normal);
    }

    _normal.normalize();
    _distance = _normal.dot(o);

    updateDirectionIndex();
}

/*! Transform plane equation by the given matrix. This function
    expects the given transformation matrix to be already transposed
    and inverted. I.e. it calculates the Matrix * <noraml, -distance>
    and brings the result back to Hesse normalization.
 */

void Plane::transformTransposedInverse(const Matrix &matrix)
{
    setEquation(matrix * getEquation());
    updateDirectionIndex();
}

void Plane::updateDirectionIndex(void)
{
    UInt8 ind = 0;
    
    if(_normal[0] > 0.f)
        ind |= 0x1;
    if(_normal[1] > 0.f)
        ind |= 0x2;
    if(_normal[2] > 0.f)
        ind |= 0x4; 
    
    _directionIndex = ind;
}

/*---------------------------------------------------------------------------*/
/* Assignment                                                                */

Plane &Plane::operator =(const Plane &source)
{
    if(this == &source)
        return *this;
    
    _normal         = source._normal;
    _distance       = source._distance;
    _directionIndex = source._directionIndex;
    
    updateDirectionIndex();
    
    return *this;
}


bool Plane::operator ==(const Plane &rhs) const
{
    return ((_distance  == rhs._distance ) &&
            (_normal    == rhs._normal)   );
}


OSG_BASE_DLLMAPPING
std::ostream &operator <<(std::ostream &outStream, const Plane &obj)
{
    return outStream << obj.getNormal() << ":" << obj.getDistanceFromOrigin();
}

OSG_END_NAMESPACE

