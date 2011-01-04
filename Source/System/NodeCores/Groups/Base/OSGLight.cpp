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
#include "OSGLightEngine.h"
#include "OSGLight.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGLightBase.cpp file.
// To modify it, please change the .fcd file (OSGLight.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

void Light::setAmbient(Real32 rRed, 
                       Real32 rGreen, 
                       Real32 rBlue, 
                       Real32 rAlpha)
{
    editSField(AmbientFieldMask);

    _sfAmbient.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setDiffuse(Real32 rRed, 
                       Real32 rGreen, 
                       Real32 rBlue, 
                       Real32 rAlpha)
{
    editSField(DiffuseFieldMask);

    _sfDiffuse.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

void Light::setSpecular(Real32 rRed, 
                        Real32 rGreen, 
                        Real32 rBlue, 
                        Real32 rAlpha)
{
    editSField(SpecularFieldMask);

    _sfSpecular.getValue().setValuesRGBA(rRed, rGreen, rBlue, rAlpha);
}

/*-------------------------------------------------------------------------*/
/*                             Chunk                                       */

LightChunk *Light::getChunk(void) const
{
    return _pChunk;
}

void Light::makeChunk(void)
{
    if(_pChunk == NULL)
    {
        _pChunk = LightChunk::createLocal();
    }

    _pChunk->setBeacon  (getBeacon  ());
    _pChunk->setAmbient (getAmbient ());
    _pChunk->setDiffuse (getDiffuse ());
    _pChunk->setSpecular(getSpecular());
}

/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void Light::changed(ConstFieldMaskArg whichField, 
                    UInt32            origin,
                    BitVector         details)
{
    makeChunk();

    Inherited::changed(whichField, origin, details);
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void Light::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Light::Light(void) :
     Inherited  (    ),
    _pChunk     (NULL)
{
}

Light::Light(const Light &source) :
     Inherited  (source             ),
    _pChunk     (source._pChunk     )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Light::~Light(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE Light::renderEnter(LightEngine::LightTypeE  eType,
                                   RenderAction   *action)
{
    Action::ResultE        r = Action::Continue;

    if(this->getOn() == false)
        return Action::Continue;

    LightEngine *pLightEngine = this->getLightEngine();

    if(pLightEngine != NULL && pLightEngine->getEnabled() == true)
    {
        r = pLightEngine->runOnEnter(this, eType, action);
    }
    else
    {
        // ok we can cull the light only when it is invisible and has
        // no LightEnv parent and local lights are enabled!
        if (action->pushVisibility())
        {
            if(action->selectVisibles() == 0)
            {
                action->popVisibility();
                return Action::Skip;
            }
        }

        StateChunk *pChunk          = this->getChunk();
        
        UInt32      uiSlot          = pChunk->getClassId();
        
        Int32       iLightIndex     = action->allocateLightIndex();
        
        action->pushState();
        
        if(iLightIndex >= 0)
        {
            action->addOverride(uiSlot + iLightIndex, pChunk);
        }
        else
        {
            SWARNING << "maximum light source limit ("
                     << -iLightIndex
                     << ") is reached" 
                     << " skipping light sources!"
                     << std::endl;
        }
    }

    return r;
}

Action::ResultE Light::renderLeave(LightEngine::LightTypeE  eType,
                                   Action                  *action)
{
    Action::ResultE  r = Action::Continue;
    RenderAction    *a = dynamic_cast<RenderAction *>(action);

    if(this->getOn() == false)
        return Action::Continue;

    LightEngine *pLightEngine = this->getLightEngine();

    if(pLightEngine != NULL && pLightEngine->getEnabled() == true)
    {
        r = pLightEngine->runOnLeave(this, eType, a);
    }
    else
    {
        a->releaseLightIndex();
        a->popState();

        a->popVisibility();
    }

    return r;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void Light::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pChunk = NULL;
}

//! initialize the static features of the class, e.g. action callbacks

void Light::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

