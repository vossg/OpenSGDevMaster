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

#ifndef _OSGTEXTWIN32BACKEND_H_
#define _OSGTEXTWIN32BACKEND_H_

#include "OSGConfig.h"
#include "OSGTextDef.h"


#ifdef _MSC_VER
# pragma once
#endif


#if defined(_WIN32) || defined(OSG_DO_DOC)


#include "OSGTextBackend.h"
#include <windows.h>


OSG_BEGIN_NAMESPACE


class EnumData;


/**
 * Backend that uses WIN32 system calls.
 * Developers do not use this backend directly, instead,
 * they use the interface of the TextFaceFactory object to
 * create new fonts.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextBackends
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextWIN32Backend: public TextBackend
{
  /** Needs access to hDC_ */
  friend class TextWIN32VectorFace;

  /** Needs access to hDC_ */
  friend class TextWIN32PixmapFace;

  /** Needs access to hDC_ */
  friend class TextWIN32TXFFace;

    /*==========================  PUBLIC  =================================*/
  public:

    /**
     * Creates a new %TextWIN32Backend object.
     */
    TextWIN32Backend();

    /** Destroys the %TextWIN32Backend object. */
    virtual ~TextWIN32Backend();

    /**
     * Creates a new vector face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @return The vector face object or 0 in case of an error.
     */
    virtual TextVectorFaceTransitPtr
    createVectorFace(const std::string &family, TextFace::Style style);

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
                           UInt32           size  );

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
                  const TextTXFParam    &param);

    /**
     * Returns the names of all font families available.
     * @param families A vector that gets filled with the names
     * of all font families.
     */
    virtual void getFontFamilies(std::vector<std::string> &families);

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextWIN32Backend(const TextWIN32Backend &);

    /** Copy operator (not implemented!) */
    const TextWIN32Backend &operator=(const TextWIN32Backend &);

    /** Enumerates fonts */
    void enumerateFonts(const std::string &family, EnumData &enumData);

    /** Creates horizontal and vertical fonts */
    void createFonts(const std::string     &family, 
                           UInt32           size, 
                           TextFace::Style  style,
                           HFONT           &hHoriFont, 
                           HFONT           &hVertFont);

    /** Device context */
    HDC _hDC;
};


OSG_END_NAMESPACE


#endif // _WIN32


#include "OSGTextWIN32Backend.inl"

#endif /* _OSGTEXTWIN32BACKEND_H_ */
