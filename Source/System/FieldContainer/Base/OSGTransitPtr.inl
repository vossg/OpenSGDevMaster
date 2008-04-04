/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                       Copyright 2008 by OpenSG Forum                      *
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
TransitPtr<ObjectT>::TransitPtr(ObjectPtrConstArg pObj) :
    _pObj(pObj)
{
    if(_pObj != NULL)
        _pObj->addReferenceX();
}

template<class ObjectT> inline
TransitPtr<ObjectT>::TransitPtr(Self &other) :
    _pObj(other._pObj)
{
    other._pObj = NULL;
}

template<class ObjectT> inline
TransitPtr<ObjectT>::~TransitPtr(void)
{
    if(_pObj != NULL)
        _pObj->subReferenceX();
}

template<class ObjectT> inline
typename TransitPtr<ObjectT>::Self &TransitPtr<ObjectT>::operator =(Self &other)
{
    if(_pObj != NULL)
        _pObj->subReferenceX();

    _pObj = other._pObj;

    other._pObj = NULL;

    return *this;
}

OSG_END_NAMESPACE

