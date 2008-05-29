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

template<class ValueTypeT, class StorageInterfaceT>
class PointInterface;

template<class ValueTypeT, class StorageInterfaceT>
class VectorInterface;


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

template<class ValueTypeT, class StorageInterfaceT>
class PointInterface : public StorageInterfaceT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          StorageInterfaceT                      Inherited;

    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

    typedef          ValueTypeT                             ValueType;

    typedef          VectorInterface<ValueTypeT, 
                                     StorageInterfaceT>     VecInterface;


    typedef          PointInterface <ValueTypeT, 
                                     StorageInterfaceT>     Self;

    static  const    PointInterface                         Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PointInterface(      void                  );

    PointInterface(const ValueTypeT     *pVals );
    PointInterface(      ValueTypeT     *pVals );

    template <class ValueType2T, class StorageInterface2T> 
    PointInterface(const PointInterface<ValueType2T, 
                                        StorageInterface2T> &vec);

    template <class ValueType2T, class StorageInterface2T> 
    PointInterface(const VectorInterface<ValueType2T, 
                                         StorageInterface2T> &vec);

    
    
    PointInterface(const PointInterface &source);

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    PointInterface(const ValueTypeT rVal1);

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2);

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                   const ValueTypeT rVal3);

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                   const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~PointInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void setNull (void);


    //void setValue(const ValueTypeT     &rVal1);

    void setValue(const PointInterface &vec     );

    template <class ValueType2T, class StorageInterface2T> 
    void setValue(const PointInterface<ValueType2T, 
                                       StorageInterface2T> &vec);

    void setValue           (const ValueTypeT     *pVals   );
    void setValue           (      ValueTypeT     *pVals   );

    void setValueFromCString(const Char8          *szString);
    void setValueFromCString(      Char8          *szString);

#ifndef OSG_DISABLE_DEPRECATED
    void setValue           (const Char8          *szString);
    void setValue           (      Char8          *szString);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Values                                  */
    /*! \{                                                                 */

          ValueTypeT *getValues(void);
    const ValueTypeT *getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

          bool            isZero  (      void                     ) const;

          void            negate  (      void                     );

          bool            equals  (const PointInterface &vec,
                                   const ValueTypeT      tolerance) const;

          VecInterface   &subZero (      void                     );
    const VecInterface   &subZero (      void                     ) const;

          RealReturnType  dist    (const PointInterface &vec      ) const;
          RealReturnType  dist2   (const PointInterface &vec      ) const;

          RealReturnType  maxValue(      void                     ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void            operator *=(const ValueTypeT      val );
    void            operator /=(const ValueTypeT      val );

    VecInterface    operator - (const PointInterface &vec ) const;

    PointInterface  operator + (const VecInterface   &vec ) const;

    PointInterface  operator - (const VecInterface   &vec ) const;

    PointInterface  operator * (const ValueTypeT      rVal) const;

    PointInterface  operator - (      void                );

    void            operator +=(const VecInterface   &vec );
    void            operator -=(const VecInterface   &vec );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Element Access                             */
    /*! \{                                                                 */

           ValueTypeT &operator[](const UInt32 uiVal);
    const  ValueTypeT &operator[](const UInt32 uiVal) const;

    /* Cast operator, cast VecBase to ValueTypeT *
       Bad Bad idea, in my opion to buggy to be used, use getValues
       Const cast operator, cast VecBase to ValueTypeT *

       operator       ValueTypeT *(void);
       operator const ValueTypeT *(void);
    */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    PointInterface &operator =(const PointInterface &source);
    PointInterface &operator =(const VecInterface   &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const PointInterface &other)  const;

    bool operator == (const PointInterface &other) const;
    bool operator != (const PointInterface &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};


template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                         val,
               const PointInterface<ValueTypeT,
                                    StorageInterfaceT> &vec);

template <class ValueTypeT,
          class StorageInterfaceT> inline
std::ostream &operator <<(        std::ostream                 &os,
                          const   PointInterface<ValueTypeT,
                                            StorageInterfaceT> &obj);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector Interface, for details about how vectors, points and matrices
    are actually build see \guide(BaseMath).
    \ingroup GrpBaseBaseMathObj
 */

template<class ValueTypeT, class StorageInterfaceT>
class VectorInterface :
    public PointInterface<ValueTypeT, StorageInterfaceT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          PointInterface<ValueTypeT,
                                    StorageInterfaceT>      Inherited;

    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

    typedef                        ValueTypeT               ValueType;

    typedef          Inherited                              PntInterface;

    typedef          VectorInterface<ValueTypeT, 
                                     StorageInterfaceT>     Self;

    static  const    VectorInterface                        Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VectorInterface(      void                   );

    VectorInterface(const ValueTypeT      *pVals );
    VectorInterface(      ValueTypeT      *pVals );

    template <class ValueType2T, class StorageInterface2T> 
    VectorInterface(const PointInterface<ValueType2T, 
                                         StorageInterface2T> &vec);

    template <class ValueType2T, class StorageInterface2T> 
    VectorInterface(const VectorInterface<ValueType2T, 
                                          StorageInterface2T> &vec);


    VectorInterface(const VectorInterface &source);


    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    VectorInterface(const ValueTypeT rVal1);

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2);

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                    const ValueTypeT rVal3);

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                    const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VectorInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

    RealReturnType  length       (      void                  ) const;
    RealReturnType  squareLength (      void                  ) const;

    void            normalize    (      void                  );

    VectorInterface cross        (const VectorInterface &vec  ) const;
    VectorInterface operator %   (const VectorInterface &vec  ) const;

    void            crossThis    (const VectorInterface &vec  );

    ValueTypeT      dot          (const VectorInterface &vec  ) const;
    ValueTypeT      operator *   (const VectorInterface &vec  ) const;
    ValueTypeT      dot          (const PntInterface    &pnt  ) const;
    ValueTypeT      operator *   (const PntInterface    &pnt  ) const;

    RealReturnType  enclosedAngle(const VectorInterface &vec  ) const;

    RealReturnType  projectTo    (const VectorInterface &toVec);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Conv                                    */
    /*! \{                                                                 */

          PntInterface    &addToZero (void);
    const PntInterface    &addToZero (void) const;

          VectorInterface &subZero   (void);
    const VectorInterface &subZero   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    VectorInterface operator - (const VectorInterface &vec ) const;
    VectorInterface operator + (const VectorInterface &vec ) const;

    VectorInterface operator * (const ValueTypeT       rVal) const;

    VectorInterface operator - (      void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    VectorInterface &operator =(const VectorInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const VectorInterface &other) const;

    bool operator == (const VectorInterface &other) const;
    bool operator != (const VectorInterface &other) const;

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
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                          val,
               const VectorInterface<ValueTypeT,
                                     StorageInterfaceT> &vec);

template <class ValueTypeT,
          class StorageInterfaceT> inline
std::ostream &operator <<(        std::ostream                  &os,
                          const   VectorInterface<ValueTypeT,
                                             StorageInterfaceT> &obj);


// Actual Types


/*! \var typedef VectorInterface< UInt8, VecStorage1<UInt8> > Vec1ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt8, VecStorage1<UInt8> > Vec1ub;

/*! \var typedef Vec1ub *Vec1ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1ub *Vec1ubP;

/*! \var typedef VectorInterface< Int8, VecStorage1<Int8> > Vec1b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef VectorInterface< Int8, VecStorage1<Int8> > Vec1b;
#endif

/*! \var typedef Vec1b *Vec1bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec1b *Vec1bP;
#endif

/*! \var typedef VectorInterface< UInt16, VecStorage1<UInt16> > Vec1us;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt16, VecStorage1<UInt16> > Vec1us;

/*! \var typedef Vec1us *Vec1usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1us *Vec1usP;

/*! \var typedef VectorInterface< Int16, VecStorage1<Int16> > Vec1s;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Int16, VecStorage1<Int16> > Vec1s;

/*! \var typedef Vec1s *Vec1sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1s *Vec1sP;

/*! \var typedef VectorInterface< Real32, VecStorage1<Real32> > Vec1f;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real32, VecStorage1<Real32> > Vec1f;

/*! \var typedef Vec1f *Vec1fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1f *Vec1fP;

/*! \var typedef VectorInterface< Fixed32, VecStorage1<Fixed32> > Vec1fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Fixed32, VecStorage1<Fixed32> > Vec1fx;

/*! \var typedef Vec1fx *Vec1fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1fx *Vec1fxP;

/*! \var typedef VectorInterface< Real64, VecStorage1<Real64> > Vec1d;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real64, VecStorage1<Real64> > Vec1d;

/*! \var typedef Vec1d *Vec1dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1d *Vec1dP;

/*! \var typedef VectorInterface< Real128, VecStorage1<Real128> > Vec1ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real128, VecStorage1<Real128> > Vec1ld;

/*! \var typedef Vec1ld *Vec1ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec1ld *Vec1ldP;


/*! \var typedef VectorInterface< UInt8, VecStorage2<UInt8> > Vec2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt8, VecStorage2<UInt8> > Vec2ub;

/*! \var typedef Vec2ub *Vec2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ub *Vec2ubP;

/*! \var typedef VectorInterface< Int8, VecStorage2<Int8> > Vec2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef VectorInterface< Int8, VecStorage2<Int8> > Vec2b;
#endif

/*! \var typedef Vec2b *Vec2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec2b *Vec2bP;
#endif

/*! \var typedef VectorInterface< UInt16, VecStorage2<UInt16> > Vec2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt16, VecStorage2<UInt16> > Vec2us;

/*! \var typedef Vec2us *Vec2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2us *Vec2usP;

/*! \var typedef VectorInterface< Int16, VecStorage2<Int16> > Vec2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Int16, VecStorage2<Int16> > Vec2s;

/*! \var typedef Vec2s *Vec2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2s *Vec2sP;

/*! \var typedef VectorInterface< Int32, VecStorage2<Int32> > Vec2i;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Int32, VecStorage2<Int32> > Vec2i;

/*! \var typedef Vec2i *Vec2iP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2i *Vec2iP;

/*! \var typedef VectorInterface< Real32, VecStorage2<Real32> > Vec2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real32,  VecStorage2<Real32 > > Vec2f;

/*! \var typedef Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2f *Vec2fP;

/*! \var typedef VectorInterface< Fixed32, VecStorage2<Fixed32> > Vec2fx;
    \ingroup GrpBaseBaseMathObj
 */


typedef VectorInterface< Fixed32, VecStorage2<Fixed32> > Vec2fx;

/*! \var typedef Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2fx *Vec2fxP;

/*! \var typedef VectorInterface< Real64, VecStorage2<Real64> > Vec2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real64, VecStorage2<Real64> > Vec2d;

/*! \var typedef Vec2d *Vec2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2d *Vec2dP;

/*! \var typedef VectorInterface< Real128, VecStorage2<Real128> > Vec2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real128, VecStorage2<Real128> > Vec2ld;

/*! \var typedef Vec2ld *Vec2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ld *Vec2ldP;


/*! \var typedef VectorInterface< UInt8, VecStorage3<UInt8> > Vec3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt8, VecStorage3<UInt8> > Vec3ub;

/*! \var typedef Vec3ub *Vec3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ub *Vec3ubP;

/*! \var typedef VectorInterface< Int8, VecStorage3<Int8> > Vec3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef VectorInterface< Int8, VecStorage3<Int8> > Vec3b;
#endif

/*! \var typedef Vec3b *Vec3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec3b *Vec3bP;
#endif

/*! \var typedef VectorInterface< UInt16, VecStorage3<UInt16> > Vec3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt16, VecStorage3<UInt16> > Vec3us;

/*! \var typedef Vec3us *Vec3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3us *Vec3usP;

/*! \var typedef VectorInterface< Int16, VecStorage3<Int16> > Vec3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Int16, VecStorage3<Int16> > Vec3s;

/*! \var typedef Vec3s *Vec3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3s *Vec3sP;

/*! \var typedef VectorInterface< Real32, VecStorage3<Real32> > Vec3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface < Real32, VecStorage3<Real32>  > Vec3f;

/*! \var typedef Vec3f *Vec3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3f *Vec3fP;

/*! \var typedef VectorInterface< Fixed32, VecStorage3<Fixed32> > Vec3fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Fixed32, VecStorage3<Fixed32> > Vec3fx;

/*! \var typedef Vec3fx *Vec3fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3fx *Vec3fxP;

/*! \var typedef VectorInterface< Real64, VecStorage3<Real64> > Vec3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real64, VecStorage3<Real64> > Vec3d;

/*! \var typedef Vec3d *Vec3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3d *Vec3dP;

/*! \var typedef VectorInterface< Real128, VecStorage3<Real128> > Vec3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real128, VecStorage3<Real128> > Vec3ld;

/*! \var typedef Vec3ld *Vec3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ld *Vec3ldP;


/*! \var typedef VectorInterface< UInt8, VecStorage4<UInt8> > Vec4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt8, VecStorage4<UInt8> > Vec4ub;

/*! \var typedef Vec4ub *Vec4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ub *Vec4ubP;

/*! \var typedef VectorInterface< Int8, VecStorage4<Int8> > Vec4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef VectorInterface< Int8, VecStorage4<Int8> > Vec4b;
#endif

/*! \var typedef Vec4b *Vec4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec4b *Vec4bP;
#endif

/*! \var typedef VectorInterface< UInt16, VecStorage4<UInt16> > Vec4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< UInt16, VecStorage4<UInt16> > Vec4us;

/*! \var typedef Vec4us *Vec4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4us *Vec4usP;

/*! \var typedef VectorInterface< Int16, VecStorage4<Int16> > Vec4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Int16, VecStorage4<Int16> > Vec4s;

/*! \var typedef Vec4s *Vec4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4s *Vec4sP;

/*! \var typedef VectorInterface< Real32, VecStorage4<Real32> > Vec4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real32,  VecStorage4<Real32 > > Vec4f;

/*! \var typedef Vec4f *Vec4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4f *Vec4fP;

/*! \var typedef VectorInterface< Fixed32, VecStorage4<Fixed32> > Vec4fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Fixed32, VecStorage4<Fixed32> > Vec4fx;

/*! \var typedef Vec4fx *Vec4fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4fx *Vec4fxP;

/*! \var typedef VectorInterface< Real64, VecStorage4<Real64> > Vec4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real64, VecStorage4<Real64> > Vec4d;

/*! \var typedef Vec4d *Vec4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4d *Vec4dP;

/*! \var typedef VectorInterface< Real128, VecStorage4<Real128> > Vec4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef VectorInterface< Real128, VecStorage4<Real128> > Vec4ld;

/*! \var typedef Vec4ld *Vec4ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ld *Vec4ldP;




/*! \var typedef PointInterface< UInt8, VecStorage1<UInt8> > Pnt1ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt8, VecStorage1<UInt8> > Pnt1ub;

/*! \var typedef Pnt1ub *Pnt1ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1ub *Pnt1ubP;

/*! \var typedef PointInterface< Int8, VecStorage1<Int8> > Pnt1b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef PointInterface< Int8, VecStorage1<Int8> > Pnt1b;
#endif

/*! \var typedef Pnt1b *Pnt1bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt1b *Pnt1bP;
#endif

/*! \var typedef PointInterface< UInt16, VecStorage1<UInt16> > Pnt1us;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt16, VecStorage1<UInt16> > Pnt1us;

/*! \var typedef Pnt1us *Pnt1usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1us *Pnt1usP;

/*! \var typedef PointInterface< Int16, VecStorage1<Int16> > Pnt1s;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Int16, VecStorage1<Int16> > Pnt1s;

/*! \var typedef Pnt1s *Pnt1sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1s *Pnt1sP;

/*! \var typedef PointInterface< Real32, VecStorage1<Real32> > Pnt1f;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real32, VecStorage1<Real32> > Pnt1f;

/*! \var typedef Pnt1f *Pnt1fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1f *Pnt1fP;

/*! \var typedef PointInterface< Fixed32, VecStorage1<Fixed32> > Pnt1fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Fixed32, VecStorage1<Fixed32> > Pnt1fx;

/*! \var typedef Pnt1fx *Pnt1fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1fx *Pnt1fxP;

/*! \var typedef PointInterface< Real64, VecStorage1<Real64> > Pnt1d;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real64, VecStorage1<Real64> > Pnt1d;

/*! \var typedef Pnt1d *Pnt1dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1d *Pnt1dP;

/*! \var typedef PointInterface< Real128, VecStorage1<Real128> > Pnt1ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real128, VecStorage1<Real128> > Pnt1ld;

/*! \var typedef Pnt1ld *Pnt1ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt1ld *Pnt1ldP;



/*! \var typedef PointInterface< UInt8, VecStorage2<UInt8> > Pnt2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt8, VecStorage2<UInt8> > Pnt2ub;

/*! \var typedef Pnt2ub *Pnt2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ub *Pnt2ubP;

/*! \var typedef PointInterface< Int8, VecStorage2<Int8> > Pnt2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef PointInterface< Int8, VecStorage2<Int8> > Pnt2b;
#endif

/*! \var typedef Pnt2b *Pnt2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt2b *Pnt2bP;
#endif

/*! \var typedef PointInterface< UInt16, VecStorage2<UInt16> > Pnt2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt16, VecStorage2<UInt16> > Pnt2us;

/*! \var typedef Pnt2us *Pnt2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2us *Pnt2usP;

/*! \var typedef PointInterface< Int16, VecStorage2<Int16> > Pnt2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Int16, VecStorage2<Int16> > Pnt2s;

/*! \var typedef Pnt2s *Pnt2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2s *Pnt2sP;

/*! \var typedef PointInterface< Int32, VecStorage2<Int32> > Pnt2i;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Int32, VecStorage2<Int32> > Pnt2i;

/*! \var typedef Pnt2i *Pnt2iP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2i *Pnt2iP;

/*! \var typedef PointInterface< Real32, VecStorage2<Real32> > Pnt2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real32,  VecStorage2<Real32 > > Pnt2f;

/*! \var typedef Pnt2f *Pnt2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2f *Pnt2fP;

/*! \var typedef PointInterface< Fixed32, VecStorage2<Fixed32> > Pnt2fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Fixed32, VecStorage2<Fixed32> > Pnt2fx;

/*! \var typedef Pnt2fx *Pnt2fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2fx *Pnt2fxP;

/*! \var typedef PointInterface< Real64, VecStorage2<Real64> > Pnt2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real64, VecStorage2<Real64> > Pnt2d;

/*! \var typedef Pnt2d *Pnt2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2d *Pnt2dP;

/*! \var typedef PointInterface< Real128, VecStorage2<Real128> > Pnt2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real128, VecStorage2<Real128> > Pnt2ld;

/*! \var typedef Pnt2ld *Pnt2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ld *Pnt2ldP;


/*! \var typedef PointInterface< UInt8, VecStorage3<UInt8> > Pnt3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt8, VecStorage3<UInt8> > Pnt3ub;

/*! \var typedef Pnt3ub *Pnt3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ub *Pnt3ubP;

/*! \var typedef PointInterface< Int8, VecStorage3<Int8> > Pnt3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef PointInterface< Int8, VecStorage3<Int8> > Pnt3b;
#endif

/*! \var typedef Pnt3b *Pnt3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt3b *Pnt3bP;
#endif

/*! \var typedef PointInterface< UInt16, VecStorage3<UInt16> > Pnt3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt16, VecStorage3<UInt16> > Pnt3us;

/*! \var typedef Pnt3us *Pnt3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3us *Pnt3usP;

/*! \var typedef PointInterface< Int16, VecStorage3<Int16> > Pnt3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Int16, VecStorage3<Int16> > Pnt3s;

/*! \var typedef Pnt3s *Pnt3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3s *Pnt3sP;

/*! \var typedef PointInterface< Real32, VecStorage3<Real32> > Pnt3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real32, VecStorage3<Real32   > > Pnt3f;

/*! \var typedef Pnt3f *Pnt3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3f *Pnt3fP;

/*! \var typedef PointInterface< Fixed32, VecStorage3<Fixed32> > Pnt3fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface < Fixed32, VecStorage3<Fixed32> > Pnt3fx;

/*! \var typedef Pnt3fx *Pnt3fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3fx *Pnt3fxP;

/*! \var typedef PointInterface< Real64, VecStorage3<Real64> > Pnt3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real64, VecStorage3<Real64> > Pnt3d;

/*! \var typedef Pnt3d *Pnt3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3d *Pnt3dP;

/*! \var typedef PointInterface< Real128, VecStorage3<Real128> > Pnt3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real128, VecStorage3<Real128> > Pnt3ld;

/*! \var typedef Pnt3ld *Pnt3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ld *Pnt3ldP;


/*! \var typedef PointInterface< UInt8, VecStorage4<UInt8> > Pnt4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt8, VecStorage4<UInt8> > Pnt4ub;

/*! \var typedef Pnt4ub *Pnt4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4ub *Pnt4ubP;

/*! \var typedef PointInterface< Int8, VecStorage4<Int8> > Pnt4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef PointInterface< Int8, VecStorage4<Int8> > Pnt4b;
#endif

/*! \var typedef Pnt4b *Pnt4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt4b *Pnt4bP;
#endif

/*! \var typedef PointInterface< UInt16, VecStorage4<UInt16> > Pnt4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< UInt16, VecStorage4<UInt16> > Pnt4us;

/*! \var typedef Pnt4us *Pnt4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4us *Pnt4usP;

/*! \var typedef PointInterface< Int16, VecStorage4<Int16> > Pnt4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Int16, VecStorage4<Int16> > Pnt4s;

/*! \var typedef Pnt4s *Pnt4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4s *Pnt4sP;

/*! \var typedef PointInterface< Real32, VecStorage4<Real32> > Pnt4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real32, VecStorage4<Real32> > Pnt4f;

/*! \var typedef Pnt4f *Pnt4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4f *Pnt4fP;

/*! \var typedef PointInterface< Fixed32, VecStorage4<Fixed32> > Pnt4fx;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Fixed32, VecStorage4<Fixed32> > Pnt4fx;

/*! \var typedef Pnt4fx *Pnt4fxP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4fx *Pnt4fxP;

/*! \var typedef PointInterface< Real64, VecStorage4<Real64> > Pnt4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real64, VecStorage4<Real64> > Pnt4d;

/*! \var typedef Pnt4d *Pnt4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4d *Pnt4dP;

/*! \var typedef PointInterface< Real128, VecStorage4<Real128> > Pnt4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef PointInterface< Real128, VecStorage4<Real128> > Pnt4ld;

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


