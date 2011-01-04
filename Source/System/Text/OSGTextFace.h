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

#ifndef _OSGTEXTFACE_H_
#define _OSGTEXTFACE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGContainerForwards.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGTransitPtr.h"

#include "OSGTextGlyph.h"

#include <string>
#include <vector>


OSG_BEGIN_NAMESPACE


class TextLayoutParam;
class TextLayoutResult;


/**
 * Abstract base class of all faces.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextFaces
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextFace : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef MemoryObject                            Inherited;
    typedef TextFace                                Self;

    typedef TransitPtr <Self                      > ObjTransitPtr;
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
      
    /** Defines the styles of a face */
    enum Style
    {
        STYLE_PLAIN,
        STYLE_BOLD,
        STYLE_ITALIC,
        STYLE_BOLDITALIC
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /**
     * Returns the actual font family of the face.
     * @return The font family.
     */
    inline const std::string getFamily(void) const;

    /**
     * Returns the actual style of the face.
     * @return The style.
     */
    inline Style getStyle(void) const;

    /**
     * Returns the ascent of the face for horizontal layout. The ascent
     * is the distance from the baseline to the top of the face.
     * @return The ascent for horizontal layout.
     */
    inline Real32 getHoriAscent(void) const;

    /**
     * Returns the ascent of the face for vertical layout. The ascent
     * is the distance from the baseline to the left side of the face.
     * This value is usually negative!
     * @return The ascent for vertical layout.
     */
    inline Real32 getVertAscent(void) const;
    
    /**
     * Returns the descent of the face for horizontal layout. The descent
     * is the distance from the baseline to the bottom of the face.
     * This value is usually negative!
     * @return The descent for horizontal layout.
     */
    inline Real32 getHoriDescent(void) const;

    /**
     * Returns the descent of the face for vertical layout. The descent
     * is the distance from the baseline to the right side of the face.
     * @return The descent for vertical layout.
     */
    inline Real32 getVertDescent(void) const;

    /**
     * Returns information about a glyph.
     * @param glyphIndex The index of the glyph. Use the layout method
     * to get the glyph indices corresponding to a character string.
     * @return A glyph object containing information about the glyph.
     */
    virtual const TextGlyph &getGlyph(TextGlyph::Index glyphIndex) = 0;

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
                        TextLayoutResult &result) = 0;

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
     * Calculates the bounding box of a text after layout.
     * @param layoutResult The results of the layout operation
     * @param lowerLeft After returning from the method, contains the lower left
     * position of the bounding box
     * @param upperRight After returning from the method, contains the lower left
     * position of the bounding box
     */
    void calculateBoundingBox(const TextLayoutResult &layoutResult, Vec2f &lowerLeft, Vec2f &upperRight);

    /**
     * Converts a UTF8 encoded string to a unicode string.
     * @param utf8Text The UTF8 encoded text string.
     * @param text A string that gets filled with the unicode
     * version of the UTF8 encoded string.
     */
    static void convertUTF8ToUnicode(const std::string &utf8Text, std::wstring &text);

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextFace object. */
    inline TextFace(void);

    /** Destroys the %TextFace object. */
    virtual ~TextFace(void);
    
    /** The font family of the face */
    std::string _family;

    /** The style of the face */
    Style _style;

    /** The ascent of the font for horizontal layout */
    Real32 _horiAscent;

    /** The ascent of the font for vertical layout */
    Real32 _vertAscent;
    
    /** The descent of the font for horizontal layout */
    Real32 _horiDescent;
    
    /** The descent of the font for vertical layout */
    Real32 _vertDescent;

    /**
     * Justifies one line of text.
     * @param param The current layout parameters
     * @param spaceIndices The indices of space characters in the line
     * @param currPos The position on the base line behind the last
     * character
     * @param layoutResult The glyph positions that get justified
     * by this method.
     */
    void justifyLine(const TextLayoutParam &param,
                     const std::vector<UInt32> &spaceIndices,
                     Vec2f &currPos, TextLayoutResult &layoutResult) const;

    /**
     * Adjusts the positions of glyphs, depending on the alignment.
     * @param param The current layout parameters
     * @param currPos The position on the base line behind the last
     * character
     * @param layoutResult The glyph positions that gets adjusted
     * by this method.
     */
    void adjustLineOrigin(const TextLayoutParam &param,
                          const Vec2f &currPos,
                          TextLayoutResult &layoutResult) const;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextFace(const TextFace &);

    /** Copy operator (not implemented!) */
    const TextFace &operator=(const TextFace &);
};

typedef TextFace::ObjTransitPtr TextFaceTransitPtr;
typedef TextFace::ObjRefPtr     TextFaceRefPtr;

OSG_END_NAMESPACE

#include "OSGTextFace.inl"

#endif /* _OSGTEXTFACE_H_ */
