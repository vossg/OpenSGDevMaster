/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <UnitTest++.h>

// Unit tests for OSB file io.

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGNameAttachment.h"
#include "OSGSceneFileHandler.h"

#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGImage.h"
#include "OSGChunkMaterial.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

#ifndef OSG_DISABLE_DEPRECATED
#include "OSGTextureChunk.h"
#endif

#include <boost/filesystem/operations.hpp>

namespace bf = boost::filesystem;

SUITE(OSBTests)
{

struct FileFixture
{
   FileFixture()
   {
      test_file = bf::path("test_file.osb");
      bf::remove(test_file);
   }

   ~FileFixture()
   {
      bf::remove(test_file);
   }

   bf::path test_file;
};


TEST_FIXTURE(FileFixture, CreateOSBFile)
{
   OSG::NodeUnrecPtr n = OSG::Node::create();
   n->setCore(OSG::Group::create());

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodeUnrecPtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != NULL);
}

TEST_FIXTURE(FileFixture, CreateOSBTree)
{
   // Test larger tree
   OSG::NodeUnrecPtr base_node  = OSG::Node::create();
   base_node->setCore(OSG::Group::create());
   OSG::NodeUnrecPtr child_node = OSG::Node::create();
   child_node->setCore(OSG::Group::create());

   base_node->addChild(child_node);

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(base_node, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodeUnrecPtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != NULL);
   CHECK(new_n->getCore() != NULL);
   CHECK(new_n->getNChildren() == 1);
   CHECK(new_n->getChild(0) != NULL);
   CHECK(new_n->getChild(0)->getCore() != NULL);
}


TEST_FIXTURE(FileFixture, TestNameRetention)
{
   std::string start_name("node");
   OSG::NodeUnrecPtr n = OSG::Node::create();
   OSG::setName(n, start_name);
   n->setCore(OSG::Group::create());

   CHECK(!bf::exists(test_file));
   OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
   CHECK(bf::exists(test_file));

   OSG::NodeUnrecPtr new_n =
      OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
   CHECK(new_n != NULL);
   CHECK(OSG::getName(new_n) != NULL);
   std::string cur_name = std::string(OSG::getName(new_n));

   CHECK(cur_name == start_name);
}

#ifndef OSG_DISABLE_DEPRECATED
TEST_FIXTURE(FileFixture, TextureChunkIO)
{
    OSG::NodeUnrecPtr          n   = OSG::Node::create();
    OSG::GeometryUnrecPtr      geo = OSG::makeBoxGeo(2.0, 2.0, 2.0, 1, 1, 1);
    OSG::ChunkMaterialUnrecPtr mat = OSG::ChunkMaterial::create();
    
    OSG::ImageUnrecPtr img = OSG::Image::create();
    img->set(OSG::Image::OSG_RGBA_PF, 2, 2);
    
    img->editData()[0 * 2 * 4 + 0 * 4 + 0] = 255;
    img->editData()[0 * 2 * 4 + 0 * 4 + 1] =   0;
    img->editData()[0 * 2 * 4 + 0 * 4 + 2] =   0;
    img->editData()[0 * 2 * 4 + 0 * 4 + 3] = 255;
    
    img->editData()[0 * 2 * 4 + 1 * 4 + 0] = 255;
    img->editData()[0 * 2 * 4 + 1 * 4 + 1] = 255;
    img->editData()[0 * 2 * 4 + 1 * 4 + 2] =   0;
    img->editData()[0 * 2 * 4 + 1 * 4 + 3] = 255;
    
    img->editData()[1 * 2 * 4 + 0 * 4 + 0] =   0;
    img->editData()[1 * 2 * 4 + 0 * 4 + 1] =   0;
    img->editData()[1 * 2 * 4 + 0 * 4 + 2] = 255;
    img->editData()[1 * 2 * 4 + 0 * 4 + 3] = 255;
    
    img->editData()[1 * 2 * 4 + 1 * 4 + 0] =   0;
    img->editData()[1 * 2 * 4 + 1 * 4 + 1] = 255;
    img->editData()[1 * 2 * 4 + 1 * 4 + 2] = 255;
    img->editData()[1 * 2 * 4 + 1 * 4 + 3] = 255;
    
    OSG::TextureChunkUnrecPtr tex = OSG::TextureChunk::create();
    tex->setImage(img);
    
    mat->addChunk(tex);
    geo->setMaterial(mat);
    
    n->setCore(geo);
    
    OSG::SceneFileHandler::the()->write(n, test_file.native_file_string().c_str());
    
    OSG::NodeUnrecPtr n2 =
        OSG::SceneFileHandler::the()->read(test_file.native_file_string().c_str());
        
    CHECK(n2 != NULL);
    
    CHECK(n2->getCore() != NULL);
    OSG::GeometryUnrecPtr      geo2 =
        dynamic_cast<OSG::Geometry *>(n2->getCore());
    CHECK(geo2 != NULL);
    
    CHECK(geo2->getMaterial() != NULL);
    OSG::ChunkMaterialUnrecPtr mat2 =
        dynamic_cast<OSG::ChunkMaterial *>(geo2->getMaterial());
    CHECK(mat2 != NULL);    
    
    CHECK(mat2->getChunk(0) != NULL);
    const OSG::TextureChunk *tex2 =
        dynamic_cast<const OSG::TextureChunk *>(mat2->getChunk(0));
    const OSG::TextureObjChunk *texObj =
        dynamic_cast<const OSG::TextureObjChunk *>(mat2->getChunk(0));
    const OSG::TextureEnvChunk *texEnv =
        dynamic_cast<const OSG::TextureEnvChunk *>(mat2->getChunk(1));
    CHECK(tex2   == NULL);    
    CHECK(texObj != NULL);
    CHECK(texEnv != NULL);
    
    CHECK(texObj->getImage() != NULL);
    OSG::Image *img2 = texObj->getImage();
    CHECK(img2 != NULL);
    
    CHECK_EQUAL(255, img2->getData()[0 * 2 * 4 + 0 * 4 + 0]);
    CHECK_EQUAL(  0, img2->getData()[0 * 2 * 4 + 0 * 4 + 1]);
    CHECK_EQUAL(  0, img2->getData()[0 * 2 * 4 + 0 * 4 + 2]);
    CHECK_EQUAL(255, img2->getData()[0 * 2 * 4 + 0 * 4 + 3]);
    
    CHECK_EQUAL(255, img2->getData()[0 * 2 * 4 + 1 * 4 + 0]);
    CHECK_EQUAL(255, img2->getData()[0 * 2 * 4 + 1 * 4 + 1]);
    CHECK_EQUAL(  0, img2->getData()[0 * 2 * 4 + 1 * 4 + 2]);
    CHECK_EQUAL(255, img2->getData()[0 * 2 * 4 + 1 * 4 + 3]);
    
    CHECK_EQUAL(  0, img2->getData()[1 * 2 * 4 + 0 * 4 + 0]);
    CHECK_EQUAL(  0, img2->getData()[1 * 2 * 4 + 0 * 4 + 1]);
    CHECK_EQUAL(255, img2->getData()[1 * 2 * 4 + 0 * 4 + 2]);
    CHECK_EQUAL(255, img2->getData()[1 * 2 * 4 + 0 * 4 + 3]);
    
    CHECK_EQUAL(  0, img2->getData()[1 * 2 * 4 + 1 * 4 + 0]);
    CHECK_EQUAL(255, img2->getData()[1 * 2 * 4 + 1 * 4 + 1]);
    CHECK_EQUAL(255, img2->getData()[1 * 2 * 4 + 1 * 4 + 2]);
    CHECK_EQUAL(255, img2->getData()[1 * 2 * 4 + 1 * 4 + 3]);
}
#endif // OSG_DISABLE_DEPRECATED

} // SUITE
