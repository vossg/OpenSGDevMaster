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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGRenderPartition.h"
#include "OSGRenderTreeNodePool.h"
#include "OSGRenderAction.h"
#include "OSGStateOverridePool.h"
#include "OSGTreeBuilderBase.h"
#include "OSGBackground.h"
#include "OSGFrameBufferObject.h"
#include "OSGVolumeDraw.h"

#include "OSGCamera.h"
#include "OSGFrameBufferAttachment.h"

#include "OSGStateSortTreeBuilder.h"
#include "OSGDepthSortTreeBuilder.h"
#include "OSGOcclusionCullingTreeBuilder.h"

#include "OSGDrawableStatsAttachment.h"
#ifdef OSG_NEW_SHADER
#include "OSGShaderProgramChunk.h"
#include "OSGShaderProgramVariableChunk.h"
#include "OSGShaderExecutableChunk.h"
#include "OSGShaderCache.h"
#endif

#ifdef OSG_DEBUG
#define OSG_TRACE_PARTITION
#endif

#include "OSGOSGSceneFileType.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class RenderPartition

In many ways it is equivalent to a drawing pass. For simple cases there will
be only one, and it will take care of everything. For cases involving shadow
map shadows there will be one partition that creates the shadow map and one
that draws the scene and shadows etc.


*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StatElemDesc<StatIntElem>
    RenderPartition::statCullTestedNodes("Partition::cullTestedNodes",
                                         "nodes tested"             );

StatElemDesc<StatIntElem>
    RenderPartition::statCulledNodes    ("Partition::culledNodes",
                                        "nodes culled from frustum");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void RenderPartition::setAction(RenderAction *pAction)
{
    _oDrawEnv.setAction(pAction);
}


/*------------- constructors & destructors --------------------------------*/

RenderPartition::RenderPartition(Mode eMode) :
     Inherited               (         ),
    _eMode                   (eMode    ),
    _uiSetupMode             (FullSetup),
    _bDone                   (false    ),
    _vGroupStore             (         ),

    _oDrawEnv                (         ),
    _oSimpleDrawCallback     (     NULL),
    _pBackground             (     NULL),

    _uiMatrixId              (        0),
    _modelMatrixValid        (true     ),
    _modelViewMatrix         (         ),
    _modelMatrix             (         ),
    _modelViewMatrixStack    (         ),

    _pNodePool               (     NULL),

    _mMatTrees               (         ),
    _mTransMatTrees          (         ),

    _uiActiveMatrix          (        0),

    _pStatePool              (     NULL),
    _sStateOverrides         (         ),

    _pTreeBuilderPool        (     NULL),

    _iNextLightIndex         (        0),
    _uiLightState            (        0),
    _uiKeyGen                (        0),

    _pMaterial               (     NULL),
    _pMaterialNode           (     NULL),
    _addedStateOverride      (    false),

    _pRenderTarget           (     NULL),
    _eDrawBuffer             (  GL_NONE),

    _visibilityStack         (         ),
    _bFrustumCulling         (    true ),
    _bVolumeDrawing          (    false),
    _bAutoFrustum            (    true ),
    _oFrustum                (         ),
    _vPreRenderCallbacks     (         ),
    _vPostRenderCallbacks    (         ),
    _pNode                   (     NULL)
#ifdef OSG_DEBUG
   ,_szDebugString           (         )
#endif
{
    _modelViewMatrix.first = 1;
    _modelViewMatrix.second.setIdentity();
}

RenderPartition::~RenderPartition(void)
{
}

/*------------------------------ access -----------------------------------*/

OSG_BEGIN_NAMESPACE

struct ResetSecond
{
    void operator() (std::pair<const Int32, TreeBuilderBase *> &oPair)
    {
        oPair.second = NULL;
    }
};

OSG_END_NAMESPACE

void RenderPartition::reset(Mode eMode)
{
    _eMode = eMode;

    _uiSetupMode = FullSetup;

    _bDone       = false;

    _vGroupStore.clear();

    _vPreRenderCallbacks .clear();
    _vPostRenderCallbacks.clear();

    _eDrawBuffer = GL_NONE;

#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "reset %p\n", this);
#endif

    if(_eMode == StateSorting || _eMode == TransformSorting)
    {
        _pBackground = NULL;

        _uiMatrixId = 1;

        _modelViewMatrix.first = 1;
        _modelViewMatrix.second.setIdentity();

        _modelMatrixValid      = true;
        _modelMatrix           .setIdentity();

        _modelViewMatrixStack.clear();


        std::for_each(_mMatTrees     .begin(),
                      _mMatTrees     .end(), ResetSecond());
        std::for_each(_mTransMatTrees.begin(),
                      _mTransMatTrees.end(), ResetSecond());


        _bSortTrans       = true;
        _bZWriteTrans     = false;
        _bCorrectNegScale = false;

        _uiActiveMatrix           = 0;

        _oDrawEnv.clearState();

        while(_sStateOverrides.empty() == false)
        {
            _sStateOverrides.pop();
        }


        _iNextLightIndex = 0;
        _uiLightState    = 0;

        _pMaterial          = NULL;
        _pMaterialNode      = NULL;
        _addedStateOverride = false;

        _pRenderTarget    = NULL;

        _visibilityStack.clear();

        _bFrustumCulling = true;
        _bVolumeDrawing  = false;
        _bAutoFrustum    = true;
    }
    else
    {
        _pBackground      = NULL;

        _pRenderTarget    = NULL;

        _oDrawEnv.clearState();

        while(_sStateOverrides.empty() == false)
        {
            _sStateOverrides.pop();
        }

        _oSimpleDrawCallback = NULL;
    }

    _uiNumTriangles = 0;
    _ubState        = RenderPartitionBase::Full;

    _pNode = NULL;
/*
    static FrustumVolume empty;

    _oFrustum = empty;
 */
}

void RenderPartition::calcFrustum(void)
{
    Matrix pr = _oDrawEnv.getCameraFullProjection();

    pr.mult(_oDrawEnv.getCameraViewing());

    _oFrustum.setPlanes(pr);
}

void RenderPartition::calcViewportDimension(Real32 rLeft,
                                            Real32 rBottom,
                                            Real32 rRight,
                                            Real32 rTop,

                                            UInt16 iTargetWidth,
                                            UInt16 iTargetHeight)
{
    Int32 iPixelLeft;
    Int32 iPixelRight;
    Int32 iPixelTop;
    Int32 iPixelBottom;

    if(rLeft > 1.f)
        iPixelLeft = Int32(rLeft);
    else
        iPixelLeft = Int32(iTargetWidth * rLeft);

    if(rRight > 1.f)
        iPixelRight = Int32(rRight);
    else
        iPixelRight = Int32(iTargetWidth * rRight) - 1;


    if(rBottom > 1.f)
        iPixelBottom = Int32(rBottom);
    else
        iPixelBottom = Int32(iTargetHeight * rBottom);

    if(rTop > 1.f)
        iPixelTop = Int32(rTop);
    else
        iPixelTop = Int32(iTargetHeight * rTop) - 1;


    bool bFull = ( (iPixelLeft   == 0                ) &&
                   (iPixelRight  == iTargetWidth  - 1) &&
                   (iPixelBottom == 0                ) &&
                   (iPixelTop    == iTargetHeight - 1)  );

    _oDrawEnv.setViewportDimension(iPixelLeft,
                                   iPixelBottom,
                                   iPixelRight,
                                   iPixelTop,
                                   bFull       );
}

void RenderPartition::setupExecution(bool bUpdateGlobalViewport)
{
    if(_bDone == true)
        return;

#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "setupexecute %p %d\n", this, UInt32(_ubState));
    fflush(stderr);
#endif

#ifdef OSG_TRACE_PARTITION
    if(_szDebugString.size() != 0)
    {
        fprintf(stderr,
                "RenderPartition::setupExecution %s\n",
                _szDebugString.c_str());
    }
#endif

    if(_pRenderTarget != NULL)
        _pRenderTarget->activate(&_oDrawEnv, _eDrawBuffer);

    // We always push so stages with callbacks can modify the values
    // as needed

    if(bUpdateGlobalViewport == false)
        glPushAttrib(GL_VIEWPORT_BIT | GL_SCISSOR_BIT);

    if(0x0000 != (_uiSetupMode & ViewportSetup))
    {
        if(0x0000 == (_uiSetupMode & PassiveBit))
        {
            glViewport(_oDrawEnv.getPixelLeft  (),
                       _oDrawEnv.getPixelBottom(),
                       _oDrawEnv.getPixelWidth (),
                       _oDrawEnv.getPixelHeight());

            if(_oDrawEnv.getFull() == false)
            {
                glScissor (_oDrawEnv.getPixelLeft  (),
                           _oDrawEnv.getPixelBottom(),
                           _oDrawEnv.getPixelWidth (),
                           _oDrawEnv.getPixelHeight());

                glEnable(GL_SCISSOR_TEST);
            }
            else
            {
                glDisable(GL_SCISSOR_TEST);
            }
        }
    }
    else
    {
        glDisable(GL_SCISSOR_TEST);
    }

    if(bUpdateGlobalViewport == true)
        glPushAttrib(GL_VIEWPORT_BIT | GL_SCISSOR_BIT);

    if(0x0000 != (_uiSetupMode & ProjectionSetup))
    {
        glMatrixMode (GL_PROJECTION);
        glPushMatrix();

        glLoadMatrixf(_oDrawEnv.getCameraFullProjection().getValues());

        glMatrixMode(GL_MODELVIEW);
    }

    RenderCallbackStore::const_iterator cbIt  = _vPreRenderCallbacks.begin();
    RenderCallbackStore::const_iterator cbEnd = _vPreRenderCallbacks.end  ();

    while(cbIt != cbEnd)
    {
        (*cbIt)(&_oDrawEnv);
        ++cbIt;
    }

    if(0x0000 != (_uiSetupMode & BackgroundSetup))
    {
        if(_pBackground != NULL)
        {
            _pBackground->clear(&_oDrawEnv); //, _oDrawEnv.getViewport());
        }
    }
}

void RenderPartition::doExecution   (void)
{
    if(_bDone == true)
        return;

#ifdef OSG_TRACE_PARTITION
    if(_szDebugString.size() != 0)
    {
        fprintf(stderr,
                "RenderPartition::doExecution %s\n",
                _szDebugString.c_str());
    }
#endif

    if(_eMode == SimpleCallback)
    {
        _oSimpleDrawCallback(&_oDrawEnv);
    }
    else
    {
        BuildKeyMapIt      mapIt  = _mMatTrees.begin();
        BuildKeyMapConstIt mapEnd = _mMatTrees.end  ();

        _uiNumMatrixChanges = 0;

        while(mapIt != mapEnd)
        {
            if(mapIt->second != NULL)
            {
                mapIt->second->draw(_oDrawEnv, this);
            }

            ++mapIt;
        }

        mapIt  = _mTransMatTrees.begin();
        mapEnd = _mTransMatTrees.end  ();

        if(!_bZWriteTrans)
            glDepthMask(false);

        while(mapIt != mapEnd)
        {
            if(mapIt->second != NULL)
            {
                mapIt->second->draw(_oDrawEnv, this);
            }

            ++mapIt;
        }

        if(!_bZWriteTrans)
            glDepthMask(true);
    }

    RenderCallbackStore::const_iterator cbIt  = _vPostRenderCallbacks.begin();
    RenderCallbackStore::const_iterator cbEnd = _vPostRenderCallbacks.end  ();

    while(cbIt != cbEnd)
    {
        (*cbIt)(&_oDrawEnv);
        ++cbIt;
    }

    if(0x0000 != (_uiSetupMode & ProjectionSetup))
    {
        glMatrixMode (GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    // We always push/pop so stages with callback can modify the values
    // as needed

    glPopAttrib();

    if(_pRenderTarget != NULL)
        _pRenderTarget->deactivate(&_oDrawEnv);

    this->exit();
}


void RenderPartition::execute(void)
{
    if(_bDone == false)
    {
        setupExecution();
        doExecution   ();
    }

    GroupStore::iterator gIt  = _vGroupStore.begin();
    GroupStore::iterator gEnd = _vGroupStore.end  ();

    while(gIt != gEnd)
    {
        (*gIt)->execute();
//        (*gIt)->exit   ();

        ++gIt;
    }
}

void RenderPartition::execute(HardwareContext *pContext, DrawEnv *pEnv)
{
#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "execute %p %d\n", this, UInt32(_ubState));
    fflush(stderr);
#endif

    switch(_ubState)
    {
        case Setup:
        {
            this->setupExecution(true);
            ++_ubState;
        }
        break;

        case Execute:
        {
            this->doExecution();
            ++_ubState;
        }
        break;

        case Full:
        {
            if(_bDone == false)
            {
                setupExecution();
                doExecution   ();
            }
        }
        break;
    }

#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "execute done %p %d\n", this, UInt32(_ubState));
    fflush(stderr);
#endif
}

void RenderPartition::dump(UInt32 uiIndent)
{
    uiIndent += 4;

    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "RenderParition %p | %d\n", this, Int32(_ubState));

    for(UInt32 i = 0; i < uiIndent; ++i) { fprintf(stderr, " "); }
    fprintf(stderr, "with %"PRISize" groups\n", _vGroupStore.size());

    GroupStore::iterator gIt  = _vGroupStore.begin();
    GroupStore::iterator gEnd = _vGroupStore.end  ();

    while(gIt != gEnd)
    {
        (*gIt)->dump(uiIndent + 4);

        ++gIt;
    }

}

/*---------------------------- properties ---------------------------------*/

bool RenderPartition::pushShaderState(State *pState)
{
    bool statePushed = false;

#ifdef OSG_NEW_SHADER
    if(pState != NULL)
    {
        ShaderProgramChunk *pSPChunk =
            static_cast<ShaderProgramChunk *>(
                pState->getChunk(ShaderProgramChunk::getStaticClassId()));
        ShaderProgramVariableChunk *pSPVChunk =
            static_cast<ShaderProgramVariableChunk *>(
                pState->getChunk(ShaderProgramVariableChunk::getStaticClassId()));

        if(pSPChunk != NULL || pSPVChunk != NULL)
        {
            this->pushState();

            statePushed = true;
        }

        if(pSPChunk != NULL)
        {
            _sStateOverrides.top()->addOverride(0, pSPChunk);
            _sStateOverrides.top()->setShader  (NULL       );
        }

        if(pSPVChunk != NULL)
        {
            _sStateOverrides.top()->addOverride (0, pSPVChunk);
            _sStateOverrides.top()->setShaderVar(NULL        );
        }
    }

    if(_sStateOverrides.top()->getShader ()         == NULL  &&
       _sStateOverrides.top()->getProgIds().empty() == false   )
    {
        ShaderExecutableChunkUnrecPtr pShader =
            _oDrawEnv.getWindow()->getShaderCache()->findShader(
                _sStateOverrides.top()->getProgIds());

        if(pShader == NULL)
        {
            pShader = ShaderExecutableChunk::create();

            typedef StateOverride::ProgramChunkStore ProgChunkStore;

            ProgChunkStore::const_iterator pIt =
                _sStateOverrides.top()->getPrograms().begin();
            ProgChunkStore::const_iterator pEnd =
                _sStateOverrides.top()->getPrograms().end  ();

            for(; pIt != pEnd; ++pIt)
            {
                pShader->merge(*pIt);
            }

            _oDrawEnv.getWindow()->getShaderCache()->addShader(
                _sStateOverrides.top()->getProgIds(), pShader);
        }

        _sStateOverrides.top()->setShader(pShader);
        _sStateOverrides.top()->addOverride(
            ShaderExecutableChunk::getStaticClassId(),
            pShader                      );

        OSG_ASSERT(ShaderExecutableChunk::getStaticClassId() ==
                   pShader->getClassId()                       );

    }

    if(_sStateOverrides.top()->getShaderVar()         == NULL &&
       _sStateOverrides.top()->getVarIds   ().empty() == false   )
    {
        ShaderExecutableVarChunkUnrecPtr pShaderVar =
            _oDrawEnv.getWindow()->getShaderCache()->findShaderVar(
                _sStateOverrides.top()->getVarIds());

        if(pShaderVar == NULL)
        {
            pShaderVar = ShaderExecutableVarChunk::create();

            typedef StateOverride::ProgramVarChunkStore ProgVarChunkStore;

            ProgVarChunkStore::const_iterator vIt =
                _sStateOverrides.top()->getVariables().begin();
            ProgVarChunkStore::const_iterator vEnd =
                _sStateOverrides.top()->getVariables().end();

            for(; vIt != vEnd; ++vIt)
            {
                pShaderVar->merge(*vIt);
            }

            _oDrawEnv.getWindow()->getShaderCache()->addShaderVar(
                _sStateOverrides.top()->getVarIds(), pShaderVar);
        }

        _sStateOverrides.top()->setShaderVar(pShaderVar);
        _sStateOverrides.top()->addOverride (
            ShaderExecutableVarChunk::getStaticClassId(),
            pShaderVar);

        OSG_ASSERT(ShaderExecutableVarChunk::getStaticClassId() ==
                   pShaderVar->getClassId()                       );

    }
#endif // OSG_NEW_SHADER

    return statePushed;
}

void RenderPartition::dropFunctor(DrawFunctor &drawFunc,
                                  State       *pState,
                                  Int32        iSortKey,
                                  bool         bIgnoreOverrides)
{
    if(_eMode == SimpleCallback)
        return;

    RenderAction  *ract    = dynamic_cast<RenderAction *>(_oDrawEnv.getAction());
    Node          *actNode = ract   ->getActNode();
    NodeCore      *actCore = actNode->getCore   ();

    bool           bOverrodeState = false;
    StateOverride *pStateOverride = NULL;

    DrawableStatsAttachment *st = DrawableStatsAttachment::get(actCore);

    if(st == NULL)
    {
        DrawableStatsAttachment::addTo(actCore);

        st = DrawableStatsAttachment::get(actCore);
    }

    st->validate();

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(
            RenderAction::statNTriangles)->add(st->getTriangles());
    }

    _uiNumTriangles += st->getTriangles();

    #ifdef OSG_NEW_SHADER
    bOverrodeState = pushShaderState(pState);
#endif // OSG_NEW_SHADER

    if(_sStateOverrides.top()->empty() == false &&
       bIgnoreOverrides                == false   )
    {
        pStateOverride = _sStateOverrides.top();
    }

    bool bTransparent =
        (pState->isTransparent()                                         ) ||
        (pStateOverride != NULL ? pStateOverride->isTransparent() : false);

    if(_bSortTrans == true && bTransparent == true)
    {
        BuildKeyMapIt mapIt = _mTransMatTrees.lower_bound(iSortKey);

        if(mapIt == _mTransMatTrees.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<DepthSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mTransMatTrees.insert(
                mapIt, BuildKeyMap::value_type(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<DepthSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);
            
            mapIt->second = pBuilder;
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           drawFunc,
                           pState,
                           pStateOverride);
    }
    else if(ract != NULL && ract->getOcclusionCulling() == true)
    {
        BuildKeyMapIt mapIt = _mMatTrees.lower_bound(iSortKey);

        if(mapIt == _mMatTrees.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<OcclusionCullingTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mMatTrees.insert(mapIt,
                                      std::make_pair(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second =
                _pTreeBuilderPool->create<OcclusionCullingTreeBuilder>();

            mapIt->second->setNodePool(_pNodePool);
        }
       
        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           drawFunc,
                           pState,
                           pStateOverride);
    }
    else
    {
        BuildKeyMapIt mapIt = _mMatTrees.lower_bound(iSortKey);

        if(mapIt == _mMatTrees.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<StateSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mMatTrees.insert(
                mapIt, BuildKeyMap::value_type(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second = 
                _pTreeBuilderPool->create<StateSortTreeBuilder>();

            mapIt->second->setNodePool(_pNodePool);
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           drawFunc,
                           pState,
                           pStateOverride);
    }

#ifdef OSG_NEW_SHADER
    if(bOverrodeState == true)
    {
        this->popState();
    }
#endif
}

// ==============================================
#if 0
void RenderPartition::dropFunctor(DrawFunctor &func,
                                  State       *pState,
                                  Int32        iSortKey,
                                  bool         bIgnoreOverrides)
{
    if(_eMode == SimpleCallback)
        return;

    RenderAction *rt = dynamic_cast<RenderAction *>(_oDrawEnv.getAction());

    Node         *actNode = rt     ->getActNode();
    NodeCore     *actCore = actNode->getCore   ();

    // Add Stats
    DrawableStatsAttachment *st;
    bool                     bOverrodeState = false;
    StateOverride           *pStateOverride = NULL;

    st = DrawableStatsAttachment::get(actCore);

    if(st == NULL)
    {
        DrawableStatsAttachment::addTo(actCore);

        st = DrawableStatsAttachment::get(actCore);
    }

    st->validate();

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(
            RenderAction::statNTriangles)->add(st->getTriangles());
    }

    _uiNumTriangles += st->getTriangles();

#ifdef OSG_NEW_SHADER
    bOverrodeState = pushShaderState(pState);
#endif // OSG_NEW_SHADER

    if(_sStateOverrides.top()->empty() == false &&
       bIgnoreOverrides                == false   )
    {
        pStateOverride = _sStateOverrides.top();
    }

    bool bTransparent =
        (pState->isTransparent()                                         ) ||
        (pStateOverride != NULL ? pStateOverride->isTransparent() : false);

    if(_bSortTrans == true && bTransparent == true)
    {
        BuildKeyMapIt mapIt = _mTransMatTrees.lower_bound(iSortKey);

        if(mapIt == _mTransMatTrees.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<DepthSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mTransMatTrees.insert(
                mapIt, BuildKeyMap::value_type(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<DepthSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);
            
            mapIt->second = pBuilder;
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           func,
                           pState,
                           pStateOverride);


#if 0
        BuildKeyMapIt mapIt = _mTransMatRoots.lower_bound(iSortKey);

        if(mapIt == _mTransMatRoots.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<ScalarSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mTransMatRoots.insert(mapIt,
                                           std::make_pair(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second =
                _pTreeBuilderPool->create<ScalarSortTreeBuilder>();

            mapIt->second->setNodePool(_pNodePool);
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           func,
                           _uiKeyGen);


        RenderTreeNode *pNewElem = _pNodePool->create<RenderTreeNode>();

        Pnt3f         objPos;

        actNode->getVolume().getCenter(objPos);

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        _modelViewMatrix.second.mult(objPos, objPos);
#else
        Pnt3d temp(objPos[0], objPos[1], objPos[2]);
        _modelViewMatrix.second.mult(temp);
#endif

        pNewElem->setNode        (&*actNode         );
        pNewElem->setFunctor     (  func            );
        pNewElem->setState       (  pState          );

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        pNewElem->setMatrixStore (  _modelViewMatrix);
        pNewElem->setScalar      (  objPos[2]       );
#else
        // Now that we have accumulated all transformations we can convert back
        // to a floating point matrix.
        Matrix4f tempMat;
        tempMat.convertFrom(_modelViewMatrix.second);
        std::pair<UInt32, Matrix> temp_ms(_modelViewMatrix.first, tempMat);

        pNewElem->setMatrixStore (temp_ms      );
        pNewElem->setScalar      ( temp[2]     );
#endif

        pNewElem->setLightState  (_uiLightState);

        if(_sStateOverrides.top()->empty() == false &&
            bIgnoreOverrides               == false  )
        {
            pNewElem->setStateOverride(_sStateOverrides.top());
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                            this,
                            pNewElem,
                            NULL,
                            NULL,
                            0);
#endif
    }
    else if(rt != NULL && rt->getOcclusionCulling() == true)
    {
        BuildKeyMapIt mapIt = _mMatRoots.lower_bound(iSortKey);

        if(mapIt == _mMatRoots.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<OcclusionCullingTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mMatRoots.insert(mapIt,
                                      std::make_pair(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second =
                _pTreeBuilderPool->create<OcclusionCullingTreeBuilder>();

            mapIt->second->setNodePool(_pNodePool);
        }

        RenderTreeNode  *pNewElem = _pNodePool->create<RenderTreeNode>();

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        Pnt3f            objPos;
#else
        Pnt3d            objPos;
#endif

        //_oDrawEnv.getRTAction()->getActNode()->getVolume().getCenter(objPos);

        //_modelViewMatrix.second.mult(objPos, objPos);

        const BoxVolume &objVol   = actNode->getVolume();

        Pnt3r min,max;

        objVol.getBounds(min,max);

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        Pnt3r p[8];
#else
        Pnt3d p[8];
#endif
        p[0].setValues(min[0],min[1],min[2]);
        p[1].setValues(max[0],min[1],min[2]);
        p[2].setValues(min[0],max[1],min[2]);
        p[3].setValues(min[0],min[1],max[2]);
        p[4].setValues(max[0],max[1],min[2]);
        p[5].setValues(max[0],min[1],max[2]);
        p[6].setValues(min[0],max[1],max[2]);
        p[7].setValues(max[0],max[1],max[2]);

        for(UInt32 i = 0; i < 8; i++)
        {
            _modelViewMatrix.second.mult(p[i], p[i]);
        }

        objPos = p[0];

        for(UInt32 i = 1; i < 8; ++i)
        {
            if(p[i][2] < objPos[2])
                objPos[2] = p[i][2];
        }

        //std::cout << objPos[2] << std::endl;

        pNewElem->setVol        (  objVol          );
        pNewElem->setNode       (&*actNode         );

        pNewElem->setFunctor    (  func            );
        pNewElem->setState      (  pState          );
        pNewElem->setLightState (  _uiLightState   );

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        pNewElem->setMatrixStore(  _modelViewMatrix);
#else
        // Now that we have accumulated all transformations we can convert back
        // to a floating point matrix.
        Matrix4f tempMat;
        tempMat.convertFrom(_modelViewMatrix.second);
        std::pair<UInt32, Matrix> temp_ms(_modelViewMatrix.first, tempMat);

        pNewElem->setMatrixStore(temp_ms      );
#endif

        // Normalize scalar to 0..1 for bucket sorting
        pNewElem->setScalar     ( (-objPos[2] - getNear()) /
                                  (getFar()   - getNear()) );

        if(_sStateOverrides.top()->empty() == false &&
            bIgnoreOverrides               == false  )
        {
            pNewElem->setStateOverride(_sStateOverrides.top());
        }
        mapIt->second->add(_oDrawEnv.getAction(),
                            this,
                            pNewElem,
                            NULL,
                            NULL,
                            0);
    }
    else
    {
        BuildKeyMapIt mapIt = _mMatRoots.lower_bound(iSortKey);

        if(mapIt == _mMatRoots.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create<StateSortTreeBuilder>();

            pBuilder->setNodePool(_pNodePool);

            mapIt = _mMatRoots.insert(
                mapIt, BuildKeyMap::value_type(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second = 
                _pTreeBuilderPool->create<StateSortTreeBuilder>();

            mapIt->second->setNodePool(_pNodePool);
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                           this,
                           drawFunc,
                           pState,
                           pStateOverride);


#if 0
        RenderTreeNode *pNewElem  = _pNodePool->create<RenderTreeNode>();
        StateOverride  *pOverride = NULL;

        pNewElem->setNode       (&*actNode         );
        pNewElem->setFunctor    (  func            );

#ifndef OSG_ENABLE_DOUBLE_MATRIX_STACK
        pNewElem->setMatrixStore(  _modelViewMatrix);
#else
        // Now that we have accumulated all transformations we can convert back
        // to a floating point matrix.
        Matrix4f tempMat;
        tempMat.convertFrom(_modelViewMatrix.second);
        std::pair<UInt32, Matrix> temp_ms(_modelViewMatrix.first, tempMat);

        pNewElem->setMatrixStore(  temp_ms    );
#endif

        pNewElem->setLightState (_uiLightState);

        if(_sStateOverrides.top()->empty() == false &&
            bIgnoreOverrides               == false  )
        {
            pOverride = _sStateOverrides.top();
        }

        mapIt->second->add(_oDrawEnv.getAction(),
                            this,
                            pNewElem,
                            pState,
                            pOverride,
                           _uiKeyGen );
#endif
    }

#ifdef OSG_NEW_SHADER
    if(bOverrodeState == true)
    {
        this->popState();
    }
#endif
}
#endif
// ==============================================

void RenderPartition::pushState(void)
{
    StateOverride *pNewState = _pStatePool->create();

    pNewState->fillFrom(_sStateOverrides.top());

    _sStateOverrides.push(pNewState);

//    fprintf(stderr, "push so size %d\n", _sStateOverrides.size());
}

void RenderPartition::popState(void)
{
    _sStateOverrides.pop();

//    fprintf(stderr, "pop so size %d\n", _sStateOverrides.size());
}

void RenderPartition::addOverride(UInt32 uiSlot, StateChunk *pChunk)
{
    _sStateOverrides.top()->addOverride(uiSlot, pChunk);
}

void RenderPartition::overrideMaterial(Material *       pMaterial,
                                       Node     * const pNode    )
{
    if(_pMaterialNode == NULL)
    {
        _pMaterial     = pMaterial;
        _pMaterialNode = pNode;

#ifdef OSG_NEW_SHADER_DISABLE
        State *pState = _pMaterial->getState();

        OSG_ASSERT(pState != NULL);

        ShaderProgramChunk *pSPChunk =
            static_cast<ShaderProgramChunk *>(
                pState->getChunk(ShaderProgramChunk::getStaticClassId()));

        if(pSPChunk != NULL)
        {
            this->pushState();

            _sStateOverrides.top()->addOverride(0, pSPChunk);

            _sStateOverrides.top()->setShader(NULL);

            _addedStateOverride = true;
        }

        ShaderProgramVariableChunk *pSPVChunk =
            static_cast<ShaderProgramVariableChunk *>(
                pState->getChunk(
                    ShaderProgramVariableChunk::getStaticClassId()));

        if(pSPChunk != NULL)
        {
            if(_addedStateOverride == false)
            {
                this->pushState();

                _addedStateOverride = true;
            }

            _sStateOverrides.top()->addOverride(0, pSPVChunk);

            _sStateOverrides.top()->setShaderVar(NULL);
        }
#endif
    }
    else if(_pMaterialNode == pNode)
    {
        if(pMaterial == NULL)
        {
            _pMaterial     = NULL;
            _pMaterialNode = NULL;

#ifdef OSG_NEW_SHADER_DISABLE
            if(_addedStateOverride == true)
            {
                this->popState();

                _addedStateOverride = false;
            }
#endif
        }
        else
        {
            fprintf(stderr, "strange reset with non null mat\n");
        }
    }
}

Int32 RenderPartition::allocateLightIndex(void)
{
    Int32 returnValue = _iNextLightIndex++;

    if(_iNextLightIndex > 7)
    {
        return -_iNextLightIndex;
    }
    else
    {
        _uiLightState |= 1 << returnValue;

        return returnValue;
    }
}

void RenderPartition::releaseLightIndex(void)
{
    --_iNextLightIndex;

    _uiLightState &= ~(1 << _iNextLightIndex);
}

// test a single node
bool RenderPartition::isVisible(Node *pNode)
{
    if(getFrustumCulling() == false)
        return true;

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(statCullTestedNodes)->inc();
    }

//    _oDrawEnv.getRTAction()->getStatistics()->getElem(statCullTestedNodes)->inc();

    if(pNode->getVolume().isInfinite() == true)
        return true;

    BoxVolume vol;

    pNode->updateVolume();

    vol = pNode->getVolume();

    vol.transform(topMatrix());

    if(_oFrustum.intersect(vol))
    {
// fprintf(stderr,"%p: node 0x%p vis\n", Thread::getCurrent(), node);
        return true;
    }

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(statCulledNodes)->inc();
    }

//    _oDrawEnv.getRTAction()->getStatistics()->getElem(statCulledNodes)->inc();

// fprintf(stderr,"%p: node 0x%p invis\n", Thread::getCurrent(), node);
// _frustum.dump();

    return false;
}

// visibility levels
bool RenderPartition::pushVisibility(Node * const pNode)
{
    if(getFrustumCulling() == false)
        return true;

    FrustumVolume::PlaneSet inplanes = _visibilityStack.back();

    if(inplanes == FrustumVolume::P_ALL)
    {
        _visibilityStack.push_back(inplanes);

        return true;
    }

    Color3f col;
    bool result = true;

    FrustumVolume frustum = _oFrustum;
    BoxVolume     vol     = pNode->getVolume();

    // don't mess with infinite volumes
    if(vol.isInfinite() == false)
    {
        pNode->updateVolume();

        vol = pNode->getVolume();

#if 1
        vol.transform(topMatrix());
#else
    // not quite working
        Matrix m = topMatrix();
        m.invert();

        frustum.transform(m);
#endif
    }

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(statCullTestedNodes)->inc();
    }

    if(intersect(frustum, vol, inplanes) == false)
    {
         result = false;

         col.setValuesRGB(1,0,0);

         if(_oDrawEnv.getStatCollector() != NULL)
         {
             _oDrawEnv.getStatCollector()->getElem(statCulledNodes)->inc();
         }
    }
    else
    {
        if(inplanes == FrustumVolume::P_ALL)
        {
            col.setValuesRGB(0,1,0);
        }
        else
        {
            col.setValuesRGB(0,0,1);
        }
    }

    if(getVolumeDrawing())
    {
        dropVolume(this, pNode, col);
    }

    _visibilityStack.push_back(inplanes);

    return result;
}

void RenderPartition::popVisibility(void)
{
    if(getFrustumCulling() == false)
        return;

    _visibilityStack.pop_back();
}

void RenderPartition::init(void)
{
    _sStateOverrides.push(_pStatePool->create());

    _sStateOverrides.top()->setKeyGen(_uiKeyGen);

    _visibilityStack.push_back(FrustumVolume::P_NONE);
}

void RenderPartition::initFrom(RenderPartition *pSource,
                               RenderPartition *pInitial,
                               Int32            uiCopyOnPush)
{
    if(uiCopyOnPush == 0x0000 || pSource == NULL)
    {
        _sStateOverrides.push(_pStatePool->create());

        _sStateOverrides.top()->setKeyGen(_uiKeyGen);

        _visibilityStack.push_back(FrustumVolume::P_NONE);

#ifdef OSG_RENPART_DUMP_PAR
        fprintf(stderr, "after init early %d %p (%p|%p)\n",
                _sStateOverrides.size(),
                this,
                pSource,
                pInitial);
        fflush(stderr);
#endif

        return;
    }

    _sStateOverrides.push(_pStatePool->create());

    _sStateOverrides.top()->setKeyGen(_uiKeyGen);

    if(0x0000 != (uiCopyOnPush & CopyStateOverride))
    {
        _sStateOverrides.top()->fillFrom(pSource->_sStateOverrides.top());
    }

    if(0x0000 != (uiCopyOnPush & CopyVisibility))
    {
        _visibilityStack.push_back(pSource->_visibilityStack.back());
    }
    else
    {
        _visibilityStack.push_back(FrustumVolume::P_NONE);
    }

    if(0x0000 != (uiCopyOnPush & CopyViewing))
    {
        this->setupViewing(pSource->getViewing());
    }

    if(0x0000 != (uiCopyOnPush & CopyMatrix))
    {
        this->pushMatrix(pSource->getModelMatrix());
    }

    if(0x0000 != (uiCopyOnPush & CopyProjection))
    {
        this->setupProjection(pSource->getProjection     (),
                              pSource->getProjectionTrans() );
    }

    if(0x0000 != (uiCopyOnPush & CopyTarget))
    {
        this->setRenderTarget(pSource->getRenderTarget());
    }

    if(0x0000 != (uiCopyOnPush & CopyWindow))
    {
        this->setWindow  (pSource->getWindow());
    }

    if(0x0000 != (uiCopyOnPush & CopyViewportSize))
    {
        this->setViewportDimension(pSource->_oDrawEnv.getPixelLeft  (),
                                   pSource->_oDrawEnv.getPixelBottom(),
                                   pSource->_oDrawEnv.getPixelRight (),
                                   pSource->_oDrawEnv.getPixelTop   (),
                                   pSource->_oDrawEnv.getFull       ());

    }

    if(0x0000 != (uiCopyOnPush & CopyFrustum))
    {
        this->_oFrustum = pSource->_oFrustum;
    }

    if(0x0000 != (uiCopyOnPush & CopyNearFar))
    {
        this->setNear(pSource->getNear());
        this->setFar (pSource->getFar ());
    }

    if(0x0000 != (uiCopyOnPush & CopyVPCamera) && pInitial != NULL)
    {
        _oDrawEnv.setVPCameraMatrices(
            pInitial->_oDrawEnv.getVPCameraFullProjection (),
            pInitial->_oDrawEnv.getVPCameraProjection     (),
            pInitial->_oDrawEnv.getVPCameraProjectionTrans(),
            pInitial->_oDrawEnv.getVPCameraViewing        (),
            pInitial->_oDrawEnv.getVPCameraToWorld        (),
            pInitial->_oDrawEnv.getVPWorldToScreen        ());
    }

#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "after init %d %p (%p|%p)\n",
            _sStateOverrides.size(),
            this,
            pSource,
            pInitial);

    fflush(stderr);
#endif
}

void RenderPartition::initVPMatricesFromCamera(void)
{
    _oDrawEnv.initVPMatricesFromCamera();
}

void RenderPartition::setVPCameraMatrices(const Matrixr &mFullprojection,
                                          const Matrixr &mProjection,
                                          const Matrixr &mProjectionTrans,
                                          const Matrixr &mViewing,
                                          const Matrixr &mToWorld,
                                          const Matrixr &mWorldToScreen  )
{
    _oDrawEnv.setVPCameraMatrices(mFullprojection,
                                  mProjection,
                                  mProjectionTrans,
                                  mViewing,
                                  mToWorld,
                                  mWorldToScreen   );
}

void RenderPartition::exit(void)
{
    if(_bDone == true)
        return;

#ifdef OSG_RENPART_DUMP_PAR
    fprintf(stderr, "exit %p %d %d\n",
            this, _sStateOverrides.size(), pthread_self());
    fflush(stderr);
#endif

    _sStateOverrides.pop();

    _oDrawEnv.deactivateState();

    _bDone = true;
}


void RenderPartition::updateModelMatrix(void) const
{
    if(_modelMatrixValid == false)
    {
        _modelMatrixValid = true;
        _modelMatrix      = _oDrawEnv.getCameraToWorld();
        _modelMatrix.mult(_modelViewMatrix.second);
    }
}

void RenderPartition::popMatrix(void         )
{
    _modelViewMatrix.first  = _modelViewMatrixStack.back().first;
    _modelViewMatrix.second = _modelViewMatrixStack.back().second;
    _modelViewMatrixStack.pop_back();

    _modelMatrixValid       = false;
}

const Matrix &RenderPartition::topMatrix(void)
{
    return getModelMatrix();
}



/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */
