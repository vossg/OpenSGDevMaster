/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class MultiSwitch!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGMultiSwitchBase.h"
#include "OSGMultiSwitch.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::MultiSwitch
    MultiSwitch allows the selective inclusion of zero or more of its children from
    traversal. It supports three different modes (selected by _sfSwitchMode), to
    include either ALL, NONE or CHOICES of its children.
 */

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

/*! \var UInt32          MultiSwitchBase::_mfChoices
    Indices of children to be included in CHOICES mode. The indices are kept
    sorted and any duplicates are removed.
*/

/*! \var Int32           MultiSwitchBase::_sfSwitchMode
    Mode of operation.
*/


void MultiSwitchBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "choices",
        "Indices of children to be included in CHOICES mode. The indices are kept\n"
        "sorted and any duplicates are removed.\n",
        ChoicesFieldId, ChoicesFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MultiSwitch::editHandleChoices),
        static_cast<FieldGetMethodSig >(&MultiSwitch::getHandleChoices));

    oType.addInitialDesc(pDesc);

    pDesc = new SFInt32::Description(
        SFInt32::getClassType(),
        "switchMode",
        "Mode of operation.\n",
        SwitchModeFieldId, SwitchModeFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&MultiSwitch::editHandleSwitchMode),
        static_cast<FieldGetMethodSig >(&MultiSwitch::getHandleSwitchMode));

    oType.addInitialDesc(pDesc);
}


MultiSwitchBase::TypeObject MultiSwitchBase::_type(
    MultiSwitchBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&MultiSwitchBase::createEmptyLocal),
    MultiSwitch::initMethod,
    MultiSwitch::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&MultiSwitchBase::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "\tname=\"MultiSwitch\"\n"
    "\tparent=\"Group\"\n"
    "\tlibrary=\"System\"\n"
    "\tpointerfieldtypes=\"both\"\n"
    "\tstructure=\"concrete\"\n"
    "\tsystemcomponent=\"true\"\n"
    "\tparentsystemcomponent=\"true\"\n"
    "\tdecoratable=\"false\"\n"
    ">\n"
    "MultiSwitch allows the selective inclusion of zero or more of its children from\n"
    "traversal. It supports three different modes (selected by _sfSwitchMode), to\n"
    "include either ALL, NONE or CHOICES of its children.\n"
    "\t<Field\n"
    "\t\tname=\"choices\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "    Indices of children to be included in CHOICES mode. The indices are kept\n"
    "    sorted and any duplicates are removed.\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"switchMode\"\n"
    "\t\ttype=\"Int32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\tdefaultValue=\"-1\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "    Mode of operation.\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    "MultiSwitch allows the selective inclusion of zero or more of its children from\n"
    "traversal. It supports three different modes (selected by _sfSwitchMode), to\n"
    "include either ALL, NONE or CHOICES of its children.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &MultiSwitchBase::getType(void)
{
    return _type;
}

const FieldContainerType &MultiSwitchBase::getType(void) const
{
    return _type;
}

UInt32 MultiSwitchBase::getContainerSize(void) const
{
    return sizeof(MultiSwitch);
}

/*------------------------- decorator get ------------------------------*/


MFUInt32 *MultiSwitchBase::editMFChoices(void)
{
    editMField(ChoicesFieldMask, _mfChoices);

    return &_mfChoices;
}

const MFUInt32 *MultiSwitchBase::getMFChoices(void) const
{
    return &_mfChoices;
}


SFInt32 *MultiSwitchBase::editSFSwitchMode(void)
{
    editSField(SwitchModeFieldMask);

    return &_sfSwitchMode;
}

const SFInt32 *MultiSwitchBase::getSFSwitchMode(void) const
{
    return &_sfSwitchMode;
}






/*------------------------------ access -----------------------------------*/

UInt32 MultiSwitchBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChoicesFieldMask & whichField))
    {
        returnValue += _mfChoices.getBinSize();
    }
    if(FieldBits::NoField != (SwitchModeFieldMask & whichField))
    {
        returnValue += _sfSwitchMode.getBinSize();
    }

    return returnValue;
}

void MultiSwitchBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChoicesFieldMask & whichField))
    {
        _mfChoices.copyToBin(pMem);
    }
    if(FieldBits::NoField != (SwitchModeFieldMask & whichField))
    {
        _sfSwitchMode.copyToBin(pMem);
    }
}

void MultiSwitchBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChoicesFieldMask & whichField))
    {
        _mfChoices.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (SwitchModeFieldMask & whichField))
    {
        _sfSwitchMode.copyFromBin(pMem);
    }
}

//! create a new instance of the class
MultiSwitchTransitPtr MultiSwitchBase::createLocal(BitVector bFlags)
{
    MultiSwitchTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<MultiSwitch>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
MultiSwitchTransitPtr MultiSwitchBase::create(void)
{
    MultiSwitchTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<MultiSwitch>(tmpPtr);
    }

    return fc;
}

MultiSwitch *MultiSwitchBase::createEmptyLocal(BitVector bFlags)
{
    MultiSwitch *returnValue;

    newPtr<MultiSwitch>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
MultiSwitch *MultiSwitchBase::createEmpty(void)
{
    MultiSwitch *returnValue;

    newPtr<MultiSwitch>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr MultiSwitchBase::shallowCopyLocal(
    BitVector bFlags) const
{
    MultiSwitch *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const MultiSwitch *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr MultiSwitchBase::shallowCopy(void) const
{
    MultiSwitch *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const MultiSwitch *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

MultiSwitchBase::MultiSwitchBase(void) :
    Inherited(),
    _mfChoices                (),
    _sfSwitchMode             (Int32(-1))
{
}

MultiSwitchBase::MultiSwitchBase(const MultiSwitchBase &source) :
    Inherited(source),
    _mfChoices                (source._mfChoices                ),
    _sfSwitchMode             (source._sfSwitchMode             )
{
}


/*-------------------------- destructors ----------------------------------*/

MultiSwitchBase::~MultiSwitchBase(void)
{
}


GetFieldHandlePtr MultiSwitchBase::getHandleChoices         (void) const
{
    MFUInt32::GetHandlePtr returnValue(
        new  MFUInt32::GetHandle(
             &_mfChoices,
             this->getType().getFieldDesc(ChoicesFieldId)));

    return returnValue;
}

EditFieldHandlePtr MultiSwitchBase::editHandleChoices        (void)
{
    MFUInt32::EditHandlePtr returnValue(
        new  MFUInt32::EditHandle(
             &_mfChoices,
             this->getType().getFieldDesc(ChoicesFieldId)));


    editMField(ChoicesFieldMask, _mfChoices);

    return returnValue;
}

GetFieldHandlePtr MultiSwitchBase::getHandleSwitchMode      (void) const
{
    SFInt32::GetHandlePtr returnValue(
        new  SFInt32::GetHandle(
             &_sfSwitchMode,
             this->getType().getFieldDesc(SwitchModeFieldId)));

    return returnValue;
}

EditFieldHandlePtr MultiSwitchBase::editHandleSwitchMode     (void)
{
    SFInt32::EditHandlePtr returnValue(
        new  SFInt32::EditHandle(
             &_sfSwitchMode,
             this->getType().getFieldDesc(SwitchModeFieldId)));


    editSField(SwitchModeFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void MultiSwitchBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    MultiSwitch *pThis = static_cast<MultiSwitch *>(this);

    pThis->execSync(static_cast<MultiSwitch *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *MultiSwitchBase::createAspectCopy(void) const
{
    MultiSwitch *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const MultiSwitch *>(this));

    return returnValue;
}
#endif

void MultiSwitchBase::resolveLinks(void)
{
    Inherited::resolveLinks();

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfChoices.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<MultiSwitch *>::_type("MultiSwitchPtr", "GroupPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(MultiSwitch *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           MultiSwitch *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           MultiSwitch *,
                           0);

OSG_END_NAMESPACE
