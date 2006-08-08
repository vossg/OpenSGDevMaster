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

#ifndef _OSGSYSMFIELDS_H_
#define _OSGSYSMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGSysFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSysMFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
 */
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti
    \warning the getValue and operator[] functions may not return what
             you expect them to return. Descent STL implementation will 
             certainly not return 'bool &' nor 'const bool &'.
 */

typedef MField<bool, 2>   MFBool;
#endif

#if 0
#if ! defined(OSG_WIN32_CL)             || \
      defined(OSG_WITH_STLPORT)         || \
      defined(OSG_NEED_BOOL_MFIELD_SPEZ)
template <> inline
UInt32 MField<bool, 2>::getBinSize(void) const
{
    return sizeof(UInt32) + // num elements
           sizeof(UInt8) * _values.size();
}

template <> inline
void MField<bool, 2>::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);

    for(UInt32 i = 0; i < n; ++i)
    {
        UInt8 bval = _values[i];

        pMem.putValue(bval);
    }
}

template <> inline
void MField<bool, 2>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;
    
     pMem  .getValue(n);
    _values.clear ( );

#ifdef __hpux
    bool tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    UInt8 tmpBVal;

    for(UInt32 i = 0; i < n; ++i)
    {
        pMem.getValue(tmpBVal);

        _values[i] = (tmpBVal != 0);
    }
}
#endif
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL2(MField, bool, 2, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Int8>   MFInt8;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Int8, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<UInt8>  MFUInt8;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, UInt8, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Int16>  MFInt16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Int16, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<UInt16> MFUInt16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, UInt16, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Int32>  MFInt32;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Int32, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <UInt32         > MFUInt32;
#ifdef FDFOO
typedef FieldDescription<UInt32FieldDesc,
                         MultiField     > MUInt32FieldDescription;
#endif
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, UInt32, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Int64>  MFInt64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Int64, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<UInt64> MFUInt64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, UInt64, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Real16> MFReal16;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Real16, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Real32> MFReal32;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Real32, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Fixed32> MFFixed32;
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Real64> MFReal64;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, Real64, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<void *>   MFVoidP;
#endif

#ifndef OSG_COMPILEFIELDINST
//OSG_FIELD_DLLEXPORT_DECL1(MField, void *, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef MFReal32  MFReal;
#else
typedef MFFixed32 MFReal;
#endif

OSG_END_NAMESPACE

#define OSGSYSMFIELDS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSYSMFIELDS_H_ */
