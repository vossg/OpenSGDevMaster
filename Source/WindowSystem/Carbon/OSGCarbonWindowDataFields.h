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


#ifndef _OSGCARBONWINDOWDATAFIELDS_H_
#define _OSGCARBONWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

// Forget everything if we're not doing a Mac OS compile
#ifdef __APPLE__

#include "OSGWindowCarbonDef.h"

#include "OSGWindowFields.h"

#include <AGL/agl.h>

/*! The field types for the local types needed by the CarbonWindow class */

OSG_BEGIN_NAMESPACE

template <>
struct FieldTraits<AGLContext> : 
    public FieldTraitsPtrToStringTemplateBase<AGLContext>
{
    typedef FieldTraits<AGLContext>  Self;
    static  DataType                _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWCARBON_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFAGLContext"; }
    static char     *getMName(void) { return "MFAGLContext"; }

    static bool      getFromCString(      AGLContext    &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      AGLContext &,
                                         std::string     &outStr)
    {
        outStr.assign("AGLContext");
    }
};

//! SFAGLContext
//! \ingroup GrpBaseFieldSingle

typedef SField<AGLContext> SFAGLContext;

//! MFAGLContext
//! \ingroup GrpBaseFieldMulti

typedef MField<AGLContext> MFAGLContext;

OSG_END_NAMESPACE

#endif /* __APPLE__ */

#endif /* _OSGCARBONWINDOWDATAFIELDS_H_ */
