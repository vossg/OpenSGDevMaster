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
 **     class TimeSensor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include <OSGConfig.h>




#include "OSGTimeSensorBase.h"
#include "OSGTimeSensor.h"

#include "boost/bind.hpp"

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TimeSensor
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var bool            TimeSensorBase::_sfEnabled
    
*/

/*! \var bool            TimeSensorBase::_sfIsActive
    
*/

/*! \var bool            TimeSensorBase::_sfLoop
    
*/

/*! \var Real32          TimeSensorBase::_sfFraction
    
*/

/*! \var Time            TimeSensorBase::_sfStartTime
    
*/

/*! \var Time            TimeSensorBase::_sfStopTime
    
*/

/*! \var Time            TimeSensorBase::_sfCycleTime
    
*/

/*! \var Time            TimeSensorBase::_sfTime
    
*/

/*! \var Time            TimeSensorBase::_sfCycleInterval
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<TimeSensor *>::_type("TimeSensorPtr", "NodeCorePtr");
#endif

OSG_FIELDTRAITS_GETTYPE(TimeSensor *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           TimeSensor *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           TimeSensor *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void TimeSensorBase::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "enabled",
        "",
        EnabledFieldId, EnabledFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleEnabled),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleEnabled));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "isActive",
        "",
        IsActiveFieldId, IsActiveFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleIsActive),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleIsActive));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "loop",
        "",
        LoopFieldId, LoopFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleLoop),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleLoop));

    oType.addInitialDesc(pDesc);

    pDesc = new SFReal32::Description(
        SFReal32::getClassType(),
        "fraction",
        "",
        FractionFieldId, FractionFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleFraction),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleFraction));

    oType.addInitialDesc(pDesc);

    pDesc = new SFTime::Description(
        SFTime::getClassType(),
        "startTime",
        "",
        StartTimeFieldId, StartTimeFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleStartTime),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleStartTime));

    oType.addInitialDesc(pDesc);

    pDesc = new SFTime::Description(
        SFTime::getClassType(),
        "stopTime",
        "",
        StopTimeFieldId, StopTimeFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleStopTime),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleStopTime));

    oType.addInitialDesc(pDesc);

    pDesc = new SFTime::Description(
        SFTime::getClassType(),
        "cycleTime",
        "",
        CycleTimeFieldId, CycleTimeFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleCycleTime),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleCycleTime));

    oType.addInitialDesc(pDesc);

    pDesc = new SFTime::Description(
        SFTime::getClassType(),
        "time",
        "",
        TimeFieldId, TimeFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleTime),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleTime));

    oType.addInitialDesc(pDesc);

    pDesc = new SFTime::Description(
        SFTime::getClassType(),
        "cycleInterval",
        "",
        CycleIntervalFieldId, CycleIntervalFieldMask,
        true,
        (Field::FThreadLocal),
        static_cast<FieldEditMethodSig>(&TimeSensor::editHandleCycleInterval),
        static_cast<FieldGetMethodSig >(&TimeSensor::getHandleCycleInterval));

    oType.addInitialDesc(pDesc);
}


TimeSensorBase::TypeObject TimeSensorBase::_type(
    TimeSensorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&TimeSensorBase::createEmptyLocal),
    TimeSensor::initMethod,
    TimeSensor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&TimeSensor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"TimeSensor\"\n"
    "    parent=\"NodeCore\"\n"
    "    mixinparent=\"NodeCoreSensorParent\"\n"
    "    library=\"Dynamics\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"true\"\n"
    "    isBundle=\"false\"\n"
    "    parentFields=\"none\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"enabled\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"true\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    " \t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"isActive\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"false\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"loop\"\n"
    "\t\ttype=\"bool\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"false\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"fraction\"\n"
    "\t\ttype=\"Real32\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"startTime\"\n"
    "\t\ttype=\"Time\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"stopTime\"\n"
    "\t\ttype=\"Time\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"cycleTime\"\n"
    "\t\ttype=\"Time\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"time\"\n"
    "\t\ttype=\"Time\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"0.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"cycleInterval\"\n"
    "\t\ttype=\"Time\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "        defaultValue=\"1.0\"\n"
    "        fieldFlags=\"FThreadLocal\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &TimeSensorBase::getType(void)
{
    return _type;
}

const FieldContainerType &TimeSensorBase::getType(void) const
{
    return _type;
}

UInt32 TimeSensorBase::getContainerSize(void) const
{
    return sizeof(TimeSensor);
}

/*------------------------- decorator get ------------------------------*/


SFBool *TimeSensorBase::editSFEnabled(void)
{
    editSField(EnabledFieldMask);

    return &_sfEnabled;
}

const SFBool *TimeSensorBase::getSFEnabled(void) const
{
    return &_sfEnabled;
}


SFBool *TimeSensorBase::editSFIsActive(void)
{
    editSField(IsActiveFieldMask);

    return &_sfIsActive;
}

const SFBool *TimeSensorBase::getSFIsActive(void) const
{
    return &_sfIsActive;
}


SFBool *TimeSensorBase::editSFLoop(void)
{
    editSField(LoopFieldMask);

    return &_sfLoop;
}

const SFBool *TimeSensorBase::getSFLoop(void) const
{
    return &_sfLoop;
}


SFReal32 *TimeSensorBase::editSFFraction(void)
{
    editSField(FractionFieldMask);

    return &_sfFraction;
}

const SFReal32 *TimeSensorBase::getSFFraction(void) const
{
    return &_sfFraction;
}


SFTime *TimeSensorBase::editSFStartTime(void)
{
    editSField(StartTimeFieldMask);

    return &_sfStartTime;
}

const SFTime *TimeSensorBase::getSFStartTime(void) const
{
    return &_sfStartTime;
}


SFTime *TimeSensorBase::editSFStopTime(void)
{
    editSField(StopTimeFieldMask);

    return &_sfStopTime;
}

const SFTime *TimeSensorBase::getSFStopTime(void) const
{
    return &_sfStopTime;
}


SFTime *TimeSensorBase::editSFCycleTime(void)
{
    editSField(CycleTimeFieldMask);

    return &_sfCycleTime;
}

const SFTime *TimeSensorBase::getSFCycleTime(void) const
{
    return &_sfCycleTime;
}


SFTime *TimeSensorBase::editSFTime(void)
{
    editSField(TimeFieldMask);

    return &_sfTime;
}

const SFTime *TimeSensorBase::getSFTime(void) const
{
    return &_sfTime;
}


SFTime *TimeSensorBase::editSFCycleInterval(void)
{
    editSField(CycleIntervalFieldMask);

    return &_sfCycleInterval;
}

const SFTime *TimeSensorBase::getSFCycleInterval(void) const
{
    return &_sfCycleInterval;
}






/*------------------------------ access -----------------------------------*/

UInt32 TimeSensorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
    {
        returnValue += _sfEnabled.getBinSize();
    }
    if(FieldBits::NoField != (IsActiveFieldMask & whichField))
    {
        returnValue += _sfIsActive.getBinSize();
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        returnValue += _sfLoop.getBinSize();
    }
    if(FieldBits::NoField != (FractionFieldMask & whichField))
    {
        returnValue += _sfFraction.getBinSize();
    }
    if(FieldBits::NoField != (StartTimeFieldMask & whichField))
    {
        returnValue += _sfStartTime.getBinSize();
    }
    if(FieldBits::NoField != (StopTimeFieldMask & whichField))
    {
        returnValue += _sfStopTime.getBinSize();
    }
    if(FieldBits::NoField != (CycleTimeFieldMask & whichField))
    {
        returnValue += _sfCycleTime.getBinSize();
    }
    if(FieldBits::NoField != (TimeFieldMask & whichField))
    {
        returnValue += _sfTime.getBinSize();
    }
    if(FieldBits::NoField != (CycleIntervalFieldMask & whichField))
    {
        returnValue += _sfCycleInterval.getBinSize();
    }

    return returnValue;
}

void TimeSensorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
    {
        _sfEnabled.copyToBin(pMem);
    }
    if(FieldBits::NoField != (IsActiveFieldMask & whichField))
    {
        _sfIsActive.copyToBin(pMem);
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        _sfLoop.copyToBin(pMem);
    }
    if(FieldBits::NoField != (FractionFieldMask & whichField))
    {
        _sfFraction.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StartTimeFieldMask & whichField))
    {
        _sfStartTime.copyToBin(pMem);
    }
    if(FieldBits::NoField != (StopTimeFieldMask & whichField))
    {
        _sfStopTime.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CycleTimeFieldMask & whichField))
    {
        _sfCycleTime.copyToBin(pMem);
    }
    if(FieldBits::NoField != (TimeFieldMask & whichField))
    {
        _sfTime.copyToBin(pMem);
    }
    if(FieldBits::NoField != (CycleIntervalFieldMask & whichField))
    {
        _sfCycleInterval.copyToBin(pMem);
    }
}

void TimeSensorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (EnabledFieldMask & whichField))
    {
        _sfEnabled.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (IsActiveFieldMask & whichField))
    {
        _sfIsActive.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (LoopFieldMask & whichField))
    {
        _sfLoop.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (FractionFieldMask & whichField))
    {
        _sfFraction.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StartTimeFieldMask & whichField))
    {
        _sfStartTime.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (StopTimeFieldMask & whichField))
    {
        _sfStopTime.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CycleTimeFieldMask & whichField))
    {
        _sfCycleTime.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (TimeFieldMask & whichField))
    {
        _sfTime.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (CycleIntervalFieldMask & whichField))
    {
        _sfCycleInterval.copyFromBin(pMem);
    }
}

//! create a new instance of the class
TimeSensorTransitPtr TimeSensorBase::createLocal(BitVector bFlags)
{
    TimeSensorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<TimeSensor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
TimeSensorTransitPtr TimeSensorBase::createDependent(BitVector bFlags)
{
    TimeSensorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<TimeSensor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
TimeSensorTransitPtr TimeSensorBase::create(void)
{
    TimeSensorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<TimeSensor>(tmpPtr);
    }

    return fc;
}

TimeSensor *TimeSensorBase::createEmptyLocal(BitVector bFlags)
{
    TimeSensor *returnValue;

    newPtr<TimeSensor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
TimeSensor *TimeSensorBase::createEmpty(void)
{
    TimeSensor *returnValue;

    newPtr<TimeSensor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr TimeSensorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    TimeSensor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TimeSensor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr TimeSensorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    TimeSensor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const TimeSensor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr TimeSensorBase::shallowCopy(void) const
{
    TimeSensor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const TimeSensor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

TimeSensorBase::TimeSensorBase(void) :
    Inherited(),
    _sfEnabled                (bool(true)),
    _sfIsActive               (bool(false)),
    _sfLoop                   (bool(false)),
    _sfFraction               (Real32(0.0)),
    _sfStartTime              (Time(0.0)),
    _sfStopTime               (Time(0.0)),
    _sfCycleTime              (Time(0.0)),
    _sfTime                   (Time(0.0)),
    _sfCycleInterval          (Time(1.0))
{
}

TimeSensorBase::TimeSensorBase(const TimeSensorBase &source) :
    Inherited(source),
    _sfEnabled                (source._sfEnabled                ),
    _sfIsActive               (source._sfIsActive               ),
    _sfLoop                   (source._sfLoop                   ),
    _sfFraction               (source._sfFraction               ),
    _sfStartTime              (source._sfStartTime              ),
    _sfStopTime               (source._sfStopTime               ),
    _sfCycleTime              (source._sfCycleTime              ),
    _sfTime                   (source._sfTime                   ),
    _sfCycleInterval          (source._sfCycleInterval          )
{
}


/*-------------------------- destructors ----------------------------------*/

TimeSensorBase::~TimeSensorBase(void)
{
}


GetFieldHandlePtr TimeSensorBase::getHandleEnabled         (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfEnabled,
             this->getType().getFieldDesc(EnabledFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleEnabled        (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfEnabled,
             this->getType().getFieldDesc(EnabledFieldId),
             this));


    editSField(EnabledFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleIsActive        (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfIsActive,
             this->getType().getFieldDesc(IsActiveFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleIsActive       (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfIsActive,
             this->getType().getFieldDesc(IsActiveFieldId),
             this));


    editSField(IsActiveFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleLoop            (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfLoop,
             this->getType().getFieldDesc(LoopFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleLoop           (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfLoop,
             this->getType().getFieldDesc(LoopFieldId),
             this));


    editSField(LoopFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleFraction        (void) const
{
    SFReal32::GetHandlePtr returnValue(
        new  SFReal32::GetHandle(
             &_sfFraction,
             this->getType().getFieldDesc(FractionFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleFraction       (void)
{
    SFReal32::EditHandlePtr returnValue(
        new  SFReal32::EditHandle(
             &_sfFraction,
             this->getType().getFieldDesc(FractionFieldId),
             this));


    editSField(FractionFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleStartTime       (void) const
{
    SFTime::GetHandlePtr returnValue(
        new  SFTime::GetHandle(
             &_sfStartTime,
             this->getType().getFieldDesc(StartTimeFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleStartTime      (void)
{
    SFTime::EditHandlePtr returnValue(
        new  SFTime::EditHandle(
             &_sfStartTime,
             this->getType().getFieldDesc(StartTimeFieldId),
             this));


    editSField(StartTimeFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleStopTime        (void) const
{
    SFTime::GetHandlePtr returnValue(
        new  SFTime::GetHandle(
             &_sfStopTime,
             this->getType().getFieldDesc(StopTimeFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleStopTime       (void)
{
    SFTime::EditHandlePtr returnValue(
        new  SFTime::EditHandle(
             &_sfStopTime,
             this->getType().getFieldDesc(StopTimeFieldId),
             this));


    editSField(StopTimeFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleCycleTime       (void) const
{
    SFTime::GetHandlePtr returnValue(
        new  SFTime::GetHandle(
             &_sfCycleTime,
             this->getType().getFieldDesc(CycleTimeFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleCycleTime      (void)
{
    SFTime::EditHandlePtr returnValue(
        new  SFTime::EditHandle(
             &_sfCycleTime,
             this->getType().getFieldDesc(CycleTimeFieldId),
             this));


    editSField(CycleTimeFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleTime            (void) const
{
    SFTime::GetHandlePtr returnValue(
        new  SFTime::GetHandle(
             &_sfTime,
             this->getType().getFieldDesc(TimeFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleTime           (void)
{
    SFTime::EditHandlePtr returnValue(
        new  SFTime::EditHandle(
             &_sfTime,
             this->getType().getFieldDesc(TimeFieldId),
             this));


    editSField(TimeFieldMask);

    return returnValue;
}

GetFieldHandlePtr TimeSensorBase::getHandleCycleInterval   (void) const
{
    SFTime::GetHandlePtr returnValue(
        new  SFTime::GetHandle(
             &_sfCycleInterval,
             this->getType().getFieldDesc(CycleIntervalFieldId),
             const_cast<TimeSensorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr TimeSensorBase::editHandleCycleInterval  (void)
{
    SFTime::EditHandlePtr returnValue(
        new  SFTime::EditHandle(
             &_sfCycleInterval,
             this->getType().getFieldDesc(CycleIntervalFieldId),
             this));


    editSField(CycleIntervalFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void TimeSensorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    TimeSensor *pThis = static_cast<TimeSensor *>(this);

    pThis->execSync(static_cast<TimeSensor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *TimeSensorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    TimeSensor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const TimeSensor *>(pRefAspect),
                  dynamic_cast<const TimeSensor *>(this));

    return returnValue;
}
#endif

void TimeSensorBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE
