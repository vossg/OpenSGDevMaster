// Headers
#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"
#include "OSGSimpleGeometry.h"

// New Headers

// the general scene file loading handler
#include "OSGSceneFileHandler.h"
#include "OSGFieldContainerFactory.h"

#define BOOST_FILESYSTEM_VERSION 2

#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/convenience.hpp>
namespace fs = boost::filesystem;

#include "OSGBackgroundLoader.h"
#include "OSGModelRequest.h"

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;
OSG::GroupNodeRefPtr gScene;

unsigned gNextModelIdx = 0;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void findModels(std::string dirname)
{
   fs::path dir_path(dirname);

   if (!fs::exists(dir_path))
   { 
      std::cerr << "ERROR: path does not exist: " << dirname << std::endl; 
      gScene = static_cast<OSG::Node *>(NULL);
      OSG::osgExit();
      exit(-1);
   }

   fs::directory_iterator end_itr;
   for(fs::directory_iterator itr(dir_path); itr != end_itr; ++itr)
   {
      if(!fs::is_directory(*itr))
      {
         if (fs::extension(*itr) == std::string(".osb") ||
             fs::extension(*itr) == std::string(".wrl"))
         {
            fs::path  complete_file = fs::complete(*itr);
            std::string filename(complete_file.string());
            std::cout << "Found file: " << filename << std::endl;
            OSG::ModelRequestPtr req = OSG::ModelRequest::create()->init(OSG::NodeRefPtr(gScene.node()), filename);
            OSG::BackgroundLoader::the()->addRequest(req);
         }
      }
   }

}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    OSG::osgInit(argc,argv);

    gScene = OSG::GroupNodeRefPtr::create();

    if (argc < 2)
    {
       std::cout << "Specify a directory to load models from." << std::endl;
       gScene = static_cast<OSG::Node *>(NULL);
       OSG::osgExit();
       exit(-1);
    }

    findModels(std::string(argv[1]));

    // Start the background loader.
    OSG::BackgroundLoader::the()->start();

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowUnrecPtr gwin= OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();
    
    // create the SimpleSceneManager helper
    mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (gScene.node());

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    OSG::BackgroundLoader::the()->stop(); 
 
   return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    OSG::Thread::getCurrentChangeList()->commitChangesAndClear();

    //OSG::BackgroundLoader::the()->processOne();
    // Sync changes from BackgroundLoader.
    OSG::BackgroundLoader::the()->sync();

    mgr->idle();
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

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            delete mgr;
            gScene = static_cast<OSG::Node *>(NULL);
            OSG::osgExit();
            exit(0);
        }
        break;

        case 'f':
        {
            mgr->setNavigationMode(OSG::Navigator::FLY);
        }
        break;

        case 't':
        {
            mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        }
        break;

    case 'a':
       {
          mgr->showAll();
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
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
