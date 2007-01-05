/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

//
// Normalize funcs
//

template <class ValueTypeT>
inline typename detail::NoNormalizationFunc<ValueTypeT>::ValueType
detail::NoNormalizationFunc<ValueTypeT>::apply(
    const ValueType& src, const Real64, const Real64)
{
    return src;
}

template <class ValueTypeT>
inline typename detail::InNormalizationFunc<ValueTypeT>::ValueType
detail::InNormalizationFunc<ValueTypeT>::apply(
    const ValueType& src, const Real64 scale, const Real64 offset)
{
    return static_cast<ValueType>((scale * src) + offset);
}

template <class ValueTypeT>
inline typename detail::OutNormalizationFunc<ValueTypeT>::ValueType
detail::OutNormalizationFunc<ValueTypeT>::apply(
    const ValueType& src, const Real64 scale, const Real64 offset)
{
    return static_cast<ValueType>((src - offset) / scale);
}

//
// Access funcs
//

template <class ValueTypeT>
inline typename detail::VectorElementAccessFunc<ValueTypeT>::ElementType
detail::VectorElementAccessFunc<ValueTypeT>::apply(
    const ValueType& src, const UInt32 index)
{
    return src[index];
}

template <class ValueTypeT>
inline typename detail::Fixed32VectorElementAccessFunc<ValueTypeT>::ElementType
detail::Fixed32VectorElementAccessFunc<ValueTypeT>::apply(
    const ValueType& src, const UInt32 index)
{
    return src[index].getValue();
}

//
// Convert funcs
//

template <class DestTypeT,
          class SourceTypeT,
          template <class> class NormalizeFuncT,
          template <class> class ElementAccessFuncT>
inline void
detail::GeoConvertFunc<DestTypeT,
                       SourceTypeT,
                       NormalizeFuncT,
                       ElementAccessFuncT>::convert(
          DestType& dest,  const SourceType& src,
    const Real64    scale, const Real64      offset)
{
    if(SourceType::_uiSize >= DestType::_uiSize)
    {
        UInt32 i;
        for(i = 0; i < DestType::_uiSize; ++i)
        {
            dest[i] = static_cast<DestElementType>(
                NormFunc::apply(AccessFunc::apply(src, i), scale, offset));
        }
    }
    else
    {
        UInt32 i;
        for(i = 0; i < SourceType::_uiSize; ++i)
        {
            dest[i] = static_cast<DestElementType>(
                NormFunc::apply(AccessFunc::apply(src, i), scale, offset));
        }

        for(; i < DestType::_uiSize; ++i)
        {
            dest[i] = static_cast<DestElementType>(
                NormFunc::apply(
                    AccessFunc::apply(SourceType::Null, i), scale, offset));
        }
    }
}

template <class                  ValueTypeT,
          template <class> class ElementAccessFuncT>
inline void
detail::GeoConvertFunc<ValueTypeT,
                       ValueTypeT,
                       detail::NoNormalizationFunc,
                       ElementAccessFuncT          >::convert(
          DestType& dest,  const SourceType& src,
    const Real64    scale, const Real64      offset)
{
    dest = src;
}

OSG_END_NAMESPACE

#define OSGGEOVECTORPROPERTYCONVERSION_INLINE_CVSID "@(#)$Id$"
