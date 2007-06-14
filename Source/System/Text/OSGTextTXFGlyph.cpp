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

#include "OSGTextTXFGlyph.h"


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFGlyph::TextTXFGlyph()
: TextGlyph(), _width(0), _height(0), _horiBearingX(0), _horiBearingY(0),
  _vertBearingX(0), _vertBearingY(0), _x(0), _y(0), _scale(1.f), _texCoord()
{
    _texCoord[COORD_LEFT] = _texCoord[COORD_BOTTOM] =
    _texCoord[COORD_RIGHT] = _texCoord[COORD_TOP] = 0.f;
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFGlyph::~TextTXFGlyph() {}


//----------------------------------------------------------------------
// Returns the width of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getWidth() const
{ return static_cast<Real32>(_width) * _scale; }


//----------------------------------------------------------------------
// Returns the height of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getHeight() const
{ return static_cast<Real32>(_height) * _scale; }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getHoriBearingX() const
{ return static_cast<Real32>(_horiBearingX) * _scale; }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getHoriBearingY() const
{ return static_cast<Real32>(_horiBearingY) * _scale; }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getVertBearingX() const
{ return static_cast<Real32>(_vertBearingX) * _scale; }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextTXFGlyph::getVertBearingY() const
{ return static_cast<Real32>(_vertBearingY) * _scale; }


//----------------------------------------------------------------------
// Calculates coordinates
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFGlyph::calculateCoordinates(UInt32 textureWidth,
                                            UInt32 textureHeight)
{
    Real32 w = static_cast<Real32>(textureWidth);
    Real32 h = static_cast<Real32>(textureHeight);
    _texCoord[TextTXFGlyph::COORD_LEFT] = _x / w;
    _texCoord[TextTXFGlyph::COORD_BOTTOM] = _y / h;
    _texCoord[TextTXFGlyph::COORD_RIGHT] = (_x + _width) / w;
    _texCoord[TextTXFGlyph::COORD_TOP] = (_y + _height) / h;
}


OSG_END_NAMESPACE
