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
#include "OSGNameAttachment.h"
#include "OSGNode.h"
#include "OSGOgreSkeletonReader.h"
#include "OSGSceneFileHandler.h"
#include "OSGSimpleMaterial.h"
#include "OSGSkinnedGeometry.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

const std::string OgreMeshReader::_versionString("[MeshSerializer_v1.8]");

/* explicit */
OgreMeshReader::OgreMeshReader(std::istream& is, const OgreOptions &options)
    : Inherited(is),
      _options (options),
      _rootN   (),
      _skel    ()
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

std::string
OgreMeshReader::getVertexElementTypeString(VertexElementType veType)
{
    std::string result;

    switch(veType)
    {
    case VET_FLOAT1:      result = "VET_FLOAT1";      break;
    case VET_FLOAT2:      result = "VET_FLOAT2";      break;
    case VET_FLOAT3:      result = "VET_FLOAT3";      break;
    case VET_FLOAT4:      result = "VET_FLOAT4";      break;
    case VET_COLOUR:      result = "VET_COLOUR";      break;
    case VET_SHORT1:      result = "VET_SHORT1";      break;
    case VET_SHORT2:      result = "VET_SHORT2";      break;
    case VET_SHORT3:      result = "VET_SHORT3";      break;
    case VET_SHORT4:      result = "VET_SHORT4";      break;
    case VET_UBYTE4:      result = "VET_UBYTE4";      break;
    case VET_COLOUR_ARGB: result = "VET_COLOUR_ARGB"; break;
    case VET_COLOUR_ABGR: result = "VET_COLOUR_ABGR"; break;
    default:              result = "?INVALID?";       break;
    }

    return result;
}

std::string
OgreMeshReader::getVertexElementSemanticString(VertexElementSemantic veSemantic)
{
    std::string result;

    switch(veSemantic)
    {
    case VES_POSITION:            result = "VES_POSITION";            break;
    case VES_BLEND_WEIGHTS:       result = "VES_BLEND_WEIGHTS";       break;
    case VES_BLEND_INDICES:       result = "VES_BLEND_INDICES";       break;
    case VES_NORMAL:              result = "VES_NORMAL";              break;
    case VES_DIFFUSE:             result = "VES_DIFFUSE";             break;
    case VES_SPECULAR:            result = "VES_SPECULAR";            break;
    case VES_TEXTURE_COORDINATES: result = "VES_TEXTURE_COORDINATES"; break;
    case VES_BINORMAL:            result = "VES_BINORMAL";            break;
    case VES_TANGENT:             result = "VES_TANGENT";             break;
    default:                      result = "?INVALID?";               break;
    }

    return result;
}

std::string
OgreMeshReader::getSubMeshOperationString(SubMeshOperation meshOp)
{
    std::string result;

    switch(meshOp)
    {
    case SMO_POINT_LIST:     result = "SMO_POINT_LIST";     break;
    case SMO_LINE_LIST:      result = "SMO_LINE_LIST";      break;
    case SMO_LINE_STRIP:     result = "SMO_LINE_STRIP";     break;
    case SMO_TRIANGLE_LIST:  result = "SMO_TRIANGLE_LIST";  break;
    case SMO_TRIANGLE_STRIP: result = "SMO_TRIANGLE_STRIP"; break;
    case SMO_TRIANGLE_FAN:   result = "SMO_TRIANGLE_FAN";   break;
    default:                 result = "?INVALID?";          break;
    }

    return result;
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
    SubMeshStore       subMeshInfo;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_SUBMESH:
            readSubMesh(subMeshInfo, sharedVertexElements, skelAnim);
            break;

        case CHUNK_GEOMETRY:
            readGeometry(sharedVertexElements);
            break;

        case CHUNK_MESH_SKELETON_LINK:
            readMeshSkeletonLink(subMeshInfo);
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
            readSubMeshNameTable(subMeshInfo);
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

    SubMeshStore::iterator smIt  = subMeshInfo.begin();
    SubMeshStore::iterator smEnd = subMeshInfo.end  ();

    for(; smIt != smEnd; ++smIt)
    {
        if((*smIt).sharedVertex == true)
        {
            constructSubMesh(*smIt, sharedVertexElements);
        }
        else
        {
            constructSubMesh(*smIt, (*smIt).vertexElements);
        }
    }
}

void
OgreMeshReader::readSubMesh(SubMeshStore       &subMeshInfo,
                            VertexElementStore &sharedVertexElements,
                            bool                skelAnim             )
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMesh\n"));

    subMeshInfo.push_back((SubMeshInfo()));
    SubMeshInfo &smInfo = subMeshInfo.back();

    smInfo.matName       = readString(_is);
    smInfo.sharedVertex  = readBool  (_is);
    UInt32      idxCount = readUInt32(_is);
    bool        idx32Bit = readBool  (_is);

    OSG_OGRE_LOG(("OgreMeshReader::readSubMesh: matName '%s' sharedVert '%d' "
                  "idxCount '%d' idx32Bit '%d'\n",
                  smInfo.matName.c_str(), smInfo.sharedVertex, idxCount, idx32Bit));

    smInfo.skelAnim = skelAnim;
    smInfo.meshOp   = SMO_TRIANGLE_LIST;

    if(idx32Bit == true)
    {
        GeoUInt32PropertyUnrecPtr pi = GeoUInt32Property::create();
        pi->resize(idxCount);

        _is.read(reinterpret_cast<Char8 *>(&pi->editField().front()),
                 idxCount * sizeof(UInt32));

        smInfo.propIdx = pi;
    }
    else
    {
        GeoUInt16PropertyUnrecPtr pi = GeoUInt16Property::create();
        pi->resize(idxCount);

        _is.read(reinterpret_cast<Char8 *>(&pi->editField().front()),
                 idxCount * sizeof(UInt16));

        smInfo.propIdx = pi;
    }

    Int16 boneIdxVE    = -1;
    Int16 boneWeightVE = -1;
    bool  stop         = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_GEOMETRY:
            readGeometry(smInfo.vertexElements);
            break;

        case CHUNK_SUBMESH_OPERATION:
            readSubMeshOperation(smInfo);
            break;

        case CHUNK_SUBMESH_BONE_ASSIGNMENT:
            readSubMeshBoneAssignment(smInfo, boneIdxVE, boneWeightVE);
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
}

void
OgreMeshReader::readSubMeshOperation(SubMeshInfo &smInfo)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshOperation\n"));

    smInfo.meshOp = static_cast<SubMeshOperation>(readUInt16(_is));

    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshOperation: opType '%s'\n",
                  getSubMeshOperationString(smInfo.meshOp).c_str()));
}

void
OgreMeshReader::readSubMeshBoneAssignment(SubMeshInfo &smInfo,
                                          Int16       &boneIdxVE,
                                          Int16       &boneWeightVE   )
{
    readBoneAssignment(smInfo.vertexElements, boneIdxVE, boneWeightVE);
}

void
OgreMeshReader::readSubMeshTextureAlias(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshTextureAlias\n"));

    std::string aliasName   = readString(_is);
    std::string textureName = readString(_is);

    SWARNING << "OgreMeshReader::readSubMeshTextureAlias: CHUNK_SUBMESH_TEXTURE_ALIAS NIY"
             << std::endl;
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
                  "bufferIdx '%d' type '%s' semantic '%s' offset '%d' index '%d'\n",
                  vElem.bufferIdx,
                  getVertexElementTypeString    (vElem.type    ).c_str(),
                  getVertexElementSemanticString(vElem.semantic).c_str(),
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
                     << "semantic '" << getVertexElementSemanticString(vElem.semantic)
                     << "' does not support type '"
                     << getVertexElementTypeString(vElem.type) << "'"
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
                     << "semantic '" << getVertexElementSemanticString(vElem.semantic)
                     << "' does not support type '"
                     << getVertexElementTypeString(vElem.type) << "'"
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
#ifndef OSG_OGRE_SILENT
    UInt16 vertSize = 
#endif
        readUInt16(_is);

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
                Vec2f v;
                v[0] = readReal32(_is);
                v[1] = readReal32(_is);

                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_FLOAT3:
            {
                Vec3f v;
                v[0] = readReal32(_is);
                v[1] = readReal32(_is);
                v[2] = readReal32(_is);

                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_FLOAT4:
            {
                Vec4f v;
                v[0] = readReal32(_is);
                v[1] = readReal32(_is);
                v[2] = readReal32(_is);
                v[3] = readReal32(_is);

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
                Vec2s v;
                v[0] = readInt16(_is);
                v[1] = readInt16(_is);

                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_SHORT3:
            {
                Vec3s v;
                v[0] = readInt16(_is);
                v[1] = readInt16(_is);
                v[2] = readInt16(_is);

                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_SHORT4:
            {
                Vec4s v;
                v[0] = readInt16(_is);
                v[1] = readInt16(_is);
                v[2] = readInt16(_is);
                v[3] = readInt16(_is);

                vertexElements[veIdx].prop->addValue(v);
            }
            break;

            case VET_UBYTE4:
                readUInt32(_is);
                SWARNING << "OgreMeshReader::readGeometryVertexBufferData: "
                         << "type VET_UBYTE4 NIY" << std::endl;
                break;

            case VET_COLOUR_ARGB:
                SWARNING << "OgreMeshReader::readGeometryVertexBufferData: "
                         << "type VET_COLOUR_ARGB NIY" << std::endl;
                break;

            case VET_COLOUR_ABGR:
                SWARNING << "OgreMeshReader::readGeometryVertexBufferData: "
                         << "type VET_COLOUR_ABGR NIY" << std::endl;
                break;
            }
        }
    }
}

void
OgreMeshReader::readMeshSkeletonLink(SubMeshStore &subMeshInfo)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshSkeletonLink\n"));

    if(_options.getLoadSkeleton() == true)
    {
        std::string skelName = readString(_is);

        std::string   skelFile = SceneFileHandler::the()->getPathHandler()->findFile(skelName.c_str());
        std::ifstream ifs(skelFile.c_str(), std::ios_base::in | std::ios_base::binary);

        OSG_OGRE_LOG(("OgreMeshReader::readMeshSkeletonLink: skelName '%s' file '%s'\n",
                      skelName.c_str(), skelFile.c_str()));

        OgreSkeletonReader osr(ifs, _options);
        osr.read();

        _skel = osr.getSkeleton();

        if(osr.getGlobals() != NULL)
            _rootN->addAttachment(osr.getGlobals());
    }
    else
    {
        skip(_is, _header.chunkSize - _chunkHeaderSize);
    }
}

void
OgreMeshReader::readMeshBoneAssignment(VertexElementStore &vertexElements,
                                       Int16              &boneIdxVE,
                                       Int16              &boneWeightVE   )
{
    readBoneAssignment(vertexElements, boneIdxVE, boneWeightVE);
}

void
OgreMeshReader::readMeshLOD(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshLOD\n"));

    std::string strategyName = readString(_is);

    //UInt16 levelCount
    readUInt16(_is);

    // bool manual
    readBool  (_is);

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

    //Real32 lodValue
    readReal32(_is);

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

    SWARNING << "OgreMeshReader::readMeshLODManual: CHUNK_MESH_LOD_MANUAL NIY"
             << std::endl;
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

    SWARNING << "OgreMeshReader::readMeshLODManual: CHUNK_MESH_LOD_GENERATED NIY"
             << std::endl;
}

void
OgreMeshReader::readMeshBounds(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readMeshBounds\n"));

    Pnt3f  bbMin;
    bbMin[0] = readReal32(_is);
    bbMin[1] = readReal32(_is);
    bbMin[2] = readReal32(_is);

    Pnt3f  bbMax;
    bbMax[0] = readReal32(_is);
    bbMax[1] = readReal32(_is);
    bbMax[2] = readReal32(_is);

    //Real32 radius
    readReal32(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readMeshBounds: bbMin '(%f %f %f)' bbMax '(%f %f %f)'\n",
                  bbMin[0], bbMin[1], bbMin[2], bbMax[0], bbMax[1], bbMax[2]));

    _rootN->editVolume().setBounds(bbMin, bbMax);
    _rootN->editVolume().setStatic(true);
}

void
OgreMeshReader::readSubMeshNameTable(SubMeshStore &subMeshInfo)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTable\n"));

    bool stop = false;

    while(_is)
    {
        readChunkHeader(_is);

        switch(_header.chunkId)
        {
        case CHUNK_SUBMESH_NAME_TABLE_ELEMENT:
            readSubMeshNameTableElement(subMeshInfo);
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
OgreMeshReader::readSubMeshNameTableElement(SubMeshStore &subMeshInfo)
{
    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTableElement\n"));

    UInt16      meshIdx  = readUInt16(_is);
    std::string meshName = readString(_is);

    OSG_OGRE_LOG(("OgreMeshReader::readSubMeshNameTableElement: "
                  "meshIdx '%d' meshName '%s' matName '%s'\n",
                  meshIdx, meshName.c_str(), subMeshInfo[meshIdx].matName.c_str()));

    if(meshIdx < subMeshInfo.size())
    {
        subMeshInfo[meshIdx].name = meshName;
    }
}

void
OgreMeshReader::readEdgeLists(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readEdgeLists\n"));

    skip(_is, _header.chunkSize - _chunkHeaderSize);

    SWARNING << "OgreMeshReader::readEdgeLists: CHUNK_EDGE_LISTS NIY"
             << std::endl;
}

void
OgreMeshReader::readPoses(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readPoses\n"));

    skip(_is, _header.chunkSize - _chunkHeaderSize);

    SWARNING << "OgreMeshReader::readPoses: CHUNK_POSES NIY"
             << std::endl;
}

void
OgreMeshReader::readAnimations(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readAnimations\n"));

    skip(_is, _header.chunkSize - _chunkHeaderSize);

    SWARNING << "OgreMeshReader::readAnimations CHUNK_ANIMATIONS NIY"
             << std::endl;
}

void
OgreMeshReader::readTableExtremes(void)
{
    OSG_OGRE_LOG(("OgreMeshReader::readTableExtremes\n"));

    skip(_is, _header.chunkSize - _chunkHeaderSize);

    SWARNING << "OgreMeshReader::readTableExtremes CHUNK_TABLE_EXTREMES NIY"
             << std::endl;
}

void
OgreMeshReader::readBoneAssignment(VertexElementStore &vertexElements,
                                   Int16              &boneIdxVE,
                                   Int16              &boneWeightVE   )
{
    // OSG_OGRE_LOG(("OgreMeshReader::readBoneAssignment\n");

    UInt32 vertIdx    = readUInt32(_is);
    UInt16 boneIdx    = readUInt16(_is);
    Real32 boneWeight = readReal32(_is);

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
    boneWeightProp = dynamic_pointer_cast<GeoVec4fProperty>(vertexElements[boneWeightVE].prop);

    GeoVec4fProperty::StoredFieldType* boneIdxF    = boneIdxProp   ->editFieldPtr();
    GeoVec4fProperty::StoredFieldType* boneWeightF = boneWeightProp->editFieldPtr();

    if(vertIdx >= boneIdxF->size())
        boneIdxF->resize(vertIdx + 1, Vec4f(-1.f, -1.f, -1.f, -1.f));

    if(vertIdx >= boneWeightF->size())
        boneWeightF->resize(vertIdx + 1, Vec4f(0.f, 0.f, 0.f, 0.f));

    bool found = false;

    for(UInt16 i = 0; i < 4; ++i)
    {
        if((*boneIdxF)[vertIdx][i] == boneIdx)
        {
            if((*boneWeightF)[vertIdx][i] < boneWeight)
            {
                SINFO << "OgreMeshReader::readBoneAssignment: "
                      << "vertex '" << vertIdx
                      << "' changing bone influence from ("
                      << (*boneIdxF   )[vertIdx][i] << ", "
                      << (*boneWeightF)[vertIdx][i]
                      << ") to (" << boneIdx << ", " << boneWeight
                      << ")." << std::endl;
            }
            else
            {
                SINFO << "OgreMeshReader::readBoneAssignment: "
                      << "vertex '" << vertIdx
                      << "' already influenced by bone ("
                      << boneIdx << "' " << boneWeight << ")."
                      << std::endl;
            }

            found = true;
            break;
        }
        else if((*boneIdxF)[vertIdx][i] < 0.f)
        {
            (*boneIdxF   )[vertIdx][i] = boneIdx;
            (*boneWeightF)[vertIdx][i] = boneWeight;

            found = true;
            break;
        }
    }

    if(found == false)
    {
        SWARNING << "OgreMeshReader::readBoneAssignment: "
                 << "vertex '" << vertIdx
                 << "' has more than 4 bones assigned." << std::endl;

        UInt16 smallestWeightIdx = 0;
        Real32 smallestWeight    = TypeTraits<Real32>::getMax();

        for(UInt16 i = 0; i < 4; ++i)
        {
            if((*boneWeightF)[vertIdx][i] < smallestWeight)
            {
                smallestWeightIdx = i;
                smallestWeight    = (*boneWeightF)[vertIdx][i];
            }
        }

        if((*boneWeightF)[vertIdx][smallestWeightIdx] < boneWeight)
        {
            SINFO << "OgreMeshReader::readBoneAssignment: "
                  << "vertex '" << vertIdx
                  << "' replacing smallest influence ("
                  << (*boneIdxF   )[vertIdx][smallestWeightIdx] << ", "
                  << (*boneWeightF)[vertIdx][smallestWeightIdx]
                  << ") with (" << boneIdx << ", " << boneWeight << ")"
                  << std::endl;

            (*boneIdxF   )[vertIdx][smallestWeightIdx] = boneIdx;
            (*boneWeightF)[vertIdx][smallestWeightIdx] = boneWeight;
        }
        else
        {
            SINFO << "OgreMeshReader::readBoneAssignment: "
                  << "vertex '" << vertIdx
                  << "' smallest existing influence ("
                  << (*boneIdxF   )[vertIdx][smallestWeightIdx] << ", "
                  << (*boneWeightF)[vertIdx][smallestWeightIdx]
                  << ") is larger than " << boneIdx << ", " << boneWeight << ")"
                  << std::endl;
        }
    }
}

void
OgreMeshReader::constructSubMesh(SubMeshInfo        &smInfo,
                                 VertexElementStore &vertexElements)
{
    OSG_OGRE_LOG(("OgreMeshReader::constructSubMesh\n"));

    if(smInfo.skelAnim == true)
    {
        smInfo.mesh = SkinnedGeometry::create();
    }
    else
    {
        smInfo.mesh = Geometry::create();
    }

    smInfo.meshN = makeNodeFor(smInfo.mesh);
    smInfo.meshN->editSFVolume()->setValue(_rootN->getVolume());

    setName(smInfo.meshN, smInfo.name);

    UInt16 nextIdx = Geometry::TexCoordsIndex;

    for(UInt32 i = 0; i < vertexElements.size(); ++i)
    {
        Int32 usage   = -1;
        Int16 propSlot = -1;

        switch(vertexElements[i].semantic)
        {
        case VES_POSITION:
            usage    = GeoProperty::UsageObjectSpace;
            propSlot = Geometry::PositionsIndex;
            break;

        case VES_BLEND_WEIGHTS:
        case VES_BLEND_INDICES:
        case VES_TEXTURE_COORDINATES:
            usage    = GeoProperty::UsageParameterSpace;
            propSlot = nextIdx++;
            break;

        case VES_BINORMAL:
        case VES_TANGENT:
            usage    = GeoProperty::UsageTangentSpace;
            propSlot = nextIdx++;
            break;

        case VES_NORMAL:
            usage    = GeoProperty::UsageTangentSpace;
            propSlot = Geometry::NormalsIndex;
            break;

        case VES_DIFFUSE:
            usage    = GeoProperty::UsageColorSpace;
            propSlot = Geometry::ColorsIndex;
            break;

        case VES_SPECULAR:
            usage    = GeoProperty::UsageColorSpace;
            propSlot = Geometry::SecondaryColorsIndex;
            break;
        }

        if(usage >= 0)
        {
            vertexElements[i].prop->setUsage(usage);
        }

        if(propSlot >= 0)
        {
            OSG_OGRE_LOG(("OgreMeshReader::constructSubMesh: vertex elem semantic '%s'"
                          " using property '%u'\n",
                          getVertexElementSemanticString(vertexElements[i].semantic).c_str(),
                          propSlot));

            smInfo.mesh->setProperty(vertexElements[i].prop, propSlot);
            smInfo.mesh->setIndex   (smInfo.propIdx,         propSlot);
        }
        else
        {
            SWARNING << "OgreMeshReader::constructSubMesh: no property slot found for "
                     << "vertex elem semantic '"
                     << getVertexElementSemanticString(vertexElements[i].semantic)
                     << "'. Skipping." << std::endl;
        }

        if(vertexElements[i].semantic == VES_BLEND_INDICES)
        {
            SkinnedGeometry* skin =
                dynamic_pointer_cast<SkinnedGeometry>(smInfo.mesh);

            skin->setJointIndexProperty(propSlot);
        }

        if(vertexElements[i].semantic == VES_BLEND_WEIGHTS)
        {
            SkinnedGeometry* skin =
                dynamic_pointer_cast<SkinnedGeometry>(smInfo.mesh);

            skin->setJointWeightProperty(propSlot);
        }
    }

    GeoUInt8PropertyUnrecPtr types = GeoUInt8Property::create();
    switch(smInfo.meshOp)
    {
    case SMO_POINT_LIST:
        types->addValue(GL_POINTS);
        break;

    case SMO_LINE_LIST:
        types->addValue(GL_LINES);
        break;

    case SMO_LINE_STRIP:
        types->addValue(GL_LINE_STRIP);
        break;

    case SMO_TRIANGLE_LIST:
        types->addValue(GL_TRIANGLES);
        break;

    case SMO_TRIANGLE_STRIP:
        types->addValue(GL_TRIANGLE_STRIP);
        break;

    case SMO_TRIANGLE_FAN:
        types->addValue(GL_TRIANGLE_FAN);
        break;
    }

    GeoUInt32PropertyUnrecPtr lengths = GeoUInt32Property::create();
    lengths->addValue(smInfo.propIdx->size());

    smInfo.mesh->setTypes  (types);
    smInfo.mesh->setLengths(lengths);

    constructMaterial(smInfo);

    if(smInfo.skelAnim == true && _skel != NULL)
    {
        SkinnedGeometry* skin = dynamic_pointer_cast<SkinnedGeometry>(smInfo.mesh);

        if(skin != NULL)
        {
            skin->setSkeleton  (_skel);
            skin->setRenderMode(SkinnedGeometry::RMSkeleton);
        }
    }

    _rootN->addChild(smInfo.meshN);
}

void
OgreMeshReader::constructMaterial(SubMeshInfo &smInfo)
{
    OSG_OGRE_LOG(("OgreMeshReader::constructMaterial\n"));

    MaterialMap::const_iterator  mmIt = _matMap.find(smInfo.matName);
    Material                    *mat  = NULL;

    if(mmIt != _matMap.end())
    {
        mat = (*mmIt).second;
    }
    else
    {
        SimpleMaterialUnrecPtr newMat = SimpleMaterial::create();
        newMat->setDiffuse  (Color3f(0.7f, 0.7f, 0.5f));
        newMat->setAmbient  (Color3f(0.1f, 0.1f, 0.1f));
        newMat->setSpecular (Color3f(0.3f, 0.3f, 0.3f));
        newMat->setShininess(20.f);

        setName(newMat, smInfo.matName);

        _matMap.insert(MaterialMap::value_type(smInfo.matName, newMat));

        mat = newMat;
    }

    smInfo.mesh->setMaterial(mat);
}

OSG_END_NAMESPACE
