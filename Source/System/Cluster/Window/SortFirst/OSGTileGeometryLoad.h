/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSG_TILE_GEOMETRY_LOAD_H_
#define _OSG_TILE_GEOMETRY_LOAD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGClusterDef.h"
#include "OSGGeometry.h"
#include "OSGCamera.h"
#include "OSGViewport.h"

#include <vector>

OSG_BEGIN_NAMESPACE

#define FACE_DISTRIBUTION_SAMPLING_COUNT 8

/*! \ingroup GrpClusterWindowBalancer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING TileGeometryLoad
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TileGeometryLoad(UInt32 nodeId,bool useFaceDistribution=false);
    TileGeometryLoad(const TileGeometryLoad &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TileGeometryLoad(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  load calculation                            */
    /*! \{                                                                 */

    void updateView        ( Matrix &viewing,
                             Matrix &projection,
                             Real32 near,
                             UInt32 width,
                             UInt32 height                );
    void updateGeometry    (                              );
    bool checkRegion       ( Int32 min[2],
                             Int32 max[2]                 );
    bool isVisible         (                              ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void             setValid(bool s);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    Node *            getNode() const;
    const Int32 *     getMin();
    const Int32 *     getMax();
    UInt32            getFaces();
    Real32            getVisibleFraction( const Int32 wmin[2],
                                          const Int32 wmax[2],
                                                Int32 viswmin[2],
                                                Int32 viswmax[2] );
    bool              getVisibleArea    ( const Int32 wmin[2],
                                          const Int32 wmax[2],
                                                Int32 viswmin[2],
                                                Int32 viswmax[2] );

    bool              isInvalid(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    TileGeometryLoad& operator = (const TileGeometryLoad &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator < (const TileGeometryLoad &other) const;
    //bool operator == (const TileGeometryLoad &other) const;
    //bool operator != (const TileGeometryLoad &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                     utilities                                */
    /*! \{                                                                 */

    Real32 getFaceDistribution(UInt32 dir,Real32 cut);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                        Members                               */
    /*! \{                                                                 */

    UInt32                             _nodeId;
    Geometry                          *_geometry;
    UInt32                             _faces;
    Int32                              _min[2];
    Int32                              _max[2];
    std::vector<std::vector<Real32> >  _faceDistribution;
    UInt32                             _faceDistDirX;
    UInt32                             _faceDistDirY;
    bool                               _visible;
    bool                               _useFaceDistribution;
    Real32                             _areaSize;
    bool                               _valid;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                  static elements                             */
    /*! \{                                                                 */

    static std::vector<Plane>    _directions;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:
};

OSG_END_NAMESPACE

#include "OSGTileGeometryLoad.inl"

#endif /* OSG_TILE_GEOMETRY_LOAD_H */
