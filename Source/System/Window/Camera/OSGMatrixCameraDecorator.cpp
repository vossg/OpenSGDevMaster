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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGMatrixCameraDecorator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MatrixCameraDecorator
    \ingroup GrpSystemWindowCameraDecorators

  The decorator to modify the Camera matrices simply by matrices. 	
  
  The OSG::MatrixCameraDecorator for madifying the camera matrices by 
  matrices, see \ref
  PageSystemWindowCameraDecoratorsMatrix for a description.
  
  The matrices to use are defined by the _sf Fields. The size of the full
  image is defined by the _sfFullWidth and
  _sfFullHeight Fields.
*/

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
                                    UInt32            origin    )
{
    Inherited::changed(whichField, origin);
}


void MatrixCameraDecorator::getProjection(Matrix &result, 
                                          UInt32  width, 
                                          UInt32  height)
{        
    getDecoratee()->getProjection(result, width, height);
    
    result.multLeft(getPostProjection());
    result.mult    (getPreProjection ());
}                                       

void MatrixCameraDecorator::getProjectionTranslation(Matrix &result, 
                                                     UInt32  width, 
                                                     UInt32  height)
{        
    getDecoratee()->getProjectionTranslation(result, width, height);
    
    result.multLeft(getPostProjectionTranslation());
    result.mult    (getPreProjectionTranslation ());
}                                       

void MatrixCameraDecorator::getViewing(Matrix &result, 
                                       UInt32  width,
                                       UInt32  height)
{        
    getDecoratee()->getViewing(result, width, height);
    
    result.multLeft(getPostViewing());
    result.mult    (getPreViewing ());
}                                       

void MatrixCameraDecorator::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump MatrixCameraDecorator NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = 
                                   OSGMATRIXCAMERADECORATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = 
                                   OSGMATRIXCAMERADECORATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = 
                                   OSGMATRIXCAMERADECORATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

