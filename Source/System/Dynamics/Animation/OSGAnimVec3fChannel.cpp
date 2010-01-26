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

#include <OSGConfig.h>

#include "OSGAnimVec3fChannel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimVec3fChannelBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimVec3fChannel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimVec3fChannel::initMethod(InitPhase ePhase)
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

AnimVec3fChannel::AnimVec3fChannel(void) :
    Inherited()
{
}

AnimVec3fChannel::AnimVec3fChannel(const AnimVec3fChannel &source) :
    Inherited(source)
{
}

AnimVec3fChannel::~AnimVec3fChannel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimVec3fChannel::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AnimVec3fChannel::evaluate(void)
{
    if(getEnabled() == false)
        return;

    if(_sfData.getValue() != NULL)
    {
        editSField(OutValueFieldMask);

        _sfData.getValue()->evaluate(_sfOutValue.getValue(),
                                     _sfInValue .getValue() );
    }
    else
    {
        SWARNING << "AnimVec3fChannel::evaluate: No AnimData."
                 << std::endl;
    }
}

void AnimVec3fChannel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimVec3fChannel NI" << std::endl;
}

OSG_END_NAMESPACE
