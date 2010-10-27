/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#include "OSGOgreMeshReader.h"
#include "OSGOgreLog.h"

#include "OSGGeometry.h"
#include "OSGGroup.h"
#include "OSGNode.h"
#include "OSGPrimeMaterial.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

const std::string OgreMeshReader::_versionString("[MeshSerializer_v1.8]");

/* explicit */
OgreMeshReader::OgreMeshReader(std::istream& is)
    : Inherited(is),
      _rootN   ()
{
    _rootN = makeCoredNode<Group>();
}

/* virtual */
OgreMeshReader::~OgreMeshReader(void)
{
}

Node*
OgreMeshReader::getRoot(void)
{
    return _rootN;
}

void
OgreMeshReader::read(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::read\n"));

    UInt16 headerId = readUInt16(_is);

    if(headerId == CHUNK_HEADER)
    {
        std::string version = readString(_is);

        if(version == _versionString)
        {
            readChunkHeader(_is);
            readMesh();
        }
        else
        {
            SWARNING << "OgreMeshReader::read: Unsupported version '"
                     << version << "'." << std::endl;
        }
    }
    else
    {
        SWARNING << "OgreMeshReader::read: Unrecognized file header."
                 << std::endl;
    }
}

void
OgreMeshReader::readMesh(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMesh\n"));

    bool skelAnim = readBool(_is);
    bool stop     = false;

    Int16              boneIdxVE    = -1;
    Int16              boneWeightVE = -1;
    VertexElementStore sharedVertexElements;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_SUBMESH:
            readSubMesh(sharedVertexElements);
            break;

        case CHUNK_GEOMETRY:
            readGeometry(sharedVertexElements);
            break;

        case CHUNK_MESH_SKELETON_LINK:
            readMeshSkeletonLink();
            break;

        case CHUNK_MESH_BONE_ASSIGNMENT:
            readMeshBoneAssignment(sharedVertexElements, boneIdxVE, boneWeightVE);
            break;

        case CHUNK_MESH_LOD:
            readMeshLOD();
            break;

        case CHUNK_MESH_BOUNDS:
            readMeshBounds();
            break;

        case CHUNK_SUBMESH_NAME_TABLE:
            readSubMeshNameTable();
            break;

        case CHUNK_EDGE_LISTS:
            readEdgeLists();
            break;

        case CHUNK_POSES:
            readPoses();
            break;

        case CHUNK_ANIMATIONS:
            readAnimations();
            break;

        case CHUNK_TABLE_EXTREMES:
            readTableExtremes();
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readMesh: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        };

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readSubMesh(VertexElementStore &sharedVertexElements)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMesh\n"));

    std::string matName    = readString(_is);
    bool        sharedVert = readBool  (_is);
    UInt32      idxCount   = readUInt32(_is);
    bool        idx32Bit   = readBool  (_is);

    OSG_OGRE_LOG(("OgreMeshReader::readSubMesh: matName '%s' sharedVert '%d' "
                  "idxCount '%d' idx32Bit '%d'\n",
                  matName.c_str(), sharedVert, idxCount, idx32Bit));

    GeoIntegralPropertyUnrecPtr propIdx;

    if(idx32Bit == true)
    {
        GeoUInt32PropertyUnrecPtr pi = GeoUInt32Property::create();
        pi->resize(idxCount);

        _is.read(reinterpret_cast<Char8 *>(&pi->editField().front()),
                 idxCount * sizeof(UInt32));

        propIdx = pi;
    }
    else
    {
        GeoUInt16PropertyUnrecPtr pi = GeoUInt16Property::create();
        pi->resize(idxCount);

        _is.read(reinterpret_cast<Char8 *>(&pi->editField().front()),
                 idxCount * sizeof(UInt16));

        propIdx = pi;
    }

    Int16              boneIdxVE    = -1;
    Int16              boneWeightVE = -1;
    VertexElementStore vertexElements;

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_GEOMETRY:
            readGeometry(vertexElements);
            break;

        case CHUNK_SUBMESH_OPERATION:
            readSubMeshOperation();
            break;

        case CHUNK_SUBMESH_BONE_ASSIGNMENT:
            readSubMeshBoneAssignment(vertexElements, boneIdxVE, boneWeightVE);
            break;

        case CHUNK_SUBMESH_TEXTURE_ALIAS:
            readSubMeshTextureAlias();
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readSubMesh: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        };

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }

    if(sharedVert == true)
    {
        constructSubMesh(sharedVertexElements, propIdx);
    }
    else
    {
        constructSubMesh(vertexElements, propIdx);
    }
}

void
OgreMeshReader::readSubMeshOperation(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshOperation\n"));

    UInt16 opType = readUInt16(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshOperation: opType '%d'\n", opType));

    // XXX TODO
}

void
OgreMeshReader::readSubMeshBoneAssignment(VertexElementStore &vertexElements,
                                          Int16              &boneIdxVE,
                                          Int16              &boneWeightVE   )
{
    //OSG_OGRE_LOG(("OgreMeshReader::readSubMeshBoneAssignment\n"));

    UInt32 vertIdx = readUInt32(_is);
    UInt16 boneIdx = readUInt16(_is);
    Real32 weight  = readReal32(_is);

    GeoVec4fPropertyUnrecPtr boneIdxProp;
    GeoVec4fPropertyUnrecPtr boneWeightProp;

    if(boneIdxVE < 0)
    {
        boneIdxProp = GeoVec4fProperty::create();

        VertexElement vElem;

        vElem.bufferIdx = 0;
        vElem.type      = VET_FLOAT4;
        vElem.semantic  = VES_BLEND_INDICES;
        vElem.offset    = 0;
        vElem.index     = 0;
        vElem.prop      = boneIdxProp;

        boneIdxVE       = vertexElements.size();

        vertexElements.push_back(vElem);
    }

    if(boneWeightVE < 0)
    {
        boneWeightProp = GeoVec4fProperty::create();

        VertexElement vElem;

        vElem.bufferIdx = 0;
        vElem.type      = VET_FLOAT4;
        vElem.semantic  = VES_BLEND_WEIGHTS;
        vElem.offset    = 0;
        vElem.index     = 0;
        vElem.prop      = boneWeightProp;

        boneWeightVE    = vertexElements.size();

        vertexElements.push_back(vElem);
    }

    boneIdxProp    = dynamic_pointer_cast<GeoVec4fProperty>(vertexElements[boneIdxVE   ].prop);
    boneWeightProp = dynamic_pointer_cast<GeoVec4fProperty >(vertexElements[boneWeightVE].prop);

    GeoVec4fProperty::StoredFieldType* boneIdxF    = boneIdxProp   ->editFieldPtr();
    GeoVec4fProperty::StoredFieldType* boneWeightF = boneWeightProp->editFieldPtr();

    if(vertIdx >= boneIdxF->size())
        boneIdxF->resize(vertIdx + 1);

    if(vertIdx >= boneWeightF->size())
        boneWeightF->resize(vertIdx + 1);

    bool found = false;

    for(UInt16 i = 0; i < 4; ++i)
    {
        if((*boneIdxF)[vertIdx][i] == 0.f)
        {
            (*boneIdxF   )[vertIdx][i] = boneIdx;
            (*boneWeightF)[vertIdx][i] = weight;

            found = true;
            break;
        }
    }

    if(found == false)
    {
        SWARNING << "OgreMeshReader::readSubMeshBoneAssignment: "
                 << "vertex '" << vertIdx << "' influenced by more than 4 "
                 << "bones." << std::endl;
    }
}

void
OgreMeshReader::readSubMeshTextureAlias(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshTextureAlias\n"));

    std::string aliasName   = readString(_is);
    std::string textureName = readString(_is);

    // XXX TODO
}

void
OgreMeshReader::readGeometry(VertexElementStore &vertexElements)
{
    OSG_OGRE_LOG(("OgreMeshReader::readGeometry\n"));

    UInt32          vertCount = readUInt32(_is);
    BufferVertexMap bufferMap;

    OSG_OGRE_LOG(("OgreMeshReader::readGeometry: vertCount '%d'\n", vertCount));

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_GEOMETRY_VERTEX_DECLARATION:
            readGeometryVertexDeclaration(vertexElements, bufferMap);
            break;

        case CHUNK_GEOMETRY_VERTEX_BUFFER:
            readGeometryVertexBuffer(vertCount, vertexElements, bufferMap);
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readGeometry: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        };

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readGeometryVertexDeclaration(VertexElementStore &vertexElements,
                                              BufferVertexMap    &bufferMap      )
{
    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexDeclaration\n"));

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_GEOMETRY_VERTEX_ELEMENT:
            readGeometryVertexElement(vertexElements, bufferMap);
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexDeclaration: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readGeometryVertexElement(VertexElementStore &vertexElements,
                                          BufferVertexMap    &bufferMap      )
{
    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexElement\n"));

    VertexElement vElem;

    vElem.bufferIdx = readUInt16(_is);
    vElem.type      = static_cast<VertexElementType    >(readUInt16(_is));
    vElem.semantic  = static_cast<VertexElementSemantic>(readUInt16(_is));
    vElem.offset    = readUInt16(_is);
    vElem.index     = readUInt16(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexElement: "
                  "bufferIdx '%d' type '%d' semantic '%d' offset '%d' index '%d'\n",
                  vElem.bufferIdx, vElem.type, vElem.semantic,
                  vElem.offset, vElem.index));

    if(vElem.semantic == VES_POSITION)
    {
        switch(vElem.type)
        {
        case VET_FLOAT3:
            vElem.prop = GeoPnt3fProperty::create();
            break;

        case VET_FLOAT4:
            vElem.prop = GeoPnt4fProperty::create();
            break;

        default:
            SWARNING << "OgreMeshReader::readGeometryVertexElement: "
                     << "semantic 'VES_POSITION' only supports types "
                     << "'VET_FLOAT3' and 'VET_FLOAT4'"
                     << std::endl;
            break;
        }
    }
    else if(vElem.semantic == VES_DIFFUSE  ||
            vElem.semantic == VES_SPECULAR   )
    {
        SWARNING << "OgreMeshReader::readGeometryVertexElement: "
                 << "semantic 'VES_DIFFUSE'/'VES_SPECULAR'  NIY"
                 << std::endl;
    }
    else
    {
        switch(vElem.type)
        {
        case VET_FLOAT2:
            vElem.prop = GeoVec2fProperty::create();
            break;

        case VET_FLOAT3:
            vElem.prop = GeoVec3fProperty::create();
            break;

        case VET_FLOAT4:
            vElem.prop = GeoVec4fProperty::create();
            break;

        default:
            SWARNING << "OgreMeshReader::readGeometryVertexElement: "
                     << "semantic '" << vElem.semantic
                     << "' does not support type '" << vElem.type << "'"
                     << std::endl;
            break;
        }
    }

    if(bufferMap.size() <= vElem.bufferIdx)
    {
        bufferMap.resize(vElem.bufferIdx + 1);
    }

    bufferMap[vElem.bufferIdx].push_back(vertexElements.size());

    vertexElements.push_back(vElem);
}

void
OgreMeshReader::readGeometryVertexBuffer(UInt32              vertCount,
                                         VertexElementStore &vertexElements,
                                         BufferVertexMap    &bufferMap      )
{
    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexBuffer\n"));

    UInt16 bindIdx  = readUInt16(_is);
    UInt16 vertSize = readUInt16(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexBuffer: "
                  "bindIdx '%d' vertSize '%d'\n", bindIdx, vertSize));

    readChunkHeader(_is);

    if(_header.chunkId == CHUNK_GEOMETRY_VERTEX_BUFFER_DATA)
    {
        readGeometryVertexBufferData(vertCount,      bindIdx,
                                     vertexElements, bufferMap);
    }
    else
    {
        skip(_is, -_chunkHeaderSize);
    }
}

void
OgreMeshReader::readGeometryVertexBufferData(UInt32              vertCount,
                                             UInt16              bindIdx,
                                             VertexElementStore &vertexElements,
                                             BufferVertexMap    &bufferMap      )
{
    OSG_OGRE_LOG(("OgreMeshReader::readGeometryVertexBufferData\n"));

    for(UInt32 i = 0; i < vertCount; ++i)
    {
        for(UInt32 j = 0; j < bufferMap[bindIdx].size(); ++j)
        {
            UInt32 veIdx = bufferMap[bindIdx][j];

            switch(vertexElements[veIdx].type)
            {
            case VET_FLOAT1:
            {
                Vec1f v(readReal32(_is));
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_FLOAT2:
            {
                Vec2f v(readReal32(_is),
                        readReal32(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_FLOAT3:
            {
                Vec3f v(readReal32(_is),
                        readReal32(_is),
                        readReal32(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_FLOAT4:
            {
                Vec4f v(readReal32(_is),
                        readReal32(_is),
                        readReal32(_is),
                        readReal32(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_COLOUR:
                break;

            case VET_SHORT1:
            {
                Vec1s v(readInt16(_is));
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_SHORT2:
            {
                Vec2s v(readInt16(_is),
                        readInt16(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_SHORT3:
            {
                Vec3s v(readInt16(_is),
                        readInt16(_is),
                        readInt16(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_SHORT4:
            {
                Vec4s v(readInt16(_is),
                        readInt16(_is),
                        readInt16(_is),
                        readInt16(_is) );
                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_UBYTE4:
                readUInt32(_is);
                break;

            case VET_COLOUR_ARGB:
                break;

            case VET_COLOUR_ABGR:
                break;
            }
        }
    }
}

void
OgreMeshReader::readMeshSkeletonLink(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshSkeletonLink\n"));

    std::string skelName = readString(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readMeshSkeletonLink: skelName '%s'\n",
                  skelName.c_str()));

    // XXX TODO
}

void
OgreMeshReader::readMeshBoneAssignment(VertexElementStore &vertexElements,
                                       Int16              &boneIdxVE,
                                       Int16              &boneWeightVE   )
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshBoneAssignment\n"));

    readSubMeshBoneAssignment(vertexElements, boneIdxVE, boneWeightVE);
}

void
OgreMeshReader::readMeshLOD(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshLOD\n"));

    std::string strategyName = readString(_is);
    UInt16      levelCount   = readUInt16(_is);
    bool        manual       = readBool  (_is);

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_MESH_LOD_USAGE:
            readMeshLODUsage();
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readMeshLOD: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readMeshLODUsage(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshLODUsage\n"));

    Real32 lodValue = readReal32(_is);

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_MESH_LOD_MANUAL:
            readMeshLODManual();
            break;

        case CHUNK_MESH_LOD_GENERATED:
            readMeshLODGenerated();
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readMeshLODUsage: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readMeshLODManual(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshLODManual\n"));

    std::string meshName = readString(_is);

    // XXX TODO
}

void
OgreMeshReader::readMeshLODGenerated(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshLODGenerated\n"));

    UInt32 idxCount = readUInt32(_is);
    bool   idx32Bit = readBool  (_is);

    if(idx32Bit == true)
    {
        // XXX TODO read index
        skip(_is, idxCount * sizeof(UInt32));
    }
    else
    {
        // XXX TODO read index
        skip(_is, idxCount * sizeof(UInt16));
    }

    // XXX TODO
}

void
OgreMeshReader::readMeshBounds(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshBounds\n"));

    Real32 minX   = readReal32(_is);
    Real32 minY   = readReal32(_is);
    Real32 minZ   = readReal32(_is);

    Real32 maxX   = readReal32(_is);
    Real32 maxY   = readReal32(_is);
    Real32 maxZ   = readReal32(_is);

    Real32 radius = readReal32(_is);

    // XXX TODO
}

void
OgreMeshReader::readSubMeshNameTable(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTable\n"));

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_SUBMESH_NAME_TABLE_ELEMENT:
            readSubMeshNameTableElement();
            break;

        default:
            OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTable: Unknown chunkId '0x%x'\n",
                          _header.chunkId));
            stop = true;
            break;
        }

        if(stop == true)
        {
            skip(_is, -_chunkHeaderSize);
            break;
        }
    }
}

void
OgreMeshReader::readSubMeshNameTableElement(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTableElement\n"));

    UInt16      meshIdx  = readUInt16(_is);
    std::string meshName = readString(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTableElement: "
                  "meshIdx '%d' meshName '%s'\n", meshIdx, meshName.c_str()));

    // XXX TODO
}

void
OgreMeshReader::readEdgeLists(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readEdgeLists\n"));

    // XXX TODO
    skip(_is, _header.chunkSize - _chunkHeaderSize);
}

void
OgreMeshReader::readPoses(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readPoses\n"));

    // XXX TODO
     skip(_is, _header.chunkSize - _chunkHeaderSize);
}

void
OgreMeshReader::readAnimations(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readAnimations\n"));

    // XXX TODO
    skip(_is, _header.chunkSize - _chunkHeaderSize);
}

void
OgreMeshReader::readTableExtremes(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readTableExtremes\n"));

    // XXX TODO
    skip(_is, _header.chunkSize - _chunkHeaderSize);
}

void
OgreMeshReader::constructSubMesh(VertexElementStore  &vertexElements,
                                 GeoIntegralProperty *propIdx        )
{
    OSG_OGRE_LOG(("OgreMeshReader::constructSubMesh\n"));

    GeometryUnrecPtr geo     = Geometry::create();
    NodeUnrecPtr     geoN    = makeNodeFor(geo);
    UInt16           nextIdx = Geometry::TexCoordsIndex;

    for(UInt32 i = 0; i < vertexElements.size(); ++i)
    {
        switch(vertexElements[i].semantic)
        {
        case VES_POSITION:
            geo->setProperty(vertexElements[i].prop,
                             Geometry::PositionsIndex);
            geo->setIndex   (propIdx,
                             Geometry::PositionsIndex);
            break;

        case VES_BLEND_WEIGHTS:
        case VES_BLEND_INDICES:
        case VES_TEXTURE_COORDINATES:
        case VES_BINORMAL:
        case VES_TANGENT:
            geo->setProperty(vertexElements[i].prop, nextIdx);
            geo->setIndex   (propIdx,                nextIdx);
            ++nextIdx;
            break;

        case VES_NORMAL:
            geo->setProperty(vertexElements[i].prop,
                             Geometry::NormalsIndex);
            geo->setIndex   (propIdx,
                             Geometry::NormalsIndex);
            break;

        case VES_DIFFUSE:
            geo->setProperty(vertexElements[i].prop,
                             Geometry::ColorsIndex);
            geo->setIndex   (propIdx,
                             Geometry::ColorsIndex);
            break;

        case VES_SPECULAR:
            geo->setProperty(vertexElements[i].prop,
                             Geometry::SecondaryColorsIndex);
            geo->setIndex   (propIdx,
                             Geometry::SecondaryColorsIndex);
            break;
        }
    }

    GeoUInt8PropertyUnrecPtr types = GeoUInt8Property::create();
    types->addValue(GL_TRIANGLES);

    GeoUInt32PropertyUnrecPtr lengths = GeoUInt32Property::create();
    lengths->addValue(propIdx->size());

    geo->setTypes  (types);
    geo->setLengths(lengths);

    geo->setMaterial(getDefaultMaterial());

    _rootN->addChild(geoN);
}


OSG_END_NAMESPACE
