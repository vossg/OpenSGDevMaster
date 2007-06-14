/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#define OSG_

#include <OSGField.h>

#include <OSGSField.h>
#include <OSGSField.ins>

#include <OSGMField.h>
#include <OSGMField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"

#endif

#include "OSGFieldBundleSFields.h"
#include "OSGFieldBundleMFields.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

DataType FieldTraits<FieldBundleP         >::_type("FieldBundleP", 
                                                   "TypeRoot");
DataType FieldTraits<ParentFieldBundleP, 1>::_type("ParentFieldBundleP",
                                                    "TypeRoot");

OSG_FIELDTRAITS_GETTYPE   (FieldBundleP         )
OSG_FIELDTRAITS_GETTYPE_NS(ParentFieldBundleP, 1)
#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//OSG_FIELD_DLLEXPORT_DEF1(SField,   Int8         )

OSG_FIELD_DLLEXPORT_DEF1(MField,   FieldBundleP         )
OSG_FIELD_DLLEXPORT_DEF2(MField,   ParentFieldBundleP, 1)

OSG_FIELD_DLLEXPORT_DEF1(SField,   FieldBundleP         )
OSG_FIELD_DLLEXPORT_DEF2(SField,   ParentFieldBundleP, 1)

template<>
void
FieldDescription<FieldTraits<FieldBundleP>,
                 MultiField                >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription<FieldTraits<FieldBundleP>, MultiField>::cloneValues NIY\n"));
}

template <>
void
FieldDescription<FieldTraits<FieldBundleP>,
                 MultiField                >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription<FieldTraits<FieldBundleP>, MultiField>::shareValues NIY\n"));
}

template<>
void
FieldDescription<FieldTraits<FieldBundleP>,
                 SingleField             >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription<FieldTraits<FieldBundleP>, SingleField>::cloneValues NIY\n"));
}

template <>
void
FieldDescription<FieldTraits<FieldBundleP>,
                 SingleField             >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const
{
    FWARNING(("FieldDescription<FieldTraits<FieldBundleP>, SingleField>::shareValues NIY\n"));
}

OSG_END_NAMESPACE
