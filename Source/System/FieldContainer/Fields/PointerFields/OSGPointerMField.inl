/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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
/*! \file OSGPointerPointerMField.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* PointerMFieldIterator<ObjectTypeT>                                      */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldIterator<ObjectTypeT,
                      RefCountPolicy,
                      NamespaceI    >::PointerMFieldIterator(void) : 
     Inherited(    ),
    _pField   (NULL)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldIterator<ObjectTypeT,
                      RefCountPolicy,
                      NamespaceI    >::PointerMFieldIterator(
                          const Self &source) : 
     Inherited(source        ),
    _pField   (source._pField)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldIterator<ObjectTypeT,
                      RefCountPolicy,
                      NamespaceI    >::PointerMFieldIterator(
                          const PtrStoreItType &storeIter,  
                                MFieldType     *pField) : 
     Inherited(storeIter),
    _pField   (pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldIterator<ObjectTypeT,
                      RefCountPolicy,
                      NamespaceI    >::~PointerMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::reference
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator *(void) const
{
    return reference(*this, _pField);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::reference
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI>::operator [](
                              const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#else
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::const_value
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::const_value
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI>::operator [](
                              const difference_type offset) const
{
    return *(*this + offset);
}
#endif
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self &
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI>::operator ++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self &
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator --(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self &
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator +=(
                              const difference_type offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator +(
                              const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self &
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator -=(
                              const difference_type offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename PointerMFieldIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::Self
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::operator - (
                              const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool PointerMFieldIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::operator ==(const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool PointerMFieldIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::operator !=(const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool PointerMFieldIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::operator ==(
                               const const_iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool PointerMFieldIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::operator !=(
                               const const_iterator &rhs) const
{
    return ! (*this == rhs);
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
const typename PointerMFieldIterator<ObjectTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::PtrStoreItType &
    PointerMFieldIterator<ObjectTypeT,
                          RefCountPolicy,
                          NamespaceI    >::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

#if 0
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
typename WeakMFieldIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator<ObjectTypeT> const &rhs )
{
    return std::distance<
        typename WeakMFieldIterator<ObjectTypeT>::StoreItType
                         >(lhs, rhs);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
WeakMFieldIterator<ObjectTypeT>
    operator+(typename WeakMFieldIterator<ObjectTypeT>::differece_type const offset,
              WeakMFieldIterator<ObjectTypeT>                          const &rhs   )
{
    return WeakMFieldIterator<ObjectTypeT>(rhs) += offset;
}
#endif



/*-------------------------------------------------------------------------*/
/* PointerMFieldConstIterator<ObjectTypeT>                                 */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldConstIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::PointerMFieldConstIterator(void) : 
    Inherited()
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldConstIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::PointerMFieldConstIterator(
                            const Self &source) : 
    Inherited(source)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMFieldConstIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::PointerMFieldConstIterator(
                            const iterator &fieldIter) :
    Inherited(fieldIter.base())
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldConstIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::PointerMFieldConstIterator(
                            const PtrStoreConstItType &storeIter) :
    Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
PointerMFieldConstIterator<ObjectTypeT,
                           RefCountPolicy,
                           NamespaceI    >::~PointerMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::const_value
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}
    
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI   >::const_value
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator [](
        const difference_type offset) const
{
    return *(*this + offset);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self &
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator ++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self &
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator --(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::oprator--();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self &
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator +=(
                                   const difference_type offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator +(
                                   const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self &
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator -=(
                                   const difference_type offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMFieldConstIterator<ObjectTypeT,
                                    RefCountPolicy,
                                    NamespaceI    >::Self
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::operator -(
                                   const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
bool PointerMFieldConstIterator<ObjectTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator ==(
                                   const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
bool PointerMFieldConstIterator<ObjectTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator !=(
                                   const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
bool PointerMFieldConstIterator<ObjectTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator ==(
                                    const iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
bool PointerMFieldConstIterator<ObjectTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator !=(
                                    const iterator &rhs) const
{
    return ! (*this == rhs);
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
const typename PointerMFieldConstIterator<ObjectTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::PtrStoreConstItType &
    PointerMFieldConstIterator<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI    >::base(void) const
{
    return *this;
}

#if 0
/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}
              
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldIterator     <ObjectTypeT> const &lhs,
              WeakMFieldConstIterator<ObjectTypeT> const &rhs )
{
    return typename WeakMFieldIterator<ObjectTypeT>::
               PtrStoreItType(lhs) -
           typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(rhs);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
typename WeakMFieldConstIterator<ObjectTypeT>::difference_type
    operator-(WeakMFieldConstIterator<ObjectTypeT> const &lhs,
              WeakMFieldIterator     <ObjectTypeT> const &rhs )
{
    return typename WeakMFieldConstIterator<ObjectTypeT>::
               PtrStoreConstItType(lhs) -
           typename WeakMFieldIterator<ObjectTypeT>::
               PtrStoreItType(rhs);
}             
              
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
WeakMFieldConstIterator<ObjectTypeT>
    operator+(typename WeakMFieldConstIterator<ObjectTypeT>::difference_type const offset,
              WeakMFieldConstIterator<ObjectTypeT>                           const &rhs   )
{
    return WeakMFieldConstIterator<ObjectTypeT>(rhs) += offset;
}
#endif


/*-------------------------------------------------------------------------*/
/* PointerMFieldReferenceProxy<ObjectTypeT>                                */
/*-------------------------------------------------------------------------*/

#ifndef OSG_CLEAN_FCFIELDS
/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMFieldReferenceProxy<ObjectTypeT,
                            RefCountPolicy,
                            NamespaceI    >::PointerMFieldReferenceProxy(
                                const PtrStoreItType &storeIter, 
                                      MFieldType     *pField   ) :
    _storeIter(storeIter),
    _pField   (pField   )
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMFieldReferenceProxy<ObjectTypeT,
                            RefCountPolicy,
                            NamespaceI    >::PointerMFieldReferenceProxy(
                                const Self &source) :
    _storeIter(source._storeIter),
    _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMFieldReferenceProxy<ObjectTypeT,
                            RefCountPolicy,
                            NamespaceI    >::~PointerMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMFieldReferenceProxy<ObjectTypeT,
                            RefCountPolicy,
                            NamespaceI    >::operator value_type(void) const
{
    return AccessHandler::validate(*_storeIter);
}
            
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename PointerMFieldReferenceProxy<ObjectTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::value_type
     PointerMFieldReferenceProxy<ObjectTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator->(void) const
{
    return AccessHandler::validate(*_storeIter);
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMFieldReferenceProxy<ObjectTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator=(value_type newValue)
{
    AccessHandler::onReplace(
        _pField, *_storeIter, newValue);
    
    *_storeIter = newValue;
}

#endif

/*-------------------------------------------------------------------------*/
/* PointerPointerMField<ObjectTypeT,                                          */
/*                   NamespaceI  >                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
const FieldType &PointerMField<ObjectTypeT,
                               RefCountPolicy,
                               NamespaceI >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerMField(void) : 
    Inherited()
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerMField(Self const &other) : 
    Inherited(other)
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::PointerMField(UInt32 const size) : 
    Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
PointerMField<ObjectTypeT,
              RefCountPolicy,
              NamespaceI    >::~PointerMField(void)
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}



template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::begin_nc(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::end_nc(void)
{
    return iterator(this->_ptrStore.end(), this);
}

#ifndef OSG_CLEAN_FCFIELDS
    reference front_nc(void              );
    reference back_nc (void              );

    iterator  find_nc (ArgumentType value);
#endif

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::begin(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::end(void)
{
    return iterator(this->_ptrStore, this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::reverse_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::rbegin(void)
{
    return reverse_iterator(this->end());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::reverse_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::rend(void)
{
    return reverse_iterator(this->begin());
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::begin(void) const
{
    return const_iterator(this->_ptrStore.begin());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::end(void) const
{
    return const_iterator(this->_ptrStore.end());
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_reverse_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_reverse_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::reference
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::front(void)
{
    return reference(this->_ptrStore.begin(), this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_value
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::front(void) const
{
    return static_cast<const_value>(this->ptrStoreGet(this->_ptrStore.begin()));
}

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::reference
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::back(void)
{
    return reference(this->_ptrStore.end() - 1, this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_value
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::back(void) const
{
    return static_cast<const_value>(
        this->ptrStoreGet(this->_ptrStore.end() - 1));
}

   
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI  >::insert(iterator pos, const_value value)
{
    return iterator(this->ptrStoreInsert(pos.base(), value), this);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::insert(iterator       pos, 
                                           InputIteratorT first, 
                                           InputIteratorT last)
{
    this->ptrStoreInsert(pos.base(), first, last);
}
 
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::erase(iterator pos)
{
    return iterator(this->ptrStoreErase(pos.base()), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::erase(iterator first, iterator last)
{
    return iterator(this->ptrStoreErase(first.base(), last.base()), this);
}
    
#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::find(const_value value)
{
    return iterator(this->ptrStoreFind(value),
                    this                     );
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_iterator
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::find(const_value value) const
{
    return const_iterator(this->ptrStoreFind(value),
                          this                     );
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::push_back(const_value value)
{
    this->ptrStoreAppend(value);
}
   
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::resize(size_t newSize, const_value value)
{
    this->ptrStoreResize(newSize, value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::clear(void)
{
    this->ptrStoreClear();
}
                               
#ifdef OSG_1_COMPAT
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::addValue(const_value value)
{
    this->push_back(value);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::assign(size_type newSize, 
                                           const_value value)
{
    this->ptrStoreClear();
    
    for(size_type i = 0; i < newSize; ++i)
        this->ptrStoreAppend(value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::assign(InputIteratorT first, 
                                           InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::replace(UInt32      uiIdx, 
                                            const_value value)
{
    this->ptrStoreReplace(uiIdx, value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::replace(iterator    pos, 
                                            const_value value)
{
    this->ptrStoreReplace(pos.base(), value);
}

/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::reference
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::operator [](const UInt32 index)
{
    return reference(_ptrStore.begin() + index, this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::const_value
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::operator [](const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

#ifdef OSG_FIELD_TOCHECK
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename PointerMField<ObjectTypeT,
                       RefCountPolicy,
                       NamespaceI    >::Self &
    PointerMField<ObjectTypeT,
                  RefCountPolicy,
                  NamespaceI    >::operator=(const Self &source)
{
    this->setValues(source);
    
    return *this;
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void PointerMField<ObjectTypeT,
                   RefCountPolicy,
                   NamespaceI    >::syncWith(Self               &source, 
                                             ConstFieldMaskArg   syncMode,
                                             UInt32              uiSyncInfo,
                                             AspectOffsetStore  &oOffsets    )
{
    Inherited::syncWith(source,
                        syncMode,
                        uiSyncInfo,
                        oOffsets  );
}
#endif

OSG_END_NAMESPACE
