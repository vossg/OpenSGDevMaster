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

#ifndef _OSGVECTOR_H_
#define _OSGVECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT, UInt32 SizeI>
class Point;

template<class ValueTypeT, UInt32 SizeI>
class Vector;


#ifdef __sgi
#pragma set woff 1209
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector storage holding 1 elements, for details about how vectors,
    points and matrices are actually build see 
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ValueTypeT>
class VecStorage1
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _uiSize = 1;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage1(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage1(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1);

    void       getSeparateValues(      ValueTypeT &rVal1) const;

    ValueTypeT x                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ValueTypeT _values[_uiSize];

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage1(const VecStorage1 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage1 &source);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector storage holding 2 elements, for details about how vectors,
    points and matrices are actually build see \guide{BaseMath}.
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ValueTypeT>
class VecStorage2
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _uiSize = 2;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage2(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage2(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1, 
                                 const ValueTypeT  rVal2);

    void       getSeparateValues(      ValueTypeT &rVal1, 
                                       ValueTypeT &rVal2) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ValueTypeT _values[_uiSize];

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage2(const VecStorage2 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage2 &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector storage holding 3 elements, for details about how vectors,
    points and matrices are actually build see \guide{BaseMath}.
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ValueTypeT>
class VecStorage3
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _uiSize = 3;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1,
                                 const ValueTypeT  rVal2,
                                 const ValueTypeT  rVal3);

    void       getSeparateValues(      ValueTypeT &rVal1,
                                       ValueTypeT &rVal2,
                                       ValueTypeT &rVal3) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;
    ValueTypeT z                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ValueTypeT _values[_uiSize];

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage3(const VecStorage3 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage3 &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector storage holding 4 elements, for details about how vectors,
    points and matrices are actually build see \guide{BaseMath}.
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

template <class ValueTypeT>
class VecStorage4
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _uiSize = 4;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1,
                                 const ValueTypeT  rVal2,
                                 const ValueTypeT  rVal3,
                                 const ValueTypeT  rVal4);

    void       getSeparateValues(      ValueTypeT &rVal1,
                                       ValueTypeT &rVal2,
                                       ValueTypeT &rVal3,
                                       ValueTypeT &rVal4) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;
    ValueTypeT z                (void                   ) const;
    ValueTypeT w                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ValueTypeT _values[_uiSize];

    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage4(const VecStorage4 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage4 &source);
};


/*! \brief Helper struct to select the correct storage class for vector types.
 */
template <class ValueTypeT, UInt32 SizeI>
struct SelectVecStorage;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 1> : public VecStorage1<ValueTypeT>
{
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 2> : public VecStorage2<ValueTypeT>
{
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 3> : public VecStorage3<ValueTypeT>
{
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 4> : public VecStorage4<ValueTypeT>
{
};
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Point Interface, for details about how vectors, points and matrices
    are actually build see \guide{BaseMath}.
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
 */

#ifdef __sgi
#pragma set woff 1375
#endif

template <class ValueTypeT, UInt32 SizeI>
class Point : public SelectVecStorage<ValueTypeT, SizeI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          SelectVecStorage<ValueTypeT,
                                      SizeI      >          Inherited;
    typedef          Point           <ValueTypeT, 
                                      SizeI      >          Self;
    typedef          SelectVecStorage<ValueTypeT,
                                      SizeI      >          StorageInterface;
    
    typedef          ValueTypeT                             ValueType;    
    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

    typedef          Point           <ValueTypeT, 
                                      SizeI      >          PointType;
    typedef          Vector          <ValueTypeT,
                                      SizeI      >          VectorType;

    
    static  const    Point                                  Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             Point(      void                               );

    explicit Point(const ValueType                   *pVals );
    explicit Point(      ValueType                   *pVals );

    template <class ValueType2T, UInt32 Size2I> 
    explicit Point(const Point <ValueType2T, Size2I> &pnt   );

    template <class ValueType2T, UInt32 Size2I> 
    explicit Point(const Vector<ValueType2T, Size2I> &vec   );

             Point(const Point                       &source);

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    Point(const ValueType rVal1                        );

    Point(const ValueType rVal1, const ValueType rVal2 );

    Point(const ValueType rVal1, const ValueType rVal2,
          const ValueType rVal3                        );

    Point(const ValueType rVal1, const ValueType rVal2,
          const ValueType rVal3, const ValueType rVal4 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Point(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void setNull (void);

    template <class ValueType2T, UInt32 Size2I> 
    void setValue           (const Point<ValueType2T,
                                         Size2I      > &pnt     );
                                         
    void setValue           (const Point               &pnt     );

    void setValue           (const ValueType           *pVals   );
    void setValue           (      ValueType           *pVals   );

    void setValueFromCString(const Char8               *szString);
    void setValueFromCString(      Char8               *szString);

#ifndef OSG_DISABLE_DEPRECATED
    void setValue           (const Char8               *szString);
    void setValue           (      Char8               *szString);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Values                                  */
    /*! \{                                                                 */

          ValueType *getValues(void);
    const ValueType *getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

          bool            isZero  (      void                 ) const;

          void            negate  (      void                 );

          bool            equals  (const Point      &pnt,
                                   const ValueType   tolerance) const;

          VectorType     &subZero (      void                 );
    const VectorType     &subZero (      void                 ) const;

          RealReturnType  dist    (const Point      &pnt      ) const;
          RealReturnType  dist2   (const Point      &pnt      ) const;

          RealReturnType  maxValue(      void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void       operator *=(const ValueType   val);
    void       operator /=(const ValueType   val);

    VectorType operator - (const Point      &pnt) const;

    Point      operator + (const VectorType &vec) const;

    Point      operator - (const VectorType &vec) const;

    Point      operator * (const ValueType   val) const;

    Point      operator / (const ValueType   val) const;

    Point      operator - (      void           ) const;

    void       operator +=(const VectorType &vec);
    void       operator -=(const VectorType &vec);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Element Access                             */
    /*! \{                                                                 */

           ValueType &operator[](const UInt32 uiVal);
    const  ValueType &operator[](const UInt32 uiVal) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    Point &operator =(const Point      &source);
    Point &operator =(const VectorType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const Point &other)  const;

    bool operator == (const Point &other) const;
    bool operator != (const Point &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};

/*! \relates Point
 */
template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    operator *(const ValueTypeT                val,
               const Point<ValueTypeT, SizeI> &pnt );

/*! \relates Point
 */
template <class  ValueTypeT,
          UInt32 SizeI      > OSG_BASE_DLLMAPPING
std::ostream &operator <<(
          std::ostream             &os,
    const Point<ValueTypeT, SizeI> &pnt);

/*! \relates Point
 */
template <class  ValueTypeT,
          UInt32 SizeI      > OSG_BASE_DLLMAPPING
std::istream &operator >>(
    std::istream             &is,
    Point<ValueTypeT, SizeI> &pnt);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector Interface, for details about how vectors, points and matrices
    are actually build see \guide{BaseMath}.
    \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
 */

template <class ValueTypeT, UInt32 SizeI>
class Vector : public Point<ValueTypeT, SizeI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          Point <ValueTypeT, SizeI>              Inherited;
    typedef          Vector<ValueTypeT, SizeI>              Self;
    
    typedef          ValueTypeT                             ValueType;    
    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;
    
    typedef typename Inherited::PointType                   PointType;
    typedef typename Inherited::VectorType                  VectorType;
    
    
    static  const    Vector                                 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             Vector(      void                   );

    explicit Vector(const ValueTypeT      *pVals );
    explicit Vector(      ValueTypeT      *pVals );

    template <class ValueType2T, UInt32 Size2I> 
    explicit Vector(const Point <ValueType2T, Size2I> &pnt);

    template <class ValueType2T, UInt32 Size2I> 
    explicit Vector(const Vector<ValueType2T, Size2I> &vec);

    Vector(const Vector &source);

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    Vector(const ValueType rVal1                        );

    Vector(const ValueType rVal1, const ValueType rVal2 );

    Vector(const ValueType rVal1, const ValueType rVal2,
           const ValueType rVal3                        );

    Vector(const ValueType rVal1, const ValueType rVal2,
           const ValueType rVal3, const ValueType rVal4 );
      
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Vector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

    RealReturnType length       (      void             ) const;
    RealReturnType squareLength (      void             ) const;

    void           normalize    (      void             );

    Vector         cross        (const Vector    &vec   ) const;
    Vector         operator %   (const Vector    &vec   ) const;

    void           crossThis    (const Vector    &vec   );

    ValueType      dot          (const Vector    &vec   ) const;
    ValueType      operator *   (const Vector    &vec   ) const;
    ValueType      dot          (const PointType &pnt   ) const;
    ValueType      operator *   (const PointType &pnt   ) const;

    RealReturnType enclosedAngle(const Vector    &vec   ) const;

    RealReturnType projectTo    (const Vector    &toVec );

    Vector         reflect      (const Vector    &Normal) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Conv                                    */
    /*! \{                                                                 */

          PointType &addToZero (void);
    const PointType &addToZero (void) const;

          Vector    &subZero   (void);
    const Vector    &subZero   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    Vector operator - (const Vector    &vec) const;
    Vector operator + (const Vector    &vec) const;

    Vector operator * (const ValueType  val) const;
    Vector operator / (const ValueType  val) const;

    Vector operator - (      void          ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    Vector &operator =(const Vector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const Vector &other) const;

    bool operator == (const Vector &other) const;
    bool operator != (const Vector &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};

#ifdef __sgi
#pragma reset woff 1375
#endif

/*! \relates Vector
 */
template <class ValueTypeT,
          UInt32 SizeI     > inline
Vector<ValueTypeT, SizeI>
    operator *(const ValueTypeT                 val,
               const Vector<ValueTypeT, SizeI> &vec );

/*! \relates Vector
 */
template <class ValueTypeT,
          UInt32 SizeI     > OSG_BASE_DLLMAPPING
std::ostream &operator <<(
          std::ostream              &os,
    const Vector<ValueTypeT, SizeI> &vec);

/*! \relates Vector
 */
template <class  ValueTypeT,
          UInt32 SizeI      > OSG_BASE_DLLMAPPING
std::istream &operator >>(
    std::istream              &is,
    Vector<ValueTypeT, SizeI> &vec);


// Actual Types

/*---------------------------------------------------------------------*/
/*! \name Vector Types                                                 */
/*! \{                                                                 */

/*! \var typedef OSG::Vector< OSG::UInt8, 1 > Vec1ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt8, 1> Vec1ub;

/*! \var typedef OSG::Vec1ub *Vec1ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1ub *Vec1ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Vector< OSG::Int8, 1 > Vec1b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int8, 1 > Vec1b;

/*! \var typedef OSG::Vec1b *Vec1bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1b *Vec1bP;
#endif

/*! \var typedef OSG::Vector< OSG::UInt16, 1 > Vec1us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt16, 1 > Vec1us;

/*! \var typedef OSG::Vec1us *Vec1usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1us *Vec1usP;

/*! \var typedef OSG::Vector< OSG::Int16, 1 > Vec1s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int16, 1 > Vec1s;

/*! \var typedef OSG::Vec1s *Vec1sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1s *Vec1sP;

/*! \var typedef OSG::Vector< OSG::Real32, 1 > Vec1f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real32, 1 > Vec1f;

/*! \var typedef OSG::Vec1f *Vec1fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1f *Vec1fP;

/*! \var typedef OSG::Vector< Fixed32, 1 > Vec1fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< Fixed32, 1 > Vec1fx;

/*! \var typedef OSG::Vec1fx *Vec1fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1fx *Vec1fxP;

/*! \var typedef OSG::Vector< OSG::Real64, 1 > Vec1d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real64, 1 > Vec1d;

/*! \var typedef OSG::Vec1d *Vec1dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1d *Vec1dP;

/*! \var typedef OSG::Vector< OSG::Real128, 1 > Vec1ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real128, 1 > Vec1ld;

/*! \var typedef OSG::Vec1ld *Vec1ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec1ld *Vec1ldP;


/*! \var typedef OSG::Vector< OSG::UInt8, 2 > Vec2ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt8, 2 > Vec2ub;

/*! \var typedef OSG::Vec2ub *Vec2ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2ub *Vec2ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Vector< OSG::Int8, 2 > Vec2b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int8, 2 > Vec2b;

/*! \var typedef OSG::Vec2b *Vec2bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2b *Vec2bP;
#endif

/*! \var typedef OSG::Vector< OSG::UInt16, 2 > Vec2us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt16, 2 > Vec2us;

/*! \var typedef OSG::Vec2us *Vec2usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2us *Vec2usP;

/*! \var typedef OSG::Vector< OSG::Int16, 2 > Vec2s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int16, 2 > Vec2s;

/*! \var typedef OSG::Vec2s *Vec2sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2s *Vec2sP;

/*! \var typedef OSG::Vector< OSG::Int32, 2 > Vec2i;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int32, 2 > Vec2i;

/*! \var typedef OSG::Vec2i *Vec2iP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2i *Vec2iP;

/*! \var typedef OSG::Vector< OSG::UInt32, 2 > Vec2u;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt32, 2 > Vec2u;

/*! \var typedef OSG::Vec2u *Vec2uP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2u *Vec2uP;

/*! \var typedef OSG::Vector< OSG::Real32, 2 > Vec2f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real32, 2 > Vec2f;

/*! \var typedef OSG::Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2f *Vec2fP;

/*! \var typedef OSG::Vector< Fixed32, 2 > Vec2fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */


typedef OSG::Vector< Fixed32, 2 > Vec2fx;

/*! \var typedef OSG::Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2fx *Vec2fxP;

/*! \var typedef OSG::Vector< OSG::Real64, 2 > Vec2d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real64, 2 > Vec2d;

/*! \var typedef OSG::Vec2d *Vec2dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2d *Vec2dP;

/*! \var typedef OSG::Vector< OSG::Real128, 2 > Vec2ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real128, 2 > Vec2ld;

/*! \var typedef OSG::Vec2ld *Vec2ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec2ld *Vec2ldP;


/*! \var typedef OSG::Vector< OSG::UInt8, 3 > Vec3ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt8, 3 > Vec3ub;

/*! \var typedef OSG::Vec3ub *Vec3ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3ub *Vec3ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Vector< OSG::Int8, 3 > Vec3b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int8, 3 > Vec3b;

/*! \var typedef OSG::Vec3b *Vec3bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3b *Vec3bP;
#endif

/*! \var typedef OSG::Vector< OSG::UInt16, 3 > Vec3us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt16, 3 > Vec3us;

/*! \var typedef OSG::Vec3us *Vec3usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3us *Vec3usP;

/*! \var typedef OSG::Vector< OSG::Int16, 3 > Vec3s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int16, 3 > Vec3s;

/*! \var typedef OSG::Vec3s *Vec3sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3s *Vec3sP;

/*! \var typedef OSG::Vector< OSG::Real32, 3 > Vec3f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector < OSG::Real32, 3  > Vec3f;

/*! \var typedef OSG::Vec3f *Vec3fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3f *Vec3fP;

/*! \var typedef OSG::Vector< Fixed32, 3 > Vec3fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< Fixed32, 3 > Vec3fx;

/*! \var typedef OSG::Vec3fx *Vec3fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3fx *Vec3fxP;

/*! \var typedef OSG::Vector< OSG::Real64, 3 > Vec3d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real64, 3 > Vec3d;

/*! \var typedef OSG::Vec3d *Vec3dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3d *Vec3dP;

/*! \var typedef OSG::Vector< OSG::Real128, 3 > Vec3ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real128, 3 > Vec3ld;

/*! \var typedef OSG::Vec3ld *Vec3ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec3ld *Vec3ldP;


/*! \var typedef OSG::Vector< OSG::UInt8, 4 > Vec4ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt8, 4 > Vec4ub;

/*! \var typedef OSG::Vec4ub *Vec4ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4ub *Vec4ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Vector< OSG::Int8, 4 > Vec4b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int8, 4 > Vec4b;

/*! \var typedef OSG::Vec4b *Vec4bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4b *Vec4bP;
#endif

/*! \var typedef OSG::Vector< OSG::UInt16, 4 > Vec4us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::UInt16, 4 > Vec4us;

/*! \var typedef OSG::Vec4us *Vec4usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4us *Vec4usP;

/*! \var typedef OSG::Vector< OSG::Int16, 4 > Vec4s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Int16, 4 > Vec4s;

/*! \var typedef OSG::Vec4s *Vec4sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4s *Vec4sP;

/*! \var typedef OSG::Vector< OSG::Real32, 4 > Vec4f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real32,  4 > Vec4f;

/*! \var typedef OSG::Vec4f *Vec4fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4f *Vec4fP;

/*! \var typedef OSG::Vector< Fixed32, 4 > Vec4fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< Fixed32, 4 > Vec4fx;

/*! \var typedef OSG::Vec4fx *Vec4fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4fx *Vec4fxP;

/*! \var typedef OSG::Vector< OSG::Real64, 4 > Vec4d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real64, 4 > Vec4d;

/*! \var typedef OSG::Vec4d *Vec4dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4d *Vec4dP;

/*! \var typedef OSG::Vector< OSG::Real128, 4 > Vec4ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vector< OSG::Real128, 4 > Vec4ld;

/*! \var typedef OSG::Vec4ld *Vec4ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Vector
 */

typedef OSG::Vec4ld *Vec4ldP;


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name Point Types                                                  */
/*! \{                                                                 */


/*! \var typedef OSG::Point< OSG::UInt8, 1 > Pnt1ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt8, 1 > Pnt1ub;

/*! \var typedef OSG::Pnt1ub *Pnt1ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1ub *Pnt1ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Point< OSG::Int8, 1 > Pnt1b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int8, 1 > Pnt1b;

/*! \var typedef OSG::Pnt1b *Pnt1bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1b *Pnt1bP;
#endif

/*! \var typedef OSG::Point< OSG::UInt16, 1 > Pnt1us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt16, 1 > Pnt1us;

/*! \var typedef OSG::Pnt1us *Pnt1usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1us *Pnt1usP;

/*! \var typedef OSG::Point< OSG::Int16, 1 > Pnt1s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int16, 1 > Pnt1s;

/*! \var typedef OSG::Pnt1s *Pnt1sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1s *Pnt1sP;

/*! \var typedef OSG::Point< OSG::Real32, 1 > Pnt1f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real32, 1 > Pnt1f;

/*! \var typedef OSG::Pnt1f *Pnt1fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1f *Pnt1fP;

/*! \var typedef OSG::Point< Fixed32, 1 > Pnt1fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< Fixed32, 1 > Pnt1fx;

/*! \var typedef OSG::Pnt1fx *Pnt1fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1fx *Pnt1fxP;

/*! \var typedef OSG::Point< OSG::Real64, 1 > Pnt1d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real64, 1 > Pnt1d;

/*! \var typedef OSG::Pnt1d *Pnt1dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1d *Pnt1dP;

/*! \var typedef OSG::Point< OSG::Real128, 1 > Pnt1ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real128, 1 > Pnt1ld;

/*! \var typedef OSG::Pnt1ld *Pnt1ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt1ld *Pnt1ldP;



/*! \var typedef OSG::Point< OSG::UInt8, 2 > Pnt2ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt8, 2 > Pnt2ub;

/*! \var typedef OSG::Pnt2ub *Pnt2ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2ub *Pnt2ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Point< OSG::Int8, 2 > Pnt2b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int8, 2 > Pnt2b;

/*! \var typedef OSG::Pnt2b *Pnt2bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2b *Pnt2bP;
#endif

/*! \var typedef OSG::Point< OSG::UInt16, 2 > Pnt2us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt16, 2 > Pnt2us;

/*! \var typedef OSG::Pnt2us *Pnt2usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2us *Pnt2usP;

/*! \var typedef OSG::Point< OSG::Int16, 2 > Pnt2s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int16, 2 > Pnt2s;

/*! \var typedef OSG::Pnt2s *Pnt2sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2s *Pnt2sP;

/*! \var typedef OSG::Point< OSG::Int32, 2 > Pnt2i;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int32, 2 > Pnt2i;

/*! \var typedef OSG::Pnt2i *Pnt2iP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2i *Pnt2iP;

/*! \var typedef OSG::Point< OSG::Real32, 2 > Pnt2f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real32,  2 > Pnt2f;

/*! \var typedef OSG::Pnt2f *Pnt2fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2f *Pnt2fP;

/*! \var typedef OSG::Point< Fixed32, 2 > Pnt2fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< Fixed32, 2 > Pnt2fx;

/*! \var typedef OSG::Pnt2fx *Pnt2fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2fx *Pnt2fxP;

/*! \var typedef OSG::Point< OSG::Real64, 2 > Pnt2d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real64, 2 > Pnt2d;

/*! \var typedef OSG::Pnt2d *Pnt2dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2d *Pnt2dP;

/*! \var typedef OSG::Point< OSG::Real128, 2 > Pnt2ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real128, 2 > Pnt2ld;

/*! \var typedef OSG::Pnt2ld *Pnt2ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt2ld *Pnt2ldP;


/*! \var typedef OSG::Point< OSG::UInt8, 3 > Pnt3ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt8, 3 > Pnt3ub;

/*! \var typedef OSG::Pnt3ub *Pnt3ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3ub *Pnt3ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Point< OSG::Int8, 3 > Pnt3b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int8, 3 > Pnt3b;

/*! \var typedef OSG::Pnt3b *Pnt3bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3b *Pnt3bP;
#endif

/*! \var typedef OSG::Point< OSG::UInt16, 3 > Pnt3us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt16, 3 > Pnt3us;

/*! \var typedef OSG::Pnt3us *Pnt3usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3us *Pnt3usP;

/*! \var typedef OSG::Point< OSG::Int16, 3 > Pnt3s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int16, 3 > Pnt3s;

/*! \var typedef OSG::Pnt3s *Pnt3sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3s *Pnt3sP;

/*! \var typedef OSG::Point< OSG::Real32, 3 > Pnt3f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real32, 3 > Pnt3f;

/*! \var typedef OSG::Pnt3f *Pnt3fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3f *Pnt3fP;

/*! \var typedef OSG::Point< Fixed32, 3 > Pnt3fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point < Fixed32, 3 > Pnt3fx;

/*! \var typedef OSG::Pnt3fx *Pnt3fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3fx *Pnt3fxP;

/*! \var typedef OSG::Point< OSG::Real64, 3 > Pnt3d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real64, 3 > Pnt3d;

/*! \var typedef OSG::Pnt3d *Pnt3dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3d *Pnt3dP;

/*! \var typedef OSG::Point< OSG::Real128, 3 > Pnt3ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real128, 3 > Pnt3ld;

/*! \var typedef OSG::Pnt3ld *Pnt3ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt3ld *Pnt3ldP;


/*! \var typedef OSG::Point< OSG::UInt8, 4 > Pnt4ub;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt8, 4 > Pnt4ub;

/*! \var typedef OSG::Pnt4ub *Pnt4ubP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4ub *Pnt4ubP;

#ifndef OSG_NO_INT8_PNT
/*! \var typedef OSG::Point< OSG::Int8, 4 > Pnt4b;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int8, 4 > Pnt4b;

/*! \var typedef OSG::Pnt4b *Pnt4bP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4b *Pnt4bP;
#endif

/*! \var typedef OSG::Point< OSG::UInt16, 4 > Pnt4us;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::UInt16, 4 > Pnt4us;

/*! \var typedef OSG::Pnt4us *Pnt4usP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4us *Pnt4usP;

/*! \var typedef OSG::Point< OSG::Int16, 4 > Pnt4s;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Int16, 4 > Pnt4s;

/*! \var typedef OSG::Pnt4s *Pnt4sP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4s *Pnt4sP;

/*! \var typedef OSG::Point< OSG::Real32, 4 > Pnt4f;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real32, 4 > Pnt4f;

/*! \var typedef OSG::Pnt4f *Pnt4fP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4f *Pnt4fP;

/*! \var typedef OSG::Point< Fixed32, 4 > Pnt4fx;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< Fixed32, 4 > Pnt4fx;

/*! \var typedef OSG::Pnt4fx *Pnt4fxP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4fx *Pnt4fxP;

/*! \var typedef OSG::Point< OSG::Real64, 4 > Pnt4d;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real64, 4 > Pnt4d;

/*! \var typedef OSG::Pnt4d *Pnt4dP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4d *Pnt4dP;

/*! \var typedef OSG::Point< OSG::Real128, 4 > Pnt4ld;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Point< OSG::Real128, 4 > Pnt4ld;

/*! \var typedef OSG::Pnt4ld *Pnt4ldP;
    \ingroup GrpBaseBaseMathObj
    \relatesalso OSG::Point
 */

typedef OSG::Pnt4ld *Pnt4ldP;

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#include "OSGVector.inl"


#ifdef __sgi
#pragma reset woff 1209
#endif

#endif /* OSGVECTOR_H */


