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

#include "OSGOSBCommonElement.h"
#include "OSGOSBElementFactory.h"
#include "OSGOSBRootElement.h"

#include "OSGAttachmentContainer.h"
#include "OSGChunkMaterial.h"
#include "OSGGroup.h"
#include "OSGNode.h"
#include "OSGStateChunk.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBCommonElement                                                       */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBCommonElement
    This element is intended as base class for most (all) other elements and
    provides functions that simplify implementing these.
    It itself is abstract and can not handle any types.
 */

/*-------------------------------------------------------------------------*/
/* Constants                                                               */

const UInt8 OSBCommonElement::FCPtrUnknown        = 0;
const UInt8 OSBCommonElement::FCPtrFieldContainer = 1;
const UInt8 OSBCommonElement::FCPtrNode           = 2;
const UInt8 OSBCommonElement::FCPtrNodeCore       = 3;
const UInt8 OSBCommonElement::FCPtrAttachment     = 4;
const UInt8 OSBCommonElement::FCPtrMaterial       = 5;
const UInt8 OSBCommonElement::FCPtrStateChunk     = 6;

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBCommonElement::OSBCommonElement(OSBRootElement *root, UInt16 version)
    : Inherited(root, version)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBCommonElement::~OSBCommonElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBCommonElement::read(const std::string &/* typeName */)
{
    // nothing to do.
}

void
OSBCommonElement::postRead(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBCommonElement::preWrite(const FieldContainerPtr &/* fc */)
{
    // nothing to do.
}

void
OSBCommonElement::write(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading Helper methods                                                  */

/*! Reads the common part introducing a FieldContainer and returns
    the information in \a typeName and \a fcId.

    \param[out] typeName Type of the next container in the stream or "" if
    no more data is available.
    \param[out] fcId Id of the next container - only valid if true is returned.

    \return If another container is to be read, true is returned,
    otherwise false.
 */
bool
OSBCommonElement::readFieldContainerHeader(
    std::string &typeName,
    UInt32      &fcId     )
{
    FDEBUG(("OSBCommonElement::readFieldContainerHeader\n"));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    rh->getValue(typeName);

    if(typeName.empty())
        return false;

    rh->getValue(fcId);

    return true;
}

/*! Reads the common part introducing a Field and returns the information
    in \a fieldName, \a fieldTypeName, and \a fieldSize.
    By default reading would stop an a field name of "", by passing a string
    of type names in \a endMarkers additional stop conditions can be specified.

    The format of the \a endMarkers string is: "'name1' 'name2' 'name3'", the
    spaces between the "'" are mandatory.

    \param[in] endMarkers String of field names on which reading stops.
    \param[out] fieldName Name of the next field in the stream.
    \param[out] fieldTypeName Type of the next field in the stream - only valid
    if true is returned.
    \param[out] fieldSize Size in bytes of the next field in the stream -
    only valid if true is returned.

    \return False, if an endMarker (including the implicit "") is encountered,
    true otherwise.

    \sa OSG::OSBCommonElement::readFieldContent
    \sa OSG::OSBCommonElement::readFieldHeaderContinue
 */
bool
OSBCommonElement::readFieldHeader(
    const std::string &endMarkers,
          std::string &fieldName,
          std::string &fieldTypeName,
          UInt32      &fieldSize     )
{
    FDEBUG(("OSBCommonElement::readFieldHeader\n"));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    rh->getValue(fieldName);

    return readFieldHeaderContinue(endMarkers, fieldName,
                                   fieldTypeName, fieldSize);
}

/*! Reads the common part introducing a Field, but after the field name is
    already consumed from the input stream. This is mainly useful to continue
    reading after readFields stopped on a non empty endMarkers entry.
    The information from the field header is returned in \a fieldTypeName and
    \a fieldSize.

    By default reading would stop an a field name of "", by passing a string
    of type names in \a endMarkers additional stop conditions can be specified.

    The format of the \a endMarkers string is: "'name1' 'name2' 'name3'", the
    spaces between the "'" are mandatory.

    \param[in] endMarkers String of field names on which reading stops.
    \param[in] fieldName Name of the next field in the stream.
    \param[out] fieldTypeName Type of the next field in the stream - only valid
    if true is returned.
    \param[out] fieldSize Size in bytes of the next field in the stream -
    only valid if true is returned.

    \return False, if an endMarker (including the implicit "") is encountered,
    true otherwise.

    \sa OSG::OSBCommonElement::readFieldContent
    \sa OSG::OSBCommonElement::readFieldHeader
 */
bool
OSBCommonElement::readFieldHeaderContinue(
    const std::string &endMarkers,
    const std::string &fieldName,
          std::string &fieldTypeName,
          UInt32      &fieldSize     )
{
    FDEBUG(("OSBCommonElement::readFieldHeaderContinue\n"));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    if(fieldName.empty() ||
       (!endMarkers.empty() &&
       (endMarkers.find("'" + fieldName + "'") != std::string::npos)))
    {
        FDEBUG(("OSBCommonElement::readFieldHeaderContinue: "
                "Found field end marker.\n"));

        return false;
    }
    else
    {
        rh->getValue(fieldTypeName);
        rh->getValue(fieldSize    );

        FDEBUG(("OSBCommonElement::readFieldHeaderContinue: "
                "[%s] [%s] [%u]\n",
                fieldName.c_str(), fieldTypeName.c_str(), fieldSize));

        return true;
    }
}

/*! Reads the contents of a field from the stream. It is intended to be used
    in conjunction with readFieldHeader and uses the information obtained
    by it (\a fieldName, \a fieldTypeName, \a fieldSize ).

    If a field is not to be read, but skipped instead, its name can be passed
    in the \a excludeFields argument. The string has the format:
    "'name1' 'name2' 'name3'", the spaces between the "'" are mandatory.

    \param[in] fieldName Name of the field.
    \param[in] fieldTypeName Type of the field.
    \param[in] fieldSize Size in bytes of the field.
    \param[in] excludeFields
    \param[out] ptrFieldIt Iterator that points to the PtrFieldInfo structure
    that was created, if this is a "pointer field" - only valid if true is
    returned.

    \return True, if the field is a "pointer field", i.e. a field holding
    pointers to other FieldContainers, false otherwise.
 */
bool
OSBCommonElement::readFieldContent(
    const std::string    &fieldName,
    const std::string    &fieldTypeName,
    const UInt32          fieldSize,
    const std::string    &excludeFields,
          PtrFieldListIt &ptrFieldIt    )
{
    FDEBUG(("OSBCommonElement::readFieldContent: [%s] [%s] [%u]\n",
            fieldName.c_str(), fieldTypeName.c_str(), fieldSize));

    BinaryReadHandler    *rh         = editRoot()->getReadHandler();
    bool                  isPtrField = false;
    FieldDescriptionBase *fieldDesc  =
        getContainer()->getFieldDescription(fieldName.c_str());

    if(fieldDesc == 0)
    {
        FWARNING(("OSBCommonElement::readFieldContent: "
                  "Skipping unknown field [%s] [%s].\n",
                  fieldName.c_str(), fieldTypeName.c_str()));

        rh->skip(fieldSize);
        return false;
    }

    const FieldType &fieldType  = fieldDesc->getFieldType();
    UInt32           fieldId    = 0;
    BitVector        fieldMask;

    // HACK the 1.0 MaterialChunk had a internal field the 2.0 MaterialChunk
    // has also a internal field but a internal internal field ;-)
    // but fDesc->isInternal() returns false BUG ????
    if(getRoot()->getHeaderVersion() == OSGOSBHeaderVersion100 &&
       fieldName                     == "internal"                )
    {
        FINFO(("OSBCommonElement::readFieldContent: "
               "Skipping internal field [%s] (%s).\n",
               fieldName.c_str(), fieldTypeName.c_str()));

        rh->skip(fieldSize);
        return false;
    }
    else
    {
        fieldMask = fieldDesc->getFieldMask();
        fieldId   = fieldDesc->getFieldId  ();
    }

    if((!excludeFields.empty()                                        ) &&
       (excludeFields.find("'" + fieldName + "'") != std::string::npos)   )
    {
        FDEBUG(("OSBCommonElement::readFieldContent: "
                "Skipping excluded field [%s]\n", fieldName.c_str()));

        rh->skip(fieldSize);
        return false;
    }

    if(fieldType.getContentType().isDerivedFrom(
        FieldTraits<FieldContainerAttachmentMap>::getType()) == true)
    {
        ptrFieldIt = readAttachmentMapField(fieldId, fieldSize);
        isPtrField = true;
    }
    else if(fieldType.getContentType().isDerivedFrom(
        FieldTraits<FieldContainerPtr>::getType()) == true)
    {
        if(fieldType.getCardinality() == FieldType::SINGLE_FIELD)
        {
            ptrFieldIt = readPtrSingleField(fieldId);
            isPtrField = true;
        }
        else if(fieldType.getCardinality() == FieldType::MULTI_FIELD)
        {
            ptrFieldIt = readPtrMultiField(fieldId, fieldSize);
            isPtrField = true;
        }
    }
    else
    {
        getContainer()->copyFromBin(*rh, fieldMask);
        isPtrField = false;
    }

    return isPtrField;
}

/*! Reads fields from the stream until an end marker (either a field name of ""
    or one in \a endMarkers) is encountered, skipping fields in
    \a excludeFields.
    This makes use of readFieldHeader and readFieldContent and also demonstates
    how these two functions can be used.

    \param[in] excludeFields Field names that should be skipped in the stream.
    \param[in] endMarkers Fields names (in additon to "") that will cause
    reading to stop.

    \return The last field name that was read, this can be "", if the end of
    the fields was reached.
 */
std::string
OSBCommonElement::readFields(const std::string &excludeFields,
                             const std::string &endMarkers    )
{
    BinaryReadHandler  *rh         = editRoot()->getReadHandler();
    std::string         fieldName  = "";
    PtrFieldListIt      ptrFieldIt;

    while(true)
    {
        std::string fieldTypeName;
        UInt32      fieldSize;

        if(!readFieldHeader(endMarkers, fieldName,
                            fieldTypeName, fieldSize))
        {
            FDEBUG(("OSBCommonElement::readFields: "
                    "Reading stopped at field: [%s].\n", fieldName.c_str() ));
            break;
        }

        readFieldContent(fieldName, fieldTypeName, fieldSize,
                         excludeFields, ptrFieldIt           );
    }

    return fieldName;
}

/*! Reads fields from the stream until an end marker (either a field name of ""
    or one in \a endMarkers) is encountered, skipping fields in
    \a excludeFields.
    This function is intended to be used when the next fields name was already
    consumed from the input stream, e.g. when readFields stopped on a non empty
    endMarkers entry.
    This makes use of readFieldHeader and readFieldContent and also demonstates
    how these two functions can be used.

    \param[in] fieldName Name of the next field in the stream.
    \param[in] excludeFields Field names that should be skipped in the stream.
    \param[in] endMarkers Fields names (in additon to "") that will cause
    reading to stop.

    \return The last field name that was read, this can be "", if the end of
    the fields was reached.
 */
std::string
OSBCommonElement::readFieldsContinue(const std::string &fieldName,
                                     const std::string &excludeFields,
                                     const std::string &endMarkers    )
{
    BinaryReadHandler  *rh         = editRoot()->getReadHandler();
    PtrFieldListIt      ptrFieldIt;
    std::string         fieldName2;
    std::string         fieldTypeName;
    UInt32              fieldSize;

    // Read the first field specially - its name was already consumed
    if(!readFieldHeaderContinue(endMarkers, fieldName,
                                fieldTypeName, fieldSize))
    {
        FDEBUG(("OSBCommonElement::readFieldsContinue: "
                "Reading stopped at field: [%s].\n", fieldName.c_str() ));
        return fieldName;
    }

    readFieldContent(fieldName, fieldTypeName, fieldSize,
                     excludeFields, ptrFieldIt           );

    // continue reading normally
    while(true)
    {
        if(!readFieldHeader(endMarkers, fieldName2,
                            fieldTypeName, fieldSize))
        {
            FDEBUG(("OSBCommonElement::readFieldsContinue: "
                    "Reading stopped at field: [%s].\n", fieldName2.c_str() ));
            break;
        }

        readFieldContent(fieldName2, fieldTypeName, fieldSize,
                         excludeFields, ptrFieldIt            );
    }

    return fieldName;
}

/*! Skips all fields in the stream, until the field end
    marker "" is encountered.
 */
void
OSBCommonElement::skipFields(void)
{
    BinaryReadHandler *rh = editRoot()->getReadHandler();

    while(true)
    {
        std::string fieldName;
        std::string fieldTypeName;
        UInt32      fieldSize;

        rh->getValue(fieldName);

        if(fieldName.empty())
        {
            FDEBUG(("OSBCommonElement::skipFields: "
                    "Found field end marker.\n"      ));
            break;
        }

        rh->getValue(fieldTypeName);
        rh->getValue(fieldSize    );
        rh->skip    (fieldSize    );
    }
}

/*! Reads a SFFieldContainerPtr (or a more specific pointer type) from the
    stream. It has the given \a fieldId in the container it belongs to.

    \param[in] fieldId Id of the field in the container it belongs to.

    \return Iterator that points to the PtrFieldInfo structure
    that was created for this field.
 */
OSBCommonElement::PtrFieldListIt
OSBCommonElement::readPtrSingleField(const UInt32 fieldId)
{
    FDEBUG(("OSBCommonElement::readPtrSingleField: "
            "fieldId: [%u]\n", fieldId));

    OSBRootElement *root  = editRoot();
    UInt32           ptrId;

    root->getReadHandler()->getValue(ptrId);

    root->editPtrFieldList().push_back(PtrFieldInfo(getContainer(), fieldId));
    root->editPtrFieldList().back().editIdStore().push_back(ptrId);

    return --(root->editPtrFieldList().end());
}

/*! Reads a MFFieldContainerPtr (or a more specific pointer type) from the
    stream. It has the given \a fieldId in the container it belongs to.

    \param[in] fieldId Id of the field in the container it belongs to.

    \return Iterator that points to the PtrFieldInfo structure
    that was created for this field.
 */
OSBCommonElement::PtrFieldListIt
OSBCommonElement::readPtrMultiField(
    const UInt32 fieldId, const UInt32 fieldSize)
{
    FDEBUG(("OSBCommonElement::readPtrMultiField: "
            "fieldId: [%u]\n", fieldId));

    UInt32             ptrId;
    UInt32             numElements;
    OSBRootElement   *root        = editRoot();
    BinaryReadHandler *rh          = editRoot()->getReadHandler();

    root->editPtrFieldList().push_back(PtrFieldInfo(getContainer(), fieldId));
    PtrFieldInfo &pfi = root->editPtrFieldList().back();

    rh->getValue(numElements);

    for(UInt32 i = 0; i < numElements; ++i)
    {
        rh->getValue(ptrId);
        pfi.editIdStore().push_back(ptrId);
    }

    return --(root->editPtrFieldList().end());
}

/*! Reads a SFFieldContainerAttachmentPtrMap from the stream. It has the
    given \a fieldId in the container it belongs to and size \a fieldSize.

    \param[in] fieldId Id of the field in the container it belongs to.
    \param[in] fieldSize Size in byte of the field.

    \return Iterator that points to the PtrFieldInfo structure
    that was created for this field.
 */
OSBCommonElement::PtrFieldListIt
OSBCommonElement::readAttachmentMapField(
    const UInt32 fieldId, const UInt32 fieldSize)
{
    FDEBUG(("OSBCommonElement::readAttachmentMapField: "
            "fieldId: [%u]\n", fieldId));

    bool               hasBindingInfo = false;
    UInt32             ptrId;
    UInt16             binding;
    UInt32             numElements;
    OSBRootElement   *root           = editRoot();
    BinaryReadHandler *rh             = editRoot()->getReadHandler();

    root->editPtrFieldList().push_back(PtrFieldInfo(getContainer(), fieldId));
    PtrFieldInfo &pfi = root->editPtrFieldList().back();

    rh->getValue(numElements);

    // keep these ordered from highest to lowest version
    if(root->getHeaderVersion() >= OSGOSBHeaderVersion200)
    {
        if(root->getHeaderVersion() > OSGOSBHeaderVersion200)
        {
            FINFO(("OSBCommonElement::readAttachmentMapField: "
                   "Unknown header version, trying to read as latest.\n"));
        }

        hasBindingInfo = true;
    }
    else if(root->getHeaderVersion() >= OSGOSBHeaderVersion100)
    {
        // distinguish format with or without binding info
        if(fieldSize == (sizeof(UInt32) + numElements * sizeof(UInt32)))
        {
            hasBindingInfo = false;
        }
        else
        {
            hasBindingInfo = true;
        }
    }

    if(hasBindingInfo == true)
    {
        for(UInt32 i = 0; i < numElements; ++i)
        {
            rh->getValue(binding);
            rh->getValue(ptrId  );

            pfi.editBindingStore().push_back(binding);
            pfi.editIdStore     ().push_back(ptrId  );
        }
    }
    else
    {
        for(UInt32 i = 0; i < numElements; ++i)
        {
            rh->getValue(ptrId);
            pfi.editIdStore().push_back(ptrId);
        }
    }

    return --(root->editPtrFieldList().end());
}

/*-------------------------------------------------------------------------*/
/* Prewriting Helper methods                                               */

/*! Visits a SFFieldContainerPtr (or more specific pointer type) during
    preWrite. It creates an element for the pointed to container and
    calls preWrite on it. If the pointed to container is not in the
    root's id set it is added and thus scheduled for writing.

    \param[in] fieldId Id of the field in the container of this element.
 */
void
OSBCommonElement::preWritePtrSingleField(const UInt32 fieldId)
{
    FDEBUG(("OSBCommonElement::preWritePtrSingleField: "
            "fieldId: [%u]\n", fieldId));

    OSBRootElement     *root       = editRoot();

    SFFieldContainerPtr::GetHandlePtr sfPtrField =
        boost::dynamic_pointer_cast<SFFieldContainerPtr::GetHandle>(
            getContainer()->getField(fieldId));

    if(sfPtrField == NULL || sfPtrField->isValid() == false)
        return;

    FieldContainerPtr refedFC = (*sfPtrField)->getValue();

    if(refedFC == NullFC)
        return;

    UInt32      refedId  = OSG::getContainerId(refedFC);
    std::string typeName = refedFC->getType().getCName();

    // only schedule a container once
    if(root->getIdSet().count(refedId) == 0)
    {
        OSBElementBase *elem = OSBElementFactory::the()->acquire(
            typeName, root);

        root->editIdSet      ().insert   (refedId);
        root->editElementList().push_back(elem   );
        elem->setContainer(refedFC);
        elem->preWrite    (refedFC);
    }
}

/*! Visits a MFFieldContainerPtr (or more specific pointer type) during
    preWrite. It creates elements for the pointed to containers and
    calls preWrite on them. If the pointed to containers are not in the
    root's id set they are added and thus scheduled for writing.

    \param[in] fieldId Id of the field in the container of this element.
 */
void
OSBCommonElement::preWritePtrMultiField(const UInt32 fieldId)
{
    FDEBUG(("OSBCommonElement::preWritePtrMultiField: "
            "fieldId: [%u]\n", fieldId));

    OSBRootElement           *root       = editRoot();

    MFFieldContainerPtr::GetHandlePtr mfPtrField =
        boost::dynamic_pointer_cast<MFFieldContainerPtr::GetHandle>(
            getContainer()->getField(fieldId));

    if(mfPtrField == NULL || mfPtrField->isValid() == false)
        return;

    MFFieldContainerPtr::const_iterator fieldIt  = (*mfPtrField)->begin();
    MFFieldContainerPtr::const_iterator fieldEnd = (*mfPtrField)->end  ();

    for(; fieldIt != fieldEnd; ++fieldIt)
    {
        FieldContainerPtr refedFC = *fieldIt;

        if(refedFC == NullFC)
            continue;

        UInt32      refedId  = OSG::getContainerId(refedFC);
        std::string typeName = refedFC->getType().getCName();

        // only schedule a container once
        if(root->getIdSet().count(refedId) > 0)
            continue;

        OSBElementBase *elem = OSBElementFactory::the()->acquire(
            typeName, root);

        root->editIdSet      ().insert   (refedId);
        root->editElementList().push_back(elem   );
        elem->setContainer(refedFC);
        elem->preWrite    (refedFC);

    }
}

/*! Visits a SFFieldContainerAttachmentPtrMap during
    preWrite. It creates elements for the pointed to containers and
    calls preWrite on them. If the pointed to containers are not in the
    root's id set they are added and thus scheduled for writing.

    \param[in] fieldId Id of the field in the container of this element.
 */
void
OSBCommonElement::preWriteAttachmentMapField(const UInt32 fieldId)
{
    FDEBUG(("OSBCommonElement::preWriteAttachmentMapField: "
            "fieldId: [%u]\n", fieldId));

    OSBRootElement                        *root        = editRoot();

    SFFieldContainerAttachmentPtrMap::GetHandlePtr sfAMapField =
        boost::dynamic_pointer_cast<
            SFFieldContainerAttachmentPtrMap::GetHandle>(
                getContainer()->getField(fieldId));

    if(sfAMapField == NULL || sfAMapField->isValid() == false)
        return;

    FieldContainerAttachmentMap::const_iterator mapIt  =
        (*sfAMapField)->getValue().begin();
    FieldContainerAttachmentMap::const_iterator mapEnd =
        (*sfAMapField)->getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        FieldContainerPtr refedFC = mapIt->second;

        if(refedFC == NullFC)
            continue;

        UInt32      refedId  = OSG::getContainerId(refedFC);
        std::string typeName = refedFC->getType().getCName();

        // only schedule a container once
        if(root->getIdSet().count(refedId) > 0)
            continue;

        OSBElementBase *elem = OSBElementFactory::the()->acquire(
            typeName, root);

        root->editIdSet      ().insert   (refedId);
        root->editElementList().push_back(elem   );
        elem->setContainer(refedFC);
        elem->preWrite    (refedFC);
    }
}

/*! Visits the given container \a fc during preWrite and creates elements
    for all containers reachable from this (except for those refered to by
    fields whose names are in \a excludeFields).

    The excludeFields string has the format: "'name1' 'name2' 'name3'",
    the spaces between the "'" are mandatory.

    \param[in] fc Container this element shall visit.
    \param[in] excludeFields Field names that are not to be considered when
    determining reachable containers.
 */
void
OSBCommonElement::preWriteFieldContainer(
    const FieldContainerPtr &fc, const std::string &excludeFields)
{
    FDEBUG(("OSBCommonElement::preWriteFieldContainer: "
            "excludeFields: [%s]\n", excludeFields.c_str()));

    UInt32 fieldCount = fc->getType().getNumFieldDescs();

    // go through all fields and find those refering to other FCs
    for(UInt32 fieldId = 1; fieldId <= fieldCount; ++fieldId)
    {
        const FieldDescriptionBase *fieldDesc = fc->getFieldDescription(fieldId);
        const FieldType            &fieldType = fieldDesc->getFieldType();
        BitVector                   fieldMask = fieldDesc->getFieldMask();
        std::string                 fieldName = fieldDesc->getCName    ();

        FDEBUG(("OSBCommonElement::preWriteFieldContainer: "
                "fieldName: [%s] fieldId: [%u]\n", fieldName.c_str(), fieldId));

        // skip internal fields
        if(fieldDesc->isInternal())
        {
            FDEBUG(("OSBCommonElement::preWriteFieldContainer: "
                    "Skipping internal field: [%s]\n", fieldName.c_str()));
            continue;
        }

        // skip excluded fields
        if((!excludeFields.empty()                                        ) &&
           (excludeFields.find("'" + fieldName + "'") != std::string::npos)   )
        {
            FDEBUG(("OSBCommonElement::preWriteFieldContainer: "
                    "Skipping excluded field: [%s]\n", fieldName.c_str()));
            continue;
        }

        // check if field refers to another FC, i.e. its a field holding
        // FieldContainerPtr or an FieldContainerAttachmentMap
        if(fieldType.getContentType().isDerivedFrom(
            FieldTraits<FieldContainerPtr>::getType()) == true)
        {
            if(fieldType.getCardinality() == FieldType::SINGLE_FIELD)
            {
                preWritePtrSingleField(fieldId);
            }
            else if(fieldType.getCardinality() == FieldType::MULTI_FIELD)
            {
                preWritePtrMultiField(fieldId);
            }
        }
        else if(fieldType.getContentType().isDerivedFrom(
            FieldTraits<FieldContainerAttachmentMap>::getType()) == true)
        {
            preWriteAttachmentMapField(fieldId);
        }
    }
}

/*-------------------------------------------------------------------------*/
/* Writing Helper methods                                                  */

/*! Writes the header for the given container \a fc to the stream.

    \param[in] fc Container to write the header for.
 */
void
OSBCommonElement::writeFieldContainerHeader(const FieldContainerPtr &fc)
{
    FDEBUG(("OSBCommonElement::writeFieldContainerHeader\n"));

    BinaryWriteHandler *wh       = editRoot()->getWriteHandler();
    std::string         typeName = fc->getType().getCName();
    UInt32              fcId     = OSG::getContainerId(fc);

    wh->putValue(typeName);
    wh->putValue(fcId    );
}

/*! Writes the header for a field to the stream.

    \param[in] fieldName Name of the field.
    \param[in] fieldTypeName Type of the field.
    \param[in] fieldSize Size in bytes of the field.
 */
void
OSBCommonElement::writeFieldHeader(
    const std::string &fieldName, const std::string &fieldTypeName,
    const UInt32       fieldSize                                   )
{
    FDEBUG(("OSBCommonElement::writeFieldHeader: "
            "[%s] [%s] [%u]\n",
            fieldName.c_str(), fieldTypeName.c_str(), fieldSize));

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(fieldName    );
    wh->putValue(fieldTypeName);
    wh->putValue(fieldSize    );
}

/*! Write the contents of the field with the given \a fieldId to the stream.

    \param[in] fieldId Id of the field to write.
 */
void
OSBCommonElement::writeFieldContent(const UInt32 fieldId)
{
    FDEBUG(("OSBCommonElement::writeFieldContent\n"));

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();
    FieldContainerPtr   fc = getContainer();

    const FieldDescriptionBase *fieldDesc = fc->getFieldDescription(fieldId);
    const BitVector             fieldMask = fieldDesc->getFieldMask(       );

    fc->copyToBin(*wh, fieldMask);
}

/*! Writes all fields to the stream, except for those whose name is in
    \a excludeFields. Optionally writes an end marker.

    The excludeFields string has the format: "'name1' 'name2' 'name3'",
    the spaces between the "'" are mandatory.

    \param[in] excludeFields String of field names that shall be skipped.
    \param[in] endMaker Write an end marker to the stream after all fields are
    processed.
 */
void
OSBCommonElement::writeFields(
    const std::string &excludeFields, const bool endMarker)
{
    FDEBUG(("OSBCommonElement::writeFields: "
            "excludeFields: [%s]\n", excludeFields.c_str()));

    FieldContainerPtr fc         = getContainer();
    UInt32            fieldCount = fc->getType().getNumFieldDescs();

    // go through all fields and write them.
    for(UInt32 fieldId = 1; fieldId <= fieldCount; ++fieldId)
    {
        const FieldDescriptionBase *fieldDesc =
            fc->getFieldDescription(fieldId);
        std::string                 fieldName = fieldDesc->getCName();

        // skip internal fields
        if(fieldDesc->isInternal())
        {
            FDEBUG(("OSBCommonElement::writeFields: "
                    "Skipping internal field: [%s]\n", fieldName.c_str()));
            continue;
        }

        // skip excluded fields
        if((!excludeFields.empty()                                        ) &&
           (excludeFields.find("'" + fieldName + "'") != std::string::npos)   )
        {
            FDEBUG(("OSBCommonElement::writeFields: "
                    "Skipping excluded field: [%s]\n", fieldName.c_str()));
            continue;
        }

        const FieldType &fieldType     = fieldDesc->getFieldType();
        std::string      fieldTypeName = fieldType .getCName    ();
        BitVector        fieldMask     = fieldDesc->getFieldMask();
        UInt32           fieldSize     = fc->getBinSize(fieldMask);

        writeFieldHeader (fieldName, fieldTypeName, fieldSize);
        writeFieldContent(fieldId                            );
    }

    if(endMarker)
    {
        writeEndMarker();
    }
}

/*! Writes an end marker to the stream.
 */
void
OSBCommonElement::writeEndMarker(void)
{
    FDEBUG(("OSBCommonElement::writeEndMarker\n"));

    editRoot()->getWriteHandler()->putValue(std::string(""));
}

/*-------------------------------------------------------------------------*/
/* Misc Helper methods                                                     */

/*! Creates a container that can be used as a replacement for an unavailable
    type. The type of the replacement is determined by the \a fcPtrType
    which must be one of the constants in this class.

    \param[in] fcPtrType One of the constants in this class, descibing what
    type of container is to be replaced.

    \return A container that can act as replacement for a missing type or
    NullFC if no such container was found.
 */
FieldContainerPtr
OSBCommonElement::createReplacementFC(const UInt8 fcPtrType)
{
    FieldContainerPtr fc = NullFC;

    switch(fcPtrType)
    {
        case OSBCommonElement::FCPtrNode:
            fc = Node::create();
            break;

        case OSBCommonElement::FCPtrNodeCore:
            fc = Group::create();
            break;

        case OSBCommonElement::FCPtrMaterial:
            fc = ChunkMaterial::create();
            break;

        case OSBCommonElement::FCPtrStateChunk:
            // do nothing.
            break;

        case OSBCommonElement::FCPtrAttachment:
            // do nothing.
            break;

        default:
            fc = Node::create();
            break;
    }

    return fc;
}

/*! Classifies the given \a container by returning one of the constants in this
    class.

    \param[in] container Container to classify.

    \return One of the constants in this class.
 */
UInt8
OSBCommonElement::getFCPtrType(const FieldContainerPtr &container)
{
    FieldContainerType &fcType  = container->getType();
    UInt8               ptrType = OSBCommonElement::FCPtrFieldContainer;

    if(fcType.isNode())
    {
        ptrType = OSBCommonElement::FCPtrNode;
    }
    else if(fcType.isNodeCore())
    {
        ptrType = OSBCommonElement::FCPtrNodeCore;
    }
    else if(fcType.isDerivedFrom(Material::getClassType()))
    {
        ptrType = OSBCommonElement::FCPtrMaterial;
    }
    else if(fcType.isDerivedFrom(StateChunk::getClassType()))
    {
        ptrType = OSBCommonElement::FCPtrStateChunk;
    }
    else if(fcType.isAttachment())
    {
        ptrType = OSBCommonElement::FCPtrAttachment;
    }

    return ptrType;
}
