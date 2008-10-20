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
#include "OSGBezierCurve3D.h"
#include <OSGBaseTypes.h>

OSG_USING_NAMESPACE


#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif


//construction (& destruction, but not here :)
BezierCurve3D::BezierCurve3D()
{
    control_points.resize(0);
}

//setup functions
int BezierCurve3D::setControlPointVector(const DCTPVec4dvector& cps)
{
    if(cps.size() < 2)
        return -1;                 //invalid dimension, at least two points are required
    control_points = cps;
    return 0;
}


//some REAL functionality
//! Compute the value of the Bezier curve at given the parameter value.
/*!
 *  This function computes the value of the Bezier curve
 *  at the given parameter value, using de Casteljau's method of
 *  repeated linear interpolations.
 *
 *  \param t the parameter value at which to compute the approximation
 *  \param error flag to indicate if an error has happened
 *  \return the approximated value
 *
 */
Vec3d BezierCurve3D::computewdeCasteljau(double t, int &error)
{
    Vec4d rat_res = computewdeCasteljau4D(t, error);
    Vec3d res;

    res[0] = rat_res[0] / rat_res[3];
    res[1] = rat_res[1] / rat_res[3];
    res[2] = rat_res[2] / rat_res[3];

    return res;
}


Vec4d BezierCurve3D::computewdeCasteljau4D(double t, int &error)
{
    //FIXME: verification before goin' into computation!!
//  Vec3dvector Q = control_points; //local array not to destroy da other points
    const unsigned int n = control_points.size() - 1;
    Vec4d              rat_res;

    if(n < 1)   //too few points, at least 2 needed
    {
        error      = -1;
        rat_res    = control_points[0];
        rat_res[0] = DCTP_EPS * floor(rat_res[0] / DCTP_EPS);
        rat_res[1] = DCTP_EPS * floor(rat_res[1] / DCTP_EPS);
        rat_res[2] = DCTP_EPS * floor(rat_res[2] / DCTP_EPS);
        rat_res[3] = DCTP_EPS * floor(rat_res[3] / DCTP_EPS);
        return rat_res;
    }

    unsigned int       i, k;
    Vec4d             *Q  = new Vec4d[n];
    const double       t2 = 1.0 - t;
    const unsigned int n1 = n - 1;

    for(i = 0; i < n; ++i)
    {
        const unsigned int i1 = i + 1;
        Q[i] = control_points[i] * t2 + control_points[i1] * t;
    }

    for(k = 0; k < n1; ++k)
    {
        const unsigned int nk = n1 - k;

        for(i = 0; i < nk; ++i)
        {
            const unsigned int i1 = i + 1;
            Q[i] *= t2;
            Q[i] += Q[i1] * t;
        }
    }

    rat_res = Q[0];

    delete[]  Q;
    return rat_res;

}

//! Compute the linear approximation of the Bezier curve at the given parameter value.
/*!
 *  This function computes the linear approximation of the Bezier curve
 *  at the given parameter value.
 *
 *  \param t the parameter value at which to compute the approximation
 *  \param error flag to indicate if an error has happened
 *  \return the approximated value
 *
 */
Vec3d BezierCurve3D::computeLinearApproximation(double t, int &error)
{
    //FIXME: verification before goin' into computation!!
    DCTPVec4dvector::size_type n = control_points.size() - 1;
    Vec3d                      result(0.0, 0.0, 0.0);
    Vec4d                      rat_res;

    if(n < 1)
    { //too few points, at least 2 needed
        error = -1;
        return result;
    }
    rat_res   = control_points[0] * t + control_points[n] * (1 - t);
    result[0] = rat_res[0] / rat_res[3];
    result[1] = rat_res[1] / rat_res[3];
    result[2] = rat_res[2] / rat_res[3];

    return (result);
}

//! Subdivide Bezier curve at midpoint into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the midpoint, using de Casteljau's
 *  algorithm.
 *
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::midPointSubDivision(bezier3dvector &newbeziers)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec4dvector::size_type n = control_points.size();

    if(n < 2)    //too few points, at least 2 needed to split curve
    {
        return -1;
    }

    newbeziers.resize(2);   // we return exactly two curves
    DCTPVec4dvector::size_type i, k;

    DCTPVec4dvector &cp1 = newbeziers[0].control_points;
    DCTPVec4dvector &cp2 = newbeziers[1].control_points;
    cp1.clear();    // very important for performance (no copying around of obsolte stuff!)
    cp2.clear();    // very important for performance (no copying around of obsolte stuff!)
    cp1.resize(n);
    cp2.resize(n);

    for(k = 0; k < n; ++k)
    {
        cp1[k] = control_points[k];
    }

    --n;

    for(k = 0; k < n; ++k)
    {
        cp2[n - k] = cp1[n];

        for(i = n; i > k; --i)
        {
            cp1[i] += cp1[i - 1];
            cp1[i] *= 0.5;
        }
    }

    cp2[0] = cp1[n];
//  newbeziers[ 0 ].setControlPointVector( cp1 );
//  newbeziers[ 1 ].setControlPointVector( cp2 );
    return 0;
}

//! Subdivide Bezier curve at midpoint into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the midpoint, using de Casteljau's
 *  algorithm.
 *
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::midPointSubDivision(BezierCurve3D &newcurve)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec4dvector::size_type n = control_points.size();

    if(n < 2)
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    DCTPVec4dvector::size_type i, k;

    DCTPVec4dvector &cp1 = control_points;
    DCTPVec4dvector &cp2 = newcurve.control_points;

    cp2.clear();    // very important for performance (no copying around of obsolte stuff!)
    cp2.resize(n);

    --n;

    for(k = 0; k < n; ++k)
    {
        cp2[n - k] = cp1[n];

        for(i = n; i > k; --i)
        {
            cp1[i] += cp1[i - 1];
            cp1[i] *= 0.5;
        }
    }

    cp2[0] = cp1[n];

    return 0;
}

//! Subdivide Bezier curve at t into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the parameter value `t', using de Casteljau's
 *  algorithm.
 *
 *  \param t the parameter at which to subdivide the curve.
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::subDivision(double t, bezier3dvector &newbeziers)
{
    if(t <= 0.0 || t >= 1.0)
        return -1;                         // t must be between (0, 1) exclusive

    newbeziers.resize(2);   // we return exactly two curves
    DCTPVec4dvector            Q = control_points; //local array not to destroy da other points
    DCTPVec4dvector::size_type n = control_points.size() - 1;
    DCTPVec4dvector            cp1(n + 1);
    DCTPVec4dvector            cp2(n + 1);
    if(n < 1)    //too few points, at least 2 needed to split curve
    {
        return -1;
    }

    for(DCTPVec4dvector::size_type k = 0; k < n; ++k)
    {
        cp1[k]     = Q [0];
        cp2[n - k] = Q [n - k];

        for(DCTPVec4dvector::size_type i = 0; i < n - k; ++i)
        {
            Q[i] = Q[i] * (1.0 - t) + Q[i + 1] * t;
        }
    }

    cp1[n] = Q[0];
    cp2[0] = Q[0];
    newbeziers[0].setControlPointVector(cp1);
    newbeziers[1].setControlPointVector(cp2);
    return 0;
}

//! Subdivide Bezier curve at t into two new curves.
/*!
 *  This function subdivides a Bezier curve into two new Bezier curves
 *  of the same degree at the parameter value `t', using de Casteljau's
 *  algorithm.
 *
 *  \param t the parameter at which to subdivide the curve.
 *  \param newbeziers the two new Bezier curves (returned in a vector of size 2)
 *  \return zero on success, and a negative value when some error occured.
 *
 *
 */
int BezierCurve3D::subDivision(double t, BezierCurve3D &newcurve)
{
    if(t <= 0.0 || t >= 1.0)
    {
        return -1; // t must be between (0, 1) exclusive
    }

    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec4dvector::size_type n = control_points.size();

    if(n < 2)
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    double t2 = 1.0 - t;

    DCTPVec4dvector::size_type i, k;

    DCTPVec4dvector &cp1 = control_points;
    DCTPVec4dvector &cp2 = newcurve.control_points;

    cp2.clear();    // very imporatant for performance (no copying around of obsolte stuff!)
    cp2.resize(n);

    --n;

    for(k = 0; k < n; ++k)
    {
        cp2[n - k] = cp1[n];

        for(i = n; i > k; --i)
        {
            cp1[i] *= t;
            cp1[i] += cp1[i - 1] * t2;
        }
    }

    cp2[0] = cp1[n];

    return 0;
}

//! Approximate curve linearly with given maximum tolerance.
/*!
 *  This function approximates the Bezier curve with a polyline. The maximum
 *  error of the approximation will not be larger than the given tolerance.
 *
 *
 *  \param vertices the vertices of the approximating polyline.
 *  \param delta maximum error.
 *  \return zero on success, and a negative value when some error occured.
 */
int BezierCurve3D::approximate(std::vector<double> &vertices, double delta, unsigned char strategy)
{
    vertices.resize(0);

    // check for first degree Bezier.
    if(control_points.size() == 2)
    {
        vertices.push_back(0.0);
        vertices.push_back(1.0);
        return 0;
    }

    // call recursive subdividing function
    return approximate_sub(vertices, delta, 0.0, 1.0, strategy);
}

int BezierCurve3D::approximate_sub(std::vector<double> &vertices, double delta, double min, double max, unsigned char strategy)
{
    double              max_error = 0;
    Vec3d               ae;
    double              aenorm;
    double              t1, t2;
    int                 worst_i = 0;
    Vec3d               n0_norm;
    DCTPVec3dvector     eucl;
    DCTPVec4dvector     mycps;
    unsigned int        i;
    std::vector<double> t;

    int n = control_points.size() - 1;

    for(i = 0; i <= n; i++)
    {
        t.push_back((double( n - i ) ) / n);
    }

    // first, make a copy of the cp vector, and do one
    // or more de Casteljau steps to get rid of 0 weights
    mycps = control_points;

    for(i = 0; i <= n; ++i)
    {
        unsigned int s  = mycps.size();
        bool         ok = true;

        mycps.push_back(mycps[s - 1]);
        t.push_back(t[s - 1]);

        for(unsigned int j = s; j > i; --j)
        {
            mycps[j] = (mycps[j] + mycps[j - 1]) * 0.5f;
            t[j]     = (t[j] + t[j - 1]) * 0.5f;
            if(mycps[j][2] < DCTP_EPS)
                ok = false;
        }

        if(ok)
            break;
    }

    n = mycps.size() - 1;

    eucl.resize(n + 1);

    for(i = 0; i <= n; ++i)
    {
        eucl[i][0] = mycps[i][0] / mycps[i][3];
        eucl[i][1] = mycps[i][1] / mycps[i][3];
        eucl[i][2] = mycps[i][2] / mycps[i][3];
    }

    if( (strategy & DISTANCE) == LINE_DISTANCE)
    {
        n0_norm = eucl[n] - eucl[0];
        aenorm  = n0_norm.squareLength();
        if(aenorm > 1e-300)
        {
            n0_norm *= 1.0 / aenorm;
        }
        else
        {
            n0_norm = Vec3d(0.0, 0.0, 0.0);
        }
    }

    for(i = 0; i <= n; i++)
    {
        if( (strategy & DISTANCE) == POINT_DISTANCE)
        {
            t2 = 1.0 - t[i];
        }
        else
        {
            t2 = (eucl[i] - eucl[0]).dot(n0_norm);
            if(t2 < 0.0)
            {
                t2 = 0.0;
            }
            else if(t2 > 1.0)
            {
                t2 = 1.0;
            }
        }
        t1 = 1.0 - t2;
        ae = eucl[i] - eucl[0] * t1 - eucl[n] * t2;

//    std::cerr << "i: " << i << " ae.x: " << ae[0] << " ae.y: " << ae[1] << std::endl;

        aenorm = sqrt(ae.squareLength() );
        if(aenorm > max_error)
        {
            max_error = aenorm;
            worst_i   = i;
        }
    }

//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ][0] << " " << control_points[ 0 ][1] << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ][0] << " " << control_points[ control_points.size() - 1 ][1] << std::endl;
    if(max_error > delta)
    {
        // we have to subdivide further
        BezierCurve3D newbez;
        int           error;
        double        mid;
        if( (strategy & SUBDIVISION) == MIDPOINT_SUBDIVISION)
        {
            error = midPointSubDivision(newbez);
            if(error)
                return error;
            mid = (min + max) * 0.5;
        }
        else
        {
            mid   = (double(worst_i) ) / n;
            error = subDivision(mid, newbez);
            if(error)
                return error;
            mid = min + (max - min) * mid;
        }
        approximate_sub(vertices, delta, min, mid, strategy);
        newbez.approximate_sub(vertices, delta, mid, max, strategy);
    }
    else
    {
        // this is a good enough approximation
        if(!vertices.size() )
        {
            // this is the first approximation, we have to record both the
            // startpoint and the endpoint
            vertices.push_back(min);
            vertices.push_back(max);
        }
        else
        {
            // we had some subdivisions before, we only need to record the endpoint
            vertices.push_back(max);
        }
    }
    return 0;
}

// generate a bezier curve through these points
int BezierCurve3D::createCurve(DCTPVec4dvector &points)
{
    int n = points.size() - 1;

    if(n < 1)
    {
        return -1;  // too few points
    }

    control_points.resize(n + 1);

    control_points[0] = points[0];
    control_points[n] = points[n];

    if(n == 1)
    {
        return 0;   // linear curve, so we are done...
    }

/*	if( m_svvvdCreateMatrix.size( ) == 0 )
    {
        if( loadCreateMatrices( ) != 0 )
        {
            return -3;	// matrix file not found
        }
    }

    if( n - 1 > m_svvvdCreateMatrix.size( ) )
    {
        return -2;	// degree too high (sorry...)
    }*/

    int i;
    int j;
//	std::vector< std::vector< double > >	&mat = m_svvvdCreateMatrix[ n - 2 ];

    for(i = 1; i < n; ++i)
    {
/*		std::vector< double >	&row = mat[ i ];
        control_points[ i ][0] = control_points[ i ][1] = control_points[ i ][2] = 0.0;
        for( j = 0; j <= n; ++j )
        {
            control_points[ i ] += ( points[ j ] - points[ n >> 1 ] ) * row[ j ];
//			std::cerr << row[ j ] << " ";
        }
        control_points[ i ] += points[ n >> 1 ];
//		std::cerr << std::endl;*/
        control_points[i] = points[i];
    }

    // try to approximate it better
    double maxerr = 1.0;

//	std::cerr << "n = " << n;

    unsigned int ui_exit = 0;
    while(maxerr > 1e-8)
    {
        std::vector<Vec4d> vcl_err(n + 1);

        maxerr = 0.0;

        for(i = 0; i <= n; ++i)
        {
            int err = 0;
            vcl_err[i] = points[i] - computewdeCasteljau4D( (double(i) ) / n, err);

            double acterr = (vcl_err[i]).squareLength();

            maxerr = osgMax(maxerr, acterr);
        }

        for(i = 1; i < n; ++i)
        {
//			std::vector< double >	&row = mat[ i ];
            control_points[i] += vcl_err[i];
        }

        if( (++ui_exit) > 10000)
        {
//			for( i = 0; i <= n; ++i )
//			{
// FIXME: operator<< depracated
//				std::cerr << points[ i ] << std::endl;
//			}
//			std::cerr << std::endl;
//			std::cerr << "approxerr: " << sqrt( maxerr ) << std::endl;

            return -2;
        }
    }
//	std::cerr << ", approxerr: " << sqrt( maxerr ) << std::endl;
    return 0;   // everything ok.
}


//! Degree reduce the Bezier curve with t tolerance if possible.
/*!
 *  This function tries to degree reduce the Bezier curve ensuring
 *  that the new curve does not deviate more from the original curve
 *  than a specified error tolerance.
 *
 *  \param t error tolerance which is still accepted for the new
 *           (lower degree) curve.
 *  \return true on success, false if degree reduction is not possible
 *           within the given tolerance.
 */
bool BezierCurve3D::reduceDegree(double tol)
{
    UInt32 n = control_points.size() - 1;      // orig cps: 0, ..., n
    if(n < 2)
    {
        // cannot degree reduce a first degree curve
        return false;
    }
    DCTPVec4dvector b_left(n);
    DCTPVec4dvector b_right(n);
    UInt32          i;

    // calculate b_right:
    b_right[0] = control_points[0];

    for(i = 1; i < n; ++i)
    {
        b_right[i] = (control_points[i] * n - b_right[i - 1] * i) *
                     (1.0 / Real64(n - i));
    }

    // calculate b_left:
    b_left[n - 1] = control_points[n];

    for(i = n - 1; i > 0; --i)
    {
        b_left[i - 1] = (control_points[i] * n - b_left[i] * (n - i)) *
                        (1.0 / Real64(i));
    }

    // check for introduced error:
    Real64 quad_error = tol * tol;
    double dist4d;

    unsigned int n_half  = n >> 1;
    unsigned int n_half1 = (n + 1) >> 1;

//	for (i = 0; i < n_half; ++i)
//    {
//        control_points[ i ] = b_right[ i ];
//    }
    for(i = n_half1; i < n; ++i)
    {
        b_right[i] = b_left[i];
    }

    if(n_half != n_half1)
    {
        dist4d          = b_right[n_half].dist2(b_left[n_half]);
        b_right[n_half] = b_left[n_half] * 0.5 + b_right[n_half] * 0.5;
    }
    else
    {
        dist4d = control_points[n_half].dist2(0.5 * (b_right[n_half - 1] + b_left[n_half]));
    }



    //Vec3d dist;
    double minweight = b_right[0][3];

    for(i = 1; i < n; ++i)
    {
        if(minweight > b_right[i][3])
            minweight = b_right[i][3];
    }

    if(minweight < DCTP_EPS)
    {
        // can't degree reduce a curve with zero weight(s)...
        return false;
    }

    if(dist4d / (minweight * minweight) > quad_error)
    {
        return false;
    }

    control_points = b_right;
//    setControlPointVector( b_new );

    return true;
}
