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

#include "OSGDrawEnv.h"
#include "OSGState.h"
#include "OSGStateOverride.h"
#include <OSGBaseFunctions.h>

OSG_USING_NAMESPACE

/*! \class OSG::DrawEnv
    \ingroup GrpSystemRenderingBackend
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DrawEnv::DrawEnv(void) :
    _pRenderAction          (NULL ),
    _cameraFullProjection   (     ),
    _cameraProjection       (     ),
    _cameraProjectionTrans  (     ),
    _cameraViewing          (     ),
    _cameraToWorld          (     ),
    _cameraDecoration       (     ),
    _objectToWorld          (     ),

    _vpCameraFullProjection (     ),
    _vpCameraProjection     (     ),
    _vpCameraProjectionTrans(     ),
    _vpCameraViewing        (     ),
    _vpCameraToWorld        (     ),
    _vpWorldToScreen        (     ),

    _cameraNear             (1.f  ),
    _cameraFar              (100.f),

    _iPixelLeft             (    0),
    _iPixelRight            (    1),
    _iPixelBottom           (    0),
    _iPixelTop              (    1),
    _bFull                  ( true),

    _uiLightState           (    0),

    _pWindow                (NULL ),
    _pActiveState           (NULL ),
    _pActiveStateOverride   (NULL ),
    _uiNumStateChanges      (0    ),
    _uiNumShaderChanges     (0    ),
    _uiNumShaderParamChanges(0    ),
    _pStatCollector         (NULL ),
    _uiActiveShader         (0    )
{
    _cameraFullProjection   .setIdentity();
    _cameraProjection       .setIdentity();
    _cameraProjectionTrans  .setIdentity();
    _cameraViewing          .setIdentity();
    _cameraToWorld          .setIdentity();
    _cameraDecoration       .setIdentity();

    _objectToWorld          .setIdentity();

    _vpCameraFullProjection .setIdentity();
    _vpCameraProjection     .setIdentity();
    _vpCameraProjectionTrans.setIdentity();
    _vpCameraViewing        .setIdentity();
    _vpCameraToWorld        .setIdentity();
    _vpWorldToScreen        .setIdentity();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DrawEnv::~DrawEnv(void)
{
}

void DrawEnv::activate(State *pState)
{
    pState->activate(this);

    ++_uiNumStateChanges;
}


void DrawEnv::activate(State         *pState,
                       StateOverride *pOverride)
{
    if(pOverride == NULL)
    {
        activate(pState);
        return;
    }

    MFUnrecStateChunkPtr::const_iterator cIt  = pState->getMFChunks()->begin();
    MFUnrecStateChunkPtr::const_iterator cEnd = pState->getMFChunks()->end  (); 

    StateOverride::ChunkStoreIt          overIt = pOverride->begin();

    Int32                     ind  = 0;
    UInt32                    cind = osgMin(State::SkipNumChunks, 
                                            pState->getMFChunks()->size());


    OSG_SKIP_IT(cIt, cind);

    if(overIt != pOverride->end() && overIt->first < cind)
    {
        for(Int32 i = 0; i < cind; ++i)
        {
            StateChunk *n = NULL;
            
            if(overIt != pOverride->end() && overIt->first == i)
            {
                n = overIt->second;
                ++overIt;
            }
            
            if(n != NULL && n->getIgnore() == false)
            {
                n->activate(this, UInt32(ind));
            }
            
            if(++ind >= StateChunkClass::getNumSlots(i))
            {
                ind = 0;
            }
        }

        ind = 0;
    }

    for(; cIt != cEnd; ++cIt, ++cind)
    {
        if(overIt != pOverride->end() && overIt->first == cind)
        {
            if(overIt->second->getIgnore() == false)
            {
                overIt->second->activate(this, UInt32(ind));
            }

            ++overIt;
        }
        else
        {
            if(*cIt != NULL && (*cIt)->getIgnore() == false)
            {
                (*cIt)->activate(this, UInt32(ind));
            }
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }

    while(overIt != pOverride->end())
    {
        if(overIt->second->getIgnore() == false)
        {
            overIt->second->activate(this,
                                     UInt32(overIt->first -
                                            overIt->second->getClassId()));
        }

        ++overIt;
    }

    ++_uiNumStateChanges;
}

void DrawEnv::changeTo(State         *pState,
                       State         *pOld)
{
    if(pState != pOld)
    {
        pState->changeFrom(this, pOld);

        ++_uiNumStateChanges;
    }
}

void DrawEnv::changeTo(State         *pState,
                       State         *pOld,
                       StateOverride *pOldOverride)
{
    if(pOldOverride == NULL)
    {
        changeTo(pState, pOld);
        return;
    }

    MFUnrecStateChunkPtr::const_iterator cIt  = pState->getMFChunks()->begin();
    MFUnrecStateChunkPtr::const_iterator cEnd = pState->getMFChunks()->end  (); 

    StateOverride::ChunkStoreIt          overIt = pOldOverride->begin();

    Int32                     ind = 0;
    UInt32                    i;
    UInt32                    cind = osgMin(State::SkipNumChunks, 
                                            pState->getMFChunks()->size());
    StateChunk               *n    = NULL;

    OSG_SKIP_IT(cIt, cind);

    if(overIt != pOldOverride->end() && overIt->first < cind)
    {
        for(i = 0; i < cind; ++i)
        {
            StateChunk *o = NULL;
            
            if(overIt != pOldOverride->end() && overIt->first == i)
            {
                o = overIt->second;
                ++overIt;
            }
            
            if(o != NULL && o->getIgnore() == false)
            {
                o->deactivate(this, UInt32(ind));
            }
            
            if(++ind >= StateChunkClass::getNumSlots(i))
            {
                ind = 0;
            }
        }

        ind = 0;
    }

    for(; cIt != cEnd; ++cIt, ++cind)
    {
        StateChunk *o = pOld->getChunk(cind);

        n  = *cIt;

        if(overIt != pOldOverride->end() && overIt->first == cind)
        {
            o = overIt->second;
            ++overIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
        {
            ind = 0;
        }
    }

    if(ind >= StateChunkClass::getNumSlots(cind))
        ind = 0;

    for(i = cind; i < pOld->getMFChunks()->size(); ++i)
    {
        StateChunk *o = pOld->getChunk(i);

        if(overIt != pOldOverride->end() && overIt->first == cind)
        {
            if(overIt->second->getIgnore() == false)
            {
                overIt->second->deactivate(this, UInt32(ind));
            }

            ++overIt;
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }

    while(overIt != pOldOverride->end())
    {
        if(overIt->second->getIgnore() == false)
        {
            overIt->second->deactivate(this,
                                       UInt32(overIt->first -
                                              overIt->second->getClassId()));
        }

        ++overIt;
    }

    ++_uiNumStateChanges;
}

void DrawEnv::changeTo(State         *pState,
                       StateOverride *pOverride,
                       State         *pOld)
{
    if(pOverride == NULL)
    {
        changeTo(pState, pOld);
        return;
    }

    MFUnrecStateChunkPtr::const_iterator cIt  = pState->getMFChunks()->begin();
    MFUnrecStateChunkPtr::const_iterator cEnd = pState->getMFChunks()->end  (); 

    StateOverride::ChunkStoreIt          overIt = pOverride->begin();

    Int32                     ind = 0;
    UInt32                    i;
    UInt32                    cind = osgMin(State::SkipNumChunks, 
                                            pState->getMFChunks()->size());
    StateChunk               *n    = NULL;

    OSG_SKIP_IT(cIt, cind);

    if(overIt != pOverride->end() && overIt->first < cind)
    {
        for(Int32 i = 0; i < cind; ++i)
        {
            StateChunk *n = NULL;
            
            if(overIt != pOverride->end() && overIt->first == i)
            {
                n = overIt->second;
                ++overIt;
            }
            
            if(n != NULL && n->getIgnore() == false)
            {
                n->activate(this, UInt32(ind));
            }
            
            if(++ind >= StateChunkClass::getNumSlots(i))
            {
                ind = 0;
            }
        }

        ind = 0;
    }

    for(; cIt != cEnd; ++cIt, ++cind)
    {
        StateChunk *o = pOld->getChunk(cind);
                    n = *cIt;

        if(overIt != pOverride->end() && overIt->first == cind)
        {
            n = overIt->second;
            ++overIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
        {
            ind = 0;
        }
    }

    if(ind >= StateChunkClass::getNumSlots(cind))
        ind = 0;

    for(i = cind; i < pOld->getMFChunks()->size(); ++i)
    {
        StateChunk *o = pOld->getChunk(i);

        n = NULL;

        if(overIt != pOverride->end() && overIt->first == cind)
        {
            n = overIt->second;
            ++overIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }

    while(overIt != pOverride->end())
    {
        if(overIt->second->getIgnore() == false)
        {
            overIt->second->activate(this,
                                     UInt32(overIt->first -
                                            overIt->second->getClassId()));
        }

        ++overIt;
    }

    ++_uiNumStateChanges;
}

void DrawEnv::changeTo(State         *pState,
                       StateOverride *pOverride,
                       State         *pOld,
                       StateOverride *pOldOverride)
{
    if(pOverride == NULL)
    {
        changeTo(pState, pOld, pOldOverride);
        return;
    }

    if(pOldOverride == NULL)
    {
        changeTo(pState, pOverride, pOld);
        return;
    }

    MFUnrecStateChunkPtr::const_iterator cIt  = pState->getMFChunks()->begin();
    MFUnrecStateChunkPtr::const_iterator cEnd = pState->getMFChunks()->end  (); 

    StateOverride::ChunkStoreIt          newOverIt = pOverride  ->begin();
    StateOverride::ChunkStoreIt          oldOverIt = pOldOverride->begin();

    Int32                     ind  = 0;
    UInt32                    i;
    UInt32                    cind = osgMin(State::SkipNumChunks, 
                                            pState->getMFChunks()->size());
    StateChunk               *n    = NULL;

    OSG_SKIP_IT(cIt, cind);

    for(i = 0; i < cind; ++i)
    {
        StateChunk *o = NULL;
                    n = NULL;

        if(oldOverIt != pOldOverride->end() && oldOverIt->first == i)
        {
            o = oldOverIt->second;
            ++oldOverIt;
        }

        if(newOverIt != pOverride->end() && newOverIt->first == i)
        {
            n = newOverIt->second;
            ++newOverIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }

    ind = 0;

    for(; cIt != cEnd; ++cIt, ++cind)
    {
        StateChunk *o = pOld->getChunk(cind);
                    n = *cIt;

        if(oldOverIt != pOldOverride->end() && oldOverIt->first == cind)
        {
            o = oldOverIt->second;
            ++oldOverIt;
        }

        if(newOverIt != pOverride->end() && newOverIt->first == cind)
        {
            n = newOverIt->second;
            ++newOverIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
        {
            ind = 0;
        }
    }



    if(ind >= StateChunkClass::getNumSlots(cind))
        ind = 0;

    for(i = cind; i < pOld->getMFChunks()->size(); ++i)
    {
        StateChunk *o = pOld->getChunk(i);
        n = NULL;

        if(oldOverIt != pOldOverride->end() && oldOverIt->first == cind)
        {
            o = oldOverIt->second;
            ++oldOverIt;
        }

        if(newOverIt != pOverride->end() && newOverIt->first == cind)
        {
            n = newOverIt->second;
            ++newOverIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(o != NULL && o->getIgnore() == false)
            {
                n->changeFrom(this, o, UInt32(ind));
            }
            else
            {
                n->activate(this, UInt32(ind));
            }
        }
        else if(o != NULL && o->getIgnore() == false)
        {
            o->deactivate(this, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }

    while(oldOverIt != pOldOverride->end())
    {
        n = NULL;

        if(newOverIt        != pOverride->end() &&
           newOverIt->first == oldOverIt->first  )
        {
            n = newOverIt->second;
            ++newOverIt;
        }

        if(n != NULL && n->getIgnore() == false)
        {
            if(oldOverIt->second->getIgnore() == false)
            {
                n->changeFrom(this,
                              oldOverIt->second,
                              UInt32(oldOverIt->first -
                                     oldOverIt->second->getClassId()));
            }
            else
            {
                n->activate(this,
                            UInt32(oldOverIt->first -
                                   oldOverIt->second->getClassId()));
            }
        }
        else if(oldOverIt->second->getIgnore() == false)
        {
            oldOverIt->second->deactivate(
                this,
                  UInt32(oldOverIt->first -
                         oldOverIt->second->getClassId()));
        }

        ++oldOverIt;
    }


    while(newOverIt != pOverride->end())
    {
        if(newOverIt->second->getIgnore() == false)
        {
            newOverIt->second->activate(this,
                                        UInt32(
                                            newOverIt->first -
                                            newOverIt->second->getClassId()));
        }

        ++newOverIt;
    }

    ++_uiNumStateChanges;
}

void DrawEnv::deactivate(State *pState)
{
    if(pState != NULL)
        pState->deactivate(this);
}

void DrawEnv::deactivate(State         *pState,
                         StateOverride *pOverride  )
{
    if(pOverride == NULL)
    {
        deactivate(pState);
        return;
    }

    MFUnrecStateChunkPtr::const_iterator cIt  = pState->getMFChunks()->begin();
    MFUnrecStateChunkPtr::const_iterator cEnd = pState->getMFChunks()->end  ();

    StateOverride::ChunkStoreIt          overIt = pOverride->begin();

    Int32                     ind  = 0;
    UInt32                    cind = osgMin(State::SkipNumChunks, 
                                            pState->getMFChunks()->size());

    OSG_SKIP_IT(cIt, cind);

    if(overIt != pOverride->end() && overIt->first < cind)
    {
        for(Int32 i = 0; i < cind; ++i)
        {
            if(overIt != pOverride->end() && overIt->first == i)
            {
                if(overIt->second              != NULL && 
                   overIt->second->getIgnore() == false  )
                {
                    overIt->second->activate(this, UInt32(ind));
                }

                ++overIt;
            }
            
            if(++ind >= StateChunkClass::getNumSlots(i))
            {
                ind = 0;
            }
        }

        ind = 0;
    }

    for(; cIt != cEnd; ++cIt, ++cind)
    {
        if(overIt != pOverride->end() && overIt->first == cind)
        {
            if(overIt->second->getIgnore() == false)
            {
                overIt->second->deactivate(this, UInt32(ind));
            }

            ++overIt;
        }
        else
        {
            if(*cIt != NULL && (*cIt)->getIgnore() == false)
            {
                (*cIt)->deactivate(this, UInt32(ind));
            }
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }

    while(overIt !=  pOverride->end())
    {
        if(overIt->second->getIgnore() == false)
        {
            overIt->second->deactivate(this,
                                       UInt32(overIt->first -
                                              overIt->second->getClassId()));
        }

        ++overIt;
    }
}

