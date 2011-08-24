/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGINTERSECTKDTREE_H_
#define _OSGINTERSECTKDTREE_H_

#include "OSGConfig.h"
#include "OSGDrawableDef.h"
#include "OSGIntersectKDTreeNodeFields.h"
#include "OSGLine.h"
#include "OSGSysFields.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

class Geometry;

OSG_DRAWABLE_DLLMAPPING void
buildIntersectKDTree(Geometry              *geo,
                     Int32                  maxDepth,
                     MFIntersectKDTreeNode *mfNodes,
                     MFUInt32              *mfTriIndices);

OSG_DRAWABLE_DLLMAPPING void
buildSplitPlanePositions(const BoxVolume             &bounds,
                         const MFIntersectKDTreeNode *mfNodes,
                               UInt32                 maxDepth,
                               GeoPnt3fProperty      *pnts     );

OSG_DRAWABLE_DLLMAPPING bool
intersectIntersectKDTree(const Line                  &ray,
                         const BoxVolume             &bounds,
                               Geometry              *geo,
                         const MFIntersectKDTreeNode *mfNodes,
                         const MFUInt32              *mfTriIndices,
                               Real32                &closestHitT,
                               Vec3f                 &hitNormal,
                               UInt32                &hitTriangle,
                               UInt32                *numTris      = NULL);

OSG_END_NAMESPACE

#endif // _OSGINTERSECTKDTREE_H_

