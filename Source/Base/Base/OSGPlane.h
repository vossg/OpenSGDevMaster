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

#ifndef _OSGPLANE_H_
#define _OSGPLANE_H_

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include "OSGVector.h"
#include "OSGMatrixFwd.h"
#include "OSGLine.h"
#include "OSGLineSegment.h"
#include "OSGPolygon.h"

OSG_BEGIN_NAMESPACE

class Line;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING Plane 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    Plane(      void                                        );
    Plane(const Plane &obj                                  );
    Plane(const Pnt3f &p0, const Pnt3f  &p1, const Pnt3f &p2);
    Plane(const Pnt3f &p0, const Pnt3f  &p1, const Pnt3f &p2, Polygon::VertexOrder order);
    Plane(const Vec3f &n,        Real32  d                  );
    Plane(const Vec3f &n, const  Pnt3f  &p                  );
    Plane(const Vec4f &equation                             );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Plane(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Offset                                  */
    /*! \{                                                                 */

    void offset(Real32 d);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool   intersect        (const Plane   &pl, 
                                   Line    &intersection) const;
    bool   intersect        (const Line    &l,  
                                   Pnt3f   &intersection) const;
    bool   intersect        (const Line    &l,  
                                   Real32  &t           ) const;
    bool   intersectInfinite(const Line    &l,  
                                   Real32  &t           ) const;
    bool   intersectInfinite(const Line    &l,  
                                   Pnt3f   &intersection) const;

    bool   intersect        (const LineSegment &segment,
                                   Real32      &t,
                                   Real32      tolerance = 
                        TypeTraits<OSG::Real32>::getDefaultEps()) const;

    bool   intersect        (const LineSegment &segment,
                                   Pnt3f       &intersection,
                                   Real32      tolerance = 
                        TypeTraits<OSG::Real32>::getDefaultEps()) const;

    void   transform        (const Matrix  &matrix,
                                   bool    ortho = true );

    void   transformTransposedInverse
                            (const Matrix  &matrix      );

    int    clip             (      Pnt3f  *polyIn, 
                                   Pnt3f  *polyOut, 
                                   int     count        ) const;


    bool   isOnPlane        (const Pnt3f  &point        ) const;
    bool   isInHalfSpace    (const Pnt3f  &point        ) const;
    bool   isBehind         (const Pnt3f  &point        ) const;
    Real32 distance         (const Pnt3f  &point        ) const;

    bool   isInHalfSpace    (const Pnt3f  &min, 
                             const Pnt3f  &max          ) const;
    bool   isOutHalfSpace   (const Pnt3f  &min, 
                             const Pnt3f  &max          ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void set(const Vec3f  &normal, 
                   Real32  dist  );
    void set(      Real32   x, 
                   Real32   y, 
                   Real32   z, 
                   Real32   dist );
    void set(const Vec4f  &plane );
    void setEquation    (const Vec4f& equation);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    const Vec3f  &getNormal            (void) const;
          Real32  getDistanceFromOrigin(void) const;


    void  setDirectionIndexPoint(const Pnt3f &min,   const Pnt3f &max,
                                 const UInt8  index,       Pnt3f &pnt) const;

    Vec4f getEquation           (void) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */
    
    Plane &operator =(const Plane &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator ==(const Plane &rhs) const;
    bool operator !=(const Plane &rhr) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
   
    void updateDirectionIndex(void);
    void calcHessNorm        (void);

    Vec3f  _normal;
    Real32 _distance;
    UInt8  _directionIndex;
};

/*! \relates Plane
 */
OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os, 
                          const OSG::Plane   &obj);

OSG_END_NAMESPACE

#include "OSGPlane.inl"

#endif // _OSG_PLANE_H_
