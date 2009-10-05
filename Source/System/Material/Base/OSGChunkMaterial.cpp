/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGGL.h"

#include "OSGState.h"
#include "OSGMaterialDrawable.h"

#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGChunkMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGChunkMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void ChunkMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

ChunkMaterial::ChunkMaterial(void) :
    Inherited()
{
}

ChunkMaterial::ChunkMaterial(const ChunkMaterial &source) :
    Inherited(source)
{
}

ChunkMaterial::~ChunkMaterial(void)
{
}

void ChunkMaterial::pushToChunks(StateChunk * const value)
{
    if(value == NULL)
        return;

    editMField(ChunksFieldMask, _mfChunks);

    _mfChunks.push_back(value);
}

#if 0
void ChunkMaterial::assignChunks   (const MFUnrecStateChunkPtr &value)
{
    MFUnrecStateChunkPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecStateChunkPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<ChunkMaterial *>(this)->clearChunks();

    while(elemIt != elemEnd)
    {
        this->pushToChunks(*elemIt);

        ++elemIt;
    }
}
#endif

void ChunkMaterial::removeFromChunks(UInt32 uiIndex)
{
    if(uiIndex < _mfChunks.size())
    {
        editMField(ChunksFieldMask, _mfChunks);

/*
        MFUnrecStateChunkPtr::iterator fieldIt = _mfChunks.begin_nc();

        fieldIt += uiIndex;
 */

        _mfChunks.erase(uiIndex);

        if(uiIndex < _mfSlots.size())
        {
            editMField(SlotsFieldMask,  _mfSlots );
            
            MFInt32::iterator slotIt  = _mfSlots.begin();

            slotIt  += uiIndex;

            _mfSlots.erase(slotIt);
        }
    }
}

void ChunkMaterial::removeFromChunksByObj(StateChunk * const value)
{
    Int32 iElemIdx = _mfChunks.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ChunksFieldMask, _mfChunks);

/*
        MFUnrecStateChunkPtr::iterator fieldIt = _mfChunks.begin_nc();

        fieldIt += iElemIdx;
 */

        _mfChunks.erase(iElemIdx);

        if(iElemIdx < Int32(_mfSlots.size()))
        {
            editMField(SlotsFieldMask,  _mfSlots );
            
            MFInt32::iterator slotIt  = _mfSlots.begin();

            slotIt  += iElemIdx;

            _mfSlots.erase(slotIt);
        }
    }
}

void ChunkMaterial::replaceChunk(UInt32                       uiIndex,
                                 StateChunk           * const value  )
{
    if(uiIndex < _mfChunks.size() && value != NULL)
    {
        editMField(ChunksFieldMask, _mfChunks);

        _mfChunks.replace(uiIndex, value);
    }    
}


void ChunkMaterial::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*-------------------------- your_category---------------------------------*/

/*! Add the given chunk to the material. It is possible to specify
  which slot this chunk should be associated with. See \ref StateChunkClass 
  for a general description of the slots concept. The default slot is
  State::AutoSlotReplace. 
 */

bool ChunkMaterial::addChunk(StateChunk *chunk, Int32 slot)
{
    if(chunk == NULL)
        return false;

    if(slot != State::AutoSlotReplace)
    {
        editMField(SlotsFieldMask, _mfSlots);

        while(_mfSlots.size() < _mfChunks.size())
            _mfSlots.push_back(State::AutoSlotReplace);
    }
    
    editMField(ChunksFieldMask, _mfChunks);

    _mfChunks.push_back(chunk);
    
    if(slot != State::AutoSlotReplace)
    {
        editMField(SlotsFieldMask, _mfSlots);

        _mfSlots.push_back(slot);
    }
   
    return true;
}

/*! Remove the given chunk from the material. If the slot is not
State::AutoSlotReplace, only the given slot will be searched and
removed if found. Returns true if the chunk couldn't be found. */

bool ChunkMaterial::subChunk(StateChunk *chunk, Int32 slot)
{
    UInt32 i;
    
    const ChunkMaterial *pThis = this;

    for(i = 0; i < _mfChunks.size(); ++i)
    {
        if(pThis->_mfChunks[i] == chunk &&
           ((i < _mfSlots.size() && pThis->_mfSlots[i] == slot) ||
            slot == State::AutoSlotReplace))
        {
            editMField(ChunksFieldMask, _mfChunks);

            _mfChunks.erase(i);

            if(i < _mfSlots.size())
            {
                editMField(SlotsFieldMask, _mfSlots);

                _mfSlots.erase(_mfSlots.begin() + i);
            }

            return false;
        }
    }

    SWARNING << "ChunkMaterial::subChunk(" << this << ") has no chunk "
             << chunk << " with slot " << slot << std::endl;
             
    return true;
}

/*! Search the list of chunks for the given chunk. Returns its index, -1
  if the chunk is not used in the material.
*/

Int32 ChunkMaterial::find(StateChunk *chunk) const
{
    UInt32 i;
    
    for(i = 0; i < _mfChunks.size(); ++i)
    {
        if(_mfChunks[i] == chunk)
            return i;
    }
             
    return -1;
}

/*! Search the list of chunks for a chunk of the given type and the given
  slot. If slot is State::AutoSlotReplace, all slots are searched and the
  first found chunk is returned.
  For searching a specific chunk with a AutoSlotReplace slot,
  the slot parameter is interpreted as a index.
 */

StateChunk *ChunkMaterial::find(const FieldContainerType &type, 
                                      Int32               slot) const
{
    UInt32 index = 0;

    for(UInt32 i = 0; i < _mfChunks.size(); ++i)
    {
        StateChunk *p = _mfChunks[i];

        Int32 s = State::AutoSlotReplace;

        if(i < getMFSlots()->size())
            s = getSlots(i);

        if(s == State::AutoSlotReplace)
            s = index;

        if(p->getType() == type)
        {           
            if(slot == State::AutoSlotReplace || slot == s)
                return (p);

            ++index;
        }
    }

    return NULL;
}

#if 0
bool ChunkMaterial::operator==(const ChunkMaterial &other) const
{
    return Inherited::operator==(other);
}
#endif

void ChunkMaterial::clearChunks(void)
{
    editMField(ChunksFieldMask, _mfChunks);
    editMField(SlotsFieldMask,  _mfSlots );

    _mfChunks.clear();
    _mfSlots .clear();
}

/*! Add chunks to the given state. Needed for ordering in the drived
  materials.
*/

void ChunkMaterial::addChunks(State *state) const
{
    UInt32 i;
    
    for(i = 0; i < _mfChunks.size(); ++i)
    {
        state->addChunk(_mfChunks[i], 
                        (i < _mfSlots.size()) ? _mfSlots[i]
                                                : State::AutoSlotReplace);
    }
}

/*! Rebuild the internal State. Just collects the chunks in the State.
 */

void ChunkMaterial::rebuildState(void)
{
    FDEBUG(("ChunkMat::rebuild state\n"));

    if(_pState != NULL)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::createLocal();

        _pState->setDefaultSortKey(this->getId());

    }

    addChunks(_pState);
}

/*! Check if the Material (i.e. any of its chunks) is transparent..
 */

bool ChunkMaterial::isTransparent(void) const
{
    Int32 tm = getTransparencyMode();

    if(tm != Material::TransparencyAutoDetection)
    {
        return (tm == Material::TransparencyForceTransparent);
    }

    bool             returnValue = false;

    MFChunksType::const_iterator chunksIt  = _mfChunks.begin();
    MFChunksType::const_iterator chunksEnd = _mfChunks.end  ();

    for(; chunksIt != chunksEnd && returnValue == false; ++chunksIt)
    {
        returnValue = (*chunksIt)->isTransparent();
    }

    return returnValue;
}

/*------------------------------- dump ----------------------------------*/

void ChunkMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "ChunkMaterial at " << this << std::endl;
    SLOG << "Chunks: " << std::endl;

    UInt32 i;
    
    for(i = 0; i < _mfChunks.size(); ++i)
    {
        SLOG << _mfChunks[i] << " "
             << static_cast<Int32>((i < _mfSlots.size()) 
                                   ? _mfSlots[i]
                                   :   State::AutoSlotReplace)
             << std::endl;
    }
}
