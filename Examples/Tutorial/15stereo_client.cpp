// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGFileGrabForeground.h>
#include <OpenSG/OSGShearedStereoCameraDecorator.h>
#include <OpenSG/OSGMultiDisplayWindow.h>

OSG_USING_NAMESPACE

NodeRecPtr scene;

// one camera will be used only  - the
// decorators will distinguish of left and right
// eye position
PerspectiveCameraRecPtr camera;

// we need two viewports - one for the left
// and one for the right eye
ViewportRecPtr leftViewport;
ViewportRecPtr rightViewport;

MultiDisplayWindowRecPtr multiWindow;

NodeRecPtr camBeacon, lightBeacon, lightNode;

RenderAction *renderAction;

int setupGLUT( int *argc, char *argv[] );

NodeTransitPtr createScenegraph(void)
{
    //create geometry - just a simple torus
    NodeRecPtr torus = makeTorus(1,5,8,16);
    
    //create transformations & beacons for cameras & light
    camBeacon   = Node::create();
    lightBeacon = Node::create();
    
    // the following style is a bit different than from before
    // this is only to remind you that beginEditCP()'s can also
    // be interleaved
        
    //create Transformations
    TransformRecPtr camTrans, lightTrans;
    
    camTrans   = Transform::create();
    lightTrans = Transform::create();
    
    Matrix camM, lightM;
    camM  .setTransform(Vec3f(0,  1, 10));
    lightM.setTransform(Vec3f(1, 10,  2));
    
    camTrans  ->setMatrix(camM  );
    lightTrans->setMatrix(lightM);
    
    camBeacon  ->setCore(camTrans  );
    lightBeacon->setCore(lightTrans);
    // -- end of camera beacon creation
    
    //create the light source
    DirectionalLightRecPtr dLight = DirectionalLight::create();
    
    dLight->setDirection(Vec3f(0,1,2));
    
    //color information
    dLight->setDiffuse (Color4f(1,   1,   1,   1));
    dLight->setAmbient (Color4f(0.2, 0.2, 0.2, 1));
    dLight->setSpecular(Color4f(1,   1,   1,   1));
    
    //set the beacon
    dLight->setBeacon(lightBeacon);
    
    // create the node that will contain the light source
    
    lightNode = Node::create();
    lightNode->setCore(dLight);
    lightNode->addChild(torus);
    
    // now create the root and add all children
    
    NodeRecPtr root = Node::create();
    root->setCore (GroupRecPtr(Group::create()));
    root->addChild(lightNode);
    root->addChild(camBeacon);
    root->addChild(lightBeacon);
    
    return NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    
    int winid = setupGLUT(&argc, argv);
    
    {
        //create the main window for navigation
        GLUTWindowRecPtr navWindow = GLUTWindow::create();
        navWindow->setGlutId(winid);
        navWindow->setSize(300,300);
        navWindow->init();
        
        scene = createScenegraph();
        
        //we beginn with creating our cameras
        camera = PerspectiveCamera::create();
        
        camera->setBeacon(camBeacon);
        camera->setFov(osgDegree2Rad(90));
        camera->setNear(0.1);
        camera->setFar(100);
        
        //next we create the backgrounds
        
        SolidBackgroundRecPtr bkg = SolidBackground::create();
        bkg->setColor(Color3f(0,0,0));
        
        leftViewport  = Viewport::create();
        rightViewport = Viewport::create();
        
        //the decorator decarates the camera and will create the left eye
        ShearedStereoCameraDecoratorRecPtr cameraDecorator = ShearedStereoCameraDecorator::create();
        cameraDecorator->setLeftEye(true);
        //unit length assume that one unit equals one meter
        cameraDecorator->setEyeSeparation(0.06);
        cameraDecorator->setDecoratee(camera);
        cameraDecorator->setZeroParallaxDistance(2);
        
        leftViewport->setCamera    (cameraDecorator);
        leftViewport->setBackground(bkg);
        leftViewport->setRoot      (scene);
        leftViewport->setSize      (0,0,.5,1);
        
        //thr right decorator for the right eye
        cameraDecorator = OSG::ShearedStereoCameraDecorator::create();
    
        cameraDecorator->setLeftEye(false);
        cameraDecorator->setEyeSeparation(0.06);
        cameraDecorator->setDecoratee(camera);
        cameraDecorator->setZeroParallaxDistance(2);
        
        rightViewport->setCamera    (cameraDecorator);
        rightViewport->setBackground(bkg);
        rightViewport->setRoot      (scene);
        rightViewport->setSize      (.5,0,1,1);
        
        multiWindow = MultiDisplayWindow::create();
        
        multiWindow->setClientWindow(navWindow);
        multiWindow->setConnectionType("Multicast");
        multiWindow->editMFServers()->push_back("Server1");
        multiWindow->editMFServers()->push_back("Server2");
        multiWindow->setHServers(2);
        multiWindow->setVServers(1);
        multiWindow->addPort(leftViewport);
        multiWindow->addPort(rightViewport);
        multiWindow->init();
        
        // add an logo foreground to the right viwport
        
        //and the render action - more on that later
        renderAction = RenderAction::create();
        
        std::cout << "create scenegraph..." << std::endl;
    }
    
    glutMainLoop();
    
    return 0;
}

void reshape(int w, int h)
{
    multiWindow->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    multiWindow->render(renderAction);
    
    //the changelist should be cleared - else things
    //could be copied multiple times
    OSG::Thread::getCurrentChangeList()->clear();
    
    // to ensure a black navigation window
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void motion(int x, int y)
{
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
    switch(k)
    {
    case 27:
    {
        // clean up global variables
        scene = NULL;
        camera = NULL;
        rightViewport = NULL;
        leftViewport  = NULL;
        multiWindow   = NULL;
        camBeacon     = NULL;
        lightBeacon   = NULL;
        lightNode     = NULL;
        
        delete renderAction;
        
        osgExit();
        exit(1);
    }
    break;
    }
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG Navigation Window");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    
    return winid;
}
