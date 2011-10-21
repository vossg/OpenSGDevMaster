/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2011 by the OpenSG Forum                  *
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

#include "OSGOSBVoidPAttachmentElement.h"

#include "OSGOSBRootElement.h"
#include "OSGVoidPAttachment.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBVoidPAttachmentElement                                               */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBVoidPAttachmentElement>
    OSBVoidPAttachmentElement::_regHelper =
        OSBElementRegistrationHelper<OSBVoidPAttachmentElement>("VoidPAttachment");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBVoidPAttachmentElement::OSBVoidPAttachmentElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBVoidPAttachmentElement::~OSBVoidPAttachmentElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBVoidPAttachmentElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBVoidPAttachmentElement::read [%s]\n", typeName.c_str()));

    OSBRootElement    *root      = editRoot();
    BinaryReadHandler *rh        = editRoot()->getReadHandler();
    UInt8              fcPtrType;
    UInt16             version;

    rh->getValue(fcPtrType);
    rh->getValue(version  );

    setContainer(VoidPAttachmentUnrecPtr(VoidPAttachment::create()));

    // keep these ordered from highest to lowest version
    if(root->getHeaderVersion() >= OSGOSBHeaderVersion200)
    {
        if(root->getHeaderVersion() > OSGOSBHeaderVersion200)
        {
            FINFO(("OSBVoidPAttachmentElement::read: "
                   "Unknown header version, trying to read as latest.\n"));
        }

        readFields("", "");
    }
    else if(root->getHeaderVersion() >= OSGOSBHeaderVersion100)
    {
        // 1.x stores the address in 32 (!) chars and writes a string,
        // skip it

        readFields("'data'", "");
    }
}

void
OSBVoidPAttachmentElement::postRead(void)
{
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBVoidPAttachmentElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBVoidPAttachmentElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBVoidPAttachmentElement::write(void)
{
    OSG_OSB_LOG(("OSBVoidPAttachmentElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBVoidPAttachmentElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}

OSG_END_NAMESPACE
