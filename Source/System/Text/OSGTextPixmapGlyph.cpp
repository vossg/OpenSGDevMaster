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

#include "OSGTextPixmapGlyph.h"


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapGlyph::~TextPixmapGlyph()
{ delete [] _pixmap; }


//----------------------------------------------------------------------
// Returns the width of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getWidth() const
{ return static_cast<Real32>(_width); }


//----------------------------------------------------------------------
// Returns the height of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getHeight() const
{ return static_cast<Real32>(_height); }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getHoriBearingX() const
{ return static_cast<Real32>(_horiBearingX); }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getHoriBearingY() const
{ return static_cast<Real32>(_horiBearingY); }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getVertBearingX() const
{ return static_cast<Real32>(_vertBearingX); }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextPixmapGlyph::getVertBearingY() const
{ return static_cast<Real32>(_vertBearingY); }


//----------------------------------------------------------------------
// Copies the glyph pixmap into a texture
// Author: pdaehne
//----------------------------------------------------------------------
void TextPixmapGlyph::putPixmap(Int32 x, Int32 y, UInt8 *tex,
                                UInt32 width, UInt32 height) const
{
    if (_pixmap != 0)
    {
        // Clip the glyph at the left border of the texture
        int left = 0;
        int glyphWidth = _width;
        int src = 0;
        int dst = 0;
        int delta = x;
        if (delta < left)
        {
            delta = left - delta;
            src += delta;
            glyphWidth -= delta;
            delta = left;
        }
        dst += delta;

        // Clip the glyph at the right border of the texture
        int right = width;
        delta = right - dst;
        if (delta < glyphWidth)
            glyphWidth =  delta;

        // Clip the glyph at the bottom border of the texture
        int bottom  = 0;
        int glyphHeight = _height;
        delta = y - _height;
        if (delta < bottom)
        {
            delta = bottom - delta;
            src += delta * _pitch;
            glyphHeight -= delta;
            delta = bottom;
        }
        dst += delta * width;

        // Clip the glyph at the top border of the texture
        int top = height;
        delta = top - y /*- _horiBearingY*/;
        if (delta < 0)
            glyphHeight += delta;

        int xi, yi;
        for (yi = glyphHeight; yi > 0; --yi)
        {
            unsigned char *srcPtr = &(_pixmap[src]);
            unsigned char *dstPtr = &(tex[dst]);
            for (xi = glyphWidth; xi > 0; --xi)
            {
                unsigned char p = 255 - ((255 - *dstPtr) * (255 - *srcPtr) / 255);
                *dstPtr++ = p;
                srcPtr++;
            }
            src += _pitch;
            dst += width;
        }
    }
}


//----------------------------------------------------------------------
// Flips the glyph pixmap around the x axis
// Author: pdaehne
//----------------------------------------------------------------------
void TextPixmapGlyph::flipPixmap()
{
    if (_pixmap == 0)
        return;
    unsigned char *ptr1 = _pixmap;
    unsigned char *ptr2 = _pixmap + _pitch * (_height - 1);
    unsigned int x, y;
    for (y = _height >> 1; y > 0; --y)
    {
        for (x = 0; x < _width; ++x)
        {
            unsigned char h = ptr1[x];
            ptr1[x] = ptr2[x];
            ptr2[x] = h;
        }
        ptr1 += _pitch;
        ptr2 -= _pitch;
    }
}


OSG_END_NAMESPACE


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
    static OSG::Char8 cvsid_cpp[] = "@(#)$Id$";
    static OSG::Char8 cvsid_hpp[] = OSGTEXTPIXMAPGLYPH_HEADER_CVSID;
    static OSG::Char8 cvsid_inl[] = OSGTEXTPIXMAPGLYPH_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
