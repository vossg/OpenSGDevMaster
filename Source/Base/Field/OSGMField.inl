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

#if !defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) && \
    !defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGMFieldFuncs.ins"

#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueT, Int32 iNamespace> inline
MField<ValueT, iNamespace>::MField(void) :
     Inherited   ( ),
    _values      ( ),
    _uiSharedWith(0)
{
}

template <class ValueT, Int32 iNamespace> inline
MField<ValueT, iNamespace>::MField(const MField &obj) :
     Inherited   (obj        ),
    _values      (obj._values),
    _uiSharedWith(0          )
{
}

template <class ValueT, Int32 iNamespace> inline
MField<ValueT, iNamespace>::MField(const UInt32 size) :
     Inherited   ( ),
    _values      ( ),
    _uiSharedWith(0)
{
    _values.resize(size);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueT, Int32 iNamespace> inline
MField<ValueT, iNamespace>::~MField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

/*! Return a reference to the value store 
 */

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, iNamespace>::StorageType &
    MField<ValueT, iNamespace>::getValues(void)
{
    return _values;
}

/*! Return a const reference to the value store 
 */

template <class ValueT, Int32 iNamespace> inline
const typename MField<ValueT, iNamespace>::StorageType &
    MField<ValueT, iNamespace>::getValues(void) const
{
    return _values;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::setValues(const StorageType &value)
{
    _values = value;
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::setValues(
    const StorageTypeParent &value)
{
    // Hack probably move it to MFieldVector (GV)

    *(static_cast<StorageTypeParent *>(&_values)) = value;
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::setValues(const Self &obj)
{
    _values = obj._values;
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::addValueFromCString(const Char8 *str)
{
    ValueT tmpVal;

    typedef typename boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<ValueT,
                              iNamespace> >::type Converter;
    
    Converter::getFromCString(tmpVal, str);
    
    push_back(tmpVal);
}


template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::pushValuesToString(std::string  &str) const
{
    typedef typename boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStringConvertible)>, 
        MFieldTraits, 
        StringConversionError<ValueT,
                              iNamespace> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToString(_values[i], str);

        if(i < (size()-1))
        {
            str.append(", ");
        }
    }

}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::pushValuesFromStream(std::istream &str)
{
    ValueT tmpVal;

    typedef typename boost::mpl::if_<boost::mpl::bool_<
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::FromStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<ValueT,
                              iNamespace> >::type Converter;
    
    Converter::getFromStream(tmpVal, str);
    
    push_back(tmpVal);
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::pushValuesToStream(OutStream &str) const
{
    typedef typename boost::mpl::if_<boost::mpl::bool_< 
        static_cast<bool>(MFieldTraits    ::Convertible &
                          FieldTraitsBase ::ToStreamConvertible)>, 
        MFieldTraits, 
        StreamConversionError<ValueT,
                              iNamespace> >::type Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToStream(_values[i], str);

        if(i < (size()-1))
        {
            str << ", ";
        }
    }

}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::pushSizeToStream(OutStream &str) const
{
    str << _values.size();
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

template <class ValueTypeT, Int32 iNameSpace> inline
UInt32 MField<ValueTypeT, iNameSpace>::getBinSize(void) const
{
    return 
        sizeof(UInt32) + // num elements
        (_values.size() ? 
         MFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);
}

template <class ValueTypeT, Int32 iNameSpace> inline
void MField<ValueTypeT, 
            iNameSpace>::copyToBin(BinaryDataHandler &pMem) const
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

template <class ValueTypeT, Int32 iNameSpace> inline
void MField<ValueTypeT, iNameSpace>::copyFromBin(BinaryDataHandler &pMem)
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

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::iterator MField<ValueT, 
                                             iNamespace>::begin (void)
{
    return _values.begin();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::iterator MField<ValueT, 
                                             iNamespace>::end(void)
{
    return _values.end();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::reverse_iterator 
    MField<ValueT, 
           iNamespace>::rbegin(void)
{
    return _values.rbegin();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::reverse_iterator 
    MField<ValueT, 
           iNamespace>::rend(void)
{
    return _values.rend();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_iterator MField<ValueT, 
                                                   iNamespace>::begin(
                                                                    void) const
{
    return _values.begin();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_iterator MField<ValueT,
                                                   iNamespace>::end(void) const
{
    return _values.end();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT,
                iNamespace>::const_reverse_iterator 
    MField<ValueT, 
           iNamespace>::rbegin(void) const
{
    return _values.rbegin();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_reverse_iterator 
    MField<ValueT, 
           iNamespace>::rend(void) const
{
    return _values.rend();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::reference MField<ValueT, 
                                              iNamespace>::front(void)
{
    return _values.front();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_reference MField<ValueT, 
                                                    iNamespace>::front(
                                                                    void) const
{
    return _values.front();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::reference MField<ValueT, 
                                              iNamespace>::back(void)
{
    return _values.back();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_reference MField<ValueT, 
                                                    iNamespace>::back(
                                                                    void) const
{
    return _values.back();
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::clear(void)
{
    _values.clear();
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::iterator MField<ValueT, 
                                             iNamespace>::insert(
    iterator pos, ArgumentType value)
{
    return _values.insert(pos, value);
}

#ifdef __STL_MEMBER_TEMPLATES
template <class ValueT, Int32 iNamespace> 
template <class InputIterator> inline
void MField<ValueT, iNamespace>::insert(iterator      pos, 
                                        InputIterator first, 
                                        InputIterator last )
{
    _values.insert(pos, first, last);
}
#else
template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::insert(iterator      pos, 
                                        iterator      first,
                                        iterator      last )
{
    _values.insert(pos, first, last);
}
#endif /* __STL_MEMBER_TEMPLATES */

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::iterator MField<ValueT, 
                                             iNamespace>::erase(iterator pos)
{
    return _values.erase(pos);
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::iterator MField<ValueT, 
                                             iNamespace>::find(
    ArgumentType value)
{
    return std::find(_values.begin(), _values.end(), value);
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::const_iterator MField<ValueT, 
                                                   iNamespace>::find(
    ArgumentType value) const
{
    return std::find(_values.begin(), _values.end(), value);
}

template <class ValueT, Int32 iNamespace> inline
Int32 MField<ValueT, iNamespace>::findIndex(ArgumentType value) const
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

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::push_back(ArgumentType value)
{
    _values.push_back(value);
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::resize(size_t newsize, ValueT t)
{
    _values.resize(newsize, t);
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

template <class ValueT, Int32 iNamespace> inline
UInt32 MField<ValueT, iNamespace>::size(void) const
{
    return _values.size();
}

template <class ValueT, Int32 iNamespace> inline
UInt32 MField<ValueT, iNamespace>::capacity(void) const
{
    return _values.capacity();
}

template <class ValueT, Int32 iNamespace> inline
bool MField<ValueT, iNamespace>::empty(void) const
{
    return _values.empty();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::swap(MField &right)
{
    _values.swap(right._values);
}

/*-------------------------------------------------------------------------*/
/*                           Index Operator                                */

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, iNamespace>::reference
    MField<ValueT, iNamespace>::operator [](UInt32 index)
{
    return _values[index];
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, iNamespace>::const_reference
    MField<ValueT, iNamespace>::operator [](UInt32 index) const
{
    return _values[index];
}

template <class ValueT, Int32 iNamespace> inline
bool MField<ValueT, iNamespace>::operator ==(const MField &source) const
{
    return _values == source._values;
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::operator =(const MField &source)
{
    if(this == &source)
       return;

    _values = source._values;
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::syncWith(Self              &source,
                                          ConstFieldMaskArg  syncMode,
                                          UInt32             uiSyncInfo,
                                          UInt32             uiCopyOffset)
{
    if(syncMode != 0x0000)
    {
        setValues  (source);
    }
    else
    {
        UInt32 uiFromAspect  = (uiSyncInfo & 0xFF000000) >> 24;
        UInt32 uiToAspect    = (uiSyncInfo & 0x00FF0000) >> 16;

        bool   bTargetDelete = true;

        if(_uiSharedWith != 0x0000)
        {
            bTargetDelete = false;

            resolveShare(uiToAspect, uiCopyOffset);
        }

        Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
        Self   *pOther    = NULL;
        UInt32  uiShared  = source._uiSharedWith;
        UInt32  uiCheck   = 1;

        pOtherMem -= uiToAspect * uiCopyOffset;

        for(UInt32 i = 0; i < 32; ++i)
        {
            if(0x0000 != (uiShared & uiCheck))
            {
                pOther = 
                    reinterpret_cast<Self *>(
                        pOtherMem + (i * uiCopyOffset));

                pOther->_uiSharedWith |= (1 << uiToAspect);

                uiShared &= ~uiCheck;
            }

            if(0x0000 == uiShared)
            {
                break;
            }

            uiCheck <<= 1;
        }
        
        _uiSharedWith        |= source._uiSharedWith;
        _uiSharedWith        |= (1 << uiFromAspect);

        source._uiSharedWith |= (1 << uiToAspect  );

        _values.shareValues(source._values, bTargetDelete);
    }
}


template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::beginEdit(UInt32 uiAspect,
                                           UInt32 uiCopyOffset)
{
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, uiCopyOffset);

        _values.resolveShare();

        setValues(*pOther);
    }
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::Self *
    MField<ValueT, 
           iNamespace>::resolveShare(UInt32 uiAspect, 
                                     UInt32 uiCopyOffset)
{
    Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
    Self   *pOther    = NULL;
    UInt32  uiShared  = _uiSharedWith;
    UInt32  uiCheck   = 1;
    UInt32  uiOwn     = 1 << uiAspect;
    
    pOtherMem -= uiAspect * uiCopyOffset;
    
    for(UInt32 i = 0; i < 32; ++i)
    {
        if(0x0000 != (uiShared & uiCheck))
        {
            pOther = 
                reinterpret_cast<Self *>(
                    pOtherMem + (i * uiCopyOffset));
            
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
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::terminateShare(UInt32 uiAspect, 
                                                UInt32 uiCopyOffset)
{
    if(_uiSharedWith != 0x0000)
    {
        Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
        Self   *pOther    = NULL;
        UInt32  uiShared  = _uiSharedWith;
        UInt32  uiCheck   = 1 << (uiAspect + 1);
        UInt32  uiOwn     = 1 << uiAspect;

        for(UInt32 i = 1; i < 32; ++i)
        {
            if(0x0000 != (uiShared & uiCheck))
            {
                pOther = 
                    reinterpret_cast<Self *>(
                        pOtherMem + (i * uiCopyOffset));
                
                pOther->_uiSharedWith &= ~uiOwn;
                _uiSharedWith         &= ~uiCheck;

                pOther->_values.resolveShare();

                uiShared &= ~uiCheck;
            }
            
            if(0x0000 == uiShared)
            {
                break;
            }

            uiCheck <<= 1;
        }
    }
}

#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::syncWith(Self               &source, 
                                          ConstFieldMaskArg   syncMode,
                                          UInt32              uiSyncInfo,
                                          AspectOffsetStore  &oOffsets  )
{
    if(syncMode != 0x0000)
    {
        setValues  (source);
    }
    else
    {
        UInt32 uiFromAspect  = (uiSyncInfo & 0xFF000000) >> 24;
        UInt32 uiToAspect    = (uiSyncInfo & 0x00FF0000) >> 16;

        bool   bTargetDelete = true;

        if(_uiSharedWith != 0x0000)
        {
            bTargetDelete = false;

            resolveShare(uiToAspect, oOffsets);
        }

        Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
        Self   *pOther    = NULL;
        UInt32  uiShared  = source._uiSharedWith;
        UInt32  uiCheck   = 1;

//        pOtherMem -= uiToAspect * uiCopyOffset;

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
                    reinterpret_cast<Self *>(
                        pOtherMem + (oOffsets[i]));

                pOther->_uiSharedWith |= (1 << uiToAspect);

                uiShared &= ~uiCheck;
            }

            if(0x0000 == uiShared)
            {
                break;
            }

            uiCheck <<= 1;
        }
        
        _uiSharedWith        |= source._uiSharedWith;
        _uiSharedWith        |= (1 << uiFromAspect);

        source._uiSharedWith |= (1 << uiToAspect  );

        _values.shareValues(source._values, bTargetDelete);
    }
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::beginEdit(UInt32             uiAspect,
                                           AspectOffsetStore &oOffsets)
{
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, oOffsets);

        _values.resolveShare();

        setValues(*pOther);
    }
}


template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::Self *
    MField<ValueT, 
           iNamespace>::resolveShare(UInt32             uiAspect, 
                                     AspectOffsetStore &oOffsets)
{
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
}
#endif


template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::dump(      UInt32    uiIndent, 
                                      const BitVector bvFlags ) const
{
    for(UInt32 i = 0; i < uiIndent; ++i)
        fprintf(stderr, " ");

    fprintf(stderr, "Share with : %08x\n", _uiSharedWith);

    _values.dump(uiIndent, bvFlags);
}

OSG_END_NAMESPACE

#define OSGMFIELD_INLINE_CVSID "@(#)$Id$"

