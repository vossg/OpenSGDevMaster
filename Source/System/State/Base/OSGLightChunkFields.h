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


#ifndef _OSGLIGHTCHUNKFIELDS_H_
#define _OSGLIGHTCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class LightChunk;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! LightChunkPtr

OSG_GEN_CONTAINERPTR(LightChunk);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<LightChunkPtr> :
    public FieldTraitsFCPtrBase<LightChunkPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<LightChunkPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFLightChunkPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFLightChunkPtr"; }
};

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakLightChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LightChunkPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdLightChunkPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<LightChunkPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef FieldContainerPtrSField<LightChunkPtr,
                                RecordedRefCountPolicy  > SFRecLightChunkPtr;
typedef FieldContainerPtrSField<LightChunkPtr,
                                UnrecordedRefCountPolicy> SFUnrecLightChunkPtr;
typedef FieldContainerPtrSField<LightChunkPtr,
                                WeakRefCountPolicy      > SFWeakLightChunkPtr;
typedef FieldContainerPtrSField<LightChunkPtr,
                                NoRefCountPolicy        > SFUncountedLightChunkPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef FieldContainerPtrMField<LightChunkPtr,
                                RecordedRefCountPolicy  > MFRecLightChunkPtr;
typedef FieldContainerPtrMField<LightChunkPtr,
                                UnrecordedRefCountPolicy> MFUnrecLightChunkPtr;
typedef FieldContainerPtrMField<LightChunkPtr,
                                WeakRefCountPolicy      > MFWeakLightChunkPtr;
typedef FieldContainerPtrMField<LightChunkPtr,
                                NoRefCountPolicy        > MFUncountedLightChunkPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGLIGHTCHUNKFIELDS_H_ */
