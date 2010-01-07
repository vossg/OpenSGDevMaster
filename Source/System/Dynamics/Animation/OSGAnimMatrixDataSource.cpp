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

#include "OSGAnimMatrixDataSource.h"
#include "OSGAnimMatrixChannel.h"
#include "OSGAnimMatrixBlender.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimMatrixDataSourceBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimMatrixDataSource.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimMatrixDataSource::initMethod(InitPhase ePhase)
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

AnimMatrixDataSource::AnimMatrixDataSource(void) :
    Inherited()
{
}

AnimMatrixDataSource::AnimMatrixDataSource(const AnimMatrixDataSource &source) :
    Inherited(source)
{
}

AnimMatrixDataSource::~AnimMatrixDataSource(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimMatrixDataSource::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

AnimChannelTransitPtr
AnimMatrixDataSource::createChannel(void) const
{
    AnimMatrixChannelUnrecPtr channel = AnimMatrixChannel::create();
    channel->setData(const_cast<AnimMatrixDataSource *>(this));

    return AnimChannelTransitPtr(channel);
}

AnimBlenderTransitPtr
AnimMatrixDataSource::createBlender(void) const
{
    AnimMatrixBlenderUnrecPtr blender = AnimMatrixBlender::create();

    return AnimBlenderTransitPtr(blender);
}

void AnimMatrixDataSource::evaluate(Matrix &outValue, Real32 inValue)
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
        SWARNING << "AnimMatrixDataSource: Unknown interpolation mode ["
                 << im << "] - using IM_Linear [" << IM_Linear << "]"
                 << std::endl;
        evalLinear(outValue, _mfInValues.front() + inValue, ivIt);
        break;
    }
}

void AnimMatrixDataSource::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimMatrixDataSource NI" << std::endl;
}

void AnimMatrixDataSource::evalStep(
    Matrix &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
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

void AnimMatrixDataSource::evalLinear(
    Matrix &outValue, Real32 inValue, MFInValuesType::const_iterator ivRIt)
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

            outValue = *vLIt;
            outValue.scale    (1.f - s );
            outValue.addScaled(*vRIt, s);
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

void AnimMatrixDataSource::extrapolateFront(Matrix &outValue, Real32 inValue)
{
    outValue = _mfValues.front();
}

void AnimMatrixDataSource::extrapolateBack(Matrix &outValue, Real32 inValue)
{
    outValue = _mfValues.back();
}

OSG_END_NAMESPACE
