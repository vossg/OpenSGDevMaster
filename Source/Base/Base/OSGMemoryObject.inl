/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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

/*! class MemoryObject
 */

/*! \var Int32 MemoryObject::_refCount
 *  \brief reference count
 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
MemoryObject::~MemoryObject(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Reference Counting                               */

inline
void MemoryObject::addRef(void)
{
    osgAtomicIncrement(&_refCount);
}

inline
void MemoryObject::subRef(void)
{
    RefCountStore tmpRefCnt = osgAtomicExchangeAndAdd(&_refCount, -1);

    if(tmpRefCnt <= 1)
        delete this;
}

inline
Int32 MemoryObject::getRefCount(void)
{
    return osgAtomicExchangeAndAdd(&_refCount, 0);
}

inline
void MemoryObject::addReferenceUnrecorded(void)
{
    addRef();
}

inline
void MemoryObject::subReferenceUnrecorded(void)
{
    subRef();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
MemoryObject::MemoryObject(void) :
    _refCount(0)
{
}

inline
MemoryObject::MemoryObject(const MemoryObject &) :
    _refCount(0)
{
}

inline 
void addRef(OSG::MemoryObjectPConst pObject)
{
    if(pObject != NULL)
    {
        pObject->addRef();
    }
}

inline
void subRef(OSG::MemoryObjectPConst pObject)
{
    if(pObject != NULL)
    {
        pObject->subRef();
    }
}

template <class T> inline
void setRefd(T *&pObject, T * const pNewObject)
{
    addRef(pNewObject);
    subRef(pObject   );
    
    pObject = pNewObject;
}

template <class T> inline
void clearRef(T *&pObject)
{
    subRef(pObject);

    pObject = NULL;
}

OSG_END_NAMESPACE

