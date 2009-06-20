
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OSGCubes.h>

OSG_USING_NAMESPACE

Real32 random(Real32 lower, Real32 upper)
{
    return lower + osgRand() * (upper - lower);
}


SimpleSceneManager *mgr;
NodeUnrecPtr        cubesN;
CubesUnrecPtr       cubes;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void init(int argc, char *argv[])
{
    osgInit(argc, argv);

    int winId = setupGLUT(&argc, argv);

    GLUTWindowUnrecPtr gwin = GLUTWindow::create();
    gwin->setGlutId(winId);
    gwin->init     (     );

    cubes  = Cubes::create();
    cubesN = makeNodeFor(cubes);

    cubes->setMaterial(getDefaultMaterial());

    for(UInt32 i = 0; i < 10; ++i)
    {
        cubes->editMFPosition()->push_back(
            Pnt3f  (random(-2.f, 2.f), random(-2.f, 2.f), random(-2.f, 2.f)));
        cubes->editMFLength  ()->push_back(random(0.5f, 2.f));
        cubes->editMFColor   ()->push_back(
            Color3f(random(0.5f, 1.f), random(0.5f, 1.f), random(0.5f, 1.f)));
    }

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin  );
    mgr->setRoot  (cubesN);

    mgr->showAll();

    commitChanges();
}

void fini(void)
{
    delete mgr;
    mgr    = NULL;
    
    cubesN = NULL;
    cubes  = NULL;

    commitChanges();

    osgExit();
}

int main(int argc, char *argv[])
{
    init(argc, argv);

    SLOG << "OpenSG CubesApp\n"
         << "  <ESC>      exit\n"
         << "  <space>    add a new cube\n"
         << "  a          auto position camera to show the whole scene\n"
         << "  v          toggle bounding volume drawing"
         << std::endl;

    glutMainLoop();

    fini();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    
    {
        fini( );
        exit(0);
    }
    break;

    case 'a':
    {
        mgr->showAll();
    }  
    break;

    case ' ':
    {
        // Add a new cube
        cubes->editMFPosition()->push_back(
            Pnt3f(random(-4.f, 4.f), random(-4.f, 4.f), random(-4.f, 4.f)));
        cubes->editMFLength  ()->push_back(random(0.5f, 2.f));
        cubes->editMFColor   ()->push_back(
            Color3f(random(0.5f, 1.f), random(0.5f, 1.f), random(0.5f, 1.f)));

        commitChanges();
    }
    break;
    
    case 'v':   
    {
        bool vd = mgr->getRenderAction()->getVolumeDrawing();
        mgr->getRenderAction()->setVolumeDrawing(!vd);
        SLOG << "Volume Drawing set to " << !vd << endLog;
    }
    break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG CubesApp");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
