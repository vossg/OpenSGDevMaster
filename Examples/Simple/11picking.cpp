// OpenSG Tutorial Example: Picking
//
// In addition to the loading example this one shows how to pick an object.
//
// To do that the IntersectAction is introduced, which tests rays against
// geometry.
//
// Use Space to send a ray into the scene. If it hits something the hit
// triangle will be highlighted.
//

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGeoProperties.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGGroup.h>
#include <OSGSceneFileHandler.h>
#include <OSGTriangleIterator.h>

// New Headers

// the ray intersect traversal
#include <OSGIntersectAction.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoProperties.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGTriangleIterator.h>

// New Headers

// the ray intersect traversal
#include <OpenSG/OSGIntersectAction.h>
#endif


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// The file root node, needed for intersection
OSG::NodeRefPtr fileroot;

// The points used for visualising the ray and hit object
OSG::GeoPnt3fPropertyRefPtr isectPoints;

// The visualisation geometry, needed for update.
OSG::GeometryRefPtr testgeocore;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            fileroot    = NULL;
            isectPoints = NULL;
            testgeocore = NULL;
            delete mgr;
        
            OSG::osgExit();
            exit(0);
        }
        break;

        case ' ':   // send a ray through the clicked pixel
                /*
                    Intersection testing for rays is done using an
                    IntersectAction. The ray itself is calculated by the
                    SimpleSceneManager, given the clicked pixel.
                    
                    It needs to be set up with the line that is to be
                    intersected. A line is a semi-infinite ray which has a
                    starting point and a direction, and extends in the
                    direction to infinity.
                    
                    To do the actual test the Action's apply() method is used.
                    
                    The results can be received from the Action. The main
                    difference is if something was hit or not, which is
                    returned in didHit().
                    
                    If an intersection did occur, the other data elements are
                    valid, otherwise they are undefined.
                    
                    The information that is stored in the action is the object
                    which was hit, the triangle of the object that was hit (in
                    the form of its index) and the actual hit position.             
                */
                {
                OSG::Line l;
                
                l = mgr->calcViewRay(x, y);

                std::cerr << "From "  << l.getPosition () 
                          << ", dir " << l.getDirection() << std::endl;
    
                OSG::IntersectAction *act = OSG::IntersectAction::create();
                
                act->setLine(l);
                act->apply(fileroot);
            
                isectPoints->setValue(l.getPosition(), 0);
                isectPoints->setValue(l.getPosition() + l.getDirection(), 1);
            
                // did we hit something?
                if (act->didHit())
                {
                    // yes!! print and highlight it
                    std::cerr << " object " << act->getHitObject  () 
                              << " tri "    << act->getHitTriangle() 
                              << " at "     << act->getHitPoint   ();
                    
                    mgr->setHighlight(act->getHitObject());
                    
                    // stop the ray on the hit surface
                    isectPoints->setValue(l.getPosition() + 
                            l.getDirection() * act->getHitT(), 1);
                    
                    // find the triangle that was hit
                    OSG::TriangleIterator it(act->getHitObject());
                    it.seek(act->getHitTriangle());
                    
                    // calculate its vertex positions in world space
                    OSG::Matrix m;
                    act->getHitObject()->getToWorld(m);
            
                    // and turn them into a triangle
                    OSG::Pnt3f p = it.getPosition(0);
                    m.mult(p, p);
                    isectPoints->setValue(p, 2);
                    p = it.getPosition(1);
                    m.mult(p, p);
                    isectPoints->setValue(p, 3);
                    p = it.getPosition(2);
                    m.mult(p, p);
                    isectPoints->setValue(p, 4);
                }
                else
                {
                    // no, get rid of the triangle and highlight.
                    isectPoints->setValue(OSG::Pnt3f(0,0,0), 2);
                    isectPoints->setValue(OSG::Pnt3f(0,0,0), 3);
                    isectPoints->setValue(OSG::Pnt3f(0,0,0), 4);
                    
                    mgr->setHighlight(NULL);
                }

                OSG::commitChanges();
            
                // free the action
                delete act;
                
                std::cerr << std::endl;
                
                glutPostRedisplay();           
                }
                break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;
    }
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
    
        // The scene group
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        OSG::GroupRefPtr g     = OSG::Group::create();
        
        scene->setCore(g);
        
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
            
            std::list<const char*> suffixes;
            OSG::SceneFileHandler::the()->getSuffixList(suffixes);
            
            for(std::list<const char*>::iterator it  = suffixes.begin();
                                                 it != suffixes.end();
                                               ++it)
            {
                FWARNING(("%s\n", *it));
            }
    
            fileroot = OSG::makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            fileroot = OSG::SceneFileHandler::the()->read(argv[1]);
        }
    
        scene->addChild(fileroot);
        
        // Create a small geometry to show the ray and what was hit
        // Contains a line and a single triangle.
        // The line shows the ray, the triangle whatever was hit.
        
        OSG::SimpleMaterialRefPtr red = OSG::SimpleMaterial::create();
        
        red->setDiffuse     (OSG::Color3f( 1,0,0 ));   
        red->setTransparency(0.5);   
        red->setLit         (false);   
    
        isectPoints = OSG::GeoPnt3fProperty::create();
        isectPoints->addValue(OSG::Pnt3f(0,0,0));
        isectPoints->addValue(OSG::Pnt3f(0,0,0));
        isectPoints->addValue(OSG::Pnt3f(0,0,0));
        isectPoints->addValue(OSG::Pnt3f(0,0,0));
        isectPoints->addValue(OSG::Pnt3f(0,0,0));
    
        OSG::GeoUInt32PropertyRefPtr index = OSG::GeoUInt32Property::create();
        index->addValue(0);
        index->addValue(1);
        index->addValue(2);
        index->addValue(3);
        index->addValue(4);
    
        OSG::GeoUInt32PropertyRefPtr lens = OSG::GeoUInt32Property::create();
        lens->addValue(2);
        lens->addValue(3);
        
        OSG::GeoUInt8PropertyRefPtr type = OSG::GeoUInt8Property::create();
        type->addValue(GL_LINES);
        type->addValue(GL_TRIANGLES);
    
        testgeocore = OSG::Geometry::create();
        testgeocore->setPositions(isectPoints);
        testgeocore->setIndices(index);
        testgeocore->setLengths(lens);
        testgeocore->setTypes(type);
        testgeocore->setMaterial(red);
        
        OSG::NodeRefPtr testgeo = OSG::Node::create();
        testgeo->setCore(testgeocore);
        
        scene->addChild(testgeo);
    
        OSG::commitChanges();
    
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

// redraw the window
void display(void)
{
    mgr->redraw();
}

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

    return winid;
}
