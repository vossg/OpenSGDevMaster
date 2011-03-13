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

#define OSG_FIELDCONTAINER_DEBUG_SILENT

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
FieldContainer::TypeObject &FieldContainer::getClassType(void)
{
    return _type;
}

inline
UInt32 FieldContainer::getClassTypeId(void)
{
    return _type.getId();
}

inline
UInt16 FieldContainer::getClassGroupId(void)
{
    return _type.getGroupId();
}

inline
void FieldContainer::changed(ConstFieldMaskArg whichField, 
                             UInt32            ,
                             BitVector         )
{
    callChangedFunctors(whichField);
}

inline
void FieldContainer::callChangedFunctors(ConstFieldMaskArg whichField)
{
    MFChangedFunctorCallback::iterator       cfIt = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd= _mfChangedFunctors.end();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func)
            (cfIt->_func)(this, whichField);
    }
}

inline
void FieldContainer::addReferenceRecorded(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addReference [%p] [%d] [%s] START - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    osgAtomicIncrement(&_iRefCount);
    
    Thread::getCurrentChangeList()->addAddRefd(Inherited::getId());

#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addReference [%p] [%d] [%s] STOP - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif
}

inline
void FieldContainer::addReferenceUnrecorded(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addReferenceUnrec [%p] [%d] [%s] START - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif

    osgAtomicIncrement(&_iRefCount);

#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addReferenceUnrec [%p] [%d] [%s] STOP - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif
}

inline
RefCountStore FieldContainer::getRefCount(void) 
{
    return static_cast<RefCountStore const volatile &>(_iRefCount);
}


inline
void FieldContainer::addWeakReference(void)
{
#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addWeakReference [%p] [%d] [%s] START - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif
        
    osgAtomicIncrement(&_iWeakRefCount);

#ifndef OSG_FIELDCONTAINER_DEBUG_SILENT
    FINFO(("FieldContainer::addWeakReference [%p] [%d] [%s] STOP - [%d %d]\n",
           this, 
           this->getId(), 
           this->getType().getCName(),
           this->_iRefCount, 
           this->_iWeakRefCount));
#endif
}


inline
RefCountStore FieldContainer::getWeakRefCount(void) 
{
    return static_cast<RefCountStore const volatile &>(_iWeakRefCount);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainer::FieldContainer(void) :
     Inherited        (    ),
#ifdef OSG_MT_CPTR_ASPECT
    _pAspectStore     (NULL),
#endif
    _pFieldFlags      (NULL),
    _mfChangedFunctors(    ),
    _iRefCount        (   0),
    _iWeakRefCount    (   0)
{
    _pFieldFlags = new FieldFlags;
}

inline
FieldContainer::FieldContainer(const FieldContainer &source) :
     Inherited        (source                   ),
#ifdef OSG_MT_CPTR_ASPECT
    _pAspectStore     (NULL                     ),
#endif
    _pFieldFlags      (NULL                     ),
    _mfChangedFunctors(source._mfChangedFunctors),
    _iRefCount        (                        0),
    _iWeakRefCount    (                        0)
{
    _pFieldFlags = new FieldFlags(*(source._pFieldFlags));
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainer::~FieldContainer(void)
{
    if (NULL != _pFieldFlags)
    {
       delete _pFieldFlags;
       _pFieldFlags = NULL;
    }

    if(_pContainerChanges != NULL)
    {
        _pContainerChanges->release();

        _pContainerChanges = NULL;
    }
}

inline
void FieldContainer::addChangedFunctor(ChangedFunctor     func,
                                       const std::string &createSymbol)
{
    ChangedFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _mfChangedFunctors.push_back(oTmp);
}

template<class FunctorT> inline
void FieldContainer::subChangedFunctor(FunctorT func)
{
    MFChangedFunctorCallback::iterator       cfIt  = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd = _mfChangedFunctors.end  ();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
        {
            _mfChangedFunctors.erase(cfIt);
            break;
        }
    }
}

inline
void FieldContainer::subChangedFunctor(const std::string &createSymbol)
{
    MFChangedFunctorCallback::iterator       cfIt  = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd = _mfChangedFunctors.end  ();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_createSymbol == createSymbol)
        {
            _mfChangedFunctors.erase(cfIt);
            break;
        }
    }
}

template<class FunctorT> inline
bool FieldContainer::hasChangedFunctor(FunctorT func)
{
    bool returnValue = false;

    MFChangedFunctorCallback::iterator       cfIt  = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd = _mfChangedFunctors.end  ();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
        {
            returnValue = true;
            break;
        }
    }
    
    return returnValue;
}

inline
bool FieldContainer::hasChangedFunctor(const std::string &createSymbol)
{
    bool returnValue = false;

    MFChangedFunctorCallback::iterator       cfIt  = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd = _mfChangedFunctors.end  ();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_createSymbol == createSymbol)
        {
            returnValue = true;
            break;
        }
    }

    return returnValue;
}

inline 
void FieldContainer::clearChangedFunctors(void)
{
    _mfChangedFunctors.clear();
}

inline
const FieldFlags *FieldContainer::getFieldFlags(void)
{
    return _pFieldFlags;
}

inline
bool FieldContainer::isMTLocal(void) const
{
    bool returnValue =         
        ((this->_pFieldFlags->_bNamespaceMask & FCLocal::MTMask) == 
         TypeTraits<BitVector>::BitsClear);

    return returnValue;
}

#ifdef OSG_MT_CPTR_ASPECT
inline
FieldContainer *FieldContainer::getAspectPtr(UInt32 uiAspect) const
{
    if(_pAspectStore == NULL)
        return NULL;

    return _pAspectStore->getPtr(uiAspect);
}

inline
void FieldContainer::setupAspectStore(void)
{
    _pAspectStore = new AspectStore;

    OSG::addRef(_pAspectStore);

    _pAspectStore->setPtrForAspect(this, Thread::getCurrentAspect());
}

inline
void FieldContainer::setupAspectStore(AspectStore *pStore)
{
    _pAspectStore = pStore;

    OSG::addRef(_pAspectStore);

    _pAspectStore->setPtrForAspect(this, Thread::getCurrentAspect());
}

inline
AspectStoreP FieldContainer::getAspectStore(void) const
{
    return _pAspectStore;
}

#endif

inline
void FieldContainer::editSField(ConstFieldMaskArg whichField)
{
    if(_bvChanged == TypeTraits<BitVector>::BitsClear)
    {
        registerChangedContainer();
    }
    
    _bvChanged |= whichField;
}

#if OSG_MT_CPTR_ASPECT
template<class FieldT> inline
void FieldContainer::editMField(ConstFieldMaskArg  whichField,
                                FieldT            &oField    )
{
    if(_bvChanged == TypeTraits<BitVector>::BitsClear)
    {
        registerChangedContainer();
    }

    _bvChanged |= whichField;

    if(oField.isShared() == false)
    {
        return;
    }

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    oField.beginEdit(Thread::getCurrentAspect(),
                     oOffsets);
}
#else
template<class FieldT> inline
void FieldContainer::editMField(ConstFieldMaskArg  whichField,
                                FieldT            &oField    )
{
    if(_bvChanged == TypeTraits<BitVector>::BitsClear)
    {
        registerChangedContainer();
    }
    
    _bvChanged |= whichField;
}
#endif

inline
void FieldContainer::clearUncommited(ConstFieldMaskArg whichField)
{
    if(_pContainerChanges != NULL)
    {
          _pContainerChanges->whichField            |=  whichField;
        *(_pContainerChanges->bvUncommittedChanges) &= ~whichField;
    }
}

#ifdef OSG_MT_CPTR_ASPECT
inline
void FieldContainer::execSync(      FieldContainer    *pFrom,
                                    ConstFieldMaskArg  whichField,
                                    AspectOffsetStore &oOffsets,
                                    ConstFieldMaskArg  syncMode  ,
                              const UInt32             uiSyncInfo)
{
    editSField(whichField);
}
#endif


inline
void FieldContainer::onCreateAspect(const FieldContainer *,
                                    const FieldContainer *source)
{
    if(source == NULL)
    {
              BitVector           bCurrent = 0x0002;
        const FieldContainerType &pType    = this->getType();

        for(UInt32 i = 1; i <= pType.getNumFieldDescs(); ++i)
        {
            FieldDescriptionBase *pDesc = pType.getFieldDesc(i);

            if(0x0000 != (pDesc->getFlags() & Field::FThreadLocal))
            {
                _pFieldFlags->_bThreadLocalFlags |= bCurrent;
            }

            if(0x0000 != (pDesc->getFlags() & Field::FClusterLocal))
            {
                _pFieldFlags->_bClusterLocalFlags |= bCurrent;
            }

            if(pDesc->isMField() == true)
            {
                if(0x0000 != (pDesc->getFlags() & Field::MFCopySync))
                {
                    _pFieldFlags->_bSyncFlags |= bCurrent;
                }
            }

            bCurrent <<= 1;
        }

        _pFieldFlags->_bThreadLocalFlags  = 
            ~(_pFieldFlags->_bThreadLocalFlags);

        _pFieldFlags->_bClusterLocalFlags = 
            ~(_pFieldFlags->_bClusterLocalFlags);
    }

    _pFieldFlags->_bNamespaceMask = 
        (Thread::getCurrentNamespaceMask() | FCLocal::MT);
}

inline
void FieldContainer::onCreate(const FieldContainer *)
{
    registerChangedContainer();
    
    _bvChanged = 
        TypeTraits<BitVector>::BitsSet & getType().getUnmarkedOnCreate();
}

inline
void FieldContainer::onDestroy(UInt32)
{
}

inline
void FieldContainer::initMethod(InitPhase ePhase)
{
    FDEBUG(("FieldContainer initMethod called (%d)\n", ePhase));
}

inline
void FieldContainer::exitMethod(InitPhase ePhase)
{
    FDEBUG(("FieldContainer exitMethod called (%d)\n", ePhase));
}

inline
const Char8 *FieldContainer::getClassname(void)
{
    return "FieldContainer";
}

#ifdef OSG_MT_CPTR_ASPECT
template<class ContainerPtr> inline
ContainerPtr convertToCurrentAspect(ContainerPtr pFC)
{
    if(pFC == NULL)
    {
        return NULL;
    }
    
    ContainerPtr result = 
        static_cast<ContainerPtr>(
            pFC->getAspectPtr(Thread::getCurrentAspect()));

    return result;
}
#endif


template <class ObjectT> inline
void FieldContainer::newPtr(      typename ObjectT::ObjCPtr &result, 
                            const          ObjectT          *pPrototype,
                                           BitVector         bFlags    )
{
    result = new ObjectT(*pPrototype);

#ifdef OSG_MT_CPTR_ASPECT
    result->setupAspectStore();
#endif

    result->setId(FieldContainerFactory::the()->registerContainer(result));
    
    if(bFlags != TypeTraits<BitVector>::BitsSet)
        Thread::getCurrentChangeList()->addCreated(result->getId(), bFlags);

    result->onCreate      (        pPrototype);
    result->onCreateAspect(result, pPrototype);
}

template <class ObjectT> inline
void FieldContainer::newPtr(typename ObjectT::ObjCPtr &result,
                                     BitVector         bFlags)
{
    result = new ObjectT;

#ifdef OSG_MT_CPTR_ASPECT
    result->setupAspectStore();
#endif

    result->setId(FieldContainerFactory::the()->registerContainer(result));
    
    if(bFlags != TypeTraits<BitVector>::BitsSet)
        Thread::getCurrentChangeList()->addCreated(result->getId(), bFlags);

    result->onCreate      (      );
    result->onCreateAspect(result);
}

#ifdef OSG_MT_CPTR_ASPECT
template <class ObjectT> inline
void FieldContainer::newAspectCopy(typename ObjectT::ObjCPtr &result, 
                                   const    ObjectT          *pRefAspect,
                                   const    ObjectT          *pPrototype)
{
    result = new ObjectT(*pPrototype);

    result->onCreateAspect(pRefAspect, pPrototype);
}
#endif

template <class FieldT> inline
void SFieldConnector<FieldT>::process(void)
{
    _pDst->editSField(_bDstMask);

    *_pDstField = *_pSrcField;
}


template <class FieldT> inline
void MFieldConnector<FieldT>::process(void)
{
    _pDst->editMField(_bDstMask, *_pDstField);

    *_pDstField = *_pSrcField;
}

OSG_END_NAMESPACE

