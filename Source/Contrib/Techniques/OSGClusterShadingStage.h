/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGCLUSTERSHADINGSTAGE_H_
#define _OSGCLUSTERSHADINGSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGClusterShadingStageBase.h"
#include "OSGAction.h"
#include "OSGClusterShadingStageDataFields.h"

#include "OSGPlane.h"
#include "OSGImageFields.h"
#include "OSGTextureObjChunkFields.h"
#include "OSGTextureImageChunkFields.h"
#include "OSGShaderStorageBufferObjStdLayoutChunkFields.h"
#include "OSGUniformBufferObjStd140ChunkFields.h"
#include "OSGAlgorithmComputeElementFields.h"

OSG_BEGIN_NAMESPACE

class Camera;
class DrawEnv;
class RenderAction;

/*! \brief ClusterShadingStage class. See \ref
           PageContribTechniquesClusterShadingStage for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ClusterShadingStage : public ClusterShadingStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ClusterShadingStageBase Inherited;
    typedef ClusterShadingStage     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Data                                  */
    /*! \{                                                                 */

    void initData  (RenderAction *pAction,
                    Int32         iVPLeft,
                    Int32         iVPBottom,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    void updateData(RenderAction *pAction,
                    Int32         iVPLeft,
                    Int32         iVPBottom,
                    Int32         iVPWidth,
                    Int32         iVPHeight);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name            Shader Program Snippets                           */
    /*! \{                                                                 */

    std::string getFragmentProgramSnippet       () const;

    std::string getClusteringProgSnippet        (bool is_frag_shader = true) const;
    std::string getFrustumProgSnippet           () const;
    std::string getLightIndexProgSnippet        () const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name            Shader Program Snippets                           */
    /*! \{                                                                 */

    std::string getDispatchProgSnippet          () const;

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Helper Types                              */
    /*! \{                                                                 */

    //
    // simple frustum with only left, right, top and bottom planes. 
    // Front and back planes are calculated differently.
    //
    struct Frustum
    {
        Plane planes[4];
    };

    //
    // data that are used in the compute shader code
    //
    struct DispatchData
    {
        DispatchData() : matTransf(), viewport(), numTiles() {}

        Matrix matTransf;
        Vec4u  viewport;
        Vec2i  numTiles;
    };

    //
    // The clustering data are used in the light culling and in the
    // fragment shader for the cluster key and z-coord calculation.
    // Addditional some helper flags are added to this struct.
    //
    struct ClusteringData
    {
        ClusteringData() 
        : zNear  (0.f), zFar(0.f)  //, D(0.f)
        , nD     (0.f), lg_nD(0.f)
        , a   (0.f), b(0.f) //, c(0)
        , c_1    (0),   p_v (0,0)  //, n_c(0,0,0)
        , enabled(true)
        {}

        Real32 zNear;  // positive near plane distance from eye zNear > 0
        Real32 zFar;   // positive  far plane distance from eye zFar > zNear > 0
        //Real32 D;    // positive near plane offset D >= 0, used only for testing
        Real32 nD;     // zNear + D : shader optimization
        Real32 lg_nD;  // log2(nD) : shader optimization
        Real32 a;      // precalculated factor (c-1)/log2(f/(n+D))
        Real32 b;      // precalculated factor log2(f/(n+D))/(c-1)
        //Int32  c;    // number of cluster planes used only for testing
        Int32  c_1;    // number of cluster planes minus one : shader optimization
        Vec2i  p_v;    // viewport corner points
        //Vec3i  n_c;  // number of clusters, used only for testing
        bool   enabled;// enable cluster shading
    };

    struct LightEyeSpaceData
    {
        Pnt3f position;
        Vec3f direction;

        LightEyeSpaceData(void) :
            position (0.f, 0.f, 0.f),
            direction(0.f, 0.f, 0.f)
        {
        }
    };

    typedef std::vector<Frustum>            VecFrustumsT;
    typedef std::pair<UInt32, UInt32>       ImageDataT;
    typedef std::vector<ImageDataT>         VecImageDataT;
    typedef std::vector<UInt32>             VecLightIndexT;
    typedef std::vector<LightEyeSpaceData>  VecLightEyeSpaceDataT;

    struct Sphere
    {
        Pnt3f  c;   // Center point.
        Real32 r;   // Radius.

        Sphere(void) :
            c(0.f, 0.f, 0.f),
            r(0.f          )
        {
        }
    };

    struct Cone
    {
        Pnt3f  T;   // Cone tip.
        Real32 h;   // Height of the cone.
        Vec3f  d;   // Direction of the cone.
        Real32 r;   // bottom radius of the cone.
        
        Cone(void) :
            T(0.f, 0.f, 0.f),
            h(0.f          ),
            d(0.f, 0.f, 0.f),
            r(0.f          )
        {
        }
    };

    /*! \}                                                                 */

    // Variables should all be in ClusterShadingStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ClusterShadingStage(void);
    ClusterShadingStage(const ClusterShadingStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ClusterShadingStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    Action::ResultE renderEnter(Action *action);
    Action::ResultE renderLeave(Action *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   StageData                                  */
    /*! \{                                                                 */

    void            setupStageData  (ClusterShadingStageData* pData,
                                     Camera*                  pCam,
                                     Int32                    iPixelLeft,
                                     Int32                    iPixelBottom,
                                     Int32                    iPixelWidth,
                                     Int32                    iPixelHeight);

    void            updateStageData (ClusterShadingStageData* pData,
                                     Camera*                  pCam,
                                     Int32                    iPixelLeft,
                                     Int32                    iPixelBottom,
                                     Int32                    iPixelWidth,
                                     Int32                    iPixelHeight);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                StageData Details                             */
    /*! \{                                                                 */
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                 Frustum Details                              */
    /*! \{                                                                 */
    void                resize_frustums
                            (ClusterShadingStageData* pData,
                             std::size_t              size);

    Frustum             getFrustum
                            (ClusterShadingStageData* pData,
                             const UInt32             idx) const;

    void                setFrustum
                            (ClusterShadingStageData* pData,
                             const UInt32             idx, 
                             const Frustum&           frustum);

    std::size_t         calc_frustum_buffer_size
                            (const VecFrustumsT& vFrustums);

    std::vector<UInt8>  create_frustum_buffer
                            (const VecFrustumsT& vFrustums);

    ShaderStorageBufferObjStdLayoutChunkTransitPtr 
                        create_frustum_state
                            (const VecFrustumsT& vFrustums);

    void                update_frustum_state
                            (ShaderStorageBufferObjStdLayoutChunk* ssbo, 
                             const VecFrustumsT&                   vFrustums);

    std::size_t         calc_frustum_buffer_size
                            (ClusterShadingStageData* pData);

    std::vector<UInt8>  create_frustum_buffer
                            (ClusterShadingStageData* pData);

    ShaderStorageBufferObjStdLayoutChunkTransitPtr 
                        create_frustum_state
                            (ClusterShadingStageData* pData);

    void                update_frustum_state
                            (ShaderStorageBufferObjStdLayoutChunk* ssbo, 
                             ClusterShadingStageData*              pData);

    void                update_frustum_state
                            (ClusterShadingStageData*              pData,
                             const VecFrustumsT&                   vFrustums);

    bool                check_frustum_state
                            (ClusterShadingStageData*              pData,
                             const Vec4u&                          viewport);

    Pnt4f               NdcFromScreen
                            (const Pnt3f&    p_w, 
                             const Vec4u&    viewport, 
                             Real32          zNear, 
                             Real32          zFar);

    Pnt4f               NdcFromScreen
                            (const Pnt3f&    p_w,       // with z-coord already 
                             const Vec4u&    viewport); // given in ndc coords!

    Pnt3f               EyeFromNdc
                            (const Pnt4f&    p_n, 
                             const Matrix&   matInvProjection);

    bool                isOrthographicCamera
                            (Camera*         cam, 
                             UInt32          width, 
                             UInt32          height);

    void                calc_ortho_frustums_cpu
                            (const Vec4u&    viewport,
                             const Matrix&   matInvProjection,
                             VecFrustumsT&   frustums);

    void                calc_persp_frustums_cpu
                            (const Vec4u&    viewport,
                             const Matrix&   matInvProjection,
                             VecFrustumsT&   frustums);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Image Details                              */
    /*! \{                                                                 */
    ImageTransitPtr     create_image
                            (UInt32                  width, 
                             UInt32                  height, 
                             UInt32                  depth, 
                             bool                    allocate_memory);

    void                update_image
                            (Image*                  image,
                             UInt32                  width, 
                             UInt32                  height, 
                             UInt32                  depth, 
                             bool                    allocate_memory);

    void                update_image_data
                            (Image*                  image, 
                             const VecImageDataT&    imageData);

    void                write_image_data
                            (UInt32                  i, 
                             UInt32                  j, 
                             UInt32                  k, 
                             const Vec3u&            dimensions, 
                             const ImageDataT&       data, 
                             VecImageDataT&          imageData);

    TextureObjChunkTransitPtr 
                        create_texture_state
                            (Image*                  image);

    void                update_texture_state
                            (TextureObjChunk*        texObjChunk);

    TextureImageChunkTransitPtr 
                        create_texture_image_state
                            (TextureObjChunk*        texObjChunk,
                             const GLenum            access);

    void                update_light_grid_image
                            (const Vec4u&            viewport,
                             Image*                  image,
                             bool                    allocate_memory);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Light Index Details                           */
    /*! \{                                                                 */
    std::size_t         calc_light_index_buffer_size
                            (const VecLightIndexT& vIndexList);

    std::vector<UInt8>  create_light_index_buffer
                            (const VecLightIndexT& vIndexList);

    ShaderStorageBufferObjStdLayoutChunkTransitPtr
                        create_index_state
                            (const VecLightIndexT& vIndexList);

    ShaderStorageBufferObjStdLayoutChunkTransitPtr
                        create_index_state
                            (std::size_t sz);

    void                update_index_state
                            (ShaderStorageBufferObjStdLayoutChunk* ssbo,
                             const VecLightIndexT&                 vIndexList);

    void                clear_index_state
                            (ShaderStorageBufferObjStdLayoutChunk* ssbo,
                             std::size_t                           sz);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Light Index Counter Details                      */
    /*! \{                                                                 */
    ShaderStorageBufferObjStdLayoutChunkTransitPtr
                        create_light_index_counter_state();

    void                clear_light_index_counter_state
                            (ShaderStorageBufferObjStdLayoutChunk* ssbo);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Dispatch Data Details                         */
    /*! \{                                                                 */
    std::size_t         calc_dispatch_data_buffer_size
                            (const DispatchData&          data);

    std::vector<UInt8>  create_dispatch_data_buffer
                            (const DispatchData&          data);

    UniformBufferObjStd140ChunkTransitPtr
                        create_dispatch_data
                            (const DispatchData&          data);

    void                update_dispatch_data
                            (UniformBufferObjStd140Chunk* ubo, 
                             const DispatchData&          data);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Clustering Data Details                        */
    /*! \{                                                                 */
    std::size_t         calc_clustering_data_buffer_size
                            (const ClusteringData&        data);

    std::vector<UInt8>  create_clustering_data_buffer
                            (const ClusteringData&        data);

    UniformBufferObjStd140ChunkTransitPtr 
                        create_clustering_data
                            (const ClusteringData&        data);

    void                update_clustering_data
                            (UniformBufferObjStd140Chunk* ubo, 
                             const ClusteringData&        data);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Plane and Frustums Test                       */
    /*! \{                                                                 */
    bool    PointInsidePlane            (const Pnt3f&   p, 
                                         const Plane&   plane);

    bool    SphereInsidePlane           (const Sphere&  sphere, 
                                         const Plane&   plane);

    bool    SphereInsideFrustum         (const Sphere&  sphere, 
                                         const Frustum& frustum, 
                                         Real32         zNear, 
                                         Real32         zFar);

    bool    ConeInsidePlane             (const Cone&    cone, 
                                         const Plane&   plane);

    bool    ConeInsideFrustum           (const Cone&    cone, 
                                         const Frustum& frustum, 
                                         Real32         zNear, 
                                         Real32         zFar);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Cluster Access                           */
    /*! \{                                                                 */
    UInt32 cluster_k                    (Real32 z_e,
                                         Real32 n,
                                         Real32 f,
                                         Real32 D,
                                         UInt32 c);

    Real32 cluster_z                    (UInt32 k,
                                         Real32 n,
                                         Real32 f,
                                         Real32 D,
                                         UInt32 c);

    UInt32 cluster_k                    (Real32 z_e,
                                         Real32 nD,
                                         Real32 lg_nD,
                                         Real32 f,
                                         Real32 a,
                                         UInt32 c_1);

    Real32 cluster_z                    (UInt32 k,
                                         Real32 n,
                                         Real32 f,
                                         Real32 nD,
                                         Real32 b,
                                         UInt32 c_1);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Compute Shader Programs                      */
    /*! \{                                                                 */

    std::string get_persp_frustum_cp_program();
    std::string get_ortho_frustum_cp_program();
    std::string get_light_culling_cp_program();
    std::string get_fragment_cp_program();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Computation                             */
    /*! \{                                                                 */

    void create_computation(ClusterShadingStageData* pData);
    void update_computation(ClusterShadingStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Frustum Computation                        */
    /*! \{                                                                 */

    void create_frustum_computation(ClusterShadingStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Light Culling Computation                     */
    /*! \{                                                                 */

    void create_light_culling_computation(ClusterShadingStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Fragment Shader                          */
    /*! \{                                                                 */

    void create_fragment_shader(ClusterShadingStageData* pData);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Update Dispatch Configurations                   */
    /*! \{                                                                 */

    void update_dispatch_config_frustums
                            (ClusterShadingStageData* pData,
                             const Vec4u&             viewport,
                             const Matrix&            matInvProjection);

    void update_dispatch_config_cull_lights 
                            (ClusterShadingStageData* pData,
                             const Vec4u&             viewport,
                             const Matrix&            matViewing);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Calculate Affected Lights                     */
    /*! \{                                                                 */

    void calc_affected_lights   (const Matrix&          matEyeFromWorld,
                                 FrustumVolume          volViewFrustum,
                                 VecLightIndexT&        vecAffectedLights,
                                 VecLightEyeSpaceDataT& vecEyeSpaceData);

    void transform_to_eye_space (Matrix                 matEyeFromWorld,
                                 Node*                  beacon,
                                 const Pnt3f&           position_bs,
                                 const Vec3f&           direction_bs,
                                 Pnt3f&                 position_es,
                                 Vec3f&                 direction_es);

    bool point_light_inside_frustum
                                (const Pnt3f&           position_es,
                                 Real32                 range,
                                 const Frustum&         frustum, 
                                 Real32                 n, 
                                 Real32                 f);

    bool spot_light_inside_frustum
                                (const Pnt3f&           position_es,
                                 const Vec3f&           direction_es,
                                 Real32                 range,
                                 Real32                 spotlightAngle,
                                 const Frustum&         frustum, 
                                 Real32                 n, 
                                 Real32                 f);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    CPU Light Culling                         */
    /*! \{                                                                 */

    std::size_t frustum_accessor
                        (const UInt32 i, 
                         const UInt32 j, 
                         const Vec3u& dimensions);

    void        cull_lights
                        (ClusterShadingStageData*     pData,
                         const VecLightIndexT&        vecAffectedLights,
                         const VecLightEyeSpaceDataT& vecEyeSpaceData,
                         const Vec3u&                 dimensions,
                         const Matrix&                matEyeFromWorld,
                         Real32                       zNear,
                         Real32                       zFar,
                         Real32                       D,
                         VecImageDataT&               gridData,
                         VecLightIndexT&              lightIndexList);

   /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    bool _bSetupStage;

    friend class FieldContainer;
    friend class ClusterShadingStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ClusterShadingStage &source);
};

typedef ClusterShadingStage *ClusterShadingStageP;

OSG_END_NAMESPACE

#include "OSGClusterShadingStageBase.inl"
#include "OSGClusterShadingStage.inl"

#endif /* _OSGCLUSTERSHADINGSTAGE_H_ */
