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
    return Desc::getTypeName();
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

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execSync(      
          SimpleAttachment   *pFrom,
          ConstFieldMaskArg   whichField,
          ConstFieldMaskArg   syncMode  ,
    const UInt32              uiSyncInfo,
          UInt32              uiCopyOffset)
{
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execSyncV(     
          FieldContainer     &oFrom,
          ConstFieldMaskArg   whichField,
          ConstFieldMaskArg   syncMode  ,
    const UInt32              uiSyncInfo,
          UInt32              uiCopyOffset)
{
    this->execSync(static_cast<Self *>(&oFrom), 
                   whichField, 
                   syncMode,
                   uiSyncInfo,
                   uiCopyOffset);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execSync(
          SimpleAttachment  *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
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

#if 0
template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execBeginEdit(
    ConstFieldMaskArg whichField, 
    UInt32            uiAspect,
    UInt32            uiContainerSize)
{
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::execBeginEditV(
    ConstFieldMaskArg whichField, 
    UInt32            uiAspect,
    UInt32            uiContainerSize)
{
    this->execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif

template <class AttachmentDescT> inline
UInt32 SimpleAttachment<AttachmentDescT>::getBinSize(
    ConstFieldMaskArg  whichField)
{
    return 0;
}


template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyToBin(
    BinaryDataHandler &pMem, 
    ConstFieldMaskArg  whichField)
{
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::copyFromBin(
    BinaryDataHandler &pMem, 
    ConstFieldMaskArg  whichField)
{
}

template <class AttachmentDescT> inline
void SimpleAttachment<AttachmentDescT>::dump(
          UInt32    uiIndent, 
    const BitVector bvFlags) const
{
}

OSG_END_NAMESPACE
