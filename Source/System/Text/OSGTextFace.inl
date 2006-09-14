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


OSG_BEGIN_NAMESPACE


inline const std::string TextFace::getFamily() const { return _family; }


inline TextFace::Style TextFace::getStyle() const { return _style; }


inline Real32 TextFace::getHoriAscent() const { return _horiAscent; }


inline Real32 TextFace::getVertAscent() const { return _vertAscent; }


inline Real32 TextFace::getHoriDescent() const { return _horiDescent; }


inline Real32 TextFace::getVertDescent() const { return _vertDescent; }


inline TextFace::TextFace()
: _family(), _style(STYLE_PLAIN),
  _horiAscent(0.f), _vertAscent(0.f),
  _horiDescent(0.f), _vertDescent(0.f)
{}


OSG_END_NAMESPACE


#define OSGTEXTFACE_INLINE_CVSID "@(#)$Id$"
