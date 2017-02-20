/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

inline
Real32 OrthographicProjection::getLeft() const
{
    return _left;
}

inline
void OrthographicProjection::setLeft(Real32 left)
{
    _left = left;
}

inline
Real32 OrthographicProjection::getRight() const
{
    return _right;
}

inline
void OrthographicProjection::setRight(Real32 right)
{
    _right = right;
}

inline
Real32 OrthographicProjection::getBottom() const
{
    return _bottom;
}

inline
void OrthographicProjection::setBottom(Real32 bottom)
{
    _bottom = bottom;
}

inline
Real32 OrthographicProjection::getTop() const
{
    return _top;
}

inline
void OrthographicProjection::setTop(Real32 top)
{
    _top = top;
}

OSG_END_NAMESPACE
