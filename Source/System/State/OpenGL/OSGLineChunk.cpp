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

#include "OSGGL.h"

#include "OSGWindow.h"

#include "OSGLineChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGLineChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGLineChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass LineChunk::_class("Line", 1, 50);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LineChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/


LineChunk::LineChunk(void) :
    Inherited()
{
}

LineChunk::LineChunk(const LineChunk &source) :
    Inherited(source)
{
}

LineChunk::~LineChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *LineChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void LineChunk::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*------------------------------ Output ----------------------------------*/

void LineChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LineChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void LineChunk::activate(DrawEnv *, UInt32)
{
    if(_sfWidth.getValue() != 1)
    {
        glLineWidth(_sfWidth.getValue());
    }
    
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(_sfStipplePattern.getValue() != 0xffffu)
    {
        glLineStipple(_sfStippleRepeat.getValue(), 
                      _sfStipplePattern.getValue());
        glEnable(GL_LINE_STIPPLE);
    }
#endif
    
#ifndef OSG_OGL_ES2
    if(_sfSmooth.getValue())
    {
        glEnable(GL_LINE_SMOOTH);
    }
#endif
}

void LineChunk::changeFrom(DrawEnv    *act, 
                           StateChunk *old_chunk, 
                           UInt32      index    )
{
    old_chunk->deactivate(act, index);

    activate( act, index );
}

void LineChunk::deactivate(DrawEnv *, UInt32)
{
    if(_sfWidth.getValue() != 1)
    {
        glLineWidth(1);
    }
    
#if !defined(OSG_OGL_COREONLY) || defined(OSG_CHECK_COREONLY)
    if(_sfStipplePattern.getValue() != 0xffffu)
    {
        glDisable(GL_LINE_STIPPLE);
    }
#endif
    
#ifndef OSG_OGL_ES2
    if(_sfSmooth.getValue())
    {
        glDisable(GL_LINE_SMOOTH);
    }
#endif
}

/*-------------------------- Comparison -----------------------------------*/

Real32 LineChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool LineChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool LineChunk::operator ==(const StateChunk &other) const
{
    LineChunk const *tother = dynamic_cast<LineChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getWidth()          != tother->getWidth()          ||
       getStipplePattern() != tother->getStipplePattern() ||
       getSmooth()         != tother->getSmooth()           )
    {
        return false;
    }

    return true;
}

/** \brief unequal
 */

bool LineChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

