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

inline
void OFRecord::readChar8(std::istream &is, Char8  *cVal, UInt32 iSize)
{
    is.read(cVal, iSize);
}

template<class ValueT> inline
UInt32 OFRecord::readVal(std::istream &is, ValueT &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(ValueT));

    val = osgNetToHost<ValueT>(val);

    return sizeof(ValueT);
}

template<> inline
UInt32 OFRecord::readVal<Int8>(std::istream &is, Int8 &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(Int8));

    return sizeof(Int8);
}

template<> inline
UInt32 OFRecord::readVal<UInt8>(std::istream &is, UInt8 &val)
{
    is.read(reinterpret_cast<char *>(&val), sizeof(UInt8));

    return sizeof(UInt8);
}

template <> inline
UInt32 OFRecord::readVal<Real32>(std::istream &is, Real32 &val)
{
    UInt32 v;
    is.read(reinterpret_cast<char *>(&v), sizeof(UInt32));

    val = osgNetToHostFP(v);

    return sizeof(Real32);
}

template <> inline
UInt32 OFRecord::readVal<Real64>(std::istream &is, Real64 &val)
{
    UInt64 v;
    is.read(reinterpret_cast<char *>(&v), sizeof(UInt64));

    val = osgNetToHostFP(v);

    return sizeof(Real64);
}

OSG_END_NAMESPACE
