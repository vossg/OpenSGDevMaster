/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
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

OSG_BEGIN_NAMESPACE

inline Int32
FastTriangleIterator::getIndex(Int32 which) const
{
    return Inherited::getIndex(_triPntIndex[which]);
}

inline Int32
FastTriangleIterator::getIndex(void) const
{
    return _triIndex;
}

inline Int32
FastTriangleIterator::getPropertyIndex(UInt16 att, Int32 which) const
{
    return Inherited::getPropertyIndex(att, _triPntIndex[which]);
}

template <class ReturnT>
inline ReturnT
FastTriangleIterator::getPropertyValue(UInt16 att, Int32 which) const
{
    Int32 ind = getPropertyIndex(att, which);

    return _props[att]->getValue<ReturnT>(ind);
}

inline FastTriangleIterator
FastTriangleIterator::operator++(int)
{
    FastTriangleIterator returnValue(*this);

    ++(*this);

    return returnValue;
}

inline bool
FastTriangleIterator::operator<(const FastTriangleIterator &lhs) const
{
    return (*static_cast<const Inherited *>(this) <  lhs) ||
         ( (*static_cast<const Inherited *>(this) == lhs)       &&
           _triIndex                              <  lhs._triIndex);
}

inline bool
FastTriangleIterator::operator==(const FastTriangleIterator &lhs) const
{
    if(isAtEnd() && lhs.isAtEnd())
        return true;

    if(isAtEnd() || lhs.isAtEnd())
        return false;

    return (*static_cast<const Inherited *>(this) == lhs          ) &&
           (_triIndex                             == lhs._triIndex);
}

inline bool
FastTriangleIterator::operator!=(const FastTriangleIterator &lhs) const
{
    return !(*this == lhs);
}

OSG_END_NAMESPACE
