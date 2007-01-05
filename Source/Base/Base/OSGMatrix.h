/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGMATRIX_H_
#define _OSGMATRIX_H_
#ifdef __sgi
#pragma once
#endif


#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <iomanip>

#include "OSGLog.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

#if defined(OSG_MICROSOFT_COMPILER_HACKS) || defined(__sun)
static const UInt32 JacobiRank = 3;
#endif

template <class ValueTypeT> class QuaternionBase;

/*! TransformationMatrix, for details about the vector, point and
    matrix desing see \ref PageBaseMath, nevertheless
    the following applies : M=(V0 V1 V2 V3), M[Column][Row], M[0] = V0
    M[0][0] = V0[0]
    M.getValues() returns M transposed (as it returns the raw storage)
    \ingroup GrpBaseBaseMathObj
 */

template<class ValueTypeT>
class TransformationMatrix
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Types                                     */
    /*! \{                                                                 */

    typedef                 ValueTypeT                ValueType;
    typedef VectorInterface<ValueTypeT, 
                            VecStorage4<ValueTypeT> > VectorType;

    typedef QuaternionBase <ValueType>                QuaternionType;

    typedef VectorInterface<ValueTypeT, 
                            VecStorage3<ValueTypeT> > VectorType3f;

    typedef PointInterface<ValueTypeT, 
                           VecStorage3<ValueTypeT>  > PointType3f;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const TransformationMatrix &identity(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TransformationMatrix(void);
    TransformationMatrix(const TransformationMatrix &source );

    TransformationMatrix(const VectorType3f         &vector1,
                         const VectorType3f         &vector2,
                         const VectorType3f         &vector3);    

    TransformationMatrix(const VectorType3f         &vector1,
                         const VectorType3f         &vector2,
                         const VectorType3f         &vector3,
                         const VectorType3f         &vector4);    

    TransformationMatrix(const ValueTypeT            rVal00,
                         const ValueTypeT            rVal10,
                         const ValueTypeT            rVal20,
                         const ValueTypeT            rVal30,
                         
                         const ValueTypeT            rVal01,
                         const ValueTypeT            rVal11,
                         const ValueTypeT            rVal21,
                         const ValueTypeT            rVal31,
                         
                         const ValueTypeT            rVal02,
                         const ValueTypeT            rVal12,
                         const ValueTypeT            rVal22,
                         const ValueTypeT            rVal32,
                         
                         const ValueTypeT            rVal03,
                         const ValueTypeT            rVal13,
                         const ValueTypeT            rVal23,
                         const ValueTypeT            rVal33);
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
   
    ~TransformationMatrix(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */
   
    void setIdentity       (void                                           );

    void setValue          (const TransformationMatrix &mat                );

    void setValue          (const VectorType3f         &vector1,
                            const VectorType3f         &vector2,
                            const VectorType3f         &vector3            );

    void setValue          (const VectorType3f         &vector1,
                            const VectorType3f         &vector2,
                            const VectorType3f         &vector3,
                            const VectorType3f         &vector4            );

    void setValue          (const ValueTypeT            rVal00,
                            const ValueTypeT            rVal10,
                            const ValueTypeT            rVal20,
                            const ValueTypeT            rVal30,
                            
                            const ValueTypeT            rVal01,
                            const ValueTypeT            rVal11,
                            const ValueTypeT            rVal21,
                            const ValueTypeT            rVal31,
                            
                            const ValueTypeT            rVal02,
                            const ValueTypeT            rVal12,
                            const ValueTypeT            rVal22,
                            const ValueTypeT            rVal32,
                            
                            const ValueTypeT            rVal03,
                            const ValueTypeT            rVal13,
                            const ValueTypeT            rVal23,
                            const ValueTypeT            rVal33             );

    void setValueTransposed(const ValueTypeT            rVal00,
                            const ValueTypeT            rVal01,
                            const ValueTypeT            rVal02,
                            const ValueTypeT            rVal03,
                            
                            const ValueTypeT            rVal10,
                            const ValueTypeT            rVal11,
                            const ValueTypeT            rVal12,
                            const ValueTypeT            rVal13,
                            
                            const ValueTypeT            rVal20,
                            const ValueTypeT            rVal21,
                            const ValueTypeT            rVal22,
                            const ValueTypeT            rVal23,
                            
                            const ValueTypeT            rVal30,
                            const ValueTypeT            rVal31,
                            const ValueTypeT            rVal32,
                            const ValueTypeT            rVal33             );

    void setValue          (const ValueTypeT           *pMat,
                                  bool                  bTransposed = true );

    void setValue          (const VectorType           *pMat               );

#ifndef WIN32
    void setValue          (const VectorType3f         *pMat               );
#endif

    void setValue           (const Char8               *string,
                                   bool                 bTransposed = true );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

          ValueTypeT *getValues(void);
    const ValueTypeT *getValues(void) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set Transformations                        */
    /*! \{                                                                 */

    void setScale    (const ValueTypeT      s               );

    void setScale    (const ValueTypeT      sx,
                      const ValueTypeT      sy, 
                      const ValueTypeT      sz              );

    void setScale    (const VectorType3f   &s               );


    void setTranslate(const ValueTypeT      tx,
                      const ValueTypeT      ty,
                      const ValueTypeT      tz              );

    void setTranslate(const VectorType3f   &t               );

    void setTranslate(const PointType3f    &t               );


    void setRotate   (const QuaternionType &q               );


    void setTransform(const VectorType3f   &t               );

    void setTransform(const QuaternionType &r               );

    void setTransform(const VectorType3f   &t, 
                      const QuaternionType &r               );

    void setTransform(const VectorType3f   &t, 
                      const QuaternionType &r,
                      const VectorType3f   &s               );

    void setTransform(const VectorType3f   &t, 
                      const QuaternionType &r,
                      const VectorType3f   &s, 
                      const QuaternionType &so              );

    void setTransform(const VectorType3f   &translation,
                      const QuaternionType &rotation,
                      const VectorType3f   &scaleFactor,
                      const QuaternionType &scaleOrientation,
                      const VectorType3f   &center          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get Transformations                        */
    /*! \{                                                                 */

    void getTransform(      VectorType3f         &translation, 
                            QuaternionType       &rotation,
                            VectorType3f         &scaleFactor, 
                            QuaternionType       &scaleOrientation,
                      const VectorType3f         &center) const;

    void getTransform(      VectorType3f         &translation, 
                            QuaternionType       &rotation,
                            VectorType3f         &scaleFactor, 
                            QuaternionType       &scaleOrientation) const;

    bool factor      (      TransformationMatrix &r, 
                            VectorType3f         &s, 
                            TransformationMatrix &u,
                            VectorType3f         &t, 
                            TransformationMatrix &proj) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transform                                  */
    /*! \{                                                                 */

    void multMatrixPnt    (const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multMatrixPnt    (      PointType3f  &pnt) const;
    void multFullMatrixPnt(const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multFullMatrixPnt(      PointType3f  &pnt) const;

    void multMatrixVec    (const VectorType3f &src, 
                                 VectorType3f &dst) const;
    void multMatrixVec    (      VectorType3f &vec) const;

    void mult             (const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void mult             (      PointType3f  &vec) const;
    void mult             (const VectorType3f &src, 
                                 VectorType3f &dst) const;
    void mult             (      VectorType3f &vec) const;


    void multPntMatrix    (const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multPntMatrix    (      PointType3f  &pnt) const;
    void multPntFullMatrix(const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multPntFullMatrix(      PointType3f  &pnt) const;

    void multVecMatrix    (const VectorType3f &src, 
                                 VectorType3f &dst) const;
    void multVecMatrix    (      VectorType3f &vec) const;


    void multMatrixVec    (const VectorType &src, 
                                 VectorType &dst) const;
    void multMatrixVec    (      VectorType &vec) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Math                                       */
    /*! \{                                                                 */

    bool       equals       (const TransformationMatrix &matrix, 
                             const ValueType             tol   ) const;

    ValueTypeT det3         (      void                        ) const;
    ValueTypeT det          (      void                        ) const;

    bool       inverse      (      TransformationMatrix &result) const;
    bool       invert       (      void                        );
    bool       invertFrom   (const TransformationMatrix &matrix);

    bool       inverse3     (      TransformationMatrix &result) const;
    bool       invert3      (      void                        );
    bool       invertFrom3  (const TransformationMatrix &matrix);

    bool       transposed   (      TransformationMatrix &result) const;
    bool       transpose    (      void                        );
    bool       transposeFrom(const TransformationMatrix &matrix);

    void       mult         (const TransformationMatrix &matrix);
    void       multLeft     (const TransformationMatrix &matrix);
    
    void       add          (const TransformationMatrix &matrix);
    void       scale        (      ValueTypeT            s     );
    void       addScaled    (const TransformationMatrix &matrix, 
                                   ValueTypeT            s     );
    void       negate       (      void                        );
    
    ValueTypeT norm1        (      void                        ) const;
    ValueTypeT norm2        (      void                        ) const;
    ValueTypeT normInfinity (      void                        ) const;
    
    bool       sqrt         (      TransformationMatrix &result) const;
    bool       sqrtOf       (const TransformationMatrix &matrix);
    bool       sqrt         (      void                        );
    
    bool       log          (      TransformationMatrix &result) const;
    bool       logOf        (const TransformationMatrix &matrix);
    
    bool       exp          (      TransformationMatrix &result) const;
    bool       expOf        (const TransformationMatrix &matrix);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Element Access                             */
    /*! \{                                                                 */

          VectorType &operator [](UInt32 uiIndex);
    const VectorType &operator [](UInt32 uiIndex) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    TransformationMatrix &operator =(const TransformationMatrix &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator == (const TransformationMatrix &other) const;
    bool operator != (const TransformationMatrix &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Storage                                    */
    /*! \{                                                                 */

    VectorType _matrix[4];

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Internal Math                              */
    /*! \{                                                                 */

    ValueTypeT rowMulCol4(const TransformationMatrix &gRowMat, 
                                UInt32                iRow, 
                          const TransformationMatrix &gColMat, 
                                UInt32                iColumn) const;

    ValueTypeT det2      (const ValueTypeT            a1, 
                          const ValueTypeT            a2,
                          const ValueTypeT            b1, 
                          const ValueTypeT            b2     ) const;
    ValueTypeT det3      (const ValueTypeT            a1, 
                          const ValueTypeT            a2, 
                          const ValueTypeT            a3,
                          const ValueTypeT            b1, 
                          const ValueTypeT            b2, 
                          const ValueTypeT            b3,
                          const ValueTypeT            c1, 
                          const ValueTypeT            c2, 
                          const ValueTypeT            c3     ) const;

#ifdef __sgi
#pragma set woff 1424
#endif

#if !defined(OSG_MICROSOFT_COMPILER_HACKS) && !defined(__sun)
    static const UInt32 JacobiRank = 3;
#endif

    bool jacobi(ValueTypeT    evalues [JacobiRank],
                VectorType3f  evectors[JacobiRank],
                Int32        &rots);

#ifdef __sgi
#pragma reset woff 1424
#endif
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    static TransformationMatrix _identityMatrix;
};

/*! \var typedef TransformationMatrix<Real32> Matrix4f;
    \brief Matrix4f
    \ingroup GrpBaseBaseMathObj
*/

typedef TransformationMatrix<Real32> Matrix4f;

/*! \var typedef TransformationMatrix<Real64> Matrix4d;
    \brief Matrix4d
    \ingroup GrpBaseBaseMathObj
*/

typedef TransformationMatrix<Real64> Matrix4d;

/*! \var typedef TransformationMatrix<Fixed32> Matrix4fx;
    \brief Matrix4f
    \ingroup GrpBaseBaseMathObj
*/

typedef TransformationMatrix<Fixed32> Matrix4fx;

/*! \var typedef TransformationMatrix<Real32> Matrix;
    \brief Matrix
    \ingroup GrpBaseBaseMathObj
*/

typedef TransformationMatrix<Real32 > Matrix;

/*! \var typedef TransformationMatrix<Fixed32> Matrifx;
    \brief Matrix
    \ingroup GrpBaseBaseMathObj
*/

typedef TransformationMatrix<Fixed32> Matrix4fx;

#ifdef OSG_FLOAT_PROFILE

/*! \var typedef Matrix4f Matrixr
    \brief Matrix
    \ingroup GrpBaseBaseMathObj
*/

typedef Matrix4f Matrixr;

#else

/*! \var typedef Matrix4fx Matrixr
    \brief Matrix
    \ingroup GrpBaseBaseMathObj
*/

typedef Matrix4fx Matrixr;

#endif

template<class ValueTypeT> 
std::ostream &operator <<(      std::ostream                     &os,
                          const TransformationMatrix<ValueTypeT> &obj);

OSG_END_NAMESPACE

#include "OSGMatrix.inl"

#endif /* _OSGMATRIX_H_ */


