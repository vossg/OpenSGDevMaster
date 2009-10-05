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

#include "OSGConfig.h"

#include "OSGChunkOverrideGroup.h"
#include "OSGRenderAction.h"
#include "OSGChunkBlock.h"
#include "OSGStateChunk.h"

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
    Inherited()
{
}

ChunkOverrideGroup::ChunkOverrideGroup(const ChunkOverrideGroup &source) :
    Inherited(source)
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

void ChunkOverrideGroup::addChunkBlock(ChunkBlock       * const pBlock,
                                       ChunkBlockMapKey         key)
{
    Inherited::addElement(pBlock, key);
}


void ChunkOverrideGroup::subChunkBlock(ChunkBlockMapKey key)
{
    Inherited::subElement(key);
}

const SFChunkBlockPtrMap *ChunkOverrideGroup::getSFChunkBlockStore(void) const
{
    return Inherited::getMapCacheField();
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

OSG_END_NAMESPACE
