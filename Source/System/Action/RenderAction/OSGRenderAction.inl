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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


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

/*------------- constructors & destructors --------------------------------*/

/*------------------------------ access -----------------------------------*/

inline
void RenderAction::dropFunctor(DrawEnv::DrawFunctor &func,
                               State                *pState,
                               UInt32                uiSortKey,
                               bool                  bIgnoreOverrides)
{
    _pActivePartition->dropFunctor(func, 
                                   pState, 
                                   uiSortKey,
                                   bIgnoreOverrides);
}

inline
void RenderAction::pushState(void)
{
    _pActivePartition->pushState();
}

inline
void RenderAction::popState(void)
{
    _pActivePartition->popState();
}

inline
void RenderAction::addOverride(UInt32 uiSlot, StateChunk *pChunk)
{
    _pActivePartition->addOverride(uiSlot, pChunk);
}

inline
const StateOverride *RenderAction::getCurrentOverrides(void) const
{
    return _pActivePartition->getCurrentOverrides();
}

inline
Int32 RenderAction::allocateLightIndex(void)
{
    return _pActivePartition->allocateLightIndex();
}

inline
void  RenderAction::releaseLightIndex(void)
{
    _pActivePartition->releaseLightIndex();
}

inline
UInt32 RenderAction::getLightState(void) const
{
    return _pActivePartition->getLightState();
}

template<class MatrixType> inline
void RenderAction::pushMatrix(const MatrixType &matrix)
{
    _pActivePartition->pushMatrix(matrix);
}

inline
void RenderAction::popMatrix(void)
{
    _pActivePartition->popMatrix();
}

inline
const Matrix &RenderAction::topMatrix(void)
{
    return _pActivePartition->topMatrix();
}

inline
bool RenderAction::isVisible(Node *node)
{
    return _pActivePartition->isVisible(node);
}

inline
void RenderAction::popVisibility(void)
{
    _pActivePartition->popVisibility();
}

inline
void RenderAction::overrideMaterial(Material *       pMaterial,
                                    Node     * const pNode    )
{
    _pActivePartition->overrideMaterial(pMaterial, pNode);
}

inline
Material *RenderAction::getMaterial(void)
{
    return _pActivePartition->getMaterial();
}

inline
void RenderAction::setKeyGen(UInt32 uiKeyGen)
{
    _uiKeyGen = uiKeyGen;
}

inline
Int32 RenderAction::getActivePartitionIdx(void)
{
    return _iActivePartitionIdx;
}

inline
Int32 RenderAction::getLastPartitionIdx(void)
{
    return Int32(_vRenderPartitions[_currentBuffer].size() - 1);
}

inline
void RenderAction::disableDefaultPartition(void)
{
    _vRenderPartitions[_currentBuffer][0]->disable();
}

inline
RenderPartition *RenderAction::getActivePartition(void)
{
    return _pActivePartition;
}

inline
void RenderAction::addPassMask(BitVector bvMask)
{
    _bvPassMask |= bvMask;
}

inline
void RenderAction::subPassMask(BitVector bvMask)
{
    _bvPassMask &= ~bvMask;
}

inline
BitVector RenderAction::getPassMask(void)
{
    return _bvPassMask;
}

inline
void RenderAction::setDoCullOnly(bool val)
{
    _doCullOnly = val;
}

inline
bool RenderAction::getDoCullOnly(void)
{
    return _doCullOnly;
}

inline
UInt32 RenderAction::getNumBuffers(void)
{
    return _numBuffers;
}

inline
void RenderAction::setCurrentBuffer(UInt32 b)
{
    _currentBuffer = b;
}

inline
UInt32 RenderAction::getCurrentBuffer(void)
{
    return _currentBuffer;
}

inline
void RenderAction::setOcclusionCulling(const bool val)
{
    _occlusionCulling = val;
}

inline
bool RenderAction::getOcclusionCulling(void)
{
    return _occlusionCulling;
}

inline
void RenderAction::setOcclusionCullingDebug(const bool val)
{
    _occlusionCullingDebug = val;
}

inline
bool RenderAction::getOcclusionCullingDebug(void)
{
    return _occlusionCullingDebug;
}

inline
void RenderAction::setOcclusionDebugMasks(const UInt32 tested, 
                                          const UInt32 culled, 
                                          const UInt32 visible)
{
    _occDMTested  = tested;
    _occDMCulled  = culled;
    _occDMVisible = visible;
}

inline
UInt32 RenderAction::getOcclusionTestedDebugMask(void)
{
    return _occDMTested;
}

inline
UInt32 RenderAction::getOcclusionCulledDebugMask(void)
{
    return _occDMCulled;
}

inline
UInt32 RenderAction::getOcclusionVisibleDebugMask(void)
{
    return _occDMVisible;
}

inline
void RenderAction::setOcclusionCullingMinimumFeatureSize(const UInt32 pixels)
{
    _occMinFeatureSize = pixels;
}

inline
UInt32 RenderAction::getOcclusionCullingMinimumFeatureSize(void)
{
    return _occMinFeatureSize;
}

inline
void RenderAction::setOcclusionCullingVisibilityThreshold(const UInt32 pixels)
{
    _occVisibilityThreshold = pixels;
}

inline
UInt32 RenderAction::getOcclusionCullingVisibilityThreshold(void)
{
    return _occVisibilityThreshold;
}

inline
void RenderAction::setOcclusionCullingCoveredThreshold(const Real32 percent)
{
    _occCoveredThreshold = percent;
}

inline
Real32 RenderAction::getOcclusionCullingCoveredThreshold(void)
{
    return _occCoveredThreshold;
}

inline
void RenderAction::setOcclusionCullingQueryBufferSize(const UInt32 size)
{
    _occQueryBufferSize = size;
}

inline
UInt32 RenderAction::getOcclusionCullingQueryBufferSize(void)
{
    return _occQueryBufferSize;
}

inline
void RenderAction::setOcclusionCullingMinimumTriangleCount(const UInt32 count)
{
    _occMinimumTriangleCount = count;
}

inline
UInt32 RenderAction::getOcclusionCullingMinimumTriangleCount(void)
{
    return _occMinimumTriangleCount;
}

inline
void RenderAction::setScreenLODCoverageThreshold(const Real32 percent)
{
    _scrlodCoverageThreshold = percent;
}

inline
Real32 RenderAction::getScreenLODCoverageThreshold(void)
{
    return _scrlodCoverageThreshold;
}

inline
void RenderAction::setScreenLODNumLevels(const UInt32 levels)
{
    _scrlodNumLODsToUse = levels;
}

inline
UInt32 RenderAction::getScreenLODNumLevels(void)
{
    return _scrlodNumLODsToUse;
}

inline
void RenderAction::setScreenLODDegradationFactor(const Real32 percent)
{
    _scrlodDegradationFactor = percent;
}

inline
Real32 RenderAction::getScreenLODDegradationFactor(void)
{
    return _scrlodDegradationFactor;
}

/*---------------------------- properties ---------------------------------*/


inline
void RenderAction::beginPartitionGroup(void)
{
    _sRenderPartitionIdxStack.push(_iActivePartitionIdx);

    _iActivePartitionIdx = Int32(_vRenderPartitions[_currentBuffer].size());

    _bInPartitionGroup = true;
}

inline
void RenderAction::endPartitionGroup(void)
{
    _iActivePartitionIdx = _sRenderPartitionIdxStack.top();

    _sRenderPartitionIdxStack.pop();

    _bInPartitionGroup = false;
}

/*-------------------------- your_category---------------------------------*/


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE
