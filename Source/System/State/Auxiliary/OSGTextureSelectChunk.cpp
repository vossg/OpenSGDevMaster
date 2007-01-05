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

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGImage.h>

#include "OSGDrawActionBase.h"
#include "OSGDrawEnv.h"

#include "OSGTextureSelectChunk.h"
#include "OSGTextureBaseChunk.h"

//#define OSG_DUMP_TEX

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureSelectChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureSelectChunk.fcd) and
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

void TextureSelectChunk::initMethod(InitPhase ePhase)
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

TextureSelectChunk::TextureSelectChunk(void) :
    Inherited()
{
}

TextureSelectChunk::TextureSelectChunk(const TextureSelectChunk &source) :
    Inherited(source)
{
}

TextureSelectChunk::~TextureSelectChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep
    it consistent with the cubeTexture specifics
*/

void TextureSelectChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

bool TextureSelectChunk::isTransparent(void) const
{
    // Even if the texture has alpha, the Blending is makes the sorting
    // important, thus textures per se are not transparent
    return false;
}


/*----------------------------- onCreate --------------------------------*/

void TextureSelectChunk::onCreate(const TextureSelectChunk *source)
{
    Inherited::onCreate(source);
}

void TextureSelectChunk::onCreateAspect(const TextureSelectChunk *createAspect,
                                        const TextureSelectChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

/*------------------------------ Output ----------------------------------*/

void TextureSelectChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TextureSelectChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/


void TextureSelectChunk::activate(DrawEnv *pEnv, UInt32 idx)
{    
    if(_sfChoice.getValue() >= _mfTextures.size())
    {
        FWARNING(("TextureSelect::activate choice beyond size %d %d!\n",
                  _sfChoice.getValue(), 
                  _mfTextures.size  ()));
        return;        
    }

    _mfTextures[_sfChoice.getValue()]->activate(pEnv, idx);
}


void TextureSelectChunk::changeFrom(DrawEnv    *pEnv,
                                    StateChunk *old   ,
                                    UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if(old == this)
        return;

    if(_sfChoice.getValue() >= _mfTextures.size())
    {
        FWARNING(("TextureSelect::changeFrom choice beyond size %d %d!\n",
                  _sfChoice.getValue(), 
                  _mfTextures.size  ()));
        return;        
    }

    _mfTextures[_sfChoice.getValue()]->changeFrom(pEnv, old, idx);
}

void TextureSelectChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    if(_sfChoice.getValue() >= _mfTextures.size())
    {
        FWARNING(("TextureSelect::deactivate choice beyond size %d %d!\n",
                  _sfChoice.getValue(), 
                  _mfTextures.size  ()));
        return;        
    }

    _mfTextures[_sfChoice.getValue()]->deactivate(pEnv, idx);
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TextureSelectChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureSelectChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TextureSelectChunk::operator == (const StateChunk &other) const
{
    bool returnValue = false;

    return returnValue;
}

bool TextureSelectChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGTEXTURESELECTCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTURESELECTCHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTURESELECTCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

