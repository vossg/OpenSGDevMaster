/*---------------------------------------------------------------------------*\
 *                         OpenSG Toolbox Toolbox                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSG_BOOSTPATHFIELDTRAITS_H_
#define _OSG_BOOSTPATHFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGBaseFieldTraits.h"

#include <boost/filesystem/path.hpp>

OSG_BEGIN_NAMESPACE

typedef boost::filesystem::path BoostPath;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have


template <>
struct FieldTraits<BoostPath> : public FieldTraitsTemplateBase<BoostPath>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType                 _type;

    typedef FieldTraits<BoostPath>   Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.

    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING 
                 DataType       &getType      (void);

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFBoostPath"; }
    static const Char8          *getMName     (void) { return "MFBoostPath"; }

    // Create a default instance of the class, needed for Field creation
    static       BoostPath       getDefault   (void) { return BoostPath();   }


    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    static void putToStream(const BoostPath &inVal,
                                  OutStream &outVal)
    {
        outVal << inVal.string();
    }
    
    // Setup outVal from the contents of inVal
    static bool getFromCString(      BoostPath  &outVal,
                               const Char8     *&inVal)
    {
        std::string oPathString("");

        if(FieldTraits<std::string>::getFromCString(oPathString, inVal))
        {
            outVal = oPathString;

            return true;
        }
        else
        {
            return false;
        }
    }

    // Binary conversion
    
    // Return the size of the binary version in byte   
    static UInt32 getBinSize(const BoostPath &oObj)
    {
        return FieldTraits<std::string>::getBinSize(oObj.string());
    }

    static UInt32 getBinSize(const BoostPath *pObjStore, 
                                   UInt32     uiNumObjs)
    {
        //Size:
        //Sum of all the objs
        UInt32 uiSizeSum = 0;

        for(UInt32 i = 0; i < uiNumObjs; ++i)
        {
            uiSizeSum += 
                FieldTraits<std::string>::getBinSize(pObjStore[i].string());
        }

        return uiSizeSum;
    }

    // Copy the object into the BinaryDataHandler
    static void copyToBin   (      BinaryDataHandler &oMem, 
                             const BoostPath         &oObj)
    {
        FieldTraits<std::string>::copyToBin(oMem, oObj.string());
    }

    static void copyToBin   (      BinaryDataHandler &oMem,
                             const BoostPath         *pObjStore,
                                   UInt32             uiNumObjs)
    {
        for(UInt32 i = 0; i < uiNumObjs; ++i)
        {
            copyToBin(oMem, pObjStore[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    static void copyFromBin (      BinaryDataHandler &oMem, 
                                   BoostPath         &oObj)
    {
        std::string oPathString("");

        FieldTraits<std::string>::copyFromBin(oMem, oPathString);

        oObj = oPathString;
    }

    static void copyFromBin (      BinaryDataHandler &oMem,
                                   BoostPath         *pObjStore,
                                   UInt32             uiNum)
    {
        for(UInt32 i = 0; i < uiNum; ++i)
        {
            copyFromBin(oMem, pObjStore[i]);
        }
    }
};


OSG_END_NAMESPACE

#endif /* _OSG_PATH_TYPE_H_ */


