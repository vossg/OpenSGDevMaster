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

#ifndef _OSGTEXTTXFPARAM_H_
#define _OSGTEXTTXFPARAM_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGTextFace.h"

#include <string>


OSG_BEGIN_NAMESPACE


/**
 * Defines a set of parameters used when creating new
 * TXF faces.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextFaces
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextTXFParam
{
    /*==========================  PUBLIC  =================================*/
  public:

    /**
     * Creates a new TextTXFParam object.
     */
    inline TextTXFParam(void);

    /** The size of the glyphs in pixels */
    UInt32 size;

    /** The gap between glyphs in pixels */
    UInt32 gap;

    /** The width of the texture in pixels */
    UInt32 textureWidth;

    /**
     * Sets the characters contained in the texture.
     * @param utf8Characters The UTF-8 encoded characters contained in the
     *                       texture. 
     */
    inline void setCharacters(const std::string &utf8Characters);

    /**
     * Sets the characters contained in the texture.
     * @param characters The unicode characters contained in the texture.
     */
    inline void setCharacters(const std::wstring &characters);

    /**
     * Returns the characters contained in the texture.
     * @return The characters contained in the texture.
     */
    inline const std::wstring &getCharacters(void) const;

    /**
     * Compares the TextTXFParam object with another TextTXFParam object.
     * @param other The other %TextTXFParam object.
     * @return true when both %TextTXFParam objects are the same.
     */
    bool operator==(const TextTXFParam &other) const;

    /*==========================  PRIVATE  ================================*/
  private:

    /** The characters contained in the texture */
    std::wstring _characters;

    /** The default character set */
    static std::wstring _defaultCharacters;

    /** Sorts the characters in the character string and removes duplicates */
    void normalizeCharacters(void);
};


OSG_END_NAMESPACE


#include "OSGTextTXFParam.inl"

#endif /* _OSGTEXTTXFPARAM_H_ */
