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

#ifndef _OSGMATHSFIELDS_H_
#define _OSGMATHSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGMathFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMathSFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
*/
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <Matrix         > SFMatrix;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Matrix, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <Matrix4fx      > SFMatrix4fx;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Matrix4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <Quaternion         > SFQuaternion;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Quaternion, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <Quaternionfx       > SFQuaternionfx;

#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Quaternionfx, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef SFMatrix       SFMatrixr;
typedef SFQuaternion   SFQuaternionr;
#else
typedef SFMatrix4fx    SFMatrixr;
typedef SFQuaternionfx SFQuaternionr;
#endif

OSG_END_NAMESPACE

#define OSGMATHSFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGMATHSFIELDS_H_ */
