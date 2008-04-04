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

#ifndef _OSGFIELDCONTAINERFIELDTRAITS_H_
#define _OSGFIELDCONTAINERFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGContainerForwards.h"
#include "OSGFieldContainerFactory.h"
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
struct FieldTraitsFCPtrBase : 
    public FieldTraitsTemplateBase<ValueT, iNamespace>
{
    static const bool bIsPointerField = true;

    typedef FieldContainerPtr ParentContainerPtr;

    static const Char8 *getSPName(void)
    {
        return "FieldContainerPtrSFieldBase";   
    }

    static const Char8 *getMPName(void) 
    {
        return "FieldContainerPtrMFieldBase";   
    }

    static UInt32 getBinSize(const FieldContainerPtr &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(const FieldContainerPtr *,
                                   UInt32             uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldContainerPtr &pObject)
    {
        UInt32 containerId;

        if(pObject == NullFC)
        {
            // containerId=0 indicates an Null Ptr
            containerId = 0;
        }
        else
        {
            containerId = getContainerId(pObject);
        }

        pMem.putValue(containerId);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldContainerPtr *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerPtr &pObject)
    {
        UInt32 containerId;

        pMem.getValue(containerId);

        if(0 != containerId)
        {
            pObject = 
                FieldContainerFactory::the()->getMappedContainer(containerId);
        }
        else
        {
            pObject = NullFC;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerPtr *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }   
};

#if 0
template<>
struct FieldTraitsFCPtrBase<ParentFieldContainerPtr> : 
    public FieldTraitsTemplateBase<ParentFieldContainerPtr>
{
    static const bool bIsPointerField = true;

    static UInt32 getBinSize(const ParentFieldContainerPtr &)
    {
        return sizeof(UInt32) + sizeof(UInt16);
    }

    static UInt32 getBinSize(const ParentFieldContainerPtr *,
                                   UInt32                   uiNumObjects)
    {
        return (sizeof(UInt32) + sizeof(UInt16)) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler       &pMem, 
                          const ParentFieldContainerPtr &pObject)
    {
        UInt32 containerId;

        if(pObject == NullFC)
        {
            // containerId=0 indicates an Null Ptr
            containerId = 0;
        }
        else
        {
            containerId = getContainerId(pObject);
        }

        pMem.putValue(containerId);
        pMem.putValue(pObject.getParentFieldPos());
    }

    static void copyToBin(      BinaryDataHandler       &pMem, 
                          const ParentFieldContainerPtr *pObjectStore,
                                UInt32                   uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler       &pMem, 
                            ParentFieldContainerPtr &pObject)
    {
        UInt32 containerId;
        UInt16 parentFieldPos;

        pMem.getValue(containerId   );
        pMem.getValue(parentFieldPos);

        if(0 != containerId)
        {
            pObject.set(
                FieldContainerFactory::the()->getMappedContainer(containerId),
                parentFieldPos);
        }
        else
        {
            pObject = NullFC;
        }
    }

    static void copyFromBin(BinaryDataHandler       &pMem, 
                            ParentFieldContainerPtr *pObjectStore,
                            UInt32                   uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};
#endif

/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FieldContainerPtr> : 
    public FieldTraitsFCPtrBase<FieldContainerPtr>
{
  private:

    static  DataType                       _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<FieldContainerPtr>  Self;


    enum             { Convertible = Self::NotConvertible                 };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) { return "SFFieldContainerPtr"; }

    static const Char8    *getMName(void) { return "MFFieldContainerPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<FieldContainerPtr> */
/*! \hideinhierarchy                         */
#endif


/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif
template <>
struct FieldTraits<FieldContainerPtr, 1> : 
    public FieldTraitsFCPtrBase<FieldContainerPtr, 1>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<FieldContainerPtr, 1>        Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentFieldContainerPtr"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentFieldContainerPtr"; 
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ParentFieldContainerPtr> */
/*! \hideinhierarchy                         */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

struct RecordedRefCounts
{
    static void addRef(FieldContainerPtrConst objectP)
    {
        OSG::addRefX(objectP);
    }
    static void subRef(FieldContainerPtrConst objectP)
    {
        OSG::subRefX(objectP);
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        OSG::setRefdX(pTarget, pSource);
    }

    template<class T>
    static T *validate(T *pIn)
    {
        return pIn;
    }

    template<class T>
    static T &dereference(T *pIn)
    {
        return *pIn;
    }
};

struct UnrecordedRefCounts
{
};

struct NoRefCounts
{
    static void addRef(FieldContainerPtrConst)
    {
    }
    static void subRef(FieldContainerPtrConst)
    {
    }

    template <class StoreT, class SourceT> 
    static void setRefd(StoreT  &pTarget,
                        SourceT  pSource)
    {
        pTarget = pSource;
    }

    template<class T>
    static T *validate(T *pIn)
    {
        return pIn;
    }

};

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFIELDTRAITS_H_ */
