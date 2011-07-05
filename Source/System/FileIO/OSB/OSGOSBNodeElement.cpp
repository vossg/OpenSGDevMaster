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

#include "OSGOSBNodeElement.h"

#include "OSGOSBRootElement.h"
#include "OSGNode.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBNodeElement                                                         */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBNodeElement>
    OSBNodeElement::_regHelper =
        OSBElementRegistrationHelper<OSBNodeElement>("Node");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBNodeElement::OSBNodeElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBNodeElement::~OSBNodeElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBNodeElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBNodeElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh        = editRoot()->getReadHandler();
    UInt8              fcPtrType;
    UInt16             version;

    rh->getValue(fcPtrType);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBNodeElement::read: version: [%u]\n", version));

    if(fcPtrType != OSBCommonElement::FCPtrNode)
    {
        FFATAL(("OSBNodeElement::read: fcPtrType has unexpected value.\n"));

        skipFields();
        return;
    }

    NodeUnrecPtr node = Node::create();

    setContainer(node);
    readFields("", "");
}

void
OSBNodeElement::postRead(void)
{
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBNodeElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBNodeElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBNodeElement::write(void)
{
    OSG_OSB_LOG(("OSBNodeElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBNodeElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(OSBCommonElement::FCPtrNode);
    wh->putValue(getVersion()               );

    Node*       node       = dynamic_cast<Node*>(getContainer());
    std::string skipFields = "";

    if(node->getVolume().isStatic  () == false &&
       node->getVolume().isInfinite() == false   )
    {
        skipFields += "'volume'";
    }

    writeFields(skipFields, true);
}
