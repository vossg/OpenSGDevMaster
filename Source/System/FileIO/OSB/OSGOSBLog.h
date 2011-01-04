/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#ifndef _OSGOSBLOG_H_
#define _OSGOSBLOG_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGFileIODef.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

#define OSG_OSB_SILENT 1

#ifndef OSG_OSB_SILENT

#define OSG_OSB_LOG(OSG_MESSAGE)            \
    FDEBUG(OSG_MESSAGE)

#define OSG_OSB_PLOG(OSG_MESSAGE)           \
    FPDEBUG(OSG_MESSAGE)

#else

#define OSG_OSB_LOG(OSG_MESSAGE)

#define OSG_OSB_PLOG(OSG_MESSAGE)

#endif // OSG_OSG_SILENT

OSG_END_NAMESPACE

#endif // _OSGOSBLOG_H_
