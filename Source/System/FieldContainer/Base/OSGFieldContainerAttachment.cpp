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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGFieldContainerAttachment.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                               Fields                                    */

void FieldContainerAttachment::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc;

    typedef MFParentFieldContainerPtr::Description SFDesc;

    pDesc = new SFDesc(
        MFParentFieldContainerPtr::getClassType(),
        "parents",
        "",
        OSG_RC_FIELD_DESC(Self::Parents),
        true,
        Field::MFDefaultFlags,
        static_cast     <FieldEditMethodSig>(&Self::invalidEditField),
        reinterpret_cast<FieldGetMethodSig >(&Self::getHandleParents),
        NULL);

    oType.addInitialDesc(pDesc);


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "internal",
        "",
        OSG_RC_FIELD_DESC(Self::Internal),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&Self::editInternalHandler),
        reinterpret_cast<FieldGetMethodSig >(&Self::getInternalHandler ),
        NULL);

    oType.addInitialDesc(pDesc);
}

Char8 *FieldContainerAttachment::getClassname(void)
{
    return "FieldContainerAttachment";
}

FieldContainerAttachment::TypeObject FieldContainerAttachment::_type(
    FieldContainerAttachment::getClassname(),
    Inherited               ::getClassname(),
    "FieldContainer",
    0,
    NULL,
    NULL,
    (InitalInsertDescFunc) &FieldContainerAttachment::classDescInserter,
    false,
    0);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerAttachment::FieldContainerAttachment(void) :
     Inherited (     ),
    _mfParents (     ),
    _sfInternal(false)
{
}

FieldContainerAttachment::FieldContainerAttachment(
    const FieldContainerAttachment &source) :

     Inherited (source            ),
    _mfParents (                  ),
    _sfInternal(source._sfInternal)
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerAttachment::~FieldContainerAttachment(void)
{
}

OSG_ABSTR_FIELD_CONTAINER_DEF(FieldContainerAttachment)

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

UInt32 FieldContainerAttachment::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);
    
    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _mfParents.getBinSize();
    }
    
    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        returnValue += _sfInternal.getBinSize();
    }
    
    return returnValue;
}

void FieldContainerAttachment::copyToBin(BinaryDataHandler &pMem,
                                         ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.copyToBin(pMem);
    }
    
    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.copyToBin(pMem);
    }
}

void FieldContainerAttachment::copyFromBin(BinaryDataHandler &pMem,
                                           ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _mfParents.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.copyFromBin(pMem);
    }
}

SFBool::EditHandlePtr FieldContainerAttachment::editInternalHandler(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfInternal, 
             this->getType().getFieldDesc(InternalFieldId)));

    editSField(InternalFieldMask);

    return returnValue;
}

SFBool::GetHandlePtr FieldContainerAttachment::getInternalHandler(void)
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfInternal, 
             this->getType().getFieldDesc(InternalFieldId)));

    return returnValue;
}

MFParentFieldContainerPtr::GetHandlePtr 
    FieldContainerAttachment::getHandleParents(void)
{
    MFParentFieldContainerPtr::GetHandlePtr returnValue(
        new  MFParentFieldContainerPtr::GetHandle(
             &_mfParents, 
             this->getType().getFieldDesc(ParentsFieldId)));

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

