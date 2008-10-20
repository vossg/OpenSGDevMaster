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
#ifdef WIN32
#   pragma warning (disable : 985)
#endif
#include "OSGBezierTensorSurface.h"

OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif


//setup functions
int BezierTensorSurface::setControlPointMatrix(const DCTPVec4dmatrix& cps)
{
    DCTPVec4dmatrix::size_type u_size = cps.size();
    if(u_size < 2)
        return -1;             //invalid, at least two row of points are required
    DCTPVec4dvector::size_type v_size = cps[0].size();
    if(v_size < 2)
        return -1;             //invalid size, at least two columns are needed

    for(DCTPVec4dvector::size_type i = 1; i < u_size; ++i)
        if(cps[i].size() != v_size)
            return -1;                           //the size of columns're not equal!

    control_points = cps;
    return 0;
}

//some REAL functionality
Vec3d BezierTensorSurface::computewdeCasteljau(Vec2d uv, int & /*error*/)
{
    const unsigned int cui_u = control_points.size();
    const unsigned int cui_v = control_points[0].size() - 1;

    Vec4d             *pcl_u = new Vec4d[cui_u];
    Vec4d             *pcl_v = new Vec4d[cui_v];
    unsigned int       ui_i;
    unsigned int       ui_j;
    unsigned int       ui_k;
    const double       cd_tu  = uv[0];
    const double       cd_tu2 = 1.0 - cd_tu;
    const double       cd_tv  = uv[1];
    const double       cd_tv2 = 1.0 - cd_tv;
    const unsigned int cui_u1 = cui_u - 1;
    const unsigned int cui_v1 = cui_v - 1;
    Vec3d              cl_ret;

//	std::cerr << uv << std::endl;

    for(ui_i = 0; ui_i < cui_u; ++ui_i)
    {
        for(ui_j = 0; ui_j < cui_v; ++ui_j)
        {
            const unsigned int cui_j1 = ui_j + 1;

            pcl_v[ui_j] = control_points[ui_i][ui_j] * cd_tv2 + control_points[ui_i][cui_j1] * cd_tv;
//			std::cerr << pd_vx[ ui_j ] << " " << pd_vy[ ui_j ] << " " << pd_vz[ ui_j ] << std::endl;
        }

        for(ui_k = 0; ui_k < cui_v1; ++ui_k)
        {
            const unsigned int cui_vk = cui_v1 - ui_k;

            for(ui_j = 0; ui_j < cui_vk; ++ui_j)
            {
                const unsigned int cui_j1 = ui_j + 1;

                pcl_v[ui_j] *= cd_tv2;
                pcl_v[ui_j] += pcl_v[cui_j1] * cd_tv;
            }
        }

        pcl_u[ui_i] = pcl_v[0];
//		std::cerr << pd_ux[ ui_i ] << " " << pd_uy[ ui_i ] << " " << pd_uz[ ui_i ] << std::endl;
    }

/*	for( ui_i = 0; ui_i < cui_u; ++ui_i )
    {
        const unsigned int	cui_i1 = ui_i + 1;

    }*/

    for(ui_k = 0; ui_k < cui_u1; ++ui_k)
    {
        const unsigned int cui_uk = cui_u1 - ui_k;

        for(ui_i = 0; ui_i < cui_uk; ++ui_i)
        {
            const unsigned int cui_i1 = ui_i + 1;

            pcl_u[ui_i] *= cd_tu2;
            pcl_u[ui_i] += pcl_u[cui_i1] * cd_tu;
        }
    }

    cl_ret[0] = pcl_u[0][0] / pcl_u[0][3];
    cl_ret[1] = pcl_u[0][1] / pcl_u[0][3];
    cl_ret[2] = pcl_u[0][2] / pcl_u[0][3];

    delete[]  pcl_u;
    delete[]  pcl_v;

//	std::cerr << cl_ret << std::endl << std::endl;

    return cl_ret;

    // NOTE: Old code was far too slow, because of memory allocation...

    //FIXME: verification before goin' into computation!!
    //FIXME: there are a lot of unverified error reports!!
/*  Vec3dmatrix::size_type n = control_points.size() - 1;
  Vec3dvector::size_type m = control_points[ 0 ].size() - 1;

  if ( n <= m ) { //less expensive: first by u0 we get a (m+1) element vector
    Vec3dvector Q( m + 1 ); //temp to store computed values at u0
    for( Vec3dvector::size_type j = 0; j <= m; ++j ) {
      Vec3dvector row( n + 1 ); //temp to store current row o' da control_points
      for( Vec2dvector::size_type k = 0; k <= n; ++k ) row[ k ] = control_points[ k ][ j ]; //copied jth row
      BezierCurve3D curve_of_row;
      curve_of_row.setControlPointVector( row );
      Q[ j ] = curve_of_row.computewdeCasteljau( uv[0], error );
    } //OK - in Q now we have the points on the surface at u0 (uv.u )
    BezierCurve3D column_at_u0;
    column_at_u0.setControlPointVector( Q );
    return column_at_u0.computewdeCasteljau( uv[1], error );
  }
  else {
    Vec3dvector Q( n + 1 );
    for( Vec3dvector::size_type j = 0; j <= n; ++j ) {
      Vec3dvector column( m + 1 ); //temp to current column o' da control_points
      column = control_points[ j ];
      BezierCurve3D curve_of_column;
      curve_of_column.setControlPointVector( column );
      Q[ j ] = curve_of_column.computewdeCasteljau( uv[1], error );
    } //OK - in Q now we have the points on the surfave at v0 (uv.v)
    BezierCurve3D row_at_v0;
    row_at_v0.setControlPointVector( Q );
    return row_at_v0.computewdeCasteljau( uv[0], error );
  }*/
}

Vec3d BezierTensorSurface::computeLinearApproximation(Vec2d uv, int &error)
{
    //FIXME: verification before goin' into computation!!
    DCTPVec4dmatrix::size_type n = control_points.size() - 1;
    DCTPVec4dvector::size_type m = control_points[0].size() - 1;
    Vec4d                      rat_res(0.0, 0.0, 0.0, 0.0);
    Vec3d                      result(0.0, 0.0, 0.0);

    if(n < 1 || m < 1)    //too few points, at least 2 needed
    {
        error = -1;
        return result;
    }
    rat_res  = (control_points[0][0] * (1 - uv[0]) + control_points[n][0] * uv[0]) * (1 - uv[1]);
    rat_res += (control_points[0][m] * (1 - uv[0]) + control_points[n][m] * uv[0]) * uv[1];

    result[0] = rat_res[0] / rat_res[3];
    result[1] = rat_res[1] / rat_res[3];
    result[2] = rat_res[2] / rat_res[3];

    return (result);
}

// subdivide surface at midpoint into 4 bezier surfaces
int BezierTensorSurface::midPointSubDivision(beziersurfacematrix &newbeziers)
{
    int          error;
    unsigned int i;
    newbeziers.resize(2);
    newbeziers[0].resize(2);
    newbeziers[1].resize(2);   // we return exactly 4 new bezier tensorsurfaces


    //FIXME: verification before goin' into computation!!
    //FIXME: there are a lot of unverified error reports!!
    DCTPVec4dmatrix::size_type n = control_points.size() - 1;
    DCTPVec4dvector::size_type m = control_points[0].size() - 1;
    bezier3dmatrix             horizdiv(n + 1);
    bezier3dmatrix             vertdivleft(m + 1);
    bezier3dmatrix             vertdivright(m + 1);

//  std::cerr << "n: " << n << " m: " << m << std::endl;
//FIXME: does the order u->v or v->u really not matter? e.g. for speed if for nothing else
    for(i = 0; i <= n; i++)
    {
        horizdiv[i].resize(2);
        horizdiv[i][0].setControlPointVector(control_points[i]);
        error = horizdiv[i][0].midPointSubDivision(horizdiv[i][1]);
        if(error)
            return error;
    }

    for(i = 0; i <= m; i++)
    {
        DCTPVec4dvector tempvecleft(n + 1);
        DCTPVec4dvector tempvecright(n + 1);

        for(DCTPdvector::size_type j = 0; j <= n; j++)
        {
            tempvecleft[j]  = horizdiv[j][0].getControlPointVector()[i];
            tempvecright[j] = horizdiv[j][1].getControlPointVector()[i];
        } // j

        vertdivleft[i].resize(2);
        vertdivleft[i][0].setControlPointVector(tempvecleft);
        error = vertdivleft[i][0].midPointSubDivision(vertdivleft[i][1]);
        if(error)
            return error;
        vertdivright[i].resize(2);
        vertdivright[i][0].setControlPointVector(tempvecright);
        error = vertdivright[i][0].midPointSubDivision(vertdivright[i][1]);
        if(error)
            return error;
    } // i

    DCTPVec4dmatrix cps(n + 1);

    for(i = 0; i <= n; i++)
        cps[i].resize(m + 1);

    for(i = 0; i <= n; i++)
    {
        for(DCTPVec4dmatrix::size_type j = 0; j <= m; j++)
        {
            cps[i][j] = vertdivleft[j][0].getControlPointVector()[i];
        }
    }

    newbeziers[0][0].setControlPointMatrix(cps);

    for(i = 0; i <= n; i++)
    {
        for(DCTPVec4dmatrix::size_type j = 0; j <= m; j++)
        {
            cps[i][j] = vertdivleft[j][1].getControlPointVector()[i];
        }
    }

    newbeziers[1][0].setControlPointMatrix(cps);

    for(i = 0; i <= n; i++)
    {
        for(DCTPVec4dmatrix::size_type j = 0; j <= m; j++)
        {
            cps[i][j] = vertdivright[j][0].getControlPointVector()[i];
        }
    }

    newbeziers[0][1].setControlPointMatrix(cps);

    for(i = 0; i <= n; i++)
    {
        for(DCTPVec4dmatrix::size_type j = 0; j <= m; j++)
        {
            cps[i][j] = vertdivright[j][1].getControlPointVector()[i];
        }
    }

    newbeziers[1][1].setControlPointMatrix(cps);


    return 0;
}

// subdivide surface at midpoint into 4 bezier surfaces
int BezierTensorSurface::midPointSubDivision(beziersurfacevector &newbeziers)
{
    int error;

    newbeziers.resize(3); // we return exactly 3 new bezier tensorsurfaces

    error = midPointSubDivisionU(newbeziers[1]);    // first in u because this is slower
    if(error)
        return error;
    error = midPointSubDivisionV(newbeziers[0]);
    if(error)
        return error;
    return newbeziers[1].midPointSubDivisionV(newbeziers[2]);
}

// subdivide surface at midpoint into 2 bezier surfaces
int BezierTensorSurface::midPointSubDivisionU(BezierTensorSurface &newsurface)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec4dmatrix::size_type n = control_points.size();
    DCTPVec4dvector::size_type m = control_points[0].size();

    if( (n < 2) || (m < 2) )
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    DCTPVec4dvector::size_type i, k;
    DCTPVec4dmatrix::size_type j;

    newsurface.control_points.clear();  // very imporatant for performance (no copying around of obsolte stuff!)
    newsurface.control_points.resize(n);

    for(j = 0; j < n; ++j)
    {
        DCTPVec4dvector &cp2 = newsurface.control_points[j];

        cp2.resize(m);
    }

    DCTPVec4dmatrix &cp1 = control_points;
    DCTPVec4dmatrix &cp2 = newsurface.control_points;

    --n;

    for(j = 0; j < m; ++j)
    {
        for(k = 0; k < n; ++k)
        {
            cp2[n - k][j] = cp1[n][j];

            for(i = n; i > k; --i)
            {
                cp1[i][j] += cp1[i - 1][j];
                cp1[i][j] *= 0.5;
            }
        }

        cp2[0][j] = cp1[n][j];
    }

    return 0;
}

// subdivide surface at midpoint into 2 bezier surfaces
int BezierTensorSurface::midPointSubDivisionV(BezierTensorSurface &newsurface)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec4dmatrix::size_type n = control_points.size();
    DCTPVec4dvector::size_type m = control_points[0].size();

    if( (n < 2) || (m < 2) )
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    DCTPVec4dvector::size_type i, k;
    DCTPVec4dmatrix::size_type j;

    newsurface.control_points.clear();  // very imporatant for performance (no copying around of obsolte stuff!)
    newsurface.control_points.resize(n);
    --m;

    for(j = 0; j < n; ++j)
    {
        DCTPVec4dvector &cp1 = control_points[j];
        DCTPVec4dvector &cp2 = newsurface.control_points[j];

        cp2.resize(m + 1);

        for(k = 0; k < m; ++k)
        {
            cp2[m - k] = cp1[m];

            for(i = m; i > k; --i)
            {
                cp1[i] += cp1[i - 1];
                cp1[i] *= 0.5;
            }
        }

        cp2[0] = cp1[m];
    }

    return 0;
}
