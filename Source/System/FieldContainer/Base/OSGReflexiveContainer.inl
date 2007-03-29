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
FieldHandle::FieldHandle(const FieldHandle &source) :
    _pField      (source._pField      ),
    _pDescription(source._pDescription)
{
}

inline
FieldHandle::FieldHandle(const Field                *pField,
                         const FieldDescriptionBase *pDescription) :
    _pField      (const_cast<Field *>(pField)),
    _pDescription(pDescription               )
{
}

inline
FieldHandle::~FieldHandle(void)
{
}


inline
bool FieldHandle::isInternal(void) const
{
    return _pDescription->isInternal();
}

inline
bool FieldHandle::isValid(void) const
{
    return (_pField != NULL && _pDescription != NULL);
}

inline
const FieldType &FieldHandle::getType(void) const
{
    return _pDescription->getFieldType();
}

inline
FieldType::Cardinality FieldHandle::getCardinality(void) const
{
    return getType().getCardinality();
}



inline
const Field *FieldHandle::getField(void) const
{
    return _pField;
}

inline
const IDString &FieldHandle::getName(void) const
{
    return _pDescription->getName();
}


inline
void FieldHandle::pushValueToStream(OutStream &str) const
{
    _pDescription->pushValueToStream(_pField, str);
}

inline
void FieldHandle::pushSizeToStream(OutStream &str) const
{
    _pDescription->pushSizeToStream(_pField, str);
}


inline
EditFieldHandle::EditFieldHandle(const EditFieldHandle &source) :
    Inherited(source)
{
}

inline
EditFieldHandle::EditFieldHandle(      Field                *pField,
                                 const FieldDescriptionBase *pDescription) :
    Inherited(pField, pDescription)
{
}

inline
EditFieldHandle::~EditFieldHandle(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
ReflexiveContainer::TypeObject &ReflexiveContainer::getClassType(void)
{
    return _type;
}

inline
UInt32 ReflexiveContainer::getClassTypeId(void)
{
    return _type.getId();
}

inline
UInt16 ReflexiveContainer::getClassGroupId(void)
{
    return _type.getGroupId();
}

inline
UInt32 ReflexiveContainer::getTypeId(void) const
{
    return getType().getId();
}

inline
UInt16 ReflexiveContainer::getGroupId(void) const
{
    return getType().getGroupId();
}

inline
const Char8 *ReflexiveContainer::getTypeName(void) const
{
    return getType().getCName();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
ReflexiveContainer::ReflexiveContainer(void) :
    _bvChanged        (TypeTraits<BitVector>::BitsClear),
    _pContainerChanges(NULL                            )
{
}

inline
ReflexiveContainer::ReflexiveContainer(const ReflexiveContainer &source) :
    _bvChanged        (TypeTraits<BitVector>::BitsClear),
    _pContainerChanges(NULL                            )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
ReflexiveContainer::~ReflexiveContainer(void)
{
#ifdef OSG_ENABLE_MEMORY_DEBUGGING
   _bvChanged         = 0xDEADBEEF;
   _pContainerChanges = (ContainerChangeEntry*)(0xDEADBEEF);
#endif
}


inline
void ReflexiveContainer::initMethod(InitPhase ePhase)
{
}

inline
void ReflexiveContainer::onCreate(const ReflexiveContainer *)
{
}

inline
void ReflexiveContainer::onDestroy(UInt32)
{
}

inline
void ReflexiveContainer::onDestroyAspect(UInt32 uiContainerId,
                                         UInt32 uiAspect     )
{
}

inline
void ReflexiveContainer::resolveLinks(void)
{
}

inline
void ReflexiveContainer::execEndEdit(ConstFieldMaskArg whichField)
{
    _pContainerChanges->whichField |= whichField;
}

inline
ContainerChangeEntry *ReflexiveContainer::getChangeEntry(void)
{
    return _pContainerChanges;
}

inline
void ReflexiveContainer::setChangeEntry(ContainerChangeEntry *pEntry)
{
    _pContainerChanges = pEntry;
}

inline
UInt32 ReflexiveContainer::getNumFields(void) const
{
    return getType().getNumFieldDescs();
}

inline
Field *ReflexiveContainer::editField(UInt32 fieldId)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    if(desc != NULL)
    {
        if(_bvChanged == TypeTraits<BitVector>::BitsClear)
        {
            registerChangedContainerV();
        }

        _bvChanged |= desc->getFieldMask();

        return desc->editField(*this);
    }

    return NULL;
}

inline
Field *ReflexiveContainer::editField(const Char8 *fieldName)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    if(desc != NULL)
    {
        if(_bvChanged == TypeTraits<BitVector>::BitsClear)
        {
            registerChangedContainerV();
        }

        _bvChanged |= desc->getFieldMask();

        return desc->editField(*this);
    }

    return NULL;
}

inline
const Field *ReflexiveContainer::getField(UInt32 fieldId) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    return (desc != NULL) ? desc->getField(*this) : NULL;
}

inline
const Field *ReflexiveContainer::getField(const Char8 *fieldName) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    return (desc != NULL) ? desc->getField(*this) : NULL;
}


inline
EditFieldHandle ReflexiveContainer::editHandledField(UInt32 fieldId)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    if(desc != NULL)
    {
        if(_bvChanged == TypeTraits<BitVector>::BitsClear)
        {
            registerChangedContainerV();
        }

        _bvChanged |= desc->getFieldMask();

        return EditFieldHandle(desc->editField(*this), desc);
    }

    return EditFieldHandle(NULL, NULL);
}

inline
EditFieldHandle ReflexiveContainer::editHandledField(const Char8 *fieldName)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    if(desc != NULL)
    {
        if(_bvChanged == TypeTraits<BitVector>::BitsClear)
        {
            registerChangedContainerV();
        }

        _bvChanged |= desc->getFieldMask();

        return EditFieldHandle(desc->editField(*this), desc);
    }

    return EditFieldHandle(NULL, NULL);
}

inline
FieldHandle ReflexiveContainer::getHandledField(UInt32 fieldId) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    return FieldHandle((desc != NULL) ? desc->getField(*this) : NULL,
                       desc);
}

inline
FieldHandle ReflexiveContainer::getHandledField(const Char8 *fieldName) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    return FieldHandle((desc != NULL) ? desc->getField(*this) : NULL,
                       desc);
}


inline
FieldDescriptionBase *ReflexiveContainer::getFieldDescription(UInt32 fieldId)
{
    return getType().getFieldDesc(fieldId);
}

inline
FieldDescriptionBase *ReflexiveContainer::getFieldDescription(
    const Char8 *fieldName)
{
    return getType().getFieldDesc(fieldName);
}

OSG_END_NAMESPACE

#define OSGREFLEXIVECONTAINER_INLINE_CVSID "@(#)$Id$"

