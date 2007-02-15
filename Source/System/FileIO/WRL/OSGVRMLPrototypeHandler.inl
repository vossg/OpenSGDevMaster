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

/*! \class OSG::VRMLPrototypeHandler
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BaseT> inline
VRMLNodePrototypeHandler<BaseT>::VRMLNodePrototypeHandler(void) :
     Inherited      (    ),

    _pCurrentHelper (NULL),
    _mNodeHelperHash(    )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class BaseT> inline
VRMLNodePrototypeHandler<BaseT>::~VRMLNodePrototypeHandler(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Skel Replacements                            */

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::beginProto(const Char8 *szProtoname)
{
#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "Begin Proto " << szProtoname << std::endl;
#endif

    Char8 *szName = NULL;

    NameHelperMap::iterator mNodeHelperIt = 
        _mNodeHelperHash.find(szProtoname);

    if(mNodeHelperIt == _mNodeHelperHash.end())
    {
        VRMLNodeHelper *pNewHelper = 
            VRMLNodeHelperFactory::the()->createHelper(szProtoname);

        if(pNewHelper == NULL)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentHelper = VRMLDefaultHelper::create();

            _pCurrentHelper->init(szProtoname);

            _mNodeHelperHash[szName] = _pCurrentHelper;
        }
        else
        {
            osgStringDup(szProtoname, szName);

            _pCurrentHelper = pNewHelper;

            _pCurrentHelper->init(szProtoname);

            _mNodeHelperHash[szName] = _pCurrentHelper;
        }
    }
    else
    {
        fprintf(stderr, "Helper already present for %s\n", szProtoname);
    }

#if 0
    Char8 *szName = NULL;
    if(mNodeDescIt == _mNodeDescHash.end())
    {
        else if(osgStringCaseCmp("PointSet", szProtoname) == 0)
        {
            osgStringDup(szProtoname, szName);

            _pCurrentNodeDesc = new VRMLGeometryPointSetDesc();

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
    }

#endif

    VRMLNodeHelper::incIndent();
    VRMLNodeHelper::incIndent();
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::endProtoInterface(void)
{
    if(_pCurrentHelper != NULL)
        _pCurrentHelper->endProtoInterface();

#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();
#endif
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::endProto(void)
{
#ifdef OSG_DEBUG_VRML
    VRMLNodeHelper::decIndent();
#endif
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::beginEventInDecl(
    const Char8  *OSG_VRML_ARG(szEventType),
    const UInt32,
    const Char8  *OSG_VRML_ARG(szEventName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "AddEventIn " << szEventType << " " << szEventName << std::endl;
#endif
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::beginEventOutDecl(
    const Char8  *OSG_VRML_ARG(szEventType),
    const UInt32,
    const Char8  *OSG_VRML_ARG(szEventName))
{
#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "AddEventOut " << szEventType << " " << szEventName << std::endl;
#endif
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::beginFieldDecl(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeHelper::getIndent(), PINFO);
    PINFO << "AddField " 
          << szFieldType 
          << " " << uiFieldTypeId 
          << " " << szFieldName 
          << std::endl;
#endif

    if(_pCurrentHelper != NULL)
    {
        _pCurrentHelper->prototypeAddField(
            szFieldType,
            Self::mapIntExtFieldType(szFieldName, uiFieldTypeId),
            szFieldName);
    }
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::endFieldDecl(void)
{
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::beginExposedFieldDecl(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    beginFieldDecl(szFieldType, uiFieldTypeId, szFieldName);
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::endExposedFieldDecl(void)
{
    endFieldDecl();
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */


/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

template <class BaseT> inline
VRMLNodeHelper *VRMLNodePrototypeHandler<BaseT>::findNodeHelper(
    const Char8 *szNodeTypename)
{
    VRMLNodeHelper *returnValue = NULL;

    NameHelperMap::iterator mNodeHelperIt =
        _mNodeHelperHash.find(szNodeTypename);

    if(mNodeHelperIt != _mNodeHelperHash.end())
    {
#ifdef OSG_DEBUG_VRML
        indentLog(VRMLNodeHelper::getIndent(), PINFO);
        PINFO << "Found Node "
              << mNodeHelperIt->first << " ("
              << szNodeTypename     << ")" << std::endl;
#endif

        returnValue = mNodeHelperIt->second;
    }

    return returnValue;
}


template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::preStandardProtos (void)
{
}

template <class BaseT> inline
void VRMLNodePrototypeHandler<BaseT>::postStandardProtos(void)
{
    VRMLNodeHelper         *pNodeHelper         = NULL;
    VRMLShapeHelper        *pShapeHelper        = NULL;
    VRMLAppearanceHelper   *pAppearanceHelper   = NULL;
    VRMLMaterialHelper     *pMaterialHelper     = NULL;

    pNodeHelper = findNodeHelper("Shape");

    if(pNodeHelper != NULL)
    {
        pShapeHelper = dynamic_cast<VRMLShapeHelper *>(pNodeHelper);
    }

    pNodeHelper = findNodeHelper("Appearance");

    if(pNodeHelper != NULL)
    {
        pAppearanceHelper = dynamic_cast<VRMLAppearanceHelper *>(pNodeHelper);
    }

    pNodeHelper = findNodeHelper("Material");

    if(pNodeHelper != NULL)
    {
        pMaterialHelper = dynamic_cast<VRMLMaterialHelper *>(pNodeHelper);
    }

    if(pShapeHelper != NULL)
    {
        pShapeHelper->setMaterialHelper(pMaterialHelper);
    }

    if(pAppearanceHelper != NULL)
    {
        pAppearanceHelper->setMaterialHelper(pMaterialHelper);
    }
}

OSG_END_NAMESPACE

#define OSGVRMLPROTOTYPEHANDLER_INLINE_CVSID "@(#)$Id$"
