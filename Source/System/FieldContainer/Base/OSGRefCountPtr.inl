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

/*! \class ReferenceCountPointer

    \brief Smart pointer class that manipulates the internal ref count of
    the pointed to object.
*/

OSG_BEGIN_NAMESPACE

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
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(ObjectTransitPtr &other)
{
    RefCountPolicy::convertTransitPtr(_pObj, other._pObj);
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
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(
    ObjectTransitPtr const &other) :

    _pObj(NULL)
{
    RefCountPolicy::convertTransitPtr(_pObj, other._pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(const ObjectPtr pObj) :
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
        const ObjectPtr objectPtr)
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

template <class ObjectT, 
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::operator 
    typename RefCountPtr<ObjectT, RefCountPolicyT>::ObjectPtr (void) const
{
    return RefCountPolicy::validate(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
typename RefCountPtr<ObjectT, RefCountPolicyT>::ObjectPtr 
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
typename RefCountPtr<ObjectT, RefCountPolicyT>::ObjectPtr 
    RefCountPtr<ObjectT, RefCountPolicyT>::get(void) const
{
    return RefCountPolicy::validate(_pObj);
}

template <class ObjectT, 
          class RefCountPolicyT> inline
void RefCountPtr<ObjectT, RefCountPolicyT>::set(const ObjectPtr objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);
}


template <class TargetObjectT, class SourceObjectT, class RP> inline
RefCountPtr<TargetObjectT, RP> dynamic_pointer_cast(
    RefCountPtr<SourceObjectT, RP> const &source)
{
    TargetObjectT *pRet = dynamic_cast<TargetObjectT *>(source.get());

    return RefCountPtr<TargetObjectT, RP>(pRet);
}
 
template <class TargetObjectT, class SourceObjectT, class RP> inline
RefCountPtr<TargetObjectT, RP> static_pointer_cast(
    RefCountPtr<SourceObjectT, RP> const &source)
{
    TargetObjectT *pRet = static_cast<TargetObjectT *>(source.get());

    return RefCountPtr<TargetObjectT, RP>(pRet);
}
  
OSG_END_NAMESPACE
