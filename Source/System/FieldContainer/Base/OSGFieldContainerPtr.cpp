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

#include <cstdlib>
#include <cstdio>

#include <OpenSG/OSGConfig.h>

#ifdef OSG_MT_FIELDCONTAINERPTR

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldContainer.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGContainerPtrFuncs.h>

OSG_BEGIN_NAMESPACE
const NilFieldContainerPtr NullFC;

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

#ifdef OSG_ENABLE_MEMORY_DEBUGGING
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum)
{
    if(NULL == _storeP)
    {  return NULL; }

    if( ((FieldContainer *)(_storeP + (_containerSize * uiElemNum)))->_check_is_deleted() )
    {
       FcPtrInfo info;
       if (_memDebug_FcPtrInfoMap.find(_storeP) != _memDebug_FcPtrInfoMap.end() )
       { info = _memDebug_FcPtrInfoMap[_storeP]; }
       std::cout << "FC Ptr failure: FC of type: " << info.type_name                 
                 << "\n allocated: " << info.allocation_stack_trace
                 << "\n deallocated: " << info.deallocation_stack_trace 
                 << "\n accessed: " << OSG::getCallStack() << "\n" << std::endl;
       OSG_ASSERT(false && "Attempted to access deallocated field container.");
    }
    return (_storeP + (_containerSize * uiElemNum));
}

UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum) const
{
    if(NULL == _storeP)
    {  return NULL; }

    if( ((FieldContainer *)(_storeP + (_containerSize * uiElemNum)))->_check_is_deleted() )
    {
       FcPtrInfo info;
       if (_memDebug_FcPtrInfoMap.find(_storeP) != _memDebug_FcPtrInfoMap.end() )
       { info = _memDebug_FcPtrInfoMap[_storeP]; }
       std::cout << "FC Ptr failure: FC of type: " << info.type_name 
       		 << "\n allocated: " << info.allocation_stack_trace
                 << "\n deallocated: " << info.deallocation_stack_trace 
                 << "\n accessed: " << OSG::getCallStack() << "\n" << std::endl;
       OSG_ASSERT(false && "Attempted to access deallocated field container.");
    }
    return (_storeP + (_containerSize * uiElemNum));
}

/** Call when a new fc is allocated for an fc ptr. */
void FieldContainerPtrBase::memDebugTrackFcAllocate  (OSG::UInt8* storePVal, std::string typeName)
{
   FcPtrInfo allocate_info;
   allocate_info.type_name              = typeName;
   allocate_info.allocation_stack_trace = OSG::getCallStack();
   _memDebug_FcPtrInfoMap[storePVal] = allocate_info;
}

/** Call with an fcptr is dellocate and thus invalidated. */
void FieldContainerPtrBase::memDebugTrackFcDeallocate(OSG::UInt8* storePVal)
{
   if (_memDebug_FcPtrInfoMap.find(storePVal) != _memDebug_FcPtrInfoMap.end())
   {
      _memDebug_FcPtrInfoMap[storePVal].deallocation_stack_trace = OSG::getCallStack();
   }   
}

/** Call when we actually free the memory and don't need to track it any more. */
void FieldContainerPtrBase::memDebugTrackFcFree      (OSG::UInt8* storePVal)
{
   _memDebug_FcPtrInfoMap.erase(storePVal);
}

#endif


void FieldContainerPtrBase::subReference(void) const
{
    Thread::getCurrentChangeList()->addSubRefd(*(getIdP()));

    Thread::getCurrentChangeList()->incSubRefLevel();

    _pRefCountLock->acquire(_storeP);

    (*getRefCountP())--;

    if((*getRefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        UInt8 *pTmp = getFirstElemP();

        ReflexiveContainer *pRC =
            reinterpret_cast<ReflexiveContainer *>(
                getElemP(Thread::getCurrentAspect()));


        pRC->onDestroy   (*(getIdP()));
        pRC->resolveLinks(           );

#ifdef OSG_ASPECT_REFCOUNT
        if((*getARefCountP()) <= 0)
        {
#endif
            if(((ReflexiveContainer *) pTmp)->deregister(*(getIdP())) == true)
            {
                // Clean up a little.
                const_cast<FieldContainerPtrBase *>(this)->_storeP = NULL;

                return;
            }

            for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
            {
                ((ReflexiveContainer *) pTmp)->onDestroyAspect(*(getIdP()), i);

                ((ReflexiveContainer *) pTmp)->~ReflexiveContainer();

                pTmp += _containerSize;
            }

#ifndef OSG_ENABLE_MEMORY_DEBUGGING
            // If no memory debugging, just delete immediately
            operator delete(_storeP + getMemStartOff());
#else
            // Otherwise delay it for a while by storing the buffer until we reach the set limit            
            _memDebug_DelayedFreeList.push_back(_storeP);
            FieldContainerPtrBase::memDebugTrackFcDeallocate(_storeP);

            while(_memDebug_DelayedFreeList.size() > _memDebug_MaxFreeListSize)
            {
               OSG::UInt8* buf = _memDebug_DelayedFreeList.front();
               _memDebug_DelayedFreeList.pop_front();
               FieldContainerPtrBase::memDebugTrackFcFree(buf);
               operator delete(buf + getMemStartOff());
            }
#endif

#ifdef OSG_ASPECT_REFCOUNT
        }
#endif

#ifndef OSG_ENABLE_MEMORY_DEBUGGING
         // Clean up a little. (don't do this when debugging memory, because then it is
         // helpful to know the difference between a NullFC and a deallocated one)
        const_cast<FieldContainerPtrBase *>(this)->_storeP = NULL;
#endif
    }
    else
    {
        _pRefCountLock->release(_storeP);
    }

    Thread::getCurrentChangeList()->decSubRefLevel();
}

#ifdef OSG_ASPECT_REFCOUNT
void FieldContainerPtrBase::subAReference(void) const
{
    _pRefCountLock->acquire(_storeP);

    (*getARefCountP())--;

    if((*getRefCountP()) <= 0 && (*getARefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        UInt8 *pTmp = getFirstElemP();

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            ((ReflexiveContainer *) pTmp)->onDestroyAspect(*(getIdP()), i);

            ((ReflexiveContainer *) pTmp)->~ReflexiveContainer();

            pTmp += _containerSize;
        }

#ifndef OSG_ENABLE_MEMORY_DEBUGGING
        // If no memory debugging, just delete immediately
        operator delete(_storeP + getMemStartOff());
#else
        // Otherwise delay it for a while by storing the buffer until we reach the set limit            
        _memDebug_DelayedFreeList.push_back(_storeP);
        FieldContainerPtrBase::memDebugTrackFcDeallocate(_storeP);

        while(_memDebug_DelayedFreeList.size() > _memDebug_MaxFreeListSize)
        {
           OSG::UInt8* buf = _memDebug_DelayedFreeList.front();
           _memDebug_DelayedFreeList.pop_front();
           FieldContainerPtrBase::memDebugTrackFcFree(buf);
           operator delete(buf + getMemStartOff());
        }
#endif
    }
    else
    {
        _pRefCountLock->release(_storeP);
    }
}
#endif


bool FieldContainerPtrBase::addFCPtrInit(void)
{
    addPreFactoryInitFunction (FieldContainerPtrBase::initialize);
    addPostFactoryExitFunction(FieldContainerPtrBase::terminate );

    return true;
}

#ifdef OSG_ENABLE_MEMORY_DEBUGGING
std::deque<UInt8*>            FieldContainerPtrBase::_memDebug_DelayedFreeList;
OSG::UInt32                   FieldContainerPtrBase::_memDebug_MaxFreeListSize = 10000000;
std::map<UInt8*, FieldContainerPtrBase::FcPtrInfo>   FieldContainerPtrBase::_memDebug_FcPtrInfoMap;
#endif

LockPool              *FieldContainerPtrBase::_pRefCountLock  = NULL;

StaticInitFuncWrapper  FieldContainerPtrBase::_initFuncWrapper(addFCPtrInit);

bool FieldContainerPtrBase::initialize(void)
{
    bool           returnValue = false;
    ThreadManager *pManager    = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase init" << std::endl;

    if(pManager != NULL)
    {
        _pRefCountLock = pManager->getLockPool("DSPTRRefCountLockPool");

        addRef(_pRefCountLock);

        if(_pRefCountLock != NULL)
            returnValue = true;
    }

    return returnValue;
}

bool FieldContainerPtrBase::terminate(void)
{
    ThreadManager *pManager = ThreadManager::the();

    SINFO << "OSGFieldContainerPtrBase terminate" << std::endl;

    if(pManager == NULL)
        return false;

    subRef(_pRefCountLock);

    return true;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

void FieldContainerPtrBase::dump(void)
{
    fprintf(stderr, "FCPtr :\n");
    fprintf(stderr, "Base  : %p\n", _storeP);
#ifdef OSG_ASPECT_REFCOUNT
    fprintf(stderr, "ARef  : %d\n", *(getARefCountP()));
#endif
    fprintf(stderr, "Ref   : %d\n", *(getRefCountP ()));
    fprintf(stderr, "Id    : %d\n", *(getIdP       ()));
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

std::ostream &OSG::operator <<(      std::ostream       &os,
                               const FieldContainerPtr  &fc)
{
    if(fc == NullFC)
    {
        os << std::hex
           << "FieldContainerPtr 0x"
           << &fc
           << std::dec
           << ":NullFC";
    }
    else
    {
        os << std::hex << "FieldContainerPtr 0x"
           << &fc << std::dec << ":" << fc->getType().getName() << "Ptr(0x"
           << std::hex << (&(*fc)) << std::dec << ")";
    }

    return os;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */



/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERPTR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINERPTR_INLINE_CVSID;
}

#endif
