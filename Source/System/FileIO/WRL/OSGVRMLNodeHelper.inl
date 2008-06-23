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
    PINFO << "GroupHelper::init : " << szName << std::endl;
#endif

    _pNodeProto     = Node      ::create();
    _pNodeCoreProto = ContainerT::create();

    _pGenAttProto   = VRMLGenericAtt::create();
    _pGenAttProto->setInternal(true);
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
