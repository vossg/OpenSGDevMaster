/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGConfig.h>

#include <OSGMatrixUtility.h>

#include "OSGPerspectiveCamera.h"
#include "OSGShearedStereoCameraDecorator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShearedStereoCameraDecorator
    \ingroup GrpSystemWindowCameraDecorators

  The osg::CameraDecorator for standard sheared stereo projections, see \ref
  PageSystemWindowCameraDecoratorsStereoSheared for a description.
  
  The only parameter is defined by the _sfZeroParallaxDistance field.

 */

/*----------------------- constructors & destructors ----------------------*/

ShearedStereoCameraDecorator::ShearedStereoCameraDecorator(void) :
    Inherited()
{
}

ShearedStereoCameraDecorator::ShearedStereoCameraDecorator(
    const ShearedStereoCameraDecorator &source) :

    Inherited(source)
{
}

ShearedStereoCameraDecorator::~ShearedStereoCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShearedStereoCameraDecorator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void ShearedStereoCameraDecorator::changed(ConstFieldMaskArg whichField, 
                                           UInt32            origin)
{
    Inherited::changed(whichField, origin);
}

void ShearedStereoCameraDecorator::dump(      UInt32    , 
                                        const BitVector ) const
{
    SLOG << "Dump ShearedStereoCameraDecorator NI" << std::endl;
}


/*! Get the projection matrix, uses MatrixStereoPerspective to generate it.
*/

void ShearedStereoCameraDecorator::getProjection(Matrix &result, 
                                                 UInt32  width, 
                                                 UInt32  height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }
       
    PerspectiveCameraPtr cam = 
        cast_dynamic<PerspectiveCameraPtr>(getDecoratee());
    
    if(cam == NullFC)
    {
        FFATAL(("ShearedStereoCameraDecorator::getProjection: can only"
                " decorate PerspectiveCameras!\n"));

        result.setIdentity();
        return;
    }
    
    Matrix trans;
    MatrixStereoPerspective(result, trans, cam->getFov(), 
                            width / (Real32) height * cam->getAspect(), 
                            cam->getNear(), 
                            cam->getFar(),
                            getZeroParallaxDistance(),
                            getEyeSeparation(),
                            getLeftEye() ? 0.f : 1.f,
                            getOverlap());
    
    result.mult(trans);
}                                       


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGSHEAREDSTEREOCAMERADECORATOR_HEADER_CVSID;
    static char cvsid_inl[] = OSGSHEAREDSTEREOCAMERADECORATOR_INLINE_CVSID;
}
