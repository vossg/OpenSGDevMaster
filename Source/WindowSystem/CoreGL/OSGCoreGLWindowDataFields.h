/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGCOREGLWINDOWDATAFIELDS_H_
#define _OSGCOREGLWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS compile
#ifdef __APPLE__

#include "OSGWindowCoreGLDef.h"

#include "OSGWindowFields.h"

#include <OpenGL/OpenGL.h>

/*! The field types for the local types needed by the CoreGLWindow class */

OSG_BEGIN_NAMESPACE

template <>
struct FieldTraits<CGLContextObj> : 
    public FieldTraitsPtrToStringTemplateBase<CGLContextObj>
{
    typedef FieldTraits<CGLContextObj> Self;
    static  DataType                   _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWCOREGL_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFCGLContextObj"; }
    static char     *getMName(void) { return "MFCGLContextObj"; }

    static bool      getFromCString(      CGLContextObj &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      CGLContextObj &,
                                         std::string        &outStr)
    {
        outStr.assign("CGLContextObj");
    }
};

//! SFCGLContextObj
//! \ingroup GrpBaseFieldSingle

typedef SField<CGLContextObj> SFCGLContextObj;

//! MFCGLContextObj
//! \ingroup GrpBaseFieldMulti

typedef MField<CGLContextObj> MFCGLContextObj;

// Instantiations

#ifndef OSG_COMPILECOREGLWINDOWINST

OSG_FIELD_DLLEXPORT_DECL1(SField, CGLContextObj, OSG_WINDOWCOREGL_DLLTMPLMAPPING)

OSG_FIELD_DLLEXPORT_DECL1(MField, CGLContextObj, OSG_WINDOWCOREGL_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

#endif /* __APPLE__ */

#endif /* _OSGCOREGLWINDOWDATAFIELDS_H_ */
