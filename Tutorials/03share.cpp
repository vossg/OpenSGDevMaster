// OpenSG Tutorial Example: Share
//
// This example shows how to use core sharing to create copies
// of an object, e.g. a geometry, which take up less memory.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>

// new headers: 

// the Group node core
#include <OpenSG/OSGGroup.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// number of copies to create
const UInt16 ncopies = 20;

// a seprate transformation for every copy
TransformPtr trans[ncopies];


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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // create the scene
    
    /*
       Scenegraph nodes in OpenSG consist of two parts: the Node and its Core.
       
       The Node contains the general information that anchors an object in the
       graph: the parent, a list of children, a bounding volume. Note that the
       Node contains a single parent, a Node can only be connected to a graph
       in one place.
       
       There is only one Node class, all nodes in the scenegraph use the same
       Node. The specific information that distinguishes node kinds from each
       other is stored in the NodeCore.

       Consequently there is a different kind of NodeCore for the different
       kinds of functions a node can have. The NodeCore contains all the
       information that the Node doesn't.
       
       NodeCores can be used by multiple Nodes. In this example the Geometry
       NodeCore of the torus is used to display multiple tori.
    */
    
    // this time, create just the core of the geometry
    GeometryPtr torus = makeTorusGeo( .5, 2, 8, 12 );

    // create the scene
    // the scene has a single group with ncopies transformations below,
    // each of these carries a Node that shares the geometry
    
    /*
       The Group NodeCore is the basic type to create the hierarchical graph.
       It does very little to its children, just calls all of them when asked
       to do anything, and collecting their information if necessary.
    */
    
    // create the root Group node
    NodePtr  scene = Node::create();
    GroupPtr g     = Group::create();
    
    scene->setCore(g);
    
    // create the copied geometry nodes and their transformations
    for(UInt16 i = 0; i<ncopies; ++i)
    {
        // create the nodes for the shared Geometry core
        NodePtr geonode = Node::create();
        
        // assign the Core to the Node
        geonode->setCore(torus);

        // add a transformation for every Geometry
        NodePtr transnode = Node::create();
        
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
