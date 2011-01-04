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

#include <cstdlib>
#include <cstdio>

#include <fstream>

#include "OSGConfig.h"

#include "OSGLog.h"

#include "OSGSceneFileType.h"
#include "OSGSceneFileHandler.h"
#include "OSGBaseInitFunctions.h"

OSG_BEGIN_NAMESPACE


/*! \class SceneFileType

    Base class for all file loaders.
 */

//---------------------------------------------------------

/*! Constructor for SceneFileType.
 
    \param[in] suffixArray     Raw char buffer of supported suffix values.
    \param[in] suffixByteCount Length of suffix strings to extract.
    \param[in] override
    \param[in] overridePriority Priority of this file handler in overload
                                resolution. 
    \param[in] flags    Combination of OSG_READ_SUPPORTED and
                        OSG_WRITE_SUPPORTED to say what this handler supports.
 */

SceneFileType::SceneFileType(const Char8  *suffixArray[],
                                   UInt16  suffixByteCount,
                                   bool    override,
                                   UInt32  overridePriority,
                                   UInt32  flags           ) :
     Inherited       (flags           ),
    _suffixList      (                ),
    _override        (override        ),
    _overridePriority(overridePriority)
{
    FINFO(( "Init %s Scene File Type %p\n", suffixArray[0], this ));

    int count = (suffixByteCount / sizeof(const Char8 *)), i = 0;

    std::list<std::string>::iterator sI;

    _suffixList.resize(count);

    for(sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
    {
        sI->assign(suffixArray[i++]);
    }

	SceneFileHandler::the()->addSceneFileType(*this);
}

//---------------------------------------------------------

/*! Copy constructor
 */

SceneFileType::SceneFileType(const SceneFileType &obj) :
    Inherited        (obj                  ),
    _suffixList      (obj._suffixList      ),
    _override        (obj._override        ),
    _overridePriority(obj._overridePriority)
{
    SWARNING << "In SceneFileType copy constructor" << std::endl;
}

//---------------------------------------------------------
SceneFileType::~SceneFileType(void)
{
    if(GlobalSystemState < OSG::Shutdown)
        SceneFileHandler::the()->subSceneFileType(*this);
}

void SceneFileType::terminate(void)
{
}

//---------------------------------------------------------
/*! Print supported suffixes to osgLog. */
void SceneFileType::print(void)
{
    std::list<std::string>::iterator sI;

    osgLog() << getName();

    if (_suffixList.empty())
    {
        osgLog() << "NONE";
    }
    else
    {
        for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
        {
            osgLog().stream(OSG::LOG_DEBUG) << sI->c_str() << " ";
        }
    }
    osgLog() << std::endl;
}

//---------------------------------------------------------
/*! Return list of supported suffix strings. */
std::list<std::string> &SceneFileType::suffixList(void)
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

NodeTransitPtr SceneFileType::read(
          std::istream &,
    const Char8        *,
          Resolver      ) const
{
    FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));

    return NodeTransitPtr(NULL);
}

#ifndef OSG_DISABLE_DEPRECATED
NodeTransitPtr SceneFileType::readFile(const Char8 *) const
{
    FWARNING (("FILE INTERFACE NOT IMPLEMENTED!\n"));

    return NodeTransitPtr(NULL);
}
#endif

bool SceneFileType::write(
    Node         * const   OSG_CHECK_ARG(node               ),
    std::ostream          &OSG_CHECK_ARG(os                 ),
    Char8          const  *OSG_CHECK_ARG(fileNameOrExtension)) const
{
    FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));
    return false;
}

#ifndef OSG_DISABLE_DEPRECATED
bool SceneFileType::writeFile(Node * const  OSG_CHECK_ARG(node    ),
                              Char8  const *OSG_CHECK_ARG(fileName)) const
{
    FWARNING (("FILE INTERFACE NOT IMPLEMENTED!\n"));
    return false;
}
#endif

OSG_END_NAMESPACE
