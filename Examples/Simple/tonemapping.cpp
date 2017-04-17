// OpenSG Tutorial Example: tonemapping
//
// This example shows the usage of the HDR2Stage for tonemapping and blooming.
//
// The example uses the Antweak bar for gui rendering on top of OpenSG.
//

#define USE_MIRROR_SPHERE

#include <cstddef>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign/std/vector.hpp>

#ifdef OSG_WITH_ANTTWEAKBAR
#include <AntTweakBar.h>
#endif

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
#include <OSGSkyBackground.h>
#include <OSGSolidBackground.h>
#include <OSGShaderVariableOSG.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialGroup.h>
#include <OSGMaterialChunkOverrideGroup.h>
#include <OSGUniformBufferObjStd140Chunk.h>
#include <OSGPolygonChunk.h>
#include <OSGDepthChunk.h>
#include <OSGShaderProgramVariableChunk.h>
#include <OSGSimpleSHLChunk.h>
#include <OSGHDR2Stage.h>
#include <OSGCallbackAlgorithm.h>
#include <OSGCallbackAlgorithmForeground.h>
#include <OSGCubeMapGenerator.h>
#include <OSGVisitSubTree.h>
#include <OSGImageFileHandler.h>
#include <OSGTextureObjChunk.h>
#include <OSGRandomPoolManager.h>

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
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGShaderVariableOSG.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGMaterialChunkOverrideGroup.h>
#include <OpenSG/OSGUniformBufferObjStd140Chunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGShaderProgramVariableChunk.h>
#include <OpenSG/OSGSimpleSHLChunk.h>
#include <OpenSG/OSGHDR2Stage.h>
#include <OpenSG/OSGCallbackAlgorithm.h>
#include <OpenSG/OSGCallbackAlgorithmForeground.h>
#include <OpenSG/OSGCubeMapGenerator.h>
#include <OpenSG/OSGVisitSubTree.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGRandomPoolManager.h>
#endif

/*---- Light --------------------------------------------------------------*/

struct Light
{
    enum Type
    {
        directional_light = 0,
        point_light,
        spot_light,
        no_light
    };

    Light();

    static Light        create_light(Type e);

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

/*---- Material -----------------------------------------------------------*/

struct Material
{
    Material();

    OSG::Color3f ambient;
    OSG::Color3f diffuse;
    OSG::Color3f specular;
    OSG::Color3f emissive;

    OSG::Real32  opacity;
    OSG::Real32  shininess;
};

typedef std::vector<Material> VecMaterialsT;        // multiple materials

VecMaterialsT initialize_materials(std::size_t num); // helper to create materials

const std::size_t num_materials = 100;              // any number of materials

/*---- GeomState ----------------------------------------------------------*/

struct GeomState
{
    GeomState();

    OSG::UInt32  material_index;
};

const std::size_t num_geometries = 10;               // number of colored geometry: cyl + torus mirror_sphere + colored spheres
const float circle_radius = 5.f;

/*---- HDRShaderData ------------------------------------------------------*/

struct HDRShaderData
{
    HDRShaderData();
    HDRShaderData(const HDRShaderData& rhs);

    HDRShaderData&  operator=   (const HDRShaderData& rhs);

    static HDRShaderData create_min_shader_data();
    static HDRShaderData create_max_shader_data();

    float bloomThreshold;
    float bloomMagnitude;
    int   toneMapTechnique;
    float exposure;
    float keyValue;
    int   autoExposure;
    float whiteLevel;
    float shoulderStrength;
    float linearStrength;
    float linearAngle;
    float toeStrength;
    float toeNumerator;
    float toeDenominator;
    float linearWhite;
    float lumSaturation;
    float bias;
    float tau;
    int   nTaps;
    float sigma;
    bool  useLinChromInterp;
};

/*---- Example ------------------------------------------------------------*/

class Example
{
public:
    static void displayCB   ()                                      { if (_pExample) _pExample->display(); }
    static void reshapeCB   (int w, int h)                          { if (_pExample) _pExample->reshape(w, h); }
    static void mouseCB     (int button, int state, int x, int y)   { if (_pExample) _pExample->mouse(button, state, x, y); }
    static void motionCB    (int x, int y)                          { if (_pExample) _pExample->motion(x, y); }
    static void keyboardCB  (unsigned char k, int x, int y)         { if (_pExample) _pExample->keyboard(k, x, y); }
    static void specialCB   (int k, int x, int y)                   { if (_pExample) _pExample->special(k, x, y); }

public:
            Example(int argc, char *argv[]);
           ~Example();

private:
    void                        initialize                          (int argc, char *argv[]);
    int                         setupGLUT                           (int *argc, char *argv[]);
    void                        initialize_skybackgrounds           ();

    void                        display                             ();
    void                        reshape                             (int w, int h);
    void                        mouse                               (int button, int state, int x, int y);
    void                        motion                              (int x, int y);
    void                        keyboard                            (unsigned char k, int x, int y);
    void                        special                             (int key, int x, int y);
    void                        tweakbar                            (OSG::DrawEnv* drawEnv);

    void                        setupScene                          ();

    std::string                 get_vp_program                      ();
    std::string                 get_fp_program                      ();

    // Light
    OSG::Pnt3f                  transform_to_eye_space              (const OSG::Pnt3f& p, OSG::SimpleSceneManager* pSSM);
    OSG::Vec3f                  transform_to_eye_space              (const OSG::Vec3f& v, OSG::SimpleSceneManager* pSSM);

    std::size_t                 calc_light_buffer_size              (const VecLightsT& lights);
    std::vector<OSG::UInt8>     create_light_buffer                 (const VecLightsT& lights);

    OSG::UniformBufferObjStd140ChunkTransitPtr
                                create_light_state                  (const VecLightsT& lights);
    void                        update_light_state                  (OSG::UniformBufferObjStd140Chunk* ubo, const VecLightsT& lights);

    // Material
    std::size_t                 calc_material_database_buffer_size  (const VecMaterialsT& materials);
    std::vector<OSG::UInt8>     create_material_database_buffer     (const VecMaterialsT& materials);

    OSG::UniformBufferObjStd140ChunkTransitPtr 
                                create_material_database_state      (const VecMaterialsT& materials);
    void                        update_material_database_state      (OSG::UniformBufferObjStd140Chunk* ubo, const VecMaterialsT& materials);

    // Geom state
    std::size_t                 calc_geometry_material_buffer_size  ();
    std::vector<OSG::UInt8>     create_geometry_material_buffer     (const GeomState& geom_state);

    OSG::UniformBufferObjStd140ChunkTransitPtr 
                                create_geometry_material_state      (const GeomState& geom_state);
    void                        update_geometry_material_state      (OSG::UniformBufferObjStd140Chunk* ubo, const GeomState& geom_state);

    // HDR stage
    void                        create_hdr_stage                    ();
    void                        setup_hdr_stage                     ();

#ifdef OSG_WITH_ANTTWEAKBAR
private:
    void    setupTweakBar   ();

public:
    void    ResetParameters     ();
    void    SetSampleNumber     (int   value);                  int                 GetSampleNumber     () const;
    void    SetClearColor       (const OSG::Color3f& value);    const OSG::Color3f& GetClearColor       () const;
    void    SetForceBgnd        (bool  value);                  bool                GetForceBgnd        () const;
    void    SetAjustLuminance   (bool  value);                  bool                GetAjustLuminance   () const;
    void    SetSkyBgndIndex     (int   value);                  int                 GetSkyBgndIndex     () const;
    void    SetPerformBloom     (bool  value);                  bool                GetPerformBloom     () const;
    void    SetBloomBackground  (bool  value);                  bool                GetBloomBackground  () const;
    void    SetCarryDepth       (bool  value);                  bool                GetCarryDepth       () const;
    void    SetResultIndex      (int   value);                  int                 GetResultIndex      () const;
    void    SetRenderEmissive   (bool  value);                  bool                GetRenderEmissive   () const;
    void    SetRenderAmbient    (bool  value);                  bool                GetRenderAmbient    () const;
    void    SetRenderDiffuse    (bool  value);                  bool                GetRenderDiffuse    () const;
    void    SetRenderSpecular   (bool  value);                  bool                GetRenderSpecular   () const;
    void    SetAccurateGamma    (bool  value);                  bool                GetAccurateGamma    () const;
    void    SetGamma            (bool  value);                  bool                GetGamma            () const;
    void    SetUseITURBT709     (bool  value);                  bool                GetUseITURBT709     () const;
    void    SetMipmapLevel      (int   value);                  int                 GetMipmapLevel      () const;
    void    SetBloomThreshold   (float value);                  float               GetBloomThreshold   () const;
    void    SetBloomMagnitude   (float value);                  float               GetBloomMagnitude   () const;
    void    SetToneMapTechnique (int   value);                  int                 GetToneMapTechnique () const;
    void    SetExposure         (float value);                  float               GetExposure         () const;
    void    SetKeyValue         (float value);                  float               GetKeyValue         () const;
    void    SetAutoExposure     (int   value);                  int                 GetAutoExposure     () const;
    void    SetWhiteLevel       (float value);                  float               GetWhiteLevel       () const;
    void    SetShoulderStrength (float value);                  float               GetShoulderStrength () const;
    void    SetLinearStrength   (float value);                  float               GetLinearStrength   () const;
    void    SetLinearAngle      (float value);                  float               GetLinearAngle      () const;
    void    SetToeStrength      (float value);                  float               GetToeStrength      () const;
    void    SetToeNumerator     (float value);                  float               GetToeNumerator     () const;
    void    SetToeDenominator   (float value);                  float               GetToeDenominator   () const;
    void    SetLinearWhite      (float value);                  float               GetLinearWhite      () const;
    void    SetLumSaturation    (float value);                  float               GetLumSaturation    () const;
    void    SetBias             (float value);                  float               GetBias             () const;
    void    SetTau              (float value);                  float               GetTau              () const;
    void    SetNTaps            (int   value);                  int                 GetNTaps            () const;
    void    SetSigma            (float value);                  float               GetSigma            () const;
    void    SetUseLinChromInterp(bool  value);                  bool                GetUseLinChromInterp() const;
#endif

private:
    static Example*                         _pExample;  // Hack

    OSG::SimpleSceneManagerRefPtr           _mgr;

    VecLightsT                              _lights;
    VecMaterialsT                           _materials;

    OSG::NodeRefPtr                         _hdrRoot;
    OSG::HDR2StageRefPtr                    _hdrStage;

    OSG::TransformRefPtr                    _geom_trans[num_geometries];
    
    OSG::SimpleSHLChunkRefPtr               _prog_chunk;

    OSG::UniformBufferObjStd140ChunkRefPtr  _ubo_light_state;
    OSG::UniformBufferObjStd140ChunkRefPtr  _ubo_geom_state[num_geometries];

    HDRShaderData                           _hdrShaderData;
    HDRShaderData                           _hdrShaderDataDefault;
    HDRShaderData                           _hdrShaderDataMin;
    HDRShaderData                           _hdrShaderDataMax;

    bool                                    _gamma;
    bool                                    _accurate_gamma;
    bool                                    _use_ITU_R_BT_709;
    int                                     _mipmap_level;
    int                                     _num_samples;

    OSG::Color3f                            _clear_color;
    bool                                    _force_bgnd;
    bool                                    _adjust_luminance;

    OSG::SolidBackgroundRefPtr              _solidBgnd;
    typedef std::vector<std::pair<std::string, OSG::SkyBackgroundRefPtr> >  VecSkyBgndT;
    VecSkyBgndT                             _vecSkyBgnd;
    int                                     _skyBgnd_index;

    int                                     _result_index;

    bool                                    _render_ambient;
    bool                                    _render_diffuse;
    bool                                    _render_specular;
    bool                                    _render_emissive;

    bool                                    _perform_bloom;
    bool                                    _bloom_background;
    bool                                    _carry_depth;

    bool                                    _pause;

#ifdef OSG_WITH_ANTTWEAKBAR
    TwBar*                                  _tweakbar; 
#endif
};

/*---- helper -------------------------------------------------------------*/

std::size_t align_offset(std::size_t base_alignment, std::size_t base_offset)
{
    return base_alignment * ((base_alignment + base_offset - 1) / base_alignment);
}

/*---- Example ------------------------------------------------------------*/

Example* Example::_pExample = NULL;

Example::Example(int argc, char *argv[])
: _mgr(NULL)
, _lights(initialize_lights())
, _materials(initialize_materials(num_materials))
, _hdrRoot(NULL)
, _hdrStage(NULL)
, _prog_chunk(NULL)
, _ubo_light_state(NULL)
, _hdrShaderData()
, _hdrShaderDataDefault()
, _hdrShaderDataMin(HDRShaderData::create_min_shader_data())
, _hdrShaderDataMax(HDRShaderData::create_max_shader_data())
, _gamma(true)
, _accurate_gamma(true)
, _use_ITU_R_BT_709(true)
, _mipmap_level(-1)
, _num_samples(4)
, _clear_color(0.0f, 0.0f, 0.4f)
, _force_bgnd(false)
, _adjust_luminance(true)
, _solidBgnd(NULL)
, _vecSkyBgnd()
, _skyBgnd_index(-1)
, _result_index(OSG::HDR2Stage::COMPOSITE_TEXTURE)
, _render_ambient(true)
, _render_diffuse(true)
, _render_specular(true)
, _render_emissive(false)
, _perform_bloom(true)
, _bloom_background(true)
, _carry_depth(true)
, _pause(true)
#ifdef OSG_WITH_ANTTWEAKBAR
, _tweakbar(NULL)
#endif
{
    for (std::size_t i = 0; i < num_geometries; ++i)
    {
        _geom_trans[i]     = NULL;
        _ubo_geom_state[i] = NULL;
    }

    initialize(argc, argv);
}

Example::~Example()
{
    _pExample = NULL;
}

void Example::initialize(int argc, char *argv[])
{
    _pExample = this;

    //
    // This might be necessary depending on the
    // used platform to ensure that the corresponding
    // libraries get loaded.
    //
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    OSG::preloadSharedObject("OSGContribPLY");

    // OSG init
    OSG::osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwInit(TW_OPENGL_CORE, NULL);
#endif

    // the connection between GLUT and OpenSG
    OSG::GLUTWindowRefPtr gwin = OSG::GLUTWindow::create();
    gwin->setGlutId(winid);
    gwin->init();

    // create a callback for AntTweakBar drawing
    OSG::RenderFunctor functor = boost::bind(&Example::tweakbar, this, _1);

    OSG::CallbackAlgorithmRefPtr cbAlgorithm = OSG::CallbackAlgorithm::create();
    cbAlgorithm->setCallback(functor, "");

    // create a callback foreground for the AntTweackBar drawing callback
    OSG::CallbackAlgorithmForegroundRefPtr cbForeground = OSG::CallbackAlgorithmForeground::create();
    cbForeground->setCallbackAlgorithm(cbAlgorithm);


    // create the SimpleSceneManager helper
    _mgr = OSG::SimpleSceneManager::create();
    _mgr->setWindow(gwin);

    _mgr->addForeground(cbForeground);

    initialize_skybackgrounds();
    setupScene();

    _solidBgnd = OSG::SolidBackground::create();
    _solidBgnd->setColor(_clear_color);

    if (_skyBgnd_index >= 0 && _skyBgnd_index < int(_vecSkyBgnd.size()))
        _mgr->setBackground(_vecSkyBgnd[_skyBgnd_index].second);
    else
        _mgr->setBackground(_solidBgnd);

    // show the whole scene
    _mgr->showAll();

#ifdef OSG_WITH_ANTTWEAKBAR
    setupTweakBar();
#endif
}

void Example::initialize_skybackgrounds()
{
    namespace fs = boost::filesystem;

    using namespace boost::assign;

    std::vector<fs::path> names;
    names += "+x", "negx";

    std::vector<fs::path> extensions;
    extensions += ".jpg", ".jpeg", ".png";

    fs::path skybox_path("data/skybox");
    try
    {
        // default hdr cross cube map
        fs::path file("data/grace_cross.chdr");
        if (fs::exists(file) && fs::is_regular_file(file))
        {
            std::string skybox_name = file.filename().stem().string();

            OSG::SkyBackgroundRefPtr skyBgnd = OSG::SkyBackground::create();
            OSG::ImageUnrecPtr image = OSG::ImageFileHandler::the()->read(file.string().c_str());
            OSG::TextureObjChunkUnrecPtr texObj = OSG::TextureObjChunk::create();

            texObj->setImage(image);
            texObj->setInternalFormat(GL_RGB32F);
            texObj->setWrapS(GL_CLAMP_TO_EDGE);
            texObj->setWrapT(GL_CLAMP_TO_EDGE);

            skyBgnd->setFrontTexture (texObj);
            skyBgnd->setBackTexture  (texObj);
            skyBgnd->setLeftTexture  (texObj);
            skyBgnd->setRightTexture (texObj);
            skyBgnd->setTopTexture   (texObj);
            skyBgnd->setBottomTexture(texObj);

            _vecSkyBgnd.push_back(std::make_pair(skybox_name, skyBgnd));
        }

        // try to lookup more cube maps for the sky background
        if (exists(skybox_path) && fs::is_directory(skybox_path))
        {
            fs::directory_iterator iter(skybox_path);
            fs::directory_iterator end;

            for (; iter != end; ++iter)
            {
                if (fs::is_directory(iter->status()))
                {
                    const fs::path dir = *iter;

                    std::string skybox_name = dir.filename().string();

                    BOOST_FOREACH(fs::path name, names)
                    {
                        BOOST_FOREACH(fs::path ext, extensions)
                        {
                            fs::path p = dir / name; p.replace_extension(ext);
                            if (fs::exists(p))
                            {
                                fs::path pth_negx, pth_negy, pth_negz, pth_posx, pth_posy, pth_posz;

                                if (name == "+x")
                                {
                                    pth_negx = dir / "-x"; pth_negx.replace_extension(ext);
                                    pth_negy = dir / "-y"; pth_negy.replace_extension(ext);
                                    pth_negz = dir / "-z"; pth_negz.replace_extension(ext);
                                    pth_posx = dir / "+x"; pth_posx.replace_extension(ext);
                                    pth_posy = dir / "+y"; pth_posy.replace_extension(ext);
                                    pth_posz = dir / "+z"; pth_posz.replace_extension(ext);
                                }
                                else
                                {
                                    pth_negx = dir / "negx"; pth_negx.replace_extension(ext);
                                    pth_negy = dir / "negy"; pth_negy.replace_extension(ext);
                                    pth_negz = dir / "negz"; pth_negz.replace_extension(ext);
                                    pth_posx = dir / "posx"; pth_posx.replace_extension(ext);
                                    pth_posy = dir / "posy"; pth_posy.replace_extension(ext);
                                    pth_posz = dir / "posz"; pth_posz.replace_extension(ext);
                                }

                                if (fs::exists(pth_negx) && fs::exists(pth_negy) && fs::exists(pth_negz) && 
                                    fs::exists(pth_posx) && fs::exists(pth_posy) && fs::exists(pth_posz))
                                {
                                    OSG::SkyBackgroundRefPtr skyBgnd = OSG::SkyBackground::create();

                                    OSG::ImageUnrecPtr imgNegX = OSG::ImageFileHandler::the()->read(pth_negx.string().c_str());
                                    OSG::ImageUnrecPtr imgNegY = OSG::ImageFileHandler::the()->read(pth_negy.string().c_str());
                                    OSG::ImageUnrecPtr imgNegZ = OSG::ImageFileHandler::the()->read(pth_negz.string().c_str());
                                    OSG::ImageUnrecPtr imgPosX = OSG::ImageFileHandler::the()->read(pth_posx.string().c_str());
                                    OSG::ImageUnrecPtr imgPosY = OSG::ImageFileHandler::the()->read(pth_posy.string().c_str());
                                    OSG::ImageUnrecPtr imgPosZ = OSG::ImageFileHandler::the()->read(pth_posz.string().c_str());

                                    OSG::TextureObjChunkUnrecPtr texObjNegX = OSG::TextureObjChunk::create();
                                    OSG::TextureObjChunkUnrecPtr texObjNegY = OSG::TextureObjChunk::create();
                                    OSG::TextureObjChunkUnrecPtr texObjNegZ = OSG::TextureObjChunk::create();
                                    OSG::TextureObjChunkUnrecPtr texObjPosX = OSG::TextureObjChunk::create();
                                    OSG::TextureObjChunkUnrecPtr texObjPosY = OSG::TextureObjChunk::create();
                                    OSG::TextureObjChunkUnrecPtr texObjPosZ = OSG::TextureObjChunk::create();

                                    texObjNegX->setImage(imgNegX);
                                    texObjNegY->setImage(imgNegY);
                                    texObjNegZ->setImage(imgNegZ);
                                    texObjPosX->setImage(imgPosX);
                                    texObjPosY->setImage(imgPosY);
                                    texObjPosZ->setImage(imgPosZ);

                                    texObjNegX->setInternalFormat(GL_RGB32F);
                                    texObjNegY->setInternalFormat(GL_RGB32F);
                                    texObjNegZ->setInternalFormat(GL_RGB32F);
                                    texObjPosX->setInternalFormat(GL_RGB32F);
                                    texObjPosY->setInternalFormat(GL_RGB32F);
                                    texObjPosZ->setInternalFormat(GL_RGB32F);

                                    texObjNegX->setWrapS(GL_CLAMP_TO_EDGE);
                                    texObjNegY->setWrapS(GL_CLAMP_TO_EDGE);
                                    texObjNegZ->setWrapS(GL_CLAMP_TO_EDGE);
                                    texObjPosX->setWrapS(GL_CLAMP_TO_EDGE);
                                    texObjPosY->setWrapS(GL_CLAMP_TO_EDGE);
                                    texObjPosZ->setWrapS(GL_CLAMP_TO_EDGE);

                                    texObjNegX->setWrapT(GL_CLAMP_TO_EDGE);
                                    texObjNegY->setWrapT(GL_CLAMP_TO_EDGE);
                                    texObjNegZ->setWrapT(GL_CLAMP_TO_EDGE);
                                    texObjPosX->setWrapT(GL_CLAMP_TO_EDGE);
                                    texObjPosY->setWrapT(GL_CLAMP_TO_EDGE);
                                    texObjPosZ->setWrapT(GL_CLAMP_TO_EDGE);

                                    skyBgnd->setBackTexture  (texObjNegZ);
                                    skyBgnd->setFrontTexture (texObjPosZ);
                                    skyBgnd->setLeftTexture  (texObjNegX);
                                    skyBgnd->setRightTexture (texObjPosX);
                                    skyBgnd->setBottomTexture(texObjNegY);
                                    skyBgnd->setTopTexture   (texObjPosY);

                                    _vecSkyBgnd.push_back(std::make_pair(skybox_name, skyBgnd));
                                }
                            }
                        }
                    }
                }
                else if (fs::is_regular_file(iter->status()))
                {
                    const fs::path filePath = *iter;
                    std::string ext = filePath.extension().string();
                    boost::to_lower(ext);
                    if (ext == ".chdr")
                    {
                        std::string skybox_name = filePath.filename().stem().string();

                        OSG::SkyBackgroundRefPtr skyBgnd = OSG::SkyBackground::create();
                        OSG::ImageUnrecPtr image = OSG::ImageFileHandler::the()->read(filePath.string().c_str());
                        OSG::TextureObjChunkUnrecPtr texObj = OSG::TextureObjChunk::create();

                        texObj->setImage(image);
                        texObj->setInternalFormat(GL_RGB32F);
                        texObj->setWrapS(GL_CLAMP_TO_EDGE);
                        texObj->setWrapT(GL_CLAMP_TO_EDGE);

                        skyBgnd->setFrontTexture (texObj);
                        skyBgnd->setBackTexture  (texObj);
                        skyBgnd->setLeftTexture  (texObj);
                        skyBgnd->setRightTexture (texObj);
                        skyBgnd->setTopTexture   (texObj);
                        skyBgnd->setBottomTexture(texObj);

                        _vecSkyBgnd.push_back(std::make_pair(skybox_name, skyBgnd));
                    }
                }
            }
        }
    } catch (const fs::filesystem_error&) {}

    // load the first sky background if available
    if (!_vecSkyBgnd.empty())
        _skyBgnd_index = 0;
}

void Example::setupScene()
{
    // create a pretty simple graph: a Group with two Transforms as children,
    // each of which carries a single Geometry.

    // The hdr root node
    _hdrRoot = OSG::Node::create();
    _hdrRoot->setCore(OSG::Group::create());
   
    create_hdr_stage();

    OSG::NodeRefPtr root = OSG::Node::create();
    root->setCore(OSG::Group::create());

    _hdrRoot->addChild(root);

    // The scene
    OSG::NodeRefPtr scene = OSG::Node::create();

    // The geometry transformations: cylinder, torus and spheres
    for (std::size_t i = 0; i < num_geometries; ++i)
        _geom_trans[i] = OSG::Transform::create();

    // The cylinder
    OSG::NodeRefPtr     cyl    = OSG::Node::create();
    OSG::GeometryRefPtr cylGeo = OSG::makeCylinderGeo( 1.4f, .3f, 24, true, true, true );
        
    cyl->setCore(cylGeo);

    OSG::NodeRefPtr cylTransNode = OSG::Node::create();
    cylTransNode->setCore(_geom_trans[0]);
    cylTransNode->addChild(cyl);
        
    scene->addChild(cylTransNode);
        
    // The torus
    OSG::NodeRefPtr     torus    = OSG::Node::create();
    OSG::GeometryRefPtr torusGeo = OSG::makeTorusGeo( .2f, 1, 24, 36 );
        
    torus->setCore(torusGeo);
            
    OSG::NodeRefPtr torTransNode = OSG::Node::create();
    torTransNode->setCore(_geom_trans[1]);
    torTransNode->addChild(torus);
        
    scene->addChild(torTransNode);

    OSG::Matrix m;

#ifdef USE_MIRROR_SPHERE
    // The mirror sphere
    OSG::NodeRefPtr             mirrorSceneRoot = OSG::Node::create();
    OSG::VisitSubTreeRefPtr     visitSubTree    = OSG::VisitSubTree::create();

    mirrorSceneRoot->setCore(visitSubTree);
    visitSubTree->setSubTreeRoot(root);

    OSG::NodeRefPtr             mirrorRoot = OSG::Node::create();
    OSG::CubeMapGeneratorRefPtr cubeMapGen = OSG::CubeMapGenerator::create();

    cubeMapGen->setBackground(_solidBgnd);
    cubeMapGen->setRoot(mirrorSceneRoot);
    cubeMapGen->setTexUnit(3);
    cubeMapGen->setSize(512, 512);
    cubeMapGen->setTextureFormat(GL_RGB32F);

    mirrorRoot->setCore(cubeMapGen);

    OSG::NodeRefPtr     mirrorSphere    = OSG::Node::create();
    OSG::GeometryRefPtr mirrorSphereGeo = OSG::makeSphereGeo(3, 1.f);
        
    mirrorSphere->setCore(mirrorSphereGeo);

    m.setIdentity();
    m.setTranslate(OSG::Vec3f(0.3f*circle_radius, 0.3f*circle_radius, 0.3f*circle_radius));
    _geom_trans[2]->setMatrix(m);
            
    OSG::NodeRefPtr mirrorSphereTransNode = OSG::Node::create();
    mirrorSphereTransNode->setCore(_geom_trans[2]);
    mirrorSphereTransNode->addChild(mirrorRoot);

    mirrorRoot->addChild(mirrorSphere);
#endif // USE_MIRROR_SPHERE

    // The spheres
    OSG::GeometryRefPtr sphereGeo[num_geometries];
    for (std::size_t i = 3; i < num_geometries; ++i)
    {
        OSG::NodeRefPtr sphere    = OSG::Node::create();

        sphereGeo[i] = OSG::makeSphereGeo(3, 0.7f);
        
        sphere->setCore(sphereGeo[i]);

        OSG::Real32 theta = (i-3) * 2.f * OSG::Pi / (num_geometries - 3);

        m.setIdentity();
        m.setTranslate(OSG::Vec3f(circle_radius * OSG::osgCos(theta), 0.5f, circle_radius * OSG::osgSin(theta)));
        
        _geom_trans[i]->setMatrix(m);

        OSG::NodeRefPtr sphereTransNode = OSG::Node::create();
        sphereTransNode->setCore (_geom_trans[i]);
        sphereTransNode->addChild(sphere);
        
        // add it to the scene
        scene->addChild(sphereTransNode);
    }

    //
    // create the shader program
    //
    _prog_chunk = OSG::SimpleSHLChunk::create();

    _prog_chunk->setVertexProgram    (get_vp_program());
    _prog_chunk->setFragmentProgram  (get_fp_program());

    _prog_chunk->addUniformBlock("Materials", 1);    // block binding point
    _prog_chunk->addUniformBlock("Lights",    2);    // block binding point

    _prog_chunk->addUniformVariable("uRenderEmissive", _render_emissive);
    _prog_chunk->addUniformVariable("uRenderAmbient",  _render_ambient);
    _prog_chunk->addUniformVariable("uRenderDiffuse",  _render_diffuse);
    _prog_chunk->addUniformVariable("uRenderSpecular", _render_specular);

    //
    // create uniform buffer objects and corresponding materials
    //
    OSG::UniformBufferObjStd140ChunkRefPtr ubo_material_database = create_material_database_state(_materials);
                                          _ubo_light_state       = create_light_state(_lights);

    OSG::PolygonChunkRefPtr polygon_chunk = OSG::PolygonChunk::create();
    polygon_chunk->setFrontMode(GL_FILL);
    polygon_chunk->setBackMode(GL_FILL);
    polygon_chunk->setCullFace(GL_NONE);

    OSG::DepthChunkRefPtr depth_chunk = OSG::DepthChunk::create();
    depth_chunk->setEnable(true);

    OSG::ChunkMaterialRefPtr prog_state = OSG::ChunkMaterial::create();
    prog_state->addChunk( ubo_material_database, 1);  // buffer binding point 1
    prog_state->addChunk(_ubo_light_state,       2);  // buffer binding point 2
    prog_state->addChunk(_prog_chunk);
    prog_state->addChunk(polygon_chunk);
    prog_state->addChunk(depth_chunk);


    OSG::ShaderProgramVariableChunkRefPtr shader_var_chunk = OSG::ShaderProgramVariableChunk::create();
    shader_var_chunk->addUniformBlock("GeomState", 3);

    OSG::ChunkMaterialRefPtr geom_state[num_geometries];

    for (std::size_t i = 0; i < num_geometries; ++i)
    {
        if (i == 2) continue;   // do not do this for the mirror sphere
        GeomState geom; 
        geom.material_index = OSG::RandomPoolManager::the()->getRandomInt32(0, num_materials-1);

        geom_state[i] = OSG::ChunkMaterial::create();

        _ubo_geom_state[i] = create_geometry_material_state(geom);

        geom_state[i]->addChunk(_ubo_geom_state[i], 3);    // buffer binding point 3
        geom_state[i]->addChunk(shader_var_chunk);         // block binding point
    }

    cylGeo  ->setMaterial(geom_state[0]);
    torusGeo->setMaterial(geom_state[1]);

    for (std::size_t i = 3; i < num_geometries; ++i)
        sphereGeo[i]->setMaterial(geom_state[i]);

    OSG::MaterialChunkOverrideGroupRefPtr mgrp = OSG::MaterialChunkOverrideGroup::create();
    mgrp->setMaterial(prog_state);
    scene->setCore(mgrp);

    root->addChild(scene);
#ifdef USE_MIRROR_SPHERE
    root->addChild(mirrorSphereTransNode);
#endif // USE_MIRROR_SPHERE

    OSG::commitChanges();
    
    _mgr->setRoot(_hdrRoot);
}

int Example::setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 800);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshapeCB);
    glutDisplayFunc(displayCB);

    glutMouseFunc(mouseCB);
    glutMotionFunc(motionCB);
    glutPassiveMotionFunc(motionCB);
    glutKeyboardFunc(keyboardCB);
    glutSpecialFunc(specialCB);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwGLUTModifiersFunc(glutGetModifiers);
#endif

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(displayCB);

    return winid;
}

void Example::display()
{
    // light spot direction and light position must be provided in eye space
    update_light_state(_ubo_light_state, _lights);

    if (!_pause)
    {

        // create the matrix
        OSG::Matrix m;
        OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
        // set the transforms' matrices
        m.setTransform(OSG::Vec3f(0, 0, OSG::osgSin(t / 1000.f) * 1.5),
                       OSG::Quaternion( OSG::Vec3f (1, 0, 0), t / 500.f));

        _geom_trans[0]->setMatrix(m);
    
        m.setTransform(OSG::Vec3f(OSG::osgSin(t / 1000.f), 0, 0),
                       OSG::Quaternion( OSG::Vec3f (0, 0, 1), t / 1000.f));

        _geom_trans[1]->setMatrix(m);

        for (std::size_t i = 3; i < num_geometries; ++i)
        {
            OSG::Real32 theta = (i-3) * 2.f * OSG::Pi / (num_geometries - 3);

            OSG::Real32 rad = circle_radius + 0.3 * circle_radius * OSG::osgSin(t / 2000.f);

            m.setIdentity();
            m.setTranslate(OSG::Vec3f(rad * OSG::osgCos(theta), 0.5f, rad * OSG::osgSin(theta)));
            _geom_trans[i]->setMatrix(m);
        }
    }

    OSG::commitChanges();
    
    _mgr->redraw();
}

void Example::reshape(int w, int h)
{
    _mgr->resize(w, h);

#ifdef OSG_WITH_ANTTWEAKBAR
    TwWindowSize(w, h);
#endif

    glutPostRedisplay();
}

//
// react to mouse button presses
//
void Example::mouse(int button, int state, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventMouseButtonGLUT(button, state, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

//
// react to mouse motions with pressed buttons
//
void Example::motion(int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventMouseMotionGLUT(x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    _mgr->mouseMove(x, y);

    glutPostRedisplay();
}

//
// react to keys
//
void Example::keyboard(unsigned char k, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventKeyboardGLUT(k, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif

    switch(k)
    {
        case 27:    
        {
            // clean up global variables
            _mgr = NULL;

            _ubo_light_state = NULL;

            for (std::size_t i = 0; i < num_geometries; ++i)
            {
                _geom_trans[i]     = NULL;
                _ubo_geom_state[i] = NULL;
            }

            OSG::osgExit();
            exit(0);
        }
        break;

        case 'm':
        {
            for (std::size_t i = 0; i < num_geometries; ++i)
            {
                GeomState geom; 
                geom.material_index = OSG::RandomPoolManager::the()->getRandomInt32(0, num_materials-1);

                update_geometry_material_state(_ubo_geom_state[i], geom);
            }

            glutPostRedisplay();
        }
        break;

        case 's':
        {
            _mgr->setStatistics(!_mgr->getStatistics());
        }
        break;
    }
}

void Example::special(int key, int x, int y)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    if(TwEventSpecialGLUT(key, x, y))
    {
        glutPostRedisplay();
        return;
    }
#endif
}

void Example::tweakbar(OSG::DrawEnv* drawEnv)
{
#ifdef OSG_WITH_ANTTWEAKBAR
    //
    // Save the current state
    //
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    //
    // execute the actual callback wrapped by this class
    //
    TwDraw();

    //
    // Restore the state
    //
    glPopAttrib();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

//
// transform point from world space to eye space
//
OSG::Pnt3f Example::transform_to_eye_space(const OSG::Pnt3f& p, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
        return p;

    OSG::Viewport* pPort = _mgr->getWindow()->getPort(0);

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
OSG::Vec3f Example::transform_to_eye_space(const OSG::Vec3f& v, OSG::SimpleSceneManager* pSSM)
{
    if (!pSSM || !pSSM->getWindow() || pSSM->getWindow()->getMFPort()->size() == 0)
        return v;

    OSG::Viewport* pPort = _mgr->getWindow()->getPort(0);

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
std::size_t Example::calc_light_buffer_size(const VecLightsT& lights)
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

    ao *= lights.size();        bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> Example::create_light_buffer(const VecLightsT& lights)
{
    std::size_t size = calc_light_buffer_size(lights);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < lights.size(); ++i)
    {
        OSG::Pnt3f position_es       = transform_to_eye_space(lights[i].position,       _mgr);
        OSG::Vec3f spot_direction_es = transform_to_eye_space(lights[i].spot_direction, _mgr);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &position_es[0], sizeof(OSG::Pnt3f));
        bo = ao + sizeof(OSG::Pnt4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &spot_direction_es[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &lights[i].Ia[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &lights[i].Id[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &lights[i].Is[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &lights[i].attenuation[0], sizeof(OSG::Vec3f));
        bo = ao + sizeof(OSG::Vec4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = lights[i].spot_cos_cutoff;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = lights[i].spot_exponent;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Int32*>(&buffer[0] + ao)) = lights[i].type;
        bo = ao + sizeof(OSG::Int32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::UniformBufferObjStd140ChunkTransitPtr Example::create_light_state(const VecLightsT& lights)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_light_buffer(lights);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void Example::update_light_state(OSG::UniformBufferObjStd140Chunk* ubo, const VecLightsT& lights)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_light_buffer(lights);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

std::size_t Example::calc_material_database_buffer_size(const VecMaterialsT& materials)
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

    ao *= materials.size();     bo = ao;                        // array
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> Example::create_material_database_buffer(const VecMaterialsT& materials)
{
    std::size_t size = calc_material_database_buffer_size(materials);

    std::vector<OSG::UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < materials.size(); ++i)
    {
        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &materials[i].ambient[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &materials[i].diffuse[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &materials[i].specular[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset(16, bo);
        memcpy(&buffer[0] + ao, &materials[i].emissive[0], sizeof(OSG::Color3f));
        bo = ao + sizeof(OSG::Color4f);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = materials[i].opacity;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 4, bo);
        *(reinterpret_cast<OSG::Real32*>(&buffer[0] + ao)) = materials[i].shininess;
        bo = ao + sizeof(OSG::Real32);

        ao = align_offset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

OSG::UniformBufferObjStd140ChunkTransitPtr Example::create_material_database_state(const VecMaterialsT& materials)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_material_database_buffer(materials);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_STATIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void Example::update_material_database_state(OSG::UniformBufferObjStd140Chunk* ubo, const VecMaterialsT& materials)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_material_database_buffer(materials);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

//
// the geomertry uniform buffer object
//
std::size_t Example::calc_geometry_material_buffer_size()
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    ao = align_offset(  4, bo); bo = ao + sizeof(OSG::UInt32);  // OSG::UInt32  material_index;
    ao = align_offset( 16, bo); bo = ao;                        // padding

    return ao;
}

std::vector<OSG::UInt8> Example::create_geometry_material_buffer(const GeomState& geom_state)
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

OSG::UniformBufferObjStd140ChunkTransitPtr Example::create_geometry_material_state(const GeomState& geom_state)
{
    OSG::UniformBufferObjStd140ChunkRefPtr ubo = OSG::UniformBufferObjStd140Chunk::create();

    std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_DYNAMIC_DRAW);

    return OSG::UniformBufferObjStd140ChunkTransitPtr(ubo);
}

void Example::update_geometry_material_state(OSG::UniformBufferObjStd140Chunk* ubo, const GeomState& geom_state)
{
    if (ubo) {
        std::vector<OSG::UInt8> buffer = create_geometry_material_buffer(geom_state);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

void Example::create_hdr_stage()
{
    if (_hdrRoot)
    {
        _hdrStage = OSG::HDR2Stage::create();

        setup_hdr_stage();

        _hdrRoot->setCore(_hdrStage);
    }
}

void Example::setup_hdr_stage()
{
    if (_hdrStage)
    {
        _hdrStage->setApplyGamma                (_gamma);
        _hdrStage->setAccurateGamma             (_accurate_gamma);

        _hdrStage->setPerformBloom              (_perform_bloom);
        _hdrStage->setBloomBackground           (_bloom_background);

        _hdrStage->setForceBackground           (_force_bgnd);
        _hdrStage->setUse_ITU_R_BT_709          (_use_ITU_R_BT_709);
        _hdrStage->setMipmapLevel               (_mipmap_level);

        _hdrStage->setTarget                    (_result_index);
        _hdrStage->setCarryDepth                (_carry_depth);

        _hdrStage->setColorBufferInternalFormat (GL_RGBA16F);
        _hdrStage->setColorBufferPixelFormat    (GL_RGBA);
        _hdrStage->setColorBufferType           (GL_FLOAT);

        _hdrStage->setDepthBufferInternalFormat (GL_DEPTH24_STENCIL8);
        _hdrStage->setDepthBufferPixelFormat    (GL_DEPTH_STENCIL);
        _hdrStage->setDepthBufferType           (GL_UNSIGNED_INT_24_8);

        _hdrStage->setLumBufferInternalFormat   (GL_R32F);
        _hdrStage->setLumBufferPixelFormat      (GL_RED);
        _hdrStage->setLumBufferType             (GL_FLOAT);

        _hdrStage->setImageBufferInternalFormat (GL_RGB16F);
        _hdrStage->setImageBufferPixelFormat    (GL_RGB);
        _hdrStage->setImageBufferType           (GL_FLOAT);

        _hdrStage->setNumSamples                (_num_samples);

        _hdrStage->setBloomThreshold            (_hdrShaderData.bloomThreshold);
        _hdrStage->setBloomMagnitude            (_hdrShaderData.bloomMagnitude);
        _hdrStage->setToneMappingMode           (_hdrShaderData.toneMapTechnique);
        _hdrStage->setExposure                  (_hdrShaderData.exposure);
        _hdrStage->setKeyValue                  (_hdrShaderData.keyValue);
        _hdrStage->setAutoExposureMode          (_hdrShaderData.autoExposure);
        _hdrStage->setWhiteLevel                (_hdrShaderData.whiteLevel);
        _hdrStage->setFilmicShoulderStrenght    (_hdrShaderData.shoulderStrength);
        _hdrStage->setFilmicLinearStrength      (_hdrShaderData.linearStrength);
        _hdrStage->setFilmicLinearAngle         (_hdrShaderData.linearAngle);
        _hdrStage->setFilmicToeStrength         (_hdrShaderData.toeStrength);
        _hdrStage->setFilmicToeNumerator        (_hdrShaderData.toeNumerator);
        _hdrStage->setFilmicToeDenominator      (_hdrShaderData.toeDenominator);
        _hdrStage->setFilmicLinearWhite         (_hdrShaderData.linearWhite);
        _hdrStage->setSaturation                (_hdrShaderData.lumSaturation);
        _hdrStage->setDragoBias                 (_hdrShaderData.bias);
        _hdrStage->setTau                       (_hdrShaderData.tau);
        _hdrStage->setNumTaps                   (_hdrShaderData.nTaps);
        _hdrStage->setBlurGaussSigma            (_hdrShaderData.sigma);
        _hdrStage->setUseLinChromCorrection     (_hdrShaderData.useLinChromInterp);
    }
}

//
// Initialize GLUT & OpenSG and set up the scene
//
int main(int argc, char **argv)
{
    Example example(argc, argv);

    // GLUT main loop
    glutMainLoop();

#ifdef OSG_WITH_ANTTWEAKBAR
    TwTerminate();
#endif

    return 0;
}

/*---- Light Shader -------------------------------------------------------*/

#define SHADER_EOL  << std::endl <<

//
// vertex shader program.
//
std::string Example::get_vp_program()
{
    using namespace std;

    stringstream ost;

    ost << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "out vec3 vNormalES;        // eye space normal"
    << endl << "out vec3 vPositionES;      // eye space position"
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
std::string Example::get_fp_program()
{
    using namespace std;

    stringstream ost;

    ost << "#version 330 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_separate_shader_objects: enable"
    << endl << "#extension GL_ARB_uniform_buffer_object:   enable"
    << endl << ""
    << endl << "in vec3 vNormalES;         // eye space normal"
    << endl << "in vec3 vPositionES;       // eye space position"
    << endl << ""
    << endl << "uniform bool uRenderAmbient;"
    << endl << "uniform bool uRenderDiffuse;"
    << endl << "uniform bool uRenderSpecular;"
    << endl << "uniform bool uRenderEmissive;"
    << endl << ""
    << endl << "const int num_lights    =   1;"
    << endl << "const int num_materials = 100;"
    << endl << ""
    << endl << "const int directional_light = 0;"
    << endl << "const int point_light = 1;"
    << endl << "const int spot_light = 2;"
    << endl << "const int no_light = 3;"
    << endl << ""
    << endl << "struct Light"
    << endl << "{"
    << endl << "    vec4 position;          // in eye space"
    << endl << "    vec4 spot_direction;    // in eye space"
    << endl << ""
    << endl << "    vec4 Ia;                // ambient  max. Intensity"
    << endl << "    vec4 Id;                // diffuse  max. Intensity"
    << endl << "    vec4 Is;                // specular max. Intensity"
    << endl << ""
    << endl << "    vec4 attenuation;       // (constant, linear, quadratic) with constant >= 1 and linear,quadratic >= 0"
    << endl << "    "
    << endl << "    float spot_cos_cutoff;  // cosine cut of angle"
    << endl << ""
    << endl << "    float spot_exponent;    // [0-128]"
    << endl << "    int  type;              // directional_light, point_light, spot_light, no_light"
    << endl << "};"
    << endl << ""
    << endl << "layout (std140) uniform Lights"
    << endl << "{"
    << endl << "    Light light[num_lights];"
    << endl << "} lights;"
    << endl << ""
    << endl << "struct Material"
    << endl << "{"
    << endl << "    vec4 ambient;"
    << endl << "    vec4 diffuse;"
    << endl << "    vec4 specular;"
    << endl << "    vec4 emissive;"
    << endl << ""
    << endl << "    float opacity;"
    << endl << "    float shininess;"
    << endl << "};"
    << endl << ""
    << endl << "layout (std140) uniform Materials"
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
    << endl << "    vec3 l = -lights.light[i].spot_direction.xyz;    // we carry the directional light direction in the spot_direction slot"
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
    << endl << "    vec3 result = vec3(0);"
    << endl << ""
    << endl << "    if (uRenderEmissive) result += materials.material[j].emissive.rgb;"
    << endl << "    if (uRenderAmbient)  result += lights.light[i].Ia.rgb * materials.material[j].ambient.rgb;"
    << endl << "    if (uRenderDiffuse)  result += lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l;           // / PI"
    << endl << "    if (uRenderSpecular) result += lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf; // * (m+8)/(8*PI)"
    << endl << ""
    << endl << "    return result;"
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
    << endl << "    vec3  l = vec3(lights.light[i].position.xyz) - p;    // direction from surface to light position"
    << endl << "    float d = length(l);                                 // distance from surface to light source"
    << endl << "    l = normalize(l);                                    // normalized direction from surface to light position"
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
    << endl << "    vec3 result = vec3(0);"
    << endl << ""
    << endl << "    if (uRenderEmissive) result += materials.material[j].emissive.rgb;"
    << endl << "    if (uRenderAmbient)  result += lights.light[i].Ia.rgb * materials.material[j].ambient.rgb;"
    << endl << "    if (uRenderDiffuse)  result += lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l;           // / PI"
    << endl << "    if (uRenderSpecular) result += lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf; // * (m+8)/(8*PI)"
    << endl << ""
    << endl << "    return result;"
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
    << endl << "    vec3  l = vec3(lights.light[i].position.xyz) - p;   // direction from surface to light position"
    << endl << "    float d = length(l);                                // distance from surface to light source"
    << endl << "    l = normalize(l);                                   // normalized direction from surface to light position"
    << endl << "    "
    << endl << "    vec3 s = lights.light[i].spot_direction.xyz;        // spot direction"
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
    << endl << "    vec3 result = vec3(0);"
    << endl << ""
    << endl << "    if (uRenderEmissive) result += materials.material[j].emissive.rgb;"
    << endl << "    if (uRenderAmbient)  result += lights.light[i].Ia.rgb * materials.material[j].ambient.rgb;"
    << endl << "    if (uRenderDiffuse)  result += lights.light[i].Id.rgb * materials.material[j].diffuse.rgb  * n_dot_l;           // / PI"
    << endl << "    if (uRenderSpecular) result += lights.light[i].Is.rgb * materials.material[j].specular.rgb * (m+8)*0.0125 * pf; // * (m+8)/(8*PI)"
    << endl << ""
    << endl << "    return result;"
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

/*---- Light --------------------------------------------------------------*/

Light::Light() 
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

Light Light::create_light(Type e)
{
    Light l;
    l.type = e;

    switch (e) {
        case directional_light:
            l.spot_direction = OSG::Vec3f(1.f, 0.f, 0.f);
            break;
        case point_light:
            l.position = OSG::Pnt3f(0.f, 0.2f, 0.f);
            break;
        case spot_light:
            l.position = OSG::Pnt3f(0.f, 0.2f, 0.f); l.spot_direction = OSG::Pnt3f(0.f, 0.f, 0.f) - l.position;
            break;
        default:
            break;
    }
    return l;
}

/*---- Material -----------------------------------------------------------*/

Material::Material()
: ambient (0.f, 0.f, 0.f)
, diffuse (0.f, 0.f, 0.f)
, specular(0.f, 0.f, 0.f)
, emissive(0.f, 0.f, 0.f)
, opacity(1.f)
, shininess(100.f)
{}

VecMaterialsT initialize_materials(std::size_t num) // helper to create materials
{
    VecMaterialsT materials;

    for (std::size_t i = 0; i < num; ++i)
    {
        Material m;

        OSG::Real32 specular = OSG::RandomPoolManager::the()->getRandomReal32(0.5f, 1.f);

        m.diffuse.setRandom();
        m.ambient   = 0.2f * m.diffuse;
        m.specular  = OSG::Color3f(specular, specular, specular);
        m.emissive  = OSG::RandomPoolManager::the()->getRandomReal32(0.1f, 1.f) * m.diffuse;
        m.opacity   = 1.f;
        m.shininess = OSG::RandomPoolManager::the()->getRandomReal32(30.f, 300.f);

        materials.push_back(m);
    }

    return materials;
}

/*---- GeomState ----------------------------------------------------------*/

GeomState::GeomState()
: material_index(0)
{}

/*---- HDRShaderData ------------------------------------------------------*/

HDRShaderData::HDRShaderData()
: bloomThreshold(2.0f)
, bloomMagnitude(0.0f)
, toneMapTechnique(4)
, exposure(0.0f)
, keyValue(0.18f)
, autoExposure(2)
, whiteLevel(5.0f)
, shoulderStrength(0.15f)
, linearStrength(0.5f)
, linearAngle(0.1f)
, toeStrength(0.2f)
, toeNumerator(0.02f)
, toeDenominator(0.3f)
, linearWhite(11.2f)
, lumSaturation(1.0f)
, bias(0.85f)
, tau(1.25f)
, nTaps(4)
, sigma(0.8f)
, useLinChromInterp(true)
{}

HDRShaderData::HDRShaderData(const HDRShaderData& rhs)
: bloomThreshold(rhs.bloomThreshold)
, bloomMagnitude(rhs.bloomMagnitude)
, toneMapTechnique(rhs.toneMapTechnique)
, exposure(rhs.exposure)
, keyValue(rhs.keyValue)
, autoExposure(rhs.autoExposure)
, whiteLevel(rhs.whiteLevel)
, shoulderStrength(rhs.shoulderStrength)
, linearStrength(rhs.linearStrength)
, linearAngle(rhs.linearAngle)
, toeStrength(rhs.toeStrength)
, toeNumerator(rhs.toeNumerator)
, toeDenominator(rhs.toeDenominator)
, linearWhite(rhs.linearWhite)
, lumSaturation(rhs.lumSaturation)
, bias(rhs.bias)
, tau(rhs.tau)
, nTaps(rhs.nTaps)
, sigma(rhs.sigma)
, useLinChromInterp(rhs.useLinChromInterp)
{}

HDRShaderData& HDRShaderData::operator=(const HDRShaderData& rhs)
{
    if (&rhs == this) return *this;

    bloomThreshold = rhs.bloomThreshold;
    bloomMagnitude = rhs.bloomMagnitude;
    toneMapTechnique = rhs.toneMapTechnique;
    exposure = rhs.exposure;
    keyValue = rhs.keyValue;
    autoExposure = rhs.autoExposure;
    whiteLevel = rhs.whiteLevel;
    shoulderStrength = rhs.shoulderStrength;
    linearStrength = rhs.linearStrength;
    linearAngle = rhs.linearAngle;
    toeStrength = rhs.toeStrength;
    toeNumerator = rhs.toeNumerator;
    toeDenominator = rhs.toeDenominator;
    linearWhite = rhs.linearWhite;
    lumSaturation = rhs.lumSaturation;
    bias = rhs.bias;
    tau = rhs.tau;
    nTaps = rhs.nTaps;
    sigma = rhs.sigma;
    useLinChromInterp = rhs.useLinChromInterp;

    return *this;
}

HDRShaderData HDRShaderData::create_min_shader_data()
{
    HDRShaderData data;

    data.bloomThreshold = 0.0;
    data.bloomMagnitude = 0.0;
    data.toneMapTechnique = 0;
    data.exposure = -10.0;
    data.keyValue = 0.0;
    data.autoExposure = 0;
    data.whiteLevel = 0.0;
    data.shoulderStrength = 0.0;
    data.linearStrength = 0.0;
    data.linearAngle = 0.0;
    data.toeStrength = 0.0;
    data.toeNumerator = 0.0;
    data.toeDenominator = 0.0;
    data.linearWhite = 0.0;
    data.lumSaturation = 0.0;
    data.bias = 0.0;
    data.tau = 0.0;
    data.nTaps = 2;
    data.sigma = 0.5;

    return data;
}

HDRShaderData HDRShaderData::create_max_shader_data()
{
    HDRShaderData data;

    data.bloomThreshold = 10.0;
    data.bloomMagnitude = 2.0;
    data.toneMapTechnique = 7;
    data.exposure = 10.0;
    data.keyValue = 1.0;
    data.autoExposure = 2;
    data.whiteLevel = 25.0;
    data.shoulderStrength = 2.0;
    data.linearStrength = 5.0;
    data.linearAngle = 1.0;
    data.toeStrength = 2.0;
    data.toeNumerator = 0.5;
    data.toeDenominator = 2.0;
    data.linearWhite = 20.0;
    data.lumSaturation = 4.0;
    data.bias = 1.0;
    data.tau = 40.0;
    data.nTaps = 10;
    data.sigma = 1.5;

    return data;
}

/*---- AntTweakBar --------------------------------------------------------*/

#ifdef OSG_WITH_ANTTWEAKBAR

std::string sGenTwDefinition(float vMin, float vMax, float steps, int precision, const char* keyinc, const char* keydec, const char* msg, const char* grp = NULL)
{
    std::string result;
    std::stringstream stream;

    stream << "min=" << vMin << " "
           << "max=" << vMax << " "
           << "step=" << (vMax - vMin)/steps << " "
           << "precision=" << precision << " "
           << "keyIncr=" << keyinc << " "
           << "keyDecr=" << keydec << " "
           << "help='" << msg << "'";

    if (grp)
        stream << " " << "group=" << grp;

    result = stream.str();

    return result;
}

std::string sGenTwDefinition(int vMin, int vMax, int delta, const char* keyinc, const char* keydec, const char* msg, const char* grp = NULL)
{
    std::string result;
    std::stringstream stream;

    stream << "min=" << vMin << " "
           << "max=" << vMax << " "
           << "step=" << delta << " "
           << "keyIncr=" << keyinc << " "
           << "keyDecr=" << keydec << " "
           << "help='" << msg << "'";

    if (grp)
        stream << " " << "group=" << grp;

    result = stream.str();

    return result;
}

void TW_CALL ResetParametersCB(void *clientData)
{ 
    Example* example = reinterpret_cast<Example*>(clientData);
    example->ResetParameters();
}

void TW_CALL SetSampleNumberCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetSampleNumber(*num);
}

void TW_CALL GetSampleNumberCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetSampleNumber();
}

void TW_CALL SetClearColorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const OSG::Color3f* num = reinterpret_cast<const OSG::Color3f*>(value);
    example->SetClearColor(*num);
}

void TW_CALL GetClearColorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    OSG::Color3f* num = reinterpret_cast<OSG::Color3f*>(value);
    *num = example->GetClearColor();
}

void TW_CALL SetForceBgndCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetForceBgnd(*num);
}

void TW_CALL GetForceBgndCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetForceBgnd();
}

void TW_CALL SetAjustLuminanceCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetAjustLuminance(*num);
}

void TW_CALL GetAjustLuminanceCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetAjustLuminance();
}
void TW_CALL SetSkyBgndIndexCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetSkyBgndIndex(*num);
}

void TW_CALL GetSkyBgndIndexCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetSkyBgndIndex();
}

void TW_CALL SetPerformBloomCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetPerformBloom(*num);
}

void TW_CALL GetPerformBloomCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetPerformBloom();
}

void TW_CALL SetBloomBackgroundCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetBloomBackground(*num);
}

void TW_CALL GetBloomBackgroundCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetBloomBackground();
}

void TW_CALL SetCarryDepthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetCarryDepth(*num);
}

void TW_CALL GetCarryDepthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetCarryDepth();
}

void TW_CALL SetResultIndexCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetResultIndex(*num);
}

void TW_CALL GetResultIndexCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetResultIndex();
}

void TW_CALL SetRenderEmissiveCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderEmissive(*num);
}

void TW_CALL GetRenderEmissiveCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderEmissive();
}

void TW_CALL SetRenderAmbientCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderAmbient(*num);
}

void TW_CALL GetRenderAmbientCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderAmbient();
}

void TW_CALL SetRenderDiffuseCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderDiffuse(*num);
}

void TW_CALL GetRenderDiffuseCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderDiffuse();
}

void TW_CALL SetRenderSpecularCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetRenderSpecular(*num);
}

void TW_CALL GetRenderSpecularCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetRenderSpecular();
}

void TW_CALL SetAccurateGammaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetAccurateGamma(*num);
}

void TW_CALL GetAccurateGammaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetAccurateGamma();
}

void TW_CALL SetGammaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetGamma(*num);
}

void TW_CALL GetGammaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetGamma();
}

void TW_CALL SetUseITURBT709CB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetUseITURBT709(*num);
}

void TW_CALL GetUseITURBT709CB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetUseITURBT709();
}

void TW_CALL SetMipmapLevelCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetMipmapLevel(*num);
}

void TW_CALL GetMipmapLevelCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetMipmapLevel();
}

void TW_CALL SetBloomThresholdCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBloomThreshold(*num);
}

void TW_CALL GetBloomThresholdCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBloomThreshold();
}

void TW_CALL SetBloomMagnitudeCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBloomMagnitude(*num);
}

void TW_CALL GetBloomMagnitudeCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBloomMagnitude();
}

void TW_CALL SetToneMapTechniqueCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetToneMapTechnique(*num);
}

void TW_CALL GetToneMapTechniqueCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetToneMapTechnique();
}

void TW_CALL SetExposureCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetExposure(*num);
}

void TW_CALL GetExposureCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetExposure();
}

void TW_CALL SetKeyValueCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetKeyValue(*num);
}

void TW_CALL GetKeyValueCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetKeyValue();
}

void TW_CALL SetAutoExposureCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetAutoExposure(*num);
}

void TW_CALL GetAutoExposureCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetAutoExposure();
}

void TW_CALL SetWhiteLevelCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetWhiteLevel(*num);
}

void TW_CALL GetWhiteLevelCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetWhiteLevel();
}

void TW_CALL SetShoulderStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetShoulderStrength(*num);
}

void TW_CALL GetShoulderStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetShoulderStrength();
}

void TW_CALL SetLinearStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearStrength(*num);
}

void TW_CALL GetLinearStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearStrength();
}

void TW_CALL SetLinearAngleCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearAngle(*num);
}

void TW_CALL GetLinearAngleCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearAngle();
}

void TW_CALL SetToeStrengthCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeStrength(*num);
}

void TW_CALL GetToeStrengthCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeStrength();
}

void TW_CALL SetToeNumeratorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeNumerator(*num);
}

void TW_CALL GetToeNumeratorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeNumerator();
}

void TW_CALL SetToeDenominatorCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetToeDenominator(*num);
}

void TW_CALL GetToeDenominatorCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetToeDenominator();
}

void TW_CALL SetLinearWhiteCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLinearWhite(*num);
}

void TW_CALL GetLinearWhiteCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLinearWhite();
}

void TW_CALL SetLumSaturationCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetLumSaturation(*num);
}

void TW_CALL GetLumSaturationCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetLumSaturation();
}

void TW_CALL SetBiasCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetBias(*num);
}

void TW_CALL GetBiasCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetBias();
}

void TW_CALL SetTauCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetTau(*num);
}

void TW_CALL GetTauCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetTau();
}

void TW_CALL SetNTapsCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const int* num = reinterpret_cast<const int*>(value);
    example->SetNTaps(*num);
}

void TW_CALL GetNTapsCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    int* num = reinterpret_cast<int*>(value);
    *num = example->GetNTaps();
}

void TW_CALL SetSigmaCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const float* num = reinterpret_cast<const float*>(value);
    example->SetSigma(*num);
}

void TW_CALL GetSigmaCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    float* num = reinterpret_cast<float*>(value);
    *num = example->GetSigma();
}

void TW_CALL SetUseLinChromInterpCB(const void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    const bool* num = reinterpret_cast<const bool*>(value);
    example->SetUseLinChromInterp(*num);
}

void TW_CALL GetUseLinChromInterpCB(void *value, void *clientData)
{
    Example* example = reinterpret_cast<Example*>(clientData);
    bool* num = reinterpret_cast<bool*>(value);
    *num = example->GetUseLinChromInterp();
}

void Example::ResetParameters()
{
    _hdrShaderData = _hdrShaderDataDefault;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

void Example::SetSampleNumber(int value)
{
    if (value < _num_samples)
    {
        switch (_num_samples)
        {
            case 0:
                break;
            case 4:
                _num_samples = 0;
                break;
            case 8:
                _num_samples = 4;
                break;
            case 16:
                _num_samples = 8;
                break;
            case 32:
                _num_samples = 16;
                break;
        }
    }
    else if (value > _num_samples)
    {
        switch (_num_samples)
        {
            case 0:
                _num_samples = 4;
                break;
            case 4:
                _num_samples = 8;
                break;
            case 8:
                _num_samples = 16;
                break;
            case 16:
                _num_samples = 32;
                break;
            case 32:
                break;
        }
    }

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

int Example::GetSampleNumber() const
{
    return _num_samples;
}

void Example::SetClearColor(const OSG::Color3f& value)
{
    _clear_color = value;

    _solidBgnd->setColor(_clear_color);

    glutPostRedisplay();
}

const OSG::Color3f& Example::GetClearColor() const
{
    return _clear_color;
}

void Example::SetForceBgnd(bool value)
{
    _force_bgnd = value;

    if (_hdrStage)
    _hdrStage->setForceBackground(_force_bgnd);

    glutPostRedisplay();
}

bool Example::GetForceBgnd() const
{
    return _force_bgnd;
}

void Example::SetAjustLuminance(bool value)
{
    _adjust_luminance = value;

    if (_hdrStage)
    _hdrStage->setAdjustLuminance(_adjust_luminance);

    glutPostRedisplay();
}

bool Example::GetAjustLuminance() const
{
    return _adjust_luminance;
}

void Example::SetPerformBloom(bool value)
{
    _perform_bloom = value;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

bool Example::GetPerformBloom() const
{
    return _perform_bloom;
}

void Example::SetBloomBackground(bool value)
{
    _bloom_background = value;

    if (_hdrStage)
        _hdrStage->setBloomBackground(_bloom_background);

    glutPostRedisplay();
}

bool Example::GetBloomBackground() const
{
    return _bloom_background;
}

void Example::SetCarryDepth(bool value)
{
    _carry_depth = value;

    if (_hdrStage)
        create_hdr_stage();

    glutPostRedisplay();
}

bool Example::GetCarryDepth() const
{
    return _carry_depth;
}

void Example::SetSkyBgndIndex(int value)
{
    if (_skyBgnd_index != value)
    {
        _skyBgnd_index = value;

        if (_skyBgnd_index < 0)
            _mgr->setBackground(_solidBgnd);
        else if (_skyBgnd_index < _vecSkyBgnd.size())
            _mgr->setBackground(_vecSkyBgnd[_skyBgnd_index].second);

        glutPostRedisplay();
    }
}

int Example::GetSkyBgndIndex() const
{
    return _skyBgnd_index;
}

void Example::SetResultIndex(int value)
{
    if (_result_index != value)
    {
        _result_index = value;

        if (_hdrStage)
            _hdrStage->setTarget(_result_index);

        glutPostRedisplay();
    }
}

int Example::GetResultIndex() const
{
    return _result_index;
}

void Example::SetRenderEmissive(bool value)
{
    _render_emissive = value;
    _prog_chunk->updateUniformVariable("uRenderEmissive", _render_emissive);
    glutPostRedisplay();
}

bool Example::GetRenderEmissive() const
{
    return _render_emissive;
}

void Example::SetRenderAmbient(bool value)
{
    _render_ambient = value;
    _prog_chunk->updateUniformVariable("uRenderAmbient",  _render_ambient);
    glutPostRedisplay();
}

bool Example::GetRenderAmbient() const
{
    return _render_ambient;
}

void Example::SetRenderDiffuse(bool value)
{
    _render_diffuse = value;
    _prog_chunk->updateUniformVariable("uRenderDiffuse",  _render_diffuse);
    glutPostRedisplay();
}

bool Example::GetRenderDiffuse() const
{
    return _render_diffuse;
}

void Example::SetRenderSpecular(bool value)
{
    _render_specular = value;
    _prog_chunk->updateUniformVariable("uRenderSpecular", _render_specular);
    glutPostRedisplay();
}

bool Example::GetRenderSpecular() const
{
    return _render_specular;
}

void Example::SetAccurateGamma(bool value)
{
    _accurate_gamma = value;

    if (_hdrStage)
        _hdrStage->setAccurateGamma(_accurate_gamma);

    glutPostRedisplay();
}

bool Example::GetAccurateGamma() const
{
    return _accurate_gamma;
}

void Example::SetGamma(bool value)
{
    _gamma = value;

    if (_hdrStage)
        _hdrStage->setApplyGamma(_gamma);

    glutPostRedisplay();
}

bool Example::GetGamma() const
{
    return _gamma;
}

void Example::SetUseITURBT709(bool value)
{
    _use_ITU_R_BT_709 = value;

    if (_hdrStage)
        _hdrStage->setUse_ITU_R_BT_709(_use_ITU_R_BT_709);

    glutPostRedisplay();
}

bool Example::GetUseITURBT709() const
{
    return _use_ITU_R_BT_709;
}

void Example::SetMipmapLevel(int value)
{
    _mipmap_level = value;

    if (_hdrStage)
        _hdrStage->setMipmapLevel(_mipmap_level);

    glutPostRedisplay();
}

int Example::GetMipmapLevel() const
{
    return _mipmap_level;
}

void Example::SetBloomThreshold(float value)
{
    _hdrShaderData.bloomThreshold = value;

    if (_hdrStage)
        _hdrStage->setBloomThreshold(_hdrShaderData.bloomThreshold);

    glutPostRedisplay();
}

float Example::GetBloomThreshold() const
{
    return _hdrShaderData.bloomThreshold;
}

void Example::SetBloomMagnitude(float value)
{
    _hdrShaderData.bloomMagnitude = value;

    if (_hdrStage)
        _hdrStage->setBloomMagnitude(_hdrShaderData.bloomMagnitude);

    glutPostRedisplay();
}

float Example::GetBloomMagnitude() const
{
    return _hdrShaderData.bloomMagnitude;
}

void Example::SetToneMapTechnique(int value)
{
    _hdrShaderData.toneMapTechnique = value;

    if (_hdrStage)
        _hdrStage->setToneMappingMode(_hdrShaderData.toneMapTechnique);

    glutPostRedisplay();
}

int Example::GetToneMapTechnique() const
{
    return _hdrShaderData.toneMapTechnique;
}

void Example::SetExposure(float value)
{
    _hdrShaderData.exposure = value;

    if (_hdrStage)
        _hdrStage->setExposure(_hdrShaderData.exposure);

    glutPostRedisplay();
}

float Example::GetExposure() const
{
    return _hdrShaderData.exposure;
}

void Example::SetKeyValue(float value)
{
    _hdrShaderData.keyValue = value;

    if (_hdrStage)
        _hdrStage->setKeyValue(_hdrShaderData.keyValue);

    glutPostRedisplay();
}

float Example::GetKeyValue() const
{
    return _hdrShaderData.keyValue;
}

void Example::SetAutoExposure(int value)
{
    _hdrShaderData.autoExposure = value;

    if (_hdrStage)
        _hdrStage->setAutoExposureMode(_hdrShaderData.autoExposure);

    glutPostRedisplay();
}

int Example::GetAutoExposure() const
{
    return _hdrShaderData.autoExposure;
}

void Example::SetWhiteLevel(float value)
{
    _hdrShaderData.whiteLevel = value;

    if (_hdrStage)
        _hdrStage->setWhiteLevel(_hdrShaderData.whiteLevel);

    glutPostRedisplay();
}

float Example::GetWhiteLevel() const
{
    return _hdrShaderData.whiteLevel;
}

void Example::SetShoulderStrength(float value)
{
    _hdrShaderData.shoulderStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicShoulderStrenght(_hdrShaderData.shoulderStrength);

    glutPostRedisplay();
}

float Example::GetShoulderStrength() const
{
    return _hdrShaderData.shoulderStrength;
}

void Example::SetLinearStrength(float value)
{
    _hdrShaderData.linearStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearStrength(_hdrShaderData.linearStrength);

    glutPostRedisplay();
}

float Example::GetLinearStrength() const
{
    return _hdrShaderData.linearStrength;
}

void Example::SetLinearAngle(float value)
{
    _hdrShaderData.linearAngle = value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearAngle(_hdrShaderData.linearAngle);

    glutPostRedisplay();
}

float Example::GetLinearAngle() const
{
    return _hdrShaderData.linearAngle;
}

void Example::SetToeStrength(float value)
{
    _hdrShaderData.toeStrength = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeStrength(_hdrShaderData.toeStrength);

    glutPostRedisplay();
}

float Example::GetToeStrength() const
{
    return _hdrShaderData.toeStrength;
}

void Example::SetToeNumerator(float value)
{
    _hdrShaderData.toeNumerator = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeNumerator(_hdrShaderData.toeNumerator);

    glutPostRedisplay();
}

float Example::GetToeNumerator() const
{
    return _hdrShaderData.toeNumerator;
}

void Example::SetToeDenominator(float value)
{
    _hdrShaderData.toeDenominator = value;

    if (_hdrStage)
        _hdrStage->setFilmicToeDenominator(_hdrShaderData.toeDenominator);

    glutPostRedisplay();
}

float Example::GetToeDenominator() const
{
    return _hdrShaderData.toeDenominator;
}

void Example::SetLinearWhite(float value)
{
    _hdrShaderData.linearWhite =  value;

    if (_hdrStage)
        _hdrStage->setFilmicLinearWhite(_hdrShaderData.linearWhite);

    glutPostRedisplay();
}

float Example::GetLinearWhite() const
{
    return _hdrShaderData.linearWhite;
}

void Example::SetLumSaturation(float value)
{
    _hdrShaderData.lumSaturation = value;

    if (_hdrStage)
        _hdrStage->setSaturation(_hdrShaderData.lumSaturation);

    glutPostRedisplay();
}

float Example::GetLumSaturation() const
{
    return _hdrShaderData.lumSaturation;
}

void Example::SetBias(float value)
{
    _hdrShaderData.bias = value;

    if (_hdrStage)
        _hdrStage->setDragoBias(_hdrShaderData.bias);

    glutPostRedisplay();
}

float Example::GetBias() const
{
    return _hdrShaderData.bias;
}

void Example::SetTau(float value)
{
    _hdrShaderData.tau = value;

    if (_hdrStage)
        _hdrStage->setTau(_hdrShaderData.tau);

    glutPostRedisplay();
}

float Example::GetTau() const
{
    return _hdrShaderData.tau;
}

void Example::SetNTaps(int value)
{
    _hdrShaderData.nTaps = value;

    if (_hdrStage)
        _hdrStage->setNumTaps(_hdrShaderData.nTaps);

    glutPostRedisplay();
}

int Example::GetNTaps() const
{
    return _hdrShaderData.nTaps;
}

void Example::SetSigma(float value)
{
    _hdrShaderData.sigma = value;

    if (_hdrStage)
        _hdrStage->setBlurGaussSigma(_hdrShaderData.sigma);

    glutPostRedisplay();
}

float Example::GetSigma() const
{
    return _hdrShaderData.sigma;
}

void Example::SetUseLinChromInterp(bool value)
{
    _hdrShaderData.useLinChromInterp = value;

    if (_hdrStage)
        _hdrStage->setUseLinChromCorrection(_hdrShaderData.useLinChromInterp);

    glutPostRedisplay();
}

bool Example::GetUseLinChromInterp() const
{
    return _hdrShaderData.useLinChromInterp;
}

void Example::setupTweakBar()
{
    if (_tweakbar) return;

    _tweakbar = TwNewBar("TweakBar");

    TwDefine(" GLOBAL help='This example is about tone mapping in OpenSG.' ");
    TwDefine(" TweakBar size='350 700' color='96 216 224' valueswidth=170");

    //
    // Global group
    //
    TwAddButton(_tweakbar, "Reset Parameters", ResetParametersCB, this, "key=r     help='Reset all  parameters back to default values'");
    TwAddVarRW(_tweakbar, "Pause Animation", TW_TYPE_BOOLCPP, &_pause,  "key=SPACE help='Pause animation'");
    TwAddVarCB(_tweakbar, "Carry Depth",     TW_TYPE_BOOLCPP, SetCarryDepthCB, GetCarryDepthCB, this,  "help='Carry depth buffer to final render target'");

    //
    // Group 'Luminance Adaption'
    //
    TwAddVarCB(_tweakbar, "Adjust Luminance", TW_TYPE_BOOLCPP, SetAjustLuminanceCB, GetAjustLuminanceCB, this,  "help='Toggle Luminance time dependent adjustment.' group='Luminance Adaption'");
    TwAddVarCB(_tweakbar, "Tau",              TW_TYPE_FLOAT,   SetTauCB, GetTauCB, this, sGenTwDefinition(_hdrShaderDataMin.tau, _hdrShaderDataMax.tau, 100, 2, "a", "A", "Luminance (eye) adaption time parameter.", "'Luminance Adaption'").c_str());

    //
    // Group 'Gamma Correction'
    //
    TwAddVarCB(_tweakbar, "Gamma",        TW_TYPE_BOOLCPP, SetGammaCB, GetGammaCB, this,          "key=g help='Apply Gamma correction at the end of the pipeline.' group='Gamma Correction'");
    TwAddVarCB(_tweakbar, "Accurate",     TW_TYPE_BOOLCPP, SetAccurateGammaCB, GetAccurateGammaCB, this, "key=G help='Use accurate Gamma to linear mapping.' group='Gamma Correction'");

    //
    // Group 'Bloom'
    //
    TwAddVarCB(_tweakbar, "Bloom Pass",      TW_TYPE_BOOLCPP, SetPerformBloomCB,    GetPerformBloomCB,    this, "help='Perform Bloom pass.' group=Bloom");
    TwAddVarCB(_tweakbar, "Bloom Background",TW_TYPE_BOOLCPP, SetBloomBackgroundCB, GetBloomBackgroundCB, this, "help='Perform Bloom pass.' group=Bloom");
    TwAddVarCB(_tweakbar, "Threshold",       TW_TYPE_FLOAT,   SetBloomThresholdCB,  GetBloomThresholdCB,  this, sGenTwDefinition(_hdrShaderDataMin.bloomThreshold, _hdrShaderDataMax.bloomThreshold, 100, 2, "t", "T", "Used by function CalcExposedColor of the Threshold shader: exposure -= bloomThreshold", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Magnitude",       TW_TYPE_FLOAT,   SetBloomMagnitudeCB,  GetBloomMagnitudeCB,  this, sGenTwDefinition(_hdrShaderDataMin.bloomMagnitude, _hdrShaderDataMax.bloomMagnitude, 100, 2, "u", "U", "Used by function main of the Composite shader: bloom *= bloomMagnitude", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Taps",            TW_TYPE_INT32,   SetNTapsCB,           GetNTapsCB,           this, sGenTwDefinition(_hdrShaderDataMin.nTaps, _hdrShaderDataMax.nTaps, 1, "p", "P", "Number if tap iterations used in the Bloom Blur shader.", "Bloom").c_str());
    TwAddVarCB(_tweakbar, "Sigma",           TW_TYPE_FLOAT,   SetSigmaCB,           GetSigmaCB,           this, sGenTwDefinition(_hdrShaderDataMin.sigma, _hdrShaderDataMax.sigma, 100, 2, "f", "F", "Used by function CalcGaussianWeight of the Blur shader.", "Bloom").c_str());

    //
    // Group 'Tonemapping'
    //
    TwAddVarCB(_tweakbar, "Luminance ITU-R-BT.709", TW_TYPE_BOOLCPP, SetUseITURBT709CB, GetUseITURBT709CB, this, "help='Calculate relative luminance according to ITU-R-BT.709.' group=Tonemapping");
    TwAddVarCB(_tweakbar, "Mipmap Level",           TW_TYPE_INT32,   SetMipmapLevelCB,  GetMipmapLevelCB,  this, sGenTwDefinition(-1, 12, 1, "z", "Z", "The Mipmap Level addresses the texture to be used for avg. luminance lookup. See Exposure render texture. Default is -1.", "Tonemapping").c_str());

    TwEnumVal toneMappingEnums[] = { {0, "None"}, {1, "Logarithmic"}, {2, "Exponential"}, {3, "Drago Logarithmic"}, {4, "Reinhard"}, {5, "Reinhard Modified"}, {6, "Filmic Hable"}, {7, "Filmic Uncharte2D"} };
    TwType toneMappingType = TwDefineEnum("ToneMappingType", toneMappingEnums, 8);
    TwAddVarCB(_tweakbar, "Technique", toneMappingType, SetToneMapTechniqueCB, GetToneMapTechniqueCB, this, "help='The tone mapping algorithm.' group=Tonemapping");

    TwEnumVal autoExposureEnums[] = { {0, "Manual"}, {1, "Geom. mean of lumi. (KeyValue)"}, {2, "Geom. mean of lumi. (Auto KeyValue)"} };
    TwType autoExposureType = TwDefineEnum("AutoExposureType", autoExposureEnums, 3);
    TwAddVarCB(_tweakbar, "AutoExposure", autoExposureType, SetAutoExposureCB, GetAutoExposureCB, this, "help='Algorithm to determine the exposure value.' group=Tonemapping");

    TwAddVarCB(_tweakbar, "Exposure",           TW_TYPE_FLOAT,   SetExposureCB, GetExposureCB, this,      sGenTwDefinition(_hdrShaderDataMin.exposure,      _hdrShaderDataMax.exposure,      100, 2, "e", "E", "Manual exposure: The HDR pixel value is then scaled by 2^exposure.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "KeyValue",           TW_TYPE_FLOAT,   SetKeyValueCB, GetKeyValueCB, this,      sGenTwDefinition(_hdrShaderDataMin.keyValue,      _hdrShaderDataMax.keyValue,      100, 2, "k", "K", "Used in the geometric mean calculation of the luminance. a \"key value\" is user-controlled, and is meant to be chosen based on whether the scene is \"high-key\" (bright, low contrast) or \"low-key\" (dark, high contrast).", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "White Level",        TW_TYPE_FLOAT,   SetWhiteLevelCB, GetWhiteLevelCB, this,    sGenTwDefinition(_hdrShaderDataMin.whiteLevel,    _hdrShaderDataMax.whiteLevel,  10000, 4, "w", "W", "Sets what pixels are pure white in the image, producing a result similar to how exposure functions in a camera.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "Saturation",         TW_TYPE_FLOAT,   SetLumSaturationCB, GetLumSaturationCB, this, sGenTwDefinition(_hdrShaderDataMin.lumSaturation, _hdrShaderDataMax.lumSaturation, 100, 2, "l", "L", "Luminance saturation.", "Tonemapping").c_str());
    TwAddVarCB(_tweakbar, "Linear Sat Interp.", TW_TYPE_BOOLCPP, SetUseLinChromInterpCB, GetUseLinChromInterpCB, this, "help='Perform linear interpolation on color correction.' group=Tonemapping");

    TwAddVarCB(_tweakbar, "Shoulder Strength",  TW_TYPE_FLOAT, SetShoulderStrengthCB, GetShoulderStrengthCB, this, sGenTwDefinition(_hdrShaderDataMin.shoulderStrength, _hdrShaderDataMax.shoulderStrength, 100, 2, "y", "Y", "Shoulder strength used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Linear Strength",    TW_TYPE_FLOAT, SetLinearStrengthCB, GetLinearStrengthCB, this,   sGenTwDefinition(_hdrShaderDataMin.linearStrength,   _hdrShaderDataMax.linearStrength,   100, 2, "x", "X", "Linear strength used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Linear Angle",       TW_TYPE_FLOAT, SetLinearAngleCB, GetLinearAngleCB, this,      sGenTwDefinition(_hdrShaderDataMin.linearAngle,      _hdrShaderDataMax.linearAngle,      100, 2, "c", "C", "Linear angle used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Toe Strength",       TW_TYPE_FLOAT, SetToeStrengthCB, GetToeStrengthCB, this,      sGenTwDefinition(_hdrShaderDataMin.toeStrength,      _hdrShaderDataMax.toeStrength,      100, 2, "v", "V", "Toe strength used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Toe Numerator",      TW_TYPE_FLOAT, SetToeNumeratorCB, GetToeNumeratorCB, this,     sGenTwDefinition(_hdrShaderDataMin.toeNumerator,     _hdrShaderDataMax.toeNumerator,     100, 2, "b", "B", "Toe numerator used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Toe Denominator",    TW_TYPE_FLOAT, SetToeDenominatorCB, GetToeDenominatorCB, this,   sGenTwDefinition(_hdrShaderDataMin.toeDenominator,   _hdrShaderDataMax.toeDenominator,   100, 2, "n", "N", "Toe denominator used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());
    TwAddVarCB(_tweakbar, "Linear White",       TW_TYPE_FLOAT, SetLinearWhiteCB, GetLinearWhiteCB, this,      sGenTwDefinition(_hdrShaderDataMin.linearWhite,      _hdrShaderDataMax.linearWhite,     1000, 2, "d", "D", "Linear white used in Uncharte2D Filmic Tonmapping.", "'Filmic Uncharte2D'").c_str());

    TwAddVarCB(_tweakbar, "Bias", TW_TYPE_FLOAT, SetBiasCB, GetBiasCB, this, sGenTwDefinition(_hdrShaderDataMin.bias, _hdrShaderDataMax.bias, 100, 2, "i", "I", "Bias parameter of the Drago Logarithmic Tonmapping.", "'Drago Logarithmic'").c_str());

    TwDefine("TweakBar/'Filmic Uncharte2D'   group=Tonemapping");
    TwDefine("TweakBar/'Drago Logarithmic'   group=Tonemapping");

    //
    // Group 'Environment'
    //
    TwAddVarCB(_tweakbar, "Sample Number", TW_TYPE_INT32, SetSampleNumberCB, GetSampleNumberCB, this, "help='Multisampling buffer sample number step=4' group=Environment");
    TwAddVarCB(_tweakbar, "Background Color", TW_TYPE_COLOR3F, SetClearColorCB, GetClearColorCB, this, "help='Background color used for rendering' group=Environment");
    TwAddVarCB(_tweakbar, "Force Background", TW_TYPE_BOOLCPP, SetForceBgndCB, GetForceBgndCB, this,  "help='Force the background as defined by the user, i.e. do not allow tonemapping of the background.' group=Environment");

    std::vector<TwEnumVal> skyBoxeEnums;

    TwEnumVal val;
    val.Value = -1;
    val.Label = "No SkyBox";
    skyBoxeEnums.push_back(val);
    
    for (int i = 0; i < _vecSkyBgnd.size(); ++i)
    {
        TwEnumVal val;
        val.Value = i;
        val.Label = _vecSkyBgnd[i].first.c_str();
        skyBoxeEnums.push_back(val);
    }

    TwType skyBoxType = TwDefineEnum("SkyBoxType", &skyBoxeEnums[0], static_cast<unsigned int>(skyBoxeEnums.size()));
    TwAddVarCB(_tweakbar, "SkyBox", skyBoxType, SetSkyBgndIndexCB, GetSkyBgndIndexCB, this, "help='Available sky boxes' group=Environment");

    TwEnumVal renderTextureEnums[] = { 
        { OSG::HDR2Stage::SCENE_TEXTURE,             "Non Post Processed Scene"}, 
        { OSG::HDR2Stage::LUMINANCE_TEXTURE,         "Luminance Map (No exp)"}, 
        { OSG::HDR2Stage::ADAPTED_LUMINANCE_TEXTURE, "Avaraged Luminance Map (exp)"},
        { OSG::HDR2Stage::THRESHOLD_TEXTURE,         "Threshold Map"},
        { OSG::HDR2Stage::BLURRED_TEXTURE,           "Bloom Blurred Map"},
        { OSG::HDR2Stage::COMPOSITE_TEXTURE,         "Composite"}, 
        { OSG::HDR2Stage::EXPOSURE_TEXTURE,          "Exposure Map"},
        { OSG::HDR2Stage::DEPTH_TEXTURE,             "Depth Map"}, 
        { OSG::HDR2Stage::LINEARIZED_DEPTH_TEXTURE,  "Linearized Depth Map"}

        ,
        { OSG::HDR2Stage::DOWN_SCALED_0,      "Down Scale 0 Map"},
        { OSG::HDR2Stage::DOWN_SCALED_1,      "Down Scale 1 Map"},
        { OSG::HDR2Stage::DOWN_SCALED_2,      "Down Scale 2 Map"},
        { OSG::HDR2Stage::BLUR_TEXTURE,       "BLUR Map"},
        { OSG::HDR2Stage::UPSCALED_SCALED_0,  "Up Scale 0 MapDepth Map"},
        { OSG::HDR2Stage::UPSCALED_SCALED_1,  "Up Scale 1 Map"},


    };
    TwType renderTextureType = TwDefineEnum("RenderTextureType", renderTextureEnums, 15);//9);
    TwAddVarCB(_tweakbar, "Render Texture", renderTextureType, SetResultIndexCB, GetResultIndexCB, this, "help='The texture that is finally drawn' group=Environment");

    //
    // Group 'Light'
    //
    TwAddVarCB(_tweakbar, "Emissive",   TW_TYPE_BOOLCPP, SetRenderEmissiveCB, GetRenderEmissiveCB, this, "help='Render emessive contribution.' group=Light");
    TwAddVarCB(_tweakbar, "Ambient",    TW_TYPE_BOOLCPP, SetRenderAmbientCB, GetRenderAmbientCB, this,  "help='Render ambient contribution.'  group=Light");
    TwAddVarCB(_tweakbar, "Diffuse",    TW_TYPE_BOOLCPP, SetRenderDiffuseCB, GetRenderDiffuseCB, this,  "help='Render diffuse contribution.'  group=Light");
    TwAddVarCB(_tweakbar, "Specular",   TW_TYPE_BOOLCPP, SetRenderSpecularCB, GetRenderSpecularCB, this, "help='Render specular contribution.' group=Light");
}

#endif

