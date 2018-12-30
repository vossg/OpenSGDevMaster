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

#ifndef _OSGTEXTVECTORFACE_H_
#define _OSGTEXTVECTORFACE_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGGeometry.h"
#include "OSGNode.h"

#include "OSGTextFace.h"
#include "OSGTextGlyph.h"

#include <string>
#include <map>
#include <memory>


OSG_BEGIN_NAMESPACE


class TextVectorGlyph;
class TextLayoutResult;


/**
 * Represents a vector face. A vector face allows to create texts as
 * 3D objects. The following piece of code demonstrates how to create
 * and use %TextVectorFace objects.
 *
 * @code
 * // Includes
 * #include "OSGTextVectorFace.h"
 * #include "OSGTextLayoutParam.h"
 * #include "OSGTextLayoutResult.h"
 *
 * // Try to create a new %TextVectorFace object. The create
 * // method returns 0 in case of an error
 * TextVectorFaceRefPtr face = TextVectorFace::create("SANS");
 * if (face == 0)
 *   ; // error handling
 *
 * // Lay out a single line of text. There are lots of parameters
 * // you can set in the layoutParam object, but for now we are
 * // satisfied with the default values. See the documentation
 * // of the TextLayoutParam class for more information.
 * TextLayoutParam layoutParam;
 * TextLayoutResult layoutResult;
 * face->layout("Hello World!", layoutParam, layoutResult);
 *
 * // Create the geometry using the layout information returned
 * // from the previous call to the layout method.
 * Real32 scale = 2.f;  // This is the height of the glyphs
 * Real32 depth = 0.5f; // This is the depth of the glyphs
 * GeometryRecPtr geo = face->makeGeo(layoutResult, scale, depth);
 *
 * // We do not need the vector face anymore, so set the variable to NULL.
 * face = NULL;
 * @endcode
 *
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextFaces
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextVectorFace: public TextFace
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef TextFace                                Inherited;
    typedef TextVectorFace                          Self;

    typedef TransitPtr <Self                      > ObjTransitPtr;
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /**
     * Returns information about a glyph.
     * @param glyphIndex The index of the glyph. Use the layout method
     * to get the glyph indices corresponding to a character string.
     * @return A glyph object containing information about the glyph.
     */
    virtual const TextGlyph &getGlyph(TextGlyph::Index glyphIndex);

    /**
     * Returns information about a glyph.
     * @param glyphIndex The index of the glyph. Use the layout method
     * to get the glyph indices corresponding to a character string.
     * @return A glyph object containing information about the glyph.
     */
    const TextVectorGlyph &getVectorGlyph(TextGlyph::Index glyphIndex);

    /**
     * Fills a geometry with a new text.
     * @param geoPtr The geometry that gets filled with the new text.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param depth The depth of the VectorGlyphs. If depth is 0.f no
     *              backside will be generated.
     * @param level The level of detail. Usually between 0 and 10.
     * @param creaseAngle The angle (in radians) which determines how faceted
     *                    the  glyphs should be lighted.
     *                    If the angle enclosed by two vertex normals in a point
     *                    exceeds the creaseAngle both of the two normals will 
     *                    be attached to the point. Otherwise their mean is
     *                    used. 
     */
    void fillGeo(Geometry *geoPtr, const TextLayoutResult &layoutResult,
                 Real32 scale = 1.f, Real32 depth = 0.f, UInt32 level = 2, 
                 Real32 creaseAngle = Pi / 4.f);

    /**
     * Creates a new text geometry.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param depth The depth of the VectorGlyphs. If depth is 0.f no
     *              backside will be generated.
     * @param level The level of detail. Usually between 0 and 10.
     * @param creaseAngle The angle (in radians) which determines how faceted
     *                    the glyphs should be lighted.
     *                    If the angle enclosed by two vertex normals in a point
     *                    exceeds the creaseAngle both of the two normals will 
     *                    be attached to the point. Otherwise their mean is
     *                    used. 
     * @return A new text geometry.
     */
    GeometryTransitPtr makeGeo(const TextLayoutResult &layoutResult, 
                                     Real32            scale       = 1.f,
                                     Real32            depth       = 0.f, 
                                     UInt32            level       = 2, 
                                     Real32            creaseAngle = Pi / 4.f);

    /**
     * Creates a new node with a text geometry.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param depth The depth of the VectorGlyphs. If depth is 0.f no
     *              backside will be generated.
     * @param level The level of detail. Usually between 0 and 10.
     * @param creaseAngle The angle (in radians) which determines how faceted
     *                    the glyphs should be lighted.
     *                    If the angle enclosed by two vertex normals in a point
     *                    exceeds the creaseAngle both of the two normals will 
     *                    be attached to the point. Otherwise their mean is
     *                    used. 
     * @return A new node containing a text geometry.
     */
    NodeTransitPtr makeNode(const TextLayoutResult &layoutResult, 
                                  Real32            scale       = 1.f,
                                  Real32            depth       = 0.f, 
                                  UInt32            level       = 2, 
                                  Real32            creaseAngle = Pi / 4.f);

    /**
     * Tries to create a vector face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @return The vector face object or 0 in case of an error.
     */
    static ObjTransitPtr create(
            const std::string &family,  Style style = STYLE_PLAIN);

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextVectorFace object. */
    inline TextVectorFace(void);

    /** Destroys the %TextVectorFace object. */
    virtual ~TextVectorFace(void);

    /** The scale factor used to scale font metrics */
    Real32 _scale;

    /** Defines a map of glyphs */
    typedef std::map<TextGlyph::Index, TextVectorGlyph*> GlyphMap;

    /** The map of glyphs */
    GlyphMap _glyphMap;

    /**
     * Creates a new Glyph object.
     * This method has to be implemented by descendants of the %VectorFace
     * class. 
     * @param glyphIndex The index of the glyph.
     * @return The glyph object or 0 when no glyph exists for the given
     * glyph index.
     */
    virtual 
    std::unique_ptr<TextVectorGlyph> createGlyph(TextGlyph::Index glyphIndex) = 0;

    /** An empty glyph */
    static TextVectorGlyph _emptyGlyph;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextVectorFace(const TextVectorFace &);

    /** Copy operator (not implemented!) */
    const TextVectorFace &operator=(const TextVectorFace &);
};

typedef TextVectorFace::ObjTransitPtr TextVectorFaceTransitPtr;
typedef TextVectorFace::ObjRefPtr     TextVectorFaceRefPtr;

OSG_END_NAMESPACE


#include "OSGTextVectorFace.inl"

#endif /* _OSGTEXTVECTORFACE_H_ */
