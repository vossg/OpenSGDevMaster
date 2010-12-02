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

template<class ValueT, Int32 iNamespace> inline
SField<ValueT, iNamespace>::SField(void) : 
     Inherited (),
    _fieldValue()
{
}

template <class ValueT, Int32 iNamespace> inline
SField<ValueT, iNamespace>::SField(const SField &obj) :
     Inherited (obj            ),
    _fieldValue(obj._fieldValue)
{
}

template <class ValueT, Int32 iNamespace> inline
SField<ValueT, iNamespace>::SField(ArgumentType value) :
     Inherited(     ),
    _fieldValue    (value)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template<class ValueT, Int32 iNamespace> inline
SField<ValueT, iNamespace>::~SField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

template <class ValueT, Int32 iNamespace> inline
typename SField<ValueT, iNamespace>::reference 
    SField<ValueT, iNamespace>::getValue(void)

{
    return _fieldValue;
}

template <class ValueT, Int32 iNamespace> inline
typename SField<ValueT, iNamespace>::const_reference
    SField<ValueT, iNamespace>::getValue(void) const
{
    return _fieldValue;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::setValue(ArgumentType value)
{
    _fieldValue = value;
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::setValue(const Self &obj)
{
    _fieldValue = obj._fieldValue;
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::setValueFromCString(const Char8 *str)
{
    typedef typename boost::mpl::if_c<
      (SFieldTraits   ::Convertible &
       FieldTraitsBase::FromStringConvertible), 
      SFieldTraits, 
      StringConversionError<ValueT, iNamespace> >::type Converter;
    
    Converter::getFromCString(_fieldValue, str);
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::pushValueToString  (std::string  &str) const
{
    typedef typename boost::mpl::if_c<
      (SFieldTraits   ::Convertible &
       FieldTraitsBase::ToStringConvertible), 
      SFieldTraits, 
      StringConversionError<ValueT, iNamespace> >::type Converter;
    
    Converter::putToString(_fieldValue, str);
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::pushValueFromStream(std::istream &str)
{
    typedef typename boost::mpl::if_c<
      (SFieldTraits   ::Convertible &
       FieldTraitsBase::FromStreamConvertible), 
      SFieldTraits, 
      StreamConversionError<ValueT, iNamespace> >::type Converter;
    
    Converter::getFromStream(_fieldValue, str);
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::pushValueToStream  (OutStream &str) const
{
    typedef typename boost::mpl::if_c<
      (SFieldTraits   ::Convertible &
       FieldTraitsBase::ToStreamConvertible), 
      SFieldTraits, 
      StreamConversionError<ValueT, iNamespace> >::type Converter;
    
    Converter::putToStream(_fieldValue, str);
}

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::pushSizeToStream  (OutStream &str) const
{
    str << 1;
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

template <class ValueTypeT, Int32 iNameSpace> inline
UInt32 SField<ValueTypeT, iNameSpace>::getBinSize(void) const
{
    return SFieldTraits::getBinSize(_fieldValue);
}

template <class ValueTypeT, Int32 iNameSpace> inline
void SField<ValueTypeT, iNameSpace>::copyToBin(BinaryDataHandler &pMem) const
{
    SFieldTraits::copyToBin( pMem, 
                            _fieldValue);
}

template <class ValueTypeT, Int32 iNameSpace> inline
void SField<ValueTypeT, iNameSpace>::copyFromBin(BinaryDataHandler &pMem)
{
    SFieldTraits::copyFromBin( pMem, 
                              _fieldValue);
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

#ifdef OSG_MT_CPTR_ASPECT
template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::syncWith(Self &source)
{
    setValue(source);
}
#endif

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

template <class ValueT, Int32 iNamespace> inline
bool SField<ValueT, iNamespace>::operator ==(const SField &source) const
{
    return _fieldValue == source._fieldValue;
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

template <class ValueT, Int32 iNamespace> inline
void SField<ValueT, iNamespace>::operator =(const SField &source)
{
    if(this != &source)
    {
        _fieldValue = source._fieldValue;
    }
}

OSG_END_NAMESPACE
