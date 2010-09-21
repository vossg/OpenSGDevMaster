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
    OSGGETGLFUNC( OSGglCheckFramebufferStatusProc,                     \
                  osgGlCheckFramebufferStatusProc,                     \
                 _uiFuncCheckFramebufferStatus    );                   \
                                                                       \
    status = osgGlCheckFramebufferStatusProc(GL_FRAMEBUFFER_EXT);      \
                                                                       \
                                                                       \
    switch(status)                                                     \
    {                                                                  \
        case GL_FRAMEBUFFER_COMPLETE_EXT:                              \
            break;                                                     \
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:                           \
            FWARNING(("Unsupported Framebuffer\n"));                   \
            /* choose different formats */                             \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:                 \
            FWARNING(("Incomplete Attachment\n"));                     \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:         \
            FWARNING(("Incomplete Missing Attachment\n"));             \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:                 \
            FWARNING(("Incomplete Dimensions\n"));                     \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:                    \
            FWARNING(("Incomplete Formats\n"));                        \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:                \
            FWARNING(("Incomplete Draw Buffer\n"));                    \
            break;                                                     \
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:                \
            FWARNING(("Incomplete Read Buffer\n"));                    \
            break;                                                     \
		default:                                                       \
			FWARNING(("Unknown error %x\n", status));                  \
			break;                                                     \
    }                                                                  \
}


#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLEXT.h"
#include "OSGGLU.h"
#include "OSGGLFuncProtos.h"

#include "OSGWindow.h"

#include "OSGFrameBufferObject.h"
#include "OSGDrawEnv.h"
#include "OSGFrameBufferAttachment.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"

OSG_USING_NAMESPACE

UInt32 FrameBufferObject::_uiFramebuffer_object_extension = 
    Window::invalidExtensionID;

UInt32 FrameBufferObject::_uiPackedDepthStencilExtension  =
    Window::invalidExtensionID;

UInt32 FrameBufferObject::_uiFuncGenFramebuffers          = 
    Window::invalidFunctionID;

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

// Documentation for this class is emited in the
// OSGFrameBufferObjectBase.cpp file.
// To modify it, please change the .fcd file (OSGFrameBufferObject.fcd) and
// regenerate the base file.

void FrameBufferObject::setColorAttachment(
    FrameBufferAttachment *pAttachment,
    UInt32                 uiSlot     )
{
    if(uiSlot >= GL_COLOR_ATTACHMENT0_EXT)
    {
        uiSlot -= GL_COLOR_ATTACHMENT0_EXT;
    }

    if(uiSlot <= _mfColorAttachments.size())
    {
        _mfColorAttachments.resize(uiSlot + 1, NULL);
    }

    _mfColorAttachments.replace(uiSlot, pAttachment);
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
        _uiPackedDepthStencilExtension  =
            Window::registerExtension("GL_EXT_packed_depth_stencil");

        _uiFuncGenFramebuffers =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glGenFramebuffersEXT",
                _uiFramebuffer_object_extension);

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
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&FrameBufferObject::handleGL, 
                        FrameBufferObjectMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &FrameBufferObject::handleDestroyGL));
}

void FrameBufferObject::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);    

    Inherited::onDestroy(uiContainerId);
}

void FrameBufferObject::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & (WidthFieldMask | HeightFieldMask)))
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();
   
        for(; attIt != attEnd; ++attIt)
        {
            if(*attIt == NULL)
                continue;
        
            (*attIt)->resize(getWidth(), getHeight());
        }

        if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment.getValue()->resize(getWidth (),
                                                  getHeight());
        }

        if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->resize(getWidth (),
                                                    getHeight());
        }

        Window::refreshGLObject(getGLId());
    }

    if(0x0000 != (whichField & DepthAttachmentFieldMask))
    {
        if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment.getValue()->resize(getWidth (),
                                                  getHeight());
        }

        Window::reinitializeGLObject(getGLId());
    }

    if(0x0000 != (whichField & StencilAttachmentFieldMask))
    {
        if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->resize(getWidth (),
                                                    getHeight());
        }

        Window::reinitializeGLObject(getGLId());
    }

    if(0x0000 != (whichField & ColorAttachmentsFieldMask))
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();
   
        for(; attIt != attEnd; ++attIt)
        {
            if(*attIt == NULL)
                continue;
        
            (*attIt)->resize(getWidth(), getHeight());
        }

        Window::reinitializeGLObject(getGLId());
    }
}

void FrameBufferObject::dump(      UInt32    , 
                             const BitVector ) const
{
    SLOG << "Dump FrameBufferObject NI" << std::endl;
}

void FrameBufferObject::activate(DrawEnv *pEnv,
                                 GLenum   eDrawBuffer)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtension(_uiFramebuffer_object_extension) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

//    FLOG(("FBO Activate %p\n", this));

    win->validateGLObject(getGLId(), pEnv);

    OSGGETGLFUNC( OSGglBindFramebufferProc,
                  osgGlBindFramebufferProc,
                 _uiFuncBindFramebuffer   );

    osgGlBindFramebufferProc(GL_FRAMEBUFFER_EXT, 
                             win->getGLObjectId(getGLId()));

    glErr("FrameBufferObject::activate::bind");

    glErr("FrameBufferObject::activate");

    if(eDrawBuffer == GL_NONE)
    {
        if(_mfDrawBuffers.size() != 0)
        {
            OSGGETGLFUNC( OSGglDrawBuffersProc,
                          osgGlDrawBuffersProc,
                         _uiFuncDrawBuffers);

            osgGlDrawBuffersProc(_mfDrawBuffers.size(), &(_mfDrawBuffers[0]) );
        }
        else
        {
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
        }
    }
    else
    {
        OSGGETGLFUNC( OSGglDrawBuffersProc,
                      osgGlDrawBuffersProc,
                     _uiFuncDrawBuffers);
        
        osgGlDrawBuffersProc(1, &eDrawBuffer );
    }

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

    OSGGETGLFUNC( OSGglBindFramebufferProc,
                  osgGlBindFramebufferProc,
                 _uiFuncBindFramebuffer   );

    if(_sfPostProcessOnDeactivate.getValue() == true)
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();

        UInt32 index = GL_COLOR_ATTACHMENT0_EXT;
    
        for(; attIt != attEnd; ++attIt, ++index)
        {
            if(*attIt == NULL)
                continue;
        
            (*attIt)->processPreDeactivate(pEnv, index);
        }

        if(_sfDepthAttachment  .getValue() != NULL &&
           _sfStencilAttachment.getValue() != NULL   )
        {
            if(_sfDepthAttachment.getValue() == _sfStencilAttachment.getValue())
            {
                _sfDepthAttachment.getValue()->processPreDeactivate(
                    pEnv, GL_NONE);
            }
            else
            {
                _sfDepthAttachment  .getValue()->processPreDeactivate(
                    pEnv, GL_NONE);
                _sfStencilAttachment.getValue()->processPreDeactivate(
                    pEnv, GL_NONE);
            }
        }
        else if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment  .getValue()->processPreDeactivate(
                pEnv, GL_NONE);
        }
        else if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->processPreDeactivate(
                pEnv, GL_NONE);
        }
    }

    osgGlBindFramebufferProc(GL_FRAMEBUFFER_EXT, 0);
    
    if(_sfPostProcessOnDeactivate.getValue() == true)
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();
    
        for(; attIt != attEnd; ++attIt)
        {
            if(*attIt == NULL)
                continue;
        
            (*attIt)->processPostDeactivate(pEnv);
        }
    }
}

UInt32 FrameBufferObject::handleGL(DrawEnv                 *pEnv, 
                                   UInt32                   osgid, 
                                   Window::GLObjectStatusE  mode,
                                   UInt32                        ) const
{
    Window *win     = pEnv->getWindow();
    GLuint  uiFBOId = 0;

    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        if(mode == Window::initialize)
        {
            OSGGETGLFUNC( OSGglGenFramebuffersProc,
                          osgGlGenFramebuffersProc,
                         _uiFuncGenFramebuffers   );

            osgGlGenFramebuffersProc(1, &uiFBOId);

            win->setGLObjectId(osgid, uiFBOId);
        }
        else
        {
            // already has an GLid
            uiFBOId = win->getGLObjectId(osgid);
        }
    }

    
    if(mode == Window::initialize || mode == Window::reinitialize)
    {
        OSGGETGLFUNC( OSGglBindFramebufferProc,
                      osgGlBindFramebufferProc,
                     _uiFuncBindFramebuffer   );

        OSGGETGLFUNC( OSGglFramebufferRenderbufferProc,
                      osgGlFramebufferRenderbufferProc,
                     _uiFuncFramebufferRenderbuffer   );

        osgGlBindFramebufferProc(GL_FRAMEBUFFER_EXT, uiFBOId);

        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  = 
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd = 
            _mfColorAttachments.end  ();

        GLint iMaxColorAttachments;

        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &iMaxColorAttachments);

        Int32 index = GL_COLOR_ATTACHMENT0_EXT;
        
        iMaxColorAttachments += GL_COLOR_ATTACHMENT0_EXT;

        while(attIt != attEnd && index < iMaxColorAttachments)
        {
            if(*attIt != NULL)
            {
                (*attIt)->bind(pEnv, index);
            }
            else
            {
                osgGlFramebufferRenderbufferProc(GL_FRAMEBUFFER_EXT,
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
            osgGlFramebufferRenderbufferProc(GL_FRAMEBUFFER_EXT,
                                             index,
                                             GL_RENDERBUFFER_EXT,
                                             0);
            
            glErr("FrameBufferObject::coloroff");

            ++index;
        }

        if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment.getValue()->bind(pEnv, 
                                                GL_DEPTH_ATTACHMENT_EXT);
        }
        else
        {
            osgGlFramebufferRenderbufferProc(GL_FRAMEBUFFER_EXT,
                                             GL_DEPTH_ATTACHMENT_EXT,
                                             GL_RENDERBUFFER_EXT,
                                             0);
        }

        glErr("FrameBufferObject::depth");
        
        if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->bind(pEnv, 
                                                  GL_STENCIL_ATTACHMENT_EXT);
        }
        else
        {
            osgGlFramebufferRenderbufferProc(GL_FRAMEBUFFER_EXT,
                                             GL_STENCIL_ATTACHMENT_EXT,
                                             GL_RENDERBUFFER_EXT,
                                             0);
        }

        glErr("FrameBufferObject::stencil");
    }
    else if(mode == Window::needrefresh)
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  = 
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd = 
            _mfColorAttachments.end  ();

        while(attIt != attEnd)
        {
            if(*attIt != NULL)
            {
                (*attIt)->validate(pEnv);
            }

            glErr("FrameBufferObject::refresh");

            ++attIt;
        }

        if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment.getValue()->validate(pEnv);
        }

        if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->validate(pEnv);
        }
    }

    return 0;
}

void FrameBufferObject::handleDestroyGL(DrawEnv                 *pEnv, 
                                        UInt32                   osgid, 
                                        Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();

    if(mode == Window::destroy)
    {
        GLuint uiFBOId = win->getGLObjectId(osgid);

        if(win->hasExtension(_uiFramebuffer_object_extension) != false)
        {
            OSGGETGLFUNC( OSGglDeleteFramebuffersProc,
                          osgGlDeleteFramebuffersProc,
                         _uiFuncDeleteFramebuffers   );

            osgGlDeleteFramebuffersProc(1, &uiFBOId);
        }
    }
}
