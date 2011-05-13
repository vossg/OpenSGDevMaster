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


#ifndef _OSGEAGLWINDOWDATAFIELDS_H_
#define _OSGEAGLWINDOWDATAFIELDS_H_
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

/*! \ingroup GrpWindowEAGLFieldTraits 
 */

typedef EAGLContext *EAGLContextP;

/*! The field types for the local types needed by the EAGLWindow class */

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpWindowEAGLFieldTraits 
 */

template <>
struct FieldTraits<EAGLContextP> : 
    public FieldTraitsPtrToStringTemplateBase<EAGLContextP>
{
    typedef FieldTraits<EAGLContextP>  Self;
    static  DataType                  _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWEAGL_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFEAGLContextP"; }
    static char     *getMName(void) { return "MFEAGLContextP"; }

    static bool      getFromCString(      EAGLContextP    &,
                                    const Char8           *)
    {
        return true;
    }

    static void      putToString  (const      EAGLContextP &,
                                         std::string       &outStr)
    {
        outStr.assign("EAGLContextP");
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowEAGLFieldSFields */
typedef SField<EAGLContextP> SFEAGLContextP;

/*! \ingroup GrpWindowEAGLFieldSFields */
typedef MField<EAGLContextP> MFEAGLContextP;
#else
/*! \ingroup GrpWindowEAGLFieldSFields \ingroup GrpLibOSGWindowEAGL */
struct SFEAGLContextP : public SField<EAGLContextP> {};

/*! \ingroup GrpWindowEAGLFieldSFields \ingroup GrpLibOSGWindowEAGL */
struct MFEAGLContextP : public MField<EAGLContextP> {};
#endif

OSG_END_NAMESPACE

#endif /* __APPLE__ */

#endif /* _OSGEAGLWINDOWDATAFIELDS_H_ */
