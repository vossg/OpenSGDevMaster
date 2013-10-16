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
UInt32 SValueMultiplier<Desc>::getContainerSize(void) const
{
    return sizeof(Self);
}


template<class Desc> inline
typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::editSFValue(void)
{
    editSField(ValueFieldMask);

    return &_sfValue;
}

template<class Desc> inline
const typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::getSFValue(void) const
{
    return &_sfValue;
}

//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType &
    SValueMultiplier<Desc>::editValue(void)
{
    editSField(ValueFieldMask);

    return _sfValue.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType 
    SValueMultiplier<Desc>::getValue(void) const
{
    return _sfValue.getValue();
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void SValueMultiplier<Desc>::setValue(const ValueType value)
{
    editSField(ValueFieldMask);

    _sfValue.setValue(value);
}



template<class Desc> inline
typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::editSFLhs(void)
{
    editSField(LhsFieldMask);

    return &_sfLhs;
}

template<class Desc> inline
const typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::getSFLhs(void) const
{
    return &_sfLhs;
}

//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType &
    SValueMultiplier<Desc>::editLhs(void)
{
    editSField(LhsFieldMask);

    return _sfLhs.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType 
    SValueMultiplier<Desc>::getLhs(void) const
{
    return _sfLhs.getValue();
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void SValueMultiplier<Desc>::setLhs(const ValueType value)
{
    editSField(LhsFieldMask);

    _sfLhs.setValue(value);
}



template<class Desc> inline
typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::editSFRhs(void)
{
    editSField(RhsFieldMask);

    return &_sfRhs;
}

template<class Desc> inline
const typename SValueMultiplier<Desc>::SFValueType *
    SValueMultiplier<Desc>::getSFRhs(void) const
{
    return &_sfRhs;
}

//! Get the value of the Real32Counter::_sfValue field.

template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType &
    SValueMultiplier<Desc>::editRhs(void)
{
    editSField(RhsFieldMask);

    return _sfRhs.getValue();
}

//! Get the value of the Real32Counter::_sfValue field.
template<class Desc> inline
typename SValueMultiplier<Desc>::ValueType 
    SValueMultiplier<Desc>::getRhs(void) const
{
    return _sfRhs.getValue();
}

//! Set the value of the Real32Counter::_sfValue field.
template<class Desc> inline
void SValueMultiplier<Desc>::setRhs(const ValueType value)
{
    editSField(RhsFieldMask);

    _sfRhs.setValue(value);
}


/*----------------------------- class specific ----------------------------*/

template<class Desc> inline
void SValueMultiplier<Desc>::changed(ConstFieldMaskArg whichField, 
                                     UInt32            origin,
                                     BitVector         details)
{
    if(0x0000 != (whichField & (LhsFieldMask | RhsFieldMask)))
    {
       
        Desc::multiply(this->editValue(),
                       
                       _sfLhs.getValue(),
                       _sfRhs.getValue());
    }

    Inherited::changed(whichField, origin, details);
}

/*------------------------------ access -----------------------------------*/

template<class Desc> inline
SizeT SValueMultiplier<Desc>::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        returnValue += _sfValue.getBinSize();
    }

    if(FieldBits::NoField != (LhsFieldMask & whichField))
    {
        returnValue += _sfLhs.getBinSize();
    }

    if(FieldBits::NoField != (RhsFieldMask & whichField))
    {
        returnValue += _sfRhs.getBinSize();
    }

    return returnValue;
}

template<class Desc> inline
void SValueMultiplier<Desc>::copyToBin(BinaryDataHandler &pMem,
                                       ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyToBin(pMem);
    }

    if(FieldBits::NoField != (LhsFieldMask & whichField))
    {
        _sfLhs.copyToBin(pMem);
    }

    if(FieldBits::NoField != (RhsFieldMask & whichField))
    {
        _sfRhs.copyToBin(pMem);
    }
}

template<class Desc> inline
void SValueMultiplier<Desc>::copyFromBin(BinaryDataHandler &pMem,
                                         ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
    {
        _sfValue.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (LhsFieldMask & whichField))
    {
        _sfLhs.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (RhsFieldMask & whichField))
    {
        _sfRhs.copyFromBin(pMem);
    }
}

//! create a new instance of the class
template<class Desc> inline
typename SValueMultiplier<Desc>::ObjTransitPtr 
    SValueMultiplier<Desc>::createLocal(BitVector bFlags)
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
typename SValueMultiplier<Desc>::ObjTransitPtr 
    SValueMultiplier<Desc>::createDependent(BitVector bFlags)
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
typename SValueMultiplier<Desc>::ObjTransitPtr 
    SValueMultiplier<Desc>::create(void)
{
    return createLocal();
}

template<class Desc> inline
typename SValueMultiplier<Desc>::Self *
    SValueMultiplier<Desc>::createEmptyLocal(BitVector bFlags)
{
    Self *returnValue;

    newPtr<Self>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
template<class Desc> inline
typename SValueMultiplier<Desc>::Self *SValueMultiplier<Desc>::createEmpty(void)
{
    return createEmptyLocal();
}


template<class Desc> inline
FieldContainerTransitPtr 
    SValueMultiplier<Desc>::shallowCopyLocal(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr 
    SValueMultiplier<Desc>::shallowCopyDependent(BitVector bFlags) const
{
    Self *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Self *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

template<class Desc> inline
FieldContainerTransitPtr SValueMultiplier<Desc>::shallowCopy(void) const
{
    return shallowCopyLocal();
}


template<class Desc> inline
const Char8 *SValueMultiplier<Desc>::getClassname(void)
{
    return Desc::getClassname();
}

/*------------------------- constructors ----------------------------------*/

template<class Desc> inline
SValueMultiplier<Desc>::SValueMultiplier(void) :
     Inherited         (                  ),
    _sfValue           (Desc::getDefault()),
    _sfLhs             (Desc::getDefault()),
    _sfRhs             (Desc::getDefault())
{
}

template<class Desc> inline
SValueMultiplier<Desc>::SValueMultiplier(const SValueMultiplier &source) :
     Inherited         (source                    ),
    _sfValue           (source._sfValue           ),
    _sfLhs             (source._sfLhs             ),
    _sfRhs             (source._sfRhs             )
{
}


/*-------------------------- destructors ----------------------------------*/

template<class Desc> inline
SValueMultiplier<Desc>::~SValueMultiplier(void)
{
}

template<class Desc> inline
GetFieldHandlePtr SValueMultiplier<Desc>::getHandleValue(void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SValueMultiplier<Desc>::editHandleValue(void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfValue,
             this->getType().getFieldDesc(ValueFieldId),
             this));


    editSField(ValueFieldMask);

    return returnValue;
}


template<class Desc> inline
GetFieldHandlePtr SValueMultiplier<Desc>::getHandleLhs(void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfLhs,
             this->getType().getFieldDesc(LhsFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SValueMultiplier<Desc>::editHandleLhs(void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfLhs,
             this->getType().getFieldDesc(LhsFieldId),
             this));


    editSField(LhsFieldMask);

    return returnValue;
}


template<class Desc> inline
GetFieldHandlePtr SValueMultiplier<Desc>::getHandleRhs(void) const
{
    typename SFValueType::GetHandlePtr returnValue(
        new typename SFValueType::GetHandle(
             &_sfRhs,
             this->getType().getFieldDesc(RhsFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template<class Desc> inline
EditFieldHandlePtr SValueMultiplier<Desc>::editHandleRhs(void)
{
    typename SFValueType::EditHandlePtr returnValue(
        new typename SFValueType::EditHandle(
             &_sfRhs,
             this->getType().getFieldDesc(RhsFieldId),
             this));


    editSField(RhsFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
template<class Desc> inline
void SValueMultiplier<Desc>::execSync (      Self              *pFrom,
                                             ConstFieldMaskArg  whichField,
                                             AspectOffsetStore &oOffsets,
                                             ConstFieldMaskArg  syncMode,
                                       const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ValueFieldMask & whichField))
        _sfValue.syncWith(pFrom->_sfValue);

    if(FieldBits::NoField != (LhsFieldMask & whichField))
        _sfLhs.syncWith(pFrom->_sfLhs);

    if(FieldBits::NoField != (RhsFieldMask & whichField))
        _sfRhs.syncWith(pFrom->_sfRhs);
}

template<class Desc> inline
void SValueMultiplier<Desc>::execSyncV(      FieldContainer    &oFrom,
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
FieldContainer *SValueMultiplier<Desc>::createAspectCopy(
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
void SValueMultiplier<Desc>::resolveLinks(void)
{
    Inherited::resolveLinks();


}

template<class Desc> inline
void SValueMultiplier<Desc>::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

OSG_END_NAMESPACE

