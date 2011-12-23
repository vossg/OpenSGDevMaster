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
#include "OSGErrorQuadTree.h"

#include "OSGDCTPMesh.h"
#include "OSGBezierTensorSurface.h"
#include "OSGBSplineTensorSurface.h"



#include <stdlib.h>
#include <float.h>

OSG_USING_NAMESPACE


//#define min( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
//#define max( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )

//#define OSG_EUCLID_ERRORS

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

bool CErrorQuadTree::m_sbNormalApproximation = false;

CErrorQuadTree::CErrorQuadTree()
{
    m_fMaxError = -1.0;
#ifdef OSG_USE_NURBS_PATCH
    m_ptRoot = NULL;
#else
    m_vvptRoot.clear();
    m_ptBPRoot = NULL;
#endif
    m_fErrorCutoff = DCTP_EPS;
}


CErrorQuadTree::~CErrorQuadTree()
{
#ifdef OSG_USE_NURBS_PATCH
    if(m_ptRoot)
    {
        DeleteNode(m_ptRoot);
 #ifdef OSG_ONE_CHILD_PTR
        delete m_ptRoot;
        m_ptRoot = NULL;
 #endif
    }
#else
    const unsigned int cui_size_u = m_vvptRoot.size();

    if(cui_size_u)
    {
        const unsigned int cui_size_v = m_vvptRoot[0].size();
        unsigned int       ui_u;
        unsigned int       ui_v;

        for(ui_u = 0; ui_u < cui_size_u; ++ui_u)
        {
            for(ui_v = 0; ui_v < cui_size_v; ++ui_v)
            {
                DeleteNode(m_vvptRoot[ui_u][ui_v]);
 #ifdef OSG_ONE_CHILD_PTR
                delete m_vvptRoot[ui_u][ui_v];
                m_vvptRoot[ui_u][ui_v] = NULL;
 #endif
            }
        }

        m_vvptRoot.clear();
    }

    if(m_ptBPRoot)
    {
        DeleteBPNode(m_ptBPRoot);
    }
#endif
}


//#ifndef OSG_ARBITRARY_SPLIT
void CErrorQuadTree::BuildMesh(DCTPMesh *pclMesh,
#ifdef OSG_USE_NURBS_PATCH
                               BSplineTensorSurface *pclPatch,
 #ifdef OSG_ARBITRARY_SPLIT
                               const Vec2d cclMinParam, const Vec2d cclMaxParam,
 #endif
#else
                               std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                               const std::vector<double> *cpvdIntervalsU,
                               const std::vector<double> *cpvdIntervalsV,
#endif
                               float fError, float &rfMinError, float &rfMaxError)
{
    pclMesh->reinit();
#ifdef OSG_USE_NURBS_PATCH
 #ifdef OSG_ARBITRARY_SPLIT
    SetInitialCells(pclMesh, fError, pclPatch, cclMinParam, cclMaxParam);

    if( (cclMaxParam[0] - cclMinParam[0] < DCTP_EPS) ||
        (cclMaxParam[1] - cclMinParam[1] < DCTP_EPS) )
    {
        return;
    }
 #else
    SetInitialCells(pclMesh, fError, pclPatch);
 #endif
#else
    SetInitialCells(pclMesh, fError, pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
#endif

    unsigned int   ui_face;
    unsigned int   ui_face_cnt = UInt32(pclMesh->faces.size());
    DCTPFace      *pcl_face;
    SFaceTreeCell *pt_finfo;
    float          f_act_error;
    float          f_prev_error;

    rfMinError = -1.0;
    rfMaxError = FLT_MAX;

    if(fError < m_fErrorCutoff)
    {
        fError = m_fErrorCutoff;
    }

    if( (fError >= m_fMaxError) && (m_fMaxError >= 0.0) )
    {
        // ok, we already have a subdivision for that error...
        for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
        {
            pcl_face = pclMesh->faces[ui_face];
            if(pcl_face->faceinfo)
            {
                f_prev_error = FLT_MAX;
#ifdef OSG_USE_NURBS_PATCH
                f_act_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                while(f_act_error > fError)
                {
//					std::cerr << ",";
 #ifdef OSG_USE_KD_TREE
  #ifdef OSG_ARBITRARY_SPLIT
                    if( (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fSplitValue < 0.0)
  #else
                    if( (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->bSplitHoriz)
  #endif
                    {
  #ifdef OSG_ARBITRARY_SPLIT
                        pclMesh->SubdivideQuadEW(pcl_face, -(static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fSplitValue);
  #else
                        pclMesh->SubdivideQuadEW(pcl_face);
  #endif
                    }
                    else
                    {
  #ifdef OSG_ARBITRARY_SPLIT
                        pclMesh->SubdivideQuadNS(pcl_face, (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fSplitValue);
  #else
                        pclMesh->SubdivideQuadNS(pcl_face);
  #endif
                    }
                    SubdivideNode(pclMesh, pcl_face);
                    ++ui_face_cnt;      // one new face
 #else
                    pclMesh->SubdivideQuad(pcl_face);
                    SubdivideNode(pclMesh, pcl_face);
                    ui_face_cnt += 3;   // three new faces
 #endif
                    f_prev_error = f_act_error;
                    f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                }
#else
                if( (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell)
                {
                    f_act_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                    while(f_act_error > fError)
                    {
                        pclMesh->SubdivideQuad(pcl_face);
                        SubdivideNode(pclMesh, pcl_face);
                        ui_face_cnt += 3;   // three new faces
                        f_prev_error = f_act_error;
                        f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                    }
                }
                else
                {
                    f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptBPCell->fError;
                    f_prev_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptBPCell->fPrevError;
//					std::cerr << pcl_face->orig_quad[ 3 ]->coords << pcl_face->orig_quad[ 1 ]->coords << std::endl;
//					std::cerr << f_act_error << ", " << f_prev_error << std::endl;
                }
#endif
                if(f_act_error > rfMinError)
                {
                    rfMinError = f_act_error;
                }
                if(f_prev_error < rfMaxError)
                {
                    rfMaxError = f_prev_error;
                }
            }
        }

        // delete faceinfo
        for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
        {
            pcl_face = pclMesh->faces[ui_face];
            pt_finfo = static_cast<SFaceTreeCell*>(pcl_face->faceinfo);
            if(pt_finfo)
            {
                delete pt_finfo;
                pcl_face->faceinfo = NULL;
            }
/*			else
            {
                pclMesh->removeFace( ui_face );
                --ui_face;
                --ui_face_cnt;
            }*/
        }

//		std::cerr << "reconstructed " << ui_face_cnt << " faces" << std::endl;
/*		if( pclMesh->faces.size( ) >= 1000 )
        {
            if( fError > m_fErrorCutoff )
            {
                std::cerr << "reduce error cutoff: " << m_fErrorCutoff << " -> " << fError << std::endl;
                m_fErrorCutoff = fError;
            }
        }
        if( fError <= m_fErrorCutoff )
        {
            rfMinError = 0.0;
        }*/
        return;
    }

#ifdef OSG_ARBITRARY_SPLIT
 #ifndef OSG_USE_NURBS_PATCH
  #error
 #endif
    // create first surface
    std::vector<BSplineTensorSurface> vcl_surf;
    double                            d_split;
    Vec2d                             cl_min;
    Vec2d                             cl_add;

    pt_finfo                       = (static_cast<SFaceTreeCell*>(pclMesh->faces[0]->faceinfo) );
    pt_finfo->bOwnSurface          = true;
    pt_finfo->pclBSplineSurface    = new BSplineTensorSurface;
    *(pt_finfo->pclBSplineSurface) = *pclPatch;
    pclPatch->getParameterInterval_U(cl_min[0], cl_add[0]);
    pclPatch->getParameterInterval_V(cl_min[1], cl_add[1]);
    cl_add -= cl_min;

    d_split = (cclMinParam[0] - cl_min[0]) / cl_add[0];
    if(d_split > 0.999)
        d_split = 0.999;
    if(d_split > DCTP_EPS)
    {
        pt_finfo->pclBSplineSurface->subDivisionU(vcl_surf, d_split);
        *(pt_finfo->pclBSplineSurface) = vcl_surf[1];
    }

    d_split = (cclMaxParam[0] - cclMinParam[0]) / (cl_add[0] - cclMinParam[0]);
    if(d_split < 0.001)
        d_split = 0.001;
    if(1.0 - d_split > DCTP_EPS)
    {
        pt_finfo->pclBSplineSurface->subDivisionU(vcl_surf, d_split);
        *(pt_finfo->pclBSplineSurface) = vcl_surf[0];
    }

    d_split = (cclMinParam[1] - cl_min[1]) / cl_add[1];
    if(d_split > 0.999)
        d_split = 0.999;
    if(d_split > DCTP_EPS)
    {
        pt_finfo->pclBSplineSurface->subDivisionV(vcl_surf, d_split);
        *(pt_finfo->pclBSplineSurface) = vcl_surf[1];
    }

    d_split = (cclMaxParam[1] - cclMinParam[1]) / (cl_add[1] - cclMinParam[1]);
    if(d_split < 0.001)
        d_split = 0.001;
    if(1.0 - d_split > DCTP_EPS)
    {
        pt_finfo->pclBSplineSurface->subDivisionV(vcl_surf, d_split);
        *(pt_finfo->pclBSplineSurface) = vcl_surf[0];
    }

    vcl_surf.clear();
#endif

    // we need to build a new quadtree
/*	if( ( fError > m_fMaxError * 0.7071068115 ) && ( m_fMaxError >= 0.0 ) )
    {
        // new error must be 1 / sqrt( 2 ) or less than old...
        fError = m_fMaxError * 0.7071068115;
    }*/

    // init errors if computed for the first time
//	if( m_fMaxError < 0.0 )
    {
        for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
        {
            pcl_face = pclMesh->faces[ui_face];
            if(pcl_face->faceinfo)
            {
                if( (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell)
                {
                    ComputeError(pcl_face);
                }
            }
        }
    }

    // subdivide and get max error
    m_fMaxError = -1.0;

    for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
    {
        pcl_face = pclMesh->faces[ui_face];
        if(pcl_face->faceinfo)
        {
            f_prev_error = FLT_MAX;
#ifdef OSG_USE_NURBS_PATCH
            f_act_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
            while(f_act_error > fError)
            {
                const SErrorTreeCell* cpt_errcell = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell;
                bool                  b_split_ok  = true;

//				std::cerr << ".";
 #ifdef OSG_USE_KD_TREE
  #ifdef OSG_ARBITRARY_SPLIT
                if(cpt_errcell->fSplitValue < 0.0)
  #else
                if(cpt_errcell->bSplitHoriz)
  #endif
                {
  #ifdef OSG_ARBITRARY_SPLIT
                    const double cd_ratio = osgMin(-cpt_errcell->fSplitValue, 1.0f + cpt_errcell->fSplitValue);
   #ifdef OSG_UNION_TRI_QUAD
                    if( (pcl_face->orig_face[1]->coords[0] - pcl_face->orig_face[0]->coords[0]) * cd_ratio > DCTP_EPS * 100.0)
   #else
                    if( (pcl_face->orig_quad[1]->coords[0] - pcl_face->orig_quad[0]->coords[0]) * cd_ratio > DCTP_EPS * 100.0)
   #endif
  #else
   #ifdef OSG_UNION_TRI_QUAD
                    if( (pcl_face->orig_face[1]->coords[0] - pcl_face->orig_face[0]->coords[0]) * 0.5 > DCTP_EPS * 100.0)
   #else
                    if( (pcl_face->orig_quad[1]->coords[0] - pcl_face->orig_quad[0]->coords[0]) * 0.5 > DCTP_EPS * 100.0)
   #endif
  #endif
                    {
  #ifdef OSG_ARBITRARY_SPLIT
                        pclMesh->SubdivideQuadEW(pcl_face, -cpt_errcell->fSplitValue);
  #else
                        pclMesh->SubdivideQuadEW(pcl_face);
  #endif
                    }
                    else
                    {
                        b_split_ok = false;
                    }
                }
                else
                {
  #ifdef OSG_ARBITRARY_SPLIT
                    const double cd_ratio = osgMin(cpt_errcell->fSplitValue, 1.0f - cpt_errcell->fSplitValue);
   #ifdef OSG_UNION_TRI_QUAD
                    if( (pcl_face->orig_face[0]->coords[1] - pcl_face->orig_face[3]->coords[1]) * cd_ratio > DCTP_EPS * 100.0)
   #else
                    if( (pcl_face->orig_quad[0]->coords[1] - pcl_face->orig_quad[3]->coords[1]) * cd_ratio > DCTP_EPS * 100.0)
   #endif
  #else
   #ifdef OSG_UNION_TRI_QUAD
                    if( (pcl_face->orig_face[0]->coords[1] - pcl_face->orig_face[3]->coords[1]) * 0.5 > DCTP_EPS * 100.0)
   #else
                    if( (pcl_face->orig_quad[0]->coords[1] - pcl_face->orig_quad[3]->coords[1]) * 0.5 > DCTP_EPS * 100.0)
   #endif
  #endif
                    {
  #ifdef OSG_ARBITRARY_SPLIT
                        pclMesh->SubdivideQuadNS(pcl_face, cpt_errcell->fSplitValue);
  #else
                        pclMesh->SubdivideQuadNS(pcl_face);
  #endif
                    }
                    else
                    {
                        b_split_ok = false;
                    }
                }
                if(b_split_ok)
                {
                    SubdivideBuild(pclMesh, pcl_face);
                    ++ui_face_cnt;      // one new face
                    f_prev_error = f_act_error;
                    f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                }
                else
                {
                    f_prev_error = f_act_error;
                    f_act_error  = 0.0;
                }
 #else
                pclMesh->SubdivideQuad(pcl_face);
                SubdivideBuild(pclMesh, pcl_face);
                ui_face_cnt += 3;   // three new faces
                f_prev_error = f_act_error;
                f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
 #endif
            }
#else
            if( (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell)
            {
                f_act_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                while(f_act_error > fError)
                {
                    pclMesh->SubdivideQuad(pcl_face);
                    SubdivideBuild(pclMesh, pcl_face);
                    ui_face_cnt += 3;   // three new faces
                    f_prev_error = f_act_error;
                    f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptErrorCell->fError;
                }
            }
            else
            {
                f_act_error  = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptBPCell->fError;
                f_prev_error = (static_cast<SFaceTreeCell*>(pcl_face->faceinfo) )->ptBPCell->fPrevError;
            }
#endif
            if(f_act_error > m_fMaxError)
            {
                m_fMaxError = f_act_error;
                rfMinError  = f_act_error;
            }
            if(f_prev_error < rfMaxError)
            {
                rfMaxError = f_prev_error;
            }
        }
    }

    // delete faceinfo and constructed bezier patches
    for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
    {
        pcl_face = pclMesh->faces[ui_face];
        pt_finfo = static_cast<SFaceTreeCell*>(pcl_face->faceinfo);
        if(pt_finfo)
        {
            if(pt_finfo->bOwnSurface)
            {
#ifdef OSG_USE_NURBS_PATCH
                delete pt_finfo->pclBSplineSurface;
#else
                delete pt_finfo->pclBezierSurface;
#endif
            }
            delete pt_finfo;
            pcl_face->faceinfo = NULL;
        }
/*		else
        {
            pclMesh->removeFace( ui_face );
            --ui_face;
            --ui_face_cnt;
        }*/
    }

//	std::cerr << "build " << ui_face_cnt << " faces" << std::endl;

/*	if( pclMesh->faces.size( ) >= 1000 )
    {
        if( fError > m_fErrorCutoff )
        {
            std::cerr << "reduce error cutoff: " << m_fErrorCutoff << " -> " << fError << std::endl;
            m_fErrorCutoff = fError;
        }
    }
    if( fError <= m_fErrorCutoff )
    {
        rfMinError = 0.0;
    }*/

//	std::cerr << "done" << std::endl;

    return;
}
//#endif


/*#ifdef OSG_ARBITRARY_SPLIT
void CErrorQuadTree::CalculatePoints( std::vector< Vec2d > *pvclInsert, std::vector< Vec2d > *pvclDelete,
                                      BSplineTensorSurface *pclPatch,
                                      float fError, float &rfMinError, float &rfMaxError )
{
    std::vector< SFaceTreeCell >			vt_build_cells;
    unsigned int					ui_cell;
    unsigned int					ui_cell_cnt = 1;
    float							f_act_error;
    float							f_prev_error;
    float							f_old_error;
    bool							b_insert;
    std::vector< BSplineTensorSurface >	vcl_surfaces;
    Vec2dset						scl_check;

    if( fError < m_fErrorCutoff )
    {
        fError = m_fErrorCutoff;
    }

    pvclInsert->clear( );
    pvclDelete->clear( );

    if( m_fMaxError >= 0.0 )
    {
        f_old_error = rfMinError;
        if( fError <= rfMinError )
        {
            b_insert = true;
        }
        else if( fError >= rfMaxError )
        {
            b_insert = false;
        }
        else
        {
            return;
        }
    }
    else
    {
        f_old_error = FLT_MAX;
        b_insert = true;
    }

    if( m_ptRoot == NULL )
    {
        m_ptRoot = new SErrorTreeCell;
        m_ptRoot->ptChildren = NULL;
        m_ptRoot->fError = -1.0;
    }

    vt_build_cells.resize( 1 );
    vt_build_cells[ 0 ].bOwnSurface = false;
    vt_build_cells[ 0 ].pclBSplineSurface = pclPatch;
    vt_build_cells[ 0 ].ptErrorCell = m_ptRoot;
    pclPatch->getParameterInterval_U( vt_build_cells[ 0 ].clMin[0], vt_build_cells[ 0 ].clMax[0] );
    pclPatch->getParameterInterval_V( vt_build_cells[ 0 ].clMin[1], vt_build_cells[ 0 ].clMax[1] );
    ComputeError( &( vt_build_cells[ 0 ] ) );

    rfMinError = -1.0;
    rfMaxError = FLT_MAX;

    if( ( fError >= m_fMaxError ) && ( m_fMaxError >= 0.0 ) )
    {
        // ok, we already have a subdivision for that error...
        for( ui_cell = 0; ui_cell < ui_cell_cnt; ++ui_cell )
        {
            f_prev_error = FLT_MAX;
            f_act_error = vt_build_cells[ ui_cell ].ptErrorCell->fError;
            while( f_act_error > fError )
            {
                vt_build_cells.resize( ui_cell_cnt + 1 );
                vt_build_cells[ ui_cell_cnt ].bOwnSurface = false;
                vt_build_cells[ ui_cell_cnt ].pclBSplineSurface = NULL;
                vt_build_cells[ ui_cell_cnt ].clMin = vt_build_cells[ ui_cell ].clMin;
                vt_build_cells[ ui_cell_cnt ].clMax = vt_build_cells[ ui_cell ].clMax;
                vt_build_cells[ ui_cell ].bOwnSurface = false;
                vt_build_cells[ ui_cell ].pclBSplineSurface = NULL;
                if( vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue < 0.0 )
                {
                    vt_build_cells[ ui_cell ].clMax[0] =
                        vt_build_cells[ ui_cell ].clMin[0]
                        - ( vt_build_cells[ ui_cell ].clMax[0] - vt_build_cells[ ui_cell ].clMin[0] )
                        * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                    vt_build_cells[ ui_cell_cnt ].clMin[0] = vt_build_cells[ ui_cell ].clMax[0];
                }
                else
                {
                    vt_build_cells[ ui_cell ].clMax[1] =
                        vt_build_cells[ ui_cell ].clMin[1]
                        + ( vt_build_cells[ ui_cell ].clMax[1] - vt_build_cells[ ui_cell ].clMin[1] )
                        * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                    vt_build_cells[ ui_cell_cnt ].clMin[1] = vt_build_cells[ ui_cell ].clMax[1];
                }
                // set new error cells
                vt_build_cells[ ui_cell_cnt ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 1 ] );
                vt_build_cells[ ui_cell ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 0 ] );
                if( ( b_insert ) && ( f_act_error >= f_old_error ) )
                {
                    // insert new points
                    if( scl_check.insert( vt_build_cells[ ui_cell ].clMax ).second )
                    {
                        pvclInsert->push_back( vt_build_cells[ ui_cell ].clMax );
                    }
                    if( scl_check.insert( vt_build_cells[ ui_cell_cnt ].clMin ).second )
                    {
                        pvclInsert->push_back( vt_build_cells[ ui_cell_cnt ].clMin );
                    }
                }
                else
                {
                    scl_check.insert( vt_build_cells[ ui_cell ].clMax );
                    scl_check.insert( vt_build_cells[ ui_cell_cnt ].clMin );
                }
                ++ui_cell_cnt;		// one new face
                f_prev_error = f_act_error;
                f_act_error = vt_build_cells[ ui_cell ].ptErrorCell->fError;
            }
            if( f_act_error > rfMinError )
            {
                rfMinError = f_act_error;
            }
            if( f_prev_error < rfMaxError )
            {
                rfMaxError = f_prev_error;
            }
            if( !b_insert )
            {
                // delete old points
                while( f_act_error > f_old_error )
                {
                    vt_build_cells.resize( ui_cell_cnt + 1 );
                    vt_build_cells[ ui_cell_cnt ].bOwnSurface = false;
                    vt_build_cells[ ui_cell_cnt ].pclBSplineSurface = NULL;
                    vt_build_cells[ ui_cell_cnt ].clMin = vt_build_cells[ ui_cell ].clMin;
                    vt_build_cells[ ui_cell_cnt ].clMax = vt_build_cells[ ui_cell ].clMax;
                    vt_build_cells[ ui_cell ].bOwnSurface = false;
                    vt_build_cells[ ui_cell ].pclBSplineSurface = NULL;
                    if( vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue < 0.0 )
                    {
                        vt_build_cells[ ui_cell ].clMax[0] =
                            vt_build_cells[ ui_cell ].clMin[0]
                            - ( vt_build_cells[ ui_cell ].clMax[0] - vt_build_cells[ ui_cell ].clMin[0] )
                            * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                        vt_build_cells[ ui_cell_cnt ].clMin[0] = vt_build_cells[ ui_cell ].clMax[0];
                    }
                    else
                    {
                        vt_build_cells[ ui_cell ].clMax[1] =
                            vt_build_cells[ ui_cell ].clMin[1]
                            + ( vt_build_cells[ ui_cell ].clMax[1] - vt_build_cells[ ui_cell ].clMin[1] )
                            * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                        vt_build_cells[ ui_cell_cnt ].clMin[1] = vt_build_cells[ ui_cell ].clMax[1];
                    }
                    // set new error cells
                    vt_build_cells[ ui_cell_cnt ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 1 ] );
                    vt_build_cells[ ui_cell ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 0 ] );
                    if( scl_check.insert( vt_build_cells[ ui_cell ].clMax ).second )
                    {
                        pvclDelete->push_back( vt_build_cells[ ui_cell ].clMax );
                    }
                    if( scl_check.insert( vt_build_cells[ ui_cell_cnt ].clMin ).second )
                    {
                        pvclDelete->push_back( vt_build_cells[ ui_cell_cnt ].clMin );
                    }
                    ++ui_cell_cnt;		// one new face
                    f_act_error = vt_build_cells[ ui_cell ].ptErrorCell->fError;
                }
            }
        }
        vt_build_cells.clear( );
        return;
    }

    // we need to build a new Kd-tree
    for( ui_cell = 0; ui_cell < ui_cell_cnt; ++ui_cell )
    {
        f_prev_error = FLT_MAX;
        f_act_error = vt_build_cells[ ui_cell ].ptErrorCell->fError;
        while( f_act_error > fError )
        {
            if( vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue < 0.0 )
            {
                vt_build_cells[ ui_cell ].pclBSplineSurface->subDivisionU(
                    vcl_surfaces, -vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue );
            }
            else
            {
                vt_build_cells[ ui_cell ].pclBSplineSurface->subDivisionV(
                    vcl_surfaces, vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue );
            }
            vt_build_cells.resize( ui_cell_cnt + 1 );
            vt_build_cells[ ui_cell_cnt ].bOwnSurface = true;
            vt_build_cells[ ui_cell_cnt ].pclBSplineSurface = new BSplineTensorSurface;
            *( vt_build_cells[ ui_cell_cnt ].pclBSplineSurface ) = vcl_surfaces[ 1 ];
            vt_build_cells[ ui_cell_cnt ].clMin = vt_build_cells[ ui_cell ].clMin;
            vt_build_cells[ ui_cell_cnt ].clMax = vt_build_cells[ ui_cell ].clMax;
            if( vt_build_cells[ ui_cell ].bOwnSurface )
            {
                delete vt_build_cells[ ui_cell ].pclBSplineSurface;
            }
            vt_build_cells[ ui_cell ].bOwnSurface = true;
            vt_build_cells[ ui_cell ].pclBSplineSurface = new BSplineTensorSurface;
            *( vt_build_cells[ ui_cell ].pclBSplineSurface ) = vcl_surfaces[ 0 ];
            std::cerr << vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue << std::endl;
            std::cerr << vt_build_cells[ ui_cell ].clMin << vt_build_cells[ ui_cell ].clMax << std::endl;
            if( vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue < 0.0 )
            {
                vt_build_cells[ ui_cell ].clMax[0] =
                    vt_build_cells[ ui_cell ].clMin[0]
                    - ( vt_build_cells[ ui_cell ].clMax[0] - vt_build_cells[ ui_cell ].clMin[0] )
                    * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                vt_build_cells[ ui_cell_cnt ].clMin[0] = vt_build_cells[ ui_cell ].clMax[0];
            }
            else
            {
                vt_build_cells[ ui_cell ].clMax[1] =
                    vt_build_cells[ ui_cell ].clMin[1]
                    + ( vt_build_cells[ ui_cell ].clMax[1] - vt_build_cells[ ui_cell ].clMin[1] )
                    * vt_build_cells[ ui_cell ].ptErrorCell->fSplitValue;
                vt_build_cells[ ui_cell_cnt ].clMin[1] = vt_build_cells[ ui_cell ].clMax[1];
            }
            std::cerr << vt_build_cells[ ui_cell ].clMin << vt_build_cells[ ui_cell ].clMax << std::endl;
            std::cerr << vt_build_cells[ ui_cell_cnt ].clMin << vt_build_cells[ ui_cell_cnt ].clMax << std::endl << std::endl;
            // set new error cells
            if( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren == NULL )
            {
                vt_build_cells[ ui_cell ].ptErrorCell->ptChildren = new SErrorTreeCell[ 2 ];
                vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 0 ].ptChildren = NULL;
                vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 0 ].fError = -1.0;
                vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 1 ].ptChildren = NULL;
                vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 1 ].fError = -1.0;
            }
            vt_build_cells[ ui_cell_cnt ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 1 ] );
            vt_build_cells[ ui_cell ].ptErrorCell = &( vt_build_cells[ ui_cell ].ptErrorCell->ptChildren[ 0 ] );
            // compute error
            ComputeError( &( vt_build_cells[ ui_cell ] ) );
            ComputeError( &( vt_build_cells[ ui_cell_cnt ] ) );
            // insert new points
            if( scl_check.insert( vt_build_cells[ ui_cell ].clMax ).second )
            {
                pvclInsert->push_back( vt_build_cells[ ui_cell ].clMax );
            }
            if( scl_check.insert( vt_build_cells[ ui_cell_cnt ].clMin ).second )
            {
                pvclInsert->push_back( vt_build_cells[ ui_cell_cnt ].clMin );
            }
            ++ui_cell_cnt;		// one new face
            f_prev_error = f_act_error;
            f_act_error = vt_build_cells[ ui_cell ].ptErrorCell->fError;
        }
        if( f_act_error > rfMinError )
        {
            rfMinError = f_act_error;
        }
        if( f_prev_error < rfMaxError )
        {
            rfMaxError = f_prev_error;
        }
    }

    // delete build cells and constructed bspline patches
    for( ui_cell = 0; ui_cell < ui_cell_cnt; ++ui_cell )
    {
        if( vt_build_cells[ ui_cell ].bOwnSurface )
        {
            vt_build_cells[ ui_cell ].pclBSplineSurface;
        }
    }
    vt_build_cells.clear( );
}
#endif*/


#ifdef OSG_ONE_CHILD_PTR
void CErrorQuadTree::DeleteNode(SErrorTreeCell *pclNode)
{
    if(pclNode->ptChildren)
    {
        DeleteNode(&(pclNode->ptChildren[0]) );
        DeleteNode(&(pclNode->ptChildren[1]) );
 #ifndef OSG_USE_KD_TREE
        DeleteNode(&(pclNode->ptChildren[2]) );
        DeleteNode(&(pclNode->ptChildren[3]) );
 #endif
        delete[]  pclNode->ptChildren;
        pclNode->ptChildren = NULL;
    }
}
#else
void CErrorQuadTree::DeleteNode(SErrorTreeCell *&rpclNode)
{
    if(rpclNode->aptChildren[0])
    {
        DeleteNode(rpclNode->aptChildren[0]);
        DeleteNode(rpclNode->aptChildren[1]);
 #ifndef OSG_USE_KD_TREE
        DeleteNode(rpclNode->aptChildren[2]);
        DeleteNode(rpclNode->aptChildren[3]);
 #endif
    }
    delete rpclNode;
    rpclNode = NULL;
}
#endif


//#ifndef OSG_ARBITRARY_SPLIT
void CErrorQuadTree::SetInitialCells(DCTPMesh *pclMesh, float fError,
#ifdef OSG_USE_NURBS_PATCH
 #ifdef OSG_ARBITRARY_SPLIT
                                     BSplineTensorSurface *pclPatch,
                                     const Vec2d cclMinParam, const Vec2d cclMaxParam)
 #else
BSplineTensorSurface * pclPatch)
 #endif
#else
std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
const std::vector<double> *cpvdIntervalsU,
const std::vector<double> *cpvdIntervalsV)
#endif
{
#ifdef OSG_USE_NURBS_PATCH
    double         d_min_x;
    double         d_max_x;
    double         d_min_y;
    double         d_max_y;
    Vec3d          acl_edge_points[4];
    DCTPFace      *pcl_face;
    SFaceTreeCell *pt_finfo;

 #ifdef OSG_ARBITRARY_SPLIT
    d_min_x = cclMinParam[0];
    d_min_y = cclMinParam[1];
    d_max_x = cclMaxParam[0];
    d_max_y = cclMaxParam[1];
 #else
    pclPatch->getParameterInterval_U(d_min_x, d_max_x);
    pclPatch->getParameterInterval_V(d_min_y, d_max_y);
 #endif
    acl_edge_points[0][0] = d_min_x;
    acl_edge_points[1][0] = d_max_x;
    acl_edge_points[2][0] = d_max_x;
    acl_edge_points[3][0] = d_min_x;
    acl_edge_points[0][1] = d_max_y;
    acl_edge_points[1][1] = d_max_y;
    acl_edge_points[2][1] = d_min_y;
    acl_edge_points[3][1] = d_min_y;
    acl_edge_points[0][2] = 0.0;
    acl_edge_points[1][2] = 0.0;
    acl_edge_points[2][2] = 0.0;
    acl_edge_points[3][2] = 0.0;

    if(m_ptRoot == NULL)
    {
        m_ptRoot = new SErrorTreeCell;
 #ifdef OSG_ONE_CHILD_PTR
        m_ptRoot->ptChildren = NULL;
 #else
        m_ptRoot->aptChildren[0] = NULL;
        m_ptRoot->aptChildren[1] = NULL;
        m_ptRoot->aptChildren[2] = NULL;
        m_ptRoot->aptChildren[3] = NULL;
 #endif
        m_ptRoot->fError = -1.0;
    }

    pcl_face = pclMesh->AddQuad(acl_edge_points[0], acl_edge_points[1],
                                acl_edge_points[2], acl_edge_points[3], 0.0);
    pt_finfo              = new SFaceTreeCell;
    pt_finfo->bOwnSurface = false;
 #ifdef OSG_ARBITRARY_SPLIT
    pt_finfo->pclBSplineSurface = NULL;
 #else
    pt_finfo->pclBSplineSurface = pclPatch;
 #endif
    pt_finfo->ptErrorCell = m_ptRoot;
    pcl_face->faceinfo    = static_cast<void*>(pt_finfo);
#else
    const unsigned int cui_u_size = cpvdIntervalsU->size() - 1;
    const unsigned int cui_v_size = cpvdIntervalsV->size() - 1;
    Vec3d              acl_edge_points[4];
    unsigned int       ui_u;
    unsigned int       ui_v;
    DCTPFace          *pcl_face;
    SFaceTreeCell     *pt_finfo;
    unsigned int       ui_face;
    unsigned int       ui_face_cnt;
    float              f_act_error;

    acl_edge_points[0][2] = 1.0;
    acl_edge_points[1][2] = 1.0;
    acl_edge_points[2][2] = 1.0;
    acl_edge_points[3][2] = 1.0;

    if(m_vvptRoot.size() == 0)
    {
//		std::cerr << "new QuadTree" << std::endl;
        m_vvptRoot.resize(cui_u_size);

        for(ui_u = 0; ui_u < cui_u_size; ++ui_u)
        {
            m_vvptRoot[ui_u].resize(cui_v_size);

            for(ui_v = 0; ui_v < cui_v_size; ++ui_v)
            {
                m_vvptRoot[ui_u][ui_v] = new SErrorTreeCell;
 #ifdef OSG_ONE_CHILD_PTR
                m_vvptRoot[ui_u][ui_v]->ptChildren = NULL;
 #else
                m_vvptRoot[ui_u][ui_v]->aptChildren[0] = NULL;
                m_vvptRoot[ui_u][ui_v]->aptChildren[1] = NULL;
                m_vvptRoot[ui_u][ui_v]->aptChildren[2] = NULL;
                m_vvptRoot[ui_u][ui_v]->aptChildren[3] = NULL;
 #endif
                m_vvptRoot[ui_u][ui_v]->fError = -1.0;
            }
        }

        ComputeBPTree(pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
    }

    acl_edge_points[0][0] = (*cpvdIntervalsU)[0];
    acl_edge_points[1][0] = (*cpvdIntervalsU)[cui_u_size];
    acl_edge_points[2][0] = (*cpvdIntervalsU)[cui_u_size];
    acl_edge_points[3][0] = (*cpvdIntervalsU)[0];
    acl_edge_points[0][1] = (*cpvdIntervalsV)[cui_v_size];
    acl_edge_points[1][1] = (*cpvdIntervalsV)[cui_v_size];
    acl_edge_points[2][1] = (*cpvdIntervalsV)[0];
    acl_edge_points[3][1] = (*cpvdIntervalsV)[0];
    pcl_face              = pclMesh->AddQuad(acl_edge_points[0], acl_edge_points[1],
                                             acl_edge_points[2], acl_edge_points[3], 0.0);
    pt_finfo                   = new SFaceTreeCell;
    pt_finfo->bOwnSurface      = false;
    pt_finfo->pclBezierSurface = NULL;
    pt_finfo->ptErrorCell      = NULL;
    pt_finfo->ptBPCell         = m_ptBPRoot;
    pcl_face->faceinfo         = ( void* ) pt_finfo;

    ui_face_cnt = 1;

    for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
    {
        pcl_face = pclMesh->faces[ui_face];
        if( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell)
        {
            f_act_error = ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->fError;
            while(f_act_error > fError)
            {
                if( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->aptChildren[1])
                {
                    // xx
                    // xx
                    pclMesh->SubdivideQuad(pcl_face);
                    SubdivideNode(pclMesh, pcl_face);
                    ui_face_cnt += 3;
                }
                else if( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->aptChildren[0])
                {
                    // x
                    // x
                    pclMesh->SubdivideQuadNS(pcl_face);
                    SubdivideNode(pclMesh, pcl_face);
                    ++ui_face_cnt;
                }
                else if( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->aptChildren[2])
                {
                    // xx
                    pclMesh->SubdivideQuadEW(pcl_face);
                    SubdivideNode(pclMesh, pcl_face);
                    ++ui_face_cnt;
                }
                if( ( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell) &&
                    ( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->aptChildren[3]) )
                {
                    f_act_error = ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->fError;
                }
                else
                {
                    f_act_error = 0.0;
                }
            }
        }
        if( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell == NULL)
        {
            delete ( ( SFaceTreeCell* ) pcl_face->faceinfo);
            pcl_face->faceinfo = NULL;
        }
    }

    for(ui_face = 0; ui_face < ui_face_cnt; ++ui_face)
    {
        pcl_face = pclMesh->faces[ui_face];
        if(pcl_face->faceinfo)
        {
/*			std::cerr << "quad:";
            std::cerr << pcl_face->orig_quad[ 0 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 1 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 2 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 3 ]->coords << std::endl;
            std::cerr << ( ( SFaceTreeCell* ) pcl_face->faceinfo )->ptBPCell->uiLeft << " - ";
            std::cerr << ( ( SFaceTreeCell* ) pcl_face->faceinfo )->ptBPCell->uiRight << " , ";
            std::cerr << ( ( SFaceTreeCell* ) pcl_face->faceinfo )->ptBPCell->uiBottom << " - ";
            std::cerr << ( ( SFaceTreeCell* ) pcl_face->faceinfo )->ptBPCell->uiTop << std::endl;*/
 #ifdef OSG_UNION_TRI_QUAD
            pclMesh->MoveVertex(
                pcl_face->orig_face[0],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiLeft],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiTop + 1],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_face[1],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiRight + 1],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiTop + 1],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_face[2],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiRight + 1],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiBottom],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_face[3],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiLeft],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiBottom],
                       0.0) );
 #else
            pclMesh->MoveVertex(
                pcl_face->orig_quad[0],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiLeft],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiTop + 1],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_quad[1],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiRight + 1],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiTop + 1],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_quad[2],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiRight + 1],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiBottom],
                       0.0) );
            pclMesh->MoveVertex(
                pcl_face->orig_quad[3],
                Vec3d( (*cpvdIntervalsU)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiLeft],
                       (*cpvdIntervalsV)[( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiBottom],
                       0.0) );
 #endif
/*			std::cerr << "moved to:";
            std::cerr << pcl_face->orig_quad[ 0 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 1 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 2 ]->coords << " ";
            std::cerr << pcl_face->orig_quad[ 3 ]->coords << std::endl;*/
            if( ( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->aptChildren[3] == NULL) &&
                ( ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->fError > fError) )
            {
                // single patch
                ui_u = ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiLeft;
                ui_v = ( ( SFaceTreeCell* ) pcl_face->faceinfo)->ptBPCell->uiBottom;
//				std::cerr << ui_u << "," << ui_v << std::endl;
                pt_finfo                   = ( ( SFaceTreeCell* ) pcl_face->faceinfo);
                pt_finfo->bOwnSurface      = false;
                pt_finfo->pclBezierSurface = &( (*pvvclPatches)[ui_u][ui_v]);
                pt_finfo->ptErrorCell      = m_vvptRoot[ui_u][ui_v];
                pt_finfo->ptBPCell         = NULL;
//				pcl_face->faceinfo = ( void* ) pt_finfo;
            }
        }
    }

#endif
}


void CErrorQuadTree::SubdivideNode(DCTPMesh *pclMesh, DCTPFace *pclFace)
{
    const unsigned int cui_face_cnt = UInt32(pclMesh->faces.size());
    unsigned int       ui_child;
#ifdef OSG_USE_KD_TREE
    DCTPFace *apcl_faces[2];
#else
    DCTPFace *apcl_faces[4];
#endif
    SFaceTreeCell *pcl_old_node = static_cast<SFaceTreeCell*>(pclFace->faceinfo);
    SFaceTreeCell *pcl_new_node;

    pclFace->faceinfo = NULL;

#ifdef OSG_USE_NURBS_PATCH
    apcl_faces[0] = pclFace;
 #ifdef OSG_USE_KD_TREE
    apcl_faces[1] = pclMesh->faces[cui_face_cnt - 1];
 #else
    apcl_faces[1] = pclMesh->faces[cui_face_cnt - 3];
    apcl_faces[2] = pclMesh->faces[cui_face_cnt - 2];
    apcl_faces[3] = pclMesh->faces[cui_face_cnt - 1];
 #endif

 #ifdef OSG_USE_KD_TREE

    for(ui_child = 0; ui_child < 2; ++ui_child)
 #else

    for(ui_child = 0; ui_child < 4; ++ui_child)
 #endif
    {
        pcl_new_node = new SFaceTreeCell;
//		std::cerr << "subdivide with ErrorCell" << std::endl;
 #ifdef OSG_ONE_CHILD_PTR
        pcl_new_node->ptErrorCell = &(pcl_old_node->ptErrorCell->ptChildren[ui_child]);
 #else
        pcl_new_node->ptErrorCell = pcl_old_node->ptErrorCell->aptChildren[ui_child];
 #endif
        pcl_new_node->pclBSplineSurface = NULL;
        pcl_new_node->bOwnSurface       = false;
        apcl_faces[ui_child]->faceinfo  = static_cast<void*>(pcl_new_node);
    }

#else
    if(pcl_old_node->ptErrorCell)
    {
        apcl_faces[0] = pclFace;
        apcl_faces[1] = pclMesh->faces[cui_face_cnt - 3];
        apcl_faces[2] = pclMesh->faces[cui_face_cnt - 2];
        apcl_faces[3] = pclMesh->faces[cui_face_cnt - 1];

        for(ui_child = 0; ui_child < 4; ++ui_child)
        {
            pcl_new_node = new SFaceTreeCell;
//			std::cerr << "subdivide with ErrorCell" << std::endl;
 #ifdef OSG_ONE_CHILD_PTR
            pcl_new_node->ptErrorCell = &(pcl_old_node->ptErrorCell->ptChildren[ui_child]);
 #else
            pcl_new_node->ptErrorCell = pcl_old_node->ptErrorCell->aptChildren[ui_child];
 #endif
            pcl_new_node->ptBPCell         = NULL;
            pcl_new_node->pclBezierSurface = NULL;
            pcl_new_node->bOwnSurface      = false;
            apcl_faces[ui_child]->faceinfo = static_cast<void*>(pcl_new_node);
        }
    }
    else if(pcl_old_node->ptBPCell->aptChildren[1])
    {
        // xx
        // xx
        apcl_faces[0] = pclFace;
        apcl_faces[1] = pclMesh->faces[cui_face_cnt - 3];
        apcl_faces[2] = pclMesh->faces[cui_face_cnt - 2];
        apcl_faces[3] = pclMesh->faces[cui_face_cnt - 1];

        for(ui_child = 0; ui_child < 4; ++ui_child)
        {
            pcl_new_node = new SFaceTreeCell;
//			std::cerr << "subdivide with BPCell" << std::endl;
            pcl_new_node->ptErrorCell = NULL;
            pcl_new_node->ptBPCell    = pcl_old_node->ptBPCell->aptChildren[ui_child];
/*			std::cerr << pcl_new_node->ptBPCell->uiLeft << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiRight << " , ";
            std::cerr << pcl_new_node->ptBPCell->uiBottom << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiTop << std::endl;
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 0 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 1 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 2 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 3 ]->coords << std::endl;*/
            pcl_new_node->pclBezierSurface = NULL;
            pcl_new_node->bOwnSurface      = false;
            apcl_faces[ui_child]->faceinfo = static_cast<void*>(pcl_new_node);
        }
    }
    else if(pcl_old_node->ptBPCell->aptChildren[0])
    {
        // x
        // x
        apcl_faces[0] = pclFace;
        apcl_faces[1] = pclMesh->faces[cui_face_cnt - 1];

        for(ui_child = 0; ui_child < 2; ++ui_child)
        {
            pcl_new_node = new SFaceTreeCell;
//			std::cerr << "subdivide with BPCell" << std::endl;
            pcl_new_node->ptErrorCell = NULL;
            pcl_new_node->ptBPCell    = pcl_old_node->ptBPCell->aptChildren[3 * ui_child];
/*			std::cerr << pcl_new_node->ptBPCell->uiLeft << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiRight << " , ";
            std::cerr << pcl_new_node->ptBPCell->uiBottom << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiTop << std::endl;
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 0 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 1 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 2 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 3 ]->coords << std::endl;*/
            pcl_new_node->pclBezierSurface = NULL;
            pcl_new_node->bOwnSurface      = false;
            apcl_faces[ui_child]->faceinfo = static_cast<void*>(pcl_new_node);
        }
    }
    else
    {
        // xx
        apcl_faces[0] = pclFace;
        apcl_faces[1] = pclMesh->faces[cui_face_cnt - 1];

        for(ui_child = 0; ui_child < 2; ++ui_child)
        {
            pcl_new_node = new SFaceTreeCell;
//			std::cerr << "subdivide with BPCell" << std::endl;
            pcl_new_node->ptErrorCell = NULL;
            pcl_new_node->ptBPCell    = pcl_old_node->ptBPCell->aptChildren[3 - ui_child];
/*			std::cerr << pcl_new_node->ptBPCell->uiLeft << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiRight << " , ";
            std::cerr << pcl_new_node->ptBPCell->uiBottom << " - ";
            std::cerr << pcl_new_node->ptBPCell->uiTop << std::endl;
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 0 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 1 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 2 ]->coords << " ";
            std::cerr << apcl_faces[ ui_child ]->orig_quad[ 3 ]->coords << std::endl;*/
            pcl_new_node->pclBezierSurface = NULL;
            pcl_new_node->bOwnSurface      = false;
            apcl_faces[ui_child]->faceinfo = static_cast<void*>(pcl_new_node);
        }
    }
#endif

    delete pcl_old_node;
}


void CErrorQuadTree::SubdivideBuild(DCTPMesh *pclMesh, DCTPFace *pclFace)
{
    const unsigned int cui_face_cnt = UInt32(pclMesh->faces.size());
    unsigned int       ui_child;
#ifdef OSG_USE_KD_TREE
    DCTPFace *apcl_faces[2];
#else
    DCTPFace *apcl_faces[4];
#endif
    SFaceTreeCell *pcl_old_node = static_cast<SFaceTreeCell*>(pclFace->faceinfo);
    SFaceTreeCell *pcl_new_node;
#ifdef OSG_USE_NURBS_PATCH
 #ifdef OSG_USE_KD_TREE
    std::vector<BSplineTensorSurface> vcl_surfaces;
 #else
    std::vector<std::vector<BSplineTensorSurface> > vvcl_surfaces;
 #endif
#else
 #ifdef OSG_USE_KD_TREE
    std::vector<BezierTensorSurface> vcl_surfaces;
 #else
    std::vector<std::vector<BezierTensorSurface> > vvcl_surfaces;
 #endif
#endif

    apcl_faces[0] = pclFace;
#ifdef OSG_USE_KD_TREE
    apcl_faces[1] = pclMesh->faces[cui_face_cnt - 1];
#else
    apcl_faces[1] = pclMesh->faces[cui_face_cnt - 3];
    apcl_faces[2] = pclMesh->faces[cui_face_cnt - 2];
    apcl_faces[3] = pclMesh->faces[cui_face_cnt - 1];
#endif

    pclFace->faceinfo = NULL;
#ifdef OSG_USE_NURBS_PATCH
 #ifdef OSG_USE_KD_TREE
  #ifdef OSG_ARBITRARY_SPLIT
    if(pcl_old_node->ptErrorCell->fSplitValue < 0.0)
    {
        pcl_old_node->pclBSplineSurface->subDivisionU(vcl_surfaces, -pcl_old_node->ptErrorCell->fSplitValue);
    }
    else
    {
        pcl_old_node->pclBSplineSurface->subDivisionV(vcl_surfaces, pcl_old_node->ptErrorCell->fSplitValue);
    }
  #else
    if(pcl_old_node->ptErrorCell->bSplitHoriz)
    {
        pcl_old_node->pclBSplineSurface->midPointSubDivisionU(vcl_surfaces);
    }
    else
    {
        pcl_old_node->pclBSplineSurface->midPointSubDivisionV(vcl_surfaces);
    }
  #endif
 #else
    pcl_old_node->pclBSplineSurface->midPointSubDivision(vvcl_surfaces);
 #endif
#else
 #ifdef OSG_USE_KD_TREE
  #error
 #else
    pcl_old_node->pclBezierSurface->midPointSubDivision(vvcl_surfaces);
 #endif
#endif

#ifdef OSG_ONE_CHILD_PTR
 #ifdef OSG_USE_KD_TREE

    for(ui_child = 0; ui_child < 2; ++ui_child)
 #else

    for(ui_child = 0; ui_child < 4; ++ui_child)
 #endif
    {
        pcl_new_node              = new SFaceTreeCell;
        pcl_new_node->ptErrorCell = &(pcl_old_node->ptErrorCell->ptChildren[ui_child]);
        pcl_new_node->bOwnSurface = true;
 #ifdef OSG_USE_NURBS_PATCH
        pcl_new_node->pclBSplineSurface = new BSplineTensorSurface;
  #ifdef OSG_USE_KD_TREE
                                                          (*pcl_new_node->pclBSplineSurface) = vcl_surfaces[ui_child];
  #else
        (*pcl_new_node->pclBSplineSurface) = vvcl_surfaces[( (ui_child + 1) >> 1) & 1][1 - (ui_child >> 1)];
  #endif
 #else
        pcl_new_node->pclBezierSurface = new BezierTensorSurface;
  #ifdef OSG_USE_KD_TREE
                                                          (*pcl_new_node->pclBezierSurface) = vvcl_surfaces[ui_child];
  #else
        (*pcl_new_node->pclBezierSurface) = vvcl_surfaces[( (ui_child + 1) >> 1) & 1][1 - (ui_child >> 1)];
  #endif
 #endif
        apcl_faces[ui_child]->faceinfo = static_cast<void*>(pcl_new_node);
    }

    if(pcl_old_node->ptErrorCell->ptChildren == NULL)
    {
 #ifdef OSG_USE_KD_TREE
        pcl_old_node->ptErrorCell->ptChildren = new SErrorTreeCell[2];

        for(ui_child = 0; ui_child < 2; ++ui_child)
 #else
        pcl_old_node->ptErrorCell->ptChildren = new SErrorTreeCell[4];

        for(ui_child = 0; ui_child < 4; ++ui_child)
 #endif
        {
            pcl_new_node                          = static_cast<SFaceTreeCell*>(apcl_faces[ui_child]->faceinfo);
            pcl_new_node->ptErrorCell             = &(pcl_old_node->ptErrorCell->ptChildren[ui_child]);
            pcl_new_node->ptErrorCell->ptChildren = NULL;
            pcl_new_node->ptErrorCell->fError     = -1.0;
            ComputeError(apcl_faces[ui_child]);
        }
    }
#else
#ifdef OSG_USE_KD_TREE

    for(ui_child = 0; ui_child < 2; ++ui_child)
#else

    for(ui_child = 0; ui_child < 4; ++ui_child)
#endif
    {
        pcl_new_node                      = new SFaceTreeCell;
        pcl_new_node->ptErrorCell         = pcl_old_node->ptErrorCell->aptChildren[ui_child];
        pcl_new_node->bOwnSurface         = true;
        pcl_new_node->pclBezierSurface    = new BezierTensorSurface;
        (*pcl_new_node->pclBezierSurface) = vvcl_surfaces[( (ui_child + 1) >> 1) & 1][1 - (ui_child >> 1)];
        apcl_faces[ui_child]->faceinfo    = static_cast<void*>(pcl_new_node);
        if(pcl_new_node->ptErrorCell == NULL)
        {
            pcl_old_node->ptErrorCell->aptChildren[ui_child] = new SErrorTreeCell;
            pcl_new_node->ptErrorCell                        = pcl_old_node->ptErrorCell->aptChildren[ui_child];
            pcl_new_node->ptErrorCell->aptChildren[0]        = NULL;
            pcl_new_node->ptErrorCell->aptChildren[1]        = NULL;
 #ifndef OSG_USE_KD_TREE
            pcl_new_node->ptErrorCell->aptChildren[2] = NULL;
            pcl_new_node->ptErrorCell->aptChildren[3] = NULL;
 #endif
            pcl_new_node->ptErrorCell->fError = -1.0;
            ComputeError(apcl_faces[ui_child]);
        }
    }

#endif
/*	( SFaceTreeCell* )( apcl_faces[ 0 ]->faceinfo )->pclBezierSurface = vvcl_surfaces[ 0 ][ 1 ];
    ( SFaceTreeCell* )( apcl_faces[ 1 ]->faceinfo )->pclBezierSurface = vvcl_surfaces[ 1 ][ 1 ];
    ( SFaceTreeCell* )( apcl_faces[ 2 ]->faceinfo )->pclBezierSurface = vvcl_surfaces[ 1 ][ 0 ];
    ( SFaceTreeCell* )( apcl_faces[ 3 ]->faceinfo )->pclBezierSurface = vvcl_surfaces[ 0 ][ 0 ];*/

    if(pcl_old_node->bOwnSurface)
    {
#ifdef OSG_USE_NURBS_PATCH
        delete pcl_old_node->pclBSplineSurface;
#else
        delete pcl_old_node->pclBezierSurface;
#endif
    }
    delete pcl_old_node;
}
//#endif


/*#ifdef OSG_ARBITRARY_SPLIT
void CErrorQuadTree::ComputeError( SFaceTreeCell *ptCell )
#else*/
void CErrorQuadTree::ComputeError(DCTPFace *pclFace)
//#endif
{
//#ifndef OSG_ARBITRARY_SPLIT
    SFaceTreeCell *ptCell = static_cast<SFaceTreeCell*>(pclFace->faceinfo);
//#endif

    if(ptCell->ptErrorCell->fError >= 0.0)
    {
        return; // error was already calculated
    }

    if( ( (pclFace->orig_face[1]->coords[0] - pclFace->orig_face[3]->coords[0]) < 10.0) ||
        ( (pclFace->orig_face[1]->coords[1] - pclFace->orig_face[3]->coords[1]) < 10.0) )
    {
        // too small face!
        ptCell->ptErrorCell->fError = 0.0;
        return;
    }

#ifdef OSG_USE_NURBS_PATCH
    BSplineTensorSurface      *pcl_surface = ptCell->pclBSplineSurface;
    const std::vector<double> &crvd_knot_u = pcl_surface->getKnotVector_U();
    const std::vector<double> &crvd_knot_v = pcl_surface->getKnotVector_V();
    const unsigned int         cui_dim_u   = pcl_surface->getDimension_U();
    const unsigned int         cui_dim_v   = pcl_surface->getDimension_V();
    unsigned int               ui_idx;
#else
    BezierTensorSurface *pcl_surface = ptCell->pclBezierSurface;
#endif
    const std::vector<std::vector <Vec4d> > &crvvcl_cps = pcl_surface->getControlPointMatrix();
    const unsigned int                       cui_m      = UInt32(crvvcl_cps.size()) - 1;
    const unsigned int                       cui_n      = UInt32(crvvcl_cps[0].size()) - 1;
    Vec3d                                    ccl_b00;
    ccl_b00[0] = crvvcl_cps[0][0][0] / crvvcl_cps[0][0][3];
    ccl_b00[1] = crvvcl_cps[0][0][1] / crvvcl_cps[0][0][3];
    ccl_b00[2] = crvvcl_cps[0][0][2] / crvvcl_cps[0][0][3];
    Vec3d ccl_b0n;
    ccl_b0n[0] = crvvcl_cps[0][cui_n][0] / crvvcl_cps[0][cui_n][3];
    ccl_b0n[1] = crvvcl_cps[0][cui_n][1] / crvvcl_cps[0][cui_n][3];
    ccl_b0n[2] = crvvcl_cps[0][cui_n][2] / crvvcl_cps[0][cui_n][3];
    Vec3d ccl_bm0;
    ccl_bm0[0] = crvvcl_cps[cui_m][0][0] / crvvcl_cps[cui_m][0][3];
    ccl_bm0[1] = crvvcl_cps[cui_m][0][1] / crvvcl_cps[cui_m][0][3];
    ccl_bm0[2] = crvvcl_cps[cui_m][0][2] / crvvcl_cps[cui_m][0][3];
    Vec3d ccl_bmn;
    ccl_bmn[0] = crvvcl_cps[cui_m][cui_n][0] / crvvcl_cps[cui_m][cui_n][3];
    ccl_bmn[1] = crvvcl_cps[cui_m][cui_n][1] / crvvcl_cps[cui_m][cui_n][3];
    ccl_bmn[2] = crvvcl_cps[cui_m][cui_n][2] / crvvcl_cps[cui_m][cui_n][3];
    Vec3d        cl_cij;
    Vec3d        cl_bij;
    double       d_quad_size;
    unsigned int ui_i;
    unsigned int ui_j;
#ifndef OSG_USE_NURBS_PATCH
    const double cd_rn = 1.0 / cui_n;
    const double cd_rm = 1.0 / cui_m;
#endif
    Vec3d cl_ci0;
    Vec3d cl_cin;
#ifndef OSG_USE_NURBS_PATCH
    const Vec3d ccl_dcx0 = (ccl_bm0 - ccl_b00) * cd_rm;
    const Vec3d ccl_dcxn = (ccl_bmn - ccl_b0n) * cd_rm;
#endif
    Vec3d cl_norm;
#ifndef OSG_USE_NURBS_PATCH
    const Vec3d ccl_dc0x = (ccl_b0n - ccl_b00) * cd_rn;
    const Vec3d ccl_dcmx = (ccl_bmn - ccl_bm0) * cd_rn;
    Vec3d       cl_c0j;
    Vec3d       cl_cmj;
#endif
    int   i_err;
    Vec2d cl_uv;
#ifdef OSG_USE_NURBS_PATCH
    Vec2d cl_min;
    Vec2d cl_add;
#endif
#ifdef OSG_ARBITRARY_SPLIT
    Vec2d cl_worst;
#endif
    // normal stuff
    Vec3d cl_nb00;
    Vec3d cl_nb0n;
    Vec3d cl_nbm0;
    Vec3d cl_nbmn;
    Vec3d cl_ncij;
    Vec3d cl_nbij;
    Vec3d cl_nci0;
    Vec3d cl_ncin;
#ifndef OSG_USE_NURBS_PATCH
    Vec3d cl_ndcx0;
    Vec3d cl_ndcxn;
    Vec3d cl_ndc0x;
    Vec3d cl_ndcmx;
    Vec3d cl_ndcix;
    Vec3d cl_ndcxj;
    Vec3d cl_nc0j;
    Vec3d cl_ncmj;
#endif
    Vec3f  cl_normal;
    Pnt3f  cl_position;
    double d_quadcurv = 0.0;

#ifdef OSG_USE_NURBS_PATCH
    pcl_surface->getParameterInterval_U(cl_min[0], cl_add[0]);
    pcl_surface->getParameterInterval_V(cl_min[1], cl_add[1]);
    cl_add -= cl_min;
 #ifdef OSG_ARBITRARY_SPLIT
    cl_worst = cl_min;
 #endif
#endif

    if(m_sbNormalApproximation)
    {
//#ifndef OSG_USE_NURBS_PATCH

        Vec3d du, dv;
        du[0] = crvvcl_cps[1][0][0];
        du[1] = crvvcl_cps[1][0][1];
        du[2] = crvvcl_cps[1][0][2];

        // we take the difference of two homogenious cps, but as the length of the cross product
        // is irrevelant (we're calculating normals) we ignore the weights.
        // In addition the weight of cp[1][0] might be zero so we avoid dividing by it (multiply is OK).
        du -= ccl_b00 * crvvcl_cps[1][0][3];

        dv[0]   = crvvcl_cps[0][1][0];
        dv[1]   = crvvcl_cps[0][1][1];
        dv[2]   = crvvcl_cps[0][1][2];
        dv     -= ccl_b00 * crvvcl_cps[0][1][3];
        cl_nb00 = du.cross(dv);

        du[0]   = crvvcl_cps[1][cui_n][0];
        du[1]   = crvvcl_cps[1][cui_n][1];
        du[2]   = crvvcl_cps[1][cui_n][2];
        du     -= ccl_b0n * crvvcl_cps[1][cui_n][3];
        dv[0]   = crvvcl_cps[0][cui_n - 1][0];
        dv[1]   = crvvcl_cps[0][cui_n - 1][1];
        dv[2]   = crvvcl_cps[0][cui_n - 1][2];
        dv     -= ccl_b0n * crvvcl_cps[0][cui_n - 1][3];
        cl_nb0n = du.cross(-dv);

        du[0]   = crvvcl_cps[cui_m - 1][0][0];
        du[1]   = crvvcl_cps[cui_m - 1][0][1];
        du[2]   = crvvcl_cps[cui_m - 1][0][2];
        du     -= ccl_bm0 * crvvcl_cps[cui_m - 1][0][3];
        dv[0]   = crvvcl_cps[cui_m][1][0];
        dv[1]   = crvvcl_cps[cui_m][1][1];
        dv[2]   = crvvcl_cps[cui_m][1][2];
        dv     -= ccl_bm0 * crvvcl_cps[cui_m][1][3];
        cl_nbm0 = -du.cross(dv);

        du[0]   = crvvcl_cps[cui_m - 1][cui_n][0];
        du[1]   = crvvcl_cps[cui_m - 1][cui_n][1];
        du[2]   = crvvcl_cps[cui_m - 1][cui_n][2];
        du     -= ccl_bmn * crvvcl_cps[cui_m - 1][cui_n][3];
        dv[0]   = crvvcl_cps[cui_m][cui_n - 1][0];
        dv[1]   = crvvcl_cps[cui_m][cui_n - 1][1];
        dv[2]   = crvvcl_cps[cui_m][cui_n - 1][2];
        dv     -= ccl_bmn * crvvcl_cps[cui_m][cui_n - 1][3];
        cl_nbmn = du.cross(dv);    // -du X -dv  => du X dv

/*
        cl_nb00 = ( crvvcl_cps[ 1 ][ 0 ] - crvvcl_cps[ 0 ][ 0 ] ).cross(
                    ( crvvcl_cps[ 0 ][ 1 ] - crvvcl_cps[ 0 ][ 0 ] ) );
        cl_nb0n = ( crvvcl_cps[ 1 ][ cui_n ] - crvvcl_cps[ 0 ][ cui_n ] ).cross(
                    ( crvvcl_cps[ 0 ][ cui_n ] - crvvcl_cps[ 0 ][ cui_n - 1 ] ) );
        cl_nbm0 = ( crvvcl_cps[ cui_m ][ 1 ] - crvvcl_cps[ cui_m ][ 0 ] ).cross(
                    ( crvvcl_cps[ cui_m - 1 ][ 0 ] - crvvcl_cps[ cui_m ][ 0 ] ) );
        cl_nbmn = ( crvvcl_cps[ cui_m ][ cui_n ] - crvvcl_cps[ cui_m - 1 ][ cui_n ] ).cross(
                    ( crvvcl_cps[ cui_m ][ cui_n ] - crvvcl_cps[ cui_m ][ cui_n - 1 ] ) );
*/
//		std::cerr << cl_nb00 << std::endl;
//		std::cerr << cl_nb0n << std::endl;
//		std::cerr << cl_nbm0 << std::endl;
//		std::cerr << cl_nbmn << std::endl << std::endl;
/*#else
        cl_uv = cl_min;
        cl_normal = pcl_surface->computeNormal( cl_uv, i_err, cl_position );
        cl_nb00[0] = cl_normal[ 0 ];
        cl_nb00[1] = cl_normal[ 1 ];
        cl_nb00[2] = cl_normal[ 2 ];

        cl_uv[1] += cl_add[1];
        cl_normal = pcl_surface->computeNormal( cl_uv, i_err, cl_position );
        cl_nb0n[0] = cl_normal[ 0 ];
        cl_nb0n[1] = cl_normal[ 1 ];
        cl_nb0n[2] = cl_normal[ 2 ];

        cl_uv[0] += cl_add[0];
        cl_normal = pcl_surface->computeNormal( cl_uv, i_err, cl_position );
        cl_nbmn[0] = cl_normal[ 0 ];
        cl_nbmn[1] = cl_normal[ 1 ];
        cl_nbmn[2] = cl_normal[ 2 ];

        cl_uv[1] = cl_min[1];
        cl_normal = pcl_surface->computeNormal( cl_uv, i_err, cl_position );
        cl_nbm0[0] = cl_normal[ 0 ];
        cl_nbm0[1] = cl_normal[ 1 ];
        cl_nbm0[2] = cl_normal[ 2 ];
//		std::cerr << cl_nb00 << std::endl;
//		std::cerr << cl_nb0n << std::endl;
//		std::cerr << cl_nbm0 << std::endl;
//		std::cerr << cl_nbmn << std::endl << std::endl;
#endif*/

        d_quad_size = cl_nb00.squareLength();
        if(d_quad_size > DCTP_EPS * DCTP_EPS)
        {
            cl_nb00 *= 1.0 / sqrt(d_quad_size);
        }
        d_quad_size = cl_nb0n.squareLength();
        if(d_quad_size > DCTP_EPS * DCTP_EPS)
        {
            cl_nb0n *= 1.0 / sqrt(d_quad_size);
        }
        d_quad_size = cl_nbm0.squareLength();
        if(d_quad_size > DCTP_EPS * DCTP_EPS)
        {
            cl_nbm0 *= 1.0 / sqrt(d_quad_size);
        }
        d_quad_size = cl_nbmn.squareLength();
        if(d_quad_size > DCTP_EPS * DCTP_EPS)
        {
            cl_nbmn *= 1.0 / sqrt(d_quad_size);
        }
        // AKOS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//		std::cerr << cl_nb00 << std::endl;
//		std::cerr << cl_nb0n << std::endl;
//		std::cerr << cl_nbm0 << std::endl;
//		std::cerr << cl_nbmn << std::endl << std::endl;

#ifndef OSG_USE_NURBS_PATCH
        cl_ndcx0 = (cl_nbm0 - cl_nb00) * cd_rm;
        cl_ndcxn = (cl_nbmn - cl_nb0n) * cd_rm;
        cl_ndc0x = (cl_nb0n - cl_nb00) * cd_rn;
        cl_ndcmx = (cl_nbmn - cl_nbm0) * cd_rn;
#endif

        if( (cl_nb00.squareLength() < DCTP_EPS * DCTP_EPS) ||
            (cl_nb0n.squareLength() < DCTP_EPS * DCTP_EPS) ||
            (cl_nbm0.squareLength() < DCTP_EPS * DCTP_EPS) ||
            (cl_nbmn.squareLength() < DCTP_EPS * DCTP_EPS) ||
            ((ccl_b00 - ccl_b0n).squareLength() < DCTP_EPS * DCTP_EPS) ||
            ((ccl_b0n - ccl_bmn).squareLength() < DCTP_EPS * DCTP_EPS) ||
            ((ccl_bmn - ccl_bm0).squareLength() < DCTP_EPS * DCTP_EPS) ||
            ((ccl_bm0 - ccl_b00).squareLength() < DCTP_EPS * DCTP_EPS))
        {
            d_quadcurv = 1e100;
        }
        else
        {
            d_quadcurv = osgMax(osgMax( (cl_nb00 - cl_nb0n).squareLength() / (ccl_b00 - ccl_b0n).squareLength(),
                                        (cl_nb0n - cl_nbmn).squareLength() / (ccl_b0n - ccl_bmn).squareLength() ),
                                osgMax( (cl_nbmn - cl_nbm0).squareLength() / (ccl_bmn - ccl_bm0).squareLength(),
                                        (cl_nbm0 - cl_nb00).squareLength() / (ccl_bm0 - ccl_b00).squareLength() ) );

//			d_quadcurv *= 4.0;	// 0.5 pixel geometric, 1 pixel shading error
        }

        if(d_quadcurv < 1e-4)
        {
//			std::cerr << d_quadcurv << std::endl;
            d_quadcurv = 1e-4;
        }
/*		else
        {
            std::cerr << d_quadcurv << std::endl;
        }*/
    }

#ifndef OSG_USE_NURBS_PATCH
    cl_ci0 = ccl_b00;
    cl_cin = ccl_b0n;
    if(m_sbNormalApproximation)
    {
        cl_nci0 = cl_nb00;
        cl_ncin = cl_nb0n;
    }
#endif

    for(ui_i = 0; ui_i <= cui_m; ++ui_i)
    {
#ifdef OSG_USE_NURBS_PATCH
//		cl_uv[0] += ( crvd_knot_u[ cui_dim_u + ui_i ] - crvd_knot_u[ ui_i ] ) / cui_dim_u;
        cl_uv[0] = 0.0;

        for(ui_idx = 0; ui_idx < cui_dim_u; ++ui_idx)
        {
            cl_uv[0] += crvd_knot_u[ui_idx + ui_i + 1];
        }

        cl_uv[0] /= cui_dim_u;

        const double cd_xrel = (cl_uv[0] - cl_min[0]) / cl_add[0];

        cl_ci0 = (ccl_bm0 - ccl_b00) * cd_xrel + ccl_b00;
        cl_cin = (ccl_bmn - ccl_b0n) * cd_xrel + ccl_b0n;
        if(m_sbNormalApproximation)
        {
            cl_nci0 = (cl_nbm0 - cl_nb00) * cd_xrel + cl_nb00;
            cl_ncin = (cl_nbmn - cl_nb0n) * cd_xrel + cl_nb0n;
        }
#else
        cl_cij = cl_ci0;
        cl_c0j = ccl_b00;
        cl_cmj = ccl_bm0;

        const Vec3d ccl_dcix = (cl_cin - cl_ci0) * cd_rn;

        if(m_sbNormalApproximation)
        {
            cl_ncij = cl_nci0;
            cl_nc0j = cl_nb00;
            cl_ncmj = cl_nbm0;

            cl_ndcix = (cl_ncin - cl_nci0) * cd_rn;
        }

        cl_uv[0] = ui_i * cd_rm;
#endif

        for(ui_j = 0; ui_j <= cui_n; ++ui_j)
        {
#ifdef OSG_USE_NURBS_PATCH
            cl_uv[1] = 0.0;

            for(ui_idx = 0; ui_idx < cui_dim_v; ++ui_idx)
            {
                cl_uv[1] += crvd_knot_v[ui_idx + ui_j + 1];
            }

            cl_uv[1] /= cui_dim_v;

            const double cd_yrel = (cl_uv[1] - cl_min[1]) / cl_add[1];

            cl_cij = cl_ci0 + (cl_cin - cl_ci0) * cd_yrel;
            if(m_sbNormalApproximation)
            {
                cl_ncij = cl_nci0 + (cl_ncin - cl_nci0) * cd_yrel;
            }
#else
            const Vec3d ccl_dcxj = cl_cmj - cl_c0j;

            if(m_sbNormalApproximation)
            {
                cl_ndcxj = cl_ncmj - cl_nc0j;
            }

            cl_uv[1] = ui_j * cd_rn;
#endif
#ifdef OSG_DIFF_TO_BILIN
 #ifdef OSG_USE_NURBS_PATCH
  #ifdef OSG_CONSERVATIVE_ERROR
            cl_bij = crvvcl_cps[ui_i][ui_j];
  #else
            if(m_sbNormalApproximation)
            {
                // TODO Vec3f f�r normale, Pnt3f f�r punkt
                cl_nbij     = pcl_surface->computeNormal(cl_uv, i_err, cl_bij);
                d_quad_size = cl_ncij.squareLength();
                if(d_quad_size > DCTP_EPS * DCTP_EPS)
                {
                    cl_norm = cl_ncij * (1.0 / sqrt(d_quad_size) );
                }
                else
                {
                    cl_norm = cl_nbij;
                }
//				std::cerr << cl_uv << cl_nbij << cl_norm << std::endl;
                cl_nbij -= cl_norm;
            }
            else
            {
                cl_bij = pcl_surface->compute(cl_uv, i_err);
            }
  #endif
 #else
  #ifdef OSG_CONSERVATIVE_ERROR
            cl_bij = crvvcl_cps[ui_i][ui_j];
  #else
            cl_bij = pcl_surface->computewdeCasteljau(cl_uv, i_err);
  #endif
 #endif
            if( (m_sbNormalApproximation) && (cl_nbij.squareLength() > DCTP_EPS * DCTP_EPS) )
            {
                // calculate shading error
                d_quad_size = cl_nbij.squareLength() / d_quadcurv;

 #ifdef OSG_EUCLID_ERRORS
                // for euclidian norm first calculate distance to next correcly shaded pixel
                d_quad_size += (cl_bij - cl_cij).squareLength();
 #endif

                // the corner points are correcly shaded pixels...
                d_quad_size = osgMin(d_quad_size, (cl_bij - ccl_b00).squareLength() );
                d_quad_size = osgMin(d_quad_size, (cl_bij - ccl_b0n).squareLength() );
                d_quad_size = osgMin(d_quad_size, (cl_bij - ccl_bm0).squareLength() );
                d_quad_size = osgMin(d_quad_size, (cl_bij - ccl_bmn).squareLength() );

 #ifdef OSG_EUCLID_ERRORS
                d_quad_size = sqrt(d_quad_size);
 #else
                // for maximum norm choose the maximum error
                d_quad_size = sqrt(osgMax( (cl_bij - cl_cij).squareLength(), d_quad_size) );
 #endif
            }
            else
            {
                d_quad_size = sqrt( (cl_bij - cl_cij).squareLength() );
            }
 #ifdef OSG_ARBITRARY_SPLIT
            if(osgAbs(d_quad_size - ptCell->ptErrorCell->fError) < DCTP_EPS)
            {
                double cd_old_x = osgMin(cl_worst[0] - cl_min[0], cl_min[0] + cl_add[0] - cl_worst[0]);
                double cd_old_y = osgMin(cl_worst[1] - cl_min[1], cl_min[1] + cl_add[1] - cl_worst[1]);
                double cd_new_x = osgMin(cl_uv[0] - cl_min[0], cl_min[0] + cl_add[0] - cl_uv[0]);
                double cd_new_y = osgMin(cl_uv[1] - cl_min[1], cl_min[1] + cl_add[1] - cl_uv[1]);
//				std::cerr << cd_old_x * cd_old_x + cd_old_y * cd_old_y << " " << cd_new_x * cd_new_x + cd_new_y * cd_new_y << std::endl;
                if(cd_old_x * cd_old_x + cd_old_y * cd_old_y <= cd_new_x * cd_new_x + cd_new_y * cd_new_y)
                {
                    cl_worst = cl_uv;
                }
                if(d_quad_size > ptCell->ptErrorCell->fError)
                {
                    ptCell->ptErrorCell->fError = float(d_quad_size);
                }
            }
            else
 #endif
            if(d_quad_size > ptCell->ptErrorCell->fError)
            {
                ptCell->ptErrorCell->fError = float(d_quad_size);
 #ifdef OSG_ARBITRARY_SPLIT
                cl_worst = cl_uv;
 #endif
            }
#else
 #ifdef OSG_CONSERVATIVE_ERROR
            cl_bij = crvvcl_cps[ui_i][ui_j];
 #else
  #ifdef OSG_USE_NURBS_PATCH
            cl_bij = pcl_surface->compute(cl_uv, i_err);
  #else
            cl_bij = pcl_surface->computewdeCasteljau(cl_uv, i_err);
  #endif
 #endif
            d_quad_size = osgMin(computeDistToTriangle(cl_bij, ccl_b00, ccl_b0n, ccl_bm0),
                                 computeDistToTriangle(cl_bij, ccl_bmn, ccl_b0n, ccl_bm0) );
//			std::cerr << d_quad_size << std::endl;
            if(d_quad_size > ptCell->ptErrorCell->fError)
            {
//				std::cerr << d_quad_size << std::endl;
                ptCell->ptErrorCell->fError = ( float ) d_quad_size;
            }
            d_quad_size = osgMin(computeDistToTriangle(cl_bij, ccl_b0n, ccl_b00, ccl_bmn),
                                 computeDistToTriangle(cl_bij, ccl_bm0, ccl_b00, ccl_bmn) );
//			std::cerr << d_quad_size << std::endl;
            if(d_quad_size > ptCell->ptErrorCell->fError)
            {
//				std::cerr << d_quad_size << std::endl;
                ptCell->ptErrorCell->fError = ( float ) d_quad_size;
            }
#endif
#ifndef OSG_USE_NURBS_PATCH
            cl_cij += ccl_dcix;
            cl_c0j += ccl_dc0x;
            cl_cmj += ccl_dcmx;
#endif
        }

#ifndef OSG_USE_NURBS_PATCH
        cl_ci0 += ccl_dcx0;
        cl_cin += ccl_dcxn;
#endif
    }

    // add twist vector error
#ifdef OSG_DIFF_TO_BILIN
 #ifdef OSG_CONSERVATIVE_ERROR
    ptCell->ptErrorCell->fError += ( float ) sqrt( (ccl_b00 - ccl_b0n + ccl_bmn - ccl_bm0).squareLength() ) * 0.25;
 #endif
#endif
//	ptCell->ptErrorCell->fError *= 0.1;
//	std::cerr << ptCell->ptErrorCell->fError << std::endl;
#ifdef OSG_USE_KD_TREE
 #ifdef OSG_ARBITRARY_SPLIT
//	std::cerr << cl_min << cl_add << cl_worst << std::endl;
    if( (osgAbs(cl_worst[0] - cl_min[0]) <= osgMax(DCTP_EPS, 1e-4 * cl_add[0]) ) ||
        (osgAbs(cl_worst[0] - (cl_min[0] + cl_add[0]) ) <= osgMax(DCTP_EPS, 1e-4 * cl_add[0]) ) )
    {
//		std::cerr << "y";
        if( (osgAbs(cl_worst[1] - cl_min[1]) <= osgMax(DCTP_EPS, 1e-4 * cl_add[1]) ) ||
            (osgAbs(cl_worst[1] - (cl_min[1] + cl_add[1]) ) <= osgMax(DCTP_EPS, 1e-4 * cl_add[1]) ) )
        {
            if(osgAbs(cl_add[0]) < osgAbs(cl_add[1]) )
            {
//				std::cerr << "my";
                ptCell->ptErrorCell->fSplitValue = 0.5;
            }
            else
            {
//				std::cerr << "mx";
                ptCell->ptErrorCell->fSplitValue = -0.5;
            }
        }
        else
        {
            ptCell->ptErrorCell->fSplitValue = (cl_worst[1] - cl_min[1]) / cl_add[1];
        }
    }
    else if( (osgAbs(cl_worst[1] - cl_min[1]) <= osgMax(DCTP_EPS, 1e-4 * cl_add[1]) ) ||
             (osgAbs(cl_worst[1] - (cl_min[1] + cl_add[1]) ) <= osgMax(DCTP_EPS, 1e-4 * cl_add[1]) ) )
    {
//		std::cerr << "x";
        ptCell->ptErrorCell->fSplitValue = -(cl_worst[0] - cl_min[0]) / cl_add[0];
    }
    else
    {
        double d_hdiff;
        double d_vdiff;

        cl_uv[0] = cl_worst[0];
        cl_uv[1] = cl_min[1];
        if(m_sbNormalApproximation)
        {
            cl_nci0   = pcl_surface->computeNormal(cl_uv, i_err, cl_ci0);
            cl_uv[1] += cl_add[1];
            cl_ncin   = pcl_surface->computeNormal(cl_uv, i_err, cl_cin);
            cl_uv[1]  = cl_worst[1];
            cl_ncij   = pcl_surface->computeNormal(cl_uv, i_err, cl_cij);

            cl_bij      = cl_ci0 + (cl_cin - cl_ci0) * ( (cl_worst[1] - cl_min[1]) / cl_add[1]);
            cl_nbij     = cl_nci0 + (cl_ncin - cl_nci0) * ( (cl_worst[1] - cl_min[1]) / cl_add[1]);
            d_quad_size = cl_nbij.squareLength();
            if(d_quad_size > DCTP_EPS * DCTP_EPS)
            {
                cl_nbij *= 1.0 / sqrt(d_quad_size);
            }
        }
        else
        {
            cl_ci0    = pcl_surface->compute(cl_uv, i_err);
            cl_uv[1] += cl_add[1];
            cl_cin    = pcl_surface->compute(cl_uv, i_err);
            cl_uv[1]  = cl_worst[1];
            cl_cij    = pcl_surface->compute(cl_uv, i_err);

            cl_bij = cl_ci0 + (cl_cin - cl_ci0) * ( (cl_worst[1] - cl_min[1]) / cl_add[1]);
        }

//		const double	cd_hdiff = computeDistToLine( cl_cij, cl_ci0, cl_cin );
//		const double	cd_hdiff = sqrt( ( cl_cij - cl_bij ).squareLength( ) );
        if( (m_sbNormalApproximation) && (cl_ncij.squareLength() > DCTP_EPS * DCTP_EPS) )
        {
            // calculate shading error
            d_hdiff = (cl_ncij - cl_nbij).squareLength() / d_quadcurv;

   #ifdef OSG_EUCLID_ERRORS
            // for euclidian norm first calculate distance to next correcly shaded pixel
            d_hdiff += (cl_cij - cl_bij).squareLength();
   #endif

            // the new corner points will be correcly shaded pixels...
//			d_hdiff = osgMin( d_hdiff, ( cl_cij - cl_ci0 ).squareLength( ) );
//			d_hdiff = osgMin( d_hdiff, ( cl_cij - cl_cin ).squareLength( ) );

   #ifdef OSG_EUCLID_ERRORS
            d_hdiff = sqrt(d_hdiff);
   #else
            // for maximum norm choose the maximum error
            d_hdiff = sqrt(osgMax( (cl_cij - cl_bij).squareLength(), d_hdiff) );
   #endif

/*   #ifdef OSG_EUCLID_ERRORS
            d_hdiff = sqrt( ( cl_cij - cl_bij ).squareLength( )
                      + ( cl_ncij - cl_nbij ).squareLength( ) / d_quadcurv );
   #else
            d_hdiff = sqrt( osgMax( ( cl_cij - cl_bij ).squareLength( ),
                            ( cl_ncij - cl_nbij ).squareLength( ) / d_quadcurv ) );
   #endif*/
            d_hdiff += sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.0001;
        }
        else
        {
            d_hdiff = sqrt( (cl_cij - cl_bij).squareLength() )
                      + sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.0001;
        }
//		const double	cd_hdiff = sqrt( ( cl_ci0 - cl_cin ).squareLength( ) );



/*		std::cerr.precision( 4 );
        if( m_sbNormalApproximation )
        {
            std::cerr << cl_ci0 << cl_cij << cl_cin << cl_nci0 << cl_ncij << cl_ncin << d_hdiff << std::endl;
        }
        else
        {
            std::cerr << cl_ci0 << cl_cij << cl_cin << d_hdiff << std::endl;
        }*/

        if(m_sbNormalApproximation)
        {
            cl_uv[0]  = cl_min[0];
            cl_nci0   = pcl_surface->computeNormal(cl_uv, i_err, cl_ci0);
            cl_uv[0] += cl_add[0];
            cl_ncin   = pcl_surface->computeNormal(cl_uv, i_err, cl_cin);

            cl_bij      = cl_ci0 + (cl_cin - cl_ci0) * ( (cl_worst[0] - cl_min[0]) / cl_add[0]);
            cl_nbij     = cl_nci0 + (cl_ncin - cl_nci0) * ( (cl_worst[0] - cl_min[0]) / cl_add[0]);
            d_quad_size = cl_nbij.squareLength();
            if(d_quad_size > DCTP_EPS * DCTP_EPS)
            {
                cl_nbij *= 1.0 / sqrt(d_quad_size);
            }
        }
        else
        {
            cl_uv[0]  = cl_min[0];
            cl_ci0    = pcl_surface->compute(cl_uv, i_err);
            cl_uv[0] += cl_add[0];
            cl_cin    = pcl_surface->compute(cl_uv, i_err);

            cl_bij = cl_ci0 + (cl_cin - cl_ci0) * ( (cl_worst[0] - cl_min[0]) / cl_add[0]);
        }

//		const double	cd_vdiff = computeDistToLine( cl_cij, cl_ci0, cl_cin );
//		const double	cd_vdiff = sqrt( ( cl_cij - cl_bij ).squareLength( ) );
        if( (m_sbNormalApproximation) && (cl_ncij.squareLength() > DCTP_EPS * DCTP_EPS) )
        {
            // calculate shading error
            d_vdiff = (cl_ncij - cl_nbij).squareLength() / d_quadcurv;

   #ifdef OSG_EUCLID_ERRORS
            // for euclidian norm first calculate distance to next correcly shaded pixel
            d_vdiff += (cl_cij - cl_bij).squareLength();
   #endif

            // the new corner points will be correcly shaded pixels...
//			d_vdiff = osgMin( d_vdiff, ( cl_cij - cl_ci0 ).squareLength( ) );
//			d_vdiff = osgMin( d_vdiff, ( cl_cij - cl_cin ).squareLength( ) );

   #ifdef OSG_EUCLID_ERRORS
            d_vdiff = sqrt(d_vdiff);
   #else
            // for maximum norm choose the maximum error
            d_vdiff = sqrt(osgMax( (cl_cij - cl_bij).squareLength(), d_vdiff) );
   #endif

/*   #ifdef OSG_EUCLID_ERRORS
            d_vdiff = sqrt( ( cl_cij - cl_bij ).squareLength( )
                            + ( cl_ncij - cl_nbij ).squareLength( ) / d_quadcurv );
   #else
            d_vdiff = sqrt( osgMax( ( cl_cij - cl_bij ).squareLength( ),
                                    ( cl_ncij - cl_nbij ).squareLength( ) / d_quadcurv ) );
   #endif*/
            d_vdiff += sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.0001;
        }
        else
        {
            d_vdiff = sqrt( (cl_cij - cl_bij).squareLength() )
                      + sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.0001;
        }
//		const double	cd_vdiff = sqrt( ( cl_ci0 - cl_cin ).squareLength( ) );

/*		if( m_sbNormalApproximation )
        {
            std::cerr << cl_ci0 << cl_cij << cl_cin << cl_nci0 << cl_ncij << cl_ncin << d_vdiff << std::endl;
        }
        else
        {
            std::cerr << cl_ci0 << cl_cij << cl_cin << d_vdiff << std::endl;
        }*/
//		std::cerr << cd_hdiff << " " << cd_vdiff << std::endl;
//		std::cerr << "--------------------" << std::endl;

        if(d_hdiff < d_vdiff)
        {
            ptCell->ptErrorCell->fSplitValue = -(cl_worst[0] - cl_min[0]) / cl_add[0];
        }
        else
        {
            ptCell->ptErrorCell->fSplitValue = (cl_worst[1] - cl_min[1]) / cl_add[1];
        }
    }
//	std::cerr << cl_min << cl_min + cl_add << std::endl;
//	std::cerr << ptCell->ptErrorCell->fSplitValue << std::endl;
 #else
    cl_uv[0]  = cl_min[0] + cl_add[0] * 0.5;
    cl_uv[1]  = cl_min[1];
    cl_ci0    = pcl_surface->compute(cl_uv, i_err);
    cl_uv[1] += cl_add[1];
    cl_cin    = pcl_surface->compute(cl_uv, i_err);
    cl_uv[1] -= cl_add[1] * 0.5;
    cl_cij    = pcl_surface->compute(cl_uv, i_err);

//	const double	cd_hdiff = computeDistToLine( cl_cij, cl_ci0, cl_cin );
//	const double	cd_hdiff = sqrt( ( cl_cij - ( cl_ci0 + cl_cin ) * 0.5 ).squareLength( ) );
//	const double	cd_hdiff = sqrt( ( cl_cij - cl_ci0 ).squareLength( ) ) + sqrt( ( cl_cij - cl_cin ).squareLength( ) );
    const double cd_hdiff = computeDistToLine(cl_cij, cl_ci0, cl_cin)
                            + sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.001;

//	std::cerr.precision( 4 );
//	std::cerr << cl_ci0 << cl_cij << cl_cin << cd_hdiff << std::endl;

    cl_uv[0]  = cl_min[0];
    cl_ci0    = pcl_surface->compute(cl_uv, i_err);
    cl_uv[0] += cl_add[0];
    cl_cin    = pcl_surface->compute(cl_uv, i_err);

//	const double	cd_vdiff = computeDistToLine( cl_cij, cl_ci0, cl_cin );
//	const double	cd_vdiff = sqrt( ( cl_cij - ( cl_ci0 + cl_cin ) * 0.5 ).squareLength( ) );
//	const double	cd_vdiff = sqrt( ( cl_cij - cl_ci0 ).squareLength( ) ) + sqrt( ( cl_cij - cl_cin ).squareLength( ) );
    const double cd_vdiff = computeDistToLine(cl_cij, cl_ci0, cl_cin)
                            + sqrt( (cl_ci0 - cl_cin).squareLength() ) * 0.001;

//	std::cerr << cl_ci0 << cl_cij << cl_cin << cd_vdiff << std::endl;
//	std::cerr << cd_hdiff << " " << cd_vdiff << std::endl;
//	std::cerr << "--------------------" << std::endl;

    ptCell->ptErrorCell->bSplitHoriz = (cd_hdiff < cd_vdiff);
 #endif
#endif

/*	const double cd_size = 0.5 * sqrt( osgMax( osgMax( osgMax( ( ccl_b00 - ccl_b0n ).squareLength( ),
                                                               ( ccl_b0n - ccl_bmn ).squareLength( ) ),
                                                       osgMax( ( ccl_bmn - ccl_bm0 ).squareLength( ),
                                                               ( ccl_bm0 - ccl_b00 ).squareLength( ) ) ),
                                               osgMax( ( ccl_b00 - ccl_bmn ).squareLength( ),
                                                       ( ccl_b0n - ccl_bm0 ).squareLength( ) ) ) );

    if( ( cd_size > DCTP_EPS ) &&
        ( ptCell->ptErrorCell->fError > cd_size ) )
    {
        // error can't be larger than the current face, except for a torus. ;-)
        ptCell->ptErrorCell->fError = cd_size;
    }*/
}


#ifndef OSG_USE_NURBS_PATCH
void CErrorQuadTree::ComputeBPTree(std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                                   const std::vector<double>                     * cpvdIntervalsU,
                                   const std::vector<double>                     * cpvdIntervalsV)
{
    m_ptBPRoot             = new SBPETreeCell;
    m_ptBPRoot->uiBottom   = 0;
    m_ptBPRoot->uiTop      = (*cpvdIntervalsV).size() - 2;
    m_ptBPRoot->uiLeft     = 0;
    m_ptBPRoot->uiRight    = (*cpvdIntervalsU).size() - 2;
    m_ptBPRoot->fPrevError = 1e+32;
    ComputeBPError(m_ptBPRoot, pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
    SubdivideBPTree(m_ptBPRoot, pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
}


void CErrorQuadTree::ComputeBPError(SBPETreeCell                                  * pclBPNode,
                                    std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                                    const std::vector<double>                     * cpvdIntervalsU,
                                    const std::vector<double>                     * cpvdIntervalsV)
{
    unsigned int         ui_u_surf;
    unsigned int         ui_v_surf;
    BezierTensorSurface *pcl_surface;
    Vec3d                cl_cij;
    Vec3d                cl_bij;
    double               d_quad_size;
    unsigned int         ui_i;
    unsigned int         ui_j;
    Vec3d                cl_ci0;
    Vec3d                cl_cin;
    Vec3d                cl_norm;
    Vec3d                cl_c0j;
    Vec3d                cl_cmj;
    int                  i_err;
    Vec2d                cl_uv;


//	std::cerr << pclBPNode->uiLeft << " - " << pclBPNode->uiRight << std::endl;
//	std::cerr << pclBPNode->uiBottom << " - " << pclBPNode->uiTop << std::endl;

//	std::cerr << ( *cpvdIntervalsU ).size( ) << " x " << ( *cpvdIntervalsV ).size( ) << std::endl;

    pclBPNode->fError = 0.0;

/*	if( ( pclBPNode->uiLeft == pclBPNode->uiRight ) &&
        ( pclBPNode->uiBottom == pclBPNode->uiTop ) )
    {
        return; // handled as single bezier patch
    }*/

    pcl_surface = &( (*pvvclPatches)[pclBPNode->uiLeft][pclBPNode->uiBottom]);
    const Vec3d ccl_a00 = pcl_surface->getControlPointMatrix()[0][0];

    pcl_surface = &( (*pvvclPatches)[pclBPNode->uiRight][pclBPNode->uiBottom]);
    const Vec3d ccl_s0n = pcl_surface->getControlPointMatrix()[0][pcl_surface->getControlPointMatrix()[0].size() - 1];
    const Vec3d ccl_a0n = ccl_s0n - ccl_a00;

    pcl_surface = &( (*pvvclPatches)[pclBPNode->uiLeft][pclBPNode->uiTop]);
    const Vec3d ccl_sm0 = pcl_surface->getControlPointMatrix()[pcl_surface->getControlPointMatrix().size() - 1][0];
    const Vec3d ccl_am0 = ccl_sm0 - ccl_a00;

    pcl_surface = &( (*pvvclPatches)[pclBPNode->uiRight][pclBPNode->uiTop]);
    const Vec3d ccl_smn = pcl_surface->getControlPointMatrix()[pcl_surface->getControlPointMatrix().size() - 1][pcl_surface->getControlPointMatrix()[0].size() - 1];
    const Vec3d ccl_amn = ccl_smn - ccl_am0 - ccl_a00;

    for(ui_v_surf = pclBPNode->uiBottom; ui_v_surf <= pclBPNode->uiTop; ++ui_v_surf)
    {
//		std::cerr << "v:" << ui_v_surf << std::endl;
        const double cd_mul_v  = ( (*cpvdIntervalsV)[ui_v_surf] - (*cpvdIntervalsV)[pclBPNode->uiBottom]) / ( (*cpvdIntervalsV)[pclBPNode->uiTop + 1] - (*cpvdIntervalsV)[pclBPNode->uiBottom]);
        const double cd_mul_vn = ( (*cpvdIntervalsV)[ui_v_surf + 1] - (*cpvdIntervalsV)[pclBPNode->uiBottom]) / ( (*cpvdIntervalsV)[pclBPNode->uiTop + 1] - (*cpvdIntervalsV)[pclBPNode->uiBottom]);

        for(ui_u_surf = pclBPNode->uiLeft; ui_u_surf <= pclBPNode->uiRight; ++ui_u_surf)
        {
//			std::cerr << "u:" << ui_u_surf << std::endl;
            pcl_surface = &( (*pvvclPatches)[ui_u_surf][ui_v_surf]);

            const std::vector<std::vector <Vec3d> > &crvvcl_cps = pcl_surface->getControlPointMatrix();
            const unsigned int                       cui_m      = crvvcl_cps.size() - 1;
            const unsigned int                       cui_n      = crvvcl_cps[0].size() - 1;
            const double                             cd_mul_u   = ( (*cpvdIntervalsU)[ui_u_surf] - (*cpvdIntervalsU)[pclBPNode->uiLeft]) / ( (*cpvdIntervalsU)[pclBPNode->uiRight + 1] - (*cpvdIntervalsU)[pclBPNode->uiLeft]);
            const double                             cd_mul_un  = ( (*cpvdIntervalsU)[ui_u_surf + 1] - (*cpvdIntervalsU)[pclBPNode->uiLeft]) / ( (*cpvdIntervalsU)[pclBPNode->uiRight + 1] - (*cpvdIntervalsU)[pclBPNode->uiLeft]);
            const Vec3d                              ccl_b00    = ccl_a00 + ccl_a0n * cd_mul_v + (ccl_am0 + ccl_amn * cd_mul_v) * cd_mul_u;
            const Vec3d                              ccl_b0n    = ccl_a00 + ccl_a0n * cd_mul_vn + (ccl_am0 + ccl_amn * cd_mul_vn) * cd_mul_u;
            const Vec3d                              ccl_bm0    = ccl_a00 + ccl_a0n * cd_mul_v + (ccl_am0 + ccl_amn * cd_mul_v) * cd_mul_un;
            const Vec3d                              ccl_bmn    = ccl_a00 + ccl_a0n * cd_mul_vn + (ccl_am0 + ccl_amn * cd_mul_vn) * cd_mul_un;
            const double                             cd_rn      = 1.0 / cui_n;
            const double                             cd_rm      = 1.0 / cui_m;
            const Vec3d                              ccl_dcx0   = (ccl_bm0 - ccl_b00) * cd_rm;
            const Vec3d                              ccl_dcxn   = (ccl_bmn - ccl_b0n) * cd_rm;
            const Vec3d                              ccl_dc0x   = (ccl_b0n - ccl_b00) * cd_rn;
            const Vec3d                              ccl_dcmx   = (ccl_bmn - ccl_bm0) * cd_rn;

//			std::cerr << cui_n << "," << cui_m << std::endl;
//			std::cerr << ( void* ) pclBPNode << std::endl;

            cl_ci0 = ccl_b00;
            cl_cin = ccl_b0n;

            for(ui_i = 0; ui_i <= cui_m; ++ui_i)
            {
                cl_cij = cl_ci0;
                cl_c0j = ccl_b00;
                cl_cmj = ccl_bm0;

                const Vec3d ccl_dcix = (cl_cin - cl_ci0) * cd_rn;

                cl_uv[0] = ui_i * cd_rm;

                for(ui_j = 0; ui_j <= cui_n; ++ui_j)
                {
                    const Vec3d ccl_dcxj = cl_cmj - cl_c0j;

                    cl_uv[1] = ui_j * cd_rn;
#ifdef OSG_DIFF_TO_BILIN
//					cl_bij = crvvcl_cps[ ui_i ][ ui_j ] - cl_cij;
                    cl_bij = pcl_surface->computewdeCasteljau(cl_uv, i_err) - cl_cij;
//					std::cerr << ccl_dcix << "x" << ccl_dcxj << std::endl;
/*					cl_norm = ccl_dcix.cross( ccl_dcxj );
                    d_quad_size = cl_norm.squareLength( );
                    if( d_quad_size > 0.0 )
                    {
//						std::cerr << "qs:" << d_quad_size << std::endl;
                        cl_norm *= 1.0 / sqrt( d_quad_size );
                        d_quad_size = osgAbs( cl_bij.dot( cl_norm ) );
                        if( d_quad_size > pclBPNode->fError )
                        {
                            pclBPNode->fError = ( float ) d_quad_size;
                        }
                    }
                    else*/
                    {
                        d_quad_size = sqrt(cl_bij.squareLength() );
//						std::cerr << "qs:" << d_quad_size << std::endl;
                        if(d_quad_size > pclBPNode->fError)
                        {
                            pclBPNode->fError = ( float ) d_quad_size;
                        }
                    }
#else
//					std::cerr << cl_uv << std::endl;
                    cl_bij = pcl_surface->computewdeCasteljau(cl_uv, i_err);
//					std::cerr << i_err << std::endl;
                    if(cl_uv[0] + cl_uv[1] <= 1.0)
                    {
                        d_quad_size = computeDistToTriangle(cl_bij, ccl_a00, ccl_s0n, ccl_sm0);
                    }
                    else
                    {
                        d_quad_size = computeDistToTriangle(cl_bij, ccl_smn, ccl_s0n, ccl_sm0);
                    }
//					d_quad_size = osgMin( computeDistToTriangle( cl_bij, ccl_a00, ccl_s0n, ccl_sm0 ),
//									   computeDistToTriangle( cl_bij, ccl_smn, ccl_s0n, ccl_sm0 ) );
                    if(d_quad_size > pclBPNode->fError)
                    {
                        pclBPNode->fError = ( float ) d_quad_size;
                    }
                    if(cl_uv[0] <= cl_uv[1])
                    {
                        d_quad_size = computeDistToTriangle(cl_bij, ccl_s0n, ccl_a00, ccl_smn);
                    }
                    else
                    {
                        d_quad_size = computeDistToTriangle(cl_bij, ccl_sm0, ccl_a00, ccl_smn);
                    }
//					d_quad_size = osgMin( computeDistToTriangle( cl_bij, ccl_s0n, ccl_a00, ccl_smn ),
//									   computeDistToTriangle( cl_bij, ccl_sm0, ccl_a00, ccl_smn ) );
                    if(d_quad_size > pclBPNode->fError)
                    {
                        pclBPNode->fError = ( float ) d_quad_size;
                    }
//					std::cerr << ccl_a00 << ccl_a0n << ccl_am0 << ccl_amn << std::endl << std::endl;
#endif
                    cl_cij += ccl_dcix;
                    cl_c0j += ccl_dc0x;
                    cl_cmj += ccl_dcmx;
                }

                cl_ci0 += ccl_dcx0;
                cl_cin += ccl_dcxn;
            }
        }
    }

    // add twist vector error
#ifdef OSG_DIFF_TO_BILIN
//	pclBPNode->fError += ( float ) sqrt( ( ccl_amn - ccl_a0n ).squareLength( ) ) * 0.25;
#endif
//	pclBPNode->fError *= 0.1;
//	pcl_node->ptErrorCell->fError = 0.0;
}


void CErrorQuadTree::SubdivideBPTree(SBPETreeCell                                  * pclBPNode,
                                     std::vector<std::vector<BezierTensorSurface> > *pvvclPatches,
                                     const std::vector<double>                     * cpvdIntervalsU,
                                     const std::vector<double>                     * cpvdIntervalsV)
{
    unsigned int ui_diff;

    ui_diff = 1;
    while( (ui_diff <= pclBPNode->uiRight - pclBPNode->uiLeft) ||
           (ui_diff <= pclBPNode->uiTop - pclBPNode->uiBottom) )
    {
        ui_diff = (ui_diff << 1);
    }
    ui_diff = ( (ui_diff - 1) >> 1);

/*	std::cerr << "subdivide:" << std::endl;
    std::cerr << pclBPNode->uiLeft << ", " << pclBPNode->uiRight << std::endl;
    std::cerr << pclBPNode->uiBottom << ", " << pclBPNode->uiTop << std::endl;
    std::cerr << ui_diff << std::endl;*/

    if(pclBPNode->uiBottom + ui_diff < pclBPNode->uiTop)
    {
        if(pclBPNode->uiLeft + ui_diff < pclBPNode->uiRight)
        {
            // xx
            // xx
            pclBPNode->aptChildren[3]             = new SBPETreeCell;
            pclBPNode->aptChildren[3]->uiBottom   = pclBPNode->uiBottom;
            pclBPNode->aptChildren[3]->uiTop      = pclBPNode->uiBottom + ui_diff;
            pclBPNode->aptChildren[3]->uiLeft     = pclBPNode->uiLeft;
            pclBPNode->aptChildren[3]->uiRight    = pclBPNode->uiLeft + ui_diff;
            pclBPNode->aptChildren[3]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            pclBPNode->aptChildren[2]             = new SBPETreeCell;
            pclBPNode->aptChildren[2]->uiBottom   = pclBPNode->uiBottom;
            pclBPNode->aptChildren[2]->uiTop      = pclBPNode->aptChildren[3]->uiTop;
            pclBPNode->aptChildren[2]->uiLeft     = pclBPNode->aptChildren[3]->uiRight + 1;
            pclBPNode->aptChildren[2]->uiRight    = pclBPNode->uiRight;
            pclBPNode->aptChildren[2]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            pclBPNode->aptChildren[0]             = new SBPETreeCell;
            pclBPNode->aptChildren[0]->uiBottom   = pclBPNode->aptChildren[3]->uiTop + 1;
            pclBPNode->aptChildren[0]->uiTop      = pclBPNode->uiTop;
            pclBPNode->aptChildren[0]->uiLeft     = pclBPNode->uiLeft;
            pclBPNode->aptChildren[0]->uiRight    = pclBPNode->aptChildren[3]->uiRight;
            pclBPNode->aptChildren[0]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            pclBPNode->aptChildren[1]             = new SBPETreeCell;
            pclBPNode->aptChildren[1]->uiBottom   = pclBPNode->aptChildren[0]->uiBottom;
            pclBPNode->aptChildren[1]->uiTop      = pclBPNode->uiTop;
            pclBPNode->aptChildren[1]->uiLeft     = pclBPNode->aptChildren[2]->uiLeft;
            pclBPNode->aptChildren[1]->uiRight    = pclBPNode->uiRight;
            pclBPNode->aptChildren[1]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            ComputeBPError(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            ComputeBPError(pclBPNode->aptChildren[2], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            ComputeBPError(pclBPNode->aptChildren[0], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            ComputeBPError(pclBPNode->aptChildren[1], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[2], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[0], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[1], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
        }
        else
        {
            // x
            // x
            pclBPNode->aptChildren[3]             = new SBPETreeCell;
            pclBPNode->aptChildren[3]->uiBottom   = pclBPNode->uiBottom;
            pclBPNode->aptChildren[3]->uiTop      = pclBPNode->uiBottom + ui_diff;
            pclBPNode->aptChildren[3]->uiLeft     = pclBPNode->uiLeft;
            pclBPNode->aptChildren[3]->uiRight    = pclBPNode->uiRight;
            pclBPNode->aptChildren[3]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            pclBPNode->aptChildren[2]             = NULL;
            pclBPNode->aptChildren[0]             = new SBPETreeCell;
            pclBPNode->aptChildren[0]->uiBottom   = pclBPNode->aptChildren[3]->uiTop + 1;
            pclBPNode->aptChildren[0]->uiTop      = pclBPNode->uiTop;
            pclBPNode->aptChildren[0]->uiLeft     = pclBPNode->uiLeft;
            pclBPNode->aptChildren[0]->uiRight    = pclBPNode->uiRight;
            pclBPNode->aptChildren[0]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
            pclBPNode->aptChildren[1]             = NULL;
            ComputeBPError(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            ComputeBPError(pclBPNode->aptChildren[0], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
            SubdivideBPTree(pclBPNode->aptChildren[0], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
        }
    }
    else if(pclBPNode->uiLeft + ui_diff < pclBPNode->uiRight)
    {
        // xx
        pclBPNode->aptChildren[3]             = new SBPETreeCell;
        pclBPNode->aptChildren[3]->uiBottom   = pclBPNode->uiBottom;
        pclBPNode->aptChildren[3]->uiTop      = pclBPNode->uiTop;
        pclBPNode->aptChildren[3]->uiLeft     = pclBPNode->uiLeft;
        pclBPNode->aptChildren[3]->uiRight    = pclBPNode->uiLeft + ui_diff;
        pclBPNode->aptChildren[3]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
        pclBPNode->aptChildren[2]             = new SBPETreeCell;
        pclBPNode->aptChildren[2]->uiBottom   = pclBPNode->uiBottom;
        pclBPNode->aptChildren[2]->uiTop      = pclBPNode->uiTop;
        pclBPNode->aptChildren[2]->uiLeft     = pclBPNode->aptChildren[3]->uiRight + 1;
        pclBPNode->aptChildren[2]->uiRight    = pclBPNode->uiRight;
        pclBPNode->aptChildren[2]->fPrevError = osgMin(pclBPNode->fError, pclBPNode->fPrevError);
        pclBPNode->aptChildren[0]             = NULL;
        pclBPNode->aptChildren[1]             = NULL;
        ComputeBPError(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
        ComputeBPError(pclBPNode->aptChildren[2], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
        SubdivideBPTree(pclBPNode->aptChildren[3], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
        SubdivideBPTree(pclBPNode->aptChildren[2], pvvclPatches, cpvdIntervalsU, cpvdIntervalsV);
    }
    else
    {
        pclBPNode->aptChildren[0] = NULL;
        pclBPNode->aptChildren[1] = NULL;
        pclBPNode->aptChildren[2] = NULL;
        pclBPNode->aptChildren[3] = NULL;
    }
}


void CErrorQuadTree::DeleteBPNode(SBPETreeCell *&rpclNode)
{
    if(rpclNode->aptChildren[0])
    {
        DeleteBPNode(rpclNode->aptChildren[0]);
    }
    if(rpclNode->aptChildren[1])
    {
        DeleteBPNode(rpclNode->aptChildren[1]);
    }
    if(rpclNode->aptChildren[2])
    {
        DeleteBPNode(rpclNode->aptChildren[2]);
    }
    if(rpclNode->aptChildren[3])
    {
        DeleteBPNode(rpclNode->aptChildren[3]);
    }
    delete rpclNode;
    rpclNode = NULL;
}
#endif


#ifndef OSG_DIFF_TO_BILIN
double CErrorQuadTree::computeDistToPlane(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2, const Vec3d cclV3)
{
    Vec3d  cl_norm;
    double d_quad_size;
    Vec3d  cl_diff;

    cl_diff     = cclP - cclV1;
    cl_norm     = (cclV2 - cclV1).cross(cclV3 - cclV1);
    d_quad_size = cl_norm.squareLength();
//	std::cerr << cclP << cclV1 << cclV2 << cclV3 << std::endl;
    if(d_quad_size > 0.0)
    {
//		std::cerr << "qs:" << d_quad_size << std::endl;
        cl_norm *= 1.0 / sqrt(d_quad_size);
//		std::cerr << cl_diff << cl_norm << std::endl;
        return osgAbs(cl_diff.dot(cl_norm) );
    }
    else
    {
//		std::cerr << cl_diff << std::endl;
        return sqrt(cl_diff.squareLength() );
    }
}


double CErrorQuadTree::computeDistToTriangle(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2, const Vec3d cclV3)
{
    Vec3d       cl_norm;
    double      d_dist;
    Vec3d       cl_diff;
    Vec3d       cl_proj;
    double      d_temp;
    double      d_temp2;
    const Vec3d ccl_d1 = cclV2 - cclV1;
    const Vec3d ccl_d2 = cclV3 - cclV1;

    cl_diff = cclP - cclV1;
    cl_norm = ccl_d1.cross(ccl_d2);
    d_temp  = cl_norm.squareLength();
    if(d_temp > 0.0)
    {
        cl_norm *= 1.0 / sqrt(d_temp);
        // project point to triangle plane
        d_dist  = cl_diff.dot(cl_norm);
        cl_proj = cclP - cl_norm * d_dist;
//		std::cerr << ( cl_proj - cclV1 ).dot( cl_norm ) << std::endl;
        // check if point is inside triangle
        cl_diff = cl_proj - cclV1;
        d_temp  = ccl_d1.dot(cl_diff) / ccl_d1.squareLength();
        d_temp2 = ccl_d2.dot(cl_diff) / ccl_d2.squareLength();
        if( (d_temp < 0.0) || (d_temp2 < 0.0) || (d_temp + d_temp2 > 1.0) )
        {
//			std::cerr << d_temp << " " << d_temp2 << ": " << osgAbs( d_dist );
            d_dist = computeDistToLine(cclP, cclV1, cclV2);
            d_temp = computeDistToLine(cclP, cclV1, cclV3);
            if(d_temp < d_dist)
                d_dist = d_temp;
            d_temp = computeDistToLine(cclP, cclV2, cclV3);
            if(d_temp < d_dist)
                d_dist = d_temp;
//			std::cerr << " -> " << d_dist << std::endl;
        }
        return osgAbs(d_dist);
    }
    else
    {
        return sqrt(cl_diff.squareLength() );
    }
}
#endif

double CErrorQuadTree::computeDistToLine(const Vec3d cclP, const Vec3d cclV1, const Vec3d cclV2)
{
    const Vec3d ccl_d    = cclV2 - cclV1;
    const Vec3d ccl_diff = cclP - cclV1;
    double      d_temp;
    double      d_temp2;

    d_temp = ccl_d.dot(ccl_diff);
    if(d_temp <= 0.0)
    {
//		std::cerr << "a " << sqrt( ccl_diff.squareLength( ) ) << std::endl;
        return sqrt(ccl_diff.squareLength() );
    }
    d_temp2 = ccl_d.squareLength();
    if(d_temp2 <= d_temp)
    {
//		std::cerr << "b " << sqrt( ( cclP - cclV2 ).squareLength( ) ) << std::endl;
        return sqrt( (cclP - cclV2).squareLength() );
    }
//	std::cerr << "c " << sqrt( ( ccl_d * ( d_temp / d_temp2 ) - ccl_diff ).squareLength( ) ) << std::endl;
    return sqrt( (ccl_d * (d_temp / d_temp2) - ccl_diff).squareLength() );
}

void CErrorQuadTree::WriteTree(std::ostream &rclFile)
{
#ifdef OSG_ARBITRARY_SPLIT
    SErrorTreeCell              *pt_act;
    std::vector<SErrorTreeCell*> vpt_stack;

    // store max error
    rclFile << m_fMaxError << std::endl;

    // store error cells
    vpt_stack.push_back(m_ptRoot);
    while(vpt_stack.size() )
    {
        pt_act = vpt_stack[vpt_stack.size() - 1];
        vpt_stack.pop_back();
        rclFile << pt_act->fError << " " << pt_act->fSplitValue << " ";
        rclFile << ( (pt_act->ptChildren != NULL) ? true : false) << std::endl;
        if(pt_act->ptChildren != NULL)
        {
            vpt_stack.push_back(&(pt_act->ptChildren[1]) );
            vpt_stack.push_back(&(pt_act->ptChildren[0]) );
        }
    }
#endif
}

void CErrorQuadTree::ReadTree(std::istream &rclFile)
{
#ifdef OSG_ARBITRARY_SPLIT
    SErrorTreeCell              *pt_act;
    std::vector<SErrorTreeCell*> vpt_stack;
    bool                         b_has_children;

    // load max error
    rclFile >> m_fMaxError >> std::ws;

    // load error cells
    m_ptRoot = new SErrorTreeCell;
    vpt_stack.push_back(m_ptRoot);
    while(vpt_stack.size() )
    {
        pt_act = vpt_stack[vpt_stack.size() - 1];
        vpt_stack.pop_back();
        rclFile >> pt_act->fError >> std::ws >> pt_act->fSplitValue >> std::ws;
        rclFile >> b_has_children >> std::ws;
        if(b_has_children)
        {
            pt_act->ptChildren = new SErrorTreeCell[2];
            vpt_stack.push_back(&(pt_act->ptChildren[1]) );
            vpt_stack.push_back(&(pt_act->ptChildren[0]) );
        }
        else
        {
            pt_act->ptChildren = NULL;
        }
    }
#endif
}
