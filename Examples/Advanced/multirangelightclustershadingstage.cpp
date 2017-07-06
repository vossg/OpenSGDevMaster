// OpenSG Example: MultiRangeLightClusterShadingStage
//
// This example implements a forward cluster shading algorithm according to
//      Ola Olsson et.al and Emil Persson
//      https://newq.net/publications/more/s2015-many-lights-course
//
// It uses the MultiLightChunk for the light representation and the
// ClusterShadingStage core. It shows a simple scene that
// is filled with geometry and point, spot and cinema lights.
// Keyboard bindings allow to manipulate the setup in various ways. 
//
// At startup you can see 128 lights and 256 geometries moving in the scene.
// On a NVidia GeForce GTX 560 rendering this scene renders smoothly.
// Pressing button 't' stops the clustering and the frame rate drops.
// After enabling clustering again by pressing 't' you can increase
// the number of lights to 512 by pressing key '3' two times. Now the
// frame rate miserable despite of the clustering. The reason is that
// the cluster population is now to hight. We can lower it by decreasing
// the range of influence of the lights by pressing key 'P' (shift) four
// times. Now the frame rate is somewhat reasonable. Switching clustering
// off by key 't' gets the GPU into considerable workload with resulting
// in a very poor frame rate.
//
// Remarks:
//      - only tested on decsent NVidia GPUs
//      - this example is a proof of concept
//      - this example is not performance optimized
//
// Key bindings:
//      Esc   : quit example
//      Space : toogle geometry simulation on/off
//      1     : only one light
//      2     : half number of lights
//      3     : double number of lights
//      4     : half number of geometry objects
//      5     : double number of geometry objects
//      a     : add directional test lights useful only if the view
//              frustum is visualized
//      b     : show correct light geometry frustum
//      c     : cull lights on cpu. Only useful for testing
//      e/E   : speed up/down simulation
//      h     : toogle HDR stage usage on/off
//      i/I   : increase/decrease light intensity
//      l     : toogle light simulation on/off
//      m     : assign new color to geometry
//      o/O   : double/half simulation time interval
//      p/P   : increase/decrease light range
//      r     : reset the example
//      s     : toogle statistics on/off
//      t     : toogle usage of cluster shading on/off
//      u     : toggle spot direction line on/off
//      U     : toggle special spot direction cases
//      v     : toogle frustum visualization on/off
//      x     : recreate the lights with current spot dir case
//

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>
#include <boost/random.hpp>
#include <boost/tuple/tuple.hpp>
#include "boost/tuple/tuple_comparison.hpp"
#include <boost/multi_array.hpp>

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
#include <OSGTime.h>
#include <OSGPlane.h>
#include <OSGMatrixCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGOrthographicCamera.h>
#include <OSGHDR2Stage.h>
#include <OSGClusterShadingStage.h>
#include <OSGInverseTransform.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGShaderProgramVariables.h>
#include <OSGShaderStorageBufferObjChunk.h>
#include <OSGShaderStorageBufferObjStdLayoutChunk.h>
#include <OSGUniformBufferObjChunk.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGMatrixUtility.h>
#include <OSGMultiLightChunk.h>
#include <OSGMultiPropertyUBOChunk.h>
#include <OSGMultiPropertySSBOChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTextureObjChunk.h>
#include <OSGTextureEnvChunk.h>
#include <OSGTextureImageChunk.h>
#include <OSGTwoSidedLightingChunk.h>
#include <OSGAlgorithmComputeElement.h>
#include <OSGComputeShaderAlgorithm.h>
#include <OSGComputeShaderChunk.h>
#include <OSGGeoProperties.h>
#include <OSGSimpleLightGeometry.h>
#include <OSGSimpleCurve.h>

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
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGPlane.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGOrthographicCamera.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGClusterShadingStage.h>
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGShaderProgramVariables.h>
#include <OpenSG/OSGShaderStorageBufferObjChunk.h>
#include <OpenSG/OSGShaderStorageBufferObjStdLayoutChunk.h>
#include <OpenSG/OSGUniformBufferObjChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGMultiLightChunk.h>
#include <OpenSG/OSGMultiPropertyUBOChunk.h>
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGTextureEnvChunk.h>
#include <OpenSG/OSGTextureImageChunk.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#include <OpenSG/OSGAlgorithmComputeElement.h>
#include <OpenSG/OSGComputeShaderAlgorithm.h>
#include <OpenSG/OSGComputeShaderChunk.h>
#include <OpenSG/OSGGeoProperties.h>
#include <OpenSG/OSGSimpleLightGeometry.h>
#include <OpenSG/OSGSimpleCurve.h>
#endif

// ============================================================================
//
// Part: Declaration of the example scene and some helpers:
//      - constants that governs the example
//      - random number generators
//      - smooth cubic Bezier spline curve
//
// ============================================================================

const bool        use_ortho_camera      = false;    // use a orthographic camera instead of the perspective camera

const OSG::Int32  init_num_geometries   = 256;      // the initial number of to be lit geometry
const OSG::Int32  max_num_geometries    = 2048;     // the maximal number of lit geometry

const OSG::Int32  num_grid_boxes        = 100;      // each light and geometry has a motion curve. 
                                                    // Sample a number if different cube boxes from the scene and
                                                    // take randomly one point from each cube. That guarantees that
                                                    // the knot points do not clump and that they are all unequal.
const OSG::Int32  num_curve_knots       = 40;       // each motion curve has that number of knot points

const std::size_t num_materials         = 5000;     // material database has this number of entries

const OSG::Int32  init_num_lights       = 128;      // initial number if example lights
const OSG::Int32  max_num_lights        = 2048;     // maximal number of allowed lights

const OSG::Real32 max_light_power       = 10.f;     // light intensity is choosen randomly up to the maximal light power

const OSG::Real32 world_size            = 10.f;     // lights and geometry init positions are bounded in the world
const OSG::Real32 box_factor            = 1.5f;     // visualization box is drawn around the world

OSG::Real32 simulation_delta            = 0.0001f;  // determines the simulation speed (keys e/E)
OSG::Real32 elapse_time_limit           = 10.f;     // time in milliseconds after which a simulation step is performed (keys o/O)



const OSG::Real32 rangeFactor           = 1.15f;    // range multiplication factor (keys p/P)
const OSG::Real32 intensityFactor       = 1.2f;     // intensity multiplication factor (keys i/I)

const OSG::UInt32 block_size            = 16;       // number of compute shader threads per xy-direction
const OSG::UInt32 tile_size             = 64;       // number of pixel per cluster tile per xy-direction
const OSG::UInt32 num_cluster_z         = 32;       // number of clusters in the z direction
const OSG::Real32 near_plane_offset     = 5.f;      // clustering starts to (zNear + near_plane_offset)

const OSG::UInt32 light_index_list_size = 2097152;  // Max number of light index list entries.
                                                    // If we have a screen size of 1920*1080 pixel and assume 
                                                    // a 32 cluster in z-direction we have, with a tile size 
                                                    // of 64 pixel, 30*17*32 = 16320 cluster. With 2^21 = 2097152 
                                                    // light list entries we have on average space for around 64 
                                                    // lights per cluster. The light list then occupy 
                                                    // 2097152*4 bytes = 8388608 bytes of graphic memory.
                                       
const OSG::Vec3i work_group_size        = OSG::Vec3i(block_size, block_size, 1);
                                                    // each compute shader work group has that thread layout

const OSG::UInt32 num_test_val_entries  = 65536;    // number of array elements in the TestData members.
                                                    // on default the test data is not transfered to the GPU
                                                    // and no test are performed. Test were used on example
                                                    // development and are leaved in for illustration purpose.

//
// Simulation parameters
//
OSG::TimeStamp time_stamp        = 0;               // time stamp is updated after each simulation step
OSG::Real32    simulation_param  = 0.f;             // value in range [0,1]. Used for motion curve evaluation
bool           simulate_geometry = true;            // motion of lit geometry
bool           simulate_lights   = true;            // motion of shading lights

bool           visualize_frustum = false;

OSG::SimpleSceneManagerRefPtr mgr;                  // the global scene manager

//
// The example makes use of many randomly choosen values for various parameters.
// Most parameters have specific ranges and types. Therefore the example provides
// special dices on uniform distributions over the ranges for the different parameters.
//
typedef boost::mt19937 RNGType;
RNGType rng(time(0));

boost::uniform_int<>        box_dist(0, num_grid_boxes-1);
boost::variate_generator<RNGType, boost::uniform_int<> >            box_idx_die(rng, box_dist);

boost::uniform_int<>        die_dist(1, 6);
boost::variate_generator<RNGType, boost::uniform_int<> >            classic_die(rng, die_dist);  

boost::uniform_int<>        geom_dist(0, 7);
boost::variate_generator<RNGType, boost::uniform_int<> >            geom_idx_die(rng, geom_dist);  

boost::uniform_01<float>    unit_distribution;
boost::variate_generator< RNGType, boost::uniform_01<float> >       unit_die(rng, unit_distribution);

boost::uniform_real<float>  small_distribution(0.1f, 1.f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     small_die(rng,  small_distribution);

boost::uniform_real<float>  spot_distribution(5.f, 90.f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     spot_die(rng,  spot_distribution);

boost::uniform_real<float>  light_range_distribution(0.2f, 0.7f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_range_die(rng,  light_range_distribution);

boost::uniform_real<float>  light_ellipsis_roundness_distribution1(0.2f, 1.0f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_roundness_die1(rng,  light_ellipsis_roundness_distribution1);

boost::uniform_real<float>  light_ellipsis_roundness_distribution2(1.0f, 2.0f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_roundness_die2(rng,  light_ellipsis_roundness_distribution2);

boost::uniform_real<float>  light_ellipsis_roundness_distribution3(2.0f, 51.0f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_roundness_die3(rng,  light_ellipsis_roundness_distribution3);

boost::uniform_real<float>  light_ellipsis_twist_distribution(0.f, 360.0f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_twist_die(rng,  light_ellipsis_twist_distribution);

boost::uniform_real<float>  light_ellipsis_radius_distribution(0.1f, 2.0f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_radius_die(rng,  light_ellipsis_radius_distribution);

boost::uniform_real<float>  light_ellipsis_radius_ratio_distribution(1.01f, 1.5f);
boost::variate_generator< RNGType, boost::uniform_real<float> >     light_ellipsis_radius_ratio_die(rng,  light_ellipsis_radius_ratio_distribution);

std::vector<OSG::Pnt3f> dice_knots(bool close_curve);

OSG::Vec3f dice_unit_vector()
{
    OSG::Vec3f v;

    while (v.length() < OSG::Eps)
        v.setValues(
            -1.f + 2.f * unit_die(), 
            -1.f + 2.f * unit_die(), 
            -1.f + 2.f * unit_die());

    v.normalize();

    return v;
}

// ============================================================================
//
// Part: Declaration/Implementation of
//      - struct Light and type VecLightsT,
//      - struct Material and type VecMaterialsT,
//      - struct GeomState
//  and corresponding initialization routines.
//
// ============================================================================

//
// simple light data structure
//
struct Light : public OSG::MultiLight
{
    explicit Light(Type e);
            ~Light();

    static Light create_light(Type e, OSG::Int32 test_dir_light_type = -1);

    void create_light_geometry(OSG::UInt32 material_idx);

    OSG::TransformRefPtr         transform; // the beacons transform core
    OSG::SmoothCubicBezierSpline curve;     // the path that the light will follow

    static bool         cpu_cull_lights;
    static bool         cpu_calc_frustums;
    static bool         add_dir_test_lights;
    static bool         correct_light_geometry;
    static bool         use_light_index_list;
    static bool         show_spot_dir_line;
    static int          force_spot_dir;
    static OSG::Vec3f   dir_test_case_6;
    static OSG::Vec3f   dir_test_case_7;
    static OSG::Vec3f   dir_test_case_8;
};

bool        Light::cpu_cull_lights        = false;
bool        Light::cpu_calc_frustums      = false;
bool        Light::add_dir_test_lights    = false;
bool        Light::correct_light_geometry = false;
bool        Light::use_light_index_list   = true;
bool        Light::show_spot_dir_line     = false;
int         Light::force_spot_dir         = 0;
OSG::Vec3f  Light::dir_test_case_6        = OSG::Vec3f(0,0,-1);
OSG::Vec3f  Light::dir_test_case_7        = OSG::Vec3f(0,0,-1);
OSG::Vec3f  Light::dir_test_case_8        = OSG::Vec3f(0,0,-1);

typedef std::vector<Light>  VecLightsT;         // multiple lights
VecLightsT lights;                              // the lights of the scene

Light::Light(Type e) 
: MultiLight(e)
, transform(NULL)
, curve(dice_knots(true))
{}

Light::~Light() 
{
    beacon    = NULL;
    transform = NULL;
}

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
    OSG_ASSERT(num > max_num_lights + 1);

    VecMaterialsT mat(num);

    for (std::size_t i = max_num_lights+1; i < num; ++i)
    {
        mat[i].ambient   = OSG::Color3f(0.001f, 0.001f, 0.001f);
        mat[i].diffuse.setRandom();
        mat[i].specular  = OSG::Color3f(0.9f, 0.9f, 0.9f);
        mat[i].emissive  = OSG::Color3f(0.0f, 0.0f, 0.0f);
        mat[i].opacity   = 1.f;
        mat[i].shininess = 320.f * small_die();

        //int r = classic_die();
        //if (r <= 3)
        //    mat[i].opacity = small_die();
    }

    //
    // special grey material for box
    //
    mat[0].ambient   = OSG::Color3f(0.001f, 0.001f, 0.001f);
    mat[0].diffuse   = OSG::Color3f(0.7f, 0.7f, 0.7f);
    mat[0].specular  = OSG::Color3f(0.9f, 0.9f, 0.9f);
    mat[0].emissive  = OSG::Color3f(0.0f, 0.0f, 0.0f);
    mat[0].opacity   = 1.f;
    mat[0].shininess = 100.f;

    return mat;
}

VecMaterialsT materials = initialize_materials(num_materials);    // the material database

// 
// we reserve the first max_num_lights + 1 materials for the light simulation and 
// the grey box.
//
boost::uniform_int<OSG::UInt32> material_dist(max_num_lights+1, num_materials-1); 
boost::variate_generator<RNGType, boost::uniform_int<OSG::UInt32> > material_idx_die(rng, material_dist);  

//
// Simple geometry state data structure
//
struct GeomState
{
    GeomState()
    : material_index(0)
    {}

    OSG::UInt32  material_index;

    static OSG::UInt32 material_index_id;
};

OSG::UInt32 GeomState::material_index_id = 0;

// ============================================================================
//
// Part: Creation and update of the light state
//
// ============================================================================

OSG::MultiLightChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::MultiLightChunkRefPtr lightChunk = OSG::MultiLightChunk::create();

    lightChunk->setUsage(GL_DYNAMIC_DRAW);
    lightChunk->setLayoutType(OSG::MultiLight::SIMPLE_LAYOUT | OSG::MultiLight::CINEMA_LAYOUT);

    lightChunk->setHasEyeToLightSpaceMatrix(true);  // provide a struct entry for the transform from view space to light space
    lightChunk->setHasCosSpotlightAngle    (true);  // provide a struct entry for the cosine of the spot light angle (defaults to true)
    lightChunk->setHasSpotlightAngle       (true);  // provide a struct entry for the spot light angle itself (defaults to false)

    //lightChunk->setEyeSpace(true);

    BOOST_FOREACH(const Light& light, vLights)
    {
        lightChunk->addLight(light);
    }

    return OSG::MultiLightChunkTransitPtr(lightChunk);
}

void update_light_state(OSG::MultiLightChunk* lightChunk, const VecLightsT& vLights)
{
    if (lightChunk)
    {
        if (lightChunk->numLights() != vLights.size())
        {
            lightChunk->clearLights();

            BOOST_FOREACH(const Light& light, vLights)
            {
                lightChunk->addLight(light);
            }
        }
        else
        {
            for (OSG::UInt32 idx = 0; idx < vLights.size(); ++idx)
            {
                const Light& light = vLights[idx];
                lightChunk->updateLight(idx, light);
            }
        }
    }
}

// ============================================================================
//
// Part: Some routines for handling of the memory buffer and the the
//          creation on the MultiPropertySSBOChunk objects:
//
//           i) create_material_database_state, 
//              update_material_database_state
//
//          ii) create_geometry_material_state, 
//              update_geometry_material_state
//
// ============================================================================

//
// i) the material shader storage buffer object
//
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

//
// ii) the geomertry shader storage buffer object
//
OSG::MultiPropertyUBOChunkTransitPtr create_geometry_material_state(const GeomState& geomState)
{
    OSG::MultiPropertyUBOChunkRefPtr geomStateChunk = OSG::MultiPropertyUBOChunk::create();

    GeomState::material_index_id = geomStateChunk->addMember(OSG::MultiPropertyUBOChunk::UINT_T, 1);
    geomStateChunk->setUsage(GL_DYNAMIC_DRAW);

    OSG::UInt32 idx = geomStateChunk->addProperty();
    geomStateChunk->setUIntProperty(idx, GeomState::material_index_id, geomState.material_index);

    return OSG::MultiPropertyUBOChunkTransitPtr(geomStateChunk);
}

void update_geometry_material_state(OSG::MultiPropertyUBOChunk* geomStateChunk, const GeomState& geomState)
{
    if (geomStateChunk)
    {
        if (geomStateChunk->getNumProperties() != 1)
        {
            geomStateChunk->clearProperties();

            OSG::UInt32 idx = geomStateChunk->addProperty();
            geomStateChunk->setUIntProperty(idx, GeomState::material_index_id, geomState.material_index);
        }
        else
        {
            geomStateChunk->setUIntProperty(  0, GeomState::material_index_id, geomState.material_index);
        }
    }
}

// ============================================================================
//
// Part: The application finally starts here
//
// ============================================================================

// UBO block binding points
const OSG::UInt32                 geom_binding_point = 0;

// SSBO block binding points
const OSG::UInt32             material_binding_point = 0;

//
// shader programs.
//
std::string               get_vp_program();
std::string               get_fp_program();

OSG::ShaderProgramRefPtr frag_shader = NULL;

//
// The scene 
//
OSG::NodeRefPtr scene_node = NULL;

//
// Cluster visualisation root node
//
OSG::NodeRefPtr cluster_geometry_root_node = NULL;

//
// The ClusterShadingStage
//
OSG::ClusterShadingStageRefPtr cluster_shading_stage = NULL;
OSG::NodeRefPtr                cluster_shading_node  = NULL;

//
// A HDR stage
//
OSG::HDR2StageRefPtr hdr_stage = NULL;
OSG::NodeRefPtr      hdr_node  = NULL;

//
// The material database for all visible geometry: objects, lights, stage box
//
OSG::MultiPropertySSBOChunkRefPtr ssbo_material_database = NULL;

//
// The mulit light chunk
//
OSG::MultiLightChunkRefPtr multi_light_chunk = NULL;

//
// The shader program variable chunk for the geom state
//
OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = NULL;

//
// Shader Storage buffer objects corresponding to transient shader blocks
//
std::vector<OSG::MultiPropertyUBOChunkRefPtr> ubo_geom_states;

//
// A separate transformation for each object and a spline for the trajectory
//
std::vector<OSG::NodeRefPtr>              geom_nodes;
std::vector<OSG::TransformRefPtr>         geom_trafos;
std::vector<OSG::SmoothCubicBezierSpline> geom_curves;

//
// Simulate some movement in the scene
//
void update_simulation()
{
    //
    // Simulation code: If enough time has passed perform a simulation step.
    //

    if (time_stamp == 0) time_stamp = OSG::getTimeStamp();

    OSG::Time elapsed = OSG::getTimeStampMsecs(OSG::getTimeStamp() - time_stamp);

    if (elapsed > elapse_time_limit)
    {
        OSG::Matrix matSimulation;

        simulation_param += simulation_delta;
        if (simulation_param >= 1.f)
            simulation_param = 0.f;

        if (simulate_geometry)
        {
            std::size_t numCurves = geom_curves.size();

            OSG_ASSERT(numCurves == geom_trafos.size());

            for (std::size_t i = 0; i < numCurves; ++i)
            {
                matSimulation = geom_curves[i].getFrame(simulation_param);
                geom_trafos[i]->setMatrix(matSimulation);
            }
        }

        if (simulate_lights)
        {
            BOOST_FOREACH(Light& light, lights)
            {
                matSimulation = light.curve.getFrame(simulation_param, true);
                light.transform->setMatrix(matSimulation);

            }
        }

        time_stamp = OSG::getTimeStamp();
    }
}

//
// Cluster shading stage ...
//
void setup_cluster_shading_stage()
{
    if (cluster_shading_stage)
    {
        //
        // The multi light chunk must be known by the cluster shading stage
        //
        cluster_shading_stage->setMultiLightChunk(multi_light_chunk);

        //
        // Some values that determine the computational efficiency
        //
        cluster_shading_stage->setMaxLightIndexListSize (light_index_list_size);
        cluster_shading_stage->setMaxClusterLightCount  (1024);
        cluster_shading_stage->setBlockSize             (block_size);
        cluster_shading_stage->setTileSize              (tile_size);
        cluster_shading_stage->setNumClusterZ           (num_cluster_z);
        cluster_shading_stage->setNearPlaneOffset       (near_plane_offset);

        //
        // UBO fragment/compute shader binding points
        //
        cluster_shading_stage->setDispatchDataBindingPnt(1);
        cluster_shading_stage->setClusterDataBindingPnt (2);

        //
        // SSBO fragment/compute shader binding points
        //
        cluster_shading_stage->setLightBindingPnt                   (1);
        cluster_shading_stage->setAffectedLightIndexListBindingPnt  (2);
        cluster_shading_stage->setFrustumBindingPnt                 (3);
        cluster_shading_stage->setLightIndexListBindingPnt          (4);
        cluster_shading_stage->setLightIndexCounterBindingPnt       (5);

        //
        // Texture image fragment shader binding point
        //
        cluster_shading_stage->setLightGridBindingPnt(0);

        //
        // Misc. flags
        //
        cluster_shading_stage->setCalcFrustumsOnCPU ( Light::cpu_calc_frustums);
        cluster_shading_stage->setCullLighsOnCPU    ( Light::cpu_cull_lights);
        cluster_shading_stage->setDisabled          (!Light::use_light_index_list);
    }
}

void removeClusterShadingStage()
{
    OSG::GroupRefPtr group = OSG::Group::create();
    cluster_shading_node->setCore(group);

    cluster_shading_stage = NULL;
}

void createClusterShadingStage()
{
    if (!cluster_shading_stage)
    {
        cluster_shading_stage = OSG::ClusterShadingStage::create();
        setup_cluster_shading_stage();
    }

    if (cluster_shading_node)
        cluster_shading_node->setCore(cluster_shading_stage);
}

//
// HDR stage ...
//
void setup_hdr_stage()
{
    if (hdr_stage)
    {
        hdr_stage->setApplyGamma                (true);
        hdr_stage->setAccurateGamma             (true);

        hdr_stage->setAdjustLuminance           (false);

        hdr_stage->setPerformBloom              (false);
        hdr_stage->setBloomBackground           (false);
        
        hdr_stage->setForceBackground           (true);
        hdr_stage->setUse_ITU_R_BT_709          (true);
        hdr_stage->setMipmapLevel               (-1);

        hdr_stage->setTarget                    (OSG::HDR2Stage::COMPOSITE_TEXTURE);
        hdr_stage->setCarryDepth                (true);

        hdr_stage->setColorBufferInternalFormat (GL_RGBA16F);
        hdr_stage->setColorBufferPixelFormat    (GL_RGBA);
        hdr_stage->setColorBufferType           (GL_FLOAT);

        hdr_stage->setDepthBufferInternalFormat (GL_DEPTH24_STENCIL8);
        hdr_stage->setDepthBufferPixelFormat    (GL_DEPTH_STENCIL);
        hdr_stage->setDepthBufferType           (GL_UNSIGNED_INT_24_8);

        hdr_stage->setLumBufferInternalFormat   (GL_R32F);
        hdr_stage->setLumBufferPixelFormat      (GL_RED);
        hdr_stage->setLumBufferType             (GL_FLOAT);

        hdr_stage->setImageBufferInternalFormat (GL_RGB16F);
        hdr_stage->setImageBufferPixelFormat    (GL_RGB);
        hdr_stage->setImageBufferType           (GL_FLOAT);

        hdr_stage->setNumSamples                (0);

        hdr_stage->setBloomThreshold            (2.0f);
        hdr_stage->setBloomMagnitude            (0.0f);
        hdr_stage->setToneMappingMode           (OSG::HDR2Stage::REINHARD_TONE_MAPPING);
        hdr_stage->setExposure                  (0.0f);
        hdr_stage->setKeyValue                  (0.18f);
        hdr_stage->setAutoExposureMode          (OSG::HDR2Stage::MANUAL);
        hdr_stage->setWhiteLevel                (5.0f);
        hdr_stage->setFilmicShoulderStrenght    (0.15f);
        hdr_stage->setFilmicLinearStrength      (0.5f);
        hdr_stage->setFilmicLinearAngle         (0.1f);
        hdr_stage->setFilmicToeStrength         (0.2f);
        hdr_stage->setFilmicToeNumerator        (0.02f);
        hdr_stage->setFilmicToeDenominator      (0.3f);
        hdr_stage->setFilmicLinearWhite         (11.2f);
        hdr_stage->setSaturation                (1.0f);
        hdr_stage->setDragoBias                 (0.85f);
        hdr_stage->setTau                       (1.25f);
        hdr_stage->setNumTaps                   (4);
        hdr_stage->setBlurGaussSigma            (0.8f);
        hdr_stage->setUseLinChromCorrection     (true);
    }
}

void removeHDRStage()
{
    OSG::GroupRefPtr group = OSG::Group::create();
    hdr_node->setCore(group);

    hdr_stage = NULL;
}

void createHDRStage()
{
    if (!hdr_stage)
    {
        hdr_stage = OSG::HDR2Stage::create();
        setup_hdr_stage();
    }

    if (hdr_node)
        hdr_node->setCore(hdr_stage);
}

//
// Lights...
//
void deinitialize_lights()
{
    BOOST_FOREACH(const Light& light, lights)
    {
        scene_node->subChild(light.beacon);
    }

    lights.clear();
}

void initialize_lights(OSG::UInt32 num)   // helper to create lights
{
    deinitialize_lights();

    for (OSG::UInt32 i = 0; i < num; ++i)
    {
        
        int n = classic_die();
        Light::Type type;

        switch (n)
        {
        case 1:
        case 2:
            type = OSG::MultiLight::POINT_LIGHT;
            break;
        case 3:
        case 4:
            type = OSG::MultiLight::SPOT_LIGHT;
            break;
        case 5:
        case 6:
            type = OSG::MultiLight::CINEMA_LIGHT;
            break;
        }

        lights.push_back(Light::create_light(type));
        
        lights[i].create_light_geometry(i+1);

        scene_node->addChild(lights[i].beacon);
    }

    if (Light::add_dir_test_lights)
    {
        lights.push_back(Light::create_light(OSG::MultiLight::DIRECTIONAL_LIGHT, 0));
        lights.push_back(Light::create_light(OSG::MultiLight::DIRECTIONAL_LIGHT, 1));
    }
}

void change_spot_dir_lights()
{
    for (std::size_t i = 0; i < lights.size(); ++i)
    {
        Light& light = lights[i];

        switch (Light::force_spot_dir)
        {
            case 0: light.direction = dice_unit_vector();  break;
            case 1: light.direction = OSG::Vec3f(0, 0,-1); break;
            case 2: light.direction = OSG::Vec3f(1, 0, 0); break;
            case 3: light.direction = OSG::Vec3f(0,-1, 0); break;
            case 4: light.direction = OSG::Vec3f(1, 0,-1); break;
            case 5: light.direction = OSG::Vec3f(1,-1,-1); break;
            case 6:
            {
                static bool increase_flag = true;

                light.direction = Light::dir_test_case_6;
                light.direction.normalize();

                OSG::Vec3f e1(1,0,-1);
                OSG::Vec3f e2(0,0,-1);

                if (Light::dir_test_case_6.equals(e1, OSG::Eps))
                    increase_flag = false;
                if (Light::dir_test_case_6.equals(e2, OSG::Eps))
                    increase_flag = true;

                if (increase_flag)
                    Light::dir_test_case_6 += OSG::Vec3f(0.1f, 0.f, 0.f);
                else
                    Light::dir_test_case_6 -= OSG::Vec3f(0.1f, 0.f, 0.f);
            }
            break;
            case 7:
            {
                static bool increase_flag = true;

                light.direction = Light::dir_test_case_7;
                light.direction.normalize();

                OSG::Vec3f e1(1,-1,-1);
                OSG::Vec3f e2(0,0,-1);

                if (Light::dir_test_case_7.equals(e1, OSG::Eps))
                    increase_flag = false;
                if (Light::dir_test_case_7.equals(e2, OSG::Eps))
                    increase_flag = true;

                if (increase_flag)
                    Light::dir_test_case_7 += OSG::Vec3f(0.1f, -0.1f, 0.f);
                else
                    Light::dir_test_case_7 -= OSG::Vec3f(0.1f, -0.1f, 0.f);
            }
            break;

            case 8:
            {
                static bool increase_flag = true;

                light.direction = Light::dir_test_case_8;
                light.direction.normalize();

                OSG::Vec3f e1(0,-1, 0);
                OSG::Vec3f e2(0, 0,-1);

                if (Light::dir_test_case_8.equals(e1, OSG::Eps))
                    increase_flag = false;
                if (Light::dir_test_case_8.equals(e2, OSG::Eps))
                    increase_flag = true;

                if (increase_flag)
                    Light::dir_test_case_8 += OSG::Vec3f(0.f, -0.1f, 0.1f);
                else
                    Light::dir_test_case_8 -= OSG::Vec3f(0.f, -0.1f, 0.1f);
            }
            break;

            case 9:
            {
            }
            break;
        }

        lights[i].create_light_geometry(OSG::UInt32(i+1));
    }
}

Light Light::create_light(
    Type e,                         // type of the light
    OSG::Int32 test_dir_light_type) // for special testing directional lights
{
    Light l(e);

    l.beacon = OSG::makeCoredNode<OSG::Transform>(&l.transform);
    l.transform->setMatrix(OSG::Matrix::identity());

    OSG::Real32 L = box_factor * world_size;

    switch (Light::force_spot_dir)
    {
        case 0: l.direction = dice_unit_vector();  break;
        case 1: l.direction = OSG::Vec3f(0, 0,-1); break;
        case 2: l.direction = OSG::Vec3f(1, 0, 0); break;
        case 3: l.direction = OSG::Vec3f(0,-1, 0); break;
        case 4: l.direction = OSG::Vec3f(1, 0,-1); break;
        case 5: l.direction = OSG::Vec3f(1,-1,-1); break;
        case 6: l.direction = OSG::Vec3f(0, 0,-1); break;
        case 7: l.direction = OSG::Vec3f(0, 0,-1); break;
        case 8: l.direction = OSG::Vec3f(0, 0,-1); break;
        case 9: break;
    }

    Light::dir_test_case_6 = OSG::Vec3f(0,0,-1);
    Light::dir_test_case_7 = OSG::Vec3f(0,0,-1);
    Light::dir_test_case_8 = OSG::Vec3f(0,0,-1);

    l.color.setRandom();
    l.intensity   = max_light_power * small_die();
    l.rangeCutOff = L * light_range_die();

    switch (e)
    {
        case OSG::MultiLight::POINT_LIGHT:
        {
        }
        break;

        case OSG::MultiLight::DIRECTIONAL_LIGHT:
        {
            if (Light::add_dir_test_lights)
            {
                if (test_dir_light_type == 0)
                    l.direction = OSG::Vec3f(0,0,-1);
                if (test_dir_light_type == 1)
                    l.direction = OSG::Vec3f(0,0,1);

                l.intensity = 0.1f;
            }
        }
        break;

        case OSG::MultiLight::SPOT_LIGHT:
        {
            l.spotlightAngle = spot_die();
        }
        break;

        case OSG::MultiLight::CINEMA_LIGHT:
        {
            l.innerSuperEllipsesWidth  = light_ellipsis_radius_die();
            l.innerSuperEllipsesHeight = light_ellipsis_radius_die();

            float f = light_ellipsis_radius_ratio_die();

            l.outerSuperEllipsesWidth  = f * l.innerSuperEllipsesWidth;
            l.outerSuperEllipsesHeight = f * l.innerSuperEllipsesHeight;

            int n = classic_die();
            switch (n)
            {
            case 1:
            case 2:
                l.superEllipsesRoundness = light_ellipsis_roundness_die1();
                break;
            case 3:
            case 4:
                l.superEllipsesRoundness = light_ellipsis_roundness_die2();
                break;
            case 5:
            case 6:
                l.superEllipsesRoundness = light_ellipsis_roundness_die3();
                break;
            }

            l.superEllipsesTwist = light_ellipsis_twist_die();

            //std::cout << "d = (" << l.direction.x() << ", " << l.direction.y() << ", " << l.direction.z() << ")" << std::endl;
            //std::cout << "a = " << l.innerSuperEllipsesWidth  << std::endl;
            //std::cout << "b = " << l.innerSuperEllipsesHeight << std::endl;
            //std::cout << "A = " << l.outerSuperEllipsesWidth  << std::endl;
            //std::cout << "B = " << l.outerSuperEllipsesHeight << std::endl;
            //std::cout << "r = " << l.superEllipsesRoundness   << std::endl;
            //std::cout << "w = " << l.superEllipsesTwist       << std::endl;
        }
        break;

        default:
            break;
    }

    return l;
}

void Light::create_light_geometry(OSG::UInt32 material_idx)
{
    if (!beacon) return;

    beacon->clearChildren();

    Material mat;
    mat.emissive = color;
    mat.opacity  = 0.7f;

    materials[material_idx] = mat;

    OSG::ChunkMaterialRefPtr geomState = OSG::ChunkMaterial::create();

    OSG::Real32 R = rangeCutOff;
    
    if (!correct_light_geometry)
        R = 0.5;

    switch (type)
    {
        case OSG::MultiLight::POINT_LIGHT:
        {
            OSG::GeometryRefPtr  geometry = OSG::makeSphereGeo(3, R);
            OSG::NodeRefPtr      node     = OSG::makeNodeFor(geometry);

            GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point 
            geomState->addChunk(shader_var_chunk);                      // block binding point

            geometry->setMaterial(geomState);

            beacon->addChild(node);

            //
            // Test: Add mini sphere at the origin of the point light sphere
            //
            //{
            //    OSG::GeometryRefPtr  geometry = OSG::makeSphereGeo(6, 0.1);
            //    OSG::NodeRefPtr      node     = OSG::makeNodeFor(geometry);

            //    GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            //    OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            //    geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point 
            //    geomState->addChunk(shader_var_chunk);                      // block binding point

            //    geometry->setMaterial(geomState);

            //    beacon->addChild(node);
            //}
        }
        break;

        case OSG::MultiLight::DIRECTIONAL_LIGHT:
        {
        }
        break;

        case OSG::MultiLight::SPOT_LIGHT:
        {
            GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point
            geomState->addChunk(shader_var_chunk);                      // block binding point

            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = OSG::makeSpotGeo(h, OSG::osgDegree2Rad(spotlightAngle), 24, 24);
            geometry->setMaterial(geomState);

            OSG::TransformRefPtr coneTrans = OSG::Transform::create();

            OSG::Matrix rotMat;
            OSG::MatrixRotateTowards(rotMat, OSG::Vec3f(0.f, 1.f, 0.f), direction);
            coneTrans->setMatrix(rotMat);

            OSG::NodeRefPtr coneTransNode  = OSG::makeNodeFor(coneTrans);
            OSG::NodeRefPtr coneNode       = OSG::makeNodeFor(geometry);

            beacon->addChild(coneTransNode);
            coneTransNode->addChild(coneNode);

            //
            // Create a help line to visualize the spot hit point on the wall
            //
            if (Light::show_spot_dir_line)
            {
                OSG::GeometryRefPtr line_geometry = OSG::makeCylinderGeo(30, 0.1f, 24, true, true, true );
                line_geometry->setMaterial(geomState);
            
                OSG::TransformRefPtr line_translation = OSG::Transform::create();
                OSG::Matrix matLineTrans;
                matLineTrans.setTranslate(OSG::Vec3f(0,-15,0));
                line_translation->setMatrix(matLineTrans);
            
                OSG::TransformRefPtr line_rotation = OSG::Transform::create();
                OSG::Matrix matLineRot;
                matLineRot.setRotate(OSG::Quaternion(OSG::Vec3f(1,0,0), OSG::Pi));
                line_rotation->setMatrix(matLineRot);
            
                OSG::NodeRefPtr lineRotationNode    = OSG::makeNodeFor(line_rotation);
                OSG::NodeRefPtr lineTranslationNode = OSG::makeNodeFor(line_translation);
                OSG::NodeRefPtr lineGeometryNode    = OSG::makeNodeFor(line_geometry);
                coneTransNode      ->addChild(lineRotationNode);
                lineRotationNode   ->addChild(lineTranslationNode);
                lineTranslationNode->addChild(lineGeometryNode);
            }
        }
        break;

        case OSG::MultiLight::CINEMA_LIGHT:
        {
            GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point
            geomState->addChunk(shader_var_chunk);                      // block binding point

            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = OSG::makeCinemaGeo(
                                                outerSuperEllipsesWidth,
                                                outerSuperEllipsesHeight,
                                                superEllipsesRoundness,
                                                OSG::osgDegree2Rad(superEllipsesTwist),
                                                h, 48, 48);
            geometry->setMaterial(geomState);

            OSG::Matrix matLSFromWS;

            OSG::Matrix matLightPos;
            matLightPos.setTranslate(position);

            OSG::Matrix matLightDir;
            OSG::Quaternion rotLightDir(OSG::Vec3f(0.f, 0.f, 1.f), -direction);
            matLightDir.setRotate(rotLightDir);

            matLSFromWS.mult  (matLightPos);
            matLSFromWS.mult  (matLightDir);

            OSG::Matrix matRot;
            matRot.setRotate(OSG::Quaternion(OSG::Vec3f(1,0,0), -0.5*OSG::Pi));

            matLSFromWS.mult(matRot);

            OSG::TransformRefPtr coneTrans = OSG::Transform::create();
            coneTrans->setMatrix(matLSFromWS);

            OSG::NodeRefPtr coneTransNode  = OSG::makeNodeFor(coneTrans);
            OSG::NodeRefPtr coneNode       = OSG::makeNodeFor(geometry);

            beacon->addChild(coneTransNode);
            coneTransNode->addChild(coneNode);

            //
            // Create a help line to visualize the spot hit point on the wall
            //
            if (Light::show_spot_dir_line)
            {
                OSG::GeometryRefPtr line_geometry = OSG::makeCylinderGeo(30, 0.1f, 24, true, true, true );
                line_geometry->setMaterial(geomState);
            
                OSG::TransformRefPtr line_translation = OSG::Transform::create();
                OSG::Matrix matLineTrans;
                matLineTrans.setTranslate(OSG::Vec3f(0,-15,0));
                line_translation->setMatrix(matLineTrans);
            
                OSG::TransformRefPtr line_rotation = OSG::Transform::create();
                OSG::Matrix matLineRot;
                matLineRot.setRotate(OSG::Quaternion(OSG::Vec3f(1,0,0), OSG::Pi));
                line_rotation->setMatrix(matLineRot);
            
                OSG::NodeRefPtr lineRotationNode    = OSG::makeNodeFor(line_rotation);
                OSG::NodeRefPtr lineTranslationNode = OSG::makeNodeFor(line_translation);
                OSG::NodeRefPtr lineGeometryNode    = OSG::makeNodeFor(line_geometry);
                coneTransNode      ->addChild(lineRotationNode);
                lineRotationNode   ->addChild(lineTranslationNode);
                lineTranslationNode->addChild(lineGeometryNode);
            }
        }
        break;

        default:
            break;
    }

    OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
    polygonChunk->setFrontMode(GL_SMOOTH);
    polygonChunk->setBackMode(GL_SMOOTH);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);

    if (mat.opacity < 1.f)
    {
        polygonChunk->setCullFace(GL_BACK);

        OSG::BlendChunkRefPtr blendChunk = OSG::BlendChunk::create();
        blendChunk->setSrcFactor (GL_SRC_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        geomState->addChunk(blendChunk);
        geomState->setTransparencyMode(OSG::Material::TransparencyForceTransparent);

        OSG::TwoSidedLightingChunkRefPtr twoSidedLightingChunk = OSG::TwoSidedLightingChunk::create();
        geomState->addChunk(twoSidedLightingChunk);

    } else {
        polygonChunk->setCullFace(GL_BACK);
        geomState->setTransparencyMode(OSG::Material::TransparencyForceOpaque);
    }

    geomState->addChunk(polygonChunk);
}

OSG::NodeTransitPtr createBox()
{
    OSG::NodeRefPtr boxRoot = OSG::makeCoredNode<OSG::Group>();

    OSG::Real32 L = box_factor * world_size;
    OSG::GeometryRefPtr boxPlane  = OSG::makePlaneGeo(2.f*L, 2.f*L, 128, 128);

    OSG::NodeRefPtr boxBottom = OSG::makeNodeFor(boxPlane);
    OSG::NodeRefPtr boxLeft   = OSG::makeNodeFor(boxPlane);
    OSG::NodeRefPtr boxRight  = OSG::makeNodeFor(boxPlane);
    OSG::NodeRefPtr boxFar    = OSG::makeNodeFor(boxPlane);

    OSG::TransformRefPtr boxBottomTrans = OSG::Transform::create();
    OSG::TransformRefPtr boxLeftTrans   = OSG::Transform::create();
    OSG::TransformRefPtr boxRightTrans  = OSG::Transform::create();
    OSG::TransformRefPtr boxFarTrans    = OSG::Transform::create();

    OSG::Matrix matBottom, matLeft, matRight, matFar;

    matBottom.setTransform(OSG::Vec3f(0.f,  -L, 0.f), OSG::Quaternion( OSG::Vec3f(1, 0, 0), OSG::osgDegree2Rad(270.f)));
    matLeft  .setTransform(OSG::Vec3f( -L, 0.f, 0.f), OSG::Quaternion( OSG::Vec3f(0, 1, 0), OSG::osgDegree2Rad(90.f)));
    matRight .setTransform(OSG::Vec3f(  L, 0.f, 0.f), OSG::Quaternion( OSG::Vec3f(0, 1, 0), OSG::osgDegree2Rad(270.f)));
    matFar   .setTransform(OSG::Vec3f(0.f, 0.f,  -L), OSG::Quaternion( OSG::Vec3f(0, 0, 1), OSG::osgDegree2Rad(  0.f)));

    boxBottomTrans ->setMatrix(matBottom);
    boxLeftTrans   ->setMatrix(matLeft);
    boxRightTrans  ->setMatrix(matRight);
    boxFarTrans    ->setMatrix(matFar);

    OSG::NodeRefPtr boxBottomTransNode = OSG::makeNodeFor(boxBottomTrans);
    OSG::NodeRefPtr boxLeftTransNode   = OSG::makeNodeFor(boxLeftTrans);
    OSG::NodeRefPtr boxRightTransNode  = OSG::makeNodeFor(boxRightTrans);
    OSG::NodeRefPtr boxFarTransNode    = OSG::makeNodeFor(boxFarTrans);

    boxBottomTransNode ->addChild(boxBottom);
    boxLeftTransNode   ->addChild(boxLeft);
    boxRightTransNode  ->addChild(boxRight);
    boxFarTransNode    ->addChild(boxFar);

    boxRoot->addChild(boxBottomTransNode);
    boxRoot->addChild(boxLeftTransNode);
    boxRoot->addChild(boxRightTransNode);
    boxRoot->addChild(boxFarTransNode);

    GeomState geom; geom.material_index = 0;                        // grey box material index
    OSG::ChunkMaterialRefPtr geomState = OSG::ChunkMaterial::create();
    OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
    geomState->addChunk(uboGeomState, geom_binding_point);          // buffer binding point
    geomState->addChunk(shader_var_chunk);                          // block binding point

    OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
    polygonChunk->setFrontMode(GL_SMOOTH);
    polygonChunk->setBackMode(GL_SMOOTH);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);
    polygonChunk->setCullFace(GL_NONE);
    geomState->addChunk(polygonChunk);

    geomState->setTransparencyMode(OSG::Material::TransparencyForceOpaque);

    OSG::TwoSidedLightingChunkRefPtr twoSidedLightingChunk = OSG::TwoSidedLightingChunk::create();
    geomState->addChunk(twoSidedLightingChunk);

    boxPlane->setMaterial(geomState);

    return OSG::NodeTransitPtr(boxRoot);
}

OSG::NodeTransitPtr createGeometry()
{
    int idx = geom_idx_die();

    OSG::GeometryRefPtr geometry;

    switch (idx)
    {
        case 0: // cone
            geometry = OSG::makeConeGeo(3.f * small_die(), 1.f * small_die(), 24, true, true);
            break;
        case 1: // box
            geometry = OSG::makeBoxGeo(3.f * small_die(), 3.f * small_die(), 3.f * small_die(),  1, 1, 1);
            break;
        case 2: // cylinder
            geometry = OSG::makeCylinderGeo(3.f * small_die(), .3f, 24, true, true, true );
            break;
        case 3: // sphere
            geometry = OSG::makeSphereGeo(6, 3.f * small_die());
            break;
        case 4: // torus
            geometry = OSG::makeTorusGeo(0.6f * small_die(), 2.f * small_die(), 24, 36);
            break;
        case 5: // ellipsoide
            geometry = OSG::makeLatLongEllipsoidGeo(24, 36, 2.f * small_die(), 1.f * small_die());
            break;
        case 6: // frustum
            geometry = OSG::makeConicalFrustumGeo(2.f * small_die(), 2.f * small_die(), 2.f * small_die(), 6, true, true, true);
            break;
        case 7: // teapot
            geometry = OSG::makeTeapotGeo(24, 1.f * small_die());
            break;
    }

    OSG::NodeRefPtr geomNode = OSG::makeNodeFor(geometry);

    OSG::TransformRefPtr trafoCore = OSG::Transform::create();    
    OSG::NodeRefPtr transNode = OSG::makeNodeFor(trafoCore);
    transNode->addChild(geomNode);
  
    GeomState geom; geom.material_index = material_idx_die();
    OSG::ChunkMaterialRefPtr geomState = OSG::ChunkMaterial::create();
    OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
    geomState->addChunk(uboGeomState, geom_binding_point);         // buffer binding point
    geomState->addChunk(shader_var_chunk);                         // block binding point

    OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
    polygonChunk->setFrontMode(GL_SMOOTH);
    polygonChunk->setBackMode(GL_SMOOTH);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);

    OSG::Real32 opacity = materials[geom.material_index].opacity;
    if (opacity < 1.f)
    {
        polygonChunk->setCullFace(GL_BACK);

        OSG::BlendChunkRefPtr blendChunk = OSG::BlendChunk::create();
        blendChunk->setSrcFactor (GL_SRC_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        geomState->addChunk(blendChunk);
        geomState->setTransparencyMode(OSG::Material::TransparencyForceTransparent);

        OSG::TwoSidedLightingChunkRefPtr twoSidedLightingChunk = OSG::TwoSidedLightingChunk::create();
        geomState->addChunk(twoSidedLightingChunk);

    } else {
        polygonChunk->setCullFace(GL_BACK);
        geomState->setTransparencyMode(OSG::Material::TransparencyForceOpaque);
    }

    geomState->addChunk(polygonChunk);

    geometry->setMaterial(geomState);

    geom_nodes.push_back(transNode);
    geom_trafos.push_back(trafoCore);
    ubo_geom_states.push_back(uboGeomState);

    geom_curves.push_back(OSG::SmoothCubicBezierSpline(dice_knots(true)));

    return OSG::NodeTransitPtr(transNode);
}

//
// forward declaration so we can have the interesting stuff upfront
//
int  setupGLUT  (int *argc, char *argv[]);
void print_state();
void print_help();
void releaseGLUT();

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
        // Because we animate the lights by simple geometry, the lights initialization must be happens
        // after the creation of the 'shader_var_chunk' and after the creation of the scene node that
        // actually contains the geometry. Additionally, it must happens before we call 'create_light_state', 
        // since here we do need the already defined lights.
        //

        cluster_shading_node       = OSG::makeCoredNode<OSG::Group>();
        hdr_node                   = OSG::makeCoredNode<OSG::Group>();

        //
        // The block binding is added to each ChunkMaterial in order to provide the state
        // shader uniform block for the geometery shown in the scene
        //
        shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
        shader_var_chunk->addUniformBlock("GeomState", geom_binding_point);

        //
        // The scene does contain all visible rendering. It will be append to the hdr node.
        //
        scene_node = OSG::makeCoredNode<OSG::Group>();

        initialize_lights(init_num_lights);

        //
        // create shader storage buffer objects and corresponding materials
        //
        ssbo_material_database = create_material_database_state(materials);
        multi_light_chunk      = create_light_state(lights);

        hdr_node            ->addChild(cluster_shading_node);
        cluster_shading_node->addChild(scene_node);

        //
        // The scene graph
        //
        mgr->setRoot(hdr_node);

        if (use_ortho_camera)
        {
            OSG::OrthographicCameraRefPtr orthoCamera = OSG::OrthographicCamera::create();
            mgr->setCamera(orthoCamera);
        }

        createHDRStage();
        createClusterShadingStage();

        //
        // create the shader program
        //
        OSG::ShaderProgramChunkRefPtr progChunk  = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
                                     frag_shader = OSG::ShaderProgram::createFragmentShader();

         vertShader->setProgram(get_vp_program());
        frag_shader->setProgram(get_fp_program());

        frag_shader->addOSGVariable("OSGViewMatrix");

        //
        // binding the shader storage block to a buffer binding point can be performed 
        // either by calling the shaders's addShaderStorageBlock method or by
        // adding a 'buffer block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        frag_shader->addShaderStorageBlock("Materials",
                                           material_binding_point);

        progChunk->addShader( vertShader);
        progChunk->addShader(frag_shader);

        OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
        polygonChunk->setFrontMode(GL_FILL);
        polygonChunk->setBackMode(GL_FILL);
        polygonChunk->setCullFace(GL_BACK);

        OSG::DepthChunkRefPtr depthChunk = OSG::DepthChunk::create();
        depthChunk->setEnable(true);

        OSG::ChunkMaterialRefPtr progState = OSG::ChunkMaterial::create();
        progState->addChunk(ssbo_material_database, material_binding_point);
        
        progState->addChunk(progChunk);
        progState->addChunk(polygonChunk);
        progState->addChunk(depthChunk);

        scene_node->addChild(createBox());

        cluster_geometry_root_node = OSG::makeCoredNode<OSG::Group>();
        scene_node->addChild(cluster_geometry_root_node);

        for (OSG::Int32 i = 0; i < init_num_geometries; ++i)
            scene_node->addChild(createGeometry());

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(progState);
        scene_node->setCore(mgrp);

        OSG::commitChanges();

        print_state();
    
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
    if (!mgr) return;

    //
    // Simulation code
    //
    update_simulation();

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

            frag_shader = NULL;

            scene_node = NULL;
            cluster_geometry_root_node = NULL;

            cluster_shading_stage = NULL;
            cluster_shading_node = NULL;

            hdr_stage = NULL;
            hdr_node = NULL;

            ssbo_material_database = NULL;

            multi_light_chunk = NULL;
            shader_var_chunk = NULL;

            geom_nodes.clear();
            geom_trafos.clear();
            geom_curves.clear();

            ubo_geom_states.clear();

            materials.clear();
            lights.clear();

            releaseGLUT();

            OSG::osgExit();
            exit(0);
        }
        break;

        case 32:        // Space
        {
            simulate_geometry = !simulate_geometry;
            std::cout << "simulate_geometry = " << simulate_geometry << std::endl;
        }
        break;

        case '1':
        {
            initialize_lights(1);
            update_light_state(multi_light_chunk, lights);
            update_material_database_state(ssbo_material_database, materials);
            glutPostRedisplay();
        }
        break;

        case '2':
        {
            if (lights.size() > 1)
            {
                OSG::UInt32 num = static_cast<OSG::UInt32>(lights.size() / 2);
                initialize_lights(num);
                update_light_state(multi_light_chunk, lights);
                update_material_database_state(ssbo_material_database, materials);

                std::cout << "number if lights = " << num << std::endl;

                glutPostRedisplay();
            }
            else
            {
                std::cout << "minimal number if lights reached!" << std::endl;
            }
        }
        break;

        case '3':
        {
            if (lights.size() <= max_num_lights)
            {
                OSG::UInt32 num = static_cast<OSG::UInt32>(lights.size() * 2);
                initialize_lights(num);
                update_light_state(multi_light_chunk, lights);
                update_material_database_state(ssbo_material_database, materials);

                std::cout << "number if lights = " << num << std::endl;

                glutPostRedisplay();
            }
            else
            {
                std::cout << "maximal number if lights reached!" << std::endl;
            }

        }
        break;

        case '4':
        {
            if (geom_nodes.size() > 1)
            {
                OSG::UInt32 num = static_cast<OSG::UInt32>(geom_nodes.size() / 2);

                BOOST_FOREACH(OSG::Node* node, geom_nodes)
                    scene_node->subChild(node);

                geom_nodes.clear();
                geom_trafos.clear();
                geom_curves.clear();
                ubo_geom_states.clear();

                for (OSG::UInt32 i = 0; i < num; ++i)
                    scene_node->addChild(createGeometry());

                std::cout << "number if geometries = " << num << std::endl;

                glutPostRedisplay();
            }
            else
            {
                std::cout << "minimal number if geometries reached!" << std::endl;
            }
        }
        break;

        case '5':
        {
            if (geom_nodes.size() <= max_num_geometries)
            {
                OSG::UInt32 num = static_cast<OSG::UInt32>(geom_nodes.size() * 2);

                BOOST_FOREACH(OSG::Node* node, geom_nodes)
                    scene_node->subChild(node);

                geom_nodes.clear();
                geom_trafos.clear();
                geom_curves.clear();
                ubo_geom_states.clear();

                for (OSG::UInt32 i = 0; i < num; ++i)
                    scene_node->addChild(createGeometry());

                std::cout << "number if geometries = " << num << std::endl;

                glutPostRedisplay();
            }
            else
            {
                std::cout << "maximal number if geometries reached!" << std::endl;
            }
        }
        break;

        case 'a':
        {
            Light::add_dir_test_lights = !Light::add_dir_test_lights;
            std::cout << "Light::add_dir_test_lights = " << Light::add_dir_test_lights << std::endl;

            initialize_lights(1);
            update_light_state(multi_light_chunk, lights);
            update_material_database_state(ssbo_material_database, materials);
            glutPostRedisplay();
        }
        break;

        case 'b':
        {
            Light::correct_light_geometry = !Light::correct_light_geometry;
            std::cout << "Light::correct_light_geometry = " << Light::correct_light_geometry << std::endl;

            for (std::size_t i = 0; i < lights.size(); ++i)
            {
                Light& light = lights[i];
                light.create_light_geometry(OSG::UInt32(i+1));
            }

            glutPostRedisplay();
        }
        break;

        case 'c':
        {
            Light::cpu_cull_lights = !Light::cpu_cull_lights;
            std::cout << "Light::cpu_cull_lights = " << Light::cpu_cull_lights << std::endl;

            cluster_shading_stage->setCullLighsOnCPU(Light::cpu_cull_lights);

            if (Light::cpu_cull_lights && !Light::cpu_calc_frustums)
            {
                Light::cpu_calc_frustums = true;
                std::cout << "Light::cpu_calc_frustums = " << Light::cpu_calc_frustums << std::endl;
                cluster_shading_stage->setCalcFrustumsOnCPU(Light::cpu_calc_frustums);
            }
            glutPostRedisplay();
        }
        break;

        case 'C':
        {
            Light::cpu_calc_frustums = !Light::cpu_calc_frustums;
            std::cout << "Light::cpu_calc_frustums = " << Light::cpu_calc_frustums << std::endl;

            cluster_shading_stage->setCalcFrustumsOnCPU(Light::cpu_calc_frustums);

            if (Light::cpu_cull_lights && !Light::cpu_calc_frustums)
            {
                Light::cpu_cull_lights = false;
                std::cout << "Light::cpu_cull_lights = " << Light::cpu_cull_lights << std::endl;
                cluster_shading_stage->setCullLighsOnCPU(Light::cpu_cull_lights);
            }
            glutPostRedisplay();
        }
        break;

        case 'e':
        {
            simulation_delta *= 2.f;
        }
        break;

        case 'E':
        {
            simulation_delta /= 2.f;
        }
        break;

        case 'h':
        {
            OSG::HDR2Stage* core = dynamic_cast<OSG::HDR2Stage*>(hdr_node->getCore());
            if (core)
            {
                removeHDRStage();

                std::cout << "HDR is off" << std::endl;
            }
            else
            {
                createHDRStage();

                std::cout << "HDR is on" << std::endl;
            }

            glutPostRedisplay();
        }
        break;

        case 'i':
        {
            BOOST_FOREACH(Light& light, lights)
                light.intensity *= 1.2f;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'I':
        {
            BOOST_FOREACH(Light& light, lights)
                if (light.rangeCutOff / intensityFactor >= OSG::Eps)
                    light.intensity /= intensityFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'l':
        {
            simulate_lights = !simulate_lights;
            std::cout << "simulate_lights = " << simulate_lights << std::endl;
        }
        break;

        case 'm':
        {
            BOOST_FOREACH(OSG::MultiPropertyUBOChunk* uboGeomState, ubo_geom_states)
            {
                GeomState geom; geom.material_index = material_idx_die();
                update_geometry_material_state(uboGeomState, geom);
            }

            glutPostRedisplay();
        }
        break;

        case 'o':
        {
            elapse_time_limit *= 2.f;
        }
        break;

        case 'O':
        {
            elapse_time_limit /= 2.f;
        }
        break;

        case 'p':
        {
            for (std::size_t i = 0; i < lights.size(); ++i)
            {
                Light& light = lights[i];

                light.rangeCutOff *= rangeFactor;
                light.create_light_geometry(OSG::UInt32(i+1));
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'P':
        {
            for (std::size_t i = 0; i < lights.size(); ++i)
            {
                Light& light = lights[i];

                if (light.rangeCutOff / rangeFactor >= OSG::Eps)
                {
                    light.rangeCutOff /= rangeFactor;
                    light.create_light_geometry(OSG::UInt32(i+1));
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'r':
        {
            initialize_lights(init_num_lights);
            update_light_state(multi_light_chunk, lights);
            update_material_database_state(ssbo_material_database, materials);

            simulation_delta  = 0.0001f;
            elapse_time_limit = 10.f;

            simulate_geometry = true;
            simulate_lights   = true;

            std::cout << "example resetted" << std::endl;

            glutPostRedisplay();
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;

        case 't':
        {
            Light::use_light_index_list = !Light::use_light_index_list;
            std::cout << "Light::use_light_index_list = " << Light::use_light_index_list << std::endl;
            cluster_shading_stage->setDisabled(!Light::use_light_index_list);
            glutPostRedisplay();
        }
        break;

        case 'u':
        {
            Light::show_spot_dir_line = !Light::show_spot_dir_line;
            std::cout << "Light::show_spot_dir_line = " << Light::show_spot_dir_line << std::endl;

            for (std::size_t i = 0; i < lights.size(); ++i)
            {
                Light& light = lights[i];
                light.create_light_geometry(OSG::UInt32(i+1));
            }

            glutPostRedisplay();
        }
        break;

        case 'U':
        {
            Light::force_spot_dir += 1;
            if (Light::force_spot_dir > 9)
                Light::force_spot_dir = 0;

            std::cout << "Light::force_spot_dir = ";

             switch (Light::force_spot_dir)
             {
                case 0: std::cout << "dice";  break;
                case 1: std::cout << "(0, 0,-1)"; break;
                case 2: std::cout << "(1, 0, 0)"; break;
                case 3: std::cout << "(0,-1, 0)"; break;
                case 4: std::cout << "(1, 0,-1)"; break;
                case 5: std::cout << "(1,-1,-1)"; break;
                case 6: std::cout << "from (0,0,-1) to (1,0,-1)"; break;
                case 7: std::cout << "from (0,0,-1) to (1,-1,-1)"; break;
                case 8: std::cout << "from (0,0,-1) to (0,-1, 0)"; break;
                case 9: std::cout << "recreate"; break;
             }
            
            std::cout << std::endl;
        }
        break;

        case 'x':
        {
            change_spot_dir_lights();
            update_light_state(multi_light_chunk, lights);
            update_material_database_state(ssbo_material_database, materials);
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
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutKeyboardFunc(NULL);
    glutIdleFunc(NULL);
}

void print_state()
{
    std::cout << "simulate_geometry = " << simulate_geometry << std::endl;
    std::cout << "simulate_lights = " << simulate_lights << std::endl;
    std::cout << "number if lights = " << lights.size() << std::endl;
    std::cout << "number if geometries = " << geom_nodes.size() << std::endl;
    std::cout << "Light::use_light_index_list = " << Light::use_light_index_list << std::endl;
    std::cout << "Light::add_dir_test_lights = " << Light::add_dir_test_lights << std::endl;
    std::cout << "Light::correct_light_geometry = " << Light::correct_light_geometry << std::endl;
    std::cout << "Light::show_spot_dir_line = " << Light::show_spot_dir_line << std::endl;
    std::cout << "Light::cpu_cull_lights = " << Light::cpu_cull_lights << std::endl;
    std::cout << "Light::cpu_calc_frustums = " << Light::cpu_calc_frustums << std::endl;
    std::cout << "HDR is " << (dynamic_cast<OSG::HDR2Stage*>(hdr_node->getCore()) != NULL ? "on" : "off") << std::endl;
    std::cout << "visualize_frustum = " << visualize_frustum << std::endl;
}

void print_help()
{
    std::cout << "Esc   : quit example" << std::endl;
    std::cout << "Space : toogle geometry simulation on/off" << std::endl;
    std::cout << "1     : only one light" << std::endl;
    std::cout << "2     : half number of lights" << std::endl;
    std::cout << "3     : double number of lights" << std::endl;
    std::cout << "4     : half number of geometry objects" << std::endl;
    std::cout << "5     : double number of geometry objects" << std::endl;
    std::cout << "a     : add directional test lights" << std::endl;
    std::cout << "b     : show correct light geometry" << std::endl;
    std::cout << "c     : cull lights on cpu" << std::endl;
    std::cout << "C     : calc frustums on cpu" << std::endl;
    std::cout << "e/E   : speed up/down simulation" << std::endl;
    std::cout << "h     : toogle HDR stage usage on/off" << std::endl;
    std::cout << "i/I   : increase/decrease light intensity" << std::endl;
    std::cout << "l     : toogle light simulation on/off" << std::endl;
    std::cout << "m     : assign new color to geometry" << std::endl;
    std::cout << "o/O   : double/half simulation time interval" << std::endl;
    std::cout << "p/P   : increase/decrease light range" << std::endl;
    std::cout << "r     : reset the example" << std::endl;
    std::cout << "s     : toogle statistics on/off" << std::endl;
    std::cout << "t     : toogle usage of cluster shading on/off" << std::endl;
    std::cout << "u     : toggle spot direction line on/off" << std::endl;
    std::cout << "U     : toggle special spot direction cases" << std::endl;
    std::cout << "x     : recreate the lights with current spot dir case" << std::endl;
}

// ============================================================================
//
// Part: dice_knots helper implementation
//
// ============================================================================

typedef boost::tuples::tuple<int, int, int> index_t;

struct index_hash_t : public std::unary_function<index_t, std::size_t>
{
    std::size_t operator()(const index_t& v) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.get<0>());
        boost::hash_combine(seed, v.get<1>());
        boost::hash_combine(seed, v.get<2>());
        return seed;
    }
};

std::vector<OSG::Pnt3f> dice_knots(bool close_curve)
{
    //
    // idea: sample a number if different cube boxes from the scene and
    //       take randomly one point from each cube. That guarantees that
    //       the knot points do not clump and that they are all unequal.
    //
    namespace tp = boost::tuples;

    boost::unordered_set<index_t, index_hash_t> indices;

    while (indices.size() < num_curve_knots)
    {
        indices.insert(tp::make_tuple(box_idx_die(), box_idx_die(), box_idx_die()));
    }

    OSG::Real32 l = 2 * world_size / num_grid_boxes;
    
    std::vector<OSG::Pnt3f> knots;

    BOOST_FOREACH(const index_t& idx, indices)
    {
        OSG::Pnt3f p;
        p[0] = -world_size + idx.get<0>() * l + unit_die() * l;
        p[1] = -world_size + idx.get<1>() * l + unit_die() * l;
        p[2] = -world_size + idx.get<2>() * l + unit_die() * l;

        knots.push_back(p);
    }

    if (close_curve)
        knots.push_back(knots.front());

    return knots;
}

// ============================================================================
//
// Part: The shader programs
//
// ============================================================================

//
// vertex shader program.
//
std::string get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 440 compatibility"
    << endl << ""
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

    ost
            << "#version 440 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << "#extension GL_ARB_shader_image_load_store:      enable"
    << endl << ""
    << endl << "smooth in vec3 vNormalES;           // eye space normal"
    << endl << "smooth in vec3 vPositionES;         // eye space position"
    << endl << "" 
    << endl << "const int num_materials = " << num_materials << ";"
    << endl << ""
    << endl << "uniform mat4  OSGViewMatrix;    // from world space to view space transformation"
    << endl << ""
    << cluster_shading_stage->getFragmentProgramSnippet()
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
    << endl << "layout (std140) uniform GeomState"
    << endl << "{"
    << endl << "    uint material_index;"
    << endl << "} geom_state;"
    << endl << ""
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based on the light "
    << endl << "// range r and the distance d of the light to the current point."
    << endl << "//"
    << endl << "float calcAttenuation("
    << endl << "    in const float r,"
    << endl << "    in const float d)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "    // float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "    // smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "    //"
    << endl << "    return 1.0 - smoothstep(0.75 * r, r, d);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      minCosSpotAngle: the cosine of the spot light angle"
    << endl << "//      l              :  normalized direction between fragment and light position"
    << endl << "//      s              :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation("
    << endl << "    in const float minCosSpotAngle,"
    << endl << "    in const vec3 l,"
    << endl << "    in const vec3 s)"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Linear interpolate between x and y using weight a"
    << endl << "    // mix(x,y,a) = x*(1-a)+y*a"
    << endl << "    //"
    << endl << "    float maxCosSpotAngle = mix(minCosSpotAngle, 1.0, 0.5);"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    //"
    << endl << "    // Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "    // float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "    // smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "    //"
    << endl << "    return smoothstep(minCosSpotAngle, maxCosSpotAngle, l_dot_s);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// cinema (uber) light super ellipses clipping"
    << endl << "// Parameters:"
    << endl << "//      a     :  inner super ellipses width"
    << endl << "//      b     :  inner super ellipses height"
    << endl << "//      A     :  outer super ellipses width"
    << endl << "//      B     :  outer super ellipses height"
    << endl << "//      r     :  roundness parameter"
    << endl << "//      theta :  twist parameter"
    << endl << "//      pos   :  fragment position in light space"
    << endl << "//"
    << endl << "//      |x/a|^r + |y/b|^r = 1 <=> a*b*(|b*x|^r + |a*y|^r)^(-1/r) = 1"
    << endl << "//"
    << endl << "// smoothstep(e0,e1,x)"
    << endl << "//      Perform smooth Hermite interpolation between 0 and 1, when e0<x<e1"
    << endl << "//      float t = clamp((x-e0)/(e1-e0),0.0,1.0);"
    << endl << "//      smoothstep(e0,e1,x) = t*t*(3-2*t);"
    << endl << "//"
    << endl << "float clipSuperEllipses("
    << endl << "    in float a,"
    << endl << "    in float b,"
    << endl << "    in float A,"
    << endl << "    in float B,"
    << endl << "    in float r,"
    << endl << "    in float theta,"
    << endl << "    in vec3 pos)"
    << endl << "{"
    << endl << "    float result = 1.0;"
    << endl << ""
    << endl << "    vec2 P = pos.xy / pos.z;"
    << endl << "    if (all(equal(P, vec2(0.0, 0.0))))"
    << endl << "        return 1.0;"
    << endl << ""
    << endl << "    float cos_theta = cos(-theta);"
    << endl << "    float sin_theta = sin(-theta);"
    << endl << ""
    << endl << "    float x =  abs(cos_theta * P.x - sin_theta * P.y);"
    << endl << "    float y =  abs(sin_theta * P.x + cos_theta * P.y);"
    << endl << ""
    << endl << "    if (r > 50) // basically a square"
    << endl << "    {"
    << endl << "        // Simpler case of a square"
    << endl << "        result = (1.0 - smoothstep(a, A, x)) * (1.0 - smoothstep(b, B, y));"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        float q = pow(x/a, r) + pow(y/b, r);"
    << endl << "        float Q = pow(x/A, r) + pow(y/B, r);"
    << endl << ""
    << endl << "        if (q <  1) return 1.0;"
    << endl << "        if (Q >= 1) return 0.0;"
    << endl << ""
    << endl << "        result = 1.0 - smoothstep(q, Q, 1.0);"
    << endl << "    }"
    << endl << ""
    << endl << "    return result;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// directional light contribution"
    << endl << "//"
    << endl << "vec3 directionalLight("
    << endl << "    in const uint i,  // light identifier, i.e. current light"
    << endl << "    in const uint j,  // material identifier"
    << endl << "    in const vec3 n,  // vertex normal in eye space"
    << endl << "    in const vec3 v)  // view direction in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light direction from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
    << endl << ""
    << endl << "    vec3 l = -direction.xyz;"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
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
    << endl << "    vec3 light_intensity = lights.light[i].intensity * lights.light[i].color;"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + light_intensity * materials.material[j].ambient"
    << endl << "     + light_intensity * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + light_intensity * materials.material[j].specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// point light contribution"
    << endl << "//"
    << endl << "vec3 pointLight("
    << endl << "    in const uint i,  // light identifier, i.e. current light"
    << endl << "    in const uint j,  // material identifier"
    << endl << "    in const vec3 n,  // vertex normal in eye space"
    << endl << "    in const vec3 v,  // view direction in eye space"
    << endl << "    in const vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light position from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
    << endl << ""
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    if (lights.light[i].rangeCutOff < d)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm direction from surf to light"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].rangeCutOff, d);"
    << endl << ""
    << endl << "    vec3 light_intensity = attenuation * lights.light[i].intensity * lights.light[i].color;"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + light_intensity * materials.material[j].ambient"
    << endl << "     + light_intensity * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + light_intensity * materials.material[j].specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// spot light contribution"
    << endl << "//"
    << endl << "vec3 spotLight("
    << endl << "    in const uint i,  // light identifier, i.e. current light"
    << endl << "    in const uint j,  // material identifier"
    << endl << "    in const vec3 n,  // vertex normal in eye space"
    << endl << "    in const vec3 v,  // view direction in eye space"
    << endl << "    in const vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light position from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
    << endl << ""
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    if (lights.light[i].rangeCutOff < d)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm dir from surface to light"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light direction from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
    << endl << ""
    << endl << "    vec3 s = direction.xyz;"
    << endl << "    s = normalize(s);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].rangeCutOff, d);"
    << endl << ""
    << endl << "    attenuation *= spotAttenuation(lights.light[i].cosSpotlightAngle, l, s);"
    << endl << ""
    << endl << "    vec3 light_intensity = attenuation * lights.light[i].intensity * lights.light[i].color;"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + light_intensity * materials.material[j].ambient"
    << endl << "     + light_intensity * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + light_intensity * materials.material[j].specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// cinema light contribution"
    << endl << "//"
    << endl << "vec3 cinemaLight("
    << endl << "    in const uint i,  // light identifier, i.e. current light"
    << endl << "    in const uint j,  // material identifier"
    << endl << "    in const vec3 n,  // vertex normal in eye space"
    << endl << "    in const vec3 v,  // view direction in eye space"
    << endl << "    in const vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light position from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
    << endl << ""
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    if (lights.light[i].rangeCutOff < d)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm dir from surface to light"
    << endl << ""
    << endl << "    //"
    << endl << "    // Transform the light direction from world space into eye space for further considerations"
    << endl << "    //"
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
    << endl << ""
    << endl << "    vec3 s = direction.xyz;"
    << endl << "    s = normalize(s);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the half vector"
    << endl << "    //"
    << endl << "    vec3 h = normalize(l+v);"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].rangeCutOff, d);"
    << endl << ""
    << endl << "    vec3 p_LS = (lights.light[i].eyeToLightSpaceMatrix * vec4(p, 1.0)).xyz;"
    << endl << ""
    << endl << "    attenuation *= clipSuperEllipses("
    << endl << "                            lights.light[i].innerSuperEllipsesWidth,"
    << endl << "                            lights.light[i].innerSuperEllipsesHeight,"
    << endl << "                            lights.light[i].outerSuperEllipsesWidth,"
    << endl << "                            lights.light[i].outerSuperEllipsesHeight,"
    << endl << "                            lights.light[i].superEllipsesRoundness,"
    << endl << "                            lights.light[i].superEllipsesTwist,"
    << endl << "                            p_LS);"
    << endl << ""
    << endl << "    if (p_LS.z > 0.0) attenuation = 0.0;"
    << endl << ""
    << endl << "    attenuation = clamp(attenuation, 0.0, 1.0);"
    << endl << ""
    << endl << "    vec3 light_intensity = attenuation * lights.light[i].intensity * lights.light[i].color;"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + light_intensity * materials.material[j].ambient"
    << endl << "     + light_intensity * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + light_intensity * materials.material[j].specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // normalize the eye space normal"
    << endl << "    //"
    << endl << "    int frontCond = -(1 - int(gl_FrontFacing)*2);"
    << endl << "    vec3 N = frontCond * normalize(vNormalES);"
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
    << endl << ""
    << endl << "    uint list_idx    = 0;"
    << endl << "    uint light_count = 0;"
    << endl << ""
    << endl << "    if (clusteringData.enabled)"
    << endl << "    {"
    << endl << "        uvec2 grid_data = getGridData(gl_FragCoord.xy, vPositionES.z);"
    << endl << "        "
    << endl << "        list_idx    = grid_data.x;"
    << endl << "        light_count = grid_data.y;"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        light_count = affectedLightIndexList.idx.length();"
    << endl << "    }"
    << endl << ""
    << endl << "    for (uint i = 0; i < light_count; ++i)"
    << endl << "    {"
    << endl << "        uint light_idx = (clusteringData.enabled) ? lightIndexList.idx[list_idx+i] : affectedLightIndexList.idx[i];"
    << endl << ""
    << endl << "        switch (lights.light[light_idx].type)"
    << endl << "        {"
    << endl << "            case       POINT_LIGHT: color +=       pointLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case DIRECTIONAL_LIGHT: color += directionalLight(light_idx, geom_state.material_index, N, V);               break;"
    << endl << "            case        SPOT_LIGHT: color +=        spotLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case      CINEMA_LIGHT: color +=      cinemaLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "        }"
    << endl << "    }"
    << endl << "    vFragColor = vec4(color, materials.material[geom_state.material_index].opacity);"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

