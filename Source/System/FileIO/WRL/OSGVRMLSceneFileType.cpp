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
    return "VRML Geometry";
}

/*-------------------------------------------------------------------------*/
/*                               Read                                      */

NodeTransitPtr VRMLSceneFileType::read(      std::istream &is, 
                                       const Char8        *,
                                             Resolver        ) const
{
    NodeTransitPtr root(NULL);

    VRMLFile *loader = new VRMLFile();

    bool pushNames = false;

    if(this->getOptionAs("pushNames", pushNames) == true)
    {
        if(pushNames == true)
            loader->addOptions(VRMLFile::PushNames);
    }

    loader->createStandardPrototypes();

    root = loader->scanStream(is);

    delete loader;

    commitChanges();

    return root;
}

/*-------------------------------------------------------------------------*/
/*                               Write                                     */

bool VRMLSceneFileType::write(Node         * const  node, 
                              std::ostream         &os,
                              Char8          const *fileNameOrExtension) const
{
    // This is a hack but should be safer.

    std::ofstream *osf = dynamic_cast<std::ofstream *>(&os);

    if(osf != NULL)
        osf->close();
    
    VRMLWriteAction *pWriter = VRMLWriteAction::create();

    // parse options
    bool inlineTex = false;
    if(getOptionAs<bool>("inlineTextures", inlineTex))
    {
        if(inlineTex)
            pWriter->addOptions(VRMLWriteAction::OSGPixelTextures);
        else
            pWriter->subOptions(VRMLWriteAction::OSGPixelTextures);
    }
    
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


