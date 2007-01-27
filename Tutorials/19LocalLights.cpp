// OpenSG Tutorial Example: LocalLights
//
// This example shows how to create use local light sources.
// It creates four light sources (red, green, blue, white)
// each light source lights only its subtree.

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSceneFileHandler.h>

// the headers for the SimpleMaterials
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGImage.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *_mgr = NULL;
NodePtr _scene = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{
    _mgr->redraw();
}


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
    _scene = makeCoredNode<Group>();

    // create four lights sharing the same beacon.
    TransformPtr light_trans;
    NodePtr light_beacon = makeCoredNode<Transform>(&light_trans);
    light_trans->editMatrix().setTranslate(0.0, 0.0, 10.0);

    // red light.
    PointLightPtr light1_core;
    NodePtr light1 = makeCoredNode<PointLight>(&light1_core);
    light1_core->setAmbient(0.0,0.0,0.0,1);
    light1_core->setDiffuse(1.0,0.0,0.0,1);
    light1_core->setSpecular(0.8,0.8,0.8,1);
    light1_core->setBeacon(light_beacon);
    light1_core->setOn(true);

    // green light.
    PointLightPtr light2_core;
    NodePtr light2 = makeCoredNode<PointLight>(&light2_core);
    light2_core->setAmbient(0.0,0.0,0.0,1);
    light2_core->setDiffuse(0.0,1.0,0.0,1);
    light2_core->setSpecular(0.8,0.8,0.8,1);
    light2_core->setBeacon(light_beacon);
    light2_core->setOn(true);
    
    // blue light.
    PointLightPtr light3_core;
    NodePtr light3 = makeCoredNode<PointLight>(&light3_core);
    light3_core->setAmbient(0.0,0.0,0.0,1);
    light3_core->setDiffuse(0.0,0.0,1.0,1);
    light3_core->setSpecular(0.8,0.8,0.8,1);
    light3_core->setBeacon(light_beacon);
    light3_core->setOn(true);

    // white light.
    PointLightPtr light4_core;
    NodePtr light4 = makeCoredNode<PointLight>(&light4_core);
    light4_core->setAmbient(0.0,0.0,0.0,1);
    light4_core->setDiffuse(1.0,1.0,1.0,1);
    light4_core->setSpecular(0.0,0.0,0.0,1);
    light4_core->setBeacon(light_beacon);
    light4_core->setOn(true);

    NodePtr bottom = makePlane(25.0, 25.0, 128, 128);

    // create three spheres.
    NodePtr sphere1 = makeLatLongSphere(50, 50, 1.0);
    TransformPtr sphere1_trans_core;
    NodePtr sphere1_trans = makeCoredNode<Transform>(&sphere1_trans_core);
    sphere1_trans_core->editMatrix().setTranslate(-5.0, 0.0, 5.0);
    sphere1_trans->addChild(sphere1);
    
    NodePtr sphere2 = makeLatLongSphere(50, 50, 1.0);
    TransformPtr sphere2_trans_core;
    NodePtr sphere2_trans = makeCoredNode<Transform>(&sphere2_trans_core);
    sphere2_trans_core->editMatrix().setTranslate(0.0, 0.0, 5.0);
    sphere2_trans->addChild(sphere2);
    
    NodePtr sphere3 = makeLatLongSphere(50, 50, 1.0);
    TransformPtr sphere3_trans_core;
    NodePtr sphere3_trans = makeCoredNode<Transform>(&sphere3_trans_core);
    sphere3_trans_core->editMatrix().setTranslate(5.0, 0.0, 5.0);
    sphere3_trans->addChild(sphere3);
    
    light1->addChild(sphere1_trans);
    light2->addChild(sphere2_trans);
    light3->addChild(sphere3_trans);
    light4->addChild(bottom);

    _scene->addChild(light_beacon);
    _scene->addChild(light1);
    _scene->addChild(light2);
    _scene->addChild(light3);
    _scene->addChild(light4);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (_scene);
    _mgr->turnHeadlightOff();

    // show the whole scene
    _mgr->showAll();

    // enable local lights.
    RenderAction *ract = (RenderAction *) _mgr->getAction();
    ract->setLocalLights(true);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            OSG::osgExit();
            exit(0);
        break;
        case 'w':
            SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.\n");
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
