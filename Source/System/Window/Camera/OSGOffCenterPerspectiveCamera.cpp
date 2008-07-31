/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "OSGMatrixUtility.h"
#include "OSGOffCenterPerspectiveCamera.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::OffCenterPerspectiveCamera
    \ingroup GrpSystemWindowCameras

The OffCenter Perspective Camera class.

The only new parameter is the _sfPrincipalPoint field.

The OffCenter Perspective Camera provides a more general camera than the
Perspective Camera.
The viewing frustrum is by default the same as given by the Perspective 
Camera.
Iff principal points params are unequal zero the viewing frustrums parameters
(left,right,top,bottom) are simple shifted in the camera's image plane.
The principal point parameters are relative to left--right (or respectively
bottom--top).
A value of x=2 means the left value is equal to default 
right value.
A value of x=-2 means the right value is equal to default 
left value.
Marginal note: Iff the principal point is unequal zero the field of view
value is unequal to the real field of view of the camera. 
(mail to: dherzog (at) mip.informatik.uni-kiel.de)
*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void OffCenterPerspectiveCamera::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

OffCenterPerspectiveCamera::OffCenterPerspectiveCamera(void) :
    Inherited()
{
}

OffCenterPerspectiveCamera::
OffCenterPerspectiveCamera(const OffCenterPerspectiveCamera &source) :
    Inherited(source)
{
}

OffCenterPerspectiveCamera::~OffCenterPerspectiveCamera(void)
{
}

void OffCenterPerspectiveCamera::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

bool OffCenterPerspectiveCamera::MatrixPerspectivePrincipalPnt(
    Matrix &result,
    Real32 rFovy,
    Real32 rAspect,
    Real32 rNear,
    Real32 rFar,
    Real32 rPrincipalPointX,
    Real32 rPrincipalPointY)
{
    Real32 ct = osgTan(rFovy);
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

    if(osgAbs(rNear - rFar) < Eps)
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
                    -rNear * ct * rAspect * (Real32(1)+rPrincipalPointX), 
                     rNear * ct * rAspect * (Real32(1)-rPrincipalPointX),
                    -rNear * ct * (Real32(1)+rPrincipalPointY), 
                     rNear * ct * (Real32(1)-rPrincipalPointY), 
                     rNear, 
                     rFar                );

    return false;
}

void OffCenterPerspectiveCamera::getProjection(Matrix &result, 
                                               UInt32  width, 
                                               UInt32  height)
{
    Real32 fov = getFov();

    // catch some illegal cases
    if(fov < 0 || width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }
    
    // try to be nice to people giving degrees...
    if(fov > Pi)
        fov = osgDegree2Rad(fov);

    Real32 principalPointX = getPrincipalPoint()[0];
    Real32 principalPointY = getPrincipalPoint()[1];

    // if principal point (x,y) is default (==(0,0)) everything works
    // like before or rather for an symmetical camera
    if(principalPointX == Real32(0) && principalPointY == Real32(0)) 
    {
        MatrixPerspective(result, fov / 2, 
                          width / Real32(height) * getAspect(), 
                          getNear(), getFar());
    } 
    else 
    {
        MatrixPerspectivePrincipalPnt(result, fov / 2, 
                                      width / Real32(height) * getAspect(), 
                                      getNear(), getFar(),
                                      principalPointX, principalPointY);
    }
}
    

/*------------------------------- dump ----------------------------------*/

void OffCenterPerspectiveCamera::dump(  
          UInt32    OSG_CHECK_ARG(uiIndent), 
    const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump OffCenterPerspectiveCamera NI" << std::endl;
}


