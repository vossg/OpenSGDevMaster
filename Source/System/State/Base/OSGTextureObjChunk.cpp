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
#include "OSGGLU.h"
#include "OSGGLEXT.h"
#include "OSGGLFuncProtos.h"
#include "OSGImage.h"

#include "OSGDrawEnv.h"

#include "OSGTextureObjChunk.h"

//#define OSG_DUMP_TEX

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureObjChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureObjChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

typedef OSG::Window Win;

UInt32 TextureObjChunk::_extTex3D                    = Win::invalidExtensionID;
UInt32 TextureObjChunk::_arbCubeTex                  = Win::invalidExtensionID;
UInt32 TextureObjChunk::_sgisGenerateMipmap          = Win::invalidExtensionID;
UInt32 TextureObjChunk::_arbTextureCompression       = Win::invalidExtensionID;
UInt32 TextureObjChunk::_arbTextureRectangle         = Win::invalidExtensionID;
UInt32 TextureObjChunk::_arbTextureNonPowerOfTwo     = Win::invalidExtensionID;
UInt32 TextureObjChunk::_extTextureFilterAnisotropic = Win::invalidExtensionID;
UInt32 TextureObjChunk::_extShadow                   = Win::invalidExtensionID;
UInt32 TextureObjChunk::_extDepthTexture             = Win::invalidExtensionID;

UInt32 TextureObjChunk::_funcTexImage3D              = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcTexSubImage3D           = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexImage1D    = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexSubImage1D = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexImage2D    = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexSubImage2D = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexImage3D    = Win::invalidFunctionID;
UInt32 TextureObjChunk::_funcCompressedTexSubImage3D = Win::invalidFunctionID;

// define GL_TEXTURE_3D, if not defined yet
#ifndef GL_VERSION_1_2
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3DEXT"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3DEXT"
#else
#  define GL_FUNC_TEXIMAGE3D    OSG_DLSYM_UNDERSCORE"glTexImage3D"
#  define GL_FUNC_TEXSUBIMAGE3D OSG_DLSYM_UNDERSCORE"glTexSubImage3D"
#endif


StatElemDesc<StatIntOnceElem> TextureObjChunk::statNTextures(
    "NTextures",
    "number of texture changes");

StatElemDesc<StatIntOnceElem> TextureObjChunk::statNTexBytes(
    "NTexBytes",
    "sum of all used textures' sizes (approx., in bytes)");


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void TextureObjChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extTex3D          =
            Window::registerExtension("GL_EXT_texture3D"       );
        _arbCubeTex        =
            Window::registerExtension("GL_ARB_texture_cube_map");
        _sgisGenerateMipmap  =
            Window::registerExtension("GL_SGIS_generate_mipmap"  );
        _arbTextureCompression  =
            Window::registerExtension("GL_ARB_texture_compression"  );
        _arbTextureRectangle  =
            Window::registerExtension("GL_ARB_texture_rectangle"    );
        _arbTextureNonPowerOfTwo  =
            Window::registerExtension("GL_ARB_texture_non_power_of_two" );
        _extTextureFilterAnisotropic =
            Window::registerExtension("GL_EXT_texture_filter_anisotropic" );

        _extShadow =
            Window::registerExtension("GL_ARB_shadow"  );
        _extDepthTexture =
            Window::registerExtension("GL_ARB_depth_texture"  );

        _funcTexImage3D    =
            Window::registerFunction (GL_FUNC_TEXIMAGE3D,
                                      _extTex3D,
                                      0x0102 );
        _funcTexSubImage3D =
            Window::registerFunction (GL_FUNC_TEXSUBIMAGE3D,
                                      _extTex3D,
                                      0x0102);

        _funcCompressedTexImage1D    = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexImage1DARB"             ,
            _arbTextureCompression);

        _funcCompressedTexSubImage1D = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexSubImage1DARB"          ,
            _arbTextureCompression);

        _funcCompressedTexImage2D    = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexImage2DARB"             ,
            _arbTextureCompression);

        _funcCompressedTexSubImage2D = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexSubImage2DARB"          ,
            _arbTextureCompression);

        _funcCompressedTexImage3D    = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexImage3DARB"             ,
            _arbTextureCompression);

        _funcCompressedTexSubImage3D = Window::registerFunction(
            OSG_DLSYM_UNDERSCORE"glCompressedTexSubImage3DARB"          ,
            _arbTextureCompression);

        Window::registerConstant(GL_MAX_TEXTURE_UNITS_ARB      );
        Window::registerConstant(GL_MAX_TEXTURE_IMAGE_UNITS_ARB);
        Window::registerConstant(GL_MAX_TEXTURE_COORDS_ARB     );
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

TextureObjChunk::TextureObjChunk(void) :
    Inherited()
{
}

TextureObjChunk::TextureObjChunk(const TextureObjChunk &source) :
    Inherited(source)
{
}

TextureObjChunk::~TextureObjChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

bool TextureObjChunk::isCubeTexture(void)
{
    return 
        this->getImage()                 != NULL && 
        this->getImage()->getSideCount() == 6;
}

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep
    it consistent with the cubeTexture specifics
*/

void TextureObjChunk::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         details)
{
    GLenum id = _sfGLId.getValue();

    // Only filter changed? Mipmaps need reinit.
    if((whichField & ~(MinFilterFieldMask | MagFilterFieldMask)) == 0)
    {
        if((getMinFilter() != GL_NEAREST) &&
           (getMinFilter() != GL_LINEAR))
        {
            Window::reinitializeGLObject(id);
        }
        else
        {
            imageContentChanged();
        }
    } // Only priority changed? Refresh is fine.
    else if((whichField & ~PriorityFieldMask || FrameFieldMask) == 0)
    {
        imageContentChanged();
    } // Only dirty rectangle changed? Refresh is fine.
    else if ((whichField & ~(DirtyMinXFieldMask | DirtyMaxXFieldMask |
                             DirtyMinYFieldMask | DirtyMaxYFieldMask |
                             DirtyMinZFieldMask | DirtyMaxZFieldMask)) == 0)
    {
        Window::refreshGLObject(id);
    }
    else
    {
        if(origin  == ChangedOrigin::Child       && 
           0x0000 != (whichField & ImageFieldMask))
        {
            if((details & ~(Image::PixelFieldMask)) == 0)
            {
                Window::refreshGLObject(id);
            }
            else
            {
                if(0x0000 != (whichField & (Image::WidthFieldMask  |
                                            Image::HeightFieldMask |
                                            Image::DepthFieldMask)))
                {
                    Window::reinitializeGLObject(id);
                }
            }
        }
        else
        {
            Window::reinitializeGLObject(id);
        }
    }

    Inherited::changed(whichField, origin, details);
}

bool TextureObjChunk::isTransparent(void) const
{
    // Even if the texture has alpha, the Blending makes the sorting
    // important, thus textures per se are not transparent
    return false;
}


/*----------------------------- onCreate --------------------------------*/

void TextureObjChunk::onCreate(const TextureObjChunk *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    setGLId(Window::registerGLObject(
                boost::bind(&TextureObjChunk::handleGL, 
                            TextureObjChunkMTUncountedPtr(this), 
                            _1, _2, _3, _4),
                &TextureObjChunk::handleDestroyGL));
}

void TextureObjChunk::onCreateAspect(const TextureObjChunk *createAspect,
                                     const TextureObjChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void TextureObjChunk::onDestroy(UInt32 uiContainerId)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    Inherited::onDestroy(uiContainerId);
}

/*------------------------------ Output ----------------------------------*/

void TextureObjChunk::dump(      UInt32    uiIndent,
                           const BitVector bvFlags  ) const
{
    Inherited::dump(uiIndent, bvFlags);

    if((bvFlags & ImageFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "image " << _sfImage.getValue() << "\n";
    }

    if((bvFlags & InternalFormatFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "internalFormat "
             << GLDefineMapper::the()->toString(_sfInternalFormat.getValue())
             << "\n";
    }

    if((bvFlags & ExternalFormatFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "externalFormat "
             << GLDefineMapper::the()->toString(_sfExternalFormat.getValue())
             << "\n";
    }

    if((bvFlags & ScaleFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "scale " << _sfScale.getValue() << "\n";
    }

    if((bvFlags & FrameFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "frame " << _sfFrame.getValue() << "\n";
    }

    if((bvFlags & MinFilterFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "minFilter "
             << GLDefineMapper::the()->toString(_sfMinFilter.getValue())
             << "\n";
    }

    if((bvFlags & MagFilterFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "magFilter "
             << GLDefineMapper::the()->toString(_sfMagFilter.getValue())
             << "\n";
    }

    if((bvFlags & WrapSFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warpS "
             << GLDefineMapper::the()->toString(_sfWrapS.getValue())
             << "\n";
    }

    if((bvFlags & WrapTFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warpT "
             << GLDefineMapper::the()->toString(_sfWrapT.getValue())
             << "\n";
    }

    if((bvFlags & WrapRFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "warpR "
             << GLDefineMapper::the()->toString(_sfWrapR.getValue())
             << "\n";
    }

    if((bvFlags & AnisotropyFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "anisotropy " << _sfAnisotropy.getValue() << "\n";
    }

    if((bvFlags & BorderColorFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "borderColor " << _sfBorderColor.getValue() << "\n";
    }

    if((bvFlags & CompareModeFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "compareMode "
             << GLDefineMapper::the()->toString(_sfCompareMode.getValue())
             << "\n";
    }

    if((bvFlags & CompareFuncFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "compareFunc "
             << GLDefineMapper::the()->toString(_sfCompareFunc.getValue())
             << "\n";
    }

    if((bvFlags & DepthModeFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "depthMode "
             << GLDefineMapper::the()->toString(_sfDepthMode.getValue())
             << "\n";
    }

    if((bvFlags & BorderWidthFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "borderWidth " << _sfBorderWidth.getValue() << "\n";
    }

    if((bvFlags & SkipMipMapLevelsFieldMask) != 0)
    {
        indentLog(uiIndent, PLOG);
        PLOG << "skipMipMapLevels " << _sfSkipMipMapLevels.getValue() << "\n";
    }
}



void TextureObjChunk::handleTexture(Window                  *win,
                                    UInt32                   id,
                                    GLenum                   bindtarget,
                                    GLenum                   paramtarget,
                                    GLenum                   imgtarget,
                                    Window::GLObjectStatusE  mode,
                                    Image                   *img,
                                    Int32                    side)
{
    if( img==NULL || ! img->getDimension()) // no image ?
        return;

    // Early out if we don't have any image data, probably because we cleared on upload.
    // NOTE: We need to be absolutely sure that no changes happen to the texture object
    //       after the first initialization.
    if (img->getClearOnLoad() && img->getMFPixel()->empty())
    {
        return;
    }

    if(mode == Window::initialize || mode == Window::reinitialize)
    {
        if( bindtarget                   == GL_TEXTURE_3D && 
           !win->hasExtension(_extTex3D)                  &&
            win->getGLVersion()          <   0x0102        )
        {
            FWARNING(("3D textures not supported on Window %p!\n", win));
            return;
        }

        if(imgtarget == GL_TEXTURE_RECTANGLE_ARB &&
           !win->hasExtension(_arbTextureRectangle))
        {
            FWARNING(("Rectangular textures not supported on Window %p!\n",
                      win));
            return;
        }

        if(paramtarget == GL_TEXTURE_CUBE_MAP_ARB &&
           !win->hasExtension(_arbCubeTex))
        {
            FNOTICE(("Cube textures not supported on Window %p!\n", win));
            return;
        }

        if(img->hasCompressedData() &&
           !win->hasExtension(_arbTextureCompression))
        {
            FWARNING(("Compressed textures not supported on Window %p!\n",
                      win));
            return;
        }

#if 0 // ????? GV
        if(mode == Window::reinitialize)
        {
            GLuint tex = id;
            glDeleteTextures(1, &tex);
        }
#endif

        // 3D texture functions
        OSGGETGLFUNCBYID(OSGglTexImage3D,    TexImage3D,
                         _funcTexImage3D,    win);
        OSGGETGLFUNCBYID(OSGglTexSubImage3D, TexSubImage3D,
                         _funcTexSubImage3D, win);

        // Compressed texture functions
        OSGGETGLFUNCBYID(OSGglCompressedTexImage1D,    CompressedTexImage1D,
                         _funcCompressedTexImage1D,    win);
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage1D, CompressedTexSubImage1D,
                         _funcCompressedTexSubImage1D, win);
        OSGGETGLFUNCBYID(OSGglCompressedTexImage2D,    CompressedTexImage2D,
                         _funcCompressedTexImage2D,    win);
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage2D, CompressedTexSubImage2D,
                         _funcCompressedTexSubImage2D, win);
        OSGGETGLFUNCBYID(OSGglCompressedTexImage3D,    CompressedTexImage3D,
                         _funcCompressedTexImage3D,    win);
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage3D, CompressedTexSubImage3D,
                         _funcCompressedTexSubImage3D, win);

        // as we're not allocating anything here, the same code can be used
        // for reinitialization

        glErr("TextureObjChunk::initialize precheck");

        FDEBUG(("texture (re-)initialize\n"));

        glBindTexture(bindtarget, id);

        if(paramtarget != GL_NONE)
        {
            // set the parameters
            glTexParameterf(paramtarget, GL_TEXTURE_PRIORITY,   getPriority());
            glTexParameteri(paramtarget, GL_TEXTURE_MIN_FILTER, getMinFilter());
            glTexParameteri(paramtarget, GL_TEXTURE_MAG_FILTER, getMagFilter());
            glTexParameteri(paramtarget, GL_TEXTURE_WRAP_S, getWrapS());

            if(paramtarget == GL_TEXTURE_2D           ||
               paramtarget == GL_TEXTURE_3D           ||
               paramtarget == GL_TEXTURE_CUBE_MAP_ARB ||
               paramtarget == GL_TEXTURE_RECTANGLE_ARB )
            {
                glTexParameteri(paramtarget, GL_TEXTURE_WRAP_T, getWrapT());
            }

            if(paramtarget == GL_TEXTURE_3D ||
               paramtarget == GL_TEXTURE_CUBE_MAP_ARB)
            {
                glTexParameteri(paramtarget, GL_TEXTURE_WRAP_R, getWrapR());
            }

             if(getAnisotropy() > 1.0f &&
                win->hasExtension(_extTextureFilterAnisotropic))
             {
                glTexParameterf(paramtarget,
                                GL_TEXTURE_MAX_ANISOTROPY_EXT,
                                getAnisotropy());
             }

             glTexParameterfv(paramtarget,
                              GL_TEXTURE_BORDER_COLOR,
                              const_cast<GLfloat *>(
                                  getBorderColor().getValuesRGBA()));

             if(getCompareMode() != GL_NONE &&
                win->hasExtension(_extShadow))
             {
                 glTexParameteri(paramtarget,
                                 GL_TEXTURE_COMPARE_MODE,
                                 getCompareMode());
                 glTexParameteri(paramtarget,
                                 GL_TEXTURE_COMPARE_FUNC,
                                 getCompareFunc());
             }

             if(getDepthMode() != GL_LUMINANCE &&
                win->hasExtension(_extDepthTexture))
             {
                 glTexParameteri(paramtarget,
                                 GL_DEPTH_TEXTURE_MODE,
                                 getDepthMode());
             }

            glErr("TextureObjChunk::initialize params");
        }

        // set the image
        GLenum internalFormat = GL_NONE;
        GLenum externalFormat = GL_NONE;
        GLenum type           = img->getDataType();
        UInt32 width          = img->getWidth();
        UInt32 height         = img->getHeight();
        UInt32 depth          = img->getDepth();
        bool   compressedData = img->hasCompressedData();

        bool doScale = getScale(); // scale the texture to 2^?
        UInt32 frame = getFrame();

        bool defined = false;   // Texture defined ?
        bool needMipmaps =  getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
                            getMinFilter() == GL_LINEAR_MIPMAP_NEAREST  ||
                            getMinFilter() == GL_NEAREST_MIPMAP_LINEAR  ||
                            getMinFilter() == GL_LINEAR_MIPMAP_LINEAR   ;

        determineFormats(internalFormat, externalFormat);

        if(imgtarget == GL_TEXTURE_RECTANGLE_ARB && needMipmaps)
        {
            SWARNING << "TextureObjChunk::initialize1: Can't do mipmaps"
                     << "with GL_TEXTURE_RECTANGLE_ARB target! Ignored"
                     << std::endl;
            needMipmaps= false;
        }

        // do we need mipmaps?
        if(needMipmaps)
        {
            // do we have usable mipmaps ?
            if(img->getMipMapCount() == Int32(img->calcMipmapLevelCount()) &&
                 osgIsPower2(width) && osgIsPower2(height) &&
                 osgIsPower2(depth)
              )
            {
                UInt16 baseLevel = 0;
                Real32 skipLevels = osgClamp(0.f, getSkipMipMapLevels(), 1.f);

                if(img->getMipMapCount() != 0)
                {
                    baseLevel = 
                        UInt16(skipLevels * (img->getMipMapCount() - 1)); 
                }

                for(UInt16 i = baseLevel; i < img->getMipMapCount(); i++)
                {
                    UInt32 w, h, d;
                    img->calcMipmapGeometry(i, w, h, d);

                    if(compressedData)
                    {
                        switch (imgtarget)
                        {
                            case GL_TEXTURE_1D:
                                CompressedTexImage1D(
                                    GL_TEXTURE_1D, 
                                    i - baseLevel, 
                                    internalFormat,
                                    w, 
                                    getBorderWidth(),
                                    img->calcMipmapLevelSize(i),
                                    img->getData(i, frame, side));
                                break;
                            case GL_TEXTURE_2D:
                                CompressedTexImage2D(
                                    imgtarget, 
                                    i - baseLevel, 
                                    internalFormat,
                                    w, 
                                    h, 
                                    getBorderWidth(),
                                    img->calcMipmapLevelSize(i),
                                    img->getData(i, frame, side));
                                break;
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                                CompressedTexImage2D(
                                    imgtarget, 
                                    i - baseLevel, 
                                    internalFormat,
                                    w, 
                                    h, 
                                    getBorderWidth(),
                                    img->calcMipmapLevelSize(i),
                                    img->getData(i, frame, side));
                                break;
                            case GL_TEXTURE_3D:
                                CompressedTexImage3D(
                                    GL_TEXTURE_3D, 
                                    i - baseLevel, 
                                    internalFormat,
                                    w, 
                                    h, 
                                    d, 
                                    getBorderWidth(),
                                    img->calcMipmapLevelSize(i),
                                    img->getData(i, frame, side));
                                break;
                            default:
                                SFATAL << "TextureObjChunk::initialize1: "
                                       << "unknown target "
                                       << imgtarget << "!!!" << std::endl;
                                break;
                        }
                    }
                    else
                    {
                        switch (imgtarget)
                        {
                            case GL_TEXTURE_1D:
                                glTexImage1D(GL_TEXTURE_1D, 
                                             i - baseLevel, 
                                             internalFormat,
                                             w, 
                                             getBorderWidth(),
                                             externalFormat, 
                                             type,
                                             img->getData(i, frame, side));
                                break;
                            case GL_TEXTURE_2D:
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                            case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                            case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                                glTexImage2D(imgtarget, 
                                             i - baseLevel, 
                                             internalFormat,
                                             w, 
                                             h, 
                                             getBorderWidth(),
                                             externalFormat, 
                                             type,
                                             img->getData(i, frame, side));
                                break;
                            case GL_TEXTURE_3D:
                                TexImage3D(GL_TEXTURE_3D, 
                                           i - baseLevel, 
                                           internalFormat,
                                           w, 
                                           h, 
                                           d, 
                                           getBorderWidth(),
                                           externalFormat, 
                                           type,
                                           img->getData(i, frame, side));
                                break;
                            default:
                                SFATAL << "TextureObjChunk::initialize1: "
                                       << "unknown target "
                                       << imgtarget << "!!!" << std::endl;
                                break;
                        }
                    }
                }
                defined = true;
            }

            if(! defined)
            {
                // Nope, do we have SGIS_generate_mipmaps?
                if(win->hasExtension(_sgisGenerateMipmap))
                {
                    if(paramtarget != GL_NONE)
                    {
                        glTexParameteri(paramtarget, 
                                        GL_GENERATE_MIPMAP_SGIS, 
                                        GL_TRUE);
                    }

                    // same as GL_GENERATE_MIPMAP which is part of the
                    // standard since 1.4 

                    glErr("TextureObjChunk::activate generate_mipmaps");
                    needMipmaps = false; // automagic does it
                }
                else
                {
                    // Nope, try to use gluBuild?DMipmaps
                    void *data = NULL;

                    // can we use it directly?
                    if(! osgIsPower2(width) ||
                         ! osgIsPower2(height) ||
                         ! osgIsPower2(depth)
                      )
                    {
                        // scale is only implemented for 2D
                        if(imgtarget != GL_TEXTURE_2D)
                        {
                            SWARNING << "TextureObjChunk::initialize: can't mipmap "
                                     << "non-2D textures that are not 2^x !!!"
                                     << std::endl;
                        }
                        else
                        {
                            UInt32 outw = osgNextPower2(width);
                            UInt32 outh = osgNextPower2(height);

                            data = malloc(outw * outh * img->getBpp());

                            // should we scale to next power of 2?
                            if(doScale)
                            {
                                GLint res = gluScaleImage(externalFormat,
                                                width, height, type, img->getData(0, frame, side),
                                                outw, outh, type, data);

                                if(res)
                                {
                                    SWARNING << "TextureObjChunk::initialize: "
                                             << "gluScaleImage failed: "
                                             << gluErrorString(res) << "("
                                             << res << ")!"
                                             << std::endl;
                                    free(data);
                                    data = NULL;
                                }
                                else
                                {
                                    width = outw;
                                    height = outh;
                                }
                            }
                            else // nope, just copy the image to the lower left part
                            {
                                memset(data, 0, outw * outh * img->getBpp());

                                UInt16 bpl = width * img->getBpp();

                                const UInt8 * src = img->getData(0, 
                                                                 frame, 
                                                                 side);

                                UInt8 * dest= static_cast<UInt8 *>(data);

                                for(UInt32 y = 0; y < height; y++)
                                {
                                    memcpy(dest, src, bpl);

                                    src  += bpl;
                                    dest += outw * img->getBpp();
                                }
                                width = outw;
                                height = outh;
                            }
                        }
                    }
                    else
                    {
                        data = const_cast<void *>(
                            static_cast<const void *>(img->getData(0,
                                                                   frame,
                                                                   side)));
                    }

                    if(data)
                    {
                        switch (imgtarget)
                        {
                        case GL_TEXTURE_1D:
                                gluBuild1DMipmaps(imgtarget, internalFormat, width,
                                                    externalFormat, type, data);
                                break;
                        case GL_TEXTURE_2D:
                        case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                                gluBuild2DMipmaps(imgtarget, internalFormat,
                                                    width, height,
                                                    externalFormat, type, data);
                                break;
                        case GL_TEXTURE_3D:
#  ifdef GLU_VERSION_1_3
                                gluBuild3DMipmaps(imgtarget, internalFormat,
                                                    width, height, depth,
                                                    externalFormat, type, data);
#  else
                                FWARNING(("TextureObjChunk::initialize: 3d textures "
                                          "supported, but GLU version < 1.3, thus "
                                          "gluBuild3DMipmaps not supported!\n"));
#  endif
                                break;
                        default:
                                SFATAL << "TextureObjChunk::initialize2: unknown target "
                                       << imgtarget << "!!!" << std::endl;
                        }

                        if(data != img->getData(0, frame, side))
                            free(data);
                        defined = true;
                    } // data
                } // need to use gluBuildMipmaps?
            } // got them from the image already?
        } // need mipmaps?

        // no mipmaps, or mipmapping failed?
        if(! defined)
        {
            // got here needing mipmaps?
            if(needMipmaps && paramtarget != GL_NONE)  // turn them off
                glTexParameteri(paramtarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            void * data = NULL;
            UInt32 datasize = 0;

            // Do we need to massage the texture or can we just use it?
            if(imgtarget != GL_TEXTURE_RECTANGLE_ARB &&
               !win->hasExtension(_arbTextureNonPowerOfTwo) &&
               (!osgIsPower2(width) || !osgIsPower2(height) || !osgIsPower2(depth))
              )
            {
                // No, need to scale or cut

                // should we scale to next power of 2?
                if(doScale)
                {
                    // scale is only implemented for 2D
                    if(imgtarget != GL_TEXTURE_2D &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB &&
                       imgtarget != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
                      )
                    {
                        SWARNING << "TextureObjChunk::initialize: can't scale "
                                 << "non-2D textures that are not 2^x !!!"
                                 << std::endl;
                    }
                    else
                    {
                        UInt32 outw = osgNextPower2(width);
                        UInt32 outh = osgNextPower2(height);

                        data = malloc(outw * outh * img->getBpp());
                        datasize = outw * outh * img->getBpp();

                        GLint res = gluScaleImage(externalFormat,
                                        width, height, type,
                                        img->getData(0, frame, side),
                                        outw, outh, type, data);

                        if(res)
                        {
                            SWARNING << "TextureObjChunk::initialize: "
                                     << "gluScaleImage failed: "
                                     << gluErrorString(res) << "("
                                     << res << ")!" << std::endl;
                            free(data);
                            data = NULL;
                        }
                        else
                        {
                            width = outw;
                            height = outh;
                        }
                    }
                }
                else // don't scale, just use ll corner
                {
                   if(compressedData)
                   {
                       switch (imgtarget)
                       {
                       case GL_TEXTURE_1D:
                           CompressedTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                           osgNextPower2(width), getBorderWidth(), 0, NULL);
                           CompressedTexSubImage1D(GL_TEXTURE_1D, 0, 0, width,
                                           externalFormat,
                                           img->getFrameSize(),
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_2D:
                           CompressedTexImage2D(imgtarget, 0, internalFormat,
                                                osgNextPower2(width),
                                                osgNextPower2(height), 
                                                getBorderWidth(),
                                                0, NULL);
                           CompressedTexSubImage2D(imgtarget, 0, 0, 0, width, height,
                                           externalFormat,
                                           img->getFrameSize(),
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                           CompressedTexImage2D(imgtarget, 0, internalFormat,
                                           osgNextPower2(width),
                                           osgNextPower2(height), getBorderWidth(),
                                           0, NULL);
                           CompressedTexSubImage2D(imgtarget, 0, 0, 0, width, height,
                                           externalFormat,
                                           (img->getSideCount() > 1) ? img->getSideSize() :
                                                img->getFrameSize(),
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_RECTANGLE_ARB:
                           CompressedTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, internalFormat,
                                           width, height, getBorderWidth(),
                                           img->getFrameSize(),
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_3D:
                           CompressedTexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                           osgNextPower2(width),
                                           osgNextPower2(height),
                                           osgNextPower2(depth),
                                           getBorderWidth(), 0, NULL);
                           CompressedTexSubImage3D(GL_TEXTURE_3D, 0,  0, 0, 0,
                                           width, height, depth,
                                           externalFormat,
                                           img->getFrameSize(),
                                           img->getData(0, frame, side));
                           break;
                       default:
                               SFATAL << "TextureObjChunk::initialize4: unknown target "
                                      << imgtarget << "!!!" << std::endl;
                       }
                   }
                   else
                   {
                       switch (imgtarget)
                       {
                       case GL_TEXTURE_1D:
                           glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                           osgNextPower2(width), getBorderWidth(),
                                           externalFormat, type,
                                           NULL);
                           glTexSubImage1D(GL_TEXTURE_1D, 0, 0, width,
                                           externalFormat, type,
                                            img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_2D:
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                       case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                       case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                           glTexImage2D(imgtarget, 0, internalFormat,
                                           osgNextPower2(width),
                                           osgNextPower2(height), getBorderWidth(),
                                           externalFormat, type,
                                           NULL);
                           glTexSubImage2D(imgtarget, 0, 0, 0, width, height,
                                           externalFormat, type,
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_RECTANGLE_ARB:
                           glTexImage2D( GL_TEXTURE_RECTANGLE_ARB, 0, internalFormat,
                                           width, height, getBorderWidth(),
                                           externalFormat, type,
                                           img->getData(0, frame, side));
                           break;
                       case GL_TEXTURE_3D:
                             TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                           osgNextPower2(width),
                                           osgNextPower2(height),
                                           osgNextPower2(depth),
                                           getBorderWidth(), externalFormat, type, NULL);
                             TexSubImage3D(GL_TEXTURE_3D, 0,  0, 0, 0,
                                           width, height, depth,
                                           externalFormat, type,
                                           img->getData(0, frame, side));
                           break;
                       default:
                               SFATAL << "TextureObjChunk::initialize4: unknown target "
                                      << imgtarget << "!!!" << std::endl;
                       } // switch imgtarget
                   } // compressed data?

                   defined = true;
               } // do scale
            }
            else // can we use it directly?
            {
                data = const_cast<void *>(
                    static_cast<const void *>(img->getData(0,
                                                           frame,
                                                           side)));

                datasize = (img->getSideCount() > 1) ? img->getSideSize() :
                                                       img->getFrameSize();
            } // can we use it directly?

            if(!defined) // either we can use the texture directly, or it was scaled
            {
                // A image without data is quite handy if you need the
                // texture only on the graphics card. So don't check for data here

                if(compressedData)
                {
                    switch (imgtarget)
                    {
                    case GL_TEXTURE_1D:
                        CompressedTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                             width, getBorderWidth(),
                                             datasize, data);
                        break;
                    case GL_TEXTURE_2D:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                        CompressedTexImage2D(imgtarget, 0, internalFormat,
                                             width, height, getBorderWidth(),
                                             datasize, data);
                        break;
                    case GL_TEXTURE_RECTANGLE_ARB:
                        CompressedTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, internalFormat,
                                             width, height, getBorderWidth(),
                                             datasize, data);
                        break;
                    case GL_TEXTURE_3D:
                        CompressedTexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                             width, height, depth, getBorderWidth(),
                                             datasize, data);
                        break;
                    default:
                        SFATAL << "TextureObjChunk::initialize3: unknown target "
                               << imgtarget << "!!!" << std::endl;
                    }
                }
                else
                {
                    switch (imgtarget)
                    {
                    case GL_TEXTURE_1D:
                        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat,
                                     width, getBorderWidth(),
                                     externalFormat, type,
                                     data);
                        break;
                    case GL_TEXTURE_2D:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                        glTexImage2D(imgtarget, 0, internalFormat,
                                     width, height, getBorderWidth(),
                                     externalFormat, type,
                                     data);
                        break;
                    case GL_TEXTURE_RECTANGLE_ARB:
                        glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, internalFormat,
                                     width, height, getBorderWidth(),
                                     externalFormat, type,
                                     data);
                        break;
                    case GL_TEXTURE_3D:
                        TexImage3D(GL_TEXTURE_3D, 0, internalFormat,
                                   width, height, depth, getBorderWidth(),
                                   externalFormat, type,
                                   data);
                        break;
                    default:
                        SFATAL << "TextureObjChunk::initialize3: unknown target "
                               << imgtarget << "!!!" << std::endl;
                    }
                }

            }

            if(data != img->getData(0, frame, side))
                free(data);
        }

        glErr("TextureObjChunk::initialize image");

        // unbind texture
        glBindTexture(bindtarget, 0);

        // Clear image data after upload to the graphics card.
        if (img->getClearOnLoad())
        {
            img->clearData();
        }
    }
    else if(mode == Window::needrefresh)
    {
        // 3D texture functions
        OSGGETGLFUNCBYID(OSGglTexSubImage3D, TexSubImage3D,
                         _funcTexSubImage3D, win);

        // Compressed texture functions
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage1D, CompressedTexSubImage1D,
                         _funcCompressedTexSubImage1D, win);
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage2D, CompressedTexSubImage2D,
                         _funcCompressedTexSubImage2D, win);
        OSGGETGLFUNCBYID(OSGglCompressedTexSubImage3D, CompressedTexSubImage3D,
                         _funcCompressedTexSubImage3D, win);

        GLenum externalFormat = img->getPixelFormat();
        GLenum type           = img->getDataType();
        bool   compressedData = img->hasCompressedData();
        bool   has3DTex       = win->hasExtension(_extTex3D) ||
                                win->getGLVersion() >= 0x0102;

        if(bindtarget == GL_TEXTURE_3D && !has3DTex)
        {
            FINFO(("3D textures not supported on Window %p!\n", win));
            return;
        }

        if(! img) // no image ?
            return;

        if(getExternalFormat() != GL_NONE)
            externalFormat = getExternalFormat();

        if(!getScale() || imgtarget == GL_TEXTURE_RECTANGLE_ARB
                       || win->hasExtension(_arbTextureNonPowerOfTwo)
                       ||  (osgIsPower2(img->getWidth() ) &&
                            osgIsPower2(img->getHeight()) &&
                            osgIsPower2(img->getDepth() )
          )                )
        {
            // activate the texture
            glBindTexture(bindtarget, id);

            // Find out what to update
            UInt32 ix, ax, iy, ay, iz, az;
            ix = (getDirtyMinX()!=-1) ? getDirtyMinX() : 0;
            ax = (getDirtyMaxX()!=-1) ? getDirtyMaxX() : img->getWidth() - 1;
            iy = (getDirtyMinY()!=-1) ? getDirtyMinY() : 0;
            ay = (getDirtyMaxY()!=-1) ? getDirtyMaxY() : img->getHeight() - 1;
            iz = (getDirtyMinZ()!=-1) ? getDirtyMinZ() : 0;
            az = (getDirtyMaxZ()!=-1) ? getDirtyMaxZ() : img->getDepth() - 1;

            UInt32 w, h, d;
            w = ax - ix + 1;
            h = ay - iy + 1;
            d = az - iz + 1;

            if(w != UInt32(img->getWidth()))
                glPixelStorei(GL_UNPACK_ROW_LENGTH,  img->getWidth());
            if(ix != 0)
                glPixelStorei(GL_UNPACK_SKIP_PIXELS, ix);
            if(iy != 0)
                glPixelStorei(GL_UNPACK_SKIP_ROWS,   iy);
            if(has3DTex && iz != 0)
                glPixelStorei(GL_UNPACK_SKIP_IMAGES, iz);

            if(compressedData)
            {
                switch (imgtarget)
                {
                case GL_TEXTURE_1D:
                    CompressedTexSubImage1D(GL_TEXTURE_1D, 0, ix, w,
                                    externalFormat, img->getFrameSize(),
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_2D:
                    CompressedTexSubImage2D(imgtarget, 0, ix, iy, w, h,
                                    externalFormat, img->getFrameSize(),
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                    CompressedTexSubImage2D(imgtarget, 0, ix, iy, w, h,
                                    externalFormat,
                                    (img->getSideCount() > 1) ? img->getSideSize() :
                                                                img->getFrameSize(),
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_RECTANGLE_ARB:
                    CompressedTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0,
                                    ix, iy, w, h,
                                    externalFormat, img->getFrameSize(),
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_3D:
                      CompressedTexSubImage3D(GL_TEXTURE_3D, 0,  ix, iy, iz,
                                    w, h, d,
                                    externalFormat, img->getFrameSize(),
                                    img->getData( 0, getFrame(), side ) );
                    break;
                default:
                        SFATAL << "TextureObjChunk::refresh: unknown target "
                               << imgtarget << "!!!" << std::endl;
                }
            }
            else
            {
                switch (imgtarget)
                {
                case GL_TEXTURE_1D:
                    glTexSubImage1D(GL_TEXTURE_1D, 0, ix, w,
                                    externalFormat, type,
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_2D:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB:
                case GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB:
                case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB:
                    glTexSubImage2D(imgtarget, 0, ix, iy, w, h,
                                    externalFormat, type,
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_RECTANGLE_ARB:
                    glTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0,
                                    ix, iy, w, h,
                                    externalFormat, type,
                                    img->getData( 0, getFrame(), side ) );
                    break;
                case GL_TEXTURE_3D:
                      TexSubImage3D(GL_TEXTURE_3D, 0,  ix, iy, iz,
                                    w, h, d,
                                    externalFormat, type,
                                    img->getData( 0, getFrame(), side ) );
                    break;
                default:
                        SFATAL << "TextureObjChunk::refresh: unknown target "
                               << imgtarget << "!!!" << std::endl;
                }
            }


            if(w != UInt32(img->getWidth()))
                glPixelStorei(GL_UNPACK_ROW_LENGTH,  0);
            if(ix != 0)
                glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
            if(iy != 0)
                glPixelStorei(GL_UNPACK_SKIP_ROWS,   0);
            if(has3DTex && iz != 0)
                glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);

            if(paramtarget != GL_NONE)
            {
                glTexParameterf(paramtarget, GL_TEXTURE_PRIORITY,
                                  getPriority());
                glTexParameteri(paramtarget, GL_TEXTURE_MIN_FILTER,
                                getMinFilter()                     );
                glTexParameteri(paramtarget, GL_TEXTURE_MAG_FILTER,
                                getMagFilter()                     );
            }

            // unbind the texture
            glBindTexture(bindtarget, 0);
        }
        else
        {
            SWARNING << "TextureObjChunk::refresh: not implemented yet for "
                     << "scaling!!!" << std::endl;
        }

        glErr("TextureObjChunk::refresh image");
    }

}


/*! GL object handler
    create the texture and destroy it
*/
UInt32 TextureObjChunk::handleGL(DrawEnv                 *pEnv, 
                                 UInt32                   osgid, 
                                 Window::GLObjectStatusE  mode,
                                 UInt32                   uiOptions)
{
    Window *win = pEnv->getWindow();
    GLuint  id  = win->getGLObjectId(osgid);

    if(mode == Window::initialize || mode == Window::reinitialize ||
       mode == Window::needrefresh )
    {
        if(mode == Window::initialize)
        {
            glGenTextures(1, &id);
            win->setGLObjectId(osgid, id);
        }

        GLenum target;

        Image *img = getImage();

        if (img != NULL)
        {
            if(img->getSideCount() == 1)
            {
                target = getTarget();
                if ( target == GL_NONE )
                {
                    if(img->getDepth() > 1)
                    {
                        if(win->hasExtension(_extTex3D) ||
                           win->getGLVersion() >= 0x0102)
                        {
                            target = GL_TEXTURE_3D;
                        }
                        else
                        {
                            FWARNING(
                                ("TextureObjChunk::initialize: 3D textures not "
                                 "supported for this window!\n"));
                            return 0;
                        }
                    }
                    else if(img->getHeight() > 1)
                    {
                        target = GL_TEXTURE_2D;
                    }
                    else
                    {
                        target = GL_TEXTURE_1D;
                    }
                }

                handleTexture(win, id, target, target, target, mode, img);
            }
            else
            {
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
                              mode, getImage(), 5);
                // Have to use initialize mode here, otherwise the
                // texture is destroyed for every side
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_NONE,
                              GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
                              Window::initialize, getImage(), 4);
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_NONE,
                              GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
                              Window::initialize, getImage(), 3);
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_NONE,
                              GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
                              Window::initialize, getImage(), 2);
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_NONE,
                              GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
                              Window::initialize, getImage(), 1);
                handleTexture(win, id,
                              GL_TEXTURE_CUBE_MAP_ARB,
                              GL_NONE,
                              GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
                              Window::initialize, getImage(), 0);

            }
        }
    }
    else
    {
        SWARNING << "TextureObjChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

    return 0;
}

/*! GL object handler
    destroy it
*/
void TextureObjChunk::handleDestroyGL(DrawEnv                 *pEnv, 
                                      UInt32                   osgid, 
                                      Window::GLObjectStatusE  mode)
{
    Window *win = pEnv->getWindow();
    GLuint  id  = win->getGLObjectId(osgid);

    if(mode == Window::destroy)
    {
        glDeleteTextures(1, &id);
        win->setGLObjectId(osgid, 0);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last texture user destroyed" << std::endl;
    }
    else
    {
        SWARNING << "TextureObjChunk::handleDestroyGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

void TextureObjChunk::activate(DrawEnv *pEnv, UInt32 idx)
{
#ifdef OSG_DUMP_TEX
    fprintf(stderr, "Activate %d\n", _uiChunkId);
#endif

    Window *win = pEnv->getWindow();

    Real32 nteximages, ntexcoords;

    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant)
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }

    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant)
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureObjChunk::activate: Trying to bind image unit %d,"
                  " but Window %p only supports %lf!\n",
                  idx, win, nteximages));
#endif
        return;
    }

    if(activateTexture(win, idx))
        return; // trying to access too many textures

    win->validateGLObject(getGLId(), pEnv);

    Image  *img    = getImage();
    GLenum  target = getTarget();

    if(img == NULL || ! img->getDimension()) // no image ?
        return;

    glErr("TextureObjChunk::activate precheck");

    if(img->getSideCount() == 1)
    {
        if(target == GL_NONE)
        {
            if(img->getDepth() > 1)
            {
                if(win->hasExtension(_extTex3D) ||
                   win->getGLVersion() >= 0x0102)
                {
                    target = GL_TEXTURE_3D;
                }
                else
                {
                    FWARNING(("TextureObjChunk::activate: 3D textures not "
                              "supported for this window!\n"));
                    return;
                }
            }
            else if(img->getHeight() > 1)
            {
                target = GL_TEXTURE_2D;
            }
            else
            {
                target = GL_TEXTURE_1D;
            }
        }
    }
    else
    {
        target = GL_TEXTURE_CUBE_MAP_ARB;
    }

#ifdef OSG_DUMP_TEX
    FDEBUG(("TextureObjChunk::activate - %d\n", getGLId()));
#endif

    // Update the texture statistics
    StatCollectorP pColl = pEnv->getStatCollector();
    
    if(NULL != pColl)
    {
        pColl->getElem(statNTextures)->inc(getGLId());
        pColl->getElem(statNTexBytes)->add(getGLId(), 
                                           img->getSize(true,true,true));
    }


    glBindTexture(target, win->getGLObjectId(getGLId()));

    pEnv->setActiveTexTarget(idx, target);

    Real32 ntexunits = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

    // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
    if(ntexunits == Window::unknownConstant)
        ntexunits = 1.0f;

    if(idx < static_cast<UInt32>(ntexunits))
    {
        glEnable(target);
    }

    glErr("TextureObjChunk::activate");
}


void TextureObjChunk::changeFrom(DrawEnv    *pEnv,
                                 StateChunk *old   ,
                                 UInt32      idx )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime.
    // is that a valid assumption?
    if(old == this)
        return;

    // If the old one is not a texture chunk, deactivate it and activate
    // ourselves
    // Need to check for exact type, as derived chunks might change
    // different state (e.g. CubeTexture)
    if(getTypeId() != old->getTypeId())
    {
        old->deactivate(pEnv, idx);
        activate(pEnv, idx);
        return;
    }

    TextureObjChunk *oldp      = dynamic_cast<TextureObjChunk *>(old);

#ifdef OSG_DUMP_TEX
    fprintf(stderr, "Change %d %d\n", oldp->_uiChunkId, _uiChunkId);
#endif

    Image        *img       = getImage();
    GLenum        target    = getTarget();
    GLenum        oldtarget = oldp->getTarget();
    bool          oldused   = (oldp->getImage() != NULL &&
                               oldp->getImage()->getDimension());

    if(img == NULL || img->getDimension() == 0)
    {
        oldp->deactivate(pEnv, idx);
        return;
    }

    glErr("TextureObjChunk::changeFrom precheck");

    Window *win = pEnv->getWindow();

    if(activateTexture(win, idx))
        return; // trying to use too many textures

    UInt32 nteximages, ntexcoords, ntexunits;

    Real32 dummy = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

    if(dummy == Window::unknownConstant)
    {
        ntexunits = 1;
    }
    else
    {
        ntexunits = static_cast<UInt32>(dummy);
    }

    if((dummy = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant
      )
    {
        nteximages = ntexunits;
    }
    else
    {
        nteximages = static_cast<UInt32>(dummy);
    }

    if((dummy = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = ntexunits;
    }
    else
    {
        ntexcoords = static_cast<UInt32>(dummy);
    }

    if(idx >= nteximages)
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureObjChunk::activate: Trying to bind image unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, nteximages));
#endif
        return;
    }

    if(img->getSideCount() == 1)
    {
        if(target == GL_NONE)
        {
            if(img->getDepth() > 1)
            {
                if(win->hasExtension(_extTex3D) ||
                   win->getGLVersion() >= 0x0102)
                {
                    target = GL_TEXTURE_3D;
                }
                else
                {
                    FWARNING(("TextureObjChunk::changeFrom: 3D textures not "
                              "supported for this window!\n"));
                    oldp->deactivate(pEnv, idx);
                    return;
                }
            }
            else if(img->getHeight() > 1)   target = GL_TEXTURE_2D;
            else                            target = GL_TEXTURE_1D;
        }
    }
    else
    {
        target = GL_TEXTURE_CUBE_MAP_ARB;
    }

    if(oldused)
    {
        if(oldp->getImage()->getSideCount() == 1)
        {
            if(oldtarget == GL_NONE)
            {
                if(oldp->getImage()->getDepth() > 1)
                {
                    if(win->hasExtension(_extTex3D) ||
                       win->getGLVersion() >= 0x0102 )
                    {
                        oldtarget = GL_TEXTURE_3D;
                    }
                    else
                    {
                        FWARNING(("TextureObjChunk::changeFrom: 3D textures "
                                  "not supported for this window!\n"));
                        oldp->deactivate(pEnv, idx);
                        return;
                    }
                }
                else if(oldp->getImage()->getHeight() > 1)
                {
                    oldtarget = GL_TEXTURE_2D;
                }
                else
                {
                    oldtarget = GL_TEXTURE_1D;
                }
            }
        }
        else
        {
            oldtarget = GL_TEXTURE_CUBE_MAP_ARB;
        }

        if(target != oldtarget && idx < ntexunits)
        {
            glDisable(oldtarget);
        }
    }

    win->validateGLObject(getGLId(), pEnv);


    // Update the texture statistics
    StatCollectorP pColl = pEnv->getStatCollector();
    
    if(NULL != pColl)
    {
        pColl->getElem(statNTextures)->inc(getGLId());
        pColl->getElem(statNTexBytes)->add(getGLId(), img->getSize(true,true,true));
    }


    glBindTexture(target, win->getGLObjectId(getGLId()));

    pEnv->setActiveTexTarget(idx, GL_TEXTURE_CUBE_MAP_ARB);


    if(idx < ntexunits)
    {
        if(target != oldtarget)
        {
            glEnable(target);
        }
    }

    glErr("TextureObjChunk::changeFrom");
}

void TextureObjChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
#ifdef OSG_DUMP_TEX
    fprintf(stderr, "Deactivate %d\n", _uiChunkId);
#endif

    Window *win = pEnv->getWindow();

    Real32 nteximages, ntexcoords;
    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant
      )
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }
    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant
      )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("TextureObjChunk::deactivate: Trying to bind image unit %d,"
                  " but Window %p only supports %lf!\n",
                  idx, win, nteximages));
#endif
        return;
    }

    Image  *img    = getImage();
    GLenum  target = getTarget();

    if(img == NULL || ! img->getDimension())
      return;

    glErr("TextureObjChunk::deactivate precheck");

    bool isActive = false;


    Real32 ntexunits = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

    if(ntexunits == Window::unknownConstant)
        ntexunits = 1.0f;

    if(idx >= static_cast<UInt32>(ntexunits))
        return; // textures >= MTU are not enabled and don't have an env

    if(!isActive)
        activateTexture(win, idx);

    if(img->getSideCount() == 1)
    {
        if ( target == GL_NONE )
        {
            if ( img->getDepth() > 1 )
            {
                if(win->hasExtension(_extTex3D) ||
                   win->getGLVersion() >= 0x0102)
                {
                    target = GL_TEXTURE_3D;
                }
                else
                {
                    FWARNING(("TextureObjChunk::deactivate: 3D textures not "
                              "supported for this window!\n"));
                    return;
                }
            }
            else if(img->getHeight() > 1)   target = GL_TEXTURE_2D;
            else                            target = GL_TEXTURE_1D;
        }
    }
    else
    {
        target = GL_TEXTURE_CUBE_MAP_ARB;
    }

    glDisable(target);

    pEnv->setActiveTexTarget(idx, GL_NONE);

    glErr("TextureObjChunk::deactivate");
}

GLenum TextureObjChunk::determineTextureTarget(Window *pWindow) const
{
    GLenum target = GL_NONE;

    Image *img = getImage();

    if(img != NULL)
    {
        target = getTarget();

        if(target == GL_NONE)
        {
            if(img->getDepth() > 1)
            {
                if(pWindow->hasExtension(_extTex3D))
                {
                    target = GL_TEXTURE_3D;
                }
                else
                {
                    FWARNING(("TexturObjChunk::initialize: 3D textures not "
                              "supported for this window!\n"));
                    return target;
                }
            }
            else if(img->getHeight() > 1)
            {
                target = GL_TEXTURE_2D;
            }
            else
            {
                target = GL_TEXTURE_1D;
            }
        }
    }

    return target;
}

void TextureObjChunk::determineFormats(
    GLenum &internalFormat, GLenum &externalFormat) const
{
    Image  *img            = getImage         ();
            internalFormat = getInternalFormat();

    if(img != NULL)
    {
                externalFormat = img->getPixelFormat();
        GLenum  type           = img->getDataType   ();

        if(internalFormat == GL_NONE)
        {
            switch(externalFormat)
            {
#if defined(GL_BGR) && defined(GL_BGR_EXT)
            case GL_BGR:
#else
#  if defined(GL_BGR)
            case GL_BGR:
#  endif
#  if defined(GL_BGR_EXT)
            case GL_BGR_EXT:
#  endif
#endif
            case GL_RGB:
            {
                switch(type)
                {
#if defined(GL_ARB_texture_float)
                case GL_FLOAT:
                    internalFormat = GL_RGB32F;
                    break;

                case GL_HALF_FLOAT_NV:
                    internalFormat = GL_RGB16F;
                    break;
#endif

                default:
                    internalFormat = GL_RGB;
                }
            }
            break;

#if defined(GL_BGRA) && defined(GL_BGRA_EXT)
            case GL_BGRA:
#else
#  if defined(GL_BGRA)
            case GL_BGRA:
#  endif
#  if defined(GL_BGRA_EXT)
            case GL_BGRA_EXT:
#  endif
#endif
            case GL_RGBA:
            {
                switch(type)
                {
#if defined(GL_ARB_texture_float)
                case GL_FLOAT:
                    internalFormat = GL_RGBA32F;
                    break;

                case GL_HALF_FLOAT_NV:
                    internalFormat = GL_RGBA16F;
                    break;
#endif
                default:
                    internalFormat = GL_RGBA;
                }
            }
            break;

            case GL_INTENSITY:
                internalFormat = GL_INTENSITY;
                externalFormat = GL_LUMINANCE;
                break;

            default:
                internalFormat = externalFormat;
                break;
            }
        }
    }
    else
    {
        externalFormat = getExternalFormat();
    }

    if(getExternalFormat() != GL_NONE)
        externalFormat = getExternalFormat();
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TextureObjChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureObjChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TextureObjChunk::operator == (const StateChunk &other) const
{
    TextureObjChunk const *tother =
        dynamic_cast<TextureObjChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;


    bool returnValue =
        getImage          () == tother->getImage          () &&
        getMinFilter      () == tother->getMinFilter      () &&
        getMagFilter      () == tother->getMagFilter      () &&
        getWrapS          () == tother->getWrapS          () &&
        getWrapT          () == tother->getWrapT          () &&
        getWrapR          () == tother->getWrapR          () &&
        getPriority       () == tother->getPriority       ();

    return returnValue;
}

bool TextureObjChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

