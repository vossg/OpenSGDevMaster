/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGL.h"

#include "OSGRenderAction.h"
#include "OSGStatCollector.h"

#include "OSGSpotLight.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSpotLightBase.cpp file.
// To modify it, please change the .fcd file (OSGSpotLight.fcd) and
// regenerate the base file.

/*----------------------------- class variables ---------------------------*/

StatElemDesc<StatIntElem>  SpotLight::statNSpotLights(
    "NSpotLights", 
    "number of spot light sources");

/*-------------------------------------------------------------------------*/
/*                             Changed                                     */

void SpotLight::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

void SpotLight::makeChunk(void)
{
    Inherited::makeChunk();

    Vec4f pos(_sfPosition.getValue ());

    pos[3] = 1.f;

    _pChunk->setPosition (pos                             );

    _pChunk->setDirection(              getDirection   () );
    _pChunk->setExponent (              getSpotExponent() );
    _pChunk->setCutoff   (osgRad2Degree(getSpotCutOff  ()));
}

/*-------------------------------------------------------------------------*/
/*                           LightEngine                                   */

void SpotLight::callLightEngineEnter(RenderAction *ract)
{
    if(getLightEngine() != NULL && getLightEngine()->getEnabled() == true)
    {
        getLightEngine()->runOnEnter(this, LightEngine::Spot, ract);
    }
}

void SpotLight::callLightEngineLeave(RenderAction *ract)
{
    if(getLightEngine() != NULL && getLightEngine()->getEnabled() == true)
    {
        getLightEngine()->runOnLeave(this, LightEngine::Spot, ract);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void SpotLight::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SpotLight::SpotLight(void) :
    Inherited()
{
}

SpotLight::SpotLight(const SpotLight &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SpotLight::~SpotLight(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

#ifdef OSG_OLD_RENDER_ACTION
Action::ResultE SpotLight::renderEnter(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    DrawActionBase *da    = dynamic_cast<DrawActionBase *>(action);

    if(da->getStatCollector() != NULL)
    {
        da->getStatCollector()->getElem(SpotLight::statNSpotLights)->inc();
    }

    return PointLight::renderEnter(action);
}

Action::ResultE SpotLight::renderLeave(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    return PointLightBase::renderLeave(action);
}
#endif

Action::ResultE SpotLight::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a->getActivePartition()->getStatCollector() != NULL)
    {
        a->getActivePartition()->getStatCollector()->getElem(
            SpotLight::statNSpotLights)->inc();
    }

    return Light::renderEnter(LightEngine::Spot,
                                  a);
}

Action::ResultE SpotLight::renderLeave(Action *action)
{
    return Light::renderLeave(LightEngine::Spot,
                              action);
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void SpotLight::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SpotLight::getClassType(), 
            reinterpret_cast<Action::Callback>(&SpotLight::renderEnter));

        RenderAction::registerLeaveDefault( 
            SpotLight::getClassType(), 
            reinterpret_cast<Action::Callback>(&SpotLight::renderLeave));
    }
}

