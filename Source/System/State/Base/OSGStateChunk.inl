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

inline
UInt32 StateChunkClass::mapId(UInt32 id) const
{
    return (*_idMap)[id].first;
}

/*---------------------- Chunk Class Access -------------------------------*/

inline
UInt32 StateChunk::getClassId(void) const
{
    return getClass()->getId();
}

/*-------------------- Static Chunk Class Access --------------------------*/

inline
UInt32 StateChunk::getStaticClassId(void)
{
    return StateChunk::getStaticClass()->getId();
}

inline
const StateChunkClass *StateChunk::getStaticClass(void)
{
    return NULL;
}

inline
UInt32 StateChunkClass::getUsedSlots(void)
{
    return StateChunkClass::_numslots->size();
}

OSG_END_NAMESPACE

