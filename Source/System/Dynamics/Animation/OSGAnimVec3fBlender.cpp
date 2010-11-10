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

#include "OSGAnimVec3fBlender.h"
#include "OSGAnimVec3fChannel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimVec3fBlenderBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimVec3fBlender.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimVec3fBlender::initMethod(InitPhase ePhase)
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

AnimVec3fBlender::AnimVec3fBlender(void) :
    Inherited()
{
}

AnimVec3fBlender::AnimVec3fBlender(const AnimVec3fBlender &source) :
    Inherited(source)
{
}

AnimVec3fBlender::~AnimVec3fBlender(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimVec3fBlender::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

bool AnimVec3fBlender::init(void)
{
    return Inherited::init();
}

void AnimVec3fBlender::frame(Time oTime, UInt32 uiFrame)
{
    FDEBUG(("AnimVec3fBlender::frame: time [%f] frame [%d]\n",
            oTime, uiFrame));

    bool  activeChannels = false;
    Vec3f blendValue;
    MFChannelsType::const_iterator cIt  = _mfChannels.begin();
    MFChannelsType::const_iterator cEnd = _mfChannels.end  ();

    for(UInt32 i = 0; cIt != cEnd; ++cIt, ++i)
    {
        if((*cIt)->getEnabled() == true)
        {
            activeChannels  = true;
            blendValue     += (*cIt)->getWeight() * (*cIt)->getOutValue();

            // FLOG((" channel [%u] - w [%f] v [%f %f %f] - b [%f %f %f]\n",
            //       i, (*cIt)->getWeight(),
            //       (*cIt)->getOutValue()[0], (*cIt)->getOutValue()[1], (*cIt)->getOutValue()[2],
            //       blendValue[0], blendValue[1], blendValue[2]));
        }
    }

    if(activeChannels == true)
        setOutValue(blendValue);
}

void AnimVec3fBlender::shutdown(void)
{
    Inherited::shutdown();
}

void AnimVec3fBlender::addChannel(AnimChannel *channel)
{
    AnimVec3fChannel *matChannel = dynamic_cast<AnimVec3fChannel *>(channel);

    if(matChannel == NULL)
    {
        SWARNING << "AnimVec3fBlender::addChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    pushToChannels(matChannel);
}

void AnimVec3fBlender::subChannel(AnimChannel *channel)
{
    AnimVec3fChannel *matChannel = dynamic_cast<AnimVec3fChannel *>(channel);

    if(matChannel == NULL)
    {
        SWARNING << "AnimVec3fBlender::subChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    removeObjFromChannels(matChannel);
}

void AnimVec3fBlender::connectTo(
    AttachmentContainer *container, const std::string &fieldName)
{
    FDEBUG(("AnimVec3fBlender::connectTo: this [%p] target [%p] [%s]\n",
            this, container, fieldName.c_str()));

    addConnection(this, "outValue", container, fieldName.c_str());
}

void AnimVec3fBlender::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimVec3fBlender NI" << std::endl;
}

OSG_END_NAMESPACE
