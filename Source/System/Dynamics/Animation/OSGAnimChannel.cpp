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

#include "OSGAnimChannel.h"
#include "OSGAnimation.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimChannelBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimChannel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimChannel::initMethod(InitPhase ePhase)
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

AnimChannel::AnimChannel(void) :
    Inherited()
{
}

AnimChannel::AnimChannel(const AnimChannel &source) :
    Inherited(source)
{
}

AnimChannel::~AnimChannel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimChannel::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    if(0 != ((WeightFieldMask | InValueFieldMask)  & whichField))
    {
        this->evaluate();
    }

    Inherited::changed(whichField, origin, details);
}

/*! Returns if this channel is enabled. Only enabled channels are
    considered when blending animation data.

    This is a convenience function that returns the parent animation status.
 */
bool AnimChannel::getEnabled(void) const
{
    bool retVal = false;

    if(_sfAnimation.getValue() != NULL)
    {
        retVal = _sfAnimation.getValue()->getEnabled();
    }

    return retVal;
}

void AnimChannel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimChannel NI" << std::endl;
}

OSG_END_NAMESPACE
