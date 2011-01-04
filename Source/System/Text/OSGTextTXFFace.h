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

#ifndef _OSGTEXTTXFFACE_H_
#define _OSGTEXTTXFFACE_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGGeometry.h"
#include "OSGNode.h"
#include "OSGImage.h"

#include "OSGTextFace.h"
#include "OSGTextGlyph.h"
#include "OSGTextTXFParam.h"

#include <string>
#include <map>
#include <iosfwd>


OSG_BEGIN_NAMESPACE


class TextTXFGlyph;
class TextLayoutParam;
class TextLayoutResult;


/**
 * Represents a TXF face. A TXF face is a texture containing a set of
 * glyphs. It allows to take geometries consisting of small rectangles
 * onto which one glyph of the texture is mapped, respectively. You
 * can load TXF faces from TXF files, or you can create TXF faces from
 * the faces installed on the system. The following piece of code
 * demonstrates how to create and use %TextTXFFace objects.
 *
 * @code
 * // Includes
 * #include "OSGTextTXFFace.h"
 * #include "OSGTextLayoutParam.h"
 * #include "OSGTextLayoutResult.h"
 *
 * // Try to create a new %TextTXFFace object. The create
 * // method returns 0 in case of an error.
 * // Make sure to use a RefPtr for the face as they are cached and there may
 * // be more than one user.
 * TextTXFFaceRefPtr face = TextTXFFace::create("SANS");
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
 * GeometryRefPtr geo = face->makeGeo(layoutResult, scale);
 *
 * // Get the texture. You have to map this texture onto the
 * // geometry we created above.
 * ImageRefPtr img = face->getTexture();
 *
 * // We do not need the TXF face anymore, so clear the pointer or let it go
 * // out of scope.
 * face = NULL;
 * @endcode
 *
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextFaces
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextTXFFace: public TextFace
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef TextFace                                Inherited;
    typedef TextTXFFace                             Self;

    typedef TransitPtr <Self                      > ObjTransitPtr;
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /**
     * Returns the scaling factor.
     * @return The scaling factor
     */
    inline Real32 getScale() const;

    /**
     * Returns the parameters of the face.
     * @return The parameters.
     */
    inline const TextTXFParam &getParam() const;

    /**
     * Returns the texture that contains all glyphs.
     * @return The texture. Do not modify this texture in
     * any way!
     */
    inline Image *getTexture() const;

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
    const TextTXFGlyph &getTXFGlyph(TextGlyph::Index glyphIndex);

    /**
     * Lays out one line of text.
     * @param utf8Text The UTF8 encoded text.
     * @param param Contains parameters that affect the layout process.
     * @param result Gets filled with the layout results.
     */
    virtual void layout(const std::string &utf8Text,
                        const TextLayoutParam &param,
                        TextLayoutResult &result);

    /**
     * Lays out one line of text.
     * @param text The text.
     * @param param Contains parameters that affect the layout process.
     * @param result Gets filled with the layout results.
     */
    virtual void layout(const std::wstring &text,
                        const TextLayoutParam &param,
                        TextLayoutResult &result);

    /**
     * Lays out multiple lines of text.
     * @param lines The vector of UTF8 encoded lines.
     * @param param Contains parameters that affect the layout process.
     * @param result Gets filled with the layout results.
     */
    virtual void layout(const std::vector<std::string> &lines,
                        const TextLayoutParam &param,
                        TextLayoutResult &result);

    /**
     * Lays out multiple lines of text.
     * @param lines The vector of text lines.
     * @param param Contains parameters that affect the layout process.
     * @param result Gets filled with the layout results.
     */
    virtual void layout(const std::vector<std::wstring> &lines,
                        const TextLayoutParam &param,
                        TextLayoutResult &result);

    /**
     * Fills a geometry with a new text.
     * @param geoPtr The geometry that gets filled with the new text.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param offset Amount to offset the positions in the layout.
     * @param color  The color to use for the text.  If not specified, then we will not add color container.
     */
    void fillGeo(Geometry *geoPtr, const TextLayoutResult &layoutResult, Real32 scale = 1.f,
                 Vec2f offset = Vec2f(0,0), Color3f color = Color3f(-1,-1,-1));

    /**
     * Adds geometry for new text to an existing text geometry.
     * @param geoPtr The geometry that gets filled with the new text.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param offset Amount to offset the positions in the layout.
     * @param color  The color to use for the text.
     * @note  Iff initial fill or add call used non-default color, the color parameter will be used.
     */
    void addToGeom(Geometry *geoPtr, const TextLayoutResult &layoutResult, Real32 scale = 1.f,
                 Vec2f offset = Vec2f(0,0), Color3f color = Color3f(-1,-1,-1));

    /**
     * Creates a new text geometry.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param offset Amount to offset the positions in the layout.
     * @param color  The color to use for the text.
     * @return A new text geometry.
     */
    GeometryTransitPtr makeGeo(const TextLayoutResult &layoutResult, Real32 scale = 1.f,
                        Vec2f offset = Vec2f(0,0), Color3f color = Color3f(-1,-1,-1));

    /**
     * Creates a new node with a text geometry.
     * @param layoutResult The result of a layout operation.
     * @param scale The size of the glyphs.
     * @param offset Amount to offset the positions in the layout.
     * @param color  The color to use for the text.
     * @return A new node containing a text geometry.
     */
    NodeTransitPtr makeNode(const TextLayoutResult &layoutResult, Real32 scale = 1.f,
                     Vec2f offset = Vec2f(0,0), Color3f color = Color3f(-1,-1,-1));

    /**
     * Helper method to draw the results of a layout using this face.
     * @param layoutResult  The results of a previous layout
     * @pre   The texture for this face *must* be active before calling this method
     */
    void drawCharacters(const TextLayoutResult &layoutResult);

    /**
     * Tries to create a TXF face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param param Parameters that affect the creation of the
     * TXF face.
     * @return The TXF face object or 0 in case of an error.
     */
    static ObjTransitPtr create(
            const std::string  &family,
                  Style         style = STYLE_PLAIN,
            const TextTXFParam &param = TextTXFParam());

    /**
     * Reads a TXF face from an input stream.
     * @param is The input stream.
     * @param family The font family
     * @param style The font style
     * @return The TXF face or 0 in case of an error.
     */
    static ObjTransitPtr createFromStream(
                  std::istream &is,
            const std::string  &family = std::string(),
                  Style         style  = STYLE_PLAIN   );

    /**
     * Reads a TXF face from a file.
     * @param filename The name of the TXF file.
     * @return The TXF face or 0 in case of an error.
     */
    static ObjTransitPtr createFromFile(const std::string &filename);

    /**
     * Writes a TXF face to an output stream.
     * @param os The output stream.
     * @return false in case of an error.
     */
    bool writeToStream(std::ostream &os) const;

    /**
     * Writes a TXF face to a TXF file.
     * @param filename The name of the TXF file.
     * @return false in case of an error.
     */
    bool writeToFile(const std::string &filename) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextTXFFace object. */
    inline TextTXFFace();

    /** Destroys the %TextTXFFace object. */
    virtual ~TextTXFFace();

    /** Calculates the positions of the glyphs on the texture */
    void prepareTexture(const TextTXFParam &param);

    /** The scale factor used to scale font metrics */
    Real32 _scale;

    /** The parameters of the face */
    TextTXFParam _param;

    /** The texture that contains all glyphs */
    ImageUnrecPtr _texture;

    /** Defines a map of glyphs */
    typedef std::map<TextGlyph::Index, TextTXFGlyph*> GlyphMap;

    /** The map of glyphs */
    GlyphMap _glyphMap;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextTXFFace(const TextTXFFace &);

    /** Copy operator (not implemented!) */
    const TextTXFFace &operator=(const TextTXFFace &);

    /** An empty glyph */
    static TextTXFGlyph _emptyGlyph;
};

typedef TextTXFFace::ObjTransitPtr TextTXFFaceTransitPtr;
typedef TextTXFFace::ObjRefPtr     TextTXFFaceRefPtr;

OSG_END_NAMESPACE


#include "OSGTextTXFFace.inl"

#endif /* _OSGTEXTTXFFACE_H_ */
