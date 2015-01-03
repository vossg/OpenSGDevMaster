/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGConfig.h>

#include <OSGBaseFunctions.h>

#include "OSGFresnelMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \class osg::FresnelMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FresnelMaterial::FresnelMaterial(void) :
     Inherited      (    ),
    _materialChunk  (NULL),
    _textureObjChunk(NULL),
    _textureEnvChunk(NULL),
    _texGenChunk    (NULL),
    _blendChunk     (NULL),
    _img            (NULL)
{
}

FresnelMaterial::FresnelMaterial(const FresnelMaterial &source) :
     Inherited      (source                 ),
    _materialChunk  (source._materialChunk  ),
    _textureObjChunk(source._textureObjChunk),
    _textureEnvChunk(source._textureEnvChunk),
    _texGenChunk    (source._texGenChunk    ),
    _blendChunk     (source._blendChunk     ),
    _img            (source._img            )
{
}

FresnelMaterial::~FresnelMaterial(void)
{
}

void FresnelMaterial::resolveLinks(void)
{
    Inherited::resolveLinks();

    _materialChunk   = NULL;
    _textureObjChunk = NULL;
    _textureEnvChunk = NULL;
    _texGenChunk     = NULL; 
    _blendChunk      = NULL;
    _img             = NULL;
}

void FresnelMaterial::prepareLocalChunks(void)
{
    if(_textureObjChunk != NULL)
        return;

    _img = Image::create();
    
    UInt8 imgdata[] = 
    { 
        255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 
    };
   
    _img->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata);
    
    _materialChunk = MaterialChunk::create();
    
    _textureObjChunk = TextureObjChunk::create();

    _textureObjChunk->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    _textureObjChunk->setMagFilter(GL_LINEAR              );
    _textureObjChunk->setWrapS    (GL_CLAMP               );
    _textureObjChunk->setWrapT    (GL_CLAMP               );

    _textureEnvChunk = TextureEnvChunk::create();

    _textureEnvChunk->setEnvMode(GL_DECAL);

    _texGenChunk  = TexGenChunk::create();

    _texGenChunk->setGenFuncS(GL_SPHERE_MAP);
    _texGenChunk->setGenFuncT(GL_SPHERE_MAP);
    
    _blendChunk = BlendChunk::create();

    _blendChunk->setSrcFactor (GL_SRC_ALPHA);
    _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
}

void FresnelMaterial::updateFresnel(void)
{
    if(getImage() == NULL)
        return;

    if(getImage()->getPixelFormat() != Image::OSG_RGB_PF &&
       getImage()->getPixelFormat() != Image::OSG_RGBA_PF)
    {
        FWARNING(("FresnelMaterial::updateFresnel : pixelformat(%u) not "
                  "supported\n", getImage()->getPixelFormat()));
        return;
    }

    if(_img->getPixelFormat() != getImage()->getPixelFormat() ||
       _img->getWidth()       != getImage()->getWidth      () ||
       _img->getHeight()      != getImage()->getHeight     ()  ) 
    {
        _img->set(Image::OSG_RGBA_PF, 
                  getImage()->getWidth(), 
                  getImage()->getHeight());
    }

    if(_textureObjChunk->getImage() != _img)
    {
        _textureObjChunk->setImage(_img);
    }

    // copy the image and calculate the alpha values.
    const UInt8 *src =  getImage()->getData ();
          UInt8 *dst = _img       ->editData();
    
   
    Real32 bias   =  getBias();
    Real32 offset =  getIndex();
    Real32 expo   =  getScale();
    Int32 width   = _img->getWidth();
    Int32 height  = _img->getHeight();
    Int32 bpp     =  getImage()->getBpp();
    Int32 ws      =  width / 2;
    Int32 hs      =  height / 2;

    for(Int32 y = -hs; y < hs; ++y)
    {
        for(Int32 x = -ws; x < ws; ++x)
        {
            Real32 xs = Real32(x) / Real32(width);
            Real32 ys = Real32(y) / Real32(height);
                
            Real32 a = osgPow(osgSqrt(xs * xs + ys * ys), expo) * bias + offset;
            UInt32 ac = (UInt32(a * 255.0f)) & 0xff;
            //ac = 255 - ac;
                
            UInt32 i = (x + ws) + ((y + hs) * width);
            
            UInt32 si = i * bpp;
            UInt32 di = i * 4;
                
            dst[di++] = src[si++]; // r
            dst[di++] = src[si++]; // g
            dst[di++] = src[si];   // b
            dst[di]   = ac;        // a
        }
    }

    _textureObjChunk->imageContentChanged();
}

/*----------------------------- class specific ----------------------------*/

void FresnelMaterial::changed(ConstFieldMaskArg whichField, 
                              UInt32            origin,
                              BitVector         detail    )
{
    prepareLocalChunks();

    if(whichField & ImageFieldMask)
    {
        if(getImage() != NULL)
        {
            _img->set(Image::OSG_RGBA_PF, 
                      getImage()->getWidth(), 
                      getImage()->getHeight());
            
            _textureObjChunk->setImage(_img);
        }
    }
    
    if((whichField & ImageFieldMask) ||
       (whichField & IndexFieldMask) ||
       (whichField & ScaleFieldMask) ||
       (whichField & BiasFieldMask))
    {
        updateFresnel();
    }
    
    Inherited::changed(whichField, origin, detail);
}

void FresnelMaterial::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump FresnelMaterial NI" << std::endl;
}

void FresnelMaterial::rebuildState(void)
{
    Color3f v3;
    Color4f v4;
    Real32  alpha = 1.f - getTransparency();

    Inherited::rebuildState();

    prepareLocalChunks();

    v3 = getAmbient();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setAmbient(v4);

    v3 = getDiffuse();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
    _materialChunk->setDiffuse(v4);
        
    v3 = getSpecular();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
    _materialChunk->setSpecular(v4);
        
    _materialChunk->setShininess(getShininess());
        
    v3 = getEmission();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
    _materialChunk->setEmission(v4);
        
    _materialChunk->setLit(getLit());
    _materialChunk->setColorMaterial(getColorMaterial());
    
    _pState->addChunk(_materialChunk  );
    _pState->addChunk(_textureObjChunk);
    _pState->addChunk(_textureEnvChunk);
    _pState->addChunk(_texGenChunk    );
    
    if(isTransparent())
    {
        _pState->addChunk(_blendChunk);
    }
}

bool FresnelMaterial::isTransparent(void) const
{
    return ((getTransparency() > Eps) || (Inherited::isTransparent()));
}


OSG_END_NAMESPACE

