// OpenSG Tutorial Example: Traverse & Attachments
//
// This example shows how to traverse the graph and work on each node. 
// The traverse() functions can be used for that. They need functors to pass
// the functions to be called around, which are also introduced here.
//
// It also shows how to downcast pointers in OpenSG to get from a generic
// pointer, e.g. a NodeCorePtr to the specific class, e.g. GeometryPtr.
//
// The graphical display is just for show, the interesting stuff is 
// printed to the console. ;)
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
#include <OSGGroup.h>

// new headers: 

// the Action header, containing the traverse() functions
#include <OSGAction.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 

// the Action header, containing the traverse() functions
#include <OpenSG/OSGAction.h>
#endif

// boost::bind - to allow member functions as traversal functors
#include <boost/bind.hpp>

// a separate transformation for every object
OSG::TransformRefPtr cyltrans, tortrans;


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME);
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0,
                              0, 
                              OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion(OSG::Vec3f (1, 0, 0), 
                                   t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 2000.f), 
                              0, 
                              0),
                   OSG::Quaternion(OSG::Vec3f (0, 0, 1), 
                                   t / 2000.f));

    tortrans->setMatrix(m);
    
    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

/* 
    The traverse() functions used below need a function that is called for
    every node encountered. There are two variants.
    
    One just calls one function when it enters the node. The other in addition
    calls another function when it leaves the node on the way up, i.e. after
    all children of the node have been processed.
    
    The return values define how the traversal continues after this function.
    
    Returning Action::Continue will just continue the traversal. Action::Skip
    will not go deeper but skip all children of this node (and their children
    etc.). Action::Quit will abort the traversal on the spot and just unwind
    the enters on the way up.
    
    You may notice that the traversal functions do not take NodeRefPtr
    arguments, but raw Node * instead. This is true for all OpenSG functions
    and prevents unecessary increments/decrements of the reference count only
    to pass a pointer to a function.
    Note that this works because the objects are alive for the duration of
    the function call anyways. If the arguments to a function are stored in
    some data structure to be used later (e.g. from a different function) you
    should store the pointer in a RefPtr to prevent the object from being
    destroyed.
*/

// these are the trivial traversal function, they just print and return
OSG::Action::ResultE enter(OSG::Node *node)
{
    SLOG << "entering " << node << OSG::endLog;

    return OSG::Action::Continue; 
}

OSG::Action::ResultE leave(OSG::Node *node, OSG::Action::ResultE res) 
{
    SLOG << "leaving " << node << ", got code " << res << OSG::endLog;

    // you should return the result that you're passed, to propagate Quits
    return res; 
}

// This is an example of a traversal state object

class travstate
{
  public:
  
    travstate( void ) : _indent(0) {}
    
    OSG::Action::ResultE enter(OSG::Node *node)
    {
        for(OSG::UInt16 i = 0; i < _indent; i++)
            SLOG << "    ";

        SLOG << "entering " << node << OSG::endLog;

        ++_indent;
        return OSG::Action::Continue;        
    }
    
    OSG::Action::ResultE leave(OSG::Node *node, OSG::Action::ResultE res)
    {
        --_indent;
        
        for(OSG::UInt16 i = 0; i < _indent; i++)
            SLOG << "    ";

        SLOG << "leaving " << node << OSG::endLog;

        // you should return the result that you're passed, to propagate Quits
        return res;
    }
    
  private:
  
    OSG::UInt16 _indent;
};

// a traversal functions that does not descend below transformations

/*
    It also shows how to access the node core of a given node. After making
    sure that the core is indeed the expected type (using the isDerivedFrom())
    call use <FieldContainerTyep>Ptr::dcast() to downcast the core. ::dcast()
    acts comparable to dynamic_cast. dcast() works for all kinds of field
    containers and is not restricted to Nodes or NodeCores.
*/

OSG::Action::ResultE dontEnterTrans(OSG::Node *node)
{   
    SLOG << "entering " << node << OSG::endLog;

    if(node->getCore()->getType().isDerivedFrom(OSG::Transform::getClassType()))
    {
        OSG::Transform *t = dynamic_cast<OSG::Transform *>(node->getCore());
        
        SLOG << "derived from transform, skipping children" << OSG::endLog;
        SLOG << "Matrix: " << OSG::endLog << t->getMatrix();
        return OSG::Action::Skip;
    }   
    return OSG::Action::Continue; 
}


// a traversal functions that quits as soon as it finds a Geometry

/*
    This function uses the fact that ::dcast() acts like dynamic_cast. It tries
    to dcast the core to a GeometryPtr, and tests the result to see if it
    actually was derived from Geometry.
*/

OSG::Action::ResultE quitGeo(OSG::Node *node)
{   
    SLOG << "entering " << node << OSG::endLog;

    OSG::Geometry *geo = dynamic_cast<OSG::Geometry *>(node->getCore());
    
    if(geo != NULL)
    {
        SLOG << "derived from geometry, quitting" << OSG::endLog;
        return OSG::Action::Quit;
    }   
    return OSG::Action::Continue; 
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
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        
        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene group
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        // The cylinder and its transformation
        OSG::NodeRefPtr cyl = OSG::makeCylinder( 1.4f, .3f, 8, true, true, true );
            
        cyltrans = OSG::Transform::create();
    
        OSG::NodeRefPtr cyltransnode = OSG::Node::create();

        cyltransnode->setCore (cyltrans);
        cyltransnode->addChild(cyl     );
        
        // add it to the scene
        scene->addChild(cyltransnode);
        
        // The torus and its transformation
        OSG::NodeRefPtr torus = OSG::makeTorus( .2f, 1, 8, 12 );
            
        tortrans = OSG::Transform::create();
    
        OSG::NodeRefPtr tortransnode = OSG::Node::create();
        
        tortransnode->setCore (tortrans);
        tortransnode->addChild(torus   );
        
        // add it to the scene
        scene->addChild(tortransnode);
        
        // now traverse the scene
        
        /*
            There are four variants of the traverse() function.
            
            It can either be called for a single node or for a vector nodes. And
            they can either call a function just when entering the node, or in
            addition when leaving the node. The signatures of the functions are:
            
            enter functions: 
                Action::ResultE enter(Node *node);
                
            leave functions: 
                Action::ResultE leave(Node *node, Action::ResultE res);
        
            The functions that are called are wrapped in functors. A functor is an
            object that contains a function or method, which can be called through
            the functor. OpenSG uses boost::function for this purpose and
            provides appriopriate typedefs for enter and leave functors as
            TraverseEnterFunctor and TraverseLeaveFunctor (see OSGAction.h).
            
            In order to call member functions through a functor an object of
            the correct type has to be available (there has to an object to
            take the role of this for the member function). To store an
            instance of an object in a functor use boost::bind to bind the
            first argument of the member function functor to the object (see
            below for examples).
        */
        
        SLOG << "Variant 1: just print every encountered node" << OSG::endLog;
        traverse(scene, enter);
        
        SLOG << OSG::endLog 
             << "Variant 2: just print every encountered node, using a" 
             << " vector of nodes" << OSG::endLog;
            
        std::vector<OSG::Node *> nodevec;
        nodevec.push_back(tortransnode);
        nodevec.push_back(cyltransnode);
        
        traverse(nodevec, enter);
        
        SLOG << OSG::endLog 
             << "Variant 3: just print every encountered node on entering"
             << " and leaving" << OSG::endLog;
    
        traverse(scene, enter, leave);
        
        // now use a travstate object to hold additional data   
        travstate t;
        
        SLOG << OSG::endLog 
                << "Variant 4: use an object to hold state for indentation" 
                << OSG::endLog;
        traverse(scene, boost::bind(&travstate::enter, &t, _1    ),
                        boost::bind(&travstate::leave, &t, _1, _2) );
        
        SLOG << OSG::endLog 
             << "Variant 5: don't descend into transforms" << OSG::endLog;
        traverse(scene, dontEnterTrans, leave);
        
        SLOG << OSG::endLog 
                << "Variant 6: quit when you find a geometry" << OSG::endLog;
        traverse(scene, quitGeo, leave);
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
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
            cyltrans = NULL;
            tortrans = NULL;
            delete mgr;
            
            OSG::osgExit();
            exit(0);
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
