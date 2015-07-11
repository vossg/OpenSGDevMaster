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

#include "OSGOSBCubeTextureChunkElement.h"

#include "OSGOSBRootElement.h"

#include "OSGChunkMaterial.h"
#include "OSGCubeTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBCubeTextureChunkElement                                              */
/*-------------------------------------------------------------------------*/

/*! Reads the depreciated TextureChunk from an osb and converts it to the
    CubeTextureObjChunk + TextureEnvChunk combination that is now the preferred
    way to store the same information.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBCubeTextureChunkElement>
    OSBCubeTextureChunkElement::_regHelper =
        OSBElementRegistrationHelper<OSBCubeTextureChunkElement>(
            "CubeTextureChunk");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBCubeTextureChunkElement::OSBCubeTextureChunkElement(OSBRootElement *root) :
     Inherited  (root, OSGOSBHeaderVersion200),
    _pCubeTexObj(NULL                        ),
    _pTexEnv    (NULL                        )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBCubeTextureChunkElement::~OSBCubeTextureChunkElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

// TextureChunk is being split into CubeTextureObjChunk and TextureEnvChunk when
// reading it from an .osb
// The CubeTextureObjChunk will be returned by the getContainer function for
// this element.

void OSBCubeTextureChunkElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBCubeTextureChunkElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();
    
    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBCubeTextureChunkElement::read: version: [%u]\n", version));
    
    // create the two replacement chunks
    _pCubeTexObj = CubeTextureObjChunk::create();
    _pTexEnv     = TextureEnvChunk    ::create();
        
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
            
            _pCubeTexObj->setInternal(fieldValue);
            _pTexEnv    ->setInternal(fieldValue);
        }
        else if(fieldName == "ignore")
        {
            bool fieldValue;
            rh->getValue(fieldValue);
            
            _pCubeTexObj->setIgnore(fieldValue);
            _pTexEnv    ->setIgnore(fieldValue);
        }        
        else if(isTexObjField(fieldName))
        {
            // set TexObj as container for reading the field
            setContainer(_pCubeTexObj);
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
            FWARNING(("OSBCubeTextureChunkElement::read: Skipping unrecognized "
                      "field [%s].\n", fieldName.c_str()));
                      
            rh->skip(fieldSize);
        }
    }
    
    // set TexObj as "the" container
    setContainer(_pCubeTexObj);
}

// All uses of (i.e. pointers to) the TextureChunk need to be replaced with
// pointers to TexObj and TexEnv.

void
OSBCubeTextureChunkElement::postRead(void)
{
    OSG_OSB_LOG(("OSBCubeTextureChunkElement::postRead:\n"));
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
        ChunkMaterial *chkMat =
            dynamic_cast<ChunkMaterial *>(ptrFieldIt->getContainer());

        if(chkMat != NULL)
        {
            // OSBChunkMaterialElement takes care of handling the two chunks
            // replacing TextureChunk
            continue;
        }
        else
        {
            UInt32 numIds  = UInt32(ptrFieldIt->getIdStore     ().size());
            UInt32 numBind = UInt32(ptrFieldIt->getBindingStore().size());

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
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBCubeTextureChunkElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBCubeTextureChunkElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBCubeTextureChunkElement::write(void)
{
    OSG_OSB_LOG(("OSBCubeTextureChunkElement::write\n"));
    
    if(getContainer() == NULL)
    {
        FWARNING((
            "OSBCubeTextureChunkElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}


bool
OSBCubeTextureChunkElement::isTexObjField(const std::string &fieldName) const
{
    return CubeTextureObjChunk::getClassType().getFieldDesc(fieldName.c_str()) != NULL;
}

bool
OSBCubeTextureChunkElement::isTexEnvField(const std::string &fieldName) const
{
    return TextureEnvChunk::getClassType().getFieldDesc(fieldName.c_str()) != NULL;
}

