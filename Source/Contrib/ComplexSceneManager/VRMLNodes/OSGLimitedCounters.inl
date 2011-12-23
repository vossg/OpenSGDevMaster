/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

template<class Desc> inline
UInt32 LimitedCounterImpl<Desc>::getContainerSize(void) const
{
    return sizeof(Self);
}

/*------------------------- decorator get ------------------------------*/


template<class Desc> inline
typename LimitedCounterImpl<Desc>::SFLimitType *
    LimitedCounterImpl<Desc>::editSFUpperLimit(void)
{
    Self::editSField(UpperLimitFieldMask);

    return &_sfUpperLimit;
}

template<class Desc> inline
const typename LimitedCounterImpl<Desc>::SFLimitType *
    LimitedCounterImpl<Desc>::getSFUpperLimit(void) const
{
    return &_sfUpperLimit;
}

template<class Desc> inline
typename LimitedCounterImpl<Desc>::SFLimitType *
    LimitedCounterImpl<Desc>::editSFLowerLimit(void)
{
    Self::editSField(LowerLimitFieldMask);

    return &_sfLowerLimit;
}

template<class Desc> inline
const typename LimitedCounterImpl<Desc>::SFLimitType *
    LimitedCounterImpl<Desc>::getSFLowerLimit(void) const
{
    return &_sfLowerLimit;
}

template<class Desc> inline
SFBool *LimitedCounterImpl<Desc>::editSFLoop(void)
{
    Self::editSField(LoopFieldMask);

    return &_sfLoop;
}

template<class Desc> inline
const SFBool *LimitedCounterImpl<Desc>::getSFLoop(void) const
{
    return &_sfLoop;
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the LimitedReal32Counter::_sfUpperLimit field.

template<class Desc> inline
typename LimitedCounterImpl<Desc>::LimitType &
    LimitedCounterImpl<Desc>::editUpperLimit(void)
{
    Self::editSField(UpperLimitFieldMask);

    return _sfUpperLimit.getValue();
}

//! Get the value of the LimitedReal32Counter::_sfUpperLimit field.
template<class Desc> inline
typename LimitedCounterImpl<Desc>::LimitType 
    LimitedCounterImpl<Desc>::getUpperLimit(void) const
{
    return _sfUpperLimit.getValue();
}

//! Set the value of the LimitedReal32Counter::_sfUpperLimit field.
template<class Desc> inline
void LimitedCounterImpl<Desc>::setUpperLimit(const LimitType value)
{
    Self::editSField(UpperLimitFieldMask);

    _sfUpperLimit.setValue(value);
}
//! Get the value of the LimitedReal32Counter::_sfLowerLimit field.

template<class Desc> inline
typename LimitedCounterImpl<Desc>::LimitType &
    LimitedCounterImpl<Desc>::editLowerLimit(void)
{
    Self::editSField(LowerLimitFieldMask);

    return _sfLowerLimit.getValue();
}

//! Get the value of the LimitedReal32Counter::_sfLowerLimit field.
template<class Desc> inline
typename LimitedCounterImpl<Desc>::LimitType 
    LimitedCounterImpl<Desc>::getLowerLimit(void) const
{
    return _sfLowerLimit.getValue();
}

//! Set the value of the LimitedReal32Counter::_sfLowerLimit field.
template<class Desc> inline
void LimitedCounterImpl<Desc>::setLowerLimit(const LimitType value)
{
    Self::editSField(LowerLimitFieldMask);

    _sfLowerLimit.setValue(value);
}
//! Get the value of the LimitedReal32Counter::_sfLoop field.

template<class Desc> inline
bool &LimitedCounterImpl<Desc>::editLoop(void)
{
    Self::editSField(LoopFieldMask);

    return _sfLoop.getValue();
}

//! Get the value of the LimitedReal32Counter::_sfLoop field.
template<class Desc> inline
bool  LimitedCounterImpl<Desc>::getLoop(void) const
{
    return _sfLoop.getValue();
}

//! Set the value of the LimitedReal32Counter::_sfLoop field.
template<class Desc> inline
void LimitedCounterImpl<Desc>::setLoop(const bool value)
{
    Self::editSField(LoopFieldMask);

    _sfLoop.setValue(value);
}


template<class Desc> inline
void LimitedCounterImpl<Desc>::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((Self::IncTriggerFieldMask | Self::DecTriggerFieldMask) !=
       (whichField & (Self::IncTriggerFieldMask | Self::DecTriggerFieldMask)))
    {

        if(0x0000 != (whichField & Self::IncTriggerFieldMask))
        {
            if(Self::getValue() > getUpperLimit())
            {
                if(Self::getLoop() == true)
                {
                    Self::setValue(getLowerLimit());
                }
                else
                {
                    Self::setValue(getUpperLimit());
                }

            }
        }
        
        if(0x0000 != (whichField & Self::DecTriggerFieldMask))
        {
            if(Self::getValue() < getLowerLimit())
            {
                if(Self::getLoop() == true)
                {
                    Self::setValue(getUpperLimit());
                }
                else
                {
                    Self::setValue(getLowerLimit());
                }
            }
        }
    }
}


/*------------------------------ access -----------------------------------*/

template<class Desc> inline
SizeT LimitedCounterImpl<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (UpperLimitFieldMask & whichField))
    {
        returnValue += _sfUpperLimit.getBinSize();
    }
    if(FieldBits::NoField != (LowerLimitFieldMask & whichField))
    {
        returnValue += _sfLowerLimit.getBinSize();
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        returnValue += _sfLoop.getBinSize();
    }

    return returnValue;
}

template<class Desc> inline
void LimitedCounterImpl<Desc>::copyToBin(BinaryDataHandler &pMem,
                                         ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (UpperLimitFieldMask & whichField))
    {
        _sfUpperLimit.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LowerLimitFieldMask & whichField))
    {
        _sfLowerLimit.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        _sfLoop.copyToBin(pMem);
    }
}

template<class Desc> inline
void LimitedCounterImpl<Desc>::copyFromBin(BinaryDataHandler &pMem,
                                           ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (UpperLimitFieldMask & whichField))
    {
        _sfUpperLimit.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LowerLimitFieldMask & whichField))
    {
        _sfLowerLimit.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        _sfLoop.copyFromBin(pMem);
    }
}

//! create a new instance of the class
template<class Desc> inline
typename LimitedCounterImpl<Desc>::ObjTransitPtr
    LimitedCounterImpl<Desc>::createLocal(BitVector bFlags)
{
    ObjTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<Self>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
template<class Desc> inline
typename LimitedCounterImpl<Desc>::ObjTransitPtr
    LimitedCounterImpl<Desc>::createDependent(BitVector bFlags)
{
    ObjTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<Self>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
template<class Desc> inline
typename LimitedCounterImpl<Desc>::ObjTransitPtr
    LimitedCounterImpl<Desc>::create(void)
{
    return createLocal();
}

template<class Desc> inline
typename LimitedCounterImpl<Desc>::Self *
    LimitedCounterImpl<Desc>::createEmptyLocal(BitVector bFlags)
{
    Self *returnValue;

    Counter::newPtr<Self>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
template<class Desc> inline
typename LimitedCounterImpl<Desc>::Self *
    LimitedCounterImpl<Desc>::createEmpty(void)
{
    return createEmptyLocal();
}

template<class Desc> inline
FieldContainerTransitPtr LimitedCounterImpl<Desc>::shallowCopyLocal(
    BitVector bFlags) const
{
    Self *tmpPtr;

    Self::newPtr(tmpPtr, dynamic_cast<const Self *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr LimitedCounterImpl<Desc>::shallowCopyDependent(
    BitVector bFlags) const
{
    Self *tmpPtr;

    Self::newPtr(tmpPtr, dynamic_cast<const Self *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr LimitedCounterImpl<Desc>::shallowCopy(void) const
{
    return shallowCopyLocal();
}


template<class Desc> inline
const Char8 *LimitedCounterImpl<Desc>::getClassname(void)
{
    return Desc::getClassname();
}

/*------------------------- constructors ----------------------------------*/

template<class Desc> inline
LimitedCounterImpl<Desc>::LimitedCounterImpl(void) :
     Inherited(),
    _sfUpperLimit             (TypeTraits<LimitType>::getMin()),
    _sfLowerLimit             (TypeTraits<LimitType>::getMax()),
    _sfLoop                   (false)
{
}

template<class Desc> inline
LimitedCounterImpl<Desc>::LimitedCounterImpl(const LimitedCounterImpl &source) :
     Inherited(source),
    _sfUpperLimit             (source._sfUpperLimit             ),
    _sfLowerLimit             (source._sfLowerLimit             ),
    _sfLoop                   (source._sfLoop                   )
{
}


/*-------------------------- destructors ----------------------------------*/

template<class Desc> inline
LimitedCounterImpl<Desc>::~LimitedCounterImpl(void)
{
}

template<class Desc> inline
GetFieldHandlePtr LimitedCounterImpl<Desc>::getHandleUpperLimit(void) const
{
    typename SFLimitType::GetHandlePtr returnValue(
        new typename SFLimitType::GetHandle(
             &_sfUpperLimit,
             this->getType().getFieldDesc(UpperLimitFieldId),
             const_cast<Self *>(this)));
    
    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr LimitedCounterImpl<Desc>::editHandleUpperLimit(void)
{
    typename SFLimitType::EditHandlePtr returnValue(
        new typename SFLimitType::EditHandle(
             &_sfUpperLimit,
             this->getType().getFieldDesc(UpperLimitFieldId),
             this));


    Self::editSField(UpperLimitFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr LimitedCounterImpl<Desc>::getHandleLowerLimit(void) const
{
    typename SFLimitType::GetHandlePtr returnValue(
        new typename SFLimitType::GetHandle(
             &_sfLowerLimit,
             this->getType().getFieldDesc(LowerLimitFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr LimitedCounterImpl<Desc>::editHandleLowerLimit(void)
{
    typename SFLimitType::EditHandlePtr returnValue(
        new typename SFLimitType::EditHandle(
             &_sfLowerLimit,
             this->getType().getFieldDesc(LowerLimitFieldId),
             this));


    Self::editSField(LowerLimitFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr LimitedCounterImpl<Desc>::getHandleLoop(void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfLoop,
             this->getType().getFieldDesc(LoopFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr LimitedCounterImpl<Desc>::editHandleLoop(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfLoop,
             this->getType().getFieldDesc(LoopFieldId),
             this));


    Self::editSField(LoopFieldMask);

    return returnValue;
}



#ifdef OSG_MT_CPTR_ASPECT
template<class Desc> inline
void LimitedCounterImpl<Desc>::execSync (      Self              *pFrom,
                                               ConstFieldMaskArg  whichField,
                                               AspectOffsetStore &oOffsets,
                                               ConstFieldMaskArg  syncMode,
                                         const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (UpperLimitFieldMask & whichField))
        _sfUpperLimit.syncWith(pFrom->_sfUpperLimit);

    if(FieldBits::NoField != (LowerLimitFieldMask & whichField))
        _sfLowerLimit.syncWith(pFrom->_sfLowerLimit);

    if(FieldBits::NoField != (LoopFieldMask & whichField))
        _sfLoop.syncWith(pFrom->_sfLoop);
}

template<class Desc> inline
void LimitedCounterImpl<Desc>::execSyncV(      FieldContainer    &oFrom,
                                               ConstFieldMaskArg  whichField,
                                               AspectOffsetStore &oOffsets,
                                               ConstFieldMaskArg  syncMode,
                                         const UInt32             uiSyncInfo)
{
    Self *pThis = static_cast<Self *>(this);

    pThis->execSync(static_cast<Self *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}

template<class Desc> inline
FieldContainer *LimitedCounterImpl<Desc>::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    Self *returnValue;

    this->newAspectCopy(returnValue,
                        dynamic_cast<const Self *>(pRefAspect),
                        dynamic_cast<const Self *>(this));

    return returnValue;
}
#endif

template<class Desc> inline
void LimitedCounterImpl<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();


}

template<class Desc> inline
void LimitedCounterImpl<Desc>::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


OSG_END_NAMESPACE

