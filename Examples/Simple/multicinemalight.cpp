// OpenSG Tutorial Example: MultiCinemaLight
//
// This example introduces the MultiLightChunk, the MultiPropertySSBOChunk and
// the MultiPropertyUBOChunk. The first two chunks are derived from the 
// ShaderStorageBufferObjStdLayoutChunk and easily permit the preparation 
// of array buffers in shader code with std430 shader storage buffer block
// format. The third chunk is derived from the UniformBufferObjStd140Chunk
// and allows easy preparation of a std140 uniform array block.
//
// The MultiLightChunk models a light data structures for multiple lights. 
// It supports a number of different light types and also gives the user 
// freedom in the details of the data structure layout provided in shader code
// for these lights. It currently supports data for directional, point, spot
// and Ueber (cinema) lights. It is feasible to strip-down the light structure
// data layout somewhat if requested. This example actively only uses cinema
// lights and uses the standard OpenGL light abstraction. Of course the 
// shader code's responsibilty is to make usage of the provided light data
// attrubutes, and the writer of the shader can implement whatever light model 
// he likes on the given light buffer layout.
//
// The MultiPropertyUBOChunk and MultiPropertySSBOChunk do also provides means
// to conviently create shader buffer data. They are, however, not as 
// specialized as the MultiLightChunk.
// They have a simple interface for the data layout preparation but allows only
// a restricted subset of layout structure that the std140 uniform buffer block 
// repspectively the std430 shader storage buffer block specifications allows.
//
// In this example a MultiPropertySSBOChunk is used to model a material database
// with the simple basic material properties. The material database shader 
// buffer is shared by all geometry that is rendered by the example. 
//
// The MultiPropertyUBOChunk is used to provide geometry state data to the
// fragment shader. That is, each geometry gets its own chunk, but for the 
// purpose of the example only the material index to be used for the particular 
// geometry is added to chunk.
//
// Additionally, the example runs riot with boost random number generators.
// Hopefully, that does not distract the reader.
//
// Different aspects of the example can be manipulated at runtime like the
// number of lights and their range and intensity parameters as well as the
// number of geometries simulated and their material among many others.
//
// The examples uses a HDR2Stage core for managing the mapping of the 
// accumulated intensities into the feasible region of the final screen 
// render target. It does use mostly default settings for this stage.
//
// At last the example provides a bezier curve abstraction for generating
// the light and object pathes.
//
// See also:
//      multistandardlight.cpp
//      multicinemalight.cpp
//      uniformbufferobject_std140.cpp
//      shaderstoragebufferobject_std430.cpp
//      multipropertyubochunk_test.cpp
//      multipropertyssbochunk_test.cpp
//      tonemapping.cpp
//

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>
#include <boost/random.hpp>
#include <boost/tuple/tuple.hpp>
#include "boost/tuple/tuple_comparison.hpp"

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
#include <OSGHDR2Stage.h>
#include <OSGInverseTransform.h>
#include <OSGShaderProgramChunk.h>
#include <OSGShaderProgram.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGMatrixUtility.h>
#include <OSGMultiLightChunk.h>
#include <OSGMultiPropertyUBOChunk.h>
#include <OSGMultiPropertySSBOChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGBlendChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGTwoSidedLightingChunk.h>

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
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGMultiLightChunk.h>
#include <OpenSG/OSGMultiPropertyUBOChunk.h>
#include <OpenSG/OSGMultiPropertySSBOChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#endif

// ============================================================================
//
// Part I: Declaration of the example scene and some helpers:
//      - constants that governs the example
//      - random number generators
//      - smooth cubic Bezier spline curve
//
// ============================================================================

OSG::SimpleSceneManagerRefPtr mgr;

const OSG::Int32  num_geometries     = 16;
const OSG::Int32  num_grid_boxes     = 100;
const OSG::Int32  num_curve_knots    = 40;
const OSG::Int32  num_passes         = 4;
const std::size_t num_materials      = 5000;
const OSG::Int32  max_num_lights     = 1024;
const OSG::Real32 world_size         = 10.f;
const OSG::Real32 box_factor         = 1.5f;

OSG::Real32 simulation_delta         = 0.0001f;
OSG::Real32 elapse_time_limit        = 10.f;

const OSG::Real32 max_light_power    = 10.f;

const OSG::Real32 quadraticAttFactor = 1.2f;
const OSG::Real32 linearAttFactor    = 1.2f;
const OSG::Real32 spotExponentFactor = 1.2f;
const OSG::Real32 ellipsesGeomFactor = 1.05f;
const OSG::Real32 ellipsesRoundFactor= 1.05f;

typedef boost::mt19937 RNGType;
RNGType rng(time(0));

boost::uniform_int<> box_dist(0, num_grid_boxes-1);
boost::variate_generator<RNGType, boost::uniform_int<> > box_idx_die(rng, box_dist);

boost::uniform_int<> die_dist(1, 6);
boost::variate_generator<RNGType, boost::uniform_int<> > classic_die(rng, die_dist);  

boost::uniform_int<> geom_dist(0, 7);
boost::variate_generator<RNGType, boost::uniform_int<> > geom_idx_die(rng, geom_dist);  

boost::uniform_01<float>  unit_distribution;
boost::variate_generator< RNGType, boost::uniform_01<float> > unit_die(rng, unit_distribution);

boost::uniform_real<float>  small_distribution(0.1f, 1.f);
boost::variate_generator< RNGType, boost::uniform_real<float> >  small_die(rng,  small_distribution);

boost::uniform_real<float>  light_range_distribution(0.2f, 0.7f);
boost::variate_generator< RNGType, boost::uniform_real<float> >  light_range_die(rng,  light_range_distribution);

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

class CubicBezierCurve
{
public:
    CubicBezierCurve(const OSG::Pnt3f& p0, const OSG::Pnt3f& p1, const OSG::Pnt3f& p2, const OSG::Pnt3f& p3);
    CubicBezierCurve(const CubicBezierCurve& rhs);
    
    CubicBezierCurve& operator=(const CubicBezierCurve& rhs);

    OSG::Pnt3f  operator()      (OSG::Real32 t) const;
    OSG::Vec3f  tangent         (OSG::Real32 t) const;
    OSG::Vec3f  normal          (OSG::Real32 t) const;
    OSG::Vec3f  binormal        (OSG::Real32 t) const;
    OSG::Matrix frame           (OSG::Real32 t, bool position_only) const;
    OSG::Real32 length          (OSG::UInt32 numSeg = 10) const;

private:
    OSG::Vec3f  fst_derivative  (OSG::Real32 t) const;
    OSG::Vec3f  sec_derivative  (OSG::Real32 t) const;
    OSG::Vec3f  thr_devivative  (OSG::Real32 t) const;

private:
    OSG::Pnt3f p[4];
};

class SmoothCubicBezierSpline
{
public:
    typedef std::vector<OSG::Pnt3f> points_t;

    SmoothCubicBezierSpline(const points_t& knots);
    SmoothCubicBezierSpline(const SmoothCubicBezierSpline& rhs);

    SmoothCubicBezierSpline& operator=(const SmoothCubicBezierSpline& rhs);

    OSG::Pnt3f  operator()  (OSG::Real32 t) const;
    OSG::Vec3f  tangent     (OSG::Real32 t) const;
    OSG::Vec3f  normal      (OSG::Real32 t) const;
    OSG::Vec3f  binormal    (OSG::Real32 t) const;
    OSG::Matrix frame       (OSG::Real32 t, bool position_only = false) const;
    OSG::Real32 length      (OSG::UInt32 numSeg = 10) const;

private:
    void        calc_ctrl_pnts  (points_t& p1, points_t& p2) const;
    std::size_t index           (OSG::Real32 t) const;
    OSG::Real32 t_              (OSG::Real32 t, std::size_t idx) const;

private:
    std::vector<OSG::Pnt3f>         knots;
    std::vector<OSG::Real32>        intervals;
    std::vector<CubicBezierCurve>   curves;
};

// ============================================================================
//
// Part II: Declaration of
//      - struct Light and type VecLightsT,
//      - struct Material and type VecMaterialsT,
//      - struct GeomState
//  and corresponding initialization routines.
//
// ============================================================================

//
// simple light data structure
//
struct Light
{
    enum Type
    {
        directional_light = OSG::MultiLight::DIRECTIONAL_LIGHT,
        point_light       = OSG::MultiLight::POINT_LIGHT,
        spot_light        = OSG::MultiLight::SPOT_LIGHT,
        cinema_light      = OSG::MultiLight::CINEMA_LIGHT
    };

    OSG::MultiLight::Type getType() const { return static_cast<OSG::MultiLight::Type>(type); }

    explicit Light(Type e);
            ~Light();

    static Light create_light(Type e, OSG::UInt32 material_idx);

    OSG::Pnt3f   position;                  // light position in object space for point and spot lights
    OSG::Vec3f   direction;                 // direction of directional light or spot light in object space
    OSG::Vec3f   ambientIntensity;          // the ambient light intensity
    OSG::Vec3f   diffuseIntensity;          // the diffuse light intensity
    OSG::Vec3f   specularIntensity;         // the specular light intensity
    OSG::Real32  constantAttenuation;       // the intensity of the light
    OSG::Real32  linearAttenuation;         // the intensity of the light
    OSG::Real32  quadraticAttenuation;      // the intensity of the light
    OSG::Real32  spotlightAngle;            // the cone angle in case of a spot light
    OSG::Real32  spotExponent;              // the spot exponent governs the attenuation of the light
    OSG::Real32  innerSuperEllipsesWidth;   // cinema light parameter
    OSG::Real32  innerSuperEllipsesHeight;  // cinema light parameter
    OSG::Real32  outerSuperEllipsesWidth;   // cinema light parameter
    OSG::Real32  outerSuperEllipsesHeight;  // cinema light parameter
    OSG::Real32  superEllipsesRoundness;    // cinema light parameter
    OSG::Real32  superEllipsesTwist;        // cinema light parameter

    OSG::Int32   type;                  // the type of light: see OSG::MultiLight::LightType
    bool         enabled;               // on/off state of the light

    OSG::NodeRefPtr         beacon;     // the light beacon that if defined evaluates the position parameter
    OSG::TransformRefPtr    transform;  // the beacons transform core
    SmoothCubicBezierSpline curve;      // the path that the light will follow
};

typedef std::vector<Light>  VecLightsT;         // multiple lights
VecLightsT lights;                              // the lights of the scene

Light::Light(Type e) 
: position(0.f, 0.f, 0.f)
, direction(0.f, 0.f, 1.f)
, ambientIntensity(1.f,1.f,1.f)
, diffuseIntensity(1.f,1.f,1.f)
, specularIntensity(1.f,1.f,1.f)
, constantAttenuation(1.f)
, linearAttenuation(0.0001f)
, quadraticAttenuation(0.000001f)
, spotlightAngle(20.f)
, spotExponent(1.f)
, innerSuperEllipsesWidth(1.f)
, innerSuperEllipsesHeight(1.f)
, outerSuperEllipsesWidth(1.3f)
, outerSuperEllipsesHeight(1.3f)
, superEllipsesRoundness(0.45f)
, superEllipsesTwist(0.f)
, type(e)
, enabled(true)
, beacon(NULL)
, transform(NULL)
, curve(dice_knots(true))
{}

Light::~Light() 
{
    beacon = NULL;
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
// Part III: Creation and update of the light state
//
// ============================================================================

OSG::MultiLightChunkTransitPtr create_light_state(const VecLightsT& vLights)
{
    OSG::MultiLightChunkRefPtr lightChunk = OSG::MultiLightChunk::create();

    lightChunk->setUsage(GL_DYNAMIC_DRAW);
    lightChunk->setLayoutType(
                    OSG::MultiLight::OPENGL_LAYOUT | 
                    OSG::MultiLight::RANGE_LAYOUT |
                    OSG::MultiLight::CINEMA_LAYOUT);

    lightChunk->setHasEyeToLightSpaceMatrix(true);
    lightChunk->setAutoCalcRanges(true);

    BOOST_FOREACH(const Light& light, vLights)
    {
        OSG::UInt32 idx = lightChunk->addLight(light.getType());

        lightChunk->setPosition                 (idx, light.position);
        lightChunk->setDirection                (idx, light.direction);
        lightChunk->setAmbientIntensity         (idx, light.ambientIntensity);
        lightChunk->setDiffuseIntensity         (idx, light.diffuseIntensity);
        lightChunk->setSpecularIntensity        (idx, light.specularIntensity);
        lightChunk->setAttenuation              (idx, OSG::Vec3f(light.constantAttenuation,
                                                                 light.linearAttenuation,
                                                                 light.quadraticAttenuation));
        lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
        lightChunk->setSpotExponent             (idx, light.spotExponent);
        lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
        lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
        lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
        lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
        lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
        lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
        lightChunk->setEnabled                  (idx, light.enabled);
        lightChunk->setType                     (idx, light.getType());
        lightChunk->setBeacon                   (idx, light.beacon);
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
                OSG::UInt32 idx = lightChunk->addLight(light.getType());

                lightChunk->setPosition                 (idx, light.position);
                lightChunk->setDirection                (idx, light.direction);
                lightChunk->setAmbientIntensity         (idx, light.ambientIntensity);
                lightChunk->setDiffuseIntensity         (idx, light.diffuseIntensity);
                lightChunk->setSpecularIntensity        (idx, light.specularIntensity);
                lightChunk->setAttenuation              (idx, OSG::Vec3f(light.constantAttenuation,
                                                                         light.linearAttenuation,
                                                                         light.quadraticAttenuation));
                lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
                lightChunk->setSpotExponent             (idx, light.spotExponent);
                lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
                lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
                lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
                lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
                lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
                lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
                lightChunk->setEnabled                  (idx, light.enabled);
                lightChunk->setType                     (idx, light.getType());
                lightChunk->setBeacon                   (idx, light.beacon);
            }
        }
        else
        {
            for (OSG::UInt32 idx = 0; idx < vLights.size(); ++idx)
            {
                const Light& light = vLights[idx];

                lightChunk->setPosition                 (idx, light.position);
                lightChunk->setDirection                (idx, light.direction);
                lightChunk->setAmbientIntensity         (idx, light.ambientIntensity);
                lightChunk->setDiffuseIntensity         (idx, light.diffuseIntensity);
                lightChunk->setSpecularIntensity        (idx, light.specularIntensity);
                lightChunk->setAttenuation              (idx, OSG::Vec3f(light.constantAttenuation,
                                                                         light.linearAttenuation,
                                                                         light.quadraticAttenuation));
                lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
                lightChunk->setSpotExponent             (idx, light.spotExponent);
                lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
                lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
                lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
                lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
                lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
                lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
                lightChunk->setEnabled                  (idx, light.enabled);
                lightChunk->setType                     (idx, light.getType());
                lightChunk->setBeacon                   (idx, light.beacon);
            }
        }
    }
}

// ============================================================================
//
// Part IV: Some routines for handling of the memory buffer and the the
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
OSG::MultiPropertyUBOChunkTransitPtr create_geometry_material_state(const GeomState& geom_state)
{
    OSG::MultiPropertyUBOChunkRefPtr geomStateChunk = OSG::MultiPropertyUBOChunk::create();

    GeomState::material_index_id = geomStateChunk->addMember(OSG::MultiPropertyUBOChunk::UINT_T, 1);
    geomStateChunk->setUsage(GL_DYNAMIC_DRAW);

    OSG::UInt32 idx = geomStateChunk->addProperty();
    geomStateChunk->setUIntProperty(idx, GeomState::material_index_id, geom_state.material_index);

    return OSG::MultiPropertyUBOChunkTransitPtr(geomStateChunk);
}

void update_geometry_material_state(OSG::MultiPropertyUBOChunk* geomStateChunk, const GeomState& geom_state)
{
    if (geomStateChunk)
    {
        if (geomStateChunk->getNumProperties() != 1)
        {
            geomStateChunk->clearProperties();

            OSG::UInt32 idx = geomStateChunk->addProperty();
            geomStateChunk->setUIntProperty(idx, GeomState::material_index_id, geom_state.material_index);
        }
        else
        {
            geomStateChunk->setUIntProperty(  0, GeomState::material_index_id, geom_state.material_index);
        }
    }
}

// ============================================================================
//
// Part V: The application finally starts here
//
// ============================================================================

//
// vertex shader program.
//
std::string get_vp_program();

//
// fragment shader program for bump mapping in surface local coordinates
//
std::string get_fp_program();

//
// The scene 
//
OSG::NodeRefPtr scene_node = NULL;

//
// A HDR stage core
//
OSG::HDR2StageRefPtr hdr_stage = NULL;
OSG::NodeRefPtr hdr_node = NULL;

//
// The material database for all visible geometry: objects, lights, stage box
//
OSG::MultiPropertySSBOChunkRefPtr ssbo_material_database = NULL;

//
// The mulit light chunk
//
OSG::MultiLightChunkRefPtr multi_light_chunk = NULL;

//
// The block binding point for the geom state
//
OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = NULL;

//
// Shader Storage buffer objects corresponding to transient shader blocks
//
std::vector<OSG::MultiPropertyUBOChunkRefPtr> ubo_geom_states;

//
// A separate transformation for each object and a spline for the trajectory
//
std::vector<OSG::NodeRefPtr> geom_nodes;
std::vector<OSG::TransformRefPtr> geom_trafos;
std::vector<SmoothCubicBezierSpline> geom_curves;

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
        if (n <= 4)
              type = Light::cinema_light;
        else if (n <= 5)
            type = Light::point_light;
        else
            type = Light::spot_light;

        lights.push_back(Light::create_light(type, i+1));
        scene_node->addChild(lights[i].beacon);
    }
}

Light Light::create_light(
    Type e,                     // type of the light
    OSG::UInt32 material_idx)   // index in to the material storage for light animation
{
    Light l(e);

    l.beacon = OSG::makeCoredNode<OSG::Transform>(&l.transform);
    OSG::Matrix m;

    OSG::Real32 L = box_factor * world_size;

    l.direction = dice_unit_vector();

    OSG::Color3f c; c.setRandom();
    l.ambientIntensity  = c;
    l.diffuseIntensity  = c;
    l.specularIntensity = c;

    //
    // If we fix the constant factor to 1 we alway get attenuation <= 1
    // for l,q >= 0.
    //
    // a = 1/(c + l*d + q*d^2)
    //

    l.constantAttenuation  = 1.f;
    l.linearAttenuation    = OSG::Eps;
    l.quadraticAttenuation = OSG::Eps;

    Material mat;
    mat.emissive = c;
    materials[material_idx] = mat;

    switch (e)
    {
        case point_light:
        {
            OSG::GeometryRefPtr  geometry = OSG::makeSphereGeo(3, 0.1f);
            OSG::NodeRefPtr      node     = OSG::makeNodeFor(geometry);

            GeomState geom; geom.material_index = material_idx;     // material index used for light animiation
            OSG::ChunkMaterialRefPtr geom_state = OSG::ChunkMaterial::create();
            OSG::MultiPropertyUBOChunkRefPtr ubo_geom_state = create_geometry_material_state(geom);
            geom_state->addChunk(ubo_geom_state, 3);                // buffer binding point 3
            geom_state->addChunk(shader_var_chunk);                 // block binding point

            geometry->setMaterial(geom_state);

            l.beacon->addChild(node);
        }
        break;

        case directional_light:
        {
        }
        break;

        case spot_light:
        {
            l.spotlightAngle = 90.f * small_die();
            l.spotExponent   = 1.f;

            GeomState geom; geom.material_index = material_idx;     // material index used for light animiation
            OSG::ChunkMaterialRefPtr geom_state = OSG::ChunkMaterial::create();
            OSG::MultiPropertyUBOChunkRefPtr ubo_geom_state = create_geometry_material_state(geom);
            geom_state->addChunk(ubo_geom_state, 3);                // buffer binding point 3
            geom_state->addChunk(shader_var_chunk);                 // block binding point

            OSG::Real32 r = 0.1f;
            OSG::Real32 h = r / OSG::osgTan(OSG::osgDegree2Rad(l.spotlightAngle));
            OSG::GeometryRefPtr  geometry  = OSG::makeConeGeo(h, r, 24, true, true);
            geometry->setMaterial(geom_state);

            OSG::TransformRefPtr cone_trans = OSG::Transform::create();
            OSG::Matrix spot_mat;
            bool result = OSG::MatrixLookAt(spot_mat, l.direction, OSG::Pnt3f(0,0,0), OSG::Vec3f(0,1,0));
            if (result)
                OSG::MatrixLookAt(spot_mat, l.direction, OSG::Pnt3f(0,0,0), OSG::Vec3f(1,0,0));
            cone_trans->setMatrix(spot_mat);

            OSG::Real32 ang = -90.f;
            OSG::Vec3f rotVec(1,0,0);

            OSG::TransformRefPtr rot_trans = OSG::Transform::create();
            OSG::Matrix rot_mat;
            rot_mat.setRotate(OSG::Quaternion(rotVec, OSG::osgDegree2Rad(ang)));
            rot_trans->setMatrix(rot_mat);

            OSG::NodeRefPtr cone_trans_node  = OSG::makeNodeFor(cone_trans);
            OSG::NodeRefPtr rot_trans_node   = OSG::makeNodeFor(rot_trans);
            OSG::NodeRefPtr cone_node        = OSG::makeNodeFor(geometry);

            l.beacon->addChild(cone_trans_node);

            cone_trans_node->addChild(rot_trans_node);
            rot_trans_node->addChild(cone_node);

            //OSG::GeometryRefPtr geometry_test = OSG::makeCylinderGeo(30, .01f, 24, true, true, true );
            //geometry_test->setMaterial(geom_state);

            //OSG::TransformRefPtr test_trans = OSG::Transform::create();
            //OSG::Matrix test_mat;
            //test_mat.setTranslate(OSG::Vec3f(0,-15,0));
            //test_trans->setMatrix(test_mat);

            //OSG::NodeRefPtr test_rot_trans_node = OSG::makeNodeFor(rot_trans);
            //OSG::NodeRefPtr test_trans_node     = OSG::makeNodeFor(test_trans);
            //OSG::NodeRefPtr test_node           = OSG::makeNodeFor(geometry_test);
            //cone_trans_node->addChild(test_rot_trans_node);
            //test_rot_trans_node->addChild(test_trans_node);
            //test_trans_node->addChild(test_node);
        }
        break;

        case cinema_light:
        {
            l.spotlightAngle = 90.f * small_die();

            GeomState geom; geom.material_index = material_idx;     // material index used for light animiation
            OSG::ChunkMaterialRefPtr geom_state = OSG::ChunkMaterial::create();
            OSG::MultiPropertyUBOChunkRefPtr ubo_geom_state = create_geometry_material_state(geom);
            geom_state->addChunk(ubo_geom_state, 3);                // buffer binding point 3
            geom_state->addChunk(shader_var_chunk);                 // block binding point

            OSG::Real32 r = 0.1f;
            OSG::Real32 h = r / OSG::osgTan(OSG::osgDegree2Rad(l.spotlightAngle));
            OSG::GeometryRefPtr  geometry  = OSG::makeConeGeo(h, r, 24, true, true);
            geometry->setMaterial(geom_state);

            OSG::TransformRefPtr cone_trans = OSG::Transform::create();
            OSG::Matrix spot_mat;
            bool result = OSG::MatrixLookAt(spot_mat, l.direction, OSG::Pnt3f(0,0,0), OSG::Vec3f(0,1,0));
            if (result)
                OSG::MatrixLookAt(spot_mat, l.direction, OSG::Pnt3f(0,0,0), OSG::Vec3f(1,0,0));
            cone_trans->setMatrix(spot_mat);

            OSG::Real32 ang = -90.f;
            OSG::Vec3f rotVec(1,0,0);

            OSG::TransformRefPtr rot_trans = OSG::Transform::create();
            OSG::Matrix rot_mat;
            rot_mat.setRotate(OSG::Quaternion(rotVec, OSG::osgDegree2Rad(ang)));
            rot_trans->setMatrix(rot_mat);

            OSG::NodeRefPtr cone_trans_node  = OSG::makeNodeFor(cone_trans);
            OSG::NodeRefPtr rot_trans_node   = OSG::makeNodeFor(rot_trans);
            OSG::NodeRefPtr cone_node        = OSG::makeNodeFor(geometry);

            l.beacon->addChild(cone_trans_node);

            cone_trans_node->addChild(rot_trans_node);
            rot_trans_node->addChild(cone_node);

            //OSG::GeometryRefPtr geometry_test = OSG::makeCylinderGeo(30, .01f, 24, true, true, true );
            //geometry_test->setMaterial(geom_state);

            //OSG::TransformRefPtr test_trans = OSG::Transform::create();
            //OSG::Matrix test_mat;
            //test_mat.setTranslate(OSG::Vec3f(0,-15,0));
            //test_trans->setMatrix(test_mat);

            //OSG::NodeRefPtr test_rot_trans_node = OSG::makeNodeFor(rot_trans);
            //OSG::NodeRefPtr test_trans_node     = OSG::makeNodeFor(test_trans);
            //OSG::NodeRefPtr test_node           = OSG::makeNodeFor(geometry_test);
            //cone_trans_node->addChild(test_rot_trans_node);
            //test_rot_trans_node->addChild(test_trans_node);
            //test_trans_node->addChild(test_node);
        }
        break;

        default:
            break;
    }

    return l;
}

OSG::NodeTransitPtr createBox()
{
    OSG::NodeRefPtr box_root = OSG::makeCoredNode<OSG::Group>();

    OSG::Real32 L = box_factor * world_size;
    OSG::GeometryRefPtr box_plane  = OSG::makePlaneGeo(2.f*L, 2.f*L, 128, 128);

    OSG::NodeRefPtr box_bottom = OSG::makeNodeFor(box_plane);
    OSG::NodeRefPtr box_left   = OSG::makeNodeFor(box_plane);
    OSG::NodeRefPtr box_right  = OSG::makeNodeFor(box_plane);
    OSG::NodeRefPtr box_far    = OSG::makeNodeFor(box_plane);

    OSG::TransformRefPtr box_bottom_trans = OSG::Transform::create();
    OSG::TransformRefPtr box_left_trans   = OSG::Transform::create();
    OSG::TransformRefPtr box_right_trans  = OSG::Transform::create();
    OSG::TransformRefPtr box_far_trans    = OSG::Transform::create();

    OSG::Matrix mat_bottom, mat_left, mat_right, mat_far;

    mat_bottom.setTransform(OSG::Vec3f(0.f,  -L, 0.f), OSG::Quaternion( OSG::Vec3f(1, 0, 0), OSG::osgDegree2Rad(270.f)));
    mat_left  .setTransform(OSG::Vec3f( -L, 0.f, 0.f), OSG::Quaternion( OSG::Vec3f(0, 1, 0), OSG::osgDegree2Rad(90.f)));
    mat_right .setTransform(OSG::Vec3f(  L, 0.f, 0.f), OSG::Quaternion( OSG::Vec3f(0, 1, 0), OSG::osgDegree2Rad(270.f)));
    mat_far   .setTransform(OSG::Vec3f(0.f, 0.f,  -L), OSG::Quaternion( OSG::Vec3f(0, 0, 1), OSG::osgDegree2Rad(  0.f)));

    box_bottom_trans ->setMatrix(mat_bottom);
    box_left_trans   ->setMatrix(mat_left);
    box_right_trans  ->setMatrix(mat_right);
    box_far_trans    ->setMatrix(mat_far);

    OSG::NodeRefPtr box_bottom_trans_node = OSG::makeNodeFor(box_bottom_trans);
    OSG::NodeRefPtr box_left_trans_node   = OSG::makeNodeFor(box_left_trans);
    OSG::NodeRefPtr box_right_trans_node  = OSG::makeNodeFor(box_right_trans);
    OSG::NodeRefPtr box_far_trans_node    = OSG::makeNodeFor(box_far_trans);

    box_bottom_trans_node ->addChild(box_bottom);
    box_left_trans_node   ->addChild(box_left);
    box_right_trans_node  ->addChild(box_right);
    box_far_trans_node    ->addChild(box_far);

    box_root->addChild(box_bottom_trans_node);
    box_root->addChild(box_left_trans_node);
    box_root->addChild(box_right_trans_node);
    box_root->addChild(box_far_trans_node);

    GeomState geom; geom.material_index = 0;                        // grey box material index
    OSG::ChunkMaterialRefPtr geom_state = OSG::ChunkMaterial::create();
    OSG::MultiPropertyUBOChunkRefPtr ubo_geom_state = create_geometry_material_state(geom);
    geom_state->addChunk(ubo_geom_state, 3);                        // buffer binding point 3
    geom_state->addChunk(shader_var_chunk);                         // block binding point

    OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
    polygonChunk->setFrontMode(GL_SMOOTH);
    polygonChunk->setBackMode(GL_SMOOTH);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);
    polygonChunk->setCullFace(GL_NONE);
    geom_state->addChunk(polygonChunk);
    geom_state->setTransparencyMode(OSG::Material::TransparencyForceOpaque);

    OSG::TwoSidedLightingChunkRefPtr twoSidedLightingChunk = OSG::TwoSidedLightingChunk::create();
    geom_state->addChunk(twoSidedLightingChunk);

    box_plane->setMaterial(geom_state);

    return OSG::NodeTransitPtr(box_root);
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
    OSG::ChunkMaterialRefPtr geom_state = OSG::ChunkMaterial::create();
    OSG::MultiPropertyUBOChunkRefPtr ubo_geom_state = create_geometry_material_state(geom);
    geom_state->addChunk(ubo_geom_state, 3);                        // buffer binding point 3
    geom_state->addChunk(shader_var_chunk);                         // block binding point

    OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
    polygonChunk->setFrontMode(GL_SMOOTH);
    polygonChunk->setBackMode(GL_SMOOTH);
    polygonChunk->setOffsetFactor(1.f);
    polygonChunk->setOffsetBias(1.f);
    polygonChunk->setOffsetFill(true);

    OSG::Real32 opacity = materials[geom.material_index].opacity;
    if (opacity < 1.f)
    {
        polygonChunk->setCullFace(GL_NONE);

        OSG::BlendChunkRefPtr blendChunk = OSG::BlendChunk::create();
        blendChunk->setSrcFactor (GL_SRC_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        geom_state->addChunk(blendChunk);
        geom_state->setTransparencyMode(OSG::Material::TransparencyForceTransparent);

        OSG::TwoSidedLightingChunkRefPtr twoSidedLightingChunk = OSG::TwoSidedLightingChunk::create();
        geom_state->addChunk(twoSidedLightingChunk);

    } else {
        polygonChunk->setCullFace(GL_BACK);
        geom_state->setTransparencyMode(OSG::Material::TransparencyForceOpaque);
    }

    geom_state->addChunk(polygonChunk);

    geometry->setMaterial(geom_state);

    geom_nodes.push_back(transNode);
    geom_trafos.push_back(trafoCore);
    ubo_geom_states.push_back(ubo_geom_state);

    geom_curves.push_back(SmoothCubicBezierSpline(dice_knots(true)));

    return OSG::NodeTransitPtr(transNode);
}

//
// forward declaration so we can have the interesting stuff upfront
//
int  setupGLUT  (int *argc, char *argv[]);
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

        // The scene
        hdr_node           = OSG::makeCoredNode<OSG::Group>();
        scene_node         = OSG::makeCoredNode<OSG::Group>();

        hdr_node->addChild(scene_node);

        mgr->setRoot(hdr_node);

        createHDRStage();

        //
        // create the shader program
        //
        OSG::ShaderProgramChunkRefPtr prog_chunk = OSG::ShaderProgramChunk::create();
        OSG::ShaderProgramRefPtr      vertShader = OSG::ShaderProgram::createVertexShader();
        OSG::ShaderProgramRefPtr      fragShader = OSG::ShaderProgram::createFragmentShader();

        vertShader->setProgram(get_vp_program());
        fragShader->setProgram(get_fp_program());

        fragShader->addOSGVariable("OSGViewMatrix");

        //
        // binding the shader storage block to a buffer binding point can be performed 
        // either by calling the shaders's addShaderStorageBlock method or by
        // adding a 'buffer block' variable to a ShaderProgramVariableChunk.
        // In the following we use both variants for illustration.
        //
        fragShader->addShaderStorageBlock("Materials", 1);          // block binding point
        fragShader->addShaderStorageBlock("Lights",    2);          // block binding point

        //
        // The following is replaced by adding ShaderProgramVariableChunk objects
        // to the chunk material. See below...
        //
        // fragShader->addShaderStorageBlock("GeomState", 3);       // block binding point

        prog_chunk->addShader(vertShader);
        prog_chunk->addShader(fragShader);

        //
        // The block binding is added to each ChunkMaterial in order to provide the state
        // shader uniform block for the geometery shown in the scene
        //
        shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
        shader_var_chunk->addUniformBlock("GeomState", 3);    // block binding point

        //
        // Because we animate the lights by simple geometry, the lights initialization must be happens
        // after the creation of the 'shader_var_chunk' block binding point.
        // Additionally, it must happens before we call 'create_light_state', since here we do need the
        // already defined lights.
        //
        initialize_lights(1);

        //
        // create shader storage buffer objects and corresponding materials
        //
        ssbo_material_database = create_material_database_state(materials);
        multi_light_chunk      = create_light_state(lights);

        //multi_light_chunk->setEyeSpace(true);

        OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
        polygon_chunk->setFrontMode(GL_FILL);
        polygon_chunk->setBackMode(GL_FILL);
        polygon_chunk->setCullFace(GL_NONE);

        OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
        depth_chunk->setEnable(true);

        OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
        prog_state->addChunk(ssbo_material_database, 1);  // buffer binding point 1
        prog_state->addChunk(multi_light_chunk,      2);  // buffer binding point 2
        prog_state->addChunk(prog_chunk);
        prog_state->addChunk(polygon_chunk);
        prog_state->addChunk(depth_chunk);

        scene_node->addChild(createBox());

        for (OSG::Int32 i = 0; i < num_geometries; ++i)
            scene_node->addChild(createGeometry());

        OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
        mgrp->setMaterial(prog_state);
        scene_node->setCore(mgrp);

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
OSG::TimeStamp time_stamp        = 0;
OSG::Real32    simulation_param  = 0.f;
bool           simulate_geometry = true;
bool           simulate_lights   = true;

void display(void)
{
    // create the matrix
    OSG::Matrix m;

    if (time_stamp == 0)
        time_stamp = OSG::getTimeStamp();

    OSG::Time elapsed = OSG::getTimeStampMsecs(OSG::getTimeStamp() - time_stamp);

    if (elapsed > elapse_time_limit)
    {
        simulation_param += simulation_delta;
        if (simulation_param >= 1.f)
            simulation_param = 0.f;

        if (simulate_geometry)
        {
            std::size_t numCurves = geom_curves.size();

            OSG_ASSERT(numCurves == geom_trafos.size());

            for (std::size_t i = 0; i < numCurves; ++i)
            {
                m = geom_curves[i].frame(simulation_param);
                geom_trafos[i]->setMatrix(m);
            }
        }

        if (simulate_lights)
        {
            BOOST_FOREACH(Light& light, lights)
            {
                m = light.curve.frame(simulation_param, true);
                light.transform->setMatrix(m);
            }
        }

        time_stamp = OSG::getTimeStamp();
    }

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

            hdr_stage = NULL;
            hdr_node = NULL;

            scene_node = NULL;

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
        }
        break;

        case 'l':
        {
            simulate_lights = !simulate_lights;
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

        case 'r':
        {
            initialize_lights(1);
            update_light_state(multi_light_chunk, lights);
            update_material_database_state(ssbo_material_database, materials);

            simulation_delta  = 0.0001f;
            elapse_time_limit = 10.f;

            simulate_geometry = true;
            simulate_lights   = true;

            glutPostRedisplay();
        }
        break;

        case 'a':
        {
            BOOST_FOREACH(Light& light, lights)
                light.linearAttenuation *= linearAttFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'A':
        {
            BOOST_FOREACH(Light& light, lights)
                if (light.linearAttenuation / linearAttFactor >= OSG::Eps)
                    light.linearAttenuation /= linearAttFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'q':
        {
            BOOST_FOREACH(Light& light, lights)
                light.quadraticAttenuation *= quadraticAttFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'Q':
        {
            BOOST_FOREACH(Light& light, lights)
                if (light.quadraticAttenuation / quadraticAttFactor >= OSG::Eps)
                    light.quadraticAttenuation /= quadraticAttFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'x':
        {
            BOOST_FOREACH(Light& light, lights)
                light.spotExponent *= spotExponentFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'X':
        {
            BOOST_FOREACH(Light& light, lights)
                if (light.spotExponent / spotExponentFactor >= OSG::Eps)
                    light.spotExponent /= spotExponentFactor;

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'c':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesWidth / light.innerSuperEllipsesWidth;

                light.innerSuperEllipsesWidth *= ellipsesGeomFactor;
                light.outerSuperEllipsesWidth = r * light.innerSuperEllipsesWidth;

                std::cout << "innerSuperEllipsesWidth = " << light.innerSuperEllipsesWidth << std::endl;
                std::cout << "outerSuperEllipsesWidth = " << light.outerSuperEllipsesWidth << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'C':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                if (light.innerSuperEllipsesWidth / ellipsesGeomFactor >= OSG::Eps)
                {
                    OSG::Real32 r = light.outerSuperEllipsesWidth / light.innerSuperEllipsesWidth;

                    light.innerSuperEllipsesWidth /= ellipsesGeomFactor;
                    light.outerSuperEllipsesWidth = r * light.innerSuperEllipsesWidth;

                    std::cout << "innerSuperEllipsesWidth = " << light.innerSuperEllipsesWidth << std::endl;
                    std::cout << "outerSuperEllipsesWidth = " << light.outerSuperEllipsesWidth << std::endl;
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'v':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesHeight / light.innerSuperEllipsesHeight;

                light.innerSuperEllipsesHeight *= ellipsesGeomFactor;
                light.outerSuperEllipsesHeight = r * light.innerSuperEllipsesHeight;

                std::cout << "innerSuperEllipsesHeight = " << light.innerSuperEllipsesHeight << std::endl;
                std::cout << "outerSuperEllipsesHeight = " << light.outerSuperEllipsesHeight << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'V':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                if (light.innerSuperEllipsesHeight / ellipsesGeomFactor >= OSG::Eps)
                {
                    OSG::Real32 r = light.outerSuperEllipsesHeight / light.innerSuperEllipsesHeight;

                    light.innerSuperEllipsesHeight /= ellipsesGeomFactor;
                    light.outerSuperEllipsesHeight = r * light.innerSuperEllipsesHeight;

                    std::cout << "innerSuperEllipsesHeight = " << light.innerSuperEllipsesHeight << std::endl;
                    std::cout << "outerSuperEllipsesHeight = " << light.outerSuperEllipsesHeight << std::endl;
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'f':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesWidth / light.innerSuperEllipsesWidth;

                r *= ellipsesGeomFactor;
                light.outerSuperEllipsesWidth = r * light.innerSuperEllipsesWidth;

                std::cout << "innerSuperEllipsesWidth = " << light.innerSuperEllipsesWidth << std::endl;
                std::cout << "outerSuperEllipsesWidth = " << light.outerSuperEllipsesWidth << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'F':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesWidth / light.innerSuperEllipsesWidth;
                if (r / ellipsesGeomFactor >= 1.f)
                {
                    r /= ellipsesGeomFactor;
                    light.outerSuperEllipsesWidth = r * light.innerSuperEllipsesWidth;

                    std::cout << "innerSuperEllipsesWidth = " << light.innerSuperEllipsesWidth << std::endl;
                    std::cout << "outerSuperEllipsesWidth = " << light.outerSuperEllipsesWidth << std::endl;
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'g':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesHeight / light.innerSuperEllipsesHeight;

                r *= ellipsesGeomFactor;
                light.outerSuperEllipsesHeight = r * light.innerSuperEllipsesHeight;

                std::cout << "innerSuperEllipsesHeight = " << light.innerSuperEllipsesHeight << std::endl;
                std::cout << "outerSuperEllipsesHeight = " << light.outerSuperEllipsesHeight << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'G':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                OSG::Real32 r = light.outerSuperEllipsesHeight / light.innerSuperEllipsesHeight;
                if (r / ellipsesGeomFactor >= 1.f)
                {
                    r /= ellipsesGeomFactor;
                    light.outerSuperEllipsesHeight = r * light.innerSuperEllipsesHeight;

                    std::cout << "innerSuperEllipsesHeight = " << light.innerSuperEllipsesHeight << std::endl;
                    std::cout << "outerSuperEllipsesHeight = " << light.outerSuperEllipsesHeight << std::endl;
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'b':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                light.superEllipsesRoundness *= ellipsesRoundFactor;

                std::cout << "superEllipsesRoundness = " << light.superEllipsesRoundness << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'B':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                if (light.superEllipsesRoundness / ellipsesRoundFactor >= OSG::Eps)
                {
                    light.superEllipsesRoundness /= ellipsesRoundFactor;

                    std::cout << "superEllipsesRoundness = " << light.superEllipsesRoundness << std::endl;
                }
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'd':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                light.superEllipsesTwist += 360.f / 40.f;
                if (light.superEllipsesTwist >= 360.f)
                    light.superEllipsesTwist = light.superEllipsesTwist - 360.f;

                std::cout << "superEllipsesTwist = " << light.superEllipsesTwist << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
        }
        break;

        case 'D':
        {
            BOOST_FOREACH(Light& light, lights)
            {
                light.superEllipsesTwist -= 360.f / 40.f;
                if (light.superEllipsesTwist < 0.f)
                    light.superEllipsesTwist = light.superEllipsesTwist + 360.0;

                std::cout << "superEllipsesTwist = " << light.superEllipsesTwist << std::endl;
            }

            update_light_state(multi_light_chunk, lights);
            glutPostRedisplay();
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
                glutPostRedisplay();
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
                glutPostRedisplay();
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

                glutPostRedisplay();
            }
        }
        break;

        case '5':
        {
            if (geom_nodes.size() <= 4.f * num_geometries)
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

                glutPostRedisplay();
            }
        }
        break;

        case 'm':
        {
            BOOST_FOREACH(OSG::MultiPropertyUBOChunk* ubo_geom_state, ubo_geom_states)
            {
                GeomState geom; geom.material_index = material_idx_die();
                update_geometry_material_state(ubo_geom_state, geom);
            }

            glutPostRedisplay();
        }
        break;

        case 's':
        {
            mgr->setStatistics(!mgr->getStatistics());
        }
        break;

        case 'h':
        {
            OSG::HDR2Stage* core = dynamic_cast<OSG::HDR2Stage*>(hdr_node->getCore());
            if (core)
                removeHDRStage();
            else
                createHDRStage();

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
    std::cout << "Space : toogle geometry simulation on/off" << std::endl;
    std::cout << "h     : toogle HDR stage usage on/off" << std::endl;
    std::cout << "l     : toogle light simulation on/off" << std::endl;
    std::cout << "m     : assign new color to geometry" << std::endl;
    std::cout << "r     : reset the example" << std::endl;
    std::cout << "s     : toogle statistics on/off" << std::endl;
    std::cout << "1     : only one light" << std::endl;
    std::cout << "2     : half number of lights" << std::endl;
    std::cout << "3     : double number of lights" << std::endl;
    std::cout << "4     : half number of geometry objects" << std::endl;
    std::cout << "5     : double number of geometry objects" << std::endl;
    std::cout << "e/E   : speed up/down simulation" << std::endl;
    std::cout << "o/O   : double/half simulation time interval" << std::endl;
    std::cout << "a/A   : increase/decrease linear attenuation factor" << std::endl;
    std::cout << "q/Q   : increase/decrease quadratic attenuation factor" << std::endl;
    std::cout << "x/X   : increase/decrease spot exponent" << std::endl;
    std::cout << "c/C   : increase/decrease inner super ellipses width" << std::endl;
    std::cout << "v/V   : increase/decrease inner super ellipses height" << std::endl;
    std::cout << "f/F   : increase/decrease ratio of outer to inner ellipses width" << std::endl;
    std::cout << "g/G   : increase/decrease ratio of outer to inner ellipses height" << std::endl;
    std::cout << "b/B   : increase/decrease super ellipses roundness" << std::endl;
    std::cout << "d/D   : increase/decrease super ellipses twist" << std::endl;
}

// ============================================================================
//
// Part VI: Cubic Bezier spline curve implementation
//
// ============================================================================

CubicBezierCurve::CubicBezierCurve(
    const OSG::Pnt3f& p0, 
    const OSG::Pnt3f& p1, 
    const OSG::Pnt3f& p2, 
    const OSG::Pnt3f& p3)
{
    p[0] = p0; p[1] = p1; p[2] = p2; p[3] = p3;
}

CubicBezierCurve::CubicBezierCurve(const CubicBezierCurve& rhs)
{
    p[0] = rhs.p[0]; p[1] = rhs.p[1]; p[2] = rhs.p[2]; p[3] = rhs.p[3];
}

CubicBezierCurve& CubicBezierCurve::operator=(const CubicBezierCurve& rhs)
{
    if (this != &rhs)
    {
        p[0] = rhs.p[0]; p[1] = rhs.p[1]; p[2] = rhs.p[2]; p[3] = rhs.p[3];
    }
    return *this;
}

OSG::Pnt3f CubicBezierCurve::operator()(OSG::Real32 t) const
{
    OSG_ASSERT(0.f <= t && t <= 1.f);

    OSG::Real32    e = 1.f - t;
    OSG::Real32 sq_e = e * e;
    OSG::Real32 sq_t = t * t;

    return      e * sq_e * p[0]
        + 3.f * t * sq_e * p[1].subZero()
        + 3.f * sq_t * e * p[2].subZero()
              + t * sq_t * p[3].subZero();
}

OSG::Vec3f CubicBezierCurve::tangent(OSG::Real32 t) const
{
    OSG::Vec3f tangent = fst_derivative(t);
    tangent.normalize();

    return tangent;
}

OSG::Vec3f CubicBezierCurve::normal(OSG::Real32 t) const
{
    OSG::Vec3f normal = binormal(t);
    normal.crossThis(tangent(t));
    normal.normalize();

    return normal;
}

OSG::Vec3f CubicBezierCurve::binormal(OSG::Real32 t) const
{
    OSG::Vec3f binormal = fst_derivative(t);
    binormal.crossThis(sec_derivative(t));
    binormal.normalize();

    while (OSG::osgAbs(binormal.length() - 1.f) >= OSG::Eps)
    {
        if (t + OSG::Eps <= 1.f)
            t += OSG::Eps;
        else if (t - OSG::Eps >= 0.f)
            t -= OSG::Eps;
        else
            OSG_ASSERT(false);

        binormal = fst_derivative(t);
        binormal.crossThis(sec_derivative(t));
        binormal.normalize();
    }

    return binormal;
}

OSG::Matrix CubicBezierCurve::frame(OSG::Real32 t, bool position_only) const
{
    OSG::Matrix mat;
    mat.identity();

    OSG::Vec3f P = (*this)(t).subZero();

    if (position_only)
    {
        mat.setTranslate(P);
    }
    else
    {
        OSG::Vec3f T = tangent(t);
        OSG::Vec3f N = normal(t);
        OSG::Vec3f B = binormal(t);
    

        OSG::Real32 lT = T.length();
        OSG::Real32 lN = N.length();
        OSG::Real32 lB = B.length();

        OSG::Real32 v1 = T.dot(N);
        OSG::Real32 v2 = T.dot(B);
        OSG::Real32 v3 = N.dot(B);

        OSG_ASSERT(OSG::osgAbs(T.length() - 1.f) < OSG::Eps);
        OSG_ASSERT(OSG::osgAbs(N.length() - 1.f) < OSG::Eps);
        OSG_ASSERT(OSG::osgAbs(B.length() - 1.f) < OSG::Eps);

        mat.setValue(T,N,B,P);
    }

    return mat;
}

OSG::Real32 CubicBezierCurve::length(OSG::UInt32 numSeg) const
{
    OSG_ASSERT(numSeg >= 2);

    OSG::Real32 d = 1.f / numSeg;
    OSG::Real32 t = d;
    OSG::Real32 l = 0.f;

    OSG::Pnt3f p0 = operator()(0.f);

    while (t <= 1.f)
    {
        OSG::Pnt3f p1 = operator()(t);

        l += (p1 - p0).length();
        t += d;
    }

    return l;
}

OSG::Vec3f CubicBezierCurve::fst_derivative(OSG::Real32 t) const
{
    OSG::Vec3f v10 = p[1] - p[0];
    OSG::Vec3f v21 = p[2] - p[1];
    OSG::Vec3f v32 = p[3] - p[2];

    OSG::Real32    e = 1.f - t;
    OSG::Real32 sq_e = e * e;
    OSG::Real32 sq_t = t * t;

    return 3.f * sq_e * v10 + 6.f * e * t * v21 + 3.f * sq_t * v32;
}

OSG::Vec3f CubicBezierCurve::sec_derivative(OSG::Real32 t) const
{
    OSG::Vec3f v210 = p[2] - 2.f * p[1] + p[0].subZero();
    OSG::Vec3f v321 = p[3] - 2.f * p[2] + p[1].subZero();

    OSG::Real32 e = 1.f - t;

    return 6.f * e * v210 + 6.f * t * v321;
}

OSG::Vec3f CubicBezierCurve::thr_devivative(OSG::Real32 t) const
{
    OSG::Vec3f v21 = p[2] - p[1];
    OSG::Vec3f v30 = p[3] - p[0];

    return -18.f * v21 + 6.f * v30;
}


SmoothCubicBezierSpline::SmoothCubicBezierSpline(const std::vector<OSG::Pnt3f>& knots)
: knots(knots)
{
    OSG_ASSERT(knots.size() > 3);

    points_t p1, p2;

    calc_ctrl_pnts(p1, p2);
    
    std::size_t n = knots.size() - 1;

    std::vector<OSG::Real32> lengths(n);
    OSG::Real32 L = 0.f;

    for (std::size_t i = 0; i < n; ++i)
    {
        curves.push_back(CubicBezierCurve(knots[i], p1[i], p2[i], knots[i+1]));

        lengths[i] = curves[i].length();
        L += lengths[i];
    }

    OSG_ASSERT(L > 0.f);

    OSG::Real32 d = 1.f / L;

    intervals.resize(n);

    intervals[0] = d * lengths[0];

    for (std::size_t i = 1; i < n-1; ++i)
    {
        intervals[i] = intervals[i-1] + d * lengths[i];
    }

    intervals[n-1] = 1.f;
}

SmoothCubicBezierSpline::SmoothCubicBezierSpline(const SmoothCubicBezierSpline& rhs)
: knots(rhs.knots)
, intervals(rhs.intervals)
, curves(rhs.curves)
{
}

SmoothCubicBezierSpline& SmoothCubicBezierSpline::operator=(const SmoothCubicBezierSpline& rhs)
{
    if (this != &rhs)
    {
        knots     = rhs.knots;
        intervals = rhs.intervals;
        curves    = rhs.curves;
    }
    return *this;
}

OSG::Pnt3f SmoothCubicBezierSpline::operator()(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx](t_(t, idx));
}

OSG::Vec3f SmoothCubicBezierSpline::tangent(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].tangent(t_(t, idx));
}

OSG::Vec3f SmoothCubicBezierSpline::normal(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].normal(t_(t, idx));
}

OSG::Vec3f SmoothCubicBezierSpline::binormal(OSG::Real32 t) const
{
    std::size_t idx = index(t);
    return curves[idx].binormal(t_(t, idx));
}

OSG::Matrix SmoothCubicBezierSpline::frame(OSG::Real32 t, bool position_only) const
{
    std::size_t idx = index(t);
    return curves[idx].frame(t_(t, idx), position_only);
}

OSG::Real32 SmoothCubicBezierSpline::length(OSG::UInt32 numSeg) const
{
    OSG::Real32 l = 0.f;
    BOOST_FOREACH(const CubicBezierCurve& c, curves)
    {
        l += c.length(numSeg);
    }
    return l;
}

void SmoothCubicBezierSpline::calc_ctrl_pnts(points_t& p1, points_t& p2) const
{
    namespace tp = boost::tuples;
    typedef tp::tuple<OSG::Real32, OSG::Real32, OSG::Real32> tuple_t;
    typedef std::vector<tuple_t> tuples_t;

    std::size_t n = knots.size()-1;

    p1.resize(n);
    p2.resize(n);

    tuples_t a(n), b(n), c(n), d(n);

    a[0] = tp::make_tuple(0.f, 0.f, 0.f);
    b[0] = tp::make_tuple(2.f, 2.f, 2.f);
    c[0] = tp::make_tuple(1.f, 1.f, 1.f);
    d[0] = tp::make_tuple(
        knots[0].x() + 2.f * knots[1].x(),
        knots[0].y() + 2.f * knots[1].y(),
        knots[0].z() + 2.f * knots[1].z());

    for (std::size_t i = 1; i < n-1; ++i)
    {
        a[i] = tp::make_tuple(1.f, 1.f, 1.f);
        b[i] = tp::make_tuple(4.f, 4.f, 4.f);
        c[i] = tp::make_tuple(1.f, 1.f, 1.f);
        d[i] = tp::make_tuple(
            4.f * knots[i].x() + 2.f * knots[i+1].x(),
            4.f * knots[i].y() + 2.f * knots[i+1].y(),
            4.f * knots[i].z() + 2.f * knots[i+1].z());
    }

    a[n-1] = tp::make_tuple(2.f, 2.f, 2.f);
    b[n-1] = tp::make_tuple(7.f, 7.f, 7.f);
    c[n-1] = tp::make_tuple(0.f, 0.f, 0.f);
    d[n-1] = tp::make_tuple(
        8.f * knots[n-1].x() + 2.f * knots[n].x(),
        8.f * knots[n-1].y() + 2.f * knots[n].y(),
        8.f * knots[n-1].z() + 2.f * knots[n].z());

    for (std::size_t i = 1; i < n; ++i)
    {
        tuple_t m = tp::make_tuple(
            a[i].get<0>() / b[i-1].get<0>(),
            a[i].get<1>() / b[i-1].get<1>(),
            a[i].get<2>() / b[i-1].get<2>());

            b[i] = tp::make_tuple(
                b[i].get<0>() - m.get<0>() * c[i-1].get<0>(),
                b[i].get<1>() - m.get<1>() * c[i-1].get<1>(),
                b[i].get<2>() - m.get<2>() * c[i-1].get<2>());

            d[i] = tp::make_tuple(
                d[i].get<0>() - m.get<0>() * d[i-1].get<0>(),
                d[i].get<1>() - m.get<1>() * d[i-1].get<1>(),
                d[i].get<2>() - m.get<2>() * d[i-1].get<2>());
    }

    p1[n-1].setValues(
        d[n-1].get<0>() / b[n-1].get<0>(),
        d[n-1].get<1>() / b[n-1].get<1>(),
        d[n-1].get<2>() / b[n-1].get<2>());

    for (long long i = n-2; i >= 0; --i)
    {
        p1[i].setValues(
            (d[i].get<0>() - c[i].get<0>() * p1[i+1].x()) / b[i].get<0>(),
            (d[i].get<1>() - c[i].get<1>() * p1[i+1].y()) / b[i].get<1>(),
            (d[i].get<2>() - c[i].get<2>() * p1[i+1].z()) / b[i].get<2>());
    }

    for (std::size_t i = 0; i < n-1; ++i)
    {
        p2[i].setValues(
            2.f * knots[i+1].x() - p1[i+1].x(),
            2.f * knots[i+1].y() - p1[i+1].y(),
            2.f * knots[i+1].z() - p1[i+1].z());
    }

    p2[n-1].setValues(
            0.5f * knots[n].x() - p1[n-1].x(),
            0.5f * knots[n].y() - p1[n-1].y(),
            0.5f * knots[n].z() - p1[n-1].z());
}

std::size_t SmoothCubicBezierSpline::index(OSG::Real32 t) const
{
    OSG_ASSERT(0.f <= t && t <= 1.f);

    std::vector<OSG::Real32>::const_iterator iter = std::lower_bound(intervals.begin(), intervals.end(), t);
    std::size_t r = iter - intervals.begin();
    return r;
}

OSG::Real32 SmoothCubicBezierSpline::t_(OSG::Real32 t, std::size_t idx) const
{
    OSG_ASSERT(idx < intervals.size());

    OSG::Real32 t0 = 0.f;
    OSG::Real32 t1 = 1.f;

    if (idx > 0) t0 = intervals[idx-1];
                 t1 = intervals[idx];

    OSG::Real32 r = (t - t0) / (t1 - t0);

    return r;
}

// ============================================================================
//
// Part VII: dice_knots helper implementation
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
// Part VIII: The shader programs
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

    ost     << "#version 440 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects:      enable"
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << ""
    << endl << "smooth in vec3 vNormalES;           // eye space normal"
    << endl << "smooth in vec3 vPositionES;         // eye space position"
    << endl << "smooth in vec3 vPositionWS;         // world space position"
    << endl << ""
    << endl << "const int num_materials = 5000;"
    << endl << ""
    << endl << "const int POINT_LIGHT       = 1;    // defined in OSGMultiLightChunk.h"
    << endl << "const int DIRECTIONAL_LIGHT = 2;"
    << endl << "const int SPOT_LIGHT        = 3;"
    << endl << "const int CINEMA_LIGHT      = 4;"
    << endl << ""
    << endl << "uniform mat4  OSGViewMatrix;"
    << endl << ""
    << endl << "struct Light"
    << endl << "{"
    << endl << "    mat4  eyeToLightSpaceMatrix;"
    << endl << "    vec3  position;                 // in world space"
    << endl << "    vec3  direction;                // in world space"
    << endl << "    vec3  Ia;"
    << endl << "    vec3  Id;"
    << endl << "    vec3  Is;"
    << endl << "    float const_attenuation;"
    << endl << "    float linear_attenuation;"
    << endl << "    float quadratic_attenuation;"
    << endl << "    float rangeCutOn;"
    << endl << "    float rangeCutOff;"
    << endl << "    float cosSpotlightAngle;"
    << endl << "    float spotExponent;"
    << endl << "    float innerSuperEllipsesWidth;"
    << endl << "    float innerSuperEllipsesHeight;"
    << endl << "    float outerSuperEllipsesWidth;"
    << endl << "    float outerSuperEllipsesHeight;"
    << endl << "    float superEllipsesRoundness;"
    << endl << "    float superEllipsesTwist;"
    << endl << "    int   type;                     // specific type of light: POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT or CINEMA_LIGHT"
    << endl << "    bool  enabled;                  // on/off state of light"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Lights"
    << endl << "{"
    << endl << "    Light light[];"
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
    << endl << "layout (std140) uniform GeomState"
    << endl << "{"
    << endl << "    int material_index;"
    << endl << "} geom_state;"
    << endl << ""
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation of the light based on its"
    << endl << "// constant, linear and quadratic attenuation factors"
    << endl << "// and the distance d of the light to the current point."
    << endl << "//"
    << endl << "float calcAttenuation(in float c, in float l, in float q, in float d)"
    << endl << "{"
    << endl << "    return 1.0 / (c + l*d + q*d*d);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Calculate the attenuation with respect to the spot light cone."
    << endl << "// Parameters:"
    << endl << "//      cutoff   :  cosine of the spot cutoff angle"
    << endl << "//      exponent :  the spot exponent"
    << endl << "//      l        :  normalized direction between fragment and light position"
    << endl << "//      s        :  normalized light direction"
    << endl << "//"
    << endl << "float spotAttenuation(in float cutoff, in float exponent, in vec3 l, in vec3 s)"
    << endl << "{"
    << endl << "    float attenuation = 0.0;"
    << endl << "    float l_dot_s = dot(-l, s);"
    << endl << "    if (l_dot_s >= cutoff)"
    << endl << "        attenuation = pow(l_dot_s, exponent);"
    << endl << "    return attenuation;"
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
    << endl << "    in int i,   // light identifier, i.e. current light"
    << endl << "    in int j,   // material identifier"
    << endl << "    in vec3 n,  // vertex normal in eye space"
    << endl << "    in vec3 v)  // view direction in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    //"
    << endl << "    // the light direction in eye space"
    << endl << "    //"
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
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
    << endl << "    return materials.material[j].emissive"
    << endl << "     + lights.light[i].Ia * materials.material[j].ambient"
    << endl << "     + lights.light[i].Id * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;"
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
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
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
    << endl << "    float attenuation = calcAttenuation("
    << endl << "                            lights.light[i].const_attenuation,"
    << endl << "                            lights.light[i].linear_attenuation,"
    << endl << "                            lights.light[i].quadratic_attenuation,"
    << endl << "                            d);"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + attenuation * lights.light[i].Ia * materials.material[j].ambient"
    << endl << "     + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;"
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
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    if (lights.light[i].rangeCutOff < d)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm dir from surface to light"
    << endl << "    "
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
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
    << endl << "    float attenuation = calcAttenuation("
    << endl << "                            lights.light[i].const_attenuation,"
    << endl << "                            lights.light[i].linear_attenuation,"
    << endl << "                            lights.light[i].quadratic_attenuation,"
    << endl << "                            d);"
    << endl << ""
    << endl << "    attenuation *= spotAttenuation(lights.light[i].cosSpotlightAngle, lights.light[i].spotExponent, l, s);"
    << endl << ""
    << endl << "    return materials.material[j].emissive"
    << endl << "     + attenuation * lights.light[i].Ia * materials.material[j].ambient"
    << endl << "     + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// cinema light contribution"
    << endl << "//"
    << endl << "vec3 cinemaLight("
    << endl << "    in int i,   // light identifier, i.e. current light"
    << endl << "    in int j,   // material identifier"
    << endl << "    in vec3 n,  // vertex normal in eye space"
    << endl << "    in vec3 v,  // view direction in eye space"
    << endl << "    in vec3 p)  // vertex position in eye space"
    << endl << "{"
    << endl << "    if (!lights.light[i].enabled)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    vec4 position = OSGViewMatrix * vec4(lights.light[i].position, 1.0);"
    << endl << "    vec3  l = position.xyz - p;                     // dir from surface to light position"
    << endl << "    float d = length(l);                            // dist from surface to light source"
    << endl << ""
    << endl << "    if (lights.light[i].rangeCutOff < d)"
    << endl << "        return vec3(0.0, 0.0, 0.0);"
    << endl << ""
    << endl << "    l = normalize(l);                               // norm dir from surface to light"
    << endl << "    "
    << endl << "    vec4 direction = OSGViewMatrix * vec4(lights.light[i].direction, 0.0);"
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
    << endl << "    float attenuation = calcAttenuation("
    << endl << "                            lights.light[i].const_attenuation,"
    << endl << "                            lights.light[i].linear_attenuation,"
    << endl << "                            lights.light[i].quadratic_attenuation,"
    << endl << "                            d);"
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
    << endl << "    return materials.material[j].emissive"
    << endl << "     + attenuation * lights.light[i].Ia * materials.material[j].ambient"
    << endl << "     + attenuation * lights.light[i].Id * materials.material[j].diffuse  * n_dot_l"
    << endl << "     + attenuation * lights.light[i].Is * materials.material[j].specular * (m+8)*0.0125 * pf;"
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
    << endl << "    int num_lights = lights.light.length();"
    << endl << ""
    << endl << "    for (int i = 0; i < num_lights; ++i)"
    << endl << "    {"
    << endl << "        switch (lights.light[i].type)"
    << endl << "        {"
    << endl << "            case       POINT_LIGHT: color +=       pointLight(i, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case DIRECTIONAL_LIGHT: color += directionalLight(i, geom_state.material_index, N, V);               break;"
    << endl << "            case        SPOT_LIGHT: color +=        spotLight(i, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case      CINEMA_LIGHT: color +=      cinemaLight(i, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "        }"
    << endl << "    }"
    << endl << "    vFragColor = vec4(color, materials.material[geom_state.material_index].opacity);"
    << endl << ""
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

