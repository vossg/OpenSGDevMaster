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


#ifndef _OSGWIN32WINDOWFIELDS_H_
#define _OSGWIN32WINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowWIN32Def.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class WIN32Window;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! WIN32WindowPtr

OSG_GEN_CONTAINERPTR(WIN32Window);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpWindowWIN32FieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<WIN32WindowPtr> :
    public FieldTraitsFCPtrBase<WIN32WindowPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<WIN32WindowPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOWWIN32_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFWIN32WindowPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFWIN32WindowPtr"; }
};

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakWIN32WindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<WIN32WindowPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdWIN32WindowPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<WIN32WindowPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowWIN32FieldSingle */

typedef FieldContainerPtrSField<WIN32WindowPtr,
                                RecordedRefCountPolicy  > SFRecWIN32WindowPtr;
typedef FieldContainerPtrSField<WIN32WindowPtr,
                                UnrecordedRefCountPolicy> SFUnrecWIN32WindowPtr;
typedef FieldContainerPtrSField<WIN32WindowPtr,
                                WeakRefCountPolicy      > SFWeakWIN32WindowPtr;
typedef FieldContainerPtrSField<WIN32WindowPtr,
                                NoRefCountPolicy        > SFUncountedWIN32WindowPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpWindowWIN32FieldMulti */

typedef FieldContainerPtrMField<WIN32WindowPtr,
                                RecordedRefCountPolicy  > MFRecWIN32WindowPtr;
typedef FieldContainerPtrMField<WIN32WindowPtr,
                                UnrecordedRefCountPolicy> MFUnrecWIN32WindowPtr;
typedef FieldContainerPtrMField<WIN32WindowPtr,
                                WeakRefCountPolicy      > MFWeakWIN32WindowPtr;
typedef FieldContainerPtrMField<WIN32WindowPtr,
                                NoRefCountPolicy        > MFUncountedWIN32WindowPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGWIN32WINDOWFIELDS_H_ */
