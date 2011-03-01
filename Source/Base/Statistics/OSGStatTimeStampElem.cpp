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
#include "OSGSysFieldTraits.h"

#include "OSGStatTimeStampElem.h"

#include <boost/format.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatTimeStampElem

    The StatIntElem keeps a OSG::Time value for time measurements, 
    see \ref PageSystemStatistics for details. 
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatTimeStampElem::StatTimeStampElem(StatElemDescBase *desc) :
     Inherited(desc), 
    _time     (   0)
{
}

StatElem *StatTimeStampElem::create(StatElemDescBase *desc)
{
    return new StatTimeStampElem(desc);
}


StatTimeStampElem::~StatTimeStampElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatTimeStampElem::putToString(
    std::string &str, const std::string &format) const
{
    Real64 time = getTimeStampMsecs(_time) / 1000.;
    
    if(format.empty())
    {
        // Confusing if %e is used.

        Char8 temp[64];

        sprintf(temp, "%f", Real32(_time));

        str.assign(temp);
    }
    else
    {
        std::string            formatCopy = format;
        std::string::size_type pos        = formatCopy.find("%");
        
        if(pos != std::string::npos)
        {
            if((pos = formatCopy.find("%ms")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                time *= 1000.f;
            }
            else if((pos = formatCopy.find("%r")) != std::string::npos)
            {
                formatCopy.replace(pos, 2, "%.2f");
                time = 1.f / time;
            }
        }
        
        boost::format fmt(formatCopy);
        
        fmt % time;
        
        str = fmt.str();
    }
}

bool StatTimeStampElem::getFromCString(const Char8 *&inVal)
{
    return FieldTraits<TimeStamp>::getFromCString(_time, inVal);
}

Real64 StatTimeStampElem::getValue(void) const
{
    return static_cast<Real64>(getTime());
}

void StatTimeStampElem::reset(void) 
{ 
    // Time elements need to be started and stopped and can't be reset
}

/*-------------------------- assignment -----------------------------------*/

StatTimeStampElem& StatTimeStampElem::operator = (
    const StatTimeStampElem &source)
{
    if (this == &source)
        return *this;

    _time = source._time;
    
    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatTimeStampElem::operator < (const StatTimeStampElem &other) const
{
    return _time < other._time;
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatTimeStampElem::clone(void) const
{
    StatTimeStampElem *e = new StatTimeStampElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatTimeStampElem::operator += (const StatElem &other)
{
    const StatTimeStampElem *o = 
        dynamic_cast<const StatTimeStampElem *>(&other);
    
    _time += o->_time;
    
    return *this;
}
