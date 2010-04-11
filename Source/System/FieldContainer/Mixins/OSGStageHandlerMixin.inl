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
bool StageHandlerMixin<ParentT>::requestRun(void)
{
    Self::editSField(Inherited::RequestRunFieldMask);

    return true;
}

template <class ParentT> inline
void StageHandlerMixin<ParentT>::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    if(0x0000 != (whichField & Inherited::RequestRunFieldMask))
    {
        Window::requestStageRun(this->_iElementId);
    }

    Inherited::changed(whichField, origin, details);
}

template <class ParentT> inline
typename StageHandlerMixin<ParentT>::ValidationStatus 
    StageHandlerMixin<ParentT>::validate(RenderActionBase *pAction)
{
 
    TraversalValidator *pVal = NULL;

    if(this->_sfUpdateMode.getValue() == Self::PerWindow)
    {
        Window *pWin = pAction->getWindow();

        pVal = pWin->getTravValidator();
    }
    else if(this->_sfUpdateMode.getValue() == Self::PerViewport)
    {
        Viewport *pVP = pAction->getViewport();

        pVal = pVP->getTravValidator();
    }
    else if(this->_sfUpdateMode.getValue() == Self::PerTraversal)
    {
        pVal = pAction->getTravValidator();
    }
    else if(this->_sfUpdateMode.getValue() == Self::OnRequest)
    {
        Window *pWin = pAction->getWindow();

        pVal = pWin->getTravValidator();

        return pVal->checkRunRequest(this->_iElementId);
    }
    else
    {
        return TraversalValidator::Run;
    }

    return pVal->validate(this->_iElementId, pAction->getFrameTravCount());
}

template <class ParentT> inline
typename StageHandlerMixin<ParentT>::ValidationStatus 
    StageHandlerMixin<ParentT>::validateOnEnter(
        RenderActionBase *pAction)
{
    TraversalValidator::ValidationStatus returnValue = Self::validate(pAction);

    StageDataUnrecPtr pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

    if(pData == NULL)
    {
        pData = StageData::createLocal();

        pAction->setData(pData, this->_iDataSlotId);
    }

    if(returnValue == TraversalValidator::Finished)
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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
    StageData *pData = 
        pAction->template getData<StageData *>(this->_iDataSlotId);

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
        pAction->template getData<StageData *>(this->_iDataSlotId);

    bool bCheckCallback = false;

    OSG_ASSERT(iDataSlotId == this->_iDataSlotId);

    if(pStoredData == NULL)
    {
        pAction->setData(pData, this->_iDataSlotId);
        bCheckCallback = true;
    }
    else if(pStoredData != pData)
    {
        pData->copyFrom(pStoredData);

        pAction->setData(pData, this->_iDataSlotId);
        bCheckCallback = true;
    }

    if(bCheckCallback == true)
    {
        if(this->hasDestroyedFunctor(
               boost::bind(&DataSlotHandler::clearData,
                           pAction,
                           _1,
                           _2,
                           this->_iDataSlotId)) == false)
        {
            this->addDestroyedFunctor(
                boost::bind(&DataSlotHandler::clearData,
                            static_cast<DataSlotHandler *>(pAction),
                            _1,
                            _2,
                            this->_iDataSlotId), "");

            pAction->addDestroyedFunctorFor(
                boost::bind(&Self::clearDestroyedFunctorFor,
                            this,
                            _1),
                this);
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(void) :
    Inherited()
{
    _tmpStatus = TraversalValidator::Finished;
}

template <class ParentT> inline
StageHandlerMixin<ParentT>::StageHandlerMixin(
    const StageHandlerMixin &source) :

    Inherited(source)
{
    _tmpStatus = TraversalValidator::Finished;
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

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ParentT> inline
Action::ResultE StageHandlerMixin<ParentT>::recurseFromThis(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;

    Node            *pActNode    = action->getActNode  ();
    FieldContainer  *pActParent  = action->getActParent();

    if(pActNode != pActParent)
    {
        OSG_ASSERT(pActParent == pActNode->getCore());

        MultiCore *pCore = dynamic_cast<MultiCore *>(pActParent);

        if(pCore != NULL)
        {
            returnValue = action->recurseMultiCoreFrom(pActNode, 
                                                       pCore,
                                                       this);
        }
        else
        {
            returnValue = action->recurseNoCallback(pActNode);
        }
    }
    else
    {
        returnValue = action->recurseNoCallback(pActNode);
    }

    action->setActNode  (pActNode  );
    action->setActParent(pActParent);

    return returnValue;
}

template <class ParentT> inline
Action::ResultE StageHandlerMixin<ParentT>::recurseFrom(Action   *action,
                                                        NodeCore *pFrom )
{
    Action::ResultE  returnValue = Action::Continue;

    Node            *pActNode    = action->getActNode  ();
    FieldContainer  *pActParent  = action->getActParent();

    if(pActNode != pActParent)
    {
        OSG_ASSERT(pActParent == pActNode->getCore());

        MultiCore *pCore = dynamic_cast<MultiCore *>(pActParent);

        if(pCore != NULL)
        {
            returnValue = action->recurseMultiCoreFrom(pActNode, 
                                                       pCore,
                                                       pFrom);
        }
        else
        {
            returnValue = action->recurseNoCallback(pActNode);
        }
    }
    else
    {
        returnValue = action->recurseNoCallback(pActNode);
    }

    action->setActNode  (pActNode  );
    action->setActParent(pActParent);

    return returnValue;
}

template <class ParentT> inline
Action::ResultE StageHandlerMixin<ParentT>::recurse(Action *action,
                                                    Node   *node  )
{
    Node           *pActNode   = action->getActNode  ();
    FieldContainer *pActParent = action->getActParent();

    Action::ResultE returnValue = action->recurse(node);    

    action->setActNode  (pActNode  );
    action->setActParent(pActParent);

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE

