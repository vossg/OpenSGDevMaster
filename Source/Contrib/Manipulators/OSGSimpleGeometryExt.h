/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


#ifndef _OSGSIMPLEGEOMETRYEXT_H_
#define _OSGSIMPLEGEOMETRYEXT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGNode.h"
#include "OSGContribGUIDef.h"
#include "OSGGeometry.h"
#include "OSGMaterial.h"
#include "OSGColor.h"
#include "OSGGL.h"

#include "OSGPolygonChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMatrixUtility.h"

OSG_BEGIN_NAMESPACE


/*---------------------------------------------------------------------*/
/*! \name                   Construction functions                     */
/*! \{                                                                 */

/*! \brief create a grid geometry
 *  \ingroup SimpleGeometry
 */
OSG_CONTRIBGUI_DLLMAPPING 
GeometryTransitPtr makeGridGeo(const Real32   width,
                               const Real32   depth,
                               const Real32   horCellWidth,
                               const Color3f &color       );


/*! \brief create a grid
 *  \ingroup SimpleGeometry
 */
OSG_CONTRIBGUI_DLLMAPPING 
NodeTransitPtr makeGrid(const Real32   width,
                        const Real32   depth,
                        const Real32   horCellWidth,
                        const Color3f &color       );

OSG_CONTRIBGUI_DLLMAPPING 
NodeTransitPtr makeSelection(Node *);

OSG_CONTRIBGUI_DLLMAPPING 
GeometryTransitPtr makeSelectionGeo(Node *);


/*! \brief create a coord-axis
 *  \ingroup SimpleGeometry
 */

PolygonChunk *getPolygonChunk(const UInt16 faces = GL_FRONT_AND_BACK, 
                              const UInt16 mode = GL_LINE);

MaterialChunk *getMaterialChunk(const Color4f &ambientColor,
                                const Color4f &diffuseColor,
                                const Color4f &specularColor = Color4f(1, 1, 1, 1),
                                const bool     lit = false                     );

ChunkMaterial *getSelectionMaterial();

										   

/*! \}                                                                 */

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEGEOMETRYEXT_H_ */
