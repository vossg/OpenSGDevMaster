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

#include "OSGCameraDecorator.h"

OSG_USING_NAMESPACE

/*! \class osg::CameraDecorator
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

void CameraDecorator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CameraDecorator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CameraDecorator NI" << std::endl;
}


/*---------------------- Decorated Functions ----------------------------*/


void CameraDecorator::draw(      DrawAction *action, 
                           const Viewport   &port  )
{
    getDecoratee()->draw(action, port);
}

void CameraDecorator::getProjection(Matrix &result,
                                    UInt32  width ,
                                    UInt32  height)
{
    getDecoratee()->getProjection(result, width, height);
}

void CameraDecorator::getProjectionTranslation(Matrix &result, 
                                               UInt32  width , 
                                               UInt32  height)
{
    getDecoratee()->getProjectionTranslation(result, width, height);
}

void CameraDecorator::getViewing(Matrix &result, 
                                 UInt32  width , 
                                 UInt32  height)
{
    getDecoratee()->getViewing(result, width, height);
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
    static char cvsid_hpp[] = OSGCAMERADECORATOR_HEADER_CVSID;
    static char cvsid_inl[] = OSGCAMERADECORATOR_INLINE_CVSID;
}
