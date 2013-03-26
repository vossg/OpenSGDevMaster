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

#include "OSGChunkBlock.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGChunkBlckBase.cpp file.
// To modify it, please change the .fcd file (OSGChunkBlock.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ChunkBlock::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ChunkBlock::ChunkBlock(void) :
    Inherited()
{
}

ChunkBlock::ChunkBlock(const ChunkBlock &source) :
    Inherited(source)
{
}

ChunkBlock::~ChunkBlock(void)
{
}

/*----------------------------- class specific ----------------------------*/

bool ChunkBlock::addChunk(StateChunk *chunk, 
                          Int32       slot)
{
    if(chunk == NULL)
    {
        SWARNING << "addChunk: no chunk given, use subChunk to clear a slot" 
                 << std::endl;

        return false;
    }

    if(slot > 0 && slot > chunk->getClass()->getNumSlots())
    {
        SWARNING << "addChunk: index " 
                 << slot
                 << " > Numslots "
                 << chunk->getClass()->getNumSlots()
                 << ",  ignored!" 
                 << std::endl;

        return false;
    }

    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size32();

    const ChunkBlock *pThis = this;

    // special case: find empty slot automatically
    if(slot == State::AutoSlot || slot == State::AutoSlotReplace)
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for(ci = cindex; ci < cindex + nslots && ci < csize; ++ci)
        {
            if(pThis->_mfChunks[ci] == NULL)
            {
                break;
            }
        }

        if(ci >= cindex + nslots)    // no free slot found
        {
            if(slot == State::AutoSlot)
            {
                SWARNING << "addChunk: no free slot found for "
                         << chunk->getClass()->getName() 
                         << " class, ignored!" << std::endl;
                return false;
            }
            // use last slot
            --ci;
        }

        cindex = ci;
    }
    else
    {
        cindex += slot;
    }

    editMField(ChunksFieldMask, _mfChunks);

    // add the chunk to the state at cindex
    if(cindex >= csize)
    {
        UInt32 newsize = cindex + 1;

        _mfChunks.resize(newsize, NULL);
    }

    _mfChunks.replace(cindex, chunk);
    
    return true;
}

bool ChunkBlock::subChunk(StateChunk *chunk, 
                          Int32       slot)
{
    if(chunk == NULL)
        return false;
        
    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size32();

    // special case: find it in the slots
    UInt8 nslots = chunk->getClass()->getNumSlots();
    UInt8 ci;

    const ChunkBlock *pThis = this;

    if(slot == State::AutoSlot || slot == State::AutoSlotReplace)
    {
        for(ci = cindex; ci < cindex + nslots && ci < csize; ci++)
        {
            if(pThis->_mfChunks[ci] == chunk)
            {
                break;
            }
        }
        
        if(ci >= cindex + nslots || ci >= csize)    // chunk not found
        {
            SWARNING << "subChunk: chunk " 
                     << chunk
                     << " of class "
                     << chunk->getClass()->getName()
                     << " not found!" 
                     << std::endl;
            return false;
        }
        
        editMField(ChunksFieldMask, _mfChunks);
        
        // remove the chunk from the state
        _mfChunks.replace(ci, NULL);
    }
    else
    {
        ci = cindex + slot;

        if(ci    >=  cindex + nslots        || 
           ci    >= pThis->_mfChunks.size() ||
           chunk != pThis->_mfChunks[ci]     )    // chunk not found
        {
            SWARNING << "subChunk: chunk " 
                     << chunk
                     << " of class "
                     << chunk->getClass()->getName()
                     << " not found!" 
                     << std::endl;
            return false;
        }        

        editMField(ChunksFieldMask, _mfChunks);
        
        // remove the chunk from the state
        _mfChunks.replace(ci, NULL);
    }

    return true;
}

Int32 ChunkBlock::find(StateChunk *chunk)
{
    UInt32 i;

    const ChunkBlock *pThis = this;
    
    for(i = 0; i < _mfChunks.size(); ++i)
    {
        if(pThis->_mfChunks[i] == chunk)
            return i;
    }
             
    return -1;
}

StateChunk *ChunkBlock::find(const StateChunkClass &type, 
                                   Int32            slot)
{
    UInt32 cindex =  type.getId();
    UInt32 csize  = _mfChunks.size32();

    // special case: find it in the slots
    UInt8 nslots = type.getNumSlots();
    UInt8 ci;

    const ChunkBlock *pThis = this;

    if(slot == State::AutoSlot || slot == State::AutoSlotReplace)
    {
        for(ci = cindex; ci < cindex + nslots && ci < csize; ci++)
        {
            StateChunk *chunk = pThis->_mfChunks[ci];

            if(chunk != NULL && *(chunk->getClass()) == type)
            {
                return chunk;
            }
        }
    }
    else
    {
        ci = cindex + slot;

        if(ci    <  cindex + nslots || 
           ci    < _mfChunks.size()  )    
        {
            StateChunk *chunk = pThis->_mfChunks[ci];

            if(chunk != NULL && *(chunk->getClass()) == type)
            {
                return chunk;
            }
        }
    }

    return NULL;
}


void ChunkBlock::changed(ConstFieldMaskArg whichField, 
                         UInt32            origin,
                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ChunkBlock::dump(      UInt32    ,
                      const BitVector ) const
{
    SLOG << "Dump ChunkOverrideGroup NI" << std::endl;
}

Int32 ChunkBlock::getSlot(StateChunk *pChunk)
{
    if(pChunk == NULL)
        return -1;

    Int32 iPos = this->find(pChunk);

    if(iPos == -1)
        return -1;

    return iPos - pChunk->getClassId();
}

void ChunkBlock::pushToChunks(StateChunk * const value)
{
    if(value != NULL)
    {
        // addChunk(value) does not work as expected
        //
        // Do at least a sanity check if the slot matches
        // the chunk

        if(_mfChunks.size() < value->getClassId() ||
           _mfChunks.size() >= (value->getClassId() + 
                                value->getClass()->getNumSlots()))
        {
            SWARNING << "pushToChunk: chunk (" 
                     << value->getClassId()
                     << " | "
                     << value->getClass()->getNumSlots()
                     << ") does not match available slot "
                     << _mfChunks.size()
                     << ",  ignored!" 
                     << std::endl;
            
            
            return;
        }
    }

    editMField(ChunksFieldMask, _mfChunks);

    _mfChunks.push_back(value);
}

void ChunkBlock::replaceChunk(UInt32             uiIndex,
                              StateChunk * const value   )
{
    if(uiIndex < _mfChunks.size())
    {
        editMField(ChunksFieldMask, _mfChunks);

        _mfChunks.replace(uiIndex, value);
    }
}

void ChunkBlock::removeFromChunks(UInt32 uiIndex)
{
    if(uiIndex < _mfChunks.size())
    {
        editMField(ChunksFieldMask, _mfChunks);

        _mfChunks.replace(uiIndex, NULL);
    }
}

void ChunkBlock::removeFromChunks(StateChunk * const value)
{
    Int32 iElemIdx = _mfChunks.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

        _mfChunks.replace(iElemIdx, NULL);
    }
}

void ChunkBlock::clearChunks(void)
{
    editMField(ChunksFieldMask, _mfChunks);

    _mfChunks.clear();
}

OSG_END_NAMESPACE
