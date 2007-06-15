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
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editMFField1),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getMFField1 ));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "field2",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field2),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editSFField2),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getSFField2 ));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "field3",
        "",
        OSG_RC_FIELD_DESC(TestFC::Field3),
        false,
        Field::MFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&TestFC::editMFField3),
        reinterpret_cast<FieldGetMethodSig >(&TestFC::getMFField3 ));

    oType.addInitialDesc(pDesc);
}

TestFC::TypeObject TestFC::_type(
    TestFC   ::getClassname(),
    Inherited::getClassname(),
    "Test",
    0,
    (PrototypeCreateF) &TestFC::createEmpty,
    NULL,
    (InitalInsertDescFunc) &TestFC::classDescInserter,
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
    _mfField3 ()
{
}

TestFC::TestFC(const TestFC &source) :
     Inherited(source          ),
    _mfField1 (source._mfField1),
    _sfField2 (source._sfField2),
    _mfField3 (source._mfField3)
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
TestFC::ObjPtr TestFC::createAspectCopy(void) const
{
    TestFCPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const TestFC *>(this)); 

    return returnValue; 
}
#endif

void TestFC::changed(ConstFieldMaskArg whichField, 
                   UInt32            origin    )
{
    fprintf(stderr, "TestFC Changed\n");

    Inherited::changed(whichField, origin);
}

void TestFC::dump(      UInt32    uiIndent, 
                  const BitVector bvFlags ) const
{
#ifdef OSG_MT_CPTR_ASPECT
    fprintf(stderr, "TestFC %p %p\n", this, _pAspectStore);

    _pAspectStore->dump();
#endif

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
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

void TestFC::pushToField(const FieldContainerPtrConstArg pNewElement,
                         const UInt32                    whichField )
{
}

void TestFC::insertIntoMField(const UInt32                    uiIndex, 
                                    FieldContainerPtrConstArg pNewElement,
                              const UInt32                    whichField )
{
}

void TestFC::replaceInMField(const UInt32                    uiIndex,
                                   FieldContainerPtrConstArg pNewElement, 
                             const UInt32                    whichField )
{
}

void TestFC::replaceInMField(      FieldContainerPtrConstArg pOldElement,
                                   FieldContainerPtrConstArg pNewElement, 
                             const UInt32                    whichField )
{
}


void TestFC::removeFromMField(const UInt32 uiIndex, 
                              const UInt32 whichField)
{
}
    
void TestFC::removeFromMField(      FieldContainerPtrConstArg pElement, 
                              const UInt32                    whichField)
{
}

void TestFC::clearField(const UInt32 whichField)
{
}
