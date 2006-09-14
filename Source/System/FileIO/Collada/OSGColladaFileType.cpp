/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2006 by the OpenSG Forum                   *
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

/*! \file OSGColladaFileType.cpp
    \ingroup GrpLoader
 */

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGColladaFileType.h"
#include "OSGColladaLoader.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

const Char8           *ColladaFileType::_suffixA[] = { "dae" };

      ColladaFileType  ColladaFileType::_the(_suffixA,
                                             sizeof(_suffixA), 
                                             false, 
                                             10,
                                             (OSG_READ_SUPPORTED | 
                                              OSG_WRITE_SUPPORTED));

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

ColladaFileType::ColladaFileType(const Char8  *suffixArray[],
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
}

ColladaFileType::~ColladaFileType(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

const Char8 *ColladaFileType::getName(void) const
{
    return "Collada SCENE";
}


NodePtr ColladaFileType::read(      std::istream &is,
                              const Char8        *fileNameOrExtension) const
{
    NodePtr returnValue = NullFC;

    ColladaLoader *pLoader = new ColladaLoader;

    returnValue = pLoader->read(is, fileNameOrExtension);

    delete pLoader;

    return returnValue;
}


bool ColladaFileType::write(const NodePtr      &node, 
                                  std::ostream &os,
                            const Char8        *fileNameOrExtension) const
{
    return true;
}



/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGCOLLADAFILETYPE_HEADER_CVSID;
}

#endif
