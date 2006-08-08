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

#ifndef _OSGLINE_H_
#define _OSGLINE_H_

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class BoxVolume;
class SphereVolume;
class CylinderVolume;
class FrustumVolume;

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING Line
{
    /*==========================  PUBLIC  =================================*/

  public:
      
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Line(       void                        );
    Line(const  Line  &obj                  );
    Line(const  Pnt3r &p0,  const Pnt3r &p1 );
    Line(const  Pnt3r &pos, const Vec3r &dir);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Line(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */

    void setValue(const Pnt3r &p0 , const Pnt3r &p1 );
    void setValue(const Pnt3r &pos, const Vec3r &dir);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */

    bool  getClosestPoints(const Line  &line2,
                                 Pnt3r &ptOnThis, 
                                 Pnt3r &ptOnLine2) const;
    Pnt3r getClosestPoint (const Pnt3r &point    ) const;
    Real  distance        (const Pnt3r &point    ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    const Pnt3r &getPosition (void) const; 
    const Vec3r &getDirection(void) const; 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool intersect(const SphereVolume   &sphere              ) const;
    bool intersect(const SphereVolume   &sphere,  Real &enter,
                                                  Real &exit ) const;
    bool intersect(const CylinderVolume &cyl                 ) const;
    bool intersect(const CylinderVolume &cyl,     Real &enter,
                                                  Real &exit ) const;
    bool intersect(const FrustumVolume  &frustum             ) const;
    bool intersect(const FrustumVolume  &frustum, Real &enter,
                                                  Real &exit ) const;
    bool intersect(const BoxVolume      &box,     Real &enter,
                                                  Real &exit ) const;
    bool intersect(      Real            angle,
                   const BoxVolume      &box                 ) const;
    bool intersect(      Real            angle,
                   const Vec3r          &point               ) const;
    bool intersect(      Real            angle,
                   const Vec3r          &v0,
                   const Vec3r          &v1,
                         Vec3r          &pt                  ) const;
    bool intersect(const Pnt3r          &v0,
                   const Pnt3r          &v1,
                   const Pnt3r          &v2,
                         Real           &t,
                         Vec3r          *normal = NULL       ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3r   _pos;
    Vec3r   _dir;

};

OSG_END_NAMESPACE

#include "OSGLine.inl"

#endif // _OSGLINE_H_
