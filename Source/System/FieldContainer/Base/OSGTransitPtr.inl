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
/*! \file OSGTransitPtr.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

/*! \class TransitPtr

The TransitPtr is used to avoid copying RefPtr by value, as that would incur
an unnecessary reference increment/decrement. They work very much like a
std::auto_ptr in that they pass ownership when assigned to or from.

\sa RefPtr MTRefPtr

*/

OSG_BEGIN_NAMESPACE

// TransitPtr methods

template<class ContainerPtr> inline
TransitPtr<ContainerPtr>::TransitPtr(TransitPtr &other) :
    _pRef()
{
    _pRef.swap(other._pRef);
}

template<class ContainerPtr> inline
TransitPtr<ContainerPtr>::TransitPtr(SelfRefPtr &other) :
    _pRef()
{
    _pRef.swap(other);
}

template<class ContainerPtr> inline
TransitPtr<ContainerPtr>::~TransitPtr(void)
{
}

template<class ContainerPtr> inline
TransitPtr<ContainerPtr> &TransitPtr<ContainerPtr>::operator =(const TransitPtr<ContainerPtr> &other)
{
    _pRef.swap(other._pRef);

    return *this;
}

template<class ContainerPtr> inline
TransitPtr<ContainerPtr> &TransitPtr<ContainerPtr>::operator =(const SelfRefPtr &other)
{
    _pRef.swap(other);

    return *this;
}


template<class ContainerPtr> inline
void TransitPtr<ContainerPtr>::swap(RefPtr<ContainerPtr> &other)
{
    _pRef.swap(other);
}

template<class ContainerPtr> inline
void TransitPtr<ContainerPtr>::swap(TransitPtr<ContainerPtr> &other)
{
    _pRef.swap(other._pRef);
}

OSG_END_NAMESPACE
