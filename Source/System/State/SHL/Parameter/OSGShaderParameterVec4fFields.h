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


#ifndef _OSGSHADERPARAMETERVEC4FFIELDS_H_
#define _OSGSHADERPARAMETERVEC4FFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class ShaderParameterVec4f;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! ShaderParameterVec4fPtr

OSG_GEN_CONTAINERPTR(ShaderParameterVec4f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ShaderParameterVec4fPtr> :
    public FieldTraitsFCPtrBase<ShaderParameterVec4fPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderParameterVec4fPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFShaderParameterVec4fPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFShaderParameterVec4fPtr"; }
};

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderParameterVec4fPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterVec4fPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderParameterVec4fPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ShaderParameterVec4fPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef FieldContainerPtrSField<ShaderParameterVec4fPtr,
                                RecordedRefCountPolicy  > SFRecShaderParameterVec4fPtr;
typedef FieldContainerPtrSField<ShaderParameterVec4fPtr,
                                UnrecordedRefCountPolicy> SFUnrecShaderParameterVec4fPtr;
typedef FieldContainerPtrSField<ShaderParameterVec4fPtr,
                                WeakRefCountPolicy      > SFWeakShaderParameterVec4fPtr;
typedef FieldContainerPtrSField<ShaderParameterVec4fPtr,
                                NoRefCountPolicy        > SFUncountedShaderParameterVec4fPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef FieldContainerPtrMField<ShaderParameterVec4fPtr,
                                RecordedRefCountPolicy  > MFRecShaderParameterVec4fPtr;
typedef FieldContainerPtrMField<ShaderParameterVec4fPtr,
                                UnrecordedRefCountPolicy> MFUnrecShaderParameterVec4fPtr;
typedef FieldContainerPtrMField<ShaderParameterVec4fPtr,
                                WeakRefCountPolicy      > MFWeakShaderParameterVec4fPtr;
typedef FieldContainerPtrMField<ShaderParameterVec4fPtr,
                                NoRefCountPolicy        > MFUncountedShaderParameterVec4fPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGSHADERPARAMETERVEC4FFIELDS_H_ */
