// OpenSG Tutorial Example: Share
//
// This example shows how to use core sharing to create copies
// of an object, e.g. a geometry, which take up less memory.
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

// the Group node core
#include <OSGGroup.h>
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

// the Group node core
#include <OpenSG/OSGGroup.h>
#endif


// number of copies to create
const OSG::UInt16 ncopies = 20;

// a seprate transformation for every copy
OSG::TransformRefPtr trans[ncopies];


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    for(OSG::UInt16 i=0; i < ncopies; ++i)
    {
        m.setTransform(OSG::Vec3f(
                           OSG::osgSin(t / 1000.f + i * 4 * ncopies / OSG::Pi), 
                           OSG::osgCos(t / 1000.f + i * 6 * ncopies / OSG::Pi), 
                           OSG::osgSin(t / 1000.f + i * 7 * ncopies / OSG::Pi)),
                       OSG::Quaternion(OSG::Vec3f (1,1,0), 
                                       t / 1000.f + i * 4 * ncopies / OSG::Pi));
    
        trans[i]->setMatrix(m);
    }

    OSG::commitChanges();
    
    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin= OSG::GLUTWindow::create();
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
        OSG::GeometryRefPtr torus = OSG::makeTorusGeo( .5, 2, 8, 12 );
    
        // create the scene
        // the scene has a single group with ncopies transformations below,
        // each of these carries a Node that shares the geometry
        
        /*
        The Group NodeCore is the basic type to create the hierarchical graph.
        It does very little to its children, just calls all of them when asked
        to do anything, and collecting their information if necessary.
        */
        
        // create the root Group node
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        // create the copied geometry nodes and their transformations
        for(OSG::UInt16 i = 0; i < ncopies; ++i)
        {
            // create the nodes for the shared Geometry core
            OSG::NodeRefPtr geonode = OSG::Node::create();
            
            // assign the Core to the Node
            geonode->setCore(torus);
    
            // add a transformation for every Geometry
            OSG::NodeRefPtr transnode = OSG::Node::create();
            
            trans[i] = OSG::Transform::create();
            
            transnode->setCore (trans[i]);
            transnode->addChild(geonode );
        
            scene->addChild(transnode);       
        }
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
    
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
            for(OSG::UInt16 i = 0; i < ncopies; ++i)
                trans[i] = NULL;
            
            mgr = NULL;
        
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
