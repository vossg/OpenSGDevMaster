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

#include "OSGColladaLight.h"
#include "OSGColladaLog.h"

#ifdef OSG_WITH_COLLADA

#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"

OSG_BEGIN_NAMESPACE

void ColladaLight::read(void)
{
    OSG_COLLADA_LOG(("ColladaLight::read:\n"));

    domLightRef light = getDOMElementAs<domLight>();

    if(light == NULL)
    {
        FWARNING(("ColladaLight::read: domLight is NULL.\n"));
        return;
    }

    domTechnique_commonRef commonTech = light->getTechnique_common();
    
    if(commonTech != NULL)
    {
        domAmbientRef     ambientL     = commonTech->getAmbient    ();
        domDirectionalRef directionalL = commonTech->getDirectional();
        domPointRef       pointL       = commonTech->getPoint      ();
        domSpotRef        spotL        = commonTech->getSpot       ();

        if(ambientL != NULL)
        {
            handleAmbient(ambientL);
        }
        else if(directionalL != NULL)
        {
            handleDirectional(directionalL);
        }
        else if(pointL != NULL)
        {
            handlePoint(pointL);
        }
        else if(spotL != NULL)
        {
            handleSpot(spotL);
        }
        else
        {
            FWARNING(("ColladaLight::read: No light type found.\n"));
            return;
        }
    }
    else if(light->getTechnique_array().getCount() > 0)
    {
        FWARNING(("ColladaLight::read: Ignoring non-empty "
                  "<technique> array.\n"));
        return;
    }
    
}

void ColladaLight::handleAmbient(domAmbient *ambientL)
{
    FWARNING(("ColladaLight::handleAmbient: NIY\n"));
}

void ColladaLight::handleDirectional(domDirectional *directionalL)
{
    DirectionalLightUnrecPtr light = DirectionalLight::create();
    domFloat3                color = directionalL->getColor()->getValue();

    light->setAmbient (Color4f(color[0], color[1], color[2], 1.f));
    light->setDiffuse (Color4f(color[0], color[1], color[2], 1.f));
    light->setSpecular(Color4f(color[0], color[1], color[2], 1.f));

    _light = light;
}

void ColladaLight::handlePoint(domPoint *pointL)
{
    PointLightUnrecPtr light = PointLight::create();
    domFloat3          color = pointL->getColor()->getValue();

    light->setAmbient (Color4f(color[0], color[1], color[2], 1.f));
    light->setDiffuse (Color4f(color[0], color[1], color[2], 1.f));
    light->setSpecular(Color4f(color[0], color[1], color[2], 1.f));

    if(pointL->getConstant_attenuation() != NULL)
    {
        light->setConstantAttenuation(
            pointL->getConstant_attenuation()->getValue());
    }

    if(pointL->getLinear_attenuation() != NULL)
    {
        light->setLinearAttenuation(
            pointL->getLinear_attenuation()->getValue());
    }

    if(pointL->getQuadratic_attenuation() != NULL)
    {
        light->setQuadraticAttenuation(
            pointL->getQuadratic_attenuation()->getValue());
    }

    _light = light;
}

void ColladaLight::handleSpot(domSpot *spotL)
{
    SpotLightUnrecPtr light = SpotLight::create();
    domFloat3         color = spotL->getColor()->getValue();

    light->setAmbient (Color4f(color[0], color[1], color[2], 1.f));
    light->setDiffuse (Color4f(color[0], color[1], color[2], 1.f));
    light->setSpecular(Color4f(color[0], color[1], color[2], 1.f));

    if(spotL->getConstant_attenuation() != NULL)
    {
        light->setConstantAttenuation(
            spotL->getConstant_attenuation()->getValue());
    }

    if(spotL->getLinear_attenuation() != NULL)
    {
        light->setLinearAttenuation(
            spotL->getLinear_attenuation()->getValue());
    }

    if(spotL->getQuadratic_attenuation() != NULL)
    {
        light->setQuadraticAttenuation(
            spotL->getQuadratic_attenuation()->getValue());
    }

    if(spotL->getFalloff_angle() != NULL)
    {
        light->setSpotCutOff(
            osgDegree2Rad(spotL->getFalloff_angle()->getValue()));
    }

    if(spotL->getFalloff_exponent() != NULL)
    {
        light->setSpotExponent(spotL->getFalloff_exponent()->getValue());
    }

    _light = light;
}

ColladaLight::ColladaLight(domLight *light, ColladaGlobal *global)
    : Inherited(light, global)
{
}

ColladaLight::~ColladaLight(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
