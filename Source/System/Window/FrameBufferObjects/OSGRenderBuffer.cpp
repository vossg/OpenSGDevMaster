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
#include "OSGDrawEnv.h"
#include "OSGGLU.h"
#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

UInt32 RenderBuffer::_uiFramebufferObjectArb             =     
    Window::invalidExtensionID;

UInt32 RenderBuffer::_uiFramebufferMultiSampleExt        =
    Window::invalidExtensionID;

UInt32 RenderBuffer::_uiFramebufferMultiSampleCoverageNV =
    Window::invalidExtensionID;


UInt32 RenderBuffer::_uiFuncFramebufferRenderbuffer                = 
    Window::invalidFunctionID;

UInt32  RenderBuffer::_uiFuncGenRenderbuffers                      =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncDeleteRenderbuffers                    =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncBindRenderbuffer                       =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncRenderbufferStorage                    =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncRenderbufferStorageMultiSample         =
    Window::invalidFunctionID;

UInt32 RenderBuffer::_uiFuncRenderbufferStorageMultiSampleCoverage =
    Window::invalidFunctionID;

// Documentation for this class is emited in the
// OSGRenderBufferBase.cpp file.
// To modify it, please change the .fcd file (OSGRenderBuffer.fcd) and
// regenerate the base file.

void RenderBuffer::bind(DrawEnv *pEnv, UInt32 index)
{
    Window *pWindow = pEnv->getWindow();

    pWindow->validateGLObject(getGLId(), pEnv);

    OSGGETGLFUNCBYID_GL3_ES( glFramebufferRenderbuffer,
                             osgGlFramebufferRenderbuffer,
                            _uiFuncFramebufferRenderbuffer,
                             pWindow);

    osgGlFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                 index,
                                 GL_RENDERBUFFER, 
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
        _uiFramebufferObjectArb         = 
            Window::registerExtension("GL_ARB_framebuffer_object");

        _uiFramebufferMultiSampleExt    =
            Window::registerExtension("GL_EXT_framebuffer_multisample");

        _uiFramebufferMultiSampleCoverageNV =
            Window::registerExtension("GL_NV_framebuffer_multisample_coverage");

        _uiFuncFramebufferRenderbuffer  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glFramebufferRenderbuffer", 
                _uiFramebufferObjectArb);

        _uiFuncGenRenderbuffers         =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glGenRenderbuffers", 
                _uiFramebufferObjectArb);

        _uiFuncDeleteRenderbuffers      =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glDeleteRenderbuffers", 
                _uiFramebufferObjectArb);

        _uiFuncRenderbufferStorage      =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glRenderbufferStorage", 
                _uiFramebufferObjectArb);


        _uiFuncBindRenderbuffer         =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBindRenderbuffer", 
                _uiFramebufferObjectArb);


        _uiFuncRenderbufferStorageMultiSample          =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glRenderbufferStorageMultisampleEXT", 
                _uiFramebufferMultiSampleExt);

        _uiFuncRenderbufferStorageMultiSampleCoverage  =
            Window::registerFunction (
              OSG_DLSYM_UNDERSCORE"glRenderbufferStorageMultisampleCoverageNV", 
             _uiFramebufferMultiSampleCoverageNV);
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

void RenderBuffer::resizeBuffers(UInt32 uiWidth, UInt32 uiHeight)
{
    Inherited::resize(uiWidth, uiHeight);

    Window::reinitializeGLObject(getGLId());
}

GLenum RenderBuffer::getBufferFormat(void) const
{
    return _sfInternalFormat.getValue();
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
            OSGGETGLFUNCBYID_GL3_ES( glGenRenderbuffers,
                                     osgGlGenRenderbuffers,
                                    _uiFuncGenRenderbuffers,
                                     pWindow);

            osgGlGenRenderbuffers(1, &uiBufferId);

            pWindow->setGLObjectId(osgid, uiBufferId);
        }
        else
        {
            uiBufferId = pWindow->getGLObjectId(osgid);
        }

        OSGGETGLFUNCBYID_GL3_ES( glBindRenderbuffer,
                                 osgGlBindRenderbuffer,
                                _uiFuncBindRenderbuffer, 
                                 pWindow);

        OSGGETGLFUNCBYID_GL3_ES( glRenderbufferStorage,
                                 osgGlRenderbufferStorage,
                                _uiFuncRenderbufferStorage,
                                 pWindow);

        osgGlBindRenderbuffer(GL_RENDERBUFFER, uiBufferId);

        GLenum internalFormat = getInternalFormat();

        if(internalFormat == GL_NONE && getImage() != NULL)
        {
            internalFormat = getImage()->getPixelFormat();
        }

        
        if(pWindow->hasExtension(_uiFramebufferMultiSampleCoverageNV) == true &&

           (_sfColorSamples   .getValue() != 0 ||
            _sfCoverageSamples.getValue() != 0  )                         )
        {
            OSGGETGLFUNCBYID_EXT(
                 glRenderbufferStorageMultisampleCoverage,
                 osgGlRenderbufferStorageMultisampleCoverage,
                _uiFuncRenderbufferStorageMultiSampleCoverage,
                 pWindow);

            osgGlRenderbufferStorageMultisampleCoverage(
                GL_RENDERBUFFER,
                _sfCoverageSamples.getValue(),
                _sfColorSamples   .getValue(),
                internalFormat,
                getWidth(), 
                getHeight());
        }
        else if(pWindow->hasExtOrVersion(
                    _uiFramebufferMultiSampleExt, 
                     0x0300                     ) == true &&

           (_sfColorSamples   .getValue() != 0)            )
        {
            OSGGETGLFUNCBYID_GL3( glRenderbufferStorageMultisample,
                                  osgGlRenderbufferStorageMultisample,
                                 _uiFuncRenderbufferStorageMultiSample,
                                  pWindow                             );

            osgGlRenderbufferStorageMultisample(
                 GL_RENDERBUFFER,
                _sfColorSamples.getValue(),
                 internalFormat,
                 getWidth(), 
                 getHeight()              );
        }
        else
        {
            osgGlRenderbufferStorage(GL_RENDERBUFFER,
                                     internalFormat,
                                     getWidth(), 
                                     getHeight());
        }
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

        OSGGETGLFUNCBYID_GL3_ES( glDeleteRenderbuffers,
                                 osgGlDeleteRenderbuffers,
                                _uiFuncDeleteRenderbuffers,
                                 pWindow);

        osgGlDeleteRenderbuffers(1, &uiBufferId);

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
#ifndef OSG_OGL_ES2
        glReadBuffer(index);
#endif
        glReadPixels(0, 0, 
                     pImg->getWidth      (), 
                     pImg->getHeight     (),
                     pImg->getPixelFormat(), 
                     pImg->getDataType   (),
                     pImg->editData      ());

#ifndef OSG_OGL_ES2
        glReadBuffer(GL_NONE);
#endif

        glErr("renderbuffer:predeactivate");
    }
}

void RenderBuffer::processPostDeactivate(DrawEnv *pEnv)
{
}

OSG_END_NAMESPACE
