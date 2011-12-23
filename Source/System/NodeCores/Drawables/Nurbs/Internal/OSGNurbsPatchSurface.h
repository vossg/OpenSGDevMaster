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
#ifndef _OSG_NurbsPatchSurface_h
#define _OSG_NurbsPatchSurface_h
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawableDef.h"
#include "OSGConfig.h"


#include "OSGBaseTypes.h"
#include "OSGVector.h"

// DCTP-lib includes
#include "OSGdctptypes.h"
#include "OSGBezierCurve2D.h"
#include "OSGBSplineTrimmedSurface.h"
#include "OSGDCTPMesh.h"

// own includes
#include "OSGGraphTraverser.h"
#include "OSGErrorQuadTree.h"   // needed due to arbitrary split -> new tree generation stuff
#include "OSGQuadTreeCreator.h" // needed due to quadtree moved back to class variable
#include "OSGParSpaceTrimmer.h" // needed due to triangle reduction at trimming curves

OSG_BEGIN_NAMESPACE

#define OSG_TIMING_FUNCS

static const unsigned char BEZIER_SURFACES_VALID = 0x01;
static const unsigned char QUAD_TREE_VALID     = 0x02;
static const unsigned char TRIMMING_VALID      = 0x04;
static const unsigned char TRIANGULATION_VALID = 0x08;
static const unsigned char INTERVALS_VALID     = 0x10;
static const unsigned char TRIM_SEGS_VALID     = 0x20;

static const unsigned char QUAD_TREE_ERROR = 0x80;

static const unsigned char QUAD_TREE_INVALID_MASK = BEZIER_SURFACES_VALID | TRIM_SEGS_VALID;

// Activate the OpenSG namespace
//OSG_USING_NAMESPACE

struct SCone
{
    Vec3d clDirection;
//	double					dHalfAngle;
    double dThreshold;
};

struct SSurface
{
    double dError;
    float fMinError;
    float fMaxError;
    unsigned char ucStatus;
    bezier2ddequevector vvclBezierCurves;
    bezier3ddequevector vvcl3DCurves;
    std::vector<std::vector<Vec2d> > vvclEdgeLoops;
    std::vector<std::vector<Vec3d> > vvclEdgeLoops3D;
// added to comply with ParSpaceTrimmer when using FORCE_NO_T_VERTICES
    std::vector<std::vector<Vec3d> > vvclEdgeLoopsNorm;
    std::vector<std::vector<Vec2d> > vvclEdgeLoopsTex;
    Vec3d clMin;
    Vec3d clMax;
    CErrorQuadTree *pclErrorTree;
    unsigned int uiTriangleCnt;
    std::vector<bool> vbReversed;
    std::vector<bool> vbUsed;
    SCone tNormalCone;
#ifdef OSG_ARBITRARY_SPLIT
    Vec2d clMinParam;
    Vec2d clMaxParam;
#endif
};

class OSG_DRAWABLE_DLLMAPPING CNurbsPatchSurface
{

  public:

    CNurbsPatchSurface();

    ~CNurbsPatchSurface();

    // add surface patch
    void AddSurface(BSplineTrimmedSurface *clSurface);

    // set error for given surface patch
    void SetError(const unsigned int cuiSurface, double dError);


    // return pointer to meshes and recalculate what is needed
//	std::vector< NodePtr >* GetNodes( std::ofstream &meshout, std::ofstream &rclLinesOut, std::ofstream &rclLinesOut2 );

//	std::vector< NodePtr >* GetNodes( void );

    // returns the number of surfaces
    unsigned int GetSurfaceNumber() const
    {
        return UInt32( m_vtSurfaces.size());
    }

    // returns if node is valid
    bool IsNodeValid(unsigned int uiNode) const
    {
        return (m_vtSurfaces[uiNode].ucStatus & TRIANGULATION_VALID) ? true : false;
    }

    // new interface:
    // set surface
    void setSurface(BSplineTrimmedSurface *clSurface, std::vector<Pnt2f> &texturecps, bool bUseTextures = false);
    // set error
    void setError(double dError);
    // get tessellated geometry
    void getTessellation(std::vector<Pnt3f> &        gverts,
                         std::vector<Vec3f> &        norms,
                         std::vector<SimplePolygon> &tris,
                         bool                        usedelaunay);
    void getTessellation(std::vector<Pnt3f> &        gverts,
                         std::vector<Vec3f> &        norms,
                         std::vector<Pnt2f> &        texturecoords,
                         std::vector<SimplePolygon> &tris,
                         bool                        usedelaunay);
    void getTessellation(std::vector<Pnt3f> &        gverts,
                         std::vector<Pnt2f> &        texturecoords,
                         std::vector<SimplePolygon> &tris,
                         bool                        usedelaunay);
    void calculateNormals(std::vector<Vec3f> &norms);
    void calculatePointsAndNormals(
        std::vector<Pnt3f> &        gverts,
        std::vector<SimplePolygon> &tris,
        std::vector<Vec3f> &        norms);
    void calculatePointsNormalsAndTextureCoords(
        std::vector<Pnt3f> &        gverts,
        std::vector<SimplePolygon> &tris,
        std::vector<Vec3f> &        norms,
        std::vector<Pnt2f> &        texturecoords);
    void calculatePointsAndTextureCoords(
        std::vector<Pnt3f> &        gverts,
        std::vector<SimplePolygon> &tris,
        std::vector<Pnt2f> &        texturecoords);


    // get internal representation (Surface + additional data)
    inline SSurface * getSurfaceData()
    {
        return &m_vtSurfaces[0];
    }

#ifdef OSG_TIMING_FUNCS
    unsigned int GetTotalTriangleCnt() const
    {
        return m_uiTotalTriangleCnt;
    }
    unsigned int GetNewTriangleCnt() const
    {
        return m_uiNewTriangleCnt;
    }
#endif

    void setupErrorTree(double dError);

    void clearEdgeloopNormals()
    {
        m_vtSurfaces[0].vvclEdgeLoopsNorm.clear();
    }

  private:

    // convert surface to piecewise bezier form
    void ConvertToBezier(unsigned int uiSurface);

    // set up quad tree with saved error
    void CalculateQuadTree(unsigned int uiSurface, bool bForEdges);

    // calculate finest trimming curve
    void CalculateTrimmingLoops(unsigned int uiSurface);

    // calculate actual trimming curve
    void CalculateActualTrimming(unsigned int uiSurface);

    // perform graph traversal
    void CalculateGraph(unsigned int uiSurface, bool usedelaunay);

    // convert points from parameter to object space
    void ConvertPoints(unsigned int uiSurface);
    void convertPoints(std::vector<Pnt3f> &        gverts,
                       std::vector<SimplePolygon> &tris);

    // compute the normalcone (needed for backface culling)
    void ComputeNormalCone(const unsigned int  cuiSurface,
                           std::vector<Vec3f>& normals);

    void Gen3DLoops(const unsigned int cuiSurface);
    void CutCurve(const unsigned int cuiSurface, BezierCurve2D &rclCurve, bezier2ddeque &rclCut, std::vector<unsigned int> &rvuiUSeg, std::vector<unsigned int> &rvuiVSeg);

    std::vector<BSplineTrimmedSurface> m_vclBSplineSurfaces;
    std::vector<beziersurfacematrix>   m_vvvclBezierSurfaces;
    std::vector<std::vector<double> >  m_vvdUParams;
    std::vector<std::vector<double> >  m_vvdVParams;
    DCTPMesh                           m_clMesh;
    std::vector<SSurface>              m_vtSurfaces;
    std::vector<Vec2d>                 m_vclParameterVertices;
    std::vector<Vec3d>                 m_vclGlobalVertices;
//	std::vector< Vec3d >			m_vclNormal;
    DirectedGraph<Vec2d, unsigned char> *m_pclGraph;
    simplepolygonvector                  m_vclTriangles;
    QuadTreeCreator                     *m_pclQuadTree;
    bool                                 m_bErrorTreeValid;
    bool                                 m_bUseTextures;
    std::vector<std::vector<Vec2d> >     m_vvTextureControlPoints;

#ifdef OSG_TIMING_FUNCS
    unsigned int m_uiTotalTriangleCnt;
    unsigned int m_uiNewTriangleCnt;
#endif

#ifdef OSG_KEEP_2D_POINTS
    std::vector<unsigned int> m_vuiIndex;
#endif
};

OSG_END_NAMESPACE

#endif
