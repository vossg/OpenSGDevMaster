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

#ifndef _OSGTEXTFACEFACTORY_H_
#define _OSGTEXTFACEFACTORY_H_

#ifdef _MSC_VER
# pragma once
#endif


#include "OSGConfig.h"
#include "OSGTextDef.h"
#include "OSGBaseTypes.h"
#include "OSGSingletonHolder.h"

#include "OSGTextFace.h"
#include "OSGTextTXFParam.h"

#include <map>
#include <vector>
#include <string>

using namespace std;
OSG_BEGIN_NAMESPACE


class TextBackend;
class TextVectorFace;
class TextPixmapFace;
class TextTXFFace;

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
 * A singleton used to create new faces. The %TextFaceFactory
 * keeps a cache of all currently created faces. When creating
 * a new face, the factory first searches in the cache if the
 * face already exists. If yes, it returns that face. If no, it
 * creates a new face, adds it to the cache, and returns it.
 * Usually you do not use the %TextFaceFactory singleton directly,
 * instead you use the create method of the TextFace classes.
 * @author Patrick D&auml;hne
 * 
 * \ingroup GrpTextFactory
 * \ingroup GrpLibOSGText
 */

class OSG_TEXT_DLLMAPPING TextFaceFactoryBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /**
     * Tries to create a vector face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @return The vector face object or 0 in case of an error.
     */
    TextVectorFaceTransitPtr
    createVectorFace(const std::string     &family,
                           TextFace::Style  style = TextFace::STYLE_PLAIN);

    /**
     * Tries to create a pixmap face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param size The size of the pixmap font in pixels.
     * @return The pixmap face object or 0 in case of an error.
     */
    TextPixmapFaceTransitPtr
    createPixmapFace(const std::string     &family,
                           TextFace::Style  style  = TextFace::STYLE_PLAIN,
                           UInt32           size   = 32                    );

    /**
     * Tries to create a TXF face.
     * @param family The font family of the face (Arial, Courier etc.)
     * @param style The style of the face (bold, italic etc.)
     * @param param Parameters that affect the creation of the
     * TXF face.
     * @return The TXF face object or 0 in case of an error.
     */
    TextTXFFaceTransitPtr
    createTXFFace(const std::string     &family,
                        TextFace::Style  style = TextFace::STYLE_PLAIN,
                  const TextTXFParam    &param = TextTXFParam()        );

    /** Removes all faces from the face cache. */
    void clearCache(void);

    /**
     * Returns the names of all font families available.
     * @param families A vector that gets filled with the names
     * of all font families.
     */
    void getFontFamilies(std::vector<std::string> &families) const;

    /*==========================  PRIVATE  ================================*/
  private:

    template <class SingletonT>
    friend class SingletonHolder;

    /** Default Constructor */
    TextFaceFactoryBase(void);

    /** Copy constructor (not implemented!) */
    TextFaceFactoryBase(const TextFaceFactoryBase &);

    /** Destroys the %TextFaceFactoryBase object. */
    ~TextFaceFactoryBase(void);

    /** Copy operator (not implemented!) */
    const TextFaceFactoryBase &operator=(const TextFaceFactoryBase &);

    /** The backend that creates all faces */
    TextBackend *_backend;

    /** Defines the map that contains the vector faces */
    typedef std::multimap<std::string, TextVectorFaceRefPtr> VectorFaceMap;

    /** The map of vector faces currently instantiated (face cache) */
    VectorFaceMap _vectorFaceMap;

    /** Defines the map that contains the pixmap faces */
    typedef std::multimap<std::string, TextPixmapFaceRefPtr> PixmapFaceMap;

    /** The map of pixmap faces currently instanciated (face cache) */
    PixmapFaceMap _pixmapFaceMap;

    /** Defines the map that contains the TXF faces */
    typedef std::multimap<std::string, TextTXFFaceRefPtr> TXFFaceMap;

    /** The map of TXF faces currently instantiated (face cache) */
    TXFFaceMap _txfFaceMap;
};

/*! \typedef OSG::SingletonHolder<OSG::TextFaceFactoryBase> TextFaceFactory;
    \ingroup GrpTextFactory
    \relatesalso OSG::TextFaceFactoryBase
 */

typedef SingletonHolder<TextFaceFactoryBase> TextFaceFactory;

OSG_END_NAMESPACE


#include "OSGTextFaceFactory.inl"

#endif /* _OSGTEXTFACEFACTORY_H_ */
