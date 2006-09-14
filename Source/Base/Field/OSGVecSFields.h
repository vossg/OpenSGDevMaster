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

#ifndef _OSGVECSFIELDS_H_
#define _OSGVECSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGVecFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGVecSFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
 */
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2ub> SFVec2ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2b> SFVec2b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2us> SFVec2us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2s> SFVec2s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2f> SFVec2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2f, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2fx> SFVec2fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2d> SFVec2d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec2ld> SFVec2ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec2ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3ub> SFVec3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3b> SFVec3b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3us> SFVec3us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3s> SFVec3s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3f> SFVec3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3fx> SFVec3fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3d> SFVec3d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec3ld> SFVec3ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec3ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4ub> SFVec4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4b> SFVec4b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4us> SFVec4us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4s> SFVec4s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4f> SFVec4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4fx> SFVec4fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4d> SFVec4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Vec4ld> SFVec4ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Vec4ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2ub> SFPnt2ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2b> SFPnt2b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2us> SFPnt2us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2s> SFPnt2s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2f> SFPnt2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2fx> SFPnt2fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2d> SFPnt2d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt2ld> SFPnt2ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt2ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3ub> SFPnt3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3b> SFPnt3b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3us> SFPnt3us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3s> SFPnt3s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3f> SFPnt3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3fx> SFPnt3fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3d> SFPnt3d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt3ld> SFPnt3ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt3ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4ub> SFPnt4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4b> SFPnt4b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4us> SFPnt4us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4s> SFPnt4s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4f> SFPnt4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4fx> SFPnt4fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4d> SFPnt4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Pnt4ld> SFPnt4ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(SField, Pnt4ld, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef SFVec2f  SFVec2r;
typedef SFVec3f  SFVec3r;
typedef SFVec4f  SFVec4r;

typedef SFPnt2f  SFPnt2r;
typedef SFPnt3f  SFPnt3r;
typedef SFPnt4f  SFPnt4r;
#else
typedef SFVec2fx SFVec2r;
typedef SFVec3fx SFVec3r;
typedef SFVec4fx SFVec4r;

typedef SFPnt2fx SFPnt2r;
typedef SFPnt3fx SFPnt3r;
typedef SFPnt4fx SFPnt4r;
#endif


OSG_END_NAMESPACE

#define OSGVECSFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGVECSFIELDS_H_ */
