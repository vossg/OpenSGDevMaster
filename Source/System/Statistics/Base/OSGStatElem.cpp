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

#include "OSGStatElem.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StatElem
    \ingroup Statistics

  The StatElem is the abstract base class for all the data types that can be 
  recorded statistically. See \ref PageSystemStatistics for an overview of the
  statistics 
  structure.

  It mainly provides the general interfaces for accessing the statistics data 
  as a Real64 value via getValue, if possible, and in ASCII via the 
  putToString and getFromString methods. Additionally every StatElem can be 
  switched on or off,  to prevent collecting statistics that is not needed, 
  via the setOn methods. 
  Finally, ever StatElem can give information about itself in the form of a 
  OSG::StatElemDesc*. 

  /ext 

  To add a new StatElem type the given interface has to be implemented. 
  There are no restrictions as to which types are possible, as long as they 
  can be converted to and from a string. See StatIntElem for a simple example.

  /endext

 */

/*! \fn void OSG::StatElem::putToString(std::string &str, 
                                        const char *format) const
  
  The putToString method converts the value of the StatElem into a standard 
  STL string. 
  
  The conversion can be parameterized by the format string parameter. It is 
  modelled after the printf()-format string. It typically should contain a 
  single "%" value to format the contents of the StatElem.
  
 */ 

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

StatElem::StatElem(StatElemDescBase *desc) :
    _on  (true),
    _desc(desc)
{
}

StatElem::~StatElem(void)
{
}

/*-------------------------- assignment -----------------------------------*/

StatElem &StatElem::operator = (const StatElem &source)
{
    if (this == &source)
        return *this;
        
    // copy 

	_on   = source._on;
	_desc = source._desc;
	
  	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*! Comparison. This does not compare the actual values of the StatElem, as
    that may not be possible for all types. 
*/

bool StatElem::operator < (const StatElem &other) const
{
    return this < &other;
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
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGSTATELEM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATELEM_INLINE_CVSID;
}
