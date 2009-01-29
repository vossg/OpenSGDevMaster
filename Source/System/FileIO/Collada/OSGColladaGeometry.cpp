/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include <OSGColladaGeometry.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaGlobal.h>
#include <OSGColladaSource.h>

#include <OSGColladaGeoInputAttachment.h>


#include <dom/domGeometry.h>
#include <dom/domLines.h>
#include <dom/domLinestrips.h>
#include <dom/domPolygons.h>
#include <dom/domPolylist.h>
#include <dom/domTriangles.h>
#include <dom/domTrifans.h>
#include <dom/domTristrips.h>

OSG_BEGIN_NAMESPACE

void ColladaGeometry::read(void)
{
    OSG_COLLADA_LOG(("ColladaGeometry::read:\n"));

    domGeometryRef geo  = getDOMElementAs<domGeometry>();
    domMeshRef     mesh = geo->getMesh();

    if(mesh == NULL)
    {
        FWARNING(("ColladaGeometry::read: Geometry has no <mesh>.\n"));
        return;
    }

    const domInputLocal_Array &vertInputs   =
        mesh->getVertices()->getInput_array();
    const domLines_Array      &lines       = mesh->getLines_array();

    for(UInt32 i = 0, linesCount = lines.getCount(); i < linesCount; ++i)
    {
        handleLines(vertInputs, lines[i]);
    }

    const domLinestrips_Array &linestrips  = mesh->getLinestrips_array();

    for(UInt32 i = 0, lsCount = linestrips.getCount(); i < lsCount; ++i)
    {
        handleLinestrips(vertInputs, linestrips[i]);
    }

    const domPolygons_Array   &polys       = mesh->getPolygons_array();

    for(UInt32 i = 0, polysCount = polys.getCount(); i < polysCount; ++i)
    {
        handlePolygons(vertInputs, polys[i]);
    }

    const domPolylist_Array   &polylist    = mesh->getPolylist_array();

    for(UInt32 i = 0, plCount = polylist.getCount(); i < plCount; ++i)
    {
        handlePolylist(vertInputs, polylist[i]);
    }

    const domTriangles_Array  &tris        = mesh->getTriangles_array();

    for(UInt32 i = 0, trisCount = tris.getCount(); i < trisCount; ++i)
    {
        handleTriangles(vertInputs, tris[i]);
    }

    const domTrifans_Array    &trifans     = mesh->getTrifans_array();

    for(UInt32 i = 0, tfCount = trifans.getCount(); i < tfCount; ++i)
    {
        handleTrifans(vertInputs, trifans[i]);
    }

    const domTristrips_Array  &tristrips   = mesh->getTristrips_array();

    for(UInt32 i = 0, tsCount = tristrips.getCount(); i < tsCount; ++i)
    {
        handleTristrips(vertInputs, tristrips[i]);
    }
}

ColladaGeometry::ColladaGeometry(domGeometry *geo, ColladaGlobal *global)
    : Inherited(geo, global)
{
}

ColladaGeometry::~ColladaGeometry(void)
{
    GeoMapIt geoIt  = _geosMap.begin();
    GeoMapIt geoEnd = _geosMap.end  ();

    for(; geoIt != geoEnd; ++geoIt)
        delete geoIt->second;
}


void ColladaGeometry::setupGeometry(
          xsNCName                    matName,
    const domInputLocal_Array        &vertInputs,
    const domInputLocalOffset_Array  &inputs,
          GeoUInt32PropertyUnrecPtr  &lengthsOut,
          GeoUInt8PropertyUnrecPtr   &typesOut,
          IndexVec                   &indexVecOut )
{
    OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry:\n"));

    daeURI      sourceURI(getGlobal()->getDAE());

    std::string geoRef;
    std::string matRef;

    lengthsOut = NULL;
    typesOut   = NULL;

    if(matName != NULL)
    {
        geoRef = matName;
        matRef = matName;
    }

    for(UInt32 i = 0; i < inputs.getCount(); ++i)
    {
        sourceURI = inputs[i]->getSource();

        OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                         "offset [%u] semantic [%s] source.id [%s] source.uri [%s]\n",
                         inputs[i]->getOffset(),
                         inputs[i]->getSemantic(),
                         sourceURI.getID(),
                         sourceURI.getURI()));

        geoRef += sourceURI.getID();
    }

    OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: geoRef [%s] matRef [%s]\n",
                     geoRef.c_str(), matRef.c_str()));

    GeoMapIt      currGeoIt = _geosMap.find(geoRef);
    GeometryInfo *geoInfo   = NULL;

    if(currGeoIt == _geosMap.end())
    {
        geoInfo = new GeometryInfo;

        geoInfo->geo = Geometry::create();

        _geosMap  [geoRef] = geoInfo;
        _geosByMat[matRef].push_back(geoInfo);

        for(UInt32 i = 0; i < inputs.getCount(); ++i)
        {
            UInt32 propIdx = mapSemanticToGeoProp(inputs[i]->getSemantic());

            // index and vector data for this input
            GeoUInt32PropertyUnrecPtr iProp = GeoUInt32Property::create();
            GeoVectorPropertyUnrecPtr vProp = NULL;

            if(propIdx == 0xFFFE)
            {
                // handle <input semantic=VERTEX ...>

                for(UInt32 j = 0; j < vertInputs.getCount(); ++j)
                {
                    UInt32 viPropIdx =
                        mapSemanticToGeoProp(vertInputs[j]->getSemantic());

                    geoInfo->geo->setIndex(iProp, viPropIdx);

                    OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                                     "added vertices prop: "
                                     "semantic [%s] viPropIdx [%d]\n",
                                     vertInputs[j]->getSemantic(), viPropIdx));

                    vProp = fillVecProp(viPropIdx, vertInputs[j]->getSource());

                    geoInfo->geo->setProperty(vProp, viPropIdx);
                }
            }
            else if(propIdx == 0xFFFF || propIdx == Geometry::TexCoordsIndex)
            {
                // handle <input semantic=TEXCOORD ...> and
                //        <input semantic=??? ...>

                SourcePropIndexMapIt propIt = geoInfo->sourcePropIndexMap.find(
                    inputs[i]->getSource().getID());

                if(propIt == geoInfo->sourcePropIndexMap.end())
                {
                    vProp = fillVecProp(propIdx, inputs[i]->getSource());
                }
            }
            else
            {
                // handle <input semantic=POSITION ...> and
                //        <input semantic=NORMAL ...>

                geoInfo->geo->setIndex(iProp, propIdx);

                OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                                 "added prop: semantic [%s] propIdx [%d]\n",
                                 inputs[i]->getSemantic(), propIdx));

                vProp = fillVecProp(propIdx, inputs[i]->getSource());

                geoInfo->geo->setProperty(vProp, propIdx);
            }
            
            // store the property/propIndex pair in the map
            SourcePropIndexMapIt propIt = geoInfo->sourcePropIndexMap.find(
                inputs[i]->getSource().getID());
            
            if(propIt == geoInfo->sourcePropIndexMap.end () &&
               iProp  != NULL                               &&
               vProp  != NULL                                 )
            {
                PropIndexPair newPair;
                newPair.first  = vProp;
                newPair.second = iProp;
                
                geoInfo->sourcePropIndexMap[
                    inputs[i]->getSource().getID()            ] = newPair;
                geoInfo->semanticPropIndexMap[
                    SemanticSetPair(inputs[i]->getSemantic(),
                                    inputs[i]->getSet     () )] = newPair;
                
                OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                                 "Store prop/index [%s] [%u] [%s]:\n"
                                 "  [%p] : [%s]\n"
                                 "  [%p] : [%s]\n",
                                 inputs[i]->getSemantic(),
                                 inputs[i]->getSet     (),
                                 inputs[i]->getSource  ().getID(),
                                 newPair.first.get(),
                                 newPair.first->getType().getCName(),
                                 newPair.second.get(),
                                 newPair.second->getType().getCName() ));
            }
        }

        lengthsOut = GeoUInt32Property::create();
        typesOut   = GeoUInt8Property ::create();

        geoInfo->geo->setLengths(lengthsOut);
        geoInfo->geo->setTypes  (typesOut  );
    }
    else
    {
        geoInfo = currGeoIt->second;

        lengthsOut =
            static_cast<GeoUInt32Property *>(geoInfo->geo->getLengths());
        typesOut   =
            static_cast<GeoUInt8Property  *>(geoInfo->geo->getTypes  ());
    }

    ColladaGeoInputAttachmentUnrecPtr inputAtt =
        ColladaGeoInputAttachment::create();
    geoInfo->geo->addAttachment(inputAtt);
    
    for(UInt32 i = 0; i < inputs.getCount(); ++i)
    {
        if(indexVecOut.size() <= inputs[i]->getOffset())
            indexVecOut.resize(inputs[i]->getOffset() + 1);

        UInt32 propIdx = mapSemanticToGeoProp(inputs[i]->getSemantic(), true);

        if(propIdx != Geometry::TexCoordsIndex)
        {
            indexVecOut[inputs[i]->getOffset()] =
                static_cast<GeoUInt32Property *>(
                    geoInfo->geo->getIndex(propIdx));
        }
        else
        {
            SourcePropIndexMapIt propIt = geoInfo->sourcePropIndexMap.find(
                inputs[i]->getSource().getID());

            if(propIt != geoInfo->sourcePropIndexMap.end())
            {
                indexVecOut[inputs[i]->getOffset()] =
                    static_pointer_cast<GeoUInt32Property>(
                        propIt->second.second);
            }
        }
        
        // store all inputs in an attachment to the geometry
        SourcePropIndexMapIt propIt = geoInfo->sourcePropIndexMap.find(
            inputs[i]->getSource().getID());
        
        if(propIt != geoInfo->sourcePropIndexMap.end())
        {
            OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                             "inputAtt [%s] [%d] [%p] [%p]\n",
                             inputs[i]->getSemantic(),
                             inputs[i]->getSet     (),
                             propIt->second.first.get(),
                             propIt->second.second.get() ));
            
            inputAtt->editMFSemantics  ()->push_back(inputs[i]->getSemantic());
            inputAtt->editMFSets       ()->push_back(inputs[i]->getSet     ());
            inputAtt->editMFProperties ()->push_back(propIt->second.first    );
            inputAtt->editMFPropIndices()->push_back(propIt->second.second   );
        }
    }

#ifndef OSG_COLLADA_SILENT
    for(UInt32 i = 0; i < indexVecOut.size(); ++i)
    {
        OSG_COLLADA_LOG(("ColladaGeometry::setupGeometry: "
                         "indexVecOut i [%d] : [%p]\n",
                         i, &(*(indexVecOut[i]))       ));
    }
#endif
}





void ColladaGeometry::handleLines(
    const domInputLocal_Array &vertInputs, domLines *lines)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handleLines:\n"));

    const domInputLocalOffset_Array &inputs = lines->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(lines->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                   );

    const domListOfUInts &pList   = lines->getP()->getValue();
    UInt32                currIdx = 0;
    UInt32                length  = 0;

    for(UInt32 i = 0; i < pList.getCount(); ++i)
    {
        iProps[currIdx]->push_back(pList[i]);

        ++currIdx;

        if(currIdx == iProps.size())
        {
            currIdx = 0;
            ++length;
        }
    }

    types  ->push_back(GL_LINES);
    lengths->push_back(length  );
}

void ColladaGeometry::handleLinestrips(
    const domInputLocal_Array &vertInputs, domLinestrips *linestrips)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handleLinestrips:\n"));

    const domInputLocalOffset_Array &inputs = linestrips->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(linestrips->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                        );

    const domP_Array &pArray  = linestrips->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            iProps[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == iProps.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        types  ->push_back(GL_LINE_STRIP);
        lengths->push_back(length       );

        length = 0;
    }
}

void ColladaGeometry::handlePolygons(
    const domInputLocal_Array &vertInputs, domPolygons *polygons)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handlePolygons:\n"));

    const domInputLocalOffset_Array &inputs = polygons->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(polygons->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                      );

    const domP_Array &pArray  = polygons->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            iProps[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == iProps.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        types  ->push_back(GL_POLYGON);
        lengths->push_back(length    );

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
            iProps[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == iProps.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        types  ->push_back(GL_POLYGON);
        lengths->push_back(length    );

        length = 0;
    }
}

void ColladaGeometry::handlePolylist(
    const domInputLocal_Array &vertInputs, domPolylist *polylist)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handlePolylist:\n"));

    const domInputLocalOffset_Array &inputs = polylist->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(polylist->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                      );

    const domListOfUInts &pList   = polylist->getP     ()->getValue();
    const domListOfUInts &vList   = polylist->getVcount()->getValue();
    UInt32                currIdx = 0;
    UInt32                length  = 0;

    for(UInt32 i = 0; i < vList.getCount(); ++i)
    {
        for(UInt32 j = 0; j < vList[i]; ++j)
        {
            for(UInt32 k = 0; k < iProps.size(); ++k)
            {
                iProps[k]->push_back(pList[currIdx]);

                ++currIdx;
            }
        }

        types  ->push_back(GL_POLYGON);
        lengths->push_back(vList[i]  );
    }
}

void ColladaGeometry::handleTriangles(
    const domInputLocal_Array &vertInputs, domTriangles *triangles)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handleTriangles:\n"));

    const domInputLocalOffset_Array &inputs = triangles->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(triangles->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                       );

    const domListOfUInts &pList   = triangles->getP()->getValue();
    UInt32                currIdx = 0;
    UInt32                length  = 0;

    for(UInt32 i = 0; i < pList.getCount(); ++i)
    {
        iProps[currIdx]->push_back(pList[i]);

        ++currIdx;

        if(currIdx == iProps.size())
        {
            currIdx = 0;
            ++length;
        }
    }

    types  ->push_back(GL_TRIANGLES);
    lengths->push_back(length      );
}

void ColladaGeometry::handleTrifans(
    const domInputLocal_Array &vertInputs, domTrifans *trifans)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handleTrifans:\n"));

    const domInputLocalOffset_Array &inputs = trifans->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(trifans->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                     );

    const domP_Array &pArray  = trifans->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            iProps[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == iProps.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        types  ->push_back(GL_TRIANGLE_FAN);
        lengths->push_back(length         );

        length = 0;
    }
}

void ColladaGeometry::handleTristrips(
    const domInputLocal_Array &vertInputs, domTristrips *tristrips)
{
    OSG_COLLADA_LOG(("ColladaGeometry::handleTristrips:\n"));

    const domInputLocalOffset_Array &inputs = tristrips->getInput_array();

    GeoUInt32PropertyUnrecPtr lengths = NULL;
    GeoUInt8PropertyUnrecPtr  types   = NULL;
    IndexVec                  iProps;

    setupGeometry(tristrips->getMaterial(), vertInputs, inputs,
                  lengths, types, iProps                       );

    const domP_Array &pArray  = tristrips->getP_array();
    UInt32            currIdx = 0;
    UInt32            length  = 0;

    for(UInt32 i = 0; i < pArray.getCount(); ++i)
    {
        const domListOfUInts &pList = pArray[i]->getValue();

        for(UInt32 j = 0; j < pList.getCount(); ++j)
        {
            iProps[currIdx]->push_back(pList[j]);

            ++currIdx;

            if(currIdx == iProps.size())
            {
                currIdx = 0;
                ++length;
            }
        }

        types  ->push_back(GL_TRIANGLE_FAN);
        lengths->push_back(length         );

        length = 0;
    }
}

UInt32 ColladaGeometry::mapSemanticToGeoProp(
    const std::string &semantic, bool vertexAsPos)
{
    UInt32 returnValue = 0xFFFF;

    if(semantic == "VERTEX")
    {
        if(vertexAsPos == true)
        {
            returnValue = Geometry::PositionsIndex;
        }
        else
        {
            returnValue = 0xFFFE;
        }
    }
    else if(semantic == "POSITION")
    {
        returnValue = Geometry::PositionsIndex;
    }
    else if(semantic == "NORMAL")
    {
        returnValue = Geometry::NormalsIndex;
    }
    else if(semantic == "TEXCOORD")
    {
        returnValue = Geometry::TexCoordsIndex;
    }

    return returnValue;
}

GeoVectorProperty *ColladaGeometry::fillVecProp(
    UInt32 propIdx, daeURI sourceURI)
{
    GeoVectorProperty *returnValue = NULL;

    OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: URI [%s]\n",
                     sourceURI.getURI()));

    daeElementRef elem = sourceURI.getElement();

    OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: elem [%s] [%s]\n",
                     elem->getTypeName(), elem->getElementName()));

    domVerticesRef vert   = daeSafeCast<domVertices>(elem);
    domSourceRef   source = daeSafeCast<domSource  >(elem);

    if(vert != NULL)
    {
        const domInputLocal_Array &vertInputs = vert->getInput_array();

        OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: vertInputs [%d]\n",
                         vertInputs.getCount()));

        daeURI sourceDesc = vertInputs[0]->getSource();

        elem = sourceDesc.getElement();

        OSG_COLLADA_LOG(("ColladaGeoemtry::fillVecProp: elem [%s] [%s]\n",
                         elem->getTypeName(), elem->getElementName()));

        source = daeSafeCast<domSource>(elem);
    }

    if(source != NULL)
    {
        OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: source\n"));

        ColladaSourceRefPtr colSource = getUserDataAs<ColladaSource>(source);

        if(colSource == NULL)
        {
            colSource = ColladaSource::create(source, getGlobal());
            addElement(colSource);

            colSource->read();
        }

        if(propIdx == Geometry::NormalsIndex)
        {
            OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: reading as Vec3f\n"));

            returnValue = colSource->getAsVec3fProp();
        }
        else if(propIdx == Geometry::PositionsIndex)
        {
            OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: reading as Pnt3f\n"));

            returnValue = colSource->getAsPnt3fProp();
        }
        else if(propIdx == Geometry::TexCoordsIndex)
        {
            OSG_COLLADA_LOG(("ColladaGeometry::fillVecProp: reading as Vec2f\n"));

            returnValue = colSource->getAsVec2fProp();
        }
    }

    return returnValue;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
