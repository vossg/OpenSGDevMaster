/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include "OSGConfig.h"

#include "OSGCSMPerspectiveCamera.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCSMPerspectiveCameraBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMPerspectiveCamera.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CSMPerspectiveCamera::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSMPerspectiveCamera::CSMPerspectiveCamera(void) :
    Inherited()
{
}

CSMPerspectiveCamera::CSMPerspectiveCamera(const CSMPerspectiveCamera &source) :
    Inherited(source)
{
}

CSMPerspectiveCamera::~CSMPerspectiveCamera(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CSMPerspectiveCamera::changed(ConstFieldMaskArg whichField, 
                                   UInt32            origin,
                                   BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & FovFieldMask))
    {
        if(_sfFov.getValue() > 2 * Pi)
        {
            _sfFov.setValue(osgDegree2Rad(_sfFov.getValue()));
        }
    }
}

void CSMPerspectiveCamera::dump(      UInt32    ,
                                const BitVector ) const
{
    SLOG << "Dump CSMPerspectiveCamera NI" << std::endl;
}

OSG_END_NAMESPACE
