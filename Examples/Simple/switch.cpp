// OpenSG Tutorial Example: Switch
//
// This example shows how to use the Switch NodeCore to selectively display one
// of a number of children of a node.
//
// You can use the keys 1-0 to display a single node, 'a' to select all nodes
// and 'n' to select none.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>

// new headers: 

// the Switch node core
#include <OSGSwitch.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>

// new headers: 

// the Switch node core
#include <OpenSG/OSGSwitch.h>
#endif


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// the Switch Core
SwitchRefPtr sw;

// number of copies to create
const UInt16 ncopies = 10;

// Transforms to move the nodes
TransformRefPtr trans[ncopies];


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
    
    // set the transforms' matrices
    for(UInt16 i=0; i<ncopies; ++i)
    {
        m.setTransform(Vec3f(      osgSin(t / 1000.f + i * 4 * ncopies / Pi), 
                                   osgCos(t / 1000.f + i * 6 * ncopies / Pi), 
                                   osgSin(t / 1000.f + i * 7 * ncopies / Pi)),
                       Quaternion( Vec3f (1,1,0), 
                                          t / 1000.f + i * 4 * ncopies / Pi));
    
        trans[i]->setMatrix(m);
    }
    
    commitChanges();
    
    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
    
        // the connection between GLUT and OpenSG
        GLUTWindowRefPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        
        // this time, create just the core of the geometry
        GeometryRefPtr torus = makeTorusGeo( .5, 2, 8, 12 );
    
        // create the scene
        // the scene has a single group with ncopies transformations below,
        // each of these carries a Node that shares the geometry
        
        /*
        The Switch NodeCore very similar to the Group, but it has the additional
        capability to only show one or none of its children.
        
        This is controlled by the choice Field, and is used below in the keys
        function.
        */
        
        // create the root Switch node
        NodeRefPtr  scene = Node::create();
        
        sw = Switch::create();
        sw->setChoice(Switch::ALL);
        
        scene->setCore(sw);
        
        // create the copied geometry nodes and their transformations
        for(UInt16 i = 0; i<ncopies; ++i)
        {
            // create the nodes for the shared Geometry core
            NodeRefPtr geonode = Node::create();
            
            // assign the Core to the Node
            geonode->setCore(torus);
    
            // add a transformation for every Geometry
            NodeRefPtr transnode = Node::create();
            
            trans[i] = Transform::create();
            
            transnode->setCore (trans[i]);
            transnode->addChild(geonode );

            scene->addChild(transnode);
        }
        
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
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            for(UInt32 i = 0; i < ncopies; ++i)
                trans[i] = NULL;
            
            sw = NULL;
            delete mgr;
            
            osgExit();
            exit(1);
        }
        break;

        case '0':   case '1':   case '2':   case '3':   case '4':   
        case '5':   case '6':   case '7':   case '8':   case '9': 
        {   
            sw->setChoice(k - '0');
            break;
        }
        break;

        case 'a':
        {
            sw->setChoice(Switch::ALL); 
        }
        break;

        case 'n':
        {
            sw->setChoice(Switch::NONE); 
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
    glutIdleFunc(update);

    return winid;
}
