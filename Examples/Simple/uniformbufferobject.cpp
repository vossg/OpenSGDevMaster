// OpenSG Tutorial Example: UniformBufferObject
//
// This example shows how to create a shader uniform block and binding it 
// to a uniform buffer object.
//
// The example does use the UniformBufferObjChunk which allows the host
// application to provide the uniform block member values directly to 
// the chunk. The layout of the uniform block is determined by the 
// shader code. Any of the layout values of the specification (shared, 
// packed, std140) are allowed.
// It is however, important the the order and the cardinality of the
// members is matched exactly.
//
// Internally, the shader uniform block is queried for the offsets,
// array and matrix strides of the block variables.
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
#include <OSGUniformBufferObjChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>

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
#include <OpenSG/OSGUniformBufferObjChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#endif

//
// USE_TEST_FP_SHADER
// ------------------
// Activate a test mode that does test the material and light at index 0,
// respectively, against specific values set by the application. If all
// values are read correctly in the shader the geometry is colored in green.
// Otherwise the geometry is colored red indicating failure.
//
//#define USE_TEST_FP_SHADER

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

    lights.push_back(Light::create_light(Light::directional_light));

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
};

typedef std::vector<Material> VecMaterialsT;        // multiple materials

VecMaterialsT initialize_materials(std::size_t num) // helper to create materials
{
    VecMaterialsT materials;

    for (std::size_t i = 0; i < num; ++i)
    {
        Material m;

        m.ambient   = OSG::Color3f(0.1f, 0.1f, 0.1f);
        m.diffuse.setRandom();
        m.specular  = OSG::Color3f(0.9f, 0.9f, 0.9f);
        m.emissive  = OSG::Color3f(0.0f, 0.0f, 0.0f);
        m.opacity   = 1.f;
        m.shininess = 80.f;

        materials.push_back(m);
    }

    return materials;
}

const std::size_t num_materials = 100;                            // any numnber of materials
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
OSG::Pnt3f transform_to_eye_space(const OSG::Pnt3f& p, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
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
OSG::Vec3f transform_to_eye_space(const OSG::Vec3f& v, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
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
void update_light_state(OSG::UniformBufferObjChunk* ubo, const VecLightsT& vLights)
{
    if (ubo) {
        for (std::size_t i = 0; i < vLights.size(); ++i) {
            std::stringstream stream;
            stream << "Lights.light[" << i << "]." << std::flush;
            std::string name;
#ifndef USE_TEST_FP_SHADER
            OSG::Pnt3f position_es       = transform_to_eye_space(vLights[i].position,       mgr);
            OSG::Vec3f spot_direction_es = transform_to_eye_space(vLights[i].spot_direction, mgr);

            name = stream.str() + "position";           ubo->setVec3 (name,  position_es);
            name = stream.str() + "spot_direction";     ubo->setVec3 (name,  spot_direction_es);
            name = stream.str() + "Ia";                 ubo->setVec3 (name,  vLights[i].Ia);
            name = stream.str() + "Id";                 ubo->setVec3 (name,  vLights[i].Id);
            name = stream.str() + "Is";                 ubo->setVec3 (name,  vLights[i].Is);
            name = stream.str() + "attenuation";        ubo->setVec3 (name,  vLights[i].attenuation);
            name = stream.str() + "spot_cos_cutoff";    ubo->setFloat(name,  vLights[i].spot_cos_cutoff);
            name = stream.str() + "spot_exponent";      ubo->setFloat(name,  vLights[i].spot_exponent);
            name = stream.str() + "type";               ubo->setInt  (name,  vLights[i].type);
#else
            name = stream.str() + "position";           ubo->setVec3 (name,  OSG::Pnt3f(1.1f, 2.2f, 3.3f));
            name = stream.str() + "spot_direction";     ubo->setVec3 (name,  OSG::Vec3f(4.4f, 5.5f, 6.6f));
            name = stream.str() + "Ia";                 ubo->setVec3 (name,  OSG::Color3f(0.2f, 0.2f, 0.2f));
            name = stream.str() + "Id";                 ubo->setVec3 (name,  OSG::Color3f(0.4f, 0.4f, 0.4f));
            name = stream.str() + "Is";                 ubo->setVec3 (name,  OSG::Color3f(0.6f, 0.6f, 0.6f));
            name = stream.str() + "attenuation";        ubo->setVec3 (name,  OSG::Vec3f(0.8f, 0.8f, 0.8f));
            name = stream.str() + "spot_cos_cutoff";    ubo->setFloat(name,  0.8f);
            name = stream.str() + "spot_exponent";      ubo->setFloat(name,  12.3f);
            name = stream.str() + "type";               ubo->setInt  (name,  Light::point_light);
#endif
        }
    }
}

OSG::UniformBufferObjChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::UniformBufferObjChunkRefPtr ubo = OSG::UniformBufferObjChunk::create();

    ubo->setBlockName("Lights");
    ubo->setUsage(GL_STREAM_DRAW);

    for (std::size_t i = 0; i < vLights.size(); ++i) {
        std::stringstream stream;
        stream << "Lights.light[" << i << "]." << std::flush;
        std::string name;

        name = stream.str() + "position";           ubo->addVec3 (name);
        name = stream.str() + "spot_direction";     ubo->addVec3 (name);
        name = stream.str() + "Ia";                 ubo->addVec3 (name);
        name = stream.str() + "Id";                 ubo->addVec3 (name);
        name = stream.str() + "Is";                 ubo->addVec3 (name);
        name = stream.str() + "attenuation";        ubo->addVec3 (name);
        name = stream.str() + "spot_cos_cutoff";    ubo->addFloat(name);
        name = stream.str() + "spot_exponent";      ubo->addFloat(name);
        name = stream.str() + "type";               ubo->addInt  (name);
    }

    update_light_state(ubo, vLights);

    return OSG::UniformBufferObjChunkTransitPtr(ubo);
}

//
// The material state
//
void update_material_database_state(OSG::UniformBufferObjChunk* ubo, const VecMaterialsT& vMaterials)
{
    if (ubo) {
        for (std::size_t i = 0; i < vMaterials.size(); ++i) {
            std::stringstream stream;
            stream << "Materials.material[" << i << "]." << std::flush;
            std::string name;
#ifndef USE_TEST_FP_SHADER
            name = stream.str() + "ambient";    ubo->setVec3 (name, vMaterials[i].ambient);
            name = stream.str() + "diffuse";    ubo->setVec3 (name, vMaterials[i].diffuse);
            name = stream.str() + "specular";   ubo->setVec3 (name, vMaterials[i].specular);
            name = stream.str() + "emissive";   ubo->setVec3 (name, vMaterials[i].emissive);
            name = stream.str() + "opacity";    ubo->setFloat(name, vMaterials[i].opacity);
            name = stream.str() + "shininess";  ubo->setFloat(name, vMaterials[i].shininess);
#else
            name = stream.str() + "ambient";    ubo->setVec3 (name, OSG::Color3f(0.1f,0.2f,0.3f));
            name = stream.str() + "diffuse";    ubo->setVec3 (name, OSG::Color3f(0.2f,0.4f,0.6f));
            name = stream.str() + "specular";   ubo->setVec3 (name, OSG::Color3f(0.4f,0.6f,0.8f));
            name = stream.str() + "emissive";   ubo->setVec3 (name, OSG::Color3f(0.6f,0.8f,1.0f));
            name = stream.str() + "opacity";    ubo->setFloat(name, 0.7f);
            name = stream.str() + "shininess";  ubo->setFloat(name, 25.4f);
#endif
        }
    }
}

OSG::UniformBufferObjChunkTransitPtr create_material_database_state(const VecMaterialsT& vMaterials)
{
    OSG::UniformBufferObjChunkRefPtr ubo = OSG::UniformBufferObjChunk::create();

    ubo->setBlockName("Materials");
    ubo->setUsage(GL_STATIC_DRAW);

    for (std::size_t i = 0; i < vMaterials.size(); ++i) {
        std::stringstream stream;
        stream << "Materials.material[" << i << "]." << std::flush;
        std::string name;

        name = stream.str() + "ambient";    ubo->addVec3 (name);
        name = stream.str() + "diffuse";    ubo->addVec3 (name);
        name = stream.str() + "specular";   ubo->addVec3 (name);
        name = stream.str() + "emissive";   ubo->addVec3 (name);
        name = stream.str() + "opacity";    ubo->addFloat(name);
        name = stream.str() + "shininess";  ubo->addFloat(name);
    }

    update_material_database_state(ubo, vMaterials);

    return OSG::UniformBufferObjChunkTransitPtr(ubo);
}

//
// The geometry material state
//
void update_geometry_material_state(OSG::UniformBufferObjChunk* ubo, const GeomState& geom_state)
{
    if (ubo) {
#ifndef USE_TEST_FP_SHADER
        ubo->setInt("GeomState.material_index", geom_state.material_index);
#else
        ubo->setInt("GeomState.material_index", 7);
#endif
    }
}

OSG::UniformBufferObjChunkTransitPtr create_geometry_material_state(const GeomState& geom_state)
{
    OSG::UniformBufferObjChunkRefPtr ubo = OSG::UniformBufferObjChunk::create();

    ubo->setBlockName("GeomState");
    ubo->setUsage(GL_DYNAMIC_DRAW);

    ubo->addInt("GeomState.material_index");

    update_geometry_material_state(ubo, geom_state);

    return OSG::UniformBufferObjChunkTransitPtr(ubo);
}

//
// vertex shader program.
//
std::string get_vp_program();

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program();

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
// Uniform buffer objects corresponding to transient shader blocks
//
OSG::UniformBufferObjChunkRefPtr ubo_light_state  = NULL;
OSG::UniformBufferObjChunkRefPtr ubo_geom_state_1 = NULL;
OSG::UniformBufferObjChunkRefPtr ubo_geom_state_2 = NULL;

//
// forward declaration so we can have the interesting stuff upfront
//
int setupGLUT(int *argc, char *argv[]);

//
// redraw the window
//
void display(void)
{
    // light spot direction and light position must be provided in eye space
    update_light_state(ubo_light_state, lights);

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
// Initialize GLUT & OpenSG and set up the scene
//
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
    
        // create the SimpleSceneManager helper
        mgr = OSG::SimpleSceneManager::create();
        mgr->setWindow(gwin);

        // create a pretty simple graph: a Group with two Transforms as children,
        // each of which carries a single Geometry.
        
        // The scene
        
        OSG::NodeRefPtr  scene = OSG::Node::create();
        
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
        // either by calling the shaders's addUniformBlock method or by
        // adding a 'uniform block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        fragShader->addUniformBlock("Materials", 1);    // block binding point
        fragShader->addUniformBlock("Lights",    2);    // block binding point

        //
        // The following is replaced by adding ShaderProgramVariableChunk objects
        // to the chunk material. See below...
        //
        // fragShader->addUniformBlock("GeomState", 3);    // block binding point

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        //
        // create uniform buffer objects and corresponding materials
        //
        OSG::UniformBufferObjChunkRefPtr ubo_material_database = create_material_database_state(materials);
                                         ubo_light_state       = create_light_state(lights);

        OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
        polygon_chunk->setFrontMode(GL_FILL);
        polygon_chunk->setBackMode(GL_FILL);
        polygon_chunk->setCullFace(GL_NONE);

        OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
        depth_chunk->setEnable(true);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(ubo_material_database, 1);  // buffer binding point 1
        prog_state->addChunk(ubo_light_state,       2);  // buffer binding point 2
        prog_state->addChunk(prog_chunk);
        prog_state->addChunk(polygon_chunk);
        prog_state->addChunk(depth_chunk);

        OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
        shader_var_chunk->addUniformBlock("GeomState", 3);

        GeomState geom1; geom1.material_index = dist(generator);
        OSG::ChunkMaterialRefPtr geom1_state = OSG::ChunkMaterial::create();
        ubo_geom_state_1 = create_geometry_material_state(geom1);
        geom1_state->addChunk(ubo_geom_state_1, 3);     // buffer binding point 3
        geom1_state->addChunk(shader_var_chunk);        // block binding point

        GeomState geom2; geom2.material_index = dist(generator);
        OSG::ChunkMaterialRefPtr geom2_state = OSG::ChunkMaterial::create();
        ubo_geom_state_2 = create_geometry_material_state(geom2);
        geom2_state->addChunk(ubo_geom_state_2, 3);     // buffer binding point 3
        geom2_state->addChunk(shader_var_chunk);        // block binding point
       
        cylgeo  ->setMaterial(geom1_state);
        torusgeo->setMaterial(geom2_state);

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);
        scene->setCore(mgrp);

        OSG::commitChanges();
    
        mgr->setRoot(scene);
    
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

            ubo_light_state  = NULL;
            ubo_geom_state_1 = NULL;
            ubo_geom_state_2 = NULL;

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            GeomState geom1; geom1.material_index = dist(generator);
            GeomState geom2; geom2.material_index = dist(generator);

            update_geometry_material_state(ubo_geom_state_1, geom1);
            update_geometry_material_state(ubo_geom_state_2, geom2);

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

//
// vertex shader program.
//
std::string get_vp_program()
{
    std::string vp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
            "smooth out vec3 vNormalES;        // eye space normal\n"
            "smooth out vec3 vPositionES;      // eye space position\n"
            "\n"
            "void main()\n"
            "{\n"
            "    //\n"
            "    // multiply the object space vertex position with the modelview matrix \n"
            "    // to get the eye space vertex position\n"
            "    //\n"
            "    vPositionES = (gl_ModelViewMatrix * gl_Vertex).xyz;\n"
            "\n"
            "    //\n"
            "    // multiply the object space normal with the normal matrix (transpose of the inverse \n"
            "    // model view matrix) to get the eye space normal\n"
            "    //\n"
            "    vNormalES = gl_NormalMatrix * gl_Normal;\n"
            "\n"
            "    //\n"
            "    // multiply the combiend modelview projection matrix with the object space vertex\n"
            "    // position to get the clip space position\n"
            "    //\n"
            "    gl_Position = ftransform();\n"
            "}\n"
            "\n"
            ;
    return vp_program;
}

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program()
{
#ifndef USE_TEST_FP_SHADER
    std::string fp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
            "smooth in vec3 vNormalES;         // eye space normal\n"
            "smooth in vec3 vPositionES;       // eye space position\n"
            "\n"
            "const int num_lights    = 1;\n"
            "const int num_materials = 100;\n"
            "\n"
            "const int directional_light = 0;\n"
            "const int point_light = 1;\n"
            "const int spot_light = 2;\n"
            "const int no_light = 3;\n"
            "\n"
            "struct Light\n"
            "{\n"
            "    vec3 position;          // in eye space\n"
            "    vec3 spot_direction;    // in eye space\n"
            "\n"
            "    vec3 Ia;                // ambient  max. Intensity\n"
            "    vec3 Id;                // diffuse  max. Intensity\n"
            "    vec3 Is;                // specular max. Intensity\n"
            "\n"
            "    vec3 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0\n"
            "    \n"
            "    float spot_cos_cutoff;  // cosine cut of angle\n"
            "\n"
            "    float spot_exponent;    // [0-128]\n"
            "    int  type;              // directional_light, point_light, spot_light, no_light\n"
            "};\n"
            "\n"
            "layout (shared) uniform Lights\n"
            "{\n"
            "    Light light[num_lights];\n"
            "} lights;\n"
            "\n"
            "struct Material\n"
            "{\n"
            "    vec3 ambient;\n"
            "    vec3 diffuse;\n"
            "    vec3 specular;\n"
            "    vec3 emissive;\n"
            "\n"
            "    float opacity;\n"
            "    float shininess;\n"
            "};\n"
            "\n"
            "layout (shared) uniform Materials\n"
            "{\n"
            "    Material material[num_materials];\n"
            "} materials;\n"
            "\n"
            "\n"
            "layout (shared) uniform GeomState\n"
            "{\n"
            "    int material_index;\n"
            "} geom_state;\n"
            "\n"
            "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!\n"
            "\n"
            "layout(location = 0) out vec4 vFragColor;\n"
            "\n"
            "//\n"
            "// directional light contribution\n"
            "//\n"
            "vec3 directionalLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v)  // view direction in eye space\n"
            "{\n"
            "    if (lights.light[i].type != directional_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    //\n"
            "    // the light direction in eye space\n"
            "    //\n"
            "    vec3 l = -lights.light[i].spot_direction;    // we carry the directional light direction in the spot_direction slot\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    return materials.material[j].emissive \n"
            "         + lights.light[i].Ia * materials.material[j].ambient \n"
            "         + lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI\n"
            "         + lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "//\n"
            "// point light contribution\n"
            "//\n"
            "vec3 pointLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v,  // view direction in eye space\n"
            "    in vec3 p)  // vertex position in eye space\n"
            "{\n"
            "    if (lights.light[i].type != point_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    vec3  l = vec3(lights.light[i].position) - p;    // direction from surface to light position\n"
            "    float d = length(l);                             // distance from surface to light source\n"
            "    l = normalize(l);                                // normalized direction from surface to light position\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    //\n"
            "    // Compute attenuation\n"
            "    //\n"
            "    float attenuation = 1.0 / (lights.light[i].attenuation.x + \n"
            "                              (lights.light[i].attenuation.y * d) + \n"
            "                              (lights.light[i].attenuation.z * d * d));\n"
            "\n"
            "    attenuation = clamp(attenuation, 0.0, 1.0);\n"
            "\n"
            "    return materials.material[j].emissive \n"
            "         + attenuation * lights.light[i].Ia * materials.material[j].ambient \n"
            "         + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "//\n"
            "// spot light contribution\n"
            "//\n"
            "vec3 spotLight(\n"
            "    in int i,   // light identifier, i.e. current light\n"
            "    in int j,   // material identifier\n"
            "    in vec3 n,  // vertex normal in eye space\n"
            "    in vec3 v,  // view direction in eye space\n"
            "    in vec3 p)  // vertex position in eye space\n"
            "{\n"
            "    if (lights.light[i].type != spot_light)\n"
            "        return vec3(0.0, 0.0, 0.0);\n"
            "\n"
            "    vec3  l = vec3(lights.light[i].position) - p;   // direction from surface to light position\n"
            "    float d = length(l);                            // distance from surface to light source\n"
            "    l = normalize(l);                               // normalized direction from surface to light position\n"
            "    \n"
            "    vec3 s = lights.light[i].spot_direction;        // spot direction\n"
            "\n"
            "    //\n"
            "    // the half vector\n"
            "    //\n"
            "    vec3 h = normalize(l + v);\n"
            "\n"
            "    float n_dot_l = max(0.0, dot(n, l));\n"
            "    float n_dot_h = max(0.0, dot(n, h));\n"
            "    float l_dot_s = dot(-l, s);\n"
            "\n"
            "    float m = materials.material[j].shininess;\n"
            "\n"
            "    float pf;           // power factor\n"
            "\n"
            "    if (n_dot_l == 0.0)\n"
            "       pf = 0.0;\n"
            "    else\n"
            "       pf = pow(n_dot_h, m);\n"
            "\n"
            "    //\n"
            "    // Compute attenuation\n"
            "    //\n"
            "    float attenuation = 1.0 / (lights.light[i].attenuation.x + \n"
            "                              (lights.light[i].attenuation.y * d) + \n"
            "                              (lights.light[i].attenuation.z * d * d));\n"
            "\n"
            "    attenuation = clamp(attenuation, 0.0, 1.0);\n"
            "\n"
            "    if (l_dot_s < lights.light[i].spot_cos_cutoff) \n"
            "        attenuation = 0.0;\n"
            "    else\n"
            "        attenuation *= pow(l_dot_s, lights.light[i].spot_exponent);\n"
            "\n"
            "    return materials.material[j].emissive \n"
            "         + attenuation * lights.light[i].Ia * materials.material[j].ambient \n"
            "         + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
            "}\n"
            "\n"
            "void main()\n"
            "{\n"
            "    //\n"
            "    // normalize the eye space normal\n"
            "    //\n"
            "    vec3 N = normalize(vNormalES);\n"
            "\n"
            "    //\n"
            "    // get the view vector and normalize it\n"
            "    //\n"
            "    vec3 V = normalize(cCameraPositionES - vPositionES);\n"
            "\n"
            "    //\n"
            "    // Integrate over all lights: Any unused light does not contribute and each light\n"
            "    // contribute either from the directional light, the point light or the spot light.\n"
            "    //\n"
            "    vec3 color = vec3(0.0, 0.0, 0.0);\n"
            "    for (int i = 0; i < num_lights; ++i) {\n"
            "        color += directionalLight(i, geom_state.material_index, N, V) \n"
            "              +        pointLight(i, geom_state.material_index, N, V, vPositionES) \n"
            "              +         spotLight(i, geom_state.material_index, N, V, vPositionES);\n"
            "    }\n"
            "    vFragColor = vec4(color, materials.material[geom_state.material_index  ].opacity);\n"
            "}\n"
            "\n"
            ;
#else
    std::string fp_program =
            "\n"
            "#version 330 compatibility\n"
            "\n"
            "#extension GL_ARB_separate_shader_objects: enable\n"
            "#extension GL_ARB_uniform_buffer_object:   enable\n"
            "\n"
            "smooth in vec3 vNormalES;         // eye space normal\n"
            "smooth in vec3 vPositionES;       // eye space position\n"
            "\n"
            "const int num_lights    = 1;\n"
            "const int num_materials = 100;\n"
            "\n"
            "const int directional_light = 0;\n"
            "const int point_light = 1;\n"
            "const int spot_light = 2;\n"
            "const int no_light = 3;\n"
            "\n"
            "struct Light\n"
            "{\n"
            "    vec3 position;          // in eye space\n"
            "    vec3 spot_direction;    // in eye space\n"
            "\n"
            "    vec3 Ia;                // ambient  max. Intensity\n"
            "    vec3 Id;                // diffuse  max. Intensity\n"
            "    vec3 Is;                // specular max. Intensity\n"
            "\n"
            "    vec3 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0\n"
            "\n"
            "    float spot_cos_cutoff;  // cosine cut of angle\n"
            "    float spot_exponent;    // [0-128]\n"
            "    int  type;              // directional_light, point_light, spot_light, no_light\n"
            "};\n"
            "\n"
            "layout (shared) uniform Lights\n"
            "{\n"
            "    Light light[num_lights];\n"
            "} lights;\n"
            "\n"
            "struct Material\n"
            "{\n"
            "    vec3 ambient;\n"
            "    vec3 diffuse;\n"
            "    vec3 specular;\n"
            "    vec3 emissive;\n"
            "\n"
            "    float opacity;\n"
            "    float shininess;\n"
            "};\n"
            "\n"
            "layout (shared) uniform Materials\n"
            "{\n"
            "    Material material[num_materials];\n"
            "} materials;\n"
            "\n"
            "\n"
            "layout (shared) uniform GeomState\n"
            "{\n"
            "    int material_index;\n"
            "} geom_state;\n"
            "\n"
            "layout(location = 0) out vec4 vFragColor;\n"
            "\n"
            "\n"
            "void main()\n"
            "{\n"
            "\n"
            "    int   type            = lights.light[0].type;\n"
            "    vec3  position        = lights.light[0].position;\n"
            "    vec3  spot_direction  = lights.light[0].spot_direction;\n"
            "    vec3  Ia              = lights.light[0].Ia;\n"
            "    vec3  Id              = lights.light[0].Id;\n"
            "    vec3  Is              = lights.light[0].Is;\n"
            "    vec3  attenuation     = lights.light[0].attenuation;\n"
            "    float spot_cos_cutoff = lights.light[0].spot_cos_cutoff;\n"
            "    float spot_exponent   = lights.light[0].spot_exponent;\n"
            "\n"
            "    vec3  ambient   = materials.material[0].ambient;\n"
            "    vec3  diffuse   = materials.material[0].diffuse;\n"
            "    vec3  specular  = materials.material[0].specular;\n"
            "    vec3  emissive  = materials.material[0].emissive;\n"
            "    float opacity   = materials.material[0].opacity;\n"
            "    float shininess = materials.material[0].shininess;\n"
            "\n"
            "    int material_index = geom_state.material_index;\n"
            "\n"
            "    vec4 error = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "    vec4 color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "\n"
            "    if (type != point_light)\n"
            "        color = error;\n"
            "\n"
            "    if (position != vec3(1.1, 2.2, 3.3))\n"
            "        color = error;\n"
            "\n"
            "    if (spot_direction != vec3(4.4, 5.5, 6.6))\n"
            "        color = error;\n"
            "\n"
            "    if (Ia != vec3(0.2, 0.2, 0.2))\n"
            "        color = error;\n"
            "\n"
            "    if (Id != vec3(0.4, 0.4, 0.4))\n"
            "        color = error;\n"
            "\n"
            "    if (Is != vec3(0.6, 0.6, 0.6))\n"
            "        color = error;\n"
            "\n"
            "    if (attenuation != vec3(0.8, 0.8, 0.8))\n"
            "        color = error;\n"
            "\n"
            "    if (spot_cos_cutoff != 0.8)\n"
            "        color = error;\n"
            "\n"
            "    if (spot_exponent != 12.3)\n"
            "        color = error;\n"
            "\n"
            "    if (ambient != vec3(0.1, 0.2, 0.3))\n"
            "        color = error;\n"
            "\n"
            "    if (diffuse != vec3(0.2, 0.4, 0.6))\n"
            "        color = error;\n"
            "\n"
            "    if (specular != vec3(0.4, 0.6, 0.8))\n"
            "        color = error;\n"
            "\n"
            "    if (emissive != vec3(0.6, 0.8, 1.0))\n"
            "        color = error;\n"
            "\n"
            "    if (opacity != 0.7)\n"
            "        color = error;\n"
            "\n"
            "    if (shininess != 25.4)\n"
            "        color = error;\n"
            "\n"
            "    if (material_index != 7)\n"
            "        color = error;\n"
            "\n"
            "\n"
            "    vFragColor = color;\n"
            "}\n"
            "\n"
            ;
#endif
    return fp_program;
}
