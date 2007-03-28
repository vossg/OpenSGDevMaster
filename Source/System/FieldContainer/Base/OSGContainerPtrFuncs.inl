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


template <class PtrT> inline
void CPointerFuncs::addRef(const PtrT objectP)
{
    if(objectP != NullFC)
        objectP.addReference();
}

template <class PtrT> inline
void CPointerFuncs::subRef(const PtrT objectP)
{
    if(objectP != NullFC)
        objectP.subReference();
}

template <class PtrT> inline
void CPointerFuncs::beginEdit(const PtrT      objectP,
                                    BitVector whichField,
                                    UInt32    origin    )
{
#ifdef OSG_OLD_EDIT
    if(Thread::getCurrentChangeList()->isReadOnly() == true)
        return;

    FDEBUG(("CPtrF::beginEdit %p 0x%016llx 0x%08x\n", 
            &(*objectP), whichField, origin));

    objectP->execBeginEdit(whichField, 
                           objectP.getContainerSize());
#endif
}

template <class PtrT> inline
void CPointerFuncs::endEdit(const PtrT      objectP,
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
        FDEBUG(("CPtrF::endEdit %p 0x%016llx 0x%08x\n", 
                &(*objectP), whichField, origin));

        if(objectP->getChangeEntry() == NULL)
        {
            objectP->setChangeEntry(
                Thread::getCurrentChangeList()->getNewEntry());
            
            objectP->getChangeEntry()->uiEntryDesc   = 
                ContainerChangeEntry::Change;
            
            objectP->getChangeEntry()->uiContainerId = 
                objectP.getContainerId();
        }
        
        objectP->execEndEdit(whichField        );
        objectP->changed    (whichField, origin);
    }
#endif
}

template<class PtrT> inline
void CPointerFuncs::executeSync(      PtrT              &pTarget,
                                      UInt32             uiFromAspect,
                                      UInt32             uiToAspect,
                                      ConstFieldMaskArg  whichField,
                                      ConstFieldMaskArg  syncMode,
                                const UInt32             uiSyncInfo  )
{
    FieldContainer *pFrom = 
        ((FieldContainer *) pTarget.getElemP(uiFromAspect));

    FDEBUG(("Execute sync %u %u %u %016llx\n",
            pTarget.getContainerId(),
            uiFromAspect,
            uiToAspect,
            whichField));

    UInt32 uiSInfo = uiSyncInfo | (uiFromAspect << 24) | (uiToAspect << 16); 

    pTarget->execSyncV(*pFrom,
                        whichField,
                        syncMode,
                        uiSInfo,
                        pTarget.getContainerSize());
}

template <class PtrT> inline
UInt32 CPointerFuncs::getContainerId(PtrT objectP)
{
    return objectP.getContainerId();
}

template <class PtrT> inline
Int32 CPointerFuncs::getRefCount(PtrT objectP)
{
    return objectP.getRefCount();
}


template <class Ptr> inline
typename Ptr::StoredObject *CPointerFuncs::getCPtr(Ptr pObject)
{
    return pObject.getCPtr();
}


#ifdef OSG_FIELDBUNDLE
inline
void addRef(FieldBundlePConst objectP)
{
    PointerFuncs::addRef(objectP);

}
#endif

inline
void addRef(FieldContainerPtrConst objectP)
{
    typedef 
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs                   >::type Functions;

    Functions::addRef(objectP);
}

#ifndef OSG_MT_FIELDCONTAINERPTR
inline 
void addRef(ParentFieldContainerPtrConst objectP)
{
    CPointerFuncs::addRef(objectP);
}
#endif

#ifdef OSG_FIELDBUNDLE
inline
void subRef(FieldBundlePConst objectP)
{
    PointerFuncs::subRef(objectP);
}
#endif

inline
void subRef(FieldContainerPtrConst objectP)
{
    typedef 
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs                   >::type Functions;

    Functions::subRef(objectP);
}

#ifndef OSG_MT_FIELDCONTAINERPTR
inline 
void subRef(ParentFieldContainerPtrConst objectP)
{
    CPointerFuncs::subRef(objectP);
}
#endif

#ifdef OSG_FIELDBUNDLE
inline
void shallowSubRef(FieldBundlePConst objectP)
{
    PointerFuncs::shallowSubRef(objectP);
}
#endif

inline
void shallowSubRef(FieldContainerPtrConst objectP)
{
    typedef
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs                   >::type Functions;

    Functions::shallowSubRef(objectP);
}

template <class StoreT, class SourceT> inline
void setRefd(StoreT  &pTarget,
             SourceT  pSource)
{
    OSG::addRef(pSource);
    OSG::subRef(pTarget);
    
    pTarget = pSource;
}

#ifndef OSG_DISABLE_DEPRECATED
template <class PtrT> inline
void beginEdit(const PtrT      objectP,
                     BitVector whichField,
                     UInt32    origin    )
{
#ifdef OSG_OLD_EDIT
    fprintf(stderr, "beginEditX %p 0x%016llx 0x%08x\n", 
            &(*objectP), whichField, origin);

    typedef typename 
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<SourceT>::value>,
            PointerFuncs,
            CPointerFuncs      >::type Functions;

    Functions::beginEdit(objectP, whichField, origin);
#endif
}

template <class PtrT> inline
void endEdit  (const PtrT      objectP,
                     BitVector whichField,
                     UInt32    origin    )
{
#ifdef OSG_OLD_EDIT
    fprintf(stderr, "endEditX %p 0x%016llx 0x%08x\n", 
            &(*objectP), whichField, origin);

    typedef typename
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<SourceT>::value>,
            PointerFuncs,
            CPointerFuncs      >::type Functions;

    Functions::endEdit(objectP, whichField, origin);
#endif
}
#endif

inline
void executeSync(      FieldContainerPtrConst pTarget,
                       UInt32                 uiFromAspect,
                       UInt32                 uiToAspect,
                       ConstFieldMaskArg      whichField,
                       ConstFieldMaskArg      syncMode,
                 const UInt32                 uiSyncInfo  )
{
    typedef 
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs          >::type Functions;

    Functions::executeSync(pTarget,
                           uiFromAspect,
                           uiToAspect,
                           whichField,
                           syncMode,
                           uiSyncInfo);
}

#ifdef OSG_FIELDBUNDLE
inline
UInt32 getContainerId(FieldBundleConstPConst objectP)
{
    return PointerFuncs::getContainerId(objectP);
}

Int32 getRefCount(FieldBundleConstPConst objectP)
{
    return PointerFuncs::getRefCount(objectP);
}
#endif

inline
UInt32 getContainerId(FieldContainerConstPtrConst objectP)
{
    typedef
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs          >::type Functions;

    return Functions::getContainerId(objectP);
}

inline
Int32 getRefCount(FieldContainerConstPtrConst objectP)
{
    typedef
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<FieldContainerPtr>::value>,
            PointerFuncs,
            CPointerFuncs          >::type Functions;

    return Functions::getRefCount(objectP);
}

#ifdef OSG_FIELDBUNDLE
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
#endif

template <class Ptr> inline 
typename PtrStripper<Ptr>::Object *getCPtr(Ptr objectP)
{
    typedef typename PtrStripper<Ptr>::Ptr InPtr;

    typedef typename
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<InPtr>::value>,
            PointerFuncs,
            CPointerFuncs          >::type Functions;

    return Functions::getCPtr(objectP);
}

template <class Ptr> inline 
typename PtrStripper<Ptr>::ConstObject *getCConstPtr(Ptr objectP)
{
    typedef typename PtrStripper<Ptr>::Ptr InPtr;

    typedef typename 
        boost::mpl::if_<
            boost::mpl::bool_<boost::is_pointer<InPtr>::value>,
            PointerFuncs,
            CPointerFuncs          >::type Functions;

    return Functions::getCPtr(objectP);
}

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class B, class C> inline 
typename PtrStripper< FCPtr<B, C> >::Object *get_pointer( FCPtr<B,C> objectP)
{
    return getCPtr(objectP);
}

template <typename FcPtrType>
inline typename RefPtr<FcPtrType>::Ref::StoredObject* get_pointer(RefPtr<FcPtrType> p)
{
   return getCPtr(p.get());
}
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 488 )
#endif

template<class PointerT> inline
PointerT cast_dynamic(FieldContainer::ObjPtrConst pIn)
{
#ifdef OSG_MT_FIELDCONTAINERPTR

   if (NULL == pIn._storeP)
   {
      return PointerT(OSG::NullFC);
   }
   else
   {
    return PointerT(
        (dynamic_cast<const typename PointerT::StoredObject *>(
            pIn.getCPtr())),
        pIn.getContainerSize (),
        pIn.getParentFieldPos());
   }
#else
    return dynamic_cast<PointerT>(pIn);
#endif
}

template<class PointerT> inline
PointerT cast_static(FieldContainer::ObjPtr pIn)
{
#ifdef OSG_MT_FIELDCONTAINERPTR
    return *(static_cast<PointerT *>(&pIn));
#else
    return static_cast<PointerT>(pIn);
#endif
}

template<> inline
ParentFieldContainerPtr cast_dynamic(FieldContainer::ObjPtrConst pIn)
{
#ifdef OSG_MT_FIELDCONTAINERPTR
   if (NULL == pIn._storeP)
   {
      return ParentFieldContainerPtr(OSG::NullFC);
   }
   else
   {
    return ParentFieldContainerPtr(
        (dynamic_cast<const ParentFieldContainerPtr::StoredObject *>(
            pIn.getCPtr())),
        pIn.getContainerSize (),
        pIn.getParentFieldPos());
   }
#else
    return ParentFieldContainerPtr(
        dynamic_cast<ParentFieldContainerPtr::Pointer>(pIn));
#endif
}

#ifdef OSG_LINUX_ICC
#pragma warning( default : 488 )
#endif

OSG_END_NAMESPACE

#define OSGCONTAINERPTRFUNCS_INLINE_CVSID "@(#)$Id$"
