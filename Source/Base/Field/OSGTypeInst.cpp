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

#include "OSGBaseSFields.h"
#include "OSGBaseMFields.h"

#include "OSGSysSFields.h"
#include "OSGSysMFields.h"

#include "OSGMathSFields.h"
#include "OSGMathMFields.h"

#include "OSGVecSFields.h"
#include "OSGVecMFields.h"

#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

namespace
{
    // Type objects for "abstract" types in the type hierarchy.
    // These types do not correspond with any real types, but are used to
    // group the concrete types.
    DataType typeObjTypeRoot    ("TypeRoot",     NULL      );
    DataType typeObjBaseType    ("BaseType",     "TypeRoot");
    DataType typeObjIntegralType("IntegralType", "TypeRoot");
    DataType typeObjField       ("Field",        "TypeRoot");
}


DataType FieldTraits<bool,      2 >::_type("bool"  ,       "IntegralType");
DataType FieldTraits< Int8        >::_type("Int8"  ,       "IntegralType");
DataType FieldTraits<UInt8        >::_type("UInt8" ,       "IntegralType");
DataType FieldTraits< Int16       >::_type("Int16" ,       "IntegralType");
DataType FieldTraits<UInt16       >::_type("UInt16",       "IntegralType");
DataType FieldTraits< Int32       >::_type("Int32" ,       "IntegralType");
DataType FieldTraits<UInt32       >::_type("UInt32",       "IntegralType");
DataType FieldTraits< Int64       >::_type("Int64" ,       "IntegralType");
DataType FieldTraits<UInt64       >::_type("UInt64",       "IntegralType");
DataType FieldTraits<Real16       >::_type("Real16",       "IntegralType");
DataType FieldTraits<Real32       >::_type("Real32",       "IntegralType");
DataType FieldTraits<Fixed32      >::_type("Fixed32",      "IntegralType");
DataType FieldTraits<Real64       >::_type("Real64",       "IntegralType");
DataType FieldTraits<void *       >::_type("VoidP" ,       "IntegralType");

DataType FieldTraits<Color3f      >::_type("Color3f",      "BaseType"    );
DataType FieldTraits<Color3fx     >::_type("Color3fx",     "BaseType"    );
DataType FieldTraits<Color4f      >::_type("Color4f",      "BaseType"    );
DataType FieldTraits<Color4fx     >::_type("Color4fx",     "BaseType"    );
DataType FieldTraits<Color3ub     >::_type("Color3ub",     "BaseType"    );
DataType FieldTraits<Color4ub     >::_type("Color4ub",     "BaseType"    );
DataType FieldTraits<std::string  >::_type("string",       "BaseType"    );
DataType FieldTraits<Time,      1 >::_type("Time",         "BaseType"    );
DataType FieldTraits<BoxVolume    >::_type("BoxVolume",    "BaseType"    );
DataType FieldTraits<BitVector, 1 >::_type("BitVector",    "BaseType"    );
DataType FieldTraits<GLenum,    1 >::_type("GLenum",       "BaseType"    );
DataType FieldTraits<Plane        >::_type("Plane",        "BaseType"    );

DataType FieldTraits<Vec1ub       >::_type("Vec1ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Vec1b        >::_type("Vec1b" ,       "BaseType"    );
#endif
DataType FieldTraits<Vec1us       >::_type("Vec1us",       "BaseType"    );
DataType FieldTraits<Vec1s        >::_type("Vec1s" ,       "BaseType"    );
DataType FieldTraits<Vec1f        >::_type("Vec1f" ,       "BaseType"    );
DataType FieldTraits<Vec1fx       >::_type("Vec1fx",       "BaseType"    );
DataType FieldTraits<Vec1d        >::_type("Vec1d" ,       "BaseType"    );
DataType FieldTraits<Vec1ld       >::_type("Vec1ld",       "BaseType"    );

#ifndef OSG_DOXYGEN_REC_MACRO_PROBS
DataType FieldTraits<Vec2ub       >::_type("Vec2ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Vec2b        >::_type("Vec2b" ,       "BaseType"    );
#endif
DataType FieldTraits<Vec2us       >::_type("Vec2us",       "BaseType"    );
DataType FieldTraits<Vec2s        >::_type("Vec2s" ,       "BaseType"    );
DataType FieldTraits<Vec2f        >::_type("Vec2f" ,       "BaseType"    );
DataType FieldTraits<Vec2fx       >::_type("Vec2fx",       "BaseType"    );
DataType FieldTraits<Vec2d        >::_type("Vec2d" ,       "BaseType"    );
DataType FieldTraits<Vec2ld       >::_type("Vec2ld",       "BaseType"    );

DataType FieldTraits<Vec3ub       >::_type("Vec3ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Vec3b        >::_type("Vec3b" ,       "BaseType"    );
#endif
DataType FieldTraits<Vec3us       >::_type("Vec3us",       "BaseType"    );
DataType FieldTraits<Vec3s        >::_type("Vec3s" ,       "BaseType"    );
DataType FieldTraits<Vec3f        >::_type("Vec3f" ,       "BaseType"    );
DataType FieldTraits<Vec3fx       >::_type("Vec3fx",       "BaseType"    );
DataType FieldTraits<Vec3d        >::_type("Vec3d" ,       "BaseType"    );
DataType FieldTraits<Vec3ld       >::_type("Vec3ld",       "BaseType"    );

DataType FieldTraits<Vec4ub       >::_type("Vec4ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Vec4b        >::_type("Vec4b" ,       "BaseType"    );
#endif
DataType FieldTraits<Vec4us       >::_type("Vec4us",       "BaseType"    );
DataType FieldTraits<Vec4s        >::_type("Vec4s" ,       "BaseType"    );
DataType FieldTraits<Vec4f        >::_type("Vec4f" ,       "BaseType"    );
DataType FieldTraits<Vec4fx       >::_type("Vec4fx",       "BaseType"    );
DataType FieldTraits<Vec4d        >::_type("Vec4d" ,       "BaseType"    );
DataType FieldTraits<Vec4ld       >::_type("Vec4ld",       "BaseType"    );

DataType FieldTraits<Pnt1ub       >::_type("Pnt1ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Pnt1b        >::_type("Pnt1b" ,       "BaseType"    );
#endif
DataType FieldTraits<Pnt1us       >::_type("Pnt1us",       "BaseType"    );
DataType FieldTraits<Pnt1s        >::_type("Pnt1s" ,       "BaseType"    );
DataType FieldTraits<Pnt1f        >::_type("Pnt1f" ,       "BaseType"    );
DataType FieldTraits<Pnt1fx       >::_type("Pnt1fx",       "BaseType"    );
DataType FieldTraits<Pnt1d        >::_type("Pnt1d" ,       "BaseType"    );
DataType FieldTraits<Pnt1ld       >::_type("Pnt1ld",       "BaseType"    );

DataType FieldTraits<Pnt2ub       >::_type("Pnt2ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Pnt2b        >::_type("Pnt2b" ,       "BaseType"    );
#endif
DataType FieldTraits<Pnt2us       >::_type("Pnt2us",       "BaseType"    );
DataType FieldTraits<Pnt2s        >::_type("Pnt2s" ,       "BaseType"    );
DataType FieldTraits<Pnt2f        >::_type("Pnt2f" ,       "BaseType"    );
DataType FieldTraits<Pnt2fx       >::_type("Pnt2fx",       "BaseType"    );
DataType FieldTraits<Pnt2d        >::_type("Pnt2d" ,       "BaseType"    );
DataType FieldTraits<Pnt2ld       >::_type("Pnt2ld",       "BaseType"    );

DataType FieldTraits<Pnt3ub       >::_type("Pnt3ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Pnt3b        >::_type("Pnt3b" ,       "BaseType"    );
#endif
DataType FieldTraits<Pnt3us       >::_type("Pnt3us",       "BaseType"    );
DataType FieldTraits<Pnt3s        >::_type("Pnt3s" ,       "BaseType"    );
DataType FieldTraits<Pnt3f        >::_type("Pnt3f" ,       "BaseType"    );
DataType FieldTraits<Pnt3fx       >::_type("Pnt3fx",       "BaseType"    );
DataType FieldTraits<Pnt3d        >::_type("Pnt3d" ,       "BaseType"    );
DataType FieldTraits<Pnt3ld       >::_type("Pnt3ld",       "BaseType"    );

DataType FieldTraits<Pnt4ub       >::_type("Pnt4ub",       "BaseType"    );
#ifndef OSG_NO_INT8_PNT
DataType FieldTraits<Pnt4b        >::_type("Pnt4b" ,       "BaseType"    );
#endif
DataType FieldTraits<Pnt4us       >::_type("Pnt4us",       "BaseType"    );
DataType FieldTraits<Pnt4s        >::_type("Pnt4s" ,       "BaseType"    );
DataType FieldTraits<Pnt4f        >::_type("Pnt4f" ,       "BaseType"    );
DataType FieldTraits<Pnt4fx       >::_type("Pnt4fx" ,      "BaseType"    );
DataType FieldTraits<Pnt4d        >::_type("Pnt4d" ,       "BaseType"    );
DataType FieldTraits<Pnt4ld       >::_type("Pnt4ld",       "BaseType"    );
#endif

DataType FieldTraits<Matrix       >::_type("Matrix"    ,   "BaseType"    );
DataType FieldTraits<Matrix4d     >::_type("Matrix4d"  ,   "BaseType"    );
DataType FieldTraits<Matrix4fx    >::_type("Matrix4fx" ,   "BaseType"    );
DataType FieldTraits<Quaternion   >::_type("Quaternion",   "BaseType"    );
DataType FieldTraits<Quaternionfx >::_type("Quaternionfx", "BaseType"    );

OSG_FIELDTRAITS_GETTYPE_NS(bool,         2)
OSG_FIELDTRAITS_GETTYPE   ( Int8          )
OSG_FIELDTRAITS_GETTYPE   (UInt8          )
OSG_FIELDTRAITS_GETTYPE   ( Int16         )
OSG_FIELDTRAITS_GETTYPE   (UInt16         )
OSG_FIELDTRAITS_GETTYPE   ( Int32         )
OSG_FIELDTRAITS_GETTYPE   (UInt32         )
OSG_FIELDTRAITS_GETTYPE   ( Int64         )
OSG_FIELDTRAITS_GETTYPE   (UInt64         )
OSG_FIELDTRAITS_GETTYPE   (Real16         )
OSG_FIELDTRAITS_GETTYPE   (Real32         )
OSG_FIELDTRAITS_GETTYPE   (Fixed32        )
OSG_FIELDTRAITS_GETTYPE   (Real64         )
OSG_FIELDTRAITS_GETTYPE   (void *         )

OSG_FIELDTRAITS_GETTYPE   (Color3f        )
OSG_FIELDTRAITS_GETTYPE   (Color3fx       )
OSG_FIELDTRAITS_GETTYPE   (Color4f        )
OSG_FIELDTRAITS_GETTYPE   (Color4fx       )
OSG_FIELDTRAITS_GETTYPE   (Color3ub       )
OSG_FIELDTRAITS_GETTYPE   (Color4ub       )
OSG_FIELDTRAITS_GETTYPE   (std::string    )
OSG_FIELDTRAITS_GETTYPE_NS(Time,         1)
OSG_FIELDTRAITS_GETTYPE   (BoxVolume      )
OSG_FIELDTRAITS_GETTYPE_NS(BitVector,    1)
OSG_FIELDTRAITS_GETTYPE_NS(GLenum,       1)
OSG_FIELDTRAITS_GETTYPE   (Plane          )

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

OSG_FIELDTRAITS_GETTYPE   (Matrix         )
OSG_FIELDTRAITS_GETTYPE   (Matrix4d       )
OSG_FIELDTRAITS_GETTYPE   (Matrix4fx      )
OSG_FIELDTRAITS_GETTYPE   (Quaternion     )
OSG_FIELDTRAITS_GETTYPE   (Quaternionfx   )

OSG_FIELD_DLLEXPORT_DEF2(SField,   bool,       2)
OSG_FIELD_DLLEXPORT_DEF1(SField,   Int8         )
OSG_FIELD_DLLEXPORT_DEF1(SField,  UInt8         )
OSG_FIELD_DLLEXPORT_DEF1(SField,  Int16         )
OSG_FIELD_DLLEXPORT_DEF1(SField, UInt16         )
OSG_FIELD_DLLEXPORT_DEF1(SField,  Int32         )
OSG_FIELD_DLLEXPORT_DEF1(SField, UInt32         )
OSG_FIELD_DLLEXPORT_DEF1(SField,  Int64         )
OSG_FIELD_DLLEXPORT_DEF1(SField, UInt64         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Real16         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Real32         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Fixed32        )
OSG_FIELD_DLLEXPORT_DEF1(SField, Real64         )
OSG_FIELD_DLLEXPORT_DEF1(SField, void *         )

OSG_FIELD_DLLEXPORT_DEF2(MField,   bool,       2)
OSG_FIELD_DLLEXPORT_DEF1(MField,   Int8         )
OSG_FIELD_DLLEXPORT_DEF1(MField,  UInt8         )
OSG_FIELD_DLLEXPORT_DEF1(MField,  Int16         )
OSG_FIELD_DLLEXPORT_DEF1(MField, UInt16         )
OSG_FIELD_DLLEXPORT_DEF1(MField,  Int32         )
OSG_FIELD_DLLEXPORT_DEF1(MField, UInt32         )
OSG_FIELD_DLLEXPORT_DEF1(MField,  Int64         )
OSG_FIELD_DLLEXPORT_DEF1(MField, UInt64         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Real16         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Real32         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Fixed32        )
OSG_FIELD_DLLEXPORT_DEF1(MField, Real64         )
OSG_FIELD_DLLEXPORT_DEF1(MField, void *         )


OSG_FIELD_DLLEXPORT_DEF1(SField, Color3f        )
OSG_FIELD_DLLEXPORT_DEF1(SField, Color3fx       )
OSG_FIELD_DLLEXPORT_DEF1(SField, Color4f        )
OSG_FIELD_DLLEXPORT_DEF1(SField, Color4fx       )
OSG_FIELD_DLLEXPORT_DEF1(SField, Color3ub       )
OSG_FIELD_DLLEXPORT_DEF1(SField, Color4ub       )
OSG_FIELD_DLLEXPORT_DEF1(SField, std::string    )
OSG_FIELD_DLLEXPORT_DEF2(SField, Time,         1)
OSG_FIELD_DLLEXPORT_DEF1(SField, BoxVolume      )
OSG_FIELD_DLLEXPORT_DEF2(SField, BitVector,    1)
OSG_FIELD_DLLEXPORT_DEF2(SField, GLenum,       1)
OSG_FIELD_DLLEXPORT_DEF1(SField, Plane          )

OSG_FIELD_DLLEXPORT_DEF1(MField, Color3f        )
OSG_FIELD_DLLEXPORT_DEF1(MField, Color3fx       )
OSG_FIELD_DLLEXPORT_DEF1(MField, Color4f        )
OSG_FIELD_DLLEXPORT_DEF1(MField, Color4fx       )
OSG_FIELD_DLLEXPORT_DEF1(MField, Color3ub       )
OSG_FIELD_DLLEXPORT_DEF1(MField, Color4ub       )
OSG_FIELD_DLLEXPORT_DEF1(MField, std::string    )
OSG_FIELD_DLLEXPORT_DEF2(MField, Time,         1)
OSG_FIELD_DLLEXPORT_DEF1(MField, BoxVolume      )
OSG_FIELD_DLLEXPORT_DEF2(MField, BitVector,    1)
OSG_FIELD_DLLEXPORT_DEF2(MField, GLenum,       1)
OSG_FIELD_DLLEXPORT_DEF1(MField, Plane          )

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

OSG_FIELD_DLLEXPORT_DEF1(SField, Matrix         )
OSG_FIELD_DLLEXPORT_DEF1(SField, Matrix4d       )
OSG_FIELD_DLLEXPORT_DEF1(SField, Matrix4fx      )
OSG_FIELD_DLLEXPORT_DEF1(SField, Quaternion     )
OSG_FIELD_DLLEXPORT_DEF1(SField, Quaternionfx   )

OSG_FIELD_DLLEXPORT_DEF1(MField, Matrix         )
OSG_FIELD_DLLEXPORT_DEF1(MField, Matrix4d       )
OSG_FIELD_DLLEXPORT_DEF1(MField, Matrix4fx      )
OSG_FIELD_DLLEXPORT_DEF1(MField, Quaternion     )
OSG_FIELD_DLLEXPORT_DEF1(MField, Quaternionfx   )

OSG_END_NAMESPACE
