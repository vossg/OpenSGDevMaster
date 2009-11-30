/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

/*! Return the index of the current face. The index runs from 0 to the
    number of points in the geometry. Its main use is as an input to 
    OSG::PointIterator::seek.
*/
inline       
Int32 PointIterator::getIndex(void) const
{
    return _pointIndex;
}

inline       
Int32 PointIterator::getPositionIndex(Int32 which) const
{
    return Inherited::getPositionIndex(_pointPntIndex);
}

inline       
Pnt3f PointIterator::getPosition(Int32 which) const
{
    Int32 ind = getPositionIndex(which);
    
    return getGeometry()->getPositions()->getValue<Pnt3f>(ind);
}

inline       
Int32 PointIterator::getNormalIndex(Int32 which) const
{
    return Inherited::getNormalIndex(_pointPntIndex);
}

inline 
Vec3f PointIterator::getNormal(Int32 which) const
{   
    Int32 ind = getNormalIndex(which);
    
    if(ind < 0)
        return Vec3f::Null;
        
    return getGeometry()->getNormals()->getValue<Vec3f>(ind);
}

inline       
Int32 PointIterator::getColorIndex(Int32 which) const
{
    return Inherited::getColorIndex(_pointPntIndex);
}

inline 
Color3f PointIterator::getColor(Int32 which) const
{   
    Int32 ind = getColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return getGeometry()->getColors()->getValue<Color3f>(ind);
}

inline       
Int32 PointIterator::getSecondaryColorIndex(Int32 which) const
{
    return Inherited::getSecondaryColorIndex(_pointPntIndex);
}

inline 
Color3f PointIterator::getSecondaryColor(Int32 which) const
{   
    Int32 ind = getSecondaryColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return getGeometry()->getSecondaryColors()->getValue<Color3f>(ind);
}


inline       
Int32 PointIterator::getTexCoordsIndex(Int32 which) const
{
    return Inherited::getTexCoordsIndex(_pointPntIndex);
}

inline 
Vec2f PointIterator::getTexCoords(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords()->getValue<Vec2f>(ind);
}


inline       
Int32 PointIterator::getTexCoordsIndex1(Int32 which) const
{
    return Inherited::getTexCoordsIndex1(_pointPntIndex);
}

inline 
Vec2f PointIterator::getTexCoords1(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex1(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords1()->getValue<Vec2f>(ind);
}


inline       
Int32 PointIterator::getTexCoordsIndex2(Int32 which) const
{
    return Inherited::getTexCoordsIndex2(_pointPntIndex);
}

inline 
Vec2f PointIterator::getTexCoords2(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex2(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords2()->getValue<Vec2f>(ind);
}


inline       
Int32 PointIterator::getTexCoordsIndex3(Int32 which) const
{
    return Inherited::getTexCoordsIndex3(_pointPntIndex);
}

inline 
Vec2f PointIterator::getTexCoords3(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex3(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords3()->getValue<Vec2f>(ind);
}

inline
Int32 PointIterator::getTexCoordsIndex4(Int32 which) const
{
    return Inherited::getTexCoordsIndex4(_pointPntIndex);
}

inline
Vec2f PointIterator::getTexCoords4(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex4(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords4()->getValue<Vec2f>(ind);
}

inline
Int32 PointIterator::getTexCoordsIndex5(Int32 which) const
{
    return Inherited::getTexCoordsIndex5(_pointPntIndex);
}

inline
Vec2f PointIterator::getTexCoords5(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex5(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords5()->getValue<Vec2f>(ind);
}

inline
Int32 PointIterator::getTexCoordsIndex6(Int32 which) const
{
    return Inherited::getTexCoordsIndex6(_pointPntIndex);
}

inline
Vec2f PointIterator::getTexCoords6(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex6(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords6()->getValue<Vec2f>(ind);
}

inline
Int32 PointIterator::getTexCoordsIndex7(Int32 which) const
{
    return Inherited::getTexCoordsIndex7(_pointPntIndex);
}

inline
Vec2f PointIterator::getTexCoords7(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex7(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords7()->getValue<Vec2f>(ind);
}


OSG_END_NAMESPACE

