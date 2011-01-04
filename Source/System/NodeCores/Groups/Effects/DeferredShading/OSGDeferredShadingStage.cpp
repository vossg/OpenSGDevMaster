/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGConfig.h"

#include "OSGDeferredShadingStage.h"
#include "OSGShaderShadowMapEngine.h"

#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGDirectionalLight.h"
#include "OSGMatrixUtility.h"
#include "OSGOrthographicCamera.h"
#include "OSGPointLight.h"
#include "OSGRenderBuffer.h"
#include "OSGRenderAction.h"
#include "OSGSolidBackground.h"
#include "OSGSpotLight.h"
#include "OSGTransform.h"
#include "OSGDepthChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDeferredShadingStageBase.cpp file.
// To modify it, please change the .fcd file (OSGDeferredShadingStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DeferredShadingStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            DeferredShadingStage::getClassType(),
            reinterpret_cast<Action::Callback>(&DeferredShadingStage::renderEnter));
        RenderAction::registerLeaveDefault(
            DeferredShadingStage::getClassType(),
            reinterpret_cast<Action::Callback>(&DeferredShadingStage::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DeferredShadingStage::DeferredShadingStage(void) :
    Inherited         (                                ),
    _changeCache      (TypeTraits<BitVector>::BitsClear),
    _targetSizeChanged(false                           )
{
}

DeferredShadingStage::DeferredShadingStage(const DeferredShadingStage &source) :
    Inherited         (source                          ),
    _changeCache      (TypeTraits<BitVector>::BitsClear),
    _targetSizeChanged(false                           )
{
}

DeferredShadingStage::~DeferredShadingStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DeferredShadingStage::changed(ConstFieldMaskArg whichField,
                                   UInt32            origin,
                                   BitVector         details)
{
    _changeCache |= (whichField & (PixelFormatsFieldMask   |
                                   PixelTypesFieldMask     |
                                   GBufferProgramFieldMask |
                                   AmbientProgramFieldMask |
                                   LightProgramsFieldMask  |
                                   LightsFieldMask         |
                                   Inherited::RenderTargetFieldMask));

    if((whichField & Inherited::RenderTargetFieldMask) != 0)
    {
        _targetSizeChanged = true;
    }

    Inherited::changed(whichField, origin, details);
}

void DeferredShadingStage::dump(      UInt32    ,
                                const BitVector ) const
{
    SLOG << "Dump DeferredShadingStage NI" << std::endl;
}

ActionBase::ResultE DeferredShadingStage::renderEnter(Action *action)
{
    RenderAction *ract = dynamic_cast<RenderAction *>(action);

    if(ract == NULL)
        return Action::Continue;

    RenderPartition   *parentPart = ract->getActivePartition();
    FrameBufferObject *target     = this->getRenderTarget   ();

    if(target == NULL && this->getInheritedTarget() == true)
    {
        target = parentPart->getRenderTarget();
    }

    DSStageData *data = ract->getData<DSStageData *>(_iDataSlotId);

    if(data == NULL)
    {
        DSStageDataUnrecPtr newData = createStageData();
        data = newData;

        setData(newData, _iDataSlotId, ract);
    }

    updateStageData(data, target, parentPart);

    this->beginPartitionGroup(ract);
    {
        // render the tree below this to gBufferTarget using gBufferShader
        scheduleGBufferPass(ract);

        // render a quad to this stage's target using shadingShader
        scheduleShadingPass(ract);
    }
    this->endPartitionGroup(ract);

    commitChanges();

    return Action::Skip;
}

ActionBase::ResultE DeferredShadingStage::renderLeave(Action *action)
{
    return Action::Continue;
}

DeferredShadingStage::DSStageDataTransitPtr
    DeferredShadingStage::createStageData(void)
{
    DSStageDataTransitPtr              data              =
        DSStageData::createLocal();
    FrameBufferObjectUnrecPtr          gBufferTarget     =
        FrameBufferObject::createLocal();
    RenderBufferUnrecPtr               gBufferDepth      =
        RenderBuffer::createLocal();
    SolidBackgroundUnrecPtr            gBufferBackground =
        SolidBackground::createLocal();
    BlendChunkUnrecPtr                 shadingBlendChunk =
        BlendChunk::createLocal();

    gBufferDepth     ->setInternalFormat (GL_DEPTH_COMPONENT24);
    gBufferTarget    ->setDepthAttachment(gBufferDepth        );

    gBufferBackground->setColor(Color3f(0.0f, 0.0f, 0.0f));

    shadingBlendChunk->setSrcFactor (GL_ONE);
    shadingBlendChunk->setDestFactor(GL_ONE);

    data->setGBufferTarget    (gBufferTarget    );
    data->setGBufferBackground(gBufferBackground);

    data->setBlendChunk       (shadingBlendChunk);

    return data;
}

TextureBufferTransitPtr DeferredShadingStage::createGBuffer(
    UInt32 index, Int32 width, Int32 height)
{
    TextureBufferTransitPtr buf    = TextureBuffer  ::createLocal();
    TextureObjChunkUnrecPtr bufTex = TextureObjChunk::createLocal();
    ImageUnrecPtr           bufImg = Image          ::createLocal();

    bufImg->set(_mfPixelFormats[index],
                width,
                height,
                1,
                1,
                1,
                0.0f,
                NULL,
                _mfPixelTypes[index],
                false,
                1);

    bufTex->setImage    (bufImg                  );
    bufTex->setTarget   (GL_TEXTURE_RECTANGLE_ARB);
    bufTex->setMinFilter(GL_NEAREST              );
    bufTex->setMagFilter(GL_NEAREST              );
    bufTex->setWrapS    (GL_CLAMP                );
    bufTex->setWrapT    (GL_CLAMP                );
    bufTex->setScale    (false                   );

    buf   ->setTexture  (bufTex                  );

// START DEBUG
    GLenum internalFormat;
    GLenum externalFormat;

    bufTex->determineFormats(internalFormat, externalFormat);

    FLOG(("DSStage::createGBuffer: IF [%s] EF [%s]\n",
        GLDefineMapper::the()->toString(internalFormat).c_str(),
        GLDefineMapper::the()->toString(externalFormat).c_str() ));
// END DEBUG

    return buf;
}

void DeferredShadingStage::updateStageData(
    DSStageData         *data,
    FrameBufferObject   *shadingTarget,
    RenderPartition     *parentPart    )
{
    FrameBufferObject *gBufferTarget = data->getGBufferTarget();

    Int32 targetWidth;
    Int32 targetHeight;
    Int32 targetLeft;
    Int32 targetBottom;

    if(shadingTarget != NULL)
    {
        targetWidth  = shadingTarget->getWidth ();
        targetHeight = shadingTarget->getHeight();

        targetLeft   = 0;
        targetBottom = 0;
    }
    else
    {
        targetWidth  = parentPart->getDrawEnv().getPixelWidth ();
        targetHeight = parentPart->getDrawEnv().getPixelHeight();

        targetLeft   = parentPart->getDrawEnv().getPixelLeft  ();
        targetBottom = parentPart->getDrawEnv().getPixelBottom();
    }

    if(gBufferTarget->getWidth () != targetWidth ||
       gBufferTarget->getHeight() != targetHeight  )
    {
        _targetSizeChanged = true;
    }

    if(_targetSizeChanged == true)
    {
        gBufferTarget->setSize(targetWidth, targetHeight);
    }

    if(getMFPixelFormats()->size() != getMFPixelTypes()->size())
    {
        SWARNING << "DeferredShadingStage::updateStageData: "
                 << "Number of PixelFormats and PixelTypes inconsistent."
                 << std::endl;
    }

    UInt32 lightCount  =        getMFLights      ()->size();
    UInt32 bufferCount = osgMin(getMFPixelFormats()->size(),
                                getMFPixelTypes  ()->size() );

    // buffers changed - remove them here, recreate below
    if((_changeCache & (PixelFormatsFieldMask |
                        PixelTypesFieldMask    )) != 0)
    {
        gBufferTarget->editMFColorAttachments()->clear (                    );
        gBufferTarget->editMFColorAttachments()->resize(bufferCount, NULL   );
        gBufferTarget->editMFDrawBuffers     ()->clear (                    );
        gBufferTarget->editMFDrawBuffers     ()->resize(bufferCount, GL_NONE);
    }

    for(UInt32 i = 0; i < bufferCount; ++i)
    {
        TextureBuffer *buf =
            dynamic_cast<TextureBuffer *>(gBufferTarget->getColorAttachments(i));

        if(buf == NULL)
        {
            TextureBufferUnrecPtr newBuf =
                createGBuffer(i, targetWidth, targetHeight);
            buf = newBuf;

            gBufferTarget->editMFColorAttachments()->replace(i, newBuf                      );
            gBufferTarget->editMFDrawBuffers     ()->replace(i, GL_COLOR_ATTACHMENT0_EXT + i);
        }
        else
        {
            updateGBuffer(buf, i, targetWidth, targetHeight);
        }
    }

    if((_changeCache & LightsFieldMask) != 0)
    {
        data->editMFLightChunks         ()->resize(    lightCount, NULL);
        data->editMFShadingStates       ()->resize(1 + lightCount, NULL);
        data->editMFShadingProgramChunks()->resize(1 + lightCount, NULL);
    }

    // update shading states
    if((_changeCache & (PixelFormatsFieldMask   |
                        PixelTypesFieldMask     |
                        AmbientProgramFieldMask |
                        LightProgramsFieldMask  |
                        LightsFieldMask          )) != 0)
    {
        // copy ambient and light programs
        DSStageData::MFShadingProgramChunksType::const_iterator spcIt  =
            data->editMFShadingProgramChunks()->begin();
        DSStageData::MFShadingProgramChunksType::const_iterator spcEnd =
            data->editMFShadingProgramChunks()->end  ();

        for(UInt32 progIdx = 0; spcIt != spcEnd; ++spcIt, ++progIdx)
        {
            if(*spcIt == NULL)
            {
                ShaderProgramChunkUnrecPtr newSPC =
                    ShaderProgramChunk::createLocal();
                //*spcIt = newSPC;

                data->editMFShadingProgramChunks()->replace(progIdx, newSPC);
            }

            (*spcIt)->clearVertexShaders  ();
            (*spcIt)->clearGeometryShaders();
            (*spcIt)->clearFragmentShaders();

            if(progIdx == 0 && getAmbientProgram() != NULL)
            {
                // ambient program
                copyProgramChunk(*spcIt, getAmbientProgram());

                // TODO: there must be a better way to add this uniform
                (*spcIt)->getFragmentShader(0)->addUniformVariable(
                    "vpOffset", Vec2f(targetLeft,
                                      targetBottom));
            }
            else
            {
                // light programs
                if(_mfLightPrograms.size() == 1)
                {
                    copyProgramChunk(*spcIt, getLightPrograms(0));

                    // TODO: there must be a better way to add this uniform
                    (*spcIt)->getFragmentShader(0)->addUniformVariable(
                        "vpOffset", Vec2f(targetLeft,
                                          targetBottom));
                }
                else if(_mfLightPrograms.size() == _mfLights.size())
                {
                    copyProgramChunk(*spcIt, getLightPrograms(progIdx - 1));

                    // TODO: there must be a better way to add this uniform
                    (*spcIt)->getFragmentShader(0)->addUniformVariable(
                        "vpOffset", Vec2f(targetLeft,
                                          targetBottom));
                }
                else
                {
                    SWARNING << "DeferredShadingStage::updateStageData: "
                             << "Number of Lights and LightPrograms "
                             << "inconsistent." << std::endl;
                }
            }
        }

        // create light chunks
        DSStageData::MFLightChunksType::const_iterator lcIt  =
            data->editMFLightChunks()->begin();
        DSStageData::MFLightChunksType::const_iterator lcEnd =
            data->editMFLightChunks()->end  ();

        for(UInt32 lightIdx = 0; lcIt != lcEnd; ++lcIt, ++lightIdx)
        {
            if(*lcIt == NULL)
            {
                DSLightChunkUnrecPtr newLC = DSLightChunk::createLocal();
                //*lcIt = newLC;
                data->editMFLightChunks()->replace(lightIdx, newLC);
            }

            updateLightChunk(*lcIt, getLights(lightIdx));
        }

        // populate shading states
        DSStageData::MFShadingStatesType::const_iterator stateIt  =
            data->editMFShadingStates()->begin();
        DSStageData::MFShadingStatesType::const_iterator stateEnd =
            data->editMFShadingStates()->end  ();

        for(UInt32 stateIdx = 0; stateIt != stateEnd; ++stateIt, ++stateIdx)
        {
            if(*stateIt == NULL)
            {
                StateUnrecPtr newState = State::createLocal();
                //*stateIt = newState;
                data->editMFShadingStates()->replace(stateIdx, newState);
            }

            // remove all chunks
            (*stateIt)->clearChunks();

            // add G Buffer textures
            for(UInt32 bufferIdx = 0;
                bufferIdx < bufferCount; ++bufferIdx)
            {
                TextureBuffer   *buf    = static_cast<TextureBuffer *>(
                    gBufferTarget->getColorAttachments(bufferIdx));
                TextureObjChunk *bufTex = buf->getTexture();

                (*stateIt)->addChunk(bufTex, bufferIdx);
            }

            // add ambient/light programs and light chunks
            if(stateIdx == 0)
            {
                if(getAmbientProgram() != NULL)
                {
                    (*stateIt)->addChunk(
                        data->getShadingProgramChunks(stateIdx));
                }
            }
            else
            {
                (*stateIt)->addChunk(
                    data->getShadingProgramChunks(stateIdx    ));
                (*stateIt)->addChunk(
                    data->getLightChunks         (stateIdx - 1));
            }

            // add blend chunk to light states
            if(stateIdx > 0)
            {
                (*stateIt)->addChunk(data->getBlendChunk());
            }
        }
    }

    _changeCache       = TypeTraits<BitVector>::BitsClear;
    _targetSizeChanged = false;
}

void DeferredShadingStage::updateGBuffer(
    TextureBuffer *buf, UInt32 index, Int32 width, Int32 height)
{
    TextureObjChunk *bufTex = buf   ->getTexture();
    Image           *bufImg = bufTex->getImage  ();

    if((_changeCache & (PixelFormatsFieldMask |
                        PixelTypesFieldMask    )) != 0)
    {
        bufImg->setPixelFormat(_mfPixelFormats[index]);
        bufImg->setDataType   (_mfPixelTypes  [index]);
    }

    if(_targetSizeChanged == true)
    {
        bufImg->setWidth (width );
        bufImg->setHeight(height);
    }
}

/*! Sets the \a lightChunk fields based on light.
    
    \dev
    DeferredShadingStage can not use the light's own chunk, because
    it computes the light position based on DrawEnv::getCameraViewing(),
    which is just the ortho camera for rendering the full screen quads, not
    the perspective camera used during the gbuffer pass.
    \enddev
 */
void DeferredShadingStage::updateLightChunk(
    DSLightChunk *lightChunk, Light *light)
{
    lightChunk->setBeacon  (light->getBeacon  ());
    lightChunk->setAmbient (light->getAmbient ());
    lightChunk->setDiffuse (light->getDiffuse ());
    lightChunk->setSpecular(light->getSpecular());

    if(light->getType() == DirectionalLight::getClassType())
    {
        DirectionalLight *dirL = static_cast<DirectionalLight *>(light);

        Vec4f dir(dirL->getDirection());
        dir[3] = 0.f;

        lightChunk->setPosition(dir);
    }
    else if(light->getType() == PointLight::getClassType())
    {
        PointLight *pointL = static_cast<PointLight *>(light);

        Vec4f pos(pointL->getPosition());
        pos[3] = 1.f;

        lightChunk->setPosition            (pos                              );
        lightChunk->setConstantAttenuation (pointL->getConstantAttenuation ());
        lightChunk->setLinearAttenuation   (pointL->getLinearAttenuation   ());
        lightChunk->setQuadraticAttenuation(pointL->getQuadraticAttenuation());
        lightChunk->setCutoff              (180.f                            );
    }
    else if(light->getType() == SpotLight::getClassType())
    {
        SpotLight *spotL = static_cast<SpotLight *>(light);

        Vec4f pos(spotL->getPosition());
        pos[3] = 1.f;

        lightChunk->setPosition            (pos                             );
        lightChunk->setConstantAttenuation (spotL->getConstantAttenuation ());
        lightChunk->setLinearAttenuation   (spotL->getLinearAttenuation   ());
        lightChunk->setQuadraticAttenuation(spotL->getQuadraticAttenuation());
        lightChunk->setDirection           (spotL->getDirection           ());
        lightChunk->setExponent            (spotL->getSpotExponent        ());
        lightChunk->setCutoff              (
            osgRad2Degree(spotL->getSpotCutOff()));
    }
    else
    {
        SWARNING << "DeferredShadingStage::updateLightChunk: "
                 << "Unknown light type." << endLog;
    }
}

void DeferredShadingStage::copyProgramChunk(
    ShaderProgramChunk *spcDest, ShaderProgramChunk *spcSource)
{
    ShaderProgramChunk::MFVertexShaderType::const_iterator vsIt  =
        spcSource->getMFVertexShader()->begin();
    ShaderProgramChunk::MFVertexShaderType::const_iterator vsEnd =
        spcSource->getMFVertexShader()->end  ();

    for(; vsIt != vsEnd; ++vsIt)
    {
        spcDest->addVertexShader(*vsIt);
    }

    ShaderProgramChunk::MFFragmentShaderType::const_iterator fsIt  =
        spcSource->getMFFragmentShader()->begin();
    ShaderProgramChunk::MFFragmentShaderType::const_iterator fsEnd =
        spcSource->getMFFragmentShader()->end  ();

    for(; fsIt != fsEnd; ++fsIt)
    {
        spcDest->addFragmentShader(*fsIt);
    }
}


void DeferredShadingStage::scheduleGBufferPass(RenderAction *ract)
{
#if 0
    RenderPartition    *parentPart  = ract->getActivePartition();
#endif
    DSStageData        *data        = ract->getData<DSStageData *>(_iDataSlotId);
    ShaderProgramChunk *shader      = this->getGBufferProgram();
#if 0
    UInt32              bufferCount = osgMin(getMFPixelFormats()->size(),
                                             getMFPixelTypes  ()->size() );
#endif

    // create shadow maps
    MFLightsType::const_iterator lIt         = _mfLights.begin();
    MFLightsType::const_iterator lEnd        = _mfLights.end  ();

    for(UInt32 i = 0; lIt != lEnd; ++lIt, ++i)
    {
        (*lIt)->callLightEngineEnter(ract);

        ShaderProgramChunk    *spc   = data->getShadingProgramChunks(1+i);
        State                 *state = data->getShadingStates       (1+i);
        ShaderShadowMapEngine *sme   = dynamic_cast<ShaderShadowMapEngine *>(
            (*lIt)->getLightEngine());

        if(sme != NULL)
        {
//             ShaderProgram *shadowVP = sme->getShadowVertexProgram  ();
            ShaderProgram *shadowFP = sme->getShadowFragmentProgram();

//             if(shadowVP                                      != NULL &&
//                spc->getMFVertexShader()->findIndex(shadowVP) == -1     )
//             {
//                 spc->addShader(shadowVP);
//             }

            if(shadowFP                                        != NULL &&
               spc->getMFFragmentShader()->findIndex(shadowFP) == -1     )
            {
                spc->addShader(shadowFP);
            }

            Int32 shadowTexUnit = sme->getForceTextureUnit() > 0 ?
                                  sme->getForceTextureUnit()     : 7;

            if(sme->getEnabled() == true)
            {
                state->addChunk(sme->getShadowTexChunk(),
                                shadowTexUnit            );
            }
            else
            {
                state->subChunk(TextureObjChunk::getStaticClassId(),
                                shadowTexUnit                       );
            }
        }
    }

    this->pushPartition(ract);
    {
        RenderPartition *part = ract->getActivePartition();

#ifdef OSG_DEBUG
        part->setDebugString("DeferredShadingStage::GBufferPartition");
#endif
        setupGBufferPartition(part, ract, data);

        if(shader != NULL)
        {
            part->pushState  (                            );
            part->addOverride(shader->getClassId(), shader);
        }

        this->recurseFromThis(ract);

        if(shader != NULL)
            part->popState();
    }
    this->popPartition(ract);

    // create shadow maps
    lIt  = _mfLights.begin();
    lEnd = _mfLights.end  ();

    for(; lIt != lEnd; ++lIt)
    {
        (*lIt)->callLightEngineLeave(ract);
    }
}

void DeferredShadingStage::scheduleShadingPass(RenderAction *ract)
{
#if 0
    RenderPartition *parentPart = ract->getActivePartition    (            );
#endif
    DSStageData     *data       = ract->getData<DSStageData *>(_iDataSlotId);

    this->pushPartition(ract,
                        (RenderPartition::CopyWindow      |
                         RenderPartition::CopyViewportSize) );
    {
        RenderPartition *part = ract->getActivePartition();

#ifdef OSG_DEBUG
        part->setDebugString("DeferredShadingStage::ShadingPartition");
#endif
        setupShadingPartition(part, ract, data);

        RenderPartition::DrawFunctor f =
            boost::bind(&DeferredShadingStage::executeShadingPass, this, _1);

        DSStageData::MFShadingStatesType::const_iterator sIt  =
            data->getMFShadingStates()->begin();
        DSStageData::MFShadingStatesType::const_iterator sEnd =
            data->getMFShadingStates()->end();

        for(UInt32 i = 0; sIt != sEnd; ++sIt, ++i)
        {
            if((i > 0) &&  (getLights(i-1)->getOn() == false))
                continue;
          
            part->dropFunctor(f, *sIt, (*sIt)->getSortKey());
        }
    }
    this->popPartition(ract);
}

Action::ResultE DeferredShadingStage::executeShadingPass(DrawEnv *drawEnv)
{
    glBegin(GL_QUADS);
    {
        glVertex2f(-1.f, -1.f);
        glVertex2f( 1.f, -1.f);
        glVertex2f( 1.f,  1.f);
        glVertex2f(-1.f,  1.f);
    }
    glEnd();

    return Action::Continue;
}

void DeferredShadingStage::setupGBufferPartition(
    RenderPartition *part, RenderAction *ract, DSStageData *data)
{
    Window            *win    = ract->getWindow           ();
    FrameBufferObject *target = data->getGBufferTarget    ();
    Camera            *cam    = this->getCamera           ();
    Background        *back   = data->getGBufferBackground();

    Inherited::setupPartition(part, win, target, cam, back);
}

void DeferredShadingStage::setupShadingPartition(
    RenderPartition *part, RenderAction *ract, DSStageData *data)
{
    Window            *win    = ract->getWindow           ();
    FrameBufferObject *target = data->getShadingTarget    ();
    Camera            *cam    = this->getCamera           ();
    Background        *back   = this->getBackground       ();

    part->setRenderTarget(target);
    part->setWindow      (win   );

    if(target != NULL)
    {
        part->calcViewportDimension(this->getLeft    (),
                                    this->getBottom  (),
                                    this->getRight   (),
                                    this->getTop     (),

                                    target->getWidth (),
                                    target->getHeight() );
    }
    else if(win != NULL)
    {
        part->calcViewportDimension(this->getLeft  (),
                                    this->getBottom(),
                                    this->getRight (),
                                    this->getTop   (),

                                    win->getWidth  (),
                                    win->getHeight () );
    }
    else
    {
        SWARNING << "DeferredShadingStage::setupShadingPartition: "
                 << "No target or window." << std::endl;
    }

    // setup ortho projection
    Matrix matProjection;
    Matrix matProjectionTranslation;
    Matrix matViewing;

    matProjectionTranslation.setIdentity();
    matViewing              .setIdentity();

    MatrixOrthogonal(matProjection,
                     -1.f, 1.f,
                     -1.f, 1.f,
                     -1.f, 1.f );

    part->setupProjection(matProjection, matProjectionTranslation);
    part->setupViewing   (matViewing                             );

    part->setNear(-1.f);
    part->setFar ( 1.f);

    // setup VPCamera matrices to original projection -- TODO copy from GBuffer pass?
    cam->getProjection           (matProjection,
                                  part->getViewportWidth (),
                                  part->getViewportHeight() );
    cam->getProjectionTranslation(matProjectionTranslation,
                                  part->getViewportWidth (),
                                  part->getViewportHeight() );

    Matrix matProjectionFull = matProjection;
    matProjectionFull.mult(matProjectionTranslation);

    Matrix matToWorld;
    Matrix matWorldToScreen;

    cam->getViewing(matViewing, part->getViewportWidth (),
                                part->getViewportHeight() );
    matToWorld.invertFrom(matViewing);

    matWorldToScreen = matProjectionFull;
    matWorldToScreen.mult(matToWorld);

    part->setVPCameraMatrices(matProjectionFull,
                              matProjection,
                              matProjectionTranslation,
                              matViewing,
                              matToWorld,
                              matWorldToScreen          );

    part->setBackground(back);

    part->setSetupMode(RenderPartition::ProjectionSetup |
                       RenderPartition::BackgroundSetup  );
}

OSG_END_NAMESPACE
