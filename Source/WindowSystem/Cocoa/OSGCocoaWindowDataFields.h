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


#ifndef _OSGCOCOAWINDOWDATAFIELDS_H_
#define _OSGCOCOAWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS compile
#if defined(__APPLE__) || defined(OSG_DO_DOC)

#include "OSGWindowCocoaDef.h"

#include "OSGWindowFields.h"

#ifndef __OBJC__
struct NSOpenGLContext;
#else
@class NSOpenGLContext;
#endif

/*! \ingroup GrpWindowCocoaFieldTraits 
 */

typedef NSOpenGLContext *NSOpenGLContextP;

/*! The field types for the local types needed by the CocoaWindow class */

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpWindowCocoaFieldTraits 
 */

template <>
struct FieldTraits<NSOpenGLContextP> : 
    public FieldTraitsPtrToStringTemplateBase<NSOpenGLContextP>
{
    typedef FieldTraits<NSOpenGLContextP>  Self;
    static  DataType                       _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWCOCOA_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFNSOpenGLContextP"; }
    static char     *getMName(void) { return "MFNSOpenGLContextP"; }

    static bool      getFromCString(      NSOpenGLContextP    &,
                                    const Char8               *)
    {
        return true;
    }

    static void      putToString  (const      NSOpenGLContextP &,
                                         std::string           &outStr)
    {
        outStr.assign("NSOpenGLContextP");
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowCocoaFieldSFields */
typedef SField<NSOpenGLContextP> SFNSOpenGLContextP;

/*! \ingroup GrpWindowCocoaFieldSFields */
typedef MField<NSOpenGLContextP> MFNSOpenGLContextP;
#else
/*! \ingroup GrpWindowCocoaFieldSFields \ingroup GrpLibOSGWindowCocoa */
struct SFNSOpenGLContextP : public SField<NSOpenGLContextP> {};

/*! \ingroup GrpWindowCocoaFieldSFields \ingroup GrpLibOSGWindowCocoa */
struct MFNSOpenGLContextP : public MField<NSOpenGLContextP> {};
#endif

OSG_END_NAMESPACE

#endif /* __APPLE__ */

#endif /* _OSGCOCOAWINDOWDATAFIELDS_H_ */
