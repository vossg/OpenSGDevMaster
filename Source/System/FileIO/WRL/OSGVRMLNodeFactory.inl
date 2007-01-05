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
#include "OSGLog.h"

//#include <OSGFieldFactory.h>
#include "OSGTransform.h"

#include <iostream>

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


OSG_BEGIN_NAMESPACE

/*! \class OSG::VRMLNodeFactory
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BaseT> inline
VRMLNodeFactory<BaseT>::VRMLNodeFactory(void) :
    Inherited(),

    _pCurrentNodeDesc(NULL),
    _mNodeDescHash   (),

    _bInFieldProto   (false),

    _bIgnoreProto    (false)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class BaseT> inline
VRMLNodeFactory<BaseT>::~VRMLNodeFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Skel Replacements                            */

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginProto(
    const Char8 *szProtoname)
{
#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "Begin Proto " << szProtoname << std::endl;
#endif

    Char8 *szName = NULL;

    NodeNameDescHash::iterator mNodeDescIt =
        _mNodeDescHash.find(szProtoname);

    if(mNodeDescIt == _mNodeDescHash.end())
    {
        if(osgStringCaseCmp("IndexedFaceSet", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryDesc(true);

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("IndexedLineSet", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryDesc(false);

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("PointSet", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPointSetDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Shape", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLShapeDesc;

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Coordinate", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPartDesc("point",
                                                         "positions",
                                                         "GeoPositions3f");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Normal", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPartDesc("vector",
                                                         "normals",
                                                         "GeoNormals3f");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Color", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPartDesc("color",
                                                         "colors",
                                                         "GeoColors3f");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("TextureCoordinate", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPartDesc("point",
                                                         "TexCoords",
                                                         "GeoTexCoords2f");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Appearance", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLAppearanceDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Material", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLMaterialDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Box", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Box");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Cone", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Cone");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Cylinder", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Cylinder");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Sphere", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Sphere");

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("TextureTransform", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLTextureTransformDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("ImageTexture", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLImageTextureDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("PixelTexture", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLPixelTextureDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("LOD", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLLODDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Switch", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLSwitchDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Group", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGroupDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Inline", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLInlineDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Viewpoint", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLViewpointDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else if(osgStringCaseCmp("Extrusion", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLExtrusionDesc();

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }
        else
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLNodeDesc;

            _pCurrentNodeDesc->init(szProtoname);

            _mNodeDescHash[szName] = _pCurrentNodeDesc;
        }

    }
    else
    {
#ifdef OSG_DEBUG_VRML
        indentLog(VRMLNodeDesc::getIndent(), PINFO);
        PINFO << "Could not add second proto named "
              << szProtoname
              << std::endl;
#endif

        _bIgnoreProto = true;
    }

    VRMLNodeDesc::incIndent();
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endProto  (void)
{
    if(_pCurrentNodeDesc != NULL)
        _pCurrentNodeDesc->endProtoInterface();

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::decIndent();
#endif

    _bIgnoreProto = false;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginEventInDecl(
    const Char8  *OSG_VRML_ARG(szEventType),
    const UInt32,
    const Char8  *OSG_VRML_ARG(szEventName))
{
    if(_bIgnoreProto == true)
        return;

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "AddEventIn " << szEventType << " " << szEventName << std::endl;
#endif
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginEventOutDecl(
    const Char8  *OSG_VRML_ARG(szEventType),
    const UInt32,
    const Char8  *OSG_VRML_ARG(szEventName))
{
    if(_bIgnoreProto == true)
        return;

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "AddEventOut " << szEventType << " " << szEventName << std::endl;
#endif
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginFieldDecl(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    bool rc;

    if(_bIgnoreProto == true)
        return;

    if(_pCurrentNodeDesc != NULL)
    {
        rc = _pCurrentNodeDesc->prototypeAddField(
            szFieldType,
            Self::mapIntExtFieldType(szFieldName, uiFieldTypeId),
            szFieldName);

        if(rc == true)
        {
            _bInFieldProto = true;
        }
    }
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endFieldDecl(void)
{
    _bInFieldProto = false;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginExposedFieldDecl(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    beginFieldDecl(szFieldType, uiFieldTypeId, szFieldName);
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endExposedFieldDecl(void)
{
    endFieldDecl();
}

#if 0
template <class BaseT> inline
OSG::NodePtr VRMLNodeFactory<BaseT>::getNode(const Char8 *szNodename)
{
    OSG::NodePtr              returnValue = OSG::NullNode;
    OSG::FieldContainerPtr    pTmp;
    NodeProtoMap::iterator gIt;

    if(szNodename == NULL)
        return returnValue;

    gIt = _mNodeProtos.find(IDStringLink(szNodename));

    if(gIt != _mNodeProtos.end())
    {
        pTmp = (*gIt).second->clone();

        if(pTmp != OSG::NullFC)
            returnValue = pTmp.dcast<OSG::NodePtr>();
    }

    return returnValue;
}
#endif

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addFieldValue(const Char8 *szFieldVal)
{
    if(_bInFieldProto == true)
    {
#ifdef OSG_DEBUG_VRML
        indentLog(VRMLNodeDesc::getIndent(), PINFO);

        PINFO << "Add proto field value : " << szFieldVal << std::endl;
#endif
    }

    if(_pCurrentNodeDesc != NULL)
    {
        _pCurrentNodeDesc->prototypeAddFieldValue(szFieldVal);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::dumpTable(void)
{
    NodeNameDescHash::iterator  mNodeDescIt = _mNodeDescHash.begin();

    while(mNodeDescIt != _mNodeDescHash.end())
    {
//        fprintf(stderr, "NodeDesc : %s\n", mNodeDescIt->first);

        mNodeDescIt->second->dump(mNodeDescIt->first);

        mNodeDescIt++;
    }
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

template <class BaseT> inline
VRMLNodeDesc *VRMLNodeFactory<BaseT>::findNodeDesc(const Char8 *szNodeTypename)
{
    VRMLNodeDesc *returnValue = NULL;

    NodeNameDescHash::iterator mNodeDescIt =
        _mNodeDescHash.find(szNodeTypename);

    if(mNodeDescIt != _mNodeDescHash.end())
    {
#ifdef OSG_DEBUG_VRML
        indentLog(VRMLNodeDesc::getIndent(), PINFO);
        PINFO << "Found Node "
              << mNodeDescIt->first << " ("
              << szNodeTypename     << ")" << std::endl;
#endif

        returnValue = mNodeDescIt->second;
    }

    return returnValue;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addNodeDesc(const Char8        *szNodeTypename,
                                               VRMLNodeDesc *pDesc)
{
    Char8 *szName = NULL;

    if(szNodeTypename == NULL || pDesc == NULL)
        return;

    osgStringDup(szNodeTypename, szName);

    _mNodeDescHash[szName] = pDesc;

    _pCurrentNodeDesc = pDesc;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::preStandardProtos (void)
{
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::postStandardProtos(void)
{
    VRMLNodeDesc         *pNodeDesc         = NULL;
    VRMLShapeDesc        *pShapeDesc        = NULL;
    VRMLAppearanceDesc   *pAppearanceDesc   = NULL;
    VRMLMaterialDesc     *pMaterialDesc     = NULL;

    pNodeDesc = findNodeDesc("Shape");

    if(pNodeDesc != NULL)
    {
        pShapeDesc = dynamic_cast<VRMLShapeDesc *>(pNodeDesc);
    }

    pNodeDesc = findNodeDesc("Appearance");

    if(pNodeDesc != NULL)
    {
        pAppearanceDesc = dynamic_cast<VRMLAppearanceDesc *>(pNodeDesc);
    }

    pNodeDesc = findNodeDesc("Material");

    if(pNodeDesc != NULL)
    {
        pMaterialDesc = dynamic_cast<VRMLMaterialDesc *>(pNodeDesc);
    }

    if(pShapeDesc != NULL)
    {
        pShapeDesc->setMaterialDesc(pMaterialDesc);
    }

    if(pAppearanceDesc != NULL)
    {
        pAppearanceDesc->setMaterialDesc(pMaterialDesc);
    }
}

OSG_END_NAMESPACE

#define OSGVRNLNODEFACTORY_INLINE_CVSID "@(#)$Id$"
