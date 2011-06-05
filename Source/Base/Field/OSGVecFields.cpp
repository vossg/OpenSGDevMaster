/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

#define OSG_COMPILEFIELDINST

#include "OSGField.h"

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

#include "OSGVecSFields.h"
#include "OSGVecMFields.h"

#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

OSG_FIELDTRAITS_GETTYPE   (Vec1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Vec1b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Vec1us         )
OSG_FIELDTRAITS_GETTYPE   (Vec1s          )
OSG_FIELDTRAITS_GETTYPE   (Vec1f          )
OSG_FIELDTRAITS_GETTYPE   (Vec1fx         )
OSG_FIELDTRAITS_GETTYPE   (Vec1d          )
OSG_FIELDTRAITS_GETTYPE   (Vec1ld         )

#ifndef OSG_DOXYGEN_REC_MACRO_PROBS
OSG_FIELDTRAITS_GETTYPE   (Vec2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Vec2b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Vec2us         )
OSG_FIELDTRAITS_GETTYPE   (Vec2s          )
OSG_FIELDTRAITS_GETTYPE   (Vec2f          )
OSG_FIELDTRAITS_GETTYPE   (Vec2fx         )
OSG_FIELDTRAITS_GETTYPE   (Vec2d          )
OSG_FIELDTRAITS_GETTYPE   (Vec2ld         )

OSG_FIELDTRAITS_GETTYPE   (Vec3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Vec3b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Vec3us         )
OSG_FIELDTRAITS_GETTYPE   (Vec3s          )
OSG_FIELDTRAITS_GETTYPE   (Vec3f          )
OSG_FIELDTRAITS_GETTYPE   (Vec3fx         )
OSG_FIELDTRAITS_GETTYPE   (Vec3d          )
OSG_FIELDTRAITS_GETTYPE   (Vec3ld         )

OSG_FIELDTRAITS_GETTYPE   (Vec4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Vec4b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Vec4us         )
OSG_FIELDTRAITS_GETTYPE   (Vec4s          )
OSG_FIELDTRAITS_GETTYPE   (Vec4f          )
OSG_FIELDTRAITS_GETTYPE   (Vec4fx         )
OSG_FIELDTRAITS_GETTYPE   (Vec4d          )
OSG_FIELDTRAITS_GETTYPE   (Vec4ld         )

OSG_FIELDTRAITS_GETTYPE   (Pnt1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Pnt1b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Pnt1us         )
OSG_FIELDTRAITS_GETTYPE   (Pnt1s          )
OSG_FIELDTRAITS_GETTYPE   (Pnt1f          )
OSG_FIELDTRAITS_GETTYPE   (Pnt1fx         )
OSG_FIELDTRAITS_GETTYPE   (Pnt1d          )
OSG_FIELDTRAITS_GETTYPE   (Pnt1ld         )

OSG_FIELDTRAITS_GETTYPE   (Pnt2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Pnt2b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Pnt2us         )
OSG_FIELDTRAITS_GETTYPE   (Pnt2s          )
OSG_FIELDTRAITS_GETTYPE   (Pnt2f          )
OSG_FIELDTRAITS_GETTYPE   (Pnt2fx         )
OSG_FIELDTRAITS_GETTYPE   (Pnt2d          )
OSG_FIELDTRAITS_GETTYPE   (Pnt2ld         )

OSG_FIELDTRAITS_GETTYPE   (Pnt3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Pnt3b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Pnt3us         )
OSG_FIELDTRAITS_GETTYPE   (Pnt3s          )
OSG_FIELDTRAITS_GETTYPE   (Pnt3f          )
OSG_FIELDTRAITS_GETTYPE   (Pnt3fx         )
OSG_FIELDTRAITS_GETTYPE   (Pnt3d          )
OSG_FIELDTRAITS_GETTYPE   (Pnt3ld         )

OSG_FIELDTRAITS_GETTYPE   (Pnt4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELDTRAITS_GETTYPE   (Pnt4b          )
#endif
OSG_FIELDTRAITS_GETTYPE   (Pnt4us         )
OSG_FIELDTRAITS_GETTYPE   (Pnt4s          )
OSG_FIELDTRAITS_GETTYPE   (Pnt4f          )
OSG_FIELDTRAITS_GETTYPE   (Pnt4fx         )
OSG_FIELDTRAITS_GETTYPE   (Pnt4d          )
OSG_FIELDTRAITS_GETTYPE   (Pnt4ld         )
#endif


OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec1ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec2ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec3ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Vec4ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt1ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt2ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt3ld         )

OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4us         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4s          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4f          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4fx         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4d          )
OSG_FIELD_DLLEXPORT_DEF1(SField, Pnt4ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec1ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec2ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec3ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Vec4ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt1ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt2ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt3ld         )

OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4ub         )
#ifndef OSG_NO_INT8_PNT
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4b          )
#endif
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4us         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4s          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4f          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4fx         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4d          )
OSG_FIELD_DLLEXPORT_DEF1(MField, Pnt4ld         )

OSG_END_NAMESPACE
