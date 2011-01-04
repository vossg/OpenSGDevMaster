/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2007 by the OpenSG Forum                *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include "OSGLog.h"
#include "OSGNode.h"
#include "OSGGeometry.h"
#include "OSGGeoProperty.h"
#include "OSGSimpleMaterial.h"

#include "OSGNFIOSceneFileType.h"

#include "OSGOSBDriver.h"

OSG_USING_NAMESPACE

/*! \class OSG::NFIOSceneFileType
    \ingroup GrpSystemFileIO

    Loader for the binary file type. (.osb)
 */

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning(disable : 383)
#endif

/*-------------------------------------------------------------------------*/
/*                            static get                                   */

/*! Returns the singleton instance.
 */
NFIOSceneFileType &NFIOSceneFileType::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            destructor                                   */

/*! Destructor, does nothing.
 */
NFIOSceneFileType::~NFIOSceneFileType(void)
{
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            read                                         */

/*! Read from the given input stream.
    \see OSG::NFIODriver
 */
NodeTransitPtr NFIOSceneFileType::read(      std::istream &is, 
                                       const Char8        *,
                                             Resolver        ) const
{
    return OSBDriver::read(is, getOptions());
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                            write                                        */

/*! Writes the given \a node and its subtree to the given output stream.
    \see OSG::NFIOBase

    \param[in] node Root of the subtree to write.
    \param[in] os Output stream to write to.
    \param[in] fileNameOrExtension filename or file extension
    \return True if the operation succeeded, false otherwise.
 */
bool NFIOSceneFileType::write(Node         * const  node,
                              std::ostream         &os,
                              Char8          const *fileNameOrExtension) const
{
    return OSBDriver::write(node, os, getOptions());
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor.
    \see SceneFileType::SceneFileType
 */
NFIOSceneFileType::NFIOSceneFileType(const Char8  *suffixArray[],
                                           UInt16  suffixByteCount,
                                           bool    override,
                                           UInt32  overridePriority,
                                           UInt32  flags            )
    : SceneFileType(suffixArray, suffixByteCount, override,
                    overridePriority, flags)
{
}

/*! Copy constructor.
 */
NFIOSceneFileType::NFIOSceneFileType(const NFIOSceneFileType &obj) :
    SceneFileType(obj)
{
}

/*! Returns a descriptive name for the type of files read.
 */
const Char8 *NFIOSceneFileType::getName(void) const
{
    return "OSG Binary";
}

/*-------------------------------------------------------------------------*/
/*                              static elements                            */

const Char8 *     NFIOSceneFileType::_suffixA[] = { "osb" };
NFIOSceneFileType NFIOSceneFileType::_the(_suffixA,
                                         sizeof(_suffixA), false, 10,
                                         OSG_READ_SUPPORTED |
                                         OSG_WRITE_SUPPORTED);
