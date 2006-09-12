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

#include "OSGTileCameraDecorator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TileCameraDecorator
    \ingroup GrpSystemWindowCameraDecorators

  The OSG::TileCameraDecorator for selecting only a part of a virtual large
  image, see \ref
  PageSystemWindowCameraDecoratorsTile for a description.
  
  The borders of the tile are defined by the _sfLeft, _sfRight, _sfBottom and
  _sfTop Fields. The size of the full image is defined by the _sfFullWidth and
  _sfFullHeight Fields.

*/

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

void TileCameraDecorator::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
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
    
    if(getFullWidth() != 0)
        width = getFullWidth();
    
    if(getFullHeight() != 0)
        height = getFullHeight();
        
    getDecoratee()->getProjection(result, width, height);
    
    Real32 left   = getLeft(),
           right  = getRight(),
           top    = getTop(),
           bottom = getBottom();
           
    if(left < 0)
        left = -left / width;
        
    if(right < 0)
        right = -right / width;
        
    if(top < 0)
        top = -top / height;
        
    if(bottom < 0)
        bottom = -bottom / height;

    // scale the wanted part from the projection matrix
    Real32  xs = 1.f / (right - left),
            ys = 1.f / (top - bottom);

    Matrix sm(xs,  0, 0, -(left*2-1)*xs-1,  
               0, ys, 0, -(bottom*2-1)*ys-1,  
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

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGTILECAMERADECORATOR_HEADER_CVSID;
    static char cvsid_inl[] = OSGTILECAMERADECORATOR_INLINE_CVSID;
}
