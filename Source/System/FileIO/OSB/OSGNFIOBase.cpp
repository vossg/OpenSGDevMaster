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

UInt32                          NFIOBase::_id = 1;
NFIOBase::fcMap                 NFIOBase::_fcMap;
std::list<NFIOBase::fcInfo>     NFIOBase::_fieldList;

std::list<FieldContainerPtr>    NFIOBase::_fcList;
std::set<UInt32>                NFIOBase::_fcSet;
NFIOBase::IdMap                 NFIOBase::_ids;

UInt16                          NFIOBase::_header_version = 0;
        
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------------- constructors  -----------------------------*/

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

NodePtr NFIOBase::read(std::istream &is, const std::string &options)
{
    _options.init(options);

    _in = new BinaryReadHandler(is);
    
    NodePtr node = NullFC;
    
    FieldContainerPtr fc = readFieldContainer();
    node = cast_dynamic<NodePtr>(fc);
    
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

    std::string hname;
    _in->getValue(hname);
    std::string hoptions;
    _in->getValue(hoptions);
    UInt64 hsize;
    _in->getValue(hsize);

    std::string typeName;
    UInt32 id;
    FieldContainerPtr root = NullFC;
    FieldContainerPtr fc = NullFC;
    
    while(true)
    {
        // read fieldcontainer type.
        _in->getValue(typeName);
        
        if(typeName.empty()) // check for eof.
            break;
        
        // read fieldcontainer id
        _in->getValue(id);

        FDEBUG(("NFIOBase::readFieldContainer %s with id %u\n", typeName.c_str(), id));
    
        // get the reader.
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
            fc = FieldContainerFactory::the()->getContainer((*it).first);

            if(fc != NullFC)
            {
                //fc = (*it).second;

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

            fc = (*i).second;

            if(fc == NullFC)
                return;
        }

        // adds pointer fc to fieldcontainer info._fc in field info._fieldId
        info._fc->pushToField(fc, info._fieldId);
    }
    else
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
                fc = (*i).second;
                if(fc == NullFC)
                    continue;
            }

            // adds pointer fc to fieldcontainer info._fc in field info._fieldId
            info._fc->pushToField(fc, info._fieldId);
        }
    }
}

void NFIOBase::addReadFieldContainer(const FieldContainerPtr &fc, UInt32 id)
{
    _fcMap.insert(std::pair<UInt32, FieldContainerPtr>(id, fc));
}

std::string NFIOBase::readFCFields(const FieldContainerPtr &fc,
                                   const std::string &exclude,
                                   const std::string &endMarkers)
{
    FieldContainerType  &fcType = fc->getType();

    std::string fieldName;
    while(true)
    {
        _in->getValue(fieldName);
        // check for fieldcontainer end marker.
        if(fieldName.empty() || (!endMarkers.empty() &&
                                 endMarkers.find("'" + fieldName + "'") != std::string::npos))
        {
            FDEBUG(("NFIOBase::readFCPtr: found fieldcontainer end marker.\n"));
            break;
        }
        
        std::string fieldType;
        _in->getValue(fieldType);
        UInt32 size;
        _in->getValue(size);
        
        FDEBUG(("NFIOBase::readFCPtr: field: '%s' '%s' %u\n",
                fieldName.c_str(), fieldType.c_str(), size));
        
        const Field *field = fc->getField(fieldName.c_str());
        FieldDescriptionBase *fDesc = fc->getFieldDescription(fieldName.c_str());
        
        BitVector mask;
        UInt32 fieldId = 0;
        if(fDesc != NULL)
        {
            // HACK the 1.0 MaterialChunk had a internal field the 2.0 MaterialChunk
            // has also a internal field but a internal internal field ;-)
            // but fDesc->isInternal() returns false BUG ????
            if(_header_version == 100 && fieldName == "internal" /*fDesc->isInternal()*/)
            {
                FINFO(("NFIOBase::readFCPtr: skipping internal field '%s' with "
                       "type '%s'!\n", fieldName.c_str(),
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
            FWARNING(("NFIOBase::readFCPtr: skipping unknown field '%s' with "
                      "type '%s'!\n", fieldName.c_str(),
                      fieldType.c_str()));
            _in->skip(size);
            continue;
        }
        
        if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
        {
            FDEBUG(("NFIOBase::readFCPtr: skipping field '%s'!\n",
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


void NFIOBase::readSFFieldContainerPtr(const FieldContainerPtr &fc,
                                       UInt32 fieldId, 
                                       const Field *field)
{
    UInt32 id;
    _in->getValue(id);
    _fieldList.push_back(fcInfo(fc, fieldId, id, field));
}


void NFIOBase::readMFFieldContainerPtr(const FieldContainerPtr &fc,
                                       UInt32 fieldId,
                                       const Field *field)
{
    UInt32 noe;
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

    _id = 1;
    _fcList.clear();
    _fcSet.clear();
    _ids.clear();

    initialiseAll();

    // write header
    _out->putValue(std::string(OSGNFIOHEADERID2));
    _out->putValue(std::string(""));
    _out->putValue(std::string(""));
    _out->putValue((UInt64) 0);
    
    std::string typeName = fc->getType().getCName();
    
    _out->putValue(typeName);
    //_out->putValue(fc.getFieldContainerId());
    _out->putValue(OSG::getContainerId(fc));
    
    NFIOFactory::the().get(typeName)->writeFC(fc);

    SceneFileHandler::the()->updateWriteProgress((currentFCCount++ * 100) / fcCount);

    FDEBUG(("NFIOBase::writeFC: writing fclist\n"));
    
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
            
            FDEBUG(("NFIOBase::writeFCPtr: field: '%s' '%s'\n",
                    fDesc->getCName(), fType.getCName()));
            std::string fieldName = fDesc->getCName();
            std::string fieldType = fType.getCName();
            
            if(!exclude.empty() && exclude.find("'" + fieldName + "'") != std::string::npos)
            {
                FDEBUG(("NFIOBase::writeFields: skipping field: '%s'.\n",
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
                _out->putValue(fieldName);
                _out->putValue(fieldType);
                _out->putValue(fc->getBinSize(mask));
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

void NFIOBase::writeSFFieldContainerPtr(SFFieldContainerPtr *field)
{
    writeFCId(field->getValue());
}


void NFIOBase::writeMFFieldContainerPtr(MFFieldContainerPtr *field)
{
    UInt32 noe = field->size();
    _out->putValue(noe);
    for(UInt32 i = 0; i < noe; ++i)
    {
        writeFCId((*(field))[i]);
    }
}

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

NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc,
                         UInt32 fieldId, UInt32 id, const Field *field) :
    _fc(fc),
    _fieldId(fieldId),
    _id(id),
    _field(field),
    _ids()
{
}

NFIOBase::fcInfo::fcInfo(const FieldContainerPtr &fc,
                         UInt32 fieldId, const Field *field) :
    _fc(fc),
    _fieldId(fieldId),
    _id(0),
    _field(field),
    _ids()
{
}

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
