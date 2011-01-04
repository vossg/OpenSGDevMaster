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

#include "OSGDirectionalLight.h"
#include "OSGRenderAction.h"

#include "OSGStatCollector.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGDirectionalLightBase.cpp file.
// To modify it, please change the .fcd file (OSGDirectionalLight.fcd) and
// regenerate the base file.

/*----------------------------- class variables ---------------------------*/

StatElemDesc<StatIntElem>  DirectionalLight::statNDirectionalLights(
    "NDirectionalLights", 
    "number of directional light sources");


/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void DirectionalLight::setDirection(Real32 rX, Real32 rY, Real32 rZ)
{
    editSField(DirectionFieldMask);

    _sfDirection.getValue().setValues(rX, rY, rZ);
}

/*-------------------------------------------------------------------------*/
/*                             Changed                                     */

void DirectionalLight::changed(ConstFieldMaskArg whichField, 
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

void DirectionalLight::makeChunk(void)
{
    Inherited::makeChunk();

    Vec4f dir(_sfDirection.getValue());

    dir[3] = 0.f;

    _pChunk->setPosition(dir);
}

/*-------------------------------------------------------------------------*/
/*                           LightEngine                                   */

void DirectionalLight::callLightEngineEnter(RenderAction *ract)
{
    if(getLightEngine() != NULL && getLightEngine()->getEnabled() == true)
    {
        getLightEngine()->runOnEnter(this, LightEngine::Directional, ract);
    }
}

void DirectionalLight::callLightEngineLeave(RenderAction *ract)
{
    if(getLightEngine() != NULL && getLightEngine()->getEnabled() == true)
    {
        getLightEngine()->runOnLeave(this, LightEngine::Directional, ract);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void DirectionalLight::dump(      UInt32    uiIndent, 
                            const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DirectionalLight::DirectionalLight(void) :
    Inherited()
{
}

DirectionalLight::DirectionalLight(const DirectionalLight &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DirectionalLight::~DirectionalLight(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

#ifdef OSG_OLD_RENDER_ACTION
Action::ResultE DirectionalLight::renderEnter(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    if(da->getStatCollector() != NULL)
    {
        da->getStatCollector()->getElem(
            DirectionalLight::statNDirectionalLights)->inc();
    }

    return Light::renderEnter(action);
}

Action::ResultE DirectionalLight::renderLeave(Action *action)
{
    if(getOn() == false)
        return Action::Continue;

    return Light::renderLeave(action);
}
#endif

Action::ResultE DirectionalLight::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a->getActivePartition()->getStatCollector() != NULL)
    {
        a->getActivePartition()->getStatCollector()->getElem(
            DirectionalLight::statNDirectionalLights)->inc();
    }

    return Inherited::renderEnter(LightEngine::Directional, a);
}

Action::ResultE DirectionalLight::renderLeave(Action *action)
{
    return Inherited::renderLeave(LightEngine::Directional, action);
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void DirectionalLight::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault( 
            DirectionalLight::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &DirectionalLight::renderEnter));

        RenderAction::registerLeaveDefault(
            DirectionalLight::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &DirectionalLight::renderLeave));
    }
}
