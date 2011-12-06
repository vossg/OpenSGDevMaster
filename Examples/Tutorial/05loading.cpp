// all needed include files
#ifdef OSG_BUILD_ACTIVE
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

//additional include files
#include <OSGSceneFileHandler.h>
#else
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional include files
#include <OpenSG/OSGSceneFileHandler.h>
#endif


OSG::SimpleSceneManager *mgr;
OSG::NodeRecPtr          scene;

int setupGLUT( int *argc, char *argv[] );

OSG::NodeTransitPtr createScenegraph(void)
{
    // the scene must be created here
    
    OSG::NodeRecPtr n = OSG::SceneFileHandler::the()->read("Data/terrain.wrl");
    
    //we check the result
    if (n != NULL)
        return OSG::NodeTransitPtr(n);
    else
    {
        std::cout << "Loading the specified file was not possible!"
                  << std::endl;
        return OSG::NodeTransitPtr();
    }
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

void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 's':
        OSG::SceneFileHandler::the()->write(scene, "output.osb");
        
        std::cout << "File written!" << std::endl;
        break;
    }
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
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    
    return winid;
}
