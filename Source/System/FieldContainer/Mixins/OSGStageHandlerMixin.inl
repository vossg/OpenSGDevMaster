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


template <class ParentT> inline
void StageHandlerMixin<ParentT>::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc;

    typedef typename SFUInt32::Description SFDesc;

    pDesc = new SFDesc(
        SFUInt32::getClassType(),
        "updateMode",
        "how the stage is updated.",
        OSG_RC_FIELD_DESC(Self::UpdateMode),
        false,
        Field::SFDefaultFlags,
        reinterpret_cast<FieldEditMethodSig>(&Self::editSFUpdateMode),
        reinterpret_cast<FieldGetMethodSig >(&Self::getSFUpdateMode ),
        NULL);

    oType.addInitialDesc(pDesc);
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ParentT> inline
void StageHandlerMixin<ParentT>::setUpdateMode(UpdateMode eMode)
{
    Inherited::editSField(UpdateModeFieldMask);

    _sfUpdateMode.setValue(eMode);
}

template <class ParentT> inline
UInt32 StageHandlerMixin<ParentT>::getUpdateMode(void) const
{
    return _sfUpdateMode.getValue();
}

template <class ParentT> inline
SFUInt32 *StageHandlerMixin<ParentT>::editSFUpdateMode(void)
{
    Inherited::editSField(UpdateModeFieldMask);

    return &_sfUpdateMode;
}

template <class ParentT> inline
const SFUInt32 *StageHandlerMixin<ParentT>::getSFUpdateMode(void) const
{
    return &_sfUpdateMode;
}

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

template <class ParentT> inline
UInt32 StageHandlerMixin<ParentT>::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (UpdateModeFieldMask & whichField))
    {
        returnValue += _sfUpdateMode.getBinSize();
    }

    return returnValue;
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::copyToBin(
    BinaryDataHandler  &pMem, ConstFieldMaskArg whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (UpdateModeFieldMask & whichField))
    {
        _sfUpdateMode.copyToBin(pMem);
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::copyFromBin(
    BinaryDataHandler &pMem, ConstFieldMaskArg whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (UpdateModeFieldMask & whichField))
    {
        _sfUpdateMode.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(void) :
     Inherited   (            ),
    _sfUpdateMode(PerTraversal),
    _iDataSlotId (-1          )
     
{
}

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(
    const StageHandlerMixin &source) :

     Inherited   (source              ),
    _sfUpdateMode(source._sfUpdateMode),
    _iDataSlotId (                  -1)
{
}

template <class ParentT> inline
StageHandlerMixin<ParentT>::~StageHandlerMixin(void)
{
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::dump(      UInt32    uiIndent,
                                      const BitVector bvFlags ) const
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

#ifdef OSG_MT_FIELDCONTAINERPTR
template <class ParentT> inline
void StageHandlerMixin<ParentT>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo,
          UInt32             uiCopyOffset)
{
    Inherited::execSync(pFrom, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (UpdateModeFieldMask & whichField))
    {
        _sfUpdateMode.syncWith(pFrom->_sfUpdateMode);
    }
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class ParentT> inline
void StageHandlerMixin<ParentT>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
                             AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (UpdateModeFieldMask & whichField))
    {
        _sfUpdateMode.syncWith(pFrom->_sfUpdateMode);
    }
}
#endif

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onCreateAspect(const Self   *createAspect,
                                                const Self   *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    // avoid prototype
    if(GlobalSystemState == Running)
    {
        _iDataSlotId = createAspect->_iDataSlotId;
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onCreate(const Self *source)
{
    Inherited::onCreate(source);

    // avoid prototype
    if(GlobalSystemState == Running)
    {
        _iDataSlotId = ActionDataSlotPool::the()->create();
        
        fprintf(stderr, "Got data slot %d\n", _iDataSlotId);
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);

    // avoid prototype
    if(GlobalSystemState == Running)
    {
        ActionDataSlotPool::the()->release(_iDataSlotId);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

