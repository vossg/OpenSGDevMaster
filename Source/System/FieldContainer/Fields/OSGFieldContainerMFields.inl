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

inline
MField<FieldContainerPtr, 0>::MField(void) :
     Inherited   ( ),
    _values      ( )
#ifdef OSG_MT_CPTR_ASPECT
   ,_uiSharedWith(0)
#endif
{
}

inline
MField<FieldContainerPtr, 0>::MField(const MField &obj) :
     Inherited   (obj        ),
    _values      (obj._values)
#ifdef OSG_MT_CPTR_ASPECT
   ,_uiSharedWith(0          )
#endif
{
}

inline
MField<FieldContainerPtr, 0>::MField(const UInt32 size) :
     Inherited   ( ),
    _values      ( )
#ifdef OSG_MT_CPTR_ASPECT
    ,_uiSharedWith(0)
#endif
{
    _values.resize(size);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
MField<FieldContainerPtr, 0>::~MField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

/*! Return a reference to the value store 
 */

inline
MField<FieldContainerPtr, 0>::StorageType &
    MField<FieldContainerPtr, 0>::getValues(void)
{
    return _values;
}

/*! Return a const reference to the value store 
 */

inline
const MField<FieldContainerPtr, 0>::StorageType &
    MField<FieldContainerPtr, 0>::getValues(void) const
{
    return _values;
}


/*-------------------------------------------------------------------------*/
/*                                Set                                      */

inline
void MField<FieldContainerPtr, 0>::setValues(const StorageType &value)
{
    _values = value;
}

inline
void MField<FieldContainerPtr, 0>::setValues(
    const StorageTypeParent &value)
{
    // Hack probably move it to MFieldVector (GV)

    *(static_cast<StorageTypeParent *>(&_values)) = value;
}

inline
void MField<FieldContainerPtr, 0>::setValues(const Self &obj)
{
    _values = obj._values;
}


#if 0
inline
void MField<FieldContainerPtr, 0>::addValueFromCString(const Char8 *str)
{
    FieldContainerPtr tmpVal;

    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<FieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromCString(tmpVal, str);
    
    push_back(tmpVal);
}


inline
void MField<FieldContainerPtr, 0>::pushValuesToString(std::string  &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<FieldContainerPtr, 0> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToString(_values[i], str);

        if(i < (size()-1))
        {
            str.append(", ");
        }
    }

}

inline
void MField<FieldContainerPtr, 0>::pushValuesFromStream(std::istream &str)
{
    FieldContainerPtr tmpVal;

    typedef boost::mpl::if_<boost::mpl::bool_<
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<FieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromStream(tmpVal, str);
    
    push_back(tmpVal);
}

inline
void MField<FieldContainerPtr, 0>::pushValuesToStream(OutStream &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<FieldContainerPtr, 0> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToStream(_values[i], str);

        if(i < (size()-1))
        {
            str << ", ";
        }
    }

}

inline
void MField<FieldContainerPtr, 0>::pushSizeToStream(OutStream &str) const
{
    str << _values.size();
}
#endif

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */


inline
UInt32 MField<FieldContainerPtr, 0>::getBinSize(void) const
{
    return 
        sizeof(UInt32) + // num elements
        (_values.size() ? 
         MFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);
}

inline
void MField<FieldContainerPtr, 0>::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    if(n != 0)
    {
        MFieldTraits::copyToBin(   pMem, 
                                &(_values[0]),
                                  _values.size());
    }
}

inline
void MField<FieldContainerPtr, 0>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;

     pMem  .getValue(n);
    _values.clear ( );

#ifdef __hpux
    FieldTypeT tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    if(n != 0)
    {
        MFieldTraits::copyFromBin(   pMem, 
                                  &(_values[0]),
                                     n);
    }
}

/*-------------------------------------------------------------------------*/
/*                             STL Interface                               */

inline
MField<FieldContainerPtr, 0>::iterator 
    MField<FieldContainerPtr, 0>::begin(void)
{
    return _values.begin();
}

inline
MField<FieldContainerPtr, 0>::iterator MField<FieldContainerPtr, 0>::end(void)
{
    return _values.end();
}

inline
MField<FieldContainerPtr, 0>::reverse_iterator 
    MField<FieldContainerPtr, 0>::rbegin(void)
{
    return _values.rbegin();
}

inline
MField<FieldContainerPtr, 0>::reverse_iterator 
    MField<FieldContainerPtr, 0>::rend(void)
{
    return _values.rend();
}

inline
MField<FieldContainerPtr, 0>::const_iterator 
    MField<FieldContainerPtr, 0>::begin(void) const
{
    return _values.begin();
}

inline
MField<FieldContainerPtr, 0>::const_iterator 
    MField<FieldContainerPtr, 0>::end(void) const
{
    return _values.end();
}

inline
MField<FieldContainerPtr, 0>::const_reverse_iterator 
    MField<FieldContainerPtr, 0>::rbegin(void) const
{
    return _values.rbegin();
}

inline
MField<FieldContainerPtr, 0>::const_reverse_iterator 
    MField<FieldContainerPtr, 0>::rend(void) const
{
    return _values.rend();
}

inline
MField<FieldContainerPtr, 0>::reference 
    MField<FieldContainerPtr, 0>::front(void)
{
    return _values.front();
}

inline
MField<FieldContainerPtr, 0>::const_reference 
    MField<FieldContainerPtr, 0>::front(void) const
{
    return _values.front();
}

inline
MField<FieldContainerPtr, 0>::reference 
    MField<FieldContainerPtr, 0>::back(void)
{
    return _values.back();
}

inline
MField<FieldContainerPtr, 0>::const_reference 
    MField<FieldContainerPtr, 0>::back(void) const
{
    return _values.back();
}

inline
void MField<FieldContainerPtr, 0>::clear(void)
{
    _values.clear();
}

inline
MField<FieldContainerPtr, 0>::iterator MField<FieldContainerPtr, 0>::insert(
    iterator pos, ArgumentType value)
{
    return _values.insert(pos, value);
}

#ifdef __STL_MEMBER_TEMPLATES

template <class InputIterator> inline
void MField<FieldContainerPtr, 0>::insert(iterator      pos, 
                                          InputIterator first, 
                                          InputIterator last )
{
    _values.insert(pos, first, last);
}
#else
inline
void MField<FieldContainerPtr, 0>::insert(iterator      pos, 
                                          iterator      first,
                                          iterator      last )
{
    _values.insert(pos, first, last);
}
#endif /* __STL_MEMBER_TEMPLATES */

inline
MField<FieldContainerPtr, 0>::iterator 
    MField<FieldContainerPtr, 0>::erase(iterator pos)
{
    return _values.erase(pos);
}

inline
MField<FieldContainerPtr, 0>::iterator MField<FieldContainerPtr, 0>::find(
    ArgumentType value)
{
    return std::find(_values.begin(), _values.end(), value);
}

inline
MField<FieldContainerPtr, 0>::const_iterator 
    MField<FieldContainerPtr, 0>::find(ArgumentType value) const
{
    return std::find(_values.begin(), _values.end(), value);
}

inline
Int32 MField<FieldContainerPtr, 0>::findIndex(ArgumentType value) const
{
    const_iterator it = std::find(_values.begin(), _values.end(), value);

    if(it != _values.end())
    {
        return it - _values.begin();
    }
    else
    {
        return -1;
    }
}

inline
void MField<FieldContainerPtr, 0>::push_back(ArgumentType value)
{
    _values.push_back(value);
}

inline
void MField<FieldContainerPtr, 0>::resize(size_t newsize, StoredType t)
{
    _values.resize(newsize, t);
}

inline
void MField<FieldContainerPtr, 0>::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

inline
UInt32 MField<FieldContainerPtr, 0>::size(void) const
{
    return _values.size();
}

inline
UInt32 MField<FieldContainerPtr, 0>::capacity(void) const
{
    return _values.capacity();
}

inline
bool MField<FieldContainerPtr, 0>::empty(void) const
{
    return _values.empty();
}

inline
void MField<FieldContainerPtr, 0>::swap(MField &right)
{
    _values.swap(right._values);
}

#ifdef OSG_1_COMPAT
inline
void MField<FieldContainerPtr, 0>::addValue (ArgumentType value)
{
    _values.push_back(value);
    
}
#endif

/*-------------------------------------------------------------------------*/
/*                           Index Operator                                */

inline
MField<FieldContainerPtr, 0>::reference
    MField<FieldContainerPtr, 0>::operator [](UInt32 index)
{
    return _values[index];
}

inline
MField<FieldContainerPtr, 0>::const_reference
    MField<FieldContainerPtr, 0>::operator [](UInt32 index) const
{
    return _values[index];
}

inline
bool MField<FieldContainerPtr, 0>::operator ==(const MField &source) const
{
    return _values == source._values;
}

inline
void MField<FieldContainerPtr, 0>::operator =(const MField &source)
{
    if(this == &source)
       return;

    _values = source._values;
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void MField<FieldContainerPtr, 0>::syncWith(Self               &source, 
                                            ConstFieldMaskArg   syncMode,
                                            UInt32              uiSyncInfo,
                                            AspectOffsetStore  &oOffsets  )
{
    if(source.size() != 0)
    {
        _values.resize(source.size());

        Self::iterator sIt  = source._values.begin();
        Self::iterator sEnd = source._values.end  ();

        Self::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
            (*fIt) = convertToCurrentAspect(*sIt);

            ++sIt;
            ++fIt;
        }
    }
    else
    {
        _values.clear();
    }
}

inline
void MField<FieldContainerPtr, 0>::beginEdit(UInt32             uiAspect,
                                             AspectOffsetStore &oOffsets)
{
#if 0
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, oOffsets);

        _values.resolveShare();

        setValues(*pOther);
    }
#endif
}


inline
MField<FieldContainerPtr, 0>::Self *
    MField<FieldContainerPtr, 0>::resolveShare(UInt32             uiAspect, 
                                               AspectOffsetStore &oOffsets)
{
#if 0
    Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
    Self   *pOther    = NULL;

    UInt32  uiShared  = _uiSharedWith;
    UInt32  uiCheck   = 1;
    UInt32  uiOwn     = 1 << uiAspect;
         
    for(UInt32 i = 0; i < oOffsets.size(); ++i)
    {
        if(oOffsets[i] == -1)
        {
            uiCheck <<= 1;
            continue;
        }

        if(0x0000 != (uiShared & uiCheck))
        {
            pOther = 
                reinterpret_cast<Self *>(pOtherMem + oOffsets[i]);
            
            pOther->_uiSharedWith &= ~uiOwn;
            _uiSharedWith         &= ~uiCheck;
            
            uiShared &= ~uiCheck;
        }
        
        if(0x0000 == uiShared)
        {
            break;
        }
        
        uiCheck <<= 1;
    }    

    return pOther;
#endif

    return NULL;
}

inline
void MField<FieldContainerPtr, 0>::terminateShare(UInt32             uiAspect,
                                                  AspectOffsetStore &oOffsets)
{
#if 0
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, oOffsets);

        _values.resolveShare();
    }
#endif
}

inline
bool  MField<FieldContainerPtr, 0>::isShared(void)
{
#if 0
    return _uiSharedWith != 0x0000;
#else
    return false;
#endif
}
#endif


inline
void MField<FieldContainerPtr, 0>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags ) const
{
    for(UInt32 i = 0; i < uiIndent; ++i)
        fprintf(stderr, " ");

    fprintf(stderr, "Share with : %08x\n", _uiSharedWith);

    _values.dump(uiIndent, bvFlags);
}



/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
MField<ParentFieldContainerPtr, 0>::MField(void) :
     Inherited   ( ),
    _values      ( )
#ifdef OSG_MT_CPTR_ASPECT
   ,_uiSharedWith(0)
#endif
{
}

inline
MField<ParentFieldContainerPtr, 0>::MField(const MField &obj) :
     Inherited   (obj        ),
    _values      (obj._values)
#ifdef OSG_MT_CPTR_ASPECT
   ,_uiSharedWith(0          )
#endif
{
}

inline
MField<ParentFieldContainerPtr, 0>::MField(const UInt32 size) :
     Inherited   ( ),
    _values      ( )
#ifdef OSG_MT_CPTR_ASPECT
    ,_uiSharedWith(0)
#endif
{
    _values.resize(size);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
MField<ParentFieldContainerPtr, 0>::~MField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

/*! Return a reference to the value store 
 */

inline
MField<ParentFieldContainerPtr, 0>::StorageType &
    MField<ParentFieldContainerPtr, 0>::getValues(void)
{
    return _values;
}

/*! Return a const reference to the value store 
 */

inline
const MField<ParentFieldContainerPtr, 0>::StorageType &
    MField<ParentFieldContainerPtr, 0>::getValues(void) const
{
    return _values;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

inline
void MField<ParentFieldContainerPtr, 0>::setValues(const StorageType &value)
{
    _values = value;
}

inline
void MField<ParentFieldContainerPtr, 0>::setValues(
    const StorageTypeParent &value)
{
    // Hack probably move it to MFieldVector (GV)

    *(static_cast<StorageTypeParent *>(&_values)) = value;
}

inline
void MField<ParentFieldContainerPtr, 0>::setValues(const Self &obj)
{
    _values = obj._values;
}

#if 0
inline
void MField<ParentFieldContainerPtr, 0>::addValueFromCString(const Char8 *str)
{
    ParentFieldContainerPtr tmpVal;

    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromCString(tmpVal, str);
    
    push_back(tmpVal);
}


inline
void MField<ParentFieldContainerPtr, 0>::pushValuesToString(
    std::string  &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<ParentFieldContainerPtr, 0> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToString(_values[i], str);

        if(i < (size()-1))
        {
            str.append(", ");
        }
    }

}

inline
void MField<ParentFieldContainerPtr, 0>::pushValuesFromStream(
    std::istream &str)
{
    ParentFieldContainerPtr tmpVal;

    typedef boost::mpl::if_<boost::mpl::bool_<
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<ParentFieldContainerPtr, 0> >::type Converter;
    
    Converter::getFromStream(tmpVal, str);
    
    push_back(tmpVal);
}

inline
void MField<ParentFieldContainerPtr, 0>::pushValuesToStream(
    OutStream &str) const
{
    typedef boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<ParentFieldContainerPtr, 0> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToStream(_values[i], str);

        if(i < (size()-1))
        {
            str << ", ";
        }
    }

}

inline
void MField<ParentFieldContainerPtr, 0>::pushSizeToStream(OutStream &str) const
{
    str << _values.size();
}
#endif

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

inline
UInt32 MField<ParentFieldContainerPtr, 0>::getBinSize(void) const
{
    return 
        sizeof(UInt32) + // num elements
        (_values.size() ? 
         MFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);
}

inline
void MField<ParentFieldContainerPtr, 0>::copyToBin(
    BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    if(n != 0)
    {
        MFieldTraits::copyToBin(   pMem, 
                                &(_values[0]),
                                  _values.size());
    }
}

inline
void MField<ParentFieldContainerPtr, 0>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;

     pMem  .getValue(n);
    _values.clear ( );

#ifdef __hpux
    FieldTypeT tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    if(n != 0)
    {
        MFieldTraits::copyFromBin(   pMem, 
                                  &(_values[0]),
                                     n);
    }
}

/*-------------------------------------------------------------------------*/
/*                             STL Interface                               */

inline
MField<ParentFieldContainerPtr, 0>::iterator 
    MField<ParentFieldContainerPtr, 0>::begin(void)
{
    return _values.begin();
}

inline
MField<ParentFieldContainerPtr, 0>::iterator 
    MField<ParentFieldContainerPtr, 0>::end(void)
{
    return _values.end();
}

inline
MField<ParentFieldContainerPtr, 0>::reverse_iterator 
    MField<ParentFieldContainerPtr, 0>::rbegin(void)
{
    return _values.rbegin();
}

inline
MField<ParentFieldContainerPtr, 0>::reverse_iterator 
    MField<ParentFieldContainerPtr, 0>::rend(void)
{
    return _values.rend();
}

inline
MField<ParentFieldContainerPtr, 0>::const_iterator 
    MField<ParentFieldContainerPtr, 0>::begin(void) const
{
    return _values.begin();
}

inline
MField<ParentFieldContainerPtr, 0>::const_iterator 
    MField<ParentFieldContainerPtr, 0>::end(void) const
{
    return _values.end();
}

inline
MField<ParentFieldContainerPtr, 0>::const_reverse_iterator 
    MField<ParentFieldContainerPtr, 0>::rbegin(void) const
{
    return _values.rbegin();
}

inline
MField<ParentFieldContainerPtr, 0>::const_reverse_iterator 
    MField<ParentFieldContainerPtr, 0>::rend(void) const
{
    return _values.rend();
}

inline
MField<ParentFieldContainerPtr, 0>::reference 
    MField<ParentFieldContainerPtr, 0>::front(void)
{
    return _values.front();
}

inline
MField<ParentFieldContainerPtr, 0>::const_reference 
    MField<ParentFieldContainerPtr, 0>::front(void) const
{
    return _values.front();
}

inline
MField<ParentFieldContainerPtr, 0>::reference 
    MField<ParentFieldContainerPtr, 0>::back(void)
{
    return _values.back();
}

inline
MField<ParentFieldContainerPtr, 0>::const_reference 
    MField<ParentFieldContainerPtr, 0>::back(void) const
{
    return _values.back();
}

inline
void MField<ParentFieldContainerPtr, 0>::clear(void)
{
    _values.clear();
}

inline
MField<ParentFieldContainerPtr, 0>::iterator 
    MField<ParentFieldContainerPtr, 0>::insert(iterator     pos, 
                                               ArgumentType value)
{
    return _values.insert(pos, value);
}

#ifdef __STL_MEMBER_TEMPLATES

template <class InputIterator> inline
void MField<ParentFieldContainerPtr, 0>::insert(iterator      pos, 
                                                InputIterator first, 
                                                InputIterator last )
{
    _values.insert(pos, first, last);
}
#else
inline
void MField<ParentFieldContainerPtr, 0>::insert(iterator      pos, 
                                                iterator      first,
                                                iterator      last )
{
    _values.insert(pos, first, last);
}
#endif /* __STL_MEMBER_TEMPLATES */

inline
MField<ParentFieldContainerPtr, 0>::iterator 
    MField<ParentFieldContainerPtr, 0>::erase(iterator pos)
{
    return _values.erase(pos);
}

inline
MField<ParentFieldContainerPtr, 0>::iterator 
    MField<ParentFieldContainerPtr, 0>::find(ArgumentType value)
{
    return std::find(_values.begin(), _values.end(), value);
}

inline
MField<ParentFieldContainerPtr, 0>::const_iterator 
    MField<ParentFieldContainerPtr, 0>::find(ArgumentType value) const
{
    return std::find(_values.begin(), _values.end(), value);
}

inline
Int32 MField<ParentFieldContainerPtr, 0>::findIndex(ArgumentType value) const
{
    const_iterator it = std::find(_values.begin(), _values.end(), value);

    if(it != _values.end())
    {
        return it - _values.begin();
    }
    else
    {
        return -1;
    }
}

inline
void MField<ParentFieldContainerPtr, 0>::push_back(ArgumentType value)
{
    _values.push_back(value);
}

inline
void MField<ParentFieldContainerPtr, 0>::resize(size_t newsize, StoredType t)
{
    _values.resize(newsize, t);
}

inline
void MField<ParentFieldContainerPtr, 0>::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

inline
UInt32 MField<ParentFieldContainerPtr, 0>::size(void) const
{
    return _values.size();
}

inline
UInt32 MField<ParentFieldContainerPtr, 0>::capacity(void) const
{
    return _values.capacity();
}

inline
bool MField<ParentFieldContainerPtr, 0>::empty(void) const
{
    return _values.empty();
}

inline
void MField<ParentFieldContainerPtr, 0>::swap(MField &right)
{
    _values.swap(right._values);
}

#ifdef OSG_1_COMPAT
inline
void MField<ParentFieldContainerPtr, 0>::addValue (ArgumentType value)
{
    _values.push_back(value);
    
}
#endif

/*-------------------------------------------------------------------------*/
/*                           Index Operator                                */

inline
MField<ParentFieldContainerPtr, 0>::reference
    MField<ParentFieldContainerPtr, 0>::operator [](UInt32 index)
{
    return _values[index];
}

inline
MField<ParentFieldContainerPtr, 0>::const_reference
    MField<ParentFieldContainerPtr, 0>::operator [](UInt32 index) const
{
    return _values[index];
}

inline
bool MField<ParentFieldContainerPtr, 0>::operator ==(
    const MField &source) const
{
    return _values == source._values;
}

inline
void MField<ParentFieldContainerPtr, 0>::operator =(const MField &source)
{
    if(this == &source)
       return;

    _values = source._values;
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void MField<ParentFieldContainerPtr, 0>::syncWith(
    Self               &source, 
    ConstFieldMaskArg   syncMode,
    UInt32              uiSyncInfo,
    AspectOffsetStore  &oOffsets  )
{
    if(source.size() != 0)
    {
        _values.resize(source.size());

        Self::iterator sIt  = source._values.begin();
        Self::iterator sEnd = source._values.end  ();

        Self::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
            (*fIt) = convertToCurrentAspect(*sIt);

            ++sIt;
            ++fIt;
        }
    }
    else
    {
        _values.clear();
    }
}

inline
void MField<ParentFieldContainerPtr, 0>::beginEdit(UInt32             uiAspect,
                                                   AspectOffsetStore &oOffsets)
{
#if 0
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, oOffsets);

        _values.resolveShare();

        setValues(*pOther);
    }
#endif
}


inline
MField<ParentFieldContainerPtr, 0>::Self *
    MField<ParentFieldContainerPtr, 0>::resolveShare(
        UInt32             uiAspect, 
        AspectOffsetStore &oOffsets)
{
#if 0
    Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
    Self   *pOther    = NULL;

    UInt32  uiShared  = _uiSharedWith;
    UInt32  uiCheck   = 1;
    UInt32  uiOwn     = 1 << uiAspect;
         
    for(UInt32 i = 0; i < oOffsets.size(); ++i)
    {
        if(oOffsets[i] == -1)
        {
            uiCheck <<= 1;
            continue;
        }

        if(0x0000 != (uiShared & uiCheck))
        {
            pOther = 
                reinterpret_cast<Self *>(pOtherMem + oOffsets[i]);
            
            pOther->_uiSharedWith &= ~uiOwn;
            _uiSharedWith         &= ~uiCheck;
            
            uiShared &= ~uiCheck;
        }
        
        if(0x0000 == uiShared)
        {
            break;
        }
        
        uiCheck <<= 1;
    }    

    return pOther;
#endif
    return NULL;
}

inline
void MField<ParentFieldContainerPtr, 0>::terminateShare(
    UInt32             uiAspect,
    AspectOffsetStore &oOffsets)
{
#if 0
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, oOffsets);

        _values.resolveShare();
    }
#endif
}

inline
bool  MField<ParentFieldContainerPtr, 0>::isShared(void)
{
#if 0
    return _uiSharedWith != 0x0000;
#else
    return false;
#endif
}
#endif


inline
void MField<ParentFieldContainerPtr, 0>::dump(      UInt32    uiIndent, 
                                              const BitVector bvFlags ) const
{
    for(UInt32 i = 0; i < uiIndent; ++i)
        fprintf(stderr, " ");

    fprintf(stderr, "Share with : %08x\n", _uiSharedWith);

    _values.dump(uiIndent, bvFlags);
}




/*---------------------------------------------------------------------*/

inline
EditMFieldHandle<MFFieldContainerPtr>::EditMFieldHandle(
    const EditMFieldHandle &source) :
    
     Inherited (source            ),
    _fAddMethod(source._fAddMethod)
{
}

inline
EditMFieldHandle<MFFieldContainerPtr>::EditMFieldHandle(      
          MFFieldContainerPtr  *pField, 
    const FieldDescriptionBase *pDescription) :

     Inherited (pField, 
                pDescription),
    _fAddMethod(NULL        )
{
}

inline
const FieldType &EditMFieldHandle<MFFieldContainerPtr>::getType(void) const
{
    return MFFieldContainerPtr::getClassType();
}

inline
bool EditMFieldHandle<MFFieldContainerPtr>::isPointerField(void) const
{
    return true;
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::add(
    FieldContainerPtrConstArg pNewElement)
{
    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pNewElement);
    }
}


inline
void EditMFieldHandle<MFFieldContainerPtr>::replace(
    const UInt32                    uiIndex,
          FieldContainerPtrConstArg pNewElement)
{
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::setAddMethod(AddMethod fMethod)
{
    _fAddMethod = fMethod;
}

inline
bool EditMFieldHandle<MFFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<EditMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    MFFieldContainerPtr *pLhs = 
        static_cast<MFFieldContainerPtr *>(        _pField);

    MFFieldContainerPtr *pRhs = 
        static_cast<MFFieldContainerPtr *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::copyValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFFieldContainerPtr>::shareValues(
    GetFieldHandlePtr source)
{
    OSG_ASSERT(false);
}


inline
void EditMFieldHandle<MFFieldContainerPtr>::cloneValues(
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
GetMFieldHandle<MFFieldContainerPtr>::GetMFieldHandle(
    const GetMFieldHandle &source) :

    Inherited(source)
{
}

inline
GetMFieldHandle<MFFieldContainerPtr>::GetMFieldHandle(
    const MFFieldContainerPtr  *pField, 
    const FieldDescriptionBase *pDescription) :

    Inherited(pField, pDescription)
{
}

inline
const FieldType &GetMFieldHandle<MFFieldContainerPtr>::getType(void) const
{
    return MFFieldContainerPtr::getClassType();
}


inline
bool GetMFieldHandle<MFFieldContainerPtr>::isPointerField(void) const
{
    return true;
}


inline
void GetMFieldHandle<MFFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetMFieldHandle<MFFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetMFieldHandle<MFFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<GetMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    MFFieldContainerPtr const *pLhs = 
        static_cast<MFFieldContainerPtr const *>(        _pField);

    MFFieldContainerPtr const *pRhs = 
        static_cast<MFFieldContainerPtr const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
MFFieldContainerPtr const *
    GetMFieldHandle<MFFieldContainerPtr>::operator ->(void)
{
    return static_cast<MFFieldContainerPtr const *>(_pField);
}

inline
MFFieldContainerPtr const &
    GetMFieldHandle<MFFieldContainerPtr>::operator * (void)
{
    return *(static_cast<MFFieldContainerPtr const *>(_pField));
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
void EditFCPtrMFieldHandle<FieldT>::add(FieldContainerPtrConstArg pNewElement)
{
    typename FieldT::ArgumentType pVal = 
        dynamic_cast<typename FieldT::ArgumentType>(pNewElement);

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
    const    UInt32                    uiIndex,
             FieldContainerPtrConstArg pNewElement)
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
void EditFCPtrMFieldHandle<FieldT>::copyValues(GetFieldHandlePtr  source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

template<class FieldT> inline
void EditFCPtrMFieldHandle<FieldT>::shareValues(GetFieldHandlePtr source)
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


/*---------------------------------------------------------------------*/


inline
EditMFieldHandle<MFParentFieldContainerPtr>::EditMFieldHandle(
    const EditMFieldHandle &source) :

    Inherited(source)
{
}

inline
EditMFieldHandle<MFParentFieldContainerPtr>::EditMFieldHandle(      
          MFParentFieldContainerPtr *pField, 
    const FieldDescriptionBase      *pDescription) :

    Inherited(pField, pDescription)
{
}

inline
const FieldType &EditMFieldHandle<MFParentFieldContainerPtr>::getType(
    void) const
{
    return MFParentFieldContainerPtr::getClassType();
}

inline
bool EditMFieldHandle<MFParentFieldContainerPtr>::isPointerField(void) const
{
    return true;
}

inline
void EditMFieldHandle<MFParentFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFParentFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool EditMFieldHandle<MFParentFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<EditMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    MFParentFieldContainerPtr *pLhs = 
        static_cast<MFParentFieldContainerPtr *>(        _pField);

    MFParentFieldContainerPtr *pRhs = 
        static_cast<MFParentFieldContainerPtr *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
void EditMFieldHandle<MFParentFieldContainerPtr>::pushValueFromCString(
    const Char8 *str)
{
    FWARNING(("illegal pushValueFromCString called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFParentFieldContainerPtr>::copyValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void EditMFieldHandle<MFParentFieldContainerPtr>::shareValues(
    GetFieldHandlePtr source)
{
    FWARNING(("illegal copyValues called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}


inline
void EditMFieldHandle<MFParentFieldContainerPtr>::cloneValues(
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
GetMFieldHandle<MFParentFieldContainerPtr>::GetMFieldHandle(
    const GetMFieldHandle &source) :

    Inherited(source)
{
}

inline
GetMFieldHandle<MFParentFieldContainerPtr>::GetMFieldHandle(
    const MFParentFieldContainerPtr *pField, 
    const FieldDescriptionBase      *pDescription) :

    Inherited(pField, pDescription)
{
}

inline
const FieldType &
    GetMFieldHandle<MFParentFieldContainerPtr>::getType(void) const
{
    return MFFieldContainerPtr::getClassType();
}


inline
bool GetMFieldHandle<MFParentFieldContainerPtr>::isPointerField(void) const
{
    return true;
}

inline
void GetMFieldHandle<MFParentFieldContainerPtr>::pushValueToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushValueToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
void GetMFieldHandle<MFParentFieldContainerPtr>::pushSizeToStream(
    OutStream &str) const
{
    FWARNING(("illegal pushSizeToStream called for %s\n", 
              this->getName().c_str()));
    OSG_ASSERT(false);
}

inline
bool GetMFieldHandle<MFParentFieldContainerPtr>::equal(Inherited::Ptr rhs)
{
    Ptr pOther = boost::dynamic_pointer_cast<GetMFieldHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    MFParentFieldContainerPtr const *pLhs = 
        static_cast<MFParentFieldContainerPtr const *>(        _pField);

    MFParentFieldContainerPtr const *pRhs = 
        static_cast<MFParentFieldContainerPtr const *>(pOther->_pField);

    return (*pLhs) == (*pRhs);
}

inline
MFParentFieldContainerPtr const *
    GetMFieldHandle<MFParentFieldContainerPtr>::operator ->(void)
{
    return static_cast<MFParentFieldContainerPtr const *>(_pField);
}

inline
MFParentFieldContainerPtr const &
    GetMFieldHandle<MFParentFieldContainerPtr>::operator * (void)
{
    return *(static_cast<MFParentFieldContainerPtr const *>(_pField));
}



OSG_END_NAMESPACE

