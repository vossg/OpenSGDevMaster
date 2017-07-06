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

#include <cmath>

#include "OSGMatrixUtility.h"
#include "OSGBaseFunctions.h"
#include "OSGMatrix.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

OSG_BASE_DLLMAPPING bool MatrixOrthogonal(OSG::Matrix &result,
                                          OSG::Real32  rLeft,
                                          OSG::Real32  rRight,
                                          OSG::Real32  rBottom,
                                          OSG::Real32  rTop,
                                          OSG::Real32  rNear,
                                          OSG::Real32  rFar)
{
    bool error = false;

    if(osgAbs(rRight - rLeft) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: right " << rRight << " ~= left " 
                 << rLeft << "!\n" << std::endl;

        error = true;
    }

    if(osgAbs(rTop - rBottom) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: top " << rTop << " ~= bottom " 
                 << rBottom << "!\n" << std::endl;

        error = true;
    }

    if(osgAbs(rFar - rNear) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }


    if(error == true)
    {
        result.setIdentity();
        return true;
    }

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
         1.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixOrthogonal(OSG::Matrix &result,
                                          OSG::Real32  rWidth,
                                          OSG::Real32  rHeight,
                                          OSG::Real32  rNear,
                                          OSG::Real32  rFar)
{
    bool error = false;

    if(rWidth < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: width " << rWidth << " very small " 
                 << "!\n" << std::endl;

        error = true;
    }

    if(rHeight < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: height " << rHeight << " very small " 
                 << "!\n" << std::endl;

        error = true;
    }

    if(osgAbs(rFar - rNear) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }


    if(error == true)
    {
        result.setIdentity();
        return true;
    }

    result.setValueTransposed(

         2.f / rWidth, 
         0.f, 
         0.f, 
         0.f,

         0.f, 
         2.f / rHeight, 
         0.f, 
         0.f,

         0.f, 
         0.f, 
        -2.f / (rFar - rNear), 
         0.f,

         0.f,
         0.f,
        -(rFar + rNear) / (rFar - rNear), 
         1.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixOrthogonal2D(OSG::Matrix &result,
                                            OSG::Real32  rLeft,
                                            OSG::Real32  rRight,
                                            OSG::Real32  rBottom,
                                            OSG::Real32  rTop)
{
    bool error = false;

    if(osgAbs(rRight - rLeft) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal2D: right " << rRight << " ~= left " 
                 << rLeft << "!\n" << std::endl;

        error = true;
    }

    if(osgAbs(rTop - rBottom) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal2D: top " << rTop << " ~= bottom " 
                 << rBottom << "!\n" << std::endl;

        error = true;
    }

    if(error == true)
    {
        result.setIdentity();
        return true;
    }

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
        -1.f, 
         0.f,

        -(rRight + rLeft  ) / (rRight - rLeft  ),
        -(rTop   + rBottom) / (rTop   - rBottom),
         0.f, 
         1.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixOrthogonal2D(OSG::Matrix &result,
                                            OSG::Real32  rWidth,
                                            OSG::Real32  rHeight)
{
    bool error = false;

    if(rWidth < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal2D: width " << rWidth << " very small " 
                 << "!\n" << std::endl;

        error = true;
    }

    if(rHeight < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixOrthogonal2D: height " << rHeight << " very small " 
                 << "!\n" << std::endl;

        error = true;
    }

    if(error == true)
    {
        result.setIdentity();
        return true;
    }

    result.setValueTransposed(

         2.f / rWidth, 
         0.f, 
         0.f, 
         0.f,

         0.f, 
         2.f / rHeight, 
         0.f, 
         0.f,

         0.f, 
         0.f, 
        -1.f, 
         0.f,

         0.f,
         0.f,
         0.f, 
         1.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixFrustum(OSG::Matrix &result,
                                       OSG::Real32  rLeft,
                                       OSG::Real32  rRight,
                                       OSG::Real32  rBottom,
                                       OSG::Real32  rTop,
                                       OSG::Real32  rNear,
                                       OSG::Real32  rFar)
{
    Real32 dx = rRight - rLeft;
    Real32 dy = rTop   - rBottom;
    Real32 dz = rFar   - rNear;
    Real32 n2 = 2.f    * rNear;

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


OSG_BASE_DLLMAPPING bool MatrixPerspective(OSG::Matrix &result,
                                           OSG::Real32  rFovy,
                                           OSG::Real32  rAspect,
                                           OSG::Real32  rNear,
                                           OSG::Real32  rFar)
{
    bool   error = false;

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rFovy <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(osgAbs(rNear - rFar) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rAspect < TypeTraits<Real32>::getDefaultEps())
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

    Real32 ct = osgTan(rFovy);

    MatrixFrustum( result, 
                  -rNear * ct * rAspect, 
                   rNear * ct * rAspect,
                  -rNear * ct, 
                   rNear * ct, 
                   rNear, 
                   rFar                );

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixPerspective(OSG::Matrix &result,
                                           OSG::Real32  rFovy,
                                           OSG::Real32  rWidth,
                                           OSG::Real32  rHeight,
                                           OSG::Real32  rNear,
                                           OSG::Real32  rFar)
{
    bool   error = false;

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rFovy <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(osgAbs(rNear - rFar) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rWidth < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: width " << rWidth << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(rHeight < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: height " << rHeight << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(error)
    {
        result.setIdentity();
        return true;
    }

    Real32 rAspect = rWidth / rHeight;
    Real32 ct      = osgTan(rFovy);

    MatrixFrustum( result, 
                  -rNear * ct * rAspect, 
                   rNear * ct * rAspect,
                  -rNear * ct, 
                   rNear * ct, 
                   rNear, 
                   rFar                );

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixStereoPerspective(OSG::Matrix &projection,
                                                 OSG::Matrix &projtrans,
                                                 OSG::Real32  rFovy,
                                                 OSG::Real32  rAspect,
                                                 OSG::Real32  rNear,
                                                 OSG::Real32  rFar,
                                                 OSG::Real32  rZeroparallax,
                                                 OSG::Real32  rEyedistance,
                                                 OSG::Real32  rWhicheye,
                                                 OSG::Real32  rOverlap)
{
    Real32 rLeft;
    Real32 rRight;
    Real32 rTop;
    Real32 rBottom;

    Real32 gltan;
    Real32 rEye = -rEyedistance * (rWhicheye - .5f);
    Real32 d;

    bool  error = false;

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rFovy <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(osgAbs(rNear - rFar) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;

        error = true;
    }

    if(rAspect < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: aspect ratio " << rAspect
                 << " very small!\n"                   << std::endl;

        error = true;
    }

    if(rZeroparallax < TypeTraits<Real32>::getDefaultEps())
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
    rTop    = osgTan(rFovy / 2.0f) * rNear; 
    rBottom = -rTop;

    /* Calculate left and right clipping planes */
    gltan  = osgTan(rFovy / 2.0f) * rAspect;  

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

OSG_BASE_DLLMAPPING bool MatrixInfinitePerspective(OSG::Matrix &result,
                                                   OSG::Real32  rFovy,
                                                   OSG::Real32  rAspect,
                                                   OSG::Real32  rNear)
{
    // see http://www.terathon.com/gdc07_lengyel.pdf

    bool   error = false;

    if(rFovy <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixInfinitePerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(rAspect < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixInfinitePerspective: aspect ratio " << rAspect
                 << " very small!\n" << std::endl;

        error = true;
    }

    if(error)
    {
        result.setIdentity();
        return true;
    }

    Real32 r  = osgTan(rFovy) * rNear;
    Real32 dx = 2.f * r * rAspect;
    Real32 dy = 2.f * r;
    Real32 n2 = 2.f * rNear;

    result.setValueTransposed(
         n2 / dx, 
         0.f, 
         0.f, 
         0.f,

         0.f,
         n2 / dy, 
         0.f, 
         0.f,

         0.f,
         0.f,
        -1.f, 
        -1.f,

         0.f, 
         0.f, 
        -n2, 
         0.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixEpsInfinitePerspective(OSG::Matrix &result,
                                                      OSG::Real32  rFovy,
                                                      OSG::Real32  rAspect,
                                                      OSG::Real32  rNear,
                                                      OSG::Real32  rEps)
{
    // see http://www.terathon.com/gdc07_lengyel.pdf

    bool   error = false;

    if(rFovy <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixEpsInfinitePerspective: fovy " << rFovy << " very small!\n"
                 << std::endl;

        error = true;
    }

    if(rAspect < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixEpsInfinitePerspective: aspect ratio " << rAspect
                 << " very small!\n" << std::endl;

        error = true;
    }

    if(rEps <= 2.4E-7)
    {
        SWARNING << "MatrixEpsInfinitePerspective: epsilon " << rEps << " to small!\n"
                 << std::endl;
    }

    if(error)
    {
        result.setIdentity();
        return true;
    }

    Real32 r  = osgTan(rFovy) * rNear;
    Real32 dx = 2.f * r * rAspect;
    Real32 dy = 2.f * r;
    Real32 n2 = 2.f * rNear;

    result.setValueTransposed(
         n2 / dx, 
         0.f, 
         0.f, 
         0.f,

         0.f,
         n2 / dy, 
         0.f, 
         0.f,

         0.f,
         0.f,
         rEps - 1.f, 
        -1.f,

         0.f, 
         0.f, 
         (rEps - 2.f) * rNear, 
         0.f);

    return false;
}

/*! \warning This matrix is meant to used for setting up the 
      beacon transformation of a OSG::Camera! They are inverted compared to
      the similarly named OpenGl function!
*/

OSG_BASE_DLLMAPPING bool MatrixLookAt(OSG::Matrix &result,
                                      OSG::Real32  fromx,
                                      OSG::Real32  fromy,
                                      OSG::Real32  fromz,
                                      OSG::Real32  atx,
                                      OSG::Real32  aty,
                                      OSG::Real32  atz,
                                      OSG::Real32  upx,
                                      OSG::Real32  upy,
                                      OSG::Real32  upz)
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f up;

    view.setValues(fromx - atx , fromy - aty, fromz - atz);
    view.normalize();

    up.setValues(upx, upy, upz);

    right = up.cross(view);

    if(right.dot(right) < TypeTraits<Real32>::getDefaultEps())
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
      beacon transformation of a OSG::Camera! They are inverted compared to
      the similarly named OpenGl function!
*/

OSG_BASE_DLLMAPPING bool MatrixLookAt(OSG::Matrix &result,
                                      OSG::Pnt3f   from, 
                                      OSG::Pnt3f   at, 
                                      OSG::Vec3f   up    )
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f tmp;

    view = from - at;
    view.normalize();

    right = up.cross(view);

    if(right.dot(right) < TypeTraits<Real32>::getDefaultEps())
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

/*! \warning This matrix is the classical OpenGL lookAt function.
    For setting up the beacon transformation of a OSG::Camera you
    should go for the MatrixLookAt(...) functions.
*/
OSG_BASE_DLLMAPPING bool MatrixLookAtGL(OSG::Matrix &result,
                                        OSG::Real32  fromx,
                                        OSG::Real32  fromy,
                                        OSG::Real32  fromz,
                                        OSG::Real32  atx,
                                        OSG::Real32  aty,
                                        OSG::Real32  atz,
                                        OSG::Real32  upx,
                                        OSG::Real32  upy,
                                        OSG::Real32  upz)
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f up;

    view.setValues(fromx - atx , fromy - aty, fromz - atz);
    view.normalize();

    up.setValues(upx, upy, upz);

    right = up.cross(view);

    if(right.dot(right) < TypeTraits<Real32>::getDefaultEps())
    {
        return true;
    }

    right.normalize();

    newup = view.cross(right);

    Pnt3f from(fromx, fromy, fromz);

    result.setIdentity ();
    result.setTranslate(-right.dot(from), -newup.dot(from), -view.dot(from));

    Matrix tmpm;

    tmpm.setValue(right, newup, view);

    result.mult(tmpm);
    result.transpose();

    return false;
}

/*! \warning This matrix is the classical OpenGL lookAt function.
    For setting up the beacon transformation of a OSG::Camera you
    should go for the MatrixLookAt(...) functions.
*/
OSG_BASE_DLLMAPPING bool MatrixLookAtGL(OSG::Matrix &result,
                                        OSG::Pnt3f   from, 
                                        OSG::Pnt3f   at, 
                                        OSG::Vec3f   up    )
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f tmp;

    view = from - at;
    view.normalize();

    right = up.cross(view);

    if(right.dot(right) < TypeTraits<Real32>::getDefaultEps())
    {
        return true;
    }

    right.normalize();

    newup = view.cross(right);

    result.setValue(
         right[0], 
         right[1], 
         right[2], 
        -right.dot(from),

         newup[0],
         newup[1],
         newup[2],
        -newup.dot(from),

         view[0],
         view[1],
         view[2],
        -view.dot(from),

         0.f, 
         0.f, 
         0.f, 
         1.f);

    return false;
}

OSG_BASE_DLLMAPPING bool MatrixProjection(OSG::Matrix &OSG_CHECK_ARG(result),
                                          OSG::Real32  OSG_CHECK_ARG(rLeft),
                                          OSG::Real32  OSG_CHECK_ARG(rRight),
                                          OSG::Real32  OSG_CHECK_ARG(rBottom),
                                          OSG::Real32  OSG_CHECK_ARG(rTop),
                                          OSG::Real32  OSG_CHECK_ARG(rNear),
                                          OSG::Real32  OSG_CHECK_ARG(rFar) )
{
    SFATAL << "MatrixProjection: Not yet implemented!" << std::endl;

    return false;
}

void makeViewFromUVND(      Matrix &Result,
                      const Vec3f  &U,
                      const Vec3f  &V,
                      const Vec3f  &N,
                      const Vec3f  &D     )
{
    //Set up the Rotation matrix
    //Put U in the 1st row
    Result[0][0] = U.x();
    Result[1][0] = U.y();
    Result[2][0] = U.z();

    //Put V in the 2nd row
    Result[0][1] = V.x();
    Result[1][1] = V.y();
    Result[2][1] = V.z();

    //Put N in the 3rd row
    Result[0][2] = N.x();
    Result[1][2] = N.y();
    Result[2][2] = N.z();

    //Put D in the 4th column
    Result[3][0] = D.x();
    Result[3][1] = D.y();
    Result[3][2] = D.z();

    //Clear up the rest of the matrix
    Result[3][3] = 1.f;
    Result[0][3] = Result[1][3] = Result[2][3] = 0.f;
}

void getUVNDFromMat(const Matrix &Mat,
                          Vec3f  &U,
                          Vec3f  &V,
                          Vec3f  &N,
                          Vec3f  &D  )
{
    //get U in the 1st row
    U.setValues(Mat[0][0],
                Mat[1][0],
                Mat[2][0]);
    //get V in the 2nd row
    V.setValues(Mat[0][1],
                Mat[1][1],
                Mat[2][1]);
    //get N in the 3rd row
    N.setValues(Mat[0][2],
                Mat[1][2],
                Mat[2][2]);

    //get D in the 4th column
    D.setValues(Mat[3][0],
                Mat[3][1],
                Mat[3][2]);
}

void makeViewFromUVNP(      Matrix &Result,
                      const Vec3f  &U,
                      const Vec3f  &V,
                      const Vec3f  &N,
                      const Pnt3f  &P     )
{
    makeViewFromUVND(Result, 
                     U,
                     V,
                     N, 
                     Vec3f(-Vec3f(P).dot(U), 
                           -Vec3f(P).dot(V), 
                           -Vec3f(P).dot(N)));
}

void getUVNPFromMat(const Matrix &Mat, Vec3f &U, Vec3f &V, Vec3f &N, Pnt3f &P)
{
    //Get U, V, N, D from the mat
    Vec3f D;
    getUVNDFromMat(Mat,U,V,N,D);

    //Calculate the Eye position from U, V, N, D
    P = Pnt3f(-((D.x() * U) + (D.y() * V) + (D.z() * N)));
}

void getPFromViewMat(Pnt3f &P, const Matrix &Mat)
{
    //Get U, V, N, D from the mat
    Vec3f U,V,N;
    getUVNPFromMat(Mat,U,V,N,P);
}

void setViewMatEyePos(Matrix &Result,const Pnt3f &P)
{
    //Get U, V, N, D from the mat

    Vec3f U,V,N,D;

    getUVNDFromMat(Result,U,V,N,D);

    Vec3f TempP(P[0],P[1],P[2]);

    Result[3][0] = -TempP.dot(U);
    Result[3][1] = -TempP.dot(V);
    Result[3][2] = -TempP.dot(N);
}

void MatrixSkew(      Matrix &result, 
                const Vec3f  &vRotationAxis, 
                const Vec3f  &vTranslationAxis, 
                      Real32  rAngleInRadians)
{
    /* 
     * Implemented in accordance with the RenderMan specification.
     * See
     * http://www.koders.com/cpp/fidA08C276050F880D11C2E49280DD9997478DC5BA1.aspx
     * for the implementation that this was copied from.
     * (If the url is invalid, this implementation was copied from the GNU
     * GMAN project, in the gmanmatrix4.cpp file.)
     *
     */

    result.setIdentity();

    Real32 an1,an2,rx,ry,alpha;
    Vec3f  a1,a2,n1,n2;

    Vec3f a(vRotationAxis), b(vTranslationAxis);

    b.normalize();

    a1 = b * a.dot(b);
    a2 = a - a1;

    a2.normalize();

    an1 = a.dot(a2);
    an2 = a.dot(b);

    rx = an1 * osgCos(rAngleInRadians) - an2 * osgSin(rAngleInRadians);
    ry = an1 * osgSin(rAngleInRadians) + an2 * osgCos(rAngleInRadians);

    if(rx <= 0.0f)
    {  // skew rAngleInRadians too large, and we can't calculate the skew
       // matrix 
        SWARNING << "ColladaNode::handleSkew: Skew Angle too large! ( rx = "
                 << rx << " )" << std::endl;

        return; 
    }

    // are A and B parallel?
    if(osgAbs(an1) < 0.000001)
    {
        alpha = 0.0f;
    }
    else
    {
        alpha = ry / rx - an2 / an1;
    }

    result[0][0] = a2.x() * b.x() * alpha + 1.0f;
    result[1][0] = a2.y() * b.x() * alpha;
    result[2][0] = a2.z() * b.x() * alpha;

    result[0][1] = a2.x() * b.y() * alpha;
    result[1][1] = a2.y() * b.y() * alpha + 1.0f;
    result[2][1] = a2.z() * b.y() * alpha;

    result[0][2] = a2.x() * b.z() * alpha;
    result[1][2] = a2.y() * b.z() * alpha;
    result[2][2] = a2.z() * b.z() * alpha + 1.0f;
}

void MatrixReflectOriginPlane(Matrix& Result, const Vec3f& N)
{
    Real32 xx = N[0]*N[0];
    Real32 yy = N[1]*N[1];
    Real32 zz = N[2]*N[2];
    Real32 xy = N[0]*N[1];
    Real32 xz = N[0]*N[2];
    Real32 yz = N[1]*N[2];

    Result.setValue(1.f-2.f*xx,    -2.f*xy,    -2.f*xz, 0.f,
                       -2.f*xy, 1.f-2.f*yy,    -2.f*yz, 0.f,
                       -2.f*xz,    -2.f*yz, 1.f-2.f*zz, 0.f,
                           0.f,        0.f,        0.f, 1.f);
}

void MatrixRotateTowards(Matrix& Result, Vec3f a, Vec3f b)
{
    Result.setIdentity();

    a.normalize();
    b.normalize();

    Real32 c = a.dot(b);
    if (osgAbs(1.f - c) < Eps)
        return;

    if (osgAbs(-1.f - c) < Eps)
    {
        MatrixReflectOriginPlane(Result, a);
        return;
    }

    Vec3f v = a.cross(b);

    Matrix skew( 0.f,-v[2], v[1],  0.f,
                v[2],  0.f,-v[0],  0.f,
               -v[1], v[0],  0.f,  0.f,
                 0.f,  0.f,  0.f,  0.f);

    Matrix T(skew); T.mult(skew); T.scale(1.f / (1.f + c));

    Result.add(skew); Result.add(T);
}

OSG_END_NAMESPACE




