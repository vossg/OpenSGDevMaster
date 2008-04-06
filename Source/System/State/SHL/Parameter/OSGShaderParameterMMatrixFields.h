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


#ifndef _OSGSHADERPARAMETERMMATRIXFIELDS_H_
#define _OSGSHADERPARAMETERMMATRIXFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class ShaderParameterMMatrix;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! ShaderParameterMMatrixPtr

OSG_GEN_CONTAINERPTR(ShaderParameterMMatrix);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ShaderParameterMMatrixPtr> :
    public FieldTraitsFCPtrBase<ShaderParameterMMatrixPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderParameterMMatrixPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFShaderParameterMMatrixPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFShaderParameterMMatrixPtr"; }
};

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderParameterMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterMMatrixPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderParameterMMatrixPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ShaderParameterMMatrixPtr, 0>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef FieldContainerPtrSField<ShaderParameterMMatrixPtr,
                                RecordedRefCountPolicy  > SFRecShaderParameterMMatrixPtr;
typedef FieldContainerPtrSField<ShaderParameterMMatrixPtr,
                                UnrecordedRefCountPolicy> SFUnrecShaderParameterMMatrixPtr;
typedef FieldContainerPtrSField<ShaderParameterMMatrixPtr,
                                WeakRefCountPolicy      > SFWeakShaderParameterMMatrixPtr;
typedef FieldContainerPtrSField<ShaderParameterMMatrixPtr,
                                NoRefCountPolicy        > SFUncountedShaderParameterMMatrixPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef FieldContainerPtrMField<ShaderParameterMMatrixPtr,
                                RecordedRefCountPolicy  > MFRecShaderParameterMMatrixPtr;
typedef FieldContainerPtrMField<ShaderParameterMMatrixPtr,
                                UnrecordedRefCountPolicy> MFUnrecShaderParameterMMatrixPtr;
typedef FieldContainerPtrMField<ShaderParameterMMatrixPtr,
                                WeakRefCountPolicy      > MFWeakShaderParameterMMatrixPtr;
typedef FieldContainerPtrMField<ShaderParameterMMatrixPtr,
                                NoRefCountPolicy        > MFUncountedShaderParameterMMatrixPtr;
#endif


OSG_END_NAMESPACE

#endif /* _OSGSHADERPARAMETERMMATRIXFIELDS_H_ */
