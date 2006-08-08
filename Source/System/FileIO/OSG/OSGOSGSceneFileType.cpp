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

#include "OSGOSGSceneFileType.h"

#ifdef OSG_HAVE_OSGWRITER // CHECK
#include "OSGOSGWriter.h"
#endif

#include "OSGOSGLoader.h"

OSG_USING_NAMESPACE


/*! \class osg::OSGSceneFileType
    \ingroup GrpSystemFileIO

 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8 *OSGSceneFileType::_suffixA[] =  { "osg" };

OSGSceneFileType OSGSceneFileType::_the(_suffixA,
                                        sizeof(_suffixA),
                                        false,
                                        10,
                                        OSG_READ_SUPPORTED | 
                                        OSG_WRITE_SUPPORTED);

OSGLoader *OSGSceneFileType::_pFile = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSGSceneFileType &OSGSceneFileType::the(void)
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

const Char8 *OSGSceneFileType::getName(void) const
{
    return "OSG GEOMETRY";
}


NodePtr OSGSceneFileType::read(std::istream &is, const Char8 *) const
{
    if(_pFile == NULL)
        _pFile = new OSGLoader;

    _pFile->scanStream(is);

    return _pFile->getRootNode();
}

bool OSGSceneFileType::write(const NodePtr      &root, 
                                   std::ostream &os,
                             const Char8        *) const
{
    if(!os)
    {
        FFATAL(("Can not open output stream!\n"));
        return false;
    }

#ifdef OSG_HAVE_OSGWRITER // CHECK
    OSGWriter writer(os, 4);
    writer.write(root);
#endif

    return true;
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

OSGSceneFileType::OSGSceneFileType(const char   *suffixArray[],
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

OSGSceneFileType::~OSGSceneFileType(void)
{
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
    static Char8 cvsid_hpp[] = OSGOSGSCENEFILETYPE_HEADER_CVSID;
}
