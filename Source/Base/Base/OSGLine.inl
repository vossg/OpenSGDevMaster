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

#ifndef _OSGLINE_INL_
#define _OSGLINE_INL_

OSG_BEGIN_NAMESPACE

/*! Accessors for position
 */

inline
const Pnt3f &Line::getPosition(void) const
{
    return _pos;
}

inline
Pnt3f Line::getPoint(Real32 t) const
{
    return _pos + t * _dir;
}

/*! Accessors for direction
 */

inline
const Vec3f &Line::getDirection(void) const
{
    return _dir;
}

inline
bool Line::operator !=(const Line &rhs) const
{
    return !(*this == rhs);
}

inline
bool Line::equals(const Line &rhs, Real32 tolerance) const
{
    return (
                _pos.equals(rhs._pos, tolerance) && 
                _dir.equals(rhs._dir, tolerance)
           )
           || 
           (
                _pos.equals(rhs._pos + rhs._dir, tolerance) && 
                rhs._pos.equals(_pos + _dir, tolerance)
           );
}

OSG_END_NAMESPACE

#endif // LINE_CLASS_DECLARATION

