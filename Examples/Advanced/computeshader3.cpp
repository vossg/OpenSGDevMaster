// OpenSG Example: ComputeShader3
//
// This example shows the basic usage of the compute shader.
// It is a variation of the ComplexSceneManager example
// found in Examples/CSM/NewShader/Compute/SimpleTex.
//
// In this example a material database in form of a shader storage
// buffer object is used in the shader in order to color the pixels
// of the image differently. The setup of the shader storage buffer
// object is shown and the example works with a variable work
// group size for illustration purpose. Additionally, the use of a
// memory barrier at the end of the comptuation is shown.
//
#include <boost/foreach.hpp>

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
#include <OSGMultiPropertySSBOChunk.h>
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
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
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

const OSG::Vec3i work_group_count(32,32,1);
const OSG::Vec3i work_group_size(16,16,1);

const std::size_t num_materials = (work_group_size.z()-1) * work_group_size.y() * work_group_size.x()
                                + (work_group_size.y()-1) * work_group_size.x()
                                + (work_group_size.x()-1)
                                + 1;
//
// Simple material data structure
//
struct Material
{
    Material()
    : ambient (0.f, 0.f, 0.f)
    , diffuse (0.f, 0.f, 0.f)
    , specular(0.f, 0.f, 0.f)
    , emissive(0.f, 0.f, 0.f)
    , opacity(1.f)
    , shininess(100.f)
    {}

    OSG::Color3f ambient;
    OSG::Color3f diffuse;
    OSG::Color3f specular;
    OSG::Color3f emissive;

    OSG::Real32  opacity;
    OSG::Real32  shininess;

    static OSG::UInt32   ambient_id;
    static OSG::UInt32   diffuse_id;
    static OSG::UInt32  specular_id;
    static OSG::UInt32  emissive_id;
    static OSG::UInt32   opacity_id;
    static OSG::UInt32 shininess_id;
};

OSG::UInt32 Material::  ambient_id = 0;
OSG::UInt32 Material::  diffuse_id = 0;
OSG::UInt32 Material:: specular_id = 0;
OSG::UInt32 Material:: emissive_id = 0;
OSG::UInt32 Material::  opacity_id = 0;
OSG::UInt32 Material::shininess_id = 0;

typedef std::vector<Material> VecMaterialsT;        // multiple materials

VecMaterialsT initialize_materials(std::size_t num) // helper to create materials
{
    VecMaterialsT mat(num);

    for (std::size_t i = 0; i < num; ++i)
    {
        mat[i].ambient   = OSG::Color3f(0.001f, 0.001f, 0.001f);
        mat[i].diffuse.setRandom();
        mat[i].specular  = OSG::Color3f(0.9f, 0.9f, 0.9f);
        mat[i].emissive  = OSG::Color3f(0.0f, 0.0f, 0.0f);
        mat[i].opacity   = 1.f;
        mat[i].shininess = 100.f;
    }

    return mat;
}

VecMaterialsT materials = initialize_materials(num_materials);    // the material database

OSG::MultiPropertySSBOChunkTransitPtr create_material_database_state(const VecMaterialsT& vMaterials)
{
    OSG::MultiPropertySSBOChunkRefPtr materialChunk = OSG::MultiPropertySSBOChunk::create();

    OSG::UInt32 vec3_id, float_id;

    vec3_id  = materialChunk->addMember(OSG::MultiPropertySSBOChunk:: VEC3_T, 4);
    float_id = materialChunk->addMember(OSG::MultiPropertySSBOChunk::FLOAT_T, 2);

    materialChunk->setUsage(GL_STATIC_DRAW);

    Material::  ambient_id = vec3_id++;
    Material::  diffuse_id = vec3_id++;
    Material:: specular_id = vec3_id++;
    Material:: emissive_id = vec3_id;

    Material::  opacity_id = float_id++;
    Material::shininess_id = float_id;

    BOOST_FOREACH(const Material& mat, vMaterials)
    {
        OSG::UInt32 idx = materialChunk->addProperty();

        materialChunk->setVec3Property (idx, Material::  ambient_id, mat.ambient);
        materialChunk->setVec3Property (idx, Material::  diffuse_id, mat.diffuse);
        materialChunk->setVec3Property (idx, Material:: specular_id, mat.specular);
        materialChunk->setVec3Property (idx, Material:: emissive_id, mat.emissive);

        materialChunk->setFloatProperty(idx, Material::  opacity_id, mat.opacity);
        materialChunk->setFloatProperty(idx, Material::shininess_id, mat.shininess);
    }

    return OSG::MultiPropertySSBOChunkTransitPtr(materialChunk);
}

void update_material_database_state(OSG::MultiPropertySSBOChunk* materialChunk, const VecMaterialsT& vMaterials)
{
    if (materialChunk)
    {
        if (materialChunk->getNumProperties() != vMaterials.size())
        {
            materialChunk->clearProperties();

            BOOST_FOREACH(const Material& mat, vMaterials)
            {
                OSG::UInt32 idx = materialChunk->addProperty();

                materialChunk->setVec3Property (idx, Material::  ambient_id, mat.ambient);
                materialChunk->setVec3Property (idx, Material::  diffuse_id, mat.diffuse);
                materialChunk->setVec3Property (idx, Material:: specular_id, mat.specular);
                materialChunk->setVec3Property (idx, Material:: emissive_id, mat.emissive);

                materialChunk->setFloatProperty(idx, Material::  opacity_id, mat.opacity);
                materialChunk->setFloatProperty(idx, Material::shininess_id, mat.shininess);
            }
        }
        else
        {
            for (OSG::UInt32 idx = 0; idx < vMaterials.size(); ++idx)
            {
                const Material& mat = vMaterials[idx];

                materialChunk->setVec3Property (idx, Material::  ambient_id, mat.ambient);
                materialChunk->setVec3Property (idx, Material::  diffuse_id, mat.diffuse);
                materialChunk->setVec3Property (idx, Material:: specular_id, mat.specular);
                materialChunk->setVec3Property (idx, Material:: emissive_id, mat.emissive);

                materialChunk->setFloatProperty(idx, Material::  opacity_id, mat.opacity);
                materialChunk->setFloatProperty(idx, Material::shininess_id, mat.shininess);
            }
        }
    }
}

OSG::SimpleSceneManagerRefPtr mgr = NULL;

OSG::MultiPropertySSBOChunkRefPtr ssbo_data_state = NULL;

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
    const OSG::UInt32 data_binding_point = 5;

    ssbo_data_state = create_material_database_state(materials);

    OSG::ChunkMaterialRefPtr data_state = OSG::ChunkMaterial::create();
    data_state->addChunk(ssbo_data_state, data_binding_point);

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

    data_state->addChunk(texImgChunk, 0);

    OSG::ShaderProgramRefPtr compShader = OSG::ShaderProgram::create();
    compShader->setShaderType(GL_COMPUTE_SHADER);
    compShader->setProgram(get_cp_program());
    compShader->addUniformVariable("destTex", 0);
    compShader->addUniformVariable("roll",    0.f);
    compShader->addShaderStorageBlock("Materials", data_binding_point);          // block binding point

    OSG::ComputeShaderChunkRefPtr compShaderChunk = OSG::ComputeShaderChunk::create();
    compShaderChunk->addComputeShader(compShader);
    compShaderChunk->setVariables(compShader->getVariables());

    compShaderAlgo->setUseMemoryBarrier(true);
    compShaderAlgo->setUseVariableWorkGroupSize(true);
    compShaderAlgo->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    compShaderAlgo->setComputeShader(compShaderChunk);
    compShaderAlgo->setDispatchConfig(work_group_count);
    compShaderAlgo->setWorkGroupSize(work_group_size);
    compShaderAlgo->setChunkMaterial(data_state);

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
            ssbo_data_state = NULL;

            releaseGLUT();

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            materials = initialize_materials(num_materials);
            update_material_database_state(ssbo_data_state, materials);
            glutPostRedisplay();
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
    std::cout << "m     : reinitialize material database" << std::endl;
}

std::string get_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 450 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_compute_variable_group_size: enable"
    << endl << ""
    << endl << "uniform float roll;"
    << endl << "uniform writeonly image2D destTex;"
    << endl << ""
    << endl << "struct Material"
    << endl << "{"
    << endl << "    vec3 ambient;"
    << endl << "    vec3 diffuse;"
    << endl << "    vec3 specular;"
    << endl << "    vec3 emissive;"
    << endl << ""
    << endl << "    float opacity;"
    << endl << "    float shininess;"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Materials"
    << endl << "{"
    << endl << "    Material material[];"
    << endl << "} materials;"
    << endl << ""
    << endl << "layout (local_size_variable) in;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Due to driver issue at the time of writing this code: The build in variable"
    << endl << "    // gl_LocalInvocationIndex is not properly set in case of a variable work group"
    << endl << "    // size specification."
    << endl << "    //"
    //<< endl << "    uint localInvocationIndex = gl_LocalInvocationIndex;"
    << endl << "    uint localInvocationIndex = gl_LocalInvocationID.z * (gl_LocalGroupSizeARB.x * gl_LocalGroupSizeARB.y)"
    << endl << "                              + gl_LocalInvocationID.y * gl_LocalGroupSizeARB.x"
    << endl << "                              + gl_LocalInvocationID.x;"
    << endl << ""
    << endl << ""
    << endl << "    ivec2   storePos = ivec2( gl_GlobalInvocationID.xy );"
    << endl << "    float  localCoef = length( vec2( ivec2(gl_LocalInvocationID.xy) - 8 ) / 8.0 );"
    << endl << "    float globalCoef = sin( float(gl_WorkGroupID.x + gl_WorkGroupID.y) * 0.1 + roll ) * 0.5;"
    << endl << ""
    << endl << "    vec4 color = vec4(materials.material[localInvocationIndex].diffuse, 0.0);"
    << endl << ""
    << endl << "    color.x -= globalCoef * localCoef;"
    << endl << "    color.y -= globalCoef * localCoef;"
    << endl << "    color.z -= globalCoef * localCoef;"
    << endl << ""
    << endl << "    imageStore(destTex, storePos, color);"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
