/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGGeometry.h"


OSG_BEGIN_NAMESPACE


/*! Check if the iterator has already reached the end of the geometry.
*/
inline
bool PrimitiveIterator::isAtEnd(void) const
{
    return _ended;
}

inline
Int32 PrimitiveIterator::getIndex(Int32 which) const
{
    return _actPointIndex + which;
}

/*! Return the index of the current primitive. The index runs from 0 to the
    number of faces in the geometry. Its main use is as an input to seek().
*/
inline
Int32 PrimitiveIterator::getIndex(void) const
{
    return _primIndex;
}

/*! Return the length(i.e. number of used vertices) of the current primitive.
*/
inline
UInt32 PrimitiveIterator::getLength(void) const
{
    return _actPrimLength;
}

/*! Return the type of the current primitive.
*/
inline
UInt32 PrimitiveIterator::getType(void) const
{
    return _actPrimType;
}

/*! Return the index (i.e. the number of the entry in the attribute's
    property which is used) of an attribute in the current primitive. 
    \a which is the attribute to access. Must be between 0 and getLength().
*/
inline
Int32 PrimitiveIterator::getPropertyIndex(Int32 att, Int32 which) const
{
    if(_props[att] == NullFC)
    {
        return -1;
    }
    
    GeoIntegralPropertyPtr ind = _inds[att];
    
    if(ind != NullFC)
    {
        return ind->getValue<Int32>(_actPointIndex + which);
    }
    else
    {
        return _actPointIndex + which;
    }
}

// Old style accessors. Still useful, even if a little limited

/*! Return the position index (i.e. the number of the entry in the positions
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
*/
inline
Int32 PrimitiveIterator::getPositionIndex(Int32 which) const
{
    return getPropertyIndex(Geometry::PositionsIndex, which);
}


/*! Return the position of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
*/
inline
Pnt3f PrimitiveIterator::getPosition(Int32 which) const
{
    Int32 ind = getPositionIndex(which);

    return _props[Geometry::PositionsIndex]->getValue<Pnt3f>(ind);
}

/*! Return the normal index (i.e. the number of the entry in the normal
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no normals, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getNormalIndex(Int32 which) const
{
    return getPropertyIndex(Geometry::NormalsIndex, which);
}


/*! Return the normal of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no normals, Vec3f::Null is returned.
*/
inline
Vec3f PrimitiveIterator::getNormal(Int32 which) const
{
    Int32 ind = getNormalIndex(which);

    if(ind < 0)
        return Vec3f::Null;

    return _props[Geometry::NormalsIndex]->getValue<Vec3f>(ind);
}

/*! Return the color index (i.e. the number of the entry in the color
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no colors, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getColorIndex(Int32 which) const
{
    return getPropertyIndex(Geometry::ColorsIndex, which);
}

/*! Return the color of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no colors, Color3f::Null is returned.
*/
inline
Color3f PrimitiveIterator::getColor(Int32 which) const
{
    Int32 ind = getColorIndex(which);

    if(ind < 0)
        return Color3f::Null;

    return _geo->getColors()->getValue<Color3f>(ind);
}


/*! Return the secondary color index (i.e. the number of the entry in the 
    secondary color property which is used) of a point in the current
    primitive. \a which is the point to access. Must be between 0 and
    getLength().

    If the geometry has no secondary colors, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getSecondaryColorIndex(Int32 which) const
{
    return getPropertyIndex(Geometry::SecondaryColorsIndex, which);
}

/*! Return the secondary color of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no secondary colors, Color3f::Null is returned.
*/
inline
Color3f PrimitiveIterator::getSecondaryColor(Int32 which) const
{
    Int32 ind = getSecondaryColorIndex(which);

    if(ind < 0)
        return Color3f::Null;

    return _geo->getSecondaryColors()->getValue<Color3f>(ind);
}

/*! Return the texture coordinates index (i.e. the number of the entry in the 
    texture coordinates property which is used) of a point in the current
    primitive.  \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex(Int32 which) const
{
    return getPropertyIndex(Geometry::TexCoordsIndex, which);
}

/*! Return the texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords(Int32 which) const
{
    Int32 ind = getTexCoordsIndex(which);

    if(ind < 0)
        return Vec2f::Null;

    return _props[Geometry::TexCoordsIndex]->getValue<Vec2f>(ind);
}


/*! Return the second texture coordinates index (i.e. the number of the entry
    in the textureCoordinates1 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no second texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex1(Int32 which) const
{
    return getPropertyIndex(Geometry::TexCoords1Index, which);
}


/*! Return the second texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no second texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords1(Int32 which) const
{
    Int32 ind = getTexCoordsIndex1(which);

    if(ind < 0)
        return Vec2f::Null;

    return _props[Geometry::TexCoords1Index]->getValue<Vec2f>(ind);
}


/*! Return the third texture coordinates index (i.e. the number of the entry
    in the textureCoordinates2 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no third texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex2(Int32 which) const
{
     return getPropertyIndex(Geometry::TexCoords2Index, which);
}


/*! Return the third texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no third texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords2(Int32 which) const
{
    Int32 ind = getTexCoordsIndex2(which);

    if(ind < 0)
        return Vec2f::Null;

    return _props[Geometry::TexCoords2Index]->getValue<Vec2f>(ind);
}


/*! Return the fourth texture coordinates index (i.e. the number of the entry
    in the textureCoordinates3 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no fourth texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex3(Int32 which) const
{
     return getPropertyIndex(Geometry::TexCoords3Index, which);
}


/*! Return the fourth texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no fourth texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords3(Int32 which) const
{
    Int32 ind = getTexCoordsIndex3(which);

    if(ind < 0)
        return Vec2f::Null;

    return _props[Geometry::TexCoords3Index]->getValue<Vec2f>(ind);
}

/*! Return the geometry the iterator is currently attached to.
*/
inline
ConstGeometryPtr PrimitiveIterator::getGeometry(void) const
{
    return _geo;
}

OSG_END_NAMESPACE
