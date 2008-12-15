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
    _pDescription(source._pDescription)
{
}

inline
FieldHandle::FieldHandle(const FieldDescriptionBase *pDescription) :
    _pDescription(pDescription)
{
}

inline
FieldHandle::~FieldHandle(void)
{
}


inline
bool FieldHandle::isInternal(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->isInternal();
    }
    else
    {
        return false;
    }
}

inline
FieldType::Cardinality FieldHandle::getCardinality(void) const
{
    return getType().getCardinality();
}



inline
std::string FieldHandle::getName(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getName();
    }
    else
    {
        return std::string();
    }
}


/*---------------------------------------------------------------------*/

inline
GetFieldHandle::GetFieldHandle(const GetFieldHandle &source) :
     Inherited(source        ),
    _pField   (source._pField)
{
}

inline
GetFieldHandle::GetFieldHandle(const Field                *pField,
                               const FieldDescriptionBase *pDescription) :
     Inherited(pDescription),
    _pField   (pField      )
{
}

inline
GetFieldHandle::~GetFieldHandle(void)
{
}

inline
bool GetFieldHandle::isValid(void) const
{
    return _pField != NULL;
}

inline
const Field *GetFieldHandle::getField(void)
{
    return _pField;
}

inline
bool GetFieldHandle::operator ==(const EditFieldHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pField       == rhs._pField        );
}

inline
bool GetFieldHandle::operator ==(const GetFieldHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pField       == rhs._pField        );
}

/*---------------------------------------------------------------------*/

inline
EditFieldHandle::EditFieldHandle(const EditFieldHandle &source) :
     Inherited(source        ),
    _pField   (source._pField)
{
}

inline
EditFieldHandle::EditFieldHandle(      Field                *pField,
                                 const FieldDescriptionBase *pDescription) :
     Inherited(pDescription),
    _pField   (pField      )
{
}

inline
EditFieldHandle::~EditFieldHandle(void)
{
}

inline
bool EditFieldHandle::isValid(void) const
{
    return _pField != NULL;
}

inline
bool EditFieldHandle::operator ==(const EditFieldHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pField       == rhs._pField        );
}

inline
bool EditFieldHandle::operator ==(const GetFieldHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pField       == rhs._pField        );
}

/*---------------------------------------------------------------------*/

template<class FieldT> inline
EditSFieldHandle<FieldT>::EditSFieldHandle(const EditSFieldHandle &source) :
    Inherited(source)
{
}

template<class FieldT> inline
EditSFieldHandle<FieldT>::EditSFieldHandle(     
          FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :
    
    Inherited(pField, pDescription)
{
}


template<class FieldT> inline
EditSFieldHandle<FieldT>::~EditSFieldHandle(void)
{
}

template<class FieldT> inline
const FieldType &EditSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
bool EditSFieldHandle<FieldT>::isPointerField(void) const
{
    return false;
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    static_cast<FieldT *>(_pField)->pushValueToStream(str);
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::pushSizeToStream (OutStream &str) const
{
    static_cast<FieldT *>(_pField)->pushSizeToStream(str);
}

template<class FieldT> inline
bool EditSFieldHandle<FieldT>::equal(Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldT *pLhs = static_cast<FieldT *>(        _pField);
    FieldT *pRhs = static_cast<FieldT *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::pushValueFromCString(
    const Char8 *str)
{
    FieldT *pField = static_cast<FieldT *>(_pField);

    pField->setValueFromCString(str);
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source) const
{
    typename GetSFieldHandle<FieldT>::Ptr pSource = 
        boost::dynamic_pointer_cast<GetSFieldHandle<FieldT> >(source);

    if(pSource != NULL)
    {
        FieldT *pField = static_cast<FieldT *>(_pField);
        
        pField->setValue(**pSource);
    }
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::shareValues(GetFieldHandlePtr) const
{
    FWARNING(("illegal shareValues called for %s\n", this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditSFieldHandle<FieldT>::cloneValues(      GetFieldHandlePtr  ,
                                           const TypePtrVector     &,
                                           const TypePtrVector     &,
                                           const TypeIdVector      &,
                                           const TypeIdVector      &) const
{
    FWARNING(("illegal cloneValues called for %s\n", this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
FieldT *EditSFieldHandle<FieldT>::getField(void)
{
    return static_cast<FieldT *>(_pField);
}

template<class FieldT> inline
FieldT *EditSFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT *>(_pField);
}


template<class FieldT> inline
FieldT &EditSFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT *>(_pField));
}


/*---------------------------------------------------------------------*/

template<class FieldT> inline
EditMFieldHandle<FieldT>::EditMFieldHandle(const EditMFieldHandle &source):
    Inherited(source)
{
}

template<class FieldT> inline
EditMFieldHandle<FieldT>::EditMFieldHandle(     
          FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

template<class FieldT> inline
EditMFieldHandle<FieldT>::~EditMFieldHandle(void)
{
}

template<class FieldT> inline
const FieldType &EditMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
bool EditMFieldHandle<FieldT>::isPointerField(void) const
{
    return false;
}

template<class FieldT> inline
void EditMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    static_cast<FieldT *>(_pField)->pushValuesToStream(str);
}

template<class FieldT> inline
void EditMFieldHandle<FieldT>::pushSizeToStream (OutStream &str) const
{
    static_cast<FieldT *>(_pField)->pushSizeToStream(str);
}

template<class FieldT> inline
bool EditMFieldHandle<FieldT>::equal(Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<EditMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldT *pLhs = static_cast<FieldT *>(        _pField);
    FieldT *pRhs = static_cast<FieldT *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

template<class FieldT> inline
void EditMFieldHandle<FieldT>::pushValueFromCString(
    const Char8 *str)
{
    FieldT *pField = static_cast<FieldT *>(_pField);

    pField->addValueFromCString(str);
}

template<class FieldT> inline
void EditMFieldHandle<FieldT>::copyValues(GetFieldHandlePtr source) const
{
    typename GetMFieldHandle<FieldT>::Ptr pSource = 
        boost::dynamic_pointer_cast<GetMFieldHandle<FieldT> >(source);

    if(pSource != NULL)
    {
        FieldT *pField = static_cast<FieldT *>(_pField);
        
        pField->setValues(**pSource);
    }
}

template<class FieldT> inline
void EditMFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source) const
{
    FWARNING(("illegal shareValues called for %s\n", this->getName().c_str()));
    OSG_ASSERT(false);
}


template<class FieldT> inline
void EditMFieldHandle<FieldT>::cloneValues(      GetFieldHandlePtr  ,
                                           const TypePtrVector     &,
                                           const TypePtrVector     &,
                                           const TypeIdVector      &,
                                           const TypeIdVector      &) const
{
    FWARNING(("illegal cloneValues called for %s\n", this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
FieldT *EditMFieldHandle<FieldT>::getField(void)
{
    return static_cast<FieldT *>(_pField);
}

template<class FieldT> inline
FieldT *EditMFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT *>(_pField);
}

template<class FieldT> inline
FieldT &EditMFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT *>(_pField));
}


/*---------------------------------------------------------------------*/

template<class FieldT> inline
GetSFieldHandle<FieldT>::GetSFieldHandle(const GetSFieldHandle &source) :
    Inherited(source)
{
}

template<class FieldT> inline
GetSFieldHandle<FieldT>::GetSFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

template<class FieldT> inline
GetSFieldHandle<FieldT>::~GetSFieldHandle(void)
{
}

template<class FieldT> inline
const FieldType &GetSFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
bool GetSFieldHandle<FieldT>::isPointerField(void) const
{
    return false;
}

template<class FieldT> inline
void GetSFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    static_cast<FieldT const *>(_pField)->pushValueToStream(str);
}

template<class FieldT> inline
void GetSFieldHandle<FieldT>::pushSizeToStream (OutStream &str) const
{
    static_cast<FieldT const *>(_pField)->pushSizeToStream(str);
}

template<class FieldT> inline
bool GetSFieldHandle<FieldT>::equal(Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldT const *pLhs = static_cast<FieldT const *>(        _pField);
    FieldT const *pRhs = static_cast<FieldT const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

template<class FieldT> inline
FieldT const *GetSFieldHandle<FieldT>::getField(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const *GetSFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const &GetSFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT const *>(_pField));
}


/*---------------------------------------------------------------------*/

template<class FieldT> inline
GetMFieldHandle<FieldT>::GetMFieldHandle(const GetMFieldHandle &source) :
    Inherited(source)
{
}

template<class FieldT> inline
GetMFieldHandle<FieldT>::GetMFieldHandle(
    const FieldT               *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

template<class FieldT> inline
GetMFieldHandle<FieldT>::~GetMFieldHandle(void)
{
}

template<class FieldT> inline
const FieldType &GetMFieldHandle<FieldT>::getType(void) const
{
    return FieldT::getClassType();
}

template<class FieldT> inline
bool GetMFieldHandle<FieldT>::isPointerField(void) const
{
    return false;
}

template<class FieldT> inline
void GetMFieldHandle<FieldT>::pushValueToStream(OutStream &str) const
{
    static_cast<FieldT const *>(_pField)->pushValuesToStream(str);
}

template<class FieldT> inline
void GetMFieldHandle<FieldT>::pushSizeToStream (OutStream &str) const
{
    static_cast<FieldT const *>(_pField)->pushSizeToStream(str);
}

template<class FieldT> inline
bool GetMFieldHandle<FieldT>::equal(Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    FieldT const *pLhs = static_cast<FieldT const *>(        _pField);
    FieldT const *pRhs = static_cast<FieldT const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

template<class FieldT> inline
FieldT const *GetMFieldHandle<FieldT>::getField(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const *GetMFieldHandle<FieldT>::operator ->(void)
{
    return static_cast<FieldT const *>(_pField);
}

template<class FieldT> inline
FieldT const &GetMFieldHandle<FieldT>::operator * (void)
{
    return *(static_cast<FieldT const *>(_pField));
}


/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE
