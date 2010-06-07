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

// AMZ disabled for now.

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLFile.h"

#include "OSGFieldType.h"
#include "OSGMathMFields.h"
#include "OSGMathSFields.h"
#include "OSGVecMFields.h"
#include "OSGVecSFields.h"


#include "OSGAction.h"
#include "OSGMaterial.h"
#include "OSGMaterialGroup.h"
#include "OSGNameAttachment.h"

#include "OSGGroup.h"

#include "OSGBlendChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGFieldConnector.h"


#include "OSGSceneFileHandler.h"

#define OSG_DEBUG_VRML

OSG_USING_NAMESPACE

/*! \class OSG::VRMLFile
 */

/*! \var OSG::VRMLFile::PushNames
    Option to push the name attachments for entities that can not have a
    NameAttachment in OpenSG to their respective parent.
    
    This is currently only implemented for MaterialChunks and only sets the
    name on the containing ChunkMaterial if that does not have a name of its
    own.
 */

OSG::Time startTime = 0.;
OSG::Time useTime   = 0.;
OSG::Time findTime  = 0.;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLFile::VRMLFile(void) :
    Inherited(),

    _pSceneRootNode     (NULL),

    _pCurrNodeHelper(NULL),
    _sNodeHelpers   (),

    _pCurrentFC       (NULL  ),
    _pCurrentFieldFC  (NULL  ),
    _pCurrentField    (      ),
    _pCurrentFieldDesc(NULL  ),

    _fcStack  (),
    _fStack   (),
    _fdStack  (),

    _nameFCMap    ()
{
    Self::setReferenceHeader("#VRML V2.0 ");

    initIntExtFieldTypeMapper();
    initExtIntFieldTypeMapper();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLFile::~VRMLFile(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Skel Replacements                             */

NodeTransitPtr VRMLFile::scanStream(std::istream &is)
{
    startTime = getSystemTime();

    _pSceneRootNode      = NULL;
    _pCurrentFC          = NULL;

    _nameFCMap.clear();

#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::resetIndent();
#endif

    if(is)
    {
        Inherited::scanStream(is);
    }

    SceneFileHandler::the()->updateReadProgress(100);

    NodeTransitPtr returnValue(_pSceneRootNode);

    _pSceneRootNode      = NULL;
    _pCurrentFC          = NULL;

    FINFO(("Full Time : %lf | Use Time %lf\n",
            getSystemTime() - startTime,
            useTime));

    return returnValue;
}

bool VRMLFile::checkHeader(void)
{
    return true;
}

void VRMLFile::handleError(const Char8 *szErrorText)
{
    Inherited::handleError(szErrorText);
    // on an error we destroy the incomplete scene.

#if 0
    if(_pSceneRootNode != NULL)
    {
        _pSceneRootNode = NULL;
    }
#endif
}

void VRMLFile::beginNode(const Char8 *szNodeTypename,
                         const Char8 *szNodename)
{
    SceneFileHandler::the()->updateReadProgress();

    FieldContainerUnrecPtr pNewNode;

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "Begin Node " << szNodeTypename << std::endl;

    VRMLNodeHelper::incIndent();
#endif

    VRMLNodeHelper *pOldHelper = _pCurrNodeHelper;

    _pCurrNodeHelper = findNodeHelper(szNodeTypename);

    _sNodeHelpers.push(_pCurrNodeHelper);

    if(_pCurrNodeHelper == NULL)
    {
        std::string szTmp = "Unknow node type '#";

        szTmp += szNodeTypename;
        szTmp += "#";

        Inherited::handleError(szTmp.c_str());

        return;
    }

    _pCurrNodeHelper->reset();

    pNewNode = _pCurrNodeHelper->beginNode( szNodeTypename,
                                            szNodename,
                                           _pCurrentFC);


    if(szNodename != NULL)
    {
        if(pNewNode != NULL)
        {
            std::string szKey = szNodename;

            AttachmentContainer *pAttC = 
                dynamic_pointer_cast<AttachmentContainer>(pNewNode);

            if(pAttC != NULL)
            {
                setName(pAttC, szKey);
            }


            NameContainerMap::iterator mIt = _nameFCMap.find(szKey);

            // amz - I removed the map checks that's more spec conform.
            // From the spec:
            // If multiple nodes are given the same name,
            // each USE statement refers to the closest node with the given
            // name preceding it 
            // in either the VRML file or prototype definition.
                
            //if(mIt == _nameFCMap.end())
            {
                _nameFCMap[szKey] = pNewNode;
            }
//            else
//            {
//                PWARNING << "Did not add fieldContainer with name "
//                         << szKey
//                         << " a second time"
//                         << std::endl;
//            }

        }
    }

    if(pOldHelper != NULL)
    {
        pOldHelper->setContainerFieldValue( pNewNode,
                                           _pCurrentFieldDesc,
                                           _pCurrentFieldFC  );
    }

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        Node *pNode = dynamic_cast<Node *>(_pCurrentFC.get());

        if(_pSceneRootNode == NULL)
        {
            _pSceneRootNode = Node::create();

            _pSceneRootNode->setCore(Group::create());
        }

        _pSceneRootNode->addChild(pNode);
    }
}

void VRMLFile::endNode(void)
{
    SceneFileHandler::the()->updateReadProgress();

    if(_pCurrNodeHelper == NULL)
    {
#ifdef OSG_DEBUG_VRML
        VRMLNodeHelper::decIndent();

        indentLog(VRMLNodeHelper::getIndent(), PINFO);
        PINFO << "End Node " << std::endl;
#endif

        _sNodeHelpers.pop();

        if(_sNodeHelpers.size() != 0)
        {
            _pCurrNodeHelper = _sNodeHelpers.top();
        }
        else
        {
            _pCurrNodeHelper = NULL;
        }

        return;
    }

    _pCurrNodeHelper->endNode(_pCurrentFC);

    _sNodeHelpers.pop();

    if(_sNodeHelpers.size() != 0)
    {
        _pCurrNodeHelper = _sNodeHelpers.top();
    }
    else
    {
        _pCurrNodeHelper = NULL;
    }

    if(_pCurrentFC != NULL)
    {
        if(_pCurrentFC->getType().isNode() == true)
        {
            Node *pNode = dynamic_cast<Node *>(_pCurrentFC.get());

            if(pNode->getCore() == NULL)
            {
                pNode->setCore(Group::create());
            }
        }
    }

    _fcStack.pop();

    if(_fcStack.size() != 0)
    {
        _pCurrentFC = _fcStack.top();
    }
    else
    {
        _pCurrentFC = NULL;
    }

    if(_pCurrentFieldDesc != NULL)
    {
        _pCurrentFieldFC = _pCurrentFC;
    }
#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();

    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "End Node " << std::endl;
#endif
}

void VRMLFile::beginScript(const Char8 *szNodename)
{
    beginNode("Script", szNodename);
}

void VRMLFile::endScript(void)
{
    endNode();
}

void VRMLFile::beginField(const Char8  *szFieldname,
                          const UInt32  OSG_VRML_ARG(uiFieldTypeId))
{
    if(szFieldname == NULL)
        return;

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "VRMLFile::beginField : looking for "
          << szFieldname
          << " ("
          << uiFieldTypeId
          << " | "
          << _pCurrentField
          << " | "
          << _pCurrentFieldDesc
          << ") "
          << ScanParseSkel::OSGmfNode
          << std::endl;

    VRMLNodeHelper::incIndent();
#endif

    _fStack .push(_pCurrentField    );
    _fdStack.push(_pCurrentFieldDesc);
}

void VRMLFile::endField(void)
{
    _fStack.pop();

    if(_fStack.size() != 0)
    {
        _pCurrentField = _fStack.top();
    }
    else
    {
        _pCurrentField.reset();
    }


    _fdStack.pop();

    if(_fdStack.size() != 0)
    {
        _pCurrentFieldDesc = _fdStack.top();
    }
    else
    {
        _pCurrentFieldDesc = NULL;
    }

#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();

    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "VRMLFile::endField " << std::endl;
#endif
}


void VRMLFile::addFieldValue(const Char8 *szFieldVal)
{
    if(_pCurrNodeHelper != NULL)
    {
        _pCurrNodeHelper->addFieldValue(_pCurrentField, 
                                        _pCurrentFieldDesc,
                                        szFieldVal);
    }
}

void VRMLFile::addImageValue(Image *pImage)
{
    if(_pCurrNodeHelper != NULL)
    {
        _pCurrNodeHelper->addImageValue(_pCurrentField, 
                                        _pCurrentFieldDesc,
                                         pImage           );
    }
}

void VRMLFile::beginProto(const Char8 *szProtoname)
{
    Inherited::beginProto(szProtoname);

    _pCurrNodeHelper = Inherited::_pCurrentHelper;
}

void VRMLFile::endProtoInterface(void)
{
    Inherited::endProtoInterface();
}

void VRMLFile::endProto(void)
{
    Inherited::endProto();

    if(_sNodeHelpers.size() != 0)
    {
        _pCurrNodeHelper = _sNodeHelpers.top();
    }
}


void VRMLFile::beginFieldDecl(const Char8  *szFieldType,
                              const UInt32  uiFieldTypeId,
                              const Char8  *szFieldName)
{
    Inherited::beginFieldDecl(szFieldType, uiFieldTypeId, szFieldName);

    getFieldType(szFieldName);

    beginField(szFieldName, uiFieldTypeId);
}

void VRMLFile::endFieldDecl(void)
{
    Inherited::endFieldDecl();

    endField();
}


UInt32 VRMLFile::getFieldType(const Char8 *szFieldname)
{
    UInt32   returnValue = 0;

    if(_pCurrNodeHelper == NULL)
        return returnValue;

    if(szFieldname == NULL)
        return returnValue;

    _pCurrentFieldFC   = NULL;
    _pCurrentField.reset();
    _pCurrentFieldDesc = NULL;

    _pCurrNodeHelper->getFieldAndDesc(_pCurrentFC,
                                       szFieldname,
                                      _pCurrentFieldFC,
                                      _pCurrentField,
                                      _pCurrentFieldDesc);

    if(_pCurrentFieldDesc != NULL)
        returnValue = _pCurrentFieldDesc->getFieldType().getId();

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "VRMLFile::getFieldType : Got Field and type "
          << returnValue        << " "
          << _pCurrentField     << " "
          << _pCurrentFieldDesc << " ";

    if(_pCurrentFieldDesc != NULL)
        PINFO << _pCurrentFieldDesc->getFieldType().getName() << std::endl;
    else
        PINFO << std::endl;
#endif

    return returnValue;
}

void VRMLFile::use(const Char8 *szName)
{
    SceneFileHandler::the()->updateReadProgress();
    Time beginUse = getSystemTime();

    FieldContainerUnrecPtr pUsedFC;

    // try to find a container with the given name attachment

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "VRMLFile::use : looking for "
          << szName
          << std::endl;

    VRMLNodeHelper::incIndent();
#endif

    pUsedFC = findReference(szName);

    if(pUsedFC == NULL)
    {
        PWARNING << "No fieldContainer with name found to use"
                 << szName
                 << std::endl;
    }
    else
    {
        // assign nodepointer to current sf|mf field

        if(_pCurrNodeHelper != NULL)
        {
            if(pUsedFC->getType().isNode())
            {
                Node *pRootNode = dynamic_pointer_cast<Node>(pUsedFC);
                
                pUsedFC = cloneTree(pRootNode);
            }
            
            _pCurrNodeHelper->setContainerFieldValue( pUsedFC,
                                                     _pCurrentFieldDesc,
                                                     _pCurrentFieldFC  );
        }
    }

#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();
#endif

    useTime += (getSystemTime() - beginUse);
}

void VRMLFile::addRoute(const Char8  *szOutNodename,
                        const Char8  *szOutFieldname,
                        const Char8  *szInNodename,
                        const Char8  *szInFieldname )
{
    if(szOutNodename == NULL || szOutFieldname == NULL ||
       szInNodename  == NULL || szInFieldname  == NULL  )
    {
        FWARNING(("addRoute missing params\n"));
    }

    FieldContainer *pSrcNode = findReference(szOutNodename);
    FieldContainer *pDstNode = findReference(szInNodename);

    AttachmentContainer *pSrc = dynamic_cast<AttachmentContainer *>(pSrcNode);
    AttachmentContainer *pDst = dynamic_cast<AttachmentContainer *>(pDstNode);

    if(pSrc == NULL)
    {
        FWARNING(("Unknow src node %s\n", szOutNodename));
        return;
    }

    if(pDstNode == NULL)
    {
        FWARNING(("Unknow dst node %s\n", szInNodename));
        return;
    }

    VRMLGenericAtt *pSrcAtt = dynamic_cast<VRMLGenericAtt *>(
        pSrc->findAttachment(VRMLGenericAtt::getClassType()));

    VRMLGenericAtt *pDstAtt = NULL;

    if(pDst != NULL)
    {
        pDstAtt = dynamic_cast<VRMLGenericAtt *>(
            pDst->findAttachment(VRMLGenericAtt::getClassType()));
    }

    if(pSrcAtt == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pSrc);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pSrcAtt = dynamic_cast<VRMLGenericAtt *>(
                pNode->getCore()->findAttachment(
                    VRMLGenericAtt::getClassType())); 
        }
    }

    if(pDstAtt == NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pDst);

        if(pNode != NULL && pNode->getCore() != NULL)
        {
            pDstAtt = dynamic_cast<VRMLGenericAtt *>(
                pNode->getCore()->findAttachment(
                    VRMLGenericAtt::getClassType())); 
        }
    }

   
    std::string szOutFName = szOutFieldname;
    std::string szInFName  = szInFieldname;

    
    std::string::size_type uiPos = szOutFName.rfind(std::string("_changed"));


    if(uiPos != std::string::npos)
    {
        szOutFName.erase(uiPos, std::string::npos);
    }
    
    uiPos = szInFName.find(std::string("set_"));

    if(uiPos != std::string::npos)
    {
        szInFName.erase(uiPos, uiPos + 4);
    }


    if(pSrcAtt != NULL)
    {
        VRMLNodeHelper *pHelper = findNodeHelper(
            pSrcAtt->getVrmlNodeTypename().c_str());

        if(pHelper != NULL)
        {
            pHelper->mapFieldname(pSrcAtt->getVrmlNodeTypename(), szOutFName);
        }
    }

    if(pSrcAtt != NULL)
    {
        VRMLNodeHelper *pHelper = findNodeHelper(
            pDstAtt->getVrmlNodeTypename().c_str());

        if(pHelper != NULL)
        {
            pHelper->mapFieldname(pDstAtt->getVrmlNodeTypename(), szInFName);
        }
    }

    addConnection(pSrc,     szOutFName.c_str(),
                  pDstNode, szInFName .c_str());
}

/*-------------------------------------------------------------------------*/
/*                          Helper                                         */

void VRMLFile::scanStandardPrototypes(const Char8  *szFilename)
{
#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::resetIndent();
#endif

    preStandardProtos();
    scanFile(szFilename);
    postStandardProtos();
}

#if 0
static Action::ResultE modifyMaterial(Node * const node)
{   
    MaterialGroup *mg = dynamic_cast<MaterialGroup *>(node->getCore());
    
    if(mg == NULL)
        return Action::Continue; 
    
    ChunkMaterial *cmat = dynamic_cast<ChunkMaterial *>(mg->getMaterial());
    
    if(cmat == NULL)
        return Action::Continue; 
    
    TextureObjChunk *texc = 
        dynamic_cast<TextureObjChunk *>(
            cmat->find(TextureObjChunk::getClassType()));
    
    if(texc == NULL)
        return Action::Continue;
    
    MaterialChunk *matc = 
        dynamic_cast<MaterialChunk *>(
            cmat->find(MaterialChunk::getClassType()));

    TextureEnvChunkUnrecPtr texe = 
        dynamic_cast<TextureEnvChunk *>(
            cmat->find(TextureEnvChunk::getClassType()));
    
    if(texe == NULL)
    {
        texe = TextureEnvChunk::create();
        cmat->addChunk(texe);
    }

    if(matc == NULL)
    {
        // no material chunk so we use the replace mode.
        texe->setEnvMode(GL_REPLACE);
        return Action::Continue;
    }
    
    if(matc != NULL)
    {
        Image *img = texc->getImage();

        texe->setEnvMode(GL_MODULATE);

        if(img != NULL && img->getBpp() > 2)
        {
            // for color textures the texture replaces only the diffuse part.
            matc->setDiffuse(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
        }
        
        
        // check for textures with alpha
        if(!matc->isTransparent()         && 
            img                   != NULL &&
            img->getBpp()         ==    4   )
        {
            BlendChunkUnrecPtr blendc = 
                dynamic_cast<BlendChunk *>(
                    cmat->find(BlendChunk::getClassType()));

            if(blendc == NULL)
            {
                blendc = OSG::BlendChunk::create();

                blendc->setSrcFactor (GL_SRC_ALPHA);
                blendc->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    
                cmat->addChunk(blendc);
            }
        }
    }

    return Action::Continue;
}
#endif

/*-------------------------------------------------------------------------*/
/*                           Member                                        */

void VRMLFile::initIntExtFieldTypeMapper(void)
{
    Self::setIntExtMapping(SFBool::getClassType().getId(),
                           ScanParseSkel::OSGsfBool);

    Self::setIntExtMapping(SFColor3f::getClassType().getId(),
                           ScanParseSkel::OSGsfColor);

    Self::setIntExtMapping(SFReal32::getClassType().getId(),
                           ScanParseSkel::OSGsfFloat);

    Self::setIntExtMapping(SFUnrecImagePtr::getClassType().getId(),
                           ScanParseSkel::OSGsfImage);

    Self::setIntExtMapping(SFInt32::getClassType().getId(),
                           ScanParseSkel::OSGsfInt32);

    Self::setIntExtMapping(SFGLenum::getClassType().getId(),
                           ScanParseSkel::OSGsfString);


    Self::setIntExtMapping(SFQuaternion::getClassType().getId(),
                           ScanParseSkel::OSGsfRotation);

    Self::setIntExtMapping(SFString::getClassType().getId(),
                           ScanParseSkel::OSGsfString);

    Self::setIntExtMapping(SFTime::getClassType().getId(),
                           ScanParseSkel::OSGsfTime);

    Self::setIntExtMapping(SFVec2f::getClassType().getId(),
                           ScanParseSkel::OSGsfVec2f);

    Self::setIntExtMapping(SFVec2s::getClassType().getId(),
                           ScanParseSkel::OSGsfVec2i);

    Self::setIntExtMapping(SFVec3f::getClassType().getId(),
                           ScanParseSkel::OSGsfVec3f);



    Self::setIntExtMapping(MFColor3f::getClassType().getId(),
                           ScanParseSkel::OSGmfColor);

    Self::setIntExtMapping(MFReal32::getClassType().getId(),
                           ScanParseSkel::OSGmfFloat);

    Self::setIntExtMapping(MFInt32::getClassType().getId(),
                           ScanParseSkel::OSGmfInt32);

    Self::setIntExtMapping(MFGLenum::getClassType().getId(),
                           ScanParseSkel::OSGmfString);

    Self::setIntExtMapping(MFQuaternion::getClassType().getId(),
                           ScanParseSkel::OSGmfRotation);

    Self::setIntExtMapping(MFString::getClassType().getId(),
                           ScanParseSkel::OSGmfString);

    Self::setIntExtMapping(MFTime::getClassType().getId(),
                           ScanParseSkel::OSGmfTime);

    Self::setIntExtMapping(MFVec3f::getClassType().getId(),
                           ScanParseSkel::OSGmfVec3f);

    Self::setIntExtMapping(MFVec2f::getClassType().getId(),
                           ScanParseSkel::OSGmfVec2f);


    Self::setIntExtMapping(SFUnrecFieldContainerPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(MFUnrecFieldContainerPtr::getClassType().getId(),
                           ScanParseSkel::OSGmfNode);

    Self::setIntExtMapping(SFUnrecNodePtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(MFUnrecChildNodePtr::getClassType().getId(),
                           ScanParseSkel::OSGmfNode);

    /* To Base Type Mappings */

    Self::setIntExtMapping(SFUInt8::getClassType().getId(),
                           ScanParseSkel::OSGsfInt32);

    Self::setIntExtMapping(MFUInt8::getClassType().getId(),
                           ScanParseSkel::OSGmfInt32);

    Self::setIntExtMapping(SFUInt32::getClassType().getId(),
                           ScanParseSkel::OSGsfInt32);

    Self::setIntExtMapping(MFUInt32::getClassType().getId(),
                           ScanParseSkel::OSGmfInt32);

    /* To Node Mappings */

    Self::setIntExtMapping(SFUnrecNodeCorePtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFUnrecMaterialPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    // AMZ
#if 0
    Self::setIntExtMapping(SFGeoPTypesPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoIndicesPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoPLengthsPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoColorsPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoPositionsPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoNormalsPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);

    Self::setIntExtMapping(SFGeoTexCoordsPtr::getClassType().getId(),
                           ScanParseSkel::OSGsfNode);
#endif
    Self::setIntExtMapping(MFUnrecStateChunkPtr::getClassType().getId(),
                           ScanParseSkel::OSGmfNode);

    //SFAttachmentMap
    Self::setIntExtMapping(SFAttachmentPtrMap::getClassType().getId(),
                           ScanParseSkel::OSGmfNode);

    /* extended types */

    Self::setIntExtMapping(SFMatrix::getClassType().getId(),
                           ScanParseSkel::OSGsfMatrix);

    Self::setIntExtMapping(SFPnt3f::getClassType().getId(),
                           ScanParseSkel::OSGsfPnt3f);

    Self::setIntExtMapping(MFPnt3f::getClassType().getId(),
                           ScanParseSkel::OSGmfPnt3f);
}


void VRMLFile::initExtIntFieldTypeMapper(void)
{
    Self::setExtIntMapping(ScanParseSkel::OSGsfBool,
                           SFBool::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfColor,
                           SFColor3f::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfFloat,
                           SFReal32::getClassType().getId());

/*
    Self::setExtIntMapping(SFImage::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
                     */

    Self::setExtIntMapping(ScanParseSkel::OSGsfImage,
                           SFUnrecImagePtr::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfInt32,
                           SFInt32::getClassType().getId());


    Self::setExtIntMapping(ScanParseSkel::OSGsfRotation,
                           SFQuaternion::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfString,
                           SFString::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfTime,
                           SFTime::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfVec2f,
                           SFVec2f::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfVec2i,
                           SFVec2s::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfVec3f,
                           SFVec3f::getClassType().getId());



    Self::setExtIntMapping(ScanParseSkel::OSGmfColor,
                           MFColor3f::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfFloat,
                           MFReal32::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfInt32,
                           MFInt32::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfRotation,
                           MFQuaternion::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfString,
                           MFString::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfTime,
                           MFTime::getClassType().getId());


    Self::setExtIntMapping(ScanParseSkel::OSGmfVec3f,
                           MFVec3f::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfVec2f,
                           MFVec2f::getClassType().getId());


    Self::setExtIntMapping(ScanParseSkel::OSGsfNode,
                           SFUnrecFieldContainerPtr::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfNode,
                           MFUnrecFieldContainerPtr::getClassType().getId());


    /* extended types */

    Self::setExtIntMapping(ScanParseSkel::OSGsfMatrix,
                           SFMatrix::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGsfPnt3f,
                           SFPnt3f::getClassType().getId());

    Self::setExtIntMapping(ScanParseSkel::OSGmfPnt3f,
                           MFPnt3f::getClassType().getId());
}

/* remove this, if there is a general methode to find containers */
FieldContainer *VRMLFile::findFCByName(const Char8 *szName,
                                             Node  *pNode)
{
    MFUnrecNodePtr::const_iterator i;

    FieldContainer *pFC       = NULL;

#if 0
    Name           *pNodename = NULL;
    NodeCore       *pCore     = NULL;
    // check if name matches nodename

    pNodename =
        dynamic_cast<NamePtr>(
            pNode->findAttachment(Name::getClassType().getGroupId()));

    if(pNodename != NullFC)
    {
        if(strcmp(szName, pNodename->getFieldPtr()->getValue().c_str())==0)
            return pNode;
    }
    // check if name matches corename

    pCore = pNode->getCore();

    if(pCore != NullFC)
    {
        pNodename = dynamic_cast<NamePtr>(
            pCore->findAttachment(Name::getClassType().getGroupId()));

        if(pNodename != NullFC)
        {
            if(strcmp(szName, pNodename->getFieldPtr()->getValue().c_str())==0)
                return pCore;
        }
    }

    // matching for children
    for(i  = pNode->getMFChildren()->begin();
        i != pNode->getMFChildren()->end();
        i++)
    {
        pFC = findFCByName(szName, *i);

        if(pFC != NullFC)
        {
            return pFC;
        }
    }
#endif

    return pFC;
}

FieldContainer *VRMLFile::findReference(const Char8 *szName)
{
    // search reference in this file
    FieldContainer            *returnValue = NULL;

    std::string                szKey       = szName;

    NameContainerMap::iterator mIt         = _nameFCMap.find(szKey);

    if(mIt != _nameFCMap.end())
    {
        returnValue = mIt->second;
    }
    else
    {
        returnValue = findFCByName(szName, _pSceneRootNode);
    }

    return returnValue;
}


#include "OSGVRMLProtos.inl"
