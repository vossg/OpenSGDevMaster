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

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldSingle */
typedef SField<Matrix      > SFMatrix;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Matrix4d    > SFMatrix4d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Matrix4fx   > SFMatrix4fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Quaternion  > SFQuaternion;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Quaternionfx> SFQuaternionfx;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFMatrix : public SField<Matrix> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFMatrix4d : public SField<Matrix4d> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFMatrix4fx : public SField<Matrix4fx> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFQuaternion : public SField<Quaternion> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFQuaternionfx : public SField<Quaternionfx> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGMATHSFIELDS_H_ */
