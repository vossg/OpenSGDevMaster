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

#ifndef _OSGBASESFIELDS_H_
#define _OSGBASESFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGBaseFieldTraits.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color3f> SFColor3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color3f, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color3fx> SFColor3fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color3fx, OSG_BASE_DLLMAPPING);
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4f> SFColor4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color4f, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4fx> SFColor4fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color4fx, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color3ub> SFColor3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color3ub, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4ub> SFColor4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Color4ub, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<std::string> SFString;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, std::string, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Time, 1> SFTime;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL2(SField,Time, 1, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <DynamicVolume        > SFDynamicVolume;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, DynamicVolume, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<BitVector, 1>  SFBitVector;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL2(SField, BitVector, 1, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<GLenum, 1>  SFGLenum;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL2(SField, GLenum, 1, OSG_BASE_DLLMAPPING);
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Plane> SFPlane;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Plane, OSG_BASE_DLLMAPPING);
#endif

#ifdef OSG_FLOAT_PROFILE
typedef SFColor3f  SFColor3r;
typedef SFColor4f  SFColor4r;
#else
typedef SFColor3fx SFColor3r;
typedef SFColor4fx SFColor4r;
#endif

OSG_END_NAMESPACE

#endif /* _OSGBASESFIELDS_H_ */
