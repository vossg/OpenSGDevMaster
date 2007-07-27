/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGMatrixCameraDecorator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGMatrixCameraDecoratorBase.cpp file.
// To modify it, please change the .fcd file (OSGMatrixCameraDecorator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MatrixCameraDecorator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MatrixCameraDecorator::MatrixCameraDecorator(void) :
    Inherited()
{
}

MatrixCameraDecorator::MatrixCameraDecorator(
    const MatrixCameraDecorator &source) :

    Inherited(source)
{
}

MatrixCameraDecorator::~MatrixCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MatrixCameraDecorator::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


void MatrixCameraDecorator::getProjection(Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height)
{        
    CameraPtr camera = getDecoratee();

    if(camera == NullFC)
    {
        FWARNING(("MatrixCameraDecorator::getProjection: no decoratee!\n"));

        result.setIdentity();

        return;
    }

    camera->getProjection(result, width, height);
    
    result.multLeft(getPostProjection());
    result.mult    (getPreProjection ());
}                                       

void MatrixCameraDecorator::getProjectionTranslation(Matrix &result, 
                                                     UInt32  width, 
                                                     UInt32  height)
{        
    CameraPtr camera = getDecoratee();

    if(camera == NullFC)
    {
        FWARNING(("MatrixCameraDecorator::getProjectionTranslation: "
                  "no decoratee!\n"));

        result.setIdentity();

        return;
    }

    camera->getProjectionTranslation(result, width, height);
    
    result.multLeft(getPostProjectionTranslation());
    result.mult    (getPreProjectionTranslation ());
}                                       

void MatrixCameraDecorator::getViewing(Matrix &result, 
                                       UInt32  width,
                                       UInt32  height)
{        
    CameraPtr camera = getDecoratee();

    if(camera == NullFC)
    {

        FWARNING(("MatrixCameraDecorator::getViewing: no decoratee!\n"));
        result.setIdentity();

        return;
    }

    camera->getViewing(result, width, height);
    
    result.multLeft(getPostViewing());
    result.mult    (getPreViewing ());
}                                       

void MatrixCameraDecorator::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump MatrixCameraDecorator NI" << std::endl;
}
