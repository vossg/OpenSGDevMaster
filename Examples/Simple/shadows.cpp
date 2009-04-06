// OpenSG Tutorial Example: Shadows
//
// This example shows realtime shadows via shadow maps.

#ifdef OSG_BUILD_ACTIVE
#include <OSGConfig.h>

#include <OSGGLUT.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGBaseFunctions.h>

#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGGradientBackground.h>
#include <OSGSolidBackground.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

// New Headers
#include <OSGSimpleShadowMapEngine.h>
#else
#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGBaseFunctions.h>

#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

// New Headers
#include <OpenSG/OSGSimpleShadowMapEngine.h>
#endif


/*
    This tutorial has quite a few global objects, to simplify the cleanup at
    program exit we put them all in a struct.
*/

struct GlobalObjects
{
    OSG::SimpleSceneManager     *mgr;

    OSG::GLUTWindowRefPtr        gwin;

    OSG::NodeRefPtr              rootNode;
    OSG::SpotLightRefPtr         spot1_core;
    OSG::SpotLightRefPtr         spot2_core;
    OSG::DirectionalLightRefPtr  dir_core;
    OSG::PointLightRefPtr        point1_core;
    OSG::PointLightRefPtr        point2_core;
    OSG::TransformRefPtr         box_trans;
    OSG::TransformRefPtr         cylinder1_trans;
    OSG::TransformRefPtr         cylinder2_trans;
};

GlobalObjects *globals = NULL;

const OSG::UInt32 SM_RESOLUTION = 1024;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf("Press key '1' or '2' to switch between one and two light sources.\n");
    // OSG init
    OSG::osgInit(argc,argv);

    globals = new GlobalObjects;
    
    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // GLUT init
        int winid = setupGLUT(&argc, argv);
        globals->gwin = OSG::GLUTWindow::create();
    
        /*
            Construct a scene with a ground plane, some objects and two lights.
            Nothing very interesting at this point.
            See further down for the part relevant to shadows.
        */
        
        globals->rootNode      = OSG::makeCoredNode<OSG::Group>();
        OSG::NodeRefPtr  scene = OSG::makeCoredNode<OSG::Group>();
    
        // create lights
        OSG::TransformRefPtr point1_trans;
        OSG::NodeRefPtr point1        = OSG::makeCoredNode<OSG::PointLight>(&globals->point1_core);
        OSG::NodeRefPtr point1_beacon = OSG::makeCoredNode<OSG::Transform >(&point1_trans);
        
        point1_trans->editMatrix().setTranslate(0.0, 0.0, 15.0);
        
        globals->point1_core->setAmbient(0.15,0.15,0.15,1);
        globals->point1_core->setDiffuse(0.4,0.4,0.4,1);
        globals->point1_core->setSpecular(0.0,0.0,0.0,1);
        globals->point1_core->setBeacon(point1_beacon);
        globals->point1_core->setOn(true);
        
        OSG::TransformRefPtr point2_trans;
        OSG::NodeRefPtr point2        = OSG::makeCoredNode<OSG::PointLight>(&globals->point2_core);
        OSG::NodeRefPtr point2_beacon = OSG::makeCoredNode<OSG::Transform >(&point2_trans);
        
        point2_trans->editMatrix().setTranslate(2.5, 2.5, 15.0);
        
        globals->point2_core->setAmbient(0.15,0.15,0.15,1);
        globals->point2_core->setDiffuse(0.4,0.4,0.4,1);
        globals->point2_core->setSpecular(0.0,0.0,0.0,1);
        globals->point2_core->setBeacon(point2_beacon);
        globals->point2_core->setOn(true);
        
        point1->addChild(point2);
        point2->addChild(scene );
        
        // create scene
        
        // bottom
        OSG::NodeRefPtr plane = OSG::makePlane(25.0, 25.0, 128, 128);
    
        OSG::UChar8 imgdata[] =
            {  255,0,0,  0,255,0,  0,0,255, 255,255,0 };
        OSG::ImageRefPtr plane_img = OSG::Image::create();
        plane_img->set(OSG::Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);
    
        OSG::TextureObjChunkRefPtr plane_tex = OSG::TextureObjChunk::create();
        plane_tex->setImage(plane_img);
        plane_tex->setMinFilter(GL_LINEAR);
        plane_tex->setMagFilter(GL_LINEAR);
        plane_tex->setWrapS(GL_REPEAT);
        plane_tex->setWrapT(GL_REPEAT);
        
        OSG::TextureEnvChunkRefPtr plane_tex_env = OSG::TextureEnvChunk::create();
        plane_tex_env->setEnvMode(GL_MODULATE);
    
        OSG::SimpleMaterialRefPtr plane_mat = OSG::SimpleMaterial::create();
        plane_mat->setAmbient(OSG::Color3f(0.3,0.3,0.3));
        plane_mat->setDiffuse(OSG::Color3f(1.0,1.0,1.0));
        plane_mat->addChunk(plane_tex);
        plane_mat->addChunk(plane_tex_env);
    
        OSG::GeometryRefPtr plane_geo = dynamic_cast<OSG::Geometry *>(plane->getCore());
        plane_geo->setMaterial(plane_mat);
        
        // box
        OSG::NodeRefPtr box_trans_node = OSG::makeCoredNode<OSG::Transform>(&globals->box_trans);
        globals->box_trans->editMatrix().setTranslate(0.0, 0.0, 2.0);
        
        OSG::NodeRefPtr box = OSG::makeBox(8.0, 8.0, 0.8, 10, 10 , 10);
        box_trans_node->addChild(box);
    
        OSG::SimpleMaterialRefPtr box_mat = OSG::SimpleMaterial::create();
        box_mat->setAmbient(OSG::Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(OSG::Color3f(0.0,0.0,1.0));
    
        OSG::GeometryRefPtr box_geo = dynamic_cast<OSG::Geometry *>(box->getCore());
        box_geo->setMaterial(box_mat);
    
        // cylinder1
        OSG::NodeRefPtr cylinder1_trans_node = OSG::makeCoredNode<OSG::Transform>(&globals->cylinder1_trans);
        globals->cylinder1_trans->editMatrix().setTranslate(0.0, 0.0, 5.0);
        
        OSG::NodeRefPtr cylinder1 = OSG::makeCylinder(10.0, 0.4, 32, true, true ,true);
        cylinder1_trans_node->addChild(cylinder1);
        
        OSG::SimpleMaterialRefPtr cylinder1_mat = OSG::SimpleMaterial::create();
        cylinder1_mat->setAmbient(OSG::Color3f(0.0,0.0,0.0));
        cylinder1_mat->setDiffuse(OSG::Color3f(1.0,0.0,0.0));
        
        OSG::GeometryRefPtr cylinder1_geo = dynamic_cast<OSG::Geometry *>(cylinder1->getCore());
        cylinder1_geo->setMaterial(cylinder1_mat);
        
        // cylinder2
        OSG::NodeRefPtr cylinder2_trans_node = OSG::makeCoredNode<OSG::Transform>(&globals->cylinder2_trans);
        globals->cylinder2_trans->editMatrix().setTranslate(0.0, 0.0, 8.0);
        
        OSG::NodeRefPtr cylinder2 = OSG::makeCylinder(10.0, 0.4, 32, true, true ,true);
        cylinder2_trans_node->addChild(cylinder2);
        
        OSG::SimpleMaterialRefPtr cylinder2_mat = OSG::SimpleMaterial::create();
        cylinder2_mat->setAmbient(OSG::Color3f(0.0,0.0,0.0));
        cylinder2_mat->setDiffuse(OSG::Color3f(0.0,1.0,0.0));
    
        OSG::GeometryRefPtr cylinder2_geo = dynamic_cast<OSG::Geometry *>(cylinder2->getCore());
        cylinder2_geo->setMaterial(cylinder2_mat);
    
        // scene
        scene->addChild(plane);
        scene->addChild(box_trans_node);
        scene->addChild(cylinder1_trans_node);
        scene->addChild(cylinder2_trans_node);
        
        globals->rootNode->addChild(point1);
        globals->rootNode->addChild(point1_beacon);
        globals->rootNode->addChild(point2_beacon);
    
        globals->gwin->setGlutId(winid);
        globals->gwin->init();
        
        /*
            SHADOWS
            Shadows are implemented as LightEngines (every Light can have one
            to augment it's regular effect).
        */
        
        // create the engines
        OSG::SimpleShadowMapEngineRefPtr ssme1 = OSG::SimpleShadowMapEngine::create();
        OSG::SimpleShadowMapEngineRefPtr ssme2 = OSG::SimpleShadowMapEngine::create();
        
        // add them to the light sources
        globals->point1_core->setLightEngine(ssme1);
        globals->point2_core->setLightEngine(ssme2);
        
        ssme1->setWidth (SM_RESOLUTION);
        ssme1->setHeight(SM_RESOLUTION);
        ssme1->setShadowColor(OSG::Color4f(0.1, 0.1, 0.1, 1.0));
        
        ssme2->setWidth (SM_RESOLUTION);
        ssme2->setHeight(SM_RESOLUTION);
        
        OSG::Vec3f min,max;
        globals->rootNode->updateVolume();
        globals->rootNode->getVolume   ().getBounds( min, max );
    
        OSG::commitChanges();
        
        // create the SimpleSceneManager helper
        globals->mgr = new OSG::SimpleSceneManager;
    
        globals->mgr->setWindow(globals->gwin    );
        globals->mgr->setRoot  (globals->rootNode);
        
        globals->mgr->turnHeadlightOff();
    
        globals->mgr->showAll();
    }

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//do Animation-Calculations here
void Animate()
{
    static OSG::Real64 t0 = OSG::getSystemTime();

    OSG::Real64 t = OSG::getSystemTime() - t0;

    OSG::Real32 rotb = t * 10.0;
    if(rotb > 360.0)
        rotb -= 360.0;

    OSG::Real32 rotc1 = t * 20.0;
    if(rotc1 > 360.0)
        rotc1 -= 360.0;

    OSG::Real32 rotc2 = t * 40.0;
    if(rotc2 > 360.0)
        rotc2 -= 360.0;

    OSG::Quaternion q;
    q.setValueAsAxisDeg(0,0,1, rotb);
    globals->box_trans->editMatrix().setRotate(q);

    q.setValueAsAxisDeg(0,0,1, rotc1);
    globals->cylinder1_trans->editMatrix().setRotate(q);

    q.setValueAsAxisDeg(0,0,1, rotc2);
    globals->cylinder2_trans->editMatrix().setRotate(q);

    globals->mgr->redraw();
}

// redraw the window
void display(void)
{
    globals->mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    globals->mgr->resize( w, h );
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if ( state )
        globals->mgr->mouseButtonRelease( button, x, y );
    else
        globals->mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    globals->mgr->mouseMove( x, y );
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete globals->mgr;
            delete globals;
            
            OSG::osgExit();
            exit(0);
        }
        break;

        case '1':
        {
            globals->point1_core->setOn(true);
            globals->point1_core->setAmbient(0.3,0.3,0.3,1);
            globals->point1_core->setDiffuse(0.8,0.8,0.8,1);

            globals->point2_core->setOn(false);
            break;
        }

        case '2':
        {
            globals->point1_core->setAmbient(0.15,0.15,0.15,1);
            globals->point1_core->setDiffuse(0.4,0.4,0.4,1);
            globals->point1_core->setOn(true);

            globals->point2_core->setAmbient(0.15,0.15,0.15,1);
            globals->point2_core->setDiffuse(0.4,0.4,0.4,1);
            globals->point2_core->setOn(true);
            break;
        }

        case 'x':
        {
            OSG::SceneFileHandler::the()->write(globals->rootNode, "shadow.osb.gz", true);
        }
    }
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Set WindowSize here
    glutInitWindowSize(640,640);
    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
