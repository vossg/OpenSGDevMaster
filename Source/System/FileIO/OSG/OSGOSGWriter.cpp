/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGOSGWriter.h"
//#include <OSGAttachment.h>
//#include <OSGSimpleAttachments.h>
//#include "OSGVRMLNodeDescs.h"

#include <OSGAttachmentMapSFields.h>
#include <OSGFieldContainerAttachment.h>

OSG_USING_NAMESPACE

#define WFC

#if 0
#if defined(OSG_WIN32_ICL)
#pragma warning (disable : 383)
#endif

#if defined(OSG_WIN32_ICL)
#pragma warning (default : 383)
#endif
#endif

const UInt32 OSGWriter::DefaultSFWidth = TypeTraits<UInt32>::getMax();
const UInt32 OSGWriter::DefaultMFWidth = 60;

/*-------------------------------------------------------------------------*/
/*                             Constructor                                 */

/*! Constructor. Set members to initial values.
 */
OSGWriter::FCInfoHelper::FCInfoHelper(void) :
    written      (false),
    hasName      (false),
    containerName(     )
{
}

/*! Constructor. Set members to initial values.
 */
OSGWriter::OSGWriter(OutStream &stream, UInt32 indentStep) :
    _visitedFCMap(                 ),
    _outStream   (stream           )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor. There are no dynamic members to destroy.
 */
OSGWriter::~OSGWriter(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Methods                                     */

/*! Write a single FieldContainer with all its "children", i.e. everything
 *  that can be reached via Ptr-Fields.
 */
void OSGWriter::write(FieldContainerPtr container)
{
    _visitedFCMap.clear();
//    _indent.setIndent(0);

    _outStream << "#OSG V1.0 ";
    _outStream << "\n";

    visitContainer(container);
    writeContainer(container, true);
}


/*! Write all FieldContainers in containers with their "children",
 *  i.e. everything that can be reached via Ptr-Fields.
 */
void OSGWriter::write(std::vector<FieldContainerPtr> containers)
{
    _visitedFCMap.clear();
//    _indent.setIndent(0);

    _outStream << "#OSG V1.0 " << "\n";

    std::vector<FieldContainerPtr>::reverse_iterator iter;

    for(iter = containers.rbegin(); iter != containers.rend(); ++iter)
    {
        visitContainer(*iter);
    }

    for(iter = containers.rbegin(); iter != containers.rend(); ++iter)
    {
        writeContainer(*iter, true);
    }
}


/*! Set the name by which this FieldContainer is referenced. If available
 *  a NameAttachment is used, otherwise the name is constructed from
 *  the type name and the container id.
 */

void OSGWriter::FCInfoHelper::setName(const FieldContainerPtr pFC)
{
    const FieldContainerType& fcType = pFC->getType();

#ifdef FIXME
    AttachmentContainerPtr pAttCon;
    NamePtr                pNameAtt;

    if(fcType.isDerivedFrom(AttachmentContainer::getClassType()))
    {
        pAttCon = AttachmentContainerPtr::dcast(pFC);
        if(pAttCon != NullFC)
        {
            pNameAtt = NamePtr::dcast(pAttCon->findAttachment(
                Name::getClassType().getGroupId()));

            if(pNameAtt != NullFC)
            {
                containerName = pNameAtt->getFieldPtr()->getValue().c_str();
                return;
            }
        }
    }
#endif

    //no NameAttachment. Build name from Type and Id
    containerName = pFC->getTypeName();

    TypeTraits<UInt32>::putToString(getContainerId(pFC), containerName);
}


void OSGWriter::visitContainer(const FieldContainerPtr pFC)
{

    if(pFC == NullFC)
    {
        return;
    }

    typedef std::pair<FCInfoHelperMap::iterator, bool> MapInsertInfo;

          std::string         containerName;
//    const FieldContainerType &fcType    = pFC->getType();
          UInt32              numFields = pFC->getNumFields();
          MapInsertInfo       insertInfo;

    insertInfo = _visitedFCMap.insert(std::make_pair(pFC, FCInfoHelper()));

    if(insertInfo.second == true)
    {
        //the FC was NOT visited before
        for(UInt32 field = 1; field <= numFields; field++)
        {
            FieldHandle fHandle = pFC->getHandledField(field);

            if(fHandle.isInternal())
            {
                continue;
            }

            visitField(fHandle);
        }
    }
    else
    {
        //the FC was in the map => FC is shared

        FCInfoHelperMap::iterator iter = _visitedFCMap.find(pFC);

        if(iter == _visitedFCMap.end())
        {
            SWARNING << "OSGWriter::visitContainer(): FieldContainerPtr "
                     << "not found in map" << std::endl;
            return;
        }
        if(iter->second.hasName == false)
        {
            iter->second.setName(pFC);
            iter->second.hasName = true;
        }
    }
}

void OSGWriter::visitField(const FieldHandle &hF)
{
    if(hF.isValid() == false)
    {
        return;
    }

    const FieldType &fType       = hF.getType();

//    const DataType & contentType = pF->getContentType();

    //handle SFAttachmentMap as special case here
    //if(fType.isDerivedFrom(SFAttachmentMap::getClassType()))

    if(strstr(fType.getCName(), "AttachmentPtrMap") != NULL)
    {
        //visit the Attachment FCs
        const SFFieldContainerAttachmentPtrMap *sfAttMap = 
            reinterpret_cast<const SFFieldContainerAttachmentPtrMap *>(
                hF.getField());

//        FieldContainerAttachmentMap    attMap   = sfAttMap->getValue();

        FieldContainerAttachmentMap::const_iterator iter = 
            sfAttMap->getValue().begin();
        FieldContainerAttachmentMap::const_iterator end  = 
            sfAttMap->getValue().end();

        for(; iter!=end; ++iter)
        {
            visitContainer(iter->second);
        }
    }
    //else if(contentType.isDerivedFrom(FieldContainerPtr::getClassType()))
    else if(strstr(fType.getCName(), "Ptr") != NULL)
    {
        //this Field points to FC

        //to access the content of a field one must know the cardinality
        if(hF.getCardinality() == FieldType::SINGLE_FIELD)
        {
            const SFFieldContainerPtr *sfFCPtr =
                reinterpret_cast<const SFFieldContainerPtr *>(hF.getField());

            visitContainer(sfFCPtr->getValue());
        }
        else if(hF.getCardinality() == FieldType::MULTI_FIELD)
        {
            const MFFieldContainerPtr *mfFCPtr =
                reinterpret_cast<const MFFieldContainerPtr *>(hF.getField());

            UInt32 mfSize = mfFCPtr->size();

            for(UInt32 i=0; i < mfSize; i++)
            {
                visitContainer((*(mfFCPtr))[i]);
            }
        }
    }
}


void OSGWriter::writeContainer(const FieldContainerPtr pFC,
                                     bool              bIndent)
{
    if(pFC == NullFC)
    {
        return;
    }

    UInt32 numFields = pFC->getNumFields();

    FCInfoHelperMap::iterator iter = _visitedFCMap.find(pFC);

    if(iter == _visitedFCMap.end())
    {
        SWARNING << "OSGWriter::writeContainer(): FieldContainerPtr "
                 << "not found in map" << std::endl;
        return;
    }

    if(!iter->second.written)
    {
        //FC is not written yet
        iter->second.written = true;

        if(bIndent == true)
        {
            _outStream << BeginElem;
        }

        if(iter->second.hasName)
        {
            _outStream << "DEF "
                       << iter->second.containerName 
                       << " "
                       << pFC->getTypeName()
                       << EndElemNL
                       << BeginElem
                       << "{"
                       << EndElemNL;
        }
        else
        {
            _outStream <<  pFC->getTypeName() 
                       << EndElemNL
                       << BeginElem
                       << "{"
                       << EndElemNL;
        }
        
        _outStream << IncIndent;

        for(UInt32 field=1; field<=numFields; field++)
        {
            FieldHandle fHandle = pFC->getHandledField(field);

            if(fHandle.isInternal())
            {
                continue;
            }

            writeField(fHandle);
        }

        _outStream << DecIndent;

        _outStream << BeginElem 
                   << "}" 
                   << EndElemNL;
    }
    else
    {
        //FC is already written -> its shared -> write reference
        if(!iter->second.hasName)
        {
            SWARNING << "OSGWriter::writeContainer(): FieldContainer is "
                     << "shared, but not named"
                     << std::endl;
            return;
        }
        
        if(bIndent == true)
        {
            _outStream << BeginElem;
        }

        _outStream << "USE "
                   << iter->second.containerName 
                   << EndElemNL;
    }

}


void OSGWriter::writeField(const FieldHandle &hF)
{

    if(hF.isValid() == false)
    {
        return;
    }

    const FieldType& fType = hF.getType();

//    const DataType&  contentType = pF->getContentType();

    //handle SFAttachmentMap as special case here
    //if(fType.isDerivedFrom(SFAttachmentMap::getClassType()))

    if(strstr(fType.getCName(), "AttachmentPtrMap") != NULL)
    {
        //write Attachments

        const SFFieldContainerAttachmentPtrMap *sfAttMap = 
            reinterpret_cast<const SFFieldContainerAttachmentPtrMap *>(
                hF.getField());

        FieldContainerAttachmentMap::const_iterator iter = 
            sfAttMap->getValue().begin();
        FieldContainerAttachmentMap::const_iterator end  = 
            sfAttMap->getValue().end();

        _outStream << BeginElem 
                   << hF.getName();

//        _state.setIndent(_indent.getIndent());
        
        //if the Attachment Map is empty write [] as its content
        if(iter == end)
        {
            _outStream << " [ ] " << EndElemNL;
        }
        else
        {
            _outStream << EndElemNL
                       << BeginElem
                       << "["
                       << EndElem;

            _outStream << IncIndent;
        
            for(; iter!=end; ++iter)
            {
                if(iter->second->getInternal().getValue() != true)
                {
                    writeContainer(iter->second, true);
                }
            }

            _outStream << DecIndent; 
            
            _outStream << BeginElem
                       << "]"
                       << EndElemNL;
        }
    }
    //else if(contentType.isDerivedFrom(FieldContainerPtr::getClassType()))
    else if(strstr(fType.getCName(), "Ptr") != NULL)
    {
        //this Field points to FC

        _outStream << BeginElem 
                   << hF.getName();

        //to access the content of a field via a Field*
        //one must know the cardinality

        if(hF.getCardinality() == FieldType::SINGLE_FIELD)
        {
            const SFFieldContainerPtr* sfFCPtr =
                reinterpret_cast<const SFFieldContainerPtr*>(hF.getField());

            if(sfFCPtr->getValue() == NullFC)
            {
                _outStream << " NULL" << EndElemNL;
            }
            else
            {
                _outStream << " ";
                writeContainer(sfFCPtr->getValue(), false);
            }
        }
        else if(hF.getCardinality() == FieldType::MULTI_FIELD)
        {
            _outStream << EndElemNL
                       << BeginElem
                       << "[" 
                       << EndElemNL;

            _outStream << IncIndent;

            const MFFieldContainerPtr* mfFCPtr =
                reinterpret_cast<const MFFieldContainerPtr *>(hF.getField());

            UInt32 mfSize = mfFCPtr->size();

            for(UInt32 i=0; i < mfSize; i++)
            {
                if((*(mfFCPtr))[i] == NullFC)
                {
                    _outStream << BeginElem
                               << "NULL" 
                               << EndElemNL;
                }
                else
                {
                    writeContainer((*(mfFCPtr))[i], true);
                }
            }

            _outStream << DecIndent;

            _outStream << BeginElem
                       << "]" 
                       << EndElemNL;
        }
    }
    else
    {
        //this Field contains data -> write it out

        _outStream << BeginElem << hF.getName();

//        std::string fieldValue;

        //to access the content of a field via a Field*
        //one must know the cardinality
        if(hF.getCardinality() == FieldType::SINGLE_FIELD)
        {
            _outStream << " ";

            hF.pushValueToStream(_outStream);

            _outStream << EndElemNL;
        }
        else if(hF.getCardinality() == FieldType::MULTI_FIELD)
        {
            _outStream << " #";

            hF.pushSizeToStream(_outStream);

            _outStream << EndElemNL
                       << BeginElem
                       << "[" 
                       << EndElemNL;

            _outStream << IncIndent;

#ifdef WFC
            hF.pushValueToStream(_outStream);

            _outStream << EndElemNL;
#endif


            _outStream << DecIndent;
            
            _outStream << BeginElem
                       << "]" 
                       << EndElemNL;
        }
    }
}
