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
/*                            Constructors                                 */
#if 0
inline
SField<ParentFieldContainerPtr, 0>::SField(void) : 
     Inherited (),
    _fieldValue()
{
}

inline
SField<ParentFieldContainerPtr, 0>::SField(const SField &obj) :
     Inherited (obj            ),
    _fieldValue(obj._fieldValue)
{
}

inline
SField<ParentFieldContainerPtr, 0>::SField(ArgumentType value) :
     Inherited (     ),
    _fieldValue(value)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
SField<ParentFieldContainerPtr, 0>::~SField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

inline
SField<ParentFieldContainerPtr, 0>::reference 
    SField<ParentFieldContainerPtr, 0>::getValue(void)

{
    return _fieldValue;
}

inline
SField<ParentFieldContainerPtr, 0>::const_reference
    SField<ParentFieldContainerPtr, 0>::getValue(void) const
{
    return _fieldValue;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

inline
void SField<ParentFieldContainerPtr, 0>::setValue(ArgumentType value)
{
    _fieldValue = value;
}

inline
void SField<ParentFieldContainerPtr, 0>::setValue(const Self &obj)
{
    _fieldValue = obj._fieldValue;
}

#if 0
inline
void SField<ParentFieldContainerPtr, 0>::setValueFromCString(const Char8 *str)
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(SFieldTraits   ::Convertible &
                          FieldTraitsBase::FromStringConvertible)>, 
        SFieldTraits, 
        StringConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromCString(_fieldValue, str);
}

inline
void SField<ParentFieldContainerPtr, 
            0                     >::pushValueToString(std::string  &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(SFieldTraits   ::Convertible &
                          FieldTraitsBase::ToStringConvertible)>, 
        SFieldTraits, 
        StringConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::putToString(_fieldValue, str);
}

inline
void SField<ParentFieldContainerPtr, 0>::pushValueFromStream(std::istream &str)
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(SFieldTraits   ::Convertible &
                          FieldTraitsBase::FromStreamConvertible)>, 
        SFieldTraits, 
        StreamConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromStream(_fieldValue, str);
}

inline
void SField<ParentFieldContainerPtr, 
            0                      >::pushValueToStream(OutStream &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(SFieldTraits   ::Convertible &
                          FieldTraitsBase::ToStreamConvertible)>, 
        SFieldTraits, 
        StreamConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::putToStream(_fieldValue, str);
}

inline
void SField<ParentFieldContainerPtr, 0>::pushSizeToStream(OutStream &str) const
{
    str << 1;
}
#endif

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

inline
UInt32 SField<ParentFieldContainerPtr, 0>::getBinSize(void) const
{
    return SFieldTraits::getBinSize(_fieldValue);
}

inline
void SField<ParentFieldContainerPtr, 
            0                      >::copyToBin(BinaryDataHandler &pMem) const
{
    SFieldTraits::copyToBin( pMem, 
                            _fieldValue);
}

inline
void SField<ParentFieldContainerPtr, 0>::copyFromBin(BinaryDataHandler &pMem)
{
    SFieldTraits::copyFromBin( pMem, 
                              _fieldValue);
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

#ifdef OSG_MT_CPTR_ASPECT
inline
void SField<ParentFieldContainerPtr, 0>::syncWith(Self &source)
{
    ParentFieldContainerPtr pParent(
        convertToCurrentAspect(source.getValue().getCPtr          ()),
                               source.getValue().getParentFieldPos());

    setValue(pParent);
}
#endif

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

inline
bool SField<ParentFieldContainerPtr, 
            0                      >::operator ==(const SField &source) const
{
    return _fieldValue == source._fieldValue;
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

inline
void SField<ParentFieldContainerPtr, 0>::operator =(const SField &source)
{
    if(this != &source)
    {
        _fieldValue = source._fieldValue;
    }
}

#endif

/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/

inline
EditSFieldHandle<SFParentFieldContainerPtr>::EditSFieldHandle(
    const EditSFieldHandle &source) :

    Inherited(source)
{
}

inline
EditSFieldHandle<SFParentFieldContainerPtr>::EditSFieldHandle(      
          SFParentFieldContainerPtr *pField, 
    const FieldDescriptionBase      *pDescription) :

    Inherited(pField, pDescription)
{
}

inline
const FieldType &EditSFieldHandle<SFParentFieldContainerPtr>::getType(
    void) const
{
    return SFParentFieldContainerPtr::getClassType();
}

inline
bool EditSFieldHandle<SFParentFieldContainerPtr>::isPointerField(void) const
{
    return true;
}

inline
void EditSFieldHandle<SFParentFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFParentFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool EditSFieldHandle<SFParentFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<EditSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFParentFieldContainerPtr *pLhs = 
        static_cast<SFParentFieldContainerPtr *>(        _pField);

    SFParentFieldContainerPtr *pRhs = 
        static_cast<SFParentFieldContainerPtr *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditSFieldHandle<SFParentFieldContainerPtr>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFParentFieldContainerPtr>::copyValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditSFieldHandle<SFParentFieldContainerPtr>::shareValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}


inline
void EditSFieldHandle<SFParentFieldContainerPtr>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

/*---------------------------------------------------------------------*/


inline
GetSFieldHandle<SFParentFieldContainerPtr>::GetSFieldHandle(
    const GetSFieldHandle &source) :

    Inherited(source)
{
}

inline
GetSFieldHandle<SFParentFieldContainerPtr>::GetSFieldHandle(
    const SFParentFieldContainerPtr *pField, 
    const FieldDescriptionBase      *pDescription) :

    Inherited(pField, pDescription)
{
}

inline
const FieldType &
    GetSFieldHandle<SFParentFieldContainerPtr>::getType(void) const
{
    return SFFieldContainerPtr::getClassType();
}


inline
bool GetSFieldHandle<SFParentFieldContainerPtr>::isPointerField(void) const
{
    return true;
}

inline
void GetSFieldHandle<SFParentFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetSFieldHandle<SFParentFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetSFieldHandle<SFParentFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<GetSFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    SFParentFieldContainerPtr const *pLhs = 
        static_cast<SFParentFieldContainerPtr const *>(        _pField);

    SFParentFieldContainerPtr const *pRhs = 
        static_cast<SFParentFieldContainerPtr const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
SFParentFieldContainerPtr const *
    GetSFieldHandle<SFParentFieldContainerPtr>::operator ->(void)
{
    return static_cast<SFParentFieldContainerPtr const *>(_pField);
}

inline
SFParentFieldContainerPtr const &
    GetSFieldHandle<SFParentFieldContainerPtr>::operator * (void)
{
    return *(static_cast<SFParentFieldContainerPtr const *>(_pField));
}

OSG_END_NAMESPACE
