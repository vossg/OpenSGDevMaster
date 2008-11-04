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
        static_cast<FieldEditMethodSig>(&Self::editHandleUpdateMode),
        static_cast<FieldGetMethodSig >(&Self::getHandleUpdateMode ));

    oType.addInitialDesc(pDesc);

    pDesc = new SFDesc(
        SFOSGAny::getClassType(),
        "requestRun",
        "",
        OSG_RC_FIELD_DESC(Self::RequestRun),
        true,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::invalidEditField   ),
        static_cast<FieldGetMethodSig >(&Self::getHandleRequestRun));

    oType.addInitialDesc(pDesc);

    pDesc = new MFChangedFunctorCallback::Description(
        MFChangedFunctorCallback::getClassType(),
        "destroyedFunctors",
        "",
        OSG_RC_FIELD_DESC(Self::DestroyedFunctors),
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast     <FieldEditMethodSig>(&Self::invalidEditField),
        static_cast     <FieldGetMethodSig >(&Self::invalidGetField));

    oType.addInitialDesc(pDesc);
}

template <class ParentT> inline
bool StageHandlerMixin<ParentT>::requestRun(void)
{
    Self::editSField(RequestRunFieldMask);

    return true;
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    if(0x0000 != (whichField & RequestRunFieldMask))
    {
        Window::requestStageRun(_iStageId);
    }

    Inherited::changed(whichField, origin, details);
}

template <class ParentT> inline
typename StageHandlerMixin<ParentT>::ValidationStatus 
    StageHandlerMixin<ParentT>::validate(RenderActionBase *pAction)
{
 
    StageValidator *pVal = NULL;

    if(_sfUpdateMode.getValue() == Self::PerWindow)
    {
        Window *pWin = pAction->getWindow();

        pVal = pWin->getStageValidator();
    }
    else if(_sfUpdateMode.getValue() == Self::PerViewport)
    {
        Viewport *pVP = pAction->getViewport();

        pVal = pVP->getStageValidator();
    }
    else if(_sfUpdateMode.getValue() == Self::PerTraversal)
    {
        pVal = pAction->getStageValidator();
    }
    else if(_sfUpdateMode.getValue() == Self::OnRequest)
    {
        Window *pWin = pAction->getWindow();

        pVal = pWin->getStageValidator();

        return pVal->checkRunRequest(_iStageId);
    }
    else
    {
        return StageValidator::Run;
    }

    return pVal->validate(_iStageId, pAction->getFrameTravCount());
}

template <class ParentT> inline
typename StageHandlerMixin<ParentT>::ValidationStatus 
    StageHandlerMixin<ParentT>::validateOnEnter(
        RenderActionBase *pAction)
{
    StageValidator::ValidationStatus returnValue = Self::validate(pAction);

    StageDataUnrecPtr pData = 
        pAction->template getData<StageData *>(_iDataSlotId);

    if(pData == NULL)
    {
        pData = StageData::createLocal();

        pAction->setData(pData, _iDataSlotId);
    }

    if(returnValue == StageValidator::Finished)
    {
        if(pData != NULL)
        {           
            Int32 iPartBegin = pData->getPartitionRangeBegin();
            Int32 iPartEnd   = pData->getPartitionRangeEnd  ();
            
            while(iPartBegin <= iPartEnd)
            {
                pAction->readdPartitionByIndex(iPartBegin);
                
                ++iPartBegin;
            }
        }
    }

    return returnValue;
}

template <class ParentT> inline
typename StageHandlerMixin<ParentT>::ValidationStatus 
    StageHandlerMixin<ParentT>::validateOnLeave(
        RenderActionBase *pAction)
{
    return Self::validate(pAction);
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::pushPartition(
    RenderActionBase          *pAction,
    UInt32                     uiCopyOnPush, 
    RenderPartitionBase::Mode  eMode)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    pAction->pushPartition(uiCopyOnPush, eMode);

    if(pData != NULL)
    {
        if(pData->getGroupMode() == NoPartitionGroup)
        {
            pData->setPartitionRangeBegin(pAction->getActivePartitionIdx());
        }

    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::popPartition(
    RenderActionBase *pAction)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    pAction->popPartition();

    if(pData != NULL)
    {
        if(pData->getGroupMode() == NoPartitionGroup)
        {
            pData->setPartitionRangeEnd(pAction->getLastPartitionIdx());
        }
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::beginPartitionGroup(
    RenderActionBase *pAction)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    if(pData != NULL)
    {
        pData->setGroupMode(InPartitionGroup);
    }

    pAction->beginPartitionGroup();

    if(pData != NULL)
    {
        pData->setPartitionRangeBegin(pAction->getActivePartitionIdx());
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::endPartitionGroup(
    RenderActionBase *pAction)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    if(pData != NULL)
    {
        pData->setGroupMode(NoPartitionGroup);
    }

    pAction->endPartitionGroup();

    if(pData != NULL)
    {
        pData->setPartitionRangeEnd(pAction->getLastPartitionIdx());
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::beginPartitions(
    RenderActionBase *pAction)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    if(pData != NULL)
    {
        pData->setGroupMode          (InPartitionList                   );
        pData->setPartitionRangeBegin(pAction->getLastPartitionIdx() + 1);
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::endPartitions(
    RenderActionBase *pAction)
{
    StageData *pData = pAction->template getData<StageData *>(_iDataSlotId);

    if(pData != NULL)
    {
        pData->setGroupMode        (NoPartitionGroup              );
        pData->setPartitionRangeEnd(pAction->getLastPartitionIdx());
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::setData(
    StageData        *pData, 
    Int32             iDataSlotId,
    RenderActionBase *pAction)
{
    StageData *pStoredData = 
        pAction->template getData<StageData *>(_iDataSlotId);

    bool bCheckCallback = false;

    OSG_ASSERT(iDataSlotId == _iDataSlotId);

    if(pStoredData == NULL)
    {
        pAction->setData(pData, _iDataSlotId);
        bCheckCallback = true;
    }
    else if(pStoredData != pData)
    {
        pData->copyFrom(pStoredData);

        pAction->setData(pData, _iDataSlotId);
        bCheckCallback = true;
    }

    if(bCheckCallback == true)
    {
        if(this->hasDestroyedFunctor(
               boost::bind(&RenderActionBase::clearData,
                           pAction,
                           _1,
                           _2,
                           _iDataSlotId)) == false)
        {
            this->addDestroyedFunctor(
                boost::bind(&RenderActionBase::clearData,
                            static_cast<DataSlotHandler *>(pAction),
                            _1,
                            _2,
                            _iDataSlotId), "");

            pAction->addDestroyedFunctorFor(
                boost::bind(&Self::clearDestroyedFunctorFor,
                            this,
                            _1),
                this);
        }
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::addDestroyedFunctor(
    ChangedFunctor func,
    std::string    createSymbol)
{
    ChangedFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _mfDestroyedFunctors.push_back(oTmp);
}

template <class ParentT> 
template<class FunctorT> inline
void StageHandlerMixin<ParentT>::subDestroyedFunctor(FunctorT func)
{
    MFChangedFunctorCallback::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    MFChangedFunctorCallback::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();

    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
            break;
    }

    if(cfIt != cfEnd)
        _mfDestroyedFunctors.erase(cfIt);
}

template <class ParentT> 
template<class FunctorT> inline
bool StageHandlerMixin<ParentT>::hasDestroyedFunctor(FunctorT func)
{
    bool returnValue = false;

    MFChangedFunctorCallback::iterator       cfIt = 
        _mfDestroyedFunctors.begin();

    MFChangedFunctorCallback::const_iterator cfEnd= 
        _mfDestroyedFunctors.end();


    for(; cfIt != cfEnd; ++cfIt)
    {
        if(cfIt->_func == func)
        {
            returnValue = true;
            break;
        }
    }
    
    return returnValue;
}

template <class ParentT> inline 
void StageHandlerMixin<ParentT>::clearDestroyedFunctors(void)
{
    _mfDestroyedFunctors.clear();
}

template <class ParentT> inline 
void StageHandlerMixin<ParentT>::clearDestroyedFunctorFor(
    DataSlotHandler *pHandler)
{
    this->subDestroyedFunctor(boost::bind(&RenderActionBase::clearData,
                                            pHandler,
                                           _1,
                                           _2,
                                           _iDataSlotId));
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
    if(FieldBits::NoField != (RequestRunFieldMask & whichField))
    {
        returnValue += _sfRequestRun.getBinSize();
    }
    if(FieldBits::NoField != (DestroyedFunctorsFieldMask & whichField))
    {
        returnValue += _mfDestroyedFunctors.getBinSize();
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
    if(FieldBits::NoField != (RequestRunFieldMask & whichField))
    {
        _sfRequestRun.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DestroyedFunctorsFieldMask & whichField))
    {
        _mfDestroyedFunctors.copyToBin(pMem);
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
    if(FieldBits::NoField != (RequestRunFieldMask & whichField))
    {
        _sfRequestRun.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DestroyedFunctorsFieldMask & whichField))
    {
        _mfDestroyedFunctors.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(void) :
     Inherited          (            ),
    _iDataSlotId        (-1          ),
    _iStageId           (-1          ),
    _sfUpdateMode       (PerTraversal),
    _sfRequestRun       (            ),
    _mfDestroyedFunctors(            )
{
    _tmpStatus = StageValidator::Finished;
}

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(
    const StageHandlerMixin &source) :

     Inherited          (source                     ),
    _iStageId           (-1                         ),
    _iDataSlotId        (-1                         ),
    _sfUpdateMode       (source._sfUpdateMode       ),
    _sfRequestRun       (source._sfRequestRun       ),
    _mfDestroyedFunctors(source._mfDestroyedFunctors)
{
    _tmpStatus = StageValidator::Finished;
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

template <class ParentT> inline
EditFieldHandlePtr StageHandlerMixin<ParentT>::editHandleUpdateMode(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfUpdateMode, 
             this->getType().getFieldDesc(UpdateModeFieldId)));

    Self::editSField(UpdateModeFieldMask);

    return returnValue;
}

template <class ParentT> inline
GetFieldHandlePtr  StageHandlerMixin<ParentT>::getHandleUpdateMode(
    void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfUpdateMode, 
             this->getType().getFieldDesc(UpdateModeFieldId)));

    return returnValue;
}

template <class ParentT> inline
GetFieldHandlePtr  StageHandlerMixin<ParentT>::getHandleRequestRun(
    void) const
{
    SFOSGAny::GetHandlePtr returnValue(
        new  SFOSGAny::GetHandle(
             &_sfRequestRun, 
             this->getType().getFieldDesc(RequestRunFieldId)));

    return returnValue;
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */


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
    if(FieldBits::NoField != (RequestRunFieldMask & whichField))
    {
        _sfRequestRun.syncWith(pFrom->_sfRequestRun);
    }
}
#endif

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onCreateAspect(const Self   *createAspect,
                                                const Self   *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
        _iDataSlotId = createAspect->_iDataSlotId;
        _iStageId    = createAspect->_iStageId;
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onCreate(const Self *source)
{
    Inherited::onCreate(source);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
        _iDataSlotId = ActionDataSlotPool::the()->create();
        _iStageId    = StageIdPool       ::the()->create();
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
        ActionDataSlotPool::the()->release(_iDataSlotId);
        StageIdPool       ::the()->release(_iStageId   );
    }
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::onDestroyAspect(UInt32  uiContainerId,
                                                 UInt32  uiAspect     )
{
    Inherited::onDestroy(uiContainerId);

    // avoid prototype
    if(GlobalSystemState == OSG::Running)
    {
        MFChangedFunctorCallback::iterator       cfIt = 
            _mfDestroyedFunctors.begin();

        MFChangedFunctorCallback::const_iterator cfEnd= 
            _mfDestroyedFunctors.end();
        
        for(; cfIt != cfEnd; ++cfIt)
        {
            if(cfIt->_func)
                (cfIt->_func)(this, 0x0000);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

