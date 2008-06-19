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

#ifndef _OSGFIELDCONTAINERMFIELDS_H_
#define _OSGFIELDCONTAINERMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"

#include "OSGFieldContainerFieldTraits.h"

#include "OSGPointerMField.h"
#include "OSGParentPointerMField.h"
#include "OSGChildPointerMField.h"

#include "OSGFieldContainerMFieldHandle.h"  

#include "OSGRefCountPolicies.h"

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup  */

typedef PointerMField<FieldContainer *,
                      RecordedRefCountPolicy  > MFRecFieldContainerPtr;

typedef PointerMField<FieldContainer *,
                      UnrecordedRefCountPolicy> MFUnrecFieldContainerPtr;

typedef PointerMField<FieldContainer *,
                      WeakRefCountPolicy      > MFWeakFieldContainerPtr;

typedef PointerMField<FieldContainer *,
                      NoRefCountPolicy        > MFUncountedFieldContainerPtr;
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup  */

typedef 
    ParentPointerMField<FieldContainer *, 
                        NoRefCountPolicy,
                        1                > MFParentFieldContainerPtr;
#endif



OSG_END_NAMESPACE

//#include "OSGFieldContainerParentMFieldHandle.h"

#ifndef OSG_COMPILECONTAINERFIELDINST
#include "OSGFieldContainerMFields.inl"
#endif

#endif /* _OSGFIELDCONTAINERMFIELDS_H_ */
