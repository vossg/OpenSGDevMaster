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

#ifndef _OSGTEXTPIXMAPGLYPH_H_
#define _OSGTEXTPIXMAPGLYPH_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"

#include "OSGTextGlyph.h"


OSG_BEGIN_NAMESPACE


/**
 * Defines a pixmap glyph.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextGlyphs
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextPixmapGlyph: public TextGlyph
{

  /** Needs access to constructor */
  friend class TextPixmapFace;

    /*==========================  PUBLIC  =================================*/
  public:

    /** Destroys the %TextPixmapGlyph object. */
    virtual ~TextPixmapGlyph();

    /**
     * Returns the width of the glyph.
     * @return The width of the glyph
     */
    virtual Real32 getWidth() const;

    /**
     * Returns the height of the glyph.
     * @return The height of the glyph
     */
    virtual Real32 getHeight() const;

    /**
     * Returns the x bearing of the glyph for horizontal layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingX() const;

    /**
     * Returns the y bearing of the glyph for horizontal layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingY() const;

    /**
     * Returns the x bearing of the glyph for vertical layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingX() const;

    /**
     * Returns the y bearing of the glyph for vertical layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingY() const;

    /**
     * Returns the width of the pixmap in pixels.
     * @return The width of the pixmap in pixels
     */
    inline UInt32 getPixmapWidth() const;

    /**
     * Returns the pitch of the pixmap (the number of bytes
     * per row).
     * @return The pitch of the pixmap
     */
    inline UInt32 getPixmapPitch() const;

    /**
     * Returns the height of the pixmap in pixels.
     * @return The height of the pixmap in pixels
     */
    inline UInt32 getPixmapHeight() const;

    /**
     * Returns the x bearing of the glyph in pixels for horizontal layout.
     * The x bearing is the distance from the origin to the left border
     * of the glyph.
     * @return The x bearing of the glyph for horizontal layout
     */
    //inline Int32 getPixmapHoriBearingX() const;

    /**
     * Returns the y bearing of the glyph in pixels for horizontal layout.
     * The y bearing is the distance from the origin to the top border
     * of the glyph.
     * @return The y bearing of the glyph for horizontal layout
     */
    //inline Int32 getPixmapHoriBearingY() const;

    /**
     * Returns the x bearing of the glyph in pixels for vertical layout.
     * The x bearing is the distance from the origin to the left border
     * of the glyph.
     * @return The x bearing of the glyph for verical layout
     */
    //inline Int32 getPixmapVertBearingX() const;

    /**
     * Returns the y bearing of the glyph in pixels for vertical layout.
     * The y bearing is the distance from the origin to the top border
     * of the glyph.
     * @return The y bearing of the glyph for vertical layout
     */
    //inline Int32 getPixmapVertBearingY() const;

    /**
     * Returns the pixmap.
     * @return The pixmap
     */
    inline const UInt8 *getPixmap() const;

    /**
     * Copies the glyph pixmap into a texture.
     * @param x The x position in the texture in pixels
     * @param y The y position in the texture in pixels
     * @param tex The texture
     * @param width The width of the texture in pixels
     * @param height The height of the texture in pixels
     */
    void putPixmap(Int32 x, Int32 y, UInt8 *tex, UInt32 width, 
                   UInt32 height) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextPixmapGlyph object. */
    inline TextPixmapGlyph();

    /** Flips the glyph pixmap around the x axis. */
    void flipPixmap();

    /** The width of the pixmap in pixels */
    UInt32 _width;

    /** The pitch of the pixmap (number of bytes per row) */
    UInt32 _pitch;

    /** The height of the pixmap in pixels */
    UInt32 _height;

    /** The x bearing of the pixmap in pixels for horizontal layout */
    Int32 _horiBearingX;

    /** The y bearing of the pixmap in pixels for horizontal layout */
    Int32 _horiBearingY;

    /** The x bearing of the pixmap in pixels for vertical layout */
    Int32 _vertBearingX;

    /** The y bearing of the pixmap in pixels for vertical layout */
    Int32 _vertBearingY;

    /** The pixmap */
    UInt8 *_pixmap;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextPixmapGlyph(const TextPixmapGlyph &);

    /** Copy operator (not implemented!) */
    const TextPixmapGlyph &operator=(const TextPixmapGlyph &);
};


OSG_END_NAMESPACE


#include "OSGTextPixmapGlyph.inl"

#endif /* _OSGTEXTPIXMAPGLYPH_H_ */
