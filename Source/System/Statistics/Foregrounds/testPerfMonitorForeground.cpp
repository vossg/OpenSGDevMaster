#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGPassiveWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"

#include "OSGDrawable.h"
#include "OSGPerfMonitorForeground.h"
#include "OSGPerfMonitor.h"
#include "OSGPerfMonitorGuard.h"
#include "OSGBaseFunctions.h"

#include "OSGTextureBaseChunk.h"
#include "OSGMaterialChunk.h"
#include <boost/assign/list_of.hpp>


OSG::SimpleSceneManagerRefPtr mgr(NULL);
OSG::RenderActionRefPtr       act(NULL);

OSG::PassiveWindowRecPtr         pwin;
OSG::PerfMonitorForegroundRecPtr perfmon_fg;

bool show = true;

void doStuff();   // Function to just do some things to analyze

// redraw the window
void display(void)
{
    doStuff();
    OSG::PerfMonitor::the()->updateFrame();     // Have to update the stats each "frame"
    
    mgr->redraw();

    // all done, swap
    glutSwapBuffers();
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
        case 27:
        {
            OSG::osgExit();
            exit(0);
        }
        case 'm':
           perfmon_fg->cycleMode(-1);
           break;
        case 'M':
           perfmon_fg->cycleMode();        
           break;
        case 'S':
        case 's':
           mgr->setStatistics(!mgr->getStatistics());
           break;

        // Output help about the controls
        // - If you add an option, please add it here too.
       case '?':
       case '/':
       case 'h':
       {
          std::cerr << "\nControls:"
                    << "ESC: Exit application\n"
                    << "m/M: Switch stat mode.\n"
                    << "s: Cycle stats display.\n"
                    << std::endl;
       }
       break;
   }
}


int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    OSG::PerfMonitor::the()->enable(true);   // Enable performance monitoring

    // GLUT init
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(500, 500);
    glutCreateWindow("PerfMonitor FG Test");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    pwin=OSG::PassiveWindow::create();
    pwin->init();

    // create the scene
    OSG::NodeUnrecPtr scene;

    if(argc > 1)
    {
        scene = OSG::Node::create();
        OSG::GroupUnrecPtr g = OSG::Group::create();

        scene->setCore(g);

        for(OSG::UInt16 i = 1; i < argc; ++i)
            scene->addChild(OSG::SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
        scene = OSG::makeTorus(.5, 3, 16, 16);
    }

    // create the SimpleSceneManager helper
    mgr = OSG::SimpleSceneManager::create();

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);

    OSG::Thread::getCurrentChangeList()->commitChanges();

    // show the whole scene
    mgr->showAll();

    // add the statistics forground

    perfmon_fg = OSG::PerfMonitorForeground::create();
    pwin->getPort(0)->addForeground(perfmon_fg);

    //statfg->setMaxSize(25);
    //statfg->setColor(Color4f(0,1,0,0.7));

    act = OSG::RenderAction::create();
    mgr->setAction(act);

    // GLUT main loop
    glutMainLoop();

    return 0;
}


void randWork(unsigned baseTime, unsigned randMax, std::string name)
{
OSG::PerfMonitorGuard g(name);
   unsigned rand_time = unsigned(OSG::osgRand() * float(randMax));   
   OSG::osgSleep(baseTime + rand_time);
}

void recursiveFunc(unsigned depth=3)
{
   OSG::PerfMonitorGuard g("recursiveFunc");

   //osgSleep(10);
   //std::cout << "depth: " << depth << std::endl;

   if (depth == 0)
   { return; }
   else
   { recursiveFunc(depth-1); }   
}

void doStuff()
{
   static float x     =0;      // Value to influence the work
   static float x_inc =0.01f;
   x += x_inc;
   if ((x<=0.0) || (x>=1.0))
   {
      x_inc = -x_inc;
      x += x_inc;
   }   
   
   OSG::PerfMonitorGuard gG("doStuff");

   {
      OSG::PerfMonitorGuard g("Work1");
      recursiveFunc();
      randWork(unsigned(10.0*x),       1, "10*x");
      randWork(unsigned(10.0*(1.0-x)), 1, "10*(1-x)");
   }

   {
      OSG::PerfMonitorGuard g("Work2");
      recursiveFunc();
      randWork(unsigned(5.0*x),    1, "5x-1");
      randWork(2,                 10, "2-10");
   }
   
   {
      OSG::PerfMonitorGuard g("Work3");
      recursiveFunc();
      randWork( 1, unsigned(5.0*x), "1-5x");
      randWork(2,                0, "2-0");
   }   

   {
      OSG::PerfMonitorGuard g("Work4");
      recursiveFunc(3);      
   }

   {
      OSG::PerfMonitorGuard g("Work5");
      recursiveFunc(3);      
   }

   {
      OSG::PerfMonitorGuard g("Work6");
      recursiveFunc(3);      
   }

   {
      OSG::PerfMonitorGuard g("Work7");
      recursiveFunc(3);      
   }
}
