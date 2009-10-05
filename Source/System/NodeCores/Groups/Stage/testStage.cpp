#include "OSGConfig.h"

#include <iostream>

#include "OSGGLUT.h"

#include "OSGFieldContainerFactory.h"
#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGBoxVolume.h"
#include "OSGLine.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGThread.h"
#include "OSGTransform.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGSimpleGeometry.h"
#include "OSGSceneFileHandler.h"

#include "OSGDirectionalLight.h"

#include "OSGViewport.h"

#include "OSGFBOViewport.h"
#include "OSGFrameBufferObject.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"
#include "OSGOSGWriter.h"
#include "OSGChangeList.h"
#include "OSGIOStream.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGStage.h"
#include "OSGVisitSubTree.h"

#include "OSGTrackball.h"

OSG::RenderAction *rentravact = NULL;

OSG::NodeRecPtr  root;
OSG::NodeRecPtr  animRoot;

OSG::NodeRecPtr  file;

OSG::FBOViewportRecPtr vpScene;
OSG::ViewportRecPtr    vpPlane;

OSG::GLUTWindowRecPtr  win;

OSG::Vec3f           sceneTrans;
OSG::TransformRecPtr cam_transScene;
OSG::TransformRecPtr scene_trans;

OSG::TransformRecPtr cam_transPlane;

OSG::TextureObjChunkRecPtr tx1o;
OSG::TextureEnvChunkRecPtr tx1e;

OSG::Trackball    tball;

OSG::Vec3f min,max;

int mouseb = 0;
int lastx  = 0;
int lasty  = 0;

void display(void)
{
    OSG::Matrix m1, m2, m3;
    OSG::Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
    m2.setTranslate( tball.getPosition() );
    
    m1.mult( m2 );

    cam_transPlane->editSFMatrix()->setValue(m1);


    // Anim

    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME);
    
    m1.setRotate(OSG::Quaternion(OSG::Vec3f(0,1,0), t / 1000.f));


    m1[3][0] = -sceneTrans[0];
    m1[3][1] = -sceneTrans[1];
    m1[3][2] = -sceneTrans[2];

    scene_trans->editSFMatrix()->setValue(m1);

    OSG::Thread::getCurrentChangeList()->commitChanges();

    win->render(rentravact);
}

void reshape(int w, int h)
{
    std::cerr << "Reshape: " << w << "," << h << std::endl;
    win->resize( w, h );
}


void animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void motion(int x, int y)
{   
    OSG::Real32 w = win->getWidth(), h = win->getHeight();
    

    OSG::Real32 a = -2. * ( lastx / w - .5 );
    OSG::Real32 b = -2. * ( .5 - lasty / h );
    OSG::Real32 c = -2. * ( x / w - .5 );
    OSG::Real32 d = -2. * ( .5 - y / h );

    if(mouseb & (1 << GLUT_LEFT_BUTTON))
    {
        tball.updateRotation(a, b, c, d);     
    }
    else if(mouseb & (1 << GLUT_MIDDLE_BUTTON))
    {
        tball.updatePosition(a, b, c, d);     
    }
    else if(mouseb & (1 << GLUT_RIGHT_BUTTON))
    {
        tball.updatePositionNeg(a, b, c, d);  
    }

    lastx = x;
    lasty = y;
}

void mouse(int button, int state, int x, int y)
{
    if(state == 0)
    {
        switch ( button )
        {
            case GLUT_LEFT_BUTTON:  
                break;
            case GLUT_MIDDLE_BUTTON: 
                tball.setAutoPosition(true);
                break;
            case GLUT_RIGHT_BUTTON:
                tball.setAutoPositionNeg(true);
                break;
        }
        mouseb |= 1 << button;
    }
    else if(state == 1)
    {
        switch(button)
        {
            case GLUT_LEFT_BUTTON:  
                break;
            case GLUT_MIDDLE_BUTTON:
                tball.setAutoPosition(false);
                break;
            case GLUT_RIGHT_BUTTON:     
                tball.setAutoPositionNeg(false);
                break;
        }       
        mouseb &= ~(1 << button);
    }

    lastx = x;
    lasty = y;
}

void vis(int visible)
{
    if(visible == GLUT_VISIBLE) 
    {
        glutIdleFunc(animate);
    } 
    else 
    {
        glutIdleFunc(NULL);
    }
}

void key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:   
            delete rentravact;

            root     = NULL;
            animRoot = NULL;

            file     = NULL;

            vpScene  = NULL;
            vpPlane  = NULL;

            win      = NULL;

            cam_transScene = NULL;
            scene_trans    = NULL;

            cam_transPlane = NULL;

            tx1o           = NULL;
            tx1e           = NULL;

            OSG::commitChangesAndClear();

            OSG::osgExit(); 
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
    }
}

void initAnimSetup(int argc, char **argv)
{
    // beacon for camera and light  
    OSG::NodeUnrecPtr  b1n = OSG::Node ::create();
    OSG::GroupUnrecPtr b1  = OSG::Group::create();

    b1n->setCore(b1);

    // transformation

    OSG::NodeUnrecPtr      t1n = OSG::Node     ::create();
    OSG::TransformUnrecPtr t1  = OSG::Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    cam_transScene = t1;

    // light
    
    OSG::NodeUnrecPtr             dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl     = OSG::DirectionalLight::create();

    dlight->setCore(dl);
    
    dl->setAmbient  (.3f, .3f, .3f, 1);
    dl->setDiffuse  ( 1,  1,  1, 1);
    dl->setDirection( 0,  0,  1   );
    dl->setBeacon   (b1n          );

    // root
    OSG::NodeUnrecPtr  root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1  = OSG::Group::create();

    root->setCore (gr1   );

    root->addChild(t1n   );
//    root->addChild(dlight);

    // Load the file

    OSG::NodeUnrecPtr file = NULL;
    
    if(argc > 1)
    {
        file = OSG::SceneFileHandler::the()->read(argv[1]);
    }
        
    if(file == NULL)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

        file = OSG::makeTorus(.5, 2, 16, 16);
    }
    
    OSG::Thread::getCurrentChangeList()->commitChanges();
    file->updateVolume();

    file->dump();

#if 0
    char *outFileName = "/tmp/foo.osg";

    OSG::FileOutStream outFileStream( outFileName );

    if( !outFileStream )
    {
        std::cerr << "Can not open output stream to file: "
                  << outFileName << std::endl;
        return -1;
    }

    std::cerr << "STARTING PRINTOUT:" << std::endl;
    OSGWriter writer( outFileStream, 4 );

//    writer.write( file );

    outFileStream.close();
#endif


    file->getVolume().getBounds(min, max);

    std::cout << "Volume: from " << min << " to " << max << std::endl;

                       scene_trans = OSG::Transform::create();
    OSG::NodeUnrecPtr  sceneTrN    = OSG::Node     ::create();

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(file       );

    dlight->addChild(sceneTrN);


    // Camera
    
    OSG::PerspectiveCameraUnrecPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon(b1n);
    cam->setFov   (OSG::osgDegree2Rad(90));
    cam->setNear  (0.1f);
    cam->setFar   (100000);

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(0,1,0));
    
    // Viewport

    vpScene = OSG::FBOViewport::create();

    vpScene->setCamera    (cam           );
    vpScene->setBackground(bkgnd         );
    vpScene->setRoot      (root          );
    vpScene->setSize      (0, 0, 1, 1);

    OSG::FrameBufferObjectUnrecPtr pFBO = OSG::FrameBufferObject::create();

//    vpScene->setFrameBufferObject(pFBO);

    OSG::TextureBufferUnrecPtr pTexBuffer   = OSG::TextureBuffer::create();
    OSG::RenderBufferUnrecPtr  pDepthBuffer = OSG::RenderBuffer ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

    pTexBuffer->setTexture(tx1o);

    pFBO->setSize(512, 512);
    
    pFBO->setColorAttachment(pTexBuffer, 0);
    pFBO->setDepthAttachment(pDepthBuffer );

    pFBO->editMFDrawBuffers()->clear();
    pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    
    sceneTrans.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                         min[1] + ((max[1] - min[1]) * 0.5), 
                         max[2] + ( max[2] - min[2]) * 4.5 );
    

    animRoot = root;

    OSG::NodeUnrecPtr pStageNode = OSG::Node::create();

    OSG::StageUnrecPtr pStage = OSG::Stage::create();

    pStageNode->setCore(pStage);

    pStage->setRenderTarget(pFBO  );

  
    OSG::VisitSubTreeUnrecPtr pVisit     = OSG::VisitSubTree::create();
    OSG::NodeUnrecPtr         pVisitNode = OSG::Node::create();

    pVisit    ->setSubTreeRoot(dlight);
    pVisitNode->setCore       (pVisit);

    pStageNode->setCore(pStage    );
    pStageNode->addChild(pVisitNode);
  
    root->addChild(pStageNode);
    root->addChild(dlight);
}


void initPlaneSetup(void)
{
    // beacon for camera and light  
    OSG::NodeUnrecPtr  b1n = OSG::Node ::create();
    OSG::GroupUnrecPtr b1  = OSG::Group::create();

    b1n->setCore(b1);

    // transformation

    OSG::NodeUnrecPtr      t1n = OSG::Node     ::create();
    OSG::TransformUnrecPtr t1  = OSG::Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    cam_transPlane = t1;

    // light
    
    OSG::NodeUnrecPtr             dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl     = OSG::DirectionalLight::create();

    dlight->setCore(dl);
    
    dl->setAmbient  (.3f, .3f, .3f, 1);
    dl->setDiffuse  ( 1,  1,  1, 1);
    dl->setDirection( 0,  0,  1   );
    dl->setBeacon   (b1n          );

    // root
    OSG::NodeUnrecPtr  root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1  = OSG::Group::create();

    root->setCore (gr1   );

    root->addChild(t1n     );
    root->addChild(animRoot);
    root->addChild(dlight  );

    // Load the file

    OSG::NodeUnrecPtr file = NULL;
    
    file = OSG::makePlane(10, 10, 5, 5);
    
    OSG::Thread::getCurrentChangeList()->commitChanges();
    file->updateVolume();

    file->dump();

    OSG::GeometryUnrecPtr pGeo = dynamic_cast<OSG::Geometry *>(file->getCore());

    OSG::ImageUnrecPtr pImg = OSG::Image::create();

    pImg->set(OSG::Image::OSG_RGB_PF, 512, 512);

    tx1o->setImage    (pImg      ); 
    tx1o->setMinFilter(GL_LINEAR );
    tx1o->setMagFilter(GL_LINEAR );
    tx1o->setWrapS    (GL_REPEAT );
    tx1o->setWrapT    (GL_REPEAT );
    tx1e->setEnvMode  (GL_REPLACE);

    OSG::SimpleMaterialUnrecPtr mat = OSG::SimpleMaterial::create();
    
    mat->setDiffuse(OSG::Color3f(1,1,1));
    mat->setLit    (false              );
    mat->addChunk  (tx1o               );
    mat->addChunk  (tx1e               );

    pGeo->setMaterial(mat);

#if 0
    char *outFileName = "/tmp/foo.osg";

    OSG::FileOutStream outFileStream( outFileName );

    if( !outFileStream )
    {
        std::cerr << "Can not open output stream to file: "
                  << outFileName << std::endl;
        return -1;
    }

    std::cerr << "STARTING PRINTOUT:" << std::endl;
    OSGWriter writer( outFileStream, 4 );

//    writer.write( file );

    outFileStream.close();
#endif


    file->getVolume().getBounds(min, max);

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    OSG::TransformUnrecPtr scene_trans = OSG::Transform::create();
    OSG::NodeUnrecPtr      sceneTrN    = OSG::Node     ::create();

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(file       );

    dlight->addChild(sceneTrN);


    // Camera
    
    OSG::PerspectiveCameraUnrecPtr cam = OSG::PerspectiveCamera::create();

    cam->setBeacon(b1n);
    cam->setFov   (OSG::osgDegree2Rad(90));
    cam->setNear  (0.1f);
    cam->setFar   (100000);

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(1, 0, 0));
    
    // Viewport

    vpPlane = OSG::Viewport::create();

    vpPlane->setCamera    (cam       );
    vpPlane->setBackground(bkgnd     );
    vpPlane->setRoot      (root      );
    vpPlane->setSize      (0, 0, 1, 1);
}

int main (int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    // GLUT init

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    glutIdleFunc(display);  

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // OSG

    OSG::SceneFileHandler::the()->print();

    // create shared texture

    tx1o = OSG::TextureObjChunk::create();
    tx1e = OSG::TextureEnvChunk::create();

    // create the graph

    initAnimSetup(argc, argv);

    initPlaneSetup();


    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLint glvp[4];

    glGetIntegerv(GL_VIEWPORT, glvp);

    win = OSG::GLUTWindow::create();
    
    win->setGlutId(winid           );
    win->setSize(glvp[2], glvp[3]);

//    win->addPort(vpScene);
    win->addPort(vpPlane);

    win->init();

    // Action
    
    rentravact = OSG::RenderAction::create();

    // tball

    OSG::Vec3f pos;
    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    OSG::Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                       min[1] + (max[1] - min[1]) / 2,
                       min[2] + (max[2] - min[2]) / 2);

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // run...
    
    glutMainLoop();
    
    return 0;
}

