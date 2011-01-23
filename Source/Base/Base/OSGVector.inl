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

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  VecStorage1
//---------------------------------------------------------------------------

/*! \var VecStorage1::VectorSizeE VecStorage1::_uiSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage1::_values[iSize];
    \brief Value store
*/

#if defined(__hpux)
template <class ValueTypeT> 
const UInt32 VecStorage1<ValueTypeT>::_uiSize;
#endif
	

template <class ValueTypeT> inline
VecStorage1<ValueTypeT>::VecStorage1(void)
{
    for(UInt32 i = 0; i < _uiSize; i++)
    {
        _values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}


template <class ValueTypeT> inline
VecStorage1<ValueTypeT>::~VecStorage1(void)
{
}


template <class ValueTypeT> inline
void VecStorage1<ValueTypeT>::setValues(const ValueTypeT rVal1)
{
    _values[0] = rVal1;
}


template <class ValueTypeT> inline
void VecStorage1<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1) const
{
    rVal1 = _values[0];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage1<ValueTypeT>::x(void) const
{
    return _values[0];
}



//---------------------------------------------------------------------------
//  VecStorage2
//---------------------------------------------------------------------------

/*! \var VecStorage2::VectorSizeE VecStorage2::_uiSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage2::_values[iSize];
    \brief Value store
*/

#if defined(__hpux)
template <class ValueTypeT> 
const UInt32 VecStorage2<ValueTypeT>::_uiSize;
#endif
	

template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::VecStorage2(void)
{
    for(UInt32 i = 0; i < _uiSize; i++)
    {
        _values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}


template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::~VecStorage2(void)
{
}


template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
}


template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::x(void) const
{
    return _values[0];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::y(void) const
{
    return _values[1];
}




//---------------------------------------------------------------------------
//  VecStorage3
//---------------------------------------------------------------------------

/*! \var VecStorage3::VectorSizeE VecStorage3::_uiSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage3::_values[iSize];
    \brief Value store
*/

#if defined(__hpux)
template <class ValueTypeT> 
const UInt32 VecStorage3<ValueTypeT>::_uiSize;
#endif


template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::VecStorage3(void)
{
    for(UInt32 i = 0; i < _uiSize; i++)
    {
        _values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}


template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::~VecStorage3(void)
{
}


template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2,
                                        const ValueTypeT rVal3)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
}


template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2,
                                                ValueTypeT &rVal3) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
    rVal3 = _values[2];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::x(void) const
{
    return _values[0];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::y(void) const
{
    return _values[1];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::z(void) const
{
    return _values[2];
}




//---------------------------------------------------------------------------
//  VecStorage4
//---------------------------------------------------------------------------

/*! \var VecStorage4::VectorSizeE VecStorage4::_uiSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage4::_values[iSize];
    \brief Value store
*/

#if defined(__hpux)
template <class ValueTypeT> inline
const UInt32 VecStorage4<ValueTypeT>::_uiSize;
#endif


template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::VecStorage4(void)
{
    for(UInt32 i = 0; i < _uiSize; i++)
    {
        _values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}


template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::~VecStorage4(void)
{
}


template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2,
                                        const ValueTypeT rVal3,
                                        const ValueTypeT rVal4)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
    _values[3] = rVal4;
}


template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2,
                                                ValueTypeT &rVal3,
                                                ValueTypeT &rVal4) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
    rVal3 = _values[2];
    rVal4 = _values[3];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::x(void) const
{
    return _values[0];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::y(void) const
{
    return _values[1];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::z(void) const
{
    return _values[2];
}


template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::w(void) const
{
    return _values[3];
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \typedef Point::Inherited
    \brief Parent type, one of the VecStorage{1,2,3,4} types
 */

/*! \typedef Point::RealReturnType
    \brief Used type if the returnvalue must be a real value
*/

/*! \typedef Point::ValueType
    \brief Value type
*/

/*! \typedef Point::PointType
    \brief Own type
*/

/*! \typedef Point::VectorType
    \brief Type of the corresponding vector of the same size and value type.
*/

#ifndef darwinXXX
template <class  ValueTypeT,
          UInt32 SizeI      >
const Point<ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::Null;
#endif


template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(void) : 
    Inherited()
{
}

/*! \brief Constructor which takes a const value array.
  
    \warning Make sure the array size is at least as large as the vector size.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const ValueTypeT *pVals) : 
    Inherited()
{
    if(pVals == NULL)
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
    else
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = pVals[i];
        }
    }
}

/*! \brief Constructor which takes a value array.
  
    Be shure the array size at least as large as the vector size.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(ValueTypeT *pVals) : 
    Inherited()
{
    if(pVals == NULL)
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
    else
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = pVals[i];
        }
    }
}

template <class  ValueTypeT,
          UInt32 SizeI       >
template <class  ValueType2T, 
          UInt32 Size2I      > inline
Point<ValueTypeT, SizeI>::Point(const Point<ValueType2T, Size2I> &pnt)
{
    typedef Point<ValueType2T, Size2I> Point2T;

    if(Self::_uiSize <= Point2T::_uiSize)
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = pnt.getValues()[i];
        }
    }
    else
    {
        UInt32 i;
        for(i = 0; i < Point2T::_uiSize; i++)
        {
            Self::_values[i] = pnt.getValues()[i];
        }
        for(i = Point2T::_uiSize; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
}

template <class  ValueTypeT,
          UInt32 SizeI       >
template <class  ValueType2T, 
          UInt32 Size2I      > inline
Point<ValueTypeT, SizeI>::Point(const Vector<ValueType2T, Size2I> &vec)
{
    typedef Vector<ValueType2T, Size2I> Vector2T;

    if(Self::_uiSize <= Vector2T::_uiSize)
    {
        for(UInt32 i = 0; i < Self::_uiSize; i++)
        {
            Self::_values[i] = vec.getValues()[i];
        }
    }
    else
    {
        UInt32 i;
        for(i = 0; i < Vector2T::_uiSize; i++)
        {
            Self::_values[i] = vec.getValues()[i];
        }
        for(i = Vector2T::_uiSize; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
}


template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const Point &source) : 

    Inherited()
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = source._values[i];
    }
}



template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const ValueType rVal1)
{
    UInt32 i;

    Self::_values[0] = rVal1;

    for(i = 1; i < Self::_uiSize; i++)
    {
        Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}



#ifdef __sgi
#pragma set woff 1209
#endif

//! Constructor which takes two values, remaining entries will be zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const ValueType rVal1,
                                const ValueType rVal2) : 
    Inherited()
{
    Self::_values[0] = rVal1;

    if(Self::_uiSize == 2)
    {
        Self::_values[1] = rVal2;
    }
    else if(Self::_uiSize >= 3)
    {
        Self::_values[1] = rVal2;

        for(UInt32 i = 2; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

//! Constructor which takes three values, remaining entries will be zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const ValueTypeT rVal1,
                                const ValueTypeT rVal2,
                                const ValueTypeT rVal3) : 
    Inherited()
{
    Self::_values[0] = rVal1;

    if(Self::_uiSize == 2)
    {
        Self::_values[1] = rVal2;
    }
    else if(Self::_uiSize == 3)
    {
        Self::_values[1] = rVal2;
        Self::_values[2] = rVal3;
    }
    else if(Self::_uiSize >= 4)
    {
        Self::_values[1] = rVal2;
        Self::_values[2] = rVal3;

        for(UInt32 i = 3; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

//! Constructor which takes four values, remaining entries will be zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::Point(const ValueTypeT rVal1,
                                const ValueTypeT rVal2,
                                const ValueTypeT rVal3,
                                const ValueTypeT rVal4 ) : 
    Inherited()
{
    Self::_values[0] = rVal1;

    if(Self::_uiSize == 2)
    {
        Self::_values[1] = rVal2;
    }
    else if(Self::_uiSize == 3)
    {
        Self::_values[1] = rVal2;
        Self::_values[2] = rVal3;
    }
    else if(Self::_uiSize == 4)
    {
        Self::_values[1] = rVal2;
        Self::_values[2] = rVal3;
        Self::_values[3] = rVal4;
    }
    else if(Self::_uiSize >= 5)
    {
        Self::_values[1] = rVal2;
        Self::_values[2] = rVal3;
        Self::_values[3] = rVal4;

        for(UInt32 i = 4; i < Self::_uiSize; i++)
        {
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>::~Point(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setNull(void)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValue(const Point &pnt)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = pnt._values[i];
    }
}

template <class  ValueTypeT,
          UInt32 SizeI       >
template <class  ValueType2T, 
          UInt32 Size2I      > inline
void Point<ValueTypeT, SizeI>::setValue(const Point<ValueType2T, Size2I> &pnt)
{
    typedef Point<ValueType2T, Size2I> Point2T;

    static const UInt32 nElementsToCopy = 
        Self::_uiSize < Point2T::_uiSize ? Self::_uiSize : Point2T::_uiSize;

    for(UInt32 i = 0; i < nElementsToCopy; ++i)
    {
        Self::_values[i] = pnt.getValues()[i];
    }
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValue(const ValueType *pVals)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = pVals[i];
    }
}

//! Set value from a given array, be sure to match sizes

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValue(ValueType *pVals)
{
    setValue(static_cast<const ValueType *>(pVals));
}

/*! \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValueFromCString(const Char8 *szString)
{
    UInt32 i;
    UInt32 numOfToken = Self::_uiSize;

    Char8 *c      = const_cast<Char8 *>(szString);
    Char8 *tokenC = 0;

    Char8  token[256];

    if(szString == NULL || (*szString) == '\0')
    {
        for(i = 0; i < Self::_uiSize; i++)
            Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();

        return;
    }

    for (i = 0; i < numOfToken; c++)
    {
        switch (*c)
        {
            case '\0':
                if(tokenC)
                {
                    *tokenC = 0;
                    Self::_values[i++] =
                        TypeTraits<ValueTypeT>::getFromCString(token);
                }

                while (i < numOfToken)
                {
                    Self::_values[i++] =
                        TypeTraits<ValueTypeT>::getZeroElement();
                }
                break;

            case ' ' :
            case '\t':
            case '\n':
            case ',':
                if(tokenC)
                {
                    *tokenC = 0;
                    Self::_values[i++] =
                        TypeTraits<ValueTypeT>::getFromCString(token);
                    tokenC = 0;
                }
                break;
            default:
                if(!tokenC)
                {
                    tokenC = token;
                }
                *tokenC++ = *c;
                break;
        }
    }
}

/*! \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
 */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValueFromCString(Char8 *szString)
{
    setValueFromCString(static_cast<const Char8 *>(szString));
}

#ifndef OSG_DISABLE_DEPRECATED
template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValue(const Char8 *szString)
{
    setValueFromCString(szString);
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::setValue(Char8 *szString)
{
    setValueFromCString(szString);
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

//! Get a pointer to the value storage

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT *Point<ValueTypeT, SizeI>::getValues(void)
{
    return Self::_values;
}

//! Get a const pointer to the value storage

template <class  ValueTypeT,
          UInt32 SizeI      > inline
const ValueTypeT *Point<ValueTypeT, SizeI>::getValues(void) const
{
    return Self::_values;
}

/*-------------------------------------------------------------------------*/
/*                        Common Math                                      */

//! Returns true iff the norm of each value is less than Eps

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Point<ValueTypeT, SizeI>::isZero(void) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue &= 
            ((Self::_values[i] <=  TypeTraits<ValueTypeT>::getDefaultEps()) &&
             (Self::_values[i] >= -TypeTraits<ValueTypeT>::getDefaultEps())   );
    }

    return returnValue;
}

//! Negates each value of the point in place

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::negate(void)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = -Self::_values[i];
    }
}

//! Returns true iff the two points are eual within a given tolerance

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Point<ValueTypeT, SizeI>::equals(
    const Point      &pnt,
    const ValueType   tolerance) const
{
    bool returnValue = true;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue &= 
            ( (Self::_values[i] - pnt  ._values[i] <= tolerance) &&
              (pnt  ._values[i] - Self::_values[i] <= tolerance));
    }

    return returnValue;
}

//! Returns the corrosponding vector by subtracting zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Point<ValueTypeT, SizeI>::VectorType &
    Point<ValueTypeT, SizeI>::subZero(void)
{
    return *(static_cast<VectorType *>(this));
}

//! Returns the corrosponding vector by subtracting zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
const typename Point<ValueTypeT, SizeI>::VectorType &
    Point<ValueTypeT, SizeI>::subZero(void) const
{
    return *(static_cast<const VectorType *>(this));
}


//! Returns the distance between the two points

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Point<ValueTypeT, SizeI>::RealReturnType 
    Point<ValueTypeT, SizeI>::dist(const Point &pnt) const
{
    return osgSqrt(dist2(pnt));
}

//! Returns the distance between the two points, squared

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Point<ValueTypeT, SizeI>::RealReturnType 
    Point<ValueTypeT, SizeI>::dist2(const Point &pnt) 
    const
{
    RealReturnType returnValue = TypeTraits<RealReturnType>::getZeroElement();
    RealReturnType tmp;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        tmp = Self::_values[i] - pnt._values[i];
        
        returnValue += tmp * tmp;
    }

    return returnValue;
}

//! Returns the maximum value of the vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Point<ValueTypeT, SizeI>::RealReturnType 
    Point<ValueTypeT, SizeI>::maxValue(void) const
{
    RealReturnType returnValue = TypeTraits<RealReturnType>::getMin();

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        if(Self::_values[i] > returnValue)
            returnValue = Self::_values[i];
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                                Math                                     */

//! Component wise scalar multiplication

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::operator *=(const ValueType val)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] *= val;
    }
}

//! Component wise scalar division

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::operator /=(const ValueType  val)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] /= val;
    }
}


//! Point substraction, returns a new vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Point<ValueTypeT, SizeI>::VectorType
    Point<ValueTypeT, SizeI>::operator -(const Point &pnt) const
{
    VectorType returnValue(*this);

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] -= pnt[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::operator + (const VectorType &vec) const
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] + vec[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::operator - (const VectorType &vec) const
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] - vec[i];
    }

    return returnValue;
}

//! Component wise binary scalar multiplication

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point <ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::operator * (const ValueType rVal) const
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] * rVal;
    }

    return returnValue;
}

//! Component wise binary scalar division

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point <ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::operator / (const ValueType rVal) const
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] / rVal;
    }

    return returnValue;
}

//! Nondestructive unary negation, returns new point

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    Point<ValueTypeT, SizeI>::operator -(void) const
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue._values[i] = - Self::_values[i];
    }

    return returnValue;
}

//! Component wise vector addition

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::operator +=(const VectorType &vec)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] += vec._values[i];
    }
}

//! Component wise vector substraction

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Point<ValueTypeT, SizeI>::operator -=(const VectorType &vec)
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] -= vec._values[i];
    }
}

/*-------------------------------------------------------------------------*/
/*                          Element Access                                 */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT &Point<ValueTypeT, SizeI>::operator[](const UInt32 uiVal)
{
    return Self::_values[uiVal];
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
const ValueTypeT &
    Point<ValueTypeT, SizeI>::operator[](const UInt32 uiVal) const
{
    return Self::_values[uiVal];
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI> &
    Point<ValueTypeT, SizeI>::operator =(const Point &source)
{
    if(this == &source)
        return *this;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = source._values[i];
    }

    return *this;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI> &
    Point<ValueTypeT, SizeI>::operator =(const VectorType &source)
{
    Point<ValueTypeT, SizeI>::error_cannot_assign_vector;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Point<ValueTypeT, SizeI>::operator < (const Point &other) const
{
    bool ret = false;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        if(Self::_values[i] > other._values[i])
        {
            break;
        }

        if(Self::_values[i] < other._values[i])
        {
            ret = true;
            break;
        }
    }

    return ret;
}

//! Equal operator, using Eps as the tolerance

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Point<ValueTypeT, SizeI>::operator == (const Point &other) const
{
    return Self::equals(other, TypeTraits<ValueTypeT>::getDefaultEps());
}

//! Not equal operator, using Eps as the tolerance

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Point<ValueTypeT, SizeI>::operator != (const Point &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Component wise binary scalar multiplication

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Point<ValueTypeT, SizeI>
    operator *(const ValueTypeT                val,
               const Point<ValueTypeT, SizeI> &pnt )
{
    Point<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Point<ValueTypeT, SizeI>::_uiSize; i++)
    {
        returnValue[i] = pnt[i] * val;
    }

    return returnValue;
}

//! Write point to the given stream
/*
template <class  ValueTypeT,
          UInt32 SizeI      > inline
std::ostream &operator <<(      std::ostream             &os,
                          const Point<ValueTypeT, SizeI> &pnt)
{
    for(UInt32 i = 0; i < Point<ValueTypeT, SizeI>::_uiSize; i++)
    {
        os << pnt[i];

        if(i != Point<ValueTypeT, SizeI>::_uiSize - 1)
            os << ", ";
    }

    return os;
}*/


//! Specializations for char-equivalent types, to prevent writing them
//  as ASCII characters
/*
template <UInt32 SizeI> inline
std::ostream &operator <<(      std::ostream        &os,
                          const Point<UInt8, SizeI> &pnt)
{
    for(UInt32 i = 0; i < Point<UInt8, SizeI>::_uiSize; i++)
    {
        os << static_cast<UInt16>(pnt[i]);

        if(i != Point<UInt8, SizeI>::_uiSize - 1)
            os << ", ";
    }

    return os;
}

template <UInt32 SizeI> inline
std::ostream &operator <<(      std::ostream       &os,
                          const Point<Int8, SizeI> &pnt)
{
    for(UInt32 i = 0; i < Point<Int8, SizeI>::_uiSize; i++)
    {
        os << static_cast<Int16>(pnt[i]);

        if(i != Point<Int8, SizeI>::_uiSize - 1)
            os << ", ";
    }

    return os;
}*/


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \typedef Vector::RealReturnType
    \brief Used type if the returnvalue must be a real value.
 */

/*! \typedef Vector::ValueType
    \brief Value type
 */

/*! \typedef Vector::Inherited
    \brief Parent type
 */

template <class  ValueTypeT,
          UInt32 SizeI      >
const Vector<ValueTypeT, SizeI>  Vector<ValueTypeT, SizeI>::Null;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(void) : 
    Inherited()
{
    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}


/*! \brief Constructor which takes a const value array.
 
    Be shure the array size at least as large as the vector size.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const ValueTypeT *pVals) :
    Inherited(pVals)
{
}

/*! \brief Constructor which takes a const value array.
  
    Be shure the array size at least as large as the vector size.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(ValueTypeT *pVals) : 
    Inherited(pVals)
{
}

template <class  ValueTypeT,
          UInt32 SizeI       >
template <class  ValueType2T, 
          UInt32 Size2I      > inline
Vector<ValueTypeT, SizeI>::Vector(const Point<ValueType2T, Size2I> &pnt) :

    Inherited(pnt)
{
}

template <class  ValueTypeT,
          UInt32 SizeI       >
template <class  ValueType2T, 
          UInt32 Size2I      > inline
Vector<ValueTypeT, SizeI>::Vector(const Vector<ValueType2T, Size2I> &vec) :

    Inherited(vec)
{
}


template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const Vector &source) : 

    Inherited(source)
{
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const ValueType rVal1)
{
    UInt32 i;

    Self::_values[0] = rVal1;

    for(i = 1; i < Self::_uiSize; i++)
    {
        Self::_values[i] = TypeTraits<ValueTypeT>::getZeroElement();
    }
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const ValueType rVal1,
                                  const ValueType rVal2) :

    Inherited(rVal1, rVal2)
{
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const ValueType rVal1,
                                  const ValueType rVal2,
                                  const ValueType rVal3) :

    Inherited(rVal1, rVal2, rVal3)
{
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::Vector(const ValueType rVal1,
                                  const ValueType rVal2,
                                  const ValueType rVal3,
                                  const ValueType rVal4) :

    Inherited(rVal1, rVal2, rVal3, rVal4)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>::~Vector(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          Common Math                                    */

//! square of the Euclidean length of the vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Vector<ValueTypeT, SizeI>::RealReturnType
    Vector<ValueTypeT, SizeI>::squareLength(void) const
{
    RealReturnType rTmpVal = RealReturnType(Self::_values[0] * 
                                            Self::_values[0] );

    for(UInt32 i = 1; i < Self::_uiSize; i++)
    {
        rTmpVal += Self::_values[i] * Self::_values[i];
    }

    return rTmpVal;
}

//! Euclidean length of the vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Vector<ValueTypeT, SizeI>::RealReturnType
    Vector<ValueTypeT, SizeI>::length(void) const
{
    return osgSqrt(Self::squareLength());
}


//! Changes vector to be of unit length

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Vector<ValueTypeT, SizeI>::normalize(void)
{
    ValueTypeT rLength = ValueTypeT(length());

    if(osgAbs(rLength) < TypeTraits<ValueTypeT>::getDefaultEps())
    {
        rLength = TypeTraits<ValueTypeT>::getOneElement();
    }
    else
    {
        rLength = TypeTraits<ValueTypeT>::getOneElement() / rLength;
    }

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        Self::_values[i] *= rLength;
    }
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! \brief Returns the right handed cross-product for a given vector;
    This function is implemented for size 3 vectors only.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::cross(const Vector &vec) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    if(Self::_uiSize >= 3)
    {
        returnValue[0] =
            Self::_values[1] * vec._values[2] - 
            Self::_values[2] * vec._values[1];
        returnValue[1] =
            Self::_values[2] * vec._values[0] - 
            Self::_values[0] * vec._values[2];
        returnValue[2] =
            Self::_values[0] * vec._values[1] - 
            Self::_values[1] * vec._values[0];
    }
    else
    {
        // Must be changed
        fprintf(stderr, "cross only implemented for size 3\n");
    }

    return returnValue;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator % (const Vector &vec) const
{
    return this->cross(vec);
}

/*! \brief Calculates the right handed cross-product with a given vector;
    This function is implemented for size 3 vectors only.
*/

template <class  ValueTypeT,
          UInt32 SizeI      > inline
void Vector<ValueTypeT, SizeI>::crossThis(const Vector &vec)
{
    if(Self::_uiSize >= 3)
    {
        ValueTypeT rTmp[2];

        rTmp[0] = 
            Self::_values[1] * vec._values[2] - 
            Self::_values[2] * vec._values[1];
        rTmp[1] = 
            Self::_values[2] * vec._values[0] - 
            Self::_values[0] * vec._values[2];

        Self::_values[2] =
            Self::_values[0] * vec._values[1] -
            Self::_values[1] * vec._values[0];

        Self::_values[0] = rTmp[0];
        Self::_values[1] = rTmp[1];
    }
    else
    {
        // Must be changed
        fprintf(stderr, "crossThis only available for size 3\n");
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif

//! \brief Return the dot (inner) product for a given vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT Vector<ValueTypeT, SizeI>::dot(const Vector &vec) const
{
    ValueTypeT rTmpVal = Self::_values[0] * vec._values[0];

    for(UInt32 i = 1; i < Self::_uiSize; i++)
    {
        rTmpVal += Self::_values[i] * vec._values[i];
    }

    return rTmpVal;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT Vector<ValueTypeT, SizeI>::operator * (const Vector &vec) const
{
    return this->dot(vec);
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT Vector<ValueTypeT, SizeI>::dot (const PointType &pnt) const
{
    ValueTypeT rTmpVal = Self::_values[0] * pnt[0];

    for(UInt32 i = 1; i < Self::_uiSize; i++)
    {
        rTmpVal += Self::_values[i] * pnt[i];
    }

    return rTmpVal;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
ValueTypeT Vector<ValueTypeT, SizeI>::operator * (const PointType &pnt) const
{
     return this->dot(pnt);
}

//! Returns the angle between this and another vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Vector<ValueTypeT, SizeI>::RealReturnType
     Vector<ValueTypeT, SizeI>::enclosedAngle(const Vector &vec) const
{
    RealReturnType returnValue;

    if(Self::isZero() || vec.isZero())
    {
        returnValue = TypeTraits<RealReturnType>::getZeroElement();
    }
    else
    {
        returnValue  = dot(vec);
        returnValue /= (length() * vec.length());

        if((returnValue - TypeTraits<ValueTypeT>::getDefaultEps()) < -1.)
        {
            returnValue = Pi;
        }
        else if((returnValue + TypeTraits<ValueTypeT>::getDefaultEps()) > 1.)
        {
            returnValue = TypeTraits<RealReturnType>::getZeroElement();
        }
        else
        {
            returnValue = osgACos(returnValue);
        }
    }

    return returnValue;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Vector<ValueTypeT, SizeI>::RealReturnType
    Vector<ValueTypeT, SizeI>::projectTo(const Vector &toVec)
{
    RealReturnType rDot       = this ->dot(toVec);
    RealReturnType rSquareDot = toVec .dot(toVec);

    if(rSquareDot > TypeTraits<ValueTypeT>::getDefaultEps())
    {
        rDot /= rSquareDot;

        if(osgAbs(rDot) > TypeTraits<ValueTypeT>::getDefaultEps())
        {
            *this  = toVec;
            *this *= ValueTypeT(rDot);
        }
        else
        {
            this->setNull();
            rDot = TypeTraits<RealReturnType>::getZeroElement();
        }
    }
    else
    {
        rDot = TypeTraits<RealReturnType>::getOneElement();
    }

    return rDot;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::reflect(const Vector &Normal) const
{
   Vector<ValueTypeT, SizeI> Result;

   const ValueTypeT dot_prod(2.0f * this->dot(Normal));
   Result = *this - dot_prod * Normal;

   return Result;
}

//! Returns the corrosponding point by adding it to zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
const typename Vector<ValueTypeT, SizeI>::PointType &
    Vector<ValueTypeT, SizeI>::addToZero(void) const
{
    return *(static_cast<const PointType *>(this));
}

//! Returns the corrosponding point by adding it to zero

template <class  ValueTypeT,
          UInt32 SizeI      > inline
typename Vector<ValueTypeT, SizeI>::PointType &
    Vector<ValueTypeT, SizeI>::addToZero(void)
{
    return *(static_cast<PointType *>(this));
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI> &
    Vector<ValueTypeT, SizeI>::subZero(void)
{
    return *this;
}

template <class  ValueTypeT,
          UInt32 SizeI      > inline
const Vector<ValueTypeT, SizeI> &
    Vector<ValueTypeT, SizeI>::subZero(void) const
{
    return (*this);
}

/*-------------------------------------------------------------------------*/
/*                                Math                                     */

//! Component wise binary vector subtraction operator

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector <ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator - (const Vector &vec) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] - vec[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector <ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator + (const Vector &vec) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] + vec[i];
    }

    return returnValue;
}


//! Component wise binary scalar division

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector <ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator / (const ValueType rVal) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] / rVal;
    }

    return returnValue;
}

//! Component wise binary scalar multiplication

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector <ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator * (const ValueType rVal) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue[i] = Self::_values[i] * rVal;
    }

    return returnValue;
}

//! Nondestructive unary negation, returns new vector

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>
    Vector<ValueTypeT, SizeI>::operator -(void) const
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        returnValue._values[i] = - Self::_values[i];
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI> &
    Vector<ValueTypeT, SizeI>::operator =(const Vector &source)
{
    if(this == &source)
        return *this;

    *(static_cast<Inherited *>(this)) = 
        static_cast<const Inherited &>(source);

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Vector<ValueTypeT, SizeI>::operator < (const Vector &other) const
{
    bool ret = false;

    for(UInt32 i = 0; i < Self::_uiSize; i++)
    {
        if(Self::_values[i] > other._values[i])
        {
            break;
        }
        if(Self::_values[i] < other._values[i])
        {
            ret = true;
            break;
        }
    }

    return ret;
}

//! Equal operator, using Eps as the tolerance

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Vector<ValueTypeT, SizeI>::operator == (const Vector &other) const
{
    return Self::equals(other, TypeTraits<ValueTypeT>::getDefaultEps());
}

//! Not eual operator, using Eps as the tolerance

template <class  ValueTypeT,
          UInt32 SizeI      > inline
bool Vector<ValueTypeT, SizeI>::operator != (const Vector &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Component wise binary scalar multiplication

template <class  ValueTypeT,
          UInt32 SizeI      > inline
Vector<ValueTypeT, SizeI>
    operator *(const ValueTypeT                 val,
               const Vector<ValueTypeT, SizeI> &vec )
{
    Vector<ValueTypeT, SizeI> returnValue;

    for(UInt32 i = 0; i < Vector<ValueTypeT, SizeI>::_uiSize; i++)
    {
        returnValue[i] = vec[i] * val;
    }

    return returnValue;
}

OSG_END_NAMESPACE
