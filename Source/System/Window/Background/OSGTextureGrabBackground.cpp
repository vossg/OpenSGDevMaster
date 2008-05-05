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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>

#include <OSGViewport.h>
#include <OSGImage.h>
#include <OSGTextureObjChunk.h>
#include <OSGDrawEnv.h>

#include "OSGTextureGrabBackground.h"

OSG_USING_NAMESPACE

// Documentation for this class is emited in the
// OSGTextureGrabBackgroundBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureGrabBackground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureGrabBackground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureGrabBackground::TextureGrabBackground(void) :
    Inherited()
{
}

TextureGrabBackground::TextureGrabBackground(
    const TextureGrabBackground &source) :

    Inherited(source)
{
}

TextureGrabBackground::~TextureGrabBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureGrabBackground::changed(ConstFieldMaskArg whichField, 
                                    UInt32            origin,
                                    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------- your_category---------------------------------*/

void TextureGrabBackground::clear(DrawEnv *pEnv)
{   
    // grab the texture
    TextureObjChunk *t = getTexture();
    
    if(t == NULL)       // No texture, no grab.
    {
        Inherited::clear(pEnv);
        return;
    }
    
    Int32  pw = pEnv->getPixelWidth ();
    Int32  ph = pEnv->getPixelHeight();
    
    // Ignore empty viewports
    if(pw < 1 || ph < 1)
        return;
 
    Image *i = t->getImage();
             
    // If image is smaller than 2x2, resize it to vp size
    // the 2x2 is because you can't create 0x0 images
    if((i->getWidth() <= 1 && i->getHeight() <= 1) ||
       (getAutoResize() && (osgAbs(i->getWidth()  - pw) > 1 ||
                            osgAbs(i->getHeight() - ph) > 1 ) ) )
    {
        i->set(i->getPixelFormat(), pw, ph);
    }
    
    UInt32 w = osgMin((Int32)i->getWidth(),  pw);
    UInt32 h = osgMin((Int32)i->getHeight(), ph);

    glErr("TextureGrabBackground::activate precheck");
    
    pEnv->getWindow()->validateGLObject(t->getGLId(), pEnv);

    glErr("TextureGrabBackground::bind precheck");
    
    GLenum bindTarget = getBindTarget(), copyTarget = getCopyTarget();
    
    if(bindTarget == GL_NONE)
    {
        if(i->getDepth() > 1)
        {
            FWARNING(("TextureGrabBackground:: 3D textures not "
                      "supported for this window!\n"));
            Inherited::clear(pEnv);
            return;
        }
        else if(h > 1) 
        {
            bindTarget = GL_TEXTURE_2D;
        }
        else
        {
            bindTarget = GL_TEXTURE_1D;        
        }
    }
    
    if(copyTarget == GL_NONE)
        copyTarget = bindTarget;
    
    glBindTexture(bindTarget,
                  pEnv->getWindow()->getGLObjectId(t->getGLId()));

    glErr("TextureGrabBackground::copy precheck");

    if(copyTarget == GL_TEXTURE_3D)
    {
        FWARNING(("TextureGrabBackground:: grabbing to 3D textures not "
                  "supported yet!\n"));      
    }
    else if(copyTarget == GL_TEXTURE_1D)
    {
        glCopyTexSubImage1D(copyTarget, 0, 0, 
                            pEnv->getPixelLeft(), pEnv->getPixelBottom(), 
                            w);
    }
    else
    {
        glCopyTexSubImage2D(copyTarget, 0, 0, 0, 
                            pEnv->getPixelLeft(), pEnv->getPixelBottom(), 
                            w, h);
    }
    
    glErr("TextureGrabBackground::copy postcheck");
   
    glBindTexture(bindTarget, 0);
   
    // now do the clearing
    Inherited::clear(pEnv);
}

/*------------------------------- dump ----------------------------------*/

void TextureGrabBackground::dump(      UInt32    , 
                                 const BitVector ) const
{
    SLOG << "Dump TextureGrabBackground NI" << std::endl;
}
