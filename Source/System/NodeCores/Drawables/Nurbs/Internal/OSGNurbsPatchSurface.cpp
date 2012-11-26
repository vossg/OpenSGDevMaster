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
#include "OSGLog.h"

#include "OSGQuadTreeCreator.h"
#include "OSGParSpaceTrimmer.h"
#include "OSGNurbsPatchSurface.h"
//#include <DCTPBoundary.h>
#include "OSGpredicates.h"   // for exactinit
//#include "rounding.h"	// for FPU_ROUND_DOUBLE
#include "OSGSurface.h"

#include <map>

//#include "BoundarySimplifier/BoundaryObject.h"

OSG_USING_NAMESPACE

//put miniball inside OSG namespace
//#include "miniball/miniball.H"

#ifdef WIN32
#pragma warning (disable : 985)
#endif

//#define DRAW_LINES
#define OSG_VEC_COMPUTE

//static unsigned int g_uiColor = 0;

#ifdef WRITE_STAT
static double    g_dTrimmingConversionTime    = 0.0;
static double    g_dTrimmingApproximationTime = 0.0;
static OSG::Time g_clTrimmingApproximationStart;
static double    g_dTotalTime = 0.0;
static OSG::Time g_clTotalStart;
static OSG::Time g_clActTime;
#endif

#define OSG_3D_LOOPS

CNurbsPatchSurface::CNurbsPatchSurface()
{
    m_pclGraph        = NULL;
    m_bErrorTreeValid = false;
    m_pclQuadTree     = NULL;
}


CNurbsPatchSurface::~CNurbsPatchSurface()
{
//    unsigned int ui_idx;

    if(m_pclGraph)
    {
        delete m_pclGraph;
    }

    for(unsigned int ui_number = 0; ui_number < m_vtSurfaces.size(); ++ui_number)
    {
        delete m_vtSurfaces[ui_number].pclErrorTree;
    }

    m_vclBSplineSurfaces.clear();
    m_vvvclBezierSurfaces.clear();
    m_vvdUParams.clear();
    m_vvdVParams.clear();
    m_vtSurfaces.clear();
//	m_vpclNodes.clear( );
    if(m_pclQuadTree != NULL)
    {
        delete m_pclQuadTree;
        m_pclQuadTree = NULL;
    }
}


// add surface patch
void CNurbsPatchSurface::AddSurface(BSplineTrimmedSurface *clSurface)
{
#ifdef WRITE_STAT
    g_clTotalStart = OSG::getSystemTime();
#endif

    unsigned int ui_number = UInt32(m_vclBSplineSurfaces.size());

//	std::cerr << "\rreading surface " << ui_number + 1;

    // resize vectors
    m_vclBSplineSurfaces.resize(ui_number + 1);
    m_vvvclBezierSurfaces.resize(ui_number + 1);
    m_vvdUParams.resize(ui_number + 1);
    m_vvdVParams.resize(ui_number + 1);
//	m_vclSeperateMeshes.resize( ui_number + 1 );
//	m_vclSewedMeshes.resize( ui_number + 1 );
    m_vtSurfaces.resize(ui_number + 1);
//	m_vtTrimmingCurves.resize( ui_number + 1 );
//	m_vpclNodes.resize( ui_number + 1 );


    // copy and init values
    m_vclBSplineSurfaces[ui_number]       = *clSurface;
    m_vtSurfaces[ui_number].dError        = 10.0;
    m_vtSurfaces[ui_number].ucStatus      = 0;
    m_vtSurfaces[ui_number].pclErrorTree  = new CErrorQuadTree();
    m_bErrorTreeValid                     = true;
    m_vtSurfaces[ui_number].uiTriangleCnt = 0;

    // calculate initial values
    ConvertToBezier(ui_number);

#ifdef WRITE_STAT
    g_clActTime                = OSG::getSystemTime();
    g_dTotalTime              += g_clActTime - g_clTotalStart;
    g_dTrimmingConversionTime += g_clActTime - g_clTotalStart;
#endif
}

//FIXME: quick hack
void CNurbsPatchSurface::setSurface(BSplineTrimmedSurface *clSurface,
                                    std::vector<Pnt2f> &   texturecps,
                                    bool                   bUseTextures)
{
    //FIXME: I'm not sure how much of these reinits is actually needed
    if(m_pclGraph)
    {
        delete m_pclGraph;
        m_pclGraph = NULL;
    }

    for(unsigned int ui_number = 0; ui_number < m_vtSurfaces.size(); ++ui_number)
    {
        delete m_vtSurfaces[ui_number].pclErrorTree;
        m_vtSurfaces[ui_number].pclErrorTree = NULL;
    }

    m_vclBSplineSurfaces.clear();
    m_vvvclBezierSurfaces.clear();
    m_vvdUParams.clear();
    m_vvdVParams.clear();
    m_vtSurfaces.clear();
    //FIXME END

//    std::cerr<<"setSurface: m_vtSurfaces.size(): " << m_vtSurfaces.size() <<
//            std::endl;
    AddSurface(clSurface);

    m_bUseTextures = bUseTextures;
    if(m_bUseTextures)
    {
        UInt32                k = 0;
        UInt32                i, j;
        BSplineTensorSurface &tensor_surface = clSurface->getSurface();
        DCTPVec4dmatrix &     surf_cps       = tensor_surface.getControlPointMatrix();
        UInt32                u_size         = UInt32(surf_cps.size());
        UInt32                v_size         = UInt32(surf_cps[0].size());
        Vec2d                 tempv2d;
        if( (u_size * v_size) != texturecps.size() )
        {
            std::cerr << "setSurface: wrong number of texture control points, texturing disabled" << std::endl;
            m_bUseTextures = false;
            return;
        }
        m_vvTextureControlPoints.resize(u_size);

        for(i = 0; i < u_size; ++i)
        {
            m_vvTextureControlPoints[i].resize(v_size);
        }

        for(i = 0; i < u_size; ++i)
        {
            for(j = 0; j < v_size; ++j)
            {
                tempv2d[0]                     = texturecps[k][0];
                tempv2d[1]                     = texturecps[k][1];
                m_vvTextureControlPoints[i][j] = tempv2d;
                k++;
            }
        }

    }
}

void CNurbsPatchSurface::setupErrorTree(double dError)
{
    double d_old_err = m_vtSurfaces[0].dError;

    m_vtSurfaces[0].dError = dError;
    CalculateQuadTree(0, false);
    m_clMesh.reinit();
    m_vtSurfaces[0].dError = d_old_err;
}

void CNurbsPatchSurface::setError(double dError)
{
    if(m_pclGraph)
    {
        delete m_pclGraph;
        m_pclGraph = NULL;
    }
    m_vtSurfaces[0].vvclEdgeLoops.clear();
    m_vtSurfaces[0].vvclEdgeLoops3D.clear();
    m_vtSurfaces[0].vvclEdgeLoopsNorm.clear();
    m_vtSurfaces[0].vvclEdgeLoopsTex.clear();
    SetError(0, dError);
}

//less hack...
//normal tessellation, no texture
void CNurbsPatchSurface::getTessellation(std::vector<Pnt3f> &        gverts,
                                         std::vector<Vec3f> &        norms,
                                         std::vector<SimplePolygon> &tris,
                                         bool                        usedelaunay)
{
#ifdef WRITE_STAT
    g_clTotalStart = OSG::getSystemTime();
#endif

    if( (m_vtSurfaces[0].ucStatus & BEZIER_SURFACES_VALID) &&
        ( (m_vtSurfaces[0].ucStatus & TRIM_SEGS_VALID) == 0) )
    {
#ifdef WRITE_STAT
        g_clTrimmingApproximationStart = OSG::getSystemTime();
#endif
        CalculateQuadTree(0, true);
        CalculateTrimmingLoops(0);
#ifdef WRITE_STAT
        g_clActTime                   = OSG::getSystemTime();
        g_dTrimmingApproximationTime += g_clActTime - g_clTrimmingApproximationStart;
#endif
        CalculateQuadTree(0, false);
//		std::cerr << "\rtesselating surface " << ui_surface + 1;
        CalculateActualTrimming(0);
        CalculateGraph(0, usedelaunay);
//		ConvertPoints( 0 );
////	convertPoints( gverts, tris );
        if(m_pclGraph)
        {
            delete m_pclGraph;
            m_pclGraph = NULL;
        }
//		BuildNode( ui_surface );
////	calculateNormals( norms );
        calculatePointsAndNormals(gverts, tris, norms);
        ComputeNormalCone(0, norms);
        m_vclParameterVertices.clear();
        m_vclGlobalVertices.clear();
        m_vclTriangles.clear();
    }
    else
    {
        std::cerr << "shouldn't be here..." << std::endl;
    }
//		std::cerr << std::endl;
#ifdef WRITE_STAT
    g_clActTime   = OSG::getSystemTime();
    g_dTotalTime += g_clActTime - g_clTotalStart;
//	std::cerr << "conversion " << g_dTrimmingConversionTime << " sec" << std::endl;
//	std::cerr << "trimming   " << g_dTrimmingApproximationTime << " sec " << std::endl;
//	std::cerr << "total      " << g_dTotalTime << " sec" << std::endl;
#endif
}

//normal tessellation, texturemapping: both normals and texturecoords
void CNurbsPatchSurface::getTessellation(std::vector<Pnt3f> &        gverts,
                                         std::vector<Vec3f> &        norms,
                                         std::vector<Pnt2f> &        texturecoords,
                                         std::vector<SimplePolygon> &tris,
                                         bool                        usedelaunay)
{

    if( (m_vtSurfaces[0].ucStatus & BEZIER_SURFACES_VALID) &&
        ( (m_vtSurfaces[0].ucStatus & TRIM_SEGS_VALID) == 0) )
    {
        CalculateQuadTree(0, true);
        CalculateTrimmingLoops(0);
        CalculateQuadTree(0, false);
//			std::cerr << "\rtesselating surface " << ui_surface + 1;
        CalculateActualTrimming(0);
        CalculateGraph(0, usedelaunay);
        if(m_pclGraph)
        {
            delete m_pclGraph;
            m_pclGraph = NULL;
        }
//			BuildNode( ui_surface );
////			calculateNormals( norms );
        calculatePointsNormalsAndTextureCoords(gverts,
                                               tris,
                                               norms,
                                               texturecoords);
        ComputeNormalCone(0, norms);
        m_vclParameterVertices.clear();
        m_vclGlobalVertices.clear();
        m_vclTriangles.clear();
    }
    else
    {
        std::cerr << "shouldn't be here..." << std::endl;
    }
//		std::cerr << std::endl;

}

// get tessellation, using normalmaps (texcoords, but not normals!)
void CNurbsPatchSurface::getTessellation(std::vector<Pnt3f> &        gverts,
                                         std::vector<Pnt2f> &        texturecoords,
                                         std::vector<SimplePolygon> &tris,
                                         bool                        usedelaunay)
{
//	Real64 d_time, d_last_time;
//	d_last_time = getSystemTime();

    if( (m_vtSurfaces[0].ucStatus & BEZIER_SURFACES_VALID) &&
        ( (m_vtSurfaces[0].ucStatus & TRIM_SEGS_VALID) == 0) )
    {
//		std::cerr << "CalculateQuadTree";// << std::endl;
        CalculateQuadTree(0, true);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;
        std::cerr << "CalculateTrimmingLoops";// << std::endl;*/
        CalculateTrimmingLoops(0);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;
        std::cerr << "CalculateQuadTree";// << std::endl;*/
        CalculateQuadTree(0, false);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;
//		std::cerr << "\rtesselating surface " << ui_surface + 1;
        std::cerr << "CalculateActualTrimming";// << std::endl;*/
        CalculateActualTrimming(0);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;
        std::cerr << "CalculateGraph";// << std::endl;*/
        CalculateGraph(0, usedelaunay);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;*/
//		ConvertPoints( 0 );
////		convertPoints( gverts, tris );
        if(m_pclGraph)
        {
            delete m_pclGraph;
            m_pclGraph = NULL;
        }
//		BuildNode( ui_surface );
////	calculateNormals( norms );
//                        calculatePointsAndNormals( gverts, tris, norms );
//		std::cerr << "calculatePointsAndTextureCoords";// << std::endl;
        calculatePointsAndTextureCoords(gverts, tris, texturecoords);
/*		d_time = getSystemTime();
        std::cerr << " " << d_time - d_last_time << std::endl;
        d_last_time = d_time;
//                       ComputeNormalCone( 0, norms );
        std::cerr << "clearing" << std::endl;*/
        m_vclParameterVertices.clear();
        m_vclGlobalVertices.clear();
        m_vclTriangles.clear();
    }
    else
    {
        std::cerr << "shouldn't be here..." << std::endl;
    }
//		std::cerr << std::endl;


}



void CNurbsPatchSurface::calculatePointsAndNormals(
    std::vector<Pnt3f> &        gverts,
    std::vector<SimplePolygon> &tris,
    std::vector<Vec3f> &        norms)
{
    BSplineTensorSurface cl_surf;

//	std::cerr << "c" << std::endl;

    cl_surf = m_vclBSplineSurfaces[0].getSurface();
    // NOTE: also computes 3D vertex info in the gverts array
#ifdef OSG_VEC_COMPUTE
    cl_surf.computeNormal(m_vclParameterVertices,
                          gverts,
                          norms);
#else
    gverts.resize(m_vclParameterVertices.size() );
    norms.resize(m_vclParameterVertices.size() );

    for(unsigned int i = 0; i < m_vclParameterVertices.size(); ++i)
    {
        int i_err = 0;
        norms[i] = cl_surf.computeNormal(m_vclParameterVertices[i], i_err, gverts[i]);
    }

#endif
/*
    std::cerr<<"haho"<< m_vclParameterVertices.size() << " " << gverts.size() << " " << norms.size() << std::endl;
    for ( UInt32 i = 0; i < gverts.size(); ++i )
    {
        std::cerr << gverts[i] << " " << norms[i] << std::endl;
    }
*/
/*
    std::cerr<<"m_vclParameterVertices.size(): " << m_vclParameterVertices.size() << std::endl;
    for ( UInt32 i = 0; i < m_vclParameterVertices.size(); ++i )
    {
        std::cerr<< m_vclParameterVertices[i] << std::endl;
        if (osgabs(m_vclParameterVertices[i][1] - 8271.61) < 1.0f)
        {
            std::cerr<<"zeroing norm: " << i << std::endl;
            norms[i][0] = norms[i][1] = norms[i][2] = 0.f;
        }
    }
*/
    tris.clear();
    tris = m_vclTriangles;

    //copy the normals into the vvclEdgeLoopsNorm structure
    unsigned int numloops = UInt32(m_vtSurfaces[0].vvclEdgeLoops.size());
    unsigned int actlooplength;
#ifdef OSG_KEEP_2D_POINTS
    unsigned int ui_actvertidx = 0;
#endif

    Vec3d cl_norm;
//    Int32 i_err;
    m_vtSurfaces[0].vvclEdgeLoopsNorm.resize(numloops);
#ifndef OSG_FORCE_NO_T_VERTICES
    m_vtSurfaces[0].vvclEdgeLoops3D.resize(numloops);
#endif

    for(unsigned int ui_actloop = 0; ui_actloop < numloops; ++ui_actloop)
    {
        actlooplength = UInt32(m_vtSurfaces[0].vvclEdgeLoops[ui_actloop].size());
        m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop].resize(actlooplength);
#ifdef OSG_KEEP_2D_POINTS

        for(unsigned int ui_act = 0; ui_act < actlooplength; ++ui_act)
        {
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop][ui_act] =
                Vec3d(norms[ui_actvertidx][0],
                      norms[ui_actvertidx][1],
                      norms[ui_actvertidx][2]);

/*			std::cerr << norms[ ui_actvertidx ][0] << " ";
            std::cerr << norms[ ui_actvertidx ][1] << " ";
            std::cerr << norms[ ui_actvertidx ][2] << std::endl;*/

            ui_actvertidx++;
        }

#else
 #ifdef OSG_FORCE_NO_T_VERTICES
        cl_surf.computeNormalforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop]);
 #else
        cl_surf.computeNormalforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop],
            &m_vtSurfaces[0].vvclEdgeLoops3D[ui_actloop]);
 #endif
#endif
    }



}


void CNurbsPatchSurface::calculatePointsNormalsAndTextureCoords(
    std::vector<Pnt3f> &        gverts,
    std::vector<SimplePolygon> &tris,
    std::vector<Vec3f> &        norms,
    std::vector<Pnt2f> &        texturecoords)
{
    BSplineTensorSurface cl_surf;


    cl_surf = m_vclBSplineSurfaces[0].getSurface();
    // NOTE: also computes 3D vertex info in the gverts array
    cl_surf.computeNormal(m_vclParameterVertices,
                          gverts,
                          norms);
    // FIXME: this is a hack just to try out if it works.
    // FIXME: will need to modify OSGBSplineTensorSurface.cpp to have
    // FIXME: a fucnction that combines these two.
    std::vector<Pnt3f> dummyverts;
    cl_surf.computeTex(m_vclParameterVertices,
                       dummyverts,
                       texturecoords,
                       &m_vvTextureControlPoints);



/*
    std::cerr<<"haho"<< m_vclParameterVertices.size() << " " << gverts.size() << " " << norms.size() << std::endl;
    for ( UInt32 i = 0; i < gverts.size(); ++i )
    {
        std::cerr << gverts[i] << " " << norms[i] << std::endl;
    }
*/
    tris.clear();
    tris = m_vclTriangles;

    //copy the normals into the vvclEdgeLoopsNorm structure
    unsigned int numloops = UInt32(m_vtSurfaces[0].vvclEdgeLoops.size());
    unsigned int actlooplength;
    unsigned int ui_actloop;
#ifdef OSG_KEEP_2D_POINTS
    unsigned int ui_actvertidx = 0;
#endif

    Vec3d cl_norm;
//    Int32 i_err;
    m_vtSurfaces[0].vvclEdgeLoopsNorm.resize(numloops);
#ifndef OSG_FORCE_NO_T_VERTICES
    m_vtSurfaces[0].vvclEdgeLoops3D.resize(numloops);
#endif

    for(ui_actloop = 0; ui_actloop < numloops; ++ui_actloop)
    {
        actlooplength = UInt32(m_vtSurfaces[0].vvclEdgeLoops[ui_actloop].size());
        m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop].resize(actlooplength);
#ifdef OSG_KEEP_2D_POINTS

        for(unsigned int ui_act = 0; ui_act < actlooplength; ++ui_act)
        {
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop][ui_act] =
                Vec3d(norms[ui_actvertidx][0],
                      norms[ui_actvertidx][1],
                      norms[ui_actvertidx][2]);
            ui_actvertidx++;
        }

#else
 #ifdef OSG_FORCE_NO_T_VERTICES
        cl_surf.computeNormalforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop]);
 #else
        cl_surf.computeNormalforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsNorm[ui_actloop],
            &m_vtSurfaces[0].vvclEdgeLoops3D[ui_actloop]);
 #endif
#endif
    }


    //copy the texturecoords into the vvclEdgeLoopsTex structure
    numloops = UInt32(m_vtSurfaces[0].vvclEdgeLoops.size());
#ifdef OSG_KEEP_2D_POINTS
    ui_actvertidx = 0;
#endif

    m_vtSurfaces[0].vvclEdgeLoopsTex.resize(numloops);

    for(ui_actloop = 0; ui_actloop < numloops; ++ui_actloop)
    {
        actlooplength = UInt32(m_vtSurfaces[0].vvclEdgeLoops[ui_actloop].size());
        m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop].resize(actlooplength);
#ifdef OSG_KEEP_2D_POINTS

        for(unsigned int ui_act = 0; ui_act < actlooplength; ++ui_act)
        {
            m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop][ui_act] =
                Vec3d(texturecoords[ui_actvertidx][0],
                      texturecoords[ui_actvertidx][1],
                      texturecoords[ui_actvertidx][2]);
            ui_actvertidx++;
        }

#else
        cl_surf.computeTexforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop],
            &m_vvTextureControlPoints);
#endif
    }





}


void CNurbsPatchSurface::calculatePointsAndTextureCoords(
    std::vector<Pnt3f> &        gverts,
    std::vector<SimplePolygon> &tris,
    std::vector<Pnt2f> &        texturecoords)
{
    BSplineTensorSurface cl_surf;


    cl_surf = m_vclBSplineSurfaces[0].getSurface();
    cl_surf.computeTex(m_vclParameterVertices,
                       gverts,
                       texturecoords,
                       &m_vvTextureControlPoints);
/*
    std::cerr<<"haho"<< m_vclParameterVertices.size() << " " << gverts.size() << " " << norms.size() << std::endl;
    for ( UInt32 i = 0; i < gverts.size(); ++i )
    {
        std::cerr << gverts[i] << " " << norms[i] << std::endl;
    }
*/
    tris.clear();
    tris = m_vclTriangles;

    //copy the normals into the vvclEdgeLoopsNorm structure
    unsigned int numloops = UInt32(m_vtSurfaces[0].vvclEdgeLoops.size());
    unsigned int actlooplength;
#ifdef OSG_KEEP_2D_POINTS
    unsigned int ui_actvertidx = 0;
#endif

    Vec3d cl_norm;
//    Int32 i_err;
    m_vtSurfaces[0].vvclEdgeLoopsTex.resize(numloops);

    for(unsigned int ui_actloop = 0; ui_actloop < numloops; ++ui_actloop)
    {
        actlooplength = UInt32(m_vtSurfaces[0].vvclEdgeLoops[ui_actloop].size());
        m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop].resize(actlooplength);
#ifdef OSG_KEEP_2D_POINTS

        for(unsigned int ui_act = 0; ui_act < actlooplength; ++ui_act)
        {
            m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop][ui_act] =
                Vec3d(texturecoords[ui_actvertidx][0],
                      texturecoords[ui_actvertidx][1],
                      texturecoords[ui_actvertidx][2]);
            ui_actvertidx++;
        }

#else
        cl_surf.computeTexforTrimming(
            m_vtSurfaces[0].vvclEdgeLoops[ui_actloop],
            m_vtSurfaces[0].vvclEdgeLoopsTex[ui_actloop],
            &m_vvTextureControlPoints);
#endif
    }



}



// set error for given surface patch
void CNurbsPatchSurface::SetError(const unsigned int cuiSurface, double dError)
{
    if(cuiSurface >= m_vtSurfaces.size() )
    {
        return;
    }

//	std::cerr << "Setting error = " << dError << " for surface " << cuiSurface + 1 << "." << std::endl << std::endl;

    m_vtSurfaces[cuiSurface].dError = dError;
//	m_vtSurfaces[ cuiSurface ].ucStatus &= QUAD_TREE_INVALID_MASK;
    m_vtSurfaces[cuiSurface].ucStatus &= BEZIER_SURFACES_VALID;
}


// convert surface to piecewise bezier form
void CNurbsPatchSurface::ConvertToBezier(unsigned int uiSurface)
{
    BSplineTensorSurface&     rcl_bspline_surface  = m_vclBSplineSurfaces[uiSurface].getSurface();
    trimmingloop&             rvvcl_trimming_loops = m_vclBSplineSurfaces[uiSurface].getTrimmingLoops();
    bezier2dvector            vcl_beziertrimmingcurves;
    std::vector<unsigned int> vui_curves_per_loop(0);
    unsigned int              ui_tloops = UInt32(rvvcl_trimming_loops.size());
    unsigned int              ui_curve;

//	std::cerr << "Converting surface " << uiSurface + 1 << " to bezier form." << std::endl;

    vui_curves_per_loop.resize(ui_tloops);
    m_vtSurfaces[uiSurface].vvclBezierCurves.resize(ui_tloops);

//        std::cerr << "ConvertToBezier: numofloops: " << ui_tloops << std::endl;
    for(unsigned int ui_loop = 0; ui_loop < ui_tloops; ++ui_loop)
    {
        unsigned int ui_curves = UInt32(rvvcl_trimming_loops[ui_loop].size());
        unsigned int ui_prev   = ui_curves - 1;

        vui_curves_per_loop[ui_loop] = 0;
        vcl_beziertrimmingcurves.clear();

        for(ui_curve = 0; ui_curve < ui_curves; ++ui_curve)
        {
//			std::cerr << "processing curve " << ui_curve + 1 << std::endl;
            bezier2dvector vcl_converted_tmp;
            DCTPdvector    vd_pars;

            DCTPVec3dvector vcl_cp =
                rvvcl_trimming_loops[ui_loop][ui_prev].getControlPointVector();
            Vec3d cl_prev = vcl_cp[vcl_cp.size() - 1];
            vcl_cp = rvvcl_trimming_loops[ui_loop][ui_curve].getControlPointVector();
            if(DCTPVecIsNotEqual(cl_prev, vcl_cp[0]) )
            {
                BezierCurve2D   cl_temp;
                DCTPVec3dvector vcl_temp(2);

                vcl_temp[0] = cl_prev;
                vcl_temp[1] = vcl_cp[0];
                cl_temp.setControlPointVector(vcl_temp);
                cl_temp.optimizeDegree();
//				std::cerr << "inserting linear trimming curve to close gap." << std::endl;
//				std::cerr << vcl_temp[ 0 ] << " -> " << vcl_temp[ 1 ] << std::endl;
                vcl_beziertrimmingcurves.insert(vcl_beziertrimmingcurves.end(), cl_temp);
                ++vui_curves_per_loop[ui_loop];
            }
            ui_prev = ui_curve;

            if(rvvcl_trimming_loops[ui_loop][ui_curve].makeBezier(vcl_converted_tmp, vd_pars) )
            {
//				SWARNING << "Conversion of trimming loop " << ui_loop + 1;
//				SWARNING << " curve " << ui_curve + 1;
//				SWARNING << " surface " << uiSurface + 1 << " to bezier form failed!" << endLog;
            }
            else
            {
                vcl_beziertrimmingcurves.insert(
                    vcl_beziertrimmingcurves.end(), vcl_converted_tmp.begin(), vcl_converted_tmp.end() );
                vui_curves_per_loop[ui_loop] += UInt32(vcl_converted_tmp.size());
            }
        }

        // check for colinear trimming
        for(ui_curve = 0; ui_curve < vcl_beziertrimmingcurves.size(); ++ui_curve)
        {
            unsigned int ui_next = (ui_curve + 1) % vcl_beziertrimmingcurves.size();

            // check if both linear
            if( (vcl_beziertrimmingcurves[ui_curve].getControlPointVector().size() == 2) &&
                (vcl_beziertrimmingcurves[ui_next].getControlPointVector().size() == 2) &&
                (DCTPVecIsEqual(vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1],
                                vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0]) ) )
            {
                // check if colinear
                Vec2d cl_s0, cl_e0, cl_s1, cl_e1;
                Vec2d cl_tmp;

                cl_s0[0] = vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[0][0]
                           / vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[0][2];
                cl_s0[1] = vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[0][1]
                           / vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[0][2];

                cl_e0[0] = vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1][0]
                           / vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1][2];
                cl_e0[1] = vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1][1]
                           / vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1][2];

                cl_s1[0] = vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0][0]
                           / vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0][2];
                cl_s1[1] = vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0][1]
                           / vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0][2];

                cl_e1[0] = vcl_beziertrimmingcurves[ui_next].getControlPointVector()[1][0]
                           / vcl_beziertrimmingcurves[ui_next].getControlPointVector()[1][2];
                cl_e1[1] = vcl_beziertrimmingcurves[ui_next].getControlPointVector()[1][1]
                           / vcl_beziertrimmingcurves[ui_next].getControlPointVector()[1][2];

                cl_tmp = cl_e1 - cl_s0;

                cl_tmp *= 1.0 / sqrt(cl_tmp.squareLength() );
                cl_tmp *= cl_tmp.dot(cl_e0 - cl_s0);
                cl_tmp -= cl_e0 - cl_s0;

                if(cl_tmp.squareLength() < DCTP_EPS * DCTP_EPS)
                {
                    if(ui_next == 0)
                    {
                        vcl_beziertrimmingcurves[ui_next].getControlPointVector()[0] =
                            vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[0];
                    }
                    else
                    {
                        vcl_beziertrimmingcurves[ui_curve].getControlPointVector()[1] =
                            vcl_beziertrimmingcurves[ui_next].getControlPointVector()[1];

                        for( ; ui_next < vcl_beziertrimmingcurves.size() - 1; ++ui_next)
                        {
                            vcl_beziertrimmingcurves[ui_next] = vcl_beziertrimmingcurves[ui_next + 1];
                        }
                    }
                    vcl_beziertrimmingcurves.pop_back();
                    --ui_curve;
                }
            }
        }

        vui_curves_per_loop[ui_loop] = UInt32(vcl_beziertrimmingcurves.size());

//		std::cerr << "loop " << ui_loop + 1 << " contains " << vui_curves_per_loop[ ui_loop ] << " curves." << std::endl;
        for(ui_curve = 0; ui_curve < vui_curves_per_loop[ui_loop]; ++ui_curve)
        {
/*			Vec2dvector	vcl_cp = vcl_beziertrimmingcurves[ ui_curve ].getControlPointVector( );

            std::cerr << vcl_cp[ 0 ] << " -> " << vcl_cp[ vcl_cp.size( ) - 1 ] << std::endl;*/
            m_vtSurfaces[uiSurface].vvclBezierCurves[ui_loop].push_back(vcl_beziertrimmingcurves[ui_curve]);
        }
    }

    if(rcl_bspline_surface.makeBezier(m_vvvclBezierSurfaces[uiSurface],
                                      m_vvdUParams[uiSurface],
                                      m_vvdVParams[uiSurface]) )
    {
//		SWARNING << "Conversion of surface " << uiSurface + 1 << " to bezier form failed!" << endLog;
    }

#ifdef OSG_3D_LOOPS
    Gen3DLoops(uiSurface);
    m_vvvclBezierSurfaces[uiSurface].clear();
#endif

//	std::cerr <<"numofbeziers: " << m_vvvclBezierSurfaces[ uiSurface ].size() << " " <<
//                                   m_vvvclBezierSurfaces[ uiSurface ][0].size() << std::endl;
    m_vtSurfaces[uiSurface].ucStatus |= BEZIER_SURFACES_VALID;
}


//this is a new one, that has to be called twice because of the direct
//NURBS usage

// set up quad tree with saved error
void CNurbsPatchSurface::CalculateQuadTree(unsigned int uiSurface, bool bForEdges)
{
    if(!(m_vtSurfaces[uiSurface].ucStatus & BEZIER_SURFACES_VALID) )
    {
        std::cerr << "Bezier surfaces invalid for surface " << uiSurface + 1 << std::endl;
        return;
    }

//	std::cerr << "Building QuadTree for surface " << uiSurface + 1 << "." << std::endl;

//	m_vclSeperateMeshes[ uiSurface ].reinit( );
    if(bForEdges)
    {
        if(m_vtSurfaces[uiSurface].vvcl3DCurves.size() != 0)
        {
            // no quadtree required when 3d loops are present
            m_vtSurfaces[uiSurface].ucStatus |= QUAD_TREE_VALID;
            return;
        }
//		std::cerr << "q";
        m_clMesh.reinit();

        m_pclQuadTree = new QuadTreeCreator(&m_clMesh /*, bForEdges*/);
//		m_pclQuadTree = new QuadTreeCreator( &m_vclSeperateMeshes[ uiSurface ] );
        m_pclQuadTree->setErrorTolerance(m_vtSurfaces[uiSurface].dError / 3.0);
        if(m_pclQuadTree->setInitialLeaves(m_vvvclBezierSurfaces[uiSurface],
                                           m_vvdUParams[uiSurface],
                                           m_vvdVParams[uiSurface]) )
        {
            std::cerr << "QuadTree setup of surface " << uiSurface + 1 << " failed." << std::endl;
            m_vtSurfaces[uiSurface].ucStatus |= QUAD_TREE_ERROR;
            delete m_pclQuadTree;
            return;
        }
#ifndef OSG_ADAPTIVE_QUAD_TREE
        if(m_pclQuadTree->createQuadTree() )
        {
            std::cerr << "QuadTree creation of surface " << uiSurface + 1 << " failed." << std::endl;
            m_vtSurfaces[uiSurface].ucStatus |= QUAD_TREE_ERROR;
            delete m_pclQuadTree;
            return;
        }
        delete m_pclQuadTree;
#endif
    }
    else //2nd round...
    {
//		std::cerr << "b";
        m_clMesh.reinit();

#ifdef OSG_USE_NURBS_PATCH
        m_vtSurfaces[uiSurface].pclErrorTree->BuildMesh(&m_clMesh,
                                                        &(m_vclBSplineSurfaces[uiSurface].getSurface() ),
 #ifdef OSG_ARBITRARY_SPLIT
                                                        m_vtSurfaces[uiSurface].clMinParam,
                                                        m_vtSurfaces[uiSurface].clMaxParam,
 #endif
                                                        m_vtSurfaces[uiSurface].dError,
                                                        m_vtSurfaces[uiSurface].fMinError,
                                                        m_vtSurfaces[uiSurface].fMaxError);
#else
        m_vtSurfaces[uiSurface].pclErrorTree->BuildMesh(&m_clMesh,
                                                        &m_vvvclBezierSurfaces[uiSurface],
                                                        &m_vvdUParams[uiSurface],
                                                        &m_vvdVParams[uiSurface],
                                                        m_vtSurfaces[uiSurface].dError,
                                                        m_vtSurfaces[uiSurface].fMinError,
                                                        m_vtSurfaces[uiSurface].fMaxError);
#endif
//		std::cerr << "min error = " << m_vtSurfaces[ uiSurface ].fMinError << std::endl;
//		std::cerr << "max error = " << m_vtSurfaces[ uiSurface ].fMaxError << std::endl;
//#endif
    }
    m_vtSurfaces[uiSurface].ucStatus |= QUAD_TREE_VALID;
}






// calculate finest trimming curve
void CNurbsPatchSurface::CalculateTrimmingLoops(unsigned int uiSurface)
{
    bezier2ddequevector vvcl_curves = m_vtSurfaces[uiSurface].vvclBezierCurves;

    if(!(m_vtSurfaces[uiSurface].ucStatus & QUAD_TREE_VALID) )
    {
        std::cerr << "Quad tree invalid for surface " << uiSurface + 1 << std::endl;
        m_vtSurfaces[uiSurface].clMin = Vec3d(m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100);
        m_vtSurfaces[uiSurface].clMax = Vec3d(0, 0, 0);     // this is invalid and will always fail BB test
        return;
    }

//	std::cerr << "t";

    ParSpaceTrimmer cl_trimmer;

    if(m_vtSurfaces[uiSurface].vvcl3DCurves.size() != 0)
    {
 #ifdef OSG_USE_SIMPLIFIER
        cl_trimmer.Initialize(m_clMesh, vvcl_curves,
                              m_vtSurfaces[uiSurface].vvcl3DCurves,
                              m_vtSurfaces[uiSurface].vvclEdgeLoops,
                              m_vtSurfaces[uiSurface].dError,
                              &m_vclBSplineSurfaces[uiSurface].getSurface() );
 #else
        cl_trimmer.Initialize(m_clMesh, vvcl_curves,
                              m_vtSurfaces[uiSurface].vvcl3DCurves,
                              m_vtSurfaces[uiSurface].vvclEdgeLoops,
                              m_vtSurfaces[uiSurface].dError);
 #endif
    }
    else
    {
#ifdef OSG_ADAPTIVE_QUAD_TREE
 #ifdef OSG_USE_SIMPLIFIER
        cl_trimmer.Initialize(m_clMesh, vvcl_curves,
                              m_vtSurfaces[uiSurface].vvclEdgeLoops, m_pclQuadTree,
                              &m_vclBSplineSurfaces[uiSurface].getSurface() );
 #else
        cl_trimmer.Initialize(m_clMesh, vvcl_curves, m_vtSurfaces[uiSurface].vvclEdgeLoops, m_pclQuadTree);
 #endif
#else
        cl_trimmer.Initialize(m_clMesh, vvcl_curves, m_vtSurfaces[uiSurface].vvclEdgeLoops);
#endif
    }
    try
    {
        if(cl_trimmer.PerformTrimming() )
        {
            std::cerr << "Par space trimmer failed (surface " << uiSurface + 1 << ")." << std::endl;
            m_vtSurfaces[uiSurface].clMin = Vec3d(m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100);
            m_vtSurfaces[uiSurface].clMax = Vec3d(0, 0, 0);     // this is invalid and will always fail BB test
#ifndef OSG_ADAPTIVE_QUAD_TREE
            if(m_pclQuadTree != NULL)
            {
                delete m_pclQuadTree;
                m_pclQuadTree = NULL;
            }
#endif
            return;
        }
    }
    catch(ParSpaceTrimmerError cl_err)
    {
        std::cerr << "Par space trimmer exception caught: " << cl_err.errtype << " (surface " << uiSurface + 1 << ")" << std::endl;
        m_vtSurfaces[uiSurface].clMin = Vec3d(m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100, m_vtSurfaces[uiSurface].dError * 100);
        m_vtSurfaces[uiSurface].clMax = Vec3d(0, 0, 0);     // this is invalid and will always fail BB test
#ifndef OSG_ADAPTIVE_QUAD_TREE
        if(m_pclQuadTree != NULL)
        {
            delete m_pclQuadTree;
            m_pclQuadTree = NULL;
        }
#endif
        return;
    }


//    int                i_err;
    const unsigned int cui_size =
        UInt32(m_vtSurfaces[uiSurface].vvclEdgeLoops.size());

    m_vtSurfaces[uiSurface].vvclEdgeLoops3D.resize(cui_size);
    m_vtSurfaces[uiSurface].vbReversed.resize(cui_size);
    m_vtSurfaces[uiSurface].vbUsed.resize(cui_size);

//        std::cerr <<"edgeloops.size(): " << cui_size << std::endl;
    unsigned int ui_vertex;

    for(unsigned int ui_loop = 0; ui_loop < cui_size; ++ui_loop)
    {
//		std::cerr << "edge loop " << ui_loop + 1 << " of " << cui_size << std::endl;
        const unsigned int cui_size2 = UInt32(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop].size());
        std::vector<Pnt3f> vcl_temp3d;

        m_vtSurfaces[uiSurface].vvclEdgeLoops3D[ui_loop].resize(cui_size2);
        vcl_temp3d.resize(cui_size2);
        m_vclBSplineSurfaces[uiSurface].getSurface().compute(
            m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop],
            vcl_temp3d);

        for(ui_vertex = 0; ui_vertex < cui_size2; ++ui_vertex)
        {
//			std::cerr << "vertex " << ui_vertex + 1 << " of " << cui_size2 << std::endl;
/*			const Vec3d	ccl_vec = m_vclBSplineSurfaces[ uiSurface ].getSurface( ).compute(
                m_vtSurfaces[ uiSurface ].vvclEdgeLoops[ ui_loop ][ ui_vertex ],
                i_err );*/
            Vec3d ccl_vec;
            ccl_vec[0] = vcl_temp3d[ui_vertex][0];
            ccl_vec[1] = vcl_temp3d[ui_vertex][1];
            ccl_vec[2] = vcl_temp3d[ui_vertex][2];
//			std::cerr << "pos: " << ccl_vec << std::endl;

            m_vtSurfaces[uiSurface].vvclEdgeLoops3D[ui_loop][ui_vertex] = ccl_vec;

            if( (ui_loop == 0) && (ui_vertex == 0) )
            {
                m_vtSurfaces[uiSurface].clMin     =
                    m_vtSurfaces[uiSurface].clMax = ccl_vec;
#ifdef OSG_ARBITRARY_SPLIT
                m_vtSurfaces[uiSurface].clMinParam = m_vtSurfaces[uiSurface].clMaxParam =
                                                         m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex];
#endif
            }
            else
            {
                if(ccl_vec[0] < m_vtSurfaces[uiSurface].clMin[0])
                    m_vtSurfaces[uiSurface].clMin[0] = ccl_vec[0];
                else if(ccl_vec[0] > m_vtSurfaces[uiSurface].clMax[0])
                    m_vtSurfaces[uiSurface].clMax[0] = ccl_vec[0];
                if(ccl_vec[1] < m_vtSurfaces[uiSurface].clMin[1])
                    m_vtSurfaces[uiSurface].clMin[1] = ccl_vec[1];
                else if(ccl_vec[1] > m_vtSurfaces[uiSurface].clMax[1])
                    m_vtSurfaces[uiSurface].clMax[1] = ccl_vec[1];
                if(ccl_vec[2] < m_vtSurfaces[uiSurface].clMin[2])
                    m_vtSurfaces[uiSurface].clMin[2] = ccl_vec[2];
                else if(ccl_vec[2] > m_vtSurfaces[uiSurface].clMax[2])
                    m_vtSurfaces[uiSurface].clMax[2] = ccl_vec[2];
#ifdef OSG_ARBITRARY_SPLIT
                if(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][0] < m_vtSurfaces[uiSurface].clMinParam[0])
                    m_vtSurfaces[uiSurface].clMinParam[0] = m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][0];
                else if(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][0] > m_vtSurfaces[uiSurface].clMaxParam[0])
                    m_vtSurfaces[uiSurface].clMaxParam[0] = m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][0];
                if(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][1] < m_vtSurfaces[uiSurface].clMinParam[1])
                    m_vtSurfaces[uiSurface].clMinParam[1] = m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][1];
                else if(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][1] > m_vtSurfaces[uiSurface].clMaxParam[1])
                    m_vtSurfaces[uiSurface].clMaxParam[1] = m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop][ui_vertex][1];
#endif
            }
        }

        //check direction
        SimplePolygon cl_check;
//                std::cerr <<"baszom1: " << cui_size2 << std::endl;
        cl_check.vertices.resize(cui_size2 - 1);

        for(ui_vertex = 0; ui_vertex < cui_size2 - 1; ++ui_vertex)
        {
            cl_check.vertices[ui_vertex] = ui_vertex;
        }

//                std::cerr <<"baszom2" << std::endl;
//                std::cerr <<"checked vector: " << std::endl;
//                unsigned int kk = m_vtSurfaces[ uiSurface ].vvclEdgeLoops[ ui_loop ].size();
//                for (unsigned int iii = 0; iii < kk; ++iii)
//                    std::cerr << m_vtSurfaces[ uiSurface ].vvclEdgeLoops[ ui_loop
//                            ][iii] << std::endl;



        if(cl_check.isReversed(m_vtSurfaces[uiSurface].vvclEdgeLoops[ui_loop]) )
        {
//			std::cerr << "loop is reversed" << std::endl;
            m_vtSurfaces[uiSurface].vbReversed[ui_loop] = true;
//                        std::cerr <<"baszom2.5" << std::endl;

        }
        else
        {
//			std::cerr << "loop is normal" << std::endl;
            m_vtSurfaces[uiSurface].vbReversed[ui_loop] = false;
//                        std::cerr <<"baszom2.6"<<std::endl;
        }
//                std::cerr <<"baszom3"<<std::endl;
        m_vtSurfaces[uiSurface].vbUsed[ui_loop] = true;

    }

    m_vtSurfaces[uiSurface].clMin -= Vec3d(m_vtSurfaces[uiSurface].dError, m_vtSurfaces[uiSurface].dError, m_vtSurfaces[uiSurface].dError);
    m_vtSurfaces[uiSurface].clMax += Vec3d(m_vtSurfaces[uiSurface].dError, m_vtSurfaces[uiSurface].dError, m_vtSurfaces[uiSurface].dError);
#ifdef OSG_ADAPTIVE_QUAD_TREE
    if(m_pclQuadTree != NULL)
    {
        delete m_pclQuadTree;
        m_pclQuadTree = NULL;
    }
#endif
    m_vtSurfaces[uiSurface].ucStatus |= TRIMMING_VALID;
}





// calculate actual trimming curve
void CNurbsPatchSurface::CalculateActualTrimming(unsigned int uiSurface)
{
    ParSpaceTrimmer cl_trimmer;

//	std::cerr << "g";

////	cl_trimmer.Initialize2( m_clMesh, m_vtSurfaces[ uiSurface ].vvclEdgeLoops, m_vtSurfaces[ uiSurface ].vvclEdgeLoops3D );

#ifdef OSG_FORCE_NO_T_VERTICES
    cl_trimmer.Initialize2(m_clMesh,
                           m_vtSurfaces[uiSurface].vvclEdgeLoops,
                           m_vtSurfaces[uiSurface].vvclEdgeLoops3D,
//                m_vtSurfaces[ uiSurface ].vvclEdgeLoopsNorm,
                           m_vtSurfaces[uiSurface].vbReversed,
                           m_vtSurfaces[uiSurface].vbUsed);

#else
    cl_trimmer.Initialize2(m_clMesh, m_vtSurfaces[uiSurface].vvclEdgeLoops, m_vtSurfaces[uiSurface].vvclEdgeLoops3D, m_vtSurfaces[uiSurface].vbReversed, m_vtSurfaces[uiSurface].vbUsed);
#endif /* OSG_FORCE_NO_T_VERTICES */
//	cl_trimmer.Initialize2( m_vclSeperateMeshes[ uiSurface ], m_vtSurfaces[ uiSurface ].vvclEdgeLoops );
    try
    {
        if(cl_trimmer.PerformTrimming2() )
        {
            std::cerr << "Par space trimmer2 failed (surface " << uiSurface + 1 << ")." << std::endl;
            return;
        }
    }
    catch(ParSpaceTrimmerError cl_err)
    {
        std::cerr << "Par space trimmer2 exception caught: " << cl_err.errtype << " (surface " << uiSurface + 1 << ")" << std::endl;
        return;
    }

#ifndef OSG_FORCE_NO_T_VERTICES
    // get new trimming loops
    cl_trimmer.getTrimmingLoops(m_vtSurfaces[uiSurface].vvclEdgeLoops);
#endif

    try
    {
        if(m_pclGraph)
        {
            delete m_pclGraph;
        }
        m_pclGraph = new DirectedGraph<Vec2d, unsigned char>;
#ifdef OSG_KEEP_2D_POINTS
        if(cl_trimmer.buildSurfaceGraph(m_pclGraph, &m_vclGlobalVertices, NULL, &m_vuiIndex) )
#else
        if(cl_trimmer.buildSurfaceGraph(m_pclGraph, &m_vclGlobalVertices) )
#endif
        {
            std::cerr << "Build surface graph failed (surface " << uiSurface + 1 << ")." << std::endl;
            return;
        }
    }
    catch(ParSpaceTrimmerError cl_err)
    {
        std::cerr << "Par space trimmer exception caught: " << cl_err.errtype << " (surface " << uiSurface + 1 << ")" << std::endl;
//		m_vtSurfaces[ uiSurface ].ucStatus |= TRIMMING_ERROR;
        return;
    }

    m_vtSurfaces[uiSurface].ucStatus |= TRIMMING_VALID;
}


// perform graph traversal
void CNurbsPatchSurface::CalculateGraph(unsigned int uiSurface, bool usedelaunay)
{
    GraphTraverser cl_traverser;

    if(!(m_vtSurfaces[uiSurface].ucStatus & TRIMMING_VALID) )
    {
        std::cerr << "Trimming invalid for surface " << uiSurface + 1 << std::endl;
        return;
    }

//	std::cerr << "t";
//	std::cerr << "Traversing graph of surface " << uiSurface + 1 << "." << std::endl;

    cl_traverser.Initialize(*m_pclGraph, usedelaunay);
    try
    {
        if(cl_traverser.Traverse() )
        {
            std::cerr << "Graph traverser failed (surface " << uiSurface + 1 << ")." << std::endl;
//			m_vtSurfaces[ uiSurface ].ucStatus |= TRIANGULATION_ERROR;
//			return;
        }
    }
    catch(GraphTraverserError cl_err)
    {
        std::cerr << "Graph traverser exception caught: " << cl_err.errtype << " (surface " << uiSurface + 1 << ")" << std::endl;
//		m_vtSurfaces[ uiSurface ].ucStatus |= TRIANGULATION_ERROR;
//		return;
    }

    m_vclTriangles                    = *(cl_traverser.getPolys() );
    m_vclParameterVertices            = *(cl_traverser.getVertices() );
    m_vtSurfaces[uiSurface].ucStatus |= TRIANGULATION_VALID;

#ifdef OSG_KEEP_2D_POINTS
    // change triangle vertices to indices of trimming loop vertex
    const unsigned int cui_size = m_vclTriangles.size();
    unsigned int       ui_idx;

    for(ui_idx = 0; ui_idx < cui_size; ++ui_idx)
    {
        std::vector<int> & rvi_verts    = m_vclTriangles[ui_idx].vertices;
        const unsigned int cui_vert_cnt = rvi_verts.size();
        unsigned int       ui_vert;

        for(ui_vert = 0; ui_vert < cui_vert_cnt; ++ui_vert)
        {
            // change triangle indices
            if(rvi_verts[ui_vert] < ( int ) m_vuiIndex.size() )
                rvi_verts[ui_vert] = ( int ) m_vuiIndex[rvi_verts[ui_vert]];
        }
    }

    // copy trimming loops to global vertices
    const unsigned int cui_loop_cnt = m_vtSurfaces[0].vvclEdgeLoops3D.size();
    unsigned int       ui_loop;

    ui_idx = 0;

    for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
    {
        if(m_vtSurfaces[0].vbUsed[ui_loop])
        {
            const unsigned int cui_vert_cnt = m_vtSurfaces[0].vvclEdgeLoops[ui_loop].size();
            unsigned int       ui_vert;

            for(ui_vert = 0; ui_vert < cui_vert_cnt; ++ui_vert)
            {
                m_vclParameterVertices[ui_idx] = m_vtSurfaces[0].vvclEdgeLoops[ui_loop][ui_vert];
                ++ui_idx;
            }
        }
    }

/*	if( m_vclGlobalVertices.size( ) > ui_idx )
    {
        m_vclGlobalVertices.resize( ui_idx );
    }*/
#endif
}




void CNurbsPatchSurface::ComputeNormalCone(const unsigned int  cuiSurface,
                                           std::vector<Vec3f>& normals)
{
/*	unsigned int	ui_cnt = 0;

    Miniball<3> cl_miniball;
    for ( unsigned int ui_normal= 0; ui_normal < normals.size(); ++ui_normal )
    {
        double	d_len = normals[ ui_normal ].length( );
        if( d_len > DCTP_EPS )
        {
            normals[ ui_normal ] *= 1.0 / d_len;
//			std::cerr << normals[ ui_normal ] << std::endl;
            Miniball<3>::Point cl_point;
            cl_point[ 0 ]=  normals[ ui_normal ].x();
            cl_point[ 1 ]=  normals[ ui_normal ].y();
            cl_point[ 2 ]=  normals[ ui_normal ].z();
            cl_miniball.check_in( cl_point );
            ++ui_cnt;
        }
    }
//	std::cerr << "-----" << std::endl;

    cl_miniball.build();

    Vec3d cl_center;
    cl_center[0]= cl_miniball.center()[0];
    cl_center[1]= cl_miniball.center()[1];
    cl_center[2]= cl_miniball.center()[2];

    // compute intersection of sphere bounding the normals with unit sphere
    // => formula from http://astronomy.swin.edu.au/~pbourke/geometry/spheresphere/
double d_distance_squared= cl_center.squareLength();

    if ( (d_distance_squared < 0.001) || ( ui_cnt < 3 ) )
    {
        // arbitrary direction
        m_vtSurfaces[ cuiSurface ].tNormalCone.clDirection= Vec3d(1.0, 0.0, 0.0);

        // angle > 180 degrees
        m_vtSurfaces[ cuiSurface ].tNormalCone.dThreshold = 1.0;
        return;
    }

    double d_nominator_root= ( d_distance_squared - cl_miniball.squared_radius( ) + 1.0 ) * 0.5;
    double d_height= sqrt( 1.0 - ( d_nominator_root * d_nominator_root ) / d_distance_squared );
    cl_center *= 1.0 / sqrt( d_distance_squared );//.normalize();

    m_vtSurfaces[ cuiSurface ].tNormalCone.clDirection= cl_center;
    m_vtSurfaces[ cuiSurface ].tNormalCone.dThreshold = d_height;

//	std::cerr << cl_center << std::endl;
//	std::cerr << d_height << std::endl;*/
}

void CNurbsPatchSurface::Gen3DLoops(const unsigned int cuiSurface)
{
    const unsigned int        cui_loop_cnt = UInt32(m_vtSurfaces[cuiSurface].vvclBezierCurves.size());
    unsigned int              ui_loop;
    unsigned int              ui_curve_cnt;
    unsigned int              ui_curve;
    bezier2ddeque             vcl_new_curves;
    std::vector<unsigned int> vui_u_seg;
    std::vector<unsigned int> vui_v_seg;
    unsigned int              ui_dim;
    unsigned int              ui_pos;
    Vec2d                     cl_param;
    std::vector<Vec4d>        vcl_points;
    int                       i_err;

    m_vtSurfaces[cuiSurface].vvcl3DCurves.resize(cui_loop_cnt);

    for(ui_loop = 0; ui_loop < cui_loop_cnt; ++ui_loop)
    {
        // first cut the curves with the bezier patches
        vcl_new_curves.clear();
        vui_u_seg.clear();
        vui_v_seg.clear();
        ui_curve_cnt = UInt32(m_vtSurfaces[cuiSurface].vvclBezierCurves[ui_loop].size());

        for(ui_curve = 0; ui_curve < ui_curve_cnt; ++ui_curve)
        {
            CutCurve(cuiSurface, m_vtSurfaces[cuiSurface].vvclBezierCurves[ui_loop][ui_curve],
                     vcl_new_curves, vui_u_seg, vui_v_seg);
        }

        m_vtSurfaces[cuiSurface].vvclBezierCurves[ui_loop] = vcl_new_curves;

        // then elevate the trimming curves into 3d space
        ui_curve_cnt = UInt32(m_vtSurfaces[cuiSurface].vvclBezierCurves[ui_loop].size());
        m_vtSurfaces[cuiSurface].vvcl3DCurves[ui_loop].resize(ui_curve_cnt);

        for(ui_curve = 0; ui_curve < ui_curve_cnt; ++ui_curve)
        {
            const unsigned int   cui_u_seg   = vui_u_seg[ui_curve];
            const unsigned int   cui_v_seg   = vui_v_seg[ui_curve];
            BezierTensorSurface &rcl_surf    = m_vvvclBezierSurfaces[cuiSurface][cui_u_seg][cui_v_seg];
            BezierCurve2D &      rcl_curve2d = m_vtSurfaces[cuiSurface].vvclBezierCurves[ui_loop][ui_curve];

            rcl_curve2d.optimizeDegree();

            // REMARK:
            // Even though there exists a closed formula which
            // gives the degree of a rational Bezier curve elevated by
            // a rational Bezier patch, here we don't take into account
            // the weights of the elevating Bezier patch and therefore
            // this degree approximation is necessary for rational
            // trimming curves. The closed formula is also quite
            // expensive to calculate, our method is a bit cheaper.
            // Although it usually overestimates the degree, it doesn't
            // really matter in practice since the approximated 3D
            // Bezier curve will be degree reduced as much as possible.
            // And this method was easier to implement anyway. :-)
            unsigned int approxdegree = rcl_curve2d.computeNonratApproximationDegree(1e-4);
            ui_dim = ( (UInt32(rcl_surf.getControlPointMatrix().size()) - 1)
                       + (UInt32(rcl_surf.getControlPointMatrix()[0].size()) - 1) )
                     * approxdegree;
#ifdef OSG_NURBS_DEBUG
            if(approxdegree != rcl_curve2d.getControlPointVector().size() - 1)
            {
                std::cerr << "approxdegree: " << approxdegree << " dim: " << ui_dim << std::endl;
            }
#endif /* OSG_NURBS_DEBUG */

            if(ui_dim > 40)
                ui_dim = 40;

            vcl_points.clear();

            for(ui_pos = 0; ui_pos <= ui_dim; ++ui_pos)
            {
                i_err    = 0;
                cl_param = rcl_curve2d.computewdeCasteljau( (double(ui_pos) ) / ui_dim, i_err);
//				vcl_points.push_back( rcl_surf.computewdeCasteljau( cl_param, i_err ) );
                vcl_points.push_back(m_vclBSplineSurfaces[cuiSurface].getSurface().compute4D(cl_param, i_err) );
            }

            if(m_vtSurfaces[cuiSurface].vvcl3DCurves[ui_loop][ui_curve].createCurve(vcl_points) == 0)
            {
                m_vtSurfaces[cuiSurface].vvcl3DCurves[ui_loop][ui_curve].optimizeDegree();
            }
#ifdef OSG_NURBS_DEBUG
            if(approxdegree != rcl_curve2d.getControlPointVector().size() - 1)
            {
                std::cerr << "optimdegree: " << m_vtSurfaces[cuiSurface].vvcl3DCurves[ui_loop][ui_curve].getControlPointVector().size() - 1 << std::endl;
            }
#endif /* OSG_NURBS_DEBUG */
//			rcl_curve2d.write( );
//			m_vtSurfaces[ cuiSurface ].vvcl3DCurves[ ui_loop ][ ui_curve ].write( );
        }
    }
}

void CNurbsPatchSurface::CutCurve(const unsigned int         cuiSurface,
                                  BezierCurve2D&             rclCurve,
                                  bezier2ddeque&             rclCut,
                                  std::vector<unsigned int>& rvuiUSeg,
                                  std::vector<unsigned int>& rvuiVSeg)
{
    typedef std::multimap<double, unsigned int> CurveMap;
    typedef CurveMap::iterator                  CurveMapIt;

    const int                  ci_u_seg_cnt = UInt32(m_vvdUParams[cuiSurface].size());
    const int                  ci_v_seg_cnt = UInt32(m_vvdVParams[cuiSurface].size());
    int                        i_u_seg;
    int                        i_v_seg;
    unsigned int               ui_curve;
    unsigned int               ui_curve_cnt = 1;
    std::vector<BezierCurve2D> vcl_curves;
    std::vector<double>        vd_curvestart;
    std::vector<double>        vd_curveend;
    std::vector<double>        vd_int;
    unsigned int               ui_int;
    BezierCurve2D              cl_new_curve;
    CurveMap                   mm_curve_sort;
    CurveMapIt                 itmm_curve_it;
    int                        i_err;
    bool                       b_cut;

    vcl_curves.push_back(rclCurve);
    vd_curvestart.push_back(0.0);
    vd_curveend.push_back(1.0);
    mm_curve_sort.insert(CurveMap::value_type(0.0, 0u));

    for(ui_curve = 0; ui_curve < ui_curve_cnt; ++ui_curve)
    {
        b_cut = false;

        // cut in u-direction
        for(i_u_seg = 0; i_u_seg < ci_u_seg_cnt; ++i_u_seg)
        {
            vd_int.clear();
            vcl_curves[ui_curve].intersection(vd_int, m_vvdUParams[cuiSurface][i_u_seg], false);

            for(ui_int = 0; ui_int < vd_int.size(); ++ui_int)
            {
                if( (vd_int[ui_int] > 1e-7) &&
                    (1.0 - vd_int[ui_int] > 1e-7) )
                {
                    vcl_curves[ui_curve].subDivision(vd_int[ui_int], cl_new_curve);
                    vcl_curves.push_back(cl_new_curve);
                    vd_curvestart.push_back( (vd_curvestart[ui_curve] + vd_curveend[ui_curve]) * 0.5);
                    vd_curveend.push_back(vd_curveend[ui_curve]);
                    vd_curveend[ui_curve] = vd_curvestart[ui_curve_cnt];
                    mm_curve_sort.insert(CurveMap::value_type(vd_curvestart[ui_curve_cnt], ui_curve_cnt));
                    ++ui_curve_cnt;
                    b_cut = true;
                    break;
                }
            }
        }

        if(!b_cut)
        {
            // cut in v-direction
            for(i_v_seg = 0; i_v_seg < ci_v_seg_cnt; ++i_v_seg)
            {
                vd_int.clear();
                vcl_curves[ui_curve].intersection(vd_int, m_vvdVParams[cuiSurface][i_v_seg], true);

                for(ui_int = 0; ui_int < vd_int.size(); ++ui_int)
                {
                    if( (vd_int[ui_int] > 1e-7) &&
                        (1.0 - vd_int[ui_int] > 1e-7) )
                    {
                        vcl_curves[ui_curve].subDivision(vd_int[ui_int], cl_new_curve);
                        vcl_curves.push_back(cl_new_curve);
                        vd_curvestart.push_back( (vd_curvestart[ui_curve] + vd_curveend[ui_curve]) * 0.5);
                        vd_curveend.push_back(vd_curveend[ui_curve]);
                        vd_curveend[ui_curve] = vd_curvestart[ui_curve_cnt];
                        mm_curve_sort.insert(CurveMap::value_type(vd_curvestart[ui_curve_cnt], ui_curve_cnt) );
                        ++ui_curve_cnt;
                        b_cut = true;
                        break;
                    }
                }
            }
        }
        if(b_cut)
        {
            --ui_curve;
        }
    }

    // sort and append new curves
    const unsigned int cui_offset = UInt32(rclCut.size());

    rclCut.resize(ui_curve_cnt + cui_offset);
    ui_curve = 0;

    for(itmm_curve_it = mm_curve_sort.begin(); itmm_curve_it != mm_curve_sort.end(); ++itmm_curve_it)
    {
//		std::cerr << itmm_curve_it->second << " ";
        rclCut[ui_curve + cui_offset] = vcl_curves[itmm_curve_it->second];
        ++ui_curve;
    }

//	std::cerr << std::endl;

    // ok, now we know that all curve midpoints are INSIDE a cell (or the whole curve is on the edge)
    for(ui_curve = 0; ui_curve < ui_curve_cnt; ++ui_curve)
    {
        const Vec2d ccl_mid = rclCut[ui_curve + cui_offset].computewdeCasteljau(0.5, i_err);

        // check if curve lies outside the surface
        if(ccl_mid[0] <= m_vvdUParams[cuiSurface][0])
        {
            std::vector<Vec3d> &rcl_cp = rclCut[ui_curve + cui_offset].getControlPointVector();

            rcl_cp[1]    = rcl_cp[rcl_cp.size() - 1];
            rcl_cp[0][0] = m_vvdUParams[cuiSurface][0] * rcl_cp[0][2];
            rcl_cp[1][0] = m_vvdUParams[cuiSurface][0] * rcl_cp[1][2];
            rcl_cp.resize(2);
            rvuiUSeg.push_back(0);
        }
        else if(ccl_mid[0] >= m_vvdUParams[cuiSurface][ci_u_seg_cnt - 1])
        {
            std::vector<Vec3d> &rcl_cp = rclCut[ui_curve + cui_offset].getControlPointVector();

            rcl_cp[1]    = rcl_cp[rcl_cp.size() - 1];
            rcl_cp[0][0] = m_vvdUParams[cuiSurface][ci_u_seg_cnt - 1] * rcl_cp[0][2];
            rcl_cp[1][0] = m_vvdUParams[cuiSurface][ci_u_seg_cnt - 1] * rcl_cp[1][2];
            rcl_cp.resize(2);
            rvuiUSeg.push_back(ci_u_seg_cnt - 2);
        }
        else
        {
            for(i_u_seg = 1; i_u_seg < ci_u_seg_cnt; ++i_u_seg)
            {
                if(ccl_mid[0] <= m_vvdUParams[cuiSurface][i_u_seg])
                {
                    rvuiUSeg.push_back(i_u_seg - 1);
                    break;
                }
            }
        }

        // check if curve lies outside the surface
        if(ccl_mid[1] <= m_vvdVParams[cuiSurface][0])
        {
            std::vector<Vec3d> &rcl_cp = rclCut[ui_curve + cui_offset].getControlPointVector();

            rcl_cp[1]    = rcl_cp[rcl_cp.size() - 1];
            rcl_cp[0][1] = m_vvdVParams[cuiSurface][0] * rcl_cp[0][2];
            rcl_cp[1][1] = m_vvdVParams[cuiSurface][0] * rcl_cp[1][2];
            rcl_cp.resize(2);
            rvuiVSeg.push_back(0);
        }
        else if(ccl_mid[1] >= m_vvdVParams[cuiSurface][ci_v_seg_cnt - 1])
        {
            std::vector<Vec3d> &rcl_cp = rclCut[ui_curve + cui_offset].getControlPointVector();

            rcl_cp[1]    = rcl_cp[rcl_cp.size() - 1];
            rcl_cp[0][1] = m_vvdVParams[cuiSurface][ci_v_seg_cnt - 1] * rcl_cp[0][2];
            rcl_cp[1][1] = m_vvdVParams[cuiSurface][ci_v_seg_cnt - 1] * rcl_cp[1][2];
            rcl_cp.resize(2);
            rvuiVSeg.push_back(ci_v_seg_cnt - 2);
        }
        else
        {
            for(i_v_seg = 1; i_v_seg < ci_v_seg_cnt; ++i_v_seg)
            {
                if(ccl_mid[1] <= m_vvdVParams[cuiSurface][i_v_seg])
                {
                    rvuiVSeg.push_back(i_v_seg - 1);
                    break;
                }
            }
        }
    }
}
