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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include <assert.h>

#include "OSGSphereVolume.h"

#include "OSGQuaternion.h"
#include "OSGLine.h"
#include "OSGBoxVolume.h"
#include "OSGLog.h"
#include "OSGMatrix.h"

OSG_USING_NAMESPACE

#if 0
/*! Return a sphere containing a given box */
void SphereVolume::circumscribe(const BoxVolume &box)
{
    float radius = 0.5 * (box.getMax() - box.getMin()).length();
    Vec3f center;

    box.getCenter(center);

    setValue(center, radius);
}
#endif

/*! Returns the center */

void SphereVolume::getCenter(Pnt3r &center) const
{
    center = _center;
}


Real SphereVolume::getScalarVolume (void) const
{
    return isEmpty() ? 0.0f : (4.f / 3.f * Pi * _radius * _radius * _radius);
}


void SphereVolume::getBounds(Pnt3r &min, Pnt3r &max) const
{
    min.setValues(_center[0] - _radius,
                  _center[1] - _radius,
                  _center[2] - _radius);
    max.setValues(_center[0] + _radius,
                  _center[1] + _radius,
                  _center[2] + _radius);
}


void SphereVolume::extendBy(const Pnt3r &pt)
{
    if(isUntouchable() == true)
        return;
    
    if(isEmpty() == true)
    {
        _center = pt;
        _radius = 0.f;
        
        setEmpty(false);
    }
    else
    {
        Real d = (_center - pt).length();
        
        if(d > _radius)
            _radius = d;
    }
}


void SphereVolume::extendBy(const Volume &volume)
{
    OSG::extend(*this, volume);
}

/*------------------------- intersection ------------------------------*/

/*! Returns true if intersection of given point and Volume is not empty */

bool SphereVolume::intersect(const Pnt3r &point) const
{
    Real d = (_center - point).length();

    if(d <= _radius)
        return true;
    else
        return false;
}

/*! intersect the SphereVolume with the given Line */

bool SphereVolume::intersect(const Line &line) const
{
    return line.intersect(*this);
}

/*! intersect the SphereVolume with the given Line */

bool SphereVolume::intersect(const Line &line,
                                   Real &enter, 
                                   Real &exit ) const
{
    return line.intersect(*this, enter, exit);
}


bool SphereVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this, volume);
}


bool SphereVolume::isOnSurface (const Pnt3r &point) const
{
    if(osgabs((point - _center).length() - _radius) < Eps)
        return true;
    else
        return false;
}


/*-------------------------- transformation -------------------------------*/

void SphereVolume::transform(const Matrixr &mat)
{
    // assume uniform scaling, otherways we get an ellipsoid
    Pnt3r hull(_center);

    hull += Vec3r(0.f, _radius, 0.f);

    mat.mult(_center);
    mat.mult(hull);

    _radius = (hull - _center).length();

/*
    Vec3f translation, scaleFactor;
    Quaternion rotation, scaleOrientation;
    
    mat.mult(_center);
    mat.getTransform(translation, rotation, scaleFactor, scaleOrientation);
    _radius *= scaleFactor[0];
*/
}

/*! print the volume */
void SphereVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                        const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    PLOG << "Sphere(" << _center << "|" << _radius << ")";
}
