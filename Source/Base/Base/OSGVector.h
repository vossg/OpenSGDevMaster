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
    points and matrices are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
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
    points and matrices are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
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
    points and matrices are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
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
    points and matrices are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
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


/*! \struct SelectVecStorage<ValueTypeT,SizeI>
    \brief Helper struct to select the correct storage class for vector types.
 */
template <class ValueTypeT, UInt32 SizeI>
struct SelectVecStorage;

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 1>
{
    typedef VecStorage1<ValueTypeT> type;
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 2>
{
    typedef VecStorage2<ValueTypeT> type;
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 3>
{
    typedef VecStorage3<ValueTypeT> type;
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 4>
{
    typedef VecStorage4<ValueTypeT> type;
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Point Interface, for details about how vectors, points and matrices
    are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
 */

#ifdef __sgi
#pragma set woff 1375
#endif

template <class ValueTypeT, UInt32 SizeI>
class Point : public SelectVecStorage<ValueTypeT, SizeI>::type
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename SelectVecStorage<ValueTypeT,
                                      SizeI      >::type    Inherited;
    typedef          Point           <ValueTypeT, 
                                      SizeI      >          Self;
    typedef typename SelectVecStorage<ValueTypeT,
                                      SizeI      >::type    StorageInterface;
    
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

          bool            isZero  (      void                     ) const;

          void            negate  (      void                     );

          bool            equals  (const Point      &pnt,
                                   const ValueType       tolerance) const;

          VectorType     &subZero (      void                     );
    const VectorType     &subZero (      void                     ) const;

          RealReturnType  dist    (const Point &pnt      ) const;
          RealReturnType  dist2   (const Point &pnt      ) const;

          RealReturnType  maxValue(      void                     ) const;

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

    Point      operator - (void                 );

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


template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    operator *(const ValueTypeT                val,
               const Point<ValueTypeT, SizeI> &pnt );

template <class  ValueTypeT,
          UInt32 SizeI      > inline
std::ostream &operator <<(      std::ostream             &os,
                          const Point<ValueTypeT, SizeI> &pnt);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector Interface, for details about how vectors, points and matrices
    are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
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

    RealReturnType length       (      void            ) const;
    RealReturnType squareLength (      void            ) const;

    void           normalize    (      void            );

    Vector         cross        (const Vector    &vec  ) const;
    Vector         operator %   (const Vector    &vec  ) const;

    void           crossThis    (const Vector    &vec  );

    ValueType      dot          (const Vector    &vec  ) const;
    ValueType      operator *   (const Vector    &vec  ) const;
    ValueType      dot          (const PointType &pnt  ) const;
    ValueType      operator *   (const PointType &pnt  ) const;

    RealReturnType enclosedAngle(const Vector    &vec  ) const;

    RealReturnType projectTo    (const Vector    &toVec);

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

template <class ValueTypeT,
          UInt32 SizeI     > inline
Vector<ValueTypeT, SizeI>
    operator *(const ValueTypeT                 val,
               const Vector<ValueTypeT, SizeI> &vec );

template <class ValueTypeT,
          UInt32 SizeI     > inline
std::ostream &operator <<(        std::ostream              &os,
                          const   Vector<ValueTypeT, SizeI> &obj);


// Actual Types


/*! \var typedef Vector< UInt8, 1 > Vec1ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt8, 1> Vec1ub;

/*! \var typedef Vec1ub *Vec1ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1ub *Vec1ubP;

/*! \var typedef Vector< Int8, 1 > Vec1b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector< Int8, 1 > Vec1b;
#endif

/*! \var typedef Vec1b *Vec1bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec1b *Vec1bP;
#endif

/*! \var typedef Vector< UInt16, 1 > Vec1us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt16, 1 > Vec1us;

/*! \var typedef Vec1us *Vec1usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1us *Vec1usP;

/*! \var typedef Vector< Int16, 1 > Vec1s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Int16, 1 > Vec1s;

/*! \var typedef Vec1s *Vec1sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1s *Vec1sP;

/*! \var typedef Vector< Real32, 1 > Vec1f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real32, 1 > Vec1f;

/*! \var typedef Vec1f *Vec1fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1f *Vec1fP;

/*! \var typedef Vector< Fixed32, 1 > Vec1fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Fixed32, 1 > Vec1fx;

/*! \var typedef Vec1fx *Vec1fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1fx *Vec1fxP;

/*! \var typedef Vector< Real64, 1 > Vec1d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real64, 1 > Vec1d;

/*! \var typedef Vec1d *Vec1dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1d *Vec1dP;

/*! \var typedef Vector< Real128, 1 > Vec1ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real128, 1 > Vec1ld;

/*! \var typedef Vec1ld *Vec1ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1ld *Vec1ldP;


/*! \var typedef Vector< UInt8, 2 > Vec2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt8, 2 > Vec2ub;

/*! \var typedef Vec2ub *Vec2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ub *Vec2ubP;

/*! \var typedef Vector< Int8, 2 > Vec2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector< Int8, 2 > Vec2b;
#endif

/*! \var typedef Vec2b *Vec2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec2b *Vec2bP;
#endif

/*! \var typedef Vector< UInt16, 2 > Vec2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt16, 2 > Vec2us;

/*! \var typedef Vec2us *Vec2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2us *Vec2usP;

/*! \var typedef Vector< Int16, 2 > Vec2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Int16, 2 > Vec2s;

/*! \var typedef Vec2s *Vec2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2s *Vec2sP;

/*! \var typedef Vector< Int32, 2 > Vec2i;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Int32, 2 > Vec2i;

/*! \var typedef Vec2i *Vec2iP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2i *Vec2iP;

/*! \var typedef Vector< Real32, 2 > Vec2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real32, 2 > Vec2f;

/*! \var typedef Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2f *Vec2fP;

/*! \var typedef Vector< Fixed32, 2 > Vec2fx;
    \ingroup GrpBaseBaseMathObj
 */


typedef Vector< Fixed32, 2 > Vec2fx;

/*! \var typedef Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2fx *Vec2fxP;

/*! \var typedef Vector< Real64, 2 > Vec2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real64, 2 > Vec2d;

/*! \var typedef Vec2d *Vec2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2d *Vec2dP;

/*! \var typedef Vector< Real128, 2 > Vec2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real128, 2 > Vec2ld;

/*! \var typedef Vec2ld *Vec2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ld *Vec2ldP;


/*! \var typedef Vector< UInt8, 3 > Vec3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt8, 3 > Vec3ub;

/*! \var typedef Vec3ub *Vec3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ub *Vec3ubP;

/*! \var typedef Vector< Int8, 3 > Vec3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector< Int8, 3 > Vec3b;
#endif

/*! \var typedef Vec3b *Vec3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec3b *Vec3bP;
#endif

/*! \var typedef Vector< UInt16, 3 > Vec3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt16, 3 > Vec3us;

/*! \var typedef Vec3us *Vec3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3us *Vec3usP;

/*! \var typedef Vector< Int16, 3 > Vec3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Int16, 3 > Vec3s;

/*! \var typedef Vec3s *Vec3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3s *Vec3sP;

/*! \var typedef Vector< Real32, 3 > Vec3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector < Real32, 3  > Vec3f;

/*! \var typedef Vec3f *Vec3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3f *Vec3fP;

/*! \var typedef Vector< Fixed32, 3 > Vec3fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Fixed32, 3 > Vec3fx;

/*! \var typedef Vec3fx *Vec3fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3fx *Vec3fxP;

/*! \var typedef Vector< Real64, 3 > Vec3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real64, 3 > Vec3d;

/*! \var typedef Vec3d *Vec3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3d *Vec3dP;

/*! \var typedef Vector< Real128, 3 > Vec3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real128, 3 > Vec3ld;

/*! \var typedef Vec3ld *Vec3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ld *Vec3ldP;


/*! \var typedef Vector< UInt8, 4 > Vec4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt8, 4 > Vec4ub;

/*! \var typedef Vec4ub *Vec4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ub *Vec4ubP;

/*! \var typedef Vector< Int8, 4 > Vec4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector< Int8, 4 > Vec4b;
#endif

/*! \var typedef Vec4b *Vec4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec4b *Vec4bP;
#endif

/*! \var typedef Vector< UInt16, 4 > Vec4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< UInt16, 4 > Vec4us;

/*! \var typedef Vec4us *Vec4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4us *Vec4usP;

/*! \var typedef Vector< Int16, 4 > Vec4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Int16, 4 > Vec4s;

/*! \var typedef Vec4s *Vec4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4s *Vec4sP;

/*! \var typedef Vector< Real32, 4 > Vec4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real32,  4 > Vec4f;

/*! \var typedef Vec4f *Vec4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4f *Vec4fP;

/*! \var typedef Vector< Fixed32, 4 > Vec4fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Fixed32, 4 > Vec4fx;

/*! \var typedef Vec4fx *Vec4fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4fx *Vec4fxP;

/*! \var typedef Vector< Real64, 4 > Vec4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real64, 4 > Vec4d;

/*! \var typedef Vec4d *Vec4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4d *Vec4dP;

/*! \var typedef Vector< Real128, 4 > Vec4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector< Real128, 4 > Vec4ld;

/*! \var typedef Vec4ld *Vec4ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ld *Vec4ldP;




/*! \var typedef Point< UInt8, 1 > Pnt1ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt8, 1 > Pnt1ub;

/*! \var typedef Pnt1ub *Pnt1ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1ub *Pnt1ubP;

/*! \var typedef Point< Int8, 1 > Pnt1b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point< Int8, 1 > Pnt1b;
#endif

/*! \var typedef Pnt1b *Pnt1bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt1b *Pnt1bP;
#endif

/*! \var typedef Point< UInt16, 1 > Pnt1us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt16, 1 > Pnt1us;

/*! \var typedef Pnt1us *Pnt1usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1us *Pnt1usP;

/*! \var typedef Point< Int16, 1 > Pnt1s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Int16, 1 > Pnt1s;

/*! \var typedef Pnt1s *Pnt1sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1s *Pnt1sP;

/*! \var typedef Point< Real32, 1 > Pnt1f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real32, 1 > Pnt1f;

/*! \var typedef Pnt1f *Pnt1fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1f *Pnt1fP;

/*! \var typedef Point< Fixed32, 1 > Pnt1fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Fixed32, 1 > Pnt1fx;

/*! \var typedef Pnt1fx *Pnt1fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1fx *Pnt1fxP;

/*! \var typedef Point< Real64, 1 > Pnt1d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real64, 1 > Pnt1d;

/*! \var typedef Pnt1d *Pnt1dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1d *Pnt1dP;

/*! \var typedef Point< Real128, 1 > Pnt1ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real128, 1 > Pnt1ld;

/*! \var typedef Pnt1ld *Pnt1ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1ld *Pnt1ldP;



/*! \var typedef Point< UInt8, 2 > Pnt2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt8, 2 > Pnt2ub;

/*! \var typedef Pnt2ub *Pnt2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ub *Pnt2ubP;

/*! \var typedef Point< Int8, 2 > Pnt2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point< Int8, 2 > Pnt2b;
#endif

/*! \var typedef Pnt2b *Pnt2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt2b *Pnt2bP;
#endif

/*! \var typedef Point< UInt16, 2 > Pnt2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt16, 2 > Pnt2us;

/*! \var typedef Pnt2us *Pnt2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2us *Pnt2usP;

/*! \var typedef Point< Int16, 2 > Pnt2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Int16, 2 > Pnt2s;

/*! \var typedef Pnt2s *Pnt2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2s *Pnt2sP;

/*! \var typedef Point< Int32, 2 > Pnt2i;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Int32, 2 > Pnt2i;

/*! \var typedef Pnt2i *Pnt2iP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2i *Pnt2iP;

/*! \var typedef Point< Real32, 2 > Pnt2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real32,  2 > Pnt2f;

/*! \var typedef Pnt2f *Pnt2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2f *Pnt2fP;

/*! \var typedef Point< Fixed32, 2 > Pnt2fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Fixed32, 2 > Pnt2fx;

/*! \var typedef Pnt2fx *Pnt2fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2fx *Pnt2fxP;

/*! \var typedef Point< Real64, 2 > Pnt2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real64, 2 > Pnt2d;

/*! \var typedef Pnt2d *Pnt2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2d *Pnt2dP;

/*! \var typedef Point< Real128, 2 > Pnt2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real128, 2 > Pnt2ld;

/*! \var typedef Pnt2ld *Pnt2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ld *Pnt2ldP;


/*! \var typedef Point< UInt8, 3 > Pnt3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt8, 3 > Pnt3ub;

/*! \var typedef Pnt3ub *Pnt3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ub *Pnt3ubP;

/*! \var typedef Point< Int8, 3 > Pnt3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point< Int8, 3 > Pnt3b;
#endif

/*! \var typedef Pnt3b *Pnt3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt3b *Pnt3bP;
#endif

/*! \var typedef Point< UInt16, 3 > Pnt3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt16, 3 > Pnt3us;

/*! \var typedef Pnt3us *Pnt3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3us *Pnt3usP;

/*! \var typedef Point< Int16, 3 > Pnt3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Int16, 3 > Pnt3s;

/*! \var typedef Pnt3s *Pnt3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3s *Pnt3sP;

/*! \var typedef Point< Real32, 3 > Pnt3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real32, 3 > Pnt3f;

/*! \var typedef Pnt3f *Pnt3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3f *Pnt3fP;

/*! \var typedef Point< Fixed32, 3 > Pnt3fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point < Fixed32, 3 > Pnt3fx;

/*! \var typedef Pnt3fx *Pnt3fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3fx *Pnt3fxP;

/*! \var typedef Point< Real64, 3 > Pnt3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real64, 3 > Pnt3d;

/*! \var typedef Pnt3d *Pnt3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3d *Pnt3dP;

/*! \var typedef Point< Real128, 3 > Pnt3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real128, 3 > Pnt3ld;

/*! \var typedef Pnt3ld *Pnt3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ld *Pnt3ldP;


/*! \var typedef Point< UInt8, 4 > Pnt4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt8, 4 > Pnt4ub;

/*! \var typedef Pnt4ub *Pnt4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4ub *Pnt4ubP;

/*! \var typedef Point< Int8, 4 > Pnt4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point< Int8, 4 > Pnt4b;
#endif

/*! \var typedef Pnt4b *Pnt4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt4b *Pnt4bP;
#endif

/*! \var typedef Point< UInt16, 4 > Pnt4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< UInt16, 4 > Pnt4us;

/*! \var typedef Pnt4us *Pnt4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4us *Pnt4usP;

/*! \var typedef Point< Int16, 4 > Pnt4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Int16, 4 > Pnt4s;

/*! \var typedef Pnt4s *Pnt4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4s *Pnt4sP;

/*! \var typedef Point< Real32, 4 > Pnt4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real32, 4 > Pnt4f;

/*! \var typedef Pnt4f *Pnt4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4f *Pnt4fP;

/*! \var typedef Point< Fixed32, 4 > Pnt4fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Fixed32, 4 > Pnt4fx;

/*! \var typedef Pnt4fx *Pnt4fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4fx *Pnt4fxP;

/*! \var typedef Point< Real64, 4 > Pnt4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real64, 4 > Pnt4d;

/*! \var typedef Pnt4d *Pnt4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4d *Pnt4dP;

/*! \var typedef Point< Real128, 4 > Pnt4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point< Real128, 4 > Pnt4ld;

/*! \var typedef Pnt4ld *Pnt4ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4ld *Pnt4ldP;

#ifdef OSG_FLOAT_PROFILE

typedef Vec2f Vec2r;
typedef Vec3f Vec3r;
typedef Vec4f Vec4r;

typedef Pnt2f Pnt2r;
typedef Pnt3f Pnt3r;
typedef Pnt4f Pnt4r;

#else

typedef Vec2fx Vec2r;
typedef Vec3fx Vec3r;
typedef Vec4fx Vec4r;

typedef Pnt2fx Pnt2r;
typedef Pnt3fx Pnt3r;
typedef Pnt4fx Pnt4r;

#endif

OSG_END_NAMESPACE

#include "OSGVector.inl"


#ifdef __sgi
#pragma reset woff 1209
#endif

#endif /* OSGVECTOR_H */


