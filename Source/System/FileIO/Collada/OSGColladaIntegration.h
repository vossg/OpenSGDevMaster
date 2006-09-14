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

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"

#include "OSGNode.h"
#include "OSGChunkMaterial.h"

#include "OSGGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTransform.h"

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

    NodePtr _pScene;

  public:

    VisualSceneIntegration(void);
    ~VisualSceneIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    NodePtr getScene(void);

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

    NodePtr      _pNode;
    TransformPtr _pTransform;

    bool handleNode     (daeElementRef pElem);
    bool handleTranslate(daeElementRef pElem);
    bool handleRotate   (daeElementRef pElem);
    bool handleScale    (daeElementRef pElem);
    bool handleInstance (daeElementRef pElem);

  public:

    NodeIntegration(void);
    ~NodeIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

    NodePtr getNode(void);

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

    NodePtr _pNode;
    UInt32  _uiCount;

  public:

    InstanceIntegration(void);
    ~InstanceIntegration(void);

    NodePtr getInstance(void);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpFoundationLoader
 */

class GeometryInstanceIntegration : public InstanceIntegration
{
  protected:

    typedef InstanceIntegration                               Inherited;

    typedef std::map<std::string, ChunkMaterialPtr>           MaterialMap;
    typedef std::map<std::string, ChunkMaterialPtr>::iterator MaterialMapIt;

    static daeMetaElement *_pMeta;
   
           MaterialMap     _mMatMap;

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

class GeometryIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

  
    typedef std::vector<             GeometryPtr>           GeoStore;

    typedef std::map   <std::string, GeoStore   >           MatGeoMap;

    typedef std::map   <std::string, GeometryPtr>           GeoMap;
    typedef std::map   <std::string, GeometryPtr>::iterator GeoMapIt;

    typedef std::vector<GeoUInt32PropertyPtr    >           PropVec;


    static daeMetaElement *_pMeta;

           MatGeoMap       _mGeosByMat;
           GeoMap          _mGeosMap;

    void   setupGeometry         (xsNCName                    szMatName,
                                  domInputLocal_Array        &aVertexInput,
                                  domInputLocalOffset_Array  &aInput,
                                  GeoUInt32PropertyPtr       &pLengthsOut,
                                  GeoUInt8PropertyPtr        &pTypesOut,
                                  PropVec                    &pPropVecOut );


    void   handlePolygon         (      domInputLocal_Array &aVertexInput,
                                        domPolygonsRef      &pPoly       );
    void   handlePolygonList     (      domInputLocal_Array &aVertexInput,
                                        domPolylistRef      &pPoly       );

    UInt32 SemanticToPropGeoIndex(const Char8          *szSemantic,
                                        bool            bVertexAsPos = false);

    void   fillVecProp           (      GeometryPtrArg  pGeo,
                                        UInt32          uiPropIdx,
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

class SourceIntegration : public ColladaIntegrationBase
{
  protected:

    typedef ColladaIntegrationBase Inherited;

    static daeMetaElement *_pMeta;
    
    GeoVec3fPropertyPtr    _pVec3fProp;
    GeoPnt3fPropertyPtr    _pPnt3fProp;

  public:

    SourceIntegration(void);
    ~SourceIntegration(void);

    static daeElementRef   create         (daeInt bytes);
	static daeMetaElement *registerElement(void        );

	virtual void fromCOLLADA(void);

    GeoVec3fPropertyPtr getAsVec3fProp(void);
    GeoPnt3fPropertyPtr getAsPnt3fProp(void);

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

    struct TextureHelper
    {
    };

    static daeMetaElement   *_pMeta;
           ChunkMaterialPtr  _pMaterial;
 
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

    ChunkMaterialPtr getMaterial(void);
};

typedef daeSmartRef<EffectIntegration> EffectIntegrationRef;

void initColladaIntegration(void);

OSG_END_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define OSGCOLLADAINTEGRATION_HEADER_CVSID "@(#)$Id$"

#endif

#endif /* OSG_WITH_COLLADA */


#endif /* _OSGCOLLADAINTEGRATION_H_ */
