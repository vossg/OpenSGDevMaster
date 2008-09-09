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
UInt32 SValueEmitter<Desc>::getContainerSize(void) const
{
    return sizeof(Self);
}


template<class Desc> inline
typename SValueEmitter<Desc>::SFValueType *
    SValueEmitter<Desc>::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

template<class Desc> inline
const typename SValueEmitter<Desc>::SFValueType *
    SValueEmitter<Desc>::getSFValue(void) const
{
    return &_sfValue;
}

//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename SValueEmitter<Desc>::ValueType &SValueEmitter<Desc>::editValue(void)
{
    editSField(ValueFieldMask);

    return _sfValue.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename SValueEmitter<Desc>::ValueType 
    SValueEmitter<Desc>::getValue(void) const
{
    return _sfValue.getValue();
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void SValueEmitter<Desc>::setValue(const ValueType value)
{
    editSField(ValueFieldMask);

    _sfValue.setValue(value);
}

/*----------------------------- class specific ----------------------------*/

template<class Desc> inline
void SValueEmitter<Desc>::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    if(0x0000 != (whichField & TriggerFieldMask))
    {
        editSField(ValueFieldMask);
    }

    Inherited::changed(whichField, origin, details);
}

/*------------------------------ access -----------------------------------*/

template<class Desc> inline
UInt32 SValueEmitter<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    return returnValue;
}

template<class Desc> inline
void SValueEmitter<Desc>::copyToBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

template<class Desc> inline
void SValueEmitter<Desc>::copyFromBin(BinaryDataHandler &pMem,
                                      ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }
}

//! create a new instance of the class
template<class Desc> inline
typename SValueEmitter<Desc>::ObjTransitPtr 
    SValueEmitter<Desc>::createLocal(BitVector bFlags)
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
typename SValueEmitter<Desc>::ObjTransitPtr SValueEmitter<Desc>::create(void)
{
    ObjTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<Self>(tmpPtr);
    }

    return fc;
}

template<class Desc> inline
typename SValueEmitter<Desc>::Self *
    SValueEmitter<Desc>::createEmptyLocal(BitVector bFlags)
{
    Self *returnValue;

    newPtr<Self>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
template<class Desc> inline
typename SValueEmitter<Desc>::Self *SValueEmitter<Desc>::createEmpty(void)
{
    Self *returnValue;

    newPtr<Self>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


template<class Desc> inline
FieldContainerTransitPtr 
    SValueEmitter<Desc>::shallowCopyLocal(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr SValueEmitter<Desc>::shallowCopy(void) const
{
    Self *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const Self *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}


template<class Desc> inline
const Char8 *SValueEmitter<Desc>::getClassname(void)
{
    return Desc::getClassname();
}

/*------------------------- constructors ----------------------------------*/

template<class Desc> inline
SValueEmitter<Desc>::SValueEmitter(void) :
     Inherited(                  ),
    _sfValue  (Desc::getDefault())
{
}

template<class Desc> inline
SValueEmitter<Desc>::SValueEmitter(const SValueEmitter &source) :
     Inherited(source         ),
    _sfValue  (source._sfValue)
{
}


/*-------------------------- destructors ----------------------------------*/

template<class Desc> inline
SValueEmitter<Desc>::~SValueEmitter(void)
{
}

template<class Desc> inline
GetFieldHandlePtr SValueEmitter<Desc>::getHandleValue(void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SValueEmitter<Desc>::editHandleValue(void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId)));


    editSField(ValueFieldMask);

    return returnValue;
}

#ifdef OSG_MT_CPTR_ASPECT
template<class Desc> inline
void SValueEmitter<Desc>::execSync (      Self              *pFrom,
                                          ConstFieldMaskArg  whichField,
                                          AspectOffsetStore &oOffsets,
                                          ConstFieldMaskArg  syncMode,
                                    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
        _sfValue.syncWith(pFrom->_sfValue);
}

template<class Desc> inline
void SValueEmitter<Desc>::execSyncV(      FieldContainer    &oFrom,
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
FieldContainer *SValueEmitter<Desc>::createAspectCopy(
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
void SValueEmitter<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();


}

template<class Desc> inline
void SValueEmitter<Desc>::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

OSG_END_NAMESPACE

