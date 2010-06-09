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
UInt32 CounterImpl<Desc>::getContainerSize(void) const
{
    return sizeof(Self);
}

/*------------------------------ get -----------------------------------*/

template<class Desc> inline
typename CounterImpl<Desc>::SFValueType *CounterImpl<Desc>::editSFStep(void)
{
    editSField(StepFieldMask);

    return &_sfStep;
}

template<class Desc> inline
const typename CounterImpl<Desc>::SFValueType *
    CounterImpl<Desc>::getSFStep(void) const
{
    return &_sfStep;
}


template<class Desc> inline
typename CounterImpl<Desc>::SFValueType * 
    CounterImpl<Desc>::editSFResetValue(void)
{
    editSField(ResetValueFieldMask);

    return &_sfResetValue;
}

template<class Desc> inline
const typename CounterImpl<Desc>::SFValueType *
    CounterImpl<Desc>::getSFResetValue(void) const
{
    return &_sfResetValue;
}


template<class Desc> inline
typename CounterImpl<Desc>::SFValueType *CounterImpl<Desc>::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

template<class Desc> inline
const typename CounterImpl<Desc>::SFValueType *
    CounterImpl<Desc>::getSFValue(void) const
{
    return &_sfValue;
}

//! Get the value of the Real32Counter::_sfStep field.

template<class Desc> inline
typename CounterImpl<Desc>::ValueType &CounterImpl<Desc>::editStep(void)
{
    editSField(StepFieldMask);

    return _sfStep.getValue();
}

//! Get the value of the Real32Counter::_sfStep field.
template<class Desc> inline
typename CounterImpl<Desc>::ValueType CounterImpl<Desc>::getStep(void) const
{
    return _sfStep.getValue();
}

//! Set the value of the Real32Counter::_sfStep field.
template<class Desc> inline
void CounterImpl<Desc>::setStep(const ValueType value)
{
    editSField(StepFieldMask);

    _sfStep.setValue(value);
}
//! Get the value of the Real32Counter::_sfResetValue field.

template<class Desc> inline
typename CounterImpl<Desc>::ValueType &CounterImpl<Desc>::editResetValue(void)
{
    editSField(ResetValueFieldMask);

    return _sfResetValue.getValue();
}

//! Get the value of the Real32Counter::_sfResetValue field.
template<class Desc> inline
typename CounterImpl<Desc>::ValueType 
    CounterImpl<Desc>::getResetValue(void) const
{
    return _sfResetValue.getValue();
}

//! Set the value of the Real32Counter::_sfResetValue field.
template<class Desc> inline
void CounterImpl<Desc>::setResetValue(const ValueType value)
{
    editSField(ResetValueFieldMask);

    _sfResetValue.setValue(value);
}
//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename CounterImpl<Desc>::ValueType &CounterImpl<Desc>::editValue(void)
{
    editSField(ValueFieldMask);

    return _sfValue.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename CounterImpl<Desc>::ValueType CounterImpl<Desc>::getValue(void) const
{
    return _sfValue.getValue();
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void CounterImpl<Desc>::setValue(const ValueType value)
{
    editSField(ValueFieldMask);

    _sfValue.setValue(value);
}

/*----------------------------- class specific ----------------------------*/

template<class Desc> inline
void CounterImpl<Desc>::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    if((IncTriggerFieldMask | DecTriggerFieldMask) !=
       (whichField & (IncTriggerFieldMask | DecTriggerFieldMask)))
    {

        if(0x0000 != (whichField & IncTriggerFieldMask))
        {
            setValue(getValue() + getStep());
        }
        
        if(0x0000 != (whichField & DecTriggerFieldMask))
        {
            setValue(getValue() - getStep());
        }
    }

    Inherited::changed(whichField, origin, details);
}

/*------------------------------ access -----------------------------------*/

template<class Desc> inline
UInt32 CounterImpl<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (StepFieldMask & whichField))
    {
        returnValue += _sfStep.getBinSize();
    }
    if(FieldBits::NoField != (ResetValueFieldMask & whichField))
    {
        returnValue += _sfResetValue.getBinSize();
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    return returnValue;
}

template<class Desc> inline
void CounterImpl<Desc>::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (StepFieldMask & whichField))
    {
        _sfStep.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ResetValueFieldMask & whichField))
    {
        _sfResetValue.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

template<class Desc> inline
void CounterImpl<Desc>::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (StepFieldMask & whichField))
    {
        _sfStep.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ResetValueFieldMask & whichField))
    {
        _sfResetValue.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }
}


//! create a new instance of the class
template<class Desc> inline
typename CounterImpl<Desc>::ObjTransitPtr 
    CounterImpl<Desc>::createLocal(BitVector bFlags)
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
typename CounterImpl<Desc>::ObjTransitPtr 
    CounterImpl<Desc>::createDependent(BitVector bFlags)
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
typename CounterImpl<Desc>::ObjTransitPtr CounterImpl<Desc>::create(void)
{
#if 0
    ObjTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<Self>(tmpPtr);
    }

    return fc;
#else
    return createLocal();
#endif
}

template<class Desc> inline
typename CounterImpl<Desc>::Self *
    CounterImpl<Desc>::createEmptyLocal(BitVector bFlags)
{
    Self *returnValue;

    newPtr<Self>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
template<class Desc> inline
typename CounterImpl<Desc>::Self *CounterImpl<Desc>::createEmpty(void)
{
#if 0
    Self *returnValue;

    newPtr<Self>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
#else
    return createEmptyLocal();
#endif
}


template<class Desc> inline
FieldContainerTransitPtr 
    CounterImpl<Desc>::shallowCopyLocal(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr 
    CounterImpl<Desc>::shallowCopyDependent(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr CounterImpl<Desc>::shallowCopy(void) const
{
#if 0
    Self *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const Self *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
#else
    return shallowCopyLocal();
#endif
}


template<class Desc> inline
const Char8 *CounterImpl<Desc>::getClassname(void)
{
    return Desc::getClassname();
}

/*------------------------- constructors ----------------------------------*/

template<class Desc> inline
CounterImpl<Desc>::CounterImpl(void) :
    Inherited(),
    _sfStep                   (TypeTraits<ValueType>::getOneElement ()),
    _sfResetValue             (TypeTraits<ValueType>::getZeroElement()),
    _sfValue                  (TypeTraits<ValueType>::getZeroElement())
{
}

template<class Desc> inline
CounterImpl<Desc>::CounterImpl(const CounterImpl &source) :
    Inherited(source),
    _sfStep                   (source._sfStep                   ),
    _sfResetValue             (source._sfResetValue             ),
    _sfValue                  (source._sfValue                  )
{
}


/*-------------------------- destructors ----------------------------------*/

template<class Desc> inline
CounterImpl<Desc>::~CounterImpl(void)
{
}

template<class Desc> inline
GetFieldHandlePtr CounterImpl<Desc>::getHandleStep            (void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfStep,
             this->getType().getFieldDesc(StepFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr CounterImpl<Desc>::editHandleStep           (void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfStep,
             this->getType().getFieldDesc(StepFieldId),
             this));


    editSField(StepFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr CounterImpl<Desc>::getHandleResetValue      (void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfResetValue,
             this->getType().getFieldDesc(ResetValueFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr CounterImpl<Desc>::editHandleResetValue     (void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfResetValue,
             this->getType().getFieldDesc(ResetValueFieldId),
             this));


    editSField(ResetValueFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr CounterImpl<Desc>::getHandleValue           (void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr CounterImpl<Desc>::editHandleValue          (void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             this));


    editSField(ValueFieldMask);

    return returnValue;
}

#ifdef OSG_MT_CPTR_ASPECT
template<class Desc> inline
void CounterImpl<Desc>::execSync (  Self              *pFrom,
                                    ConstFieldMaskArg  whichField,
                                    AspectOffsetStore &oOffsets,
                                    ConstFieldMaskArg  syncMode,
                              const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (StepFieldMask & whichField))
        _sfStep.syncWith(pFrom->_sfStep);

    if(FieldBits::NoField != (ResetValueFieldMask & whichField))
        _sfResetValue.syncWith(pFrom->_sfResetValue);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
        _sfValue.syncWith(pFrom->_sfValue);
}

template<class Desc> inline
void CounterImpl<Desc>::execSyncV(  FieldContainer    &oFrom,
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
FieldContainer *CounterImpl<Desc>::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    Self *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const Self *>(pRefAspect),
                  dynamic_cast<const Self *>(this));

    return returnValue;
}

#endif

template<class Desc> inline
void CounterImpl<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();


}

template<class Desc> inline
void CounterImpl<Desc>::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


OSG_END_NAMESPACE

