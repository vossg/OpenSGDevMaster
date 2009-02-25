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

#ifndef _OSGCHANGEDFUNCTORFIELDTRAITS_H_
#define _OSGCHANGEDFUNCTORFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerFieldTraits
 */

template <>
struct FieldTraits<ChangedFunctorCallback> : 
    public FieldTraitsTemplateBase<ChangedFunctorCallback>
{
  private:

    static  DataType                            _type;

  public:

    typedef FieldTraits<ChangedFunctorCallback>  Self;


    enum             { Convertible = Self::NotConvertible                  };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) 
    {
        return "SFChangedFunctorCallback";   
    }

    static const Char8    *getMName     (void)
    { 
        return "MFChangedFunctorCallback";   
    }


    static UInt32 getBinSize(const ChangedFunctorCallback &)
    {
        return 0; //sizeof(ValueT);
    }

    static UInt32 getBinSize(const ChangedFunctorCallback *,
                                   UInt32                  uiNumObjects)
    {
        return 0; //sizeof(ValueT) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler      &pMem,
                          const ChangedFunctorCallback &oObject)
    {
//        pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler      &pMem,
                          const ChangedFunctorCallback *pObjectStore,
                                UInt32                  uiNumObjects)
    {
//        pMem.putValues(&(pObjectStore[0]), uiNumObjects);
    }

    static void copyFromBin(BinaryDataHandler      &pMem,
                            ChangedFunctorCallback &oObject)
    {
//        pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler      &pMem,
                            ChangedFunctorCallback *pObjectStore,
                            UInt32                  uiNumObjects)
    {
//        pMem.getValues(&(pObjectStore[0]), uiNumObjects);
    }
};

OSG_END_NAMESPACE

#endif /* _OSGCHANGEDFUNCTORFIELDTRAITS_H_ */
