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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <OSGGL.h>

#include "OSGStateChunk.h"

#include "OSGState.h"

#include "OSGTextureBaseChunk.h"
#include "OSGMaterialChunk.h"

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

OSG_BEGIN_NAMESPACE

/*! \ingroup STLHelpers
    \hideinhierarchy
    Helper struct to remove chunks from a state.
*/

struct ClearSlot : public std::unary_function<StateChunkPtr &, 
                                              void>
{
    void operator() (StateChunkPtr &slotPtr) 
    { 
        subRef(slotPtr);
        
        slotPtr = NullFC;
    }
};

OSG_END_NAMESPACE

#endif

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGStateBase.cpp file.
// To modify it, please change the .fcd file (OSGState.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void State::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void State::onCreateAspect(const State *createAspect,
                           const State *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    UInt32 uiTId = TextureBaseChunk::getStaticClassId() & 0x000003FF;
    UInt32 uiMId = MaterialChunk   ::getStaticClassId() & 0x000003FF;
    
    _uiKeyGen = (uiTId | (uiMId << 10) | (Key1Mask << 20));
    
/*
    fprintf(stderr, "CreateKeyGen (%p | %p | %p) from %d %d -> %08x\n",
            this,
            createAspect,
            source,
            TextureChunk ::getStaticClassId(),
            MaterialChunk::getStaticClassId(),
            _uiKeyGen);
*/
}

/*------------- constructors & destructors --------------------------------*/

State::State(void) :
     Inherited       ( ),
    _uiDefaultSortKey(0),
    _uiSortKey       (0),
    _uiKeyGen        (0)
{
}

State::State(const State &source) :
     Inherited       (source),
    _uiDefaultSortKey(     0),
    _uiSortKey       (     0),
    _uiKeyGen        (     0)
{
}

State::~State(void)
{
//    clearChunks();
}

void State::rebuildSortKey(void)
{
    UInt32 uiKey1 =  _uiKeyGen & Key1Mask;
    UInt32 uiKey2 = (_uiKeyGen & Key2Mask) >> 10;
    UInt32 uiKey3 = (_uiKeyGen & Key3Mask) >> 20;

    UInt32 uiSizeChunks = _mfChunks.size();

//    fprintf(stderr, "Got Keys %d %d %d\n", uiKey1, uiKey2, uiKey3);

    if(uiKey1 != InvalidKey && uiKey1 < uiSizeChunks)
    {
        uiKey1 = 
            (_mfChunks[uiKey1]              != NullFC && 
             _mfChunks[uiKey1]->getIgnore() == false   ) ? 

            _mfChunks[uiKey1]->getChunkId() : 0;
    }
    else
    {
        uiKey1 = 0x00000000;
    }

    if(uiKey2 != InvalidKey && uiKey2 < uiSizeChunks)
    {
        uiKey2 = 
            (_mfChunks[uiKey2]              != NullFC &&
             _mfChunks[uiKey2]->getIgnore() == false   ) ? 

            _mfChunks[uiKey2]->getChunkId() : 0;
    }
    else
    {
        uiKey2 = 0x00000000;
    }

    if(uiKey3 != InvalidKey && uiKey3 < uiSizeChunks)
    {
        uiKey3 = 
            (_mfChunks[uiKey3]              != NullFC &&
             _mfChunks[uiKey3]->getIgnore() == false   ) ? 

            _mfChunks[uiKey3]->getChunkId() : 0;
    }
    else
    {
        uiKey3 = 0x00000000;
    }

    _uiSortKey = 
         (uiKey1 & Key1Mask)        | 
        ((uiKey2 & Key1Mask) << 10) |
        ((uiKey3 & Key1Mask) << 20);

    if(_uiSortKey == 0x00000000)
    {
        _uiSortKey = _uiDefaultSortKey;
    }

/*
    fprintf(stderr, "Use Sort Key : %08x %08x %08x %08x -> %08x\n",
             uiKey1,
             uiKey2,
             uiKey3,
            _uiDefaultSortKey,
            _uiSortKey);
 */
}

void State::changed(ConstFieldMaskArg whichField, 
                    UInt32            origin,
                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    rebuildSortKey();
}

/*------------------------------- dump ----------------------------------*/

void State::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                 const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    std::cerr << "State at " << this << std::endl;

    MFStateChunkPtr::const_iterator it;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end(); it++, cind++)
    {
        std::cerr << StateChunkClass::getName(cind) << "\t";

        if(*it == NullFC)
        {
            std::cerr << "NullChunk" << std::endl;
        }
        else
        {
            std::cerr << *it << std::endl;
        }
    }
}

/*-------------------- OpenGL State Management --------------------------*/

/*! Activate (i.e. call all their OpenGL commands) the current set of
    StateChunks. Activate will simply overwrite whatever was set before. 
*/

void State::activate(DrawEnv *pEnv)
{
    MFStateChunkPtr::iterator it;
    Int32                     ind = 0;
    UInt32                    cind;

    for(  it  = _mfChunks.begin(), cind = 0; 
          it != _mfChunks.end  ();
        ++it, ++cind)
    {
        if(*it != NullFC && (*it)->getIgnore() == false)
        {
            (*it)->activate(pEnv, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}


/*! Switch to this state from the given old State. The chunks will try to 
    optimize the transition.
*/

void State::changeFrom(DrawEnv *pEnv, State *pOld)
{
    MFStateChunkPtr::iterator it;
    Int32                     ind = 0;
    UInt32                    i;
    UInt32                    cind;

    for(  it = _mfChunks.begin(), cind = 0; 
          it != _mfChunks.end();
        ++it, ++cind)
    {
        StateChunkPtr o = pOld->getChunk(cind);
        StateChunkPtr n = *it;

        if(n != NullFC && n->getIgnore() == false)
        {
            if(o != NullFC && o->getIgnore() == false)
            {
                n->changeFrom(pEnv, getCPtr(o), UInt32(ind));
            }
            else
            {
                n->activate(pEnv, UInt32(ind));
            }
        }
        else if(o != NullFC && o->getIgnore() == false)
        {
            o->deactivate(pEnv, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }

    if(ind >= StateChunkClass::getNumSlots(cind))
        ind = 0;

    for(i = cind; i < pOld->getChunks().size(); ++i)
    {
        StateChunkPtr o = pOld->getChunk(i);

        if(o != NullFC && o->getIgnore() == false)
        {
            o->deactivate(pEnv, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }
}


/*! Deactivate the current set of StateChunks, i.e. switch everything back to
    the default state for the OpenGL state covered by the given chunks.
*/

void State::deactivate(DrawEnv *pEnv)
{
    MFStateChunkPtr::iterator it;
    Int32                     ind = 0;
    UInt32                    cind;

    for(  it =  _mfChunks.begin(), cind = 0; 
          it != _mfChunks.end  ();
        ++it, ++cind)
    {
        if(*it != NullFC && (*it)->getIgnore() == false)
            (*it)->deactivate(pEnv, UInt32(ind));

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}

/*---------------------------- Access -----------------------------------*/

/*! Add the given chunk to the State. The index defines the behaviour,
    especially for multi-slot chunks. 

    If it is set to AutoSlotReplace (the default), addChunk will try to find an
    empty slot for the chunk class, if it doesn't find one the last one will be
    replaced with the new entry. This is also useful for chunk classes with
    only a single slot, as it will override an old instance of the chunk class,
    which is usually the desired behaviour.
    
    If it is set to AutoSlot, the new chunk will only be added to the State if
    there is a free slot. If there is no free slot true will be returned, in
    all other cases it will be false.
    
    If the index is explicitly given (i.e. it is >=0) the chunk will be set
    into the given slot, possibly overwriting an old entry. If the index is
    larger than the number of slots for the given chunck class true will be
    returned.
*/

bool State::addChunk(StateChunkPtr chunk, Int32 index)
{
    if(index > 0 && index > chunk->getClass()->getNumSlots())
    {
        SWARNING << "addChunk: index " 
                 << index
                 << " > Numslots "
                 << chunk->getClass()->getNumSlots()
                 << ",  ignored!" 
                 << std::endl;
        return true;
    }

    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size();

    // special case: find empty slot automatically
    if(index == AutoSlot || index == AutoSlotReplace)
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for(ci = cindex; ci < cindex + nslots && ci < csize; ++ci)
        {
            if(_mfChunks[ci] == NullFC)
            {
                break;
            }
        }

        if(ci >= cindex + nslots)    // no free slot found
        {
            if(index == AutoSlot)
            {
                SWARNING << "addChunk: no free slot found for "
                         << chunk->getClass()->getName() 
                         << " class, ignored!" << std::endl;
                return true;
            }
            // use last slot
            --ci;
        }

        cindex = ci;
    }
    else
    {
        cindex += index;
    }

    editMField(ChunksFieldMask, _mfChunks);

    // add the chunk to the state at cindex
    if(cindex >= csize)
    {
        UInt32 oldsize = csize;
        UInt32 newsize = cindex + 1;

        _mfChunks.resize(newsize);

        for(UInt32 i = oldsize; i < newsize; i++)
        {
            _mfChunks[i] = NullFC;
        }
    }

    setRefd(_mfChunks[cindex], chunk);
    
    return false;
}

/*! Remove the given chunk from the State. Returns false if successful, true if
    the chunk wasn't found.
*/

bool State::subChunk(StateChunkPtr chunk)
{
    if(chunk == NullFC)
        return true;
        
    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size();

    // special case: find it in the slots
    UInt8 nslots = chunk->getClass()->getNumSlots();
    UInt8 ci;

    for(ci = cindex; ci < cindex + nslots && ci < csize; ci++)
    {
        if(_mfChunks[ci] == chunk)
        {
            break;
        }
    }

    if(ci >= cindex + nslots)    // chunk not found
    {
        SWARNING << "subChunk: chunk " 
                 << chunk
                 << " of class "
                 << chunk->getClass()->getName()
                 << " not found!" 
                 << std::endl;
        return true;
    }

    editMField(ChunksFieldMask, _mfChunks);

    // remove the chunk from the state

    subRef(_mfChunks[ci]);

    _mfChunks[ci] = NullFC;
    
    return false;
}


/*! Remove the chunk defined by the class id and the slot index from the State. 
    Returns false if successful, true if the chunk wasn't found.
*/

bool State::subChunk(UInt32 classid, Int32 index)
{
    if(index < 0 || index > StateChunkClass::getNumSlots(classid))
    {
        SWARNING << "subChunk: index " << index << " > Numslots "
                 << StateChunkClass::getNumSlots(classid)
                 << ",  ignored!" << std::endl;
        return true;
    }

    if(_mfChunks[classid + index] == NullFC)
        return true;

    editMField(ChunksFieldMask, _mfChunks);

    // remove the chunk from the state

    subRef(_mfChunks[classid + index]);

    _mfChunks[classid + index] = NullFC;
    
    return false;
}

/*! Remove all chunks from the state
*/

void State::clearChunks(void)
{
    editMField(ChunksFieldMask, _mfChunks);

    std::for_each(_mfChunks.begin(), 
                  _mfChunks.end  (),
                   ClearSlot());
}

bool State::isTransparent(void) const
{
    bool returnValue = false;

    MFStateChunkPtr::const_iterator it        = _mfChunks.begin();
    MFStateChunkPtr::const_iterator chunksEnd = _mfChunks.end();

    for(; it != chunksEnd && returnValue == false; ++it)
    {
        if((*it) != NullFC)
        {
            returnValue =(*it)->isTransparent();
        }
    }

    return returnValue;
}

/*-------------------------- comparison -----------------------------------*/


/*! Calculate the switch cost for the whole state, which is the sum of the
switch cost of all its chunks. Right now it's always 0.
*/

Real32 State::switchCost(State *OSG_CHECK_ARG(state))
{
    return 0;
}

bool State::operator < (const State &other) const
{
    return this < &other;
}

/*! Compare the two states. Not implemented yet, always false.
*/

bool State::operator == (const State &OSG_CHECK_ARG(other)) const
{
    return false;
}

bool State::operator != (const State &other) const
{
    return ! (*this == other);
}
