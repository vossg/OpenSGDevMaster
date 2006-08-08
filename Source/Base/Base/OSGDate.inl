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

#ifndef _OSGDATE_INL_
#define _OSGDATE_INL_
#ifdef  __sgi
#pragma  once
#endif

OSG_BEGIN_NAMESPACE

inline 
void Date::setSecond(UInt32 second)
{
    _second = second;
}


inline 
UInt32 Date::getSecond(void)
{ 
    return _second;
}


inline
void Date::setMinute(UInt32 minute)
{ 
    _minute = minute;
}


inline
UInt32 Date::getMinute(void)
{ 
    return _minute;
}


inline
void Date::setHour(UInt32 hour)
{
    _hour = hour;
}


inline
UInt32 Date::getHour(void)
{
    return _hour;
}


inline 
void Date::setDay(UInt32 day)
{
    _day = day; 
}


inline 
UInt32 Date::getDay(void)
{ 
    return _day;
}



inline 
void Date::setYear(Int32 year)
{
    _year = year;
}


inline 
Int32 Date::getYear(void)
{ 
    return _year;
}
 

inline
bool Date::operator !=(const Date &other)
{
    return !(*this == other);
}

OSG_END_NAMESPACE

#endif // _OSGDATE_INL_
