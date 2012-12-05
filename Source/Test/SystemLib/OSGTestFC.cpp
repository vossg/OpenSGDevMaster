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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGLog.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGTestFC.h"

OSG_USING_NAMESPACE

void TestFC::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;

    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "field1",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field1),
        false,
        Field::MFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editHandleField1),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getHandleField1 ));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "field2",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field2),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editHandleField2),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getHandleField2 ));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "field3",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field3),
        false,
        Field::MFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editHandleField3),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getHandleField3 ));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "field4",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field4),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editHandleField4),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getHandleField4 ));

    oType.addInitialDesc(pDesc);
}

TestFC::TypeObject TestFC::_type(
    TestFC   ::getClassname(),
    Inherited::getClassname(),
    "Test",
    0,
    reinterpret_cast<PrototypeCreateF>(&TestFC::createEmptyLocal),
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(&TestFC::classDescInserter),
    false,
    0);


OSG_FIELD_CONTAINER_DEF(TestFC)

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

TestFC::TestFC(void) :
     Inherited(),
    _mfField1 (),
    _sfField2 (),
    _mfField3 (),
    _sfField4 ()
{
}

TestFC::TestFC(const TestFC &source) :
     Inherited(source          ),
    _mfField1 (source._mfField1),
    _sfField2 (source._sfField2),
    _mfField3 (source._mfField3),
    _sfField4 (source._sfField4)
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

TestFC::~TestFC(void)
{
}

void TestFC::onDestroyAspect(UInt32 uiContainerId,
                             UInt32 uiAspect     )
{
//    _mfField1.terminateShare(uiAspect, getContainerSize());
//    _mfField3.terminateShare(uiAspect, getContainerSize());
}

#ifdef OSG_MT_CPTR_ASPECT
TestFC::ObjCPtr TestFC::createAspectCopy(const FieldContainer *pRefAspect) const
{
    TestFC *returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const TestFC *>(pRefAspect),
                  dynamic_cast<const TestFC *>(this)); 

    return returnValue; 
}
#endif

void TestFC::changed(ConstFieldMaskArg whichField, 
                     UInt32            origin,
                     BitVector         details)
{
    fprintf(stderr, "TestFC changed\n");

    Inherited::changed(whichField, origin, details);
}

void TestFC::dump(      UInt32    uiIndent, 
                  const BitVector bvFlags ) const
{
#ifdef OSG_MT_CPTR_ASPECT
    fprintf(stderr, "TestFC %p %p\n", this, _pAspectStore);

    _pAspectStore->dump();
#endif

    fprintf(stderr, "%p %p | 0x%016" PRIx64 "\n", 
            _pContainerChanges, 
            &_bvChanged,
           _bvChanged);

    _mfField1.dump(uiIndent + 4, bvFlags);
    
    for(UInt32 i = 0; i < _mfField1.size(); ++i)
    {
        fprintf(stderr, "%d ", _mfField1[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "%d\n", _sfField2.getValue());

    _mfField3.dump(uiIndent + 4, bvFlags);

    for(UInt32 i = 0; i < _mfField3.size(); ++i)
    {
        fprintf(stderr, "%d ", _mfField3[i]);
    }
    fprintf(stderr, "\n");
}

MFUInt32 *TestFC::editMFField1(void)
{
    editMField(Field1FieldMask, _mfField1);

    return &_mfField1;
}

const MFUInt32 *TestFC::getMFField1(void) const
{
    return &_mfField1;
}

SFUInt32 *TestFC::editSFField2(void)
{
    editSField(Field2FieldMask);

    return &_sfField2;
}

const SFUInt32 *TestFC::getSFField2(void) const
{
    return &_sfField2;
}

MFUInt32 *TestFC::editMFField3(void)
{
    editMField(Field3FieldMask, _mfField3);

    return &_mfField3;
}

const MFUInt32 *TestFC::getMFField3(void) const
{
    return &_mfField3;
}

SFUInt32 *TestFC::editSFField4(void)
{
    editSField(Field4FieldMask);

    return &_sfField4;
}

const SFUInt32 *TestFC::getSFField4(void) const
{
    return &_sfField4;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

#ifdef OSG_MT_CPTR_ASPECT
void TestFC::execSyncV(      FieldContainer    &oFrom,
                             ConstFieldMaskArg  whichField,
                             AspectOffsetStore &oOffsets,
                             ConstFieldMaskArg  syncMode  ,
                       const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<TestFC *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

void TestFC::resolveLinks(void)
{
    Inherited::resolveLinks();
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

MFUInt32::EditHandlePtr TestFC::editHandleField1(void)
{
    MFUInt32::EditHandlePtr returnValue(
        new MFUInt32::EditHandle(
            &_mfField1, 
            this->getType().getFieldDesc(Field1FieldId),
            this));

    editMField(Field1FieldMask, _mfField1);

    return returnValue;
}

MFUInt32::GetHandlePtr  TestFC::getHandleField1 (void) const
{
    MFUInt32::GetHandlePtr returnValue(
        new MFUInt32::GetHandle(
            &_mfField1, 
            this->getType().getFieldDesc(Field1FieldId),
            const_cast<TestFC *>(this)));

    return returnValue;
}

SFUInt32::EditHandlePtr TestFC::editHandleField2(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new SFUInt32::EditHandle(
            &_sfField2, 
            this->getType().getFieldDesc(Field2FieldId),
            this));

    editSField(Field2FieldMask);

    return returnValue;
}

SFUInt32::GetHandlePtr  TestFC::getHandleField2 (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new SFUInt32::GetHandle(
            &_sfField2, 
            this->getType().getFieldDesc(Field2FieldId),
            const_cast<TestFC *>(this)));

    return returnValue;
}


MFUInt32::EditHandlePtr TestFC::editHandleField3(void)
{
    MFUInt32::EditHandlePtr returnValue(
        new MFUInt32::EditHandle(
            &_mfField3, 
            this->getType().getFieldDesc(Field3FieldId),
            this));

    editMField(Field3FieldMask, _mfField3);

    return returnValue;
}

MFUInt32::GetHandlePtr  TestFC::getHandleField3 (void) const
{
    MFUInt32::GetHandlePtr returnValue(
        new MFUInt32::GetHandle(
            &_mfField3, 
            this->getType().getFieldDesc(Field3FieldId),
            const_cast<TestFC *>(this)));

    return returnValue;
}

SFUInt32::EditHandlePtr TestFC::editHandleField4(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new SFUInt32::EditHandle(
            &_sfField4, 
            this->getType().getFieldDesc(Field4FieldId),
            this));

    editSField(Field4FieldMask);

    return returnValue;
}

SFUInt32::GetHandlePtr  TestFC::getHandleField4 (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new SFUInt32::GetHandle(
            &_sfField4, 
            this->getType().getFieldDesc(Field4FieldId),
            const_cast<TestFC *>(this)));

    return returnValue;
}
