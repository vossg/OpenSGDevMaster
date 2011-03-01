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

#include "OSGStatIntElem.h"

#include <boost/format.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatIntElem

    The StatIntElem keeps an Int32 counter, see \ref PageSystemStatistics for
    details. 
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatIntElem::StatIntElem(StatElemDescBase *desc) :
    StatElem(desc), 
    _value  (   0)
{
}

StatElem *StatIntElem::create(StatElemDescBase *desc)
{
    return new StatIntElem(desc);
}

StatIntElem::~StatIntElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatIntElem::putToString(
    std::string &str, const std::string &format) const
{
    if(format.empty())
    {
        FieldTraits<Int32>::putToString(_value, str);
    }
    else
    {
        std::string            formatCopy = format;
        std::string::size_type pos        = formatCopy.find("%");
        Real32                 val        = _value;
        
        if(pos != std::string::npos)
        {
            if((pos = formatCopy.find("%KB")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                val /= 1024.f;
            }
            else if((pos = formatCopy.find("%MB")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                val /= 1024.f * 1024.f;
            }
            else if((pos = formatCopy.find("%GB")) != std::string::npos)
            {
                formatCopy.replace(pos, 3, "%.2f");
                val /= 1024.f * 1024.f * 1024.f;
            }
        }
        
        boost::format fmt(formatCopy);
        
        fmt % val;
        
        str = fmt.str();
    }
}

bool StatIntElem::getFromCString(const Char8 *&inVal)
{
    return FieldTraits<Int32>::getFromCString(_value, inVal);
}

Real64 StatIntElem::getValue(void) const
{
    return static_cast<Real64>(get());
}

void StatIntElem::reset(void) 
{ 
    _value = 0; 
}

/*-------------------------- assignment -----------------------------------*/

StatIntElem& StatIntElem::operator = (const StatIntElem &source)
{
    if (this == &source)
        return *this;

    set(source.get());

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatIntElem::operator < (const StatIntElem &other) const
{
    return this->get() < other.get();
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatIntElem::clone(void) const
{
    StatIntElem *e = new StatIntElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatIntElem::operator += (const StatElem &other)
{
    const StatIntElem *o = dynamic_cast<const StatIntElem *>(&other);
    
    _value += o->_value;
    
    return *this;
}
