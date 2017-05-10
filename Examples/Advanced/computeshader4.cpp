// OpenSG Tutorial Example: ComputeShader4
//
// This example renders just the cylinder / torus animation that
// is known from many others of the simple examples. What is new
// is that the material database is filled by a compute shader.
//
// The point here is that the shader storage buffer object for
// the material database is modified by the compute shader and
// then read by the fragment shader that runs after the compute
// shader.
//

#include <sstream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

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
#include <OSGGLEXT.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGShaderStorageBufferObjChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGAlgorithmComputeElement.h>
#include <OSGComputeShaderAlgorithm.h>
#include <OSGComputeShaderChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramVariables.h>

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
#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGShaderStorageBufferObjChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGAlgorithmComputeElement.h>
#include <OpenSG/OSGComputeShaderAlgorithm.h>
#include <OpenSG/OSGComputeShaderChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramVariables.h>
#endif

const OSG::Vec3i work_group_count(32,32,1);
const OSG::Vec3i work_group_size(16,16,1);

const OSG::UInt32 num_materials = (work_group_size.z()-1) * work_group_size.y() * work_group_size.x()
                                + (work_group_size.y()-1) * work_group_size.x()
                                + (work_group_size.x()-1)
                                + 1;
//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// simple light data structure
//
struct Light
{
    enum Type
    {
        directional_light = 0,
        point_light,
        spot_light,
        no_light
    };

    Light() 
    : position(0.f, 0.f, 0.f)
    , spot_direction(0.f, 1.f, 0.f)
    , Ia(1.f, 1.f, 1.f)
    , Id(1.f, 1.f, 1.f)
    , Is(1.f, 1.f, 1.f)
    , attenuation(1.f, 0.f, 0.f)
    , spot_cos_cutoff(cosf(45.f))
    , spot_exponent(1.f)
    , type(no_light)
    {}

    static Light create_light(Type e)
    {
        Light l;
        l.type = e;

        switch (e) {
            case directional_light:                                          l.spot_direction = OSG::Vec3f(1.f, 0.f, 0.f);
                break;
            case       point_light: l.position = OSG::Pnt3f(0.f, 0.2f, 0.f);
                break;
            case        spot_light: l.position = OSG::Pnt3f(0.f, 0.2f, 0.f); l.spot_direction = OSG::Pnt3f(0.f, 0.f, 0.f) - l.position;
                break;
            default:
                break;
        }
        return l;
    }

    OSG::Pnt3f   position;           // in object space
    OSG::Vec3f   spot_direction;     // in object space, also used for dir of directional lights (see shader code)
    OSG::Color3f Ia;                 // ambient  max. Intensity
    OSG::Color3f Id;                 // diffuse  max. Intensity
    OSG::Color3f Is;                 // specular max. Intensity

    OSG::Vec3f   attenuation;        // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0
    OSG::Real32  spot_cos_cutoff;    // cosine cut of angle
    OSG::Real32  spot_exponent;      // [0-128]
    OSG::Int32   type;               // directional_light, point_light, spot_light, no_light
};

typedef std::vector<Light>       VecLightsT;        // multiple lights

const std::size_t num_lights = 1;                   // simple example with just one light

VecLightsT initialize_lights()         // helper to create lights
{
    VecLightsT lights;

    lights.push_back(Light::create_light(Light::point_light));

    assert(lights.size() == num_lights);

    return lights;
}

VecLightsT lights = initialize_lights();    // the lights


//
// Simple material data structure
//
struct Material
{
    Material()
    : ambient (0.f, 0.f, 0.f)
    , diffuse (1.f, 1.f, 1.f)
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
};

typedef std::vector<Material> VecMaterialsT;        // multiple materials

VecMaterialsT initialize_materials(std::size_t num) // helper to create materials
{
    VecMaterialsT materials;
    materials.resize(num);

    return materials;
}

VecMaterialsT materials = initialize_materials(num_materials);  // the material database


//
// Simple geometry state data structure
//
struct GeomState
{
    GeomState()
    : material_index(0)
    {}

    OSG::UInt32  material_index;
};

//
// transform point from world space to eye space
//
OSG::Pnt3f transform_to_eye_space(const OSG::Pnt3f& p)
{
    if (!mgr || !mgr->getWindow() || mgr->getWindow()->getMFPort()->size() == 0)
        return p;

    OSG::Viewport* pPort = mgr->getWindow()->getPort(0);

    OSG::Pnt3f p_es;

    OSG::Matrix view;
    OSG::Int16 width  = pPort->calcPixelWidth();
    OSG::Int16 height = pPort->calcPixelHeight();

    pPort->getCamera()->getViewing(view, width, height);

    view.multFull( p, p_es);

    return p_es;
}

//
// transform vector from world space to eye space
//
OSG::Vec3f transform_to_eye_space(const OSG::Vec3f& v)
{
    if (!mgr || !mgr->getWindow() || mgr->getWindow()->getMFPort()->size() == 0)
        return v;

    OSG::Viewport* pPort = mgr->getWindow()->getPort(0);

    OSG::Vec3f v_es;

    OSG::Matrix view;
    OSG::Int16 width  = pPort->calcPixelWidth();
    OSG::Int16 height = pPort->calcPixelHeight();

    pPort->getCamera()->getViewing(view, width, height);

    view.multFull( v, v_es);

    return v_es;
}

//
// The light state
//
void update_light_state(OSG::ShaderStorageBufferObjChunk* ssbo, const VecLightsT& vLights)
{
    if (ssbo) {
        for (std::size_t i = 0; i < vLights.size(); ++i) {
            std::stringstream stream;
            stream << "Lights.light[" << i << "]." << std::flush;
            std::string name;

            OSG::Pnt3f position_es       = transform_to_eye_space(vLights[i].position);
            OSG::Vec3f spot_direction_es = transform_to_eye_space(vLights[i].spot_direction);

            name = stream.str() + "position";           ssbo->setVec3 (name,  position_es);
            name = stream.str() + "spot_direction";     ssbo->setVec3 (name,  spot_direction_es);
            name = stream.str() + "Ia";                 ssbo->setVec3 (name,  vLights[i].Ia);
            name = stream.str() + "Id";                 ssbo->setVec3 (name,  vLights[i].Id);
            name = stream.str() + "Is";                 ssbo->setVec3 (name,  vLights[i].Is);
            name = stream.str() + "attenuation";        ssbo->setVec3 (name,  vLights[i].attenuation);
            name = stream.str() + "spot_cos_cutoff";    ssbo->setFloat(name,  vLights[i].spot_cos_cutoff);
            name = stream.str() + "spot_exponent";      ssbo->setFloat(name,  vLights[i].spot_exponent);
            name = stream.str() + "type";               ssbo->setInt  (name,  vLights[i].type);
        }
    }
}

OSG::ShaderStorageBufferObjChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::ShaderStorageBufferObjChunkRefPtr ssbo = OSG::ShaderStorageBufferObjChunk::create();

    ssbo->setBlockName("Lights");
    ssbo->setUsage(GL_STREAM_DRAW);

    for (std::size_t i = 0; i < vLights.size(); ++i) {
        std::stringstream stream;
        stream << "Lights.light[" << i << "]." << std::flush;
        std::string name;

        name = stream.str() + "position";           ssbo->addVec3 (name);
        name = stream.str() + "spot_direction";     ssbo->addVec3 (name);
        name = stream.str() + "Ia";                 ssbo->addVec3 (name);
        name = stream.str() + "Id";                 ssbo->addVec3 (name);
        name = stream.str() + "Is";                 ssbo->addVec3 (name);
        name = stream.str() + "attenuation";        ssbo->addVec3 (name);
        name = stream.str() + "spot_cos_cutoff";    ssbo->addFloat(name);
        name = stream.str() + "spot_exponent";      ssbo->addFloat(name);
        name = stream.str() + "type";               ssbo->addInt  (name);
    }

    update_light_state(ssbo, vLights);

    return OSG::ShaderStorageBufferObjChunkTransitPtr(ssbo);
}

//
// The material state
//
void update_material_database_state(OSG::ShaderStorageBufferObjChunk* ssbo, const VecMaterialsT& vMaterials)
{
    if (ssbo) {
        for (std::size_t i = 0; i < vMaterials.size(); ++i) {
            std::stringstream stream;
            stream << "Materials.material[" << i << "]." << std::flush;
            std::string name;

            name = stream.str() + "ambient";    ssbo->setVec3 (name, vMaterials[i].ambient);
            name = stream.str() + "diffuse";    ssbo->setVec3 (name, vMaterials[i].diffuse);
            name = stream.str() + "specular";   ssbo->setVec3 (name, vMaterials[i].specular);
            name = stream.str() + "emissive";   ssbo->setVec3 (name, vMaterials[i].emissive);
            name = stream.str() + "opacity";    ssbo->setFloat(name, vMaterials[i].opacity);
            name = stream.str() + "shininess";  ssbo->setFloat(name, vMaterials[i].shininess);
        }
    }
}

OSG::ShaderStorageBufferObjChunkTransitPtr create_material_database_state(const VecMaterialsT& vMaterials)
{
    OSG::ShaderStorageBufferObjChunkRefPtr ssbo = OSG::ShaderStorageBufferObjChunk::create();

    ssbo->setBlockName("Materials");
    ssbo->setUsage(GL_STATIC_DRAW);

    for (std::size_t i = 0; i < vMaterials.size(); ++i) {
        std::stringstream stream;
        stream << "Materials.material[" << i << "]." << std::flush;
        std::string name;

        name = stream.str() + "ambient";    ssbo->addVec3 (name);
        name = stream.str() + "diffuse";    ssbo->addVec3 (name);
        name = stream.str() + "specular";   ssbo->addVec3 (name);
        name = stream.str() + "emissive";   ssbo->addVec3 (name);
        name = stream.str() + "opacity";    ssbo->addFloat(name);
        name = stream.str() + "shininess";  ssbo->addFloat(name);
    }

    update_material_database_state(ssbo, vMaterials);

    return OSG::ShaderStorageBufferObjChunkTransitPtr(ssbo);
}

//
// The geometry material state
//
void update_geometry_material_state(OSG::ShaderStorageBufferObjChunk* ssbo, const GeomState& geom_state)
{
    if (ssbo)
    {
        ssbo->setInt("GeomState.material_index", geom_state.material_index);
    }
}

OSG::ShaderStorageBufferObjChunkTransitPtr create_geometry_material_state(const GeomState& geom_state)
{
    OSG::ShaderStorageBufferObjChunkRefPtr ssbo = OSG::ShaderStorageBufferObjChunk::create();

    ssbo->setBlockName("GeomState");
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    ssbo->addInt("GeomState.material_index");

    update_geometry_material_state(ssbo, geom_state);

    return OSG::ShaderStorageBufferObjChunkTransitPtr(ssbo);
}

//
// compute, vertex and fragment shader program.
//
std::string get_cp_program();
std::string get_vp_program();
std::string get_fp_program();

const OSG::UInt32  data_binding_point = 1;
const OSG::UInt32 light_binding_point = 2;
const OSG::UInt32  geom_binding_point = 3;

//
// random number generator
//
boost::random::mt19937  generator;
boost::random::uniform_int_distribution<> dist(0, num_materials-1);

//
// a separate transformation for every object
//
OSG::TransformRefPtr cyltrans, tortrans;

//
// Shader storage buffer objects corresponding to transient shader blocks
//
OSG::ShaderStorageBufferObjChunkRefPtr ssbo_material_database = NULL;
OSG::ShaderStorageBufferObjChunkRefPtr ssbo_light_state       = NULL;
OSG::ShaderStorageBufferObjChunkRefPtr ssbo_geom_state_1      = NULL;
OSG::ShaderStorageBufferObjChunkRefPtr ssbo_geom_state_2      = NULL;

//
// The computation core that is responsible for generating matrial database content
//
OSG::AlgorithmComputeElementTransitPtr createComputation()
{
    OSG::ChunkMaterialRefPtr data_state = OSG::ChunkMaterial::create();
    data_state->addChunk(ssbo_material_database, data_binding_point);

    OSG::ShaderProgramRefPtr compShader = OSG::ShaderProgram::create();
    compShader->setShaderType(GL_COMPUTE_SHADER);
    compShader->setProgram(get_cp_program());
    compShader->addShaderStorageBlock("Materials", data_binding_point);          // block binding point

    OSG::ComputeShaderChunkRefPtr compShaderChunk = OSG::ComputeShaderChunk::create();
    compShaderChunk->addComputeShader(compShader);
    compShaderChunk->setVariables(compShader->getVariables());

    OSG::ComputeShaderAlgorithmRefPtr compShaderAlgo = OSG::ComputeShaderAlgorithm::create();
    compShaderAlgo->setUseMemoryBarrier(true);
    compShaderAlgo->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    compShaderAlgo->setComputeShader(compShaderChunk);
    compShaderAlgo->setDispatchConfig(work_group_count);
    compShaderAlgo->setChunkMaterial(data_state);

    OSG::AlgorithmComputeElementRefPtr algoCompElement = OSG::AlgorithmComputeElement::create();
    algoCompElement->setAlgorithm(compShaderAlgo);

    return OSG::AlgorithmComputeElementTransitPtr(algoCompElement);
}

//
// The scene to be rendered
//
OSG::NodeTransitPtr createScene()
{
    OSG::NodeRefPtr scene = OSG::Node::create();
        
    // The cylinder and its transformation
    OSG::NodeRefPtr     cyl    = OSG::Node::create();
    OSG::GeometryRefPtr cylgeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, 
                                                        true, true, true );
        
    cyl->setCore(cylgeo);
    
    cyltrans = OSG::Transform::create();
    
    OSG::NodeRefPtr cyltransnode = OSG::Node::create();
    cyltransnode->setCore (cyltrans);
    cyltransnode->addChild(cyl     );
        
    // add it to the scene
    scene->addChild(cyltransnode);
        
    // The torus and its transformation
    OSG::NodeRefPtr     torus    = OSG::Node::create();
    OSG::GeometryRefPtr torusgeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );
        
    torus->setCore(torusgeo);
            
    tortrans = OSG::Transform::create();
    
    OSG::NodeRefPtr tortransnode = OSG::Node::create();
    tortransnode->setCore (tortrans);
    tortransnode->addChild(torus   );
        
    // add it to the scene
    scene->addChild(tortransnode);

    //
    // create the shader program
    //
    OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
    OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
    OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

    vertShader->setProgram(get_vp_program());
    fragShader->setProgram(get_fp_program());

    //
    // binding the unifrom block to a buffer binding point can be performed 
    // either by calling the shaders's addShaderStorageBlock method or by
    // adding a 'shader storage block' variable to a ShaderProgramVariableChunk.
    // In the following we use both variants for illustration.
    //
    fragShader->addShaderStorageBlock("Materials",  data_binding_point);    // block binding point
    fragShader->addShaderStorageBlock("Lights",    light_binding_point);    // block binding point

    //
    // The following is replaced by adding ShaderProgramVariableChunk objects
    // to the chunk material. See below...
    //
    // fragShader->addShaderStorageBlock("GeomState", 3);    // block binding point

    prog_chunk->addShader(vertShader);
    prog_chunk->addShader(fragShader);

    //
    // create shader storage buffer object for the light state
    //
    ssbo_light_state = create_light_state(lights);

    OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
    polygon_chunk->setFrontMode(GL_FILL);
    polygon_chunk->setBackMode(GL_FILL);
    polygon_chunk->setCullFace(GL_NONE);

    OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
    depth_chunk->setEnable(true);

    OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
    prog_state->addChunk(ssbo_material_database,  data_binding_point);  // buffer binding point 1
    prog_state->addChunk(ssbo_light_state,       light_binding_point);  // buffer binding point 2
    prog_state->addChunk(prog_chunk);
    prog_state->addChunk(polygon_chunk);
    prog_state->addChunk(depth_chunk);

    OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
    shader_var_chunk->addShaderStorageBlock("GeomState", geom_binding_point);

    GeomState geom1; geom1.material_index = dist(generator);
    OSG::ChunkMaterialRefPtr geom1_state = OSG::ChunkMaterial::create();
    ssbo_geom_state_1 = create_geometry_material_state(geom1);
    geom1_state->addChunk(ssbo_geom_state_1, geom_binding_point);     // buffer binding point 3
    geom1_state->addChunk(shader_var_chunk);        // block binding point

    GeomState geom2; geom2.material_index = dist(generator);
    OSG::ChunkMaterialRefPtr geom2_state = OSG::ChunkMaterial::create();
    ssbo_geom_state_2 = create_geometry_material_state(geom2);
    geom2_state->addChunk(ssbo_geom_state_2, geom_binding_point);     // buffer binding point 3
    geom2_state->addChunk(shader_var_chunk);        // block binding point
       
    cylgeo  ->setMaterial(geom1_state);
    torusgeo->setMaterial(geom2_state);

    OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
    mgrp->setMaterial(prog_state);
    scene->setCore(mgrp);

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

        //
        // create shader storage buffer object for the material database
        //
        ssbo_material_database = create_material_database_state(materials);

        OSG::NodeRefPtr root = OSG::makeNodeFor(createComputation()); // OSG::Group::create());

        root->addChild(createScene());

        mgr->setRoot(root);

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
    // light spot direction and light position must be provided in eye space
    update_light_state(ssbo_light_state, lights);

    // create the matrix
    OSG::Matrix m;
    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    // set the transforms' matrices
    m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                   OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

    cyltrans->setMatrix(m);
    
    m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                   OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

    tortrans->setMatrix(m);

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
        case 27:    
        {
            // clean up global variables
            cyltrans = NULL;
            tortrans = NULL;
            mgr      = NULL;

            ssbo_material_database = NULL;
            ssbo_light_state       = NULL;
            ssbo_geom_state_1      = NULL;
            ssbo_geom_state_2      = NULL;

            releaseGLUT();

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            GeomState geom1; geom1.material_index = dist(generator);
            GeomState geom2; geom2.material_index = dist(generator);

            update_geometry_material_state(ssbo_geom_state_1, geom1);
            update_geometry_material_state(ssbo_geom_state_2, geom2);

            glutPostRedisplay();
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
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
    std::cout << "m     : change object colors" << std::endl;
}

//
// compute shader program.
//
std::string get_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "const int num_materials = " << num_materials << ";"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
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
    << endl << "    Material material[" << num_materials << "];"
    << endl << "} materials;"
    << endl << ""
    << endl << "uint hash( uint x ) {"
    << endl << "    x += ( x << 10u );"
    << endl << "    x ^= ( x >>  6u );"
    << endl << "    x += ( x <<  3u );"
    << endl << "    x ^= ( x >> 11u );"
    << endl << "    x += ( x << 15u );"
    << endl << "    return x;"
    << endl << "}"
    << endl << ""
    << endl << "float random( float f ) {"
    << endl << "    const uint mantissaMask = 0x007FFFFFu;"
    << endl << "    const uint one          = 0x3F800000u;"
    << endl << ""
    << endl << "    uint h = hash( floatBitsToUint( f ) );"
    << endl << "    h &= mantissaMask;"
    << endl << "    h |= one;"
    << endl << ""
    << endl << "    float  r2 = uintBitsToFloat( h );"
    << endl << "    return r2 - 1.0;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    vec3 color;"
    << endl << ""
    << endl << "    if (gl_LocalInvocationIndex >= " << num_materials << ")"
    << endl << "        color = vec3(1.0, 0.0, 0.0);"
    << endl << "    else"
    << endl << "    {"
    << endl << "        float value = length( vec2( ivec2(gl_LocalInvocationID.xy) - 8 ) / 8.0 );"
    << endl << "        float r = random(value);"
    << endl << "        float g = random(2*value);"
    << endl << "        float b = random(7*value);"
    << endl << "        color = vec3(r, g, b);"
    << endl << "    }"
    << endl << ""
    << endl << "    materials.material[gl_LocalInvocationIndex].diffuse = color;"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

//
// vertex shader program.
//
std::string get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
    << endl << "smooth out vec3 vNormalES;        // eye space normal"
    << endl << "smooth out vec3 vPositionES;      // eye space position"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // multiply the object space vertex position with the modelview matrix "
    << endl << "    // to get the eye space vertex position"
    << endl << "    //"
    << endl << "    vPositionES = (gl_ModelViewMatrix * gl_Vertex).xyz;"
    << endl << ""
    << endl << "    //"
    << endl << "    // multiply the object space normal with the normal matrix (transpose of the inverse "
    << endl << "    // model view matrix) to get the eye space normal"
    << endl << "    //"
    << endl << "    vNormalES = gl_NormalMatrix * gl_Normal;"
    << endl << ""
    << endl << "    //"
    << endl << "    // multiply the combiend modelview projection matrix with the object space vertex"
    << endl << "    // position to get the clip space position"
    << endl << "    //"
    << endl << "    gl_Position = ftransform();"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
    << endl << "smooth in vec3 vNormalES;         // eye space normal"
    << endl << "smooth in vec3 vPositionES;       // eye space position"
    << endl << ""
    << endl << "const int num_lights    = " << num_lights    << ";"
    << endl << "const int num_materials = " << num_materials << ";"
    << endl << ""
    << endl << "const int directional_light = 0;"
    << endl << "const int point_light       = 1;"
    << endl << "const int spot_light        = 2;"
    << endl << "const int no_light          = 3;"
    << endl << ""
    << endl << "struct Light"
    << endl << "{"
    << endl << "    vec3 position;          // in eye space"
    << endl << "    vec3 spot_direction;    // in eye space"
    << endl << ""
    << endl << "    vec3 Ia;                // ambient  max. Intensity"
    << endl << "    vec3 Id;                // diffuse  max. Intensity"
    << endl << "    vec3 Is;                // specular max. Intensity"
    << endl << ""
    << endl << "    vec3 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0"
    << endl << "    "
    << endl << "    float spot_cos_cutoff;  // cosine cut of angle"
    << endl << ""
    << endl << "    float spot_exponent;    // [0-128]"
    << endl << "    int  type;              // directional_light, point_light, spot_light, no_light"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Lights"
    << endl << "{"
    << endl << "    Light light[num_lights];"
    << endl << "} lights;"
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
    << endl << "    Material material[num_materials];"
    << endl << "} materials;"
    << endl << ""
    << endl << ""
    << endl << "layout (std430) buffer GeomState"
    << endl << "{"
    << endl << "    int material_index;"
    << endl << "} geom_state;"
    << endl << ""
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "//"
    << endl << "// directional light contribution"
    << endl << "//"
    << endl << "vec3 directionalLight("
    << endl << "    in int i,   // light identifier, i.e. current light"
    << endl << "    in int j,   // material identifier"
    << endl << "    in vec3 n,  // vertex normal in eye space"
    << endl << "    in vec3 v)  // view direction in eye space"
    << endl << "{"
    << endl << "    if (lights.light[i].type != directional_light)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the light direction in eye space"
    << endl << "    //"
    << endl << "    vec3 l = -lights.light[i].spot_direction;    // we carry the directional light direction in the spot_direction slot"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l + v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << ""
    << endl << "    float m = materials.material[j].shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    return materials.material[j].emissive "
    << endl << "         + lights.light[i].Ia * materials.material[j].ambient "
    << endl << "         + lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI"
    << endl << "         + lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// point light contribution"
    << endl << "//"
    << endl << "vec3 pointLight("
    << endl << "    in int i,   // light identifier, i.e. current light"
    << endl << "    in int j,   // material identifier"
    << endl << "    in vec3 n,  // vertex normal in eye space"
    << endl << "    in vec3 v,  // view direction in eye space"
    << endl << "    in vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (lights.light[i].type != point_light)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec3  l = vec3(lights.light[i].position) - p;    // direction from surface to light position"
    << endl << "    float d = length(l);                             // distance from surface to light source"
    << endl << "    l = normalize(l);                                // normalized direction from surface to light position"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l + v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << ""
    << endl << "    float m = materials.material[j].shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Compute attenuation"
    << endl << "    //"
    << endl << "    float attenuation = 1.0 / (lights.light[i].attenuation.x + "
    << endl << "                              (lights.light[i].attenuation.y * d) + "
    << endl << "                              (lights.light[i].attenuation.z * d * d));"
    << endl << ""
    << endl << "    attenuation = clamp(attenuation, 0.0, 1.0);"
    << endl << ""
    << endl << "    return materials.material[j].emissive "
    << endl << "         + attenuation * lights.light[i].Ia * materials.material[j].ambient "
    << endl << "         + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI"
    << endl << "         + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// spot light contribution"
    << endl << "//"
    << endl << "vec3 spotLight("
    << endl << "    in int i,   // light identifier, i.e. current light"
    << endl << "    in int j,   // material identifier"
    << endl << "    in vec3 n,  // vertex normal in eye space"
    << endl << "    in vec3 v,  // view direction in eye space"
    << endl << "    in vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (lights.light[i].type != spot_light)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec3  l = vec3(lights.light[i].position) - p;   // direction from surface to light position"
    << endl << "    float d = length(l);                            // distance from surface to light source"
    << endl << "    l = normalize(l);                               // normalized direction from surface to light position"
    << endl << "    "
    << endl << "    vec3 s = lights.light[i].spot_direction;        // spot direction"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l + v);"
    << endl << ""
    << endl << "    float n_dot_l = max(0.0, dot(n, l));"
    << endl << "    float n_dot_h = max(0.0, dot(n, h));"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << ""
    << endl << "    float m = materials.material[j].shininess;"
    << endl << ""
    << endl << "    float pf;           // power factor"
    << endl << ""
    << endl << "    if (n_dot_l == 0.0)"
    << endl << "       pf = 0.0;"
    << endl << "    else"
    << endl << "       pf = pow(n_dot_h, m);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Compute attenuation"
    << endl << "    //"
    << endl << "    float attenuation = 1.0 / (lights.light[i].attenuation.x + "
    << endl << "                              (lights.light[i].attenuation.y * d) + "
    << endl << "                              (lights.light[i].attenuation.z * d * d));"
    << endl << ""
    << endl << "    attenuation = clamp(attenuation, 0.0, 1.0);"
    << endl << ""
    << endl << "    if (l_dot_s < lights.light[i].spot_cos_cutoff) "
    << endl << "        attenuation = 0.0;"
    << endl << "    else"
    << endl << "        attenuation *= pow(l_dot_s, lights.light[i].spot_exponent);"
    << endl << ""
    << endl << "    return materials.material[j].emissive "
    << endl << "         + attenuation * lights.light[i].Ia * materials.material[j].ambient "
    << endl << "         + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI"
    << endl << "         + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // normalize the eye space normal"
    << endl << "    //"
    << endl << "    vec3 N = normalize(vNormalES);"
    << endl << ""
    << endl << "    //"
    << endl << "    // get the view vector and normalize it"
    << endl << "    //"
    << endl << "    vec3 V = normalize(cCameraPositionES - vPositionES);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Integrate over all lights: Any unused light does not contribute and each light"
    << endl << "    // contribute either from the directional light, the point light or the spot light."
    << endl << "    //"
    << endl << "    vec3 color = vec3(0.0, 0.0, 0.0);"
    << endl << "    for (int i = 0; i < num_lights; ++i) {"
    << endl << "        color += directionalLight(i, geom_state.material_index, N, V) "
    << endl << "              +        pointLight(i, geom_state.material_index, N, V, vPositionES) "
    << endl << "              +         spotLight(i, geom_state.material_index, N, V, vPositionES);"
    << endl << "    }"
    << endl << "    vFragColor = vec4(color, materials.material[geom_state.material_index  ].opacity);"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
