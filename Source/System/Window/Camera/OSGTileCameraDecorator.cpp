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

#include "OSGTileCameraDecorator.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTileCameraDecoratorBase.cpp file.
// To modify it, please change the .fcd file (OSGTileCameraDecorator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TileCameraDecorator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

TileCameraDecorator::TileCameraDecorator(void) :
    Inherited()
{
}

TileCameraDecorator::TileCameraDecorator(const TileCameraDecorator &source) :
    Inherited(source)
{
}

TileCameraDecorator::~TileCameraDecorator(void)
{
}

void TileCameraDecorator::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*! Set all the size-related Fields at once. 

    Does not call begin/endEdit internally!
*/ 

void TileCameraDecorator::setSize(Real32 left, 
                                  Real32 bottom, 
                                  Real32 right, 
                                  Real32 top   )
{
    setLeft  (left  );
    setRight (right );
    setBottom(bottom);
    setTop   (top   );
}

void TileCameraDecorator::getProjection(Matrix &result, 
                                        UInt32  width, 
                                        UInt32  height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }
    
    Camera *camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("TileCameraDecorator::getProjection: no decoratee!\n"));

        result.setIdentity();

        return;
    }

    if(getFullWidth() != 0)
        width = getFullWidth();
    
    if(getFullHeight() != 0)
        height = getFullHeight();
        
    camera->getProjection(result, width, height);
    
    Real32 left   = getLeft  ();
    Real32 right  = getRight ();
    Real32 top    = getTop   ();
    Real32 bottom = getBottom();
           
    if(left < 0)
        left = -left / width;
        
    if(right < 0)
        right = -right / width;
        
    if(top < 0)
        top = -top / height;
        
    if(bottom < 0)
        bottom = -bottom / height;

    // scale the wanted part from the projection matrix
    Real32 xs = 1.f / (right - left  );
    Real32 ys = 1.f / (top   - bottom);

    Matrix sm(xs,  0, 0, -(left*2-1)*xs-1,  
               0, ys, 0, -(bottom*2-1)*ys-1,  
               0,  0, 1, 0, 
               0,  0, 0, 1);
    
    result.multLeft(sm);
}                                       

/*! Get/calculate the decoration matrix for this camera. 
    The default is identity.
*/

void TileCameraDecorator::getDecoration(Matrix &result, 
										UInt32  width, 
                                        UInt32  height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }

    Camera *camera = getDecoratee();

    if(camera == NULL)
    {
        FWARNING(("TileCameraDecorator::getProjection: no decoratee!\n"));

        result.setIdentity();

        return;
    }

    if(getFullWidth() != 0)
        width = getFullWidth();
    
    if(getFullHeight() != 0)
        height = getFullHeight();
	
	// this is the only difference to getProjection()
    camera->getDecoration(result, width, height);

    Real32 left   = getLeft  ();
    Real32 right  = getRight ();
    Real32 top    = getTop   ();
    Real32 bottom = getBottom();
           
    if(left < 0)
        left = -left / width;
        
    if(right < 0)
        right = -right / width;
        
    if(top < 0)
        top = -top / height;
        
    if(bottom < 0)
        bottom = -bottom / height;

    // scale the wanted part from the decoration matrix
    Real32 xs = 1.f / (right - left);
    Real32 ys = 1.f / (top - bottom);

    Matrix sm(  xs,  0, 0, -(left   * 2 - 1) * xs - 1,  
                 0, ys, 0, -(bottom * 2 - 1) * ys - 1,  
                 0,  0, 1, 0, 
                 0,  0, 0, 1);
    
    result.multLeft(sm);
}

/*------------------------------- dump ----------------------------------*/

void TileCameraDecorator::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                               const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TileCameraDecorator NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */
