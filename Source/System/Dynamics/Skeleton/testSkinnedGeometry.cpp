#include "OSGConfig.h"
#include "OSGGLUT.h"
#include "OSGSimpleGeometry.h"
#include "OSGGLUTWindow.h"
#include "OSGSimpleSceneManager.h"
#include "OSGComponentTransform.h"
#include "OSGGroup.h"

#include "OSGSkeleton.h"
#include "OSGSkeletonJoint.h"
#include "OSGSkinnedGeometry.h"

#if 0
#include "OSGAnimation.h"
#include "OSGAnimBindAction.h"
#include "OSGAnimKeyFrameTemplate.h"
#include "OSGAnimVec3fChannel.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimTargetAttachment.h"
#include "OSGTimeSensor.h"
#endif

OSG_USING_NAMESPACE

SimpleSceneManager *mgr    = NULL;
NodeUnrecPtr        sceneN = NULL;
SkeletonUnrecPtr    skel   = NULL;


int setupGLUT(int *argc, char *argv[]);

void init   (int argc, char *argv[]);
void cleanup(void                  );

void buildScene(void);


int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    init(argc, argv);

    glutMainLoop();

    cleanup();

    return 0;
}


void init(int argc, char *argv[])
{
    int winId = setupGLUT(&argc, argv);

    GLUTWindowUnrecPtr gwin = GLUTWindow::create();
    gwin->setGlutId(winId);
    gwin->init     (     );

    buildScene();

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin  );
    mgr->setRoot  (sceneN);

    mgr->showAll();
}


void cleanup(void)
{
    delete mgr;
    mgr    = NULL;

    sceneN = NULL;
}

void buildScene(void)
{
    // construct joints hierarchy
    SkeletonJointUnrecPtr joint0  = SkeletonJoint::create();
    NodeUnrecPtr          joint0N = makeNodeFor(joint0);

    SkeletonJointUnrecPtr jointR1  = SkeletonJoint::create();
    NodeUnrecPtr          jointR1N = makeNodeFor(jointR1);
    SkeletonJointUnrecPtr jointR2  = SkeletonJoint::create();
    NodeUnrecPtr          jointR2N = makeNodeFor(jointR2);

    SkeletonJointUnrecPtr jointL1  = SkeletonJoint::create();
    NodeUnrecPtr          jointL1N = makeNodeFor(jointL1);
    SkeletonJointUnrecPtr jointL2  = SkeletonJoint::create();
    NodeUnrecPtr          jointL2N = makeNodeFor(jointL2);

    joint0N->addChild(jointR1N);
    joint0N->addChild(jointL1N);

    jointR1N->addChild(jointR2N);

    jointL1N->addChild(jointL2N);


    joint0 ->setJointId(0);

    jointR1->setJointId(1);
    jointR2->setJointId(2);

    jointL1->setJointId(3);
    jointL2->setJointId(4);

    //    joint1->editMatrix().setRotate   (Quaternion(Vec3f(0.f, 0.f, 1.f),
    //                                                 osgDegree2Rad(45.f)  ));
    jointR1->editMatrix().setTranslate(Vec3f( 1.f, 1.f, 0.f)             );
    jointR2->editMatrix().setTranslate(Vec3f( 0.f, 1.f, 0.f)             );

    //    joint2->editMatrix().setRotate   (Quaternion(Vec3f(0.f, 0.f, 1.f),
    //                                                 osgDegree2Rad(-45.f) ));
    jointL1->editMatrix().setTranslate(Vec3f(-1.f, 1.f, 0.f)             );
    jointL2->editMatrix().setTranslate(Vec3f( 0.f, 1.f, 0.f)             );

    // construct skeleton
    SkeletonUnrecPtr skel = Skeleton::create();

    skel->editMFRoots()->push_back(joint0N);

    // construct skinned geometry
    SkinnedGeometryUnrecPtr skin = SkinnedGeometry::create();
    sceneN                       = makeNodeFor(skin);

    skin->setSkeleton(skel);
    skin->addFlag(SkinnedGeometry::SG_FLAG_DEBUG);
}


void display(void)
{
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

    case ' ':
        glutPostRedisplay();
        break;
    }

}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG - testSkinnedGeometry");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
