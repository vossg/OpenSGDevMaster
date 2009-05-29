/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILE_FIELDCONTAINERFACTORY

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldContainerFactory.h"
#include "OSGSingletonHolder.ins"
#include "OSGFieldContainerType.h"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldContainerFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<FieldContainerFactoryBase>;

OSG_END_NAMESPACE

#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::FieldContainerFactoryBase

This class is a singleton.  It should be accessed using the typedef
for OSG::FieldContainerFactory.
*/


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerFactoryBase::FieldContainerFactoryBase(void) :
     Inherited      ("FieldContainerFactory"),
#ifndef OSG_EMBEDDED
    _pStoreLock     (NULL                   ),
#endif
    _vContainerStore(                       ),
    _pMapper        (NULL                   )
{
    _vContainerStore.push_back(NULL);
}

FieldContainerFactoryBase::FieldContainerFactoryBase(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),
#ifndef OSG_EMBEDDED
    _pStoreLock     (NULL         ),
#endif
	_vContainerStore(             ),
    _pMapper        (NULL         )
{
    _vContainerStore.push_back(NULL);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerFactoryBase::~FieldContainerFactoryBase(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

bool FieldContainerFactoryBase::initialize(void)
{
    if(this->_bInitialized == true)
        return true;

#ifndef OSG_EMBEDDED
    _pStoreLock = ThreadManager::the()->getLock("ContainerFactory::slock");

    addRef(_pStoreLock);

    PINFO << "Got store lock " << _pStoreLock << std::endl;

    if(_pStoreLock == NULL)
    {
        return false;
    }
    else
    {
#endif
        return Inherited::initialize();
#ifndef OSG_EMBEDDED
    }
#endif
}

bool FieldContainerFactoryBase::terminate(void)
{
    bool returnValue = Inherited::terminate();

#ifndef OSG_EMBEDDED
    subRef(_pStoreLock);
#endif

    this->_bInitialized = false;

#ifdef OSG_DEBUG
    ContainerStoreIt sI = _vContainerStore.begin();
    ContainerStoreIt sE = _vContainerStore.end  ();
    
    for(UInt32 i = 0; sI != sE; ++sI, ++i)
    {
        if((*sI) != NULL)
        {
            FWARNING(("FieldContainerFactoryBase::terminate: "
                      "Entry [%d] is not NULL ([%p]). \n", i, *sI));
                                              
            for(UInt32 j = 0; j < (*sI)->getNumAspects(); ++j)
            {
                if((*sI)->getPtr(j) != NULL)
                {
                    FWARNING(("  [%d] [%p] [%s] [%d %d]\n",
                              j, 
                              (*sI)->getPtr(j), 
                              (*sI)->getPtr(j)->getType().getCName(),
                              (*sI)->getPtr(j)->getRefCount(),
                              (*sI)->getPtr(j)->getWeakRefCount() ));
                }
                else
                {
                    FWARNING(("  [%d] [%p] [] [N/A N/A]\n",
                              j, 
                              (*sI)->getPtr(j)));
                }
            }
        }
    }
#endif // OSG_DEBUG
    

    return returnValue;
}

bool FieldContainerFactoryBase::initializeFactoryPost(void)
{
    return Inherited::initializeFactoryPost();
}

UInt32 FieldContainerFactoryBase::registerContainer(
    const ContainerPtr &pContainer)
{
#ifdef OSG_ENABLE_VALGRIND_CHECKS
    VALGRIND_CHECK_VALUE_IS_DEFINED(pContainer);
#endif

    UInt32 returnValue = 0;

#ifndef OSG_EMBEDDED
    _pStoreLock->acquire();
#endif

#ifdef OSG_MT_CPTR_ASPECT
    ContainerHandlerP pHandler = NULL;

    if(pContainer != NULL)
        pHandler = pContainer->getAspectStore();

    _vContainerStore.push_back(pHandler);
#else
    _vContainerStore.push_back(pContainer);
#endif

    returnValue = _vContainerStore.size() - 1;

#ifndef OSG_EMBEDDED
    _pStoreLock->release();
#endif

    return returnValue;
}

/*! Try to find the ptr container in the factory. Primarily used to verify
that a container is still valid and registered with the factory. As this
function does not access the ptr itself at all, it is safe to call it with
corrupted data.

\return The container's id, or -1 if not found.

\warning It uses the current thread's aspect to compare against, therefore it's not
possible with this function to verify pointers from other threads/aspects.

*/

Int32 FieldContainerFactoryBase::findContainer(ContainerPtr ptr) const
{
#ifndef OSG_EMBEDDED
    _pStoreLock->acquire();
#endif

    ContainerStore::const_iterator it, end;
    Int32 id = 0;
    Int32 returnValue = -1;
    
    for(it = _vContainerStore.begin(), end = _vContainerStore.end();
        it != end; ++it, ++id)
    {
#ifdef OSG_MT_CPTR_ASPECT
        if((*it)->getPtr() == ptr)
#else
        if(*it == ptr)
#endif
        {
            returnValue = id;
            break;
        }
    }

#ifndef OSG_EMBEDDED
    _pStoreLock->release();
#endif

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

void FieldContainerFactoryBase::dump(void)
{
    ContainerStoreIt sI = _vContainerStore.begin();
    ContainerStoreIt sE = _vContainerStore.end  ();
    
    for(UInt32 i = 0; sI != sE; ++sI, ++i)
    {
        if((*sI) != NULL)
        {
            FWARNING(("FieldContainerFactoryBase::dump: "
                      "Entry [%d] is not NULL ([%p]). \n", i, *sI));
                                              
            for(UInt32 j = 0; j < (*sI)->getNumAspects(); ++j)
            {
                if((*sI)->getPtr(j) != NULL)
                {
                    FWARNING(("  [%d] [%p] [%s] [%d %d]\n",
                              j, 
                              (*sI)->getPtr(j), 
                              (*sI)->getPtr(j)->getType().getCName(),
                              (*sI)->getPtr(j)->getRefCount(),
                              (*sI)->getPtr(j)->getWeakRefCount() ));
                }
                else
                {
                    FWARNING(("  [%d] [%p] [] [N/A N/A]\n",
                              j, 
                              (*sI)->getPtr(j)));
                }
            }
        }
    }
}

OSG_END_NAMESPACE


