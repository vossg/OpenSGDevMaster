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
/* MemObjPointerMFieldIterator<PtrTypeT>                                   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldIterator<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::MemObjPointerMFieldIterator(void) :
     Inherited(    ),
    _pField   (NULL)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldIterator<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::MemObjPointerMFieldIterator(
                                const Self &source) :
     Inherited(source        ),
    _pField   (source._pField)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldIterator<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::MemObjPointerMFieldIterator(
                                const PtrStoreItType &storeIter,
                                      MFieldType     *pField) :
     Inherited(storeIter),
    _pField   (pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldIterator<PtrTypeT,
                            RefCountPolicy,
                            NamespaceI    >::~MemObjPointerMFieldIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::reference
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator *(void) const
{
    return reference(*this, _pField);
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::reference
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI>::operator [](
                                    const difference_type offset) const
{
    return reference(*this + offset, _pField);
}
#else
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::const_value
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::const_value
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI>::operator [](
                                    const difference_type offset) const
{
    return *(*this + offset);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self &
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator ++(void)
{
    this->Inherited::operator++();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator ++(int)
{
    Self retVal = *this;

    this->Inherited::operator++();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self &
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator --(void)
{
    this->Inherited::operator--();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator --(int)
{
    Self retVal = *this;

    this->Inherited::operator--();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self &
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator +=(
                                    const difference_type offset)
{
    this->Inherited::operator+=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator +(
                                    const difference_type offset) const
{
    Self retVal = *this;

    return retVal += offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self &
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator -=(
                                    const difference_type offset)
{
    this->Inherited::operator-=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::Self
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::operator - (
                                    const difference_type offset) const
{
    Self retVal = *this;

    return retVal -= offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldIterator<PtrTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator ==(
                                     const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldIterator<PtrTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator !=(
                                     const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldIterator<PtrTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator ==(
                                     const const_iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldIterator<PtrTypeT,
                                 RefCountPolicy,
                                 NamespaceI    >::operator !=(
                                     const const_iterator &rhs) const
{
    return ! (*this == rhs);
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
const typename MemObjPointerMFieldIterator<PtrTypeT,
                                           RefCountPolicy,
                                           NamespaceI    >::PtrStoreItType &
    MemObjPointerMFieldIterator<PtrTypeT,
                                RefCountPolicy,
                                NamespaceI    >::base(void) const
{
    return *this;
}

/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
typename MemObjPointerMFieldIterator<PtrTypeT,
                                     RefCountPolicyT,
                                     NamespaceI      >::difference_type
    operator-(MemObjPointerMFieldIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      > const &lhs,
              MemObjPointerMFieldIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
MemObjPointerMFieldIterator<PtrTypeT,
                            RefCountPolicyT,
                            NamespaceI      >
    operator+(typename MemObjPointerMFieldIterator<PtrTypeT,
                                                   RefCountPolicyT,
                                                   NamespaceI      >::differece_type const offset,
              MemObjPointerMFieldIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      >                          const &rhs   )
{
    return MemObjPointerMFieldIterator<PtrTypeT,
                                       RefCountPolicyT,
                                       NamespaceI      >(rhs) += offset;
}


/*-------------------------------------------------------------------------*/
/* MemObjPointerMFieldConstIterator<PtrTypeT>                              */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldConstIterator(void) :

    Inherited()
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldConstIterator(
              const Self &source) :

    Inherited(source)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldConstIterator(
              const iterator &fieldIter) :

    Inherited(fieldIter.base())
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldConstIterator(
              const PtrStoreConstItType &storeIter) :

    Inherited(storeIter)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::~MemObjPointerMFieldConstIterator(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::const_value
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator *(void) const
{
    return static_cast<const_value>(
        AccessHandler::validate(this->Inherited::operator*()));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI   >::const_value
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator [](
        const difference_type offset) const
{
    return *(*this + offset);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self &
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator ++(void)
{
    this->Inherited::operator++();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator ++(int)
{
    Self retVal = *this;

    this->Inherited::operator++();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self &
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator --(void)
{
    this->Inherited::operator--();

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator --(int)
{
    Self retVal = *this;

    this->Inherited::oprator--();

    return retVal;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self &
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator +=(
                                         const difference_type offset)
{
    this->Inherited::operator+=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator +(
                                         const difference_type offset) const
{
    Self retVal = *this;

    return retVal += offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self &
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator -=(
                                         const difference_type offset)
{
    this->Inherited::operator-=(offset);

    return *this;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicy,
                                          NamespaceI    >::Self
    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::operator -(
                                         const difference_type offset) const
{
    Self retVal = *this;

    return retVal -= offset;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldConstIterator<PtrTypeT,
                                      RefCountPolicy,
                                      NamespaceI    >::operator ==(
                                          const Self &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldConstIterator<PtrTypeT,
                                      RefCountPolicy,
                                      NamespaceI    >::operator !=(
                                          const Self &rhs) const
{
    return ! (*this == rhs);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldConstIterator<PtrTypeT,
                                      RefCountPolicy,
                                      NamespaceI    >::operator ==(
                                          const iterator &rhs) const
{
    return *(static_cast<const Inherited *>(this)) == rhs;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
bool MemObjPointerMFieldConstIterator<PtrTypeT,
                                      RefCountPolicy,
                                      NamespaceI    >::operator !=(
                                          const iterator &rhs) const
{
    return ! (*this == rhs);
}

/*-------------------------------------------------------------------------*/
/* Base                                                                    */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
const typename MemObjPointerMFieldConstIterator<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::PtrStoreConstItType &

    MemObjPointerMFieldConstIterator<PtrTypeT,
                                     RefCountPolicy,
                                     NamespaceI    >::base(void) const
{
    return *this;
}


/*-------------------------------------------------------------------------*/
/* Free Functions                                                          */

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      >::difference_type
    operator-(MemObjPointerMFieldConstIterator<PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &lhs,
              MemObjPointerMFieldConstIterator<PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      >::difference_type
    operator-(MemObjPointerMFieldIterator     <PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &lhs,
              MemObjPointerMFieldConstIterator<PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                          RefCountPolicyT,
                                          NamespaceI      >::difference_type
    operator-(MemObjPointerMFieldConstIterator<PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &lhs,
              MemObjPointerMFieldIterator     <PtrTypeT,
                                               RefCountPolicyT,
                                               NamespaceI      > const &rhs )
{
    return (lhs.base() - rhs.base());
}

template <class PtrTypeT, typename RefCountPolicyT, Int32 NamespaceI>
MemObjPointerMFieldConstIterator<PtrTypeT,
                                 RefCountPolicyT,
                                 NamespaceI      >
    operator+(typename MemObjPointerMFieldConstIterator<PtrTypeT,
                                                        RefCountPolicyT,
                                                        NamespaceI       >::difference_type const offset,
              MemObjPointerMFieldConstIterator         <PtrTypeT,
                                                        RefCountPolicyT,
                                                        NamespaceI       >                  const &rhs   )
{
    return MemObjPointerMFieldConstIterator<PtrTypeT,
                                            RefCountPolicyT,
                                            NamespaceI      >(rhs) += offset;
}


/*-------------------------------------------------------------------------*/
/* MemObjPointerMFieldReferenceProxy<PtrTypeT>                             */
/*-------------------------------------------------------------------------*/

#ifndef OSG_CLEAN_FCFIELDS
/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldReferenceProxy<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldReferenceProxy(
              const PtrStoreItType &storeIter,
              MFieldType     *pField   ) :

    _storeIter(storeIter),
    _pField   (pField   )
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldReferenceProxy<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::MemObjPointerMFieldReferenceProxy(
              const Self &source) :

    _storeIter(source._storeIter),
    _pField   (source._pField   )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldReferenceProxy<
          PtrTypeT,
          RefCountPolicy,
          NamespaceI    >::~MemObjPointerMFieldReferenceProxy(void)
{
}

/*-------------------------------------------------------------------------*/
/* Operators                                                               */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMFieldReferenceProxy<PtrTypeT,
                                  RefCountPolicy,
                                  NamespaceI    >::operator
#if defined(_MSC_VER) && _MSC_VER < 1400
typename MemObjPointerMFieldReferenceProxy<PtrTypeT,
                                           RefCountPolicy,
                                           NamespaceI    >::
#endif
                                                      value_type(void) const
{
    return static_cast<value_type>(AccessHandler::validate(*_storeIter));
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMFieldReferenceProxy<PtrTypeT,
                                           RefCountPolicy,
                                           NamespaceI    >::value_type
     MemObjPointerMFieldReferenceProxy<PtrTypeT,
                                       RefCountPolicy,
                                       NamespaceI    >::operator->(void) const
{
    return static_cast<value_type>(AccessHandler::validate(*_storeIter));
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMFieldReferenceProxy<PtrTypeT,
                                       RefCountPolicy,
                                       NamespaceI    >::operator=(
                                           value_type newValue)
{
    AccessHandler::onReplace(_pField, *_storeIter, newValue);

    *_storeIter = newValue;
}

#endif

/*-------------------------------------------------------------------------*/
/* MemObjPointerPointerMField<PtrTypeT,                                    */
/*                            NamespaceI  >                                */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Class Type                                                              */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::MemObjPointerMField(void) :
    Inherited()
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::MemObjPointerMField(Self const &other) :
    Inherited(other)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::MemObjPointerMField(UInt32 const size) :
    Inherited(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
MemObjPointerMField<PtrTypeT,
                    RefCountPolicy,
                    NamespaceI    >::~MemObjPointerMField(void)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::copyFromBin(BinaryDataHandler &pMem)
{
    Inherited::copyFromBin(pMem);
}



template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin_nc(void)
{
    return iterator(this->_ptrStore.begin(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end_nc(void)
{
    return iterator(this->_ptrStore.end(), this);
}

#ifndef OSG_CLEAN_FCFIELDS
#if 0
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reference
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::front_nc(void)
{
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reference back_nc (void);
#endif
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find_nc(const_value value)
{
    return iterator(this->ptrStoreFind(value),
                    this                     );
}

/*-------------------------------------------------------------------------*/
/* Std Library Interface                                                   */

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->_ptrStore.begin(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->_ptrStore.end(), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reverse_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rbegin(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reverse_iterator
    MemObjPointerMField<PtrTypeT,
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
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::begin(void) const
{
    return const_iterator(this->_ptrStore.begin());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::end(void) const
{
    return const_iterator(this->_ptrStore.end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_reverse_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rbegin(void) const
{
    return const_reverse_iterator(this->end());
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_reverse_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::rend(void) const
{
    return const_reverse_iterator(this->begin());
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reference
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::front(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reference(this->_ptrStore.begin(), this);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::front(void) const
{
    return static_cast<const_value>(this->ptrStoreGet(this->_ptrStore.begin()));
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reference
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::back(void)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return reference(this->_ptrStore.end() - 1, this);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::back(void) const
{
    return static_cast<const_value>(
        this->ptrStoreGet(this->_ptrStore.end() - 1));
}


template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI  >::insert(iterator pos, const_value value)
{
    return iterator(this->ptrStoreInsert(pos.base(), value), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI     >::insert(iterator    pos,
                                                  size_type   n,
                                                  const_value value)
{
    this->ptrStoreInsert(pos, n, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI>
template <class InputIteratorT                                        > inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::insert(iterator       pos,
                                                 InputIteratorT first,
                                                 InputIteratorT last)
{
    this->ptrStoreInsert(pos, first, last);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::erase(size_type index)
{
    return this->ptrStoreErase(index);
}

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                  RefCountPolicy,
                  NamespaceI    >::erase(iterator pos)
{
    return iterator(this->ptrStoreErase(pos.base()), this);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::erase(iterator first, iterator last)
{
    return iterator(this->ptrStoreErase(first.base(), last.base()), this);
}
#endif

#ifndef OSG_CLEAN_FCFIELDS
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find(const_value value)
{
#ifdef OSG_CHECK_CONST_CORRECT_FIELD_USAGE
    BOOST_STATIC_ASSERT(sizeof(PtrTypeT) == 0);
#endif

    return iterator(this->ptrStoreFind(value),
                    this                     );
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_iterator
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::find(const_value value) const
{
    return const_iterator(this->ptrStoreFind(value),
                          this                     );
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::push_back(const_value value)
{
    this->ptrStoreAppend(value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::resize(size_t      newSize, 
                                                 const_value value  )
{
    this->ptrStoreResize(newSize, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::reserve(size_type size)
{
    this->_ptrStore.reserve(size);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::clear(void)
{
    this->ptrStoreClear();
}

#ifdef OSG_1_COMPAT
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::addValue(const_value value)
{
    this->push_back(value);
}
#endif

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
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
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::assign(InputIteratorT first,
                                                 InputIteratorT last)
{
    this->ptrStoreAssign(first, last);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::replace(UInt32      uiIdx,
                                                  const_value value)
{
    this->ptrStoreReplace(uiIdx, value);
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
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
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::reference
    MemObjPointerMField<PtrTypeT,
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
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::const_value
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::operator [](const UInt32 index) const
{
    return static_cast<const_value>(this->ptrStoreGet(index));
}

/*-------------------------------------------------------------------------*/
/* Assignment                                                              */

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
typename MemObjPointerMField<PtrTypeT,
                             RefCountPolicy,
                             NamespaceI    >::Self &
    MemObjPointerMField<PtrTypeT,
                        RefCountPolicy,
                        NamespaceI    >::operator=(const Self &source)
{
//    this->setValues(source);

    OSG_ASSERT(false);

    return *this;
}


#ifdef OSG_MT_CPTR_ASPECT
template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
void MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::syncWith(
                             Self               &source,
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

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
FieldDescriptionBase *
    MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::createFieldDescription   (
                             const Char8                *szFieldname,
                                   UInt32                uiFieldFlags,
                                   FieldEditMethod       fEditMethod,
                                   FieldGetMethod        fGetMethod  )
{
    return NULL;
}

template <class PtrTypeT, typename RefCountPolicy, Int32 NamespaceI> inline
FieldDescriptionBase *
    MemObjPointerMField<PtrTypeT,
                         RefCountPolicy,
                         NamespaceI    >::createIdxFieldDescription(
                             const Char8                *szFieldname,
                                   UInt32                uiFieldFlags,
                                   FieldIndexEditMethod  fEditMethod,
                                   FieldIndexGetMethod   fGetMethod  )
{
    return NULL;
}
    

OSG_END_NAMESPACE
