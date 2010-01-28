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

#include "OSGColladaInstanceLight.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceLight::_regHelper(
    &ColladaInstanceLight::create, "instance_light");


ColladaElementTransitPtr
ColladaInstanceLight::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceLight(elem, global));
}

void
ColladaInstanceLight::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaInstanceLight::read\n"));

    ColladaLightRefPtr colLight = getTargetElem();

    if(colLight == NULL)
    {
        colLight = dynamic_pointer_cast<ColladaLight>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colLight->read(this);
    }
}

ColladaLight *
ColladaInstanceLight::getTargetElem(void) const
{
    ColladaLight  *retVal     = NULL;
    daeElementRef  targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaLight>(targetElem);
    }

    return retVal;
}

domLight *
ColladaInstanceLight::getTargetDOMElem(void) const
{
    domLightRef          retVal    = NULL;
    domInstance_lightRef instLight = getDOMElementAs<domInstance_light>();

    if(instLight->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domLight>(instLight->getUrl().getElement());
    }

    return retVal;
}

ColladaInstanceLight::ColladaInstanceLight(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceLight::~ColladaInstanceLight(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
