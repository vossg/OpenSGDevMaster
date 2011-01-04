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
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template<class ValueTypeT>
class TransformationMatrix
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Types                                     */
    /*! \{                                                                 */

    typedef TransformationMatrix<ValueTypeT>    Self;

    typedef                      ValueTypeT     ValueType;
    typedef Vector              <ValueTypeT, 4> VectorType;

    typedef QuaternionBase      <ValueType>     QuaternionType;

    typedef Vector              <ValueTypeT, 3> VectorType3f;

    typedef Point               <ValueTypeT, 4> PointType;
    typedef Point               <ValueTypeT, 3> PointType3f;

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

    TransformationMatrix(const VectorType           &vector1,
                         const VectorType           &vector2,
                         const VectorType           &vector3,
                         const VectorType           &vector4 );

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
    
    template<class ValueTypeR>
    void convertFrom       (const TransformationMatrix<ValueTypeR>& mat    );

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

    void setValue          (const VectorType3f         *pMat               );

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
    
    void mult        (const PointType    &pntIn, PointType    &pntOut) const;
    void multFull    (const PointType3f  &pntIn, PointType3f  &pntOut) const;
    void mult        (const PointType3f  &pntIn, PointType3f  &pntOut) const;
    
    void mult        (const VectorType   &vecIn, VectorType   &vecOut) const;
    void multFull    (const VectorType3f &vecIn, VectorType3f &vecOut) const;
    void mult        (const VectorType3f &vecIn, VectorType3f &vecOut) const;
    
    void mult3x3     (const PointType3f  &pntIn, PointType3f  &pntOut) const;
    void mult3x3     (const VectorType3f &vecIn, VectorType3f &vecOut) const;

    void multLeftFull(const PointType3f  &pntIn, PointType3f  &pntOut) const;
    void multLeft    (const PointType3f  &pntIn, PointType3f  &pntOut) const;

    void multLeftFull(const VectorType3f &vecIn, VectorType3f &vecOut) const;
    void multLeft    (const VectorType3f &vecIn, VectorType3f &vecOut) const;
    
    PointType    operator *(const PointType    &pntIn) const;
    PointType3f  operator *(const PointType3f  &pntIn) const;
             
    VectorType   operator *(const VectorType   &vecIn) const;
    VectorType3f operator *(const VectorType3f &vecIn) const;
       
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

    template<class ValueTypeR>
    void       mult         (const TransformationMatrix<ValueTypeR>& mat);
    template<class ValueTypeR>
    void       multLeft     (const TransformationMatrix<ValueTypeR>& mat);

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

#ifdef OSG_1_COMPAT
    void mult             (      PointType3f  &pnt) const;
    void multMatrixPnt    (      PointType3f  &pnt) const;
    void multMatrixPnt    (const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multMatrixVec    (      VectorType3f &vec) const;
    void multMatrixVec    (const VectorType3f &src, 
                                 VectorType3f &dst) const;
    void multFullMatrixPnt(      PointType3f  &pnt) const;
    void multFullMatrixPnt(const PointType3f  &src, 
                                 PointType3f  &dst) const;
    void multPntFullMatrix(const PointType3f  &src, 
                                 PointType3f  &dst) const;
#endif

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

    template<class ValueTypeR, class ValueTypeS>
    ValueTypeT rowMulCol4(const TransformationMatrix<ValueTypeR> &gRowMat,
                                UInt32                            iRow,
                          const TransformationMatrix<ValueTypeS> &gColMat,
                                UInt32                            iColumn) const;

    ValueTypeT det2_calc (const ValueTypeT            a1,
                          const ValueTypeT            a2,
                          const ValueTypeT            b1,
                          const ValueTypeT            b2     ) const;
    ValueTypeT det3_calc (const ValueTypeT            a1,
                          const ValueTypeT            a2,
                          const ValueTypeT            a3,
                          const ValueTypeT            b1,
                          const ValueTypeT            b2,
                          const ValueTypeT            b3,
                          const ValueTypeT            c1,
                          const ValueTypeT            c2,
                          const ValueTypeT            c3     ) const;


    bool       calcInverse (      TransformationMatrix *destM,
                            const TransformationMatrix *srcM  ) const;
    bool       calcInverse3(      TransformationMatrix *destM,
                            const TransformationMatrix *srcM  ) const;

    // helper functions for matrix decomposition
    ValueType norm1_3x3   (void) const;
    ValueType normInf_3x3 (void) const;
    
    void adjointT_3x3     (TransformationMatrix       &result) const;
    void polarDecompose   (TransformationMatrix       &Q,
                           TransformationMatrix       &S,
                           ValueType                  &det   ) const;
    void spectralDecompose(TransformationMatrix       &SO,
                           VectorType3f               &k     ) const;
    void decompose        (VectorType3f               &t,
                           ValueType                  &f,
                           QuaternionType             &r,
                           QuaternionType             &so,
                           VectorType3f               &s     ) const;
                          
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

/*---------------------------------------------------------------------*/
/*! \name Matrix Types                                                */
/*! \{                                                                 */

/*! \var typedef OSG::TransformationMatrix<OSG::Real32> Matrix4f;
    \brief Matrix4f
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::TransformationMatrix
 */
typedef OSG::TransformationMatrix<OSG::Real32> Matrix4f;


/*! \var typedef OSG::TransformationMatrix<OSG::Real64> Matrix4d;
    \brief Matrix4d
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::TransformationMatrix
 */
typedef OSG::TransformationMatrix<OSG::Real64> Matrix4d;


/*! \var typedef OSG::TransformationMatrix<OSG::Fixed32> Matrix4fx;
    \brief Matrix4f
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::TransformationMatrix
 */
typedef OSG::TransformationMatrix<OSG::Fixed32> Matrix4fx;


/*! \var typedef OSG::TransformationMatrix<OSG::Real32> Matrix;
    \brief Matrix
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::TransformationMatrix
 */
typedef OSG::TransformationMatrix<OSG::Real32 > Matrix;


/*! \var typedef OSG::TransformationMatrix<OSG::Fixed32> Matrixfx;
    \brief Matrixr
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::TransformationMatrix
 */
typedef OSG::TransformationMatrix<OSG::Fixed32> Matrixfx;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

/*! \relates TransformationMatrix
 */
template<class ValueTypeT>
std::ostream &operator <<(      std::ostream                     &os,
                          const TransformationMatrix<ValueTypeT> &obj);

OSG_END_NAMESPACE

#include "OSGMatrix.inl"

#endif /* _OSGMATRIX_H_ */


