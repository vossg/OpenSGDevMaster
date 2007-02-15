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

#define OSG_COMPILEVRMLNODEDESCINST

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGVRMLNodeHelper.h"
#include "OSGSingletonHolder.ins"


#include "OSGScanParseSkel.h"
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

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

OSG_DYNFIELDATTACHMENT_INST(VRMLGenericAttDesc)

OSG_SINGLETON_INST(VRMLNodeHelperFactoryBase)

template class SingletonHolder<VRMLNodeHelperFactoryBase>;

OSG_END_NAMESPACE


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

VRMLNodeHelperFactoryBase::RegisterHelper::RegisterHelper(
          CreateHelper  fCreate, 
    const Char8        *szNodeName)
{
    VRMLNodeHelperFactory::the()->registerNodeHelper(fCreate, szNodeName);
}


VRMLNodeHelperFactoryBase::VRMLNodeHelperFactoryBase(void) :
    _mRegisteredNodeHelperHash()
{
}

VRMLNodeHelperFactoryBase::~VRMLNodeHelperFactoryBase(void)
{
}

void VRMLNodeHelperFactoryBase::registerNodeHelper(      
          CreateHelper  fHelper,
    const Char8        *szNodeName)
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


/*! \defgroup GrpSystemFileIOVRML VRML-specific File Input/Output
    \ingroup GrpSystemFileIO

    See \ref PageSystemFileIO for details.
*/

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLNodeDesc
    \ingroup GrpSystemFileIOVRML
    General VRML Node description
*/

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
        PWARNING << "Indent smaller 4 decremented" << std::endl;

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
    _pGenAttProto       (NullFC),
    _pNodeProto         (NullFC),
    _pNodeCoreProto     (NullFC),

    OSG_INIT_DESC(_sfVec3fDesc,   SFVec3f,             "sfVec3fHelperDesc"),
    OSG_INIT_DESC(_sfFCPtrDesc,   SFFieldContainerPtr, "sfFCPtrHelperDesc"),
    OSG_INIT_DESC(_sfReal32Desc,  SFReal32,            "sfReal32HelperDesc"),
    OSG_INIT_DESC(_sfColor3fDesc, SFColor3f,           "sfColor3fHelperDesc")
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLNodeHelper::~VRMLNodeHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Helper                                     */


void VRMLNodeHelper::reset(void)
{
}


/*-------------------------------------------------------------------------*/
/*                                Field                                    */

FieldContainerPtr VRMLNodeHelper::beginNode(
    const Char8             *szTypename,
    const Char8             *szName,
          FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pCore       = NullFC;
    VRMLGenericAttPtr pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        returnValue = _pNodeProto->shallowCopy();

        if(_pNodeCoreProto != NullFC)
        {
            FieldContainerPtr pCoreClone = _pNodeCoreProto->shallowCopy();

            pNode = cast_dynamic<NodePtr    >(returnValue);
            pCore = cast_dynamic<NodeCorePtr>(pCoreClone );

            pNode->setCore(pCore);
        }

        if(_pGenAttProto != NullFC)
        {
            FieldContainerPtr pAttClone = _pGenAttProto->clone();

            pAtt = cast_dynamic<VRMLGenericAttPtr>(pAttClone);

            if(pAtt != NullFC)
            {
                pAtt->setInternal(true);
            }

            if(pCore != NullFC)
            {
                pCore->addAttachment(pAtt);
            }
            else
            {
                AttachmentContainerPtr pAttCnt = 
                    cast_dynamic<AttachmentContainerPtr>(returnValue);

                if(pAttCnt != NULL)
                {
                    pAttCnt->addAttachment(pAtt);
                }
            }
        }
    }

    return returnValue;
}

void VRMLNodeHelper::endNode(FieldContainerPtr)
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


    const Field *pField = getField(_pNodeProto,
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

    if(pField == NULL)
    {
        FieldDescriptionBase *pDesc = getFieldDescription(szFieldName,
                                                          uiFieldTypeId);

        if(pDesc != NULL)
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

        returnValue = (pField != NULL);
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

void VRMLNodeHelper::getFieldAndDesc(      FieldContainerPtr      pFC,
                                     const Char8                * szFieldname,
                                           FieldContainerPtr     &pFieldFC,
                                           Field                *&pField,
                                     const FieldDescriptionBase *&pDesc)
{
    FieldContainerPtr pTmpFC    = NullFC;
    NodePtr           pNode     = NullFC;
    NodeCorePtr       pNodeCore = NullFC;

    pFieldFC = NullFC;
    pField   = NULL;
    pDesc    = NULL;

    if(pFC == NullFC)
        return;

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
            pNode     = cast_dynamic<NodePtr>(pFC);
            
            pNodeCore = pNode->getCore();

            if(pNodeCore != NullFC)
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

                    if(pTmpFC != NullFC)
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
                        
                        if(pTmpFC != NullFC)
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
        }
        else if(pFC->getType().isNodeCore() == true)
        {
            pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

            pTmpFC = pNodeCore->findAttachment(
                VRMLGenericAtt::getClassType().getGroupId());

            if(pTmpFC != NullFC)
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

const Field *VRMLNodeHelper::getField(      FieldContainerPtr  pFC1,
                                            FieldContainerPtr  pFC2,
                                            VRMLGenericAttPtr  pGenAtt,
                                      const Char8             *szFieldname)
{
    const Field *returnValue = NULL;

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

    if(pFC1 != NullFC)
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
        if(pFC2 != NullFC)
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
            if(pGenAtt != NullFC)
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


// HACK Should be somewhere else and automatic

#define OSG_CREATE_DESC(TYPE) new TYPE::Description(        \
        TYPE::getClassType(),                               \
        szFieldName,                                        \
        "",                                                 \
        0,                                                  \
        0,                                                  \
        false,                                              \
        OSG::Field::SFDefaultFlags,                         \
        reinterpret_cast<OSG::FieldIndexEditMethodSig>(     \
            &VRMLGenericAtt::editDynamicField),             \
        reinterpret_cast<OSG::FieldIndexGetMethodSig >(     \
            &VRMLGenericAtt::getDynamicField ))

#define OSG_CREATE_DESC_ELSE(TYPE)                          \
    else if(uiFieldTypeId == TYPE::getClassType().getId())  \
    {                                                       \
        returnValue = OSG_CREATE_DESC(TYPE);                \
    }



FieldDescriptionBase *VRMLNodeHelper::getFieldDescription(
    const Char8  *szFieldName,
    const UInt32  uiFieldTypeId)
{
    FieldDescriptionBase *returnValue = NULL;


    if(uiFieldTypeId == SFBool::getClassType().getId())
    {
        returnValue = OSG_CREATE_DESC(SFBool);
    }
    OSG_CREATE_DESC_ELSE(SFInt32)
    OSG_CREATE_DESC_ELSE(MFInt32)
    OSG_CREATE_DESC_ELSE(SFString)
    OSG_CREATE_DESC_ELSE(MFString)
    OSG_CREATE_DESC_ELSE(SFReal32)
    OSG_CREATE_DESC_ELSE(MFReal32)
    OSG_CREATE_DESC_ELSE(SFTime)
    OSG_CREATE_DESC_ELSE(MFTime)

    OSG_CREATE_DESC_ELSE(MFPnt3f)
    OSG_CREATE_DESC_ELSE(SFPnt3f)
    OSG_CREATE_DESC_ELSE(MFVec3f)
    OSG_CREATE_DESC_ELSE(SFVec3f)
    OSG_CREATE_DESC_ELSE(MFColor3f)
    OSG_CREATE_DESC_ELSE(SFColor3f)

    OSG_CREATE_DESC_ELSE(SFFieldContainerPtr)

    return returnValue;
}

void VRMLNodeHelper::addFieldValue(      Field                *pField,
                                   const FieldDescriptionBase *pFieldDesc,
                                   const Char8                *szFieldVal)
{
    if(pFieldDesc != NULL && pField != NULL)
    {
        pFieldDesc->pushValueFromCString(szFieldVal, pField);
    }
}

void VRMLNodeHelper::setContainerFieldValue(      
          FieldContainerPtr     pFC,
    const FieldDescriptionBase *pFieldDesc,
          FieldContainerPtr     pFieldFC  )
{
    if((pFieldDesc != NULL  ) && 
       (pFieldFC   != NullFC)   )
    {
        pFieldFC->pushToField(pFC, 
                              pFieldDesc->getFieldId());
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */








//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLDefaultHelper
    \ingroup GrpSystemFileIOVRML
    VRML Group description
*/

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


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLDefaultHelper::dump(const Char8 *)
{
}






//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGroupHelper
    \ingroup GrpSystemFileIOVRML
    VRML Group description
*/

VRMLNodeHelper *VRMLGroupHelper::create(void)
{
    return new VRMLGroupHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGroupHelper::VRMLGroupHelper(void) :
    Inherited(),

    _defaultBoxCenter(),
    _defaultBoxSize  (),

    _boxCenter       (),
    _boxSize         ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGroupHelper::~VRMLGroupHelper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGroupHelper::init(const Char8 *szName)
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

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLGroupHelper::prototypeAddField(const Char8  *szFieldType,
                                        const UInt32  uiFieldTypeId,
                                        const Char8  *szFieldname)
{
    bool bFound = false;

    if(osgStringCaseCmp("bboxCenter", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("bboxSize", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(osgStringCaseCmp("children", szFieldname) == 0)
    {
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

void VRMLGroupHelper::getFieldAndDesc(
          FieldContainerPtr      pFC,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLGroupDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pNode == NullFC)
    {
        PWARNING << "VRMLGroupDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    GroupPtr pGroup       = cast_dynamic<GroupPtr>(pNodeCore);

    if(pGroup == NullFC)
    {
        PWARNING << "VRMLGroupDesc::getFieldAndDesc : No Group" << std::endl;
        return;
    }

    incIndent();

    if(osgStringCaseCmp("bboxCenter", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultBoxCenter;
        }
        else
        {
            pField = &_boxCenter;
        }

        pDesc    = &_sfVec3fDesc;
    }
    else if(osgStringCaseCmp("bboxSize", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultBoxSize;
        }
        else
        {
            pField = &_boxSize;
        }

        pDesc    = &_sfVec3fDesc;
    }
    else if(osgStringCaseCmp("children", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif
        pFieldFC = pNode;
        pField   = NULL;
        pDesc    = pNode->getFieldDescription("children");
    }
    else
    {
        Inherited::getFieldAndDesc(pGroup,
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
/*                                Dump                                     */

void VRMLGroupHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper VRMLGroupHelper::_regHelper(
    &VRMLGroupHelper::create,
    "Group");




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLMaterialDesc
    \ingroup GrpSystemFileIOVRML
    VRML Material description
*/

VRMLNodeHelper *VRMLMaterialHelper::create(void)
{
    return new VRMLMaterialHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLMaterialHelper::VRMLMaterialHelper(void) :
    Inherited(),

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

    _pDefMat                (NullFC),
    _pMat                   (NullFC)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLMaterialHelper::~VRMLMaterialHelper(void)
{
    subRef(_pDefMat);
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
    _pMat = NullFC;

    _ambientIntensity.setValue(_defaultAmbientIntensity);
    _diffuseColor    .setValue(_defaultDiffuseColor);
    _emissiveColor   .setValue(_defaultEmissiveColor);
    _shininess       .setValue(_defaultShininess);
    _specularColor   .setValue(_defaultSpecularColor);
    _transparency    .setValue(_defaultTransparency);
}

MaterialPtr VRMLMaterialHelper::getDefaultMaterial(void)
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
    Color4f          cCol;
    MaterialChunkPtr pMatChunk;

    cCol.setValuesRGBA(_defaultDiffuseColor    .getValue().red() *
                       _defaultAmbientIntensity.getValue(),
                       _defaultDiffuseColor    .getValue().green() *
                       _defaultAmbientIntensity.getValue(),
                       _defaultDiffuseColor    .getValue().blue() *
                       _defaultAmbientIntensity.getValue(),
                       1.f - _defaultTransparency    .getValue());

    _pDefMat = ChunkMaterial::create();
    addRef(_pDefMat);

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
          FieldContainerPtr,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
    const FieldDescriptionBase *&pDesc)
{
    pFieldFC = NullFC;
    pField   = NULL;
    pDesc    = NULL;

    if(osgStringCaseCmp("ambientIntensity", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultAmbientIntensity;
        }
        else
        {
            pField = &_ambientIntensity;
        }

        pDesc = &_sfReal32Desc;
    }
    else if(osgStringCaseCmp("diffuseColor", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultDiffuseColor;
        }
        else
        {
            pField = &_diffuseColor;
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("emissiveColor", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultEmissiveColor;
        }
        else
        {
            pField = &_emissiveColor;
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("shininess", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultShininess;
        }
        else
        {
            pField = &_shininess;
        }

        pDesc = &_sfReal32Desc;
    }
    else if(osgStringCaseCmp("specularColor", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultSpecularColor;
        }
        else
        {
            pField = &_specularColor;
        }

        pDesc = &_sfColor3fDesc;
    }
    else if(osgStringCaseCmp("transparency", szFieldname) == 0)
    {
        pFieldFC = NullFC;

        if(_bProtoInterfaceDone == false)
        {
            pField = &_defaultTransparency;
        }
        else
        {
            pField = &_transparency;
        }

        pDesc = &_sfReal32Desc;
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLMaterialHelper::beginNode(
    const Char8            *,
    const Char8            *,
          FieldContainerPtr  )
{
    reset();

    _pMat = MaterialChunk::create();

    return _pMat;
}

void VRMLMaterialHelper::endNode(FieldContainerPtr)
{
    if(_pMat != NullFC)
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
/*                                Dump                                     */

void VRMLMaterialHelper::dump(const Char8 *)
{
}

VRMLNodeHelperFactoryBase::RegisterHelper VRMLMaterialHelper::_regHelper(
    &VRMLMaterialHelper::create,
    "Material");





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLShapeDesc
    \ingroup GrpSystemFileIOVRML
    VRML Shape description
*/

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
          FieldContainerPtr      pFC,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

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
        pField   = NULL;
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

        NodePtr pNode = cast_dynamic<NodePtr>(pFC);

        if(pNode != NullFC)
        {
            if(pNode->getCore() != NullFC)
            {
                pFieldFC = pNode->getCore();
                pField   = NULL;
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


void VRMLShapeHelper::endNode(FieldContainerPtr pFC)
{
    if(pFC != NullFC)
    {
        NodePtr pNode = cast_dynamic<NodePtr>(pFC);

        if(pNode != NullFC && pNode->getCore() == NullFC)
        {
            PWARNING << "warning empty material, using default\n" << std::endl;

            MaterialGroupPtr pMatGroup = MaterialGroup::create();

            pMatGroup->setMaterial(_pMaterialHelper->getDefaultMaterial());

            pNode->setCore(pMatGroup);
        }
        else
        {
            MaterialGroupPtr pMatGroup;

            pMatGroup = cast_dynamic<MaterialGroupPtr>(pNode->getCore());

            if(pMatGroup != NullFC)
            {
                if(pMatGroup->getMaterial() == NullFC)
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
    "Shape");




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLAppearanceDesc
    \ingroup GrpSystemFileIOVRML
    VRML Appearance description
*/

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
          FieldContainerPtr      pFC,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
    const FieldDescriptionBase *&pDesc)
{

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLAppearanceHelper::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pFC == NullFC)
        return;

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
        pField   = NULL;
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
        pField   = NULL;
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
        pField   = NULL;
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


void VRMLAppearanceHelper::endNode(FieldContainerPtr pFC)
{
    if(pFC != NullFC)
    {
        ChunkMaterialPtr pChunkMat = cast_dynamic<ChunkMaterialPtr>(pFC);

        if(pChunkMat != NullFC)
        {
            StateChunkPtr cp = 
                pChunkMat->find(TextureObjChunk::getClassType());

            TextureObjChunkPtr tex = NullFC;

            if(cp != NullFC)
            {
                tex = cast_dynamic<TextureObjChunkPtr>(cp);
            }

            if ((pChunkMat->isTransparent() == true             ) ||
                (tex                                != NullFC && 
                 tex->getImage()                    != NullFC &&
                 tex->getImage()->hasAlphaChannel() == true    ))
            {
                BlendChunkPtr pBlendChunk = OSG::BlendChunk::create();

                if(tex                              != NullFC && 
                   tex->getImage()                  != NullFC &&
                   tex->getImage()->isAlphaBinary() == true)
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
        }
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
    "Appearance");




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLIndexedGeometryHelper
    \ingroup GrpSystemFileIOVRML
    VRML Geometry description
*/

VRMLNodeHelper *VRMLIndexedGeometryHelper::create(void)
{
    return new VRMLIndexedGeometryHelper();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLIndexedGeometryHelper::VRMLIndexedGeometryHelper(void) :
     Inherited      (                        ),
    _bIsFaceSet     (true                    ),
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
          FieldContainerPtr      pFC,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
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

    if(pFC == NullFC)
        return;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

    if(pNode == NullFC)
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    GeometryPtr pGeo      = cast_dynamic<GeometryPtr>(pNodeCore);

    if(pGeo == NullFC)
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
        pField   = NULL;
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
        pField   = NULL;
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
        pField   = NULL;
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
        pField   = NULL;
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



void VRMLIndexedGeometryHelper::endNode(FieldContainerPtr pFC)
{
    NodePtr     pNode = NullFC;
    GeometryPtr pGeo  = NullFC;

    if(pFC == NullFC)
    {
        return;
    }

    pNode = cast_dynamic<NodePtr>(pFC);

    if(pNode == NullFC)
    {
        return;
    }

    pGeo = cast_dynamic<GeometryPtr>(pNode->getCore());

    if(pGeo == NullFC)
    {
        return;
    }

          Field                *pField   = NULL;
    const FieldDescriptionBase *pDesc    = NULL;
          FieldContainerPtr     pDummyFC = NullFC;


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
        pCoordIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "texCoordIndex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pTexCoordIndex = static_cast<MFInt32 *>(pField);
    }



    Inherited::getFieldAndDesc(pFC,
                               "convex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pConvex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "ccw",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCcw = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalPerVertex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorPerVertex",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "creaseAngle",
                               pDummyFC,
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCreaseAngle = static_cast<SFReal32 *>(pField);
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
            //   (pGeo->getNormals() == NullFC))

            if(pGeo->getNormals() == NullFC)
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
            pGeo = NullFC;
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
            pGeo = NullFC;
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
          FieldContainerPtr     pFC,
    const FieldDescriptionBase *pFieldDesc,
          FieldContainerPtr     pFieldFC  )
{
    GeometryPtr          pGeo     = 
        cast_dynamic<GeometryPtr         >(pFieldFC);

    GeoVectorPropertyPtr pVecProp = 
        cast_dynamic<GeoVectorPropertyPtr>(pFC);

    if(pGeo != NullFC && pVecProp != NullFC)
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
        "IndexedFaceSet");

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLIndexedGeometryHelper::_regHelperILS(
        &VRMLIndexedGeometryHelper::create,
        "IndexedLineSet");





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGeometryPartHelper
    \ingroup GrpSystemFileIOVRML
    VRML Geometry Part Set description
*/

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

    if(_pNodeProto == NullFC)
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
          FieldContainerPtr      pFC,
    const Char8                * szFieldname,
          FieldContainerPtr     &pFieldFC,
          Field                *&pField,
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

    if(pFC == NullFC)
        return;

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


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryPartHelper::dump(const Char8 *)
{
}


VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperCoordinate(
        &VRMLGeometryPartHelper::create,
        "Coordinate");

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperNormal(
        &VRMLGeometryPartHelper::create,
        "Normal");

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperColor(
        &VRMLGeometryPartHelper::create,
        "Color");

VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGeometryPartHelper::_regHelperTexCoordinate(
        &VRMLGeometryPartHelper::create,
        "TextureCoordinate");


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGVRMLNODEHELPER_HEADER_CVSID;
}

