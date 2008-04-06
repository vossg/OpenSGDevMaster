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


#ifndef _OSGSHADERPARAMETERFIELDS_H_
#define _OSGSHADERPARAMETERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGFieldContainerPtrSField.h"
#include "OSGFieldContainerPtrMField.h"


OSG_BEGIN_NAMESPACE

class ShaderParameter;

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! ShaderParameterPtr

OSG_GEN_CONTAINERPTR(ShaderParameter);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpStateFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<ShaderParameterPtr> :
    public FieldTraitsFCPtrBase<ShaderParameterPtr>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderParameterPtr>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFShaderParameterPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFShaderParameterPtr"; }
};

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderParameterPtr"; 
}

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsTemplateBase<ShaderParameterPtr, 0>
    \hideinhierarchy
 */
#endif


template <>
struct FieldTraits<ShaderParameterPtr, 1> :
    public FieldTraitsFCPtrBase<ShaderParameterPtr, 1>
{
  private:

  public:

    typedef FieldTraits<ShaderParameterPtr, 1>  Self;
    typedef FieldContainerPtr           ParentType;

    static const FieldCardinality eFieldCard = MultiField;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFShaderParameterPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFShaderParameterPtr"; }
};

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFieldContainerChildShaderParameterPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderParameterPtr, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFieldContainerChildShaderParameterPtr"; 
}


#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldSingle */

typedef FieldContainerPtrSField<ShaderParameterPtr,
                                RecordedRefCountPolicy  > SFRecShaderParameterPtr;
typedef FieldContainerPtrSField<ShaderParameterPtr,
                                UnrecordedRefCountPolicy> SFUnrecShaderParameterPtr;
typedef FieldContainerPtrSField<ShaderParameterPtr,
                                WeakRefCountPolicy      > SFWeakShaderParameterPtr;
typedef FieldContainerPtrSField<ShaderParameterPtr,
                                NoRefCountPolicy        > SFUncountedShaderParameterPtr;
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpStateFieldMulti */

typedef FieldContainerPtrMField<ShaderParameterPtr,
                                RecordedRefCountPolicy  > MFRecShaderParameterPtr;
typedef FieldContainerPtrMField<ShaderParameterPtr,
                                UnrecordedRefCountPolicy> MFUnrecShaderParameterPtr;
typedef FieldContainerPtrMField<ShaderParameterPtr,
                                WeakRefCountPolicy      > MFWeakShaderParameterPtr;
typedef FieldContainerPtrMField<ShaderParameterPtr,
                                NoRefCountPolicy        > MFUncountedShaderParameterPtr;
#endif



typedef FieldContainerPtrChildMField<
          ShaderParameterPtr, 
          UnrecordedRefCountPolicy,
          1                  > MFUnrecFieldContainerChildShaderParameterPtr;

typedef MFUnrecFieldContainerChildShaderParameterPtr
    MFUnrecChildShaderParameterPtr;

OSG_END_NAMESPACE

#endif /* _OSGSHADERPARAMETERFIELDS_H_ */
