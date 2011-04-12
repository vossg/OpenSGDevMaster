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

#ifndef _OSGOGREMESHREADER_H_
#define _OSGOGREMESHREADER_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGOgreMeshReader.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"
#include "OSGFileIODef.h"
#include "OSGOgreChunkReader.h"
#include "OSGOgreOptions.h"
#include "OSGGeometry.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGGeoVectorProperty.h"
#include "OSGSkeleton.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING OgreMeshReader : public OgreChunkReader
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef OgreChunkReader  Inherited;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Constructors/Destructor                                      */
    /*! \{                                                                 */

    explicit  OgreMeshReader(      std::istream &is,
                             const OgreOptions  &options);
    virtual  ~OgreMeshReader(void                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name Read                                                         */
    /*! \{                                                                 */

    Node* getRoot(void);

    void read(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    enum ChunkIds
    {
        CHUNK_HEADER                      = 0x1000,
        CHUNK_MESH                        = 0x3000,

        CHUNK_SUBMESH                     = 0x4000,
        CHUNK_SUBMESH_OPERATION           = 0x4010,
        CHUNK_SUBMESH_BONE_ASSIGNMENT     = 0x4100,
        CHUNK_SUBMESH_TEXTURE_ALIAS       = 0x4200,

        CHUNK_GEOMETRY                    = 0x5000,
        CHUNK_GEOMETRY_VERTEX_DECLARATION = 0x5100,
        CHUNK_GEOMETRY_VERTEX_ELEMENT     = 0x5110,
        CHUNK_GEOMETRY_VERTEX_BUFFER      = 0x5200,
        CHUNK_GEOMETRY_VERTEX_BUFFER_DATA = 0x5210,

        CHUNK_MESH_SKELETON_LINK          = 0x6000,
        CHUNK_MESH_BONE_ASSIGNMENT        = 0x7000,
        CHUNK_MESH_LOD                    = 0x8000,
        CHUNK_MESH_LOD_USAGE              = 0x8100,
        CHUNK_MESH_LOD_MANUAL             = 0x8110,
        CHUNK_MESH_LOD_GENERATED          = 0x8120,
        CHUNK_MESH_BOUNDS                 = 0x9000,

        CHUNK_SUBMESH_NAME_TABLE          = 0xA000,
        CHUNK_SUBMESH_NAME_TABLE_ELEMENT  = 0xA100,

        CHUNK_EDGE_LISTS                  = 0xB000,
        CHUNK_EDGE_LIST_LOD               = 0xB100,
        CHUNK_EDGE_GROUP                  = 0xB110,

        CHUNK_POSES                       = 0xC000,
        CHUNK_POSE                        = 0xC100,
        CHUNK_POSE_VERTEX                 = 0xC111,

        CHUNK_ANIMATIONS                  = 0xD000,
        CHUNK_ANIMATION                   = 0xD100,
        CHUNK_ANIMATION_TRACK             = 0xD110,
        CHUNK_ANIMATION_MORPH_KEYFRAME    = 0xD111,
        CHUNK_ANIMATION_POSE_KEYFRAME     = 0xD112,
        CHUNK_ANIMAITON_POSE_REF          = 0xD113,

        CHUNK_TABLE_EXTREMES              = 0xE000,
    };

    enum VertexElementType
    {
        VET_FLOAT1      = 0,
        VET_FLOAT2      = 1,
        VET_FLOAT3      = 2,
        VET_FLOAT4      = 3,
        VET_COLOUR      = 4,
        VET_SHORT1      = 5,
        VET_SHORT2      = 6,
        VET_SHORT3      = 7,
        VET_SHORT4      = 8,
        VET_UBYTE4      = 9,
        VET_COLOUR_ARGB = 10,
        VET_COLOUR_ABGR = 11
    };

    enum VertexElementSemantic
    {
        VES_POSITION            = 1,
        VES_BLEND_WEIGHTS       = 2,
        VES_BLEND_INDICES       = 3,
        VES_NORMAL              = 4,
        VES_DIFFUSE             = 5,
        VES_SPECULAR            = 6,
        VES_TEXTURE_COORDINATES = 7,
        VES_BINORMAL            = 8,
        VES_TANGENT             = 9
    };

    enum SubMeshOperation
    {
        SMO_POINT_LIST     = 1,
        SMO_LINE_LIST      = 2,
        SMO_LINE_STRIP     = 3,
        SMO_TRIANGLE_LIST  = 4,
        SMO_TRIANGLE_STRIP = 5,
        SMO_TRIANGLE_FAN   = 6
    };

    struct VertexElement
    {
        UInt16                    bufferIdx;
        VertexElementType         type;
        VertexElementSemantic     semantic;
        UInt16                    offset;
        UInt16                    index;

        GeoVectorPropertyUnrecPtr prop;
    };

    typedef std::vector<VertexElement       >  VertexElementStore;
    typedef std::vector<std::vector<UInt32> >  BufferVertexMap;

    struct SubMeshInfo
    {
        bool                        sharedVertex;
        bool                        skelAnim;
        VertexElementStore          vertexElements;
        SubMeshOperation            meshOp;
        std::string                 name;
        std::string                 matName;

        GeoIntegralPropertyUnrecPtr propIdx;

        GeometryUnrecPtr            mesh;
        NodeUnrecPtr                meshN;
    };

    typedef std::vector<SubMeshInfo>                SubMeshStore;

    typedef std::map<std::string, MaterialUnrecPtr> MaterialMap;

    std::string getVertexElementTypeString    (VertexElementType     veType    );
    std::string getVertexElementSemanticString(VertexElementSemantic veSemantic);
    std::string getSubMeshOperationString     (SubMeshOperation      meshOp    );


    void readMesh                     (void);
    void readSubMesh                  (SubMeshStore       &subMeshInfo,
                                       VertexElementStore &sharedVertexElements,
                                       bool                skelAnim             );

    void readSubMeshOperation         (SubMeshInfo        &smInfo         );
    void readSubMeshBoneAssignment    (SubMeshInfo        &smInfo,
                                       Int16              &boneIdxVE,
                                       Int16              &boneWeightVE   );
    void readSubMeshTextureAlias      (void);
    void readGeometry                 (VertexElementStore &vertexElements );
    void readGeometryVertexDeclaration(VertexElementStore &vertexElements,
                                       BufferVertexMap    &bufferMap      );
    void readGeometryVertexElement    (VertexElementStore &vertexElements,
                                       BufferVertexMap    &bufferMap      );
    void readGeometryVertexBuffer     (UInt32              vertCount,
                                       VertexElementStore &vertexElements,
                                       BufferVertexMap    &bufferMap      );
    void readGeometryVertexBufferData (UInt32              vertCount,
                                       UInt16              bindIdx,
                                       VertexElementStore &vertexElements,
                                       BufferVertexMap    &bufferMap      );

    void readMeshSkeletonLink         (SubMeshStore       &subMeshInfo    );
    void readMeshBoneAssignment       (VertexElementStore &vertexElements,
                                       Int16              &boneIdxVE,
                                       Int16              &boneWeightVE   );
    void readMeshLOD                  (void);
    void readMeshLODUsage             (void);
    void readMeshLODManual            (void);
    void readMeshLODGenerated         (void);
    void readMeshBounds               (void);
    void readSubMeshNameTable         (SubMeshStore       &subMeshInfo    );
    void readSubMeshNameTableElement  (SubMeshStore       &subMeshInfo    );
    void readEdgeLists                (void);
    void readPoses                    (void);
    void readAnimations               (void);
    void readTableExtremes            (void);

    void readBoneAssignment           (VertexElementStore &vertexElements,
                                       Int16              &boneIdxVE,
                                       Int16              &boneWeightVE   );

    void constructSubMesh             (SubMeshInfo        &smInfo,
                                       VertexElementStore &vertexElements );
    void constructMaterial            (SubMeshInfo        &smInfo         );

    static const std::string _versionString;

    const OgreOptions &_options;

    MaterialMap        _matMap;

    NodeUnrecPtr       _rootN;
    SkeletonUnrecPtr   _skel;
};

OSG_END_NAMESPACE

#endif // _OSGOGREMESHREADER_H_
