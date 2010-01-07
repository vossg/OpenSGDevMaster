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
#if !defined(OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK)

ColladaInstInfoTransitPtr
ColladaAnimationClip::ColladaAnimationInstInfo::create(
    ColladaAnimationClip     *colInstParent,
    ColladaInstanceAnimation *colInst,
    AnimKeyFrameTemplate     *animTmpl)
{
    return ColladaInstInfoTransitPtr(
        new ColladaAnimationInstInfo(colInstParent, colInst, animTmpl));
}

void
ColladaAnimationClip::ColladaAnimationInstInfo::process(void)
{
    ColladaAnimationClip *colAnimClip =
        dynamic_cast<ColladaAnimationClip *>(getColInstParent());

    colAnimClip->handleInstanceAnimation(this);
}

AnimKeyFrameTemplate *
ColladaAnimationClip::ColladaAnimationInstInfo::getTemplate(void) const
{
    return _animTmpl;
}

ColladaAnimationClip::ColladaAnimationInstInfo::ColladaAnimationInstInfo(
    ColladaAnimationClip     *colInstParent,
    ColladaInstanceAnimation *colInst,
    AnimKeyFrameTemplate     *animTmpl)

    : Inherited(colInstParent, colInst, NULL)
    , _animTmpl(animTmpl)
{
}

ColladaAnimationClip::ColladaAnimationInstInfo::~ColladaAnimationInstInfo(void)
{
}

#else
// ===========================================================================

ColladaInstInfoTransitPtr
ColladaAnimationClip::ColladaAnimationInstInfo::create(
    ColladaAnimationClip     *colInstParent,
    ColladaInstanceAnimation *colInst,
    ColladaAnimation         *colAnim,
    AnimKeyFrameTemplate     *animTmpl)
{
    return ColladaInstInfoTransitPtr(
        new ColladaAnimationInstInfo(colInstParent, colInst,
                                     colAnim,       animTmpl));
}

void
ColladaAnimationClip::ColladaAnimationInstInfo::process(void)
{
    ColladaAnimationClip *colAnimClip =
        dynamic_cast<ColladaAnimationClip *>(getColInstParent());

    colAnimClip->handleInstanceAnimation(this);
}

ColladaAnimation *
ColladaAnimationClip::ColladaAnimationInstInfo::getAnim(void) const
{
    return _colAnim;
}

AnimKeyFrameTemplate *
ColladaAnimationClip::ColladaAnimationInstInfo::getTemplate(void) const
{
    return _animTmpl;
}

ColladaAnimationClip::ColladaAnimationInstInfo::ColladaAnimationInstInfo(
    ColladaAnimationClip *colInstParent, ColladaInstanceAnimation *colInst,
    ColladaAnimation     *colAnim,       AnimKeyFrameTemplate     *animTmpl)

    : Inherited(colInstParent, colInst, NULL)
    , _colAnim (colAnim                     )
    , _animTmpl(animTmpl                    )
{
}

ColladaAnimationClip::ColladaAnimationInstInfo::~ColladaAnimationInstInfo(void)
{
}

#endif // OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK

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

#if !defined(OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK)

    AnimKeyFrameTemplateUnrecPtr animTmpl = AnimKeyFrameTemplate::create();
    getGlobal()->getGlobalsAtt()->editMFElements()->push_back(animTmpl);

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
            ColladaAnimationInstInfo::create(this, colInstAnim, animTmpl);

        getGlobal()->editInstQueue().push_back(animInstInfo);
    }

#else

    // add anim template to the globals attachment
    AnimKeyFrameTemplateUnrecPtr animTmpl = AnimKeyFrameTemplate::create();
    getGlobal()->getGlobalsAtt()->editMFElements()->push_back(animTmpl);

    domCOLLADA *docRoot = getGlobal()->getDocRoot();
    const domLibrary_animations_Array &libAnims =
        docRoot->getLibrary_animations_array();

    for(UInt32 i = 0; i < libAnims.getCount(); ++i)
    {
        const domAnimation_Array &anims = libAnims[i]->getAnimation_array();

        for(UInt32 j = 0; j < anims.getCount(); ++j)
        {
            ColladaAnimationRefPtr colAnim =
                getUserDataAs<ColladaAnimation>(anims[j]);

            if(colAnim == NULL)
            {
                colAnim = dynamic_pointer_cast<ColladaAnimation>(
                    ColladaElementFactory::the()->create(
                        anims[j], getGlobal(), "animation"));

                colAnim->read(this);
            }

            // queue an instance
            ColladaInstInfoRefPtr animInstInfo =
                ColladaAnimationInstInfo::create(this,    NULL,
                                                 colAnim, animTmpl);

            getGlobal()->editInstQueue().push_back(animInstInfo);
        }
    }
#endif // OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK
}

void
ColladaAnimationClip::setCurrTemplate(AnimKeyFrameTemplate *animTmpl)
{
    _currAnimTmpl = animTmpl;
}

AnimKeyFrameTemplate *
ColladaAnimationClip::getCurrTemplate(void) const
{
    return _currAnimTmpl;
}

ColladaAnimationClip::ColladaAnimationClip(
    daeElement *elem, ColladaGlobal *global)

    : Inherited    (elem, global)
    , _currAnimTmpl(NULL        )
{
}

ColladaAnimationClip::~ColladaAnimationClip(void)
{
}

#if 1
void
ColladaAnimationClip::handleInstanceAnimation(ColladaInstInfo *instInfo)
{
    OSG_COLLADA_LOG(("ColladaAnimationClip::handleInstanceAnimation\n"));

    ColladaAnimationInstInfo *animInstInfo =
        dynamic_cast<ColladaAnimationInstInfo *>(instInfo);

    OSG_ASSERT(animInstInfo                                != NULL);
    OSG_ASSERT(animInstInfo->getColInst()                  != NULL);
    OSG_ASSERT(animInstInfo->getColInst()->getTargetElem() != NULL);
    OSG_ASSERT(animInstInfo->getTemplate()                 != NULL);

    setCurrTemplate(animInstInfo->getTemplate());

    animInstInfo->getColInst()->getTargetElem()->createInstance(
        animInstInfo->getColInstParent(), animInstInfo->getColInst());

    setCurrTemplate(NULL);
}

#else
void
ColladaAnimationClip::handleInstanceAnimation(ColladaInstInfo *instInfo)
{
    OSG_COLLADA_LOG(("ColladaAnimationClip::handleInstanceAnimation\n"));

    ColladaAnimationInstInfo *animInstInfo =
        dynamic_cast<ColladaAnimationInstInfo *>(instInfo);

    OSG_ASSERT(animInstInfo                != NULL);
    OSG_ASSERT(animInstInfo->getAnim    () != NULL);
    OSG_ASSERT(animInstInfo->getTemplate() != NULL);

    setCurrTemplate(animInstInfo->getTemplate());

    animInstInfo->getAnim()->createInstance(
        animInstInfo->getColInstParent(), animInstInfo->getColInst());

    setCurrTemplate(NULL);
}
#endif

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
