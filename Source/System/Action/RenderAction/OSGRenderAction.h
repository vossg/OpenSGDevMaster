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

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    static StatElemDesc<StatTimeElem   > statDrawTime;
    static StatElemDesc<StatIntElem    > statNMaterials;
    static StatElemDesc<StatIntElem    > statNMatrices;
    static StatElemDesc<StatIntElem    > statNGeometries;
    static StatElemDesc<StatIntElem    > statNTransGeometries;

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



    void setStateSorting(bool s);
    bool getStateSorting(void);

    std::vector<Light *> getActiveLights(void);
    UInt32 getActiveLightsMask(void);
    UInt32 getActiveLightsCount(void);

    /*------------------------- comparison ----------------------------------*/

    void setSortTrans(bool bVal);
    bool getSortTrans(void);
    void setZWriteTrans(bool bVal);
    bool getZWriteTrans(void);
    void setLocalLights(bool bVal);
    bool getLocalLights(void);
    void setCorrectTwoSidedLighting(bool bVal);
    bool getCorrectTwoSidedLighting(void);
    void setOcclusionCulling(bool bVal);
    bool getOcclusionCulling(void);
    void setSmallFeatureCulling(bool bVal);
    bool getSmallFeatureCulling(void);
    void setSmallFeaturePixels(Real32 pixels);
    Real32 getSmallFeaturePixels(void);
    void setSmallFeatureThreshold(UInt32 threshold);
    UInt32 getSmallFeatureThreshold(void);
    void setUseGLFinish(bool s);
    bool getUseGLFinish(void);

    /*------------------------- comparison ----------------------------------*/

    bool isSmallFeature(const NodePtr &node);

    // test a single node
    bool            isVisible( Node* node );

    // visibility levels
    bool  pushVisibility(void);
    void  popVisibility(void);

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

    bool                      _bSortTrans;
    bool                      _bZWriteTrans;
    bool                      _bLocalLights;
    bool                      _bCorrectTwoSidedLighting;
    bool                      _bOcclusionCulling;
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

    bool                      _stateSorting;

    std::vector<FrustumVolume::PlaneSet>  _visibilityStack;

    GLuint _occlusionQuery;

    void (OSG_APIENTRY* _glGenQueriesARB)(GLsizei, GLuint*);
    void (OSG_APIENTRY* _glDeleteQueriesARB)(GLsizei, GLuint*);
    void (OSG_APIENTRY* _glBeginQueryARB)(GLenum, GLuint);
    void (OSG_APIENTRY* _glEndQueryARB)(GLenum);
    void (OSG_APIENTRY* _glGetQueryObjectuivARB)(GLuint, GLenum, GLuint*);

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

    //-----------------------------------------------------------------------
    //   friend functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables
    //-----------------------------------------------------------------------

    static char cvsid[];

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


