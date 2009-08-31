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

#include <boost/bind.hpp>

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGWindow.h"

#include "OSGVertexProgramChunk.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGVertexProgramChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGVertexProgramChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass VertexProgramChunk::_class("VertexProgram");

UInt32 VertexProgramChunk::_arbVertexProgram = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VertexProgramChunk::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _arbVertexProgram = Window::registerExtension("GL_ARB_vertex_program");
    }
 }


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VertexProgramChunk::VertexProgramChunk(void) :
    Inherited()
{
}

VertexProgramChunk::VertexProgramChunk(const VertexProgramChunk &source) :
    Inherited(source)
{
}

VertexProgramChunk::~VertexProgramChunk(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void VertexProgramChunk::onCreate(const VertexProgramChunk *chunk)
{
    Inherited::onCreate(chunk); 

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                    boost::bind(&VertexProgramChunk::handleGL, 
                                VertexProgramChunkMTUncountedPtr(this), 
                                _1, _2, _3, _4),
                    &VertexProgramChunk::handleDestroyGL));
}

void VertexProgramChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *VertexProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void VertexProgramChunk::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VertexProgramChunk::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "Dump VertexProgramChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

UInt32 VertexProgramChunk::getExtension(void) const
{
    return _arbVertexProgram;
}

GLenum VertexProgramChunk::getTarget(void) const
{
    return GL_VERTEX_PROGRAM_ARB;
}

const char *VertexProgramChunk::getTargetName(void) const
{
    return "Vertex Program";
}


UInt32 VertexProgramChunk::handleGL(DrawEnv                 *pEnv, 
                                    UInt32                   osgid, 
                                    Window::GLObjectStatusE  mode,
                                    UInt32                   uiOptions)
{
    Inherited::handleGL(pEnv, 
                        osgid,
                        mode, 
                        GL_VERTEX_PROGRAM_ARB, 
                        _arbVertexProgram);

    return 0;
}

void VertexProgramChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                         UInt32                   osgid, 
                                         Window::GLObjectStatusE  mode)
{
    Inherited::handleDestroyGL(pEnv, 
                        osgid,
                        mode, 
                        GL_VERTEX_PROGRAM_ARB, 
                        _arbVertexProgram);
}
