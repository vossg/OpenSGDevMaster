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
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

class BoxVolume;
class SphereVolume;
class CylinderVolume;
class FrustumVolume;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
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
    Line(const  Pnt3f &p0,  const Pnt3f &p1 );
    Line(const  Pnt3f &pos, const Vec3f &dir);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Line(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
    
    bool  operator ==(const Line &rhs) const;
    bool  operator !=(const Line &rhs) const;

    bool  equals     (const Line &rhs, 
                      Real32 tolerance = 
                            TypeTraits<OSG::Real32>::getDefaultEps()) const;
    
    Line &operator = (const Line &rhs);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */

    void setValue(const Pnt3f &p0 , const Pnt3f &p1 );
    void setValue(const Pnt3f &pos, const Vec3f &dir);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Transform                                    */
    /*! \{                                                                 */

    void transform(const Matrix4f &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */

    bool   getClosestPoints(const Line   &line2,
                                  Pnt3f  &ptOnThis, 
                                  Pnt3f  &ptOnLine2) const;
    bool   getClosestPoints(const Line   &line2,
                                  Real32 &tOnThis, 
                                  Real32 &tOnLine2 ) const;
    Pnt3f  getClosestPoint (const Pnt3f  &point    ) const;
    Real32 getClosestPointT(const Pnt3f  &point    ) const;
    Real32 distance        (const Pnt3f  &point    ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    const Pnt3f &getPosition (void) const; 
    const Vec3f &getDirection(void) const;
          Pnt3f  getPoint    (Real32 t) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool intersect(const SphereVolume   &sphere                ) const;
    bool intersect(const SphereVolume   &sphere,  Real32 &enter,
                                                  Real32 &exit ) const;
    bool intersect(const CylinderVolume &cyl                   ) const;
    bool intersect(const CylinderVolume &cyl,     Real32 &enter,
                                                  Real32 &exit ) const;
    bool intersect(const FrustumVolume  &frustum               ) const;
    bool intersect(const FrustumVolume  &frustum, Real32 &enter,
                                                  Real32 &exit ) const;
    bool intersect(const BoxVolume      &box,     Real32 &enter,
                                                  Real32 &exit ) const;
    bool intersect(      Real32          angle,
                   const BoxVolume      &box                   ) const;
    bool intersect(      Real32          angle,
                   const Vec3f          &point                 ) const;
    bool intersect(      Real32          angle,
                   const Vec3f          &v0,
                   const Vec3f          &v1,
                         Vec3f          &pt                    ) const;
    bool intersect(const Pnt3f          &v0,
                   const Pnt3f          &v1,
                   const Pnt3f          &v2,
                         Real32         &t,
                         Vec3f          *normal = NULL         ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3f   _pos;
    Vec3f   _dir;

};

/*! \relates Line
 */
OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os, 
                          const OSG::Line    &obj);

OSG_END_NAMESPACE

#include "OSGLine.inl"

#endif // _OSGLINE_H_
