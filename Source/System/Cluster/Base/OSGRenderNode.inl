/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

OSG_BEGIN_NAMESPACE

inline 
Real32 RenderNode::getVisibleFaceCost(void) const
{
    return _visibleFaceCost;
}

inline 
Real32 RenderNode::getInvisibleFaceCost(void) const
{
    return _invisibleFaceCost;
}

inline 
Real32 RenderNode::getDrawPixelCost(void) const
{
    return _drawPixelCost;
}

inline 
Real32 RenderNode::getReadPixelCost(void) const
{
    return _readPixelCost;
}

inline 
Real32 RenderNode::getWritePixelCost(void) const
{
    return _writePixelCost;
}

inline 
std::string RenderNode::getVendor(void) const
{
    return _vendor;
}

inline 
std::string RenderNode::getRenderer(void) const
{
    return _renderer;
}

inline 
void RenderNode::setVisibleFaceCost(Real32 value)
{
    _visibleFaceCost=value;
}

inline 
void RenderNode::setInvisibleFaceCost(Real32 value)
{
    _invisibleFaceCost=value;
}

inline 
void RenderNode::setDrawPixelCost(Real32 value)
{
    _drawPixelCost=value;
}

inline 
void RenderNode::setReadPixelCost(Real32 value)
{
    _readPixelCost=value;
}

inline 
void RenderNode::setWritePixelCost(Real32 value)
{
    _writePixelCost=value;
}

/*! set vendor string of the graphics board
 */

inline 
void RenderNode::setVendor(const std::string &value)
{
    _vendor=value;
}

/*! set renderer string of the graphics board
 */

inline 
void RenderNode::setRenderer(const std::string &value)
{
    _renderer=value;
}

/*! Estimate rendering performance. Facesetup end rasterisation is done
 *  in parallel on most hardware plattforms. So we use the maximum of 
 *  face cost and rasterisation cost.
 */
inline 
Real32 RenderNode::estimatePerformance(Real32 invisibleFaces,
                                       Real32 visibleFaces,
                                       Real32 pixel         ) const
{
    return 
        ( invisibleFaces * _invisibleFaceCost ) +
        osgMax( ( visibleFaces   * _visibleFaceCost   ), 
                ( pixel          * _drawPixelCost     ) );
}

OSG_END_NAMESPACE
