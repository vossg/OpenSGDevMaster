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

#define GL_GLEXT_PROTOTYPES

#include <cstdlib>
#include <cstdio>

#include <boost/bind.hpp>

#include "OSGConfig.h"

#include "OSGGL.h"
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGImage.h"

#include "OSGDrawEnv.h"

#include "OSGTextureImageChunk.h"
#include "OSGTextureBaseChunk.h"

#include "OSGGLFuncProtos.h"

//#define OSG_DUMP_TEX


OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureImageChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureImageChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TextureImageChunk::_class("TextureImage", osgMaxTexImages, 30);

UInt32 TextureImageChunk::_arbShaderImageLS      = Window::invalidExtensionID;
UInt32 TextureImageChunk::FuncIdBindImageTexture = Window::invalidFunctionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void TextureImageChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _arbShaderImageLS = 
            Window::registerExtension("GL_ARB_shader_image_load_store");

        FuncIdBindImageTexture =
            Window::registerFunction
            (OSG_DLSYM_UNDERSCORE"glBindImageTexture",
             _arbShaderImageLS);

    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

TextureImageChunk::TextureImageChunk(void) :
    Inherited()
{
}

TextureImageChunk::TextureImageChunk(const TextureImageChunk &source) :
    Inherited(source)
{
}

TextureImageChunk::~TextureImageChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TextureImageChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep
    it consistent with the cubeTexture specifics
*/

void TextureImageChunk::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

bool TextureImageChunk::isTransparent(void) const
{
    // Even if the texture has alpha, the Blending is makes the sorting
    // important, thus textures per se are not transparent
    return false;
}


/*----------------------------- onCreate --------------------------------*/

void TextureImageChunk::onCreate(const TextureImageChunk *source)
{
    Inherited::onCreate(source);
}

void TextureImageChunk::onCreateAspect(const TextureImageChunk *createAspect,
                                       const TextureImageChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

/*------------------------------ Output ----------------------------------*/

void TextureImageChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                             const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TextureImageChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/


void TextureImageChunk::activate(DrawEnv *pEnv, UInt32 idx) 
{    
    if(this->_sfTexture.getValue() == NULL)
        return;

    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbShaderImageLS, 0x0402, 0xFFFF))
    {
        FWARNING(("OpenGL shader image load store is not supported, couldn't "
                  "find extension 'GL_ARB_shader_image_load_store'!\n"));

        return;
    }

    this->_sfTexture.getValue()->validate(pEnv);

    GLint  iTexGLId = this->_sfTexture.getValue()->getOpenGLId(pEnv);
    GLenum eFormat  = this->getFormat();
    
    if(eFormat == GL_NONE)
    {
    }

    OSGGETGLFUNCBYID_GL4(glBindImageTexture,
                         osgGlBindImageTexture,
                         TextureImageChunk::FuncIdBindImageTexture,
                         pWin);

    osgGlBindImageTexture(idx,  
                          iTexGLId,  
                          this->getLevel (),  
                          this->getLayer () != -1 ? GL_FALSE         : GL_TRUE, 
                          this->getLayer () != -1 ? this->getLayer() : 0,  
                          this->getAccess(),  
                          eFormat                                            ); 
}


void TextureImageChunk::changeFrom(DrawEnv    *pEnv,
                                   StateChunk *old   ,
                                   UInt32      idx ) 
{
    if(this->_sfTexture.getValue() == NULL)
        return;

    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbShaderImageLS, 0x0402, 0xFFFF))
    {
        FWARNING(("OpenGL shader image load store is not supported, couldn't "
                  "find extension 'GL_ARB_shader_image_load_store'!\n"));

        return;
    }

    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if(old == this)
        return;

    this->_sfTexture.getValue()->validate(pEnv);

    GLint  iTexGLId = 0;
    GLenum eFormat  = this->getFormat();
    
    if(eFormat == GL_NONE)
    {
    }
    
    OSGGETGLFUNCBYID_GL4(glBindImageTexture,
                         osgGlBindImageTexture,
                         TextureImageChunk::FuncIdBindImageTexture,
                         pWin);

    osgGlBindImageTexture(idx,  
                          iTexGLId,  
                          this->getLevel (),  
                          this->getLayer () != -1 ? GL_FALSE         : GL_TRUE, 
                          this->getLayer () != -1 ? this->getLayer() : 0,  
                          this->getAccess(),  
                          eFormat); 
}

void TextureImageChunk::deactivate(DrawEnv *pEnv, UInt32 idx) 
{
    if(this->_sfTexture.getValue() == NULL)
        return;

    Window *pWin = pEnv->getWindow();

    if(!pWin->hasExtOrVersion(_arbShaderImageLS, 0x0402, 0xFFFF))
    {
        FWARNING(("OpenGL shader image load store is not supported, couldn't "
                  "find extension 'GL_ARB_shader_image_load_store'!\n"));

        return;
    }

    GLenum eFormat = this->getFormat();

    if(eFormat == GL_NONE)
    {
    }
    
    OSGGETGLFUNCBYID_GL4(glBindImageTexture,
                         osgGlBindImageTexture,
                         TextureImageChunk::FuncIdBindImageTexture,
                         pWin);

    osgGlBindImageTexture(idx,  
                          0,  
                          this->getLevel (),  
                          this->getLayer () != -1 ? GL_FALSE         : GL_TRUE, 
                          this->getLayer () != -1 ? this->getLayer() : 0,  
                          this->getAccess(),  
                          eFormat); 
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TextureImageChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureImageChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TextureImageChunk::operator == (const StateChunk &other) const
{
    bool returnValue = false;

    return returnValue;
}

bool TextureImageChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

#if 0
void TextureImageChunk::validate(DrawEnv *pEnv)
{
    if(this->_sfTexture.getValue() == NULL)
        return;

    this->_sfTexture.getValue()->validate(pEnv);
}
#endif
