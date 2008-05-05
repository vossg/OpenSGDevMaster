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
EditSFieldHandle<FieldContainerPtrSFieldBase>::EditSFieldHandle(
    const EditSFieldHandle &source) :

     Inherited (source            ),
    _pContainer(source._pContainer),
    _fSetMethod(source._fSetMethod)
{
}

inline
EditSFieldHandle<FieldContainerPtrSFieldBase>::EditSFieldHandle(      
          FieldContainerPtrSFieldBase *pField, 
    const FieldDescriptionBase        *pDescription) :

     Inherited (pField, 
                pDescription),
    _pContainer(NULL        ),
    _fSetMethod(NULL        )
{
}

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

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::setValue(
    FieldContainer * const rhs)
{
    // for whatever reason VS2003 does not like == NULL
    if(_fSetMethod)
    {
        _fSetMethod(rhs);
    }
}

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
void EditSFieldHandle<FieldContainerPtrSFieldBase>::setSetMethod(
    SetMethod fMethod)
{
    _fSetMethod = fMethod;
}

inline
void EditSFieldHandle<FieldContainerPtrSFieldBase>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

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




/*---------------------------------------------------------------------*/

inline
GetSFieldHandle<FieldContainerPtrSFieldBase>::GetSFieldHandle(
    const GetSFieldHandle &source) :

    Inherited(source)
{
}

inline
GetSFieldHandle<FieldContainerPtrSFieldBase>::GetSFieldHandle(
    const FieldContainerPtrSFieldBase *pField, 
    const FieldDescriptionBase        *pDescription) :

    Inherited(pField, pDescription)
{
}

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
FieldContainerPtrSFieldBase const *
    GetSFieldHandle<FieldContainerPtrSFieldBase>::operator ->(void)
{
    return static_cast<FieldContainerPtrSFieldBase const *>(_pField);
}

inline
FieldContainerPtrSFieldBase const &
    GetSFieldHandle<FieldContainerPtrSFieldBase>::operator * (void)
{
    return *(static_cast<FieldContainerPtrSFieldBase const *>(_pField));
}



/*---------------------------------------------------------------------*/

template<class FieldT> inline
GetFCPtrSFieldHandle<FieldT>::GetFCPtrSFieldHandle(
    const GetFCPtrSFieldHandle &source) :

    Inherited(source)
{
}

template<class FieldT> inline
GetFCPtrSFieldHandle<FieldT>::GetFCPtrSFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

template<class FieldT> inline
const FieldType &GetFCPtrSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
void GetFCPtrSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void GetFCPtrSFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
FieldT const *GetFCPtrSFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const &GetFCPtrSFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT const *>(_pField));
}

/*---------------------------------------------------------------------*/

template<class FieldT> inline
EditFCPtrSFieldHandle<FieldT>::EditFCPtrSFieldHandle(
    const EditFCPtrSFieldHandle &source) :
    
     Inherited (source            ),
    _fSetMethod(source._fSetMethod)
{
}

template<class FieldT> inline
EditFCPtrSFieldHandle<FieldT>::EditFCPtrSFieldHandle(
          FieldT                *pField, 
    const FieldDescriptionBase  *pDescription) :
    
     Inherited (pField, 
                pDescription),
    _fSetMethod(NULL)
{
}

template<class FieldT> inline
const FieldType &EditFCPtrSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::setValue(FieldContainer * const rhs)
{
    typename FieldT::const_value pVal = 
        dynamic_cast<typename FieldT::const_value>(rhs);

    if(rhs != NULL && pVal == NULL)
        return;

    // for whatever reason VS2003 does not like == NULL
    if(_fSetMethod)
    {
        _fSetMethod(pVal);
    }
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));

    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushSizeToStream(OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::setSetMethod(SetMethod fMethod)
{
    _fSetMethod = fMethod;
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::pushValueFromCString(const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source)
{
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrSFieldHandle<FieldT>::cloneValues(
              GetFieldHandlePtr  pSrc,
        const TypePtrVector     &shareTypes,
        const TypePtrVector     &ignoreTypes,
        const TypeIdVector      &shareGroupIds,
        const TypeIdVector      &ignoreGroupIds) const
{
    OSG_ASSERT(false);
}

OSG_END_NAMESPACE
