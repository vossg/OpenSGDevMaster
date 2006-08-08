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

#include <OSGConfig.h>

#include "OSGStatStringElem.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StatStringElem
    \ingroup GrpSystemStatistics

    The StatIntElem keeps a std::string for messages, states or status
    information, see \ref PageSystemStatistics for details. 
*/

/***************************************************************************\
 *                         Instance methods                                *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

StatStringElem::StatStringElem(StatElemDescBase *desc) :
    StatElem(desc), 
    _value  (    )
{
}

StatElem *StatStringElem::create(StatElemDescBase *desc)
{
    return new StatStringElem(desc);
}

StatStringElem::~StatStringElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatStringElem::putToString(std::string &str, const Char8 *format) const
{
    if(!format)
    {
        str = _value;
    }
    else
    {
        Char8 *temp = new Char8[strlen(format) + _value.size() + 10];
        sprintf(temp, format, _value.c_str());
        str = temp;
        delete [] temp;
    }
}

bool StatStringElem::getFromCString(const Char8 *&inVal)
{
    if(inVal != 0)
    {
        _value = inVal;
    }

    return true;
}

Real64 StatStringElem::getValue(void) const
{
    return 0;
}

void StatStringElem::reset(void) 
{ 
    _value.resize(0); 
}


/*-------------------------- assignment -----------------------------------*/

StatStringElem& StatStringElem::operator = (const StatStringElem &source)
{
    if (this == &source)
        return *this;

    set(source.get());

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool StatStringElem::operator < (const StatStringElem &other) const
{
    return this < &other;
}

/*--------------------------- creation ------------------------------------*/

StatElem *StatStringElem::clone(void) const
{
    StatStringElem *e = new StatStringElem(getDesc());
    
    *e = *this;
    
    return e;
}

/*--------------------------- operators ------------------------------------*/

StatElem &StatStringElem::operator += (const StatElem &other)
{
    const StatStringElem *o = dynamic_cast<const StatStringElem *>(&other);
    
    _value += " " + o->_value;
    
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
    static Char8 cvsid_hpp[] = OSGSTATSTRINGELEM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATSTRINGELEM_INLINE_CVSID;
}
