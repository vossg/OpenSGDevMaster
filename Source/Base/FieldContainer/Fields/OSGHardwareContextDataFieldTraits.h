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

#ifndef _OSGHARDWARECONTEXTDATAFIELDTRAITS_H_
#define _OSGHARDWARECONTEXTDATAFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGHardwareContextData.h"

OSG_BEGIN_NAMESPACE


/*! \ingroup GrpBaseMemoryObjectsFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<HardwareContextData *> : 
    public FieldTraitsPODTemplateBase<HardwareContextData *>
{
  private:

    static  DataType            _type;
    
  public:

    typedef FieldTraits<HardwareContextData *>  Self;
    typedef HardwareContextData *               ArgumentType;
    typedef HardwareContextData *               FieldTypeT;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_BASE_DLLMAPPING
                 DataType     &getType   (void);

    template<typename RefCountPolicy> inline
    static const Char8        *getSName  (void);

    template<typename RefCountPolicy> inline
    static const Char8        *getMName  (void);


    static       HardwareContextData *getDefault(void) { return NULL; }
    
    // Binary
    
    // TODO Is it correct to just ignore these for binary ??
    
    static UInt32 getBinSize(HardwareContextData * const &)
    {
        return 0;
    }

    static UInt32 getBinSize(HardwareContextData* const*,
                             UInt32                      )
    {
        return 0;
    }

    static void copyToBin(BinaryDataHandler   &,
                          HardwareContextData * const &  )
    {
    }

    static void copyToBin(BinaryDataHandler   &,
                          HardwareContextData * const *,
                          UInt32                         )
    {
    }

    static void copyFromBin(BinaryDataHandler   &,
                            HardwareContextData * const &)
    {
    }

    static void copyFromBin(BinaryDataHandler   &,
                            HardwareContextData * const *,
                            UInt32                       )
    {
    }
};



template<> inline
const Char8 *FieldTraits<HardwareContextData *, 
                         0                    >::getMName<MemObjRefCountPolicy>(
                             void)
{
    return "MFHardwareContextDataPtr"; 
}

template<> inline
const Char8 *FieldTraits<HardwareContextData *, 
                         0                    >::getSName<MemObjRefCountPolicy>(
                             void)
{
    return "SFHardwareContextDataPtr"; 
}

OSG_END_NAMESPACE

#endif /* _OSGHARDWARECONTEXTDATAFIELDTRAITS_H_ */
