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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGSysFieldTraits.h"

#include "OSGStatTimeStampElem.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatTimeStampElem
    \ingroup GrpSystemStatistics

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

void StatTimeStampElem::putToString(std::string &str, const char *format) const
{
    double time = getTimeStampMsecs(_time) / 1000.;
    
    if(!format)
    {
        FieldTraits<TimeStamp>::putToString(_time, str);
    }
    else
    {
        const char *proc = strchr(format,'%');        
              char *temp = new char [strlen(format) + 60];

        if(proc)
        {
            if(! strncmp(proc, "%ms", 3))
            {
                std::string fcopy(format);
                fcopy.insert((proc - format) + 1,".2f ");
                sprintf(temp, fcopy.c_str(), time*1000.);
            }
            else if(! strncmp(proc, "%r", 2))
            {
                std::string fcopy(format);
                fcopy.erase((proc - format) + 1, 1);
                sprintf(temp, fcopy.c_str(), 1./time);
            }
            else
            {
                sprintf(temp, format, time);
            }
           
        }
        else
        {
            sprintf(temp, format, time);
        }
        
        str = temp;
        delete [] temp;
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


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSTATTIMESTAMPELEM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATTIMESTAMPELEM_INLINE_CVSID;
}
