/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#include "OSGOSBGenericAttElement.h"

#include "OSGOSBRootElement.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBGenericAttElement                                                    */
/*-------------------------------------------------------------------------*/

/*! Skips a 1.x GenericAtt attachment in the stream. This is not handled
    correctly by the GenericElement, because the GenericAtt has a header
    format that is inconsistent with other elements.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBGenericAttElement>
    OSBGenericAttElement::_regHelper =
        OSBElementRegistrationHelper<OSBGenericAttElement>("GenericAtt");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBGenericAttElement::OSBGenericAttElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBGenericAttElement::~OSBGenericAttElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBGenericAttElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBGenericAttElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    // GenericAtt only exists in 1.x osb files, but has no ptrTypeTag
//     UInt8  ptrTypeTag;
    UInt16 version;

//     rh->getValue(ptrTypeTag);
    rh->getValue(version   );

    OSG_OSB_LOG(("OSBGenericAttElement::read: version: [%u]\n", version));

    skipFields();
}

void
OSBGenericAttElement::postRead(void)
{
    Inherited::postRead();
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBGenericAttElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBGenericAttElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBGenericAttElement::write(void)
{
    OSG_OSB_LOG(("OSBGenericAttElement::write\n"));
    
    if(getContainer() == NULL)
    {
        FWARNING(("OSBGenericAttElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}
