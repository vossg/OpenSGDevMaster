
#include "OSGConfig.h"
#include "OSGGLUT.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGComponentTransform.h"
#include "OSGGroup.h"

#include "OSGAnimation.h"
#include "OSGAnimBindAction.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimTargetAttachment.h"
#include "OSGTimeSensor.h"

OSG_USING_NAMESPACE

SimpleSceneManager *mgr    = NULL;
ComponentTransform *gXForm = NULL;


// anim stuff
AnimTemplateUnrecPtr g_at0;
AnimTemplateUnrecPtr g_at1;

struct AnimInfo
{
    bool              on;
    AnimationUnrecPtr anim;
};

std::vector<AnimInfo> g_anim;

int setupGLUT( int *argc, char *argv[] );

void init   (int argc, char *argv[]);
void cleanup(void                  );

NodeTransitPtr buildScene       (void);
void           buildAnimTemplate(void);
void           buildAnim        (void);


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

    FrameHandler::the()->init();

    mgr->showAll();
}

void cleanup(void)
{
    FrameHandler::the()->shutdown();

    delete mgr;
    mgr = NULL;

    g_at0 = NULL;
    g_at1 = NULL;

    for(UInt32 i = 0; i < g_anim.size(); ++i)
    {
        g_anim[i].anim = NULL;
    }
}

NodeTransitPtr buildScene(void)
{
    NodeUnrecPtr geoN = makeBox(1.f, 1.f, 1.f, 1, 1, 1);

    ComponentTransformUnrecPtr xform  = ComponentTransform::create();
    NodeUnrecPtr               xformN = makeNodeFor(xform);
    
    setTargetId(xform, "xform0");

    gXForm = xform;

    NodeUnrecPtr      groupN = makeCoredNode<Group>();

    xformN->addChild(geoN  );
    groupN->addChild(xformN);

    return NodeTransitPtr(groupN);
}

void buildAnimTemplate(void)
{
    std::cout << "\n == buildAnimTemplate == START ==" << std::endl;

    // register AnimBindAction callbacks -- temporarily done here
    AnimBindAction::registerEnterDefault(ComponentTransform::getClassType(),
                                         &bindEnterDefault                  );

    // anim "TranslateX"
    AnimKeyFrameTemplateUnrecPtr at0   = AnimKeyFrameTemplate::create();
    at0->setName("TranslateX");
    
    AnimVec3fDataSourceUnrecPtr  data0 = AnimVec3fDataSource::create();
    data0->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    data0->editMFInValues()->push_back(0.f);
    data0->editMFInValues()->push_back(3.f);
    data0->editMFInValues()->push_back(5.f);

    data0->editMFValues()->push_back(Vec3f( 0.f, 0.f, 0.f));
    data0->editMFValues()->push_back(Vec3f( 1.f, 0.f, 0.f));
    data0->editMFValues()->push_back(Vec3f(-1.f, 0.f, 0.f));

    at0->editMFSources  ()->push_back(data0);
    at0->editMFTargetIds()->push_back("xform0.translation");

    g_at0 = at0;

    
    // anim "Rotate"
    AnimKeyFrameTemplateUnrecPtr     at1   = AnimKeyFrameTemplate::create();
    at1->setName("Rotate");

    AnimQuaternionDataSourceUnrecPtr data1 = AnimQuaternionDataSource::create();
    data1->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);
    
    data1->editMFInValues()->push_back(0.f);
    data1->editMFInValues()->push_back(1.f);
    data1->editMFInValues()->push_back(2.f);
    data1->editMFInValues()->push_back(3.f);

    data1->editMFValues()->push_back(Quaternion(Vec3f(0.f, 1.f, 0.f), 0.25f * Pi));
    data1->editMFValues()->push_back(Quaternion(Vec3f(0.f, 1.f, 0.f), 0.75f * Pi));
    data1->editMFValues()->push_back(Quaternion(Vec3f(0.f, 1.f, 0.f), 1.25f * Pi));
    data1->editMFValues()->push_back(Quaternion(Vec3f(0.f, 1.f, 0.f), 1.75f * Pi));

    at1->editMFSources  ()->push_back(data1);
    at1->editMFTargetIds()->push_back("xform0.rotation");

    AnimQuaternionDataSourceUnrecPtr data2 = AnimQuaternionDataSource::create();
    data2->editMFInterpolationModes()->push_back(AnimKeyFrameDataSource::IM_Linear);

    data2->editMFInValues()->push_back(2.f);
    data2->editMFInValues()->push_back(3.f);
    data2->editMFInValues()->push_back(4.f);
    data2->editMFInValues()->push_back(5.f);
    data2->editMFInValues()->push_back(6.f);

    data2->editMFValues()->push_back(Quaternion(Vec3f(1.f, 0.f, 0.f), 0.25f * Pi));
    data2->editMFValues()->push_back(Quaternion(Vec3f(1.f, 0.f, 0.f), 0.75f * Pi));
    data2->editMFValues()->push_back(Quaternion(Vec3f(1.f, 0.f, 0.f), 1.25f * Pi));
    data2->editMFValues()->push_back(Quaternion(Vec3f(1.f, 0.f, 0.f), 1.75f * Pi));
    data2->editMFValues()->push_back(Quaternion(Vec3f(1.f, 0.f, 0.f), 0.25f * Pi));

    at1->editMFSources  ()->push_back(data2);
    at1->editMFTargetIds()->push_back("xform0.rotation");

    g_at1 = at1;

    std::cout << "\n == buildAnimTemplate == STOP ==" << std::endl;
}

void buildAnim(void)
{
    std::cout << "\n == buildAnim == START ==" << std::endl;

    Node *root = mgr->getRoot();

    g_anim.push_back(AnimInfo());
    g_anim.back().on   = false;
    g_anim.back().anim = g_at0->instantiate(root);
    //g_anim.back().anim->setEnabled(true);

    g_anim.push_back(AnimInfo());
    g_anim.back().on   = false;
    g_anim.back().anim = g_at1->instantiate(root);
    //g_anim.back().anim->setEnabled(true);

    std::cout << "\n == buildAnim == STOP ==" << std::endl;
}

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    init(argc, argv);

    buildAnimTemplate();
    buildAnim();

    glutMainLoop();

    cleanup();

    return 0;
}

void display(void)
{
/*
    std::cout << "FH timeStamp: " << FrameHandler::the()->getTimeStamp()
              << std::endl;

    std::cout <<   "xform0.translation: " << gXForm->getTranslation()
              << "\nxform0.rotation: " << gXForm->getRotation()
              << std::endl;
*/

    FrameHandler::the()->frame();

    commitChangesAndClear();

#if 0
    for(UInt32 i = 0; i < g_anim.size(); ++i)
    {
        g_anim[i].anim->getTimeSensor()->dump();
    }
#endif

    mgr->redraw();

    osgSleep(100);
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

void toggleAnim(UInt32 index, bool loop)
{
    if(g_anim[index].on == true)
    {
        std::cout << "STOP anim " << index << std::endl;
        g_anim[index].anim->stop();
        g_anim[index].on = false;
    }
    else
    {
        if(loop == true)
        {
            std::cout << "START LOOP anim " << index << std::endl;
            g_anim[index].anim->startLoop(FrameHandler::the()->getTimeStamp());
        }
        else
        {
            std::cout << "START anim " << index << std::endl;
            g_anim[index].anim->start(FrameHandler::the()->getTimeStamp());
        }

        g_anim[index].on = true;
    }
}

void resetAnim(UInt32 index)
{
    std::cout << "RESET anim " << index << std::endl;
    g_anim[index].anim->reset();
}

void toggleAnimEnable(UInt32 index)
{
    std::cout << (!g_anim[index].anim->getEnabled() ? "ENABLE anim " : "DISABLE anim ")
              << index << std::endl;

    g_anim[index].anim->setEnabled(!g_anim[index].anim->getEnabled());
}

void increaseTimeScale(UInt32 index)
{
    g_anim[index].anim->getTimeSensor()->setTimeScale(
        1.5 * g_anim[index].anim->getTimeSensor()->getTimeScale());

    std::cout << "TIMESCALE anim " << index 
              << " - " <<  g_anim[index].anim->getTimeSensor()->getTimeScale()
              << std::endl;
}

void decreaseTimeScale(UInt32 index)
{
    g_anim[index].anim->getTimeSensor()->setTimeScale(
        (1/1.5) * g_anim[index].anim->getTimeSensor()->getTimeScale());

    std::cout << "TIMESCALE anim " << index 
              << " - " <<  g_anim[index].anim->getTimeSensor()->getTimeScale()
              << std::endl;
}

void toggleAnimDirection(UInt32 index)
{
    std::cout << (!g_anim[index].anim->getTimeSensor()->getForward() ? "FORWARD anim " : "BACKWARD anim ")
              << index << std::endl;

    g_anim[index].anim->getTimeSensor()->setForward(
        !g_anim[index].anim->getTimeSensor()->getForward());
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

    case 'q':
        toggleAnim(0, false);
        break;
    case 'w':
        toggleAnim(0, true);
        break;
    case 'e':
        resetAnim(0);
        break;
    case 'r':
        toggleAnimEnable(0);
        break;
    case 't':
        increaseTimeScale(0);
        break;
    case 'y':
        decreaseTimeScale(0);
        break;
    case 'u':
        toggleAnimDirection(0);
        break;

    case 'a':
        toggleAnim(1, false);
        break;
    case 's':
        toggleAnim(1, true);
        break;
    case 'd':
        resetAnim(1);
        break;
    case 'f':
        toggleAnimEnable(1);
        break;
    case 'g':
        increaseTimeScale(1);
        break;
    case 'h':
        decreaseTimeScale(1);
        break;
    case 'j':
        toggleAnimDirection(1);
        break;
    }
}



int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG - testTrivialAnim3");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
