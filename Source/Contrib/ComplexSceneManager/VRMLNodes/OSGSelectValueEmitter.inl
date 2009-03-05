
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
UInt32 SelectSValueEmitter<Desc>::getContainerSize(void) const
{
    return sizeof(Self);
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::SFChoiceType *
    SelectSValueEmitter<Desc>::editSFChoice(void)
{
    editSField(ChoiceFieldMask);

    return &_sfChoice;
}

template<class Desc> inline
const typename SelectSValueEmitter<Desc>::SFChoiceType *
    SelectSValueEmitter<Desc>::getSFChoice(void) const
{
    return &_sfChoice;
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::ChoiceType &
    SelectSValueEmitter<Desc>::editChoice(void)
{
    editSField(ChoiceFieldMask);

    return _sfChoice.getValue();
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::ChoiceType
    SelectSValueEmitter<Desc>::getChoice(void) const
{
    return _sfChoice.getValue();
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::MFChoiceValuesType *
    SelectSValueEmitter<Desc>::editMFChoiceValues(void)
{
    editMField(ChoiceValuesFieldMask, _mfChoiceValues);
    
    return &_mfChoiceValues;
}

template<class Desc> inline
const typename SelectSValueEmitter<Desc>::MFChoiceValuesType *
    SelectSValueEmitter<Desc>::getMFChoiceValues(void) const
{
    return &_mfChoiceValues;
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::ChoiceValuesType &
    SelectSValueEmitter<Desc>::editChoiceValue(const UInt32 index)
{
    editMField(ChoiceValuesFieldMask, _mfChoiceValues);

    return _mfChoiceValues[index];
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::ChoiceValuesType    
    SelectSValueEmitter<Desc>::getChoiceValue(const UInt32 index) const
{
    return _mfChoiceValues[index];
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::SFValueType *
    SelectSValueEmitter<Desc>::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

template<class Desc> inline
const typename SelectSValueEmitter<Desc>::SFValueType *
    SelectSValueEmitter<Desc>::getSFValue(void) const
{
    return &_sfValue;
}

//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename SelectSValueEmitter<Desc>::ValueType &
    SelectSValueEmitter<Desc>::editValue(void)
{
    editSField(ValueFieldMask);

    return _sfValue.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename SelectSValueEmitter<Desc>::ValueType 
    SelectSValueEmitter<Desc>::getValue(void) const
{
    return _sfValue.getValue();
}

template<class Desc> inline
void SelectSValueEmitter<Desc>::setChoice(const ChoiceType choice)
{
    editSField(ChoiceFieldMask);

    _sfChoice.setValue(choice);
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void SelectSValueEmitter<Desc>::setValue(const ValueType value)
{
    editSField(ValueFieldMask);

    _sfValue.setValue(value);
}

template<class Desc> inline
SFBool *SelectSValueEmitter<Desc>::editSFIgnoreNextChange(void)
{
    editSField(IgnoreNextChangeFieldMask);

    return &_sfIgnoreNextChange;
}

template<class Desc> inline
const SFBool *SelectSValueEmitter<Desc>::getSFIgnoreNextChange (void) const
{
    return &_sfIgnoreNextChange;
}

/*----------------------------- class specific ----------------------------*/

template<class Desc> inline
void SelectSValueEmitter<Desc>::changed(ConstFieldMaskArg whichField, 
                                        UInt32            origin,
                                        BitVector         details)
{
    if(0x0000 != (whichField & TriggerFieldMask))
    {
        editSField(ValueFieldMask);
    }

    if(0x0000 != (whichField & (ChoiceFieldMask | ChoiceValuesFieldMask)))
    {
        if(_sfChoice.getValue() < _mfChoiceValues.size())
        {            
            setValue(Desc::convert(_mfChoiceValues[_sfChoice.getValue()]));
        }
    }

    if(0x0000 != (whichField & IgnoreNextChangeFieldMask))
    {
        if(_sfIgnoreNextChange.getValue() == false)
        {
            Inherited::changed(whichField, origin, details);
        }
    }
    else
    {
        Inherited::changed(whichField, origin, details);
    }
}

/*------------------------------ access -----------------------------------*/
template<class Desc> inline
UInt32 SelectSValueEmitter<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        returnValue += _sfChoice.getBinSize();
    }

    if(FieldBits::NoField != (ChoiceValuesFieldMask & whichField))
    {
        returnValue += _mfChoiceValues.getBinSize();
    }

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }


    return returnValue;
}

template<class Desc> inline
void SelectSValueEmitter<Desc>::copyToBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        _sfChoice.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ChoiceValuesFieldMask & whichField))
    {
        _mfChoiceValues.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }
}

template<class Desc> inline
void SelectSValueEmitter<Desc>::copyFromBin(BinaryDataHandler &pMem,
                                            ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
    {
        _sfChoice.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ChoiceValuesFieldMask & whichField))
    {
        _mfChoiceValues.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }
}


//! create a new instance of the class
template<class Desc> inline
typename SelectSValueEmitter<Desc>::ObjTransitPtr 
    SelectSValueEmitter<Desc>::createLocal(BitVector bFlags)
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
typename SelectSValueEmitter<Desc>::ObjTransitPtr 
    SelectSValueEmitter<Desc>::createDependent(BitVector bFlags)
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
typename SelectSValueEmitter<Desc>::ObjTransitPtr 
    SelectSValueEmitter<Desc>::create(void)
{
    return createLocal();
}

template<class Desc> inline
typename SelectSValueEmitter<Desc>::Self *
    SelectSValueEmitter<Desc>::createEmptyLocal(BitVector bFlags)
{
    Self *returnValue;

    newPtr<Self>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
template<class Desc> inline
typename SelectSValueEmitter<Desc>::Self *
    SelectSValueEmitter<Desc>::createEmpty(void)
{
    return createEmptyLocal();
}


template<class Desc> inline
FieldContainerTransitPtr 
    SelectSValueEmitter<Desc>::shallowCopyLocal(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr 
    SelectSValueEmitter<Desc>::shallowCopyDependent(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr SelectSValueEmitter<Desc>::shallowCopy(void) const
{
    return shallowCopyLocal();
}


template<class Desc> inline
const Char8 *SelectSValueEmitter<Desc>::getClassname(void)
{
    return Desc::getClassname();
}

/*------------------------- constructors ----------------------------------*/

template<class Desc> inline
SelectSValueEmitter<Desc>::SelectSValueEmitter(void) :
     Inherited         (                  ),
    _sfChoice          (                  ),
    _mfChoiceValues    (                  ),
    _sfValue           (Desc::getDefault()),
    _sfIgnoreNextChange(false             )
{
}

template<class Desc> inline
SelectSValueEmitter<Desc>::SelectSValueEmitter(
    const SelectSValueEmitter &source) :

     Inherited         (source                    ),
    _sfChoice          (source._sfChoice          ),
    _mfChoiceValues    (source._mfChoiceValues    ),
    _sfValue           (source._sfValue           ),
    _sfIgnoreNextChange(source._sfIgnoreNextChange)
{
}


/*-------------------------- destructors ----------------------------------*/

template<class Desc> inline
SelectSValueEmitter<Desc>::~SelectSValueEmitter(void)
{
}

template<class Desc> inline
GetFieldHandlePtr  SelectSValueEmitter<Desc>::getHandleChoice(void) const
{
    typename SFChoiceType::GetHandlePtr returnValue(
        new typename SFChoiceType::GetHandle(
             &_sfChoice,
             this->getType().getFieldDesc(ChoiceFieldId)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SelectSValueEmitter<Desc>::editHandleChoice(void)
{
    typename SFChoiceType::EditHandlePtr returnValue(
        new typename SFChoiceType::EditHandle(
             &_sfChoice,
             this->getType().getFieldDesc(ChoiceFieldId)));


    editSField(ChoiceFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr  SelectSValueEmitter<Desc>::getHandleChoiceValues(void) const
{
    typename MFChoiceValuesType::GetHandlePtr returnValue(
        new typename MFChoiceValuesType::GetHandle(
             &_mfChoiceValues,
             this->getType().getFieldDesc(ChoiceValuesFieldId)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SelectSValueEmitter<Desc>::editHandleChoiceValues(void)
{
    typename MFChoiceValuesType::EditHandlePtr returnValue(
        new typename MFChoiceValuesType::EditHandle(
             &_mfChoiceValues,
             this->getType().getFieldDesc(ChoiceValuesFieldId)));


    editMField(ChoiceValuesFieldMask, _mfChoiceValues);

    return returnValue;
}
  
template<class Desc> inline
GetFieldHandlePtr SelectSValueEmitter<Desc>::getHandleValue(void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SelectSValueEmitter<Desc>::editHandleValue(void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId)));


    editSField(ValueFieldMask);

    return returnValue;
}

template<class Desc> inline
GetFieldHandlePtr 
    SelectSValueEmitter<Desc>::getHandleIgnoreNextChange (void) const
{
    typename SFBool::GetHandlePtr returnValue(
        new typename SFBool::GetHandle(
             &_sfIgnoreNextChange,
             this->getType().getFieldDesc(IgnoreNextChangeFieldId)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SelectSValueEmitter<Desc>::editHandleIgnoreNextChange(void)
{
    typename SFBool::EditHandlePtr returnValue(
        new typename SFBool::EditHandle(
             &_sfIgnoreNextChange,
             this->getType().getFieldDesc(IgnoreNextChangeFieldId)));


    editSField(IgnoreNextChangeFieldMask);

    return returnValue;
}

#ifdef OSG_MT_CPTR_ASPECT
template<class Desc> inline
void SelectSValueEmitter<Desc>::execSync (      Self              *pFrom,
                                                ConstFieldMaskArg  whichField,
                                                AspectOffsetStore &oOffsets,
                                                ConstFieldMaskArg  syncMode,
                                          const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ChoiceFieldMask & whichField))
        _sfChoice.syncWith(pFrom->_sfChoice);

    if(FieldBits::NoField != (ChoiceValuesFieldMask & whichField))
    {
        _mfChoiceValues.syncWith(pFrom->_mfChoiceValues,
                                 syncMode,
                                 uiSyncInfo,
                                 oOffsets);
    }

    if(FieldBits::NoField != (ValueFieldMask & whichField))
        _sfValue.syncWith(pFrom->_sfValue);
}

template<class Desc> inline
void SelectSValueEmitter<Desc>::execSyncV(      FieldContainer    &oFrom,
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
FieldContainer *SelectSValueEmitter<Desc>::createAspectCopy(
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
void SelectSValueEmitter<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();


}

template<class Desc> inline
void SelectSValueEmitter<Desc>::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}
OSG_END_NAMESPACE

