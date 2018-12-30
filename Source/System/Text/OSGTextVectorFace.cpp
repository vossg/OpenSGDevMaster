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

#include "OSGTextVectorFace.h"
#include "OSGTextVectorGlyph.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Static Class Variable implementations:
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorGlyph TextVectorFace::_emptyGlyph;


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFace::~TextVectorFace(void)
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
const TextGlyph &TextVectorFace::getGlyph(TextGlyph::Index glyphIndex)
{
    return getVectorGlyph(glyphIndex);
}


//----------------------------------------------------------------------
// Returns information about a glyph.
// Author: pdaehne
//----------------------------------------------------------------------
const TextVectorGlyph &TextVectorFace::getVectorGlyph(TextGlyph::Index glyphIndex)
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
    unique_ptr<TextVectorGlyph> glyph = createGlyph(glyphIndex);

    // We could not create the glyph, return 0
    if (glyph.get() == 0)
        return _emptyGlyph;

    // Put the glyph into the glyph cache
    _glyphMap.insert(GlyphMap::value_type(glyphIndex, glyph.get()));

    // Return the glyph
    return *(glyph.release());
}


//----------------------------------------------------------------------
// Fills a geometry with a new text
// Author: afischle, pdaehne
//----------------------------------------------------------------------
void TextVectorFace::fillGeo(Geometry *geoPtr, const TextLayoutResult &layoutResult,
                             Real32 scale, Real32 depth, UInt32 level,
                             Real32 creaseAngle)
{
    // cast the field containers down to the needed type and create them
    // when they have the wrong type
    GeoPnt3fPropertyUnrecPtr posPtr = 
        dynamic_cast<GeoPnt3fProperty *>(geoPtr->getPositions());

    if (posPtr == NULL)
    {
        posPtr = GeoPnt3fProperty::create();
        geoPtr->setPositions(posPtr);
    }
    else
        posPtr->clear();
    GeoVec3fPropertyUnrecPtr normalsPtr = 
        dynamic_cast<GeoVec3fProperty *>(geoPtr->getNormals());

    if (normalsPtr == NULL)
    {
        normalsPtr = GeoVec3fProperty::create();
        geoPtr->setNormals(normalsPtr);
    }
    else
        normalsPtr->clear();

    GeoVec2fPropertyUnrecPtr texPtr = 
        dynamic_cast<GeoVec2fProperty *>(geoPtr->getTexCoords());

    if (texPtr == NULL)
    {
        texPtr = GeoVec2fProperty::create();
        geoPtr->setTexCoords(texPtr);
    }
    else
        texPtr->clear();

    GeoUInt32PropertyUnrecPtr lensPtr = 
        dynamic_cast<GeoUInt32Property *>(geoPtr->getLengths());

    if (lensPtr == NULL)
    {
        lensPtr = GeoUInt32Property::create();
        geoPtr->setLengths(lensPtr);
    }
    else
        lensPtr->clear();

    GeoUInt32PropertyUnrecPtr posIndicesPtr = 
        dynamic_cast<GeoUInt32Property *>(
            geoPtr->getIndex(Geometry::PositionsIndex));

    if (posIndicesPtr == NULL)
    {
        posIndicesPtr = GeoUInt32Property::create();
        geoPtr->setIndex(posIndicesPtr, Geometry::PositionsIndex);
    }
    else
        posIndicesPtr->clear();

    GeoUInt32PropertyUnrecPtr normalIndicesPtr = 
        dynamic_cast<GeoUInt32Property *>(
            geoPtr->getIndex(Geometry::NormalsIndex));

    if (normalIndicesPtr == NULL)
    {
        normalIndicesPtr = GeoUInt32Property::create();
        geoPtr->setIndex(normalIndicesPtr, Geometry::NormalsIndex);
    }
    else
        normalIndicesPtr->clear();

    GeoUInt32PropertyUnrecPtr texCoordIndicesPtr = 
        dynamic_cast<GeoUInt32Property *>(
            geoPtr->getIndex(Geometry::TexCoordsIndex));

    if (texCoordIndicesPtr == NULL)
    {
        texCoordIndicesPtr = GeoUInt32Property::create();
        geoPtr->setIndex(texCoordIndicesPtr, Geometry::TexCoordsIndex);
    }
    else
        texCoordIndicesPtr->clear();

    GeoUInt8PropertyUnrecPtr typesPtr = 
        dynamic_cast<GeoUInt8Property *>(geoPtr->getTypes());

    if (typesPtr == NULL)
    {
        typesPtr = GeoUInt8Property::create();
        geoPtr->setTypes(typesPtr);
    }
    else
        typesPtr->clear();

    geoPtr->setColors(NULL);
    geoPtr->setSecondaryColors(NULL);
    geoPtr->setTexCoords1(NULL);
    geoPtr->setTexCoords2(NULL);
    geoPtr->setTexCoords3(NULL);

    UInt32 numGlyphs = layoutResult.getNumGlyphs();
    if (numGlyphs == 0)
    {
        return;
    }

    // the interleaved multi-index blocks have the layout
    // Position | Normal | TexCoord
/*
    geoPtr->getIndexMapping().push_back(Geometry::MapPosition);
    geoPtr->getIndexMapping().push_back(Geometry::MapNormal);
    geoPtr->getIndexMapping().push_back(Geometry::MapTexCoords);
 */

    // store the normal for the front face
    normalsPtr->push_back(Vec3f(0.f, 0.f, 1.f));
    if (depth > 0.f)
        // store the normal for the back face
        normalsPtr->push_back(Vec3f(0.f, 0.f, -1.f));

    UInt32 i;
    for (i = 0; i < numGlyphs; ++i)
    {
        const TextVectorGlyph &glyph = getVectorGlyph(layoutResult.indices[i]);
        const TextVectorGlyph::PolygonOutline &outline = glyph.getLines(level);
        const Vec2f &pos = layoutResult.positions[i];

        // add the front face to the geometry

        // store positions and texture coordinates
        UInt32 coordOffset = posPtr->size32();
        UInt32 texCoordOffset = texPtr->size32();
        Real32 coordZ = 0.5f * depth;
        vector<Vec2f>::const_iterator cIt;
        for (cIt = outline.coords.begin(); cIt != outline.coords.end(); ++cIt)
        {
            Vec2f coord = *cIt + pos;
            Vec2f texCoord = coord;
            coord *= scale;
            posPtr->push_back(Vec3f(coord.x(), coord.y(), coordZ));
            texCoord -= layoutResult.positions.front();
            texPtr->push_back(texCoord);
        }

        // Store types, lengths and indices
        vector<TextVectorGlyph::PolygonOutline::TypeIndex>::const_iterator tIt;
        UInt32 indexBegin = 0, indexEnd;
        for (tIt = outline.types.begin(); tIt != outline.types.end(); ++tIt)
        {
            typesPtr->push_back(tIt->first);
            indexEnd = tIt->second;
            OSG_ASSERT(indexEnd >= indexBegin);
            lensPtr->push_back(indexEnd - indexBegin);
            UInt32 j;
            for (j = indexBegin; j < indexEnd; ++j)
            {
                // the interleaved multi-index blocks have the layout
                // Position | Normal | TexCoord
                OSG_ASSERT(j < outline.indices.size());
                UInt32 index = outline.indices[j];
                OSG_ASSERT(coordOffset + index < posPtr->size());
                posIndicesPtr->push_back(coordOffset + index);
                normalIndicesPtr->push_back(0);
                OSG_ASSERT(texCoordOffset + index < texPtr->size());
                texCoordIndicesPtr->push_back(texCoordOffset + index);
            }
            indexBegin = indexEnd;
        }

        // add the back and side faces only if depth > 0
        if (depth > 0.f)
        {
            // add the back face to the geometry

            // store positions
            // No need to store texture coordinates - we reuse the
            // texture coordinates from the front side
            UInt32 backCoordOffset = posPtr->size32();
            coordZ = -0.5f * depth;
            for (cIt = outline.coords.begin(); cIt != outline.coords.end(); ++cIt)
            {
                Vec2f coord = *cIt + pos;
                coord *= scale;
                posPtr->push_back(Vec3f(coord.x(), coord.y(), coordZ));
            }

            // Store types, lengths and indices
            // We have to flip all triangles to enable correct backface culling.
            // For GL_TRIANGLES, we simply flip the vertices.
            // For GL_TRIANGLE_FANs, we leave the first vertex at its place and flip the
            // remaining vertices.
            // For GL_TRIANGLE_STRIPs, things are more complicated. When the number of
            // vertices is uneven, we simply flip the vertices. When the number of
            // vertices is even, we have to add an additional vertex before we flip the
            // vertices.
//            UInt32 indexBegin = 0, indexEnd;
            for (tIt = outline.types.begin(); tIt != outline.types.end(); ++tIt)
            {
                typesPtr->push_back(tIt->first);
                indexEnd = tIt->second;
                OSG_ASSERT(indexEnd >= indexBegin);
                UInt32 len = indexEnd - indexBegin;
                UInt32 j = indexEnd;
                if (tIt->first == GL_TRIANGLE_FAN)
                {
                    j = indexBegin;
                    ++indexBegin;
                }
                if ((tIt->first == GL_TRIANGLE_STRIP) && ((len & 1) == 0))
                {
                    OSG_ASSERT((indexEnd >= 2) && (indexEnd - 2 >= indexBegin));
                    j = indexEnd - 2;
                    ++len;
                }
                if (j != indexEnd)
                {
                    // the interleaved multi-index blocks have the layout
                    // Position | Normal | TexCoord
                    OSG_ASSERT(j < outline.indices.size());
                    UInt32 index = outline.indices[j];
                    OSG_ASSERT(backCoordOffset + index < posPtr->size());
                    posIndicesPtr->push_back(backCoordOffset + index);
                    normalIndicesPtr->push_back(1);
                    OSG_ASSERT(texCoordOffset + index < texPtr->size());
                    texCoordIndicesPtr->push_back(texCoordOffset + index);
                    j = indexEnd;
                }
                lensPtr->push_back(len);
                while (true)
                {
                    if (j <= indexBegin)
                        break;
                    --j;

                    // the interleaved multi-index blocks have the layout
                    // Position | Normal | TexCoord
                    OSG_ASSERT(j < outline.indices.size());
                    UInt32 index = outline.indices[j];
                    OSG_ASSERT(backCoordOffset + index < posPtr->size());
                    posIndicesPtr->push_back(backCoordOffset + index);
                    normalIndicesPtr->push_back(1);
                    OSG_ASSERT(texCoordOffset + index < texPtr->size());
                    texCoordIndicesPtr->push_back(texCoordOffset + index);
                }
                indexBegin = indexEnd;
            }

            // Add the side faces to the geometry
            const TextVectorGlyph::Normals &normals = glyph.getNormals(level);

            // construct the multi index
            UInt32 start = 0, end, index = 0;
            vector<UInt32>::const_iterator iIt;
            vector<TextVectorGlyph::Orientation>::const_iterator oriIt = glyph.getContourOrientations().begin();
            for (iIt = outline.contours.begin(); iIt != outline.contours.end(); ++iIt, ++oriIt)
            {
                OSG_ASSERT(oriIt != glyph.getContourOrientations().end());
                UInt32 contourCoordOffset, contourBackCoordOffset;
                if (*oriIt == TextVectorGlyph::CCW)
                {
                    contourCoordOffset = coordOffset;
                    contourBackCoordOffset = backCoordOffset;
                }
                else
                {
                    contourCoordOffset = backCoordOffset;
                    contourBackCoordOffset = coordOffset;
                }

                end = *iIt;

                // the side faces are stored as quads
                GLenum mode = GL_QUAD_STRIP;
                UInt32 len = 0;

                UInt32 coordIndex, backCoordIndex;
                UInt32 normalOffset, startNormalOffset = normalsPtr->size32();
                for (index = start; index < end; ++index)
                {
                    normalOffset = normalsPtr->size32() - 1;
                    OSG_ASSERT(index < normals.size());
                    if (normals[index].edgeAngle > creaseAngle)
                    {
                        // We have an edge with two normals, so we need to
                        // add the vertices twice, but with different normals
                        // - but only when this is not the start index
                        if (index > start)
                        {
                            if ((mode == GL_QUAD_STRIP) && (len > 2))
                            {
                                typesPtr->push_back(GL_QUAD_STRIP);
                                OSG_ASSERT(((len + 2) & 1) == 0);
                                lensPtr->push_back(len + 2);
                                len = 0;
                                coordIndex = contourCoordOffset + index;
                                backCoordIndex = contourBackCoordOffset + index;
                            }
                            else
                            {
                                mode = GL_QUADS;
                                len += 2;
                                coordIndex = contourBackCoordOffset + index;
                                backCoordIndex = contourCoordOffset + index;
                            }

                            // back
                            OSG_ASSERT(backCoordIndex < posPtr->size());
                            posIndicesPtr->push_back(backCoordIndex);
                            OSG_ASSERT(normalOffset < normalsPtr->size());
                            normalIndicesPtr->push_back(normalOffset);
                            OSG_ASSERT(texCoordOffset + index < texPtr->size());
                            texCoordIndicesPtr->push_back(texCoordOffset + index);
                            // front
                            OSG_ASSERT(coordIndex < posPtr->size());
                            posIndicesPtr->push_back(coordIndex);
                            OSG_ASSERT(normalOffset < normalsPtr->size());
                            normalIndicesPtr->push_back(normalOffset);
                            OSG_ASSERT(texCoordOffset + index < texPtr->size());
                            texCoordIndicesPtr->push_back(texCoordOffset + index);
                        }

                        const Vec2f &normal = normals[index].nextEdgeNormal;
                        normalsPtr->push_back(Vec3f(normal.x(), normal.y(), 0.f));
                    }
                    else
                    {
                        if (mode == GL_QUADS)
                        {
                            typesPtr->push_back(GL_QUADS);
                            mode = GL_QUAD_STRIP;
                            OSG_ASSERT(len >= 6);
                            OSG_ASSERT(((len - 2) & 3) == 0);
                            lensPtr->push_back(len - 2);
                            len = 2;
                        }

                        const Vec2f &normal = normals[index].meanEdgeNormal;
                        normalsPtr->push_back(Vec3f(normal.x(), normal.y(), 0.f));
                    }
                    ++normalOffset;

                    // back
                    OSG_ASSERT(contourBackCoordOffset + index < posPtr->size());
                    posIndicesPtr->push_back(contourBackCoordOffset + index);
                    OSG_ASSERT(normalOffset < normalsPtr->size());
                    normalIndicesPtr->push_back(normalOffset);
                    OSG_ASSERT(texCoordOffset + index < texPtr->size());
                    texCoordIndicesPtr->push_back(texCoordOffset + index);
                    // front
                    OSG_ASSERT(contourCoordOffset + index < posPtr->size());
                    posIndicesPtr->push_back(contourCoordOffset + index);
                    OSG_ASSERT(normalOffset < normalsPtr->size());
                    normalIndicesPtr->push_back(normalOffset);
                    OSG_ASSERT(texCoordOffset + index < texPtr->size());
                    texCoordIndicesPtr->push_back(texCoordOffset + index);

                    len += 2;
                }

                // We have to close the strip, so add the start vertices again
                if (normals[start].edgeAngle <= creaseAngle)
                    normalOffset = startNormalOffset;
                if (mode == GL_QUAD_STRIP)
                {
                    coordIndex = contourCoordOffset + start;
                    backCoordIndex = contourBackCoordOffset + start;
                }
                else
                {
                    coordIndex = contourBackCoordOffset + start;
                    backCoordIndex = contourCoordOffset + start;
                }

                // back
                OSG_ASSERT(backCoordIndex < posPtr->size());
                posIndicesPtr->push_back(backCoordIndex);
                OSG_ASSERT(normalOffset < normalsPtr->size());
                normalIndicesPtr->push_back(normalOffset);
                OSG_ASSERT(texCoordOffset + start < texPtr->size());
                texCoordIndicesPtr->push_back(texCoordOffset + start);
                // front
                OSG_ASSERT(coordIndex < posPtr->size());
                posIndicesPtr->push_back(coordIndex);
                OSG_ASSERT(normalOffset < normalsPtr->size());
                normalIndicesPtr->push_back(normalOffset);
                OSG_ASSERT(texCoordOffset + start < texPtr->size());
                texCoordIndicesPtr->push_back(texCoordOffset + start);

                len += 2;

                // store the number of multi index blocks
                typesPtr->push_back(mode);
                OSG_ASSERT((mode != GL_QUADS) || ((len & 3) == 0));
                OSG_ASSERT((mode != GL_QUAD_STRIP) || ((len & 1) == 0));
                lensPtr->push_back(len);

                start = end;
            }
        }
    }
}


//----------------------------------------------------------------------
// Creates a new text geometry
// Author: pdaehne
//----------------------------------------------------------------------
GeometryTransitPtr TextVectorFace::makeGeo(const TextLayoutResult &layoutResult, Real32 scale,
                                    Real32 depth, UInt32 level, Real32 creaseAngle)
{
    GeometryTransitPtr geo = Geometry::create();
    fillGeo(geo.get(), layoutResult, scale, depth, level, creaseAngle);
    return geo;
}


//----------------------------------------------------------------------
// Creates a new node with a text geometry
// Author: pdaehne
//----------------------------------------------------------------------
NodeTransitPtr TextVectorFace::makeNode(const TextLayoutResult &layoutResult, Real32 scale,
                                 Real32 depth, UInt32 level, Real32 creaseAngle)
{
    GeometryTransitPtr geo = makeGeo(layoutResult, scale, depth, level, creaseAngle);
    NodeTransitPtr node = Node::create();

    node->setCore(geo);

    return node;
}


//----------------------------------------------------------------------
// Tries to create a vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFaceTransitPtr TextVectorFace::create(
    const std::string &family, Style style)
{
    return TextFaceFactory::the()->createVectorFace(family, style);
}

OSG_END_NAMESPACE
