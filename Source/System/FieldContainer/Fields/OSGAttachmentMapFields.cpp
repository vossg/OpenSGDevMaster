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

#define OSG_COMPILEATTACHMENTMAPFIELDINST

#include <OSGFieldContainer.h>
#include <OSGAttachmentMapSFields.h>
#include <OSGAttachment.h>
#include <OSGAttachmentContainer.h>
#include <OSGContainerPtrFuncs.h>

#include <OSGTypeBasePredicates.h>
#include <OSGReflexiveContainerTypePredicates.h>

#include <OSGSField.ins>


OSG_BEGIN_NAMESPACE

UInt32 FieldTraits<AttachmentMap>::getBinSize(const AttachmentMap &aMap)
{
    AttachmentMap::const_iterator mapIt  = aMap.begin();
    AttachmentMap::const_iterator mapEnd = aMap.end  ();

    UInt32 numPublicObjects = 0;

    for(; mapIt != mapEnd; ++mapIt)
    {
        if(mapIt->second->getInternal().getValue() == false)
        {
            ++numPublicObjects;
        }
    }

    // number of elements in map + binding and pointer id for each element
    return sizeof(UInt32) +
        numPublicObjects * (sizeof(UInt16) + sizeof(UInt32));
}

void FieldTraits<AttachmentMap>::copyToBin(      BinaryDataHandler &pMem,
                                           const AttachmentMap     &aMap )
{
    AttachmentMap::const_iterator mapIt  = aMap.begin();
    AttachmentMap::const_iterator mapEnd = aMap.end  ();
        
    UInt32 numPublicObjects = 0;
    UInt16 binding;
    UInt32 fcId;
        
    for(; mapIt != mapEnd; ++mapIt)
    {
        if(mapIt->second->getInternal().getValue() == false)
        {
            ++numPublicObjects;
        }
    }
        
    pMem.putValue(numPublicObjects);
    
    for(mapIt = aMap.begin(); mapIt != mapEnd; ++mapIt)
    {
        if(mapIt->second->getInternal().getValue() == false)
        {
            binding = mapIt->first & 0xFFFF;
            fcId    = mapIt->second->getId();
                
            pMem.putValue(binding);
            pMem.putValue(fcId   );
        }
    }
}

void FieldTraits<AttachmentMap>::copyFromBin(BinaryDataHandler &pMem,
                                             AttachmentMap     &aMap )
{
    Attachment *attPtr;
    UInt32      key;
    UInt16      binding;
    UInt32      fcId;
    UInt32      size;
        
    pMem.getValue(size);


    AttachmentMap::const_iterator mapIt  = aMap.begin();
    AttachmentMap::const_iterator mapEnd = aMap.begin();

    for(; mapIt != mapEnd; ++mapIt)
    {
        if((*mapIt).second != NULL)
        {
            Thread::getCurrentChangeList()->addDelayedSubRef<
            UnrecordedRefCountPolicy>((*mapIt).second);
        }
    }
        
    aMap.clear();

        
    for(UInt32 i = 0; i < size; ++i)
    {
        pMem.getValue(binding);
        pMem.getValue(fcId   );
        
        attPtr = dynamic_cast<Attachment *>(
            FieldContainerFactory::the()->getMappedContainer(fcId));
            
        key = (static_cast<UInt32>(attPtr->getGroupId()) << 16) | binding;

        UnrecordedRefCountPolicy::addRef(attPtr);

        aMap.insert(AttachmentMap::value_type(key, attPtr));
    }
}

void EditSFieldHandle<SFAttachmentPtrMap>::add(
    FieldContainer * const rhs,
    UInt32                 uiBindings)
{
    Attachment * const pVal = 
        dynamic_cast<Attachment * const>(rhs);

    if(rhs != NULL && pVal == NULL)
        return;

    // for whatever reason VS2003 does not like == NULL
    if(_fAddMethod)
    {
        _fAddMethod(pVal, uiBindings);
    }
}

void EditSFieldHandle<SFAttachmentPtrMap>::cloneValues(
          GetFieldHandlePtr  pSrc,
    const TypePtrVector     &shareTypes,
    const TypePtrVector     &ignoreTypes,
    const TypeIdVector      &shareGroupIds,
    const TypeIdVector      &ignoreGroupIds) const
{
    SFAttachmentPtrMap::GetHandlePtr pGetHandle = 
        boost::dynamic_pointer_cast<
            SFAttachmentPtrMap::GetHandle>(pSrc);

    if(pGetHandle == NULL || pGetHandle->isValid() == false)
        return;

    const SFAttachmentPtrMap &pAttMap = **pGetHandle;

    AttachmentMap::const_iterator mapIt  = pAttMap.getValue().begin();
    AttachmentMap::const_iterator mapEnd = pAttMap.getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        AttachmentUnrecPtr att       = mapIt->second;
        UInt16             uiBinding = UInt16(mapIt->first &
                                              0x0000FFFF    );

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
                    att = dynamic_pointer_cast<Attachment>(
                        OSG::deepClone(att, shareTypes,    ignoreTypes,
                                            shareGroupIds, ignoreGroupIds));
                }
            }
        }

        if(_fAddMethod)
        {
            _fAddMethod(att, uiBinding);
        }
    }
}

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<AttachmentMap>::_type(
    "AttachmentMap",
    NULL);

OSG_FIELDTRAITS_GETTYPE(AttachmentMap)

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_FIELD_DLLEXPORT_DEF1(SField, AttachmentMap);

OSG_END_NAMESPACE
