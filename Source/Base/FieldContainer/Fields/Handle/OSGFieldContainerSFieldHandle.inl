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
/* GetSFieldHandle<FieldContainerPtrSFieldBase>                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

inline
GetSFieldHandle<FieldContainerPtrSFieldBase>::GetSFieldHandle(
    const GetSFieldHandle &source) :

    Inherited(source)
{
}

inline
GetSFieldHandle<FieldContainerPtrSFieldBase>::GetSFieldHandle(
    const FieldContainerPtrSFieldBase *pField, 
    const FieldDescriptionBase        *pDescription,
          FieldContainer              *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

inline
const FieldType &
    GetSFieldHandle<FieldContainerPtrSFieldBase>::getType(void) const
{
    return FieldContainerPtrSFieldBase::getClassType();
}

inline
bool GetSFieldHandle<FieldContainerPtrSFieldBase>::isPointerField(void) const
{
    return true;
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

inline
void GetSFieldHandle<FieldContainerPtrSFieldBase>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetSFieldHandle<FieldContainerPtrSFieldBase>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Comparison                                                                */

inline
bool GetSFieldHandle<FieldContainerPtrSFieldBase>::equal(
    Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldContainerPtrSFieldBase const *pLhs = 
        static_cast<FieldContainerPtrSFieldBase const *>(        _pField);

    FieldContainerPtrSFieldBase const *pRhs = 
        static_cast<FieldContainerPtrSFieldBase const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
UInt32 GetSFieldHandle<FieldContainerPtrSFieldBase>::size(void) const
{
    return 1;
}

/*---------------------------------------------------------------------------*/
/* Access                                                                    */

inline
const FieldContainerPtrSFieldBase *
    GetSFieldHandle<FieldContainerPtrSFieldBase>::getField(void)
{
    return static_cast<const FieldContainerPtrSFieldBase *>(_pField);
}

inline
const FieldContainerPtrSFieldBase *
    GetSFieldHandle<FieldContainerPtrSFieldBase>::operator ->(void)
{
    return static_cast<const FieldContainerPtrSFieldBase *>(_pField);
}

inline
const FieldContainerPtrSFieldBase &
    GetSFieldHandle<FieldContainerPtrSFieldBase>::operator * (void)
{
    return *(static_cast<const FieldContainerPtrSFieldBase *>(_pField));
}

/*---------------------------------------------------------------------------*/
/* EditSFieldHandle<FieldContainerPtrSFieldBase>                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

inline
EditSFieldHandle<FieldContainerPtrSFieldBase>::EditSFieldHandle(
    const EditSFieldHandle &source) :

     Inherited(source)
{
}

inline
EditSFieldHandle<FieldContainerPtrSFieldBase>::EditSFieldHandle(      
          FieldContainerPtrSFieldBase *pField, 
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
    EditSFieldHandle<FieldContainerPtrSFieldBase>::getType(void) const
{
    return FieldContainerPtrSFieldBase::getClassType();
}

inline
bool EditSFieldHandle<FieldContainerPtrSFieldBase>::isPointerField(void) const
{
    return true;
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}


inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Comparison                                                                */

inline
bool EditSFieldHandle<FieldContainerPtrSFieldBase>::equal(
    Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldContainerPtrSFieldBase *pLhs = 
        static_cast<FieldContainerPtrSFieldBase *>(        _pField);

    FieldContainerPtrSFieldBase *pRhs = 
        static_cast<FieldContainerPtrSFieldBase *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
UInt32 EditSFieldHandle<FieldContainerPtrSFieldBase>::size(void) const
{
    return 1;
}

/*---------------------------------------------------------------------------*/
/* Copy/Share/Clone                                                          */

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::copyValues(
    GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::shareValues(
    GetFieldHandlePtr source) const
{
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* GetFCPtrSFieldHandle<FieldT>                                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

template <class FieldT> inline
GetFCPtrSFieldHandle<FieldT>::GetFCPtrSFieldHandle(
    const GetFCPtrSFieldHandle &source) :

    Inherited(source)
{
}

template <class FieldT> inline
GetFCPtrSFieldHandle<FieldT>::GetFCPtrSFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription,
          FieldContainer       *pContainer  ) :

    Inherited(pField, pDescription, pContainer)
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

template <class FieldT> inline
const FieldType &GetFCPtrSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

template <class FieldT> inline
void GetFCPtrSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void GetFCPtrSFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Access                                                                    */

template <class FieldT> inline
FieldContainer *GetFCPtrSFieldHandle<FieldT>::get(void) const
{
    return dcast_const()->getValue();
}

template <class FieldT> inline
const FieldT *GetFCPtrSFieldHandle<FieldT>::getField(void)
{
    return static_cast<const FieldT *>(_pField);
}

template <class FieldT> inline
const FieldT *GetFCPtrSFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<const FieldT *>(_pField);
}

template <class FieldT> inline
const FieldT &GetFCPtrSFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<const FieldT *>(_pField));
}

/*---------------------------------------------------------------------------*/
/* Private Helper                                                            */

template <class FieldT> inline
const typename GetFCPtrSFieldHandle<FieldT>::HandledField *
    GetFCPtrSFieldHandle<FieldT>::dcast_const(void) const
{
    return static_cast<const HandledField *>(_pField);
}

/*---------------------------------------------------------------------------*/
/* EditFCPtrSFieldHandle<FieldT>                                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Constructors                                                              */

template <class FieldT> inline
EditFCPtrSFieldHandle<FieldT>::EditFCPtrSFieldHandle(
    const EditFCPtrSFieldHandle &source) :
    
     Inherited (source            ),
    _fSetMethod(source._fSetMethod)
{
}

template <class FieldT> inline
EditFCPtrSFieldHandle<FieldT>::EditFCPtrSFieldHandle(
          FieldT                *pField, 
    const FieldDescriptionBase  *pDescription,
          FieldContainer        *pContainer  ) :
    
     Inherited (pField, 
                pDescription,
                pContainer  ),
    _fSetMethod(NULL        )
{
}

/*---------------------------------------------------------------------------*/
/* Field Type Query                                                          */

template <class FieldT> inline
const FieldType &EditFCPtrSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template <class FieldT> inline
bool EditFCPtrSFieldHandle<FieldT>::supportsSet(void) const
{
    BitVector accessFlags = _pDescription->getFlags() & Field::FAccessMask;

    return 
        ((0x0000 != (accessFlags & Field::FStdAccess      ) ||
          0x0000 != (accessFlags & Field::FNullCheckAccess)    ) ||
         (0x0000 != (accessFlags & Field::FCustomAccess   ) &&
          !_fSetMethod.empty()                                 )   );
}

/*---------------------------------------------------------------------------*/
/* Access                                                                    */

template <class FieldT> inline
FieldContainer *EditFCPtrSFieldHandle<FieldT>::get(void) const
{
    return dcast_const()->getValue();
}

template <class FieldT>
bool EditFCPtrSFieldHandle<FieldT>::set(FieldContainer *newFC) const
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
            if(!_fSetMethod.empty())
            {
                _fSetMethod(typedNewFC);
                retVal = true;
            }
            else
            {
                FFATAL(("EditFCPtrSFieldHandle<FieldT>::set called, but "
                        "_fSetMethod is not set.\n"));
            }
        }
    }
    else if(0x0000 != (accessFlags & Field::FNullCheckAccess))
    {
        if(typedNewFC != NULL)
        {
            dcast()->setValue(typedNewFC);
            retVal = true;
        }
    }
    else if(0x0000 != (accessFlags & Field::FStdAccess))
    {
        if(typedNewFC != NULL || newFC == NULL)
        {
            dcast()->setValue(typedNewFC);
            retVal = true;
        }
    }
    else
    {
        // this should never happen
        FFATAL(("EditFCPtrSFieldHandle<FieldT>::set: Field has unknown access.\n"));
    }

    return retVal;
}

/*---------------------------------------------------------------------------*/
/* Stream/String IO                                                          */

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));

    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushValueFromCString(const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------------*/
/* Callback Setup                                                            */

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::setSetMethod(SetMethod fMethod)
{
    _fSetMethod = fMethod;
}

/*---------------------------------------------------------------------------*/
/* Copy/Share/Clone                                                          */

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source) const
{
    typename Self::GetSFHandlePtr pSrcBase = 
        boost::dynamic_pointer_cast<GetSFHandle>(source);

    if(pSrcBase != NULL && pSrcBase->isValid() == true)
    {
        this->set(pSrcBase->get());
    }
    else
    {
        FWARNING(("shareValues illegal source for %s\n", 
                  this->getName().c_str()));
    }
}

template <class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes,
        const TypePtrVector     &ignoreTypes,
        const TypeIdVector      &shareGroupIds,
        const TypeIdVector      &ignoreGroupIds) const
{
    typename Self::GetSFHandlePtr pSrcBase = 
        boost::dynamic_pointer_cast<GetSFHandle>(pSrc);

    if(pSrcBase != NULL && pSrcBase->isValid() == true)
    {
        StoredPtrType pSrc = dynamic_cast<StoredPtrType>(pSrcBase->get());

        if(pSrc != NULL)
        {
            FieldContainerUnrecPtr pDst = deepClone(pSrc,
                                                    shareTypes,
                                                    ignoreTypes,
                                                    shareGroupIds,
                                                    ignoreGroupIds);

            this->set(pDst);
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
typename EditFCPtrSFieldHandle<FieldT>::HandledField *
    EditFCPtrSFieldHandle<FieldT>::dcast(void) const
{
    return static_cast<HandledField *>(_pField);
}

template <class FieldT> inline
const typename EditFCPtrSFieldHandle<FieldT>::HandledField *
    EditFCPtrSFieldHandle<FieldT>::dcast_const(void) const
{
    return static_cast<const HandledField *>(_pField);
}

OSG_END_NAMESPACE
