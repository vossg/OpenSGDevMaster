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

#include "OSGShaderProgramChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderProgramChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderProgramChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShaderProgramChunk::_class("ShaderProgram", 1, 5);
volatile UInt16 ShaderProgramChunk::_uiChunkCounter = 1;

UInt32 ShaderProgramChunk::_extSHL = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgramChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extSHL = Window::registerExtension("GL_ARB_shading_language_100");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderProgramChunk::ShaderProgramChunk(void) :
    Inherited()
{
}

ShaderProgramChunk::ShaderProgramChunk(const ShaderProgramChunk &source) :
    Inherited(source)
{
}

ShaderProgramChunk::~ShaderProgramChunk(void)
{
}

void ShaderProgramChunk::onCreate(const ShaderProgramChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _uiChunkId = _uiChunkCounter++;
}

void ShaderProgramChunk::onCreateAspect(const ShaderProgramChunk *createAspect,
                                        const ShaderProgramChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    _uiChunkId = createAspect->_uiChunkId;
}

void ShaderProgramChunk::onDestroy(UInt32 uiId)
{
    Inherited::onDestroy(uiId);
}

const StateChunkClass *ShaderProgramChunk::getClass(void) const
{
    return &_class;
}

UInt16 ShaderProgramChunk::getChunkId(void)
{
    return _uiChunkId;
}

/*----------------------------- class specific ----------------------------*/

void ShaderProgramChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderProgramChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderProgramChunk NI" << std::endl;
}

void ShaderProgramChunk::addShader(ShaderProgram * const value)
{
    if(value == NULL)
    {
        SWARNING << "ShaderProgramChunk::addShader no shader given"
                 << " ignored" << std::endl;

        return;
    }

    switch(value->getShaderType())
    {
        case GL_VERTEX_SHADER:
            this->addVertexShader(value);
            break;

        case GL_GEOMETRY_SHADER_EXT:
            this->addGeometryShader(value);
            break;

        case GL_FRAGMENT_SHADER:
            this->addFragmentShader(value);
            break;

        default:
            SWARNING << "ShaderProgramChunk::addShader unknow shader type "
                     << value->getShaderType()
                     << " ignored" << std::endl;

            break;
    }
}

void ShaderProgramChunk::activate  (DrawEnv    *pEnv,              
                                    UInt32      uiIdx)
{
    SFATAL << "ShaderProgramChunk::activate" << std::endl;
}

void ShaderProgramChunk::changeFrom(DrawEnv    *pEnv, 
                                    StateChunk *pOld, 
                                    UInt32      uiIdx)
{
    SFATAL << "ShaderProgramChunk::changeFrom" << std::endl;
}

void ShaderProgramChunk::deactivate(DrawEnv    *pEnv,              
                                    UInt32      uiIdx)
{
    SFATAL << "ShaderProgramChunk::deactivate" << std::endl;
}

OSG_END_NAMESPACE
