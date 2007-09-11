/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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
/*! \file OSGWeakPtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*! \class WeakPtr

The WeakPtr class is used to keep references that should not keep an object from being
deleted. The main use are parent pointers in the graph, but other uses are possible.

*/

// WeakPtr methods

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::WeakPtr(void) :
    _pRef(NullFC)
{
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::WeakPtr(const WeakPtr &weakPtr) :
    _pRef(NullFC)
{
    setRef(weakPtr._pRef);
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::WeakPtr(const SelfRefPtr &refPtr) :
    _pRef(NullFC)
{
    setRef(refPtr.get());
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::WeakPtr(const Ref &pRef) :
    _pRef(NullFC)
{
    setRef(pRef);
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::~WeakPtr(void)
{
    if(_pRef != NullFC)
        _pRef->subWeakReference();
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr>::operator SelfRefPtr(void) const
{
    if(_pRef->getRefCount() <= 0)
        return SelfRefPtr();
        
    return SelfRefPtr(_pRef);
}

template<class ContainerPtr> inline
typename WeakPtr<ContainerPtr>::SelfRefPtr WeakPtr<ContainerPtr>::get(void) const
{
    if(_pRef->getRefCount() <= 0)
        return SelfRefPtr();
        
    return SelfRefPtr(_pRef);
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr> &WeakPtr<ContainerPtr>::operator =(const Ref &pContainer)
{
    setRef(pContainer);

    return *this;
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr> &WeakPtr<ContainerPtr>::operator =(const WeakPtr &weakPtr)
{
    setRef(weakPtr._pRef);

    return *this;
}

template<class ContainerPtr> inline
WeakPtr<ContainerPtr> &WeakPtr<ContainerPtr>::operator =(const SelfRefPtr &refPtr)
{
    setRef(refPtr.get());

    return *this;
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator < (const FieldContainerPtr &other) const
{
    return _pRef < other;
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator ==(const FieldContainerPtr &other) const
{
    return _pRef == other;
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator !=(const FieldContainerPtr &other) const
{
    return !(_pRef == other);
}


template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator < (const WeakPtr<ContainerPtr> &other) const
{
    return _pRef < other._pRef;
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator ==(const WeakPtr<ContainerPtr> &other) const
{
    return _pRef == other._pRef;
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator !=(const WeakPtr<ContainerPtr> &other) const
{
    return !(_pRef == other._pRef);
}

template<class ContainerPtr> inline
bool WeakPtr<ContainerPtr>::operator ! (void) const
{
    return _pRef == NullFC || _pRef->getRefCount() <= 0;
}

template< class ContainerPtr >
WeakPtr<ContainerPtr>::operator 
     typename WeakPtr<ContainerPtr>::unspecified_bool_type (void) const
{
    return  !*this ? 0 : &WeakPtr<Ref>::_ref;
}

template<class ContainerPtr> inline
void WeakPtr<ContainerPtr>::setRef(const Ref &pContainer)
{
    if(_pRef == pContainer)
        return;

    if(pContainer != NullFC)
        pContainer->addWeakReference();
        
    if(_pRef != NullFC)
        _pRef->subWeakReference();
    
    _pRef = pContainer;
}

OSG_END_NAMESPACE
