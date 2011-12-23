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

#include "OSGTextTXFFace.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"
#include "OSGTypedGeoIntegralProperty.h"

#include <fstream>

OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Static Class Variable implementations
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFGlyph TextTXFFace::_emptyGlyph;


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFace::~TextTXFFace()
{
    // Delete all glyphs in the glyph cache
    GlyphMap::iterator it;
    for (it = _glyphMap.begin(); it != _glyphMap.end(); ++it)
    {
        OSG_ASSERT(it->second != 0);
        delete it->second;
    }

    // Delete the texture
    _texture = NULL;
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextGlyph &TextTXFFace::getGlyph(TextGlyph::Index glyphIndex)
{
    return getTXFGlyph(glyphIndex);
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextTXFGlyph &TextTXFFace::getTXFGlyph(TextGlyph::Index glyphIndex)
{
    // Try to find the glyph in the map of glyphs
    GlyphMap::const_iterator it = _glyphMap.find(glyphIndex);
    if (it != _glyphMap.end())
    {
        OSG_ASSERT(it->second != 0);
        return *(it->second);
    }

    // We did not find the glyph in the map of glyphs,
    // so try to convert uppercase letters to lowercase
    // letters and vice versa
    if (glyphIndex > 255)
        glyphIndex = TextGlyph::INVALID_INDEX;
    else if (isupper(glyphIndex))
        glyphIndex = tolower(glyphIndex);
    else if (islower(glyphIndex))
        glyphIndex = toupper(glyphIndex);
    else
        glyphIndex = TextGlyph::INVALID_INDEX;
    it = _glyphMap.find(glyphIndex);
    if (it != _glyphMap.end())
    {
        OSG_ASSERT(it->second != 0);
        return *(it->second);
    }

    return _emptyGlyph;
}


//----------------------------------------------------------------------
// Fills a geometry with a new text
// Author: afischle, pdaehne
//----------------------------------------------------------------------
void TextTXFFace::fillGeo(Geometry *geoPtr, const TextLayoutResult &layoutResult, Real32 scale,
                          Vec2f offset, Color3f color)
{
    // cast the field containers down to the needed type and create them
    // when they have the wrong type
    GeoPnt3fProperty *posPtr = 
        dynamic_cast<GeoPnt3fProperty *>(geoPtr->getPositions());

    if (posPtr != NULL)
       posPtr->clear();

    // Clear out any existing data and then add to the geom
    GeoVec3fProperty *normalPtr = 
        dynamic_cast<GeoVec3fProperty *>(geoPtr->getNormals());

    if (normalPtr != NULL)
       normalPtr->clear();

    GeoVec2fProperty *texPtr = 
        dynamic_cast<GeoVec2fProperty *>(geoPtr->getTexCoords());

    if (texPtr != NULL)
       texPtr->clear();

    GeoColor3fProperty *colorPtr = 
        dynamic_cast<GeoColor3fProperty *>(geoPtr->getColors());

    if (NULL != colorPtr)
       colorPtr->clear();

    GeoUInt32Property *lensPtr = 
        dynamic_cast<GeoUInt32Property *>(geoPtr->getLengths());

    if (lensPtr != NULL)
       lensPtr->clear();

    GeoUInt8Property *typesPtr = 
        dynamic_cast<GeoUInt8Property *>(geoPtr->getTypes());

    if (typesPtr != NULL)
       typesPtr->clear();

    geoPtr->setIndices(NULL);
    geoPtr->setSecondaryColors(NULL);
    geoPtr->setTexCoords1(NULL);
    geoPtr->setTexCoords2(NULL);
    geoPtr->setTexCoords3(NULL);

    addToGeom(geoPtr,layoutResult,scale,offset,color);
}

void TextTXFFace::addToGeom(Geometry *geoPtr, const TextLayoutResult &layoutResult, Real32 scale,
                            Vec2f offset, Color3f color)
{
    // cast the field containers down to the needed type and create them
    // when they have the wrong type
    GeoPnt3fPropertyUnrecPtr posPtr = 
        dynamic_cast<GeoPnt3fProperty *>(geoPtr->getPositions());

    GeoVec3fPropertyUnrecPtr normalPtr = 
        dynamic_cast<GeoVec3fProperty *>(geoPtr->getNormals());

    GeoVec2fPropertyUnrecPtr texPtr = 
        dynamic_cast<GeoVec2fProperty *>(geoPtr->getTexCoords());

    GeoColor3fPropertyUnrecPtr colorPtr = 
        dynamic_cast<GeoColor3fProperty *>(geoPtr->getColors());

    GeoUInt32PropertyUnrecPtr lensPtr = 
        dynamic_cast<GeoUInt32Property *>(geoPtr->getLengths());

    GeoUInt8PropertyUnrecPtr typesPtr = 
        dynamic_cast<GeoUInt8Property *>(geoPtr->getTypes());

    // Create color buffer: If Null container AND color is set && we have not potentially added text before
    if ((colorPtr == NULL) && (color != OSG::Color3f(-1,-1,-1)) &&
        ((posPtr == NULL) && (texPtr == NULL)) )
    {
       colorPtr = GeoColor3fProperty::create();
       geoPtr->setColors(colorPtr);
    }
    bool use_colors(colorPtr != NULL);

    if (posPtr == NULL)
    {
        posPtr = GeoPnt3fProperty::create();
        geoPtr->setPositions(posPtr);
    }

    if (normalPtr == NULL)
    {
        normalPtr = GeoVec3fProperty::create();
        geoPtr->setNormals(normalPtr);
    }

    if (texPtr == NULL)
    {
        texPtr = GeoVec2fProperty::create();
        geoPtr->setTexCoords(texPtr);
    }

    if (lensPtr == NULL)
    {
        lensPtr = GeoUInt32Property::create();
        geoPtr->setLengths(lensPtr);
    }

    if (typesPtr == NULL)
    {
        typesPtr = GeoUInt8Property::create();
        geoPtr->setTypes(typesPtr);
    }

    UInt32 numGlyphs = layoutResult.getNumGlyphs();
    if (numGlyphs == 0)
    {
        return;
    }

    OSG::Vec3f normal(0.f, 0.f, 1.f);        // normal to use for each glyph

    typesPtr->push_back(GL_QUADS);
    unsigned num_glyphs_added(0);

    for (UInt32 i = 0; i < numGlyphs; ++i)
    {
        TextGlyph::Index glyphIndex = layoutResult.indices[i];
        const TextTXFGlyph &glyph = getTXFGlyph(glyphIndex);
        Real32 width = glyph.getWidth();
        Real32 height = glyph.getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;
        else
            num_glyphs_added += 1;

        // Calculate coordinates
        Vec2f pos = layoutResult.positions[i];
        Real32 posLeft = (pos.x() * scale) + offset.x();
        Real32 posTop = (pos.y() * scale) + offset.y();
        Real32 posRight = ((pos.x() + width) * scale) + offset.x();
        Real32 posBottom = ((pos.y() - height) * scale) + offset.y();

        // Calculate texture coordinates
        Real32 texCoordLeft = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop = glyph.getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        posPtr->push_back(Vec3f(posLeft, posBottom, 0.f));
        texPtr->push_back(Vec2f(texCoordLeft, texCoordBottom));
        normalPtr->push_back(normal);
        if(use_colors) colorPtr->push_back(color);

        // lower right corner
        posPtr->push_back(Vec3f(posRight, posBottom, 0.f));
        texPtr->push_back(Vec2f(texCoordRight, texCoordBottom));
        normalPtr->push_back(normal);
        if(use_colors) colorPtr->push_back(color);

        // upper right corner
        posPtr->push_back(Vec3f(posRight, posTop, 0.f));
        texPtr->push_back(Vec2f(texCoordRight, texCoordTop));
        normalPtr->push_back(normal);
        if(use_colors) colorPtr->push_back(color);

        // upper left corner
        posPtr->push_back(Vec3f(posLeft, posTop, 0.f));
        texPtr->push_back(Vec2f(texCoordLeft, texCoordTop));
        normalPtr->push_back(normal);
        if(use_colors) colorPtr->push_back(color);
    }
    lensPtr->push_back(num_glyphs_added*4);
}


//----------------------------------------------------------------------
// Creates a new text geometry
// Author: pdaehne
//----------------------------------------------------------------------
GeometryTransitPtr TextTXFFace::makeGeo(const TextLayoutResult &layoutResult, 
                                              Real32            scale,
                                              Vec2f             offset, 
                                              Color3f           color       )
{
    GeometryTransitPtr geo = Geometry::create();
    fillGeo(geo.get(), layoutResult, scale, offset, color);
    return geo;
}


//----------------------------------------------------------------------
// Creates a new node with a text geometry
// Author: pdaehne
//----------------------------------------------------------------------
NodeTransitPtr TextTXFFace::makeNode(const TextLayoutResult &layoutResult, Real32 scale,
                              Vec2f offset, Color3f color)
{
    GeometryTransitPtr geo = makeGeo(layoutResult, scale, offset, color);
    NodeTransitPtr node = Node::create();
    node->setCore(geo);
    return node;
}

// Render the text using the layout
void TextTXFFace::drawCharacters(const TextLayoutResult &layoutResult)
{
    glBegin(GL_QUADS);

    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    for(i = 0; i < numGlyphs; ++i)
    {
        const TextTXFGlyph &glyph = getTXFGlyph(layoutResult.indices[i]);
        Real32 width = glyph.getWidth();
        Real32 height = glyph.getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 posLeft   = pos.x();
        Real32 posTop    = pos.y();
        Real32 posRight  = pos.x() + width;
        Real32 posBottom = pos.y() - height;
        Real32 texCoordLeft   = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop    = glyph.getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight  = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex2f(posLeft, posBottom);

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex2f(posRight, posBottom);

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex2f(posRight, posTop);

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex2f(posLeft, posTop);
    }

    glEnd();
}



//----------------------------------------------------------------------
// Tries to create a TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextTXFFace::create(const string &family, Style style, const TextTXFParam &param)
{
    return TextFaceFactory::the()->createTXFFace(family, style, param);
}

//----------------------------------------------------------------------
// Reads a long value in network byte order from the input stream
// Author: pdaehne
//----------------------------------------------------------------------
static UInt32 readLong(istream &is, bool swap)
{
    UInt8 bytes[4];
    is.read(reinterpret_cast<istream::char_type *>(bytes), 4);
    return swap ?
        (bytes[3] << 24) |
        (bytes[2] << 16) |
        (bytes[1] << 8) |
        bytes[0]
                :
        (bytes[0] << 24) |
        (bytes[1] << 16) |
        (bytes[2] << 8) |
        bytes[3];
}


//----------------------------------------------------------------------
// Reads a short value in network byte order from the input stream
// Author: pdaehne
//----------------------------------------------------------------------
static UInt16 readShort(istream &is, bool swap)
{
    UInt8 bytes[2];
    is.read(reinterpret_cast<istream::char_type *>(bytes), 2);
    return swap ?
        (bytes[1] << 8) |
        bytes[0]
                :
        (bytes[0] << 8) |
        bytes[1];
}


//----------------------------------------------------------------------
// Reads a TXF face from an input stream
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextTXFFace::createFromStream(
    istream &is, const string &family, Style style)
{
    // Check the magic bytes
    istream::char_type magicBytes[4];
    is.read(magicBytes, 4);
    if ((is.good() == false) || (strncmp(magicBytes, "\xfftxf", 4) != 0))
        return TextTXFFaceTransitPtr();

    // Check endianess
    UInt32 endianness = readLong(is, false);
    bool swap;
    if (endianness == 0x12345678)
        swap = false;
    else if (endianness == 0x78563412)
        swap = true;
    else
        return TextTXFFaceTransitPtr();

    TextTXFFaceTransitPtr face(new TextTXFFace());
    face->_family = family;
    face->_style  = style;

    // Read header
    UInt32 format        = readLong(is, swap);
    UInt32 textureWidth  = readLong(is, swap);
    UInt32 textureHeight = readLong(is, swap);
    Int32  max_ascent    = readLong(is, swap);
    Int32  max_descent   = readLong(is, swap);
    if (max_descent < 0)
        max_descent = -max_descent;
    UInt32 num_glyphs = readLong(is, swap);
    if (is.good() == false)
    {
        return TextTXFFaceTransitPtr();
    }

    // Determine parameters
    face->_param.size         = max_ascent + max_descent;
    face->_param.gap          = 0; // There is no way to determine the gap
    face->_param.textureWidth = textureWidth;

    // Determine the scale factor
    face->_scale = 1.f / static_cast<Real32>(max_ascent + max_descent);

    // Determine ascent
    face->_horiAscent = static_cast<Real32>(max_ascent) * face->_scale;
    face->_vertAscent = -0.5f;

    // Determine descent
    face->_horiDescent = static_cast<Real32>(-max_descent) * face->_scale;
    face->_vertDescent = 0.5f;

    // Parse glyph information
    Int32 vertBearingY = -(max_ascent + max_descent) / 20;
    if (vertBearingY > -1)
        vertBearingY = -1;
    Real32 vertAdvanceOffset = static_cast<Real32>(vertBearingY) * 2.f * face->_scale;
    wstring characters;
    characters.reserve(num_glyphs);
    UInt32 i;
    for (i = 0; i < num_glyphs; ++i)
    {
        // Create the new glyph object
        TextTXFGlyph *glyph = new TextTXFGlyph();
        UInt16 glyphIndex = readShort(is, swap);
        characters.append(static_cast<wchar_t>(glyphIndex), 1);
        glyph->_glyphIndex = glyphIndex;
        glyph->_scale = face->_scale;
        glyph->_width = static_cast<unsigned char>(is.get());
        glyph->_height = static_cast<unsigned char>(is.get());
        glyph->_horiBearingX = static_cast<signed char>(is.get());
        glyph->_horiBearingY = 
            static_cast<signed char>(is.get()) + glyph->_height;
        glyph->_horiAdvance = 
            (static_cast<signed char>(is.get())) * face->_scale;
        is.ignore(); // padding
        glyph->_x = readShort(is, swap);
        glyph->_y = readShort(is, swap);

        // There is no vertical layout information in a TXF file,
        // therefore we have to guess reasonable values
        glyph->_vertBearingX = -static_cast<Int32>(glyph->_width >> 1);
        if (glyphIndex == 32)
        {
            glyph->_vertBearingY = -glyph->_horiBearingX;
            glyph->_vertAdvance = -glyph->_horiAdvance;
        }
        else
        {
            glyph->_vertBearingY = vertBearingY;
            glyph->_vertAdvance = -static_cast<Real32>(glyph->_height) * face->_scale + vertAdvanceOffset;
        }

        glyph->calculateCoordinates(textureWidth, textureHeight);
        face->_glyphMap[glyphIndex] = glyph;

        if (is.good() == false)
        {
            return TextTXFFaceTransitPtr();
        }
    }
    face->_param.setCharacters(characters);

    // Create the texture
    face->_texture = Image::create();

    face->_texture->set(Image::OSG_A_PF, textureWidth, textureHeight);
    face->_texture->clear();

    // Parse texture
    switch (format)
    {
        case 0: // TXF_FORMAT_BYTE
            {
                UInt32 size = textureWidth * textureHeight;
                OSG_ASSERT(face->_texture->getSize() == size);
                is.read(
                    reinterpret_cast<
                        istream::char_type *>(face->_texture->editData()), 
                    size);

                if (is.good() == false)
                {
                    return TextTXFFaceTransitPtr();
                }
            }
            break;
        case 1: // TXF_FORMAT_BITMAP
            {
                UInt32 stride = (textureWidth + 7) >> 3;
                UInt32 size = stride * textureHeight;
                UInt8 *buffer = new UInt8[size];
                is.read(reinterpret_cast<istream::char_type *>(buffer), size);
                if (is.good() == false)
                {
                    delete [] buffer;

                    return TextTXFFaceTransitPtr();
                }
                OSG_ASSERT(face->_texture->getSize() == textureWidth * textureHeight);
                UInt8 *dst = face->_texture->editData();
                UInt32 x, y;
                for (y = 0; y < textureHeight; ++y)
                    for (x = 0; x < textureWidth; ++x)
                        dst[y * textureWidth + x] = buffer[y * stride + (x >> 3)] & (1 << (x & 7)) ? 255 : 0;
                delete [] buffer;

            }
            break;
        default:
            return TextTXFFaceTransitPtr();
    }

    return face;
}


//----------------------------------------------------------------------
// Reads a TXF face from a file
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextTXFFace::createFromFile(const string &filename)
{
    // Open the file
    ifstream is(filename.c_str(), ios_base::in | ios_base::binary);
    if (is.good() == false)
        return TextTXFFaceTransitPtr();

    // Remove the directory and the suffix from the filename and use the
    // remaining filename as the family name
    string::size_type pos = filename.find_last_of("/\\");
    string family = pos != string::npos ? filename.substr(pos + 1) : filename;
    pos = family.rfind('.');
    if (pos != string::npos)
        family.erase(pos);

    // Parse the file
    TextTXFFaceTransitPtr face = createFromStream(is, family);
    
    return face;
}


//----------------------------------------------------------------------
// Writes a long value in network byte order to the output stream
// Author: pdaehne
//----------------------------------------------------------------------
static void writeLong(ostream &os, UInt32 value)
{
    UInt8 bytes[4];
    bytes[0] = static_cast<UInt8>((value >> 24) & 0xff);
    bytes[1] = static_cast<UInt8>((value >> 16) & 0xff);
    bytes[2] = static_cast<UInt8>((value >> 8) & 0xff);
    bytes[3] = static_cast<UInt8>(value & 0xff);
    os.write(reinterpret_cast<ostream::char_type*>(bytes), 4);
}


//----------------------------------------------------------------------
// Writes a short value in network byte order to the output stream
// Author: pdaehne
//----------------------------------------------------------------------
static void writeShort(ostream &os, UInt16 value)
{
    UInt8 bytes[2];
    bytes[0] = static_cast<UInt8>((value >> 8) & 0xff);
    bytes[1] = static_cast<UInt8>(value & 0xff);
    os.write(reinterpret_cast<ostream::char_type*>(bytes), 2);
}


//----------------------------------------------------------------------
// Writes a TXF face to an output stream
// Author: pdaehne
//----------------------------------------------------------------------
bool TextTXFFace::writeToStream(ostream &os) const
{
    // Write the magic bytes
    const ostream::char_type *magicBytes = "\xfftxf";
    os.write(magicBytes, 4);

    // Write the header
    OSG_ASSERT(_texture != NULL);
    writeLong(os, 0x12345678); // endianness
    writeLong(os, 0); // format
    writeLong(os, _texture->getWidth());
    writeLong(os, _texture->getHeight());
    writeLong(os, static_cast<UInt32>(_horiAscent / _scale));
    writeLong(os, static_cast<UInt32>(_horiDescent / _scale));
    writeLong(os, UInt32(_glyphMap.size()));
    if (os.good() == false)
        return false;

    // Write glyph information
    GlyphMap::const_iterator it;
    for (it = _glyphMap.begin(); it != _glyphMap.end(); ++it)
    {
        OSG_ASSERT(it->second != 0);
        writeShort(os, static_cast<UInt16>(it->second->getGlyphIndex()));
        os.put(it->second->getPixmapWidth());
        os.put(it->second->getPixmapHeight());
        os.put(it->second->getPixmapHoriBearingX());
        os.put(it->second->getPixmapHoriBearingY() - it->second->getPixmapHeight());
        os.put(static_cast<ostream::char_type>(it->second->getHoriAdvance() / _scale));
        os.put(0); // padding
        writeShort(os, it->second->getX());
        writeShort(os, it->second->getY());
        if (os.good() == false)
            return false;
    }

    // Write texture
    OSG_ASSERT(_texture->getSize() == static_cast<UInt32>(_texture->getWidth() * _texture->getHeight()));
    os.write(reinterpret_cast<const ostream::char_type*>(_texture->getData()), 
             _texture->getWidth() * _texture->getHeight());

    return os.good();
}


//----------------------------------------------------------------------
// Writes a TXF face to a file
// Author: pdaehne
//----------------------------------------------------------------------
bool TextTXFFace::writeToFile(const string &filename) const
{
    ofstream os(filename.c_str(), ios_base::out | ios_base::trunc | ios_base::binary);
    if (os.good() == false)
        return false;
    return writeToStream(os);
}


//----------------------------------------------------------------------
// Lays out one line of text.
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFFace::layout(const string &utf8Text,
                         const TextLayoutParam &param,
                         TextLayoutResult &result)
{
    TextFace::layout(utf8Text, param, result);
}


//----------------------------------------------------------------------
// Lays out one line of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFFace::layout(const wstring &text,
                         const TextLayoutParam &param,
                         TextLayoutResult &result)
{
    // Initialize return values
    result.clear();

    // Do the layout depending on the direction
    Vec2f currPos;
    size_t i, len = text.length();
    result.indices.reserve(len);
    result.positions.reserve(len);
    vector<UInt32> spaceIndices;
    bool justify = param.getLength(0) > 0.f;
    for (i = 0; i < len; ++i)
    {
        // Get glyph
        const TextGlyph &glyph = getGlyph(text[i]);
        if ((justify == true) && (text[i] == ' '))
            spaceIndices.push_back(UInt32(result.indices.size()));

        // Calculate position
        Vec2f pos;
        if (param.horizontal == true)
        {
            if (param.leftToRight == true)
            {
                pos = currPos;
                pos[0] += glyph.getHoriBearingX();
                pos[1] += glyph.getHoriBearingY();
                currPos[0] += glyph.getHoriAdvance();
            }
            else // leftToRight == false
            {
                currPos[0] -= glyph.getHoriAdvance();
                pos = currPos;
                pos[0] += glyph.getHoriBearingX();
                pos[1] += glyph.getHoriBearingY();
            }
        }
        else // horizontal == false
        {
            if (param.topToBottom == true)
            {
                pos = currPos;
                pos[0] += glyph.getVertBearingX();
                pos[1] += glyph.getVertBearingY();
                currPos[1] += glyph.getVertAdvance();
            }
            else // topToBottom == false
            {
                currPos[1] -= glyph.getVertAdvance();
                pos = currPos;
                pos[0] += glyph.getVertBearingX();
                pos[1] += glyph.getVertBearingY();
            }
        }

        result.indices.push_back(glyph.getGlyphIndex());
        result.positions.push_back(pos);
    }

    // Justify the line
    if (justify == true)
        justifyLine(param, spaceIndices, currPos, result);

    // Adjust the origin depending on the major and the minor alignment
    adjustLineOrigin(param, currPos, result);

    // Determine text bounds / line bounds
    if (param.horizontal == true)
        result.textBounds.setValues(osgAbs(currPos.x()), _horiAscent - _horiDescent);
    else
        result.textBounds.setValues(_vertDescent - _vertAscent, osgAbs(currPos.y()));
    result.lineBounds.push_back(result.textBounds);
}


//----------------------------------------------------------------------
// Lays out multiple lines of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFFace::layout(const vector<string> &lines,
                         const TextLayoutParam &param,
                         TextLayoutResult &result)
{
    TextFace::layout(lines, param, result);
}


//----------------------------------------------------------------------
// Lays out multiple lines of text
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFFace::layout(const vector<wstring> &lines,
                         const TextLayoutParam &param,
                         TextLayoutResult &result)
{
    TextFace::layout(lines, param, result);
}


//----------------------------------------------------------------------
// Calculates the positions of the glyphs on the texture
// Author: pdaehne
//----------------------------------------------------------------------
void TextTXFFace::prepareTexture(const TextTXFParam &param)
{
    // Sort characters by height and calculate the area necessary
    // to keep all characters
    typedef multimap<UInt32, TextTXFGlyph*, greater<UInt32> > HeightMap;
    HeightMap heightMap;
    UInt32 area = 0, maxWidth = 0;
    GlyphMap::iterator gmIt;
    for (gmIt = _glyphMap.begin(); gmIt != _glyphMap.end(); ++gmIt)
    {
        TextTXFGlyph *glyph = gmIt->second;
        heightMap.insert(HeightMap::value_type(glyph->getPixmapHeight(), glyph));
        if (maxWidth < glyph->getPixmapWidth())
            maxWidth = glyph->getPixmapWidth();
        area += (glyph->getPixmapWidth() + param.gap) * (glyph->getPixmapHeight() + param.gap);
    }

    UInt32 textureSize;
    if (param.textureWidth == 0)
    {
        // Try to make a good guess about the optimal width of the texture
        textureSize = static_cast<UInt32>(ceil(sqrt(static_cast<Real32>(area))));
    }
    else
        textureSize = param.textureWidth;
    maxWidth += param.gap << 1;
    if (textureSize < maxWidth)
        textureSize = maxWidth;
    UInt32 textureWidth = osgNextPower2(textureSize);

    // Calculate the positions of the glyphs in the texture
    HeightMap::iterator hmIt = heightMap.begin();
    UInt32 xpos = param.gap, ypos = param.gap, heightOfRow = 0;
    while (hmIt != heightMap.end())
    {
        HeightMap::iterator hmIt3;
        // Does the next glyph fit into the line?
        if (xpos + hmIt->second->getPixmapWidth() + param.gap > textureWidth)
        {
            // No, so lets try to find another glyph
            HeightMap::iterator hmIt2 = hmIt;
            for (++hmIt2; hmIt2 != heightMap.end(); ++hmIt2)
            {
                if (xpos + hmIt2->second->getPixmapWidth() + param.gap <= textureWidth)
                    break;
            }
            if (hmIt2 == heightMap.end())
            {
                // There is no other glyph
                xpos = param.gap;
                ypos += heightOfRow + param.gap;
                heightOfRow = 0;
                hmIt3 = hmIt;
                ++hmIt;
            }
            else // There is another glyph that fits
                hmIt3 = hmIt2;
        }
        else
        {
            // Yes, the glyph fits into the line
            hmIt3 = hmIt;
            ++hmIt;
        }
        hmIt3->second->_x = xpos;
        hmIt3->second->_y = ypos;
        xpos += hmIt3->second->getPixmapWidth() + param.gap;
        if (hmIt3->second->getPixmapHeight() > heightOfRow)
            heightOfRow = hmIt3->second->getPixmapHeight();
        heightMap.erase(hmIt3);
    }
    ypos += heightOfRow;

    // Calculate the height of the texture
    UInt32 textureHeight = osgNextPower2(static_cast<UInt32>(ypos));

    // Create the texture
    _texture = Image::create();

    _texture->set(Image::OSG_A_PF, textureWidth, textureHeight);
    _texture->clear();

    // Calculate the coordinates of all glyphs
    for (gmIt = _glyphMap.begin(); gmIt != _glyphMap.end(); ++gmIt)
        gmIt->second->calculateCoordinates(textureWidth, textureHeight);
}


OSG_END_NAMESPACE
