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

#ifndef _OSGRENDERTRAVERSALACTION_H_
#define _OSGRENDERTRAVERSALACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stack>

#include "OSGRenderTravDef.h"
#include "OSGRenderTraversalFwd.h"
#include "OSGRenderTraversalActionBase.h"
#include "OSGRenderPartition.h"
#include "OSGMaterial.h"

#include "OSGMixinHead.h"
#include "OSGDataSlotMixin.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class State;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

struct RenderTravDataSlotDesc
{
    typedef RenderTraversalActionBase ParentT;
};

typedef DataSlotMixin< 
            MixinHead < 
                RenderTravDataSlotDesc > > RenderTraversalActionParent;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief RenderTraversalAction class
 */

class OSG_RENDERTRAV_DLLMAPPING RenderTraversalAction : 
    public RenderTraversalActionParent
{
  public:

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    static StatElemDesc<StatTimeElem>     statDrawTime;
    static StatElemDesc<StatIntElem >     statNStates;
    static StatElemDesc<StatIntElem >     statNMatrices;
    static StatElemDesc<StatIntElem >     statNGeometries;
//    static StatElemDesc<StatIntElem > statNTransGeometries;
    static StatElemDesc<StatIntElem >     statNTriangles;
    static StatElemDesc<StatIntElem >     statNShaders;
    static StatElemDesc<StatIntElem >     statNShaderParams;

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    typedef std::vector<RenderPartition *> RenderPartitionStore;
    typedef std::stack <RenderPartition *> RenderPartitionStack;
    typedef std::stack <Int32            > RenderPartitionIdxStack;

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static
    RenderTraversalAction *create      (void                             );

    static
    void                   setPrototype(RenderTraversalAction *pPrototype);

    static
    RenderTraversalAction *getPrototype(void                             );


    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static void registerEnterDefault (const FieldContainerType &type,
                                      const Action::Functor    &func      );

    static void registerLeaveDefault (const FieldContainerType &type,
                                      const Action::Functor    &func      );

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    virtual ~RenderTraversalAction(void);

    /*------------------------- your_category -------------------------------*/

    ResultE recurceNoNodeCallbacks(NodePtrConstArg node);

    /*------------------------- your_operators ------------------------------*/

    virtual Action::ResultE start(void       );
    virtual Action::ResultE stop (ResultE res);

    /*------------------------- your_operators ------------------------------*/

    void dropFunctor(Material::DrawFunctor &func,
                     State                 *pState,
                     UInt32                 uiSortKey);

    /*---------------------------- state ------------------------------------*/

    void pushState  (void                             );
    void popState   (void                             );

    void addOverride(UInt32 uiSlot, StateChunk *pChunk);

    /*---------------------------- state ------------------------------------*/

    Int32 allocateLightIndex(void);
    void  releaseLightIndex (void);

    /*--------------------------- matrix ------------------------------------*/

          void    pushMatrix (const Matrix &matrix);
          void    popMatrix  (      void          );

    const Matrix &topMatrix  (      void          );

    /*------------------------- visibility ---------------------------------*/

    // test a single node
    virtual bool isVisible      (Node *node);

    // visibility levels
            bool  pushVisibility(void      );
            void  popVisibility (void      );

    /*------------------------- culling ------------------------------------*/

    // control activation of frustum culling
    virtual bool                 getFrustumCulling(void                ) const;
    virtual void                 setFrustumCulling(bool val = true     );

    // control frustum
    virtual const FrustumVolume &getFrustum       (void                ) const;
    virtual void                 setFrustum       (FrustumVolume &frust);

    /*------------------------- comparison ----------------------------------*/

    void      overrideMaterial(Material        *pMaterial,
                               NodePtrConstArg  pNode    );

    Material *getMaterial(void);

    void setKeyGen(UInt32 uiKeyGen);

    /*------------------------- comparison ----------------------------------*/


    void pushPartition(UInt32 uiCopyOnPush = 0x0000,
                       RenderPartition::Mode eMode =
                                                RenderPartition::StateSorting);
    void popPartition (void                        );

    RenderPartition *getActivePartition(void);

    /*----------- multi-frame buffering / split cull/draw -------------------*/

    void      addPassMask(BitVector bvMask);
    void      subPassMask(BitVector bvMask);
    BitVector getPassMask(void            );

    /*----------- multi-frame buffering / split cull/draw -------------------*/

    void    setDoCullOnly(bool val);
    bool    getDoCullOnly(void);
    void    setNumBuffers(UInt32 n);
    UInt32  getNumBuffers(void);
    void    setCurrentBuffer(UInt32 b);
    UInt32  getCurrentBuffer(void);

    // use with care. Should probably be more protected
    void    drawBuffer(UInt32 buf);

    /*----------- multi-frame buffering / split cull/draw -------------------*/

    void setUseGLFinish(bool bVal);
    bool getUseGLFinish(void     );

    /*------------------ Occlusion Culling control --------------------------*/

    void setOcclusionCulling(const bool bVal);
    bool getOcclusionCulling(void     );

    void setOcclusionCullingDebug(const bool bVal);
    bool getOcclusionCullingDebug(void     );

    void setOcclusionDebugMasks(const UInt32 tested, const UInt32 culled, const UInt32 visible);
    UInt32 getOcclusionTestedDebugMask(void);
    UInt32 getOcclusionCulledDebugMask(void);
    UInt32 getOcclusionVisibleDebugMask(void);

    void setOcclusionCullingMinimumFeatureSize(const UInt32 pixels);
    UInt32 getOcclusionCullingMinimumFeatureSize(void);

    void setOcclusionCullingVisibilityThreshold(const UInt32 pixels);
    UInt32 getOcclusionCullingVisibilityThreshold(void);

    void setOcclusionCullingCoveredThreshold(const Real32 percent);
    Real32 getOcclusionCullingCoveredThreshold(void);

    void setOcclusionCullingQueryBufferSize(const UInt32 size);
    UInt32 getOcclusionCullingQueryBufferSize(void);

    void setOcclusionCullingMinimumTriangleCount(const UInt32 count);
    UInt32 getOcclusionCullingMinimumTriangleCount(void);

    /*------------------- ScreenLOD Control -------------------------------*/
    void setScreenLODCoverageThreshold(const Real32 percent);
    Real32 getScreenLODCoverageThreshold(void);

    void setScreenLODNumLevels(const UInt32 levels);
    UInt32 getScreenLODNumLevels(void);

    void setScreenLODDegradationFactor(const Real32 percent);
    Real32 getScreenLODDegradationFactor(void);


  protected:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    typedef RenderTraversalActionParent Inherited;

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    static RenderTraversalAction *_pPrototype;

    static std::vector<Functor>  *_vDefaultEnterFunctors;
    static std::vector<Functor>  *_vDefaultLeaveFunctors;


    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static bool terminateEnter(void);
    static bool terminateLeave(void);

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    bool                    _doCullOnly;
    UInt32                  _numBuffers;
    UInt32                  _currentBuffer;

    UInt32                  _uiKeyGen;

    // Multi-buffered pools for cull/draw separation
    std::vector<RenderPartitionPool *> _pPartitionPools;
    std::vector<RenderTreeNodePool  *> _pNodePools;
    std::vector<StateOverridePool   *> _pStatePools;
    std::vector<TreeBuilderPool     *> _pTreeBuilderPools;

    std::vector<RenderPartitionStore > _vRenderPartitions;

    Int32                   _iActivePartitionIdx;
    RenderPartition        *_pActivePartition;

    RenderPartitionStack    _sRenderPartitionStack;
    RenderPartitionIdxStack _sRenderPartitionIdxStack;

    BitVector               _bvPassMask;
    bool                    _bUseGLFinish;

    // Occlusion Culling

    bool                    _occlusionCulling;
    bool                    _occlusionCullingDebug;
    UInt32                  _occDMTested, _occDMCulled, _occDMVisible;
    UInt32                  _occMinFeatureSize, _occVisibilityThreshold;
    Real32                  _occCoveredThreshold;
    UInt32                  _occQueryBufferSize;
    UInt32                  _occMinimumTriangleCount;

    // Screen LOD
    Real32 _scrlodCoverageThreshold;
    UInt32 _scrlodNumLODsToUse;
    Real32 _scrlodDegradationFactor;

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    RenderTraversalAction(void);
    RenderTraversalAction(const RenderTraversalAction &source);

    // access default functors

    virtual std::vector<Functor> *getDefaultEnterFunctors(void);
    virtual std::vector<Functor> *getDefaultLeaveFunctors(void);

//            void dump(DrawTreeNode *pRoot, UInt32 uiIndent);
//    virtual void draw(DrawTreeNode *pRoot);

  private:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------


    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const RenderTraversalAction &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

Action::ResultE MaterialDrawableRenderEnter(const NodeCorePtr &pCore,
                                                  Action      *action);

Action::ResultE MaterialDrawableRenderLeave(const NodeCorePtr &pCore,
                                                  Action      *action);

OSG_END_NAMESPACE

#define OSGRENDERTRAVERSALACTION_HEADER_CVSID "@(#)$Id$"

#include "OSGRenderTraversalAction.inl"

#endif /* _OSGRENDERTRAVERSALACTION_H_ */


