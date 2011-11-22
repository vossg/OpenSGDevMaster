/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

#ifndef _OSGGEOOPTIMIZATION_H_
#define _OSGGEOOPTIMIZATION_H_

#include "OSGDrawableDef.h"

OSG_BEGIN_NAMESPACE

class Geometry;

// The algorithms here are meant to perform various optimizations/remappings
// on geometry. They are currently EXPERIMENTAL.
// Algorithms are probably best run in order from top to bottom.

OSG_DRAWABLE_DLLMAPPING
void makeSingleIndexed(Geometry *geo);

OSG_DRAWABLE_DLLMAPPING
void makeIndexedTriangles(Geometry *geo);

OSG_DRAWABLE_DLLMAPPING
void makeOptimizedIndex(Geometry *geo);

OSG_DRAWABLE_DLLMAPPING
void makeOptimizedProperties(Geometry *geo);

OSG_END_NAMESPACE

#endif /* _OSGGEOOPTIMIZATION_H_ */
