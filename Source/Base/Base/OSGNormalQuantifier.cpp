/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2000-2003 by the OpenSG Forum                *
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
 *  initial version: based on code from P. Reuter (preuter@labri.fr)         *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGNormalQuantifier.h"
#include "OSGLog.h"

#define EPSILON 0.0000001

OSG_USING_NAMESPACE


/*--------------------------- Constructors --------------------------------*/

NormalQuantifier::NormalQuantifier(UInt32 numberSubdivisions)
{
    build(numberSubdivisions);
}

/*---------------------------- Destructor ---------------------------------*/

NormalQuantifier::~NormalQuantifier(void)
{
}

/*---------------------------- get ----------------------------------------*/

/*! get a index for the given normal
 */

UInt32 NormalQuantifier::getIndex(Vec3f  &normal, 
                                  UInt32  numberSubdivisions) const
{
    UInt32 index;
    UInt32 nS;
    UInt32 octant;
    Int32 xoctant;
    Int32 yoctant;
    Int32 zoctant;

    Vec3f point1;
    Vec3f point2;
    Vec3f point3;
  
    if(numberSubdivisions == 0)
    {
        nS = _numberSubdivisions;
    }
    else if(numberSubdivisions > _numberSubdivisions)
    {
        nS = _numberSubdivisions;
    }
    else
    {
        nS = numberSubdivisions;
    }
  
    octant = 
        (((normal.x() >= 0) ? 0 : 1) << 2) | 
        (((normal.y() >= 0) ? 0 : 1) << 1) | 
        ( (normal.z() >= 0) ? 0 : 1);

    xoctant = (octant & 4) ? -1 : 1;
    yoctant = (octant & 2) ? -1 : 1;
    zoctant = (octant & 1) ? -1 : 1;
    
    point1.setValues(0.f * xoctant, 0.f * yoctant, 1.f * zoctant);
    point2.setValues(1.f * xoctant, 0.f * yoctant, 0.f * zoctant);
    point3.setValues(0.f * xoctant, 1.f * yoctant, 0.f * zoctant);

    index = getSubIndex(normal, point1, point2, point3, nS);
  
    index = (octant << (2 * nS)) + index;
  
    return index;
}

/*---------------------------- Build --------------------------------------*/

/*! fills the normal table with 8*(2^(2*numberSubdivisions))
 */

void NormalQuantifier::build (UInt32 numberSubdivisions)
{
    UInt32 index = 0;
    UInt32 nN    = ((1 << (2 * numberSubdivisions)) * 8);
    
    _numberSubdivisions = numberSubdivisions;

    _normalTable.resize(nN);
  
    if(_numberSubdivisions != 0) 
    {
        for(UInt32 octant = 0; octant < 8; octant++) 
        {
            Int32 xoctant = (octant & 4)>0?-1:1;
            Int32 yoctant = (octant & 2)>0?-1:1;
            Int32 zoctant = (octant & 1)>0?-1:1;
            
            Vec3f point1(0.f * xoctant, 0.f * yoctant, 1.f * zoctant);
            Vec3f point2(1.f * xoctant, 0.f * yoctant, 0.f * zoctant);
            Vec3f point3(0.f * xoctant, 1.f * yoctant, 0.f * zoctant);
            
            subdivide(point1, point2, point3, _numberSubdivisions+1, index);
        }
        
        if(index != nN)
        {
            FFATAL(("NormalQuantifier::build() index missmatch!\n"));
        }
        else
        {
            FLOG(("NormalQuantifier init: %d subdivision, %d normal\n",
                  _numberSubdivisions, _normalTable.size()));
        }
    }  
}

/*---------------------------- Helper -------------------------------------*/

// ----------------------------------------------
// RayTriangle Intersection Function
// by RealTime Rendering:
// http://www.acm.org/jgt/papers/MollerTrumbore97/
// date: December 12th, 2000
// ----------------------------------------------
bool NormalQuantifier::rayTriangle ( const Vec3f & dir, 
                                     const Vec3f & vert0, 
                                     const Vec3f & vert1, 
                                     const Vec3f & vert2 ) const
{
  Vec3f edge1, edge2, tvec, pvec, qvec;
  float det,inv_det;
  float u,v;
  Vec3f orig(0,0,0);
 
  /* find vectors for two edges sharing vert0 */
  edge1 = vert1 - vert0;
  edge2 = vert2 - vert0;

  /* begin calculating determinant - also used to calculate U parameter */
  pvec = dir.cross(edge2);

  /* if determinant is near zero, ray lies in plane of triangle */
  det = edge1.dot(pvec);
 
  /* the non-culling branch */
  if (det > -EPSILON && det < EPSILON)
    return false;

  inv_det = 1.0f / det;

  /* calculate distance from vert0 to ray origin */
  tvec = orig - vert0;

  /* calculate U parameter and test bounds */
  u = tvec.dot(pvec) *inv_det;
 
  if (u < 0.0 || u > 1.0)
    return false;

  /* prepare to test V parameter */
  qvec = tvec.cross(edge1);

  /* calculate V parameter and test bounds */
  v = dir.dot(qvec) * inv_det;

  if (v < 0.0 || u + v > 1.0)
    return false;

  /* calculate t, ray intersects triangle */
  //t = edge2.dot(qvec) * inv_det;

  return true;
};


/*! recursive function to fill the NormalsTable
 */

void NormalQuantifier::subdivide(Vec3f   point1, 
                                 Vec3f   point2, 
                                 Vec3f   point3, 
                                 UInt32  number, 
                                 UInt32 &index ) 
{
    number--;
  
    if(number == 0) 
    {
        Vec3f newPoint = point1;

        newPoint += point2;
        newPoint += point3;
        newPoint /= 3;
        
        newPoint.normalize();

        _normalTable[index] = newPoint;
        ++index; 
    }
    else 
    {  
        Vec3f newPoint1 = point1;

        newPoint1 += point2;
        newPoint1 /= 2;
        newPoint1.normalize();
        
        Vec3f newPoint2 = point1;

        newPoint2 += point3;
        newPoint2 /= 2; 
        newPoint2.normalize();
        
        Vec3f newPoint3 = point2;

        newPoint3 += point3;
        newPoint3 /= 2;
        newPoint3.normalize();
        
        subdivide(point1   , newPoint1, newPoint2, number, index);
        subdivide(newPoint1, point2   , newPoint3, number, index);
        subdivide(newPoint1, newPoint2, newPoint3, number, index);
        subdivide(newPoint2, newPoint3, point3   , number, index);
    }
}

/*! recursive function to get an index
 */

UInt32 NormalQuantifier::getSubIndex(Vec3f point, 
                                     Vec3f point1, 
                                     Vec3f point2, 
                                     Vec3f point3, 
                                     UInt32 number) const
{
	int intersect = -1, index = 0;
  Vec3f newPoint1(point1);
  Vec3f newPoint2(point1);
  Vec3f newPoint3(point2);
  
	//newPoint1 = (point1+point2)/2; newPoint1.normalize();
	//newPoint2 = (point1+point3)/2; newPoint2.normalize();
	//newPoint3 = (point2+point3)/2; newPoint3.normalize();
  
  newPoint1 += point2;
  newPoint1 /= 2; 
  newPoint1.normalize();
  
  newPoint2 += point3;
  newPoint2 /=2; 
  newPoint2.normalize();
  
  newPoint3 += point3;
  newPoint3 /= 2; 
  newPoint3.normalize();
  
	number--;
  
  if (rayTriangle(point, point1, newPoint1, newPoint2)) 
    intersect = 0;
  else 
    if (rayTriangle(point, newPoint1, point2, newPoint3)) 
      intersect = 1;
    else 
      if ( rayTriangle(point, newPoint1, newPoint2, newPoint3)) 
        intersect = 2;
      else 
        if ( rayTriangle(point, newPoint2, newPoint3, point3)) 
          intersect = 3;
  
  if ( intersect >= 0 ) {
    
    index = intersect;
    
    if (number != 0) {
      
      index = index << (number*2);
      
      switch (intersect) {
      case 0:
        index += getSubIndex(point, point1, newPoint1, newPoint2, number);
        break;
      case 1:
        index += getSubIndex(point, newPoint1, point2, newPoint3, number);
        break;
      case 2:
        index += getSubIndex(point, newPoint1, newPoint2, newPoint3, number);
        break;
      case 3: 
        index += getSubIndex(point, newPoint2, newPoint3, point3, number);
        break;
      }
    }
  }
  else {
    FFATAL (( "Intersect < 0 in NormalQuantifier::getSubIndex()\n"));
  }

  return index;
}





/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGNORMALQUANTIFIER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGNORMALQUANTIFIER_INLINE_CVSID;
}
