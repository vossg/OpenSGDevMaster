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

#include "OSGTextVectorGlyph.h"

#include <OSGGLU.h>

#ifdef __sgi
# include <cassert>
# include <cmath>
#else
# include <cassert>
# include <cmath>
#endif


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorGlyph::~TextVectorGlyph(void) {}


//----------------------------------------------------------------------
// Returns the width of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getWidth(void) const
{ return _width; }


//----------------------------------------------------------------------
// Returns the height of the glyph
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getHeight(void) const
{ return _height; }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getHoriBearingX(void) const
{ return _horiBearingX; }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for horizontal layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getHoriBearingY(void) const
{ return _horiBearingY; }


//----------------------------------------------------------------------
// Returns the x bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getVertBearingX(void) const
{ return _vertBearingX; }


//----------------------------------------------------------------------
// Returns the y bearing of the glyph for vertical layout
// Author: pdaehne
//----------------------------------------------------------------------
Real32 TextVectorGlyph::getVertBearingY(void) const
{ return _vertBearingY; }


//----------------------------------------------------------------------
// Evalutes a quadratic bezier curve via "forward differencing" (i.e. taylor
// expansion) in a non-adaptive way.
// The output is written into the specified PolygonContour &polygonContour.
//
// Note: The last point is not written into the polygonContour.
//
// Author: afischle
//----------------------------------------------------------------------
static void evalCubicBezierCurve(const Vec2f &pt1, const Vec2f &pt2, const Vec2f &pt3, const Vec2f &pt4,
                                 const UInt32 level, vector<Vec2f> &coords)
{
    // granularity for the detail level
    const UInt32 knotsPerLevel = 3;
    // number of points generated for detail level n
    const UInt32 steps = knotsPerLevel * (level + 1) - 1;

    const Real32 h = 1.0f / steps;
    const Real32 hh = h * h; // h squared
    const Real32 hhh = h * hh; // h cube

    // initialize taylor coefficients for a bezier curve f at x=0
    // f = f, f' = df, f'' = ddf, f''' = dddf
    Vec2f f = pt1;
    Vec2f df = (pt2 - pt1) * 3.0f * h;

    Vec2f ddf_div_2 = (pt1 - pt2  * 2.0f + pt3) * 3.0f * hh;
    Vec2f ddf = ddf_div_2 + ddf_div_2;

    const Vec2f dddf_div_2 = ((pt2 - pt3) * 3.0f + pt4 - pt1) * 3.0f * hhh;
    const Vec2f dddf = dddf_div_2 + dddf_div_2;
    const Vec2f dddf_div_6 = dddf_div_2 * (1.0f / 3.0f);

    // sum up the taylor coefficients to obtain f(x+h)
    UInt32 i;
    for (i = steps; i > 0; --i)
    {
        coords.push_back(f);
        // taylor series of a cubic bezier curve (i.e. polynomial) f
        // and its derivatives f', f''
        f   += df + ddf_div_2 + dddf_div_6;
        df  += ddf + dddf_div_2;
        ddf += dddf;
        ddf_div_2 += dddf_div_2;
    }
}


//----------------------------------------------------------------------
// Evalutes a quadratic bezier curve via "forward differencing" (i.e. taylor
// expansion) in a non-adaptive way.
// The output is written into the specified PolygonContour &polygonContour.
//
// Note: The last point is not written into the polygonContour.
//
// Author: afischle
//----------------------------------------------------------------------
static void evalQuadraticBezierCurve(const Vec2f &pt1, const Vec2f &pt2, const Vec2f &pt3,
                                     const UInt32 level, vector<Vec2f> &coords)
{
    const UInt32 knotsPerLevel = 3;
    // determines the number of points generated for level n
    const UInt32 steps = knotsPerLevel * (level + 1) - 1;

    const Real32 h = 1.0f / steps;
    const Real32 hh = h * h;

    // f(0)
    Vec2f f = pt1;

    // df(0) = -2*P_0 + 2P_1
    Vec2f df = (pt2 - pt1) * 2.f * h;

    // ddf(0) = 2*P_0 - 4*P_1 + 2*P_2
    const Vec2f ddf_div_2 = (pt1 - pt2 * 2.f + pt3) * hh;
    const Vec2f ddf = ddf_div_2 + ddf_div_2;

    // sum up the taylor coefficients to obtain f(x+h)
    UInt32 i;
    for (i = steps; i > 0; --i)
    {
        coords.push_back(f);
        // taylor series of a quadratic bezier curve (i.e polynomial) f
        f  += df + ddf_div_2;
        df += ddf;
    }
}


//----------------------------------------------------------------------
// Selects the bezier curve evaluation function for the specified order
// and evaluates the bezier curve.
//
// returns a PolygonOutline containing the rendered polygon outline.
//
// Author: afischle
//----------------------------------------------------------------------
static void evalBezierCurve(const TextVectorGlyph::Contour &contour, UInt32 &index,
                            const UInt32 level,
                            vector<Vec2f> &coords)
{
    assert(index + 1 < contour.size());
    switch (contour[index + 1].type)
    {
        // linear segment - copy first point only
        case TextVectorGlyph::Point::PT_ON:
            assert(index < contour.size());
            coords.push_back(contour[index].pos);
            ++index;
            break;
            // quadratic segment - last point point omitted by evaluation function
        case TextVectorGlyph::Point::PT_QUAD:
            assert(index + 2 < contour.size());
            evalQuadraticBezierCurve(contour[index].pos, contour[index + 1].pos, contour[index + 2].pos, level, coords);
            index += 2;
            break;
            // cubic segment - last point point omitted by evaluation function
        case TextVectorGlyph::Point::PT_CUBIC:
            assert(index + 3 < contour.size());
            evalCubicBezierCurve(contour[index].pos, contour[index + 1].pos, contour[index + 2].pos, contour[index + 3].pos, level, coords);
            index += 3;
            break;
        default:
            assert(false);
            break;
    }
}


//----------------------------------------------------------------------
// Tesselation callback function - Called at the beginning of a primitive
// Author: afischle, pdaehne
//----------------------------------------------------------------------
static void OSG_APIENTRY gluTessBeginDataCB(GLenum type, void *polygonData)
{
    TextVectorGlyph::PolygonOutline *outline = reinterpret_cast<TextVectorGlyph::PolygonOutline*>(polygonData);
    assert(outline != 0);
    outline->types.push_back(TextVectorGlyph::PolygonOutline::TypeIndex(type, 0));
}


//----------------------------------------------------------------------
// Tesselation callback function - Called at the ned of a primitive
// Author: afischle, pdaehne
//----------------------------------------------------------------------
static void OSG_APIENTRY gluTessEndDataCB(void *polygonData)
{
    TextVectorGlyph::PolygonOutline *outline = reinterpret_cast<TextVectorGlyph::PolygonOutline*>(polygonData);
    assert(outline != 0);
    assert(outline->types.empty() == false);
    outline->types.back().second = outline->indices.size();
}


//----------------------------------------------------------------------
// Vertex data handler: Receives the triangle vertex indices from the
//                      GLU Tesselator
// Author: afischle, pdaehne
//----------------------------------------------------------------------
static void OSG_APIENTRY gluTessVertexDataCB(void *vertexData, void *polygonData)
{
    TextVectorGlyph::PolygonOutline *outline = reinterpret_cast<TextVectorGlyph::PolygonOutline*>(polygonData);
    
    // Go via 64 bit int to avoid problems on 64 bit machines
    UInt64 coordIndexHelp = UInt64(vertexData);
    UInt32 coordIndex = static_cast<UInt32>(coordIndexHelp);

    assert(outline != 0);
    outline->indices.push_back(coordIndex);
}


//----------------------------------------------------------------------
// Combine data handler: Linearly combines vertices in case of self intersections
//                       and inserts them into the frontFace and vertexIndices
//                       structures.
// Author: afischle, pdaehne
//----------------------------------------------------------------------
static void OSG_APIENTRY gluTessCombineDataCB(GLdouble coords[3], void *vertexData[4],
                                 GLfloat weight[4], void **outDatab,
                                 void *polygonData)
{
    TextVectorGlyph::PolygonOutline *outline = reinterpret_cast<TextVectorGlyph::PolygonOutline*>(polygonData);
    assert(outDatab != 0);
    *outDatab = reinterpret_cast<void*>(outline->coords.size());
    assert(outline != 0);
    outline->coords.push_back(Vec2f(coords[0], coords[1]));
}


//----------------------------------------------------------------------
// Returns a PolygonOutline containing only on-curve points with the specified
// detail level. The contours contained in this outline are not closed!
// Author: afischle, pdaehne
//----------------------------------------------------------------------
const TextVectorGlyph::PolygonOutline &TextVectorGlyph::getLines(UInt32 level) const
{
    // Try to find the polygon outline of the specified detail level in the
    // cache map
    PolygonOutlineMap::const_iterator it = _polygonOutlineMap.find(level);
    if (it != _polygonOutlineMap.end())
        // We already have that level - return the corresponding outline
        return it->second;

    // We did not find that level, so we have to create it
    PolygonOutline &newOutline = _polygonOutlineMap.insert(PolygonOutlineMap::value_type(level, PolygonOutline())).first->second;

    // Calculate the bezier curves for this level
    Outline::const_iterator oIt;
    for (oIt = _outline.begin(); oIt != _outline.end(); ++oIt)
    {
        UInt32 size = oIt->size();
        if (size > 0)
        {
            size -= 1;
            UInt32 index = 0;
            while (index < size)
                evalBezierCurve(*oIt, index, level, newOutline.coords);
            newOutline.contours.push_back(newOutline.coords.size());
        }
    }

    // Calculate the faces

    // Create a new GLU tesselator object
    GLUtesselator *tess = gluNewTess();
    if (tess == 0)
        return newOutline;

    // hint to the GLU tesselator that all points lie in the xy-plane
    gluTessNormal(tess, 0.0, 0.0, 1.0);
    // set the winding rule
    gluTessProperty(tess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);

    // register GLU Tesselator callback methods
    gluTessCallback(tess,
                    GLU_TESS_BEGIN_DATA,
                    reinterpret_cast<OSGGLUfuncptr>(gluTessBeginDataCB));
    gluTessCallback(tess,
                    GLU_TESS_END_DATA,
                    reinterpret_cast<OSGGLUfuncptr>(gluTessEndDataCB));
    gluTessCallback(tess,
                    GLU_TESS_COMBINE_DATA,
                    reinterpret_cast<OSGGLUfuncptr>(gluTessCombineDataCB));
    gluTessCallback(tess,
                    GLU_TESS_VERTEX_DATA,
                    reinterpret_cast<OSGGLUfuncptr>(gluTessVertexDataCB));

    // make shared data structure available to callbacks */
    gluTessBeginPolygon(tess, &newOutline);

    vector<UInt32>::const_iterator cIt;
    UInt32 coordIndex = 0;
    for (cIt = newOutline.contours.begin(); cIt != newOutline.contours.end(); ++cIt)
    {
        // begin new contour
        gluTessBeginContour(tess);

        while (coordIndex < *cIt)
        {
            GLdouble coords[3];
            assert(coordIndex < newOutline.coords.size());
            coords[0] = newOutline.coords[coordIndex].x();
            coords[1] = newOutline.coords[coordIndex].y();
            coords[2] = 0.f;
            gluTessVertex(tess, coords, reinterpret_cast<void*>(coordIndex++));
        }

        // end of contour
        gluTessEndContour(tess);
    }

    // trigger tesselator action
    gluTessEndPolygon(tess);

    // clean up
    gluDeleteTess(tess);

    return newOutline;
}


//----------------------------------------------------------------------
// the next edge normal is computed as a pi/2 clockwise rotation of
// the direction from this point to the next one. The edge normals
// do thus point to the left of the path.
// Author: afischle
//----------------------------------------------------------------------
static Vec2f computeEdgeNormal(const Vec2f &a, const Vec2f &b, bool cw)
{
    Vec2f d = b - a;
    d.normalize();
    return cw == true ? Vec2f(d.y(), -d.x()) : Vec2f(-d.y(), d.x());
}


//----------------------------------------------------------------------
// Returns a normal outline containining normal contours. These normal contours
// contain GlyphVertexNormal structs providing the normals of the adjacent edges,
// the mean normal and the angle enclosed by the edge normals.
//
// Author: afischle
//----------------------------------------------------------------------
const TextVectorGlyph::Normals &TextVectorGlyph::getNormals(UInt32 level) const
{
    // Try to find the normal outline of the specified detail level in the
    // cache map
    NormalMap::const_iterator it = _normalMap.find(level);
    if (it != _normalMap.end())
        // We already have that level - return the corresponding outline
        return it->second;

    // We did not find that level, so we have to create it
    Normals &normals = _normalMap.insert(NormalMap::value_type(level, Normals())).first->second;

    // get the polygon outline of this glyph at the desired detail level
    // The contours of this outline are not closed!
    const PolygonOutline &outline = getLines(level);

    // compute the contour orientations when they are not available
    if (_contourOrientations.empty())
        computeContourOrientations();

    UInt32 start = 0, end, index = 0;
    vector<UInt32>::const_iterator iIt;
    vector<Orientation>::const_iterator oriIt = _contourOrientations.begin();
    for (iIt = outline.contours.begin(); iIt != outline.contours.end(); ++iIt, ++oriIt)
    {
        end = *iIt;

        assert(end - 1 < outline.coords.size());
        assert(start < outline.coords.size());
        assert(oriIt != _contourOrientations.end());
        Vec2f prevEdgeNormal = computeEdgeNormal(outline.coords[end - 1],
                                                 outline.coords[start],
                                                 (*oriIt) == CW);
        while (index < end)
        {
            UInt32 nextIndex = index + 1;
            if (nextIndex >= end)
                nextIndex = start;

            assert(index < outline.coords.size());
            assert(nextIndex < outline.coords.size());
            Vec2f nextEdgeNormal = computeEdgeNormal(outline.coords[index], outline.coords[nextIndex], (*oriIt) == CW);
            Vec2f meanEdgeNormal = prevEdgeNormal + nextEdgeNormal;
            meanEdgeNormal.normalize();
            Real32 edgeAngle = osgACos(osgAbs(prevEdgeNormal.dot(nextEdgeNormal)));
            normals.push_back(VertexNormal(nextEdgeNormal, meanEdgeNormal, edgeAngle));

            //the outgoing edge of this vertex is the incoming of the next vertex
            prevEdgeNormal = nextEdgeNormal;

            ++index;
        }

        start = end;
    }

    return normals;
}


//----------------------------------------------------------------------
// Returns the orientations of the outlines
// Author: pdaehne
//----------------------------------------------------------------------
const vector<TextVectorGlyph::Orientation> &TextVectorGlyph::getContourOrientations() const
{
    // compute the contour orientations when they are not available
    if (_contourOrientations.empty())
        computeContourOrientations();
    return _contourOrientations;
}


//----------------------------------------------------------------------
// returns true if the given goint lies in the left half plane of the
// oriented line AB.
// Author: afischle
//----------------------------------------------------------------------
static bool isLeft(const Vec2f &a, const Vec2f &b, const Vec2f &point)
{
    // compute the normal pointing into the left half plane of the oriented
    // line
    Vec2f n = computeEdgeNormal(a, b, false);
    // the dot product is >0 when two vectors point into the same direction
    return n.dot(point - a) > 0.f;
}


//----------------------------------------------------------------------
// returns the winding number of the given contour with respect to the point
// by counting how often the infinite line f(x) = point.y was crossed by the
// contour
// Author: afischle
//----------------------------------------------------------------------
static Int32 calcWindingNumber(const vector<Vec2f> &coords, UInt32 start, UInt32 end, const Vec2f &point)
{
    Int32 windingNumber = 0;
    assert(end - 1 < coords.size());
    const Vec2f *prevPoint = &(coords[end - 1]);
    UInt32 i;
    for (i = start; i < end; ++i)
    {
        assert(i < coords.size());
        const Vec2f *curPoint = &(coords[i]);
        if (prevPoint->y() <= point.y())
        {
            // upward crossing
            if (curPoint->y() > point.y())
            {
                if (isLeft(*prevPoint, *curPoint, point) == true)
                    windingNumber++;
            }
        }
        else // prevPoint->y() > point.y()
        {
            // downward crossing
            if (curPoint->y() < point.y())
            {
                if (isLeft(*prevPoint, *curPoint, point) == false)
                    windingNumber--;
            }
        }
        prevPoint = curPoint;
    }

    return windingNumber;
}


//----------------------------------------------------------------------
// Checks if a point lies inside the glyph
// Author: afischle
//----------------------------------------------------------------------
static bool isInteriorPoint(const Vec2f &point, const TextVectorGlyph::PolygonOutline &outline, GLenum windingRule)
{
    Int32 totalWindingNumber = 0;
    UInt32 start = 0, end;
    vector<UInt32>::const_iterator it;
    for (it = outline.contours.begin(); it != outline.contours.end(); ++it)
    {
        end = *it;
        totalWindingNumber += calcWindingNumber(outline.coords, start, end, point);
        start = end;
    }

    switch(windingRule)
    {
        case GLU_TESS_WINDING_NONZERO:
            return totalWindingNumber != 0;
        case GLU_TESS_WINDING_ODD:
            return (totalWindingNumber % 2) != 0;
        default:
            return false;
    }
}


//----------------------------------------------------------------------
// Calculates the orientations of the contours
// Author: afischle
//----------------------------------------------------------------------
void TextVectorGlyph::computeContourOrientations() const
{
    // get the simplest outline available as it should suffice for the
    // orientation check
    const PolygonOutline &outline = getLines(0);
    UInt32 start = 0, end;
    vector<UInt32>::const_iterator it;
    for (it = outline.contours.begin(); it != outline.contours.end(); ++it)
    {
        end = *it;

        // return value does not matter
        if (end - start < 3)
            _contourOrientations.push_back(CCW);

        assert(start + 2 < outline.coords.size());
        Vec2f en1 = computeEdgeNormal(outline.coords[start], outline.coords[start + 1], false);
        Vec2f en2 = computeEdgeNormal(outline.coords[start + 1], outline.coords[start + 2], false);
        // compute the mean of the edge normals at vertex 0.
        Vec2f testNormal = en1 + en2;
        testNormal.normalize();
        // calculate the displacement of vertex 0 along its mean edge normal
        Vec2f testPoint = outline.coords[start + 1] + testNormal * (1000.f * Eps);

        if (isInteriorPoint(testPoint, outline, GLU_TESS_WINDING_NONZERO))
            _contourOrientations.push_back(CW);
        else
            _contourOrientations.push_back(CCW);

        start = end;
    }
}


OSG_END_NAMESPACE

