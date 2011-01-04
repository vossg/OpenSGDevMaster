/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaFileType.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaGlobal.h"
#include "OSGColladaOptions.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const Char8           *ColladaFileType::_suffixA[] = { "dae" };

      ColladaFileType  ColladaFileType::_the(_suffixA,
                                              sizeof(_suffixA),
                                             false,
                                             10,
                                             OSG_READ_SUPPORTED);


const Char8 *
ColladaFileType::getName(void) const
{
    return "Collada SCENE";
}

NodeTransitPtr
ColladaFileType::read(
    std::istream &is, const Char8 *fileNameOrExtension, Resolver resolver) const
{
    NodeTransitPtr       rootN;

    ColladaGlobalRefPtr  colGlobal = ColladaGlobal ::create();
    ColladaOptionsRefPtr colOpts   = ColladaOptions::create();

    colOpts->parseOptions(this->getOptions());

    colGlobal->setOptions(colOpts);

    rootN = colGlobal->read(is, fileNameOrExtension);

    commitChanges();

    return rootN;
}
                      

ColladaFileType::ColladaFileType(
    const Char8  *suffixArray[], UInt16 suffixByteCount,
    bool          override,      UInt32 overridePriority,
    UInt32        flags                                  )

    : Inherited(suffixArray, suffixByteCount,
                override, overridePriority, flags)
{
}

ColladaFileType::~ColladaFileType(void)
{
}
                                 

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
