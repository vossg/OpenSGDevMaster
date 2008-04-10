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

    static  DataType                _type;

  public:

    typedef FieldTraits<NodePtr, 0>  Self;
    typedef NodePtr                  ParentContainerPtr;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdNodePtr"; 
}



template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdNodePtr"; 
}



template <>
struct FieldTraits<NodePtr, 1> : public FieldTraitsFCPtrBase<NodePtr, 1>
{
  private:

  public:

    typedef FieldTraits<NodePtr, 1>  Self;
    typedef NodePtr                  ParentType;

    enum             { Convertible = Self::NotConvertible              };

    static const FieldType::Cardinality eParentCard = FieldType::SingleField;

    static OSG_SYSTEM_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdNodeChildNodePtr"; 
}



template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakNodeChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<NodePtr, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdNodeChildNodePtr"; 
}

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


OSG_END_NAMESPACE

#endif /* _OSGNODEFIELDTRAITS_H_ */
