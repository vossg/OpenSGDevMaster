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

#ifndef _OSGSYSSFIELDS_H_
#define _OSGSYSSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGSysFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSysSFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
 */
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<bool, 2>   SFBool;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL2(SField, bool, 2, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Int8>   SFInt8;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Int8, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<UInt8>  SFUInt8;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, UInt8, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Int16>  SFInt16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Int16, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<UInt16> SFUInt16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, UInt16, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Int32>  SFInt32;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Int32, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <UInt32         > SFUInt32;
#ifdef FDFOO
typedef FieldDescription<UInt32FieldDesc,
                         SingleField    > SUInt32FieldDescription;
#endif

#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, UInt32, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Int64>  SFInt64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Int64, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<UInt64> SFUInt64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, UInt64, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Real16> SFReal16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Real16, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Real32> SFReal32;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Real32, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Fixed32> SFFixed32;
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Real64> SFReal64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, Real64, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<void *>   SFVoidP;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(SField, void *, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef SFReal32  SFReal;
#else
typedef SFFixed32 SFReal;
#endif


OSG_END_NAMESPACE

#endif /* _OSGSYSSFIELDS_H_ */
