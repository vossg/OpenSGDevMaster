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

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include "OSGConfig.h"

#include "OSGBaseTypes.h"
#include "OSGLog.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGPerspectiveCamera.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGPerspectiveCameraBase.cpp file.
// To modify it, please change the .fcd file (OSGPerspectiveCamera.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void PerspectiveCamera::initMethod(InitPhase ePhase)
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

PerspectiveCamera::PerspectiveCamera(void) :
    Inherited()
{
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &source) :
    Inherited(source)
{
}

PerspectiveCamera::~PerspectiveCamera(void)
{
}

void PerspectiveCamera::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/



void PerspectiveCamera::getProjection(Matrix &result, 
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


    Real32 rNear  = getNear();
    Real32 rFar   = getFar ();
    Real32 aspect = Real32(width) / Real32(height) * getAspect();
    Real32 ct     = osgTan(fov / 2.f);

    if(rNear > rFar)
    {
        SWARNING << "MatrixPerspective: near " << rNear << " > far " << rFar
                 << "!\n" << std::endl;
        result.setIdentity();
        return;
    }

    if(fov <= TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: fov " << fov << " very small!\n"
                 << std::endl;
        result.setIdentity();
        return;
    }

    if(osgAbs(rNear - rFar) < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: near " << rNear << " ~= far " << rFar
                 << "!\n" << std::endl;
        result.setIdentity();
        return;
    }

    if(aspect < TypeTraits<Real32>::getDefaultEps())
    {
        SWARNING << "MatrixPerspective: aspect ratio " << aspect
                 << " very small!\n" << std::endl;
        result.setIdentity();
        return;
    }

    Real32 x = ct * rNear;
    Real32 y = ct * rNear;

    UInt32 fovMode = getFovMode();

    switch (fovMode)
    {
        case VerticalFoV:
            x *= aspect;
            break;

        case HorizontalFoV:
            y /= aspect;
            break;

        case SmallerFoV:
            if(width * getAspect() >= height)
            {
                x *= aspect;
            }
            else
            {
                y /= aspect;
            }
            break;

        default:
            result.setIdentity();
            return;
    }

    MatrixFrustum( result,
                  -x,
                   x,
                  -y,
                   y,
                   rNear,
                   rFar);

}
    

/*------------------------------- dump ----------------------------------*/

void PerspectiveCamera::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                             const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump PerspectiveCamera NI" << std::endl;
}

