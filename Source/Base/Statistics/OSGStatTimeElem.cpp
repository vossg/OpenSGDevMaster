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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGStatTimeElem.h"
#include "OSGBaseFieldTraits.h"

#include <boost/format.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatTimeElem

    The StatIntElem keeps a OSG::Time value for time measurements, 
    see \ref PageSystemStatistics for details. 
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatTimeElem::StatTimeElem(StatElemDescBase *desc) :
     StatElem(desc),
    _time    (   0)
{
}

StatElem *StatTimeElem::create(StatElemDescBase *desc)
{
    return new StatTimeElem(desc);
}


StatTimeElem::~StatTimeElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatTimeElem::putToString(
    std::string &str, const std::string &format) const
{
    if(format.empty())
    {
        // Confusing if %e is used.

        Char8 temp[64];

        sprintf(temp, "%f", _time);

        str.assign(temp);
    }
    else
    {
        std::string            formatCopy = format;
        std::string::size_type pos        = formatCopy.find("%");
        Time                   val        = _time;
        
        if(pos != std::string::npos)
        {
            if((pos = formatCopy.find("%ms")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                val *= 1000.f;
            }
            else if((pos = formatCopy.find("%r")) != std::string::npos)
            {
                formatCopy.replace(pos, 2, "%");
                if(val <= TypeTraits<Time>::ZeroEps())
                {
                    val = 0.;
                }
                else
                {
                    val = 1. / val;
                }
            }
        }
        
        boost::format fmt(formatCopy);
        
        fmt % val;
        
        str = fmt.str();
    }
}

bool StatTimeElem::getFromCString(const Char8 *&inVal)
{
    return FieldTraits<Time, 1>::getFromCString(_time, inVal);
}

Real64 StatTimeElem::getValue(void) const
{
    return static_cast<Real64>(getTime());
}

void StatTimeElem::reset(void) 
{ 
    // Time elements need to be started and stopped and can't be reset
}

/*-------------------------- assignment -----------------------------------*/

StatTimeElem& StatTimeElem::operator = (const StatTimeElem &source)
{
    if (this == &source)
        return *this;

    _time = source._time;
    
    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatTimeElem::operator < (const StatTimeElem &other) const
{
    return _time < other._time;
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatTimeElem::clone(void) const
{
    StatTimeElem *e = new StatTimeElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatTimeElem::operator += (const StatElem &other)
{
    const StatTimeElem *o = dynamic_cast<const StatTimeElem *>(&other);
    
    _time += o->_time;
    
    return *this;
}

