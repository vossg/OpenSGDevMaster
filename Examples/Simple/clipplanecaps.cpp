// OpenSG example: ClipPlaneCaps
//
// Demonstrates the use of the ClipPlaneChunk, StencilChunk for capping of
// clipped geometry
//
// This examples allows creation of a box and a torus. Additionally, two clip
// planes can be set up. On clipping the geometry caps are used to repair the
// clipped geometry.
//
// User interface:
//  a) mouse => standard navigator
//  b) keyboard =>
//      '1': enable/disable clip plane 0
//      '2': enable/disable clip plane 1
//      '3': enable/disable box geometry
//      '4': enable/disable torus geometry
//      'n': move clip plane 0 opposite to the normal direction of the plane
//      'm': move clip plane 0 in the normal direction of the plane
//      ',': move clip plane 1 opposite to the normal direction of the plane
//      '.': move clip plane 1 in the normal direction of the plane
//      'q': move box in -x direction
//      'w': move box in +x direction
//      'a': move box in -y direction
//      's': move box in +y direction
//      'y': move box in -z direction
//      'x': move box in +z direction
//      'e': move torus in -x direction
//      'r': move torus in +x direction
//      'd': move torus in -y direction
//      'f': move torus in +y direction
//      'c': move torus in -z direction
//      'v': move torus in +z direction
//
// This example was contributed by Johannes Brunen

#include <vector>

#ifdef OSG_BUILD_ACTIVE

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGMultiSwitch.h>
#include <OSGMaterialGroup.h>
#include <OSGGroupingStage.h>
#include <OSGChunkMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGClipPlaneChunk.h>
#include <OSGStencilChunk.h>
#include <OSGInverseTransform.h>
#include <OSGPassiveBackground.h>
#include <OSGFieldContainerUtils.h>
#include <OSGSceneGraphUtils.h>
#include <OSGContainerCollection.h>

#else // OSG_BUILD_ACTIVE

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGMultiSwitch.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGGroupingStage.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGClipPlaneChunk.h>
#include <OpenSG/OSGStencilChunk.h>
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGFieldContainerUtils.h>
#include <OpenSG/OSGSceneGraphUtils.h>
#include <OpenSG/OSGContainerCollection.h>

#endif // OSG_BUILD_ACTIVE


typedef std::vector<OSG::NodeRefPtr> VecNodesT; // convenience type

//
// transport container for the actual clip plane data
//
struct ClipPlaneData
{
    OSG::Vec4f _equation;
    bool       _enabled;
};

typedef std::vector<ClipPlaneData> VecClipPlaneData;

//
// for each clip plane these data are necessary
//
struct ClipPlaneDetails
{
    OSG::ClipPlaneChunkRefPtr  _clipPlaneChunk;
    OSG::GeometryRefPtr        _planeGeometryCore;
    OSG::TransformRefPtr       _planeTrafoCore;
    OSG::NodeRefPtr            _planeBeaconNode;
    OSG::Color3f               _planeColor;
};

typedef std::vector<ClipPlaneDetails> VecClipPlaneDetailsT;

//
// global state
//
VecClipPlaneData      vecClipPlaneData;      // transport clip plane info
VecClipPlaneDetailsT  vecClipPlaneDetails;   // opensg clip plane state
VecNodesT             vecGeometries;         // box and torus

OSG::SimpleSceneManagerRefPtr   mgr;
OSG::NodeRefPtr                 scene;
OSG::ContainerCollectionRefPtr  container;

//
// the number of clipping planes supported by the demo. Define a plane color
// for each.
//
const int iNumClipPlanes = 2;
OSG::Color3f planeCol[iNumClipPlanes] = { OSG::Color3f(0,1,0),
                                          OSG::Color3f(0,0,1) };

//
// Build the global clip plane state
//
void createClipPlaneDetails(void)
{
    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        ClipPlaneDetails details;

        //
        // Create clip plane chunk
        //
        details._planeBeaconNode = OSG::Node::create();
        details._planeBeaconNode->setCore(OSG::Transform::create());

        container->addContainer(details._planeBeaconNode);

        details._clipPlaneChunk = OSG::ClipPlaneChunk::create();
        details._clipPlaneChunk->setEquation(OSG::Vec4f(1,0,0,0));
        details._clipPlaneChunk->setEnable(false);
        details._clipPlaneChunk->setBeacon(details._planeBeaconNode);


        //
        // Create plane geometry
        //
        details._planeGeometryCore = OSG::makePlaneGeo(100.f, 100.f, 128, 128);

        //
        // Create plane transformation core
        //
        OSG::Matrix mat;
        mat.setIdentity();

        details._planeTrafoCore = OSG::Transform::create();
        details._planeTrafoCore->setMatrix(mat);

        //
        // Define plane color
        //
        details._planeColor = planeCol[i];

        vecClipPlaneDetails.push_back(details);
    }
}

//
// Clean up code
//
void cleanup(void)
{
    vecClipPlaneDetails.clear();
    vecGeometries      .clear();

    mgr = NULL;

    scene     = NULL;
    container = NULL;
}

//
// In  case the clip plane data change this function is called
//
void updateClipPlanes(const VecClipPlaneData& vec)
{
    int sz  = vec.size();

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        OSG::ClipPlaneChunk *clipPlaneChunk =
            vecClipPlaneDetails[i]._clipPlaneChunk;

        clipPlaneChunk->setEnable(false);

        if(i < sz)
        {
            const ClipPlaneData& data = vec[i];

            //
            // Update the clip plane chunk
            //
            clipPlaneChunk->setEquation(data._equation);
            clipPlaneChunk->setEnable  (data._enabled );

            //
            // and the plane transform core
            //
            OSG::Matrix rotMat;
            OSG::Vec4f v1(0.f, 0.f, -1.f, 0.f);
            OSG::Quaternion q(OSG::Vec3f(v1), OSG::Vec3f(data._equation));
            rotMat.setTransform(q);

            OSG::Matrix mat;
            OSG::Vec3f v2(0.0f, 0.0f, data._equation[3]);
            mat.setTranslate(v2);

            mat.multLeft(rotMat);

            vecClipPlaneDetails[i]._planeTrafoCore->setMatrix(mat);
        }
    }
}

//
// build geometry scenegraph Tree
//
//
// We need 3 material groups for the clip plane capping trick:
//
//                        scene
//                          |
//     +--------------------+--------------------+
//     |                    |                    |
//  group1 (mat1)        group2 (mat2)        group3 (mat3)
//     |                    |                    |
// geometry (geo1)      geometry (geo2)      geometry (geo1)
//
//    geo1 : actual geometry to draw
//    geo2 : plane geometry coincident with the clip plane
//
//    mat1 : has a stencil chunk that clears the stencil buffer first, than
//           does the inversion, and has a clip plane chunk that enables one
//           clip plane. Sort key 2*i + 0 with i idx of a clip plane.
//    mat2 : has a stencil chunk and settings for drawing the clip plane
//           geometry. All clip planes but the one coincident with the plane
//           are activated. Sort key 2*i + 0 with i idx of a clip plane.
//    mat3 : the material used for the actual geometry. All clip planes are
//           activated. Sort key none.
//
//    For each active clip plane copies of the left two branches need to be
//    added.
//
OSG::NodeTransitPtr buildGeoTree(      OSG::Node     *scene,
                                       OSG::Geometry *geo1,
                                 const OSG::Matrix   &matrix)
{
    //
    // Parent nodes for the left two branches
    //
    VecNodesT vecMaterialNodes1;
    VecNodesT vecMaterialNodes2;

    for(int i = 0; i < iNumClipPlanes; ++i) // foreach clip plane
    {
        //
        // Branch 1: Imprint the geometry clip plane intersection into the
        //           stencil buffer.
        //
        OSG::NodeRefPtr geomNode = OSG::Node::create();
        geomNode->setCore(geo1);

        OSG::NodeRefPtr materialNode1 = OSG::Node::create();
        //
        // Create stencil material core
        //
        OSG::StencilChunkRefPtr stencilChunk1 = OSG::StencilChunk::create();
        stencilChunk1->setClearBuffer(1);
        stencilChunk1->setStencilFunc(GL_NEVER);
        stencilChunk1->setStencilValue(1);
        stencilChunk1->setStencilMask(1);
        stencilChunk1->setStencilOpFail(GL_INVERT);
        stencilChunk1->setStencilOpZFail(GL_INVERT);
        stencilChunk1->setStencilOpZPass(GL_INVERT);

        OSG::ChunkMaterialRefPtr mat1 = OSG::ChunkMaterial::create();
        mat1->addChunk(stencilChunk1);
        mat1->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
        mat1->setSortKey(2 * i + 0);

        OSG::MaterialGroupRefPtr mgrp1 = OSG::MaterialGroup::create();
        mgrp1->setMaterial(mat1);

        materialNode1->setCore(mgrp1);
        materialNode1->addChild(geomNode);  // the primary geometry

        vecMaterialNodes1.push_back(materialNode1);

        //
        // Branch 2: Draw plane at places were the stencil buffer is set
        //
        OSG::NodeRefPtr         materialNode2 = OSG::Node        ::create();
        OSG::StencilChunkRefPtr stencilChunk2 = OSG::StencilChunk::create();

        stencilChunk2->setStencilFunc(GL_EQUAL);
        stencilChunk2->setStencilValue(1);
        stencilChunk2->setStencilMask(1);
        stencilChunk2->setStencilOpFail(GL_KEEP);
        stencilChunk2->setStencilOpZFail(GL_ZERO);
        stencilChunk2->setStencilOpZPass(GL_ZERO);

        OSG::SimpleMaterialRefPtr mat2 = OSG::SimpleMaterial::create();
        mat2->setDiffuse(vecClipPlaneDetails[i]._planeColor);
        mat2->setSpecular(OSG::Color3f(1,1,1));
        mat2->setLit(true);

        //
        // Do clip the plane with all clip planes but the one coincident
        // with the plane.
        //
        for(int j = 0; j < iNumClipPlanes; ++j)
        {
            if(i != j)
            {
                mat2->addChunk(vecClipPlaneDetails[j]._clipPlaneChunk);
            }
        }
        mat2->addChunk(stencilChunk2);
        mat2->setSortKey(2 * i + 1);

        OSG::NodeRefPtr planeGeoNode = OSG::Node::create();
        planeGeoNode->setCore(vecClipPlaneDetails[i]._planeGeometryCore);

        OSG::NodeRefPtr planeTrafoNode = OSG::Node::create();
        planeTrafoNode->setCore(vecClipPlaneDetails[i]._planeTrafoCore);
        planeTrafoNode->addChild(planeGeoNode);

        //
        // Neutralize the summed up transformation at this point in the
        // scenegraph since we are describing the plane in the same frame
        // as the clip planes, i.e. world coordinates.
        //
        OSG::NodeRefPtr planeRootNode = OSG::Node::create();
        planeRootNode->setCore(OSG::InverseTransform::create());
        planeRootNode->addChild(planeTrafoNode);

        OSG::MaterialGroupRefPtr mgrp2 = OSG::MaterialGroup::create();
        mgrp2->setMaterial(mat2);

        materialNode2->setCore(mgrp2);
        materialNode2->addChild(planeRootNode); // plane geometry

        vecMaterialNodes2.push_back(materialNode2);
    }

    //
    // Finally, set up a branch for drawing the primary geometry
    //
    OSG::NodeRefPtr           materialNode3 = OSG::Node          ::create();
    OSG::SimpleMaterialRefPtr mat3          = OSG::SimpleMaterial::create();

    mat3->setDiffuse(OSG::Color3f(1,0,0));
    mat3->setSpecular(OSG::Color3f(1,1,1));
    mat3->setLit(true);

    //
    // Clip the geometry with each clip plane
    //
    for(int i = 0; i < iNumClipPlanes; ++i)\
    {
        mat3->addChunk(vecClipPlaneDetails[i]._clipPlaneChunk);
    }

    OSG::MaterialGroupRefPtr mgrp3 = OSG::MaterialGroup::create();
    mgrp3->setMaterial(mat3);

    OSG::NodeRefPtr geometryNode = OSG::Node::create();
    geometryNode->setCore(geo1);

    materialNode3->setCore (mgrp3);
    materialNode3->addChild(geometryNode);

    //
    // The grouping stage core does suppress a reordering
    // of the render states. This is necessary because the
    // stencil states must be rendered in correct order.
    // There is no state sorting across stages, so that
    // would ensure that everything below a stage is rendered
    // together and the sort key can enforce the right order
    // among those things.
    //
    OSG::NodeRefPtr stageNode = OSG::Node::create();
    stageNode->setCore(OSG::GroupingStage::create());

    OSG::NodeRefPtr clipPlanePartNode = OSG::Node::create();
    clipPlanePartNode->setCore(OSG::Group::create());
    stageNode->addChild(clipPlanePartNode);

    for(int i = 0; i < iNumClipPlanes; ++i)
    {
        clipPlanePartNode->addChild(vecMaterialNodes1[i]);
        clipPlanePartNode->addChild(vecMaterialNodes2[i]);
    }

    //
    // The multi switch core is not actually used in this
    // example. However it could be used to define multiple
    // render branches and selectively activate and deactivate
    // them in a given context.
    //
    OSG::MultiSwitchRefPtr selectCore = OSG::MultiSwitch::create();
    selectCore->setSwitchMode(OSG::MultiSwitch::ALL);

    //
    // Add the branches to some parent node.
    //
    OSG::NodeRefPtr selectNode = OSG::Node::create();
    selectNode->setCore(selectCore);

    selectNode->addChild(stageNode);
    selectNode->addChild(materialNode3);

    //
    // Finally, the geometry should be transformable
    //
    OSG::TransformRefPtr transfCore;
    OSG::NodeRefPtr      transfNode =
    OSG::makeCoredNode<OSG::Transform>(&transfCore);

    transfCore->setMatrix(matrix);
    transfNode->addChild(selectNode); // if using sort keys use this
                                       // instead of the former line.

    return OSG::NodeTransitPtr(transfNode);
}

//
// redraw the window
//
void display(void)
{
    // render

    mgr->redraw();

    // all done, swap
    glutSwapBuffers();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w,h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int, int)
{
    static OSG::Real32 val0 = 0.f;
    static OSG::Real32 val1 = 0.f;

    static OSG::Real32 x1 = 0.f;
    static OSG::Real32 y1 = 0.f;
    static OSG::Real32 z1 = 0.f;

    static OSG::Real32 x2 = 0.f;
    static OSG::Real32 y2 = 0.f;
    static OSG::Real32 z2 = 0.f;

    switch(k)
    {
    case ' ':
        {
            OSG::SceneGraphPrinter sgp(mgr->getRoot());
            sgp.printDownTree(std::cout);
        }
        break;

    case '1':   // enable/disable clip plane 0
        {
            vecClipPlaneData[0]._enabled = !vecClipPlaneData[0]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '2':   // enable/disable clip plane 1
        {
            vecClipPlaneData[1]._enabled = !vecClipPlaneData[1]._enabled;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '3':   // enable/disable box geometry
        {
            if(vecGeometries[0] == NULL)
            {
                OSG::Matrix matrix;
                OSG::Vec3f v(10.f,  0.f, 15.f);
                matrix.setTranslate(v);

                OSG::GeometryRefPtr boxGeo  =
                    OSG::makeBoxGeo(15, 15, 15, 1, 1, 1);

                OSG::NodeRefPtr     boxTree = buildGeoTree(scene,
                                                           boxGeo,
                                                           matrix);

                vecGeometries[0] = boxTree;
                scene->addChild(boxTree);
            }
            else
            {
                scene->subChild(vecGeometries[0]);
                vecGeometries[0] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;
    case '4':   // enable/disable torus geometry
        {
            if (vecGeometries[1] == NULL)
            {
                OSG::Matrix matrix;
                OSG::Vec3f v( 0.f, 10.f, 0.f);
                matrix.setTranslate(v);

                OSG::GeometryRefPtr torusGeo  = OSG::makeTorusGeo(2, 6, 8, 16);
                OSG::NodeRefPtr     torusTree = buildGeoTree(scene,
                                                             torusGeo, matrix);

                vecGeometries[1] = torusTree;
                scene->addChild(torusTree);
            }
            else
            {
                scene->subChild(vecGeometries[1]);
                vecGeometries[1] = NULL;
            }

//             mgr->showAll();
//             mgr->redraw();
        }
        break;

    case '5':
        {
            OSG::SceneFileHandler::the()->write(mgr->getRoot(), 
                                                "clipplane_model.osb", true);
        }
        break;
    case 'n':   // move clip plane 0 opposite to the normal direction of the plane
        {
            val0 -= 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'm':   // move clip plane 0 in the normal direction of the plane
        {
            val0 += 0.2;
            vecClipPlaneData[0]._equation[3] = val0;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case ',':   // move clip plane 1 opposite to the normal direction of the plane
        {
            val1 -= 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case '.':   // move clip plane 1 in the normal direction of the plane
        {
            val1 += 0.2;
            vecClipPlaneData[1]._equation[3] = val1;
            updateClipPlanes(vecClipPlaneData);
        }
        break;
    case 'q':   // move box in -x direction
        {
            x1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'w':   // move box in +x direction
        {
            x1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'a':   // move box in -y direction
        {
            y1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 's':   // move box in +y direction
        {
            y1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'y':   // move box in -z direction
        {
            z1 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'x':   // move box in +z direction
        {
            z1 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v(10.f + x1,  0.f + y1, 15.f + z1);
            matrix.setTranslate(v);

            if(vecGeometries[0] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[0]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'e':   // move torus in -x direction
        {
            x2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'r':   // move torus in +x direction
        {
            x2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'd':   // move torus in -y direction
        {
            y2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'f':   // move torus in +y direction
        {
            y2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'c':   // move torus in -z direction
        {
            z2 -= 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 'v':   // move torus in +z direction
        {
            z2 += 0.2f;

            OSG::Matrix matrix;
            OSG::Vec3f v( 0.f + x2, 10.f + y2, 0.f + z2);
            matrix.setTranslate(v);

            if(vecGeometries[1] != NULL)
            {
                OSG::TransformRefPtr transformCore =
                    dynamic_cast<OSG::Transform *>(vecGeometries[1]->getCore());

                transformCore->setMatrix(matrix);
            }
        }
        break;
    case 27:
        {
            cleanup();

            OSG::osgExit();
            exit(0);
        }
        break;
    }

    glutPostRedisplay();
}

int doMain(int argc, char **argv)
{
    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    OSG::osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    OSG::PassiveWindowRefPtr pwin=OSG::PassiveWindow::create();
    pwin->init();

    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);

    //
    // for storing clipplane beacon we use a container
    // collection attachment which we attach to the scene
    // node. Otherwise the scene could not be saved correctly,
    // as the beacons would be lost.
    //
    container = OSG::ContainerCollection::create();

    //
    // Implementation details:
    //      For each clip plane we provide a ClipPlaneChunk, the plane geometry,
    //      the plane transform core and at least a plane color conveniently in
    //      a vector of type VecClipPlaneDetailsT. The next function call
    //      initializes this data structure.
    //
    createClipPlaneDetails();

    //
    // The scene
    //
    scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addAttachment(container);

    //
    // A place for accessing the box and torus.
    //
    vecGeometries.push_back(NULL);
    vecGeometries.push_back(NULL);

    //
    // Build concrete clipping planes and update the clip plane details.
    //
    ClipPlaneData data1;
    ClipPlaneData data2;

    data1._equation = OSG::Vec4f(0,0,1,0);
    data1._enabled  = true;

    data2._equation = OSG::Vec4f(1,0,0,0);
    data2._enabled  = false;

    vecClipPlaneData.push_back(data1);
    vecClipPlaneData.push_back(data2);

    updateClipPlanes(vecClipPlaneData);

    keyboard('3',-1,-1);
    keyboard('4',-1,-1);

    // tell the manager what to manage
    mgr->setRoot(scene);

    // show the whole scene
    mgr->showAll();
    mgr->redraw();

    pwin->dumpExtensions();

    return 0;
}

int main(int argc, char *argv[])
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    //
    // Clean up the global held data
    //
    cleanup();

    OSG::osgExit();

    return 0;
}
