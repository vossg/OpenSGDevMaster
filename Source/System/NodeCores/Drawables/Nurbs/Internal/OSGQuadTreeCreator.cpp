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
#include "OSGQuadTreeCreator.h"
#include <stdio.h>

OSG_USING_NAMESPACE

#ifdef WIN32
#pragma warning (disable : 985)
#endif

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

double QuadTreeCreator::
computeApproximationError(DCTPFace *f)
{
//the approximate error comes from to error,
//I: interpolation with a bilinear surface
//II: interpolating this bilinear surface with two triangles

//first gotta get needed controlpoints from the index-ed quadtreeleaf
    BezierTensorSurface *btsp =
        static_cast<BezierTensorSurface*>(f->faceinfo);

    const DCTPVec4dmatrix &          cps = btsp->getControlPointMatrix();
    const DCTPVec4dmatrix::size_type m   = cps.size() - 1;
    //size of control point matrix in x direction
    const DCTPVec4dvector::size_type n = cps[0].size() - 1;
    //size of cpm. in y direction
    Vec3d b00;
    Vec3d b0n;
    Vec3d bm0;
    Vec3d bmn;
    b00[0] = cps[0][0][0] / cps[0][0][3];
    b00[1] = cps[0][0][1] / cps[0][0][3];
    b00[2] = cps[0][0][2] / cps[0][0][3];
    b0n[0] = (cps[0][n][0] / cps[0][n][3]);
    b0n[1] = (cps[0][n][1] / cps[0][n][3]);
    b0n[2] = (cps[0][n][2] / cps[0][n][3]);
    bm0[0] = (cps[m][0][0] / cps[m][0][3]);
    bm0[1] = (cps[m][0][1] / cps[m][0][3]);
    bm0[2] = (cps[m][0][2] / cps[m][0][3]);
    bmn[0] = (cps[m][n][0] / cps[m][n][3]);
    bmn[1] = (cps[m][n][1] / cps[m][n][3]);
    bmn[2] = (cps[m][n][2] / cps[m][n][3]);
    //now computin' I. error:
    //we hafta decide a maxmimum value:
    double                     max_quad = -1.0;
    Vec3d                      cij, bij;
    double                     quad_size;
    DCTPVec3dmatrix::size_type i;
    DCTPVec3dvector::size_type j;
    const double               rn = 1.0 / n;
    const double               rm = 1.0 / m;

    Vec3d       ci0 = b00;
    Vec3d       cin = b0n;
    const Vec3d dc0 = (bm0 - b00) * rm;
    const Vec3d dcn = (bmn - b0n) * rm;
//	Vec2d cl_uv;
//	int i_err = 0;

//	if( m_bForTrimming )
    {
//		cl_uv[0] = 0.0;
        for(i = 0; i <= m; ++i)
        {
//			cl_uv[1] = 0.0;
            cij = ci0;
            const Vec3d dci = (cin - ci0) * rn;

            for(j = 0; j <= n; ++j)
            {
                if(cps[i][j][3] < DCTP_EPS)
                {
                    // the weight is zero so we return a practically
                    // infinite error enforcing a subdivision of the patch
                    quad_size = 1.0e300;
                }
                else
                {
                    bij[0] = (cps[i][j][0] / cps[i][j][3]) - cij[0];
                    bij[1] = (cps[i][j][1] / cps[i][j][3]) - cij[1];
                    bij[2] = (cps[i][j][2] / cps[i][j][3]) - cij[2];
//				bij = btsp->computewdeCasteljau( cl_uv, i_err ) - cij;
                    quad_size = bij.squareLength();
                }
                if(quad_size > max_quad)
                    max_quad = quad_size;
                cij += dci;
//				cl_uv[1] += rn;
            } //end for

            ci0 += dc0;
            cin += dcn;
//			cl_uv[0] += rm;
        }

        const double error_I = sqrt(max_quad);

        //now get error2
        const Vec3d  linerr_vect = (b00 - b0n + bmn - bm0);
        const double error_II    = sqrt(linerr_vect.squareLength() ) * 0.25;
        //now the error iz the sum o' I and II:
        return error_I + error_II;
    }
/*	else
    {
        Vec3d		cl_norm;
        const Vec3d cdc0 = ( b0n - b00 ) * rn;
        const Vec3d cdcm = ( bmn - bm0 ) * rn;
        Vec3d		c0j;
        Vec3d		cmj;

        for( i = 0; i <= m; ++i )
        {
            cij = ci0;
            c0j = b00;
            cmj = bm0;

            const Vec3d dci = ( cin - ci0 ) * rn;

//			std::cerr << dci << std::endl;

            for( j = 0; j <= n; ++j )
            {
                const Vec3d	dcj = cmj - c0j;

                bij = cps[ i ][ j ] - cij;
                cl_norm = dci.cross( dcj );
//				std::cerr << dci << " x " << dcj << std::endl;
//				std::cerr << cl_norm << "," << bij << std::endl;
                quad_size = cl_norm.squareLength( );
                if( quad_size > 0.0 )
                {
                    cl_norm *= 1.0 / sqrt( quad_size );
                    quad_size = osgabs( bij.dot( cl_norm ) );
//					quad_size = bij.squareLength();
                    if ( quad_size > max_quad ) max_quad = quad_size;
                }
                cij += dci;
                c0j += cdc0;
                cmj += cdcm;
            } //end for
            ci0 += dc0;
            cin += dcn;
        }
//		std::cerr << max_quad << std::endl;
        return max_quad;
    }*/
}


int QuadTreeCreator::setInitialLeaves(
    const beziersurfacematrix& patches,
    const DCTPdvector&         intervals_u,
    const DCTPdvector&         intervals_v)
{
//sets up the basic leaves array of the quadtree
//FIXME: no size & sanity checks made to input, they may be wrong
    beziersurfacematrix::size_type u_size = patches.size();
    beziersurfacevector::size_type v_size = patches[0].size();
    Vec3d                          a,b,c,d;

    for(beziersurfacematrix::size_type u = 0; u < u_size; ++u)
    {
        for(beziersurfacevector::size_type v = 0; v < v_size; ++v)
        {
            a[0] = intervals_u[u]; a[1] = intervals_v[v + 1]; a[2] = 0.0;
            b[0] = intervals_u[u + 1]; b[1] = intervals_v[v + 1]; b[2] = 0.0;
            c[0] = intervals_u[u + 1]; c[1] = intervals_v[v]; c[2] = 0.0;
            d[0] = intervals_u[u]; d[1] = intervals_v[v]; d[2] = 0.0;

//			std::cerr << a << b << c << d << std::endl;

            DCTPFace *face = qtm->AddQuad(a, b, c, d, 0.0);
            face->faceinfo = new BezierTensorSurface;
#ifdef OSG_ADAPTIVE_QUAD_TREE
            face->norm = -1.0;
#endif
            *(static_cast<BezierTensorSurface*>(face->faceinfo)) = patches[u][v];
            BezierTensorSurface temp_surface = patches[u][v];
        } //end inner for

    }

    return 0;
}

int QuadTreeCreator::finishSubdivisions(DCTPFace *f)
{
/*        BezierTensorSurface *btsp = (BezierTensorSurface*)f->faceinfo;
        beziersurfacematrix created_surfaces( 0 );
        if ( btsp->midPointSubDivision( created_surfaces ) ) {
                std::cerr << "QuadTreeCreator::finisSubdivisions:" <<
                        "Cannot midpointsubdivide BezierSurf'!" << std::endl;
                return -1;
        }
        dctpfacevector::size_type idx = qtm->faces.size() - 3;
        (qtm->faces[ idx ])->faceinfo = new BezierTensorSurface;
        *((BezierTensorSurface*)(qtm->faces[ idx++ ])->faceinfo) =
                created_surfaces[ 1 ][ 1 ];
        (qtm->faces[ idx ])->faceinfo = new BezierTensorSurface;
        *((BezierTensorSurface*)(qtm->faces[ idx++ ])->faceinfo) =
                created_surfaces[ 1 ][ 0 ];
        (qtm->faces[ idx ])->faceinfo = new BezierTensorSurface;
        *((BezierTensorSurface*)(qtm->faces[ idx++ ])->faceinfo) =
                created_surfaces[ 0 ][ 0 ];

        delete btsp;
        f->faceinfo = new BezierTensorSurface;
        *((BezierTensorSurface*)f->faceinfo) = created_surfaces[ 0 ][ 1 ];
        return 0;*/

    BezierTensorSurface *btsp = static_cast<BezierTensorSurface*>(f->faceinfo);
    beziersurfacevector  created_surfaces;
    if(btsp->midPointSubDivision(created_surfaces) )
    {
        std::cerr << "QuadTreeCreator::finisSubdivisions:" <<
        "Cannot midpointsubdivide BezierSurf'!" << std::endl;
        return -1;
    }
    dctpfacevector::size_type idx = qtm->faces.size() - 3;

    (qtm->faces[idx])->faceinfo                                         = new BezierTensorSurface;
    *(static_cast<BezierTensorSurface*>((qtm->faces[idx++])->faceinfo)) =
        created_surfaces[2];

/*		std::cerr << std::endl;
        std::cerr << ( qtm->faces[ idx ] )->orig_face[ 0 ]->coords << std::endl;
        std::cerr << ( qtm->faces[ idx ] )->orig_face[ 1 ]->coords << std::endl;
        std::cerr << ( qtm->faces[ idx ] )->orig_face[ 2 ]->coords << std::endl;
        std::cerr << ( qtm->faces[ idx ] )->orig_face[ 3 ]->coords << std::endl;
        std::cerr << created_surfaces[ 1 ].getControlPointMatrix( )[ 0 ][ 0 ] << std::endl;*/

    (qtm->faces[idx])->faceinfo                                         = new BezierTensorSurface;
    *(static_cast<BezierTensorSurface*>((qtm->faces[idx++])->faceinfo)) =
        created_surfaces[1];

    (qtm->faces[idx])->faceinfo = btsp;

    f->faceinfo                                       = new BezierTensorSurface;
    *(static_cast<BezierTensorSurface*>(f->faceinfo)) = created_surfaces[0];
    return 0;
}


int QuadTreeCreator::createQuadTree(void)
{
//now this is the essentials of this whole class
//all other are 'eye-candys'

    for(dctpfacevector::size_type f = 0;
        f < qtm->faces.size(); ++f)
    {
        DCTPFace *face = qtm->faces[f];
        while(computeApproximationError(face) > error_epsilon)
        {
            qtm->SubdivideQuad(face);
            if(finishSubdivisions(face) )
                return -1;
        }
        face->norm = error_epsilon / computeBilinearNorm(face);
    }

    return 0;     //all OK, whew...
}

double QuadTreeCreator::computeBilinearNorm(DCTPFace *face)
{
    BezierTensorSurface *btsp =
        static_cast<BezierTensorSurface*>(face->faceinfo);
    DCTPVec4dmatrix&           cps = btsp->getControlPointMatrix();
    DCTPVec4dmatrix::size_type m   = cps.size() - 1;
    DCTPVec4dvector::size_type n   = cps[0].size() - 1;
    Vec3d                      b00;
    Vec3d                      b0n;
    Vec3d                      bm0;
    Vec3d                      bmn;
    b00[0] = cps[0][0][0] / cps[0][0][3];
    b00[1] = cps[0][0][1] / cps[0][0][3];
    b00[2] = cps[0][0][2] / cps[0][0][3];
    b0n[0] = (cps[0][n][0] / cps[0][n][3]) - b00[0];
    b0n[1] = (cps[0][n][1] / cps[0][n][3]) - b00[1];
    b0n[2] = (cps[0][n][2] / cps[0][n][3]) - b00[2];
    bm0[0] = (cps[m][0][0] / cps[m][0][3]) - b00[0];
    bm0[1] = (cps[m][0][1] / cps[m][0][3]) - b00[1];
    bm0[2] = (cps[m][0][2] / cps[m][0][3]) - b00[2];
    bmn[0] = (cps[m][n][0] / cps[m][n][3]) - b00[0];
    bmn[1] = (cps[m][n][1] / cps[m][n][3]) - b00[1];
    bmn[2] = (cps[m][n][2] / cps[m][n][3]) - b00[2];
    double tmp1,tmp2;
    tmp1 = sqrt(b0n.squareLength() );
    tmp2 = sqrt(bm0.squareLength() );
    if(tmp1 < tmp2)
        tmp1 = tmp2;
    tmp2 = sqrt(bmn.squareLength() ) / sqrt(2.f);        //1.414213; //divided by length
    if(tmp1 < tmp2)
        return tmp2;
    else
        return tmp1;
}

void QuadTreeCreator::resetMesh(void)
{
    dctpfacevector::iterator fe = qtm->faces.end();

    for(dctpfacevector::iterator f = qtm->faces.begin(); f != fe; ++f)
        delete static_cast<BezierTensorSurface*>((*f)->faceinfo);

    qtm->reinit();
}
