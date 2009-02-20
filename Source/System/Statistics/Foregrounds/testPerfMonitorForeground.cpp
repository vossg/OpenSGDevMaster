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


OSG_USING_NAMESPACE

SimpleSceneManager *mgr(NULL);
RenderAction       *act(NULL);

PassiveWindowRecPtr         pwin;
PerfMonitorForegroundRecPtr perfmon_fg;

bool show = true;

void doStuff();   // Function to just do some things to analyze

// redraw the window
void display(void)
{
    doStuff();
    PerfMonitor::the()->updateFrame();     // Have to update the stats each "frame"
    
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
            osgExit();
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
    osgInit(argc,argv);
    PerfMonitor::the()->enable(true);   // Enable performance monitoring

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

    pwin=PassiveWindow::create();
    pwin->init();

    // create the scene
    NodeUnrecPtr scene;

    if(argc > 1)
    {
        scene = Node::create();
        GroupUnrecPtr g = Group::create();

        scene->setCore(g);

        for(UInt16 i = 1; i < argc; ++i)
            scene->addChild(SceneFileHandler::the()->read(argv[i]));
    }
    else
    {
        scene = makeTorus(.5, 3, 16, 16);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);

    Thread::getCurrentChangeList()->commitChanges();

    // show the whole scene
    mgr->showAll();

    // add the statistics forground

    perfmon_fg = PerfMonitorForeground::create();
    pwin->getPort(0)->addForeground(perfmon_fg);

    //statfg->setMaxSize(25);
    //statfg->setColor(Color4f(0,1,0,0.7));

    act = RenderAction::create();
    mgr->setAction(act);

    // GLUT main loop
    glutMainLoop();

    return 0;
}


void randWork(unsigned baseTime, unsigned randMax, std::string name)
{
PerfMonitorGuard g(name);
   unsigned rand_time = unsigned(osgRand() * float(randMax));   
   osgSleep(baseTime + rand_time);
}

void recursiveFunc(unsigned depth=3)
{
   PerfMonitorGuard g("recursiveFunc");

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
   static float x_inc =0.01;
   x += x_inc;
   if ((x<=0.0) || (x>=1.0))
   {
      x_inc = -x_inc;
      x += x_inc;
   }   
   
   PerfMonitorGuard g("doStuff");

   {
      PerfMonitorGuard g("Work1");
      recursiveFunc();
      randWork(unsigned(10.0*x),       1, "10*x");
      randWork(unsigned(10.0*(1.0-x)), 1, "10*(1-x)");
   }

   {
      PerfMonitorGuard g("Work2");
      recursiveFunc();
      randWork(unsigned(5.0*x),    1, "5x-1");
      randWork(2,                 10, "2-10");
   }
   
   {
      PerfMonitorGuard g("Work3");
      recursiveFunc();
      randWork( 1, unsigned(5.0*x), "1-5x");
      randWork(2,                0, "2-0");
   }   

   {
      PerfMonitorGuard g("Work4");
      recursiveFunc(3);      
   }

   {
      PerfMonitorGuard g("Work5");
      recursiveFunc(3);      
   }

   {
      PerfMonitorGuard g("Work6");
      recursiveFunc(3);      
   }

   {
      PerfMonitorGuard g("Work7");
      recursiveFunc(3);      
   }
}
