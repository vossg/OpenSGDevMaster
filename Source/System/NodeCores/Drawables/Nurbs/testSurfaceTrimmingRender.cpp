// OpenSG NURBS example: testSurfaceTrimmingRender.cpp
//
// Shows how to render a trimmed NURBS surface.

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleMaterial.h>
#include <OSGGLUTWindow.h>
#include <OSGSolidBackground.h>
#include <OSGSurface.h>


OSG::SimpleSceneManager   *mgr;
OSG::SimpleMaterialRefPtr  gpcl_defaultmat;
OSG::Real32                g_error;
OSG::SurfaceRefPtr         gpcl_surface;

// redraw the window
void display(void)
{      
    // render
    
    mgr->redraw();

    // all done, swap  (better not GV)
    //glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    delete mgr;
                gpcl_defaultmat = NULL;
                gpcl_surface    = NULL;
                exit(1);
    case 'y':   
    case 'z':
                glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
                std::cerr << "PolygonMode: Point." << std::endl;
                break;
    case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
                std::cerr << "PolygonMode: Line." << std::endl;
                break;
    case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
                std::cerr << "PolygonMode: Fill." << std::endl;
                break;
    case 'f':   g_error *= 2;
                std::cerr << "Error: " << g_error << std::endl;
                gpcl_surface->setError( g_error );
                break;
    case 'g':   g_error /= 2;
                std::cerr << "Error: " << g_error << std::endl;
                gpcl_surface->setError( g_error );
                break;
    default:    std::cerr << "y,z   = Polygon Point Mode\n"
                          << "x     = Polygon Line Mode\n"
                          << "c     = Polygon Fill Mode\n"
                          << "f/g   = +/- Error\n"
                          << std::endl;
                break;
    }
}


void setupDefaultMaterial( void )
{
    gpcl_defaultmat = OSG::SimpleMaterial::create();
    gpcl_defaultmat->setDiffuse( OSG::Color3f(1.0,0.0,0.0) ); // RED
    gpcl_defaultmat->setAmbient( OSG::Color3f(0.2,0.2,0.2) );
    gpcl_defaultmat->setEmission( OSG::Color3f(0.02,0.02,0.02) );
    gpcl_defaultmat->setSpecular( OSG::Color3f(0.78,0.78,0.78) );
    gpcl_defaultmat->setShininess( 128 );
}






OSG::NodeTransitPtr makeScene( void )
{
    setupDefaultMaterial();

    OSG::NodeTransitPtr         root    = OSG::Node            ::create();
    OSG::SurfaceRefPtr          surface = OSG::Surface         ::create();
    OSG::GeoPnt3fPropertyRefPtr cps     = OSG::GeoPnt3fProperty::create();

    // control points should always be 3D for the time being,
    // rational support will be added later
    cps->clear();
    cps->push_back( OSG::Pnt3f(  1,  1,  0 ));
    cps->push_back( OSG::Pnt3f(  1,  0,  0 ));
    cps->push_back( OSG::Pnt3f(  1,  0,  1 ));
    cps->push_back( OSG::Pnt3f(  1, -1,  1 ));

    cps->push_back( OSG::Pnt3f(  0,  1,  0 ));
    cps->push_back( OSG::Pnt3f(  0,  0,  0 ));
    cps->push_back( OSG::Pnt3f(  0,  0,  1 ));
    cps->push_back( OSG::Pnt3f(  0, -1,  1 ));

    cps->push_back( OSG::Pnt3f(  0,  1,  1 ));
    cps->push_back( OSG::Pnt3f(  0,  0,  1 ));
    cps->push_back( OSG::Pnt3f(  0,  0,  0 ));
    cps->push_back( OSG::Pnt3f(  0, -1,  0 ));

    cps->push_back( OSG::Pnt3f( -1,  1,  1 ));
    cps->push_back( OSG::Pnt3f( -1,  0,  1 ));
    cps->push_back( OSG::Pnt3f( -1,  0,  0 ));
    cps->push_back( OSG::Pnt3f( -1, -1,  0 ));
    
    std::vector<OSG::Real64> knots1;
    std::vector<OSG::Real64> knots2;
    std::vector<OSG::Pnt2f> points;
    knots1.clear();
    knots1.push_back(0);
    knots1.push_back(0);
    knots1.push_back(1);
    knots1.push_back(1);
    knots2.clear();
    knots2.push_back(0);
    knots2.push_back(0);
    knots2.push_back(0);
    knots2.push_back(1);
    knots2.push_back(1);
    knots2.push_back(1);
        
    // first, let's clear the trimming
    surface->removeCurves();

    // add the outer trimming around the domain
    points.clear();
    points.push_back( OSG::Pnt2f(0,0) );
    points.push_back( OSG::Pnt2f(1,0) );
    surface->addCurve( 1, knots1, points, true );
    points.clear();
    points.push_back( OSG::Pnt2f(1,0) );
    points.push_back( OSG::Pnt2f(1,1) );
    surface->addCurve( 1, knots1, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(1,1) );
    points.push_back( OSG::Pnt2f(0,1) );
    surface->addCurve( 1, knots1, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(0,1) );
    points.push_back( OSG::Pnt2f(0,0) );
    surface->addCurve( 1, knots1, points, false );

    // add inner trimming loop 1
    points.clear();
    points.push_back( OSG::Pnt2f(0.3,0.5) );
    points.push_back( OSG::Pnt2f(0.1,0.9) );
    points.push_back( OSG::Pnt2f(0.5,0.7) );
    surface->addCurve( 2, knots2, points, true );
    points.clear();
    points.push_back( OSG::Pnt2f(0.5,0.7) );
    points.push_back( OSG::Pnt2f(0.9,0.9) );
    points.push_back( OSG::Pnt2f(0.7,0.5) );
    surface->addCurve( 2, knots2, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(0.7,0.5) );
    points.push_back( OSG::Pnt2f(0.9,0.1) );
    points.push_back( OSG::Pnt2f(0.5,0.3) );
    surface->addCurve( 2, knots2, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(0.5,0.3) );
    points.push_back( OSG::Pnt2f(0.1,0.1) );
    points.push_back( OSG::Pnt2f(0.3,0.5) );
    surface->addCurve( 2, knots2, points, false );
    
    // add inner trimming loop 2
    points.clear();
    points.push_back( OSG::Pnt2f(0.4,0.5) );
    points.push_back( OSG::Pnt2f(0.4,0.4) );
    points.push_back( OSG::Pnt2f(0.5,0.4) );
    surface->addCurve( 2, knots2, points, true );
    points.clear();
    points.push_back( OSG::Pnt2f(0.5,0.4) );
    points.push_back( OSG::Pnt2f(0.6,0.4) );
    points.push_back( OSG::Pnt2f(0.6,0.5) );
    surface->addCurve( 2, knots2, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(0.6,0.5) );
    points.push_back( OSG::Pnt2f(0.6,0.6) );
    points.push_back( OSG::Pnt2f(0.5,0.6) );
    surface->addCurve( 2, knots2, points, false );
    points.clear();
    points.push_back( OSG::Pnt2f(0.5,0.6) );
    points.push_back( OSG::Pnt2f(0.4,0.6) );
    points.push_back( OSG::Pnt2f(0.4,0.5) );
    surface->addCurve( 2, knots2, points, false );
    
    // set up dimensions and knot vectors:
    surface->setDimU( 3 );
    surface->setDimV( 3 );
    surface->editMFKnotsU()->clear();
    surface->editMFKnotsU()->push_back( 0 );
    surface->editMFKnotsU()->push_back( 0 );
    surface->editMFKnotsU()->push_back( 0 );
    surface->editMFKnotsU()->push_back( 0 );
    surface->editMFKnotsU()->push_back( 1 );
    surface->editMFKnotsU()->push_back( 1 );
    surface->editMFKnotsU()->push_back( 1 );
    surface->editMFKnotsU()->push_back( 1 );
    surface->editMFKnotsV()->clear();
    surface->editMFKnotsV()->push_back( 0 );
    surface->editMFKnotsV()->push_back( 0 );
    surface->editMFKnotsV()->push_back( 0 );
    surface->editMFKnotsV()->push_back( 0 );
    surface->editMFKnotsV()->push_back( 1 );
    surface->editMFKnotsV()->push_back( 1 );
    surface->editMFKnotsV()->push_back( 1 );
    surface->editMFKnotsV()->push_back( 1 );
    
    // set control points and texture control points
    surface->setControlPoints( cps );
    
    // set error
    surface->setError( g_error );
    
    // and finally set the material
    surface->setMaterial( gpcl_defaultmat );

    root->setCore( surface );

    gpcl_surface = surface;

    return root;
}

int main(int argc, char **argv)
{
    g_error = 0.01;

    if ( argc == 2 )
    {
        g_error = atof( argv[1] );
    }
    if ( g_error < 0.001 )
    {
        g_error = 0.001;
    }
    
    OSG::osgInit(argc,argv);
    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    {
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        OSG::NodeRefPtr scene;
        scene = makeScene( );
        
        if ( scene == NULL )
        {
            std::cerr<<"makeScene returned NullFC, exiting..."<<std::endl;
            return -1;
        }
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // create the window and initial camera/viewport
        mgr->setWindow( gwin );
        // tell the manager what to manage
        mgr->setRoot  ( scene );
        
        // show the whole scene
        mgr->showAll();
        mgr->redraw();
        OSG::SolidBackgroundRefPtr bgr = OSG::SolidBackground::create();
        bgr->setColor( OSG::Color3f( 0.7, 0.7, 0.7 ));
        mgr->getWindow()->getPort(0)->setBackground( bgr );
    }
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

