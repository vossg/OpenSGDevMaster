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

/*! \var Int32 AspectStore::_refCount
 *  \brief reference count
 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
AspectStore::~AspectStore(void)
{
}

inline
FieldContainer *AspectStore::getPtr(UInt32 uiAspect)
{
    if(uiAspect < _vAspects.size())
    {
        return _vAspects[uiAspect];
    }
    else
    { 
        return NULL;
   }
}


inline
FieldContainer *AspectStore::getPtr(void)
{
    return getPtr(Thread::getCurrentAspect());
}

inline
void AspectStore::setPtrForAspect(FieldContainerPtr pContainer, 
                                  UInt32            uiAspect  )
{
    _vAspects.resize(uiAspect + 1, NULL);
    
    _vAspects[uiAspect] = pContainer;
}

inline
void AspectStore::removePtrForAspect(UInt32 uiAspect)
{
    if(uiAspect >= _vAspects.size())
    {
        return;
    }

    _vAspects[uiAspect] = NULL;
}

/*-------------------------------------------------------------------------*/
/*                        Reference Counting                               */

inline
void AspectStore::addRef(void)
{
    _refCount++;
}

inline
void AspectStore::subRef(void)
{
    _refCount--;

    if(_refCount <= 0)
        delete this;
}

inline
Int32 AspectStore::getRefCount(void)
{
    return _refCount;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
AspectStore::AspectStore(void) :
    _refCount(0)
{
}

inline
AspectStore::AspectStore(const AspectStore &) :
    _refCount(0)
{
}

inline
void AspectStore::fillOffsetArray(AspectOffsetStore &oStore, 
                                  FieldContainerPtr  pRef  )
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
void addRef(const AspectStoreP pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

inline
void subRef(const AspectStoreP pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}


OSG_END_NAMESPACE
