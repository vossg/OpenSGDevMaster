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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>

#include <OSGSHLChunk.h>
#include <OSGDrawEnv.h>
#include <OSGWindow.h>

#include "OSGSHLParameterChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGSHLParameterChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGSHLParameterChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLParameterChunk::_class("SHLParameter", 1, 31);

volatile UInt16 SHLParameterChunk::_uiChunkCounter = 1;

UInt32 SHLParameterChunk::_shl_extension = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SHLParameterChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _shl_extension = 
            Window::registerExtension("GL_ARB_shading_language_100");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SHLParameterChunk::SHLParameterChunk(void) :
     Inherited( ),
    _uiChunkId(0)
{
}

SHLParameterChunk::SHLParameterChunk(const SHLParameterChunk &source) :
     Inherited(source),
    _uiChunkId(     0)
{
 
}

SHLParameterChunk::~SHLParameterChunk(void)
{
}

void SHLParameterChunk::onCreate(const SHLParameterChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void SHLParameterChunk::onCreateAspect(const SHLParameterChunk *createAspect,
                                       const SHLParameterChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

const StateChunkClass *SHLParameterChunk::getClass(void) const
{
    return &_class;
}

UInt16 SHLParameterChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void SHLParameterChunk::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SHLParameterChunk::dump(      UInt32    ,
                             const BitVector ) const
{
    SLOG << "Dump SHLParameterChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void SHLParameterChunk::activate(DrawEnv *pEnv, UInt32 /*idx*/)
{
    if(!pEnv->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't "
                  "find extension 'GL_ARB_shading_language_100'!\n"));

        return;
    }

    updateParameters(pEnv->getWindow());
}

void SHLParameterChunk::changeFrom(DrawEnv    *pEnv, 
                                   StateChunk *old_chunk,
                                   UInt32      /*idx*/)
{
    SHLParameterChunk *old = dynamic_cast<SHLParameterChunk *>(old_chunk);

    if(old == this)
        return;

    if(!pEnv->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't "
                  "find extension 'GL_ARB_shading_language_100'!\n"));

        return;
    }

    if(old == NULL)
    {
        FWARNING(( "SHLParameterChunk::changeFrom: caught "
                   "non-SHLParameterChunk!\n"));
        return;
    }

    updateParameters(pEnv->getWindow());

    // SHLParameterChunk didn't change so do nothing.
    if(old == this)
        return;
}


void SHLParameterChunk::deactivate(DrawEnv * /*action*/, UInt32 /*idx*/)
{
}

/*-------------------------- Comparison -----------------------------------*/

Real32 SHLParameterChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SHLParameterChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SHLParameterChunk::operator == (const StateChunk &other) const
{
    SHLParameterChunk const *tother = 
        dynamic_cast<SHLParameterChunk const*>(&other);

    if(!tother)
        return false;

    if(getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool SHLParameterChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}
