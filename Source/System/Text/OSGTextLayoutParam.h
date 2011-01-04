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

#ifndef _OSGTEXTLAYOUTPARAM_H_
#define _OSGTEXTLAYOUTPARAM_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"

#include <vector>


OSG_BEGIN_NAMESPACE


/**
 * Keeps the parameters for the layout operation. For more information
 * about these parameters, the the documentation for the VRML Text and
 * FontStyle nodes - all parameters correspond to fields of these nodes
 * and have exactly the same meaning.
 * 
 * See: http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-VRML97/part1/nodesRef.html#Text
 * See: http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-VRML97/part1/nodesRef.html#FontStyle
 *
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextLayout
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextLayoutParam
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Defines the layout alignment */
    enum Alignment
    {
        ALIGN_FIRST,
        ALIGN_BEGIN,
        ALIGN_MIDDLE,
        ALIGN_END
    };

    /** Creates a new %TextLayoutParam object. */
    inline TextLayoutParam();

    /** The direction of the layout */
    bool horizontal;

    /** The x direction of the layout */
    bool leftToRight;

    /** The x direction of the layout */
    bool topToBottom;

    /** The major alignment of the layout */
    Alignment majorAlignment;

    /** The minor alignment of the layout */
    Alignment minorAlignment;

    /** The line spacing */
    Real32 spacing;

    /** The length of the text lines */
    std::vector<Real32> length;

    /**
     * Sets the length of the first line and sets the size
     * of the length vector to one. Use this method when you
     * lay out a single line of text.
     * @param l The length of the first line.
     */
    inline void setLength(Real32 l);

    /**
     * Returns the length of a single line.
     * @param index The index of the line, starting at 0. When
     * the index is larger then the size of the length vector,
     * this method returns 0.
     * @return The length of the single line.
     */
    inline Real32 getLength(UInt32 index = 0) const;

    /** The maximum extend of all lines */
    Real32 maxExtend;
};


OSG_END_NAMESPACE


#include "OSGTextLayoutParam.inl"

#endif /* _OSGTEXTLAYOUTPARAM_H_ */
