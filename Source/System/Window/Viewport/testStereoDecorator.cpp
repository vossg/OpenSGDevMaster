
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGPerspectiveCamera.h>
#include <OSGStereoBufferViewport.h>
#include <OSGColorBufferViewport.h>
#include <OSGShearedStereoCameraDecorator.h>
#include <OSGSceneFileHandler.h>
#include <OSGOSGSceneFileType.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

ShearedStereoCameraDecoratorUnrecPtr decoleft, decoright;
Real32 zpp = 2, ed = 1;

// redraw the window
void display(void)
{   
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
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

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
        case 27:    exit(1);
        case 'a':   zpp /= 1.1;
            break;
        case 's':   zpp *= 1.1;
            break;
        case 'z':   ed /= 1.1;
            break;
        case 'x':   ed *= 1.1;
                break;         
    }
    
    std::cout << "ZPP:" << zpp << " ED:" << ed << std::endl;
    
    decoleft->setEyeSeparation(ed);
    decoleft->setZeroParallaxDistance(zpp);
    
    decoright->setEyeSeparation(ed);
    decoright->setZeroParallaxDistance(zpp);
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    bool stereobuffer = false;
    bool amberblue    = false;

    if(argc >= 2 && !strcmp(argv[1],"-s"))
    {
        stereobuffer = true;
        --argc, ++argv;
    }
    if(argc >= 2 && !strcmp(argv[1],"-a"))
    {
        amberblue = true;
        --argc, ++argv;
    }
    
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
                        (stereobuffer?GLUT_STEREO:0) );
    
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc (reshape );
    glutDisplayFunc (display );
    glutIdleFunc    (display );
    glutMouseFunc   (mouse   );
    glutMotionFunc  (motion  );
    glutKeyboardFunc(keyboard);

    PassiveWindowUnrecPtr pwin = PassiveWindow::create();
    pwin->init();

    // create the scene
    NodeUnrecPtr scene;
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the()->read(argv[1]);
    }
    else
    {
        scene = makeBox(2,2,2, 1,1,1);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // now create the second vp for stereo
    Viewport *vp = pwin->getPort(0);
    
    PerspectiveCamera *cam = dynamic_cast<PerspectiveCamera *>(vp->getCamera());

    cam->setFov   (osgDegree2Rad(60));
    cam->setAspect(1);

    Navigator *nav = mgr->getNavigator();

    nav->setAt(Pnt3f(0,0,0));
    nav->setDistance(1.5);
    
    mgr->showAll();
    
    // create the decorators and the second viewport
    ViewportUnrecPtr vpleft,vpright;
       
    decoleft  = ShearedStereoCameraDecorator::create();
    decoright = ShearedStereoCameraDecorator::create();
    
    decoleft->setEyeSeparation(ed);
    decoleft->setZeroParallaxDistance(zpp);
    decoleft->setLeftEye(true);  
    decoleft->setDecoratee(cam);  
    
    decoright->setEyeSeparation(ed);
    decoright->setZeroParallaxDistance(zpp);
    decoright->setLeftEye(false);  
    decoright->setDecoratee(cam);  

    if(amberblue)
    {
        ColorBufferViewportUnrecPtr svpleft  = ColorBufferViewport::create();
        ColorBufferViewportUnrecPtr svpright = ColorBufferViewport::create();
 
        svpleft->setLeft(0);
        svpleft->setRight(1);
        svpleft->setBottom(0);
        svpleft->setTop(1);
        svpleft->setCamera(decoleft);
        svpleft->setBackground(vp->getBackground());
        svpleft->setRoot(vp->getRoot());
        svpleft->setRed(GL_TRUE);
        svpleft->setGreen(GL_TRUE);
        svpleft->setBlue(GL_FALSE);
        svpleft->setAlpha(GL_TRUE);
 
        svpright->setLeft(0);
        svpright->setRight(1);
        svpright->setBottom(0);
        svpright->setTop(1);
        svpright->setCamera(decoright);
        svpright->setBackground(vp->getBackground());
        svpright->setRoot(vp->getRoot());
        svpright->setRed(GL_FALSE);
        svpright->setGreen(GL_FALSE);
        svpright->setBlue(GL_TRUE);
        svpright->setAlpha(GL_FALSE);
        
        vpleft  = svpleft;
        vpright = svpright;
    }
    else if(stereobuffer)
    {
        StereoBufferViewportUnrecPtr svpleft  = StereoBufferViewport::create();
        StereoBufferViewportUnrecPtr svpright = StereoBufferViewport::create();
 
        svpleft->setLeft(0);
        svpleft->setRight(1);
        svpleft->setBottom(0);
        svpleft->setTop(1);
        svpleft->setCamera(decoleft);
        svpleft->setBackground(vp->getBackground());
        svpleft->setRoot(vp->getRoot());
        svpleft->setLeftBuffer(true);
        svpleft->setRightBuffer(false);
 
        svpright->setLeft(0);
        svpright->setRight(1);
        svpright->setBottom(0);
        svpright->setTop(1);
        svpright->setCamera(decoright);
        svpright->setBackground(vp->getBackground());
        svpright->setRoot(vp->getRoot());
        svpright->setLeftBuffer(false);
        svpright->setRightBuffer(true);
        
        vpleft  = svpleft;
        vpright = svpright;
    }
    else
    {
        vpleft  = vp;
        vpright = Viewport::create();

        vpleft->setLeft(0);
        vpleft->setRight(1);
        vpleft->setBottom(0);
        vpleft->setTop(0.5);

        vpright->setLeft(0);
        vpright->setRight(1);
        vpright->setBottom(0.5);
        vpright->setTop(1);
        vpright->setBackground(vp->getBackground());
        vpright->setRoot(vp->getRoot());
    }
    
    vpleft->setCamera(decoleft);
    
    vpright->setCamera(decoright);
 
    pwin->subPortByObj(vp     );  
    pwin->addPort     (vpleft );  
    pwin->addPort     (vpright);  

    OSGSceneFileType::the().writeContainer(pwin, "/tmp/windowtest.osg");

    // make it notice the changes
    mgr->setWindow(pwin );
    
    // show the whole scene
    mgr->showAll();
    
    // OpenGL info
    GLint val;
    
#define cv(v)\
    glGetIntegerv((v),&val);\
    printf("%s: %d\n", #v, val)
    
    cv(GL_RED_BITS);
    cv(GL_GREEN_BITS);
    cv(GL_BLUE_BITS);
    cv(GL_DEPTH_BITS);
    
    glEnable(GL_DEPTH_TEST);
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
