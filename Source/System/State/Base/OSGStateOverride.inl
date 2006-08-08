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
    _vChunks = pState->_vChunks;
}

inline
void StateOverride::reset(void)
{
    _vChunks.clear();
}

inline
void StateOverride::addOverride(UInt32 uiSlot, StateChunk *pChunk)
{
    ChunkElement newElem(uiSlot, pChunk);

    ChunkStoreIt cIt = std::lower_bound(_vChunks.begin(),
                                        _vChunks.end  (),
                                         newElem);

    if(cIt == _vChunks.end())
    {
        _vChunks.insert(cIt, newElem);
    }
    else
    {
        if(cIt->first == uiSlot)
        {
            cIt->second = pChunk;
        }
        else
        {
            _vChunks.insert(cIt, newElem);
        }
    }
}

inline
bool StateOverride::empty(void)
{
    return _vChunks.empty();
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

OSG_END_NAMESPACE

#define OSGSTATEOVERRIDE_INLINE_CVSID "@(#)$Id: OSGStateOverride.inl,v 1.1.2.1 2006/04/21 02:27:50 vossg Exp $"
