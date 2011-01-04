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

#include "OSGPrimeMaterial.h"
#include "OSGGeoBuilder.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

// Default Typenames for the given attribute
const char* GeoBuilder::_defaultPropTypes[Geometry::MaxAttribs] =
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
}

void GeoBuilder::reset(void)
{
    _geo = NULL;

    _geo = Geometry::create();

    PrimeMaterial *mat = getDefaultMaterial();

    _geo->setMaterial(mat);

    _actLen = 0;
    _actType = -1;
}

// Property Helper
GeoVectorProperty *GeoBuilder::getProperty(UInt32 index)
{
    GeoVectorPropertyUnrecPtr att;

    if(index >= _geo->getMFProperties()->size() ||
       _geo->getProperty(index) == NULL)
    {
        att = dynamic_pointer_cast<GeoVectorProperty>(
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

    for(UInt16 i = 1; i < _geo->getMFProperties()->size(); ++i)
    {
        if(_geo->getProperty(i) != NULL)
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
        index(possize - 1);

    _actLen++;
    return possize - 1;
}


void GeoBuilder::addType(Int32 type)
{
    if(_geo->getTypes() == NULL)
    {
        GeoIntegralPropertyUnrecPtr t = GeoUInt8Property::create();
        _geo->setTypes(t);

    }
    _geo->getTypes()->addValue(type);
}

void GeoBuilder::addLength(UInt32 length)
{
    if(_geo->getLengths() == NULL)
    {
        GeoIntegralPropertyUnrecPtr l = GeoUInt32Property::create();
        _geo->setLengths(l);
    }
    _geo->getLengths()->addValue(length);
}

void GeoBuilder::index(UInt32 index)
{
    if(_actType == -1)
    {
        FWARNING(("GeoBuilder::index: called outside begin/end block!\n"));
        return;
    }

    if(_geo->getIndices() == NULL)
    {
        GeoIntegralPropertyUnrecPtr i = GeoUInt32Property::create();
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

void GeoBuilder::line(UInt32 start)
{
    begin(GL_LINES);

    index(start    );
    index(start + 1);

    _actLen += 2;

    end();
}

void GeoBuilder::line(UInt32 i1, UInt32 i2)
{
    begin(GL_LINES);

    index(i1);
    index(i2);

    _actLen += 2;

    end();
}

void GeoBuilder::tri(UInt32 start)
{
    begin(GL_TRIANGLES);

    index(start    );
    index(start + 1);
    index(start + 2);

    _actLen += 3;

    end();
}

void GeoBuilder::tri(UInt32 i1, UInt32 i2, UInt32 i3)
{
    begin(GL_TRIANGLES);

    index(i1);
    index(i2);
    index(i3);

    _actLen += 3;

    end();
}

void GeoBuilder::quad(UInt32 start)
{
    begin(GL_QUADS);

    index(start    );
    index(start + 1);
    index(start + 2);
    index(start + 3);

    _actLen += 4;

    end();
}

void GeoBuilder::quad(UInt32 i1, UInt32 i2, UInt32 i3, UInt32 i4)
{
    begin(GL_QUADS);

    index(i1);
    index(i2);
    index(i3);
    index(i4);

    _actLen += 4;

    end();
}


Geometry *GeoBuilder::getGeometry(void)
{
    return _geo;
}
