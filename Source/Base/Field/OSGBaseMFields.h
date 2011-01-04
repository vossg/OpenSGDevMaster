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

#ifndef _OSGBASEMFIELDS_H_
#define _OSGBASEMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGBaseFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color3f> MFColor3f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color3fx> MFColor3fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color4f> MFColor4f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color4fx> MFColor4fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color3ub> MFColor3ub;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Color4ub> MFColor4ub;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<std::string> MFString;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Time, 1> MFTime;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<BoxVolume> MFBoxVolume;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<BitVector, 1>  MFBitVector;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<GLenum, 1>  MFGLenum;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Plane> MFPlane;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor3f : public MField<Color3f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor3fx : public MField<Color3fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor4f : public MField<Color4f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor4fx : public MField<Color4fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor3ub : public MField<Color3ub> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFColor4ub : public MField<Color4ub> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFString : public MField<std::string> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFTime : public MField<Time, 1> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFBoxVolume : public MField<BoxVolume> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFBitVector : public MField<BitVector, 1> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFGLenum : public MField<GLenum, 1> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPlane : public MField<Plane> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGBASEMFIELDS_H_ */
