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

#include "OSGOpenFlightSceneFileType.h"

#include "OSGOFDatabase.h"

OSG_USING_NAMESPACE


/*! \class OSG::OSGSceneFileType
    \ingroup GrpSystemFileIO

 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8 *OpenFlightSceneFileType::_suffixA[] =  { "flt" };

OpenFlightSceneFileType OpenFlightSceneFileType::_the(_suffixA,
                                                      sizeof(_suffixA),
                                                      false,
                                                      10,
                                                      OSG_READ_SUPPORTED);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OpenFlightSceneFileType &OpenFlightSceneFileType::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

const Char8 *OpenFlightSceneFileType::getName(void) const
{
    return "OpenFlight file format";
}


NodeTransitPtr OpenFlightSceneFileType::read(      std::istream &is, 
                                             const Char8        *,
                                                   Resolver      resolver) const
{
    NodeTransitPtr returnValue(NULL);

    OFDatabase *pDB = new OFDatabase;

    bool rc = pDB->read(is);

    if(rc == true)
    {
        returnValue = pDB->convert();
    }

    delete pDB;

    commitChanges();

    return returnValue;
}


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Constructor
 */

OpenFlightSceneFileType::OpenFlightSceneFileType(const char   *suffixArray[],
                                                 UInt16  suffixByteCount,
                                                 bool    override,
                                                 UInt32  overridePriority,
                                                 UInt32  flags) :
     Inherited(suffixArray,
               suffixByteCount,
               override,
               overridePriority,
               flags)
{
    return;
}


/** \brief Destructor
 */

OpenFlightSceneFileType::~OpenFlightSceneFileType(void)
{
}
