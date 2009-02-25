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

#ifndef _OSGVECSFIELDS_H_
#define _OSGVECSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSField.h"
#include "OSGVecFieldTraits.h"

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2ub> SFVec2ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2b> SFVec2b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2us> SFVec2us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2s> SFVec2s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2f> SFVec2f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2fx> SFVec2fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2d> SFVec2d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec2ld> SFVec2ld;





/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3ub> SFVec3ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3b> SFVec3b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3us> SFVec3us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3s> SFVec3s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3f> SFVec3f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3fx> SFVec3fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3d> SFVec3d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec3ld> SFVec3ld;





/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4ub> SFVec4ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4b> SFVec4b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4us> SFVec4us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4s> SFVec4s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4f> SFVec4f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4fx> SFVec4fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4d> SFVec4d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Vec4ld> SFVec4ld;




/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2ub> SFPnt2ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2b> SFPnt2b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2us> SFPnt2us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2s> SFPnt2s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2f> SFPnt2f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2fx> SFPnt2fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2d> SFPnt2d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt2ld> SFPnt2ld;





/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3ub> SFPnt3ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3b> SFPnt3b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3us> SFPnt3us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3s> SFPnt3s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3f> SFPnt3f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3fx> SFPnt3fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3d> SFPnt3d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt3ld> SFPnt3ld;





/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4ub> SFPnt4ub;


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4b> SFPnt4b;
#endif


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4us> SFPnt4us;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4s> SFPnt4s;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4f> SFPnt4f;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4fx> SFPnt4fx;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4d> SFPnt4d;


/*! \ingroup GrpBaseFieldSingle */
typedef SField<Pnt4ld> SFPnt4ld;



#ifdef OSG_FLOAT_PROFILE
typedef SFVec2f  SFVec2r;
typedef SFVec3f  SFVec3r;
typedef SFVec4f  SFVec4r;

typedef SFPnt2f  SFPnt2r;
typedef SFPnt3f  SFPnt3r;
typedef SFPnt4f  SFPnt4r;
#else
typedef SFVec2fx SFVec2r;
typedef SFVec3fx SFVec3r;
typedef SFVec4fx SFVec4r;

typedef SFPnt2fx SFPnt2r;
typedef SFPnt3fx SFPnt3r;
typedef SFPnt4fx SFPnt4r;
#endif

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle */
struct SFVec2ub : public SField<Vec2ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2b : public SField<Vec2b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2us : public SField<Vec2us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2s : public SField<Vec2s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2f : public SField<Vec2f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2fx : public SField<Vec2fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2d : public SField<Vec2d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec2ld : public SField<Vec2ld> {};

/*! \ingroup GrpBaseFieldSingle */
struct SFVec3ub : public SField<Vec3ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3b : public SField<Vec3b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3us : public SField<Vec3us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3s : public SField<Vec3s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3f : public SField<Vec3f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3fx : public SField<Vec3fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3d : public SField<Vec3d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec3ld : public SField<Vec3ld> {};

/*! \ingroup GrpBaseFieldSingle */
struct SFVec4ub : public SField<Vec4ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4b : public SField<Vec4b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4us : public SField<Vec4us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4s : public SField<Vec4s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4f : public SField<Vec4f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4fx : public SField<Vec4fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4d : public SField<Vec4d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFVec4ld : public SField<Vec4ld> {};


/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2ub : public SField<Pnt2ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2b : public SField<Pnt2b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2us : public SField<Pnt2us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2s : public SField<Pnt2s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2f : public SField<Pnt2f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2fx : public SField<Pnt2fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2d : public SField<Pnt2d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt2ld : public SField<Pnt2ld> {};

/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3ub : public SField<Pnt3ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3b : public SField<Pnt3b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3us : public SField<Pnt3us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3s : public SField<Pnt3s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3f : public SField<Pnt3f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3fx : public SField<Pnt3fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3d : public SField<Pnt3d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt3ld : public SField<Pnt3ld> {};

/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4ub : public SField<Pnt4ub> {};
#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4b : public SField<Pnt4b> {};
#endif
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4us : public SField<Pnt4us> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4s : public SField<Pnt4s> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4f : public SField<Pnt4f> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4fx : public SField<Pnt4fx> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4d : public SField<Pnt4d> {};
/*! \ingroup GrpBaseFieldSingle */
struct SFPnt4ld : public SField<Pnt4ld> {};



#ifdef OSG_FLOAT_PROFILE
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec2f  SFVec2r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec3f  SFVec3r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec4f  SFVec4r;

/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt2f  SFPnt2r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt3f  SFPnt3r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt4f  SFPnt4r;
#else
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec2fx SFVec2r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec3fx SFVec3r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFVec4fx SFVec4r;

/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt2fx SFPnt2r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt3fx SFPnt3r;
/*! \ingroup GrpBaseFieldSingle */
typedef SFPnt4fx SFPnt4r;
#endif

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGVECSFIELDS_H_ */
