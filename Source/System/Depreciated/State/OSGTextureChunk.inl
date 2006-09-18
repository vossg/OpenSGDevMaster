/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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


OSG_BEGIN_NAMESPACE

/*! Utility function to be called whenever the contents of the image change. 
    Forces efficient update of the texture. Should not be called when the 
    size of the texture changes, in that case setImage() should be called to 
    renew the texture.
*/

inline 
void TextureChunk::imageContentChanged(Int32 minx, Int32 maxx, 
                                       Int32 miny, Int32 maxy,
                                       Int32 minz, Int32 maxz)
{
    setDirtyMinX(minx);
    setDirtyMaxX(maxx);
    setDirtyMinY(miny);
    setDirtyMaxY(maxy);
    setDirtyMinZ(minz);
    setDirtyMaxZ(maxz);
}


inline 
bool TextureChunk::hasMultiTexture(Window *win)
{
    return win->hasExtension(_arbMultiTex);
}

//! call glActiveTexture via the extension mechanism
inline 
void TextureChunk::activeTexture(Window *win, UInt16 texture)
{
    void (OSG_APIENTRY *ActiveTexture)(GLenum target) = 
        (void (OSG_APIENTRY*)(GLenum target))
            win->getFunction(_funcActiveTexture);

    ActiveTexture(GL_TEXTURE0_ARB + texture);
}

//! call glActiveTexture via the extension mechanism, if MultiTextures
//! are supported. Return false if successful, true if not.
inline 
bool TextureChunk::activateTexture(Window *win, UInt16 texture)
{
    if(hasMultiTexture(win))
    {
        activeTexture(win, texture);
    }
#ifdef OSG_DEBUG
    else
    {
        if(texture != 0)
        {
            FWARNING(("TextureChunk::activateTexture: trying to activate "
                "texture %d, but Window %p doesn't support multi-textures!\n",
                texture, win));
            return true;
        }
    }
#endif
    return false;
}

inline
void TextureChunk::setShaderOffsetMatrix(Real32 m11, Real32 m12, 
                                         Real32 m21, Real32 m22)
{
    editShaderOffsetMatrix().resize(4);

    editShaderOffsetMatrix()[0] = m11;
    editShaderOffsetMatrix()[1] = m12;
    editShaderOffsetMatrix()[2] = m21;
    editShaderOffsetMatrix()[3] = m22;
}


OSG_END_NAMESPACE

#define OSGTEXTURECHUNK_INLINE_CVSID "@(#)$Id$"

