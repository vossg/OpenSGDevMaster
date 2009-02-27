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

/*! \ingroup GrpBaseFieldContainerFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<Node *> : public FieldTraitsFCPtrBase<Node *>
{
  private:

    static  DataType                _type;

  public:

    typedef FieldTraits<Node *, 0>   Self;

    enum             { Convertible = Self::NotConvertible              };

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<Node *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdNodePtr"; 
}



template<> inline
const Char8 *FieldTraits<Node *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdNodePtr"; 
}



/*! \ingroup GrpBaseFieldContainerFieldTraits
    \ingroup GrpLibOSGBase
 */

template <>
struct FieldTraits<Node *, 1> : public FieldTraitsFCPtrBase<Node *, 1>
{
  private:

  public:

    typedef FieldTraits<Node *, 1>  Self;

    enum             { Convertible = Self::NotConvertible              };

    static const FieldType::Cardinality eParentCard = FieldType::SingleField;

    static OSG_BASE_DLLMAPPING
                 DataType &getType      (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<Node *, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildNodePtr"; 
}



template<> inline
const Char8 *FieldTraits<Node *, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChildNodePtr"; 
}

template<> inline
const Char8 *FieldTraits<Node *, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChildNodePtr"; 
}

OSG_END_NAMESPACE

#endif /* _OSGNODEFIELDTRAITS_H_ */
