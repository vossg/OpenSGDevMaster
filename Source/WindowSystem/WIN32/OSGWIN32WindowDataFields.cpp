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

#define OSG_COMPILEWIN32WINDOWINST

#include "OSGConfig.h"

#include "OSGWIN32WindowDataFields.h"

#include "OSGSField.ins"
#include "OSGMField.ins"

OSG_BEGIN_NAMESPACE

DataType FieldTraits<HWND       >::_type("HWND",        NULL);
DataType FieldTraits<HDC        >::_type("HDC",         NULL);
DataType FieldTraits<HGLRC      >::_type("HGLRC",       NULL);
DataType FieldTraits<PAINTSTRUCT>::_type("PAINTSTRUCT", NULL);

OSG_FIELDTRAITS_GETTYPE(HWND)
OSG_FIELDTRAITS_GETTYPE(HDC)
OSG_FIELDTRAITS_GETTYPE(HGLRC)
OSG_FIELDTRAITS_GETTYPE(PAINTSTRUCT)

OSG_FIELD_DLLEXPORT_DEF1(SField, HWND       );
OSG_FIELD_DLLEXPORT_DEF1(MField, HWND       );
OSG_FIELD_DLLEXPORT_DEF1(SField, HDC        );
OSG_FIELD_DLLEXPORT_DEF1(MField, HDC        );
OSG_FIELD_DLLEXPORT_DEF1(SField, HGLRC      );
OSG_FIELD_DLLEXPORT_DEF1(MField, HGLRC      );
OSG_FIELD_DLLEXPORT_DEF1(SField, PAINTSTRUCT);
OSG_FIELD_DLLEXPORT_DEF1(MField, PAINTSTRUCT);

OSG_END_NAMESPACE

