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

OSG_BEGIN_NAMESPACE



template <class PtrT> inline
void PointerFuncs::addRef(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->addReference();
}

template <class PtrT> inline
void PointerFuncs::subRef(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->subReference();
}

template <class PtrT> inline
void PointerFuncs::subRefLocalVar(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->subReferenceLocalVar();
}

template <class PtrT> inline
void PointerFuncs::beginEdit(const PtrT     ,
                                   BitVector,
                                   UInt32   )
{
}

template <class PtrT> inline
void PointerFuncs::endEdit(const PtrT      objectP,
                                 BitVector whichField,
                                 UInt32    origin    )
{
#ifdef OSG_OLD_EDIT
    if(Thread::getCurrentChangeList()->isReadOnly() == true)
    {
        objectP->changed(whichField, origin);
    }
    else
    {
        if(objectP->getChangeEntry() == NULL)
        {
            objectP->setChangeEntry(
                Thread::getCurrentChangeList()->getNewEntry());
            
            objectP->getChangeEntry()->uiEntryDesc   = 
                ContainerChangeEntry::Change;
            
            objectP->getChangeEntry()->uiContainerId = 
                objectP->getId();
        }

        objectP->execEndEdit(whichField        );
        objectP->changed    (whichField, origin);
    }
#endif
}

template<class PtrT> inline
void PointerFuncs::executeSync(      PtrT              &,
                                     UInt32             ,
                                     UInt32             ,
                                     ConstFieldMaskArg  ,
                                     ConstFieldMaskArg  ,
                               const UInt32             )
{
    FDEBUG(("Trying to sync fieldcontainer * implementation, ignored\n"));
}

template <class PtrT> inline 
UInt32 PointerFuncs::getContainerId(PtrT objectP)
{
    return objectP->getId();
}

template <class PtrT> inline 
Int32 PointerFuncs::getRefCount(PtrT objectP)
{
    return objectP->getRefCount();
}

template <class Ptr> inline
Ptr PointerFuncs::getCPtr(Ptr pObject)
{
    return pObject;
}



inline
void addRef(FieldBundlePConst objectP)
{
    PointerFuncs::addRef(objectP);

}

inline
void addRef(FieldContainerPtrConst objectP)
{
    PointerFuncs::addRef(objectP);
}

inline 
void addRef(ParentFieldContainerPtrConst objectP)
{
    PointerFuncs::addRef(objectP);
}


inline
void subRef(FieldBundlePConst objectP)
{
    PointerFuncs::subRef(objectP);
}

inline
void subRef(FieldContainerPtrConst objectP)
{
    PointerFuncs::subRef(objectP);
}

inline
void subRefLocalVar(FieldContainerPtrConst objectP)
{
    PointerFuncs::subRefLocalVar(objectP);
}

inline 
void subRef(ParentFieldContainerPtrConst objectP)
{
    PointerFuncs::subRef(objectP);
}

inline
void shallowSubRef(FieldBundlePConst objectP)
{
    PointerFuncs::shallowSubRef(objectP);
}

inline
void shallowSubRef(FieldContainerPtrConst objectP)
{
    PointerFuncs::shallowSubRef(objectP);
}

template <class StoreT, class SourceT> inline
void setRefd(StoreT  &pTarget,
             SourceT  pSource)
{
    OSG::addRef(pSource);
    OSG::subRef(pTarget);
    
    pTarget = pSource;
}

inline
UInt32 getContainerId(FieldBundleConstPConst objectP)
{
    return PointerFuncs::getContainerId(objectP);
}

Int32 getRefCount(FieldBundleConstPConst objectP)
{
    return PointerFuncs::getRefCount(objectP);
}

inline
UInt32 getContainerId(FieldContainerConstPtrConst objectP)
{
    return PointerFuncs::getContainerId(objectP);
}

inline
Int32 getRefCount(FieldContainerConstPtrConst objectP)
{
    return PointerFuncs::getRefCount(objectP);
}

inline 
FieldBundleConstP getCPtr(FieldBundleConstPConst objectP)
{
    return objectP;
}

inline 
FieldBundleP getCPtr(FieldBundlePConst objectP)
{
    return objectP;
}

template <class Ptr> inline 
typename PtrStripper<Ptr>::Object *getCPtr(Ptr objectP)
{
    return PointerFuncs::getCPtr(objectP);
}

template <class Ptr> inline 
typename PtrStripper<Ptr>::ConstObject *getCConstPtr(Ptr objectP)
{
    return PointerFuncs::getCPtr(objectP);
}

OSG_END_NAMESPACE

