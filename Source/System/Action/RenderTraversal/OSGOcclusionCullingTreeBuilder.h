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

#include "OSGHashSorter.h"
#include "OSGStatElemDesc.h"
#include "OSGStatIntElem.h"
#include "OSGStatRealElem.h"

#include "OSGTreeBuilderBase.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \class OcclusionCullingTreeBuilder
 *  \brief OcclusionCullingTreeBuilder class
 */

class OSG_RENDERTRAV_DLLMAPPING OcclusionCullingTreeBuilder : public TreeBuilderBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                             
    //-----------------------------------------------------------------------
   
    static OcclusionCullingTreeBuilder Proto;

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //! Sorting mode to use
    typedef enum { 
        ModeScalar, //!< Use standard scalar sort
        ModeBucket, //!< Use fixed bucket sorting
        ModeAdaptiveBucket  //!< Use adaptive bucket sorting
    } SortModeE;   
    
    static SortModeE setSortMode(SortModeE mode);
    
    static UInt32 setNBuckets(UInt32 nbuckets);
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------
    virtual void draw(DrawEnv &denv, RenderPartition *part);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------


    /*------------------------- your_category -------------------------------*/

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/
  
    /*------------------------- comparison ----------------------------------*/

    virtual void reset(void);

    /*------------------------- comparison ----------------------------------*/

    virtual void add(DrawEnv &denv, 
                     RenderPartition *part,
                     RenderTreeNode *pNode,
                     State          *pState,
                     StateOverride  *pStateOverride,
                     UInt32          uiKeyGen      );

    /*-------------------------- comparison ---------------------------------*/

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

    void testNode(RenderTreeNode *pNode, DrawEnv &denv, RenderPartition *part, Real32 &scr_percent);
    void drawNode(RenderTreeNode *pNode, DrawEnv &denv, RenderPartition *part);
    void drawTestNode(RenderTreeNode *pNode, DrawEnv &denv, RenderPartition *part);
    void drawTestResults(DrawEnv &denv, RenderPartition *part);

    inline void enterTesting(DrawEnv &denv, RenderPartition *part);
    inline void leaveTesting(DrawEnv &denv, RenderPartition *part);

    OcclusionCullingTreeBuilder(void);
    virtual ~OcclusionCullingTreeBuilder(void);

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

    friend class MultiPool<TreeBuilderBase>::TypeStore;
    UInt32 uNumNodes;

    static UInt32 _extOcclusionQuery;

    static UInt32 _funcGenQueriesARB;
    static UInt32 _funcGetQueryObjectuivARB;
    static UInt32 _funcBeginQueryARB;
    static UInt32 _funcEndQueryARB;

    static bool                    _isOccStateCreated;
    static StatePtr                _testingStatePtr;
    static State                  *_testingState;

    GLuint* _testSamples;
    UInt32  _numTestSamples;
    bool    _isOccSetup;
    UInt32  _currSample; //!< Last current sample test number
    //UInt32  _currSampleBack; //!< Last number we can test to
    UInt32  _testedNodes; //!< Number of OC tested nodes
    bool    _inTesting;  //!< Whether in testing mode or not
    
    static UInt32     _nBuckets;  //!< number of buckets for approximate sorting
    static SortModeE  _sortMode;  //!< Sorting mode to use
    
    std::vector<RenderTreeNode*> _buckets; //!< buckets for approximate sorting
    std::vector<RenderTreeNode*> _bucketsWork; //!< work copy of buckets
    Real32 _bucketLow;                     //!< value for lowest bucket
    Real32 _bucketHigh;                    //!< value for highest bucket
    Real32 _bucketScale;                   //!< 1 / all buckets width
   
    std::vector<RenderTreeNode*> _testNodes; //!< Nodes currently being tested
    std::queue<RenderTreeNode*> _testPendingNodes; //!< Nodes with tests pending

    //-----------------------------------------------------------------------
    //   traversal data cache                                                    
    //-----------------------------------------------------------------------
    
    Matrix                  _worldToScreen;
    Int32                   _vpWidth;
    Int32                   _vpHeight;
    RenderTraversalAction  *_rt;
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

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const OcclusionCullingTreeBuilder &source);    
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGOcclusionCullingTreeBuilder.inl"

#endif /* _OSGOCCLUSIONCULLINGTREEBUILDER_H_ */


