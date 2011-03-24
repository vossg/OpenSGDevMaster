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

#ifdef _MSC_VER
# pragma warning (disable: 4786)
#endif

#include "OSGTextFaceFactory.h"
#include "OSGTextBackend.h"
#include "OSGTextVectorFace.h"
#include "OSGTextPixmapFace.h"
#include "OSGTextTXFFace.h"
#include "OSGTextWIN32Backend.h"
#include "OSGTextMacBackend.h"
#include "OSGTextFT2Backend.h"

#include "OSGSingletonHolder.ins"

#ifdef __sgi
# include <cassert>
#else
# include <cassert>
#endif

OSG_BEGIN_NAMESPACE


OSG_SINGLETON_INST(TextFaceFactoryBase, addPreFactoryExitFunction)

template class SingletonHolder<TextFaceFactoryBase>;


//----------------------------------------------------------------------
// Constructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFaceFactoryBase::TextFaceFactoryBase(void)
    : _backend      (),
      _vectorFaceMap(),
      _pixmapFaceMap(),
      _txfFaceMap   ()
{
#if defined(_WIN32)
    _backend = new TextWIN32Backend();
#elif defined(__APPLE__)
# ifdef __LP64__
    _backend = new TextFT2Backend();
# else
    _backend = new TextMacBackend();
    //_backend = new TextFT2Backend();
# endif
#elif defined(OSG_WITH_FT2)
    _backend = new TextFT2Backend();
#else
    _backend = 0;
#endif
}


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextFaceFactoryBase::~TextFaceFactoryBase(void)
{
    clearCache();
    delete _backend;
}


//----------------------------------------------------------------------
// Returns a vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFaceTransitPtr TextFaceFactoryBase::createVectorFace(
    const string &family, TextFace::Style style)
{
    // Try to find the face in the cache
    pair<VectorFaceMap::iterator, VectorFaceMap::iterator> range = _vectorFaceMap.equal_range(family);
    VectorFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if (it->second->getStyle() == style)
            return TextVectorFaceTransitPtr(it->second);
    }

    // We did not find the face in the cache, so let the backend create it
    if (_backend == 0)
        return TextVectorFaceTransitPtr();
    
    TextVectorFaceRefPtr face = _backend->createVectorFace(family, style);
    if (face == 0)
        return TextVectorFaceTransitPtr();
    _vectorFaceMap.insert(VectorFaceMap::value_type(family, face));
    
    return TextVectorFaceTransitPtr(face);
}


//----------------------------------------------------------------------
// Returns a pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFaceTransitPtr TextFaceFactoryBase::createPixmapFace(
    const string &family, TextFace::Style style, UInt32 size)
{
    // Try to find the face in the cache
    pair<PixmapFaceMap::iterator, PixmapFaceMap::iterator> range = _pixmapFaceMap.equal_range(family);
    PixmapFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if ((it->second->getStyle() == style) && (it->second->getSize() == size))
            return TextPixmapFaceTransitPtr(it->second);
    }

    // We did not find the face in the cache, so let the backend create it
    if(_backend == 0)
        return TextPixmapFaceTransitPtr();
    
    TextPixmapFaceRefPtr face = _backend->createPixmapFace(family, style, size);
    if (face == 0)
        return TextPixmapFaceTransitPtr();
    _pixmapFaceMap.insert(PixmapFaceMap::value_type(family, face));

    return TextPixmapFaceTransitPtr(face);
}


//----------------------------------------------------------------------
// Returns a TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFaceTransitPtr TextFaceFactoryBase::createTXFFace(
    const string &family, TextFace::Style style, const TextTXFParam &param)
{
    // Try to find the face in the cache
    pair<TXFFaceMap::iterator, TXFFaceMap::iterator> range = _txfFaceMap.equal_range(family);
    TXFFaceMap::iterator it;
    for (it = range.first; it != range.second; ++it)
    {
        assert(it->second != 0);
        if ((it->second->getStyle() == style) && (it->second->getParam() == param))
            return TextTXFFaceTransitPtr(it->second);
    }

    // We did not find the face in the cache, so let the backend create it
    if (_backend == 0)
        return TextTXFFaceTransitPtr();
    
    TextTXFFaceRefPtr face = _backend->createTXFFace(family, style, param);
    if (face == 0)
        return TextTXFFaceTransitPtr();
    _txfFaceMap.insert(TXFFaceMap::value_type(family, face));
    
    return TextTXFFaceTransitPtr(face);
}


//----------------------------------------------------------------------
// Removes all faces from the face cache
// Author: pdaehne
//----------------------------------------------------------------------
void TextFaceFactoryBase::clearCache(void)
{
    _vectorFaceMap.clear();
    _pixmapFaceMap.clear();
    _txfFaceMap   .clear();
}


//----------------------------------------------------------------------
// Returns the names of all font families available
// Author: pdaehne
//----------------------------------------------------------------------
void TextFaceFactoryBase::getFontFamilies(vector<string> &families) const
{
    families.clear();
    if (_backend != 0)
        _backend->getFontFamilies(families);
}


OSG_END_NAMESPACE
