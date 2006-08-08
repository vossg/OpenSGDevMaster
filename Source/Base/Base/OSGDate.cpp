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

#include <iostream>
#include <iomanip>

#include <time.h>

#include "OSGDate.h"

OSG_USING_NAMESPACE


Date::Date(void) :
    _second(0), 
    _minute(0), 
    _hour  (0), 
    _day   (0), 
    _month (0), 
    _year  (0)
{
}


Date::Date(const Date &obj) : 
    _second(obj._second), 
    _minute(obj._minute), 
    _hour  (obj._hour  ),
    _day   (obj._day   ), 
    _month (obj._month ), 
    _year  (obj._year  )
{
}


Date::~Date(void)
{
}


void Date::setSystemDate(void)
{
           time_t  clock;
    struct tm     *tm_time;

    time(&clock);

    tm_time = localtime(&clock);

    _second = tm_time->tm_sec;
    _minute = tm_time->tm_min;
    _hour   = tm_time->tm_hour;
    _day    = tm_time->tm_mday;
    _month  = tm_time->tm_mon + 1;
    _year   = tm_time->tm_year + 1900;
}


void Date::set(const Char8 *stringP)
{
    if(stringP != NULL&& *stringP != '\0')
    {
//        istrstream is(string);
        // is >> *this;
    }
}


bool Date::isLeapYear(void)
{
    if(_year & 3)
    {
        return false;
    }

    if((_year % 100) || !(_year % 400))
    {
        return true;
    }

    return false;
}


bool Date::valid(void)
{
    static const UInt32 daysPerMonth[12] =
    { 
        31, 28, 31, 30, 31, 30, 30, 31, 30, 31, 30, 31 
    };

    if((_hour > 23) || (_minute > 59) || (_second > 59))
    {
        return false;
    }

    if((_month < 1) || (_day < 1) || (_month > 12))
    {
        return false;
    }

    if(_day <= daysPerMonth[_month - 1])
    {
        return true;
    }

    if((_month == 2) && (_day == 29))
    {
        return isLeapYear();
    }

    return false;
}


void Date::set(UInt32 day,  
               UInt32 month,  
                Int32 year,
               UInt32 hour, 
               UInt32 minute, 
               UInt32 sec   )
{
    _day    = day;
    _month  = month;
    _year   = year;
    _hour   = hour;
    _minute = minute;
    _second = sec;
}


bool Date::operator ==(const Date &other)
{
    return ((_day    == other._day   ) &&
            (_month  == other._month ) &&
            (_year   == other._year  ) &&
            (_hour   == other._hour  ) &&
            (_minute == other._minute) &&
            (_second == other._second)  );
}


bool Date::operator <(const Date &other)
{
    if(_year < other._year)
        return true;

    if(_year > other._year)
        return false;

    // _year == other._year

    if(_month < other._month)
        return true;

    if(_month > other._month)
        return false;

    // _month == other._month

    if(_day < other._day)
        return true;
    if(_day > other._day)
        return false;

    // _day == other._day

    if(_hour < other._hour)
        return true;
    if(_hour > other._hour)
        return false;

    // _hour == other._hour

    if(_minute < other._minute)
        return true;
    if(_minute > other._minute)
        return false;

    // _minute == other._minute

    if(_second < other._second)
        return true;

    return false;
}


std::ostream &OSG::operator <<(std::ostream &outStream, const Date &obj)
{
  return  outStream << std::setfill('0')
                    << std::setw(2) << obj._day    << '.'
                    << std::setw(2) << obj._month  << '.'
                    << obj._year                   << ' '
                    << std::setw(2) << obj._hour   << ':'
                    << std::setw(2) << obj._minute << ':'
                    << std::setw(2) << obj._second;
}


std::istream &OSG::operator >>(std::istream &inStream, Date &obj)
{
    Char8 c;
    
    return inStream >> obj._day  >> c >> obj._month  >> c >> obj._year
                    >> obj._hour >> c >> obj._minute >> c >> obj._second;
}

