/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2008 by the OpenSG Forum                          *
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

#ifndef _OSGANYFIELDS_H_
#define _OSGANYFIELDS_H_

#include "OSGContribCSMDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
#include "OSGSField.h"
#include "OSGMField.h"

OSG_BEGIN_NAMESPACE

class Window;

struct OSGAny
{
    bool operator ==(const OSGAny &) const
    {
        return true;
    }
};


template <>
struct FieldTraits<OSGAny> : public FieldTraitsTemplateBase<OSGAny>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<OSGAny>  Self;

    enum             { Convertible = Self::NotConvertible  };

    static OSG_CONTRIBCSM_DLLMAPPING
                 DataType   &getType      (void);

    static const Char8      *getSName     (void) { return "SFAny";    }

    static const Char8      *getMName     (void) { return "MFAny";    }

    static       OSGAny      getDefault   (void) { return OSGAny(); }


    static       UInt32    getBinSize (const OSGAny &oObject)
    {
        return 0; //oObject.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const OSGAny *pObjectStore,
                                             UInt32  uiNumObjects)
    {
        UInt32 size=0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }


    static void copyToBin(      BinaryDataHandler &pMem, 
                          const OSGAny            &oObject)
    {
    	//pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const OSGAny            *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            OSGAny            &oObject)
    {
        //pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            OSGAny            *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

typedef SField<OSGAny> SFOSGAny;
typedef MField<OSGAny> MFOSGAny;

OSG_END_NAMESPACE

#endif
