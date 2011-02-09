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

#include "OSGTypeFactory.h"

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
    _pStoreLock     (NULL                   ),
    _nextContainerId(1                      ),
    _containerStore (                       ),
    _pMapper        (NULL                   )
{
}

FieldContainerFactoryBase::FieldContainerFactoryBase(
    const Char8 *szFactoryName) :

     Inherited      (szFactoryName),
    _pStoreLock     (NULL         ),
    _nextContainerId(1            ),
    _containerStore (             ),
    _pMapper        (NULL         )
{
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

    _pStoreLock = ThreadManager::the()->getLock(
        "ContainerFactory::_pStorelock", false);

    PINFO << "Got store lock " << _pStoreLock.get() << std::endl;

    if(_pStoreLock == NULL)
    {
        return false;
    }
    else
    {
        return Inherited::initialize();
    }
}

bool FieldContainerFactoryBase::terminate(void)
{
    bool returnValue = Inherited::terminate();

    _pStoreLock = NULL;

    this->_bInitialized = false;

#ifdef OSG_DEBUG
    ContainerStoreConstIt sI = _containerStore.begin();
    ContainerStoreConstIt sE = _containerStore.end  ();
    
    for(; sI != sE; ++sI)
    {
        if((*sI).second != NULL)
        {
            FWARNING(("FieldContainerFactoryBase::terminate: "
                      "Entry [%d] is not NULL ([%p]). \n",
                      (*sI).first, (*sI).second));
                                              
            for(UInt32 j = 0; j < (*sI).second->getNumAspects(); ++j)
            {
                if((*sI).second->getPtr(j) != NULL)
                {
                    FWARNING(("  [%d] [%p] [%s] [%d %d]\n",
                              j, 
                              (*sI).second->getPtr(j),
                              (*sI).second->getPtr(j)->getType().getCName(),
                              (*sI).second->getPtr(j)->getRefCount(),
                              (*sI).second->getPtr(j)->getWeakRefCount() ));
                }
                else
                {
                    FWARNING(("  [%d] [%p] [] [N/A N/A]\n",
                              j, 
                              (*sI).second->getPtr(j)));
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

    _pStoreLock->acquire();

    UInt32 returnValue =  _nextContainerId++;

#ifdef OSG_MT_CPTR_ASPECT
    ContainerHandlerP pHandler = NULL;

    if(pContainer != NULL)
        pHandler = pContainer->getAspectStore();

    _containerStore.insert(
        ContainerStore::value_type(returnValue, pHandler));
#else
    _containerStore.insert(
        ContainerStore::value_type(returnValue, pContainer));
#endif

    _pStoreLock->release();

    return returnValue;
}

bool FieldContainerFactoryBase::deregisterContainer(const UInt32 uiContainerId)
{
    bool returnValue = false;

    _pStoreLock->acquire();

    ContainerStoreIt sI = _containerStore.find(uiContainerId);

    if(sI != _containerStore.end())
    {
        _containerStore.erase(sI);
    }
#ifdef OSG_DEBUG
    else
    {
        SWARNING << "FieldContainerFactory::unregisterContainer: "
                 << "id '" << uiContainerId << "' not found in "
                 << "container store!"
                 << std::endl;

        returnValue = true;
    }
#endif

    _pStoreLock->release();

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
    _pStoreLock->acquire();

    ContainerStoreConstIt sI          = _containerStore.begin();
    ContainerStoreConstIt sE          = _containerStore.end  ();
    Int32                 returnValue = -1;
    
    for(; sI != sE; ++sI)
    {
#ifdef OSG_MT_CPTR_ASPECT
        if((*sI).second->getPtr() == ptr)
#else
        if((*sI).second == ptr)
#endif
        {
            returnValue = (*sI).first;
            break;
        }
    }

    _pStoreLock->release();

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

void FieldContainerFactoryBase::dump(void)
{
    _pStoreLock->acquire();

    ContainerStoreConstIt sI = _containerStore.begin();
    ContainerStoreConstIt sE = _containerStore.end  ();
    
    for(; sI != sE; ++sI)
    {
        if((*sI).second != NULL)
        {
            FWARNING(("FieldContainerFactoryBase::dump: "
                      "Entry [%d] is not NULL ([%p]). \n",
                      (*sI).first, (*sI).second));
                                              
            for(UInt32 j = 0; j < (*sI).second->getNumAspects(); ++j)
            {
                if((*sI).second->getPtr(j) != NULL)
                {
                    FWARNING(("  [%d] [%p] [%s] [%d %d]\n",
                              j, 
                              (*sI).second->getPtr(j),
                              (*sI).second->getPtr(j)->getType().getCName(),
                              (*sI).second->getPtr(j)->getRefCount(),
                              (*sI).second->getPtr(j)->getWeakRefCount() ));
                }
                else
                {
                    FWARNING(("  [%d] [%p] [] [N/A N/A]\n",
                              j, 
                              (*sI).second->getPtr(j)));
                }
            }
        }
    }

    _pStoreLock->release();
}

DerivedFieldContainerTypeIterator 
    FieldContainerFactoryBase::begin(const FieldContainerType &oRef)
{
    return DerivedFieldContainerTypeIterator(oRef);
}

DerivedFieldContainerTypeIterator 
    FieldContainerFactoryBase::end(void)
{
    return DerivedFieldContainerTypeIterator();
}

FieldContainerType *DerivedFieldContainerTypeIterator::operator->(void)
{
    return _pCurrentType;
}

FieldContainerType *DerivedFieldContainerTypeIterator::operator *(void)
{
    return _pCurrentType;
}

void DerivedFieldContainerTypeIterator::operator++ (void)
{
    _pCurrentType = NULL;
    
    ++_uiCurrentType;

    for(; _uiCurrentType < TypeFactory::the()->getNumTypes(); 
        ++_uiCurrentType)
    {
        FieldContainerType *pTestType = 
            FieldContainerFactory::the()->findType(_uiCurrentType);

        if(pTestType                        != NULL)
        {
            if(pTestType->isDerivedFrom(*_pRef) == true   )
            {
                _pCurrentType = pTestType;
                
                break;
            }
        }
    }
}


bool DerivedFieldContainerTypeIterator::operator ==(
    const DerivedFieldContainerTypeIterator &lhs)
{
    return this->_uiCurrentType == lhs._uiCurrentType;
}

bool DerivedFieldContainerTypeIterator::operator !=(
    const DerivedFieldContainerTypeIterator &lhs)
{
    return !(*this == lhs);
}


DerivedFieldContainerTypeIterator::DerivedFieldContainerTypeIterator(void) :
    _pRef         (NULL                             ),
    _uiCurrentType(TypeFactory::the()->getNumTypes()),
    _pCurrentType (NULL                             )
{
}

DerivedFieldContainerTypeIterator::DerivedFieldContainerTypeIterator(
    const FieldContainerType &oRef) :

    _pRef         (&oRef),
    _uiCurrentType(0    ),
    _pCurrentType (NULL )
{
    ++(*this);
}

DerivedFieldContainerTypeIterator::DerivedFieldContainerTypeIterator(
    const DerivedFieldContainerTypeIterator &source) :

    _pRef         (source._pRef         ),
    _uiCurrentType(source._uiCurrentType),
    _pCurrentType (source._pCurrentType )
{
}


OSG_END_NAMESPACE


