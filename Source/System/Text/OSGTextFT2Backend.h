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

#ifndef _OSGTEXTFT2BACKEND_H_
#define _OSGTEXTFT2BACKEND_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"


#if defined(OSG_WITH_FT2) || defined(OSG_DO_DOC)


#include "OSGTextBackend.h"
#ifndef OSG_WITH_FONTCONFIG
# include <map>
#endif
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>


OSG_BEGIN_NAMESPACE


/**
 * Backend that uses the Freetype 2 library.
 * Developers do not use this backend directly, instead,
 * they use the interface of the TextFace classes to
 * create fonts.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextBackends
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextFT2Backend: public TextBackend
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Creates a new %TextFT2Backend object. */
    TextFT2Backend(void);

    /** Destroys the %TextFT2Backend object. */
    virtual ~TextFT2Backend(void);

    /**
     * Creates a new vector face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @return The vector face object or 0 in case of an error.
     */
    virtual TextVectorFaceTransitPtr
    createVectorFace(const std::string     &family,
                           TextFace::Style  style  );

    /**
     * Creates a new pixmap face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param size The size of the pixmap font in pixels.
     * @return The pixmap face object or 0 in case of an error.
     */
    virtual TextPixmapFaceTransitPtr
    createPixmapFace(const std::string     &family,
                           TextFace::Style  style,
                           UInt32           size   );

    /**
     * Creates a new TXF face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param param Some parameters that affect the creation of the
     * TXF face.
     * @return The TXF face object or 0 in case of an error.
     */
    virtual TextTXFFaceTransitPtr
    createTXFFace(const std::string     &family,
                        TextFace::Style  style,
                  const TextTXFParam    &param  );

    /**
     * Returns the names of all font families available.
     * @param families A vector that gets filled with the names
     * of all font families.
     */
    virtual void getFontFamilies(std::vector<std::string> &families);

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextFT2Backend(const TextFT2Backend &);

    /** Copy operator (not implemented!) */
    const TextFT2Backend &operator=(const TextFT2Backend &);

    /** Tries to find the path and the index of a font */
    bool findPath(const std::string &family, TextFace::Style style, std::string &path, int &index);

    /** Tries to create a freetype2 face */
    FT_Face createFace(const std::string &family, TextFace::Style style, FT_UInt size);

    /** Freetype library object */
    FT_Library _library;

#ifndef OSG_WITH_FONTCONFIG

    /** The list of directories that get scanned for fonts */
    std::string _pathList;

    /** True when we need to scan for fonts */
    bool _scanForFonts;

    /** Keeps information about a font 
     *
     * \nohierarchy
     */

    typedef struct
    {
        std::string path;
        int index;
        TextFace::Style style;
    }
    FontInfo;

    /** Defines the map of fonts */
    typedef std::multimap<std::string, FontInfo> FontMap;

    /** The map of fonts */
    FontMap _fontMap;

    /** Scans the font search path for fonts. */
    void scanForFonts(void);

    /**
     * Scans a directory and its subdirectories for fonts.
     * @param path The path of the directory.
     */
    void scanDir(const std::string &path);

    /**
     * Checks if a file is a font.
     * @param fullname The filename
     */
    void checkFile(const std::string &fullname);

#endif // !OSG_WITH_FONTCONFIG

};


OSG_END_NAMESPACE


#endif // OSG_WITH_FT2


#include "OSGTextFT2Backend.inl"

#endif /* _OSGTEXTFT2BACKEND_H_ */
