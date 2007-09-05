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



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color3fx> SFColor3fx;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4f> SFColor4f;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4fx> SFColor4fx;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color3ub> SFColor3ub;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Color4ub> SFColor4ub;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<std::string> SFString;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Time, 1> SFTime;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <DynamicVolume        > SFDynamicVolume;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField          <BoxVolume            > SFBoxVolume;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<BitVector, 1>  SFBitVector;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<GLenum, 1>  SFGLenum;
#endif



#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField<Plane> SFPlane;
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
