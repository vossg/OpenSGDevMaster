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

#ifndef _OSGTEXTPIXMAPFACE_H_
#define _OSGTEXTPIXMAPFACE_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGImage.h"
#include "OSGVector.h"

#include "OSGTextFace.h"
#include "OSGTextGlyph.h"

#include <string>
#include <map>
#include <memory>


OSG_BEGIN_NAMESPACE


class TextPixmapGlyph;
class TextLayoutResult;


/**
 * Represents a pixmap face. A pixmap face allows to render texts into
 * textures. The following piece of code demonstrates how to create
 * and use %TextPixmapFace objects.
 *
 * @code
 * // Includes
 * #include "OSGTextPixmapFace.h"
 * #include "OSGTextLayoutParam.h"
 * #include "OSGTextLayoutResult.h"
 *
 * // Try to create a new %TextPixmapFace object. The create
 * // method returns 0 in case of an error
 * TextPixmapFace *face = TextPixmapFace::create("SANS");
 * if (face == 0)
 *   ; // error handling
 *
 * // Increment the reference counter of the face object.
 * // Faces are cached, and we might not be the only one
 * // using the face object
 * addRefP(face);
 *
 * // Lay out a single line of text. There are lots of parameters
 * // you can set in the layoutParam object, but for now we are
 * // satisfied with the default values. See the documentation
 * // of the TextLayoutParam class for more information.
 * TextLayoutParam layoutParam;
 * TextLayoutResult layoutResult;
 * face->layout("Hello World!", layoutParam, layoutResult);
 *
 * // Create the texture using the layout information returned
 * // from the previous call to the layout method.
 * Real32 offset; // This is the offset from the coordinate origin to the
 *                // upper left corner of the texture (in pixels).
 * ImagePtr img = face->makeImage(layoutResult, offset);
 *
 * // We do not need the pixmap face anymore, so decrement
 * // the reference counter. Do not use the face object anymore!
 * subRefP(face);
 * @endcode
 *
 * @author Patrick D&auml;hne
 */
class OSG_TEXT_DLLMAPPING TextPixmapFace: public TextFace
{
    /*==========================  PUBLIC  =================================*/
  public:

    /**
     * Returns the actual size of the face in pixels.
     * @return The size in pixels.
     */
    inline UInt32 getSize() const;

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
    const TextPixmapGlyph &getPixmapGlyph(TextGlyph::Index glyphIndex);

    /**
     * Creates a texture image with the result of a layout operation.
     * The format of the texture image is GL_INTENSITY.
     * @param layoutResult The result of a layout operation.
     * @param offset Gets filled with the offset of the upper left
     * corner of the image from the coordinate origin.
     * @return The image filled with the text.
     */
    ImagePtr makeImage(const TextLayoutResult &layoutResult, Vec2f &offset);

    /**
     * Tries to create a pixmap face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param size The size of the pixmap font in pixels.
     * @return The pixmap face object or 0 in case of an error.
     */
    static TextPixmapFace *create(const std::string &family,
                                  Style style = STYLE_PLAIN,
                                  UInt32 size = 32);

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextPixmapFace object. */
    inline TextPixmapFace();

    /** Destroys the %TextPixmapFace object. */
    virtual ~TextPixmapFace();

    /** The size of the face in pixels */
    UInt32 _size;

    /** Defines a map of glyphs */
    typedef std::map<TextGlyph::Index, TextPixmapGlyph*> GlyphMap;

    /** The map of glyphs */
    GlyphMap _glyphMap;

    /**
     * Creates a new Glyph object.
     * This method has to be implemented by descendants of the %TextPixmapFace class.
     * @param glyphIndex The index of the glyph.
     * @return The glyph object or 0 when no glyph exists for the given
     * glyph index.
     */
    virtual std::auto_ptr<TextPixmapGlyph> createGlyph(TextGlyph::Index glyphIndex) = 0;

    /** An empty glyph */
    static TextPixmapGlyph _emptyGlyph;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextPixmapFace(const TextPixmapFace &);

    /** Copy operator (not implemented!) */
    const TextPixmapFace &operator=(const TextPixmapFace &);
};


OSG_END_NAMESPACE


#include "OSGTextPixmapFace.inl"

#define OSGTEXTPIXMAPFACE_HEADER_CVSID "@(#)$Id: OSGTextPixmapFace.h,v 1.1.4.2 2006/05/08 06:01:15 vossg Exp $"

#endif /* _OSGTEXTPIXMAPFACE_H_ */
