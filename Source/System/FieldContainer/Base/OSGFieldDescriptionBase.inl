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

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
const Char8 *FieldDescriptionBase::getCName(void) const
{
    return _szName.str();
}

inline
const IDString &FieldDescriptionBase::getName(void) const
{
    return _szName;
}

inline
UInt32 FieldDescriptionBase::getTypeId(void) const
{
    return _fieldType.getId();
}

inline
BitVector FieldDescriptionBase::getFieldMask(void) const
{
    return _vFieldMask;
}

inline
void FieldDescriptionBase::setFieldMask(BitVector vFieldMask)
{
    _vFieldMask = vFieldMask;
}

inline
UInt32 FieldDescriptionBase::getFieldId(void) const
{
    return _uiFieldId;
}

inline
void FieldDescriptionBase::setFieldId(UInt32 uiFieldId)
{
    _uiFieldId = uiFieldId;
}

inline
const Char8 *FieldDescriptionBase::getDefaultValue(void) const
{
    return _defaultValue.str();
}

inline
const FieldType &FieldDescriptionBase::getFieldType(void) const
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/*                                Is                                       */

inline
bool FieldDescriptionBase::isInternal(void)  const
{
    return _bInternal;
}

inline
bool FieldDescriptionBase::isSField(void) const
{
    return (_fieldType.getCardinality() == FieldType::SINGLE_FIELD);
}

inline
bool FieldDescriptionBase::isMField(void) const
{
    return (_fieldType.getCardinality() == FieldType::MULTI_FIELD);
}

inline
UInt32 FieldDescriptionBase::getFlags(void) const
{
    return _uiFieldFlags;
}

inline
bool FieldDescriptionBase::isValid(void)  const
{
    return (this != NULL && _szName.getLength()) ? true : false;
}

inline
Field *FieldDescriptionBase::editField(ReflexiveContainer &oContainer) const
{
    Field *pField = NULL;

#ifdef FDESC_USE_BOOST
    if(_fEditMethod.empty() == false)
    {
        pField = _fEditMethod(&oContainer);
    }
    else if(_fIndexedEditMethod.empty() == false)
    {
        pField = _fIndexedEditMethod(&oContainer, _uiFieldId);
    }
#else
    if(_fEditMethod != 0)
    {
        pField = ( (&oContainer)->*_fEditMethod) ();
    }
    else if(_fIndexedEditMethod != 0)
    {
        pField = ( (&oContainer)->*_fIndexedEditMethod)(_uiFieldId);
    }
#endif

    return pField;
}

inline
const Field *FieldDescriptionBase::getField(
    const ReflexiveContainer &oContainer) const
{
    const Field *pField = NULL;
    
#ifdef FDESC_USE_BOOST
    if(_fGetMethod.empty() == false)
    {
        pField = _fGetMethod(&oContainer);
    }
    else if(_fIndexedGetMethod.empty() == false)
    {
        pField = _fIndexedGetMethod(&oContainer, _uiFieldId);
    }
#else
    if(_fGetMethod != 0)
    {
        pField = ( (&oContainer)->*_fGetMethod) ();
    }
    else if(_fIndexedGetMethod != 0)
    {
        pField = ( (&oContainer)->*_fIndexedGetMethod)(_uiFieldId);
    }
#endif

    return pField;
}

inline
bool FieldDescriptionBasePLT::operator()(
    const FieldDescriptionBase *pElemDesc1, 
    const FieldDescriptionBase *pElemDesc2) const
{
    return (pElemDesc1->getFieldId() < pElemDesc2->getFieldId());
}


OSG_END_NAMESPACE

#define OSGFIELDDESCRIPTIONBASE_INLINE_CVSID "@(#)$Id: $"

