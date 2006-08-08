/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include "OSGVolume.h"

#include "OSGPolytopeVolume.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*------------------------------ feature ----------------------------------*/

/// set method
void PolytopeVolume::setPlane(const Plane& p, const UInt16 i)
{
    if(i>=_numPlanes)
    {
        std::cerr << "\nARGL!\n\n";
        return;
    }
    _planes[i]=p;
}

/// Returns the center of a box
void PolytopeVolume::getCenter(Pnt3f &OSG_CHECK_ARG(center)) const
{
    // not implemented
    return;
}

/// Gives the volume of the frustum
Real32 PolytopeVolume::getScalarVolume() const
{
    // not implemented
    return 0.0;
}

/// Gives the boundaries of the volume
void PolytopeVolume::getBounds(Pnt3f &OSG_CHECK_ARG(minPnt), 
                              Pnt3f &OSG_CHECK_ARG(maxPnt)) const
{
    // not implemented !!!
    return;
}

/*-------------------------- extending ------------------------------------*/

/// Extends Frustum3f (if necessary) to contain given 3D point
void PolytopeVolume::extendBy(const Pnt3f &OSG_CHECK_ARG(pt))
{
    // not implemented !!!
    return;
}

/*-------------------------- intersection ---------------------------------*/

/// Returns true if intersection of given point and Frustum3f is not empty
bool PolytopeVolume::intersect(const Pnt3f &point) const
{
    int i;
    bool retCode = true;

    for (i = 0; i < _numPlanes; i++)
    {
      /*
    if ( ( _planes[i].getNormal().x() * point.x() +
                     _planes[i].getNormal().y() * point.x() +
                     _planes[i].getNormal().z() * point.x() +
                     _planes[i].getDistanceFromOrigin()) < 0 ) {
      retCode = false;
      break;
    }
   */
        if(_planes[i].isInHalfSpace(point)==false)
        {
            retCode = false;
            break;
        }
  }

  return retCode;
}


/** intersect the box with the given Line */
bool PolytopeVolume::intersect (const Line &OSG_CHECK_ARG(line)) const
{
    // not implented
    return 0;
}



/** intersect the box with the given Line */
bool PolytopeVolume::intersect (const Line &OSG_CHECK_ARG(line),
                                Real32 &OSG_CHECK_ARG(minDist),
                                Real32 &OSG_CHECK_ARG(maxDist)) const
{
    // not implented
    return 0;
}

bool PolytopeVolume::isOnSurface (const Pnt3f &OSG_CHECK_ARG(point)) const
{
    // not implemented
    return false;
}


/// Transforms Frustum3f by matrix, enlarging Frustum3f to contain result
void PolytopeVolume::transform(const Matrix &OSG_CHECK_ARG(m))
{
    // not implemented
    return;
}

/// Assignment operator
const PolytopeVolume &PolytopeVolume::operator =(const PolytopeVolume &b1)
{
    for (int i = 0; i < _numPlanes; i++)
        _planes[i] = b1._planes[i];

    return *this;
}

/// print the volume */
void PolytopeVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    // not implemented...
}

/// Equality comparisons
OSG_BASE_DLLMAPPING
bool operator ==(const PolytopeVolume &OSG_CHECK_ARG(b1),
                 const PolytopeVolume &OSG_CHECK_ARG(b2))
{
    FWARNING(("PolytopeVolume == NIY!\n"));
    // not implemented...
    /*
    if(b1._numPlanes == b2._numPlanes){
        for(int i=0; i<b1._numPlanes; i++){
            if(b1.planes[i]!=b2.planes[i])
                return(false);
        }
        return(true);
    }
    */
    return(false);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE
