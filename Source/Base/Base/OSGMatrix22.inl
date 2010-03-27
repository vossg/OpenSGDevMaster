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

template<class FloatTypeT> inline
Matrix22<FloatTypeT>::Matrix22(FloatTypeT a11, FloatTypeT a12, FloatTypeT a21, FloatTypeT a22)
{
    _Values[0] = a11;
    _Values[1] = a12;
    _Values[2] = a21;
    _Values[3] = a22;
}

template<class FloatTypeT> inline
FloatTypeT Matrix22<FloatTypeT>::det(void) const
{
    return _Values[0]*_Values[3] - _Values[1]*_Values[2];
}

template<class FloatTypeT> inline
Matrix22<FloatTypeT> Matrix22<FloatTypeT>::inverse(void) const
{
    return Matrix22<FloatTypeT>(_Values[3], -_Values[1], -_Values[2], _Values[0]);
}

template<class FloatTypeT> inline
typename Matrix22<FloatTypeT>::VectorType Matrix22<FloatTypeT>::mult(const VectorType& src) const
{
    return VectorType(_Values[0]*src[0] + _Values[1]*src[1], _Values[2]*src[0]+_Values[3]*src[1]);
}

template<class FloatTypeT> inline
typename Matrix22<FloatTypeT>::VectorType Matrix22<FloatTypeT>::operator*(const VectorType& src) const
{
    return VectorType(_Values[0]*src[0] + _Values[1]*src[1], _Values[2]*src[0]+_Values[3]*src[1]);
}

template<class FloatTypeT> inline
typename Matrix22<FloatTypeT>::PointType Matrix22<FloatTypeT>::operator*(const PointType& src) const
{
    return PointType(_Values[0]*src[0] + _Values[1]*src[1], _Values[2]*src[0]+_Values[3]*src[1]);
}

OSG_END_NAMESPACE

