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

#include <cmath>

#include "OSGConfig.h"

#include <cassert>

#include "OSGLine.h"

#include "OSGPlane.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"
#include "OSGFrustumVolume.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Line
     A line starting at a point p and extending infinitely far into the 
     direction d. This will probably split up into multiple classes for 
     dual-inifinite and non-infinite lines
*/


/*-------------------------- constructor ----------------------------------*/

Line::Line(void) : 
    _pos(0.f, 0.f ,0.f), 
    _dir(0.f, 0.f, 0.f)
{
}


Line::Line(const Line &obj) : 
    _pos(obj._pos), 
    _dir(obj._dir)
{
}


Line::Line(const Pnt3f &p0, const Pnt3f &p1) :
    _pos(0.f, 0.f ,0.f), 
    _dir(0.f, 0.f, 0.f)
{
    setValue(p0, p1);
}


Line::Line(const Pnt3f &pos, const Vec3f &dir) :
    _pos(pos), 
    _dir(dir)
{
    _dir.normalize();
}


/*--------------------------- destructor ----------------------------------*/

Line::~Line(void)
{
}

/*---------------------------------------------------------------------------*/
/* Operators                                                                 */

Line &Line::operator =(const Line &rhs)
{
    if(this == &rhs)
        return *this;
    
    _pos = rhs._pos;
    _dir = rhs._dir;
    
    return *this;
}

bool Line::operator ==(const Line &rhs) const
{
    return (_pos == rhs._pos) && (_dir == rhs._dir);
}

/*------------------------------ feature ----------------------------------*/

void Line::setValue(const Pnt3f &p0, const Pnt3f &p1)
{
    _pos = p0;
    _dir = p1 - p0;

    _dir.normalize();
}


void Line::setValue(const Pnt3f &pos, const Vec3f &dir)
{
    _pos = pos;
    _dir = dir;
    _dir.normalize();
}

/*! Find closest points between the two lines. Return false if they are
    parallel, otherwise return true.
 */

bool Line::getClosestPoints(const Line  &line2    ,
                                  Pnt3f &ptOnThis ,
                                  Pnt3f &ptOnLine2) const
{
    // Assumes that _dir and line2._dir are valid and normalized

    Vec3f normal=_dir.cross(line2._dir);

    if(normal.isZero()) 
        return false; // Lines are parallel

    Vec3f p0p1 = line2._pos - _pos;

    Real32 lengthSqr = normal.squareLength();
    Real32 s         = p0p1.cross(line2._dir).dot(normal) / lengthSqr;
    Real32 t         = p0p1.cross(      _dir).dot(normal) / lengthSqr;

    ptOnThis  =       _pos + s *       _dir;
    ptOnLine2 = line2._pos + t * line2._dir;

    return true;
}

/*! Returns the closest point on the line to the given point.
 */

Pnt3f Line::getClosestPoint(const Pnt3f &point) const
{
    Vec3f vec(point - _pos);

    return _pos + _dir * vec.dot(_dir);
}


/*! Returns the distance of the given point to the line.
 */

Real32 Line::distance(const Pnt3f &point) const
{
    return (point - getClosestPoint(point)).length();
}


/*-------------------------- intersection ---------------------------------*/

/*! Intersect the Line with a Sphere
 */

bool Line::intersect(const SphereVolume &sphere) const
{
    Real32 ent;
    Real32 ex;

    return this->intersect(sphere, ent, ex);
}

/*! Intersect the line with a sphere, returns points of intersection
 */

bool Line::intersect(const SphereVolume &sphere,
                           Real32       &enter, 
                           Real32       &exit  ) const
{
    Vec3f v;
    Pnt3f center;

    sphere.getCenter(center);

    Real32 radius;
    Real32 h;
    Real32 b;
    Real32 d;
    Real32 t1;
    Real32 t2;

    radius = sphere.getRadius();

    v = center - _pos;

    h = (v.dot(v))-(radius * radius);
    b = (v.dot(_dir));

    if(h >= 0.f && b <= 0.f)
        return false;

    d = b * b - h;

    if(d < 0.f)
        return false;

    d  = osgSqrt(d);
    t1 = b - d;

//    if (t1 > 1)
//        return false;

    t2 = b + d;

    if( t1 < TypeTraits<Real32>::getDefaultEps() )
    {
        if( t2 < TypeTraits<Real32>::getDefaultEps() /*|| t2 > 1*/)
        {
            return false;
        }
    }

    enter = t1;
    exit  = t2;

    return true;
}

/*!Intersect the line with a cylinder
 */

bool Line::intersect(const CylinderVolume &cyl) const
{
    Real32 ent;
    Real32 ex;

    return this->intersect(cyl, ent, ex);
}

/*!Intersect the line with a cylinder, returns points of intersection
   based on GGems IV
 */

bool Line::intersect(const CylinderVolume &cyl, 
                           Real32         &enter,  
                           Real32         &exit ) const
{
    Real32  radius = cyl.getRadius();

    Vec3f adir;
    Vec3f o_adir;
    Pnt3f apos;

    cyl.getAxis(apos, adir);

    o_adir = adir;
    adir.normalize();

    bool isect;

    Real32 ln;
    Real32 dl;
    Vec3f  RC;
    Vec3f  n;
    Vec3f  D;

    RC = _pos - apos;

    n  = _dir.cross (adir);
    ln =  n  .length(    );

    if(ln == 0.f)    // IntersectionLine is parallel to CylinderAxis
    {
        D  = RC - (RC.dot(adir)) * adir;
        dl = D.length();

        if(dl <= radius)   // line lies in cylinder
        {
            enter = 0.f;
            exit  = Inf;
        }
        else
        {
            return false;
        }
    }
    else
    {
        n.normalize();

        dl    = osgAbs(RC.dot(n));        //shortest distance
        isect = (dl <= radius);

        if(isect)
        {                 // if ray hits cylinder
            Real32 t;
            Real32 s;
            Vec3f  O;

            O = RC.cross(adir);
            t = - (O.dot(n)) / ln;
            O = n.cross(adir);

            O.normalize();

            s = osgAbs (
                (osgSqrt ((radius * radius) - (dl * dl))) / (_dir.dot(O)));

            exit = t + s;

            if(exit < 0.f)
                return false;

            enter = t - s;

            if(enter < 0.f)
                enter = 0.f;
        }
        else
        {
            return false;
        }
    }

    Real32 t;

    Plane bottom(-adir, apos);

    if(bottom.intersect(*this, t))
    {
        if(bottom.isInHalfSpace(_pos))
        {
            if(t > enter) 
                enter = t;
        }
        else
        {
            if(t < exit) 
                exit = t;
        }
    }
    else
    {
        if(bottom.isInHalfSpace(_pos))
            return false;
    }
    
    Plane top(adir, apos + o_adir);

    if(top.intersect(*this, t))
    {
        if(top.isInHalfSpace(_pos))
        {
            if(t > enter)
                enter = t;
        }
        else
        {
            if(t < exit)
                exit = t;
        }
    }
    else
    {
        if(top.isInHalfSpace(_pos))
            return false;
    }

    return (enter < exit);
}

/*! Intersect the line with a frustum
 */

bool Line::intersect(const FrustumVolume &frustum) const
{
    Real32 ent;
    Real32 ex;

    return this->intersect(frustum, ent, ex);
}

/*! Intersect the line with a frustum, returns points of intersection
    based on Cyrus Beck Algorithm for clipping a line segment to a
    convex volume.
    \nohierarchy
 */
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

/*! \nohierarchy */

struct face
{
    Pnt3f point;
    Vec3f inner_vector;
    Vec3f inner_normal;
};

#endif

bool Line::intersect(const FrustumVolume &frustum ,
                           Real32        &enter   ,
                           Real32        &exit    ) const
{
    const Real32 inf = 2u << 16;

    Pnt3f enter_point = _pos + _dir * 0.f;
    Pnt3f exit_point  = _pos + _dir * inf;

    face faces[6];

    const Plane *planes = frustum.getPlanes();

    Line lines[2];

    //ln[0] - intersection of right and top planes
    planes[3].intersect(planes[4], lines[0]); 

    //ln[1] - left and bottom
    planes[2].intersect(planes[5], lines[1]); 
    
    Pnt3f pointA;
    Pnt3f pointB;

    if(!planes[0].intersectInfinite(lines[0],pointA))
        std::cout << "This should never happen (A)!!!!";
                    
    if(!planes[1].intersectInfinite(lines[1],pointB))
        std::cout << "This should never happen (B)!!!!";

    faces[0].point        = pointA; 
    faces[0].inner_vector = pointB - pointA;

    faces[1].point        = pointB; 
    faces[1].inner_vector = pointA - pointB;

    faces[2].point        = pointB; 
    faces[2].inner_vector = pointA - pointB;

    faces[3].point        = pointA; 
    faces[3].inner_vector = pointB - pointA;

    faces[4].point        = pointA; 
    faces[4].inner_vector = pointB - pointA;

    faces[5].point        = pointB; 
    faces[5].inner_vector = pointA - pointB;

    for(Int32 i = 0; i < 6; i++)
    {
        faces[i].inner_normal=planes[i].getNormal();

        if(faces[i].inner_normal.dot(faces[i].inner_vector) < 0.f)
            faces[i].inner_normal=-faces[i].inner_normal;

        Vec3f test_enp = enter_point - faces[i].point;
        Vec3f test_exp = exit_point  - faces[i].point;

        Real32 value_enp = test_enp.dot(faces[i].inner_normal);
        Real32 value_exp = test_exp.dot(faces[i].inner_normal);

        if(value_enp < 0.f && value_exp < 0.f) 
            return false;

        if(value_enp > 0.f && value_exp < 0.f) 
            planes[i].intersect(*this, exit_point );

        if(value_enp < 0.f && value_exp > 0.f) 
            planes[i].intersect(*this, enter_point);
    }
    
    Real32 a;
    
    if((a = (enter_point - _pos).dot(_dir)) != 0.f)
    {
        enter = (enter_point - _pos).dot(enter_point - _pos) / a;
    }
    else 
    {
        enter = 0.f;
    }

    if((a = (exit_point  - _pos).dot(_dir)) != 0.f)
    {
        exit  = (exit_point  - _pos).dot(exit_point  - _pos) / a;
    }
    else
    {
        enter = 0.f;              
    }

    return true;
}


/*! Intersect the line with a box, returns points of intersection
 */

bool Line::intersect(const BoxVolume &box,
                           Real32    &enter, 
                           Real32    &exit ) const
{
    Pnt3f low;
    Pnt3f high;

    box.getBounds(low, high);

    Real32 r;
    Real32 te;
    Real32 tl;

    Real32 in  = 0.f;
    Real32 out = Inf;

    if(_dir[0] > TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[0];
    
        te = (low [0] - _pos[0]) * r;
        tl = (high[0] - _pos[0]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_dir[0] < -TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[0];
    
        te = (high[0] - _pos[0]) * r;
        tl = (low [0] - _pos[0]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_pos[0] < low[0] || _pos[0] > high[0])
    {
        return false;
    }
    
    if(_dir[1] > TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[1];
    
        te = (low [1] - _pos[1]) * r;
        tl = (high[1] - _pos[1]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    
        if(in-out >= TypeTraits<Real32>::getDefaultEps())
            return false;
    }
    else if(_dir[1] < -TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[1];
    
        te = (high[1] - _pos[1]) * r;
        tl = (low [1] - _pos[1]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    
        if(in-out >= TypeTraits<Real32>::getDefaultEps())
            return false;
    }
    else if(_pos[1] < low[1] || _pos[1] > high[1])
    {
        return false;
    }
    
    if(_dir[2] > TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[2];
    
        te = (low [2] - _pos[2]) * r;
        tl = (high[2] - _pos[2]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_dir[2] < -TypeTraits<Real32>::getDefaultEps())
    {
        r = 1.f / _dir[2];
    
        te = (high[2] - _pos[2]) * r;
        tl = (low [2] - _pos[2]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_pos[2] < low[2] || _pos[2] > high[2])
    {
        return false;
    }

    enter = in;
    exit  = out;

    // Eps: count flat boxes as intersected


    // BUGFIXED, was:  

    // return enter-exit < Eps;

    // This got unstable with bbox check of huge planes
    // and if compiled as opt lib (at least with my gcc 4.0.2).
    // However it worked when compiled as dbg lib. 

    // And now something completely different...

    return in-out < TypeTraits<Real32>::getDefaultEps();

    // To get you even more confused: It also works if you leave it
    // as "enter-exit" but declare in/out as Real64.

    // Now think about it......and if it is not 42, please tell!
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! Intersect the line with a box.
 */

bool Line::intersect(      Real32     OSG_CHECK_ARG(angle),
                     const BoxVolume &OSG_CHECK_ARG(box  )) const
{
    // TODO
    assert(false);
    return false;
}

/*! Intersect the line with a point.
 */

bool Line::intersect(      Real32  OSG_CHECK_ARG(angle),
                     const Vec3f  &OSG_CHECK_ARG(point)) const
{
    // TODO
    assert(false);
    return false;
}

/*! Intersect the line with a line.
 */

bool Line::intersect(      Real32  OSG_CHECK_ARG(angle),
                     const Vec3f  &OSG_CHECK_ARG(v0   ),
                     const Vec3f  &OSG_CHECK_ARG(v1   ),
                           Vec3f  &OSG_CHECK_ARG(pt   )) const
{
    // TODO
    assert(false);
    return false;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*! Intersect the line with a triangle.
    \param [in] v0,v1,v2  Points definiting a triangle in CW orientation.
    \param [out] t  If hit, this returns the distance the hit is down the line.
    \param [in,out] norm If non-NULL, this is set to the normal at the point of
            intersection
    \returns True if there is an intersection.

    This algorithm is based on "Fast, Minimum Storage Ray/Triangle Instersection" by
    T. Moeller and B. Trumbore, with the addition of avoiding the computation of
    inv_det when no intersection happens.
 */
bool Line::intersect(const Pnt3f  &v0, 
                     const Pnt3f  &v1,
                     const Pnt3f  &v2, 
                           Real32 &t,
                           Vec3f  *norm) const
{
    // Eps (1E-6f) didn't work with very small geometries!
    static const Real32 sEps = 1E-10f;

    // find vectors for two edges sharing v0.
    Vec3f edge1 = v1 - v0;
    Vec3f edge2 = v2 - v0;

    // begin calculating determinant - also used to calculate U parameter.
    Vec3f pvec = _dir.cross(edge2);

    // if determinant is near zero, ray lies in plane of triangle.
    Real32 det = edge1.dot(pvec);

    Vec3f qvec;

    if(det > sEps)
    {
        // calculate distance from v0 to ray origin.
        Vec3f tvec = _pos - v0;

        // calculate U parameter and test bounds.
        Real32 u = tvec.dot(pvec);

        if(u < 0.f || u > det)
        {
            return false;
        }

        // prepare to test V parameter.
        qvec = tvec.cross(edge1);

        // calculate V parameter and test bounds.
        Real32 v = _dir.dot(qvec);

        if(v < 0.f || u + v > det)
        {
            return false;
        }
    }
    else if(det < -sEps)
    {
        // calculate distance from v0 to ray origin.
        Vec3f tvec = _pos - v0;

        // calculate U parameter and test bounds.
        Real32 u = tvec.dot(pvec);

        if(u > 0.f || u < det)
        {
            return false;
        }

        // prepare to test V parameter.
        qvec = tvec.cross(edge1);

        // calculate V parameter and test bounds.
        Real32 v = _dir.dot(qvec);

        if(v > 0.f || u + v < det)
        {
            return false;
        }
    }
    else
    {
        return false;  // ray is parallel to the plane of the triangle.
    }

    Real32 inv_det = 1.0f / det;

    // calculate t, ray intersects triangle.
    t = edge2.dot(qvec) * inv_det;

    if(norm != NULL)
    {
        *norm = edge1.cross(edge2);
        norm->normalize();
    }

    return true;
}

/* Check this against Peter Shirleys code:

float a = v1.x() - v2.x();
float b = v1.y() - v2.y();
float c = v1.z() - v2.z();

float d = v1.x() - v3.x();
float e = v1.y() - v3.y();
float f = v1.z() - v3.z();

float g = _d.x();
float h = _d.y();
float i = _d.z();

float j = v1.x() - _s.x();
float k = v1.y() - _s.y();
float l = v1.z() - _s.z();

float ei_hf = e*i-h*f;
float gf_di = g*f-d*i;
float dh_eg = d*h-e*g;
float ak_jb = a*k-j*b;
float jc_al = j*c-a*l;
float bl_kc = b*l-k*c;

float M = a*(ei_hf) + b*(gf_di) + c*(dh_eg);
float beta = ( j*(ei_hf)+ k*(gf_di) + l*(dh_eg) ) / M;
float gamma = ( i*(ak_jb) + h*(jc_al) + g*(bl_kc) ) / M;
float t = -( f*(ak_jb) + e*(jc_al) + d*(bl_kc) ) / M;

/// Intersects?
return (beta+gamma < 1.0f)
        && (beta > 0.0f) && (gamma > 0.0f)
        && (t >= 0.0f) && (t <= 1.0f);

*/

OSG_BASE_DLLMAPPING
std::ostream &operator <<(std::ostream &outStream, const Line &obj)
{
    return outStream << obj.getPosition() << ":" << obj.getDirection();
}

OSG_END_NAMESPACE





