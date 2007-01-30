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
    osgSqrt(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSqrt(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgSqrt(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sqrt(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return sqrtf(rValue);
#else
    return static_cast<Real32>(sqrt(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgSqrt(const Real64 rValue)
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
Real128 osgSqrt(const Real128 rValue)
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
Fixed32 osgSqrt(const Fixed32 rValue)
{
    return Fixed32::sqrt(rValue);
}

#ifdef OSG_1_COMPAT
/*! Return the square root of the argument, i.e. the number \c y that satisfies
    <tt>y<sup>2</sup> == rValue</tt>. The argument must be nonnegative.

    \param[in] rValue The number to compute the square root of, must be >= 0.
    \return The square root of the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgSqrt instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgsqrt(const FloatTypeT rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgsqrt(const Real32 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgsqrt(const Real64 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgsqrt(const Real128 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgsqrt(const Fixed32 rValue)
{
    return OSG::osgSqrt(rValue);
}
#endif  // OSG_1_COMPAT

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
    osgCos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgCos(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgCos(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::cos(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return cosf(rValue);
#else
    return static_cast<Real32>(cos(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgCos(const Real64 rValue)
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
Real128 osgCos(const Real128 rValue)
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
Fixed32 osgCos(const Fixed32 rValue)
{
    return Fixed32::cos(rValue);
}

#ifdef OSG_1_COMPAT
/*! Return the cosine of the argument, which is given in radians.

    \param[in] rValue The angle in radians to compute the cosine of.
    \return Cosine of \a rValue, it is in the range -1 to 1.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgCos instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgcos(const FloatTypeT rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgcos(const Real32 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgcos(const Real64 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgcos(const Real128 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgcos(const Fixed32 rValue)
{
    return OSG::osgCos(rValue);
}
#endif // OSG_1_COMPAT

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
    osgSin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSin(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgSin(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::sin(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return sinf(rValue);
#else
    return static_cast<Real32>(sin(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgSin(const Real64 rValue)
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
Real128 osgSin(const Real128 rValue)
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
Fixed32 osgSin(const Fixed32 rValue)
{
    return Fixed32::sin(rValue);
}

#ifdef OSG_1_COMPAT
/*! Return the sine of the argument, which is given in radians.

    \param[in] rValue The angle in radians to compute the sine of.
    \return Sine of \a rValue, it is in the range -1 to 1.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgSin instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgsin(const FloatTypeT rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgsin(const Real32 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgsin(const Real64 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgsin(const Real128 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgsin(const Fixed32 rValue)
{
    return OSG::osgSin(rValue);
}
#endif // OSG_1_COMPAT

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
    osgTan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgTan(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgTan(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::tan(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return tanf(rValue);
#else
    return static_cast<Real32>(tan(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgTan(const Real64 rValue)
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
Real128 osgTan(const Real128 rValue)
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
Fixed32 osgTan(const Fixed32 rValue)
{
    return Fixed32::tan(rValue);
}

#ifdef OSG_1_COMPAT
/*! Return the tangent of the argument, which is given in radians. The tangent
    is defined as tan(x) = sin(x) / cos(x) and therefore has singularities at
    odd multiples of pi/2.

    \param[in] rValue The angle in radians to compute the tangent of.
    \return Tangent of \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgTan instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgtan(const FloatTypeT rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgtan(const Real32 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgtan(const Real64 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgtan(const Real128 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgtan(const Fixed32 rValue)
{
    return OSG::osgTan(rValue);
}
#endif // OSG_1_COMPAT

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
    osgACos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgACos(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgACos(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return acosf(rValue);
#else
    return static_cast<Real32>(acos(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgACos(const Real64 rValue)
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
Real128 osgACos(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#else
    return acosl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the arc cosine (in radians) of the argument, i.e. the number \c y
    such that <tt>rValue == cos(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc cosine of, must be
    in the range [-1; 1].
    \return The arc cosine of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgACos instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgacos(const FloatTypeT rValue)
{
    return OSG::osgACos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgacos(const Real32 rValue)
{
    return OSG::osgACos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgacos(const Real64 rValue)
{
    return OSG::osgACos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgacos(const Real128 rValue)
{
    return OSG::osgACos(rValue);
}
#endif // OSG_1_COMPAT

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
    osgASin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgASin(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgASin(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return asinf(rValue);
#else
    return static_cast<Real32>(asin(static_cast<Real32>(rValue)));
#endif
}


/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgASin(const Real64 rValue)
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
Real128 osgASin(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#else
    return asinl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the arc sine (in radians) of the argument, i.e. the number \c y such
    that <tt>rValue == sin(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc sine of, must be
    in the range [-1; 1].
    \return The arc sine of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgASin instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgasin(const FloatTypeT rValue)
{
    return OSG::osgASin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgasin(const Real32 rValue)
{
    return OSG::osgASin(rValue);
}


/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgasin(const Real64 rValue)
{
    return OSG::osgASin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgasin(const Real128 rValue)
{
    return OSG::osgASin(rValue);
}
#endif // OSG_1_COMPAT

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

    \sa osgATan2(const FloatTypeT,const FloatTypeT)

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgATan(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return atanf(rValue);
#else
    return static_cast<Real32>(atan(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgATan(const Real64 rValue)
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
Real128 osgATan(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#else
    return atanl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the arc tangent (in radians) of the argument, i.e. the number \c y
    such that <tt>rValue == tan(y)</tt> and \c y is in the range [-pi/2; pi/2].

    \param[in] rValue The number to compute the arc tangent of.
    \return The arc tangent of \a rValue in the range [-pi/2; pi/2].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \sa osgATan2(const FloatTypeT,const FloatTypeT)

    \deprecated use osgATan instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgatan(const FloatTypeT rValue)
{
    return OSG::osgATan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgatan(const Real32 rValue)
{
    return OSG::osgATan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgatan(const Real64 rValue)
{
    return OSG::osgATan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgatan(const Real128 rValue)
{
    return OSG::osgATan(rValue);
}
#endif // OSG_1_COMPAT

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
    osgATan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan2(RealType(rValue1), RealType(rValue2));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgATan2(const Real32 rValue1, const Real32 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#elif defined(OSG_HAS_FLOATMATH)
#ifndef _OSG_HAS_ATANF2__
    return atan2f(rValue1, rValue2);
#else
    return static_cast<Real32>(atan2(static_cast<Real32>(rValue1),
                                     static_cast<Real32>(rValue2) ));
#endif
#else
    return static_cast<Real32>(atan2(static_cast<Real32>(rValue1),
                                     static_cast<Real32>(rValue2) ));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgATan2(const Real64 rValue1, const Real64 rValue2)
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
Real128 osgATan2(const Real128 rValue1, const Real128 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#else
    return atan2l(rValue1, rValue2);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the arc tangent (in radians) of <tt>rValue1 / rValue2</tt> using
    the signs of both arguments to determine the quadrant. This can be used to
    obtain the angle component of the polar coordinates of a point with
    cartesian coordinates (\a rValue2, \a rValue1).

    \param[in] rValue1 The numerator of the value to compute atan of.
    \param[in] rValue2 The denominator of the value to compute atan of.
    \return The arc tangent of <tt>rValue1 / rValue2</tt> in the range [-pi; pi].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgATan2 instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgatan2(const FloatTypeT rValue1,
         const FloatTypeT rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgatan2(const Real32 rValue1, const Real32 rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgatan2(const Real64 rValue1, const Real64 rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgatan2(const Real128 rValue1, const Real128 rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}
#endif // OSG_1_COMPAT

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
TypeT osgAbs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgAbs(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#elif defined(OSG_HAS_FLOATMATH) && !defined(OSG_NO_FABSF)
    return fabsf(rValue);
#else
    return static_cast<Real32>(fabs(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgAbs(const Real64 rValue)
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
Fixed32 osgAbs(const Fixed32 rValue)
{
    return Fixed32::abs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgAbs(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#else
    return fabsl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the absolute value of the argument.

    \param[in] rValue Number to compute absolute value of.
    \return Absolute value of \a rValue.

    \note For floating point arguments this function forwards to an
    appropriate C++ or C library function, hence exhibits the
    respective error behavior.

    \deprecated use osgAbs instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgabs(const TypeT rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgabs(const Real32 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgabs(const Real64 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgabs(const Fixed32 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgabs(const Real128 rValue)
{
    return OSG::osgAbs(rValue);
}
#endif // OSG_1_COMPAT

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
    osgPow(const FloatTypeT rValue,
           const FloatTypeT rExp)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgPow(RealType(rValue), RealType(rExp));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgPow(const Real32 rValue, const Real32 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#elif defined(OSG_HAS_FLOATMATH)
    return powf(rValue, rExp);
#else
    return static_cast<Real32>(pow(static_cast<Real32>(rValue),
                                   static_cast<Real32>(rExp)   ));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgPow(const Real64 rValue, const Real64 rExp)
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
Real128 osgPow(const Real128 rValue, const Real128 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#else
    return powl(rValue, rExp);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return \a rValue to the power of \a rExp.

    \param[in] rValue Base.
    \param[in] rExp Exponent.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgPow instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgpow(const FloatTypeT rValue,
       const FloatTypeT rExp)
{
    return OSG::osgPow(rValue, rExp);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgpow(const Real32 rValue, const Real32 rExp)
{
    return OSG::osgPow(rValue, rExp);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgpow(const Real64 rValue, const Real64 rExp)
{
    return OSG::osgPow(rValue, rExp);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgpow(const Real128 rValue, const Real128 rExp)
{
    return OSG::osgPow(rValue, rExp);
}
#endif // OSG_1_COMPAT

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
    osgLog(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgLog(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgLog(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return logf(rValue);
#else
    return static_cast<Real32>(log(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgLog(const Real64 rValue)
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
Real128 osgLog(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#else
    return logl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return the natural logarithm of the argument, i.e. the number \c y such that
    <tt>e<sup>y</sup> == rValue</tt>, where e is Euler's number.

    \param[in] rValue The number to compute the natural logarithm of,
    must be >= 0.
    \return Natural logarithm of \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgLog instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osglog(const FloatTypeT rValue)
{
    return OSG::osgLog(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osglog(const Real32 rValue)
{
    return OSG::osgLog(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osglog(const Real64 rValue)
{
    return OSG::osgLog(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osglog(const Real128 rValue)
{
    return OSG::osgLog(rValue);
}
#endif // OSG_1_COMPAT

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
    osgExp(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgExp(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgExp(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#elif defined(OSG_HAS_FLOATMATH)
    return expf(rValue);
#else
    return static_cast<Real32>(exp(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgExp(const Real64 rValue)
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
Real128 osgExp(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#else
    return expl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Return e to the power \a rValue, where e is Euler's number, the base of the
    natural logarithm.

    \param[in] rValue Exponent.
    \return e to the power \a rValue.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgExp instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgexp(const FloatTypeT rValue)
{
    return OSG::osgExp(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgexp(const Real32 rValue)
{
    return OSG::osgExp(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgexp(const Real64 rValue)
{
    return OSG::osgExp(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgexp(const Real128 rValue)
{
    return OSG::osgExp(rValue);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name floor                                                        */
/*! \{                                                                 */

/*! Returns the argument rounded downwards to the nearest integer, i.e. returns
    the largest integer not greater than \a rValue.

    Example:
    \code
    osgFloor( 1.5) ==  1.0;
    osgFloor(-1.5) == -2.0;
    \endcode

    \param[in] rValue Number to round down.
    \return Largest integer not greater than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgFloor(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgFloor(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgFloor(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#elif defined(OSG_HAS_FLOATMATH)
# ifdef OSG_HPUX_ACC
    return static_cast<Real32>(floor(static_cast<Real32>(rValue)));
# else
    return floorf(rValue);
# endif
#else
    return static_cast<Real32>(floor(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgFloor(const Real64 rValue)
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
Real128 osgFloor(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#else
    return floorl(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Returns the argument rounded downwards to the nearest integer, i.e. returns
    the largest integer not greater than \a rValue.

    Example:
    \code
    osgFloor( 1.5) ==  1.0;
    osgFloor(-1.5) == -2.0;
    \endcode

    \param[in] rValue Number to round down.
    \return Largest integer not greater than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgFloor instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgfloor(const FloatTypeT rValue)
{
    return OSG::osgFloor(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgfloor(const Real32 rValue)
{
    return OSG::osgFloor(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgfloor(const Real64 rValue)
{
    return OSG::osgFloor(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgfloor(const Real128 rValue)
{
    return OSG::osgFloor(rValue);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name ceil                                                         */
/*! \{                                                                 */

/*! Returns the argument rounded upwards to the nearest integer, i.e. returns
    the smallest integer not less than \a rValue.

    Example:
    \code
    osgCeil( 1.5) ==  2.0;
    osgCeil(-1.5) == -1.0;
    \endcode

    \param[in] rValue Number to round up.
    \return Smallest integer not less than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCeil(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgCeil(RealType(rValue));
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgCeil(const Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#elif defined(OSG_HAS_FLOATMATH)
# ifdef OSG_HPUX_ACC
    return static_cast<Real32>(ceil(static_cast<Real32>(rValue)));
# else
    return ceilf(rValue);
# endif
#else
    return static_cast<Real32>(ceil(static_cast<Real32>(rValue)));
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgCeil(const Real64 rValue)
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
Real128 osgCeil(const Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#else
    return ceill(rValue);
#endif
}

#ifdef OSG_1_COMPAT
/*! Returns the argument rounded upwards to the nearest integer, i.e. returns
    the smallest integer not less than \a rValue.

    Example:
    \code
    osgCeil( 1.5) ==  2.0;
    osgCeil(-1.5) == -1.0;
    \endcode

    \param[in] rValue Number to round up.
    \return Smallest integer not less than the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgCeil instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgceil(const FloatTypeT rValue)
{
    return OSG::osgCeil(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgceil(const Real32 rValue)
{
    return OSG::osgCeil(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgceil(const Real64 rValue)
{
    return OSG::osgCeil(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real128 osgceil(const Real128 rValue)
{
    return OSG::osgCeil(rValue);
}
#endif // OSG_1_COMPAT

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
UInt32 osgFinite(const FloatTypeT rValue)
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

#ifdef OSG_1_COMPAT
/*! Returns a nonzero value if \a rValue is a finite number, i.e. neither
    plus or minus infinity nor NAN.

    \param[in] rValue Number to test.
    \return Nonzero value if argument is finite.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.

    \deprecated use osgFinite instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rValue)
{
    return OSG::osgFinite(rValue);
}
#endif // OSG_1_COMPAT

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

    \note It is usually better to use std::swap instead, as it often has
    special handling for standard library types.

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
Real32 osgDegree2Rad(const Real32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgDegree2Rad(const Real64 rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgDegree2Rad(const Fixed32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgDegree2Rad(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgDegree2Rad(RealType(rValue));
}

#ifdef OSG_1_COMPAT
/*! Converts the argument angle from degrees to radians.

    \param[in] rValue Angle in degree to convert.
    \return Angle in radians.

    \deprecated use osgDegree2Rad instead.

    \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgdegree2rad(const Real32 rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgdegree2rad(const Real64 rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgdegree2rad(const Fixed32 rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgdegree2rad(const FloatTypeT rValue)
{
    return OSG::osgDegree2Rad(rValue);
}
#endif // OSG_1_COMPAT


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
Real32 osgRad2Degree(const Real32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgRad2Degree(const Real64 rValue)
{
    return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgRad2Degree(const Fixed32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgRad2Degree(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgRad2Degree(RealType(rValue));
}

#ifdef OSG_1_COMPAT
/*! Converts the argument angle from radians to degrees.

    \param[in] rValue Angle in radians to convert.
    \return Angle in degrees.

    \deprecated use osgRad2Degree instead.

    \ingroup GrpBaseBaseMathFn
 */
inline
Real32 osgrad2degree(const Real32 rValue)
{
    return OSG::osgRad2Degree(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Real64 osgrad2degree(const Real64 rValue)
{
    return OSG::osgRad2Degree(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
Fixed32 osgrad2degree(const Fixed32 rValue)
{
    return OSG::osgRad2Degree(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
osgrad2degree(const FloatTypeT rValue)
{
    return OSG::osgRad2Degree(rValue);
}
#endif // OSG_1_COMPAT

#ifdef OSG_1_COMPAT
/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name deg2rad / rad2deg                                            */
/*! \{                                                                 */

/*! Converts the argument angle from degrees to radians.

    \param[in] rValue Angle in degree to convert.
    \return Angle in radians.

    \deprecated use osgDegree2Rad instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! Converts the argument angle from radians to degrees.

    \param[in] rValue Angle in radians to convert.
    \return Angle in degrees.

    \deprecated use osgRad2Degree instead.

    \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    rad2deg(const FloatTypeT rValue)
{
    return OSG::osgRad2Degree(rValue);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name ispower2                                                     */
/*! \{                                                                 */

/*! Test if the argument is a power of 2 or zero.

    \param[in] rValue Number to test.
    \return true if rValue is a power of 2 or zero, false otherwise.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
bool osgIsPower2<UInt32>(const UInt32 rValue)
{
    return !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<Int32>(const Int32 rValue)
{
    return (rValue >= 0) && !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<UInt64>(const UInt64 rValue)
{
    return !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<Int64>(const Int64 rValue)
{
    return (rValue >= 0) && !(rValue & (rValue - 1));
}

#ifdef OSG_1_COMPAT
/*! Test if the argument is a power of 2 or zero.

    \param[in] rValue Number to test.
    \return true if rValue is a power of 2 or zero, false otherwise.

    \deprecated use osgIsPower2 instead.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
bool osgispower2<UInt32>(const UInt32 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<Int32>(const Int32 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<UInt64>(const UInt64 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<Int64>(const Int64 rValue)
{
    return OSG::osgIsPower2(rValue);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name nextpower2                                                   */
/*! \{                                                                 */

/*! Return the next larger power of 2, i.e. the smallest power of 2 not less
    than \a rValue.

    \param[in] rValue The lower bound for the wanted power of 2.
    \return A power of 2 not less than \a rValue or 0 if there is no such value
    within \a rValue type's range.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt32 osgNextPower2<UInt32>(UInt32 rValue)
{
    if(rValue == 0)
        return TypeTraits<UInt32>::getOneElement();

    --rValue;
    rValue |= rValue >> 1;
    rValue |= rValue >> 2;
    rValue |= rValue >> 4;
    rValue |= rValue >> 8;
    rValue |= rValue >> 16;
    ++rValue;

    return rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int32 osgNextPower2<Int32>(Int32 rValue)
{
    const Int32 maxPower2 = TypeTraits<Int32>::getOneElement() << 30;

    if(rValue <= 0)
        return TypeTraits<Int32>::getOneElement();

    // signed overflow invokes undefined behavior, avoid it.
    if(rValue > maxPower2)
        return TypeTraits<Int32>::getZeroElement();

    --rValue;
    rValue |= rValue >> 1;
    rValue |= rValue >> 2;
    rValue |= rValue >> 4;
    rValue |= rValue >> 8;
    rValue |= rValue >> 16;
    ++rValue;

    return rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt64 osgNextPower2<UInt64>(UInt64 rValue)
{
    if(rValue == 0)
        return TypeTraits<UInt64>::getOneElement();

    --rValue;
    rValue |= rValue >> 1;
    rValue |= rValue >> 2;
    rValue |= rValue >> 4;
    rValue |= rValue >> 8;
    rValue |= rValue >> 16;
    rValue |= rValue >> 32;
    ++rValue;

    return rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int64 osgNextPower2<Int64>(Int64 rValue)
{
    const Int64 maxPower2 = TypeTraits<Int64>::getOneElement() << 62;

    if(rValue <= 0)
        return TypeTraits<Int64>::getOneElement();

    // signed overflow invokes undefined behavior, avoid it.
    if(rValue > maxPower2)
        return TypeTraits<Int64>::getZeroElement();

    --rValue;
    rValue |= rValue >> 1;
    rValue |= rValue >> 2;
    rValue |= rValue >> 4;
    rValue |= rValue >> 8;
    rValue |= rValue >> 16;
    rValue |= rValue >> 32;
    ++rValue;

    return rValue;
}

#ifdef SIZE_T_NEQ_UINT32

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
size_t osgNextPower2<size_t>(size_t rValue)
{
    if(rValue == 0)
        return TypeTraits<size_t>::getOneElement();

    --rValue;
    rValue |= rValue >> 1;
    rValue |= rValue >> 2;
    rValue |= rValue >> 4;
    rValue |= rValue >> 8;
    rValue |= rValue >> 16;
    rValue |= rValue >> 32;
    ++rValue;

    return rValue;
}
#endif

#ifdef OSG_1_COMPAT
/*! Return the next larger power of 2, i.e. the smallest power of 2 not less
    than \a rValue.

    \param[in] rValue The lower bound for the wanted power of 2.
    \return A power of 2 not less than \a rValue or 0 if there is no such value
    within \a rValue type's range.

    \deprecated use osgNextPower2 instead.

    \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt32 osgnextpower2<UInt32>(UInt32 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int32 osgnextpower2<Int32>(Int32 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
UInt64 osgnextpower2<UInt64>(UInt64 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
Int64 osgnextpower2<Int64>(Int64 rValue)
{
    return OSG::osgNextPower2(rValue);
}

#ifdef SIZE_T_NEQ_UINT32

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
size_t osgnextpower2<size_t>(size_t rValue)
{
    return OSG::osgNextPower2(rValue);
}
#endif
#endif // OSG_1_COMPAT


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
        osgAbs(v[0]) > osgAbs(v[1]) ?
            (osgAbs(v[0]) > osgAbs(v[2]) ? 0 : 2) :
            (osgAbs(v[1]) > osgAbs(v[2]) ? 1 : 2);
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
void osgSleep(UInt32 millisecs)
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

#ifdef OSG_1_COMPAT
/*! Pause program execution for the given number of milliseconds.

    \param[in] millisecs Duration of the pause.

    \deprecated use osgSleep instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
void osgsleep(UInt32 millisecs)
{
    OSG::osgSleep(millisecs);
}
#endif // OSG_1_COMPAT

/*! Returns a uniformly distributed random Real32 between 0 and 1 inclusive.

    \return A random Real32 number between 0 and 1 inclusive.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgRand(void)
{
    return rand() / static_cast<Real32>(RAND_MAX);
}

#ifdef OSG_1_COMPAT
/*! Returns a uniformly distributed random Real32 between 0 and 1 inclusive.

    \return A random Real32 number between 0 and 1 inclusive.

    \deprecated use osgRand instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgrand(void)
{
    return OSG::osgRand();
}
#endif // OSG_1_COMPAT

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

#ifdef OSG_LONGLONG_HAS_LL

#define OSG_UINT64_LITERAL(value) value##ULL

#define OSG_INT64_LITERAL(value) value##LL

#else

#define OSG_UINT64_LITERAL(value) value##U

#define OSG_INT64_LITERAL(value) value

#endif

/*! Reverses the bytes of the value \a src . This function is a helper
    for the byte order conversion functions below.

    \param[in] src Value to be swapped.
    \return Value with it's byte order reversed.

    \ingroup GrpBaseBaseMiscFn
 */
template <>
inline UInt16
osgSwapBytes<UInt16>(UInt16 src)
{
    return (((src & 0x00ff) << 8) |
            ((src & 0xff00) >> 8)  );
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Int16
osgSwapBytes<Int16>(Int16 src)
{
    return static_cast<Int16>(osgSwapBytes(static_cast<UInt16>(src)));
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline UInt32
osgSwapBytes<UInt32>(UInt32 src)
{
    return (((src & 0x000000ff) << 24) |
            ((src & 0x0000ff00) <<  8) |
            ((src & 0x00ff0000) >>  8) |
            ((src & 0xff000000) >> 24)  );
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Int32
osgSwapBytes<Int32>(Int32 src)
{
    return static_cast<Int32>(osgSwapBytes(static_cast<UInt32>(src)));
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline UInt64
osgSwapBytes<UInt64>(UInt64 src)
{
    return (((src & OSG_UINT64_LITERAL(0x00000000000000ff)) << 56) |
            ((src & OSG_UINT64_LITERAL(0x000000000000ff00)) << 40) |
            ((src & OSG_UINT64_LITERAL(0x0000000000ff0000)) << 24) |
            ((src & OSG_UINT64_LITERAL(0x00000000ff000000)) <<  8) |
            ((src & OSG_UINT64_LITERAL(0x000000ff00000000)) >>  8) |
            ((src & OSG_UINT64_LITERAL(0x0000ff0000000000)) >> 24) |
            ((src & OSG_UINT64_LITERAL(0x00ff000000000000)) >> 40) |
            ((src & OSG_UINT64_LITERAL(0xff00000000000000)) >> 56)  );
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Int64
osgSwapBytes<Int64>(Int64 src)
{
    return static_cast<Int64>(osgSwapBytes(static_cast<UInt64>(src)));
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real32
osgSwapBytes<Real32>(Real32 src)
{
    UInt8* pStart = reinterpret_cast<UInt8*>(&src);
    UInt8* pEnd   = reinterpret_cast<UInt8*>(&src) + sizeof(Real32);

    std::reverse(pStart, pEnd);

    return src;
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real64
osgSwapBytes<Real64>(Real64 src)
{
    UInt8* pStart = reinterpret_cast<UInt8*>(&src);
    UInt8* pEnd   = reinterpret_cast<UInt8*>(&src) + sizeof(Real64);

    std::reverse(pStart, pEnd);

    return src;
}

/*! Convert a value from host byte order to big endian byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to big endian byte order.

    \note An actual conversion only happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgHostToBigEndian(TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return osgSwapBytes(src);
#else
    return src;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real128
osgHostToBigEndian<Real128>(Real128 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    char *p = reinterpret_cast<char*>(&src);

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[14]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
#else
    return src;
#endif
}

/*! Convert a value from host byte order to little endian byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to little endian byte order.

    \note An actual conversion only happens on big endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgHostToLittleEndian(TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return src;
#else
    return osgSwapBytes(src);
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real128
osgHostToLittleEndian<Real128>(Real128 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return src;
#else
    char *p = reinterpret_cast<char*>(&src);

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[14]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
#endif
}

/*! Convert a value from big endian byte order to host byte order.

    \param[in] src Input value in big endian byte order.
    \return The input converted to host byte order.

    \note An actual conversion only happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgBigEndianToHost(TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return osgSwapBytes(src);
#else
    return src;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real128
osgBigEndianToHost<Real128>(Real128 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    char *p = reinterpret_cast<char*>(&src);

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[14]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
#else
    return src;
#endif
}

/*! Convert a value from little endian byte order to host byte order.

    \param[in] src Input value in little endian byte order.
    \return The input converted to host byte order.

    \note An actual conversion only happens on big endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgLittleEndianToHost(TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return src;
#else
    return osgSwapBytes(src);
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <>
inline Real128
osgLittleEndianToHost<Real128>(Real128 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return src;
#else
    char *p = reinterpret_cast<char*>(&src);

    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[14]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);

    return src;
#endif
}

/*! Convert a value from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgHostToNet(const TypeT src)
{
    return OSG::osgHostToBigEndian(src);
}

/*! Convert a value from network byte order to host byte order.

    \param[in] src Input value in network byte order.
    \return The input converted to host byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT>
inline TypeT
osgNetToHost(const TypeT src)
{
    return OSG::osgBigEndianToHost(src);
}

// host to network

/*! Convert a UInt16 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osghtons(UInt16 src)
{
    return OSG::osgHostToNet(src);
}

/*! Convert a UInt32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osghtonl(UInt32 src)
{
    return OSG::osgHostToNet(src);
}

/*! Convert a UInt64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osghtonll(UInt64 src)
{
    return OSG::osgHostToNet(src);
}

/*! Convert a Real32 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osghtonf(Real32 src)
{
    return OSG::osgHostToNet(src);
}

/*! Convert a Real64 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osghtond(Real64 src)
{
    return OSG::osgHostToNet(src);
}

/*! Convert a Real128 from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgHostToNet instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osghtondd(Real128 src)
{
    return OSG::osgHostToNet(src);
}

// network to host

/*! Convert a UInt16 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt16 osgntohs(UInt16 src)
{
    return OSG::osgNetToHost(src);
}

/*! Convert a UInt32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt32 osgntohl(UInt32 src)
{
    return OSG::osgNetToHost(src);
}

/*! Convert a UInt64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
UInt64 osgntohll(UInt64 src)
{
    return OSG::osgNetToHost(src);
}

/*! Convert a Real32 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real32 osgntohf(Real32 src)
{
    return OSG::osgNetToHost(src);
}

/*! Convert a Real64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real64 osgntohd(Real64 src)
{
    return OSG::osgNetToHost(src);
}

/*! Convert a Real128 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
Real128 osgntohdd(Real128 src)
{
    return OSG::osgNetToHost(src);
}


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
void osgStringDup(const TChar *szInput, TChar *&szOutput)
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

#ifdef OSG_1_COMPAT
/*! Creates a copy of the C string \a szInput and stores a pointer to the copy
    in \a szOutput. The memory for the copy is allocated using \c new[], while
    any memory already pointed to by \a szOutput is deallocated
    with \c delete[].

    \param[in] szInput The C string to copy.
    \param[out] szOutput Set to point to the copy.

    \deprecated use osgStringDup instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
void stringDup(const TChar *szInput, TChar *&szOutput)
{
    OSG::osgStringDup(szInput, szOutput);
}
#endif // OSG_1_COMPAT

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
void  osgStringCopy(const Char8 *szInput, Char8 *szOutput)
{
    if(szInput != NULL && szOutput != NULL)
    {
        ::strcpy(szOutput, szInput);
    }
}

#ifdef OSG_1_COMPAT
/*! Creates a copy of the C string \a szInput at the position pointed to by
    \a szOutput. This function does not allocate memory, so \a szOutput must
    point to a buffer that is large enough.

    \param[in] szInput The C string to copy.
    \param[out] szOutput Pointer to a buffer where the copy is stored.

    \warning This function does not check the size of the destination buffer,
    hence it could overwrite other data if the buffer is not large enough !

    \deprecated use osgStringCopy instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
void  stringcpy(const Char8 *szInput, Char8 *szOutput)
{
    OSG::osgStringCopy(szInput, szOutput);
}
#endif // OSG_1_COMPAT

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
Int32 osgStringNCmp(const Char8 *string1, const Char8 *string2, size_t count)
{
    return ::strncmp(string1, string2, count);
}

#ifdef OSG_1_COMPAT
/*! Compares two C strings, but considers at most the first \a count characters.
    The return value has the same sign as the difference of the first differing
    pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \param[in] count Maximal number of charaters to compare
    \return 0 if the first \a count characters of both strings are equal,
    -1 if \a string1 is less than \a string2 and 1 otherwise.

    \deprecated use osgStringNCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringncmp(const Char8 *string1, const Char8 *string2, size_t count)
{
    return OSG::osgStringNCmp(string1, string2, count);
}
#endif // OSG_1_COMPAT

/*! Returns the length of a C string, i.e. the number of characters from the
    given pointer, to the first zero character.

    \param[in] string1 String whose length is determined.
    \return Length of the string.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 osgStringLen(const Char8 *string1)
{
    return ::strlen(string1);
}

#ifdef OSG_1_COMPAT
/*! Returns the length of a C string, i.e. the number of characters from the
    given pointer, to the first zero character.

    \param[in] string1 String whose length is determined.
    \return Length of the string.

    \deprecated use osgStringLen instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringlen(const Char8 *string1)
{
    return OSG::osgStringLen(string1);
}
#endif // OSG_1_COMPAT

/*! Compares two C strings. The return value has the same sign as the
    difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 osgStringCmp(const Char8 *string1, const Char8 *string2)
{
    return ::strcmp(string1, string2);
}

#ifdef OSG_1_COMPAT
/*! Compares two C strings. The return value has the same sign as the
    difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \deprecated use osgStringCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringcmp(const Char8 *string1, const Char8 *string2)
{
    return OSG::osgStringCmp(string1, string2);
}
#endif // OSG_1_COMPAT

/*! Compare two C strings ignoring differences in case. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 osgStringCaseCmp(const Char8 *string1,
                       const Char8 *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp  (string1, string2);
#endif
}

#ifdef OSG_1_COMPAT
/*! Compare two C strings ignoring differences in case. The return value has
    the same sign as the difference of the first differing pair of characters.

    \param[in] string1 First string for comparison.
    \param[in] string2 Second string for comparison.
    \return 0 if both strings are equal, -1 if \a string1 is less than
    \a string2 and 1 otherwise.

    \deprecated use osgStringCaseCmp instead.

    \ingroup GrpBaseBaseStringFn
 */
inline
Int32 stringcasecmp(const Char8 *string1,
                    const Char8 *string2)
{
    return OSG::osgStringCaseCmp(string1, string2);
}
#endif // OSG_1_COMPAT


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

#undef OSG_UINT64_LITERAL
#undef OSG_INT64_LITERAL

OSG_END_NAMESPACE

#define OSGBASEFUNCTIONS_INLINE_CVSID "@(#)$Id$"
