// OpenSG example: callback.cpp
//
// This example shows how to establish a callback which is executed once on 
// each render traversal. This can be useful for applications which have to 
// render native OpenGL code, for various reasons.
//
// To be absolutely clear, this callback technique for native OpenGL rendering
// is not applicable in a cluster setup and it should only be exceptionally 
// used at special circumstances.
//
// Especially demonstrated is the use of the following classes:
//      - CallbackAlgorithm
//      - VisitSubTree, 
//      - AlgorithmStage
//      - DrawEnv
//
// This examples renders a torus or if no model file is provided at the command
// line.
//
// User interface:
//  a) mouse => standard navigator
//

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGAction.h>
#include <OSGCallbackAlgorithm.h>
#include <OSGAlgorithmStage.h>
#include <OSGVisitSubTree.h>
#include <OSGDrawEnv.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGCallbackAlgorithm.h>
#include <OpenSG/OSGAlgorithmStage.h>
#include <OpenSG/OSGSimpleStage.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGDrawEnv.h>
#endif

using namespace OSG; // just for convenience but not recommended

//
// function forward declarations
//
static void onExit();
static void cleanup(void);
static void display(void);
static void reshape(int w, int h);
static void mouse(int button, int state, int x, int y);
static void motion(int x, int y);
static void keyboard(unsigned char k, int, int);
static int  setupGLUT(int *argc, char *argv[]);
static int  doMain(int argc, char *argv[]);
static void addStage();
static void theCallback(DrawEnv* env);

//
// global state of example
//
SimpleSceneManager* mgr;
NodeRefPtr          root;
NodeRefPtr          scene;
GLUTWindowRefPtr    win;


static void onExit()
{
    commitChanges();

    cleanup();
    osgExit();
}

static void cleanup(void)
{
    mgr->setWindow(NULL);
    mgr->setRoot(NULL);

    delete mgr;
    mgr   = NULL;
    root  = NULL;
    scene = NULL;
    win   = NULL;
}

static void display(void)
{
    commitChanges();
    mgr->redraw();
}

static void reshape(int w, int h)
{
    mgr->resize(w,h);
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

static void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

static void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:
    case 'q':
    {
        std::exit(EXIT_SUCCESS);
    }
    break;
    }
}

static void addStage()
{
    //
    // We would like to render the scene but won't detach it from its parent.
    // The VisitSubTree allows just that.
    //
    VisitSubTreeUnrecPtr visitor = VisitSubTree::create();
    visitor->setSubTreeRoot(scene);
    NodeUnrecPtr visit_node = makeNodeFor(visitor);

    //
    // Algorithm object: CallbackAlgorithm is kind of Algorithm
    //
    CallbackAlgorithmUnrecPtr algo = CallbackAlgorithm::create();
    algo->setCallback(theCallback, "");
    //
    // Stage object
    //
    AlgorithmStageUnrecPtr stage = AlgorithmStage::create();
    stage->setAlgorithm(algo);

    //
    // Give the stage core a place to live
    //
    NodeUnrecPtr stage_node = makeNodeFor(stage);
    stage_node->addChild(visit_node);

    root->addChild(stage_node);
}

static void theCallback(DrawEnv* env)
{
    //
    // Save the current state
    //
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //
    // Setup current viewport
    //
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(env->getVPCameraFullProjection().getValues());

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(env->getVPCameraViewing().getValues());

    //
    // State initialization
    //
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //
    // Some model geometry
    //
    glPushMatrix();
    glTranslatef(-1.5f,0.0f,-6.0f);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1.0f,-1.0f, -1.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-1.0f,-1.0f, -1.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.5f,0.0f,-7.0f);
    glBegin(GL_QUADS);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);

        glColor3f(1.0f,0.5f,0.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);

        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f( 1.0f, 1.0f,-1.0f);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);

        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( 1.0f, 1.0f,-1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);
    glEnd();
    glPopMatrix();

    //
    // Restore the state
    //
    glPopAttrib();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

//
// initialize GLUT
//
static int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}

//
// setup scene
//
static int doMain(int argc, char *argv[])
{
    preloadSharedObject("OSGFileIO");
    preloadSharedObject("OSGImageFileIO");
    preloadSharedObject("OSGContribPLY");
    
    osgInit(argc,argv);

    int winid = setupGLUT(&argc, argv);

    win = GLUTWindow::create();
    win->setGlutId(winid);
    win->init();

    root = Node::create();
    root->setCore(Group::create());

    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));

        std::list<const char*> suffixes;
        SceneFileHandler::the()->getSuffixList(suffixes);

        for(std::list<const char*>::iterator it  = suffixes.begin();
                                            it != suffixes.end();
                                        ++it)
        {
            FWARNING(("%s\n", *it));
        }

        scene = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        scene = SceneFileHandler::the()->read(argv[1]);
    }

    root->addChild(scene);

    addStage();
    
    commitChanges();
    
    mgr = new SimpleSceneManager;

    mgr->setWindow(win);
    mgr->setRoot  (root);
    
    mgr->showAll();
    
    return 0;
}

//
// main entry point
//
int main(int argc, char *argv[])
{
    int ret = doMain(argc, argv);

    atexit(onExit);

    glutMainLoop();

    cleanup();

    osgExit();

    return ret;
}


