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

#ifndef _OSGVECMFIELDS_H_
#define _OSGVECMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGVecFieldTraits.h"

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGVecMFields.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldMulti
 */
#endif

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1ub> MFVec1ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1b> MFVec1b;
#endif
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1b, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1us> MFVec1us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1s> MFVec1s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1f> MFVec1f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1fx> MFVec1fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1d> MFVec1d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec1ld> MFVec1ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec1ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2ub> MFVec2ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2b> MFVec2b;
#endif
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2b, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2us> MFVec2us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2s> MFVec2s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2f> MFVec2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2f, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2fx> MFVec2fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2d> MFVec2d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec2ld> MFVec2ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec2ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3ub> MFVec3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3b> MFVec3b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3us> MFVec3us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3s> MFVec3s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3f> MFVec3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3fx> MFVec3fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3d> MFVec3d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec3ld> MFVec3ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec3ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4ub> MFVec4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4b> MFVec4b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4us> MFVec4us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4s> MFVec4s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4f> MFVec4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4f, OSG_BASE_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4fx> MFVec4fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4d> MFVec4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Vec4ld> MFVec4ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Vec4ld, OSG_BASE_DLLTMPLMAPPING)
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1ub> MFPnt1ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1b> MFPnt1b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1us> MFPnt1us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1s> MFPnt1s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1f> MFPnt1f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1fx> MFPnt1fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1d> MFPnt1d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt1ld> MFPnt1ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt1ld, OSG_BASE_DLLTMPLMAPPING)
#endif





#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2ub> MFPnt2ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2b> MFPnt2b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2us> MFPnt2us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2s> MFPnt2s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2f> MFPnt2f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2fx> MFPnt2fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2d> MFPnt2d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt2ld> MFPnt2ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt2ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3ub> MFPnt3ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3b> MFPnt3b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3us> MFPnt3us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3s> MFPnt3s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3f> MFPnt3f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3fx> MFPnt3fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3d> MFPnt3d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt3ld> MFPnt3ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt3ld, OSG_BASE_DLLTMPLMAPPING)
#endif




#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4ub> MFPnt4ub;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4ub, OSG_BASE_DLLTMPLMAPPING)
#endif


#ifndef OSG_NO_INT8_PNT
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4b> MFPnt4b;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4b, OSG_BASE_DLLTMPLMAPPING)
#endif
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4us> MFPnt4us;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4us, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4s> MFPnt4s;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4s, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4f> MFPnt4f;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4f, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4fx> MFPnt4fx;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4fx, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4d> MFPnt4d;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4d, OSG_BASE_DLLTMPLMAPPING)
#endif


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldMulti */

typedef MField<Pnt4ld> MFPnt4ld;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_FIELD_DLLEXPORT_DECL1(MField, Pnt4ld, OSG_BASE_DLLTMPLMAPPING)
#endif

#ifdef OSG_FLOAT_PROFILE
typedef MFVec1f  MFVec1r;
typedef MFVec2f  MFVec2r;
typedef MFVec3f  MFVec3r;
typedef MFVec4f  MFVec4r;

typedef MFPnt1f  MFPnt1r;
typedef MFPnt2f  MFPnt2r;
typedef MFPnt3f  MFPnt3r;
typedef MFPnt4f  MFPnt4r;
#else
typedef MFVec1fx MFVec1r;
typedef MFVec2fx MFVec2r;
typedef MFVec3fx MFVec3r;
typedef MFVec4fx MFVec4r;

typedef MFPnt1fx MFPnt1r;
typedef MFPnt2fx MFPnt2r;
typedef MFPnt3fx MFPnt3r;
typedef MFPnt4fx MFPnt4r;
#endif

OSG_END_NAMESPACE

#define OSGVECMFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGVECMFIELDS_H_ */
