/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2007 by the OpenSG Forum                  *
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

#include "OSGOSBGenericElement.h"

#include "OSGOSBRootElement.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBGenericElement                                                      */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBGenericElement
    The default element that can be used to read all types that do not require
    special handling and thus have their own elments.

    \dev
    The generic format is:
    UInt8  ptrTypeId                an id classifying the kind of container
    UInt16 version                  OSB version used to write this container

    for each non-internal field:
        std::string fieldName       name of the field
        std::string fieldTypeName   name of the type stored in the field
        UInt32      fieldSize       number of following bytes for this field
        [Binary representation of the fields contents]
    \enddev
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBDefaultElementRegistrationHelper<OSBGenericElement>
    OSBGenericElement::_regHelper =
        OSBDefaultElementRegistrationHelper<OSBGenericElement>();

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBGenericElement::OSBGenericElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBGenericElement::~OSBGenericElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBGenericElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBGenericElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    UInt8  ptrTypeTag;
    UInt16 version;

    rh->getValue(ptrTypeTag);
    rh->getValue(version   );

    OSG_OSB_LOG(("OSBGenericElement::read: version: [%u] ptrTypeTag [%u]\n",
                 version, ptrTypeTag));

    setContainer(FieldContainerUnrecPtr(
        FieldContainerFactory::the()->createContainer(typeName.c_str())));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBGenericElement::read: Skipping unknown "
                  "FieldContainer [%s].\n", typeName.c_str()));

        skipFields();

        setContainer(FieldContainerUnrecPtr(createReplacementFC(ptrTypeTag)));
        return;
    }

    readFields("", "");
}

void
OSBGenericElement::postRead(void)
{
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBGenericElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBGenericElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBGenericElement::write(void)
{
    OSG_OSB_LOG(("OSBGenericElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBGenericElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}
