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

#include "OSGConfig.h"

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGImage.h>

#include "OSGDrawActionBase.h"
#include "OSGDrawEnv.h"

#include "OSGTextureEnvChunk.h"
#include "OSGTextureBaseChunk.h"

//#define OSG_DUMP_TEX

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureEnvChunk
    \ingroup GrpSystemState

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TextureEnvChunk::_class("TextureEnv", osgMaxTexImages, 20);

UInt32 TextureEnvChunk::_nvPointSprite           = Window::invalidExtensionID;
UInt32 TextureEnvChunk::_nvTextureShader         = Window::invalidExtensionID;
UInt32 TextureEnvChunk::_nvTextureShader2        = Window::invalidExtensionID;
UInt32 TextureEnvChunk::_nvTextureShader3        = Window::invalidExtensionID;
UInt32 TextureEnvChunk::_extTextureLodBias       = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void TextureEnvChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _nvPointSprite     =
            Window::registerExtension("GL_NV_point_sprite"     );
        _nvTextureShader   =
            Window::registerExtension("GL_NV_texture_shader"   );
        _nvTextureShader2  =
            Window::registerExtension("GL_NV_texture_shader2"  );
        _nvTextureShader3  =
            Window::registerExtension("GL_NV_texture_shader3"  );
        _extTextureLodBias  = 
            Window::registerExtension("GL_EXT_texture_lod_bias");

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

TextureEnvChunk::TextureEnvChunk(void) :
    Inherited()
{
}

TextureEnvChunk::TextureEnvChunk(const TextureEnvChunk &source) :
    Inherited(source)
{
}

TextureEnvChunk::~TextureEnvChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TextureEnvChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------ State ------------------------------------*/

/*! Texture handler. Create/update a single texture.
    Also used by derived CubeMap chunk.
*/

void TextureEnvChunk::handleTextureShader(Window *win, GLenum bindtarget)
{
    if(!win->hasExtension(_nvTextureShader))
    {
        if(getShaderOperation() != GL_NONE)
            FINFO(("NV Texture Shaders not supported on Window %p!\n", win));
        return;
    }

    glErr("textureShader precheck");

    glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV,
                getShaderOperation());

    glErr("textureShader setup: operation");

    if(getShaderOperation() == GL_NONE)
        return;

    if(bindtarget == GL_TEXTURE_3D && !win->hasExtension(_nvTextureShader2))
    {
        FINFO(("NV Texture Shaders 2 not supported on Window %p!\n", win));
        return;
    }

    if(getShaderInput() != GL_NONE)
        glTexEnvi(GL_TEXTURE_SHADER_NV, GL_PREVIOUS_TEXTURE_INPUT_NV,
                    getShaderInput());

    glErr("textureShader setup: input");

    if(getShaderRGBADotProduct() != GL_NONE)
        glTexEnvi(GL_TEXTURE_SHADER_NV, 
                  GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV,
                  getShaderRGBADotProduct());

    glErr("textureShader setup: rgba dotprod");

    if(getShaderOffsetMatrix().size() == 4)
    {
        glTexEnvfv(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_MATRIX_NV,
                    (GLfloat*)&(getShaderOffsetMatrix()[0]));

        glErr("textureShader setup: offset matrix");
    }
    else if(getShaderOffsetMatrix().size() != 0)
    {
        FWARNING(("TextureEnvChunk::handleTextureShader: shaderOffsetMatrix "
                  "has to have 4 entries, not %d!\n",
                    getShaderOffsetMatrix().size() ));
    }

    glTexEnvf(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_SCALE_NV,
                getShaderOffsetScale());

    glErr("textureShader setup: offset scale");

    glTexEnvf(GL_TEXTURE_SHADER_NV, GL_OFFSET_TEXTURE_BIAS_NV,
                getShaderOffsetBias());

    glErr("textureShader setup: offset bias");

    GLint cullmodes[4];
    if(getShaderCullModes() & 0x1)
    {
        cullmodes[0] = GL_GEQUAL;
    }
    else
    {
        cullmodes[0] = GL_LESS;
    }

    if(getShaderCullModes() & 0x2)
    {
        cullmodes[1] = GL_GEQUAL;
    }
    else
    {
        cullmodes[1] = GL_LESS;
    }

    if(getShaderCullModes() & 0x4)
    {
        cullmodes[2] = GL_GEQUAL;
    }
    else
    {
        cullmodes[2] = GL_LESS;
    }

    if(getShaderCullModes() & 0x8)
    {
        cullmodes[3] = GL_GEQUAL;
    }
    else
    {
        cullmodes[3] = GL_LESS;
    }

    glTexEnviv(GL_TEXTURE_SHADER_NV, GL_CULL_MODES_NV,
                    cullmodes);

    glErr("textureShader setup: cull modes");

    glTexEnvfv(GL_TEXTURE_SHADER_NV, GL_CONST_EYE_NV,
                    getShaderConstEye().getValues());

    glErr("textureShader setup: const eye");



#ifdef OSG_DEBUG
    GLint consistent;
    glGetTexEnviv(GL_TEXTURE_SHADER_NV, GL_SHADER_CONSISTENT_NV,
          &consistent);
    if(!consistent)
    {
        FWARNING(("Texture shaders not consistent!\n"));
    }
#endif
}

/*------------------------------- Sync -----------------------------------*/

/*! React to field changes.
    Note: this function also handles CubeTexture changes, make sure to keep
    it consistent with the cubeTexture specifics
*/

void TextureEnvChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

bool TextureEnvChunk::isTransparent(void) const
{
    // Even if the texture has alpha, the Blending is makes the sorting
    // important, thus textures per se are not transparent
    return false;
}


/*----------------------------- onCreate --------------------------------*/

void TextureEnvChunk::onCreate(const TextureEnvChunk *source)
{
    Inherited::onCreate(source);
}

void TextureEnvChunk::onCreateAspect(const TextureEnvChunk *createAspect,
                                     const TextureEnvChunk *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

/*------------------------------ Output ----------------------------------*/

void TextureEnvChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TextureEnvChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/


void TextureEnvChunk::activate(DrawEnv *pEnv, UInt32 idx)
{    
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
        FWARNING(("TextureEnvChunk::activate: Trying to bind image unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, nteximages));
#endif
        return;        
    }

    if(TextureBaseChunk::activateTexture(win, idx) == true)
        return;

#ifdef GL_NV_point_sprite
    if(idx < static_cast<UInt32>(ntexcoords))
    {
        if(getPointSprite() && win->hasExtension(_nvPointSprite))
        {
            glTexEnvi(GL_POINT_SPRITE_NV, GL_COORD_REPLACE_NV, GL_TRUE);
        }
    }
#endif

    if(getLodBias() != 0.0f && win->hasExtension(_extTextureLodBias))
    {
        glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT, 
                  GL_TEXTURE_LOD_BIAS_EXT,
	              getLodBias());
    }

    Real32 ntexunits = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

    // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
    if(ntexunits == Window::unknownConstant)
        ntexunits = 1.0f;

    if(idx < static_cast<UInt32>(ntexunits))
    {
        // texture env
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());

        glTexEnvfv(GL_TEXTURE_ENV, 
                   GL_TEXTURE_ENV_COLOR,
                   (GLfloat*)getEnvColor().getValuesRGBA());

        if(getEnvMode() == GL_COMBINE_EXT)
        {
            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_COMBINE_RGB_EXT,  
                      getEnvCombineRGB ());

            glTexEnvf(GL_TEXTURE_ENV, 
                      GL_RGB_SCALE_EXT,    
                      getEnvScaleRGB   ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE0_RGB_EXT,  
                      getEnvSource0RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE1_RGB_EXT,  
                      getEnvSource1RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE2_RGB_EXT,  
                      getEnvSource2RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND0_RGB_EXT, 
                      getEnvOperand0RGB());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND1_RGB_EXT, 
                      getEnvOperand1RGB());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND2_RGB_EXT, 
                      getEnvOperand2RGB());


            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_COMBINE_ALPHA_EXT, 
                      getEnvCombineAlpha ());

            glTexEnvf(GL_TEXTURE_ENV, 
                      GL_ALPHA_SCALE,       
                      getEnvScaleAlpha   ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE0_ALPHA_EXT, 
                      getEnvSource0Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE1_ALPHA_EXT, 
                      getEnvSource1Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE2_ALPHA_EXT, 
                      getEnvSource2Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND0_ALPHA_EXT,
                      getEnvOperand0Alpha());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND1_ALPHA_EXT,
                      getEnvOperand1Alpha());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND2_ALPHA_EXT,
                      getEnvOperand2Alpha());
        }

        TextureEnvChunk::handleTextureShader(
            win, 
            pEnv->getActiveTexTarget(idx));

        if(idx                                 == 0       &&
           getShaderOperation()                != GL_NONE && 
           win->hasExtension(_nvTextureShader) == true      )
        {
            glEnable(GL_TEXTURE_SHADER_NV);
        }
    }
    
    glErr("TextureEnvChunk::activate");
}

void TextureEnvChunk::changeFrom(DrawEnv    *pEnv, 
                                 StateChunk *old   , 
                                 UInt32      idx   )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    TextureEnvChunk *oldp = dynamic_cast<TextureEnvChunk *>(old);

    glErr("TextureEnvChunk::changeFrom precheck");

    Window *win = pEnv->getWindow();   

    if(TextureBaseChunk::activateTexture(win, idx))
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
   
    
    if((dummy = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant)
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
        FWARNING(("TextureEnvChunk::activate: Trying to bind image unit %d,"
                  " but Window %p only supports %d!\n",
                  idx, win, nteximages));
#endif
        return;        
    }

#ifdef GL_NV_point_sprite
    if(idx < ntexcoords)
    {
        if(oldp->getPointSprite() != getPointSprite() &&
           win->hasExtension(_nvPointSprite))
        {
            glTexEnvi(GL_POINT_SPRITE_NV, 
                      GL_COORD_REPLACE_NV,
                      getPointSprite());
        }
    }
#endif

    if(oldp->getLodBias() != getLodBias() &&
       win->hasExtension(_extTextureLodBias))
    {
        glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT, 
                  GL_TEXTURE_LOD_BIAS_EXT,
                  getLodBias());
    }

    if(idx < ntexunits)
    {
        if(oldp->getEnvMode() != getEnvMode())
        {
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode());
        }

        glTexEnvfv(GL_TEXTURE_ENV, 
                   GL_TEXTURE_ENV_COLOR,
                   (GLfloat *) getEnvColor().getValuesRGBA());

        if(getEnvMode() == GL_COMBINE_EXT)
        {
            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_COMBINE_RGB_EXT,  
                      getEnvCombineRGB ());

            glTexEnvf(GL_TEXTURE_ENV, 
                      GL_RGB_SCALE_EXT,    
                      getEnvScaleRGB   ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE0_RGB_EXT,  
                      getEnvSource0RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE1_RGB_EXT,  
                      getEnvSource1RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE2_RGB_EXT,  
                      getEnvSource2RGB ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND0_RGB_EXT, 
                      getEnvOperand0RGB());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND1_RGB_EXT, 
                      getEnvOperand1RGB());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND2_RGB_EXT, 
                      getEnvOperand2RGB());



            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_COMBINE_ALPHA_EXT, 
                      getEnvCombineAlpha ());

            glTexEnvf(GL_TEXTURE_ENV, 
                      GL_ALPHA_SCALE,       
                      getEnvScaleAlpha   ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE0_ALPHA_EXT, 
                      getEnvSource0Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE1_ALPHA_EXT, 
                      getEnvSource1Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_SOURCE2_ALPHA_EXT, 
                      getEnvSource2Alpha ());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND0_ALPHA_EXT,
                      getEnvOperand0Alpha());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND1_ALPHA_EXT,
                      getEnvOperand1Alpha());

            glTexEnvi(GL_TEXTURE_ENV, 
                      GL_OPERAND2_ALPHA_EXT,
                      getEnvOperand2Alpha());
        }

        if(win->hasExtension(_nvTextureShader))
        {
            if(      getShaderOperation() != GL_NONE &&
               oldp->getShaderOperation() == GL_NONE   )
            {
                handleTextureShader(win, 
                                    pEnv->getActiveTexTarget(idx));

                if(idx == 0)
                    glEnable(GL_TEXTURE_SHADER_NV);
            }
            else if(      getShaderOperation() == GL_NONE &&
                    oldp->getShaderOperation() != GL_NONE   )
            {
                glTexEnvi(GL_TEXTURE_SHADER_NV, 
                          GL_SHADER_OPERATION_NV, 
                          GL_NONE);

                if(idx == 0)
                {
                    glDisable(GL_TEXTURE_SHADER_NV);
                }
            }
        }
    }

    glErr("TextureEnvChunk::changeFrom");
}


void TextureEnvChunk::deactivate(DrawEnv *pEnv, UInt32 idx)
{
    Window *win = pEnv->getWindow();   

    Real32 nteximages, ntexcoords;
    if((nteximages = win->getConstantValue(GL_MAX_TEXTURE_IMAGE_UNITS_ARB)) ==
       Window::unknownConstant )
    {
        nteximages = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(nteximages == Window::unknownConstant)
            nteximages = 1.0f;
    }

    if((ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_COORDS_ARB)) ==
       Window::unknownConstant )
    {
        ntexcoords = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

        // sgi doesn't support GL_MAX_TEXTURE_UNITS_ARB!
        if(ntexcoords == Window::unknownConstant)
            ntexcoords = 1.0f;
    }

    if(idx >= static_cast<UInt32>(nteximages))
    {
#ifdef OSG_DEBUG
        FWARNING(("CubeTextureEnvChunk::deactivate: Trying to bind image unit "
                  "%d, but Window %p only supports %d!\n",
                  idx, win, nteximages));
#endif
        return;        
    }

    bool isActive = false;

#ifdef GL_NV_point_sprite
    if(getPointSprite() &&
       win->hasExtension(_nvPointSprite) &&
       idx < static_cast<UInt32>(ntexcoords) )
    {
        if(!isActive)
        {
            TextureBaseChunk::activateTexture(win, idx);
            isActive = true;
        }

        glTexEnvi(GL_POINT_SPRITE_NV, GL_COORD_REPLACE_NV, GL_FALSE);
    }
#endif

    if(getLodBias() != 0.0f && win->hasExtension(_extTextureLodBias))
    {
        if(!isActive)
        {
            TextureBaseChunk::activateTexture(win, idx);
            isActive = true;
        }

        glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT, 
                  GL_TEXTURE_LOD_BIAS_EXT,
                  0.0f);

    }
    
    Real32 ntexunits = win->getConstantValue(GL_MAX_TEXTURE_UNITS_ARB);

    if(ntexunits == Window::unknownConstant)
        ntexunits = 1.0f;
    
    if(idx >= static_cast<UInt32>(ntexunits))
    {
        return; // tetxures >= MTU are not enabled and don't have an env
    }
   
    if(!isActive)
        TextureBaseChunk::activateTexture(win, idx);

    if(getShaderOperation() != GL_NONE &&
       win->hasExtension(_nvTextureShader))
    {
        glTexEnvi(GL_TEXTURE_SHADER_NV, GL_SHADER_OPERATION_NV, GL_NONE);

        if(idx == 0)
            glDisable(GL_TEXTURE_SHADER_NV);
    }

    glErr("CubeTextureBaseChunk::deactivate");
}

/*-------------------------- Comparison -----------------------------------*/

Real32 TextureEnvChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TextureEnvChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool TextureEnvChunk::operator == (const StateChunk &other) const
{
    TextureEnvChunk const *tother = 
        dynamic_cast<TextureEnvChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    bool returnValue = 
        getEnvMode  () == tother->getEnvMode  ();

    if(returnValue == true && getEnvMode() == GL_COMBINE_EXT)
    {
        returnValue =
            getEnvCombineRGB ()   == tother->getEnvCombineRGB   () &&

            getEnvSource0RGB ()   == tother->getEnvSource0RGB   () &&
            getEnvSource1RGB ()   == tother->getEnvSource1RGB   () &&
            getEnvSource2RGB ()   == tother->getEnvSource2RGB   () &&

            getEnvOperand0RGB()   == tother->getEnvOperand0RGB  () &&
            getEnvOperand1RGB()   == tother->getEnvOperand1RGB  () &&
            getEnvOperand2RGB()   == tother->getEnvOperand2RGB  () &&

            getEnvCombineAlpha () == tother->getEnvCombineAlpha () &&

            getEnvSource0Alpha () == tother->getEnvSource0Alpha () &&
            getEnvSource1Alpha () == tother->getEnvSource1Alpha () &&
            getEnvSource2Alpha () == tother->getEnvSource2Alpha () &&

            getEnvOperand0Alpha() == tother->getEnvOperand0Alpha() &&
            getEnvOperand1Alpha() == tother->getEnvOperand1Alpha() &&
            getEnvOperand2Alpha() == tother->getEnvOperand2Alpha();


        returnValue &=
           ((        getEnvScaleRGB  () - tother->getEnvScaleRGB  ()) < Eps) &&
           ((tother->getEnvScaleRGB  () -         getEnvScaleRGB  ()) < Eps) &&
           ((        getEnvScaleAlpha() - tother->getEnvScaleAlpha()) < Eps) &&
           ((tother->getEnvScaleAlpha() -         getEnvScaleAlpha()) < Eps);


    }

    return returnValue;
}

bool TextureEnvChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_hpp       [] = OSGTEXTUREENVCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTUREENVCHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTUREENVCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

