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

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLEXT.h"
#include "OSGGLFuncProtos.h"

#include "OSGRenderBuffer.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"
#include "OSGGLU.h"

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

// Documentation for this class is emited in the
// OSGRenderBufferBase.cpp file.
// To modify it, please change the .fcd file (OSGRenderBuffer.fcd) and
// regenerate the base file.

void RenderBuffer::bind(DrawEnv *pEnv, UInt32 index)
{
    Window *pWindow = pEnv->getWindow();

    pWindow->validateGLObject(getGLId(), pEnv);

    OSGGETGLFUNC( OSGglFramebufferRenderbufferProc,
                  osgGlFramebufferRenderbufferProc,
                 _uiFuncFramebufferRenderbuffer   );

    osgGlFramebufferRenderbufferProc(GL_FRAMEBUFFER_EXT,
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
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
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
    if(GlobalSystemState == Startup)
        return;

    setGLId(               
        Window::registerGLObject(
            boost::bind(&RenderBuffer::handleGL, 
                        RenderBufferMTUncountedPtr(this), 
                        _1, _2, _3, _4),
            &RenderBuffer::handleDestroyGL));
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

UInt32 RenderBuffer::handleGL(DrawEnv                 *pEnv, 
                              UInt32                   osgid, 
                              Window::GLObjectStatusE  mode,
                              UInt32                        )
{
    Window *pWindow = pEnv->getWindow();
    
    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        GLuint uiBufferId = 0;

        if(mode == Window::initialize)
        {
            OSGGETGLFUNC( OSGglGenRenderbuffersProc,
                          osgGlGenRenderbuffersProc,
                         _uiFuncGenRenderbuffers   );

            osgGlGenRenderbuffersProc(1, &uiBufferId);

            pWindow->setGLObjectId(osgid, uiBufferId);
        }
        else
        {
            uiBufferId = pWindow->getGLObjectId(osgid);
        }

        OSGGETGLFUNC( OSGglBindRenderbufferProc,
                      osgGlBindRenderbufferProc,
                     _uiFuncBindRenderbuffer   );

        OSGGETGLFUNC( OSGglRenderbufferStorageProc,
                      osgGlRenderbufferStorageProc,
                     _uiFuncRenderbufferStorage   );

        osgGlBindRenderbufferProc(GL_RENDERBUFFER_EXT, uiBufferId);

        GLenum internalFormat = getInternalFormat();

        if(internalFormat == GL_NONE && getImage() != NULL)
        {
            internalFormat = getImage()->getPixelFormat();
        }

        osgGlRenderbufferStorageProc(GL_RENDERBUFFER_EXT,
                                     internalFormat,
                                     getWidth(), 
                                     getHeight());
    }

    return 0;
}
 

void RenderBuffer::handleDestroyGL(DrawEnv                 *pEnv, 
                                   UInt32                   osgid, 
                                   Window::GLObjectStatusE  mode)
{
    Window *pWindow = pEnv->getWindow();
    
    if(mode == Window::destroy)
    {
        GLuint uiBufferId =  pWindow->getGLObjectId(osgid);

        OSGGETGLFUNC( OSGglDeleteRenderbuffersProc,
                      osgGlDeleteRenderbuffersProc,
                     _uiFuncDeleteRenderbuffers   );

        osgGlDeleteRenderbuffersProc(1, &uiBufferId);

        pWindow->setGLObjectId(osgid, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
}
 
void RenderBuffer::processPreDeactivate (DrawEnv *pEnv, UInt32 index)
{
    if(_sfReadBack.getValue() == true)
    {
        Image *pImg = this->getImage();
        
        if(pImg == NULL)
            return;
                           
        if(pImg->getData() == NULL)
        {
            SINFO << "TextureBuffer::render: (Re)Allocating image "
                  << "for read-back."
                  << endLog;
            
            pImg->set(pImg->getPixelFormat(),
                      pImg->getWidth      (),
                      pImg->getHeight     (),
                      pImg->getDepth      (),
                      pImg->getMipMapCount(),
                      pImg->getFrameCount (),
                      pImg->getFrameDelay (),
                      NULL,
                      pImg->getDataType   (),
                      true,
                      pImg->getSideCount  () );
        }
       
        // select GL_COLORATTACHMENTn and read data into image
        glReadBuffer(index);
        glReadPixels(0, 0, 
                     pImg->getWidth      (), 
                     pImg->getHeight     (),
                     pImg->getPixelFormat(), 
                     pImg->getDataType   (),
                     pImg->editData      ());

        glReadBuffer(GL_NONE);

        glErr("renderbuffer:predeactivate");
    }
}

void RenderBuffer::processPostDeactivate(DrawEnv *pEnv)
{
}
