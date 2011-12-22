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

#ifndef _OSGINT32TOSTRINGMAP_H_
#define _OSGINT32TOSTRINGMAP_H_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseTypes.h"
#include "OSGSysFieldTraits.h"
#include "OSGBaseFieldTraits.h"

#include <string>
#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, std::string> Int32ToStringMap;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<Int32ToStringMap> : 
    public FieldTraitsTemplateBase<Int32ToStringMap>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType                        _type;

    typedef FieldTraits<Int32ToStringMap>   Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING 
                 DataType         &getType    (void);

    // Access to the names of the actual Fields
    static const Char8            *getSName   (void) 
    { 
        return "SFInt32ToStringMap"; 
    }

    static const Char8            *getMName   (void) 
    {
        return "MFInt32ToStringMap"; 
    }

    // Create a default instance of the class, needed for Field creation
    static       Int32ToStringMap  getDefault(void) 
    {
        return Int32ToStringMap();   
    }

    
    // String conversion

    // Output inVal into outVal
    static void putToStream   (const Int32ToStringMap  &inVal,
                                     OutStream         &outVal)
    {
        //Put the Size of the map
        FieldTraits<UInt32>::putToStream(static_cast<UInt32>(inVal.size()),
                                         outVal);

        //Loop through all of the map elelments
        Int32ToStringMap::const_iterator it = inVal.begin();

        for(; it != inVal.end(); ++it)
        {
            outVal << ",";
            FieldTraits<Int32ToStringMap::key_type>::putToStream(it->first,
                                                                 outVal   );

            outVal << ",";
            FieldTraits<Int32ToStringMap::mapped_type>::putToStream(
                it->second,
                outVal    );
        }
    }

    // Setup outVal from the contents of inVal
    static bool getFromCString(      Int32ToStringMap  &outVal,
                               const Char8            *&inVal )
    {
        //Get Size of the map
        UInt32 uiSize = 0;

        if(sscanf(inVal,"%d", &uiSize) != 1)
        {
            return false;
        }

        outVal.clear();

        //Loop through all of the map elelments
        const Char8 *curInString = inVal;

        Int32       iKey;
        std::string szValue;

        for(UInt32 i = 0; i < uiSize ; ++i)
        {
            //Move past the ; seperator
            curInString = strchr(curInString, ',');

            ++curInString;

            if(curInString == NULL)
            {
                return false;
            }

            //Get the key value
            FieldTraits<Int32ToStringMap::key_type>::getFromCString(
                iKey, 
                curInString);

            //Move past the ; seperator
            curInString = strchr(curInString, ',');
            
            ++curInString;

            if(curInString == NULL)
            {
                return false;
            }

            //Move past the ; seperator
            curInString = strchr(curInString, '\"');

            ++curInString;

            if(curInString == NULL)
            {
                return false;
            }

            //Get the map value
            szValue.assign(curInString, 
                         (strchr(curInString, '\"') - curInString));

            //Move past the map value
            curInString = strchr(curInString, '\"');
            ++curInString;
            //if(curInString == NULL)
            //{
            //    return false;
            //}

            //Add the Key/Value pair
            outVal[iKey] = szValue;
        }

        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    static SizeT getBinSize  (const Int32ToStringMap  &obj   )
    {
        //Size:
        //Size of a Int32 -> number of items in the Map
        //Sum of all the sizes of the strings
        SizeT uiStringSizeSum = 0;

        Int32ToStringMap::const_iterator it = obj.begin();

        for(; it != obj.end() ; ++it)
        {
            uiStringSizeSum += FieldTraits<std::string>::getBinSize(it->second);
        }

        return sizeof(UInt32) + obj.size() * sizeof(Int32) + uiStringSizeSum;
    }

    static SizeT  getBinSize  (const Int32ToStringMap  *obj, 
                                     SizeT              num   )
    {
        //Size:
        //Sum of all the objs
        SizeT uiSizeSum = 0;

        for(SizeT i = 0; i < num; ++i)
        {
            uiSizeSum += getBinSize(obj[i]);
        }

        return uiSizeSum;
    }

    // Copy the object into the BinaryDataHandler
    static void copyToBin     (      BinaryDataHandler &bdh, 
                               const Int32ToStringMap  &obj   )
    {
        //Number of items in the map
        bdh.putValue(static_cast<UInt32>(obj.size()));

        //Loop through all of the map elelments
        Int32ToStringMap::const_iterator it = obj.begin();

        for(; it != obj.end(); ++it)
        {
            bdh.putValue(
                static_cast<Int32ToStringMap::key_type   >(it->first));

            bdh.putValue(
                static_cast<Int32ToStringMap::mapped_type>(it->second));
        }
    }

    static void copyToBin     (      BinaryDataHandler &bdh,
                               const Int32ToStringMap  *objs,
                                     SizeT              num   )
    {
        for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    
    // Copy the object from the BinaryDataHandler
    static void copyFromBin   (      BinaryDataHandler &bdh, 
                                     Int32ToStringMap  &obj   )
    {
        //Number of items in the list
        UInt32 uiSize = 0;

        bdh.getValue(uiSize);

        obj.clear();
        
        Int32       iKey;
        std::string szValue;

        //Loop through all of the map elelments
        for(UInt32 i = 0; i < uiSize ; ++i)
        {
            bdh.getValue(iKey);

            FieldTraits<Int32ToStringMap::mapped_type>::copyFromBin(bdh, 
                                                                    szValue);

            obj[iKey] = szValue;
        }
    }

    static void copyFromBin   (      BinaryDataHandler &bdh,
                                     Int32ToStringMap  *objs,
                                     SizeT              num   )
    {
        for(SizeT i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};



OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_STRING_MAP_TYPE_H_ */


