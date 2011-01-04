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

#ifndef _OSGSYSSFIELDS_H_
#define _OSGSYSSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGSysFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldSingle */
typedef SField<bool, 2>   SFBool;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Int8>   SFInt8;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<UInt8>  SFUInt8;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Int16>  SFInt16;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<UInt16> SFUInt16;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Int32>  SFInt32;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<UInt32> SFUInt32;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Int64>  SFInt64;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<UInt64> SFUInt64;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Real16> SFReal16;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Real32> SFReal32;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Fixed32> SFFixed32;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Real64> SFReal64;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<void *>   SFVoidP;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFBool    : public SField<bool, 2> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFInt8    : public SField<Int8> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFUInt8   : public SField<UInt8> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFInt16   : public SField<Int16> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFUInt16  : public SField<UInt16> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFInt32   : public SField<Int32> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFUInt32  : public SField<UInt32> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFInt64   : public SField<Int64> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFUInt64  : public SField<UInt64> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFReal16  : public SField<Real16> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFReal32  : public SField<Real32> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFFixed32 : public SField<Fixed32> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFReal64  : public SField<Real64> {};
/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFVoidP   : public SField<void *> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSYSSFIELDS_H_ */
