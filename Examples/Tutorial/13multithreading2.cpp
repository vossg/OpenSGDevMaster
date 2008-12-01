// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGThreadManager.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// we will store the transformation globally - this
// is not necessary, but comfortable
// Note that these global objects are accessed from different aspects,
// therefore you need to use MTRecPtr here, so that you get a pointer to the
// correct aspect copy of the object.

TransformMTRecPtr  trans;
NodeMTRecPtr       scene;
Thread            *animationThread;
Thread            *applicationThread;
Barrier           *syncBarrier;

int setupGLUT(int *argc, char *argv[]);

NodeTransitPtr createScenegraph(void)
{
    // the scene must be created here
    NodeRecPtr n = makeTorus(.5,2,16,16);
    
    //add a simple Transformation
    trans = Transform::create();
    Matrix m;
    m.setIdentity();
    trans->setMatrix(m);
    
    NodeRecPtr transNode = Node::create();
    transNode->setCore(trans);
    transNode->addChild(n);
    
    return NodeTransitPtr(transNode);
}

//this function will run in a thread and simply will
//rotate the cube by setting a new transformation matrix
void rotate(void *args)
{
    // sync this thread to the main thread, i.e. pull in all changes done
    // during scene construction
    syncBarrier->enter(2);
    applicationThread->getChangeList()->applyAndClear();
    syncBarrier->enter(2);
    
    // we won't stop calculating new matrices....
    while(true)
    {
        Real32 time = glutGet(GLUT_ELAPSED_TIME);
        Matrix m;
        m.setIdentity();
        m.setRotate(Quaternion(Vec3f(0,1,0), time/1000));
        
        trans->setMatrix(m);
        // nothing unusual until here
        
        // we are done with changing this aspect copy (for this iteration),
        // committing the changes makes sure they are being picked up when
        // the render thread syncronizes the next time.
        commitChanges();
        
        //well that's new...
        
        //wait until two threads are cought in the
        //same barrier
        syncBarrier->enter(2);    // barrier (1)
        
        //just the same again
        syncBarrier->enter(2);    // barrier (2)
    }
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        GLUTWindowRecPtr gwin = GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        scene = createScenegraph();
        
        //create the barrier, that will be used to
        //synchronize threads
        
        //instead of NULL you could provide a name
        syncBarrier = Barrier::get(NULL);
        
        mgr = new SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        // store a pointer to the application thread
        applicationThread = dynamic_cast<Thread *>(ThreadManager::getAppThread());
        
        //create the thread that will run generation of new matrices
        animationThread = dynamic_cast<Thread *>(ThreadManager::the()->getThread("anim"));
        
        //do it...
        animationThread->runFunction(rotate, 1, NULL);
        
        // wait for animationThread to complete its sync
        syncBarrier->enter(2);
        syncBarrier->enter(2);
        
        commitChanges();
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
    // we wait here until the animation thread enters
    // barrier (1)
    syncBarrier->enter(2);
    
    //now we sync data
    animationThread->getChangeList()->applyAndClear();
    
    // now wait for animation thread to enter barrier (2)
    syncBarrier->enter(2);
    
    // !!!! Attention
    // you will find a more detailed description
    // of what's going on here in the documentation
    // itself!
    
    // now render...
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
