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

#include "OSGFogChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFogChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGFogChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass FogChunk::_class("Fog");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FogChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FogChunk::FogChunk(void) :
    Inherited()
{
}

FogChunk::FogChunk(const FogChunk &source) :
    Inherited(source)
{
}

FogChunk::~FogChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *FogChunk::getClass(void) const
{
    return &_class;
}

void FogChunk::activate(DrawEnv *pEnv, UInt32 /* index */)
{
    glFogi (GL_FOG_MODE,    getMode   ()                );
    glFogf (GL_FOG_DENSITY, getDensity()                );
    glFogf (GL_FOG_START,   getStart  ()                );
    glFogf (GL_FOG_END,     getEnd    ()                );
    glFogfv(GL_FOG_COLOR,   getColor  ().getValuesRGBA());

    glEnable(GL_FOG);
}

void FogChunk::changeFrom(DrawEnv    *pEnv,
                          StateChunk *oldChunk,
                          UInt32     index     )
{
    oldChunk->deactivate(pEnv, index);
    this    ->activate  (pEnv, index);
}

void FogChunk::deactivate(DrawEnv * /* pEnv */, UInt32 /* index */)
{
    glDisable(GL_FOG);
}

bool FogChunk::isTransparent(void) const
{
    return false;
}

void FogChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FogChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FogChunk NI" << std::endl;
}

Real32 FogChunk::switchCost(StateChunk * /* chunk */)
{
    return 0;
}

bool FogChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool FogChunk::operator == (const StateChunk &other) const
{
    FogChunk const *tother = dynamic_cast<FogChunk const *>(&other);

    if(tother == NULL)
        return false;

    if(getMode() != tother->getMode())
        return false;

    if(getDensity() != tother->getDensity())
        return false;

    if(getStart() != tother->getStart())
        return false;

    if(getEnd() != tother->getEnd())
        return false;

    if(getColor() != tother->getColor())
        return false;

    return true;
}

bool FogChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

OSG_END_NAMESPACE
