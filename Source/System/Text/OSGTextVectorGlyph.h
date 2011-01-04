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

#ifndef _OSGTEXTVECTORGLYPH_H_
#define _OSGTEXTVECTORGLYPH_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"

#include "OSGTextGlyph.h"

#include <vector>
#include <map>


OSG_BEGIN_NAMESPACE


/**
 * Defines a vector glyph.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextGlyphs
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextVectorGlyph: public TextGlyph
{

  /** Needs access to constructor */
  friend class TextVectorFace;

    /*==========================  PUBLIC  =================================*/
  public:

    /**
     * Defines a point of an outline.
     * @author Patrick D&auml;hne
     *
     * \nohierarchy
     */

    struct OSG_TEXT_DLLMAPPING Point
    {
        /** Defines different types of outline points */
        enum PointType
        {
            PT_ON,
            PT_QUAD,
            PT_CUBIC
        };
        
        /** The position */
        Vec2f pos;
        
        /** The type of point (on, quad, cubic) */
        PointType type;
        
        /**
         * Creates a new %Point object.
         * @param _pos The position
         * @param _type The type of point
         */
        inline Point(const Vec2f &_pos, PointType _type);
    };

    /** Defines a contour */
    typedef std::vector<Point> Contour;

    /** Defines an outline */
    typedef std::vector<Contour> Outline;

    /** Defines an outline consisting of 2-d polygon lines 
     *
     * \nohierarchy
     */

    struct OSG_TEXT_DLLMAPPING PolygonOutline
    {
        /** All vertices of the outline */
        std::vector<Vec2f> coords;

        /** The index of the last vertex of each contour */
        std::vector<UInt32> contours;

        /** The vertex indices produced by the tesselation */
        std::vector<UInt32> indices;
        
        /** Defines a pair of a GL primitive type and an index */
        typedef std::pair<GLenum, UInt32> TypeIndex;

        /**
         * The GL primitive types (triangles, triangle strips or
         * triangle fans) and the index of the last vertex of each
         * sequence of primitives.
         */
        std::vector<TypeIndex> types;
    };
    
    /**
     * Defines a normal for a vertex in a contour. The normal is approximated
     *  by taking the mean of its adjacent edge normals.
     *
     * \nohierarchy
     */

    struct OSG_TEXT_DLLMAPPING VertexNormal
    {
        /** The edge normal of the outgoing edge */
        Vec2f nextEdgeNormal;

        /** normalized mean of the adjacent edge normals */
        Vec2f meanEdgeNormal;

        /** the angle between the adjacent edges */
        Real32 edgeAngle;

        /** Constructor */
        inline VertexNormal(const Vec2f &nextEdgeNormal_, 
                            const Vec2f &meanEdgeNormal_, 
                                  Real32 edgeAngle_     );
    };

    /** Defines a vector containing the edge normals along a polygon contour. */
    typedef std::vector<VertexNormal> Normals;

    /** Destroys the %VectorGlyph object. */
    virtual ~TextVectorGlyph(void);

    /**
     * Returns the width of the glyph.
     * @return The width of the glyph
     */
    virtual Real32 getWidth(void) const;

    /**
     * Returns the height of the glyph.
     * @return The height of the glyph
     */
    virtual Real32 getHeight(void) const;

    /**
     * Returns the x bearing of the glyph for horizontal layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingX(void) const;

    /**
     * Returns the y bearing of the glyph for horizontal layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingY(void) const;

    /**
     * Returns the x bearing of the glyph for vertical layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingX(void) const;

    /**
     * Returns the y bearing of the glyph for vertical layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingY(void) const;

    /**
     * Returns the contours that describe the outline
     * of the glyph.
     * @return The contours.
     */
    inline const Outline &getOutline(void) const;

    /**
     * Returns a polygon outline containing only on-curve points.
     * The contours contained in this outline are not closed!
     * @param level The level of detail.
     * @return An outline containing only on-curve points.
     */
    const PolygonOutline &getLines(UInt32 level = 2) const;

    /**
     * Returns an edge normal outline of the specified detail level
     * @param level The level of detail.
     * @return The normals at the edges of the outline.
     */
    const Normals &getNormals(UInt32 level = 2) const;

    /** Defines symbolic constants for the orientation of a contour. */
    enum Orientation
    {
        CW, CCW
    };

    /**
     * Returns the orientations of the outlines.
     * @return The orientations of the outline.
     */
    const std::vector<Orientation> &getContourOrientations(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %VectorGlyph object. */
    inline TextVectorGlyph(void);
        
    /** The width of the glyph */
    Real32 _width;

    /** The height of the glyph */
    Real32 _height;

    /** The x bearing of the glyph for horizontal layout */
    Real32 _horiBearingX;

    /** The y bearing of the glyph for horizontal layout */
    Real32 _horiBearingY;

    /** The x bearing of the glyph for vertical layout */
    Real32 _vertBearingX;

    /** The y bearing of the glyph for vertical layout */
    Real32 _vertBearingY;

    /** The original outline information */
    Outline _outline;

    /** The vector of contour orientations */
    mutable std::vector<Orientation> _contourOrientations;
    
    /** Defines the map of polygon outlines (level -> outline)*/
    typedef std::map<UInt32, PolygonOutline> PolygonOutlineMap;
  
    /** The map of polygon outlines (level -> outline)*/
    mutable PolygonOutlineMap _polygonOutlineMap;

    /** Defines the map of normal outlines (level -> edge normal outline) */
    typedef std::map<UInt32, Normals> NormalMap;

    /** The map of normal outlines (level -> edge normal outline) */
    mutable NormalMap _normalMap;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextVectorGlyph(const TextVectorGlyph &);

    /** Copy operator (not implemented!) */
    const TextVectorGlyph &operator=(const TextVectorGlyph &);

    /** Computes the orientation of each contour */
    void computeContourOrientations(void) const;
};


OSG_END_NAMESPACE


#include "OSGTextVectorGlyph.inl"

#endif /* _OSGTEXTVECTORGLYPH_H_ */
