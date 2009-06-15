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

OSG::NodeRecPtr scene;

// one camera will be used only  - the
// decorators will distinguish of left and right
// eye position
OSG::PerspectiveCameraRecPtr camera;

// we need two viewports - one for the left
// and one for the right eye
OSG::ViewportRecPtr leftViewport;
OSG::ViewportRecPtr rightViewport;

OSG::MultiDisplayWindowRecPtr multiWindow;

OSG::NodeRecPtr camBeacon, lightBeacon, lightNode;

OSG::RenderAction *renderAction;

int setupGLUT( int *argc, char *argv[] );

OSG::NodeTransitPtr createScenegraph(void)
{
    //create geometry - just a simple torus
    OSG::NodeRecPtr torus = OSG::makeTorus(1,5,8,16);
    
    //create transformations & beacons for cameras & light
    camBeacon   = OSG::Node::create();
    lightBeacon = OSG::Node::create();
    
    // the following style is a bit different than from before
    // this is only to remind you that beginEditCP()'s can also
    // be interleaved
        
    //create Transformations
    OSG::TransformRecPtr camTrans, lightTrans;
    
    camTrans   = OSG::Transform::create();
    lightTrans = OSG::Transform::create();
    
    OSG::Matrix camM, lightM;
    camM  .setTransform(OSG::Vec3f(0,  1, 10));
    lightM.setTransform(OSG::Vec3f(1, 10,  2));
    
    camTrans  ->setMatrix(camM  );
    lightTrans->setMatrix(lightM);
    
    camBeacon  ->setCore(camTrans  );
    lightBeacon->setCore(lightTrans);
    // -- end of camera beacon creation
    
    //create the light source
    OSG::DirectionalLightRecPtr dLight = OSG::DirectionalLight::create();
    
    dLight->setDirection(OSG::Vec3f(0,1,2));
    
    //color information
    dLight->setDiffuse (OSG::Color4f(1,   1,   1,   1));
    dLight->setAmbient (OSG::Color4f(0.2, 0.2, 0.2, 1));
    dLight->setSpecular(OSG::Color4f(1,   1,   1,   1));
    
    //set the beacon
    dLight->setBeacon(lightBeacon);
    
    // create the node that will contain the light source
    
    lightNode = OSG::Node::create();
    lightNode->setCore(dLight);
    lightNode->addChild(torus);
    
    // now create the root and add all children
    
    OSG::NodeRecPtr root = OSG::Node::create();
    root->setCore (OSG::GroupRecPtr(OSG::Group::create()));
    root->addChild(lightNode);
    root->addChild(camBeacon);
    root->addChild(lightBeacon);
    
    return OSG::NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    int winid = setupGLUT(&argc, argv);
    
    {
        //create the main window for navigation
        OSG::GLUTWindowRecPtr navWindow = OSG::GLUTWindow::create();
        navWindow->setGlutId(winid);
        navWindow->setSize(300,300);
        navWindow->init();
        
        scene = createScenegraph();
        
        //we beginn with creating our cameras
        camera = OSG::PerspectiveCamera::create();
        
        camera->setBeacon(camBeacon);
        camera->setFov(OSG::osgDegree2Rad(90));
        camera->setNear(0.1);
        camera->setFar(100);
        
        //next we create the backgrounds
        
        OSG::SolidBackgroundRecPtr bkg = OSG::SolidBackground::create();
        bkg->setColor(OSG::Color3f(0,0,0));
        
        leftViewport  = OSG::Viewport::create();
        rightViewport = OSG::Viewport::create();
        
        //the decorator decarates the camera and will create the left eye
        OSG::ShearedStereoCameraDecoratorRecPtr cameraDecorator = 
            OSG::ShearedStereoCameraDecorator::create();
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
        
        multiWindow = OSG::MultiDisplayWindow::create();
        
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
        renderAction = OSG::RenderAction::create();
        
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
        
        OSG::osgExit();
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
