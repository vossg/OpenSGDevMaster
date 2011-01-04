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

#ifndef _OSGTEXTTXFGLYPH_H_
#define _OSGTEXTTXFGLYPH_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"

#include "OSGTextGlyph.h"


OSG_BEGIN_NAMESPACE


/**
 * Defines a TXF glyph.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextGlyphs
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextTXFGlyph: public TextGlyph
{

  /** Needs access to constructor */
  friend class TextTXFFace;

    /*==========================  PUBLIC  =================================*/
  public:

    /** Destroys a %TextTXFGlyph object. */
    virtual ~TextTXFGlyph(void);

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
     * Returns the x position of the glyph in the texture.
     * @return The x position of the glyph in the texture
     */
    inline UInt32 getX(void) const;

    /**
     * Returns the y position of the glyph in the texture.
     * @return The y position of the glyph in the texture
     */
    inline UInt32 getY(void) const;

    /**
     * Returns the width of the glyph in pixels.
     * @return The width of the glyph
     */
    inline UInt32 getPixmapWidth(void) const;

    /**
     * Returns the height of the glyph in pixels.
     * @return The height of the glyph
     */
    inline UInt32 getPixmapHeight(void) const;

    /**
     * Returns the x bearing of the glyph in pixels for horizontal layout.
     * The x bearing is the distance from the origin to the left border
     * of the glyph.
     * @return The x bearing of the glyph for horizontal layout
     */
    inline Int32 getPixmapHoriBearingX(void) const;

    /**
     * Returns the y bearing of the glyph in pixels for horizontal layout.
     * The y bearing is the distance from the origin to the top border
     * of the glyph.
     * @return The y bearing of the glyph for horizontal layout
     */
    inline Int32 getPixmapHoriBearingY(void) const;

    /**
     * Returns the x bearing of the glyph in pixels for vertical layout.
     * The x bearing is the distance from the origin to the left border
     * of the glyph.
     * @return The x bearing of the glyph for vertical layout
     */
    inline Int32 getPixmapVertBearingX(void) const;

    /**
     * Returns the y bearing of the glyph in pixels for vertical layout.
     * The y bearing is the distance from the origin to the top border
     * of the glyph.
     * @return The y bearing of the glyph for vertical layout
     */
    inline Int32 getPixmapVertBearingY(void) const;

    /**
     * Returns the scale factor.
     * @return The scale factor
     */
    inline Real32 getScale(void) const;

    /** Defines the coordinate indices */
    enum CoordIndex 
    {
        COORD_LEFT = 0, 
        COORD_TOP = 1, 
        COORD_RIGHT = 2, 
        COORD_BOTTOM = 3 
    };

    /**
     * Returns a texture coordinate.
     * @param index The index of the texture coordinate (must be between 0 and
     *              3, inclusively)
     * @return The texture coordinate
     */
    inline Real32 getTexCoord(UInt32 index) const;

    /**
     * Returns a coordinate.
     * @param index The index of the coordinate (must be between 0 and 3,
     * inclusively)
     * @return The coordinate
     */
    inline Real32 getCoord(UInt32 index) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextTXFGlyph object. */
    TextTXFGlyph(void);

    /** The width of the glyph in pixels */
    UInt32 _width;

    /** The height of the glyph in pixels */
    UInt32 _height;

    /** The x bearing of the glyph in pixels for horizontal layout */
    Int32 _horiBearingX;

    /** The y bearing of the glyph in pixels for horizontal layout */
    Int32 _horiBearingY;

    /** The x bearing of the glyph in pixels for vertical layout */
    Int32 _vertBearingX;

    /** The y bearing of the glyph in pixels for vertical layout */
    Int32 _vertBearingY;

    /** The x position of the glyph in the texture in pixels */
    UInt32 _x;

    /** The y position of the glyph in the texture in pixels */
    UInt32 _y;

    /** The scaling factor */
    Real32 _scale;

    /** The texture coordinates */
    Real32 _texCoord[4];

    /** Calculates coordinates */
    void calculateCoordinates(UInt32 textureWidth, UInt32 textureHeight);

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextTXFGlyph(const TextTXFGlyph &);

    /** Copy operator (not implemented!) */
    const TextTXFGlyph &operator=(const TextTXFGlyph &);
};


OSG_END_NAMESPACE


#include "OSGTextTXFGlyph.inl"

#endif /* _OSGTEXTTXFGLYPH_H_ */
