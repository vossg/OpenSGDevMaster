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

#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

#include "OSGTextPixmapFace.h"
#include "OSGTextPixmapGlyph.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"

using namespace std;
OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Static Class Variable implementations:
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapGlyph TextPixmapFace::_emptyGlyph;


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFace::~TextPixmapFace(void)
{
    // Delete all glyphs in the glyph cache
    GlyphMap::iterator it;
    for (it = _glyphMap.begin(); it != _glyphMap.end(); ++it)
    {
        OSG_ASSERT(it->second != 0);
        delete it->second;
    }
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextGlyph &TextPixmapFace::getGlyph(TextGlyph::Index glyphIndex)
{
    return getPixmapGlyph(glyphIndex);
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextPixmapGlyph &TextPixmapFace::getPixmapGlyph(TextGlyph::Index glyphIndex)
{
    if (glyphIndex == TextGlyph::INVALID_INDEX)
        return _emptyGlyph;

    // Try to find the glyph in the map of glyphs
    GlyphMap::const_iterator it = _glyphMap.find(glyphIndex);
    if (it != _glyphMap.end())
    {
        OSG_ASSERT(it->second != 0);
        return *(it->second);
    }

    // We did not find the glyph, so we have to create it
    unique_ptr<TextPixmapGlyph> glyph = createGlyph(glyphIndex);

    // We could not create the glyph, return the empty glyph
    if (glyph.get() == 0)
        return _emptyGlyph;

    // Put the glyph into the glyph cache
    _glyphMap.insert(GlyphMap::value_type(glyphIndex, glyph.get()));

    // Return the glyph
    return *(glyph.release());
}


//----------------------------------------------------------------------
// Creates a texture image with the result of a layout operation
// Author: pdaehne
//----------------------------------------------------------------------
ImageTransitPtr TextPixmapFace::makeImage(const TextLayoutResult &layoutResult, Vec2f &offset, UInt32 border)
{
    Vec2f lowerLeft, upperRight;
    calculateBoundingBox(layoutResult, lowerLeft, upperRight);
    offset.setValues(lowerLeft.x() - border, upperRight.y() + border);

    ImageTransitPtr imagePtr = Image::create();

    UInt32 width  = static_cast<UInt32>(osgCeil(upperRight.x() - lowerLeft.x())) + (border << 1);
    UInt32 height = static_cast<UInt32>(osgCeil(upperRight.y() - lowerLeft.y())) + (border << 1);
    imagePtr->set(Image::OSG_A_PF, width, height);
    imagePtr->clear();
    UInt8 *buffer = imagePtr->editData();
    
    // Put the glyphs into the texture
    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for (i = 0; i < numGlyphs; ++i)
    {
        const TextPixmapGlyph &glyph = getPixmapGlyph(layoutResult.indices[i]);
        const Vec2f &pos = layoutResult.positions[i];
        Int32 x = static_cast<Int32>(pos.x() - lowerLeft.x() + 0.5f) + border;
        Int32 y = static_cast<Int32>(pos.y() - lowerLeft.y() + 0.5f) + border;
        glyph.putPixmap(x, y, buffer, width, height);
    }

    return imagePtr;
}


//----------------------------------------------------------------------
// Tries to create a pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFaceTransitPtr TextPixmapFace::create(
    const std::string &family, Style style, UInt32 size)
{
    return TextFaceFactory::the()->createPixmapFace(family, style, size);
}


OSG_END_NAMESPACE
