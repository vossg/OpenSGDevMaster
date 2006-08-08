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


inline TextLayoutParam::TextLayoutParam()
: horizontal(true), leftToRight(true), topToBottom(true),
  majorAlignment(ALIGN_FIRST), minorAlignment(ALIGN_FIRST), spacing(1.f),
  length(), maxExtend(0.f)
{}


inline void TextLayoutParam::setLength(Real32 l)
{ length.assign(1, l); }


inline Real32 TextLayoutParam::getLength(UInt32 index) const
{ return index >= length.size() ? 0.f : length[index]; }


OSG_END_NAMESPACE


#define OSGTEXTLAYOUTPARAM_INLINE_CVSID "@(#)$Id: OSGTextLayoutParam.inl,v 1.1.4.2 2006/05/08 06:01:15 vossg Exp $"
