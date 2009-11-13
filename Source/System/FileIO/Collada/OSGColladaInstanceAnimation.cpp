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

#include "OSGColladaInstanceAnimation.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstanceWithExtra.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceAnimation::_regHelper(
    &ColladaInstanceAnimation::create, "instance_animation");


ColladaElementTransitPtr
ColladaInstanceAnimation::create(daeElement *elem, ColladaGlobal *global)
{
    return
        ColladaElementTransitPtr(new ColladaInstanceAnimation(elem, global));
}

void
ColladaInstanceAnimation::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaInstanceAnimation::read\n"));

    ColladaAnimationRefPtr colAnim = getTargetElem();

    if(colAnim == NULL)
    {
        colAnim = dynamic_pointer_cast<ColladaAnimation>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colAnim->read(this);
    }
}

ColladaAnimation *
ColladaInstanceAnimation::getTargetElem(void) const
{
    ColladaAnimation *retVal     = NULL;
    daeElementRef     targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaAnimation>(targetElem);
    }

    return retVal;
}

domAnimation *
ColladaInstanceAnimation::getTargetDOMElem(void) const
{
    domAnimationRef         retVal   = NULL;
    domInstanceWithExtraRef instAnim = getDOMElementAs<domInstanceWithExtra>();

    if(instAnim->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domAnimation>(instAnim->getUrl().getElement());
    }

    return retVal;
}

ColladaInstanceAnimation::ColladaInstanceAnimation(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceAnimation::~ColladaInstanceAnimation(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
