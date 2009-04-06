// OpenSG Tutorial Example: FBO Texture
//
// This example shows how to use FrameBufferObject and SimpleStage to render
// a subtree of the scene graph to a texture and then use that texture
// when drawing another part of the scene.
//
// The scene graph constructed in this example looks like this:
//
// scene[Group] -+- fboScene[SimpleStage] --- fboScene --- {loaded model +
//               |                                          light and beacon}
//               |
//               +- flagScene[Group] --- {flag and pole}
//
// If you run this example and zoom in close to the flag or move it to the
// edge of the screen the model on it may stop rotating. This happens because
// the model actually is positioned about half way up the flag's pole and
// get's frustum culled if that part of the scene is outside the camera
// frustum.

#ifdef OSG_BUILD_ACTIVE
// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGComponentTransform.h>

#include <OSGSimpleStage.h>
#include <OSGPointLight.h>
#include <OSGFrameBufferObject.h>
#include <OSGTextureBuffer.h>
#include <OSGRenderBuffer.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGTwoSidedLightingChunk.h>
#include <OSGSceneFileHandler.h>
#include <OSGImageFunctions.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGTextureTransformChunk.h>
#include <OSGGradientBackground.h>
#include <OSGPerspectiveCamera.h>
#else
// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGComponentTransform.h>

#include <OpenSG/OSGSimpleStage.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGFrameBufferObject.h>
#include <OpenSG/OSGTextureBuffer.h>
#include <OpenSG/OSGRenderBuffer.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTexGenChunk.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGImageFunctions.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGTextureTransformChunk.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#endif

// flag parameters
const OSG::Real32 flagHeight   = 8.0f;
const OSG::Real32 flagWidth    = 16.0f;
const OSG::UInt32 flagGeoHor   = static_cast<OSG::UInt32>(flagWidth  * 3);
const OSG::UInt32 flagGeoVert  = static_cast<OSG::UInt32>(flagHeight / 2);
const OSG::Real32 flagWaveDamp = 0.06f;

const OSG::Real32 poleHeight   = 24.0f;
const OSG::Real32 poleDia      = poleHeight * 0.01f;

// fbo size -- you can increase these values to get a higher resolution image
const OSG::UInt32 fboWidth     = static_cast<OSG::UInt32>(flagWidth  * 32);
const OSG::UInt32 fboHeight    = static_cast<OSG::UInt32>(flagHeight * 32);

// global variables
OSG::SimpleSceneManager   *mgr;
OSG::NodeRefPtr            stageCamBeaconN;
OSG::TransformRefPtr       stageCamBeacon;

OSG::NodeRefPtr            modelTransN;
OSG::TransformRefPtr       modelTrans;

// forward declaration so we can have the interesting stuff upfront
int                 setupGLUT    (int *argc, char *argv[]);
OSG::NodeTransitPtr buildFBOScene(int  argc, char *argv[]);
OSG::NodeTransitPtr buildScene   (OSG::TextureObjChunkRefPtr fboTex);

/*
    Construct a scene that uses a Stage to render a subtree to an FBO (making
    the result available as a texture) and use that in another subtree.
*/
OSG::NodeTransitPtr buildStage(int argc, char *argv[])
{
    /*
        Begin by setting up an FBO with a TextureBuffer, so we can capture
        and reuse what is being rendered to the FBO.
    */
    
    OSG::ImageRefPtr             fboTexImg = OSG::Image            ::create();
    OSG::TextureObjChunkRefPtr   fboTex    = OSG::TextureObjChunk  ::create();
    
    OSG::FrameBufferObjectRefPtr fbo       = OSG::FrameBufferObject::create();
    OSG::TextureBufferRefPtr     texBuf    = OSG::TextureBuffer    ::create();
    OSG::RenderBufferRefPtr      depthBuf  = OSG::RenderBuffer     ::create();
    
    // set up the texture ...
    fboTexImg->set(OSG::Image::OSG_RGB_PF, fboWidth, fboHeight);
    fboTex->setImage(fboTexImg);
    
    // ... and add it to the texture buffer
    texBuf->setTexture(fboTex);
    
    // add a depth attachment, otherwise there is no depth buffer when
    // rendering to the FBO
    depthBuf->setInternalFormat(GL_DEPTH_COMPONENT24);
    
    // make the fbo render to the texture
    fbo->setColorAttachment(texBuf,   0);
    fbo->setDepthAttachment(depthBuf   );
    fbo->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);
    fbo->setWidth (fboWidth );
    fbo->setHeight(fboHeight);
    
    /*
        Next we set up a Stage, which renders the subtree below it to its
        render target (the FBO from above).
    */
    
    OSG::SimpleStageRefPtr stage  = OSG::SimpleStage::create();
    OSG::NodeRefPtr        stageN = OSG::makeNodeFor(stage);
    
    // add the scene to be rendered to the fbo as child of the Stage
    OSG::NodeRefPtr fboSceneN = buildFBOScene(argc, argv);
    stageN->addChild(fboSceneN);
    
    // make the stage render to the FBO instead of the normal framebuffer
    stage->setRenderTarget(fbo);
    
    // use the full size of the target (this is like setting up the viewport
    // of the stage)
    stage->setSize(0.0f, 0.0f, 1.0f, 1.0f);
    
    // set a different background for things on the stage ...
    OSG::GradientBackgroundRefPtr gb = OSG::GradientBackground::create();
    gb->addLine(OSG::Color3f(0.3, 0.3, 0.8), 0.0);
    gb->addLine(OSG::Color3f(0.5, 0.5, 0.5), 1.0);
    stage->setBackground(gb);
    
    // ... and add a camera
    OSG::PerspectiveCameraRefPtr stageCam = OSG::PerspectiveCamera::create();
    stage->setCamera(stageCam);
    
    stageCam->setBeacon(stageCamBeaconN);
    stageCam->setNear  (   0.1);
    stageCam->setFar   (1000.0);
    stageCam->setFov   (   1.5);
    
    // add the scene using the fbo
    OSG::NodeRefPtr sceneN = buildScene(fboTex);
    
    // place the stage and the scene using the fbo under a common group
    OSG::NodeRefPtr rootN = OSG::makeCoredNode<OSG::Group>();
    
    rootN->addChild(stageN);
    rootN->addChild(sceneN);
    
    return OSG::NodeTransitPtr(rootN);
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

        OSG::NodeRefPtr scene = buildStage(argc, argv);
        
        OSG::commitChanges();
        
        // create the SimpleSceneManager helper
        mgr = new OSG::SimpleSceneManager;
    
        // tell the manager what to manage
        mgr->setWindow(gwin );
        mgr->setRoot  (scene);
    
        // show the whole scene
        mgr->showAll();
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
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
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

void update(void)
{
    glutPostRedisplay();
}

// redraw the window
void display( void )
{
    static OSG::Real64 t0 = OSG::getSystemTime();

    // get the current time
    OSG::Real64 t = OSG::getSystemTime() - t0;
    
    OSG::Matrix m;
    OSG::Quaternion q;
    q.setValueAsAxisDeg(0, 1, 0, t * 10.f);
    m.setRotate(q);
    modelTrans->setMatrix(m);
    
    
    OSG::commitChangesAndClear();
    
    mgr->redraw();
}

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            // clean up global variables
            delete mgr;
            stageCamBeaconN = NULL;
            stageCamBeacon  = NULL;
            
            modelTransN     = NULL;
            modelTrans      = NULL;
            
            OSG::osgExit();
            exit(0);
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
    glutIdleFunc(update);

    return winid;
}

/*
    Loads a model given on the command line or creates a fallback.
    This scene is rendered to a texture (fboTexture) which is later used on
    another object, however none of this happens in here, only the scene is
    constructed.
*/
OSG::NodeTransitPtr buildFBOScene(int argc, char *argv[])
{
    OSG::NodeRefPtr modelN;

    if(argc > 1)
        modelN = OSG::SceneFileHandler::the()->read(argv[1]);

    // no argument or loading failed -> use a torus
    if(modelN == NULL)
        modelN = OSG::makeTorus(0.3, 4, 16, 64);

    OSG::commitChanges();
    OSG::Pnt3f bbMin, bbMax;
    modelN->updateVolume();
    modelN->getVolume().getBounds(bbMin, bbMax);
    
    OSG::NodeRefPtr fboSceneN = OSG::makeCoredNode<OSG::Group>();
    
    stageCamBeacon;
    stageCamBeaconN      = OSG::makeCoredNode<OSG::Transform>(&stageCamBeacon);

    modelTransN          = OSG::makeCoredNode<OSG::Transform>(&modelTrans);
    
    // move the camera back
    OSG::Real32 bbDia = (bbMax - bbMin).length();
    stageCamBeacon->editMatrix().setTranslate(OSG::Vec3f(0.0f, 0.0f, bbDia));
    
    OSG::PointLightRefPtr light;
    OSG::NodeRefPtr       lightN = OSG::makeCoredNode<OSG::PointLight>(&light);
    light->setBeacon(stageCamBeaconN);
    
    fboSceneN->addChild(lightN );
    fboSceneN->addChild(stageCamBeaconN);
    
    lightN->addChild(modelTransN);

    modelTransN->addChild(modelN);
    
    return OSG::NodeTransitPtr(fboSceneN);
}

// create a wood texture
OSG::SimpleTexturedMaterialTransitPtr createWoodMaterial(void)
{
    OSG::SimpleTexturedMaterialRefPtr mat = 
        OSG::SimpleTexturedMaterial::create();

    OSG::ImageRefPtr img = OSG::Image::create();
    createNoise(img, OSG::Image::OSG_L_PF, 7, 64);
    
    mat->setImage(img);
    mat->setEnvMode(GL_MODULATE);
    mat->setDiffuse(OSG::Color3f(0.9f, 0.57f, 0.1f));
    mat->setSpecular(OSG::Color3f(0.2f, 0.2f, 0.1f));
    
    OSG::TextureTransformChunkRefPtr ttrans = 
        OSG::TextureTransformChunk::create();
    OSG::Matrix m;
    m.setScale(2.0, 8.0, 2.0);
    ttrans->setMatrix(m);
    
    mat->addChunk(ttrans);

    return OSG::SimpleTexturedMaterialTransitPtr(mat);
}


/*
    Builds a scene with a flag on a pole. The flag is textured with the
    image of the fbo scene (fboTexture).
*/
OSG::NodeTransitPtr buildScene(OSG::TextureObjChunkRefPtr fboTex)
{
    OSG::NodeRefPtr     flagScene = OSG::makeCoredNode<OSG::Group>();
    OSG::GeometryRefPtr flagGeo   = OSG::makePlaneGeo(flagWidth,  flagHeight,
                                                      flagGeoHor, flagGeoVert);
    
    // disable caching as we will change this geometry every frame
    flagGeo->setDlistCache(false);

    OSG::SimpleMaterialRefPtr  flagMat   = OSG::SimpleMaterial ::create();
    OSG::TextureEnvChunkRefPtr fboTexEnv = OSG::TextureEnvChunk::create();
    
    fboTexEnv->setEnvMode(GL_REPLACE);
    
    flagMat->addChunk(fboTex   );
    flagMat->addChunk(fboTexEnv);
        
    // add a light glossy effect (environment noise-map)
    if (0)
    {
        OSG::ImageRefPtr noise = OSG::Image::create();
        createNoise(noise, OSG::Image::OSG_I_PF, 5, 256);
        
        // make noise image darker (as it will be GL_ADDed)
        for(int i = 0; i < noise->getSize(); ++i)
            noise->editData()[i] >>= 2; // *= 0.125
        
        OSG::TextureObjChunkRefPtr glossObj = OSG::TextureObjChunk::create();
        OSG::TextureEnvChunkRefPtr glossEnv = OSG::TextureEnvChunk::create();
        
        glossObj->setImage(noise);
        glossEnv->setEnvMode(GL_ADD);
        
        OSG::TexGenChunkRefPtr envMap = OSG::TexGenChunk::create();
        envMap->setGenFuncS(GL_SPHERE_MAP);
        envMap->setGenFuncT(GL_SPHERE_MAP);

        // add for use with 2nd texture unit
        flagMat->addChunk(glossObj, 1);
        flagMat->addChunk(glossEnv, 1);
        flagMat->addChunk(envMap,   1);
    }

    flagMat->addChunk(
        OSG::StateChunkRefPtr(OSG::TwoSidedLightingChunk::create()));
    flagMat->setSpecular(OSG::Color3f(0.4f, 0.4f, 0.4f));
    flagMat->setDiffuse (OSG::Color3f(0.7f, 0.7f, 0.7f));

    flagGeo->setMaterial(flagMat);

    // create transform node to hook up the flag to the pole
    OSG::ComponentTransformRefPtr flagTrans;
    OSG::NodeRefPtr flagTransN = 
        OSG::makeCoredNode<OSG::ComponentTransform>(&flagTrans);
    
    OSG::Vec3f v(0.5f * flagWidth, 0.5f * (poleHeight - flagHeight) , 0.0f);
    flagTrans->setTranslation(v);

    // attach flag-geometry to transform-node
    flagTransN->addChild(OSG::NodeRefPtr(OSG::makeNodeFor(flagGeo)));

    // build flag pole
    OSG::GeometryRefPtr pole    = OSG::makeCylinderGeo(poleHeight, poleDia, 24, true, true, true);
    OSG::NodeRefPtr     poleN   = OSG::makeNodeFor(pole);
    OSG::MaterialRefPtr woodMat = createWoodMaterial();
    
    pole->setMaterial(woodMat);

    // attach objects to group node
    flagScene->addChild(flagTransN);
    flagScene->addChild(poleN     );

    return OSG::NodeTransitPtr(flagScene);
}
