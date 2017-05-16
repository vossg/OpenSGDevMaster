/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"

#include "OSGGLFuncProtos.h"

#include "OSGDrawEnv.h"

#include "OSGShaderStorageBufferObjBaseChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderStorageBufferObjBaseChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderStorageBufferObjBaseChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderStorageBufferObjBaseChunk::_class("ShaderStorageBuffer", 
                                                        osgMaxShaderStorageBufferBindings, // number if slots
                                                        30);                               // priority

volatile UInt16 ShaderStorageBufferObjBaseChunk::_uiChunkCounter = 1;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderStorageBufferObjBaseChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderStorageBufferObjBaseChunk::ShaderStorageBufferObjBaseChunk(void) :
    Inherited(),
    _uiChunkId(0)
{
}

ShaderStorageBufferObjBaseChunk::ShaderStorageBufferObjBaseChunk(const ShaderStorageBufferObjBaseChunk &source) :
    Inherited(source),
    _uiChunkId(0)
{
}

ShaderStorageBufferObjBaseChunk::~ShaderStorageBufferObjBaseChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *ShaderStorageBufferObjBaseChunk::getClass(void) const
{
    return &_class;
}

void ShaderStorageBufferObjBaseChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*----------------------------- onCreate --------------------------------*/

void ShaderStorageBufferObjBaseChunk::onCreate(const ShaderStorageBufferObjBaseChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void ShaderStorageBufferObjBaseChunk::onCreateAspect(const ShaderStorageBufferObjBaseChunk *createAspect,
                                                     const ShaderStorageBufferObjBaseChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

/*------------------------------ Output ----------------------------------*/

void ShaderStorageBufferObjBaseChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderStorageBufferObjBaseChunk NI" << std::endl;
}

OSG_END_NAMESPACE
