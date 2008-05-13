/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include "OSGOSBTextureChunkElement.h"

#include "OSGOSBRootElement.h"

#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBTextureChunkElement                                                  */
/*-------------------------------------------------------------------------*/

/*! Reads the depreciated TextureChunk from an osb and converts it to the
    TextureObjChunk + TextureEnvChunk combination that is now the preferred
    way to store the same information.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBTextureChunkElement>
    OSBTextureChunkElement::_regHelper =
        OSBElementRegistrationHelper<OSBTextureChunkElement>("TextureChunk");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBTextureChunkElement::OSBTextureChunkElement(OSBRootElement *root)
    : Inherited(root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBTextureChunkElement::~OSBTextureChunkElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

// TextureChunk is being split into TextureObjChunk and TextureEnvChunk when
// reading it from an .osb
// The TextureObjChunk will be returned by the getContainer function for this
// element.

void
OSBTextureChunkElement::read(const std::string &typeName)
{
    FDEBUG(("OSBTextureChunkElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();
    
    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    FDEBUG(("OSBTextureChunkElement::read: version: [%u]\n", version));
    
    // create the two replacement chunks
    _pTexObj = TextureObjChunk::create();
    _pTexEnv = TextureEnvChunk::create();
        
    std::string    fieldName;
    std::string    fieldTypeName;
    UInt32         fieldSize;
    PtrFieldListIt ptrFieldIt;
    
    while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
    {
        // some fields need to be duplicated for the two replacement chunks
        if(fieldName == "parents")
        {
            // parent fields are ignored
            rh->skip(fieldSize);
        }    
        else if(fieldName == "internal")
        {
            bool fieldValue;
            rh->getValue(fieldValue);
            
            _pTexObj->setInternal(fieldValue);
            _pTexEnv->setInternal(fieldValue);
        }
        else if(fieldName == "ignore")
        {
            bool fieldValue;
            rh->getValue(fieldValue);
            
            _pTexObj->setIgnore(fieldValue);
            _pTexEnv->setIgnore(fieldValue);
        }        
        else if(isTexObjField(fieldName))
        {
            // set TexObj as container for reading the field
            setContainer(_pTexObj);
            readFieldContent(fieldName, fieldTypeName, fieldSize, "", ptrFieldIt);
        }
        else if(isTexEnvField(fieldName))
        {
            // set TexEnv as container for reading the field
            setContainer(_pTexEnv);
            readFieldContent(fieldName, fieldTypeName, fieldSize, "", ptrFieldIt);
        }
        else
        {
            FWARNING(("OSBTextureChunkElement::read: Skipping unrecognized "
                      "field [%s].\n", fieldName.c_str()));
                      
            rh->skip(fieldSize);
        }
    }
    
    // set TexObj as "the" container
    setContainer(_pTexObj);
}

// All uses of (i.e. pointers to) the TextureChunk need to be replaced with
// pointers to TexObj and TexEnv.

void
OSBTextureChunkElement::postRead(void)
{
    FDEBUG(("OSBTextureChunkElement::postRead:\n"));
    OSBRootElement *pRoot = editRoot();

    // for the id remapping TexEnv needs an id that is not used in the file
    UInt32 texEnvIdFile = pRoot->getIdMap().rbegin()->first;
    while(pRoot->getIdMap().find(texEnvIdFile) != pRoot->getIdMap().end())
    {
        ++texEnvIdFile;
    }
    
    // add mapping entry for TexEnv
    pRoot->editIdMap()[texEnvIdFile] = _pTexEnv->getId();
    
    PtrFieldListIt ptrFieldIt  = pRoot->editPtrFieldList().begin();
    PtrFieldListIt ptrFieldEnd = pRoot->editPtrFieldList().end  ();

    for(; ptrFieldIt != ptrFieldEnd; ++ptrFieldIt)
    {
        UInt32 numIds  = ptrFieldIt->getIdStore     ().size();
        UInt32 numBind = ptrFieldIt->getBindingStore().size();
        
        if(numBind > 0)
        {
            // TextureChunk is pointed to from an attachment map
        
            for(UInt32 i = 0; (i < numIds) && (i < numBind); ++i)
            {
                if(ptrFieldIt->getIdStore()[i] == getFCIdFile())
                {
                    // insert a pointer to TexEnv right after the TexObj
                    ptrFieldIt->editIdStore().insert(
                        ptrFieldIt->editIdStore().begin() + i + 1,
                        texEnvIdFile                              );
                    
                    // duplicate the binding of the TexObj
                    ptrFieldIt->editBindingStore().insert(
                        ptrFieldIt->editBindingStore().begin() + i + 1,
                        ptrFieldIt->getBindingStore()[i]               );
                        
                    ++numIds;
                    ++numBind;
                }
            }
        }
        else
        {
            for(UInt32 i = 0; i < numIds; ++i)
            {
                if(ptrFieldIt->getIdStore()[i] == getFCIdFile())
                {
                    // insert a pointer to TexEnv right after the TexObj
                    ptrFieldIt->editIdStore().insert(
                        ptrFieldIt->editIdStore().begin() + i + 1,
                        texEnvIdFile                              );
                        
                    ++numIds;
                }
            }
        }            
    }
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBTextureChunkElement::preWrite(FieldContainer * const fc)
{
    FDEBUG(("OSBTextureChunkElement::preWrite\n"));

    OSBRootElement *root       = editRoot();
    UInt32          fieldCount = fc->getType().getNumFieldDescs();

    preWriteFieldContainer(fc, "");
}

void
OSBTextureChunkElement::write(void)
{
    FDEBUG(("OSBTextureChunkElement::write\n"));
    
    if(getContainer() == NULL)
    {
        FWARNING(("OSBTextureChunkElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}


bool
OSBTextureChunkElement::isTexObjField(const std::string &fieldName) const
{
    return TextureObjChunk::getClassType().getFieldDesc(fieldName.c_str()) != NULL;
}

bool
OSBTextureChunkElement::isTexEnvField(const std::string &fieldName) const
{
    return TextureEnvChunk::getClassType().getFieldDesc(fieldName.c_str()) != NULL;
}

