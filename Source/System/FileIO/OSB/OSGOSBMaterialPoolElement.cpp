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

#include "OSGOSBMaterialPoolElement.h"

#include "OSGOSBRootElement.h"

#include "OSGGroup.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBMaterialPoolElement                                                  */
/*-------------------------------------------------------------------------*/

/*! Reads the removed MaterialPool from an osb and converts it to a Group
    with a ContainerCollection attachment.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBMaterialPoolElement>
    OSBMaterialPoolElement::_regHelper =
        OSBElementRegistrationHelper<OSBMaterialPoolElement>("MaterialPool");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBMaterialPoolElement::OSBMaterialPoolElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBMaterialPoolElement::~OSBMaterialPoolElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBMaterialPoolElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBMaterialPoolElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();
    
    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    GroupUnrecPtr group = Group              ::create();
    _pCollection        = ContainerCollection::create();

    setContainer(group);

    // set attachment on the Group
    group       ->addAttachment(_pCollection  );
    _pCollection->setName      ("MaterialPool");

    std::string    fieldName;
    std::string    fieldTypeName;
    UInt32         fieldSize;
    PtrFieldListIt ptrFieldIt;
    
    while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
    {
        if(fieldName == "materials")
        {
            // materials from MaterialPool need to be stored in the
            // ContainerCollection
            readMaterialsField();
        }
        else
        {
            // all other fields can be read directly
            readFieldContent(fieldName, fieldTypeName,
                             fieldSize, "", ptrFieldIt);
        }
    }
}

void
OSBMaterialPoolElement::postRead(void)
{
    Inherited::postRead();
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBMaterialPoolElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBMaterialPoolElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBMaterialPoolElement::write(void)
{
    OSG_OSB_LOG(("OSBMaterialPoolElement::write\n"));
    
    if(getContainer() == NULL)
    {
        FWARNING(("OSBMaterialPoolElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}

/*! Reads MFMaterials from MaterialPool and stores the pointer ids so that
    they get put into ContainerCollection MFContainers.
 */
void
OSBMaterialPoolElement::readMaterialsField(void)
{
    OSG_OSB_LOG(("OSBMaterialPoolElement::readMaterialsField\n"));

    UInt32             ptrId;
    UInt32             numElements;
    OSBRootElement    *root        = editRoot();
    BinaryReadHandler *rh          = editRoot()->getReadHandler();

    FieldDescriptionBase *contFieldDesc =
        _pCollection->getFieldDescription("containers");
    UInt32                contFieldId   = contFieldDesc->getFieldId();

    root->editPtrFieldList().push_back(PtrFieldInfo(_pCollection,
                                                    contFieldId  ));
    PtrFieldInfo &pfi = root->editPtrFieldList().back();

    rh->getValue(numElements);

    for(UInt32 i = 0; i < numElements; ++i)
    {
        rh->getValue(ptrId);
        pfi.editIdStore().push_back(ptrId);
    }
}
