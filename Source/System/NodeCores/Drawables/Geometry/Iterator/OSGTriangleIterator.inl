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

OSG_BEGIN_NAMESPACE

/*! Return the index of the current vertex. 
*/

inline 
Int32 TriangleIterator::getIndex(Int32 which) const
{
    return Inherited::getIndex(_triPntIndex[which]);
}

/*! Return the index of the current face. The index runs from 0 to the
    number of triangles in the geometry. Its main use is as an input to 
    OSG::TriangleIterator::seek.
*/
inline       
Int32 TriangleIterator::getIndex(void) const
{
    return _triIndex;
}

inline 
Int32 TriangleIterator::getPropertyIndex(Int32 att, 
                                         Int32 which) const
{
    return Inherited::getPropertyIndex(att, _triPntIndex[which]);
}

template <class ReturnT> inline
ReturnT TriangleIterator::getPropertyValue(Int32 att,
                                           Int32 which) const
{
    Int32 ind = getPropertyIndex(att, which);

    return _props[att]->getValue<ReturnT>(ind);
}

inline       
Int32 TriangleIterator::getPositionIndex(Int32 which) const
{
    return Inherited::getPositionIndex(_triPntIndex[which]);
}

inline       
Pnt3f TriangleIterator::getPosition(Int32 which) const
{
    Int32 ind = getPositionIndex(which);
    
    return _props[Geometry::PositionsIndex]->getValue<Pnt3f>(ind);
}

inline 
Vec3f TriangleIterator::getNormal(Int32 att,
                                  Int32 which) const
{
    Int32 ind = getPropertyIndex(att, which);
    
    if(ind < 0)
        return Vec3f::Null;
        
    return _props[att]->getValue<Vec3f>(ind);
}

inline       
Int32 TriangleIterator::getNormalIndex(Int32 which) const
{
    return Inherited::getNormalIndex(_triPntIndex[which]);
}

inline 
Vec3f TriangleIterator::getNormal(Int32 which) const
{   
    Int32 ind = getNormalIndex(which);
    
    if(ind < 0)
        return Vec3f::Null;
        
    return _props[Geometry::NormalsIndex]->getValue<Vec3f>(ind);
}

inline       
Int32 TriangleIterator::getColorIndex(Int32 which) const
{
    return Inherited::getColorIndex(_triPntIndex[which]);
}

inline 
Color3f TriangleIterator::getColor(Int32 which) const
{   
    Int32 ind = getColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return _props[Geometry::ColorsIndex]->getValue<Color3f>(ind);
}

inline       
Int32 TriangleIterator::getSecondaryColorIndex(Int32 which) const
{
    return Inherited::getSecondaryColorIndex(_triPntIndex[which]);
}

inline 
Color3f TriangleIterator::getSecondaryColor(Int32 which) const
{   
    Int32 ind = getSecondaryColorIndex(which);
    
    if(ind < 0)
        return Color3f::Null;
        
    return _props[Geometry::SecondaryColorsIndex]->getValue<Color3f>(ind);
}

inline 
Vec2f TriangleIterator::getTexCoords(Int32 att,
                                     Int32 which) const
{
    Int32 ind = getPropertyIndex(att, which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[att]->getValue<Vec2f>(ind);
}

inline       
Int32 TriangleIterator::getTexCoordsIndex(Int32 which) const
{
    return Inherited::getTexCoordsIndex(_triPntIndex[which]);
}

inline 
Vec2f TriangleIterator::getTexCoords(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoordsIndex]->getValue<Vec2f>(ind);
}


inline       
Int32 TriangleIterator::getTexCoordsIndex1(Int32 which) const
{
    return Inherited::getTexCoordsIndex1(_triPntIndex[which]);
}

inline 
Vec2f TriangleIterator::getTexCoords1(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex1(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords1Index]->getValue<Vec2f>(ind);
}


inline       
Int32 TriangleIterator::getTexCoordsIndex2(Int32 which) const
{
    return Inherited::getTexCoordsIndex2(_triPntIndex[which]);
}

inline 
Vec2f TriangleIterator::getTexCoords2(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex2(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords2Index]->getValue<Vec2f>(ind);
}


inline       
Int32 TriangleIterator::getTexCoordsIndex3(Int32 which) const
{
    return Inherited::getTexCoordsIndex3(_triPntIndex[which]);
}

inline 
Vec2f TriangleIterator::getTexCoords3(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex3(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords3Index]->getValue<Vec2f>(ind);
}

inline
Int32 TriangleIterator::getTexCoordsIndex4(Int32 which) const
{
    return Inherited::getTexCoordsIndex4(_triPntIndex[which]);
}

inline
Vec2f TriangleIterator::getTexCoords4(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex4(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords4Index]->getValue<Vec2f>(ind);
}

inline
Int32 TriangleIterator::getTexCoordsIndex5(Int32 which) const
{
    return Inherited::getTexCoordsIndex5(_triPntIndex[which]);
}

inline
Vec2f TriangleIterator::getTexCoords5(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex5(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords5Index]->getValue<Vec2f>(ind);
}

inline
Int32 TriangleIterator::getTexCoordsIndex6(Int32 which) const
{
    return Inherited::getTexCoordsIndex6(_triPntIndex[which]);
}

inline
Vec2f TriangleIterator::getTexCoords6(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex6(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords6Index]->getValue<Vec2f>(ind);
}

inline
Int32 TriangleIterator::getTexCoordsIndex7(Int32 which) const
{
    return Inherited::getTexCoordsIndex7(_triPntIndex[which]);
}

inline
Vec2f TriangleIterator::getTexCoords7(Int32 which) const
{   
    Int32 ind = getTexCoordsIndex7(which);
    
    if(ind < 0)
        return Vec2f::Null;
        
    return _props[Geometry::TexCoords7Index]->getValue<Vec2f>(ind);
}

OSG_END_NAMESPACE

