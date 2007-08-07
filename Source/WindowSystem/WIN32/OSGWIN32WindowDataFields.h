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


#ifndef _OSGWIN32WINDOWDATAFIELDS_H_
#define _OSGWIN32WINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

// Forget everything if we're not doing a windows compile
#ifdef WIN32

#include "OSGWindowWIN32Def.h"

#include "OSGWindowFields.h"

//#include "windows.h"

/*! The field types for the local types needed by the WIN32WINdow class */

OSG_BEGIN_NAMESPACE

template <>
struct FieldTraits<HWND> : 
    public FieldTraitsPtrToStringTemplateBase<HWND>
{
    typedef FieldTraits<HWND>   Self;
    static  DataType           _type;                       

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWWIN32_DLLMAPPING
    static DataType &getType (void);

    static char     *getSName(void) { return "SFHWND"; }
    static char     *getMName(void) { return "MFHWND"; }

    static bool      getFromCString(      HWND          &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      HWND   &,
                                         std::string &outStr)
    {
        outStr.assign("HWND");
    }
};

template <>
struct FieldTraits<HDC> : 
    public FieldTraitsPtrToStringTemplateBase<HDC>
{
    static  DataType             _type;                       
    typedef FieldTraits<HDC>      Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void);

    static char     *getSName(void) { return "SFHDC"; }
    static char     *getMName(void) { return "MFHDC"; }

    static bool      getFromCString(      HDC           &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const      HDC    &,
                                         std::string &outStr)
    {
        outStr.assign("HDC");
    }
};

template <>
struct FieldTraits<HGLRC> : 
    public FieldTraitsPtrToStringTemplateBase<HGLRC>
{
    static  DataType             _type;                       
    typedef FieldTraits<HGLRC>    Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    static DataType &getType (void);

    static char     *getSName(void) { return "SFHGLRC"; }
    static char     *getMName(void) { return "MFHGLRC"; }

    static bool      getFromCString(      HGLRC         &,
                                    const Char8         *)
    {
        return true;
    }

    static void      putToString  (const       HGLRC &,
                                         std::string &outStr)
    {
        outStr.assign("HGLRC");
    }
};

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

//! SFHWND
//! \ingroup GrpBaseFieldSingle

typedef SField<HWND> SFHWND;

//! MFHWND
//! \ingroup GrpBaseFieldMulti

typedef MField<HWND> MFHWND;

//! SFHDC
//! \ingroup GrpBaseFieldSingle

typedef SField<HDC> SFHDC;

//! MFHDC
//! \ingroup GrpBaseFieldMulti

typedef MField<HDC> MFHDC;

//! SFHGLRC
//! \ingroup GrpBaseFieldSingle

typedef SField<HGLRC> SFHGLRC;

//! MFHGLRC
//! \ingroup GrpBaseFieldMulti

typedef MField<HGLRC> MFHGLRC;

//! SFPAINTSTRUCT
//! \ingroup GrpBaseFieldSingle

typedef SField<PAINTSTRUCT> SFPAINTSTRUCT;

//! MFPAINTSTRUCT
//! \ingroup GrpBaseFieldMulti

typedef MField<PAINTSTRUCT> MFPAINTSTRUCT;

OSG_END_NAMESPACE

#endif /* WIN32 */

#endif /* _OSGWIN32WINDOWDATAFIELDS_H_ */
