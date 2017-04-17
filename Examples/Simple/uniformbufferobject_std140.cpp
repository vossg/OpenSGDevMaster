// OpenSG Tutorial Example: UniformBufferObject
//
// This example shows how to create a shader uniform block and binding it 
// to a uniform buffer object.
//
// The example does use the UniformBufferObjStd140Chunk which allows the
// host application to directly provide a buffer to the chunk according
// to the std140 specification.
//

//
// * - Attention
// =============
//      The fragment shader of this example declares two uniform block arrays:
//      one for the lights and one for the materials. The members of these 
//      blocks are design to be vectors of size 3: postions, directions, 
//      colors etc. 
//      The ATI/AMD graphic adapters contain a driver bug at the time of
//      writing this example which forces the use of vectors of size 4 for
//      the uniform members. Only then, it is possible to access the members
//      of the uniform block arrays by non constant index variable values. 
//      This driver bug does only show up for the UBO std140 block layout. 
//      NVIDIA drivers do not show this bug and they work as expected
//      from point of view of the std140 specification.
//

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
#include <OSGUniformBufferObjStd140Chunk.h>
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
#include <OpenSG/OSGUniformBufferObjStd140Chunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#endif

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

const std::size_t num_materials = 100;                          // any number of materials
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
// helper to calculate the correct buffer insert positions on std140
//
std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset)
{
    return base_alignment * ((base_alignment + base_offset - 1) / base_alignment);
}

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
// the light uniform buffer object 
// see comment *) at the top of the file
//
std::size_t calc_light_buffer_size(const VecLightsT& vLights)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Pnt4f);   // OSG::Pnt3f   position;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Vec4f);   // OSG::Vec3f   spot_direction;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Ia;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Id;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f Is;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Vec4f);   // OSG::Vec3f   attenuation;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  spot_cos_cutoff;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  spot_exponent;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Int32);   // OSG::Int32   type;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    ao *= vLights.size();       bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_light_buffer(const VecLightsT& vLights)
{
    std::size_t size = calc_light_buffer_size(vLights);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vLights.size(); ++i)
    {
        OSG::Pnt3f position_es       = transform_to_eye_space(vLights[i].position,       mgr);
        OSG::Vec3f spot_direction_es = transform_to_eye_space(vLights[i].spot_direction, mgr);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &position_es[0], sizeof(OSG::Pnt3f));
        bo = ao + sizeof(OSG::Pnt4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &spot_direction_es[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Ia[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Id[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].Is[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vLights[i].attenuation[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vLights[i].spot_cos_cutoff;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vLights[i].spot_exponent;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = vLights[i].type;
        bo = ao + sizeof(OSG::Int32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::UniformBufferObjStd140ChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_light_buffer(vLights);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void update_light_state(OSG::UniformBufferObjStd140Chunk* ubo, const VecLightsT& vLights)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_light_buffer(vLights);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

//
// the material uniform buffer object
// see comment *) at the top of the file
//
std::size_t calc_material_database_buffer_size(const VecMaterialsT& vMaterials)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f ambient;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f diffuse;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f specular;
    ao = align_offset( 16, bo); bo = ao + sizeof(OSG::Color4f); // OSG::Color3f emissive;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  opacity;
    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::Real32);  // OSG::Real32  shininess;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    ao *= vMaterials.size();    bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_material_database_buffer(const VecMaterialsT& vMaterials)
{
    std::size_t size = calc_material_database_buffer_size(vMaterials);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vMaterials.size(); ++i)
    {
        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].ambient[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].diffuse[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].specular[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &vMaterials[i].emissive[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vMaterials[i].opacity;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vMaterials[i].shininess;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::UniformBufferObjStd140ChunkTransitPtr create_material_database_state(const VecMaterialsT& vMaterials)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_material_database_buffer(vMaterials);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_STATIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void update_material_database_state(OSG::UniformBufferObjStd140Chunk* ubo, const VecMaterialsT& vMaterials)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_material_database_buffer(vMaterials);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

//
// the geomertry uniform buffer object
//
std::size_t calc_geometry_material_buffer_size()
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::UInt32);  // OSG::UInt32  material_index;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> create_geometry_material_buffer(const GeomState& geom_state)
{
    std::size_t size = calc_geometry_material_buffer_size();

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = geom_state.material_index;
    bo = ao + sizeof(OSG::UInt32);

    return buffer;
}

OSG::UniformBufferObjStd140ChunkTransitPtr create_geometry_material_state(const GeomState& geom_state)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void update_geometry_material_state(OSG::UniformBufferObjStd140Chunk* ubo, const GeomState& geom_state)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);
        ubo->editMFBuffer()->setValues(buffer);
    }
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
OSG::UniformBufferObjStd140ChunkRefPtr ubo_light_state  = NULL;
OSG::UniformBufferObjStd140ChunkRefPtr ubo_geom_state_1 = NULL;
OSG::UniformBufferObjStd140ChunkRefPtr ubo_geom_state_2 = NULL;

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
        OSG::UniformBufferObjStd140ChunkRefPtr ubo_material_database = create_material_database_state(materials);
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
            "const int num_lights    =   1;\n"
            "const int num_materials = 100;\n"
            "\n"
            "const int directional_light = 0;\n"
            "const int point_light = 1;\n"
            "const int spot_light = 2;\n"
            "const int no_light = 3;\n"
            "\n"
            "struct Light\n"
            "{\n"
            "    vec4 position;          // in eye space\n"
            "    vec4 spot_direction;    // in eye space\n"
            "\n"
            "    vec4 Ia;                // ambient  max. Intensity\n"
            "    vec4 Id;                // diffuse  max. Intensity\n"
            "    vec4 Is;                // specular max. Intensity\n"
            "\n"
            "    vec4 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0\n"
            "    \n"
            "    float spot_cos_cutoff;  // cosine cut of angle\n"
            "\n"
            "    float spot_exponent;    // [0-128]\n"
            "    int  type;              // directional_light, point_light, spot_light, no_light\n"
            "};\n"
            "\n"
            "layout (std140) uniform Lights\n"
            "{\n"
            "    Light light[num_lights];\n"
            "} lights;\n"
            "\n"
            "struct Material\n"
            "{\n"
            "    vec4 ambient;\n"
            "    vec4 diffuse;\n"
            "    vec4 specular;\n"
            "    vec4 emissive;\n"
            "\n"
            "    float opacity;\n"
            "    float shininess;\n"
            "};\n"
            "\n"
            "layout (std140) uniform Materials\n"
            "{\n"
            "    Material material[num_materials];\n"
            "} materials;\n"
            "\n"
            "\n"
            "layout (std140) uniform GeomState\n"
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
            "    vec3 l = -lights.light[i].spot_direction.xyz;    // we carry the directional light direction in the spot_direction slot\n"
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
            "    return materials.material[j].emissive.rgb \n"
            "         + lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
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
            "    vec3  l = vec3(lights.light[i].position.xyz) - p;    // direction from surface to light position\n"
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
            "    return materials.material[j].emissive.rgb \n"
            "         + attenuation * lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + attenuation * lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
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
            "    vec3  l = vec3(lights.light[i].position.xyz) - p;   // direction from surface to light position\n"
            "    float d = length(l);                            // distance from surface to light source\n"
            "    l = normalize(l);                               // normalized direction from surface to light position\n"
            "    \n"
            "    vec3 s = lights.light[i].spot_direction.xyz;        // spot direction\n"
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
            "    return materials.material[j].emissive.rgb \n"
            "         + attenuation * lights.light[i].Ia.rgb * materials.material[j].ambient.rgb \n"
            "         + attenuation * lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l                   // / PI\n"
            "         + attenuation * lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf;        // * (m+8)/(8*PI)\n"
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

    return fp_program;
}
