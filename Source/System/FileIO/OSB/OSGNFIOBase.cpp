/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

// Header format
// "OpenSG binary V1.0"(std::string)<Name>(string)<Options>(string)<Size>(UInt64)
// For each FieldContainer:
// <FieldContainerType>(std::string)<FieldContainerId>(UInt32)
// "" empty FieldContainerType string as file endmarker.

#include <OSGConfig.h>
#include "OSGNFIOBase.h"

#include <OSGSField.h>
#include <OSGMField.h>
#include "OSGFieldContainerAttachment.h"
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGSceneFileHandler.h>

#include <OSGLog.h>

#include "OSGNFIOFactory.h"

#define OSGNFIOHEADERID1 "OpenSG binary V1.0"
#define OSGNFIOHEADERID2 "OpenSG binary V2.0"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NFIOBase
           Base class for native file io.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

NFIOOptions                     NFIOBase::_options;

NFIOBase::BinaryReadHandler     *NFIOBase::_in = NULL;
NFIOBase::BinaryWriteHandler    *NFIOBase::_out = NULL;

//UInt32                          NFIOBase::_id = 1;
NFIOBase::fcMap                 NFIOBase::_fcMap;
std::list<NFIOBase::fcInfo>     NFIOBase::_fieldList;

std::list<FieldContainerPtr>    NFIOBase::_fcList;
std::set<UInt32>                NFIOBase::_fcSet;
//NFIOBase::IdMap                 NFIOBase::_ids;

UInt16                          NFIOBase::_header_version = 0;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

/*! Constructor.
* Automatically registers this handler with the NFIOFactory.
*/
NFIOBase::NFIOBase(const char *name) :
    _version(200)
{
    NFIOFactory::the().add(name, this);
}

/*------------------------------ destructor -------------------------------*/

NFIOBase::~NFIOBase()
{
    NFIOFactory::the().sub(this);
}

/*! Read nodes from an istream.
* This is the main entry point for loading data with the osb loader.
*/
NodePtr NFIOBase::read(std::istream &is, const std::string &options)
{
    _options.init(options);

    _in = new BinaryReadHandler(is);

    NodePtr node = NullFC;

    FieldContainerPtr fc = readFieldContainer();
    node = dynamic_cast<NodePtr>(fc);

    delete _in;

    return node;
}

bool NFIOBase::write(const NodePtr &node, std::ostream &os,
                     const std::string &options)
{
    _options.init(options);

    _out = new BinaryWriteHandler(os);

    writeFieldContainer(node);

    _out->flush();
    delete _out;

    return true;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                            Options                                      *
\***************************************************************************/

const NFIOOptions &NFIOBase::getOptions(void)
{
    return _options;
}

/***************************************************************************\
 *                            Init                                         *
\***************************************************************************/

void NFIOBase::initialiseAll(void)
{
    NFIOFactory::registryMap fmap = NFIOFactory::the().getMap();
    for(NFIOFactory::registryMap::iterator it = fmap.begin();it != fmap.end();++it)
        (*it).second->initialise();
}

void NFIOBase::terminateAll(void)
{
    NFIOFactory::registryMap fmap = NFIOFactory::the().getMap();
    for(NFIOFactory::registryMap::iterator it = fmap.begin();it != fmap.end();++it)
        (*it).second->terminate();
}

void NFIOBase::initialise(void)
{
}

void NFIOBase::terminate(void)
{
}

/***************************************************************************\
 *                            Reader                                       *
\***************************************************************************/

/*! Main reader method.
* Reads an entire "file" of binary data from the current binary reader.
*/
FieldContainerPtr NFIOBase::readFieldContainer(void)
{
    FDEBUG(("NFIOBase::readFieldContainer\n"));

    _fieldList.clear();
    _fcMap.clear();

    // read header
    std::string hid;
    _in->getValue(hid);

    _header_version = 0;

    if(hid == OSGNFIOHEADERID1)
        _header_version = 100;
    else if (hid == OSGNFIOHEADERID2)
        _header_version = 200;
    else
    {
        FWARNING(("NFIOBase::readFieldContainer : Couldn't load file "
                  "this is not a OpenSG binary file!\n"));
        return NullFC;
    }

    initialiseAll();

    // Read the rest of the header
    std::string hname;
    _in->getValue(hname);           // Name
    std::string hoptions;
    _in->getValue(hoptions);        // Options string
    UInt64 hsize;
    _in->getValue(hsize);           // Size value

    std::string typeName;
    UInt32 id;
    FieldContainerPtr root = NullFC;
    FieldContainerPtr fc = NullFC;

    // Keep reading field containers until end of file
    while(true)
    {
        // read fieldcontainer type name (string)
        _in->getValue(typeName);

        if(typeName.empty()) // check for eof marker
            break;

        // read fieldcontainer id
        _in->getValue(id);

        FDEBUG(("NFIOBase::readFieldContainer %s with id %u\n", typeName.c_str(), id));

        // get the reader and read in field container
        fc = NFIOFactory::the().get(typeName)->readFC(typeName);

        if(fc != NullFC)
            addReadFieldContainer(fc, id);

        if(root == NullFC) // first fc is the root node.
        {
            root = fc;
        }
        SceneFileHandler::the()->updateReadProgress();
    }

    SceneFileHandler::the()->updateReadProgress();

    // process all SF/MFFieldContainerPtr
    for(std::list<fcInfo>::iterator i = _fieldList.begin();
        i != _fieldList.end(); ++i)
    {
        chargeFieldPtr(*i);
    }

    //Thread::getCurrentChangeList()->commitChanges();

    // for the 1.0 to 2.0 conversion we need to call postProcess
    if(_header_version == 100)
    {
        for(fcMap::iterator it = _fcMap.begin();it != _fcMap.end(); ++it)
        {
            // we use here the fieldcontainer id as postProcessFC can
            // delete a field container that is still to be processed
            // (geometry indices in my case)
            fc = FieldContainerFactory::the()->getContainer((*it).second);

            if(fc != NullFC)
            {
                FieldContainerType  &fcType = fc->getType();
                typeName = fcType.getCName();
                NFIOFactory::the().get(typeName)->postProcessFC(fc);
            }
        }
    }

    _fieldList.clear();
    _fcMap.clear();

    terminateAll();

    SceneFileHandler::the()->updateReadProgress(100);

    return root;
}

/*! Remap the fcptr's in the field wrapped by info. */
void NFIOBase::chargeFieldPtr(const fcInfo &info)
{
    FieldContainerType  &fcType = info._fc->getType();
    const Field *field = info._field;

    if(!info.isMultiField())
    {
        FieldContainerPtr fc = NullFC;

        UInt32 id = info._id;

        if(id != 0)
        {
            fcMap::iterator i = _fcMap.find(id);

            if(i == _fcMap.end())
            {
                FWARNING(("NFIOBase::chargeFieldPtr: couldn't find "
                          "FieldContainer with id %u\n", id));
                return;
            }

            fc = FieldContainerFactory::the()->getContainer((*i).second);

            if(fc == NullFC)
                return;
        }

        // adds pointer fc to fieldcontainer info._fc in field info._fieldId
        info._fc->pushToField(fc, info._fieldId);
    }
    else    // MField case
    {
        if(info._ids.empty())
            return;

        for(std::vector<UInt32>::const_iterator i = info._ids.begin();
            i != info._ids.end(); ++i)
        {
            UInt32 id = *i;
            FieldContainerPtr fc = NullFC;
            if(id != 0)
            {
                fcMap::iterator i = _fcMap.find(id);
                if(i == _fcMap.end())
                {
                    FWARNING(("NFIOBase::chargeFieldPtr: couldn't find "
                              "FieldContainer with id %u\n", id));
                    continue;
                }
                fc = FieldContainerFactory::the()->getContainer((*i).second);
                if(fc == NullFC)
                    continue;
            }

            // adds pointer fc to fieldcontainer info._fc in field info._fieldId
            info._fc->pushToField(fc, info._fieldId);
        }
    }
}

/*! Called for every fc added.
* \param fc   The field container instantiated.
* \param id   The id the fc used in the original file.
*
* Updates the _fcMap to allow fcptr remapping.
*/
void NFIOBase::addReadFieldContainer(const FieldContainerPtr &fc, UInt32 id)
{
    _fcMap.insert(std::pair<UInt32, UInt32>(id, OSG::getContainerId(fc)));
}

/*!
* Read a set of fields from the current in stream into fc.
* \param fc  The field container to read into
* \param exclude List of fieldnames to exclude while reading
*                in the format of "'field_name' 'other_field'"
* \param endMarkers List of end markers besides an empty string.
*                in the format of "'marker' 'other_marker'"
* \returns Name of last field read (or field marker).  This combined
*          with endMarkers can allow for partial reading of fields.
*/
std::string NFIOBase::readFCFields(const FieldContainerPtr &fc,
                                   const std::string &exclude,
                                   const std::string &endMarkers)
{
    FieldContainerType  &fcType = fc->getType();

    // Read fields until end marker is found
    std::string fieldName;
    while(true)
    {
        _in->getValue(fieldName);
        // check for fieldcontainer end marker.
        if(fieldName.empty() || (!endMarkers.empty() &&
                                 endMarkers.find("'" + fieldName + "'") != std::string::npos))
        {
            FDEBUG(("NFIOBase::readFCFields: found fieldcontainer end marker.\n"));
            break;
        }

        std::string fieldType;
        _in->getValue(fieldType);
        UInt32 size;
        _in->getValue(size);

        FDEBUG(("NFIOBase::readFCFields: field: '%s' '%s' %u\n",
                fieldName.c_str(), fieldType.c_str(), size));

        // Get field and field description
        const Field *field = fc->getField(fieldName.c_str());
        FieldDescriptionBase *fDesc = fc->getFieldDescription(fieldName.c_str());

        // Lookup the mask and id for the field
        BitVector mask;
        UInt32 fieldId = 0;
        if(fDesc != NULL)
        {
            // HACK the 1.0 MaterialChunk had a internal field the 2.0 MaterialChunk
            // has also a internal field but a internal internal field ;-)
            // but fDesc->isInternal() returns false BUG ????
            if(_header_version == 100 && fieldName == "internal" /*fDesc->isInternal()*/)
            {
                FINFO(("NFIOBase::readFCFields: skipping internal field '%s' "
                       "with type '%s'!\n", fieldName.c_str(),
                       fieldType.c_str()));
                _in->skip(size);
                continue;
            }
            else
            {
                mask = fDesc->getFieldMask();
                fieldId = fDesc->getFieldId();
            }
        }
        else
        {
            FWARNING(("NFIOBase::readFCFields: skipping unknown field '%s' with "
                      "type '%s'!\n", fieldName.c_str(),
                      fieldType.c_str()));
            _in->skip(size);
            continue;
        }

        if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
        {
            FDEBUG(("NFIOBase::readFCFields: skipping field '%s'!\n",
                    fieldName.c_str()));
            _in->skip(size);
            continue;
        }

        // need to test this before the Ptr's as
        // SFFieldContainerAttachmentPtrMap contains also the Ptr string!
        if(!strcmp(fieldName.c_str(), "attachments"))
        {
            readMFFieldContainerPtr(fc, fieldId, field);
        }
        else if(strstr(fieldType.c_str(), "Ptr") != NULL)
        {
            if(fieldType[0] == 'S' && fieldType[1] == 'F') // single field
            {
                readSFFieldContainerPtr(fc, fieldId, field);
            }
            else if(fieldType[0] == 'M' && fieldType[1] == 'F') // multi field
            {
                readMFFieldContainerPtr(fc, fieldId, field);
            }
        }
        else
        {
            fc->copyFromBin(*_in, mask);
        }
    }
    return fieldName;
}

/*! Read entry for an SFField with a fc ptr. */
void NFIOBase::readSFFieldContainerPtr(const FieldContainerPtr &fc,
                                       UInt32 fieldId,
                                       const Field *field)
{
    UInt32 id;
    _in->getValue(id);
    _fieldList.push_back(fcInfo(fc, fieldId, id, field));
}

/*! Read entry for an MFField with fc ptrs. */
void NFIOBase::readMFFieldContainerPtr(const FieldContainerPtr &fc,
                                       UInt32 fieldId,
                                       const Field *field)
{
    UInt32 noe;            // number of entries
    _in->getValue(noe);
    _fieldList.push_back(fcInfo(fc, fieldId, field));
    fcInfo &info = _fieldList.back();
    UInt32 id;
    for(UInt32 j=0;j<noe;++j)
    {
        _in->getValue(id);
        info._ids.push_back(id);
    }
}


/***************************************************************************\
 *                            Writer                                       *
\***************************************************************************/

/*! Return a count of all the fc's that are going to be written. */
void NFIOBase::getFCCount(const FieldContainerPtr &fc, UInt32 &count)
{
    if(fc == NullFC)
        return;

    if(_fcSet.count(OSG::getContainerId(fc)) > 0)
        return;

    _fcSet.insert(OSG::getContainerId(fc));
    ++count;

    FieldContainerType  &fcType = fc->getType();

    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescriptionBase *fDesc     = fc->getFieldDescription(i);
        const Field          *fieldPtr  = fc->getField(i);
        const FieldType      &fType     = fDesc->getFieldType();

        if(!fDesc->isInternal())
        {
            // ignore node volume
            if(fcType == Node::getClassType() &&
               fDesc->getFieldMask() == Node::VolumeFieldMask)
            {
                continue;
            }

            FDEBUG(("NFIOBase::getFCCount: field: '%s' '%s'\n",
                    fDesc->getCName(), fType.getCName()));

            if(fType.getContentType().isDerivedFrom(
               FieldTraits<FieldContainerPtr>::getType()) == true)
            {
                if(fType.getCardinality() == FieldType::SINGLE_FIELD)
                {
                    getFCCount(((SFFieldContainerPtr *) fieldPtr)->getValue(), count);
                }
                else
                {
                    MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                    UInt32 noe = mfield->size();
                    for(UInt32 i = 0; i < noe; ++i)
                    {
                        getFCCount((*(mfield))[i], count);
                    }
                }

            }
            else if(!strcmp(fDesc->getCName(), "attachments"))
            {
                SFFieldContainerAttachmentPtrMap *amap = (SFFieldContainerAttachmentPtrMap *) fieldPtr;

                FieldContainerAttachmentMap::const_iterator   mapIt = amap->getValue().begin();
                FieldContainerAttachmentMap::const_iterator   mapEnd = amap->getValue().end();

                UInt32 noe = amap->getValue().size();

                for(; mapIt != mapEnd; ++mapIt)
                {
                    getFCCount(mapIt->second, count);
                }
            }
        }
    }
}

/*! Main writer method.
* \param fc   Field container to write.
*
* Writes contents of fc and all fc's reachable from fc.
*/
void NFIOBase::writeFieldContainer(const FieldContainerPtr &fc)
{
    FDEBUG(("NFIOBase::writeFieldContainer\n"));

    if(fc == NullFC)
        return;

    SceneFileHandler::the()->updateWriteProgress(0);

    // need this for the progress calculation.
    UInt32 fcCount = 0;
    UInt32 currentFCCount = 0;
    if(SceneFileHandler::the()->getWriteProgressCB() != NULL)
    {
        _fcSet.clear();
        getFCCount(fc, fcCount);
    }

    if(fcCount == 0)
        fcCount = 1;

    //_id = 1;
    _fcList.clear();
    _fcSet.clear();
    //_ids.clear();

    initialiseAll();

    // write header
    _out->putValue(std::string(OSGNFIOHEADERID2));    // version
    _out->putValue(std::string(""));                  // name
    _out->putValue(std::string(""));                  // options
    _out->putValue((UInt64) 0);                       // size

    std::string typeName = fc->getType().getCName();

    // Write the first field container
    _out->putValue(typeName);
    _out->putValue(OSG::getContainerId(fc));

    NFIOFactory::the().get(typeName)->writeFC(fc);

    SceneFileHandler::the()->updateWriteProgress((currentFCCount++ * 100) / fcCount);

    FDEBUG(("NFIOBase::writeFieldContainer: writing fclist\n"));

    // Write the rest of the fc's
    // Note: list grows in reachability behind the scenes as side-effect of writeFC
    FieldContainerPtr lfc;
    for(std::list<FieldContainerPtr>::iterator i = _fcList.begin();
        i != _fcList.end(); ++i)
    {
        lfc = *i;
        typeName = lfc->getType().getCName();
        _out->putValue(typeName);
        //_out->putValue(lfc.getFieldContainerId());
        _out->putValue(OSG::getContainerId(lfc));
        NFIOFactory::the().get(lfc->getType().getCName())->writeFC(lfc);
        SceneFileHandler::the()->updateWriteProgress((currentFCCount++ * 100) / fcCount);
    }

    // write eof marker
    writeEndMarker();

    _fcList.clear();
    _fcSet.clear();

    terminateAll();
    SceneFileHandler::the()->updateWriteProgress(100);
}

/*! Write all fc fields to binary stream.
* \param fc  The fc to write.
* \param exclude   Fields to exclude from writing
* \param endMarker Wether or not to write an end marker.
*/
void NFIOBase::writeFCFields(const FieldContainerPtr &fc,
                             const std::string &exclude,
                             bool endMarker)
{
    FieldContainerType  &fcType = fc->getType();

    //go through all fields
    for(UInt32 i = 1; i <= fcType.getNumFieldDescs(); ++i)
    {
        FieldDescriptionBase *fDesc = fc->getFieldDescription(i);
        const Field               *fieldPtr = fc->getField(i);
        const FieldType     &fType = fDesc->getFieldType();
        BitVector           mask = fDesc->getFieldMask();

        if(!fDesc->isInternal())
        {
            // ignore node volume
            if(fcType == Node::getClassType() &&
               mask == Node::VolumeFieldMask)
            {
                continue;
            }

            FDEBUG(("NFIOBase::writeFCFields: field: '%s' '%s'\n",
                    fDesc->getCName(), fType.getCName()));
            std::string fieldName = fDesc->getCName();
            std::string fieldType = fType.getCName();

            if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
            {
                FDEBUG(("NFIOBase::writeFCFields: skipping field: '%s'.\n",
                        fieldName.c_str()));
                continue;
            }

            if(fType.getContentType().isDerivedFrom(
               FieldTraits<FieldContainerPtr>::getType()) == true)
            {
                //if(fieldPtr->getCardinality() == FieldType::SINGLE_FIELD)
                if(fType.getCardinality() == FieldType::SINGLE_FIELD)
                {
                    _out->putValue(fieldName);
                    _out->putValue(fieldType);
                    _out->putValue(fc->getBinSize(mask));
                    writeSFFieldContainerPtr((SFFieldContainerPtr *) fieldPtr);
                }
                else
                {
                    MFFieldContainerPtr *mfield = (MFFieldContainerPtr *) fieldPtr;
                    if(!mfield->empty())
                    {
                        UInt32 size = sizeof(UInt32) + sizeof(UInt32) * mfield->size();
                        _out->putValue(fieldName);
                        _out->putValue(fieldType);
                        _out->putValue(size);

                        writeMFFieldContainerPtr(mfield);
                    }
                }

            }
            else if(!strcmp(fDesc->getCName(), "attachments"))
            {
                SFFieldContainerAttachmentPtrMap *amap = (SFFieldContainerAttachmentPtrMap *) fieldPtr;

                if(!amap->getValue().empty())
                {
                    UInt32 size = sizeof(UInt32) + sizeof(UInt32) * amap->getValue().size();
                    _out->putValue(fieldName);
                    _out->putValue(fieldType);
                    _out->putValue(size);
                    writeSFAttachmentMap(amap);
                }
            }
            else
            {
                UInt32 size = fc->getBinSize(mask);
                
                FDEBUG(("NFIOBase::writeFCFields: size: %d\n", size));
                
                _out->putValue(fieldName);
                _out->putValue(fieldType);
                _out->putValue(size);
                fc->copyToBin(*_out, mask);
            }

        }
    }

    if(endMarker)
    {
        // write fieldcontainer end marker
        writeEndMarker();
    }
}

/*! Write the information for a single field ptr. */
void NFIOBase::writeSFFieldContainerPtr(SFFieldContainerPtr *field)
{
    writeFCId(field->getValue());
}

/*! Write the information for a mffield ptr. */
void NFIOBase::writeMFFieldContainerPtr(MFFieldContainerPtr *field)
{
    UInt32 noe = field->size();
    _out->putValue(noe);
    for(UInt32 i = 0; i < noe; ++i)
    {
        writeFCId((*(field))[i]);
    }
}

/*! Write the pointers for an attachment map. */
void NFIOBase::writeSFAttachmentMap(SFFieldContainerAttachmentPtrMap *amap)
{
    //AttachmentMap::const_iterator   mapIt = amap->getValue().begin();
    //AttachmentMap::const_iterator   mapEnd = amap->getValue().end();
    FieldContainerAttachmentMap::const_iterator   mapIt = amap->getValue().begin();
    FieldContainerAttachmentMap::const_iterator   mapEnd = amap->getValue().end();

    UInt32 noe = amap->getValue().size();
    _out->putValue(noe);
    for(; mapIt != mapEnd; ++mapIt)
    {
        writeFCId(mapIt->second);
    }
}

void NFIOBase::readEndMarker(void)
{
    // end marker a empty field or fieldcontainer type name.
    std::string endMarker;
    _in->getValue(endMarker);
}

void NFIOBase::writeEndMarker(void)
{
    // end marker a empty field or fieldcontainer type name.
    _out->putValue(std::string(""));
}

void NFIOBase::writeFCId(const FieldContainerPtr &fc)
{
    if(fc == NullFC)
    {
        _out->putValue((UInt32) 0);
        return;
    }

    UInt32 id = OSG::getContainerId(fc); //fc.getFieldContainerId();
    _out->putValue(id);

    if(_fcSet.count(id) == 0)
    {
        _fcSet.insert(id);
        _fcList.push_back(fc);
    }
}

/***************************************************************************\
 *                            PostProcess                                  *
\***************************************************************************/

void NFIOBase::postProcessFC(const FieldContainerPtr &fc)
{
}

/*! Helper method to skip to end of set of FC Fields. */
void NFIOBase::skipFCFields(void)
{
    // skip all fields
    std::string fieldName;
    std::string fieldType;
    UInt32 size;
    while(true)
    {
        _in->getValue(fieldName);
        // check for fieldcontainer end marker.
        if(fieldName.empty())
        {
            FDEBUG(("NFIOBase::skipFCFields: found fieldcontainer end marker.\n"));
            break;
        }

        _in->getValue(fieldType);
        _in->getValue(size);

        _in->skip(size);
    }
}

/*-------------------------------------------------------------------------*/
/*                           fcInfo struct                                 */

/*! Constructor for sfield. */
NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc,
                         UInt32 fieldId, UInt32 id, const Field *field) :
    _fc(fc),
    _fieldId(fieldId),
    _id(id),
    _field(field),
    _ids()
{
}

/*! Constructor for mfield. */
NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc,
                         UInt32 fieldId, const Field *field) :
    _fc(fc),
    _fieldId(fieldId),
    _id(0),
    _field(field),
    _ids()
{
}

/*! Return true if we are pointing to a multi-field. */
bool NFIOBase::fcInfo::isMultiField(void) const
{
    return (_id == 0);
}


/*-------------------------------------------------------------------------*/
/*                              BinaryReadHandler                          */

/*! constructor
 */
NFIOBase::BinaryReadHandler::BinaryReadHandler(std::istream &is) :
    BinaryDataHandler(1),
    _is(is)
{
    _readMemory.resize(8192);
    readBufAdd(&_readMemory[0], _readMemory.size());
}

/*! destructor
 */
NFIOBase::BinaryReadHandler::~BinaryReadHandler(void)
{
}

/*! read
 */
void NFIOBase::BinaryReadHandler::read(MemoryHandle mem, UInt32 size)
{
    _is.read((char *) mem, size);
}

void NFIOBase::BinaryReadHandler::skip(UInt32 size)
{
    if(size == 0)
        return;

    char b;
    for(UInt32 i=0;i<size;++i)
        get((void *) &b, 1);
}

/*-------------------------------------------------------------------------*/
/*                           BinaryWriteHandler                             */

/*! constructor
 */
NFIOBase::BinaryWriteHandler::BinaryWriteHandler(std::ostream &os) :
    BinaryDataHandler(1),
    _os(os)
{
    _writeMemory.resize(8192);
    writeBufAdd(&_writeMemory[0], _writeMemory.size());
}

/*! destructor
 */
NFIOBase::BinaryWriteHandler::~BinaryWriteHandler(void)
{
}

/*! write to binary file
 */
void NFIOBase::BinaryWriteHandler::write(MemoryHandle mem, UInt32 size)
{
    _os.write((const char *) mem, size);
}



/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGNFIOBASE_HEADER_CVSID;
}
