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

#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimation.h"
#include "OSGAnimBindAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAnimKeyFrameTemplateBase.cpp file.
// To modify it, please change the .fcd file (OSGAnimKeyFrameTemplate.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnimKeyFrameTemplate::initMethod(InitPhase ePhase)
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

AnimKeyFrameTemplate::AnimKeyFrameTemplate(void) :
    Inherited()
{
}

AnimKeyFrameTemplate::AnimKeyFrameTemplate(const AnimKeyFrameTemplate &source) :
    Inherited(source)
{
}

AnimKeyFrameTemplate::~AnimKeyFrameTemplate(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnimKeyFrameTemplate::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

AnimationTransitPtr
AnimKeyFrameTemplate::instantiate(Node *rootNode)
{
    AnimTimeSensorUnrecPtr ts   = AnimTimeSensor::create();
    AnimationUnrecPtr      anim = Animation     ::create();

    anim->setTimeSensor(ts  );
    anim->setTemplate  (this);
    
    AnimBindAction *bindAct = AnimBindAction::create();

    bindAct->setTemplate(this);
    bindAct->setAnim    (anim);

    bindAct->apply(rootNode);

    delete bindAct;

    return AnimationTransitPtr(anim);
}


void AnimKeyFrameTemplate::dump(      UInt32    uiIndent,
                                const BitVector bvFlags  ) const
{
    Inherited::dump(uiIndent, bvFlags);
}

OSG_END_NAMESPACE
