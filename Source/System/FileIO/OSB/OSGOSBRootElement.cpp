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
OSBRootElement::OSBRootElement(OSBRootElement * /* root */)
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

/*! Reads from the stream set by a preceding call to initialiseRead. Since the
    root element is the first one created it reads the file header and
    creates the elements to read the data following the header.

    \param[in] typeName The argument is ignored.
 */
void
OSBRootElement::read(const std::string &/*typeName*/)
{
    OSG_OSB_LOG(("OSBRootElement::read\n"));

    BinaryReadHandler *rh           = getReadHandler();
    std::string        headerMarker;

    rh->getValue(headerMarker);

    if(headerMarker == OSGOSB_HEADER_ID_1)
    {
        OSG_OSB_LOG(("OSBRootElement::read: Header version: [%u]\n",
                OSGOSBHeaderVersion100));
        setHeaderVersion(OSGOSBHeaderVersion100);
    }
    else if(headerMarker == OSGOSB_HEADER_ID_2)
    {
        OSG_OSB_LOG(("OSBRootElement::read: Header version: [%u]\n",
                OSGOSBHeaderVersion200));
        setHeaderVersion(OSGOSBHeaderVersion200);
    }
//     else if(headerMarker == OSGOSB_HEADER_ID_201)
//     {
//         OSG_OSB_LOG(("OSBRootElement::read: Header version: [%u]\n",
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

    OSG_OSB_LOG(("OSBRootElement::read: headerName: [%s]\n",
            headerName.c_str()));
    OSG_OSB_LOG(("OSBRootElement::read: headerOptions: [%s]\n",
            headerOptions.c_str()));
    OSG_OSB_LOG(("OSBRootElement::read: fileSize: [%u]\n",
            fileSize));

    std::string     fcTypeName;
    UInt32          fcIdFile;    // id used in the file
    UInt32          fcIdSystem;  // id used in the system
    OSBElementBase *elem;

    while(true)
    {
        if(!readFieldContainerHeader(fcTypeName, fcIdFile))
            break;

        OSG_OSB_LOG(("OSBRootElement::read: fcTypeName [%s] fcIdFile: [%u]\n",
                fcTypeName.c_str(), fcIdFile));

        elem = OSBElementFactory::the()->acquire(fcTypeName, this);
        elem->setFCIdFile(fcIdFile  );
        elem->read       (fcTypeName);

        if(elem->getContainer() != NULL)
        {
            fcIdSystem = elem->getContainer()->getId();

            OSG_OSB_LOG(("OSBRootElement::read: fcIdFile: [%u] fcIdSystem: [%u]\n",
                    fcIdFile, fcIdSystem));

            editIdMap().insert(
                FieldContainerIdMap::value_type(fcIdFile, fcIdSystem));

            if(getContainer() == NULL)
            {
                setContainer(elem->getContainer());
            }

            editElementList().push_back(elem                          );
            editIdElemMap  ().insert   (std::make_pair(fcIdFile, elem));
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
    OSG_OSB_LOG(("OSBRootElement::postRead\n"));

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
OSBRootElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBRootElement::preWrite\n"));

    if(fc == NULL)
        return;

    const std::string    &typeName = fc->getType().getName();
          OSBElementBase *elem     = OSBElementFactory::the()->acquire(
        typeName, this);

    editElementList().push_back(elem);
    elem->setContainer(fc         );
    elem->setFCIdFile (fc->getId());
    elem->preWrite    (fc         );
}

/*! Writes the containers collected with the previous call to preWrite to the
    stream set by initialiseWrite.
    First the file header is written, then for each element created during
    preWrite the write function is called.
 */
void
OSBRootElement::write(void)
{
    OSG_OSB_LOG(("OSBRootElement::write\n"));

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
    OSG_OSB_LOG(("OSBRootElement::mapPtrField\n"));

    PtrFieldInfo::PtrIdStoreConstIt   idIt       = ptrField.beginIdStore();
    PtrFieldInfo::PtrIdStoreConstIt   idEnd      = ptrField.endIdStore  ();

    PtrFieldInfo::BindingStoreConstIt bindingIt  = ptrField.beginBindingStore();
    PtrFieldInfo::BindingStoreConstIt bindingEnd = ptrField.endBindingStore  ();

    const FieldContainerIdMap        &idMap      = getIdMap();
          FieldContainerIdMapConstIt  idMapIt;
          FieldContainerIdMapConstIt  idMapEnd   = idMap.end();
        
    if(bindingIt != bindingEnd)
    {
        if(ptrField.getHandledField() == true)
        {
            FieldContainer    *fieldCon = ptrField.getContainer();
            UInt32             fieldId  = ptrField.getFieldId();
        
            EditFieldHandlePtr fHandle  = fieldCon->editField(fieldId);

            EditMapFieldHandlePtr sfMapField =
                boost::dynamic_pointer_cast<EditMapFieldHandle>(fHandle);

            if(sfMapField == NULL || sfMapField->isValid() == false)
                return;

            sfMapField->fillFrom(ptrField.getBindingStore(),
                                 ptrField.getIdStore     (),
                                 idMap);
        }
        else
        {
            Attachment          *att    = NULL;
            AttachmentContainer *attCon =
                dynamic_cast<AttachmentContainer *>(ptrField.getContainer());
            
            for(; (idIt != idEnd) && (bindingIt != bindingEnd); ++idIt, 
                                                                ++bindingIt)
            {
                if(*idIt != 0)
                {
                    idMapIt = idMap.find(*idIt);
                    
                    if(idMapIt != idMapEnd)
                    {
                        att = dynamic_cast<Attachment *>(
                            FieldContainerFactory::the()->getContainer(
                                idMapIt->second));
                    }
                    else
                    {
                        FWARNING(("OSBRootElement::mapPtrField: could not find "
                                  "FieldContainer with id [%u]\n", *idIt));
                        att = NULL;
                    }
                }
                else
                {
                    att = NULL;
                }
                
                if(att != NULL)
                {
                    OSG_OSB_LOG(("OSBRootElement::mapPtrField: adding "
                            "attchment [%u] [%u]\n",
                            att->getType().getGroupId(), *bindingIt));
                }

                attCon->addAttachment(att, *bindingIt);
            }
        }
    }
    else
    {
        FieldContainer    *fc       = NULL;
        FieldContainer    *fieldCon = ptrField.getContainer();
        UInt32             fieldId  = ptrField.getFieldId();
        
        EditFieldHandlePtr fHandle  = fieldCon->editField(fieldId);
        
        FieldContainerPtrSFieldBase::EditHandlePtr pSFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::EditHandle>(fHandle);
            
        FieldContainerPtrMFieldBase::EditHandlePtr pMFHandle = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::EditHandle>(fHandle);
        
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
                              "FieldContainer with (file) id [%u]\n", *idIt));
                    fc = NULL;
                }
            }
            else
            {
                fc = NULL;
            }
            
            if(pSFHandle != NULL && pSFHandle->isValid())
            {
                pSFHandle->set(fc);
            }
            else if(pMFHandle != NULL && pMFHandle->isValid())
            {
                pMFHandle->add(fc);
            }
            else
            {
                FWARNING(("OSBRootElement::mapPtrField: FieldHandles invalid, "
                          "can not set pointer - target fc [%u] fieldId [%u] file id [%u] system id [%u]\n",
                          (fc != NULL ? fc->getId() : 0), fieldId, *idIt, (idMapIt != idMapEnd ? idMapIt->second : 0)));
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
    OSG_OSB_LOG(("OSBRootElement::dumpIdMap\n"));

    FieldContainerIdMapConstIt mapIt  = getIdMap().begin();
    FieldContainerIdMapConstIt mapEnd = getIdMap().end  ();

    for(; mapIt != mapEnd; ++mapIt)
    {
        OSG_OSB_LOG(("  file id  %u  ->  %u  system id\n", mapIt->first, mapIt->second));
    }
}
