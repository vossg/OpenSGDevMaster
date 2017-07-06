/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

OSG_BEGIN_NAMESPACE

/*---------------------  Plane and Frustums Test --------------------------*/

//
// Check to see if a point is fully behind (inside the negative halfspace of) a plane.
//
inline bool ClusterShadingStage::PointInsidePlane(
    const Pnt3f& p, 
    const Plane& plane)
{
    Real32 val = plane.getNormal().dot(p) - plane.getDistanceFromOrigin();
    return val < 0;
}

//
// Check to see if a sphere is fully behind (inside the negative halfspace of) a plane.
//
inline bool ClusterShadingStage::SphereInsidePlane(
    const Sphere& sphere, 
    const Plane&  plane)
{
    Real32 val = plane.getNormal().dot(sphere.c) - plane.getDistanceFromOrigin();
    return val < -sphere.r;
}

//
// Check to see if a cone if fully behind (inside the negative halfspace of) a plane.
//
inline bool ClusterShadingStage::ConeInsidePlane(
    const Cone&  cone, 
    const Plane& plane)
{
    // Compute the farthest point on the end of the cone to the positive space of the plane.
    Vec3f m = plane.getNormal().cross(cone.d).cross(cone.d);
    Pnt3f Q = cone.T + cone.d * cone.h - m * cone.r;

    // The cone is in the negative halfspace of the plane if both
    // the tip of the cone and the farthest point on the end of the cone to the 
    // positive halfspace of the plane are both inside the negative halfspace 
    // of the plane.
    return PointInsidePlane(cone.T, plane) && PointInsidePlane(Q, plane);
}

//
// Check to see of a point light is partially contained within the frustum.
//
inline bool ClusterShadingStage::SphereInsideFrustum(
    const Sphere&  sphere, 
    const Frustum& frustum, 
    Real32         zNear, 
    Real32         zFar)
{
    bool result = true;

    if (sphere.c.z() - sphere.r > zNear || zFar > sphere.c.z() + sphere.r)
    {
        result = false;
    }

    for (int i = 0; i < 4 && result; i++)
    {
        if (SphereInsidePlane(sphere, frustum.planes[i]))
        {
            result = false;
        }
    }

    return result;
}

inline bool ClusterShadingStage::ConeInsideFrustum(
    const Cone&    cone, 
    const Frustum& frustum, 
    Real32         zNear, 
    Real32         zFar)
{
    bool result = true;

    Plane nearPlane(Vec3f(0, 0,-1),-zNear);
    Plane farPlane (Vec3f(0, 0, 1), zFar );

    if (ConeInsidePlane(cone, nearPlane) || ConeInsidePlane(cone, farPlane))
    {
        result = false;
    }

    for (int i = 0; i < 4 && result; i++)
    {
        if (ConeInsidePlane(cone, frustum.planes[i]))
        {
            result = false;
        }
    }

    return result;
}

OSG_END_NAMESPACE
