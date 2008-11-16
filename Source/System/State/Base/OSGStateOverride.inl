/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

inline
bool operator <(const StateOverride::ChunkElement &lhs, 
                const StateOverride::ChunkElement &rhs)
{
    return lhs.first < rhs.first;
}

inline
void StateOverride::fillFrom(StateOverride *pState)
{
    _vChunks        = pState->_vChunks;


    _pShader        = pState->_pShader;
    _pShaderVar     = pState->_pShaderVar;


    _vProgChunks    = pState->_vProgChunks;
    _vProgIds       = pState->_vProgIds;

    _vProgVarChunks = pState->_vProgVarChunks;
    _vProgVarIds    = pState->_vProgVarIds;


    _uiSortKey      = pState->_uiSortKey;
    _uiKeyGen       = pState->_uiKeyGen;
    _uiKeyMask      = pState->_uiKeyMask;
}

inline
void StateOverride::setKeyGen(UInt32 uiKeyGen)
{
    _uiKeyGen = uiKeyGen;
}

inline
void StateOverride::updateSortKey(UInt32 &uiSortKey, 
                                  UInt32  uiKeyGen)
{
    if(_uiKeyGen != uiKeyGen && uiKeyGen < SkipRebuild)
    {
        _uiKeyGen = uiKeyGen;

        rebuildSortKey();
    }

    if(_uiSortKey != 0x0000)
    {
        uiSortKey = (uiSortKey & _uiKeyMask) | _uiKeyGen;
    }
}

inline
void StateOverride::reset(void)
{
    _vChunks.clear();

    _pShader    = NULL;
    _pShaderVar = NULL;


    _vProgChunks.clear();
    _vProgIds   .clear();

    _vProgVarChunks.clear();
    _vProgVarIds   .clear();


    _uiSortKey  = 0;
    _uiKeyGen   = 0;
    _uiKeyMask  = 0;
}

inline
bool StateOverride::empty(void)
{
    return _vChunks.empty();
}

inline
bool StateOverride::isTransparent(void)
{
    ChunkStoreIt cIt  = _vChunks.begin();
    ChunkStoreIt cEnd = _vChunks.end  ();

    for(; cIt != cEnd; ++cIt)
    {
        if(cIt->second != NULL && cIt->second->isTransparent() == true)
        {
            return true;
        }
    }

    return false;
}

inline
StateOverride::ChunkStoreIt StateOverride::begin(void)
{
    return _vChunks.begin();
}

inline
StateOverride::ChunkStoreIt StateOverride::end(void)
{
    return _vChunks.end();
}

inline
UInt32 StateOverride::size(void)
{
    return _vChunks.size();
}

inline
const StateOverride::IdStore &StateOverride::getProgIds(void)
{
    return _vProgIds;
}

inline
const StateOverride::ProgramChunkStore &StateOverride::getPrograms(void)
{
    return _vProgChunks;
}

inline
const StateOverride::IdStore &StateOverride::getVarIds(void)
{
    return _vProgVarIds;
}

inline
const StateOverride::ProgramVarChunkStore &StateOverride::getVariables(void)
{
    return _vProgVarChunks;
}

inline
void StateOverride::setShader(ShaderExecutableChunk *pShader)
{
    _pShader = pShader;
}

inline
ShaderExecutableChunk *StateOverride::getShader(void)
{
    return _pShader;
}

inline
void StateOverride::setShaderVar(ShaderExecutableVarChunk *pVar)
{
    _pShaderVar = pVar;
}

inline
ShaderExecutableVarChunk *StateOverride::getShaderVar(void)
{
    return _pShaderVar;
}

OSG_END_NAMESPACE
