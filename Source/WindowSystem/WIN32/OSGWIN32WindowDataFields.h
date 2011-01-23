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
#if defined(WIN32) || defined(OSG_DO_DOC)

#include "OSGWindowWIN32Def.h"

#include "OSGWindowFields.h"


/*! The field types for the local types needed by the WIN32WINdow class */

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpWindowWIN32FieldTraits
 */

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

/*! \ingroup GrpWindowWIN32FieldTraits
 */

template <>
struct FieldTraits<HDC> : 
    public FieldTraitsPtrToStringTemplateBase<HDC>
{
    static  DataType             _type;                       
    typedef FieldTraits<HDC>      Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWWIN32_DLLMAPPING
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

/*! \ingroup GrpWindowWIN32FieldTraits
 */

template <>
struct FieldTraits<HGLRC> : 
    public FieldTraitsPtrToStringTemplateBase<HGLRC>
{
    static  DataType             _type;                       
    typedef FieldTraits<HGLRC>    Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWWIN32_DLLMAPPING
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

/*! \ingroup GrpWindowWIN32FieldTraits
 */

template <>
struct FieldTraits<PAINTSTRUCT> : 
    public FieldTraitsPtrToStringTemplateBase<PAINTSTRUCT>
{
    static  DataType                 _type;                       
    typedef FieldTraits<PAINTSTRUCT>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible)};

    OSG_WINDOWWIN32_DLLMAPPING
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

// there is no good way of comparing paintstruct objects
template<> inline
bool SField<PAINTSTRUCT, 0>::operator ==(
    const SField<PAINTSTRUCT, 0> &source) const
{
    return false;
}

template<> inline
bool MField<PAINTSTRUCT, 0>::operator ==(
    const MField<PAINTSTRUCT, 0> &source) const
{
    return false;
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowWIN32FieldSFields */
typedef SField<HWND> SFHWND;
/*! \ingroup GrpWindowWIN32FieldMFields */
typedef MField<HWND> MFHWND;

/*! \ingroup GrpWindowWIN32FieldSFields */
typedef SField<HDC> SFHDC;
/*! \ingroup GrpWindowWIN32FieldMFields */
typedef MField<HDC> MFHDC;

/*! \ingroup GrpWindowWIN32FieldSFields */
typedef SField<HGLRC> SFHGLRC;
/*! \ingroup GrpWindowWIN32FieldMFields */
typedef MField<HGLRC> MFHGLRC;

/*! \ingroup GrpWindowWIN32FieldSFields */
typedef SField<PAINTSTRUCT> SFPAINTSTRUCT;
/*! \ingroup GrpWindowWIN32FieldMFields */
typedef MField<PAINTSTRUCT> MFPAINTSTRUCT;
#else // doxygen hacks
/*! \ingroup GrpWindowWIN32FieldSFields \ingroup GrpLibOSGWindowWIN32 */
struct SFHWND : public SField<HWND> {};
/*! \ingroup GrpWindowWIN32FieldMFields \ingroup GrpLibOSGWindowWIN32 */
struct MFHWND : public MField<HWND> {};

/*! \ingroup GrpWindowWIN32FieldSFields \ingroup GrpLibOSGWindowWIN32 */
struct SFHDC : public SField<HDC> {};
/*! \ingroup GrpWindowWIN32FieldMFields \ingroup GrpLibOSGWindowWIN32 */
struct MFHDC : public MField<HDC> {};

/*! \ingroup GrpWindowWIN32FieldSFields \ingroup GrpLibOSGWindowWIN32 */
struct SFHGLRC : public SField<HGLRC> {};
/*! \ingroup GrpWindowWIN32FieldMFields \ingroup GrpLibOSGWindowWIN32 */
struct MFHGLRC : public MField<HGLRC> {};

/*! \ingroup GrpWindowWIN32FieldSFields \ingroup GrpLibOSGWindowWIN32 */
struct SFPAINTSTRUCT : public SField<PAINTSTRUCT> {};
/*! \ingroup GrpWindowWIN32FieldMFields \ingroup GrpLibOSGWindowWIN32 */
struct MFPAINTSTRUCT : public MField<PAINTSTRUCT> {};
#endif

OSG_END_NAMESPACE

#endif /* WIN32 */

#endif /* _OSGWIN32WINDOWDATAFIELDS_H_ */
