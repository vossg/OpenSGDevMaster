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

#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fBlender.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimVec3fDataSourceBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimVec3fDataSource.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimVec3fDataSource::initMethod(InitPhase ePhase)
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

AnimVec3fDataSource::AnimVec3fDataSource(void) :
    Inherited()
{
}

AnimVec3fDataSource::AnimVec3fDataSource(const AnimVec3fDataSource &source) :
    Inherited(source)
{
}

AnimVec3fDataSource::~AnimVec3fDataSource(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimVec3fDataSource::changed(ConstFieldMaskArg whichField, 
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
AnimVec3fDataSource::createChannel(void) const
{
    AnimVec3fChannelUnrecPtr channel = AnimVec3fChannel::create();
    channel->setData(const_cast<AnimVec3fDataSource *>(this));

    return AnimChannelTransitPtr(channel);
}

AnimBlenderTransitPtr
AnimVec3fDataSource::createBlender(void) const
{
    AnimVec3fBlenderUnrecPtr blender = AnimVec3fBlender::create();
    
    return AnimBlenderTransitPtr(blender);
}

void AnimVec3fDataSource::evaluate(Vec3f &outValue, Real32 inValue)
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
        SWARNING << "AnimVec3fDataSource: Unkown interpolation mode ["
                 << im << "] - using IM_Linear [" << IM_Linear << "]"
                 << std::endl;
        evalLinear(outValue, _mfInValues.front() + inValue, ivIt);
        break;
    }
}

void AnimVec3fDataSource::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimVec3fDataSource NI" << std::endl;
}

void AnimVec3fDataSource::evalStep(
    Vec3f &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
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

void AnimVec3fDataSource::evalLinear(
    Vec3f &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
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

            outValue =  *vRIt - *vLIt;
            outValue *= s;
            outValue += *vLIt;
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

void AnimVec3fDataSource::extrapolateFront(Vec3f &outValue, Real32 inValue)
{
    outValue = _mfValues.front();
}

void AnimVec3fDataSource::extrapolateBack(Vec3f &outValue, Real32 inValue)
{
    outValue = _mfValues.back();
}

void AnimVec3fDataSource::checkDataConsistency(void)
{
    if(_mfInValues.size() != _mfValues.size())
    {
        SWARNING << "AnimVec3fDataSource: "
                 << "MFInValues and MFValues sizes inconsistent." << std::endl;
    }

    if(_mfInterpolationModes.size() != 1 &&
       _mfInterpolationModes.size() != _mfInValues.size())
    {
        SWARNING << "AnimVec3fDataSource: "
                 << "MFInterpolationModes invalid." << std::endl;
    }
}

OSG_END_NAMESPACE
