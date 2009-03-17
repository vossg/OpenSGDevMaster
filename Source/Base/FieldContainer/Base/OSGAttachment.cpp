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

#include "OSGAttachment.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                               Fields                                    */

void Attachment::classDescInserter(TypeObject &oType)
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
        static_cast<FieldEditMethodSig>(&Self::invalidEditField),
        static_cast<FieldGetMethodSig >(&Self::getHandleParents));

    oType.addInitialDesc(pDesc);


    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "internal",
        "",
        OSG_RC_FIELD_DESC(Self::Internal),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::editInternalHandler),
        static_cast<FieldGetMethodSig >(&Self::getInternalHandler ));

    oType.addInitialDesc(pDesc);
}

const Char8 *Attachment::getClassname(void)
{
    return "Attachment";
}

Attachment::TypeObject Attachment::_type(
    Attachment::getClassname(),
    Inherited ::getClassname(),
    "FieldContainer",
    0,
    NULL,
    NULL,
    NULL,
    reinterpret_cast<InitalInsertDescFunc>(&Attachment::classDescInserter),
    false,
    0);

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Attachment::Attachment(void) :
     Inherited (     ),
    _mfParents (     ),
    _sfInternal(false)
{
}

Attachment::Attachment(const Attachment &source) :

     Inherited (source            ),
    _mfParents (                  ),
    _sfInternal(source._sfInternal)
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Attachment::~Attachment(void)
{
}

OSG_ABSTR_FIELD_CONTAINER_DEF(Attachment)


bool Attachment::linkParent  (FieldContainer * const pParent,
                              UInt16           const childFieldId,
                              UInt16           const parentFieldId)
{
    if(parentFieldId == ParentsFieldId)
    {
        FieldContainer *pTypedParent =
             dynamic_cast<FieldContainer *>(pParent);
        
        if(pTypedParent != NULL)
        {
            editMField(ParentsFieldMask, _mfParents);

            _mfParents.push_back(pParent, childFieldId);
            
            return true;
        }
    
        return false;
    }
    
    return Inherited::linkParent(pParent, childFieldId, parentFieldId);
}

bool Attachment::unlinkParent(FieldContainer * const pParent,
                              UInt16           const parentFieldId)
{
    if(parentFieldId == ParentsFieldId)
    {
        FieldContainer *pTypedParent =
            dynamic_cast<FieldContainer *>(pParent);
            
        if(pTypedParent != NULL)
        {
            Int32 iParentIdx  = _mfParents.findIndex(pParent);

            if(iParentIdx != -1)
            {
                editMField(ParentsFieldMask, _mfParents);
                
                _mfParents.erase(iParentIdx);
                
                return true;
            }
             
            FWARNING(("Attachment::unlinkParent: "
                      "Child <-> Parent link inconsistent.\n"));
            
            return false;
        }

        return false;
    }
        
    return Inherited::unlinkParent(pParent, parentFieldId);
}
 

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

UInt32 Attachment::getBinSize(ConstFieldMaskArg whichField)
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

void Attachment::copyToBin(BinaryDataHandler &pMem,
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

void Attachment::copyFromBin(BinaryDataHandler &pMem,
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

EditFieldHandlePtr Attachment::editInternalHandler(void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfInternal, 
             this->getType().getFieldDesc(InternalFieldId),
             this));

    editSField(InternalFieldMask);

    return returnValue;
}

GetFieldHandlePtr Attachment::getInternalHandler(void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfInternal, 
             this->getType().getFieldDesc(InternalFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

GetFieldHandlePtr Attachment::getHandleParents(void) const
{
    MFParentFieldContainerPtr::GetHandlePtr returnValue(
        new  MFParentFieldContainerPtr::GetHandle(
             &_mfParents, 
             this->getType().getFieldDesc(ParentsFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

#ifdef OSG_MT_CPTR_ASPECT
void Attachment::execSyncV(     
          FieldContainer    &oFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<Attachment *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

OSG_END_NAMESPACE
