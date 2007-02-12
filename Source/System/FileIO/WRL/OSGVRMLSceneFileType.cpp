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

#include <cstdlib>
#include <cstdio>

#include <fstream>

#include "OSGConfig.h"

#include "OSGVRMLSceneFileType.h"
#include "OSGVRMLWriteAction.h"

#include "OSGVRMLFile.h"

OSG_USING_NAMESPACE

/*! \class OSG::VRMLSceneFileType
    \ingroup GrpSystemFileIO
*/

const Char8 *VRMLSceneFileType::_suffixA[] =  { "wrl" };

VRMLSceneFileType VRMLSceneFileType::_the(_suffixA,
                                          sizeof(_suffixA),
                                          false,
                                          10,
                                          (OSG_READ_SUPPORTED |
                                           OSG_WRITE_SUPPORTED));

/*-------------------------------------------------------------------------*/
/*                                The                                      */

VRMLSceneFileType &VRMLSceneFileType::the(void)
{
    return _the;
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLSceneFileType::~VRMLSceneFileType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

const Char8 *VRMLSceneFileType::getName(void) const
{
    return "VRML GEOMETRY";
}

/*-------------------------------------------------------------------------*/
/*                               Read                                      */

NodePtr VRMLSceneFileType::read(std::istream &is, const Char8 *) const
{
    NodePtr root = NullFC;

    VRMLFile *loader = new VRMLFile();

    loader->createStandardPrototypes();
    loader->scanStream(is);

    root = loader->getRoot();

    delete loader;

    return root;
}

/*-------------------------------------------------------------------------*/
/*                               Write                                     */

bool VRMLSceneFileType::write(const NodePtr &node, std::ostream &os,
                              const Char8 *fileNameOrExtension) const
{
    // This is a hack but should be safer.

    std::ofstream *osf = dynamic_cast<std::ofstream *>(&os);

    if(osf != NULL)
        osf->close();
    
    VRMLWriteAction *pWriter = VRMLWriteAction::create();

    // parse options
    if(_options.find("inlineTextures=true") != std::string::npos)
        pWriter->addOptions(VRMLWriteAction::OSGPixelTextures);
    else if(_options.find("inlineTextures=false") != std::string::npos)
        pWriter->subOptions(VRMLWriteAction::OSGPixelTextures);

    pWriter->open(fileNameOrExtension);

    pWriter->write(node);

    pWriter->close();

    delete pWriter;

    return true;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLSceneFileType::VRMLSceneFileType(const Char8  *suffixArray[],
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
    static Char8 cvsid_cpp[] = "@(#)$Id$";
    static Char8 cvsid_hpp[] = OSGVRMLSCENEFILETYPE_HEADER_CVSID;
}

