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


#ifndef _OSGDEFAULTFONT_H_
#define _OSGDEFAULTFONT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGTextDef.h"
#include "OSGTextureObjChunk.h"
#include "OSGSingletonHolder.h"
#include "OSGTextTXFFace.h"

OSG_BEGIN_NAMESPACE

class OSG_TEXT_DLLMAPPING DefaultFontBase
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
    DefaultFontBase();

    /** Copy constructor (not implemented!) */
    DefaultFontBase(const DefaultFontBase &);

    /** Destroys the DefaultFontBase object. */
    ~DefaultFontBase();

    /** Copy operator (not implemented!) */
    const DefaultFontBase &operator=(const DefaultFontBase &);

    /** The default face used for statistics */
    TextTXFFaceRefPtr       _face;

    /** Texture object chunk that keeps the texture for the default font */
    TextureObjChunkMTRecPtr _texObjChunk;
};

#if defined(WIN32)
OSG_TEXT_EXPIMP_TMPL 
template class OSG_TEXT_DLLMAPPING SingletonHolder<DefaultFontBase>;
#endif

typedef SingletonHolder<DefaultFontBase> DefaultFont;

OSG_END_NAMESPACE

#include "OSGDefaultFont.inl"

#endif /* _OSGDEFAULTFONT_H_ */
