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
Int32 EdgeIterator::getIndex(void) const
{
    return _edgeIndex;
}


/*! Return the length of the current face. 3 or 4, depending on the current 
    primitive.

*/
inline       
UInt32 EdgeIterator::getLength(void) const
{
	if ( getType() == GL_LINES )
		return 2;
	else
		return Inherited::getLength();
}


// Why isn't the following list of methods not implemented via macros like:
//
// #define getPROPERTYIndex(PROPERTY)                                          
// inline                                                                      
// Int32 EdgeIterator::get ## PROPERTY ## Index(Int32 which) const             
// {                                                                           
//     if ( getType() == GL_LINES )                                            
//         return Inherited::get ## PROPERTY ## Index(_edgePntIndex[which]);   
//     else                                                                    
//         return Inherited::get ## PROPERTY ## Index(which);                  
// }                                                                           
//
// #define getPROPERTY(PROPERTY,PROPERTY_TYPE)                         
// inline                                                              
// PROPERTY_TYPE EdgeIterator::get ## PROPERTY ## (Int32 which) const  
// {                                                                   
//     Int32 ind = get ## PROPERTY ## Index(which);                    
//                                                                     
//     return getGeometry()->get ## PROPERTY ## s()->getValue(ind);    
// }
//
// getPROPERTYIndex(Position)
// getPROPERTY(     Position,Pnt3f)
//
// It won't Work this way unfortunately since the TexCoordsIndex breaks 
// an implicit naming convention: "TexCoords3" and "TexCoordsIndex3" instead of
// "TexCoords3" and "TexCoords3Index" :-/


inline       
Int32 EdgeIterator::getPositionIndex(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getPositionIndex(_edgePntIndex[which]);
	else
        return Inherited::getPositionIndex(which);
}

inline
Pnt3f EdgeIterator::getPosition(Int32 which) const
{ 
	Int32 ind = getPositionIndex(which);

    return getGeometry()->getPositions()->getValue<Pnt3f>(ind);
}

inline       
Int32 EdgeIterator::getNormalIndex(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getNormalIndex(_edgePntIndex[which]);
	else
        return Inherited::getNormalIndex(which);
}

inline
Vec3f EdgeIterator::getNormal(Int32 which) const
{ 
	Int32 ind = getNormalIndex(which);

    return getGeometry()->getNormals()->getValue<Vec3f>(ind);
}

inline       
Int32 EdgeIterator::getColorIndex(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getColorIndex(_edgePntIndex[which]);
	else
        return Inherited::getColorIndex(which);
}

inline
Color3f EdgeIterator::getColor(Int32 which) const
{ 
	Int32 ind = getColorIndex(which);

    return getGeometry()->getColors()->getValue<Color3f>(ind);
}

inline       
Int32 EdgeIterator::getSecondaryColorIndex(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getSecondaryColorIndex(_edgePntIndex[which]);
	else
        return Inherited::getSecondaryColorIndex(which);
}

inline
Color3f EdgeIterator::getSecondaryColor(Int32 which) const
{ 
	Int32 ind = getSecondaryColorIndex(which);

    return getGeometry()->getSecondaryColors()->getValue<Color3f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getTexCoordsIndex(_edgePntIndex[which]);
	else
        return Inherited::getTexCoordsIndex(which);
}

inline
Vec2f EdgeIterator::getTexCoords(Int32 which) const
{ 
	Int32 ind = getTexCoordsIndex(which);

    return getGeometry()->getTexCoords()->getValue<Vec2f>(ind);
}


inline       
Int32 EdgeIterator::getTexCoordsIndex1(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getTexCoordsIndex1(_edgePntIndex[which]);
	else
        return Inherited::getTexCoordsIndex1(which);
}

inline
Vec2f EdgeIterator::getTexCoords1(Int32 which) const
{ 
	Int32 ind = getTexCoordsIndex1(which);

    return getGeometry()->getTexCoords1()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex2(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getTexCoordsIndex2(_edgePntIndex[which]);
	else
        return Inherited::getTexCoordsIndex2(which);
}

inline
Vec2f EdgeIterator::getTexCoords2(Int32 which) const
{ 
	Int32 ind = getTexCoordsIndex2(which);

    return getGeometry()->getTexCoords2()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex3(Int32 which) const
{
	if ( getType() == GL_LINES )
		return Inherited::getTexCoordsIndex3(_edgePntIndex[which]);
	else
        return Inherited::getTexCoordsIndex3(which);
}

inline
Vec2f EdgeIterator::getTexCoords3(Int32 which) const
{ 
	Int32 ind = getTexCoordsIndex3(which);

    return getGeometry()->getTexCoords3()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex4(Int32 which) const
{
    if ( getType() == GL_LINES )
        return Inherited::getTexCoordsIndex4(_edgePntIndex[which]);
    else
        return Inherited::getTexCoordsIndex4(which);
}

inline
Vec2f EdgeIterator::getTexCoords4(Int32 which) const
{ 
    Int32 ind = getTexCoordsIndex4(which);

    return getGeometry()->getTexCoords4()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex5(Int32 which) const
{
    if ( getType() == GL_LINES )
        return Inherited::getTexCoordsIndex5(_edgePntIndex[which]);
    else
        return Inherited::getTexCoordsIndex5(which);
}

inline
Vec2f EdgeIterator::getTexCoords5(Int32 which) const
{ 
    Int32 ind = getTexCoordsIndex5(which);

    return getGeometry()->getTexCoords5()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex6(Int32 which) const
{
    if ( getType() == GL_LINES )
        return Inherited::getTexCoordsIndex6(_edgePntIndex[which]);
    else
        return Inherited::getTexCoordsIndex6(which);
}

inline
Vec2f EdgeIterator::getTexCoords6(Int32 which) const
{ 
    Int32 ind = getTexCoordsIndex6(which);

    return getGeometry()->getTexCoords6()->getValue<Vec2f>(ind);
}

inline       
Int32 EdgeIterator::getTexCoordsIndex7(Int32 which) const
{
    if ( getType() == GL_LINES )
        return Inherited::getTexCoordsIndex7(_edgePntIndex[which]);
    else
        return Inherited::getTexCoordsIndex7(which);
}

inline
Vec2f EdgeIterator::getTexCoords7(Int32 which) const
{ 
    Int32 ind = getTexCoordsIndex7(which);

    return getGeometry()->getTexCoords7()->getValue<Vec2f>(ind);
}

OSG_END_NAMESPACE
