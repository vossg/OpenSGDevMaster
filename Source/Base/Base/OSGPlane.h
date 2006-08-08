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

OSG_BEGIN_NAMESPACE

class Line;

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING Plane 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    Plane(      void                                       );
    Plane(const Plane &obj                                 );
    Plane(const Pnt3r &p0, const Pnt3r &p1, const Pnt3r &p2);
    Plane(const Vec3r &n,        Real   d                  );
    Plane(const Vec3r &n, const  Pnt3r &p                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Plane(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Offset                                  */
    /*! \{                                                                 */

    void offset(Real d);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool intersect        (const Plane   &pl, 
                                 Line    &intersection) const;
    bool intersect        (const Line    &l,  
                                 Pnt3r   &intersection) const;
    bool intersect        (const Line    &l,  
                                 Real    &t           ) const;

    bool intersectInfinite(const Line    &l,  
                                 Real    &t           ) const;
    bool intersectInfinite(const Line    &l,  
                                 Pnt3r   &intersection) const;

    void transform        (const Matrixr &matrix      );

    int  clip             (      Pnt3r  *polyIn, 
                                 Pnt3r  *polyOut, 
                                 int     count        ) const;


    bool isOnPlane        (const Pnt3r  &point        ) const;
    bool isInHalfSpace    (const Pnt3r  &point        ) const;
    Real distance         (const Pnt3r  &point        ) const;

    bool isInHalfSpace    (const Pnt3r  &min, 
                           const Pnt3r  &max          ) const;
    bool isOutHalfSpace   (const Pnt3r  &min, 
                           const Pnt3r  &max          ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void set(const Vec3r &normal, 
                          Real  distance);
    void set(      Real   x, 
                   Real   y, 
                   Real   z, 
                   Real   distance      );
    void set(const Vec4r &plane         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    const Vec3r &getNormal            (void) const;
          Real   getDistanceFromOrigin(void) const;


    void  setDirectionIndexPoint(const Pnt3r &min,   const Pnt3r &max,
                                 const UInt8  index,       Pnt3r &pnt) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    friend bool operator ==(const Plane &p1, const Plane &p2);

    inline 
    friend bool operator !=(const Plane &p1, const Plane &p2);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
   
    void updateDirectionIndex(void);

    Vec3r _normalVec;
    Real  _distance;
    UInt8 _directionIndex;
};

OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os, 
                          const Plane        &obj);

OSG_END_NAMESPACE

#include "OSGPlane.inl"

#endif // _OSG_PLANE_H_
