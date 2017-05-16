/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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


#ifndef _OSGUNIFORMBUFFEROBJBASECHUNKFIELDS_H_
#define _OSGUNIFORMBUFFEROBJBASECHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class UniformBufferObjBaseChunk;

OSG_GEN_CONTAINERPTR(UniformBufferObjBaseChunk);
/*! \ingroup GrpSystemStateFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<UniformBufferObjBaseChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<UniformBufferObjBaseChunk *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<UniformBufferObjBaseChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakUniformBufferObjBaseChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<UniformBufferObjBaseChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdUniformBufferObjBaseChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<UniformBufferObjBaseChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<UniformBufferObjBaseChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<UniformBufferObjBaseChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<UniformBufferObjBaseChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedUniformBufferObjBaseChunkPtr;


/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<UniformBufferObjBaseChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<UniformBufferObjBaseChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<UniformBufferObjBaseChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakUniformBufferObjBaseChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<UniformBufferObjBaseChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedUniformBufferObjBaseChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecUniformBufferObjBaseChunkPtr : 
    public PointerSField<UniformBufferObjBaseChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecUniformBufferObjBaseChunkPtr : 
    public PointerSField<UniformBufferObjBaseChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakUniformBufferObjBaseChunkPtr :
    public PointerSField<UniformBufferObjBaseChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedUniformBufferObjBaseChunkPtr :
    public PointerSField<UniformBufferObjBaseChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecUniformBufferObjBaseChunkPtr :
    public PointerMField<UniformBufferObjBaseChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecUniformBufferObjBaseChunkPtr :
    public PointerMField<UniformBufferObjBaseChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakUniformBufferObjBaseChunkPtr :
    public PointerMField<UniformBufferObjBaseChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedUniformBufferObjBaseChunkPtr :
    public PointerMField<UniformBufferObjBaseChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGUNIFORMBUFFEROBJBASECHUNKFIELDS_H_ */
