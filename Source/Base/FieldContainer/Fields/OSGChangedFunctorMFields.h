/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGCHANGEDFUNCTORMFIELDS_H_
#define _OSGCHANGEDFUNCTORMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGChangedFunctorFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef MField<ChangedFunctorCallback> MFChangedFunctorCallback;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef MFChangedFunctorCallback : public MField<ChangedFunctorCallback> {};

#endif // these are the doxygen hacks

// there is no good way of comparing boost function objects
template<> inline
bool MField<ChangedFunctorCallback, 0>::operator ==(
    const MField<ChangedFunctorCallback, 0> & OSG_CHECK_ARG(source)) const
{
    return false;
}

#if 0
template <>
OSG_BASE_DLLMAPPING
void FieldDescription<FieldTraits<ChangedFunctorCallback>,
                      MultiField                          >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;

template <>
OSG_BASE_DLLMAPPING
void FieldDescription<FieldTraits<ChangedFunctorCallback>,
                      MultiField                          >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;
#endif

OSG_END_NAMESPACE

#endif /* _OSGCHANGEDFUNCTORCOREMFIELDS_H_ */
