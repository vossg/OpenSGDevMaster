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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>
#include <OSGNode.h>
#include <OSGGeometry.h>
#include <OSGGeoProperty.h>
#include <OSGSimpleMaterial.h>

#include "OSGNFIOSceneFileType.h"
#include "OSGNFIOBase.h"

OSG_USING_NAMESPACE

/*! \class OSG::NFIOSceneFileType
    \ingroup GrpSystemFileIO

    Binary file type
 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning(disable : 383)
#endif

/*-------------------------------------------------------------------------*/
/*                            static get                                   */

/*! get instance
 */
NFIOSceneFileType &NFIOSceneFileType::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            destructor                                   */

/*! destructor
 */
NFIOSceneFileType::~NFIOSceneFileType(void)
{
    return;
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            read                                         */

/*! read filename
 */
NodePtr NFIOSceneFileType::read(std::istream &is, const Char8 *) const
{
    return NFIOBase::read(is, _options);
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            write                                        */

/*! write node and its subtree to the given fileName
 */
bool NFIOSceneFileType::write(const NodePtr &node,
                             std::ostream &os, const Char8 *) const
{
    return NFIOBase::write(node, os, _options);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! constructor
 */
NFIOSceneFileType::NFIOSceneFileType(const Char8 *suffixArray[],
                                     UInt16 suffixByteCount, bool override,
                                     UInt32 overridePriority,
                                     UInt32 flags) :
        SceneFileType(suffixArray, suffixByteCount, override,
                      overridePriority, flags)
{
}

/*! copy constructor
 */
NFIOSceneFileType::NFIOSceneFileType(const NFIOSceneFileType &obj) :
    SceneFileType(obj)
{
    return;
}

/*! get name
 */
const Char8 *NFIOSceneFileType::getName(void) const
{
    return "OSG Binary";
}

/*-------------------------------------------------------------------------*/
/*                              static elements                            */

const Char8 *    NFIOSceneFileType::_suffixA[] = { "osb" };
NFIOSceneFileType NFIOSceneFileType:: _the(_suffixA,
                                         sizeof(_suffixA), false, 10,
                                         OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED);

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8    cvsid_cpp[] = "@(#)$Id: OSGNFIOSceneFileType.cpp,v 1.1.2.1 2005/08/16 16:18:10 a-m-z Exp $";
    static Char8    cvsid_hpp[] = OSGBINSCENEFILETYPE_HEADER_CVSID;
}
