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


#include <string>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGNode.h"
#include "OSGGeometry.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGGeoProperty.h"
#include "OSGGroup.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoProperty.h"
#include "OSGNameAttachment.h"
#include "OSGTriangleIterator.h"
#include "OSGGeoFunctions.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGBlendChunk.h"
#include "OSGImage.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGImageFileHandler.h"

#include "OSG3DSSceneFileType.h"

OSG_USING_NAMESPACE

const Char8 *A3DSSceneFileType::_suffixA[] = {"3ds"};

A3DSSceneFileType  A3DSSceneFileType::_the(_suffixA,
                                           sizeof(_suffixA),
                                           false,
                                           10,
                                           SceneFileType::OSG_READ_SUPPORTED);

NodeTransitPtr A3DSSceneFileType::read(      std::istream &is, 
                                       const Char8        *,
                                             Resolver        ) const
{
    if(!is)
        return NodeTransitPtr(NULL);

    _materials.clear();

    L3DS scene;

    if(!scene.Load(is))
    {
        SWARNING << "Couldn't read from stream!" << std::endl;

        return NodeTransitPtr(NULL);
    }

    NodeTransitPtr  root = Node::create();

    root->setCore(Group::create());

    for(uint i=0;i<scene.GetMeshCount();++i)
    {
        NodeUnrecPtr mesh = createMesh(scene, scene.GetMesh(i));

        if(mesh != NULL)
            root->addChild(mesh);
    }

    _materials.clear();
 
    commitChanges();
   
    return root;
}

A3DSSceneFileType::A3DSSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority,
                                         UInt32  flags) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority,
                  flags)
{
}


A3DSSceneFileType &A3DSSceneFileType::the(void)
{
    return _the;
}


const Char8 *A3DSSceneFileType::getName(void) const
{
    return "3DS Geometry";
}


A3DSSceneFileType::A3DSSceneFileType(const A3DSSceneFileType &obj) :
    SceneFileType(obj),
    _materials()
{
    return;
}


A3DSSceneFileType::~A3DSSceneFileType (void )
{
    return;
}

NodeTransitPtr A3DSSceneFileType::createMesh(L3DS &scene, LMesh &mesh) const
{
    if(mesh.GetTriangleCount() == 0)
        return NodeTransitPtr(NULL);

    NodeUnrecPtr     node = Node::create();
    GeometryUnrecPtr geo = Geometry::create();

    node->setCore(geo);

    OSG::setName(node, mesh.GetName().c_str());

    GeoPnt3fPropertyUnrecPtr points    = GeoPnt3fProperty::create();
    GeoVec3fPropertyUnrecPtr normals   = GeoVec3fProperty::create();
    GeoVec2fPropertyUnrecPtr texcoords = GeoVec2fProperty::create();

    for(UInt32 i=0;i<mesh.GetTriangleCount();++i)
    {
        const LTriangle2 &t = mesh.GetTriangle2(i);

        points->push_back(Pnt3f(t.vertices[0].x, 
                                t.vertices[0].y, 
                                t.vertices[0].z));

        points->push_back(Pnt3f(t.vertices[1].x, 
                                t.vertices[1].y, 
                                t.vertices[1].z));

        points->push_back(Pnt3f(t.vertices[2].x, 
                                t.vertices[2].y, 
                                t.vertices[2].z));

        normals->push_back(Vec3f(t.vertexNormals[0].x, 
                                 t.vertexNormals[0].y, 
                                 t.vertexNormals[0].z));

        normals->push_back(Vec3f(t.vertexNormals[1].x, 
                                 t.vertexNormals[1].y, 
                                 t.vertexNormals[1].z));

        normals->push_back(Vec3f(t.vertexNormals[2].x, 
                                 t.vertexNormals[2].y, 
                                 t.vertexNormals[2].z));

        texcoords->push_back(Vec2f(t.textureCoords[0].x, t.textureCoords[0].y));
        texcoords->push_back(Vec2f(t.textureCoords[1].x, t.textureCoords[1].y));
        texcoords->push_back(Vec2f(t.textureCoords[2].x, t.textureCoords[2].y));
    }

    // create material opensg supports only one material per geometry!
    MaterialUnrecPtr mat = OSG::getDefaultMaterial();

    if(mesh.GetMaterialCount() > 0)
        mat = createMaterial(scene, mesh.GetMaterial(0));

    int nv = mesh.GetTriangleCount() * 3;

    GeoUInt32PropertyUnrecPtr indices = GeoUInt32Property::create();

    indices->editFieldPtr()->reserve(nv);

    for (int i = 0; i < nv; ++i)
        indices->push_back(i);

    GeoUInt32PropertyUnrecPtr lengths = GeoUInt32Property::create();

    lengths->push_back(nv);

    GeoUInt8PropertyUnrecPtr types = GeoUInt8Property::create();
    types->push_back(GL_TRIANGLES);

    geo->setMaterial(mat);
    geo->setPositions(points);
    geo->setNormals(normals);
    geo->setTexCoords(texcoords);
    geo->setIndices(indices);
    geo->setLengths(lengths);
    geo->setTypes(types);

    //createSharedIndex(geo);
    //OSG::calcVertexNormals(geo);

    return NodeTransitPtr(node);
}

MaterialTransitPtr A3DSSceneFileType::createMaterial(L3DS   &scene, 
                                                     UInt32  id   ) const
{
    materialIt mi = _materials.find(id);

    if(mi != _materials.end())
        return MaterialTransitPtr((*mi).second);

    LMaterial m = scene.GetMaterial(id);

    ChunkMaterialUnrecPtr cmat = ChunkMaterial::create();

    OSG::setName(cmat, m.GetName());

    MaterialChunkUnrecPtr matc = MaterialChunk::create();

    cmat->addChunk(matc);

    Real32 t = m.GetTransparency();

    matc->setAmbient(Color4f(m.GetAmbientColor().r, m.GetAmbientColor().g,
                     m.GetAmbientColor().b, 1.0f - t));
    matc->setDiffuse(Color4f(m.GetDiffuseColor().r, m.GetDiffuseColor().g,
                     m.GetDiffuseColor().b, 1.0f - t));
    matc->setSpecular(Color4f(m.GetSpecularColor().r, m.GetSpecularColor().g,
                     m.GetSpecularColor().b, 1.0f - t));
    matc->setEmission(Color4f(0.0f, 0.0f, 0.0f, 1.0f - t));
    matc->setShininess(m.GetShininess() * 128.0f);


    // create a texture chunk
    LMap &map = m.GetTextureMap1();
    const char *texname = map.mapName;

    ImageUnrecPtr image = NULL;

    if(texname != NULL && strlen(texname) > 0)
    {
        image = Image::create();
        bool img_ok = image->read(texname);

        if(!img_ok)
        {
            std::string casename(texname);
            for(std::string::reverse_iterator it = casename.rbegin(); 
                it != casename.rend() && *it != '/' && *it != '\\'; 
                ++it)
            {
                if(*it >= 'a' && *it <= 'z')
                {
                    *it = 'A' + *it - 'a';
                }
                else
                if(*it >= 'A' && *it <= 'Z')
                {
                    *it = 'a' + *it - 'A';
                }
                
            }
            
            FWARNING(("Couldn't load image '%s', trying case "
                      "reversed version '%s'! \n", texname,
                      casename.c_str()));
                      
            img_ok = image->read(casename.c_str());
        }
        
        if(img_ok)
        {
            image->setForceAlphaBinary(image->calcIsAlphaBinary());
            
            TextureObjChunkUnrecPtr texc  = TextureObjChunk::create();
            TextureEnvChunkUnrecPtr texec = TextureEnvChunk::create();

            texc->setImage(image);

            // 0x0008 means no tiling.
            GLenum wm = (map.tiling & 0x0008) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
            texc->setWrapS(wm);
            texc->setWrapT(wm);

            texec->setEnvMode(GL_MODULATE);
            texc ->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
            texc ->setMagFilter(GL_LINEAR);

            cmat->addChunk(texc);
            cmat->addChunk(texec);
        }
    }

    // add a blend chunk for transparency
    if(t > 0.0 || 
       ( image != NULL && 
         image->hasAlphaChannel()) )
    {
        BlendChunkUnrecPtr blendc = BlendChunk::create();
        
        if(image != NULL && image->isAlphaBinary())
        {
            blendc->setAlphaFunc(GL_NOTEQUAL);
            blendc->setAlphaValue(0);
        }
        else
        {
            blendc->setSrcFactor(GL_SRC_ALPHA);
            blendc->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        }
        
        cmat->addChunk(blendc);
    }

    _materials.insert(std::pair<UInt32, MaterialUnrecPtr>(
                          id, MaterialUnrecPtr(cmat)));

    return MaterialTransitPtr(cmat);
}
