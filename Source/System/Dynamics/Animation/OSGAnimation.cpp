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

#include "OSGAnimation.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimationBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimation.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Animation::initMethod(InitPhase ePhase)
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

Animation::Animation(void) :
    Inherited()
{
}

Animation::Animation(const Animation &source) :
    Inherited(source)
{
}

Animation::~Animation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Animation::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    if(0 != ((WeightFieldMask | ChannelsFieldMask) & whichField))
    {
        MFChannelsType::const_iterator cIt  = _mfChannels.begin();
        MFChannelsType::const_iterator cEnd = _mfChannels.end  ();

        for(; cIt != cEnd; ++cIt)
        {
            (*cIt)->setWeight(_sfWeight.getValue());
        }
    }

    Inherited::changed(whichField, origin, details);
}

void Animation::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Animation NI" << std::endl;
}

void Animation::setTimeSensor(TimeSensor *value)
{
    if(_sfTimeSensor.getValue() == value)
        return;

    if(_sfTimeSensor.getValue() != NULL)
    {
        _sfTimeSensor.getValue()->subChangedFunctor(
            boost::bind(&Animation::timeSensorChanged, this, _1, _2));
    }

    Inherited::setTimeSensor(value);

    if(_sfTimeSensor.getValue() != NULL)
    {
        _sfTimeSensor.getValue()->addChangedFunctor(
            boost::bind(&Animation::timeSensorChanged, this, _1, _2), "");
    }
}

TimeSensor *Animation::getTimeSensor(void) const
{
    return Inherited::getTimeSensor();
}


void Animation::timeSensorChanged(FieldContainer *fc, BitVector whichField)
{
    TimeSensor *ts = _sfTimeSensor.getValue();

    OSG_ASSERT(fc == ts);

    if(0 != (TimeSensor::TimeFieldMask & whichField))
    {
        // sensor is active or just changed to inactive
        if(true == ts->getIsActive()                           ||
           0    != (TimeSensor::IsActiveFieldMask & whichField)   )
        {
            MFChannelsType::const_iterator cIt  = _mfChannels.begin();
            MFChannelsType::const_iterator cEnd = _mfChannels.end  ();
            
            for(; cIt != cEnd; ++cIt)
            {
                SLOG << "Animation::timeSensorChanged: "
                     << (ts->getFraction() * ts->getCycleInterval())
                     << std::endl;

                (*cIt)->setInValue(ts->getFraction() * ts->getCycleInterval());
            }
        }
    }
}


OSG_END_NAMESPACE
