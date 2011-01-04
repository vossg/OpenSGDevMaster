/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2007 by the OpenSG Forum                    *
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

#include "OSGOSBDriver.h"

#include "OSGOSBElementFactory.h"
#include "OSGOSBRootElement.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBDriver                                                              */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBDriver
    This is the interface used by OSG::NFIOSceneFileType to access the
    functionality of the OSB IO (OpenSG Binary IO) subsystem.
 */

/*! Reads from \a inStream which must provide access to an ".osb" file.

    \param[in] inStream Stream to read data from.
    \param[in] options String that holds the options for the read operation.

    \return On success a Node * to the root of the read scene,
     NULL otherwise.
 */
NodeTransitPtr OSBDriver::read(      std::istream              &inStream,
                               const IOFileTypeBase::OptionSet &options  )
{
    return dynamic_pointer_cast<Node>(readFC(inStream, options));
}

/*! Writes the scene with root \a node to \a outStream in OSB format.

    \param[in] node Root of scene to write.
    \param[in] outStream Stream to write data to.
    \param[in] options String that holds the options for the write operation.

    \return true.
    \todo Should only return true if write was successful.
 */
bool OSBDriver::write(      Node              * const  node,
                            std::ostream              &outStream,
                      const IOFileTypeBase::OptionSet &options   )
{
    return writeFC(node, outStream, options);
}

/*! Reads from \a inStream which must provide access to an ".osb" file.

    \param[in] inStream Stream to read data from.
    \param[in] options String that holds the options for the read operation.

    \return On success a pointer to the container read from the file.
     NULL otherwise.
 */
FieldContainerTransitPtr
OSBDriver::readFC(      std::istream              &inStream,
                  const IOFileTypeBase::OptionSet &options  )
{
    FieldContainerTransitPtr  retVal;
    OSBRootElement           *root   = dynamic_cast<OSBRootElement *>(
        OSBElementFactory::the()->acquire("RootElement", 0));

    root->initialiseRead(inStream);
    root->editOptions   (        ).init(options);

    root->read    ("");
    root->postRead(  );

    retVal = root->getContainer();

    root->terminateRead();

    OSBElementFactory::the()->release(root);

    commitChanges();

    return retVal;
}

bool
OSBDriver::writeFC(      FieldContainer * const     fc,
                         std::ostream              &outStream,
                   const IOFileTypeBase::OptionSet &options   )
{
   OSBRootElement *root = dynamic_cast<OSBRootElement *>(
        OSBElementFactory::the()->acquire("RootElement", 0));

    root->initialiseWrite(outStream);
    root->editOptions    (         ).init(options);

    root->preWrite(fc);
    root->write   (  );

    root->terminateWrite();

    OSBElementFactory::the()->release(root);

    return true;
}

OSG_END_NAMESPACE
