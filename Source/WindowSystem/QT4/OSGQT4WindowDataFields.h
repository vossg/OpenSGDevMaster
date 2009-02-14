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

#include "OSGWindowFields.h"

#include "OSGQ4GLWidget_qt.h"

OSG_BEGIN_NAMESPACE

typedef OSGQGLWidget *OSGQGLWidgetP;

template <>
struct FieldTraits<OSGQGLWidgetP>
    : public FieldTraitsPtrToStringTemplateBase<OSGQGLWidgetP>
{
    static  DataType              _type;                       
    typedef FieldTraits<OSGQGLWidget *>  Self;

    enum                        { Convertible = (Self::ToStringConvertible  |
                                  Self::FromStringConvertible)};

	OSG_WINDOWQTLIB_DLLMAPPING
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

/*! \ingroup GrpWindowQTFieldSingle */

typedef SField<OSGQGLWidgetP> SFOSGQGLWidgetP;

/*! \ingroup GrpWindowQTFieldMulti */

typedef MField<OSGQGLWidgetP> MFOSGQGLWidgetP;

OSG_END_NAMESPACE


#endif /* _OSGQTWINDOWDATAFIELDS_H_ */
