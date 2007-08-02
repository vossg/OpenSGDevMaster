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

OSG_BEGIN_NAMESPACE

OSG_FIELD_CONTAINER_TMPL_NO_TYPE_DEF  (SimpleAttachment, AttachmentDescT)
OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(SimpleAttachment, AttachmentDescT)

template <class AttachmentDescT> inline
typename SimpleAttachment<AttachmentDescT>::StoredFieldType *
    SimpleAttachment<AttachmentDescT>::editFieldPtr(void)
{
//    EditFieldResult::editField(SimpleFieldMask, _field, this);

//    this->editField(_field);

    return &_field;
}

template <class AttachmentDescT> inline
const typename SimpleAttachment<AttachmentDescT>::StoredFieldType *
    SimpleAttachment<AttachmentDescT>::getFieldPtr(void) const
{
    return &_field;
}

template <class AttachmentDescT> inline
typename SimpleAttachment<AttachmentDescT>::StoredFieldType &
    SimpleAttachment<AttachmentDescT>::editField(void)
{
//    EditFieldResult::editField(SimpleFieldMask, _field, this);

    return _field;
}

template <class AttachmentDescT> inline
const typename SimpleAttachment<AttachmentDescT>::StoredFieldType &
    SimpleAttachment<AttachmentDescT>::getField(void) const
{
    return _field;
}

template <class AttachmentDescT> inline
Char8 *SimpleAttachment<AttachmentDescT>::getClassname(void)
{
    return SimpleDesc::getTypeName();
}

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::SimpleAttachment(void) :
     Inherited(),
    _field    ()
{
}

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::SimpleAttachment(
    const SimpleAttachment &source) :

     Inherited(source       ),
    _field    (source._field)
{
}

template <class AttachmentDescT> inline
SimpleAttachment<AttachmentDescT>::~SimpleAttachment(void)
{
}

#ifdef OSG_MT_CPTR_ASPECT
template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execSync(
          SimpleAttachment  *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
//    OSG_ASSERT(false);
}

template <class AttachmentDescT> inline
 void SimpleAttachment<AttachmentDescT>::execSyncV(
            FieldContainer    &oFrom,
            ConstFieldMaskArg  whichField,
            AspectOffsetStore &oOffsets,
            ConstFieldMaskArg  syncMode  ,
      const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<SimpleAttachment *>(&oFrom), 
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class AttachmentDescT> inline
typename SimpleAttachment<AttachmentDescT>::ObjPtr 
    SimpleAttachment<AttachmentDescT>::createAspectCopy(void) const
{
    ObjPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const Self *>(this)); 

    return returnValue; 
}
#endif

template <class AttachmentDescT> inline
UInt32 SimpleAttachment<AttachmentDescT>::getBinSize(
    ConstFieldMaskArg  whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);
    
    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}


template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyToBin(
    BinaryDataHandler &pMem, 
    ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);
    
    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyFromBin(
    BinaryDataHandler &pMem, 
    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);
    
    if(FieldBits::NoField != (SimpleFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::dump(
          UInt32    OSG_CHECK_ARG(uiIndent), 
    const BitVector OSG_CHECK_ARG(bvFlags)) const
{
}

template <class AttachmentDescT> inline
GetFieldHandlePtr SimpleAttachment<AttachmentDescT>::getHandleField(void) const
{
    GetHandlePtr returnValue(
        new  GetHandle(
             &_field, 
             this->getType().getFieldDesc(SimpleFieldId)));

    return returnValue;
}

template <class AttachmentDescT> inline
EditFieldHandlePtr SimpleAttachment<AttachmentDescT>::editHandleField(void)
{
    EditHandlePtr returnValue(
        new  EditHandle(
             &_field, 
             this->getType().getFieldDesc(SimpleFieldId)));

//    editSField(TravMaskFieldMask);

    return returnValue;
}

OSG_END_NAMESPACE
