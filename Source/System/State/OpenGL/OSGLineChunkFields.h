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


#ifndef _OSGLINECHUNKFIELDS_H_
#define _OSGLINECHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class LineChunk;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! LineChunkPtr

OSG_GEN_CONTAINERPTR(LineChunk);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<LineChunkPtr> :
    public FieldTraitsFCPtrBase<LineChunkPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<LineChunkPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFLineChunkPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFLineChunkPtr"; }
};

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunkPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdLineChunkPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<LineChunkPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef FieldContainerPtrSField<LineChunkPtr,
                                RecordedRefCountPolicy  > SFRecLineChunkPtr;
typedef FieldContainerPtrSField<LineChunkPtr,
                                UnrecordedRefCountPolicy> SFUnrecLineChunkPtr;
typedef FieldContainerPtrSField<LineChunkPtr,
                                WeakRefCountPolicy      > SFWeakLineChunkPtr;
typedef FieldContainerPtrSField<LineChunkPtr,
                                NoRefCountPolicy        > SFUncountedLineChunkPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef FieldContainerPtrMField<LineChunkPtr,
                                RecordedRefCountPolicy  > MFRecLineChunkPtr;
typedef FieldContainerPtrMField<LineChunkPtr,
                                UnrecordedRefCountPolicy> MFUnrecLineChunkPtr;
typedef FieldContainerPtrMField<LineChunkPtr,
                                WeakRefCountPolicy      > MFWeakLineChunkPtr;
typedef FieldContainerPtrMField<LineChunkPtr,
                                NoRefCountPolicy        > MFUncountedLineChunkPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGLINECHUNKFIELDS_H_ */
