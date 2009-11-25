/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaAnimationClip.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaElementFactory.h"
#include "OSGColladaInstanceAnimation.h"

#include <dom/domAnimation_clip.h>

OSG_BEGIN_NAMESPACE

// ===========================================================================

ColladaInstInfoTransitPtr
ColladaAnimationClip::ColladaAnimationInstInfo::create(
    ColladaAnimationClip *colInstParent, ColladaInstanceAnimation *colInst)
{
    return ColladaInstInfoTransitPtr(
        new ColladaAnimationInstInfo(colInstParent, colInst));
}

void
ColladaAnimationClip::ColladaAnimationInstInfo::process(void)
{
    ColladaAnimationClip *colAnimClip =
        dynamic_cast<ColladaAnimationClip *>(getColInstParent());

    colAnimClip->handleInstanceAnimation(this);
}

ColladaAnimationClip::ColladaAnimationInstInfo::ColladaAnimationInstInfo(
    ColladaAnimationClip *colInstParent, ColladaInstanceAnimation *colInst)

    : Inherited(colInstParent, colInst, NULL)
{
}

ColladaAnimationClip::ColladaAnimationInstInfo::~ColladaAnimationInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaAnimationClip::_regHelper(
    &ColladaAnimationClip::create, "animation_clip");


ColladaElementTransitPtr
ColladaAnimationClip::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaAnimationClip(elem, global));
}

void
ColladaAnimationClip::read(ColladaElement *colElemParent)
{
    domAnimation_clipRef animClip = getDOMElementAs<domAnimation_clip>();

    OSG_COLLADA_LOG(("ColladaAnimationClip::read: id [%s]\n",
                     (animClip->getId() != NULL ? animClip->getId() : "")));

    const domInstanceWithExtra_Array &animInsts =
        animClip->getInstance_animation_array();

    for(UInt32 i = 0; i < animInsts.getCount(); ++i)
    {
        ColladaInstanceAnimationRefPtr colInstAnim =
            getUserDataAs<ColladaInstanceAnimation>(animInsts[i]);

        if(colInstAnim == NULL)
        {
            colInstAnim = dynamic_pointer_cast<ColladaInstanceAnimation>(
                ColladaElementFactory::the()->create(
                    animInsts[i], getGlobal(), "instance_animation"));

            colInstAnim->read(this);
        }

        ColladaInstInfoRefPtr animInstInfo =
            ColladaAnimationInstInfo::create(this, colInstAnim);

        getGlobal()->editInstQueue().push_back(animInstInfo);
    }
}

ColladaAnimationClip::ColladaAnimationClip(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaAnimationClip::~ColladaAnimationClip(void)
{
}

void
ColladaAnimationClip::handleInstanceAnimation(ColladaInstInfo *instInfo)
{
    OSG_COLLADA_LOG(("ColladaAnimationClip::handleInstanceAnimation\n"));

    ColladaAnimationInstInfo *animInstInfo =
        dynamic_cast<ColladaAnimationInstInfo *>(instInfo);

    OSG_ASSERT(instInfo                                != NULL);
    OSG_ASSERT(instInfo->getColInst()                  != NULL);
    OSG_ASSERT(instInfo->getColInst()->getTargetElem() != NULL);

    // XXX TODO: what to do with the instance ??

    animInstInfo->getColInst()->getTargetElem()->createInstance(
        animInstInfo->getColInstParent(), animInstInfo->getColInst());
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
