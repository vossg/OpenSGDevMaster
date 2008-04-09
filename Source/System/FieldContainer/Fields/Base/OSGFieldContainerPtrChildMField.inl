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

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > 
template<class To> inline
To &FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::dcast(void)
{
    return reinterpret_cast<To &>(Self::_values); 
}

template<class    ValueT, 
         typename RefCountPolicy, 
          Int32   iNamespace    > 
template<class To> inline
const To &FieldContainerPtrChildMField<ValueT, 
                                       RefCountPolicy, 
                                       iNamespace    >::dcast(void) const 
{
    return reinterpret_cast<const To &>(Self::_values); 
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

#if 0
template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
FieldContainerPtrChildMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::FieldContainerPtrChildMField(
                                 void) :
    Inherited()
{
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
FieldContainerPtrChildMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::FieldContainerPtrChildMField(
    const Self &obj) :

    Inherited()
{
    if(obj._values.size() > 0)
    {
        _values.resize(obj._values.size(), NULL);

        typename StorageType::const_iterator sIt  = obj._values.begin();
        typename StorageType::const_iterator sEnd = obj._values.end  ();

        typename StorageType::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
            RefCountPolicy::setRefd((*fIt), *sIt);

            ++sIt;
            ++fIt;
        }
    }
}


template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
FieldContainerPtrChildMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::FieldContainerPtrChildMField(
    const UInt32 size) : 

    Inherited(size)
{
}
#endif

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
FieldContainerPtrChildMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::FieldContainerPtrChildMField(
                                 ParentT pParent,
                                 UInt16  usParentFieldPos) :
     Inherited       (                ),
    _pParent         (pParent         ),
    _usParentFieldPos(usParentFieldPos)
{
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
FieldContainerPtrChildMField<ValueT, 
                             RefCountPolicy, 
                             iNamespace    >::~FieldContainerPtrChildMField(
                                 void)
{
    this->clear();
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::copyFromBin(
                                      BinaryDataHandler &pMem)
{
    UInt32 n;

    pMem.getValue(n);

    if(n != 0)
    {
        if(_values.size() == 0)
        {
            _values.resize(n, NULL);

            MFieldTraits::copyFromBin(   pMem, 
                                      &(_values[0]),
                                         n);
            
            typename Inherited::const_iterator sIt  = _values.begin();
            typename Inherited::const_iterator sEnd = _values.end  ();
            
            while(sIt != sEnd)
            {
                RefCountPolicy::addRef(*sIt);
                
                ++sIt;
            }
        }
        else
        {
            if(n > _values.size())
            {
                _values.resize(n, NullFC);
            }
            
            typename Inherited::      iterator sIt  = _values.begin();
            typename Inherited::const_iterator sEnd = _values.end  ();

            FieldContainerPtr tmpVal;

            for(UInt32 i = 0; i < n; ++i)
            {
                if(*sIt != NULL)
                {
                    Thread::getCurrentChangeList()->addDelayedSubRef
                        <RefCountPolicy>(*sIt);
                }

                MFieldTraits::copyFromBin(pMem, 
                                          tmpVal);
                
                RefCountPolicy::addRef(tmpVal);
                
                *sIt = tmpVal;

                ++sIt;
            }

            if(n < _values.size())
            {
                while(sIt != sEnd)
                {
                    if(*sIt != NULL)
                    {
                        Thread::getCurrentChangeList()->addDelayedSubRef<
                            RefCountPolicy>(*sIt);
                    }
                
                    ++sIt;
                };

                _values.resize(n);
            }
        }
    }
    else
    {
        this->clear();
    }
}


//reference getValue(void);
//const_reference getValue(void) const;

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::iterator
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::begin_nc(void)
{
    return typename Self::iterator(
        (this->template dcast<typename Self::StorageType>()).begin(),
        this);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::iterator
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::end_nc(void)
{
    return typename Self::iterator(
        (this->template dcast<typename Self::StorageType>()).end(),
        this);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::const_iterator
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::begin(void) const
{
    return (this->template dcast<typename Self::StorageType>()).begin();
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::const_iterator
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::end(void) const
{
    return (this->template dcast<typename Self::StorageType>()).end();
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::iterator 
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::insert(iterator     pos, 
                                                         ArgumentType value)
{
    RefCountPolicy::addRef(value);

    typename Self::iterator returnValue(
        (this->template dcast<typename Self::StorageType>()).insert(pos, 
                                                                    value),
        this);

    ParentHandler::updateParentLinking(value, _pParent, _usParentFieldPos);

    return returnValue;
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::clear(void)
{
    typename StorageType::iterator       fieldIt  = this->begin_nc();
    typename StorageType::const_iterator fieldEnd = this->end     ();

    while(fieldIt != fieldEnd)
    {
        ParentHandler::clearParentLinking(*fieldIt, 
                                          _pParent,
                                          _usParentFieldPos);

        RefCountPolicy::subRef(*fieldIt);

        ++fieldIt;
    }

    _values.clear();
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::iterator 
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::erase(iterator pos)
{
    typename StorageType::iterator tmpIt(pos);

    ParentHandler::clearParentLinking(*tmpIt, _pParent, _usParentFieldPos);
    
    RefCountPolicy::subRef(*tmpIt);

    return typename Self::iterator(
        (this->template dcast<typename Self::StorageType>()).erase(pos),
        this);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::iterator
     FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::erase(iterator     first,
                                                         iterator     last )
{
    typename StorageType::iterator tmpFirst(first);
    typename StorageType::iterator tmpLast (last );

    for(; first != last; ++first)
    {
        ParentHandler::clearParentLinking( first.deref(), 
                                          _pParent, 
                                          _usParentFieldPos);

        RefCountPolicy::subRef(first.deref());
    }
    
    return typename Self::iterator(
        (this->template dcast<typename Self::StorageType>()).erase(tmpFirst,
                                                                   tmpLast ),
        this);
    
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::push_back(ArgumentType value)
{
    RefCountPolicy::addRef(value);

    _values.push_back(value);

    ParentHandler::updateParentLinking(value, _pParent, _usParentFieldPos);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::resize(size_t     newsize, 
                                                          StoredType t)
{
    size_t oldSize = _values.size();

    if(newsize < oldSize)
    {
        this->erase(this->begin_nc() + newsize, this->end_nc());
    }
    else
    {
        _values.resize(newsize, t);

        ParentHandler::updateParentLinking(t, _pParent, _usParentFieldPos);

        typename Inherited::iterator       vI = _values.begin() + oldSize;
        typename Inherited::const_iterator vE = _values.end  ();
        
        for(; vI != vE; ++vI)
        {
            RefCountPolicy::addRef(*vI);
        }
    }
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::replace(UInt32       uiIdx, 
                                                           ArgumentType value)
{
    StorageType &oStorage = this->template dcast<typename Self::StorageType>();

    ParentHandler::clearParentLinking( oStorage[uiIdx], 
                                      _pParent, 
                                      _usParentFieldPos);

    RefCountPolicy::setRefd(oStorage[uiIdx], value);

    ParentHandler::updateParentLinking(value, _pParent, _usParentFieldPos);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, 
                                  RefCountPolicy, 
                                  iNamespace    >::replace(iterator     pos, 
                                                           ArgumentType value)
{
    typename StorageType::iterator tmpIt(pos);

    ParentHandler::clearParentLinking(*tmpIt, _pParent, _usParentFieldPos);

    RefCountPolicy::setRefd(*tmpIt, value);

    ParentHandler::updateParentLinking(value, _pParent, _usParentFieldPos);
}

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::const_reference 
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::operator [](
                                     UInt32 index) const
{
    ValueT returnValue = 
        (this->template dcast<typename Self::StorageType>())[index];

    return RefCountPolicy::validate(returnValue);
}

#ifndef OSG_CLEAN_FCFIELDS
template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
typename FieldContainerPtrChildMField<ValueT, 
                                      RefCountPolicy, 
                                      iNamespace    >::reference 
    FieldContainerPtrChildMField<ValueT, 
                                 RefCountPolicy, 
                                 iNamespace    >::operator [](UInt32 index) 
{
    return typename Self::reference(this->begin_nc() + index, this);
}
#endif

template<class    ValueT, 
         typename RefCountPolicy, 
         Int32    iNamespace    > inline
void FieldContainerPtrChildMField<ValueT, RefCountPolicy, iNamespace>::syncWith(
    Self               &source, 
    ConstFieldMaskArg   syncMode,
    UInt32              uiSyncInfo,
    AspectOffsetStore  &oOffsets  )
{
    size_type n = source.size();

    if(n != 0)
    {
        if(_values.size() == 0)
        {
            _values.resize(n, NULL);

            Inherited::iterator sIt  = source._values.begin();
            Inherited::iterator sEnd = source._values.end  ();

            Inherited::iterator fIt  = _values.begin();
        
            while(sIt != sEnd)
            {
                *fIt = convertToCurrentAspect(*sIt);

                RefCountPolicy::addRef(*fIt);
                
                ++sIt;
                ++fIt;
            }
        }
        else
        {
            if(n > _values.size())
            {
                _values.resize(n, NullFC);
            }

            Inherited::      iterator sIt  =  source._values.begin();

            Inherited::iterator       fIt  = _values.begin();
            Inherited::const_iterator fEnd = _values.end  ();

            for(UInt32 i = 0; i < n; ++i)
            {
                if(*fIt != NULL)
                {
                    Thread::getCurrentChangeList()->addDelayedSubRef<
                        RefCountPolicy>(*fIt);
                }

                *fIt = convertToCurrentAspect(*sIt);

                RefCountPolicy::addRef(*fIt);

                ++sIt;
                ++fIt;
            }

            if(n < _values.size())
            {
                while(fIt != fEnd)
                {
                    if(*fIt != NULL)
                    {
                        Thread::getCurrentChangeList()->addDelayedSubRef
                            <RefCountPolicy>(*fIt);
                    }

                    ++fIt;
                };

                _values.resize(n);
            }
        }
    }
    else
    {
        this->clear();
    }

#if 0
    if(source.size() != 0)
    {
        this->resize(source.size(), NullFC);

        Inherited::iterator sIt  = source._values.begin();
        Inherited::iterator sEnd = source._values.end  ();

        Inherited::iterator fIt  = _values.begin();
        
        while(sIt != sEnd)
        {
#if 1
            RefCountPolicy::setRefd((*fIt),
                                    convertToCurrentAspect(*sIt));
#endif
//            *fIt = convertToCurrentAspect(*sIt);

            ++sIt;
            ++fIt;
        }
    }
    else
    {
        this->clear();
    }
#endif
}

OSG_END_NAMESPACE

