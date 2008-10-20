/*---------------------------------------------------------------------------*\
 *                           OpenSG NURBS Library                            *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2006 by the University of Bonn, Computer Graphics Group*
 *                                                                           *
 *                         http://cg.cs.uni-bonn.de/                         *
 *                                                                           *
 * contact: edhellon@cs.uni-bonn.de, guthe@cs.uni-bonn.de, rk@cs.uni-bonn.de *
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
#ifndef _OSG_DCTPTYPES_H_
#define _OSG_DCTPTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGConfig.h>

#include <iostream>
#include <set>
#include <math.h>
#include <vector>
#include <list>

#include <OSGVector.h>

OSG_BEGIN_NAMESPACE

#define DCTP_EPS 0.000000001
//#define DCTP_EPS 1.0e-20

#define DCTP_PRECISION 16

/*************************************************************************/
/*
 *  Originally the tessellation library used its own vector classes,
 *  for which the "operator" methods had slightly different semantics
 *  than the OpenSG versions. Therefore when migrating to the OpenSG
 *  vector classes, we opted for producing some "wrapper" functions
 *  that provide the old semantics. As everything is inlined, and
 *  the implementation is pretty much the same as for the old
 *  functions there should not be any performance issues.
 */

inline bool DCTPVecIsLesser(const Vec3d v1, const Vec3d v2)
{
    // this should be better...
    if(v2[2] - v1[2] >= DCTP_EPS) // z < vec.z
        return true;
    if(v1[2] - v2[2] >= DCTP_EPS) // z > vec.z
        return false;
    if(v2[1] - v1[1] >= DCTP_EPS) // y < vec.y
        return true;
    if(v1[1] - v2[1] >= DCTP_EPS) // y > vec.y
        return false;
    if(v2[0] - v1[0] >= DCTP_EPS) // x < vec.x
        return true;
    return false;
}

inline bool DCTPVecIsLesser(const Vec4d v1, const Vec4d v2)
{
    // this should be better...
    if(v2[3] - v1[3] >= DCTP_EPS) // w < vec.w
        return true;
    if(v1[3] - v2[3] >= DCTP_EPS) // w > vec.w
        return false;
    if(v2[2] - v1[2] >= DCTP_EPS) // z < vec.z
        return true;
    if(v1[2] - v2[2] >= DCTP_EPS) // z > vec.z
        return false;
    if(v2[1] - v1[1] >= DCTP_EPS) // y < vec.y
        return true;
    if(v1[1] - v2[1] >= DCTP_EPS) // y > vec.y
        return false;
    if(v2[0] - v1[0] >= DCTP_EPS) // x < vec.x
        return true;
    return false;
}

inline bool DCTPVecIsLesser(const Vec2d v1, const Vec2d v2)
{
    // this should be better...
    if(v2[1] - v1[1] >= DCTP_EPS) // y < vec.y
        return true;
    if(v1[1] - v2[1] >= DCTP_EPS) // y > vec.y
        return false;
    if(v2[0] - v1[0] >= DCTP_EPS) // x < vec.x
        return true;
    return false;
}

inline bool DCTPVecIsGreater(const Vec4d v1, const Vec4d v2)
{
    // this should be better...
    if(v1[3] - v2[3] >= DCTP_EPS)
        return true;
    if(v2[3] - v1[3] >= DCTP_EPS)
        return false;
    if(v1[2] - v2[2] >= DCTP_EPS)
        return true;
    if(v2[2] - v1[2] >= DCTP_EPS)
        return false;
    if(v1[1] - v2[1] >= DCTP_EPS)
        return true;
    if(v2[1] - v1[1] >= DCTP_EPS)
        return false;
    if(v1[0] - v2[0] >= DCTP_EPS)
        return true;
    return false;
}

inline bool DCTPVecIsGreater(const Vec3d v1, const Vec3d v2)
{
    // this should be better...
    if(v1[2] - v2[2] >= DCTP_EPS)
        return true;
    if(v2[2] - v1[2] >= DCTP_EPS)
        return false;
    if(v1[1] - v2[1] >= DCTP_EPS)
        return true;
    if(v2[1] - v1[1] >= DCTP_EPS)
        return false;
    if(v1[0] - v2[0] >= DCTP_EPS)
        return true;
    return false;
}

inline bool DCTPVecIsGreater(const Vec2d v1, const Vec2d v2)
{
    // this should be better...
    if(v1[1] - v2[1] >= DCTP_EPS)
        return true;
    if(v2[1] - v1[1] >= DCTP_EPS)
        return false;
    if(v1[0] - v2[0] >= DCTP_EPS)
        return true;
    return false;
}

inline bool DCTPVecIsEqual(const Vec3d v1, const Vec3d v2)
{
    if( (osgAbs(v1[0] - v2[0]) < DCTP_EPS) &&
        (osgAbs(v1[1] - v2[1]) < DCTP_EPS) &&
        (osgAbs(v1[2] - v2[2]) < DCTP_EPS) )
        return true;
    else
        return false;
}

inline bool DCTPVecIsEqual(const Vec2d v1, const Vec2d v2)
{
    if( (osgAbs(v1[0] - v2[0]) < DCTP_EPS) &&
        (osgAbs(v1[1] - v2[1]) < DCTP_EPS) )
        return true;
    else
        return false;
}

inline bool DCTPVecIsNotEqual(const Vec3d v1, const Vec3d v2)
{
    if( (osgAbs(v1[0] - v2[0]) < DCTP_EPS) &&
        (osgAbs(v1[1] - v2[1]) < DCTP_EPS) &&
        (osgAbs(v1[2] - v2[2]) < DCTP_EPS) )
        return false;
    else
        return true;
//    return ( v1 != v2 );
}

inline bool DCTPVecIsNotEqual(const Vec2d v1, const Vec2d v2)
{
    if( (osgAbs(v1[0] - v2[0]) < DCTP_EPS) &&
        (osgAbs(v1[1] - v2[1]) < DCTP_EPS) )
        return false;
    else
        return true;

//    return ( v1 != v2 );
}

/*************************************************************************/

struct DCTPSVec2dless
{
    inline bool operator()(const Vec2d v1, const Vec2d v2) const
    {
        return DCTPVecIsLesser(v1, v2);
    }
};

struct DCTPSVec3dless
{
    inline bool operator()(const Vec3d v1, const Vec3d v2) const
    {
        return DCTPVecIsLesser(v1, v2);
    }
};
struct DCTPSVec4dless
{
    inline bool operator()(const Vec4d v1, const Vec4d v2) const
    {
        return DCTPVecIsLesser(v1, v2);
    }
};

/*************************************************************************/

typedef std::vector<double>             DCTPdvector;
typedef std::vector<int>                DCTPivector;
typedef std::vector<DCTPivector>        DCTPimatrix;
typedef std::vector<Vec2d>              DCTPVec2dvector;
typedef std::vector<Vec3d>              DCTPVec3dvector;
typedef std::vector<Vec4d>              DCTPVec4dvector;
typedef std::vector<DCTPVec3dvector>    DCTPVec3dmatrix;
typedef std::vector<DCTPVec4dvector>    DCTPVec4dmatrix;
typedef std::list<double>               DCTPdlist;
typedef std::set<double>                DCTPdset;
typedef std::set<Vec2d, DCTPSVec2dless> DCTPVec2dset;
typedef std::set<Vec3d, DCTPSVec3dless> DCTPVec3dset;
typedef std::set<Vec4d, DCTPSVec4dless> DCTPVec4dset;

OSG_END_NAMESPACE

#endif /* _OSG_DCTPTYPES_H_ */
