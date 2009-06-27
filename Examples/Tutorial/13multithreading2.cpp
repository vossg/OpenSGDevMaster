// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGThreadManager.h>

OSG::SimpleSceneManager *mgr;

// we will store the transformation globally - this
// is not necessary, but comfortable
// Note that these global objects are accessed from different aspects,
// therefore you need to use MTRecPtr here, so that you get a pointer to the
// correct aspect copy of the object.

OSG::TransformMTRecPtr  trans;
OSG::NodeMTRecPtr       scene;
OSG::Thread            *animationThread;
OSG::Thread            *applicationThread;
OSG::Barrier           *syncBarrier;

int setupGLUT(int *argc, char *argv[]);

OSG::NodeTransitPtr createScenegraph(void)
{
    // the scene must be created here
    OSG::NodeRecPtr n = OSG::makeTorus(.5,2,16,16);
    
    //add a simple Transformation
    trans = OSG::Transform::create();
    OSG::Matrix m;
    m.setIdentity();
    trans->setMatrix(m);
    
    OSG::NodeRecPtr transNode = OSG::Node::create();
    transNode->setCore(trans);
    transNode->addChild(n);
    
    return OSG::NodeTransitPtr(transNode);
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

    // clear the local changelist as we only want to sync the
    // real changes we make back.
    OSG::commitChanges();
    animationThread->getChangeList()->clear();


    // we won't stop calculating new matrices....
    while(true)
    {
        OSG::Real32 time = glutGet(GLUT_ELAPSED_TIME);
        OSG::Matrix m;
        m.setIdentity();
        m.setRotate(OSG::Quaternion(OSG::Vec3f(0,1,0), time/1000));
        
        trans->setMatrix(m);
        // nothing unusual until here
        
        // we are done with changing this aspect copy (for this iteration),
        // committing the changes makes sure they are being picked up when
        // the render thread syncronizes the next time.
        OSG::commitChanges();

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
    OSG::ChangeList::setReadWriteDefault(true);
    OSG::osgInit(argc,argv);
    
    {
        int winid = setupGLUT(&argc, argv);
        OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
        
        scene = createScenegraph();
        
        //create the barrier, that will be used to
        //synchronize threads
        
        //instead of NULL you could provide a name
        syncBarrier = OSG::Barrier::get(NULL);
        
        mgr = new OSG::SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
        mgr->showAll();
        
        // store a pointer to the application thread
        applicationThread = 
            dynamic_cast<OSG::Thread *>(OSG::ThreadManager::getAppThread());
        
        //create the thread that will run generation of new matrices
        animationThread = 
            dynamic_cast<OSG::Thread *>(
                OSG::ThreadManager::the()->getThread("anim"));
        
        //do it...
        animationThread->runFunction(rotate, 1, NULL);
        
        // wait for animationThread to complete its sync
        syncBarrier->enter(2);
        syncBarrier->enter(2);
        
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
    // we wait here until the animation thread enters
    // barrier (1)
    syncBarrier->enter(2);

    //now we sync data
    animationThread->getChangeList()->applyAndClear();

    // update dependend data
    OSG::commitChanges();

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
