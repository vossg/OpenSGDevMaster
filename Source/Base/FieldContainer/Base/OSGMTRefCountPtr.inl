/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2009 by OpenSG Forum                      *
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

/*! \class MTRefCountPtr

  \brief Smart pointer class that manipulates the internal ref count of
  the pointed-to object.
  When dereferencing an MTRefCountPtr it returns a pointer to the correct
  aspect copy of the pointer-to object for the current thread.
*/

template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(void)
    : _pAspectStore(NULL)
{
}

template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(Self const &other)
    : _pAspectStore(NULL)
{
    RefCountPolicy::addRef(other.get());

    _pAspectStore = other._pAspectStore;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(Object * const otherObj)
    : _pAspectStore(NULL)
{
    ObjectT *pOtherObj = RefCountPolicy::validate(otherObj);

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::addRef(pOtherObjAspect);

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SFATAL << "MTRefCountPtr<>::c'tor : Construction from different "
                   << "aspect attempted." << std::endl;
        }
    }
}

template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(
    ObjectTransitPtr const &other) 

    : _pAspectStore(NULL)
{
    ObjectT *pOtherObj = RefCountPolicy::validate(other._pObj);
    ObjectT *pObj      = NULL;

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::convertTransitPtr(pObj, other._pObj);

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SFATAL << "MTRefCountPtr<>::c'tor : Construction from different "
                   << "aspect attempted." << std::endl;
        }
    }
}

template <class ObjectT, 
          class RefCountPolicyT>
template <class OtherObjectT   > inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(
    TransitPtr<OtherObjectT> const &other)

    : _pAspectStore(NULL)
{
    ObjectT *pOtherObj = RefCountPolicy::validate(other._pObj);
    ObjectT *pObj      = NULL;

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::convertTransitPtr(pObj, other._pObj);

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
    }
}

template <class ObjectT,
          class RefCountPolicyT     >
template <class OtherObjectT,
          class OtherRefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(
    MTRefCountPtr<OtherObjectT, OtherRefCountPolicyT> const &refPtr)
    
    : _pAspectStore(NULL)
{
    // make sure types are compatible
    ObjectT *pOtherObj = RefCountPolicy::validate(refPtr.get());

    if(pOtherObj != NULL)
    {
        RefCountPolicy::addRef(pOtherObj);

        _pAspectStore = refPtr._pAspectStore;
    }
}

template <class ObjectT,
          class RefCountPolicyT     >
template <class OtherObjectT,
          class OtherRefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(
    RefCountPtr<OtherObjectT, OtherRefCountPolicyT> const &refPtr)

    : _pAspectStore(NULL)
{
    // make sure types are compatible
    ObjectT *pOtherObj = RefCountPolicy::validate(refPtr.get());

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::addRef(pOtherObjAspect);

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SFATAL << "MTRefCountPtr<>::c'tor : Construction from different "
                   << "aspect attempted." << std::endl;
        }
    }
}

template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::~MTRefCountPtr(void)
{
    // for non-counting the pointer can outlive the object
    // so we need to avoid accessing the already deleted
    // AspectStore

    if(RefCountPolicy::NotCounting == false)
        RefCountPolicy::subRef(this->get());
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator =(Self const &other)
{
    if(this == &other)
        return *this;

    ObjectT *pOtherObj = other .get();
    ObjectT *pObj      = this ->get();

    RefCountPolicy::addRef(pOtherObj);
    RefCountPolicy::subRef(pObj     );

    _pAspectStore = other._pAspectStore;

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator =(
    Object * const otherObj)
{
    ObjectT *pOtherObj = RefCountPolicy::validate(otherObj);
    ObjectT *pObj      = this->get();

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::addRef(pOtherObjAspect);
            RefCountPolicy::subRef(pObj           );

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SWARNING << "MTRefCountPtr<>::operator = : Assignment from "
                     << "different aspect attempted." << std::endl;
        }
    }
    else
    {
        RefCountPolicy::subRef(pObj);
        _pAspectStore = NULL;
    }

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator =(
    const ObjectTransitPtr &other)
{
    ObjectT *pOtherObj = RefCountPolicy::validate(other._pObj);
    ObjectT *pObj      = this->get();

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::convertTransitPtr(pObj, other._pObj);
            
            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SWARNING << "MTRefCountPtr<>::operator = : Assignment from "
                     << "different aspect attempted." << std::endl;
        }
    }
    else
    {
        RefCountPolicy::subRef(pObj);
        _pAspectStore = NULL;
    }

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT     > 
template <class OtherObjectT, 
          class OtherRefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator =(
    const MTRefCountPtr<OtherObjectT,
                        OtherRefCountPolicyT> &refPtr)
{
    // make sure types are compatible
    ObjectT *pOtherObj = RefCountPolicy::validate(refPtr.get());
    ObjectT *pObj      = this->get();

    if(pOtherObj != NULL)
    {
        RefCountPolicy::addRef(pOtherObj);
        RefCountPolicy::subRef(pObj     );

        _pAspectStore = pOtherObj->getAspectStore();
    }
    else
    {
        RefCountPolicy::subRef(pObj);
        _pAspectStore = NULL;
    }
}

template <class ObjectT, 
          class RefCountPolicyT     > 
template <class OtherObjectT, 
          class OtherRefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator =(
    RefCountPtr<OtherObjectT,
                OtherRefCountPolicyT> const &refPtr)
{
    // make sure types are compatible
    ObjectT *pOtherObj = RefCountPolicy::validate(refPtr.get());
    ObjectT *pObj      = this->get();

    if(pOtherObj != NULL)
    {
        ObjectT *pOtherObjAspect = convertToCurrentAspect(pOtherObj);

        // check for cross aspect assignment
        if(pOtherObjAspect == pOtherObj)
        {
            RefCountPolicy::addRef(pOtherObjAspect);
            RefCountPolicy::subRef(pObj           );

            _pAspectStore = pOtherObjAspect->getAspectStore();
        }
        else
        {
            SFATAL << "MTRefCountPtr<>::c'tor : Construction from different "
                   << "aspect attempted." << std::endl;
        }
    }
    else
    {
        RefCountPolicy::subRef(pObj);
        _pAspectStore = NULL;
    }

    return *this;
}

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator 
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Object *(void) const
{
    return this->get();
}
#endif

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Object * 
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator->(void) const
{
    return this->get();
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Object &
MTRefCountPtr<ObjectT, RefCountPolicyT>::operator *(void) const
{
    return RefCountPolicy::dereference(this->get());
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Object * 
MTRefCountPtr<ObjectT, RefCountPolicyT>::get(void) const
{
    ObjectT *pObj = NULL;

    if(_pAspectStore != NULL)
    {
        pObj = static_cast<ObjectT *>(_pAspectStore->getPtr());
        pObj = RefCountPolicy::validate(pObj);
    }
    
    return pObj;
}

#if 0 // NEEDED ?
template <class ObjectT, 
          class RefCountPolicyT> inline
void MTRefCountPtr<ObjectT, RefCountPolicyT>::set(Object * const objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);
}
#endif

template <class ObjectT, 
          class RefCountPolicyT> inline
void MTRefCountPtr<ObjectT, RefCountPolicyT>::shutdownSetNull(void)
{
    if(_pAspectStore != NULL)
    {
        UInt32 uiSize = _pAspectStore->getNumAspects();

        for(UInt32 i = 0; i < uiSize; ++i)
        {
            if(_pAspectStore->getPtr(i) != NULL)
            {
                RefCountPolicy::subRef(_pAspectStore->getPtr(i));
            }
        }

        _pAspectStore = NULL;
    }    
}

#if defined(OSG_1_COMPAT)
template <class ObjectT, 
          class RefCountPolicyT> inline
MTRefCountPtr<ObjectT, RefCountPolicyT>::MTRefCountPtr(const NullFCType)
    : _pAspectStore(NULL)
{
}

template <class ObjectT, 
          class RefCountPolicyT> inline
bool MTRefCountPtr<ObjectT, RefCountPolicyT>::operator ==(const NullFCType) const
{
    return (this->get() == NULL);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
bool MTRefCountPtr<ObjectT, RefCountPolicyT>::operator !=(const NullFCType) const
{
    return (this->get() != NULL);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Object *
MTRefCountPtr<ObjectT, RefCountPolicyT>::getCPtr(void) const
{
    return this->get();
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename MTRefCountPtr<ObjectT, RefCountPolicyT>::Self    
MTRefCountPtr<ObjectT, RefCountPolicyT>::dcast(FieldContainer * const src)
{
    ObjectT *pRet = dynamic_cast<ObjectT *>(src);

    return Self(pRet);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
Int32 MTRefCountPtr<ObjectT, RefCountPolicyT>::getRefCount(void) const
{
    ObjectT *pObj = this->get();

    if(pObj != NULL)
    {
        return pObj->getRefCount();
    }
    else
    {
        return -1;
    }
}

#endif // defined(OSG_1_COMPAT)


template <class TargetT, class SourceT, class RCPolicyT> inline
OSG::MTRefCountPtr<TargetT, RCPolicyT> dynamic_pointer_cast(
    OSG::MTRefCountPtr<SourceT, RCPolicyT> const &source)
{
    TargetT *pRet = dynamic_cast<TargetT *>(source.get());

    return MTRefCountPtr<TargetT, RCPolicyT>(pRet);
}
 
template <class TargetT, class SourceT, class RCPolicyT> inline
OSG::MTRefCountPtr<TargetT, RCPolicyT> static_pointer_cast(
    OSG::MTRefCountPtr<SourceT, RCPolicyT> const &source)
{
    TargetT *pRet = static_cast<TargetT *>(source.get());

    return MTRefCountPtr<TargetT, RCPolicyT>(pRet);
}

template <class ObjectT, class RCPolicyT> inline
ObjectT *get_pointer(const OSG::MTRefCountPtr<ObjectT, RCPolicyT> &refPtr)
{
    return refPtr.get();
}

#if defined(OSG_1_COMPATX)
template <class TargetT, class SourceT> inline
MTRefCountPtr<typename TargetT::Object, 
              typename TargetT::RefCountPolicy> dynamic_pointer_cast(
    SourceT * const pIn)
{
    typename TargetT::Object *pRet = 
        dynamic_cast<typename TargetT::Object *>(pIn);

    return MTRefCountPtr<typename TargetT::Object, 
        typename TargetT::RefCountPolicy>(pRet);
}
#endif // defined(OSG_1_COMPATX)
  
OSG_END_NAMESPACE
