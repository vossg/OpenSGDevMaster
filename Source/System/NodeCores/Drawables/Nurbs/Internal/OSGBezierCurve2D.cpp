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

#include "OSGBezierCurve2D.h"

OSG_USING_NAMESPACE


#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

//setup functions
int BezierCurve2D::setControlPointVector(const DCTPVec3dvector& cps)
{
    if(cps.size() < 2)
        return -1;                 //invalid dimension, at least rwo points are required
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
 *  \return the computed value
 *
 */
Vec2d BezierCurve2D::computewdeCasteljau(double t, int &error)
{
    //FIXME: verification before goin' into computation!!
    DCTPVec3dvector            Q = control_points; //local array not to destroy da other points
    DCTPVec3dvector::size_type n = Q.size() - 1;
    Vec2d                      result;

    error = 0;
    if(n < 1)    //too few points, at least 2 needed
    {
        error     = -1;
        Q[0][0]   = DCTP_EPS * floor(Q[0][0] / DCTP_EPS);
        Q[0][1]   = DCTP_EPS * floor(Q[0][1] / DCTP_EPS);
        result[0] = Q[0][0] / Q[0][2];
        result[1] = Q[0][1] / Q[0][2];
        return result;
    }
//  std::cerr.precision( DCTP_PRECISION );
//  for ( unsigned int kkk = 0; kkk < Q.size(); kkk++ )
//     std::cerr << Q[ kkk ] << " " ;
//  std::cerr << std::endl;

    // orig fecu code
    for(DCTPVec3dvector::size_type k = 0; k < n; ++k)
        for(DCTPVec3dvector::size_type i = 0; i < n - k; ++i)
            Q[i] = Q[i] * (1.0 - t) + Q[i + 1] * t;

    result[0] = Q[0][0] / Q[0][2];
    result[1] = Q[0][1] / Q[0][2];

    return result;
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
Vec2d BezierCurve2D::computeLinearApproximation(double t, int &error)
{
    //FIXME: verification before goin' into computation!!
    DCTPVec3dvector::size_type n = control_points.size() - 1;
    Vec2d                      result(0.0, 0.0);
    Vec3d                      tempres;

    error = 0;
    if(n < 1)    //too few points, at least 2 needed
    {
        error = -1;
        return result;
    }
    tempres   = control_points[0] * (1 - t) + control_points[n] * t;
    result[0] = tempres[0] / tempres[2];
    result[1] = tempres[1] / tempres[2];
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
int BezierCurve2D::midPointSubDivision(bezier2dvector &newbeziers)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec3dvector::size_type n = control_points.size();

    if(n < 2)    //too few points, at least 2 needed to split curve
    {
        return -1;
    }

    newbeziers.resize(2);   // we return exactly two curves
    DCTPVec3dvector::size_type i, k;

    DCTPVec3dvector &cp1 = newbeziers[0].control_points;
    DCTPVec3dvector &cp2 = newbeziers[1].control_points;

    cp1.clear();    // very imporatant for performance (no copying around of obsolte stuff!)
    cp2.clear();    // very imporatant for performance (no copying around of obsolte stuff!)
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
int BezierCurve2D::midPointSubDivision(BezierCurve2D &newcurve)
{
    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec3dvector::size_type n = control_points.size();

    if(n < 2)
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    DCTPVec3dvector::size_type i, k;

    DCTPVec3dvector &cp1 = control_points;
    DCTPVec3dvector &cp2 = newcurve.control_points;

    cp2.clear();    // very imporatant for performance (no copying around of obsolte stuff!)
    cp2.resize(n);

    --n;

    for(k = 0; k < n; ++k)
    {
        cp2[n - k] = cp1[n];

//		cp2[ n - k ][0] = cp1[ n ][0];
//		cp2[ n - k ][1] = cp1[ n ][1];
        for(i = n; i > k; --i)
        {
            cp1[i] += cp1[i - 1];
//			cp1[ i ][0] += cp1[ i - 1 ][0];
//			cp1[ i ][1] += cp1[ i - 1 ][1];
            cp1[i] *= 0.5;
//			cp1[ i ][0] *= 0.5;
//			cp1[ i ][1] *= 0.5;
        }
    }

    cp2[0] = cp1[n];
//	cp2[ 0 ][0] = cp1[ n ][0];
//	cp2[ 0 ][1] = cp1[ n ][1];

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
int BezierCurve2D::subDivision(double t, bezier2dvector &newbeziers)
{
    if(t <= 0.0 || t >= 1.0)
        return -1;                       // t must be between (0, 1) exclusive

    newbeziers.resize(2); // we return exactly two curves
    DCTPVec3dvector            Q = control_points; //local array not to destroy da other points
    DCTPVec3dvector::size_type n = control_points.size() - 1;
    DCTPVec3dvector            cp1(n + 1);
    DCTPVec3dvector            cp2(n + 1);
    if(n < 1)    //too few points, at least 2 needed to split curve
    {
        return -1;
    }

    for(DCTPVec3dvector::size_type k = 0; k < n; ++k)
    {
        cp1[k]     = Q [0];
        cp2[n - k] = Q [n - k];

        for(DCTPVec3dvector::size_type i = 0; i < n - k; ++i)
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
int BezierCurve2D::subDivision(double t, BezierCurve2D &newcurve)
{
    if(t <= 0.0 || t >= 1.0)
    {
        return -1; // t must be between (0, 1) exclusive
    }

    // This function is time critical so optimize at the cost of readabiltity...
    DCTPVec3dvector::size_type n = control_points.size();

    if(n < 2)
    {
        return -1;  //too few points, at least 2 needed to split curve
    }

    double t2 = 1.0 - t;

    DCTPVec3dvector::size_type i, k;

    DCTPVec3dvector &cp1 = control_points;
    DCTPVec3dvector &cp2 = newcurve.control_points;

    cp2.clear();    // very important for performance (no copying around of obsolte stuff!)
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

//! Calculate intersection of the Bezier curve with the polyline (a, b).
/*!
 *  This function calculates the number of intersections the curve has
 *  with the polyline (a, b), using Bezier clipping and the minmax algorithm.
 *
 *  \param res the double vector which will contain the results
 *             (in (0, 1) parameter space)
 *  \param a   the first point of the polyline
 *  \param b   the second point of the polyline
 *  \return zero on success, a negative value if some error occured, and <BR>
 *          1 if the curve lies entirely on the polyline. <BR>
 *          2 if the curve lies partly on the polyline. <BR>
 *
 */
int BezierCurve2D::intersection(DCTPdvector &res, Vec2d a, Vec2d b)
{
    int          result;
    unsigned int i;

    if(osgAbs(a[0] - b[0]) < DCTP_EPS && osgAbs(a[1] - b[1]) < DCTP_EPS)
        return -1; // the two points are (almost) the same

//  DCTPdvector dists( control_points.size() ); // the signed distance of the control points and the polyline
    Vec2d norm; // norm of ( a - b )
    //due to the check above, lab must be positive
    double lab = sqrt( (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) );
    norm[0] = -(b[1] - a[1]) / lab;   // This is a normal -> rotated 90 degrees
    norm[1] = (b[0] - a[0]) / lab;


    DCTPVec3dvector newcp(control_points.size() ); // the control points of the explicit Bezier curve
    int             flag   = 1;
    unsigned int    cpsize = control_points.size() - 1;

    for(i = 0; i <= cpsize; i++)
    {
//    std::cerr.precision( DCTP_PRECISION );
//    std::cerr << "cp[i].x: " << control_points[ i ][0] << " cp[i].y: " << control_points[ i ][1] << std::endl;
        newcp[i][0] = (i / cpsize) * control_points[i][2];
        newcp[i][1] = pointLineDistancewNormal(control_points[i], a, norm);
        newcp[i][2] = control_points[i][2];
        //std::cerr << " dists[i]: " << newcp[ i ][1] << std::endl;
        if(newcp[i][1] < -DCTP_EPS || newcp[i][1] > DCTP_EPS)
            flag = 0;
    }

    if(flag)
    {
        res.resize(0); // zero result vector because
        // check start and endpoint of curve, is it really on the polyline, or before/after ?
        double ta, tb;
        Vec2d  first, last;
        // we assume that the first and last control points can't have zero weights !!!
        // (if they were zero, the curve goes through infinity...
        first[0] = control_points[0][0] / control_points[0][2];
        first[1] = control_points[0][1] / control_points[0][2];
        last[0]  = control_points[cpsize][0] / control_points[cpsize][2];
        last[1]  = control_points[cpsize][1] / control_points[cpsize][2];

        if(osgAbs(first[0] - last[0]) > DCTP_EPS)
        {
            ta = (a[0] - first[0]) / (last[0] - first[0]);
            tb = (b[0] - first[0]) / (last[0] - first[0]);
        }
        else
        {
            ta = (a[1] - first[1]) / (last[1] - first[1]);
            tb = (b[1] - first[1]) / (last[1] - first[1]);
        }

        if(tb < ta)
        {
            double tmp = ta;
            ta = tb;
            tb = tmp;
        }
        if(ta <= 0.0)
            ta = 0.0;
        if(tb <= 0.0)
            tb = 0.0;
        if(ta >= 1.0)
            ta = 1.0;
        if(tb >= 1.0)
            tb = 1.0;

        if(ta == tb)
            return 0;          // fully before or after
        if(ta == 0.0 && tb == 1.0)
            return 1;                        // fully on the polyline

        res.resize(2); // the curve lies partially on the polyline
//    std::cerr << " ta: " << ta << " tb: " << tb << std::endl;
        res[0] = ta;
        res[1] = tb;
        return 2; //the curve partially lies on the polyline
    }

    BezierCurve2D bstart;
    result = bstart.setControlPointVector(newcp);
    if(result)
        return result;         // some error happened
    result = bstart.minMaxIntersection(res, 0.0, 1.0);
    bool zeroroot = (osgAbs(newcp[0][1]) < DCTP_EPS);
    bool oneroot  = (osgAbs(newcp[cpsize][1]) < DCTP_EPS);

    // special care taken for start/end points
    // FIXME: hack #1 :-|
    if(res.size() )
    {
        if(res[res.size() - 1] >= 1.0 - DCTP_EPS)
            res[res.size() - 1] = 1.0;
        if(res[0] <= DCTP_EPS)
            res[0] = 0.0;
    }
    if(zeroroot)
    {
        // we have some solutions, but the first solution is not 0.0, we
        // have to insert 0.0 as first solution
        if(res.size() && res[0] >= DCTP_EPS)
            res.insert(res.begin(), 0.0);
        // we don't have any solutions yet, but this is a solution, so we have to
        // insert this
        else if(!res.size() )
            res.push_back(0.0);
    }
    if(oneroot)
    {
        // if we have oneroot, and the last item is not 1.0, we have to insert it
        // as last result, regardless of what is actually in the vector (it can even be empty)
        // check for the last item ( & its existence )
        if(res.size() && res[res.size() - 1] < 1.0 - DCTP_EPS)
            res.push_back(1.0);
        // insert it if the resultvector is empty
        else if(!res.size() )
            res.push_back(1.0);
    }


//  std::cerr << "still here. solutions: " << res.size() << std::endl;
    for(i = 0; i < res.size(); i++)
    {
        Vec2d  p;
        int    er;
        double t;
//    std::cerr << " i: " << i << " solution[i]: " << res[ i ];
        p = computewdeCasteljau(res[i], er);
//    std::cerr << " value: " << p[0] << " " << p[1] << std::endl;
        if(osgAbs(b[0] - a[0]) > DCTP_EPS)
            t = (p[0] - a[0]) / (b[0] - a[0]);
        else
            t = (p[1] - a[1]) / (b[1] - a[1]);
//    std::cerr << " lineparam: " << t << std::endl;
        if(DCTPVecIsNotEqual(p, a) && DCTPVecIsNotEqual(p, b) )
            if(t < -DCTP_EPS || t > (1 + DCTP_EPS) )
            {
                res.erase(res.begin() + i);
                i--;
            }
    }

//  std::cerr << "still here. solutions after: " << res.size() << std::endl;
//  if ( res.size() ) std::cerr << res[ 0 ] << std::endl;

#if 0
    // we have to make this check _after_ the results have been filtered
    if(res.size() > control_points.size() )
    {
        /*
         * We have more results than possible, the curve partly lies on the polyline
         * we only return the first and last results, and hope for the best.
         * note this is not a 100% general solution, but in the vast majority
         * of cases it works.
         * FIXME: a 100% general solution may be desirable some day...
         */
        double tt = res[res.size() - 1];
        res.resize(2);
        res[1] = tt;
        return -2; // to indicate some problem happened
    }
#endif
    return result;
}


// calculate intersection of curve with line (a)
int BezierCurve2D::intersection(DCTPdvector &res, double a, bool horiz)
{
    DCTPVec3dvector    newcp(control_points.size() ); // the control points of the explicit Bezier curve
    BezierCurve2D      tempcurve;
    const unsigned int cpsize = control_points.size() - 1;

    for(unsigned int i = 0; i < newcp.size(); ++i)
    {
        if(horiz)
        {
            newcp[i] = control_points[i];
        }
        else
        {
            newcp[i][0] = control_points[i][1];
            newcp[i][1] = control_points[i][0];
            newcp[i][2] = control_points[i][2];
        }
        newcp[i][1] -= a * newcp[i][2];
    }

    int result = tempcurve.setControlPointVector(newcp);
    if(result)
        return result;         // some error happened
    result = tempcurve.minMaxIntersection(res, 0.0, 1.0);
    bool zeroroot = (osgAbs(newcp[0][1]) < DCTP_EPS);
    bool oneroot  = (osgAbs(newcp[cpsize][1]) < DCTP_EPS);
    // special care taken for start/end points
    // FIXME: hack #1 :-|
    if(res.size() )
    {
        if(res[res.size() - 1] >= 1.0 - DCTP_EPS)
            res[res.size() - 1] = 1.0;
        if(res[0] <= DCTP_EPS)
            res[0] = 0.0;
    }
    if(zeroroot)
    {
        // we have some solutions, but the first solution is not 0.0, we
        // have to insert 0.0 as first solution
        if(res.size() && res[0] >= DCTP_EPS)
            res.insert(res.begin(), 0.0);
        // we don't have any solutions yet, but this is a solution, so we have to
        // insert this
        else if(!res.size() )
            res.push_back(0.0);
    }
    if(oneroot)
    {
        // if we have oneroot, and the last item is not 1.0, we have to insert it
        // as last result, regardless of what is actually in the vector (it can even be empty)
        // check for the last item ( & its existence )
        if(res.size() && res[res.size() - 1] < 1.0 - DCTP_EPS)
            res.push_back(1.0);
        // insert it if the resultvector is empty
        else if(!res.size() )
            res.push_back(1.0);
    }
    return result;
}


// calculate intersection of x axis and Bezier curve, calls itself recursively
int BezierCurve2D::minMaxIntersection(DCTPdvector &res, double s, double e)
{
    double miny = control_points[0][1];
    double maxy = control_points[0][1];
    int    result;
    Vec2d  r;
    double mid = 0.0;

//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << "minmax for: " << s << " " << e << std::endl;
// find the minmax box of the control polygon - note we only need the y values
// meanwhile also check that we do not lie on the line :)
    DCTPVec3dvector::size_type cpsize = control_points.size();
    DCTPVec3dvector::size_type i;

    for(i = 1; i < cpsize; i++)
    {
        if(control_points[i][1] > maxy)
            maxy = control_points[i][1];
        else if(control_points[i][1] < miny)
            miny = control_points[i][1];
    }

//  std::cerr << " miny: " << miny << " maxy: " << maxy << std::endl;

#if 0
    if(miny > -DCTP_EPS && miny < DCTP_EPS && maxy > -DCTP_EPS && maxy < DCTP_EPS)
    {
        std::cerr << " found interval: [ " << control_points[0][0] << " - " << control_points[cpsize - 1][0] << " ]" << std::endl;
        return 0;
    }
    if(osgAbs(control_points[0][1]) < DCTP_EPS)
    {
///   original code
//    if ( res.size() && res[ res.size() - 1 ] == s ) return 0;
        if(!res.size() || res[res.size() - 1] != s)
        {
            std::cerr << " special recording: " << s << std::endl;
            res.push_back(s);
            // we have to check for the last point too, for really degenerate cases
//    if ( !( osgAbs( control_points[ cpsize - 1 ][1] )  < DCTP_EPS ) || control_points[ 0 ] == control_points[ cpsize - 1 ] )
//       return 0;
        }
    }
    std::cerr << "still here 1 " << std::endl;
    if(osgAbs(control_points[cpsize - 1][1]) < DCTP_EPS)
    {
/// original code
//    if ( res.size() && res[ res.size() - 1 ] == e ) return 0;
        if(!res.size() || res[res.size() - 1] != e)
        {
            std::cerr << " special recording #2: " << e << std::endl;
            res.push_back(e);
//    return 0;
        }
    }
    std::cerr << "still here 2 " << std::endl;
#endif /* 0 */

    if( (miny > 0 && maxy > 0) || (miny < 0 && maxy < 0) )
        return 0;

/*
  if ( ( miny <= 0.0 && maxy <= 0.0 ) ||
       ( miny > 0.0 && maxy > 0.0 ) ) return 0;
*/
//  if ( ! ( (miny < 0.0 && maxy > 0.0) ||
//           (miny > 0.0 && maxy < 0.0) ) ) return 0;
//  std::cerr <<"still here 3 " << std::endl;
    if(maxy - miny < DCTP_EPS)
    {
        if(e - s > DCTP_EPS)
        {
            // completely on the line, so return start and end...
            if(res.size() == 0)
            {
                res.push_back(s);
            }
            res.push_back(e);
        }
        else
        {
            res.push_back( (s + e) / 2.0);   // we have a new (unique) solution, record it
        }
        return 0;
    }
/*  if( maxy - miny < DCTP_EPS )	// this should be sufficient...
//  if( control_points[ 0 ] == control_points[ cpsize - 1 ] &&
//       (e - s ) < DCTP_EPS )
  {
    if ( res.size() > 0 ) {
      if ( osgAbs( res[ res.size() - 1 ] - (s + e) / 2.0 ) > DCTP_EPS )
//           osgAbs( res[ res.size() - 1 ][0] - e ) > DCTP_MINMAX_DIFFTOL) {
//        std::cerr << " recording : " << s << std::endl;
//        std::cerr << " res.size(): " << res.size() << " res[res.size()-1]: " << res[res.size()-1] << std::endl;
        res.push_back( (s + e) / 2.0 ); // we have a new (unique) solution, record it
//      }
      return 0;
    }
    else {
//      std::cerr << " recording first: " << s << std::endl;
      res.push_back( (s + e) / 2.0 ); // this is the first solution, record it anyway
      return 0;
    }
  }*/
// we have a solution in our minmax box, subdivide and continue recursively
    BezierCurve2D newbez;

    // find first intersection of contol polygon with axis
    for(i = 1; i < cpsize; ++i)
    {
        const double &p1 =  control_points[i - 1][1];
        const double &p2 =  control_points[i][1];

        if(p1 < 0.0)
        {
            if(p2 >= 0.0)
            {
                if( (p2 == 0.0) && (i == cpsize - 1) )
                {
                    res.push_back(e);
                    return 0;
                }
                else
                {
                    mid = (i - p2 / (p2 - p1) ) / cpsize;
                    break;
                }
            }
        }
        else if(p1 > 0.0)
        {
            if(p2 <= 0.0)
            {
                if( (p2 == 0.0) && (i == cpsize - 1) )
                {
                    res.push_back(e);
                    return 0;
                }
                else
                {
                    mid = (i + p2 / (p1 - p2) ) / cpsize;
                    break;
                }
            }
        }
        else if(i == 1)
        {
            if(res.size() != 0)
            {
                if(osgAbs(res[res.size() - 1] - s) > DCTP_EPS)
                {
                    res.push_back(s); // we have a new (unique) solution, record it
                }
            }
            else
            {
                res.push_back(s); // this is the first solution, record it anyway
            }
        }
    }

    if(i == cpsize)
    {
        return 0;
    }
//  for( i = 0; i < cpsize; ++i )
//  {
//	std::cerr << control_points[ i ][1] << " ";
//  }
//  std::cerr << std::endl;

    mid = osgMin(0.999, osgMax(0.001, mid) );
//  std::cerr << mid << std::endl;
    result = subDivision(mid, newbez);
//  result = midPointSubDivision( newbez );
    if(result)
        return result;         // some error happened

    result = minMaxIntersection(res, s, s + (e - s) * mid);
//  result = minMaxIntersection( res, s, ( (s + e) / 2 ) );
    if(result)
        return result;         // some error happened

    result = newbez.minMaxIntersection(res, s + (e - s) * mid, e);
//  result = newbez.minMaxIntersection( res, ( (s + e) / 2 ), e );
    return result;
}


// calculate the signed distance between a homogenious point and a line (given with a point and a normalvector)
// returns the signed distance
double BezierCurve2D::pointLineDistancewNormal(Vec3d p, Vec2d a, Vec2d n)
{
    Vec2d t, l;
    l[0] = p[0];
    l[1] = p[1];
    t    = l - a;
//  t[0] = p[0] - a[0];
//  t[1] = p[1] - a[1];
//  std::cerr << " a.x: " << a[0] << " a.y: " << a[1] << " p.x: " << p[0] << " p.y: " << p[1] << std::endl;
    return t[0] * n[0] + t[1] * n[1];
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
int BezierCurve2D::approximate(DCTPVec2dvector &vertices, double delta)
{
    vertices.resize(0);

    // check for first degree Bezier.
    if(control_points.size() == 2)
    {
        Vec2d tmp;
        tmp[0] = control_points[0][0] / control_points[0][2];
        tmp[1] = control_points[0][1] / control_points[0][2];
        vertices.push_back(tmp);
        tmp[0] = control_points[1][0] / control_points[1][2];
        tmp[1] = control_points[1][1] / control_points[1][2];
        vertices.push_back(tmp);
        return 0;
    }

    // call recursive subdividing function
    return approximate_sub(vertices, delta);
}

#if 0
int BezierCurve2D::approximateLength(DCTPVec2dvector &vertices, double delta)
{
    vertices.resize(0);

    // check for first degree Bezier.
    std::cerr << control_points.size() << std::endl;
    if(control_points.size() == 2)
    {
        double d_dist  = sqrt( (control_points[1] - control_points[0]).squareLength() );
        int    i_steps = ( int ) ceil(d_dist / (1.5 * delta) );
        int    i_step;
        double d_param;

        std::cerr << d_dist << " - " << delta << " -> " << i_steps << " " << d_dist / (3.0 * delta) << std::endl;

        vertices.push_back(control_points[0]);

        for(i_step = 1; i_step < i_steps; ++i_step)
        {
            d_param = ( double ) i_step / ( double ) i_steps;
            vertices.push_back(control_points[0] + (control_points[1] - control_points[0]) * d_param);
        }

        vertices.push_back(control_points[1]);
        return 0;
    }

    // call recursive subdividing function
    // std::cerr << "approx..." << std::endl;
    return approximateLength_sub(vertices, delta);

}
#endif /* 0 */

int BezierCurve2D::approximate_sub(DCTPVec2dvector &vertices, double delta)
{
    double              max_error = 0;
    Vec2d               ae;
    double              aenorm;
    double              t1, t2;
    int                 i;
    int                 n = control_points.size() - 1;
    std::vector<double> t;
    Vec2d               e0, en, ei;

    for(i = 0; i <= n; i++)
    {
        t.push_back((double( n - i ) ) / n);
    }

    // first, make a copy of the cp vector, and do one
    // or more de Casteljau steps to get rid of 0 weights
    DCTPVec3dvector mycps;
    mycps = control_points;

    for(i = 0; i <= n; ++i)
    {
        unsigned int s  = mycps.size();
        bool         ok = true;

        mycps.push_back(mycps[s - 1]);
        t.push_back(t[s - 1]);

        for(int j = s; j > i; --j)
        {
            mycps[j] = (mycps[j] + mycps[j - 1]) * 0.5f;
            t[j]     = (t[j] + t[j - 1]) * 0.5f;
            if(mycps[j][2] < DCTP_EPS)
                ok = false;
        }

        if(ok)
            break;
    }

    n     = mycps.size() - 1;
    e0[0] = mycps[0][0] / mycps[0][2];
    e0[1] = mycps[0][1] / mycps[0][2];
    en[0] = mycps[n][0] / mycps[n][2];
    en[1] = mycps[n][1] / mycps[n][2];

    for(i = 0; i <= n; i++)
    {
        t1    = t[i];
        t2    = 1.0 - t[i];
        ei[0] = mycps[i][0] / mycps[i][2];
        ei[1] = mycps[i][1] / mycps[i][2];
        ae    = ei - e0 * t1 - en * t2;
//    ae[0] = control_points[ i ][0] - t1 * control_points[ 0 ][0] - t2 * control_points[ n ][0];
//    ae[1] = control_points[ i ][1] - t1 * control_points[ 0 ][1] - t2 * control_points[ n ][1];

//    std::cerr << "i: " << i << " ae.x: " << ae[0] << " ae.y: " << ae[1] << std::endl;

        aenorm = sqrt(ae[0] * ae[0] + ae[1] * ae[1]);
        if(aenorm > max_error)
            max_error = aenorm;
    }

//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ][0] << " " << control_points[ 0 ][1] << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ][0] << " " << control_points[ control_points.size() - 1 ][1] << std::endl;
    if(max_error > delta)
    {
        // we have to subdivide further
        BezierCurve2D newbez;
        int           error;
        error = midPointSubDivision(newbez);
        if(error)
            return error;
        approximate_sub(vertices, delta);
        newbez.approximate_sub(vertices, delta);
    }
    else
    {
        // this is a good enough approximation
        Vec2d tmp;
        if(!vertices.size() )
        {
            // this is the first approximation, we have to record both the
            // startpoint and the endpoint
            tmp[0] = control_points[0][0] / control_points[0][2];
            tmp[1] = control_points[0][1] / control_points[0][2];
            vertices.push_back(tmp);
            tmp[0] = control_points[control_points.size() - 1][0] / control_points[control_points.size() - 1][2];
            tmp[1] = control_points[control_points.size() - 1][1] / control_points[control_points.size() - 1][2];
            vertices.push_back(tmp);
        }
        else
        {
            // we had some subdivisions before, we only need to record the endpoint
            tmp[0] = control_points[control_points.size() - 1][0] / control_points[control_points.size() - 1][2];
            tmp[1] = control_points[control_points.size() - 1][1] / control_points[control_points.size() - 1][2];
            vertices.push_back(tmp);
        }
    }
    return 0;
}

#if 0
int BezierCurve2D::approximateLength_sub(DCTPVec2dvector &vertices, double delta)
{
    double act_error;
    double max_error = 0;
    Vec2d  ae;
    double twopower = 1;
    double aenorm;
    double t1, t2;

    int    n      = control_points.size() - 1;
    double d_dist = sqrt( (control_points[n] - control_points[0]).squareLength() );
//  std::cerr << d_dist << " - " << delta << std::endl;
    if(d_dist > delta * 1.5)
    {
        // we have to subdivide further
        bezier2dvector newbez;
        int            error;
        error = midPointSubDivision(newbez);
        if(error)
            return error;
        newbez[0].approximateLength_sub(vertices, delta);
        newbez[1].approximateLength_sub(vertices, delta);
    }
    else
    {
        for(int i = 0; i <= n; i++)
        {
            t1 = ( (double) (n - i) ) / n;
            t2 = ( (double) i) / n;
            ae = control_points[i] - control_points[0] * t1 - control_points[n] * t2;
            //    ae[0] = control_points[ i ][0] - t1 * control_points[ 0 ][0] - t2 * control_points[ n ][0];
//      ae[1] = control_points[ i ][1] - t1 * control_points[ 0 ][1] - t2 * control_points[ n ][1];

//      std::cerr << "i: " << i << " ae.x: " << ae[0] << " ae.y: " << ae[1] << std::endl;

            aenorm = sqrt(ae[0] * ae[0] + ae[1] * ae[1]);
            if(aenorm > max_error)
                max_error = aenorm;
            if(i)
                twopower *= 2;   // this is a double so it can be arbitrarily high, an int wouldn't suffice
        }

        act_error = ( (twopower - 1) / twopower) * max_error;
//  std::cerr.precision( DCTP_PRECISION );
//  std::cerr << " twopower: " << twopower << std::endl;
//  std::cerr << " act_error: " << act_error << " max_error: " << max_error << std::endl;
//  std::cerr << control_points[ 0 ][0] << " " << control_points[ 0 ][1] << std::endl;
//  std::cerr << control_points[ control_points.size() - 1 ][0] << " " << control_points[ control_points.size() - 1 ][1] << std::endl;
        if(act_error > delta)
        {
            // we have to subdivide further
            bezier2dvector newbez;
            int            error;
            error = midPointSubDivision(newbez);
            if(error)
                return error;
            newbez[0].approximateLength_sub(vertices, delta);
            newbez[1].approximateLength_sub(vertices, delta);
        }
        else
        {
            // this is a good enough approximation
            if(!vertices.size() )
            {
                // this is the first approximation, we have to record both the
                // startpoint and the endpoint
                vertices.push_back(control_points[0]);
                vertices.push_back(control_points[control_points.size() - 1]);
            }
            else
            {
                // we had some subdivisions before, we only need to record the endpoint
                vertices.push_back(control_points[control_points.size() - 1]);
            }
        }
    }
    return 0;
}
#endif /* 0 */

//! Return distance between two homogenious control points
/*!
 *  This functions returns the norm of the difference of the two control points
 *  which serves as the distance betwen the two homogenious control points.
 */
double BezierCurve2D::homogeniousDistanceSquared(Vec3d v1, Vec3d v2)
{

    return v1.dist2(v2);
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
bool BezierCurve2D::reduceDegree(double tol)
{
    unsigned int n = control_points.size() - 1;      // orig cps: 0, ..., n
    if(n < 2)
    {
        // cannot degree reduce a first degree curve
        return false;
    }
    DCTPVec3dvector b_left(n);
    DCTPVec3dvector b_right(n);
    unsigned int    i;

    // calculate b_right:
    b_right[0] = control_points[0];

    for(i = 1; i < n; ++i)
    {
        b_right[i] = (control_points[i] * n - b_right[i - 1] * i) *
                     (1.0 / double(n - i));
    }

    // calculate b_left:
    b_left[n - 1] = control_points[n];

    for(i = n - 1; i > 0; --i)
    {
        b_left[i - 1] = (control_points[i] * n - b_left[i] * (n - i)) *
                        (1.0 / double(i));
    }

    // check for introduced error:
    double quad_error = tol * tol;
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
        dist4d          = homogeniousDistanceSquared(b_right[n_half], b_left[n_half]);
        b_right[n_half] = b_left[n_half] * 0.5 + b_right[n_half] * 0.5;
    }
    else
    {
        dist4d = homogeniousDistanceSquared(control_points[n_half],
                                            0.5 * (b_right[n_half - 1] + b_left[n_half]));
    }



    //Vec3d dist;
    double minweight = b_right[0][2];

    for(i = 1; i < n; ++i)
    {
        if(minweight > b_right[i][2])
            minweight = b_right[i][2];
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


unsigned int BezierCurve2D::computeNonratApproximationDegree(double eps) const
{
    BezierCurve2D nonrat_curve;
    bool          rational = false;
    unsigned int  n        = control_points.size();
    unsigned int  i, k;
    Vec3d         nonrat_cp;
    Vec3d         d0, d1;
    BezierCurve2D deriv_curve;
    BezierCurve2D diff_curve;

    nonrat_cp[2] = 1.0;
    d0[2]        = d1[2] = 0.0;

    for(i = 0; i < n; ++i)
    {
        if(osgAbs(control_points[i][2] - 1.0) > DCTP_EPS)
        {
            rational = true;
            break;
        }
    }

    if(!rational)
    {
        return n - 1;
    }

    // end control points
    nonrat_cp[0] = control_points[0][0] / control_points[0][2];
    nonrat_cp[1] = control_points[0][1] / control_points[0][2];
    nonrat_curve.control_points.push_back(nonrat_cp);
    nonrat_cp[0] = control_points[n - 1][0] / control_points[n - 1][2];
    nonrat_cp[1] = control_points[n - 1][1] / control_points[n - 1][2];
    nonrat_curve.control_points.push_back(nonrat_cp);

    n                          = 1;
    deriv_curve.control_points = control_points;
    while(n < 15)
    {
        deriv_curve.CalculateDerivativeCurve();
        k     = deriv_curve.control_points.size() - 1;
        d0[0] = deriv_curve.control_points[0][0] / deriv_curve.control_points[0][2];
        d0[1] = deriv_curve.control_points[0][1] / deriv_curve.control_points[0][2];
        d1[0] = deriv_curve.control_points[k][0] / deriv_curve.control_points[k][2];
        d1[1] = deriv_curve.control_points[k][1] / deriv_curve.control_points[k][2];
        ++n;

        // add points to hermite curve
        nonrat_curve.AddNthHermitePoints(d0,  d1);

        // check difference
        CalculateDifferenceCurve(nonrat_curve, diff_curve);
        if(diff_curve.CalculateSupinumSquared() < eps * eps)
        {
            break;
        }
    }

    // degree might be too high by one
    nonrat_curve.reduceDegree(eps);

    return nonrat_curve.control_points.size() - 1;
}


void BezierCurve2D::CalculateDerivativeCurve()
{
    unsigned int        n;
    unsigned int        i;
    BezierCurve2D       deriv_curve;
    BezierCurve2D       temp_curve;
    std::vector<double> squared_weight;
    bool                rational = false;

    // check for single point curves
    n = control_points.size();
    if(n == 1)
    {
        control_points[0] = Vec3d(0.0, 0.0, 1.0);
    }

    // deriv: P'(t)/w'(t)
    CalculatePolyDerivCurve(deriv_curve);

    // check for non-rational curves
    for(i = 0; i < n; ++i)
    {
        if(osgAbs(control_points[i][2] - 1.0) > DCTP_EPS)
        {
            rational = true;
            break;
        }
    }

    if(!rational)
    {
        // deriv: P'(t)/1
        control_points = deriv_curve.control_points;

        for(i = 0; i < n - 1; ++i)
        {
            control_points[i][2] = 1.0;
        }

        return;
    }

    // deriv: P'(t)w(t) / w(t)w'(t), temp: P(t)w'(t) / w(t)w'(t)
    temp_curve.control_points = control_points;
    temp_curve.CrossMultiply(deriv_curve);

    // deriv: ( P'(t)w(t) - P(t)w'(t) ) / 1
    for(i = 0; i < deriv_curve.control_points.size(); ++i)
    {
        deriv_curve.control_points[i]   -= temp_curve.control_points[i];
        deriv_curve.control_points[i][2] = 1.0;
    }

    // elevate degree from 2n-1 to 2n
    deriv_curve.DegreeElevate();

    // deriv: ( P'(t)w(t) - P(t)w'(t) )~ / w(t)^2
    SquareWeight(squared_weight);

    for(i = 0; i < deriv_curve.control_points.size(); ++i)
    {
        deriv_curve.control_points[i][2] = squared_weight[i];
    }

    control_points = deriv_curve.control_points;
}


void BezierCurve2D::CalculateNOverIVector(std::vector<double> &NOverI, const unsigned int n) const
{
    unsigned int i;

    NOverI.resize(n + 1);
    NOverI[0] = NOverI[n] = 1.0;

    for(i = 1; i <= n / 2; ++i)
    {
        NOverI[i]     = NOverI[i - 1] * (n + 1 - i) / i;
        NOverI[n - i] = NOverI[i];
    }
}


void BezierCurve2D::CalculatePolyDerivCurve(BezierCurve2D &DerivativeCurve) const
{
    const unsigned int n = control_points.size() - 1;
    unsigned int       i;

    DerivativeCurve.control_points.resize(n);

    for(i = 0; i < n; ++i)
    {
        DerivativeCurve.control_points[i] = (control_points[i + 1] - control_points[i]) * n;
    }
}


void BezierCurve2D::CrossMultiply(BezierCurve2D &OtherCurve)
{
    std::vector<Vec3d>  p_wo;
    std::vector<Vec3d>  po_w;
    const unsigned int  n  = control_points.size() - 1;
    const unsigned int  m  = OtherCurve.control_points.size() - 1;
    const unsigned int  nm = n + m;
    unsigned int        i;
    unsigned int        j;
    unsigned int        k;
    std::vector<double> i_over_n;
    std::vector<double> j_over_m;
    std::vector<double> k_over_nm;

    // calculate a over b arrays
    CalculateNOverIVector(i_over_n, n);
    CalculateNOverIVector(j_over_m, m);
    CalculateNOverIVector(k_over_nm, nm);

    // init
    p_wo.resize(nm + 1);
    po_w.resize(nm + 1);

    for(k = 0; k <= nm; ++k)
    {
        p_wo[k] = po_w[k] = Vec3d(0.0, 0.0, 0.0);
    }

    // cross multiply (leave out Bernstein factor)
    for(i = 0; i <= n; ++i)
    {
        k = i;

        for(j = 0; j <= m; ++j)
        {
            p_wo[k] += control_points[i] * OtherCurve.control_points[j][2] * i_over_n[i] * j_over_m[j];
            po_w[k] += OtherCurve.control_points[j] * control_points[i][2] * i_over_n[i] * j_over_m[j];
            ++k;
        }
    }

    // divide by new Bernstein factor
    for(k = 0; k <= nm; ++k)
    {
        p_wo[k] /= k_over_nm[k];
        po_w[k] /= k_over_nm[k];
    }

    control_points            = p_wo;
    OtherCurve.control_points = po_w;
}


void BezierCurve2D::SquareWeight(std::vector<double> &Squared) const
{
    const unsigned int  n  = control_points.size() - 1;
    const unsigned int  nn = n * 2;
    unsigned int        i;
    unsigned int        j;
    unsigned int        k;
    std::vector<double> i_over_n;
    std::vector<double> k_over_nn;

    // calculate a over b arrays
    CalculateNOverIVector(i_over_n, n);
    CalculateNOverIVector(k_over_nn, nn);

    // init
    Squared.resize(nn + 1);

    for(k = 0; k <= nn; ++k)
    {
        Squared[k] = 0.0;
    }

    // cross multiply (leave out Bernstein factor)
    for(i = 0; i <= n; ++i)
    {
        for(j = 0; j <= n; ++j)
        {
            k           = i + j;
            Squared[k] += control_points[i][2] * control_points[j][2] * i_over_n[i] * i_over_n[j];
        }
    }

    // divide by new Bernstein factor
    for(k = 0; k <= nn; ++k)
    {
        Squared[k] /= k_over_nn[k];
    }
}


double BezierCurve2D::CalculateSupinumSquared() const
{
    const unsigned int n = control_points.size();
    unsigned int       i;
    Vec3d              curr;
    double             sup;
    double             diff;

    // generalized convex hull property
    sup = (control_points[0][0] * control_points[0][0] + control_points[0][1] * control_points[0][1])
          / (control_points[0][2] * control_points[0][2]);

    for(i = 1; i < n; ++i)
    {
        curr = (control_points[i] + control_points[i - 1]) * 0.5;
        diff = (curr[0] * curr[0] + curr[1] * curr[1]) / (curr[2] * curr[2]);
        if(diff > sup)
        {
            sup = diff;
        }
    }

    diff = (control_points[n - 1][0] * control_points[n - 1][0] + control_points[n - 1][1] * control_points[n - 1][1])
           / (control_points[n - 1][2] * control_points[n - 1][2]);
    if(diff > sup)
    {
        sup = diff;
    }

//    std::cerr << " CalculateSupinumSquared::sup: " << sup << std::endl;
    return sup;
}


void BezierCurve2D::CalculateDifferenceCurve(const BezierCurve2D &Other, BezierCurve2D &Diff) const
{
    BezierCurve2D temp_curve;
    unsigned int  i;
    bool          rational = false;

    Diff.control_points       = control_points;
    temp_curve.control_points = Other.control_points;

    // check for non-rational curves
    for(i = 0; i < control_points.size(); ++i)
    {
        if(osgAbs(control_points[i][2] - 1.0) > DCTP_EPS)
        {
            rational = true;
            break;
        }
    }

    if(!rational)
    {
        for(i = 0; i < temp_curve.control_points.size(); ++i)
        {
            if(osgAbs(temp_curve.control_points[i][2] - 1.0) > DCTP_EPS)
            {
                rational = true;
                break;
            }
        }
    }

    if(rational)
    {
        // rational curvel -> cross multiply with denominator
        Diff.CrossMultiply(temp_curve);
    }
    else
    {
        // polynomial curves -> elevate to same degree
        while(Diff.control_points.size() < temp_curve.control_points.size() )
        {
            Diff.DegreeElevate();
        }
        while(temp_curve.control_points.size() < control_points.size() )
        {
            temp_curve.DegreeElevate();
        }
    }

    for(i = 0; i < Diff.control_points.size(); ++i)
    {
        Diff.control_points[i][0] -= temp_curve.control_points[i][0];
        Diff.control_points[i][1] -= temp_curve.control_points[i][1];
    }
}


void BezierCurve2D::DegreeElevate()
{
    const unsigned int n = control_points.size();
    unsigned int       i;

    control_points.push_back(control_points[n - 1]);

    for(i = n - 1; i != 0; --i)
    {
        double alpha  = i / double(n);
        double malpha = 1.0 - alpha;

        control_points[i] = control_points[i - 1] * alpha + control_points[i] * malpha;
    }
}


void BezierCurve2D::AddNthHermitePoints(Vec3d d0, Vec3d d1)
{
    const unsigned int  n = control_points.size() / 2;
    unsigned int        i;
    std::vector<double> n_over_i;
    int                 sign = 1;
    double              fact;

    DegreeElevate();
    DegreeElevate();

    fact = 1.0;

    for(i = control_points.size() - 1; i >= control_points.size() - n; --i)
    {
        fact *= i;
    }

    d1 /= fact;
    d0 /= fact;

    // TODO: CHECK!!!
    CalculateNOverIVector(n_over_i, n);

    for(i = 0; i <= n; ++i)
    {
        if(i > 0)
            d0 -= control_points[n - i]      * (n_over_i[i] * sign);
        if(i < n)
            d1 -= control_points[2 * n + 1 - i] * (n_over_i[i] * sign);
        sign = -sign;
//        std::cerr<<"i: " << i << " d1: " << d1 << std::endl;
    }

    d1 *= -sign;

    // insert
//    std::cerr<<"bah0: "<< d0 << std::endl;
    control_points[n] = d0;
//    std::cerr<<"bah1: "<< d1 << std::endl;
    control_points[n + 1] = d1;
//    std::cerr<<"bah3"<<std::endl;
//    for ( i = 0; i < control_points.size(); ++i )
//    {
//        std::cerr<<"AddNthHermitePoints:: cps[i]: " << control_points[i] << std::endl;
//    }

}
