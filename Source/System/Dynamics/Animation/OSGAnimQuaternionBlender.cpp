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

#include "OSGAnimQuaternionBlender.h"
#include "OSGAnimQuaternionChannel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimQuaternionBlenderBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimQuaternionBlender.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimQuaternionBlender::initMethod(InitPhase ePhase)
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

AnimQuaternionBlender::AnimQuaternionBlender(void) :
    Inherited()
{
}

AnimQuaternionBlender::AnimQuaternionBlender(const AnimQuaternionBlender &source) :
    Inherited(source)
{
}

AnimQuaternionBlender::~AnimQuaternionBlender(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimQuaternionBlender::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

bool AnimQuaternionBlender::init(void)
{
    return Inherited::init();
}

void AnimQuaternionBlender::frame(Time oTime, UInt32 uiFrame)
{
    bool       activeChannels = false;
    Quaternion blendValue;
    MFChannelsType::const_iterator cIt  = _mfChannels.begin();
    MFChannelsType::const_iterator cEnd = _mfChannels.end  ();

    for(UInt32 i = 0; cIt != cEnd; ++cIt, ++i)
    {
        if((*cIt)->getEnabled() == true)
        {
            activeChannels = true;

            Quaternion temp((*cIt)->getOutValue());
            temp.scaleAngle((*cIt)->getWeight  ());

            //blendValue += temp;
            blendValue.mult(temp);

            // FLOG((" channel [%u] - w [%f] v [%f %f %f %f] - b [%f %f %f %f]\n",
            //       i, (*cIt)->getWeight(),
            //       (*cIt)->getOutValue()[0], (*cIt)->getOutValue()[1], (*cIt)->getOutValue()[2], (*cIt)->getOutValue()[3],
            //       blendValue[0], blendValue[1], blendValue[2], blendValue[3]));
        }
    }

    if(activeChannels == true)
    {
        blendValue.normalize();

        setOutValue(blendValue);
    }
}

void AnimQuaternionBlender::shutdown(void)
{
    Inherited::shutdown();
}

void AnimQuaternionBlender::addChannel(AnimChannel *channel)
{
    AnimQuaternionChannel *quatChannel =
        dynamic_cast<AnimQuaternionChannel *>(channel);

    if(quatChannel == NULL)
    {
        SWARNING << "AnimQuaternionBlender::addChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    pushToChannels(quatChannel);
}

void AnimQuaternionBlender::subChannel(AnimChannel *channel)
{
    AnimQuaternionChannel *quatChannel =
        dynamic_cast<AnimQuaternionChannel *>(channel);

    if(quatChannel == NULL)
    {
        SWARNING << "AnimQuaternionBlender::subChannel: Channel type mismatch"
                 << std::endl;
        return;
    }

    removeObjFromChannels(quatChannel);
}

void AnimQuaternionBlender::connectTo(
    AttachmentContainer *container, const std::string &fieldName)
{
    FDEBUG(("AnimQuaternionBlender::connectTo: this [%p] target [%p] [%s]\n",
            this, container, fieldName.c_str()));

    addConnection(this, "outValue", container, fieldName.c_str());
}

void AnimQuaternionBlender::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AnimQuaternionBlender NI" << std::endl;
}

OSG_END_NAMESPACE
