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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* ChildMFieldIterator<PtrTypeT>                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldIterator<PtrTypeT,
                    RefCountPolicy,
                    iNamespace    >::ChildMFieldIterator(void) :
     Inherited(    ),
    _pField   (NULL)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldIterator<PtrTypeT,
                    RefCountPolicy,
                    iNamespace    >::ChildMFieldIterator(const Self &source) :
     Inherited(source        ),
    _pField   (source._pField)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldIterator<PtrTypeT,
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

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldIterator<PtrTypeT,
                    RefCountPolicy,
                    iNamespace    >::~ChildMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::reference
ChildMFieldIterator<PtrTypeT,
                    RefCountPolicy,
                    iNamespace    >::operator * (void) const
{
    return reference(*this, _pField);
}


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::reference
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator [](
                            const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#else
template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::const_value
ChildMFieldIterator<PtrTypeT,
                    RefCountPolicy,
                    iNamespace    >::operator * (void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::const_value
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator [](
                            const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#endif


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::Self &
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator ++(void)
{
    this->Inherited::operator++();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator ++(int)
{
    Self retVal = *this;

    this->Inherited::operator++();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::Self &
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator --(void)
{
    this->Inherited::operator--();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator --(int)
{
    Self retVal = *this;

    this->Inherited::operator--();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::Self &
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace>::operator +=(const difference_type offset)
{
    this->Inherited::operator+=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace   >::operator +(
                            const difference_type offset) const
{
    Self retVal = *this;

    return retVal += offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT, RefCountPolicy, iNamespace>::Self &
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator -=(
                            const difference_type offset)
{
    this->Inherited::operator-=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldIterator<PtrTypeT, RefCountPolicy, iNamespace>::Self
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator -(
                            const difference_type offset) const
{
    Self retVal = *this;

    return retVal -= offset;
}


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::operator == (const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator != (const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator == (
                            const const_iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::operator != (
                            const const_iterator &rhs) const
{
    return ! (*this == rhs);
}


/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
const typename ChildMFieldIterator<PtrTypeT,
                                   RefCountPolicy,
                                   iNamespace    >::PtrStoreItType &
    ChildMFieldIterator<PtrTypeT,
                        RefCountPolicy,
                        iNamespace    >::base(void) const
{
    return *this;
}


/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename ChildMFieldIterator<PtrTypeT,
                             RefCountPolicyT,
                             iNamespace      >::difference_type
    operator-(ChildMFieldIterator<PtrTypeT,
                                  RefCountPolicyT,
                                  iNamespace      > const &lhs,
              ChildMFieldIterator<PtrTypeT,
                                  RefCountPolicyT,
                                  iNamespace      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
ChildMFieldIterator<PtrTypeT, RefCountPolicyT, iNamespace>
    operator+(
        typename ChildMFieldIterator<PtrTypeT,
                                     RefCountPolicyT,
                                     iNamespace      >::differece_type const offset,
        ChildMFieldIterator<PtrTypeT,
                            RefCountPolicyT,
                            iNamespace               >                 const &rhs   )
{
    return ChildMFieldIterator<PtrTypeT,
                               RefCountPolicyT,
                               iNamespace      >(rhs) += offset;
}


/*-------------------------------------------------------------------------*/
/* ChildMFieldConstIterator<PtrTypeT>                            */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::ChildMFieldConstIterator(void) :
    Inherited()
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::ChildMFieldConstIterator(
                             const Self &source) :
    Inherited(source)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::ChildMFieldConstIterator(
                             const iterator &fieldIter) :
    Inherited(fieldIter.base())
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::ChildMFieldConstIterator(
                             const PtrStoreConstItType &storeIter) :
    Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldConstIterator<PtrTypeT,
                         RefCountPolicy,
                         iNamespace    >::~ChildMFieldConstIterator(void)
{
}


/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::const_value
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::const_value
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator [](
                                 const difference_type offset) const
{
    return *(*this + offset);
}


template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator ++(void)
{
    this->Inherited::operator++();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator ++(int)
{
    Self retVal = *this;

    this->Inherited::operator++();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator --(void)
{
    this->Inherited::operator--();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator --(int)
{
    Self retVal = *this;

    this->Inherited::oprator--();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace   >::Self &
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator +=(
                                 const difference_type offset)
{
    this->Inherited::operator+=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator +(
                                 const difference_type offset) const
{
    Self retVal = *this;

    return retVal += offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self &
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator -=(
                                 const difference_type offset)
{
    this->Inherited::operator-=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicy,
                                  iNamespace    >::Self
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::operator -(
                                 const difference_type offset) const
{
    Self retVal = *this;

    return retVal -= offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldConstIterator<PtrTypeT,
                              RefCountPolicy,
                              iNamespace    >::operator == (
                                  const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldConstIterator<PtrTypeT,
                              RefCountPolicy,
                              iNamespace    >::operator != (
                                  const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldConstIterator<PtrTypeT,
                              RefCountPolicy,
                              iNamespace    >::operator == (
                                  const iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
bool ChildMFieldConstIterator<PtrTypeT,
                              RefCountPolicy,
                              iNamespace    >::operator != (
                                  const iterator &rhs) const
{
    return ! (*this == rhs);
}


/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
const typename ChildMFieldConstIterator<PtrTypeT,
                                        RefCountPolicy,
                                        iNamespace    >::PtrStoreConstItType &
    ChildMFieldConstIterator<PtrTypeT,
                             RefCountPolicy,
                             iNamespace    >::base(void) const
{
    return *this;
}


/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicyT,
                                  iNamespace      >::difference_type
    operator-(ChildMFieldConstIterator<PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &lhs,
              ChildMFieldConstIterator<PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicyT,
                                  iNamespace      >::difference_type
    operator-(ChildMFieldIterator     <PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &lhs,
              ChildMFieldConstIterator<PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
typename ChildMFieldConstIterator<PtrTypeT,
                                  RefCountPolicyT,
                                  iNamespace      >::difference_type
    operator-(ChildMFieldConstIterator<PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &lhs,
              ChildMFieldIterator     <PtrTypeT,
                                       RefCountPolicyT,
                                       iNamespace      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, class RefCountPolicyT, Int32 iNamespace>
ChildMFieldConstIterator<PtrTypeT, RefCountPolicyT, iNamespace>
    operator+(
        typename ChildMFieldConstIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          iNamespace      >::difference_type const offset,
        ChildMFieldConstIterator<PtrTypeT,
                                 RefCountPolicyT,
                                 iNamespace      >                           const &rhs   )
{
    return ChildMFieldConstIterator<PtrTypeT,
                                    RefCountPolicyT,
                                    iNamespace      >(rhs) += offset;
}


/*-------------------------------------------------------------------------*/
/* ChildMFieldReferenceProxy<PtrTypeT>                                  */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<PtrTypeT,
                          RefCountPolicy,
                          iNamespace    >::ChildMFieldReferenceProxy(
                              const PtrStoreItType &storeIter,
                                    MFieldType     *pField   ) :
    _storeIter(storeIter),
    _pField   (pField   )
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<PtrTypeT,
                          RefCountPolicy,
                          iNamespace    >::ChildMFieldReferenceProxy(
                              const Self &source) :
    _storeIter(source._storeIter),
    _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<PtrTypeT,
                          RefCountPolicy,
                          iNamespace    >::~ChildMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
ChildMFieldReferenceProxy<PtrTypeT,
                          RefCountPolicy,
                          iNamespace    >::operator
    typename ChildMFieldReferenceProxy<PtrTypeT,
                                       RefCountPolicy,
                                       iNamespace    >::const_value(void) const
{
    return static_cast<const_value>(AccessHandler::validate(*_storeIter));
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
typename ChildMFieldReferenceProxy<PtrTypeT,
                                   RefCountPolicy,
                                   iNamespace    >::const_value
     ChildMFieldReferenceProxy<PtrTypeT,
                               RefCountPolicy,
                               iNamespace    >::operator->(void) const
{
    return static_cast<const_value>(AccessHandler::validate(*_storeIter));
}

template <class PtrTypeT, typename RefCountPolicy, Int32 iNamespace> inline
void ChildMFieldReferenceProxy<PtrTypeT,
                               RefCountPolicy,
                               iNamespace    >::operator =(const_value newValue)
{
    AccessHandler::onReplace(_pField, *_storeIter, newValue);

    *_storeIter = newValue;
}


/*-------------------------------------------------------------------------*/
/* ChildPointerMField<PtrTypeT,                                         */
/*                    NamespaceI  >                                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerMField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI  >::ChildPointerMField(
                       FieldContainer * const pParent,
                       UInt16                 usChildFieldId,
                       UInt16                 usParentFieldId) :
    Inherited(pParent, usChildFieldId, usParentFieldId)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
ChildPointerMField<PtrTypeT,
                   RefCountPolicy,
                   NamespaceI    >::~ChildPointerMField(void)
{
}


/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::begin_nc(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::end_nc(void)
{
    return iterator(this->_ptrStore.end(), this);
}

#ifndef OSG_CLEAN_FCFIELDS
#if 0
    reference front_nc(void             );
    reference back_nc (void             );
#endif
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::find_nc(const_value value)
{
    return iterator(this->ptrStoreFind(value), this);
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::begin(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->_ptrStore.begin(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::end(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->_ptrStore.end(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::reverse_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::rbegin(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::reverse_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::rend(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reverse_iterator(this->begin());
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::const_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::begin(void) const
{
    return const_iterator(this->_ptrStore.begin());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::const_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::end(void) const
{
    return const_iterator(this->_ptrStore.end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::const_reverse_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI  >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::const_reverse_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}


#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::reference
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::front(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reference(this->_ptrStore.begin(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::reference
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::back(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reference(this->editRawStore().end() - 1, this);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::const_value
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::front(void) const
{
    return static_cast<const_value>(this->ptrStoreGet(this->_ptrStore.begin()));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::const_value
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::back(void) const
{
    return static_cast<const_value>(
        this->ptrStoreGet(this->_ptrStore.end() - 1));
}




template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::insert(iterator    pos,
                                               const_value value)
{
    return iterator(this->ptrStoreInsert(pos.base(), value), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI     >::insert(iterator    pos,
                                                 size_type   n,
                                                 const_value value)
{
    this->ptrStoreInsert(pos, n, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI  >::insert(iterator       pos,
                                              InputIteratorT first,
                                              InputIteratorT last)
{
    this->ptrStoreInsert(pos, first, last);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::erase(size_type index)
{
    return this->ptrStoreErase(index);
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::erase(iterator pos)
{
    return iterator(this->ptrStoreErase(pos.base()), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::erase(
        iterator first, iterator last)
{
    return iterator(this->ptrStoreErase(first.base(), last.base()), this);
}
#endif

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::find(const_value value)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->ptrStoreFind(value), this);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::const_iterator
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::find(const_value value) const
{
    return const_iterator(this->ptrStoreFind(value),
                          this                     );
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::push_back(const_value value)
{
    this->ptrStoreAppend(value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::resize(size_t      newSize,
                                                const_value value  )
{
    this->ptrStoreResize(newSize, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::reserve(size_type size)
{
    this->_ptrStore.reserve(size);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::clear(void)
{
    this->ptrStoreClear();
}


#ifdef OSG_1_COMPAT
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::addValue(const_value value)
{
    this->ptrStoreAppend(value);
}
#endif


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::assign(size_type   newSize,
                                                const_value value  )
{
    this->ptrStoreClear();

    for(size_type i = 0; i < newSize; ++i)
        this->ptrStoreAppend(value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::assign(InputIteratorT first,
                                                InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::replace(UInt32      uiIdx,
                                                 const_value value)
{
    this->ptrStoreReplace(uiIdx, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::replace(iterator    pos,
                                                 const_value value)
{
    this->ptrStoreReplace(pos.base(), value);
}


/*-------------------------------------------------------------------------*/
/* Index Operator                                                          */

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::reference
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI    >::operator [](const UInt32 index)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reference(this->_ptrStore.begin() + index, this);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename ChildPointerMField<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI  >::const_value
    ChildPointerMField<PtrTypeT,
                       RefCountPolicy,
                       NamespaceI  >::operator [](const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}


#ifdef OSG_MT_CPTR_ASPECT
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void ChildPointerMField<PtrTypeT,
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

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline void
    ChildPointerMField<PtrTypeT,
                               RefCountPolicy,
                       NamespaceI  >::setValues(Self const &source)
{
    this->assign(source.begin(), source.end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline typename ChildPointerMField<PtrTypeT,
                               RefCountPolicy,
                                   NamespaceI  >::Self &
    ChildPointerMField<PtrTypeT,
                               RefCountPolicy,
                       NamespaceI  >::operator=(Self const &source)
{
    this->setValues(source);

    return *this;
}

/*-------------------------------------------------------------------------*/
/* Value Access                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
inline typename ChildPointerMField<PtrTypeT,
                               RefCountPolicy,
                                   NamespaceI  >::ValueStoreType const &
    ChildPointerMField<PtrTypeT,
                               RefCountPolicy,
                       NamespaceI  >::getValues(void) const
{
    return this->template getStore<ValueType>();
}
#endif

OSG_END_NAMESPACE
