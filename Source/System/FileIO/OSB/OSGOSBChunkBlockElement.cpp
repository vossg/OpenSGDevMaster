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

#include "OSGOSBChunkBlockElement.h"

#include "OSGOSBRootElement.h"
#include "OSGChunkBlock.h"

#include "OSGOSBTextureChunkElement.h"
#include "OSGOSBCubeTextureChunkElement.h"
#include "OSGTextureObjChunk.h"
#include "OSGCubeTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBChunkBlockElement                                                    */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBChunkBlockElement>
    OSBChunkBlockElement::_regHelper =
        OSBElementRegistrationHelper<OSBChunkBlockElement>("ChunkBlock");


/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBChunkBlockElement::OSBChunkBlockElement(OSBRootElement *root) :
     Inherited            (root, 
                           OSGOSBHeaderVersion200),
    _mfSlots              (                      ),
    _chunksPtrFieldIt     (                      ),
    _chunksPtrFieldItValid(false                 )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBChunkBlockElement::~OSBChunkBlockElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void OSBChunkBlockElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBChunkBlockElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBChunkBlockElement::read: version: [%u]\n", version));

    std::string    fieldName;
    std::string    fieldTypeName;
    UInt32         fieldSize;
    PtrFieldListIt ptrFieldIt;

    ChunkBlockUnrecPtr pMat = dynamic_pointer_cast<ChunkBlock>(
        FieldContainerFactory::the()->createContainer(typeName.c_str()));

    setContainer(pMat);

    while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
    {
        if(fieldName == "chunks")
        {
            // keep an interator to the _mfChunks field contents
            readFieldContent(fieldName, fieldTypeName, fieldSize, "",
                             _chunksPtrFieldIt);

            _chunksPtrFieldItValid = true;
        }
        else
        {
            readFieldContent(fieldName, fieldTypeName, fieldSize, "",
                             ptrFieldIt);
        }
    }
}

void OSBChunkBlockElement::postRead(void)
{
    // _mfChunks and _mfSlots have to be kept consistent for ChunkBlock.
    // Also TextureChunk is split into TextureObjChunk and TextureObjChunk
    // on load, so the slot info has to be duplicated.
    // TODO:
    // It would be better if that handling could be confined to
    // TextureChunkElement, but I've not found a good way to do that and keep
    // the information in _mfSlots correct. -- cneumann

    const OSBRootElement *root   = getRoot();
          ChunkBlock     *chkMat = dynamic_cast<ChunkBlock *>(getContainer());
    
    // No chunks loaded
    if(_chunksPtrFieldItValid == false)
        return;

    PtrFieldInfo::PtrIdStoreConstIt idIt  = 
        _chunksPtrFieldIt->getIdStore().begin();
    PtrFieldInfo::PtrIdStoreConstIt idEnd = 
        _chunksPtrFieldIt->getIdStore().end  ();

    for(UInt32 i = 0; idIt != idEnd; ++idIt, ++i)
    {
        UInt32 uiId   =  (*idIt) & 0x00FFFFFF;
        UInt32 uiSlot = ((*idIt) & 0xFF000000) >> 24;

        OSBRootElement::IdElemMapConstIt mapIt = 
            root->getIdElemMap().find(uiId);

        if(mapIt == root->getIdElemMap().end())
        {
            continue;
        }

        OSBElementBase *chunkElem = mapIt->second;

        // other chunk
        StateChunk     *chunk     = 
            dynamic_cast<StateChunk *>(chunkElem->getContainer());
        

        chkMat->addChunk(chunk, uiSlot);
    }
    
    // pointer mapping is already done here for _mfChunks, clear info
    _chunksPtrFieldIt->editIdStore     ().clear();
    _chunksPtrFieldIt->editBindingStore().clear();
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void OSBChunkBlockElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBChunkBlockElement::preWrite\n"));

    if(getContainer() == NULL || fc == NULL)
    {
        FWARNING(("OSBChunkBlockElement::prewrite: Attempt to write NULL.\n"));
        return;
    }

    preWriteFieldContainer(fc, "");
}

void OSBChunkBlockElement::write(void)
{
    OSG_OSB_LOG(("OSBChunkBlockElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBChunkBlockElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );
 
    ChunkBlock *pCBlock = dynamic_cast<ChunkBlock *>(getContainer());

    if(pCBlock != NULL)
    {
        _mfSlots.clear();
        
        ChunkBlock::MFChunksType::const_iterator cIt  = 
            pCBlock->getMFChunks()->begin();
        ChunkBlock::MFChunksType::const_iterator cEnd = 
            pCBlock->getMFChunks()->end();
        
        UInt32 cIdx = 0;

        for(; cIt != cEnd; ++cIt, ++cIdx)
        {
            if(*cIt != NULL)
            {
                UInt32 uiId  = (*cIt)->getId();
                Int32  iSlot = cIdx - (*cIt)->getClassId();

                if(iSlot != -1)
                {
                    uiId |= iSlot << 24;
                }

                _mfSlots.push_back(uiId);
            }
        }

        writeFieldHeader("chunks", 
                         "MFUnrecStateChunkPtr", 
                         _mfSlots.size() * sizeof(UInt32));

        BinaryWriteHandler *wh = editRoot()->getWriteHandler();
        
        _mfSlots.copyToBin(*wh);
    }

    writeFields("'chunks'", true);
}
