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

#include "OSGFullStateChunk.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass FullStateChunk::_class("FullStateChunk", 1, 6);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FullStateChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

FullStateChunk::FullStateChunk(void) :
    Inherited()
{
}

FullStateChunk::FullStateChunk(const FullStateChunk &source) :
    Inherited(source)
{
}

FullStateChunk::~FullStateChunk(void)
{
}

/*------------------------------- Sync -----------------------------------*/

void FullStateChunk::changed(ConstFieldMaskArg whichField, 
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void FullStateChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump FullStateChunk NI" << std::endl;
}


/*---------------------- Chunk Class Access -------------------------------*/

const StateChunkClass *FullStateChunk::getClass(void) const
{
    return &_class;
}

void FullStateChunk::activate(DrawEnv    *, 
                              UInt32      )
{
    SFATAL << "FullStateChunk::activate" << std::endl;
}

void FullStateChunk::changeFrom(DrawEnv    *, 
                                StateChunk *,
                                UInt32      )
{
    SFATAL << "FullStateChunk::changeFrom" << std::endl;
}

void FullStateChunk::deactivate(DrawEnv    *, 
                                UInt32      )
{
    SFATAL << "FullStateChunk::deactivate" << std::endl;
}

/*-------------------------- Comparison -----------------------------------*/

/*! Calculate how expensive it is to switch from one instance of the chunk
    class to another. In most cases not implemented yet, will return 0.
 */

Real32 FullStateChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool FullStateChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

/*! Compare two chunks. In most cases not implemented yet, will return false.
 */

bool FullStateChunk::operator ==(const StateChunk &OSG_CHECK_ARG(other)) const
{
    return false;
}

bool FullStateChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}

OSG_END_NAMESPACE
