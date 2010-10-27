
// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"

#include "OSGSceneFileHandler.h"
#include "OSGFieldContainerUtils.h"
#include "OSGOgreMeshReader.h"

OSG::SimpleSceneManager           *mgr = NULL;
OSG::NodeUnrecPtr                  sceneN;   // scene from file
OSG::NodeUnrecPtr                  rootN;    // root

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void init     (int argc, char *argv[]);
void cleanup  (void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char *argv[])
{
    init(argc, argv);

    // GLUT main loop
    glutMainLoop();

    cleanup();
    OSG::osgExit();

    return 0;
}

void init(int argc, char *argv[])
{
    OSG::osgInit(argc, argv);

    int glutWinId = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(glutWinId);
    gwin->init();

    rootN = OSG::makeCoredNode<OSG::Group>();

    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));

        OSG::SceneFileHandler::the()->print();
        sceneN = OSG::makeTorus(.5, 2, 16, 16);
    }
    else
    {
        std::ifstream ifs(argv[1], std::ios_base::in);

        OSG::OgreMeshReader omr(ifs);
        omr.read();

        sceneN = omr.getRoot();
    }

    rootN->addChild(sceneN);

    // create the SimpleSceneManager helper
    mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (rootN);

    // show the whole scene
    mgr->showAll();
}

void cleanup(void)
{
    delete mgr;
    mgr = NULL;

    sceneN = NULL;
    rootN  = NULL;
}



// redraw the window
void display(void)
{
//     std::cout << ">> FRAME START" << std::endl;

    static OSG::Time   tAcc = 0;
    static OSG::UInt32 fc   = 0;

    OSG::Time t0 = OSG::getSystemTime();

    OSG::commitChangesAndClear();

    mgr->idle();
    mgr->redraw();

    OSG::Time t1 = OSG::getSystemTime();

    tAcc += (t1 - t0);
    fc   += 1;

    if(tAcc >= 1)
    {
        std::cout << "frame count [" << fc
                  << "] fc/tAcc [" << (fc/tAcc)
                  << "] tAcc [" << tAcc << "]" << std::endl;

        tAcc = 0;
        fc   = 0;
    }
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

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:
    {
        cleanup();

        OSG::osgExit();
        std::exit(0);
    }
    break;
    case 'f':
    {
        mgr->setNavigationMode(OSG::Navigator::FLY);
        std::cout << "Fly mode" << std::endl;
    }
    break;
    case 't':
    {
        mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        std::cout << "Trackball mode" << std::endl;
    }
    break;
    case 'q':
    {
        mgr->setStatistics(!mgr->getStatistics());
        std::cout << "Statistics "
                  << (mgr->getStatistics() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'h':
    {
        mgr->setHeadlight(!mgr->getHeadlightState());
        std::cout << "Headlight "
                  << (mgr->getHeadlightState() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'v':
    {
        mgr->getRenderAction()->setVolumeDrawing(
            !mgr->getRenderAction()->getVolumeDrawing());
        std::cout << "Volume drawing: "
                  << (mgr->getRenderAction()->getVolumeDrawing() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'p':
    {
        OSG::SceneGraphPrinter sgp(mgr->getRoot());
        sgp.printDownTree(std::cout);
    }
    break;
    case 'c':
    {
        mgr->getRenderAction()->setFrustumCulling(
            !mgr->getRenderAction()->getFrustumCulling());

        std::cout << "Frustum culling: "
                  << (mgr->getRenderAction()->getFrustumCulling() ? "enabled" : "disabled")
                  << std::endl;
    }
    break;
    case 'a':
    {
        mgr->showAll();

        std::cout << "Showing all of scene." << std::endl;
    }
    break;
    }

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
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
