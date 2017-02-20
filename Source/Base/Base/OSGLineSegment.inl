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

#ifndef _OSGLINESEGMENT_INL_
#define _OSGLINESEGMENT_INL_

OSG_BEGIN_NAMESPACE

inline
const Pnt3f& LineSegment::getStartPoint() const
{
    return _startPoint;
}

inline
const Pnt3f LineSegment::getEndPoint() const
{
    return _startPoint + _direction;
}

/*! Accessors for direction
 */

inline
const Vec3f& LineSegment::getDirection() const
{
    return _direction;
}

inline
Pnt3f LineSegment::getPoint(Real32 t) const
{
    return _startPoint + t * _direction;
}

inline
void LineSegment::setStartPoint(const Pnt3f& p)
{
    _startPoint = p;
}

inline
void LineSegment::setEndPoint(const Pnt3f& p)
{
    _direction = p - _startPoint;
}

/*! Warning: operator!= does not test for semantic but for bitwise
             equality.
*/
inline
bool LineSegment::operator!=(const LineSegment &rhs) const
{
    return !(*this == rhs);
}

/*! Warning: operator== does not test for semantic but for bitwise
             equality.
*/
inline
bool LineSegment::operator==(const LineSegment &rhs) const
{
    return _startPoint == rhs._startPoint && _direction == rhs._direction;
 }

/*! This operation performs a semantic equal test respecting the given
    tolerance.
*/
inline
bool LineSegment::equals(const LineSegment &rhs, Real32 tolerance) const
{
    return (
                _startPoint.equals(rhs._startPoint, tolerance) &&
                _direction. equals(rhs._direction,  tolerance)
           )
           ||
           (
                    _startPoint.equals(rhs._startPoint + rhs._direction, tolerance) &&
                rhs._startPoint.equals(    _startPoint +     _direction, tolerance)
           );
}

OSG_END_NAMESPACE

#endif // _OSGLINESEGMENT_INL_

