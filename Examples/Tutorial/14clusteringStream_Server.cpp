#ifdef OSG_BUILD_ACTIVE
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGClusterServer.h>
#include <OSGGLUTWindow.h>
#include <OSGRenderAction.h>
#else
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGClusterServer.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGRenderAction.h>
#endif

OSG::GLUTWindowRecPtr    window;
OSG::RenderActionRefPtr  ract;
OSG::ClusterServer      *server;

void display(void);
void reshape(int width, int height);

int main(int argc,char **argv)
{
    int winid;

    // initialize Glut
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB |GLUT_DEPTH | GLUT_DOUBLE);

    if(!argv[1])
    {
        std::cout << "No name was given!" << std::endl;
        return -1;
    }
    
    // init OpenSG
    OSG::osgInit(argc, argv);

    winid = glutCreateWindow(argv[1]);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutSetCursor(GLUT_CURSOR_NONE);

    ract = OSG::RenderAction::create();

    window = OSG::GLUTWindow::create();
    window->setGlutId(winid);
    window->init();

    window->resize(512, 512);

    //create a new server that will be connected via multicast
    //argv[1] is the name of the server (at least it should be...)
    server = new OSG::ClusterServer(window, argv[1], "StreamSock", "");
    server->start();

    glutMainLoop();

    return 0;
}

void display(void)
{
    //simply execute the render action
    server->render(ract);
    //and delete the change list
    OSG::Thread::getCurrentChangeList()->clear();
}

void reshape(int width, int height)
{
    window->resize(width, height);
}
