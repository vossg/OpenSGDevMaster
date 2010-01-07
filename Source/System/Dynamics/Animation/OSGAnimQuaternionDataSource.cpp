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

#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimQuaternionChannel.h"
#include "OSGAnimQuaternionBlender.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimQuaternionDataSourceBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimQuaternionDataSource.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimQuaternionDataSource::initMethod(InitPhase ePhase)
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

AnimQuaternionDataSource::AnimQuaternionDataSource(void) :
    Inherited()
{
}

AnimQuaternionDataSource::AnimQuaternionDataSource(const AnimQuaternionDataSource &source) :
    Inherited(source)
{
}

AnimQuaternionDataSource::~AnimQuaternionDataSource(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimQuaternionDataSource::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(0 != ((InValuesFieldMask           |
              ValuesFieldMask             |
              InterpolationModesFieldMask  ) & whichField))
    {
        checkDataConsistency();
    }

    Inherited::changed(whichField, origin, details);
}

AnimChannelTransitPtr
AnimQuaternionDataSource::createChannel(void) const
{
    AnimQuaternionChannelUnrecPtr channel = AnimQuaternionChannel::create();
    channel->setData(const_cast<AnimQuaternionDataSource *>(this));

    return AnimChannelTransitPtr(channel);
}

AnimBlenderTransitPtr
AnimQuaternionDataSource::createBlender(void) const
{
    AnimQuaternionBlenderUnrecPtr blender = AnimQuaternionBlender::create();

    return AnimBlenderTransitPtr(blender);
}

void
AnimQuaternionDataSource::evaluate(Quaternion &outValue, Real32 inValue)
{
    MFInValuesType::const_iterator ivIt =
        std::lower_bound(_mfInValues.begin(),
                         _mfInValues.end  (),
                         _mfInValues.front() + inValue);

    InterpolationModeE im = IM_Linear;

    if(_mfInterpolationModes.size() == 1)
    {
        im = InterpolationModeE(_mfInterpolationModes.front());
    }
    else if(_mfInterpolationModes.size() == _mfInValues.size())
    {
        MFInterpolationModesType::const_iterator imIt =
            _mfInterpolationModes.begin();
        std::advance(imIt, ivIt - _mfInValues.begin());

        im = InterpolationModeE(*imIt);
    }

    switch(im)
    {
    case IM_Step:
        evalStep(outValue, _mfInValues.front() + inValue, ivIt);
        break;

    case IM_Linear:
        evalLinear(outValue, _mfInValues.front() + inValue, ivIt);
        break;

    default:
        SWARNING << "AnimQuaternionDataSource: Unknown interpolation mode ["
                 << im << "] - using IM_Linear [" << IM_Linear << "]"
                 << std::endl;
        evalLinear(outValue, _mfInValues.front() + inValue, ivIt);
        break;
    }
}

void AnimQuaternionDataSource::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimQuaternionDataSource NI" << std::endl;
}

void
AnimQuaternionDataSource::evalStep(
    Quaternion &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
{
    if(ivRIt != _mfInValues.end())
    {
        if(ivRIt != _mfInValues.begin())
        {
            MFValuesType::const_iterator vIt = _mfValues.begin();
            std::advance(vIt, ivRIt - _mfInValues.begin());

            outValue = *vIt;
        }
        else
        {
            extrapolateFront(outValue, inValue);
        }
    }
    else
    {
        extrapolateBack(outValue, inValue);
    }
}

void AnimQuaternionDataSource::evalLinear(
    Quaternion &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
{
    if(ivRIt != _mfInValues.end())
    {
        if(ivRIt != _mfInValues.begin())
        {
            MFInValuesType::const_iterator ivLIt = ivRIt - 1;

            MFValuesType  ::const_iterator vRIt  = _mfValues.begin();
            MFValuesType  ::const_iterator vLIt  = _mfValues.begin();
            std::advance(vRIt, ivRIt - _mfInValues.begin());
            std::advance(vLIt, ivLIt - _mfInValues.begin());

            Real32 s = (inValue - *ivLIt) / (*ivRIt - *ivLIt);

            outValue.slerpThis(*vLIt, *vRIt, s);
        }
        else
        {
            extrapolateFront(outValue, inValue);
        }
    }
    else
    {
        extrapolateBack(outValue, inValue);
    }
}

void AnimQuaternionDataSource::extrapolateFront(
    Quaternion &outValue, Real32 inValue)
{
    outValue = _mfValues.front();
}

void AnimQuaternionDataSource::extrapolateBack(
    Quaternion &outValue, Real32 inValue)
{
    outValue = _mfValues.back();
}

void AnimQuaternionDataSource::checkDataConsistency(void)
{
    if(_mfInValues.size() != _mfValues.size())
    {
        SWARNING << "AnimQuaternionDataSource: "
                 << "MFInValues and MFValues sizes inconsistent." << std::endl;
    }

    if(_mfInterpolationModes.size() != 1 &&
       _mfInterpolationModes.size() != _mfInValues.size())
    {
        SWARNING << "AnimQuaternionDataSource: "
                 << "MFInterpolationModes invalid." << std::endl;
    }
}

OSG_END_NAMESPACE
