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

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> 
template<class To> inline
To &FieldContainerPtrParentMField<ValueT,
                                  RefCountPolicy, 
                                  iNamespace    >::dcast(void)
{
    return reinterpret_cast<To &>(Self::_values); 
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> 
template<class To> inline
const To &FieldContainerPtrParentMField<ValueT, 
                                        RefCountPolicy, 
                                        iNamespace    >::dcast(void) const 
{
    return reinterpret_cast<const To &>(Self::_values); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentMField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::FieldContainerPtrParentMField(
                                  void) :
     Inherited (),
    _vParentPos()
{
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentMField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::FieldContainerPtrParentMField(
    const Self &obj) :

     Inherited (),
    _vParentPos()
{
    _values     = obj._values;
    _vParentPos = obj._vParentPos;
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
FieldContainerPtrParentMField<ValueT, 
                              RefCountPolicy, 
                              iNamespace    >::~FieldContainerPtrParentMField(
                                  void)
{
}

#if 0
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::StorageType &
    FieldContainerPtrMField<ValueT, RefCountPolicy, iNamespace>::getValues(void)
{
    return (this->template dcast<typename Self::StorageType>());
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
const typename FieldContainerPtrMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::StorageType &
    FieldContainerPtrMField<ValueT, 
                            RefCountPolicy, 
                            iNamespace    >::getValues(void) const
{
    return (this->template dcast<typename Self::StorageType>());
}
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
UInt32 FieldContainerPtrParentMField<ValueT, 
                                     RefCountPolicy, 
                                     iNamespace    >::getBinSize (void) const
{
    UInt32 returnValue =  
        sizeof(UInt32) + // num elements
        (_values.size() ? 
         PtrMFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);

    returnValue +=
        sizeof(UInt32) + // num elements
        (_vParentPos.size() ? 
         PosMFieldTraits::getBinSize(&(_vParentPos[0]), 
                                       _vParentPos.size()) : 0);

    return returnValue;
}
    
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::copyToBin(
                                       BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    if(n != 0)
    {
        PtrMFieldTraits::copyToBin(   pMem, 
                                   &(_values[0]),
                                     _values.size());
    }

    n = _vParentPos.size();

    pMem.putValue(n);

    if(n != 0)
    {
        PosMFieldTraits::copyToBin(   pMem, 
                                   &(_vParentPos[0]),
                                     _vParentPos.size());
    }
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::copyFromBin(
                                       BinaryDataHandler &pMem)
{
    UInt32 n;

     pMem  .getValue(n);

     OSG_ASSERT(_values.size() == 0);

#ifdef __hpux
    FieldTypeT tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    if(n != 0)
    {
        PtrMFieldTraits::copyFromBin(   pMem, 
                                     &(_values[0]),
                                        n);
    }

     pMem.getValue(n);
    
     OSG_ASSERT(_vParentPos.size() == 0);
    
    _vParentPos.resize(n);

    if(n != 0)
    {
        PosMFieldTraits::copyFromBin(   pMem, 
                                     &(_vParentPos[0]),
                                        n);        
    }
}

//reference getValue(void);
//const_reference getValue(void) const;

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::iterator
    FieldContainerPtrParentMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::begin_nc(void)
{
    return iterator(
        (this->template dcast<typename Self::StorageType>()).begin(),
        _vParentPos.begin());
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::iterator
    FieldContainerPtrParentMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::end_nc(void)
{
    return iterator(
        (this->template dcast<typename Self::StorageType>()).end(),
         _vParentPos.end());
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::const_iterator
    FieldContainerPtrParentMField<ValueT, RefCountPolicy, iNamespace>::begin(void) const
{
    return const_iterator(
        (this->template dcast<typename Self::StorageType>()).begin(),
        _vParentPos.begin());
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::const_iterator
    FieldContainerPtrParentMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::end(void) const
{
    return const_iterator(
        (this->template dcast<typename Self::StorageType>()).end(),
         _vParentPos.end());
}

#if 0
template<class ValueT, Int32 iNamespace> inline
typename FieldContainerPtrMField<ValueT, RefCountPolicy, iNamespace>::iterator 
    FieldContainerPtrMField<ValueT, 
                            RefCountPolicy,  
                            iNamespace    >::insert(iterator     pos, 
                                                    ArgumentType value)
{
    OSG::addRefX(value);

    return (this->template dcast<typename Self::StorageType>()).insert(pos, 
                                                                       value);
}

template<class ValueT, Int32 iNamespace> inline
typename FieldContainerParentPtrMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::iterator 
    FieldContainerParentPtrMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::erase(iterator pos)
{
    typename StorageType::iterator tmpIt(pos);
    
    OSG::subRefX(*tmpIt);

    return (this->template dcast<typename Self::StorageType>()).erase(pos);
}
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::erase(size_type pos)
{
    typename StorageType::iterator sIt = 
        (this->template dcast<typename Self::StorageType>()).begin();

    std::vector<UInt16> ::iterator pIt = _vParentPos.begin();

    sIt += pos;
    pIt += pos;

    (this->template dcast<typename Self::StorageType>()).erase(sIt);

    _vParentPos.erase(pIt);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::push_back(
    ArgumentType value,
    UInt16       parentFieldPos)
{
    _values.push_back(value);

    _vParentPos.push_back(parentFieldPos);
}

#if 0
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::resize(size_t     newsize, 
                                                     StoredType t)
{
    Inherited::resize(newsize, t);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrMField<ValueT, RefCountPolicy, iNamespace>::replace(UInt32       uiIdx, 
                                                          ArgumentType value)
{
    OSG::setRefdX((this->template dcast<typename Self::StorageType>())[uiIdx],
                  value);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::replace(iterator     pos, 
                                                      ArgumentType value)
{
    typename StorageType::iterator tmpIt(pos);

    OSG::setRefdX(*tmpIt, value);
}

#if 0
template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrMField<ValueT, iNamespace>::reference 
    FieldContainerPtrMField<ValueT, 
                            RefCountPolicy, 
                            iNamespace    >::operator [](UInt32 index)
{
    return (this->template dcast<typename Self::StorageType>())[index];
}
#endif
#endif

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
typename FieldContainerPtrParentMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::const_reference 
    FieldContainerPtrParentMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::operator [](
                                      UInt32 index) const
{
    return (this->template dcast<typename Self::StorageType>())[index];
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
bool FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::operator ==(
                                       const Self &source) const
{
    return (_values == source._values && _vParentPos == source._vParentPos);
}

template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::syncWith(
    Self               &source, 
    ConstFieldMaskArg   syncMode,
    UInt32              uiSyncInfo,
    AspectOffsetStore  &oOffsets    )
{
    if(source.size() != 0)
    {
        this->resize(source.size());

        Inherited::iterator sIt  = source._values.begin();
        Inherited::iterator sEnd = source._values.end  ();

        Inherited::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
            (*fIt) = convertToCurrentAspect(*sIt);

            ++sIt;
            ++fIt;
        }
    }
    else
    {
        this->clear();
    }
    
    _vParentPos = source._vParentPos;
}


template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::resize(size_t     newsize, 
                                                           StoredType t      )
{
    _values    .resize(newsize,      t);
    _vParentPos.resize(newsize, 0xFFFF);
}

 template<class ValueT, typename RefCountPolicy, Int32 iNamespace> inline
 void FieldContainerPtrParentMField<ValueT, 
                                   RefCountPolicy, 
                                   iNamespace    >::clear(void)
{
    _values    .clear();
    _vParentPos.clear();
}

OSG_END_NAMESPACE

