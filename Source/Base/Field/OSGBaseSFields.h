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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color3f> SFColor3f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color3fx> SFColor3fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color4f> SFColor4f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color4fx> SFColor4fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color3ub> SFColor3ub;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Color4ub> SFColor4ub;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<std::string> SFString;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Time, 1> SFTime;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<BoxVolume> SFBoxVolume;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<BitVector, 1>  SFBitVector;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<GLenum, 1>  SFGLenum;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Plane> SFPlane;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor3f : public SField<Color3f> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor3fx : public SField<Color3fx> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor4f : public SField<Color4f> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor4fx : public SField<Color4fx> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor3ub : public SField<Color3ub> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFColor4ub : public SField<Color4ub> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFString : public SField<std::string> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFTime : public SField<Time, 1> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFBoxVolume : public SField<BoxVolume> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFBitVector : public SField<BitVector, 1>  {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFGLenum : public SField<GLenum, 1> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFPlane : public SField<Plane> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGBASESFIELDS_H_ */
