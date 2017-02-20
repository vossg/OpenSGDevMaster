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

#ifndef _OSGPOLYGONBODY_H_
#define _OSGPOLYGONBODY_H_

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGPolygon.h"

OSG_BEGIN_NAMESPACE

class LineSegment;
class Plane;
class BoxVolume;
class FrustumVolume;

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING PolygonBody
{
    /*==========================  PUBLIC  =================================*/

  public:
    typedef Polygon::VecVerticesT       VecVerticesT;
    typedef std::vector<Polygon*>       VecPolygonsT;
    typedef std::vector<LineSegment*>   VecLineSegmentsT;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PolygonBody();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~PolygonBody();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set                                       */
    /*! \{                                                                 */

    void    setVertices         (const VecVerticesT& vertices);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */
    void    add     (Polygon* polygon);
    void    add     (const VecVerticesT& vertices, const Vec3f& normal);
    void    add     (const FrustumVolume& frustum);

    void    clip    (const Plane& plane);
    void    clip    (const BoxVolume& boundingBox);
    void    clip    (const FrustumVolume& frustum);

    void    extrude (const Vec3f& direction, const BoxVolume& boundingBox);

    void    createHull          (const Pnt3f& point);
    void    createConvexHull    (const Pnt3f& point);
    void    createConvexHull    ();

    void    createUniqueVertices(Real32 tolerance = TypeTraits<OSG::Real32>::getDefaultEps());

    void    clear               ();


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */
    std::size_t             getNumVertices  () const;
    const VecVerticesT&     getVertices     () const;

    std::size_t             getNumPolygons  () const;
    const VecPolygonsT&     getPolygons     () const;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/
  private:
                    PolygonBody             (const PolygonBody& rhs);
    PolygonBody&    operator=               (const PolygonBody& rhs);

    void            addUniqueEdge           (VecLineSegmentsT& outEdgeList, const LineSegment& line) const;
    void            addUniqueVertex         (const Pnt3f& vertex, Real32 tolerance);
    void            removeVisiblePolygons   (const Pnt3f& point);
    void            intersect               (
                                                const LineSegment& line,
                                                const Pnt3f& min,
                                                const Pnt3f& max,
                                                VecVerticesT& vertices
                                            );
    bool            clip                    (Real32 p, Real32 q, Real32& u1, Real32& u2) const;
    void            extrudePolygons         (const Vec3f& direction, const BoxVolume& boundingBox);
    void            createConvexHull        (const VecVerticesT& vertices);


  private:
    VecVerticesT    _vertices;
    VecPolygonsT    _polygons;
};

OSG_END_NAMESPACE

#include "OSGPolygonBody.inl"

#endif // _OSGPOLYGONBODY_H_
