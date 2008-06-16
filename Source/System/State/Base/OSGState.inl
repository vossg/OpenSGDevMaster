/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

/*! Return the chunk with the given id. Returns NullFC if no such chunk is in
   the State. 
*/

inline
StateChunk * const State::getChunk(UInt32 chunkId) const
{
    if(chunkId < _mfChunks.size())
        return _mfChunks[chunkId];

    return NULL;
}

/*! Checks if a chunk with the given id is in the current state. 
*/

inline
bool State::chunkPresent(UInt32 chunkId) const
{
    return (chunkId < _mfChunks.size() && _mfChunks[chunkId] != NULL);
}

/*! Checks if a chunk of the same type like the given one is in the current 
    state. 
*/

inline
bool State::chunkPresent(StateChunk *chunk) const
{
    const StateChunkClass * cls = chunk->getClass();
    
    for(UInt16 i = 0; i < cls->getNumSlots(); ++i)
    {
        if(chunkPresent(cls->getId() + i))
            return true;
    }
    
    return false;
}

inline
void State::setDefaultSortKey(UInt32 uiSortKey)
{
    _uiDefaultSortKey = (uiSortKey | DefaultKeyMask);
}

inline
UInt32 State::getSortKey(UInt32 uiKeyGen)
{
    if(_uiKeyGen != uiKeyGen && uiKeyGen < SkipRebuild)
    {
        _uiKeyGen = uiKeyGen;

        rebuildSortKey();
    }

    return _uiSortKey;
}

inline
const MFUnrecStateChunkPtr *State::getMFChunks(void) const
{
    return &_mfChunks;
}

OSG_END_NAMESPACE

