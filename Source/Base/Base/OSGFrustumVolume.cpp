/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

#include <iostream>

#include <cassert>

#include "OSGFrustumVolume.h"
#include "OSGLog.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

/*! \class OSG::FrustumVolume

    
*/


OSG_BEGIN_NAMESPACE

/*-------------------------------- get ------------------------------------*/

void FrustumVolume::getCenter(Pnt3f &center) const
{
    Pnt3f vertices[8];
    Line  lines   [4];

    _planeVec[5].intersect(_planeVec[3],lines[3]);
    _planeVec[3].intersect(_planeVec[4],lines[2]);
    _planeVec[4].intersect(_planeVec[2],lines[0]);
    _planeVec[2].intersect(_planeVec[5],lines[1]);
    
    for(Int32 i = 0; i < 4; i++)
    {
        _planeVec[0].intersectInfinite(lines[i],vertices[    i]);
        _planeVec[1].intersectInfinite(lines[i],vertices[4 + i]);
    }    
    
    center = Pnt3f(0.f, 0.f ,0.f);

    for(Int32 i = 0; i < 8; i++)
    {        
        center = center + vertices[i].subZero();
    }

    center /= 8.f;
}


Real32 FrustumVolume::getScalarVolume() const
{
    const Int32 faces[6][4] =
    {
        {0,1,3,2},
        {4,5,7,6},
        {0,4,5,1},
        {2,6,7,3},
        {2,6,4,0},
        {1,5,7,3}
    };

    Pnt3f vertices[8];
    Line  lines   [4];

    _planeVec[5].intersect(_planeVec[3], lines[3]); 
    _planeVec[3].intersect(_planeVec[4], lines[2]); 
    _planeVec[4].intersect(_planeVec[2], lines[0]); 
    _planeVec[2].intersect(_planeVec[5], lines[1]); 
    
    for(Int32 i = 0; i < 4; i++)
    {
        _planeVec[0].intersectInfinite(lines[i], vertices[    i]);
        _planeVec[1].intersectInfinite(lines[i], vertices[4 + i]);
    }
    

    Pnt3f center = Pnt3f(0.f, 0.f, 0.f);

    for(Int32 i = 0; i < 8; i++)
    {
        center = center + vertices[i].subZero();
    }

    center /= 8.f;
    
    Real32 volume = .0f;

    for(Int32 i = 0; i < 6; i++)
    {
        Real32 height;
        Real32 area;

        height = 
            _planeVec[i].getNormal().dot(center) - 
            _planeVec[i].getDistanceFromOrigin();
        
        Vec3f main_diag = vertices[faces[i][0]] - vertices[faces[i][2]];
        Vec3f sec_diag  = vertices[faces[i][1]] - vertices[faces[i][3]];

        area = osgAbs((main_diag.cross(sec_diag)).length() / 2.f);        

        volume += osgAbs((height*area)) / 3.f;
    }

    return volume;
}


/*! Computes the \a minPnt and \a maxPnt of an axis aligned bounding box
    containing this volume.
 */
void FrustumVolume::getBounds(Pnt3f &minPnt,
                              Pnt3f &maxPnt ) const
{
    Pnt3f corners[8];

    this->getCorners(corners[0], corners[1], corners[2], corners[3],
                     corners[4], corners[5], corners[6], corners[7] );

    minPnt[0] = TypeTraits<Pnt3f::ValueType>::getMax();
    minPnt[1] = TypeTraits<Pnt3f::ValueType>::getMax();
    minPnt[2] = TypeTraits<Pnt3f::ValueType>::getMax();

    maxPnt[0] = TypeTraits<Pnt3f::ValueType>::getMin();
    maxPnt[1] = TypeTraits<Pnt3f::ValueType>::getMin();
    maxPnt[2] = TypeTraits<Pnt3f::ValueType>::getMin();

    for(UInt32 i = 0; i < 8; ++i)
    {
        minPnt[0] = osgMin(minPnt[0], corners[i][0]);
        minPnt[1] = osgMin(minPnt[1], corners[i][1]);
        minPnt[2] = osgMin(minPnt[2], corners[i][2]);

        maxPnt[0] = osgMax(maxPnt[0], corners[i][0]);
        maxPnt[1] = osgMax(maxPnt[1], corners[i][1]);
        maxPnt[2] = osgMax(maxPnt[2], corners[i][2]);
    }
}

/*! Computes the eight corner points of the frustum.
 */
void FrustumVolume::getCorners(Pnt3f &nlt, Pnt3f &nlb,
                               Pnt3f &nrt, Pnt3f &nrb,
                               Pnt3f &flt, Pnt3f &flb,
                               Pnt3f &frt, Pnt3f &frb ) const
{
    Line edges[4];

    _planeVec[PLANE_BOTTOM].intersect(_planeVec[PLANE_RIGHT ], edges[3]);
    _planeVec[PLANE_RIGHT ].intersect(_planeVec[PLANE_TOP   ], edges[2]);
    _planeVec[PLANE_TOP   ].intersect(_planeVec[PLANE_LEFT  ], edges[0]);
    _planeVec[PLANE_LEFT  ].intersect(_planeVec[PLANE_BOTTOM], edges[1]);

    _planeVec[PLANE_NEAR].intersectInfinite(edges[0], nlt);
    _planeVec[PLANE_FAR ].intersectInfinite(edges[0], flt);
    _planeVec[PLANE_NEAR].intersectInfinite(edges[1], nlb);
    _planeVec[PLANE_FAR ].intersectInfinite(edges[1], flb);
    _planeVec[PLANE_NEAR].intersectInfinite(edges[2], nrt);
    _planeVec[PLANE_FAR ].intersectInfinite(edges[2], frt);
    _planeVec[PLANE_NEAR].intersectInfinite(edges[3], nrb);
    _planeVec[PLANE_FAR ].intersectInfinite(edges[3], frb);
}

Pnt3f FrustumVolume::getCorner(Corner cornerId) const
{
    Pnt3f cornerPnt;
    Line edge;
    switch (cornerId)
    {
        case NEAR_LEFT_BOTTOM:
            _planeVec[PLANE_LEFT  ].intersect(_planeVec[PLANE_BOTTOM], edge);
            _planeVec[PLANE_NEAR].intersectInfinite(edge, cornerPnt);
            break;
        case NEAR_RIGHT_BOTTOM:
            _planeVec[PLANE_BOTTOM].intersect(_planeVec[PLANE_RIGHT ], edge);
            _planeVec[PLANE_NEAR].intersectInfinite(edge, cornerPnt);
            break;
        case NEAR_RIGHT_TOP:
            _planeVec[PLANE_RIGHT ].intersect(_planeVec[PLANE_TOP   ], edge);
            _planeVec[PLANE_NEAR].intersectInfinite(edge, cornerPnt);
            break;
        case NEAR_LEFT_TOP:
            _planeVec[PLANE_TOP   ].intersect(_planeVec[PLANE_LEFT  ], edge);
            _planeVec[PLANE_NEAR].intersectInfinite(edge, cornerPnt);
            break;
        case FAR_LEFT_BOTTOM:
            _planeVec[PLANE_LEFT  ].intersect(_planeVec[PLANE_BOTTOM], edge);
            _planeVec[PLANE_FAR ].intersectInfinite(edge, cornerPnt);
            break;
        case FAR_RIGHT_BOTTOM:
            _planeVec[PLANE_BOTTOM].intersect(_planeVec[PLANE_RIGHT ], edge);
            _planeVec[PLANE_FAR ].intersectInfinite(edge, cornerPnt);
            break;
        case FAR_RIGHT_TOP:
            _planeVec[PLANE_RIGHT ].intersect(_planeVec[PLANE_TOP   ], edge);
            _planeVec[PLANE_FAR ].intersectInfinite(edge, cornerPnt);
            break;
        case FAR_LEFT_TOP:
            _planeVec[PLANE_TOP   ].intersect(_planeVec[PLANE_LEFT  ], edge);
            _planeVec[PLANE_FAR ].intersectInfinite(edge, cornerPnt);
            break;
        default:
            SWARNING << "FrustumVolume::getCorner: invalid corner type!" << std::endl;
    }
    return cornerPnt;
}

/*------------------------------ feature ----------------------------------*/

void FrustumVolume::setPlanes(const Plane &pnear, const Plane &pfar,
                              const Plane &pleft, const Plane &pright,
                              const Plane &ptop,  const Plane &pbottom)
{
    _planeVec[0] = pnear;
    _planeVec[1] = pfar;
    _planeVec[2] = pleft;
    _planeVec[3] = pright;
    _planeVec[4] = ptop;
    _planeVec[5] = pbottom;
}


void FrustumVolume::setPlanes(const Pnt3f &nlt, const Pnt3f &nlb,
                              const Pnt3f &nrt, const Pnt3f &nrb,
                              const Pnt3f &flt, const Pnt3f &flb,
                              const Pnt3f &frt, const Pnt3f &frb)
{

    Plane pnear  (nlb,nlt,nrb);
    Plane pfar   (frb,frt,flb);
    Plane pleft  (flb,flt,nlb);
    Plane pright (nrb,nrt,frb);
    Plane ptop   (frt,nrt,flt);
    Plane pbottom(nlb,nrb,flb);


    _planeVec[0] = pnear;
    _planeVec[1] = pfar;
    _planeVec[2] = pleft;
    _planeVec[3] = pright;
    _planeVec[4] = ptop;
    _planeVec[5] = pbottom;

}


void FrustumVolume::setPlanes(const Matrix &objectClipMat)
{
    Vec4f  planeEquation[6];
    Real32 vectorLength;
    Vec3f  normal;

    // right plane
    planeEquation[0][0] = objectClipMat[0][3] - objectClipMat[0][0];
    planeEquation[0][1] = objectClipMat[1][3] - objectClipMat[1][0];
    planeEquation[0][2] = objectClipMat[2][3] - objectClipMat[2][0];
    planeEquation[0][3] = objectClipMat[3][3] - objectClipMat[3][0];

    // left plane
    planeEquation[1][0] = objectClipMat[0][3] + objectClipMat[0][0];
    planeEquation[1][1] = objectClipMat[1][3] + objectClipMat[1][0];
    planeEquation[1][2] = objectClipMat[2][3] + objectClipMat[2][0];
    planeEquation[1][3] = objectClipMat[3][3] + objectClipMat[3][0];

    // bottom plane
    planeEquation[2][0] = objectClipMat[0][3] + objectClipMat[0][1];
    planeEquation[2][1] = objectClipMat[1][3] + objectClipMat[1][1];
    planeEquation[2][2] = objectClipMat[2][3] + objectClipMat[2][1];
    planeEquation[2][3] = objectClipMat[3][3] + objectClipMat[3][1];

    // top plane
    planeEquation[3][0] = objectClipMat[0][3] - objectClipMat[0][1];
    planeEquation[3][1] = objectClipMat[1][3] - objectClipMat[1][1];
    planeEquation[3][2] = objectClipMat[2][3] - objectClipMat[2][1];
    planeEquation[3][3] = objectClipMat[3][3] - objectClipMat[3][1];

    // near plane
    planeEquation[4][0] = objectClipMat[0][3] + objectClipMat[0][2];
    planeEquation[4][1] = objectClipMat[1][3] + objectClipMat[1][2];
    planeEquation[4][2] = objectClipMat[2][3] + objectClipMat[2][2];
    planeEquation[4][3] = objectClipMat[3][3] + objectClipMat[3][2];

    // far plane
    planeEquation[5][0] = objectClipMat[0][3] - objectClipMat[0][2];
    planeEquation[5][1] = objectClipMat[1][3] - objectClipMat[1][2];
    planeEquation[5][2] = objectClipMat[2][3] - objectClipMat[2][2];
    planeEquation[5][3] = objectClipMat[3][3] - objectClipMat[3][2];

    for(Int32  i = 0; i < 6; i++) 
    {
        vectorLength = 
            osgSqrt(planeEquation[i][0] * planeEquation[i][0] +
                    planeEquation[i][1] * planeEquation[i][1] +
                    planeEquation[i][2] * planeEquation[i][2]);
 
        planeEquation[i][0] /=  vectorLength;
        planeEquation[i][1] /=  vectorLength;
        planeEquation[i][2] /=  vectorLength;
        planeEquation[i][3] /= -vectorLength;
    }

  // right
  _planeVec[3].set(planeEquation[0]);

  // left
  _planeVec[2].set(planeEquation[1]);

  // bottom
  _planeVec[5].set(planeEquation[2]);

  // top
  _planeVec[4].set(planeEquation[3]);

  // near
  _planeVec[0].set(planeEquation[4]);

  // far
  _planeVec[1].set(planeEquation[5]);
}


void FrustumVolume::setPlanesOutwards(const Matrix &objectClipMat)
{
    Vec4f  planeEquation[6];
    Real32 vectorLength;
    Vec3f  normal;

    // right plane
    planeEquation[0][0] = objectClipMat[0][3] - objectClipMat[0][0];
    planeEquation[0][1] = objectClipMat[1][3] - objectClipMat[1][0];
    planeEquation[0][2] = objectClipMat[2][3] - objectClipMat[2][0];
    planeEquation[0][3] = objectClipMat[3][3] - objectClipMat[3][0];

    // left plane
    planeEquation[1][0] = objectClipMat[0][3] + objectClipMat[0][0];
    planeEquation[1][1] = objectClipMat[1][3] + objectClipMat[1][0];
    planeEquation[1][2] = objectClipMat[2][3] + objectClipMat[2][0];
    planeEquation[1][3] = objectClipMat[3][3] + objectClipMat[3][0];

    // bottom plane
    planeEquation[2][0] = objectClipMat[0][3] + objectClipMat[0][1];
    planeEquation[2][1] = objectClipMat[1][3] + objectClipMat[1][1];
    planeEquation[2][2] = objectClipMat[2][3] + objectClipMat[2][1];
    planeEquation[2][3] = objectClipMat[3][3] + objectClipMat[3][1];

    // top plane
    planeEquation[3][0] = objectClipMat[0][3] - objectClipMat[0][1];
    planeEquation[3][1] = objectClipMat[1][3] - objectClipMat[1][1];
    planeEquation[3][2] = objectClipMat[2][3] - objectClipMat[2][1];
    planeEquation[3][3] = objectClipMat[3][3] - objectClipMat[3][1];

    // near plane
    planeEquation[4][0] = objectClipMat[0][3] + objectClipMat[0][2];
    planeEquation[4][1] = objectClipMat[1][3] + objectClipMat[1][2];
    planeEquation[4][2] = objectClipMat[2][3] + objectClipMat[2][2];
    planeEquation[4][3] = objectClipMat[3][3] + objectClipMat[3][2];

    // far plane
    planeEquation[5][0] = objectClipMat[0][3] - objectClipMat[0][2];
    planeEquation[5][1] = objectClipMat[1][3] - objectClipMat[1][2];
    planeEquation[5][2] = objectClipMat[2][3] - objectClipMat[2][2];
    planeEquation[5][3] = objectClipMat[3][3] - objectClipMat[3][2];

    for(Int32  i = 0; i < 6; i++) 
    {
        vectorLength = 
            osgSqrt(planeEquation[i][0] * planeEquation[i][0] +
                    planeEquation[i][1] * planeEquation[i][1] +
                    planeEquation[i][2] * planeEquation[i][2]);
 
        planeEquation[i][0] /= -vectorLength;
        planeEquation[i][1] /= -vectorLength;
        planeEquation[i][2] /= -vectorLength;
        planeEquation[i][3] /=  vectorLength;
    }

  // right
  _planeVec[3].set(planeEquation[0]);

  // left
  _planeVec[2].set(planeEquation[1]);

  // bottom
  _planeVec[5].set(planeEquation[2]);

  // top
  _planeVec[4].set(planeEquation[3]);

  // near
  _planeVec[0].set(planeEquation[4]);

  // far
  _planeVec[1].set(planeEquation[5]);
}

/*-------------------------- extending ------------------------------------*/

/*! 
  \warning NOT IMPLEMENTED 
  \brief   NOT IMPLEMENTED 
 */

void FrustumVolume::extendBy(const Pnt3f &OSG_CHECK_ARG(pt))
{
}

/*!
  \brief extend the volume to enclose the given one.
 */

void FrustumVolume::extendBy(const Volume &volume)
{
    OSG::extend(*this, volume);
}


/*-------------------------- intersection ---------------------------------*/

bool FrustumVolume::intersect(const Pnt3f &point) const
{
    bool retCode = true;

    for(Int32 i = 0; i < 6; i++) 
    {
        if((_planeVec[i].getNormal().x() * point.x() +
            _planeVec[i].getNormal().y() * point.y() +
            _planeVec[i].getNormal().z() * point.z() -
            _planeVec[i].getDistanceFromOrigin()     ) < 0.f) 
        {
            retCode = false;
            break;
        }
    }
    
    return retCode;
}


bool FrustumVolume::intersect(const Line &line) const
{
    return line.intersect(*this);
}


bool FrustumVolume::intersect(const Line   &line,
                                    Real32 &minDist, 
                                    Real32 &maxDist) const
{
    return line.intersect(*this, minDist, maxDist);
}


bool FrustumVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this, volume);
}

/*! 
  \warning NOT IMPLEMENTED 
  \brief   NOT IMPLEMENTED 
 */

bool FrustumVolume::isOnSurface(const Pnt3f &OSG_CHECK_ARG(point)) const
{
    FWARNING(("FrustumVolume::isOnSurface: NYI!\n"));
    return false;
}

void FrustumVolume::transform(const Matrix &m)
{
    _planeVec[0].transform(m);
    _planeVec[1].transform(m);
    _planeVec[2].transform(m);
    _planeVec[3].transform(m);
    _planeVec[4].transform(m);
    _planeVec[5].transform(m); 
}

FrustumVolume &FrustumVolume::operator =(const FrustumVolume &rhs)
{
    if(this == &rhs)
        return *this;

    for(Int32 i = 0; i < 6; i++)
    {
        _planeVec[i] = rhs._planeVec[i];
    }

    _state = rhs._state;

    return *this;
}

bool FrustumVolume::operator ==(const FrustumVolume &rhs) const
{
    return ((static_cast<const Volume &>(*this) == rhs) &&
            (_planeVec[0] == rhs._planeVec[0]         ) &&
            (_planeVec[1] == rhs._planeVec[1]         ) &&
            (_planeVec[2] == rhs._planeVec[2]         ) &&
            (_planeVec[3] == rhs._planeVec[3]         ) &&
            (_planeVec[4] == rhs._planeVec[4]         ) &&
            (_planeVec[5] == rhs._planeVec[5]         ));
}

void FrustumVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
#if 1
    fprintf(stderr,"Frustum:(%f %f %f:%f)(%f %f %f:%f)(%f %f %f:%f)"
                "(%f %f %f:%f)(%f %f %f:%f)(%f %f %f:%f)\n",
                _planeVec[0].getNormal()[0],
                _planeVec[0].getNormal()[1],
                _planeVec[0].getNormal()[2],
                _planeVec[0].getDistanceFromOrigin(),
                _planeVec[1].getNormal()[0],
                _planeVec[1].getNormal()[1],
                _planeVec[1].getNormal()[2],
                _planeVec[1].getDistanceFromOrigin(),
                _planeVec[2].getNormal()[0],
                _planeVec[2].getNormal()[1],
                _planeVec[2].getNormal()[2],
                _planeVec[2].getDistanceFromOrigin(),
                _planeVec[3].getNormal()[0],
                _planeVec[3].getNormal()[1],
                _planeVec[3].getNormal()[2],
                _planeVec[3].getDistanceFromOrigin(),
                _planeVec[4].getNormal()[0],
                _planeVec[4].getNormal()[1],
                _planeVec[4].getNormal()[2],
                _planeVec[4].getDistanceFromOrigin(),
                _planeVec[5].getNormal()[0],
                _planeVec[5].getNormal()[1],
                _planeVec[5].getNormal()[2],
                _planeVec[5].getDistanceFromOrigin() );
                

#else 
    print(PLOG);
#endif
}

void FrustumVolume::print(std::ostream &os) const
{
    os << "Frustum ("
       << _planeVec[0].getNormal()             << ":"
       << _planeVec[0].getDistanceFromOrigin() << "|"
       << _planeVec[1].getNormal()             << ":"
       << _planeVec[1].getDistanceFromOrigin() << "|"
       << _planeVec[2].getNormal()             << ":"
       << _planeVec[2].getDistanceFromOrigin() << "|"
       << _planeVec[3].getNormal()             << ":"
       << _planeVec[3].getDistanceFromOrigin() << "|"
       << _planeVec[4].getNormal()             << ":"
       << _planeVec[4].getDistanceFromOrigin() << "|"
       << _planeVec[5].getNormal()             << ":"
       << _planeVec[5].getDistanceFromOrigin()
       << ") ";
    printState(os);
}


/*! Check the volume against the frustum, but only against the given planes.

    If in inplanes the bit relating to the P_* enums is set, the volume is
    known to be fully in the halfspace of the given plane and is not checked.

    For the other planes the volume is checked if it is in the halfspace at 
    all, and if it is fully in the halfspace, for which the inplanes are
    adjusted.
*/

OSG_BASE_DLLMAPPING 
bool intersect(const OSG::FrustumVolume           &frustum, 
               const OSG::Volume                  &vol, 
                     OSG::FrustumVolume::PlaneSet &inplanes)
{
    // it's probably safe to assume the frustum is not empty and finite
    // so we only check vol for these conditions

    if(vol.isEmpty() == true)
    {
        return false;
    }
    else if(vol.isInfinite() == true)
    {
        inplanes = FrustumVolume::P_ALL;
        return true;
    }
    else
    {
        Pnt3f min, max;

        vol.getBounds(min, max);
     
        const Plane             *frust = frustum.getPlanes();
        FrustumVolume::PlaneSet  mask  = 0x1;
   
        // check the box against the 6 planes, adjust the inplanes set
        // accordingly

        for(Int32 i = 0; i < 6; i++, mask <<= 1)
        {
            if((inplanes & mask) != 0)
                continue;
        
            if(frust[i].isOutHalfSpace(min, max))
                return false;
        
            if(frust[i].isInHalfSpace(min, max))
                inplanes |= mask;
        }
    }

    return true;
}

OSG_END_NAMESPACE
