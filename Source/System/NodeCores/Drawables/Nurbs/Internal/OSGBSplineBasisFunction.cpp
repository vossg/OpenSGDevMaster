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
#include "OSGBSplineBasisFunction.h"


OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

const char BSplineBasisFunction::ff_const_1[] = "BEGINBSPLINEBASISFUNCTION";
const char BSplineBasisFunction::ff_const_2[] = "NUMBEROFKNOTS";
const char BSplineBasisFunction::ff_const_3[] = "KNOTS";


//setup methods
int BSplineBasisFunction::setKnotVector(const DCTPdvector &k)
{
    int err;
    if(k.size() < 2)
        return -1;               //one knot doesn't make any knotspan
    // Commented out because of iv2tso,
    // bailed out when encountering degenerate curves (empty knotspan)
    // found in some files

    err = CheckKnotPoints(k);
    if(err)
    {
//       std::cerr<<"setKnotVector: err: " << err << std::endl;
//       std::cerr<<"beginknotvec: " << k[0] << std::endl;
//       std::cerr<<"endknotvec: " << k[k.size()-1] << std::endl;
//       std::cerr<<"lengthofknotvec: " << k.size() << std::endl;
        return -2; //bad knot series
    }
    knots = k;
    return 0;
}

//query methods
// inserts a knot. Returns the (original) span index of the new knot inserted.
// or -1 on error.
int BSplineBasisFunction::insertKnot(double k)
{
    if(k < knots[0] || k > knots[knots.size() - 1])
        return -1;
    int                    span = findSpan(k);
    DCTPdvector::size_type i;
    i = 0;
    while(knots[i] < k && i < knots.size())
        i++;
    knots.insert(knots.begin() + i, k);    // FIXME: what if it doesn't fit??? exception?
    return span; // FIXME: maybe it would be more efficient to calculate it from i?
}

void BSplineBasisFunction::getParameterInterval(double &minpar, double &maxpar)
{
    if(knots.size() < 1)
    {
        minpar = 1.0; maxpar = 0.0; return;
    }
    else
    {
        minpar = knots[0]; maxpar = knots[knots.size() - 1]; return;
    }
}

//I/O support - FIXME: read( char *fname ) outta be supported , etc
int BSplineBasisFunction::read(std::istream &infile)
{
    //FIXME: maybe we need more checks!!!
    char txtbuffer[256];

    infile.getline(txtbuffer, 255); //read line

    if(strcmp(txtbuffer, ff_const_1) )
        return -1;                                  //bad file format

    infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!

    if(strcmp(txtbuffer, ff_const_2) )
        return -1;                                   //yeah, bad file format again

    DCTPdvector::size_type num_of_knots;
    infile >> num_of_knots;
    if(num_of_knots < 2)
        return -2;                   //ah, bad number of knots
    knots.resize(num_of_knots); //FIXME: whatif noe enoght memory?

    infile >> std::ws >> txtbuffer; //skip whitespaces and read string
    if(strcmp(txtbuffer, ff_const_3) )
        return -1;
//  std::cerr<<"numofknots: " << num_of_knots << std::endl;

    for(DCTPdvector::size_type i = 0; i < num_of_knots; ++i)
    {
        infile >> knots[i];   //FIXME: ya see, we need ERROR CHECKS!!!
//	  std::cerr << knots[ i ] << " ";
    }

    int ckp = CheckKnotPoints(knots);
    if(ckp == -1)
        return -3;           // empty knot series
    else if(ckp)
        return -4;          // wrong knot series

    return 0;

}

int BSplineBasisFunction::write(std::ostream &outfile)
{

    //FIXME: ya outta do some f***n' ERRORTESTIN'!!!!
    outfile.precision(DCTP_PRECISION);
    outfile << ff_const_1 << std::endl;

    DCTPdvector::size_type num_of_knots = knots.size();
    outfile << ff_const_2 << " " << num_of_knots << std::endl << ff_const_3 << " ";

    for(DCTPdvector::size_type i = 0; i < num_of_knots; ++i)
        outfile << knots[i] << " ";

    outfile << std::endl;
    return 0;
}

//some REAL functionality
double BSplineBasisFunction::compute(double u, int i, int p)
{
//u - parameter value, knots[0] <= u <= knots[ m ]
//i,p - the ith p-dimensional basis function should be computed
    unsigned int j;

    if(knots.size() < 1)
        return -1.0;                   //the knots are not set up
    DCTPdvector::size_type m = knots.size() - 1; //m: number of knots
    if(u < knots[0] || u > knots[m])
        return -2.0;                                   //invalid u
    if(p >= m)
        return -3.0;         //this high dimension is not defined
    if(i < 0 || i >= m - p)
        return -4.0;                      //i is invalid

    if( (i == 0 && u == knots[0]) ||
        (i == m - p - 1 && u == knots[m]) )
        return 1.0;                                        //special cases
    if(u < knots[i] || u >= knots[i + p + 1])
        return 0.0;                                            //local support property

    DCTPdvector n(p + 1);

    for(j = 0; j < p + 1; ++j) //setup 0th degree basis functionsi
        if(knots[i + j] <= u && u < knots[i + j + 1])
            n[j] = 1.0;
        else
            n[j] = 0.0;

    for(j = 1; j < p + 1; ++j)
    {
        for(DCTPdvector::size_type k = 0; k < p + 1 - j; ++k)
        {
            double den = knots[k + i + j] - knots[k + i];
            double left;
            if(den < DCTP_EPS) //don't divide by 0!
                left = 0.0;
            else
                left = (u - knots[k + i]) / den * n[k];
            den = knots[k + i + j + 1] - knots[k + i + 1];
            double right;
            if(den < DCTP_EPS) //don't divide by 0!
                right = 0.0;
            else
                right = (knots[k + i + j + 1] - u) / den * n[k + 1];
            n[k] = left + right;
        }
    }

    return n[0];
}

int BSplineBasisFunction::computeDersBasisFuns(double dU, int iP, double **&rppdDers, int iDepth)
{
    int      i_span;
    double **ppd_ndu;
    int      i_j;
    double  *pd_left;
    double  *pd_right;
    double   d_saved;
    int      i_r;
    double   d_temp;
    int      i_s1;
    int      i_s2;
    double **ppd_a;
    int      i_k;
    int      i_rk;
    int      i_pk;
    int      i_j1;
    int      i_j2;

    if(knots.size() < 1)
    {
        return -1; //the knots are not set up
    }
    i_span = findSpan(dU);
    if(i_span < 0)
    {
        return -2; //invalid u
    }
    if(i_span - iP < 0)
    {
        return -3; //invalid p
    }
    if(iP < 0)
    {
        return -4; // negative p
    }

    ppd_ndu  = new double*[iP + 1];
    pd_left  = new double[iP + 1];
    pd_right = new double[iP + 1];
    ppd_a    = new double*[2];

//	vvd_ndu.resize( iP + 1 );
    for(i_j = 0; i_j <= iP; ++i_j)
    {
        ppd_ndu[i_j] = new double[iP + 1];
//		vvd_ndu[ i_j ].resize( iP + 1 );
    }

//	vd_left.resize( iP + 1 );
//	vd_right.resize( iP + 1 );
    rppdDers = new double*[iDepth + 1];

//	rvvdDers.resize( iDepth + 1 );
    for(i_j = 0; i_j < iDepth + 1; ++i_j)
    {
        rppdDers[i_j] = new double[iP + 1];
//		rvvdDers[ i_j ].resize( iP + 1 );
    }

//	vvd_a.resize( 2 );
    ppd_a[0] = new double[iP + 1];
//	vvd_a[ 0 ].resize( iP + 1 );
    ppd_a[1] = new double[iP + 1];
//	vvd_a[ 1 ].resize( iP + 1 );

    ppd_ndu[0][0] = 1.0;

    for(i_j = 1; i_j <= iP; ++i_j)
    {
        const int ci_j1    = i_j - 1;
        double   *pd_ndujr = ppd_ndu[i_j];

        pd_left[i_j]  = dU - knots[i_span - ci_j1];
        pd_right[i_j] = knots[i_span + i_j] - dU;
        d_saved       = 0.0;

        for(i_r = 0; i_r < i_j; ++i_r)
        {
            const int ci_r1 = i_r + 1;
            const int ci_jr = i_j - i_r;

            (*pd_ndujr)       = pd_right[ci_r1] + pd_left[ci_jr];
            d_temp            = ppd_ndu[i_r][ci_j1] / (*pd_ndujr);
            ppd_ndu[i_r][i_j] = d_saved + pd_right[ci_r1] * d_temp;
            d_saved           = pd_left[ci_jr] * d_temp;
            ++pd_ndujr;
        }

        ppd_ndu[i_j][i_j] = d_saved;
    }

    for(i_j = 0; i_j <= iP; ++i_j)
    {
        rppdDers[0][i_j] = ppd_ndu[i_j][iP];
    }

    for(i_r = 0; i_r <= iP; ++i_r)
    {
        i_s1        = 0;
        i_s2        = 1;
        ppd_a[0][0] = 1.0;

        for(i_k = 1; i_k <= iDepth; ++i_k)
        {
            d_temp = 0.0;
            i_rk   = i_r - i_k;
            i_pk   = iP - i_k;
            if(i_r >= i_k)
            {
                d_temp         = ppd_a[i_s1][0] / ppd_ndu[i_pk + 1][i_rk];
                ppd_a[i_s2][0] = d_temp;
                d_temp        *= ppd_ndu[i_rk][i_pk];
            }
            if(i_rk >= -1)
            {
                i_j1 = 1;
            }
            else
            {
                i_j1 = -i_rk;
            }
            if(i_r - 1 <= i_pk)
            {
                i_j2 = i_k - 1;
            }
            else
            {
                i_j2 = iP - i_r;
            }

            for(i_j = i_j1; i_j <= i_j2; ++i_j)
            {
                ppd_a[i_s2][i_j] = (ppd_a[i_s1][i_j] - ppd_a[i_s1][i_j - 1])
                                   / ppd_ndu[i_pk + 1][i_rk + i_j];
                d_temp += ppd_a[i_s2][i_j] * ppd_ndu[i_rk + i_j][i_pk];
            }

            if(i_r <= i_pk)
            {
                ppd_a[i_s2][i_k] = -ppd_a[i_s1][i_k - 1] / ppd_ndu[i_pk + 1][i_r];
                d_temp          += ppd_a[i_s2][i_k] * ppd_ndu[i_r][i_pk];
            }
            rppdDers[i_k][i_r] = d_temp;
            i_j                = i_s1;
            i_s1               = i_s2;
            i_s2               = i_j;
        }
    }

    i_r = iP;

    for(i_k = 1; i_k <= iDepth; ++i_k)
    {
        for(i_j = 0; i_j <= iP; ++i_j)
        {
            rppdDers[i_k][i_j] *= i_r;
        }

        i_r *= (iP - i_k);
    }

    //clean up allocated memory
    for(i_j = 0; i_j <= iP; ++i_j)
    {
        delete[]  ppd_ndu[i_j];
    }

    delete[]  ppd_a[0];
    delete[]  ppd_a[1];
    delete[]  ppd_ndu;
    delete[]  pd_left;
    delete[]  pd_right;
    delete[]  ppd_a;

    return i_span;
}

int BSplineBasisFunction::computeAllNonzero(double u, int p, double *&rpd_n)
{
    if(knots.size() < 1)
        return -1;                   //the knots are not set up
    int i = findSpan(u);
    if(i < 0)
        return -2;        //invalid u

//FIXME
//  if ( u < 0 ) return -2; //invalid u
    if(i - p < 0)
        return -3;            //invalid p
    rpd_n = new double[p + 1];
//  n.resize( p + 1 );
    rpd_n[0] = 1.0;
    double *pd_left  = new double[p + 1];
    double *pd_right = new double[p + 1];

//  DCTPdvector left( p + 1), right( p + 1 );
//  for( DCTPdvector::size_type j = 1; j <= p; ++j ) {
    for(int j = 1; j <= p; ++j)
    {
        pd_left[j]  = u - knots[i + 1 - j];
        pd_right[j] = knots[i + j] - u;
        double saved = 0.0;

        for(DCTPdvector::size_type r = 0; r < j; ++r)
        {
            double temp = rpd_n[r] / (pd_left[j - r] + pd_right[r + 1]);
            rpd_n[r] = saved + temp * pd_right[r + 1];
            saved    = temp * pd_left[j - r];
        }

        rpd_n[j] = saved;
    }

    delete[]  pd_left;
    delete[]  pd_right;

    return i;
}

int BSplineBasisFunction::CheckKnotPoints(const DCTPdvector &k)
{
    if(osgAbs(k[0] - k[k.size() - 1]) < DCTP_EPS)
    {
        std::cerr << "BSplineBasisFunction::CheckKnotPoints: first and last knot are equal: " << k[0] << std::endl;
        return -1; //at least two different knots define a knotspan! FIXME: double == double ???
    }
    DCTPdvector::const_iterator i    = k.begin();
    double                      temp = *i; i++;
    while(i != k.end() )
    {
        if(temp > *i)
        {
            std::cerr << "BSplineBasisFunction::CheckKnotPoints: illegal consecutive knots: " << temp << " " << *i << std::endl;
            return -2;
        }
        temp = *i;
        i++;
    }
    return 0;
}

int BSplineBasisFunction::findSpan(double &u)
{
    DCTPdvector::size_type n = knots.size() - 1;

    if(u < knots[0] || u > knots[n])
    {
        //FIXME:
        if(u < knots[0])
        {
            u = knots[0];
//        return 0;
        }
        else
        {
            u = knots[n];
//        return  n;
        }
//    return -1; //invalid u
    }

/*    for( unsigned int ui_test = 0; ui_test <= n; ++ui_test )
    {
        std::cerr << knots[ ui_test ] << " ";
    }
    std::cerr << std::endl;*/

    while(osgAbs(knots[n] - knots[n - 1]) < DCTP_EPS)
        --n;                                                        //FIXME: double ==double ???
    --n; //n holds the index of the last different knot before the equal ones at the of the knot vector

    while(u < knots[n])
        --n;
    return n;
#if 0
    if(osgAbs(u - knots[n + 1]) < DCTP_EPS)
        return n;                                            //special case: u is at the end FIXME: double ==double ???
    DCTPdvector::size_type low = 0;
    while(osgAbs(knots[low] - knots[low + 1]) < DCTP_EPS)
        ++low;                                                            //FIXME: double ==double ???
    DCTPdvector::size_type high = n + 1;
    //now get span with a binary search
    DCTPdvector::size_type mid = (low + high) / 2;
    while(u < knots[mid] || u >= knots[mid + 1])
    {
//	  std::cerr << knots[ low ] << " " << knots[ mid ] << " " << knots[ high ] << std::endl;
        if(u < knots[mid])
            high = mid;
        else
            low = mid;
        mid = (low + high) / 2;
    }
    return mid;
#endif
}
