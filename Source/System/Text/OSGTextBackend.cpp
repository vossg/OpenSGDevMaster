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

#include "OSGTextBackend.h"


using namespace std;


OSG_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// Destructor
// Author: pdaehne
//----------------------------------------------------------------------
TextBackend::~TextBackend() {}


//----------------------------------------------------------------------
// Creates a new vector face
// Author: pdaehne
//----------------------------------------------------------------------
TextVectorFace *TextBackend::createVectorFace(const string &family,
                                              TextFace::Style style)
{ return 0; }


//----------------------------------------------------------------------
// Creates a new pixmap face
// Author: pdaehne
//----------------------------------------------------------------------
TextPixmapFace *TextBackend::createPixmapFace(const string &family,
                                              TextFace::Style style,
                                              UInt32 size)
{ return 0; }


//----------------------------------------------------------------------
// Creates a new TXF face
// Author: pdaehne
//----------------------------------------------------------------------
TextTXFFace *TextBackend::createTXFFace(const string &family,
                                        TextFace::Style style,
                                        const TextTXFParam &param)
{ return 0; }


OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static OSG::Char8 cvsid_cpp[] = "@(#)$Id$";
    static OSG::Char8 cvsid_hpp[] = OSGTEXTBACKEND_HEADER_CVSID;
    static OSG::Char8 cvsid_inl[] = OSGTEXTBACKEND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
