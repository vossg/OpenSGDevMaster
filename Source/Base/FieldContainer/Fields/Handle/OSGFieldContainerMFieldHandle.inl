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

/*---------------------------------------------------------------------------*/
/* GetMFieldHandle<FieldContainerPtrMFieldBase>                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

inline
GetMFieldHandle<FieldContainerPtrMFieldBase>::GetMFieldHandle(
    const GetMFieldHandle &source) :

    Inherited(source)
{
}

inline
GetMFieldHandle<FieldContainerPtrMFieldBase>::GetMFieldHandle(
    const FieldContainerPtrMFieldBase *pField, 
    const FieldDescriptionBase        *pDescription,
          FieldContainer              *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

inline
const FieldType &
    GetMFieldHandle<FieldContainerPtrMFieldBase>::getType(void) const
{
    return FieldContainerPtrMFieldBase::getClassType();
}


inline
bool GetMFieldHandle<FieldContainerPtrMFieldBase>::isPointerField(void) const
{
    return true;
}


inline
void GetMFieldHandle<FieldContainerPtrMFieldBase>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetMFieldHandle<FieldContainerPtrMFieldBase>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetMFieldHandle<FieldContainerPtrMFieldBase>::equal(
    Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }
    
    const FieldContainerPtrMFieldBase *pLhs = 
        static_cast<const FieldContainerPtrMFieldBase *>(        _pField);

    const FieldContainerPtrMFieldBase *pRhs = 
        static_cast<const FieldContainerPtrMFieldBase *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
const FieldContainerPtrMFieldBase *
    GetMFieldHandle<FieldContainerPtrMFieldBase>::getField(void)
{
    return static_cast<const FieldContainerPtrMFieldBase *>(_pField);
}

inline
const FieldContainerPtrMFieldBase *
    GetMFieldHandle<FieldContainerPtrMFieldBase>::operator ->(void)
{
    return static_cast<const FieldContainerPtrMFieldBase *>(_pField);
}

inline
const FieldContainerPtrMFieldBase &
    GetMFieldHandle<FieldContainerPtrMFieldBase>::operator * (void)
{
    return *(static_cast<const FieldContainerPtrMFieldBase *>(_pField));
}

/*---------------------------------------------------------------------------*/
/* EditMFieldHandle<FieldContainerPtrMFieldBase>                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

inline
EditMFieldHandle<FieldContainerPtrMFieldBase>::EditMFieldHandle(
    const EditMFieldHandle &source) :
    
     Inherited(source)
{
}

inline
EditMFieldHandle<FieldContainerPtrMFieldBase>::EditMFieldHandle(      
          FieldContainerPtrMFieldBase *pField, 
    const FieldDescriptionBase        *pDescription,
          FieldContainer              *pContainer  ) :

     Inherited(pField, 
               pDescription,
               pContainer  )
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

inline
const FieldType & 
    EditMFieldHandle<FieldContainerPtrMFieldBase>::getType(void) const
{
    return FieldContainerPtrMFieldBase::getClassType();
}

inline
bool EditMFieldHandle<FieldContainerPtrMFieldBase>::isPointerField(void) const
{
    return true;
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Comparison                                                                */

inline
bool EditMFieldHandle<FieldContainerPtrMFieldBase>::equal(
    Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldContainerPtrMFieldBase *pLhs = 
        static_cast<FieldContainerPtrMFieldBase *>(        _pField);

    FieldContainerPtrMFieldBase *pRhs = 
        static_cast<FieldContainerPtrMFieldBase *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

/*---------------------------------------------------------------------------*/
/* Copy/Share/Clone                                                          */

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::copyValues(
    GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::shareValues(
    GetFieldHandlePtr source) const
{
    OSG_ASSERT(false);
}


inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* GetFCPtrMFieldHandle<FieldT>                                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

template <class FieldT> inline
GetFCPtrMFieldHandle<FieldT>::GetFCPtrMFieldHandle(
    const GetFCPtrMFieldHandle &source) :

    Inherited(source)
{
}

template <class FieldT> inline
GetFCPtrMFieldHandle<FieldT>::GetFCPtrMFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

template <class FieldT> inline
const FieldType &GetFCPtrMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

template <class FieldT> inline
void GetFCPtrMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void GetFCPtrMFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Access                                                                    */

template <class FieldT> inline
FieldContainer *GetFCPtrMFieldHandle<FieldT>::get(UInt32 index) const
{
    return (*dcast_const())[index];
}

template <class FieldT> inline
UInt32 GetFCPtrMFieldHandle<FieldT>::size(void) const
{
    return dcast_const()->size();
}

template <class FieldT>
Int32 GetFCPtrMFieldHandle<FieldT>::find(FieldContainer *existingFC) const
{
    Int32                        retVal          = -1;
    typename FieldT::const_value typedExistingFC =
        dynamic_cast<typename FieldT::const_value>(existingFC);
    BitVector                    accessFlags     =
        _pDescription->getFlags() & Field::FAccessMask;

    if(0x0000 != (accessFlags & Field::FCustomAccess) ||
       0x0000 != (accessFlags & Field::FStdAccess   )   )
    {
        if(typedExistingFC != NULL || existingFC == NULL)
        {
            retVal = dcast_const()->findIndex(typedExistingFC);
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        retVal = dcast_const()->findIndex(typedExistingFC);
    }
    else
    {
        // this should never happen
        FFATAL(("GetFCPtrMFieldHandle<FieldT>::find: Field has unknown access.\n"));
    }
        
    return retVal;
}

template <class FieldT> inline
const FieldT *GetFCPtrMFieldHandle<FieldT>::getField(void)
{
    return dcast_const();
}

template <class FieldT> inline
const FieldT *GetFCPtrMFieldHandle<FieldT>::operator ->(void)
{
    return dcast_const();
}

template <class FieldT> inline
const FieldT &GetFCPtrMFieldHandle<FieldT>::operator * (void)
{
    return *dcast_const();
}

/*---------------------------------------------------------------------------*/
/* Private Helper                                                            */

template <class FieldT> inline
const typename GetFCPtrMFieldHandle<FieldT>::HandledField *
    GetFCPtrMFieldHandle<FieldT>::dcast_const(void) const
{
    return static_cast<const HandledField *>(_pField);
}

/*---------------------------------------------------------------------------*/
/* EditFCPtrMFieldHandle<FieldT>                                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

template <class FieldT> inline
EditFCPtrMFieldHandle<FieldT>::EditFCPtrMFieldHandle(
    const EditFCPtrMFieldHandle &source) :
    
     Inherited         (source                   ),
     _fAddMethod       (source._fAddMethod       ),
     _fRemoveMethod    (source._fRemoveMethod    ),
     _fRemoveObjMethod (source._fRemoveObjMethod ),
     _fInsertMethod    (source._fInsertMethod    ),
     _fReplaceMethod   (source._fReplaceMethod   ),
     _fReplaceObjMethod(source._fReplaceObjMethod),
     _fClearMethod     (source._fClearMethod     )
{
}

template <class FieldT> inline
EditFCPtrMFieldHandle<FieldT>::EditFCPtrMFieldHandle( 
          FieldT               *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

     Inherited         (pField, 
                        pDescription,
                        pContainer  ),
     _fAddMethod       (            ),
     _fRemoveMethod    (            ),
     _fRemoveObjMethod (            ),
     _fInsertMethod    (            ),
     _fReplaceMethod   (            ),
     _fReplaceObjMethod(            ),
     _fClearMethod     (            )
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

template <class FieldT> inline
const FieldType &EditFCPtrMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

/*! Returns whether the edited field supports addition of values.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsAdd(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fAddMethod.empty()                                 )   );
}

/*! Returns whether the edited field supports removal of values by index.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsRemove(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fRemoveMethod.empty()                                 )   );
}

/*! Returns whether the edited field supports removal of values by object.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsRemoveObject(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fRemoveObjMethod.empty()                              )   );
}

/*! Returns whether the edited field supports insertion of values.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsInsert(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return 
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fInsertMethod.empty()                                 )   );
}

/*! Returns whether the edited field supports replacement of values by index.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsReplace(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fReplaceMethod.empty()                                )   );
}

/*! Returns whether the edited field supports replacement of values by object.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsReplaceObject(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fReplaceObjMethod.empty()                                )   );
}

/*! Returns whether the edited field supports clearing of values.
 */
template <class FieldT> inline
bool EditFCPtrMFieldHandle<FieldT>::supportsClear(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fClearMethod.empty()                                  )   );
}

/*---------------------------------------------------------------------------*/
/* Access                                                                    */

/*! Returns the value stored at \a index in the edited field; no range checking
    is performed on \a index.
 */
template <class FieldT> inline
FieldContainer *EditFCPtrMFieldHandle<FieldT>::get(UInt32 index) const
{
    return (*dcast_const())[index];
}

/*! Returns the number of elements stored in the edited field.
 */
template <class FieldT> inline
UInt32 EditFCPtrMFieldHandle<FieldT>::size(void) const
{
    return dcast_const()->size();
}

/*! Returns the (first) index of \a existingFC in the edited field or -1 if it
    can not be found.
 */
template <class FieldT>
Int32 EditFCPtrMFieldHandle<FieldT>::find(FieldContainer *existingFC) const
{
    Int32                        retVal          = -1;
    typename FieldT::const_value typedExistingFC =
        dynamic_cast<typename FieldT::const_value>(existingFC);
    BitVector                    accessFlags     =
        _pDescription->getFlags() & Field::FAccessMask;

    if(0x0000 != (accessFlags & Field::FCustomAccess) ||
       0x0000 != (accessFlags & Field::FStdAccess   )   )
    {
        if(typedExistingFC != NULL || existingFC == NULL)
        {
            retVal = dcast_const()->findIndex(typedExistingFC);
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        retVal = dcast_const()->findIndex(typedExistingFC);
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::find: Field has unknown "
                "access.\n", typeid(FieldT).name()                   ));
    }
        
    return retVal;
}

/*! Adds \a newFC to the edited field and returns \c true iff successful.

    \note This operation is only available if \c supportsAdd returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::add(FieldContainer *newFC) const
{
    bool                         retVal      = false;
    typename FieldT::const_value typedNewFC  =
        dynamic_cast<typename FieldT::const_value>(newFC);
    BitVector                    accessFlags =
        _pDescription->getFlags() & Field::FAccessMask;

    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            if(!_fAddMethod.empty())
            {
                _fAddMethod(typedNewFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrMFieldHandle<%s>::add called, but "
                        "_fAddMethod is not set.\n", typeid(FieldT).name()));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if(typedNewFC != NULL)
        {
            dcast()->push_back(typedNewFC);
            retVal = true;
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            dcast()->push_back(typedNewFC);
            retVal = true;
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::add: Field has unknown "
                "access.\n", typeid(FieldT).name()                  ));
    }

    return retVal;
}

/*! Removes the value at \a index from the edited field and returns \c true
    iff successful; no range checking is performed on \a index.
    
    \note This operation is only available if \c supportsRemove returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::remove(UInt32 index) const
{
    bool      retVal      = false;
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;
    
    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(!_fRemoveMethod.empty())
        {
            _fRemoveMethod(index);
            retVal = true;
        }
        else
        {
            FFATAL(("EditFCPtrMFieldHandle<%s>::remove called, but "
                    "_fRemoveMethod is not set.\n", typeid(FieldT).name()));
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        dcast()->erase(index);
        retVal = true;
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        dcast()->erase(index);
        retVal = true;
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::remove: Field has unknown "
                "access.\n", typeid(FieldT).name()                     ));
    }

    return retVal;
}

/*! Removes the given \a existingFC from the edited field and returns \c true
    iff successful.
    
    \note This operation is only available if \c supportsRemoveObject
          returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::removeObject(
    FieldContainer *existingFC) const
{
    bool                         retVal          = false;
    typename FieldT::const_value typedExistingFC =
        dynamic_cast<typename FieldT::const_value>(existingFC);
    BitVector                    accessFlags     =
        _pDescription->getFlags() & Field::FAccessMask;

    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(typedExistingFC != NULL || existingFC == NULL)
        {
            if(!_fRemoveObjMethod.empty())
            {
                _fRemoveObjMethod(typedExistingFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrMFieldHandle<%s>::removeObject called, "
                        "but _fRemoveObjMethod is not set.\n", 
                        typeid(FieldT).name()                             ));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if(typedExistingFC != NULL)
        {
            Int32 iElemIdx = dcast()->findIndex(typedExistingFC);
        
            if(iElemIdx != -1)
            {
                dcast()->erase(iElemIdx);
                retVal = true;
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if(typedExistingFC != NULL || existingFC == NULL)
        {
            Int32 iElemIdx = dcast()->findIndex(typedExistingFC);
        
            if(iElemIdx != -1)
            {
                dcast()->erase(iElemIdx);
                retVal = true;
            }
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::removeObject: Field has unknown "
                "access.\n", typeid(FieldT).name()));
    }

    return retVal;
}

/*! Inserts the value \a newFC at \a index into the edited field and returns
    \c true iff successful; no range checking is performed on \a index.
    
    \note This operation is only available if \c supportsInsert returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::insert(
    UInt32 index, FieldContainer *newFC) const
{
    bool                         retVal      = false;
    typename FieldT::const_value typedNewFC  =
        dynamic_cast<typename FieldT::const_value>(newFC);
    BitVector                    accessFlags =
        _pDescription->getFlags() & Field::FAccessMask;
        
    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            if(!_fInsertMethod.empty())
            {
                _fInsertMethod(index, typedNewFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrMFieldHandle<%s>::insert called, but "
                        "_fInsertMethod is not set.\n", typeid(FieldT).name()));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if(typedNewFC != NULL)
        {
            dcast()->insert(dcast()->begin_nc() + index, typedNewFC);
            retVal = true;
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            dcast()->insert(dcast()->begin_nc() + index, typedNewFC);
            retVal = true;
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::insert: Field has unknown "
                " access.\n", typeid(FieldT).name()                    ));
    }

    return retVal;
}

/*! Replaces the value at \a index with \a newFC in the edited field and returns
    \c true iff successful; no range checking is performed on \a index.
    
    \note This operation is only available if \c supportsReplace returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::replace(
    UInt32 index, FieldContainer *newFC) const
{
    bool                         retVal      = false;
    typename FieldT::const_value typedNewFC  =
        dynamic_cast<typename FieldT::const_value>(newFC);
    BitVector                    accessFlags =
        _pDescription->getFlags() & Field::FAccessMask;
        
    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            if(!_fReplaceMethod.empty())
            {
                _fReplaceMethod(index, typedNewFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrMFieldHandle<%s>::replace called, but "
                        "_fReplaceMethod is not set.\n", typeid(FieldT).name()));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if(typedNewFC != NULL)
        {
            dcast()->replace(index, typedNewFC);
            retVal = true;
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            dcast()->replace(index, typedNewFC);
            retVal = true;
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::replace: Field has unknown "
                "access.\n", typeid(FieldT).name()                      ));
    }

    return retVal;
}

/*! Replaces the value \a existingFC with \a newFC in the edited field and
    returns \c true iff successful.
    
    \note This operation is only available if \c supportsReplaceObject
          returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::replaceObject(
    FieldContainer *existingFC, FieldContainer *newFC) const
{
    bool                         retVal          = false;
    typename FieldT::const_value typedExistingFC =
        dynamic_cast<typename FieldT::const_value>(existingFC);
    typename FieldT::const_value typedNewFC      =
        dynamic_cast<typename FieldT::const_value>(newFC);
    BitVector                    accessFlags     =
        _pDescription->getFlags() & Field::FAccessMask;
        
    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if((typedExistingFC != NULL || existingFC == NULL) &&
           (typedNewFC      != NULL || newFC      == NULL)   )
        {
            if(!_fReplaceObjMethod.empty())
            {
                _fReplaceObjMethod(typedExistingFC, typedNewFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrMFieldHandle<%s>::replaceObject called, "
                        "but _fReplaceMethod is not set.\n", 
                        typeid(FieldT).name()));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if((typedExistingFC != NULL) && (typedNewFC != NULL))
        {
            Int32 iElemIdx = dcast()->findIndex(typedExistingFC);
        
            if(iElemIdx != -1)
            {
                dcast()->replace(iElemIdx, typedNewFC);
                retVal = true;
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if((typedExistingFC != NULL || existingFC == NULL) &&
           (typedNewFC      != NULL || newFC      == NULL)   )
        {
            Int32 iElemIdx = dcast()->findIndex(typedExistingFC);
        
            if(iElemIdx != -1)
            {
                dcast()->replace(iElemIdx, typedNewFC);
                retVal = true;
            }
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::replaceObject: Field has unknown "
                "access.\n", typeid(FieldT).name()));
    }

    return retVal;
}

/*! Clears the edited field and returns \c true iff successful.

    \note This operation is only available if \c supportsClear returns \c true.
 */
template <class FieldT>
bool EditFCPtrMFieldHandle<FieldT>::clear(void) const
{
    bool      retVal      = false;
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;
    
    if(0x0000 != (accessFlags & Field::FCustomAccess))
    {
        if(!_fClearMethod.empty())
        {
            _fClearMethod();
            retVal = true;
        }
        else
        {
            FFATAL(("EditFCPtrMFieldHandle<%s>::clear called, but "
                    "_fClearMethod is not set.\n", typeid(FieldT).name()));
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        dcast()->clear();
        retVal = true;
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        dcast()->clear();
        retVal = true;
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrMFieldHandle<%s>::clear: Field has unknown "
                "access.\n", typeid(FieldT).name()                    ));
    }

    return retVal;
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushValueFromCString(const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Callback Setup                                                            */

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setAddMethod(AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setRemoveMethod(RemoveMethod fMethod)
{
    _fRemoveMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setRemoveObjMethod(RemoveObjMethod fMethod)
{
    _fRemoveObjMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setInsertMethod(InsertMethod fMethod)
{
    _fInsertMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setReplaceMethod(ReplaceMethod fMethod)
{
    _fReplaceMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setReplaceObjMethod(
    ReplaceObjMethod fMethod)
{
    _fReplaceObjMethod = fMethod;
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setClearMethod(ClearMethod fMethod)
{
    _fClearMethod = fMethod;
}

/*---------------------------------------------------------------------------*/
/* Copy/Share/Clone                                                          */

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source) const
{
    typename Self::GetMFHandlePtr pSrcBase = 
        boost::dynamic_pointer_cast<GetMFHandle>(source);

    FieldContainerUnrecPtr pDst = NULL;

    if(pSrcBase != NULL && pSrcBase->isValid() == true)
    {
        const FieldContainerPtrMFieldBase *pSrcField = pSrcBase->getField();
            
        for(UInt32 i = 0; i < pSrcField->size(); ++i)
        {
            this->add((*pSrcField)[i]);
        }
    }
    else
    {
        FWARNING(("shareValues illegal source for %s\n", 
                  this->getName().c_str()));
    }
}

template <class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes,
        const TypePtrVector     &ignoreTypes,
        const TypeIdVector      &shareGroupIds,
        const TypeIdVector      &ignoreGroupIds) const
{
    typename Self::GetMFHandlePtr pSrcBase = 
        boost::dynamic_pointer_cast<GetMFHandle>(pSrc);

    FieldContainerUnrecPtr pDst = NULL;

    if(pSrcBase != NULL && pSrcBase->isValid() == true)
    {
        const FieldContainerPtrMFieldBase *pSrcField = pSrcBase->getField();
            
        for(UInt32 i = 0; i < pSrcField->size(); ++i)
        {
            StoredPtrType pSrc = dynamic_cast<StoredPtrType>((*pSrcField)[i]);

            if(pSrc != NULL)
            {
                pDst = deepClone(pSrc,
                                 shareTypes,
                                 ignoreTypes,
                                 shareGroupIds,
                                 ignoreGroupIds);
            }
            else
            {
                pDst = NULL;
            }
            
            this->add(pDst);
        }
    }
    else
    {
        FWARNING(("cloneValues illegal source for %s\n", 
                  this->getName().c_str()));
    }
}

/*---------------------------------------------------------------------------*/
/* Private Helper                                                            */

template <class FieldT> inline
typename EditFCPtrMFieldHandle<FieldT>::HandledField *
    EditFCPtrMFieldHandle<FieldT>::dcast(void) const
{
    return static_cast<HandledField *>(_pField);
}

template <class FieldT> inline
const typename EditFCPtrMFieldHandle<FieldT>::HandledField *
    EditFCPtrMFieldHandle<FieldT>::dcast_const(void) const
{
    return static_cast<const HandledField *>(_pField);
}


OSG_END_NAMESPACE
