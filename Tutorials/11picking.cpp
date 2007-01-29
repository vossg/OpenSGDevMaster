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


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// The file root node, needed for intersection
NodePtr fileroot;

// The points used for visualising the ray and hit object
GeoPnt3fPropertyPtr isectPoints;

// The visualisation geometry, needed for update.
GeometryPtr testgeocore;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

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
                Line l;
                
                l = mgr->calcViewRay(x, y);

                std::cerr << "From "  << l.getPosition () 
                          << ", dir " << l.getDirection() << std::endl;
    
                IntersectAction *act = IntersectAction::create();
                
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
                    TriangleIterator it(act->getHitObject());
                    it.seek(act->getHitTriangle());
                    
                    // calculate its vertex positions in world space
                    Matrix m;
                    act->getHitObject()->getToWorld(m);
            
                    // and turn them into a triangle
                    Pnt3f p = it.getPosition(0);
                    m.multMatrixPnt(p);
                    isectPoints->setValue(p, 2);
                    p = it.getPosition(1);
                    m.multMatrixPnt(p);
                    isectPoints->setValue(p, 3);
                    p = it.getPosition(2);
                    m.multMatrixPnt(p);
                    isectPoints->setValue(p, 4);
                }
                else
                {
                    // no, get rid of the triangle and highlight.
                    isectPoints->setValue(Pnt3f(0,0,0), 2);
                    isectPoints->setValue(Pnt3f(0,0,0), 3);
                    isectPoints->setValue(Pnt3f(0,0,0), 4);
                    
                    mgr->setHighlight(NullFC);
                }

                commitChanges();
            
                // free the action
                delete act;
                
                std::cerr << std::endl;
                
                glutPostRedisplay();           
                }
                break;
    }
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
    gwin->setId(winid);
    gwin->init();

    // The scene group
    
    NodePtr  scene = Node::create();
    GroupPtr g     = Group::create();
    
    scene->setCore(g);
    
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the()->getSuffixList(suffixes);
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        fileroot = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        /*
            All scene file loading is handled via the SceneFileHandler.
        */
        fileroot = SceneFileHandler::the()->read(argv[1]);
    }

    scene->addChild(fileroot);
    
    // Create a small geometry to show the ray and what was hit
    // Contains a line and a single triangle.
    // The line shows the ray, the triangle whatever was hit.
    
    SimpleMaterialPtr red = SimpleMaterial::create();
    
    red->setDiffuse     (Color3f( 1,0,0 ));   
    red->setTransparency(0.5);   
    red->setLit         (false);   

    isectPoints = GeoPnt3fProperty::create();
    isectPoints->addValue(Pnt3f(0,0,0));
    isectPoints->addValue(Pnt3f(0,0,0));
    isectPoints->addValue(Pnt3f(0,0,0));
    isectPoints->addValue(Pnt3f(0,0,0));
    isectPoints->addValue(Pnt3f(0,0,0));

    GeoUInt32PropertyPtr index = GeoUInt32Property::create();
    index->addValue(0);
    index->addValue(1);
    index->addValue(2);
    index->addValue(3);
    index->addValue(4);

    GeoUInt32PropertyPtr lens = GeoUInt32Property::create();
    lens->addValue(2);
    lens->addValue(3);
    
    GeoUInt8PropertyPtr type = GeoUInt8Property::create();
    type->addValue(GL_LINES);
    type->addValue(GL_TRIANGLES);

    testgeocore = Geometry::create();
    testgeocore->setPositions(isectPoints);
    testgeocore->setIndices(index);
    testgeocore->setLengths(lens);
    testgeocore->setTypes(type);
    testgeocore->setMaterial(red);
    
    NodePtr testgeo = Node::create();
    testgeo->setCore(testgeocore);
    
    scene->addChild(testgeo);

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
