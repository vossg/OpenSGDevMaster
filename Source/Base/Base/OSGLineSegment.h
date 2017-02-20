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

#ifndef _OSGLINESEGMENT_H_
#define _OSGLINESEGMENT_H_

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

class OSG_BASE_DLLMAPPING LineSegment
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LineSegment(                                         );
    LineSegment(const  LineSegment &rhs                  );
    LineSegment(const  Pnt3f       &p0,  const Pnt3f &p1 );
    LineSegment(const  Pnt3f       &pos, const Vec3f &dir);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~LineSegment();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    LineSegment&    operator=   (const LineSegment &rhs);

    bool            operator==  (const LineSegment &rhs) const;
    bool            operator!=  (const LineSegment &rhs) const;

    bool            equals      (const LineSegment &rhs,
                                       Real32 tolerance =
                            TypeTraits<OSG::Real32>::getDefaultEps()) const;



    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */

    void setValue           (const Pnt3f &p0 , const Pnt3f &p1 );
    void setValue           (const Pnt3f &pos, const Vec3f &dir);

    void setStartPoint      (const Pnt3f& p);
    void setEndPoint        (const Pnt3f& p);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Transform                                    */
    /*! \{                                                                 */

    void transform(const Matrix4f &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    const Pnt3f& getStartPoint  () const;
    const Pnt3f  getEndPoint    () const;

    const Vec3f &getDirection   () const;

          Pnt3f  getPoint       (Real32 t) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
    Pnt3f   _startPoint;
    Vec3f   _direction;

};

/*! \relates Line
 */
OSG_BASE_DLLMAPPING
std::ostream &operator <<(      std::ostream &os,
                          const OSG::LineSegment    &obj);

OSG_END_NAMESPACE

#include "OSGLineSegment.inl"

#endif // _OSGLINESEGMENT_H_
