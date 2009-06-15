// what follows here is the smallest OpenSG programm possible
// most things used here are explained now or on the next few pages, so don't 
// worry if not everythings clear right at the beginning...

// Some needed inlcude files - these will become more, believe me ;)
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// The SimpleSceneManager is a little usefull class which helps us to 
// manage little scenes. It will be discussed in detail later on
OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr          scene;

// we have a forward declarion here, just to sort the code 
int setupGLUT( int *argc, char *argv[] );

// This function will create our scenegraph
OSG::NodeTransitPtr createScenegraph(void)
{
    // we will use the variable to set our trandform matrices
    OSG::Matrix m;
    
    // First we will create all needed geometry
    // the body of the house
    OSG::NodeRecPtr houseMain = OSG::makeBox(20,20,20,1,1,1);
    
    // now the roof
    OSG::NodeRecPtr roof = OSG::makeBox(14.14, 14.14, 20, 1, 1, 1);
    
    // we translate the roof to the correct position
    OSG::TransformRecPtr tRoof = OSG::Transform::create();
    m.setIdentity();
    m.setTranslate(0,10,0);
    m.setRotate(OSG::Quaternion(OSG::Vec3f(0,0,1), 3.14159/4));
    
    tRoof->setMatrix(m);
    
    OSG::NodeRecPtr roofTrans = OSG::Node::create();
    roofTrans->setCore(tRoof);
    roofTrans->addChild(roof);
    
    // and the chimney - we have the top and sides generated
    // but we have no need for the bottom (it is inside the house)
    OSG::NodeRecPtr chimney = OSG::makeCylinder(10,1,8,true,true,false);
    
    //now we translate the chimney
    
    //create the transform core
    OSG::TransformRecPtr tChimney = OSG::Transform::create();
    m.setIdentity();
    // -5 along the x-axis and 2.5 along the z axis
    // translates the chimney away from the center
    // 15 along the y-axis translates the chimney to fit on top
    // of the big box (have a look at the figure above2,5
    m.setTranslate(-5,15,2.5);
    
    tChimney->setMatrix(m);
    
    //insert the transform core into the node
    OSG::NodeRecPtr chimneyTrans  = OSG::Node::create();
    chimneyTrans->setCore(tChimney);
    chimneyTrans->addChild(chimney);

    // Now we create the root node and attach the geometry nodes to it
    OSG::NodeRecPtr n = OSG::Node::create();
    n->setCore(OSG::Group::create());
    n->addChild(houseMain);
    n->addChild(roofTrans);
    n->addChild(chimneyTrans);
    
    return OSG::NodeTransitPtr(n);
}

int main(int argc, char **argv)
{
    // Init the OpenSG subsystem
    OSG::osgInit(argc,argv);
    
    {
        // We create a GLUT Window (that is almost the same for most applications)
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        // That will be our whole scene for now : an incredible Torus
        scene = createScenegraph();
        
        // Create and setup our little friend - the SSM
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        OSG::commitChanges();
    }
    
    // Give Control to the GLUT Main Loop
    glutMainLoop();
    
    return 0;
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// just redraw our scene if this GLUT callback is invoked
void display(void)
{
    mgr->redraw();
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

//The GLUT subsystem is set up here. This is very similar to other GLUT applications
//If you have worked with GLUT before, you may have the feeling of meeting old friends again,
//if you have not used GLUT before that is no problem. GLUT will be introduced shortly on the
//next section

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    return winid;
}
