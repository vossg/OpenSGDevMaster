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

#include "OSGConfig.h"

#ifdef OSG_MT_FIELDCONTAINERPTR

#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE
const NilFieldContainerPtr NullFC;

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

#ifdef OSG_ENABLE_MEMORY_DEBUGGING
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum)
{
    ((FieldContainer *)(_storeP + (_containerSize * uiElemNum)))->_assert_not_deleted();
    return (_storeP + (_containerSize * uiElemNum));
}

UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum) const
{
    ((FieldContainer *)(_storeP + (_containerSize * uiElemNum)))->_assert_not_deleted();
    return (_storeP + (_containerSize * uiElemNum));
}
#endif

bool FieldContainerPtrBase::addFCPtrInit(void)
{
    addPreFactoryInitFunction (FieldContainerPtrBase::initialize);
    addPostFactoryExitFunction(FieldContainerPtrBase::terminate );

    return true;
}

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
