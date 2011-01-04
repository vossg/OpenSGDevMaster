/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGGEOFUNCTIONS_H_
#define _OSGGEOFUNCTIONS_H_

#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGBaseTypes.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                 Calc properties functions                   */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING 
void    calcVertexNormals        (Geometry   *geo        );

OSG_DRAWABLE_DLLMAPPING 
void    calcVertexNormals        (Geometry   *geo,
                                  Real32      creaseAngle);
OSG_DRAWABLE_DLLMAPPING 
void    calcFaceNormals          (Geometry   *geo        );

OSG_DRAWABLE_DLLMAPPING 
void    calcVertexTangentsProp   (Geometry   *geo,
                                  UInt32      srcTexProp,
                                  UInt32      srcNormalProp,
                                  UInt32      dstPropTan,
                                  UInt32      dstPropBin);

OSG_DRAWABLE_DLLMAPPING 
void    calcVertexTangents       (Geometry   *geo,
                                  UInt32      srcTexIndex,
                                  UInt32      dstPropTan,
                                  UInt32      dstPropBin);

OSG_DRAWABLE_DLLMAPPING
void    calcVertexTexCoordsProp2D(Geometry            *geo,
                                  UInt32               propIndex = 
                                                     Geometry::TexCoordsIndex);

OSG_DRAWABLE_DLLMAPPING
void    calcVertexTexCoords      (Geometry            *geo,
                                  UInt32               texIndex = 0);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                   Conversion functions                       */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING 
Int32   setIndexFromVRMLData     (     Geometry       *geo,
                                  std::vector<Int32>  &coordIndex,
                                  std::vector<Int32>  &normalIndex,
                                  std::vector<Int32>  &colorIndex,
                                  std::vector<Int32>  &texCoordIndex,
                                       bool            convex          = true,
                                       bool            ccw             = true,
                                       bool            normalPerVertex = true,
                                       bool            colorPerVertex  = true,
                                       bool            createNormal    = true,
                                       bool            faceSet         = true);

OSG_DRAWABLE_DLLMAPPING 
Int32 setIndexFromIndexedX3DData (     Geometry       *geo,
                                  std::vector<Int32>  &coordIndex,
                                  std::vector<Int32>  &normalIndex,
                                  std::vector<Int32>  &colorIndex,
                                  std::vector<Int32>  &texCoordIndex,
                                       Int32           primitiveType   = 
                                                                    GL_POLYGON,
                                       bool            convex          = true,
                                       bool            ccw             = true,
                                       bool            normalPerVertex = true,
                                       bool            colorPerVertex  = true,
                                       bool            createNormal    = true);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                   Optimization functions                     */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING 
Int32   createOptimizedPrimitives(Geometry       *geo,
                                  UInt32          iteration       = 1,
                                  bool            createStrips    = true,
                                  bool            createFans      = true,
                                  UInt32          minFanEdgeCount = 8,
                                  bool            colorCode       = false,
                                  bool            stitchStrips    = false);

OSG_DRAWABLE_DLLMAPPING 
void    createConvexPrimitives   (Geometry       *geo);

OSG_DRAWABLE_DLLMAPPING 
Int32   createSharedIndex        (Geometry       *geo);

OSG_DRAWABLE_DLLMAPPING 
Int32   createSingleIndex        (Geometry       *geo);

OSG_DRAWABLE_DLLMAPPING 
UInt32  calcPrimitiveCount       (Geometry       *geo,
                                  UInt32         &triangle,
                                  UInt32         &line,
                                  UInt32         &point);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                 Debug Geometry functions                     */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING 
NodeTransitPtr calcVertexNormalsGeo    (Geometry *geo, 
                                        Real32    length);

OSG_DRAWABLE_DLLMAPPING 
void updateVertexNormalsGeo            (      Geometry *pGeo, 
                                              Real32    length,
                                        const Geometry *pRefGeo);

OSG_DRAWABLE_DLLMAPPING 
NodeTransitPtr calcFaceNormalsGeo      (Geometry *geo, 
                                        Real32    length);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                   Merge helper functions                     */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING 
void    separateProperties             (Geometry *geo);


OSG_DRAWABLE_DLLMAPPING 
void    mergeGeometries         (std::vector<Node *> &nodes,
                                 std::vector<Node *> &results);

OSG_DRAWABLE_DLLMAPPING
bool mergeableGeo(const Geometry *geo1, const Geometry *geo2);

OSG_DRAWABLE_DLLMAPPING             
GeometryTransitPtr mergeGeo(const Geometry *geo1, const Geometry *geo2);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                   Global Helper                              */
/*! \{                                                                 */

OSG_DRAWABLE_DLLMAPPING
void setVBOUsageOnPropertyProtos(bool bVal);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGGeoFunctions.inl"

#endif /* _OSGGEOFUNCTIONS_H_ */
