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

/*! \var RefCountStore AspectStore::_refCount
 *  \brief reference count
 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
AspectStore::~AspectStore(void)
{
#ifdef OSG_ENABLE_MEMORY_DEBUGGING
    for(UInt32 i = 0; i < _vAspects.size(); ++i)
    {
        _vAspects[i] = reinterpret_cast<FieldContainer *>(0xDEADBEEF);
    }
#endif
}

inline
FieldContainer *AspectStore::getPtr(const UInt32 uiAspect) const
{
    if(uiAspect < _vAspects.size())
    {
#ifdef OSG_ENABLE_MEMORY_DEBUGGING
        OSG_ASSERT(_vAspects[uiAspect] != reinterpret_cast<FieldContainer *>(0xDEADBEEF));
#endif

        return _vAspects[uiAspect];
    }
    else
    { 
        return NULL;
   }
}


inline
FieldContainer *AspectStore::getPtr(void) const
{
    return getPtr(Thread::getCurrentAspect());
}

inline
void AspectStore::setPtrForAspect(      FieldContainer *pContainer, 
                                  const UInt32          uiAspect  )
{
    _vAspects.resize(osgMax<UInt32>(_vAspects.size(), uiAspect + 1), NULL);
    
    _vAspects[uiAspect] = pContainer;
}

inline
void AspectStore::removePtrForAspect(const UInt32 uiAspect)
{
    if(uiAspect >= _vAspects.size())
    {
        return;
    }

    _vAspects[uiAspect] = NULL;
}

inline
UInt32 AspectStore::getNumAspects(void) const
{
    return _vAspects.size();
}

/*-------------------------------------------------------------------------*/
/*                        Reference Counting                               */

inline
void AspectStore::addRef(void)
{
    osgAtomicIncrement(&_refCount);
}

inline
void AspectStore::subRef(void)
{
    RefCountStore tmpRefCount = osgAtomicExchangeAndAdd(&_refCount, -1);

    if(tmpRefCount <= 1)
        delete this;
}

inline
Int32 AspectStore::getRefCount(void)
{
    return osgAtomicExchangeAndAdd(&_refCount, 0);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
AspectStore::AspectStore(void) :
    _vAspects( ),
    _refCount(0)
{
}

inline
AspectStore::AspectStore(const AspectStore &) :
    _vAspects( ),
    _refCount(0)
{
}

inline
void AspectStore::fillOffsetArray(AspectOffsetStore &       oStore, 
                                  FieldContainer    * const pRef  )
{
    Char8 *pRefMem = reinterpret_cast<Char8 *>(pRef);

    oStore.resize(ThreadManager::getNumAspects());
    
    std::fill(oStore.begin(), oStore.end(), -1);

    for(UInt32 i = 0; i < _vAspects.size(); ++i)
    {
        Char8 *pCurrMem = reinterpret_cast<Char8 *>(_vAspects[i]);

        if(pCurrMem != pRefMem && pCurrMem != NULL)
        {
            oStore[i] = pCurrMem - pRefMem;
        }
    }
}

inline
void AspectStore::dump(void)
{
    fprintf(stderr, "RC : %d\n", _refCount);

    for(UInt32 i = 0; i < _vAspects.size(); ++i)
    {
        fprintf(stderr, "AS %d : %p\n", i, _vAspects[i]);
    }
}

inline 
void addRef(const OSG::AspectStoreP pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

inline
void subRef(const OSG::AspectStoreP pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}


OSG_END_NAMESPACE
