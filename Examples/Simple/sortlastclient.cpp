// OpenSG Tutorial Example: Sort Last Cluster
//
// Minimalistic OpenSG cluster client program demonstrating sort-last
// clustering (i.e. using multiple machine to draw a single image)
// 
// To test it, run 
//   ./clusterServer -geometry 300x300+200+100 -m -w test1 &
//   ./clusterServer -geometry 300x300+500+100 -m -w test2 &
//   ./sortlastclient -m -fData/tie.wrl test1 test2
//
// If you have trouble with multicasting, you can alternatively try
//   ./clusterserver -geometry 300x300+200+100 -w 127.0.0.1:30000 &
//   ./clusterserver -geometry 300x300+500+100 -w 127.0.0.1:30001 &
//   ./sortlastclient -fData/tie.wrl 127.0.0.1:30000 127.0.0.1:30001
// This will work as long as your loopback interface can handle broadcasts.
// If that is not the case you need to use your local IP address instead
// of 127.0.0.1.
// 
// The client will open a window that you can use to navigate.
//
// This will run all three on the same machine, but you can also start the 
// servers anywhere else, as long as you can reach them via broadcast and
// multicast, if using option 1 above.
//
// Note: This will run two VERY active OpenGL programs on one screen. Not all
// OpenGL drivers are happy with that, so if it crashes your X, it's not our
// fault! ;)

#ifdef OSG_BUILD_ACTIVE
// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// The cluster window that handles sort-last (scene-split) clustering
#include <OSGSortLastWindow.h>
#include <OSGPipelineComposer.h>
#include <OSGBinarySwapComposer.h>
#include <OSGParallelComposer.h>

// Scene file handler for loading geometry files
#include <OSGSceneFileHandler.h>
#else
// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// The cluster window that handles sort-last (scene-split) clustering
#include <OpenSG/OSGSortLastWindow.h>
#include <OpenSG/OSGPipelineComposer.h>
#include <OpenSG/OSGBinarySwapComposer.h>
#include <OpenSG/OSGParallelComposer.h>

// Scene file handler for loading geometry files
#include <OpenSG/OSGSceneFileHandler.h>
#endif

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    char *opt;

    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        OSG::NodeRefPtr scene;
        
        // the connection between this client and the servers
        OSG::SortLastWindowRefPtr mwin = OSG::SortLastWindow::create();
    
        // all changes must be enclosed in beginEditCP and endEditCP
        // otherwise the changes will not be transfered over the network.
    
        // evaluate params
        for(int a=1 ; a<argc ; ++a)
        {
            if(argv[a][0] == '-')
            {
                switch(argv[a][1])
                {
                case 'm': mwin->setConnectionType("Multicast");
                          std::cout << "Connection type set to Multicast"
                                    << std::endl;
                          break;
                case 'p': mwin->setConnectionType("SockPipeline");
                          std::cout << "Connection type set to SockPipeline"
                                    << std::endl;
                          break;
                case 'i': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setConnectionInterface(opt);
                          break;
                case 'a': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              mwin->setServiceAddress(opt);
                          break;
                case 'f': opt = argv[a][2] ? argv[a]+2 : argv[++a];
                          if(opt != argv[argc])
                              scene = OSG::SceneFileHandler::the()->read(opt, 0);
                          break;
                case 'L':
                {
                    OSG::ImageComposerRefPtr comp = OSG::PipelineComposer::create();
                    mwin->setComposer(comp);
                }
                break;
                case 'B':
                {
                    OSG::ImageComposerRefPtr comp = OSG::BinarySwapComposer::create();
                    mwin->setComposer(comp);
                }
                break;
                case 'P':
                {
                    OSG::ImageComposerRefPtr comp = OSG::ParallelComposer::create();
                    mwin->setComposer(comp);
                }
                break;
                default:  std::cout << argv[0]  
                                    << " -m"
                                    << " -p"
                                    << " -i interface"
                                    << " -f file"
                                << OSG::endLog;
                        return 0;
                }
            }
            else
            {
                printf("%s\n",argv[a]);
                mwin->editMFServers()->push_back(argv[a]);
            }
        }
    
        // Set the composer to use
    
        if(mwin->getComposer() == NULL)
        {
            OSG::ImageComposerRefPtr comp = OSG::PipelineComposer::create();
            mwin->setComposer(comp);
        }
    
        fprintf(stderr, "Using : %s\n", mwin->getComposer()->getType().getCName());
    
        // window size
        mwin->setSize(300,300);
    
        // Create/set the client window that will display the result
        
        OSG::GLUTWindowRefPtr clientWindow = OSG::GLUTWindow::create();
        
        glutReshapeWindow(300,300);
        clientWindow->setGlutId(winid);
        clientWindow->init();
        
        clientWindow->resize(300,300);
        
        // Set the client window that will display the result
        mwin->setClientWindow(clientWindow);
        
        // create default scene
        if(scene == NULL)
        {
            scene = OSG::makeNodeFor(OSG::Group::create());
    
            scene->addChild(OSG::makeTorus(.5, 2, 16, 16));
            scene->addChild(OSG::makeCylinder(1, .3f, 8, true, true, true));
        }
        
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(mwin );
        mgr->setRoot  (scene);
        mgr->setUseTraversalAction(false);
    
        // show the whole scene
        mgr->showAll();
        
        // initialize window
        mwin->init();
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
    // redraw the cluster window
    mgr->redraw();
    // clear change list. If you don't clear the changelist,
    // then the same changes will be transmitted a second time
    // in the next frame. 
    OSG::Thread::getCurrentChangeList()->clear();
}

// react to size changes
void reshape(int w, int h)
{
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

    return winid;
}
