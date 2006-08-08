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


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include <assert.h>

#include "OSGCylinderVolume.h"
#include "OSGPlane.h"
#include "OSGMatrix.h"

OSG_USING_NAMESPACE


void CylinderVolume::getCenter(Pnt3r &center) const
{
    center = _axisPos + _axisDir * .5f;
}


Real CylinderVolume::getScalarVolume(void) const
{
    return isEmpty() ? 0.0f : (_radius * _radius * Pi * _axisDir.length());
}

/*! gives the boundaries of the volume */

void CylinderVolume::getBounds(Pnt3r &min, Pnt3r &max) const
{
    for(UInt32 i = 0; i < 3; i++) 
    {
        min[i] = _axisPos[i] - _radius;
        max[i] = _axisPos[i] + _radius;

        ((_axisDir[i] < 0.f) ? min[i] : max[i]) += _axisDir[i];
    }    
}

/*-------------------------- extending ------------------------------------*/

#ifdef __sgi
#pragma set woff 1209
#endif

/*! extends (if necessary) to contain the given 3D point */

void CylinderVolume::extendBy(const Pnt3r &OSG_CHECK_ARG(pt))
{
    assert(false);
}


void CylinderVolume::extendBy(const Volume &volume)
{
  OSG::extend(*this, volume);
}

#ifdef __sgi
#pragma reset woff 1209
#endif


/*-------------------------- intersection ---------------------------------*/

/*! Returns true if intersection of given point and CylinderVolume 
    is not empty
*/

bool CylinderVolume::intersect(const Pnt3r &point) const
{
	Real dist = Line(_axisPos, _axisDir).distance(point);

    if(dist > _radius)
        return false;

    Plane bottom( _axisDir, _axisPos           );
    Plane top   (-_axisDir, _axisPos + _axisDir);

    bool inspace = bottom.isInHalfSpace(point) && top.isInHalfSpace(point);

    return inspace;
}


/*! intersect the CylinderVolume with the given Line */

bool CylinderVolume::intersect(const Line &line) const
{
    return line.intersect(*this);
}

/*! intersect the volume with the given Line */

bool CylinderVolume::intersect(const Line        &line,
                                     Real &enter, 
                                     Real &exit ) const
{
    return line.intersect(*this, enter, exit);
}

bool CylinderVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this,volume);
}


bool CylinderVolume::isOnSurface(const Pnt3r &point) const
{
    Real dist = Line(_axisPos, _axisDir).distance(point);

    if(dist > _radius)
        return false;
    
    Plane bottom(-_axisDir, _axisPos           );
    Plane top   ( _axisDir, _axisPos + _axisDir);

    bool onplane = bottom.isOnPlane(point) || top.isOnPlane(point);

    return  ( onplane &&  dist <= _radius            ) ||
            (!onplane && osgabs(dist - _radius) < Eps);
}

/*-------------------------- transformation -------------------------------*/

/*! transform volume by the given matrix */
void CylinderVolume::transform(const Matrixr &mtx)
{
     // get pos & axis
    Pnt3r p;
    Vec3r v, v2, v3;

    getAxis(p,v);
     
     // find perpendicular vector (to detect radius transformation)
    v2 = v;
    v2.normalize();
    v3 = v2.x() > 0.9f ? Vec3f(0,1,0) : Vec3f(1,0,0);
    v3.crossThis(v2);
    
    // transform
    mtx.mult(p);
    mtx.mult(v);
    mtx.mult(v3);
     
    // update
    setAxis(p,v);
    setRadius(getRadius() * v3.length());
}

#ifdef __sgi
#pragma reset woff 1209
#endif

//! print the volume 

void CylinderVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    PLOG << "Cylinder(" 
         << _axisPos 
         << "|" 
         << _axisDir
         << "|" 
         << _radius
         << ")";
}





