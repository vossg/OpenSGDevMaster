/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

/*-------------------------- constructor ----------------------------------*/

inline
Fixed32::Fixed32(void) :
    _value(0)
{
}

inline
Fixed32::Fixed32(const Real32 source) :
    _value(Int32(source * 65536.0f))
{
    
}

inline
Fixed32::Fixed32(const UInt32 source) :
    _value(source << 16)
{
}

inline
Fixed32::Fixed32(const Int32 source) :
    _value(source)
{
}

inline
Fixed32::Fixed32(const Fixed32 &source) :
    _value(source._value)
{
}

inline
Fixed32::~Fixed32(void)
{
}

/*------------------------------ feature ----------------------------------*/

inline
Fixed32 Fixed32::operator - () const
{
    Fixed32 returnValue;

    returnValue._value = -_value;

    return returnValue;
}

inline
void Fixed32::setFixedValue(Int32 src)
{
    _value = src;
}

/*-------------------------- extending ------------------------------------*/

inline
Fixed32 &Fixed32::operator = (const Fixed32 rhs)
{
    _value = rhs._value;

    return *this;
}

inline
Fixed32 &Fixed32::operator +=(const Fixed32 rhs)
{
    _value += rhs._value;

    return *this;
}

inline
Fixed32 &Fixed32::operator -=(const Fixed32  rhs)
{
    _value -= rhs._value;

    return *this;
}

inline
Fixed32 &Fixed32::operator *=(const Fixed32 rhs)
{
    _value = Int32((Int64(_value) * Int64(rhs._value)) >> 16);

    return *this;
}

inline
Fixed32 &Fixed32::operator /=(const Fixed32 rhs)
{
    _value = Int32((Int64(_value) << 16) / rhs._value);

    return *this;
}

inline
Fixed32  Fixed32::operator + (const Fixed32 rhs) const
{
    Fixed32 returnValue(_value);

    returnValue._value += rhs._value;

    return returnValue;
}


inline
Fixed32  Fixed32::operator - (const Fixed32 rhs) const
{
    Fixed32 returnValue(_value);

    returnValue._value -= rhs._value;

    return returnValue;
}

inline
Fixed32  Fixed32::operator * (const Fixed32 rhs) const
{
    Fixed32 returnValue;

    returnValue._value = Int32((Int64 (_value) * 
                                Int64 (rhs._value)) >> 16);

    return returnValue;
}

inline
Fixed32  Fixed32::operator / (const Fixed32 rhs) const
{
    Fixed32 returnValue;

    returnValue._value = Int32((Int64(_value) << 16) / rhs._value);

    return returnValue;
}

inline
bool Fixed32::operator ==(const Fixed32 rhs) const
{
    return _value == rhs._value;
}

inline
bool Fixed32::operator !=(const Fixed32 rhs) const
{
    return _value != rhs._value;
}

inline
bool Fixed32::operator < (const Fixed32 rhs) const
{
    return _value < rhs._value;
}

inline
bool Fixed32::operator > (const Fixed32 rhs) const
{
    return _value > rhs._value;
}


inline
bool Fixed32::operator <=(const Fixed32 rhs) const
{
    return _value <= rhs._value;
}


inline
bool Fixed32::operator >=(const Fixed32 rhs) const
{
    return _value >= rhs._value;
}

inline
Int32 Fixed32::getValue(void) const
{
    return _value;
}

inline
void Fixed32::setValue(Int32 iVal)
{
    _value = iVal;
}

inline
Fixed32 Fixed32::abs(Fixed32 rhs)
{
    Fixed32 returnValue;
	
	returnValue._value = (rhs._value > 0 ? rhs._value : - rhs._value);

    return returnValue;
}

inline
Real32 Fixed32::toFloat(Fixed32 rhs)
{
    return Real32(rhs._value) / Real32(1 << 16);
}

inline
Fixed32 Fixed32::sqrt(Fixed32 rhs)
{
    Fixed32 returnValue((Real32(std::sqrt(Fixed32::toFloat(rhs)))));

    return returnValue;
}

inline
Fixed32 Fixed32::sin(Fixed32 rhs)
{
    Fixed32 returnValue((Real32(std::sin(Fixed32::toFloat(rhs)))));

    return returnValue;
}

inline
Fixed32 Fixed32::cos(Fixed32 rhs)
{
    Fixed32 returnValue((Real32(std::cos(Fixed32::toFloat(rhs)))));

    return returnValue;
}

inline
Fixed32 Fixed32::tan(Fixed32 rhs)
{
    Fixed32 returnValue((Real32(std::tan(Fixed32::toFloat(rhs)))));

    return returnValue;
}

/*-------------------------- intersection ---------------------------------*/

inline
Fixed32 operator -(const Real32 lhs, const Fixed32 rhs)
{
    Fixed32 returnValue(lhs);

    returnValue -= rhs; 

    return returnValue;
}

inline
Fixed32 operator /(const Real32 lhs, const Fixed32 rhs)
{
    Fixed32 returnValue(lhs);

    returnValue /= rhs;

    return returnValue;
}

inline
Fixed32 operator *(const Real32 lhs, const Fixed32 rhs)
{
    Fixed32 returnValue(lhs);

    returnValue *= rhs;

    return returnValue;
}

inline
std::ostream &operator << (std::ostream &os, Fixed32 OSG_CHECK_ARG(fVal))
{
    return os;
}

inline
std::istream &operator >> (std::istream &is, Fixed32 &OSG_CHECK_ARG(fVal))
{
    return is;
}

/*-------------------------- operators ------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

