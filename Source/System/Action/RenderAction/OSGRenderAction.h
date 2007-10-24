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

#include <vector>
#include <stack>
#include <map>
#include <set>

#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGDrawActionBase.h"
#include "OSGMatrix.h"
#include "OSGMaterial.h"
#include "OSGStatElemTypes.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Material;
class DrawTreeNode;
class MaterialDrawable;
class State;
class Light;
class LightEnv;
class LightChunk;
#if 0
class ClipPlane;
#endif
class SClipPlaneChunk;
class DrawTreeNodeFactory;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief RenderAction class
 */

class OSG_SYSTEM_DLLMAPPING RenderAction : public DrawActionBase
{
  public:

    typedef struct
    {
        UInt32  first;
        Matrixr second;
        Matrixr acc;
    }
    MatrixStore;

    typedef std::map <Material   *,      DrawTreeNode *> MaterialMap;
    typedef std::pair<LightChunk *,      Matrixr       > LightStore;
    typedef std::pair<SClipPlaneChunk *, Matrix        > ClipPlaneStore;

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    static StatElemDesc<StatTimeElem   > statDrawTime;
    static StatElemDesc<StatIntElem    > statNMaterials;
    static StatElemDesc<StatIntElem    > statNMatrices;
    static StatElemDesc<StatIntElem    > statNGeometries;
    static StatElemDesc<StatIntElem    > statNTransGeometries;
    static StatElemDesc<StatStringElem > statNOcclusionMode;
    static StatElemDesc<StatIntElem    > statNOcclusionTests;
    static StatElemDesc<StatIntElem    > statNOcclusionCulled;

    static const Int32 OcclusionStopAndWait;
    static const Int32 OcclusionMultiFrame;
    static const Int32 OcclusionHierarchicalMultiFrame;

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static RenderAction *create      (void                    );

    static void          setPrototype(RenderAction *pPrototype);
    static RenderAction *getPrototype(void                    );


    static void registerEnterDefault (const FieldContainerType &type,
                                      const Action::Functor    &func);

    static void registerLeaveDefault (const FieldContainerType &type,
                                      const Action::Functor    &func);

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    virtual ~RenderAction(void);

    /*------------------------- your_category -------------------------------*/

    virtual Action::ResultE start(void       );
    virtual Action::ResultE stop (ResultE res);

    /*------------------------- your_operators ------------------------------*/

           void           push_matrix(const Matrixr &matrix);
           void           pop_matrix (      void           );

    inline const Matrixr &top_matrix (      void           );

    /*------------------------- assignment ----------------------------------*/

    void dropGeometry(MaterialDrawable      *pGeo);
    void dropFunctor (Material::DrawFunctor &func, Material *mat);

    void dropLight     (Light     *pLight);
    void undropLight   (Light     *pLight);

    void dropLightEnv  (LightEnv  *pLightEnv);
    void undropLightEnv(LightEnv  *pLightEnv);

#if 0
    void dropClipPlane  (ClipPlane     *pClipPlane);
    void undropClipPlane(ClipPlane     *pClipPlane);
#endif

    void setStateSorting(bool s);
    bool getStateSorting(void);

    std::vector<Light *> getActiveLights(void);
    UInt32 getActiveLightsMask(void);
    UInt32 getActiveLightsCount(void);

    const std::vector<UInt32> &getLightEnvsLightsState(void);

    inline State *getCurrentState(void);

    /*------------------------- comparison ----------------------------------*/

    void setSortTrans(bool bVal);
    bool getSortTrans(void) const;

    void setZWriteTrans(bool bVal);
    bool getZWriteTrans(void) const;

    void setLocalLights(bool bVal);
    bool getLocalLights(void) const;

    void setCorrectTwoSidedLighting(bool bVal);
    bool getCorrectTwoSidedLighting(void) const;

    void setOcclusionCulling(bool bVal);
    bool getOcclusionCulling(void) const;

    void setOcclusionCullingMode(Int32 mode);
    Int32 getOcclusionCullingMode(void) const;
    void setOcclusionCullingPixels(UInt32 pixels);
    UInt32 getOcclusionCullingPixels(void) const;
    void setOcclusionCullingThreshold(UInt32 threshold);
    UInt32 getOcclusionCullingThreshold(void) const;

    void setSmallFeatureCulling(bool bVal);
    bool getSmallFeatureCulling(void) const;
    void setSmallFeaturePixels(Real32 pixels);
    Real32 getSmallFeaturePixels(void) const;
    void setSmallFeatureThreshold(UInt32 threshold);
    UInt32 getSmallFeatureThreshold(void) const;
    void setUseGLFinish(bool s);
    bool getUseGLFinish(void) const;

    /*------------------------- comparison ----------------------------------*/

    bool isSmallFeature(const NodePtr &node);
    bool isOccluded(DrawTreeNode *pRoot);
    void deleteOcclusionQueriesPool(void);
    GLuint getOcclusionQuery(void);
    GLuint getOcclusionQuery(NodePtr node);
    void setOcclusionQuery(NodePtr node, GLuint occlusionQuery);
    void resetOcclusionQueryIndex(void);
    void setOcclusionMask(NodePtr node, UInt8 mask);
    bool hasGeometryChild(NodePtr node);

    void drawOcclusionBB(const Pnt3r &bbmin, const Pnt3r &bbmax);
    void drawMultiFrameOcclusionBB(DrawTreeNode *pRoot);
    void drawHierarchicalMultiFrameOcclusionBB(const Matrixr &view, NodePtr node);
    // test a single node
    bool            isVisible( Node* node );

    // visibility levels
    bool  pushVisibility(void);
    void  popVisibility(void);

    void (OSG_APIENTRY* _glGenQueriesARB)(GLsizei, GLuint*);
    void (OSG_APIENTRY* _glDeleteQueriesARB)(GLsizei, GLuint*);
    void (OSG_APIENTRY* _glBeginQueryARB)(GLenum, GLuint);
    void (OSG_APIENTRY* _glEndQueryARB)(GLenum);
    void (OSG_APIENTRY* _glGetQueryObjectuivARB)(GLuint, GLenum, GLuint*);

  protected:

    //-----------------------------------------------------------------------
    //   enums
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types
    //-----------------------------------------------------------------------

    typedef DrawActionBase Inherited;

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    static RenderAction    *_pPrototype;

    static std::vector<Functor> *_vDefaultEnterFunctors;
    static std::vector<Functor> *_vDefaultLeaveFunctors;

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    static bool terminateEnter(void);
    static bool terminateLeave(void);

    //-----------------------------------------------------------------------
    //   instance variables
    //-----------------------------------------------------------------------

    DrawTreeNodeFactory      *_pNodeFactory;

    UInt32                    _uiMatrixId;

    MatrixStore               _currMatrix;
    Matrixr                   _camInverse;

    std::vector<MatrixStore>  _vMatrixStack;

    MaterialMap               _mMatMap;

    //DrawTreeNode             *_pRoot;
    typedef std::map<Int32, DrawTreeNode *> SortKeyMap;
    SortKeyMap                  _pMatRoots;

    typedef std::map<Real,  DrawTreeNode *> TransSortMap;
    typedef std::map<Int32, TransSortMap  > TransSortKeyMap;
    TransSortKeyMap             _pTransMatRoots;

    DrawTreeNode               *_pNoStateSortRoot;
    DrawTreeNode               *_pNoStateSortTransRoot;

    typedef std::map<Real, DrawTreeNode  *> OCMap;
    OCMap                       _ocRoot;

    UInt32                    _uiActiveMatrix;
    State                    *_pActiveState;

    UInt32                    _uiNumMaterialChanges;
    UInt32                    _uiNumMatrixChanges;
    UInt32                    _uiNumGeometries;
    UInt32                    _uiNumTransGeometries;
    UInt32                    _uiNumOcclusionTests;
    UInt32                    _uiNumOcclusionCulled;

    bool                      _bSortTrans;
    bool                      _bZWriteTrans;
    bool                      _bLocalLights;
    bool                      _bCorrectTwoSidedLighting;
    bool                      _bOcclusionCulling;
    Int32                     _occlusionCullingMode;
    UInt32                    _occlusionCullingPixels;
    UInt32                    _occlusionCullingThreshold;
    UInt32                    _currentOcclusionQueryIndex;
    std::vector<NodePtr>      _occluded_nodes;
    std::set<UInt32>          _hier_occlusions;
    UInt32                    _occ_bb_dl;

    bool                      _bSmallFeatureCulling;
    Real32                    _smallFeaturesPixels;
    UInt32                    _smallFeaturesThreshold;
    Matrixr                   _worldToScreenMatrix;
    bool                      _useGLFinish;

    std::vector<LightStore>   _vLights;
    std::vector<Light *>      _lightsMap;
    UInt32                    _lightsState;
    UInt32                    _activeLightsState;
    UInt32                    _activeLightsCount;
    UInt32                    _activeLightsMask;

    std::vector<std::vector<UInt32> > _lightsTable;
    std::vector<UInt32>               _lightsPath;
    std::vector<UInt32>               _lightEnvsLightsState;

    std::vector<ClipPlaneStore> _vClipPlanes;
#if 0
    std::vector<ClipPlane *>    _clipPlanesMap;
#endif
    UInt32                      _clipPlanesState;
    UInt32                      _activeClipPlanesState;
    UInt32                      _activeClipPlanesCount;
    UInt32                      _activeClipPlanesMask;

    std::vector<std::vector<UInt32> > _clipPlanesTable;
    std::vector<UInt32>               _clipPlanesPath;

    bool                      _stateSorting;

    std::vector<FrustumVolume::PlaneSet>  _visibilityStack;

    GLuint _occlusionQuery;
    std::vector<GLuint> _occlusionQueriesPool;
    std::map<UInt32, GLuint> _occlusionQueries;


    Int32 _cgChunkId;
    Int32 _cgfxChunkId;
    Int32 _shlChunkId;

    static UInt32 _arbOcclusionQuery;
    static UInt32 _funcGenQueriesARB;
    static UInt32 _funcDeleteQueriesARB;
    static UInt32 _funcBeginQueryARB;
    static UInt32 _funcEndQueryARB;
    static UInt32 _funcGetQueryObjectuivARB;

//    Time                 _tMatSlot

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    RenderAction(void);
    RenderAction(const RenderAction &source);

    void operator =(const RenderAction &source);

    // access default functors

    virtual std::vector<Functor> *getDefaultEnterFunctors(void);
    virtual std::vector<Functor> *getDefaultLeaveFunctors(void);

            void dump(DrawTreeNode *pRoot, UInt32 uiIndent);
            void updateShader(State *state);
   virtual void draw(DrawTreeNode *pRoot);

    inline  void updateTopMatrix(void);
            void activateLocalLights(DrawTreeNode *pRoot);
            void activateLocalClipPlanes(DrawTreeNode *pRoot);

    void getMaterialStates(Material *mat, std::vector<State *> &states);

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

    friend class ShadowViewport;

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
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGRenderAction.inl"

#endif /* _OSGRENDERACTION_H_ */


