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

// System declarations

#include <math.h>

#include "OSGMatrixUtility.h"
#include "OSGBaseFunctions.h"
#include "OSGMatrix.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE


OSG_BASE_DLLMAPPING bool MatrixOrthogonal(Matrix &result,
                                          Real32  rLeft,
                                          Real32  rRight,
                                          Real32  rBottom,
                                          Real32  rTop,
                                          Real32  rNear,
                                          Real32  rFar)
{
    result.setValueTransposed(

         2.f / (rRight - rLeft), 
         0.f, 
         0.f, 
         0.f,

         0.f, 
         2.f / (rTop - rBottom), 
         0.f, 
         0.f,

         0.f, 
         0.f, 
        -2.f / (rFar - rNear), 
         0.f,

        -(rRight + rLeft  ) / (rRight - rLeft  ),
        -(rTop   + rBottom) / (rTop   - rBottom),
        -(rFar   + rNear  ) / (rFar   - rNear  ), 
         1.);

    return false;
}


OSG_BASE_DLLMAPPING bool MatrixFrustum(Matrixr &result,
                                       Real     rLeft,
                                       Real     rRight,
                                       Real     rBottom,
                                       Real     rTop,
                                       Real     rNear,
                                       Real     rFar)
{
    Real dz = rFar   - rNear;
    Real dx = rRight - rLeft;
    Real dy = rTop   - rBottom;
    Real n2 = 2.f    * rNear;

    result.setValueTransposed(
         n2 / dx, 
         0.f, 
         0.f, 
         0.f,

         0.f,
         n2 / dy, 
         0.f, 
         0.f,

         (rRight + rLeft  ) / dx,
         (rTop   + rBottom) / dy,
        -(rFar   + rNear  ) / dz, 
        -1.f,

         0.f, 
         0.f, 
        -(rFar * n2) / dz, 
         0.f);

    return false;
}


OSG_BASE_DLLMAPPING bool MatrixPerspective(Matrixr &result,
                                           Real     rFovy,
                                           Real     rAspect,
                                           Real     rNear,
                                           Real     rFar)
{
    Real ct    = osgtan(rFovy);
    bool error = false;

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rFovy <= Eps)
    {
        SWARNING << "MatrixPerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(osgabs(rNear - rFar) < Eps)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rAspect < Eps)
    {
        SWARNING << "MatrixPerspective: aspect ratio " << rAspect
                 << " very small!\n" << std::endl;

        error = true;
    }

    if(error)
    {
        result.setIdentity();
        return true;
    }

    MatrixFrustum( result, 
                  -rNear * ct * rAspect, 
                   rNear * ct * rAspect,
                  -rNear * ct, 
                   rNear * ct, 
                   rNear, 
                   rFar                );

    return false;
}


OSG_BASE_DLLMAPPING bool MatrixStereoPerspective(Matrixr &projection,
                                                 Matrixr &projtrans,
                                                 Real     rFovy,
                                                 Real     rAspect,
                                                 Real     rNear,
                                                 Real     rFar,
                                                 Real     rZeroparallax,
                                                 Real     rEyedistance,
                                                 Real     rWhicheye,
                                                 Real     rOverlap)
{
    Real rLeft;
    Real rRight;
    Real rTop;
    Real rBottom;

    Real gltan;
    Real rEye = -rEyedistance * (rWhicheye - .5f);
    Real d;

    bool error = false;

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rFovy <= Eps)
    {
        SWARNING << "MatrixPerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(osgabs(rNear - rFar) < Eps)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rAspect < Eps)
    {
        SWARNING << "MatrixPerspective: aspect ratio " << rAspect
                 << " very small!\n"                   << std::endl;

        error = true;
    }

    if(rZeroparallax < Eps)
    {
        SWARNING << "MatrixPerspective: zero parallax " << rZeroparallax
                 << " very small, setting to 1!\n"      << std::endl;

        rZeroparallax = 1.f;
        error         = true;
    }
    
    if(error)
    {
        projection.setIdentity();
        projtrans .setIdentity();

        return true;
    }

    /* Calculate upper and lower clipping planes */
    rTop    = osgtan(rFovy / 2.0f) * rNear; 
    rBottom = -rTop;

    /* Calculate left and right clipping planes */
    gltan  = osgtan(rFovy / 2.0f) * rAspect;  

    rLeft  = (-gltan + rEye / rZeroparallax) * rNear;
    rRight = ( gltan + rEye / rZeroparallax) * rNear;

    d = rRight - rLeft;

    rLeft  += d * (1.f - rOverlap) * (rWhicheye - .5f);
    rRight += d * (1.f - rOverlap) * (rWhicheye - .5f);

    MatrixFrustum(projection, rLeft, rRight, rBottom, rTop, rNear, rFar);

    projtrans.setIdentity();

    projtrans[3][0] = rEye;

    return false;
}

/*! \warning This matrix is meant to used for setting up the 
      beacon transformation of a osg::Camera! They are inverted compared to
      the similarly named OpenGl function!
*/

OSG_BASE_DLLMAPPING bool MatrixLookAt(Matrix &result,
                                      Real32  fromx,
                                      Real32  fromy,
                                      Real32  fromz,
                                      Real32  atx,
                                      Real32  aty,
                                      Real32  atz,
                                      Real32  upx,
                                      Real32  upy,
                                      Real32  upz)
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f up;

    view.setValues(fromx - atx , fromy - aty, fromz - atz);
    view.normalize();

    up.setValues(upx, upy, upz);

    right = up.cross(view);

    if(right.dot(right) < Eps)
    {
        return true;
    }

    right.normalize();

    newup = view.cross(right);

    result.setIdentity ();
    result.setTranslate(fromx, fromy, fromz);

    Matrix tmpm;

    tmpm.setValue(right, newup, view);

    result.mult(tmpm);

    return false;
}

/*! \warning This matrix is meant to used for setting up the 
      beacon transformation of a osg::Camera! They are inverted compared to
      the similarly named OpenGl function!
*/

OSG_BASE_DLLMAPPING bool MatrixLookAt(Matrix &result,
                                      Pnt3f   from, 
                                      Pnt3f   at, 
                                      Vec3f   up    )
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f tmp;

    view = from - at;
    view.normalize();

    right = up.cross(view);

    if(right.dot(right) < Eps)
    {
        return true;
    }

    right.normalize();

    newup = view.cross(right);

    result.setIdentity ();
    result.setTranslate(from[0], from[1], from[2]);

    Matrix tmpm;

    tmpm.setValue(right, newup, view);

    result.mult(tmpm);

    return false;
}


OSG_BASE_DLLMAPPING bool MatrixProjection(Matrix &OSG_CHECK_ARG(result),
                                          Real32  OSG_CHECK_ARG(rLeft),
                                          Real32  OSG_CHECK_ARG(rRight),
                                          Real32  OSG_CHECK_ARG(rBottom),
                                          Real32  OSG_CHECK_ARG(rTop),
                                          Real32  OSG_CHECK_ARG(rNear),
                                          Real32  OSG_CHECK_ARG(rFar) )
{
    SFATAL << "MatrixProjection: Not yet implemented!" << std::endl;

    return false;
}

OSG_END_NAMESPACE




