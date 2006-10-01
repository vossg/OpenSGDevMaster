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
 *                                                                           *
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

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGLog.h"

#include "OSGFieldContainerPtr.h"
#include "OSGGeometry.h"
#include "OSGDrawEnv.h"

#include "OSGMaterial.h"

#include "OSGGeoIgnorePumpGroup.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/* \class OSG::GeoIgnorePumpGroup
   \ingroup GrpSystemNodeCoresDrawablesGeometry
    
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

GeoIgnorePumpGroup::GeoIgnorePumpGroup(void)
{
}

GeoIgnorePumpGroup::~GeoIgnorePumpGroup(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


void GeoIgnorePumpGroup::masterGeoPump(DrawEnv  *pEnv,
                                       Geometry *geo)
{
}


void GeoIgnorePumpGroup::masterPartialGeoPump(DrawEnv  *pEnv,
                                              Geometry *geo,
                                              UInt32    primtype, 
                                              UInt32    firstvert, 
                                              UInt32    nvert   )
{
}

void GeoIgnorePumpGroup::masterExtIndexGeoPump(DrawEnv  *pEnv,
                                               Geometry *geo,
                                               UInt32   *indices, 
                                               UInt32    nvert)
{
}


GeoPumpGroup::GeoPump GeoIgnorePumpGroup::getGeoPump(
                    DrawEnv                 *pEnv,
                    PropertyCharacteristics  acset)
{
    return masterGeoPump;
}

GeoPumpGroup::PartialGeoPump GeoIgnorePumpGroup::getPartialGeoPump(
                    DrawEnv                 *pEnv, 
                    PropertyCharacteristics  acset)
{
    return masterPartialGeoPump;
}

GeoPumpGroup::ExtIndexGeoPump GeoIgnorePumpGroup::getExtIndexGeoPump(
                    DrawEnv                 *pEnv, 
                    PropertyCharacteristics  acset)
{
    return masterExtIndexGeoPump;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGGeoIgnorePumpGroup.cpp 106 2006-09-14 03:15:53Z dirk $";
    static Char8 cvsid_hpp       [] = OSGGEOIGNOREPUMPGROUP_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGGEOIgnorePUMPGROUP_INLINE_CVSID;
}

