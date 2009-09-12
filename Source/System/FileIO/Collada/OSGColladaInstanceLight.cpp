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
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaInstanceLight.h"
#include "OSGColladaLog.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLight.h"
#include "OSGColladaGlobal.h"
#include "OSGMultiCore.h"
#include "OSGNode.h"

#include <dae/daeURI.h>
#include <dom/domInstance_light.h>

OSG_BEGIN_NAMESPACE

void ColladaInstanceLight::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceLight::read:\n"));

    domInstance_lightRef instLight = getDOMElementAs<domInstance_light>();
    daeURI               lightUri  = instLight->getUrl();
    domLightRef          light     =
        daeSafeCast<domLight>(lightUri.getElement());

    OSG_COLLADA_LOG(("ColladaInstanceLight::read: lightURI [%s]\n",
                     lightUri.str().c_str()));

    setInstDOMElement(light);

    ColladaLightRefPtr colLight = getUserDataAs<ColladaLight>(light);

    if(colLight == NULL)
    {
        colLight = ColladaLight::create(light, getGlobal());
        addElement(colLight);

        colLight->read();
    }

    OSG_COLLADA_LOG(("ColladaInstanceLight::read: [%s] "
                     "instantiating [%s] [%s]\n",
                     (instLight->getName() ? instLight->getName() : ""),
                     instLight->getUrl().str().c_str(),
                     (light->getName() ? light->getName() : "") ));
}

LightTransitPtr ColladaInstanceLight::createInstance(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceLight::createInstance:\n"));

    LightTransitPtr    retVal;
    domLightRef        light    = getInstDOMElementAs<domLight>();
    ColladaLightRefPtr colLight = getUserDataAs<ColladaLight>(light);

    ++colLight->_instCount;

    if(colLight->getLight() != NULL)
    {
        LightUnrecPtr light  =
            static_pointer_cast<Light>(colLight->getLight()->shallowCopy());
        MultiCore    *lights = 
            dynamic_cast<MultiCore *>(getGlobal()->getLightsNode()->getCore());

        lights->addCore(light);

        retVal = light;
    }

    return retVal;
}


ColladaInstanceLight::ColladaInstanceLight(
    domInstance_light *instLight, ColladaGlobal *global)

    : Inherited(instLight, global)
{
}

ColladaInstanceLight::~ColladaInstanceLight(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
