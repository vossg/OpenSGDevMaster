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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                     Volume intersection Functions                        *
\***************************************************************************/

// Intersect implementation maxtrix:
//   Func:   Function implementation
//   Inl :   Inline implementation
//
//           |Box     |Sphere  |Cylinder|Frustum |Volume
//   --------+--------+--------+--------+--------+------
//   Box     |Func    |Func    |Func    |Func    |Func
//   Sphere  |Inl     |Func    |Func    |Func    |Func
//   Cylinder|Inl     |Inl     |Func    |Func    |Func
//   Frustum |Inl     |Inl     |Inl     |Func    |Func
//   Volume  |Inl     |Inl     |Inl     |Inl     |Func

// # Box ##############################################################

// all implementation in cpp file


// # Sphere ###########################################################

inline 
bool intersect(const OSG::SphereVolume &sphere, const OSG::BoxVolume &box)
{
    return intersect(box, sphere);
}


// # Cylinder ########################################################

inline
bool intersect(const OSG::CylinderVolume &cylinder, const OSG::BoxVolume &box)
{
    return intersect(box, cylinder);
}

inline
bool intersect(const OSG::CylinderVolume &cylinder, 
               const OSG::SphereVolume   &sphere)
{
    return intersect(sphere, cylinder);
}


// # Frustum ########################################################


inline
bool intersect(const OSG::FrustumVolume &frustum, const OSG::BoxVolume &box)
{
    return intersect(box, frustum);
}

inline
bool intersect(const OSG::FrustumVolume &frustum, 
               const OSG::SphereVolume  &sphere)
{
    return intersect(sphere,frustum);
}

inline 
bool intersect(const OSG::FrustumVolume  &frustum, 
               const OSG::CylinderVolume &cylinder)
{
    return intersect(cylinder,frustum);
}


// # Volume ########################################################

inline 
bool intersect(const OSG::Volume &srcVol, const OSG::BoxVolume &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const OSG::Volume &srcVol, const OSG::SphereVolume &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const OSG::Volume &srcVol, const OSG::CylinderVolume &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const OSG::Volume &srcVol, const OSG::FrustumVolume  &vol)
{
    return intersect(vol,srcVol);
}

OSG_END_NAMESPACE

