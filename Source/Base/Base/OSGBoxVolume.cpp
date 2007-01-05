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

#include "OSGConfig.h"

#include <cassert>

#include "OSGBoxVolume.h"
#include "OSGLine.h"
#include "OSGMatrix.h"


/*! \class OSG::BoxVolume

    A volume encompassing an axis-aligned box. The box is defined by the 
    point with the smallest coordinates (OSG::BoxVolume::_min) and the point
    with the largest coordinates (OSG::BoxVolume::_max).
*/


OSG_USING_NAMESPACE


//! Returns the center of a box

void BoxVolume::getCenter(Pnt3r &center) const
{
    if(isEmpty() == true)
    {
        center.setValues(0.0f, 0.0f, 0.0f);
    }
    else
    {
        center = _min + (_max - _min) * .5f;
    }
}

//! Gives the volume of the box (0 for an empty box)

Real BoxVolume::getScalarVolume() const
{
    return (isEmpty() == true) ? 0.0f : (_max[0] - _min[0]) *
                                        (_max[1] - _min[1]) *
                                        (_max[2] - _min[2]);
}


void BoxVolume::getBounds(Pnt3r &min, Pnt3r &max) const
{
    min = _min;
    max = _max;
}


//! set method
void BoxVolume::setBoundsByCenterAndSize(const Pnt3r &center,
                                         const Vec3r &size)
{
    _min.setValues(center.x() - size.x() / 2.0f,
                   center.y() - size.y() / 2.0f,
                   center.z() - size.z() / 2.0f);
    _max.setValues(center.x() + size.x() / 2.0f,
                   center.y() + size.y() / 2.0f,
                   center.z() + size.z() / 2.0f);

    Volume::setValid   (true);
    Volume::setEmpty   (size.isZero());
    Volume::setInfinite(false);
}


/*-------------------------- extending ------------------------------------*/

//! Extends Box3f (if necessary) to contain given 3D point

void BoxVolume::extendBy(const Pnt3r &pt)
{
    if(isUntouchable() == true)
        return;

    if(isEmpty() == true)
    {
        _min[0] = _max[0] = pt[0];
        _min[1] = _max[1] = pt[1];
        _min[2] = _max[2] = pt[2];

        setEmpty(false);

        return;
    }

    if(pt[0] < _min[0])
    {
        _min[0] = pt[0];
    }
    else
    {
        if(pt[0] > _max[0])
            _max[0] = pt[0];
    }

    if(pt[1] < _min[1])
    {
        _min[1] = pt[1];
    }
    else
    {
        if(pt[1] > _max[1])
            _max[1] = pt[1];
    }

    if(pt[2] < _min[2])
    {
        _min[2] = pt[2];
    }
    else
    {
        if(pt[2] > _max[2])
            _max[2] = pt[2];
    }
}


void BoxVolume::extendBy(const Volume &volume)
{
    OSG::extend(*this,volume);
}

/*-------------------------- intersection ---------------------------------*/

//! Returns true if intersection of given point and Box3f is not empty

bool BoxVolume::intersect(const Pnt3r &pt) const
{
    return 
        (!isEmpty()      &&
        (_min[0] < pt[0] && _max[0] > pt[0]) &&
        (_min[1] < pt[1] && _max[1] > pt[1]) &&
        (_min[2] < pt[2] && _max[2] > pt[2]));
}

/*! intersect the box with the given Line */

bool BoxVolume::intersect(const Line &line) const
{
    Real enter;
    Real exit;

    return line.intersect(*this, enter, exit);
}



/*! intersect the box with the given Line */

bool BoxVolume::intersect(const Line &line, 
                                Real &min, 
                                Real &max) const
{
    return line.intersect(*this, min, max);
}


bool BoxVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this, volume);
}


bool BoxVolume::intersect(const BoxVolume &volume) const
{
    return OSG::intersect(*this, volume);
}


bool BoxVolume::isOnSurface (const Pnt3r &point) const
{
    if(((osgAbs(point[0] - _min[0]) < Eps           ||
         osgAbs(point[0] - _max[0]) < Eps             ) &&
        (point[1] >= _min[1] && point[1] <= _max[1] &&
         point[2] >= _min[2] && point[2] <= _max[2]   )   ) ||

       ((osgAbs(point[1] - _min[1]) < Eps           ||
         osgAbs(point[1] - _max[1]) < Eps             ) &&
        (point[0] >= _min[0] && point[0] <= _max[1] &&
         point[2] >= _min[2] && point[2] <= _max[2]   )   ) ||

       ((osgAbs(point[2] - _min[2]) < Eps           ||
         osgAbs(point[2] - _max[2]) < Eps             ) &&
        (point[1] >= _min[1] && point[1] <= _max[1] &&
         point[0] >= _min[0] && point[0] <= _max[0]   )   )   )
    {
        return true;
    }
    else
    {
        return false;
    }
}


//! Transforms Box3f by matrix, enlarging Box3f to contain result

void BoxVolume::transform(const Matrixr &m)
{
    Real xmin;
    Real ymin;
    Real zmin;
    Real xmax;
    Real ymax;
    Real zmax;
    Real a;
    Real b;

    if(isEmpty() == true)
        return;

    xmin = xmax = m[3][0];
    ymin = ymax = m[3][1];
    zmin = zmax = m[3][2];

    //
    // calculate xmin and xmax of new tranformed BBox
    //

    a = _max[0] * m[0][0];
    b = _min[0] * m[0][0];

    if(a >= b)
    {
        xmax += a;
        xmin += b;
    }
    else
    {
        xmax += b;
        xmin += a;
    }

    a = _max[1] * m[1][0];
    b = _min[1] * m[1][0];

    if(a >= b) 
    {
        xmax += a;
        xmin += b;
    }
    else
    {
        xmax += b;
        xmin += a;
    }
    
    a = _max[2] * m[2][0];
    b = _min[2] * m[2][0];

    if(a >= b)
    {
        xmax += a;
        xmin += b;
    }
    else
    {
        xmax += b;
        xmin += a;
    }

    //
    // calculate ymin and ymax of new tranformed BBox
    //

    a = _max[0] * m[0][1];
    b = _min[0] * m[0][1];

    if(a >= b)
    {
        ymax += a;
        ymin += b;
    }
    else
    {
        ymax += b;
        ymin += a;
    }

    a = _max[1] * m[1][1];
    b = _min[1] * m[1][1];

    if(a >= b)
    {
        ymax += a;
        ymin += b;
    }
    else
    {
        ymax += b;
        ymin += a;
    }

    a = _max[2] * m[2][1];
    b = _min[2] * m[2][1];

    if(a >= b)
    {
        ymax += a;
        ymin += b;
    }
    else
    {
        ymax += b;
        ymin += a;
    }

    //
    // calculate zmin and zmax of new tranformed BBox
    //

    a = _max[0] * m[0][2];
    b = _min[0] * m[0][2];

    if(a >= b) 
    {
        zmax += a;
        zmin += b;
    }
    else
    {
        zmax += b;
        zmin += a;
    }

    a = _max[1] * m[1][2];
    b = _min[1] * m[1][2];

    if(a >= b)
    {
        zmax += a;
        zmin += b;
    }
    else
    {
        zmax += b;
        zmin += a;
    }

    a = _max[2] * m[2][2];
    b = _min[2] * m[2][2];

    if(a >= b)
    {
        zmax += a;
        zmin += b;
    }
    else
    {
        zmax += b;
        zmin += a;
    }

    _min.setValues(xmin, ymin, zmin);
    _max.setValues(xmax, ymax, zmax);
}

//! Assignment operator

const BoxVolume &BoxVolume::operator =(const BoxVolume &b1)
{
    if(&b1 == this)
        return *this;

    _min   = b1._min;
    _max   = b1._max;
    _state = b1._state;

    return *this;
}

//! print the volume 

void BoxVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                     const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    PLOG << "Box(" << _min << "|" << _max << ")";
}


OSG_BEGIN_NAMESPACE

//! Equality comparisons

bool operator ==(const BoxVolume &b1, const BoxVolume &b2)
{
    return ((b1._min[0] == b2._min[0]) &&
            (b1._min[1] == b2._min[1]) &&
            (b1._min[2] == b2._min[2]) &&
            (b1._max[0] == b2._max[0]) &&
            (b1._max[1] == b2._max[1]) &&
            (b2._max[2] == b2._max[2])   );
}


OSG_END_NAMESPACE
