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

inline       
Int32 FaceIterator::getIndex(void) const
{
    return _faceIndex;
}


/*! Return the length of the current face. 3 or 4, depending on the current 
    primitive.

*/
inline       
UInt32 FaceIterator::getLength(void) const
{
    return _facePntIndex[3] == -1 ? 3 : 4;
}

inline       
Int32 FaceIterator::getPositionIndex(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getPositionIndex(_facePntIndex[which]);
    else 
        return -1;
}

inline        
Pnt3f FaceIterator::getPosition(Int32 which) const { Int32 ind =
getPositionIndex(which);

    if(ind < 0)
        return Pnt3f::Null;
    
    return getGeometry()->getPositions()->getValue<Pnt3f>(ind);
}

inline       
Int32 FaceIterator::getNormalIndex(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getNormalIndex(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Vec3f FaceIterator::getNormal(Int32 which) const
{   
    Int32 ind = getNormalIndex(which);
    
    if(ind < 0)
        return Vec3f::Null;
        
    return getGeometry()->getNormals()->getValue<Vec3f>(ind);
}

inline       
Int32 FaceIterator::getColorIndex(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getColorIndex(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Color3f FaceIterator::getColor(Int32 which) const
{   
    Int32 ind = getColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return getGeometry()->getColors()->getValue<Color3f>(ind);
}

inline       
Int32 FaceIterator::getSecondaryColorIndex(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getSecondaryColorIndex(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Color3f FaceIterator::getSecondaryColor(Int32 which) const
{   
    Int32 ind = getSecondaryColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return getGeometry()->getSecondaryColors()->getValue<Color3f>(ind);
}

inline       
Int32 FaceIterator::getTexCoordsIndex(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getTexCoordsIndex(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Vec2f FaceIterator::getTexCoords(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords()->getValue<Vec2f>(ind);
}


inline       
Int32 FaceIterator::getTexCoordsIndex1(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getTexCoordsIndex1(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Vec2f FaceIterator::getTexCoords1(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex1(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords1()->getValue<Vec2f>(ind);
}

inline       
Int32 FaceIterator::getTexCoordsIndex2(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getTexCoordsIndex2(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Vec2f FaceIterator::getTexCoords2(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex2(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords2()->getValue<Vec2f>(ind);
}

inline       
Int32 FaceIterator::getTexCoordsIndex3(Int32 which) const
{
    if(_facePntIndex[which] >= 0)
        return Inherited::getTexCoordsIndex3(_facePntIndex[which]);
    else 
        return -1;
}

inline 
Vec2f FaceIterator::getTexCoords3(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex3(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return getGeometry()->getTexCoords3()->getValue<Vec2f>(ind);
}

OSG_END_NAMESPACE
