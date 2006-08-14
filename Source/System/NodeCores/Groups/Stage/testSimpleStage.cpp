#include <OSGConfig.h>

#include <iostream>

#include <OSGGLUT.h>

#include <OSGFieldContainerFactory.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGLine.h>
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
#include "OSGTextureChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGSimpleStage.h"
#include "OSGVisitSubTree.h"

#include "OSGTrackball.h"

using namespace OSG;

RenderAction          *renact     = NULL;
RenderTraversalAction *rentravact = NULL;

NodePtr  root;
NodePtr  animRoot;

NodePtr  file;

FBOViewportPtr vpScene;
ViewportPtr    vpPlane;

WindowPtr    win;

Vec3f        sceneTrans;
TransformPtr cam_transScene;
TransformPtr scene_trans;

TransformPtr cam_transPlane;

TextureChunkPtr tx1;

Trackball    tball;

Vec3f min,max;

int mouseb = 0;
int lastx  = 0;
int lasty  = 0;

void display(void)
{
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
    m2.setTranslate( tball.getPosition() );
    
    m1.mult( m2 );

    cam_transPlane->editSFMatrix()->setValue(m1);


    // Anim

    Real32 t = glutGet(GLUT_ELAPSED_TIME);
    
    m1.setRotate(Quaternion(Vec3f(0,1,0), t / 1000.f));


    m1[3][0] = -sceneTrans[0];
    m1[3][1] = -sceneTrans[1];
    m1[3][2] = -sceneTrans[2];

    scene_trans->editSFMatrix()->setValue(m1);

    Thread::getCurrentChangeList()->commitChanges();

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
    Real32 w = win->getWidth(), h = win->getHeight();
    

    Real32 a = -2. * ( lastx / w - .5 );
    Real32 b = -2. * ( .5 - lasty / h );
    Real32 c = -2. * ( x / w - .5 );
    Real32 d = -2. * ( .5 - y / h );

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
    }
}

void initAnimSetup(int argc, char **argv)
{
    // beacon for camera and light  
    NodePtr  b1n = Node ::create();
    GroupPtr b1  = Group::create();

    b1n->setCore(b1);

    // transformation

    NodePtr      t1n = Node     ::create();
    TransformPtr t1  = Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    cam_transScene = t1;

    // light
    
    NodePtr             dlight = Node::create();
    DirectionalLightPtr dl     = DirectionalLight::create();

    dlight->setCore(dl);
    
    dl->setAmbient  (.3, .3, .3, 1);
    dl->setDiffuse  ( 1,  1,  1, 1);
    dl->setDirection( 0,  0,  1   );
    dl->setBeacon   (b1n          );

    // root
    NodePtr  root = Node::create();
    GroupPtr gr1  = Group::create();

    root->setCore (gr1   );

    root->addChild(t1n   );
//    root->addChild(dlight);

    // Load the file

    NodePtr file = NullFC;
    
    if(argc > 1)
    {
        file = SceneFileHandler::the()->read(argv[1]);
    }
        
    if(file == NullFC)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;

        file = makeTorus(.5, 2, 16, 16);
    }
    
    Thread::getCurrentChangeList()->commitChanges();
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

             scene_trans = Transform::create();
    NodePtr  sceneTrN    = Node     ::create();

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(file       );

    dlight->addChild(sceneTrN);


    // Camera
    
    PerspectiveCameraPtr cam = PerspectiveCamera::create();

    cam->setBeacon(b1n);
    cam->setFov   (deg2rad(90));
    cam->setNear  (0.1);
    cam->setFar   (100000);

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

    bkgnd->setColor(Color3f(0,1,0));
    
    // Viewport


    FrameBufferObjectPtr pFBO = FrameBufferObject::create();


    TextureBufferPtr pTexBuffer   = TextureBuffer::create();
    RenderBufferPtr  pDepthBuffer = RenderBuffer ::create();

    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

    pTexBuffer->setTexture(tx1);

    pFBO->setSize(512, 512);
    
    pFBO->setColorAttachment(pTexBuffer, 0);
    pFBO->setDepthAttachment(pDepthBuffer );

    pFBO->editMFDrawBuffers()->clear();
    pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

    sceneTrans.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                         min[1] + ((max[1] - min[1]) * 0.5), 
                         max[2] + ( max[2] - min[2]) * 4.5 );
    

    animRoot = root;

    NodePtr pStageNode = Node::create();

    SimpleStagePtr pStage = SimpleStage::create();

    pStageNode->setCore(pStage);

    pStage->setRenderTarget(pFBO );
    pStage->setCamera      (cam  );
    pStage->setBackground  (bkgnd);

    VisitSubTreePtr pVisit     = VisitSubTree::create();
    NodePtr         pVisitNode = Node::create();

    pVisit    ->setSubTreeRoot(dlight);
    pVisitNode->setCore       (pVisit);

    pStageNode->addChild(pVisitNode);
    
    root->addChild(pStageNode);
    root->addChild(dlight);
}


void initPlaneSetup(void)
{
    // beacon for camera and light  
    NodePtr  b1n = Node ::create();
    GroupPtr b1  = Group::create();

    b1n->setCore(b1);

    // transformation

    NodePtr      t1n = Node     ::create();
    TransformPtr t1  = Transform::create();

    t1n->setCore (t1 );
    t1n->addChild(b1n);

    cam_transPlane = t1;

    // light
    
    NodePtr             dlight = Node::create();
    DirectionalLightPtr dl     = DirectionalLight::create();

    dlight->setCore(dl);
    
    dl->setAmbient  (.3, .3, .3, 1);
    dl->setDiffuse  ( 1,  1,  1, 1);
    dl->setDirection( 0,  0,  1   );
    dl->setBeacon   (b1n          );

    // root
    NodePtr  root = Node::create();
    GroupPtr gr1  = Group::create();

    root->setCore (gr1   );

    root->addChild(t1n     );
    root->addChild(animRoot);
    root->addChild(dlight  );

    // Load the file

    NodePtr file = NullFC;
    
    file = makePlane(10, 10, 5, 5);
    
    Thread::getCurrentChangeList()->commitChanges();
    file->updateVolume();

    file->dump();

    GeometryPtr pGeo = cast_dynamic<GeometryPtr>(file->getCore());

    UChar8 imgdata[] =
    {  
        64,64,64, 128,128,128, 192,192,192, 255,255,255 
    };

    ImagePtr pImg = Image::create();

    pImg->set(Image::OSG_RGB_PF, 512, 512);

    tx1->setImage    (pImg      ); 
    tx1->setMinFilter(GL_LINEAR );
    tx1->setMagFilter(GL_LINEAR );
    tx1->setWrapS    (GL_REPEAT );
    tx1->setWrapT    (GL_REPEAT );
    tx1->setEnvMode  (GL_REPLACE);

    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit    (false         );
    mat->addChunk  (tx1           );

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

    TransformPtr scene_trans = Transform::create();
    NodePtr      sceneTrN    = Node     ::create();

    sceneTrN->setCore (scene_trans);
    sceneTrN->addChild(file       );

    dlight->addChild(sceneTrN);


    // Camera
    
    PerspectiveCameraPtr cam = PerspectiveCamera::create();

    cam->setBeacon(b1n);
    cam->setFov   (deg2rad(90));
    cam->setNear  (0.1);
    cam->setFar   (100000);

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

    bkgnd->setColor(Color3f(1, 0, 0));
    
    // Viewport

    vpPlane = Viewport::create();

    vpPlane->setCamera    (cam       );
    vpPlane->setBackground(bkgnd     );
    vpPlane->setRoot      (root      );
    vpPlane->setSize      (0, 0, 1, 1);
}

int main (int argc, char **argv)
{
    osgInit(argc,argv);
    
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

    SceneFileHandler::the()->print();

    // create shared texture

    tx1 = TextureChunk::create();

    // create the graph

    initAnimSetup(argc, argv);

    initPlaneSetup();


    // Window
    std::cout << "GLUT winid: " << winid << std::endl;

    GLUTWindowPtr gwin;

    GLint glvp[4];

    glGetIntegerv(GL_VIEWPORT, glvp);

    gwin = GLUTWindow::create();

    gwin->setId  (winid           );
    gwin->setSize(glvp[2], glvp[3]);

    win = gwin;

//    win->addPort(vpScene);
    win->addPort(vpPlane);

    win->init();

    // Action
    
    renact = RenderAction::create();
//    renact->setFrustumCulling(false);

    rentravact = RenderTraversalAction::create();

    // tball

    Vec3f pos;
    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                  min[1] + (max[1] - min[1]) / 2,
                  min[2] + (max[2] - min[2]) / 2);

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // run...
    
    glutMainLoop();
    
    return 0;
}

