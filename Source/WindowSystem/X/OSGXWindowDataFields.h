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

#ifndef _OSGXWINDOWDATAFIELDS_H_
#define _OSGXWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include <GL/glx.h>

#include "OSGWindowXDef.h"

#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"


OSG_BEGIN_NAMESPACE


typedef Display *DisplayP;
typedef ::Window X11Window;

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


/*! \ingroup GrpWindowXFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<DisplayP> : 
    public FieldTraitsPtrToStringTemplateBase<DisplayP>
{
    static  DataType              _type;                       
    typedef FieldTraits<DisplayP>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFDisplayP"; }
    static char     *getMName(void) { return "MFDisplayP"; }

    static bool      getFromCString(      DisplayP      &display,
                                    const Char8         *)
    {
        display = NULL;

        return true;
    }

    static void      putToString  (const      DisplayP &,
                                         std::string   &outStr)
    {
        outStr.assign("DisplayP");
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<DisplayP> */
/*! \hideinhierarchy                         */
#endif

/*! \ingroup GrpWindowXFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif
#if ( !defined(__GNUC__) || !defined(__linux) || ( !defined(__ia64) && !defined(__x86_64) ) ) && (!defined(_MIPS_SZPTR) || _MIPS_SZPTR != 64 )

template <>
struct OSG_WINDOWX_DLLMAPPING FieldTraits<X11Window> : 
    public FieldTraitsPtrToStringTemplateBase<X11Window>
{
    static  DataType               _type;                       
    typedef FieldTraits<X11Window>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFX11Window"; }
    static char     *getMName(void) { return "MFX11Window"; }

    static bool      getFromCString(      X11Window     &window,
                                    const Char8         *)
    {
        window = NULL;

        return true;
    }

    static void      putToString  (const      X11Window &,
                                         std::string    &outStr)
    {
        outStr.assign("X11Window");
    }
};
#endif

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<X11Window> */
/*! \hideinhierarchy                          */
#endif

template <>
struct OSG_WINDOWX_DLLMAPPING FieldTraits<GLXContext, 1> : 
    public FieldTraitsPtrToStringTemplateBase<GLXContext, 1>
{
    static  DataType                   _type;                       
    typedef FieldTraits<GLXContext, 1>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void) { return _type;        }

    static char     *getSName(void) { return "SFGLXContext"; }
    static char     *getMName(void) { return "MFGLXContext"; }

    static bool      getFromCString(      GLXContext    &context,
                                    const Char8         *)
    {
        context = NULL;

        return true;
    }

    static void      putToString  (const      GLXContext &,
                                         std::string     &outStr)
    {
        outStr.assign("GLXContext");
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<GLXContext> */
/*! \hideinhierarchy                           */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)

/*! \ingroup GrpWindowXFieldSingle
 */

typedef SField<DisplayP> SFDisplayP;

/*! \ingroup GrpWindowXFieldMulti
 */

typedef MField<DisplayP> MFDisplayP;

#if (!defined(__GNUC__) || !defined(__linux) || !defined(__ia64)) || (defined(_MIPS_SZPTR) && _MIPS_SZPTR != 64 )

/*! \ingroup GrpWindowXFieldSingle
 */

typedef SField<X11Window> SFX11Window;

/*! \ingroup GrpWindowXFieldMulti
 */

typedef MField<X11Window> MFX11Window;

#else

/*! \ingroup GrpWindowXFieldSingle
 */

typedef SField<UInt64> SFX11Window;

/*! \ingroup GrpWindowXFieldMulti
 */

typedef MField<UInt64> MFX11Window;

#endif

/*! \ingroup GrpWindowXFieldSingle
 */

typedef SField<GLXContext, 1> SFGLXContext;

/*! \ingroup GrpWindowXFieldMulti
 */

typedef MField<GLXContext, 1> MFGLXContext;

#endif

// Instantiations

#ifndef OSG_COMPILEWINDOWXINST
OSG_FIELD_DLLEXPORT_DECL1(SField, DisplayP,      OSG_WINDOWX_DLLTMPLMAPPING)
OSG_FIELD_DLLEXPORT_DECL1(SField, X11Window,     OSG_WINDOWX_DLLTMPLMAPPING)
OSG_FIELD_DLLEXPORT_DECL2(SField, GLXContext, 1, OSG_WINDOWX_DLLTMPLMAPPING)

OSG_FIELD_DLLEXPORT_DECL1(MField, DisplayP,      OSG_WINDOWX_DLLTMPLMAPPING)
OSG_FIELD_DLLEXPORT_DECL1(MField, X11Window,     OSG_WINDOWX_DLLTMPLMAPPING)
OSG_FIELD_DLLEXPORT_DECL2(MField, GLXContext, 1, OSG_WINDOWX_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSGWINDOWXFIELDS_HEADER_CVSID "@(#)$Id$"

#endif /* _OSGXWINDOWDATAFIELDS_H_ */

