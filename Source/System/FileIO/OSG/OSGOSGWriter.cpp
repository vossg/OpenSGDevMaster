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
//#include "OSGAttachment.h"
//#include "OSGSimpleAttachments.h"
//#include "OSGVRMLNodeDescs.h"

#include "OSGAttachmentMapSFields.h"
#include "OSGAttachment.h"
#include "OSGNameAttachment.h"

#include <boost/bind.hpp>

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
void OSGWriter::write(FieldContainer *container)
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
void OSGWriter::write(std::vector<FieldContainer *> containers)
{
    _visitedFCMap.clear();
//    _indent.setIndent(0);

    _outStream << "#OSG V1.0 " << "\n";

    std::vector<FieldContainer *>::reverse_iterator iter;

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

void OSGWriter::FCInfoHelper::setName(FieldContainer * const pFC)
{
    AttachmentContainer *pAttCon = dynamic_cast<AttachmentContainer *>(pFC);

    if(pAttCon != NULL)
    {
        const Char8 *szName = getName(pAttCon);

        if(szName != NULL)
        {
            containerName = szName;
            return;
        }
    }

    //no NameAttachment. Build name from Type and Id
    containerName = pFC->getTypeName();

    TypeTraits<UInt32>::putToString(pFC->getId(), containerName);
}


void OSGWriter::visitContainer(FieldContainer * const pFC)
{

    if(pFC == NULL)
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
            GetFieldHandlePtr fHandle = pFC->getField(field);

            if(fHandle == NULL || (fHandle != NULL && fHandle->isInternal()))
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
            SWARNING << "OSGWriter::visitContainer(): FieldContainer * "
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

void OSGWriter::visitField(GetFieldHandlePtr hF)
{
    if(hF->isValid() == false)
    {
        return;
    }

//    const FieldType &fType       = hF->getType();

    GetMapFieldHandlePtr sfMap = 
        boost::dynamic_pointer_cast<
            GetMapFieldHandle>(hF);

    if(sfMap != NULL && sfMap->isValid() == true)
    {
        sfMap->traverse(boost::bind(&OSGWriter::visitContainer, this, _1));
    }
    else
    {
        FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrSFieldBase::GetHandle>(hF);

        FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
            boost::dynamic_pointer_cast<
                FieldContainerPtrMFieldBase::GetHandle>(hF);

        if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
        {
            visitContainer((*sfFCPtr)->getValue());
        }
        else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
        {
            UInt32 mfSize = (*mfFCPtr)->size();

            for(UInt32 i=0; i < mfSize; i++)
            {
                visitContainer((**mfFCPtr)[i]);
            }
        }
    }
}


void OSGWriter::writeContainer(FieldContainer * const pFC,
                               bool                   bIndent)
{
    if(pFC == NULL)
    {
        return;
    }

    UInt32 numFields = pFC->getNumFields();

    FCInfoHelperMap::iterator iter = _visitedFCMap.find(pFC);

    if(iter == _visitedFCMap.end())
    {
        SWARNING << "OSGWriter::writeContainer(): FieldContainer * "
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

        for(UInt32 field=numFields; field > 0; field--)
        {
            GetFieldHandlePtr fHandle = pFC->getField(field);

            if(fHandle == NULL || (fHandle != NULL && fHandle->isInternal()))
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


void OSGWriter::writeField(GetFieldHandlePtr hF)
{

    if(hF->isValid() == false)
    {
        return;
    }

//    const FieldType& fType = hF->getType();

    GetMapFieldHandlePtr sfMap = 
        boost::dynamic_pointer_cast<
            GetMapFieldHandle>(hF);

    FieldContainerPtrSFieldBase::GetHandlePtr sfFCPtr = 
        boost::dynamic_pointer_cast<FieldContainerPtrSFieldBase::GetHandle>(hF);
    
    FieldContainerPtrMFieldBase::GetHandlePtr mfFCPtr = 
        boost::dynamic_pointer_cast<FieldContainerPtrMFieldBase::GetHandle>(hF);

    if(sfMap != NULL && sfMap->isValid() == true)
    {
        _outStream << BeginElem 
                   << hF->getName();

        //if the Attachment Map is empty write [] as its content
        if(sfMap->empty() == true)
        {
            _outStream << " [ ] " << EndElemNL;
        }
        else
        {
            _outStream << EndElemNL
                       << BeginElem
                       << "["
                       << EndElemNL;

            _outStream << IncIndent;
        
            EditMapFieldHandle::MapList fcList;

            sfMap->flatten(fcList);

            EditMapFieldHandle::MapList::iterator iter = fcList.begin();
            EditMapFieldHandle::MapList::iterator end  = fcList.end  ();

            for(; iter!=end; ++iter)
            {
                _outStream << BeginElem
                           << "MapHelper"
                           << EndElemNL
                           << BeginElem
                           << "{"
                           << EndElemNL;

                _outStream << IncIndent;

                _outStream << BeginElem
                           << "keys"
                           << EndElemNL
                           << BeginElem
                           << "["
                           << EndElemNL;

                _outStream << IncIndent;

                std::vector<std::string>::const_iterator kIt  = 
                    iter->first.begin();

                std::vector<std::string>::const_iterator kEnd = 
                    iter->first.end();

                for(; kIt != kEnd; ++kIt)
                {
                    _outStream << BeginElem
                               << "\""
                               << *kIt
                               << "\""
                               << EndElemNL;
                }

                _outStream << DecIndent;

                _outStream << BeginElem
                           << "]"
                           << EndElemNL;

                _outStream << BeginElem
                           << "container ";
                    
                if(iter->second == NULL)
                {
                    _outStream << "NULL"
                               << EndElemNL;
                }
                else
                {
                    writeContainer(iter->second, false);
                    _outStream << EndElemNL;
                }

                _outStream << DecIndent;
                                    
                _outStream << BeginElem
                           << "}"
                           << EndElemNL;
            }

            _outStream << DecIndent; 
            
            _outStream << BeginElem
                       << "]"
                       << EndElemNL;
        }
    }
    else if(sfFCPtr != NULL || mfFCPtr != NULL)
    {
        //this Field points to FC

        _outStream << BeginElem 
                   << hF->getName();

        if(sfFCPtr != NULL && sfFCPtr->isValid() == true)
        {
            if((*sfFCPtr)->getValue() == NULL)
            {
                _outStream << " NULL" << EndElemNL;
            }
            else
            {
                _outStream << " ";
                writeContainer((*sfFCPtr)->getValue(), false);
            }
        }
        else if(mfFCPtr != NULL && mfFCPtr->isValid() == true)
        {
            _outStream << EndElemNL
                       << BeginElem
                       << "[" 
                       << EndElemNL;

            _outStream << IncIndent;

            UInt32 mfSize = (*mfFCPtr)->size();

            for(UInt32 i=0; i < mfSize; i++)
            {
                if((*(*mfFCPtr))[i] == NULL)
                {
                    _outStream << BeginElem
                               << "NULL" 
                               << EndElemNL;
                }
                else
                {
                    writeContainer((*(*mfFCPtr))[i], true);
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

        _outStream << BeginElem << hF->getName();

        //to access the content of a field via a Field*
        //one must know the cardinality
        if(hF->getCardinality() == FieldType::SingleField)
        {
            _outStream << " ";

            hF->pushValueToStream(_outStream);

            _outStream << EndElemNL;
        }
        else if(hF->getCardinality() == FieldType::MultiField)
        {
            _outStream << " #";

            hF->pushSizeToStream(_outStream);

            _outStream << EndElemNL
                       << BeginElem
                       << "[" 
                       << EndElemNL;

            _outStream << IncIndent;

#ifdef WFC
            hF->pushValueToStream(_outStream);

            _outStream << EndElemNL;
#endif


            _outStream << DecIndent;
            
            _outStream << BeginElem
                       << "]" 
                       << EndElemNL;
        }
    }
}
