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

#ifndef _OSGMEMORYOBJECTFIELDTRAITS_H_
#define _OSGMEMORYOBJECTFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGMemoryObject.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseMemoryObjectsFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<MemoryObject *> : 
    public FieldTraitsPODTemplateBase<MemoryObject *>
{
  private:

    static  DataType            _type;
    
  public:

    typedef FieldTraits<MemoryObject *>  Self;
    typedef MemoryObject *               ArgumentType;
    typedef MemoryObject *               FieldTypeT;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_BASE_DLLMAPPING
                 DataType     &getType   (void);

    template<typename RefCountPolicy> inline
    static const Char8        *getSName  (void);

    template<typename RefCountPolicy> inline
    static const Char8        *getMName  (void);


    static       MemoryObject *getDefault(void) { return NULL; }
    
    // Binary
    
    // TODO Is it correct to just ignore these for binary ??
    
    static UInt32 getBinSize(MemoryObject * const &)
    {
        return 0;
    }

    static UInt32 getBinSize(MemoryObject* const*,
                             UInt32              )
    {
        return 0;
    }

    static void copyToBin(BinaryDataHandler &,
                          MemoryObject      * const & )
    {
    }

    static void copyToBin(BinaryDataHandler &,
                          MemoryObject      * const *,
                          UInt32                      )
    {
    }

    static void copyFromBin(BinaryDataHandler &,
                            MemoryObject      * const & )
    {
    }

    static void copyFromBin(BinaryDataHandler &,
                            MemoryObject      * const *,
                            UInt32                      )
    {
    }
};



template<> inline
const Char8 *FieldTraits<MemoryObject *, 
                         0             >::getMName<MemObjRefCountPolicy>(
                             void)
{
    return "MFMemoryObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<MemoryObject *, 
                         0             >::getSName<MemObjRefCountPolicy>(
                             void)
{
    return "SFMemoryObjectPtr"; 
}


OSG_END_NAMESPACE

#endif /* _OSGMEMORYOBJECTFIELDTRAITS_H_ */
