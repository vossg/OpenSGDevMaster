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

#include <cassert>

#include "OSGCylinderVolume.h"
#include "OSGPlane.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE


void CylinderVolume::getCenter(Pnt3f &center) const
{
    center = _axisPos + _axisDir * .5f;
}


Real32 CylinderVolume::getScalarVolume(void) const
{
    return isEmpty() ? 0.0f : (_radius * _radius * Pi * _axisDir.length());
}

/*! gives the boundaries of the volume */

void CylinderVolume::getBounds(Pnt3f &min, Pnt3f &max) const
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

void CylinderVolume::extendBy(const Pnt3f &OSG_CHECK_ARG(pt))
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

bool CylinderVolume::intersect(const Pnt3f &point) const
{
	Real32 dist = Line(_axisPos, _axisDir).distance(point);

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

bool CylinderVolume::intersect(const Line   &line,
                                     Real32 &enter, 
                                     Real32 &exit ) const
{
    return line.intersect(*this, enter, exit);
}

bool CylinderVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this,volume);
}


bool CylinderVolume::isOnSurface(const Pnt3f &point) const
{
    Real32 dist = Line(_axisPos, _axisDir).distance(point);

    if(dist > _radius)
        return false;
    
    Plane bottom(-_axisDir, _axisPos           );
    Plane top   ( _axisDir, _axisPos + _axisDir);

    bool onplane = bottom.isOnPlane(point) || top.isOnPlane(point);

    return
      ( onplane && dist                   <= _radius                          ) ||
      (!onplane && osgAbs(dist - _radius) <  TypeTraits<
                                                      Real32>::getDefaultEps());
}

/*-------------------------- transformation -------------------------------*/

/*! transform volume by the given matrix */
void CylinderVolume::transform(const Matrix &mtx)
{
     // get pos & axis
    Pnt3f p;
    Vec3f v, v2, v3;

    getAxis(p,v);
     
     // find perpendicular vector (to detect radius transformation)
    v2 = v;
    v2.normalize();
    v3 = v2.x() > 0.9f ? Vec3f(0.f,1.f,0.f) : Vec3f(1.f,0.f,0.f);
    v3.crossThis(v2);
    
    // transform
    mtx.mult(p,  p );
    mtx.mult(v,  v );
    mtx.mult(v3, v3);
     
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
    print(PLOG);
}

void CylinderVolume::print(std::ostream &os) const
{
    os << "Cylinder (" << _axisPos
       << "|"          << _axisDir
       << "|"          << _radius
       << ")";
    printState(os);
}

/*---------------------------------------------------------------------------*/
/* Operators                                                                 */

bool CylinderVolume::operator ==(const CylinderVolume &rhs) const
{
    return (_axisPos == rhs._axisPos) &&
           (_axisDir == rhs._axisDir) &&
           (_radius  == rhs._radius );
}

CylinderVolume &CylinderVolume::operator =(const CylinderVolume &source)
{
    if(this == &source)
        return *this;
    
    _axisPos = source._axisPos;
    _axisDir = source._axisDir;
    _radius  = source._radius;
    
    return *this;
}
 
OSG_END_NAMESPACE
