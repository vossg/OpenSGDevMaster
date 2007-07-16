// OpenSG Tutorial Example: Hierarchical Transformation
//
// This example demonstrates how transformations accumulate through the graph.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// number of copies to create
const UInt16 ncopies = 10;

// just use a single transformation that is shared
TransformPtr trans;


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(0, .9, 0),
                   Quaternion( Vec3f(1,1,0), osgSin(t / 1000.f) / 2.f));
    
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

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // create the scene

    /*
        Transformation accumulate through the graph, i.e. all nodes below
        a Transformation are influenced by it, even other Transformations.
        
        This can be used to create models of objects that move together and
        in relation to each other, the prime examples being a robot arm and
        a planetary system. This example does something not quite unlike a
        robot arm.
    */    

    // create the scene
    
    /*
       This time the graph is not wide, but deep, i.e. every Transformation
       only has two children, a Geometry and another transformation.
       The end resulting motion of the geometry is the accumulation of
       all the Transformations above it.
    */
     
    // use a cylinder this time
    GeometryPtr cyl = makeCylinderGeo( 1, .3, 8, true, true, true );
    
    // the single transformation Core used
    trans = Transform::create();
    
    // setup an intial transformation
    Matrix m;
    m.setTransform(Vec3f(0, .9, 0));

    trans->setMatrix(m);
    
    /*
       NullFC is the generic NULL value for FieldContainer pointer.
    */
    NodePtr last = NullFC;
    
    // create the copied transformations and their geometry nodes
    for(UInt16 i = 1; i < ncopies; ++i)
    {
        // create the shared Geometry
        NodePtr geonode = Node::create();
        geonode->setCore(cyl);

        // add a transformation to the Geometry
        NodePtr transnode = Node::create();

        transnode->setCore (trans);
        transnode->addChild(geonode );
        if(last != NullFC)
        {
            transnode->addChild(last);       
        }
       
        last = transnode;
    }
 
    NodePtr scene = last;

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
