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
#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGWindowCoreGLDef.h"

#include "OSGWindowFields.h"

#include <OpenGL/OpenGL.h>

/*! The field types for the local types needed by the CoreGLWindow class */

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpWindowCoreGLFieldTraits
 */

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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowCoreGLFieldSFields */
typedef SField<CGLContextObj> SFCGLContextObj;

/*! \ingroup GrpWindowCoreGLFieldMFields */
typedef MField<CGLContextObj> MFCGLContextObj;
#else
/*! \ingroup GrpWindowCoreGLFieldSFields \ingroup GrpLibOSGWindowCoreGL */
struct SFCGLContextObj : public SField<CGLContextObj> {};

/*! \ingroup GrpWindowCoreGLFieldMFields \ingroup GrpLibOSGWindowCoreGL */
struct MFCGLContextObj : public MField<CGLContextObj> {};
#endif

OSG_END_NAMESPACE

#endif /* __APPLE__ */

#endif /* _OSGCOREGLWINDOWDATAFIELDS_H_ */
