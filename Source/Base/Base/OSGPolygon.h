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

#ifndef _OSGPOLYGON_H_
#define _OSGPOLYGON_H_

#include "OSGBaseTypes.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class Line;
class Plane;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING Polygon
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum VertexOrder
    {
        ccw = 0,
        cw
    };

    typedef std::vector<Pnt3f>  VecVerticesT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Polygon(                   );
    Polygon(const  Polygon& rhs);
    Polygon(
                const Pnt3f& p0,
                const Pnt3f& p1,
                const Pnt3f& p2
           );
    Polygon(
                const Pnt3f& p0,
                const Pnt3f& p1,
                const Pnt3f& p2,
                const Pnt3f& p3
           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Polygon();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
    Polygon&            operator=(const Polygon& rhs);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */
    void                setNormal(const Vec3f& normal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */

    void                addVertex       (const Pnt3f& vertex);
    void                addUniqueVertex (const Pnt3f& vertex,
                                               Real32 tolerance =
                                TypeTraits<OSG::Real32>::getDefaultEps());
    void                reverseVertices ();
    void                orderVertices(VertexOrder order = ccw);

    void                clip            (const Plane& plane,
                                         VecVerticesT& intersectionPnts  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    std::size_t         getNumVertices  () const;
    const VecVerticesT& getVertices     () const;
          VecVerticesT& getVertices     ();

    const Vec3f&        getNormal       () const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
    VecVerticesT _vertices;
    Vec3f       _normal;
};

OSG_END_NAMESPACE

#include "OSGPolygon.inl"

#endif // _OSGPOLYGON_H_
