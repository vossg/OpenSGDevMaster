/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
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

#ifndef _OSGCOLLADAINTEGRATION_H_
#define _OSGCOLLADAINTEGRATION_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaIntegration.hpp
    \ingroup GrpFoundationLoader
 */

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"

#include "OSGNode.h"
#include "OSGChunkMaterial.h"

#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTransform.h"
#include "OSGImage.h"
#include "OSGTextureObjChunk.h"

#include "dae/daeIntegrationObject.h"
#include "dae/daeMetaElement.h"
#include "dom/domBind_material.h"
#include "dom/domProfile_COMMON.h"

#include <string>
#include <vector>
#include <map>

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

/*! \ingroup GrpFoundationLoader
 */


class ColladaIntegrationBase;
class GeometryInstanceIntegration;

typedef daeSmartRef<ColladaIntegrationBase> ColladaIntegrationBaseRef;
typedef daeTArray  <ColladaIntegrationBase> ColladaIntegrationBaseArray;

class ColladaIntegrationBase : public daeIntegrationObject
{
  public: // VIRTUAL INTEGRATION INTERFACE

	// This Method is used to create tool/runtime object
	virtual void createFrom(daeElementRef pElement);

	// This method translate from COLLADA to tool/runtime object
	virtual void fromCOLLADA(void);

	// This method is used as a second pass post process on tool/runtime objs
	virtual void fromCOLLADAPostProcess(void);

    // This Method is used to create tool/runtime object
	virtual void createTo(void *userData);

	// This method translate from COLLADA to tool/runtime object
	virtual void toCOLLADA(void);

	// This method is used as a second pass post process on tool/runtime objs
	virtual void toCOLLADAPostProcess(void);

  public: // STATIC METHODS
	
    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );
	
  public: // STATIC MEMBERS
	
    static daeMetaElement *_pMeta;

  public: // USER CODE

    ColladaIntegrationBase(void);
	virtual ~ColladaIntegrationBase(void);

  protected: // USER CODE

	daeElement *_pElement;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class VisualSceneIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement *_pMeta;

    NodeUnrecPtr _pScene;

  public:

    VisualSceneIntegration(void);
    ~VisualSceneIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    Node *getScene(void);

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<VisualSceneIntegration> VisualSceneIntegrationRef;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class NodeIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement *_pMeta;

    NodeUnrecPtr      _pNode;
    TransformUnrecPtr _pTransform;

    bool handleNode     (daeElementRef pElem);
    bool handleTranslate(daeElementRef pElem);
    bool handleRotate   (daeElementRef pElem);
    bool handleScale    (daeElementRef pElem);
    bool handleMatrix   (daeElementRef pElem);
    bool handleInstance (daeElementRef pElem);

  public:

    NodeIntegration(void);
    ~NodeIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    Node *getNode(void);

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<NodeIntegration> NodeIntegrationRef;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class InstanceIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    NodeUnrecPtr _pNode;
    UInt32       _uiCount;

  public:

    InstanceIntegration(void);
    ~InstanceIntegration(void);

    NodeTransitPtr getInstance(void);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class NodeInstanceIntegration : public InstanceIntegration
{
  protected:

    typedef InstanceIntegration                               Inherited;

    static daeMetaElement *_pMeta;
   
  public:

    NodeInstanceIntegration(void);
    ~NodeInstanceIntegration(void);

    static daeElementRef   create         (daeInt bytes);
    static daeMetaElement *registerElement(void        );

    virtual void fromCOLLADA(void);
};

typedef daeSmartRef<NodeInstanceIntegration> NodeInstanceIntegrationRef;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class GeometryIntegration : public ColladaIntegrationBase
{
  protected:

    friend class GeometryInstanceIntegration;

    typedef ColladaIntegrationBase Inherited;


    typedef std::pair  <GeoIntegralPropertyUnrecPtr,
                        GeoVectorPropertyUnrecPtr  >           PropIndexPair;
    
    typedef std::map   <std::string,  
                        PropIndexPair              >           PropIndexMap;
    typedef std::map   <std::string,  
                        PropIndexPair              >::iterator PropIndexMapIt;



    struct GeometryInfo
    {
        GeometryUnrecPtr  pGeo;
        PropIndexMap     _mPropIndexMap;
    };

  
    typedef std::vector<             GeometryInfo *>            GeoStore; 

    typedef std::map   <std::string, GeoStore      >            MatGeoMap;

    typedef std::map   <std::string, GeometryInfo *>            GeoMap;
    typedef std::map   <std::string, GeometryInfo *>::iterator  GeoMapIt;

    typedef std::vector<GeoUInt32Property         *>            PropVec;


    static daeMetaElement *_pMeta;

           MatGeoMap       _mGeosByMat;
           GeoMap          _mGeosMap;



    void   setupGeometry         (xsNCName                    szMatName,
                                  domInputLocal_Array        &aVertexInput,
                                  domInputLocalOffset_Array  &aInput,
                                  GeoUInt32PropertyUnrecPtr  &pLengthsOut,
                                  GeoUInt8PropertyUnrecPtr   &pTypesOut,
                                  PropVec                    &pPropVecOut );


    void   handlePolygon         (      domInputLocal_Array &aVertexInput,
                                        domPolygonsRef      &pPoly       );
    void   handlePolygonList     (      domInputLocal_Array &aVertexInput,
                                        domPolylistRef      &pPoly       );
    void   handleTriangles       (      domInputLocal_Array &aVertexInput,
                                        domTrianglesRef     &pTriangles  );
    void   handleTristrips       (      domInputLocal_Array &aVertexInput,
                                        domTristripsRef     &pTristrips  );
    void   handleTrifans         (      domInputLocal_Array &aVertexInput,
                                        domTrifansRef       &pTrifans    );
    void   handleLines           (      domInputLocal_Array &aVertexInput,
                                        domLinesRef         &pLines      );
    void   handleLinestrips      (      domInputLocal_Array &aVertexInput,
                                        domLinestripsRef    &pLinestrips );

    UInt32 SemanticToPropGeoIndex(const Char8          *szSemantic,
                                        bool            bVertexAsPos = false);

    GeoVectorProperty *fillVecProp(UInt32          uiPropIdx,
                                   daeURI          oSource   );

  public:

    typedef MatGeoMap::iterator MatGeoMapIt;

    GeometryIntegration(void);
    ~GeometryIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

	virtual void fromCOLLADA(void);

    MatGeoMapIt beginGeo(void);
    MatGeoMapIt endGeo  (void);
};

typedef daeSmartRef<GeometryIntegration> GeometryIntegrationRef;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class GeometryInstanceIntegration : public InstanceIntegration
{
  protected:

    typedef InstanceIntegration                               Inherited;

    typedef std::map<std::string, ChunkMaterial *>           MaterialMap;
    typedef std::map<std::string, ChunkMaterial *>::iterator MaterialMapIt;

    typedef std::map<std::string, 
                     std::vector<UInt32>         >           TexBindingsMap;

    static daeMetaElement *_pMeta;
   
           MaterialMap     _mMatMap;
           TexBindingsMap  _mTexBindingsMap;

    void updateGeoTexBindings(GeometryIntegration::GeometryInfo *pGeoInfo);

  public:

    GeometryInstanceIntegration(void);
    ~GeometryInstanceIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<GeometryInstanceIntegration> 
    GeometryInstanceIntegrationRef;



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class SourceIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement *_pMeta;
    
    GeoVec3fPropertyUnrecPtr    _pVec3fProp;
    GeoPnt3fPropertyUnrecPtr    _pPnt3fProp;
    GeoVec2fPropertyUnrecPtr    _pVec2fProp;

  public:

    SourceIntegration(void);
    ~SourceIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

	virtual void fromCOLLADA(void);

    GeoVec3fProperty *getAsVec3fProp(void);
    GeoPnt3fProperty *getAsPnt3fProp(void);
    GeoVec2fProperty *getAsVec2fProp(void);

};

typedef daeSmartRef<SourceIntegration> SourceIntegrationRef;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class EffectIntegration : public ColladaIntegrationBase
{
  protected:

    typedef domCommon_color_or_texture_type::domColor   DomColor;
    typedef domCommon_color_or_texture_type::domTexture DomTexture;
    typedef domCommon_float_or_param_type               DomFloat;

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement        *_pMeta;
           ChunkMaterialUnrecPtr  _pMaterial;
    
           std::vector<std::string>              _vTexCoordMapping;
           std::map   <std::string, 
                       domFx_surface_common   *> _mSurfaceMap;
           std::map   <std::string, 
                       domFx_sampler2D_common *> _mSamplerMap;

    void handleSimpleColor  (DomColor          *pDiffuse,
                             DomColor          *pAmbient,
                             DomColor          *pSpecular,
                             DomColor          *pEmission,
                             Real32             fShininess,
                             Real32             fTransparency);

    template<class T>
    void setupSimpleColorAndTex    (T           pTechT,
                                    DomFloat   *pShininess   = NULL,
                                    DomColor   *pSpecularCol = NULL,
                                    DomTexture *pSpecularTex = NULL);

    template<class T>
    void setupSimpleSpecColorAndTex(T pTechT);

    void handleCommonProfile(domProfile_COMMON *pCommon);
    void handleGLSLProfile  (domProfile_GLSL   *pGLSL  );
    void handleCGProfile    (domProfile_CG     *pCG    );

    void fillElements(domCommon_color_or_texture_type             *pIn,
                      domCommon_color_or_texture_type::domColor   *&pColOut,
                      domCommon_color_or_texture_type::domTexture *&pTexOut);


  public:

    EffectIntegration(void);
    ~EffectIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

	virtual void fromCOLLADA(void);

    ChunkMaterial        *getMaterial  (void             );
    UInt32                getTexBinding(std::string szRef);

    domFx_surface_common *getSurface   (std::string szRef);
};

typedef daeSmartRef<EffectIntegration> EffectIntegrationRef;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class ImageIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement *_pMeta;

    ImageUnrecPtr          _pImage;

  public:

    ImageIntegration(void);
    ~ImageIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    Image *getImage(void);

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<ImageIntegration> ImageIntegrationRef;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class Sampler2DIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement           *_pMeta;

    static EffectIntegration       *_pEffectInt;

           TextureObjChunkUnrecPtr  _pTexObj;

  public:

    Sampler2DIntegration(void);
    ~Sampler2DIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    TextureObjChunk *getTexObj(void);

    static void setEffectIntegration(EffectIntegration *pInt);

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<Sampler2DIntegration> Sampler2DIntegrationRef;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class SurfaceIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement   *_pMeta;

    TextureObjChunkUnrecPtr  _pTexObj;

  public:

    SurfaceIntegration(void);
    ~SurfaceIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    TextureObjChunk *getTexObj(void);

	virtual void fromCOLLADA(void);
};

typedef daeSmartRef<SurfaceIntegration> SurfaceIntegrationRef;


void initColladaIntegration(void);

OSG_END_NAMESPACE

#endif /* OSG_WITH_COLLADA */


#endif /* _OSGCOLLADAINTEGRATION_H_ */
