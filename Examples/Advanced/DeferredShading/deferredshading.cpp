
// Work In Progress
//
// This demonstates the use of the DeferredShadingStage and the 
// Shader/TrapezoidalShadowMapEngine with it.
//
// The program must be run from the Examples/Advanced/DeferredShading directory
// so that it can find the files with the GLSL source for the shader programs.
//
// Please take a look at the keyboard glut callback for the interface
//
// Work In Progress

#ifdef OSG_BUILD_ACTIVE

#include <OSGGL.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSceneFileHandler.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleTexturedMaterial.h>

#include <OSGDeferredShadingStage.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>

#include <OSGShaderShadowMapEngine.h>
#include <OSGTrapezoidalShadowMapEngine.h>

// OpenSG Shaders
#include <OSGShaderProgram.h>
#include <OSGShaderProgramChunk.h>

#else // OSG_BUILD_INTEGRATED

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>

#include <OpenSG/OSGDeferredShadingStage.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSSPointLight.h>
#include <OpenSG/OSGSpotLight.h>

#include <OpenSG/OSGShaderShadowMapEngine.h>
#include <OpenSG/OSGTrapezoidalShadowMapEngine.h>

// OpenSG Shaders
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramChunk.h>

#endif // OSG_BUILD_INTEGRATED

#include <iostream>

OSG_USING_NAMESPACE

enum ShadowTypeE
{
    ST_NONE      = 0,
    ST_STANDARD  = 1,
    ST_TRAPEZOID = 2
};

struct LightInfo
{
    LightEngine::LightTypeE    lightType;
    ShadowTypeE                shadowType;
    LightUnrecPtr              light;
    NodeUnrecPtr               lightN;
    NodeUnrecPtr               beaconN;

    ShaderProgramUnrecPtr      lightVP;
    ShaderProgramUnrecPtr      lightFP;
    ShaderProgramChunkUnrecPtr lightSH;
};

std::ostream &operator << (std::ostream &os, const LightInfo &li);

struct GlobalValues
{
    SimpleSceneManager            *mgr;
    GLUTWindowUnrecPtr             glutWin;

    NodeUnrecPtr                   rootN;

    NodeUnrecPtr                   dsStageN;
    DeferredShadingStageUnrecPtr   dsStage;

    NodeUnrecPtr                   sceneN;
    NodeUnrecPtr                   objN;

    std::vector<LightInfo>         lightInfos;

    bool                           animateLights;
    bool                           colorLights;

    LightEngine::LightTypeE        newLightType;
    ShadowTypeE                    newShadowType;

    Int32                          currentLight;

    UInt32                         shadowMapWidth;
    UInt32                         shadowMapHeight;
};

GlobalValues *gv;

const std::string dsGBufferVPFile         ("DSGBuffer.vp.glsl"         );
const std::string dsGBufferFPFile         ("DSGBuffer.fp.glsl"         );

const std::string dsAmbientVPFile         ("DSAmbient.vp.glsl"         );
const std::string dsAmbientFPFile         ("DSAmbient.fp.glsl"         );

const std::string dsDirLightVPFile        ("DSDirLight.vp.glsl"        );
const std::string dsDirLightFPFile        ("DSDirLight.fp.glsl"        );
const std::string dsDirLightShadowFPFile  ("DSDirLightShadow.fp.glsl"  );

const std::string dsPointLightVPFile      ("DSPointLight.vp.glsl"      );
const std::string dsPointLightFPFile      ("DSPointLight.fp.glsl"      );
const std::string dsPointLightShadowFPFile("DSPointLightShadow.fp.glsl");

const std::string dsSpotLightVPFile       ("DSSpotLight.vp.glsl"       );
const std::string dsSpotLightFPFile       ("DSSpotLight.fp.glsl"       );
const std::string dsSpotLightShadowFPFile ("DSSpotLightShadow.fp.glsl" );


void initialize(int  argc, char *argv[]);
void cleanup   (void                   );

void           buildDSStage  (void                       );
NodeTransitPtr loadScene     (const std::string &fileName);
NodeTransitPtr buildTestScene(UInt32 nX, UInt32 nZ);

void addLight (LightEngine::LightTypeE lightType, ShadowTypeE shadowType);
void setShadow(UInt32                  lightIdx,  ShadowTypeE shadowType);
void setColorLights(bool colLights);

int  setupGLUT (int *argc, char *argv[]);
void keyboard(unsigned char k, int , int );

int main(int argc, char *argv[])
{
    initialize(argc, argv);

    keyboard('+', 0, 0);
//    keyboard('+', 0, 0);
    keyboard('.', 0, 0);
    
    keyboard('a', 0, 0);

    commitChanges();

    glutMainLoop();

    return 0;
}


void initialize(int argc, char *argv[])
{
    osgInit(argc, argv);

    gv = new GlobalValues;
    gv->animateLights   = false;
    gv->colorLights     = false;
    gv->newLightType    = LightEngine::Spot;
    gv->newShadowType   = ST_NONE;
    gv->currentLight    = -1;
    gv->shadowMapWidth  = 1024;
    gv->shadowMapHeight = 1024;

    int glutWinId = setupGLUT(&argc, argv);

    gv->glutWin = GLUTWindow::create();
    gv->glutWin->setGlutId(glutWinId);
    gv->glutWin->init     (         );

    gv->mgr = new SimpleSceneManager;

     // tell the manager what to manage
    gv->mgr->setWindow(gv->glutWin);

    // HACK: force creation of internal SSM objects (vp, cam, bg etc)
    gv->mgr->setRoot(NULL);

    gv->mgr->getWindow()->getPort(0)->setSize(0.1f, 0.f, 0.8f, 1.f);

    // create a "scene" to show
    if(argc >= 2)
    {
        std::string fileName = argv[1];

        gv->sceneN = makeCoredNode<Group>();
        
        gv->objN   = loadScene(fileName);
        gv->sceneN->addChild(gv->objN);
    }

    if(gv->sceneN == NULL)
    {
        gv->sceneN = makeCoredNode<Group>();
        gv->objN   = buildTestScene(5, 5);

        gv->sceneN->addChild(gv->objN);
    }

    gv->rootN = makeCoredNode<Group>();

    buildDSStage();

    gv->dsStageN->addChild(gv->sceneN  );
    gv->rootN   ->addChild(gv->dsStageN);

    gv->mgr->setRoot(gv->rootN);
    gv->mgr->showAll();
}

void cleanup(void)
{
    delete gv->mgr;
    gv->mgr = NULL;

    delete gv;
    gv = NULL;

    osgExit();
}


// creates the deferred shading stage and configures the required buffers.
// this assumes that all materials in the scene are regular enough as to be
// written with a single shader to the buffers (e.g. everything has a single
// diffuse texture).
// alternatively the GBufferProgram can be left empty and all materials in the
// scene are set up to write to the correct buffers.
void buildDSStage(void)
{
    ShaderProgramUnrecPtr      vpGBuffer = ShaderProgram::createVertexShader  ();
    ShaderProgramUnrecPtr      fpGBuffer = ShaderProgram::createFragmentShader();

    ShaderProgramUnrecPtr      vpAmbient = ShaderProgram::createVertexShader  ();
    ShaderProgramUnrecPtr      fpAmbient = ShaderProgram::createFragmentShader();

    ShaderProgramChunkUnrecPtr shGBuffer = ShaderProgramChunk::create();
    ShaderProgramChunkUnrecPtr shAmbient = ShaderProgramChunk::create();

    gv->dsStage  = DeferredShadingStage::create();
    gv->dsStageN = makeNodeFor(gv->dsStage);

    gv->dsStage->setCamera(gv->mgr->getCamera());

    // positions (RGB) + ambient (A) term buffer
    gv->dsStage->editMFPixelFormats()->push_back(Image::OSG_RGBA_PF          );
    gv->dsStage->editMFPixelTypes  ()->push_back(Image::OSG_FLOAT32_IMAGEDATA);

    // normals (RGB) buffer
    gv->dsStage->editMFPixelFormats()->push_back(Image::OSG_RGB_PF           );
    gv->dsStage->editMFPixelTypes  ()->push_back(Image::OSG_FLOAT32_IMAGEDATA);

    // diffuse (RGB) buffer
    gv->dsStage->editMFPixelFormats()->push_back(Image::OSG_RGB_PF);
    gv->dsStage->editMFPixelTypes  ()->push_back(Image::OSG_UINT8_IMAGEDATA);

    // G Buffer shader (one for the whole scene)
    vpGBuffer->readProgram(dsGBufferVPFile.c_str());
    fpGBuffer->readProgram(dsGBufferFPFile.c_str());

    fpGBuffer->addUniformVariable<Int32>("tex0", 0);

    shGBuffer->addShader(vpGBuffer);
    shGBuffer->addShader(fpGBuffer);

    gv->dsStage->setGBufferProgram(shGBuffer);

    // ambient shader
    vpAmbient->readProgram(dsAmbientVPFile.c_str());
    fpAmbient->readProgram(dsAmbientFPFile.c_str());

    fpAmbient->addUniformVariable<Int32>("texBufNorm", 1);

    shAmbient->addShader(vpAmbient);
    shAmbient->addShader(fpAmbient);

    gv->dsStage->setAmbientProgram(shAmbient);
}

std::string mapShadowType(ShadowTypeE shadowType)
{
    std::string shadow = "unknown";

    switch(shadowType)
    {
    case ST_NONE:
        shadow = "None";
        break;

    case ST_STANDARD:
        shadow = "Standard";
        break;

    case ST_TRAPEZOID:
        shadow = "Trapezoidal";
        break;
    };

    return shadow;;
}

std::string mapLightType(LightEngine::LightTypeE lightType)
{
    std::string light = "unknown";

    switch(lightType)
    {
    case LightEngine::Directional:
        light = "Directional";
        break;

    case LightEngine::Point:
        light = "Point";
        break;

    case LightEngine::Spot:
        light = "Spot";
        break;
    };

    return light;
}

// file containing vertex shader code for the light type
const std::string &getLightVPFile(
    LightEngine::LightTypeE lightType,
    ShadowTypeE             shadowType)
{
    switch(lightType)
    {
    case LightEngine::Directional:
        return dsDirLightVPFile;

    case LightEngine::Point:
        return dsPointLightVPFile;

    case LightEngine::Spot:
        return dsSpotLightVPFile;
    };
}

// file containing fragment shader code for the light type
const std::string &getLightFPFile(
    LightEngine::LightTypeE lightType,
    ShadowTypeE             shadowType)
{
    switch(lightType)
    {
    case LightEngine::Directional:
        if(shadowType == ST_NONE)
            return dsDirLightFPFile;
        else
            return dsDirLightShadowFPFile;

    case LightEngine::Point:
        if(shadowType == ST_NONE)
            return dsPointLightFPFile;
        else
            return dsPointLightShadowFPFile;

    case LightEngine::Spot:
        if(shadowType == ST_NONE)
            return dsSpotLightFPFile;
        else
            return dsSpotLightShadowFPFile;
    };
}


// adds a light of given type to the scene and makes it cast shadows
// of the given type.
void addLight(LightEngine::LightTypeE lightType, ShadowTypeE shadowType)
{
    LightInfo         li;
    TransformUnrecPtr beacon = Transform::create();
    li.beaconN = makeNodeFor(beacon);

    li.lightVP    = ShaderProgram     ::createVertexShader  ();
    li.lightFP    = ShaderProgram     ::createFragmentShader();
    li.lightSH    = ShaderProgramChunk::create              ();
    li.lightType  = lightType;
    li.shadowType = shadowType;

    switch(lightType)
    {
    case LightEngine::Directional:
    {
        DirectionalLightUnrecPtr dirL = DirectionalLight::create();
        
        li.light = dirL;
    }
    break;

    case LightEngine::Point:
    {
        PointLightUnrecPtr pointL = PointLight::create();
        pointL->setConstantAttenuation(1.0);
        //pointL->setLinearAttenuation  (1.e-5);
        //pointL->setQuadraticAttenuation(2.e-5);

        li.light = pointL;
    }
    break;

    case LightEngine::Spot:
    {
        SpotLightUnrecPtr spotL = SpotLight::create();
        spotL->setPosition (Pnt3f(0.f, 0.f,  0.f));
        spotL->setDirection(Vec3f(0.f, 0.f, -1.f));
        spotL->setSpotCutOff(Pi/6.f);
        spotL->setSpotExponent(3.f);
        spotL->setConstantAttenuation(1.0);
        //spotL->setLinearAttenuation  (1.e-5);
        //spotL->setQuadraticAttenuation(2.e-5);

        li.light = spotL;
    }
    break;
    };

    li.light->setBeacon(li.beaconN);
    li.lightN = makeNodeFor(li.light);

    li.lightFP->addUniformVariable<Int32>("texBufPos",  0);
    li.lightFP->addUniformVariable<Int32>("texBufNorm", 1);
    li.lightFP->addUniformVariable<Int32>("texBufDiff", 2);

    li.lightSH->addShader(li.lightVP);
    li.lightSH->addShader(li.lightFP);

    gv->rootN->addChild(li.beaconN);
    //gv->rootN->addChild(li.lightN );

    gv->dsStage->editMFLights       ()->push_back(li.light  );
    gv->dsStage->editMFLightPrograms()->push_back(li.lightSH);

    gv->lightInfos.push_back(li);

    setShadow(gv->lightInfos.size() - 1, shadowType);

    setColorLights(gv->colorLights);
    
    // add a coordinate system to show light position
//    OSG::NodeUnrecPtr lightAxisN = OSG::makeCoordAxis(2.f);
//    li.beaconN->addChild(lightAxisN);
}

void subLight(UInt32 lightIdx)
{
    OSG_ASSERT(lightIdx < gv->lightInfos                    .size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLights       ()->size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLightPrograms()->size());

    gv->dsStage->editMFLights       ()->erase(lightIdx);
//        gv->dsStage->editMFLights       ()->begin() + lightIdx);
    gv->dsStage->editMFLightPrograms()->erase(lightIdx);
//        gv->dsStage->editMFLightPrograms()->begin() + lightIdx);

    LightInfo &li = gv->lightInfos[lightIdx];
    gv->rootN->subChild(li.beaconN);

    //gv->rootN->subChild(li.lightN );

    gv->lightInfos.erase(gv->lightInfos.begin() + lightIdx);

    setColorLights(gv->colorLights);
}

void setShadow(UInt32 lightIdx, ShadowTypeE shadowType)
{
    OSG_ASSERT(lightIdx < gv->lightInfos                    .size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLights       ()->size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLightPrograms()->size());

    LightInfo &li = gv->lightInfos[lightIdx];

//    li.lightSH->removeObjFromVertexShader  (li.lightVP);
//    li.lightSH->removeObjFromFragmentShader(li.lightFP);

    switch(shadowType)
    {
    case ST_NONE:
    {
        li.light->setLightEngine(NULL);

        gv->dsStage->editMFLights       ();
        gv->dsStage->editMFLightPrograms();

        li.shadowType = ST_NONE;
    }
    break;

    case ST_STANDARD:
    {
        ShaderShadowMapEngineUnrecPtr shadowEng =
            ShaderShadowMapEngine::create();

        shadowEng->setWidth (gv->shadowMapWidth );
        shadowEng->setHeight(gv->shadowMapHeight);
        shadowEng->setOffsetFactor( 4.5f);
        shadowEng->setOffsetBias  (16.f );
        shadowEng->setForceTextureUnit(3);

        gv->dsStage->editMFLights       ();
        gv->dsStage->editMFLightPrograms();
        
        li.light->setLightEngine(shadowEng);
        li.shadowType = ST_STANDARD;
    }
    break;

    case ST_TRAPEZOID:
    {
        if(li.lightType != LightEngine::Directional)
        {
            TrapezoidalShadowMapEngineUnrecPtr shadowEng =
                TrapezoidalShadowMapEngine::create();

            shadowEng->setWidth (gv->shadowMapWidth );
            shadowEng->setHeight(gv->shadowMapHeight);
            shadowEng->setOffsetFactor( 4.5f);
            shadowEng->setOffsetBias  (16.f );
            shadowEng->setForceTextureUnit(3);

            gv->dsStage->editMFLights       ();
            gv->dsStage->editMFLightPrograms();
        
            li.light->setLightEngine(shadowEng);
            li.shadowType = ST_TRAPEZOID;
        }
        else
        {
            std::cout << "TSM not supported for diretional lights."
                      << std::endl;
        }
    }
    break;
    };

    std::string vpFile = getLightVPFile(li.lightType, li.shadowType);
    std::string fpFile = getLightFPFile(li.lightType, li.shadowType);

    std::cerr << "vpFile [" << vpFile << "]" <<std::endl;
    std::cerr << "fpFile [" << fpFile << "]" <<std::endl;

    li.lightVP->readProgram(vpFile.c_str());
    li.lightFP->readProgram(fpFile.c_str());

    li.lightFP->addUniformVariable<Int32>("texBufPos",  0);
    li.lightFP->addUniformVariable<Int32>("texBufNorm", 1);
    li.lightFP->addUniformVariable<Int32>("texBufDiff", 2);

//    li.lightSH->addVertexShader  (li.lightVP);
//    li.lightSH->addFragmentShader(li.lightFP);
}

void setColorLights(bool colLights)
{
    if(gv->lightInfos.size() > 1)
    {
        if(colLights == true)
        {
            // set colorful
            for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
            {
                gv->lightInfos[i].light->setDiffuse(
                    Color4f(       Real32(i+1) / gv->lightInfos.size(),
                            0.f,
                            1.f - (Real32(i+1) / gv->lightInfos.size()),
                            1.f));
            }
        }
        else
        {
            // set lights to grey
            for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
            {
                gv->lightInfos[i].light->setDiffuse(
                    Color4f(1.f / gv->lightInfos.size(),
                            1.f / gv->lightInfos.size(),
                            1.f / gv->lightInfos.size(),
                            1.f                         ));
            }
        }
    }
    else if(gv->lightInfos.empty() == false)
    {
        gv->lightInfos[0].light->setDiffuse(Color4f(1.f, 1.f, 1.f, 1.f));
    }

    // trigger update
    gv->dsStage->editMFLights();

    gv->colorLights = colLights;
}

void updateLightBeacon(OSG::UInt32 lightIdx, OSG::Time t)
{
    OSG_ASSERT(lightIdx < gv->lightInfos                    .size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLights       ()->size());
    OSG_ASSERT(lightIdx < gv->dsStage->getMFLightPrograms()->size());

    Transform *beacon = dynamic_cast<Transform *>(
        gv->lightInfos[lightIdx].beaconN->getCore());

    if(beacon == NULL)
        return;
    
    Pnt3f bbMin;
    Pnt3f bbMax;
    Pnt3f bbCenter;

    gv->objN->updateVolume();
    gv->objN->getVolume().getBounds(bbMin, bbMax);
    gv->objN->getVolume().getCenter(bbCenter    );

    UInt32 numLights  = gv->lightInfos.size();
    Real32 lightFract = Real32(lightIdx + 1) / Real32(numLights);

    Vec3f  bbDiag    = (bbMax - bbMin);
    Real32 bbDiagLen = bbDiag.length();

    Real32 angle1     = osgMod(t / 10.0, Real64(2.f * Pi));
    Real32 angle2     = (2.f * Pi / numLights);
    Real32 shiftVal   = 0.5f * osgSin(4.f * (lightFract * angle2 + angle1)) + 0.25;

    // translate to "above" center of the model
    Matrix matXform0;
    matXform0.setTranslate(bbCenter.subZero() + 
                           Vec3f(0.f, shiftVal * bbDiag[1] * 1.1, 0.f));

    // rotate around y
    Matrix matXform1;
    Quaternion rot1(Vec3f(0.f, 1.f, 0.f), (lightIdx + 1) * angle2 + angle1);
    matXform1.setRotate(rot1);

    // translate 0.5 * bb diag along x
    Matrix matXform2;
    matXform2.setTranslate(Vec3f(0.5f * bbDiagLen, 0.f, 0.f));

    matXform0.mult(matXform1);
    matXform0.mult(matXform2);

    // align to face center
    Pnt3f  lightAt(bbCenter - Vec3f(0.f, 0.25 * bbDiag[1], 0.f));
    Matrix matXform0Inv;
    matXform0Inv.invertFrom(matXform0);
    matXform0Inv.mult      (lightAt, lightAt);

    Matrix matXform3;
    Quaternion rot2(Vec3f(0.f, 0.f, -1.),
                    lightAt.subZero()         );
    matXform3.setRotate(rot2);

    matXform0.mult(matXform3);

    // shift towards center
    //Matrix matXform4;
    //matXform4.setTranslate(Vec3f(0.f, 0.f, shiftVal * bbDiagLen));

    //matXform0.mult(matXform4);

                        
    beacon->setMatrix(matXform0);
}

NodeTransitPtr loadScene(const std::string &fileName)
{
    NodeTransitPtr retVal;
    NodeUnrecPtr   fileSceneN = SceneFileHandler::the()->read(fileName.c_str());

    if(fileSceneN == NULL)
        return retVal;

    commitChanges();

    fileSceneN->updateVolume();
    const BoxVolume &bvol = fileSceneN->getVolume();
    Pnt3f            pmin;
    Pnt3f            pmax;
    bvol.getBounds(pmin, pmax);
    Vec3f            vdiag = pmax - pmin;
    Real32           diag  = vdiag.length();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Matrix matXForm;
    Matrix mat;
    matXForm.setRotate(Quaternion(Vec3f(1.f, 0.f, 0.f), -Pi/2));

    mat.setTranslate(Vec3f(0.f, 0.f, - 0.4 * diag));

    matXForm.mult(mat);

    xform->setMatrix(matXForm);
    
    GeometryUnrecPtr plane  = makePlaneGeo(4.f * diag, 4.f * diag, 1, 1); 
    NodeUnrecPtr     planeN = makeNodeFor(plane);

    UInt8 pixelData[] =
    {
        128, 128, 128, 255, 255, 255,
        255, 255, 255, 128, 128, 128
    };

    ImageUnrecPtr texImg = Image::create();
    texImg->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0.0, pixelData);

    SimpleTexturedMaterialUnrecPtr smat = SimpleTexturedMaterial::create();
    smat->setImage(texImg);
    smat->setMinFilter(GL_NEAREST);
    smat->setMagFilter(GL_NEAREST);

//    plane->setMaterial(smat);
    plane->setMaterial(getDefaultMaterial());

    xformN    ->addChild(planeN);
    gv->sceneN->addChild(xformN);

    retVal = fileSceneN;

    return retVal;
}

NodeTransitPtr buildTestScene(UInt32 nX, UInt32 nZ)
{
    Real32 stepX  = 10.f;
    Real32 stepZ  = 10.f;

    Real32 startX = - stepX * (nX-1) / 2.;
    Real32 startZ = - stepZ * (nZ-1) / 2.;

    NodeTransitPtr   groupN  = makeCoredNode<Group>();
//    GeometryUnrecPtr objGeo  = makeBoxGeo(1.f, 1.f, 1.f, 1, 1, 1);
//    GeometryUnrecPtr objGeo  = makeLatLongSphereGeo(16, 16, 1.f);
    GeometryUnrecPtr objGeo  = makeSphereGeo(2, 1.f);

    for(UInt32 iX = 0; iX < nX; ++iX)
    {
        for(UInt32 iZ = 0; iZ < nZ; ++iZ)
        {
            NodeUnrecPtr      objGeoN = makeNodeFor(objGeo);
            TransformUnrecPtr xform   = Transform::create();
            NodeUnrecPtr      xformN  = makeNodeFor(xform);

            Matrix matXForm;
            Vec3f  vecTrans(startX + iX * stepX,
                            4.f * osgCos(Pi/5.f * Real32(iX + iZ)),
                            startZ + iZ * stepZ                          );

            std::cout << "iX " << iX << " iZ " << iZ << " vecTrans " << vecTrans << std::endl;
            matXForm.setTranslate(vecTrans);
            xform->setMatrix(matXForm);

            xformN->addChild(objGeoN);
            groupN->addChild(xformN );

            // add a 2nd layer of objects
            NodeUnrecPtr      objGeoN2 = makeNodeFor(objGeo);
            TransformUnrecPtr xform2   = Transform::create();
            NodeUnrecPtr      xformN2  = makeNodeFor(xform2);

            Matrix matXForm2;
            matXForm2.setTranslate(Vec3f(startX + iX * stepX,
                                         15.f,
                                         startZ + iZ * stepZ ));
            xform2->setMatrix(matXForm2);

            xformN2->addChild(objGeoN2);
            groupN ->addChild(xformN2 );
        }
    }

    // ground plane
    TransformUnrecPtr xform   = Transform::create();
    NodeUnrecPtr      xformN  = makeNodeFor(xform);

    Matrix matXForm;
    matXForm.setTranslate(Vec3f(0.f, -5.f, 0.f));
    matXForm.setRotate   (Quaternion(Vec3f(1.f, 0.f, 0.f), -PiHalf));
    xform->setMatrix(matXForm);

    NodeUnrecPtr planeGeoN = makePlane(nX * stepX, nZ * stepZ, 1, 1);

    xformN->addChild(planeGeoN);
    groupN->addChild(xformN   );


    // back box
    xform   = Transform::create();
    xformN  = makeNodeFor(xform);

    matXForm.setIdentity();
    matXForm.setTranslate(Vec3f(0.f, 15.f, -20.f));
    xform->setMatrix(matXForm);

    NodeUnrecPtr boxGeoN = makeBox(nX * stepX, 35.f, 2.f, 1, 1, 1);

    xformN->addChild(boxGeoN);
    groupN->addChild(xformN );

    return groupN;
}

std::ostream &operator << (std::ostream &os, const LightInfo &li)
{
    os <<   "lightType " << mapLightType(li.lightType)
       << " " << (li.light->getOn() ? "on" : "off")
       << " shadowType " << mapShadowType(li.shadowType);

    return os;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    gv->mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    static OSG::Time   tStart  = OSG::getSystemTime();
    static OSG::Time   tLast   = OSG::getSystemTime();
    static OSG::Time   tAnim   = OSG::getSystemTime();
    static OSG::Time   tFrames = OSG::getSystemTime();
    static OSG::UInt32 frames  = 0;

    OSG::Time tNow = OSG::getSystemTime();

    if(gv->animateLights == true)
    {
        tAnim += (tNow - tLast);
    }

    for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
    {
        updateLightBeacon(i, tAnim);
    }

    ++frames;

    if(tNow - tFrames > 1.f)
    {
        std::cout << "delta t: " << (tNow - tFrames) << " frames: " << frames << std::endl;
        tFrames = tNow;
        frames  = 0;
    }

    tLast = tNow;

    commitChangesAndClear();

    gv->mgr->redraw();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        gv->mgr->mouseButtonRelease(button, x, y);
    else
        gv->mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    gv->mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:
    {
        // exit
        cleanup();
        exit(0);
    }
    break;

    case '1':
    {
        // all lights no shadow
        for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
        {
            setShadow(i, ST_NONE);
            std::cout << "changed shadow type for light "
                      << i << " " << gv->lightInfos[i]
                      << std::endl;
        }
    }
    break;

    case '2':
    {
        // all lights standard shadows
        for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
        {
            setShadow(i, ST_STANDARD);
            std::cout << "changed shadow type for light "
                      << i << " " << gv->lightInfos[i]
                      << std::endl;
        }
    }
    break;

    case '3':
    {
        // all lights TSM shadows
        for(UInt32 i = 0; i < gv->lightInfos.size(); ++i)
        {
            setShadow(i, ST_TRAPEZOID);
            std::cout << "changed shadow type for light "
                      << i << " " << gv->lightInfos[i]
                      << std::endl;
        }
    }
    break;

    case 'a':
    {
        // toggle lights moving
        gv->animateLights = !gv->animateLights;

        std::cout << "animating lights: " << gv->animateLights << std::endl;
    }
    break;

    case 'c':
    {
        // toggle all lights white/colorful
        gv->colorLights = !gv->colorLights;

        std::cout << "color lights: " << gv->colorLights << std::endl;
        
        setColorLights(gv->colorLights);
    }
    break;

    case 'o':
    {
        // toggle current light on/off
        if(gv->currentLight <  gv->lightInfos.size() &&
           gv->currentLight >= 0                       )
        {
            Light *light = gv->lightInfos[gv->currentLight].light;

            light->setOn(!light->getOn());

            std::cout << gv->lightInfos[gv->currentLight] << std::endl;
        }
    }
    break;

    case '+':
    {
        // add new light
        addLight (gv->newLightType, gv->newShadowType);

        std::cout << "added light " << (gv->lightInfos.size() - 1) << " "
                  << gv->lightInfos.back()
                  << std::endl;
    }
    break;

    case '-':
    {
        // remove current light
        if(gv->currentLight <  gv->lightInfos.size() &&
           gv->currentLight >= 0                       )
        {
            std::cout << "removing light " << gv->currentLight << " "
                      << gv->lightInfos[gv->currentLight]
                      << std::endl;

            subLight(gv->currentLight);
        }
    }
    break;

    case 's':
    {
        // cycle through shadow types for current light
        if(gv->currentLight <  gv->lightInfos.size() &&
           gv->currentLight >= 0                       )
        {
            if(gv->lightInfos[gv->currentLight].shadowType == ST_NONE)
            {
                setShadow(gv->currentLight, ST_STANDARD);
            }
            else if(gv->lightInfos[gv->currentLight].shadowType == ST_STANDARD)
            {
                setShadow(gv->currentLight, ST_TRAPEZOID);
            }
            else
            {
                setShadow(gv->currentLight, ST_NONE);
            }

            std::cout << "changed shadow type for light "
                      << gv->currentLight << " "
                      << gv->lightInfos[gv->currentLight]
                      << std::endl;
        }
    }
    break;

    case '.':
    {
        // select previous light
        gv->currentLight += 1;
        if(gv->currentLight >= gv->lightInfos.size())
            gv->currentLight = 0;

        if(gv->currentLight <  gv->lightInfos.size() &&
           gv->currentLight >= 0                       )
        {
            std::cout << "currentLight " << gv->currentLight
                      << " (total: " << gv->lightInfos.size() << ") "
                      << gv->lightInfos[gv->currentLight]
                      << std::endl;
        }
    }
    break;
    
    case ',':
    {
        // select next light
        gv->currentLight -= 1;
        
        if(gv->currentLight < 0)
            gv->currentLight = gv->lightInfos.size() - 1;
         
        if(gv->currentLight <  gv->lightInfos.size() &&
           gv->currentLight >= 0                       )
        {
            std::cout << "currentLight " << gv->currentLight
                      << " (total: " << gv->lightInfos.size() << ") "
                      << gv->lightInfos[gv->currentLight]
                      << std::endl;
        }
    }
    break;

    }

    glutPostRedisplay();
}

// just request a redraw
void idle(void)
{
    glutPostRedisplay();
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
    glutIdleFunc(idle);

    glutReshapeWindow(1400, 1050);

    return winid;
}
