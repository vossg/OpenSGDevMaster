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

#ifndef _OSGRENDERFUNCTORFIELDTRAITS_H_
#define _OSGRENDERFUNCTORFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGContainerForwards.h"
#include "OSGGroupDef.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpGroupStageObj
    \ingroup GrpLibOSGGroup
    \nohierarchy
 */

struct RenderFunctorCallback
{
    RenderFunctor  _func;
    UInt32         _uiId;
    std::string    _createSymbol;

    typedef std::allocator<void> Alloc;
};

/*! \ingroup GrpGroupStageFieldTraits
    \ingroup GrpLibOSGGroup
 */

template <>
struct FieldTraits<RenderFunctorCallback> : 
    public FieldTraitsTemplateBase<RenderFunctorCallback>
{
  private:

    static  DataType                            _type;

  public:

    typedef FieldTraits<RenderFunctorCallback>  Self;


    enum             { Convertible = Self::NotConvertible                  };

    static OSG_GROUP_DLLMAPPING
                 DataType &getType      (void);

    static const Char8    *getSName     (void) 
    {
        return "SFRenderFunctorCallback";   
    }

    static const Char8    *getMName     (void)
    { 
        return "MFRenderFunctorCallback";   
    }

    static UInt32 getBinSize(const RenderFunctorCallback &)
    {
        return 0;
    }

    static UInt32 getBinSize(const RenderFunctorCallback *,
                                   UInt32                 uiNumObjects)
    {
        return 0 * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler     &pMem, 
                          const RenderFunctorCallback &pObject)
    {
#if 0
        UInt32 containerId;

        if(pObject == NullFC)
        {
            // containerId=0 indicates an Null Ptr
            containerId = 0;
        }
        else
        {
            containerId = pObject->getId();
        }

        pMem.putValue(containerId);
#endif
    }

    static void copyToBin(      BinaryDataHandler     &pMem, 
                          const RenderFunctorCallback *pObjectStore,
                                UInt32                 uiNumObjects)
    {
#if 0
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
#endif
    }

    static void copyFromBin(BinaryDataHandler     &pMem, 
                            RenderFunctorCallback &pObject)
    {
#if 0
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
#endif
    }

    static void copyFromBin(BinaryDataHandler     &pMem, 
                            RenderFunctorCallback *pObjectStore,
                            UInt32                 uiNumObjects)
    {
#if 0
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
#endif
    }   

};

OSG_END_NAMESPACE

#endif /* _OSGRENDERFUNCTORFIELDTRAITS_H_ */
