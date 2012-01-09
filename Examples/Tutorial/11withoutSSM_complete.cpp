// all needed include files
#ifdef OSG_BUILD_ACTIVE
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSolidBackground.h>
#include <OSGDirectionalLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGTransform.h>
#include <OSGRenderAction.h>
#include <OSGViewport.h>
#include <OSGGradientBackground.h>
#include <OSGTextureBackground.h>
#include <OSGTextureObjChunk.h>
#include <OSGImage.h>
#include <OSGImageForeground.h>
#include <OSGFileGrabForeground.h>
#else
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
#endif

OSG::NodeRecPtr scene;

OSG::PerspectiveCameraRecPtr leftCamera;
OSG::PerspectiveCameraRecPtr rightCamera;

OSG::ViewportRecPtr leftViewport;
OSG::ViewportRecPtr rightViewport;

OSG::WindowRecPtr window;

OSG::NodeRecPtr leftCamBeacon, rightCamBeacon, lightBeacon, lightNode;

OSG::RenderActionRefPtr renderAction;

int setupGLUT(int *argc, char *argv[]);

OSG::NodeTransitPtr createScenegraph(void)
{
    //create geometry - just a simple torus
    OSG::NodeRecPtr torus = OSG::makeTorus(1,5,8,16);
    
    //create transformations & beacons for cameras & light
    leftCamBeacon = OSG::Node::create();
    rightCamBeacon = OSG::Node::create();
    lightBeacon = OSG::Node::create();
    
    // the following style is a bit different than from before
    // this is only to remind you that beginEditCP()'s can also
    // be interleaved
    
    
    //create Transformations
    OSG::TransformRecPtr leftCamTrans, rightCamTrans, lightTrans;
    
    leftCamTrans  = OSG::Transform::create();
    rightCamTrans = OSG::Transform::create();
    lightTrans    = OSG::Transform::create();
    
    OSG::Matrix leftM, rightM, lightM;
    leftM .setTransform(OSG::Vec3f(-5,  6, 10));
    rightM.setTransform(OSG::Vec3f( 5, -6, 10));
    lightM.setTransform(OSG::Vec3f( 1, 10,  2));
    
    leftCamTrans ->setMatrix(leftM );
    rightCamTrans->setMatrix(rightM);
    lightTrans   ->setMatrix(lightM);
    
    leftCamBeacon ->setCore(leftCamTrans );
    rightCamBeacon->setCore(rightCamTrans);
    lightBeacon   ->setCore(lightTrans   );
    // -- end of camera beacon creation
    
    //create the light source
    OSG::DirectionalLightRecPtr dLight = OSG::DirectionalLight::create();
    
    dLight->setDirection(OSG::Vec3f(0,1,2));
    
    //color information
    dLight->setDiffuse(OSG::Color4f(1,1,1,1));
    dLight->setAmbient(OSG::Color4f(0.2,0.2,0.2,1));
    dLight->setSpecular(OSG::Color4f(1,1,1,1));
    
    //set the beacon
    dLight->setBeacon(lightBeacon);
    
    // create the node that will contain the light source
    
    lightNode = OSG::Node::create();
    lightNode->setCore(dLight);
    lightNode->addChild(torus);
    
    // now create the root and add all children
    
    OSG::NodeRecPtr root = OSG::Node::create();
    root->setCore(OSG::Group::create());
    root->addChild(lightNode);
    root->addChild(leftCamBeacon);
    root->addChild(rightCamBeacon);
    root->addChild(lightBeacon);
    
    return OSG::NodeTransitPtr(root);
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
    
        scene = createScenegraph();
    
        //we beginn with creating our cameras
        
        leftCamera  = OSG::PerspectiveCamera::create();
        rightCamera = OSG::PerspectiveCamera::create();
        
        leftCamera->setBeacon(leftCamBeacon);
        leftCamera->setFov(OSG::osgDegree2Rad(90));
        leftCamera->setNear(0.1);
        leftCamera->setFar(100);
        
        rightCamera->setBeacon(rightCamBeacon);
        rightCamera->setFov(OSG::osgDegree2Rad(90));
        rightCamera->setNear(0.1);
        rightCamera->setFar(100);
        
        //next we create the backgrounds
        
        OSG::GradientBackgroundRecPtr leftBkg = 
            OSG::GradientBackground::create();

        leftBkg->addLine(OSG::Color3f(0,0,0),0);
        leftBkg->addLine(OSG::Color3f(1,1,1),1);
        
        // load the image file
        OSG::ImageRecPtr bkgImage = OSG::Image::create();
        bkgImage->read("Data/front.jpg");
        
        // make a texture from the image
        OSG::TextureObjChunkRecPtr bkgTex = OSG::TextureObjChunk::create();
        bkgTex->setImage(bkgImage);
        
        OSG::TextureBackgroundRecPtr rightBkg = 
            OSG::TextureBackground::create();

        rightBkg->setTexture(bkgTex);
        rightBkg->setColor(OSG::Color4f(0.8, 0.8, 0.8, 1.0));
        
        //now the viewports
        
        leftViewport  = OSG::Viewport::create();
        rightViewport = OSG::Viewport::create();
        
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
        OSG::ImageRecPtr frgImage = OSG::Image::create();
        frgImage->read("Data/logo.png");
        
        OSG::ImageForegroundRecPtr imgFrg = OSG::ImageForeground::create();
        //NOTE: the position values are between 0 and 1
        //and are relative to the viewport!
        imgFrg->addImage(frgImage, OSG::Pnt2f(0.1,0));
        
        //add the created foreground by appending it to
        //the vieports foreground multifield
        rightViewport->editMFForegrounds()->push_back(imgFrg);
        
        //create the foreground for screenshot functionality
        OSG::FileGrabForegroundRecPtr fileGrab = 
            OSG::FileGrabForeground::create();

        fileGrab->setActive(false);
        fileGrab->setName("Data/screenshot%04d.jpg");
        
        //add this one to the right viewport, too
        rightViewport->editMFForegrounds()->push_back(fileGrab);
        
        //to make a screenshot the foreground has to be set to active
        //were doing that if the user pressen the 's' key
        //have a look at the keyboard callback function
        
        //and the render action - more on that later
        renderAction = OSG::RenderAction::create();
        
        //create the window now
        
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->setSize(300,300);
        window = gwin;
        
        window->addPort(leftViewport );
        window->addPort(rightViewport);
        
        window->init();
        
        OSG::commitChanges();
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
    OSG::commitChanges();
    
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

void keyboard(unsigned char k, int x, int y)
{
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
            renderAction   = NULL;
            
            OSG::osgExit();
            exit(1);
        }
        break;
    
        case 's':
        {
            // The return value is actually a pointer to on osgPtr class
            // I don't know if that makes much sense at all...
            const OSG::Viewport::MFForegroundsType *fgField = 
                window->getPort(1)->getMFForegrounds();
            
            OSG::FileGrabForegroundRecPtr     fg      = 
                dynamic_cast<OSG::FileGrabForeground *>((*fgField)[1]);
            
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
