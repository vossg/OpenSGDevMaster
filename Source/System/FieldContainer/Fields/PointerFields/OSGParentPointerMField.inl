/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGParentPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE


/*-------------------------------------------------------------------------*/
/* ParentMFieldConstIterator<PtrTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class StorageTypeT> inline
ParentMFieldConstIterator<StorageTypeT>::ParentMFieldConstIterator(void) : 
     Inherited(),
    _posIt    ()
{
}

template <class StorageTypeT> inline
ParentMFieldConstIterator<StorageTypeT>::ParentMFieldConstIterator(
                              const Self &source) : 
     Inherited(source       ),
    _posIt    (source._posIt)
{
}

template <class StorageTypeT> inline
ParentMFieldConstIterator<StorageTypeT>::ParentMFieldConstIterator(
                              const iterator &fieldIter) : 
     Inherited(fieldIter.ptrBase()),
    _posIt    (fieldIter._posIt   )
{
}

template <class StorageTypeT> inline
ParentMFieldConstIterator<StorageTypeT>::ParentMFieldConstIterator(
                              const Inherited    &storeIt,
                              const PosStorageIt &posIt  ) : 
     Inherited(storeIt),
    _posIt    (posIt  )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class StorageTypeT> inline
ParentMFieldConstIterator<StorageTypeT>::~ParentMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::const_value
    ParentMFieldConstIterator<StorageTypeT>::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::const_value
    ParentMFieldConstIterator<StorageTypeT>::operator[](
        const  difference_type offset) const
{
    return *(*this + offset);
}


template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self &
    ParentMFieldConstIterator<StorageTypeT>::operator ++(void)
{
    this->Inherited::operator++();

    ++_posIt;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self
    ParentMFieldConstIterator<StorageTypeT>::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();

    ++_posIt;
    
    return retVal;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self &
    ParentMFieldConstIterator<StorageTypeT>::operator --(void)
{
    this->Inherited::operator--();

    --_posIt;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self
    ParentMFieldConstIterator<StorageTypeT>::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();

    --_posIt;
    
    return retVal;
}


template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self &
    ParentMFieldConstIterator<StorageTypeT>::operator +=(
        const difference_type offset)
{
    this->Inherited::operator+=(offset);

    _posIt += offset;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self
    ParentMFieldConstIterator<StorageTypeT>::operator +(
        const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self &
    ParentMFieldConstIterator<StorageTypeT>::operator -=(
        const difference_type offset)
{
    this->Inherited::operator -=(offset);

    _posIt -= offset;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::Self
    ParentMFieldConstIterator<StorageTypeT>::operator -(
        const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class StorageTypeT> inline 
bool ParentMFieldConstIterator<StorageTypeT>::operator == (
    const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class StorageTypeT> inline 
bool ParentMFieldConstIterator<StorageTypeT>::operator != (
    const Self &rhs) const
{
    return ! (*this == rhs);
}
    
template <class StorageTypeT> inline 
bool ParentMFieldConstIterator<StorageTypeT>::operator == (
    const iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class StorageTypeT> inline 
bool ParentMFieldConstIterator<StorageTypeT>::operator != (
    const iterator &rhs   ) const
{
    return ! (*this == rhs);
}


template <class StorageTypeT> inline 
typename ParentMFieldConstIterator<StorageTypeT>::const_value
    ParentMFieldConstIterator<StorageTypeT>::getPtr(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator *()));
}

template <class StorageTypeT> inline 
UInt16 ParentMFieldConstIterator<StorageTypeT>::getParentFieldPos(void) const
{
    return *_posIt;
}

template <class StorageTypeT> inline 
const typename ParentMFieldConstIterator<StorageTypeT>::Inherited &
    ParentMFieldConstIterator<StorageTypeT>::ptrBase(void) const
{
    return *this;
}

template <class StorageTypeT> inline 
const typename ParentMFieldConstIterator<StorageTypeT>::PosStorageIt &
    ParentMFieldConstIterator<StorageTypeT>::idBase (void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

#if 0
template <class StorageTypeT, typename AccessHandlerT>
template <class PtrTypeT>
inline typename ParentMFieldConstIterator<PtrTypeT>::PtrStoreConstItType const &
    ParentMFieldConstIterator<PtrTypeT>::base(void) const
{
    return *this;
}
#endif


/*-------------------------------------------------------------------------*/
/* ParentMFieldIterator<PtrTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class StorageTypeT> inline
ParentMFieldIterator<StorageTypeT>::ParentMFieldIterator(void) : 
     Inherited(),
    _posIt    ()
{
}

template <class StorageTypeT> inline
ParentMFieldIterator<StorageTypeT>::ParentMFieldIterator(
                              const Self &source) : 
     Inherited(source       ),
    _posIt    (source._posIt)
{
}

template <class StorageTypeT> inline
ParentMFieldIterator<StorageTypeT>::ParentMFieldIterator(
                              const Inherited    &storeIt,
                              const PosStorageIt &posIt  ) : 
     Inherited(storeIt),
    _posIt    (posIt  )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class StorageTypeT> inline
ParentMFieldIterator<StorageTypeT>::~ParentMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::const_value
    ParentMFieldIterator<StorageTypeT>::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::const_value
    ParentMFieldIterator<StorageTypeT>::operator[](
        const  difference_type offset) const
{
    return *(*this + offset);
}


template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self &
    ParentMFieldIterator<StorageTypeT>::operator ++(void)
{
    this->Inherited::operator++();

    ++_posIt;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self
    ParentMFieldIterator<StorageTypeT>::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();

    ++_posIt;
    
    return retVal;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self &
    ParentMFieldIterator<StorageTypeT>::operator --(void)
{
    this->Inherited::operator--();

    --_posIt;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self
    ParentMFieldIterator<StorageTypeT>::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();

    --_posIt;
    
    return retVal;
}


template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self &
    ParentMFieldIterator<StorageTypeT>::operator +=(
        const difference_type offset)
{
    this->Inherited::operator+=(offset);

    _posIt += offset;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self
    ParentMFieldIterator<StorageTypeT>::operator +(
        const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self &
    ParentMFieldIterator<StorageTypeT>::operator -=(
        const difference_type offset)
{
    this->Inherited::operator -=(offset);

    _posIt -= offset;
    
    return *this;
}

template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::Self
    ParentMFieldIterator<StorageTypeT>::operator -(
        const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class StorageTypeT> inline 
bool ParentMFieldIterator<StorageTypeT>::operator == (const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class StorageTypeT> inline 
bool ParentMFieldIterator<StorageTypeT>::operator != (const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class StorageTypeT> inline 
bool ParentMFieldIterator<StorageTypeT>::operator == (
    const const_iterator  &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class StorageTypeT> inline 
bool ParentMFieldIterator<StorageTypeT>::operator != (
    const const_iterator &rhs) const
{
    return ! (*this == rhs);
}


template <class StorageTypeT> inline 
typename ParentMFieldIterator<StorageTypeT>::const_value
    ParentMFieldIterator<StorageTypeT>::getPtr(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator *()));
}

template <class StorageTypeT> inline 
UInt16 ParentMFieldIterator<StorageTypeT>::getParentFieldPos(void) const
{
    return *_posIt;
}

template <class StorageTypeT> inline 
const typename ParentMFieldIterator<StorageTypeT>::Inherited &
    ParentMFieldIterator<StorageTypeT>::ptrBase(void) const
{
    return *this;
}

template <class StorageTypeT> inline 
const typename ParentMFieldIterator<StorageTypeT>::PosStorageIt &
    ParentMFieldIterator<StorageTypeT>::idBase (void) const
{
    return _posIt;
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

#if 0
template <class StorageTypeT, typename AccessHandlerT>
template <class PtrTypeT>
inline typename ParentMFieldConstIterator<PtrTypeT>::PtrStoreConstItType const &
    ParentMFieldConstIterator<PtrTypeT>::base(void) const
{
    return *this;
}
#endif


/*-------------------------------------------------------------------------*/
/* ParentPointerMField<PtrTypeT,                                        */
/*                     NamespaceI  >                                       */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::ParentPointerMField(void) : 
     Inherited (),
    _vParentPos()
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::ParentPointerMField(const Self &source) : 
     Inherited (source            ),
    _vParentPos(source._vParentPos)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ParentPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::~ParentPointerMField(void)
{
}

/*-------------------------------------------------------------------------*/
/* Binary IO                                                               */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
UInt32 ParentPointerMField<PtrTypeT, 
                           RefCountPolicy, 
                           NamespaceI    >::getBinSize(void) const
{
    size_type returnValue = Inherited::getBinSize();

    returnValue +=
        sizeof(UInt32) + // num elements
        (_vParentPos.size() ? 
         PosMFieldTraits::getBinSize(&(_vParentPos[0]), 
                                       _vParentPos.size()) : 0);

    return returnValue;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT, 
                         RefCountPolicy, 
                         NamespaceI    >::copyToBin(
                             BinaryDataHandler &pMem) const
{
    Inherited::copyToBin(pMem);
    
    UInt32 ptrSize = this->size();

    if(ptrSize > 0)
    {
        PosMFieldTraits::copyToBin(   pMem, 
                                   &(_vParentPos[0]),
                                     _vParentPos.size());
    }
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT, 
                         RefCountPolicy, 
                         NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);

    UInt32 ptrSize = this->size();
    
    if(ptrSize > 0)
    {
        _vParentPos.resize(ptrSize);
        
        PosMFieldTraits::copyFromBin(   pMem, 
                                     &(_vParentPos[0]),
                                        ptrSize);        
    }
    else
    {
        _vParentPos.clear();
    }
}


/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin(void) const
{
    return const_iterator(Self::_ptrStore  .begin(),
                          Self::_vParentPos.begin());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end(void) const
{
    return const_iterator(Self::_ptrStore  .end(),
                          Self::_vParentPos.end());
}
    
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI  >::const_reverse_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_reverse_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

template <class PtrTypeT,typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::front(void) const
{
    return static_cast<const_value>(this->ptrStoreGet(this->_ptrStore.begin()));
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::back(void) const
{
    return static_cast<const_value>(
        this->ptrStoreGet(this->_ptrStore.end() - 1));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin_nc(void)
{
    return iterator(Self::_ptrStore  .begin(),
                    Self::_vParentPos.begin());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end_nc(void) 
{
    return iterator(Self::_ptrStore  .end(),
                    Self::_vParentPos.end());
}
  
#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(Self::_ptrStore  .begin(),
                    Self::_vParentPos.begin());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end(void) 
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(Self::_ptrStore  .end(),
                    Self::_vParentPos.end());
}
    
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI  >::reverse_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rbegin(void) 
{
    return reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reverse_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rend(void) 
{
    return reverse_iterator(this->begin());
}
#endif


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::insert(iterator    pos,
                                                const_value value,
                                                UInt16      parentFieldPos) 
{
    PtrStoreItType ptrIt;
    IdStoreItType  posIt;

    ptrIt = this->ptrStoreInsert(pos.ptrBase(), value);

    posIt = _vParentPos.insert(pos.idBase(), parentFieldPos);

    return iterator(ptrIt, posIt);
}


#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::erase(iterator pos) 
{
    PtrStoreItType ptrIt;
    IdStoreItType  posIt;

    ptrIt = this->ptrStoreErase(pos.ptrBase());

    posIt = _vParentPos.erase(pos.idBase());

    return iterator(ptrIt, posIt);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI     >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI     >::erase(iterator first, iterator last)
{
    PtrStoreItType ptrIt;
    IdStoreItType  posIt;

    ptrIt = this->ptrStoreErase(first.ptrBase(), last.ptrBase());
    posIt = _vParentPos.erase  (first.idBase (), last.idBase ());

    return iterator(ptrIt, posIt);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::erase(size_type pos) 
{
    this->ptrStoreErase(pos);

    IdStoreItType  posIt = _vParentPos.begin();

    posIt += pos;

    _vParentPos.erase(posIt);
}

/*-------------------------------------------------------------------------*/
/* Std library interface                                                   */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT, 
                         RefCountPolicy,
                         NamespaceI    >::reserve(size_type newsize)
{
    this->_ptrStore  .reserve(newsize);
    this->_vParentPos.reserve(newsize);
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find(const_value value)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    IdStoreItType  posIt = _vParentPos.begin();

    PtrStoreItType ptrIt = this->ptrStoreFind(value);

    posIt += (ptrIt - this->_ptrStore.begin());

    return iterator(ptrIt, posIt);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find_nc(const_value value)
{
    IdStoreItType  posIt = _vParentPos.begin();

    PtrStoreItType ptrIt = this->ptrStoreFind(value);

    posIt += (ptrIt - this->_ptrStore.begin());

    return iterator(ptrIt, posIt);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find(const_value value) const
{
    IdStoreConstItType  posIt = _vParentPos.begin();

    PtrStoreConstItType ptrIt = this->ptrStoreFind(value);

    posIt += (ptrIt - this->_ptrStore.begin());

    return const_iterator(ptrIt, posIt);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::push_back(
                            const_value value,
                            UInt16       parentFieldPos)
{
    this->ptrStoreAppend(value);

    _vParentPos.push_back(parentFieldPos);
}


/*-------------------------------------------------------------------------*/
/* IdStore Interface                                                       */




/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

template <class PtrTypeT,typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::operator [](const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}

template <class PtrTypeT,typename RefCountPolicy, Int32 NamespaceI> inline 
typename ParentPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    ParentPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::ptrAt(const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
UInt16 ParentPointerMField<PtrTypeT, 
                           RefCountPolicy,
                           NamespaceI    >::parentFieldPosAt(
                               const UInt32 index) const
{
    return _vParentPos[index];
}


/*-------------------------------------------------------------------------*/
/* MT Sync                                                                 */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ParentPointerMField<PtrTypeT, 
                         RefCountPolicy,
                         NamespaceI>::syncWith(
                             Self               &source,     
                             ConstFieldMaskArg   syncMode,
                             UInt32              uiSyncInfo, 
                             AspectOffsetStore  &oOffsets  )
{
    Inherited::syncWith(source, syncMode, uiSyncInfo, oOffsets);
    
    _vParentPos = source._vParentPos;
}
                        
OSG_END_NAMESPACE
