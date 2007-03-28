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
                             UInt32            origin    )
{
    callChangedFunctors(whichField);
}

inline
void FieldContainer::callChangedFunctors(ConstFieldMaskArg whichField)
{
    MFChangedFunctorCallback::iterator       cfIt = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd= _mfChangedFunctors.end();

    ObjPtr thisP = Inherited::constructPtr<FieldContainer>(this);

    while(cfIt != cfEnd)
    {
        if(cfIt->_func)
            (cfIt->_func)(thisP, whichField);

        ++cfIt;
    }
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
    _mfChangedFunctors(    )
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
    _mfChangedFunctors(source._mfChangedFunctors)
{
    _pFieldFlags = new FieldFlags(*(source._pFieldFlags));
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainer::~FieldContainer(void)
{
    delete _pFieldFlags;
}

inline
UInt32 FieldContainer::addChangedFunctor(ChangedFunctor func,
                                         std::string    createSymbol)
{
    ChangedFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._uiId         = _mfChangedFunctors.size();
    oTmp._createSymbol = createSymbol;

    _mfChangedFunctors.push_back(oTmp);

    return oTmp._uiId;
}

template<class FunctorT> inline
void FieldContainer::subChangedFunctor(FunctorT func)
{
    MFChangedFunctorCallback::iterator       cfIt = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd= _mfChangedFunctors.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_func == func)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfChangedFunctors.erase(cfIt);
}

inline
void FieldContainer::subChangedFunctor(UInt32 uiId)
{
    MFChangedFunctorCallback::iterator       cfIt = _mfChangedFunctors.begin();
    MFChangedFunctorCallback::const_iterator cfEnd= _mfChangedFunctors.end();

    while(cfIt != cfEnd)
    {
        if(cfIt->_uiId == uiId)
            break;

        ++cfIt;
    }

    if(cfIt != cfEnd)
        _mfChangedFunctors.erase(cfIt);
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
FieldContainerPtr FieldContainer::getPtr(void)
{
    return Inherited::constructPtr<FieldContainer>(this);
}

#ifdef OSG_MT_CPTR_ASPECT
inline
FieldContainerPtr FieldContainer::getAspectPtr(UInt32 uiAspect)
{
    if(_pAspectStore == NULL)
        return NullFC;

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
AspectStoreP FieldContainer::getAspectStore(void)
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

#ifdef OSG_MT_FIELDCONTAINERPTR
template<class FieldT> inline
void FieldContainer::editMField(ConstFieldMaskArg  whichField,
                                FieldT            &oField    )
{
    if(_bvChanged == TypeTraits<BitVector>::BitsClear)
    {
        registerChangedContainer();
    }
    
    _bvChanged |= whichField;

    oField.beginEdit(Thread::getCurrentAspect(),
                     this->getContainerSize());
}
#elif OSG_MT_CPTR_ASPECT
template<class FieldT> inline
void FieldContainer::editMField(ConstFieldMaskArg  whichField,
                                FieldT            &oField    )
{
    if(_bvChanged == TypeTraits<BitVector>::BitsClear)
    {
        registerChangedContainer();
    }

    if(0x0000 != (_bvChanged & whichField))
    {
        return;
    }

    _bvChanged |= whichField;

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

#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void FieldContainer::execSync(      FieldContainer    *,
                                    ConstFieldMaskArg  whichField,
                                    ConstFieldMaskArg  ,
                              const UInt32,             
                                    UInt32             )
{
    editSField(whichField);
}
#endif

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

#if 0
inline
void FieldContainer::execBeginEdit(ConstFieldMaskArg, 
                                   UInt32,
                                   UInt32           )
{
}
#endif

inline
void FieldContainer::onCreateAspect(const FieldContainer *,
                                    const FieldContainer *source)
{
    if(source == NULL)
    {
              BitVector           bCurrent = 0x0001;
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
}

inline
void FieldContainer::onCreate(const FieldContainer *source)
{
    registerChangedContainer();
    
    _bvChanged = 
        TypeTraits<BitVector>::BitsSet & getType().getUnmarkedOnCreate();
}

inline
void FieldContainer::onDestroy(UInt32 uiContainerId)
{
#ifdef OSG_MT_CPTR_ASPECT
    this->deregister(uiContainerId);

    _pAspectStore->removePtrForAspect(Thread::getCurrentAspect());

    OSG::subRef(_pAspectStore);
#endif
}

inline
void FieldContainer::initMethod(InitPhase ePhase)
{
    FINFO(("FieldContainer initMethod called (%d)\n", 
           ePhase));
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
    if(pFC == OSGNullFC)
    {
        return OSGNullFC;
    }
    
    ContainerPtr result = 
        static_cast<ContainerPtr>(
            pFC->getAspectPtr(Thread::getCurrentAspect()));

    return result;
}
#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINER_INLINE_CVSID "@(#)$Id$"

