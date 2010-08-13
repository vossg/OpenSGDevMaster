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

#ifndef _OSGHARDWARECONTEXTDATASFIELDS_H_
#define _OSGHARDWARECONTEXTDATASFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"

#include "OSGHardwareContextDataFieldTraits.h"

#include "OSGMemObjPointerSField.h"

OSG_BEGIN_NAMESPACE


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseMemoryObjectsFieldSFields */
typedef MemObjPointerSField<HardwareContextData *,
                            MemObjRefCountPolicy > SFHardwareContextDataPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseMemoryObjectsFieldSFields \ingroup GrpLibOSGBase */
struct SFHardwareContextDataPtr : 
    public MemObjPointerSField<HardwareContextData *,
                               MemObjRefCountPolicy > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGHARDWARECONTEXTDATASFIELDS_H_ */
