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

#include "OSGColladaMaterial.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceEffect.h"
#include "OSGColladaInstanceMaterial.h"
#include "OSGColladaLog.h"
#include "OSGNameAttachment.h"

#include <dom/domMaterial.h>
#include <dom/domInstance_effect.h>

OSG_BEGIN_NAMESPACE

ColladaInstInfoTransitPtr
ColladaMaterial::ColladaMaterialInstInfo::create(
    ColladaElement *colInstParent, ColladaInstanceMaterial *colInst)
{
    return ColladaInstInfoTransitPtr(
        new ColladaMaterialInstInfo(colInstParent, colInst));
}

void
ColladaMaterial::ColladaMaterialInstInfo::process(void)
{
    SFATAL << "ColladaMaterialInstInfo::process called!" << std::endl;
}

ColladaMaterial::ColladaMaterialInstInfo::ColladaMaterialInstInfo(
    ColladaElement *colInstParent, ColladaInstanceMaterial *colInst)

    : Inherited(colInstParent, colInst)
{
}

ColladaMaterial::ColladaMaterialInstInfo::~ColladaMaterialInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaMaterial::_regHelper(
    &ColladaMaterial::create, "material");


ColladaElementTransitPtr
ColladaMaterial::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaMaterial(elem, global));
}

void
ColladaMaterial::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaMaterial::read\n"));

    domMaterialRef              material      = getDOMElementAs<domMaterial>();
    domInstance_effectRef       instEffect    = material->getInstance_effect();
    ColladaInstanceEffectRefPtr colInstEffect =
        getUserDataAs<ColladaInstanceEffect>(instEffect);

    if(colInstEffect == NULL)
    {
        colInstEffect = dynamic_pointer_cast<ColladaInstanceEffect>(
            ColladaElementFactory::the()->create(instEffect, getGlobal()));

        colInstEffect->read(this);
    }
}

Material *
ColladaMaterial::createInstance(ColladaInstInfo *colInstInfo)
{
    OSG_COLLADA_LOG(("ColladaMaterial::createInstance\n"));

    MaterialUnrecPtr            retVal        = NULL;
    domMaterialRef              material      = getDOMElementAs<domMaterial>();
    domInstance_effectRef       instEffect    = material->getInstance_effect();
    ColladaInstanceEffectRefPtr colInstEffect =
        getUserDataAs<ColladaInstanceEffect>(instEffect);

    if(getInstStore().empty() == true)
    {
        OSG_ASSERT(colInstEffect                  != NULL);
        OSG_ASSERT(colInstEffect->getTargetElem() != NULL);

        ColladaInstInfoRefPtr colEffectInstInfo =
            ColladaEffect::ColladaEffectInstInfo::create(this, colInstEffect);

        retVal = colInstEffect->getTargetElem()->createInstance(
            colEffectInstInfo);

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           material->getName()                                   != NULL   )
        {
            setName(retVal, material->getName());
        }

        editInstStore().push_back(retVal);
    }
    else
    {
        retVal = dynamic_pointer_cast<Material>(getInstStore()[0]);

        getGlobal()->getStatCollector()->getElem(
            ColladaGlobal::statNMaterialUsed)->inc();
    }

    return retVal;
}

ColladaMaterial::ColladaMaterial(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaMaterial::~ColladaMaterial(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
