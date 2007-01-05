/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGGEOVECTORPROPERTYCONVERSION_H_
#define _OSGGEOVECTORPROPERTYCONVERSION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

#if 0
namespace detail
{

// The following is quite involved because of the special handling the
// Vec*fx, Pnt*fx and Color*fx types (i.e. element type Fixed32) require.
//
// When performing a conversion with an fx type as source the
// Fixed32::getValue() method is called (which seems bogus - but so be it) to
// obtain an Int32 value used in the further computation - this leads to the
// VectorElementAccessFunc and Fixed32VectorElementAccessFunc types.
//
// Conversions with an fx type as destination only succeed for the few types
// Fixed32 accepts in its constructors (Real32, UInt32, Fixed32), but if
// source and destination are of type Fixed32 we must be careful to avoid the
// getValue call, because there is no public constructor that accepts Int32.
// To allow this behaviour the *VectorElementAccessFunc templates have two
// type parameters.

/*! \brief No-op normalization static function object.
 */
template <class ValueTypeT>
struct NoNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief "In" conversion normalization static function object.
 */
template <class ValueTypeT>
struct InNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief "Out" conversion normalization static function object.
 */
template <class ValueTypeT>
struct OutNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief Static function object for accessing an element of a vector with
    Fixed32 elements.
 */
template <class ValueTypeT>
struct Fixed32VectorElementAccessFunc
{
    typedef          ValueTypeT           ValueType;
    typedef          Int32                ElementType;

    static inline ElementType
    apply(const ValueType& src, const UInt32 index);
};

/*! \brief Static function object for accessing an element of a vector.
 */
template <class ValueTypeT>
struct VectorElementAccessFunc
{
    typedef          ValueTypeT           ValueType;
    typedef typename ValueType::ValueType ElementType;

    static inline ElementType
    apply(const ValueType& src, const UInt32 index);
};

/*! \brief Partial specialization for vectors with Fixed32 elements,
    implemented via inheritance.
 */
template <class StorageInterfaceT>
struct VectorElementAccessFunc<VectorInterface<Fixed32,
                                               StorageInterfaceT>
                               >
    : public Fixed32VectorElementAccessFunc<VectorInterface<Fixed32,
                                                            StorageInterfaceT>
                                            >
{
};

/*! \brief Partial specialization for points with Fixed32 elements,
    implemented via inheritance.
 */
template <class StorageInterfaceT>
struct VectorElementAccessFunc<PointInterface<Fixed32, StorageInterfaceT> >
    : public Fixed32VectorElementAccessFunc<PointInterface<Fixed32,
                                                           StorageInterfaceT>
                                            >
{
};

/*! \brief Specialization for Color3fx, implemented via inheritance.
 */
template <>
struct VectorElementAccessFunc<Color3fx>
    : public Fixed32VectorElementAccessFunc<Color3fx>
{
};

/*! \brief Specialization for Color4fx, implemented via inheritance.
 */
template <>
struct VectorElementAccessFunc<Color4fx>
    : public Fixed32VectorElementAccessFunc<Color4fx>
{
};

/*! \brief Main conversion function.
 */
template <class                  DestTypeT,
          class                  SourceTypeT,
          template <class> class NormalizeFuncT,
          template <class> class ElementAccessFuncT>
struct GeoConvertFunc
{
    typedef          DestTypeT                         DestType;
    typedef          SourceTypeT                       SourceType;

    typedef typename DestType::ValueType               DestElementType;
    typedef typename SourceType::ValueType             SourceElementType;

    typedef          NormalizeFuncT<SourceElementType> NormFunc;
    typedef          ElementAccessFuncT<SourceType>    AccessFunc;

    static inline void
    convert(      DestType& dest,      const SourceType& src,
            const Real64    scale = 1, const Real64      offset = 0);
};

/*! \brief Partial specialization to optimize same type conversions without
    normalization.
 */
template <class                  ValueTypeT,
          template <class> class ElementAccessFuncT>
struct GeoConvertFunc<ValueTypeT,
                      ValueTypeT,
                      NoNormalizationFunc,
                      ElementAccessFuncT  >
{
    typedef          ValueTypeT                             DestType;
    typedef          ValueTypeT                             SourceType;

    typedef typename DestType::ValueType                    DestElementType;
    typedef typename SourceType::ValueType                  SourceElementType;

    typedef          NoNormalizationFunc<SourceElementType> NormFunc;
    typedef          ElementAccessFuncT<SourceType>         AccessFunc;

    static inline void
    convert(      DestType& dest,      const SourceType& src,
            const Real64    scale = 1, const Real64      offset = 0);
};

/*! \brief The "interface" of the implementation.
 */
template <class                  DestTypeT,
          class                  SourceTypeT,
          template <class> class NormalizeFuncT>
struct GeoConvertImpl : public GeoConvertFunc<DestTypeT,
                                              SourceTypeT,
                                              NormalizeFuncT,
                                              VectorElementAccessFunc>
{
};

} // namespace detail

OSG_END_NAMESPACE

// pull in implementation for inlining below
#include "OSGGeoVectorPropertyConversion.inl"

OSG_BEGIN_NAMESPACE

struct GeoConvert
{
    template <class StoredTypeT, class ExternalTypeT>
    inline static void
    convertIn(      StoredTypeT& dest,      const ExternalTypeT& src,
              const Real64       scale = 1, const Real64         offset = 0)
    {
        detail::GeoConvertImpl<StoredTypeT,
                               ExternalTypeT,
                               detail::NoNormalizationFunc>::convert(
            dest, src, scale, offset);
    }

    template <class ExternalTypeT, class StoredTypeT>
    inline static void
    convertOut(      ExternalTypeT& dest,      const StoredTypeT& src,
               const Real64         scale = 1, const Real64       offset = 0)
    {
        detail::GeoConvertImpl<ExternalTypeT,
                               StoredTypeT,
                               detail::NoNormalizationFunc>::convert(
            dest, src, scale, offset);
    }
};

struct GeoConvertNormalize
{
    template <class StoredTypeT, class ExternalTypeT>
    inline static void
    convertIn(      StoredTypeT& dest,      const ExternalTypeT& src,
              const Real64       scale = 1, const Real64         offset = 0)
    {
        detail::GeoConvertImpl<StoredTypeT,
                               ExternalTypeT,
                               detail::InNormalizationFunc>::convert(
            dest, src, scale, offset);
    }

    template <class ExternalTypeT, class StoredTypeT>
    inline static void
    convertOut(      ExternalTypeT& dest,      const StoredTypeT& src,
               const Real64         scale = 1, const Real64       offset = 0)
    {
        detail::GeoConvertImpl<ExternalTypeT,
                               StoredTypeT,
                               detail::OutNormalizationFunc>::convert(
            dest, src, scale, offset);
    }
};

#else

/* Helper classes for vector type conversions */

// Converter class for vector conversion
struct GeoConvert
{
    template <class ExternalType, class StoredType>
    inline static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = StoredType::Null[i];
        }
    }

    template <class ExternalType, class StoredType>
    inline static void convertOut(ExternalType& dest, const StoredType& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType, class StoredType>
    inline static void convertCustomOut(      ExternalType &dest,
                                        const StoredType   &src,
                                              Real64        scale = 1,
                                              Real64        offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
            {
                dest[i] =
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
            {
                dest[i] =
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Color3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Color4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }

};

struct GeoConvertNormalize
{
    template <class ExternalType, class StoredType>
    static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            StoredType::Null[i] * scale + offset);
         }
    }

    template <class ExternalType, class StoredType>
    static void convertOut(ExternalType& dest, const StoredType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (StoredType::Null[i] - offset) / scale);
         }
    }
};

#endif

OSG_END_NAMESPACE

#define OSGGEOVECTORPROPERTYCONVERSION_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGGEOVECTORPROPERTYCONVERSION_H_ */
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGGEOVECTORPROPERTYCONVERSION_H_
#define _OSGGEOVECTORPROPERTYCONVERSION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

#if 0
namespace detail
{

// The following is quite involved because of the special handling the
// Vec*fx, Pnt*fx and Color*fx types (i.e. element type Fixed32) require.
//
// When performing a conversion with an fx type as source the
// Fixed32::getValue() method is called (which seems bogus - but so be it) to
// obtain an Int32 value used in the further computation - this leads to the
// VectorElementAccessFunc and Fixed32VectorElementAccessFunc types.
//
// Conversions with an fx type as destination only succeed for the few types
// Fixed32 accepts in its constructors (Real32, UInt32, Fixed32), but if
// source and destination are of type Fixed32 we must be careful to avoid the
// getValue call, because there is no public constructor that accepts Int32.
// To allow this behaviour the *VectorElementAccessFunc templates have two
// type parameters.

/*! \brief No-op normalization function object.
 */
template <class ValueTypeT>
struct NoNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief "In" conversion normalization function object.
 */
template <class ValueTypeT>
struct InNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief "Out" conversion normalization function object.
 */
template <class ValueTypeT>
struct OutNormalizationFunc
{
    typedef ValueTypeT ValueType;

    static inline ValueType
    apply(const ValueType& src,
          const Real64     scale = 1, const Real64 offset = 0);
};

/*! \brief Function object for accessing an element of a vector with Fixed32
    elements.
 */
template <class ValueTypeT>
struct Fixed32VectorElementAccessFunc
{
    typedef          ValueTypeT           ValueType;
    typedef          Int32                ElementType;

    static inline ElementType
    apply(const ValueType& src, const UInt32 index);
};

/*! \brief Function object for accessing an element of a vector.
 */
template <class ValueTypeT>
struct VectorElementAccessFunc
{
    typedef          ValueTypeT           ValueType;
    typedef typename ValueType::ValueType ElementType;

    static inline ElementType
    apply(const ValueType& src, const UInt32 index);
};

/*! \brief Partial specialization for vectors with Fixed32 elements,
    implemented via inheritance.
 */
template <class StorageInterfaceT>
struct VectorElementAccessFunc<VectorInterface<Fixed32,
                                               StorageInterfaceT>
                               >
    : public Fixed32VectorElementAccessFunc<VectorInterface<Fixed32,
                                                            StorageInterfaceT>
                                            >
{
};

/*! \brief Partial specialization for points with Fixed32 elements,
    implemented via inheritance.
 */
template <class StorageInterfaceT>
struct VectorElementAccessFunc<PointInterface<Fixed32, StorageInterfaceT> >
    : public Fixed32VectorElementAccessFunc<PointInterface<Fixed32,
                                                           StorageInterfaceT>
                                            >
{
};

/*! \brief Specialization for Color3fx, implemented via inheritance.
 */
template <>
struct VectorElementAccessFunc<Color3fx>
    : public Fixed32VectorElementAccessFunc<Color3fx>
{
};

/*! \brief Specialization for Color4fx, implemented via inheritance.
 */
template <>
struct VectorElementAccessFunc<Color4fx>
    : public Fixed32VectorElementAccessFunc<Color4fx>
{
};

/*! \brief Main conversion function.
 */
template <class                  DestTypeT,
          class                  SourceTypeT,
          template <class> class NormalizeFuncT,
          template <class> class ElementAccessFuncT>
struct GeoConvertFunc
{
    typedef          DestTypeT                         DestType;
    typedef          SourceTypeT                       SourceType;

    typedef typename DestType::ValueType               DestElementType;
    typedef typename SourceType::ValueType             SourceElementType;

    typedef          NormalizeFuncT<SourceElementType> NormFunc;
    typedef          ElementAccessFuncT<SourceType>    AccessFunc;

    static inline void
    convert(      DestType& dest,      const SourceType& src,
            const Real64    scale = 1, const Real64      offset = 0);
};

/*! \brief Partial specialization to optimize same type conversions without
    normalization.
 */
template <class                  ValueTypeT,
          template <class> class ElementAccessFuncT>
struct GeoConvertFunc<ValueTypeT,
                      ValueTypeT,
                      NoNormalizationFunc,
                      ElementAccessFuncT  >
{
    typedef          ValueTypeT                             DestType;
    typedef          ValueTypeT                             SourceType;

    typedef typename DestType::ValueType                    DestElementType;
    typedef typename SourceType::ValueType                  SourceElementType;

    typedef          NoNormalizationFunc<SourceElementType> NormFunc;
    typedef          ElementAccessFuncT<SourceType>         AccessFunc;

    static inline void
    convert(      DestType& dest,      const SourceType& src,
            const Real64    scale = 1, const Real64      offset = 0);
};

/*! \brief The "interface" of the implementation.
 */
template <class                  DestTypeT,
          class                  SourceTypeT,
          template <class> class NormalizeFuncT>
struct GeoConvertImpl : public GeoConvertFunc<DestTypeT,
                                              SourceTypeT,
                                              NormalizeFuncT,
                                              VectorElementAccessFunc>
{
};

} // namespace detail

OSG_END_NAMESPACE

// pull in implementation for inlining below
#include "OSGGeoVectorPropertyConversion.inl"

OSG_BEGIN_NAMESPACE

struct GeoConvert
{
    template <class StoredTypeT, class ExternalTypeT>
    inline static void
    convertIn(      StoredTypeT& dest,      const ExternalTypeT& src,
              const Real64       scale = 1, const Real64         offset = 0)
    {
        detail::GeoConvertImpl<StoredTypeT,
                               ExternalTypeT,
                               detail::NoNormalizationFunc>::convert(
            dest, src, scale, offset);
    }

    template <class ExternalTypeT, class StoredTypeT>
    inline static void
    convertOut(      ExternalTypeT& dest,      const StoredTypeT& src,
               const Real64         scale = 1, const Real64       offset = 0)
    {
        detail::GeoConvertImpl<ExternalTypeT,
                               StoredTypeT,
                               detail::NoNormalizationFunc>::convert(
            dest, src, scale, offset);
    }
};

struct GeoConvertNormalize
{
    template <class StoredTypeT, class ExternalTypeT>
    inline static void
    convertIn(      StoredTypeT& dest,      const ExternalTypeT& src,
              const Real64       scale = 1, const Real64         offset = 0)
    {
        detail::GeoConvertImpl<StoredTypeT,
                               ExternalTypeT,
                               detail::InNormalizationFunc>::convert(
            dest, src, scale, offset);
    }

    template <class ExternalTypeT, class StoredTypeT>
    inline static void
    convertOut(      ExternalTypeT& dest,      const StoredTypeT& src,
               const Real64         scale = 1, const Real64       offset = 0)
    {
        detail::GeoConvertImpl<ExternalTypeT,
                               StoredTypeT,
                               detail::OutNormalizationFunc>::convert(
            dest, src, scale, offset);
    }
};

#else

/* Helper classes for vector type conversions */

// Converter class for vector conversion
struct GeoConvert
{
    template <class ExternalType, class StoredType>
    inline static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(src[i]);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = StoredType::Null[i];
        }
    }

    template <class ExternalType, class StoredType>
    inline static void convertOut(ExternalType& dest, const StoredType& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(src[i]);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType, class StoredType>
    inline static void convertCustomOut(      ExternalType &dest,
                                        const StoredType   &src,
                                              Real64        scale = 1,
                                              Real64        offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
            {
                dest[i] =
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
            {
                dest[i] =
                    static_cast<typename ExternalType::ValueType>(
                        src[i].getValue());
            }
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = ExternalType::Null[i];
        }
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Vec4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }

    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt1fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt2fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Pnt4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Color3fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }
    template <class ExternalType>
    inline static void convertOut(ExternalType& dest, const Color4fx& src,
                                  Real64 scale = 1, Real64 offset = 0)
    {
        convertCustomOut(dest, src, scale, offset);
    }

};

struct GeoConvertNormalize
{
    template <class ExternalType, class StoredType>
    static void convertIn(StoredType& dest, const ExternalType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(ExternalType::_uiSize >= StoredType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            src[i] * scale + offset);
            for(; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename StoredType::ValueType>(
                            StoredType::Null[i] * scale + offset);
         }
    }

    template <class ExternalType, class StoredType>
    static void convertOut(ExternalType& dest, const StoredType& src,
                                 Real64 scale = 1, Real64 offset = 0)
    {
        if(StoredType::_uiSize >= ExternalType::_uiSize)
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
        }
        else
        {
            UInt32 i;
            for(i = 0; i < StoredType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (src[i] - offset) / scale);
            for(; i < ExternalType::_uiSize; ++i)
                dest[i] = static_cast<typename ExternalType::ValueType>(
                            (StoredType::Null[i] - offset) / scale);
         }
    }
};

#endif

OSG_END_NAMESPACE

#define OSGGEOVECTORPROPERTYCONVERSION_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGGEOVECTORPROPERTYCONVERSION_H_ */
