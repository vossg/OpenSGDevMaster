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

#ifndef _OSGRENDERACTION_H_
#define _OSGRENDERACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stack>

#include "OSGRenderActionFwd.h"
#include "OSGRenderActionBase.h"
#include "OSGRenderPartition.h"
#include "OSGDrawEnv.h"
#include "OSGMaterial.h"
#include "OSGRenderActionTask.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class State;
class MultiCore;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief RenderAction class
    \ingroup GrpSystemRenderAction
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING RenderAction : public RenderActionBase
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
    typedef std::stack <bool             > RenderPartitionGrpStack;

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static
    RenderAction *create      (void                    );

    static
    void          setPrototype(RenderAction *pPrototype);

    static
    RenderAction *getPrototype(void                   );


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

    virtual ~RenderAction(void);

    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    virtual Action::ResultE start    (void       );
    virtual Action::ResultE stop     (ResultE res);

    virtual void            frameInit(void       );

    /*------------------------- your_operators ------------------------------*/

    void dropFunctor(DrawEnv::DrawFunctor &func,
                     State                *pState,
                     UInt32                uiSortKey,
                     bool                  bIgnoreOverrides = false);

    void dropFunctor(DrawEnv::DrawFunctor &func,
                     Material             *pMat,
                     bool                  bIgnoreOverrides = false);

    /*---------------------------- state ------------------------------------*/

    void pushState  (void                             );
    void popState   (void                             );

    void addOverride(UInt32 uiSlot, StateChunk *pChunk);

    /*---------------------------- state ------------------------------------*/

    Int32  allocateLightIndex(void);
    void   releaseLightIndex (void);
    UInt32 getLightState     (void) const;

    /*--------------------------- matrix ------------------------------------*/

    template<class MatrixType>
          void    pushMatrix (const MatrixType &matrix);
          void    popMatrix  (      void          );

    const Matrix &topMatrix  (      void          );

    /*------------------------- visibility ---------------------------------*/

    // test a single node
    virtual bool   isVisible     (Node *node);
            UInt32 selectVisibles(void      );

    // visibility levels
            bool  pushVisibility (void      );
            void  popVisibility  (void      );

    /*------------------------- comparison ----------------------------------*/

    void      overrideMaterial(Material *       pMaterial,
                               Node     * const pNode    );

    Material *getMaterial     (      void               );

    /*------------------------- comparison ----------------------------------*/

    void      setKeyGen(UInt32 uiKeyGen);

    /*------------------------- comparison ----------------------------------*/

    Int32 getActivePartitionIdx  (void                                       );
    Int32 getLastPartitionIdx    (void                                       );
    
    void  readdPartitionByIndex  (UInt32                uiPartIdx            );
    
    void  dumpPartitionList      (void                                       );

    void  disableDefaultPartition(void                                       );

    /*------------------------- comparison ----------------------------------*/

    RenderPartition *getActivePartition(void);

    /*----------- multi-frame buffering / split cull/draw -------------------*/

    void      addPassMask(BitVector bvMask);
    void      subPassMask(BitVector bvMask);
    BitVector getPassMask(void            );

    /*----------- multi-frame buffering / split cull/draw -------------------*/
    
    void   setDoCullOnly   (bool val);
    bool   getDoCullOnly   (void    );

    void   setNumBuffers   (UInt32 n);
    UInt32 getNumBuffers   (void    );

    void   setCurrentBuffer(UInt32 b);
    UInt32 getCurrentBuffer(void    );
   
    // use with care. Should probably be more protected
    void   drawBuffer      (UInt32 buf);

    /*------------------ Occlusion Culling control --------------------------*/

    void   setOcclusionCulling                    (const bool bVal     );
    bool   getOcclusionCulling                    (      void          );

    void   setOcclusionCullingDebug               (const bool bVal     );
    bool   getOcclusionCullingDebug               (      void          );

    void   setOcclusionDebugMasks                 (const UInt32 tested, 
                                                   const UInt32 culled, 
                                                   const UInt32 visible);

    UInt32 getOcclusionTestedDebugMask            (      void          );
    UInt32 getOcclusionCulledDebugMask            (      void          );
    UInt32 getOcclusionVisibleDebugMask           (      void          );

    void   setOcclusionCullingMinimumFeatureSize  (const UInt32 pixels );
    UInt32 getOcclusionCullingMinimumFeatureSize  (      void          );

    void   setOcclusionCullingVisibilityThreshold (const UInt32 pixels );
    UInt32 getOcclusionCullingVisibilityThreshold (      void          );

    void   setOcclusionCullingCoveredThreshold    (const Real32 percent);
    Real32 getOcclusionCullingCoveredThreshold    (      void          );

    void   setOcclusionCullingQueryBufferSize     (const UInt32 size   );
    UInt32 getOcclusionCullingQueryBufferSize     (      void          );

    void   setOcclusionCullingMinimumTriangleCount(const UInt32 count  );
    UInt32 getOcclusionCullingMinimumTriangleCount(      void          );

    /*------------------- ScreenLOD Control -------------------------------*/

    void   setScreenLODCoverageThreshold(const Real32 percent);
    Real32 getScreenLODCoverageThreshold(      void          );

    void   setScreenLODNumLevels        (const UInt32 levels);
    UInt32 getScreenLODNumLevels        (      void         );

    void   setScreenLODDegradationFactor(const Real32 percent);
    Real32 getScreenLODDegradationFactor(      void          );


  protected:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    typedef RenderActionBase Inherited;

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    static RenderAction          *_pPrototype;

    static Action::FunctorStore  *_vDefaultEnterFunctors;
    static Action::FunctorStore  *_vDefaultLeaveFunctors;


    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static bool terminateEnter(void);
    static bool terminateLeave(void);

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    bool                                _doCullOnly;
    UInt32                              _numBuffers;
    UInt32                              _currentBuffer;

    UInt32                              _uiKeyGen;

    // Multi-buffered pools for cull/draw separation
    std::vector<RenderPartitionPool *>  _pPartitionPools;
    std::vector<RenderTreeNodePool  *>  _pNodePools;
    std::vector<StateOverridePool   *>  _pStatePools;
    std::vector<TreeBuilderPool     *>  _pTreeBuilderPools;
    
    std::vector<RenderPartitionStore >  _vRenderPartitions;

    Int32                               _iActivePartitionIdx;
    bool                                _bInPartitionGroup;
    bool                                _bDefaultPartHandled;
    RenderPartition                    *_pActivePartition;

    RenderPartitionStack                _sRenderPartitionStack;
    RenderPartitionIdxStack             _sRenderPartitionIdxStack;
    RenderPartitionGrpStack             _sRenderPartitionGrpStack;

    BitVector                           _bvPassMask;

    // Occlusion Culling
    bool                                _occlusionCulling;
    bool                                _occlusionCullingDebug;
    UInt32                              _occDMTested;
    UInt32                              _occDMCulled;
    UInt32                              _occDMVisible;
    UInt32                              _occMinFeatureSize;
    UInt32                              _occVisibilityThreshold;
    Real32                              _occCoveredThreshold;
    UInt32                              _occQueryBufferSize;
    UInt32                              _occMinimumTriangleCount;

    // Screen LOD
    Real32                              _scrlodCoverageThreshold;
    UInt32                              _scrlodNumLODsToUse;
    Real32                              _scrlodDegradationFactor;

    RenderActionTaskRefPtr              _pGLFinishTask;

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    RenderAction(void);
    RenderAction(const RenderAction &source);

    // access default functors

    virtual Action::FunctorStore *getDefaultEnterFunctors(void);
    virtual Action::FunctorStore *getDefaultLeaveFunctors(void);

//            void dump(DrawTreeNode *pRoot, UInt32 uiIndent);
//    virtual void draw(DrawTreeNode *pRoot);

    void pushPartition           (UInt32                uiCopyOnPush = 0x0000, 
                                  RenderPartition::Mode eMode        = 
                                                RenderPartition::StateSorting);

    void popPartition            (void                                       );

    void beginPartitionGroup     (void                                       );
    void endPartitionGroup       (void                                       );

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

    template <class ParentT>
    friend class StageHandlerMixin;

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
    void operator =(const RenderAction &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

Action::ResultE MaterialDrawableRenderEnter(NodeCore * const pCore,
                                            Action   *       action);

Action::ResultE MaterialDrawableRenderLeave(NodeCore * const pCore,
                                            Action   *       action);

OSG_END_NAMESPACE

#include "OSGRenderAction.inl"

#endif /* _OSGRENDERACTION_H_ */


