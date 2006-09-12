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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGColorMaskChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ColorMaskChunk
The color chunk contains the parameters that are specific for color write.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ColorMaskChunk::_class("Color");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorMaskChunk::initMethod(InitPhase ePhase)
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

ColorMaskChunk::ColorMaskChunk(void) :
    Inherited()
{
}

ColorMaskChunk::ColorMaskChunk(const ColorMaskChunk &source) :
    Inherited(source)
{
}

ColorMaskChunk::~ColorMaskChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *ColorMaskChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void ColorMaskChunk::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ColorMaskChunk::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump ColorMaskChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void ColorMaskChunk::activate(DrawEnv *, UInt32)
{
    glColorMask(getMaskR(), getMaskG(), getMaskB(), getMaskA());
}

void ColorMaskChunk::changeFrom(DrawEnv    *pEnv, 
                                StateChunk *old_chunk, 
                                UInt32      index )
{
    old_chunk->deactivate(pEnv, index);

    activate(pEnv, index);
}

void ColorMaskChunk::deactivate(DrawEnv *, UInt32)
{
    glColorMask(true, true, true, true);
}

/*-------------------------- Comparison -----------------------------------*/

Real32 ColorMaskChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool ColorMaskChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool ColorMaskChunk::operator == (const StateChunk &other) const
{
    ColorMaskChunk const *tother = dynamic_cast<ColorMaskChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getMaskR() != tother->getMaskR()  ||
       getMaskG() != tother->getMaskG()  ||
       getMaskB() != tother->getMaskB()  ||
       getMaskA() != tother->getMaskA()    )
    {
        return false;
    }

    return true;
}

/** \brief unequal
 */

bool ColorMaskChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGCOLORMASKCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLORMASKCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLORMASKCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

