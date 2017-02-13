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


OSG_BEGIN_NAMESPACE

//! Returns the center of a box

void BoxVolume::getCenter(Pnt3f &center) const
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

Real32 BoxVolume::getScalarVolume() const
{
    return (isEmpty() == true) ? 0.0f : (_max[0] - _min[0]) *
                                        (_max[1] - _min[1]) *
                                        (_max[2] - _min[2]);
}


void BoxVolume::getBounds(Pnt3f &min, Pnt3f &max) const
{
    min = _min;
    max = _max;
}

void BoxVolume::getCorners(Pnt3f &nlt,    Pnt3f &nlb,
                           Pnt3f &nrt,    Pnt3f &nrb,
                           Pnt3f &flt,    Pnt3f &flb,
                           Pnt3f &frt,    Pnt3f &frb ) const
{
    nlt.setValues(_min[0], _max[1], _min[2]);
    nlb.setValues(_min[0], _min[1], _min[2]);
    nrt.setValues(_max[0], _max[1], _min[2]);
    nrb.setValues(_max[0], _min[1], _min[2]);

    flt.setValues(_min[0], _max[1], _max[2]);
    flb.setValues(_min[0], _min[1], _max[2]);
    frt.setValues(_max[0], _max[1], _max[2]);
    frb.setValues(_max[0], _min[1], _max[2]);
}

Pnt3f BoxVolume::getCorner(Corner cornerId) const
{
    Pnt3f cornerPnt;
    switch (cornerId)
    {
        case NEAR_LEFT_BOTTOM:
            cornerPnt.setValues(_min[0], _min[1], _min[2]);
            break;
        case NEAR_RIGHT_BOTTOM:
            cornerPnt.setValues(_max[0], _min[1], _min[2]);
            break;
        case NEAR_RIGHT_TOP:
            cornerPnt.setValues(_max[0], _max[1], _min[2]);
            break;
        case NEAR_LEFT_TOP:
            cornerPnt.setValues(_min[0], _max[1], _min[2]);
            break;
        case FAR_LEFT_BOTTOM:
            cornerPnt.setValues(_min[0], _min[1], _max[2]);
            break;
        case FAR_RIGHT_BOTTOM:
            cornerPnt.setValues(_max[0], _min[1], _max[2]);
            break;
        case FAR_RIGHT_TOP:
            cornerPnt.setValues(_max[0], _max[1], _max[2]);
            break;
        case FAR_LEFT_TOP:
            cornerPnt.setValues(_min[0], _max[1], _max[2]);
            break;
        default:
            SWARNING << "BoxVolume::getCorner: invalid corner type!" << std::endl;
    }
    return cornerPnt;
}

Plane BoxVolume::getPlane(AABBPlane planeId) const
{
    Plane plane;

    switch (planeId)
    {
        case PLANE_NEAR:
            plane.set( 0.f, 0.f,-1.f,-_min[2]);
            break;
        case PLANE_FAR:
            plane.set( 0.f, 0.f, 1.f, _max[2]);
            break;
        case PLANE_LEFT:
            plane.set(-1.f, 0.f, 0.f,-_min[0]);
            break;
        case PLANE_RIGHT:
            plane.set( 1.f, 0.f, 0.f, _max[0]);
            break;
        case PLANE_BOTTOM:
            plane.set( 0.f,-1.f, 0.f,-_min[1]);
            break;
        case PLANE_TOP:
            plane.set( 0.f, 1.f, 0.f, _max[1]);
            break;
        default:
            SWARNING << "BoxVolume::getPlane: invalid plane type!" << std::endl;
    }

    return plane;
}

//! set method
void BoxVolume::setBoundsByCenterAndSize(const Pnt3f &center,
                                         const Vec3f &size)
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

void BoxVolume::extendBy(const Pnt3f &pt)
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

    _min[0] = osgMin(pt[0], _min[0]);
    _min[1] = osgMin(pt[1], _min[1]);
    _min[2] = osgMin(pt[2], _min[2]);

    _max[0] = osgMax(pt[0], _max[0]);
    _max[1] = osgMax(pt[1], _max[1]);
    _max[2] = osgMax(pt[2], _max[2]);
}

void BoxVolume::extendBy(const Volume &volume)
{
    OSG::extend(*this,volume);
}

/*-------------------------- intersection ---------------------------------*/

//! Returns true if intersection of given point and Box3f is not empty

bool BoxVolume::intersect(const Pnt3f &pt) const
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
    Real32 enter;
    Real32 exit;

    return line.intersect(*this, enter, exit);
}



/*! intersect the box with the given Line */

bool BoxVolume::intersect(const Line   &line, 
                                Real32 &min, 
                                Real32 &max) const
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


bool BoxVolume::isOnSurface (const Pnt3f &point) const
{
    if(((osgAbs(point[0] - _min[0]) < TypeTraits<Real32>::getDefaultEps() ||
         osgAbs(point[0] - _max[0]) < TypeTraits<Real32>::getDefaultEps()   ) &&
        (point[1] >= _min[1] && point[1] <= _max[1]                     &&
         point[2] >= _min[2] && point[2] <= _max[2]                   )   ) ||

       ((osgAbs(point[1] - _min[1]) < TypeTraits<Real32>::getDefaultEps() ||
         osgAbs(point[1] - _max[1]) < TypeTraits<Real32>::getDefaultEps()   ) &&
        (point[0] >= _min[0] && point[0] <= _max[1]                     &&
         point[2] >= _min[2] && point[2] <= _max[2]                    )   ) ||

       ((osgAbs(point[2] - _min[2]) < TypeTraits<Real32>::getDefaultEps() ||
         osgAbs(point[2] - _max[2]) < TypeTraits<Real32>::getDefaultEps()   ) &&
        (point[1] >= _min[1] && point[1] <= _max[1]                     &&
         point[0] >= _min[0] && point[0] <= _max[0]                   )   )   )
    {
        return true;
    }
    else
    {
        return false;
    }
}


//! Transforms Box3f by matrix, enlarging Box3f to contain result

void BoxVolume::transform(const Matrix &m)
{
    if(isEmpty() == true)
        return;

    Pnt3f  newMin(m[3][0], m[3][1], m[3][2]);
    Pnt3f  newMax(m[3][0], m[3][1], m[3][2]);
    Real32 a;
    Real32 b;

    for(UInt32 i = 0; i < 3; ++i)
    {
        for(UInt32 j = 0; j < 3; ++j)
        {
            a = _max[j] * m[j][i];
            b = _min[j] * m[j][i];

            if(a >= b)
            {
                newMax[i] += a;
                newMin[i] += b;
            }
            else
            {
                newMax[i] += b;
                newMin[i] += a;
            }
        }
    }

    _min = newMin;
    _max = newMax;
}

//! Assignment operator

BoxVolume &BoxVolume::operator =(const BoxVolume &b1)
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
    print(PLOG);
}

void BoxVolume::print(std::ostream &os) const
{
    os << "Box(" << _min << "|" << _max << ")";
    printState(os);
}

//! Equality comparisons

bool BoxVolume::operator ==(const BoxVolume &rhs) const
{
    return ((_min[0] == rhs._min[0]) &&
            (_min[1] == rhs._min[1]) &&
            (_min[2] == rhs._min[2]) &&
            (_max[0] == rhs._max[0]) &&
            (_max[1] == rhs._max[1]) &&
            (_max[2] == rhs._max[2])   );
}


OSG_END_NAMESPACE
