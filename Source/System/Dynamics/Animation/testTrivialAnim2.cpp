
#include "OSGConfig.h"
#include "OSGGLUT.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGComponentTransform.h"
#include "OSGGroup.h"

#include "OSGAnimation.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimTimeSensor.h"

OSG_USING_NAMESPACE

SimpleSceneManager *mgr    = NULL;
ComponentTransform *gXForm = NULL;


// anim stuff
AnimTimeSensorUnrecPtr      ts0;
AnimVec3fChannelUnrecPtr    c0;
AnimVec3fDataSourceUnrecPtr data0;
AnimationUnrecPtr           anim0;


int setupGLUT( int *argc, char *argv[] );

void init(void);
void cleanup(void);

NodeTransitPtr buildScene(void);
void           buildAnim (void);


void init(int argc, char *argv[])
{
    int winId = setupGLUT(&argc, argv);
    
    GLUTWindowUnrecPtr gwin = GLUTWindow::create();
    gwin->setGlutId(winId);
    gwin->init     (     );

    NodeUnrecPtr scene = buildScene();

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    mgr->showAll();
}

void cleanup(void)
{
    delete mgr;
    mgr = NULL;

    ts0          = NULL;
    c0           = NULL;
    data0        = NULL;
    anim0        = NULL;
}

NodeTransitPtr buildScene(void)
{
    NodeUnrecPtr geoN = makeBox(1.f, 1.f, 1.f, 1, 1, 1);

    ComponentTransformUnrecPtr xform  = ComponentTransform::create();
    NodeUnrecPtr               xformN = makeNodeFor(xform);

    gXForm = xform;

    NodeUnrecPtr      groupN = makeCoredNode<Group>();

    xformN->addChild(geoN  );
    groupN->addChild(xformN);

    return NodeTransitPtr(groupN);
}

void buildAnim(void)
{
    // set up time sensor
    ts0 = AnimTimeSensor::create();
    ts0->setStartTime  (5.f);
    ts0->setStopTime   (2.f);
    ts0->setCycleLength(3.f);

    // data source
    data0 = AnimVec3fDataSource::create();
    data0->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    data0->editMFInValues()->push_back(0.f);
    data0->editMFInValues()->push_back(1.f);
    data0->editMFInValues()->push_back(3.f);

    data0->editMFValues()->push_back(Vec3f(0.f, 0.f, 0.f));
    data0->editMFValues()->push_back(Vec3f(1.f, 0.f, 0.f));
    data0->editMFValues()->push_back(Vec3f(1.f, 2.f, 0.f));

    // data sink
    c0 = AnimVec3fChannel::create();
    c0->setData(data0);

    anim0 = Animation::create();
    anim0->editMFChannels()->push_back(c0);
    anim0->setTimeSensor(ts0);
    anim0->setWeight    (1.f);

    // connect sink to scene
    addConnection(c0, "outValue", gXForm, "translation");

    FrameHandler::the()->addTask(ts0);
}

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    init(argc, argv);

    buildAnim();

    glutMainLoop();

    cleanup();

    return 0;
}

void display(void)
{
    std::cout << "FH timeStamp: " << FrameHandler::the()->getTimeStamp()
              << std::endl;
    std::cout << "TS time: " << ts0->getTime()
              << std::endl;

    std::cout << "gXForm.translation: " << gXForm->getTranslation()
              << std::endl;

    FrameHandler::the()->frame();

    commitChangesAndClear();

    mgr->redraw();
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void idle(void)
{
    mgr->idle();
    glutPostRedisplay();
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

void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:
        cleanup();
        osgExit();

        exit(0);
        break;
    }
}



int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG - testTrivialAnim2");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
