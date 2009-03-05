/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <OSGConfig.h>

#include "OSGChunkOverrideGroup.h"
#include "OSGRenderAction.h"
#include "OSGChunkBlock.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGChunkOverrideGroupBase.cpp file.
// To modify it, please change the .fcd file (OSGChunkOverrideGroup.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ChunkOverrideGroup::classDescInserter(TypeObject &oType)
{
    Inherited::classDescInserter(oType);

    FieldDescriptionBase *pDesc;

    typedef SFChunkBlockPtrMap::Description SFDesc;

    pDesc = new SFDesc(
        SFChunkBlockPtrMap::getClassType(),
        "chunkBlockStore",
        "chunk block store.",
        OSG_RC_FIELD_DESC(ChunkBlockStore),
        false,
        Field::SFDefaultFlags,
        static_cast<FieldEditMethodSig>(&Self::editHandleChunkBlockStore),
        static_cast<FieldGetMethodSig >(&Self::getHandleChunkBlockStore ));

    oType.addInitialDesc(pDesc);
}

void ChunkOverrideGroup::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            ChunkOverrideGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ChunkOverrideGroup::renderEnter));

        RenderAction::registerLeaveDefault(
            ChunkOverrideGroup::getClassType(), 
            reinterpret_cast<Action::Callback>(
                &ChunkOverrideGroup::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ChunkOverrideGroup::ChunkOverrideGroup(void) :
     Inherited        (),
    _sfChunkBlockStore()
{
}

ChunkOverrideGroup::ChunkOverrideGroup(const ChunkOverrideGroup &source) :
     Inherited        (source),
    _sfChunkBlockStore(      )
{
}

ChunkOverrideGroup::~ChunkOverrideGroup(void)
{
}

/*----------------------------- class specific ----------------------------*/

bool ChunkOverrideGroup::addChunk(StateChunk *chunk, 
                                  Int32       slot)
{
    ChunkBlockUnrecPtr pBlock = this->finalize(0x0000);

    if(pBlock == NULL)
    {
        pBlock = ChunkBlock::create();

        this->addChunkBlock(pBlock, 0x0000);
    }

    return pBlock->addChunk(chunk, slot);
}

bool ChunkOverrideGroup::subChunk(StateChunk *chunk, 
                                  Int32       slot)
{
    if(chunk == NULL)
        return false;

    ChunkBlock *pBlock = this->finalize(0x0000);

    if(pBlock != NULL)
    {
        return pBlock->subChunk(chunk, slot);
    }

    return false;
}

Int32 ChunkOverrideGroup::find(StateChunk *chunk)
{
    ChunkBlock *pBlock = this->finalize(0x0000);

    if(pBlock != NULL)
    {
        return pBlock->find(chunk);
    }

    return -1;
}

StateChunk *ChunkOverrideGroup::find(const StateChunkClass &type, 
                                           Int32            slot)
{
    ChunkBlock *pBlock = this->finalize(0x0000);

    if(pBlock != NULL)
    {
        return pBlock->find(type, slot);
    }

    return NULL;
}

/*-------------------------------------------------------------------------*/
/* Binary access                                                           */

UInt32 ChunkOverrideGroup::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ChunkBlockStoreFieldMask & whichField))
    {
        returnValue += _sfChunkBlockStore.getBinSize();
    }

    return returnValue;
}

void ChunkOverrideGroup::copyToBin(BinaryDataHandler  &pMem, 
                                   ConstFieldMaskArg   whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ChunkBlockStoreFieldMask & whichField))
    {
        _sfChunkBlockStore.copyToBin(pMem);
    }
}

void ChunkOverrideGroup::copyFromBin(BinaryDataHandler &pMem, 
                                     ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ChunkBlockStoreFieldMask & whichField))
    {
        _sfChunkBlockStore.copyFromBin(pMem);
    }
}

void ChunkOverrideGroup::addChunkBlock(ChunkBlock       * const pBlock,
                                       ChunkBlockMapKey         key)
{
    if(pBlock == NULL)
        return;

    if(key == MapKeyPool::the()->getDefault())
    {
        setFallbackChunkBlock(pBlock);
        return;
    }

    if(this->isMTLocal())
    {
        pBlock->addReferenceRecorded();
    }
    else
    {
        pBlock->addReferenceUnrecorded();
    }

#if 0
    pAttachment->linkParent(this, 
                            AttachmentsFieldId, 
                            Attachment::ParentsFieldId);
#endif

    Self::editSField(ChunkBlockStoreFieldMask);

    ChunkBlockPtrMapIt fcI = _sfChunkBlockStore.getValue().find(key);

    if(fcI != _sfChunkBlockStore.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        (*fcI).second = pBlock;
    }
    else
    {
        _sfChunkBlockStore.getValue()[key] = pBlock;
    }
}


void ChunkOverrideGroup::subChunkBlock(ChunkBlockMapKey key)
{
    if(key == MapKeyPool::the()->getDefault())
    {
        setFallbackChunkBlock(NULL);
        return;
    }

    Self::editSField(ChunkBlockStoreFieldMask);

    ChunkBlockPtrMapIt fcI;

    fcI = _sfChunkBlockStore.getValue().find(key);

    if(fcI != _sfChunkBlockStore.getValue().end())
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Attachment::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        _sfChunkBlockStore.getValue().erase(fcI);
    }
}

ChunkBlock *ChunkOverrideGroup::finalize(ChunkBlockMapKey oKey)
{
    ChunkBlockPtrMapConstIt fcI = _sfChunkBlockStore.getValue().find(oKey);

    if(fcI == _sfChunkBlockStore.getValue().end())
    {
        return _sfFallbackChunkBlock.getValue();
    }
    else
    {
        return (*fcI).second;
    }
}

const SFChunkBlockPtrMap *ChunkOverrideGroup::getSFChunkBlockStore(void) const
{
    return &_sfChunkBlockStore;
}

void ChunkOverrideGroup::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ChunkOverrideGroup::dump(      UInt32    ,
                              const BitVector ) const
{
    SLOG << "Dump ChunkOverrideGroup NI" << std::endl;
}

ActionBase::ResultE ChunkOverrideGroup::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    if(pAction != NULL)
    {
        pAction->pushState();

        ChunkBlock *pBlock = this->finalize(pAction->getRenderProperties());

        if(pBlock == NULL)
            return Inherited::renderEnter(action);

        MFUnrecStateChunkPtr::const_iterator chIt   = pBlock->beginChunks();
        MFUnrecStateChunkPtr::const_iterator chEnd  = pBlock->endChunks  ();
        UInt32                               uiSlot = 0;

        while(chIt != chEnd)
        {
            if(*chIt != NULL)
                pAction->addOverride(uiSlot, *chIt);
            
            ++uiSlot;
            ++chIt;
        }
    }

    return Inherited::renderEnter(action);
}

ActionBase::ResultE ChunkOverrideGroup::renderLeave(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    if(pAction != NULL)
    {
        pAction->popState();
    }


    return Inherited::renderLeave(action);
}

#ifdef OSG_MT_CPTR_ASPECT
void ChunkOverrideGroup::execSync(
          ChunkOverrideGroup *pFrom,
          ConstFieldMaskArg   whichField,
          AspectOffsetStore  &oOffsets,
          ConstFieldMaskArg   syncMode  ,
    const UInt32              uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ChunkBlockStoreFieldMask & whichField))
    {
//        _sfAttachments.syncWith(pFrom->_sfAttachments);

        // needs optimizing

#if 1
        ChunkBlockMap tmpMap;

        ChunkBlockPtrMapIt fcI = pFrom->_sfChunkBlockStore.getValue().begin();
        ChunkBlockPtrMapIt fcE = pFrom->_sfChunkBlockStore.getValue().end  ();
        
        while(fcI != fcE)
        {
            ChunkBlock *pBlock = convertToCurrentAspect((*fcI).second);

            if(pBlock != NULL)
            {
                tmpMap[(*fcI).first] = pBlock;

                pBlock->addReferenceUnrecorded();
            }

            ++fcI;
        }

        fcI = _sfChunkBlockStore.getValue().begin();
        fcE = _sfChunkBlockStore.getValue().end  ();

        while(fcI != fcE)
        {
            if(this->isMTLocal())
            {
                (*fcI).second->subReferenceRecorded();
            }
            else
            {
                (*fcI).second->subReferenceUnrecorded();
            }
            
            ++fcI;
        }

        _sfChunkBlockStore.setValue(tmpMap);
#endif
    }
}
#endif

void ChunkOverrideGroup::resolveLinks(void)
{
    Inherited::resolveLinks();

    ChunkBlockPtrMapIt fcI = _sfChunkBlockStore.getValue().begin();
    ChunkBlockPtrMapIt fcE = _sfChunkBlockStore.getValue().end  ();

    while(fcI != fcE)
    {
#if 0
        (*fcI).second->unlinkParent(this, 
                                    Material::ParentsFieldId);
#endif

        if(this->isMTLocal())
        {
            (*fcI).second->subReferenceRecorded();
        }
        else
        {
            (*fcI).second->subReferenceUnrecorded();
        }

        ++fcI;
    }

    _sfChunkBlockStore.getValue().clear();
}

EditFieldHandlePtr ChunkOverrideGroup::editHandleChunkBlockStore(void) 
{
    SFChunkBlockPtrMap::EditHandlePtr returnValue(
        new  SFChunkBlockPtrMap::EditHandle(
             &_sfChunkBlockStore, 
             this->getType().getFieldDesc(ChunkBlockStoreFieldId)));

    returnValue->setAddMethod(boost::bind(&ChunkOverrideGroup::addChunkBlock,
                                          this,
                                          _1,
                                          _2));

    editSField(ChunkBlockStoreFieldMask);

    return returnValue;
}

GetFieldHandlePtr ChunkOverrideGroup::getHandleChunkBlockStore(void) const
{
    SFChunkBlockPtrMap::GetHandlePtr returnValue(
        new  SFChunkBlockPtrMap::GetHandle(
             &_sfChunkBlockStore, 
             this->getType().getFieldDesc(ChunkBlockStoreFieldId)));

    return returnValue;
}

OSG_END_NAMESPACE
