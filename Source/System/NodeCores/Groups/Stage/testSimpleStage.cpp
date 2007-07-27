#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGRenderTraversalAction.h>
#include <OSGSimpleGeometry.h>
#include <OSGSceneFileHandler.h>

#include <OSGDirectionalLight.h>

#include "OSGFBOViewport.h"
#include "OSGFrameBufferObject.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGWindow.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGChangeList.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGSimpleStage.h"
#include "OSGVisitSubTree.h"


#include <OSGSimpleSceneManager.h>
#include <OSGPassiveWindow.h>

using namespace OSG;

//#define USE_DEPTH_TEXTURE 1

SimpleSceneManager    *mgr(NULL);

GroupNodePtr  planeRoot;
GroupNodePtr  animRoot;

Vec3f            sceneTrans;
TransformNodePtr cam_transScene;    // Transofrmation of cam/light/stage
TransformNodePtr sceneXform;        // Rotation of model we are viewing

TextureObjChunkPtr tx1o;       // Texture object to shared
TextureEnvChunkPtr tx1e;       // Texture environment to share

#ifdef USE_DEPTH_TEXTURE
TextureObjChunkPtr txDepth;    // Depth texture
#endif

FrameBufferObjectPtr pFBO;

// ----- Scene structure --- //
/*
         planeRoot:Group[gr1]
      /           |          \  |
dlight:dl b1   animRoot       t1n:Xform[cam_transPlane]
      |                              |
sceneTrN:Xform[scene_trans]   b1n:Group[b1]  cam/light beacon
      |
   plane_node


                  animRoot:Group
                  /              \    |
dlight:DirLight:beacon      cam_transScene:Transform
        |                                |
sceneXform:Transform                beacon:Group
        |
      fileNode:Node

       animRoot
          |
pStage:SimpleStage --> pFBO, cam:b1n
          |
  pVisit:VisitSubTree
          |
        dlight

FrameBufferObject: pFBO    --> pTexBuffer, pDepthBuffer
TextureBuffer: pTexBuffer  --> tx1o
RenderBuffer: pDepthBuffer
*/


void display(void)
{
    Matrix m1;

    // Anim
    Real32 t = glutGet(GLUT_ELAPSED_TIME);
    m1.setTransform(-sceneTrans, Quaternion(Vec3f(0,1,0), t / 1000.f));
    sceneXform->setMatrix(m1);

    OSG::commitChanges();

    mgr->redraw();

    // all done, swap
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    mgr->resize(w,h);
    glutPostRedisplay();
}


void animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            osgExit();
            exit(0);

        case 'a':
            glDisable( GL_LIGHTING );
            std::cerr << "Lighting disabled." << std::endl;
            break;
        case 's':
            glEnable( GL_LIGHTING );
            std::cerr << "Lighting enabled." << std::endl;
            break;
        case 'z':
            glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            std::cerr << "PolygonMode: Point." << std::endl;
            break;
        case 'x':
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            std::cerr << "PolygonMode: Line." << std::endl;
            break;
        case 'c':
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            std::cerr << "PolygonMode: Fill." << std::endl;
            break;
        case 'd':
            std::cerr << "Wrote out scene file." << std::endl;
            OSG::SceneFileHandler::the()->write(planeRoot, "simple_stage_dump.osb");
            break;

        case 'B':
        {
            ImagePtr pImg = tx1o->getImage();

            pImg->set(Image::OSG_RGB_PF, 512, 512);

//            tx1o->imageContentChanged();

//            Window::reinitializeGLObject(tx1o->getGLId());

            pFBO->setSize(512, 512);
        }
        break;

        case 'S':
        {
            ImagePtr pImg = tx1o->getImage();
            
            pImg->set(Image::OSG_RGB_PF, 256, 256);

//            tx1o->imageContentChanged();

//            Window::reinitializeGLObject(tx1o->getGLId());

            pFBO->setSize(256, 256);
        }
        break;
    }
}

// Setup the part of the scene rooted at animRoot
// This includes a file to animate, a beacon for a light,
// and a staged core to render this subtree from the position
// of the light.
void initAnimSetup(int argc, char **argv)
{
    // beacon for light and stage camera
    GroupNodePtr beacon = GroupNodePtr::create();

    // transformation for beacon
    cam_transScene   = TransformNodePtr::create();
    cam_transScene.node()->addChild(beacon);

    // light
    DirectionalLightNodePtr dlight = DirectionalLightNodePtr::create();

    dlight->setAmbient  (.3, .3, .3, 1);
    dlight->setDiffuse  ( 1,  1,  1, 1);
    dlight->setDirection( 0,  0,  1   );
    dlight->setBeacon   (beacon       );

    // animRoot
    animRoot = GroupNodePtr::create();
    animRoot.node()->addChild(cam_transScene   );

    // Load the file and put it in the graph
    // under the sceneXform node.
    NodePtr file = NullFC;

    if(argc > 1)
    { file = SceneFileHandler::the()->read(argv[1]); }

    if(file == NullFC)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus(.5, 2, 16, 16);
    }

    Vec3f min,max;
    OSG::commitChanges();
    file->updateVolume();
    file->dump();
    file->getVolume().getBounds(min, max);

    std::cout << "Volume: from " << min << " to " << max << std::endl;
    sceneTrans.setValues(min[0] + ((max[0] - min[0]) * 0.5),
                         min[1] + ((max[1] - min[1]) * 0.5),
                         max[2] + ( max[2] - min[2]) * 4.5 );


    sceneXform = TransformNodePtr::create();
    sceneXform.node()->addChild(file);
    dlight.node()->addChild(sceneXform);


    // ---- STAGE RENDERING SETUP --- //
    // Camera: setup camera to point from beacon (light pos)
    //   with a 90deg FOV to render the scene
    PerspectiveCameraPtr stage_cam = PerspectiveCamera::create();

    stage_cam->setBeacon(beacon);
    stage_cam->setFov   (osgDegree2Rad(90));
    stage_cam->setNear  (0.1);
    stage_cam->setFar   (100000);

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();
    bkgnd->setColor(Color3f(0,1,0));

    // FBO setup
                         pFBO         = FrameBufferObject::create();
    TextureBufferPtr     pTexBuffer   = TextureBuffer::create();

#ifdef USE_DEPTH_TEXTURE
    TextureBufferPtr     pDepthBuffer = TextureBuffer::create();
    pDepthBuffer->setTexture(txDepth);
#else
    RenderBufferPtr      pDepthBuffer = RenderBuffer ::create();
    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );
#endif


    pTexBuffer->setTexture(tx1o);

    pFBO->setSize(512, 512);
    pFBO->setColorAttachment(pTexBuffer, 0);
    pFBO->setDepthAttachment(pDepthBuffer );

    pFBO->clearDrawBuffers();
    pFBO->pushToDrawBuffers(GL_COLOR_ATTACHMENT0_EXT);

    // Stage core setup
    SimpleStageNodePtr pStage    = SimpleStageNodePtr::create();
    pStage->setRenderTarget(pFBO );
    pStage->setCamera      (stage_cam  );
    pStage->setBackground  (bkgnd);

    // Setup sub-tree visitor
    // - This will setup a graph that will render a subtree during traversal
    VisitSubTreeNodePtr pVisit     = VisitSubTreeNodePtr::create();
    pVisit->setSubTreeRoot(dlight);

    pStage.node()->addChild(pVisit);
    animRoot.node()->addChild(pStage);
    animRoot.node()->addChild(dlight);
}


void initPlaneSetup(void)
{
    // beacon for camera and light
    GroupNodePtr  beacon = GroupNodePtr::create();

    // transformation
    TransformNodePtr cam_transPlane = TransformNodePtr::create();
    cam_transPlane.node()->addChild(beacon);

    // light
    DirectionalLightNodePtr dl = DirectionalLightNodePtr::create();

    dl->setAmbient  (.3, .3, .3, 1);
    dl->setDiffuse  ( 1,  1,  1, 1);
    dl->setDirection( 0,  0,  1   );
    dl->setBeacon   (beacon          );

    // planeRoot
    planeRoot = GroupNodePtr::create();

    planeRoot.node()->addChild(cam_transPlane);
    planeRoot.node()->addChild(animRoot);
    planeRoot.node()->addChild(dl);

    // Create plane to project the staged render
    NodePtr plane_node = makePlane(10, 10, 5, 5);

    // Setup the shared texture and texture environment
    // - Create an empty image so texture can allocate size and memory
    ImagePtr pImg = Image::create();
    pImg->set(Image::OSG_RGB_PF, 512, 512);

    tx1o->setImage    (pImg      );
    tx1o->setMinFilter(GL_LINEAR );
    tx1o->setMagFilter(GL_LINEAR );
    tx1o->setWrapS    (GL_REPEAT );
    tx1o->setWrapT    (GL_REPEAT );

    tx1e->setEnvMode (GL_REPLACE);

#ifdef USE_DEPTH_TEXTURE
    ImagePtr dImg = Image::create();
    dImg->set(Image::OSG_L_PF, 512, 512);

    txDepth->setImage (dImg);
    txDepth->setMinFilter(GL_NEAREST );
    txDepth->setMagFilter(GL_LINEAR );
    txDepth->setWrapS    (GL_CLAMP_TO_EDGE );
    txDepth->setWrapT    (GL_CLAMP_TO_EDGE );
    txDepth->setExternalFormat(GL_DEPTH_COMPONENT);
    txDepth->setInternalFormat(GL_DEPTH_COMPONENT32);
#endif


    // Material for plane
    // - Create a material that will reference the texture and render
    //     it on the plane
    SimpleMaterialPtr mat = SimpleMaterial::create();

    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit    (false         );
#ifdef USE_DEPTH_TEXTURE
    mat->addChunk  (txDepth       );
#else
    mat->addChunk  (tx1o          );
#endif
    mat->addChunk  (tx1e          );

    GeometryPtr pGeo = dynamic_cast<GeometryPtr>(plane_node->getCore());
    pGeo->setMaterial(mat);

    // Finish connecting graph
    TransformNodePtr scene_trans = TransformNodePtr::create();
    scene_trans.node()->addChild(plane_node );

    dl.node()->addChild(scene_trans);

}

int main (int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize(500,500);
    int winid = glutCreateWindow("testSimpleStage");
    glutKeyboardFunc(key);
    //glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
//    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // OSG
    SceneFileHandler::the()->print();

    // create shared texture

    tx1o = TextureObjChunk::create();
    tx1e = TextureEnvChunk::create();
#ifdef USE_DEPTH_TEXTURE
    txDepth = TextureObjChunk::create();
#endif

    // create the graph

    initAnimSetup(argc, argv);
    initPlaneSetup();

    PassiveWindowPtr pwin(PassiveWindow::create());
    pwin->init();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (planeRoot);

    OSG::commitChanges();

    // show the whole scene
    mgr->showAll();

    mgr->setUseTraversalAction(true);

    glutMainLoop();

    return 0;
}

