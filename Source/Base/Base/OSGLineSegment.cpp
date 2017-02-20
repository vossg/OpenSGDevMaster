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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cmath>

#include "OSGConfig.h"

#include <cassert>

#include "OSGLineSegment.h"

#include "OSGPlane.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"
#include "OSGFrustumVolume.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::LineSegment
     A line segment is a line between two points.
*/

/*-------------------------- constructor ----------------------------------*/

LineSegment::LineSegment()
: _startPoint(0.f, 0.f ,0.f)
,  _direction(0.f, 0.f, 0.f)
{
}


LineSegment::LineSegment(const LineSegment& rhs)
: _startPoint(rhs._startPoint)
, _direction (rhs._direction)
{
}


LineSegment::LineSegment(const Pnt3f& p0, const Pnt3f& p1)
: _startPoint(p0)
, _direction (p1-p0)
{
}


LineSegment::LineSegment(const Pnt3f& startPoint, const Vec3f &direction)
: _startPoint(startPoint)
, _direction (direction)
{
}

/*--------------------------- destructor ----------------------------------*/

LineSegment::~LineSegment()
{
}

/*---------------------------------------------------------------------------*/
/* Operators                                                                 */

LineSegment &LineSegment::operator=(const LineSegment &rhs)
{
    if (this == &rhs)
        return *this;

    _startPoint = rhs._startPoint;
    _direction  = rhs._direction;

    return *this;
}

/*------------------------------ feature ----------------------------------*/

void LineSegment::setValue(const Pnt3f &p0, const Pnt3f &p1)
{
    _startPoint = p0;
    _direction  = p1 - p0;
}


void LineSegment::setValue(const Pnt3f &pos, const Vec3f &dir)
{
    _startPoint = pos;
    _direction  = dir;
}

/*! Transform the LineSegment by the given matrix
 */
void LineSegment::transform(const Matrix4f &mat)
{
    Pnt3f pos;
    Vec3f dir;

    mat.multFull(_startPoint, pos);
    mat.mult    (_direction,  dir);

    Real32 length = dir.length();

    if(length < TypeTraits<Real32>::getDefaultEps())
        SWARNING << "LineSegment::transform: Near-zero scale!" << std::endl;

    setValue(pos, dir);
}

OSG_BASE_DLLMAPPING
std::ostream &operator <<(std::ostream &outStream, const LineSegment &obj)
{
    return outStream << obj.getStartPoint() << ":" << obj.getDirection();
}

OSG_END_NAMESPACE





