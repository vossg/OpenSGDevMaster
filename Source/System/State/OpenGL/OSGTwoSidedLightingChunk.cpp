/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGGL.h>

#include "OSGTwoSidedLightingChunk.h"
#include <OSGWindow.h>
#include <OSGDrawActionBase.h>
#include <OSGCamera.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TwoSidedLightingChunk::_class("TwoSidedLighting");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TwoSidedLightingChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

TwoSidedLightingChunk::TwoSidedLightingChunk(void) :
     Inherited(        ),
    _state    (GL_FALSE)
{
}

TwoSidedLightingChunk::TwoSidedLightingChunk(
    const TwoSidedLightingChunk &source) :

    Inherited(source),
    _state(source._state)
{
}

TwoSidedLightingChunk::~TwoSidedLightingChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TwoSidedLightingChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void TwoSidedLightingChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void TwoSidedLightingChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TwoSidedLightingChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void TwoSidedLightingChunk::activate (DrawEnv *pEnv, UInt32 idx)
{
    glGetBooleanv(GL_LIGHT_MODEL_TWO_SIDE, &_state);
    if(_state == GL_FALSE)
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void TwoSidedLightingChunk::changeFrom(DrawEnv    *pEnv, 
                                       StateChunk *old_chunk, 
                                       UInt32      idx      )
{
    TwoSidedLightingChunk *old = 
        dynamic_cast<TwoSidedLightingChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "TwoSidedLightingChunk::changeFrom: "
                   "caught non-TwoSidedLightingChunk!\n"));
        return;
    }

    // TwoSidedLightingChunk didn't change so do nothing.
    if(old == this)
        return;

    _state = old->_state;

    if(_state == GL_FALSE)
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void TwoSidedLightingChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    GLboolean tsl = GL_FALSE;

    glGetBooleanv(GL_LIGHT_MODEL_TWO_SIDE, &tsl);

    if(_state != tsl)
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, _state);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 TwoSidedLightingChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TwoSidedLightingChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

bool TwoSidedLightingChunk::operator ==(const StateChunk &other) const
{
    TwoSidedLightingChunk const *tother = 
                dynamic_cast<TwoSidedLightingChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return true;
}

bool TwoSidedLightingChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: O$";
    static char cvsid_hpp[] = OSGTWOSIDEDLIGHTINGCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGTWOSIDEDLIGHTINGCHUNK_HEADER_CVSID;
}
