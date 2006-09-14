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


OSG_BEGIN_NAMESPACE


inline UInt32 TextPixmapGlyph::getPixmapWidth() const { return _width; }


inline UInt32 TextPixmapGlyph::getPixmapPitch() const { return _pitch; }


inline UInt32 TextPixmapGlyph::getPixmapHeight() const { return _height; }


#if 0
inline Int32 TextPixmapGlyph::getPixmapHoriBearingX() const { return _horiBearingX; }


inline Int32 TextPixmapGlyph::getPixmapHoriBearingY() const { return _horiBearingY; }


inline Int32 TextPixmapGlyph::getPixmapVertBearingX() const { return _vertBearingX; }


inline Int32 TextPixmapGlyph::getPixmapVertBearingY() const { return _vertBearingY; }
#endif

inline const UInt8 *TextPixmapGlyph::getPixmap() const { return _pixmap; }


inline TextPixmapGlyph::TextPixmapGlyph()
: TextGlyph(), _width(0), _pitch(0), _height(0), _horiBearingX(0), _horiBearingY(0), _vertBearingX(0), _vertBearingY(0), _pixmap(0)
{}


OSG_END_NAMESPACE


#define OSGTEXTPIXMAPGLYPH_INLINE_CVSID "@(#)$Id$"
