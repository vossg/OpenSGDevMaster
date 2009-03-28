/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2006 by the OpenSG Forum                  *
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

#include "OSGOSBNameElement.h"

#include "OSGOSBRootElement.h"
#include "OSGNameAttachment.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBNameElement                                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBNameElement>
    OSBNameElement::_regHelper =
        OSBElementRegistrationHelper<OSBNameElement>("Name");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBNameElement::OSBNameElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBNameElement::~OSBNameElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBNameElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBNameElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh        = editRoot()->getReadHandler();
    UInt8              fcPtrType;
    UInt16             version;

    rh->getValue(fcPtrType);
    rh->getValue(version  );

    setContainer(NameUnrecPtr(Name::create()));
    readFields("", "");
}

void
OSBNameElement::postRead(void)
{
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBNameElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBNameElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBNameElement::write(void)
{
    OSG_OSB_LOG(("OSBNameElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBNameElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}
