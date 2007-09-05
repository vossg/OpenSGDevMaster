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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGOSGLoader.h"
#include <OSGLog.h>


#include <OSGSysSFields.h>
#include <OSGSysMFields.h>

#include <OSGBaseSFields.h>
#include <OSGBaseMFields.h>

#include <OSGMathSFields.h>
#include <OSGMathMFields.h>

#include <OSGVecSFields.h>
#include <OSGVecMFields.h>

#include <OSGFieldContainerSFields.h>
#include <OSGFieldContainerMFields.h>

#include <OSGFieldContainerFactory.h>
#include <OSGFieldContainer.h>

#include <OSGNode.h>
#include <OSGGroup.h>

#include <OSGAttachmentMapSFields.h>

//#include <OSGSimpleAttachments.h>



OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGLoader::initFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfBool);

/*
    setIntExtMapping(ScanParseSkel::OSGsfColor,
               ::getClassType().getId());
*/

    setIntExtMapping(SFReal32::getClassType().getId(),
                     ScanParseSkel::OSGsfFloat);
/*
    setIntExtMapping(SFImagePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfString);
*/
    setIntExtMapping(SFInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);


    setIntExtMapping(SFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGsfRotation);

    setIntExtMapping(SFString::getClassType().getId(),
                     ScanParseSkel::OSGsfString);

    setIntExtMapping(SFTime::getClassType().getId(),
                     ScanParseSkel::OSGsfTime);

    setIntExtMapping(SFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2f);

    setIntExtMapping(SFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);

    setIntExtMapping(SFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec4f);

    setIntExtMapping(SFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor4f);

    setIntExtMapping(SFColor4ub::getClassType().getId(),
                     ScanParseSkel::OSGsfColor4i);

    setIntExtMapping(SFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor3f);

/*
    setIntExtMapping(ScanParseSkel::OSGmfColor,
               ::getClassType().getId());
*/

    setIntExtMapping(MFReal32::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);

    setIntExtMapping(MFInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(MFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGmfRotation);

    setIntExtMapping(MFString::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFTime::getClassType().getId(),
                     ScanParseSkel::OSGmfTime);


    setIntExtMapping(MFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec2f);

    setIntExtMapping(MFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec4f);

    setIntExtMapping(MFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor4f);

    setIntExtMapping(MFColor4ub::getClassType().getId(),
                     ScanParseSkel::OSGmfColor4i);

    setIntExtMapping(MFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor3f);

    setIntExtMapping(SFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);


    /* To Base Type Mappings */

    setIntExtMapping(SFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    setIntExtMapping(SFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFInt16::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFInt16::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    setIntExtMapping(SFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFGLenum::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFGLenum::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    /* To Node Mappings */

    setIntExtMapping(SFFieldContainerAttachmentPtrMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    /* extended types */

    setIntExtMapping(SFMatrix::getClassType().getId(),
                     ScanParseSkel::OSGsfMatrix);

    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt3f);

    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt3f);
    setIntExtMapping(SFDynamicVolume::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);

    setIntExtMapping(SFPlane::getClassType().getId(),
                     ScanParseSkel::OSGsfPlane);
    setIntExtMapping(MFPlane::getClassType().getId(),
                     ScanParseSkel::OSGmfPlane);

    setIntExtMapping(SFDynamicVolume::getClassType().getId(),
                     ScanParseSkel::OSGsfVolume);
}

void OSGLoader::setFieldContainerValue(FieldContainerPtr pNewNode)
{
    if(_pCurrentField != NullFC)
    {
        SFFieldContainerPtr::EditHandlePtr pSFHandle = 
            boost::dynamic_pointer_cast<SFFieldContainerPtr::EditHandle>(
                _pCurrentField);

        MFFieldContainerPtr::EditHandlePtr pMFHandle = 
            boost::dynamic_pointer_cast<MFFieldContainerPtr::EditHandle>(
                _pCurrentField);

        if(pSFHandle != NULL && pSFHandle->isValid())
        {
            pSFHandle->setValue(pNewNode);
        }
        else if(pMFHandle != NULL && pMFHandle->isValid())
        {
            pMFHandle->add(pNewNode);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGLoader::OSGLoader(void) :
     Inherited        (      ),
    _pCurrentFC       (NullFC),
    _pRootNode        (NullFC),
    _pCurrentField    (      ),
    _pCurrentFieldDesc(NULL  ),
    _defMap           (      ),
    _fcStack          (      ),
    _fStack           (      ),
    _fdStack          (      ),
    _bvChanged        (     0),
    _sChangedStack    (      )
{
    Self::setReferenceHeader("#OSG V1.0 ");
    initFieldTypeMapper();
}

/** \brief Destructor
 */

OSGLoader::~OSGLoader(void)
{
}

/*------------------------------ access -----------------------------------*/

void OSGLoader::scanStream(std::istream &is)
{
    if(is)
    {
        _pRootNode         = NullFC;
        _pCurrentFC        = NullFC;

        _pCurrentField.reset();

        _pCurrentFieldDesc = NULL;

        _defMap .clear();

        Inherited::scanStream(is);
    }
}

#if defined(OSG_WIN32_ICL)
#pragma warning (disable : 383)
#endif

void OSGLoader::beginNode(const Char8 *szNodeTypename,
                          const Char8 *szNodename)
{
    FieldContainerPtr pNewNode;

    if(szNodeTypename == NULL)
        return;

    PINFO << "Begin node : " << szNodeTypename << " | ";

    if(szNodename == NULL)
    {
        PINFO << "NULL";
    }
    else
    {
        PINFO << szNodename;
    }

    PINFO << std::endl;

    pNewNode =
        FieldContainerFactory::the()->createContainer(szNodeTypename);

    
    PINFO << "  Got ptr " << pNewNode << std::endl;

    if(szNodename != NULL && pNewNode != NullFC)
    {
#ifdef DO_CHECK
        AttachmentContainerPtr pAttCon =
            AttachmentContainerPtr::dcast(pNewNode);

        if(pAttCon != NullFC)
        {
            setName(pAttCon, szNodename);
        }
#endif

        _defMap.insert(std::make_pair(std::string(szNodename), pNewNode));
    }

    // assign nodepointer to current sf|mf field
    setFieldContainerValue(pNewNode);

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        NodePtr pNode = NullFC;

        if(_pCurrentFC->getType().isNode())
        {
            pNode = dynamic_cast<NodePtr>(_pCurrentFC);
        }
        else if(_pCurrentFC->getType().isNodeCore())
        {
            pNode = Node::create();

            pNode->setCore(dynamic_cast<NodeCorePtr>(_pCurrentFC));
        }
        else
        {
            SLOG << "Fieldcontainer " << szNodeTypename
                 << "is neither Node nor NodeCore " << std::endl;
        }

        if(_pRootNode == NullFC)
        {
            GroupPtr pGroup = Group::create();

            _pRootNode = Node::create();

            _pRootNode->setCore(pGroup);
        }

        _pRootNode->addChild(pNode);
    }

    _sChangedStack.push(_bvChanged);

    _bvChanged = 0;
}

#if defined(OSG_WIN32_ICL)
#pragma warning (default : 383)
#endif

void OSGLoader::endNode(void)
{
    PINFO << "End Node" << std::endl;

    if(_pCurrentFC != NullFC)
    {
        if(_pCurrentFC->getType().isNode() == true)
        {
            NodePtr pNode = dynamic_cast<NodePtr>(_pCurrentFC);

            if(pNode->getCore() == NullFC)
            {
                GroupPtr pGroup = Group::create();

                pNode->setCore(pGroup);
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
        _pCurrentFC = NullFC;
    }

    if(_sChangedStack.size() != 0)
    {
        _bvChanged = _sChangedStack.top();
    }
    else
    {
        _bvChanged = 0;
    }

    _sChangedStack.pop();

}

void OSGLoader::nullNode(void)
{
    setFieldContainerValue(NullFC);
}

void OSGLoader::use(const Char8 *szName)
{
    FieldContainerPtr pUseNode;

    // try to find a container with the given name attachment

    pUseNode = getReference(szName);

    if(pUseNode == NullFC)
    {
        SLOG << "No FieldContainer found with name " << szName << std::endl;
    }
    else
    {
        // assign nodepointer to current sf|mf field
        setFieldContainerValue(pUseNode);
    }
}

NodePtr OSGLoader::getRootNode(void)
{
    return _pRootNode;
}

std::vector<FieldContainerPtr> OSGLoader::getRootNodes(void)
{
    std::vector<FieldContainerPtr> fcVec;

    for( UInt32 i=0; i<_pRootNode->getNChildren(); ++i )
    {
        fcVec.push_back(_pRootNode->getChild(i));
    }

    return fcVec;
}

void OSGLoader::addFieldValue(const Char8 *szFieldVal)
{
    PINFO << "\t\tFV : " << szFieldVal << std::endl;

    if(_pCurrentField != NULL)
    {
//        _pCurrentFieldDesc->pushValueFromCString( szFieldVal,
//                                                 _pCurrentField);

        _pCurrentField->pushValueFromCString(szFieldVal);
    }
}

UInt32 OSGLoader::getFieldType(const Char8 *szFieldname)
{
    UInt32                returnValue = 0;
    FieldDescriptionBase *pFieldDesc  = NULL;

    if(szFieldname == NULL)
        return returnValue;

    if(_pCurrentFC != NullFC)
    {
        pFieldDesc = _pCurrentFC->getFieldDescription(szFieldname);

        PINFO << "GF : " << szFieldname << " " << pFieldDesc << std::endl;

        if(pFieldDesc != NULL)
        {
            returnValue = pFieldDesc->getFieldType().getScanTypeId();
        }
    }

    return returnValue;
}

Int32 OSGLoader::mapExtIntFieldType(const Char8 *szFieldname,
                                    const Int32  iFieldTypeId)
{
    Int32 returnValue = Inherited::mapExtIntFieldType(szFieldname,
                                                      iFieldTypeId);

    if(returnValue < 0 && szFieldname != NULL && _pCurrentFC != NullFC)
    {
        FieldDescriptionBase *pFieldDesc = 
            _pCurrentFC->getFieldDescription(szFieldname);

        if(pFieldDesc != NULL)
        {
            const FieldType &oFieldType = pFieldDesc->getFieldType();

            PINFO << "FieldTypeId invalid, trying to fix. " << std::endl;
            PINFO << oFieldType.getContentType().getCName()
                  << " comparing with "
                  << FieldTraits<FieldContainerPtr>::getType().getCName()
                  << std::endl;


            if(oFieldType.getContentType().isDerivedFrom(
                   FieldTraits<FieldContainerPtr>::getType()) == true)
            {
                PINFO << "FieldContainerPtr or derived class, "
                      << "parsing as Node"
                      << std::endl;

                if(oFieldType.getCardinality() == FieldType::SINGLE_FIELD)
                {
                    returnValue = ScanParseSkel::OSGsfNode;
                }
                else
                {
                    returnValue = ScanParseSkel::OSGmfNode;
                }
            }
        }
    }

    return returnValue;
}

void OSGLoader::beginField(const Char8 *szFieldname,
                           const UInt32 )
{
    PINFO << "BeginField "
          << szFieldname
          << " "
          << _pCurrentField
          << std::endl;

    if(szFieldname == NULL)
        return;

    _pCurrentField.reset();

    if(_pCurrentFC != NullFC)
    {
        _pCurrentField     = _pCurrentFC->editField(szFieldname);

        _pCurrentFieldDesc =
            _pCurrentFC->getType().getFieldDesc(szFieldname);

        PINFO << "BF : "
              <<  szFieldname       << " "
              << _pCurrentField     << " "
              << _pCurrentFieldDesc << std::endl;

        if(_pCurrentFieldDesc != NULL)
        {
            _bvChanged |= _pCurrentFieldDesc->getFieldMask();
        }
    }

    _fStack.push (_pCurrentField);
    _fdStack.push(_pCurrentFieldDesc);
}

void OSGLoader::endField(void)
{
    PINFO << "End Field" << std::endl;

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
}

FieldContainerPtr OSGLoader::getReference(const Char8 *szName)
{
    // Find a previously DEF'ed FC by its name and return Ptr to it

    NamedFCMap::iterator entry = _defMap.find(std::string(szName));

    if(entry == _defMap.end())
        return NullFC;

    return entry->second; // return the stored FCPtr
}
