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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

//#include "OSGSimpleGeometry.h"
#include "OSGGeoBuilder.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/* \class OSG::GeoBuilder
   \ingroup GrpSystemNodeCoresDrawablesGeometry
    
*/


// Default Typenames for the given attribute
char* GeoBuilder::_defaultPropTypes[Geometry::MaxAttribs] =
{
    "GeoPnt3fProperty",  // Positions            = 0
    "GeoVec3fProperty",  // 1 unused  
    "GeoVec3fProperty",  // NormalsIndex         = 2 
    "GeoColor4fProperty",// ColorsIndex          = 3 
    "GeoColor4fProperty",// SecondaryColorsIndex = 4 
    "GeoVec3fProperty",  // 5 unused  
    "GeoVec3fProperty",  // 6 unused  
    "GeoVec3fProperty",  // 7 unused  
    "GeoVec2fProperty",  // TexCoordsIndex       = 8 
    "GeoVec2fProperty",  // TexCoords1Index      = 9 
    "GeoVec2fProperty",  // TexCoords2Index      = 10 
    "GeoVec2fProperty",  // TexCoords3Index      = 11 
    "GeoVec2fProperty",  // TexCoords4Index      = 12 
    "GeoVec2fProperty",  // TexCoords5Index      = 13 
    "GeoVec2fProperty",  // TexCoords6Index      = 14 
    "GeoVec2fProperty",  // TexCoords7Index      = 15 
};

GeoBuilder::GeoBuilder(void) :
    _geo()
{
    reset();
}

GeoBuilder::~GeoBuilder()
{
    if(_geo != NullFC)
        subRef(_geo);
}

void GeoBuilder::reset(void)
{
    if(_geo != NullFC)
        subRef(_geo);
        
    _geo = Geometry::create();
    addRef(_geo);
    
    MaterialPtr mat = getDefaultMaterial();

    _geo->setMaterial(mat);

    _actLen = 0;
    _actType = -1; 
}

// Property Helper
GeoVectorPropertyPtr GeoBuilder::getProperty(UInt32 index)
{
    GeoVectorPropertyPtr att;
    
    if(index >= _geo->getProperties().size() ||
       _geo->getProperty(index) == NullFC)
    {
        att = cast_dynamic<GeoVectorPropertyPtr>(
                FieldContainerFactory::the()->createContainer(
                    _defaultPropTypes[index]));
                    
        _geo->setProperty(att, index);
    }
    else
    {
        att = _geo->getProperty(index);
    }
     
    return att;
}
    
// Finish the vertex. Make sure all Properties have the same number of 
// attributes and adjust the index, if necessary
UInt32 GeoBuilder::finishVertex(void)
{
    UInt32 possize = _geo->getProperty(Geometry::PositionsIndex)->size();
    
    for(UInt16 i = 1; i < _geo->getProperties().size(); ++i)
    {
        if(_geo->getProperty(i) != NullFC)
        {
            GeoVectorProperty::MaxTypeT val;
            
            _geo->getProperty(i)->getValue(val,
                        _geo->getProperty(i)->size() - 1);
                        
            for(UInt32 propsize = _geo->getProperty(i)->size();
                propsize < possize;
                ++propsize)
            {
                _geo->getProperty(i)->addValue(val);
            }
        }
    }
    
    // Are we in a begin/end loop? Then add current vertex to index
    if(_actType != -1)
        addIndex(possize - 1);
    
    _actLen++;
    return possize - 1;
}


void GeoBuilder::addType(Int32 type)
{
    if(_geo->getTypes() == NullFC)
    {
        GeoIntegralPropertyPtr t = GeoUInt8Property::create();
        _geo->setTypes(t);
       
    }
    _geo->getTypes()->addValue(type);
}

void GeoBuilder::addLength(UInt32 length)
{
    if(_geo->getLengths() == NullFC)
    {
        GeoIntegralPropertyPtr l = GeoUInt32Property::create();
        _geo->setLengths(l);
    }
    _geo->getLengths()->addValue(length);
}

void GeoBuilder::addIndex(UInt32 index)
{
    if(_geo->getIndices() == NullFC)
    {
        GeoIntegralPropertyPtr i = GeoUInt32Property::create();
        _geo->setIndices(i);
    }
    
    _geo->getIndices()->push_back(index);           
}

// Face Creation


void GeoBuilder::begin(UInt32 type)
{
    _actLen = 0;
    _actType = type;
    
    addType(type);
}

void GeoBuilder::end(void)
{
    addLength(_actLen);

    _actLen = 0;
    _actType = -1;   
}

void GeoBuilder::tri(UInt32 start)
{
    addType(GL_QUADS);
    addLength(3);

    addIndex(start    );
    addIndex(start + 1);
    addIndex(start + 2);
}

void GeoBuilder::tri(UInt32 i1, UInt32 i2, UInt32 i3)
{
    addType(GL_TRIANGLES);
    addLength(3);

    addIndex(i1);
    addIndex(i2);
    addIndex(i3);
}

void GeoBuilder::quad(UInt32 start)
{
    addType(GL_QUADS);
    addLength(4);

    addIndex(start    );
    addIndex(start + 1);
    addIndex(start + 2);
    addIndex(start + 3);
}

void GeoBuilder::quad(UInt32 i1, UInt32 i2, UInt32 i3, UInt32 i4)
{
    addType(GL_QUADS);
    addLength(4);

    addIndex(i1);
    addIndex(i2);
    addIndex(i3);
    addIndex(i4);
}

    
GeometryPtr GeoBuilder::getGeometry(void)
{
    return _geo;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id$";
    static Char8 cvsid_hpp       [] = OSGGEOBUILDER_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOBUILDER_INLINE_CVSID;
}

