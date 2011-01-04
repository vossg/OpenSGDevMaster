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

#ifndef _OSGOCCLUSIONCULLINGTREEBUILDER_H_
#define _OSGOCCLUSIONCULLINGTREEBUILDER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <queue>

#include "OSGTreeBuilderBase.h"
#include "OSGHashSorter.h"
#include "OSGStatElemDesc.h"
#include "OSGStatIntElem.h"
#include "OSGStatRealElem.h"
#include "OSGState.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OCRenderTreeNode;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \class OcclusionCullingTreeBuilder
    \brief OcclusionCullingTreeBuilder class
    \ingroup GrpSystemRenderingBackendTreeBuild
    \ingroup GrpLibOSGSystem
 */

class OSG_SYSTEM_DLLMAPPING OcclusionCullingTreeBuilder : public TreeBuilderBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    static StatElemDesc<StatIntElem>  statNOccNodes;
    static StatElemDesc<StatIntElem>  statNOccTests;
    static StatElemDesc<StatIntElem>  statNOccInvisible;
    static StatElemDesc<StatRealElem> statNOccSuccessTestPer;
    static StatElemDesc<StatIntElem>  statNOccTriangles;

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    typedef TreeBuilderBase  Inherited;

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //! Sorting mode to use
    enum SortModeE
    {
        ModeScalar,         //!< Use standard scalar sort
        ModeBucket,         //!< Use fixed bucket sorting
        ModeAdaptiveBucket  //!< Use adaptive bucket sorting
    };

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static SortModeE setSortMode(SortModeE mode    );
    static UInt32    setNBuckets(UInt32    nbuckets);

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

             OcclusionCullingTreeBuilder(void);
    virtual ~OcclusionCullingTreeBuilder(void);

    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    virtual void setNodePool(RenderTreeNodePool *pNodePool);

    /*------------------------- comparison ----------------------------------*/

    virtual void reset(void);

    /*------------------------- comparison ----------------------------------*/

    virtual void add(RenderActionBase    *pAction,
                     RenderPartitionBase *pPart,
                     DrawFunctor         &drawFunc,
                     State               *pState,
                     StateOverride       *pStateOverride);

    virtual void draw(DrawEnv             &denv,
                      RenderPartitionBase *pPart);

    /*-------------------------- comparison ---------------------------------*/

    static bool staticInit(void);

    /*-------------------------- comparison ---------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
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

    void testNode       (OCRenderTreeNode    *pNode,
                         DrawEnv             &denv,
                         RenderPartitionBase *part,
                         Real32              &scr_percent);
    void drawTestNode   (OCRenderTreeNode    *pNode,
                         DrawEnv             &denv,
                         RenderPartitionBase *part);
    void drawNode       (OCRenderTreeNode    *pNode,
                         DrawEnv             &denv,
                         RenderPartitionBase *part);
    void drawTestResults(DrawEnv             &denv,
                         RenderPartitionBase *part);

    OCRenderTreeNode *createNode(RenderActionBase    *pAction,
                                 RenderPartitionBase *pPart,
                                 DrawFunctor         &drawFunc,
                                 State               *pState,
                                 StateOverride       *pStateOverride);

    void addNode                  (OCRenderTreeNode *pNode);
    void addNodeAdaptiveBucketMode(OCRenderTreeNode *pNode);
    void addNodeBucketMode        (OCRenderTreeNode *pNode);
    void addNodeScalarMode        (OCRenderTreeNode *pNode);


    inline
    void enterTesting(DrawEnv             &denv,
                      RenderPartitionBase *part);

    inline
    void leaveTesting(DrawEnv             &denv,
                      RenderPartitionBase *part);

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

    static UInt32 _extOcclusionQuery;

    static UInt32 _funcGenQueriesARB;
    static UInt32 _funcGetQueryObjectuivARB;
    static UInt32 _funcBeginQueryARB;
    static UInt32 _funcEndQueryARB;

    static bool                    _isOccStateCreated;
    static StateMTRecPtr           _testingStatePtr;
    static State                  *_testingState;

    static UInt32       _numBuckets;  //!< number of buckets for approximate sorting
    static SortModeE    _sortMode;  //!< Sorting mode to use

    OCRenderTreeNode   *_pRoot;

    std::vector<GLuint> _testSamples;
    UInt32              _numTestSamples;
    bool                _occInitialized;

    UInt32              _currSample;  //!< Last current sample test number
    UInt32              _testedNodes; //!< Number of OC tested nodes
    bool                _inTesting;   //!< Whether in testing mode or not


    std::vector<OCRenderTreeNode*> _buckets;     //!< buckets for approximate sorting
    std::vector<OCRenderTreeNode*> _bucketsWork; //!< work copy of buckets
    Real32 _bucketLow;                           //!< value for lowest bucket
    Real32 _bucketHigh;                          //!< value for highest bucket
    Real32 _bucketScale;                         //!< 1 / all buckets width

    std::vector<OCRenderTreeNode*> _testNodes;        //!< Nodes currently being tested
    std::queue <OCRenderTreeNode*> _testPendingNodes; //!< Nodes with tests pending
    UInt32                         _numNodes;

    //-----------------------------------------------------------------------
    //   traversal data cache
    //-----------------------------------------------------------------------

    Matrix                  _worldToScreen;
    Int32                   _vpWidth;
    Int32                   _vpHeight;
    RenderAction           *_ract;
    UInt32                 _minFeatureSize;
    UInt32                 _visPixelThreshold;
    Real32                 _coveredProbThreshold;
    //Real32                 _screenPercent;
    UInt32                 _minTriangleCount;

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

    static bool releaseTestingState(void);

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OcclusionCullingTreeBuilder &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGOcclusionCullingTreeBuilder.inl"

#endif /* _OSGOCCLUSIONCULLINGTREEBUILDER_H_ */


