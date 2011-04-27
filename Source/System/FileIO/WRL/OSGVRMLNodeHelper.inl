/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2008 by the OpenSG Forum                        *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, vossg@vossg.org, carsten_neumann@gmx.net      *
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

OSG_BEGIN_NAMESPACE

template<class ContainerT> inline
VRMLNodeHelper *VRMLGenericHelper<ContainerT>::create(void)
{
    return new VRMLGenericHelper<ContainerT>();
}
       

template<class ContainerT> inline
VRMLGenericHelper<ContainerT>::~VRMLGenericHelper(void)
{
}

template<class ContainerT> inline
void VRMLGenericHelper<ContainerT>::init(const Char8 *szName)
{
    Inherited::init(szName);

#ifdef OSG_DEBUG_VRML
    indentLog(getIndent(), PINFO);
    PINFO << "GenericHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node      ::create();
    _pNodeCoreProto = ContainerT::create();

    _pGenAttProto   = VRMLGenericAtt::createLocal(FCLocal::Cluster);
    _pGenAttProto->setInternal(true);
}

template<class ContainerT> inline
void VRMLGenericHelper<ContainerT>::mapFieldname(
    const std::string &szVRMLNodeName,
          std::string &szFieldName   )
{
    if(_mFieldNameMap.empty() == false)
    {
        FieldNameMapConstIt nIt = _mFieldNameMap.find(szFieldName);

        if(nIt != _mFieldNameMap.end())
        {
            szFieldName = nIt->second;
        }
    }
}

template<class ContainerT> inline
bool VRMLGenericHelper<ContainerT>::prototypeAddField(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    if(szFieldName == NULL)
        return false;

    std::string szDummyVRMLNodeName;
    std::string szTmpFieldName(szFieldName);

    this->mapFieldname(szDummyVRMLNodeName, szTmpFieldName);

    return Inherited::prototypeAddField(szFieldType, 
                                        uiFieldTypeId, 
                                        szTmpFieldName.c_str());
}

template<class ContainerT> inline
void VRMLGenericHelper<ContainerT>::getFieldAndDesc  (     
          FieldContainer       * pFC,
    const Char8                * szFieldname,
          FieldContainer       *&pFieldFC,
          EditFieldHandlePtr    &pField,
    const FieldDescriptionBase *&pDesc)
{
    if(szFieldname == NULL)
        return;

    std::string szDummyVRMLNodeName;
    std::string szTmpFieldName(szFieldname);

    this->mapFieldname(szDummyVRMLNodeName, szTmpFieldName);

    Inherited::getFieldAndDesc(pFC, 
                               szTmpFieldName.c_str(),
                               pFieldFC,
                               pField,
                               pDesc);
}


template<class ContainerT> inline
void VRMLGenericHelper<ContainerT>::dump(const Char8 *szNodeName)
{
}

template<class ContainerT> inline
VRMLGenericHelper<ContainerT>::VRMLGenericHelper(void) :
    Inherited()
{
}

OSG_END_NAMESPACE
