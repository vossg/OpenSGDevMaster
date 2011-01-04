/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGVECMFIELDS_H_
#define _OSGVECMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMField.h"
#include "OSGVecFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1ub> MFVec1ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1b> MFVec1b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1us> MFVec1us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1s> MFVec1s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1f> MFVec1f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1fx> MFVec1fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1d> MFVec1d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec1ld> MFVec1ld;




/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2ub> MFVec2ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2b> MFVec2b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2us> MFVec2us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2s> MFVec2s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2f> MFVec2f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2fx> MFVec2fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2d> MFVec2d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec2ld> MFVec2ld;




/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3ub> MFVec3ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3b> MFVec3b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3us> MFVec3us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3s> MFVec3s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3f> MFVec3f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3fx> MFVec3fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3d> MFVec3d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec3ld> MFVec3ld;





/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4ub> MFVec4ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4b> MFVec4b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4us> MFVec4us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4s> MFVec4s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4f> MFVec4f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4fx> MFVec4fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4d> MFVec4d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Vec4ld> MFVec4ld;




/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1ub> MFPnt1ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1b> MFPnt1b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1us> MFPnt1us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1s> MFPnt1s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1f> MFPnt1f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1fx> MFPnt1fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1d> MFPnt1d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt1ld> MFPnt1ld;





/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2ub> MFPnt2ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2b> MFPnt2b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2us> MFPnt2us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2s> MFPnt2s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2f> MFPnt2f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2fx> MFPnt2fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2d> MFPnt2d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt2ld> MFPnt2ld;





/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3ub> MFPnt3ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3b> MFPnt3b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3us> MFPnt3us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3s> MFPnt3s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3f> MFPnt3f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3fx> MFPnt3fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3d> MFPnt3d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt3ld> MFPnt3ld;





/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4ub> MFPnt4ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4b> MFPnt4b;
#endif


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4us> MFPnt4us;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4s> MFPnt4s;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4f> MFPnt4f;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4fx> MFPnt4fx;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4d> MFPnt4d;


/*! \ingroup GrpBaseFieldMulti */
typedef MField<Pnt4ld> MFPnt4ld;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1ub : public MField<Vec1ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1b : public MField<Vec1b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1us : public MField<Vec1us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1s : public MField<Vec1s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1f : public MField<Vec1f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1fx : public MField<Vec1fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1d : public MField<Vec1d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec1ld : public MField<Vec1ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2ub : public MField<Vec2ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2b : public MField<Vec2b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2us : public MField<Vec2us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2s : public MField<Vec2s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2f : public MField<Vec2f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2fx : public MField<Vec2fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2d : public MField<Vec2d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec2ld : public MField<Vec2ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3ub : public MField<Vec3ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3b : public MField<Vec3b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3us : public MField<Vec3us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3s : public MField<Vec3s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3f : public MField<Vec3f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3fx : public MField<Vec3fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3d : public MField<Vec3d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec3ld : public MField<Vec3ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4ub : public MField<Vec4ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4b : public MField<Vec4b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4us : public MField<Vec4us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4s : public MField<Vec4s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4f : public MField<Vec4f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4fx : public MField<Vec4fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4d : public MField<Vec4d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFVec4ld : public MField<Vec4ld> {};


/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1ub : public MField<Pnt1ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1b : public MField<Pnt1b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1us : public MField<Pnt1us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1s : public MField<Pnt1s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1f : public MField<Pnt1f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1fx : public MField<Pnt1fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1d : public MField<Pnt1d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt1ld : public MField<Pnt1ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2ub : public MField<Pnt2ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2b : public MField<Pnt2b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2us : public MField<Pnt2us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2s : public MField<Pnt2s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2f : public MField<Pnt2f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2fx : public MField<Pnt2fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2d : public MField<Pnt2d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt2ld : public MField<Pnt2ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3ub : public MField<Pnt3ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3b : public MField<Pnt3b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3us : public MField<Pnt3us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3s : public MField<Pnt3s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3f : public MField<Pnt3f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3fx : public MField<Pnt3fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3d : public MField<Pnt3d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt3ld : public MField<Pnt3ld> {};

/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4ub : public MField<Pnt4ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4b : public MField<Pnt4b> {};
#endif
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4us : public MField<Pnt4us> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4s : public MField<Pnt4s> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4f : public MField<Pnt4f> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4fx : public MField<Pnt4fx> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4d : public MField<Pnt4d> {};
/*! \ingroup GrpBaseFieldMulti \ingroup GrpLibOSGBase */
struct MFPnt4ld : public MField<Pnt4ld> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGVECMFIELDS_H_ */
