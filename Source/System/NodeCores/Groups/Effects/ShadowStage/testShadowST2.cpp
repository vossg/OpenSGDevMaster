#include <stdlib.h>

#include <OSGGLUT.h>
#include <OSGConfig.h>

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
#include <OSGTrackball.h>

#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>

#include <OSGSimpleSceneManager.h>

#include <OSGSceneFileHandler.h>

#include <OSGShadowStage.h>

OSG::SimpleSceneManager *mgr;

OSG::GLUTWindowUnrecPtr gwin;
OSG::ShadowStageUnrecPtr svp;

OSG::NodeUnrecPtr rootNode;
OSG::NodeUnrecPtr point1;
OSG::NodeUnrecPtr point2;
OSG::NodeUnrecPtr point3;
OSG::NodeUnrecPtr point4;
OSG::NodeUnrecPtr point5;
OSG::NodeUnrecPtr point6;
OSG::NodeUnrecPtr point7;
OSG::SpotLightUnrecPtr spot1_core;
OSG::SpotLightUnrecPtr spot2_core;
OSG::SpotLightUnrecPtr spot3_core;
OSG::SpotLightUnrecPtr spot4_core;
OSG::SpotLightUnrecPtr spot5_core;
OSG::SpotLightUnrecPtr spot6_core;
OSG::SpotLightUnrecPtr spot7_core;
OSG::DirectionalLightUnrecPtr raumlicht_core;
//PointLightPtr _point1_core;
OSG::DirectionalLightUnrecPtr _point1_core;
OSG::PointLightUnrecPtr _point2_core;
OSG::PointLightUnrecPtr _point3_core;
OSG::PointLightUnrecPtr _point4_core;
OSG::PointLightUnrecPtr _point5_core;
OSG::PointLightUnrecPtr _point6_core;
OSG::PointLightUnrecPtr _point7_core;
OSG::TransformUnrecPtr _box_trans;
OSG::TransformUnrecPtr _cylinder1_trans;
OSG::TransformUnrecPtr _cylinder2_trans;

bool animateScene;
bool useStandardScene;

OSG::UInt32 frameCount;
OSG::Real32 fps = 0.0;
OSG::Real32 startTime2;


//FPS Counter
void startFpsCounter()
{
    startTime2 = OSG::getSystemTime();
}

void showFpsCounter()
{
    frameCount++;
    if(OSG::getSystemTime() - startTime2 >= 1.0)
    {
        printf("aktuelle FPS: %i                              \r", frameCount);
        frameCount = 0;
        startTime2 = OSG::getSystemTime();
    }
}


// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// Initialize GLUT & OpenSG and set up the scene
int doMain(int argc, char **argv)
{
    printf(
        "Load a scene with first param, else a standard scene will be used.\n"
        );
    printf(
        "Press key 'u', 'i', 'o' ,'p', 'j', 'k', 'l' to switch between 1...7 light sources.\n");
    printf("Set the shadow mode with key '1' ... '7'\n");
    printf("Change MapSize with keys 'y'(512), 'x'(1024), 'c'(2048)\n");
    printf("NOTE: Real point lights only supported for ShadowMode 1...5!\n");

    // OSG init
    OSG::osgInit(argc, argv);

    // GLUT init
    int                     winid = setupGLUT(&argc, argv);
    gwin = OSG::GLUTWindow::create();

    useStandardScene = false;

    if(argc <= 1)
    {
        useStandardScene = true;
        animateScene = true;
        //Erstellen der ben�tigten Komponenten--------------------------------------

        rootNode = OSG::makeCoredNode<OSG::Group>();
        OSG::NodeUnrecPtr             scene = OSG::makeCoredNode<OSG::Group>();

        // create lights
        OSG::TransformUnrecPtr        point1_trans;
        point1 = OSG::makeCoredNode<OSG::DirectionalLight>(&_point1_core);
        OSG::NodeUnrecPtr             point1_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point1_trans);
        point1_trans->editMatrix().setTranslate(0.0, 0.0, 100.0);

        _point1_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point1_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point1_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point1_core->setBeacon(point1_beacon);
        _point1_core->setOn(true);
        _point1_core->setShadowIntensity(0.7);
        _point1_core->setDirection(0.4, 0.2, 0.8);

        OSG::TransformUnrecPtr        point2_trans;
        point2 = OSG::makeCoredNode<OSG::PointLight>(&_point2_core);
        OSG::NodeUnrecPtr             point2_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point2_trans);
        point2_trans->editMatrix().setTranslate(20.0, -30.0, 100.0);

        _point2_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point2_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point2_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point2_core->setBeacon(point2_beacon);
        _point2_core->setOn(true);
        _point2_core->setShadowIntensity(0.7);

        OSG::TransformUnrecPtr        point3_trans;
        point3 = OSG::makeCoredNode<OSG::PointLight>(&_point3_core);
        OSG::NodeUnrecPtr             point3_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point3_trans);
        point3_trans->editMatrix().setTranslate(10.0, -15.0, 100.0);

        _point3_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point3_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point3_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point3_core->setBeacon(point3_beacon);
        _point3_core->setOn(true);
        _point3_core->setShadowIntensity(0.7);

        OSG::TransformUnrecPtr        point4_trans;
        point4 = OSG::makeCoredNode<OSG::PointLight>(&_point4_core);
        OSG::NodeUnrecPtr             point4_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point4_trans);
        point4_trans->editMatrix().setTranslate(35.0, -45.0, 100.0);

        _point4_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point4_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point4_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point4_core->setBeacon(point4_beacon);
        _point4_core->setOn(true);
        _point4_core->setShadowIntensity(0.7);

        OSG::TransformUnrecPtr        point5_trans;
        point5 = OSG::makeCoredNode<OSG::PointLight>(&_point5_core);
        OSG::NodeUnrecPtr             point5_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point5_trans);
        point5_trans->editMatrix().setTranslate(40.0, -60.0, 100.0);

        _point5_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point5_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point5_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point5_core->setBeacon(point5_beacon);
        _point5_core->setOn(true);
        _point5_core->setShadowIntensity(0.7);

        OSG::TransformUnrecPtr        point6_trans;
        point6 = OSG::makeCoredNode<OSG::PointLight>(&_point6_core);
        OSG::NodeUnrecPtr             point6_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point6_trans);
        point6_trans->editMatrix().setTranslate(17.0, -55.0, 100.0);

        _point6_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point6_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point6_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point6_core->setBeacon(point6_beacon);
        _point6_core->setOn(true);
        _point6_core->setShadowIntensity(0.7);

        OSG::TransformUnrecPtr        point7_trans;
        point7 = OSG::makeCoredNode<OSG::PointLight>(&_point7_core);
        OSG::NodeUnrecPtr             point7_beacon = OSG::makeCoredNode<OSG::Transform>
            (&point7_trans);
        point7_trans->editMatrix().setTranslate(5.0, -42.0, 100.0);

        _point7_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point7_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point7_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point7_core->setBeacon(point7_beacon);
        _point7_core->setOn(true);
        _point7_core->setShadowIntensity(0.7);

        point1->addChild(point2);

        point2->addChild(point3);

        point3->addChild(point4);

        point4->addChild(point5);

        point5->addChild(point6);

        point6->addChild(point7);

        point7->addChild(scene);

        // create scene

        // bottom
        OSG::NodeUnrecPtr             plane = OSG::makePlane(50.0, 50.0, 128, 128);

        OSG::UChar8              imgdata[] =
        {
            255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0
        };
        OSG::ImageUnrecPtr            plane_img = OSG::Image::create();
        plane_img->set(OSG::Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);

        OSG::TextureObjChunkUnrecPtr     plane_tex_obj = OSG::TextureObjChunk::create();
        OSG::TextureEnvChunkUnrecPtr     plane_tex_env = OSG::TextureEnvChunk::create();
        plane_tex_obj->setImage(plane_img);
        plane_tex_obj->setMinFilter(GL_LINEAR);
        plane_tex_obj->setMagFilter(GL_LINEAR);
        plane_tex_obj->setWrapS(GL_REPEAT);
        plane_tex_obj->setWrapT(GL_REPEAT);
        plane_tex_env->setEnvMode(GL_MODULATE);

        OSG::SimpleMaterialUnrecPtr   plane_mat = OSG::SimpleMaterial::create();
        plane_mat->setAmbient(OSG::Color3f(0.3, 0.3, 0.3));
        plane_mat->setDiffuse(OSG::Color3f(1.0, 1.0, 1.0));
        plane_mat->addChunk(plane_tex_obj);
        plane_mat->addChunk(plane_tex_env);

        OSG::Geometry        *plane_geo = dynamic_cast<OSG::Geometry *>(plane->getCore());
        plane_geo->setMaterial(plane_mat);

        // box
        OSG::NodeUnrecPtr             box_trans_node = OSG::makeCoredNode<OSG::Transform>
            (&_box_trans);
        _box_trans->editMatrix().setTranslate(0.0, 0.0, 2.0);
        OSG::NodeUnrecPtr             box = OSG::makeBox(8.0, 8.0, 0.8, 10, 10, 10);
        box_trans_node->addChild(box);

        OSG::SimpleMaterialUnrecPtr   box_mat = OSG::SimpleMaterial::create();
        box_mat->setAmbient(OSG::Color3f(0.0, 0.0, 0.0));
        box_mat->setDiffuse(OSG::Color3f(0.0, 0.0, 1.0));

        OSG::Geometry     *box_geo = dynamic_cast<OSG::Geometry *>(box->getCore());
        box_geo->setMaterial(box_mat);

        // cylinder1
        OSG::NodeUnrecPtr             cylinder1_trans_node = OSG::makeCoredNode<OSG::Transform>
            (&_cylinder1_trans);

        OSG::Quaternion          q;

        q.setValueAsAxisDeg(1, 1, 0, 145.0);
        _cylinder1_trans->editMatrix().setRotate(q);
        _cylinder1_trans->editMatrix().setTranslate(0.0, 0.0, 5.0);

        OSG::NodeUnrecPtr             cylinder1 = OSG::makeCylinder(30.0, 0.9, 32, true,
                                                          true, true);
        cylinder1_trans_node->addChild(cylinder1);

        OSG::SimpleMaterialUnrecPtr   cylinder1_mat = OSG::SimpleMaterial::create();
        cylinder1_mat->setAmbient(OSG::Color3f(0.0, 0.0, 0.0));
        cylinder1_mat->setDiffuse(OSG::Color3f(1.0, 0.0, 0.0));

        OSG::Geometry     *cylinder1_geo = dynamic_cast<OSG::Geometry *>(
            cylinder1->getCore());
        cylinder1_geo->setMaterial(cylinder1_mat);

        // cylinder2
        OSG::NodeUnrecPtr             cylinder2_trans_node = OSG::makeCoredNode<OSG::Transform>
            (&_cylinder2_trans);
        _cylinder2_trans->editMatrix().setTranslate(10.0, 0.0, 10.0);
        OSG::NodeUnrecPtr             cylinder2 = OSG::makeBox(4.0, 4.0, 1.0, 4, 4, 4);
        cylinder2_trans_node->addChild(cylinder2);

        OSG::SimpleMaterialUnrecPtr   cylinder2_mat = OSG::SimpleMaterial::create();
        cylinder2_mat->setAmbient(OSG::Color3f(0.0, 0.0, 0.0));
        cylinder2_mat->setDiffuse(OSG::Color3f(0.0, 1.0, 0.0));

        OSG::Geometry       *cylinder2_geo = dynamic_cast<OSG::Geometry *>(
            cylinder2->getCore());
        cylinder2_geo->setMaterial(cylinder2_mat);

        // scene
        scene->addChild(plane);
        scene->addChild(box_trans_node);
        scene->addChild(cylinder1_trans_node);
        scene->addChild(cylinder2_trans_node);


        rootNode->addChild(point1_beacon);
        rootNode->addChild(point2_beacon);
        rootNode->addChild(point3_beacon);
        rootNode->addChild(point4_beacon);
        rootNode->addChild(point5_beacon);
        rootNode->addChild(point6_beacon);
        rootNode->addChild(point7_beacon);
        rootNode->addChild(point1);

        //one active light at startup
#if 0
        _point2_core->setOn(false);
        _point3_core->setOn(false);
        _point4_core->setOn(false);
        _point5_core->setOn(false);
        _point6_core->setOn(false);
        _point7_core->setOn(false);
 #endif

        _point1_core->setOn(true);
        _point1_core->setAmbient(0.3, 0.3, 0.3, 1);
        _point1_core->setDiffuse(0.8, 0.8, 0.8, 1);

    }
    else
    {
        animateScene = false;
        rootNode = OSG::SceneFileHandler::the()->read(argv[1]);
        if(rootNode == NULL)
        {
            fprintf(stderr, "Couldn't load '%s'!\n", argv[1]);
            exit(1);
        }
    }


    svp = OSG::ShadowStage::create();
    OSG::GradientBackgroundUnrecPtr   gbg = OSG::GradientBackground::create();
    OSG::SolidBackgroundUnrecPtr      sbg = OSG::SolidBackground::create();

    gbg->addLine(OSG::Color3f(0.7, 0.7, 0.8), 0);
    gbg->addLine(OSG::Color3f(0.0, 0.1, 0.3), 1);

    rootNode->setCore(svp);

    // Shadow viewport
#ifdef SHADOW_CHECK
    svp->setBackground(gbg);
    svp->setRoot(rootNode);
    svp->setSize(0, 0, 1, 1);
#endif

    //you can set Offset here
    //svp->setOffFactor(4.0);
    //svp->setOffBias(8.0);
    svp->setMapSize(512);
    //if globalShadowIntensity > 0.0, it is used for all lights
    //svp->setGlobalShadowIntensity(0.8);
    //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    //ShadowSmoothness also used to define the light size for PCSS Soft Shadows
    svp->setShadowSmoothness(0.5);

    //svp->setOffBias(8.0);
    // you can add the light sources here
    if(argv[1] == NULL)
    {
        svp->setAutoSearchForLights(false);
        svp->editMFLightNodes()->push_back(point1);
        svp->editMFLightNodes()->push_back(point2);
        svp->editMFLightNodes()->push_back(point3);
        svp->editMFLightNodes()->push_back(point4);
        svp->editMFLightNodes()->push_back(point5);
        svp->editMFLightNodes()->push_back(point6);
        svp->editMFLightNodes()->push_back(point7);
        svp->setOffFactor(4.0);
        svp->setOffBias(8.0);
    }
    else
    {
        //if set, all lights in the scene will be used
        svp->setAutoSearchForLights(true);
    }


    gwin->setGlutId(winid);
#ifdef SHADOW_CHECK
    gwin->addPort(svp);
#endif
    gwin->init();

    OSG::Vec3f                   min, max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds(min, max);

    // create the SimpleSceneManager helper
    mgr = new OSG::SimpleSceneManager;

    mgr->setWindow(gwin);
    mgr->setRoot(rootNode);

#ifdef SHADOW_CHECK
    svp->setCamera(mgr->getCamera());
#endif

    startFpsCounter();

//    dynamic_cast<RenderAction *>(mgr->getAction())->setLocalLights(true);
    mgr->turnHeadlightOff();

    mgr->showAll();

    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

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
    //showFpsCounter();

    if(animateScene)
    {
        static OSG::Real64   t0 = OSG::getSystemTime();

        OSG::Real64          t = OSG::getSystemTime() - t0;

        OSG::Real32          rotb = t * 10.0;
        if(rotb > 360.0)
            rotb -= 360.0;

        OSG::Real32          rotc1 = t * 20.0;
        if(rotc1 > 360.0)
            rotc1 -= 360.0;

        OSG::Real32          rotc2 = t * 40.0;
        if(rotc2 > 360.0)
            rotc2 -= 360.0;

        OSG::Quaternion      q;
        /*beginEditCP(_box_trans);
           q.setValueAsAxisDeg(0,0,1, rotb);
           _box_trans->getMatrix().setRotate(q);
           endEditCP(_box_trans);*/

        q.setValueAsAxisDeg(1, 0, 0, rotc1);
        _cylinder1_trans->editMatrix().setRotate(q);

        _cylinder2_trans->editMatrix().setTranslate(10.0, 0.0, 10.0 +
                                                   (9.0 * sin(rotb / 10.0)));

        /*beginEditCP(_cylinder2_trans);
           q.setValueAsAxisDeg(0,0,1, rotc2);
           _cylinder2_trans->getMatrix().setRotate(q);
           endEditCP(_cylinder2_trans);*/
    }


    mgr->redraw();
}

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
    if(state)
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
                gwin             = NULL;
                svp              = NULL;

                rootNode         = NULL;
                point1           = NULL;
                point2           = NULL;
                point3           = NULL;
                point4           = NULL;
                point5           = NULL;
                point6           = NULL;
                point7           = NULL;
                spot1_core       = NULL;
                spot2_core       = NULL;
                spot3_core       = NULL;
                spot4_core       = NULL;
                spot5_core       = NULL;
                spot6_core       = NULL;
                spot7_core       = NULL;
                raumlicht_core   = NULL;

                _point1_core     = NULL;
                _point2_core     = NULL;
                _point3_core     = NULL;
                _point4_core     = NULL;
                _point5_core     = NULL;
                _point6_core     = NULL;
                _point7_core     = NULL;
                _box_trans       = NULL;
                _cylinder1_trans = NULL;
                _cylinder2_trans = NULL;
                
                delete mgr;

                OSG::osgExit();
                exit(0);
            }
            break;

        case 'u':
            {
                if(useStandardScene)
                {
                    _point1_core->setOn(true);
                    _point1_core->setAmbient(0.3, 0.3, 0.3, 1);
                    _point1_core->setDiffuse(0.8, 0.8, 0.8, 1);

                    _point2_core->setOn(false);

                    _point3_core->setOn(false);

                    _point4_core->setOn(false);

                    _point5_core->setOn(false);

                    _point6_core->setOn(false);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'i':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.15, 0.15, 0.15, 1);
                    _point1_core->setDiffuse(0.4, 0.4, 0.4, 1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.15, 0.15, 0.15, 1);
                    _point2_core->setDiffuse(0.4, 0.4, 0.4, 1);
                    _point2_core->setOn(true);

                    _point3_core->setOn(false);

                    _point4_core->setOn(false);

                    _point5_core->setOn(false);

                    _point6_core->setOn(false);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'o':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point2_core->setOn(true);

                    _point3_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point3_core->setOn(true);

                    _point4_core->setOn(false);

                    _point5_core->setOn(false);

                    _point6_core->setOn(false);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'p':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point2_core->setOn(true);

                    _point3_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point3_core->setOn(true);

                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);

                    _point5_core->setOn(false);

                    _point6_core->setOn(false);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'j':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point2_core->setOn(true);

                    _point3_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point3_core->setOn(true);

                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);

                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);

                    _point6_core->setOn(false);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'k':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point2_core->setOn(true);

                    _point3_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point3_core->setOn(true);

                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);

                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);

                    _point6_core->setOn(true);
                    _point6_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point6_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);

                    _point7_core->setOn(false);
                }
                break;
            }

        case 'l':
            {
                if(useStandardScene)
                {
                    _point1_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point1_core->setOn(true);

                    _point2_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point2_core->setOn(true);

                    _point3_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point3_core->setOn(true);

                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);

                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);

                    _point6_core->setOn(true);
                    _point6_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point6_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);

                    _point7_core->setOn(true);
                    _point7_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point7_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                }
                break;
            }

        case '1':
            {
                svp->setShadowMode(OSG::ShadowStage::NO_SHADOW);
                SLOG << "NO_SHADOW" << std::endl;
                break;
            }

        case '2':
            {
                svp->setShadowMode(OSG::ShadowStage::STD_SHADOW_MAP);
                SLOG << "STD_SHADOW_MAP" << std::endl;
                break;
            }

        case '3':
            {
                svp->setShadowMode(OSG::ShadowStage::PERSPECTIVE_SHADOW_MAP);
                SLOG << "PERSPECTIVE_SHADOW_MAP" << std::endl;
                break;
            }

        case '4':
            {
                svp->setShadowMode(OSG::ShadowStage::DITHER_SHADOW_MAP);
                SLOG << "DITHER_SHADOW_MAP" << std::endl;
                break;
            }

        case '5':
            {
                svp->setShadowMode(OSG::ShadowStage::PCF_SHADOW_MAP);
                //svp->setShadowSmoothness(0.5);
                SLOG << "PCF_SHADOW_MAP" << std::endl;
                break;
            }

        case '6':
            {
                svp->setShadowMode(OSG::ShadowStage::PCSS_SHADOW_MAP);
                svp->setShadowSmoothness(0.2);
                SLOG << "PCSS_SHADOW_MAP" << std::endl;
                break;
            }

        case '7':
            {
                svp->setShadowMode(OSG::ShadowStage::VARIANCE_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                SLOG << "VARIANCE_SHADOW_MAP" << std::endl;
                break;
            }

        case 'w':
            {
                OSG::Real32  t = svp->getOffBias();

                svp->setOffBias(++t);
                SLOG << "Polygon-OffsetBias is: " << ++t << OSG::endLog;
                break;
            }

        case 's':
            {
                OSG::Real32  t = svp->getOffBias();

                svp->setOffBias(--t);
                SLOG << "Polygon-OffsetBias is: " << --t << OSG::endLog;
                break;
            }

        case 'e':
            {
                OSG::Real32  u = svp->getOffFactor();

                svp->setOffFactor(++u);
                SLOG << "Polygon-OffsetFactor is: " << u << endLog;
                break;
            }

        case 'd':
            {
                OSG::Real32  u = svp->getOffFactor();

                svp->setOffFactor(--u);
                SLOG << "Polygon-OffsetFactor is: " << u << endLog;
                break;
            }

        case '+':
            {
                OSG::Real32  r = svp->getShadowSmoothness();

                svp->setShadowSmoothness(r + 0.1);
                SLOG << "ShadowSmoothness is: " << (r + 0.1) << endLog;
                break;
            }

        case '-':
            {
                OSG::Real32  r = svp->getShadowSmoothness();

                svp->setShadowSmoothness(r - 0.1);
                SLOG << "ShadowSmoothness is: " << (r + 0.1) << endLog;
                break;
            }

        case 'y':
            {
                svp->setMapSize(512);
                SLOG << "ShadowMapSize is: 512" << endLog;
                break;
            }

        case 'x':
            {
                svp->setMapSize(1024);
                SLOG << "ShadowMapSize is: 1024" << endLog;
                break;
            }

        case 'c':
            {
                svp->setMapSize(2048);
                SLOG << "ShadowMapSize is: 2048" << endLog;
                break;
            }

        case 'a':
            {
                if(useStandardScene)
                {
                    animateScene = !animateScene;
                }
                break;
            }

    }
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int w = 640, h = 512;

    if(*argc == 4)
    {
        w = atoi(argv[2]);
        h = atoi(argv[3]);
    }
    
    //Set WindowSize here
    glutInitWindowSize(w, h);
    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
