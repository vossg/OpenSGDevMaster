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

#ifndef _OSGMATRIXUTILITY_H_
#define _OSGMATRIXUTILITY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrixFwd.h"

OSG_BEGIN_NAMESPACE

/*! \name Matrix Functions
    Matrix utility functions to create and analyze special kinds 
    of matrices.

    Remarks: 1. fovy parameters are measured from the y-axis to the
                border of the view, i.e. the half of the full fovy
                value must be given to the functions below.

             2. All projection matrices are right handed systems.
                If you need a left hand system instead, multiply by
                a scale matrix S(1, 1,-1, 1) in the diagonal.

             3. All projection matrices map to OpenGL NDC cube [-1,1]^3
    \{
 */

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixOrthogonal        (OSG::Matrix &result, 
                                                  OSG::Real32  rLeft, 
                                                  OSG::Real32  rRight, 
                                                  OSG::Real32  rBottom, 
                                                  OSG::Real32  rTop, 
                                                  OSG::Real32  rNear, 
                                                  OSG::Real32  rFar       );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixOrthogonal        (OSG::Matrix &result, 
                                                  OSG::Real32  rWidth, 
                                                  OSG::Real32  rHeight, 
                                                  OSG::Real32  rNear, 
                                                  OSG::Real32  rFar       );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixOrthogonal2D      (OSG::Matrix &result, 
                                                  OSG::Real32  rLeft, 
                                                  OSG::Real32  rRight, 
                                                  OSG::Real32  rBottom, 
                                                  OSG::Real32  rTop       );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixOrthogonal2D      (OSG::Matrix &result, 
                                                  OSG::Real32  rWidth, 
                                                  OSG::Real32  rHeight    );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixFrustum           (OSG::Matrix &result, 
                                                  OSG::Real32  rLeft, 
                                                  OSG::Real32  rRight,
                                                  OSG::Real32  rBottom, 
                                                  OSG::Real32  rTop, 
                                                  OSG::Real32  rNear, 
                                                  OSG::Real32  rFar       );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixPerspective      (OSG::Matrix &result, 
                                                 OSG::Real32  rFovy, 
                                                 OSG::Real32  rAspect,
                                                 OSG::Real32  rNear, 
                                                 OSG::Real32  rFar        );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixPerspective      (OSG::Matrix &result, 
                                                 OSG::Real32  rFovy, 
                                                 OSG::Real32  rWidth,
                                                 OSG::Real32  rHeight,
                                                 OSG::Real32  rNear, 
                                                 OSG::Real32  rFar        );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixStereoPerspective(OSG::Matrix &projection, 
                                                 OSG::Matrix &projtrans, 
                                                 OSG::Real32  rFovy, 
                                                 OSG::Real32  rAspect, 
                                                 OSG::Real32  rNear, 
                                                 OSG::Real32  rFfar, 
                                                 OSG::Real32  rZeroparallax, 
                                                 OSG::Real32  rEyedistance, 
                                                 OSG::Real32  rWhicheye, 
                                                 OSG::Real32  rOverlap    );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix

    see http://www.terathon.com/gdc07_lengyel.pdf
 */
OSG_BASE_DLLMAPPING bool MatrixInfinitePerspective(OSG::Matrix &result, 
                                                   OSG::Real32  rFovy, 
                                                   OSG::Real32  rAspect,
                                                   OSG::Real32  rNear     );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix

    see http://www.terathon.com/gdc07_lengyel.pdf
 */
OSG_BASE_DLLMAPPING bool MatrixEpsInfinitePerspective(OSG::Matrix &result, 
                                                      OSG::Real32  rFovy, 
                                                      OSG::Real32  rAspect,
                                                      OSG::Real32  rNear,
                                                      OSG::Real32  rEps = OSG::TypeTraits<OSG::Real32>::getDefaultEps() );
/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixLookAt           (OSG::Matrix &result, 
                                                 OSG::Real32  fromx, 
                                                 OSG::Real32  fromy, 
                                                 OSG::Real32  fromz, 
                                                 OSG::Real32  atx,   
                                                 OSG::Real32  aty,   
                                                 OSG::Real32  atz, 
                                                 OSG::Real32  upx,   
                                                 OSG::Real32  upy,   
                                                 OSG::Real32  upz          );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixLookAt           (OSG::Matrix &result, 
                                                 OSG::Pnt3f   from,
                                                 OSG::Pnt3f   at,
                                                 OSG::Vec3f   up           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixLookAtGL         (OSG::Matrix &result, 
                                                 OSG::Real32  fromx, 
                                                 OSG::Real32  fromy, 
                                                 OSG::Real32  fromz, 
                                                 OSG::Real32  atx,   
                                                 OSG::Real32  aty,   
                                                 OSG::Real32  atz, 
                                                 OSG::Real32  upx,   
                                                 OSG::Real32  upy,   
                                                 OSG::Real32  upz          );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixLookAtGL         (OSG::Matrix &result, 
                                                 OSG::Pnt3f   from,
                                                 OSG::Pnt3f   at,
                                                 OSG::Vec3f   up           );


/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING bool MatrixProjection       (OSG::Matrix &result, 
                                                 OSG::Real32  rLeft,
                                                 OSG::Real32  rRight, 
                                                 OSG::Real32  rBottom,
                                                 OSG::Real32  rTop,  
                                                 OSG::Real32  rNear,
                                                 OSG::Real32  rFar         );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void MatrixSkew             (      Matrix &result,
                                                 const Vec3f  &vRotationAxis,
                                                 const Vec3f  &vTranslationAxis,
                                                       Real32  rAngleInRadians);

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void makeViewFromUVND       (      Matrix &Result,
                                                 const Vec3f  &U,
                                                 const Vec3f  &V,
                                                 const Vec3f  &N,
                                                 const Vec3f  &D           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void makeViewFromUVNP       (      Matrix &Result,
                                                 const Vec3f  &U,
                                                 const Vec3f  &V,
                                                 const Vec3f  &N,
                                                 const Pnt3f  &P           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void getUVNDFromMat         (const Matrix &Mat,
                                                       Vec3f  &U,
                                                       Vec3f  &V,
                                                       Vec3f  &N,
                                                       Vec3f  &D           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void getUVNPFromMat         (const Matrix &Mat,
                                                       Vec3f  &U,
                                                       Vec3f  &V,
                                                       Vec3f  &N,
                                                       Pnt3f  &P           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void getPFromViewMat        (      Pnt3f  &P,
                                                 const Matrix &Mat         );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void setViewMatEyePos       (      Matrix &Result,
                                                 const Pnt3f  &P           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix
 */
OSG_BASE_DLLMAPPING void MatrixReflectOriginPlane
                                                (      Matrix &Result,
                                                 const Vec3f  &N           );

/*! \ingroup GrpBaseBaseMathMatrixFn
    \relatesalso TransformationMatrix

    The resulting orthonormal matrix rotates vector a into the direction 
    of vector b. If b is a unit vector then the resulting vector b' = M*b
    is identical to vector b. For some unit vector a' the resulting vector 
    b' = M*a' is also a unit vector. 
    Neither the length of a nor b is used in the calculation of the
    rotation matrix!
 */
OSG_BASE_DLLMAPPING  void MatrixRotateTowards   (       Matrix &Result,
                                                        Vec3f  a, 
                                                        Vec3f  b           );
/*! \} 
 */

OSG_END_NAMESPACE

#endif /* _OSGMATRIXUTILITY_H_ */
