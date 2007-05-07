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

#ifndef _OSGFIELDBUNDLEFIELDTRAITS_H_
#define _OSGFIELDBUNDLEFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGContainerForwards.h"
#include "OSGFieldBundleFactory.h"
#include "OSGContainerPtrFuncs.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file 
    \ingroup 
    \ingroup 
*/
#endif

template<class ValueT, Int32 iNamespace = 0>
struct FieldTraitsFBPtrBase : 
    public FieldTraitsTemplateBase<ValueT, iNamespace>
{
    static UInt32 getBinSize(const FieldBundleP &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(const FieldBundleP *,
                                   UInt32        uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldBundleP      &pObject)
    {
        UInt32 id = 0;

        if(pObject == NilP)
        {
            // id=0 indicates an Null Ptr
            id = 0;
        }
        else
        {
//            id = getBundleId(pObject);
        }

        pMem.putValue(id);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldBundleP      *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldBundleP      &pObject)
    {
        UInt32 id;

        pMem.getValue(id);

        if(0 != id)
        {
            pObject = FieldBundleFactory::the()->getMappedContainer(id);
        }
        else
        {
            pObject = NullFC;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldBundleP      *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }   
};

template<>
struct FieldTraitsFBPtrBase<ParentFieldBundleP, 1> : 
    public FieldTraitsTemplateBase<ParentFieldBundleP, 1>
{
    static UInt32 getBinSize(const ParentFieldBundleP &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(const ParentFieldBundleP *,
                                   UInt32              uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler  & OSG_CHECK_ARG(pMem),
                          const ParentFieldBundleP & OSG_CHECK_ARG(pObject))
    {
    }
    static void copyToBin(      BinaryDataHandler  &pMem, 
                          const ParentFieldBundleP *pObjectStore,
                                UInt32              uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler  & OSG_CHECK_ARG(pMem),
                            ParentFieldBundleP & OSG_CHECK_ARG(pObject))
    {
    }
    static void copyFromBin(BinaryDataHandler  & OSG_CHECK_ARG(pMem),
                            ParentFieldBundleP * OSG_CHECK_ARG(pObjectStore),
                            UInt32               OSG_CHECK_ARG(uiNumObjects))
    {
    }
};

/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FieldBundleP> : 
    public FieldTraitsFBPtrBase<FieldBundleP>
{
  private:

    static  DataType                  _type;

  public:

    typedef FieldTraits<FieldBundleP>  Self;


    enum             { Convertible = Self::NotConvertible                 };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) { return "SFFieldBundleP"; }

    static const Char8    *getMName(void) { return "MFFieldBundleP"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<FieldBundleP> */
/*! \hideinhierarchy                         */
#endif


/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ParentFieldBundleP, 1> : 
    public FieldTraitsFBPtrBase<ParentFieldBundleP, 1>
{
  private:

    static  DataType                                _type;

  public:

    typedef FieldTraits<ParentFieldBundleP, 1>  Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentFieldBundleP"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentFieldBundleP"; 
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ParentFieldBundleP> */
/*! \hideinhierarchy                         */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGFIELDBUNDLEFIELDTRAITS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGFIELDBUNDLEFIELDTRAITS_H_ */
