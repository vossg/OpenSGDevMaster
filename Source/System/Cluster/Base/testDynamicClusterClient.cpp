// testDynamicClusterClient2
//
// OpenSG cluster client program where you can dynamicly connect/disconnect
// to the servers.
// It is similar to testDynamicClusterClient but this time we create from the
// current state a changelist and send this to the cluster servers.
// This variant is much easier to implement in your own app but could be
// problematic if you use more than one aspect in your app.

// To test it, run 
//   ./testClusterServer -w pipe0 &
//   ./testDynamicClusterClient2 pipe0
//
// press 'c' to connect to the servers and 'd' to disconnect. 


#include "OSGGLUT.h"
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGMultiDisplayWindow.h"
#include "OSGSceneFileHandler.h"
#include "OSGRemoteAspect.h"
#include "OSGFieldContainerFactory.h"

#include <string>
#include <vector>

// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManager          *_mgr = NULL;
OSG::GLUTWindowRecPtr            _client_win = NULL;
OSG::MultiDisplayWindowRecPtr    _cluster_win = NULL;
OSG::NodeRecPtr                  _root = NULL;
std::vector<std::string>         _pipenames;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    std::cout << "start a cluster server with './testClusterServer -w pipe0'\n"
                 "press 'c' to connect to the servers.\n"
                 "press 'd' to disconnect from the servers.\n"
                 "press 'n' to delete current scene.\n"
                 "press 't' to create a torus.\n"
                 "press 'l' to load scene 'tie.wrl'.\n"
              << std::endl;
    
    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG

    _client_win = OSG::GLUTWindow::create();

    _client_win->setGlutId(winid);
    _client_win->init();
    _client_win->setSize(300,300);
    
    for(OSG::Int32 i=0;i<argc-1;++i)
    {
        if(argv[i+1] != NULL)
            _pipenames.push_back(argv[i+1]);
    }

    if(_pipenames.empty())
        _pipenames.push_back("pipe0");
    
    _root = OSG::Node::create();
    
    _root->setCore(OSG::Group::create());
    
    // create default scene
    OSG::NodeUnrecPtr scene = OSG::makeTorus(.5, 2, 16, 16);

    _root->addChild(scene);

    // create the SimpleSceneManager helper
    _mgr = new OSG::SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_client_win );
    _mgr->setRoot  (_root);

    // show the whole scene
    _mgr->showAll();
    
    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

    glutMainLoop();

    return 0;
}

static void connectCluster(void)
{
    if(_cluster_win != NULL)
        return;

    OSG::Viewport *clientvp = _client_win->getPort(0);
    
    // create the viewports for the cluster just a simple one ...
    OSG::ViewportUnrecPtr vp = OSG::Viewport::create();

    vp->setCamera    (_mgr->getCamera());
    vp->setBackground(clientvp->getBackground());
    vp->setRoot      (clientvp->getRoot());
    vp->setSize      (0,0, 1,1);

    // the connection between this client and the servers
    _cluster_win = OSG::MultiDisplayWindow::create();

    // all changes must be enclosed in beginEditCP and endEditCP
    // otherwise the changes will not be transfered over the network.

    for(OSG::UInt32 i=0;i<_pipenames.size();++i)
        _cluster_win->editMFServers()->push_back(_pipenames[i]);
    // dummy size for navigator
    _cluster_win->setSize(300,300);
    _cluster_win->addPort(vp);

    OSG::Thread::getCurrentChangeList()->commitChangesAndClear();
    OSG::Thread::getCurrentChangeList()->fillFromCurrentState();
    //Thread::getCurrentChangeList()->dump();
    // create from the current state a changelist.

    // initialize window
    _cluster_win->init();

    // apply changelist to the servers
    _cluster_win->render(_mgr->getRenderAction());

    // clear changelist
    OSG::Thread::getCurrentChangeList()->clear();

    glutPostRedisplay();
}

static void disconnectCluster(void)
{
    if(_cluster_win == NULL)
        return;

    _cluster_win = NULL;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    // redraw the client window
    _mgr->redraw();


    OSG::commitChanges();

    try
    {
        if(_cluster_win != NULL)
        {
            // redraw the server windows
            _cluster_win->render(_mgr->getRenderAction());
        }
    }
    
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &)
    {
        //printf("error: '%s'\n", e.what());
        printf("ClusterServer was killed!\n");

        _cluster_win = NULL;
    } 
    
    OSG::commitChanges();
    OSG::clearChangeList();
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
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);

    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:    
        {
            delete _mgr;

            _client_win  = NULL;
            _cluster_win = NULL;
            _root        = NULL;

            OSG::osgExit();
            exit(0);
        }
        case 'n':
            while(_root->getNChildren() > 0)
                _root->subChild(_root->getChild(0));

            glutPostRedisplay();
        break;
        case 'l':
        {
            OSG::NodeUnrecPtr scene = 
                OSG::SceneFileHandler::the()->read("tie.wrl", NULL);

            if(scene != NULL)
            {
                _root->addChild(scene);

                _mgr->showAll();

                glutPostRedisplay();
            }
        }
        break;
        case 't':
        {
            OSG::NodeUnrecPtr scene = OSG::makeTorus(.5, 2, 16, 16);

            _root->addChild(scene);

            _mgr->showAll();

            glutPostRedisplay();
        }
        break;
        case 'c':
            connectCluster();
        break;
        case 'd':
            disconnectCluster();
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
