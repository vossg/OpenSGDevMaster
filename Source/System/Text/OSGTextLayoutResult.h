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

#ifndef _OSGTEXTLAYOUTRESULT_H_
#define _OSGTEXTLAYOUTRESULT_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"

#include "OSGTextGlyph.h"

#include <vector>


OSG_BEGIN_NAMESPACE


/**
 * Keeps the result of a layout operation.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextLayout
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextLayoutResult
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Creates a new %TextLayoutResult object. */
    inline TextLayoutResult();

    /** Clears the %TextLayoutResult object. */
    void clear();

    /** The glyph indices */
    std::vector<TextGlyph::Index> indices;

    /** The positions of the glyphs */
    std::vector<Vec2f> positions;

    /**
     * Returns the number of glyph indices that have a
     * corresponding position.
     * @return The number of glyphs.
     */
    inline UInt32 getNumGlyphs() const;

    /** The line bounds */
    std::vector<Vec2f> lineBounds;

    /** The text bounds */
    Vec2f textBounds;
};


OSG_END_NAMESPACE


#include "OSGTextLayoutResult.inl"

#endif /* _OSGTEXTLAYOUTRESULT_H_ */
