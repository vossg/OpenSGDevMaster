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
/*! \file OSGRefPtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

// RefPtr methods

template<class ContainerPtr> inline
RefPtr<ContainerPtr>::RefPtr(void) :
    _pRef(NullFC)
{
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr>::RefPtr(const Ref &pRef) :
    _pRef(NullFC)
{
    setRefd(_pRef, pRef);
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr>::RefPtr(const RefPtr &refPtr) :
    _pRef(NullFC)
{
    setRefd(_pRef, refPtr._pRef);
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr>::~RefPtr(void)
{
    subRef(_pRef);
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr>::operator ContainerPtr(void) const
{
    return _pRef;
}

template<class ContainerPtr> inline
typename 
PtrStripper<ContainerPtr>::Object *RefPtr<ContainerPtr>::operator->(void) const
{
    return &(*_pRef);
}

template<class ContainerPtr> inline
typename RefPtr<ContainerPtr>::Ref RefPtr<ContainerPtr>::get(void) const
{
    return _pRef;
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr> &RefPtr<ContainerPtr>::operator =(const Ref &pContainer)
{
    setRef(pContainer);

    return *this;
}

template<class ContainerPtr> inline
RefPtr<ContainerPtr> &RefPtr<ContainerPtr>::operator =(const RefPtr &refPtr)
{
    setRef(refPtr._pRef);

    return *this;
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator < (const FieldContainerPtr &other) const
{
    return _pRef < other;
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator ==(const FieldContainerPtr &other) const
{
    return _pRef == other;
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator !=(const FieldContainerPtr &other) const
{
    return !(_pRef == other);
}


template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator < (const RefPtr<ContainerPtr> &other) const
{
    return _pRef < other._pRef;
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator ==(const RefPtr<ContainerPtr> &other) const
{
    return _pRef == other._pRef;
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator !=(const RefPtr<ContainerPtr> &other) const
{
    return !(_pRef == other._pRef);
}

template<class ContainerPtr> inline
bool RefPtr<ContainerPtr>::operator ! (void) const
{
    return _pRef == NullFC;
}

template<class ContainerPtr> inline
void RefPtr<ContainerPtr>::setRef(const Ref &pContainer)
{
    if(_pRef == pContainer)
        return;

    setRefd(_pRef, pContainer);
}

OSG_END_NAMESPACE
