// OpenSG Tutorial Example: Move An Object
//
// This example shows how to use Transform nodes to move objects aroung
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// new headers: 

// some wrappers for standard functions for platform independence, e.g. 
// osgSin, osgCos, osgTan
#include <OpenSG/OSGBaseFunctions.h>

// the transformation node core
#include <OpenSG/OSGTransform.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformRefPtr trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(      osgSin(t / 1000.f), 
                               osgCos(t / 1000.f), 
                               osgSin(t / 1000.f)),
                   Quaternion( Vec3f(0,1,0), 
                               t / 1000.f));
    
    // set the transform's matrix
    
    trans->setMatrix(m);

    commitChanges();

    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers gwin and scene below should
    // go out of scope before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin= GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
    
        NodeRefPtr torus = makeTorus( .5, 2, 16, 32 );
    
        // create the transformation node
        // scenegraph nodes are split into 2 parts: the node and its core
        
        // 1. create the Node
        NodeRefPtr scene = Node::create();
        
        // 2. create the core
        trans = Transform::create();
        
        // 3. associate the core with the node
    
        scene->setCore(trans);
        // add the torus as a child
        scene->addChild(torus);
        
        commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:  
        {
            // clean up global variables
            trans = NULL;
            delete mgr;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
