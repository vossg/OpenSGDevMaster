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


#ifdef __sgi
# include <cassert>
#else
# include <cassert>
#endif


OSG_BEGIN_NAMESPACE


inline UInt32 TextTXFGlyph::getX() const { return _x; }


inline UInt32 TextTXFGlyph::getY() const { return _y; }


inline UInt32 TextTXFGlyph::getPixmapWidth() const { return _width; }


inline UInt32 TextTXFGlyph::getPixmapHeight() const { return _height; }


inline Int32 TextTXFGlyph::getPixmapHoriBearingX() const { return _horiBearingX; }


inline Int32 TextTXFGlyph::getPixmapHoriBearingY() const { return _horiBearingY; }


inline Int32 TextTXFGlyph::getPixmapVertBearingX() const { return _vertBearingX; }


inline Int32 TextTXFGlyph::getPixmapVertBearingY() const { return _vertBearingY; }


inline Real32 TextTXFGlyph::getScale() const { return _scale; }


inline Real32 TextTXFGlyph::getTexCoord(UInt32 index) const
{
    assert(index < 4);
    return _texCoord[index];
}


OSG_END_NAMESPACE

