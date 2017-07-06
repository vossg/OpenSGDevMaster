// OpenSG Example: MultiRangeLightClusterShading
//
// This example implements a forward cluster shading algorithm according to
//      Ola Olsson et.al and Emil Persson
//      https://newq.net/publications/more/s2015-many-lights-course
//
// It uses the MultiLightChunk for the light representation and allows
// to visualize the lights frustums. It shows a simple scene that
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
#include <OpenSG/OSGInverseTransform.h>
#include <OpenSG/OSGShaderProgramChunk.h>
#include <OpenSG/OSGShaderProgram.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGShaderProgramVariables.h>
#include <OpenSG/OSGShaderStorageBufferObjChunk.h>
#include <OpenSG/OSGShaderStorageBufferObjStdLayoutChunk.h>
#include <OSGUniformBufferObjChunk.h>
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

//
// The example uses cubic bezier curves for the light and geometry motion simulation.
// The smooth curves are piecewise constructed from these cubic bezier curves.
//
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
// Part: Math helper
//      - reflect_at_plane_through_orgin
//      - rotate_a_into_direction_b
//
// ============================================================================

//
// The plane normal N is expected to be normalized
//
OSG::Matrix reflect_at_plane_through_orgin(const OSG::Vec3f& N)
{
    OSG::Real32 xx = N[0]*N[0];
    OSG::Real32 yy = N[1]*N[1];
    OSG::Real32 zz = N[2]*N[2];
    OSG::Real32 xy = N[0]*N[1];
    OSG::Real32 xz = N[0]*N[2];
    OSG::Real32 yz = N[1]*N[2];

    return OSG::Matrix(1.f-2.f*xx,    -2.f*xy,    -2.f*xz, 0.f,
                          -2.f*xy, 1.f-2.f*yy,    -2.f*yz, 0.f,
                          -2.f*xz,    -2.f*yz, 1.f-2.f*zz, 0.f,
                              0.f,        0.f,        0.f, 1.f);
}

//
// The resulting orthonormal matrix rotates vector a into the direction of vector b.
// If b is a unit vector then the resulting vector b' = M*b is identical
// to b and for some unit vector a' the resulting vector b' = M*a' is also a unit
// vector. Neither the length of a or b is used in the calculation of the
// rotation matrix!
//

OSG::Matrix rotate_a_into_direction_b(OSG::Vec3f a, OSG::Vec3f b)
{
    OSG::Matrix R;

    a.normalize();
    b.normalize();

    OSG::Real32 c = a.dot(b);
    if (OSG::osgAbs(1.f - c) < OSG::Eps)
        return R;

    if (OSG::osgAbs(-1.f - c) < OSG::Eps)
        return reflect_at_plane_through_orgin(a);

    OSG::Vec3f v = a.cross(b);

    OSG::Matrix skew( 0.f,-v[2], v[1],  0.f,
                     v[2],  0.f,-v[0],  0.f,
                    -v[1], v[0],  0.f,  0.f,
                      0.f,  0.f,  0.f,  0.f);

    OSG::Matrix T(skew); T.mult(skew); T.scale(1.f / (1.f + c));

    R.add(skew); R.add(T);

    return R;
}

/*
OSG::Matrix rotate_a_into_direction_b(OSG::Vec3f a, OSG::Vec3f b)
{
    OSG::Matrix R;

    a.normalize();
    b.normalize();

    OSG::Real32 c = a.dot(b);
    if (OSG::osgAbs(1.f - c) < OSG::Eps)
        return R;

    if (OSG::osgAbs(-1.f - c) < OSG::Eps)
        return reflect_at_plane_through_orgin(a);

    OSG::Vec3f v = a.cross(b);

    OSG::Real32 theta = OSG::osgACos(c);

    OSG::Matrix skew( 0.f,-v[2], v[1],  0.f,
                     v[2],  0.f,-v[0],  0.f,
                    -v[1], v[0],  0.f,  0.f,
                      0.f,  0.f,  0.f,  0.f);

    OSG::Matrix T(skew); T.mult(skew);

    skew.scale(OSG::osgSin(theta)); 
    T.scale(1 - OSG::osgCos(theta));

    R.add(skew); R.add(T);

    return R;
}
*/

// ============================================================================
//
// Part: Extensions for simple geometry generation
//      - makeSpotGeo
//      - makePyramidGeo
//      - makeCinemaGeo
//
// ============================================================================

OSG::GeometryTransitPtr makeSpotGeo(
    OSG::Real32 R,              // the spot range/radius of influence
    OSG::Real32 angle,          // the spot half angle in degree
    OSG::UInt32 slices,         // the number of subdivisions in z-Dir, i.e. in spot direction
    OSG::UInt32 sides)          // the number of circle subdivisions
{
    OSG::GeoUInt8PropertyRefPtr   types = OSG::GeoUInt8Property::create();
    OSG::GeoUInt32PropertyRefPtr  lens  = OSG::GeoUInt32Property::create();
    OSG::GeoPnt3fPropertyRefPtr   pnts  = OSG::GeoPnt3fProperty::create();
    OSG::GeoVec3fPropertyRefPtr   norms = OSG::GeoVec3fProperty::create();

    OSG::GeoUInt8Property::StoredFieldType  *t  = types->editFieldPtr();
    OSG::GeoUInt32Property::StoredFieldType *l  = lens ->editFieldPtr();
    OSG::GeoPnt3fProperty::StoredFieldType  *p  = pnts ->editFieldPtr();
    OSG::GeoVec3fProperty::StoredFieldType  *n  = norms->editFieldPtr();

    // get even slices and sides
    if ( (slices & 1) == 1 ) 
        slices += 1;

    if ( (sides & 1) == 1 ) 
        sides += 1;

    OSG::Real32 a_cone = OSG::osgDegree2Rad(angle);
    OSG::Real32 h_cone = R * OSG::osgCos(a_cone);
    OSG::Real32 d_cone = h_cone / slices;

    OSG::Real32 delta_phi = 2.f * OSG::Pi / (sides-1);

    OSG::Vec3f ey(0,1,0);

    typedef std::vector<OSG::Pnt3f> VecPntsT;

    VecPntsT vecOddPnts(sides), vecEvenPnts(sides);
    VecPntsT* pvecLast = &vecOddPnts;
    VecPntsT* pvecCurr = &vecEvenPnts;

    //
    // First the cone itself
    //
    std::vector<OSG::Vec3f> vecNormals(sides);
    for (OSG::UInt32 i = 0; i < sides; ++i)
    {
        OSG::Real32 phi = i * delta_phi;

        vecNormals[i] = -OSG::Vec3f(OSG::osgCos(a_cone) * OSG::osgCos(phi), OSG::osgSin(a_cone), OSG::osgCos(a_cone) * OSG::osgSin(phi));
    }

    OSG::Pnt3f pT(0,0,0);       // tip of spot cone

    (*pvecLast)[0] = pT;

    for (OSG::UInt32 j = 1; j <= slices; ++j)
    {
        OSG::Real32 l_cone = j * d_cone;
        OSG::Real32 r_cone = l_cone * OSG::osgTan(a_cone);

        OSG::Pnt3f pR = pT + l_cone * ey;

        OSG::Real32 d_phi = (j & 0) ?  delta_phi : delta_phi + delta_phi/2.f;

        OSG::Real32 phi = (j & 0) ?  0 : delta_phi/2.f;

        for (OSG::UInt32 i = 0; i < sides-1; ++i)
        {
            phi += delta_phi;
            (*pvecCurr)[i] = pR + r_cone * OSG::Vec3f(OSG::osgSin(phi), 0, -OSG::osgCos(phi));
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back((*pvecLast)[0]);
            n->push_back(OSG::Vec3f(0,-1,0));

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecCurr)[i]);
                n->push_back(vecNormals[i]);
            }
        }
        else
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);
                
                n->push_back(vecNormals[i]);
                n->push_back(vecNormals[i]);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    //
    // Second the sphere cap
    //
    OSG::Real32 d_alpha = a_cone / (slices-1);

    for (OSG::UInt32 j = 0; j < slices; ++j)
    {
        if (j < slices-1)
        {
            OSG::Real32 da_cone = a_cone - j * d_alpha;

            OSG::Real32 l_cone = R * OSG::osgCos(da_cone);
            OSG::Real32 r_cone = R * OSG::osgSin(da_cone);

            OSG::Pnt3f pj = pT + l_cone * ey;

            OSG::Real32 phi = (j & 0) ?  0 : delta_phi/2.f;

            for (OSG::UInt32 i = 0; i < sides-1; ++i)
            {
                phi += delta_phi;
                (*pvecCurr)[i] = pj + r_cone * OSG::Vec3f(OSG::osgSin(phi), 0, -OSG::osgCos(phi));

                OSG::Vec3f n = (*pvecCurr)[i] - pT;
                n.normalize();
                vecNormals[i] = n;
            }

            (*pvecCurr)[sides-1] = (*pvecCurr)[0];

            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);
                
                n->push_back(vecNormals[i]);
                n->push_back(vecNormals[i]);
            }
        }
        else 
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back(pT + R * ey);
            n->push_back(OSG::Vec3f(0,-1,0));

            for (OSG::Int32 i = sides-1; i >= 0; --i)
            {
                p->push_back((*pvecLast)[i]);
                n->push_back(vecNormals[i]);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    OSG::GeometryTransitPtr geo = OSG::Geometry::create();

    geo->setTypes    (types);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (norms);

    geo->setMaterial(OSG::getDefaultUnlitMaterial());

    return geo;
}

OSG::GeometryTransitPtr makeCinemaGeo(
    OSG::Real32 a,          // superellipses width
    OSG::Real32 b,          // superellipses height
    OSG::Real32 r,          // superellipses roundness parameter
    OSG::Real32 theta,      // superellipses twist parameter in radians
    OSG::Real32 h,          // z-height of the body
    OSG::UInt32 slices,     // the number of subdivisions in z-Dir, i.e. in spot direction
    OSG::UInt32 sides)      // the number of circle subdivisions
{
    OSG::GeoUInt8PropertyRefPtr   types = OSG::GeoUInt8Property::create();
    OSG::GeoUInt32PropertyRefPtr  lens  = OSG::GeoUInt32Property::create();
    OSG::GeoPnt3fPropertyRefPtr   pnts  = OSG::GeoPnt3fProperty::create();
    OSG::GeoVec3fPropertyRefPtr   norms = OSG::GeoVec3fProperty::create();

    OSG::GeoUInt8Property::StoredFieldType  *t  = types->editFieldPtr();
    OSG::GeoUInt32Property::StoredFieldType *l  = lens ->editFieldPtr();
    OSG::GeoPnt3fProperty::StoredFieldType  *p  = pnts ->editFieldPtr();
    OSG::GeoVec3fProperty::StoredFieldType  *n  = norms->editFieldPtr();

    // get even slices and sides
    if ( (slices & 1) == 1 ) 
        slices += 1;

    if ( (sides & 1) == 1 ) 
        sides += 1;

    OSG::Real32 cos_theta = OSG::osgCos(theta);
    OSG::Real32 sin_theta = OSG::osgSin(theta);

    OSG::Real32 d_body = h / slices;

    OSG::Real32 delta_phi = 2.f * OSG::Pi / (sides-1);

    OSG::Real32 two_inv_r = 2.0/r;

    OSG::Vec3f ey(0,1,0);

    typedef std::vector<OSG::Pnt3f> VecPntsT;

    VecPntsT vecOddPnts(sides), vecEvenPnts(sides);
    VecPntsT* pvecLast = &vecOddPnts;
    VecPntsT* pvecCurr = &vecEvenPnts;

    //
    // First the superellipses body itself
    //
    OSG::Pnt3f pT(0,0,0);       // tip of body

    (*pvecLast)[0] = pT;

    for (OSG::UInt32 j = 1; j <= slices; ++j)
    {
        OSG::Real32 l_body = j * d_body;

        OSG::Pnt3f pR = pT + l_body * ey;

        OSG::Real32 A = l_body * a;
        OSG::Real32 B = l_body * b;

        OSG::Real32 phi = 0.f;

        for (OSG::UInt32 i = 0; i < sides-1; ++i)
        {
            OSG::Real32 c = OSG::osgCos(phi);
            OSG::Real32 s = OSG::osgSin(phi);

            OSG::Real32 x = A * OSG::osgSgn(c) * OSG::osgPow(OSG::osgAbs(c), two_inv_r);
            OSG::Real32 z = B * OSG::osgSgn(s) * OSG::osgPow(OSG::osgAbs(s), two_inv_r);

            OSG::Pnt3f  p = pR + OSG::Vec3f(
                                       x * cos_theta - z * sin_theta, 
                                       0,
                                       x * sin_theta + z * cos_theta
                                    );

            OSG::Real32 L = p.subZero().length();

            if (L > h)
            {
                OSG::Vec3f v = p.subZero();
                v.normalize();
                v *= h;
                p = v.addToZero();
            }

            (*pvecCurr)[i] = p;

            phi += delta_phi;
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back((*pvecLast)[0]);
            n->push_back(OSG::Vec3f(0,-1,0));

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecCurr)[i]);

                OSG::Vec3f v0;
                OSG::Vec3f v1;

                if (i < sides-1)
                {
                    v0 = (*pvecCurr)[i]   - (*pvecLast)[0];
                    v1 = (*pvecCurr)[i+1] - (*pvecLast)[0];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecCurr)[0] - (*pvecLast)[0];
                    v1 = (*pvecCurr)[1] - (*pvecLast)[0];
                }

                OSG::Vec3f v = v1.cross(v0);
                v.normalize();
                n->push_back(v);
            }
        }
        else
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);

                OSG::Vec3f v0;
                OSG::Vec3f v1;
                OSG::Vec3f v2;
                
                if (i < sides-1)
                {
                    v0 = (*pvecLast)[i+1] - (*pvecCurr)[i];
                    v1 = (*pvecLast)[i+1] - (*pvecLast)[i];
                    v2 = (*pvecCurr)[i+1] - (*pvecLast)[i+1];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecLast)[1] - (*pvecCurr)[0];
                    v1 = (*pvecLast)[1] - (*pvecLast)[0];
                    v2 = (*pvecCurr)[1] - (*pvecLast)[1];
                }

                OSG::Vec3f n0 = v1.cross(v0);
                OSG::Vec3f n1 = v2.cross(v1);

                n0.normalize();
                n1.normalize();

                n->push_back(n0);
                n->push_back(n1);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    //
    // Second the sphere cap
    //
    OSG::Real32 delta_a = a / (slices - 1);
    OSG::Real32 delta_b = b / (slices - 1);

    OSG::Pnt3f pE = pT + h * ey;

    for (OSG::Int32 j = slices-2; j >= 0; --j)
    {
        OSG::Real32 A = h * delta_a * j;
        OSG::Real32 B = h * delta_b * j;

        OSG::Real32 phi = 0.f;

        for (OSG::UInt32 i = 0; i < sides-1; ++i)
        {
            OSG::Real32 c = OSG::osgCos(phi);
            OSG::Real32 s = OSG::osgSin(phi);

            OSG::Real32 x = A * OSG::osgSgn(c) * OSG::osgPow(OSG::osgAbs(c), two_inv_r);
            OSG::Real32 z = B * OSG::osgSgn(s) * OSG::osgPow(OSG::osgAbs(s), two_inv_r);

            OSG::Pnt3f  p = pE + OSG::Vec3f(
                                        x * cos_theta - z * sin_theta, 
                                        0,
                                        x * sin_theta + z * cos_theta
                                    );

            OSG::Real32 L = p.subZero().length();

            if (L > h)
            {
                OSG::Vec3f v = p.subZero();
                v.normalize();
                v *= h;
                p = v.addToZero();
            }

            (*pvecCurr)[i] = p;

            phi += delta_phi;
        }

        (*pvecCurr)[sides-1] = (*pvecCurr)[0];
        
        if (j < OSG::Int32(slices-1) && j > 0)
        {
            t->push_back(GL_TRIANGLE_STRIP);
            l->push_back(2*sides);

            for (OSG::UInt32 i = 0; i < sides; ++i)
            {
                p->push_back((*pvecLast)[i]);
                p->push_back((*pvecCurr)[i]);

                OSG::Vec3f v0;
                OSG::Vec3f v1;
                OSG::Vec3f v2;
                
                if (i < sides-1)
                {
                    v0 = (*pvecLast)[i+1] - (*pvecCurr)[i];
                    v1 = (*pvecLast)[i+1] - (*pvecLast)[i];
                    v2 = (*pvecCurr)[i+1] - (*pvecLast)[i+1];
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecLast)[1] - (*pvecCurr)[0];
                    v1 = (*pvecLast)[1] - (*pvecLast)[0];
                    v2 = (*pvecCurr)[1] - (*pvecLast)[1];
                }

                OSG::Vec3f n0 = v1.cross(v0);
                OSG::Vec3f n1 = v2.cross(v1);

                n0.normalize();
                n1.normalize();

                n->push_back(n0);
                n->push_back(n1);
            }
        }

        if (j == 1)
        {
            t->push_back(GL_TRIANGLE_FAN);
            l->push_back(1 + sides);

            p->push_back(pE);
            n->push_back(OSG::Vec3f(0,1,0));

            for (OSG::Int32 i = sides-1; i >= 0; --i)
            {
                p->push_back((*pvecCurr)[i]);

                OSG::Vec3f v0;
                OSG::Vec3f v1;

                if (i < OSG::Int32(sides-1))
                {
                    v0 = (*pvecCurr)[i]   - pE;
                    v1 = (*pvecCurr)[i+1] - pE;
                }
                else if (i == sides-1)
                {
                    v0 = (*pvecCurr)[0] - pE;
                    v1 = (*pvecCurr)[1] - pE;
                }

                OSG::Vec3f v = v1.cross(v0);
                v.normalize();
                n->push_back(v);
            }
        }

        std::swap(pvecLast, pvecCurr);
    }

    OSG::GeometryTransitPtr geo = OSG::Geometry::create();

    geo->setTypes    (types);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (norms);

    geo->setMaterial(OSG::getDefaultUnlitMaterial());

    return geo;
}

OSG::GeometryTransitPtr makePyramidGeo(
    const OSG::Pnt3f& nlt, const OSG::Pnt3f& nlb,
    const OSG::Pnt3f& nrt, const OSG::Pnt3f& nrb,
    const OSG::Pnt3f& flt, const OSG::Pnt3f& flb,
    const OSG::Pnt3f& frt, const OSG::Pnt3f& frb)
{
    OSG::GeoUInt8PropertyRefPtr type = OSG::GeoUInt8Property::create();
    type->addValue(GL_QUADS);

    OSG::GeoUInt32PropertyRefPtr lens = OSG::GeoUInt32Property::create();
    lens->addValue(6 * 4);

    OSG::GeoPnt3fPropertyRefPtr  pnts = OSG::GeoPnt3fProperty::create();
    // front face
    pnts->addValue(nlb);
    pnts->addValue(nrb);
    pnts->addValue(nrt);
    pnts->addValue(nlt);

    // back face
    pnts->addValue(frb);
    pnts->addValue(flb);
    pnts->addValue(flt);
    pnts->addValue(frt);

    // left face
    pnts->addValue(flb);
    pnts->addValue(nlb);
    pnts->addValue(nlt);
    pnts->addValue(flt);

    // right face
    pnts->addValue(nrb);
    pnts->addValue(frb);
    pnts->addValue(frt);
    pnts->addValue(nrt);

    // top face
    pnts->addValue(nrt);
    pnts->addValue(frt);
    pnts->addValue(flt);
    pnts->addValue(nlt);

    // bottom face
    pnts->addValue(nlb);
    pnts->addValue(flb);
    pnts->addValue(frb);
    pnts->addValue(nrb);

    OSG::GeoVec3fPropertyRefPtr normals = OSG::GeoVec3fProperty::create();
    OSG::Vec3f v1, v2, n;

    // front face
    v1 = nrb - nlb; v2 = nlt - nlb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // back face
    v1 = flb - frb; v2 = frt - frb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // left face
    v1 = nlb - flb; v2 = flt - flb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // right face
    v1 = frb - nrb; v2 = nrt - nrb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // top face
    v1 = frt - nrt; v2 = nlt - nrt; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    // bottom face
    v1 = flb - nlb; v2 = nrb - nlb; n = v1.cross(v2); n.normalize(); for (int i = 0; i < 4; ++i) normals->addValue(n);

    OSG::GeometryTransitPtr geo = OSG::Geometry::create();

    geo->setTypes    (type);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals  (normals);

    geo->setMaterial(OSG::getDefaultUnlitMaterial());

    return geo;
}

// ============================================================================
//
// Part: Declaration/Implementation of
//      - type VecImageDataT
//      - type VecLightIndexT
//      - struct DispatchData
//      - struct ClusteringData
//      - struct TestData
//      - light grid image
//      - light grid texture object
//      - light grid image texture chunk
//      - struct Frustum and VecFrustumsT
//      - NdcFromScreen, NdcFromScreen, ClipFromNdc, EyeFromClip, EyeFromNdc
//      - calc_ortho_frustums_cpu
//      - calc_persp_frustums_cpu
//      - create_frustum_state, update_frustum_state
//      - create_index_state, update_index_state
//      - create_light_index_counter_state
//      - struct Sphere and struct Cone
//      - SphereInsidePlane, SphereInsideFrustum, PointInsidePlane, ConeInsidePlane, ConeInsideFrustum
//      - transformToEyeSpace
//      - PointLightInsideFrustum, SpotLightInsideFrustum
//      - cluster_k, cluster_z, cluster_test
//      - cullLights
//      - struct Light and type VecLightsT,
//      - struct Material and type VecMaterialsT,
//      - struct GeomState
//  and corresponding initialization routines.
//
// ============================================================================

typedef std::vector<std::pair<OSG::UInt32, OSG::UInt32> >   VecImageDataT;
typedef std::vector<OSG::UInt32>                            VecLightIndexT;

//
// Data used by the frustum plane computation shader
//
struct DispatchData
{
    DispatchData() : matTransf(), viewport(), numTiles() {}

    OSG::Matrix matTransf;
    OSG::Vec4u  viewport;
    OSG::Vec2i  numTiles;

    static OSG::UInt32 matTransf_id;
    static OSG::UInt32 viewport_id;
    static OSG::UInt32 numTiles_id;
};

OSG::UInt32 DispatchData::matTransf_id = 0;
OSG::UInt32 DispatchData::viewport_id  = 0;
OSG::UInt32 DispatchData::numTiles_id  = 0;

OSG::UniformBufferObjChunkTransitPtr create_dispatch_data(const DispatchData& data)
{
    OSG::UniformBufferObjChunkRefPtr chunk = OSG::UniformBufferObjChunk::create();

    DispatchData::matTransf_id = chunk->addMat4 ("DispatchData.matTransf");
    DispatchData:: viewport_id = chunk->addUVec4("DispatchData.viewport");
    DispatchData:: numTiles_id = chunk->addIVec2("DispatchData.numTiles");

    chunk->setMat4 (DispatchData::matTransf_id, data.matTransf);
    chunk->setUVec4(DispatchData:: viewport_id, data.viewport);
    chunk->setIVec2(DispatchData:: numTiles_id, data.numTiles);

    chunk->setBlockName("DispatchData");
    chunk->setUsage(GL_DYNAMIC_DRAW);

    return OSG::UniformBufferObjChunkTransitPtr(chunk);
}

void update_dispatch_data(OSG::UniformBufferObjChunk* chunk, const DispatchData& data)
{
    if (chunk)
    {
        chunk->setMat4 (DispatchData::matTransf_id, data.matTransf);
        chunk->setUVec4(DispatchData:: viewport_id, data.viewport);
        chunk->setIVec2(DispatchData:: numTiles_id, data.numTiles);
    }
}

//
// The clustering data is used in the light cull shader and in the fragment shader. 
// Its data is used for:
//      - the cluster_k key evaluation
//      - the cluster_z eye space z evaluation
//
// At the moment we support two cluster_k/cluster_z functions: cluster_k/cluster_z and cluster_k_verbose/cluster_z_verbose.
// Ultimatively only the cluster_k/cluster_z variant will be used. The other one is only for
// testing purpose.
//
struct ClusteringData
{
    ClusteringData() 
    : zNear(0.f)
    , zFar(0.f)
    //, D(0.f)
    , nD(0.f)
    , a(0.f)
    , b(0.f)
    //, c(0)
    , c_1(0)
    , p_v(0,0)
    //, n_c(0,0,0)
    , t_v(0)
    {}

    OSG::Real32 zNear;  // positive near plane distance from eye zNear > 0
    OSG::Real32 zFar;   // positive  far plane distance from eye zFar > zNear > 0
    //OSG::Real32 D;      // positive near plane offset D >= 0                            // for testing
    OSG::Real32 nD;     // zNear + D : shader optimization
    OSG::Real32 lg_nD;  // log2(nD) : shader optimization
    OSG::Real32 a;      // precalculated factor (c-1)/log2(f/(n+D))
    OSG::Real32 b;      // precalculated factor log2(f/(n+D))/(c-1)
    //OSG::Int32  c;      // number of cluster planes                                     // for testing
    OSG::Int32  c_1;    // number of cluster planes minus one : shader optimization
    OSG::Vec2i  p_v;    // viewport corner points
    //OSG::Vec3i  n_c;    // number of clusters                                           // for testing
    OSG::Int32  t_v;    // test dependent content                                         // for testing

    static OSG::UInt32 zNear_id;
    static OSG::UInt32  zFar_id;
    //static OSG::UInt32     D_id;
    static OSG::UInt32    nD_id;
    static OSG::UInt32 lg_nD_id;
    static OSG::UInt32     a_id;
    static OSG::UInt32     b_id;
    //static OSG::UInt32     c_id;
    static OSG::UInt32   c_1_id;
    static OSG::UInt32   p_v_id;
    //static OSG::UInt32   n_c_id;
    static OSG::UInt32   t_v_id;
};

OSG::UInt32 ClusteringData::zNear_id = 0;
OSG::UInt32 ClusteringData:: zFar_id = 0;
//OSG::UInt32 ClusteringData::    D_id = 0;
OSG::UInt32 ClusteringData::   nD_id = 0;
OSG::UInt32 ClusteringData::lg_nD_id = 0;
OSG::UInt32 ClusteringData::    a_id = 0;
OSG::UInt32 ClusteringData::    b_id = 0;
//OSG::UInt32 ClusteringData::    c_id = 0;
OSG::UInt32 ClusteringData::  c_1_id = 0;
OSG::UInt32 ClusteringData::  p_v_id = 0;
//OSG::UInt32 ClusteringData::  n_c_id = 0;
OSG::UInt32 ClusteringData::  t_v_id = 0;

OSG::UniformBufferObjChunkTransitPtr create_clustering_data(const ClusteringData& data)
{
    OSG::UniformBufferObjChunkRefPtr chunk = OSG::UniformBufferObjChunk::create();

    ClusteringData::zNear_id = chunk->addFloat("ClusteringData.zNear");
    ClusteringData:: zFar_id = chunk->addFloat("ClusteringData.zFar");
    //ClusteringData::    D_id = chunk->addFloat("ClusteringData.D");
    ClusteringData::   nD_id = chunk->addFloat("ClusteringData.nD");
    ClusteringData::lg_nD_id = chunk->addFloat("ClusteringData.lg_nD");
    ClusteringData::    a_id = chunk->addFloat("ClusteringData.a");
    ClusteringData::    b_id = chunk->addFloat("ClusteringData.b");
    //ClusteringData::    c_id = chunk->addInt  ("ClusteringData.c");
    ClusteringData::  c_1_id = chunk->addInt  ("ClusteringData.c_1");
    ClusteringData::  p_v_id = chunk->addIVec2("ClusteringData.p_v");
    //ClusteringData::  n_c_id = chunk->addIVec3("ClusteringData.n_c");
    ClusteringData::  t_v_id = chunk->addInt  ("ClusteringData.t_v");

    chunk->setFloat(ClusteringData::zNear_id, data.zNear);
    chunk->setFloat(ClusteringData:: zFar_id, data.zFar);
    //chunk->setFloat(ClusteringData::    D_id, data.D);
    chunk->setFloat(ClusteringData::   nD_id, data.nD);
    chunk->setFloat(ClusteringData::lg_nD_id, data.lg_nD);
    chunk->setFloat(ClusteringData::    a_id, data.a);
    chunk->setFloat(ClusteringData::    b_id, data.b);
    //chunk->setInt  (ClusteringData::    c_id, data.c);
    chunk->setInt  (ClusteringData::  c_1_id, data.c_1);
    chunk->setIVec2(ClusteringData::  p_v_id, data.p_v);
    //chunk->setIVec3(ClusteringData::  n_c_id, data.n_c);
    chunk->setInt  (ClusteringData::  t_v_id, data.t_v);

    chunk->setBlockName("ClusteringData");
    chunk->setUsage(GL_STATIC_DRAW);

    return OSG::UniformBufferObjChunkTransitPtr(chunk);
}

void update_clustering_data(OSG::UniformBufferObjChunk* chunk, const ClusteringData& data)
{
    if (chunk)
    {
        chunk->setFloat(ClusteringData::zNear_id, data.zNear);
        chunk->setFloat(ClusteringData:: zFar_id, data.zFar);
        //chunk->setFloat(ClusteringData::    D_id, data.D);
        chunk->setFloat(ClusteringData::   nD_id, data.nD);
        chunk->setFloat(ClusteringData::lg_nD_id, data.lg_nD);
        chunk->setFloat(ClusteringData::    a_id, data.a);
        chunk->setFloat(ClusteringData::    b_id, data.b);
        //chunk->setInt  (ClusteringData::    c_id, data.c);
        chunk->setInt  (ClusteringData::  c_1_id, data.c_1);
        chunk->setIVec2(ClusteringData::  p_v_id, data.p_v);
        //chunk->setIVec3(ClusteringData::  n_c_id, data.n_c);
        chunk->setInt  (ClusteringData::  t_v_id, data.t_v);
    }
}

//
// The test data is used to compare the cpu with gpu computation
//
struct TestData
{
    static const OSG::UInt32 num_array_elements = num_test_val_entries;
    TestData()
    : value01(0.f)
    , value02(0.f)
    , value03(0.f)
    , value04(0.f)
    , value05(0.f,0.f,0.f)
    , value06(0.f,0.f,0.f)
    , value07(0)
    , value08(0)
    , value09(0)
    , value10(0)
    , value11(0,0,0)
    , value12(0,0,0)
    , value13(num_array_elements, 0.f)
    , value14(num_array_elements, 0.f)
    , value15(num_array_elements, 0)
    , value16(num_array_elements, OSG::Vec3f(0.f,0.f,0.f))
    , value17(num_array_elements, OSG::Vec3f(0.f,0.f,0.f))
    {}

    void clear()
    {
        value01 = 0.f;
        value02 = 0.f;
        value03 = 0.f;
        value04 = 0.f;
        value05 = OSG::Vec3f(0.f,0.f,0.f);
        value06 = OSG::Vec3f(0.f,0.f,0.f);
        value07 = 0;
        value08 = 0;
        value09 = 0;
        value10 = 0; 
        value11 = OSG::Vec3i(0,0,0);
        value12 = OSG::Vec3u(0,0,0);

        for (OSG::UInt32 i = 0; i < num_array_elements; ++i)
        {
            value13[i] = 0.f;
            value14[i] = 0.f;
            value15[i] = 0; 
            value16[i] = OSG::Vec3f(0.f,0.f,0.f); 
            value17[i] = OSG::Vec3f(0.f,0.f,0.f);
        }
    }

    OSG::Real32 value01;
    OSG::Real32 value02;
    OSG::Real32 value03;
    OSG::Real32 value04;
    OSG::Vec3f  value05;
    OSG::Vec3f  value06;
    OSG::Int32  value07;
    OSG::Int32  value08;
    OSG::UInt32 value09;
    OSG::UInt32 value10;
    OSG::Vec3i  value11;
    OSG::Vec3u  value12;

    std::vector<OSG::Real32> value13;
    std::vector<OSG::Real32> value14;
    std::vector<OSG::UInt32> value15;
    std::vector<OSG::Vec3f>  value16;
    std::vector<OSG::Vec3f>  value17;
};

TestData globalTestData;

std::size_t calc_test_data_buffer_size(const TestData& data)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Real32);
    ao = OSG::alignOffset( 4, bo); bo = ao;
    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Real32);
    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Real32);
    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Real32);

    ao = OSG::alignOffset(16, bo); bo = ao + sizeof(OSG::Vec3f);
    ao = OSG::alignOffset(16, bo); bo = ao + sizeof(OSG::Vec3f);

    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Int32);
    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Int32);

    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::UInt32);
    ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::UInt32);

    ao = OSG::alignOffset(16, bo); bo = ao + sizeof(OSG::Vec3i);
    ao = OSG::alignOffset(16, bo); bo = ao + sizeof(OSG::Vec3u);

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        bo = ao + sizeof(OSG::Real32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        bo = ao + sizeof(OSG::Real32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        bo = ao + sizeof(OSG::UInt32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset(16, bo);
        bo = ao + sizeof(OSG::Vec3f);
    }
    ao = OSG::alignOffset(16, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset(16, bo);
        bo = ao + sizeof(OSG::Vec3f);
    }
    ao = OSG::alignOffset(16, bo); bo = ao;

    return ao;
}

std::vector<OSG::UInt8> create_test_data_buffer(const TestData& data)
{
    std::size_t size = calc_test_data_buffer_size(data);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value01;
    bo = ao + sizeof(OSG::Real32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value02;
    bo = ao + sizeof(OSG::Real32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value03;
    bo = ao + sizeof(OSG::Real32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value04;
    bo = ao + sizeof(OSG::Real32);
    
    ao = OSG::alignOffset(16, bo);
    memcpy(&buffer[0] + ao, &data.value05[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);

    ao = OSG::alignOffset(16, bo);
    memcpy(&buffer[0] + ao, &data.value06[0], sizeof(OSG::Vec3f));
    bo = ao + sizeof(OSG::Vec3f);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = data.value07;
    bo = ao + sizeof(OSG::Int32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = data.value08;
    bo = ao + sizeof(OSG::Int32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = data.value09;
    bo = ao + sizeof(OSG::UInt32);

    ao = OSG::alignOffset( 4, bo);
    *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = data.value10;
    bo = ao + sizeof(OSG::UInt32);

    ao = OSG::alignOffset(16, bo);
    memcpy(&buffer[0] + ao, &data.value11[0], sizeof(OSG::Vec3i));
    bo = ao + sizeof(OSG::Vec3i);

    ao = OSG::alignOffset(16, bo);
    memcpy(&buffer[0] + ao, &data.value12[0], sizeof(OSG::Vec3u));
    bo = ao + sizeof(OSG::Vec3u);

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value13[i];
        bo = ao + sizeof(OSG::Real32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = data.value14[i];
        bo = ao + sizeof(OSG::Real32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset( 4, bo);
        *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = data.value15[i];
        bo = ao + sizeof(OSG::UInt32);
    }
    ao = OSG::alignOffset( 4, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset(16, bo);
        memcpy(&buffer[0] + ao, &data.value16[i][0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec3f);
    }
    ao = OSG::alignOffset(16, bo); bo = ao;

    for (OSG::UInt32 i = 0; i < TestData::num_array_elements; ++i)
    {
        ao = OSG::alignOffset(16, bo);
        memcpy(&buffer[0] + ao, &data.value17[i][0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec3f);
    }
    ao = OSG::alignOffset(16, bo); bo = ao;

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_test_data(const TestData& data)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_test_data_buffer(data);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_test_data(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const TestData& data)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_test_data_buffer(data);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// The light grid is basically an image represented by a TexureImageChunk and TextureObjChunk
//
OSG::ImageTransitPtr create_image(OSG::UInt32 width, 
    OSG::UInt32 height, 
    OSG::UInt32 depth, 
    bool allocate_memory)
{
    OSG::ImageRefPtr image = OSG::Image::create();
    image->set(
        GL_RG,                              // pixel format
        width,                              // width in pixel
        height,                             // height in pixel
        depth,                              // depth in pixel
        1,                                  // mipmap count
        1,                                  // frame count
        0.0,                                // frame delay
        NULL,                               // data
        OSG::Image::OSG_UINT32_IMAGEDATA,   // type
        allocate_memory,                    // allocate memory
        1                                   // side count
    );
    return OSG::ImageTransitPtr(image);
}

void update_image(
    OSG::Image* image,
    OSG::UInt32 width, 
    OSG::UInt32 height, 
    OSG::UInt32 depth, 
    bool allocate_memory)
{
    image->set(
        GL_RG,                              // pixel format
        width,                              // width in pixel
        height,                             // height in pixel
        depth,                              // depth in pixel
        1,                                  // mipmap count
        1,                                  // frame count
        0.0,                                // frame delay
        NULL,                               // data
        OSG::Image::OSG_UINT32_IMAGEDATA,   // type
        allocate_memory,                    // allocate memory
        1                                   // side count
    );
}

void update_image_data(OSG::Image* image, const VecImageDataT& imageData)
{
    OSG::UInt8* data = image->editData();

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < imageData.size(); ++i)
    {
        OSG::UInt32 offset = imageData[i].first;
        OSG::UInt32 index  = imageData[i].second;

        ao = OSG::alignOffset(4, bo);
        *(reinterpret_cast<OSG::UInt32*>(data + ao)) = offset;
        bo = ao + sizeof(OSG::UInt32);

        ao = OSG::alignOffset(4, bo);
        *(reinterpret_cast<OSG::UInt32*>(data + ao)) = index;
        bo = ao + sizeof(OSG::UInt32);
    }
}

void write_image_data(
    OSG::UInt32 i, 
    OSG::UInt32 j, 
    OSG::UInt32 k, 
    const OSG::Vec3u& dimensions, 
    const std::pair<OSG::UInt32, OSG::UInt32>& data, 
    VecImageDataT& imageData)
{
    OSG_ASSERT(i < dimensions.x());
    OSG_ASSERT(j < dimensions.y());
    OSG_ASSERT(k < dimensions.z());

    std::size_t idx = k * dimensions.x() * dimensions.y() + j * dimensions.x() + i;

    imageData[idx] = data;
}

OSG::TextureObjChunkTransitPtr create_texture_state(OSG::Image* image)
{
    OSG::TextureObjChunkRefPtr texObjChunk = OSG::TextureObjChunk::create();

    texObjChunk->setTarget(GL_TEXTURE_2D_ARRAY);
    texObjChunk->setScale(false);
    texObjChunk->setInternalFormat(GL_RG32UI);
    texObjChunk->setExternalFormat(GL_RG_INTEGER);
    texObjChunk->setMinFilter(GL_NEAREST);
    texObjChunk->setMagFilter(GL_NEAREST);
    texObjChunk->setImage(image);

    return OSG::TextureObjChunkTransitPtr(texObjChunk);
}

void update_texture_state(OSG::TextureObjChunk* texObjChunk)
{
    texObjChunk->imageContentChanged();
}

OSG::TextureImageChunkTransitPtr create_texture_image_state(
    OSG::TextureObjChunk* texObjChunk,
    const GLenum access)
{
    OSG::TextureImageChunkRefPtr texImageChunk = OSG::TextureImageChunk::create();
    texImageChunk->setTexture(texObjChunk);
    texImageChunk->setAccess(access);
    texImageChunk->setFormat(GL_RG32UI);
    texImageChunk->setLayer(-1);

    return OSG::TextureImageChunkTransitPtr(texImageChunk);
}

void update_light_grid_image(
    const OSG::Vec4u& viewport,
    OSG::Image* image,
    bool allocate_memory)
{
    OSG::Real32 w = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h = static_cast<OSG::Real32>(viewport[3]);

    OSG::UInt32 numHorizontalTiles = OSG::UInt32(OSG::osgCeil(w / tile_size));
    OSG::UInt32 numVerticalTiles   = OSG::UInt32(OSG::osgCeil(h / tile_size));

    update_image(image , numHorizontalTiles, numVerticalTiles, num_cluster_z, allocate_memory);
}

void fill_test_data_light_grid_image(
    const OSG::Vec4u& viewport,
    OSG::Image* image)
{
    OSG::Real32 w = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h = static_cast<OSG::Real32>(viewport[3]);

    OSG::UInt32 sz_i = OSG::UInt32(OSG::osgCeil(w / tile_size));
    OSG::UInt32 sz_j = OSG::UInt32(OSG::osgCeil(h / tile_size));
    OSG::UInt32 sz_k = num_cluster_z;

    OSG::Vec3u dimensions(sz_i, sz_j, sz_k);
    OSG::UInt32 sz = dimensions.x() * dimensions.y() * dimensions.z();

    VecImageDataT imageData(sz, std::make_pair(0,0));

    const OSG::UInt32 uiHeatMapColor0  =  0; // Black
    const OSG::UInt32 uiHeatMapColor1  =  1; // DarkSlateGray
    const OSG::UInt32 uiHeatMapColor2  =  2; // Navy
    const OSG::UInt32 uiHeatMapColor3  =  3; // Blue
    const OSG::UInt32 uiHeatMapColor4  =  4; // RoyalBlue
    const OSG::UInt32 uiHeatMapColor5  =  5; // DodgerBlue
    const OSG::UInt32 uiHeatMapColor6  =  6; // DeepSkyBlue
    const OSG::UInt32 uiHeatMapColor7  =  7; // Turquoise
    const OSG::UInt32 uiHeatMapColor8  =  8; // Aquamarine
    const OSG::UInt32 uiHeatMapColor9  =  9; // Cyan
    const OSG::UInt32 uiHeatMapColor10 = 10; // DarkGreen
    const OSG::UInt32 uiHeatMapColor11 = 11; // Green
    const OSG::UInt32 uiHeatMapColor12 = 12; // SpringGreen
    const OSG::UInt32 uiHeatMapColor13 = 13; // Lime
    const OSG::UInt32 uiHeatMapColor14 = 14; // Chartreuse
    const OSG::UInt32 uiHeatMapColor15 = 15; // GreenYellow
    const OSG::UInt32 uiHeatMapColor16 = 16; // Yellow
    const OSG::UInt32 uiHeatMapColor17 = 17; // Gold
    const OSG::UInt32 uiHeatMapColor18 = 18; // DarkOrange
    const OSG::UInt32 uiHeatMapColor19 = 19; // OrangeRed
    const OSG::UInt32 uiHeatMapColor20 = 20; // Red
    const OSG::UInt32 uiHeatMapColor21 = 21; // FireBrick
    const OSG::UInt32 uiHeatMapColor22 = 22; // DarkRed
    const OSG::UInt32 uiHeatMapColor23 = 23; // BlueViolet
    const OSG::UInt32 uiHeatMapColor24 = 24; // Fuchsia
    const OSG::UInt32 uiHeatMapColor25 = 25; // DeepPink
    const OSG::UInt32 uiHeatMapColor26 = 26; // HotPink
    const OSG::UInt32 uiHeatMapColor27 = 27; // Pink
    const OSG::UInt32 uiHeatMapColor28 = 28; // MistyRose
    const OSG::UInt32 uiHeatMapColor29 = 29; // LavenderBlush
    const OSG::UInt32 uiHeatMapColor30 = 30; // Seashell
    const OSG::UInt32 uiHeatMapColor31 = 31; // White

    for (OSG::UInt32 k = 0; k < dimensions.z(); ++k)
    {
        for (OSG::UInt32 j = 0; j < dimensions.y(); ++j)
        {
            for (OSG::UInt32 i = 0; i < dimensions.x(); ++i)
            {
                OSG::UInt32 light_start_offset, light_count;

                if (i == 0 && j == 0)
                {
                    light_start_offset =   7345698 + uiHeatMapColor13;
                    light_count        = 563472981 + k;
                }
                else if (i == dimensions.x()-1 && j == dimensions.y()-1)
                {
                    light_start_offset =   7345698 + uiHeatMapColor13;
                    light_count        = 563472981 + uiHeatMapColor8;
                }
                else
                {
                    light_start_offset =   7345698 + uiHeatMapColor13;
                    light_count        = 563472981 + k;
                }

                //int rnd = classic_die()*classic_die()*classic_die() + classic_die()*classic_die() + classic_die();

                write_image_data(i, j, k, dimensions, std::make_pair(light_start_offset, light_count), imageData);
            }
        }
    }

    update_image_data(image, imageData);
}

//
// simple frustum with only left, right, top and bottom planes. Front and back
// planes are calculated differently.
//
struct Frustum
{
    OSG::Plane planes[4];

    static bool visualize;
};

bool Frustum::visualize = false;

typedef std::vector<Frustum> VecFrustumsT;

VecFrustumsT frustums_cpu(1);

OSG::Pnt4f NdcFromScreen(
    const OSG::Pnt3f& p_w, 
    const OSG::Vec4u& viewport, 
    OSG::Real32 zNear, 
    OSG::Real32 zFar)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    OSG::Pnt4f p_n(
            2.f * (p_w.x() - x_v) / w - 1.f,
            2.f * (p_w.y() - y_v) / h - 1.f,
            2.f * (p_w.z() - zFar - zNear) / (zFar - zNear),
            1);

    return p_n;
}

OSG::Pnt4f NdcFromScreen(
    const OSG::Pnt3f& p_w,          // with z-coord already given in ndc coords!
    const OSG::Vec4u& viewport)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    OSG::Pnt4f p_n(
            2.f * (p_w.x() - x_v) / w - 1.f,
            2.f * (p_w.y() - y_v) / h - 1.f,
            p_w.z(),
            1);

    return p_n;
}

OSG::Pnt4f ClipFromNdc(const OSG::Pnt4f& p_n, const OSG::Matrix& matProjection)
{
    // Mathematically: m(row x col)
    // ----------------------------
    // columns: c0  c1  c2  c3
    //        (m00 m01 m02 m03)     // row 0        ( 1  2  3  4 )
    //    M = (m10 m11 m12 m13)     // row 1    M = ( 5  6  7  8 )
    //        (m20 m21 m22 m23)     // row 2        ( 9 10 11 12 )
    //        (m30 m31 m32 m33)     // row 3        (13 14 15 16 )
    //
    //           col 0    col 1    col 2    col 3
    //OSG::Real32 m00 = 1, m01 = 2, m02 = 3, m03 = 4,     // row 0
    //            m10 = 5, m11 = 6, m12 = 7, m13 = 8,     // row 1
    //            m20 = 9, m21 =10, m22 =11, m23 =12,     // row 2
    //            m30 =13, m31 =14, m32 =15, m33 =16;     // row 3
    //
    // OpenSG stores internally the transposed of the matrix as 4 row vectors
    //
    //           ( _matrix[0] )   ( _matrix[0][0] _matrix[0][1] _matrix[0][2] _matrix[0][3] )
    //  Matrix = ( _matrix[1] ) = ( _matrix[1][0] _matrix[1][1] _matrix[1][2] _matrix[1][3] )
    //           ( _matrix[2] )   ( _matrix[2][0] _matrix[2][1] _matrix[2][2] _matrix[2][3] )
    //           ( _matrix[3] )   ( _matrix[3][0] _matrix[3][1] _matrix[3][2] _matrix[3][3] )
    //
    //           ( _matrix[0][0]=m00  _matrix[0][1]=m10  _matrix[0][2]=m20  _matrix[0][3]=m30 )
    //         = ( _matrix[1][0]=m01  _matrix[1][1]=m11  _matrix[1][2]=m21  _matrix[1][3]=m31 )
    //           ( _matrix[2][0]=m02  _matrix[2][1]=m12  _matrix[2][2]=m22  _matrix[2][3]=m32 )
    //           ( _matrix[3][0]=m03  _matrix[3][1]=m13  _matrix[3][2]=m23  _matrix[3][3]=m33 )
    //
    //           ( m00 m10 m20 m30 )    T
    //         = ( m01 m11 m21 m31 ) = M
    //           ( m02 m12 m22 m32 )
    //           ( m03 m13 m23 m33 )
    //
    // That is, the vectors _matrix[i] represent the column vectors of the original matrix M!

    //
    // w_c = M34/(z_n - M33/M43)
    //
    OSG::Real32 w_c = matProjection[4][3] / (p_n.z() - matProjection[3][3]/matProjection[3][4]);
    OSG::Pnt4f p_c = w_c * p_n;

    return p_c;
}

OSG::Pnt3f EyeFromClip(const OSG::Pnt4f& p_c, const OSG::Matrix& matInvProjection)
{
    OSG::Pnt4f p_e;
    matInvProjection.mult(p_c, p_e);
    p_e /= p_e.w();
    return OSG::Pnt3f(p_e.x(), p_e.y(), p_e.z());
}

OSG::Pnt3f EyeFromNdc(const OSG::Pnt4f& p_n, const OSG::Matrix& matInvProjection)
{
    OSG::Pnt4f p_e;
    matInvProjection.mult(p_n, p_e);
    p_e /= p_e.w();
    return OSG::Pnt3f(p_e.x(), p_e.y(), p_e.z());
}

bool isOrthographicCamera(OSG::Camera* cam, OSG::UInt32 width, OSG::UInt32 height)
{
    OSG::OrthographicCamera* orthoCam = dynamic_cast<OSG::OrthographicCamera*>(cam);
    if (orthoCam)
        return true;

    OSG::MatrixCamera* matrixCam = dynamic_cast<OSG::MatrixCamera*>(cam);
    if (matrixCam)
    {
        OSG::Matrix matProjection;
        matrixCam->getProjection(matProjection, width, height);

        float m32 = matProjection[2][3];
        float m33 = matProjection[3][3];

        if (matProjection[2][3] == 0.f && matProjection[3][3] == 1.f)
            return true;
    }

    return false;
}

void calc_ortho_frustums_cpu(
    const OSG::Vec4u& viewport,
    const OSG::Matrix& matInvProjection,
    VecFrustumsT& frustums)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    OSG::UInt32 numHorizontalTiles = OSG::UInt32(OSG::osgCeil(w / tile_size));
    OSG::UInt32 numVerticalTiles   = OSG::UInt32(OSG::osgCeil(h / tile_size));

    frustums.resize(numHorizontalTiles * numVerticalTiles);

    OSG::Pnt3f pnts_w[8];
    OSG::Pnt4f pnts_n[8];
    OSG::Pnt3f pnts_e[8];

    for (OSG::UInt32 j = 0; j < numVerticalTiles; ++j)
    {
        OSG::Real32 y0 =             y_v +  j    * tile_size;
        OSG::Real32 y1 = OSG::osgMin(y_v + (j+1) * tile_size, y_v + h);

        for (OSG::UInt32 i = 0; i < numHorizontalTiles; ++i)
        {
            OSG::Real32 x0 =             x_v +  i    * tile_size;
            OSG::Real32 x1 = OSG::osgMin(x_v + (i+1) * tile_size, x_v + w);

            pnts_w[0] = OSG::Pnt3f(x0, y0, 1.f);
            pnts_w[1] = OSG::Pnt3f(x1, y0, 1.f);
            pnts_w[2] = OSG::Pnt3f(x0, y1, 1.f);
            pnts_w[3] = OSG::Pnt3f(x1, y1, 1.f);

            pnts_w[4] = OSG::Pnt3f(x0, y0, -1.f);
            pnts_w[5] = OSG::Pnt3f(x1, y0, -1.f);
            pnts_w[6] = OSG::Pnt3f(x0, y1, -1.f);
            pnts_w[7] = OSG::Pnt3f(x1, y1, -1.f);

            for (OSG::UInt32 k = 0; k < 8; ++k)
            {
                pnts_n[k] = NdcFromScreen(pnts_w[k], viewport);
                pnts_e[k] = EyeFromNdc   (pnts_n[k], matInvProjection);
            }

            OSG::UInt32 idx = j * numHorizontalTiles + i;

            frustums[idx].planes[0] = OSG::Plane(pnts_e[6], pnts_e[0], pnts_e[2]);   //   left plane
            frustums[idx].planes[1] = OSG::Plane(pnts_e[7], pnts_e[3], pnts_e[1]);   //  right plane
            frustums[idx].planes[2] = OSG::Plane(pnts_e[6], pnts_e[2], pnts_e[3]);   //    top plane
            frustums[idx].planes[3] = OSG::Plane(pnts_e[4], pnts_e[1], pnts_e[0]);   // bottom plane
        }
    }
}

void calc_persp_frustums_cpu(
    const OSG::Vec4u& viewport,
    const OSG::Matrix& matInvProjection,
    VecFrustumsT& frustums)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    OSG::UInt32 numHorizontalTiles = OSG::UInt32(OSG::osgCeil(w / tile_size));
    OSG::UInt32 numVerticalTiles   = OSG::UInt32(OSG::osgCeil(h / tile_size));

    frustums.resize(numHorizontalTiles * numVerticalTiles);

    OSG::Pnt3f pEye = (0.f, 0.f, 0.f);    // eye position in view space

    OSG::Pnt3f pnts_w[4];
    OSG::Pnt4f pnts_n[4];
    OSG::Pnt3f pnts_e[4];

    for (OSG::UInt32 j = 0; j < numVerticalTiles; ++j)
    {
        OSG::Real32 y0 =             y_v +  j    * tile_size;
        OSG::Real32 y1 = OSG::osgMin(y_v + (j+1) * tile_size, y_v + h);

        for (OSG::UInt32 i = 0; i < numHorizontalTiles; ++i)
        {
            OSG::Real32 x0 =             x_v +  i    * tile_size;
            OSG::Real32 x1 = OSG::osgMin(x_v + (i+1) * tile_size, x_v + w);

            pnts_w[0] = OSG::Pnt3f(x0, y0, -1.f);
            pnts_w[1] = OSG::Pnt3f(x1, y0, -1.f);
            pnts_w[2] = OSG::Pnt3f(x0, y1, -1.f);
            pnts_w[3] = OSG::Pnt3f(x1, y1, -1.f);

            for (OSG::UInt32 k = 0; k < 4; ++k)
            {
                pnts_n[k] = NdcFromScreen(pnts_w[k], viewport);
                pnts_e[k] = EyeFromNdc   (pnts_n[k], matInvProjection);
            }

            OSG::UInt32 idx = j * numHorizontalTiles + i;

            frustums[idx].planes[0] = OSG::Plane(pEye, pnts_e[0], pnts_e[2]);   //   left plane
            frustums[idx].planes[1] = OSG::Plane(pEye, pnts_e[3], pnts_e[1]);   //  right plane
            frustums[idx].planes[2] = OSG::Plane(pEye, pnts_e[2], pnts_e[3]);   //    top plane
            frustums[idx].planes[3] = OSG::Plane(pEye, pnts_e[1], pnts_e[0]);   // bottom plane
        }
    }
}

std::size_t calc_frustum_buffer_size(const VecFrustumsT& vFrustums)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t j = 0; j < 4; ++j)
    {
        ao = OSG::alignOffset(16, bo); bo = ao + sizeof(OSG::Vec3f);
        ao = OSG::alignOffset( 4, bo); bo = ao + sizeof(OSG::Real32);
        ao = OSG::alignOffset(16, bo); bo = ao;
    }

    ao *= vFrustums.size();         bo = ao;    // array
    ao = OSG::alignOffset( 16, bo); bo = ao;    // padding

    return ao;
}

std::vector<OSG::UInt8> create_frustum_buffer(const VecFrustumsT& vFrustums)
{
    std::size_t size = calc_frustum_buffer_size(vFrustums);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vFrustums.size(); ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            ao = OSG::alignOffset(16, bo);
            memcpy(&buffer[0] + ao, &vFrustums[i].planes[j].getNormal(), sizeof(OSG::Vec3f));
            bo = ao + sizeof(OSG::Vec3f);

            ao = OSG::alignOffset( 4, bo);
            *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = vFrustums[i].planes[j].getDistanceFromOrigin();
            bo = ao + sizeof(OSG::Real32);

            ao = OSG::alignOffset(16, bo); bo = ao;
        }

        ao = OSG::alignOffset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_frustum_state(const VecFrustumsT& vFrustums)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_frustum_buffer(vFrustums);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_frustum_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const VecFrustumsT& vFrustums)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_frustum_buffer(vFrustums);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// Index lists
//
std::size_t calc_light_index_buffer_size(const VecLightIndexT& vIndexList)
{
    return sizeof(OSG::UInt32) * vIndexList.size();
}

std::vector<OSG::UInt8> create_light_index_buffer(const VecLightIndexT& vIndexList)
{
    std::size_t size = calc_light_index_buffer_size(vIndexList);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vIndexList.size(); ++i)
    {
        ao = OSG::alignOffset(4, bo);
        *(reinterpret_cast<OSG::UInt32*>(&buffer[0] + ao)) = vIndexList[i];
        bo = ao + sizeof(OSG::UInt32);
    }

    ao = OSG::alignOffset( 4, bo); bo = ao;    // padding

    return buffer;
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_index_state(const VecLightIndexT& vIndexList)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer = create_light_index_buffer(vIndexList);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_index_state(std::size_t sz)
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    std::vector<OSG::UInt8> buffer(sizeof(OSG::UInt32) * sz, 0);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void update_index_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, const VecLightIndexT& vIndexList)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer = create_light_index_buffer(vIndexList);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

void clear_index_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo, std::size_t sz)
{
    if (ssbo) {
        std::vector<OSG::UInt8> buffer(sizeof(OSG::UInt32) * sz, 0);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

//
// Global light index counter state used for synchronization of the work groups of light culling compute shader
//
OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr create_light_index_counter_state()
{
    OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo = OSG::ShaderStorageBufferObjStdLayoutChunk::create();

    //
    // The counter compromises exactly one UInt32 element
    //
    std::vector<OSG::UInt8> buffer(sizeof(OSG::UInt32) * 1, 0);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::ShaderStorageBufferObjStdLayoutChunkTransitPtr(ssbo);
}

void clear_light_index_counter_state(OSG::ShaderStorageBufferObjStdLayoutChunk* ssbo)
{
    if (ssbo) {
        //
        // The counter compromises exactly one UInt32 element
        //
        std::vector<OSG::UInt8> buffer(sizeof(OSG::UInt32) * 1, 0);

        ssbo->editMFBuffer()->setValues(buffer);
    }
}

struct Sphere
{
    OSG::Pnt3f  c;   // Center point.
    OSG::Real32 r;   // Radius.
};

struct Cone
{
    OSG::Pnt3f  T;   // Cone tip.
    OSG::Real32 h;   // Height of the cone.
    OSG::Vec3f  d;   // Direction of the cone.
    OSG::Real32 r;   // bottom radius of the cone.
};

//
// Check to see if a sphere is fully behind (inside the negative halfspace of) a plane.
//
bool SphereInsidePlane(const Sphere& sphere, const OSG::Plane& plane)
{
    OSG::Real32 val = plane.getNormal().dot(sphere.c) - plane.getDistanceFromOrigin();
    return val < -sphere.r;
}

//
// Check to see of a light is partially contained within the frustum.
//
bool SphereInsideFrustum(const Sphere& sphere, const Frustum& frustum, OSG::Real32 zNear, OSG::Real32 zFar)
{
    bool result = true;

    if (sphere.c.z() - sphere.r > zNear || zFar > sphere.c.z() + sphere.r)
    {
        result = false;
    }

    for (int i = 0; i < 4 && result; i++)
    {
        if (SphereInsidePlane(sphere, frustum.planes[i]))
        {
            result = false;
        }
    }

    return result;
}

//
// Check to see if a point is fully behind (inside the negative halfspace of) a plane.
//
bool PointInsidePlane(const OSG::Pnt3f& p, const OSG::Plane& plane)
{
    OSG::Real32 val = plane.getNormal().dot(p) - plane.getDistanceFromOrigin();
    return val < 0;
}

//
// Check to see if a cone if fully behind (inside the negative halfspace of) a plane.
//
bool ConeInsidePlane(const Cone& cone, const OSG::Plane& plane)
{
    // Compute the farthest point on the end of the cone to the positive space of the plane.
    OSG::Vec3f m = plane.getNormal().cross(cone.d).cross(cone.d);
    OSG::Pnt3f Q = cone.T + cone.d * cone.h - m * cone.r;

    // The cone is in the negative halfspace of the plane if both
    // the tip of the cone and the farthest point on the end of the cone to the 
    // positive halfspace of the plane are both inside the negative halfspace 
    // of the plane.
    return PointInsidePlane(cone.T, plane) && PointInsidePlane(Q, plane);
}

bool ConeInsideFrustum(const Cone& cone, const Frustum& frustum, OSG::Real32 zNear, OSG::Real32 zFar)
{
    bool result = true;

    OSG::Plane nearPlane(OSG::Vec3f(0, 0,-1),-zNear);
    OSG::Plane farPlane (OSG::Vec3f(0, 0, 1), zFar );

    if (ConeInsidePlane(cone, nearPlane) || ConeInsidePlane(cone, farPlane))
    {
        result = false;
    }

    for (int i = 0; i < 4 && result; i++)
    {
        if (ConeInsidePlane(cone, frustum.planes[i]))
        {
            result = false;
        }
    }

    return result;
}

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

    static Light create_light(Type e, OSG::Int32 test_dir_light_type = -1);

    void create_light_geometry(OSG::UInt32 material_idx);

    OSG::Pnt3f   position;                  // light position in object space for point and spot lights
    OSG::Vec3f   direction;                 // direction of directional light or spot light in object space
    OSG::Color3f color;                     // the color of the light
    OSG::Real32  intensity;                 // the intensity of the light
    OSG::Real32  range;                     // the range of the light, i.e. the light sphere radius of influence
    OSG::Real32  spotlightAngle;            // the cone angle in case of a spot light
    OSG::Real32  innerSuperEllipsesWidth;   // cinema light parameter
    OSG::Real32  innerSuperEllipsesHeight;  // cinema light parameter
    OSG::Real32  outerSuperEllipsesWidth;   // cinema light parameter
    OSG::Real32  outerSuperEllipsesHeight;  // cinema light parameter
    OSG::Real32  superEllipsesRoundness;    // cinema light parameter
    OSG::Real32  superEllipsesTwist;        // cinema light parameter
    OSG::Int32   type;                      // the type of light: see OSG::MultiLight::LightType
    bool         enabled;                   // on/off state of the light

    OSG::NodeRefPtr         beacon;     // the light beacon that if defined evaluates the position parameter
    OSG::TransformRefPtr    transform;  // the beacons transform core
    SmoothCubicBezierSpline curve;      // the path that the light will follow

    //
    // Eye space position and direction are calculated on the fly for CPU light culling
    // in order to speed up performance.
    // These are not used for the GPU culling process currently.
    //
    mutable OSG::Pnt3f   position_es;       // light position in eye space for point and spot lights
    mutable OSG::Vec3f   direction_es;      // direction of directional light or spot light in eye space

    static bool         cpu_cull_lights;
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
: position(0.f, 0.f, 0.f)
, direction(0.f, 0.f, 1.f)
, color(1.f,1.f,1.f)
, intensity(1.f)
, range(1.f)
, spotlightAngle(20.f)
, innerSuperEllipsesWidth(1.f)
, innerSuperEllipsesHeight(1.f)
, outerSuperEllipsesWidth(1.3f)
, outerSuperEllipsesHeight(1.3f)
, superEllipsesRoundness(1.0f)
, superEllipsesTwist(0.f)
, type(e)
, enabled(true)
, beacon(NULL)
, transform(NULL)
, curve(dice_knots(true))
{}

Light::~Light() 
{
    beacon    = NULL;
    transform = NULL;
}

void transformToEyeSpace(
    OSG::Node* beacon,
    const OSG::Pnt3f& position_bs,
    const OSG::Vec3f& direction_bs,
    OSG::Pnt3f& position_es,
    OSG::Vec3f& direction_es)
{
    if (!mgr || !mgr->getWindow() || mgr->getWindow()->getMFPort()->size() == 0)
        return;

    OSG::Matrix matWsFromBS;

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    OSG::Viewport* pPort = mgr->getWindow()->getPort(0);

    OSG::Int16 width  = pPort->calcPixelWidth();
    OSG::Int16 height = pPort->calcPixelHeight();

    OSG::Matrix mat;                        // matEsFromWs;
    pPort->getCamera()->getViewing(mat, width, height);

    mat.mult(matWsFromBS);                  // matEsFromBs

    mat.multFull( position_bs,  position_es);
    mat.multFull(direction_bs, direction_es);
}

bool PointLightInsideFrustum(const Light& light, const Frustum& frustum, OSG::Real32 n, OSG::Real32 f)
{
    Sphere sphere;
    sphere.c = light.position_es;
    sphere.r = light.range;

    return SphereInsideFrustum(sphere, frustum, n, f);
}

bool SpotLightInsideFrustum(const Light& light, const Frustum& frustum, OSG::Real32 n, OSG::Real32 f)
{
    Cone cone;
    cone.T = light.position_es;
    cone.d = light.direction_es;
    cone.h = light.range;
    cone.r = OSG::osgTan( OSG::osgDegree2Rad(light.spotlightAngle)) * cone.h;

    return ConeInsideFrustum(cone, frustum, n, f);
}


/*
//
// cluster_k and cluster_z functions without near plane offset
//
OSG::UInt32 cluster_k_verbose(
    OSG::Real32 z_e,    // eye space z-position, z_e < 0
    OSG::Real32 n,      // near plane distance from viewer n > 0
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::UInt32 c)      // number of cluster planes
{
    if (z_e >= -n) return 0;
    if (z_e <= -f) return c-1;

    OSG::Real32 s = (c-1) * log2(z_e/-n) / log2(f/n);
    OSG::UInt32 k = OSG::UInt32(OSG::osgFloor(s));
    return k;
}

OSG::Real32 cluster_z_verbose(
    OSG::UInt32 k,      // cluster coordinate, 0 <= k <= c
    OSG::Real32 n,      // near plane distance from viewer n > 0
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::UInt32 c)      // number of cluster planes
{
    if (k > c-1) return -f;

    OSG::Real32 z_e = -n*exp2(static_cast<OSG::Real32>(k)/(c-1)*log2(f/n));
    return z_e;
}
*/
//
// cluster_k and cluster_z functions with near plane offset
//
OSG::UInt32 cluster_k_verbose(
    OSG::Real32 z_e,    // eye space z-position, z_e < 0
    OSG::Real32 n,      // near plane distance from viewer n > 0
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::Real32 D,      // near plane offset
    OSG::UInt32 c)      // number of cluster planes
{
    if (z_e >= -(n+D)) return 0;
    if (z_e <= -f)     return c-1;

    OSG::Real32 s = 1 + ((c-1) / log2(f/(n+D))) * (log2(-z_e) - log2(n+D));
    OSG::UInt32 k = OSG::UInt32(OSG::osgFloor(s));

    return OSG::osgClamp(0U, k, c-1);
}

OSG::Real32 cluster_z_verbose(
    OSG::UInt32 k,      // cluster coordinate, 0 <= k <= c
    OSG::Real32 n,      // near plane distance from viewer n > 0
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::Real32 D,      // near plane offset
    OSG::UInt32 c)      // number of cluster planes
{
    if (k == 0)  return -n;
    if (k > c-1) return -f;

    OSG::Real32 z_e = -(n+D)*exp2(static_cast<OSG::Real32>(k-1) * (log2(f/(n+D))/(c-1)));
    return z_e;
}


OSG::UInt32 cluster_k(
    OSG::Real32 z_e,    // eye space z-position, z_e < 0
    OSG::Real32 nD,     // near plane distance from viewer plus offset, nD = n+D with n > 0, D > 0
    OSG::Real32 lg_nD,  // log2(nD)
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::Real32 a,      // factor (c-1)/log2(f/nD)
    OSG::UInt32 c_1)    // number of cluster planes
{
    if (z_e >= -nD) return 0;
    if (z_e <= -f)  return c_1;

    OSG::Real32 s = 1 + a * (log2(-z_e) - lg_nD);
    OSG::UInt32 k = OSG::UInt32(s);
    return OSG::osgClamp(0U, k, c_1);
}

OSG::Real32 cluster_z(
    OSG::UInt32 k,      // cluster coordinate, 0 <= k <= c
    OSG::Real32 n,      // near plane distance from viewer n > 0
    OSG::Real32 f,      //  far plane distance from viewer f > n > 0
    OSG::Real32 nD,     // near plane distance from viewer plus offset, nD = n+D with n > 0, D > 0
    OSG::Real32 b,      // factor log2(f/(n+D))/(c-1)
    OSG::UInt32 c_1)    // number of cluster planes
{
    if (k == 0)  return -n;
    if (k > c_1) return -f;

    OSG::Real32 z_e = -nD*exp2(static_cast<OSG::Real32>(k-1) * b);
    return z_e;
}


void cluster_test(
    OSG::Real32 zNear,  // near plane distance from viewer zNear > 0
    OSG::Real32 zFar)   //  far plane distance from viewer   zFar > n > 0
{
    OSG::Real32 eps = OSG::Eps;

    OSG::UInt32 c = 32;
    OSG::UInt32 k, k_verbose;
    OSG::Real32 z_e, z_e_verbose;

    OSG::Real32 d = zFar-zNear;
    OSG::Real32 D = 5.f;

    OSG::UInt32 c_1       = c-1;
    OSG::Real32 zNearD    = zNear + D;
    OSG::Real32 lg_zNearD = log2(zNearD);
    OSG::Real32 a         = (c-1)/log2(zFar/zNearD);
    OSG::Real32 b         = log2(zFar/zNearD)/(c-1);

    z_e = -zNear;               k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear-D;             k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear-D+0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear-D-0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar;                k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);

    z_e = -zNear + 10000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 1000.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 100.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 10.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 1.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.1;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.01;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.0001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.00001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.000001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear;               k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.000001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.00001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.0001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.01;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.1;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 1.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 10.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 100.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 1000.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 10000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/48;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/24;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/12;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 6;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 2;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 10000.0;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 1000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 100.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 10.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 1.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.01;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.0001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.00001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.000001;   k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD;              k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.000001;   k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.00001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.0001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.01;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 1.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 10.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 100.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 1000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 10000.0;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/48;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/24;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/12;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 6;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 2;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 1;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 100.;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 10.;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 1.;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.1;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.01;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.001;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.0001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.00001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.000001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar;                k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.000001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.00001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.0001;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.001;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.01;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.1;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 1.0;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 10.0;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 100.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 1000.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 10000.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
   
    k =  0; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  1; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  2; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  3; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  4; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  5; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  6; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  7; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  8; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  9; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 10; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 11; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 12; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 13; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 14; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 15; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 16; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 17; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 18; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 19; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 20; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 21; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 22; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 23; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 24; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 25; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 26; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 27; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 28; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 29; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 30; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 31; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 32; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 33; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 65; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);

    zNear = 0.01f;
    zFar  = 30000.0f;

    zNearD    = zNear + D;
    lg_zNearD = log2(zNearD);
    a         = (c-1)/log2(zFar/zNearD);
    b         = log2(zFar/zNearD)/(c-1);

    z_e = -zNear;   k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);

    z_e = -zNear + 10000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 1000.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 100.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 10.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 1.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.1;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.01;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.0001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.00001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear + 0.000001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear;               k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.000001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.00001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.0001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.01;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 0.1;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 1.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 10.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 100.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 1000.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - 10000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/48;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/24;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/12;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 6;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 2;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNear - d/ 1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 10000.0;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 1000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 100.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 10.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 1.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.01;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.0001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.00001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD + 0.000001;   k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD;              k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.000001;   k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.00001;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.0001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.01;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 0.1;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 1.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 10.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 100.0;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 1000.0;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - 10000.0;    k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/48;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/24;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/12;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 6;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 2;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zNearD - d/ 1;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 100.;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 10.;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 1.;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.1;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.01;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.001;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.0001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.00001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar + 0.000001;     k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar;                k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.000001;      k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.00001;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.0001;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.001;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.01;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 0.1;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 1.0;           k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 10.0;          k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 100.0;         k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 1000.0;        k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);
    z_e = -zFar- 10000.0;       k_verbose = cluster_k_verbose(z_e, zNear, zFar, D, c); k = cluster_k(z_e, zNearD, lg_zNearD, zFar, a, c_1); assert(k == k_verbose);

    k =  0; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  1; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  2; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  3; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  4; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  5; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  6; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  7; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  8; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k =  9; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 10; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 11; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 12; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 13; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 14; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 15; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 16; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 17; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 18; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 19; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 20; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 21; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 22; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 23; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 24; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 25; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 26; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 27; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 28; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 29; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 30; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 31; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 32; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 33; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
    k = 65; z_e_verbose = cluster_z_verbose(k, zNear, zFar, D, c); z_e = cluster_z(k, zNear, zFar, zNearD, b, c_1); assert(OSG::osgAbs(z_e_verbose - z_e) < eps);
}

void calcAffectedLights(
    const VecLightsT&           lights,             // in light list
    const OSG::Matrix&          matEyeFromWorld,    // in transform from world to eye space
    OSG::FrustumVolume          volViewFrustum,     // in the view frustum volume in world space used for pre test
    VecLightIndexT&             vecAffectedLights)  // out the affected light index list
{
    //
    // We test the light against the view frustum to get only affected lights.
    // Since all of out tests happens in eye space we must transform the world space view
    // frustum to eye space first.
    //
    volViewFrustum.transform(matEyeFromWorld);

    Frustum frustum;
    frustum.planes[0] = volViewFrustum.getPlane(OSG::FrustumVolume::PLANE_LEFT);
    frustum.planes[1] = volViewFrustum.getPlane(OSG::FrustumVolume::PLANE_RIGHT);
    frustum.planes[2] = volViewFrustum.getPlane(OSG::FrustumVolume::PLANE_TOP);
    frustum.planes[3] = volViewFrustum.getPlane(OSG::FrustumVolume::PLANE_BOTTOM);

    OSG::Pnt3f nlt = volViewFrustum.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);
    OSG::Pnt3f flt = volViewFrustum.getCorner(OSG::FrustumVolume:: FAR_LEFT_TOP);

    OSG::Real32 n = nlt.z();
    OSG::Real32 f = flt.z();

    for (std::size_t i = 0; i < lights.size(); ++i)
    {
        bool affected = false;

        const Light& light = lights[i];

        if (light.enabled)
        {
            switch (light.type)
            {
                case Light::directional_light:
                {
                    affected = true;
                }
                break;
                case Light::point_light:
                case Light::cinema_light:
                {
                    transformToEyeSpace(light.beacon, light.position, light.direction, light.position_es, light.direction_es);

                    if (PointLightInsideFrustum(light, frustum, n, f))
                    {
                        affected = true;
                    }
                }
                break;
                case Light::spot_light:
                {
                    transformToEyeSpace(light.beacon, light.position, light.direction, light.position_es, light.direction_es);

                    if (SpotLightInsideFrustum(light, frustum, n, f))
                    {
                        affected = true;
                    }
                }
                break;
            }
        }

        if (affected)
            vecAffectedLights.push_back(OSG::UInt32(i));
    }
}

std::size_t frustumAccessor(
    OSG::UInt32 i, 
    OSG::UInt32 j, 
    const OSG::Vec3u& dimensions)
{
    return j * dimensions.x()  + i;
}

void cullLights(
    const VecLightsT&           lights,             // in light list
    const VecLightIndexT&       vecAffectedLights,  // in the lights that are actually contributing to the view frustum shading
    const VecFrustumsT&         frustums,           // in frustums list
    const OSG::Vec3u&           dimensions,         // in the cluster dimentsions
    const OSG::Matrix&          matEyeFromWorld,    // in transform from world to eye space
    OSG::Real32                 zNear,              // in distance of near plane from eye point
    OSG::Real32                 zFar,               // in distance of far  plane from eye point
    OSG::Real32                 D,                  // in distance offset for near plane
    VecImageDataT&              gridData,           // out the raw grid data
    VecLightIndexT&             lightIndexList)     // out the index list
{
    gridData.clear();
    lightIndexList.clear();

    gridData.resize(dimensions.x() * dimensions.y() * dimensions.z());

    OSG::UInt32 c_1    = dimensions.z()-1;
    OSG::Real32 zNearD = zNear + D;
    OSG::Real32 b      = log2(zFar/zNearD)/(c_1);

    //
    // Test
    //
    for (std::size_t l = 0; l < vecAffectedLights.size(); ++l)
    {
        std::size_t light_index = vecAffectedLights[l];

        const Light& light = lights[light_index];

        //globalTestData.value16[light_index] = light.position_es.subZero();
        //globalTestData.value17[light_index] = light.direction_es;
    }

    for (OSG::UInt32 k = 0; k < dimensions.z(); ++k)
    {
        OSG::Real32 n = cluster_z(k,   zNear, zFar, zNearD, b, c_1);
        OSG::Real32 f = cluster_z(k+1, zNear, zFar, zNearD, b, c_1);

        //OSG::Real32 n = cluster_z_verbose(k,   zNear, zFar, D, dimensions.z());
        //OSG::Real32 f = cluster_z_verbose(k+1, zNear, zFar, D, dimensions.z());

        //globalTestData.value13[k] = n;
        //globalTestData.value14[k] = f;

        for (OSG::UInt32 j = 0; j < dimensions.y(); ++j)
        {
            for (OSG::UInt32 i = 0; i < dimensions.x(); ++i)
            {
                std::size_t tile = frustumAccessor(i, j, dimensions);
                const Frustum& frustum = frustums[tile];

                OSG::UInt32 light_count = 0;
                OSG::UInt32 light_start_offset = OSG::UInt32(lightIndexList.size());

                std::size_t num_affected_lights = vecAffectedLights.size();

                for (std::size_t l = 0; l < num_affected_lights; ++l)
                {
                    std::size_t light_index = vecAffectedLights[l];

                    //OSG::UInt32 test_idx = l * dimensions.x() * dimensions.y() * dimensions.z()
                    //                     + k * dimensions.x() * dimensions.y()
                    //                     + j * dimensions.x()
                    //                     + i;

                    //globalTestData.value15[test_idx] = 0;

                    const Light& light = lights[light_index];

                    if (light.enabled)
                    {
                        switch (light.type)
                        {
                            case Light::directional_light:
                            {
                                light_count += 1;
                                lightIndexList.push_back(OSG::UInt32(light_index));

                                //globalTestData.value15[test_idx] = test_idx;
                            }
                            break;
                            case Light::point_light:
                            case Light::cinema_light:
                            {    
                                if (PointLightInsideFrustum(light, frustum, n, f))
                                {
                                    light_count += 1;
                                    lightIndexList.push_back(OSG::UInt32(light_index));

                                    //globalTestData.value15[test_idx] = test_idx;
                                }
                            }
                            break;
                            case Light::spot_light:
                            {    
                                if (SpotLightInsideFrustum(light, frustum, n, f))
                                {
                                    light_count += 1;
                                    lightIndexList.push_back(OSG::UInt32(light_index));

                                    //globalTestData.value15[test_idx] = test_idx;
                                }
                            }
                            break;
                        }
                    }
                }

                write_image_data(i, j, k, dimensions, std::make_pair(light_start_offset, light_count), gridData);
            }
        }
    }
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
        OSG::UInt32 idx = lightChunk->addLight(light.getType());

        lightChunk->setPosition                 (idx, light.position);
        lightChunk->setDirection                (idx, light.direction);
        lightChunk->setColor                    (idx, light.color);
        lightChunk->setIntensity                (idx, light.intensity);
        lightChunk->setRange                    (idx, light.range);
        lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
        lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
        lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
        lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
        lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
        lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
        lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
        lightChunk->setType                     (idx, light.getType());
        lightChunk->setEnabled                  (idx, light.enabled);
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
                lightChunk->setColor                    (idx, light.color);
                lightChunk->setIntensity                (idx, light.intensity);
                lightChunk->setRange                    (idx, light.range);
                lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
                lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
                lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
                lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
                lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
                lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
                lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
                lightChunk->setType                     (idx, light.getType());
                lightChunk->setEnabled                  (idx, light.enabled);
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
                lightChunk->setColor                    (idx, light.color);
                lightChunk->setIntensity                (idx, light.intensity);
                lightChunk->setRange                    (idx, light.range);
                lightChunk->setSpotlightAngle           (idx, light.spotlightAngle);
                lightChunk->setInnerSuperEllipsesWidth  (idx, light.innerSuperEllipsesWidth);
                lightChunk->setInnerSuperEllipsesHeight (idx, light.innerSuperEllipsesHeight);
                lightChunk->setOuterSuperEllipsesWidth  (idx, light.outerSuperEllipsesWidth);
                lightChunk->setOuterSuperEllipsesHeight (idx, light.outerSuperEllipsesHeight);
                lightChunk->setSuperEllipsesRoundness   (idx, light.superEllipsesRoundness);
                lightChunk->setSuperEllipsesTwist       (idx, light.superEllipsesTwist);
                lightChunk->setType                     (idx, light.getType());
                lightChunk->setEnabled                  (idx, light.enabled);
                lightChunk->setBeacon                   (idx, light.beacon);
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
const OSG::UInt32        dispatch_data_binding_point = 1;
const OSG::UInt32      clustering_data_binding_point = 2;

// SSBO block binding points
const OSG::UInt32             material_binding_point = 0;
const OSG::UInt32                light_binding_point = 1;
const OSG::UInt32 affected_light_index_binding_point = 2;
const OSG::UInt32              frustum_binding_point = 3;
const OSG::UInt32          light_index_binding_point = 4;
const OSG::UInt32  light_index_counter_binding_point = 5;

const OSG::UInt32          cpu_frustum_binding_point = 6;
const OSG::UInt32            test_data_binding_point = 7;

// Texture binding points
const OSG::UInt32           light_grid_binding_point = 0;
const OSG::UInt32       cpu_light_grid_binding_point = 1;

//
// shader programs.
//
std::string get_persp_frustum_cp_program();
std::string get_ortho_frustum_cp_program();
std::string get_light_culling_cp_program();
std::string               get_vp_program();
std::string               get_fp_program();

OSG::ShaderProgramRefPtr frag_shader = NULL;

//
// The scene 
//
OSG::NodeRefPtr scene_node = NULL;

//
// Frustum compute node
//
OSG::NodeRefPtr                   compute_frustum_node             = NULL;
OSG::ShaderProgramRefPtr          compute_frustum_shader           = NULL;
OSG::ComputeShaderAlgorithmRefPtr compute_frustum_shader_algorithm = NULL;

//
// Cluster visualisation root node
//
OSG::NodeRefPtr cluster_geometry_root_node = NULL;

//
// Light culling compute node
//
OSG::NodeRefPtr                   compute_light_culling_node             = NULL;
OSG::ShaderProgramRefPtr          compute_light_culling_shader           = NULL;
OSG::ComputeShaderAlgorithmRefPtr compute_light_culling_shader_algorithm = NULL;

//
// A HDR stage core
//
OSG::HDR2StageRefPtr hdr_stage = NULL;
OSG::NodeRefPtr      hdr_node  = NULL;

//
// The material database for all visible geometry: objects, lights, stage box
//
OSG::MultiPropertySSBOChunkRefPtr ssbo_material_database          = NULL;

OSG::UniformBufferObjChunkRefPtr  ubo_frustum_dispatch_data       = NULL;
OSG::UniformBufferObjChunkRefPtr  ubo_light_culling_dispatch_data = NULL;

OSG::UniformBufferObjChunkRefPtr  ubo_clustering_data             = NULL;

//
// The frustum planes calculated by the computation shader
//
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_frustums     = NULL;
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_frustums_cpu = NULL;

//
// Test data for various test
//
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_test_data = NULL;

//
// The global light lists
//
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_affected_light_index_list = NULL;
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_light_index_list          = NULL;

//
// Light culling compute shader global light index counter
//
OSG::ShaderStorageBufferObjStdLayoutChunkRefPtr ssbo_light_index_counter = NULL;

//
// Light grid
//
OSG::ImageRefPtr light_grid_image     = NULL;
OSG::ImageRefPtr light_grid_image_cpu = NULL;

OSG::TextureObjChunkRefPtr   light_grid_texture_object     = NULL;
OSG::TextureObjChunkRefPtr   light_grid_texture_object_cpu = NULL;

OSG::TextureImageChunkRefPtr light_grid_texture_image_cs   = NULL;
OSG::TextureImageChunkRefPtr light_grid_texture_image_fs   = NULL;
OSG::TextureImageChunkRefPtr light_grid_texture_image_cpu  = NULL;

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
std::vector<OSG::NodeRefPtr>         geom_nodes;
std::vector<OSG::TransformRefPtr>    geom_trafos;
std::vector<SmoothCubicBezierSpline> geom_curves;

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
                matSimulation = geom_curves[i].frame(simulation_param);
                geom_trafos[i]->setMatrix(matSimulation);
            }
        }

        if (simulate_lights)
        {
            BOOST_FOREACH(Light& light, lights)
            {
                matSimulation = light.curve.frame(simulation_param, true);
                light.transform->setMatrix(matSimulation);

            }
        }

        time_stamp = OSG::getTimeStamp();
    }
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

OSG::AlgorithmComputeElementTransitPtr createFrustumComputation()
{
    ubo_frustum_dispatch_data = create_dispatch_data(DispatchData());

    OSG::ChunkMaterialRefPtr chunkMaterial = OSG::ChunkMaterial::create();
    chunkMaterial->addChunk(ubo_frustum_dispatch_data, dispatch_data_binding_point);
    chunkMaterial->addChunk(ssbo_frustums,                   frustum_binding_point);

    compute_frustum_shader = OSG::ShaderProgram::create();
    compute_frustum_shader->setShaderType(GL_COMPUTE_SHADER);
    compute_frustum_shader->setProgram(use_ortho_camera ? get_ortho_frustum_cp_program() : get_persp_frustum_cp_program());
    compute_frustum_shader->addUniformBlock      ("DispatchData", dispatch_data_binding_point);
    compute_frustum_shader->addShaderStorageBlock("Frustums",           frustum_binding_point);

    OSG::ComputeShaderChunkRefPtr compShaderChunk = OSG::ComputeShaderChunk::create();
    compShaderChunk->addComputeShader(compute_frustum_shader);
    compShaderChunk->setVariables(compute_frustum_shader->getVariables());

    compute_frustum_shader_algorithm = OSG::ComputeShaderAlgorithm::create();
    compute_frustum_shader_algorithm->setUseMemoryBarrier(true);
    compute_frustum_shader_algorithm->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    compute_frustum_shader_algorithm->setComputeShader(compShaderChunk);

    OSG::Vec3i work_group_count(1,1,1);
    compute_frustum_shader_algorithm->setDispatchConfig(work_group_count);
    compute_frustum_shader_algorithm->setChunkMaterial(chunkMaterial);

    OSG::AlgorithmComputeElementRefPtr algoCompElement = OSG::AlgorithmComputeElement::create();
    algoCompElement->setAlgorithm(compute_frustum_shader_algorithm);

    return OSG::AlgorithmComputeElementTransitPtr(algoCompElement);
}

OSG::AlgorithmComputeElementTransitPtr createLightCullingComputation()
{
    ubo_light_culling_dispatch_data = create_dispatch_data(DispatchData());

    ssbo_light_index_counter = create_light_index_counter_state();

    OSG::ChunkMaterialRefPtr chunkMaterial = OSG::ChunkMaterial::create();
    chunkMaterial->addChunk(light_grid_texture_image_cs,               light_grid_binding_point);
    chunkMaterial->addChunk(multi_light_chunk,                              light_binding_point);
    chunkMaterial->addChunk(ubo_light_culling_dispatch_data,        dispatch_data_binding_point);
    chunkMaterial->addChunk(ubo_clustering_data,                  clustering_data_binding_point);
    //chunkMaterial->addChunk(ssbo_test_data,                             test_data_binding_point);
    chunkMaterial->addChunk(ssbo_frustums,                                frustum_binding_point);
    chunkMaterial->addChunk(ssbo_affected_light_index_list,  affected_light_index_binding_point);
    chunkMaterial->addChunk(ssbo_light_index_list,                    light_index_binding_point);
    chunkMaterial->addChunk(ssbo_light_index_counter,         light_index_counter_binding_point);
    //chunkMaterial->addChunk(ssbo_frustums_cpu,                        cpu_frustum_binding_point);

    compute_light_culling_shader = OSG::ShaderProgram::create();
    compute_light_culling_shader->setShaderType(GL_COMPUTE_SHADER);
    compute_light_culling_shader->setProgram(get_light_culling_cp_program());
    compute_light_culling_shader->addShaderStorageBlock("Lights",                                light_binding_point);
    compute_light_culling_shader->addUniformBlock      ("DispatchData",                  dispatch_data_binding_point);
    compute_light_culling_shader->addUniformBlock      ("ClusteringData",              clustering_data_binding_point);
    //compute_light_culling_shader->addShaderStorageBlock("TestData",                          test_data_binding_point);
    compute_light_culling_shader->addShaderStorageBlock("Frustums",                            frustum_binding_point);
    compute_light_culling_shader->addShaderStorageBlock("AffectedLightIndexList", affected_light_index_binding_point);
    compute_light_culling_shader->addShaderStorageBlock("LightIndexList",                  light_index_binding_point);
    compute_light_culling_shader->addShaderStorageBlock("LightIndexCounter",       light_index_counter_binding_point);
    //compute_light_culling_shader->addShaderStorageBlock("CPUFrustums",                     cpu_frustum_binding_point);

    OSG::ComputeShaderChunkRefPtr compShaderChunk = OSG::ComputeShaderChunk::create();
    compShaderChunk->addComputeShader(compute_light_culling_shader);
    compShaderChunk->setVariables(compute_light_culling_shader->getVariables());

    compute_light_culling_shader_algorithm = OSG::ComputeShaderAlgorithm::create();
    compute_light_culling_shader_algorithm->setUseMemoryBarrier(true);
    compute_light_culling_shader_algorithm->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    compute_light_culling_shader_algorithm->setComputeShader(compShaderChunk);

    OSG::Vec3i work_group_count(1,1,1);
    compute_light_culling_shader_algorithm->setDispatchConfig(work_group_count);
    compute_light_culling_shader_algorithm->setChunkMaterial(chunkMaterial);

    OSG::AlgorithmComputeElementRefPtr algoCompElement = OSG::AlgorithmComputeElement::create();
    algoCompElement->setAlgorithm(compute_light_culling_shader_algorithm);

    return OSG::AlgorithmComputeElementTransitPtr(algoCompElement);
}

void updateDispatchConfigFrustums(
    const OSG::Vec4u& viewport,
    const OSG::Matrix& matInvProjection)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    //
    // width in pixel divided by tile size in pixel, e.g. 1280 / 16 = 80
    // height in pixel divided by tile size in pixel, e.g. 720 / 16 = 45
    //
    OSG::Real32 numHorizontalTiles = OSG::osgCeil(w / tile_size);
    OSG::Real32 numVerticalTiles   = OSG::osgCeil(h / tile_size);

    DispatchData data;
    data.matTransf = matInvProjection;
    data.viewport  = viewport;
    data.numTiles  = OSG::Vec2i( OSG::Int32(numHorizontalTiles), OSG::Int32(numVerticalTiles) );    // e.g. (80, 45)

    VecFrustumsT vFrustums(data.numTiles.x() * data.numTiles.y());                                  // e.g. 80 * 45 = 3600
    update_frustum_state(ssbo_frustums, vFrustums);
    update_dispatch_data(ubo_frustum_dispatch_data, data);

    OSG::UInt32 szX = OSG::UInt32(OSG::osgCeil(numHorizontalTiles / work_group_size.x()));          // e.g. 80 / 16 ~ 5
    OSG::UInt32 szY = OSG::UInt32(OSG::osgCeil(  numVerticalTiles / work_group_size.y()));          // e.g. 45 / 16 ~ 3
    OSG::UInt32 szZ = 1;

    OSG::Vec3i work_group_count = OSG::Vec3i(szX, szY, szZ);                                        // e.g. (5,3,1)
    compute_frustum_shader_algorithm->setDispatchConfig(work_group_count);
}

void updateDispatchConfigCullLights(
    const OSG::Vec4u& viewport,
    const OSG::Matrix& matViewing)
{
    OSG::Real32 x_v = static_cast<OSG::Real32>(viewport[0]);
    OSG::Real32 y_v = static_cast<OSG::Real32>(viewport[1]);
    OSG::Real32 w   = static_cast<OSG::Real32>(viewport[2]);
    OSG::Real32 h   = static_cast<OSG::Real32>(viewport[3]);

    //
    // width in pixel divided by tile size in pixel, e.g. 1280 / 16 = 80
    // height in pixel divided by tile size in pixel, e.g. 720 / 16 = 45
    //
    OSG::Real32 numHorizontalTiles = OSG::osgCeil(w / tile_size);
    OSG::Real32 numVerticalTiles   = OSG::osgCeil(h / tile_size);

    DispatchData data;
    data.matTransf = matViewing;
    data.viewport  = viewport;
    data.numTiles  = OSG::Vec2i( OSG::Int32(numHorizontalTiles), OSG::Int32(numVerticalTiles) );    // e.g. (80, 45)

    update_dispatch_data(ubo_light_culling_dispatch_data, data);

    OSG::Vec3i work_group_count = OSG::Vec3i(numHorizontalTiles, numVerticalTiles, num_cluster_z);             // e.g. (80,45,32)
    compute_light_culling_shader_algorithm->setDispatchConfig(work_group_count);
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
            type = Light::point_light;
            break;
        case 3:
        case 4:
            type = Light::spot_light;
            break;
        case 5:
        case 6:
            type = Light::cinema_light;
            break;
        }

        lights.push_back(Light::create_light(type));
        
        lights[i].create_light_geometry(i+1);

        scene_node->addChild(lights[i].beacon);
    }

    if (Light::add_dir_test_lights)
    {
        lights.push_back(Light::create_light(Light::directional_light, 0));
        lights.push_back(Light::create_light(Light::directional_light, 1));
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
    l.intensity = max_light_power * small_die();
    l.range     = L * light_range_die();

    switch (e)
    {
        case point_light:
        {
        }
        break;

        case directional_light:
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

        case spot_light:
        {
            l.spotlightAngle = spot_die();
        }
        break;

        case cinema_light:
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

    OSG::Real32 R = range;
    
    if (!correct_light_geometry)
        R = 0.5;

    switch (type)
    {
        case point_light:
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

        case directional_light:
        {
        }
        break;

        case spot_light:
        {
            GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point
            geomState->addChunk(shader_var_chunk);                      // block binding point

            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = makeSpotGeo(h, spotlightAngle, 24, 24);
            geometry->setMaterial(geomState);

            //
            // Test code
            //
            //OSG::Vec3f a, b, c; OSG::Matrix t;
            //a = OSG::Vec3f(0.f, 1.f, 0.f); b = OSG::Vec3f(0.f, 1.f, 0.f); c = OSG::Vec3f(0,0,0);
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(0.f, 1.f, 0.f); b = OSG::Vec3f(0.f, -1.f, 0.f); c = OSG::Vec3f(0,0,0);
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(15.f, 61.f, 53.f); b = OSG::Vec3f(15.f, 61.f, 53.f); c = OSG::Vec3f(0,0,0);
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(15.f, 61.f, 53.f); b = OSG::Vec3f(-15.f, -61.f, -53.f); c = OSG::Vec3f(0,0,0);
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(745.f, 23.f, -153.f); b = OSG::Vec3f(-135.f, 561.f, 253.f); c = OSG::Vec3f(0,0,0);
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //b.normalize();
            //c.normalize();
            //
            //a = OSG::Vec3f(745.f, 23.f, -153.f); b = OSG::Vec3f(-135.f, 561.f, 253.f); c = OSG::Vec3f(0,0,0);
            //a.normalize(); b.normalize();
            //t = rotate_a_into_direction_b(a, b);
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(745.f, 23.f, -153.f); b = OSG::Vec3f(-135.f, 561.f, 253.f); c = OSG::Vec3f(0,0,0);
            //a.normalize(); b.normalize();
            //t = rotate_a_into_direction_b(a, b);
            //a.negate();
            //t.mult(a, c);
            //
            //a = OSG::Vec3f(-3.f, 1.f, 7.f); b = OSG::Vec3f(-4.f, -1.f, 5.f); c = OSG::Vec3f(0,0,0);
            //b.normalize();
            //t = rotate_a_into_direction_b(a, b);
            //a = OSG::Vec3f(4.f, -2.f, 0.6f); a.normalize();
            //t.mult(a, c);
            //OSG::Real32 L = c.length();

            OSG::TransformRefPtr coneTrans = OSG::Transform::create();

            OSG::Matrix rotMat = rotate_a_into_direction_b(OSG::Vec3f(0.f, 1.f, 0.f), direction);
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

        case cinema_light:
        {
            GeomState geom; geom.material_index = material_idx;         // material index used for light animiation
            OSG::MultiPropertyUBOChunkRefPtr uboGeomState = create_geometry_material_state(geom);
            geomState->addChunk(uboGeomState, geom_binding_point);      // buffer binding point
            geomState->addChunk(shader_var_chunk);                      // block binding point

            OSG::Real32 h = R;

            OSG::GeometryRefPtr geometry = makeCinemaGeo(
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

            //OSG::TransformRefPtr coneTrans = OSG::Transform::create();
            //OSG::Matrix rotMat = rotate_a_into_direction_b(OSG::Vec3f(0.f, 1.f, 0.f), direction);
            //coneTrans->setMatrix(rotMat);

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

OSG::NodeTransitPtr createPyramidGeometry(
    const OSG::Pnt3f& nlt, const OSG::Pnt3f& nlb,
    const OSG::Pnt3f& nrt, const OSG::Pnt3f& nrb,
    const OSG::Pnt3f& flt, const OSG::Pnt3f& flb,
    const OSG::Pnt3f& frt, const OSG::Pnt3f& frb)
{
    OSG::GeometryRefPtr geometry = makePyramidGeo(nlt, nlb, nrt, nrb, flt, flb, frt, frb);

    OSG::NodeRefPtr geomNode = OSG::makeNodeFor(geometry);

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

    return OSG::NodeTransitPtr(geomNode);
}

OSG::NodeTransitPtr createFrustumGeometry(const OSG::FrustumVolume& vol, const OSG::Matrix& m = OSG::Matrix())
{
    OSG::Pnt3f nlt = vol.getCorner(OSG::FrustumVolume::NEAR_LEFT_TOP);
    OSG::Pnt3f nlb = vol.getCorner(OSG::FrustumVolume::NEAR_LEFT_BOTTOM);
    OSG::Pnt3f nrt = vol.getCorner(OSG::FrustumVolume::NEAR_RIGHT_TOP);
    OSG::Pnt3f nrb = vol.getCorner(OSG::FrustumVolume::NEAR_RIGHT_BOTTOM);
    OSG::Pnt3f flt = vol.getCorner(OSG::FrustumVolume::FAR_LEFT_TOP);    
    OSG::Pnt3f flb = vol.getCorner(OSG::FrustumVolume::FAR_LEFT_BOTTOM);
    OSG::Pnt3f frt = vol.getCorner(OSG::FrustumVolume::FAR_RIGHT_TOP);
    OSG::Pnt3f frb = vol.getCorner(OSG::FrustumVolume::FAR_RIGHT_BOTTOM);

    m.multFull(nlt, nlt);
    m.multFull(nlb, nlb);
    m.multFull(nrt, nrt);
    m.multFull(nrb, nrb);
    m.multFull(flt, flt);
    m.multFull(flb, flb);
    m.multFull(frt, frt);
    m.multFull(frb, frb);

    return createPyramidGeometry(nlt, nlb, nrt, nrb, flt, flb, frt, frb);
}

void visualize_frustum_cpu(
    OSG::Matrix matEyeFromWorld,
    const VecFrustumsT& frustums,
    OSG::Real32 zNear,
    OSG::Real32 zFar)
{
    cluster_geometry_root_node->clearChildren();

    if (Frustum::visualize)
    {
        //
        // Test 1: simple frustum in world space
        //
        //OSG::Pnt3f pz1(0,0, -10);
        //OSG::Pnt3f pz2(0,0, -30);

        //OSG::Pnt3f nlb(10,10,pz1.z()); OSG::Pnt3f nrb(20,10,pz1.z()); OSG::Pnt3f nlt(10,20,pz1.z()); OSG::Pnt3f nrt(20,20,pz1.z()); 
        //OSG::Pnt3f flb( 5, 5,pz2.z()); OSG::Pnt3f frb(25, 5,pz2.z()); OSG::Pnt3f flt( 5,25,pz2.z()); OSG::Pnt3f frt(25,25,pz2.z());

        //cluster_geometry_root_node->addChild(createPyramidGeometry(nlt, nlb, nrt, nrb, flt, flb, frt, frb));

        //
        // Test 2: simple frustum but with world space z calculated from eye space zNear and zFar
        //
        //OSG::Matrix matWorldFromEye1;
        //matEyeFromWorld.inverse(matWorldFromEye1);

        //OSG::Pnt3f pz1(0,0,-0.3);
        //OSG::Pnt3f pz2(0,0,-300.0);

        //matWorldFromEye1.multFull(pz1,pz1);
        //matWorldFromEye1.multFull(pz2,pz2);

        //OSG::Pnt3f nlb(10,10,pz1.z()); OSG::Pnt3f nrb(20,10,pz1.z()); OSG::Pnt3f nlt(10,20,pz1.z()); OSG::Pnt3f nrt(20,20,pz1.z()); 
        //OSG::Pnt3f flb( 5, 5,pz2.z()); OSG::Pnt3f frb(25, 5,pz2.z()); OSG::Pnt3f flt( 5,25,pz2.z()); OSG::Pnt3f frt(25,25,pz2.z());

        //OSG::FrustumVolume vol;
        //vol.setPlanes(nlt, nlb, nrt, nrb, flt, flb, frt, frb);

        //cluster_geometry_root_node->addChild(createFrustumGeometry(vol));

        //
        // Test 3: the view frustum
        //
        //OSG::FrustumVolume vol = mgr->getCamera()->calcFrustumVal(*mgr->getWindow()->getPort(0));
        //cluster_geometry_root_node->addChild(createFrustumGeometry(vol));

        //
        // The actual frustum visualization code
        //
        matEyeFromWorld.invert();   // now matWorldFromEye
        OSG::Matrix& matWorldFromEye = matEyeFromWorld;

        std::size_t sz = frustums.size();
        std::size_t  i = 0;
        BOOST_FOREACH(const Frustum& frustum, frustums)
        {
            OSG::Plane nearPlane(OSG::Vec3f(0, 0, 1), -zNear);
            OSG::Plane farPlane (OSG::Vec3f(0, 0, 1), -zFar);

            OSG::FrustumVolume vol(nearPlane, farPlane, frustum.planes[0], frustum.planes[1], frustum.planes[2], frustum.planes[3]);

            //if (i==0 || i == sz-1)
            cluster_geometry_root_node->addChild(createFrustumGeometry(vol, matWorldFromEye));
            //++i;
        }
    }
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

    geom_curves.push_back(SmoothCubicBezierSpline(dice_knots(true)));

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

        TestData test_data;
        ssbo_test_data = create_test_data(test_data);

        VecFrustumsT vFrustums(1);

        ssbo_frustums                  = create_frustum_state(vFrustums);
        ssbo_frustums_cpu              = create_frustum_state(vFrustums);

        light_grid_image               = create_image(1,1,1, false);
        light_grid_image_cpu           = create_image(1,1,1, true);

        light_grid_texture_object      = create_texture_state(light_grid_image);
        light_grid_texture_object_cpu  = create_texture_state(light_grid_image_cpu);

        light_grid_texture_image_cs    = create_texture_image_state(light_grid_texture_object,     GL_WRITE_ONLY);
        light_grid_texture_image_fs    = create_texture_image_state(light_grid_texture_object,     GL_READ_ONLY);
        light_grid_texture_image_cpu   = create_texture_image_state(light_grid_texture_object_cpu, GL_READ_ONLY);

        ssbo_affected_light_index_list = create_index_state(1);
        ssbo_light_index_list          = create_index_state(light_index_list_size);

        ubo_clustering_data            = create_clustering_data(ClusteringData());

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
        frag_shader->addShaderStorageBlock("Materials",                          material_binding_point);
        frag_shader->addShaderStorageBlock("Lights",                                light_binding_point);
        frag_shader->addShaderStorageBlock("AffectedLightIndexList", affected_light_index_binding_point);
        frag_shader->addShaderStorageBlock("LightIndexList",                  light_index_binding_point);
        frag_shader->addShaderStorageBlock("Frustums",                            frustum_binding_point);
        //frag_shader->addShaderStorageBlock("CPUFrustums",                     cpu_frustum_binding_point);
        //frag_shader->addShaderStorageBlock("TestData",                          test_data_binding_point);

        frag_shader->addUniformBlock      ("ClusteringData",   clustering_data_binding_point);


        //
        // The following is replaced by adding ShaderProgramVariableChunk objects
        // to the chunk material. See below...
        //
        // frag_shader->addShaderStorageBlock("GeomState", geom_binding_point);

        progChunk->addShader( vertShader);
        progChunk->addShader(frag_shader);

        //
        // The block binding is added to each ChunkMaterial in order to provide the state
        // shader uniform block for the geometery shown in the scene
        //
        shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
        shader_var_chunk->addUniformBlock("GeomState", geom_binding_point);    // block binding point

        //
        // The scene does contain all visible rendering. It will be append to the hdr node.
        //
        scene_node = OSG::makeCoredNode<OSG::Group>();

        //
        // Because we animate the lights by simple geometry, the lights initialization must be happens
        // after the creation of the 'shader_var_chunk' and after the creation of the scene node that
        // actually contains the geometry. Additionally, it must happens before we call 'create_light_state', 
        // since here we do need the already defined lights.
        //
        initialize_lights(init_num_lights);

        //
        // create shader storage buffer objects and corresponding materials
        //
        ssbo_material_database = create_material_database_state(materials);
        multi_light_chunk      = create_light_state(lights);

        OSG::PolygonChunkRefPtr polygonChunk = OSG::PolygonChunk::create();
        polygonChunk->setFrontMode(GL_FILL);
        polygonChunk->setBackMode(GL_FILL);
        polygonChunk->setCullFace(GL_BACK);

        OSG::DepthChunkRefPtr depthChunk = OSG::DepthChunk::create();
        depthChunk->setEnable(true);

        OSG::ChunkMaterialRefPtr progState = OSG::ChunkMaterial::create();
        progState->addChunk(ssbo_material_database,                     material_binding_point);
        progState->addChunk(multi_light_chunk,                             light_binding_point);
        progState->addChunk(ssbo_affected_light_index_list, affected_light_index_binding_point);
        progState->addChunk(ssbo_light_index_list,                   light_index_binding_point);
        progState->addChunk(ssbo_frustums,                               frustum_binding_point);
        //progState->addChunk(ssbo_frustums_cpu,                       cpu_frustum_binding_point);
        progState->addChunk(ubo_clustering_data,                 clustering_data_binding_point);
        //progState->addChunk(ssbo_test_data,                            test_data_binding_point);
        progState->addChunk(light_grid_texture_image_fs,              light_grid_binding_point);
        //progState->addChunk(light_grid_texture_image_cpu,         cpu_light_grid_binding_point);
        
        progState->addChunk(progChunk);
        progState->addChunk(polygonChunk);
        progState->addChunk(depthChunk);

        //
        // The scene graph
        //
        compute_frustum_node       = OSG::makeNodeFor(createFrustumComputation());      // OSG::Group::create());
        compute_light_culling_node = OSG::makeNodeFor(createLightCullingComputation()); // OSG::Group::create());
        hdr_node                   = OSG::makeCoredNode<OSG::Group>();

        mgr->setRoot(compute_frustum_node);

        if (use_ortho_camera)
        {
            OSG::OrthographicCameraRefPtr orthoCamera = OSG::OrthographicCamera::create();
            mgr->setCamera(orthoCamera);
        }

        compute_frustum_node      ->addChild(compute_light_culling_node);
        compute_light_culling_node->addChild(hdr_node);
        hdr_node                  ->addChild(scene_node);

        createHDRStage();

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

    //
    // Common data that is used below
    //
    OSG::Real32 x_vp   = mgr->getWindow()->getPort(0)->calcPixelLeft();
    OSG::Real32 y_vp   = mgr->getWindow()->getPort(0)->calcPixelBottom();

    OSG::Real32 width  = mgr->getWindow()->getPort(0)->calcPixelWidth();
    OSG::Real32 height = mgr->getWindow()->getPort(0)->calcPixelHeight();

    OSG::Real32 zNear = mgr->getCamera()->getNear();
    OSG::Real32 zFar  = mgr->getCamera()->getFar ();

    OSG::UInt32 num_cluster_x = OSG::UInt32(OSG::osgCeil(width  / tile_size));
    OSG::UInt32 num_cluster_y = OSG::UInt32(OSG::osgCeil(height / tile_size));

    OSG::Matrix matEyeFromWorld;
    mgr->getCamera()->getViewing(matEyeFromWorld, width, height);

    OSG::FrustumVolume viewVolume;
    mgr->getCamera()->getFrustum(viewVolume, width, height);

    OSG::Vec4u viewport(x_vp, y_vp, width, height);

    //
    // Clear the CPU test data
    //
    globalTestData.clear();

    //
    // We have to update the view matrix for the light culling compute shader
    //
    updateDispatchConfigCullLights(viewport, matEyeFromWorld);

    //
    // We determine an index list of all lights that are actually contributing to the
    // shading of the complete visible view frustum.
    //
    VecLightIndexT vecAffectedLights;

    calcAffectedLights(
        lights,             // in light list
        matEyeFromWorld,    // in transform from world to eye space
        viewVolume,         // in the view frustum volume in world space
        vecAffectedLights); // out the index list

    update_index_state(ssbo_affected_light_index_list, vecAffectedLights);

    //
    // We clear the global light index list. This, however is strictly not
    // necessary and we do it currently for security reasons.
    //
    // ToDo: Must work without clearing of the global light index list
    //
    //clear_index_state(ssbo_light_index_list, light_index_list_size);

    //
    // Clearing of the global light index counter is necessary!
    //
    clear_light_index_counter_state(ssbo_light_index_counter);

    //
    // Classic light culling only for testing. The real culling is performed in a
    // compute shader, but that result can be tested against the result of this classic
    // culling in the fragment shader.
    //
    //if (Light::cpu_cull_lights)
    //{
    //    OSG::Vec4u viewport(x_vp, y_vp, width, height);
    //    fill_test_data_light_grid_image(viewport, light_grid_image_cpu);
    //
    //    update_texture_state(light_grid_texture_object_cpu);
    //
    //    Light::cpu_cull_lights = false;
    //}
    
    if (Light::cpu_cull_lights)
    {
        //
        // These are the results of the light culling procedure below. We will fill these
        // raw data into appropriate SSBO so that they are available in the fragment shader
        // for evaluation.
        //
        VecImageDataT  gridData;        // tuples of offset and cound integers: { o1,c1, o2,c2, o3,c3,...}
        VecLightIndexT lightIndexList;  // pointers into the lights array.

        OSG::Vec3u dimensions(num_cluster_x, num_cluster_y, num_cluster_z);

        cullLights(
            lights,             // in light list
            vecAffectedLights,  // in the lights that are actually contributing to the view frustum shading
            frustums_cpu,       // in frustums list
            dimensions,         // in cluster dimensions
            matEyeFromWorld,    // in transform from world to eye space
            zNear,              // in distance of near plane from eye point
            zFar,               // in distance of far  plane from eye point
            near_plane_offset,  // in distance offset for near plane
            gridData,           // out the raw grid data
            lightIndexList);    // out the index list

        //
        // Fill gridData to image and inform texture object about change
        //
        update_image_data(light_grid_image_cpu, gridData);
        update_texture_state(light_grid_texture_object_cpu);

        //
        // Fill lightIndexList to SSBO:
        //
        // This is only to be used if the light culling compute shader is not used, because the very same
        // shader storage buffer is filled. The update_index_state, however, does resize the buffer which
        // could yield in memory access problems in the compute shader. In the final implementation the
        // it should be possible to switch between usage of compute shaders and a CPU based code path.
        //
        // For testing it is not possible to compare the compute shaders and CPU based generated light
        // index lists, because of the parallel computations that are performed which always generate
        // differing sortings of the list.
        //
        // update_index_state(ssbo_light_index_list, lightIndexList);
    }

    //
    // Update the clustering data used in the light cull and fragment shader
    //
    ClusteringData clusteringData;
    clusteringData.zNear = zNear;                                                   // positive near plane distance from eye zNear > 0
    clusteringData.zFar  = zFar;                                                    // positive  far plane distance from eye zFar > zNear > 0
    //clusteringData.D     = near_plane_offset;                                       // positive near plane offset D >= 0
    clusteringData.nD    = zNear + near_plane_offset;                               // zNear + D : shader optimization
    clusteringData.lg_nD = log2(clusteringData.nD);                                 // log2(nD) : shader optimization
    clusteringData.a     = (num_cluster_z-1)/log2(zFar/clusteringData.nD);          // precalculated factor (c-1)/log2(f/(n+D))
    clusteringData.b     = 1.f/clusteringData.a;                                    // precalculated factor log2(f/(n+D))/(c-1)
    //clusteringData.c     = num_cluster_z;                                           // number of cluster planes
    clusteringData.c_1   = num_cluster_z - 1;                                       // number of cluster planes minus one : shader optimization
    clusteringData.p_v   = OSG::Vec2i(x_vp, y_vp);                                  // viewport corner points
    //clusteringData.n_c   = OSG::Vec3i(num_cluster_x, num_cluster_y, num_cluster_z); // number of clusters

    if (Light::use_light_index_list)
        clusteringData.t_v = 0;                                                     // test dependent content
    else
        clusteringData.t_v = 1;                                                     // test dependent content

    update_clustering_data(ubo_clustering_data, clusteringData);

    //update_test_data(ssbo_test_data, globalTestData);

    OSG::commitChanges();
    
    mgr->redraw();
}

//
// react to size changes
//
void reshape(int w, int h)
{
    mgr->resize(w, h);
    mgr->update();

    OSG::Real32 x_vp   = mgr->getWindow()->getPort(0)->calcPixelLeft();
    OSG::Real32 y_vp   = mgr->getWindow()->getPort(0)->calcPixelBottom();

    OSG::Real32 width  = mgr->getWindow()->getPort(0)->calcPixelWidth();
    OSG::Real32 height = mgr->getWindow()->getPort(0)->calcPixelHeight();

    OSG::Real32 zNear = mgr->getCamera()->getNear();
    OSG::Real32 zFar  = mgr->getCamera()->getFar ();

    OSG_ASSERT(w == width);
    OSG_ASSERT(h == height);

    OSG::Matrix matProjection, matInverseProjection, matProjectionTranslation, matEyeFromWorld;

    mgr->getCamera()->getProjection           (matProjection,            width, height);
    mgr->getCamera()->getProjectionTranslation(matProjectionTranslation, width, height);
    mgr->getCamera()->getViewing              (matEyeFromWorld,          width, height);

    matProjection.mult(matProjectionTranslation);
    matProjection.inverse(matInverseProjection);

    OSG::Vec4u viewport(x_vp, y_vp, width, height);

    //
    // First, CPU clustering
    //
    {
        //
        // resize the cpu light grid image and allocate appropriate memory
        //
        update_light_grid_image(viewport, light_grid_image_cpu, true);

        //
        // Currently we fill pseudo data into the image to test if they are
        // available in the fragment shader on the GPU. 
        //
        //fill_test_data_light_grid_image(viewport, light_grid_image_cpu);

        //
        // The image content has changed and we have to inform the texture object
        // so that the new content is available in the shader.
        //
        // To be removed, I have read that the image size change is tracked by another route
        //
        update_texture_state(light_grid_texture_object_cpu);

        //
        // That is at the heard of things: the actual cpu frustum generation process.
        //
        if (isOrthographicCamera(mgr->getCamera(), width, height))
            calc_ortho_frustums_cpu(viewport, matInverseProjection, frustums_cpu);
        else
            calc_persp_frustums_cpu(viewport, matInverseProjection, frustums_cpu);

        //
        // The following function generates geometry for the current tile frustums (not the clusters).
        //
        visualize_frustum_cpu(matEyeFromWorld, frustums_cpu, zNear, zFar);

        //
        // In order to check the cpu vs. the gpu generated frustums we make them available in the
        // fragment shader. The following function loads the cpu frustums into a SSBO that is 
        // binded to the fragment shader.
        //
        update_frustum_state(ssbo_frustums_cpu, frustums_cpu);
    }

    //
    // Second, GPU clustering
    //
    {
        //
        // The light grid image size must be adapted. But no CPU memory is needed!
        //
        update_light_grid_image(viewport, light_grid_image, false);

        //
        // The tile frustums are calculated on the GPU by a compute shader. This is done
        // on the rendering pass due to the AlgorithmComputeElement in the scene graph.
        //
        // ToDo: Not each render pass should recompute the frustums, but only one after
        //       the window resize.
        //
        // Addidionally, a second compute shader performs the light culling on the GPU.
        // This is also performed in the rendering pass due to a second AlgorithmCompute-
        // Element core in the scene graph.
        //
        // Both computations are goverend by their respective dispatch configurations. The
        // following call does setup these two configurations appropriately.
        //
        // Also the GPU frustum SSBO must be resized and the DispatchData uniform buffer
        // object taking the viewport, the inverse projection and the number of tiles
        // must be updated. These task are also hidden in the next function call.
        //
        updateDispatchConfigFrustums  (viewport, matInverseProjection);
        updateDispatchConfigCullLights(viewport, matEyeFromWorld);
    }

    //
    // Cluster coordinate test
    //
    cluster_test(zNear, zFar);

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

            compute_frustum_node = NULL;
            compute_frustum_shader = NULL;
            compute_frustum_shader_algorithm = NULL;

            compute_light_culling_node = NULL;
            compute_light_culling_shader = NULL;
            compute_light_culling_shader_algorithm = NULL;

            hdr_stage = NULL;
            hdr_node = NULL;

            ubo_frustum_dispatch_data = NULL;
            ubo_light_culling_dispatch_data = NULL;
            ubo_clustering_data = NULL;

            ssbo_material_database = NULL;
            ssbo_frustums = NULL;
            ssbo_frustums_cpu = NULL;
            ssbo_affected_light_index_list = NULL;
            ssbo_light_index_counter = NULL;
            ssbo_light_index_list = NULL;

            ssbo_test_data = NULL;

            light_grid_image = NULL;
            light_grid_image_cpu = NULL;

            light_grid_texture_object = NULL;
            light_grid_texture_object_cpu = NULL;

            light_grid_texture_image_cs = NULL;
            light_grid_texture_image_fs = NULL;
            light_grid_texture_image_cpu = NULL;

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
                if (light.range / intensityFactor >= OSG::Eps)
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

                light.range *= rangeFactor;
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

                if (light.range / rangeFactor >= OSG::Eps)
                {
                    light.range /= rangeFactor;
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

        case 'v':
        {
            Frustum::visualize = !Frustum::visualize;
            std::cout << "Frustum::visualize = " << Frustum::visualize << std::endl;

            OSG::Real32 w = mgr->getWindow()->getPort(0)->calcPixelWidth();
            OSG::Real32 h = mgr->getWindow()->getPort(0)->calcPixelHeight();

            OSG::Real32 zNear = mgr->getCamera()->getNear();
            OSG::Real32 zFar  = mgr->getCamera()->getFar ();

            visualize_frustum_cpu(mgr->getCamera()->getViewingVal(w, h), frustums_cpu, zNear, zFar);
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
    std::cout << "HDR is " << (dynamic_cast<OSG::HDR2Stage*>(hdr_node->getCore()) != NULL ? "on" : "off") << std::endl;
    std::cout << "Frustum::visualize = " << Frustum::visualize << std::endl;
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
    std::cout << "v     : toogle frustum visualization on/off" << std::endl;
    std::cout << "x     : recreate the lights with current spot dir case" << std::endl;
}

// ============================================================================
//
// Part: Cubic Bezier spline curve implementation
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

std::string add_test_colors()
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "const vec4 IndianRed            = vec4(0.804, 0.361, 0.361, 1.0);"
    << endl << "const vec4 LightCoral           = vec4(0.941, 0.502, 0.502, 1.0);"
    << endl << "const vec4 Salmon               = vec4(0.980, 0.502, 0.447, 1.0);"
    << endl << "const vec4 DarkSalmon           = vec4(0.914, 0.588, 0.478, 1.0);"
    << endl << "const vec4 LightSalmon          = vec4(1.000, 0.627, 0.478, 1.0);"
    << endl << "const vec4 Crimson              = vec4(0.863, 0.078, 0.235, 1.0);"
    << endl << "const vec4 Red                  = vec4(1.000, 0.000, 0.000, 1.0);"
    << endl << "const vec4 FireBrick            = vec4(0.698, 0.133, 0.133, 1.0);"
    << endl << "const vec4 DarkRed              = vec4(0.545, 0.000, 0.000, 1.0);"
    << endl << "const vec4 Pink                 = vec4(1.000, 0.753, 0.796, 1.0);"
    << endl << "const vec4 LightPink            = vec4(1.000, 0.714, 0.757, 1.0);"
    << endl << "const vec4 HotPink              = vec4(1.000, 0.412, 0.706, 1.0);"
    << endl << "const vec4 DeepPink             = vec4(1.000, 0.078, 0.576, 1.0);"
    << endl << "const vec4 MediumVioletRed      = vec4(0.780, 0.082, 0.522, 1.0);"
    << endl << "const vec4 PaleVioletRed        = vec4(0.859, 0.439, 0.576, 1.0);"
    << endl << "const vec4 Coral                = vec4(1.000, 0.498, 0.314, 1.0);"
    << endl << "const vec4 Tomato               = vec4(1.000, 0.388, 0.278, 1.0);"
    << endl << "const vec4 OrangeRed            = vec4(1.000, 0.271, 0.000, 1.0);"
    << endl << "const vec4 DarkOrange           = vec4(1.000, 0.549, 0.000, 1.0);"
    << endl << "const vec4 Orange               = vec4(1.000, 0.647, 0.000, 1.0);"
    << endl << "const vec4 Gold                 = vec4(1.000, 0.843, 0.000, 1.0);"
    << endl << "const vec4 Yellow               = vec4(1.000, 1.000, 0.000, 1.0);"
    << endl << "const vec4 LightYellow          = vec4(1.000, 1.000, 0.878, 1.0);"
    << endl << "const vec4 LemonChion           = vec4(1.000, 0.980, 0.804, 1.0);"
    << endl << "const vec4 LightGoldenrodYellow = vec4(0.980, 0.980, 0.824, 1.0);"
    << endl << "const vec4 PapayaWhip           = vec4(1.000, 0.937, 0.835, 1.0);"
    << endl << "const vec4 Moccasin             = vec4(1.000, 0.894, 0.710, 1.0);"
    << endl << "const vec4 PeachPu              = vec4(1.000, 0.855, 0.725, 1.0);"
    << endl << "const vec4 PaleGoldenrod        = vec4(0.933, 0.910, 0.667, 1.0);"
    << endl << "const vec4 Khaki                = vec4(0.941, 0.902, 0.549, 1.0);"
    << endl << "const vec4 DarkKhaki            = vec4(0.741, 0.718, 0.420, 1.0);"
    << endl << "const vec4 Lavender             = vec4(0.902, 0.902, 0.980, 1.0);"
    << endl << "const vec4 Thistle              = vec4(0.847, 0.749, 0.847, 1.0);"
    << endl << "const vec4 Plum                 = vec4(0.867, 0.627, 0.867, 1.0);"
    << endl << "const vec4 Violet               = vec4(0.933, 0.510, 0.933, 1.0);"
    << endl << "const vec4 Orchid               = vec4(0.855, 0.439, 0.839, 1.0);"
    << endl << "const vec4 Fuchsia              = vec4(1.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 Magenta              = vec4(1.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 MediumOrchid         = vec4(0.729, 0.333, 0.827, 1.0);"
    << endl << "const vec4 MediumPurple         = vec4(0.576, 0.439, 0.859, 1.0);"
    << endl << "const vec4 BlueViolet           = vec4(0.541, 0.169, 0.886, 1.0);"
    << endl << "const vec4 DarkViolet           = vec4(0.580, 0.000, 0.827, 1.0);"
    << endl << "const vec4 DarkOrchid           = vec4(0.600, 0.196, 0.800, 1.0);"
    << endl << "const vec4 DarkMagenta          = vec4(0.545, 0.000, 0.545, 1.0);"
    << endl << "const vec4 Purple               = vec4(0.502, 0.000, 0.502, 1.0);"
    << endl << "const vec4 Indigo               = vec4(0.294, 0.000, 0.510, 1.0);"
    << endl << "const vec4 SlateBlue            = vec4(0.416, 0.353, 0.804, 1.0);"
    << endl << "const vec4 DarkSlateBlue        = vec4(0.282, 0.239, 0.545, 1.0);"
    << endl << "const vec4 GreenYellow          = vec4(0.678, 1.000, 0.184, 1.0);"
    << endl << "const vec4 Chartreuse           = vec4(0.498, 1.000, 0.000, 1.0);"
    << endl << "const vec4 LawnGreen            = vec4(0.486, 0.988, 0.000, 1.0);"
    << endl << "const vec4 Lime                 = vec4(0.000, 1.000, 0.000, 1.0);"
    << endl << "const vec4 LimeGreen            = vec4(0.196, 0.804, 0.196, 1.0);"
    << endl << "const vec4 PaleGreen            = vec4(0.596, 0.984, 0.596, 1.0);"
    << endl << "const vec4 LightGreen           = vec4(0.565, 0.933, 0.565, 1.0);"
    << endl << "const vec4 MediumSpringGreen    = vec4(0.000, 0.980, 0.604, 1.0);"
    << endl << "const vec4 SpringGreen          = vec4(0.000, 1.000, 0.498, 1.0);"
    << endl << "const vec4 MediumSeaGreen       = vec4(0.235, 0.702, 0.443, 1.0);"
    << endl << "const vec4 SeaGreen             = vec4(0.180, 0.545, 0.341, 1.0);"
    << endl << "const vec4 ForestGreen          = vec4(0.133, 0.545, 0.133, 1.0);"
    << endl << "const vec4 Green                = vec4(0.000, 0.502, 0.000, 1.0);"
    << endl << "const vec4 DarkGreen            = vec4(0.000, 0.392, 0.000, 1.0);"
    << endl << "const vec4 YellowGreen          = vec4(0.604, 0.804, 0.196, 1.0);"
    << endl << "const vec4 OliveDrab            = vec4(0.420, 0.557, 0.137, 1.0);"
    << endl << "const vec4 Olive                = vec4(0.502, 0.502, 0.000, 1.0);"
    << endl << "const vec4 DarkOliveGreen       = vec4(0.333, 0.420, 0.184, 1.0);"
    << endl << "const vec4 MediumAquamarine     = vec4(0.400, 0.804, 0.667, 1.0);"
    << endl << "const vec4 DarkSeaGreen         = vec4(0.561, 0.737, 0.561, 1.0);"
    << endl << "const vec4 LightSeaGreen        = vec4(0.125, 0.698, 0.667, 1.0);"
    << endl << "const vec4 DarkCyan             = vec4(0.000, 0.545, 0.545, 1.0);"
    << endl << "const vec4 Teal                 = vec4(0.000, 0.502, 0.502, 1.0);"
    << endl << "const vec4 Aqua                 = vec4(0.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 Cyan                 = vec4(0.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 LightCyan            = vec4(0.878, 1.000, 1.000, 1.0);"
    << endl << "const vec4 PaleTurquoise        = vec4(0.686, 0.933, 0.933, 1.0);"
    << endl << "const vec4 Aquamarine           = vec4(0.498, 1.000, 0.831, 1.0);"
    << endl << "const vec4 Turquoise            = vec4(0.251, 0.878, 0.816, 1.0);"
    << endl << "const vec4 MediumTurquoise      = vec4(0.282, 0.820, 0.800, 1.0);"
    << endl << "const vec4 DarkTurquoise        = vec4(0.000, 0.808, 0.820, 1.0);"
    << endl << "const vec4 CadetBlue            = vec4(0.373, 0.620, 0.627, 1.0);"
    << endl << "const vec4 SteelBlue            = vec4(0.275, 0.510, 0.706, 1.0);"
    << endl << "const vec4 LightSteelBlue       = vec4(0.690, 0.769, 0.871, 1.0);"
    << endl << "const vec4 PowderBlue           = vec4(0.690, 0.878, 0.902, 1.0);"
    << endl << "const vec4 LightBlue            = vec4(0.678, 0.847, 0.902, 1.0);"
    << endl << "const vec4 SkyBlue              = vec4(0.529, 0.808, 0.922, 1.0);"
    << endl << "const vec4 LightSkyBlue         = vec4(0.529, 0.808, 0.980, 1.0);"
    << endl << "const vec4 DeepSkyBlue          = vec4(0.000, 0.749, 1.000, 1.0);"
    << endl << "const vec4 DodgerBlue           = vec4(0.118, 0.565, 1.000, 1.0);"
    << endl << "const vec4 CornlowerBlue        = vec4(0.392, 0.584, 0.929, 1.0);"
    << endl << "const vec4 MediumSlateBlue      = vec4(0.482, 0.408, 0.933, 1.0);"
    << endl << "const vec4 RoyalBlue            = vec4(0.255, 0.412, 0.882, 1.0);"
    << endl << "const vec4 Blue                 = vec4(0.000, 0.000, 1.000, 1.0);"
    << endl << "const vec4 MediumBlue           = vec4(0.000, 0.000, 0.804, 1.0);"
    << endl << "const vec4 DarkBlue             = vec4(0.000, 0.000, 0.545, 1.0);"
    << endl << "const vec4 Navy                 = vec4(0.000, 0.000, 0.502, 1.0);"
    << endl << "const vec4 MidnightBlue         = vec4(0.098, 0.098, 0.439, 1.0);"
    << endl << "const vec4 Cornsilk             = vec4(1.000, 0.973, 0.863, 1.0);"
    << endl << "const vec4 BlanchedAlmond       = vec4(1.000, 0.922, 0.804, 1.0);"
    << endl << "const vec4 Bisque               = vec4(1.000, 0.894, 0.769, 1.0);"
    << endl << "const vec4 NavajoWhite          = vec4(1.000, 0.871, 0.678, 1.0);"
    << endl << "const vec4 Wheat                = vec4(0.961, 0.871, 0.702, 1.0);"
    << endl << "const vec4 BurlyWood            = vec4(0.871, 0.722, 0.529, 1.0);"
    << endl << "const vec4 Tan                  = vec4(0.824, 0.706, 0.549, 1.0);"
    << endl << "const vec4 RosyBrown            = vec4(0.737, 0.561, 0.561, 1.0);"
    << endl << "const vec4 SandyBrown           = vec4(0.957, 0.643, 0.376, 1.0);"
    << endl << "const vec4 Goldenrod            = vec4(0.855, 0.647, 0.125, 1.0);"
    << endl << "const vec4 DarkGoldenrod        = vec4(0.722, 0.525, 0.043, 1.0);"
    << endl << "const vec4 Peru                 = vec4(0.804, 0.522, 0.247, 1.0);"
    << endl << "const vec4 Chocolate            = vec4(0.824, 0.412, 0.118, 1.0);"
    << endl << "const vec4 SaddleBrown          = vec4(0.545, 0.271, 0.075, 1.0);"
    << endl << "const vec4 Sienna               = vec4(0.627, 0.322, 0.176, 1.0);"
    << endl << "const vec4 Brown                = vec4(0.647, 0.165, 0.165, 1.0);"
    << endl << "const vec4 Maroon               = vec4(0.502, 0.000, 0.000, 1.0);"
    << endl << "const vec4 White                = vec4(1.000, 1.000, 1.000, 1.0);"
    << endl << "const vec4 Snow                 = vec4(1.000, 0.980, 0.980, 1.0);"
    << endl << "const vec4 Honeydew             = vec4(0.941, 1.000, 0.941, 1.0);"
    << endl << "const vec4 MintCream            = vec4(0.961, 1.000, 0.980, 1.0);"
    << endl << "const vec4 Azure                = vec4(0.941, 1.000, 1.000, 1.0);"
    << endl << "const vec4 AliceBlue            = vec4(0.941, 0.973, 1.000, 1.0);"
    << endl << "const vec4 GhostWhite           = vec4(0.973, 0.973, 1.000, 1.0);"
    << endl << "const vec4 WhiteSmoke           = vec4(0.961, 0.961, 0.961, 1.0);"
    << endl << "const vec4 Seashell             = vec4(1.000, 0.961, 0.933, 1.0);"
    << endl << "const vec4 Beige                = vec4(0.961, 0.961, 0.863, 1.0);"
    << endl << "const vec4 OldLace              = vec4(0.992, 0.961, 0.902, 1.0);"
    << endl << "const vec4 FloralWhite          = vec4(1.000, 0.980, 0.941, 1.0);"
    << endl << "const vec4 Ivory                = vec4(1.000, 1.000, 0.941, 1.0);"
    << endl << "const vec4 AntiqueWhite         = vec4(0.980, 0.922, 0.843, 1.0);"
    << endl << "const vec4 Linen                = vec4(0.980, 0.941, 0.902, 1.0);"
    << endl << "const vec4 LavenderBlush        = vec4(1.000, 0.941, 0.961, 1.0);"
    << endl << "const vec4 MistyRose            = vec4(1.000, 0.894, 0.882, 1.0);"
    << endl << "const vec4 Gainsboro            = vec4(0.863, 0.863, 0.863, 1.0);"
    << endl << "const vec4 LightGrey            = vec4(0.827, 0.827, 0.827, 1.0);"
    << endl << "const vec4 Silver               = vec4(0.753, 0.753, 0.753, 1.0);"
    << endl << "const vec4 DarkGray             = vec4(0.663, 0.663, 0.663, 1.0);"
    << endl << "const vec4 Gray                 = vec4(0.502, 0.502, 0.502, 1.0);"
    << endl << "const vec4 DimGray              = vec4(0.412, 0.412, 0.412, 1.0);"
    << endl << "const vec4 LightSlateGray       = vec4(0.467, 0.533, 0.600, 1.0);"
    << endl << "const vec4 SlateGray            = vec4(0.439, 0.502, 0.565, 1.0);"
    << endl << "const vec4 DarkSlateGray        = vec4(0.184, 0.310, 0.310, 1.0);"
    << endl << "const vec4 Black                = vec4(0.000, 0.000, 0.000, 1.0);"

    << endl << "const vec4 HeatMapColor0        = Black;"
    << endl << "const vec4 HeatMapColor1        = DarkSlateGray;"
    << endl << "const vec4 HeatMapColor2        = Navy;"
    << endl << "const vec4 HeatMapColor3        = Blue;"
    << endl << "const vec4 HeatMapColor4        = RoyalBlue;"
    << endl << "const vec4 HeatMapColor5        = DodgerBlue;"
    << endl << "const vec4 HeatMapColor6        = DeepSkyBlue;"
    << endl << "const vec4 HeatMapColor7        = Turquoise;"
    << endl << "const vec4 HeatMapColor8        = Aquamarine;"
    << endl << "const vec4 HeatMapColor9        = Cyan;"
    << endl << "const vec4 HeatMapColor10       = DarkGreen;"
    << endl << "const vec4 HeatMapColor11       = Green;"
    << endl << "const vec4 HeatMapColor12       = SpringGreen;"
    << endl << "const vec4 HeatMapColor13       = Lime;"
    << endl << "const vec4 HeatMapColor14       = Chartreuse;"
    << endl << "const vec4 HeatMapColor15       = GreenYellow;"
    << endl << "const vec4 HeatMapColor16       = Yellow;"
    << endl << "const vec4 HeatMapColor17       = Gold;"
    << endl << "const vec4 HeatMapColor18       = DarkOrange;"
    << endl << "const vec4 HeatMapColor19       = OrangeRed;"
    << endl << "const vec4 HeatMapColor20       = Red;"
    << endl << "const vec4 HeatMapColor21       = FireBrick;"
    << endl << "const vec4 HeatMapColor22       = DarkRed;"
    << endl << "const vec4 HeatMapColor23       = BlueViolet;"
    << endl << "const vec4 HeatMapColor24       = Fuchsia;"
    << endl << "const vec4 HeatMapColor25       = DeepPink;"
    << endl << "const vec4 HeatMapColor26       = HotPink;"
    << endl << "const vec4 HeatMapColor27       = Pink;"
    << endl << "const vec4 HeatMapColor28       = MistyRose;"
    << endl << "const vec4 HeatMapColor29       = LavenderBlush;"
    << endl << "const vec4 HeatMapColor30       = Seashell;"
    << endl << "const vec4 HeatMapColor31       = White;"

    << endl << "const uint uiHeatMapColor0  =  0; // Black"
    << endl << "const uint uiHeatMapColor1  =  1; // DarkSlateGray"
    << endl << "const uint uiHeatMapColor2  =  2; // Navy"
    << endl << "const uint uiHeatMapColor3  =  3; // Blue"
    << endl << "const uint uiHeatMapColor4  =  4; // RoyalBlue"
    << endl << "const uint uiHeatMapColor5  =  5; // DodgerBlue"
    << endl << "const uint uiHeatMapColor6  =  6; // DeepSkyBlue"
    << endl << "const uint uiHeatMapColor7  =  7; // Turquoise"
    << endl << "const uint uiHeatMapColor8  =  8; // Aquamarine"
    << endl << "const uint uiHeatMapColor9  =  9; // Cyan"
    << endl << "const uint uiHeatMapColor10 = 10; // DarkGreen"
    << endl << "const uint uiHeatMapColor11 = 11; // Green"
    << endl << "const uint uiHeatMapColor12 = 12; // SpringGreen"
    << endl << "const uint uiHeatMapColor13 = 13; // Lime"
    << endl << "const uint uiHeatMapColor14 = 14; // Chartreuse"
    << endl << "const uint uiHeatMapColor15 = 15; // GreenYellow"
    << endl << "const uint uiHeatMapColor16 = 16; // Yellow"
    << endl << "const uint uiHeatMapColor17 = 17; // Gold"
    << endl << "const uint uiHeatMapColor18 = 18; // DarkOrange"
    << endl << "const uint uiHeatMapColor19 = 19; // OrangeRed"
    << endl << "const uint uiHeatMapColor20 = 20; // Red"
    << endl << "const uint uiHeatMapColor21 = 21; // FireBrick"
    << endl << "const uint uiHeatMapColor22 = 22; // DarkRed"
    << endl << "const uint uiHeatMapColor23 = 23; // BlueViolet"
    << endl << "const uint uiHeatMapColor24 = 24; // Fuchsia"
    << endl << "const uint uiHeatMapColor25 = 25; // DeepPink"
    << endl << "const uint uiHeatMapColor26 = 26; // HotPink"
    << endl << "const uint uiHeatMapColor27 = 27; // Pink"
    << endl << "const uint uiHeatMapColor28 = 28; // MistyRose"
    << endl << "const uint uiHeatMapColor29 = 29; // LavenderBlush"
    << endl << "const uint uiHeatMapColor30 = 30; // Seashell"
    << endl << "const uint uiHeatMapColor31 = 31; // White"

    << endl;

    return ost.str();
}

//
// compute shader programs.
//
std::string get_persp_frustum_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "layout (std140) uniform DispatchData"
    << endl << "{"
    << endl << "    mat4  matTransf;    // inverse projection matrix"
    << endl << "    uvec4 viewport;"
    << endl << "    ivec2 numTiles;"
    << endl << "} dispatchData;"
    << endl << ""
    << endl << "struct Plane"
    << endl << "{"
    << endl << "    vec3  N;"
    << endl << "    float d;"
    << endl << "};"
    << endl << ""
    << endl << "struct Frustum"
    << endl << "{"
    << endl << "    Plane planes[4];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Frustums"
    << endl << "{"
    << endl << "    Frustum frustum[];"
    << endl << "} frustums;"
    << endl << ""
    << endl << "const vec3 eyePos = vec3(0, 0, 0);"
    << endl << ""
    << endl << "Plane computePlane(in const vec3 p0, in const vec3 p1, in const vec3 p2)"
    << endl << "{"
    << endl << "    Plane plane;"
    << endl << ""
    << endl << "    vec3 v1 = p1 - p0;"
    << endl << "    vec3 v2 = p2 - p0;"
    << endl << ""
    << endl << "    plane.N = normalize(cross(v1, v2));"
    << endl << "    plane.d = dot(plane.N, p0);"
    << endl << ""
    << endl << "    return plane;"
    << endl << "}"
    << endl << ""
    << endl << "vec4 ndcFromScreen(in const vec3 p_w)"
    << endl << "{"
    << endl << "    return vec4("
    << endl << "                2.0 * (p_w.x - dispatchData.viewport.x) / dispatchData.viewport[2] - 1.0,"
    << endl << "                2.0 * (p_w.y - dispatchData.viewport.y) / dispatchData.viewport[3] - 1.0,"
    << endl << "                p_w.z,  // assumed to be already in ndc-space!"
    << endl << "                1.0);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 eyeFromNdc(in vec4 p_n)"
    << endl << "{"
    << endl << "    vec4 p_e = dispatchData.matTransf * p_n;    // inverse projection matrix"
    << endl << "    p_e /= p_e.w;"
    << endl << "    return p_e.xyz;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    vec3 pnts_w[4];"
    << endl << "    vec4 pnts_n[4];"
    << endl << "    vec3 pnts_e[4];"
    << endl << ""
                    //
                    // gl_GlobalInvocationID = gl_WorkGroupID * gl_WorkGroupSize + gl_LocalInvocationID
                    //
                    //   gl_WorkGroupID - contains the index of the workgroup currently being operated on by a compute shader
                    //                    values range across the parameters passed into glDispatchCompute, i.e. from (0,0,0)
                    //                    to (gl_NumWorkGroups.x-1, gl_NumWorkGroups.y-1, gl_NumWorkGroups.z-1)
                    //
                    //   gl_WorkGroupSize - match those specified in the required local_size_x, local_size_y, and local_size_z
                    //                      layout qualifiers for the current shader
                    //
                    //   gl_LocalInvocationID - values for this variable range across the local work group size, i.e., (0,0,0)
                    //                          to (gl_WorkGroupSize.x-1, gl_WorkGroupSize.y-1, gl_WorkGroupSize.z-1)
                    //
    << endl << "    float x_v = dispatchData.viewport.x;"
    << endl << "    float y_v = dispatchData.viewport.y;"
    << endl << "    float w_v = dispatchData.viewport.z;"
    << endl << "    float h_v = dispatchData.viewport.w;"
    << endl << ""
    << endl << "    float x0 =     x_v +  gl_GlobalInvocationID.x    * tile_size;"
    << endl << "    float x1 = min(x_v + (gl_GlobalInvocationID.x+1) * tile_size, x_v + w_v);"
    << endl << "    float y0 =     y_v +  gl_GlobalInvocationID.y    * tile_size;"
    << endl << "    float y1 = min(y_v + (gl_GlobalInvocationID.y+1) * tile_size, y_v + h_v);"
    << endl << ""
    << endl << "    pnts_w[0] = vec3(x0, y0, -1.0);"
    << endl << "    pnts_w[1] = vec3(x1, y0, -1.0);"
    << endl << "    pnts_w[2] = vec3(x0, y1, -1.0);"
    << endl << "    pnts_w[3] = vec3(x1, y1, -1.0);"
    << endl << ""
    << endl << "    for (int i = 0; i < 4; ++i)"
    << endl << "    {"
    << endl << "        pnts_n[i] = ndcFromScreen(pnts_w[i]);"
    << endl << "        pnts_e[i] = eyeFromNdc   (pnts_n[i]);"
    << endl << "    }"
    << endl << ""
    << endl << "    Frustum frustum;"
    << endl << ""
    << endl << "    frustum.planes[0] = computePlane(eyePos, pnts_e[0], pnts_e[2]);"
    << endl << "    frustum.planes[1] = computePlane(eyePos, pnts_e[3], pnts_e[1]);"
    << endl << "    frustum.planes[2] = computePlane(eyePos, pnts_e[2], pnts_e[3]);"
    << endl << "    frustum.planes[3] = computePlane(eyePos, pnts_e[1], pnts_e[0]);"
    << endl << ""
    << endl << "    if (gl_GlobalInvocationID.x < dispatchData.numTiles.x && gl_GlobalInvocationID.y < dispatchData.numTiles.y)"
    << endl << "    {"
    << endl << "        uint idx = gl_GlobalInvocationID.y * dispatchData.numTiles.x + gl_GlobalInvocationID.x;"
    << endl << "        frustums.frustum[idx] = frustum;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string get_ortho_frustum_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "layout (std140) uniform DispatchData"
    << endl << "{"
    << endl << "    mat4  matTransf;    // inverse projection matrix"
    << endl << "    uvec4 viewport;"
    << endl << "    ivec2 numTiles;"
    << endl << "} dispatchData;"
    << endl << ""
    << endl << "struct Plane"
    << endl << "{"
    << endl << "    vec3  N;"
    << endl << "    float d;"
    << endl << "};"
    << endl << ""
    << endl << "struct Frustum"
    << endl << "{"
    << endl << "    Plane planes[4];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Frustums"
    << endl << "{"
    << endl << "    Frustum frustum[];"
    << endl << "} frustums;"
    << endl << ""
    << endl << "Plane computePlane(in const vec3 p0, in const vec3 p1, in const vec3 p2)"
    << endl << "{"
    << endl << "    Plane plane;"
    << endl << ""
    << endl << "    vec3 v1 = p1 - p0;"
    << endl << "    vec3 v2 = p2 - p0;"
    << endl << ""
    << endl << "    plane.N = normalize(cross(v1, v2));"
    << endl << "    plane.d = dot(plane.N, p0);"
    << endl << ""
    << endl << "    return plane;"
    << endl << "}"
    << endl << ""
    << endl << "vec4 ndcFromScreen(in const vec3 p_w)"
    << endl << "{"
    << endl << "    return vec4("
    << endl << "                2.0 * (p_w.x - dispatchData.viewport.x) / dispatchData.viewport[2] - 1.0,"
    << endl << "                2.0 * (p_w.y - dispatchData.viewport.y) / dispatchData.viewport[3] - 1.0,"
    << endl << "                p_w.z,  // assumed to be already in ndc-space!"
    << endl << "                1.0);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 eyeFromNdc(in vec4 p_n)"
    << endl << "{"
    << endl << "    vec4 p_e = dispatchData.matTransf * p_n;    // inverse projection matrix"
    << endl << "    p_e /= p_e.w;"
    << endl << "    return p_e.xyz;"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    vec3 pnts_w[8];"
    << endl << "    vec4 pnts_n[8];"
    << endl << "    vec3 pnts_e[8];"
    << endl << ""
                    //
                    // gl_GlobalInvocationID = gl_WorkGroupID * gl_WorkGroupSize + gl_LocalInvocationID
                    //
                    //   gl_WorkGroupID - contains the index of the workgroup currently being operated on by a compute shader
                    //                    values range across the parameters passed into glDispatchCompute, i.e. from (0,0,0)
                    //                    to (gl_NumWorkGroups.x-1, gl_NumWorkGroups.y-1, gl_NumWorkGroups.z-1)
                    //
                    //   gl_WorkGroupSize - match those specified in the required local_size_x, local_size_y, and local_size_z
                    //                      layout qualifiers for the current shader
                    //
                    //   gl_LocalInvocationID - values for this variable range across the local work group size, i.e., (0,0,0)
                    //                          to (gl_WorkGroupSize.x-1, gl_WorkGroupSize.y-1, gl_WorkGroupSize.z-1)
                    //
    << endl << "    float x_v = dispatchData.viewport.x;"
    << endl << "    float y_v = dispatchData.viewport.y;"
    << endl << "    float w_v = dispatchData.viewport.z;"
    << endl << "    float h_v = dispatchData.viewport.w;"
    << endl << ""
    << endl << "    float x0 =     x_v +  gl_GlobalInvocationID.x    * tile_size;"
    << endl << "    float x1 = min(x_v + (gl_GlobalInvocationID.x+1) * tile_size, x_v + w_v);"
    << endl << "    float y0 =     y_v +  gl_GlobalInvocationID.y    * tile_size;"
    << endl << "    float y1 = min(y_v + (gl_GlobalInvocationID.y+1) * tile_size, y_v + h_v);"
    << endl << ""
    << endl << "    pnts_w[0] = vec3(x0, y0, 1.0);"
    << endl << "    pnts_w[1] = vec3(x1, y0, 1.0);"
    << endl << "    pnts_w[2] = vec3(x0, y1, 1.0);"
    << endl << "    pnts_w[3] = vec3(x1, y1, 1.0);"
    << endl << ""
    << endl << "    pnts_w[4] = vec3(x0, y0,-1.0);"
    << endl << "    pnts_w[5] = vec3(x1, y0,-1.0);"
    << endl << "    pnts_w[6] = vec3(x0, y1,-1.0);"
    << endl << "    pnts_w[7] = vec3(x1, y1,-1.0);"
    << endl << ""
    << endl << "    for (int i = 0; i < 8; ++i)"
    << endl << "    {"
    << endl << "        pnts_n[i] = ndcFromScreen(pnts_w[i]);"
    << endl << "        pnts_e[i] = eyeFromNdc   (pnts_n[i]);"
    << endl << "    }"
    << endl << ""
    << endl << "    Frustum frustum;"
    << endl << ""
    << endl << "    frustum.planes[0] = computePlane(pnts_e[6], pnts_e[0], pnts_e[2]);"
    << endl << "    frustum.planes[1] = computePlane(pnts_e[7], pnts_e[3], pnts_e[1]);"
    << endl << "    frustum.planes[2] = computePlane(pnts_e[6], pnts_e[2], pnts_e[3]);"
    << endl << "    frustum.planes[3] = computePlane(pnts_e[4], pnts_e[1], pnts_e[0]);"
    << endl << ""
    << endl << "    if (gl_GlobalInvocationID.x < dispatchData.numTiles.x && gl_GlobalInvocationID.y < dispatchData.numTiles.y)"
    << endl << "    {"
    << endl << "        uint idx = gl_GlobalInvocationID.y * dispatchData.numTiles.x + gl_GlobalInvocationID.x;"
    << endl << "        frustums.frustum[idx] = frustum;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string get_light_culling_cp_program()
{
    using namespace std;

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_shader_image_load_store:      enable"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << add_test_colors()
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "const int POINT_LIGHT       = 1;    // defined in OSGMultiLightChunk.h"
    << endl << "const int DIRECTIONAL_LIGHT = 2;"
    << endl << "const int SPOT_LIGHT        = 3;"
    << endl << "const int CINEMA_LIGHT      = 4;"
    << endl << ""
    << endl << "//"
    << endl << "// We write our results into the global light grid with:"
    << endl << "//      imageStore(light_grid, ivec3(i,j,k), uvec4(o,c,0,0))"
    << endl << "// were:"
    << endl << "//          i,j,k  define the cluster index"
    << endl << "//          o      is the offset from the beginning of the global light index list for the cluster"
    << endl << "//          c      is the number if lights that are to be used for the cluster"
    << endl << "//"
    << endl << "layout(binding = 0, rg32ui) uniform uimage2DArray light_grid;"
    << endl << ""
    << endl << "//"
    << endl << "// We need access to the lights shape and position data"
    << endl << "//"
    << endl << "struct Light"
    << endl << "{"
    << endl << "    mat4  eyeToLightSpaceMatrix;"
    << endl << "    vec3  position;                 // in world space"
    << endl << "    vec3  direction;                // in world space"
    << endl << "    vec3  color;"
    << endl << "    float intensity;"
    << endl << "    float range;"
    << endl << "    float cosSpotlightAngle;"
    << endl << "    float spotlightAngle;"
    << endl << "    float innerSuperEllipsesWidth;  // a" 
    << endl << "    float innerSuperEllipsesHeight; // b"
    << endl << "    float outerSuperEllipsesWidth;  // A"
    << endl << "    float outerSuperEllipsesHeight; // B"
    << endl << "    float superEllipsesRoundness;   // r"
    << endl << "    float superEllipsesTwist;       // theta"
    << endl << "    int   type;                     // specific type of light: POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT or CINEMA_LIGHT"
    << endl << "    bool  enabled;                  // on/off state of light"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Lights"
    << endl << "{"
    << endl << "    Light light[];"
    << endl << "} lights;"
    << endl << ""
    << endl << "//"
    << endl << "// Miscellaneous data that are needed for the task at hand"
    << endl << "//"
    << endl << "layout (std140) uniform DispatchData"
    << endl << "{"
    << endl << "    mat4  matTransf;    // world to view matrix"
    << endl << "    uvec4 viewport;"
    << endl << "    ivec2 numTiles;"
    << endl << "} dispatchData;"
    << endl << ""
    << endl << "//"
    << endl << "// The data we need to calc the cluster depth values from the cluster key k"
    << endl << "//"
    << endl << "layout (std140) uniform ClusteringData"
    << endl << "{"
    << endl << "    float zNear;  // positive near plane distance from eye zNear > 0"
    << endl << "    float zFar;   // positive  far plane distance from eye zFar > zNear > 0"
    //<< endl << "    float D;      // positive near plane offset D >= 0                              // for testing"
    << endl << "    float nD;     // zNear + D : shader optimization"
    << endl << "    float lg_nD;  // log2(nD) : shader optimization"
    << endl << "    float a;      // precalculated factor (c-1)/log2(f/(n+D))"
    << endl << "    float b;      // precalculated factor log2(f/(n+D))/(c-1)"
    //<< endl << "    int   c;      // number of cluster planes                                       // for testing"
    << endl << "    int   c_1;    // number of cluster planes minus one : shader optimization"
    << endl << "    ivec2 p_v;    // viewport corner points"
    //<< endl << "    ivec3 n_c;    // number of clusters                                             // for testing"
    << endl << "    int   t_v;    // test dependent content                                           // for testing"
    << endl << "} clusteringData;"
    << endl << ""
    // Debug Test Begin
    //<< endl << "//"
    //<< endl << "// Pure testing data"
    //<< endl << "//"
    //<< endl << "layout (std430) buffer TestData"
    //<< endl << "{"
    //<< endl << "    float value01;"
    //<< endl << "    float value02;"
    //<< endl << "    float value03;"
    //<< endl << "    float value04;"
    //<< endl << "    vec3  value05;"
    //<< endl << "    vec3  value06;"
    //<< endl << "    int   value07;"
    //<< endl << "    int   value08;"
    //<< endl << "    uint  value09;"
    //<< endl << "    uint  value10;"
    //<< endl << "    ivec3 value11;"
    //<< endl << "    uvec3 value12;"
    //<< endl << "    float value13[" << TestData::num_array_elements << "];"
    //<< endl << "    float value14[" << TestData::num_array_elements << "];"
    //<< endl << "    uint  value15[" << TestData::num_array_elements << "];"
    //<< endl << "    vec3  value16[" << TestData::num_array_elements << "];"
    //<< endl << "    vec3  value17[" << TestData::num_array_elements << "];"
    //<< endl << "} testData;"
    //<< endl << ""
    // Debug Test End
    << endl << "//"
    << endl << "// A simple Plane abstraction"
    << endl << "//"
    << endl << "struct Plane"
    << endl << "{"
    << endl << "    vec3  N;"
    << endl << "    float d;"
    << endl << "};"
    << endl << ""
    << endl << "//"
    << endl << "// The 4 planes of the tile frustum"
    << endl << "//"
    << endl << "struct Frustum"
    << endl << "{"
    << endl << "    Plane planes[4];"
    << endl << "};"
    << endl << ""
    << endl << "//"
    << endl << "// A simple Sphere abstraction"
    << endl << "//"
    << endl << "struct Sphere"
    << endl << "{"
    << endl << "    vec3  c;   // Center point."
    << endl << "    float r;   // Radius."
    << endl << "};"
    << endl << ""
    << endl << "//"
    << endl << "// A simple Cone abstraction"
    << endl << "//"
    << endl << "struct Cone"
    << endl << "{"
    << endl << "    vec3  T;   // Cone tip."
    << endl << "    float h;   // Height of the cone."
    << endl << "    vec3  d;   // Direction of the cone."
    << endl << "    float r;   // bottom radius of the cone."
    << endl << "};"
    << endl << ""
    << endl << "//"
    << endl << "// We get the pre calculated list of frustums for each tile."
    << endl << "// The cluster frustum is accessed with the help of the"
    << endl << "// gl_WorkGroupID variable:"
    << endl << "//"
    << endl << "//      idx = j * numHorizontalTiles + i"
    << endl << "//      idx = gl_WorkGroupID.y * dispatchData.numTiles.x  + gl_WorkGroupID.x"
    << endl << "//"
    << endl << "layout (std430) buffer Frustums"
    << endl << "{"
    << endl << "    Frustum frustum[];"
    << endl << "} frustums;"
    << endl << ""
    // Debug Test Begin
    //<< endl << "layout (std430) buffer CPUFrustums"
    //<< endl << "{"
    //<< endl << "    Frustum frustum[];"
    //<< endl << "} cpuFrustums;"
    //<< endl << ""
    // Debug Test End
    << endl << "//"
    << endl << "// The affected light index list that is iterated to get the light"
    << endl << "//"
    << endl << "layout (std430) buffer AffectedLightIndexList"
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} affectedLightIndexList;"
    << endl << ""
    << endl << "//"
    << endl << "// The global light index list that is to be written by this shader"
    << endl << "//"
    << endl << "layout (std430) buffer LightIndexList"
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} lightIndexList;"
    << endl << ""
    << endl << "//"
    << endl << "// The global light index list that is to be written by this shader"
    << endl << "//"
    << endl << "layout (std430) buffer LightIndexCounter"
    << endl << "{"
    << endl << "    uint lightIndexCounter;"
    << endl << "};"
    << endl << ""
    << endl << "//"
    << endl << "// Per work group shared state"
    << endl << "//"
    << endl << "shared Frustum  sharedFrustum;"
    << endl << "shared vec2     sharedFrustumZ;"
    << endl << "shared uint     sharedLightCount;"
    << endl << "shared uint     sharedLightStartOffset;"
    << endl << "shared uint     sharedLightIndexList[1024];"
    // Debug Test Begin
    //<< endl << "shared uint     sharedTestValue;"
    //<< endl << ""
    //<< endl << "const float eps = 1.0E-4;"
    //<< endl << ""
    //<< endl << "bool isEqual(in const vec3 v1, in const vec3 v2)"
    //<< endl << "{"
    //<< endl << "    if (all(lessThan(abs(v1-v2), vec3(eps,eps,eps))))"
    //<< endl << "        return true;"
    //<< endl << "    else"
    //<< endl << "        return false;"
    //<< endl << "}"
    //<< endl << ""
    //<< endl << "bool isEqual(in const float v1, in const float v2)"
    //<< endl << "{"
    //<< endl << "    if (abs(v1-v2) < eps)"
    //<< endl << "        return true;"
    //<< endl << "    else"
    //<< endl << "        return false;"
    //<< endl << "}"
    // Debug Test End
    << endl << ""
    << endl << "//"
    << endl << "// cluster_z and cluster_z_verbose calculates the cluster eye space z from the cluster key k value"
    << endl << "//      z_e = cluster_z(k, ...) with z_e in [-n, -f]"
    << endl << "//"
    << endl << "// Formular:"
    << endl << "//      z_e = -n                                              if k == 0"
    << endl << "//      z_e = -(n+D) * exp2( (k-1)*(log2(f/(n+D))/(c-1)) )    else"
    << endl << "//      z_e = -f                                              if k > c-1"
    << endl << "//"
    // Debug Test Begin
    //<< endl << "float cluster_z_verbose("
    //<< endl << "    in const uint  k,      // cluster coordinate, 0 <= k <= c"
    //<< endl << "    in const float n,      // near plane distance from viewer n > 0"
    //<< endl << "    in const float f,      //  far plane distance from viewer f > n > 0"
    //<< endl << "    in const float D,      // near plane offset"
    //<< endl << "    in const int   c)      // number of cluster planes"
    //<< endl << "{"
    //<< endl << "    if (k == 0)  return -n;"
    //<< endl << "    if (k > c-1) return -f;"
    //<< endl << ""
    //<< endl << "    float z_e = -(n+D) * exp2(float(k-1) * (log2(f/(n+D))/float(c-1)));"
    //<< endl << "    return z_e;"
    //<< endl << "}"
    //<< endl << ""
    // Debug Test End
    << endl << "float cluster_z("
    << endl << "    in const uint  k,      // cluster coordinate, 0 <= k <= c"
    << endl << "    in const float n,      // near plane distance from viewer n > 0"
    << endl << "    in const float f,      //  far plane distance from viewer f > n > 0"
    << endl << "    in const float nD,     // near plane distance from viewer plus offset, nD = n+D with n > 0, D > 0"
    << endl << "    in const float b,      // factor log2(f/(n+D))/(c-1)"
    << endl << "    in const int c_1)      // number of cluster planes"
    << endl << "{"
    << endl << "    if (k == 0)  return -n;"
    << endl << "    if (k > c_1) return -f;"
    << endl << ""
    << endl << "    float z_e = -nD * exp2(float(k-1) * b);"
    << endl << "    return z_e;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Check to see if a sphere is fully behind (inside the negative halfspace of) a plane."
    << endl << "//"
    << endl << "bool sphereInsidePlane("
    << endl << "    in const Sphere sphere,"
    << endl << "    in const Plane plane)"
    << endl << "{"
    << endl << "    float val = dot(plane.N, sphere.c) - plane.d;"
    << endl << "    return val < -sphere.r;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Check to see of a light is partially contained within the frustum."
    << endl << "//"
    << endl << "bool sphereInsideFrustum("
    << endl << "    in const Sphere sphere,"
    << endl << "    in const Frustum frustum,"
    << endl << "    in const float zNear,"
    << endl << "    in const float zFar)"
    << endl << "{"
    << endl << "    bool result = true;"
    << endl << ""
    << endl << "    if (sphere.c.z - sphere.r > zNear || zFar > sphere.c.z + sphere.r)"
    << endl << "    {"
    << endl << "        result = false;"
    << endl << "    }"
    << endl << ""
    << endl << "    for (int i = 0; i < 4 && result; i++)"
    << endl << "    {"
    << endl << "        if (sphereInsidePlane(sphere, frustum.planes[i]))"
    << endl << "        {"
    << endl << "            result = false;"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return result;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Check to see if a point is fully behind (inside the negative halfspace of) a plane."
    << endl << "//"
    << endl << "bool pointInsidePlane("
    << endl << "    in const vec3 p,"
    << endl << "    in const Plane plane)"
    << endl << "{"
    << endl << "    float val = dot(plane.N, p) - plane.d;"
    << endl << "    return val < 0;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Check to see if a cone if fully behind (inside the negative halfspace of) a plane."
    << endl << "//"
    << endl << "bool coneInsidePlane("
    << endl << "    in const Cone cone,"
    << endl << "    in const Plane plane)"
    << endl << "{"
    << endl << "    // Compute the farthest point on the end of the cone to the positive space of the plane."
    << endl << "    vec3 m = cross(cross(plane.N, cone.d), cone.d);"
    << endl << "    vec3 Q = cone.T + cone.d * cone.h - m * cone.r;"
    << endl << ""
    << endl << "    // The cone is in the negative halfspace of the plane if both"
    << endl << "    // the tip of the cone and the farthest point on the end of the cone to the "
    << endl << "    // positive halfspace of the plane are both inside the negative halfspace "
    << endl << "    // of the plane."
    << endl << "    return pointInsidePlane(cone.T, plane) && pointInsidePlane(Q, plane);"
    << endl << "}"
    << endl << ""
    << endl << "bool coneInsideFrustum("
    << endl << "    in const Cone cone,"
    << endl << "    in const Frustum frustum,"
    << endl << "    in const float zNear,"
    << endl << "    in const float zFar)"
    << endl << "{"
    << endl << "    bool result = true;"
    << endl << ""
    << endl << "    Plane nearPlane; nearPlane.N = vec3(0, 0,-1); nearPlane.d = -zNear;"
    << endl << "    Plane  farPlane;  farPlane.N = vec3(0, 0, 1);  farPlane.d =  zFar;"
    << endl << ""
    << endl << "    if (coneInsidePlane(cone, nearPlane) || coneInsidePlane(cone, farPlane))"
    << endl << "    {"
    << endl << "        result = false;"
    << endl << "    }"
    << endl << ""
    << endl << "    for (int i = 0; i < 4 && result; i++)"
    << endl << "    {"
    << endl << "        if (coneInsidePlane(cone, frustum.planes[i]))"
    << endl << "        {"
    << endl << "            result = false;"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    return result;"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Helper function that provides the cluster index (ivec3) of the current work group invocation"
    << endl << "//"
    << endl << "ivec3 clusterAccessor()"
    << endl << "{"
                    //   gl_WorkGroupID - contains the index of the workgroup currently being operated on by a compute shader
                    //                    values range across the parameters passed into glDispatchCompute, i.e. from (0,0,0)
                    //                    to (gl_NumWorkGroups.x-1, gl_NumWorkGroups.y-1, gl_NumWorkGroups.z-1)
                    //                    in uvec3 gl_WorkGroupID 
    << endl << "    return ivec3(gl_WorkGroupID);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Helper function that provides the tile frustum index of the current cluster"
    << endl << "//"
    << endl << "int frustumAccessor()"
    << endl << "{"
                    //   gl_WorkGroupID - contains the index of the workgroup currently being operated on by a compute shader
                    //                    values range across the parameters passed into glDispatchCompute, i.e. from (0,0,0)
                    //                    to (gl_NumWorkGroups.x-1, gl_NumWorkGroups.y-1, gl_NumWorkGroups.z-1)
                    //                    in uvec3 gl_WorkGroupID 
    << endl << "    return int(gl_WorkGroupID.y) * dispatchData.numTiles.x  + int(gl_WorkGroupID.x);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Helper function that provides the tile frustum index of the current cluster"
    << endl << "//"
    << endl << "vec2 getClusterDepth()"
    << endl << "{"
    << endl << "    return vec2(cluster_z(gl_WorkGroupID.z,   clusteringData.zNear, clusteringData.zFar, clusteringData.nD, clusteringData.b, clusteringData.c_1),"
    << endl << "                cluster_z(gl_WorkGroupID.z+1, clusteringData.zNear, clusteringData.zFar, clusteringData.nD, clusteringData.b, clusteringData.c_1));"
    // Debug Test Begin
    //<< endl << "    return vec2(cluster_z_verbose(gl_WorkGroupID.z,   clusteringData.zNear, clusteringData.zFar, clusteringData.D, clusteringData.c),"
    //<< endl << "                cluster_z_verbose(gl_WorkGroupID.z+1, clusteringData.zNear, clusteringData.zFar, clusteringData.D, clusteringData.c));"
    // Debug Test End
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Append the light light_idx to the list of lights to be rendered for "
    << endl << "// this cluster. That is we have to increment the sharedLightCount and"
    << endl << "// to append the light_idx to the sharedLightIndexList."
    << endl << "// "
    << endl << "void appendLight(in const uint light_idx)"
    << endl << "{"
    << endl << "    uint idx = atomicAdd(sharedLightCount, 1);"
    << endl << "    if (idx < 1024)"
    << endl << "    {"
    << endl << "        sharedLightIndexList[idx] = light_idx;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    << endl << "void main()"
    << endl << "{"
    << endl << "    //"
    << endl << "    // Initialize the work group shared state: Only the first thread is needed for that"
    << endl << "    //"
                    //      gl_LocalInvocationIndex - contains the local linear index of work item currently being operated on by a compute shader
                    //                              - in uint gl_LocalInvocationIndex
                    //                              - is a derived input variable containing the 1-dimensional linearized index of the work invocation 
                    //                                within the work group that the current shader is executing on. The value of gl_LocalInvocationIndex 
                    //                                is equal to 
                    //                                      gl_LocalInvocationID.z * gl_WorkGroupSize.x * gl_WorkGroupSize.y 
                    //                                    + gl_LocalInvocationID.y * gl_WorkGroupSize.x 
                    //                                    + gl_LocalInvocationID.x.
                    //
    << endl << "    if (gl_LocalInvocationIndex == 0)"
    << endl << "    {"
    << endl << "        sharedFrustum    = frustums.frustum[frustumAccessor()];"
    << endl << "        sharedFrustumZ   = getClusterDepth();"
    << endl << "        sharedLightCount = 0;"
    // Debug Test Begin
    // << endl << "        sharedTestValue  = 0;"
    // Debug Test End
    << endl << "    }"
    << endl << ""
                    //      memoryBarrierShared - controls the ordering of operations on shared variables issued by a single shader invocation
                    //                          - waits on the completion of all memory accesses resulting from the use of shared variables and 
                    //                            then returns with no other effect. When this function returns, the results of any modifications 
                    //                            to the content of shared variables will be visible to any access to the same buffer from other 
                    //                            shader invocations. In particular, any modifications made in one shader stage are guaranteed to 
                    //                            be visible to accesses performed by shader invocations in subsequent stages when those invocations 
                    //                            were triggered by the execution of the original shader invocation (e.g., fragment shader invocations 
                    //                            for a primitive resulting from a particular geometry shader invocation).
                    //
                    //      barrier             - synchronize execution of multiple shader invocations
                    //                          - provides a partially defined order of execution between shader invocations.
                    //                          - for any given static instance of barrier in a compute shader, all invocations within a single work group 
                    //                            must enter it before any are allowed to continue beyond it. This ensures that values written by one 
                    //                            invocation prior to a given static instance of barrier can be safely read by other invocations after their 
                    //                            call to the same static instance of barrier.
                    //                          - may be placed anywhere in a compute shader. Calls to barrier may not be placed within any control flow.
                    //
    << endl << "    memoryBarrierShared();  // Ensure change to sharedXXX is visible in other invocations"
    << endl << "    barrier();              // Stall until every thread reaches this point"
    << endl << ""
                    //      
                    //      gl_WorkGroupSize - contains the size of the workgroup operated on by a compute shader
                    //                       - const uvec3 gl_WorkGroupSize
                    //                       - contains the size of a workgroup declared by a compute shader. The size of the work group in the X, Y, and Z dimensions 
                    //                         is stored in the x, y, and z components of gl_WorkGroupSize.
                    //                       - match those specified in the required local_size_x, local_size_y, and local_size_z layout qualifiers for the current shader. 
                    //                       - is constant so that it can be used to size arrays of memory that can be shared within the local work group.
                    //
    << endl << "    //"
    << endl << "    // We iterate over all affected lights whereby splitting the lights into subsets for each thread."
    << endl << "    // For each light we test it against the current frustum and if it is inside of the frustum, we add"
    << endl << "    // the light to the group shared list of lights contributing to the current cluster corresponding to"
    << endl << "    // the work group."
    << endl << "    //"
    << endl << "    for (uint i = gl_LocalInvocationIndex; i < affectedLightIndexList.idx.length(); i += gl_WorkGroupSize.x * gl_WorkGroupSize.y * gl_WorkGroupSize.z)"
    << endl << "    {"
    << endl << "        uint light_index = affectedLightIndexList.idx[i];"
    << endl << ""
    // Debug Test Begin
    //<< endl << "        if (!isEqual(sharedFrustumZ.x, testData.value13[gl_WorkGroupID.z]))"
    //<< endl << "            atomicAdd(sharedTestValue, 1);"
    //<< endl << "        if (!isEqual(sharedFrustumZ.y, testData.value14[gl_WorkGroupID.z]))"
    //<< endl << "            atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << "        if (lights.light[light_index].enabled)"
    << endl << "        {"
    << endl << "            Light light = lights.light[light_index];"
    // Debug Test Begin
    //<< endl << "            uint test_idx = light_index      * dispatchData.numTiles.x * dispatchData.numTiles.y * clusteringData.c"
    //<< endl << "                          + gl_WorkGroupID.z * dispatchData.numTiles.x * dispatchData.numTiles.y"
    //<< endl << "                          + gl_WorkGroupID.y * dispatchData.numTiles.x"
    //<< endl << "                          + gl_WorkGroupID.x;"
    // Debug Test End
    << endl << ""
    << endl << "            switch (light.type)"
    << endl << "            {"
    << endl << "                case DIRECTIONAL_LIGHT:"
    << endl << "                {"
    << endl << "                    appendLight(light_index);"
    // Debug Test Begin
    //<< endl << "                    if (test_idx != testData.value15[test_idx])"
    //<< endl << "                        atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << "                }"
    << endl << "                break;"
    << endl << ""
    << endl << "                case POINT_LIGHT:"
    << endl << "                case CINEMA_LIGHT:"
    << endl << "                {"
    << endl << "                    vec4 position = dispatchData.matTransf * vec4(light.position, 1.0);"
    // Debug Test Begin
    //<< endl << "                    if (!isEqual(position.xyz, testData.value16[light_index]))"
    //<< endl << "                        atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << ""
    << endl << "                    Sphere sphere = { position.xyz, light.range };"
    << endl << ""
    << endl << "                    if (sphereInsideFrustum(sphere, sharedFrustum, sharedFrustumZ.x, sharedFrustumZ.y))"
    << endl << "                    {"
    << endl << "                        appendLight(light_index);"
    // Debug Test Begin
    //<< endl << "                        if (test_idx != testData.value15[test_idx])"
    //<< endl << "                            atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << "                    }"
    << endl << "                }"
    << endl << "                break;"
    << endl << ""
    << endl << "                case SPOT_LIGHT:"
    << endl << "                {"
    << endl << "                    vec4 position  = dispatchData.matTransf * vec4(light.position,  1.0);"
    << endl << "                    vec4 direction = dispatchData.matTransf * vec4(light.direction, 0.0);"
    << endl << ""
    // Debug Test Begin
    //<< endl << "                    if (!isEqual(position.xyz, testData.value16[light_index]))"
    //<< endl << "                        atomicAdd(sharedTestValue, 1);"
    //<< endl << "                    if (!isEqual(direction.xyz, testData.value17[light_index]))"
    //<< endl << "                        atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << "                    float radius = tan(light.spotlightAngle) * light.range;"
    << endl << "                    Cone cone = { position.xyz, light.range, direction.xyz, radius };"
    << endl << ""
    << endl << "                    if (coneInsideFrustum(cone, sharedFrustum, sharedFrustumZ.x, sharedFrustumZ.y))"
    << endl << "                    {"
    << endl << "                        appendLight(light_index);"
    // Debug Test Begin
    //<< endl << "                        if (test_idx != testData.value15[test_idx])"
    //<< endl << "                            atomicAdd(sharedTestValue, 1);"
    // Debug Test End
    << endl << "                    }"
    << endl << "                }"
    << endl << "                break;"
    << endl << "            }"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    //"
    << endl << "    // Wait till all threads in group have caught up."
    << endl << "    //"
    << endl << "    memoryBarrierShared();  // Ensure change to sharedXXX is visible in other invocations"
    << endl << "    barrier();              // Stall until every thread reaches this point"
    << endl << ""
    << endl << "    //"
    << endl << "    // Now we have the sharedLightIndexList filled and know by sharedLightCount the number"
    << endl << "    // of lights that are contributing for the current cluster. What we have to do now is"
    << endl << "    // to get space in the global light index list (lightIndexList). For that, we use the"
    << endl << "    // global light index counter (lightIndexCounter) by atomically incrementing it"
    << endl << "    // with the number of lights contributing to the current cluster and getting back the"
    << endl << "    // offset from the start of the global light index list (sharedLightStartOffset)."
    << endl << "    // So now we have requested space on the global light index list and we have the data"
    << endl << "    // that need to be written to the global light grid data image, i.e. the offset from"
    << endl << "    // the beginning of the global light index list and the number of lights to use for"
    << endl << "    // shading the fragments falling into the current cluster."
    << endl << "    //"
    << endl << "    // Only thread 0 is needed for:"
    << endl << "    //      - atomically increment lightIndexCounter by sharedLightCount to get"
    << endl << "    //        sharedLightStartOffset"
    << endl << "    //      - write (sharedLightStartOffset, sharedLightCount) to light grid"
    << endl << "    //"
    << endl << "    if (gl_LocalInvocationIndex == 0)"
    << endl << "    {"
    << endl << "        sharedLightStartOffset = atomicAdd(lightIndexCounter, sharedLightCount);"
    << endl << ""
    << endl << "        uvec4 data = uvec4(sharedLightStartOffset, sharedLightCount, 0, 0);"
    << endl << ""
    << endl << "        //"
    << endl << "        // We must protect from overflow"
    << endl << "        //"
    << endl << "        uint num_indices = lightIndexList.idx.length();"
    << endl << "        if (sharedLightStartOffset + sharedLightCount >= num_indices)"
    << endl << "            data = uvec4(0,0,0,0);"
    << endl << ""
    << endl << "        imageStore(light_grid, clusterAccessor(), data);"
    // Debug Test Begin
    //
    // Test value evaluation
    //
    //<< endl << "         if (cpuFrustums.frustum.length() == 0)                            sharedTestValue += 1;"
    //<< endl << "    else if (   frustums.frustum.length() == 0)                            sharedTestValue += 1;"
    //<< endl << "    else if (   frustums.frustum.length() != cpuFrustums.frustum.length()) sharedTestValue += 1;"
    //<< endl << ""

    //<< endl << "    for (int j = 0; j < cpuFrustums.frustum.length(); ++j)"
    //<< endl << "    {"
    //<< endl << "        for (int i = 0; i < 4; ++i)"
    //<< endl << "        {"
    //<< endl << "                 if (cpuFrustums.frustum[j].planes[i].d != frustums.frustum[j].planes[i].d)         sharedTestValue += 1;"
    //<< endl << "            else if (!isEqual(cpuFrustums.frustum[j].planes[i].N, frustums.frustum[j].planes[i].N)) sharedTestValue += 1;"
    //<< endl << "        }"
    //<< endl << "    }"

    //<< endl << "        if (sharedTestValue > 0)"
    //<< endl << "            sharedTestValue = uiHeatMapColor20;"
    //<< endl << "        else"
    //<< endl << "            sharedTestValue= 1000;"
    //
    //<< endl << "        uvec4 data = uvec4(0, sharedTestValue, 0, 0);"
    //<< endl << "        imageStore(light_grid, clusterAccessor(), data);"

    //
    // Test grid storage
    //
    //<< endl << "        uint light_start_offset = 0;"
    //<< endl << "        uint light_count = 0;"
    //<< endl << "        if (gl_WorkGroupID.x == 0 && gl_WorkGroupID.y == 0)"
    //<< endl << "        {"
    //<< endl << "            light_start_offset =   7345698 + uiHeatMapColor13;"
    //<< endl << "            light_count        = 563472981 + gl_WorkGroupID.z;"
    //<< endl << "        }"
    //<< endl << "        else if (gl_WorkGroupID.x == gl_NumWorkGroups.x-1 && gl_WorkGroupID.y == gl_NumWorkGroups.y-1)"
    //<< endl << "        {"
    //<< endl << "            light_start_offset =   7345698 + uiHeatMapColor13;"
    //<< endl << "            light_count        = 563472981 + uiHeatMapColor8;"
    //<< endl << "        }"
    //<< endl << "        else"
    //<< endl << "        {"
    //<< endl << "            light_start_offset =   7345698 + uiHeatMapColor13;"
    //<< endl << "            light_count        = 563472981 + gl_WorkGroupID.z;"
    //<< endl << "        }"
    //<< endl << "        uvec4 data = uvec4(light_start_offset, light_count, 0, 0);"
    //<< endl << "        imageStore(light_grid, clusterAccessor(), data);"
    // Debug Test End
    << endl << "    }"
    << endl << ""
    << endl << "    memoryBarrierShared();  // Ensure change to sharedXXX is visible in other invocations"
    << endl << "    barrier();              // Stall until every thread reaches this point"
    << endl << ""
    << endl << "    //"
    << endl << "    // The last task is to write the actual lights affecting the current cluster into the"
    << endl << "    // the global light index list. We have already requestet the appropriate space on the"
    << endl << "    // this list so we can just iterate over the local light list (sharedLightIndexList) and"
    << endl << "    // write the carry the content to the global list. That can also be done in parrallel, so"
    << endl << "    // we use all the thread we have at hand."
    << endl << "    //"
    << endl << ""
    << endl << "    uint num_indices = lightIndexList.idx.length();"
    << endl << ""
    << endl << "    for (uint i = gl_LocalInvocationIndex; i < sharedLightCount; i += gl_WorkGroupSize.x * gl_WorkGroupSize.y * gl_WorkGroupSize.z)"
    << endl << "    {"
    << endl << "        if (sharedLightStartOffset + i < num_indices)"
    << endl << "            lightIndexList.idx[sharedLightStartOffset + i] = sharedLightIndexList[i];"
    << endl << "    }"
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

    ost
            << "#version 440 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_shader_storage_buffer_object: enable"
    << endl << "#extension GL_ARB_shader_image_load_store:      enable"
    << endl << ""
    << endl << "smooth in vec3 vNormalES;           // eye space normal"
    << endl << "smooth in vec3 vPositionES;         // eye space position"
    << endl << "" 
    << add_test_colors()
    << endl << "" 
    << endl << "const int num_materials = " << num_materials << ";"
    << endl << ""
    << endl << "const int POINT_LIGHT       = 1;    // defined in OSGMultiLightChunk.h"
    << endl << "const int DIRECTIONAL_LIGHT = 2;"
    << endl << "const int SPOT_LIGHT        = 3;"
    << endl << "const int CINEMA_LIGHT      = 4;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "uniform mat4  OSGViewMatrix;    // from world space to view space transformation"
    << endl << ""
    << endl << "layout(binding = 0, rg32ui) uniform uimage2DArray light_grid;"
    // Debug Test Begin
    //<< endl << "layout(binding = 1, rg32ui) uniform uimage2DArray light_grid_cpu;"
    // Debug Test End
    << endl << ""
    << endl << "struct Light"
    << endl << "{"
    << endl << "    mat4  eyeToLightSpaceMatrix;"
    << endl << "    vec3  position;                 // in world space"
    << endl << "    vec3  direction;                // in world space"
    << endl << "    vec3  color;"
    << endl << "    float intensity;"
    << endl << "    float range;"
    << endl << "    float cosSpotlightAngle;"
    << endl << "    float spotlightAngle;"
    << endl << "    float innerSuperEllipsesWidth;  // a" 
    << endl << "    float innerSuperEllipsesHeight; // b" 
    << endl << "    float outerSuperEllipsesWidth;  // A" 
    << endl << "    float outerSuperEllipsesHeight; // B" 
    << endl << "    float superEllipsesRoundness;   // r"
    << endl << "    float superEllipsesTwist;       // theta"
    << endl << "    int   type;                     // specific type of light: POINT_LIGHT, DIRECTIONAL_LIGHT, SPOT_LIGHT or CINEMA_LIGHT"
    << endl << "    bool  enabled;                  // on/off state of light"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Lights"
    << endl << "{"
    << endl << "    Light light[];"
    << endl << "} lights;"
    << endl << ""
    << endl << "//"
    << endl << "// The affected light index list that is iterated to get the light"
    << endl << "//"
    << endl << "layout (std430) buffer AffectedLightIndexList"
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} affectedLightIndexList;"
    << endl << ""
    << endl << "layout (std430) buffer LightIndexList"
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} lightIndexList;"
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
    << endl << "struct Plane"
    << endl << "{"
    << endl << "    vec3  N;"
    << endl << "    float d;"
    << endl << "};"
    << endl << ""
    << endl << "struct Frustum"
    << endl << "{"
    << endl << "    Plane planes[4];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Frustums"
    << endl << "{"
    << endl << "    Frustum frustum[];"
    << endl << "} frustums;"
    << endl << ""
    // Debug Test Begin
    //<< endl << "layout (std430) buffer CPUFrustums"
    //<< endl << "{"
    //<< endl << "    Frustum frustum[];"
    //<< endl << "} cpuFrustums;"
    //<< endl << ""
    // Debug Test End
    << endl << "layout (std140) uniform ClusteringData"
    << endl << "{"
    << endl << "    float zNear;  // positive near plane distance from eye zNear > 0"
    << endl << "    float zFar;   // positive  far plane distance from eye zFar > zNear > 0"
    //<< endl << "    float D;      // positive near plane offset D >= 0                              // for testing"
    << endl << "    float nD;     // zNear + D : shader optimization"
    << endl << "    float lg_nD;  // log2(nD) : shader optimization"
    << endl << "    float a;      // precalculated factor (c-1)/log2(f/(n+D))"
    << endl << "    float b;      // precalculated factor log2(f/(n+D))/(c-1)"
    //<< endl << "    int   c;      // number of cluster planes                                       // for testing"
    << endl << "    int   c_1;    // number of cluster planes minus one : shader optimization"
    << endl << "    ivec2 p_v;    // viewport corner points"
    //<< endl << "    ivec3 n_c;    // number of clusters                                             // for testing"
    << endl << "    int   t_v;    // test dependent content                                           // for testing"
    << endl << "} clusteringData;"
    << endl << ""
    // Debug Test Begin
    //<< endl << "//"
    //<< endl << "// Pure testing data"
    //<< endl << "//"
    //<< endl << "layout (std430) buffer TestData"
    //<< endl << "{"
    //<< endl << "    float value01;"
    //<< endl << "    float value02;"
    //<< endl << "    float value03;"
    //<< endl << "    float value04;"
    //<< endl << "    vec3  value05;"
    //<< endl << "    vec3  value06;"
    //<< endl << "    int   value07;"
    //<< endl << "    int   value08;"
    //<< endl << "    uint  value09;"
    //<< endl << "    uint  value10;"
    //<< endl << "    ivec3 value11;"
    //<< endl << "    uvec3 value12;"
    //<< endl << "    float value13[" << TestData::num_array_elements << "];"
    //<< endl << "    float value14[" << TestData::num_array_elements << "];"
    //<< endl << "    uint  value15[" << TestData::num_array_elements << "];"
    //<< endl << "    vec3  value16[" << TestData::num_array_elements << "];"
    //<< endl << "    vec3  value17[" << TestData::num_array_elements << "];"
    //<< endl << "} testData;"
    //<< endl << ""
    // Debug Test End
    << endl << "const vec3 cCameraPositionES = vec3(0,0,0); // eye is at vec3(0,0,0) in eye space!"
    << endl << ""
    << endl << "layout(location = 0) out vec4 vFragColor;"
    << endl << ""
    // Debug Test Begin
    //<< endl << "//"
    //<< endl << "// Test equality of two vectors with respect to local eps value"
    //<< endl << "//"
    //<< endl << "bool isEqual(in const vec3 v1, in const vec3 v2)"
    //<< endl << "{"
    //<< endl << "    const float eps = 1.0E-4;"
    //<< endl << "    if (all(lessThan(abs(v1 -v2), vec3(eps,eps,eps))))"
    //<< endl << "        return true;"
    //<< endl << "    else"
    //<< endl << "        return false;"
    //<< endl << "}"
    //<< endl << ""
    // Debug Test End
    << endl << "//"
    << endl << "// cluster_k and cluster_k_verbose calculates the cluster key from the eye space z value"
    << endl << "//      k = cluster_k(z_e, ...) with k in [0, c["
    << endl << "//"
    << endl << "// Formular:"
    << endl << "//      k = 0                                               if z_e >= -(n+D)"
    << endl << "//      k = 1 + (c-1) * log2(z_e/-(n+D)) / log2(f/(n+D))    else"
    << endl << "//      k = c-1                                             if z_e <= -f"
    << endl << "//"
    // Debug Test Begin
    //<< endl << "int cluster_k_verbose("
    //<< endl << "    in const float z_e,    // eye space z-position, z_e < 0"
    //<< endl << "    in const float n,      // near plane distance from viewer n > 0"
    //<< endl << "    in const float f,      //  far plane distance from viewer f > n > 0"
    //<< endl << "    in const float D,      // near plane offset"
    //<< endl << "    in const int   c)      // number of cluster planes"
    //<< endl << "{"
    //<< endl << "    if (z_e >= -(n+D)) return 0;"
    //<< endl << "    if (z_e <= -f)     return c-1;"
    //<< endl << ""
    //<< endl << "    float s = 1.0+(float(c-1)/log2(f/(n+D)))*log2(z_e/-(n+D));"
    //<< endl << "    return clamp(int(s), 0, c-1);"
    //<< endl << "}"
    //<< endl << ""
    // Debug Test Begin
    << endl << "int cluster_k("
    << endl << "    in const float z_e,  // eye space z-position, z_e < 0"
    << endl << "    in const float nD,   // near plane distance plus the offset D from viewer n > 0, D > 0"
    << endl << "    in const float lg_nD,// log2(nD)"
    << endl << "    in const float f,    //  far plane distance from viewer f > n > 0"
    << endl << "    in const float a,    // (c-1)/log2(f/(n+D))"
    << endl << "    in const int   c_1)  // number of cluster planes minus 1"
    << endl << "{"
    << endl << "    if (z_e >= -nD) return 0;"
    << endl << "    if (z_e <= -f)  return c_1;"
    << endl << ""
    << endl << "    float s = 1.0 + a * (log2(-z_e) - lg_nD);"
    << endl << "    return clamp(int(s), 0, c_1);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// OpenGL window space is defined such that pixel centers are on half-integer boundaries."
    << endl << "// So the center of the lower-left pixel is (0.5,0.5). Using pixel_center_integer? adjust"
    << endl << "// gl_FragCoord such that whole integer values represent pixel centers."
    << endl << "// This feature exist to be compatible with D3D's window space. Unless you need your shaders"
    << endl << "// to have this compatibility, you are advised not to use these features."
    << endl << "// => We do not use it!"
    << endl << "//"
    << endl << "// Provide a accessor key to probe the light grid."
    << endl << "//      in p_w : xy-screen position provided by gl_FragCoord.xy: lower-left is (0.5, 0.5)"
    << endl << "//      in z_e : fragment eye space z from vPositionES"
    << endl << "//      out    : 3D image coordinate"
    << endl << "//"
    << endl << "ivec3 gridAccessor("
    << endl << "    in const vec2  p_w,       // xy-screen position provided by gl_FragCoord.xy: lower-left is (0.5, 0.5)"
    << endl << "    in const float z_e)       // fragment eye space z from vPositionES"
    << endl << "{"
    << endl << "    ivec2 q_w = ivec2(p_w - vec2(0.5, 0.5));"
    << endl << "    int k = cluster_k(z_e, clusteringData.nD, clusteringData.lg_nD, clusteringData.zFar, clusteringData.a, clusteringData.c_1);"
    << endl << "    ivec2 p = (q_w - clusteringData.p_v) / tile_size;"
    << endl << "    return ivec3(p.xy, k);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Retrieve the cluster light grid data."
    << endl << "//      in p_w : xy-screen position provided by gl_FragCoord.xy: lower-left is (0.5, 0.5)"
    << endl << "//      in z_e : fragment eye space z from vPositionES"
    << endl << "//      out    : (light index list start position, number of lights)"
    << endl << "//"
    << endl << "uvec2 getGridData("
    << endl << "    in const vec2  p_w,"
    << endl << "    in const float z_e)"
    << endl << "{"
    << endl << "    ivec3 accessor = gridAccessor(p_w, z_e);"
    << endl << "    return imageLoad(light_grid, accessor).xy;"
    << endl << "}"
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
    << endl << "    if (lights.light[i].range < d)"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].range, d);"
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
    << endl << "    if (lights.light[i].range < d)"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].range, d);"
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
    << endl << "    if (lights.light[i].range < d)"
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
    << endl << "    float attenuation = calcAttenuation(lights.light[i].range, d);"
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
    //<< endl << "    uvec2 grid_data = getGridData(gl_FragCoord.xy, vPositionES.z);"
    //<< endl << ""
    //<< endl << "    uint list_idx    = grid_data.x;"
    //<< endl << "    uint light_count = grid_data.y;"
    //<< endl << ""
    //<< endl << "    if (clusteringData.t_v == 1)"
    //<< endl << "        light_count = num_lights;"
    //<< endl << ""

    << endl << "    uint list_idx    = 0;"
    << endl << "    uint light_count = 0;"
    << endl << ""
    << endl << "    if (clusteringData.t_v == 0)"
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

    // Debug Test Begin
    //
    // Consitency check
    //
    //<< endl << "    uint num_indices = lightIndexList.idx.length();"
    //<< endl << "    uint num_lights  = lights.light.length();"
    //<< endl << ""
    //<< endl << "    if (num_indices != " << light_index_list_size << ")"
    //<< endl << "        color = Cyan.xyz;"
    //<< endl << ""
    //<< endl << "    if (list_idx+light_count >= num_indices)"   // do not blow up the lightIndexList.idx array
    //<< endl << "        color = Red.xyz;"
    //<< endl << ""
    //<< endl << "    if (light_count > num_lights)"              // do not blow up the lights.light array
    //<< endl << "        color = Yellow.xyz;"
    // Debug Test End

    << endl << ""
    << endl << "    for (uint i = 0; i < light_count; ++i)"
    << endl << "    {"
    << endl << "        uint light_idx = (clusteringData.t_v == 0) ? lightIndexList.idx[list_idx+i] : affectedLightIndexList.idx[i];"
    << endl << ""
    << endl << "        switch (lights.light[light_idx].type)"
    << endl << "        {"
    << endl << "            case       POINT_LIGHT: color +=       pointLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case DIRECTIONAL_LIGHT: color += directionalLight(light_idx, geom_state.material_index, N, V);               break;"
    << endl << "            case        SPOT_LIGHT: color +=        spotLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "            case      CINEMA_LIGHT: color +=      cinemaLight(light_idx, geom_state.material_index, N, V, vPositionES);  break;"
    << endl << "        }"
    << endl << "    }"
    << endl << ""
    << endl << "    vFragColor = vec4(color, materials.material[geom_state.material_index].opacity);"
    << endl << ""
    // Debug Test Begin
    //
    // The following test checks if the layout of the cpu and gpu calculated frustums are identical
    //
    //<< endl << ""
    //<< endl << "         if (cpuFrustums.frustum.length() == 0)                            vFragColor = Red;"
    //<< endl << "    else if (gpuFrustums.frustum.length() == 0)                            vFragColor = Green;"
    //<< endl << "    else if (gpuFrustums.frustum.length() != cpuFrustums.frustum.length()) vFragColor = Blue;"
    //<< endl << ""

    //
    // The following test is really, really computational intensive. Therefore it is commented and to be used
    // only deliberately.
    //
    //<< endl << "    for (int j = 0; j < cpuFrustums.frustum.length(); ++j)"
    //<< endl << "    {"
    //<< endl << "        for (int i = 0; i < 4; ++i)"
    //<< endl << "        {"
    //<< endl << "                 if (cpuFrustums.frustum[j].planes[i].d != gpuFrustums.frustum[j].planes[i].d)         vFragColor = Yellow;"
    //<< endl << "            else if (!isEqual(cpuFrustums.frustum[j].planes[i].N, gpuFrustums.frustum[j].planes[i].N)) vFragColor = Cyan;"
    //<< endl << "        }"
    //<< endl << "    }"

    //
    // Test with artificially filled CPU/GPU grid data
    //
    //<< endl << "    ivec3 accessor = gridAccessor(gl_FragCoord.xy, vPositionES.z);"
    //<< endl << ""
    //<< endl << "    uvec2 data_cpu = imageLoad(light_grid_cpu, accessor).xy;"
    //<< endl << "    uvec2 data_gpu = imageLoad(light_grid,     accessor).xy;"
    //<< endl << ""
    //<< endl << "    uint test_value_x = data_gpu.x -   7345698;"
    //<< endl << "    uint test_value_y = data_gpu.y - 563472981;"
    //<< endl << ""
    //<< endl << "    uint test_value   = test_value_y;"
    //<< endl << ""
    //<< endl << "    if (test_value ==  0)  vFragColor = HeatMapColor0;  // Black"
    //<< endl << "    if (test_value ==  1)  vFragColor = HeatMapColor1;  // DarkSlateGray"
    //<< endl << "    if (test_value ==  2)  vFragColor = HeatMapColor2;  // Navy"
    //<< endl << "    if (test_value ==  3)  vFragColor = HeatMapColor3;  // Blue"
    //<< endl << "    if (test_value ==  4)  vFragColor = HeatMapColor4;  // RoyalBlue"
    //<< endl << "    if (test_value ==  5)  vFragColor = HeatMapColor5;  // DodgerBlue"
    //<< endl << "    if (test_value ==  6)  vFragColor = HeatMapColor6;  // DeepSkyBlue"
    //<< endl << "    if (test_value ==  7)  vFragColor = HeatMapColor7;  // Turquoise"
    //<< endl << "    if (test_value ==  8)  vFragColor = HeatMapColor8;  // Aquamarine"
    //<< endl << "    if (test_value ==  9)  vFragColor = HeatMapColor9;  // Cyan"
    //<< endl << "    if (test_value == 10)  vFragColor = HeatMapColor10; // DarkGreen"
    //<< endl << "    if (test_value == 11)  vFragColor = HeatMapColor11; // Green"
    //<< endl << "    if (test_value == 12)  vFragColor = HeatMapColor12; // SpringGreen"
    //<< endl << "    if (test_value == 13)  vFragColor = HeatMapColor13; // Lime"
    //<< endl << "    if (test_value == 14)  vFragColor = HeatMapColor14; // Chartreuse"
    //<< endl << "    if (test_value == 15)  vFragColor = HeatMapColor15; // GreenYellow"
    //<< endl << "    if (test_value == 16)  vFragColor = HeatMapColor16; // Yellow"
    //<< endl << "    if (test_value == 17)  vFragColor = HeatMapColor17; // Gold"
    //<< endl << "    if (test_value == 18)  vFragColor = HeatMapColor18; // DarkOrange"
    //<< endl << "    if (test_value == 19)  vFragColor = HeatMapColor19; // OrangeRed"
    //<< endl << "    if (test_value == 20)  vFragColor = HeatMapColor20; // Red"
    //<< endl << "    if (test_value == 21)  vFragColor = HeatMapColor21; // FireBrick"
    //<< endl << "    if (test_value == 22)  vFragColor = HeatMapColor22; // DarkRed"
    //<< endl << "    if (test_value == 23)  vFragColor = HeatMapColor23; // BlueViolet"
    //<< endl << "    if (test_value == 24)  vFragColor = HeatMapColor24; // Fuchsia"
    //<< endl << "    if (test_value == 25)  vFragColor = HeatMapColor25; // DeepPink"
    //<< endl << "    if (test_value == 26)  vFragColor = HeatMapColor26; // HotPink"
    //<< endl << "    if (test_value == 27)  vFragColor = HeatMapColor27; // Pink"
    //<< endl << "    if (test_value == 28)  vFragColor = HeatMapColor28; // MistyRose"
    //<< endl << "    if (test_value == 29)  vFragColor = HeatMapColor29; // LavenderBlush"
    //<< endl << "    if (test_value == 30)  vFragColor = HeatMapColor30; // Seashell"
    //<< endl << "    if (test_value == 31)  vFragColor = HeatMapColor31; // White"

    //
    // Test LC 4: Check if the CPU light grid is identical to the GPU light grid
    //
    //<< endl << "    ivec3 accessor = gridAccessor(gl_FragCoord.xy, vPositionES.z);"
    //<< endl << ""
    //<< endl << "    uvec2 data_cpu = imageLoad(light_grid_cpu, accessor).xy;"
    //<< endl << "    uvec2 data_gpu = imageLoad(light_grid,     accessor).xy;"
    //<< endl << ""
    //<< endl << "    if (data_cpu.y != data_gpu.y)  vFragColor = SteelBlue;"
    //<< endl << ""

    //<< endl << "    ivec3 accessor = gridAccessor(gl_FragCoord.xy, vPositionES.z);"
    //<< endl << ""
    //<< endl << "    uvec2 data_gpu = imageLoad(light_grid,     accessor).xy;"
    //<< endl << ""
    //<< endl << "    uint test_value = data_gpu.y;"
    //<< endl << ""
    //<< endl << "    if (test_value ==  0)  vFragColor = HeatMapColor0;  // Black"
    //<< endl << "    if (test_value ==  1)  vFragColor = HeatMapColor1;  // DarkSlateGray"
    //<< endl << "    if (test_value ==  2)  vFragColor = HeatMapColor2;  // Navy"
    //<< endl << "    if (test_value ==  3)  vFragColor = HeatMapColor3;  // Blue"
    //<< endl << "    if (test_value ==  4)  vFragColor = HeatMapColor4;  // RoyalBlue"
    //<< endl << "    if (test_value ==  5)  vFragColor = HeatMapColor5;  // DodgerBlue"
    //<< endl << "    if (test_value ==  6)  vFragColor = HeatMapColor6;  // DeepSkyBlue"
    //<< endl << "    if (test_value ==  7)  vFragColor = HeatMapColor7;  // Turquoise"
    //<< endl << "    if (test_value ==  8)  vFragColor = HeatMapColor8;  // Aquamarine"
    //<< endl << "    if (test_value ==  9)  vFragColor = HeatMapColor9;  // Cyan"
    //<< endl << "    if (test_value == 10)  vFragColor = HeatMapColor10; // DarkGreen"
    //<< endl << "    if (test_value == 11)  vFragColor = HeatMapColor11; // Green"
    //<< endl << "    if (test_value == 12)  vFragColor = HeatMapColor12; // SpringGreen"
    //<< endl << "    if (test_value == 13)  vFragColor = HeatMapColor13; // Lime"
    //<< endl << "    if (test_value == 14)  vFragColor = HeatMapColor14; // Chartreuse"
    //<< endl << "    if (test_value == 15)  vFragColor = HeatMapColor15; // GreenYellow"
    //<< endl << "    if (test_value == 16)  vFragColor = HeatMapColor16; // Yellow"
    //<< endl << "    if (test_value == 17)  vFragColor = HeatMapColor17; // Gold"
    //<< endl << "    if (test_value == 18)  vFragColor = HeatMapColor18; // DarkOrange"
    //<< endl << "    if (test_value == 19)  vFragColor = HeatMapColor19; // OrangeRed"
    //<< endl << "    if (test_value == 20)  vFragColor = HeatMapColor20; // Red"
    //<< endl << "    if (test_value == 21)  vFragColor = HeatMapColor21; // FireBrick"
    //<< endl << "    if (test_value == 22)  vFragColor = HeatMapColor22; // DarkRed"
    //<< endl << "    if (test_value == 23)  vFragColor = HeatMapColor23; // BlueViolet"
    //<< endl << "    if (test_value == 24)  vFragColor = HeatMapColor24; // Fuchsia"
    //<< endl << "    if (test_value == 25)  vFragColor = HeatMapColor25; // DeepPink"
    //<< endl << "    if (test_value == 26)  vFragColor = HeatMapColor26; // HotPink"
    //<< endl << "    if (test_value == 27)  vFragColor = HeatMapColor27; // Pink"
    //<< endl << "    if (test_value == 28)  vFragColor = HeatMapColor28; // MistyRose"
    //<< endl << "    if (test_value == 29)  vFragColor = HeatMapColor29; // LavenderBlush"
    //<< endl << "    if (test_value == 30)  vFragColor = HeatMapColor30; // Seashell"
    //<< endl << "    if (test_value == 31)  vFragColor = HeatMapColor31; // White"
    // Debug Test End
    << endl << ""
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

