/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGFILESYSTEM_H_
#define _OSGFILESYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseFunctions.h"

#ifndef OSG_WINCE
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef __sgi
#include <sys/fs/efs_ino.h>
#endif

#ifndef WIN32
#include <fnmatch.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#else
#include <windows.h>
#ifndef OSG_WINCE
#include <direct.h>
#endif
#include <vector>
#endif

#include <string>

OSG_BEGIN_NAMESPACE

/*! File AccessFlags
    \ingroup GrpBaseBaseFileSystem
 */

namespace AccessFlags
{
    /*! \name AccessFlags              */
    /*! \ingroup GrpBaseBaseFileSystem */
    /*! @{                             */
    
    const UInt32 None        = 0x00;
    const UInt32 IsReadable  = 0x01;
    const UInt32 IsWriteable = 0x02;

    /*! @}                             */
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace File
{
    static bool tstAttr(const Char8  *szFilename,
                              UInt32  uiAccessFlags);
}

namespace Directory
{
    static bool                  tstAttr   (const Char8  *szDirname,
                                                  UInt32  uiAccessFlags);

#ifndef OSG_WINCE
    static Char8                *getCurrent(void);

    static bool                  setCurrent(const Char8 *szDirname,
                                            const Char8 *szPattern);
#endif

    static std::vector<Char8 *> *getEntries(const Char8 *szDirname);
}

namespace Path
{
    static void fixWinNetworkPath(std::string &path);
}

#endif

OSG_END_NAMESPACE

#include "OSGFileSystem.inl"

#define OSGFILESYSTEM_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFILESYSTEM_H_ */




