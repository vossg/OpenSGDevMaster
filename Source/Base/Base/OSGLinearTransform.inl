/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \typedef LinearTransform::ValueType
 *  \brief Value type, eg Real32 
 */

/** \typedef TransformationMatrix<ValueTypeT>\
    LinearTransform::MatrixType;
 *  \brief Matrix type, eg Matrix4f
 */

/** \fn const char *LinearTransform::getClassname(void)
 *  \brief Classname
 */

/** \var MatrixType LinearTransform::_logMatrix;
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

//template<class ValueTypeT>
//char LinearTransform<ValueTypeT>::cvsid[] = "@(#)$Id$";


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** @name constructors & destructors */
//@{

/** \brief Constructor
 */

template<class ValueTypeT> 
LinearTransform<ValueTypeT>::LinearTransform(void)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _logMatrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}

/** \brief Copy Constructor
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>::LinearTransform(
    const LinearTransform &source)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _logMatrix[i] = source._logMatrix[i];
    }
}

/** \brief Constrution from regular transform
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>::LinearTransform(
	const MatrixType &mat)
{
	_logMatrix.logOf(mat);
}

/** \brief Destructor
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>::~LinearTransform(void)
{
}

//@}

/*------------------------- set functions -------------------------------*/

/** @name set functions */
//@{

/** \brief Resets the matrix to identity
 */

template<class ValueTypeT> inline
void LinearTransform<ValueTypeT>::setIdentity(void)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _logMatrix[i].setNull();
        _logMatrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}


/** \brief Set values from a given linear transform
 */

template<class ValueTypeT> inline
void LinearTransform<ValueTypeT>::setValue(
    const LinearTransform &mat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _logMatrix[i] = mat._logMatrix[i];
    }
}

/** \brief Set values from a transformation matrix
 */

template<class ValueTypeT> inline
void LinearTransform<ValueTypeT>::setValue(
    const MatrixType &mat)
{	
	_logMatrix.logOf(mat);
}

//Set the LogMatrix direct

template<class ValueTypeT> inline
void LinearTransform<ValueTypeT>::setLogMatrix( 
	MatrixType &mat )
{
	_logMatrix = mat;
}

//Get the LogMatrix direct

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT> LinearTransform<ValueTypeT>::getLogMatrix()
{
	return _logMatrix;
}

//@}

//Get the LogMatrix direct as const

template<class ValueTypeT> inline
const TransformationMatrix<ValueTypeT> LinearTransform<ValueTypeT>::getLogMatrixConst() const
{
	return _logMatrix;
}

//@}

/*------------------------- create transformation -------------------------*/

/** @name create transformation matrices */
//@{

/** \brief Returns the transformation matrix
 */
template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT> LinearTransform<ValueTypeT>::getTransform()
{
	MatrixType mat;
	mat.expOf(_logMatrix);
	return mat;
}

template<class ValueTypeT> inline
  LinearTransform<ValueTypeT>::operator
		TransformationMatrix<ValueTypeT>()
{
	MatrixType mat;
	mat.expOf(_logMatrix);
	return mat;
}
//@}


/*-------------------------- assignment -----------------------------------*/

/** @name assignement */
//@{

/** \brief assignment
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT> & 
    LinearTransform<ValueTypeT>::operator = (
        const LinearTransform &source)
{
    UInt32 i;

	if (this == &source)
		return *this;

    for(i = 0; i < 4; i++)
        _logMatrix[i] = source._logMatrix[i];

    return *this;
}

//@}

/*-------------------------- comparison -----------------------------------*/

/** @name comparison */
//@{

/** \brief equal
 */

template<class ValueTypeT> inline
bool LinearTransform<ValueTypeT>::operator == (
    const LinearTransform &other) const
{
    return (_logMatrix == other._logMatrix);
}

/** \brief not equal, returns true if all matrix elements are equal with
 *  the tolerance of Eps
 */

template<class ValueTypeT> inline
bool LinearTransform<ValueTypeT>::operator != (
    const LinearTransform &other) const
{
	return ! (*this == other);
}

//@}

/*-------------------------- operators -----------------------------------*/

/** @name operators */
//@{

/** \brief sum of linear transforms
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>
 LinearTransform<ValueTypeT>::operator + (
  const LinearTransform &lt) const
{
  LinearTransform sum;
	for (int i=0; i < 4; i++)
		for (int j=0; j < 4; j++)
			sum._logMatrix[i][j] = _logMatrix[i][j] + 
														 lt._logMatrix[i][j];
  return sum;
}

/** \brief scalar multiple of linear transform
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>
  LinearTransform<ValueTypeT>::operator * (
  	 const ValueTypeT s) const
{
  LinearTransform pro;
	for (int i=0; i < 4; i++)
		for (int j=0; j < 4; j++)
			pro._logMatrix[i][j] = s * _logMatrix[i][j];
  return pro;
}

/** \brief add to linear transforms
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT> &
 LinearTransform<ValueTypeT>::operator += (
  const LinearTransform &lt)
{
	for (int i=0; i < 4; i++)
		for (int j=0; j < 4; j++)
			_logMatrix[i][j] += lt._logMatrix[i][j];
  return *this;
}

/** \brief scalar multiple of linear transform
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT> &
 LinearTransform<ValueTypeT>::operator *= (
  const ValueTypeT s)
{
	for (int i=0; i < 4; i++)
		for (int j=0; j < 4; j++)
			_logMatrix[i][j] *= s;
  return *this;
}

/** \NEW LeftSide Operators
 */

template<class ValueTypeT> inline
LinearTransform<ValueTypeT>
  operator * ( const ValueTypeT s, const LinearTransform<ValueTypeT> &lt)
{
	TransformationMatrix<ValueTypeT> ltMat, proMat;
	LinearTransform<ValueTypeT> pro(lt);
	ltMat = pro.getLogMatrix();

	for (int i=0; i < 4; i++)
		for (int j=0; j < 4; j++)
			proMat[i][j] = s * ltMat[i][j];

	pro.setLogMatrix( proMat );
	return pro;
}

//@}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

#define OSGLINEARTRANSFORM_INLINE_CVSID "@(#)$Id$"

OSG_END_NAMESPACE
