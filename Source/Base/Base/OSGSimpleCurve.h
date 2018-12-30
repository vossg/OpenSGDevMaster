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

#ifndef _OSGSIMPLECURVE_H_
#define _OSGSIMPLECURVE_H_

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy

    This files contains a simple spline curve abstraction. A spline is 
    a sequence of Bezier curves. The splines as well as the curves are
    parametrized in the interval [0,1].

    This classes are written to support some of the examples, which needs
    some simple curve abstractions for simulation purposes.

    They are simple in the sense that the splines do not use multi field
    containers for the vector types and that the length calculation is
    based on a simple linear segment length accumulation.

    To be used in a more serious setup some polishing and enhancements
    are probably be necessary.
 */

class OSG_BASE_DLLMAPPING CubicBezierCurve
{
    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    CubicBezierCurve    (const OSG::Pnt3f& p0, 
                         const OSG::Pnt3f& p1, 
                         const OSG::Pnt3f& p2, 
                         const OSG::Pnt3f& p3);

    CubicBezierCurve    (const CubicBezierCurve& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    CubicBezierCurve& operator= (const CubicBezierCurve& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    OSG::Pnt3f  operator()      (OSG::Real32 t) const;
    OSG::Vec3f  getTangent      (OSG::Real32 t) const;
    OSG::Vec3f  getNormal       (OSG::Real32 t) const;
    OSG::Vec3f  getBinormal     (OSG::Real32 t) const;
    OSG::Matrix getFrame        (OSG::Real32 t, bool position_only) const;
    OSG::Real32 getLength       (OSG::UInt32 numSeg = 10) const;
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
private:
    OSG::Vec3f  fst_derivative  (OSG::Real32 t) const;
    OSG::Vec3f  sec_derivative  (OSG::Real32 t) const;
    OSG::Vec3f  thr_devivative  (OSG::Real32 t) const;

private:
    OSG::Pnt3f p[4];
};

class OSG_BASE_DLLMAPPING SmoothCubicBezierSpline
{
    /*==========================  PUBLIC  =================================*/
public:
    typedef std::vector<OSG::Pnt3f> points_t;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SmoothCubicBezierSpline(const points_t& vKnots);
    SmoothCubicBezierSpline(const SmoothCubicBezierSpline& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    SmoothCubicBezierSpline& operator=  (const SmoothCubicBezierSpline& rhs);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Interface                                 */
    /*! \{                                                                 */

    OSG::Pnt3f  operator()  (OSG::Real32 t) const;
    OSG::Vec3f  getTangent  (OSG::Real32 t) const;
    OSG::Vec3f  getNormal   (OSG::Real32 t) const;
    OSG::Vec3f  getBinormal (OSG::Real32 t) const;
    OSG::Matrix getFrame    (OSG::Real32 t, bool position_only = false) const;
    OSG::Real32 getLength   (OSG::UInt32 numSeg = 10) const;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
private:
    void        calc_ctrl_pnts  (points_t& p1, points_t& p2) const;
    std::size_t index           (OSG::Real32 t) const;
    OSG::Real32 t_              (OSG::Real32 t, std::size_t idx) const;

private:
    std::vector<OSG::Pnt3f>         knots;
    std::vector<OSG::Real32>        intervals;
    std::vector<CubicBezierCurve>   curves;
};

OSG_END_NAMESPACE

#include "OSGSimpleCurve.inl"

#endif // _OSGSIMPLECURVE_H_
