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

OSG_BEGIN_NAMESPACE

/*! \class MemObjPointerMFieldBase

    \brief Base class of all fields that store MemoryObjectPtr.
    
    It provides the const parts of the std::vector interface, but the pointers
    returned/accepted by these functions are always pointers to the base
    class MemoryObject, not the derived type.
    To access those as well as for write access one of the derived classes
    has to be used.
 */


inline
SizeT MemObjPointerMFieldBase::getBinSize(void) const
{
    return 
        sizeof(UInt32) + // num elements
        (_ptrStore.size() ? 
         MFieldTraits::getBinSize(&(_ptrStore[0]), _ptrStore.size()) : 0);
}


inline
void MemObjPointerMFieldBase::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = UInt32(_ptrStore.size());

    pMem.putValue(n);

    if(n != 0)
    {
        MFieldTraits::copyToBin(   pMem, 
                                &(_ptrStore[0]),
                                  _ptrStore.size());
    }
}

/*-------------------------------------------------------------------------*/
/* Std Library Const Interface                                             */

inline 
MemObjPointerMFieldBase::const_iterator 
    MemObjPointerMFieldBase::begin(void) const
{
    return _ptrStore.begin();
}

inline 
MemObjPointerMFieldBase::const_iterator MemObjPointerMFieldBase::end(void) const
{
    return _ptrStore.end();
}
    
inline 
MemObjPointerMFieldBase::const_reverse_iterator 
    MemObjPointerMFieldBase::rbegin(void) const
{
    return _ptrStore.rbegin();
}

inline 
MemObjPointerMFieldBase::const_reverse_iterator 
    MemObjPointerMFieldBase::rend(void) const
{
    return _ptrStore.rend();
}

inline 
MemObjPointerMFieldBase::value_type MemObjPointerMFieldBase::front(void) const
{
    return _ptrStore.front();
}

inline 
MemObjPointerMFieldBase::value_type MemObjPointerMFieldBase::back(void) const
{
    return _ptrStore.back();
}

inline 
bool MemObjPointerMFieldBase::empty(void) const
{
    return _ptrStore.empty();
}

inline 
MemObjPointerMFieldBase::size_type MemObjPointerMFieldBase::size(void) const
{
    return _ptrStore.size();
}

inline 
MemObjPointerMFieldBase::size_type MemObjPointerMFieldBase::max_size(void) const
{
    return _ptrStore.max_size();
}

inline 
MemObjPointerMFieldBase::size_type MemObjPointerMFieldBase::capacity(void) const
{
    return _ptrStore.capacity();
}
    
inline
MemObjPointerMFieldBase::difference_type 
    MemObjPointerMFieldBase::findIndex(const_value value) const
{
    const_iterator it = std::find(_ptrStore.begin(), _ptrStore.end(), value);

    if(it != _ptrStore.end())
    {
        return it - _ptrStore.begin();
    }
    else
    {
        return -1;
    }
}

inline 
void MemObjPointerMFieldBase::reserve(size_type size)
{
    return _ptrStore.reserve(size);
}

inline 
MemObjPointerMFieldBase::value_type 
    MemObjPointerMFieldBase::operator[](size_type const index) const
{
    return _ptrStore[index];
}

inline 
MemObjPointerMFieldBase::value_type 
    MemObjPointerMFieldBase::at(size_type const index) const
{
    return _ptrStore.at(index);
}
    
inline
bool MemObjPointerMFieldBase::operator ==(const Self &source) const
{
    return _ptrStore == source._ptrStore;
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MemObjPointerMFieldBase::beginEdit(UInt32              ,
                                        AspectOffsetStore  &)
{
}

inline
MemObjPointerMFieldBase::Self *
    MemObjPointerMFieldBase::resolveShare(UInt32              , 
                                          AspectOffsetStore  &)
{
    return NULL;
}

inline
void MemObjPointerMFieldBase::terminateShare(UInt32              , 
                                             AspectOffsetStore  &)
{
    
}

inline
bool MemObjPointerMFieldBase::isShared(void)
{
    return false;
}
#endif

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

inline
MemObjPointerMFieldBase::MemObjPointerMFieldBase(void) :
     Inherited(),
    _ptrStore ()
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

inline
MemObjPointerMFieldBase::~MemObjPointerMFieldBase(void)
{
}


/*-------------------------------------------------------------------------*/
/* Raw Store Access                                                        */

inline 
MemObjPointerMFieldBase::StorageType &
    MemObjPointerMFieldBase::editRawStore(void)
{
    return _ptrStore;
}

inline 
MemObjPointerMFieldBase::StorageType const &
    MemObjPointerMFieldBase::getRawStore(void) const
{
    return _ptrStore;
}

/*-------------------------------------------------------------------------*/
/* Cast Store Access                                                       */

template <class TargetStoredTypeT> inline 
typename MemObjPointerMFieldBase::rebindStore<TargetStoredTypeT>::type &
    MemObjPointerMFieldBase::editStore(void)
{
    return
        reinterpret_cast<typename rebindStore<TargetStoredTypeT>::type &>(
            _ptrStore);
}

template <class TargetStoredTypeT> inline 
typename MemObjPointerMFieldBase::rebindStore<TargetStoredTypeT>::type const &
    MemObjPointerMFieldBase::getStore(void) const
{
    return
        reinterpret_cast<typename rebindStore<TargetStoredTypeT>::type const &>(
            _ptrStore);
}

OSG_END_NAMESPACE
