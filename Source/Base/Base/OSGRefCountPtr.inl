/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2007 by OpenSG Forum                      *
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

/*! \class RefCountPtr

    \brief Smart pointer class that manipulates the internal ref count of
    the pointed to object.
*/

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(void) :
    _pObj(NULL)
{
}

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(Self const &other) :
    _pObj(NULL)
{
    RefCountPolicy::setRefd(_pObj, RefCountPolicy::validate(other._pObj));
}

template <class ObjectT, 
          class RefCountPolicyT>
template <class OtherObjectT   > inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(
    TransitPtr<OtherObjectT> const &other) :

    _pObj(NULL)
{
    RefCountPolicy::convertTransitPtr(_pObj, other._pObj);
}

template <class ObjectT,
          class RefCountPolicyT     >
template <class OtherObjectT,
          class OtherRefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(
    RefCountPtr<OtherObjectT, OtherRefCountPolicyT> const &other) :
    
    _pObj(NULL)
{
    ObjectT *pOther = other.get();

    RefCountPolicyT::addRef(pOther);

    _pObj = pOther;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(
    ObjectTransitPtr const &other) :

    _pObj(NULL)
{
    RefCountPolicy::convertTransitPtr(_pObj, other._pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(Object * const pObj) :
    _pObj(NULL)
{
    RefCountPolicy::setRefd(_pObj, pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::~RefCountPtr(void)
{
    RefCountPolicy::subRef(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Self &
    RefCountPtr<ObjectT, RefCountPolicyT>::operator =(Self const &other)
{
    ObjectT *pOther = RefCountPolicy::validate(other._pObj);

    if(_pObj != pOther)
        RefCountPolicy::setRefd(_pObj, pOther);

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Self &
    RefCountPtr<ObjectT, RefCountPolicyT>::operator =(
        Object * const objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Self &
    RefCountPtr<ObjectT, RefCountPolicyT>::operator =(
        const ObjectTransitPtr &other)
{
    RefCountPolicy::convertTransitPtr(_pObj, other._pObj);

    return *this;
}

template <class ObjectT, 
          class RefCountPolicyT> 
template <class OtherObjectT, 
          class OtherRefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Self &
    RefCountPtr<ObjectT, RefCountPolicyT>::operator =(
        RefCountPtr<OtherObjectT,
                    OtherRefCountPolicyT> const &refPtr)
{
    ObjectT *pOther = refPtr.get();

    if(_pObj != pOther)
    {
        RefCountPolicyT::addRef( pOther);
        RefCountPolicyT::subRef(_pObj  );

        _pObj = pOther;
    }

    return *this;
}

#ifndef OSG_DOXYGEN_IGNORE_RECOG_PROBS
template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::operator 
    typename RefCountPtr<ObjectT, RefCountPolicyT>::Object *(void) const
{
    return RefCountPolicy::validate(_pObj);
}
#endif

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Object * 
    RefCountPtr<ObjectT, RefCountPolicyT>::operator->(void) const
{
    return RefCountPolicy::validate(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Object &
    RefCountPtr<ObjectT, RefCountPolicyT>::operator *(void) const
{
    return RefCountPolicy::dereference(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Object * 
    RefCountPtr<ObjectT, RefCountPolicyT>::get(void) const
{
    return RefCountPolicy::validate(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
void RefCountPtr<ObjectT, RefCountPolicyT>::set(Object * const objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);
}

#if defined(OSG_1_COMPAT)
template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(const NullFCType) :
    _pObj(NULL)
{
}

template <class ObjectT, 
          class RefCountPolicyT> inline
bool RefCountPtr<ObjectT, RefCountPolicyT>::operator ==(const NullFCType) const
{
    return RefCountPolicy::validate(_pObj) == NULL;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
bool RefCountPtr<ObjectT, RefCountPolicyT>::operator !=(const NullFCType) const
{
    return RefCountPolicy::validate(_pObj) != NULL;
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Object *
    RefCountPtr<ObjectT, RefCountPolicyT>::getCPtr(void) const
{
    return RefCountPolicy::validate(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::Self    
    RefCountPtr<ObjectT, RefCountPolicyT>::dcast(FieldContainer * const src)
{
    Object *pRet = dynamic_cast<Object *>(src);

    return Self(pRet);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
Int32 RefCountPtr<ObjectT, RefCountPolicyT>::getRefCount(void) const
{
    if(_pObj != NULL)
    {
        return _pObj->getRefCount();
    }
    else
    {
        return -1;
    }
}

#endif


template <class TargetObjectT, class SourceObjectT, class RP> inline
OSG::RefCountPtr<TargetObjectT, RP> dynamic_pointer_cast(
    OSG::RefCountPtr<SourceObjectT, RP> const &source)
{
    TargetObjectT *pRet = dynamic_cast<TargetObjectT *>(source.get());

    return RefCountPtr<TargetObjectT, RP>(pRet);
}
 
template <class TargetObjectT, class SourceObjectT, class RP> inline
OSG::RefCountPtr<TargetObjectT, RP> static_pointer_cast(
    OSG::RefCountPtr<SourceObjectT, RP> const &source)
{
    TargetObjectT *pRet = static_cast<TargetObjectT *>(source.get());

    return RefCountPtr<TargetObjectT, RP>(pRet);
}

template <class ObjectT, class RefCountPolicyT> inline
ObjectT *get_pointer(const OSG::RefCountPtr<ObjectT, RefCountPolicyT> &refPtr)
{
    return refPtr.get();
}

#if defined(OSG_1_COMPATX)
template <class TargetT, class SourceT> inline
RefCountPtr<typename TargetT::Object, 
            typename TargetT::RefCountPolicy> dynamic_pointer_cast(
                SourceT * const pIn)
{
    typename TargetT::Object *pRet = 
        dynamic_cast<typename TargetT::Object *>(pIn);

    return RefCountPtr<typename TargetT::Object, 
                       typename TargetT::RefCountPolicy>(pRet);
}
#endif

#ifdef OSG_1_COMPAT
template <class ObjectT, class RefCountPolicyT> inline
ObjectT *getCPtr(const OSG::RefCountPtr<ObjectT, RefCountPolicyT> &refPtr)
{
    return refPtr.getCPtr();
}
#endif
  
OSG_END_NAMESPACE
