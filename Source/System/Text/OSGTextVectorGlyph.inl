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


OSG_BEGIN_NAMESPACE


inline TextVectorGlyph::Point::Point(const Vec2f &_pos, PointType _type)
    : pos (_pos ),
      type(_type)
{
}

inline const TextVectorGlyph::Outline &TextVectorGlyph::getOutline() const
{
     return _outline;
}

inline TextVectorGlyph::TextVectorGlyph(void)
    : TextGlyph           (   ),
      _width              (0.f),
      _height             (0.f),
      _horiBearingX       (0.f),
      _horiBearingY       (0.f),
      _vertBearingX       (0.f),
      _vertBearingY       (0.f),
      _outline            (   ),
      _contourOrientations(   ),
      _polygonOutlineMap  (   ),
      _normalMap          (   )
{
}

inline TextVectorGlyph::VertexNormal::VertexNormal(
    const Vec2f &nextEdgeNormal_, const Vec2f &meanEdgeNormal_, Real32 edgeAngle_)
    
    : nextEdgeNormal(nextEdgeNormal_),
      meanEdgeNormal(meanEdgeNormal_),
      edgeAngle     (edgeAngle_     )
{
}

OSG_END_NAMESPACE

