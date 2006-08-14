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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEEGLWINDOWINST

#include "OSGConfig.h"

#include "OSGEGLWindowDataFields.h"

#include <OSGSField.ins>
#include <OSGMField.ins>

#if defined(OSG_TMPL_STATIC_MEMBER_NEEDS_FUNCTION_INSTANTIATION) || \
    defined(OSG_TMPL_STATIC_MEMBER_NEEDS_CLASS_INSTANTIATION   )

#include "OSGSFieldFuncs.ins"
#include "OSGMFieldFuncs.ins"
#endif

OSG_BEGIN_NAMESPACE

// doxygen can't find these
#ifndef OSG_DO_DOC 

//DataType FieldTraits<EGLDisplay>::_type("EGLDisplay", NULL);
DataType FieldTraits<EGLSurface>::_type("EGLSurface", NULL);
DataType FieldTraits<EGLContext>::_type("EGLContext", NULL);


#endif

//OSG_FIELDTRAITS_GETTYPE(EGLDisplay)
OSG_FIELDTRAITS_GETTYPE(EGLSurface)
OSG_FIELDTRAITS_GETTYPE(EGLContext)


//OSG_FIELD_DLLEXPORT_DEF1(SField, EGLDisplay);
OSG_FIELD_DLLEXPORT_DEF1(SField, EGLSurface);
OSG_FIELD_DLLEXPORT_DEF1(SField, EGLContext);

OSG_END_NAMESPACE

