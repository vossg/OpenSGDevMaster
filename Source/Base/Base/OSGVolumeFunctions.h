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
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */

OSG_BASE_DLLMAPPING 
bool intersect(const OSG::Volume &vol1, const OSG::Volume &vol2);


// # Box #############################################################

/*! \brief intersect BoxVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::BoxVolume &vol1, const OSG::BoxVolume &vol2);


/*! \brief intersect BoxVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::BoxVolume &vol1, const OSG::SphereVolume &vol2);


/*! \brief intersect BoxVolume / CylinderVolume
 *  \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::BoxVolume &vol1, const OSG::CylinderVolume &vol2);


/*! \brief intersect BoxVolume / FrustumVolume
 *  \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::BoxVolume &vol1, const OSG::FrustumVolume &vol2);


/*! \brief intersect BoxVolume / Volume
 *  \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::BoxVolume &vol1, const OSG::Volume &vol2);


// # Sphere ###########################################################

/*! \brief intersect SphereVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
inline
bool intersect(const OSG::SphereVolume &vol1, const OSG::BoxVolume &vol2);


/*! \brief intersect SphereVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::SphereVolume &vol1, const OSG::SphereVolume &vol2);


/*! \brief intersect SphereVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::SphereVolume &vol1, const OSG::CylinderVolume &vol2);


/*! \brief intersect SphereVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::SphereVolume &vol1, const OSG::FrustumVolume &vol2);


/*! \brief intersect SphereVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::SphereVolume &vol1, const OSG::Volume &vol2);


// # Cylinder ########################################################

/*! \brief intersect CylinderVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
inline
bool intersect(const OSG::CylinderVolume &vol1, const OSG::BoxVolume &vol2);


/*! \brief intersect CylinderVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
inline
bool intersect(const OSG::CylinderVolume &vol1, const OSG::SphereVolume &vol2);


/*! \brief intersect CylinderVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::CylinderVolume &vol1, 
               const OSG::CylinderVolume &vol2);


/*! \brief intersect CylinderVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::CylinderVolume &vol1, const OSG::FrustumVolume &vol2);


/*! \brief intersect CylinderVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::CylinderVolume &vol1, const OSG::Volume &vol2);


// # Frustum ########################################################

/*! \brief intersect FrustumVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
inline
bool intersect(const OSG::FrustumVolume &vol1, const OSG::BoxVolume &vol2);


/*! \brief intersect FrustumVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
inline
bool intersect(const OSG::FrustumVolume &vol1, const OSG::SphereVolume &vol2);


/*! \brief intersect FrustumVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
inline
bool intersect(const OSG::FrustumVolume  &vol1, 
               const OSG::CylinderVolume &vol2);


/*! \brief intersect FrustumVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::FrustumVolume &vol1, const OSG::FrustumVolume &vol2);


/*! \brief intersect FrustumVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
bool intersect(const OSG::FrustumVolume &vol1, const OSG::Volume &vol2);


// # Volume ########################################################

/*! \brief extend Volume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
inline
bool intersect(const OSG::Volume &srcVol, const OSG::BoxVolume &vol);


/*! \brief extend Volume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
inline
bool intersect(const OSG::Volume &srcVol, const OSG::SphereVolume &vol);


/*! \brief extend Volume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
inline
bool intersect(const OSG::Volume &srcVol, const OSG::CylinderVolume &vol);


/*! \brief extend Volume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
inline
bool intersect(const OSG::Volume &srcVol, const OSG::FrustumVolume  &vol);

// ###################################################################
// # Volume Extend Functions #########################################
// ###################################################################

/*! @name Extend
 */

/*! \brief extend Volume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso Volume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::Volume &srcVol, const OSG::Volume &vol);


// # Box #############################################################

/*! \brief extend BoxVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::BoxVolume &srcVol, const OSG::BoxVolume &vol);


/*! \brief extend BoxVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::BoxVolume &srcVol, const OSG::SphereVolume &vol);


/*! \brief extend BoxVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::BoxVolume &srcVol, const OSG::CylinderVolume &vol);


/*! \brief extend BoxVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::BoxVolume &srcVol, const OSG::FrustumVolume &vol);


/*! \brief extend BoxVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso BoxVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::BoxVolume &srcVol, const OSG::Volume &vol);


// # Sphere ###########################################################

/*! \brief extend SphereVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::SphereVolume &srcVol, const OSG::BoxVolume &vol);


/*! \brief extend SphereVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING
void extend(OSG::SphereVolume &srcVol, const OSG::SphereVolume &vol);


/*! \brief extend SphereVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::SphereVolume &srcVol, const OSG::CylinderVolume &vol);


/*! \brief extend SphereVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::SphereVolume &srcVol, const OSG::FrustumVolume &vol);


/*! \brief extend SphereVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso SphereVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::SphereVolume &srcVol, const OSG::Volume &vol);


// # Cylinder ########################################################

/*! \brief extend CylinderVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::CylinderVolume &srcVol, const OSG::BoxVolume &vol);


/*! \brief extend CylinderVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::CylinderVolume &srcVol, const OSG::SphereVolume &vol);


/*! \brief extend CylinderVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::CylinderVolume &srcVol, const OSG::CylinderVolume &vol);


/*! \brief extend CylinderVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::CylinderVolume &srcVol, const OSG::FrustumVolume &vol);


/*! \brief extend CylinderVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso CylinderVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::CylinderVolume &srcVol, const OSG::Volume &vol);


// # Frustum ########################################################

/*! \brief extend FrustumVolume / BoxVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::FrustumVolume &srcVol, const OSG::BoxVolume &vol);


/*! \brief extend FrustumVolume / SphereVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::FrustumVolume &srcVol, const OSG::SphereVolume &vol);


/*! \brief extend FrustumVolume / CylinderVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::FrustumVolume &srcVol, const OSG::CylinderVolume &vol);


/*! \brief extend FrustumVolume / FrustumVolume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::FrustumVolume &srcVol, const OSG::FrustumVolume &vol);


/*! \brief extend FrustumVolume / Volume
    \ingroup GrpBaseBaseVolume
    \relatesalso FrustumVolume
 */
OSG_BASE_DLLMAPPING 
void extend(OSG::FrustumVolume &srcVol, const OSG::Volume &vol);

OSG_END_NAMESPACE

#include "OSGVolumeFunctions.inl"

#endif /* OSGVOLUMEINTERSECTFUNCTIONS_H */

