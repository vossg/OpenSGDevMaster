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


//---------------------------------------------------------
//  Includes
//---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <fstream>

#include "OSGConfig.h"

#include <OSGLog.h>

#include "OSGSceneFileType.h"
#include "OSGSceneFileHandler.h"
#include "OSGBaseInitFunctions.h"

OSG_USING_NAMESPACE


/*! \class OSG::SceneFileType
    \ingroup GrpSystemFileIO

 */

//---------------------------------------------------------

SceneFileType::SceneFileType(const Char8  *suffixArray[],
                                   UInt16  suffixByteCount,
                                   bool    override,
                                   UInt32  overridePriority,
                                   UInt32  flags) :
    _suffixList      (                ),
    _override        (override        ),
    _overridePriority(overridePriority),
    _flags           (flags           ),
    _options         (                )
{
    FINFO(( "Init %s Scene File Type %d\n", suffixArray[0], this ));

    int count = (suffixByteCount / sizeof(const Char8 *)), i = 0;

    std::list<IDString>::iterator sI;

    _suffixList.resize(count);

    for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
    {
        sI->set(suffixArray[i++]);
    }

    SceneFileHandler::the()->addSceneFileType(*this);
}

//---------------------------------------------------------

SceneFileType::SceneFileType(const SceneFileType &obj) :
    _suffixList      (obj._suffixList      ),
    _override        (obj._override        ),
    _overridePriority(obj._overridePriority),
    _flags           (obj._flags),
    _options         (obj._options)
{
    SWARNING << "In SceneFileType copy constructor" << std::endl;
}

//---------------------------------------------------------
SceneFileType::~SceneFileType(void)
{
    if(GlobalSystemState != Shutdown)
        SceneFileHandler::the()->subSceneFileType(*this);
}

//---------------------------------------------------------

void SceneFileType::setOptions(const Char8 *options)
{
    _options = options;
}

//---------------------------------------------------------
void SceneFileType::print(void)
{
    std::list<IDString>::iterator sI;

    osgLog() << getName();

    if (_suffixList.empty())
    {
        osgLog() << "NONE";
    }
    else
    {
        for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
        {
            osgLog().stream(OSG::LOG_DEBUG) << sI->str() << " ";
        }
    }
    osgLog() << std::endl;
}

//---------------------------------------------------------

std::list<IDString> &SceneFileType::suffixList(void)
{
    return _suffixList;
}

//---------------------------------------------------------

bool SceneFileType::doOverride(void)
{
    return _override;
}

//---------------------------------------------------------

UInt32 SceneFileType::getOverridePriority(void)
{
    return _overridePriority;
}

//---------------------------------------------------------

UInt32 SceneFileType::getFlags(void)
{
    return _flags;
}

//---------------------------------------------------------

const Char8 *SceneFileType::getOptions(void)
{
    return _options.c_str();
}

//---------------------------------------------------------

NodePtr SceneFileType::read(
          std::istream &OSG_CHECK_ARG(is                 ),
    const Char8        *OSG_CHECK_ARG(fileNameOrExtension)) const
{
    FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));
    return NullFC;
}

#ifndef OSG_DISABLE_DEPRECATED
NodePtr SceneFileType::readFile(const Char8 * OSG_CHECK_ARG(fileName)) const
{
    FWARNING (("FILE INTERFACE NOT IMPLEMENTED!\n"));
    return NullFC;
}
#endif

bool SceneFileType::write(
    const NodePtr      &OSG_CHECK_ARG(node               ),
          std::ostream &OSG_CHECK_ARG(os                 ),
    const Char8        *OSG_CHECK_ARG(fileNameOrExtension)) const
{
    FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));
    return false;
}

#ifndef OSG_DISABLE_DEPRECATED
bool SceneFileType::writeFile(const NodePtr &OSG_CHECK_ARG(node    ),
                              const Char8   *OSG_CHECK_ARG(fileName)) const
{
    FWARNING (("FILE INTERFACE NOT IMPLEMENTED!\n"));
    return false;
}
#endif

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
    static Char8 cvsid_hpp[] = OSGSCENEFILETYPE_HEADER_CVSID;
}
