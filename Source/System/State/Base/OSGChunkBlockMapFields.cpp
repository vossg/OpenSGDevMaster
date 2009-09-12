/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainer.h>
#include <OSGChunkBlockMapFields.h>
#include <OSGChunkBlock.h>
#include <OSGContainerPtrFuncs.h>

#include <OSGTypeBasePredicates.h>
#include <OSGReflexiveContainerTypePredicates.h>
#include <OSGMapHelper.h>

#include <OSGSField.ins>


OSG_BEGIN_NAMESPACE

OSG_FIELD_DLLEXPORT_DEF1(SField, ChunkBlockMap);


const FieldType &GetSFieldHandle<SFChunkBlockPtrMap>::getType(void) const
{
    return SFChunkBlockPtrMap::getClassType();
}

const FieldType &EditSFieldHandle<SFChunkBlockPtrMap>::getType(void) const
{
    return SFChunkBlockPtrMap::getClassType();
}

UInt32 FieldTraits<ChunkBlockMap>::getBinSize(const ChunkBlockMap &aMap)
{
    // number of elements in map + binding and pointer id for each element
    ChunkBlockMap::const_iterator mapIt  = aMap.begin();
    ChunkBlockMap::const_iterator mapEnd = aMap.end  ();

    UInt32 uiKeySize = 0;

    for(;mapIt != mapEnd; ++mapIt)
    {            
        std::vector<std::string> vKeyList;
        
        KeyPool::the()->keyToStringList(mapIt->first, vKeyList);

        std::vector<std::string>::const_iterator kIt  = vKeyList.begin();
        std::vector<std::string>::const_iterator kEnd = vKeyList.end  ();
        
        uiKeySize += sizeof(UInt32);

        for(; kIt != kEnd; ++kIt)
        {
            uiKeySize += FieldTraits<std::string>::getBinSize(*kIt);
        }
    }

    return sizeof(UInt32) + aMap.size() * sizeof(UInt32) + uiKeySize;
}

void FieldTraits<ChunkBlockMap>::copyToBin(      BinaryDataHandler &pMem,
                                           const ChunkBlockMap     &aMap )
{
    ChunkBlockMap::const_iterator mapIt  = aMap.begin();
    ChunkBlockMap::const_iterator mapEnd = aMap.end  ();
        
    UInt32         numPublicObjects = aMap.size();
    UInt32         fcId;
               
    pMem.putValue(numPublicObjects);
    
    for(; mapIt != mapEnd; ++mapIt)
    {
        std::vector<std::string> vKeyList;
        
        KeyPool::the()->keyToStringList(mapIt->first, vKeyList);

        std::vector<std::string>::const_iterator kIt  = vKeyList.begin();
        std::vector<std::string>::const_iterator kEnd = vKeyList.end  ();
        
        UInt32 uiNumKeys = vKeyList.size();

        pMem.putValue(uiNumKeys);
       
        for(; kIt != kEnd; ++kIt)
        {
            FieldTraits<std::string>::copyToBin(pMem, *kIt);
        }

        fcId  = mapIt->second->getId();
                
        pMem.putValue(fcId);
    }
}

void FieldTraits<ChunkBlockMap>::copyFromBin(BinaryDataHandler &pMem,
                                             ChunkBlockMap     &aMap )
{
    ChunkBlock       *matPtr;
    ChunkBlockMapKey  key  = KeyPool::the()->getDefault();
    UInt32            fcId;
    UInt32            uiNumObjects;

    pMem.getValue(uiNumObjects);

    ChunkBlockMap::const_iterator mapIt  = aMap.begin();
    ChunkBlockMap::const_iterator mapEnd = aMap.end  ();

    for(; mapIt != mapEnd; ++mapIt)
    {
        if((*mapIt).second != NULL)
        {
            Thread::getCurrentChangeList()->addDelayedSubRef<
                UnrecordedRefCountPolicy>((*mapIt).second);
        }
    }
        
    aMap.clear();

        
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        UInt32 uiNumKeys;

        pMem.getValue(uiNumKeys);

        for(UInt32 j = 0; j < uiNumKeys; ++j)
        {
            std::string tmpString;

            FieldTraits<std::string>::copyFromBin(pMem, tmpString);

            ChunkBlockMapKey tmpKey = 
                KeyPool::the()->getAuto(tmpString.c_str());

            key |= tmpKey;
        }

        pMem.getValue(fcId);
        
        matPtr = dynamic_cast<ChunkBlock *>(
            FieldContainerFactory::the()->getMappedContainer(fcId));
        
        if(matPtr != NULL)
        {
            UnrecordedRefCountPolicy::addRef(matPtr);

            aMap.insert(ChunkBlockMap::value_type(key, matPtr));
        }
    }
}

void EditSFieldHandle<SFChunkBlockPtrMap>::add(
          FieldContainer *rhs,
    const std::string    &szBindings)
{
    ChunkBlock *pVal = dynamic_cast<ChunkBlock *>(rhs);
    KeyType     oKey = 0x0000;

    if(pVal == NULL)
    {
        MapHelper *pMHelper = dynamic_cast<MapHelper *>(rhs);
 
        if(pMHelper != NULL)
        {
            pVal = dynamic_cast<ChunkBlock *>(pMHelper->getContainer());

            const MapHelper::MFKeysType *pKeys = pMHelper->getMFKeys();
           
            if(pKeys->empty() == false)
            {
                KeyType tmpKey = KeyPool::the()->getDefault();

                for(UInt32 i = 0; i < pKeys->size(); ++i)
                {
                    const std::string &szKey = pMHelper->getKeys(i);

                    tmpKey = KeyPool::the()->getAuto(szKey.c_str());

                    oKey |= tmpKey;
                }
            }
        }
    }
    else
    {
        if(szBindings.empty() == false)
        {
            oKey = KeyPool::the()->getAuto(szBindings.c_str());
        }
    }

    if(rhs != NULL && pVal == NULL)
        return;


    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pVal, oKey);
    }
}

void EditSFieldHandle<SFChunkBlockPtrMap>::traverse(TraverseCallback oCallback)
{
    const SFChunkBlockPtrMap *pMap = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(oCallback && pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            oCallback(mapIt->second);
        }
    }
}

void EditSFieldHandle<SFChunkBlockPtrMap>::flatten(MapList &vList)
{
    vList.clear();

    const SFChunkBlockPtrMap *pMap = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            ListEntry tmpEntry;

            KeyPool::the()->keyToStringList(mapIt->first,
                                            tmpEntry.first);

            tmpEntry.second = mapIt->second;

            vList.push_back(tmpEntry);
        }
    }
}

void EditSFieldHandle<SFChunkBlockPtrMap>::flatten(ContainerList &vList)
{
    vList.clear();

    const SFChunkBlockPtrMap *pMap = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            vList.push_back(mapIt->second);
        }
    }
}

bool EditSFieldHandle<SFChunkBlockPtrMap>::loadFromBin(
    BinaryDataHandler        *pMem,
    UInt32                    uiNumElements,
    bool                      hasBindingInfo,
    std::vector<UInt16>      &vBindings,
    std::vector<UInt32>      &vIds          )
{
    SFChunkBlockPtrMap *pMap = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(pMap == NULL)
        return true;
    
    ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
    ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

    for(; mapIt != mapEnd; ++mapIt)
    {
        if((*mapIt).second != NULL)
        {
            Thread::getCurrentChangeList()->addDelayedSubRef<
                 UnrecordedRefCountPolicy>((*mapIt).second);
        }
    }
        
    pMap->getValue().clear();

        
    UInt32 fcId;

    union
    {
        ChunkBlock  *pointerVal;
        UIntPointer  uiVal;
    } tmpEntry;

    for(UInt32 i = 0; i < uiNumElements; ++i)
    {
        ChunkBlockMapKey  key  = KeyPool::the()->getDefault();
        UInt32            uiNumKeys;

        pMem->getValue(uiNumKeys);

        for(UInt32 j = 0; j < uiNumKeys; ++j)
        {
            std::string tmpString;

            FieldTraits<std::string>::copyFromBin(*pMem, tmpString);

            ChunkBlockMapKey tmpKey = 
                KeyPool::the()->getAuto(tmpString.c_str());

            key |= tmpKey;
        }

        pMem->getValue(fcId);
              
        tmpEntry.uiVal = fcId;

        pMap->getValue().insert(ChunkBlockMap::value_type(key, 
                                                          tmpEntry.pointerVal));
    }

    UInt16 uiCount = 0;

    ChunkBlockMap::iterator mapWIt = pMap->getValue().begin();
                            mapEnd = pMap->getValue().end  ();

    for(; mapWIt != mapEnd; ++mapWIt, ++uiCount)
    {
        tmpEntry.pointerVal = mapWIt->second;

        vIds     .push_back(tmpEntry.uiVal);
        vBindings.push_back(uiCount       );

        mapWIt->second = NULL;
    }

    return true;
}

void EditSFieldHandle<SFChunkBlockPtrMap>::fillFrom(
    const std::vector<UInt16>      &vBindings,
    const std::vector<UInt32>      &vIds,
    const std::map<UInt32, UInt32> &mIdMap       )
{
    SFChunkBlockPtrMap *pMap = static_cast<SFChunkBlockPtrMap *>(_pField);

    if(pMap == NULL)
        return;

    ChunkBlockMap::iterator       mapIt  = pMap->getValue().begin();
    ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

    std::vector<UInt32        >::const_iterator idIt    = vIds.begin();
    std::map   <UInt32, UInt32>::const_iterator imapIt;
    std::map   <UInt32, UInt32>::const_iterator imapEnd = mIdMap.end();

    OSG_ASSERT(vIds     .size() == pMap->getValue().size() &&
               vBindings.size() == pMap->getValue().size()  );

    ChunkBlock *pMat = NULL;

    for(; mapIt != mapEnd; ++mapIt, ++idIt)
    {
        imapIt  = mIdMap.find(*idIt);

        if(imapIt != imapEnd)
        {
            pMat = dynamic_cast<ChunkBlock *>(
                FieldContainerFactory::the()->getContainer(imapIt->second));

            UnrecordedRefCountPolicy::addRef(pMat);
        }
        else
        {
            pMat = NULL;
        }

        mapIt->second = pMat;
    }
}


void EditSFieldHandle<SFChunkBlockPtrMap>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    SFChunkBlockPtrMap::GetHandlePtr pGetHandle = 
        boost::dynamic_pointer_cast<
            SFChunkBlockPtrMap::GetHandle>(pSrc);

    if(pGetHandle == NULL || pGetHandle->isValid() == false)
        return;

    const SFChunkBlockPtrMap &pAttMap = **pGetHandle;

    ChunkBlockMap::const_iterator mapIt  = pAttMap.getValue().begin();
    ChunkBlockMap::const_iterator mapEnd = pAttMap.getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        ChunkBlockUnrecPtr att = mapIt->second;
        ChunkBlockMapKey   key = mapIt->first;

        if(att != NULL)
        {
            const FieldContainerType &attType = att->getType();

            // test if att type should NOT be ignored
            if(!TypePredicates::typeInGroupIds (ignoreGroupIds.begin(),
                                                ignoreGroupIds.end(),
                                                attType                ) &&
               !TypePredicates::typeDerivedFrom(ignoreTypes.begin(),
                                                ignoreTypes.end(),
                                                attType                )   )
            {
                // test if att should cloned
                if(!TypePredicates::typeInGroupIds (shareGroupIds.begin(),
                                                    shareGroupIds.end(),
                                                    attType               ) &&
                   !TypePredicates::typeDerivedFrom(shareTypes.begin(),
                                                    shareTypes.end(),
                                                    attType               )   )
                {
                    att = dynamic_pointer_cast<ChunkBlock>(
                        OSG::deepClone(att, shareTypes,    ignoreTypes,
                                            shareGroupIds, ignoreGroupIds));
                }
            }
        }

        if(_fAddMethod)
        {
            _fAddMethod(att, key);
        }
    }
}


void GetSFieldHandle<SFChunkBlockPtrMap>::traverse(TraverseCallback oCallback)
{
    SFChunkBlockPtrMap const *pMap = 
        static_cast<SFChunkBlockPtrMap const *>(_pField);

    if(oCallback && pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            oCallback(mapIt->second);
        }
    }
}

void GetSFieldHandle<SFChunkBlockPtrMap>::flatten(MapList &vList)
{
    vList.clear();

    SFChunkBlockPtrMap const *pMap = 
        static_cast<SFChunkBlockPtrMap const *>(_pField);

    if(pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            ListEntry   tmpEntry;

            KeyPool::the()->keyToStringList(mapIt->first,
                                            tmpEntry.first);

            tmpEntry.second = mapIt->second;

            vList.push_back(tmpEntry);
        }
    }
}

void GetSFieldHandle<SFChunkBlockPtrMap>::flatten(ContainerList &vList)
{
    vList.clear();

    SFChunkBlockPtrMap const *pMap = 
        static_cast<SFChunkBlockPtrMap const *>(_pField);

    if(pMap != NULL)
    {
        ChunkBlockMap::const_iterator mapIt  = pMap->getValue().begin();
        ChunkBlockMap::const_iterator mapEnd = pMap->getValue().end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            vList.push_back(mapIt->second);
        }
    }
}

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<ChunkBlockMap>::_type(
    "ChunkBlockMap",
    "FieldContainerPtrMap");

OSG_FIELDTRAITS_GETTYPE(ChunkBlockMap)

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE
