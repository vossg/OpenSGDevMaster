
#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGPointerMFieldBase.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class PointerMFieldBase

    \brief Base class of all fields that store FieldContainerPtr.
    
    It provides the const parts of the std::vector interface, but the pointers
    returned/accepted by these functions are always pointers to the base
    class FieldContainer, not the derived type.
    To access those as well as for write access one of the derived classes
    has to be used.
 */

/*-------------------------------------------------------------------------*/
/* Constructors                                                            */

inline
    PointerMFieldBase::PointerMFieldBase(void)
    
    : _ptrStore()
{
}

inline
    PointerMFieldBase::PointerMFieldBase(Self const &source)
    
    : _ptrStore(source._ptrStore)
{
}

inline
    PointerMFieldBase::PointerMFieldBase(UInt32 const size)
    
    : _ptrStore(size)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

inline
    PointerMFieldBase::~PointerMFieldBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Std Library Const Interface                                             */

inline PointerMFieldBase::const_iterator
    PointerMFieldBase::begin(void) const
{
    return _ptrStore.begin();
}

inline PointerMFieldBase::const_iterator
    PointerMFieldBase::end(void) const
{
    return _ptrStore.end();
}
    
inline PointerMFieldBase::const_reverse_iterator
    PointerMFieldBase::rbegin(void) const
{
    return _ptrStore.rbegin();
}

inline PointerMFieldBase::const_reverse_iterator
    PointerMFieldBase::rend(void) const
{
    return _ptrStore.rend();
}

inline bool
    PointerMFieldBase::empty(void) const
{
    return _ptrStore.empty();
}

inline PointerMFieldBase::size_type
    PointerMFieldBase::size(void) const
{
    return _ptrStore.size();
}

inline PointerMFieldBase::size_type
    PointerMFieldBase::max_size(void) const
{
    return _ptrStore.max_size();
}

inline PointerMFieldBase::size_type
    PointerMFieldBase::capacity(void) const
{
    return _ptrStore.capacity();
}
    
inline PointerMFieldBase::const_reference
    PointerMFieldBase::operator[](UInt32 const index)
{
    return _ptrStore[index];
}

inline PointerMFieldBase::const_reference
    PointerMFieldBase::at(UInt32 const index)
{
    return _ptrStore.at(index);
}
    
inline PointerMFieldBase::const_reference
    PointerMFieldBase::front(void) const
{
    return _ptrStore.front();
}

inline PointerMFieldBase::const_reference
    PointerMFieldBase::back(void) const
{
    return _ptrStore.back();
}

/*-------------------------------------------------------------------------*/
/* Raw Store Access                                                        */

inline PointerMFieldBase::PtrStoreType &
    PointerMFieldBase::editRawStore(void)
{
    return _ptrStore;
}

inline PointerMFieldBase::PtrStoreType const &
    PointerMFieldBase::getRawStore(void) const
{
    return _ptrStore;
}

/*-------------------------------------------------------------------------*/
/* Cast Store Access                                                       */

template <class TargetStoredTypeT>
inline typename PointerMFieldBase::rebindStore<TargetStoredTypeT>::type &
    PointerMFieldBase::editStore(void)
{
    return
        reinterpret_cast<typename rebindStore<TargetStoredTypeT>::type &>(
            _ptrStore);
}

template <class TargetStoredTypeT>
inline typename PointerMFieldBase::rebindStore<TargetStoredTypeT>::type const &
    PointerMFieldBase::getStore(void) const
{
    return
        reinterpret_cast<typename rebindStore<TargetStoredTypeT>::type const &>(
            _ptrStore);
}

OSG_END_NAMESPACE
