// OpenSG Example: ComputeShader2
//
// This example shows the most basic usage of the compute shader.
// It is a plain translation of the ComplexSceneManager example
// found in Examples/CSM/NewShader/Compute/SimpleTex.
//
// This example differs from the ComputeShader1 only in that a
// ShaderProgram object is used instead of providing the shader
// source code directly to the ComputeShaderChunk. The variables
// are also specified in the ShaderProgram object, which allows the 
// usage of uniform and shader storage buffer objects. The next example
// ComputeShader3 makes use of that.
//

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

// new headers: 
#include <OSGAlgorithmComputeElement.h>
#include <OSGChunkMaterial.h>
#include <OSGComputeShaderAlgorithm.h>
#include <OSGComputeShaderChunk.h>
#include <OSGContainerCollection.h>
#include <OSGFieldConnector.h>
#include <OSGFrameHandler.h>
#include <OSGGeometry.h>
#include <OSGImage.h>
#include <OSGImageFileHandler.h>
#include <OSGMaterialChunk.h>
#include <OSGMaterialGroup.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramVariables.h>
#include <OSGShaderVariableReal.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTextureImageChunk.h>
#include <OSGTime.h>
#include <OSGTimeSensor.h>
#include <OSGTypedGeoIntegralProperty.h>
#include <OSGTypedGeoVectorProperty.h>
#include <OSGVRMLScalarInterpolator.h>
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

// new headers: 
#include <OpenSG/OSGAlgorithmComputeElement.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGComputeShaderAlgorithm.h>
#include <OpenSG/OSGComputeShaderChunk.h>
#include <OpenSG/OSGContainerCollection.h>
#include <OpenSG/OSGFieldConnector.h>
#include <OpenSG/OSGFrameHandler.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramVariables.h>
#include <OpenSG/OSGShaderVariableReal.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTextureImageChunk.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGTimeSensor.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>
#include <OpenSG/OSGVRMLScalarInterpolator.h>
#endif

OSG::SimpleSceneManagerRefPtr mgr = NULL;

std::string get_cp_program();

OSG::NodeTransitPtr createPlane(OSG::TextureObjChunk* texObjChunk)
{
    OSG::MaterialChunkRefPtr matChunk = OSG::MaterialChunk::create();
    matChunk->setDiffuse(OSG::Color4f(0.f, 0.f, 0.f, 1.f));

    OSG::TextureEnvChunkRefPtr texEnvChunk = OSG::TextureEnvChunk::create();
    texEnvChunk->setEnvMode(GL_REPLACE);

    OSG::ChunkMaterialRefPtr chunkMaterial = OSG::ChunkMaterial::create();
    chunkMaterial->addChunk(texObjChunk, 0);
    chunkMaterial->addChunk(texEnvChunk);
    chunkMaterial->addChunk(matChunk);


    OSG::MaterialGroupRefPtr matGroup = OSG::MaterialGroup::create();
    matGroup->setMaterial(chunkMaterial);

    OSG::NodeRefPtr plane = OSG::makeNodeFor(matGroup);

    OSG::GeometryRefPtr geometry = OSG::Geometry::create();
    geometry->setDlistCache(false);
    geometry->setUseVAO(true);
    geometry->setUseAttribCalls(true);

    OSG::NodeRefPtr geomNode = OSG::makeNodeFor(geometry);

    OSG::GeoUInt8PropertyRefPtr   types    = OSG::GeoUInt8Property ::create();
    OSG::GeoUInt32PropertyRefPtr  lengths  = OSG::GeoUInt32Property::create();
    OSG::GeoPnt3fPropertyRefPtr   vertices = OSG::GeoPnt3fProperty ::create();
    OSG::GeoVec3fPropertyRefPtr   normals  = OSG::GeoVec3fProperty ::create();
    OSG::GeoColor3fPropertyRefPtr colors   = OSG::GeoColor3fProperty::create();
    OSG::GeoVec2fPropertyRefPtr   textures = OSG::GeoVec2fProperty ::create();
    OSG::GeoUInt32PropertyRefPtr  indices  = OSG::GeoUInt32Property::create();

    types   ->setUseVBO(true);
    lengths ->setUseVBO(true);
    indices ->setUseVBO(true);
    vertices->setUseVBO(true);
    normals ->setUseVBO(true);
    colors  ->setUseVBO(true);
    textures->setUseVBO(true);

    types   ->setUsage(OSG::GeoProperty::UsageSystemSet);
    lengths ->setUsage(OSG::GeoProperty::UsageSystemSet);
    indices ->setUsage(OSG::GeoProperty::UsageSystemSet);
    vertices->setUsage(OSG::GeoProperty::UsageSystemSet);
    normals ->setUsage(OSG::GeoProperty::UsageSystemSet);
    colors  ->setUsage(OSG::GeoProperty::UsageSystemSet);
    textures->setUsage(OSG::GeoProperty::UsageSystemSet);

    types  ->push_back(4);
    lengths->push_back(6);

    indices->push_back(0);
    indices->push_back(1);
    indices->push_back(2);
    indices->push_back(0);
    indices->push_back(2);
    indices->push_back(3);

    vertices->push_back(OSG::Pnt3f(-1.f,-1.f,-1.f));
    vertices->push_back(OSG::Pnt3f( 1.f,-1.f,-1.f));
    vertices->push_back(OSG::Pnt3f( 1.f, 1.f,-3.f));
    vertices->push_back(OSG::Pnt3f(-1.f, 1.f,-3.f));

    normals->push_back(OSG::Vec3f(0.f, 0.f, 1.f));
    normals->push_back(OSG::Vec3f(0.f, 0.f, 1.f));
    normals->push_back(OSG::Vec3f(0.f, 0.f, 1.f));
    normals->push_back(OSG::Vec3f(0.f, 0.f, 1.f));

    colors->push_back(OSG::Color3f(0.f, 1.f, 0.f));

    textures->push_back(OSG::Vec2i(0,0));
    textures->push_back(OSG::Vec2i(1,0));
    textures->push_back(OSG::Vec2i(1,1));
    textures->push_back(OSG::Vec2i(0,1));

    geometry->setTypes    (types);
    geometry->setLengths  (lengths);
    geometry->setIndices  (indices);
    geometry->setPositions(vertices);
    geometry->setNormals  (normals);
    geometry->setColors   (colors);
    geometry->setTexCoords(textures);

    plane->addChild(geomNode);

    return OSG::NodeTransitPtr(plane);
}

OSG::NodeTransitPtr createScene()
{
    OSG::ImageRefPtr image = OSG::ImageFileHandler::the()->read("Examples/CSM/Models/Textures/Earth512.png");

    OSG::TextureObjChunkRefPtr texObjChunk = OSG::TextureObjChunk::create();
    texObjChunk->setInternalFormat(GL_RGBA32F);
    texObjChunk->setMinFilter(GL_LINEAR);
    texObjChunk->setMagFilter(GL_LINEAR);
    texObjChunk->setImage(image);

    OSG::NodeRefPtr planeNode = createPlane(texObjChunk);

    OSG::AlgorithmComputeElementRefPtr algoCompElement = OSG::AlgorithmComputeElement::create();
    OSG::NodeRefPtr computeNode = OSG::makeNodeFor(algoCompElement);
    computeNode->addChild(planeNode);

    OSG::ComputeShaderAlgorithmRefPtr compShaderAlgo = OSG::ComputeShaderAlgorithm::create();
    algoCompElement->setAlgorithm(compShaderAlgo);

    OSG::TextureImageChunkRefPtr  texImgChunk = OSG::TextureImageChunk::create();
    texImgChunk->setTexture(texObjChunk);
    texImgChunk->setAccess(GL_WRITE_ONLY);
    texImgChunk->setFormat(GL_RGBA32F);

    OSG::ShaderProgramRefPtr compShader = OSG::ShaderProgram::create();
    compShader->setShaderType(GL_COMPUTE_SHADER);
    compShader->setProgram(get_cp_program());
    compShader->addUniformVariable("destTex", 0);
    compShader->addUniformVariable("roll",    0.f);

    OSG::ComputeShaderChunkRefPtr compShaderChunk = OSG::ComputeShaderChunk::create();
    compShaderChunk->addComputeShader(compShader);
    compShaderChunk->setVariables(compShader->getVariables());

    compShaderAlgo->setComputeShader(compShaderChunk);
    compShaderAlgo->pushToTextureImages(texImgChunk);
    compShaderAlgo->setDispatchConfig(OSG::Vec3i(32, 32, 1));

    OSG::NodeRefPtr scene = OSG::makeCoredNode<OSG::Group>();
    scene->addChild(computeNode);

    OSG::TimeSensorRefPtr sceneTimer = OSG::TimeSensor::create();
    sceneTimer->setLoop(true);
    sceneTimer->setCycleInterval(10);

    OSG::VRMLScalarInterpolatorRefPtr rollInter = OSG::VRMLScalarInterpolator::create();
    rollInter->editMFKeyValue()->push_back(0.f);
    rollInter->editMFKeyValue()->push_back(10.24f);

    rollInter->editMFKey()->push_back(0.f);
    rollInter->editMFKey()->push_back(1.f);

    const OSG::ShaderVariableReal* varRealRoll  = dynamic_cast<const OSG::ShaderVariableReal*>(compShader->getVariables()->getVariable("roll"));

    addConnection(sceneTimer, "fraction", rollInter, "inValue");
    addConnection(rollInter, "outValue", const_cast<OSG::ShaderVariableReal*>(varRealRoll), "value");

    OSG::ContainerCollectionRefPtr containerCollection = OSG::ContainerCollection::create();

    containerCollection->addContainer(rollInter);
    containerCollection->addContainer(sceneTimer);

    scene->addAttachment(containerCollection);

    return OSG::NodeTransitPtr(scene);
}

//
// forward declaration so we can have the interesting stuff upfront
//
int  setupGLUT(int *argc, char *argv[]);
void releaseGLUT();
void print_help();

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    OSG::preloadSharedObject("OSGImageFileIO");

    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    print_help();

    // open a new scope, because the pointers below should go out of scope
    // before entering glutMainLoop.
    // Otherwise OpenSG will complain about objects being alive after shutdown.
    {
        // the connection between GLUT and OpenSG
        OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
        gwin->setGlutId(winid);
        gwin->init();
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        // The scene
        OSG::NodeRefPtr scene = createScene();

        mgr->setRoot(scene);

        OSG::commitChanges();
    
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

//
// redraw the window
//
void display(void)
{
    OSG::FrameHandler::the()->frame();

    OSG::commitChanges();
    
    mgr->redraw();
}
//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

//
// react to mouse button presses
//
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

//
// react to keys
//
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:        // ESC
        {
            // clean up global variables
            mgr = NULL;

            releaseGLUT();

            OSG::osgExit();
            exit(0);
        }
        break;
    }
}

//
// setup the GLUT library which handles the windows for us
//
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 800);
    
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

void releaseGLUT()
{
    glutReshapeFunc(NULL);
    glutDisplayFunc(NULL);
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutKeyboardFunc(NULL);
    glutIdleFunc(NULL);
}

void print_help()
{
    std::cout << "Esc   : quit example" << std::endl;
}


std::string get_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 440 compatibility"
    << endl << ""
    << endl << "uniform float roll;"
    << endl << "uniform writeonly image2D destTex;"
    << endl << ""
    << endl << "layout (local_size_x = 16, local_size_y = 16) in;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    ivec2   storePos = ivec2( gl_GlobalInvocationID.xy );"
    << endl << "    float  localCoef = length( vec2( ivec2(gl_LocalInvocationID.xy) - 8 ) / 8.0 );"
    << endl << "    float globalCoef = sin( float(gl_WorkGroupID.x + gl_WorkGroupID.y) * 0.1 + roll ) * 0.5;"
    << endl << ""
    << endl << "    imageStore(destTex, storePos, vec4(1.0 - globalCoef * localCoef, 0.0, 0.0, 0.0));"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
