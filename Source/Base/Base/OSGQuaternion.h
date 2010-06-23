/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGQUATERNION_H_
#define _OSGQUATERNION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseFunctions.h"

#include "OSGVectorFwd.h"
#include "OSGMatrixFwd.h"

#include <iostream>
#include <vector>
#include <iomanip>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ValueTypeT>
class QuaternionBase
{
    /*==========================  PUBLIC  =================================*/

    typedef QuaternionBase<ValueTypeT> Self;

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Types                                     */
    /*! \{                                                                 */

    typedef Vector              <ValueTypeT, 3> VectorType;
    typedef TransformationMatrix<ValueTypeT   > MatrixType;

    typedef ValueTypeT                          ValueType;

    static const UInt32 _uiSize = 4;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const QuaternionBase &identity(void                      );

    static       QuaternionBase slerp    (const QuaternionBase &rot0,
                                          const QuaternionBase &rot1,
                                          const ValueTypeT      t   );
    static       QuaternionBase nlerp    (const QuaternionBase &rot0,
                                          const QuaternionBase &rot1,
                                          const ValueTypeT      t   );

    static       QuaternionBase  inverse (const QuaternionBase &val );
    static       QuaternionBase  log     (const QuaternionBase &val );
    static       QuaternionBase  exp     (const QuaternionBase &val );
    static       QuaternionBase  conj    (const QuaternionBase &val );
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

                QuaternionBase(      void                               );
                QuaternionBase(const QuaternionBase &source             );
    explicit    QuaternionBase(const MatrixType     &matrix             );
                QuaternionBase(const VectorType     &axis,
                               const ValueTypeT      angle              );
                QuaternionBase(const VectorType     &rotateFrom,
                               const VectorType     &rotateTo           );
                QuaternionBase(const ValueTypeT*     values             );
                QuaternionBase(const  ValueTypeT  x,
                               const  ValueTypeT  y,
                               const  ValueTypeT  z,
                               const  ValueTypeT  w                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~QuaternionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */

    void setIdentity      (       void                  );

    void setValueAsAxisRad(const  ValueTypeT *valsP     );
    void setValueAsAxisDeg(const  ValueTypeT *valsP     );
    void setValueAsQuat   (const  ValueTypeT *valsP     );

    void setValueAsAxisRad(const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );
    void setValueAsAxisDeg(const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );
    void setValueAsQuat   (const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );

    void setValue         (const  Self       &quat      );
    void setValue         (const  MatrixType &matrix    );

    void setValueAsAxisRad(const  VectorType &axis,    
                                  ValueTypeT  angle     );
    void setValueAsAxisDeg(const  VectorType &axis,
                                  ValueTypeT  angle     );

    void setValue         (const  VectorType &rotateFrom,
                           const  VectorType &rotateTo  );

    void setValueAsAxisRad(const  Char8       *str      );
    void setValueAsAxisDeg(const  Char8       *str      );
    void setValueAsQuat   (const  Char8       *str      );

    void setValue         (const  ValueTypeT alpha,
                           const  ValueTypeT beta,
                           const  ValueTypeT gamma      );


    void setValueFromCString(const Char8          *szString);
    void setValueFromCString(      Char8          *szString);

#ifndef OSG_DISABLE_DEPRECATED
    void setValue           (const Char8          *szString);
    void setValue           (      Char8          *szString);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    const ValueTypeT *getValues        (void               ) const;

          void        getValueAsAxisDeg(ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;
          void        getValueAsAxisRad(ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;
          void        getValueAsQuat   (ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;

          void       getValueAsAxisRad (VectorType &axis, 
                                        ValueTypeT &radians) const;
          void       getValueAsAxisDeg (VectorType &axis, 
                                        ValueTypeT &degrees) const;
          
          void       getEulerAngleRad  (VectorType &euler  ) const;
          void       getEulerAngleDeg  (VectorType &euler  ) const;
          void       getValue          (MatrixType &matrix ) const;
          void       getValuesOnly     (MatrixType &matrix ) const;

          ValueTypeT x                 (void               ) const;
          ValueTypeT y                 (void               ) const;
          ValueTypeT z                 (void               ) const;
          ValueTypeT w                 (void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Simple Math                               */
    /*! \{                                                                 */

          ValueTypeT     length       (      void                       ) const;
          ValueTypeT     lengthSquared(      void                       ) const;
          void           normalize    (      void                       );
          ValueTypeT     dot          (const QuaternionBase &rValue     ) const;

          void           invert       (      void                       );
          QuaternionBase inverse      (      void                       ) const;

          void           multVec      (const VectorType     &src,
                                              VectorType    &dst        ) const;

          void           scaleAngle   (      ValueTypeT      scaleFactor);

          void           slerpThis    (const QuaternionBase &rot0,
                                       const QuaternionBase &rot1,
                                       const ValueTypeT      t          );

          void           nlerpThis    (const QuaternionBase &rot0,
                                       const QuaternionBase &rot1,
                                       const ValueTypeT      t          );

          void           mult         (const QuaternionBase &other      );
          void           multLeft     (const QuaternionBase &other      );

          bool           equals       (const QuaternionBase &rot,
                                       const ValueTypeT      tolerance  ) const;

          QuaternionBase conj         (      void                       ) const;
          QuaternionBase exp          (      void                       ) const;
          QuaternionBase log          (      void                       ) const;

          void           conjThis     (      void                       );
          void           expThis      (      void                       );
          void           logThis      (      void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Element Access                              */
    /*! \{                                                                 */

          ValueTypeT &operator [](const UInt32 index);
    const ValueTypeT &operator [](const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Math Operators                             */
    /*! \{                                                                 */

    void           operator *=(const QuaternionBase &other      );
    void           operator +=(const QuaternionBase &other      );

    QuaternionBase operator * (const QuaternionBase &rValue     ) const;
    QuaternionBase operator + (const QuaternionBase &rValue     ) const;
    QuaternionBase operator - (const QuaternionBase &rValue     ) const;
    QuaternionBase operator / (const QuaternionBase &rValue     ) const;

    QuaternionBase operator * (const ValueTypeT     &rightScalor) const;
    QuaternionBase operator / (const ValueTypeT     &rightScalor) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    QuaternionBase &operator =(const QuaternionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator == (const QuaternionBase &other) const;
    bool operator != (const QuaternionBase &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static void           squad(const std::vector<QuaternionBase> &Q,
                                const std::vector<Real32        > &t, 
                                const      Real32                 &s,
                                           QuaternionBase         &result);

    static QuaternionBase squad(const std::vector<QuaternionBase> &Q,
                                const std::vector<Real32        > &t, 
                                const      Real32                 &s     );

    /*=========================  PROTECTED  ===============================*/

  protected:

    static void slerp(const QuaternionBase &rot0,
                      const QuaternionBase &rot1,
                            QuaternionBase &result,
                      const ValueTypeT      t);

    static void nlerp(const QuaternionBase &rot0,
                      const QuaternionBase &rot1,
                            QuaternionBase &result,
                      const ValueTypeT      t);

           void mult (const ValueTypeT rVal1[4],
                      const ValueTypeT rVal2[4]);

    /*==========================  PRIVATE  ================================*/

  private:

    enum ElementIndices
    {
        Q_X = 0,
        Q_Y = 1,
        Q_Z = 2,
        Q_W = 3
    };

    static QuaternionBase _identity;

           ValueTypeT     _quat[4];
};

/*! \relates QuaternionBase
 */

template <class ValueTypeT> inline
QuaternionBase<ValueTypeT>
    operator *(const ValueTypeT                val,
               const QuaternionBase<ValueTypeT> &quat );

/*! \relates QuaternionBase
 */
template <class ValueTypeT> 
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream               &os, 
    const QuaternionBase<ValueTypeT> &obj);
    
/*! \relates QuaternionBase
 */

template <class ValueTypeT> 
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream               &is, 
    QuaternionBase<ValueTypeT> &obj);

/*---------------------------------------------------------------------*/
/*! \name Quaternion Types                                             */
/*! \{                                                                 */

/*! \var typedef OSG::QuaternionBase<OSG::Real32> Quaternion;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::QuaternionBase
 */
typedef OSG::QuaternionBase<OSG::Real32> Quaternion;


/*! \var typedef OSG::QuaternionBase<OSG::Real64> Quaterniond;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::QuaternionBase
 */
typedef OSG::QuaternionBase<OSG::Real64> Quaterniond;


/*! \var typedef OSG::QuaternionBase<OSG::Fixed32> Quaternionfx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::QuaternionBase
 */
typedef OSG::QuaternionBase<OSG::Fixed32> Quaternionfx;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGQuaternion.inl"

#endif /* _OSGQUATERNION_H_ */
