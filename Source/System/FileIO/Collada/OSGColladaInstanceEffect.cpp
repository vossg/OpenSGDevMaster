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

#include "OSGColladaInstanceEffect.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstance_effect.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceEffect::_regHelper(
    &ColladaInstanceEffect::create, "instance_effect");

ColladaElementTransitPtr
ColladaInstanceEffect::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceEffect(elem, global));
}

void
ColladaInstanceEffect::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceEffect::read\n"));

    ColladaEffectRefPtr colEffect = getSourceElem();

    if(colEffect == NULL)
    {
        colEffect = dynamic_pointer_cast<ColladaEffect>(
            ColladaElementFactory::the()->create(
                getSourceDOMElem(), getGlobal()));

        colEffect->read();
    }

    domInstance_effectRef instEffect = getDOMElementAs<domInstance_effect>();

    const domInstance_effect::domTechnique_hint_Array &techHints =
        instEffect->getTechnique_hint_array();

    if(techHints.getCount() > 0)
    {
        SWARNING << "ColladaInstanceEffect::read: Ignoring ["
                 << techHints.getCount() << "] <technique_hint> elements."
                 << std::endl;
    }

    const domInstance_effect::domSetparam_Array &setParams =
        instEffect->getSetparam_array();

    if(setParams.getCount() > 0)
    {
        SWARNING << "ColladaInstanceEffect::read: Ignoring ["
                 << setParams.getCount() << "] <setparam> elements."
                 << std::endl;
    }
}

FieldContainer *
ColladaInstanceEffect::process(ColladaElement *parent)
{
    OSG_COLLADA_LOG(("ColaldaInstanceEffect::process\n"));

    ColladaEffectRefPtr colEffect = getSourceElem();

    return colEffect->createInstance(this);
}

ColladaEffect *
ColladaInstanceEffect::getSourceElem(void) const
{
    ColladaEffect *retVal     = NULL;
    domEffectRef   sourceElem = getSourceDOMElem();

    if(sourceElem != NULL)
    {
        retVal = getUserDataAs<ColladaEffect>(sourceElem);
    }

    return retVal;
}

domEffect *
ColladaInstanceEffect::getSourceDOMElem(void) const
{
    domEffectRef          retVal     = NULL;
    domInstance_effectRef instEffect = getDOMElementAs<domInstance_effect>();

    if(instEffect->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domEffect>(instEffect->getUrl().getElement());
    }
    else
    {
        SWARNING << "ColladaInstanceEffet::getSourceDOMElem: "
                 << "can not resolve URL [" << instEffect->getUrl().str()
                 << "]." << std::endl;
    }

    return retVal;
}

ColladaInstanceEffect::ColladaInstanceEffect(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceEffect::~ColladaInstanceEffect(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
