/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

/** Constructor
 **/
inline 
TileLoadBalancer::RegionLoad::RegionLoad(TileGeometryLoad *load):
    _visibleFaces  (0.f ),
    _invisibleFaces(0.f ),
    _pixel         (0.f ),
    _load          (load)
{
}

/** Update region dependent values
 **/
inline 
void TileLoadBalancer::RegionLoad::updateCost(const Int32 wmin[2],
                                              const Int32 wmax[2])
{
    Real32 faces  =Real32(_load->getFaces());
    Real32 visible;
    Int32 vismin[2];
    Int32 vismax[2];

    visible=_load->getVisibleFraction(wmin,wmax,vismin,vismax);
    if(visible)
    {
        _visibleFaces=faces*visible;
        _invisibleFaces=faces-_visibleFaces;
        _pixel=Real32(
            (vismax[0] - vismin[0] + 1)*
            (vismax[1] - vismin[1] + 1));
    }
    else
    {
        _pixel=0;
        _invisibleFaces=0;
        _visibleFaces=0;
    }
}

/** Calculate the rendering cost
 *
 * \param renderNode  Node to render the geometry
 **/

inline 
Real32 TileLoadBalancer::RegionLoad::getCost(const RenderNode &renderNode)
{
    return renderNode.estimatePerformance(_invisibleFaces,
                                          _visibleFaces,
                                          _pixel);
}

/** Calculate the rendering cost for the given region
 *
 * \param renderNode  Node to render the geometry
 * \param wmin        bottom, left corner of the area
 * \param wmax        top, right corner of the area
 **/

inline 
Real32 TileLoadBalancer::RegionLoad::getCost(const RenderNode &renderNode,
                                             const Int32 wmin[2],
                                             const Int32 wmax[2]) const
{
    Int32 vismin[2];
    Int32 vismax[2];
    Real32 visibleFaces;
    Real32 invisibleFaces;
    Real32 visible;

    Real32 faces  =Real32(_load->getFaces());
    visible=_load->getVisibleFraction(wmin,wmax,vismin,vismax);
    if(visible==0.0)
        return 0.0;
    visibleFaces=faces*visible;
    invisibleFaces=faces-visibleFaces;
    Real32 pixel=Real32(
        (vismax[0] - vismin[0] + 1)*
        (vismax[1] - vismin[1] + 1));
    return renderNode.estimatePerformance(invisibleFaces,
                                          visibleFaces,
                                          pixel);
}

/** Return gemetry load info object
 **/
inline 
TileGeometryLoad * TileLoadBalancer::RegionLoad::getLoad(void)
{
    return _load;
}

OSG_END_NAMESPACE
