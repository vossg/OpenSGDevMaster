/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGSTATISTICSDEFAULTFONT_H_
#define _OSGSTATISTICSDEFAULTFONT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGUtilDef.h"
#include "OSGTextureObjChunk.h"
#include "OSGSingletonHolder.h"

OSG_BEGIN_NAMESPACE

class TextTXFFace;

class OSG_UTIL_DLLMAPPING StatisticsDefaultFontBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /** Returns the default face. */
    inline TextTXFFace *getFace() const;

    /**
     * Returns the texture object chunk that keeps the texture for the
	 * default font.
     */
    inline TextureObjChunk *getTexture() const;

    /*==========================  PRIVATE  ================================*/
  private:

    template <class SingletonT>
    friend class SingletonHolder;

    /** Default Constructor */
    StatisticsDefaultFontBase();

    /** Copy constructor (not implemented!) */
    StatisticsDefaultFontBase(const StatisticsDefaultFontBase &);

    /** Destroys the StatisticsDefaultFontBase object. */
    ~StatisticsDefaultFontBase();

    /** Copy operator (not implemented!) */
    const StatisticsDefaultFontBase &operator=(const StatisticsDefaultFontBase &);

    /** The default face used for statistics */
    TextTXFFace *_face;

    /** Texture object chunk that keeps the texture for the default font */
    TextureObjChunkMTRecPtr _texObjChunk;
};

#if defined(WIN32)
#    if !defined(OSG_COMPILEUTILLIB)
OSG_SYSTEM_EXPIMP_TMPL 
template class OSG_SYSTEM_DLLMAPPING SingletonHolder<StatisticsDefaultFontBase>;
#    endif
#endif

typedef SingletonHolder<StatisticsDefaultFontBase> StatisticsDefaultFont;

OSG_END_NAMESPACE

#include "OSGStatisticsDefaultFont.inl"

#endif /* _OSGSTATISTICSDEFAULTFONT_H_ */
