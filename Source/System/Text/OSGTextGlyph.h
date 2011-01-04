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

#ifndef _OSGTEXTGLYPH_H_
#define _OSGTEXTGLYPH_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"


OSG_BEGIN_NAMESPACE


/**
 * Abstract base class of all glyphes.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextGlyphs
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextGlyph
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Defines the glyph index */
    typedef Int32 Index;

    /** Defines the invalid glyph index */
    enum { INVALID_INDEX = -1 };

    /** Destroys the %Glyph object. */
    virtual ~TextGlyph();

    /**
     * Returns the index of the glyph.
     * @return The index of the glyph
     */
    inline Index getGlyphIndex() const;

    /**
     * Returns the advance of the glyph for horizontal layout. The
     * advance is the distance to the next character on the base line.
     * @return The advance for horizontal layout
     */
    inline Real32 getHoriAdvance() const;

    /**
     * Returns the advance of the glyph for vertical layout. The
     * advance is the distance to the next character on the base line.
     * This value is usually negative!
     * @return The advance for vertical layout
     */
    inline Real32 getVertAdvance() const;

    /**
     * Returns the width of the glyph.
     * @return The width of the glyph
     */
    virtual Real32 getWidth() const = 0;

    /**
     * Returns the height of the glyph.
     * @return The height of the glyph
     */
    virtual Real32 getHeight() const = 0;

    /**
     * Returns the x bearing of the glyph for horizontal layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingX() const = 0;

    /**
     * Returns the y bearing of the glyph for horizontal layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for horizontal layout
     */
    virtual Real32 getHoriBearingY() const = 0;

    /**
     * Returns the x bearing of the glyph for vertical layout.
     * The x bearing is the distance from the origin to the left
     * border of the glyph.
     * @return The x bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingX() const = 0;

    /**
     * Returns the y bearing of the glyph for vertical layout.
     * The y bearing is the distance from the origin to the top
     * border of the glyph.
     * @return The y bearing of the glyph for vertical layout
     */
    virtual Real32 getVertBearingY() const = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %Glyph object. */
    inline TextGlyph();

    /** The index of the glyph */
    Index _glyphIndex;

    /** The advance of the glyph for horizontal layout */
    Real32 _horiAdvance;

    /** The advance of the glyph for vertical layout */
    Real32 _vertAdvance;

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextGlyph(const TextGlyph &other);

    /** Copy operator (not implemented!) */
    const TextGlyph &operator=(const TextGlyph &other);
};


OSG_END_NAMESPACE


#include "OSGTextGlyph.inl"

#endif /* _OSGTEXTGLYPH_H_ */
