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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGVRMLNodeHelper.h"
#include "OSGSingletonHolder.ins"

#include "OSGFieldDescFactory.h"

#include "OSGScanParseSkel.h"
#include "OSGSceneFileHandler.h"
#include "OSGNameAttachment.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGMaterialGroup.h"
#include "OSGChunkMaterial.h"
#include "OSGGeometry.h"
#include "OSGGeoFunctions.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGBlendChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGImageFileHandler.h"
#include "OSGSimpleGeometry.h"
#include "OSGComponentTransform.h"
#include "OSGInline.h"
#include "OSGSwitch.h"
#include "OSGTimeSensor.h"
#include "OSGVRMLOrientationInterpolator.h"
#include "OSGVRMLPositionInterpolator.h"
#include "OSGVRMLCoordinateInterpolator.h"
#include "OSGVRMLScalarInterpolator.h"

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "VRMLLoader"
#endif

#define OSG_DEBUG_VRML

#ifndef OSG_DO_DOC
#    ifdef OSG_DEBUG_VRML
#        define OSG_VRML_ARG(ARG) ARG
#    else
#        define OSG_VRML_ARG(ARG)
#    endif
#else
#    define OSG_VRML_ARG(ARG) ARG
#endif

OSG_BEGIN_NAMESPACE

OSG_DYNFIELDATTACHMENT_INST(VRMLGenericAttDesc)

OSG_SINGLETON_INST(VRMLNodeHelperFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<VRMLNodeHelperFactoryBase>;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelperFactoryBase::RegisterHelper::RegisterHelper(
          CreateHelper       fCreate, 
    const Char8             *szNodeName,
          InitFuncF          fStaticInit)
{
    VRMLNodeHelperFactory::the()->registerNodeHelper(fCreate, 
                                                     szNodeName);

    if(fStaticInit)
        addPostFactoryInitFunction(fStaticInit);
}


VRMLNodeHelperFactoryBase::VRMLNodeHelperFactoryBase(void) :
    _mRegisteredNodeHelperHash()
{
}

VRMLNodeHelperFactoryBase::~VRMLNodeHelperFactoryBase(void)
{
}

void VRMLNodeHelperFactoryBase::registerNodeHelper(      
          CreateHelper       fHelper,
    const Char8             *szNodeName)
{
    if(szNodeName == NULL || fHelper == NULL) 
        return;

    NameHelperCreateMap::iterator mNodeHelperIt =
        _mRegisteredNodeHelperHash.find(szNodeName);
  

    if(mNodeHelperIt == _mRegisteredNodeHelperHash.end())
    {
        _mRegisteredNodeHelperHash[szNodeName] = fHelper;

        PINFO << "Helper registered for "
              << szNodeName
              << std::endl;
    }
    else
    {
        PWARNING << "Helper already registered for %s "
                 << szNodeName
                 << std::endl;
    }
}

VRMLNodeHelper *VRMLNodeHelperFactoryBase::createHelper(
    const Char8 *szNodeName)
{
    if(szNodeName == NULL) 
        return NULL;

    NameHelperCreateMap::iterator mNodeHelperIt =
        _mRegisteredNodeHelperHash.find(szNodeName);
  

    if(mNodeHelperIt != _mRegisteredNodeHelperHash.end())
    {
        return (*mNodeHelperIt).second();
    }
    else
    {
        return NULL;
    }
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

UInt32 VRMLNodeHelper::_uiIndent = 0;

/*-------------------------------------------------------------------------*/
/*                            Static Get                                   */

UInt32 VRMLNodeHelper::getIndent(void)
{
    return _uiIndent;
}

void VRMLNodeHelper::incIndent(void)
{
    _uiIndent += 4;
}

void VRMLNodeHelper::decIndent(void)
{
    if(_uiIndent < 4)
    {
//        PWARNING << "Indent smaller 4 decremented" << std::endl;

        _uiIndent = 4;
    }

    _uiIndent -= 4;
}

void VRMLNodeHelper::resetIndent(void)
{
    _uiIndent = 0;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

#define OSG_INIT_DESC(VAR, TYPE, NAME)                              \
    VAR(TYPE::getClassType(),                                       \
        NAME,                                                       \
        "VRML Helper",                                              \
        0,                                                          \
        0,                                                          \
        true,                                                       \
        Field::SFDefaultFlags,                                      \
        static_cast<FieldEditMethodSig>(&Node::invalidEditField),   \
        NULL)

VRMLNodeHelper::VRMLNodeHelper(void) :
    _bProtoInterfaceDone(false ),
    _pGenAttProto       (NULL  ),
    _pNodeProto         (NULL  ),
    _pNodeCoreProto     (NULL  ),

    OSG_INIT_DESC(_sfVec3fDesc,   
                  SFVec3f,             
                  "sfVec3fHelperDesc"  ),

    OSG_INIT_DESC(_sfFCPtrDesc,  
                  SFUnrecFieldContainerPtr, 
                  "sfFCPtrHelperDesc"  ),

    OSG_INIT_DESC(_sfImagePtrDesc,  
                  SFUnrecImagePtr, 
                  "sfImageHelperDesc"  ),

    OSG_INIT_DESC(_sfReal32Desc,
                  SFReal32,            
                  "sfReal32HelperDesc" ),

    OSG_INIT_DESC(_sfColor3fDesc, 
                  SFColor3f,           
                  "sfColor3fHelperDesc"),

    OSG_INIT_DESC(_mfStringDesc, 
                  MFString,            
                  "mfStringHelperDesc" ),

    OSG_INIT_DESC(_sfBoolDesc,
                  SFBool,              
                  "sfBoolDesc"         )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLNodeHelper::~VRMLNodeHelper(void)
{
    _pNodeProto     = NULL;
    _pNodeCoreProto = NULL;
    _pGenAttProto   = NULL;
}

/*-------------------------------------------------------------------------*/
/*                              Helper                                     */


void VRMLNodeHelper::reset(void)
{
}


/*-------------------------------------------------------------------------*/
/*                                Field                                    */

FieldContainerTransitPtr VRMLNodeHelper::beginNode(
    const Char8             *szTypename,
    const Char8             *szName,
          FieldContainer    *pCurrentFC)
{
    FieldContainerUnrecPtr returnValue = NULL;
    NodeUnrecPtr           pNode       = NULL;
    NodeCoreUnrecPtr       pCore       = NULL;
    VRMLGenericAttUnrecPtr pAtt        = NULL;

    if(_pNodeProto != NULL)
    {
        returnValue = _pNodeProto->shallowCopy();

        if(_pNodeCoreProto != NULL)
        {
            FieldContainerTransitPtr pCoreClone 
                = _pNodeCoreProto->shallowCopy();

            pNode = dynamic_pointer_cast<Node    >(returnValue);
            pCore = dynamic_pointer_cast<NodeCore>(pCoreClone );

            pNode->setCore(pCore);
        }

        if(_pGenAttProto != NULL)
        {
            FieldContainer *pAttClone = _pGenAttProto->clone();

            pAtt = dynamic_cast<VRMLGenericAtt *>(pAttClone);

            OSG_ASSERT(pAttClone == pAtt);

            if(pAtt != NULL)
            {
                pAtt->setVrmlNodeTypename(szTypename);
                pAtt->setInternal        (true);
            }

            if(pCore != NULL)
            {
                pCore->addAttachment(pAtt);
            }
            else
            {
                AttachmentContainer *pAttCnt = 
                    dynamic_pointer_cast<AttachmentContainer>(returnValue);

                if(pAttCnt != NULL)
                {
                    pAttCnt->addAttachment(pAtt);
                }
            }
        }
    }

    return FieldContainerTransitPtr(returnValue);
}

void VRMLNodeHelper::endNode(FieldContainer *)
{
}

void VRMLNodeHelper::mapFieldname(const std::string &, std::string &)
{
}

/*-------------------------------------------------------------------------*/
/*                              Prototypes                                 */

void VRMLNodeHelper::init(const Char8 *szName)
{
    _bProtoInterfaceDone = false;
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

bool VRMLNodeHelper::prototypeAddField(const Char8  *szFieldType,
                                       const UInt32  uiFieldTypeId,
                                       const Char8  *szFieldName)
{
    bool returnValue = false;


    GetFieldHandlePtr pField = getField(_pNodeProto,
                                        _pNodeCoreProto,
                                        _pGenAttProto,
                                         szFieldName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLNodeDesc::prototypeAddField | getField "
          << szFieldName
          << "  returned : "
          << pField
          << std::endl;
#endif

    if(pField == NULL || pField->isValid() == false)
    {
        FieldDescriptionBase *pDesc = getFieldDescription(szFieldName,
                                                          uiFieldTypeId);

        if(pDesc != NULL && _pGenAttProto != NULL)
        {
            _pGenAttProto->addField(*pDesc);

            pField = getField(_pNodeProto,
                              _pNodeCoreProto,
                              _pGenAttProto,
                               szFieldName);

            delete pDesc;
        }

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLNodeDesc::prototypeAddField | field added : "
              << szFieldType
              << " "
              << uiFieldTypeId
              << " "
              << szFieldName
              << " "
              << pField
              << std::endl;
#endif

        returnValue = (pField != NULL && pField->isValid());
    }
    else
    {
#ifdef OSG_DEBUG_VRML
        incIndent();
        indentLog(getIndent(), PINFO);
#endif
        PINFO << "VRMLNodeDesc::prototypeAddField | "
              << "Could not add field "
              << szFieldName
              << " a second time"
              << std::endl;

#ifdef OSG_DEBUG_VRML
        decIndent();
#endif
    }

    return returnValue;
}

void VRMLNodeHelper::endProtoInterface(void)
{
    _bProtoInterfaceDone = true;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLNodeHelper::getFieldAndDesc(      FieldContainer       * pFC,
                                     const Char8                * szFieldname,
                                           FieldContainer       *&pFieldFC,
                                           EditFieldHandlePtr    &pField,
                                     const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    FieldContainer *pTmpFC    = NULL;
    Node           *pNode     = NULL;
    NodeCore       *pNodeCore = NULL;

    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLNodeHelper::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;

    incIndent();
#endif

    pDesc = pFC->getFieldDescription(szFieldname);

    if(pDesc != NULL)
    {
        pFieldFC = pFC;
        pField   = pFC->editField(szFieldname);
    }
    else
    {
        if(pFC->getType().isNode() == true)
        {
            pNode     = dynamic_cast<Node *>(pFC);
            
            pNodeCore = pNode->getCore();

            if(pNodeCore != NULL)
            {
                pDesc = pNodeCore->getFieldDescription(szFieldname);

#ifdef OSG_DEBUG_VRML
                indentLog(getIndent(), PINFO);
                PINFO << "Got this from nodecore : " 
                      << pDesc 
                      << std::endl;
#endif

                if(pDesc != NULL)
                {
                    pFieldFC = pNodeCore;
                    pField   = pNodeCore->editField(szFieldname);
                }
                else
                {
                    pTmpFC = pNode->findAttachment(
                        VRMLGenericAtt::getClassType().getGroupId());

                    if(pTmpFC != NULL)
                    {
                        pDesc = pTmpFC->getFieldDescription(szFieldname);
                    }

#ifdef OSG_DEBUG_VRML
                    indentLog(getIndent(), PINFO);
                    PINFO << "Got this from node attachment : " 
                          << pDesc << std::endl;
#endif

                    if(pDesc == NULL)
                    {
                        pTmpFC =
                            pNodeCore->findAttachment(
                                VRMLGenericAtt::getClassType().getGroupId());
                        
                        if(pTmpFC != NULL)
                        {
                            pDesc = pTmpFC->getFieldDescription(szFieldname);
                        }

#ifdef OSG_DEBUG_VRML
                        indentLog(getIndent(), PINFO);
                        PINFO << "Got this from nodecore attachment : "
                              << pDesc << std::endl;
#endif
                    }

                    if(pDesc != NULL)
                    {
                        pFieldFC = pTmpFC;
                        pField   = pTmpFC->editField(szFieldname);
                    }
                }
            }
            else
            {
                if(pDesc == NULL)
                {
                    pTmpFC =
                        pNode->findAttachment(
                            VRMLGenericAtt::getClassType().getGroupId());
                    
                    if(pTmpFC != NULL)
                    {
                        pDesc = pTmpFC->getFieldDescription(szFieldname);
                    }
                    
#ifdef OSG_DEBUG_VRML
                    indentLog(getIndent(), PINFO);
                    PINFO << "Got this from node (no core) attachment : "
                          << pDesc << std::endl;
#endif
                }
                
                if(pDesc != NULL)
                {
                    pFieldFC = pTmpFC;
                    pField   = pTmpFC->editField(szFieldname);
                }
            }
        }
        else if(pFC->getType().isNodeCore() == true)
        {
            pNodeCore = dynamic_cast<NodeCore *>(pFC);

            pTmpFC = pNodeCore->findAttachment(
                VRMLGenericAtt::getClassType().getGroupId());

            if(pTmpFC != NULL)
            {
                pDesc = pTmpFC->getFieldDescription(szFieldname);
            }
            
            if(pDesc != NULL)
            {
                pFieldFC = pTmpFC;
                pField   = pTmpFC->editField(szFieldname);
            }
            
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from nodecore attachment : "
                  << pDesc << std::endl;
#endif
        }
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

GetFieldHandlePtr VRMLNodeHelper::getField(      FieldContainer *pFC1,
                                                 FieldContainer *pFC2,
                                                 VRMLGenericAtt *pGenAtt,
                                           const Char8          *szFieldname)
{
    GetFieldHandlePtr returnValue;

    if(szFieldname == NULL)
    {
        return returnValue;
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLNodeDesc::getField " << std::endl;

    incIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "Trying to find field : " << szFieldname << std::endl;
#endif

    if(pFC1 != NULL)
    {
        returnValue = pFC1->getField(szFieldname);
    }

#ifdef OSG_DEBUG_VRML
    incIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "Got this from node : " << returnValue << std::endl;
#endif

    if(returnValue == NULL)
    {
        if(pFC2 != NULL)
        {
            returnValue = pFC2->getField(szFieldname);
            
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from nodecore : " << returnValue << std::endl;
#endif
        }
        else
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "No core to check" << std::endl;
#endif
        }

        
        if(returnValue == NULL)
        {
            if(pGenAtt != NULL)
            {
                returnValue = pGenAtt->getField(szFieldname);
            }
            
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from attachment : " << returnValue << std::endl;
#endif
        }
    }


#ifdef OSG_DEBUG_VRML
    decIndent();
    decIndent();
#endif

    return returnValue;
}


void VRMLNodeHelper::getField(const Char8                * szFieldname,
                                    FieldContainer       *&pFieldFC,
                                    EditFieldHandlePtr    &pField,
                              const FieldDescriptionBase *&pDesc      )
{
    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(szFieldname == NULL)
    {
        return;
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLNodeDesc::getField " << std::endl;

    incIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "Trying to find field : " << szFieldname << std::endl;
#endif

    if(_pNodeProto != NULL)
    {
        pFieldFC = _pNodeProto;
        pField   = _pNodeProto->editField          (szFieldname);
        pDesc    = _pNodeProto->getFieldDescription(szFieldname);
    }

#ifdef OSG_DEBUG_VRML
    incIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "Got this from node : " << pDesc << " " << pField << std::endl;
#endif

    if(pDesc == NULL)
    {
        if(_pNodeCoreProto != NULL)
        {
            pFieldFC = _pNodeCoreProto;
            pField   = _pNodeCoreProto->editField          (szFieldname);
            pDesc    = _pNodeCoreProto->getFieldDescription(szFieldname);

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from nodecore : "
                  << pDesc
                  << " "
                  << pField
                  << std::endl;
#endif
        }
        else
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "No core to check" << std::endl;
#endif
        }


        if(pDesc == NULL)
        {
            if(_pGenAttProto != NULL)
            {
                pFieldFC = _pGenAttProto;
                pField   = _pGenAttProto->editField          (szFieldname);
                pDesc    = _pGenAttProto->getFieldDescription(szFieldname);
            }

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from attachment : "
                  << pDesc
                  << " "
                  << pField
                  << std::endl;
#endif
        }
    }


    if(pDesc == NULL)
    {
        pFieldFC = NULL;
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
    decIndent();
#endif
}


FieldDescriptionBase *VRMLNodeHelper::getFieldDescription(
    const Char8  *szFieldName,
    const UInt32  uiFieldTypeId)
{
    FieldDescriptionBase *returnValue = NULL;

    returnValue = FieldDescFactory::the()->createIdx(
        uiFieldTypeId,
        szFieldName,
        static_cast<OSG::FieldIndexEditMethodSig>(
            &VRMLGenericAtt::editDynamicField),
        static_cast<OSG::FieldIndexGetMethodSig >(
            &VRMLGenericAtt::getDynamicField));
    

    if(returnValue == NULL)
    {
        FWARNING(("could not create field desc for %s (%d)\n",
                  szFieldName,
                  uiFieldTypeId));
    }

    return returnValue;
}

void VRMLNodeHelper::addFieldValue(      EditFieldHandlePtr    pField,
                                   const FieldDescriptionBase *pFieldDesc,
                                   const Char8                *szFieldVal)
{
    if(pField != NULL && pField->isValid() == true)
    {
        pField->pushValueFromCString(szFieldVal);
    }
}

void VRMLNodeHelper::addImageValue(      EditFieldHandlePtr    ,
                                   const FieldDescriptionBase *,
                                         Image                *    )
{
    FWARNING(("addImageValue not caught, something is strange\n"));
}

void VRMLNodeHelper::setContainerFieldValue(      
          FieldContainer       *pFC,
    const FieldDescriptionBase *pFieldDesc,
          FieldContainer       *pFieldFC  )
{
    if((pFieldDesc != NULL  ) && 
       (pFieldFC   != NULL)   )
    {
         FieldContainerPtrSFieldBase::EditHandlePtr pSFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::EditHandle>(
                    pFieldFC->editField(pFieldDesc->getFieldId()));

         FieldContainerPtrMFieldBase::EditHandlePtr pMFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::EditHandle>(
                    pFieldFC->editField(pFieldDesc->getFieldId()));

        if(pSFHandle != NULL && pSFHandle->isValid())
        {
            pSFHandle->set(pFC);
        }
        else if(pMFHandle != NULL && pMFHandle->isValid())
        {
            pMFHandle->add(pFC);
        }
/*
       pFieldFC->pushToField(pFC, 
                              pFieldDesc->getFieldId());
 */
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */








//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLDefaultHelper::create(void)
{
    return new VRMLDefaultHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLDefaultHelper::VRMLDefaultHelper(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLDefaultHelper::~VRMLDefaultHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLDefaultHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GroupHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node ::create();
    _pNodeCoreProto = Group::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

FieldContainerTransitPtr VRMLDefaultHelper::beginNode(
    const Char8          *szTypename,
    const Char8          *szName,
          FieldContainer *pCurrentFC)
{
    FWARNING(("Use default helper for %s, functionality currently not "
              "supported\n", szTypename));

    return Inherited::beginNode(szTypename, szName, pCurrentFC);
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLDefaultHelper::dump(const Char8 *)
{
}





//---------------------------------------------------------------------------
//  Generic Helper with 1:1 mapping
//---------------------------------------------------------------------------

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
  VRMLGenericHelper<Group>::_regHelper(
    &VRMLGenericHelper<Group>::create,
    "Group",
    NULL);

OSG_INST_GENERICVRMLHELPER(Group);

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
  VRMLGenericHelper<ComponentTransform>::_regHelper(
    &VRMLGenericHelper<ComponentTransform>::create,
    "Transform",
    NULL);

OSG_INST_GENERICVRMLHELPER(ComponentTransform);



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLMaterialHelper::create(void)
{
    return new VRMLMaterialHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLMaterialHelper::VRMLMaterialHelper(void) :
     Inherited              (      ),

    _defaultAmbientIntensity(),
    _defaultDiffuseColor    (),
    _defaultEmissiveColor   (),
    _defaultShininess       (),
    _defaultSpecularColor   (),
    _defaultTransparency    (),

    _ambientIntensity       (),
    _diffuseColor           (),
    _emissiveColor          (),
    _shininess              (),
    _specularColor          (),
    _transparency           (),

    _pDefMat                (NULL),
    _pMat                   (NULL),
    
    _szName                 (    )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLMaterialHelper::~VRMLMaterialHelper(void)
{
    _pDefMat = NULL;
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLMaterialHelper::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "MaterialDesc::init : " << szName << std::endl;
#endif

}

void VRMLMaterialHelper::reset(void)
{
    _ambientIntensity.setValue(_defaultAmbientIntensity);
    _diffuseColor    .setValue(_defaultDiffuseColor);
    _emissiveColor   .setValue(_defaultEmissiveColor);
    _shininess       .setValue(_defaultShininess);
    _specularColor   .setValue(_defaultSpecularColor);
    _transparency    .setValue(_defaultTransparency);

    _szName          .erase   ();

    _pMat = NULL;
}

Material *VRMLMaterialHelper::getDefaultMaterial(void)
{
    return _pDefMat;
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLMaterialHelper::prototypeAddField(const Char8  *,
                                           const UInt32  ,
                                           const Char8  *szFieldname)
{
    bool bFound = false;

    if(osgStringCaseCmp("ambientIntensity", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("diffuseColor", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("emissiveColor", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("shininess", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("specularColor", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("transparency", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "MaterialDesc::prototypeAddField : add part "
              << szFieldname
              << std::endl;
#endif
        return true;
    }
    else
    {
        return false;
    }
}

void VRMLMaterialHelper::endProtoInterface(void)
{
    Color4f               cCol;
    MaterialChunkUnrecPtr pMatChunk;

    cCol.setValuesRGBA(_defaultDiffuseColor    .getValue().red() *
                       _defaultAmbientIntensity.getValue(),
                       _defaultDiffuseColor    .getValue().green() *
                       _defaultAmbientIntensity.getValue(),
                       _defaultDiffuseColor    .getValue().blue() *
                       _defaultAmbientIntensity.getValue(),
                       1.f - _defaultTransparency    .getValue());

    _pDefMat = ChunkMaterial::create();

    pMatChunk = MaterialChunk::create();

    pMatChunk->setAmbient(cCol);

    cCol.setValuesRGBA   (_defaultDiffuseColor.getValue()[0],
                          _defaultDiffuseColor.getValue()[1],
                          _defaultDiffuseColor.getValue()[2],
                          1.f - _defaultTransparency.getValue());

    pMatChunk->setDiffuse(cCol);

    cCol.setValuesRGBA    (_defaultSpecularColor.getValue()[0],
                           _defaultSpecularColor.getValue()[1],
                           _defaultSpecularColor.getValue()[2],
                           1.f - _defaultTransparency.getValue());
    pMatChunk->setSpecular(cCol);

    pMatChunk->setShininess(_defaultShininess.getValue() * 128.f);

    cCol.setValuesRGBA    (_defaultEmissiveColor.getValue()[0],
                           _defaultEmissiveColor.getValue()[1],
                           _defaultEmissiveColor.getValue()[2],
                           1.f - _defaultTransparency.getValue());
    pMatChunk->setEmission(cCol);

    _pDefMat->addChunk(pMatChunk);

    Inherited::endProtoInterface();
}


void VRMLMaterialHelper::getFieldAndDesc(
          FieldContainer       *,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(osgStringCaseCmp("ambientIntensity", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = 
                _sfReal32Desc.createEditHandler(&_defaultAmbientIntensity,
                                                  NULL                   );
        }
        else
        {
            pField = _sfReal32Desc.createEditHandler(&_ambientIntensity,
                                                       NULL            );
        }

        pDesc = &_sfReal32Desc;
    }
    else if(osgStringCaseCmp("diffuseColor", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = _sfColor3fDesc.createEditHandler(&_defaultDiffuseColor,
                                                        NULL               );
        }
        else
        {
            pField = _sfColor3fDesc.createEditHandler(&_diffuseColor,
                                                        NULL        );
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("emissiveColor", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = _sfColor3fDesc.createEditHandler(&_defaultEmissiveColor,
                                                        NULL                );
        }
        else
        {
            pField = _sfColor3fDesc.createEditHandler(&_emissiveColor,
                                                        NULL         );
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("shininess", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = _sfReal32Desc.createEditHandler(&_defaultShininess,
                                                       NULL            );
        }
        else
        {
            pField = _sfReal32Desc.createEditHandler(&_shininess,
                                                       NULL     );
        }

        pDesc = &_sfReal32Desc;
    }
    else if(osgStringCaseCmp("specularColor", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = _sfColor3fDesc.createEditHandler(&_defaultSpecularColor,
                                                        NULL                );
        }
        else
        {
            pField = _sfColor3fDesc.createEditHandler(&_specularColor,
                                                        NULL         );
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("transparency", szFieldname) == 0)
    {
        pFieldFC = NULL;

        if(_bProtoInterfaceDone == false)
        {
            pField = _sfReal32Desc.createEditHandler(&_defaultTransparency,
                                                       NULL               );
        }
        else
        {
            pField = _sfReal32Desc.createEditHandler(&_transparency,
                                                       NULL        );
        }

        pDesc = &_sfReal32Desc;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerTransitPtr VRMLMaterialHelper::beginNode(
    const Char8            *,
    const Char8            *szName,
          FieldContainer   *  )
{
    reset();

    _pMat = MaterialChunk::create();

    _szName = (szName != NULL) ? szName : "";

    return FieldContainerTransitPtr(_pMat);
}

void VRMLMaterialHelper::endNode(FieldContainer *)
{
    if(_pMat != NULL)
    {
        Color4f cCol;

        cCol.setValuesRGBA (_diffuseColor    .getValue().red() *
                            _ambientIntensity.getValue(),
                            _diffuseColor    .getValue().green() *
                            _ambientIntensity.getValue(),
                            _diffuseColor    .getValue().blue() *
                            _ambientIntensity.getValue(),
                            1.f - _transparency.getValue());

        _pMat->setAmbient  (cCol);

        cCol.setValuesRGBA (_diffuseColor.getValue()[0],
                            _diffuseColor.getValue()[1],
                            _diffuseColor.getValue()[2],
                            1.f - _transparency.getValue());
        _pMat->setDiffuse  (cCol);

        cCol.setValuesRGBA (_specularColor.getValue()[0],
                            _specularColor.getValue()[1],
                            _specularColor.getValue()[2],
                            1.f - _transparency.getValue());
        _pMat->setSpecular (cCol);

        _pMat->setShininess(_shininess.getValue() * 128.f );

        cCol.setValuesRGBA (_emissiveColor.getValue()[0],
                            _emissiveColor.getValue()[1],
                            _emissiveColor.getValue()[2],
                            1.f - _transparency.getValue());
        _pMat->setEmission (cCol);

    }
}

/*-------------------------------------------------------------------------*/
/*                            Type Specific                                */

const std::string &VRMLMaterialHelper::getName(void) const
{
    return _szName;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLMaterialHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper VRMLMaterialHelper::_regHelper(
    &VRMLMaterialHelper::create,
    "Material",
    NULL);





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLShapeHelper::create(void)
{
    return new VRMLShapeHelper();
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLShapeHelper::VRMLShapeHelper(void) :
     Inherited      (    ),
    _pMaterialHelper(NULL)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLShapeHelper::~VRMLShapeHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLShapeHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ShapeHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node         ::create();
    _pNodeCoreProto = MaterialGroup::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

void VRMLShapeHelper::setMaterialHelper(VRMLMaterialHelper *pMaterialHelper)
{
    _pMaterialHelper = pMaterialHelper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLShapeHelper::prototypeAddField(const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldname)
{
    bool returnValue = false;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLShapeHelper::prototypeAddField | add request : "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return false;

    incIndent();

    if(osgStringCaseCmp("geometry", szFieldname) == 0)
    {
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeHelper::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << std::endl;
#endif
    }

    if(osgStringCaseCmp("appearance", szFieldname) == 0)
    {
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);

        PINFO << "VRMLShapeHelper::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << std::endl;
#endif
    }

    if(returnValue == false)
    {
        returnValue =  Inherited::prototypeAddField(szFieldType,
                                                    uiFieldTypeId,
                                                    szFieldname);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif

    return returnValue;
}

void VRMLShapeHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLShapeHelper::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;

    incIndent();
#endif

    if(osgStringCaseCmp("geometry", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeHelper::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif
        pFieldFC = pFC;
        pField   = pFC->editField("children");
        pDesc    = pFC->getFieldDescription("children");
    }
    else if(osgStringCaseCmp("appearance", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeHelper::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        Node *pNode = dynamic_cast<Node *>(pFC);

        if(pNode != NULL)
        {
            if(pNode->getCore() != NULL)
            {
                pFieldFC = pNode->getCore();
                pField   = pNode->getCore()->editField("material");
                pDesc    = pNode->getCore()->getFieldDescription("material");
            }
        }
        else
        {
            Inherited::getFieldAndDesc(pFC,
                                       szFieldname,
                                       pFC,
                                       pField,
                                       pDesc);
        }
    }
    else
    {
        Inherited::getFieldAndDesc(pFC,
                                   szFieldname,
                                   pFC,
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */


void VRMLShapeHelper::endNode(FieldContainer *pFC)
{
    if(pFC != NULL)
    {
        Node *pNode = dynamic_cast<Node *>(pFC);

        if(pNode != NULL && pNode->getCore() == NULL)
        {
            PWARNING << "warning empty material, using default\n" << std::endl;

            MaterialGroupUnrecPtr pMatGroup = MaterialGroup::create();

            pMatGroup->setMaterial(_pMaterialHelper->getDefaultMaterial());

            pNode->setCore(pMatGroup);
        }
        else
        {
            MaterialGroup *pMatGroup;

            pMatGroup = dynamic_cast<MaterialGroup *>(pNode->getCore());

            if(pMatGroup != NULL)
            {
                if(pMatGroup->getMaterial() == NULL)
                {
                    pMatGroup->setMaterial(
                        _pMaterialHelper->getDefaultMaterial());
                }
            }
        }
    }

#ifdef OSG_DEBUG_VRML
//    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Shape " << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLShapeHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper VRMLShapeHelper::_regHelper(
    &VRMLShapeHelper::create,
    "Shape",
    NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLAppearanceHelper::create(void)
{
    return new VRMLAppearanceHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLAppearanceHelper::VRMLAppearanceHelper(void) :
     Inherited      (    ),
    _pMaterialHelper(NULL)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLAppearanceHelper::~VRMLAppearanceHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLAppearanceHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ApperanceHelper::init : " << szName << std::endl;
#endif

    _pNodeProto    = ChunkMaterial::create();

    _pGenAttProto  = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

void VRMLAppearanceHelper::setMaterialHelper(
    VRMLMaterialHelper *pMaterialHelper)
{
    _pMaterialHelper = pMaterialHelper;
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLAppearanceHelper::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    if(szFieldname == NULL)
        return false;

    if(osgStringCaseCmp("material", szFieldname) == 0)
    {
        return true;
    }
    else if(osgStringCaseCmp("texture", szFieldname) == 0)
    {
        return true;
    }
    else if(osgStringCaseCmp("textureTransform", szFieldname) == 0)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLAppearanceHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLAppearanceHelper::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

    if(szFieldname == NULL)
        return;

    incIndent();

    if(osgStringCaseCmp("material", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif
        pFieldFC = pFC;
        pField   = pFC->editField("chunks");
        pDesc    = pFC->getFieldDescription("chunks");
    }
    else if(osgStringCaseCmp("texture", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceHelper::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pFieldFC = pFC;
        pField   = pFC->editField("chunks");
        pDesc    = pFC->getFieldDescription("chunks");
    }
    else if(osgStringCaseCmp("textureTransform", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pFieldFC = pFC;
        pField   = pFC->editField("chunks");
        pDesc    = pFC->getFieldDescription("chunks");
    }
    else
    {
        Inherited::getFieldAndDesc(pFC,
                                   szFieldname,
                                   pFC,
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */


void VRMLAppearanceHelper::endNode(FieldContainer *pFC)
{
    if(pFC != NULL)
    {
        ChunkMaterial *pChunkMat = dynamic_cast<ChunkMaterial *>(pFC);

        if(pChunkMat != NULL)
        {
            TextureObjChunk *pTexC = 
                dynamic_cast<TextureObjChunk *>(
                    pChunkMat->find(TextureObjChunk::getClassType()));

            TextureEnvChunkUnrecPtr pTexE = 
                dynamic_cast<TextureEnvChunk *>(
                    pChunkMat->find(TextureEnvChunk::getClassType()));
            
         


            if ((pChunkMat->isTransparent()           == true)     ||
                (pTexC                                != NULL && 
                 pTexC->getImage()                    != NULL &&
                 pTexC->getImage()->hasAlphaChannel() == true    ))
            {
                BlendChunkUnrecPtr pBlendChunk = OSG::BlendChunk::create();

                if(pTexC                              != NULL && 
                   pTexC->getImage()                  != NULL &&
                   pTexC->getImage()->isAlphaBinary() == true)
                {
                    pBlendChunk->setAlphaFunc(GL_NOTEQUAL);
                    pBlendChunk->setAlphaValue(0);
                }
                else
                {
                    pBlendChunk->setSrcFactor (GL_SRC_ALPHA);
                    pBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                }

                pChunkMat->addChunk(pBlendChunk);
            }

            if(pTexC != NULL)
            {
                if(pTexE == NULL)
                {
                    pTexE = TextureEnvChunk::create();

                    pChunkMat->addChunk(pTexE);
                }

                MaterialChunk *pMatC = 
                    dynamic_cast<MaterialChunk *>(
                        pChunkMat->find(MaterialChunk::getClassType()));

                if(pMatC == NULL)
                {
                    pTexE->setEnvMode(GL_REPLACE);
                }
                else
                {
                    pTexE->setEnvMode(GL_MODULATE);
                }
            }
        }

        // This works around the problem that MaterialChunks can not have
        // NameAttachments on them (they are attachments themselves).
        //
        // If the ChunkMaterial (which corresponds to the VRML Appearance Node)
        // has no name of its own, the material's name is set instead.
        
        // BEGIN Material name hack
        
        AttachmentContainer *attCon    = 
            dynamic_cast<AttachmentContainer *>(pFC);
        bool                   pushNames = false;

        if(SceneFileHandler::the()->getOptionAs("wrl",
                                                "pushNames",
                                                pushNames) == false)
        {
            pushNames = false;
        }

        if(( attCon                             != NULL ) && 
           ( pushNames                          == true ) && 
           (_pMaterialHelper                    != NULL ) && 
           (_pMaterialHelper->getName().empty() == false)  )
        {        
            FieldContainer *att = attCon->findAttachment(
                Name::getClassType().getGroupId());
            
            if(att != NULL)
            {            
                // ChunkMaterial (Appearance) already has a NameAttachment
                Name *nameAtt = dynamic_cast<Name *>(att);
                
                if(nameAtt != NULL)
                {
                    if(nameAtt->getFieldPtr()->getValue().empty())
                    {
                        nameAtt->editFieldPtr()->getValue().assign(
                            _pMaterialHelper->getName());
                    }
                }
            }
            else
            {
                setName(attCon, _pMaterialHelper->getName());
            }
        }
                
        // END Material name hack

    }


#ifdef OSG_DEBUG_VRML
//    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Appearance " <<  std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                              Field Value                                */

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLAppearanceHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper VRMLAppearanceHelper::_regHelper(
    &VRMLAppearanceHelper::create,
    "Appearance",
    NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLIndexedGeometryHelper::create(void)
{
    return new VRMLIndexedGeometryHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLIndexedGeometryHelper::VRMLIndexedGeometryHelper(void) :
     Inherited      (                        ),
    _bIsFaceSet     (false                   ),
    _uiPropertyIndex(Geometry::PositionsIndex)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLIndexedGeometryHelper::~VRMLIndexedGeometryHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLIndexedGeometryHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node      ::create();
    _pNodeCoreProto = Geometry  ::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);

    if(osgStringCaseCmp("IndexedFaceSet", szName) == 0)
    {
        _bIsFaceSet = true;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLIndexedGeometryHelper::prototypeAddField(const Char8  *szFieldType,
                                                  const UInt32  uiFieldTypeId,
                                                  const Char8  *szFieldname)
{
    bool bFound = false;

    if(szFieldname == NULL)
        return false;

    if(osgStringCaseCmp("coord", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("normal", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("color", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("texCoord", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::prototypeAddField : internal "
              << szFieldname << std::endl;
#endif

        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}


void VRMLIndexedGeometryHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoDesc::getFieldAndDesc : request "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

    Node *pNode = dynamic_cast<Node *>(pFC);

    if(pNode == NULL)
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCore *pNodeCore = pNode->getCore();

    Geometry *pGeo      = dynamic_cast<Geometry *>(pNodeCore);

    if(pGeo == NULL)
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Geo" << std::endl;
        return;
    }

    if(osgStringCaseCmp("coord", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pFieldFC = pGeo;
        pField.reset();
        pDesc    = &_sfFCPtrDesc;

        _uiPropertyIndex = Geometry::PositionsIndex;
    }
    else if(osgStringCaseCmp("normal", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pFieldFC = pGeo;
        pField.reset();
        pDesc    = &_sfFCPtrDesc;

        _uiPropertyIndex = Geometry::NormalsIndex;
    }
    else if(osgStringCaseCmp("color", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pFieldFC = pGeo;
        pField.reset();
        pDesc    = &_sfFCPtrDesc;

        _uiPropertyIndex = Geometry::ColorsIndex;
    }
    else if(osgStringCaseCmp("texCoord", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pFieldFC = pGeo;
        pField.reset();
        pDesc    = &_sfFCPtrDesc;

        _uiPropertyIndex = Geometry::TexCoordsIndex;
    }
    else
    {
        Inherited::getFieldAndDesc(pGeo,
                                   szFieldname,
                                   pFieldFC,
                                   pField,
                                   pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */



void VRMLIndexedGeometryHelper::endNode(FieldContainer *pFC)
{
    Node     *pNode = NULL;
    Geometry *pGeo  = NULL;

    if(pFC == NULL)
    {
        return;
    }

    pNode = dynamic_cast<Node *>(pFC);

    if(pNode == NULL)
    {
        return;
    }

    pGeo = dynamic_cast<Geometry *>(pNode->getCore());

    if(pGeo == NULL)
    {
        return;
    }

          EditFieldHandlePtr    pField;
    const FieldDescriptionBase *pDesc    = NULL;
          FieldContainer       *pDummyFC = NULL;


    MFInt32  *pCoordIndex           = NULL;
    MFInt32  *pNormalIndex          = NULL;
    MFInt32  *pColorIndex           = NULL;
    MFInt32  *pTexCoordIndex        = NULL;
    SFBool   *pConvex               = NULL;
    SFBool   *pCcw                  = NULL;
    SFBool   *pNormalPerVertex      = NULL;
    SFBool   *pColorPerVertex       = NULL;
    SFReal32 *pCreaseAngle          = NULL;

    Inherited::getFieldAndDesc(pFC,
                               "coordIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        MFInt32::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<MFInt32::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pCoordIndex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        MFInt32::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<MFInt32::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pNormalIndex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        MFInt32::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<MFInt32::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pColorIndex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "texCoordIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        MFInt32::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<MFInt32::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pTexCoordIndex = pValField->getField();
        }
    }



    Inherited::getFieldAndDesc(pFC,
                               "convex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        SFBool::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pConvex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "ccw",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        SFBool::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pCcw = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalPerVertex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        SFBool::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pNormalPerVertex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorPerVertex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        SFBool::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pColorPerVertex = pValField->getField();
        }
    }

    Inherited::getFieldAndDesc(pFC,
                               "creaseAngle",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        SFReal32::EditHandlePtr pValField = 
            boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

        if(pValField != NULL && pValField->isValid())
        {
            pCreaseAngle = pValField->getField();
        }
    }

    if(_bIsFaceSet == true)
    {
        if(pCoordIndex         != NULL &&
           pCoordIndex->size() >     2 &&
           pNormalIndex        != NULL &&
           pColorIndex         != NULL &&
           pTexCoordIndex      != NULL &&
           pConvex             != NULL &&
           pCcw                != NULL &&
           pNormalPerVertex    != NULL &&
           pColorPerVertex     != NULL &&
           pCreaseAngle        != NULL)
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Geo create faceset " << &(*pNode) << std::endl;
#endif

            setIndexFromIndexedX3DData(pGeo,
                                       pCoordIndex     ->getValues(),
                                       pNormalIndex    ->getValues(),
                                       pColorIndex     ->getValues(),
                                       pTexCoordIndex  ->getValues(),
                                       GL_POLYGON,
                                       pConvex         ->getValue() ,
                                       pCcw            ->getValue() ,
                                       pNormalPerVertex->getValue() ,
                                       pColorPerVertex ->getValue() ,
                                       false); // create normal; not yet :)

            //if (pConvex->getValue() == false)
            //   createConvexPrimitives( pGeo );

            // TODO: Need some option _uiOptions param
            //createSharedIndex( pGeo);

            //if((0 != (_uiOptions & VRMLFile::CreateNormals) )    &&
            //   (pGeo->getNormals() == NULL))

            if(pGeo->getNormals() == NULL)
            {
#ifdef OSG_DEBUG_VRML
                indentLog(getIndent(), PINFO);
                PINFO << "Geo create normals " << &(*pNode) << std::endl;
#endif

                OSG::calcVertexNormals(pGeo, pCreaseAngle->getValue());
            }
        }
        else
        {
#if 0  // What's the point of doing that?
            PWARNING << "Invalid geometry replaced by a group" << std::endl;

            GroupPtr pGr = Group::create();

            MFNodePtr           pGeoParents = pGeo->getParents ();
            MFNodePtr::iterator parentsIt   = pGeoParents.begin();
            MFNodePtr::iterator endParents  = pGeoParents.end  ();

            // this makes pGeo invalid!
            while(parentsIt != endParents)
            {
                (*parentsIt)->setCore(pGr);

                ++parentsIt;
            }
            pGeo = NULL;
#endif
        }
    }
    else
    {
        std::vector<Int32> dummyVec;
        bool               dummybool = false;

        if(pCoordIndex         != NULL &&
           pCoordIndex->size() >     1 &&
           pColorIndex         != NULL &&
           pColorPerVertex     != NULL)
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Geo create lineset " << &(*pNode) << std::endl;
#endif

            setIndexFromIndexedX3DData(pGeo,
                                       pCoordIndex    ->getValues(),
                                       dummyVec ,
                                       pColorIndex    ->getValues(),
                                       dummyVec ,
                                       GL_LINES,
                                       dummybool,
                                       dummybool,
                                       dummybool,
                                       pColorPerVertex->getValue() ,
                                       false);  // create normal; not yet :)
        }
        else
        {
#if 0  // What's the point of doing that?
            PWARNING << "Invalid geometry replaced by a group" << std::endl;

            GroupPtr pGr = Group::create();

            MFNodePtr           pGeoParents = pGeo->getParents ();
            MFNodePtr::iterator parentsIt   = pGeoParents.begin();
            MFNodePtr::iterator endParents  = pGeoParents.end  ();

            // this makes pGeo invalid!
            while(parentsIt != endParents)
            {
                (*parentsIt)->setCore(pGr);

                ++parentsIt;
            }
            pGeo = NULL;
#endif
        }
    }

#ifdef OSG_DEBUG_VRML
//    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Geo " << &(*pNode) << std::endl;
#endif
}


void VRMLIndexedGeometryHelper::setContainerFieldValue(      
          FieldContainer       *pFC,
    const FieldDescriptionBase *pFieldDesc,
          FieldContainer       *pFieldFC  )
{
    Geometry          *pGeo     = 
        dynamic_cast<Geometry          *>(pFieldFC);

    GeoVectorProperty *pVecProp = 
        dynamic_cast<GeoVectorProperty *>(pFC);

    if(pGeo != NULL && pVecProp != NULL)
    {
        pGeo->setProperty(pVecProp, _uiPropertyIndex);
    }
    else
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Geo" << std::endl;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLIndexedGeometryHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLIndexedGeometryHelper::_regHelperIFS(
        &VRMLIndexedGeometryHelper::create,
        "IndexedFaceSet",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLIndexedGeometryHelper::_regHelperILS(
        &VRMLIndexedGeometryHelper::create,
        "IndexedLineSet",
        NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLGeometryPartHelper::create(void)
{
    return new VRMLGeometryPartHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryPartHelper::VRMLGeometryPartHelper(void) :
     Inherited     (),

    _szVRMLPartname(),
    _szOSGPartname (),
    _szOSGProtoname()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryPartHelper::~VRMLGeometryPartHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryPartHelper::init(const Char8 *szName)
{
    if(osgStringCaseCmp("Coordinate", szName) == 0)
    {
        _szVRMLPartname = "point";
        _szOSGPartname  = "values";
        _szOSGProtoname = "GeoPnt3fProperty";
    }
    else if(osgStringCaseCmp("Normal", szName) == 0)
    {
        _szVRMLPartname = "vector";
        _szOSGPartname  = "values";
        _szOSGProtoname = "GeoVec3fProperty";
    }
    else if(osgStringCaseCmp("Color", szName) == 0)
    {
        _szVRMLPartname = "color";
        _szOSGPartname  = "values";
        _szOSGProtoname = "GeoColor3fProperty";
    }
    else if(osgStringCaseCmp("TextureCoordinate", szName) == 0)
    {
        _szVRMLPartname = "point";
        _szOSGPartname  = "values";
        _szOSGProtoname = "GeoVec2fProperty";
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoPartDesc::init : "
          << szName << " "
          << _szVRMLPartname << " "
          << _szOSGPartname << " "
          << _szOSGProtoname << " "
          << std::endl;
#endif

    _pNodeProto =
        FieldContainerFactory::the()->createContainer(_szOSGProtoname.c_str());

    if(_pNodeProto == NULL)
    {
        PWARNING << "ERROR no prototype available for "
                 << _szOSGProtoname
                 << std::endl;
    }

    _pGenAttProto = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLGeometryPartHelper::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname)
{
    bool bFound = false;

    if(_szVRMLPartname == szFieldname)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoPartDesc::prototypeAddField : add part "
              << szFieldname
              << std::endl;
#endif

        bFound = true;
    }


    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLGeometryPartHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLGeometryPartDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

    incIndent();

    if(_szVRMLPartname == szFieldname)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGeometryPartDesc::getFieldAndDesc : request internal "
              << szFieldname
              << " return "
              << _szOSGPartname
              << std::endl;
#endif

        pFieldFC = pFC;
        pDesc    = pFC->getFieldDescription(_szOSGPartname.c_str());
        pField   = pFC->editField          (_szOSGPartname.c_str());

        if(pField == NULL)
        {
            PWARNING << "VRMLGeometryPartDesc::getFieldAndDesc : could not"
                     << " map : "
                     << szFieldname
                     << " to "
                     << _szOSGPartname
                     << std::endl;
        }
    }
    else
    {
        Inherited::getFieldAndDesc(pFC,
                                   szFieldname,
                                   pFieldFC,
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

void VRMLGeometryPartHelper::mapFieldname(const std::string &,
                                                std::string &szFieldName)
{
    szFieldName.assign("values");
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryPartHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperCoordinate(
        &VRMLGeometryPartHelper::create,
        "Coordinate",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperNormal(
        &VRMLGeometryPartHelper::create,
        "Normal",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperColor(
        &VRMLGeometryPartHelper::create,
        "Color",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperTexCoordinate(
        &VRMLGeometryPartHelper::create,
        "TextureCoordinate",
        NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLGeometryObjectHelper::create(void)
{
    return new VRMLGeometryObjectHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryObjectHelper::VRMLGeometryObjectHelper(void) :
     Inherited      (          ),
    _eVRMLObjectType(UnknownGeo)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryObjectHelper::~VRMLGeometryObjectHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryObjectHelper::init(const Char8 *szName)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoObjDesc::init : "
          << szName << " "
          << _eVRMLObjectType
          << std::endl;
#endif

    if(osgStringCaseCmp("Box", szName) == 0)
    {
        _eVRMLObjectType = BoxGeo;
    }
    else if(osgStringCaseCmp("Sphere", szName) == 0)
    {
        _eVRMLObjectType = SphereGeo;
    }
    else if(osgStringCaseCmp("Cone", szName) == 0)
    {
        _eVRMLObjectType = ConeGeo;
    }
    else if(osgStringCaseCmp("Cylinder", szName) == 0)
    {
        _eVRMLObjectType = CylinderGeo;
    }
    else if(osgStringCaseCmp("Teapot", szName) == 0)
    {
        _eVRMLObjectType = TeapotGeo;
    }
    else if(osgStringCaseCmp("Plane", szName) == 0)
    {
        _eVRMLObjectType = PlaneGeo;
    }

    _pNodeProto = Node::create();

    if(_pNodeProto == NULL)
    {
        PWARNING << "GeoObjDesc::init : no prototype available" << std::endl;
    }

    _pGenAttProto = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

void VRMLGeometryObjectHelper::endNode(FieldContainer *pFC)
{
          EditFieldHandlePtr    pField;
    const FieldDescriptionBase *pDesc    = NULL;
          FieldContainer       *pDummyFC = NULL;
          Node                 *pNode    = NULL;

    if(pFC == NULL)
        return;

    pNode = dynamic_cast<Node *>(pFC);

    if(pNode == NULL)
        return;

    if(_eVRMLObjectType == BoxGeo)
    {
        Inherited::getFieldAndDesc(pFC,
                                   "size",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFVec3f::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFVec3f::EditHandle>(pField);


            if(pValField != NULL && pValField->isValid())
            {
                SFVec3f *pVec = pValField->getField();

                GeometryUnrecPtr pGeo = makeBoxGeo(pVec->getValue()[0],
                                                   pVec->getValue()[1],
                                                   pVec->getValue()[2],
                                                   1,
                                                   1,
                                                   1);
                
                pNode->setCore(pGeo);
            }
        }
    }
    else if(_eVRMLObjectType == ConeGeo)
    {
        SFReal32 *pBotRad = NULL;
        SFReal32 *pHeight = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pBottom = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "bottomRadius",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pBotRad = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "height",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pHeight = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "side",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFBool::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pSide = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "bottom",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFBool::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pBottom = pValField->getField();
            }
        }

        if(pBotRad != NULL &&
           pHeight != NULL &&
           pSide   != NULL &&
           pBottom != NULL)
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "VRMLGeometryObjectDesc::endNode : Create cone"
                  << std::endl;
#endif

            GeometryUnrecPtr pGeo = makeConeGeo(pHeight->getValue(),
                                                pBotRad->getValue(),
                                                32,
                                                pSide  ->getValue(),
                                                pBottom->getValue());
            
            pNode->setCore(pGeo);
        }
    }
    else if(_eVRMLObjectType == CylinderGeo)
    {
        SFBool   *pBottom = NULL;
        SFReal32 *pHeight = NULL;
        SFReal32 *pRadius = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pTop    = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "bottom",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFBool::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pBottom = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "height",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pHeight = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "radius",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pRadius = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "side",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFBool::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pSide = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "top",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFBool::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFBool::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pTop = pValField->getField();
            }
        }


        if(pBottom != NULL &&
           pHeight != NULL &&
           pRadius != NULL &&
           pSide   != NULL &&
           pTop    != NULL)
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "VRMLGeometryObjectDesc::endNode : Create cylinder"
                  << std::endl;
#endif

            GeometryUnrecPtr pGeo = makeCylinderGeo(pHeight->getValue(),
                                                    pRadius->getValue(),
                                                    32,
                                                    pSide  ->getValue(),
                                                    pTop   ->getValue(),
                                                    pBottom->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(_eVRMLObjectType == SphereGeo)
    {
        SFReal32 *pSize       = NULL;
        SFInt32  *pResolution = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "radius",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pSize = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "resolution",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFInt32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFInt32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pResolution = pValField->getField();
            }
        }

        if(pSize != NULL && pResolution != NULL)
        {
            GeometryUnrecPtr pGeo = 
                makeLatLongSphereGeo(pResolution->getValue(), 
                                     pResolution->getValue() * 2, 
                                     pSize      ->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(_eVRMLObjectType == TeapotGeo)
    {
        SFReal32 *pScale = NULL;
        SFInt32  *pDepth = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "scale",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFReal32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pScale = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "depth",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFInt32::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFInt32::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pDepth = pValField->getField();
            }
        }

        GeometryUnrecPtr pGeo = makeTeapotGeo(
            (pDepth != NULL) ? pDepth->getValue() : 5,
            (pScale != NULL) ? pScale->getValue() : 1.f);

        pNode->setCore(pGeo);

    }
    else if(_eVRMLObjectType == PlaneGeo)
    {
        SFVec2s *pResolution = NULL;
        SFVec2f *pSize       = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "resolution",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFVec2s::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFVec2s::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pResolution = pValField->getField();
            }
        }

        Inherited::getFieldAndDesc(pFC,
                                   "size",
                                   pDummyFC,
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFVec2f::EditHandlePtr pValField = 
                boost::dynamic_pointer_cast<SFVec2f::EditHandle>(pField);

            if(pValField != NULL && pValField->isValid())
            {
                pSize = pValField->getField();
            }
        }

        GeometryUnrecPtr pGeo = makePlaneGeo(
            (pSize       != NULL) ? pSize      ->getValue()[0] : 1.f,
            (pSize       != NULL) ? pSize      ->getValue()[1] : 1.f,
            (pResolution != NULL) ? pResolution->getValue()[0] : 5,
            (pResolution != NULL) ? pResolution->getValue()[1] : 5);

        pNode->setCore(pGeo);

    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryObjectHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperBox(
        &VRMLGeometryObjectHelper::create,
        "Box",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperSphere(
        &VRMLGeometryObjectHelper::create,
        "Sphere",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperCone(
        &VRMLGeometryObjectHelper::create,
        "Cone",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperCylinder(
        &VRMLGeometryObjectHelper::create,
        "Cylinder",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperTeapot(
        &VRMLGeometryObjectHelper::create,
        "Teapot",
        NULL);

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryObjectHelper::_regHelperPlane(
        &VRMLGeometryObjectHelper::create,
        "Plane",
        NULL);



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLTextureHelper::VRMLTextureHelper(void) :
     Inherited     (),

    _defaultRepeatS(),
    _defaultRepeatT(),

    _repeatS       (),
    _repeatT       ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLTextureHelper::~VRMLTextureHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLTextureHelper::prototypeAddField(const Char8  *,
                                          const UInt32  ,
                                          const Char8  *szFieldname)
{
    bool bFound = false;

    if(osgStringCaseCmp("repeatS", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("repeatT", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "ImageTextureDesc::prototypeAddField : add part "
              << szFieldname
              << std::endl;
#endif

        return true;
    }
    else
    {
        return false;
    }
}


void VRMLTextureHelper::getFieldAndDesc(
          FieldContainer       *,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(osgStringCaseCmp("repeatS", szFieldname) == 0)
    {
        if(_bProtoInterfaceDone == false)
        {
            pField = _sfBoolDesc.createEditHandler(&_defaultRepeatS,
                                                     NULL          );
        }
        else
        {
            pField = _sfBoolDesc.createEditHandler(&_repeatS,
                                                     NULL   );
        }

        pDesc = &_sfBoolDesc;
    }
    else if(osgStringCaseCmp("repeatT", szFieldname) == 0)
    {
        if(_bProtoInterfaceDone == false)
        {
            pField = _sfBoolDesc.createEditHandler(&_defaultRepeatT,
                                                     NULL          );
        }
        else
        {
            pField = _sfBoolDesc.createEditHandler(&_repeatT,
                                                     NULL   );
        }
        
        pDesc = &_sfBoolDesc;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerTransitPtr VRMLTextureHelper::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainer    *)
{
    TextureObjChunkTransitPtr returnValue = TextureObjChunk::create();

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Texture " 
          << ((returnValue == NULL) ? "invalid obj" : "valid obj") 
          << std::endl;

    incIndent();
#endif

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    return FieldContainerTransitPtr(returnValue);
}

void VRMLTextureHelper::endNode(FieldContainer *pFC)
{
#if 0
    TextureObjChunk    *pTexture = NULL;

    ImageUnrecPtr       pImage   = NULL;

    pTexture = dynamic_cast<TextureObjChunk *>(pFC);


    if(pTexture != NULL)
    {
        for(UInt32 i = 0; i < _url.size(); ++i)
        {
#ifdef OSG_DEBUG_VRML
            PNOTICE << "VRMLImageTextureDesc::endNode : Reading texture "
                    << _url[i].c_str() << std::endl;
#endif

#ifdef OSG_VRML_IMAGETEXTURE_MAP
            UrlImageMap::iterator mIt = _urlImageMap.find(_url[i]);

            if(mIt != _urlImageMap.end())
            {
                pImage = mIt->second;
            }
            else
            {
                pImage = ImageFileHandler::the()->read(_url[i].c_str());

                if(pImage != NULL)
                {
                    _urlImageMap[_url[i]] = pImage;
                }
            }
#else
            pImage = ImageFileHandler::the()->read(_url[0].c_str());
#endif

            if(pImage != NULL)
                break;
        }

        if(pImage != NULL)
        {
            pImage->setForceAlphaBinary(pImage->calcIsAlphaBinary());

            pTexture->setImage(pImage);

            if(_repeatS.getValue() == true)
            {
                pTexture->setWrapS(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }
            if(_repeatT.getValue() == true)
            {
                pTexture->setWrapT(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapT(GL_CLAMP);
            }
        }
        else
        {
            PWARNING << "VRMLImageTextureDesc::endNode : "
                     << "Couldn't read texture "
                     << _url[0].c_str()
                     << " !!!"
                     << std::endl;
        }
    }
    else
    {
        PWARNING <<  "VRMLImageTextureDesc::endNode : Invalid texture ptr"
                 << std::endl;
    }

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End ImageTexture "
          << _url[0].c_str() << " "
          << _repeatS.getValue()    << " "
          << _repeatT.getValue()    << " "
          << &(*pFC) << std::endl;
#endif
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLTextureHelper::dump(const Char8 *)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLImageTextureHelper::create(void)
{
    return new VRMLImageTextureHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLImageTextureHelper::VRMLImageTextureHelper(void) :
     Inherited     (),

    _defaultURL    (),
    _url           ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLImageTextureHelper::~VRMLImageTextureHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLImageTextureHelper::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname  )
{
    bool bFound = false;

    if(osgStringCaseCmp("url", szFieldname) == 0)
    {
        bFound = true;
    }
    else 
    {
        bFound = Inherited::prototypeAddField(szFieldType, 
                                              uiFieldTypeId, 
                                              szFieldname);
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "ImageTextureDesc::prototypeAddField : add part "
              << szFieldname
              << std::endl;
#endif

        return true;
    }
    else
    {
        return false;
    }
}


void VRMLImageTextureHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(osgStringCaseCmp("url", szFieldname) == 0)
    {
        if(_bProtoInterfaceDone == false)
        {
            pField = _mfStringDesc.createEditHandler(&_defaultURL,
                                                       NULL     );
        }
        else
        {
            pField = _mfStringDesc.createEditHandler(&_url,
                                                       NULL);
        }

        pDesc = &_mfStringDesc;
    }
    else 
    {
        Inherited::getFieldAndDesc(pFC, 
                                   szFieldname, 
                                   pFieldFC,
                                   pField,
                                   pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerTransitPtr VRMLImageTextureHelper::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainer    *pCurrentFC)
{
    FieldContainerTransitPtr returnValue = 
        Inherited::beginNode(szTypename, szName, pCurrentFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin ImageTexture " 
          << ((returnValue == NULL) ? "invalid obj" : "valid obj") 
          << std::endl;

    incIndent();
#endif

    _url.clear();

    return returnValue;
}

void VRMLImageTextureHelper::endNode(FieldContainer *pFC)
{
    TextureObjChunk    *pTexture = NULL;

    ImageUnrecPtr       pImage   = NULL;

    pTexture = dynamic_cast<TextureObjChunk *>(pFC);


    if(pTexture != NULL && _url.size() != 0)
    {

        for(UInt32 i = 0; i < _url.size(); ++i)
        {
#ifdef OSG_DEBUG_VRML
            PNOTICE << "VRMLImageTextureDesc::endNode : Reading texture "
                    << _url[i].c_str() << std::endl;
#endif

#ifdef OSG_VRML_IMAGETEXTURE_MAP
            UrlImageMap::iterator mIt = _urlImageMap.find(_url[i]);

            if(mIt != _urlImageMap.end())
            {
                pImage = mIt->second;
            }
            else
            {
                pImage = ImageFileHandler::the()->read(_url[i].c_str());

                if(pImage != NULL)
                {
                    _urlImageMap[_url[i]] = pImage;
                }
            }
#else
            pImage = ImageFileHandler::the()->read(_url[0].c_str());
#endif

            if(pImage != NULL)
                break;
        }

        if(pImage != NULL)
        {
            pImage->setForceAlphaBinary(pImage->calcIsAlphaBinary());

            pTexture->setImage(pImage);

            if(_repeatS.getValue() == true)
            {
                pTexture->setWrapS(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }
            if(_repeatT.getValue() == true)
            {
                pTexture->setWrapT(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapT(GL_CLAMP);
            }
        }
        else
        {
            PWARNING << "VRMLImageTextureDesc::endNode : "
                     << "Couldn't read texture "
                     << _url[0].c_str()
                     << " !!!"
                     << std::endl;
        }
    }
    else
    {
        PWARNING <<  "VRMLImageTextureDesc::endNode : Invalid texture ptr"
                 << std::endl;
    }

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End ImageTexture "
          << _url[0].c_str() << " "
          << _repeatS.getValue()    << " "
          << _repeatT.getValue()    << " "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLImageTextureHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper VRMLImageTextureHelper::_regHelper(
    &VRMLImageTextureHelper::create,
    "ImageTexture",
    NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLPixelTextureHelper::create(void)
{
    return new VRMLPixelTextureHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLPixelTextureHelper::VRMLPixelTextureHelper(void) :
     Inherited(    ),
    _pImage   (NULL)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLPixelTextureHelper::~VRMLPixelTextureHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLPixelTextureHelper::addImageValue(     
          EditFieldHandlePtr    ,
    const FieldDescriptionBase *,
          Image                *pImage    )
{
    _pImage = pImage;
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLPixelTextureHelper::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname  )
{
    bool bFound = false;

    if(osgStringCaseCmp("image", szFieldname) == 0)
    {
        bFound = true;
    }
    else 
    {
        bFound = Inherited::prototypeAddField(szFieldType, 
                                              uiFieldTypeId, 
                                              szFieldname);
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "ImageTextureDesc::prototypeAddField : add part "
              << szFieldname
              << std::endl;
#endif

        return true;
    }
    else
    {
        return false;
    }
}


void VRMLPixelTextureHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    pFieldFC = NULL;
    pField.reset();
    pDesc    = NULL;

    if(osgStringCaseCmp("image", szFieldname) == 0)
    {
        pFieldFC = _pImage;
        pField.reset();
        pDesc    = &_sfImagePtrDesc;
    }
    else 
    {
        Inherited::getFieldAndDesc(pFC, 
                                   szFieldname, 
                                   pFieldFC,
                                   pField,
                                   pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerTransitPtr VRMLPixelTextureHelper::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainer    *pCurrentFC)
{
    FieldContainerTransitPtr returnValue = 
        Inherited::beginNode(szTypename, szName, pCurrentFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin PixelTexture " 
          << ((returnValue == NULL) ? "invalid obj" : "valid obj") 
          << std::endl;

    incIndent();
#endif

    return returnValue;
}

void VRMLPixelTextureHelper::endNode(FieldContainer *pFC)
{
    TextureObjChunk    *pTexture = NULL;

    pTexture = dynamic_cast<TextureObjChunk *>(pFC);


    if(pTexture != NULL)
    {
        if(_pImage != NULL)
        {
            _pImage->setForceAlphaBinary(_pImage->calcIsAlphaBinary());

            pTexture->setImage(_pImage);

            if(_repeatS.getValue() == true)
            {
                pTexture->setWrapS(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }
            if(_repeatT.getValue() == true)
            {
                pTexture->setWrapT(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapT(GL_CLAMP);
            }
        }
    }
    else
    {
        PWARNING <<  "VRMLPixelTextureDesc::endNode : Invalid texture ptr"
                 << std::endl;
    }

    _pImage = NULL;

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End PixelTexture "
          << _repeatS.getValue()    << " "
          << _repeatT.getValue()    << " "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLPixelTextureHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper VRMLPixelTextureHelper::_regHelper(
    &VRMLPixelTextureHelper::create,
    "PixelTexture",
    NULL);





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLInlineHelper::create(void)
{
    return new VRMLInlineHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLInlineHelper::VRMLInlineHelper(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLInlineHelper::~VRMLInlineHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLInlineHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "InlineHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node  ::create();
    _pNodeCoreProto = Inline::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

void VRMLInlineHelper::endNode(FieldContainer *pFC)
{
    Node *pNode = dynamic_cast<Node *>(pFC);

    if(pNode != NULL)
    {
        Inline *pInline = dynamic_cast<Inline *>(pNode->getCore());

        if(pInline != NULL)
        {
            pInline->postOSGLoading();
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLInlineHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper VRMLInlineHelper::_regHelper(
    &VRMLInlineHelper::create,
    "Inline",
    NULL);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelper *VRMLSwitchHelper::create(void)
{
    return new VRMLSwitchHelper();
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLSwitchHelper::VRMLSwitchHelper(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLSwitchHelper::~VRMLSwitchHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLSwitchHelper::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "SwitchHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node  ::create();
    _pNodeCoreProto = Switch::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLSwitchHelper::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    bool returnValue = false;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLSwitchHelper::prototypeAddField | add request : "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return false;

    incIndent();

    if(osgStringCaseCmp("choice", szFieldname) == 0)
    {
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLSwitchHelper::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << std::endl;
#endif
    }

    if(osgStringCaseCmp("whichChoice", szFieldname) == 0)
    {
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);

        PINFO << "VRMLSwitchHelper::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << std::endl;
#endif
    }

    if(returnValue == false)
    {
        returnValue =  Inherited::prototypeAddField(szFieldType,
                                                    uiFieldTypeId,
                                                    szFieldname);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif

    return returnValue;
}

void VRMLSwitchHelper::getFieldAndDesc(
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NULL)
    {
        if(_bProtoInterfaceDone == false)
        {
            Inherited::getField(szFieldname, pFieldFC, pField, pDesc);
        }

        return;
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLSwitchHelper::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;

    incIndent();
#endif

    if(osgStringCaseCmp("choice", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLSwitchHelper::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif
        pFieldFC = pFC;
        pField   = pFC->editField("children");
        pDesc    = pFC->getFieldDescription("children");
    }
    else if(osgStringCaseCmp("whichChoice", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLSwitchHelper::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        Node *pNode = dynamic_cast<Node *>(pFC);

        if(pNode != NULL)
        {
            if(pNode->getCore() != NULL)
            {
                pFieldFC = pNode->getCore();
                pField   = pNode->getCore()->editField("choice");
                pDesc    = pNode->getCore()->getFieldDescription("choice");
            }
        }
        else
        {
            Inherited::getFieldAndDesc(pFC,
                                       szFieldname,
                                       pFC,
                                       pField,
                                       pDesc);
        }
    }
    else
    {
        Inherited::getFieldAndDesc(pFC,
                                   szFieldname,
                                   pFC,
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLSwitchHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper VRMLSwitchHelper::_regHelper(
    &VRMLSwitchHelper::create,
    "Switch",
    NULL);


//---------------------------------------------------------------------------
//  Generic Helper with 1:1 mapping
//---------------------------------------------------------------------------

template<>
bool VRMLGenericHelper<TimeSensor>::initStatic(void)
{
    return true;
}

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<TimeSensor>::_regHelper(
        &VRMLGenericHelper<TimeSensor>::create,
        "TimeSensor",
        &VRMLGenericHelper<TimeSensor>::initStatic);

OSG_INST_GENERICVRMLHELPER(TimeSensor);


template<>
bool VRMLGenericHelper<VRMLOrientationInterpolator>::initStatic(void)
{
    _mFieldNameMap[std::string("fraction")] = std::string("inValue" ); 
    _mFieldNameMap[std::string("value"   )] = std::string("outValue");

    return true;
}

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<VRMLOrientationInterpolator>::_regHelper(
        &VRMLGenericHelper<VRMLOrientationInterpolator>::create,
        "OrientationInterpolator",
        &VRMLGenericHelper<VRMLOrientationInterpolator>::initStatic);

OSG_INST_GENERICVRMLHELPER(VRMLOrientationInterpolator);


template<>
bool VRMLGenericHelper<VRMLPositionInterpolator>::initStatic(void)
{
    _mFieldNameMap[std::string("fraction")] = std::string("inValue" ); 
    _mFieldNameMap[std::string("value"   )] = std::string("outValue");

    return true;
}

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<VRMLPositionInterpolator>::_regHelper(
        &VRMLGenericHelper<VRMLPositionInterpolator>::create,
        "PositionInterpolator",
        &VRMLGenericHelper<VRMLPositionInterpolator>::initStatic);

OSG_INST_GENERICVRMLHELPER(VRMLPositionInterpolator);


template<>
bool VRMLGenericHelper<VRMLCoordinateInterpolator>::initStatic(void)
{
    _mFieldNameMap[std::string("fraction")] = std::string("inValue" ); 
    _mFieldNameMap[std::string("value"   )] = std::string("outValue");

    return true;
}

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<VRMLCoordinateInterpolator>::_regHelper(
        &VRMLGenericHelper<VRMLCoordinateInterpolator>::create,
        "CoordinateInterpolator",
        &VRMLGenericHelper<VRMLCoordinateInterpolator>::initStatic);

OSG_INST_GENERICVRMLHELPER(VRMLCoordinateInterpolator);


template<>
bool VRMLGenericHelper<VRMLScalarInterpolator>::initStatic(void)
{
    _mFieldNameMap[std::string("fraction")] = std::string("inValue" ); 
    _mFieldNameMap[std::string("value"   )] = std::string("outValue");

    return true;
}

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<VRMLScalarInterpolator>::_regHelper(
        &VRMLGenericHelper<VRMLScalarInterpolator>::create,
        "ScalarInterpolator",
        &VRMLGenericHelper<VRMLScalarInterpolator>::initStatic);

OSG_INST_GENERICVRMLHELPER(VRMLScalarInterpolator);

OSG_END_NAMESPACE
