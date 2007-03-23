/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "OSGConfig.h"

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderTraversalAction.h"
#include "OSGRenderAction.h"

#include "OSGMaterialDrawable.h"

#include "OSGGeometry.h"
#include "OSGGroup.h"
#include "OSGBillboard.h"
#include "OSGComponentTransform.h"
#include "OSGDistanceLOD.h"
#include "OSGMaterialGroup.h"
#include "OSGSwitch.h"
#include "OSGTransform.h"
#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGLightChunk.h"
#include "OSGStage.h"
#include "OSGSimpleStage.h"
#ifdef OSG_GV_BETA
#include "OSGHDRStage.h"
#include "OSGAlgorithmStage.h"
#endif
#include "OSGRenderPartition.h"
#include "OSGFrameBufferObject.h"
#include "OSGVisitSubTree.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGParticles.h"

#include "OSGLightEngine.h"
#include "OSGMatrixUtility.h"


/*
#include "OSGSlices.h"
#include "OSGParticles.h"
 */

//#define OSG_DUMP_TRAVERSAL

OSG_BEGIN_NAMESPACE

Action::ResultE MaterialDrawableRenderEnter(const NodeCorePtr &pCore,
                                                  Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter MaterialDrawable %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    
    MaterialDrawablePtr pMDraw = cast_dynamic<MaterialDrawablePtr>(pCore);

    Material::DrawFunctor func;

    func = boost::bind(&MaterialDrawable::drawPrimitives, getCPtr(pMDraw), _1);

    Material *m = a->getMaterial();

    if(m == NULL)
    {
        if(pMDraw->getMaterial() != NullFC)
        {
            m = getCPtr(pMDraw->getMaterial());
        }
        else
        {
            m = getCPtr(getDefaultMaterial());
            
            FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
        }
    }

    Action::ResultE rc = m->renderEnter(pCore, action);

    if(rc == Action::Continue)
    {
        UInt32 uiNPasses = m->getNPasses();

        for(UInt32 uiPass = 0; uiPass < uiNPasses; ++uiPass)
        {
/*
        fprintf(stderr, "Enter MaterialDrawable drop %d %d %p\n", 
                uiPass, 
                m->getSortKey(),
                getCPtr(m->getState(uiPass)));
 */
            StatePtr st = m->getState(uiPass);

            if(st != NullFC)
            {
                a->dropFunctor(func, 
                               getCPtr(st), 
                               m->getSortKey() + uiPass);
            }
            else
            {
#ifndef WIN32
                FINFO(("%s: hit material with NullFC state!\n", __func__));
#else
                FINFO(("Hit material with NullFC state!\n"));
#endif
            }
        }
    }

    if(rc == Action::Skip)
        rc = Action::Continue;

    return rc;
}

Action::ResultE MaterialDrawableRenderLeave(const NodeCorePtr &pCore,
                                                  Action      *action)
{
    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    
    MaterialDrawablePtr pMDraw = cast_dynamic<MaterialDrawablePtr>(pCore);

    Material::DrawFunctor func;

    func = boost::bind(&MaterialDrawable::drawPrimitives, getCPtr(pMDraw), _1);

    Material *m = a->getMaterial();

    if(m == NULL)
    {
        if(pMDraw->getMaterial() != NullFC)
        {
            m = getCPtr(pMDraw->getMaterial());
        }
        else
        {
            m = getCPtr(getDefaultMaterial());
            
            FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
        }
    }

    Action::ResultE rc = m->renderLeave(pCore, action);

    if(rc == Action::Skip)
        rc = Action::Continue;

    return rc;
}

ActionBase::ResultE GroupRenderEnter(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter Group %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    a->pushVisibility();
    
    return ActionBase::Continue;
}

ActionBase::ResultE GroupRenderLeave(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave Group %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    a->popVisibility();
    
    return ActionBase::Continue;
}

ActionBase::ResultE SwitchRenderEnter(const NodeCorePtr &pCore,
                                            Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter Switch %p\n", &(*pCore)));
#endif

    Action::ResultE        returnValue = Action::Continue;
    SwitchPtr              pThis       = cast_dynamic<SwitchPtr>(pCore);
    RenderTraversalAction *pAction     =
        dynamic_cast<RenderTraversalAction*>(action);
    
    if((pThis->getChoice()                      >= 0                   ) &&
       (static_cast<UInt32>(pThis->getChoice()) <  pAction->getNNodes())    )
    {
        pAction->useNodeList();
        
        if(pAction->isVisible(getCPtr(pAction->getNode(pThis->getChoice()))))
        {
            pAction->addNode(pAction->getNode(pThis->getChoice()));
        }
        
        returnValue = GroupRenderEnter(pCore, action);
    }
    else if(pThis->getChoice() == Switch::ALL)
    {
        returnValue = GroupRenderEnter(pCore, action);
    }
    else
    {
        returnValue = Action::Skip;
    }
    
    return returnValue;
}

Action::ResultE SwitchRenderLeave(const NodeCorePtr &pCore,
                                        Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave Switch %p\n", &(*pCore)));
#endif
    
    return GroupRenderLeave(pCore, action);
}


ActionBase::ResultE BillboardRenderEnter(const NodeCorePtr &pCore, Action *action)
{
    BillboardPtr pBillboard = cast_dynamic<BillboardPtr>(pCore);
    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    Matrix mMat;
    Matrix cam_to_world = 
        pAction->getActivePartition()->getVPCameraToWorld();

    pBillboard->calcMatrix(cam_to_world, pAction->topMatrix(), mMat);

    pAction->pushMatrix(mMat);

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    pAction->selectVisibles();

    return ActionBase::Continue;
}

ActionBase::ResultE BillboardRenderLeave(const NodeCorePtr &pCore, Action *action)
{
    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    pAction->popMatrix();

    return ActionBase::Continue;
}


ActionBase::ResultE TransformRenderEnter(const NodeCorePtr &pCore,
                                               Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter Transform %p\n", &(*pCore)));
#endif

    TransformPtr pThis = cast_dynamic<TransformPtr>(pCore);

    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    pAction->pushVisibility();

    pAction->pushMatrix(pThis->getMatrix());

    return ActionBase::Continue;
}

ActionBase::ResultE TransformRenderLeave(const NodeCorePtr &pCore,
                                               Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave Transform %p\n", &(*pCore)));
#endif

    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return ActionBase::Continue;
}

ActionBase::ResultE MaterialGroupRenderEnter(const NodeCorePtr &pCore,
                                                   Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter MaterialGroup %p\n", &(*pCore)));
#endif

    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    MaterialGroupPtr pMatGroup = cast_dynamic<MaterialGroupPtr>(pCore);

    if(pAction                  != NULL   && 
       pMatGroup                != NullFC &&
       pMatGroup->getMaterial() != NullFC  )
    {
        pAction->overrideMaterial(getCPtr(pMatGroup->getMaterial()), 
                                  pAction->getActNode()            );
    }

    return GroupRenderEnter(pCore, action);
}

ActionBase::ResultE MaterialGroupRenderLeave(const NodeCorePtr &pCore,
                                                   Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave MaterialGroup %p\n", &(*pCore)));
#endif

    RenderTraversalAction *pAction = 
        dynamic_cast<RenderTraversalAction *>(action);

    if(pAction != NULL)
    {
        pAction->overrideMaterial(NULL, pAction->getActNode());
    }

    return GroupRenderLeave(pCore, action);
}

Action::ResultE LightRenderEnter(const NodeCorePtr              &pCore,
                                       LightEngine::LightTypeE   eType,
                                       RenderTraversalAction    *action)
{
    Action::ResultE        r = Action::Continue;
//    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    
    LightPtr      pLight      = cast_dynamic<LightPtr>(pCore);

    if(pLight->getOn() == false)
        return Action::Continue;

    LightEnginePtr pLightEngine = pLight->getLightEngine();

    if(pLightEngine != NullFC && pLightEngine->getEnabled() == true)
    {
        r = pLightEngine->runOnEnter(pLight, eType, action);
    }
    else
    {
        StateChunkPtr pChunk          = pLight->getChunk();
        
        UInt32        uiSlot          = pChunk->getClassId();
        
        Int32         iLightIndex     = action->allocateLightIndex();
        
        action->pushState();
        
        if(iLightIndex >= 0)
        {
            action->addOverride(uiSlot + iLightIndex, getCPtr(pChunk));
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


Action::ResultE LightRenderLeave(const NodeCorePtr              &pCore,
                                       LightEngine::LightTypeE   eType,
                                       Action                   *action)
{
    Action::ResultE        r = Action::Continue;
    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    LightPtr      pLight     = cast_dynamic<LightPtr>(pCore);

    if(pLight->getOn() == false)
        return Action::Continue;

    LightEnginePtr pLightEngine = pLight->getLightEngine();

    if(pLightEngine != NullFC && pLightEngine->getEnabled() == true)
    {
        r = pLightEngine->runOnLeave(pLight, eType, a);
    }
    else
    {
        a->releaseLightIndex();
        a->popState();
    }

    return r;
}

Action::ResultE DirectionalLightRenderEnter(const NodeCorePtr &pCore,
                                                  Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter DirLight %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    if(a->getActivePartition()->getStatCollector() != NULL)
    {
        a->getActivePartition()->getStatCollector()->getElem(
            DirectionalLight::statNDirectionalLights)->inc();
    }

    return LightRenderEnter(pCore, LightEngine::Directional, a);
}

Action::ResultE DirectionalLightRenderLeave(const NodeCorePtr &pCore,
                                                  Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave DirLight %p\n", &(*pCore)));
#endif

#if 0
   if(getOn() == false)
        return Action::Continue;

    return Light::renderLeave(action);
#endif

    return LightRenderLeave(pCore, LightEngine::Directional, action);
}

Action::ResultE PointLightRenderEnter(const NodeCorePtr &pCore,
                                            Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter PointLight %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    if(a->getActivePartition()->getStatCollector() != NULL)
    {
        a->getActivePartition()->getStatCollector()->getElem(
            PointLight::statNPointLights)->inc();
    }

    return LightRenderEnter(pCore,
                            LightEngine::Point,
                            a);
}

Action::ResultE PointLightRenderLeave(const NodeCorePtr &pCore,
                                            Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave PointLight %p\n", &(*pCore)));
#endif

#if 0
    if(getOn() == false)
        return Action::Continue;

    return Light::renderLeave(action);
#endif

    return LightRenderLeave(pCore, 
                            LightEngine::Point,
                            action);
}

Action::ResultE SpotLightRenderEnter(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter SpotLight %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    if(a->getActivePartition()->getStatCollector() != NULL)
    {
        a->getActivePartition()->getStatCollector()->getElem(
            SpotLight::statNSpotLights)->inc();
    }

    return LightRenderEnter(pCore,
                            LightEngine::Spot,
                            a);
}

Action::ResultE SpotLightRenderLeave(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave SpotLight %p\n", &(*pCore)));
#endif

#if 0
    if(getOn() == false)
        return Action::Continue;

    return PointLightBase::renderLeave(action);
#endif

    return LightRenderLeave(pCore, 
                            LightEngine::Spot,
                            action);
}


#if 0
Action::ResultE ShadowSpotLightRenderEnter(const NodeCorePtr &pCore,
                                                 Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter ShadowSpotLight %p\n", &(*pCore)));
#endif

    return LightRenderEnter(pCore, action);
}

Action::ResultE ShadowSpotLightRenderLeave(const NodeCorePtr &pCore,
                                                 Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave ShadowSpotLight %p\n", &(*pCore)));
#endif

    return LightRenderLeave(pCore, action);
}
#endif

ActionBase::ResultE StageRenderEnter(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter Stage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    StagePtr               pStage = cast_dynamic<StagePtr>(pCore);
    if(a == NULL || pStage == NullFC)
        return ActionBase::Continue;

    a->pushPartition();

    RenderPartition *pPart = a->getActivePartition();

    FrameBufferObject *pTarget  = getCPtr(pStage->getRenderTarget());
    Viewport          *pPort    = a->getViewport();
    Camera            *pCam     = a->getCamera  ();
    Background        *pBack    = a->getBackground();

    pPart->setRenderTarget(pTarget);

    if(pPort != NULL)
    {
        pPart->setViewport(pPort         );
        pPart->setWindow  (a->getWindow());

        if(pTarget != NULL)
        {
            pPart->calcViewportDimension(pPort->getLeft  (),
                                         pPort->getBottom(),
                                         pPort->getRight (),
                                         pPort->getTop   (),
                                         
                                         pTarget->getWidth    (),
                                         pTarget->getHeight   ());
        }
        else
        {
            pPart->calcViewportDimension(pPort->getLeft  (),
                                         pPort->getBottom(),
                                         pPort->getRight (),
                                         pPort->getTop   (),
                                         
                                         a->getWindow()->getWidth (),
                                         a->getWindow()->getHeight());
        }

        if(pCam != NULL)
        {
            Matrix m, t;

            // set the projection
            pCam->getProjection          (m, 
                                          pPart->getViewportWidth (), 
                                          pPart->getViewportHeight());

            pCam->getProjectionTranslation(t, 
                                           pPart->getViewportWidth (), 
                                           pPart->getViewportHeight());

            pPart->setupProjection(m, t);

            pCam->getViewing(m, 
                             pPart->getViewportWidth (),
                             pPart->getViewportHeight());


            pPart->setupViewing(m);

            pPart->setNear     (pCam->getNear());
            pPart->setFar      (pCam->getFar ());

            pPart->calcFrustum();
        }

        pPart->setBackground(pBack);
    }

    return ActionBase::Continue;
}

ActionBase::ResultE StageRenderLeave(const NodeCorePtr &pCore,
                                           Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave Stage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    a->popPartition();

    return ActionBase::Continue;
}


ActionBase::ResultE SimpleStageRenderEnter(const NodeCorePtr &pCore,
                                                 Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter SimpleStage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    SimpleStagePtr         pStage = cast_dynamic<SimpleStagePtr>(pCore);

    if(a == NULL || pStage == NullFC)
        return ActionBase::Continue;

    a->pushPartition();

    RenderPartition   *pPart   = a->getActivePartition();

    FrameBufferObject *pTarget = getCPtr(pStage->getRenderTarget());
    Camera            *pCam    = getCPtr(pStage->getCamera      ());
    Background        *pBack   = getCPtr(pStage->getBackground  ());

    pPart->setRenderTarget(pTarget);

    pPart->setViewport(a->getViewport());
    pPart->setWindow  (a->getWindow  ());
    
    if(pTarget != NULL)
    {
        pPart->calcViewportDimension(pStage->getLeft  (),
                                     pStage->getBottom(),
                                     pStage->getRight (),
                                     pStage->getTop   (),
                                     
                                     pTarget->getWidth    (),
                                     pTarget->getHeight   ());
    }

    if(pCam != NULL)
    {
        Matrix m, t;
        
        // set the projection
        pCam->getProjection          (m, 
                                      pPart->getViewportWidth (), 
                                      pPart->getViewportHeight());
        
        pCam->getProjectionTranslation(t, 
                                       pPart->getViewportWidth (), 
                                       pPart->getViewportHeight());
        
        pPart->setupProjection(m, t);
        
        pCam->getViewing(m, 
                         pPart->getViewportWidth (),
                         pPart->getViewportHeight());
        
        
        pPart->setupViewing(m              );

        pPart->setNear     (pCam->getNear());
        pPart->setFar      (pCam->getFar ());

        pPart->calcFrustum (               );

    }

    pPart->setBackground(pBack);

    return ActionBase::Continue;
}

ActionBase::ResultE SimpleStageRenderLeave(const NodeCorePtr &pCore,
                                                 Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave SimpleStage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    a->popPartition();

    return ActionBase::Continue;
}


#ifdef OSG_GV_BETA
ActionBase::ResultE HDRStageRenderEnter(const NodeCorePtr &pCore,
                                              Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter HDRStage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    HDRStagePtr      pStage = cast_dynamic<HDRStagePtr>(pCore);

    a->pushPartition(0, RenderPartition::SimpleCallback);
    {
        Viewport        *pPort  = a->getViewport();
        RenderPartition *pPart  = a->getActivePartition();

        if(pPort != NULL)
        {
            pPart->setViewport(pPort         );
            pPart->setWindow  (a->getWindow());
            
            pPart->calcViewportDimension(pPort->getLeft  (),
                                         pPort->getBottom(),
                                         pPort->getRight (),
                                         pPort->getTop   (),
                                         
                                         a->getWindow()->getWidth (),
                                         a->getWindow()->getHeight());

            Matrix m, t;

            m.setIdentity();
            t.setIdentity();

            MatrixOrthogonal( m,
                              0.f, 1.f,
                              0.f, 1.f,
                             -1.f, 1.f);
            
            pPart->setupProjection(m, t);

            RenderPartition::SimpleDrawCallback f;

            f = boost::bind(&HDRStage::postProcess, pStage, _1);

            pPart->dropFunctor(f);
        }
    }
    a->popPartition();
        
    a->pushPartition();
    {
        RenderPartition   *pPart    = a->getActivePartition();
        FrameBufferObject *pTarget  = getCPtr(pStage->getRenderTarget());
        Viewport          *pPort    = a->getViewport();
        Camera            *pCam     = a->getCamera  ();
        Background        *pBack    = a->getBackground();

        pPart->setRenderTarget(pTarget);

        if(pPort != NULL)
        {
            pPart->setViewport(pPort         );
            pPart->setWindow  (a->getWindow());
            
            if(pTarget != NULL)
            {
                pPart->calcViewportDimension(pPort->getLeft  (),
                                             pPort->getBottom(),
                                             pPort->getRight (),
                                             pPort->getTop   (),
                                             
                                             pTarget->getWidth    (),
                                             pTarget->getHeight   ());
            }
            else
            {
                pPart->calcViewportDimension(pPort->getLeft  (),
                                             pPort->getBottom(),
                                             pPort->getRight (),
                                             pPort->getTop   (),
                                             
                                             a->getWindow()->getWidth (),
                                             a->getWindow()->getHeight());
            }
            
            if(pCam != NULL)
            {
                Matrix m, t;
                
                // set the projection
                pCam->getProjection          (m, 
                                              pPart->getViewportWidth (), 
                                              pPart->getViewportHeight());
                
                pCam->getProjectionTranslation(t, 
                                               pPart->getViewportWidth (), 
                                               pPart->getViewportHeight());
                
                pPart->setupProjection(m, t);
                
                pCam->getViewing(m, 
                                 pPart->getViewportWidth (),
                                 pPart->getViewportHeight());
                
                
                pPart->setupViewing(m);
                
                pPart->setNear     (pCam->getNear());
                pPart->setFar      (pCam->getFar ());
                
                pPart->calcFrustum();
            }
            
            pPart->setBackground(pBack);
        }
        
        NodePtr pActNode = a->getActNode();
        
        a->recurceNoNodeCallbacks(pActNode);
    }
    a->popPartition();

    return Action::Skip;
}

ActionBase::ResultE HDRStageRenderLeave(const NodeCorePtr &pCore,
                                              Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave HDRStage %p\n", &(*pCore)));
#endif

    return Action::Skip;
}



ActionBase::ResultE AlgorithmStageRenderEnter(const NodeCorePtr &pCore,
                                                    Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Enter AlgorithmStage %p\n", &(*pCore)));
#endif

    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);

    AlgorithmStagePtr pStage = cast_dynamic<AlgorithmStagePtr>(pCore);

    a->pushPartition(0, RenderPartition::SimpleCallback);
    {
        RenderPartition *pPart  = a->getActivePartition();

        if(pStage->getProjectionMode() != AlgorithmStage::Ignore)
        {
            Viewport *pPort = a->getViewport();
            
            if(pPort != NULL)
            {
                pPart->setViewport(pPort         );
                pPart->setWindow  (a->getWindow());
                
                pPart->calcViewportDimension(pPort->getLeft  (),
                                             pPort->getBottom(),
                                             pPort->getRight (),
                                             pPort->getTop   (),
                                             
                                             a->getWindow()->getWidth (),
                                             a->getWindow()->getHeight());
                
                Matrix m, t;
                
                m.setIdentity();
                t.setIdentity();
                
                switch(pStage->getProjectionMode())
                {
                    case AlgorithmStage::ZeroOne:
                        MatrixOrthogonal( m,
                                          0.f, 1.f,
                                          0.f, 1.f,
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::CenterOne:
                        MatrixOrthogonal( m,
                                         -1.f, 1.f,
                                         -1.f, 1.f,
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::ZeroSize:
                        MatrixOrthogonal( m,
                                          0.f, pPart->getViewportWidth(),
                                          0.f, pPart->getViewportHeight(),
                                         -1.f, 1.f);
            
                        break;

                    case AlgorithmStage::CenterSize:
                    {
                        Real32 rWHalf = 
                            Real32(pPart->getViewportWidth()) / 2.f;
                        Real32 rHHalf = 
                            Real32(pPart->getViewportWidth()) / 2.f;

                        MatrixOrthogonal( m,
                                         -rWHalf, rWHalf,
                                         -rHHalf, rHHalf,
                                         -1.f, 1.f);
                    }
                    break;

                    case AlgorithmStage::StoredMatrix:
                        
                        m = pStage->getProjectionMatrix();
            
                        break;
                }

                pPart->setSetupMode(RenderPartition::FullSetup);
                pPart->setupProjection(m, t);
            }
            else
            {
                pPart->setSetupMode(RenderPartition::EmptySetup);
            }
        }
        else
        {
            pPart->setSetupMode(RenderPartition::EmptySetup);
        }
         
        RenderPartition::SimpleDrawCallback f;
        
        f = boost::bind(&AlgorithmStage::execute, pStage, _1);
        
        pPart->dropFunctor(f);
    }
    a->popPartition();

    return Action::Skip;
}

ActionBase::ResultE AlgorithmStageRenderLeave(const NodeCorePtr &pCore,
                                                    Action      *action)
{
#ifdef OSG_DUMP_TRAVERSAL
    FDEBUG_GV(("Leave AlgorithmStage %p\n", &(*pCore)));
#endif

    return Action::Skip;
}
#endif

ActionBase::ResultE VisitSubTreeRender(const NodeCorePtr &pCore,
                                             Action      *action)
{
    RenderTraversalAction *a = dynamic_cast<RenderTraversalAction *>(action);
    VisitSubTreePtr pVisit = cast_dynamic<VisitSubTreePtr>(pCore);

    a->useNodeList();
    
    if(a->isVisible(getCPtr(pVisit->getSubTreeRoot())))
        a->addNode(pVisit->getSubTreeRoot());

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                   init                                  */

bool RenderTraversalActionInitialize(void)
{
#if 0
    RenderTraversalAction::registerEnterDefault( 
        Slices::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(
                &ShadingCallbacks::matDrawableRenderEnter));
#endif

    RenderTraversalAction::registerEnterDefault(
        Geometry::getClassType(),
        MaterialDrawableRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        Geometry::getClassType(),
        MaterialDrawableRenderLeave);

    RenderTraversalAction::registerEnterDefault(
        Particles::getClassType(),
        MaterialDrawableRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        Particles::getClassType(),
        MaterialDrawableRenderLeave);

#if 1


#if 0
    ShadingAction::registerEnterDefault( 
        Particles::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(
                &ShadingCallbacks::matDrawableRenderEnter));
#endif

    RenderTraversalAction::registerEnterDefault( 
        Group::getClassType(),
        GroupRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        Group::getClassType(), 
        GroupRenderLeave);

    RenderTraversalAction::registerEnterDefault( 
        Billboard::getClassType(),
        BillboardRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        Billboard::getClassType(), 
        BillboardRenderLeave);

    RenderTraversalAction::registerEnterDefault(
        Switch::getClassType(),
        SwitchRenderEnter);
    
    RenderTraversalAction::registerLeaveDefault(
        Switch::getClassType(),
        SwitchRenderLeave);
    
    RenderTraversalAction::registerEnterDefault(
        ComponentTransform::getClassType(), 
        TransformRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        ComponentTransform::getClassType(), 
        TransformRenderLeave);


#if 0
    ShadingAction::registerEnterDefault(
        DistanceLOD::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(&ShadingCallbacks::distanceLODRender));
#endif

    RenderTraversalAction::registerEnterDefault(
        MaterialGroup::getClassType(), 
        MaterialGroupRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        MaterialGroup::getClassType(), 
        MaterialGroupRenderLeave);

#if 0
    ShadingAction::registerEnterDefault(
        Switch::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(&ShadingCallbacks::switchRender));
#endif

    RenderTraversalAction::registerEnterDefault(
        Transform::getClassType(), 
        TransformRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        Transform::getClassType(), 
        TransformRenderLeave);

    RenderTraversalAction::registerEnterDefault( 
        DirectionalLight::getClassType(), 
        DirectionalLightRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        DirectionalLight::getClassType(), 
        DirectionalLightRenderLeave);

#if 0
    RenderTraversalAction::registerEnterDefault( 
        ShadowDirectionalLight::getClassType(), 
        ShadowDirectionalLightRenderEnter);

    RenderTraversalAction::registerLeaveDefault(
        ShadowDirectionalLight::getClassType(), 
        ShadowDirectionalLightRenderLeave);
#endif


    RenderTraversalAction::registerEnterDefault( 
        PointLight::getClassType(), 
        PointLightRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        PointLight::getClassType(), 
        PointLightRenderLeave);


    RenderTraversalAction::registerEnterDefault(
        SpotLight::getClassType(), 
              SpotLightRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        SpotLight::getClassType(), 
        SpotLightRenderLeave);


#if 0
    RenderTraversalAction::registerEnterDefault(
        ShadowSpotLight::getClassType(), 
        ShadowSpotLightRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        ShadowSpotLight::getClassType(), 
        ShadowSpotLightRenderLeave);
#endif


    RenderTraversalAction::registerEnterDefault(
        Stage::getClassType(), 
              StageRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        Stage::getClassType(), 
              StageRenderLeave);

    RenderTraversalAction::registerEnterDefault(
        SimpleStage::getClassType(), 
              SimpleStageRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        SimpleStage::getClassType(), 
              SimpleStageRenderLeave);


#ifdef OSG_GV_BETA
    RenderTraversalAction::registerEnterDefault(
        HDRStage::getClassType(), 
              HDRStageRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        HDRStage::getClassType(), 
              HDRStageRenderLeave);

    RenderTraversalAction::registerEnterDefault(
        AlgorithmStage::getClassType(), 
              AlgorithmStageRenderEnter);

    RenderTraversalAction::registerLeaveDefault( 
        AlgorithmStage::getClassType(), 
              AlgorithmStageRenderLeave);
#endif


    RenderTraversalAction::registerEnterDefault(
        VisitSubTree::getClassType(), 
              VisitSubTreeRender);


    return true;

#endif
}

struct RenderTraversalActionInit
{
    RenderTraversalActionInit(void) 
    { 
        addPostFactoryInitFunction(RenderTraversalActionInitialize); 
    }
};

static RenderTraversalActionInit initDummy;

OSG_END_NAMESPACE





/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#endif
