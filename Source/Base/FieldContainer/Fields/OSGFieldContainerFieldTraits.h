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
#include "OSGFieldContainer.h"
#include "OSGRefCountPolicies.h"

OSG_BEGIN_NAMESPACE


/*! \ingroup GrpBaseFieldContainerFieldTraits
 */

template<class ValueT, Int32 iNamespace = 0>
struct FieldTraitsFCPtrBase : 
    public FieldTraitsTemplateBase<ValueT, iNamespace>
{
    static const bool bIsPointerField = true;

    static const Char8 *getSPName(void)
    {
        return "FieldContainerPtrSFieldBase";   
    }

    static const Char8 *getMPName(void) 
    {
        return "FieldContainerPtrMFieldBase";   
    }

    static UInt32 getBinSize(FieldContainer * const &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(FieldContainer * const *,
                             UInt32                  uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static void copyToBin(BinaryDataHandler         &pMem, 
                          FieldContainer    * const &pObject)
    {
        UInt32 containerId;

        if(pObject == NULL)
        {
            // containerId=0 indicates an Null Ptr
            containerId = 0;
        }
        else
        {
            containerId = pObject->getId();
        }

        pMem.putValue(containerId);
    }

    static void copyToBin(BinaryDataHandler         &pMem, 
                          FieldContainer    * const *pObjectStore,
                          UInt32                     uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler  &pMem, 
                            FieldContainer    *&pObject)
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
            pObject = NULL;
        }
    }

    static void copyFromBin(BinaryDataHandler & pMem, 
                            FieldContainer    **pObjectStore,
                            UInt32              uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }   
};


/*! \ingroup GrpBaseFieldContainerFieldTraits
 */

template <>
struct FieldTraits<FieldContainer *> : 
    public FieldTraitsFCPtrBase<FieldContainer *>
{
  private:

    static  DataType                       _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<FieldContainer *>  Self;


    enum             { Convertible = Self::NotConvertible                 };

    static OSG_BASE_DLLMAPPING
                 DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName(void);
};


template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getSName<RecordedRefCountPolicy>(
                             void)
{
    return "SFRecFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getSName<UnrecordedRefCountPolicy>(
                             void)
{
    return "SFUnrecFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFieldContainerPtr"; 
}



template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getMName<RecordedRefCountPolicy>(
                             void)
{
    return "MFRecFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getMName<UnrecordedRefCountPolicy>(
                             void)
{
    return "MFUnrecFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FieldContainer *, 
                         0               >::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFieldContainerPtr"; 
}


/*! \ingroup GrpBaseFieldContainerFieldTraits
 */

template <>
struct FieldTraits<FieldContainer *, 1> : 
    public FieldTraitsFCPtrBase<FieldContainer *, 1>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<FieldContainer *, 1>        Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_BASE_DLLMAPPING
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

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFIELDTRAITS_H_ */
