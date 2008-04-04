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

#ifndef _OSGNODEFIELDTRAITS_H_
#define _OSGNODEFIELDTRAITS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerFieldTraits.h"
#include "OSGDataType.h"

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
struct FieldTraits<NodePtr> : public FieldTraitsFCPtrBase<NodePtr>
{
  private:

    static  DataType             _type;

  public:

    typedef FieldTraits<NodePtr>  Self;
    typedef NodePtr               ParentContainerPtr;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<RecordedRefCounts>(void)
{
    return "SFNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<UnrecordedRefCounts>(void)
{
    return "SFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<WeakRefCounts>(void)
{
    return "SFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<NoRefCounts>(void)
{
    return "SFUnrefdNodePtr"; 
}



template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<RecordedRefCounts>(void)
{
    return "MFNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<UnrecordedRefCounts>(void)
{
    return "MFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<WeakRefCounts>(void)
{
    return "MFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<NoRefCounts>(void)
{
    return "MFUnrefdNodePtr"; 
}

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


OSG_END_NAMESPACE

#endif /* _OSGNODEFIELDTRAITS_H_ */
