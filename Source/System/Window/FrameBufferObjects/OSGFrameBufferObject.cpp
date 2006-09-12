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

#define CHECK_FRAMEBUFFER_STATUS()                                     \
{                                                                      \
    GLenum status;                                                     \
                                                                       \
    GLCheckFramebufferStatusEXTProcT glCheckFramebufferStatusEXTProc = \
        (GLCheckFramebufferStatusEXTProcT) win->getFunction(           \
                _uiFuncCheckFramebufferStatus);                        \
                                                                       \
    status = glCheckFramebufferStatusEXTProc(GL_FRAMEBUFFER_EXT);      \
                                                                  \
    switch(status)                                                \
    {                                                             \
        case GL_FRAMEBUFFER_COMPLETE_EXT:                         \
            break;                                                \
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:                      \
            FWARNING(("Unsupported Framebuffer\n"));              \
            /* choose different formats */                        \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT: \
            FWARNING(("Incomplete Attachment\n"));              \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT: \
            FWARNING(("Incomplete Missing Attachment\n"));              \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT: \
            FWARNING(("Incomplete Dimensions\n"));              \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT: \
            FWARNING(("Incomplete Formats\n"));              \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT: \
            FWARNING(("Incomplete Draw Buffer\n"));              \
            break;                                                \
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT: \
            FWARNING(("Incomplete Read Buffer\n"));              \
            break;                                                \
		default: \
			FWARNING(("Unknown error %x\n", status)); \
			break; \
     }                                                            \
}


#include <stdlib.h>
#include <stdio.h>
#include <boost/bind.hpp>

#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLEXT.h>
#include <OSGGLU.h>

#include "OSGWindow.h"

#include "OSGFrameBufferObject.h"
#include "OSGDrawEnv.h"
#include "OSGFrameBufferAttachment.h"

OSG_USING_NAMESPACE

UInt32 FrameBufferObject::_uiFramebuffer_object_extension = 
    Window::invalidExtensionID;


UInt32 FrameBufferObject::_uiFuncCheckFramebufferStatus   = 
    Window::invalidFunctionID;

UInt32 FrameBufferObject::_uiFuncBindFramebuffer          = 
    Window::invalidFunctionID;

UInt32 FrameBufferObject::_uiFuncDeleteFramebuffers       = 
    Window::invalidFunctionID;

UInt32 FrameBufferObject::_uiFuncFramebufferRenderbuffer  = 
    Window::invalidFunctionID;

UInt32 FrameBufferObject::_uiFuncDrawBuffers              =
    Window::invalidFunctionID;

typedef void   (OSG_APIENTRY *GLBindFramebufferEXTProcT)(GLenum target, 
                                                         GLuint framebuffer);

typedef GLenum (OSG_APIENTRY *GLCheckFramebufferStatusEXTProcT)(GLenum target);

typedef void   (OSG_APIENTRY *GLDeleteFramebuffersEXTProcT)(
          GLsizei  n, 
    const GLuint  *framebuffers);

typedef void   (OSG_APIENTRY *GLFramebufferRenderbufferEXTProcT)(
    GLenum target, 
    GLenum attachment, 
    GLenum renderbuffertarget, 
    GLuint renderbuffer);

typedef void   (OSG_APIENTRY *GLDrawBuffersEXTProcT)(
          GLsizei  n, 
    const GLenum  *buffers);

/*! \class OSG::FrameBufferObject
    \ingroup GrpSystemWindowViewports
 */


void FrameBufferObject::setColorAttachment(
    FrameBufferAttachmentPtr pAttachment,
    UInt32                   uiSlot            )
{
    if(uiSlot >= GL_COLOR_ATTACHMENT0_EXT)
    {
        uiSlot -= GL_COLOR_ATTACHMENT0_EXT;
    }

    if(uiSlot <= _mfColorAttachments.size())
    {
        _mfColorAttachments.resize(uiSlot + 1, NullFC);
    }

    setRefd(_mfColorAttachments[uiSlot], pAttachment);
}

void FrameBufferObject::setSize(UInt32 uiWidth, UInt32 uiHeight)
{
    setWidth (uiWidth );
    setHeight(uiHeight);
}

/*----------------------- constructors & destructors ----------------------*/

FrameBufferObject::FrameBufferObject(void) :
    Inherited()
{
}

FrameBufferObject::FrameBufferObject(const FrameBufferObject &source) :
    Inherited(source)
{
}

FrameBufferObject::~FrameBufferObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FrameBufferObject::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");
                    
        _uiFuncCheckFramebufferStatus   = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glCheckFramebufferStatusEXT", 
                _uiFramebuffer_object_extension);
        
        _uiFuncBindFramebuffer          = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glBindFramebufferEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncDeleteFramebuffers       = 
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDeleteFramebuffersEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncFramebufferRenderbuffer  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glFramebufferRenderbufferEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebuffer_object_extension);
    }

}

void FrameBufferObject::onCreate(const FrameBufferObject *source)
{
    FrameBufferObjectPtr tmpPtr = 
        Inherited::constructPtr<FrameBufferObject>(this);

    setGLId(
        Window::registerGLObject(
            boost::bind(&FrameBufferObject::handleGL, tmpPtr, _1, _2),
            1));
}

void FrameBufferObject::changed(ConstFieldMaskArg whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(0x0000 != (whichField & (WidthFieldMask | HeightFieldMask)))
    {
        if(_sfDepthAttachment.getValue() != NullFC)
        {
            _sfDepthAttachment.getValue()->resize(getWidth (),
                                                  getHeight());
        }
    }

    if(0x0000 != (whichField & DepthAttachmentFieldMask))
    {
        if(_sfDepthAttachment.getValue() != NullFC)
        {
            _sfDepthAttachment.getValue()->resize(getWidth (),
                                                  getHeight());
        }

        Window::refreshGLObject(getGLId());
    }

    if(0x0000 != (whichField & ColorAttachmentsFieldMask))
    {
        Window::refreshGLObject(getGLId());
    }
}

void FrameBufferObject::dump(      UInt32    , 
                             const BitVector ) const
{
    SLOG << "Dump FrameBufferObject NI" << std::endl;
}

void FrameBufferObject::activate(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_uiFramebuffer_object_extension) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

//    FLOG(("FBO Activate %p\n", this));

    GLBindFramebufferEXTProcT glBindFramebufferEXTProc =
        (GLBindFramebufferEXTProcT) win->getFunction(_uiFuncBindFramebuffer);

    glBindFramebufferEXTProc(GL_FRAMEBUFFER_EXT, getGLId());

    if(_mfDrawBuffers.size() != 0)
    {
        GLDrawBuffersEXTProcT glDrawBuffersEXTProc =
            (GLDrawBuffersEXTProcT) win->getFunction(_uiFuncDrawBuffers);

        glDrawBuffersEXTProc(_mfDrawBuffers.size(), &(_mfDrawBuffers[0]) );
    }
    else
    {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    glErr("FrameBufferObject::activate::bind");

    win->validateGLObject(getGLId(), pEnv);

    glErr("FrameBufferObject::activate");

    CHECK_FRAMEBUFFER_STATUS();
}

void FrameBufferObject::deactivate (DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_uiFramebuffer_object_extension) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

//    FLOG(("FBO DeActivate %p\n", this));

    GLBindFramebufferEXTProcT glBindFramebufferEXTProc =
        (GLBindFramebufferEXTProcT) win->getFunction(_uiFuncBindFramebuffer);

    glBindFramebufferEXTProc(GL_FRAMEBUFFER_EXT, 0);
}

void FrameBufferObject::handleGL(DrawEnv *pEnv, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    Window *win = pEnv->getWindow();

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {
        GLuint uiFBO = id;

        if(win->hasExtension(_uiFramebuffer_object_extension) == false)
        {
            GLDeleteFramebuffersEXTProcT glDeleteFramebuffersEXTProc =
                (GLDeleteFramebuffersEXTProcT) win->getFunction(
                    _uiFuncDeleteFramebuffers);
            
            glDeleteFramebuffersEXTProc(1, &uiFBO);
        }
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh )
    {
        GLFramebufferRenderbufferEXTProcT glFramebufferRenderbufferEXTProc =
            (GLFramebufferRenderbufferEXTProcT) win->getFunction(
                _uiFuncFramebufferRenderbuffer);

        MFFrameBufferAttachmentPtr::iterator attIt  = 
            _mfColorAttachments.begin();
        MFFrameBufferAttachmentPtr::iterator attEnd = 
            _mfColorAttachments.end  ();

        GLint iMaxColorAttachments;

        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &iMaxColorAttachments);

        fprintf(stderr, "Max attach %d\n", iMaxColorAttachments);

        UInt32 index = GL_COLOR_ATTACHMENT0_EXT;
        
        iMaxColorAttachments += GL_COLOR_ATTACHMENT0_EXT;

        while(attIt != attEnd && index < iMaxColorAttachments)
        {
            if(*attIt != NullFC)
            {
                (*attIt)->bind(pEnv, index);
            }
            else
            {
                glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                                 index,
                                                 GL_RENDERBUFFER_EXT,
                                                 0);
            }

            glErr("FrameBufferObject::color");

            ++attIt;
            ++index;
        }

        while(index < iMaxColorAttachments)
        {
            glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                             index,
                                             GL_RENDERBUFFER_EXT,
                                             0);
            fprintf(stderr, "%x\n", index);

            glErr("FrameBufferObject::coloroff");

            ++index;
        }

        if(_sfDepthAttachment.getValue() != NullFC)
        {
            _sfDepthAttachment.getValue()->bind(pEnv, 
                                                GL_DEPTH_ATTACHMENT_EXT);
        }
        else
        {
            glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                             GL_DEPTH_ATTACHMENT_EXT,
                                             GL_RENDERBUFFER_EXT,
                                             0);
        }

        glErr("FrameBufferObject::depth");
        
        if(_sfStencilAttachment.getValue() != NullFC)
        {
            _sfStencilAttachment.getValue()->bind(pEnv, 
                                                  GL_STENCIL_ATTACHMENT_EXT);
        }
        else
        {
            glFramebufferRenderbufferEXTProc(GL_FRAMEBUFFER_EXT,
                                             GL_STENCIL_ATTACHMENT_EXT,
                                             GL_RENDERBUFFER_EXT,
                                             0);
        }

        glErr("FrameBufferObject::stencil");
    }

    fprintf(stderr, "FBO handleGL %p, %p, %d\n", 
            this,
            win,
            id);
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
    static Char8 cvsid_hpp       [] = OSGFRAMEBUFFEROBJECTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFRAMEBUFFEROBJECTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFRAMEBUFFEROBJECTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

