/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *          Copyright (C) 2000,2001 by the OpenSG Forum & TU Darmstadt       *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: alexa@gris.informatik.tu-darmstadt.de                          *
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
 *   Initial Version by Tobias Klug                                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGLINEARTRANSFORM_H_
#define _OSGLINEARTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBase.h"
#include "OSGMatrix.h"

#include <string>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseMathObj
    \brief A transform that behaves linear under multiplication (+) and
    scalar multiplication (*)
    \nohierarchy
 */

template<class ValueTypeT>
class LinearTransform
{
public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ValueTypeT ValueType;
		typedef TransformationMatrix<ValueTypeT> MatrixType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "LinearTransform";};

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    LinearTransform(void);
    LinearTransform(const LinearTransform &source);
    LinearTransform(const MatrixType &mat);

    ~LinearTransform(void); 

    /*------------------------- set functions -------------------------------*/

    void setIdentity(void);

    void setValue(const MatrixType &mat);
    void setValue(const LinearTransform &mat);
	void setLogMatrix( MatrixType &mat );

    /*------------------------- get functions -------------------------------*/

	      MatrixType getLogMatrix();
	const MatrixType getLogMatrixConst() const;
    /*---------------------- create transformation --------------------------*/

	MatrixType getTransform();
	operator MatrixType();

    /*------------------------- assignment ----------------------------------*/
    
    LinearTransform<ValueTypeT> & operator =(
        const LinearTransform &source);

    /*------------------------- comparison ----------------------------------*/

	bool operator == (const LinearTransform &other) const;
	bool operator != (const LinearTransform &other) const;

    /*------------------------- operators -----------------------------------*/
		
		
	LinearTransform<ValueTypeT>
		operator + (const LinearTransform &lt) const;
	LinearTransform<ValueTypeT> 
		operator * (const ValueTypeT s) const;
		
	LinearTransform<ValueTypeT> &
		operator += (const LinearTransform &lt);
	LinearTransform<ValueTypeT> &
		operator *= (const ValueTypeT s);
		

protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	MatrixType _logMatrix;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

private:
    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/*! \relates LinearTransform
 */
template<class ValueTypeT>
LinearTransform<ValueTypeT> operator * (const ValueTypeT                   s, 
                                        const LinearTransform<ValueTypeT> &lt);
		

/*---------------------------------------------------------------------*/
/*! \name LinearTranform Types                                         */
/*! \{                                                                 */

/*! \var typedef OSG::LinearTransform<OSG::Real32> LinearTransform4f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::LinearTransform
 */
typedef OSG::LinearTransform<OSG::Real32> LinearTransform4f;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGLinearTransform.inl"

#endif /* _OSGLINEARTRANSFORM_H_ */
