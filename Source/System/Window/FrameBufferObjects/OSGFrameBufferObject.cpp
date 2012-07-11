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
    OSGGETGLFUNC_GL3_ES( glCheckFramebufferStatus,                     \
                         osgGlCheckFramebufferStatus,                  \
                        _uiFuncCheckFramebufferStatus    );            \
                                                                       \
    status = osgGlCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);          \
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
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:                \
            FWARNING(("Incomplete Multisample\n"));                    \
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
#include "OSGRenderBuffer.h"

OSG_BEGIN_NAMESPACE

UInt32 FrameBufferObject::_uiFramebufferObjectExt  = 
    Window::invalidExtensionID;

UInt32 FrameBufferObject::_uiFramebufferBlitExt  = 
    Window::invalidExtensionID;

UInt32 FrameBufferObject::_uiPackedDepthStencilExt =
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

UInt32 FrameBufferObject::_uiFuncBlitFramebuffer          =
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

    editMField(ColorAttachmentsFieldMask, _mfColorAttachments);

    if(uiSlot >= _mfColorAttachments.size())
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

void FrameBufferObject::resizeAll(UInt32 uiWidth, UInt32 uiHeight)
{
    // main buffer

    MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
        _mfColorAttachments.begin();
    MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
        _mfColorAttachments.end  ();
    
    for(; attIt != attEnd; ++attIt)
    {
        if(*attIt == NULL)
            continue;
        
        (*attIt)->resizeBuffers(uiWidth, uiHeight);
    }

    if(_sfDepthAttachment.getValue() != NULL)
    {
        _sfDepthAttachment.getValue()->resizeBuffers(uiWidth, uiHeight);
    }

    if(_sfStencilAttachment.getValue() != NULL)
    {
        _sfStencilAttachment.getValue()->resizeBuffers(uiWidth, uiHeight);
    }


    // multi-sample buffer

    attIt  = _mfMsaaColorAttachments.begin();
    attEnd = _mfMsaaColorAttachments.end  ();
    
    for(; attIt != attEnd; ++attIt)
    {
        if(*attIt == NULL)
            continue;
        
        (*attIt)->resizeBuffers(uiWidth, uiHeight);
    }

    if(_sfMsaaDepthAttachment.getValue() != NULL)
    {
        _sfMsaaDepthAttachment.getValue()->resizeBuffers(uiWidth, uiHeight);
    }

    if(_sfMsaaStencilAttachment.getValue() != NULL)
    {
        _sfMsaaStencilAttachment.getValue()->resizeBuffers(uiWidth, uiHeight);
    }


    this->setSize(uiWidth, uiHeight);

    Window::refreshGLObject(getGLId());
    Window::refreshGLObject(getMultiSampleGLId());
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
        _uiFramebufferObjectExt   = 
            Window::registerExtension("GL_EXT_framebuffer_object");
        _uiFramebufferBlitExt   = 
            Window::registerExtension("GL_EXT_framebuffer_blit");
        _uiPackedDepthStencilExt  =
            Window::registerExtension("GL_EXT_packed_depth_stencil");

        _uiFuncGenFramebuffers =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glGenFramebuffersEXT",
                _uiFramebufferObjectExt);

        _uiFuncCheckFramebufferStatus   = 
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glCheckFramebufferStatusEXT", 
                _uiFramebufferObjectExt);
        
        _uiFuncBindFramebuffer          = 
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBindFramebufferEXT", 
                _uiFramebufferObjectExt);

        _uiFuncDeleteFramebuffers       = 
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glDeleteFramebuffersEXT", 
                _uiFramebufferObjectExt);

        _uiFuncFramebufferRenderbuffer  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glFramebufferRenderbufferEXT", 
                _uiFramebufferObjectExt);

        _uiFuncDrawBuffers  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glDrawBuffersARB", 
                _uiFramebufferObjectExt);

        _uiFuncBlitFramebuffer  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBlitFramebufferEXT", 
                _uiFramebufferBlitExt);
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

    setMultiSampleGLId(               
        Window::registerGLObject(
            boost::bind(&FrameBufferObject::handleMultiSampleGL, 
                        FrameBufferObjectMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &FrameBufferObject::handleDestroyGL));
}

void FrameBufferObject::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);    

    if(getMultiSampleGLId() > 0)
        Window::destroyGLObject(getMultiSampleGLId(), 1);    

    Inherited::onDestroy(uiContainerId);
}

void FrameBufferObject::changed(ConstFieldMaskArg whichField, 
                                UInt32            origin,
                                BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & (WidthFieldMask | HeightFieldMask)))
    {
        // main buffer

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


        // multi-sample buffer

        attIt  = _mfMsaaColorAttachments.begin();
        attEnd = _mfMsaaColorAttachments.end  ();
   
        for(; attIt != attEnd; ++attIt)
        {
            if(*attIt == NULL)
                continue;
        
            (*attIt)->resize(getWidth(), getHeight());
        }

        if(_sfMsaaDepthAttachment.getValue() != NULL)
        {
            _sfMsaaDepthAttachment.getValue()->resize(getWidth (),
                                                      getHeight());
        }

        if(_sfMsaaStencilAttachment.getValue() != NULL)
        {
            _sfMsaaStencilAttachment.getValue()->resize(getWidth (),
                                                        getHeight());
        }

        Window::refreshGLObject(getMultiSampleGLId());
    }

    if(0x0000 != (whichField & DepthAttachmentFieldMask))
    {
        if(_sfDepthAttachment.getValue() != NULL)
        {
            _sfDepthAttachment.getValue()->resize(getWidth (),
                                                  getHeight());

            if(_sfMsaaDepthAttachment.getValue() != NULL)
            {
                _sfMsaaDepthAttachment.getValue()->resize(getWidth (),
                                                          getHeight());
            }
            else if(_sfEnableMultiSample.getValue() == true)
            {
                FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                    this->createMultiSampleBufferFrom(
                        _sfDepthAttachment.getValue());

                this->setMsaaDepthAttachment(pMsaaBuffer);
            }
        }
        else
        {
            this->setMsaaDepthAttachment(NULL);
        }

        Window::reinitializeGLObject(getGLId           ());
        Window::reinitializeGLObject(getMultiSampleGLId());
    }

    if(0x0000 != (whichField & StencilAttachmentFieldMask))
    {
        if(_sfStencilAttachment.getValue() != NULL)
        {
            _sfStencilAttachment.getValue()->resize(getWidth (),
                                                    getHeight());

            if(_sfMsaaStencilAttachment.getValue() != NULL)
            {
                _sfMsaaStencilAttachment.getValue()->resize(getWidth (),
                                                            getHeight());
            }
            else if(_sfEnableMultiSample.getValue() == true)
            {
                FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                    this->createMultiSampleBufferFrom(
                        _sfStencilAttachment.getValue());

                this->setMsaaStencilAttachment(pMsaaBuffer);
            }
        }
        else
        {
            this->setMsaaStencilAttachment(NULL);
        }

        Window::reinitializeGLObject(getGLId           ());
        Window::reinitializeGLObject(getMultiSampleGLId());
    }

    if(0x0000 != (whichField & ColorAttachmentsFieldMask))
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();
   
        if(_mfMsaaColorAttachments.size() != _mfColorAttachments.size())
        {
            editMField(MsaaColorAttachmentsFieldMask, _mfMsaaColorAttachments);

            _mfMsaaColorAttachments.resize(_mfColorAttachments.size(),
                                            NULL                     );
        }

        MFUnrecFrameBufferAttachmentPtr::iterator msaaAttIt  =
            _mfMsaaColorAttachments.begin_nc();

        for(; attIt != attEnd; ++attIt, ++msaaAttIt)
        {
            if(*attIt == NULL)
            {
                if(*msaaAttIt != NULL)
                {
                    editMField( MsaaColorAttachmentsFieldMask, 
                               _mfMsaaColorAttachments);

                    _mfMsaaColorAttachments.replace(msaaAttIt, NULL);
                }

                continue;
            }

            (*attIt)->resize(getWidth(), getHeight());

            if(*msaaAttIt != NULL)
            {
                (*msaaAttIt)->resize(getWidth(), getHeight());
            }
            else if(_sfEnableMultiSample.getValue() == true)
            {
                FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                    this->createMultiSampleBufferFrom(*attIt);

                editMField( MsaaColorAttachmentsFieldMask, 
                           _mfMsaaColorAttachments);

                _mfMsaaColorAttachments.replace(msaaAttIt, pMsaaBuffer);
            }
        }

        Window::reinitializeGLObject(getGLId           ());
        Window::reinitializeGLObject(getMultiSampleGLId());
    }

    if(0x0000 != (whichField & EnableMultiSampleFieldMask))
    {
        if(_sfDepthAttachment    .getValue() != NULL &&
           _sfMsaaDepthAttachment.getValue() == NULL)
        {
            FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                this->createMultiSampleBufferFrom(
                    _sfDepthAttachment.getValue());

            this->setMsaaDepthAttachment(pMsaaBuffer);
        }

        if(_sfStencilAttachment    .getValue() != NULL &&
           _sfMsaaStencilAttachment.getValue() == NULL)
        {
            FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                this->createMultiSampleBufferFrom(
                    _sfStencilAttachment.getValue());

            this->setMsaaStencilAttachment(pMsaaBuffer);
        }

        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  =
            _mfColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd =
            _mfColorAttachments.end  ();
   
        if(_mfMsaaColorAttachments.size() != _mfColorAttachments.size())
        {
            editMField(MsaaColorAttachmentsFieldMask, _mfMsaaColorAttachments);

            _mfMsaaColorAttachments.resize(_mfColorAttachments.size(),
                                            NULL                     );
        }

        MFUnrecFrameBufferAttachmentPtr::iterator msaaAttIt  =
            _mfMsaaColorAttachments.begin_nc();

        for(; attIt != attEnd; ++attIt, ++msaaAttIt)
        {
            if(*attIt == NULL)
                continue;

            if(*msaaAttIt == NULL)
            {
                FrameBufferAttachmentUnrecPtr pMsaaBuffer = 
                    this->createMultiSampleBufferFrom(*attIt);

                editMField( MsaaColorAttachmentsFieldMask, 
                           _mfMsaaColorAttachments);

                _mfMsaaColorAttachments.replace(msaaAttIt, pMsaaBuffer);
            }
        }

        Window::reinitializeGLObject(getMultiSampleGLId());
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

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

//    FLOG(("FBO Activate %p\n", this));

    UInt32 glId = getGLId();

    win->validateGLObject(getGLId(),            pEnv);

    if(_sfEnableMultiSample.getValue()                      == true &&
        win->hasExtOrVersion(_uiFramebufferBlitExt, 0x0300) == true   )
    {
        win->validateGLObject(getMultiSampleGLId(), pEnv);

        glId = getMultiSampleGLId();

        glEnable(GL_MULTISAMPLE);
    }

    OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                             osgGlBindFramebuffer,
                            _uiFuncBindFramebuffer,
                             win);

    osgGlBindFramebuffer(GL_FRAMEBUFFER_EXT, 
                         win->getGLObjectId(glId));

    glErr("FrameBufferObject::activate::bind");
    
    glErr("FrameBufferObject::activate");

#ifndef OSG_OGL_ES2
    if(eDrawBuffer == GL_NONE)
    {
        if(_mfDrawBuffers.size() != 0)
        {
            OSGGETGLFUNCBYID_GL3( glDrawBuffers,
                                  osgGlDrawBuffers,
                                 _uiFuncDrawBuffers,
                                  win);
            
            osgGlDrawBuffers(GLsizei(_mfDrawBuffers.size()), 
                             &(_mfDrawBuffers[0]) );
        }
        else
        {
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
        }
    }
    else
    {
        OSGGETGLFUNCBYID_GL3( glDrawBuffers,
                              osgGlDrawBuffers,
                             _uiFuncDrawBuffers,
                              win);
        
        osgGlDrawBuffers(1, &eDrawBuffer );
    }
#endif

    CHECK_FRAMEBUFFER_STATUS();
}

void FrameBufferObject::deactivate (DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    if(win->hasExtOrVersion(_uiFramebufferObjectExt, 0x0300, 0x0200) == false)
    {
        FNOTICE(("Framebuffer objects not supported on Window %p!\n", win));
        return;        
    }

//    FLOG(("FBO DeActivate %p\n", this));

    OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                             osgGlBindFramebuffer,
                            _uiFuncBindFramebuffer,
                             win                  );

    if(_sfEnableMultiSample.getValue()                      == true &&
        win->hasExtOrVersion(_uiFramebufferBlitExt, 0x0300) == true   )
    {
        OSGGETGLFUNCBYID_GL3( glBlitFramebuffer,
                              osgGlBlitFramebuffer,
                             _uiFuncBlitFramebuffer,
                              win                  );

//        GLbitfield bufferMask = GL_COLOR_BUFFER_BIT;
        glDisable(GL_MULTISAMPLE);

        osgGlBindFramebuffer(GL_READ_FRAMEBUFFER, 
                             win->getGLObjectId(getMultiSampleGLId()));
        osgGlBindFramebuffer(GL_DRAW_FRAMEBUFFER, 
                             win->getGLObjectId(getGLId           ()));

        osgGlBlitFramebuffer(0, 0, getWidth(), getHeight(),
                              0, 0, getWidth(), getHeight(),
                             (GL_COLOR_BUFFER_BIT  |
                              GL_DEPTH_BUFFER_BIT  |
                              GL_STENCIL_BUFFER_BIT), 
                              GL_NEAREST);

        osgGlBindFramebuffer(GL_FRAMEBUFFER, win->getGLObjectId(getGLId()));
    }

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

    osgGlBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
    
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
            OSGGETGLFUNCBYID_GL3_ES( glGenFramebuffers,
                                     osgGlGenFramebuffers,
                                    _uiFuncGenFramebuffers,
                                     win);

            osgGlGenFramebuffers(1, &uiFBOId);

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
        OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                                 osgGlBindFramebuffer,
                                _uiFuncBindFramebuffer,
                                 win);

        OSGGETGLFUNCBYID_GL3_ES( glFramebufferRenderbuffer,
                                 osgGlFramebufferRenderbuffer,
                                _uiFuncFramebufferRenderbuffer,
                                 win);

        osgGlBindFramebuffer(GL_FRAMEBUFFER_EXT, uiFBOId);

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
                osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
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
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
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
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
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
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
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

        if(win->hasExtOrVersion(_uiFramebufferObjectExt, 
                                0x0300, 
                                0x0200                 ) != false)
        {
            OSGGETGLFUNCBYID_GL3_ES( glDeleteFramebuffers,
                                     osgGlDeleteFramebuffers,
                                    _uiFuncDeleteFramebuffers,
                                     win);

            osgGlDeleteFramebuffers(1, &uiFBOId);
        }
    }
}

UInt32 FrameBufferObject::handleMultiSampleGL(
    DrawEnv                 *pEnv, 
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
            OSGGETGLFUNCBYID_GL3_ES( glGenFramebuffers,
                                     osgGlGenFramebuffers,
                                    _uiFuncGenFramebuffers,
                                     win);

            osgGlGenFramebuffers(1, &uiFBOId);

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
        OSGGETGLFUNCBYID_GL3_ES( glBindFramebuffer,
                                 osgGlBindFramebuffer,
                                _uiFuncBindFramebuffer,
                                 win);

        OSGGETGLFUNCBYID_GL3_ES( glFramebufferRenderbuffer,
                                 osgGlFramebufferRenderbuffer,
                                _uiFuncFramebufferRenderbuffer,
                                 win);

        osgGlBindFramebuffer(GL_FRAMEBUFFER_EXT, uiFBOId);

        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  = 
            _mfMsaaColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd = 
            _mfMsaaColorAttachments.end  ();

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
                osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
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
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
                                         index,
                                         GL_RENDERBUFFER_EXT,
                                         0);
            
            glErr("FrameBufferObject::coloroff");

            ++index;
        }

        if(_sfMsaaDepthAttachment.getValue() != NULL)
        {
            _sfMsaaDepthAttachment.getValue()->bind(pEnv, 
                                                    GL_DEPTH_ATTACHMENT_EXT);
        }
        else
        {
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
                                         GL_DEPTH_ATTACHMENT_EXT,
                                         GL_RENDERBUFFER_EXT,
                                         0);
        }

        glErr("FrameBufferObject::depth");
        
        if(_sfMsaaStencilAttachment.getValue() != NULL)
        {
            _sfMsaaStencilAttachment.getValue()->bind(
                pEnv, 
                GL_STENCIL_ATTACHMENT_EXT);
        }
        else
        {
            osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT,
                                         GL_STENCIL_ATTACHMENT_EXT,
                                         GL_RENDERBUFFER_EXT,
                                         0);
        }

        glErr("FrameBufferObject::stencil");
    }
    else if(mode == Window::needrefresh)
    {
        MFUnrecFrameBufferAttachmentPtr::const_iterator attIt  = 
            _mfMsaaColorAttachments.begin();
        MFUnrecFrameBufferAttachmentPtr::const_iterator attEnd = 
            _mfMsaaColorAttachments.end  ();

        while(attIt != attEnd)
        {
            if(*attIt != NULL)
            {
                (*attIt)->validate(pEnv);
            }

            glErr("FrameBufferObject::refresh");

            ++attIt;
        }

        if(_sfMsaaDepthAttachment.getValue() != NULL)
        {
            _sfMsaaDepthAttachment.getValue()->validate(pEnv);
        }

        if(_sfMsaaStencilAttachment.getValue() != NULL)
        {
            _sfMsaaStencilAttachment.getValue()->validate(pEnv);
        }
    }

    return 0;
}


FrameBufferAttachmentTransitPtr 
    FrameBufferObject::createMultiSampleBufferFrom(FrameBufferAttachment *pSrc)
{
    RenderBufferUnrecPtr returnValue = NULL;

    if(pSrc == NULL)
        return FrameBufferAttachmentTransitPtr(returnValue);

  
    returnValue = RenderBuffer::create();

    returnValue->setInternalFormat(pSrc->getBufferFormat());
    
    returnValue->setWidth (pSrc->getWidth ());
    returnValue->setHeight(pSrc->getHeight());

    returnValue->setColorSamples       (this->getColorSamples       ());
    returnValue->setCoverageSamples    (this->getCoverageSamples    ());
    returnValue->setFixedSampleLocation(this->getFixedSampleLocation());

    return FrameBufferAttachmentTransitPtr(returnValue);
}

OSG_END_NAMESPACE

