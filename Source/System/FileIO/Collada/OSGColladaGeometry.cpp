/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#include "OSGColladaGeometry.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaSource.h"
#include "OSGGeometry.h"
#include "OSGGroup.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"

#include <dom/domGeometry.h>
#include <dom/domMesh.h>
#include <dom/domSource.h>
#include <dom/domLines.h>
#include <dom/domLinestrips.h>
#include <dom/domPolygons.h>
#include <dom/domPolylist.h>
#include <dom/domTriangles.h>
#include <dom/domTrifans.h>
#include <dom/domTristrips.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaGeometry::_regHelper(
    &ColladaGeometry::create, "geometry");


ColladaElementTransitPtr
ColladaGeometry::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaGeometry(elem, global));
}

void
ColladaGeometry::read(void)
{
    OSG_COLLADA_LOG(("ColladaGeometry::read\n"));

    domGeometryRef geo  = getDOMElementAs<domGeometry>();
    domMeshRef     mesh = geo->getMesh();

    if(mesh == NULL)
    {
        SWARNING << "ColladaGeometry::read: No <mesh>" << std::endl;
        return;
    }

    readMesh(mesh);
}

FieldContainer *
ColladaGeometry::process(ColladaElement *parent)
{
    SFATAL << "ColladaGeometry::process: <geometry> must be "
           << "instantiated to use."
           << std::endl;

    OSG_ASSERT(false);
}

Node *
ColladaGeometry::createInstance(ColladaInstanceElement *colInstElem)
{
    SWARNING << "ColladaGeometry::createInstance: NIY" << std::endl;

    // XXX TODO - reuse geometry if possible
    //          - handle <bind_material>

    NodeUnrecPtr    groupN = makeCoredNode<Group>();

    GeoStoreConstIt gsIt   = _geoStore.begin();
    GeoStoreConstIt gsEnd  = _geoStore.end  ();

    for(; gsIt != gsEnd; ++gsIt)
    {
        OSG_ASSERT(gsIt->_propStore.size() == gsIt->_indexStore.size());

        GeometryUnrecPtr geo  = Geometry::create();
        NodeUnrecPtr     geoN = makeNodeFor(geo);
        
        geo->setLengths(gsIt->_lengths);
        geo->setTypes  (gsIt->_types  );

        PropStoreConstIt  psIt  = gsIt->_propStore .begin();
        PropStoreConstIt  psEnd = gsIt->_propStore .end  ();
        IndexStoreConstIt isIt  = gsIt->_indexStore.begin();
        IndexStoreConstIt isEnd = gsIt->_indexStore.end  ();

        for(UInt32 i = 0; psIt != psEnd && isIt != isEnd; ++psIt, ++isIt, ++i)
        {
            if(psIt->_prop != NULL && *isIt != NULL)
            {
                geo->setProperty( psIt->_prop, i);
                geo->setIndex   (*isIt,        i);
            }
        }

        groupN->addChild(geoN);
    }

    editInstStore().push_back(groupN);

    return groupN;
}

ColladaGeometry::ColladaGeometry(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaGeometry::~ColladaGeometry(void)
{
}

void
ColladaGeometry::readMesh(domMesh *mesh)
{
    readSources(mesh);

    const domLines_Array &linesArray = mesh->getLines_array();

    for(UInt32 i = 0; i < linesArray.getCount(); ++i)
    {
        readLines(mesh, linesArray[i]);
    }

    const domLinestrips_Array &lineStripsArray = mesh->getLinestrips_array();

    for(UInt32 i = 0; i < lineStripsArray.getCount(); ++i)
    {
        readLineStrips(mesh, lineStripsArray[i]);
    }

    const domPolygons_Array &polygonsArray = mesh->getPolygons_array();

    for(UInt32 i = 0; i < polygonsArray.getCount(); ++i)
    {
        readPolygons(mesh, polygonsArray[i]);
    }

    const domPolylist_Array &polyListArray = mesh->getPolylist_array();

    for(UInt32 i = 0; i < polyListArray.getCount(); ++i)
    {
        readPolyList(mesh, polyListArray[i]);
    }

    const domTriangles_Array &triArray = mesh->getTriangles_array();
    
    for(UInt32 i = 0; i < triArray.getCount(); ++i)
    {
        readTriangles(mesh, triArray[i]);
    }

    const domTrifans_Array &triFansArray = mesh->getTrifans_array();

    for(UInt32 i = 0; i < triFansArray.getCount(); ++i)
    {
        readTriFans(mesh, triFansArray[i]);
    }

    const domTristrips_Array &triStripsArray = mesh->getTristrips_array();

    for(UInt32 i = 0; i < triStripsArray.getCount(); ++i)
    {
        readTriStrips(mesh, triStripsArray[i]);
    }
}

void
ColladaGeometry::readSources(domMesh *mesh)
{
    const domSource_Array &sources = mesh->getSource_array();

    for(UInt32 i = 0; i < sources.getCount(); ++i)
    {
        ColladaSourceRefPtr colSource =
            getUserDataAs<ColladaSource>(sources[i]);

        if(colSource == NULL)
        {
            colSource = dynamic_pointer_cast<ColladaSource>(
                ColladaElementFactory::the()->create(sources[i], getGlobal()));

            colSource->read();
        }

        _sourceMap.insert(
            SourceMap::value_type(sources[i]->getId(), colSource));
    }
}

void
ColladaGeometry::readLines(domMesh *mesh, domLines *lines)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readLines\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        lines              ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        lines->getMaterial(), idxStore);

    const domListOfUInts &pList   = lines->getP()->getValue();
    UInt32                currIdx = 0;
    UInt32                length  = 0;

    for(UInt32 i = 0; i < pList.getCount(); ++i)
    {
        idxStore[currIdx]->push_back(pList[i]);

        ++currIdx;

        if(currIdx == idxStore.size())
        {
            currIdx = 0;
            ++length;
        }
    }

    _geoStore[geoIdx]._types  ->push_back(GL_LINES);
    _geoStore[geoIdx]._lengths->push_back(length  );
}

void
ColladaGeometry::readLineStrips(domMesh *mesh, domLinestrips *lineStrips)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readLineStrips\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        lineStrips         ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        lineStrips->getMaterial(), idxStore);

    const domP_Array &pArray  = lineStrips->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            idxStore[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == idxStore.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_LINE_STRIP);
        _geoStore[geoIdx]._lengths->push_back(length       );

        length = 0;
    }
}

void
ColladaGeometry::readPolygons(domMesh *mesh, domPolygons *polygons)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readPolygons\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        polygons           ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        polygons->getMaterial(), idxStore);

    const domP_Array &pArray  = polygons->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            idxStore[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == idxStore.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
        _geoStore[geoIdx]._lengths->push_back(length    );

        length = 0;
    }

    const domPolygons::domPh_Array &phArray = polygons->getPh_array();
    currIdx = 0;
    length  = 0;

    for(UInt32 i = 0; i < phArray.getCount(); ++i)
    {
        // we only get the <p> elements (polygons) and skip the <h> elements
        // (holes)

        const domListOfUInts &pList = phArray[i]->getP()->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            idxStore[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == idxStore.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
        _geoStore[geoIdx]._lengths->push_back(length    );

        length = 0;

        if(phArray[i]->getH_array().getCount() > 0)
        {
            SWARNING << "ColladaGeometry::readPolygon: Ignoring ["
                     << phArray[i]->getH_array().getCount()
                     << "] holes in polygon." << std::endl;
        }
    }
}

void
ColladaGeometry::readPolyList(domMesh *mesh, domPolylist *polyList)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readPolyList\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        polyList           ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        polyList->getMaterial(), idxStore);

    const domListOfUInts &pList    = polyList->getP     ()->getValue();
    const domListOfUInts &vList    = polyList->getVcount()->getValue();
    UInt32                currIdx  = 0;
    bool                  useQuads = true;

    // check if all polys are quads
    for(UInt32 i = 0; i < vList.getCount(); ++i)
    {
        if(vList[i] != 4)
        {
            useQuads = false;
            break;
        }
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readPolyList: useQuads [%d]\n",
                     useQuads));

    if(useQuads == true)
    {
        for(UInt32 i = 0; i < 4 * vList.getCount(); ++i)
        {
            for(UInt32 k = 0; k < idxStore.size(); ++k)
            {
                idxStore[k]->push_back(pList[currIdx]);

                ++currIdx;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_QUADS            );
        _geoStore[geoIdx]._lengths->push_back(4 * vList.getCount());
    }
    else
    {
        for(UInt32 i = 0; i < vList.getCount(); ++i)
        {
            for(UInt32 j = 0; j < vList[i]; ++j)
            {
                for(UInt32 k = 0; k < idxStore.size(); ++k)
                {
                    idxStore[k]->push_back(pList[currIdx]);

                    ++currIdx;
                }
            }

            _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
            _geoStore[geoIdx]._lengths->push_back(vList[i]  );
        }
    }
}

void
ColladaGeometry::readTriangles(domMesh *mesh, domTriangles *triangles)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readTriangles\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        triangles          ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        triangles->getMaterial(), idxStore);

    const domListOfUInts &pList   = triangles->getP()->getValue();
    UInt32                currIdx = 0;
    UInt32                length  = 0;

    for(UInt32 i = 0; i < pList.getCount(); ++i)
    {
        idxStore[currIdx]->push_back(pList[i]);

        ++currIdx;

        if(currIdx == idxStore.size())
        {
            currIdx = 0;
            ++length;
        }
    }

    _geoStore[geoIdx]._types  ->push_back(GL_TRIANGLES);
    _geoStore[geoIdx]._lengths->push_back(length      );
}

void
ColladaGeometry::readTriFans(domMesh *mesh, domTrifans *triFans)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readTriFans\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        triFans            ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        triFans->getMaterial(), idxStore);

    const domP_Array &pArray  = triFans->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            idxStore[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == idxStore.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_TRIANGLE_FAN);
        _geoStore[geoIdx]._lengths->push_back(length         );

        length = 0;
    }
}

void
ColladaGeometry::readTriStrips(domMesh *mesh, domTristrips *triStrips)
{
    OSG_COLLADA_LOG(("ColladaGeometry::readTriStrips\n"));

    const domInputLocal_Array       &vertInputs =
        mesh->getVertices()->getInput_array();
    const domInputLocalOffset_Array &inputs     =
        triStrips          ->getInput_array();

    IndexStore idxStore;
    UInt32     geoIdx   = setupGeometry(vertInputs, inputs,
                                        triStrips->getMaterial(), idxStore);

    const domP_Array &pArray  = triStrips->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            idxStore[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == idxStore.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        _geoStore[geoIdx]._types  ->push_back(GL_TRIANGLE_STRIP);
        _geoStore[geoIdx]._lengths->push_back(length           );

        length = 0;
    }
}

UInt32
ColladaGeometry::mapSemantic(
    const std::string &semantic, UInt32 set, UInt32 geoIdx)
{
    UInt32 propIdx = Geometry::LastIndex;

    if(semantic == "POSITION")
    {
        propIdx = Geometry::PositionsIndex;
    }
    else if(semantic == "NORMAL")
    {
        propIdx = Geometry::NormalsIndex;
    }
    else if(semantic == "TEXCOORD")
    {
        if(set <= Geometry::TexCoords7Index)
        {
            propIdx = Geometry::TexCoordsIndex + set;
        }
        else
        {
            SWARNING << "ColladaGeometry::mapSemantic: TEXCOORD semantic has "
                     << "out of range set [" << set << "]"
                     << std::endl;
        }
    }
    else
    {
        SWARNING << "ColladaGeometry::mapSemantic: Unknown semantic ["
                 << semantic << "] set [" << set << "]" << std::endl;
    }

    OSG_COLLADA_LOG(("ColladaGeometry::mapSemantic: semantic [%s] "
                     "set [%d] -> propIdx [%d]\n",
                     semantic.c_str(), set, propIdx));

    return propIdx;
}

void
ColladaGeometry::setupProperty(
    UInt32 geoIdx, UInt32 propIdx, const std::string &semantic, UInt32 set,
    const std::string &sourceId, GeoIntegralProperty *idxProp              )
{
    // resize
    _geoStore[geoIdx]._propStore .resize(
        osgMax<UInt32>(_geoStore[geoIdx]._propStore .size(), propIdx + 1),
        PropInfo()                                                       );
    _geoStore[geoIdx]._indexStore.resize(
        osgMax<UInt32>(_geoStore[geoIdx]._indexStore.size(), propIdx + 1),
        NULL                                                             );

    // set index for the property
    _geoStore[geoIdx]._indexStore[propIdx]          = idxProp;

    // get property from source
    SourceMapConstIt   smIt = _sourceMap.find(sourceId);
    GeoVectorProperty *prop = NULL;

    if(smIt != _sourceMap.end())
    {
        prop = smIt->second->getProperty(semantic, set);
    }
    else
    {
        SFATAL << "ColladaGeometry::setupProperty: "
               << "No <source> found with id [" << sourceId << "]."
               << std::endl;
    }

    // set property
    _geoStore[geoIdx]._propStore[propIdx]._semantic = semantic;
    _geoStore[geoIdx]._propStore[propIdx]._set      = set;
    _geoStore[geoIdx]._propStore[propIdx]._prop     = prop;
}

UInt32
ColladaGeometry::setupGeometry(const domInputLocal_Array       &vertInputs,
                               const domInputLocalOffset_Array &inputs,
                               xsNCName                         matSymbol,
                               IndexStore                      &idxStore   )
{
    OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry\n"));

    UInt32 geoIdx = _geoStore.size();
    _geoStore.push_back(GeoInfo());

    if(matSymbol != NULL)
    {
        _geoStore[geoIdx]._matSymbol = matSymbol;
    }
    else
    {
        SWARNING << "ColladaGeometry::setupGeometry: "
                 << "Found empty material symbol." << std::endl;
    }

    for(UInt32 i = 0; i < inputs.getCount(); ++i)
    {
        std::string semantic = inputs[i]->getSemantic();
        UInt32      set      = inputs[i]->getSet     ();
        UInt32      offset   = inputs[i]->getOffset  ();
        std::string sourceId = inputs[i]->getSource  ().id();

        OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: input [%d] "
                         "semantic [%s] set [%d] offset [%d] - source [%s]\n",
                         i, semantic.c_str(), set, offset, sourceId.c_str()));

        if(semantic == "VERTEX")
        {
            // handle <input> tag with semantic "VERTEX"
            // by processing vertInputs

            // all vertInputs use the same index - with the offset from the
            // <input> with semantic == VERTEX
            if(offset >= idxStore.size() || idxStore[offset] == NULL)
            {
                OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                                 "new index property for offset [%d]\n",
                                 offset));

                // new index
                idxStore.resize(
                    osgMax<UInt32>(offset + 1, idxStore.size()), NULL);
                idxStore[offset] = GeoUInt32Property::create();
            }

            for(UInt32 j = 0; j < vertInputs.getCount(); ++j)
            {
                semantic = vertInputs[j]->getSemantic();
                sourceId = vertInputs[j]->getSource  ().id();

                OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: vertices [%d] "
                                 "semantic [%s] - source [%s]\n",
                                 j, semantic.c_str(), sourceId.c_str()));

                UInt32 propIdx = mapSemantic(semantic, 0, geoIdx);

                setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                              idxStore[offset]                         );
            }
        }
        else
        {
            // handle regular <input> tags

            if(offset >= idxStore.size() || idxStore[offset] == NULL)
            {
                OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                                 "new index property for offset [%d]\n",
                                 offset));

                // new index
                idxStore.resize(osgMax<UInt32>(offset + 1, idxStore.size()), NULL);
                idxStore[offset] = GeoUInt32Property::create();
            }

            UInt32 propIdx = mapSemantic(semantic, set, geoIdx);

            setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                          idxStore[offset]                         );
        }
    }

#ifdef OSG_DEBUG
    // check for holes in idxStore - which is not supported
    IndexStoreConstIt idxIt  = idxStore.begin();
    IndexStoreConstIt idxEnd = idxStore.end  ();

    for(UInt32 i = 0; idxIt != idxEnd; ++idxIt, ++i)
    {
        if(*idxIt == NULL)
        {
            SWARNING << "ColladaGeometry::setupGeometry: idxStore contains "
                     << "hole at [" << i << "]" << std::endl;
        }
    }
#endif

    _geoStore[geoIdx]._lengths = GeoUInt32Property::create();
    _geoStore[geoIdx]._types   = GeoUInt8Property ::create();

    return geoIdx;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
