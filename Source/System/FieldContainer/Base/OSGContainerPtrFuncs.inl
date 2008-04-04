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
void PointerFuncs::addRefX(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->addReferenceX();
}

template <class PtrT> inline
void PointerFuncs::subRefX(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->subReferenceX();
}

template <class PtrT> inline
void PointerFuncs::subRefLocalVarX(const PtrT objectP)
{
    if(objectP != NilP)
        objectP->subReferenceLocalVarX();
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
void addRefX(FieldBundlePConst objectP)
{
    PointerFuncs::addRefX(objectP);

}

inline
void addRefX(FieldContainerPtrConst objectP)
{
    PointerFuncs::addRefX(objectP);
}



inline
void subRefX(FieldBundlePConst objectP)
{
    PointerFuncs::subRefX(objectP);
}

inline
void subRefX(FieldContainerPtrConst objectP)
{
    PointerFuncs::subRefX(objectP);
}

inline
void subRefLocalVarX(FieldContainerPtrConst objectP)
{
    PointerFuncs::subRefLocalVarX(objectP);
}


inline
void shallowSubRefX(FieldBundlePConst objectP)
{
    PointerFuncs::shallowSubRefX(objectP);
}

inline
void shallowSubRefX(FieldContainerPtrConst objectP)
{
    PointerFuncs::shallowSubRefX(objectP);
}

template <class StoreT, class SourceT> inline
void setRefdX(StoreT  &pTarget,
              SourceT  pSource)
{
    OSG::addRefX(pSource);
    OSG::subRefX(pTarget);
    
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

