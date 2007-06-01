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

#ifdef OSG_CLEANED_RENDERACTION

#include "OSGRenderPartition.h"
#include "OSGRenderTreeNodePool.h"
#include "OSGRenderTraversalAction.h"
#include "OSGStateOverridePool.h"
#include "OSGTreeBuilderBase.h"
#include "OSGBackground.h"
#include "OSGFrameBufferObject.h"
#include "OSGVolumeDraw.h"

#include "OSGCamera.h"
#include "OSGFrameBufferAttachment.h"

#include "OSGStateSortTreeBuilder.h"
#include "OSGScalarSortTreeBuilder.h"
#include "OSGOcclusionCullingTreeBuilder.h"

#include "OSGGeoStatsAttachment.h"

#ifdef OSG_DEBUG
#define OSG_TRACE_PARTITIONN
#endif

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

void RenderPartition::setAction(RenderTraversalAction *pAction)
{
    _oDrawEnv.setAction(pAction);
}


/*------------- constructors & destructors --------------------------------*/

RenderPartition::RenderPartition(Mode eMode) :
     Inherited               (         ),
    _eMode                   (eMode    ),
    _eSetupMode              (FullSetup),
    _bDone                   (false    ),
    _vGroupStore             (         ),

    _oDrawEnv                (         ),
    _oSimpleDrawCallback     (     NULL),
    _pBackground             (     NULL),

    _uiMatrixId              (        0),
    _currMatrix              (         ),
    _accMatrix               (         ),
    _vMatrixStack            (         ),
    
    _pNodePool               (     NULL),
    
    _mMatRoots               (         ),
    _mTransMatRoots          (         ),
    
    _bSortTrans              (    true ),
    _bZWriteTrans            (    false),
    _bCorrectTwoSidedLighting(    false),

    _uiActiveMatrix          (        0),

    _pStatePool              (     NULL),   
    _sStateOverrides         (         ),

    _pTreeBuilderPool        (     NULL),
 
    _iNextLightIndex         (        0),
    _uiKeyGen                (        0),

    _pMaterial               (     NULL),
    _pMaterialNode           (   NullFC),

    _pRenderTarget           (     NULL),
    _iPixelLeft              (        0),
    _iPixelRight             (        1),
    _iPixelBottom            (        0),
    _iPixelTop               (        1),
    _bFull                   (     true),
 
    _uiNumMatrixChanges      (        0),
    _uiNumTriangles          (        0),

    _visibilityStack         (         ),
    _bFrustumCulling         (    true ),
    _bVolumeDrawing          (    false),
    _bAutoFrustum            (    true ),
    _oFrustum                (         )
#ifdef OSG_DEBUG
   ,_szDebugString           (         )
#endif
{
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

    _eSetupMode = FullSetup;

    _bDone      = false;

    _vGroupStore.clear();

    if(_eMode == StateSorting || _eMode == TransformSorting)
    {
        _pBackground = NULL;
        
        _uiMatrixId = 1;
        
        _currMatrix.first = 1;
        _currMatrix.second.setIdentity();
        
        _vMatrixStack.clear();
        
        
        std::for_each(_mMatRoots     .begin(), 
                      _mMatRoots     .end(), ResetSecond());
        std::for_each(_mTransMatRoots.begin(), 
                      _mTransMatRoots.end(), ResetSecond());
        
        
        _bSortTrans               = true;
        _bZWriteTrans             = false;
        _bCorrectTwoSidedLighting = false;
        
        _uiActiveMatrix           = 0;
        
        _oDrawEnv.clearState();
        
        while(_sStateOverrides.empty() == false)
        {
            _sStateOverrides.pop();
        }
        
        
        _iNextLightIndex = 0;
        
        
        _pMaterial        = NULL;
        _pMaterialNode    = NullFC;
        
        
        _pRenderTarget    = NULL;
        
        _iPixelLeft       = 0;
        _iPixelRight      = 1;
        _iPixelBottom     = 0;
        _iPixelTop        = 1;
        
        
        _visibilityStack.clear();
        
        
        _bFrustumCulling = true;
        _bVolumeDrawing  = false;
        _bAutoFrustum    = true;
    }
    else
    {
        _pBackground      = NULL;

        _pRenderTarget    = NULL;

        _iPixelLeft       = 0;
        _iPixelRight      = 1;
        _iPixelBottom     = 0;
        _iPixelTop        = 1;

        _oDrawEnv.clearState();
        
        while(_sStateOverrides.empty() == false)
        {
            _sStateOverrides.pop();
        }

        _oSimpleDrawCallback = NULL;
    }

    _uiNumTriangles = 0;
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
    if(rLeft > 1.f)
        _iPixelLeft = Int32(rLeft);
    else
        _iPixelLeft = Int32(iTargetWidth * rLeft);

    if(rRight > 1.f)
        _iPixelRight = Int32(rRight);
    else
        _iPixelRight = Int32(iTargetWidth * rRight) - 1;


    if(rBottom > 1.f)
        _iPixelBottom = Int32(rBottom);
    else
        _iPixelBottom = Int32(iTargetHeight * rBottom);

    if(rTop > 1.f)
        _iPixelTop = Int32(rTop);
    else
        _iPixelTop = Int32(iTargetHeight * rTop) - 1;


    _bFull = ( (_iPixelLeft   == 0                ) &&
               (_iPixelRight  == iTargetWidth  - 1) &&
               (_iPixelBottom == 0                ) &&
               (_iPixelTop    == iTargetHeight - 1)  );
}

void RenderPartition::setupExecution(void)
{
    if(_bDone == true)
        return;

#ifdef OSG_TRACE_PARTITION
    if(_szDebugString.size() != 0)
    {
        fprintf(stderr, 
                "RenderPartition::setupExecution %s\n", 
                _szDebugString.c_str());
    }
#endif

    if(_pRenderTarget != NULL)
        _pRenderTarget->activate(&_oDrawEnv);

    if(0x0000 != (_eSetupMode & ViewportSetup))
    {
        Int32 pw  = _iPixelRight - _iPixelLeft + 1;
        Int32 ph  = _iPixelTop   - _iPixelBottom + 1;
        
        glViewport(_iPixelLeft, _iPixelBottom, pw, ph);
        
        if(_bFull == false)
        {
            glScissor (_iPixelLeft, _iPixelBottom, pw, ph);
            glEnable(GL_SCISSOR_TEST);
        }
    }

    if(0x0000 != (_eSetupMode & ProjectionSetup))
    {
        glMatrixMode (GL_PROJECTION);
        glPushMatrix();

        glLoadMatrixf(_oDrawEnv.getCameraFullProjection().getValues());

        glMatrixMode(GL_MODELVIEW);
    }
    
    if(0x0000 != (_eSetupMode & BackgroundSetup))
    {
        if(_pBackground != NULL)
        {
            _pBackground->clear(&_oDrawEnv, _oDrawEnv.getViewport());
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
        BuildKeyMapIt      mapIt  = _mMatRoots.begin();
        BuildKeyMapConstIt mapEnd = _mMatRoots.end  ();
        
        _uiNumMatrixChanges = 0;
 
        while(mapIt != mapEnd)
        {
            if(mapIt->second != NULL)
            {
                mapIt->second->draw(_oDrawEnv, this);
            }
            
            ++mapIt;
        }    
        
        mapIt  = _mTransMatRoots.begin();
        mapEnd = _mTransMatRoots.end  ();
        
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
        
        if(_bFull == false)
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }

    if(0x0000 != (_eSetupMode & ProjectionSetup))
    {
        glMatrixMode (GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    if(_pRenderTarget != NULL)
        _pRenderTarget->deactivate(&_oDrawEnv);
}


void RenderPartition::execute(void)
{
    if(_bDone == true)
        return;

    setupExecution();
    doExecution   ();  

    GroupStore::iterator gIt  = _vGroupStore.begin();
    GroupStore::iterator gEnd = _vGroupStore.end  ();

    while(gIt != gEnd)
    {
        (*gIt)->execute();
        (*gIt)->exit   ();

        ++gIt;
    }
}

/*---------------------------- properties ---------------------------------*/

void RenderPartition::dropFunctor(DrawFunctor &func, 
                                  State       *pState,
                                  Int32        iSortKey)
{
    if(_eMode == SimpleCallback)
        return;
        
    RenderTraversalAction *rt = 
        dynamic_cast<RenderTraversalAction *>(_oDrawEnv.getRTAction());

    NodePtr actNode = rt->getActNode();
    
    // Add Stats
    GeoStatsAttachmentPtr st;
    st = GeoStatsAttachment::get(actNode);
    if(st == NullFC)
    {
        GeoStatsAttachment::addTo(actNode);
        
        st = GeoStatsAttachment::get(actNode);
    }

    st->validate();

    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(
            RenderTraversalAction::statNTriangles)->add(st->getTriangles());
    }

    _uiNumTriangles += st->getTriangles();

    
    
    if(_bSortTrans == true && pState->isTransparent() == true)
    {
        BuildKeyMapIt mapIt = _mTransMatRoots.lower_bound(iSortKey);
        
        if(mapIt == _mTransMatRoots.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create(ScalarSortTreeBuilder::Proto);
            
            pBuilder->setNodePool(_pNodePool);
            
            mapIt = _mTransMatRoots.insert(mapIt, 
                                           std::make_pair(iSortKey, pBuilder));
        }
        
        if(mapIt->second == NULL)
        {
            mapIt->second = 
                _pTreeBuilderPool->create(ScalarSortTreeBuilder::Proto);
            
            mapIt->second->setNodePool(_pNodePool);
        }
        
        RenderTreeNode *pNewElem = _pNodePool->create();
        
        Pnt3f         objPos;
        
        actNode->getVolume().getCenter(objPos);
        
        _currMatrix.second.mult(objPos);
        
        pNewElem->setNode       (&*actNode);
        pNewElem->setFunctor    ( func      );
        pNewElem->setMatrixStore(_currMatrix);
        pNewElem->setState      ( pState    );
        pNewElem->setScalar     ( objPos[2] );
        
        if(_sStateOverrides.top()->empty() == false)
        {
            pNewElem->setStateOverride(_sStateOverrides.top());
        }

        mapIt->second->add(_oDrawEnv,
                            this,
                            pNewElem,
                            NULL,
                            NULL,
                            0);
    }
    else if(rt != NULL && rt->getOcclusionCulling() == true)
    {
        BuildKeyMapIt mapIt = _mMatRoots.lower_bound(iSortKey);
        
        if(mapIt == _mMatRoots.end() || mapIt->first != iSortKey)
        {
            TreeBuilderBase *pBuilder =
                _pTreeBuilderPool->create(OcclusionCullingTreeBuilder::Proto);
            
            pBuilder->setNodePool(_pNodePool);
            
            mapIt = _mMatRoots.insert(mapIt, 
                                      std::make_pair(iSortKey, pBuilder));
        }
        
        if(mapIt->second == NULL)
        {
            mapIt->second = 
                _pTreeBuilderPool->create(OcclusionCullingTreeBuilder::Proto);
            
            mapIt->second->setNodePool(_pNodePool);
        }
        
        RenderTreeNode *pNewElem = _pNodePool->create();
        
        Pnt3f           objPos;
        
        //_oDrawEnv.getRTAction()->getActNode()->getVolume().getCenter(objPos);
        
        //_currMatrix.second.mult(objPos);

        DynamicVolume     objVol;

        objVol = actNode->getVolume();

        Pnt3r min,max;

        objVol.getBounds(min,max);

        Pnt3r p[8];
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
            _currMatrix.second.mult(p[i]);
        }

        objPos = p[0];

        for(UInt32 i = 1; i < 8; i++)
        {
            if(p[0][2] < objPos[2])
            {
                objPos[2] = p[0][2];
            }
        }
        
        //std::cout << objPos[2] << std::endl;

        pNewElem->setVol        ( objVol                   );
        pNewElem->setNode       (&*actNode                 );

        pNewElem->setFunctor    ( func                     );
        pNewElem->setMatrixStore(_currMatrix               );
        pNewElem->setState      ( pState                   );

        // Normalize scalar to 0..1 for bucket sorting
        pNewElem->setScalar     ( (-objPos[2] - getNear()) / 
                                  (getFar()   - getNear()) ); 
        
        if(_sStateOverrides.top()->empty() == false)
        {
            pNewElem->setStateOverride(_sStateOverrides.top());
        }
        mapIt->second->add(_oDrawEnv,
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
                _pTreeBuilderPool->create(StateSortTreeBuilder::Proto);
            
            pBuilder->setNodePool(_pNodePool);
            
            mapIt = _mMatRoots.insert(mapIt, 
                                      std::make_pair(iSortKey, pBuilder));
        }

        if(mapIt->second == NULL)
        {
            mapIt->second = _pTreeBuilderPool->create(
                StateSortTreeBuilder::Proto);

            mapIt->second->setNodePool(_pNodePool);
        }

        RenderTreeNode *pNewElem  = _pNodePool->create();
        StateOverride  *pOverride = NULL;

        pNewElem->setNode       (&* actNode   );
        pNewElem->setFunctor    (   func      );
        pNewElem->setMatrixStore(  _currMatrix);
               
        if(_sStateOverrides.top()->empty() == false)
        {
            pOverride = _sStateOverrides.top();
        }

        mapIt->second->add(_oDrawEnv,
                            this,
                            pNewElem,
                            pState,
                            pOverride,
                           _uiKeyGen );
    }
}

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

Int32 RenderPartition::allocateLightIndex(void)
{
    Int32 returnValue = _iNextLightIndex++;

    if(_iNextLightIndex > 7)
    {
        return -_iNextLightIndex;
    }
    else
    {
        return returnValue;
    }
}

void RenderPartition::releaseLightIndex(void)
{
    --_iNextLightIndex;
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
    
    DynamicVolume vol;

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
bool RenderPartition::pushVisibility(NodePtrConstArg pNode)
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
   
    
    DynamicVolume vol     = pNode->editVolume(true);
    FrustumVolume frustum = _oFrustum;

#if 1
    vol.transform(topMatrix());
#else   
    // not quite working 
    Matrix m = topMatrix();
    m.invert();
    
    frustum.transform(m);
#endif

  
    if(_oDrawEnv.getStatCollector() != NULL)
    {
        _oDrawEnv.getStatCollector()->getElem(statCullTestedNodes)->inc();
    }

//    _oDrawEnv.getRTAction()->getStatistics()->getElem(statCullTestedNodes)->inc();

    if(intersect(frustum, vol, inplanes) == false)
    {
         result = false;

         col.setValuesRGB(1,0,0);

         if(_oDrawEnv.getStatCollector() != NULL)
         {
             _oDrawEnv.getStatCollector()->getElem(statCulledNodes)->inc();
         }

//        _oDrawEnv.getRTAction()->getStatistics()->getElem(statCulledNodes)->inc();

//        fprintf(stderr,"node 0x%p invis %0xp\n", &(*pNode), this);
    }
    else
    {
//        fprintf(stderr,"node 0x%p vis %0xp\n", &(*pNode), this);

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
//        dropVolume(this, pNode, col);
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
    _visibilityStack.push_back(FrustumVolume::P_NONE);
}

void RenderPartition::initFrom(RenderPartition *pSource,
                               RenderPartition *pInitial,
                               Int32            uiCopyOnPush)
{
    if(uiCopyOnPush == 0x0000 || pSource == NULL)
    {
        _sStateOverrides.push(_pStatePool->create());
        _visibilityStack.push_back(FrustumVolume::P_NONE);

        return;
    }

    if(0x0000 != (uiCopyOnPush & CopyStateOverride))
    {
    }
    else
    {
        _sStateOverrides.push(_pStatePool->create());
    }

    if(0x0000 != (uiCopyOnPush & CopyVisibility))
    {
    }
    else
    {
        _visibilityStack.push_back(FrustumVolume::P_NONE);
    }

    if(0x0000 != (uiCopyOnPush & CopyViewing))
    {
        this->setupViewing(pSource->getViewing());
    }

    if(0x0000 != (uiCopyOnPush & CopyProjection))
    {
        this->setupProjection(pSource->getProjection(),
                              pSource->getProjectionTrans());
    }

    if(0x0000 != (uiCopyOnPush & CopyViewport))
    {
        this->setViewport(pSource->getViewport());
    }

    if(0x0000 != (uiCopyOnPush & CopyWindow))
    {
        this->setWindow  (pSource->getWindow());
    }

    if(0x0000 != (uiCopyOnPush & CopyViewportSize))
    {
        this->setViewportDimension(pSource->_iPixelLeft,
                                   pSource->_iPixelBottom,
                                   pSource->_iPixelRight,
                                   pSource->_iPixelTop,
                                   pSource->_bFull);

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
}

void RenderPartition::initVPMatricesFromCamera(void)
{
    _oDrawEnv.initVPMatricesFromCamera();
}

void RenderPartition::exit(void)
{
    if(_bDone == true)
        return;

    _sStateOverrides.pop();

    _oDrawEnv.deactivateState();

    _bDone = true;
}


void RenderPartition::updateTopMatrix(void)
{
    _accMatrix = _oDrawEnv.getCameraToWorld();
    _accMatrix.mult(_currMatrix.second);
}

void RenderPartition::pushMatrix(const Matrix &matrix)
{
    _vMatrixStack.push_back(_currMatrix);
    
    _currMatrix.first = ++_uiMatrixId;
    _currMatrix.second.mult(matrix);
   
    updateTopMatrix();
}

void RenderPartition::popMatrix(void         )
{
    _currMatrix.first  = _vMatrixStack.back().first;
    _currMatrix.second = _vMatrixStack.back().second;
 
    updateTopMatrix();

    _vMatrixStack.pop_back();
}

const Matrix &RenderPartition::topMatrix(void)
{
    return _accMatrix;
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

#endif

#ifdef WIN32
__declspec(dllexport)
void dummyTav(void)
{
}
#endif

