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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGCameraDecorator.h"

OSG_USING_NAMESPACE

/*! \class OSG::CameraDecorator
    \ingroup GrpSystemWindowCameraDecorators
    
The base class for the camera decorator, see \ref
PageSystemWindowCameraDecorators for a description. 

The decorated object is held in the _sfDecoratee field.	

*/

/*----------------------- constructors & destructors ----------------------*/

CameraDecorator::CameraDecorator(void) :
    Inherited()
{
}

CameraDecorator::CameraDecorator(const CameraDecorator &source) :
    Inherited(source)
{
}

CameraDecorator::~CameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CameraDecorator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

void CameraDecorator::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CameraDecorator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CameraDecorator NI" << std::endl;
}


/*---------------------- Decorated Functions ----------------------------*/


void CameraDecorator::getProjection(Matrix &result,
                                    UInt32  width ,
                                    UInt32  height)
{
    Camera *camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("CameraDecorator::getProjection: no decoratee!\n"));

        result.setIdentity();

        return;
    }

    camera->getProjection(result, width, height);
}

void CameraDecorator::getProjectionTranslation(Matrix &result, 
                                               UInt32  width , 
                                               UInt32  height)
{
    Camera *camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("CameraDecorator::getProjectionTranslation: "
                  "no decoratee!\n"));

        result.setIdentity();

        return;
    }

    camera->getProjectionTranslation(result, width, height);
}

void CameraDecorator::getViewing(Matrix &result, 
                                 UInt32  width , 
                                 UInt32  height)
{
    Camera *camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("CameraDecorator::getViewing: no decoratee!\n"));

        result.setIdentity();

        return;
    }

    camera->getViewing(result, width, height);
}

