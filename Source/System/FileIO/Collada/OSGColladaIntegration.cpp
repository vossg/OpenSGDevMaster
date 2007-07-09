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

/*! \file OSgColladaIntegration.cpp
    \ingroup GrpFoundationLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGBaseTypes.h"

#include <iostream>

#include "OSGColladaIntegration.h"

#include "OSGGroup.h"
#include "OSGMaterialGroup.h"
#include "OSGMaterialChunk.h"
#include "OSGImageFileHandler.h"
#include "OSGTextureEnvChunk.h"

#include "dom/domVisual_scene.h"
#include "dom/domNode.h"
#include "dom/domGeometry.h"
#include "dom/domInstance_geometry.h"
#include "dom/domMesh.h"
#include "dom/domMaterial.h"
#include "dom/domEffect.h"
#include "dom/domProfile_GLSL.h"
#include "dom/domProfile_CG.h"
#include "dom/domImage.h"

#include "dae/daeSmartRef.h"
#include "dae/daeMetaElementAttribute.h"

OSG_USING_NAMESPACE

daeMetaElement *ColladaIntegrationBase::_pMeta = NULL;

void ColladaIntegrationBase::createFrom(daeElementRef pElement)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::createFrom %s\n", 
            pElement->getTypeName());
#endif

	_pElement = pElement;
}

void ColladaIntegrationBase::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif
}

void ColladaIntegrationBase::fromCOLLADAPostProcess(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::fromColladaPostproc\n");
#endif
}

void ColladaIntegrationBase::createTo(void *userData)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::createTo\n");
#endif
}

void ColladaIntegrationBase::toCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::toCollada\n");
#endif
}

void ColladaIntegrationBase::toCOLLADAPostProcess(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::toColladaPostProc\n");
#endif
}

daeElementRef ColladaIntegrationBase::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::create\n");
#endif

	ColladaIntegrationBaseRef ref = new(bytes) ColladaIntegrationBase;

	return ref;
}

daeMetaElement *ColladaIntegrationBase::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ColladaIntegrationBase::regElem\n");
#endif

    if(_pMeta != NULL) 
        return _pMeta;

    // The one seen

    _pMeta = new daeMetaElement;

    _pMeta->setName("ColladaIntegrationBase");

	_pMeta->registerClass(ColladaIntegrationBase::create, &_pMeta);

	_pMeta->setElementSize(sizeof(ColladaIntegrationBase));

	_pMeta->validate();

	return _pMeta;
}
	
ColladaIntegrationBase::ColladaIntegrationBase(void) :
    _pElement(NULL)
{
}

ColladaIntegrationBase::~ColladaIntegrationBase(void)
{
}


//---------------------------------------------------------------------------
//  VisualSceneIntegration
//---------------------------------------------------------------------------


daeMetaElement *VisualSceneIntegration::_pMeta = NULL;

VisualSceneIntegration::VisualSceneIntegration(void) :
     Inherited(      ),
    _pScene   (NullFC)
{
}

VisualSceneIntegration::~VisualSceneIntegration(void)
{
    OSG::subRef(_pScene);
}

daeElementRef VisualSceneIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "VisualSceneIntegration::create\n");
#endif

	VisualSceneIntegrationRef ref = new(bytes) VisualSceneIntegration;

	return ref;
}

daeMetaElement *VisualSceneIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "VisualSceneIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    

    _pMeta = new daeMetaElement;

    _pMeta->setName("VisualSceneIntegration");
	_pMeta->registerClass(VisualSceneIntegration::create, &_pMeta);

	domVisual_scene::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(VisualSceneIntegration));
	_pMeta->validate();

    return _pMeta;
}

NodePtr VisualSceneIntegration::getScene(void)
{
    return _pScene;
}

void VisualSceneIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "VisualSceneIntegration::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif

    domVisual_scene *pDomScene = 
        dynamic_cast<domVisual_scene *>(_pElement);

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got dom scene %p\n", pDomScene);
#endif

    domNode_Array &aChildren = pDomScene->getNode_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got %d children\n", aChildren.getCount());
#endif

    _pScene = Node::create();

    _pScene->setCore(Group::create());

    for(UInt32 i = 0; i < aChildren.getCount(); ++i)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "gotNode %p int %p\n",
                &*(aChildren[i]),
                aChildren[i]->getIntObject());
#endif

        NodeIntegration *pNodeInt = 
            dynamic_cast<NodeIntegration *>(aChildren[i]->getIntObject());
        
        pNodeInt->fromCOLLADAChecked();
        
        if(pNodeInt != NULL)
        {
            _pScene->addChild(pNodeInt->getNode());
        }
    }
}


//---------------------------------------------------------------------------
//  NodeIntegration
//---------------------------------------------------------------------------

daeMetaElement *NodeIntegration::_pMeta = NULL;


bool NodeIntegration::handleNode(daeElementRef pElem)
{
    domNode *pNode = dynamic_cast<domNode *>(static_cast<daeElement *>(pElem));

    if(pNode == NULL)
        return false;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Handle Node\n");
#endif

    NodeIntegration *pNodeInt = 
        dynamic_cast<NodeIntegration *>(pNode->getIntObject());

    if(pNodeInt != NULL)
    {
        pNodeInt->fromCOLLADAChecked();
        
        _pNode->addChild(pNodeInt->getNode());
    }

    return true;
}

bool NodeIntegration::handleTranslate(daeElementRef pElem)
{
    domTranslate *pTrans = 
        dynamic_cast<domTranslate *>(static_cast<daeElement *>(pElem));

    if(pTrans == NULL)
        return false;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Handle Trans\n");
#endif

    if(_pTransform == NullFC)
    {
        _pTransform = Transform::create();

        OSG::addRef(_pTransform);

        _pNode->setCore(_pTransform);
    }

    Matrix mTr;

    mTr.setTranslate(pTrans->getValue()[0],
                     pTrans->getValue()[1],
                     pTrans->getValue()[2]);


    _pTransform->editMatrix().mult(mTr);

    return true;
}

bool NodeIntegration::handleRotate(daeElementRef pElem)
{
    domRotate *pRot = 
        dynamic_cast<domRotate *>(static_cast<daeElement *>(pElem));

    if(pRot == NULL)
        return false;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Handle Rot\n");
#endif

    if(_pTransform == NullFC)
    {
        _pTransform = Transform::create();

        OSG::addRef(_pTransform);

        _pNode->setCore(_pTransform);
    }

    Matrix     mTr;
    Quaternion qR;

    qR.setValueAsAxisDeg(pRot->getValue()[0],
                         pRot->getValue()[1],
                         pRot->getValue()[2],
                         pRot->getValue()[3]);


    mTr.setRotate(qR);

    _pTransform->editMatrix().mult(mTr);

    return true;
}

bool NodeIntegration::handleScale(daeElementRef pElem)
{
    domScale *pScale = 
        dynamic_cast<domScale *>(static_cast<daeElement *>(pElem));

    if(pScale == NULL)
        return false;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Handle Scale\n");
#endif

    if(_pTransform == NullFC)
    {
        _pTransform = Transform::create();

        OSG::addRef(_pTransform);

        _pNode->setCore(_pTransform);
    }

    Matrix mTr;

    mTr.setScale(pScale->getValue()[0],
                 pScale->getValue()[1],
                 pScale->getValue()[2]);


    _pTransform->editMatrix().mult(mTr);

    return true;
}


bool NodeIntegration::handleInstance(daeElementRef pElem)
{
    InstanceIntegration *pInt = NULL;

    domInstance_geometry *pInstGeo = 
        dynamic_cast<domInstance_geometry *>(static_cast<daeElement *>(pElem));

    if(pInstGeo != NULL)
    {
        pInt = dynamic_cast<InstanceIntegration *>(pInstGeo->getIntObject());
    }

    domInstance_node *pInstNode = 
        dynamic_cast<domInstance_node *>(static_cast<daeElement *>(pElem));

    if(pInstNode != NULL)
    {
        pInt = dynamic_cast<InstanceIntegration *>(pInstGeo->getIntObject());
    }

    if(pInt == NULL)
        return false;

    pInt->fromCOLLADAChecked();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Handle Inst\n");
#endif

    _pNode->addChild(pInt->getInstance());

    return true;
}

NodeIntegration::NodeIntegration(void) :
     Inherited (      ),
    _pNode     (NullFC),
    _pTransform(NullFC)
{
}

NodeIntegration::~NodeIntegration(void)
{
    OSG::subRef(_pNode     );
    OSG::subRef(_pTransform);
}

daeElementRef NodeIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "NodeIntegration::create\n");
#endif

	NodeIntegrationRef ref = new(bytes) NodeIntegration;

	return ref;
}

daeMetaElement *NodeIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "NodeIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    
    _pMeta = new daeMetaElement;

    _pMeta->setName("NodeIntegration");
	_pMeta->registerClass(NodeIntegration::create, &_pMeta);

	domNode::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(NodeIntegration));
	_pMeta->validate();

    return _pMeta;
}

NodePtr NodeIntegration::getNode(void)
{
    return _pNode;
}

void NodeIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "NodeIntegration::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif

    _pNode = Node::create();

    OSG::addRef(_pNode);

    daeMetaElement *pMeta = _pElement->getMeta();

	if(pMeta->getContents() != NULL) 
    {
		daeElementRefArray *era = 
            (daeElementRefArray*) pMeta->getContents()->getWritableMemory(
                _pElement);

		int elemCnt = (int) era->getCount();

		for(int i = 0; i < elemCnt; i++) 
        {
			daeElementRef elem = (daeElementRef) era->get(i);

#ifdef OSG_DEBUG_PRINT
			if(elem != NULL) 
            {
                fprintf(stderr, "CT %d %p %s\n",
                        i,
                        &*(elem),
                        elem->getTypeName());
			}
#endif

            if(handleNode(elem) == true)
                continue;

            if(handleTranslate(elem) == true)
                continue;

            if(handleRotate(elem) == true)
                continue;

            if(handleScale(elem) == true)
                continue;

            if(handleInstance(elem) == true)
                continue;
		}
	}

    if(_pNode->getCore() == NullFC)
        _pNode->setCore(Group::create());
}


//---------------------------------------------------------------------------
//  InstanceIntegration
//---------------------------------------------------------------------------

InstanceIntegration::InstanceIntegration(void) :
    Inherited(      ),
   _pNode    (NullFC),
   _uiCount  (     0)
{
}

InstanceIntegration::~InstanceIntegration(void)
{
    OSG::subRef(_pNode);
}

NodePtr InstanceIntegration::getInstance(void)
{
    if(_pNode == NullFC)
        return NullFC;

    if(_uiCount == 0)
    {
        ++_uiCount;

        return _pNode;
    }
    else
    {
        ++_uiCount;

        return cloneTree(_pNode);
    }
}


//---------------------------------------------------------------------------
//  GeometryInstanceIntegration
//---------------------------------------------------------------------------

daeMetaElement *GeometryInstanceIntegration::_pMeta = NULL;

GeometryInstanceIntegration::GeometryInstanceIntegration(void) :
     Inherited      (),
    _mMatMap        (),
    _mTexBindingsMap()
{
}

GeometryInstanceIntegration::~GeometryInstanceIntegration(void)
{
}

daeElementRef GeometryInstanceIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryInstanceIntegration::create %p\n", (void *)bytes);
#endif

	GeometryInstanceIntegrationRef ref = 
        new(bytes) GeometryInstanceIntegration;

	return ref;
}

daeMetaElement *GeometryInstanceIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryInstanceIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    

    _pMeta = new daeMetaElement;

    _pMeta->setName("GeometryInstanceIntegration");
	_pMeta->registerClass(GeometryInstanceIntegration::create, &_pMeta);

	domInstance_geometry::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(GeometryInstanceIntegration));
	_pMeta->validate();

    return _pMeta;
}

void GeometryInstanceIntegration::updateGeoTexBindings(
    GeometryIntegration::GeometryInfo *pGeoInfo)
{
    TexBindingsMap::iterator texIt  = _mTexBindingsMap.begin();
    TexBindingsMap::iterator texEnd = _mTexBindingsMap.end  ();

    while(texIt != texEnd)
    {
        for(UInt32 i = 0; i < texIt->second.size(); ++i)
        {
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "Bind %s to %d\n", 
                    texIt->first.c_str(),
                    texIt->second[i]);
#endif
            
            GeometryIntegration::PropIndexPair pPropIdxPair(NullFC, NullFC);
            
            GeometryIntegration::PropIndexMapIt propIt = 
                pGeoInfo->_mPropIndexMap.find(texIt->first);

            if(propIt != pGeoInfo->_mPropIndexMap.end())
            {
                pPropIdxPair = propIt->second;
            }
            
            if(pPropIdxPair.first != NullFC && pPropIdxPair.second != NullFC)
            {
#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Got %p %p for %d\n",
                        pPropIdxPair.first,
                        pPropIdxPair.second,
                        texIt->second[i]);
                
                fprintf(stderr, "Idx : %s\n", 
                        pPropIdxPair.first->getType().getCName());
                fprintf(stderr, "Val : %s\n", 
                        pPropIdxPair.second->getType().getCName());
#endif                
                
                pGeoInfo->pGeo->setProperty(
                    pPropIdxPair.second, 
                    Geometry::TexCoordsIndex + texIt->second[i]);
                
                pGeoInfo->pGeo->setIndex   (
                    pPropIdxPair.first, 
                    Geometry::TexCoordsIndex + texIt->second[i]);
            }
        }
        
        ++texIt;
    }
    
}

void GeometryInstanceIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryInstanceIntegration::fromCollada for %s %p %p\n", 
            _pElement->getTypeName(),
            this,
            &(*_pElement));
#endif

    domInstance_geometry *pInstGeo = 
        dynamic_cast<domInstance_geometry *>(_pElement);

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got dom geometry %p\n", pInstGeo);
#endif

    if(pInstGeo == NULL)
        return;

    daeURI oUri = pInstGeo->getUrl();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "uri %s %d\n", oUri.getURI(), oUri.getState());
#endif
            
    daeElementRef pElem = oUri.getElement();
                
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "elem %p %s %s\n", 
            &*pElem, 
            pElem->getTypeName(),
            pElem->getElementName());
#endif
    
    domGeometry         *pGeo    = dynamic_cast<domGeometry         *>(
        static_cast<daeElement *>(pElem));

    GeometryIntegration *pGeoInt = dynamic_cast<GeometryIntegration *>(
        pGeo->getIntObject());

    if(pGeo == NULL)
        return;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got geo %p %p\n", pGeo, pGeoInt);
#endif

    pGeoInt->fromCOLLADAChecked();

    const domBind_materialRef pMatBindings = pInstGeo->getBind_material();

    if(pMatBindings == NULL)
    {
        fprintf(stderr, "No material\n");
        return;
    }

    _pNode = Node::create();

    _pNode->setCore(Group::create());

    
    domTechnique_Array &aTechnique = pMatBindings->getTechnique_array(); 

    bool bMatHandled = false;
        
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Num Tech %d\n", aTechnique.getCount());
#endif

    if(aTechnique.getCount() != 0)
    {
        for(UInt32 i = 0; i < aTechnique.getCount(); ++i)
        {
            daeElementRefArray &aTechniqueCont = aTechnique[i]->getContents();
            
            for(UInt32 j = 0; j < aTechniqueCont.getCount(); ++j)
            {
                daeElement *pElem = aTechniqueCont[i];
                
#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "elem %p %s %s\n", 
                        &*pElem, 
                        pElem->getTypeName(),
                        pElem->getElementName());
#endif
            }
        }
    }


    if(bMatHandled == false)
    {
        domBind_material::domTechnique_commonRef pTechnique = 
            pMatBindings->getTechnique_common();

        domInstance_material_Array &aInstMat = 
                pTechnique->getInstance_material_array();

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Got %d comm tech mat inst\n", aInstMat.getCount());
#endif

        for(UInt32 i = 0; i < aInstMat.getCount(); ++i)
        {
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "%s %s\n", 
                    aInstMat[i]->getSymbol(),
                    aInstMat[i]->getTarget().getURI());
#endif

            daeElementRef pElem = aInstMat[i]->getTarget().getElement();

            domMaterial *pMat = 
                dynamic_cast<domMaterial *>(
                    static_cast<daeElement *>(pElem));

            if(pMat == NULL)
                continue;

            const domInstance_effectRef pEffect =
                pMat->getInstance_effect();

            xsAnyURI oEffectURI = pEffect->getUrl();
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "uri %s %d\n", 
                    oEffectURI.getURI(), 
                    oEffectURI.getState());
#endif

            daeElementRef pEffectElem = oEffectURI.getElement();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "elem %p %s %s\n", 
                    &*pEffectElem, 
                    pEffectElem->getTypeName(),
                    pEffectElem->getElementName());
#endif

            EffectIntegration *pEffectInt = 
                dynamic_cast<EffectIntegration *>(pEffectElem->getIntObject());

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "Got Eff Integration %p\n",
                    pEffectInt);
#endif

            pEffectInt->fromCOLLADAChecked();

            std::string effectKey = aInstMat[i]->getSymbol();

            _mMatMap[effectKey] = pEffectInt->getMaterial();


#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "%d bonds\n", 
                    aInstMat[i]->getBind_array().getCount());
#endif

            for(UInt32 j = 0; j < aInstMat[i]->getBind_array().getCount(); ++j)
            {
                std::string szTarget = 
                    aInstMat[i]->getBind_array()[j]->getTarget();

                if(aInstMat[i]->getBind_array()[j]->getTarget()[0] == '#')
                {
                    szTarget.erase(0, 1);
                }

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Bind : %s %s\n",
                        aInstMat[i]->getBind_array()[j]->getSemantic(),
                        szTarget.c_str());
#endif

                UInt32 uiTexIdx = pEffectInt->getTexBinding(
                    aInstMat[i]->getBind_array()[j]->getSemantic());

                _mTexBindingsMap[szTarget].push_back(uiTexIdx);

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Bound %s -> %d\n",
                        szTarget.c_str(),
                        uiTexIdx);
#endif                       
            }

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "%d vertex bonds\n", 
                    aInstMat[i]->getBind_vertex_input_array().getCount());
#endif

            for(UInt32 j = 0; 
                      j < aInstMat[i]->getBind_vertex_input_array().getCount();
                    ++j)
            {
                std::string szTarget = 
                    aInstMat[i]->
                        getBind_vertex_input_array()[j]->getInput_semantic();

                if(szTarget[0] == '#')
                {
                    szTarget.erase(0, 1);
                }

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Bind : %s %s\n",
                        aInstMat[i]->
                            getBind_vertex_input_array()[j]->getSemantic(),
                        szTarget.c_str());
#endif

                UInt32 uiTexIdx = pEffectInt->getTexBinding(
                    aInstMat[i]->
                        getBind_vertex_input_array()[j]->getSemantic());

                if(uiTexIdx != 0xFFFF)
                {
                    _mTexBindingsMap[szTarget].push_back(uiTexIdx);
                }

#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Bound %s -> %d\n",
                        szTarget.c_str(),
                        uiTexIdx);
#endif                        
            }
        }
    }
    

    GeometryIntegration::MatGeoMapIt geoIt  = pGeoInt->beginGeo();
    GeometryIntegration::MatGeoMapIt geoEnd = pGeoInt->endGeo  ();

    while(geoIt != geoEnd)
    {
        for(UInt32 i = 0; i < geoIt->second.size(); ++i)
        {
            MaterialGroupPtr pMatGroup     = MaterialGroup::create();
            NodePtr          pMatGroupNode = Node         ::create();
            
            NodePtr          pGeoNode      = Node         ::create();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "%s\n", geoIt->first.c_str());
#endif
            
            MaterialMapIt matIt = _mMatMap.find( geoIt->first);

            ChunkMaterialPtr pApp = NullFC;
            
            if(matIt != _mMatMap.end())
            {
                pApp = matIt->second;
            }
           
            updateGeoTexBindings(geoIt->second[i]);

            pGeoNode     ->setCore    (geoIt->second[i]->pGeo);

            pMatGroup    ->setMaterial(pApp            );
            pMatGroupNode->setCore    (pMatGroup       );

            pMatGroupNode->addChild   (pGeoNode        );
            
            _pNode       ->addChild   (pMatGroupNode   );
        }
        
        ++geoIt;
    }
}


//---------------------------------------------------------------------------
//  GeometryIntegration
//---------------------------------------------------------------------------

daeMetaElement *GeometryIntegration::_pMeta = NULL;

void GeometryIntegration::setupGeometry(
    xsNCName                   szMatName,
    domInputLocal_Array       &aVertexInput,
    domInputLocalOffset_Array &aInput,
    GeoUInt32PropertyPtr      &pLengthsOut,
    GeoUInt8PropertyPtr       &pTypesOut,
    PropVec                   &vPropVecOut  )
{
    daeURI      oSource;

    std::string szGeoRef;
    std::string szMatRef;

    pLengthsOut = NullFC;
    pTypesOut   = NullFC;

    szGeoRef += szMatName;
    szMatRef  = szMatName;

    for(UInt32 i = 0; i < aInput.getCount(); ++i)
    {
        oSource = aInput[i]->getSource();

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "%u %s %s %s\n", 
                aInput[i]->getOffset(), 
                aInput[i]->getSemantic(),
                oSource.getID(),
                oSource.getURI());
#endif

        szGeoRef += oSource.getID();
    }

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeoRef %s\n", szGeoRef.c_str());
#endif

    GeoMapIt      iCurrGeo = _mGeosMap.find(szGeoRef);

    GeometryInfo *pGeoInfo    = NULL;

    if(iCurrGeo == _mGeosMap.end())
    {
        pGeoInfo = new GeometryInfo;

        pGeoInfo->pGeo = Geometry::create();

        _mGeosMap  [szGeoRef] = pGeoInfo;
        _mGeosByMat[szMatRef].push_back(pGeoInfo);

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "FOOO %d\n", aInput.getCount());
#endif

        for(UInt32 i = 0; i < aInput.getCount(); ++i)
        {
            UInt32 uiPropIdx = 
                SemanticToPropGeoIndex(aInput[i]->getSemantic());

            GeoUInt32PropertyPtr pProp  = GeoUInt32Property::create();
            GeoVectorPropertyPtr pVProp = NullFC;

            if(uiPropIdx == 0xFFFE)
            {
                for(UInt32 j = 0; j < aVertexInput.getCount(); ++j)
                {
                    UInt32 uiVPropIdx = 
                        SemanticToPropGeoIndex(aVertexInput[j]->getSemantic());
                    
                    pGeoInfo->pGeo->setIndex(pProp,
                                             uiVPropIdx);
                    
#ifdef OSG_DEBUG_PRINT
                    fprintf(stderr, "added Vprop %s %d %p\n", 
                            aVertexInput[j]->getSemantic(),
                            uiVPropIdx, 
                            &(*pProp));
#endif
                    
                    pVProp = fillVecProp(uiVPropIdx, 
                                         aVertexInput[j]->getSource());


                    pGeoInfo->pGeo->setProperty(pVProp, uiVPropIdx);
                }
            }
            else
            {
                if(uiPropIdx != Geometry::TexCoordsIndex)
                {
                    pGeoInfo->pGeo->setIndex(pProp,
                                             uiPropIdx);
            
#ifdef OSG_DEBUG_PRINT
                    fprintf(stderr, "added prop %s %d %p\n", 
                            aInput[i]->getSemantic(),
                            uiPropIdx, 
                            &(*pProp));
#endif 
                   
                    pVProp = fillVecProp(uiPropIdx, 
                                         aInput[i]->getSource());

                    pGeoInfo->pGeo->setProperty(pVProp, uiPropIdx);
                }
                else
                {
#ifdef OSG_DEBUG_PRINT
                    fprintf(stderr, "added tex prop %s %s %d %p\n", 
                            aInput[i]->getSource().getID(),
                            aInput[i]->getSemantic(),
                            uiPropIdx, 
                            &(*pProp));
#endif

                    PropIndexMapIt propIt = pGeoInfo->_mPropIndexMap.find(
                        aInput[i]->getSource().getID());

                    pVProp = fillVecProp(uiPropIdx, 
                                         aInput[i]->getSource());

                    if(propIt == pGeoInfo->_mPropIndexMap.end())
                    {
                        PropIndexPair newPair;

                        newPair.first  = pProp;
                        newPair.second = pVProp;

                        pGeoInfo->_mPropIndexMap[
                            aInput[i]->getSource().getID()] = newPair;

                        pGeoInfo->_mPropIndexMap[
                            aInput[i]->getSemantic()] = newPair;

#ifdef OSG_DEBUG_PRINT
                        fprintf(stderr, "Store Prop/Index %s %s: \n",
                                aInput[i]->getSource().getID(),
                                aInput[i]->getSemantic());

                        fprintf(stderr, "    %p : %s\n",
                                newPair.first, 
                                newPair.first->getType().getCName());
                                
                        fprintf(stderr, "    %p : %s\n",
                                newPair.second, 
                                newPair.second->getType().getCName());
#endif                                
                    }
                    else
                    {
                        OSG::subRef(pProp);
                    }
                }
            }
        }
            
        pLengthsOut = GeoUInt32Property::create();
        pTypesOut   = GeoUInt8Property ::create();

        pGeoInfo->pGeo->setLengths(pLengthsOut);
        pGeoInfo->pGeo->setTypes  (pTypesOut  );
    }
    else
    {
        pGeoInfo = iCurrGeo->second;

        pLengthsOut = 
            static_cast<GeoUInt32PropertyPtr>(pGeoInfo->pGeo->getLengths());

        pTypesOut   = 
            static_cast<GeoUInt8PropertyPtr >(pGeoInfo->pGeo->getTypes  ());
    }

    for(UInt32 i = 0; i < aInput.getCount(); ++i)
    {
        if(vPropVecOut.size() <= aInput[i]->getOffset())
        {
            vPropVecOut.resize(aInput[i]->getOffset() + 1);
        }

        UInt32 uiPropIdx = SemanticToPropGeoIndex(aInput[i]->getSemantic(),
                                                 true);
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "%d %d %d %s %d %p\n", 
                i, 
                vPropVecOut.size(), 
                aInput[i]->getOffset(),
                aInput[i]->getSemantic(),
                uiPropIdx,
                pGeoInfo->pGeo->getIndex(uiPropIdx));
#endif

        if(uiPropIdx != Geometry::TexCoordsIndex)
        {
            vPropVecOut[aInput[i]->getOffset()] =
                static_cast<GeoUInt32PropertyPtr>(
                    pGeoInfo->pGeo->getIndex(uiPropIdx));
        }
        else
        {
            PropIndexMapIt propIt = pGeoInfo->_mPropIndexMap.find(
                aInput[i]->getSource().getID());

            if(propIt != pGeoInfo->_mPropIndexMap.end())
            {
                vPropVecOut[aInput[i]->getOffset()] =
                    static_cast<GeoUInt32PropertyPtr>(
                        propIt->second.first);
            }
        }
    }

#ifdef OSG_DEBUG_PRINT
    for(UInt32 i = 0; i < vPropVecOut.size(); i++)
    {
        fprintf(stderr, "%d : %p\n", i, &(*(vPropVecOut[i])));
    }
#endif
}

void GeometryIntegration::handlePolygon(domInputLocal_Array &aVertexInput,
                                        domPolygonsRef      &pPoly)
{
    domInputLocalOffset_Array &aInput   = pPoly->getInput_array();

    GeoUInt32PropertyPtr       pLengths = NullFC;
    GeoUInt8PropertyPtr        pTypes   = NullFC;

    PropVec                    aProps;

    setupGeometry(pPoly->getMaterial(),
                  aVertexInput,
                  aInput,
                  pLengths,
                  pTypes,
                  aProps);
    

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "P %s\n", pPoly->getMaterial());
#endif
    
    domP_Array &oPArray = pPoly->getP_array();

    UInt32 uiCurr   = 0;
    UInt32 uiLength = 0;

    for(UInt32 j = 0; j < oPArray.getCount(); j++)
    {
        domListOfUInts &oPList = oPArray[j]->getValue();
        
        for(UInt32 k = 0; k < oPList.getCount(); ++k)
        {
            aProps[uiCurr]->push_back(oPList[k]);
            
            uiCurr++;

            if(uiCurr == aProps.size())
            {
                uiCurr = 0;
                ++uiLength;
            }
        }

        pTypes  ->push_back(GL_POLYGON);
        pLengths->push_back(uiLength  );

        uiLength = 0;
    }
}


void GeometryIntegration::handlePolygonList(domInputLocal_Array &aVertexInput,
                                            domPolylistRef      &pPoly)
{
    domInputLocalOffset_Array &aInput   = pPoly->getInput_array();

    GeoUInt32PropertyPtr       pLengths = NullFC;
    GeoUInt8PropertyPtr        pTypes   = NullFC;

    PropVec                    aProps;

    setupGeometry(pPoly->getMaterial(),
                  aVertexInput,
                  aInput,
                  pLengths,
                  pTypes,
                  aProps);
            

    domListOfUInts &oPList = pPoly->getP     ()->getValue();
    domListOfUInts &oVList = pPoly->getVcount()->getValue();

    UInt32 uiCurrent  = 0;

    for(UInt32 i = 0; i < oVList.getCount(); ++i)
    {
        for(UInt32 j = 0; j < oVList[i]; ++j)
        {
            for(UInt32 k = 0; k < aProps.size(); ++k)
            {
                aProps[k]->push_back(oPList[uiCurrent]);
                
                ++uiCurrent;
            }

        }

        pTypes  ->push_back(GL_POLYGON);
        pLengths->push_back(oVList[i] );
    }

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "P %s\n", pPoly->getMaterial());
#endif
}

void GeometryIntegration::handleTriangles(domInputLocal_Array &aVertexInput,
                                          domTrianglesRef     &pTriangles  )
{
    domInputLocalOffset_Array &aInput   = pTriangles->getInput_array();

    GeoUInt32PropertyPtr       pLengths = NullFC;
    GeoUInt8PropertyPtr        pTypes   = NullFC;

    PropVec                    aProps;

    setupGeometry(pTriangles->getMaterial(),
                  aVertexInput,
                  aInput,
                  pLengths,
                  pTypes,
                  aProps);
            

    domListOfUInts &oPList   = pTriangles->getP()->getValue();
    UInt32          uiCurr   = 0;
    UInt32          uiLength = 0;

    for(UInt32 i = 0; i < oPList.getCount(); ++i)
    {
        aProps[uiCurr]->push_back(oPList[i]);
            
        uiCurr++;
        
        if(uiCurr == aProps.size())
        {
              uiCurr = 0;
            ++uiLength;
        }
    }

    pTypes  ->push_back(GL_TRIANGLES);
    pLengths->push_back(uiLength    );

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "P %s\n", pTriangles->getMaterial());
#endif
}

UInt32 GeometryIntegration::SemanticToPropGeoIndex(
    const char *szSemantic,
          bool  bVertexAsPos)
{
    UInt32 returnValue = 0xFFFF;

    std::string szSem = szSemantic;

    if(szSem == "VERTEX")
    {
        if(bVertexAsPos == true)
        {
            returnValue = Geometry::PositionsIndex;
        }
        else
        {
            returnValue = 0xFFFE;
        }
    }
    else if(szSem == "POSITION")
    {
        returnValue = Geometry::PositionsIndex;
    }
    else if(szSem == "NORMAL")
    {
        returnValue = Geometry::NormalsIndex;
    }
    else if(szSem == "TEXCOORD")
    {
        returnValue = Geometry::TexCoordsIndex;
    }

    return returnValue;
}

GeoVectorPropertyPtr GeometryIntegration::fillVecProp(UInt32         uiPropIdx,
                                                      daeURI         oSource )
{
    GeoVectorPropertyPtr returnValue = NullFC;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "uri %s %d\n", oSource.getURI(), oSource.getState());
#endif    

    daeElementRef pElem = oSource.getElement();
    
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "elem %p %s %s\n", 
            &*pElem, 
            pElem->getTypeName(),
            pElem->getElementName());
#endif

    domVertices *pVert = 
        dynamic_cast<domVertices *>(static_cast<daeElement *>(pElem));

    domSource   *pSource = 
        dynamic_cast<domSource *>(static_cast<daeElement *>(pElem));

    if(pVert != NULL)
    {
        domInputLocal_Array &aInput = pVert->getInput_array();

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Got vert %d\n", aInput.getCount());
#endif

        daeURI sourceDesc = aInput[0]->getSource();

        pElem = sourceDesc.getElement();

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "elem %p %s %s\n", 
                &*pElem, 
                pElem->getTypeName(),
                pElem->getElementName());
#endif

        pSource = 
            dynamic_cast<domSource *>(static_cast<daeElement *>(pElem));
    }
    
    if(pSource != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Got source\n");
#endif
        
        SourceIntegration *pSourceInt = 
            dynamic_cast<SourceIntegration *>(pSource->getIntObject());

        pSourceInt->fromCOLLADAChecked();

        if(uiPropIdx == Geometry::NormalsIndex)
        {
            returnValue = pSourceInt->getAsVec3fProp();

        }

        if(uiPropIdx == Geometry::PositionsIndex)
        {
            returnValue = pSourceInt->getAsPnt3fProp();
        }

        if(uiPropIdx == Geometry::TexCoordsIndex)
        {
            returnValue = pSourceInt->getAsVec2fProp();
        }
    }

    return returnValue;
}

GeometryIntegration::GeometryIntegration(void) :
     Inherited    (),
    _mGeosByMat   (),
    _mGeosMap     ()
{
}

GeometryIntegration::~GeometryIntegration(void)
{
    GeoMapIt geoIt  = _mGeosMap.begin();
    GeoMapIt geoEnd = _mGeosMap.end  ();

    while(geoIt != geoEnd)
    {
        delete geoIt->second;
        ++geoIt;
    }
}

daeElementRef GeometryIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryIntegration::create %p\n", (void *)bytes);
#endif

	GeometryIntegrationRef ref = 
        new(bytes) GeometryIntegration;

	return ref;
}

daeMetaElement *GeometryIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    

    _pMeta = new daeMetaElement;

    _pMeta->setName("GeometryIntegration");
	_pMeta->registerClass(GeometryIntegration::create, &_pMeta);

	domGeometry::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(GeometryIntegration));
	_pMeta->validate();

    return _pMeta;
}

void GeometryIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "GeometryIntegration::fromCollada for %s %p %p\n", 
            _pElement->getTypeName(),
            this,
            &(*_pElement));
#endif

    domGeometry *pGeo = dynamic_cast<domGeometry *>(_pElement);

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got dom geometry %p\n", pGeo);
#endif

    if(pGeo == NULL)
        return;

    domMeshRef pMesh = pGeo->getMesh();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got mesh %p\n", &(*pMesh));
#endif
   
    if(pMesh == NULL)
        return;

    domInputLocal_Array &oVertexInput = 
        pMesh->getVertices()->getInput_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got mesh vertex input %d\n",
            oVertexInput.getCount());

    for(UInt32 v = 0; 
               v < oVertexInput.getCount(); 
             ++v)
    {
        // if it is the same as the semantic passed in then yippie!   
        fprintf(stderr, "%s\n", 
                oVertexInput[v]->getSemantic() );
    }
#endif

    domPolygons_Array &aPolys = pMesh->getPolygons_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got %d polys\n", aPolys.getCount());
#endif

    for(UInt32 i = 0; i < aPolys.getCount(); ++i)
    {
        handlePolygon(oVertexInput, aPolys[i]);
    }

    domPolylist_Array &aPolyLists = pMesh->getPolylist_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got %d polylists\n", aPolyLists.getCount());
#endif

    for(UInt32 i = 0; i < aPolyLists.getCount(); ++i)
    {
        handlePolygonList(oVertexInput, aPolyLists[i]);
    }

    domTriangles_Array &aTriList = pMesh->getTriangles_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got %d tris\n", aTriList.getCount());
#endif

    for(UInt32 i = 0; i < aTriList.getCount(); ++i)
    {
        handleTriangles(oVertexInput, aTriList[i]);
    }

    
}


GeometryIntegration::MatGeoMapIt GeometryIntegration::beginGeo(void)
{
    return _mGeosByMat.begin();
}

GeometryIntegration::MatGeoMapIt GeometryIntegration::endGeo(void)
{
    return _mGeosByMat.end();
}

//---------------------------------------------------------------------------
//  SourceIntegration
//---------------------------------------------------------------------------

daeMetaElement *SourceIntegration::_pMeta = NULL;

SourceIntegration::SourceIntegration(void) :
     Inherited (      ),
    _pVec3fProp(NullFC),
    _pPnt3fProp(NullFC),
    _pVec2fProp(NullFC)
{
}

SourceIntegration::~SourceIntegration(void)
{
    OSG::subRef(_pVec3fProp);
    OSG::subRef(_pPnt3fProp);
    OSG::subRef(_pVec2fProp);
}

daeElementRef SourceIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SourceIntegration::create %p\n", (void *)bytes);
#endif

	SourceIntegrationRef ref = new(bytes) SourceIntegration;

	return ref;
}

daeMetaElement *SourceIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SourceIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    

    _pMeta = new daeMetaElement;

    _pMeta->setName("SourceIntegration");
	_pMeta->registerClass(SourceIntegration::create, &_pMeta);

	domSource::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(SourceIntegration));
	_pMeta->validate();

    return _pMeta;
}

void SourceIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SournceIntegration::fromCollada for %s %p %p\n", 
            _pElement->getTypeName(),
            this,
            &(*_pElement));
#endif
}

GeoVec3fPropertyPtr SourceIntegration::getAsVec3fProp(void)
{
    if(_pVec3fProp != NULL)
        return _pVec3fProp;

    domSource *pSource = dynamic_cast<domSource *>(_pElement);

    if(pSource == NULL)
        return _pVec3fProp;

    const domFloat_arrayRef aData = pSource->getFloat_array();

    _pVec3fProp = GeoVec3fProperty::create();

    OSG::addRef(_pVec3fProp);

    UInt32 uiCurr = 0;
    Vec3f  tmpVec;
    
    for(UInt32 i = 0; i < aData->getCount(); ++i)
    {
        tmpVec[uiCurr] = aData->getValue()[i];
        
        ++uiCurr;
        
        if(uiCurr == 3)
        {
            _pVec3fProp->push_back(tmpVec);
            
            uiCurr = 0;
        }
    }
    
    return _pVec3fProp;
}

GeoPnt3fPropertyPtr SourceIntegration::getAsPnt3fProp(void)
{
    if(_pPnt3fProp != NULL)
        return _pPnt3fProp;

    domSource *pSource = dynamic_cast<domSource *>(_pElement);

    if(pSource == NULL)
        return _pPnt3fProp;

    const domFloat_arrayRef aData = pSource->getFloat_array();

    _pPnt3fProp = GeoPnt3fProperty::create();

    OSG::addRef(_pPnt3fProp);

    UInt32 uiCurr = 0;
    Vec3f  tmpVec;
    
    for(UInt32 i = 0; i < aData->getCount(); ++i)
    {
        tmpVec[uiCurr] = aData->getValue()[i];
        
        ++uiCurr;
        
        if(uiCurr == 3)
        {
            _pPnt3fProp->push_back(tmpVec);
            
            uiCurr = 0;
        }
    }
    
    return _pPnt3fProp;
}

GeoVec2fPropertyPtr SourceIntegration::getAsVec2fProp(void)
{
    if(_pVec2fProp != NULL)
        return _pVec2fProp;

    domSource *pSource = dynamic_cast<domSource *>(_pElement);

    if(pSource == NULL)
        return _pVec2fProp;

    const domFloat_arrayRef aData = pSource->getFloat_array();

    _pVec2fProp = GeoVec2fProperty::create();

    OSG::addRef(_pVec2fProp);

    UInt32 uiCurr = 0;
    Vec2f  tmpVec;
    
    for(UInt32 i = 0; i < aData->getCount(); ++i)
    {
        tmpVec[uiCurr] = aData->getValue()[i];
        
        ++uiCurr;
        
        if(uiCurr == 2)
        {
            _pVec2fProp->push_back(tmpVec);
            
            uiCurr = 0;
        }
    }
    
    return _pVec2fProp;
}

//---------------------------------------------------------------------------
//  SourceIntegration
//---------------------------------------------------------------------------

daeMetaElement *EffectIntegration::_pMeta = NULL;

void EffectIntegration::handleSimpleColor(DomColor *pDiffuse,
                                          DomColor *pAmbient,
                                          DomColor *pSpecular,
                                          DomColor *pEmission,
                                          Real32    fShininess,
                                          Real32    fTransparency)
{
    MaterialChunkPtr pMatChunk = MaterialChunk::create();

    Color4f colVal;

    colVal[3] = fTransparency;

    if(pDiffuse != NULL)
    {
        domFx_color_common &color = pDiffuse->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];

        pMatChunk->setDiffuse(colVal);
    }

    if(pAmbient != NULL)
    {
        domFx_color_common &color = pAmbient->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];

        pMatChunk->setAmbient(colVal);
    }

    if(pSpecular != NULL)
    {
        domFx_color_common &color = pSpecular->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];

        pMatChunk->setSpecular(colVal);
    }

/*
    if(pEmission != NULL)
    {
        domFx_color_common &color = pEmission->getValue();

        colVal[0] = color[0];
        colVal[1] = color[1];
        colVal[2] = color[2];

        pMatChunk->setEmission(colVal);
    }
 */

    pMatChunk->setShininess(fShininess);

    _pMaterial->addChunk(pMatChunk);
}

void EffectIntegration::fillElements(
    domCommon_color_or_texture_type             *pIn,
    domCommon_color_or_texture_type::domColor   *&pColOut,
    domCommon_color_or_texture_type::domTexture *&pTexOut)
{
    if(pIn != NULL)
    {
        pColOut = pIn->getColor  ();
        pTexOut = pIn->getTexture();
    }
}

template<class T>
void EffectIntegration::setupSimpleColorAndTex(T           pTechT,
                                               DomFloat   *pShininess,
                                               DomColor   *pSpecularCol,
                                               DomTexture *pSpecularTex)
{
    if(pTechT == NULL)
        return;

    domCommon_color_or_texture_type::domColor   *pDiffuseCol = NULL;
    domCommon_color_or_texture_type::domTexture *pDiffuseTex = NULL;
    
    domCommon_color_or_texture_type::domColor   *pAmbientCol = NULL;
    domCommon_color_or_texture_type::domTexture *pAmbientTex = NULL;
       
    domCommon_color_or_texture_type::domColor   *pEmissionCol = NULL;
    domCommon_color_or_texture_type::domTexture *pEmissionTex = NULL;

    fillElements(pTechT->getDiffuse(),
                 pDiffuseCol,
                 pDiffuseTex);
    
    fillElements(pTechT->getAmbient(),
                 pAmbientCol,
                 pAmbientTex);
    
    fillElements(pTechT->getEmission(),
                 pEmissionCol,
                 pEmissionTex);

    domCommon_float_or_param_type   *pTransparency =
        pTechT->getTransparency();

    Real32 rShininess    = 10.f;
    Real32 rTransparency = 1.f;
    
    if(pShininess != NULL && pShininess->getFloat() != NULL)
        rShininess = pShininess->getFloat()->getValue();

    if(pTransparency != NULL && pTransparency->getFloat() != NULL)
        rTransparency = pTransparency->getFloat()->getValue();
    
    handleSimpleColor(pDiffuseCol,
                      pAmbientCol,
                      pSpecularCol,
                      pEmissionCol,
                      rShininess,
                      rTransparency);

    UInt32 _uiCurrTex = 0;

    if(pAmbientTex != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "got texture %s\n",
                pAmbientTex->getTexture());
#endif

        std::map<std::string, 
                 domFx_sampler2D_common *>::iterator samplerIt;

        samplerIt = _mSamplerMap.find(pAmbientTex->getTexture());

        if(samplerIt != _mSamplerMap.end())
        {
            domFx_sampler2D_common *pSampler = samplerIt->second;

            Sampler2DIntegration::setEffectIntegration(this);

            Sampler2DIntegration *pSamplerInt = 
                dynamic_cast<Sampler2DIntegration *>(pSampler->getIntObject());

            pSamplerInt->fromCOLLADAChecked();

            Sampler2DIntegration::setEffectIntegration(NULL);
            
            TextureObjChunkPtr pTexObj = pSamplerInt->getTexObj();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "got texobj %p\n", pTexObj);
#endif            
            if(pTexObj != NULL)
            {
                TextureEnvChunkPtr pTexEnv = TextureEnvChunk::create();
                
                _pMaterial->addChunk(pTexObj);
                _pMaterial->addChunk(pTexEnv);
                
                pTexEnv->setEnvMode(GL_REPLACE);
                
                _vTexCoordMapping[_uiCurrTex++] = pAmbientTex->getTexcoord();
            }
        }
        else
        {
            domEffect *pEffect = dynamic_cast<domEffect *>(_pElement);
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "got domX effect %p %s\n%s\n", 
                    pEffect, 
                    pEffect->getId(),
                    pEffect->getDocumentURI()->getURI());
#endif
            
            std::string effectUri = pEffect->getDocumentURI()->getURI();
            
            effectUri += "#";
            effectUri += pAmbientTex->getTexture();
            
            daeURI oUri(effectUri.c_str());
            
            oUri.resolveElement();
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "uri %s %d\n", oUri.getURI(), oUri.getState());
#endif
            
            daeElementRef pImageElem = oUri.getElement();
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "image elem %p %s %s\n", 
                    &*pImageElem, 
                    pImageElem->getTypeName(),
                    pImageElem->getElementName());
#endif
            
            ImageIntegration *pImageInt = 
                dynamic_cast<ImageIntegration *>(pImageElem->getIntObject());
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "Got Image Integration %p\n",
                    pImageInt);
#endif
            
            pImageInt->fromCOLLADAChecked();
            
            ImagePtr pImage = pImageInt->getImage();
            
            if(pImage != NullFC)
            {
                TextureObjChunkPtr pTexObj = TextureObjChunk::create();
                TextureEnvChunkPtr pTexEnv = TextureEnvChunk::create();
                
                pTexObj->setImage(pImage);
                
                
                _pMaterial->addChunk(pTexObj);
                _pMaterial->addChunk(pTexEnv);
                
                pTexEnv->setEnvMode(GL_REPLACE);
                
                _vTexCoordMapping[_uiCurrTex++] = pAmbientTex->getTexcoord();
            }
        }
    }

    if(pDiffuseTex != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "got texture %s\n",
                pDiffuseTex->getTexture());
#endif

        std::map<std::string, 
                 domFx_sampler2D_common *>::iterator samplerIt;

        samplerIt = _mSamplerMap.find(pDiffuseTex->getTexture());

        if(samplerIt != _mSamplerMap.end())
        {
            domFx_sampler2D_common *pSampler = samplerIt->second;

            Sampler2DIntegration::setEffectIntegration(this);

            Sampler2DIntegration *pSamplerInt = 
                dynamic_cast<Sampler2DIntegration *>(pSampler->getIntObject());

            pSamplerInt->fromCOLLADAChecked();

            Sampler2DIntegration::setEffectIntegration(NULL);
            
            TextureObjChunkPtr pTexObj = pSamplerInt->getTexObj();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "got texobj %p\n", pTexObj);
#endif
            
            if(pTexObj != NULL)
            {
                TextureEnvChunkPtr pTexEnv = TextureEnvChunk::create();
                
                _pMaterial->addChunk(pTexObj);
                _pMaterial->addChunk(pTexEnv);
                
                pTexEnv->setEnvMode(GL_MODULATE);
                
                _vTexCoordMapping[_uiCurrTex++] = pDiffuseTex->getTexcoord();
            }
        }
        else
        {
            domEffect *pEffect = dynamic_cast<domEffect *>(_pElement);
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "got domX effect %p %s\n%s\n", 
                    pEffect, 
                    pEffect->getId(),
                    pEffect->getDocumentURI()->getURI());
#endif
            
            std::string effectUri = pEffect->getDocumentURI()->getURI();
            
            effectUri += "#";
            effectUri += pDiffuseTex->getTexture();
            
            daeURI oUri(effectUri.c_str());
            
            oUri.resolveElement();
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "uri %s %d\n", oUri.getURI(), oUri.getState());
#endif
            
            daeElementRef pImageElem = oUri.getElement();
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "image elem %p %s %s\n", 
                    &*pImageElem, 
                    pImageElem->getTypeName(),
                    pImageElem->getElementName());
#endif
            
            ImageIntegration *pImageInt = 
                dynamic_cast<ImageIntegration *>(pImageElem->getIntObject());
            
#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "Got Image Integration %p\n",
                    pImageInt);
#endif
            
            pImageInt->fromCOLLADAChecked();
            
            ImagePtr pImage = pImageInt->getImage();
            
            if(pImage != NullFC)
            {
                TextureObjChunkPtr pTexObj = TextureObjChunk::create();
                TextureEnvChunkPtr pTexEnv = TextureEnvChunk::create();
                
                pTexObj->setImage(pImage);
                
                
                _pMaterial->addChunk(pTexObj);
                _pMaterial->addChunk(pTexEnv);
                
                pTexEnv->setEnvMode(GL_MODULATE);
                
                _vTexCoordMapping[_uiCurrTex++] = pDiffuseTex->getTexcoord();
            }
        }
    }
}                        

template<class T>
void EffectIntegration::setupSimpleSpecColorAndTex(T pTechT)
{
    domCommon_color_or_texture_type::domColor   *pSpecularCol = NULL;
    domCommon_color_or_texture_type::domTexture *pSpecularTex = NULL;

    fillElements(pTechT->getSpecular(),
                 pSpecularCol,
                 pSpecularTex);

    domCommon_float_or_param_type   *pShininess =
        pTechT->getShininess();

    setupSimpleColorAndTex(pTechT, 
                           pShininess,
                           pSpecularCol,
                           pSpecularTex);
}

void EffectIntegration::handleCommonProfile(domProfile_COMMON *pCommon)
{
    domProfile_COMMON::domTechnique *pTechnique = pCommon->getTechnique(); 

    if(pTechnique == NULL)
    {
        return;
    }
    
    if(_pMaterial == NullFC)
    {
        _pMaterial = ChunkMaterial::create();
    }
    
    domCommon_newparam_type_Array &aParams = pCommon->getNewparam_array();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got %d params\n", aParams.getCount());
#endif

    for(UInt32 i = 0; i < aParams.getCount(); ++i)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "param[%d] %s\n", i, aParams[i]->getSid());
#endif

        if(aParams[i]->getSurface() != NULL)
        {
            _mSurfaceMap[aParams[i]->getSid()] = aParams[i]->getSurface();
        }

        if(aParams[i]->getSampler2D() != NULL)
        {
            _mSamplerMap[aParams[i]->getSid()] = aParams[i]->getSampler2D();
        }
    }

#if 0
    for(UInt32 i = 0; i < vSampler.size(); ++i)
    {
        fprintf(stderr, "[%d] %s\n", i, vSampler[i].second.c_str());

        if(vSampler[i].first->getSource() != NULL)
        {
            for(UInt32 j = 0; j < vSurfaces.size(); ++j)
            {
                fprintf(stderr, "  [%d] %s\n", j, vSurfaces[j].second.c_str());

                std::string tmpName = 
                    vSampler[i].first->getSource()->getValue();

                if(vSurfaces[i].second == tmpName)
                {
                    domFx_surface_init_common *pInit =
                        vSurfaces[i].first->getFx_surface_init_common();

                    if(pInit == NULL)
                        break;

                    fprintf(stderr, "Found XX %p %s\n",
                            pInit,
                            pInit->getTypeName());

                    domFx_surface_init_from_common_Array *commonInitA =
                        &(pInit->getInit_from_array());

                    domFx_surface_init_from_common *pCommonInit =
                        (*(commonInitA))[0];

                    fprintf(stderr, "Got commonInit %d %p \n", 
                            commonInitA->getCount(),
                            pCommonInit);

                    pCommonInit->getValue().resolveElement();

                    daeElement *pImageElem = 
                        pCommonInit->getValue().getElement();

                    fprintf(stderr, "%p %d\n",
                            pImageElem,
                            pCommonInit->getValue().getState());
                    break;
                }
            }
        }
    }
#endif

    if(pTechnique->getConstant() != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Constant\n");
#endif
    }
    else if(pTechnique->getLambert() != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Lambert\n");
#endif
        setupSimpleColorAndTex(pTechnique->getLambert());
    }
    else if(pTechnique->getPhong())
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Phong\n");
#endif
        setupSimpleSpecColorAndTex(pTechnique->getPhong());
    }
    else if(pTechnique->getBlinn())
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "Blinn\n");
#endif
        setupSimpleSpecColorAndTex(pTechnique->getBlinn());
    }
    else
    {
        fprintf(stderr, "Unknown technique\n");
    }
}

void EffectIntegration::handleGLSLProfile(domProfile_GLSL *pGLSL)
{
}

void EffectIntegration::handleCGProfile(domProfile_CG *pCG)
{
}

EffectIntegration::EffectIntegration(void) :
     Inherited       (      ),
    _pMaterial       (NullFC),
    _vTexCoordMapping(      )
{
    // Hack should check #gl textures
    _vTexCoordMapping.resize(16);
}

EffectIntegration::~EffectIntegration(void)
{
    OSG::subRef(_pMaterial);
}

daeElementRef EffectIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "EffectIntegration::create %p\n", (void *)bytes);
#endif

	EffectIntegrationRef ref = new(bytes) EffectIntegration;

	return ref;
}

daeMetaElement *EffectIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "EffectIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    
    _pMeta = new daeMetaElement;

    _pMeta->setName("EffectIntegration");
	_pMeta->registerClass(EffectIntegration::create, &_pMeta);

	domEffect::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(EffectIntegration));
	_pMeta->validate();

    return _pMeta;
}

void EffectIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "EffectIntegration::fromCollada for %s %p %p\n", 
            _pElement->getTypeName(),
            this,
            &(*_pElement));
#endif

    domEffect *pEffect = dynamic_cast<domEffect *>(_pElement);

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got dom effect %p %s\n%s\n", 
            pEffect, 
            pEffect->getId(),
            pEffect->getDocumentURI()->getURI());
#endif

    if(pEffect == NULL)
        return;

    UInt32 uiNumProfiles = 
        pEffect->getFx_profile_abstract_array().getCount(); 

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Effect %s has %d profile\n", 
            pEffect->getId(), 
            uiNumProfiles);
#endif

    for(UInt32 i = 0; i < uiNumProfiles; ++i)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "[%d] %s\n", 
                i,
                pEffect->getFx_profile_abstract_array()[i]->getTypeName()); 
#endif

        domProfile_COMMON *pCommon = 
            dynamic_cast<domProfile_COMMON *>(
                &(*(pEffect->getFx_profile_abstract_array()[i])));

        domProfile_GLSL   *pGLSL   = 
            dynamic_cast<domProfile_GLSL *>(
                &(*(pEffect->getFx_profile_abstract_array()[i])));

        domProfile_CG     *pCG     = 
            dynamic_cast<domProfile_CG *>(
                &(*(pEffect->getFx_profile_abstract_array()[i])));

        if(pCommon != NULL)
        {
            handleCommonProfile(pCommon);
        }
        else if(pGLSL != NULL)
        {
            handleGLSLProfile(pGLSL);
        }
        else if(pCG != NULL)
        {
            handleCGProfile(pCG);
        }
        else
        {
            fprintf(stderr, "Unknown profile %p %p %p\n",
                    pCommon,
                    pGLSL,
                    pCG);
            
        }
    }
}

ChunkMaterialPtr EffectIntegration::getMaterial(void)
{
    return _pMaterial;
}

UInt32 EffectIntegration::getTexBinding(std::string szRef)
{
    UInt32 returnValue = 0xFFFF;

    for(UInt32 i = 0; i < _vTexCoordMapping.size(); ++i)
    {
        if(_vTexCoordMapping[i] == szRef)
        {
            returnValue = i; 
            break;
        }
    }

    return returnValue;
}

domFx_surface_common *EffectIntegration::getSurface(std::string szRef)
{
    domFx_surface_common *returnValue = NULL;

    std::map<std::string, domFx_surface_common *>::iterator surfIt = 
        _mSurfaceMap.find(szRef);

    if(surfIt != _mSurfaceMap.end())
    {
        returnValue = surfIt->second;
    }

    return returnValue;
}


//---------------------------------------------------------------------------
//  ImageIntegration
//---------------------------------------------------------------------------

daeMetaElement *ImageIntegration::_pMeta = NULL;

ImageIntegration::ImageIntegration(void) :
     Inherited (      ),
    _pImage    (NullFC)
{
}

ImageIntegration::~ImageIntegration(void)
{
    OSG::subRef(_pImage);
}

daeElementRef ImageIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ImageIntegration::create\n");
#endif

	ImageIntegrationRef ref = new(bytes) ImageIntegration;

	return ref;
}

daeMetaElement *ImageIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ImageIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    
    _pMeta = new daeMetaElement;

    _pMeta->setName("ImageIntegration");
	_pMeta->registerClass(ImageIntegration::create, &_pMeta);

	domImage::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(ImageIntegration));
	_pMeta->validate();

    return _pMeta;
}

ImagePtr ImageIntegration::getImage(void)
{
    return _pImage;
}

void ImageIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "ImageIntegration::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif

    domImage *pCImage = dynamic_cast<domImage *>(_pElement);

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got %p\n", pCImage);
#endif

    if(pCImage != NULL)
    {
        const domImage::domInit_fromRef pInitFrom = pCImage->getInit_from();

        if(pInitFrom != NULL)
        {
            xsAnyURI oImageURI = pInitFrom->getValue();

#ifdef OSG_DEBUG_PRINT
            fprintf(stderr, "image uri %s\n", 
                    oImageURI.getURI());
#endif

            _pImage = ImageFileHandler::the()->read(oImageURI.getURI());

            if(_pImage != NullFC)
            {
#ifdef OSG_DEBUG_PRINT
                fprintf(stderr, "Image loaded\n");
#endif
                OSG::addRef(_pImage);
            }
        }
    }
}




//---------------------------------------------------------------------------
//  Sampler2DIntegration
//---------------------------------------------------------------------------

daeMetaElement *Sampler2DIntegration::_pMeta = NULL;

EffectIntegration *Sampler2DIntegration::_pEffectInt = NULL;

Sampler2DIntegration::Sampler2DIntegration(void) :
     Inherited (      ),
    _pTexObj   (NullFC)
{
}

Sampler2DIntegration::~Sampler2DIntegration(void)
{
    OSG::subRef(_pTexObj);
}

daeElementRef Sampler2DIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SamplerIntegration::create\n");
#endif

	Sampler2DIntegrationRef ref = new(bytes) Sampler2DIntegration;

	return ref;
}

daeMetaElement *Sampler2DIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Sampler2DIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    
    _pMeta = new daeMetaElement;

    _pMeta->setName("Sampler2DIntegration");
	_pMeta->registerClass(Sampler2DIntegration::create, &_pMeta);

	domFx_sampler2D_common::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(Sampler2DIntegration));
	_pMeta->validate();

    return _pMeta;
}

TextureObjChunkPtr Sampler2DIntegration::getTexObj(void)
{
    return _pTexObj;
}

void Sampler2DIntegration::setEffectIntegration(EffectIntegration *pInt)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "setEff %p\n", pInt);
#endif

    _pEffectInt = pInt;
}

void Sampler2DIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Sampler2DIntegration::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif
    
    domFx_sampler2D_common::domSourceRef    pSource;
    domFx_sampler2D_common::domWrap_sRef    pWrapS;
    domFx_sampler2D_common::domWrap_tRef    pWrapT;
    domFx_sampler2D_common::domMinfilterRef pMinFilter;
    domFx_sampler2D_common::domMagfilterRef pMagFilter;

    domFx_sampler2D_common *pSampler = 
        dynamic_cast<domFx_sampler2D_common *>(_pElement);

    if(pSampler == NULL)
        return;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got sampler %p\n", pSampler);
#endif

    pSource    = pSampler->getSource   ();
    pWrapS     = pSampler->getWrap_s   ();
    pWrapT     = pSampler->getWrap_t   ();
    pMinFilter = pSampler->getMinfilter();
    pMagFilter = pSampler->getMagfilter();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "EffectInt %p\n", _pEffectInt);
#endif

    if(pSource != NULL && _pEffectInt != NULL)
    {
#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "got source %s\n", 
                pSource->getValue());
#endif

        domFx_surface_common *pSurface = 
            _pEffectInt->getSurface(pSource->getValue());

#ifdef OSG_DEBUG_PRINT
        fprintf(stderr, "got surface %p\n", 
                pSurface);
#endif

        SurfaceIntegration *pSurfaceInt = 
            dynamic_cast<SurfaceIntegration *>(pSurface->getIntObject());

        pSurfaceInt->fromCOLLADAChecked();

        _pTexObj = pSurfaceInt->getTexObj();

        OSG::addRef(_pTexObj);
    }

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got surf tex obj %p\n", _pTexObj);
#endif
}



//---------------------------------------------------------------------------
//  ImageIntegration
//---------------------------------------------------------------------------

daeMetaElement *SurfaceIntegration::_pMeta = NULL;

SurfaceIntegration::SurfaceIntegration(void) :
     Inherited(      ),
    _pTexObj  (NullFC)
{
}

SurfaceIntegration::~SurfaceIntegration(void)
{
    OSG::subRef(_pTexObj);
}

daeElementRef SurfaceIntegration::create(daeInt bytes)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SurfaceIntegration::create\n");
#endif

	SurfaceIntegrationRef ref = new(bytes) SurfaceIntegration;

	return ref;
}

daeMetaElement *SurfaceIntegration::registerElement(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SurfaceIntegration::regElem\n");
#endif

    if(_pMeta != NULL )
        return _pMeta;
    
    _pMeta = new daeMetaElement;

    _pMeta->setName("SurfaceIntegration");
	_pMeta->registerClass(SurfaceIntegration::create, &_pMeta);

	domFx_surface_common::_Meta->setMetaIntegration(_pMeta);

	_pMeta->setElementSize(sizeof(SurfaceIntegration));
	_pMeta->validate();

    return _pMeta;
}

TextureObjChunkPtr SurfaceIntegration::getTexObj(void)
{
    return _pTexObj;
}

void SurfaceIntegration::fromCOLLADA(void)
{
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "SurfaceIntegration::fromCollada for %s\n", 
            _pElement->getTypeName());
#endif

    domFx_surface_common *pSurface = 
        dynamic_cast<domFx_surface_common *>(_pElement);

    if(pSurface == NULL)
        return;

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got surface %p\n", pSurface);
#endif

    domFx_surface_init_common *pInit =
        pSurface->getFx_surface_init_common();

    if(pInit == NULL)
        return;
    
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Found XX %p %s\n",
            pInit,
            pInit->getTypeName());
#endif
    
    domFx_surface_init_from_common_Array *commonInitA =
        &(pInit->getInit_from_array());
    
    domFx_surface_init_from_common *pCommonInit =
        (*(commonInitA))[0];
    
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got commonInit %d %p \n", 
            commonInitA->getCount(),
            pCommonInit);
#endif
    
    pCommonInit->getValue().resolveElement();
    
    daeElement *pImageElem = 
        pCommonInit->getValue().getElement();
    
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "%p %d\n",
            pImageElem,
            pCommonInit->getValue().getState());
#endif

    ImageIntegration *pImageInt = 
        dynamic_cast<ImageIntegration *>(pImageElem->getIntObject());
            
#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "Got Image Integration %p\n",
            pImageInt);
#endif
            
    pImageInt->fromCOLLADAChecked();
    
    ImagePtr pImage = pImageInt->getImage();

#ifdef OSG_DEBUG_PRINT
    fprintf(stderr, "got image %p\n", pImage);
#endif

    if(pImage != NULL)
    {
        _pTexObj = TextureObjChunk::create();

        _pTexObj->setImage(pImage);
    }
}





OSG_BEGIN_NAMESPACE

void initColladaIntegration(void)
{
    ColladaIntegrationBase::registerElement();

    VisualSceneIntegration     ::registerElement();
    NodeIntegration            ::registerElement();
    GeometryInstanceIntegration::registerElement();
    GeometryIntegration        ::registerElement();
    SourceIntegration          ::registerElement();
    EffectIntegration          ::registerElement();
    ImageIntegration           ::registerElement();
    Sampler2DIntegration       ::registerElement();
    SurfaceIntegration         ::registerElement();
}

OSG_END_NAMESPACE

#endif /* OSG_WITH_COLLADA */
