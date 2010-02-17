// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGThreadManager.h>

OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr         scene;

int setupGLUT(int *argc, char *argv[]);

OSG::NodeTransitPtr createScenegraph(void)
{
    // the scene must be created here
    OSG::NodeRecPtr n = OSG::makeSphere(2,2);
    return OSG::NodeTransitPtr(n);
}

void printA(void *args)
{
    while (true)
        SLOG << "Thread One 11111" << std::endl;
}

void printB(void *args)
{
    while (true)
        SLOG << "Thread Two 22222" << std::endl;
}

int main(int argc, char **argv)
{
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin= OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        scene = createScenegraph();
    
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        OSG::ThreadRefPtr threadOne =
            OSG::dynamic_pointer_cast<OSG::Thread>(
                OSG::ThreadManager::the()->getThread("One", false));

        OSG::ThreadRefPtr threadTwo =
            OSG::dynamic_pointer_cast<OSG::Thread>(
                OSG::ThreadManager::the()->getThread("Two", false));
        
        threadOne->runFunction(printA, 1, NULL);
        threadTwo->runFunction(printB, 1, NULL);
        
        OSG::commitChanges();
    }
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
        mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    return winid;
}
