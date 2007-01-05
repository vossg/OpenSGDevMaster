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

#ifndef _OSGVOLUMEINTERSECTFUNCTIONS_H_
#define _OSGVOLUMEINTERSECTFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <cmath>

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

class Volume;
class BoxVolume;
class CylinderVolume;
class SphereVolume;
class FrustumVolume;

//---------------------------------------------------------------------------
//   Volume Intersect and Extend Functions
//---------------------------------------------------------------------------

/*! @name Intersect
 */

// ###################################################################
// # Volume Interesect Functions #####################################
// ###################################################################

// Intersect implementation maxtrix:
//   Func:   Function implementation
//   Inline: Inline implementation
//
//           |Box     |Sphere  |Cylinder|Frustum |Volume
//   --------+--------+--------+--------+--------+------
//   Box     |Func    |Func    |Func    |Func    |Func
//   Sphere  |Inline  |Func    |Func    |Func    |Func
//   Cylinder|Inline  |Inline  |Func    |Func    |Func
//   Frustum |Inline  |Inline  |Inline  |Func    |Func
//   Volume  |Inline  |Inline  |Inline  |Inline  |Func

/*! \brief intersect Volume / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const Volume &vol1, const Volume &vol2);


// # Box #############################################################

/*! \brief intersect Box / Box
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &vol1, const BoxVolume      &vol2);

/*! \brief intersect BoxVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &vol1, const SphereVolume   &vol2);

/*! \brief intersect BoxVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &vol1, const CylinderVolume &vol2);

/*! \brief intersect BoxVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &vol1, const FrustumVolume  &vol2);

/*! \brief intersect Box / Volume
 *  \ingroup GrpBaseBaseVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const BoxVolume &vol1, const Volume         &vol2);


// # Sphere ###########################################################

/*! \brief intersect Sphere / Box
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const SphereVolume &vol1, const BoxVolume      &vol2);

/*! \brief intersect SphereVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &vol1, const SphereVolume   &vol2);

/*! \brief intersect SphereVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &vol1, const CylinderVolume &vol2);

/*! \brief intersect SphereVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &vol1, const FrustumVolume  &vol2);

/*! \brief intersect Sphere / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const SphereVolume &vol1, const Volume         &vol2);


// # Cylinder ########################################################

/*! \brief intersect Cylinder / Box
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const CylinderVolume &vol1, const BoxVolume      &vol2);

/*! \brief intersect CylinderVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const CylinderVolume &vol1, const SphereVolume   &vol2);

/*! \brief intersect CylinderVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &vol1, const CylinderVolume &vol2);

/*! \brief intersect CylinderVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &vol1, const FrustumVolume  &vol2);

/*! \brief intersect Cylinder / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const CylinderVolume &vol1, const Volume         &vol2);


// # Frustum ########################################################

/*! \brief intersect Frustum / Box
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const FrustumVolume &vol1, const BoxVolume      &vol2);

/*! \brief intersect FrustumVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const FrustumVolume &vol1, const SphereVolume   &vol2);

/*! \brief intersect FrustumVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const FrustumVolume  &vol1, const CylinderVolume &vol2);

/*! \brief intersect FrustumVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const FrustumVolume &vol1, const FrustumVolume   &vol2);

/*! \brief intersect Frustum / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const FrustumVolume &vol1, const Volume          &vol2);


// # Volume ########################################################

/*! \brief extend Frustum / Box
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const Volume &srcVol, const BoxVolume      &vol);

/*! \brief extend volume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const Volume &srcVol, const SphereVolume   &vol);

/*! \brief extend volume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const Volume &srcVol, const CylinderVolume &vol);

/*! \brief extend volume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

inline
bool intersect(const Volume &srcVol, const FrustumVolume  &vol);

// ###################################################################
// # Volume Extend Functions #########################################
// ###################################################################

/*! @name Extend
 */

OSG_BASE_DLLMAPPING 
void extend(Volume &srcVol,    const Volume         &vol);


// # Box #############################################################

/*! \brief extend Box / Box
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const BoxVolume      &vol);

/*! \brief extend BoxVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const SphereVolume   &vol);

/*! \brief extend BoxVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const CylinderVolume &vol);

/*! \brief extend BoxVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const FrustumVolume  &vol);

/*! \brief extend Box / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(BoxVolume &srcVol, const Volume         &vol);


// # Sphere ###########################################################

/*! \brief extend Sphere / Box
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const BoxVolume      &vol);

/*! \brief extend SphereVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING
void extend(SphereVolume &srcVol, const SphereVolume   &vol);

/*! \brief extend SphereVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const CylinderVolume &vol);

/*! \brief extend SphereVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const FrustumVolume  &vol);

/*! \brief extend SphereVolume / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(SphereVolume &srcVol, const Volume         &vol);


// # Cylinder ########################################################

/*! \brief extend Cylinder / Box
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const BoxVolume      &vol);

/*! \brief extend CylinderVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const SphereVolume   &vol);

/*! \brief extend CylinderVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const CylinderVolume &vol);

/*! \brief extend CylinderVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const FrustumVolume  &vol);

/*! \brief extend Sphere / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(CylinderVolume &srcVol, const Volume         &vol);


// # Frustum ########################################################

/*! \brief extend Frustum / Box
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(FrustumVolume &srcVol, const BoxVolume      &vol);

/*! \brief extend FrustumVolume / Sphere
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(FrustumVolume &srcVol, const SphereVolume   &vol);

/*! \brief extend FrustumVolume / Cylinder
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(FrustumVolume &srcVol, const CylinderVolume &vol);

/*! \brief extend FrustumVolume / Frustum
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(FrustumVolume &srcVol, const FrustumVolume  &vol);

/*! \brief extend Frustum / Volume
 *  \ingroup GrpBaseBaseVolume
 */

OSG_BASE_DLLMAPPING 
void extend(FrustumVolume &srcVol, const Volume         &vol);

OSG_END_NAMESPACE

#include "OSGVolumeFunctions.inl"

#endif /* OSGVOLUMEINTERSECTFUNCTIONS_H */

