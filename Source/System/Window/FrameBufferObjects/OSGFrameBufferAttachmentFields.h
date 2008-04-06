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


#ifndef _OSGFRAMEBUFFERATTACHMENTFIELDS_H_
#define _OSGFRAMEBUFFERATTACHMENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class FrameBufferAttachment;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! FrameBufferAttachmentPtr

OSG_GEN_CONTAINERPTR(FrameBufferAttachment);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<FrameBufferAttachmentPtr> :
    public FieldTraitsFCPtrBase<FrameBufferAttachmentPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<FrameBufferAttachmentPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFFrameBufferAttachmentPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFFrameBufferAttachmentPtr"; }
};

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachmentPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFrameBufferAttachmentPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<FrameBufferAttachmentPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldSingle */

typedef FieldContainerPtrSField<FrameBufferAttachmentPtr,
                                RecordedRefCountPolicy  > SFRecFrameBufferAttachmentPtr;
typedef FieldContainerPtrSField<FrameBufferAttachmentPtr,
                                UnrecordedRefCountPolicy> SFUnrecFrameBufferAttachmentPtr;
typedef FieldContainerPtrSField<FrameBufferAttachmentPtr,
                                WeakRefCountPolicy      > SFWeakFrameBufferAttachmentPtr;
typedef FieldContainerPtrSField<FrameBufferAttachmentPtr,
                                NoRefCountPolicy        > SFUncountedFrameBufferAttachmentPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpSystemFieldMulti */

typedef FieldContainerPtrMField<FrameBufferAttachmentPtr,
                                RecordedRefCountPolicy  > MFRecFrameBufferAttachmentPtr;
typedef FieldContainerPtrMField<FrameBufferAttachmentPtr,
                                UnrecordedRefCountPolicy> MFUnrecFrameBufferAttachmentPtr;
typedef FieldContainerPtrMField<FrameBufferAttachmentPtr,
                                WeakRefCountPolicy      > MFWeakFrameBufferAttachmentPtr;
typedef FieldContainerPtrMField<FrameBufferAttachmentPtr,
                                NoRefCountPolicy        > MFUncountedFrameBufferAttachmentPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGFRAMEBUFFERATTACHMENTFIELDS_H_ */
