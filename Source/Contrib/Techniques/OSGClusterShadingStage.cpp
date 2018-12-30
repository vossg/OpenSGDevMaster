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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"
#include "OSGAction.h"
#include "OSGCamera.h"
#include "OSGMatrixCamera.h"
#include "OSGOrthographicCamera.h"
#include "OSGRenderAction.h"
#include "OSGTime.h"

#include "OSGClusterShadingStage.h"
#include "OSGClusterShadingStageData.h"

#include "OSGChunkMaterial.h"
#include "OSGDrawEnv.h"
#include "OSGFrameBufferObject.h"
#include "OSGTextureObjChunk.h"
#include "OSGStateOverride.h"

#include "OSGMatrixUtility.h"

#include "OSGImage.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureImageChunk.h"
#include "OSGMultiLightChunk.h"
#include "OSGUniformBufferObjStd140Chunk.h"
#include "OSGShaderStorageBufferObjStdLayoutChunk.h"

#include "OSGShaderProgram.h"
#include "OSGShaderProgramChunk.h"
#include "OSGComputeShaderChunk.h"
#include "OSGComputeShaderAlgorithm.h"
#include "OSGAlgorithmComputeElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGClusterShadingStageBase.cpp file.
// To modify it, please change the .fcd file (OSGClusterShadingStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ClusterShadingStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            ClusterShadingStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&ClusterShadingStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            ClusterShadingStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&ClusterShadingStage::renderLeave));
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ClusterShadingStage::ClusterShadingStage(void)
: Inherited()
, _bSetupStage(false)
{
}

ClusterShadingStage::ClusterShadingStage(const ClusterShadingStage &source)
: Inherited(source)
, _bSetupStage(false)
{
}

ClusterShadingStage::~ClusterShadingStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ClusterShadingStage::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    //
    // The BeaconMatrixFieldMask is deliberately omitted
    // 
    if((whichField & ( 
                        BlockSizeFieldMask |
                        TileSizeFieldMask |
                        NumClusterZFieldMask |
                        NearPlaneOffsetFieldMask |

                        DispatchDataBindingPntFieldMask |
                        ClusterDataBindingPntFieldMask |
                        LightBindingPntFieldMask |
                        AffectedLightIndexListBindingPntFieldMask |
                        FrustumBindingPntFieldMask |
                        LightIndexListBindingPntFieldMask |
                        LightIndexCounterBindingPntFieldMask |
                        LightGridBindingPntFieldMask |

                        AffectedLightIndexListBlockNameFieldMask |
                        AffectedLightIndexListVariableNameFieldMask |
                        LightIndexListBlockNameFieldMask |
                        LightIndexListVariableNameFieldMask |
                        ClusteringDataBlockNameFieldMask |
                        ClusteringDataVariableNameFieldMask |
                        LightGridVariableNameFieldMask |

                        CalcFrustumsOnCPUFieldMask |
                        CullLighsOnCPUFieldMask |
                        //DisabledFieldMask |
                        MaxLightIndexListSizeFieldMask |
                        MaxClusterLightCountFieldMask
                        //FrustNodeFieldMask |
                        //FrustCompShaderAlgoFieldMask |
                        //CullCompShaderAlgoFieldMask |
                        //MultiLightChunkFieldMask |
                        //ShaderProgChunkFieldMask
        )) != 0)
    {
        _bSetupStage = true;
    }

    Inherited::changed(whichField, origin, details);
}

void ClusterShadingStage::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ClusterShadingStage NI" << std::endl;
}

/*------------------------------- Draw ------------------------------------*/

Action::ResultE ClusterShadingStage::renderEnter(Action* action)
{
    RenderAction* a = dynamic_cast<RenderAction*>(action);

    if(a != NULL)
    {
// ???       this->pushPartition(a, RenderPartition::CopyAll);

        RenderPartition* pPart = a->getActivePartition();

        DrawEnv& oDrawEnv = pPart->getDrawEnv();

        Int32 iVPLeft   = oDrawEnv.getPixelLeft();
        Int32 iVPBottom = oDrawEnv.getPixelBottom();
        Int32 iVPWidth  = oDrawEnv.getPixelWidth();
        Int32 iVPHeight = oDrawEnv.getPixelHeight();

        this->updateData(a, iVPLeft, iVPBottom, iVPWidth, iVPHeight);

        ClusterShadingStageDataUnrecPtr pData = a->getData<ClusterShadingStageData *>(_iDataSlotId);

        //
        // Perform the computation
        //
        if (!getDisabled())
        {
            //std::cout << "compute shader..." << std::endl;
            this->recurse(action, getFrustNode());
            a->useNodeList(false);
        }

        a->pushState();

        a->addOverride(       getMultiLightChunk                ()->getClassId() + getLightBindingPnt(),                         getMultiLightChunk());
        a->addOverride(       getShaderProgChunk                ()->getClassId(),                                                getShaderProgChunk());
        a->addOverride(pData->getLightGridTexImgChunkFS         ()->getClassId() + getLightGridBindingPnt(),              pData->getLightGridTexImgChunkFS());
        a->addOverride(pData->getAffectedLightIndexListSSBOChunk()->getClassId() + getAffectedLightIndexListBindingPnt(), pData->getAffectedLightIndexListSSBOChunk());
        a->addOverride(pData->getLightIndexListSSBOChunk        ()->getClassId() + getLightIndexListBindingPnt(),         pData->getLightIndexListSSBOChunk());
        a->addOverride(pData->getCullClusterDatUBOChunk         ()->getClassId() + getClusterDataBindingPnt(),            pData->getCullClusterDatUBOChunk());

        this->recurseFromThis(a);
        a->useNodeList(false);

        a->popState();

// ???       this->popPartition(a);
    }

    return Action::Skip;
}

Action::ResultE ClusterShadingStage::renderLeave(Action *action)
{
    return Action::Skip;
}

/*------------------------------ Data -------------------------------------*/

void ClusterShadingStage::initData(
    RenderAction* pAction,
    Int32         iVPLeft,
    Int32         iVPBottom,
    Int32         iVPWidth,
    Int32         iVPHeight)
{
    Camera* pCam = pAction->getCamera();
    if (pCam == NULL)
        return;

    OSG_ASSERT(pAction->getData<ClusterShadingStageData*>(_iDataSlotId) == NULL);

    ClusterShadingStageDataUnrecPtr pData = ClusterShadingStageData::createLocal();
    this->setData(pData, _iDataSlotId, pAction);

    setupStageData(pData, pCam, iVPLeft, iVPBottom, iVPWidth, iVPHeight);
}

void ClusterShadingStage::updateData(
    RenderAction* pAction,
    Int32         iVPLeft,
    Int32         iVPBottom,
    Int32         iVPWidth,
    Int32         iVPHeight)
{
    ClusterShadingStageDataUnrecPtr pData = pAction->getData<ClusterShadingStageData *>(_iDataSlotId);

    Camera* pCam = pAction->getCamera();
    if (pCam == NULL)
        return;

    if(pData == NULL)
    {
        initData(pAction, iVPLeft, iVPBottom, iVPWidth, iVPHeight);

        pData = pAction->getData<ClusterShadingStageData *>(_iDataSlotId);
    }
    else if (_bSetupStage)
    {
        setupStageData(pData, pCam, iVPLeft, iVPBottom, iVPWidth, iVPHeight);
    }

    updateStageData(pData, pCam, iVPLeft, iVPBottom, iVPWidth, iVPHeight);

    _bSetupStage = false;
}

/*---------------------------- StageData ----------------------------------*/

void ClusterShadingStage::setupStageData(
    ClusterShadingStageData* pData,
    Camera*                  pCam,
    Int32                    iPixelLeft,
    Int32                    iPixelBottom,
    Int32                    iPixelWidth,
    Int32                    iPixelHeight)
{
    if (pData != NULL)
    {
        ImageUnrecPtr             img_light_grid        = create_image(1,1,1, getCullLighsOnCPU());
        TextureObjChunkUnrecPtr   tex_obj_light_grid    = create_texture_state(img_light_grid);
        TextureImageChunkUnrecPtr tex_img_light_grid_cs = create_texture_image_state(tex_obj_light_grid, GL_WRITE_ONLY);
        TextureImageChunkUnrecPtr tex_img_light_grid_fs = create_texture_image_state(tex_obj_light_grid, GL_READ_ONLY);

        ShaderStorageBufferObjStdLayoutChunkUnrecPtr ssbo_frustums                  = create_frustum_state(VecFrustumsT(1));
        ShaderStorageBufferObjStdLayoutChunkUnrecPtr ssbo_affected_light_index_list = create_index_state(1);
        ShaderStorageBufferObjStdLayoutChunkUnrecPtr ssbo_light_index_list          = create_index_state(getMaxLightIndexListSize());
        ShaderStorageBufferObjStdLayoutChunkUnrecPtr ssbo_light_index_counter       = create_light_index_counter_state();

        UniformBufferObjStd140ChunkUnrecPtr ubo_frustum_dispatch_data       = create_dispatch_data(DispatchData());
        UniformBufferObjStd140ChunkUnrecPtr ubo_light_culling_dispatch_data = create_dispatch_data(DispatchData());
        UniformBufferObjStd140ChunkUnrecPtr ubo_clustering_data             = create_clustering_data(ClusteringData());

        ChunkMaterialUnrecPtr frust_chunk_material = ChunkMaterial::createLocal();
        ChunkMaterialUnrecPtr cull_chunk_material  = ChunkMaterial::createLocal();

        frust_chunk_material->addChunk(ubo_frustum_dispatch_data,      getDispatchDataBindingPnt());
        frust_chunk_material->addChunk(ssbo_frustums,                  getFrustumBindingPnt());

        cull_chunk_material->addChunk(tex_img_light_grid_cs,           getLightGridBindingPnt());
        cull_chunk_material->addChunk(getMultiLightChunk(),            getLightBindingPnt());
        cull_chunk_material->addChunk(ubo_light_culling_dispatch_data, getDispatchDataBindingPnt());
        cull_chunk_material->addChunk(ubo_clustering_data,             getClusterDataBindingPnt());
        cull_chunk_material->addChunk(ssbo_frustums,                   getFrustumBindingPnt());
        cull_chunk_material->addChunk(ssbo_affected_light_index_list,  getAffectedLightIndexListBindingPnt());
        cull_chunk_material->addChunk(ssbo_light_index_list,           getLightIndexListBindingPnt());
        cull_chunk_material->addChunk(ssbo_light_index_counter,        getLightIndexCounterBindingPnt());

        //
        // force resize in first update
        //
        pData->setLeft  (0);
        pData->setBottom(0);
        pData->setWidth (0);
        pData->setHeight(0);

        pData->setLightGridImage                 (img_light_grid);
        pData->setLightGridTexObjChunk           (tex_obj_light_grid);
        pData->setLightGridTexImgChunkCS         (tex_img_light_grid_cs);
        pData->setLightGridTexImgChunkFS         (tex_img_light_grid_fs);
        pData->setFrustumsSSBOChunk              (ssbo_frustums);
        pData->setAffectedLightIndexListSSBOChunk(ssbo_affected_light_index_list);
        pData->setLightIndexListSSBOChunk        (ssbo_light_index_list);
        pData->setCullLightIndexCounterSSBOChunk (ssbo_light_index_counter);
        pData->setFrustDispDatUBOChunk           (ubo_frustum_dispatch_data);
        pData->setCullDispDatUBOChunk            (ubo_light_culling_dispatch_data);
        pData->setCullClusterDatUBOChunk         (ubo_clustering_data);
        pData->setFrustChunkMat                  (frust_chunk_material);
        pData->setCullChunkMat                   (cull_chunk_material);

        bool isOrtho = isOrthographicCamera(pCam, iPixelWidth, iPixelHeight);
        pData->setIsOrthographicCamera(isOrtho);

        create_computation    (pData);
        create_fragment_shader(pData);

        Thread::setCurrentLocalFlags();
    }
}

void ClusterShadingStage::updateStageData(
    ClusterShadingStageData* pData,
    Camera*                  pCam,
    Int32                    iPixelLeft,
    Int32                    iPixelBottom,
    Int32                    iPixelWidth,
    Int32                    iPixelHeight)
{
    if (pData == NULL || pCam == NULL)
        return;

    update_computation(pData);

    bool resize = false;

    if (    iPixelLeft   != pData->getLeft() 
         || iPixelBottom != pData->getBottom() 
         || iPixelWidth  != pData->getWidth() 
         || iPixelHeight != pData->getHeight())
        resize = true;

    pData->setLeft  (iPixelLeft  );
    pData->setBottom(iPixelBottom);
    pData->setWidth (iPixelWidth );
    pData->setHeight(iPixelHeight);

    Vec4u viewport(iPixelLeft, iPixelBottom, iPixelWidth, iPixelHeight);

    if (!check_frustum_state(pData, viewport))
        resize = true;

    if (resize)
    {
        //std::cout << "resize...";

        Matrix matProjection, matInverseProjection, matProjectionTranslation;

        pCam->getProjection           (matProjection,            iPixelWidth, iPixelHeight);
        pCam->getProjectionTranslation(matProjectionTranslation, iPixelWidth, iPixelHeight);

        matProjection.mult(matProjectionTranslation);
        matProjection.inverse(matInverseProjection);

        //
        // The light grid image size must be adapted.
        // CPU memory is needed only if culling is performed on the CPU.
        //
        update_light_grid_image(viewport, pData->getLightGridImage(), getCullLighsOnCPU());

        //
        // Light culling on CPU forces frustum calculation on CPU
        //
        if (getCalcFrustumsOnCPU() == true || getCullLighsOnCPU() == true)
        {
            //std::cout << "...on CPU" << std::endl;
            //
            // We caclulate the tile frustum planes on the CPU, store them in the following
            // vector for further evaluation.
            //
            VecFrustumsT frustums;
            if (isOrthographicCamera(pCam, iPixelWidth, iPixelHeight))
                calc_ortho_frustums_cpu(viewport, matInverseProjection, frustums);
            else
                calc_persp_frustums_cpu(viewport, matInverseProjection, frustums);


            if (getCullLighsOnCPU())
            {
                //
                // The just CPU calculated frustum must be stored in the stage
                // data object for CPU light culling.
                //
                update_frustum_state(pData, frustums);
            }
            else
            {
                //
                // The just CPU calculated frustum must be uploaded to the SSBO
                //
                update_frustum_state(pData->getFrustumsSSBOChunk(), frustums);
            }
        }
        else
        {
            //std::cout << "...on GPU" << std::endl;

            update_dispatch_config_frustums(pData, viewport, matInverseProjection);
        }
    }

    UInt32 tile_size = getTileSize();

    Real32 zNear = pCam->getNear();
    Real32 zFar  = pCam->getFar ();

    UInt32 num_cluster_x = UInt32(osgCeil(Real32(iPixelWidth)  / tile_size));
    UInt32 num_cluster_y = UInt32(osgCeil(Real32(iPixelHeight) / tile_size));
    UInt32 num_cluster_z = getNumClusterZ();

    FrustumVolume viewVolume;
    pCam->getFrustum(viewVolume, iPixelWidth, iPixelHeight);

    Matrix matEyeFromWorld;
    pCam->getViewing(matEyeFromWorld, iPixelWidth, iPixelHeight);

    //
    // We have to update the view matrix for the light culling compute shader
    //
    if (getCullLighsOnCPU() == false)
    {
        update_dispatch_config_cull_lights(pData, viewport, matEyeFromWorld);
    }

    VecLightIndexT        vecAffectedLights;    // the lights that contribute to the view frustum illumination
    VecLightEyeSpaceDataT vecEyeSpaceData;      // the eye space position and direction of the lights

    //
    // We determine an index list of all lights that are actually contributing to the
    // shading of the complete visible view frustum...
    //
    calc_affected_lights(
                    matEyeFromWorld,    // in transform from world to eye space
                    viewVolume,         // in the view frustum volume in world space
                    vecAffectedLights,  // out the index list
                    vecEyeSpaceData);   // optimization: eye space light positions and directions

    //
    // ...and update the corresponding SSBO accordingly
    //
    update_index_state(pData->getAffectedLightIndexListSSBOChunk(), vecAffectedLights);

    if (!getDisabled())
    {
        //std::cout << "not disabled" << std::endl;
        //
        // Clearing of the global light index counter is absolutly necessary!
        //
        if (getCullLighsOnCPU() == false)
        {
            clear_light_index_counter_state(pData->getCullLightIndexCounterSSBOChunk());
        }

        if (getCullLighsOnCPU() == true)
        {
            //std::cout << "cull on CPU" << std::endl;
            //
            // These are the results of the light culling procedure below. We will fill these
            // raw data into appropriate SSBO so that they are available in the fragment shader
            // for evaluation.
            //
            VecImageDataT  gridData;        // tuples of offset and cound integers: { o1,c1, o2,c2, o3,c3,...}
            VecLightIndexT lightIndexList;  // pointers into the lights array.

            Vec3u dimensions(num_cluster_x, num_cluster_y, num_cluster_z);

            cull_lights(
                pData,                  // in contains the CPU calculated tile frustum planes
                vecAffectedLights,      // in the lights that are actually contributing to the view frustum shading
                vecEyeSpaceData,        // in the precalculated light eye space positions and directions
                dimensions,             // in cluster dimensions
                matEyeFromWorld,        // in transform from world to eye space
                zNear,                  // in distance of near plane from eye point
                zFar,                   // in distance of far  plane from eye point
                getNearPlaneOffset(),   // in distance offset for near plane
                gridData,               // out the raw grid data
                lightIndexList);        // out the index list

            //
            // Fill gridData to image and inform texture object about change
            //
            update_image_data   (pData->getLightGridImage(), gridData);
            update_texture_state(pData->getLightGridTexObjChunk());

            //
            // Fill lightIndexList to SSBO:
            //
            update_index_state(pData->getLightIndexListSSBOChunk(), lightIndexList);
        }
    }

    //
    // Update the clustering data used in the light cull and fragment shader
    //
    ClusteringData clusteringData;
    clusteringData.zNear   = zNear;                                                   // positive near plane distance from eye zNear > 0
    clusteringData.zFar    = zFar;                                                    // positive  far plane distance from eye zFar > zNear > 0
    //clusteringData.D     = getNearPlaneOffset();                                    // positive near plane offset D >= 0
    clusteringData.nD      = zNear + getNearPlaneOffset();                            // zNear + D : shader optimization
    clusteringData.lg_nD   = log2(clusteringData.nD);                                 // log2(nD) : shader optimization
    clusteringData.a       = (num_cluster_z-1)/log2(zFar/clusteringData.nD);          // precalculated factor (c-1)/log2(f/(n+D))
    clusteringData.b       = 1.f/clusteringData.a;                                    // precalculated factor log2(f/(n+D))/(c-1)
    //clusteringData.c     = num_cluster_z;                                           // number of cluster planes
    clusteringData.c_1     = num_cluster_z - 1;                                       // number of cluster planes minus one : shader optimization
    clusteringData.p_v     = Vec2i(iPixelLeft, iPixelBottom);                         // viewport corner points
    //clusteringData.n_c   = Vec3i(num_cluster_x, num_cluster_y, num_cluster_z);      // number of clusters
    clusteringData.enabled = !getDisabled();

    update_clustering_data(pData->getCullClusterDatUBOChunk(), clusteringData);

    commitChanges();
}

/*-------------------------- Frustum Details ------------------------------*/

inline
void ClusterShadingStage::resize_frustums(
    ClusterShadingStageData* pData,
    std::size_t              size)
{
    OSG_ASSERT(pData != NULL);

    MFMatrix* normals   = pData->editMFFrustumPlanesNormals();
    MFVec4f*  distances = pData->editMFFrustumPlanesDistances();

    normals  ->resize(size);
    distances->resize(size);
}

inline 
ClusterShadingStage::Frustum 
ClusterShadingStage::getFrustum(
    ClusterShadingStageData* pData,
    const UInt32             idx) const
{
    OSG_ASSERT(pData != NULL);

    Frustum frustum;

    const Matrix& normals   = pData->getFrustumPlanesNormals  (idx);
    const Vec4f&  distances = pData->getFrustumPlanesDistances(idx);

    frustum.planes[0] = Plane(Vec3f(normals[0]), distances[0]);
    frustum.planes[1] = Plane(Vec3f(normals[1]), distances[1]);
    frustum.planes[2] = Plane(Vec3f(normals[2]), distances[2]);
    frustum.planes[3] = Plane(Vec3f(normals[3]), distances[3]);

    return frustum;
}

inline
void ClusterShadingStage::setFrustum(
    ClusterShadingStageData* pData,
    const UInt32             idx, 
    const Frustum&           frustum)
{
    OSG_ASSERT(pData != NULL);
    OSG_ASSERT(pData->getMFFrustumPlanesNormals  ()->size() > idx);
    OSG_ASSERT(pData->getMFFrustumPlanesDistances()->size() > idx);

    MFMatrix::reference rMat = pData->editFrustumPlanesNormals  (idx);
    MFVec4f ::reference rVec = pData->editFrustumPlanesDistances(idx);

    rMat.setValue(frustum.planes[0].getNormal(),
                  frustum.planes[1].getNormal(),
                  frustum.planes[2].getNormal(),
                  frustum.planes[3].getNormal());

    rVec.setValue(
                    Vec4f(frustum.planes[0].getDistanceFromOrigin(),
                          frustum.planes[1].getDistanceFromOrigin(),
                          frustum.planes[2].getDistanceFromOrigin(),
                          frustum.planes[3].getDistanceFromOrigin())
                   );
}

std::size_t ClusterShadingStage::calc_frustum_buffer_size(
    const VecFrustumsT& vFrustums)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t j = 0; j < 4; ++j)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
        ao = alignOffset(16, bo); bo = ao;
    }

    ao *= vFrustums.size();    bo = ao;    // array
    ao = alignOffset( 16, bo); bo = ao;    // padding

    return ao;
}

std::vector<UInt8> ClusterShadingStage::create_frustum_buffer(
    const VecFrustumsT& vFrustums)
{
    std::size_t size = calc_frustum_buffer_size(vFrustums);

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vFrustums.size(); ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            ao = alignOffset(16, bo);
            memcpy(&buffer[0] + ao, &vFrustums[i].planes[j].getNormal(), sizeof(Vec3f));
            bo = ao + sizeof(Vec3f);

            ao = alignOffset( 4, bo);
            *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = vFrustums[i].planes[j].getDistanceFromOrigin();
            bo = ao + sizeof(Real32);

            ao = alignOffset(16, bo); bo = ao;
        }

        ao = alignOffset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

ShaderStorageBufferObjStdLayoutChunkTransitPtr 
ClusterShadingStage::create_frustum_state(
    const VecFrustumsT& vFrustums)
{
    ShaderStorageBufferObjStdLayoutChunkTransitPtr ssbo = ShaderStorageBufferObjStdLayoutChunk::createLocal();

    std::vector<UInt8> buffer = create_frustum_buffer(vFrustums);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return ssbo;
}

void ClusterShadingStage::update_frustum_state(
    ShaderStorageBufferObjStdLayoutChunk* ssbo, 
    const VecFrustumsT&                   vFrustums)
{
    if (ssbo) {
        std::vector<UInt8> buffer = create_frustum_buffer(vFrustums);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

std::size_t ClusterShadingStage::calc_frustum_buffer_size(
    ClusterShadingStageData* pData)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t j = 0; j < 4; ++j)
    {
        ao = alignOffset(16, bo); bo = ao + sizeof(Vec3f);
        ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);
        ao = alignOffset(16, bo); bo = ao;
    }

    OSG_ASSERT(pData != NULL);
    OSG_ASSERT(pData->editMFFrustumPlanesNormals()->size() == pData->editMFFrustumPlanesDistances()->size());

    ao *= pData->editMFFrustumPlanesNormals()->size();    bo = ao;    // array
    ao = alignOffset( 16, bo);                            bo = ao;    // padding

    return ao;
}

std::vector<UInt8> ClusterShadingStage::create_frustum_buffer(
    ClusterShadingStageData* pData)
{
    std::size_t size = calc_frustum_buffer_size(pData);

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    std::size_t num_frustums = pData->editMFFrustumPlanesNormals()->size();

    for (std::size_t i = 0; i < num_frustums; ++i)
    {
        Frustum frustum = getFrustum(pData, static_cast<UInt32>(i));

        for (std::size_t j = 0; j < 4; ++j)
        {
            ao = alignOffset(16, bo);
            memcpy(&buffer[0] + ao, &frustum.planes[j].getNormal(), sizeof(Vec3f));
            bo = ao + sizeof(Vec3f);

            ao = alignOffset( 4, bo);
            *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = frustum.planes[j].getDistanceFromOrigin();
            bo = ao + sizeof(Real32);

            ao = alignOffset(16, bo); bo = ao;
        }

        ao = alignOffset( 16, bo); bo = ao;    // padding
    }

    return buffer;
}

ShaderStorageBufferObjStdLayoutChunkTransitPtr 
ClusterShadingStage::create_frustum_state(
    ClusterShadingStageData* pData)
{
    ShaderStorageBufferObjStdLayoutChunkTransitPtr ssbo = ShaderStorageBufferObjStdLayoutChunk::createLocal();

    std::vector<UInt8> buffer = create_frustum_buffer(pData);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return ssbo;
}

void ClusterShadingStage::update_frustum_state(
    ShaderStorageBufferObjStdLayoutChunk* ssbo, 
    ClusterShadingStageData*              pData)
{
    if (ssbo) {
        std::vector<UInt8> buffer = create_frustum_buffer(pData);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

void ClusterShadingStage::update_frustum_state(
    ClusterShadingStageData* pData,
    const VecFrustumsT&      vFrustums)
{
    resize_frustums(pData, vFrustums.size());

    std::size_t sz = vFrustums.size();

    for (std::size_t i = 0; i < sz; ++i)
    {
        setFrustum(pData, static_cast<UInt32>(i), vFrustums[i]);
    }
}

bool ClusterShadingStage::check_frustum_state(
    ClusterShadingStageData* pData,
    const Vec4u&             viewport)
{
    if (getCalcFrustumsOnCPU() == true || getCullLighsOnCPU() == true)
    {
//        Real32 x_v = static_cast<Real32>(viewport[0]);
//        Real32 y_v = static_cast<Real32>(viewport[1]);
        Real32 w   = static_cast<Real32>(viewport[2]);
        Real32 h   = static_cast<Real32>(viewport[3]);

        UInt32 tile_size = getTileSize();

        UInt32 numHorizontalTiles = UInt32(osgCeil(w / tile_size));
        UInt32 numVerticalTiles   = UInt32(osgCeil(h / tile_size));

        std::size_t sz = numHorizontalTiles * numVerticalTiles;

        MFMatrix* normals   = pData->editMFFrustumPlanesNormals();
        MFVec4f*  distances = pData->editMFFrustumPlanesDistances();

        if (normals->size() != sz || distances->size() != sz)
            return false;
    }
    return true;
}

Pnt4f ClusterShadingStage::NdcFromScreen(
    const Pnt3f& p_w, 
    const Vec4u& viewport, 
    Real32       zNear, 
    Real32       zFar)
{
    Real32 x_v = static_cast<Real32>(viewport[0]);
    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    Pnt4f p_n(
            2.f * (p_w.x() - x_v) / w - 1.f,
            2.f * (p_w.y() - y_v) / h - 1.f,
            2.f * (p_w.z() - zFar - zNear) / (zFar - zNear),
            1);

    return p_n;
}

Pnt4f ClusterShadingStage::NdcFromScreen(
    const Pnt3f& p_w,          // with z-coord already given in ndc coords!
    const Vec4u& viewport)
{
    Real32 x_v = static_cast<Real32>(viewport[0]);
    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    Pnt4f p_n(
            2.f * (p_w.x() - x_v) / w - 1.f,
            2.f * (p_w.y() - y_v) / h - 1.f,
            p_w.z(),
            1);

    return p_n;
}

Pnt3f ClusterShadingStage::EyeFromNdc(
    const Pnt4f&  p_n, 
    const Matrix& matInvProjection)
{
    Pnt4f p_e;
    matInvProjection.mult(p_n, p_e);
    p_e /= p_e.w();
    return Pnt3f(p_e.x(), p_e.y(), p_e.z());
}

bool ClusterShadingStage::isOrthographicCamera(
    Camera* cam, 
    UInt32  width, 
    UInt32  height)
{
    OrthographicCamera* orthoCam = dynamic_cast<OrthographicCamera*>(cam);
    if (orthoCam)
        return true;

    MatrixCamera* matrixCam = dynamic_cast<MatrixCamera*>(cam);
    if (matrixCam)
    {
        Matrix matProjection;
        matrixCam->getProjection(matProjection, width, height);

//        float m32 = matProjection[2][3];
//        float m33 = matProjection[3][3];

        if (matProjection[2][3] == 0.f && matProjection[3][3] == 1.f)
            return true;
    }

    return false;
}

void ClusterShadingStage::calc_ortho_frustums_cpu(
    const Vec4u&  viewport,
    const Matrix& matInvProjection,
    VecFrustumsT& frustums)
{
    Real32 x_v = static_cast<Real32>(viewport[0]);
    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    UInt32 tile_size = getTileSize();

    UInt32 numHorizontalTiles = UInt32(osgCeil(w / tile_size));
    UInt32 numVerticalTiles   = UInt32(osgCeil(h / tile_size));

    frustums.resize(numHorizontalTiles * numVerticalTiles);

    if (getDisabled())
        return;

    Pnt3f pnts_w[8];
    Pnt4f pnts_n[8];
    Pnt3f pnts_e[8];

    for (UInt32 j = 0; j < numVerticalTiles; ++j)
    {
        Real32 y0 =             y_v +  j    * tile_size;
        Real32 y1 = osgMin(y_v + (j+1) * tile_size, y_v + h);

        for (UInt32 i = 0; i < numHorizontalTiles; ++i)
        {
            Real32 x0 =             x_v +  i    * tile_size;
            Real32 x1 = osgMin(x_v + (i+1) * tile_size, x_v + w);

            pnts_w[0] = Pnt3f(x0, y0, 1.f);
            pnts_w[1] = Pnt3f(x1, y0, 1.f);
            pnts_w[2] = Pnt3f(x0, y1, 1.f);
            pnts_w[3] = Pnt3f(x1, y1, 1.f);

            pnts_w[4] = Pnt3f(x0, y0, -1.f);
            pnts_w[5] = Pnt3f(x1, y0, -1.f);
            pnts_w[6] = Pnt3f(x0, y1, -1.f);
            pnts_w[7] = Pnt3f(x1, y1, -1.f);

            for (UInt32 k = 0; k < 8; ++k)
            {
                pnts_n[k] = NdcFromScreen(pnts_w[k], viewport);
                pnts_e[k] = EyeFromNdc   (pnts_n[k], matInvProjection);
            }

            UInt32 idx = j * numHorizontalTiles + i;

            frustums[idx].planes[0] = Plane(pnts_e[6], pnts_e[0], pnts_e[2]);   //   left plane
            frustums[idx].planes[1] = Plane(pnts_e[7], pnts_e[3], pnts_e[1]);   //  right plane
            frustums[idx].planes[2] = Plane(pnts_e[6], pnts_e[2], pnts_e[3]);   //    top plane
            frustums[idx].planes[3] = Plane(pnts_e[4], pnts_e[1], pnts_e[0]);   // bottom plane
        }
    }
}

void ClusterShadingStage::calc_persp_frustums_cpu(
    const Vec4u&  viewport,
    const Matrix& matInvProjection,
    VecFrustumsT& frustums)
{
    Real32 x_v = static_cast<Real32>(viewport[0]);
    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    UInt32 tile_size = getTileSize();

    UInt32 numHorizontalTiles = UInt32(osgCeil(w / tile_size));
    UInt32 numVerticalTiles   = UInt32(osgCeil(h / tile_size));

    frustums.resize(numHorizontalTiles * numVerticalTiles);

    if (getDisabled())
        return;

    Pnt3f pEye = Pnt3f(0.f, 0.f, 0.f);    // eye position in view space

    Pnt3f pnts_w[4];
    Pnt4f pnts_n[4];
    Pnt3f pnts_e[4];

    for (UInt32 j = 0; j < numVerticalTiles; ++j)
    {
        Real32 y0 =             y_v +  j    * tile_size;
        Real32 y1 = osgMin(y_v + (j+1) * tile_size, y_v + h);

        for (UInt32 i = 0; i < numHorizontalTiles; ++i)
        {
            Real32 x0 =             x_v +  i    * tile_size;
            Real32 x1 = osgMin(x_v + (i+1) * tile_size, x_v + w);

            pnts_w[0] = Pnt3f(x0, y0, -1.f);
            pnts_w[1] = Pnt3f(x1, y0, -1.f);
            pnts_w[2] = Pnt3f(x0, y1, -1.f);
            pnts_w[3] = Pnt3f(x1, y1, -1.f);

            for (UInt32 k = 0; k < 4; ++k)
            {
                pnts_n[k] = NdcFromScreen(pnts_w[k], viewport);
                pnts_e[k] = EyeFromNdc   (pnts_n[k], matInvProjection);
            }

            UInt32 idx = j * numHorizontalTiles + i;

            frustums[idx].planes[0] = Plane(pEye, pnts_e[0], pnts_e[2]);   //   left plane
            frustums[idx].planes[1] = Plane(pEye, pnts_e[3], pnts_e[1]);   //  right plane
            frustums[idx].planes[2] = Plane(pEye, pnts_e[2], pnts_e[3]);   //    top plane
            frustums[idx].planes[3] = Plane(pEye, pnts_e[1], pnts_e[0]);   // bottom plane
        }
    }
}

/*--------------------------  Image Details -------------------------------*/

ImageTransitPtr ClusterShadingStage::create_image(
    UInt32 width, 
    UInt32 height, 
    UInt32 depth, 
    bool   allocate_memory)
{
    ImageTransitPtr image = Image::createLocal();
    image->set(
        GL_RG,                              // pixel format
        width,                              // width in pixel
        height,                             // height in pixel
        depth,                              // depth in pixel
        1,                                  // mipmap count
        1,                                  // frame count
        0.0,                                // frame delay
        NULL,                               // data
        Image::OSG_UINT32_IMAGEDATA,        // type
        allocate_memory,                    // allocate memory
        1                                   // side count
    );
    return image;
}

void ClusterShadingStage::update_image(
    Image* image,
    UInt32 width, 
    UInt32 height, 
    UInt32 depth, 
    bool   allocate_memory)
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
        Image::OSG_UINT32_IMAGEDATA,   // type
        allocate_memory,                    // allocate memory
        1                                   // side count
    );
}

void ClusterShadingStage::update_image_data(
    Image*               image, 
    const VecImageDataT& imageData)
{
    UInt8* data = image->editData();

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < imageData.size(); ++i)
    {
        UInt32 offset = imageData[i].first;
        UInt32 index  = imageData[i].second;

        ao = alignOffset(4, bo);
        *(reinterpret_cast<UInt32*>(data + ao)) = offset;
        bo = ao + sizeof(UInt32);

        ao = alignOffset(4, bo);
        *(reinterpret_cast<UInt32*>(data + ao)) = index;
        bo = ao + sizeof(UInt32);
    }
}

void ClusterShadingStage::write_image_data(
    UInt32            i, 
    UInt32            j, 
    UInt32            k, 
    const Vec3u&      dimensions, 
    const ImageDataT& data, 
    VecImageDataT&    imageData)
{
    OSG_ASSERT(i < dimensions.x());
    OSG_ASSERT(j < dimensions.y());
    OSG_ASSERT(k < dimensions.z());

    std::size_t idx = k * dimensions.x() * dimensions.y() + j * dimensions.x() + i;

    imageData[idx] = data;
}

TextureObjChunkTransitPtr 
ClusterShadingStage::create_texture_state(Image* image)
{
    TextureObjChunkTransitPtr texObjChunk = TextureObjChunk::createLocal();

    texObjChunk->setTarget(GL_TEXTURE_2D_ARRAY);
    texObjChunk->setScale(false);
    texObjChunk->setInternalFormat(GL_RG32UI);
    texObjChunk->setExternalFormat(GL_RG_INTEGER);
    texObjChunk->setMinFilter(GL_NEAREST);
    texObjChunk->setMagFilter(GL_NEAREST);
    texObjChunk->setImage(image);

    return texObjChunk;
}

void ClusterShadingStage::update_texture_state(TextureObjChunk* texObjChunk)
{
    texObjChunk->imageContentChanged();
}

TextureImageChunkTransitPtr 
ClusterShadingStage::create_texture_image_state(
    TextureObjChunk* texObjChunk,
    const GLenum     access)
{
    TextureImageChunkTransitPtr texImageChunk = TextureImageChunk::createLocal();
    texImageChunk->setTexture(texObjChunk);
    texImageChunk->setAccess(access);
    texImageChunk->setFormat(GL_RG32UI);
    texImageChunk->setLayer(-1);

    return texImageChunk;
}

void ClusterShadingStage::update_light_grid_image(
    const Vec4u& viewport,
    Image*       image,
    bool         allocate_memory)
{
    Real32 w = static_cast<Real32>(viewport[2]);
    Real32 h = static_cast<Real32>(viewport[3]);

    UInt32 numHorizontalTiles = UInt32(osgCeil(w / getTileSize()));
    UInt32 numVerticalTiles   = UInt32(osgCeil(h / getTileSize()));

    update_image(image , numHorizontalTiles, numVerticalTiles, getNumClusterZ(), allocate_memory);
}

/*-----------------------  Light Index Details ----------------------------*/

std::size_t 
ClusterShadingStage::calc_light_index_buffer_size(
    const VecLightIndexT& vIndexList)
{
    return sizeof(UInt32) * vIndexList.size();
}

std::vector<UInt8> 
ClusterShadingStage::create_light_index_buffer(
    const VecLightIndexT& vIndexList)
{
    std::size_t size = calc_light_index_buffer_size(vIndexList);

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    for (std::size_t i = 0; i < vIndexList.size(); ++i)
    {
        ao = alignOffset(4, bo);
        *(reinterpret_cast<UInt32*>(&buffer[0] + ao)) = vIndexList[i];
        bo = ao + sizeof(UInt32);
    }

    ao = alignOffset( 4, bo); bo = ao;    // padding

    return buffer;
}

ShaderStorageBufferObjStdLayoutChunkTransitPtr 
ClusterShadingStage::create_index_state(
    const VecLightIndexT& vIndexList)
{
    ShaderStorageBufferObjStdLayoutChunkTransitPtr ssbo = ShaderStorageBufferObjStdLayoutChunk::createLocal();

    std::vector<UInt8> buffer = create_light_index_buffer(vIndexList);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return ssbo;
}

ShaderStorageBufferObjStdLayoutChunkTransitPtr 
ClusterShadingStage::create_index_state(std::size_t sz)
{
    ShaderStorageBufferObjStdLayoutChunkTransitPtr ssbo = ShaderStorageBufferObjStdLayoutChunk::createLocal();

    std::vector<UInt8> buffer(sizeof(UInt32) * sz, 0);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return ssbo;
}

void ClusterShadingStage::update_index_state(
    ShaderStorageBufferObjStdLayoutChunk* ssbo, 
    const VecLightIndexT&                 vIndexList)
{
    if (ssbo) {
        std::vector<UInt8> buffer = create_light_index_buffer(vIndexList);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

void ClusterShadingStage::clear_index_state(
    ShaderStorageBufferObjStdLayoutChunk* ssbo, 
    std::size_t                           sz)
{
    if (ssbo) {
        std::vector<UInt8> buffer(sizeof(UInt32) * sz, 0);
        ssbo->editMFBuffer()->setValues(buffer);
    }
}

/*-------------------  Light Index Counter Details ------------------------*/

ShaderStorageBufferObjStdLayoutChunkTransitPtr
ClusterShadingStage::create_light_index_counter_state()
{
    ShaderStorageBufferObjStdLayoutChunkTransitPtr ssbo = ShaderStorageBufferObjStdLayoutChunk::createLocal();

    //
    // The counter compromises exactly one UInt32 element
    //
    std::vector<UInt8> buffer(sizeof(UInt32) * 1, 0);

    ssbo->editMFBuffer()->setValues(buffer);
    ssbo->setUsage(GL_DYNAMIC_DRAW);

    return ssbo;
}

void ClusterShadingStage::clear_light_index_counter_state(
    ShaderStorageBufferObjStdLayoutChunk* ssbo)
{
    if (ssbo) {
        //
        // The counter compromises exactly one UInt32 element
        //
        std::vector<UInt8> buffer(sizeof(UInt32) * 1, 0);

        ssbo->editMFBuffer()->setValues(buffer);
    }
}

/*----------------------  Dispatch Data Details ---------------------------*/

std::size_t ClusterShadingStage::calc_dispatch_data_buffer_size(
    const DispatchData& data)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    // Matrix matTransf;
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);

    // Vec4u  viewport;
    ao = alignOffset(16, bo); bo = ao + sizeof(Vec4u);

    // Vec2i  numTiles;
    ao = alignOffset( 8, bo); bo = ao + sizeof(Vec2i);

    // Padding at end
    ao = alignOffset(8, bo); bo = ao;

    return ao;
}

std::vector<UInt8>
ClusterShadingStage::create_dispatch_data_buffer(
    const DispatchData& data)
{
    std::size_t size = calc_dispatch_data_buffer_size(data);

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    // Matrix matTransf;
    ao = alignOffset(16, bo); 
    memcpy(&buffer[0] + ao, &data.matTransf[0][0], sizeof(Vec4f)); 
    bo = ao + sizeof(Vec4f);

    ao = alignOffset(16, bo); 
    memcpy(&buffer[0] + ao, &data.matTransf[1][0], sizeof(Vec4f)); 
    bo = ao + sizeof(Vec4f);

    ao = alignOffset(16, bo); 
    memcpy(&buffer[0] + ao, &data.matTransf[2][0], sizeof(Vec4f)); 
    bo = ao + sizeof(Vec4f);

    ao = alignOffset(16, bo); 
    memcpy(&buffer[0] + ao, &data.matTransf[3][0], sizeof(Vec4f)); 
    bo = ao + sizeof(Vec4f);

    // Vec4u  viewport;
    ao = alignOffset(16, bo); 
    memcpy(&buffer[0] + ao, &data.viewport[0], sizeof(Vec4u)); 
    bo = ao + sizeof(Vec4u);

    // Vec2i  numTiles;
    ao = alignOffset( 8, bo); 
    memcpy(&buffer[0] + ao, &data.numTiles[0], sizeof(Vec2i)); 
    bo = ao + sizeof(Vec2i);

    // Padding at end
    ao = alignOffset(8, bo); bo = ao;

    return buffer;
}

UniformBufferObjStd140ChunkTransitPtr
ClusterShadingStage::create_dispatch_data(const DispatchData& data)
{
    UniformBufferObjStd140ChunkTransitPtr ubo = UniformBufferObjStd140Chunk::createLocal();

    std::vector<UInt8> buffer = create_dispatch_data_buffer(data);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_DYNAMIC_DRAW);

    return ubo;
}

void ClusterShadingStage::update_dispatch_data(
    UniformBufferObjStd140Chunk* ubo,
    const DispatchData&          data)
{
    if (ubo) {
        std::vector<UInt8> buffer = create_dispatch_data_buffer(data);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

/*--------------------  Clustering Index Details --------------------------*/

std::size_t ClusterShadingStage::calc_clustering_data_buffer_size(
    const ClusteringData& data)
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    // Real32 zNear;  // positive near plane distance from eye zNear > 0
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    // Real32 zFar;   // positive  far plane distance from eye zFar > zNear > 0
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Real32 D;      // positive near plane offset D >= 0                            // for testing
    //ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Real32 nD;     // zNear + D : shader optimization
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Real32 lg_nD;  // log2(nD) : shader optimization
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Real32 a;      // precalculated factor (c-1)/log2(f/(n+D))
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Real32 b;      // precalculated factor log2(f/(n+D))/(c-1)
    ao = alignOffset( 4, bo); bo = ao + sizeof(Real32);

    //Int32  c;      // number of cluster planes                                     // for testing
    //ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);

    //Int32  c_1;    // number of cluster planes minus one : shader optimization
    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);

    //Vec2i  p_v;    // viewport corner points
    ao = alignOffset( 8, bo); bo = ao + sizeof(Vec2i);

    //Vec3i  n_c;    // number of clusters                                           // for testing
    //ao = alignOffset(16, bo); bo = ao + sizeof(Vec3i);
    //ao = alignOffset(16, bo); bo = ao;

    //bool   enabled;// cluster shading enabled
    ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);

    // Padding at end
    ao = alignOffset(4, bo); bo = ao;

    return ao;
}

std::vector<UInt8>
ClusterShadingStage::create_clustering_data_buffer(
    const ClusteringData& data)
{
    std::size_t size = calc_clustering_data_buffer_size(data);

    std::vector<UInt8> buffer(size);

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    // Real32 zNear;  // positive near plane distance from eye zNear > 0
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.zNear; bo = ao + sizeof(Real32);

    // Real32 zFar;   // positive  far plane distance from eye zFar > zNear > 0
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.zFar; bo = ao + sizeof(Real32);

    //Real32 D;      // positive near plane offset D >= 0                            // for testing
    //ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.D; bo = ao + sizeof(Real32);

    //Real32 nD;     // zNear + D : shader optimization
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.nD; bo = ao + sizeof(Real32);

    //Real32 lg_nD;  // log2(nD) : shader optimization
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.lg_nD; bo = ao + sizeof(Real32);

    //Real32 a;      // precalculated factor (c-1)/log2(f/(n+D))
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.a; bo = ao + sizeof(Real32);

    //Real32 b;      // precalculated factor log2(f/(n+D))/(c-1)
    ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = data.b; bo = ao + sizeof(Real32);

    //Int32  c;      // number of cluster planes                                     // for testing
    //ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = data.c; bo = ao + sizeof(Int32);

    //Int32  c_1;    // number of cluster planes minus one : shader optimization
    ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = data.c_1; bo = ao + sizeof(Int32);

    //Vec2i  p_v;    // viewport corner points
    ao = alignOffset( 8, bo); memcpy(&buffer[0] + ao, &data.p_v[0], sizeof(Vec2i)); bo = ao + sizeof(Vec2i);

    //Vec3i  n_c;    // number of clusters                                           // for testing
    //ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &data.n_c[0], sizeof(Vec3i)); bo = ao + sizeof(Vec3i);
    //ao = alignOffset(16, bo); bo = ao;

    //bool   enabled;// cluster shading enabled
    ao = alignOffset( 4, bo); *(reinterpret_cast<bool*>(&buffer[0] + ao)) = data.enabled; bo = ao + sizeof(Int32);

    // Padding at end
    ao = alignOffset(4, bo); bo = ao;

    return buffer;
}

UniformBufferObjStd140ChunkTransitPtr
ClusterShadingStage::create_clustering_data(
    const ClusteringData& data)
{
    UniformBufferObjStd140ChunkTransitPtr ubo = UniformBufferObjStd140Chunk::createLocal();

    std::vector<UInt8> buffer = create_clustering_data_buffer(data);

    ubo->editMFBuffer()->setValues(buffer);
    ubo->setUsage(GL_STATIC_DRAW);

    return ubo;
}

void ClusterShadingStage::update_clustering_data(
    UniformBufferObjStd140Chunk* ubo,
    const ClusteringData& data)
{
    if (ubo) {
        std::vector<UInt8> buffer = create_clustering_data_buffer(data);
        ubo->editMFBuffer()->setValues(buffer);
    }
}

/*-------------------------  Cluster Access -------------------------------*/

UInt32 ClusterShadingStage::cluster_k(
    Real32 z_e,    // eye space z-position, z_e < 0
    Real32 n,      // near plane distance from viewer n > 0
    Real32 f,      //  far plane distance from viewer f > n > 0
    Real32 D,      // near plane offset
    UInt32 c)      // number of cluster planes
{
    if (z_e >= -(n+D)) return 0;
    if (z_e <= -f)     return c-1;

    Real32 s = 1 + ((c-1) / log2(f/(n+D))) * (log2(-z_e) - log2(n+D));
    UInt32 k = UInt32(osgFloor(s));

    return osgClamp(0U, k, c-1);
}

Real32 ClusterShadingStage::cluster_z(
    UInt32 k,      // cluster coordinate, 0 <= k <= c
    Real32 n,      // near plane distance from viewer n > 0
    Real32 f,      //  far plane distance from viewer f > n > 0
    Real32 D,      // near plane offset
    UInt32 c)      // number of cluster planes
{
    if (k == 0)  return -n;
    if (k > c-1) return -f;

    Real32 z_e = -(n+D)*exp2(static_cast<Real32>(k-1) * (log2(f/(n+D))/(c-1)));
    return z_e;
}

UInt32 ClusterShadingStage::cluster_k(
    Real32 z_e,    // eye space z-position, z_e < 0
    Real32 nD,     // near plane distance from viewer plus offset, nD = n+D with n > 0, D > 0
    Real32 lg_nD,  // log2(nD)
    Real32 f,      //  far plane distance from viewer f > n > 0
    Real32 a,      // factor (c-1)/log2(f/nD)
    UInt32 c_1)    // number of cluster planes
{
    if (z_e >= -nD) return 0;
    if (z_e <= -f)  return c_1;

    Real32 s = 1 + a * (log2(-z_e) - lg_nD);
    UInt32 k = UInt32(s);
    return osgClamp(0U, k, c_1);
}

Real32 ClusterShadingStage::cluster_z(
    UInt32 k,      // cluster coordinate, 0 <= k <= c
    Real32 n,      // near plane distance from viewer n > 0
    Real32 f,      //  far plane distance from viewer f > n > 0
    Real32 nD,     // near plane distance from viewer plus offset, nD = n+D with n > 0, D > 0
    Real32 b,      // factor log2(f/(n+D))/(c-1)
    UInt32 c_1)    // number of cluster planes
{
    if (k == 0)  return -n;
    if (k > c_1) return -f;

    Real32 z_e = -nD*exp2(static_cast<Real32>(k-1) * b);
    return z_e;
}

/*--------------------------  Computation ---------------------------------*/

void ClusterShadingStage::create_computation(
    ClusterShadingStageData* pData)
{
    create_frustum_computation      (pData);
    create_light_culling_computation(pData);

    NodeUnrecPtr frustNode = Node::createLocal();
    NodeUnrecPtr  cullNode = Node::createLocal();

    if (getCalcFrustumsOnCPU() || getCullLighsOnCPU())
    {
        frustNode->setCore(Group::createLocal());
    }
    else
    {
        frustNode->setCore(getFrustAlgoElement());
    }

    if (getCullLighsOnCPU())
    {
        cullNode->setCore(Group::createLocal());
    }
    else
    {
        cullNode->setCore(getCullAlgoElement());
    }

    frustNode->addChild(cullNode);

    frustNode->editVolume().setInfinite();
    frustNode->editVolume().setStatic  ();

    cullNode->editVolume().setInfinite();
    cullNode->editVolume().setStatic  ();

    setFrustNode(frustNode);
    setCullNode ( cullNode);
}

void ClusterShadingStage::update_computation(
    ClusterShadingStageData* pData)
{
    //
    // Adpat the stage data chunk material
    //
    if (!getCalcFrustumsOnCPU())
    {
        ChunkMaterial* pFrustChunkMat = getFrustCompShaderAlgo()->getChunkMaterial();
        if (pFrustChunkMat != pData->getFrustChunkMat())
        {
            getFrustCompShaderAlgo()->setChunkMaterial(pData->getFrustChunkMat());
        }
    }

    if (!getCullLighsOnCPU())
    {
        ChunkMaterial* pCullChunkMat  = getCullCompShaderAlgo() ->getChunkMaterial();
        if (pCullChunkMat != pData->getCullChunkMat())
        {
            getCullCompShaderAlgo()->setChunkMaterial(pData->getCullChunkMat());
        }
    }
/*
    //
    // Nothing to do here, because we always recreate the stage if the CPU/GPU modes
    // change.
    //

    //
    // Setup the computation cores
    //
    if (getCalcFrustumsOnCPU() || getCullLighsOnCPU())
    {
        if (getFrustNode()->getCore()->getType() != Group::getClassType())
        {
            getFrustNode()->setCore(Group::createLocal());
        }
    }
    else
    {
        if (getFrustNode()->getCore() != getFrustAlgoElement())
        {
            getFrustNode()->setCore(getFrustAlgoElement());
        }
    }

    if (getCullLighsOnCPU())
    {
        if (getCullNode()->getCore()->getType() != Group::getClassType())
        {
            getCullNode()->setCore(Group::createLocal());
        }
    }
    else
    {
        if (getCullNode()->getCore() != getCullAlgoElement())
        {
            getCullNode()->setCore(getCullAlgoElement());
        }
    }
*/
}

/*----------------------  Frustum Computation -----------------------------*/

void ClusterShadingStage::create_frustum_computation(
    ClusterShadingStageData* pData)
{
    OSG_ASSERT(pData);

    ShaderProgramUnrecPtr shader = ShaderProgram::createLocal();

    shader->setShaderType(GL_COMPUTE_SHADER);
    shader->setProgram(
                        pData->getIsOrthographicCamera() 
                            ? get_ortho_frustum_cp_program() 
                            : get_persp_frustum_cp_program()
                      );

    shader->addUniformBlock      ("DispatchData", getDispatchDataBindingPnt());
    shader->addShaderStorageBlock("Frustums",     getFrustumBindingPnt());

    ComputeShaderChunkUnrecPtr chunk = ComputeShaderChunk::createLocal();
    chunk->addComputeShader(shader);
    chunk->setVariables(shader->getVariables());

    ComputeShaderAlgorithmUnrecPtr algorithm = ComputeShaderAlgorithm::createLocal();
    algorithm->setUseMemoryBarrier(true);
    algorithm->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    algorithm->setComputeShader(chunk);

    Vec3i work_group_count(1,1,1);
    algorithm->setDispatchConfig(work_group_count);
    algorithm->setChunkMaterial(pData->getFrustChunkMat());

    AlgorithmComputeElementUnrecPtr element = AlgorithmComputeElement::createLocal();
    element->setAlgorithm(algorithm);

    setFrustAlgoElement(element);
    setFrustCompShaderAlgo(algorithm);
}

/*-------------------  Light Culling Computation --------------------------*/

void ClusterShadingStage::create_light_culling_computation(
    ClusterShadingStageData* pData)
{
    OSG_ASSERT(pData);

    ShaderProgramUnrecPtr shader = ShaderProgram::createLocal();
    shader->setShaderType(GL_COMPUTE_SHADER);
    shader->setProgram(get_light_culling_cp_program());

    shader->addShaderStorageBlock(getMultiLightChunk()->getLightBlockName().c_str(), getLightBindingPnt());
    shader->addUniformBlock      ("DispatchData",                               getDispatchDataBindingPnt());
    shader->addUniformBlock      (getClusteringDataBlockName().c_str(),         getClusterDataBindingPnt());
    shader->addShaderStorageBlock("Frustums",                                   getFrustumBindingPnt());
    shader->addShaderStorageBlock(getAffectedLightIndexListBlockName().c_str(), getAffectedLightIndexListBindingPnt());
    shader->addShaderStorageBlock(getLightIndexListBlockName().c_str(),         getLightIndexListBindingPnt());
    shader->addShaderStorageBlock("LightIndexCounter",                          getLightIndexCounterBindingPnt());

    ComputeShaderChunkUnrecPtr chunk = ComputeShaderChunk::createLocal();
    chunk->addComputeShader(shader);
    chunk->setVariables(shader->getVariables());

    ComputeShaderAlgorithmUnrecPtr algorithm = ComputeShaderAlgorithm::createLocal();
    algorithm->setUseMemoryBarrier(true);
    algorithm->setMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    algorithm->setComputeShader(chunk);

    Vec3i work_group_count(1,1,1);
    algorithm->setDispatchConfig(work_group_count);
    algorithm->setChunkMaterial(pData->getCullChunkMat());

    AlgorithmComputeElementUnrecPtr element = AlgorithmComputeElement::createLocal();
    element->setAlgorithm(algorithm);

    setCullAlgoElement(element);
    setCullCompShaderAlgo(algorithm);
}

/*------------------------- Fragment Shader -------------------------------*/

void ClusterShadingStage::create_fragment_shader(ClusterShadingStageData* pData)
{
    ShaderProgramChunkUnrecPtr progChunk  = ShaderProgramChunk::createLocal();

    ShaderProgramUnrecPtr shader = ShaderProgram::createLocal();
    shader->setShaderType(GL_FRAGMENT_SHADER);
    shader->setProgram(get_fragment_cp_program());

    shader->addShaderStorageBlock(getMultiLightChunk()->getLightBlockName().c_str(), getLightBindingPnt());
    shader->addShaderStorageBlock(getAffectedLightIndexListBlockName().c_str(),      getAffectedLightIndexListBindingPnt());
    shader->addShaderStorageBlock(getLightIndexListBlockName().c_str(),              getLightIndexListBindingPnt());
    shader->addUniformBlock      (getClusteringDataBlockName().c_str(),              getClusterDataBindingPnt());

    progChunk->addShader(shader);

    setShaderProgChunk(progChunk);
}

/*------------------ Update Dispatch Configurations -----------------------*/

void ClusterShadingStage::update_dispatch_config_frustums(
    ClusterShadingStageData* pData,
    const Vec4u&             viewport,
    const Matrix&            matInvProjection)
{
//    Real32 x_v = static_cast<Real32>(viewport[0]);
//    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    const Vec3i work_group_size = Vec3i(getBlockSize(), getBlockSize(), 1);
    const UInt32 tile_size      = getTileSize();

    Real32 numHorizontalTiles = osgCeil(w / tile_size);
    Real32 numVerticalTiles   = osgCeil(h / tile_size);

    DispatchData data;
    data.matTransf = matInvProjection;
    data.viewport  = viewport;
    data.numTiles  = Vec2i(Int32(numHorizontalTiles), Int32(numVerticalTiles));

    VecFrustumsT vFrustums(data.numTiles.x() * data.numTiles.y());
    update_frustum_state(pData->getFrustumsSSBOChunk(),    vFrustums);
    update_dispatch_data(pData->getFrustDispDatUBOChunk(), data);

    UInt32 szX = UInt32(osgCeil(numHorizontalTiles / work_group_size.x()));
    UInt32 szY = UInt32(osgCeil(  numVerticalTiles / work_group_size.y()));
    UInt32 szZ = 1;

    Vec3i work_group_count = Vec3i(szX, szY, szZ);
    getFrustCompShaderAlgo()->setDispatchConfig(work_group_count);
}

void ClusterShadingStage::update_dispatch_config_cull_lights(
    ClusterShadingStageData* pData,
    const Vec4u&             viewport,
    const Matrix&            matViewing)
{
//    Real32 x_v = static_cast<Real32>(viewport[0]);
//    Real32 y_v = static_cast<Real32>(viewport[1]);
    Real32 w   = static_cast<Real32>(viewport[2]);
    Real32 h   = static_cast<Real32>(viewport[3]);

    const Vec3i work_group_size = Vec3i(getBlockSize(), getBlockSize(), 1);
    const UInt32 tile_size      = getTileSize();

    Real32 numHorizontalTiles = osgCeil(w / tile_size);
    Real32 numVerticalTiles   = osgCeil(h / tile_size);

    DispatchData data;
    data.matTransf = matViewing;
    data.viewport  = viewport;
    data.numTiles  = Vec2i(Int32(numHorizontalTiles), Int32(numVerticalTiles));

    update_dispatch_data(pData->getCullDispDatUBOChunk(), data);

    Vec3i work_group_count = Vec3i(numHorizontalTiles, numVerticalTiles, getNumClusterZ());
    getCullCompShaderAlgo()->setDispatchConfig(work_group_count);
}

/*-------------------  Calculate Affected Lights --------------------------*/

void ClusterShadingStage::calc_affected_lights(
    const Matrix&          matEyeFromWorld,
    FrustumVolume          volViewFrustum,
    VecLightIndexT&        vecAffectedLights,
    VecLightEyeSpaceDataT& vecEyeSpaceData)
{
    //
    // We test the light against the view frustum to get only affected lights.
    // Since all of out tests happens in eye space we must transform the world 
    // space view frustum to eye space first.
    //
    volViewFrustum.transform(matEyeFromWorld);

    Frustum frustum;
    frustum.planes[0] = volViewFrustum.getPlane(FrustumVolume::PLANE_LEFT);
    frustum.planes[1] = volViewFrustum.getPlane(FrustumVolume::PLANE_RIGHT);
    frustum.planes[2] = volViewFrustum.getPlane(FrustumVolume::PLANE_TOP);
    frustum.planes[3] = volViewFrustum.getPlane(FrustumVolume::PLANE_BOTTOM);

    Pnt3f nlt = volViewFrustum.getCorner(FrustumVolume::NEAR_LEFT_TOP);
    Pnt3f flt = volViewFrustum.getCorner(FrustumVolume:: FAR_LEFT_TOP);

    Real32 n = nlt.z();
    Real32 f = flt.z();

    UInt32 numLights = getMultiLightChunk()->numLights();

    //
    // We do need the eye space positions and directions of the lights 
    // for our test view frustum and cluster frustum tests. In order to
    // calculate them only once we remember them in a vector.
    //
    if (vecEyeSpaceData.size() != numLights)
        vecEyeSpaceData.resize(numLights);

    for (UInt32 i = 0; i < numLights; ++i)
    {
        bool affected = false;

        if (getMultiLightChunk()->getEnabled(i))
        {
            switch (getMultiLightChunk()->getType(i))
            {
                case MultiLight::DIRECTIONAL_LIGHT:
                {
                    affected = true;
                }
                break;
                case MultiLight::POINT_LIGHT:
                case MultiLight::CINEMA_LIGHT:
                {
                    transform_to_eye_space(
                        matEyeFromWorld, 
                        getMultiLightChunk()->getBeacon(i),
                        getMultiLightChunk()->getPosition(i),
                        getMultiLightChunk()->getDirection(i),
                        vecEyeSpaceData[i].position,
                        vecEyeSpaceData[i].direction);

                    if (point_light_inside_frustum(
                                vecEyeSpaceData[i].position, 
                                getMultiLightChunk()->getRangeCutOff(i), 
                                frustum, n, f))
                    {
                        affected = true;
                    }
                }
                break;
                case MultiLight::SPOT_LIGHT:
                {
                    transform_to_eye_space(
                        matEyeFromWorld, 
                        getMultiLightChunk()->getBeacon(i),
                        getMultiLightChunk()->getPosition(i),
                        getMultiLightChunk()->getDirection(i),
                        vecEyeSpaceData[i].position,
                        vecEyeSpaceData[i].direction);

                    if (spot_light_inside_frustum(
                                vecEyeSpaceData[i].position, 
                                vecEyeSpaceData[i].direction, 
                                getMultiLightChunk()->getRangeCutOff(i),
                                getMultiLightChunk()->getSpotlightAngle(i),
                                frustum, n, f))
                    {
                        affected = true;
                    }
                }
                break;
            }
        }

        if (affected)
            vecAffectedLights.push_back(UInt32(i));
    }
}

void ClusterShadingStage::transform_to_eye_space(
    Matrix        matEyeFromWorld,
    Node*         beacon,
    const Pnt3f&  position_bs,
    const Vec3f&  direction_bs,
    Pnt3f&        position_es,
    Vec3f&        direction_es)
{
    Matrix matWsFromBS;

    if(beacon != NULL)
    {
        beacon->getToWorld(matWsFromBS);
    }
    else
    {
        matWsFromBS.setIdentity();
    }

    matEyeFromWorld.mult(matWsFromBS);                  // matEsFromBs
    matEyeFromWorld.multFull( position_bs,  position_es);
    matEyeFromWorld.multFull(direction_bs, direction_es);
}

bool ClusterShadingStage::point_light_inside_frustum(
    const Pnt3f&   position_es,
    Real32         range,
    const Frustum& frustum, 
    Real32         n, 
    Real32         f)
{
    Sphere sphere;
    sphere.c = position_es;
    sphere.r = range;

    return SphereInsideFrustum(sphere, frustum, n, f);
}

bool ClusterShadingStage::spot_light_inside_frustum(
    const Pnt3f&   position_es,
    const Vec3f&   direction_es,
    Real32         range,
    Real32         spotlightAngle,
    const Frustum& frustum, 
    Real32         n, 
    Real32         f)
{
    Cone cone;
    cone.T = position_es;
    cone.d = direction_es;
    cone.h = range;
    cone.r = osgTan( osgDegree2Rad(spotlightAngle)) * cone.h;

    return ConeInsideFrustum(cone, frustum, n, f);
}

/*-----------------------  CPU Light Culling ------------------------------*/

inline std::size_t ClusterShadingStage::frustum_accessor(
    const UInt32 i, 
    const UInt32 j, 
    const Vec3u& dimensions)
{
    return j * dimensions.x()  + i;
}

void ClusterShadingStage::cull_lights(
    ClusterShadingStageData*     pData,              // in contains the CPU calculated tile frustum planes
    const VecLightIndexT&        vecAffectedLights,  // in the lights that are actually contributing to the view frustum shading
    const VecLightEyeSpaceDataT& vecEyeSpaceData,    // in the precalculated light eye space positions and directions
    const Vec3u&                 dimensions,         // in the cluster dimentsions
    const Matrix&                matEyeFromWorld,    // in transform from world to eye space
    Real32                       zNear,              // in distance of near plane from eye point
    Real32                       zFar,               // in distance of far  plane from eye point
    Real32                       D,                  // in distance offset for near plane
    VecImageDataT&               gridData,           // out the raw grid data
    VecLightIndexT&              lightIndexList)     // out the index list
{
    gridData.clear();
    lightIndexList.clear();

    gridData.resize(dimensions.x() * dimensions.y() * dimensions.z());

    UInt32 c_1    = dimensions.z()-1;
    Real32 zNearD = zNear + D;
    Real32 b      = log2(zFar/zNearD)/(c_1);

    for (UInt32 k = 0; k < dimensions.z(); ++k)
    {
        Real32 n = cluster_z(k,   zNear, zFar, zNearD, b, c_1);
        Real32 f = cluster_z(k+1, zNear, zFar, zNearD, b, c_1);

        for (UInt32 j = 0; j < dimensions.y(); ++j)
        {
            for (UInt32 i = 0; i < dimensions.x(); ++i)
            {
                std::size_t tile = frustum_accessor(i, j, dimensions);
                Frustum frustum = getFrustum(pData, static_cast<UInt32>(tile));

                UInt32 light_count = 0;
                UInt32 light_start_offset = UInt32(lightIndexList.size());

                std::size_t num_affected_lights = vecAffectedLights.size();

                for (std::size_t l = 0; l < num_affected_lights; ++l)
                {
                    UInt32 light_index = vecAffectedLights[l];

                    if (getMultiLightChunk()->getEnabled(light_index))
                    {
                        switch (getMultiLightChunk()->getType(light_index))
                        {
                            case MultiLight::DIRECTIONAL_LIGHT:
                            {
                                light_count += 1;
                                lightIndexList.push_back(light_index);
                            }
                            break;
                            case MultiLight::POINT_LIGHT:
                            case MultiLight::CINEMA_LIGHT:
                            {    
                                if (
                                        point_light_inside_frustum(
                                            vecEyeSpaceData[light_index].position, 
                                            getMultiLightChunk()->getRangeCutOff(light_index), 
                                            frustum, n, f)
                                   )
                                {
                                    light_count += 1;
                                    lightIndexList.push_back(light_index);
                                }
                            }
                            break;
                            case MultiLight::SPOT_LIGHT:
                            {    
                                if (
                                        spot_light_inside_frustum(
                                            vecEyeSpaceData[light_index].position, 
                                            vecEyeSpaceData[light_index].direction, 
                                            getMultiLightChunk()->getRangeCutOff(light_index),
                                            getMultiLightChunk()->getSpotlightAngle(light_index),
                                            frustum, n, f)
                                   )
                                {
                                    light_count += 1;
                                    lightIndexList.push_back(light_index);
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

/*--------------------  Compute Shader Programs ---------------------------*/

std::string ClusterShadingStage::get_persp_frustum_cp_program()
{
    using namespace std;

    const Vec3i work_group_size = Vec3i(getBlockSize(), getBlockSize(), 1);
    const UInt32 tile_size      = getTileSize();

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "//"
    << endl << "// matTransf is the inverse projection matrix"
    << endl << "//"
    << getDispatchProgSnippet()
    << endl << ""
    << getFrustumProgSnippet()
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

std::string ClusterShadingStage::get_ortho_frustum_cp_program()
{
    using namespace std;

    const Vec3i work_group_size = Vec3i(getBlockSize(), getBlockSize(), 1);
    const UInt32 tile_size      = getTileSize();

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << endl << "//"
    << endl << "// matTransf is the inverse projection matrix"
    << endl << "//"
    << getDispatchProgSnippet()
    << endl << ""
    << getFrustumProgSnippet()
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

std::string ClusterShadingStage::get_light_culling_cp_program()
{
    using namespace std;

    const Vec3i work_group_size = Vec3i(getBlockSize(), getBlockSize(), 1);
    const UInt32 tile_size      = getTileSize();

    stringstream ost;

    ost     << "#version 430 compatibility"
    << endl << ""
    << endl << "#extension GL_ARB_shader_image_load_store: enable"
    << endl << ""
    << endl << "layout (local_size_x = " << work_group_size.x() 
                  << ", local_size_y = " << work_group_size.y() 
                  << ", local_size_z = " << work_group_size.z() << ") in;"
    << endl << ""
    << endl << "const int tile_size = " << tile_size << ";"
    << endl << ""
    << getMultiLightChunk()->getLightProgSnippet()
    << endl << ""
    << endl << "//"
    << endl << "// matTransf is the world to view matrix"
    << endl << "//"
    << getDispatchProgSnippet()
    << endl << ""
    << getClusteringProgSnippet(false)
    << endl << ""
    << endl << "//"
    << endl << "// We get the pre calculated list of frustums for each tile."
    << endl << "// The cluster frustum is accessed with the help of the"
    << endl << "// gl_WorkGroupID variable:"
    << endl << "//"
    << endl << "//      idx = j * numHorizontalTiles + i"
    << endl << "//      idx = gl_WorkGroupID.y * dispatchData.numTiles.x  + gl_WorkGroupID.x"
    << endl << "//"
    << getFrustumProgSnippet()
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
    << getLightIndexProgSnippet()
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
    << endl << "    return ivec3(gl_WorkGroupID);"
    << endl << "}"
    << endl << ""
    << endl << "//"
    << endl << "// Helper function that provides the tile frustum index of the current cluster"
    << endl << "//"
    << endl << "int frustumAccessor()"
    << endl << "{"
    << endl << "    return int(gl_WorkGroupID.y) * dispatchData.numTiles.x  + int(gl_WorkGroupID.x);"
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
    << endl << "    if (gl_LocalInvocationIndex == 0)"
    << endl << "    {"
    << endl << "        sharedFrustum    = frustums.frustum[frustumAccessor()];"
    << endl << "        sharedFrustumZ   = getClusterDepth();"
    << endl << "        sharedLightCount = 0;"
    << endl << "    }"
    << endl << ""
    << endl << "    memoryBarrierShared();  // Ensure change to sharedXXX is visible in other invocations"
    << endl << "    barrier();              // Stall until every thread reaches this point"
    << endl << ""
    << endl << "    //"
    << endl << "    // We iterate over all affected lights whereby splitting the lights into subsets for each thread."
    << endl << "    // For each light we test it against the current frustum and if it is inside of the frustum, we add"
    << endl << "    // the light to the group shared list of lights contributing to the current cluster corresponding to"
    << endl << "    // the work group."
    << endl << "    //"
    << endl << "    for (uint i = gl_LocalInvocationIndex; i < " << getAffectedLightIndexListVariableName() << ".idx.length(); i += gl_WorkGroupSize.x * gl_WorkGroupSize.y * gl_WorkGroupSize.z)"
    << endl << "    {"
    << endl << "        uint light_index = " << getAffectedLightIndexListVariableName() << ".idx[i];"
    << endl << ""
    << endl << "        if (" << getMultiLightChunk()->getLightVariableName() << ".light[light_index].enabled)"
    << endl << "        {"
    << endl << "            Light light = " << getMultiLightChunk()->getLightVariableName() << ".light[light_index];"
    << endl << ""
    << endl << "            switch (light.type)"
    << endl << "            {"
    << endl << "                case DIRECTIONAL_LIGHT:"
    << endl << "                {"
    << endl << "                    appendLight(light_index);"
    << endl << "                }"
    << endl << "                break;"
    << endl << ""
    << endl << "                case POINT_LIGHT:"
    << endl << "                case CINEMA_LIGHT:"
    << endl << "                {"
    << endl << "                    vec4 position = dispatchData.matTransf * vec4(light.position, 1.0);"
    << endl << ""
    << endl << "                    Sphere sphere = { position.xyz, light.rangeCutOff };"
    << endl << ""
    << endl << "                    if (sphereInsideFrustum(sphere, sharedFrustum, sharedFrustumZ.x, sharedFrustumZ.y))"
    << endl << "                    {"
    << endl << "                        appendLight(light_index);"
    << endl << "                    }"
    << endl << "                }"
    << endl << "                break;"
    << endl << ""
    << endl << "                case SPOT_LIGHT:"
    << endl << "                {"
    << endl << "                    vec4 position  = dispatchData.matTransf * vec4(light.position,  1.0);"
    << endl << "                    vec4 direction = dispatchData.matTransf * vec4(light.direction, 0.0);"
    << endl << ""
    << endl << "                    float radius = tan(light.spotlightAngle) * light.rangeCutOff;"
    << endl << "                    Cone cone = { position.xyz, light.rangeCutOff, direction.xyz, radius };"
    << endl << ""
    << endl << "                    if (coneInsideFrustum(cone, sharedFrustum, sharedFrustumZ.x, sharedFrustumZ.y))"
    << endl << "                    {"
    << endl << "                        appendLight(light_index);"
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
    << endl << "        uint num_indices = " << getLightIndexListVariableName() << ".idx.length();"
    << endl << "        if (sharedLightStartOffset + sharedLightCount >= num_indices)"
    << endl << "            data = uvec4(0,0,0,0);"
    << endl << ""
    << endl << "        imageStore(" << getLightGridVariableName() << ", clusterAccessor(), data);"
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
    << endl << "    uint num_indices = " << getLightIndexListVariableName() << ".idx.length();"
    << endl << ""
    << endl << "    for (uint i = gl_LocalInvocationIndex; i < sharedLightCount; i += gl_WorkGroupSize.x * gl_WorkGroupSize.y * gl_WorkGroupSize.z)"
    << endl << "    {"
    << endl << "        if (sharedLightStartOffset + i < num_indices)"
    << endl << "            " << getLightIndexListVariableName() << ".idx[sharedLightStartOffset + i] = sharedLightIndexList[i];"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    << endl;

    return ost.str();
}

std::string ClusterShadingStage::get_fragment_cp_program()
{
    using namespace std;

    stringstream ost;

    ost
    << endl << ""
    //<< getMultiLightChunk()->getLightProgSnippet()
    //<< endl << ""
    //<< getClusteringProgSnippet()
    //<< endl << ""
    //<< getLightIndexProgSnippet()
    //<< endl << ""
    << endl;

    return ost.str();
}

/*--------------------  Shader Program Snippets ---------------------------*/

std::string ClusterShadingStage::getDispatchProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "layout (std140) uniform DispatchData"
    << endl << "{"
    << endl << "    mat4  matTransf;"
    << endl << "    uvec4 viewport;"
    << endl << "    ivec2 numTiles;"
    << endl << "} dispatchData;"
    << endl
    ;

    return ost.str();
}

std::string ClusterShadingStage::getClusteringProgSnippet(bool is_frag_shader) const
{
    using namespace std;

    const UInt32 tile_size = getTileSize();

    stringstream ost;
   
    if (is_frag_shader)
    {
        ost
        << endl << "const int tile_size = " << tile_size << ";"
        << endl << ""
        ;
    }
    ost
    << endl << "//"
    << endl << "// We write our results into the global light grid with:"
    << endl << "//      imageStore(" << getLightGridVariableName() << ", ivec3(i,j,k), uvec4(o,c,0,0))"
    << endl << "// and read it back with:"
    << endl << "//      imageLoad(" << getLightGridVariableName() << ", ivec3(i,j,k)).xy"
    << endl << "// were:"
    << endl << "//          i,j,k  define the cluster index"
    << endl << "//          o      is the offset from the beginning of the global light index list for the cluster"
    << endl << "//          c      is the number if lights that are to be used for the cluster"
    << endl << "//"
    << endl << "layout(binding = " << getLightGridBindingPnt() << ", rg32ui) uniform uimage2DArray " << getLightGridVariableName() << ";"
    << endl << ""
    << endl << "//"
    << endl << "// The data we need to calc the cluster depth values from the cluster key k"
    << endl << "//"
    << endl << "layout (std140) uniform " << getClusteringDataBlockName()
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
    << endl << "    bool  enabled;// cluster shadingd enabled"
    << endl << "} " << getClusteringDataVariableName() << ";"
    << endl << ""
    << endl << "//"
    << endl << "// cluster_z calculates the cluster eye space z from the cluster key k value"
    << endl << "//      z_e = cluster_z(k, ...) with z_e in [-n, -f]"
    << endl << "//"
    << endl << "// Formular:"
    << endl << "//      z_e = -n                                              if k == 0"
    << endl << "//      z_e = -(n+D) * exp2( (k-1)*(log2(f/(n+D))/(c-1)) )    else"
    << endl << "//      z_e = -f                                              if k > c-1"
    << endl << "//"
    ;
    if (!is_frag_shader)
    {
        ost
        //<< endl << "float cluster_z("
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
        << endl << "// Helper function that provides the tile frustum index of the current cluster"
        << endl << "//"
        << endl << "vec2 getClusterDepth()"
        << endl << "{"
        << endl << "    return vec2(cluster_z(gl_WorkGroupID.z,   " 
                                                << getClusteringDataVariableName() << ".zNear, " 
                                                << getClusteringDataVariableName() << ".zFar, " 
                                                << getClusteringDataVariableName() << ".nD, " 
                                                << getClusteringDataVariableName() << ".b, " 
                                                << getClusteringDataVariableName() << ".c_1),"
        << endl << "                cluster_z(gl_WorkGroupID.z+1, " 
                                                << getClusteringDataVariableName() << ".zNear, " 
                                                << getClusteringDataVariableName() << ".zFar, " 
                                                << getClusteringDataVariableName() << ".nD, " 
                                                << getClusteringDataVariableName() << ".b, " 
                                                << getClusteringDataVariableName() << ".c_1));"
        << endl << "}"
        ;
    }
    else
    {
        ost
        << endl << "//"
        << endl << "// cluster_k and cluster_k_verbose calculates the cluster key from the eye space z value"
        << endl << "//      k = cluster_k(z_e, ...) with k in [0, c["
        << endl << "//"
        << endl << "// Formular:"
        << endl << "//      k = 0                                               if z_e >= -(n+D)"
        << endl << "//      k = 1 + (c-1) * log2(z_e/-(n+D)) / log2(f/(n+D))    else"
        << endl << "//      k = c-1                                             if z_e <= -f"
        << endl << "//"
        //<< endl << "int cluster_k("
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
        << endl << "    in const vec2  p_w,"
        << endl << "    in const float z_e)"
        << endl << "{"
        << endl << "    ivec2 q_w = ivec2(p_w - vec2(0.5, 0.5));"
        << endl << "    int k = cluster_k(z_e, " 
                                        << getClusteringDataVariableName() << ".nD, " 
                                        << getClusteringDataVariableName() << ".lg_nD, " 
                                        << getClusteringDataVariableName() << ".zFar, " 
                                        << getClusteringDataVariableName() << ".a, " 
                                        << getClusteringDataVariableName() << ".c_1);"
        << endl << "    ivec2 p = (q_w - " << getClusteringDataVariableName() << ".p_v) / tile_size;"
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
        << endl << "    return imageLoad(" << getLightGridVariableName() << ", accessor).xy;"
        << endl << "}"
        ;
    }
    ost
    << endl
    ;

    return ost.str();
}

std::string ClusterShadingStage::getFrustumProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
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
    << endl << "// The left, right, top and bottom planes of the tile frustum"
    << endl << "//"
    << endl << "struct Frustum"
    << endl << "{"
    << endl << "    Plane planes[4];"
    << endl << "};"
    << endl << ""
    << endl << "layout (std430) buffer Frustums"
    << endl << "{"
    << endl << "    Frustum frustum[];"
    << endl << "} frustums;"
    << endl
    ;

    return ost.str();
}

std::string ClusterShadingStage::getLightIndexProgSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "// Index list into the global light list that contain only"
    << endl << "// those lights that affect shading in the view frustum."
    << endl << "//"
    << endl << "layout (std430) buffer " << getAffectedLightIndexListBlockName()
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} " << getAffectedLightIndexListVariableName() << ";"
    << endl << ""
    << endl << "//"
    << endl << "// Index list into the global light list. All sequences of lights"
    << endl << "// contributing to shading of the individal clusters are assembled"
    << endl << "// in this list. The start position and number of lights for each"
    << endl << "// cluster are provided by the light grid image."
    << endl << "//"
    << endl << "layout (std430) buffer " << getLightIndexListBlockName()
    << endl << "{"
    << endl << "    uint idx[];"
    << endl << "} " << getLightIndexListVariableName() << ";"
    << endl
    ;

    return ost.str();
}

std::string ClusterShadingStage::getFragmentProgramSnippet() const
{
    using namespace std;

    stringstream ost;

    ost
    << endl << "//"
    << endl << "//-- ClusterShadingStage::getFragmentProgramSnippet() --"
    << endl << "//"
    << getMultiLightChunk()->getLightProgSnippet()
    << endl << ""
    << getClusteringProgSnippet(true)
    << endl << ""
    << getLightIndexProgSnippet()
    << endl << ""
    << endl << "//------------------------------------------------------"
    << endl << ""
    << endl
    ;

    return ost.str();
}

OSG_END_NAMESPACE
