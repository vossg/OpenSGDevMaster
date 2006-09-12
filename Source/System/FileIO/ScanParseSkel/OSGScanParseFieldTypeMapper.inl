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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BaseT> inline
ScanParseFieldTypeMapper<BaseT>::ScanParseFieldTypeMapper(void) :
    Inherited(),
    _mIntExt (),
    _mExtInt ()

{
    Inherited::setMapTypeIds(true);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class BaseT> inline
ScanParseFieldTypeMapper<BaseT>::~ScanParseFieldTypeMapper(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class BaseT> inline
void ScanParseFieldTypeMapper<BaseT>::setIntExtMapping(
    UInt32            uiMappedType,
    BuildInFieldTypes eBuildInType)
{
    _mExtInt[uiMappedType] = eBuildInType;
}

template <class BaseT> inline
void ScanParseFieldTypeMapper<BaseT>::setExtIntMapping(
    BuildInFieldTypes eBuildInType,
    UInt32            uiMappedType)
{
    _mIntExt[eBuildInType] = uiMappedType;
}

/*-------------------------------------------------------------------------*/
/*                                Map                                      */

template <class BaseT> inline
Int32 ScanParseFieldTypeMapper<BaseT>::mapExtIntFieldType(
    const Char8 *,
    const Int32  iFieldTypeId)
{
    typename ExtIntMap::iterator gMIt = _mExtInt.find(iFieldTypeId);

    if(gMIt != _mExtInt.end())
    {
        return gMIt->second;
    }
    else
    {
        return -iFieldTypeId;
    }
}

template <class BaseT> inline
Int32 ScanParseFieldTypeMapper<BaseT>::mapIntExtFieldType(
    const Char8 *,
    const Int32  iFieldTypeId)
{
    typename IntExtMap::iterator gMIt = _mIntExt.find(
        (BuildInFieldTypes) iFieldTypeId);

    if(gMIt != _mIntExt.end())
    {
        return gMIt->second;
    }
    else
    {
        return -iFieldTypeId;
    }
}

OSG_END_NAMESPACE

#define OSGSCANPARSEFIELDTYPEMAPPER_INLINE_CVSID "@(#)$Id$"


