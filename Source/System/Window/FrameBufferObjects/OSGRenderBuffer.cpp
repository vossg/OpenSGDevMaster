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

#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGRenderBuffer.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"

OSG_USING_NAMESPACE

UInt32 RenderBuffer::_uiFramebuffer_object_extension =     
    Window::invalidExtensionID;


UInt32 RenderBuffer::_uiFuncFramebufferRenderbuffer  = 
    Window::invalidFunctionID;

UInt32  RenderBuffer::_uiFuncGenRenderbuffers        =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncDeleteRenderbuffers      =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncBindRenderbuffer         =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncRenderbufferStorage      =
    Window::invalidFunctionID;

typedef void (OSG_APIENTRY *GLFramebufferRenderbufferEXTProcT)(
    GLenum target, 
    GLenum attachment, 
    GLenum renderbuffertarget, 
    GLuint renderbuffer);

typedef void (OSG_APIENTRY *GLGenRenderbuffersEXTProcT)(
    GLsizei  n, 
    GLuint  *renderbuffers);

typedef void (OSG_APIENTRY *GLDeleteRenderbuffersEXTProcT    )(
          GLsizei  n, 
    const GLuint  *renderbuffers);

typedef void (OSG_APIENTRY *GLBindRenderbufferEXTProcT       )(
    GLenum target, 
    GLuint renderbuffer);

typedef void (OSG_APIENTRY *GLRenderbufferStorageEXTProcT    )(
    GLenum target, 
    GLenum internalformat, 
    GLsizei width, 
    GLsizei height);

// Documentation for this class is emited in the
// OSGRenderBufferBase.cpp file.
// To modify it, please change the .fcd file (OSGRenderBuffer.fcd) and
// regenerate the base file.

void RenderBuffer::bind(DrawEnv *pEnv, UInt32 index)
{
    Window *pWindow = pEnv->getWindow();

    GLFramebufferRenderbufferEXTProcT glFramebufferRenderbufferEXTProc =
        (GLFramebufferRenderbufferEXTProcT) pWindow->getFunction(
            _uiFuncFramebufferRenderbuffer);

    pWindow->validateGLObject(getGLId(), pEnv);

    glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                     index,
                                     GL_RENDERBUFFER_EXT, 
                                     pWindow->getGLObjectId(getGLId()));
}

void RenderBuffer::validate(DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    pWindow->validateGLObject(getGLId(), pEnv);
}


/*----------------------- constructors & destructors ----------------------*/

RenderBuffer::RenderBuffer(void) :
    Inherited()
{
}

RenderBuffer::RenderBuffer(const RenderBuffer &source) :
    Inherited(source)
{
}

RenderBuffer::~RenderBuffer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RenderBuffer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

   if(ePhase == TypeObject::SystemPost)
    {
        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiFuncFramebufferRenderbuffer  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glFramebufferRenderbufferEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncGenRenderbuffers      =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glGenRenderbuffersEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncDeleteRenderbuffers      =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDeleteRenderbuffersEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncRenderbufferStorage      =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glRenderbufferStorageEXT", 
                _uiFramebuffer_object_extension);


        _uiFuncBindRenderbuffer         =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBindRenderbufferEXT", 
                _uiFramebuffer_object_extension);
    }
}

void RenderBuffer::onCreate(const RenderBuffer *source)
{
    setGLId(               
        Window::registerGLObject(
            boost::bind(&RenderBuffer::handleGL, this, 
                            _1, _2, _3),
            &RenderBuffer::handleDestroyGL
            ));
}

void RenderBuffer::changed(ConstFieldMaskArg whichField, 
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & (WidthFieldMask | HeightFieldMask)))
    {
        Window::reinitializeGLObject(getGLId());
    }
}

void RenderBuffer::dump(      UInt32    , 
                        const BitVector ) const
{
    SLOG << "Dump RenderBuffer NI" << std::endl;
}

void RenderBuffer::handleGL(DrawEnv                 *pEnv, 
                            UInt32                   osgid, 
                            Window::GLObjectStatusE  mode)
{
    Window *pWindow = pEnv->getWindow();
    
    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        GLuint uiBufferId = 0;

        if(mode == Window::initialize)
        {
            GLGenRenderbuffersEXTProcT glGenRenderbuffersEXTProc =
                (GLGenRenderbuffersEXTProcT) pWindow->getFunction(
                    _uiFuncGenRenderbuffers);

            glGenRenderbuffersEXTProc(1, &uiBufferId);

            pWindow->setGLObjectId(osgid, uiBufferId);
        }
        else
        {
            uiBufferId = pWindow->getGLObjectId(osgid);
        }

        GLBindRenderbufferEXTProcT glBindRenderbufferEXTProc =
            (GLBindRenderbufferEXTProcT) pWindow->getFunction(
                _uiFuncBindRenderbuffer);


        GLRenderbufferStorageEXTProcT glRenderbufferStorageEXTProc =
            (GLRenderbufferStorageEXTProcT) pWindow->getFunction(
                _uiFuncRenderbufferStorage);


        glBindRenderbufferEXTProc(GL_RENDERBUFFER_EXT, uiBufferId);

        glRenderbufferStorageEXTProc(GL_RENDERBUFFER_EXT,
                                     getInternalFormat(), 
                                     getWidth(), 
                                     getHeight());
    }
}
 

void RenderBuffer::handleDestroyGL(DrawEnv                 *pEnv, 
                                   UInt32                   osgid, 
                                   Window::GLObjectStatusE  mode)
{
    Window *pWindow = pEnv->getWindow();
    
    if(mode == Window::destroy)
    {
        GLuint uiBufferId =  pWindow->getGLObjectId(osgid);

        GLDeleteRenderbuffersEXTProcT glDeleteRenderbuffersEXTProc =
            (GLDeleteRenderbuffersEXTProcT) pWindow->getFunction(
                _uiFuncDeleteRenderbuffers);

        glDeleteRenderbuffersEXTProc(1, &uiBufferId);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
}
 
