// OpenSG Tutorial Example: ComputeShader5
//
// This example shows a simple particle system that uses the compute shader
// to calculate the evolution of the system.
//
// What is particular interesting in this particular example is the usage
// of the ShaderStorageBufferObjRefChunk class. It allows the referencing
// of an already existing buffer object as a shader storage buffer object.
// Here three common properties (GeoPnt4fProperty, GeoVec4fProperty and
// GeoVec1fProperty) used. One for representing the particles positions,
// one for the particles velocities and the last one for the representing
// the lifetimes of the particles. The position property and the lifetime
// property is added to the geometry core created for rendering points to
// the screen. These propeties are binded as GL_ARRAY_BUFFER to the render
// shaders. Now, these positions, velocities and lifetimes are calculated
// by a compute shader before rendering. The compute shader expects for
// input and output either a texture or shader storage buffer objects.
// With the ShaderStorageBufferObjRefChunk the very same propeties buffer
// can now be binded as shader storage buffer objects, provided that the
// memory layout is compatible to the std430 layout. This, however, is the
// case for the Pnt4f, Vec4f and Vec1f properties.
//
// This example is based on an example created by Maurice Tollmien
// that can be found at 
// https://github.com/MauriceGit/Partikel_accelleration_on_GPU
//
// His example is governed by the following license:
//
// Copyright (c) 2015, 2016 Maurice Tollmien <maurice.tollmien@gmail.com>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//

#include <sstream>
#include <boost/foreach.hpp>
#include <boost/random.hpp>

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
#include <OSGSolidBackground.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGMultiPropertySSBOChunk.h>
#include <OSGShaderStorageBufferObjRefChunk.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGAlgorithmComputeElement.h>
#include <OSGComputeShaderAlgorithm.h>
#include <OSGComputeShaderChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderProgramVariables.h>
#include <OSGTypedGeoIntegralProperty.h>
#include <OSGTypedGeoVectorProperty.h>
#include <OSGGeoVectorBufferProperty.h>

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
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
#include <OpenSG/OSGShaderStorageBufferObjRefChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGAlgorithmComputeElement.h>
#include <OpenSG/OSGComputeShaderAlgorithm.h>
#include <OpenSG/OSGComputeShaderChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderProgramVariables.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>
#include <OpenSG/OSGGeoVectorBufferProperty.h>
#endif

const OSG::Real32 world_size       =     800.0;
const OSG::UInt32 particle_count   = 6000000;
const OSG::UInt32 attractor_count  =      12;
const OSG::Real32 attractor_time   =       8.0f;
const OSG::Real32 attractor_factor =      10.0f;
const OSG::Real32 delta_time       =     100.0f;

const OSG::Vec3i work_group_count(particle_count / 128, 1,1);

const OSG::Real32 position_max  =  4.0f;
const OSG::Real32 velocity_max  =  0.3f;
const OSG::Real32 attractor_max = 40.0f;

boost::uniform_real<float>  position_distribution ( -position_max,  position_max);
boost::uniform_real<float>  velocity_distribution ( -velocity_max,  velocity_max);
boost::uniform_real<float>  attractor_distribution(-attractor_max, attractor_max);
boost::uniform_01<float>    lifetime_distribution;

typedef boost::mt19937 RNGType;
RNGType rng(time(0));

boost::variate_generator< RNGType, boost::uniform_real<float> >   position_die(rng,  position_distribution);
boost::variate_generator< RNGType, boost::uniform_real<float> >   velocity_die(rng,  velocity_distribution);
boost::variate_generator< RNGType, boost::uniform_real<float> >  attractor_die(rng, attractor_distribution);
boost::variate_generator< RNGType, boost::uniform_01<float> >     lifetime_die(rng,  lifetime_distribution);

//
// The SimpleSceneManager to manage simple applications
//
OSG::SimpleSceneManagerRefPtr mgr;

//
// Simulation data
//
struct Attractor
{
    Attractor() : position(0.f, 0.f, 0.f), mass(0.f) {}
    OSG::Pnt3f  position;
    OSG::Real32 mass;
    static OSG::UInt32 position_id;
    static OSG::UInt32 mass_id;
};
OSG::UInt32 Attractor::position_id = 0;
OSG::UInt32 Attractor::mass_id     = 0;

typedef std::vector<OSG::Pnt4f>     VecPositionsT;
typedef std::vector<OSG::Vec4f>     VecVelocitiesT;
typedef std::vector<OSG::Real32>    VecLifetimesT;
typedef std::vector<Attractor>      VecAttractorsT;

VecPositionsT initialize_positions(std::size_t num)
{
    VecPositionsT positions;
    positions.resize(num);

    for (std::size_t i = 0; i < num; ++i)
    {
        OSG::Pnt4f p(position_die(), position_die(), position_die(), 1.f);
        positions[i] = p;
    }

    return positions;
}

VecVelocitiesT initialize_velocities(std::size_t num)
{
    VecVelocitiesT velocities;
    velocities.resize(num);

    for (std::size_t i = 0; i < num; ++i)
    {
        OSG::Vec4f v(velocity_die(), velocity_die(), velocity_die(), 0.f);
        velocities[i] = v;
    }

    return velocities;
}

VecLifetimesT initialize_lifetimes(std::size_t num)
{
    VecLifetimesT lifetimes;
    lifetimes.resize(num);

    for (std::size_t i = 0; i < num; ++i)
    {
        lifetimes[i] = lifetime_die();
    }

    return lifetimes;
}

VecAttractorsT initialize_attractors(std::size_t num)
{
    VecAttractorsT attractors;
    attractors.resize(num);

    for (std::size_t i = 0; i < num; ++i)
    {
        OSG::Pnt3f p(
            attractor_die(), 
            attractor_die(), 
            attractor_die() * attractor_factor);
        attractors[i].position = p;
        attractors[i].mass = 0.f;
    }

    return attractors;
}

void update_attractors(VecAttractorsT& attractors)
{
    for (std::size_t i = 0; i < attractors.size(); ++i)
    {
        OSG::Pnt3f p(
            attractor_die(),
            attractor_die(),
            attractor_die() * attractor_factor);
        attractors[i].position = p;
        attractors[i].mass = 0.f;
    }
}

VecPositionsT  positions  = initialize_positions (particle_count);
VecVelocitiesT velocities = initialize_velocities(particle_count);
VecLifetimesT  lifetimes  = initialize_lifetimes (particle_count);
VecAttractorsT attractors = initialize_attractors(attractor_count);

OSG::GeoPnt4fPropertyTransitPtr create_position_property(const VecPositionsT& positions)
{
    OSG::GeoPnt4fPropertyRefPtr properties = OSG::GeoPnt4fProperty::create();

    properties->setUseVBO(true);

    BOOST_FOREACH(const OSG::Pnt4f pnt, positions)
    {
        properties->push_back(pnt);
    }

    return OSG::GeoPnt4fPropertyTransitPtr(properties);
}

OSG::GeoVec4fPropertyTransitPtr create_velocity_property(const VecVelocitiesT& velocities)
{
    OSG::GeoVec4fPropertyRefPtr properties = OSG::GeoVec4fProperty::create();

    properties->setUseVBO(true);

    BOOST_FOREACH(const OSG::Vec4f vec, velocities)
    {
        properties->push_back(vec);
    }

    return OSG::GeoVec4fPropertyTransitPtr(properties);
}

OSG::GeoVec1fPropertyTransitPtr create_lifetime_property(const VecLifetimesT& lifetimes)
{
    OSG::GeoVec1fPropertyRefPtr properties = OSG::GeoVec1fProperty::create();

    properties->setUseVBO(true);

    BOOST_FOREACH(OSG::Real32 val, lifetimes)
    {
        properties->push_back(OSG::Vec1f(val));
    }

    return OSG::GeoVec1fPropertyTransitPtr(properties);
}

OSG::MultiPropertySSBOChunkTransitPtr create_attractor_ssbo_chunk(const VecAttractorsT& attractors)
{
    OSG::MultiPropertySSBOChunkRefPtr attractorChunk = OSG::MultiPropertySSBOChunk::create();

    OSG::UInt32 vec3_id, float_id;

     vec3_id = attractorChunk->addMember(OSG::MultiPropertySSBOChunk:: VEC3_T);
    float_id = attractorChunk->addMember(OSG::MultiPropertySSBOChunk::FLOAT_T);

    attractorChunk->setUsage(GL_STATIC_DRAW);

    Attractor::position_id =  vec3_id++;    
    Attractor::    mass_id = float_id++;

    BOOST_FOREACH(const Attractor& a, attractors)
    {
        OSG::UInt32 idx = attractorChunk->addProperty();

        attractorChunk->setVec3Property (idx, Attractor::position_id, a.position.subZero());
        attractorChunk->setFloatProperty(idx, Attractor::    mass_id, a.mass);
    }

    return OSG::MultiPropertySSBOChunkTransitPtr(attractorChunk);
}

void update_attractor_state(OSG::MultiPropertySSBOChunk* attractorChunk, const VecAttractorsT& attractors)
{
    if (attractorChunk)
    {
        if (attractorChunk->getNumProperties() != attractors.size())
        {
            attractorChunk->clearProperties();

            BOOST_FOREACH(const Attractor& a, attractors)
            {
                OSG::UInt32 idx = attractorChunk->addProperty();

                attractorChunk->setVec3Property (idx, Attractor::position_id, a.position.subZero());
                attractorChunk->setFloatProperty(idx, Attractor::    mass_id, a.mass);
            }
        }
        else
        {
            for (OSG::UInt32 idx = 0; idx < attractors.size(); ++idx)
            {
                const Attractor& a = attractors[idx];

                attractorChunk->setVec3Property (idx, Attractor::position_id, a.position.subZero());
                attractorChunk->setFloatProperty(idx, Attractor::    mass_id, a.mass);
            }
        }
    }
}

OSG::ShaderStorageBufferObjRefChunkTransitPtr create_ssbo_ref_chunk(OSG::UInt32 glId)
{
    OSG::ShaderStorageBufferObjRefChunkRefPtr chunk = OSG::ShaderStorageBufferObjRefChunk::create();

    chunk->setOsgGLId(glId);

    return OSG::ShaderStorageBufferObjRefChunkTransitPtr(chunk);
}

//
// compute, vertex and fragment shader program.
//
std::string get_cp_program();
std::string get_vp_program();
std::string get_fp_program();

const OSG::UInt32  position_binding_point = 1;
const OSG::UInt32  velocity_binding_point = 2;
const OSG::UInt32  lifetime_binding_point = 3;
const OSG::UInt32 attractor_binding_point = 4;

//
// Proerties and shader storage buffer objects corresponding to the shader blocks
//
OSG::GeoVectorPropertyRefPtr geoprops_position  = NULL;
OSG::GeoVectorPropertyRefPtr geoprops_velocity  = NULL;
OSG::GeoVectorPropertyRefPtr geoprops_lifetime  = NULL;

OSG::ShaderStorageBufferObjRefChunkRefPtr ssbo_position = NULL;
OSG::ShaderStorageBufferObjRefChunkRefPtr ssbo_velocity = NULL;
OSG::ShaderStorageBufferObjRefChunkRefPtr ssbo_lifetime = NULL;

OSG::MultiPropertySSBOChunkRefPtr ssbo_attractor = NULL;

OSG::ShaderProgramRefPtr compShader = NULL;

//
// The computation core
//
void createSimulationData()
{
    geoprops_position = create_position_property(positions );
    geoprops_velocity = create_velocity_property(velocities);
    geoprops_lifetime = create_lifetime_property(lifetimes );

    ssbo_position = create_ssbo_ref_chunk(geoprops_position->getGLId());
    ssbo_velocity = create_ssbo_ref_chunk(geoprops_velocity->getGLId());
    ssbo_lifetime = create_ssbo_ref_chunk(geoprops_lifetime->getGLId());

    ssbo_attractor = create_attractor_ssbo_chunk(attractors);
}

OSG::AlgorithmComputeElementTransitPtr createComputation()
{
    OSG::ChunkMaterialRefPtr data_state = OSG::ChunkMaterial::create();
    data_state->addChunk(ssbo_position,   position_binding_point);
    data_state->addChunk(ssbo_velocity,   velocity_binding_point);
    data_state->addChunk(ssbo_lifetime,   lifetime_binding_point);
    data_state->addChunk(ssbo_attractor, attractor_binding_point);

    compShader = OSG::ShaderProgram::create();
    compShader->setShaderType(GL_COMPUTE_SHADER);
    compShader->setProgram(get_cp_program());
    compShader->addUniformVariable("dt", 0.f);
    compShader->addShaderStorageBlock("Positions",   position_binding_point);
    compShader->addShaderStorageBlock("Velocities",  velocity_binding_point);
    compShader->addShaderStorageBlock("Lifetimes",   lifetime_binding_point);
    compShader->addShaderStorageBlock("Attractors", attractor_binding_point);

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

    OSG::GeometryRefPtr geometry = OSG::Geometry::create();
    geometry->setDlistCache(false);
    geometry->setUseVAO(true);
    geometry->setUseAttribCalls(true);
    
    OSG::NodeRefPtr geomNode = OSG::makeNodeFor(geometry);

    OSG::GeoUInt8PropertyRefPtr  types   = OSG::GeoUInt8Property ::create();
    OSG::GeoUInt32PropertyRefPtr lengths = OSG::GeoUInt32Property::create();

    types  ->addValue(GL_POINTS);
    lengths->addValue(particle_count);

    types   ->setUseVBO(true);
    lengths ->setUseVBO(true);

    types   ->setUsage(OSG::GeoProperty::UsageSystemSet);
    lengths ->setUsage(OSG::GeoProperty::UsageSystemSet);

    geometry->setTypes    (types);
    geometry->setLengths  (lengths);

    geometry->setProperty (geoprops_position, 0);
    geometry->setProperty (geoprops_lifetime, 1);

    OSG::BoxVolume& volume = geomNode->editVolume();

    volume.setBounds(OSG::Pnt3f(-world_size,-world_size,-world_size), OSG::Pnt3f(world_size,world_size,world_size));
    volume.setStatic(true);

    scene->addChild(geomNode);

    //
    // create the shader program
    //
    OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
    OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
    OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

    vertShader->setProgram(get_vp_program());
    fragShader->setProgram(get_fp_program());

    vertShader->addOSGVariable("OSGModelViewMatrix");
    vertShader->addOSGVariable("OSGProjectionMatrix");

    prog_chunk->addShader(vertShader);
    prog_chunk->addShader(fragShader);

    OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
    prog_state->addChunk(prog_chunk);

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

        createSimulationData();

        OSG::NodeRefPtr root = OSG::makeNodeFor(createComputation());

        root->addChild(createScene());

        mgr->setRoot(root);

        OSG::SolidBackgroundRefPtr bgnd = OSG::SolidBackground::create();
        bgnd->setColor(OSG::Color3f(1.f, 1.f, 1.f));

        mgr->setBackground(bgnd);

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

OSG::TimeStamp time_stamp = 0;
OSG::Real32    simulation_time = 0;

//
// redraw the window
//
void display(void)
{
    if (!mgr) return;

    if (time_stamp == 0)
        time_stamp = OSG::getTimeStamp();

    OSG::TimeStamp now = OSG::getTimeStamp();
    OSG::Time elapsed = OSG::getTimeStampMsecs(now - time_stamp);

    OSG::Real32 dt = elapsed / 1000.f;

    simulation_time += dt;

    if (compShader)
        compShader->updateUniformVariable("dt", delta_time * OSG::Real32(elapsed) / 1000.f);

    if (simulation_time >= attractor_time)
    {
        update_attractors(attractors);
        update_attractor_state(ssbo_attractor, attractors);

        simulation_time = 0.f;
    }

    OSG::commitChanges();
   
    mgr->redraw();

    time_stamp = now;
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
            mgr = NULL;

            geoprops_position = NULL;
            geoprops_velocity = NULL;
            geoprops_lifetime = NULL;

            ssbo_position  = NULL;
            ssbo_velocity  = NULL;
            ssbo_lifetime  = NULL;
            ssbo_attractor = NULL;

            compShader = NULL;

            releaseGLUT();

            OSG::osgExit();
            exit(0);
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
    //glutDisplayFunc(NULL);
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutKeyboardFunc(NULL);
    glutIdleFunc(NULL);
}

void print_help()
{
    std::cout << "Esc   : quit example" << std::endl;
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
    << endl << "layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in;"
    << endl << ""
    << endl << "layout (std430, binding = 1) buffer Positions"
    << endl << "{"
    << endl << "    vec4 positions[];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430, binding = 2) buffer Velocities"
    << endl << "{"
    << endl << "    vec4 velocities[];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430, binding = 3) buffer Lifetimes"
    << endl << "{"
    << endl << "    float lifetimes[];"
    << endl << "};"
    << endl << ""
    << endl << "struct Attractor"
    << endl << "{"
    << endl << "    vec3  position;"
    << endl << "    float mass;"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430, binding = 4) buffer Attractors"
    << endl << "{"
    << endl << "    Attractor attractors[];"
    << endl << "};"
    << endl << ""
    << endl << "// Delta time"
    << endl << "uniform float dt;"
    << endl << ""
    << endl << "//"
    << endl << "// See: http://byteblacksmith.com/improvements-to-the-canonical-one-liner-glsl-rand-for-opengl-es-2-0/"
    << endl << "//"
    << endl << "highp float rand(vec2 v)"
    << endl << "{"
    << endl << "    highp float  a = 12.9898;"
    << endl << "    highp float  b = 78.233;"
    << endl << "    highp float  c = 43758.5453;"
    << endl << "    highp float  d = dot(v.xy, vec2(a,b));"
    << endl << "    highp float  e = mod(d, 3.14);"
    << endl << "    return fract(sin(e) * c);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 calcForceFor(vec3 forcePoint, vec3 pos)"
    << endl << "{"
    << endl << "    float gauss  = 10000.0;"
    << endl << "    float e      = 2.71828183;"
    << endl << "    float k_weak = 1.0;"
    << endl << ""
    << endl << "    vec3 dir = forcePoint - pos.xyz;"
    << endl << "    float  g = pow (e, -pow(length(dir), 2) / gauss);"
    << endl << "    vec3   f = normalize(dir) * k_weak * (1+ mod(rand(dir.xy), 10) - mod(rand(dir.yz), 10)) / 10.0 * g;"
    << endl << ""
    << endl << "    return f;"
    << endl << "}"
    << endl << ""
    << endl << "void main(void)"
    << endl << "{"
    << endl << "    uint index = gl_GlobalInvocationID.x;"
    << endl << ""
    << endl << "    vec3 forcePoint = vec3(0);"
    << endl << ""
    << endl << "    for (int i = 0; i < attractors.length(); i++)"
    << endl << "    {"
    << endl << "        forcePoint += attractors[i].position;"
    << endl << "    }"
    << endl << ""
    << endl << "    vec3  vel      = velocities[index].xyz;"
    << endl << "    vec3  pos      =  positions[index].xyz;"
    << endl << "    float lifetime =  lifetimes[index];"
    << endl << ""
    << endl << "    float k_v = 1.5;"
    << endl << ""
    << endl << "    vec3 f = calcForceFor(forcePoint, pos) + rand(pos.xz)/100.0;"
    << endl << ""
    << endl << "    vec3 v = normalize(vel + (f * dt)) * k_v;"
    << endl << ""
    << endl << "    v += (forcePoint-pos) * 0.00005;"
    << endl << ""
    << endl << "    vec3 s = pos + v * dt;"
    << endl << ""
    << endl << "    lifetime -= 0.0001 * dt;"
    << endl << ""
    << endl << "    if (lifetime <= 0)"
    << endl << "    {"
    << endl << "        s  = -s + rand(s.xy)*20.0 -rand(s.yz)*20.0;"
    << endl << "        lifetime = 0.99;"
    << endl << "    }"
    << endl << ""
    << endl << ""
    << endl << "      lifetimes[index] = lifetime;"
    << endl << "      positions[index] = vec4(s, 1.0);"
    << endl << "     velocities[index] = vec4(v, 0.0);"
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

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "layout (location = 0) in vec4  vertPos;"
    << endl << "layout (location = 1) in float lifetime;"
    << endl << ""
    << endl << "uniform mat4 OSGModelViewMatrix;"
    << endl << "uniform mat4 OSGProjectionMatrix;"
    << endl << ""
    << endl << "out float color;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    color = lifetime;"
    << endl << "    gl_Position = OSGProjectionMatrix * OSGModelViewMatrix * vertPos;"
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

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "in float color;"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    if (color < 0.1)"
    << endl << "    {"
    << endl << "        vFragColor = mix(vec4(vec3(0.0),1.0), vec4(0.0,0.5,1.0,1.0), color*10.0);"
    << endl << "    }"
    << endl << "    else if (color > 0.9)"
    << endl << "    {"
    << endl << "        vFragColor = mix(vec4(0.6,0.05,0.0,1.0), vec4(vec3(0.0),1.0), (color-0.9)*10.0);"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        vFragColor = mix(vec4(0.0,0.5,1.0,1.0), vec4(0.6,0.05,0.0,1.0), color);"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}
