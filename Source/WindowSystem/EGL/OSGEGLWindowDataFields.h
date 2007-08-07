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


#ifndef _OSGEGLWINDOWDATAFIELDS_H_
#define _OSGEGLWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

// Forget everything if we're not doing a windows compile
#ifdef OSG_USE_EGL

#include "gles/egltypes.h"

#include "OSGWindowEGLDef.h"

#include "OSGWindowFields.h"
#include "OSGSysSFields.h"

//#include "windows.h"

/*! The field types for the local types needed by the EGLWINdow class */

OSG_BEGIN_NAMESPACE

/*
template <>
struct FieldTraits<EGLDisplay> : 
    public FieldTraitsPtrToStringTemplateBase<EGLDisplay>
{
    typedef FieldTraits<EGLDisplay>   Self;
    static  DataType           _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWEGL_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFEGLDisplay"; }
    static char     *getMName(void) { return "MFEGLDisplay"; }

    static bool      getFromCString(      EGLDisplay    &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      EGLDisplay &,
                                         std::string     &outStr)
    {
        outStr.assign("EGLDisplay");
    }
};
*/

template <>
struct FieldTraits<EGLSurface> : 
    public FieldTraitsPtrToStringTemplateBase<EGLSurface>
{
    static  DataType                _type;                       
    typedef FieldTraits<EGLSurface>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void);

    static char     *getSName(void) { return "SFEGLSurface"; }
    static char     *getMName(void) { return "MFEGLSurface"; }

    static bool      getFromCString(      EGLSurface    &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      EGLSurface &,
                                         std::string     &outStr)
    {
        outStr.assign("EGLSurface");
    }
};

template <>
struct FieldTraits<EGLContext> : 
    public FieldTraitsPtrToStringTemplateBase<EGLContext>
{
    static  DataType                _type;                       
    typedef FieldTraits<EGLContext>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void);

    static char     *getSName(void) { return "SFEGLContext"; }
    static char     *getMName(void) { return "MFEGLContext"; }

    static bool      getFromCString(      EGLContext    &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const       EGLContext &,
                                         std::string      &outStr)
    {
        outStr.assign("EGLContext");
    }
};

#if 0
template <>
struct FieldTraits<PAINTSTRUCT> : 
    public FieldTraitsPtrToStringTemplateBase<PAINTSTRUCT>
{
    static  DataType                 _type;                       
    typedef FieldTraits<PAINTSTRUCT>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void);

    static char     *getSName(void) { return "SFPAINTSTRUCT"; }
    static char     *getMName(void) { return "MFPAINTSTRUCT"; }

    static bool      getFromCString(      PAINTSTRUCT   &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      PAINTSTRUCT &,
                                         std::string      &outStr)
    {
        outStr.assign("PAINTSTRUCT");
    }
};
#endif

//! SFEGLDisplay
//! \ingroup GrpBaseFieldSingle

//typedef SField<HWND> SFHWND;
typedef SFInt32 SFEGLDisplay;

//! SFEGLSurface
//! \ingroup GrpBaseFieldSingle

typedef SField<EGLSurface> SFEGLSurface;

//! SFEGLContext
//! \ingroup GrpBaseFieldSingle

typedef SField<EGLContext> SFEGLContext;

// Instantiations

OSG_END_NAMESPACE

#endif /* OSG_USE_GLES */

#endif /* _OSGEGLWINDOWDATAFIELDS_H_ */
