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

#ifndef _OSGNODECOREFIELDTRAITS_H_
#define _OSGNODECOREFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldTraits.h"
#include "OSGDataType.h"

#include "OSGFieldContainerFieldTraits.h"
#include "OSGContainerForwards.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file 
    \ingroup 
    \ingroup 
*/
#endif

/*! \ingroup 
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<NodeCorePtr> : 
    public FieldTraitsFCPtrBase<NodeCorePtr>
{
  private:

    static  DataType                 _type;

  public:

    typedef FieldTraits<NodeCorePtr>  Self;


    enum             { Convertible = Self::NotConvertible                  };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getSName<RecordedRefCounts>(void)
{
    return "SFNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getSName<UnrecordedRefCounts>(void)
{
    return "SFUnrecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getSName<WeakRefCounts>(void)
{
    return "SFWeakNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getSName<NoRefCounts>(void)
{
    return "SFUnrefdNodeCorePtr"; 
}



template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getMName<RecordedRefCounts>(void)
{
    return "MFNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getMName<UnrecordedRefCounts>(void)
{
    return "MFUnrecNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getMName<WeakRefCounts>(void)
{
    return "MFWeakNodeCorePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodeCorePtr, 0>::getMName<NoRefCounts>(void)
{
    return "MFUnrefdNodeCorePtr"; 
}

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSGNODECOREFIELDTRAITS_H_ */
