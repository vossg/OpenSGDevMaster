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

OSG_USING_NAMESPACE

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


Line::Line(const Pnt3r &p0, const Pnt3r &p1) :
    _pos(0.f, 0.f ,0.f), 
    _dir(0.f, 0.f, 0.f)
{
    setValue(p0, p1);
}


Line::Line(const Pnt3r &pos, const Vec3r &dir) :
    _pos(pos), 
    _dir(dir)
{
    _dir.normalize();
}


/*--------------------------- destructor ----------------------------------*/

Line::~Line(void)
{
}

/*------------------------------ feature ----------------------------------*/

void Line::setValue(const Pnt3r &p0, const Pnt3r &p1)
{
    _pos = p0;
    _dir = p1 - p0;

    _dir.normalize();
}


void Line::setValue(const Pnt3r &pos, const Vec3r &dir)
{
    _pos = pos;
    _dir = dir;
    _dir.normalize();
}

/*! Find closest points between the two lines. Return false if they are
    parallel, otherwise return true.
 */

bool Line::getClosestPoints(const Line  &line2    ,
                                  Pnt3r &ptOnThis ,
                                  Pnt3r &ptOnLine2) const
{
    // Assumes that _dir and line2._dir are valid and normalized

    Vec3r normal=_dir.cross(line2._dir);

    if(normal.isZero()) 
        return false; // Lines are parallel

    Vec3r p0p1 = line2._pos - _pos;

    Real lengthSqr = normal.squareLength();
    Real s         = p0p1.cross(line2._dir).dot(normal) / lengthSqr;
    Real t         = p0p1.cross(      _dir).dot(normal) / lengthSqr;

    ptOnThis  =       _pos + s *       _dir;
    ptOnLine2 = line2._pos + t * line2._dir;

    return true;
}

/*! Returns the closest point on the line to the given point.
 */

Pnt3r Line::getClosestPoint(const Pnt3r &point) const
{
    Vec3r vec(point - _pos);

    return _pos + _dir * vec.dot(_dir);
}


/*! Returns the distance of the given point to the line.
 */

Real Line::distance(const Pnt3r &point) const
{
    return (point - getClosestPoint(point)).length();
}


/*-------------------------- intersection ---------------------------------*/

/*! Intersect the Line with a Sphere
 */

bool Line::intersect(const SphereVolume &sphere) const
{
    Real ent;
    Real ex;

    return this->intersect(sphere, ent, ex);
}

/*! Intersect the line with a sphere, returns points of intersection
 */

bool Line::intersect(const SphereVolume &sphere,
                           Real         &enter, 
                           Real         &exit  ) const
{
    Vec3r v;
    Pnt3r center;

    sphere.getCenter(center);

    Real radius;
    Real h;
    Real b;
    Real d;
    Real t1;
    Real t2;

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

    if( t1 < Eps )
    {
        if( t2 < Eps /*|| t2 > 1*/)
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
    Real ent;
    Real ex;

    return this->intersect(cyl, ent, ex);
}

/*!Intersect the line with a cylinder, returns points of intersection
   based on GGems IV
 */

bool Line::intersect(const CylinderVolume &cyl, 
                           Real           &enter,  
                           Real           &exit ) const
{
    Real  radius = cyl.getRadius();

    Vec3r adir;
    Vec3r o_adir;
    Pnt3r apos;

    cyl.getAxis(apos, adir);

    o_adir = adir;
    adir.normalize();

    bool isect;

    Real  ln;
    Real  dl;
    Vec3r RC;
    Vec3r n;
    Vec3r D;

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
            Real  t;
            Real  s;
            Vec3r O;

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

    Real t;

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
    Real ent;
    Real ex;

    return this->intersect(frustum, ent, ex);
}

/*! Intersect the line with a frustum, returns points of intersection
    based on Cyrus Beck Algorithm for clipping a line segment to a
    convex volume.
    \hideinhierarchy
 */
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

OSG_BEGIN_NAMESPACE

/*! \hideinhierarchy */

struct face
{
    Pnt3r point;
    Vec3r inner_vector;
    Vec3r inner_normal;
};

OSG_END_NAMESPACE

#endif

bool Line::intersect(const FrustumVolume &frustum ,
                           Real          &enter   ,
                           Real          &exit    ) const
{
    const Real inf = 2u << 16;

    Pnt3r enter_point = _pos + _dir * 0.f;
    Pnt3r exit_point  = _pos + _dir * inf;

    face faces[6];

    const Plane *planes = frustum.getPlanes();

    Line lines[2];

    //ln[0] - intersection of right and top planes
    planes[3].intersect(planes[4], lines[0]); 

    //ln[1] - left and bottom
    planes[2].intersect(planes[5], lines[1]); 
    
    Pnt3r pointA;
    Pnt3r pointB;

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

        Vec3r test_enp = enter_point - faces[i].point;
        Vec3r test_exp = exit_point  - faces[i].point;

        Real value_enp = test_enp.dot(faces[i].inner_normal);
        Real value_exp = test_exp.dot(faces[i].inner_normal);

        if(value_enp < 0.f && value_exp < 0.f) 
            return false;

        if(value_enp > 0.f && value_exp < 0.f) 
            planes[i].intersect(*this, exit_point );

        if(value_enp < 0.f && value_exp > 0.f) 
            planes[i].intersect(*this, enter_point);
    }
    
    Real a;
    
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
                           Real      &enter, 
                           Real      &exit ) const
{
    Pnt3r low;
    Pnt3r high;

    box.getBounds(low, high);

    Real r;
    Real te;
    Real tl;

    Real in  = 0.f;
    Real out = Inf;

    if(_dir[0] > Eps)
    {
        r = 1.f / _dir[0];
    
        te = (low [0] - _pos[0]) * r;
        tl = (high[0] - _pos[0]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_dir[0] < -Eps)
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
    
    if(_dir[1] > Eps)
    {
        r = 1.f / _dir[1];
    
        te = (low [1] - _pos[1]) * r;
        tl = (high[1] - _pos[1]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    
        if(in-out >= Eps)
            return false;
    }
    else if(_dir[1] < -Eps)
    {
        r = 1.f / _dir[1];
    
        te = (high[1] - _pos[1]) * r;
        tl = (low [1] - _pos[1]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    
        if(in-out >= Eps)
            return false;
    }
    else if(_pos[1] < low[1] || _pos[1] > high[1])
    {
        return false;
    }
    
    if(_dir[2] > Eps)
    {
        r = 1.f / _dir[2];
    
        te = (low [2] - _pos[2]) * r;
        tl = (high[2] - _pos[2]) * r;
    
        if(tl < out)   
            out = tl;
    
        if(te > in)    
            in  = te;
    }
    else if(_dir[2] < -Eps)
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
    return ((enter - exit) < Eps);
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! Intersect the line with a box.
 */

bool Line::intersect(      Real       OSG_CHECK_ARG(angle),
                     const BoxVolume &OSG_CHECK_ARG(box  )) const
{
    // TODO
    assert(false);
    return false;
}

/*! Intersect the line with a point.
 */

bool Line::intersect(      Real    OSG_CHECK_ARG(angle),
                     const Vec3r  &OSG_CHECK_ARG(point)) const
{
    // TODO
    assert(false);
    return false;
}

/*! Intersect the line with a line.
 */

bool Line::intersect(      Real   OSG_CHECK_ARG(angle),
                     const Vec3r &OSG_CHECK_ARG(v0   ),
                     const Vec3r &OSG_CHECK_ARG(v1   ),
                           Vec3r &OSG_CHECK_ARG(pt   )) const
{
    // TODO
    assert(false);
    return false;
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*! Intersect the line with a triangle.
 */

bool Line::intersect(const Pnt3r &v0, 
                     const Pnt3r &v1,
                     const Pnt3r &v2, 
                           Real  &t,
                           Vec3r *norm) const
{
    // Eps (1E-6f) didn't work with very small geometries!
    static const Real sEps = 1E-10f;

    // find vectors for two edges sharing v0.
    Vec3r edge1 = v1 - v0;
    Vec3r edge2 = v2 - v0;

    // begin calculating determinant - also used to calculate U parameter.
    Vec3r pvec = _dir.cross(edge2);

    // if determinant is near zero, ray lies in plane of triangle.
    Real det = edge1.dot(pvec);

    Vec3r qvec;

    if(det > sEps)
    {
        // calculate distance from v0 to ray origin.
        Vec3r tvec = _pos - v0;

        // calculate U parameter and test bounds.
        Real u = tvec.dot(pvec);

        if(u < 0.f || u > det)
        {
            return false;
        }

        // prepare to test V parameter.
        qvec = tvec.cross(edge1);

        // calculate V parameter and test bounds.
        Real v = _dir.dot(qvec);

        if(v < 0.f || u + v > det)
        {
            return false;
        }
    }
    else if(det < -sEps)
    {
        // calculate distance from v0 to ray origin.
        Vec3r tvec = _pos - v0;

        // calculate U parameter and test bounds.
        Real u = tvec.dot(pvec);

        if(u > 0.f || u < det)
        {
            return false;
        }

        // prepare to test V parameter.
        qvec = tvec.cross(edge1);

        // calculate V parameter and test bounds.
        Real v = _dir.dot(qvec);

        if(v > 0.f || u + v < det)
        {
            return false;
        }
    }
    else
    {
        return false;  // ray is parallel to the plane of the triangle.
    }

    Real inv_det = 1.0f / det;

    // calculate t, ray intersects triangle.
    t = edge2.dot(qvec) * inv_det;

    if(norm != NULL)
    {
        *norm = pvec;
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




