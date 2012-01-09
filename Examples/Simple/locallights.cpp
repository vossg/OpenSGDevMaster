// OpenSG Tutorial Example: Local Lights
//
// This example shows how to create and use local light sources.
// It creates four light sources (red, green, blue, white)
// each light source lights only its subtree.

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGPointLight.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>

// the headers for the SimpleMaterials
#include <OSGSimpleMaterial.h>
#include <OSGImage.h>
#else
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
#endif


// The SimpleSceneManager to manage simple applications
OSG::SimpleSceneManagerRefPtr _mgr   = NULL;
OSG::NodeRefPtr               _scene;

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
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the scene
        _scene = OSG::makeCoredNode<OSG::Group>();
    
        // create four lights sharing the same beacon.
        OSG::TransformRefPtr light_trans;
        OSG::NodeRefPtr      light_beacon = 
            OSG::makeCoredNode<OSG::Transform>(&light_trans);
        light_trans->editMatrix().setTranslate(0.0, 0.0, 10.0);
    
        // red light.
        OSG::PointLightRefPtr light1_core;
        OSG::NodeRefPtr       light1      = 
            OSG::makeCoredNode<OSG::PointLight>(&light1_core);
        light1_core->setAmbient(0.0,0.0,0.0,1);
        light1_core->setDiffuse(1.0,0.0,0.0,1);
        light1_core->setSpecular(0.8f,0.8f,0.8f,1);
        light1_core->setBeacon(light_beacon);
        light1_core->setOn(true);
    
        // green light.
        OSG::PointLightRefPtr light2_core;
        OSG::NodeRefPtr       light2      = 
            OSG::makeCoredNode<OSG::PointLight>(&light2_core);
        light2_core->setAmbient(0.0,0.0,0.0,1);
        light2_core->setDiffuse(0.0,1.0,0.0,1);
        light2_core->setSpecular(0.8f,0.8f,0.8f,1);
        light2_core->setBeacon(light_beacon);
        light2_core->setOn(true);
        
        // blue light.
        OSG::PointLightRefPtr light3_core;
        OSG::NodeRefPtr       light3      = 
            OSG::makeCoredNode<OSG::PointLight>(&light3_core);
        light3_core->setAmbient(0.0,0.0,0.0,1);
        light3_core->setDiffuse(0.0,0.0,1.0,1);
        light3_core->setSpecular(0.8f,0.8f,0.8f,1);
        light3_core->setBeacon(light_beacon);
        light3_core->setOn(true);
    
        // white light.
        OSG::PointLightRefPtr light4_core;
        OSG::NodeRefPtr       light4      = 
            OSG::makeCoredNode<OSG::PointLight>(&light4_core);
        light4_core->setAmbient(0.0,0.0,0.0,1);
        light4_core->setDiffuse(1.0,1.0,1.0,1);
        light4_core->setSpecular(0.0,0.0,0.0,1);
        light4_core->setBeacon(light_beacon);
        light4_core->setOn(true);
    
        OSG::NodeRefPtr bottom = OSG::makePlane(25.0, 25.0, 128, 128);
    
        // create three spheres.
        OSG::NodeRefPtr      sphere1 = OSG::makeLatLongSphere(50, 50, 1.0);
        OSG::TransformRefPtr sphere1_trans_core;
        OSG::NodeRefPtr      sphere1_trans = 
            OSG::makeCoredNode<OSG::Transform>(&sphere1_trans_core);
        sphere1_trans_core->editMatrix().setTranslate(-5.0, 0.0, 5.0);
        sphere1_trans->addChild(sphere1);
        
        OSG::NodeRefPtr      sphere2 = OSG::makeLatLongSphere(50, 50, 1.0);
        OSG::TransformRefPtr sphere2_trans_core;
        OSG::NodeRefPtr      sphere2_trans = 
            OSG::makeCoredNode<OSG::Transform>(&sphere2_trans_core);
        sphere2_trans_core->editMatrix().setTranslate(0.0, 0.0, 5.0);
        sphere2_trans->addChild(sphere2);
        
        OSG::NodeRefPtr      sphere3 = OSG::makeLatLongSphere(50, 50, 1.0);
        OSG::TransformRefPtr sphere3_trans_core;
        OSG::NodeRefPtr      sphere3_trans = 
            OSG::makeCoredNode<OSG::Transform>(&sphere3_trans_core);
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
    
        OSG::commitChanges();
    
        // create the SimpleSceneManager helper
        _mgr = OSG::SimpleSceneManager::create();
    
        // tell the manager what to manage
        _mgr->setWindow(gwin );
        _mgr->setRoot  (_scene);
        _mgr->turnHeadlightOff();
    
        // show the whole scene
        _mgr->showAll();
    }

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
            
            // clean up global variables
            _mgr   = NULL;
            _scene = NULL;
            
            OSG::osgExit();
            exit(0);
        break;
        case 'w':
            OSG::SceneFileHandler::the()->write(_scene, "scene.osb.gz", true);
            printf("wrote scene.\n");
        break;

        case 's':
        {
            _mgr->setStatistics(!_mgr->getStatistics());
        }
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
