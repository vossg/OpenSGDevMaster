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


#ifndef _OSGQTWINDOWDATAFIELDS_H_
#define _OSGQTWINDOWDATAFIELDS_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"

#include "OSGWindowQT4Def.h"

#include "OSGQ4GLWidget_qt.h"

#include "OSGWindowFields.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpWindowQt4FieldTraits
 */

typedef OSGQGLWidget *OSGQGLWidgetP;

/*! \ingroup GrpWindowQt4FieldTraits
 */

template <>
struct FieldTraits<OSGQGLWidgetP>
    : public FieldTraitsPtrToStringTemplateBase<OSGQGLWidgetP>
{
    static  DataType              _type;                       
    typedef FieldTraits<OSGQGLWidget *>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                                 Self::FromStringConvertible) };

	OSG_WINDOWQT4_DLLMAPPING
	static       DataType &getType (void){return _type;};

    static const Char8    *getSName(void) { return "SFOSGQGLWidgetP"; }
    static const Char8    *getMName(void) { return "MFOSGQGLWidgetP"; }

    static bool      getFromCString(      OSGQGLWidgetP      &widget,
                                    const Char8         *)
    {
        widget = NULL;

        return true;
    }

    static void      putToString  (const      OSGQGLWidgetP &,
        std::string   &outStr)
    {
        outStr.assign("OSGQGLWidgetP");
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowQt4FieldSFields */
typedef SField<OSGQGLWidgetP> SFOSGQGLWidgetP;

/*! \ingroup GrpWindowQt4FieldMFields */
typedef MField<OSGQGLWidgetP> MFOSGQGLWidgetP;
#else
/*! \ingroup GrpWindowQt4FieldSFields \ingroup GrpLibOSGWindowQt4 */
struct SFOSGQGLWidgetP : public SField<OSGQGLWidgetP> {};

/*! \ingroup GrpWindowQt4FieldMFields \ingroup GrpLibOSGWindowQt4 */
struct MFOSGQGLWidgetP : public MField<OSGQGLWidgetP> {};
#endif

OSG_END_NAMESPACE


#endif /* _OSGQTWINDOWDATAFIELDS_H_ */
