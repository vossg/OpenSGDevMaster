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

#include <stdlib.h>
#include <stdio.h>
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

/*! \class OSG::RenderBuffer
    \ingroup GrpSystemWindowViewports

*/

void RenderBuffer::bind(DrawEnv *pEnv, UInt32 index)
{
    Window *pWindow = pEnv->getWindow();

    GLFramebufferRenderbufferEXTProcT glFramebufferRenderbufferEXTProc =
        (GLFramebufferRenderbufferEXTProcT) pWindow->getFunction(
            _uiFuncFramebufferRenderbuffer);

    fprintf(stderr, "RenderBuffer Activate %p\n", this);

    pWindow->validateGLObject(getGLId(), pEnv);

    glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                     index,
                                     GL_RENDERBUFFER_EXT, 
                                     getGLId()          );
}

/*
void RenderBuffer::deactivate(DrawActionBase *action, UInt32 index)
{
    fprintf(stderr, "RenderBuffer DeActivate %p\n", this);
}
*/

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
    RenderBufferPtr tmpPtr = Inherited::constructPtr<RenderBuffer>(this);

    setGLId(
        Window::registerGLObject(
            boost::bind(&RenderBuffer::handleGL, tmpPtr, _1, _2),
            1));
}

void RenderBuffer::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

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

void RenderBuffer::handleGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;

    UInt32  id;
    Window *pWindow = pEnv->getWindow();
    
    fprintf(stderr, "RenderBuffer handleGL %p, %p, %d\n", 
            this,
            pWindow,
            id);

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {
        GLuint tex = id;

        GLDeleteRenderbuffersEXTProcT glDeleteRenderbuffersEXTProc =
            (GLDeleteRenderbuffersEXTProcT) pWindow->getFunction(
                _uiFuncDeleteRenderbuffers);

        glDeleteRenderbuffersEXTProc(1, &tex);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh )
    {
        GLBindRenderbufferEXTProcT glBindRenderbufferEXTProc =
            (GLBindRenderbufferEXTProcT) pWindow->getFunction(
                _uiFuncBindRenderbuffer);


        GLRenderbufferStorageEXTProcT glRenderbufferStorageEXTProc =
            (GLRenderbufferStorageEXTProcT) pWindow->getFunction(
                _uiFuncRenderbufferStorage);


        glBindRenderbufferEXTProc(GL_RENDERBUFFER_EXT, id);

        glRenderbufferStorageEXTProc(GL_RENDERBUFFER_EXT,
                                     getInternalFormat(), 
                                     getWidth(), 
                                     getHeight());
    }
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
    static Char8 cvsid_hpp       [] = OSGRENDERBUFFERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGRENDERBUFFERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGRENDERBUFFERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

