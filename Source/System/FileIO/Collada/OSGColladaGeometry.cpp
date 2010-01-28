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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaGeometry.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceEffect.h"
#include "OSGColladaNode.h"
#include "OSGColladaSource.h"
#include "OSGGroup.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGNameAttachment.h"
#include "OSGPrimeMaterial.h"

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

ColladaInstInfoTransitPtr
ColladaGeometry::ColladaGeometryInstInfo::create(
    ColladaNode *colInstParent, ColladaInstanceGeometry *colInst,
    Node        *parentN                                         )
{
    OSG_ASSERT(colInstParent != NULL);
    OSG_ASSERT(colInst       != NULL);

    return ColladaInstInfoTransitPtr(
        new ColladaGeometryInstInfo(colInstParent, colInst, parentN));
}

void
ColladaGeometry::ColladaGeometryInstInfo::process(void)
{
    Node *geoInstN = dynamic_cast<Node *>(
        getColInst()->getTargetElem()->createInstance(this));

    getParentNode()->addChild(geoInstN);
}

ColladaGeometry::ColladaGeometryInstInfo::ColladaGeometryInstInfo(
    ColladaNode *colInstParent, ColladaInstanceGeometry *colInst,
    Node        *parentN                                         )

    : Inherited(colInstParent, colInst)
    , _parentN (parentN               )
{
}

ColladaGeometry::ColladaGeometryInstInfo::~ColladaGeometryInstInfo(void)
{
}

/*---------------------------------------------------------------------------*/

ColladaGeometry::PropInfo::PropInfo(void)
    : _semantic()
    , _set     ()
    , _prop    (NULL)
{
}

ColladaGeometry::PropInfo::PropInfo(const PropInfo &source)
    : _semantic(source._semantic)
    , _set     (source._set)
    , _prop    (source._prop)
{
}

/*---------------------------------------------------------------------------*/

ColladaElementRegistrationHelper ColladaGeometry::_regHelper(
    &ColladaGeometry::create, "geometry");

ColladaElementTransitPtr
ColladaGeometry::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaGeometry(elem, global));
}

void
ColladaGeometry::read(ColladaElement *colElemParent)
{
    domGeometryRef geometry = getDOMElementAs<domGeometry>();
    domMeshRef     mesh     = geometry->getMesh();

    OSG_COLLADA_LOG(("ColladaGeometry::read id [%s]\n",
                     geometry->getId()));

    if(mesh == NULL)
    {
        SWARNING << "ColladaGeometry::read: No <mesh>" << std::endl;
        return;
    }

    readMesh(mesh);
}

Node *
ColladaGeometry::createInstance(ColladaInstInfo *colInstInfo)
{
    typedef ColladaInstanceGeometry::MaterialMap        MaterialMap;
    typedef ColladaInstanceGeometry::MaterialMapConstIt MaterialMapConstIt;

    domGeometryRef geometry = getDOMElementAs<domGeometry>();
    NodeUnrecPtr   groupN   = makeCoredNode<Group>();

    OSG_COLLADA_LOG(("ColladaGeometry::createInstance id [%s]\n",
                     geometry->getId()));

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
       geometry->getName()                                   != NULL   )
    {
        setName(groupN, geometry->getName());
    }

    ColladaInstanceGeometryRefPtr  colInstGeo =
        dynamic_cast<ColladaInstanceGeometry *>(colInstInfo->getColInst());
    const MaterialMap             &matMap     =
        colInstGeo->getMaterialMap();

    // iterate over all parts of geometry
    GeoStoreIt gsIt   = _geoStore.begin();
    GeoStoreIt gsEnd  = _geoStore.end  ();

    for(; gsIt != gsEnd; ++gsIt)
    {
        OSG_ASSERT(gsIt->_propStore.size() == gsIt->_indexStore.size());

        // find the material associated with the geometry's material symbol
        MaterialMapConstIt mmIt       = matMap.find(gsIt->_matSymbol);
        std::string        matTarget;

        if(mmIt != matMap.end())
        {
            matTarget = mmIt->second->getTarget();
        }

        // check if the geometry was already used with that material

        GeometryUnrecPtr   geo      = NULL;
        InstanceMapConstIt instIt   = gsIt->_instMap.find(matTarget);

        if(instIt != gsIt->_instMap.end())
        {
            // reuse geometry

            geo = dynamic_pointer_cast<Geometry>(
                getInstStore()[instIt->second]);

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryUsed)->inc();
        }
        else
        {
            // create new geometry

            geo = Geometry::create();

            getGlobal()->getStatCollector()->getElem(
                ColladaGlobal::statNGeometryCreated)->inc();

            geo->setLengths(gsIt->_lengths);
            geo->setTypes  (gsIt->_types  );

            handleBindMaterial(*gsIt, geo, colInstGeo);

            // record the instantiation of the geometry with the
            // material for reuse
            gsIt->_instMap.insert(
                InstanceMap::value_type(matTarget, getInstStore().size()));

            editInstStore().push_back(geo);
        }

        NodeUnrecPtr geoN = makeNodeFor(geo);

        groupN->addChild(geoN);
    }

    // store the generated group node
    editInstStore().push_back(groupN);

    return groupN;
}

ColladaGeometry::ColladaGeometry(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global)
    , _sourceMap()
    , _geoStore ()
{
}

ColladaGeometry::~ColladaGeometry(void)
{
}

void
ColladaGeometry::readMesh(domMesh *mesh)
{
    readSources(mesh->getSource_array());

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
ColladaGeometry::readSources(const domSource_Array &sources)
{
    for(UInt32 i = 0; i < sources.getCount(); ++i)
    {
        ColladaSourceRefPtr colSource =
            getUserDataAs<ColladaSource>(sources[i]);

        if(colSource == NULL)
        {
            colSource = dynamic_pointer_cast<ColladaSource>(
                ColladaElementFactory::the()->create(sources[i], getGlobal()));

            colSource->read(this);
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

    OSG_COLLADA_LOG(("ColladaGeometry::readLines: material symbol [%s] "
                     "vertices [%d]\n",
                     (lines->getMaterial() != NULL ? lines->getMaterial() : ""),
                     length));

    _geoStore[geoIdx]._types  ->push_back(GL_LINES);
    _geoStore[geoIdx]._lengths->push_back(length  );

    // remove empty geometry
    if(length == 0)
    {
        SWARNING << "ColladaGeometry::readLines: Empty <lines> with material ["
                 << (lines->getMaterial() != NULL ? lines->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
    }
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
    UInt32            verts   = 0;

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

        // only add non-empty line strip
        if(length > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_LINE_STRIP);
            _geoStore[geoIdx]._lengths->push_back(length       );
        }

        verts  += length;
        length =  0;
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readLineStrips: material symbol [%s] "
                     "vertices [%d] strips [%d]\n",
                     (lineStrips->getMaterial() != NULL ?
                      lineStrips->getMaterial() : ""), verts,
                     _geoStore[geoIdx]._lengths->size()));

    // remove empty geometry
    if(verts == 0)
    {
        SWARNING << "ColladaGeometry::readLineStrips: Empty <linestrips> "
                 << "with material ["
                 << (lineStrips->getMaterial() != NULL ?
                     lineStrips->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
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
    UInt32            verts   = 0;

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

        // only add non-empty polygon
        if(length > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
            _geoStore[geoIdx]._lengths->push_back(length    );
        }

        verts  += length;
        length =  0;
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

        // only add non-empty polygon
        if(length > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
            _geoStore[geoIdx]._lengths->push_back(length    );
        }

        verts  += length;
        length =  0;

        if(phArray[i]->getH_array().getCount() > 0)
        {
            SWARNING << "ColladaGeometry::readPolygon: Ignoring ["
                     << phArray[i]->getH_array().getCount()
                     << "] holes in polygon." << std::endl;
        }
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readPolygons: material symbol [%s] "
                     "vertices [%d] polygons [%d]\n",
                     (polygons->getMaterial() != NULL ?
                      polygons->getMaterial() : ""), verts,
                     _geoStore[geoIdx]._lengths->size()));

    // remove empty geometry
    if(verts == 0)
    {
        SWARNING << "ColladaGeometry::readPolygons: Empty <polygons> "
                 << "with material ["
                 << (polygons->getMaterial() != NULL ?
                     polygons->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
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
    UInt32                verts    = 0;
    UInt32                prims    = 0;
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

        // only add non-empty quads
        if(vList.getCount() > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_QUADS            );
            _geoStore[geoIdx]._lengths->push_back(4 * vList.getCount());
        }

        verts += 4 * vList.getCount();
        prims +=     vList.getCount();
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

            // only add non-empty polygons
            if(vList[i] > 0)
            {
                _geoStore[geoIdx]._types  ->push_back(GL_POLYGON);
                _geoStore[geoIdx]._lengths->push_back(vList[i]  );
            }

            verts += vList[i];
            prims += 1;
        }
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readPolyList: material symbol [%s] "
                     "vertices [%d] %s [%d]\n",
                     (polyList->getMaterial() != NULL ?
                      polyList->getMaterial() : ""),
                     verts,
                     (useQuads == true ? "quads" : "polygons"), prims));

    // remove empty geometry
    if(verts == 0)
    {
        SWARNING << "ColladaGeometry::readPolyList: Empty <polylist> "
                 << "with material ["
                 << (polyList->getMaterial() != NULL ?
                     polyList->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
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

    OSG_COLLADA_LOG(("ColladaGeometry::readTriangles: material symbol [%s] "
                     "vertices [%d] triangles [%d]\n",
                     (triangles->getMaterial() != NULL ?
                      triangles->getMaterial() : ""),
                     length, length/3));

    if(length == 0)
    {
        SWARNING << "ColladaGeometry::readTriangles: Empty <triangles> "
                 << "with material ["
                 << (triangles->getMaterial() != NULL ?
                     triangles->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
    }
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
    UInt32            verts   = 0;

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

        // only add non-empty tri fans
        if(length > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_TRIANGLE_FAN);
            _geoStore[geoIdx]._lengths->push_back(length         );
        }

        verts  += length;
        length =  0;
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readTriFans: material symbol [%s] "
                     "vertices [%d] fans [%d]\n",
                     (triFans->getMaterial() != NULL ?
                      triFans->getMaterial() : ""), verts,
                     _geoStore[geoIdx]._lengths->size()));

    // remove empty geometry
    if(verts == 0)
    {
        SWARNING << "ColladaGeometry::readTriFans: Empty <trifans> "
                 << "with material ["
                 << (triFans->getMaterial() != NULL ?
                     triFans->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
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
    UInt32            verts   = 0;

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

        // only add non-empty tri strip
        if(length > 0)
        {
            _geoStore[geoIdx]._types  ->push_back(GL_TRIANGLE_STRIP);
            _geoStore[geoIdx]._lengths->push_back(length           );
        }

        verts  += length;
        length =  0;
    }

    OSG_COLLADA_LOG(("ColladaGeometry::readTriStrips: material symbol [%s] "
                     "vertices [%d] strips [%d]\n",
                     (triStrips->getMaterial() != NULL ?
                      triStrips->getMaterial() : ""), verts,
                     _geoStore[geoIdx]._lengths->size()));

    // remove empty geometry
    if(verts == 0)
    {
        SWARNING << "ColladaGeometry::readTriStrips: Empty <tristrips> "
                 << "with material ["
                 << (triStrips->getMaterial() != NULL ?
                     triStrips->getMaterial() : "")
                 << "]." << std::endl;

        _geoStore.erase(_geoStore.begin() + geoIdx);
    }
}

UInt32
ColladaGeometry::mapSemantic(
    const std::string &semantic, UInt32 set, UInt32 geoIdx)
{
    UInt32 propIdx = Geometry::MaxAttribs;

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
        OSG_COLLADA_LOG(("ColladaGeometry::mapSemantic: Unknown semantic [%s] "
                         "set [%d]\n", semantic.c_str(), set));
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
    _geoStore[geoIdx]._indexStore[propIdx] = idxProp;

    // get property from source
    SourceMapConstIt   smIt = _sourceMap.find(sourceId);
    GeoVectorProperty *prop = NULL;

    if(smIt != _sourceMap.end())
    {
        prop = smIt->second->getProperty(semantic);
    }
    else
    {
        SFATAL << "ColladaGeometry::setupProperty: "
               << "No <source> with id [" << sourceId << "] found."
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

    typedef std::vector<UInt32>             UnhandledStore;
    typedef UnhandledStore::const_iterator  UnhandledStoreConstIt;

    Int32          vertInputIndex       = -1;  // <input> with sem "VERTEX"
    UnhandledStore unhandledVertInputs;
    UnhandledStore unhandledInputs;

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
            // by processing vertInputs, i.e. the <vertices> tag

            vertInputIndex = i;

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

                if(propIdx == Geometry::MaxAttribs)
                {
                    unhandledVertInputs.push_back(j);
                }
                else
                {
                    setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                                  idxStore[offset]                         );
                }
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

            if(propIdx == Geometry::MaxAttribs)
            {
                unhandledInputs.push_back(i);
            }
            else
            {
                setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                              idxStore[offset]                         );
            }
        }
    }

    // some <inputs> could not be handled above because their
    // semantic was not recognized.
    // after everything else is set put them into free attribute
    // slots, starting at Geometry::TexCoordsIndex

    UnhandledStoreConstIt uhIt  = unhandledVertInputs.begin();
    UnhandledStoreConstIt uhEnd = unhandledVertInputs.end  ();

    for(; uhIt != uhEnd; ++uhIt)
    {
        std::string semantic = vertInputs[*uhIt         ]->getSemantic();
        UInt32      set      = inputs    [vertInputIndex]->getSet     ();
        UInt32      offset   = inputs    [vertInputIndex]->getOffset  ();
        std::string sourceId = vertInputs[*uhIt         ]->getSource  ().id();

        UInt32 propIdx = findFreePropertyIndex(geoIdx);

        OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: unhandled vertex "
                         " <input> [%d] semantic [%s] set [%d] offset [%d] - "
                         "source [%s] mapped to propIdx [%d]\n",
                         *uhIt, semantic.c_str(), set, offset, sourceId.c_str(),
                         propIdx));

        setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                      idxStore[offset]                         );
    }

    uhIt  = unhandledInputs.begin();
    uhEnd = unhandledInputs.end  ();

    for(; uhIt != uhEnd; ++uhIt)
    {
        std::string semantic = inputs[*uhIt]->getSemantic();
        UInt32      set      = inputs[*uhIt]->getSet     ();
        UInt32      offset   = inputs[*uhIt]->getOffset  ();
        std::string sourceId = inputs[*uhIt]->getSource  ().id();

        UInt32 propIdx = findFreePropertyIndex(geoIdx);

        OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: unhandled <input> "
                         "[%d] semantic [%s] set [%d] offset [%d] - "
                         "source [%s] mapped to propIdx [%d]\n",
                         *uhIt, semantic.c_str(), set, offset, sourceId.c_str(),
                         propIdx));

        setupProperty(geoIdx, propIdx, semantic, set, sourceId,
                      idxStore[offset]                         );
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

void
ColladaGeometry::handleBindMaterial(
    const GeoInfo &geoInfo, Geometry *geo, ColladaInstanceGeometry *colInstGeo)
{
    typedef ColladaInstanceGeometry::MaterialMap        MaterialMap;
    typedef ColladaInstanceGeometry::MaterialMapConstIt MaterialMapConstIt;

    const MaterialMap       &matMap        = colInstGeo->getMaterialMap();
    MaterialMapConstIt       mmIt          = matMap.find(geoInfo._matSymbol);
    Material                *material      = NULL;
    ColladaInstanceMaterial *colInstMat    = NULL;
    ColladaInstanceEffect   *colInstEffect = NULL;

    if(mmIt != matMap.end())
    {
        colInstMat = mmIt->second;

        OSG_ASSERT(colInstMat                  != NULL);
        OSG_ASSERT(colInstMat->getTargetElem() != NULL);

        ColladaInstInfoRefPtr colInstInfo =
            ColladaMaterial::ColladaMaterialInstInfo::create(this, colInstMat);

        material      =
            colInstMat->getTargetElem()->createInstance(colInstInfo);
        colInstEffect = colInstMat->getInstanceEffect();
    }
    else
    {
        SWARNING << "ColladaGeometry::handleBindMaterial: No material found "
                 << "for symbol [" << geoInfo._matSymbol << "]."
                 << std::endl;

        geo->setMaterial(getDefaultMaterial());
        return;
    }

    const BindStore       &bindStore       = colInstMat->getBindStore      ();
    const BindVertexStore &bindVertexStore = colInstMat->getBindVertexStore();

    PropStoreConstIt       psIt            = geoInfo._propStore .begin();
    PropStoreConstIt       psEnd           = geoInfo._propStore .end  ();
    IndexStoreConstIt      isIt            = geoInfo._indexStore.begin();
    IndexStoreConstIt      isEnd           = geoInfo._indexStore.end  ();

    // for every property in geoInfo we need to check if it gets remapped by a
    // <bind> or <bind_vertex_input>

    for(UInt32 i = 0; psIt != psEnd && isIt != isEnd; ++psIt, ++isIt, ++i)
    {
        if(psIt->_prop == NULL || *isIt == NULL)
            continue;

        bool   handledProperty  = false;
        UInt32 bindOffset       = 0;
        UInt32 bindVertexOffset = 0;

        const BindInfo       *bi  = findBind      (bindStore,
                                                   psIt->_semantic, bindOffset );
        const BindVertexInfo *bvi = findBindVertex(bindVertexStore,
                                                   psIt->_semantic, psIt->_set,
                                                   bindVertexOffset            );

        // there may be multiple consumers for a property, keep looping
        // until no more consumers are found
        while(bi != NULL || bvi != NULL)
        {
            UInt32 mappedProp = i;

            if(bi != NULL && bvi != NULL)
            {
                // is it a problem if there is a <bind> AND a
                // <bind_vertex_input> for the same property ??

                SWARNING << "ColladaGeometry::handleBindMaterial: "
                         << "Found <bind> AND <bind_vertex_input> for "
                         << "semantic [" << bi->semantic
                         << "] target/inSemantic [" << bi->target << "/"
                         << bvi->inSemantic << "] inSet [" << bvi->inSet
                         << "]" << std::endl;
            }

            if(bi != NULL)
            {
                if(colInstEffect->findTC(bi->target, mappedProp) == true)
                {
                    OSG_COLLADA_LOG(("ColladaGeometry::handleBindMaterial: "
                                     "Resolved <bind> semantic [%s] "
                                     "target [%s] to property [%d]\n",
                                     bi->semantic.c_str(), bi->target.c_str(),
                                     mappedProp));

                    geo->setProperty( psIt->_prop, mappedProp);
                    geo->setIndex   (*isIt,        mappedProp);

                    handledProperty = true;
                }
                else
                {
                    SWARNING << "ColladaGeometry::handleBindMaterial: "
                             << "Failed to resolve <bind> semantic ["
                             << bi->semantic << "] target [" << bi->target
                             << "]." << std::endl;
                }
            }
            else if(bvi != NULL)
            {
                if(colInstEffect->findTC(bvi->semantic, mappedProp) == true)
                {
                    OSG_COLLADA_LOG(("ColladaGeometry::handleBindMaterial: "
                                     "Resolved <bind_vertex_input> "
                                     "inSemantic [%s] inSet [%d] semantic [%s] "
                                     "to property [%d]\n",
                                     bvi->inSemantic.c_str(), bvi->inSet,
                                     bvi->semantic.c_str(), mappedProp));

                    geo->setProperty( psIt->_prop, mappedProp);
                    geo->setIndex   (*isIt,        mappedProp);
                    handledProperty = true;
                }
                else
                {
                    SWARNING << "ColladaGeometry::handleBindMaterial: "
                             << "Failed to resolve <bind_vertex_input> "
                             << "inSemantic ["
                             << bvi->inSemantic << "] inSet [" << bvi->inSet
                             << "] semantic [" << bvi->semantic
                             << "]." << std::endl;
                }
            }

            // find next consumers if any
            ++bindOffset;
            ++bindVertexOffset;

            bi  = findBind      (bindStore,       psIt->_semantic,
                                 bindOffset                       );
            bvi = findBindVertex(bindVertexStore, psIt->_semantic,
                                 psIt->_set,      bindVertexOffset);
        }

        // if the property is not remapped by <bind> or <bind_vertex_input>
        // we just put it at the location it received at read time
        // this is for properties that are not of interest to the material
        // directly (e.g. positions, normals)
        if(handledProperty == false)
        {
            OSG_COLLADA_LOG(("ColladaGeometry::handleBindMaterial: "
                             "Setting property [%d] (semantic [%s] set [%d]) "
                             "without <bind>/<bind_vertex_input> mapping.\n",
                             i, psIt->_semantic.c_str(), psIt->_set));

            geo->setProperty( psIt->_prop, i);
            geo->setIndex   (*isIt,        i);
        }
    }

    if(material != NULL)
    {
        geo->setMaterial(material);
    }
    else
    {
        SWARNING << "ColladaGeometry::handleBindMaterial: No material created "
                 << "for symbol [" << geoInfo._matSymbol << "]."
                 << std::endl;

        geo->setMaterial(getDefaultMaterial());
    }
}

/*! Returns a &lt;bind&gt; (actually a BindInfo built from a &lt;bind&gt;)
    that has the given \a semantic. The search starts at the given \a offset to
    allow multiple &lt;bind&gt; with the same semantic to be found.
 */
const ColladaGeometry::BindInfo *
ColladaGeometry::findBind(
    const BindStore &store, const std::string &semantic, UInt32 &offset)
{
    const BindInfo *retVal = NULL;

    for(UInt32 i = offset; i < store.size(); ++i)
    {
        if(store[i].semantic == semantic)
        {
            retVal = &store[i];
            offset = i;
            break;
        }
    }

    return retVal;
}

/*! Returns a &lt;bind_vertex_input&gt; (actually a BindVertexInfo built from
    a &lt;bind_vertex_input&gt;) that has the given \a inSemantic and \a inSet.
    The search starts at the given \a offset to allow
    multiple &lt;bind_vertex_input&gt; with the same inSemantic/inSet to be
    found. 
 */
const ColladaGeometry::BindVertexInfo *
ColladaGeometry::findBindVertex(
    const BindVertexStore &store, const std::string &inSemantic,
    UInt32                 inSet, UInt32            &offset     )
{
    const BindVertexInfo *retVal = NULL;

    for(UInt32 i = offset; i < store.size(); ++i)
    {
        if(store[i].inSemantic == inSemantic &&
           store[i].inSet      == inSet        )
        {
            retVal = &store[i];
            offset = i;
            break;
        }
    }

    return retVal;
}
UInt16
ColladaGeometry::findFreePropertyIndex(UInt32 geoIdx)
{
    // find an unused property
    UInt16 retVal = osgMax<UInt16>(_geoStore[geoIdx]._propStore.size(),
                                   Geometry::TexCoordsIndex            );

    for(UInt16 i = Geometry::TexCoordsIndex;
        i < _geoStore[geoIdx]._propStore.size(); ++i)
    {
        if(_geoStore[geoIdx]._propStore[i]._prop == NULL)
        {
            retVal = i;
            break;
        }
    }

    return retVal;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
