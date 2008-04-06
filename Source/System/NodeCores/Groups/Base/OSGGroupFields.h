/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGGROUPFIELDS_H_
#define _OSGGROUPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class Group;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! GroupPtr

OSG_GEN_CONTAINERPTR(Group);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<GroupPtr> :
    public FieldTraitsFCPtrBase<GroupPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<GroupPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFGroupPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFGroupPtr"; }
};

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<GroupPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdGroupPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<GroupPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef FieldContainerPtrSField<GroupPtr,
                                RecordedRefCountPolicy  > SFRecGroupPtr;
typedef FieldContainerPtrSField<GroupPtr,
                                UnrecordedRefCountPolicy> SFUnrecGroupPtr;
typedef FieldContainerPtrSField<GroupPtr,
                                WeakRefCountPolicy      > SFWeakGroupPtr;
typedef FieldContainerPtrSField<GroupPtr,
                                NoRefCountPolicy        > SFUncountedGroupPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef FieldContainerPtrMField<GroupPtr,
                                RecordedRefCountPolicy  > MFRecGroupPtr;
typedef FieldContainerPtrMField<GroupPtr,
                                UnrecordedRefCountPolicy> MFUnrecGroupPtr;
typedef FieldContainerPtrMField<GroupPtr,
                                WeakRefCountPolicy      > MFWeakGroupPtr;
typedef FieldContainerPtrMField<GroupPtr,
                                NoRefCountPolicy        > MFUncountedGroupPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGGROUPFIELDS_H_ */
