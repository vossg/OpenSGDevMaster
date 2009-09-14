// OpenSG Tutorial Example: Occlusion Culling
//

// Three algorithms are implemented "stop an wait", "multi frame"
// and "hierarchical multi frame"

// --- stop and wait ---
// Renders the scene in front to back order. For each object (except for the
// front most object) a bounding box is drawn with an occlusion query.
// The result is fetched immediately afterwards and if the box was visible
// the corresponding object is drawn.
// This is quite slow because of the front to back sorted rendering and
// the occlusions queries are stalling the graphics pipeline.
//
// --- multi frame ---
// Renders the whole scene first (with state sorting) and keeps
// the depth buffer. For each object a bounding box is drawn
// with an occlusion query. The results are fetched in the next frame,
// if the box was visible the corresponding object is drawn.
// This is really fast but can lead to render errors on fast camera movements.
//
// --- hierarchical multi frame ---
// Similar to multi frame but it tries to reduce the number of
// occlusion tests by doing hierarchical occlusion tests.

#include <fstream>

#ifdef OSG_BUILD_ACTIVE
// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

#include <OSGGradientBackground.h>

#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>

#include <OSGSceneFileHandler.h>
#include <OSGGraphOpSeq.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGStripeGraphOp.h>
#include <OSGRenderAction.h>
#else
// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

#include <OpenSG/OSGGradientBackground.h>

#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGPathHandler.h>

#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGVerifyGeoGraphOp.h>
#include <OpenSG/OSGStripeGraphOp.h>
#include <OpenSG/OSGRenderAction.h>
#endif

OSG::SimpleSceneManager *mgr;
OSG::NodeRefPtr          scene;

// Standard GLUT callback functions
void display( void )
{
    mgr->redraw();
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

void
key(unsigned char key, int , int )
{
    switch(key)
    {
    case 27:    delete mgr;
                scene = NULL;
                OSG::osgExit();
                exit(1);
    case 'a':   mgr->turnHeadlightOn();
                break;
    case 's':   mgr->turnHeadlightOff();
                break;
    case 'l':   mgr->useOpenSGLogo();
                break;
    case 'f':   mgr->setNavigationMode(OSG::Navigator::FLY);
                break;
    case 't':   mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
                break;
    case 'q':   mgr->setStatistics(true);
                break;
    case 'w':   mgr->setStatistics(false);
                break;
    case 'o':   OSG::SceneFileHandler::the()->write(scene, "out.osb");
                break;
    case 'c':
    {
        OSG::RenderAction *ract = mgr->getRenderAction();
        ract->setOcclusionCulling(!ract->getOcclusionCulling());
        printf("Occlusion culling %s.\n", ract->getOcclusionCulling() ? "enabled" : "disabled");
    }
    break;
    }
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        const char *fileName = (argc > 1) ? argv[1] : NULL;
    
        if(fileName != NULL)
            scene = OSG::SceneFileHandler::the()->read(fileName, NULL);
    
        if(scene == NULL)
        {
            printf("No filename given creating a default scene.\n");
            // ok we create some spheres and one big torus around them
            // so we can see the occlusion culling.
            
            scene = OSG::makeCoredNode<OSG::Group>();
    
            OSG::NodeRefPtr spheres = OSG::makeCoredNode<OSG::Group>();
    
            // create spheres
            for(OSG::Real32 y=-0.5f;y<0.5f;y+=0.1f)
            {
                for(OSG::Real32 x=-0.5f;x<0.5f;x+=0.1f)
                {
                    OSG::Matrix m;
                    m.setTranslate(x, y, 0.0f);
                    OSG::TransformRefPtr sphere_trans;
                    OSG::NodeRefPtr sphere_trans_node = OSG::makeCoredNode<OSG::Transform>(&sphere_trans);
                    sphere_trans->setMatrix(m);
                    
                    OSG::NodeRefPtr sphere = OSG::makeSphere(3, 0.1f);
                    sphere_trans_node->addChild(sphere);
            
                    spheres->addChild(sphere_trans_node);
                }
            }
    
            // create torus.
            OSG::NodeRefPtr torus = OSG::makeTorus(0.5f, 2.0f, 32, 32);
    
            scene->addChild(spheres);
            scene->addChild(torus);
        }
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        mgr->setWindow( gwin );
        mgr->setRoot( scene );
        mgr->setStatistics(true);
    
        mgr->showAll();
    
        // create a gradient background.
        OSG::GradientBackgroundRefPtr gback = OSG::GradientBackground::create();
        gback->clearLines();
        gback->addLine(OSG::Color3f(0.7f, 0.7f, 0.8f), 0);
        gback->addLine(OSG::Color3f(0.0f, 0.1f, 0.3f), 1);
    
        OSG::WindowRefPtr win = mgr->getWindow();
        for(OSG::UInt32 i = 0; i < win->getMFPort()->size(); ++i)
        {
            OSG::ViewportRefPtr vp = win->getPort(i);
            vp->setBackground(gback);
        }
        
        OSG::commitChanges();
    }
    
    // enable occlusion culling.
    OSG::RenderAction *ract = mgr->getRenderAction();
    ract->setOcclusionCulling(true);
    
    printf("Occlusion culling enabled.\n");
    printf("Press 'c' to toggle occlusion culling.\n");

    // GLUT main loop
    glutMainLoop();

    return 0;
}
