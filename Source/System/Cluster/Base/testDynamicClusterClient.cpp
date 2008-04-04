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


#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGMultiDisplayWindow.h>
#include <OSGSceneFileHandler.h>
#include <OSGRemoteAspect.h>
#include <OSGFieldContainerFactory.h>

#include <string>
#include <vector>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager          *_mgr = NULL;
GLUTWindowRefPtr            _client_win = NullFC;
MultiDisplayWindowRefPtr    _cluster_win = NullFC;
NodeRefPtr                  _root = NullFC;
std::vector<std::string>    _pipenames;
UInt32                      _first_fc = 0;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    std::cout << "start a cluster server with './testClusterServer -w pipe0'\n"
                 "press 'c' to connect to the servers.\n"
                 "press 'd' to disconnect from the servers.\n"
                 "press 'n' to delete current scene.\n"
                 "press 't' to create a torus.\n"
                 "press 'l' to load scene 'tie.wrl'.\n"
              << std::endl;
    
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG

    _client_win = GLUTWindow::create();

    // this is our first created fieldcontainer pointer we need this
    // to skip the prototypes in createCurrentStateChangeList().
    _first_fc = getContainerId(_client_win);

    fprintf(stderr, "%d -> %d\n", 
            _first_fc,
            FieldContainerFactory::the()->getNumContainers());

    _client_win->setGlutId(winid);
    _client_win->init();
    _client_win->setSize(300,300);
    
    for(UInt32 i=0;i<argc-1;++i)
    {
        if(argv[i+1] != NULL)
            _pipenames.push_back(argv[i+1]);
    }

    if(_pipenames.empty())
        _pipenames.push_back("pipe0");
    
    _root = Node::create();
    
    _root->setCore(Group::create());
    
    // create default scene
    NodeUnrecPtr scene = makeTorus(.5, 2, 16, 16);

    _root->addChild(scene);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(_client_win );
    _mgr->setRoot  (_root);

    // show the whole scene
    _mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}

static void connectCluster(void)
{
    if(_cluster_win != NullFC)
        return;

    ViewportPtr clientvp = _client_win->getPort()[0];
    
    // create the viewports for the cluster just a simple one ...
    ViewportUnrecPtr vp = Viewport::create();

    vp->setCamera    (_mgr->getCamera());
    vp->setBackground(clientvp->getBackground());
    vp->setRoot      (clientvp->getRoot());
    vp->setSize      (0,0, 1,1);

    // the connection between this client and the servers
    _cluster_win = MultiDisplayWindow::create();

    // all changes must be enclosed in beginEditCP and endEditCP
    // otherwise the changes will not be transfered over the network.

    for(UInt32 i=0;i<_pipenames.size();++i)
        _cluster_win->editServers().push_back(_pipenames[i]);
    // dummy size for navigator
    _cluster_win->setSize(300,300);
    _cluster_win->addPort(vp);

    Thread::getCurrentChangeList()->commitChangesAndClear();

    fprintf(stderr, "%d -> %d\n", 
            _first_fc,
            FieldContainerFactory::the()->getNumContainers());

    Thread::getCurrentChangeList()->fillFromCurrentState(_first_fc);
    Thread::getCurrentChangeList()->dump();
    // create from the current state a changelist.

    // initialize window
    _cluster_win->init();

    // apply changelist to the servers
    _cluster_win->render(_mgr->getRenderAction());

    // clear changelist
    Thread::getCurrentChangeList()->clear();

    glutPostRedisplay();
}

static void disconnectCluster(void)
{
    if(_cluster_win == NullFC)
        return;

    //subRefX(_cluster_win);

    _cluster_win = NullFC;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    // redraw the client window
    _mgr->redraw();


    commitChanges();

    try
    {
        if(_cluster_win != NullFC)
        {
            // redraw the server windows
            _cluster_win->render(_mgr->getRenderAction());
        }
    }
    
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        //printf("error: '%s'\n", e.what());
        printf("ClusterServer was killed!\n");

//        subRefX(_cluster_win);

        _cluster_win = NullFC;
    } 
    
    commitChanges();
    clearChangeList();
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

            _client_win  = NullFC;
            _cluster_win = NullFC;
            _root        = NullFC;

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
            NodeUnrecPtr scene = SceneFileHandler::the()->read("tie.wrl", NULL);

            if(scene != NullFC)
            {
                _root->addChild(scene);

                _mgr->showAll();

                glutPostRedisplay();
            }
        }
        break;
        case 't':
        {
            NodeUnrecPtr scene = makeTorus(.5, 2, 16, 16);

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
