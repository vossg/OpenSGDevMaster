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
/*! \file OSGChildPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ChildMFieldIterator<ObjectTypeT>                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::ChildMFieldIterator(void) : 
     Inherited(    ),
    _pField   (NULL)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::ChildMFieldIterator(const Self &source) :
     Inherited(source        ),
    _pField   (source._pField)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::ChildMFieldIterator(
                        const PtrStoreItType &storeIter,  
                              MFieldType     *pField   ) :
     Inherited(storeIter),
    _pField   (pField   )
{
}


/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::~ChildMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::reference
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::operator * (void) const
{
    return reference(*this, _pField);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::reference
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator [](
                            const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#else
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::const_value
ChildMFieldIterator<ObjectTypeT, 
                    RefCountPolicy, 
                    iNamespace    >::operator * (void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::const_value
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator [](
                            const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#endif

    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::Self &
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator ++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::Self &
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator --(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::operator--();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::Self &
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace>::operator +=(const difference_type offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace   >::operator +(
                            const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, RefCountPolicy, iNamespace>::Self &
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::operator -=(
                            const difference_type offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldIterator<ObjectTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy,  
                        iNamespace    >::operator -(
                            const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldIterator<ObjectTypeT, 
                         RefCountPolicy,  
                         iNamespace    >::operator == (const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy,  
                        iNamespace    >::operator != (const Self &rhs) const
{
    return ! (*this == rhs);
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy,  
                        iNamespace    >::operator == (
                            const const_iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy,  
                        iNamespace    >::operator != (
                            const const_iterator &rhs) const
{
    return ! (*this == rhs);
}


/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
const typename ChildMFieldIterator<ObjectTypeT, 
                                   RefCountPolicy, 
                                   iNamespace    >::PtrStoreItType &
    ChildMFieldIterator<ObjectTypeT, 
                        RefCountPolicy, 
                        iNamespace    >::base(void) const
{
    return *this;
}


#if 0

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT, Int32 iNamespace>
typename ChildMFieldIterator<ObjectTypeT, iNamespace>::difference_type
    operator-(ChildMFieldIterator<ObjectTypeT, iNamespace> const &lhs,
              ChildMFieldIterator<ObjectTypeT, iNamespace> const &rhs )
{
    return std::distance<
        typename ChildMFieldIterator<ObjectTypeT, iNamespace>::StoreItType
                         >(lhs, rhs);
}

template <class ObjectTypeT, Int32 iNamespace>
ChildMFieldIterator<ObjectTypeT, iNamespace>
    operator+(
        typename ChildMFieldIterator<ObjectTypeT, iNamespace>::differece_type const offset,
        ChildMFieldIterator<ObjectTypeT, iNamespace>                          const &rhs   )
{
    return ChildMFieldIterator<ObjectTypeT, iNamespace>(rhs) += offset;
}
#endif


/*-------------------------------------------------------------------------*/
/* ChildMFieldConstIterator<ObjectTypeT>                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldConstIterator<ObjectTypeT, 
                         RefCountPolicy, 
                         iNamespace    >::ChildMFieldConstIterator(void) : 
    Inherited()
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldConstIterator<ObjectTypeT, 
                         RefCountPolicy, 
                         iNamespace    >::ChildMFieldConstIterator(
                             const Self &source) : 
    Inherited(source)
{
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<ObjectTypeT, 
                         RefCountPolicy, 
                         iNamespace    >::ChildMFieldConstIterator(
                             const iterator &fieldIter) : 
    Inherited(fieldIter.base())
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldConstIterator<ObjectTypeT, 
                         RefCountPolicy, 
                         iNamespace    >::ChildMFieldConstIterator(
                             const PtrStoreConstItType &storeIter) : 
    Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
ChildMFieldConstIterator<ObjectTypeT, 
                         RefCountPolicy, 
                         iNamespace    >::~ChildMFieldConstIterator(void)
{
}


/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::const_value
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}
    
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::const_value
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator [](
                                 const difference_type offset) const
{
    return *(*this + offset);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator ++(void)
{
    this->Inherited::operator++();
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator ++(int)
{
    Self retVal = *this;
    
    this->Inherited::operator++();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator --(void)
{
    this->Inherited::operator--();
    
    return *this;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator --(int)
{
    Self retVal = *this;
    
    this->Inherited::oprator--();
    
    return retVal;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace   >::Self &
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator +=(
                                 const difference_type offset)
{
    this->Inherited::operator+=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator +(
                                 const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal += offset;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator -=(
                                 const difference_type offset)
{
    this->Inherited::operator-=(offset);
    
    return *this;
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldConstIterator<ObjectTypeT, 
                                  RefCountPolicy, 
                                  iNamespace    >::Self
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::operator -(
                                 const difference_type offset) const
{
    Self retVal = *this;
    
    return retVal -= offset;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldConstIterator<ObjectTypeT, 
                              RefCountPolicy,  
                              iNamespace    >::operator == (
                                  const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldConstIterator<ObjectTypeT, 
                              RefCountPolicy,  
                              iNamespace    >::operator != (
                                  const Self &rhs) const
{
    return ! (*this == rhs);
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldConstIterator<ObjectTypeT, 
                              RefCountPolicy,  
                              iNamespace    >::operator == (
                                  const iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
bool ChildMFieldConstIterator<ObjectTypeT, 
                              RefCountPolicy,  
                              iNamespace    >::operator != (
                                  const iterator &rhs) const
{
    return ! (*this == rhs);
}


/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
const typename ChildMFieldConstIterator<ObjectTypeT, 
                                        RefCountPolicy, 
                                        iNamespace    >::PtrStoreConstItType &
    ChildMFieldConstIterator<ObjectTypeT, 
                             RefCountPolicy, 
                             iNamespace    >::base(void) const
{
    return *this;
}

#if 0

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class ObjectTypeT, Int32 iNamespace>
typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT, iNamespace> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT, iNamespace> const &rhs )
{
    return typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::
               PtrStoreConstItType(lhs) -
           typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::
               PtrStoreConstItType(rhs);
}
              
template <class ObjectTypeT, Int32 iNamespace>
typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::difference_type
    operator-(ChildMFieldIterator     <ObjectTypeT, iNamespace> const &lhs,
              ChildMFieldConstIterator<ObjectTypeT, iNamespace> const &rhs )
{
    return typename ChildMFieldIterator<ObjectTypeT, iNamespace>::
               PtrStoreItType(lhs) -
           typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::
               PtrStoreConstItType(rhs);
}

template <class ObjectTypeT, Int32 iNamespace>
typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::difference_type
    operator-(ChildMFieldConstIterator<ObjectTypeT, iNamespace> const &lhs,
              ChildMFieldIterator     <ObjectTypeT, iNamespace> const &rhs )
{
    return typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::
               PtrStoreConstItType(lhs) -
           typename ChildMFieldIterator<ObjectTypeT, iNamespace>::
               PtrStoreItType(rhs);
}             
              
template <class ObjectTypeT, Int32 iNamespace>
ChildMFieldConstIterator<ObjectTypeT, iNamespace>
    operator+(
        typename ChildMFieldConstIterator<ObjectTypeT, iNamespace>::difference_type const offset,
        ChildMFieldConstIterator<ObjectTypeT, iNamespace>                           const &rhs   )
{
    return ChildMFieldConstIterator<ObjectTypeT, iNamespace>(rhs) += offset;
}
#endif

/*-------------------------------------------------------------------------*/
/* ChildMFieldReferenceProxy<ObjectTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<ObjectTypeT, 
                          RefCountPolicy, 
                          iNamespace    >::ChildMFieldReferenceProxy(
                              const PtrStoreItType &storeIter, 
                                    MFieldType     *pField   ) : 
    _storeIter(storeIter),
    _pField   (pField   )
{
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<ObjectTypeT, 
                          RefCountPolicy, 
                          iNamespace    >::ChildMFieldReferenceProxy(
                              const Self &source) : 
    _storeIter(source._storeIter),
    _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<ObjectTypeT, 
                          RefCountPolicy, 
                          iNamespace    >::~ChildMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<ObjectTypeT, 
                          RefCountPolicy, 
                          iNamespace    >::operator const_value(void) const
{
    return static_cast<const_value>(AccessHandler::validate(*_storeIter));
}
            
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
typename ChildMFieldReferenceProxy<ObjectTypeT, 
                                   RefCountPolicy, 
                                   iNamespace    >::const_value
     ChildMFieldReferenceProxy<ObjectTypeT, 
                               RefCountPolicy, 
                               iNamespace    >::operator->(void) const
{
    return static_cast<const_value>(AccessHandler::validate(*_storeIter));
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 iNamespace> inline 
void ChildMFieldReferenceProxy<ObjectTypeT, 
                               RefCountPolicy, 
                               iNamespace    >::operator =(const_value newValue)
{
    AccessHandler::onReplace(_pField, *_storeIter, newValue);
    
    *_storeIter = newValue;
}


/*-------------------------------------------------------------------------*/
/* ChildPointerMField<ObjectTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
const FieldType &ChildPointerMField<ObjectTypeT,
                                    RefCountPolicy, 
                                    NamespaceI    >::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerMField<ObjectTypeT,
                   RefCountPolicy, 
                   NamespaceI  >::ChildPointerMField(
                       FieldContainerPtr pParent,
                       UInt16            usParentFieldPos) : 
    Inherited(pParent, usParentFieldPos)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerMField<ObjectTypeT,
                   RefCountPolicy, 
                   NamespaceI    >::~ChildPointerMField(void)
{
}


/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::begin_nc(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::end_nc(void)
{
    return iterator(this->_ptrStore.end(), this);
}

#ifndef OSG_CLEAN_FCFIELDS
    reference front_nc(void             );
    reference back_nc (void             );

    iterator  find_nc (const_value value);
#endif

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::begin(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::end(void)
{
    return iterator(this->_ptrStore.end(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::rbegin(void)
{
    return reverse_iterator(this->end());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::rend(void)
{
    return reverse_iterator(this->begin());
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::begin(void) const
{
    return const_iterator(this->_ptrStore.begin());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::end(void) const
{
    return const_iterator(this->_ptrStore.end());
}
    
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::const_reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::const_reverse_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}


#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::reference
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::front(void)
{
    return reference(this->_ptrStore.begin(), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::reference
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::back(void)
{
    return reference(this->editRawStore().end() - 1, this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::const_value
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::front(void) const
{
    return static_cast<const_value>(this->ptrStoreGet(this->_ptrStore.begin()));
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::const_value
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::back(void) const
{
    return static_cast<const_value>(
        this->ptrStoreGet(this->_ptrStore.end() - 1));
}



   
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator 
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::insert(iterator    pos, 
                                               const_value value)
{
    return iterator(this->ptrStoreInsert(pos.base(), value), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> 
template <class InputIteratorT                                        > inline
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI  >::insert(iterator       pos, 
                                              InputIteratorT first, 
                                              InputIteratorT last)
{
    return this->ptrStoreInsert(pos.base(), first, last);
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator 
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::erase(iterator pos)
{
    return iterator(this->ptrStoreErase(pos.base()), this);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator 
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::erase(
        iterator first, iterator last)
{
    return iterator(this->ptrStoreErase(first.base(), last.base()), this);
}

   
#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::find(const_value value)
{
    return iterator(this->ptrStoreFind(value), this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI    >::const_iterator
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::find(const_value value) const
{
    return const_iterator(this->ptrStoreFind(value),
                          this                     );
}


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::push_back(const_value value)
{
    this->ptrStoreAppend(value);
}
   
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::resize(size_t      newSize, 
                                                const_value value  )
{
    this->ptrStoreResize(newSize, value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::clear(void)
{
    this->ptrStoreClear();
}

                       
#ifdef OSG_1_COMPAT
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::addValue(const_value value)
{
    this->ptrStoreAppend(value);
}
#endif


template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::assign(size_type   newSize, 
                                                const_value value  )
{
    this->ptrStoreClear();

    for(size_type i = 0; i < newSize; ++i)
        this->ptrStoreAppend(value);
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline 
void ChildPointerMField<ObjectTypeT,
                        RefCountPolicy, 
                        NamespaceI    >::assign(InputIteratorT first, 
                                                InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}


/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

#ifndef OSG_CLEAN_FCFIELDS
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::reference
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI    >::operator [](const UInt32 index)
{
    return reference(this->_ptrStore.begin() + index, this);
}
#endif

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
typename ChildPointerMField<ObjectTypeT,
                            RefCountPolicy, 
                            NamespaceI  >::const_value
    ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI  >::operator [](const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}


#ifdef OSG_MT_CPTR_ASPECT
template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI> inline 
void ChildPointerMField<ObjectTypeT,
                       RefCountPolicy, 
                       NamespaceI  >::syncWith(Self               &source, 
                                               ConstFieldMaskArg   syncMode,
                                               UInt32              uiSyncInfo,
                                               AspectOffsetStore  &oOffsets  )
{
    Inherited::syncWith(source, syncMode, uiSyncInfo, oOffsets);
}
#endif

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

#if 0

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline void
    ChildPointerMField<ObjectTypeT,
                               RefCountPolicy, 
                       NamespaceI  >::setValues(Self const &source)
{
    this->assign(source.begin(), source.end());
}

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                               RefCountPolicy, 
                                   NamespaceI  >::Self &
    ChildPointerMField<ObjectTypeT,
                               RefCountPolicy, 
                       NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);
    
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Value Access                                                            */

template <class ObjectTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline typename ChildPointerMField<ObjectTypeT,
                               RefCountPolicy, 
                                   NamespaceI  >::ValueStoreType const &
    ChildPointerMField<ObjectTypeT,
                               RefCountPolicy, 
                       NamespaceI  >::getValues(void) const
{
    return this->template getStore<ValueType>();
}
#endif

OSG_END_NAMESPACE
