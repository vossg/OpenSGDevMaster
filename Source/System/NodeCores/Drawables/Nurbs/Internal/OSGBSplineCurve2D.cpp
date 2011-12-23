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
#include "OSGBSplineCurve2D.h"

OSG_USING_NAMESPACE

#ifdef _DEBUG
 #ifdef WIN32
  #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
 #endif
#endif

const char BSplineCurve2D::ff_const_1[] = "BEGINBSPLINECURVE2D";
const char BSplineCurve2D::ff_const_2[] = "DIMENSION";
const char BSplineCurve2D::ff_const_3[] = "NUMBEROFCONTROLPOINTS";
const char BSplineCurve2D::ff_const_4[] = "BEGINRATIONALBSPLINECURVE2D";

int BSplineCurve2D::CheckKnotPoints(const DCTPdvector& knots, int dim)
{
    //now check knotvector whether it has
    //(a,a,....a, ......., b,b,....b)
    // |-dim+1-|           |-dim+1-|
    //structure

    DCTPdvector::size_type max_index  = knots.size() - 1;
    double                 test_begin = knots[0], test_end = knots[max_index];

    for(DCTPdvector::size_type i = 1; i < static_cast<unsigned int>(dim) + 1; ++i)
        if(knots[i] != test_begin || knots[max_index - i] != test_end)
            return -1;                                                                //FIXME: double comparison ?!

    return 0;
}

int BSplineCurve2D::deleteBezierKnot(double k)
{
    DCTPdvector knots = basis_function.getKnotVector();

    if(k >= knots[knots.size() - 1])
        return -1;                                 // knot is too high
    if(k <= knots[0])
        return -2;                  // knot is too low

    DCTPdvector::size_type i    = 0;
    int                    mult = 0;
    while(knots[i] <= k)
    {
        if(knots[i] == k)
            mult++;
        i++;
    }
    if(mult < dimension + 1)
        return -2;                       // knot doesn't have enough multiplicity
    i--;

    // delete from knotvector
    knots.erase(knots.begin() + i);
    // set new knot vector
    basis_function.setKnotVector(knots);
    // delete control point corresponding to just deleted knot
    control_points.erase(control_points.begin() + i - dimension);
    return 0;
}


//setup functions
int BSplineCurve2D::setKnotsAndDimension(const DCTPdvector& knots, int dim)
{
    if(dim < 1)
        return -1;          //invalid dimension

    DCTPdvector::size_type max_index = knots.size() - 1;
    if(max_index < 3)
        return -2;                //here's an implicit check fer structure, see below

    if(CheckKnotPoints(knots, dim) )
        return -3;

    dimension = dim;
    if(basis_function.setKnotVector(knots) )
        return -4;                                        //error in BSplineBasisFunction.setKno...

    return 0;
}

void BSplineCurve2D::setControlPointVector(const DCTPVec3dvector &cps)
{
    control_points = cps;
}

//query functions
void BSplineCurve2D::getParameterInterval(double &minpar, double &maxpar)
{
    basis_function.getParameterInterval(minpar, maxpar);
}

//I/O facilities - FIXME: read( char *fname ), etc. missing
int BSplineCurve2D::read(std::istream &infile)
{
    //FIXME: maybe we need more checks!!!
    char txtbuffer[256];
    bool israt       = false;
    bool isemptyknot = false;


    infile.getline(txtbuffer, 255);   //read line
    if(strcmp(txtbuffer, ff_const_1) &&
       strcmp(txtbuffer, ff_const_4))
    {
        return -1; //bad file format
    }
    if(!strcmp(txtbuffer, ff_const_4))
    {
        israt = true;
    }
    infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
    if(strcmp(txtbuffer, ff_const_2) )
        return -1;                                     //yeah, bad file format again

    infile >> dimension >> std::ws;
    if(dimension < 1)
        return -2;                  //ah, bad dimension

    int knoterr = basis_function.read(infile);
    if(knoterr == -3)  // FIXME: hardwired val...
    {
        isemptyknot = true;
    }
    else if(knoterr)
    {
        return -3; //error reading basis function
    }
    if(CheckKnotPoints(basis_function.getKnotVector(), dimension) )
        return -4;

    infile >> txtbuffer; //FIXME: error prone: too long string causes problem!!!
    if(strcmp(txtbuffer, ff_const_3) )
        return -1;                                    //bad file format once again

    DCTPVec3dvector::size_type num_of_cps;
    infile >> num_of_cps >> std::ws;
    if(num_of_cps < 1)
        return -5;                   //too few control points
    control_points.resize(num_of_cps);   //FIXME: whatif not enoght memory?

    for(DCTPdvector::size_type i = 0; i < num_of_cps; ++i)
    {
        Vec3d cp;
        if(israt)
        {
            infile >> cp[0] >> cp[1] >> cp[2] >> std::ws;
        }
        else
        {
            infile >> cp[0] >> cp[1] >> std::ws;
            cp[2] = 1.0;
        }
        control_points[i] = cp;   //FIXME: ya see, we need ERROR CHECKS!!!
    }

    if(isemptyknot)
    {
        return -10;
    }

    return 0;
}

int BSplineCurve2D::write(std::ostream &outfile)
{
    bool                   israt = false;
    DCTPdvector::size_type i     = 0;

    for(i = 0; i < control_points.size(); ++i)
    {
        if(osgAbs(control_points[i][2] - 1.0) > DCTP_EPS)
        {
            israt = true;
            break;
        }
    }

    //FIXME: maybe we need more checks!!!
    outfile.precision(DCTP_PRECISION);
    if(!israt)
    {
        outfile << ff_const_1 << std::endl;
    }
    else
    {
        outfile << ff_const_4 << std::endl;
    }
    outfile << ff_const_2 << " " << dimension << std::endl;
    basis_function.write(outfile);
    DCTPdvector::size_type num_of_cps = control_points.size();
    outfile << ff_const_3 << " " << num_of_cps << std::endl;

    for(i = 0; i < num_of_cps; ++i)
    {
        Vec3d cp = control_points[i];
        if(!israt)
        {
            outfile << cp[0] << " " << cp[1] << std::endl;
        }
        else
        {
            outfile << cp[0] << " " << cp[1] << " " << cp[2] << std::endl;

        }
    }

    return 0;
}


//some REAL functionality
Vec2d BSplineCurve2D::compute(double t, int &error)
{
    //FIXME: verification before goin' into computation!!
    double *pd_n;
    int     span = basis_function.computeAllNonzero(t, dimension, pd_n);
    Vec2d   result(0.0, 0.0);
    Vec3d   rat_res(0.0, 0.0, 0.0);
    if(span < 0)
    {
        error = span;
        return result; //error occured in BSplineBasisFunction.computeAll...
    }

    for(int i = 0; i <= dimension; ++i)
    {
        rat_res = rat_res + control_points[span - dimension + i] * pd_n[i];
    }

    delete[]  pd_n;
    result[0] = rat_res[0] / rat_res[2];
    result[1] = rat_res[1] / rat_res[2];
    return result;
}

//insert knot. Returns < 0 on error, otherwise 0.
int BSplineCurve2D::insertKnot(double k)
{
    DCTPdvector knots = basis_function.getKnotVector();
    int         span  = basis_function.insertKnot(k);
    if(span < 0)
        return span;             // some error happened

    DCTPVec3dvector newcps;
    newcps.resize(control_points.size() + 1);
    DCTPVec3dvector::size_type i;

    for(i = 0; i <= static_cast<unsigned int>(span) - dimension; i++)
    {
        newcps[i] = control_points[i];
    }

    for(i = span - dimension + 1; i <= static_cast<unsigned int>(span); i++)
    {
        double alpha;
        if(knots[i + dimension] != knots[i])
        {
            alpha = (k - knots[i]) / (knots[i + dimension] - knots[i]);
        }
        else
        {
            alpha = 0;
        }
        newcps[i] = control_points[i] * alpha + control_points[i - 1] * (1 - alpha);
    }

    for(i = span + 1; i < newcps.size(); i++)
    {

        newcps[i] = control_points[i - 1];
    }

    control_points = newcps;
    return 0;
}

int BSplineCurve2D::makeBezier(bezier2dvector &beziers, DCTPdvector &pars)
{
    double firstknot, lastknot;
    basis_function.getParameterInterval(firstknot, lastknot);
    DCTPdvector     knots     = basis_function.getKnotVector();
    DCTPdvector     origknots = knots; // backup original curve characteristics
    DCTPVec3dvector origcps   = control_points; // same here
    double          prevknot  = firstknot;
    int             mult      = 0;
    int             err;
    unsigned int    i;

    for(i = 1; i < knots.size(); i++)
    {
        double actk = knots[i];
        if(actk == prevknot)
            mult++;
        else
        {
            for(int j = mult + 1; j < dimension; j++)    //each interior knot must have the multiplicity of dimension-1
            { //each interior knot must have the multiplicity of dimension -1
                err = insertKnot(prevknot);
                if(err)
                    return err;        // some error happened during insertKnot
            }

            if(prevknot != firstknot && prevknot != lastknot)
            {
                for(int j = mult; j > dimension - 1; j--)
                {
                    err = deleteBezierKnot(prevknot);
                    if(err)
                        return err;        // some error happened during deleteBezierKnot
                }
            }
            mult = 0;
        }
        prevknot = actk;
    }

    // now do the actual conversation into n. bezier segments
    knots = basis_function.getKnotVector(); // FIXME: it could be more efficient.
    unsigned int num_of_beziers = (UInt32(knots.size()) - 2) / dimension - 1;
    if( (num_of_beziers * dimension + 2) != knots.size() - dimension)
    {
        basis_function.setKnotVector(origknots);
        control_points = origcps;
        return -5;
    }

    beziers.resize(num_of_beziers);
    pars.resize(num_of_beziers + 1);

    for(i = 0; i < num_of_beziers + 1; i++)
        pars[i] = knots[1 + dimension * i];

    DCTPVec3dvector           beziercps(dimension + 1);
    Vec3d                     firstcp;
    bool                      degenerate;
    bezier2dvector::size_type bezind              = 0;
    bezier2dvector::size_type orig_num_of_beziers = num_of_beziers;

    for(i = 0; i < orig_num_of_beziers; i++)
    {
        firstcp    = control_points[i * dimension + 0];
        degenerate = true;

        for(DCTPVec3dvector::size_type j = 0;
            j < static_cast<unsigned int>(dimension) + 1; j++)
        {
            beziercps[j] = control_points[i * dimension + j];
            if(degenerate)
                if(DCTPVecIsNotEqual(firstcp, beziercps[j]) )
                {
                    degenerate = false;
                }
        } // j

        if(degenerate)
        {
            num_of_beziers--;
            bezier2dvector::iterator bi = beziers.begin() + bezind;  // + i ???
            DCTPdvector::iterator    pi = pars.begin() + bezind;
            beziers.erase(bi); beziers.resize(num_of_beziers);
            pars.erase(pi); pars.resize(num_of_beziers + 1);
//           std::cerr << "Ignoring degenerate curve... " << std::endl;
        }
        else
        {
            beziers[bezind++].setControlPointVector(beziercps);
        }
    } // i

    // restore original curve
    basis_function.setKnotVector(origknots);
    control_points = origcps;
    return 0;
}
