/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGMATHUTILS_H_
#define _OSGMATHUTILS_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGVector.h"

#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name linear euqation systems                                      */
/*! \{                                                                 */

// Solves a system of linear equations of: 2 equations and 2 variables
//
//  Equation AX = B
// A = [ A11  A12 ]
//     [ A21  A22 ]
// X = [ R1   R2  ]
// B = [ B1   B2  ]
//
// The function returns -1 if there are an infinite number of solutions,
//  0 for 0 solutions,
//  1 for 1 solution

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
Int8 solveLinearSystem2(FloatTypeT  A11, 
                        FloatTypeT  A12, 
                        FloatTypeT  A21, 
                        FloatTypeT  A22, 

                        FloatTypeT  B1, 
                        FloatTypeT  B2, 

                        FloatTypeT &X1, 
                        FloatTypeT &X2)
{
	//Get the determinant of A
	FloatTypeT DetA = (A11 * A22) - (A12 * A21);

	if(DetA == 0.f)
	{
		//There is not a unique solution
		if(osgIsEqual(A21/A11, A22/A12, static_cast<FloatTypeT>(0.000000001)) &&
           osgIsEqual(A21/A11, B2 /B1 , static_cast<FloatTypeT>(0.000000001)))
		{
			//There are an infinite number of solutions
			return -1;
		}
		else
		{
			//There are no solutions
			return 0;
		}
	}
	
	FloatTypeT DetA1 = (B1 * A22) - (B2 * A12);
	
	FloatTypeT DetA2 = (A11 * B2) - (A21 * B1);


	X1 = DetA1 / DetA;
	X2 = DetA2 / DetA;

	return 1;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name intersections                                                */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template<class ValueTypeT, UInt32 SizeI> inline
Int8 intersectLines(const OSG::Point <ValueTypeT, SizeI> &p1,
                    const OSG::Vector<ValueTypeT, SizeI> &v1,

                    const OSG::Point <ValueTypeT, SizeI> &p2,
                    const OSG::Vector<ValueTypeT, SizeI> &v2,

                          ValueTypeT                     &t1, 
                          ValueTypeT                     &t2,
                          OSG::Point<ValueTypeT, SizeI> &intersect)
{

	switch(solveLinearSystem2( v1.x(),
                              -v2.x(),
                               v1.y(),
                              -v2.y(),

                              p2.x() - p1.x(),
                              p2.y() - p1.y(),

                              t1,
                              t2) )
	{
        case -1:
            intersect = p1;
            return -1;
            break;

        case 1:
            intersect = p1 + t1*v1;
            return 1;
            break;

        case 0:
        default:
            return 0;
            break;
	}
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#endif


