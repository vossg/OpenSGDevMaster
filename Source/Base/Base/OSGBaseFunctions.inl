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
//   Base Math Functions
//---------------------------------------------------------------------------

/*---------------------------------------------------------------------*/
/*! \name sqrt                                                         */
/*! \{                                                                 */

/*! Return the square root of the argument, i.e. the number \c y that satisfies
    <tt>y<sup>2</sup> == rValue</tt>. The argument must be nonnegative.

    \param[in] rValue The number to compute the square root of, must be >= 0.
    \return The square root of the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgsqrt(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgsqrt(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgsqrt(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sqrt(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return sqrtf(rValue);
#else
    return (Real32) sqrt((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgsqrt(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sqrt(rValue);
#else
    return sqrt(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgsqrt(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sqrt(rValue);
#else
    return sqrtl(rValue);
#endif
}


/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgsqrt(const Fixed32 rValue)
{
    return Fixed32::sqrt(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name cos                                                          */
/*! \{                                                                 */

/*! Return the cosine of the argument, which is given in radians.

    \param[in] rValue The angle in radians to compute the cosine of.
    \return Cosine of \a rValue, it is in the range -1 to 1.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgcos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgcos(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgcos(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::cos(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return cosf(rValue);
#else
    return (Real32) cos((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgcos(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::cos(rValue);
#else
    return cos(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgcos(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::cos(rValue);
#else
    return cosl(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgcos(const Fixed32 rValue)
{
    return Fixed32::cos(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name sin                                                          */
/*! \{                                                                 */

/*! Return the sine of the argument, which is given in radians.

    \param[in] rValue The angle in radians to compute the sine of.
    \return Sine of \a rValue, it is in the range -1 to 1.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgsin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgsin(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgsin(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sin(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return sinf(rValue);
#else
    return (Real32) sin((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgsin(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sin(rValue);
#else
    return sin(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgsin(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sin(rValue);
#else
    return sinl(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgsin(const Fixed32 rValue)
{
    return Fixed32::sin(rValue);
}


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name tan                                                          */
/*! \{                                                                 */

/*! Return the tangent of the argument, which is given in radians. The tangent
    is defined as tan(x) = sin(x) / cos(x) and therefore has singularities at
    odd multiples of pi/2.

    \param[in] rValue The angle in radians to compute the tangent of.
    \return Tangent of \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgtan(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgtan(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::tan(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return tanf(rValue);
#else
    return (Real32) tan((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgtan(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::tan(rValue);
#else
    return tan(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgtan(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::tan(rValue);
#else
    return tanl(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgtan(const Fixed32 rValue)
{
    return Fixed32::tan(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name acos                                                         */
/*! \{                                                                 */

/*! Return the arc cosine (in radians) of the argument, i.e. the number \c y
    such that <tt>rValue == cos(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc cosine of, must be
    in the range [-1; 1].
    \return The arc cosine of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgacos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgacos(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgacos(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return acosf(rValue);
#else
    return (Real32) acos((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgacos(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#else
    return acos(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgacos(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#else
    return acosl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name asin                                                         */
/*! \{                                                                 */

/*! Return the arc sine (in radians) of the argument, i.e. the number \c y such
    that <tt>rValue == sin(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc sine of, must be
    in the range [-1; 1].
    \return The arc sine of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgasin(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgasin(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return asinf(rValue);
#else
    return (Real32) asin((Real32) rValue);
#endif
}


/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgasin(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#else
    return asin(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgasin(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#else
    return asinl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name atan                                                         */
/*! \{                                                                 */

/*! Return the arc tangent (in radians) of the argument, i.e. the number \c y
    such that <tt>rValue == tan(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc tangent of.
    \return The arc tangent of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \sa osgatan2(const FloatTypeT,const FloatTypeT)

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgatan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgatan(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgatan(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return atanf(rValue);
#else
    return (Real32) atan((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgatan(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#else
    return atan(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgatan(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#else
    return atanl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name atan2                                                        */
/*! \{                                                                 */

/*! Return the arc tangent (in radians) of <tt>rValue1 / rValue2</tt> using
    the signs of both arguments to determine the quadrant. This can be used to
    obtain the angle component of the polar coordinates of a point with
    cartesian coordinates (\a rValue2, \a rValue1).

    \param[in] rValue1 The numerator of the value to compute atan of.
    \param[in] rValue2 The denominator of the value to compute atan of.
    \return The arc tangent of <tt>rValue1 / rValue2</tt> in the range [-pi; pi].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgatan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgatan2(RealType(rValue1), RealType(rValue2));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgatan2(const Real32 rValue1, const Real32 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#elif defined(OSG_HAS_FLOATMATH)
#ifndef _OSG_HAS_ATANF2__
    return atan2f(rValue1, rValue2);
#else
    return (Real32) atan2((Real32) rValue1, (Real32) rValue2);
#endif
#else
    return (Real32) atan2((Real32) rValue1, (Real32) rValue2);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgatan2(const Real64 rValue1, const Real64 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#else
    return atan2(rValue1, rValue2);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgatan2(const Real128 rValue1, const Real128 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#else
    return atan2l(rValue1, rValue2);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name abs                                                          */
/*! \{                                                                 */

/*! Return the absolute value of the argument.

    \param[in] rValue Number to compute absolute value of.
    \return Absolute value of \a rValue.

    \note For floating point arguments this function forwards to an
    appropriate C++ or C library function, hence exhibits the 
    respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgabs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgabs(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#elif defined(OSG_HAS_FLOATMATH) && !defined(OSG_NO_FABSF)
    return fabsf(rValue);
#else
    return (Real32) fabs((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgabs(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#else
    return fabs(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgabs(const Fixed32 rValue)
{
    return Fixed32::abs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgabs(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#else
    return fabsl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name pow                                                          */
/*! \{                                                                 */

/*! Return \a rValue to the power of \a rExp.

    \param[in] rValue Base.
    \param[in] rExp Exponent.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rValue,
           const FloatTypeT rExp)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgpow(RealType(rValue), RealType(rExp));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgpow(const Real32 rValue, const Real32 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#elif defined(OSG_HAS_FLOATMATH)
    return powf(rValue, rExp);
#else
    return (Real32) pow((Real32) rValue, (Real32) rExp);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgpow(const Real64 rValue, const Real64 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#else
    return pow(rValue, rExp);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgpow(const Real128 rValue, const Real128 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#else
    return powl(rValue, rExp);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name log                                                          */
/*! \{                                                                 */

/*! Return the natural logarithm of the argument, i.e. the number \c y such that
    <tt>e<sup>y</sup> == rValue</tt>, where e is Euler's number.

    \param[in] rValue The number to compute the natural logarithm of,
    must be >= 0.
    \return Natural logarithm of \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osglog(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osglog(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return logf(rValue);
#else
    return (Real32) log((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osglog(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#else
    return log(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osglog(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#else
    return logl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name exp                                                          */
/*! \{                                                                 */

/*! Return e to the power \a rValue, where e is Euler's number, the base of the
    natural logarithm.

    \param[in] rValue Exponent.
    \return e to the power \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgexp(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgexp(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return expf(rValue);
#else
    return (Real32) exp((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgexp(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#else
    return exp(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgexp(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#else
    return expl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name floor                                                        */
/*! \{                                                                 */

/*! Returns the argument rounded downwards to the nearest integer, i.e. returns
    the largest integer not greater than \a rValue.

    Example:
    \code
    osgfloor( 1.5) ==  1.0;
    osgfloor(-1.5) == -2.0;
    \endcode

    \param[in] rValue Number to round down.
    \return Largest integer not greater than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgfloor(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgfloor(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#elif defined(OSG_HAS_FLOATMATH)
# ifdef OSG_HPUX_ACC
    return (Real32) floor((Real32) rValue);
# else
    return floorf(rValue);
# endif
#else
    return (Real32) floor((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgfloor(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#else
    return floor(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgfloor(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#else
    return floorl(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name ceil                                                         */
/*! \{                                                                 */

/*! Returns the argument rounded upwards to the nearest integer, i.e. returns
    the smallest integer not less than \a rValue.

    Example:
    \code
    osgceil( 1.5) ==  2.0;
    osgceil(-1.5) == -1.0;
    \endcode

    \param[in] rValue Number to round up.
    \return Smallest integer not less than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgceil(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgceil(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgceil(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#elif defined(OSG_HAS_FLOATMATH)
# ifdef OSG_HPUX_ACC
    return (Real32) ceil((Real32) rValue);
# else
    return ceilf(rValue);
# endif
#else
    return (Real32) ceil((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgceil(const Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#else
    return ceil(rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgceil(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#else
    return ceill(rValue);
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name finite                                                       */
/*! \{                                                                 */

/*! Returns a nonzero value if \a rValue is a finite number, i.e. neither
    plus or minus infinity nor NAN.

    \param[in] rValue Number to test.
    \return Nonzero value if argument is finite.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rValue)
{
#ifdef WIN32
    return _finite(rValue);
#else
#ifdef __hpux
    return  isfinite(rValue);
#else
    return  finite(rValue);
#endif
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name min / max                                                    */
/*! \{                                                                 */

/*! Return the smaller of the two arguments.

    \param[in] lVal First value for comparison.
    \param[in] rValue Second value for comparison.
    \return The smaller of the two arguments.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgMin(const TypeT lValue, const TypeT rValue)
{
    return ((lValue < rValue) ? lValue : rValue);
}

/*! Return the larger of the two arguments.

    \param[in] lVal First value for comparison.
    \param[in] rValue Second value for comparison.
    \return The larger of the two arguments.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgMax(const TypeT lValue, const TypeT rValue)
{
    return ((lValue > rValue) ? lValue : rValue);
}

/*! Restrict val to the range [minVal; maxVal], inclusive.

    \param[in] minVal Lower bound of the range.
    \param[in] val Value to clamp.
    \param[in] maxVal Upper bound of the range.
    \return The value from the given range that is closest to val.

    \ingroup GrpBaseBaseMathFn
*/
template <class TypeT> inline
TypeT osgClamp(const TypeT minVal, const TypeT val, const TypeT maxVal)
{
    return ((val > minVal) ? ((val < maxVal) ? val : maxVal) : minVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name sgn                                                          */
/*! \{                                                                 */

/*! Return the sign of the argument, i.e. -1 if val is negative, 1 if it is
    positive and 0 otherwise.

    \param[in] val The number to classify.
    \return The sign of the argument.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
Int8 osgSgn(TypeT val)
{
    if(val < 0)
        return -1;
        
    if(val > 0)
        return  1;
    
    return 0;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name swap                                                         */
/*! \{                                                                 */

/*! Exchanges the values of the arguments.

    \param[in,out] lVal New value for \a rValue, is assigned the 
    old value of \a rValue.
    \param[in,out] rValue New value for lVal, is assigned the
    old value of rVal.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
void osgSwap(TypeT & lValue, TypeT & rValue)
{
    TypeT val(lValue);

    lValue = rValue;
    rValue = val;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name degree2rad                                                   */
/*! \{                                                                 */

/*! Converts the argument angle from degrees to radians.

    \param[in] rValue Angle in degree to convert.
    \return Angle in radians.

    \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgdegree2rad(const Real32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgdegree2rad(const Real64 rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgdegree2rad(const Fixed32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgdegree2rad(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgdegree2rad(RealType(rValue));
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name rad2degree                                                   */
/*! \{                                                                 */

/*! Converts the argument angle from radians to degrees.

    \param[in] rValue Angle in radians to convert.
    \return Angle in degrees.

    \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgrad2degree(const Real32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgrad2degree(const Real64 rValue)
{
    return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgrad2degree(const Fixed32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgrad2degree(RealType(rValue));
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name deg2rad / rad2deg                                            */
/*! \{                                                                 */

/*! Converts the argument angle from degrees to radians.

    \param[in] rValue Angle in degree to convert.
    \return Angle in radians.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rValue)
{
    return osgdegree2rad(rValue);
}

/*! Converts the argument angle from radians to degrees.

    \param[in] rValue Angle in radians to convert.
    \return Angle in degrees.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    rad2deg(const FloatTypeT rValue)
{
    return osgrad2degree(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name ispower2                                                     */
/*! \{                                                                 */

/*! Test if the argument is a power of 2 or zero.

    \param[in] rValue Number to test.
    \return true if rValue is a power of 2 or zero.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
bool osgispower2<UInt32>(UInt32 rValue)
{
    // find the lowest 1 bit
    while(rValue && ! (rValue & 1))
    {
        rValue >>= 1;
    }

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if(rValue)
        return false;
    else            
        return true;
}

/*! Test if the argument is a power of 2 or zero.

    \param[in] rValue Number to test, must be >= 0.
    \return true if rValue is a power of 2 or zero.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
bool osgispower2<Int32>(Int32 rValue)
{
    // find the lowest 1 bit
    while(rValue && ! (rValue & 1))
    {
        rValue >>= 1;
    }

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if(rValue)
        return false;
    else
        return true;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name nextpower2                                                   */
/*! \{                                                                 */

/*! Return the next larger power of 2, i.e. the smallest power of 2 not less
    than \a rValue.

    \param[in] rValue The lower bound for the wanted power of 2.
    \return A power of 2 to not less than \a rValue.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt32 osgnextpower2<UInt32>(UInt32 rValue)
{
    UInt32 result  = 1;
    UInt32 oresult = 0;

    while(result < rValue && result > oresult)
    {
        oresult = result;
        result <<= 1;
    }

    return (result > oresult) ? result : 0;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int32 osgnextpower2<Int32>(Int32 rValue)
{
    Int32 result  = 1;
    Int32 oresult = 0;

    while(result < rValue && result > oresult)
    {
        oresult = result;
        result <<= 1;
    }

    return (result > oresult) ? result : 0;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int64 osgnextpower2<Int64>(Int64 rValue)
{
    Int64 result  = 1;
    Int64 oresult = 0;

    while(result < rValue && result > oresult)
    {
        oresult = result;
        result <<= 1;
    }

    return (result > oresult) ? result : 0;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt64 osgnextpower2<UInt64>(UInt64 rValue)
{
    UInt64 result  = 1;
    UInt64 oresult = 0;

    while(result < rValue && result > oresult)
    {
        oresult = result;
        result <<= 1;
    }

    return (result > oresult)? result : 0;
}

#ifdef SIZE_T_NEQ_UINT32

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
size_t osgnextpower2<size_t>(size_t rValue)
{
    size_t result  = 1;
    size_t oresult = 0;

    while(result < rValue && result > oresult)
    {
        oresult = result;
        result <<= 1;
    }

    return (result > oresult)? result : 0;
}

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name Misc                                                         */
/*! \{                                                                 */

/*! Returns the index of the element that has the largest absolute value in
    a Vec3 or Pnt3.

    \param[in] v Input Vec3 or Pnt3.
    \return Index of the element with largest absolute value.

    \ingroup GrpBaseBaseMiscFn
 */
template<class VecPntT> inline
UInt32 getMaxIndexAbs3(const VecPntT &v)
{
    return 
        osgabs(v[0]) > osgabs(v[1]) ?
            (osgabs(v[0]) > osgabs(v[2]) ? 0 : 2) : 
            (osgabs(v[1]) > osgabs(v[2]) ? 1 : 2);
}

#ifndef OSG_WINCE
/*! Sets or removes an environment variable. If the \a string is of the form
    <tt>name=value</tt> the env. variable \c name is set to \c value. Otherwise
    the contents of \a string a interpreted as the name of an env. variable and
    any definition of this variable is removed from the environment.

    \param[in] string String to put into the environment.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \warning The exact \a string is put into the environment, any changes to
    it will be directly reflected there. The lifetime of \a string must only end
    when the program terminates.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Int32 putenv(Char8 *string)
{
#if !defined(WIN32) || defined(BCC)
    return ::putenv(string);
#else
    return ::_putenv(string);
#endif
}
#else
inline
Char8 *getenv(Char8 *string)
{
    return NULL;
}
#endif

/*! Pause program execution for the given number of milliseconds.

    \param[in] millisecs Duration of the pause.

    \ingroup GrpBaseBaseMiscFn
 */
inline
void osgsleep(UInt32 millisecs)
{
#ifdef WIN32
    Sleep(millisecs);
#else

#if 0 // replaced by nanosleep to work around IRIX problems
    // Rough aproximation, have to find a better way soon (GV)

    if( (millisecs * 1000) > 1000000)
    {
        ::sleep(millisecs / 1000);
    }
    else
    {
        ::usleep(millisecs * 1000);
    }
    
#else

    struct timespec req;
    int ns;
    
    req.tv_sec  = static_cast<long> (millisecs / 1000);
    req.tv_nsec = static_cast<long>((millisecs % 1000) * 1000);
    
    while((req.tv_sec > 0 || req.tv_nsec > 0) &&
          (ns = nanosleep(&req, &req)) < 0)
    {
        if(ns < 0 && errno != EINTR)
        {
            break;
        }
    }
        
#endif
#endif
}

/*! Returns a uniformly distributed random Real32 between 0 and 1 inclusive.

    \return A random Real32 number between 0 and 1 inclusive.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgrand(void)
{
    return rand() / (Real32) RAND_MAX;
}

#if defined(WIN32) && defined(_MSC_VER) 
#if _MSC_VER <= 1200  // VC6
/*! Write a UInt64 value to the given stream.

    \param[in] os Output stream to write to.
    \param[in] v Value to write.
    \return The given output stream.

    \ingroup GrpBaseBaseMiscFn
 */
inline
std::ostream &operator<<(std::ostream &os, UInt64 v)
{
    char buf[30];
    sprintf(buf, "%I64u", v);
    return os << buf;
}

/*! Write a Int64 value to the given stream.

    \param[in] os Output stream to write to.
    \param[in] v Value to write.
    \return The given output stream.

    \ingroup GrpBaseBaseMiscFn
 */
inline
std::ostream &operator<<(std::ostream &os, Int64 v)
{
    char buf[30];
    sprintf(buf, "%I64d", v);
    return os << buf;
}
#endif
#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name Byte Order                                                   */
/*! \{                                                                 */

/*! Returns \c true if the system architecture is big endian.

    \return \c true on big endian architectures, \c false otherwise.

    \ingroup GrpBaseBaseMiscFn
 */
inline
bool osgIsBigEndian(void)
{
    return (BYTE_ORDER) == (BIG_ENDIAN);
}

#if BYTE_ORDER == LITTLE_ENDIAN

// host to network

/*! Convert a UInt16 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osghtons(UInt16 src)
{
    return (src >> 8) | (src << 8);
}

/*! Convert a UInt32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osghtonl(UInt32 src)
{
    return ((src&0x000000ff) << 24) |
           ((src&0x0000ff00) << 8 ) |
           ((src&0x00ff0000) >> 8 ) |
           ((src&0xff000000) >> 24);
}

/*! Convert a UInt64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osghtonll(UInt64 src)
{
#ifdef OSG_LONGLONG_HAS_LL
    return ((src&0x00000000000000ffLL) << 56) |
           ((src&0x000000000000ff00LL) << 40) |
           ((src&0x0000000000ff0000LL) << 24) |
           ((src&0x00000000ff000000LL) << 8 ) |
           ((src&0x000000ff00000000LL) >> 8 ) |
           ((src&0x0000ff0000000000LL) >> 24) |
           ((src&0x00ff000000000000LL) >> 40) |
           ((src&0xff00000000000000LL) >> 56);
#else
    return ((src&0x00000000000000ff) << 56) |
           ((src&0x000000000000ff00) << 40) |
           ((src&0x0000000000ff0000) << 24) |
           ((src&0x00000000ff000000) << 8 ) |
           ((src&0x000000ff00000000) >> 8 ) |
           ((src&0x0000ff0000000000) >> 24) |
           ((src&0x00ff000000000000) >> 40) |
           ((src&0xff00000000000000) >> 56);
#endif
}

/*! Convert a Real32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osghtonf(Real32 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[3]);
    std::swap(p[1], p[2]);

    return src;
}

/*! Convert a Real64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osghtond(Real64 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[7]);
    std::swap(p[1], p[6]);
    std::swap(p[2], p[5]);
    std::swap(p[3], p[4]);

    return src;
}

/*! Convert a Real128 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osghtondd(Real128 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[13]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
}

// network to host

/*! Convert a UInt16 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osgntohs(UInt16 src)
{
    return (src >> 8) | (src << 8);
}

/*! Convert a UInt32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osgntohl(UInt32 src)
{
    return ((src&0x000000ff) << 24) |
           ((src&0x0000ff00) << 8 ) |
           ((src&0x00ff0000) >> 8 ) |
           ((src&0xff000000) >> 24);
}

/*! Convert a UInt64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osgntohll(UInt64 src)
{
#ifdef OSG_LONGLONG_HAS_LL
    return ((src&0x00000000000000ffLL) << 56) |
           ((src&0x000000000000ff00LL) << 40) |
           ((src&0x0000000000ff0000LL) << 24) |
           ((src&0x00000000ff000000LL) << 8 ) |
           ((src&0x000000ff00000000LL) >> 8 ) |
           ((src&0x0000ff0000000000LL) >> 24) |
           ((src&0x00ff000000000000LL) >> 40) |
           ((src&0xff00000000000000LL) >> 56);
#else
    return ((src&0x00000000000000ff) << 56) |
           ((src&0x000000000000ff00) << 40) |
           ((src&0x0000000000ff0000) << 24) |
           ((src&0x00000000ff000000) << 8 ) |
           ((src&0x000000ff00000000) >> 8 ) |
           ((src&0x0000ff0000000000) >> 24) |
           ((src&0x00ff000000000000) >> 40) |
           ((src&0xff00000000000000) >> 56);
#endif
}

/*! Convert a Real32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgntohf(Real32 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[3]);
    std::swap(p[1], p[2]);

    return src;
}

/*! Convert a Real64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osgntohd(Real64 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[7]);
    std::swap(p[1], p[6]);
    std::swap(p[2], p[5]);
    std::swap(p[3], p[4]);

    return src;
}

/*! Convert a Real128 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osgntohdd(Real128 src)
{
    UInt8 *p = (UInt8 *) &src;

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[13]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
}

#else

// host to network
// perhaps we should use macros here ...

/*! Convert a UInt16 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osghtons(UInt16 src)
{
    return src;
}

/*! Convert a UInt32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osghtonl(UInt32 src)
{
    return src;
}

/*! Convert a UInt64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osghtonll(UInt64 src)
{
    return src;
}

/*! Convert a Real32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osghtonf(Real32 src)
{
    return src;
}

/*! Convert a Real64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osghtond(Real64 src)
{
    return src;
}

/*! Convert a Real128 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osghtondd(Real128 src)
{
    return src;
}

// network to host

/*! Convert a UInt16 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osgntohs(UInt16 src)
{
    return src;
}

/*! Convert a UInt32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osgntohl(UInt32 src)
{
    return src;
}

/*! Convert a UInt64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osgntohll(UInt64 src)
{
    return src;
}

/*! Convert a Real32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgntohf(Real32 src)
{
    return src;
}

/*! Convert a Real64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osgntohd(Real64 src)
{
    return src;
}

/*! Convert a Real128 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osgntohdd(Real128 src)
{
    return src;
}

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name C strings                                                    */
/*! \{                                                                 */

/*! Creates a copy of the C string \a szInput and stores a pointer to the copy
    in \a szOutput. The memory for the copy is allocated using \c new[], while
    any memory already pointed to by \a szOutput is deallocated
    with \c delete[].

    \param[in] szInput The C string to copy.
    \param[out] szOutput Set to point to the copy.

    \ingroup GrpBaseBaseStringFn
 */
inline
void stringDup(const TChar *szInput, TChar *&szOutput)
{
    delete [] szOutput;

    szOutput = NULL;

    if(szInput != NULL)
    {
#if defined(_UNICODE) 
        szOutput = new TChar[::wcslen(szInput) + 1];
        ::wcscpy(szOutput, szInput);
#else
        szOutput = new TChar[::strlen(szInput) + 1];
        ::strcpy(szOutput, szInput);
#endif
    }
}

/*! Creates a copy of the C string \a szInput at the position pointed to by
    \a szOutput. This function does not allocate memory, so \a szOutput must
    point to a buffer that is large enough.

    \param[in] szInput The C string to copy.
    \param[out] szOutput Pointer to a buffer where the copy is stored.

    \warning This function does not check the size of the destination buffer,
    hence it could overwrite other data if the buffer is not large enough !

    \ingroup GrpBaseBaseStringFn
 */
inline
void  stringcpy(const Char8 *szInput, Char8 *szOutput)
{
    if(szInput != NULL && szOutput != NULL)
    {
        ::strcpy(szOutput, szInput);
    }
}

/*! Compares two C strings, but considers at most the first \a count characters.
    The return value has the same sign as the difference of the first differing
    pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \param[in] count Maximal number of charaters to compare
    \return 0 if the first \a count characters of both strings are equal,
    -1 if \a string1 is less than \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringncmp(const Char8 *string1, const Char8 *string2, size_t count)
{
    return ::strncmp(string1, string2, count);
}

/*! Returns the length of a C string, i.e. the number of characters from the
    given pointer, to the first zero character.

    \param[in] string1 String whose length is determined.
    \return Length of the string.

    \ingroup GrpBaseBaseStringFn 
 */
inline
Int32 stringlen(const Char8 *string1)
{
    return ::strlen(string1);
}

/*! Compares two C strings. The return value has the same sign as the
    difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringcmp(const Char8 *string1, const Char8 *string2)
{
    return ::strcmp(string1, string2);
}

/*! Compare two C strings ignoring differences in case. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringcasecmp(const Char8 *string1,
                    const Char8 *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp  (string1, string2);
#endif
}


// Indirector

template <class ContentT, class IndexT>
indirector<ContentT, IndexT>::indirector(ContentT cont) : _cont(cont)
{
}
        
template <class ContentT, class IndexT>
bool indirector<ContentT, IndexT>::operator()(IndexT a, IndexT b)
{
    if(_cont[a] < _cont[b])
        return true;

    return false;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name Reference Count                                              */
/*! \{                                                                 */

/*! Assigns \a pNewObject to \a pObject and adjusts the ref counts, i.e.
    the ref count of \a pObject is decreased and the ref count of \a pNewObject
    is increased. Both arguments must point to a ref counted object or be NULL.

    \param[in,out] pObject Pointer that is assigned to, may be NULL.
    \param[in]     pNewObject Pointer that is assigned, may be NULL.

    \ingroup GrpBaseBaseRefCountFn
 */
template <class T> inline
void setRefP(T *&pObject, T *&pNewObject)
{
    if(pNewObject != NULL)
        pNewObject->addRef();

    if(pObject != NULL)
        pObject->subRef();

    pObject = pNewObject;
}

/*! Increase the ref count of the object pointed to by \a pObject.

    \param[in] pObject Pointer to a ref counted object or NULL.

    \ingroup GrpBaseBaseRefCountFn
 */
template <class T> inline
void addRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

/*! Decrease the ref count of the object pointed to by \a pObject.

    \param[in] pObject Pointer to a ref counted object or NULL.

    \ingroup GrpBaseBaseRefCountFn
 */
template <class T> inline
void subRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}

/*! Clear the pointer \a pObject, i.e. decrease the ref count of the pointee and
    assign NULL to the pointer. The argument must point to a ref counted
    object or be NULL.

    \param[in,out] pObject Pointer to a ref counted object or NULL.

    \ingroup GrpBaseBaseRefCountFn
 */
template <class T> inline
void clearRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();

    pObject = NULL;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#define OSGBASEFUNCTIONS_INLINE_CVSID "@(#)$Id$"
