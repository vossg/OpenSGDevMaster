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

#ifndef _OSGTEXTBACKEND_H_
#define _OSGTEXTBACKEND_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"

#include "OSGTextFace.h"

#include <string>
#include <vector>


OSG_BEGIN_NAMESPACE


class TextVectorFace;
class TextPixmapFace;
class TextTXFFace;
class TextTXFParam;

/*! \ingroup GrpTextFaces
 */
typedef RefCountPtr<TextVectorFace,
                    MemObjRefCountPolicy> TextVectorFaceRefPtr;
/*! \ingroup GrpTextFaces
 */
typedef TransitPtr <TextVectorFace      > TextVectorFaceTransitPtr;

/*! \ingroup GrpTextFaces
 */
typedef RefCountPtr<TextPixmapFace,
                    MemObjRefCountPolicy> TextPixmapFaceRefPtr;
/*! \ingroup GrpTextFaces
 */
typedef TransitPtr <TextPixmapFace      > TextPixmapFaceTransitPtr;

/*! \ingroup GrpTextFaces
 */
typedef RefCountPtr<TextTXFFace,
                    MemObjRefCountPolicy> TextTXFFaceRefPtr;
/*! \ingroup GrpTextFaces
 */
typedef TransitPtr <TextTXFFace         > TextTXFFaceTransitPtr;

/**
 * Abstract base class of all backends.
 * Developers only use this class to implement new
 * Backends.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextBackends
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextBackend
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Destroys the %TextBackend object. */
    virtual ~TextBackend();

    /**
     * Creates a new vector face. Descendants of the %TextBackend class
     * have to override this method with their own implementation.
     * The default implementation of the %TextBackend class always
     * return 0.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @return The vector face object or 0 in case of an error.
     */
    virtual TextVectorFaceTransitPtr
    createVectorFace(const std::string &family, TextFace::Style style);

    /**
     * Creates a new pixmap face. Descendants of the %TextBackend class
     * have to override this method with their own implementation.
     * The default implementation of the %TextBackend class always
     * returns 0.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param size The size of the pixmap font in pixels.
     * @return The pixmap face object or 0 in case of an error.
     */
    virtual TextPixmapFaceTransitPtr
    createPixmapFace(const std::string &family, TextFace::Style style, UInt32 size);

    /**
     * Creates a new TXF face. Descendants of the %TextBackend class
     * have to override this method with their own implementation.
     * The default implementation of the %TextBackend class always
     * returns 0.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param param Some parameters that affect the creation of the
     * TXF face.
     * @return The TXF face object or 0 in case of an error.
     */
    virtual TextTXFFaceTransitPtr
    createTXFFace(const std::string &family, TextFace::Style style, const TextTXFParam &param);

    /**
     * Returns the names of all font families available.
     * @param families A vector that gets filled with the names
     * of all font families.
     */
    virtual void getFontFamilies(std::vector<std::string> &families) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    /** Creates a new %TextBackend object. */
    inline TextBackend(void);

    /*==========================  PRIVATE  ================================*/
  private:

    /** Copy constructor (not implemented!) */
    TextBackend(const TextBackend &);

    /** Copy operator (not implemented!) */
    const TextBackend &operator=(const TextBackend &);
};


OSG_END_NAMESPACE


#include "OSGTextBackend.inl"

#endif /* _OSGTEXTBACKEND_H_ */
