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

#include "OSGOSBRootElement.h"

#include "OSGOSBElementFactory.h"
#include "OSGContainerPtrFuncs.h"

#include "OSGAttachmentContainer.h"
#include "OSGAttachment.h"
#include "OSGFieldContainerSFields.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBRootElement                                                         */
/*-------------------------------------------------------------------------*/

/*! \class OSG::OSBRootElement
    The root element is different from the other elements for it is not
    responsible for loading a certain type of FieldContainer but instead holds
    the shared state of the OSB IO subsystem. All elements (including the
    root element itself) have a pointer to it and can access the shared state
    through it.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBRootElement>
    OSBRootElement::_regHelper =
        OSBElementRegistrationHelper<OSBRootElement>("RootElement");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

/*! Constructor.
 */
OSBRootElement::OSBRootElement(OSBRootElement */* root */)
    : Inherited(this, Inherited::OSGOSBHeaderVersion200)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

/*! Destructor.
 */
OSBRootElement::~OSBRootElement(void)
{
    // nothing to do.
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

/*! Initializes this root element for a read operation from \a inStream.
    This must be called before OSBRootElement::read(const std::string&).

    \param[in] inStream Stream to read data from.
 */
void
OSBRootElement::initialiseRead(std::istream &inStream)
{
    _readHandler = new BinaryReadHandler(inStream);

    _elements     .clear();
    _readIdMap    .clear();
    _readPtrFields.clear();
}

/*! Performs clean up tasks after a read operation. This must be called after
    OSBRootElement::postRead(void).
 */
void
OSBRootElement::terminateRead(void)
{
    ElementListIt eI = editElementList().begin();
    ElementListIt eE = editElementList().end  ();

    for(; eI != eE; ++eI)
    {
        OSBElementFactory::the()->release(*eI);
    }

    _elements     .clear();
    _readIdMap    .clear();
    _readPtrFields.clear();
    
    delete _readHandler;
    _readHandler = 0;
}

/*! Reads from the stream set by a preceding call to initualiseRead. Since the
    root element is the first one created it reads the file header and
    creates the elements to read the data following the header.

    \param[in] typeName The argument is ignored.
 */
void
OSBRootElement::read(const std::string &/*typeName*/)
{
    FDEBUG(("OSBRootElement::read\n"));

    BinaryReadHandler *rh           = getReadHandler();
    std::string        headerMarker;

    rh->getValue(headerMarker);

    if(headerMarker == OSGOSB_HEADER_ID_1)
    {
        FDEBUG(("OSBRootElement::read: Header version: [%u]\n",
                OSGOSBHeaderVersion100));
        setHeaderVersion(OSGOSBHeaderVersion100);
    }
    else if(headerMarker == OSGOSB_HEADER_ID_2)
    {
        FDEBUG(("OSBRootElement::read: Header version: [%u]\n",
                OSGOSBHeaderVersion200));
        setHeaderVersion(OSGOSBHeaderVersion200);
    }
//     else if(headerMarker == OSGOSB_HEADER_ID_201)
//     {
//         FDEBUG(("OSBRootElement::read: Header version: [%u]\n",
//                 OSGOSBHeaderVersion201));
//         setHeaderVersion(OSGOSBHeaderVersion201);
//     }
    else
    {
        FWARNING(("OSBRootElement::read: Unrecognized file header, could not "
                  "load file.\n"));
        return;
    }

    std::string headerName;
    rh->getValue(headerName);
    std::string headerOptions;
    rh->getValue(headerOptions);
    UInt64 fileSize;
    rh->getValue(fileSize);

    FDEBUG(("OSBRootElement::read: headerName: [%s]\n",
            headerName.c_str()));
    FDEBUG(("OSBRootElement::read: headerOptions: [%s]\n",
            headerOptions.c_str()));
    FDEBUG(("OSBRootElement::read: fileSize: [%u]\n",
            fileSize));

    std::string     fcTypeName;
    UInt32          fcIdFile;    // id used in the file
    UInt32          fcIdSystem;  // id used in the system
    OSBElementBase *elem;

    while(true)
    {
        if(!readFieldContainerHeader(fcTypeName, fcIdFile))
            break;

        elem = OSBElementFactory::the()->acquire(fcTypeName, this);
        elem->read(fcTypeName);

        if(elem->getContainer() != NullFC)
        {
            fcIdSystem = elem->getContainer()->getId();

            FDEBUG(("OSBRootElement::read: fcIdFile: [%u] fcIdSystem: [%u]\n",
                    fcIdFile, fcIdSystem));

            editIdMap().insert(
                FieldContainerIdMap::value_type(fcIdFile, fcIdSystem));

            if(getContainer() == NullFC)
            {
                setContainer(elem->getContainer());
            }

            editElementList().push_back(elem);
        }
    }
}

/*! Performs post processing for all elements created during the previous
    call to read.
    Specifically all these elements have their postRead function called and
    afterwards pointer field remapping is performed. This process fills all
    fields that hold pointers to FieldContainers with the correct values.
 */
void
OSBRootElement::postRead(void)
{
    FDEBUG(("OSBRootElement::postRead\n"));

    ElementListConstIt elemIt  = getElementList().begin();
    ElementListConstIt elemEnd = getElementList().end  ();

    for(; elemIt != elemEnd; ++elemIt)
    {
        (*elemIt)->postRead();
    }

    dumpIdMap();

    PtrFieldListConstIt ptrFieldIt  = getPtrFieldList().begin();
    PtrFieldListConstIt ptrFieldEnd = getPtrFieldList().end  ();

    for(; ptrFieldIt != ptrFieldEnd; ++ptrFieldIt)
    {
        mapPtrField(*ptrFieldIt);
    }
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

/*! Initializes this root element for a write operation to \a outStream.
    This must be called before
    OSBRootElement::preWrite(const FieldContainerPtr&).

    \param[in] outStream Stream to write data to.
 */
void
OSBRootElement::initialiseWrite(std::ostream &outStream)
{
    _writeHandler = new BinaryWriteHandler(outStream);

    _writeFCList.clear();
    _writeIdSet .clear();
}

/*! Performs clean up tasks after a write operation. This must be called after
    OSBRootElement::write(void).
 */
void
OSBRootElement::terminateWrite(void)
{
    ElementListIt eI = editElementList().begin();
    ElementListIt eE = editElementList().end  ();

    for(; eI != eE; ++eI)
    {
        OSBElementFactory::the()->release(*eI);
    }
    
    _elements   .clear();
    _writeFCList.clear();
    _writeIdSet .clear();

    _writeHandler->flush();

    delete _writeHandler;
    _writeHandler = 0;
}

/*! Collects all containers that are reachable from \a fc and schedules them
    for writing. For each container an approriate element is created and
    its preWrite method is called, thus recursively discovering all reachable
    containers.

    \param[in] fc FieldContainer that is inspected for reachable containers.
 */
void
OSBRootElement::preWrite(const FieldContainerPtr &fc)
{
    FDEBUG(("OSBRootElement::preWrite\n"));

    if(fc == NullFC)
        return;

    std::string     typeName = fc->getType().getCName();
    OSBElementBase *elem     = OSBElementFactory::the()->acquire(
        typeName, this);

    editElementList().push_back(elem);
    elem->setContainer(fc);
    elem->preWrite    (fc);
}

/*! Writes the containers collected with the previous call to preWrite to the
    stream set by initialiseWrite.
    First the file header is written, then for each element created during
    preWrite the write function is called.
 */
void
OSBRootElement::write(void)
{
    FDEBUG(("OSBRootElement::write\n"));

    BinaryWriteHandler *wh = getWriteHandler();

    wh->putValue(OSGOSB_HEADER_ID_2    );    // version
    wh->putValue(std::string("")       );    // name
    wh->putValue(std::string("")       );    // options
    wh->putValue(static_cast<UInt64>(0));    // size

    ElementListConstIt elemIt  = getElementList().begin();
    ElementListConstIt elemEnd = getElementList().end  ();

    for(; elemIt != elemEnd; ++elemIt)
    {
        writeFieldContainerHeader((*elemIt)->getContainer());
        (*elemIt)->write();
    }
}

/*-------------------------------------------------------------------------*/
/* Helper methods                                                          */

/*! Fills the "pointer field" described by \a ptrField with the correct
    pointers.

    \param[in] ptrField Field to fill.
 */
void
OSBRootElement::mapPtrField(const PtrFieldInfo &ptrField)
{
    FDEBUG(("OSBRootElement::mapPtrField\n"));

    const FieldContainerIdMap        &idMap = getIdMap();
    PtrFieldInfo::PtrIdStoreConstIt   idIt  = ptrField.beginIdStore();
    PtrFieldInfo::PtrIdStoreConstIt   idEnd = ptrField.endIdStore  ();

    PtrFieldInfo::BindingStoreConstIt bindingIt  = ptrField.beginBindingStore();
    PtrFieldInfo::BindingStoreConstIt bindingEnd = ptrField.endBindingStore  ();

    FieldContainerIdMapConstIt idMapIt;
    FieldContainerIdMapConstIt idMapEnd = idMap.end();

    if(bindingIt != bindingEnd)
    {
        AttachmentPtr          att    = NullFC;
        AttachmentContainerPtr attCon =
            dynamic_cast<AttachmentContainerPtr>(ptrField.getContainer());

        for(; (idIt != idEnd) && (bindingIt != bindingEnd); ++idIt, ++bindingIt)
        {
            if(*idIt != 0)
            {
                idMapIt = idMap.find(*idIt);

                if(idMapIt != idMapEnd)
                {
                    att = dynamic_cast<AttachmentPtr>(
                        FieldContainerFactory::the()->getContainer(
                            idMapIt->second));
                }
                else
                {
                    FWARNING(("OSBRootElement::mapPtrField: could not find "
                              "FieldContainer with id [%u]\n", *idIt));
                    att = NullFC;
                }
            }
            else
            {
                att = NullFC;
            }

            FDEBUG(("OSBRootElement::mapPtrField: adding attchment [%u] [%u]\n",
                    att->getType().getGroupId(), *bindingIt));

            attCon->addAttachment(att, *bindingIt);
        }
    }
    else
    {
        FieldContainerPtr  fc       = NullFC;
        FieldContainerPtr  fieldCon = ptrField.getContainer();
        UInt32             fieldId  = ptrField.getFieldId();

        EditFieldHandlePtr fHandle  = fieldCon->editField(fieldId);

        FieldContainerPtrSFieldBase::EditHandlePtr pSFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::EditHandle>(
                    fHandle);

        FieldContainerPtrMFieldBase::EditHandlePtr pMFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::EditHandle>(
                    fHandle);

        for(; idIt != idEnd; ++idIt)
        {
            if(*idIt != 0)
            {
                idMapIt = idMap.find(*idIt);

                if(idMapIt != idMapEnd)
                {
                    fc = FieldContainerFactory::the()->getContainer(
                        idMapIt->second);
                }
                else
                {
                    FWARNING(("OSBRootElement::mapPtrField: could not find "
                              "FieldContainer with id [%u]\n", *idIt));
                    fc = NullFC;
                }
            }
            else
            {
                fc = NullFC;
            }

            if(pSFHandle != NULL && pSFHandle->isValid())
            {
                pSFHandle->setValue(fc);
            }
            else if(pMFHandle != NULL && pMFHandle->isValid())
            {
                pMFHandle->add(fc);
            }
        }
    }
}

/*! Prints the map showing the relation between FieldContainer ids in the file
    and the system, which is used by mapPtrField to fill in the right pointers.
 */
void
OSBRootElement::dumpIdMap(void) const
{
    FDEBUG(("OSBRootElement::dumpIdMap\n"));

    FieldContainerIdMapConstIt mapIt  = getIdMap().begin();
    FieldContainerIdMapConstIt mapEnd = getIdMap().end  ();

    for(; mapIt != mapEnd; ++mapIt)
    {
        FDEBUG(("  file id  %u  ->  %u  system id\n", mapIt->first, mapIt->second));
    }
}
