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

template<class ObjectT> inline
MTPtr<ObjectT>::MTPtr(ObjectT * const pObj) :
    _pObj(pObj)
{
}

template<class ObjectT> inline
MTPtr<ObjectT>::~MTPtr(void)
{
}

template<class ObjectT> inline
ObjectT *MTPtr<ObjectT>::get(void) const
{
    ObjectT *returnValue = convertToCurrentAspect<ObjectT *>(_pObj);

    return returnValue;
}

template<class ObjectT> inline
MTPtr<ObjectT>::operator ObjectT *(void) const
{
    return this->get();
}

template<class ObjectT> inline
ObjectT *MTPtr<ObjectT>::operator->(void) const
{
    return this->get();
}

template<class ObjectT> inline
ObjectT &MTPtr<ObjectT>::operator *(void) const
{
    return *this->get();
}


template<class ObjectT> inline
ObjectT *get_pointer(const MTPtr<ObjectT> &pIn)
{
    return pIn.get();
}

OSG_END_NAMESPACE
