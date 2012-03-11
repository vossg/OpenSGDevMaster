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

#include "OSGConfig.h"

#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGRenderAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGVolumeDraw.h"

#include "OSGRenderCallbackStage.h"

#include "OSGBackground.h"
#include "OSGFrameBufferObject.h"
#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGRenderCallbackStageBase.cpp file.
// To modify it, please change the .fcd file (OSGRenderCallbackStage.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void RenderCallbackStage::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void RenderCallbackStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                               const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

RenderCallbackStage::RenderCallbackStage(void) :
    Inherited()
{
}

RenderCallbackStage::RenderCallbackStage(const RenderCallbackStage &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

RenderCallbackStage::~RenderCallbackStage(void)
{
}

void RenderCallbackStage::addCallbacks(RenderPartition *pPartition)
{
    if(pPartition == NULL)
        return;

    RenderCallbackStage::RenderFunctorStore vCallbackStore;

    this->fillPreRenderStore(vCallbackStore);

    RenderCallbackStage::RenderFunctorStore::const_iterator cbIt  = 
        vCallbackStore.begin();

    RenderCallbackStage::RenderFunctorStore::const_iterator cbEnd = 
        vCallbackStore.end  ();

    while(cbIt != cbEnd)
    {
        pPartition->addPreRenderCallback(*cbIt);
        
        ++cbIt;
    }


    vCallbackStore.clear();

    this->fillPostRenderStore(vCallbackStore);

    cbIt  = vCallbackStore.begin();
    cbEnd = vCallbackStore.end  ();

    while(cbIt != cbEnd)
    {
        pPartition->addPostRenderCallback(*cbIt);
        
        ++cbIt;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

/*!
  Draw loaded geometry. If nothing was loaded until now, start
  loading. If loading is not finished, draw the children of 
  thid group.
 */

Action::ResultE RenderCallbackStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return Action::Continue;

    Inherited::renderEnter(action);

    RenderPartition *pPart   = a->getActivePartition();

    this->addCallbacks(pPart);

    return Action::Continue;
}

Action::ResultE RenderCallbackStage::renderLeave(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    this->popPartition(a);

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               loading                                   */


UInt32 RenderCallbackStage::addPreRenderFunctor(RenderFunctor func,
                                                std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._uiId         = _mfPreRenderCallbacks.size32();
    oTmp._createSymbol = createSymbol;

    _mfPreRenderCallbacks.push_back(oTmp);

    return oTmp._uiId;
}


void RenderCallbackStage::subPreRenderFunctor(UInt32 uiId)
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


void RenderCallbackStage::clearPreRenderFunctors(void)
{
    _mfPreRenderCallbacks.clear();
}


UInt32 RenderCallbackStage::addPostRenderFunctor(RenderFunctor func,
                                                 std::string   createSymbol)
{
    RenderFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._uiId         = _mfPostRenderCallbacks.size32();
    oTmp._createSymbol = createSymbol;

    _mfPostRenderCallbacks.push_back(oTmp);

    return oTmp._uiId;
}


void RenderCallbackStage::subPostRenderFunctor(UInt32 uiId)
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


void RenderCallbackStage::clearPostRenderFunctors(void)
{
    _mfPostRenderCallbacks.clear();
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

void RenderCallbackStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            RenderCallbackStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &RenderCallbackStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            RenderCallbackStage::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &RenderCallbackStage::renderLeave));
    }
}
