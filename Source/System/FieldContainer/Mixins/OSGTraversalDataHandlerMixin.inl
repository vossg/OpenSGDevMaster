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
void TraversalDataHandlerMixin<ParentT>::changed(ConstFieldMaskArg whichField, 
                                                 UInt32            origin,
                                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class ParentT> inline
void TraversalDataHandlerMixin<ParentT>::setData(
    TraversalData    *pData, 
    Int32             iDataSlotId,
    RenderActionBase *pAction)
{
    TraversalData *pStoredData = 
        pAction->template getData<TraversalData *>(this->_iDataSlotId);

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
                boost::bind(
                    &Self::template clearDestroyedFunctorFor<DataSlotHandler>,
                    this,
                    _1),
                this);
        }

        if(pData != NULL)
        {
            this->addChangedFunctor(
                boost::bind(&TraversalData::updateData, 
                            pData, 
                            _1, 
                            _2,
                            _3),
                "");

            pData->addChangedFunctor(
                boost::bind(&Self::dataDestroyed, 
                            this, 
                            _1, 
                            _2,
                            _3),
                "");
        }
        if(pStoredData != NULL)
        {
            this->subChangedFunctor(
                boost::bind(&TraversalData::updateData, 
                            pStoredData, 
                            _1, 
                            _2,
                            _3));
            
            pStoredData->subChangedFunctor(
                boost::bind(&Self::dataDestroyed, 
                            this, 
                            _1, 
                            _2,
                            _3));
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
TraversalDataHandlerMixin<ParentT>::TraversalDataHandlerMixin(void) :
    Inherited()
{
}

template <class ParentT> inline
TraversalDataHandlerMixin<ParentT>::TraversalDataHandlerMixin(
    const TraversalDataHandlerMixin &source) :

    Inherited(source)
{
}

template <class ParentT> inline
TraversalDataHandlerMixin<ParentT>::~TraversalDataHandlerMixin(void)
{
}

template <class ParentT> inline
void TraversalDataHandlerMixin<ParentT>::dataDestroyed(
    FieldContainer *pCore,
    BitVector       whichField,
    UInt32          origin    )
{
    if(whichField == 0x0000)
    {
        this->subChangedFunctor(
            boost::bind(&TraversalData::updateData, 
                        dynamic_cast<TraversalData *>(pCore), 
                        _1, 
                        _2,
                        _3));
    }
}

template <class ParentT> inline
void TraversalDataHandlerMixin<ParentT>::dump(      UInt32    uiIndent,
                                              const BitVector bvFlags ) const
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE


