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

#include "OSGStatRealElem.h"
#include "OSGSysFieldTraits.h"

#include <boost/format.hpp>

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatRealElem

    The StatIntElem keeps an Real32 value, see \ref PageSystemStatistics for
    details. 
 */

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatRealElem::StatRealElem(StatElemDescBase *desc) :
    StatElem(desc), 
    _value  (0.f )
{
}

StatElem *StatRealElem::create(StatElemDescBase *desc)
{
    return new StatRealElem(desc);
}

StatRealElem::~StatRealElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatRealElem::putToString(
    std::string &str, const std::string &format) const
{
    if(format.empty())
    {
        FieldTraits<Real32>::putToString(_value, str);
     }
    else
    {
        std::string            formatCopy = format;
        std::string::size_type pos        = formatCopy.find("%");
        Real32                 val        = _value;
        
        if(pos != std::string::npos)
        {
            if((pos = formatCopy.find("%per")) != std::string::npos)
            {
                formatCopy.replace(pos, 4, "%.2f");
                val *= 100.f;
            }
        }
        
        boost::format fmt(formatCopy);
        
        fmt % val;
        
        str = fmt.str();
    }
}

bool StatRealElem::getFromCString(const Char8 *&inVal)
{
    return FieldTraits<Real32>::getFromCString(_value, inVal);
}

Real64 StatRealElem::getValue(void) const
{
    return static_cast<Real64>(get());
}


void StatRealElem::reset(void) 
{ 
    _value = 0.f; 
}

/*-------------------------- assignment -----------------------------------*/

StatRealElem& StatRealElem::operator = (const StatRealElem &source)
{
    if (this == &source)
        return *this;

    set(source.get());
    
    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatRealElem::operator < (const StatRealElem &other) const
{
    return this->get() < other.get();
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatRealElem::clone(void) const
{
    StatRealElem *e = new StatRealElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatRealElem::operator += (const StatElem &other)
{
    const StatRealElem *o = dynamic_cast<const StatRealElem *>(&other);
    
    _value += o->_value;
    
    return *this;
}
