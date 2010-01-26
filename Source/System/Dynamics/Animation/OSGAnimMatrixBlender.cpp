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

#include "OSGAnimMatrixBlender.h"
#include "OSGAnimMatrixChannel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimMatrixBlenderBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimMatrixBlender.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimMatrixBlender::initMethod(InitPhase ePhase)
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

AnimMatrixBlender::AnimMatrixBlender(void) :
    Inherited()
{
}

AnimMatrixBlender::AnimMatrixBlender(const AnimMatrixBlender &source) :
    Inherited(source)
{
}

AnimMatrixBlender::~AnimMatrixBlender(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimMatrixBlender::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

bool AnimMatrixBlender::init(void)
{
    return Inherited::init();
}

void AnimMatrixBlender::frame(Time oTime, UInt32 uiFrame)
{
    bool   activeChannels = false;
    Matrix blendValue;
    MFChannelsType::const_iterator cIt  = _mfChannels.begin();
    MFChannelsType::const_iterator cEnd = _mfChannels.end  ();

    for(; cIt != cEnd; ++cIt)
    {
        if((*cIt)->getEnabled() == true)
        {
            if(activeChannels == false)
            {
                blendValue =     (*cIt)->getOutValue();
                blendValue.scale((*cIt)->getWeight  ());
            }
            else
            {
                blendValue.addScaled((*cIt)->getOutValue(),
                                     (*cIt)->getWeight  () );
            }

            activeChannels = true;
        }
    }

    if(activeChannels == true)
        setOutValue(blendValue);
}

void AnimMatrixBlender::shutdown(void)
{
    Inherited::shutdown();
}

void AnimMatrixBlender::addChannel(AnimChannel *channel)
{
    AnimMatrixChannel *matChannel = dynamic_cast<AnimMatrixChannel *>(channel);

    if(matChannel == NULL)
    {
        SWARNING << "AnimMatrixBlender::addChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    pushToChannels(matChannel);
}

void AnimMatrixBlender::subChannel(AnimChannel *channel)
{
    AnimMatrixChannel *matChannel = dynamic_cast<AnimMatrixChannel *>(channel);

    if(matChannel == NULL)
    {
        SWARNING << "AnimMatrixBlender::subChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    removeObjFromChannels(matChannel);
}

void AnimMatrixBlender::connectTo(
    AttachmentContainer *container, const std::string &fieldName)
{
    FDEBUG(("AnimMatrixBlender::connectTo: this [%p] target [%p] [%s]\n",
            this, container, fieldName.c_str()));

    addConnection(this, "outValue", container, fieldName.c_str());
}

void AnimMatrixBlender::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimMatrixBlender NI" << std::endl;
}

OSG_END_NAMESPACE
