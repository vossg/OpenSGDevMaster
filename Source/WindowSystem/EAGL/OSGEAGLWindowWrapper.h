/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#ifndef _OSGEAGLWINDOWWRAPPER_H_
#define _OSGEAGLWINDOWWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS compile
#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGWindowEAGLDef.h"

#include "OSGWindowFields.h"

#ifndef __OBJC__
struct EAGLContext;
#else
@class EAGLContext;
#endif

/* \ingroup GrpWindowEAGLObj
 */

typedef EAGLContext *EAGLContextP;

EAGLContextP eaglWrapperCurrentContext(void);

#endif /* __APPLE__ */

#endif /* _OSGEAGLWINDOWWRAPPER_H_ */


