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

#ifndef _OSG_TILE_LOAD_BALANCER_H_
#define _OSG_TILE_LOAD_BALANCER_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include <vector>

#include "OSGTileGeometryLoad.h"
#include "OSGRenderNode.h"

OSG_BEGIN_NAMESPACE

class Action;

/*! \ingroup GrpClusterWindowBalancer
    \ingroup GrpLibOSGCluster
    \includebasedoc
 */

class OSG_CLUSTER_DLLMAPPING TileLoadBalancer
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*! \nohierarchy
     */

    struct Region 
    {
        Int32  x1,y1,x2,y2;
        Real32 culledFaces;
        Real32 culledNodes;
        Real32 faces;
        Real32 pixel;
    };

    typedef std::vector<TileGeometryLoad>           TileGeometryLoadLstT;
    typedef std::map<UInt32,
                    TileGeometryLoadLstT::iterator> TileGeometryLoadMapT;

    typedef std::vector<Region>                     ResultT;
    typedef std::vector<RenderNode>                 RenderNodeLstT;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TileLoadBalancer(bool useFaceDistribution=false,
                     bool cutBestDirection=true);
    TileLoadBalancer(const TileLoadBalancer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    TileLoadBalancer& operator =(const TileLoadBalancer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TileLoadBalancer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Load balancing functions                     */
    /*! \{                                                                 */

    void update             (Node             *node   );
    void balance            (Viewport         *vp,
                             bool              shrink,
                             ResultT          &result );
    void addRenderNode      (const RenderNode &rn,UInt32 id);
    void drawVolumes        (Window           *win);
    void setRegionStatistics(Viewport         *vp,
                             ResultT          &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    /*! \nohierarchy
     */

    class RegionLoad 
    {
      public:
        RegionLoad         ( TileGeometryLoad *load=NULL           );
        Real32   getCost   ( const RenderNode &renderNode );
        Real32   getCost   ( const RenderNode &renderNode,
                             const Int32 wmin[2],
                             const Int32 wmax[2]          ) const;
        TileGeometryLoad *getLoad   ( void                         );
        void     updateCost( const Int32 wmin[2],
                             const Int32 wmax[2]          );
      private:
        Real32   _visibleFaces;
        Real32   _invisibleFaces;
        Real32   _pixel;
        TileGeometryLoad *_load;
    };

    typedef std::vector<RegionLoad>   RegionLoadVecT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    TileGeometryLoadLstT  _tileGeometryLoad;
    RenderNodeLstT        _renderNode;
    bool                  _useFaceDistribution;
    bool                  _cutBestDirection;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    double runFaceBench(GLuint dlist,UInt32 size,Real32 visible);
    void updateSubtree (Node * const node,TileGeometryLoadMapT &loadMap);
    void splitRegion   (UInt32          rnFrom,
                        UInt32          rnTo,
                        RegionLoadVecT &visible,
                        Int32           amin[2],
                        Int32           amax[2],
                        UInt32          depth,
                        ResultT        &result);
    Real32 findBestCut (const RenderNode &renderNodeA,
                        const RenderNode &renderNodeB,
                        RegionLoadVecT &visible,
                        Int32           amin[2],
                        Int32           amax[2],
                        Int32          &bestAxis,
                        Int32          &bestCut);
    double calcFaceRenderingCost(TileGeometryLoad *load,
                                 Int32 amin[2],Int32 amax[2]);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/

  private:

    friend class RegionLoad;
};

OSG_END_NAMESPACE

#include "OSGTileLoadBalancer.inl"

#endif /* _TILE_GEOMETRY_LOADMANAGER_H_ */




