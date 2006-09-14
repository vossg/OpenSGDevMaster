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
#if 0

#define OSG_COMPILEVRMLNODEDESCINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGVRMLNodeDescs.h"
#include "OSGLog.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGGroup.h"
#include "OSGComponentTransform.h"
#include "OSGGeometry.h"
#include "OSGMaterialGroup.h"
#include "OSGSimpleGeometry.h"
#ifdef OSG_EXTRUSION_SUPPORT
#include "OSGExtrusionGeometry.h"
#endif
#include "OSGTextureChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGGeoFunctions.h"
#include "OSGDistanceLOD.h"
#include "OSGSwitch.h"
#include "OSGInline.h"
#include "OSGImage.h"
#include "OSGSceneFileHandler.h"
#include "OSGImageFileHandler.h"
#include "OSGZStream.h"

#include "OSGVRMLFile.h"

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "VRMLLoader"
#endif

//#define OSG_DEBUG_VRML

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

/*! \defgroup GrpSystemFileIOVRML VRML-specific File Input/Output
    \ingroup GrpSystemFileIO

    See \ref PageSystemFileIO for details.
*/

#if 0

#ifdef WIN32
OSG_FC_ST_TYPE_FUNCTIONS_INL_TMPL_DEF(GenericAttDesc,
                                      DynFieldAttachment)
#endif

OSG_DYNFIELD_FC_DLLEXPORT_DEF(DynFieldAttachment,
                              GenericAttDesc,
                              OSG_SYSTEMLIB_DLLTMPLMAPPING);

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLNodeDesc
    \ingroup GrpSystemFileIOVRML
    General VRML Node description
*/

UInt32 VRMLNodeDesc::_uiIndent = 0;

/*-------------------------------------------------------------------------*/
/*                            Static Get                                   */

UInt32 VRMLNodeDesc::getIndent(void)
{
    return _uiIndent;
}

void VRMLNodeDesc::incIndent(void)
{
    _uiIndent += 4;
}

void VRMLNodeDesc::decIndent(void)
{
    if(_uiIndent < 4)
    {
        PWARNING << "Indent smaller 4 decremented" << std::endl;

        _uiIndent = 4;
    }

    _uiIndent -= 4;
}

void VRMLNodeDesc::resetIndent(void)
{
    _uiIndent = 0;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLNodeDesc::VRMLNodeDesc(void) :
    _mFieldTypes   (),

    _pGenAtt       (NullFC),

    _pNodeProto    (NullFC),
    _pNodeCoreProto(NullFC),

    _pCurrField    (NULL),

    _szCurrentName (),
    _bSaveOnEnd    (false)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLNodeDesc::~VRMLNodeDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Helper                                     */

void VRMLNodeDesc::init(const Char8 *szName)
{
    if(szName == NULL)
    {
        _pNodeCoreProto = Group::create();
    }
    else if(stringcasecmp(szName, "Transform") == 0)
    {
        _pNodeCoreProto = ComponentTransform::create();
    }
    else
    {
        _pNodeCoreProto = Group::create();
    }

    _pNodeProto = Node::create();

    _pGenAtt    = GenericAtt::create();
    _pGenAtt->setInternal(true);
}


void VRMLNodeDesc::reset(void)
{
}

void VRMLNodeDesc::setOnEndSave(const Char8 *szName)
{
    _szCurrentName = szName; // does that make a copy? I expect it to...
    _bSaveOnEnd = true;
}

void VRMLNodeDesc::clearOnEndSave(void)
{
    _bSaveOnEnd = false;
}

bool VRMLNodeDesc::getOnEndSave(void)
{
    return _bSaveOnEnd;
}

const Char8 *VRMLNodeDesc::getSavename(void)
{
    return _szCurrentName.c_str();
}

FieldContainerPtr VRMLNodeDesc::getSaveFieldContainer(void)
{
    return NullFC;
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

const Field *VRMLNodeDesc::getField(const Char8 *szFieldname)
{
    return getField(_pNodeProto, _pNodeCoreProto, _pGenAtt, szFieldname);
}

void VRMLNodeDesc::getFieldAndDesc(
    FieldContainerPtr        pFC,
    const Char8            * szFieldname,
    const Field                  *&pField,
    const FieldDescriptionBase *&pDesc)
{
    FieldContainerPtr pTmpFC    = NullFC;
    NodePtr           pNode     = NullFC;
    NodeCorePtr       pNodeCore = NullFC;

    pField = NULL;
    pDesc  = NULL;

    if(pFC == NullFC)
        return;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLNodeDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;

    incIndent();
#endif

    pField = pFC->getField(szFieldname);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Got this from fieldcontainer : " << pField << std::endl;
#endif

    if(pField != NULL)
    {
        pDesc = pFC->getFieldDescription(szFieldname);

#ifdef OSG_DEBUG_VRML
        decIndent();
#endif

        return;
    }

    if(pFC->getType().isNode() == true)
    {
        pNode     = cast_dynamic<NodePtr>(pFC);

        pNodeCore = pNode->getCore();

        if(pNodeCore != NullFC)
        {
            pField    = pNodeCore->getField(szFieldname);

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from nodecore : " << pField << std::endl;
#endif
        }

        if(pField != NULL)
        {
            pDesc = pNodeCore->getFieldDescription(szFieldname);
        }
        else
        {
            pTmpFC = pNode->findAttachment(
                GenericAtt::getClassType().getGroupId());

            if(pTmpFC != NullFC)
            {
                pField = pTmpFC->getField(szFieldname);
            }

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Got this from node attachment : " << pField << std::endl;
#endif
            if(pField == NULL)
            {
                pTmpFC =
                    pNodeCore->findAttachment(
                        GenericAtt::getClassType().getGroupId());

                if(pTmpFC != NullFC)
                {
                    pField = pTmpFC->getField(szFieldname);
                }

#ifdef OSG_DEBUG_VRML
                indentLog(getIndent(), PINFO);
                PINFO << "Got this from nodecore attachment : "
                      << pField << std::endl;
#endif
            }

            if(pField != NULL)
            {
                pDesc = pTmpFC->getFieldDescription(szFieldname);
            }
        }
    }
    else if(pFC->getType().isNodeCore() == true)
    {
        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pTmpFC = pNodeCore->findAttachment(
            GenericAtt::getClassType().getGroupId());

        if(pTmpFC != NullFC)
        {
            pField = pTmpFC->getField(szFieldname);
        }

        if(pField != NULL)
        {
            pDesc = pTmpFC->getFieldDescription(szFieldname);
        }

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "Got this from nodecore attachment : "
              << pField << std::endl;
#endif
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                              Prototypes                                 */

bool VRMLNodeDesc::prototypeAddField(const Char8  *OSG_VRML_ARG(szFieldType),
                                     const UInt32  uiFieldTypeId,
                                     const Char8  *szFieldName)
{
#if 0 // AMZ FIXME
    FieldDescriptionBase *pDesc = NULL;
    FieldType        *pType = NULL;

    Field *pField = getField(_pNodeProto,
                             _pNodeCoreProto,
                             _pGenAtt,
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
        pType = FieldFactory::the().getFieldType(uiFieldTypeId);

        if(pType == NULL)
        {
            PWARNING << "VRMLNodeDesc::prototypeAddField "
                     << "Could not get fieldtype "
                     << uiFieldTypeId << " "
                     << szFieldName << " "
                     << std::endl;

            return false;
        }

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLNodeDesc::prototypeAddField | got fieldtype : "
              << uiFieldTypeId
              << " "
              << pType->getName()
              << " "
              << pType->getId()
              << std::endl;
#endif

        pDesc = new FieldDescription(*pType,
                                     szFieldName,
                                     0, 0,
                                     false,
                                     (FieldIndexAccessMethod)
                                     &GenericAtt::getDynamicField);

        _pGenAtt->addField(*pDesc);

        _pCurrField = getField(_pNodeProto,
                               _pNodeCoreProto,
                               _pGenAtt,
                                szFieldName);

        delete pDesc;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLNodeDesc::prototypeAddField | field added : "
              << szFieldType
              << " "
              << uiFieldTypeId
              << " "
              << szFieldName
              << " "
              << _pCurrField
              << std::endl;
#endif

        if(_pCurrField != NULL)
            return true;
        else
            return false;
    }
    else
    {
        if((_pGenAtt != NullFC                     ) &&
           (_pGenAtt->getField(szFieldName) != NULL))
        {
            PWARNING << "VRMLNodeDesc::prototypeAddField | "
                     << "Could not add field "
                     << szFieldName
                     << " a second time"
                     << std::endl;
        }

        return false;
    }
#endif
    return false;
}

void VRMLNodeDesc::prototypeAddFieldValue(const Char8 *szFieldVal)
{
    if(_pCurrField       != NULL)
    {
        _pCurrField->pushValueByStr(szFieldVal);
    }
}

void VRMLNodeDesc::endProtoInterface(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLNodeDesc::beginNode(const Char8      *,
                                          const Char8      *,
                                          FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pCore       = NullFC;
    GenericAttPtr     pAtt        = NullFC;

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

        if(_pGenAtt != NullFC)
        {
            FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

            pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

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
                pNode->addAttachment(pAtt);
            }
        }
    }

    return returnValue;
}

void VRMLNodeDesc::endNode(FieldContainerPtr)
{
}

/*-------------------------------------------------------------------------*/
/*                             Field Value                                 */

void VRMLNodeDesc::addFieldValue(      Field *pField,
                                    const Char8   *szFieldVal)
{
    if(pField != NULL)
    {
        pField->pushValueByStr(szFieldVal);
    }
}

bool VRMLNodeDesc::use(FieldContainerPtr)
{
    return false;
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLNodeDesc::dump(const Char8 *szNodeName)
{
    fprintf(stderr, "\tDefault %s\n", szNodeName);

    fprintf(stderr, "\t\tGenAtt        %p\n", &(*_pGenAtt));
    fprintf(stderr, "\t\tNodeProto     %p\n", &(*_pNodeProto));
    fprintf(stderr, "\t\tNodeCoreProto %p\n", &(*_pNodeCoreProto));

    std::string stringVal;

    if(_pGenAtt != NullFC)
    {
        fprintf(stderr, "\t\t%u Desc\n",
                _pGenAtt->getType().getNumFieldDescs());

        for(UInt32 i = 2; i <= _pGenAtt->getType().getNumFieldDescs(); i++)
        {
            FieldDescriptionBase *pFieldDesc =
                _pGenAtt->getFieldDescription(i);
            const Field            *pField     =
                _pGenAtt->getDynamicField(i);

            stringVal.erase(stringVal.begin(),
                            stringVal.end());

            pField->getValueByStr(stringVal);

            fprintf(stderr, "\t\t%s %s %s\n",
                    pFieldDesc->getCName(),
                    pFieldDesc->getFieldType().getCName(),
                    stringVal.c_str());
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

const Field *VRMLNodeDesc::getField(      FieldContainerPtr  pFC1,
                                    FieldContainerPtr  pFC2,
                                    GenericAttPtr      pGenAtt,
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

    if(returnValue != NULL)
        return returnValue;

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


    if(returnValue != NULL)
        return returnValue;

    if(pGenAtt != NullFC)
    {
        returnValue = pGenAtt->getField(szFieldname);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Got this from attachment : " << returnValue << std::endl;

    decIndent();
    decIndent();
#endif

    return returnValue;
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLShapeDesc
    \ingroup GrpSystemFileIOVRML
    VRML Shape description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLShapeDesc::VRMLShapeDesc(void) :
    Inherited     (),

    _pMaterialDesc(NULL)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLShapeDesc::~VRMLShapeDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLShapeDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ShapeDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = MaterialGroup::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

void VRMLShapeDesc::setMaterialDesc(VRMLMaterialDesc *pMaterialDesc)
{
    _pMaterialDesc = pMaterialDesc;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLShapeDesc::prototypeAddField(const Char8  *szFieldType,
                                      const UInt32  uiFieldTypeId,
                                      const Char8  *szFieldname)
{
    bool returnValue = false;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLShapeDesc::prototypeAddField | add request : "
          << szFieldname
          << std::endl;
#endif

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    incIndent();

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
        _pCurrField = _pNodeProto->getField("children");
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeDesc::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << _pCurrField
              << std::endl;
#endif
    }

    if(stringcasecmp("appearance", szFieldname) == 0)
    {
        _pCurrField = _pNodeCoreProto->getField("material");
        returnValue = true;

#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);

        PINFO << "VRMLShapeDesc::prototypeAddField | request internal : "
              << szFieldname
              << " "
              << _pCurrField
              << std::endl;
#endif
    }

    if(_pCurrField == NULL)
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

void VRMLShapeDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
    const Field             *&pField,
    const FieldDescriptionBase  *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLShapeDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;

    incIndent();
#endif

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pFC->getField("children");

        if(pField != NULL)
            pDesc = pFC->getFieldDescription("children");
    }
    else if(stringcasecmp("appearance", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLShapeDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        NodePtr pNode = cast_dynamic<NodePtr>(pFC);

        if(pNode != NullFC)
        {
            if(pNode->getCore() != NullFC)
            {
                pField = pNode->getCore()->getField("material");

                if(pField != NULL)
                {
                    pDesc =
                        pNode->getCore()->getFieldDescription(
                            "material");
                }
            }
        }
        else
        {
            VRMLNodeDesc::getFieldAndDesc(pFC,
                                          szFieldname,
                                          pField,
                                          pDesc);
        }
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pFC,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLShapeDesc::beginNode(const Char8            *,
                                           const Char8            *,
                                                 FieldContainerPtr)
{
    NodePtr           pNode     = NullFC;
    NodeCorePtr       pNodeCore = NullFC;

    if(_pNodeProto != NullFC)
    {
        pNode = cast_dynamic<NodePtr>(_pNodeProto->shallowCopy());

        if(_pNodeCoreProto != NullFC)
        {
            pNodeCore = cast_dynamic<NodeCorePtr>(_pNodeCoreProto->shallowCopy());

            pNode->setCore(pNodeCore);
        }
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Shape " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLShapeDesc::endNode(FieldContainerPtr pFC)
{
    if(pFC != NullFC)
    {
        NodePtr pNode = cast_dynamic<NodePtr>(pFC);

        if(pNode != NullFC && pNode->getCore() == NullFC)
        {
            PWARNING << "warning empty material, using default\n" << std::endl;

            MaterialGroupPtr pMatGroup = MaterialGroup::create();

            pMatGroup->setMaterial(_pMaterialDesc->getDefaultMaterial());

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
                        _pMaterialDesc->getDefaultMaterial());
                }
            }
        }
    }

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Shape " << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLShapeDesc::dump(const Char8 *)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGeometryDesc
    \ingroup GrpSystemFileIOVRML
    VRML Geometry description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryDesc::VRMLGeometryDesc(bool bIsFaceSet) :
    Inherited     (),

    _bIsFaceSet   (bIsFaceSet),

    _bInIndex     (false),
    _uiNumVertices(0),

    _pTypeField   (NullFC    ),
    _pLengthField (NullFC    )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryDesc::~VRMLGeometryDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Geometry::create();

    _pGenAtt = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLGeometryDesc::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("texCoord", szFieldname) == 0)
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


void VRMLGeometryDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
    const Field             *&pField,
    const FieldDescriptionBase  *&pDesc)
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

    _bInIndex = false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif
        pField = pGeo->getField("positions");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("positions");
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pGeo->getField("normals");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("normals");
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pGeo->getField("colors");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("colors");
    }
    else if(stringcasecmp("texCoord", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pGeo->getField("texCoords");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("texCoords");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pGeo,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLGeometryDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Geo " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLGeometryDesc::endNode(FieldContainerPtr pFC)
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

          Field            *pField = NULL;
    const FieldDescriptionBase *pDesc  = NULL;

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
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCoordIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "texCoordIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pTexCoordIndex = static_cast<MFInt32 *>(pField);
    }



    Inherited::getFieldAndDesc(pFC,
                               "convex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pConvex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "ccw",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCcw = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalPerVertex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorPerVertex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "creaseAngle",
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

            setIndexFromVRMLData(pGeo,
                                 pCoordIndex     ->getValues(),
                                 pNormalIndex    ->getValues(),
                                 pColorIndex     ->getValues(),
                                 pTexCoordIndex  ->getValues(),
                                 pConvex         ->getValue() ,
                                 pCcw            ->getValue() ,
                                 pNormalPerVertex->getValue() ,
                                 pColorPerVertex ->getValue() ,
                                 false, // create normal; not yet :)
                                 true);

            if (pConvex->getValue() == false)
                createConvexPrimitives( pGeo );

            // TODO: Need some option _uiOptions param
						createSharedIndex( pGeo);

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

            setIndexFromVRMLData(pGeo,
                                 pCoordIndex    ->getValues(),
                                 dummyVec ,
                                 pColorIndex    ->getValues(),
                                 dummyVec ,
                                 dummybool,
                                 dummybool,
                                 dummybool,
                                 pColorPerVertex->getValue() ,
                                 false,  // create normal; not yet :)
                                 false);
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
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Geo " << &(*pNode) << std::endl;
#endif
}

void VRMLGeometryDesc::addFieldValue(      Field *pField,
                                     const Char8 *szFieldVal)
{
    if(pField != NULL)
    {
        pField->pushValueByStr(szFieldVal);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGeometryPointSetDesc
    \ingroup GrpSystemFileIOVRML
    VRML Geometry Point Set description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryPointSetDesc::VRMLGeometryPointSetDesc(void) :
    Inherited     (),

    _bInIndex     (false),
    _uiNumVertices(0),

    _pTypeField   (NullFC    ),
    _pLengthField (NullFC    )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryPointSetDesc::~VRMLGeometryPointSetDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryPointSetDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Geometry::create();

    _pGenAtt = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

bool VRMLGeometryPointSetDesc::prototypeAddField(const Char8  *szFieldType,
                                                 const UInt32  uiFieldTypeId,
                                                 const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("color", szFieldname) == 0)
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


void VRMLGeometryPointSetDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
    const Field             *&pField,
    const FieldDescriptionBase  *&pDesc)
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

    _bInIndex = false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif
        pField = pGeo->getField("positions");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("positions");
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "GeoDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pGeo->getField("colors");

        if(pField != NULL)
            pDesc = pGeo->getFieldDescription("colors");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pGeo,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLGeometryPointSetDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Geo " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLGeometryPointSetDesc::endNode(FieldContainerPtr pFC)
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

    GeoPLengthsUI32Ptr pLengths = GeoPLengthsUI32::create();
    GeoPTypesUI8Ptr    pTypes   = GeoPTypesUI8::create();

    GeoPositionsPtr    pPos     = pGeo->getPositions();
    GeoPositions3fPtr  pCoords  = cast_dynamic<GeoPositions3fPtr>(pPos);

    if(pCoords == NullFC)
        return;

    GeoPLengthsUI32::StoredFieldType *pLenField  =
        pLengths->editFieldPtr();

    GeoPTypesUI8   ::StoredFieldType *pTypeField =
        pTypes ->editFieldPtr();

    pLenField->push_back(pCoords->getFieldPtr()->size());

    pTypeField->push_back(GL_POINTS);

    pGeo->setLengths(pLengths);
    pGeo->setTypes  (pTypes  );

#if 0
          Field            *pField = NULL;
    const FieldDescriptionBase *pDesc  = NULL;

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
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCoordIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "texCoordIndex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pTexCoordIndex = static_cast<MFInt32 *>(pField);
    }



    Inherited::getFieldAndDesc(pFC,
                               "convex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pConvex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "ccw",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCcw = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "normalPerVertex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "colorPerVertex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC,
                               "creaseAngle",
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

            setIndexFromVRMLData(pGeo,
                                 pCoordIndex     ->getValues(),
                                 pNormalIndex    ->getValues(),
                                 pColorIndex     ->getValues(),
                                 pTexCoordIndex  ->getValues(),
                                 pConvex         ->getValue() ,
                                 pCcw            ->getValue() ,
                                 pNormalPerVertex->getValue() ,
                                 pColorPerVertex ->getValue() ,
                                 false, // create normal; not yet :)
                                 true);

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

            while(parentsIt != endParents)
            {
                (*parentsIt)->setCore(pGr);

                ++parentsIt;
            }
#endif
        }
    }
    else
    {
        vector<Int32> dummyVec;
        bool          dummybool = false;

        if(pCoordIndex         != NULL &&
           pCoordIndex->size() >     1 &&
           pColorIndex         != NULL &&
           pColorPerVertex     != NULL)
        {
#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "Geo create lineset " << &(*pNode) << std::endl;
#endif

            setIndexFromVRMLData(pGeo,
                                 pCoordIndex    ->getValues(),
                                 dummyVec ,
                                 pColorIndex    ->getValues(),
                                 dummyVec ,
                                 dummybool,
                                 dummybool,
                                 dummybool,
                                 pColorPerVertex->getValue() ,
                                 false,  // create normal; not yet :)
                                 false);
        }
        else
        {
#if 0  // What's the point of doing that?

            PWARNING << "Invalid geometry replaced by a group" << std::endl;

            GroupPtr pGr = Group::create();

            MFNodePtr           pGeoParents = pGeo->getParents ();
            MFNodePtr::iterator parentsIt   = pGeoParents.begin();
            MFNodePtr::iterator endParents  = pGeoParents.end  ();

            while(parentsIt != endParents)
            {
                (*parentsIt)->setCore(pGr);

                ++parentsIt;
            }
#endif
        }
    }

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Geo " << &(*pNode) << std::endl;
#endif
#endif
}

void VRMLGeometryPointSetDesc::addFieldValue(      Field *pField,
                                             const Char8 *szFieldVal)
{
    if(pField != NULL)
    {
        pField->pushValueByStr(szFieldVal);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryPointSetDesc::dump(const Char8 *)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGeometryPartDesc
    \ingroup GrpSystemFileIOVRML
    VRML Geometry Part Set description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryPartDesc::VRMLGeometryPartDesc(Char8 *szVRMLPartname,
                                           Char8 *szOSGPartname,
                                           Char8 *szOSGProtoname) :
     Inherited(),

    _szVRMLPartname(NULL),
    _szOSGPartname (NULL),
    _szOSGProtoname(NULL)
{
    stringDup(szVRMLPartname, _szVRMLPartname);
    stringDup(szOSGPartname,  _szOSGPartname );
    stringDup(szOSGProtoname, _szOSGProtoname);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryPartDesc::~VRMLGeometryPartDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryPartDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
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
       FieldContainerFactory::the()->createContainer(_szOSGProtoname);

    if(_pNodeProto == NullFC)
    {
        PWARNING << "ERROR no prototype available for "
                 << _szOSGProtoname
                 << std::endl;
    }

    _pGenAtt = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLGeometryPartDesc::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp(_szVRMLPartname, szFieldname) == 0)
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
        return VRMLNodeDesc::prototypeAddField(szFieldType,
                                               uiFieldTypeId,
                                               szFieldname);
    }
}

void VRMLGeometryPartDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
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

    if(stringcasecmp(_szVRMLPartname, szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGeometryPartDesc::getFieldAndDesc : request internal "
              << szFieldname
              << " return "
              << _szOSGPartname
              << std::endl;
#endif

        pField = pFC->getField(_szOSGPartname);

        if(pField != NULL)
            pDesc = pFC->getFieldDescription(_szOSGPartname);

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
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLGeometryPartDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;

    if(_pNodeProto != NullFC)
        returnValue = _pNodeProto->shallowCopy();

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryPartDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGeometryObjectDesc
    \ingroup GrpSystemFileIOVRML
    VRML Geometry Object Set description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGeometryObjectDesc::VRMLGeometryObjectDesc(Char8 *szVRMLObjectname) :
    Inherited(),

    _szVRMLObjectname(NULL)
{
    stringDup(szVRMLObjectname, _szVRMLObjectname);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGeometryObjectDesc::~VRMLGeometryObjectDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGeometryObjectDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GeoObjDesc::init : "
          << szName << " "
          << _szVRMLObjectname
          << std::endl;
#endif

    _pNodeProto = Node::create();

    if(_pNodeProto == NullFC)
    {
        PWARNING << "GeoObjDesc::init : no prototype available" << std::endl;
    }

    _pGenAtt = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLGeometryObjectDesc::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname)
{
    _pCurrField = NULL;

    bool rc = VRMLNodeDesc::prototypeAddField(szFieldType,
                                              uiFieldTypeId,
                                              szFieldname);

    return rc;
}

void VRMLGeometryObjectDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLGeometryObjectDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    incIndent();

    Inherited::getFieldAndDesc(pFC,
                               szFieldname,
                               pField,
                               pDesc);

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLGeometryObjectDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        returnValue = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(returnValue);

        pNode->addAttachment(pAtt);
    }

    return returnValue;
}

void VRMLGeometryObjectDesc::endNode(FieldContainerPtr pFC)
{
          Field            *pField = NULL;
    const FieldDescriptionBase *pDesc  = NULL;
          NodePtr           pNode  = NullFC;

    if(pFC == NullFC)
        return;

    pNode = cast_dynamic<NodePtr>(pFC);

    if(pNode == NullFC)
        return;

    if(     stringcasecmp("Box",      _szVRMLObjectname) == 0)
    {
        Inherited::getFieldAndDesc(pFC,
                                   "size",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFVec3f *pVec = static_cast<SFVec3f *>(pField);

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "VRMLGeometryObjectDesc::endNode : Create box"
                  << std::endl;
#endif

            GeometryPtr pGeo = makeBoxGeo(pVec->getValue()[0],
                                          pVec->getValue()[1],
                                          pVec->getValue()[2],
                                          1,1,1);

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Cone",     _szVRMLObjectname) == 0)
    {
        SFReal32 *pBotRad = NULL;
        SFReal32 *pHeight = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pBottom = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "bottomRadius",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBotRad = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "height",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pHeight = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "side",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pSide = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "bottom",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBottom = static_cast<SFBool *>(pField);
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

            GeometryPtr pGeo = makeConeGeo(pHeight->getValue(),
                                           pBotRad->getValue(),
                                           32,
                                           pSide  ->getValue(),
                                           pBottom->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Cylinder", _szVRMLObjectname) == 0)
    {
        SFBool   *pBottom = NULL;
        SFReal32 *pHeight = NULL;
        SFReal32 *pRadius = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pTop    = NULL;

        Inherited::getFieldAndDesc(pFC,
                                   "bottom",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBottom = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "height",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pHeight = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "radius",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pRadius = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "side",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pSide = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC,
                                   "top",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pTop = static_cast<SFBool *>(pField);
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

            GeometryPtr pGeo = makeCylinderGeo(pHeight->getValue(),
                                               pRadius->getValue(),
                                               32,
                                               pSide  ->getValue(),
                                               pTop   ->getValue(),
                                               pBottom->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Sphere",   _szVRMLObjectname) == 0)
    {
        Inherited::getFieldAndDesc(pFC,
                                   "radius",
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32 *pValue = static_cast<SFReal32 *>(pField);

#ifdef OSG_DEBUG_VRML
            indentLog(getIndent(), PINFO);
            PINFO << "VRMLGeometryObjectDesc::endNode : Create sphere"
                  << std::endl;
#endif

            GeometryPtr pGeo = makeLatLongSphereGeo(8, 16, pValue->getValue());

            pNode->setCore(pGeo);
        }

    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGeometryObjectDesc::dump(const Char8 *)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLAppearanceDesc
    \ingroup GrpSystemFileIOVRML
    VRML Appearance description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLAppearanceDesc::VRMLAppearanceDesc(void) :
    Inherited         (),

    _pMaterialDesc    (NULL)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLAppearanceDesc::~VRMLAppearanceDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLAppearanceDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ApperanceDesc::init : " << szName << std::endl;
#endif

    _pNodeProto = ChunkMaterial::create();
    addRef(_pNodeProto);

    _pGenAtt    = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

void VRMLAppearanceDesc::setMaterialDesc(VRMLMaterialDesc *pMaterialDesc)
{
    _pMaterialDesc = pMaterialDesc;
}

FieldContainerPtr VRMLAppearanceDesc::getSaveFieldContainer(void)
{
    return NullFC;
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLAppearanceDesc::prototypeAddField(const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldname)
{
    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("material", szFieldname) == 0)
    {
        return true;
    }
    else if(stringcasecmp("texture", szFieldname) == 0)
    {
        return true;
    }
    else if(stringcasecmp("textureTransform", szFieldname) == 0)
    {
        return true;
    }
    else
    {
        return VRMLNodeDesc::prototypeAddField(szFieldType,
                                               uiFieldTypeId,
                                               szFieldname);
    }
}

void VRMLAppearanceDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLAppearanceDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pFC == NullFC)
        return;

    if(szFieldname == NULL)
        return;

    incIndent();

    if(stringcasecmp("material", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pFC->getField("chunks");

        if(pField != NULL)
            pDesc = pFC->getFieldDescription("chunks");
    }
    else if(stringcasecmp("texture", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pFC->getField("chunks");

        if(pField != NULL)
            pDesc = pFC->getFieldDescription("chunks");
    }
    else if(stringcasecmp("textureTransform", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pFC->getField("chunks");

        if(pField != NULL)
            pDesc = pFC->getFieldDescription("chunks");
    }
    else
    {
        Inherited::getFieldAndDesc(_pGenAtt,
                                   szFieldname,
                                   pField,
                                   pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLAppearanceDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr returnValue = NullFC;

    returnValue = _pNodeProto->shallowCopy();

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Appearance " << &(*returnValue) << std::endl;

    incIndent();
#endif

    return returnValue;
}

void VRMLAppearanceDesc::endNode(FieldContainerPtr pFC)
{
    if(pFC != NullFC)
    {
        ChunkMaterialPtr pChunkMat = cast_dynamic<ChunkMaterialPtr>(pFC);

        if(pChunkMat != NullFC)
        {
            StateChunkPtr cp = pChunkMat->find(TextureChunk::getClassType());
            
            TextureChunkPtr tex = NullFC;
            
            if(cp != NullFC)
                tex = cast_dynamic<TextureChunkPtr>(cp);
            
            if (pChunkMat->isTransparent() == true ||
                (tex != NullFC && tex->getImage() != NullFC && 
                 tex->getImage()->hasAlphaChannel()
               ))
            {
                BlendChunkPtr pBlendChunk = OSG::BlendChunk::create();

                if(tex != NullFC && tex->getImage() != NullFC &&
                   tex->getImage()->isAlphaBinary())
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

#if 0
            TextureChunkPtr pTexture =
                cast_dynamic<TextureChunkPtr>(_sfTexture.getValue());

            if(pChunkMat != NullFC)
            {
                if(pTexture != NullFC)
                {
                    pChunkMat->addChunk(pTexture);
                }
            }
            else
            {
                if(pTexture != NullFC)
                {
                    FieldContainerPtr pMat =
                        _pMaterialDesc->getDefaultMaterial()->shallowCopy();

                    ChunkMaterialPtr pChunkMat =
                        cast_dynamic<ChunkMaterialPtr>(pMat);

                    if(pChunkMat != NullFC)
                    {
                        if(pTexture != NullFC)
                        {
                            pChunkMat->addChunk(pTexture);
                        }

                        pMatGroup->setMaterial(pChunkMat);
                    }
                }
                else
                {
                    PWARNING << "No material, adding default" << std::endl;
                    pMatGroup->setMaterial(
                              _pMaterialDesc->getDefaultMaterial());
                }
    }
#endif

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Appearance " <<  std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                              Field Value                                */

bool VRMLAppearanceDesc::use(FieldContainerPtr)
{
    return false;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLAppearanceDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLMaterialDesc
    \ingroup GrpSystemFileIOVRML
    VRML Material description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLMaterialDesc::VRMLMaterialDesc(void) :
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

VRMLMaterialDesc::~VRMLMaterialDesc(void)
{
    subRef(_pDefMat);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLMaterialDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "MaterialDesc::init : " << szName << std::endl;
#endif
}

void VRMLMaterialDesc::reset(void)
{
    _pMat = NullFC;

    _ambientIntensity.setValue(_defaultAmbientIntensity);
    _diffuseColor    .setValue(_defaultDiffuseColor);
    _emissiveColor   .setValue(_defaultEmissiveColor);
    _shininess       .setValue(_defaultShininess);
    _specularColor   .setValue(_defaultSpecularColor);
    _transparency    .setValue(_defaultTransparency);
}

MaterialPtr VRMLMaterialDesc::getDefaultMaterial(void)
{
    return _pDefMat;
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLMaterialDesc::prototypeAddField(const Char8  *,
                                         const UInt32  ,
                                         const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("ambientIntensity", szFieldname) == 0)
    {
        _pCurrField = &_defaultAmbientIntensity;

        bFound = true;
    }
    else if(stringcasecmp("diffuseColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultDiffuseColor;

        bFound = true;
    }
    else if(stringcasecmp("emissiveColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultEmissiveColor;

        bFound = true;
    }
    else if(stringcasecmp("shininess", szFieldname) == 0)
    {
        _pCurrField = &_defaultShininess;

        bFound = true;
    }
    else if(stringcasecmp("specularColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultSpecularColor;

        bFound = true;
    }
    else if(stringcasecmp("transparency", szFieldname) == 0)
    {
        _pCurrField = &_defaultTransparency;

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

void VRMLMaterialDesc::endProtoInterface(void)
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
}

void VRMLMaterialDesc::getFieldAndDesc(
          FieldContainerPtr  ,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(stringcasecmp("ambientIntensity", szFieldname) == 0)
    {
        pField = &_ambientIntensity;
    }
    else if(stringcasecmp("diffuseColor", szFieldname) == 0)
    {
        pField = &_diffuseColor;
    }
    else if(stringcasecmp("emissiveColor", szFieldname) == 0)
    {
        pField = &_emissiveColor;
    }
    else if(stringcasecmp("shininess", szFieldname) == 0)
    {
        pField = &_shininess;
    }
    else if(stringcasecmp("specularColor", szFieldname) == 0)
    {
        pField = &_specularColor;
    }
    else if(stringcasecmp("transparency", szFieldname) == 0)
    {
        pField = &_transparency;
    }

    pDesc = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLMaterialDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    reset();

    _pMat = MaterialChunk::create();

    return _pMat;
}

void VRMLMaterialDesc::endNode(FieldContainerPtr)
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

void VRMLMaterialDesc::dump(const Char8 *)
{
}

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLTextureTransformDesc
    \ingroup GrpSystemFileIOVRML
    VRML Texture Transform description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLTextureTransformDesc::VRMLTextureTransformDesc(void) :
    Inherited(),
    _defaultCenter(),
    _defaultRotation(),
    _defaultScale(),
    _defaultTranslation(),

    _center(),
    _rotation(),
    _scale(),
    _translation()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLTextureTransformDesc::~VRMLTextureTransformDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLTextureTransformDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "TextureTransformDesc::init : " << szName << std::endl;
#endif
}

void VRMLTextureTransformDesc::reset(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLTextureTransformDesc::prototypeAddField(const Char8  *,
                                             const UInt32  ,
                                             const Char8  *szFieldname)
{
    bool bFound =false;

    _pCurrField = NULL;

    if(stringcasecmp("center", szFieldname) == 0)
    {
        _pCurrField = &_defaultCenter;

        bFound = true;
    }
    else if(stringcasecmp("rotation", szFieldname) == 0)
    {
        _pCurrField = &_defaultRotation;

        bFound = true;
    }
    else if(stringcasecmp("scale", szFieldname) == 0)
    {
        _pCurrField = &_defaultScale;

        bFound = true;
    }
    else if(stringcasecmp("translation", szFieldname) == 0)
    {
        _pCurrField = &_defaultTranslation;

        bFound = true;
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "TextureTransformDesc::prototypeAddField : add part "
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

void VRMLTextureTransformDesc::endProtoInterface(void)
{
}

void VRMLTextureTransformDesc::getFieldAndDesc(
          FieldContainerPtr  ,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(stringcasecmp("center", szFieldname) == 0)
    {
        pField = &_center;
    }
    else if(stringcasecmp("rotation", szFieldname) == 0)
    {
        pField = &_rotation;
    }
    else if(stringcasecmp("scale", szFieldname) == 0)
    {
        pField = &_scale;
    }
    else if(stringcasecmp("translation", szFieldname) == 0)
    {
        pField = &_translation;
    }

    pDesc = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLTextureTransformDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    TextureTransformChunkPtr returnValue = TextureTransformChunk::create();

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin TextureTransform " << &(*returnValue) << std::endl;

    incIndent();
#endif

    _center = _defaultCenter;
    _rotation = _defaultRotation;
    _scale = _defaultScale;
    _translation = _defaultTranslation;

    return returnValue;
}

void VRMLTextureTransformDesc::endNode(FieldContainerPtr pFC)
{
    TextureTransformChunkPtr pTexTrans = NullFC;

    pTexTrans = cast_dynamic<TextureTransformChunkPtr>(pFC);

    if(pTexTrans != NullFC)
    {
        Matrix     m;

        Vec3f center(_center.getValue()[0],
                     _center.getValue()[1], 0.0f);

        Quaternion rotation;
        rotation.setValueAsAxisRad(0.0f, 0.0f, 1.0f, _rotation.getValue());

        Vec3f scale(_scale.getValue()[0],
                    _scale.getValue()[1], 1.0f);
        
        Vec3f translation(_translation.getValue()[0],
                          _translation.getValue()[1], 0.0f);

        m.setTransform(translation,
                       rotation,
                       scale,
                       Quaternion::identity(),
                       center);

        pTexTrans->setMatrix(m);
    }
    else
    {
        PWARNING <<  "VRMLTextureTransformDesc::endNode : Invalid texture transform ptr"
                 << std::endl;
    }

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End TextureTransform "
          << _center.getValue() << " "
          << _rotation.getValue()    << " "
          << _scale.getValue()    << " "
          << _translation.getValue()    << " "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLTextureTransformDesc::dump(const Char8 *)
{
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLImageTextureDesc
    \ingroup GrpSystemFileIOVRML
    VRML Texture description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLImageTextureDesc::VRMLImageTextureDesc(void) :
    Inherited(),

    _defaultURL    (),
    _defaultRepeatS(),
    _defaultRepeatT(),

    _url           (),
    _repeatS       (),
    _repeatT       ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLImageTextureDesc::~VRMLImageTextureDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLImageTextureDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ImageTextureDesc::init : " << szName << std::endl;
#endif
}

void VRMLImageTextureDesc::reset(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLImageTextureDesc::prototypeAddField(const Char8  *,
                                             const UInt32  ,
                                             const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("url", szFieldname) == 0)
    {
        _pCurrField = &_defaultURL;

        bFound = true;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatS;

        bFound = true;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatT;

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

void VRMLImageTextureDesc::endProtoInterface(void)
{
}

void VRMLImageTextureDesc::getFieldAndDesc(
          FieldContainerPtr  ,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(stringcasecmp("url", szFieldname) == 0)
    {
        pField = &_url;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        pField = &_repeatS;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        pField = &_repeatT;
    }

    pDesc = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLImageTextureDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    TextureChunkPtr returnValue = TextureChunk::create();

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin ImageTexture " << &(*returnValue) << std::endl;

    incIndent();
#endif

    _url.clear();

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    return returnValue;
}

void VRMLImageTextureDesc::endNode(FieldContainerPtr pFC)
{
    TextureChunkPtr  pTexture = NullFC;

    ImagePtr         pImage   = NullFC;

    pTexture = cast_dynamic<TextureChunkPtr>(pFC);


    if(pTexture != NullFC)
    {
#ifdef OSG_DEBUG_VRML
        PNOTICE << "VRMLImageTextureDesc::endNode : Reading texture "
                << _url[0].c_str() << std::endl;
#endif

        pImage = ImageFileHandler::the()->read(_url[0].c_str());
        
        if(pImage != NullFC)
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
            pTexture->setEnvMode(GL_MODULATE);
        }
        else
        {
            PWARNING << "VRMLImageTextureDesc::endNode : "
                     << "Couldn't read texture "
                     << _url[0].c_str()
                     << " !!!"
                     << std::endl;

            subRef(pImage);
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

void VRMLImageTextureDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLPixelTextureDesc
    \ingroup GrpSystemFileIOVRML
    VRML Pixel Texture description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLPixelTextureDesc::VRMLPixelTextureDesc(void) :
    Inherited(),

    _defaultImage  (),
    _defaultRepeatS(),
    _defaultRepeatT(),

    _image         (),
    _repeatS       (),
    _repeatT       ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLPixelTextureDesc::~VRMLPixelTextureDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLPixelTextureDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "PixelTextureDesc::init : " << szName << std::endl;
#endif
}

void VRMLPixelTextureDesc::reset(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLPixelTextureDesc::prototypeAddField(const Char8  *,
                                             const UInt32  ,
                                             const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("image", szFieldname) == 0)
    {
        _pCurrField = &_defaultImage;

        bFound = true;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatS;

        bFound = true;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatT;

        bFound = true;
    }

    if(bFound == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "PixelTextureDesc::prototypeAddField : add part "
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

void VRMLPixelTextureDesc::endProtoInterface(void)
{
}

void VRMLPixelTextureDesc::getFieldAndDesc(
          FieldContainerPtr  ,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(stringcasecmp("image", szFieldname) == 0)
    {
        pField = &_image;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        pField = &_repeatS;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        pField = &_repeatT;
    }

    pDesc = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLPixelTextureDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    TextureChunkPtr returnValue = TextureChunk::create();

    ImagePtr iPtr=Image::create();
    _image.setValue(iPtr);

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin PixelTexture " << &(*returnValue) << std::endl;

    incIndent();
#endif

    return returnValue;
}

void VRMLPixelTextureDesc::endNode(FieldContainerPtr pFC)
{
    TextureChunkPtr  pTexture = NullFC;

    pTexture = cast_dynamic<TextureChunkPtr>(pFC);

    if(pTexture != NullFC)
    {
        if(_image.getValue() != NullFC)
        {
            pTexture->setImage(_image.getValue());

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
                pTexture->setWrapS(GL_CLAMP);
            }
        }
    }
    else
    {
        PWARNING <<  "VRMLPixelTextureDesc::endNode : Invalid texture ptr"
                 << std::endl;
    }

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
/*                              Field Value                                */

void VRMLPixelTextureDesc::addFieldValue(      Field *pField,
                                         const Char8 *szFieldVal)
{
    if(pField != NULL)
    {
        if( (pField == &_image) && (_image.getValue() != NullFC) )
        {
            _image.getValue()->addValue(szFieldVal);
        }
        else
        {
            pField->pushValueByStr(szFieldVal);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLPixelTextureDesc::dump(const Char8 *)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLLODDesc
    \ingroup GrpSystemFileIOVRML
    VRML Level Of Detail description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLLODDesc::VRMLLODDesc(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLLODDesc::~VRMLLODDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLLODDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "LODDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = DistanceLOD::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLLODDesc::prototypeAddField(const Char8  *szFieldType,
                                    const UInt32  uiFieldTypeId,
                                    const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("level", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("center", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("range", szFieldname) == 0)
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

void VRMLLODDesc::endProtoInterface(void)
{
}

void VRMLLODDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLLODDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pNode == NullFC)
    {
        PWARNING <<  "VRMLLODDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    DistanceLODPtr pLOD      = cast_dynamic<DistanceLODPtr>(pNodeCore);

    if(pLOD == NullFC)
    {
        PWARNING <<  "VRMLLODDesc::getFieldAndDesc : No LOD" << std::endl;
        return;
    }

    incIndent();

    if(stringcasecmp("level", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLLODDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pNode->getField("children");

        if(pField != NULL)
            pDesc = pNode->getFieldDescription("children");
    }
    else if(stringcasecmp("center", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLLODDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pLOD->getField("center");

        if(pField != NULL)
            pDesc = pLOD->getFieldDescription("children");
    }
    else if(stringcasecmp("range", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLLODDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pLOD->getField("range");

        if(pField != NULL)
            pDesc = pLOD->getFieldDescription("range");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pLOD,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLLODDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin LOD " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLLODDesc::endNode(FieldContainerPtr OSG_VRML_ARG(pFC))
{
#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End LOD "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLLODDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLSwitchDesc
    \ingroup GrpSystemFileIOVRML
    VRML Switch description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLSwitchDesc::VRMLSwitchDesc(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLSwitchDesc::~VRMLSwitchDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLSwitchDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "SwitchDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Switch::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLSwitchDesc::prototypeAddField(const Char8  *szFieldType,
                                       const UInt32  uiFieldTypeId,
                                       const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("choice", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
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

void VRMLSwitchDesc::endProtoInterface(void)
{
}

void VRMLSwitchDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLSwitchDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pNode == NullFC)
    {
        PWARNING << "VRMLSwitchDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    SwitchPtr pSwitch      = cast_dynamic<SwitchPtr>(pNodeCore);

    if(pSwitch == NullFC)
    {
        PWARNING << "VRMLSwitchDesc::getFieldAndDesc : No Switch" << std::endl;
        return;
    }

    incIndent();

    if(stringcasecmp("choice", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLSwitchDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pNode->getField("children");

        if(pField != NULL)
            pDesc = pNode->getFieldDescription("children");
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLSwitchDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pSwitch->getField("choice");

        if(pField != NULL)
            pDesc = pSwitch->getFieldDescription("whichChoice");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pSwitch,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLSwitchDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Switch " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLSwitchDesc::endNode(FieldContainerPtr OSG_VRML_ARG(pFC))
{
#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Switch "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLSwitchDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLGroupDesc
    \ingroup GrpSystemFileIOVRML
    VRML Group description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLGroupDesc::VRMLGroupDesc(void) :
    Inherited(),

    _defaultBoxCenter(),
    _defaultBoxSize  (),

    _boxCenter       (),
    _boxSize         ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLGroupDesc::~VRMLGroupDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLGroupDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GroupDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Group::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLGroupDesc::prototypeAddField(const Char8  *szFieldType,
                                      const UInt32  uiFieldTypeId,
                                      const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxCenter;
        bFound = true;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxSize;
        bFound = true;
    }
    else if(stringcasecmp("children", szFieldname) == 0)
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

void VRMLGroupDesc::endProtoInterface(void)
{
}

void VRMLGroupDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
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

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = &_boxCenter;
        pDesc  = NULL;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = &_boxSize;
        pDesc  = NULL;
    }
    else if(stringcasecmp("children", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = pNode->getField("children");

        if(pField != NULL)
            pDesc = pNode->getFieldDescription("children");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pGroup,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLGroupDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Group " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLGroupDesc::endNode(FieldContainerPtr OSG_VRML_ARG(pFC))
{
#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Group "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLGroupDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLExtrusionDesc
    \ingroup GrpSystemFileIOVRML
    VRML Extrusion description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLExtrusionDesc::VRMLExtrusionDesc(void) :
     Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLExtrusionDesc::~VRMLExtrusionDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLExtrusionDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ExtrusionDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
//    _pNodeCoreProto = Group::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLExtrusionDesc::prototypeAddField(const Char8  *szFieldType,
                                          const UInt32  uiFieldTypeId,
                                          const Char8  *szFieldname)
{
    _pCurrField = NULL;

    return Inherited::prototypeAddField(szFieldType,
                                        uiFieldTypeId,
                                        szFieldname);
}

void VRMLExtrusionDesc::endProtoInterface(void)
{
}

void VRMLExtrusionDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLExtrusionDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    incIndent();

    Inherited::getFieldAndDesc(pFC,
                               szFieldname,
                               pField,
                               pDesc);

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLExtrusionDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        returnValue = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(returnValue);

        pNode->addAttachment(pAtt);
    }

    return returnValue;
}

void VRMLExtrusionDesc::endNode(FieldContainerPtr pFC)
{
          Field            *pField = NULL;
    const FieldDescriptionBase *pDesc  = NULL;
          NodePtr           pNode  = NullFC;

    FLOG (("Run VRMLExtrusionDesc::endNode()\n"));

    if(pFC == NullFC)
        return;

    pNode = cast_dynamic<NodePtr>(pFC);

    if(pNode == NullFC)
        return;

    SFBool       *pBeginCap     = NULL;
    SFBool       *pCcw          = NULL;
    SFBool       *pConvex       = NULL;
    SFReal32     *pCreaseAngle  = NULL;
    MFPnt2f      *pCrossSection = NULL;
    SFBool       *pEndCap       = NULL;
    MFQuaternion *pOrientation  = NULL;
    MFVec2f      *pScale        = NULL;
    SFBool       *pSolid        = NULL;
    MFPnt3f      *pSpine        = NULL;

    Inherited::getFieldAndDesc(pFC,
                               "beginCap",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pBeginCap = static_cast<SFBool *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "ccw",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCcw = static_cast<SFBool *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "convex",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pConvex = static_cast<SFBool *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "creaseAngle",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCreaseAngle = static_cast<SFReal32 *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "crossSection",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCrossSection = static_cast<MFPnt2f *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "endCap",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pEndCap = static_cast<SFBool *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "orientation",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pOrientation = static_cast<MFQuaternion *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "scale",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pScale = static_cast<MFVec2f *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "solid",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pSolid = static_cast<SFBool *>(pField);
    }


    Inherited::getFieldAndDesc(pFC,
                               "spine",
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pSpine = static_cast<MFPnt3f *>(pField);
    }



    if(pBeginCap     != NULL &&
       pCcw          != NULL &&
       pConvex       != NULL &&
       pCreaseAngle  != NULL &&
       pCrossSection != NULL &&
       pEndCap       != NULL &&
       pOrientation  != NULL &&
       pScale        != NULL &&
       pSolid        != NULL &&
       pSpine        != NULL)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLExtrusionDesc::endNode"
              << std::endl;
#endif

        // TODO: creaseAngle/numOfSubdivision param/handling ?
#ifdef OSG_EXTRUSION_SUPPORT
        GeometryPtr pGeo = makeExtrusionGeo ( pCrossSection->getValues(),
                                              pOrientation ->getValues(),
                                              pScale       ->getValues(),
                                              pSpine       ->getValues(),
					      pCreaseAngle ->getValue (),
                                              pBeginCap    ->getValue (),
                                              pEndCap      ->getValue (),
                                              pCcw         ->getValue (),
                                              pConvex      ->getValue (),
                                              true, // buildNormal
                                              true, // buildTexCoord
                                              0     // numOfSubdivision
                                              );

/*
// snip remove later
        fprintf(stderr, "%u %u %u %f | %u | %u | %u %u | %u | %u\n",
                pBeginCap    ->getValue (),
                pCcw         ->getValue (),
                pConvex      ->getValue (),
                pCreaseAngle ->getValue (),
                pCrossSection->size     (),
                pEndCap      ->getValue (),
                pOrientation ->size     (),
                pScale       ->size     (),
                pSolid       ->getValue (),
                pSpine       ->size     ());

// snap end remove later2
*/

        pNode->setCore(pGeo);
#endif
    }
    else
    {
        FWARNING(("\n\nExtrusion parameter missing\n"));
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLExtrusionDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLInlineDesc
    \ingroup GrpSystemFileIOVRML
    VRML Inline description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLInlineDesc::VRMLInlineDesc(void) :
    Inherited(),

    _defaultBoxCenter(),
    _defaultBoxSize  (),

    _boxCenter       (),
    _boxSize         ()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLInlineDesc::~VRMLInlineDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLInlineDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "InlineDesc::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Inline::create();

    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);
}

/*-------------------------------------------------------------------------*/
/*                                Field                                    */

bool VRMLInlineDesc::prototypeAddField(const Char8  *szFieldType,
                                       const UInt32  uiFieldTypeId,
                                       const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxCenter;
        bFound = true;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxSize;
        bFound = true;
    }
    else if(stringcasecmp("url", szFieldname) == 0)
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

void VRMLInlineDesc::endProtoInterface(void)
{
}

void VRMLInlineDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "VRMLInlineDesc::getFieldAndDesc : looking for "
          << szFieldname
          << std::endl;
#endif

    if(pNode == NullFC)
    {
        PWARNING <<  "VRMLInlineDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    InlinePtr pInline     = cast_dynamic<InlinePtr>(pNodeCore);

    if(pInline == NullFC)
    {
        PWARNING <<  "VRMLInlineDesc::getFieldAndDesc : No Inline" << std::endl;
        return;
    }

    incIndent();

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLInlineDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = &_boxCenter;
        pDesc  = NULL;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "VRMLInlineDesc::getFieldAndDesc :  : request internal "
              << szFieldname
              << std::endl;
#endif

        pField = &_boxSize;
        pDesc  = NULL;
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pInline,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }

#ifdef OSG_DEBUG_VRML
    decIndent();
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLInlineDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Inline" << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLInlineDesc::endNode(FieldContainerPtr pFC)
{    
    const Field            *pField;
    const FieldDescriptionBase *pFieldDesc;

    NodePtr pNode = cast_dynamic<NodePtr>(pFC);

    VRMLNodeDesc::getFieldAndDesc(pFC, 
                                  "url", 
                                  pField,
                                  pFieldDesc);

    const MFString *pUrl = dynamic_cast<const MFString *>(pField);

    FDEBUG(("Inline : %s\n",  (*pUrl)[0].c_str()));

    VRMLFile *pVRMLLoader = new VRMLFile();

    pVRMLLoader->createStandardPrototypes();

    std::string filename =
    SceneFileHandler::the()->getPathHandler()->findFile((*pUrl)[0].c_str());

    // read it via stream could be a compressed file.
    std::ifstream in(filename.c_str(), std::ios::binary);
    if(in)
    {
        std::string path = SceneFileHandler::the()->getPathHandler()->
                           extractPath(filename.c_str());

        SceneFileHandler::the()->getPathHandler()->push_backPath(path.c_str());
        ImageFileHandler::the()->getPathHandler()->push_backPath(path.c_str());

        if(OSG::isGZip(in))
        {
#ifdef OSG_ZSTREAM_SUPPORTED
            zip_istream unzipper(in);
            pVRMLLoader->scanStream(unzipper);
#else
            FWARNING(("zstream no configured, could not read "
                      "compressed file"));
#endif
        }
        else
        {
            pVRMLLoader->scanStream(in);
        }
        in.close();
        ImageFileHandler::the()->getPathHandler()->subPath(path.c_str());
        SceneFileHandler::the()->getPathHandler()->subPath(path.c_str());
    }
    //pVRMLLoader->scanFile(filename.c_str());

    NodePtr pFile = pVRMLLoader->getRoot();

//    NodePtr pFile = SceneFileHandler::the()->read((*pUrl)[0].c_str());

    if(pFile != NullFC)
    {
        pNode->addChild(pFile);
    }

    delete pVRMLLoader;

#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Inline "
          << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLInlineDesc::dump(const Char8 *)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class OSG::VRMLViewpointDesc
    \ingroup GrpSystemFileIOVRML
    VRML Viewpoint description
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLViewpointDesc::VRMLViewpointDesc(void) :
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLViewpointDesc::~VRMLViewpointDesc(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

void VRMLViewpointDesc::init(const Char8 *OSG_VRML_ARG(szName))
{
#ifdef OSG_DEBUG_VRML
    PINFO << "Viewpoint init : " << szName << std::endl;
#endif

    _pNodeProto     = Node::create();
    _pNodeCoreProto = ComponentTransform::create();
    _pGenAtt        = GenericAtt::create();
    _pGenAtt->setInternal(true);

    FieldDescriptionBase *pDesc =
        new FieldDescription(SFBool::getClassType(),
                             "isViewpoint",
                             0, 0,
                             false,
                             (FieldIndexAccessMethod)
                             &GenericAtt::getDynamicField);


    _pGenAtt->addField(*pDesc);
}

void VRMLViewpointDesc::reset(void)
{
 //   _pCamera = PerspectiveCamera::NullFC;

//    _beaconNode = NullNode;
///    _beaconCore = ComponentTransformPtr::NullPtr;
//    _viewpointAttachment = ViewpointAttachmentPtr::NullPtr;
//
//    _defaultOrientation.setValue(_orientation);
//    _defaultPosition   .setValue(_position);
}

ComponentTransformPtr VRMLViewpointDesc::getDefaultBeacon(void)
{
    return NullFC;
}

/*
FieldContainerPtr VRMLViewpointDesc::getSaveFieldContainer(void)
{
    return getDefaultBeacon();
}
*/

/*-------------------------------------------------------------------------*/
/*                               Field                                     */

bool VRMLViewpointDesc::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("orientation", szFieldname) == 0)
    {
        _pCurrField = _pNodeCoreProto->getField("rotation");

        bFound = true;
    }
    else if(stringcasecmp("position", szFieldname) == 0)
    {
        _pCurrField = _pNodeCoreProto->getField("translation");

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

void VRMLViewpointDesc::endProtoInterface(void)
{
}

void VRMLViewpointDesc::getFieldAndDesc(
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
    const Field            *&pField,
    const FieldDescriptionBase *&pDesc)
{
#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "ViewpointDesc::getFieldAndDesc : request "
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
        PWARNING << "ViewpointDesc::getFieldAndDesc : No Node" << std::endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    ComponentTransformPtr pTransform = cast_dynamic<ComponentTransformPtr>(pNodeCore);

    if(pTransform == NullFC)
    {
        PWARNING << "ViewpointDesc::getFieldAndDesc : No Geo" << std::endl;
        return;
    }

    if(stringcasecmp("orientation", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "ViewpointDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pTransform->getField("rotation");

        if(pField != NULL)
            pDesc = pTransform->getFieldDescription("rotation");
    }
    else if(stringcasecmp("position", szFieldname) == 0)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(getIndent(), PINFO);
        PINFO << "ViewpointDesc::getFieldAndDesc : internal "
              << szFieldname << std::endl;
#endif

        pField = pTransform->getField("translation");

        if(pField != NULL)
            pDesc = pTransform->getFieldDescription("translation");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pTransform,
                                      szFieldname,
                                      pField,
                                      pDesc);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Node                                     */

FieldContainerPtr VRMLViewpointDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  )
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullFC;
    NodeCorePtr       pNodeCore   = NullFC;
    GenericAttPtr     pAtt        = NullFC;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();

        pAtt = cast_dynamic<GenericAttPtr>(pAttClone);

        if(pAtt != NullFC)
        {
            pAtt->setInternal(true);
        }

        pFC = _pNodeProto->shallowCopy();

        pNode = cast_dynamic<NodePtr>(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = cast_dynamic<NodeCorePtr>(pFC);

        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "Begin Viewpoint " << &(*pNode) << std::endl;

    incIndent();
#endif

    return pNode;
}

void VRMLViewpointDesc::endNode(FieldContainerPtr OSG_VRML_ARG(pFC))
{
#ifdef OSG_DEBUG_VRML
    decIndent();

    indentLog(getIndent(), PINFO);
    PINFO << "End Viewpoint " << &(*pFC) << std::endl;
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void VRMLViewpointDesc::dump(const Char8 *)
{
}

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

#include <OSGSField.ins>
#include <OSGMField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

DataType FieldTraits<GenericAttPtr>::_type("GenericAttPtr",
                                                "AttachmentPtr"     );

OSG_FIELD_DLLEXPORT_DEF1(SField, GenericAttPtr);
OSG_FIELD_DLLEXPORT_DEF1(MField, GenericAttPtr);

OSG_END_NAMESPACE

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
    static Char8 cvsid_hpp[] = OSGVRMLNODEDESCS_HEADER_CVSID;
}

#endif
