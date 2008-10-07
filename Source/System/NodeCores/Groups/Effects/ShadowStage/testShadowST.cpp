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
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGTrackball.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGNavigator.h>
#include "OSGShadowStage.h"
#include "OSGMatrixCamera.h"

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GLUTWindowUnrecPtr gwin;
ShadowStageUnrecPtr svp;


NodeUnrecPtr rootNode;
//DirectionalLightPtr _dir1_core;
PointLightUnrecPtr _dir1_core;

//SpotLightPtr _dir2_core;
PointLightUnrecPtr _dir2_core;
TransformUnrecPtr dir2_trans;

TransformUnrecPtr _obj1_trans;
TransformUnrecPtr _dino1_trans, _dino2_trans, _dino3_trans, _dino4_trans;
TransformUnrecPtr _tree1_trans, _tree2_trans, _tree3_trans, _tree4_trans,
    _tree5_trans, _tree6_trans, _tree7_trans, _tree8_trans, _tree9_trans;

MatrixCameraUnrecPtr camera;
PerspectiveCameraUnrecPtr Pcamera;
NodeUnrecPtr cam_beacon;
TransformUnrecPtr cam_trans;
Vec3f camPos;
Vec3f camDir;

Navigator _navigator;
Int16 _lastx;
Int16 _lasty;
UInt16 _mousebuttons;

UInt32 frameCount;
Real32 fps = 0.0;
Real32 startTime2;

bool bAnim = false;

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
        printf("aktuelle FPS: %i\r", frameCount);
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
        "Press key '8' or '9' to switch between light sources. Press key '0' to use both lights\n");
    printf("Set the shadow mode with key '1' ... '7'\n");
    printf("Change MapSize with keys 'y' = 512, 'x' = 1024, 'c' = 2048\n");
    printf("NOTE: Real point lights only supported for ShadowMode 1...5!\n");
    // OSG init
    osgInit(argc, argv);

    // GLUT init
    int                     winid = setupGLUT(&argc, argv);
    gwin = GLUTWindow::create();

    //Erstellen der ben�tigten Komponenten--------------------------------------

    rootNode = makeCoredNode<Group>();
    NodeUnrecPtr                 scene = makeCoredNode<Group>();

    // create lights
    /*//Directional Light 1
       TransformPtr dir1_trans;
       NodePtr dir1 = makeCoredNode<DirectionalLight>(&_dir1_core);
       NodePtr dir1_beacon = makeCoredNode<Transform>(&dir1_trans);
       dir1_trans->editMatrix().setTranslate(0.0, 0.0, 0.0);
       
       _dir1_core->setDirection(0.5,0.5,0.8);
       _dir1_core->setAmbient(0.15,0.15,0.15,1);
       _dir1_core->setDiffuse(0.5,0.5,0.5,1);
       _dir1_core->setSpecular(0.0,0.0,0.0,1);
       _dir1_core->setBeacon(dir1_beacon);
       _dir1_core->setShadowIntensity(0.7);
       _dir1_core->setOn(true);
       */

    //Point Light 1
    TransformUnrecPtr            dir1_trans;
    NodeUnrecPtr                 dir1 = makeCoredNode<PointLight>(&_dir1_core);
    NodeUnrecPtr                 dir1_beacon = makeCoredNode<Transform>
        (&dir1_trans);
    dir1_trans->editMatrix().setTranslate(350.0, 300.0, 300.0);

    _dir1_core->setAmbient(0.15, 0.15, 0.15, 1);
    _dir1_core->setDiffuse(0.5, 0.5, 0.5, 1);
    _dir1_core->setSpecular(0.0, 0.0, 0.0, 1);
    _dir1_core->setBeacon(dir1_beacon);
    _dir1_core->setOn(true);
    _dir1_core->setShadowIntensity(0.8);

    /*//Spot Light 2
       //TransformPtr dir2_trans;
       NodePtr dir2 = makeCoredNode<SpotLight>(&_dir2_core);
       NodePtr dir2_beacon = makeCoredNode<Transform>(&dir2_trans);
       //dir2_trans->editMatrix().setTranslate(75.0, 0.0, 25.0);
       dir2_trans->editMatrix().setTranslate(250.0, -250.0, 300.0);
       
       _dir2_core->setAmbient(0.15,0.15,0.15,1);
       _dir2_core->setDiffuse(0.5,0.5,0.5,1);
       _dir2_core->setSpecular(0.0,0.0,0.0,1);
       _dir2_core->setSpotCutOffDeg(40.0);
       _dir2_core->setSpotDirection(-0.85,0.85,-1.0);
       _dir2_core->setBeacon(dir2_beacon);
       _dir2_core->setOn(true);
       */

    //Point Light 2
    //TransformPtr dir2_trans;
    NodeUnrecPtr                 dir2 = makeCoredNode<PointLight>(&_dir2_core);
    NodeUnrecPtr                 dir2_beacon = makeCoredNode<Transform>
        (&dir2_trans);
    dir2_trans->editMatrix().setTranslate(40.0, 0.0, 40.0);

    _dir2_core->setAmbient(0.15, 0.15, 0.15, 1);
    _dir2_core->setDiffuse(0.5, 0.5, 0.5, 1);
    _dir2_core->setSpecular(0.0, 0.0, 0.0, 1);
    _dir2_core->setBeacon(dir2_beacon);
    _dir2_core->setOn(true);
    _dir2_core->setShadowIntensity(0.7);


    dir1->addChild(dir2);

    dir2->addChild(scene);

    //Eigene Kamera erstellen
    Pcamera = PerspectiveCamera::create();
    cam_beacon = makeCoredNode<Transform>(&cam_trans);
    cam_trans->editMatrix().setTranslate(0.0, 0.0, 25.0);

    Pcamera->setBeacon(cam_beacon);
    Pcamera->setFov(osgDegree2Rad(60));
    Pcamera->setNear(1.0);
    Pcamera->setFar(1000);


    // create scene

    // bottom
    NodeUnrecPtr                 plane = makePlane(300.0, 300.0, 256, 256);

    ImageUnrecPtr                plane_img = Image::create();
    plane_img->read("gras.jpg");

    TextureChunkUnrecPtr         plane_tex = TextureChunk::create();
    plane_tex->setImage(plane_img);
    plane_tex->setMinFilter(GL_LINEAR);
    plane_tex->setMagFilter(GL_LINEAR);
    plane_tex->setWrapS(GL_REPEAT);
    plane_tex->setWrapT(GL_REPEAT);
    plane_tex->setEnvMode(GL_MODULATE);

    SimpleMaterialUnrecPtr       plane_mat = SimpleMaterial::create();
    plane_mat->setAmbient(Color3f(0.3, 0.3, 0.3));
    plane_mat->setDiffuse(Color3f(1.0, 1.0, 1.0));
    plane_mat->addChunk(plane_tex);

    Geometry *plane_geo = dynamic_cast<Geometry *>(plane->getCore());
    plane_geo->setMaterial(plane_mat);

    //load Tree Objects

    NodeUnrecPtr                 tree1_trans_node = makeCoredNode<Transform>
        (&_tree1_trans);
    NodeUnrecPtr                 tree2_trans_node = makeCoredNode<Transform>
        (&_tree2_trans);
    NodeUnrecPtr                 tree3_trans_node = makeCoredNode<Transform>
        (&_tree3_trans);
    NodeUnrecPtr                 tree4_trans_node = makeCoredNode<Transform>
        (&_tree4_trans);
    NodeUnrecPtr                 tree5_trans_node = makeCoredNode<Transform>
        (&_tree5_trans);
    NodeUnrecPtr                 tree6_trans_node = makeCoredNode<Transform>
        (&_tree6_trans);
    NodeUnrecPtr                 tree7_trans_node = makeCoredNode<Transform>
        (&_tree7_trans);
    NodeUnrecPtr                 tree8_trans_node = makeCoredNode<Transform>
        (&_tree8_trans);
    NodeUnrecPtr                 tree9_trans_node = makeCoredNode<Transform>
        (&_tree9_trans);

    _tree1_trans->editMatrix().setTranslate(-80.0, -80.0, 0.0);
    _tree1_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree2_trans->editMatrix().setTranslate(0.0, -80.0, 0.0);
    _tree2_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree3_trans->editMatrix().setTranslate(80.0, -80.0, 0.0);
    _tree3_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree4_trans->editMatrix().setTranslate(-80.0, 0.0, 0.0);
    _tree4_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree5_trans->editMatrix().setTranslate(0.0, 0.0, 0.0);
    _tree5_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree6_trans->editMatrix().setTranslate(80.0, 0.0, 0.0);
    _tree6_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree7_trans->editMatrix().setTranslate(-80.0, 80.0, 0.0);
    _tree7_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree8_trans->editMatrix().setTranslate(0.0, 80.0, 0.0);
    _tree8_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    _tree9_trans->editMatrix().setTranslate(80.0, 80.0, 0.0);
    _tree9_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));

    NodeUnrecPtr tree1 = SceneFileHandler::the()->read("tree1.3ds");

//    NodeUnrecPtr tree1 = makeSphere(2, 2.0);

    tree1_trans_node->addChild(tree1);

    tree2_trans_node->addChild(cloneTree(tree1));


    tree3_trans_node->addChild(cloneTree(tree1));

    tree4_trans_node->addChild(cloneTree(tree1));

    tree5_trans_node->addChild(cloneTree(tree1));

    tree6_trans_node->addChild(cloneTree(tree1));

    tree7_trans_node->addChild(cloneTree(tree1));

    tree8_trans_node->addChild(cloneTree(tree1));

    tree9_trans_node->addChild(cloneTree(tree1));

    NodeUnrecPtr                 trees = makeCoredNode<Group>();

    trees->addChild(tree1_trans_node);
    trees->addChild(tree2_trans_node);
    trees->addChild(tree3_trans_node);
    trees->addChild(tree4_trans_node);
    trees->addChild(tree5_trans_node);
    trees->addChild(tree6_trans_node);
    trees->addChild(tree7_trans_node);
    trees->addChild(tree8_trans_node);
    trees->addChild(tree9_trans_node);

    /*//load Airplane Object
       NodePtr obj1_trans_node = makeCoredNode<Transform>(&_obj1_trans);
       
       _obj1_trans->editMatrix().setTranslate(0.0, 0.0, 10.0);
       _obj1_trans->editMatrix().setScale(Vec3f(0.15,0.15,0.15));
       
       NodePtr object1 = SceneFileHandler::the().read("triplane.3ds");
       
       obj1_trans_node->addChild(object1);
       */

    //Load a Quad as Pointlight
    GeometryUnrecPtr             boxGeo = makeBoxGeo(15, 15, 15, 1, 1, 1);
    NodeUnrecPtr                 boxNode = Node::create();
    boxNode->setCore(boxGeo);

    SimpleMaterialUnrecPtr       box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.95, 1.0, 0.2));
    box_mat->setDiffuse(Color3f(0.95, 1.0, 0.2));

    boxGeo->setMaterial(box_mat);

    NodeUnrecPtr                 obj1_trans_node = makeCoredNode<Transform>
        (&_obj1_trans);

    obj1_trans_node->addChild(boxNode);

    //load Dino Objects

    NodeUnrecPtr                 dino1_trans_node = makeCoredNode<Transform>
        (&_dino1_trans);
    NodeUnrecPtr                 dino2_trans_node = makeCoredNode<Transform>
        (&_dino2_trans);
    NodeUnrecPtr                 dino3_trans_node = makeCoredNode<Transform>
        (&_dino3_trans);
    NodeUnrecPtr                 dino4_trans_node = makeCoredNode<Transform>
        (&_dino4_trans);

    _dino1_trans->editMatrix().setTranslate(-20.0, -20.0, 10.0);
    _dino1_trans->editMatrix().setScale(Vec3f(5.0, 5.0, 5.0));

    _dino2_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino2_trans->editMatrix().setScale(Vec3f(3.0, 3.0, 3.0));

    _dino3_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino3_trans->editMatrix().setScale(Vec3f(3.0, 3.0, 3.0));

    _dino4_trans->editMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino4_trans->editMatrix().setScale(Vec3f(3.0, 3.0, 3.0));

    NodeUnrecPtr dino1 = SceneFileHandler::the()->read("dinopet.3ds");

//    NodeUnrecPtr dino1 = makeBox(2., 2., 2., 4, 4, 4);

    dino1_trans_node->addChild(dino1);

    dino2_trans_node->addChild(cloneTree(dino1));

    dino3_trans_node->addChild(cloneTree(dino1));

    dino4_trans_node->addChild(cloneTree(dino1));

    NodeUnrecPtr                 dinos = makeCoredNode<Group>();

    dinos->addChild(dino1_trans_node);
    dinos->addChild(dino2_trans_node);
    dinos->addChild(dino3_trans_node);
    dinos->addChild(dino4_trans_node);

    //load Stone Objects

    TransformUnrecPtr            _stone_trans1, _stone_trans2, _stone_trans3,
                            _stone_trans4, _stone_trans5, _stone_trans6,
                            _stone_trans7, _stone_trans8,
                            _stone_trans9;
    NodeUnrecPtr                 stone_trans_node1 = makeCoredNode<Transform>
        (&_stone_trans1);
    NodeUnrecPtr                 stone_trans_node2 = makeCoredNode<Transform>
        (&_stone_trans2);
    NodeUnrecPtr                 stone_trans_node3 = makeCoredNode<Transform>
        (&_stone_trans3);
    NodeUnrecPtr                 stone_trans_node4 = makeCoredNode<Transform>
        (&_stone_trans4);
    NodeUnrecPtr                 stone_trans_node5 = makeCoredNode<Transform>
        (&_stone_trans5);
    NodeUnrecPtr                 stone_trans_node6 = makeCoredNode<Transform>
        (&_stone_trans6);
    NodeUnrecPtr                 stone_trans_node7 = makeCoredNode<Transform>
        (&_stone_trans7);
    NodeUnrecPtr                 stone_trans_node8 = makeCoredNode<Transform>
        (&_stone_trans8);
    NodeUnrecPtr                 stone_trans_node9 = makeCoredNode<Transform>
        (&_stone_trans9);

    _stone_trans1->editMatrix().setTranslate(-70, -70, 0);

    _stone_trans2->editMatrix().setTranslate(10, -70, 0);

    _stone_trans3->editMatrix().setTranslate(90, -70, 0);

    _stone_trans4->editMatrix().setTranslate(-70, 10, 0);

    _stone_trans5->editMatrix().setTranslate(10, 10, 0);

    _stone_trans6->editMatrix().setTranslate(90, 10, 0);

    _stone_trans7->editMatrix().setTranslate(-70, 90, 0);

    _stone_trans8->editMatrix().setTranslate(10, 90, 0);

    _stone_trans9->editMatrix().setTranslate(90, 90, 0);

    NodeUnrecPtr                 stone1 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone2 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone3 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone4 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone5 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone6 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone7 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone8 = makeSphere(1, 7.0);
    NodeUnrecPtr                 stone9 = makeSphere(1, 7.0);

    ImageUnrecPtr                plane_img2 = Image::create();
    plane_img2->read("stone.jpg");

    TextureChunkUnrecPtr         plane_tex2 = TextureChunk::create();
    plane_tex2->setImage(plane_img2);
    plane_tex2->setMinFilter(GL_LINEAR);
    plane_tex2->setMagFilter(GL_LINEAR);
    plane_tex2->setWrapS(GL_REPEAT);
    plane_tex2->setWrapT(GL_REPEAT);
    plane_tex2->setEnvMode(GL_MODULATE);

    SimpleMaterialUnrecPtr       plane_mat2 = SimpleMaterial::create();
    plane_mat2->setAmbient(Color3f(0.3, 0.3, 0.3));
    plane_mat2->setDiffuse(Color3f(1.0, 1.0, 1.0));
    plane_mat2->addChunk(plane_tex2);

    Geometry *plane_geo3 = dynamic_cast<Geometry *>(stone1->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone2->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone3->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone4->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone5->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone6->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone7->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone8->getCore());
    plane_geo3->setMaterial(plane_mat2);

    plane_geo3 = dynamic_cast<Geometry *>(stone9->getCore());
    plane_geo3->setMaterial(plane_mat2);


    stone_trans_node1->addChild(stone1);

    stone_trans_node2->addChild(stone2);

    stone_trans_node3->addChild(stone3);

    stone_trans_node4->addChild(stone4);

    stone_trans_node5->addChild(stone5);

    stone_trans_node6->addChild(stone6);

    stone_trans_node7->addChild(stone7);

    stone_trans_node8->addChild(stone8);

    stone_trans_node9->addChild(stone9);

    NodeUnrecPtr                 stones = makeCoredNode<Group>();

    stones->addChild(stone_trans_node1);
    stones->addChild(stone_trans_node2);
    stones->addChild(stone_trans_node3);
    stones->addChild(stone_trans_node4);
    stones->addChild(stone_trans_node5);
    stones->addChild(stone_trans_node6);
    stones->addChild(stone_trans_node7);
    stones->addChild(stone_trans_node8);
    stones->addChild(stone_trans_node9);


    scene->addChild(plane);
    scene->addChild(obj1_trans_node);
    scene->addChild(trees);
    scene->addChild(stones);
    scene->addChild(dinos);

    svp = ShadowStage::create();
    GradientBackgroundUnrecPtr   gbg = GradientBackground::create();
    SolidBackgroundUnrecPtr      sbg = SolidBackground::create();

    gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
    gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);

    rootNode->setCore(svp);

    rootNode->addChild(dir1);
    rootNode->addChild(dir1_beacon);
    rootNode->addChild(dir2_beacon);
    rootNode->addChild(cam_beacon);


    // Shadow viewport
#ifdef SHADOW_CHECK
    svp->setBackground(gbg);
    svp->setRoot(rootNode);
    svp->setSize(0, 0, 1, 1);
#endif
    //svp->setOffFactor(4.0);
    //svp->setOffBias(8.0);
    //used to set global shadow intensity, ignores shadow intensity from light sources if != 0.0
    //svp->setGlobalShadowIntensity(0.8);
    svp->setMapSize(1024);
    //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    //ShadowSmoothness also used to define the light size for PCSS_SHADOW_MAP
    svp->setShadowSmoothness(0.5);
    // add light sources here
    svp->editMFLightNodes  ()->push_back(dir1);
    svp->editMFLightNodes  ()->push_back(dir2);
    svp->editMFExcludeNodes()->push_back(obj1_trans_node);
    //svp->setAutoSearchForLights(true);

    //one active light at startup
    _dir2_core->setOn(true);
    _dir2_core->setAmbient(0.3, 0.3, 0.3, 1);
    _dir2_core->setDiffuse(0.8, 0.8, 0.8, 1);

    _dir1_core->setOn(false);
    //_dir1_core->setAmbient(0.3,0.3,0.3,1);
    //_dir1_core->setDiffuse(0.8,0.8,0.8,1);

    gwin->setGlutId(winid);
#ifdef SHADOW_CHECK
    gwin->addPort(svp);
#endif

    gwin->init();

    Vec3f                   min, max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds(min, max);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow(gwin);
    mgr->setCamera(Pcamera);
    mgr->setRoot(rootNode);

    _navigator.setMode(Navigator::TRACKBALL);

#ifdef SHADOW_CHECK
    _navigator.setViewport(svp);
#endif
    _navigator.setCameraTransformation(cam_beacon);


    Vec3f                   up(0,1,0);
    Pnt3f                   at(0,0,0);
    Pnt3f                   from(0.0,-100.1,20.0);

    _navigator.set(from, at, up);

    _navigator.setMotionFactor(0.5f);


#ifdef SHADOW_CHECK
    svp->setCamera(Pcamera);
#endif

    //activate Framecounter
    startFpsCounter();

//    dynamic_cast<RenderAction *>(mgr->getAction())->setLocalLights(true);
    mgr->turnHeadlightOff();

    mgr->showAll();

    _navigator.setViewport(gwin->getPort(0));

    return 0;
}

int main(int argc, char **argv)
{
    doMain(argc, argv);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

void Animate()
{
    //Show FPS
    //showFpsCounter();

    if(bAnim == true)
    {
        static Real64   t0 = OSG::getSystemTime();
        
        Real64          t = OSG::getSystemTime() - t0;
        
        Real32          rot0 = t * 0.25;
        if(rot0 > 360.0)
            rot0 -= 360.0;
        
        Real32          rota = t * 0.5;
        if(rota > 360.0)
            rota -= 360.0;
        
        Real32          rotb = t * 1.0;
        if(rotb > 360.0)
            rotb -= 360.0;
        
        Real32          rotc = t * 1.5;
        if(rotc > 360.0)
            rotc -= 360.0;
        
        Real32          rotd = t * 2.0;
        if(rotd > 360.0)
            rotd -= 360.0;
        
        //    dir2_trans->editMatrix().setTranslate(-100.0*sin(rota),-100.0*cos(rota), 250.0);
        
        //animate Trees
        Quaternion      q;
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rota));
        _tree1_trans->editMatrix().setRotate(q);
        _tree1_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree2_trans->editMatrix().setRotate(q);
        _tree2_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree3_trans->editMatrix().setRotate(q);
        _tree3_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree4_trans->editMatrix().setRotate(q);
        _tree4_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree5_trans->editMatrix().setRotate(q);
        _tree5_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree6_trans->editMatrix().setRotate(q);
        _tree6_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotd));
        _tree7_trans->editMatrix().setRotate(q);
        _tree7_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
        _tree8_trans->editMatrix().setRotate(q);
        _tree8_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
        _tree9_trans->editMatrix().setRotate(q);
        _tree9_trans->editMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
        
        q.setIdentity();
        
        {
            Matrix  m;
            m.setIdentity();
            Vec3f   scale(0.15,0.15,0.15);
            Vec3f   trans(-40.0 * sin(rotb),-40.0 * cos(rotb),
                          50.0 + 25.0 * sin(rotd));
            q.setValueAsAxisRad(0, 0, 1, -rotb);
            m.setTransform(trans, q, scale);
            _obj1_trans->setMatrix(m);
        }
        
        
        {
            dir2_trans->editMatrix().setTranslate(-40.0 * sin(rotb), -40.0 *
                                                  cos(rotb),
                                                  50.0 + 25.0 * sin(rotd));
        }
        
        //animate Dinos
        
        {
            Matrix  m;
            m.setIdentity();
            Vec3f   scale(5.0,5.0,5.0);
            Real32  ztrans1 = sin(2.0 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            Vec3f   trans(-96.0 * cos(rot0),-96.0 * sin(rot0),
                          10.0 + 8.0 * ztrans1);
            m.setScale(Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170);
            m.setTransform(trans, q, scale);
            _dino1_trans->setMatrix(m);
        }
        
        {
            Matrix  m;
            m.setIdentity();
            Vec3f   scale(3.0,3.0,3.0);
            Real32  ztrans1 = sin(2.5 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            Vec3f   trans(-96.0 * cos((rot0 - 0.5)),-96.0 * sin((rot0 - 0.5)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 169.9);
            m.setTransform(trans, q, scale);
            _dino2_trans->setMatrix(m);
        }
        
        {
            Matrix  m;
            m.setIdentity();
            Vec3f   scale(3.0,3.0,3.0);
            Real32  ztrans1 = sin(3.0 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            Vec3f   trans(-96.0 * cos((rot0 - 0.8)),-96.0 * sin((rot0 - 0.8)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
            m.setTransform(trans, q, scale);
            _dino3_trans->setMatrix(m);
        }
        
        {
            Matrix  m;
            m.setIdentity();
            Vec3f   scale(3.0,3.0,3.0);
            Real32  ztrans1 = sin(2.75 * rotd);
            if(ztrans1 < 0)
                ztrans1 *= -1.0;
            Vec3f   trans(-96.0 * cos((rot0 - 1.2)),-96.0 * sin((rot0 - 1.2)),
                          6.0 + 8.0 * ztrans1);
            m.setScale(Vec3f(5.0, 5.0, 5.0));
            q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
            m.setTransform(trans, q, scale);
            _dino4_trans->setMatrix(m);
        }
    }

    _navigator.idle(_mousebuttons, _lastx, _lasty);
    mgr->redraw();
}

// redraw the window
void display(void)
{
    _navigator.updateCameraTransformation();
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
    {
        mgr->mouseButtonRelease(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonRelease(Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonRelease(Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonRelease(Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonRelease(Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonRelease(Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons &= ~(1 << button);
        _lastx = x;
        _lasty = y;
    }

    else
    {
        mgr->mouseButtonPress(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonPress(Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonPress(Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonPress(Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonPress(Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonPress(Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons |= 1 << button;
        _lastx = x;
        _lasty = y;
    }

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);

    if(_mousebuttons)
        _navigator.moveTo(x, y);
    _lastx = x;
    _lasty = y;

    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            {
                _navigator.setViewport(NULL);
                _navigator.setCameraTransformation(NULL);

                gwin         = NULL;
                svp          = NULL;


                rootNode     = NULL;
                _dir1_core   = NULL;

                _dir2_core   = NULL;
                dir2_trans   = NULL;

                _obj1_trans  = NULL;
                _dino1_trans = NULL;
                _dino2_trans = NULL;
                _dino3_trans = NULL;
                _dino4_trans = NULL;
                _tree1_trans = NULL;
                _tree2_trans = NULL;
                _tree3_trans = NULL;
                _tree4_trans = NULL;
                _tree5_trans = NULL;
                _tree6_trans = NULL;
                _tree7_trans = NULL;
                _tree8_trans = NULL;
                _tree9_trans = NULL;

                camera       = NULL;
                Pcamera      = NULL;
                cam_beacon   = NULL;
                cam_trans    = NULL;

                delete mgr;

                OSG::osgExit();
                exit(0);
            }
            break;

        case '9':
            {
                _dir1_core->setOn(true);
                _dir1_core->setAmbient(0.3, 0.3, 0.3, 1);
                _dir1_core->setDiffuse(0.8, 0.8, 0.8, 1);

                _dir2_core->setOn(false);
                break;
            }

        case '8':
            {
                _dir1_core->setOn(false);

                _dir2_core->setAmbient(0.3, 0.3, 0.3, 1);
                _dir2_core->setDiffuse(0.8, 0.8, 0.8, 1);
                _dir2_core->setOn(true);
                break;
            }

        case '0':
            {
                _dir1_core->setAmbient(0.15, 0.15, 0.15, 1);
                _dir1_core->setDiffuse(0.4, 0.4, 0.4, 1);
                _dir1_core->setOn(true);

                _dir2_core->setAmbient(0.15, 0.15, 0.15, 1);
                _dir2_core->setDiffuse(0.4, 0.4, 0.4, 1);
                _dir2_core->setOn(true);
                break;
            }

        case 'w':
            {
                Real32  t = svp->getOffBias();

                svp->setOffBias((t + 0.2));
                SLOG << "Polygon-OffsetBias is: " << (t + 0.2) << endLog;
                break;
            }

        case 's':
            {
                Real32  t = svp->getOffBias();

                svp->setOffBias((t - 0.2));
                SLOG << "Polygon-OffsetBias is: " << (t - 0.2) << endLog;
                break;
            }

        case 'e':
            {
                Real32  t = svp->getOffFactor();

                svp->setOffFactor(++t);
                SLOG << "Polygon-OffsetFactor is: " << ++t << endLog;
                break;
            }

        case 'd':
            {
                Real32  t = svp->getOffFactor();

                svp->setOffFactor(--t);
                SLOG << "Polygon-OffsetFactor is: " << --t << endLog;
                break;
            }
        case 'o':
            {
                bool    s = svp->getShadowOn();
                svp->setShadowOn(!s);
                break;
            }
            /*case 'x':
               {
               SceneFileHandler::the().write(rootNode, "shadow.osb.gz", true);
               break;
               }*/

        case '1':
            {
                svp->setShadowMode(ShadowStage::NO_SHADOW);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case '2':
            {
                svp->setShadowMode(ShadowStage::STD_SHADOW_MAP);
                SLOG << "ShadowMode is: STD_SHADOW_MAP" << endLog;
                break;
            }

        case '3':
            {
                svp->setShadowMode(ShadowStage::PERSPECTIVE_SHADOW_MAP);
                SLOG << "ShadowMode is: PERSPECTIVE_SHADOW_MAP" << endLog;
                break;
            }

        case '4':
            {
                svp->setShadowMode(ShadowStage::DITHER_SHADOW_MAP);
                SLOG << "ShadowMode is: DITHER_SHADOW_MAP" << endLog;
                break;
            }

        case '5':
            {
                svp->setShadowMode(ShadowStage::PCF_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                SLOG << "ShadowMode is: PCF_SHADOW_MAP" << endLog;
                break;
            }

        case '6':
            {
                svp->setShadowMode(ShadowStage::PCSS_SHADOW_MAP);
                svp->setShadowSmoothness(1.0);
                SLOG << "ShadowMode is: PCSS_SHADOW_MAP" << endLog;
                break;
            }

        case '7':
            {
                svp->setShadowMode(ShadowStage::VARIANCE_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                SLOG << "ShadowMode is: VARIANCE_SHADOW_MAP" << endLog;
                break;
            }

        case 'y':
            {
                svp->setMapSize(512);
                break;
            }

        case 'x':
            {
                svp->setMapSize(1024);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case 'c':
            {
                svp->setMapSize(2048);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case '+':
            {
                Real32  t = svp->getShadowSmoothness();

                svp->setShadowSmoothness(t + 0.1);
                //SLOG << "ShadowSmoothness is: " << t << endLog;
                break;
            }

        case '-':
            {
                Real32  t = svp->getShadowSmoothness();

                svp->setShadowSmoothness(t - 0.1);
                //SLOG << "ShadowSmoothness is: " << t << endLog;
                break;
            }
        case 'a':
        {
            bAnim = !bAnim;
        }
        break;
    }
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Set WindowSize here
    glutInitWindowSize(640, 512);

    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
