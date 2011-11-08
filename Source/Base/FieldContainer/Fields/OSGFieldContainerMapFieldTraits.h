/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGFIELDCONTAINERMAPFIELDTRAITS_H_
#define _OSGFIELDCONTAINERMAPFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include "OSGBaseFieldTraits.h"

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.h"
#include "OSGContainerIdMapper.h"

#include <string>
#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, FieldContainerRecPtr>  FieldContainerMap;

// The FieldTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<FieldContainerMap> : 
    public FieldTraitsTemplateBase<FieldContainerMap>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType                  _type;

    typedef FieldTraits<std::string>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING 
                 DataType    &getType   (void);

    // Access to the names of the actual Fields
    static const Char8       *getSName  (void) { return "SFFieldContainerMap"; }
    static const Char8       *getMName  (void) { return "MFFieldContainerMap"; }

    // Create a default instance of the class, needed for Field creation
    static FieldContainerMap  getDefault(void) { return FieldContainerMap();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion
    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToStream   (const FieldContainerMap  &inVal,
                                     OutStream          &outVal      )
    {
        //Loop through all of the map elelments
        FieldContainerMap::const_iterator it = inVal.begin();

        for(; it != inVal.end(); ++it)
        {
            if(it != inVal.begin())
            {
                outVal << ",";
            }

            FieldTraits<FieldContainerMap::key_type>::putToStream(it->first,
                                                                  outVal   );
            
            outVal << ",";
            if(it->second == NULL)
            {
                FieldTraits<UInt32>::putToStream(0, outVal);
            }
            else
            {
                FieldTraits<UInt32>::putToStream(it->second->getId(), outVal);
            }
        }
    }

    static void putToStream   (const FieldContainerMap  &inVal,
                                     OutStream          &outVal,
                               const ContainerIdMapper  &oIDMap      )
    {
        //Loop through all of the map elelments
        FieldContainerMap::const_iterator it = inVal.begin();

        for(; it != inVal.end(); ++it)
        {
            if(it != inVal.begin())
            {
                outVal << ",";
            }

            FieldTraits<FieldContainerMap::key_type>::putToStream(
                oIDMap.map(it->first),
                outVal               );
            
            outVal << ",";

            if(it->second == NULL)
            {
                FieldTraits<UInt32>::putToStream(0, outVal);
            }
            else
            {
                FieldTraits<UInt32>::putToStream(
                    oIDMap.map(it->second->getId()),
                    outVal                         );
            }
        }
    }

    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromCString(      FieldContainerMap  &outVal,
                               const Char8             *&inVal       )
    {
        outVal.clear();

        //Loop through all of the map elelments
        const Char8 *curInString(inVal);

        Int32           iKey               = 0;
        FieldContainer *pValue             = NULL;
        UInt32          uiFieldContainerID = 0;

        while(curInString != NULL)
        {
            //Get the key value
            /*! \todo This is a hack so the Constraints field of SpringLayout
             * loads correctly */

            FieldTraits<FieldContainerMap::key_type>::getFromCString(
                iKey, 
                curInString);

            pValue = FieldContainerFactory::the()->getMappedContainer(iKey);

            if(pValue != NULL)
            {
                iKey = pValue->getId();
            }

            //Move past the ; seperator
            curInString = strchr(curInString, ',');

            ++curInString;

            if(curInString == NULL)
            {
                return false;
            }

            //Get the map value
            FieldTraits<UInt32>::getFromCString(uiFieldContainerID, 
                                                curInString);

            pValue = FieldContainerFactory::the()->getMappedContainer(
                uiFieldContainerID);

            if(pValue == NULL)
            {
                SWARNING << "ERROR in FieldContainerMap::getFromCString(): "
                         << "Could not find Container referenced with Id: " 
                         << uiFieldContainerID 
                         << std::endl;
            }

            //Add the Key/Value pair
            outVal[iKey] = pValue;
            
            //Move past the ; seperator
            curInString = strchr(curInString, ',');

            if(curInString != NULL)
            {
                ++curInString;
            }
        }
        return true;
    }

    // Binary conversion
    static UInt32 getBinSize  (const FieldContainerMap  &oObject     )
    {
        UInt32 uiNumPublicObjects = oObject.size();

        return sizeof(UInt32) +  // Number of elements in the map 
            uiNumPublicObjects * (sizeof(Int32) + sizeof(UInt32));
    }

    static UInt32 getBinSize  (const FieldContainerMap  *pObjectStore,
                                     UInt32              uiNumObjects)
    {
        UInt32 uiSize = 0;

        // defaut: individual field sizes
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            uiSize += getBinSize(pObjectStore[i]);
        }

        return uiSize;
    }

    static void copyToBin     (      BinaryDataHandler  &pMem, 
                               const FieldContainerMap  &pObject     )
    {
        UInt32 uiId               = 0;
        UInt32 uiNumPublicObjects = pObject.size();

        pMem.putValue(uiNumPublicObjects);  //Number of Key/Value pairs

        FieldContainerMap::const_iterator mapIt  = pObject.begin();
        FieldContainerMap::const_iterator mapEnd = pObject.end  ();

        for(; mapIt != mapEnd; ++mapIt)
        {
            uiId = mapIt->second->getId();

            pMem.putValue(mapIt->first);  //Key
            pMem.putValue(uiId        ); //Value = Field Container ID
        }
    }

    static void copyToBin     (      BinaryDataHandler  &pMem, 
                               const FieldContainerMap  *pObjectStore,
                                     UInt32              uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin   (      BinaryDataHandler  &pMem, 
                                     FieldContainerMap  &pObject     )
    {
        FieldContainer *pFC    = NULL;
        Int32           iKey   = 0;
        UInt32          uiId   = 0;
        UInt32          uiSize = 0;

        pMem.getValue(uiSize);
        
        pObject.clear();

        for(UInt32 i = 0; i < uiSize; ++i)
        {
            pMem.getValue(iKey);
            pMem.getValue(uiId);

            pFC = FieldContainerFactory::the()->getMappedContainer(uiId);

            pObject[iKey] = pFC;
        }
    }

    static void copyFromBin   (      BinaryDataHandler  &pMem, 
                                     FieldContainerMap  *pObjectStore,
                                     UInt32              uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERMAPFIELDTRAITS_H_ */


