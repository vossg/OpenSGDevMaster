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
    _pContainerChanges(NULL                            ),
    _uiContainerId    (0                               )
{
}

inline
ReflexiveContainer::ReflexiveContainer(const ReflexiveContainer
                                                &OSG_CHECK_ARG(source)) :
    _bvChanged        (TypeTraits<BitVector>::BitsClear),
    _pContainerChanges(NULL                            ),
    _uiContainerId    (0                               )
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
void ReflexiveContainer::initMethod(InitPhase OSG_CHECK_ARG(ePhase))
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
void ReflexiveContainer::onDestroyAspect(UInt32 OSG_CHECK_ARG(uiContainerId),
                                         UInt32 OSG_CHECK_ARG(uiAspect))
{
}

inline
void ReflexiveContainer::execEndEdit(ConstFieldMaskArg whichField)
{
    _pContainerChanges->whichField |= whichField;
}

#if 0
inline
ContainerChangeEntry *ReflexiveContainer::getChangeEntry(void)
{
    return _pContainerChanges;
}
#endif

inline
void ReflexiveContainer::clearChangeEntry(ContainerChangeEntry *pRef)
{
    if(_pContainerChanges == pRef)
    {
        _pContainerChanges = NULL;
        _bvChanged         = 0x0000;
    }
}

inline
UInt32 ReflexiveContainer::getNumFields(void) const
{
    return getType().getNumFieldDescs();
}

/*! Returns a pointer to an EditFieldHandle for the Field with the given
    \a fieldId. If the \a fieldId is not valid an empty pointer is returned.
    
    \note This is part of the generic field interface.
 */
inline
EditFieldHandlePtr ReflexiveContainer::editField(UInt32 fieldId)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    return (desc != NULL) ? desc->editField(*this) : EditFieldHandlePtr();
}

/*! Returns a pointer to an EditFieldHandle for the Field with the given
    \a fieldName. If the \a fieldName is not valid an empty pointer is returned.
    
    \note This is part of the generic field interface.
 */
inline
EditFieldHandlePtr ReflexiveContainer::editField(const Char8 *fieldName)
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    return (desc != NULL) ? desc->editField(*this) : EditFieldHandlePtr();
}

/*! Returns a pointer to a GetFieldHandle for the Field with the given
    \a fieldId. If the \a fieldId is not valid an empty pointer is returned.
    
    \note This is part of the generic field interface.
 */
inline
GetFieldHandlePtr ReflexiveContainer::getField(UInt32 fieldId) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldId);

    return (desc != NULL) ? desc->getField(*this) : GetFieldHandlePtr();
}

/*! Returns a pointer to a GetFieldHandle for the Field with the given
    \a fieldName. If the \a fieldName is not valid an empty pointer is returned.
    
    \note This is part of the generic field interface.
 */
inline
GetFieldHandlePtr ReflexiveContainer::getField(const Char8 *fieldName) const
{
    const FieldDescriptionBase *desc = getType().getFieldDesc(fieldName);

    return (desc != NULL) ? desc->getField(*this) : GetFieldHandlePtr();
}

#if 0
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
#endif


inline
FieldDescriptionBase *ReflexiveContainer::getFieldDescription(
    UInt32 fieldId) const
{
    return getType().getFieldDesc(fieldId);
}

inline
FieldDescriptionBase *ReflexiveContainer::getFieldDescription(
    const Char8 *fieldName) const
{
    return getType().getFieldDesc(fieldName);
}

inline
void ReflexiveContainer::setId(UInt32 uiContainerId)
{
    _uiContainerId = uiContainerId;
}

inline
UInt32 ReflexiveContainer::getId(void) const
{
    return _uiContainerId;
}

OSG_END_NAMESPACE
