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

//#define OSG_GENERAL_TEMPLATE_BEFORE_SPEZ

/*---------------------------------------------------------------------*/
/*! \name sqrt                                                         */
/*! \{                                                                 */

/*! Return the square root of the argument, i.e. the number \c y that satisfies
    <tt>y<sup>2</sup> == rValue</tt>. The argument must be nonnegative.

    \param[in] rValue The number to compute the square root of, must be >= 0.
    \return The square root of the argument.

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSqrt(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSqrt(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgSqrt(const OSG::Real32 rValue)
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
OSG::Real64 osgSqrt(const OSG::Real64 rValue)
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
OSG::Real128 osgSqrt(const OSG::Real128 rValue)
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
OSG::Fixed32 osgSqrt(const OSG::Fixed32 rValue)
{
    return Fixed32::sqrt(rValue);
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSqrt(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSqrt(RealType(rValue));
}
#endif

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
OSG::Real32 osgsqrt(const OSG::Real32 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgsqrt(const OSG::Real64 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgsqrt(const OSG::Real128 rValue)
{
    return OSG::osgSqrt(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgsqrt(const OSG::Fixed32 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgCos(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgCos(const OSG::Real32 rValue)
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
OSG::Real64 osgCos(const OSG::Real64 rValue)
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
OSG::Real128 osgCos(const OSG::Real128 rValue)
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
OSG::Fixed32 osgCos(const OSG::Fixed32 rValue)
{
    return Fixed32::cos(rValue);
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgCos(RealType(rValue));
}
#endif

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
OSG::Real32 osgcos(const OSG::Real32 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgcos(const OSG::Real64 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgcos(const OSG::Real128 rValue)
{
    return OSG::osgCos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgcos(const OSG::Fixed32 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSin(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgSin(const OSG::Real32 rValue)
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
OSG::Real64 osgSin(const OSG::Real64 rValue)
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
OSG::Real128 osgSin(const OSG::Real128 rValue)
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
OSG::Fixed32 osgSin(const OSG::Fixed32 rValue)
{
    return Fixed32::sin(rValue);
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgSin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgSin(RealType(rValue));
}
#endif

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
OSG::Real32 osgsin(const OSG::Real32 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgsin(const OSG::Real64 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgsin(const OSG::Real128 rValue)
{
    return OSG::osgSin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgsin(const OSG::Fixed32 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgTan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgTan(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgTan(const OSG::Real32 rValue)
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
OSG::Real64 osgTan(const OSG::Real64 rValue)
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
OSG::Real128 osgTan(const OSG::Real128 rValue)
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
OSG::Fixed32 osgTan(const OSG::Fixed32 rValue)
{
    return Fixed32::tan(rValue);
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgTan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgTan(RealType(rValue));
}
#endif

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
OSG::Real32 osgtan(const OSG::Real32 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgtan(const OSG::Real64 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgtan(const OSG::Real128 rValue)
{
    return OSG::osgTan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgtan(const OSG::Fixed32 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgACos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgACos(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgACos(const OSG::Real32 rValue)
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
OSG::Real64 osgACos(const OSG::Real64 rValue)
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
OSG::Real128 osgACos(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::acos(rValue);
#else
    return acosl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgACos(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgACos(RealType(rValue));
}
#endif

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
OSG::Real32 osgacos(const OSG::Real32 rValue)
{
    return OSG::osgACos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgacos(const OSG::Real64 rValue)
{
    return OSG::osgACos(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgacos(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgASin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgASin(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgASin(const OSG::Real32 rValue)
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
OSG::Real64 osgASin(const OSG::Real64 rValue)
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
OSG::Real128 osgASin(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::asin(rValue);
#else
    return asinl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgASin(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgASin(RealType(rValue));
}
#endif

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
OSG::Real32 osgasin(const OSG::Real32 rValue)
{
    return OSG::osgASin(rValue);
}


/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgasin(const OSG::Real64 rValue)
{
    return OSG::osgASin(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgasin(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgATan(const OSG::Real32 rValue)
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
OSG::Real64 osgATan(const OSG::Real64 rValue)
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
OSG::Real128 osgATan(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::atan(rValue);
#else
    return atanl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan(RealType(rValue));
}
#endif

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
OSG::Real32 osgatan(const OSG::Real32 rValue)
{
    return OSG::osgATan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgatan(const OSG::Real64 rValue)
{
    return OSG::osgATan(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgatan(const OSG::Real128 rValue)
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
    \return The arc tangent of <tt>rValue1 / rValue2</tt> in the 
            range [-pi; pi].

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan2(RealType(rValue1), RealType(rValue2));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgATan2(const OSG::Real32 rValue1, const OSG::Real32 rValue2)
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
OSG::Real64 osgATan2(const OSG::Real64 rValue1, const OSG::Real64 rValue2)
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
OSG::Real128 osgATan2(const OSG::Real128 rValue1, const OSG::Real128 rValue2)
{
#ifdef OSG_USE_STDMATH
    return std::atan2(rValue1, rValue2);
#else
    return atan2l(rValue1, rValue2);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgATan2(const FloatTypeT rValue1,
             const FloatTypeT rValue2)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgATan2(RealType(rValue1), RealType(rValue2));
}
#endif

#ifdef OSG_1_COMPAT
/*! Return the arc tangent (in radians) of <tt>rValue1 / rValue2</tt> using
    the signs of both arguments to determine the quadrant. This can be used to
    obtain the angle component of the polar coordinates of a point with
    cartesian coordinates (\a rValue2, \a rValue1).

    \param[in] rValue1 The numerator of the value to compute atan of.
    \param[in] rValue2 The denominator of the value to compute atan of.
    \return The arc tangent of <tt>rValue1 / rValue2</tt> in the 
            range [-pi; pi].

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
OSG::Real32 osgatan2(const OSG::Real32 rValue1, const OSG::Real32 rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgatan2(const OSG::Real64 rValue1, const OSG::Real64 rValue2)
{
    return OSG::osgATan2(rValue1, rValue2);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgatan2(const OSG::Real128 rValue1, const OSG::Real128 rValue2)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgAbs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgAbs(const OSG::Real32 rValue)
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
OSG::Real64 osgAbs(const OSG::Real64 rValue)
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
OSG::Fixed32 osgAbs(const OSG::Fixed32 rValue)
{
    return Fixed32::abs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgAbs(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::abs(rValue);
#else
    return fabsl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class TypeT> inline
TypeT osgAbs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}
#endif

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
OSG::Real32 osgabs(const OSG::Real32 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgabs(const OSG::Real64 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgabs(const OSG::Fixed32 rValue)
{
    return OSG::osgAbs(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgabs(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgPow(const FloatTypeT rValue,
           const FloatTypeT rExp)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgPow(RealType(rValue), RealType(rExp));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgPow(const OSG::Real32 rValue, const OSG::Real32 rExp)
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
OSG::Real64 osgPow(const OSG::Real64 rValue, const OSG::Real64 rExp)
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
OSG::Real128 osgPow(const OSG::Real128 rValue, const OSG::Real128 rExp)
{
#ifdef OSG_USE_STDMATH
    return std::pow(rValue, rExp);
#else
    return powl(rValue, rExp);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgPow(const FloatTypeT rValue,
           const FloatTypeT rExp)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgPow(RealType(rValue), RealType(rExp));
}
#endif

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
OSG::Real32 osgpow(const OSG::Real32 rValue, const OSG::Real32 rExp)
{
    return OSG::osgPow(rValue, rExp);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgpow(const OSG::Real64 rValue, const OSG::Real64 rExp)
{
    return OSG::osgPow(rValue, rExp);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgpow(const OSG::Real128 rValue, const OSG::Real128 rExp)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgLog(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgLog(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgLog(const OSG::Real32 rValue)
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
OSG::Real64 osgLog(const OSG::Real64 rValue)
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
OSG::Real128 osgLog(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::log(rValue);
#else
    return logl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgLog(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgLog(RealType(rValue));
}
#endif

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
OSG::Real32 osglog(const OSG::Real32 rValue)
{
    return OSG::osgLog(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osglog(const OSG::Real64 rValue)
{
    return OSG::osgLog(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osglog(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgExp(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgExp(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgExp(const OSG::Real32 rValue)
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
OSG::Real64 osgExp(const OSG::Real64 rValue)
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
OSG::Real128 osgExp(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::exp(rValue);
#else
    return expl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgExp(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgExp(RealType(rValue));
}
#endif

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
OSG::Real32 osgexp(const OSG::Real32 rValue)
{
    return OSG::osgExp(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgexp(const OSG::Real64 rValue)
{
    return OSG::osgExp(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgexp(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgFloor(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgFloor(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgFloor(const OSG::Real32 rValue)
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
OSG::Real64 osgFloor(const OSG::Real64 rValue)
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
OSG::Real128 osgFloor(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::floor(rValue);
#else
    return floorl(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgFloor(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgFloor(RealType(rValue));
}
#endif

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
OSG::Real32 osgfloor(const OSG::Real32 rValue)
{
    return OSG::osgFloor(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgfloor(const OSG::Real64 rValue)
{
    return OSG::osgFloor(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgfloor(const OSG::Real128 rValue)
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
 */

#ifdef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCeil(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgCeil(RealType(rValue));
}
#endif

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real32 osgCeil(const OSG::Real32 rValue)
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
OSG::Real64 osgCeil(const OSG::Real64 rValue)
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
OSG::Real128 osgCeil(const OSG::Real128 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::ceil(rValue);
#else
    return ceill(rValue);
#endif
}

#ifndef OSG_GENERAL_TEMPLATE_BEFORE_SPEZ
/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgCeil(const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgCeil(RealType(rValue));
}
#endif

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
OSG::Real32 osgceil(const OSG::Real32 rValue)
{
    return OSG::osgCeil(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgceil(const OSG::Real64 rValue)
{
    return OSG::osgCeil(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real128 osgceil(const OSG::Real128 rValue)
{
    return OSG::osgCeil(rValue);
}
#endif // OSG_1_COMPAT


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name mod                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */
inline 
OSG::Real32 osgMod(const OSG::Real32 lValue, const OSG::Real32 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::fmod(lValue, rValue);
#else
    return fmodf(lValue, rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline 
OSG::Real64 osgMod(const OSG::Real64 lValue, const OSG::Real64 rValue)
{
#ifdef OSG_USE_STDMATH
    return std::fmod(lValue, rValue);
#else
    return fmod(lValue, rValue);
#endif
}

/*! \param[in] lValue 
    \param[in] rValue 
    \return lValue % rValue

    \note This function forwards to an appropriate C++ or C library function,
    hence exhibits the respective error behavior.
 */

/*! \ingroup GrpBaseBaseMathFn
 */
template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgMod(const FloatTypeT lValue, const FloatTypeT rValue)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  OSG::osgMod(RealType(lValue), RealType(rValue));
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
OSG::UInt32 osgFinite(const FloatTypeT rValue)
{
#ifdef WIN32
    return _finite(rValue);
#else
# ifdef __hpux
    return  isfinite(rValue);
# else
#  ifdef __APPLE__
    return  std::isfinite(rValue);
#  else
    return  finite(rValue);
#  endif
# endif
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
OSG::UInt32 osgfinite(const FloatTypeT rValue)
{
    return OSG::osgFinite(rValue);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name min / max                                                    */
/*! \{                                                                 */

/*! Return the smaller of the two arguments.

    \param[in] lValue First value for comparison.
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

    \param[in] lValue First value for comparison.
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
    OSG_ASSERT(minVal <= maxVal);

    return ((val > minVal) ? ((val < maxVal) ? val : maxVal) : minVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name Equality Comparison                                          */
/*! \{                                                                 */

template <class TypeT> inline
bool osgIsEqual(const TypeT lValue, const TypeT rValue, const TypeT tol)
{
    return osgAbs(lValue - rValue) < tol;
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

    \param[in,out] lValue New value for \a rValue, is assigned the
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
OSG::Real32 osgDegree2Rad(const OSG::Real32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgDegree2Rad(const OSG::Real64 rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgDegree2Rad(const OSG::Fixed32 rValue)
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
OSG::Real32 osgdegree2rad(const OSG::Real32 rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgdegree2rad(const OSG::Real64 rValue)
{
    return OSG::osgDegree2Rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgdegree2rad(const OSG::Fixed32 rValue)
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
OSG::Real32 osgRad2Degree(const OSG::Real32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgRad2Degree(const OSG::Real64 rValue)
{
    return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgRad2Degree(const OSG::Fixed32 rValue)
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
OSG::Real32 osgrad2degree(const OSG::Real32 rValue)
{
    return OSG::osgRad2Degree(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Real64 osgrad2degree(const OSG::Real64 rValue)
{
    return OSG::osgRad2Degree(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
inline
OSG::Fixed32 osgrad2degree(const OSG::Fixed32 rValue)
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
bool osgIsPower2<UInt32>(const OSG::UInt32 rValue)
{
    return !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<Int32>(const OSG::Int32 rValue)
{
    return (rValue >= 0) && !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<UInt64>(const OSG::UInt64 rValue)
{
    return !(rValue & (rValue - 1));
}

template <> inline
bool osgIsPower2<Int64>(const OSG::Int64 rValue)
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
bool osgispower2<UInt32>(const OSG::UInt32 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<Int32>(const OSG::Int32 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<UInt64>(const OSG::UInt64 rValue)
{
    return OSG::osgIsPower2(rValue);
}

template <> inline
bool osgispower2<Int64>(const OSG::Int64 rValue)
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
OSG::UInt32 osgNextPower2<UInt32>(OSG::UInt32 rValue)
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
OSG::Int32 osgNextPower2<Int32>(OSG::Int32 rValue)
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
OSG::UInt64 osgNextPower2<UInt64>(OSG::UInt64 rValue)
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
OSG::Int64 osgNextPower2<Int64>(OSG::Int64 rValue)
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
#if defined(SIZE_T_64BIT)
    rValue |= rValue >> 32;
#endif
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
OSG::UInt32 osgnextpower2<UInt32>(OSG::UInt32 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
OSG::Int32 osgnextpower2<Int32>(OSG::Int32 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
OSG::UInt64 osgnextpower2<UInt64>(OSG::UInt64 rValue)
{
    return OSG::osgNextPower2(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */
template <> inline
OSG::Int64 osgnextpower2<Int64>(OSG::Int64 rValue)
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

inline 
OSG::Int32 osgLog2Int(OSG::Real32 v)
{
    union
    {
        OSG::Real32 realVal;
        OSG::Int32  intVal;
    } data;

    data.realVal = v;

    return (data.intVal >> 23) - 127;
}

inline 
OSG::Int32 osgRound2Int(OSG::Real64 val) 
{
#ifdef OSG_FAST_INT
    union
    {
        OSG::Real64 realVal;
        OSG::Int64  intVal;
    } data;

    data.realVal = val + OSG_DOUBLEMAGIC;
    return data.intVal;
#else
	return static_cast<OSG::Int32>(val + OSG_DOUBLEMAGICROUNDEPS);
#endif
}

/*! Returns the index of the element that has the largest absolute value in
    a Vec3 or Pnt3.

    \param[in] v Input Vec3 or Pnt3.
    \return Index of the element with largest absolute value.

    \ingroup GrpBaseBaseMiscFn
 */
template<class VecPntT> inline
OSG::UInt32 getMaxIndexAbs3(const VecPntT &v)
{
    return
        osgAbs(v[0]) > osgAbs(v[1]) ?
            (osgAbs(v[0]) > osgAbs(v[2]) ? 0 : 2) :
            (osgAbs(v[1]) > osgAbs(v[2]) ? 1 : 2);
}

#if !defined(__linux)
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
OSG::Int32 putenv(Char8 *string)
{
#if !defined(WIN32) || defined(BCC)
    return ::putenv(string);
#else
    return ::_putenv(string);
#endif
}
inline
Char8 *getenv(const Char8 *string)
{
    return ::getenv(string);
}
#endif

/*! Pause program execution for the given number of milliseconds.

    \param[in] millisecs Duration of the pause.

    \ingroup GrpBaseBaseMiscFn
 */
inline
void osgSleep(OSG::UInt32 millisecs)
{
#ifdef WIN32
    Sleep(millisecs);
#else

    struct timespec req;
    int ns;

    req.tv_sec  = static_cast<long> (millisecs / 1000);
    req.tv_nsec = static_cast<long>((millisecs % 1000) * 1000 * 1000);

    while((req.tv_sec > 0 || req.tv_nsec > 0) &&
          (ns = nanosleep(&req, &req)) < 0)
    {
        if(ns < 0 && errno != EINTR)
        {
            break;
        }
    }
#endif
}

#ifdef OSG_1_COMPAT
/*! Pause program execution for the given number of milliseconds.

    \param[in] millisecs Duration of the pause.

    \deprecated use osgSleep instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
void osgsleep(OSG::UInt32 millisecs)
{
    OSG::osgSleep(millisecs);
}
#endif // OSG_1_COMPAT

/*! Returns a uniformly distributed random Real32 between 0 and 1 inclusive.

    \return A random Real32 number between 0 and 1 inclusive.

    \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real32 osgRand(void)
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
OSG::Real32 osgrand(void)
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
std::ostream &operator<<(std::ostream &os, OSG::UInt64 v)
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
std::ostream &operator<<(std::ostream &os, OSG::Int64 v)
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
template <> inline 
OSG::UInt16 osgSwapBytes<UInt16>(OSG::UInt16 src)
{
    return (((src & 0x00ff) << 8) |
            ((src & 0xff00) >> 8)  );
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline 
OSG::Int16 osgSwapBytes<Int16>(OSG::Int16 src)
{
    return static_cast<Int16>(osgSwapBytes<UInt16>(static_cast<UInt16>(src)));
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline 
OSG::UInt32 osgSwapBytes<UInt32>(OSG::UInt32 src)
{
    return (((src & 0x000000ff) << 24) |
            ((src & 0x0000ff00) <<  8) |
            ((src & 0x00ff0000) >>  8) |
            ((src & 0xff000000) >> 24)  );
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline 
OSG::Int32 osgSwapBytes<Int32>(OSG::Int32 src)
{
    return static_cast<Int32>(osgSwapBytes<UInt32>(static_cast<UInt32>(src)));
}

#ifdef OSG_GLENUM_NEQ_UINT32
/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline 
GLenum osgSwapBytes<GLenum>(GLenum src)
{
    return static_cast<GLenum>(osgSwapBytes<UInt32>(static_cast<UInt32>(src)));
}
#endif // OSG_GLENUM_NEQ_UINT32

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline 
OSG::UInt64 osgSwapBytes<UInt64>(OSG::UInt64 src)
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
template <> inline 
OSG::Int64 osgSwapBytes<Int64>(OSG::Int64 src)
{
    return static_cast<Int64>(osgSwapBytes<UInt64>(static_cast<UInt64>(src)));
}

/*! Reverse the bytes of the floating point value \a src.

    \note It does not return a floating point value, to avoid the value being
          passed through a 387 FPU register - the excess precision of the 387
          causes certain values (NaN) to be garbled and after the reversal
          the bit pattern of a regular value might be the same as a NaN.

    \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::UInt32 osgSwapBytesFP(OSG::Real32 src)
{
    union
    {
        OSG::Real32 floatVal;
        OSG::UInt32 intVal;
    } unionVal;

    unionVal.floatVal = src;
    unionVal.intVal   = osgSwapBytes(unionVal.intVal);

    return unionVal.intVal;
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real32 osgSwapBytesFP(OSG::UInt32 src)
{
    union
    {
        OSG::Real32 floatVal;
        OSG::UInt32 intVal;
    } unionVal;

    unionVal.intVal = osgSwapBytes(src);

    return unionVal.floatVal;
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::UInt64 osgSwapBytesFP(OSG::Real64 src)
{
    union
    {
        OSG::Real64 floatVal;
        OSG::UInt64 intVal;
    } unionVal;

    unionVal.floatVal = src;
    unionVal.intVal   = osgSwapBytes(unionVal.intVal);

    return unionVal.intVal;
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real64 osgSwapBytesFP(OSG::UInt64 src)
{
    union
    {
        OSG::Real64 floatVal;
        OSG::UInt64 intVal;
    } unionVal;

    unionVal.intVal = osgSwapBytes(src);

    return unionVal.floatVal;
}

/*! Reverses bytes of the \a count values of size \a ElemSize pointed to by
    \a mem.

    \warning Be sure you know what you are doing when using these functions,
             as they make aliasing rule violiations very easy/likely.

    \ingroup GrpBaseBaseMiscFn
 */
template <> inline
void osgSwapMem<2>(void *mem, OSG::SizeT count)
{
    OSG::UInt16 *p = static_cast<OSG::UInt16 *>(mem);

    for(OSG::SizeT i = 0; i < count; ++i)
    {
        p[i] = osgSwapBytes(p[i]);
    }
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline
void osgSwapMem<4>(void *mem, OSG::SizeT count)
{
    OSG::UInt32 *p = static_cast<OSG::UInt32 *>(mem);

    for(OSG::SizeT i = 0; i < count; ++i)
    {
        p[i] = osgSwapBytes(p[i]);
    }
}

/*! \ingroup GrpBaseBaseMiscFn
 */
template <> inline
void osgSwapMem<8>(void *mem, OSG::SizeT count)
{
    OSG::UInt64 *p = static_cast<OSG::UInt64 *>(mem);

    for(OSG::SizeT i = 0; i < count; ++i)
    {
        p[i] = osgSwapBytes(p[i]);
    }
}

/*! Convert a value from host byte order to network byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT> inline 
TypeT osgHostToNet(const TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytes(src);
#else
    return src;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::UInt32 osgHostToNetFP(const OSG::Real32 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytesFP(src);
#else
    union
    {
        OSG::Real32 floatVal;
        OSG::UInt32 intVal;
    } unionVal;

    unionVal.floatVal = src;

    return unionVal.intVal;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::UInt64 osgHostToNetFP(const OSG::Real64 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytesFP(src);
#else
    union
    {
        OSG::Real64 floatVal;
        OSG::UInt64 intVal;
    } unionVal;

    unionVal.floatVal = src;

    return unionVal.intVal;
#endif
}

/*! Convert a value from network byte order to host byte order.

    \param[in] src Input value in network byte order.
    \return The input converted to host byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \ingroup GrpBaseBaseMiscFn
 */
template <class TypeT> inline 
TypeT osgNetToHost(const TypeT src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytes(src);
#else
    return src;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real32 osgNetToHostFP(const OSG::UInt32 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytesFP(src);
#else
    union
    {
        OSG::Real32 floatVal;
        OSG::UInt32 intVal;
    } unionVal;

    unionVal.intVal = src;

    return unionVal.floatVal;
#endif
}

/*! \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real64 osgNetToHostFP(const OSG::UInt64 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    return OSG::osgSwapBytesFP(src);
#else
    union
    {
        OSG::Real64 floatVal;
        OSG::UInt64 intVal;
    } unionVal;

    unionVal.intVal = src;

    return unionVal.floatVal;
#endif
}


#ifdef OSG_1_COMPAT
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
OSG::UInt16 osghtons(OSG::UInt16 src)
{
    return OSG::osgHostToNet<UInt16>(src);
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
OSG::UInt32 osghtonl(OSG::UInt32 src)
{
    return OSG::osgHostToNet<UInt32>(src);
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
OSG::UInt64 osghtonll(OSG::UInt64 src)
{
    return OSG::osgHostToNet<UInt64>(src);
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
OSG::Real32 osghtonf(OSG::Real32 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    UInt8 *p = reinterpret_cast<UInt8 *>(&src);
    std::swap(p[0], p[3]);
    std::swap(p[1], p[2]);
#endif

    return src;
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
OSG::Real64 osghtond(OSG::Real64 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    UInt8 *p = reinterpret_cast<UInt8 *>(&src);
    std::swap(p[0], p[7]);
    std::swap(p[1], p[6]);
    std::swap(p[2], p[5]);
    std::swap(p[3], p[4]);
#endif

    return src;
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
OSG::Real128 osghtondd(OSG::Real128 src)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    UInt8 *p = reinterpret_cast<UInt8 *>(&src);
    std::swap(p[0], p[15]);
    std::swap(p[1], p[14]);
    std::swap(p[2], p[13]);
    std::swap(p[3], p[12]);
    std::swap(p[4], p[11]);
    std::swap(p[5], p[10]);
    std::swap(p[6], p[9]);
    std::swap(p[7], p[8]);
#endif

    return src;
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
    return osghtons(src);
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
OSG::UInt32 osgntohl(OSG::UInt32 src)
{
    return osgntohl(src);
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
OSG::UInt64 osgntohll(OSG::UInt64 src)
{
    return osghtonll(src);
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
OSG::Real32 osgntohf(OSG::Real32 src)
{
    return osghtonf(src);
}

/*! Convert a OSG::Real64 from network byte order to host byte order.

    \param[in] src Input value in host byte order.
    \return The input converted to network byte order.

    \note Network byte order is big endian, so an actual conversion only
    happens on little endian architectures.

    \deprecated use osgNetToHost instead.

    \ingroup GrpBaseBaseMiscFn
 */
inline
OSG::Real64 osgntohd(OSG::Real64 src)
{
    return osghtond(src);
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
OSG::Real128 osgntohdd(OSG::Real128 src)
{
    return osghtondd(src);
}
#endif // OSG_1_COMPAT

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name alignOffset                                               */
/*! \{                                                                 */

inline
std::size_t alignOffset(
    std::size_t base_alignment, 
    std::size_t base_offset)
{
    return 
        base_alignment * (
            (base_alignment + base_offset - 1) / base_alignment );
}


/*! \}                                                                 */
/*---------------------------------------------------------------------*/


// Indirector

template <class ContentT, class IndexT> inline
indirector<ContentT, IndexT>::indirector(ContentT cont) : _cont(cont)
{
}

template <class ContentT, class IndexT> inline
bool indirector<ContentT, IndexT>::operator()(IndexT a, IndexT b)
{
    if(_cont[a] < _cont[b])
        return true;

    return false;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

#undef OSG_UINT64_LITERAL
#undef OSG_INT64_LITERAL

OSG_END_NAMESPACE

