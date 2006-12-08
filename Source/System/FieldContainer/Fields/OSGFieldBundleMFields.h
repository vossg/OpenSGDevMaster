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

#ifndef _OSGFIELDBUNDLEMFIELDS_H_
#define _OSGFIELDBUNDLEMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGFieldBundleFieldTraits.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef MField<FieldBundleP> MFFieldBundleP;
#endif

#ifndef OSG_COMPILEBUNDLEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, FieldBundleP, OSG_SYSTEM_DLLTMPLMAPPING)
#endif

template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldBundleP>,
                 MultiField                 >::cloneValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &shareTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &shareGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;

template <>
OSG_SYSTEM_DLLMAPPING
void
FieldDescription<FieldTraits<FieldBundleP>,
                 MultiField                >::shareValues(
    const Field                                  *pSrc,
    const UInt32                                  fieldId,
          FieldContainerPtrConstArg               pDst,
    const std::vector<const FieldContainerType*> &cloneTypes,
    const std::vector<const FieldContainerType*> &ignoreTypes,
    const std::vector<UInt16>                    &cloneGroupIds,
    const std::vector<UInt16>                    &ignoreGroupIds) const;


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef MField<ParentFieldBundleP, 1> MFParentFieldBundleP;
#endif

#ifndef OSG_COMPILEBUNDLEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL2(MField, 
//                          ParentFieldBundleP, 
//                          1,
//                          OSG_SYSTEM_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGFIELDBUNDLEMFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGFIELDCBUNDLEMFIELDS_H_ */
