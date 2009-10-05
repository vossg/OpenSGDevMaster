// OpenSG Tutorial Example: Loading
//
// This example shows how to load a scene file using OpenSG.
// The supported formats right now are VRML97, OBJ, OFF and RAW, so just
// calling this program with a scene file as a parameter should load the scene
// file.
//

// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"

// New Headers

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

#include "OSGFieldContainerUtils.h"


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // load the scene
    
        OSG::NodeUnrecPtr scene;
        
        if(argc < 2)
        {
            FWARNING(("No file given!\n"));
            FWARNING(("Supported file formats:\n"));
            
            OSG::SceneFileHandler::the()->print();
            scene = OSG::makeTorus(.5, 2, 16, 16);
        }
        else
        {
            /*
                All scene file loading is handled via the SceneFileHandler.
            */
            scene = OSG::SceneFileHandler::the()->read(argv[1]);
        }
    
        //scene->dump();
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
        mgr->setUseTraversalAction(true);
    
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
    mgr->idle();
    mgr->redraw();
    OSG::Thread::getCurrentChangeList()->clear();
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
            delete mgr;

            OSG::osgExit();
            exit(0);
        break;
        case 'f':
            mgr->setNavigationMode(OSG::Navigator::FLY);
        break;
        case 't':
            mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        break;
        case 'q':
            mgr->setStatistics(true);
        break;
        case 'w':
            mgr->setStatistics(false);
        break;
        case 'r':
        {
            bool useTrav = !mgr->getUseTraversalAction();
            mgr->setUseTraversalAction(useTrav);
            printf("Using %s action.\n", useTrav ? "render traversal" : "render");
        }
        break;
        
        case 'p':
        {
            std::cout << "Scanning memory consumption." << std::endl;
            OSG::MemoryConsumption mc;
            mc.scan();
            mc.print(std::cout);
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
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
