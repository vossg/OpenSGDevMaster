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

#include <sstream>
#include <fstream>

#include <OSGConfig.h>

#include <OSGAction.h>
#include <OSGCamera.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGVolumeDraw.h>

#include "OSGSimpleStage.h"

#include "OSGBackground.h"
#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSimpleStageBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleStage.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void SimpleStage::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void SimpleStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SimpleStage::SimpleStage(void) :
    Inherited()
{
}

SimpleStage::SimpleStage(const SimpleStage &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SimpleStage::~SimpleStage(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

ActionBase::ResultE SimpleStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    RenderPartition   *pParentPart = a   ->getActivePartition();
    FrameBufferObject *pTarget     = this->getRenderTarget();

    Background        *pBack   = this->getBackground();
    Viewport          *pPort   = a->getViewport();
    Window            *pWin    = a->getWindow  ();

    SimpleStage::RenderFunctorStore vCallbackStore;

    if(pTarget == NULL && this->getInheritedTarget() == true)
    {
        pTarget = pParentPart->getRenderTarget();
    }

    a->pushPartition();
    
    RenderPartition   *pPart   = a->getActivePartition();
    Camera            *pCam    = this->getCamera();
    
    pPart->setRenderTarget(pTarget);
    
//    pPart->setViewport(pPort);
    pPart->setWindow  (pWin );
    
    if(pTarget != NULL)
    {
        pPart->calcViewportDimension(this->getLeft  (),
                                     this->getBottom(),
                                     this->getRight (),
                                     this->getTop   (),
                                     
                                     pTarget->getWidth    (),
                                     pTarget->getHeight   ());
    }
    else if(pWin != NULL)
    {
        pPart->calcViewportDimension(this->getLeft  (),
                                     this->getBottom(),
                                     this->getRight (),
                                     this->getTop   (),
                                     
                                     pWin->getWidth   (),
                                     pWin->getHeight  ());
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
    
    this->fillPreRenderStore(vCallbackStore);

    SimpleStage::RenderFunctorStore::const_iterator cbIt  = 
        vCallbackStore.begin();

    SimpleStage::RenderFunctorStore::const_iterator cbEnd = 
        vCallbackStore.end  ();

    while(cbIt != cbEnd)
    {
        pPart->addPreRenderCallback(*cbIt);
        
        ++cbIt;
    }


    vCallbackStore.clear();

    this->fillPostRenderStore(vCallbackStore);

    cbIt  = vCallbackStore.begin();
    cbEnd = vCallbackStore.end  ();

    while(cbIt != cbEnd)
    {
        pPart->addPostRenderCallback(*cbIt);
        
        ++cbIt;
    }


    pPart->setBackground(pBack);

    return ActionBase::Continue;
}

ActionBase::ResultE SimpleStage::renderLeave(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    a->popPartition();

    return ActionBase::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */


UInt32 SimpleStage::addPreRenderFunctor(RenderFunctor func,
                                        std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._uiId         = _mfPreRenderCallbacks.size();
    oTmp._createSymbol = createSymbol;

    _mfPreRenderCallbacks.push_back(oTmp);

    return oTmp._uiId;
}


void SimpleStage::subPreRenderFunctor(UInt32 uiId)
{
    MFRenderFunctorCallback::iterator       cfIt = 
        _mfPreRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPreRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_uiId == uiId)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfPreRenderCallbacks.erase(cfIt);
}


void SimpleStage::clearPreRenderFunctors(void)
{
    _mfPreRenderCallbacks.clear();
}


UInt32 SimpleStage::addPostRenderFunctor(RenderFunctor func,
                                         std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._uiId         = _mfPostRenderCallbacks.size();
    oTmp._createSymbol = createSymbol;

    _mfPostRenderCallbacks.push_back(oTmp);

    return oTmp._uiId;
}


void SimpleStage::subPostRenderFunctor(UInt32 uiId)
{
    MFRenderFunctorCallback::iterator       cfIt = 
        _mfPostRenderCallbacks.begin();

    MFRenderFunctorCallback::const_iterator cfEnd= 
        _mfPostRenderCallbacks.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_uiId == uiId)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfPostRenderCallbacks.erase(cfIt);
}


void SimpleStage::clearPostRenderFunctors(void)
{
    _mfPostRenderCallbacks.clear();
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void SimpleStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            SimpleStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SimpleStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            SimpleStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&SimpleStage::renderLeave));
    }
}
