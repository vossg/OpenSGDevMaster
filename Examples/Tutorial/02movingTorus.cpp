// what follows here is the smallest OpenSG programm possible
// most things used here are explained now or on the next few pages, so don't 
// worry if not everythings clear right at the beginning...

// Some needed inlcude files - these will become more, believe me ;)
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// In most cases it is useful to add this line, else every OpenSG command
// must be proceeded by an extra OSG::
OSG_USING_NAMESPACE

// The SimpleSceneManager is a little usefull class which helps us to 
// manage little scenes. It will be discussed in detail later on
SimpleSceneManager *mgr;
TransformRecPtr     transCore;

// we have a forward declarion here, just to sort the code 
int setupGLUT( int *argc, char *argv[] );

int main(int argc, char **argv)
{
    // Init the OpenSG subsystem
    osgInit(argc,argv);
    
    {
        // We create a GLUT Window (that is almost the same for most applications)
        int winid = setupGLUT(&argc, argv);
        GLUTWindowRecPtr gwin= GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        // That will be our whole scene for now : an incredible Torus
        
        NodeRecPtr scene;
        
        // create all that stuff we will need:
        //one geometry and one transform node
        
        NodeRecPtr torus = makeTorus(.5, 2, 16, 16);
        NodeRecPtr transNode = Node::create();
        
        transCore = Transform::create();
        Matrix m;
        
        // now provide some data...
        
        // no rotation at the beginning
        m.setIdentity();
        
        // set the core to the matrix we created
        transCore->setMatrix(m);
        
        // now "insert" the core into the node
        transNode->setCore(transCore);
        // add the torus as a child to
        // the transformation node
        transNode->addChild(torus);
        
        // "declare" the transformation as root
        scene = transNode; 
        
        // Create and setup our little friend - the SSM
        mgr = new SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        commitChanges();
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
    //--------------------------BEGIN_ADD
    Matrix m;
    
    // get the time since the apllication startet
    Real32 time = glutGet(GLUT_ELAPSED_TIME );
    
    // set the rotation
    m.setRotate(Quaternion(Vec3f(0,1,0), time/1000.f));
    
    //apply the new matrix to our transform core
    transCore->setMatrix(m);

    // Ordinarily a call to commitChanges should be placed here, since we
    // modify the scene and therefore invalidate bounding volumes on which
    // rendering depends.
    // Since we are using the SimpleSceneManager though, this is not needed,
    // it calls commitChanges internally (adding the call here anyways would
    // not be a big issue, just slightly inefficient).
    
    //--------------------------END_ADD
    
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
