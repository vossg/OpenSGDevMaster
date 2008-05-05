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
EditMFieldHandle<FieldContainerPtrMFieldBase>::EditMFieldHandle(
    const EditMFieldHandle &source) :
    
     Inherited (source            ),
    _fAddMethod(source._fAddMethod)
{
}

inline
EditMFieldHandle<FieldContainerPtrMFieldBase>::EditMFieldHandle(      
          FieldContainerPtrMFieldBase *pField, 
    const FieldDescriptionBase        *pDescription) :

     Inherited (pField, 
                pDescription),
    _fAddMethod(NULL        )
{
}

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

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::add(
    FieldContainer * const pNewElement)
{
    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pNewElement);
    }
}


inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::replace(
    UInt32           const uiIndex,
    FieldContainer * const pNewElement)
{
    OSG_ASSERT(false);
}

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
void EditMFieldHandle<FieldContainerPtrMFieldBase>::setAddMethod(
    AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

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

inline
void EditMFieldHandle<FieldContainerPtrMFieldBase>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

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

/*---------------------------------------------------------------------*/

inline
GetMFieldHandle<FieldContainerPtrMFieldBase>::GetMFieldHandle(
    const GetMFieldHandle &source) :

    Inherited(source)
{
}

inline
GetMFieldHandle<FieldContainerPtrMFieldBase>::GetMFieldHandle(
    const FieldContainerPtrMFieldBase *pField, 
    const FieldDescriptionBase        *pDescription) :

    Inherited(pField, pDescription)
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
    
    FieldContainerPtrMFieldBase const *pLhs = 
        static_cast<FieldContainerPtrMFieldBase const *>(        _pField);

    FieldContainerPtrMFieldBase const *pRhs = 
        static_cast<FieldContainerPtrMFieldBase const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
FieldContainerPtrMFieldBase const *
    GetMFieldHandle<FieldContainerPtrMFieldBase>::operator ->(void)
{
    return static_cast<FieldContainerPtrMFieldBase const *>(_pField);
}

inline
FieldContainerPtrMFieldBase const &
    GetMFieldHandle<FieldContainerPtrMFieldBase>::operator * (void)
{
    return *(static_cast<FieldContainerPtrMFieldBase const *>(_pField));
}

/*---------------------------------------------------------------------*/

template<class FieldT> inline
GetFCPtrMFieldHandle<FieldT>::GetFCPtrMFieldHandle(
    const GetFCPtrMFieldHandle &source) :

    Inherited(source)
{
}

template<class FieldT> inline
GetFCPtrMFieldHandle<FieldT>::GetFCPtrMFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

template<class FieldT> inline
const FieldType &GetFCPtrMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
void GetFCPtrMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void GetFCPtrMFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
FieldT const *GetFCPtrMFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const &GetFCPtrMFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT const *>(_pField));
}


/*---------------------------------------------------------------------*/

template<class FieldT> inline
EditFCPtrMFieldHandle<FieldT>::EditFCPtrMFieldHandle(
    const EditFCPtrMFieldHandle &source) :
    
     Inherited (source            ),
    _fAddMethod(source._fAddMethod)
{
}

template<class FieldT> inline
EditFCPtrMFieldHandle<FieldT>::EditFCPtrMFieldHandle( 
          FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

     Inherited (pField, 
                pDescription),
    _fAddMethod(NULL        )
{
}

template<class FieldT> inline
const FieldType &EditFCPtrMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::add(FieldContainer * const pNewElement)
{
    typename FieldT::const_value pVal = 
        dynamic_cast<typename FieldT::const_value>(pNewElement);

    if(pNewElement != NULL && pVal == NULL)
        return;

    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pVal);
    }
    else
    {
        FFATAL(("EditFCPtrMFieldHandle<FieldT>::add called but "
                "_fAddMethod not set!\n"));
    }
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::replace(
    UInt32           const uiIndex,
    FieldContainer * const pNewElement)
{
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::setAddMethod(AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::pushValueFromCString(const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source) const
{
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes,
        const TypePtrVector     &ignoreTypes,
        const TypeIdVector      &shareGroupIds,
        const TypeIdVector      &ignoreGroupIds) const
{
    OSG_ASSERT(false);
}


OSG_END_NAMESPACE
