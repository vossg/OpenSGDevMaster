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
#include <OpenSG/OSGTextureBackground.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGFileGrabForeground.h>

OSG_USING_NAMESPACE

NodeRecPtr scene;

PerspectiveCameraRecPtr leftCamera;
PerspectiveCameraRecPtr rightCamera;

ViewportRecPtr leftViewport;
ViewportRecPtr rightViewport;

WindowRecPtr window;

NodeRecPtr leftCamBeacon, rightCamBeacon, lightBeacon, lightNode;

RenderAction *renderAction;

int setupGLUT(int *argc, char *argv[]);

NodeTransitPtr createScenegraph(void)
{
    //create geometry - just a simple torus
    NodeRecPtr torus = makeTorus(1,5,8,16);
    
    //create transformations & beacons for cameras & light
    leftCamBeacon = Node::create();
    rightCamBeacon = Node::create();
    lightBeacon = Node::create();
    
    // the following style is a bit different than from before
    // this is only to remind you that beginEditCP()'s can also
    // be interleaved
    
    
    //create Transformations
    TransformRecPtr leftCamTrans, rightCamTrans, lightTrans;
    
    leftCamTrans  = Transform::create();
    rightCamTrans = Transform::create();
    lightTrans    = Transform::create();
    
    Matrix leftM, rightM, lightM;
    leftM .setTransform(Vec3f(-5,  6, 10));
    rightM.setTransform(Vec3f( 5, -6, 10));
    lightM.setTransform(Vec3f( 1, 10,  2));
    
    leftCamTrans ->setMatrix(leftM );
    rightCamTrans->setMatrix(rightM);
    lightTrans   ->setMatrix(lightM);
    
    leftCamBeacon ->setCore(leftCamTrans );
    rightCamBeacon->setCore(rightCamTrans);
    lightBeacon   ->setCore(lightTrans   );
    // -- end of camera beacon creation
    
    //create the light source
    DirectionalLightRecPtr dLight = DirectionalLight::create();
    
    dLight->setDirection(Vec3f(0,1,2));
    
    //color information
    dLight->setDiffuse(Color4f(1,1,1,1));
    dLight->setAmbient(Color4f(0.2,0.2,0.2,1));
    dLight->setSpecular(Color4f(1,1,1,1));
    
    //set the beacon
    dLight->setBeacon(lightBeacon);
    
    // create the node that will contain the light source
    
    lightNode = Node::create();
    lightNode->setCore(dLight);
    lightNode->addChild(torus);
    
    // now create the root and add all children
    
    NodeRecPtr root = Node::create();
    root->setCore(Group::create());
    root->addChild(lightNode);
    root->addChild(leftCamBeacon);
    root->addChild(rightCamBeacon);
    root->addChild(lightBeacon);
    
    return NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
    
        scene = createScenegraph();
    
        //we beginn with creating our cameras
        
        leftCamera  = PerspectiveCamera::create();
        rightCamera = PerspectiveCamera::create();
        
        leftCamera->setBeacon(leftCamBeacon);
        leftCamera->setFov(osgDegree2Rad(90));
        leftCamera->setNear(0.1);
        leftCamera->setFar(100);
        
        rightCamera->setBeacon(rightCamBeacon);
        rightCamera->setFov(osgDegree2Rad(90));
        rightCamera->setNear(0.1);
        rightCamera->setFar(100);
        
        //next we create the backgrounds
        
        GradientBackgroundRecPtr leftBkg = GradientBackground::create();
        leftBkg->addLine(Color3f(0,0,0),0);
        leftBkg->addLine(Color3f(1,1,1),1);
        
        // load the image file
        ImageRecPtr bkgImage = Image::create();
        bkgImage->read("Data/front.jpg");
        
        // make a texture from the image
        TextureObjChunkRecPtr bkgTex = TextureObjChunk::create();
        bkgTex->setImage(bkgImage);
        
        TextureBackgroundRecPtr rightBkg = TextureBackground::create();
        rightBkg->setTexture(bkgTex);
        rightBkg->setColor(Color4f(0.8, 0.8, 0.8, 1.0));
        
        //now the viewports
        
        leftViewport  = Viewport::create();
        rightViewport = Viewport::create();
        
        leftViewport->setCamera(leftCamera);
        leftViewport->setBackground(leftBkg);
        leftViewport->setRoot(scene);
        leftViewport->setSize(0,0,0.5,1);
        
        rightViewport->setCamera(rightCamera);
        rightViewport->setBackground(rightBkg);
        rightViewport->setRoot(scene);
        rightViewport->setSize(0.5,0,1,1);
        
        // -- end of viewport creation
        
        // add an logo foreground to the right viwport
        
        //load the logo image file
        ImageRecPtr frgImage = Image::create();
        frgImage->read("Data/logo.png");
        
        ImageForegroundRecPtr imgFrg = ImageForeground::create();
        //NOTE: the position values are between 0 and 1
        //and are relative to the viewport!
        imgFrg->addImage(frgImage, Pnt2f(0.1,0));
        
        //add the created foreground by appending it to
        //the vieports foreground multifield
        rightViewport->editMFForegrounds()->push_back(imgFrg);
        
        //create the foreground for screenshot functionality
        FileGrabForegroundRecPtr fileGrab = FileGrabForeground::create();
        fileGrab->setActive(false);
        fileGrab->setName("Data/screenshot%04d.jpg");
        
        //add this one to the right viewport, too
        rightViewport->editMFForegrounds()->push_back(fileGrab);
        
        //to make a screenshot the foreground has to be set to active
        //were doing that if the user pressen the 's' key
        //have a look at the keyboard callback function
        
        //and the render action - more on that later
        renderAction = RenderAction::create();
        
        //create the window now
        
        GLUTWindowRecPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->setSize(300,300);
        window = gwin;
        
        window->addPort(leftViewport );
        window->addPort(rightViewport);
        
        window->init();
        
        commitChanges();
    }
    
    glutMainLoop();
    
    return 0;
}

void reshape(int w, int h)
{
    window->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    commitChanges();
    
    window->render(renderAction);
}

void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void motion(int x, int y)
{
    //mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
    switch(k)
    {
    case 27:
    {
        // clean up global variables
        scene          = NULL;
        window         = NULL;
        leftCamera     = NULL;
        rightCamera    = NULL;
        leftViewport   = NULL;
        rightViewport  = NULL;
        leftCamBeacon  = NULL;
        rightCamBeacon = NULL;
        lightBeacon    = NULL;
        lightNode      = NULL;
        
        delete renderAction;
        
        osgExit();
        exit(1);
    }
    break;
    
    case 's':
    {
        // The return value is actually a pointer to on osgPtr class
        // I don't know if that makes much sense at all...
        const Viewport::MFForegroundsType *fgField = window->getPort(1)->getMFForegrounds();
              FileGrabForegroundRecPtr     fg      = dynamic_cast<FileGrabForeground *>((*fgField)[1]);
        
        if (!fg->getActive())
        {
            std::cout << "start recording..." << std::endl;
            fg->setActive(true);
        }
        else
        {
            std::cout << "stopped" << std::endl;
            fg->setActive(false);
        }
    }
    break;
    }
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    
    return winid;
}
