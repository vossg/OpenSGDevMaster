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

#include "OSGRenderAction.h"

#include "OSGRenderPartitionPool.h"
#include "OSGRenderTreeNodePool.h"
#include "OSGStateOverride.h"
#include "OSGStateSorter.h"

#include "OSGWindow.h"

#include "OSGTextureBaseChunk.h"
#include "OSGMaterialChunk.h"

#include "OSGVolumeDraw.h"
#include "OSGTreeBuilderBase.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/



/*! \brief the prototype which is copied to create new actions
 */

RenderAction *RenderAction::_pPrototype = NULL;

/*! \brief Default functors for instantiation
 */

std::vector<
    Action::Functor> *RenderAction::_vDefaultEnterFunctors = NULL;
std::vector<
    Action::Functor> *RenderAction::_vDefaultLeaveFunctors = NULL;


StatElemDesc<StatTimeElem> RenderAction::statDrawTime     (
    "RT-DrawTime",
    "time for draw tree traversal");

StatElemDesc<StatIntElem > RenderAction::statNStates      (
    "RT-States",
    "number of material changes");
StatElemDesc<StatIntElem > RenderAction::statNMatrices    (
    "RT-NMatrices",
    "number of matrix changes");
StatElemDesc<StatIntElem > RenderAction::statNGeometries  (
    "RT-NGeometries",
    "number of Geometry nodes");
StatElemDesc<StatIntElem > RenderAction::statNShaders     (
    "RT-Shaders",
    "number of shader changes");
StatElemDesc<StatIntElem > RenderAction::statNShaderParams(
    "RT-ShaderParams",
    "number of shader params changes");
StatElemDesc<StatIntElem > RenderAction::statNTriangles   (
    "RT-Triangles",
    "number of triangles");

/*
StatElemDesc<StatIntElem > RenderAction::statNTransGeometries(
    "shNTransGeometries",
    "number of transformed Geometry nodes");
 */

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

bool RenderAction::terminateEnter(void)
{
    FDEBUG_GV(("Terminate RenderAction Enter\n"));

    delete _vDefaultEnterFunctors;

    _vDefaultEnterFunctors = NULL;

    return true;
}

bool RenderAction::terminateLeave(void)
{
    FDEBUG_GV(("Terminate RenderAction Leave\n"));

    delete _vDefaultLeaveFunctors;

    _vDefaultLeaveFunctors = NULL;

    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! \brief Default registration. static, so it can be called during static init
 */

void RenderAction::registerEnterDefault(
    const FieldContainerType &type,
    const Action::Functor    &func)
{
    if(_vDefaultEnterFunctors == NULL)
    {
        _vDefaultEnterFunctors = new std::vector<Action::Functor>;

        addPostFactoryExitFunction(&RenderAction::terminateEnter);
    }

    while(type.getId() >= _vDefaultEnterFunctors->size())
    {
        _vDefaultEnterFunctors->push_back(&Action::_defaultEnterFunction);
    }

    FDEBUG_GV(("Register rendertrav for %s\n", type.getCName()));

    (*_vDefaultEnterFunctors)[type.getId()] = func;
}

void RenderAction::registerLeaveDefault(
    const FieldContainerType &type,
    const Action::Functor    &func)
{
    if(_vDefaultLeaveFunctors == NULL)
    {
        _vDefaultLeaveFunctors = new std::vector<Action::Functor>;

        addPostFactoryExitFunction(&RenderAction::terminateLeave);
    }

    while(type.getId() >= _vDefaultLeaveFunctors->size())
    {
        _vDefaultLeaveFunctors->push_back(&Action::_defaultLeaveFunction);
    }

    FDEBUG_GV(("Register rendertrav leave for %s\n", type.getCName()));

    (*_vDefaultLeaveFunctors)[type.getId()] = func;
}


/*! \brief  prototype access
 *  after setting the prototype all new DrawActions are clones of it
 */

void RenderAction::setPrototype(
    RenderAction *pPrototype)
{
    _pPrototype = pPrototype;
}

RenderAction *RenderAction::getPrototype(void)
{
    return _pPrototype;
}

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

/*------------- constructors & destructors --------------------------------*/

RenderAction::RenderAction(void) :
     Inherited               (          ),
    _doCullOnly              (     false),
    _numBuffers              (         0),
    _currentBuffer           (         0),

    _uiKeyGen                (         0),

    _pPartitionPools         (          ),
    _pNodePools              (          ),
    _pStatePools             (          ),
    _pTreeBuilderPools       (          ),
    _vRenderPartitions       (          ),

    _iActivePartitionIdx     (-1        ),
    _bInPartitionGroup       (false     ),
    _pActivePartition        (NULL      ),

    _sRenderPartitionStack   (          ),
    _sRenderPartitionIdxStack(          ),
    _sRenderPartitionGrpStack(          ),

    _bvPassMask              (          ),
    _bUseGLFinish            (false     ),

    _occlusionCulling        (false     ),
    _occlusionCullingDebug   (false     ),
    _occDMTested             (0xffffffff), 
    _occDMCulled             (0xffffffff), 
    _occDMVisible            (0xffffffff),
    _occMinFeatureSize       (         0),
    _occVisibilityThreshold  (         0),
    _occCoveredThreshold     (      0.7f),
    _occQueryBufferSize      (      1000),
    _occMinimumTriangleCount (       500),

    _scrlodCoverageThreshold (      0.01),
    _scrlodNumLODsToUse      (         0),
    _scrlodDegradationFactor (       1.0)
{
    if(_vDefaultEnterFunctors != NULL)
        _enterFunctors = *_vDefaultEnterFunctors;

    if(_vDefaultLeaveFunctors != NULL)
        _leaveFunctors = *_vDefaultLeaveFunctors;

    setNumBuffers(1);


    FieldContainerType *pSHLType  = 
        FieldContainerFactory::the()->findType("SHLChunk");

    StateChunkPtr       pSHLProto = NullFC;

    if(pSHLType != NullFC)
    {
        pSHLProto = dynamic_cast<StateChunkPtr>(pSHLType->getPrototype());
    }

    

    UInt32 uiSId = 0x0;//SHLChunk        ::getStaticClassId() & 0x000003FF;
    UInt32 uiTId = TextureBaseChunk::getStaticClassId() & 0x000003FF;
    UInt32 uiMId = MaterialChunk   ::getStaticClassId() & 0x000003FF;

    if(pSHLProto != NullFC)
    {
        uiSId = pSHLProto->getClassId();
    }

//    _uiKeyGen = (uiTId | (uiMId << 10) | (State::Key1Mask << 20));

    _uiKeyGen = (uiSId) | (uiTId << 10) | (uiMId << 20);

/*
    fprintf(stderr, "CreateKeyGen (RT) (%p) from %d %d %d -> %08x\n",
            this,
            SHLChunk     ::getStaticClassId(),
            TextureChunk ::getStaticClassId(),
            MaterialChunk::getStaticClassId(),
            _uiKeyGen);
 */

}

RenderAction::RenderAction(
    const RenderAction &source) :

     Inherited               (source                         ),
    _doCullOnly              (false                          ),
    _numBuffers              (0                              ),
    _currentBuffer           (0                              ),
    _uiKeyGen                (source._uiKeyGen               ),
    _pPartitionPools         (                               ),
    _pNodePools              (                               ),
    _pStatePools             (                               ),
    _pTreeBuilderPools       (                               ),

    _pActivePartition        (NULL                           ),
    _iActivePartitionIdx     (-1                             ),

    _vRenderPartitions       (                               ),
    _sRenderPartitionStack   (                               ),
    _sRenderPartitionIdxStack(                               ),

    _bvPassMask              (source._bvPassMask             ),
    _bUseGLFinish            (source._bUseGLFinish           ),

    _occlusionCulling        (source._occlusionCulling       ),
    _occlusionCullingDebug   (source._occlusionCullingDebug  ),
    _occDMTested             (source._occDMTested            ), 
    _occDMCulled             (source._occDMCulled            ), 
    _occDMVisible            (source._occDMVisible           ),
    _occMinFeatureSize       (source._occMinFeatureSize      ),
    _occVisibilityThreshold  (source._occVisibilityThreshold ),
    _occCoveredThreshold     (source._occCoveredThreshold    ),
    _occQueryBufferSize      (source._occQueryBufferSize     ),
    _occMinimumTriangleCount (source._occMinimumTriangleCount),
    _scrlodCoverageThreshold (source._scrlodCoverageThreshold),
    _scrlodNumLODsToUse      (source._scrlodNumLODsToUse     ),
    _scrlodDegradationFactor (source._scrlodDegradationFactor)
{
    setNumBuffers(source._numBuffers);
}

RenderAction *RenderAction::create(void)
{
    RenderAction *returnValue;

    if(_pPrototype)
    {
        returnValue = new RenderAction(*_pPrototype);
    }
    else
    {
        returnValue = new RenderAction();
    }

    return returnValue;
}


RenderAction::~RenderAction(void)
{
    for(UInt16 i = 0; i < _numBuffers; ++i)
    {
        delete _pPartitionPools[i];
        delete _pNodePools[i];
        delete _pStatePools[i];
        delete _pTreeBuilderPools[i];
    }
}

/*------------------------------ access -----------------------------------*/

/*------------------------ multi-buffer stuff -----------------------------*/

void RenderAction::setDoCullOnly(bool val)
{
    _doCullOnly = val;
}

bool RenderAction::getDoCullOnly(void)
{
    return _doCullOnly;
}

void RenderAction::setNumBuffers(UInt32 n)
{
    if(n < 1)
    {
        FWARNING(("RenderAction::setNumBuffers: need at least one "
                  "buffer!\n"));
        n = 1;
    }

    if(n > _numBuffers)
    {
        for(UInt16 i = _numBuffers; i < n; ++i)
        {
            _pPartitionPools  .push_back(new RenderPartitionPool);
            _pNodePools       .push_back(new RenderTreeNodePool);
            _pStatePools      .push_back(new StateOverridePool);
            _pTreeBuilderPools.push_back(new TreeBuilderPool);
        }

    }
    else if(n < _numBuffers)
    {
        for(UInt16 i = _numBuffers - 1; i >= n; --i)
        {
            delete _pPartitionPools[i];
            delete _pNodePools[i];
            delete _pStatePools[i];
            delete _pTreeBuilderPools[i];
        }
        _pPartitionPools  .resize(n);
        _pNodePools       .resize(n);
        _pStatePools      .resize(n);
        _pTreeBuilderPools.resize(n);
    }
    _numBuffers = n;
    _vRenderPartitions.resize(n);
}

UInt32 RenderAction::getNumBuffers(void)
{
    return _numBuffers;
}

void  RenderAction::setCurrentBuffer(UInt32 b)
{
    _currentBuffer = b;
}

UInt32 RenderAction::getCurrentBuffer(void)
{
    return _currentBuffer;
}


/*-------------------------- your_category---------------------------------*/

ActionBase::ResultE RenderAction::recurceNoNodeCallbacks(
    NodePtrConstArg node)
{
    if(node == NullFC)
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0)
        return Continue;

    NodeCorePtr core = node->getCore();

    if(core == NullFC)
    {
        SWARNING << "recurse: core is Null,  don't know what to do!"
                 << std::endl;
        return Quit;
    }

    Action::ResultE result;

    _actList = NULL;
    _actNode = node;


    if(! _newList.empty())
    {
        result = callNewList();
    }
    else if(! _useNewList) // new list is empty, but not used?
    {
        MFNodePtr::const_iterator it;

        for(  it  = node->getMFChildren()->begin();
              it != node->getMFChildren()->end();
            ++it)
        {
            result = recurse(*it);

            if(result != Continue)
                break;
        }
    }

    _actNode = node;

    if(result == Skip)
        return Continue;

    return result;
}

Action::ResultE RenderAction::start(void)
{
    Inherited::start();

#if 0 // Not needed done by the partition setup anyway.
    if(_pWindow != NULL && !_doCullOnly)
    {
        _pWindow->resizeGL();
    }
#endif

    _vRenderPartitions[_currentBuffer].clear   ();

    _pPartitionPools  [_currentBuffer]->freeAll();
    _pNodePools       [_currentBuffer]->freeAll();
    _pStatePools      [_currentBuffer]->freeAll();
    _pTreeBuilderPools[_currentBuffer]->freeAll();

    _pActivePartition = _pPartitionPools[_currentBuffer]->create();

    _vRenderPartitions[_currentBuffer].push_back(_pActivePartition);

    _iActivePartitionIdx = 0;

    _pActivePartition->setKeyGen         (_uiKeyGen                         );
    _pActivePartition->setAction         ( this                             );
    _pActivePartition->setNodePool       (_pNodePools       [_currentBuffer]);
    _pActivePartition->setStatePool      (_pStatePools      [_currentBuffer]);
    _pActivePartition->setTreeBuilderPool(_pTreeBuilderPools[_currentBuffer]);
    _pActivePartition->setStatCollector  (_pStatistics                      );

    _pActivePartition->setFrustum        (_oFrustum        );

    _pActivePartition->setFrustumCulling (_bFrustumCulling );
    _pActivePartition->setVolumeDrawing  (_bVolumeDrawing  );

    _pActivePartition->init();

#ifdef OSG_DEBUGX
    _pActivePartition->setDebugString("DefaultPartition");
#endif


    bool full = true;

    if(_pViewport != NULL)
    {
//        _pActivePartition->setViewport(_pViewport);
        _pActivePartition->setWindow  (_pWindow  );

        _pActivePartition->setViewportDimension(_pViewport->getPixelLeft  (),
                                                _pViewport->getPixelBottom(),
                                                _pViewport->getPixelRight (),
                                                _pViewport->getPixelTop   (),
                                                _pViewport->isFullWindow  ());

        if(_pCamera != NULL)
        {
            Matrix m, t;

            // set the projection
            _pCamera->getProjection          ( m,
                                              _pViewport->getPixelWidth (),
                                              _pViewport->getPixelHeight());

            _pCamera->getProjectionTranslation( t,
                                               _pViewport->getPixelWidth (),
                                               _pViewport->getPixelHeight());

            _pActivePartition->setupProjection(m, t);

            _pCamera->getViewing( m,
                                 _pViewport->getPixelWidth (),
                                 _pViewport->getPixelHeight());


            _pActivePartition->setupViewing(m);

            _pActivePartition->setNear(_pCamera->getNear());
            _pActivePartition->setFar (_pCamera->getFar ());
        }

        _pActivePartition->initVPMatricesFromCamera();

        _pActivePartition->setBackground(_pBackground);
    }

//    fprintf(stderr, "Start\n");

    return Action::Continue;
}

Action::ResultE RenderAction::stop(ResultE res)
{
//    fprintf(stderr, "Stop\n");

    Inherited::stop(res);

    if(!_doCullOnly)
    {
        drawBuffer(_currentBuffer);

        if(getVolumeDrawing())
            drawVolume(_oFrustum);

        if(_pStatistics != NULL)
        {
            UInt32 uiNMatrix      = 0;
            UInt32 uiNState       = 0;
            UInt32 uiNShader      = 0;
            UInt32 uiNShaderParam = 0;
            UInt32 uiNTriangles   = 0;
            
            for(Int32 i = 0; 
                      i < _vRenderPartitions[_currentBuffer].size(); 
                    ++i)
            {
                uiNMatrix +=
                    _vRenderPartitions[
                        _currentBuffer][i]->getNumMatrixChanges();
                
                uiNState  +=
                    _vRenderPartitions[
                        _currentBuffer][i]->getNumStateChanges();
                
                uiNShader +=
                    _vRenderPartitions[
                        _currentBuffer][i]->getNumShaderChanges();
                
                uiNShaderParam +=
                    _vRenderPartitions[
                        _currentBuffer][i]->getNumShaderParamChanges();
                
                uiNTriangles +=
                    _vRenderPartitions[_currentBuffer][i]->getNumTriangles();
            }


            _pStatistics->getElem(statNMatrices    )->set(uiNMatrix     );
            _pStatistics->getElem(statNStates      )->set(uiNState      );
            _pStatistics->getElem(statNShaders     )->set(uiNShader     );
            _pStatistics->getElem(statNShaderParams)->set(uiNShaderParam);
            _pStatistics->getElem(statNTriangles   )->set(uiNTriangles);
        }
    }

    return Action::Continue;
}

void RenderAction::drawBuffer(UInt32 buf)
{
    if(_pStatistics != NULL)
    {
        _pStatistics->getElem(statDrawTime)->start();
    }

    _vRenderPartitions[buf][0]->setupExecution();


    // Quick fix, have to check GV
    glPushAttrib(GL_VIEWPORT_BIT);

    for(Int32 i = _vRenderPartitions[buf].size() - 1; i > 0; --i)
    {
        _vRenderPartitions[buf][i]->execute();
//        _vRenderPartitions[buf][i]->exit();
    }

    // Quick fix, have to check GV
     glPopAttrib();

    _vRenderPartitions[buf][0]->doExecution();
//    _vRenderPartitions[buf][0]->exit();

    if(_bUseGLFinish == true)
    {
        glFinish();
    }

    if(_pStatistics != NULL)
    {
        _pStatistics->getElem(statDrawTime)->stop();
    }
}

void RenderAction::dropFunctor(Material::DrawFunctor &func,
                                        State                 *pState,
                                        UInt32                 uiSortKey)
{
    _pActivePartition->dropFunctor(func, pState, uiSortKey);
}

void RenderAction::dropFunctor(Material::DrawFunctor &func,
                                        Material              *pMat)
{
    if(pMat == NULL)
        return;

    UInt32 uiNPasses = pMat->getNPasses();
    
    for(UInt32 uiPass = 0; uiPass < uiNPasses; ++uiPass)
    {
        StatePtr st = pMat->getState(uiPass);
        
        if(st != NullFC)
        {
            this->dropFunctor(func, 
                              getCPtr(st), 
                              pMat->getSortKey() + uiPass);
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

void RenderAction::pushState(void)
{
    _pActivePartition->pushState();
}

void RenderAction::popState(void)
{
    _pActivePartition->popState();
}

void RenderAction::addOverride(UInt32 uiSlot, StateChunk *pChunk)
{
    _pActivePartition->addOverride(uiSlot, pChunk);
}

Int32 RenderAction::allocateLightIndex(void)
{
    return _pActivePartition->allocateLightIndex();
}

void  RenderAction::releaseLightIndex(void)
{
    _pActivePartition->releaseLightIndex();
}

void RenderAction::pushMatrix(const Matrix &matrix)
{
    _pActivePartition->pushMatrix(matrix);
}

void RenderAction::popMatrix(void)
{
    _pActivePartition->popMatrix();
}

const Matrix &RenderAction::topMatrix(void)
{
    return _pActivePartition->topMatrix();
}

void RenderAction::overrideMaterial(Material        *pMaterial,
                                             NodePtrConstArg  pNode    )
{
    _pActivePartition->overrideMaterial(pMaterial, pNode);
}

Material *RenderAction::getMaterial(void)
{
    return _pActivePartition->getMaterial();
}

void RenderAction::pushPartition(UInt32                uiCopyOnPush,
                                          RenderPartition::Mode eMode       )
{
    _sRenderPartitionIdxStack.push(_iActivePartitionIdx);
    _sRenderPartitionStack   .push(_pActivePartition   );
    _sRenderPartitionGrpStack.push(_bInPartitionGroup  );

    if(_bInPartitionGroup == false)
    {
        _pActivePartition    = 
            _pPartitionPools  [_currentBuffer]->create(eMode);
        _iActivePartitionIdx = _vRenderPartitions[_currentBuffer].size();
    
        _vRenderPartitions[_currentBuffer].push_back(_pActivePartition);
    }
    else
    {
/*
        RenderPartitionStore::iterator it = 
            _vRenderPartitions[_currentBuffer].begin();

        it += _iActivePartitionIdx;

        _pActivePartition    = 
            _pPartitionPools  [_currentBuffer]->create(eMode);

        _vRenderPartitions[_currentBuffer].insert(it, _pActivePartition);
 */
        _pActivePartition    = 
            _pPartitionPools  [_currentBuffer]->create(eMode);

        if(_iActivePartitionIdx == _vRenderPartitions[_currentBuffer].size())
        {
            _vRenderPartitions[_currentBuffer].push_back(_pActivePartition);
        }
        else
        {
            _vRenderPartitions[_currentBuffer]
                              [_iActivePartitionIdx]->addPartition(
                                  _pActivePartition);
        }

        _bInPartitionGroup   = false;
    }

    _pActivePartition->setKeyGen         (_uiKeyGen                         );
    _pActivePartition->setAction         ( this                             );
    _pActivePartition->setNodePool       (_pNodePools       [_currentBuffer]);
    _pActivePartition->setStatePool      (_pStatePools      [_currentBuffer]);
    _pActivePartition->setTreeBuilderPool(_pTreeBuilderPools[_currentBuffer]);
    _pActivePartition->setStatCollector  (_pStatistics                      );

    _pActivePartition->initFrom(_sRenderPartitionStack.top(),
                                _vRenderPartitions[_currentBuffer][0],
                                 uiCopyOnPush               );
}

void RenderAction::popPartition(void)
{
    _pActivePartition    = _sRenderPartitionStack   .top();
    _iActivePartitionIdx = _sRenderPartitionIdxStack.top();
    _bInPartitionGroup   = _sRenderPartitionGrpStack.top();

    _sRenderPartitionStack   .pop();
    _sRenderPartitionIdxStack.pop();
    _sRenderPartitionGrpStack.pop();
}

void RenderAction::readdPartitionByIndex(UInt32 uiPartIdx)
{
    OSG_ASSERT(uiPartIdx < _vRenderPartitions[_currentBuffer].size());

    _vRenderPartitions[_currentBuffer].push_back(
        _vRenderPartitions[_currentBuffer][uiPartIdx]);
}

void RenderAction::dumpPartitionList(void)
{
    fprintf(stderr, "Dump PartitionList \n");

    for(UInt32 i = 0; i < _vRenderPartitions[_currentBuffer].size(); ++i)
    {
        fprintf(stderr, "    %p\n", _vRenderPartitions[_currentBuffer][i]);
    }
}

RenderPartition *RenderAction::getActivePartition(void)
{
    return _pActivePartition;
}

bool RenderAction::isVisible(Node *node)
{
    return _pActivePartition->isVisible(node);
}

bool RenderAction::pushVisibility(void)
{
    if(_pActivePartition->pushVisibility(getActNode()) == false)
    {
        useNodeList(); // ignore all children
        return false;
    }

    return true;
}

void RenderAction::popVisibility(void)
{
    _pActivePartition->popVisibility();
}

// control activation of frustum culling
bool RenderAction::getFrustumCulling(void) const
{
    if(_pActivePartition != NULL)
        return _pActivePartition->getFrustumCulling();
    else
        return Inherited::getFrustumCulling();
}

void RenderAction::setFrustumCulling(bool val)
{
    if(_pActivePartition != NULL)
        _pActivePartition->setFrustumCulling(val);
    else
        Inherited::setFrustumCulling(val);

}

// control frustum
const FrustumVolume &RenderAction::getFrustum(void) const
{
    if(_pActivePartition != NULL)
        return _pActivePartition->getFrustum();
    else
        return Inherited::getFrustum();
}

void RenderAction::setFrustum(FrustumVolume &frust)
{
    if(_pActivePartition != NULL)
        _pActivePartition->setFrustum(frust);
    else
        Inherited::setFrustum(frust);
}


/*------------------------ Occlusion Culling -----------------------------*/

void RenderAction::setOcclusionCulling(const bool val)
{
    _occlusionCulling = val;
}

bool RenderAction::getOcclusionCulling(void)
{
    return _occlusionCulling;
}

void RenderAction::setOcclusionCullingDebug(const bool val)
{
    _occlusionCullingDebug = val;
}

bool RenderAction::getOcclusionCullingDebug(void)
{
    return _occlusionCullingDebug;
}

void RenderAction::setOcclusionDebugMasks(const UInt32 tested, const UInt32 culled, const UInt32 visible)
{
    _occDMTested  = tested;
    _occDMCulled  = culled;
    _occDMVisible = visible;
}

UInt32 RenderAction::getOcclusionTestedDebugMask(void)
{
    return _occDMTested;
}

UInt32 RenderAction::getOcclusionCulledDebugMask(void)
{
    return _occDMCulled;
}

UInt32 RenderAction::getOcclusionVisibleDebugMask(void)
{
    return _occDMVisible;
}

void RenderAction::setOcclusionCullingMinimumFeatureSize(const UInt32 pixels)
{
    _occMinFeatureSize = pixels;
}

UInt32 RenderAction::getOcclusionCullingMinimumFeatureSize(void)
{
    return _occMinFeatureSize;
}

void RenderAction::setOcclusionCullingVisibilityThreshold(const UInt32 pixels)
{
    _occVisibilityThreshold = pixels;
}

UInt32 RenderAction::getOcclusionCullingVisibilityThreshold(void)
{
    return _occVisibilityThreshold;
}

void RenderAction::setOcclusionCullingCoveredThreshold(const Real32 percent)
{
    _occCoveredThreshold = percent;
}

Real32 RenderAction::getOcclusionCullingCoveredThreshold(void)
{
    return _occCoveredThreshold;
}

void RenderAction::setOcclusionCullingQueryBufferSize(const UInt32 size)
{
    _occQueryBufferSize = size;
}

UInt32 RenderAction::getOcclusionCullingQueryBufferSize(void)
{
    return _occQueryBufferSize;
}

void RenderAction::setOcclusionCullingMinimumTriangleCount(const UInt32 count)
{
    _occMinimumTriangleCount = count;
}

UInt32 RenderAction::getOcclusionCullingMinimumTriangleCount(void)
{
    return _occMinimumTriangleCount;
}

void RenderAction::setScreenLODCoverageThreshold(const Real32 percent)
{
    _scrlodCoverageThreshold = percent;
}

Real32 RenderAction::getScreenLODCoverageThreshold(void)
{
    return _scrlodCoverageThreshold;
}

void RenderAction::setScreenLODNumLevels(const UInt32 levels)
{
    _scrlodNumLODsToUse = levels;
}

UInt32 RenderAction::getScreenLODNumLevels(void)
{
    return _scrlodNumLODsToUse;
}

void RenderAction::setScreenLODDegradationFactor(const Real32 percent)
{
    _scrlodDegradationFactor = percent;
}

Real32 RenderAction::getScreenLODDegradationFactor(void)
{
    return _scrlodDegradationFactor;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


std::vector<Action::Functor> *
    RenderAction::getDefaultEnterFunctors(void)
{
    return _vDefaultEnterFunctors;
}

std::vector<Action::Functor> *
    RenderAction::getDefaultLeaveFunctors(void)
{
    return _vDefaultLeaveFunctors;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

