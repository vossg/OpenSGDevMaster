/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

inline
UInt16 ReflexiveContainerType::getGroupId(void) const
{
    return _uiGroupId;
}

inline
FieldDescriptionBase *ReflexiveContainerType::getFieldDesc(UInt32 uiFieldId)
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

inline
FieldDescriptionBase *ReflexiveContainerType::getFieldDesc(
    UInt32 uiFieldId) const
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

inline
FieldDescriptionBase *ReflexiveContainerType::getFieldDesc(
    const Char8 *szFieldName)
{
    DescMapIt descIt = _mDescMap.find(std::string(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
FieldDescriptionBase *ReflexiveContainerType::getFieldDesc(
    const Char8 *szFieldName) const
{
    DescMapConstIt descIt = _mDescMap.find(std::string(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 ReflexiveContainerType::getNumFieldDescs(void) const
{
    return _vDescVec.size();
}

inline
BitVector ReflexiveContainerType::getUnmarkedOnCreate(void) const
{
    return _bvUnmarkedOnCreate;
}

inline
void ReflexiveContainerType::setFieldsUnmarkedOnCreate(
    const BitVector bvFieldMasks)
{
    _bvUnmarkedOnCreate &= ~bvFieldMasks;
}

inline
void ReflexiveContainerType::clearFieldsUnmarkedOnCreate(
    const BitVector bvFieldMasks)
{
    _bvUnmarkedOnCreate |= bvFieldMasks;
}

OSG_END_NAMESPACE

