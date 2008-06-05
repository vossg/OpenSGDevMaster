/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

/*! Helper struct for writing a vector-like type to a stream.
 */
template <class  VecTypeT,
          class  ValueTypeT,
          UInt32 SizeI      >
inline void VecToStreamWriter<VecTypeT, ValueTypeT, SizeI>::apply(
    std::ostream &os, const VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
            os << ", ";
    
        os << vec[i];
    }
}

// Partial specialization to prevent output as ASCII character
template <class  VecTypeT,
          UInt32 SizeI    >
inline void VecToStreamWriter<VecTypeT, Int8, SizeI>::apply(
    std::ostream &os, const VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
            os << ", ";
    
        os << static_cast<Int16>(vec[i]);
    }
}

// Partial specialization to prevent output as ASCII character
template <class  VecTypeT,
          UInt32 SizeI    >
inline void VecToStreamWriter<VecTypeT, UInt8, SizeI>::apply(
    std::ostream &os, const VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
            os << ", ";
    
        os << static_cast<UInt16>(vec[i]);
    }
}


/*! Helper struct for reading a vector-like type from a stream.
 */
template <class  VecTypeT,
          class  ValueTypeT,
          UInt32 SizeI      >
inline void VecFromStreamReader<VecTypeT, ValueTypeT, SizeI>::apply(
    std::istream &is, VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
        {
            while(is.peek() == ' ' || is.peek() == ',')
                is.ignore();
        }
    
        is >> vec[i];
    }
}

// Partial specialization to prevent input as ASCII character
template <class  VecTypeT,
          UInt32 SizeI    >
inline void VecFromStreamReader<VecTypeT, Int8, SizeI>::apply(
    std::istream &is, VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
        {
            while(is.peek() == ' ' || is.peek() == ',')
                is.ignore();
        }
    
        Int16 temp;
        
        is >> temp;
        vec[i] = static_cast<Int8>(temp);
    }
}

// Partial specialization to prevent input as ASCII character
template <class  VecTypeT,
          UInt32 SizeI    >
inline void VecFromStreamReader<VecTypeT, UInt8, SizeI>::apply(
    std::istream &is, VecTypeT &vec)
{
    for(UInt32 i = 0; i < SizeI; ++i)
    {
        if(i != 0)
        {
            while(is.peek() == ' ' || is.peek() == ',')
                is.ignore();
        }
    
        UInt16 temp;
        
        is >> temp;
        vec[i] = static_cast<UInt8>(temp);
    }
}

OSG_END_NAMESPACE
