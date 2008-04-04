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
          class RefCountPolicyT> inline
RefCountPtr<ObjectT, RefCountPolicyT>::RefCountPtr(ObjectPtrConstArg pObj) :
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
        ObjectPtrConstArg objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);

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
RefCountPtr<ObjectT, RefCountPolicyT>::operator ObjectPtr (void) const
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
void RefCountPtr<ObjectT, RefCountPolicyT>::set(ObjectPtrConstArg objectPtr)
{
    if(_pObj != objectPtr)
        RefCountPolicy::setRefd(_pObj, objectPtr);
}

OSG_END_NAMESPACE
