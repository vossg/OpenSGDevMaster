/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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
 * WITHOUT ANY WARRANTY; without even the impclied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
 \*--------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"
#include "OSGFrustumVolume.h"

OSG_BEGIN_NAMESPACE

// ###################################################################
// # Volume Interesect Functions #####################################
// ###################################################################

OSG_BASE_DLLMAPPING 
bool intersect(const Volume &vol1, const Volume &vol2)
{
    bool                  retCode = false;

    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol1)) != NULL)
    {
        retCode = intersect(*bv, vol2);
    }
    else if((sv = dynamic_cast<const SphereVolume   *>(&vol1)) != NULL)
    {
        retCode = intersect(*sv, vol2);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol1)) != NULL)
    {
        retCode = intersect(*cv, vol2);
    }
    else if((fv = dynamic_cast<const FrustumVolume  *>(&vol1)) != NULL)
    {
        retCode = intersect(*fv, vol2);
    }
    else
    {
        FWARNING(("intersect(Volume, Volume): Argument 1 has unhandled type.\n"));
    }

    return retCode;
}

// # Box #############################################################

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &box1, const BoxVolume &box2)
{
    bool retCode = false;

    if(box1.isEmpty() == true || box2.isEmpty() == true)
    {
        retCode = false;
    }
    else if(box1.isInfinite() == true || box2.isInfinite() == true)
    {
        retCode = true;
    }
    else
    {
        retCode =
            (box1.getMin()[0] <= box2.getMax()[0] &&
             box1.getMax()[0] >= box2.getMin()[0]   ) &&
            (box1.getMin()[1] <= box2.getMax()[1] &&
             box1.getMax()[1] >= box2.getMin()[1]   ) &&
            (box1.getMin()[2] <= box2.getMax()[2] &&
             box1.getMax()[2] >= box2.getMin()[2]   );
    }

    return retCode;
}


OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &box, const SphereVolume &sphere)
{
    // source:
    // J. Arvo. A simple method for box-sphere intersection testing.
    // In A. Glassner, editor, Graphics Gems, pp. 335-339,
    // Academic Press, Boston, MA, 1990

    bool    retCode;
   
    if(box.isEmpty() == true || sphere.isEmpty() == true)
    {
        retCode = false;
    }
    else if(box.isInfinite() == true || sphere.isInfinite() == true)
    {
        retCode = true;
    }
    else
    {
        Real  s;
        Real  d = 0.f;

        //find the square of the distance from the sphere to the box

        for(Int32 i = 0; i < 3; i++)
        {
            if(sphere.getCenter()[i] < box.getMin()[i])
            {
                s  = sphere.getCenter()[i] - box.getMin()[i];
                d += s * s;
            }
            else if(sphere.getCenter()[i] > box.getMax()[i])
            {
                s  = sphere.getCenter()[i] - box.getMax()[i];
                d += s * s;
            }
        }

        retCode = (d <= (sphere.getRadius() * sphere.getRadius()));
    }

    return retCode;
}

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &box, const CylinderVolume &cylinder)
{
    bool  retCode;
    Pnt3r apos;
    Vec3r adir;

    cylinder.getAxis(apos, adir);

    if(box.isEmpty() == true || cylinder.isEmpty() == true)
    {
        retCode = false;
    }
    else if(box.isInfinite() == true || cylinder.isInfinite() == true)
    {
        retCode = true;
    }
    else
    {
        Real  s1 = 0.f, s2 = 0.f, s3 = 0.f, s4 = 0.f, 
              d = 0.f, d1 = 0.f, d2 = 0.f;
        Pnt3r c, p, p1, p2;
        Vec3r u, u1, u2;

        // find the distance between the min and the max of the box
        //with the lower point and the upper point of the cylinder respectively

        s1 = (apos - box.getMin()).length();
        s2 = (apos - box.getMax()).length();

        s3 = (apos + adir - box.getMin()).length();
        s4 = (apos + adir - box.getMax()).length();

        //Check the minimum of the above distances

        if(s1 <= s2)
        {
            d1 = s1;
            p1 = box.getMin();
        }
        else
        {
            d1 = s2;
            p1 = box.getMax();
        }

        if(s3 <= s4)
        {
            d2 = s3;
            p2 = box.getMin();
        }
        else
        {
            d2 = s4;
            p2 = box.getMax();
        }

        //set the value of the vector corresponding to the shortest distance
        if(d1 <= d2)
        {
            d = d1;
            c = apos;
            p = p1;
        }
        else
        {
            d = d2;
            c = apos + adir;
            p = p2;
        }

        // decompose the vector in u1 and u2 which are parallel and 
        // perpendicular to the cylinder axis respectively
        u  = p - c;
        u1 = (u[0] * adir[0] + u[1] * adir[1] + u[2] * adir[2]) /
            (adir.length() * adir.length()) * adir;

        u2 = u - u1;

        if(u1.length() <= 10e-6f)
        {
            retCode = true;
        }
        else if(u2.length() <= 10e-6f)
        {
            retCode = (d <= 10e-6f);
        }
        else
        {
            retCode = (u2.length() <= cylinder.getRadius());
        }
    }

    return retCode;
}


OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &box, const FrustumVolume &frustum)
{
    Pnt3r min, max;

    box.getBounds(min, max);

    const Plane       *frust = frustum.getPlanes();

    // check each point of the box to the 6 planes

    for(Int32 i = 0; i < 6; i++)
    {
        if(frust[i].isOutHalfSpace(min, max))
            return false;
    }

    return true;
}

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &box, const Volume &vol)
{
    bool                 retCode = false;

    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        retCode = intersect(box, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume   *>(&vol)) != NULL)
    {
        retCode = intersect(box, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        retCode = intersect(box, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume  *>(&vol)) != NULL)
    {
        retCode = intersect(box, *fv);
    }
    else
    {
        FWARNING(("intersect(BoxVolume, Volume): Argument 2 has unhandled type.\n"));
    }

    return retCode;
}


// # Sphere ###########################################################

OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &sphere1, const SphereVolume &sphere2)
{
    bool retCode = false;
    Real dist    = (sphere2.getCenter() - sphere1.getCenter()).length();

    if(sphere1.isEmpty() || sphere2.isEmpty())
    {
        retCode = false;
    }
    else if(sphere1.isInfinite() || sphere2.isInfinite())
    {
        retCode = true;
    }
    else if(dist < sphere1.getRadius() + sphere2.getRadius())
    {
        // the distance between the center of the 2 spheres is bigger
        // than the sum of the 2 radiuses

        retCode = true;
    }

    return retCode;
}


OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &sphere, const CylinderVolume &cylinder)
{
    bool  retCode;
    Pnt3r apos;
    Vec3r adir;

    cylinder.getAxis(apos, adir);

    if(sphere.isEmpty() || cylinder.isEmpty())
    {
        retCode = false;
    }
    else if(sphere.isInfinite() || cylinder.isInfinite())
    {
        retCode = true;
    }
    else
    {
        Real  d = 0.f, s1 = 0.f, s2 = 0.f;
        Pnt3r c;
        Vec3r u, u1, u2;

        //get the distance between the upper and lower point of the cylinder
        // and the sphere center

        s1 = (apos        - sphere.getCenter()).length();
        s2 = (apos + adir - sphere.getCenter()).length();

#ifdef OSG_EMBEDDED
        if((s1 <= FLT_EPSILON) || (s2 <= FLT_EPSILON)) 
#else
        if((s1 <= DBL_EPSILON) || (s2 <= DBL_EPSILON)) 
#endif
        {
            return true;
        }
        //check the smallest distance and set the vector coordinate
        if(s1 <= s2)
        {
            d = s1;
            c = apos;
        }
        else
        {
            d = s2;
            c = apos + adir;
        }

        // decompose the vector in u1 and u2 which are parallel and 
        // perpendicular to the cylinder axis respectively

        u  = ((d - sphere.getRadius()) / d) * (c - sphere.getCenter());

        u1 = (u[0] * adir[0] + u[1] * adir[1] + u[2] * adir[2]) / 
             (adir.length() * adir.length()) * adir;
        u2 = u - u1;

        if(u2.length() <= 10e-6f)
        {
            retCode = (d <= sphere.getRadius());
        }
        else
        {
            retCode = (u2.length() <= cylinder.getRadius());
        }
    }

    return retCode;
}


OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &sphere, const FrustumVolume &frustum)
{
    const Plane             *frust = frustum.getPlanes();

    //check the center of the sphere with each plane of the frustum
    for(Int32 i = 0; i < 6; i++)
    {
        if(frust[i].distance(sphere.getCenter()) < -sphere.getRadius())
            return false;
    }

    return true;
}


OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &sphere, const Volume &vol)
{
    bool                 retCode = false;

    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        retCode = intersect(sphere, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume   *>(&vol)) != NULL)
    {
        retCode = intersect(sphere, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        retCode = intersect(sphere, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume  *>(&vol)) != NULL)
    {
        retCode = intersect(sphere, *fv);
    }
    else
    {
        FWARNING(("intersect(SphereVolume, Volume): Argument 2 has unhandled type.\n"));
    }

    return retCode;
}


// # Cylinder ########################################################

// http://softsurfer.com/Archive/algorithm_0106/algorithm_0106.htm#dist3D_Segment_to_Segment()
// Adapted for OpenSG by Marcus Lindblom 2005-09-06

// Copyright 2001, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            Point  = Point  Vector
//            Vector = Point - Point
//            Vector = Vector  Vector
//            Vector = Scalar * Vector
//    Line and Segment with defining points {Point P0, P1;}
//    Track with initial position and velocity vector
//            {Point P0; Vector v;}
//===================================================================

Real dist3D_Segment_to_Segment(const Pnt3r& s1p, 
                               const Vec3r& s1d,
                               const Pnt3r& s2p, 
                               const Vec3r& s2d)
{
    const float  SMALL_NUM = 1e-9f; // anything that avoids division overflow
    const Vec3r& u = s1d;
    const Vec3r& v = s2d;
          Vec3r  w = s1p - s2p;

    Real    a = u.dot(u);        // always >= 0
    Real    b = u.dot(v);
    Real    c = v.dot(v);        // always >= 0
    Real    d = u.dot(w);
    Real    e = v.dot(w);
    Real    D = a*c - b*b;       // always >= 0
    Real    sc, sN, sD = D;      // sc = sN / sD, default sD = D >= 0
    Real    tc, tN, tD = D;      // tc = tN / tD, default tD = D >= 0

    // compute the line parameters of the two closest points
    if(D < SMALL_NUM)   // the lines are almost parallel
    {
        sN = 0.0f;        // force using point P0 on segment S1
        sD = 1.0f;        // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else                 // get the closest points on the infinite lines
    {
        sN = (b*e - c*d);
        tN = (a*e - b*d);

        if(sN < 0.0f)       // sc < 0 => the s=0 edge is visible
        {
            sN = 0.0f;
            tN = e;
            tD = c;
        }
        else if (sN > sD)   // sc > 1 => the s=1 edge is visible
        {
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }

    if(tN < 0.0f)            // tc < 0 => the t=0 edge is visible
    {
        tN = 0.0f;
        // recompute sc for this edge
        if(-d < 0.0f)
        {
            sN = 0.0f;
        }
        else if(-d > a)
        {
            sN = sD;
        }
        else 
        {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD)       // tc > 1 => the t=1 edge is visible
    {
        tN = tD;
        // recompute sc for this edge

        if((-d + b) < 0.0f)
        {
            sN = 0.f;
        }
        else if ((-d + b) > a)
        {
            sN = sD;
        }
        else 
        {
            sN = (-d + b);
            sD = a;
        }
    }

    // finally do the division to get sc and tc
    sc = (osgAbs(sN) < SMALL_NUM ? 0.0f : sN / sD);
    tc = (osgAbs(tN) < SMALL_NUM ? 0.0f : tN / tD);

    // get the difference of the two closest points
    Vec3r dP = w + (sc * u) - (tc * v);  // = S1(sc) - S2(tc)

    return dP.length();   // return the squared distance
}

OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &cyl1, 
               const CylinderVolume &cyl2)
{
    Pnt3r p1, p2;
    Vec3r v1, v2;

    cyl1.getAxis(p1, v1);
    cyl2.getAxis(p2, v2);

    return 
        dist3D_Segment_to_Segment(p1, v1, p2, v2) <= 
        (cyl1.getRadius() + cyl2.getRadius());
}


OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &cylinder, const FrustumVolume &frustum)
{
    Pnt3r min, max;
    cylinder.getBounds(min, max);

    const Plane       *frust = frustum.getPlanes();

    // check each point of the box to the 6 planes

    for(Int32 i = 0; i < 6; i++)
    {
        if(frust[i].isOutHalfSpace(min, max))
            return false;
    }

    return true;
}


OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &cylinder, const Volume &vol)
{
    bool                 retCode = false;

    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        retCode = intersect(cylinder, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        retCode = intersect(cylinder, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        retCode = intersect(cylinder, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        retCode = intersect(cylinder, *fv);
    }
    else
    {
        FWARNING(("intersect(CylinderVolume, Volume): Argument 2 has unhandled type.\n"));
    }
    

    return retCode;
}


// # Frustum ########################################################

OSG_BASE_DLLMAPPING 
bool intersect(const FrustumVolume &OSG_CHECK_ARG(frustum1),
               const FrustumVolume &OSG_CHECK_ARG(frustum2))
{
    FFATAL(("intersect (frustum/frustum) is not impl.\n"));
    return false;
}

OSG_BASE_DLLMAPPING 
bool intersect(const FrustumVolume &frustum, const Volume &vol)
{
    bool                  retCode = false;

    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        retCode = intersect(frustum, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        retCode = intersect(frustum, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        retCode = intersect(frustum, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        retCode = intersect(frustum, *fv);
    }
    else
    {
        FWARNING(("intersect(FrustumVolume, Volume): Argument 2 has unhandled type.\n"));
    }

    return retCode;
}


// ###################################################################
// # Volume Extend Functions #########################################
// ###################################################################

OSG_BASE_DLLMAPPING
void extend(Volume &srcVol, const Volume &vol)
{
    BoxVolume      *bv;
    SphereVolume   *sv;
    CylinderVolume *cv;
    FrustumVolume  *fv;

    if((bv = dynamic_cast<BoxVolume *>(&srcVol)) != NULL)
    {
        extend(*bv, vol);
    }
    else if((sv = dynamic_cast<SphereVolume   *>(&srcVol)) != NULL)
    {
        extend(*sv, vol);
    }
    else if((cv = dynamic_cast<CylinderVolume *>(&srcVol)) != NULL)
    {
        extend(*cv, vol);
    }
    else if((fv = dynamic_cast<FrustumVolume  *>(&srcVol)) != NULL)
    {
        extend(*fv, vol);
    }
    else
    {
        FWARNING(("extend(Volume, Volume): Argument 1 has unhandled type.\n"));
    }
}

// # Box #############################################################

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const BoxVolume &vol)
{
    if( (!srcVol.isValid   () && !srcVol.isEmpty()) ||
          srcVol.isInfinite()                       ||
          srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            srcVol = vol;
            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.setBounds(osgMin(vol.getMin().x(), srcVol.getMin().x()),
                     osgMin(vol.getMin().y(), srcVol.getMin().y()),
                     osgMin(vol.getMin().z(), srcVol.getMin().z()),
                     osgMax(vol.getMax().x(), srcVol.getMax().x()),
                     osgMax(vol.getMax().y(), srcVol.getMax().y()),
                     osgMax(vol.getMax().z(), srcVol.getMax().z()));

    if(vol.isInfinite())
        srcVol.setInfinite(true);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const SphereVolume &vol)
{
    Pnt3r min, max;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            vol   .getBounds(min, max);
            srcVol.setBounds(min, max);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    vol.getBounds(min, max);

    srcVol.setBounds(osgMin(min.x(), srcVol.getMin().x()),
                     osgMin(min.y(), srcVol.getMin().y()),
                     osgMin(min.z(), srcVol.getMin().z()),
                     osgMax(max.x(), srcVol.getMax().x()),
                     osgMax(max.y(), srcVol.getMax().y()),
                     osgMax(max.z(), srcVol.getMax().z()));

    if(vol.isInfinite())
        srcVol.setInfinite(true);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const CylinderVolume &vol)
{
    Pnt3r min, max;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            vol   .getBounds(min, max);
            srcVol.setBounds(min, max);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    vol.getBounds(min, max);

    srcVol.setBounds(osgMin(min.x(), srcVol.getMin().x()),
                     osgMin(min.y(), srcVol.getMin().y()),
                     osgMin(min.z(), srcVol.getMin().z()),
                     osgMax(max.x(), srcVol.getMax().x()),
                     osgMax(max.y(), srcVol.getMax().y()),
                     osgMax(max.z(), srcVol.getMax().z()));

    if(vol.isInfinite())
        srcVol.setInfinite(true);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(      BoxVolume     &OSG_CHECK_ARG(srcVol), 
            const FrustumVolume &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (box/frustum) is not impl.\n"));
    return;
}


#ifdef __sgi
#   pragma set woff 1174, 1552
#endif

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const Volume &vol)
{
    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *fv);
    }
    else
    {
        FWARNING(("extend(BoxVolume, Volume): Argument 2 has unhandled type.\n"));
    }
}

#ifdef __sgi
#   pragma reset woff 1174, 1552
#endif

// # Sphere ###########################################################

OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const BoxVolume &vol)
{
    Pnt3r     min, max, min1, max1, c;
    Real      r;
    BoxVolume vol1;

    vol.getBounds(min, max);

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            c = Pnt3r((min.x() + max.x()) * 0.5f, 
                      (min.y() + max.y()) * 0.5f,
                      (min.z() + max.z()) * 0.5f);

            r = ((max - min).length()) / 2.f;

            srcVol.setValue(c, r);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min1, max1);

    vol1.setBounds(osgMin(min.x(), min1.x()), osgMin(min.y(), min1.y()),
                   osgMin(min.z(), min1.z()), osgMax(max.x(), max1.x()),
                   osgMax(max.y(), max1.y()), osgMax(max.z(), max1.z()));

    vol1.getBounds(min, max);

    c = Pnt3r((min.x() + max.x()) * 0.5f, 
              (min.y() + max.y()) * 0.5f,
              (min.z() + max.z()) * 0.5f);

    r = ((max - min).length()) / 2.f;

    srcVol.setValue(c, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const SphereVolume &vol)
{
    Pnt3r min, max, min1, max1, min2, max2, c;
    Real  r;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            srcVol = vol;

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min,  max );
    vol   .getBounds(min1, max1);

    min2 = Pnt3r(osgMin(min.x(), min1.x()), 
                 osgMin(min.y(), min1.y()),
                 osgMin(min.z(), min1.z()));

    max2 = Pnt3r(osgMax(max.x(), max1.x()), 
                 osgMax(max.y(), max1.y()),
                 osgMax(max.z(), max1.z()));

    c = Pnt3r((min2.x() + max2.x()) * 0.5f, 
              (min2.y() + max2.y()) * 0.5f,
              (min2.z() + max2.z()) * 0.5f);

    r = ((max2 - min2).length()) * 0.5f;

    srcVol.setValue(c, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const CylinderVolume &vol)
{
    Pnt3r min, max, min1, max1, min2, max2, c;
    Real  r;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            vol.getBounds(min, max);
            vol.getCenter(c);

            r = (min - c).length();

            srcVol.setValue(c, r);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min,  max);
    vol   .getBounds(min1, max1);

    min2 = Pnt3r(osgMin(min.x(), min1.x()), 
                 osgMin(min.y(), min1.y()),
                 osgMin(min.z(), min1.z()));

    max2 = Pnt3r(osgMax(max.x(), max1.x()), 
                 osgMax(max.y(), max1.y()),
                 osgMax(max.z(), max1.z()));

    c = Pnt3r((min2.x() + max2.x()) * 0.5f, 
              (min2.y() + max2.y()) * 0.5f,
              (min2.z() + max2.z()) * 0.5f);

    r = ((max2 - min2).length()) * 0.5f;

    srcVol.setValue(c, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(      SphereVolume  &OSG_CHECK_ARG(srcVol), 
            const FrustumVolume &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (sphere/frustum) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const Volume &vol)
{
    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *fv);
    }
    else
    {
        FWARNING(("extend(SphereVolume, Volume): Argument 2 has unhandled type.\n"));
    }
}


// # Cylinder ########################################################

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const BoxVolume &vol)
{
    Pnt3r min, max, min1, max1, min2, max2, apos;
    Vec2r p;
    Vec3r adir;
    Real  r;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
    {
        return;
    }

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            vol.getBounds(min, max);

            p = Vec2r(max.x() - min.x(), max.y() - min.y());
            r = (p.length()) * 0.5f;

            adir = Vec3r(0.f, 0.f, max.z() - min.z());
            apos = Pnt3r(p.x(), p.y(), min.z());

            srcVol.setValue(apos, adir, r);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min,  max );
    vol   .getBounds(min1, max1);

    min2 = Pnt3r(osgMin(min.x(), min1.x()), 
                 osgMin(min.y(), min1.y()),
                 osgMin(min.z(), min1.z()));
    max2 = Pnt3r(osgMax(max.x(), max1.x()), 
                 osgMax(max.y(), max1.y()),
                 osgMax(max.z(), max1.z()));

    p = Vec2r(max2.x() - min2.x(), max2.y() - min2.y());
    r = (p.length()) * 0.5f;

    adir = Vec3r(0.f, 0.f, max2.z() - min2.z());
    apos = Pnt3r(p.x(), p.y(), min2.z());

    srcVol.setValue(apos, adir, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const SphereVolume &vol)
{
    Pnt3r min, max, min1, max1, min2, max2, apos;
    Vec2r p;
    Vec3r adir;
    Real r;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            r = vol.getRadius();

            apos = Pnt3r(vol.getCenter().x() - r, 
                         vol.getCenter().y() - r,
                         vol.getCenter().z() - r);
            adir = Vec3r(vol.getCenter().x() + r - apos.x(),
                         vol.getCenter().y() + r - apos.y(),
                         vol.getCenter().z() + r - apos.z());

            srcVol.setValue(apos, adir, r);

            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min,  max);
    vol   .getBounds(min1, max1);

    min2 = Pnt3r(osgMin(min.x(), min1.x()), 
                 osgMin(min.y(), min1.y()),
                 osgMin(min.z(), min1.z()));
    max2 = Pnt3r(osgMax(max.x(), max1.x()), 
                 osgMax(max.y(), max1.y()),
                 osgMax(max.z(), max1.z()));

    p = Vec2r(max2.x() - min2.x(), max2.y() - min2.y());
    r = (p.length()) * 0.5f;

    adir = Vec3r(0.f, 0.f, max2.z() - min2.z());
    apos = Pnt3r(p.x(), p.y(), min2.z());

    srcVol.setValue(apos, adir, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const CylinderVolume &vol)
{
    Pnt3r min, max, min1, max1, min2, max2, apos;
    Vec2r p;
    Vec3r adir;
    Real  r;

    if((!srcVol.isValid   () && !srcVol.isEmpty()) ||
         srcVol.isInfinite()                       ||
         srcVol.isStatic  ()                         )
    {
        return;
    }

    if(!vol.isValid())
        return;

    if(srcVol.isEmpty())
    {
        if(vol.isEmpty())
        {
            return;
        }
        else
        {
            srcVol = vol;
            return;
        }
    }
    else if(vol.isEmpty())
    {
        return;
    }

    srcVol.getBounds(min,  max);
    vol   .getBounds(min1, max1);

    min2 = Pnt3r(osgMin(min.x(), min1.x()), 
                 osgMin(min.y(), min1.y()),
                 osgMin(min.z(), min1.z()));
    max2 = Pnt3r(osgMax(max.x(), max1.x()), 
                 osgMax(max.y(), max1.y()),
                 osgMax(max.z(), max1.z()));

    p = Vec2r(max2.x() - min2.x(), max2.y() - min2.y());
    r = (p.length()) * 0.5f;

    adir = Vec3r(0.f, 0.f, max2.z() - min2.z());
    apos = Pnt3r(p.x(), p.y(), min2.z());

    srcVol.setValue(apos, adir, r);

    return;
}


OSG_BASE_DLLMAPPING 
void extend(      CylinderVolume &OSG_CHECK_ARG(srcVol),
            const FrustumVolume  &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (cylinder/frustum) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const Volume &vol)
{
    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *fv);
    }
    else
    {
        FWARNING(("extend(CylinderVolume, Volume): Argument 2 has unhandled type.\n"));
    }
}


// # Frustum ########################################################

OSG_BASE_DLLMAPPING 
void extend(      FrustumVolume &OSG_CHECK_ARG(srcVol), 
            const BoxVolume     &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (frustum/box) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(      FrustumVolume &OSG_CHECK_ARG(srcVol), 
            const SphereVolume  &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (frustum/sphere) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(      FrustumVolume  &OSG_CHECK_ARG(srcVol),
            const CylinderVolume &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (frustum/cylinder) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(      FrustumVolume &OSG_CHECK_ARG(srcVol),
            const FrustumVolume &OSG_CHECK_ARG(vol   ))
{
    FFATAL(("extend (frustum/frustum) is not impl.\n"));
    return;
}


OSG_BASE_DLLMAPPING 
void extend(      FrustumVolume &srcVol,
            const Volume        &vol    )
{
    const BoxVolume      *bv;
    const SphereVolume   *sv;
    const CylinderVolume *cv;
    const FrustumVolume  *fv;

    if((bv = dynamic_cast<const BoxVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *bv);
    }
    else if((sv = dynamic_cast<const SphereVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *sv);
    }
    else if((cv = dynamic_cast<const CylinderVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *cv);
    }
    else if((fv = dynamic_cast<const FrustumVolume *>(&vol)) != NULL)
    {
        extend(srcVol, *fv);
    }
    else
    {
        FWARNING(("extend(FrustumVolume, Volume): Argument 2 has unhandled type.\n"));
    }
}

OSG_END_NAMESPACE

