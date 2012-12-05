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

#include "OSGConfig.h"
#include "OSGGL.h"
#include "OSGGLEXT.h"
#include "OSGGLFuncProtos.h"

#include "OSGTextureBuffer.h"
#include "OSGWindow.h"
#include "OSGDrawEnv.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

UInt32 TextureBuffer::_uiFramebuffer_object_extension = 
    Window::invalidExtensionID;

UInt32 TextureBuffer::_uiFuncFramebufferTexture1D =  Window::invalidFunctionID;
UInt32 TextureBuffer::_uiFuncFramebufferTexture2D =  Window::invalidFunctionID;
UInt32 TextureBuffer::_uiFuncFramebufferTexture3D =  Window::invalidFunctionID;
UInt32 TextureBuffer::_uiFuncGenerateMipmap       =  Window::invalidFunctionID;

// Documentation for this class is emited in the
// OSGTextureBufferBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureBuffer.fcd) and
// regenerate the base file.

void TextureBuffer::bind(DrawEnv *pEnv, UInt32 index)
{
    Window *pWindow = pEnv->getWindow();

    if(_sfTexture.getValue() != NULL)
    {
        pWindow->validateGLObject(_sfTexture.getValue()->getGLId(), pEnv);

        GLenum target;

        if(getTexTarget() != GL_NONE)
        {
            target = getTexTarget();
        }
        else
        {
            target = _sfTexture.getValue()->determineTextureTarget(pWindow);
        }
            
        switch(target)
        {
#ifndef OSG_OGL_ES2
            case GL_TEXTURE_1D:
            {
                OSGGETGLFUNCBYID_GL3( glFramebufferTexture1D,
                                      osgGlFramebufferTexture1D,
                                     _uiFuncFramebufferTexture1D,
                                      pWindow);

                osgGlFramebufferTexture1D(
                    GL_FRAMEBUFFER_EXT, 
                    index,
                    target,
                    pWindow->getGLObjectId(_sfTexture.getValue()->getGLId()),
                    getLevel());
             }
            break;
#endif
                
            case GL_TEXTURE_2D:
            case GL_TEXTURE_RECTANGLE_ARB:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
            {
                OSGGETGLFUNCBYID_GL3_ES( glFramebufferTexture2D,
                                         osgGlFramebufferTexture2D,
                                        _uiFuncFramebufferTexture2D,
                                         pWindow);

                osgGlFramebufferTexture2D(
                    GL_FRAMEBUFFER_EXT, 
                    index,
                    target,
                    pWindow->getGLObjectId(_sfTexture.getValue()->getGLId()),
                    getLevel());
            }
            break;
                
            case GL_TEXTURE_3D:
            {
                OSGGETGLFUNCBYID_GL3( glFramebufferTexture3D,
                                      osgGlFramebufferTexture3D,
                                     _uiFuncFramebufferTexture3D,
                                      pWindow);

                osgGlFramebufferTexture3D(
                    GL_FRAMEBUFFER_EXT, 
                    index,
                    target,
                    pWindow->getGLObjectId(_sfTexture.getValue()->getGLId()),
                    getLevel(),
                    getZoffset());
            }
            break;
        }
    }
}

void TextureBuffer::validate(DrawEnv *pEnv)
{
    Window *pWindow = pEnv->getWindow();

    if(_sfTexture.getValue() != NULL)
    {
        pWindow->validateGLObject(_sfTexture.getValue()->getGLId(), pEnv);
    }
}

void TextureBuffer::resizeBuffers(UInt32 uiWidth, UInt32 uiHeight)
{
    TextureObjChunk *pTex = this->getTexture();

    if(pTex == NULL)
        return;

    Image *pImg = pTex->getImage();

    if(pImg == NULL)
        return;

    pImg->set(pImg->getPixelFormat(), //Image::OSG_RGB_PF, 
              uiWidth, 
              uiHeight,
              pImg->getDepth      (),
              pImg->getMipMapCount(),
              pImg->getFrameCount (),
              pImg->getFrameDelay (),
              NULL,
              pImg->getDataType   (), //Image::OSG_UINT8_IMAGEDATA,
              false,
              pImg->getSideCount  ());
}

GLenum TextureBuffer::getBufferFormat(void) const
{
    TextureObjChunk *pTex = this->getTexture();

    if(pTex == NULL)
        return GL_NONE;

    if(pTex->getInternalFormat() != GL_NONE)
        return pTex->getInternalFormat();

    Image *pImg = pTex->getImage();

    if(pImg == NULL)
        return GL_NONE;

    return pImg->getPixelFormat();
}


void TextureBuffer::processPreDeactivate(DrawEnv *pEnv, UInt32 index)
{
    if(_sfReadBack.getValue() == true)
    {
        TextureObjChunk *pTexObj = this->getTexture();
        
        if(pTexObj == NULL)
            return;
        
        Image *pTexImg = pTexObj->getImage();
                    
        if(pTexImg->getData() == NULL)
        {
            SINFO << "TextureBuffer::render: (Re)Allocating image "
                  << "for read-back."
                  << endLog;
            
            pTexImg->set(pTexImg->getPixelFormat(),
                         pTexImg->getWidth      (),
                         pTexImg->getHeight     (),
                         pTexImg->getDepth      (),
                         pTexImg->getMipMapCount(),
                         pTexImg->getFrameCount (),
                         pTexImg->getFrameDelay (),
                         NULL,
                         pTexImg->getDataType   (),
                         true,
                         pTexImg->getSideCount  () );
        }

        UInt32  mipMapLevel = _sfLevel.getValue();
        UInt32  frame       = 0;
        UInt32  side        = 0;
        GLenum  target;
        Window *pWindow = pEnv->getWindow();

        if(_sfTexTarget.getValue() != GL_NONE)
        {
            target = _sfTexTarget.getValue();
        }
        else
        {
            target = _sfTexture.getValue()->determineTextureTarget(pWindow);
        }

        switch(target)
        {
            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                side = 0;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                side = 1;
                break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                side = 2;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                side = 3;
                break;
            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                side = 4;
                break;
            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                side = 5;
                break;
        }

        // select GL_COLORATTACHMENTn and read data into image
#ifndef OSG_OGL_ES2
        glReadBuffer(index);
#endif
        glReadPixels(0, 0, 
                     pTexImg->getWidth      (),
                     pTexImg->getHeight     (),
                     pTexImg->getPixelFormat(),
                     pTexImg->getDataType   (),
                     pTexImg->editData      (mipMapLevel, frame, side));
        
#ifndef OSG_OGL_ES2
        glReadBuffer(GL_NONE);
#endif
    }
}

void TextureBuffer::processPostDeactivate(DrawEnv *pEnv)
{
    Window *win = pEnv->getWindow();

    // If there are TextureBuffers with mipmap filters attached,
    // the mipmaps need to be regenerated
    TextureObjChunk *pTexObj = this->getTexture();
        
    if(pTexObj == NULL)
        return;
        
    GLenum target = pTexObj->determineTextureTarget(win);
    
    if(target                   == GL_TEXTURE_2D                 &&
       (pTexObj->getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
        pTexObj->getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
        pTexObj->getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
        pTexObj->getMinFilter() == GL_LINEAR_MIPMAP_LINEAR     )   )
    {
        OSGGETGLFUNCBYID_GL3_ES( glGenerateMipmap,
                                 osgGlGenerateMipmap,
                                _uiFuncGenerateMipmap,
                                 win);

        glBindTexture(target, win->getGLObjectId(pTexObj->getGLId()));

        osgGlGenerateMipmap(target);
    }
}

/*----------------------- constructors & destructors ----------------------*/

TextureBuffer::TextureBuffer(void) :
    Inherited()
{
}

TextureBuffer::TextureBuffer(const TextureBuffer &source) :
    Inherited(source)
{
}

TextureBuffer::~TextureBuffer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureBuffer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _uiFramebuffer_object_extension = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _uiFuncFramebufferTexture1D =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glFramebufferTexture1DEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncFramebufferTexture2D =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glFramebufferTexture2DEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncFramebufferTexture3D =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glFramebufferTexture3DEXT", 
                _uiFramebuffer_object_extension);

        _uiFuncGenerateMipmap =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glGenerateMipmapEXT",
                _uiFramebuffer_object_extension);
    }

}

void TextureBuffer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextureBuffer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextureBuffer NI" << std::endl;
}

OSG_END_NAMESPACE
