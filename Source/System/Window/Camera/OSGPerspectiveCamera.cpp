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
#include <math.h>

#include "OSGConfig.h"

#include <OSGBaseTypes.h>
#include <OSGLog.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

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

void PerspectiveCamera::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------- your_category---------------------------------*/



void PerspectiveCamera::getProjection(Matrixr &result, 
                                      UInt32   width, 
                                      UInt32   height)
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

    MatrixPerspective(result, 
                      fov   / 2, 
                      width / (Real32) height * getAspect(), 
                      getNear(), 
                      getFar ());
}
    

/*------------------------------- dump ----------------------------------*/

void PerspectiveCamera::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                             const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump PerspectiveCamera NI" << std::endl;
}

    

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGPERSPECTIVECAMERA_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPERSPECTIVECAMERA_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPERSPECTIVECAMERAFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

