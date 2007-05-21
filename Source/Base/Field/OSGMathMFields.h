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

#ifndef _OSGMATHMFIELDS_H_
#define _OSGMATHMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGMathFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMathMFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
*/
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <Matrix         > MFMatrix;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Matrix, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <Matrix4d       > MFMatrix4d;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Matrix, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <Matrix4fx      > MFMatrix4fx;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Matrix4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <Quaternion         > MFQuaternion;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Quaternion, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField          <Quaternionfx       > MFQuaternionfx;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Quaternionfx, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef MFMatrix       MFMatrixr;
typedef MFQuaternion   MFQuaternionr;
#else
typedef MFMatrix4fx    MFMatrixr;
typedef MFQuaternionfx MFQuaternionr;
#endif

OSG_END_NAMESPACE

#define OSGMATHMFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGMATHMFIELDS_H_ */
