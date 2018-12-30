/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifdef WIN32
#pragma warning( disable : 4305 )
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGFrustumVolume.h"
#include "OSGQuaternion.h"
#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"
#include "OSGLineChunk.h"
#include "OSGGeoProperties.h"
#include "OSGSimpleLightGeometry.h"  // for DefaultMaterials
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

// The Simple Light Geometry creation functions

//
// Attention: the created geometry from these functions do not contain
//            texture coordinates.
//

/*! Creates a spot light with spot direction in +y-direction with the tip 
    of the spot at (0,0,0).

    \param[in] R is the spot range/radius of influence
    \param[in] angle is the spot half angle in radians
    \param[in] slices is the number of subdivisions in y-Dir, i.e. in spot direction
    \param[in] sides is  the number of circle subdivisions
    \return NodeTransitPtr to a newly created Node with a Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
NodeTransitPtr makeSpot(
    Real32 R,
    Real32 angle,
    UInt32 slices,
    UInt32 sides)
{
    GeometryTransitPtr pGeo = makeSpotGeo(R, angle, slices, sides);

    if(pGeo == NULL)
    {
        return NodeTransitPtr(NULL);
    }

    NodeTransitPtr node = Node::create();

    node->setCore(pGeo);

    return node;
}

/*! Creates a spot light geometry with spot direction in +y-direction with the tip 
    of the spot at (0,0,0).

    \param[in] R is the spot range/radius of influence
    \param[in] angle is the spot half angle in radians
    \param[in] slices is the number of subdivisions in y-Dir, i.e. in spot direction
    \param[in] sides is  the number of circle subdivisions
    \return GeometryTransitPtr to a newly created Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
GeometryTransitPtr makeSpotGeo(
    Real32 R,
    Real32 angle,
    UInt32 slices,
    UInt32 sides)
{
    if(R <= 0 || angle <= 0)
    {
        SWARNING << "makeSpotGeo: illegal geometric parameters R=" << R
                 << ", angle=" << angle
                 << std::endl;
        return GeometryTransitPtr(NULL);
    }

    if(! slices || ! sides)
    {
        SWARNING << "makeSpotGeo: illegal subdivision parameters slices=" << slices << ", sides="
                 << sides << std::endl;
        return GeometryTransitPtr(NULL);
    }

    GeoUInt8PropertyRefPtr   types = GeoUInt8Property::create();
    GeoUInt32PropertyRefPtr  lens  = GeoUInt32Property::create();
    GeoPnt3fPropertyRefPtr   pnts  = GeoPnt3fProperty::create();
    GeoVec3fPropertyRefPtr   norms = GeoVec3fProperty::create();

    GeoUInt8Property::StoredFieldType  *t  = types->editFieldPtr();
    GeoUInt32Property::StoredFieldType *l  = lens ->editFieldPtr();
    GeoPnt3fProperty::StoredFieldType  *p  = pnts ->editFieldPtr();
    GeoVec3fProperty::StoredFieldType  *n  = norms->editFieldPtr();

    // get even slices and sides
    if ( (slices & 1) == 1 ) 
        slices += 1;

    if ( (sides & 1) == 1 ) 
        sides += 1;

    Real32 a_cone = angle;
    Real32 h_cone = R * osgCos(a_cone);
    Real32 d_cone = h_cone / slices;

    Real32 delta_phi = 2.f * Pi / (sides-1);

    Vec3f ey(0,1,0);

    typedef std::vector<Pnt3f> VecPntsT;

    VecPntsT vecOddPnts(sides), vecEvenPnts(sides);
    VecPntsT* pvecLast = &vecOddPnts;
    VecPntsT* pvecCurr = &vecEvenPnts;

    //
    // First the cone itself
    //
    std::vector<Vec3f> vecNormals(sides);
    for (UInt32 i = 0; i < sides; ++i)
    {
        Real32 phi = i * delta_phi;

        vecNormals[i] = -Vec3f(osgCos(a_cone) * osgCos(phi), osgSin(a_cone), osgCos(a_cone) * osgSin(phi));
    }

    Pnt3f pT(0,0,0);       // tip of spot cone

    (*pvecLast)[0] = pT;

    for (UInt32 j = 1; j <= slices; ++j)
    {
        Real32 l_cone = j * d_cone;
        Real32 r_cone = l_cone * osgTan(a_cone);

        Pnt3f pR = pT + l_cone * ey;

//        Real32 d_phi = (j & 0) ?  delta_phi : delta_phi + delta_phi/2.f;

        Real32 phi = (j & 0) ?  0 : delta_phi/2.f;

        for (UInt32 i = 0; i < sides-1; ++i)
        {
            phi += delta_phi;
            (*pvecCurr)[i] = pR + r_cone * Vec3f(osgSin(phi), 0, -osgCos(phi));
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back((*pvecLast)[0]);
            n->push_back(Vec3f(0,-1,0));

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecCurr)[i]);
                n->push_back(vecNormals[i]);
            }
        }
        else
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);
                
                n->push_back(vecNormals[i]);
                n->push_back(vecNormals[i]);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    //
    // Second the sphere cap
    //
    Real32 d_alpha = a_cone / (slices-1);

    for (UInt32 j = 0; j < slices; ++j)
    {
        if (j < slices-1)
        {
            Real32 da_cone = a_cone - j * d_alpha;

            Real32 l_cone = R * osgCos(da_cone);
            Real32 r_cone = R * osgSin(da_cone);

            Pnt3f pj = pT + l_cone * ey;

            Real32 phi = (j & 0) ?  0 : delta_phi/2.f;

            for (UInt32 i = 0; i < sides-1; ++i)
            {
                phi += delta_phi;
                (*pvecCurr)[i] = pj + r_cone * Vec3f(osgSin(phi), 0, -osgCos(phi));

                Vec3f vN = (*pvecCurr)[i] - pT;
                vN.normalize();
                vecNormals[i] = vN;
            }

            (*pvecCurr)[sides-1] = (*pvecCurr)[0];

            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);
                
                n->push_back(vecNormals[i]);
                n->push_back(vecNormals[i]);
            }
        }
        else 
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back(pT + R * ey);
            n->push_back(Vec3f(0,-1,0));

            for (Int32 i = sides-1; i >= 0; --i)
            {
                p->push_back((*pvecLast)[i]);
                n->push_back(vecNormals[i]);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    GeometryTransitPtr geo = Geometry::create();

    geo->setTypes    (types);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (norms);

    geo->setMaterial(getDefaultUnlitMaterial());

    return geo;
}

/*! Creates a cinema light with spot direction in +y-direction with the tip 
    of the spot at (0,0,0).

    \param[in] a is the superellipses width
    \param[in] b is the superellipses height
    \param[in] r is the superellipses roundness parameter
    \param[in] theta is the superellipses twist parameter in radians
    \param[in] h is the cinema light range/radius of influence, i.e. the geometry extend along the y-axis
    \param[in] slices is the number of subdivisions in y-Dir, i.e. in spot direction
    \param[in] sides is  the number of circle subdivisions
    \return NodeTransitPtr to a newly created Node with a Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
NodeTransitPtr makeCinema(
    Real32 a,
    Real32 b,
    Real32 r,
    Real32 theta,
    Real32 h,
    UInt32 slices,
    UInt32 sides)
{
    GeometryTransitPtr pGeo = makeCinemaGeo(a, b, r, theta, h, slices, sides);

    if(pGeo == NULL)
    {
        return NodeTransitPtr(NULL);
    }

    NodeTransitPtr node = Node::create();

    node->setCore(pGeo);

    return node;
}

/*! Creates a cinema light geometry with spot direction in +y-direction with the tip 
    of the spot at (0,0,0).

    \param[in] a is the superellipses width
    \param[in] b is the superellipses height
    \param[in] r is the superellipses roundness parameter
    \param[in] theta is the superellipses twist parameter in radians
    \param[in] h is the cinema light range/radius of influence, i.e. the geometry extend along the y-axis
    \param[in] slices is the number of subdivisions in y-Dir, i.e. in spot direction
    \param[in] sides is  the number of circle subdivisions
    \return GeometryTransitPtr to a Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
GeometryTransitPtr makeCinemaGeo(
    Real32 a,
    Real32 b,
    Real32 r,
    Real32 theta,
    Real32 h,
    UInt32 slices,
    UInt32 sides)
{
    if(a <= 0 || b <= 0 || r <= 0 || h <= 0)
    {
        SWARNING << "makeCinemaGeo: illegal geometric parameters a=" << a
                 << ", b=" << b
                 << ", r=" << r
                 << ", h=" << h
                 << std::endl;
        return GeometryTransitPtr(NULL);
    }

    if(! slices || ! sides)
    {
        SWARNING << "makeCinemaGeo: illegal subdivision parameters slices=" << slices << ", sides="
                 << sides << std::endl;
        return GeometryTransitPtr(NULL);
    }

    GeoUInt8PropertyRefPtr   types = GeoUInt8Property::create();
    GeoUInt32PropertyRefPtr  lens  = GeoUInt32Property::create();
    GeoPnt3fPropertyRefPtr   pnts  = GeoPnt3fProperty::create();
    GeoVec3fPropertyRefPtr   norms = GeoVec3fProperty::create();

    GeoUInt8Property::StoredFieldType  *t  = types->editFieldPtr();
    GeoUInt32Property::StoredFieldType *l  = lens ->editFieldPtr();
    GeoPnt3fProperty::StoredFieldType  *p  = pnts ->editFieldPtr();
    GeoVec3fProperty::StoredFieldType  *n  = norms->editFieldPtr();

    // get even slices and sides
    if ( (slices & 1) == 1 ) 
        slices += 1;

    if ( (sides & 1) == 1 ) 
        sides += 1;

    Real32 cos_theta = osgCos(theta);
    Real32 sin_theta = osgSin(theta);

    Real32 d_body = h / slices;

    Real32 delta_phi = 2.f * Pi / (sides-1);

    Real32 two_inv_r = 2.0/r;

    Vec3f ey(0,1,0);

    typedef std::vector<Pnt3f> VecPntsT;

    VecPntsT vecOddPnts(sides), vecEvenPnts(sides);
    VecPntsT* pvecLast = &vecOddPnts;
    VecPntsT* pvecCurr = &vecEvenPnts;

    //
    // First the superellipses body itself
    //
    Pnt3f pT(0,0,0);       // tip of body

    (*pvecLast)[0] = pT;

    for (UInt32 j = 1; j <= slices; ++j)
    {
        Real32 l_body = j * d_body;

        Pnt3f pR = pT + l_body * ey;

        Real32 A = l_body * a;
        Real32 B = l_body * b;

        Real32 phi = 0.f;

        for (UInt32 i = 0; i < sides-1; ++i)
        {
            Real32 c = osgCos(phi);
            Real32 s = osgSin(phi);

            Real32 x = A * osgSgn(c) * osgPow(osgAbs(c), two_inv_r);
            Real32 z = B * osgSgn(s) * osgPow(osgAbs(s), two_inv_r);

            Pnt3f  pP = pR + Vec3f(
                                       x * cos_theta - z * sin_theta, 
                                       0,
                                       x * sin_theta + z * cos_theta
                                    );

            Real32 L = pP.subZero().length();

            if (L > h)
            {
                Vec3f v = pP.subZero();
                v.normalize();
                v *= h;
                pP = v.addToZero();
            }

            (*pvecCurr)[i] = pP;

            phi += delta_phi;
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back((*pvecLast)[0]);
            n->push_back(Vec3f(0,-1,0));

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecCurr)[i]);

                Vec3f v0;
                Vec3f v1;

                if (i < sides-1)
                {
                    v0 = (*pvecCurr)[i]   - (*pvecLast)[0];
                    v1 = (*pvecCurr)[i+1] - (*pvecLast)[0];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecCurr)[0] - (*pvecLast)[0];
                    v1 = (*pvecCurr)[1] - (*pvecLast)[0];
                }

                Vec3f v = v1.cross(v0);
                v.normalize();
                n->push_back(v);
            }
        }
        else
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);

                Vec3f v0;
                Vec3f v1;
                Vec3f v2;
                
                if (i < sides-1)
                {
                    v0 = (*pvecLast)[i+1] - (*pvecCurr)[i];
                    v1 = (*pvecLast)[i+1] - (*pvecLast)[i];
                    v2 = (*pvecCurr)[i+1] - (*pvecLast)[i+1];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecLast)[1] - (*pvecCurr)[0];
                    v1 = (*pvecLast)[1] - (*pvecLast)[0];
                    v2 = (*pvecCurr)[1] - (*pvecLast)[1];
                }

                Vec3f n0 = v1.cross(v0);
                Vec3f n1 = v2.cross(v1);

                n0.normalize();
                n1.normalize();

                n->push_back(n0);
                n->push_back(n1);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    //
    // Second the sphere cap
    //
    Real32 delta_a = a / (slices - 1);
    Real32 delta_b = b / (slices - 1);

    Pnt3f pE = pT + h * ey;

    for (Int32 j = slices-2; j >= 0; --j)
    {
        Real32 A = h * delta_a * j;
        Real32 B = h * delta_b * j;

        Real32 phi = 0.f;

        for (UInt32 i = 0; i < sides-1; ++i)
        {
            Real32 c = osgCos(phi);
            Real32 s = osgSin(phi);

            Real32 x = A * osgSgn(c) * osgPow(osgAbs(c), two_inv_r);
            Real32 z = B * osgSgn(s) * osgPow(osgAbs(s), two_inv_r);

            Pnt3f  pP = pE + Vec3f(
                                        x * cos_theta - z * sin_theta, 
                                        0,
                                        x * sin_theta + z * cos_theta
                                    );

            Real32 L = pP.subZero().length();

            if (L > h)
            {
                Vec3f v = pP.subZero();
                v.normalize();
                v *= h;
                pP = v.addToZero();
            }

            (*pvecCurr)[i] = pP;

            phi += delta_phi;
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];
        
        if (j < Int32(slices-1) && j > 0)
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);

                Vec3f v0;
                Vec3f v1;
                Vec3f v2;
                
                if (i < sides-1)
                {
                    v0 = (*pvecLast)[i+1] - (*pvecCurr)[i];
                    v1 = (*pvecLast)[i+1] - (*pvecLast)[i];
                    v2 = (*pvecCurr)[i+1] - (*pvecLast)[i+1];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecLast)[1] - (*pvecCurr)[0];
                    v1 = (*pvecLast)[1] - (*pvecLast)[0];
                    v2 = (*pvecCurr)[1] - (*pvecLast)[1];
                }

                Vec3f n0 = v1.cross(v0);
                Vec3f n1 = v2.cross(v1);

                n0.normalize();
                n1.normalize();

                n->push_back(n0);
                n->push_back(n1);
            }
        }

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back(pE);
            n->push_back(Vec3f(0,1,0));

            for (Int32 i = sides-1; i >= 0; --i)
            {
                p->push_back((*pvecCurr)[i]);

                Vec3f v0;
                Vec3f v1;

                if (i < Int32(sides-1))
                {
                    v0 = (*pvecCurr)[i]   - pE;
                    v1 = (*pvecCurr)[i+1] - pE;
                }
                else if (i == Int32(sides-1))
                {
                    v0 = (*pvecCurr)[0] - pE;
                    v1 = (*pvecCurr)[1] - pE;
                }

                Vec3f v = v1.cross(v0);
                v.normalize();
                n->push_back(v);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    GeometryTransitPtr geo = Geometry::create();

    geo->setTypes    (types);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (norms);

    geo->setMaterial(getDefaultUnlitMaterial());

    return geo;
}

/*! Creates a frustum volume

    \param[in] nlt is the near left  top    point of the frustum
    \param[in] nlb is the near left  bottom point of the frustum
    \param[in] nrt is the near right top    point of the frustum
    \param[in] nrb is the near right bottom point of the frustum
    \param[in] flt is the far  left  top    point of the frustum
    \param[in] flb is the far  left  bottom point of the frustum
    \param[in] frt is the far  right top    point of the frustum
    \param[in] frb is the far  right bottom point of the frustum
    \return NodeTransitPtr to a newly created Node with a Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
NodeTransitPtr makeFrustumVolume(
    const Pnt3f& nlt, const Pnt3f& nlb,
    const Pnt3f& nrt, const Pnt3f& nrb,
    const Pnt3f& flt, const Pnt3f& flb,
    const Pnt3f& frt, const Pnt3f& frb)
{
    GeometryTransitPtr pGeo = makeFrustumVolumeGeo(nlt, nlb, nrt, nrb, flt, flb, frt, frb);

    if(pGeo == NULL)
    {
        return NodeTransitPtr(NULL);
    }

    NodeTransitPtr node = Node::create();

    node->setCore(pGeo);

    return node;
}

/*! Creates a frustum volume geometry

    \param[in] nlt is the near left  top    point of the frustum
    \param[in] nlb is the near left  bottom point of the frustum
    \param[in] nrt is the near right top    point of the frustum
    \param[in] nrb is the near right bottom point of the frustum
    \param[in] flt is the far  left  top    point of the frustum
    \param[in] flb is the far  left  bottom point of the frustum
    \param[in] frt is the far  right top    point of the frustum
    \param[in] frb is the far  right bottom point of the frustum
    \return GeometryTransitPtr to a newly created Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
GeometryTransitPtr makeFrustumVolumeGeo(
    const Pnt3f& nlt, const Pnt3f& nlb,
    const Pnt3f& nrt, const Pnt3f& nrb,
    const Pnt3f& flt, const Pnt3f& flb,
    const Pnt3f& frt, const Pnt3f& frb)
{
    GeoUInt8PropertyRefPtr type = GeoUInt8Property::create();
    type->addValue(GL_QUADS);

    GeoUInt32PropertyRefPtr lens = GeoUInt32Property::create();
    lens->addValue(6 * 4);

    GeoPnt3fPropertyRefPtr  pnts = GeoPnt3fProperty::create();
    // front face
    pnts->addValue(nlb);
    pnts->addValue(nrb);
    pnts->addValue(nrt);
    pnts->addValue(nlt);

    // back face
    pnts->addValue(frb);
    pnts->addValue(flb);
    pnts->addValue(flt);
    pnts->addValue(frt);

    // left face
    pnts->addValue(flb);
    pnts->addValue(nlb);
    pnts->addValue(nlt);
    pnts->addValue(flt);

    // right face
    pnts->addValue(nrb);
    pnts->addValue(frb);
    pnts->addValue(frt);
    pnts->addValue(nrt);

    // top face
    pnts->addValue(nrt);
    pnts->addValue(frt);
    pnts->addValue(flt);
    pnts->addValue(nlt);

    // bottom face
    pnts->addValue(nlb);
    pnts->addValue(flb);
    pnts->addValue(frb);
    pnts->addValue(nrb);

    GeoVec3fPropertyRefPtr normals = GeoVec3fProperty::create();
    Vec3f v1, v2, n;

    // front face
    v1 = nrb - nlb; v2 = nlt - nlb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // back face
    v1 = flb - frb; v2 = frt - frb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // left face
    v1 = nlb - flb; v2 = flt - flb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // right face
    v1 = frb - nrb; v2 = nrt - nrb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // top face
    v1 = frt - nrt; v2 = nlt - nrt; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // bottom face
    v1 = flb - nlb; v2 = nrb - nlb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    GeometryTransitPtr geo = Geometry::create();

    geo->setTypes    (type);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (normals);

    geo->setMaterial(getDefaultUnlitMaterial());

    return geo;
}

/*! Creates a frustum volume

    \param[in] vol is frustum volume
    \return NodeTransitPtr to a newly created Node with a Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
NodeTransitPtr makeFrustumVolume(const FrustumVolume& vol)
{
    GeometryTransitPtr pGeo = makeFrustumVolumeGeo(vol);

    if(pGeo == NULL)
    {
        return NodeTransitPtr(NULL);
    }

    NodeTransitPtr node = Node::create();

    node->setCore(pGeo);

    return node;
}

/*! Creates a frustum volume geometry

    \param[in] vol is frustum volume
    \return GeometryTransitPtr to a newly created Geometry core.

    \ingroup GrpDrawablesGeometryUtils
 */
GeometryTransitPtr makeFrustumVolumeGeo(const FrustumVolume& vol)
{
    Pnt3f nlt = vol.getCorner(FrustumVolume::NEAR_LEFT_TOP);
    Pnt3f nlb = vol.getCorner(FrustumVolume::NEAR_LEFT_BOTTOM);
    Pnt3f nrt = vol.getCorner(FrustumVolume::NEAR_RIGHT_TOP);
    Pnt3f nrb = vol.getCorner(FrustumVolume::NEAR_RIGHT_BOTTOM);
    Pnt3f flt = vol.getCorner(FrustumVolume::FAR_LEFT_TOP);    
    Pnt3f flb = vol.getCorner(FrustumVolume::FAR_LEFT_BOTTOM);
    Pnt3f frt = vol.getCorner(FrustumVolume::FAR_RIGHT_TOP);
    Pnt3f frb = vol.getCorner(FrustumVolume::FAR_RIGHT_BOTTOM);

    GeometryTransitPtr geo = makeFrustumVolumeGeo(nlt, nlb, nrt, nrb, flt, flb, frt, frb);
    return geo;
}

OSG_END_NAMESPACE
