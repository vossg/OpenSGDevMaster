/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------* \
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGShadowStage.h"

#include "OSGShadowStageData.h"

#include "OSGGeometry.h"
#include "OSGMaterialGroup.h"
#include "OSGMultiPassMaterial.h"

#include "OSGSpotLight.h"
#include "OSGDirectionalLight.h"
#include "OSGMatrixUtility.h"

#include "OSGPerspectiveCamera.h"
#include "OSGMatrixCamera.h"
#include "OSGMultiCore.h"

#define OSG_HAS_STDMAP
#define OSG_HAS_PERSPMAP
#define OSG_HAS_DITHERMAP
#define OSG_HAS_PCFMAP
#define OSG_HAS_PCF2MAP
#define OSG_HAS_PCSSMAP
#define OSG_HAS_VARMAP

#ifdef OSG_HAS_STDMAP
#include "OSGStdShadowMapHandler.h"
#endif
#ifdef OSG_HAS_PERSPMAP
#include "OSGPerspectiveShadowMapHandler.h"
#endif
#ifdef OSG_HAS_DITHERMAP
#include "OSGDitherShadowMapHandler.h"
#endif
#ifdef OSG_HAS_PCFMAP
#include "OSGPCFShadowMapHandler.h"
#endif
#ifdef OSG_HAS_PCF2MAP
#include "OSGPCF2ShadowMapHandler.h"
#endif
#ifdef OSG_HAS_PCSSMAP
#include "OSGPCSSShadowMapHandler.h"
#endif
#ifdef OSG_HAS_VARMAP
#include "OSGVarianceShadowMapHandler.h"
#endif

#include "OSGRenderAction.h"
#include <boost/bind.hpp>
#include "OSGTextureBuffer.h"

//--------------------------------------------------------------------

OSG_USING_NAMESPACE

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/***************************************************************************\
*                           Class variables                               *
\***************************************************************************/

UInt32 ShadowStage::_extSHL                  = Window::invalidExtensionID;
UInt32 ShadowStage::_extDepthTexture         = Window::invalidExtensionID;
UInt32 ShadowStage::_extShadows              = Window::invalidExtensionID;
UInt32 ShadowStage::_extFramebufferObject    = Window::invalidExtensionID;
UInt32 ShadowStage::_extDrawBuffers          = Window::invalidExtensionID;

UInt32 ShadowStage::FuncIdGenMipmaps         = Window::invalidFunctionID;

UInt32 ShadowStage::_uiFramebufferObjectExt  = Window::invalidExtensionID;
UInt32 ShadowStage::_uiFramebufferBlitExt    = Window::invalidExtensionID;

UInt32 ShadowStage::_uiFuncBindFramebuffer   = Window::invalidFunctionID;
UInt32 ShadowStage::_uiFuncBlitFramebuffer   = Window::invalidFunctionID;

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/

void ShadowStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            ShadowStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&ShadowStage::renderEnter));
        
        RenderAction::registerLeaveDefault( 
            ShadowStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&ShadowStage::renderLeave));

        _extSHL               = 
            Window::registerExtension("GL_ARB_shading_language_100");

        _extDepthTexture      = 
            Window::registerExtension("GL_ARB_depth_texture");

        _extShadows           = 
            Window::registerExtension("GL_ARB_shadow");

        _extFramebufferObject = 
            Window::registerExtension("GL_EXT_framebuffer_object");

        _extDrawBuffers       =
            Window::registerExtension("GL_ARB_draw_buffers");


        Window::registerConstant(GL_MAX_TEXTURE_SIZE              );
        Window::registerConstant(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);

        FuncIdGenMipmaps =
            Window::registerFunction(OSG_DLSYM_UNDERSCORE"glGenerateMipmapEXT",
                                     _extFramebufferObject);


        _uiFramebufferObjectExt   = 
            Window::registerExtension("GL_EXT_framebuffer_object");
        _uiFramebufferBlitExt   = 
            Window::registerExtension("GL_EXT_framebuffer_blit");

        _uiFuncBindFramebuffer          = 
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBindFramebufferEXT", 
                _uiFramebufferObjectExt);

        _uiFuncBlitFramebuffer  =
            Window::registerFunction (
                 OSG_DLSYM_UNDERSCORE"glBlitFramebufferEXT", 
                _uiFramebufferBlitExt);
    }
}


/***************************************************************************\
*                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
   -  private                                                                 -
   \*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShadowStage::ShadowStage(void) :
     Inherited     (     ),
    _trigger_update(false),
    _occlusionQuery(0    )
{
}

ShadowStage::ShadowStage(const ShadowStage &source) :
     Inherited     (source                ),
    _trigger_update(source._trigger_update),
    _occlusionQuery(source._occlusionQuery)
{

}

ShadowStage::~ShadowStage(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShadowStage::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details   )
{
    if(whichField & LightNodesFieldMask)
    {
#if 0
        FDEBUG(("ShadowStage::changed : light nodes changed.\n"));
        _lights.clear();
        for(UInt32 i = 0;i < getMFLightNodes()->size();++i)
            _lights.push_back(
                std::make_pair(
                    getLightNodes(i), 
                    dynamic_cast<Light *>(getLightNodes(i)->getCore())));
#endif
    }

    if(whichField & MapAutoUpdateFieldMask)
    {
        _trigger_update = true;
    }

    if(whichField & AutoSearchForLightsFieldMask)
    {
        if(getAutoSearchForLights())
        {
            FNOTICE(("auto light search mode on\n"));
        }
        else
        {
            FNOTICE(("auto light search mode off\n"));
        }
    }

    if(whichField & ShadowSmoothnessFieldMask)
    {
        if(getShadowSmoothness() < 0.0)
        {
            FNOTICE(("No ShadowSmoothness < 0 allowed!\n"));
            setShadowSmoothness(0.0);
        }
        if(getShadowSmoothness() > 1.0)
        {
            FNOTICE(("No ShadowSmoothness > 1.0 allowed!\n"));
            setShadowSmoothness(1.0);
        }
        FNOTICE(("ShadowSmoothness set to %f\n", getShadowSmoothness()));
    }

    Inherited::changed(whichField, origin, details);
}

void ShadowStage::dump(      UInt32,
                       const BitVector) const
{
    SLOG << "Dump ShadowStage NI" << std::endl;
}


void ShadowStage::onCreate(const ShadowStage *source)
{
    Inherited::onCreate(source);

    // if we're in startup this is the prototype ...
    if(OSG::GlobalSystemState == OSG::Startup)
        return;
}

void ShadowStage::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

Action::ResultE ShadowStage::renderEnter(Action *action)
{
    Action::ResultE returnValue = Action::Continue;

    RenderAction *ract = dynamic_cast<RenderAction *>(action);

    if(ract->getWindow()->hasExtOrVersion(_extSHL, 
                                           0x0200, 
                                           0x0200              ) == false ||
       ract->getWindow()->hasExtOrVersion(_extDepthTexture, 
                                           0x0104              ) == false ||
       ract->getWindow()->hasExtOrVersion(_extShadows, 
                                           0x0104              ) == false ||
       ract->getWindow()->hasExtOrVersion(_extFramebufferObject, 
                                           0x0300, 
                                           0x0200              ) == false ||
       ract->getWindow()->hasExtOrVersion(_extDrawBuffers, 
                                           0x0300              ) == false  )
    {
        return returnValue;
    }
       
    if(0x0000 == ( ract                ->getRenderProperties() & 
                  _sfRenderPropertyMask. getValue           ()))
    {
#if 0
        fprintf(stderr,
                "action      : 0x%016" PRIx64 " \n"
                "shadowstage : 0x%016" PRIx64 " \n",
                 ract                ->getRenderProperties(),
                _sfRenderPropertyMask. getValue           ());
#endif

        return returnValue;
    }

    ShadowStageData *pData = ract->getData<ShadowStageData *>(_iDataSlotId);


    if(pData == NULL)
    {
        ShadowStageDataUnrecPtr pTmp = ShadowStageData::createLocal();

        pData = pTmp;

        this->setData(pData, _iDataSlotId, ract);
    }

//    fprintf(stderr, "ShadowStage::renderEnter\n");

    if(pData->getRunning() == true)
        return returnValue;


    pData->setRunning(true);


    ShadowTreeHandler *pTreeHandler = pData->getTreeHandler();
      
    if(pTreeHandler == NULL || 
       this->getShadowMode() != pTreeHandler->getMode())
    {       
        pTreeHandler = NULL;

//        clearLights(_oldLights.size());

        GLenum eTargetFormat = this->getBufferFormat();

        if(eTargetFormat == GL_NONE)
        {
            eTargetFormat = 
                ract->getActivePartition()->
                    getDrawEnv().getTargetBufferFormat();
        }

        switch(getShadowMode())
        {
            case NO_SHADOW:
            {
                FNOTICE(("No Shadows\n"));
            }
            break;
            
            case STD_SHADOW_MAP:
            {
                FNOTICE(("using standard Shadow Mapping...\n"));
#ifdef OSG_HAS_STDMAP
                pTreeHandler = new StdShadowMapHandler(this, 
                                                       pData,
                                                       eTargetFormat,
                                                       ract->getWindow());
#endif
            }
            break;
            
            case PERSPECTIVE_SHADOW_MAP:
            {
                FNOTICE(("using Lisp Perspective Shadow Mapping...\n"));
#ifdef OSG_HAS_PERSPMAP
                pTreeHandler = 
                    new PerspectiveShadowMapHandler(this, 
                                                    pData,
                                                    eTargetFormat,
                                                    ract->getWindow());
#endif
            }
            break;
            
            case DITHER_SHADOW_MAP:
            {
                FNOTICE(("using Dither Shadow Mapping...\n"));
#ifdef OSG_HAS_DITHERMAP
                pTreeHandler = new DitherShadowMapHandler(this, 
                                                          pData,
                                                          eTargetFormat,
                                                          ract->getWindow());
#endif
            }
            break;

            case PCF_SHADOW_MAP:
            {
                FNOTICE(("using PCF Shadow Mapping...\n"));
#ifdef OSG_HAS_PCFMAP
                pTreeHandler = new PCFShadowMapHandler(this, 
                                                       pData,
                                                       eTargetFormat,
                                                       ract->getWindow());
#endif
            }
            break;

            case PCF2_SHADOW_MAP:
            {
                FNOTICE(("using PCF2 Shadow Mapping...\n"));
#ifdef OSG_HAS_PCF2MAP
                pTreeHandler = new PCF2ShadowMapHandler(this, 
                                                        pData,
                                                        eTargetFormat,
                                                        ract->getWindow());
#endif
            }
            break;

            case PCSS_SHADOW_MAP:
            {
                FNOTICE(("using PCSS Shadow Mapping...\n"));
#ifdef OSG_HAS_PCSSMAP
                pTreeHandler = new PCSSShadowMapHandler(this, 
                                                        pData,
                                                        eTargetFormat,
                                                        ract->getWindow());
#endif
            }
            break;
            
            case VARIANCE_SHADOW_MAP:
            {
                FNOTICE(("using Variance Shadow Mapping...\n"));
#ifdef OSG_HAS_VARMAP
                pTreeHandler = new VarianceShadowMapHandler(this, 
                                                            pData,
                                                            eTargetFormat,
                                                            ract->getWindow());
#endif
            }
            break;

            default:
                break;
        }

        pData->setTreeHandler(pTreeHandler);
    }

    if(pTreeHandler == NULL || getShadowOn() == false)
    {
        pData->setRunning(false);

        return returnValue;
    }


#if 0
    if(getSceneRoot() == NULL)
    {
        setSceneRoot(action->getActNode());
    }
#endif

    const ShadowStageData::LightStore    &vLights      =
        pData->getLights();
    const ShadowStageData::LStateStore   &vLightStates =
        pData->getLightStates();
          ShadowStageData::StatusStore   &vRealPLight  =
        pData->getRealPointLight();
          ShadowStageData::TravMaskStore &vExclTravMask =
        pData->getExcludeNodeTravMask();
          ShadowStageData::NodeStore     &vTransparents =
        pData->getTransparents();

    vExclTravMask.clear();
    vRealPLight  .clear();

    //get excludeNode states
    for(UInt32 i = 0;i < getMFExcludeNodes()->size();i++)
    {
        Node *exnode = getExcludeNodes(i);

        if(exnode != NULL)
        {
            vExclTravMask.push_back(exnode->getTravMask());
        }
        else
        {
            vExclTravMask.push_back(0);
        }
    }

    checkLights(ract, pData);

    bool allLightsZero = true;

    if(getGlobalShadowIntensity() != 0.0)
    {
        allLightsZero = false;
    }
    else
    {
        for(UInt32 i = 0;i < vLights.size();i++)
        {
            if(vLights     [i].second->getShadowIntensity() != 0.0 && 
               vLightStates[i]                              != 0     )
            {
                allLightsZero = false;
            }
        }
    }

    if(vLights.size() == 0 || allLightsZero)
    {
        pData->setRunning(false);

        return returnValue;
    }
    else
    {
        ract->disableDefaultPartition();

        //find transparent nodes
        vTransparents.clear();

        if(getAutoExcludeTransparentNodes())
        {
            traverse(action->getActNode(), 
                     boost::bind(&ShadowStage::findTransparent,
                                  this, 
                                  pData,
                                 _1) );
        }

        //check if excludeNodes are disabled
        for(UInt32 i = 0;i < getMFExcludeNodes()->size();++i)
        {
            Node *exnode = getExcludeNodes(i);

            if(exnode != NULL)
                vExclTravMask[i] = exnode->getTravMask();
        }

        //check if all sides of a pointlight are needed
        //TODO: Not implemented yet ...
#if 0
        _renderSide.clear();
#endif
        ract->getActivePartition()->disable();

        this->beginPartitionGroup(ract);
        {
            pTreeHandler->render(ract,
                                 &(ract->getActivePartition()->getDrawEnv()));
        }
        this->endPartitionGroup(ract);

        returnValue = Action::Skip;
    }

    pData->setRunning(false);

    return returnValue;
}

Action::ResultE ShadowStage::renderLeave(Action *action)
{
    Action::ResultE returnValue = Action::Continue;

//    fprintf(stderr, "ShadowStage::renderLeave\n");

    return returnValue;
}


















void ShadowStage::triggerMapUpdate(void)
{
    editSField(MapAutoUpdateFieldMask);
}




Action::ResultE ShadowStage::findLight(ShadowStageData *       pData,
                                       Node            * const node)
{
    if(node->getCore()->getType().isDerivedFrom(Light::getClassType()))
    {
        ShadowStageData::LightStore  &vLights = pData->getLights();

        vLights.push_back(
            std::make_pair(node, 
                           dynamic_cast<Light *>(node->getCore())));
    }
    else if(node->getCore()->getType().isDerivedFrom(MultiCore::getClassType()))
    {
        ShadowStageData::LightStore  &vLights = pData->getLights();

        MultiCore *pCore = dynamic_cast<MultiCore *>(node->getCore());

        MultiCore::MFCoresType::const_iterator cIt = 
            pCore->getMFCores()->begin();

        MultiCore::MFCoresType::const_iterator cEnd = 
            pCore->getMFCores()->end();

        for(; cIt != cEnd; ++cIt)
        {
            if((*cIt)->getType().isDerivedFrom(Light::getClassType()))
            {
                vLights.push_back(
                    std::make_pair(node, 
                                   dynamic_cast<Light *>(*cIt)));
            }
        }
    }

    return Action::Continue;
}

Action::ResultE ShadowStage::findTransparent(ShadowStageData *       pData,
                                             Node            * const node)
{
    if(node->getCore() != NULL)
    {
        ShadowStageData::NodeStore &vTransparents = pData->getTransparents();

       if(node->getCore()->getType() == Geometry::getClassType() ||
           node->getCore()->getType() == MaterialGroup::getClassType())
        {
            Material               *mat = NULL;
            MultiPassMaterial      *multiMat = NULL;
            Geometry               *geo = dynamic_cast<Geometry *>(
                node->getCore());
            MaterialGroup          *matGroup = 
                dynamic_cast<MaterialGroup *>(node->getCore());

            if(geo != NULL)
                mat = geo->getMaterial();
            if(matGroup != NULL)
                mat = matGroup->getMaterial();
            if(mat != NULL)
            {
                /* isTransparent in MultiPassMaterial returns false,
                   if one Material is not transparent. Here we need
                   to know if one Material is transparent so we can't
                   use isTransparent for MultiPassMaterials. */

                multiMat = dynamic_cast<MultiPassMaterial *>(mat);

                if(multiMat != NULL)
                {
                    MultiPassMaterial::MFMaterialsType::const_iterator it = 
                        multiMat->getMFMaterials()->begin();

                    MultiPassMaterial::MFMaterialsType::const_iterator matsEnd =
                        multiMat->getMFMaterials()->end();

                    for(;it != matsEnd;++it)
                    {
                        if((*it) == NULL)
                            continue;

                        if((*it)->isTransparent() && node->getTravMask() != 0)
                        {
                            vTransparents.push_back(node);
                            break;
                        }
                    }
                }
                else
                {
                    if(mat->isTransparent() && node->getTravMask() != 0)
                        vTransparents.push_back(node);
                }
            }

        }

        if(node->getCore()->getType() == Geometry::getClassType())
        {
            Geometry *geo = dynamic_cast<Geometry *>(node->getCore());

            if(geo->getMaterial() != NULL &&
               geo->getMaterial()->isTransparent() &&
               node->getTravMask() != 0)
            {
                vTransparents.push_back(node);
            }
        }
        else if(node->getCore()->getType() == MaterialGroup::getClassType())
        {
            MaterialGroup *matGroup = dynamic_cast<MaterialGroup *>(
                node->getCore());

            if(matGroup->getMaterial() != NULL &&
               matGroup->getMaterial()->isTransparent() &&
               node->getTravMask()  != 0)
            {
                vTransparents.push_back(node);
            }
        }
    }
    return Action::Continue;
}



void ShadowStage::checkLights(RenderActionBase *action,
                              ShadowStageData  *pData )
{
          ShadowStageData::LightStore  &vLights      = pData->getLights();
    const ShadowStageData::LightStore  &vOldLights   = pData->getOldLights();
          ShadowStageData::LStateStore &vLightStates = pData->getLightStates();

    if(getAutoSearchForLights())
    {
        //Finding lights by going through whole Scenegraph
        vLights.clear();

        traverse(action->getActNode(), 
                 boost::bind(&ShadowStage::findLight,
                             this, 
                             pData,
                             _1));
    }
    else
    {
        if(vLights.size() != _mfLightNodes.size())
        {
            vLights.resize(_mfLightNodes.size());
        }

        MFLightNodesType           ::const_iterator lIt =_mfLightNodes.begin();
        MFLightNodesType           ::const_iterator lEnd=_mfLightNodes.end  ();
        ShadowStageData::LightStore::      iterator lsIt= vLights     .begin();

        for(; lIt != lEnd; ++lIt, ++lsIt)
        {
            (*lsIt).first  = *lIt;
            (*lsIt).second = dynamic_cast<Light *>((*lIt)->getCore());
        }
    }

    vLightStates.clear();

    bool changed = false;

    if(vLights.size() > 0 && vLights.size() == vOldLights.size())
    {
        for(UInt32 i = 0;i < vLights.size();++i)
        {
            bool light_state = vLights[i].second->getOn();

            if(vLights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
            {
                light_state = true;
            }
            else if(vLights[i].second->getShadowMode() == 
                                                        Light::CAST_SHADOW_OFF)
            {
                light_state = false;
            }

            vLightStates.push_back(light_state ? 1 : 0);

            if(vLights[i] != vOldLights[i])
                changed = true;
        }
    }
    else
    {
        changed = true;
    }

    if(!changed)
    {
        updateLights(action, pData);
        return;
    }

    initializeLights(action, pData);
}

void ShadowStage::updateLights(RenderActionBase *action,
                               ShadowStageData  *pData )
{
    SpotLight        *tmpSpot;
    DirectionalLight *tmpDir;
    PointLight       *tmpPoint = NULL;
    Matrix            tmpMatrix;
    bool              isSpot, isDirect;
    Real32            sceneWidth = 0.0;
    Real32            sceneHeight = 0.0;
    Real32            PLangle = 0.0;

    const ShadowStageData::LightStore  &vLights      = 
        pData->getLights();

    const ShadowStageData::TransStore  &vLCamTrans   =
        pData->getLightCamTrans();

    const ShadowStageData::CamStore    &vLCams       =
        pData->getLightCameras();

    const ShadowStageData::NodeStore   &vLCamBeacons = 
        pData->getLightCamBeacons();

          ShadowStageData::StatusStore &vRealPLight  = 
        pData->getRealPointLight();

    for(UInt32 i = 0;i < vLights.size();++i)
    {
        pData->getLightRoot(i)->updateVolume();
        //Giving new Camera Rotation and Position of the light it belongs to
        {
            Quaternion  q;

            tmpMatrix.setIdentity();

            //Is the Lightsource a Spotlight?
            if(vLights[i].second->getType() == SpotLight::getClassType())
            {
                //Casting to Spotlight
                tmpSpot = dynamic_cast<SpotLight *>(vLights[i].second.get());
                FDEBUG(("Found Spotlight!\n"));
                isSpot = true;
                isDirect = false;

                Pnt3f   lightpos = tmpSpot->getPosition();
                Vec3f   lightdir = tmpSpot->getDirection();

                if(tmpSpot->getBeacon() != NULL)
                {
                    Matrix  m = tmpSpot->getBeacon()->getToWorld();
                    m.mult(lightpos, lightpos);
                    m.mult(lightdir, lightdir);
                }

                //<-- ???
                q.setValue(Vec3f(0, 0, -1), lightdir);
                tmpMatrix.setTransform(Vec3f(lightpos), q);

                vRealPLight.push_back(false);
            }
            else if(vLights[i].second->getType() == 
                                             DirectionalLight::getClassType())
            {
                Vec3f   diff;
                Pnt3f   center;

                tmpDir = 
                    dynamic_cast<DirectionalLight *>(vLights[i].second.get());

                FDEBUG(("Found Directionallight!\n"));
                isSpot = false;
                isDirect = true;

                diff = (pData->getLightRoot(i)->getVolume().getMax() -
                        pData->getLightRoot(i)->getVolume().getMin());

                sceneWidth = diff.length() * 0.5;
                // Not final values. May get tweaked in the future
                sceneHeight = diff.length() * 0.5;

                pData->getLightRoot(i)->getVolume().getCenter(center);

                Vec3f   lightdir = tmpDir->getDirection();

                if(tmpDir->getBeacon() != NULL)
                {
                    Matrix  m = tmpDir->getBeacon()->getToWorld();
                    m.mult(lightdir, lightdir);
                }

                MatrixLookAt(tmpMatrix, center + lightdir,
                             center, Vec3f(0, 1, 0));
                tmpMatrix.invert();
                vRealPLight.push_back(false);
            }
            else
                // Preparation for PointLight -- In this version just a hack
            {
                Vec3f   dir;
                Pnt3f   center;

                tmpPoint = dynamic_cast<PointLight *>(vLights[i].second.get());
                FDEBUG(("Found PointLight!\n"));
                isSpot = false;
                isDirect = false;

                /* Direction of LightCam is a hack. 
                   It always looks at the center of the scene.
                   If the light is placed INSIDE of your Scene
                   (surrounded by Geometry, like a bulb in a Room)
                   the result of the Shadows may be not what you wanted.
                   So, please use the PointLight only outside of your 
                   Scene/outside the Bounding-Box of the lit geometry
                   */

                Pnt3f   lightpos = tmpPoint->getPosition();
                if(tmpPoint->getBeacon() != NULL)
                {
                    Matrix  m = tmpPoint->getBeacon()->getToWorld();
                    m.mult(lightpos, lightpos);
                }

                if((getShadowMode() == STD_SHADOW_MAP         ||
                    getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                    getShadowMode() == DITHER_SHADOW_MAP      ||
                    getShadowMode() == PCF_SHADOW_MAP         ||
                    getShadowMode() == PCF2_SHADOW_MAP          ))
                {
                    //Lightpos inside Scene BB?
                    Pnt3f   sceneMin = 
                        pData->getLightRoot(i)->getVolume().getMin();

                    Pnt3f   sceneMax = 
                        pData->getLightRoot(i)->getVolume().getMax();

                    if((lightpos[0] < sceneMin[0] ||
                        lightpos[1] < sceneMin[1] ||
                        lightpos[2] < sceneMin[2]) ||
                       (lightpos[0] > sceneMax[0] ||
                        lightpos[1] > sceneMax[1] ||
                        lightpos[2] > sceneMax[2]))
                    {
                        //check if angle is ok to use one Side
                        Vec3f   dist, diff;
                        Pnt3f   center;

                        pData->getLightRoot(i)->getVolume().getCenter(center);

                        //Scene Bounding Box Points

                        Pnt3f   bb[8];
                        bb[0] = Pnt3f(sceneMin[0], sceneMin[1], sceneMin[2]);
                        bb[1] = Pnt3f(sceneMax[0], sceneMin[1], sceneMin[2]);
                        bb[2] = Pnt3f(sceneMax[0], sceneMax[1], sceneMin[2]);
                        bb[3] = Pnt3f(sceneMin[0], sceneMax[1], sceneMin[2]);
                        bb[4] = Pnt3f(sceneMin[0], sceneMin[1], sceneMax[2]);
                        bb[5] = Pnt3f(sceneMax[0], sceneMin[1], sceneMax[2]);
                        bb[6] = Pnt3f(sceneMax[0], sceneMax[1], sceneMax[2]);
                        bb[7] = Pnt3f(sceneMin[0], sceneMax[1], sceneMax[2]);	

                        PLangle = osgDegree2Rad(0);
                        Pnt3f   maxAnglePnt1, maxAnglePnt2;

                        for(UInt32 j = 0;j < 8;j++)
                        {
                            Vec3f   vector1(lightpos - center);
                            Vec3f   vector2(lightpos - bb[j]);
                            Real32  newAngle = vector1.enclosedAngle(vector2);
                            if(osgAbs(osgRad2Degree(newAngle)) > 180)
                                newAngle = vector2.enclosedAngle(vector1);
                            if(osgRad2Degree(newAngle) > osgRad2Degree(PLangle))
                            {
                                PLangle = newAngle;
                                maxAnglePnt1 = bb[j];
                            }
                        }

                        for(UInt32 j = 0;j < 8;j++)
                        {
                            Vec3f   vector1(lightpos - maxAnglePnt1);
                            Vec3f   vector2(lightpos - bb[j]);
                            Real32  newAngle = vector1.enclosedAngle(vector2);
                            if(osgAbs(osgRad2Degree(newAngle)) > 180)
                                newAngle = vector2.enclosedAngle(vector1);
                            if(osgRad2Degree(newAngle) > osgRad2Degree(PLangle))
                            {
                                PLangle = newAngle;
                                maxAnglePnt2 = bb[j];
                            }
                        }
	
                        if(osgRad2Degree(PLangle) < 120) //Use one Side only
                        {
                            pData->getLightRoot(i)->getVolume().getCenter(
                                center);
                            dir = lightpos - center;
                            dir.normalize();
                            dir.negate();
                            q.setValue(Vec3f(0, 0, -1), dir);
                            tmpMatrix.setTransform(Vec3f(lightpos), q);

                            vRealPLight.push_back(false);
                        }
                        else
                            //use 6 side Pointlight
                        {
                            dir = Vec3f(0.0, 0.0, -1.0);//lightpos - center;
                            dir.negate();
                            q.setValue(Vec3f(0, 0, -1), dir);
                            tmpMatrix.setTransform(Vec3f(lightpos), q);
                            vRealPLight.push_back(true);
                        }
                    }
                    else
                    {
                        dir = Vec3f(0.0, 0.0, -1.0);//lightpos - center;
                        dir.negate();
                        q.setValue(Vec3f(0, 0, -1), dir);
                        tmpMatrix.setTransform(Vec3f(lightpos), q);
                        vRealPLight.push_back(true);
                    }
                }
                else
                {

                    Vec3f   dist, diff;
                    Pnt3f   center;
                    Pnt3f   sceneMin = 
                        pData->getLightRoot(i)->getVolume().getMin();

                    Pnt3f   sceneMax = 
                        pData->getLightRoot(i)->getVolume().getMax();

                    pData->getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   bb[8];
                    bb[0] = Pnt3f(sceneMin[0], sceneMin[1], sceneMin[2]);
                    bb[1] = Pnt3f(sceneMax[0], sceneMin[1], sceneMin[2]);
                    bb[2] = Pnt3f(sceneMax[0], sceneMax[1], sceneMin[2]);
                    bb[3] = Pnt3f(sceneMin[0], sceneMax[1], sceneMin[2]);
                    bb[4] = Pnt3f(sceneMin[0], sceneMin[1], sceneMax[2]);
                    bb[5] = Pnt3f(sceneMax[0], sceneMin[1], sceneMax[2]);
                    bb[6] = Pnt3f(sceneMax[0], sceneMax[1], sceneMax[2]);
                    bb[7] = Pnt3f(sceneMin[0], sceneMax[1], sceneMax[2]);

                    PLangle = osgDegree2Rad(0);
                    Pnt3f   maxAnglePnt1, maxAnglePnt2;

                    for(UInt32 j = 0;j < 8;j++)
                    {
                        Vec3f   vector1(lightpos - center);
                        Vec3f   vector2(lightpos - bb[j]);
                        Real32  newAngle = vector1.enclosedAngle(vector2);
                        if(osgAbs(osgRad2Degree(newAngle)) > 180)
                            newAngle = vector2.enclosedAngle(vector1);
                        if(osgRad2Degree(newAngle) > osgRad2Degree(PLangle))
                        {
                            PLangle = newAngle;
                            maxAnglePnt1 = bb[j];
                        }
                    }

                    for(UInt32 j = 0;j < 8;j++)
                    {
                        Vec3f   vector1(lightpos - maxAnglePnt1);
                        Vec3f   vector2(lightpos - bb[j]);
                        Real32  newAngle = vector1.enclosedAngle(vector2);
                        if(osgAbs(osgRad2Degree(newAngle)) > 180)
                            newAngle = vector2.enclosedAngle(vector1);
                        if(osgRad2Degree(newAngle) > osgRad2Degree(PLangle))
                        {
                            PLangle = newAngle;
                            maxAnglePnt2 = bb[j];
                        }
                    }

                    if(osgRad2Degree(PLangle) > 175) //Use one Side only
                    {
                        PLangle = osgDegree2Rad(175);
                    }

                    dir = lightpos - center;
                    dir.normalize();
                    dir.negate();

                    q.setValue(Vec3f(0, 0, -1), dir);

                    tmpMatrix.setTransform(Vec3f(lightpos), q);
                    vRealPLight.push_back(false);
                }
            }

            vLCamTrans[i]->setMatrix(tmpMatrix);
        }

        //Feeding new Camera with paramters of original camera
        {
            // Is the Lightsource a Spotlight?
            if(isSpot)
            {
                tmpSpot = dynamic_cast<SpotLight *>(vLights[i].second.get());

                Pnt3f   lightpos = tmpSpot->getPosition();

                if(tmpSpot->getBeacon() != NULL)
                {
                    Matrix  m = tmpSpot->getBeacon()->getToWorld();
                    m.mult(lightpos, lightpos);
                }

                Pnt3f   center;
                pData->getLightRoot(i)->getVolume().getCenter(center);
                
                Vec3f   dir = lightpos - center;
                Real64  dirLength = dir.length();

                Vec3f   diff = (pData->getLightRoot(i)->getVolume().getMax() -
                                pData->getLightRoot(i)->getVolume().getMin());
                Real64  diffLength = diff.length() / 2;
                
                Real64  zNearLimit, zCalcNear = 0;
                Real64  zFar = 1.2 * (dirLength + diffLength);
                Real64  zNear = action->getCamera()->getNear();

                if (diffLength) 
                {
                    // Camera outside of the scene
                    if (dirLength > diffLength)      
                        // Camera outside of the scene
                        zCalcNear = 0.8 * (dirLength - diffLength);
                    // else camera inside of the scene
                    
                    zNear = zCalcNear;
                    zNearLimit = osgMax( 0.01, zFar / 20000 );
                    zNear = osgMax( zNear, zNearLimit );
                }
                
                vLCams[i]->setNear( zNear );
                vLCams[i]->setFar( zFar );
                
                //Using Spot-angle of Spotlight as FOV for LightCamera
                dynamic_cast<PerspectiveCamera *>(vLCams[i].get())->
                    setFov(tmpSpot->getSpotCutOffDeg() * 2);
            }
            // Is the Lightsource a Directional-Light? 
            // Setting up MatrixCamera
            else if(isDirect)
            {
                Matrix  proMatrix, modMatrix;

                MatrixOrthogonal(proMatrix, -sceneWidth,  sceneWidth,
                                            -sceneHeight, sceneHeight,
                                            -sceneWidth,  sceneWidth  );

                // Grabbing ModelView-Matrix from Light-Transformation
                modMatrix = vLCamTrans[i]->getMatrix();

                dynamic_cast<MatrixCamera *>(
                    vLCams[i].get())->setProjectionMatrix(proMatrix);
                dynamic_cast<MatrixCamera *>(
                    vLCams[i].get())->setModelviewMatrix(modMatrix);
            }
            else // If none of above the Lightsource must be a PointLight
            {
                if((getShadowMode() == STD_SHADOW_MAP         ||
                    getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                    getShadowMode() == DITHER_SHADOW_MAP      ||
                    getShadowMode() == PCF_SHADOW_MAP         ||
                    getShadowMode() == PCF2_SHADOW_MAP    ) && vRealPLight[i])
                {
                    Vec3f   dist, diff;
                    Pnt3f   center;

                    pData->getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   lightpos = tmpPoint->getPosition();

                    if(tmpPoint->getBeacon() != NULL)
                    {
                        Matrix  m = tmpPoint->getBeacon()->getToWorld();
                        m.mult(lightpos, lightpos);
                    }

                    dist = (lightpos - center);
                    diff = (pData->getLightRoot(i)->getVolume().getMax() -
                            pData->getLightRoot(i)->getVolume().getMin());

                    Real32  distLength = dist.length();
                    Real32  diffLength = diff.length();

                    vLCams[i]->setNear(0.01f);
                    vLCams[i]->setFar(distLength + diffLength);

                    dynamic_cast<PerspectiveCamera *>(
                        vLCams[i].get())->setFov(osgDegree2Rad(91));
                }
                else
                {
                    Vec3f   dist, diff;
                    Pnt3f   center;
                    pData->getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   lightpos = tmpPoint->getPosition();

                    if(tmpPoint->getBeacon() != NULL)
                    {
                        Matrix  m = tmpPoint->getBeacon()->getToWorld();
                        m.mult(lightpos, lightpos);
                    }

                    dist = (lightpos - center);
                    diff = (pData->getLightRoot(i)->getVolume().getMax() -
                            pData->getLightRoot(i)->getVolume().getMin());

                    Pnt3f   sceneMin = 
                        pData->getLightRoot(i)->getVolume().getMin();
                    Pnt3f   sceneMax = 
                        pData->getLightRoot(i)->getVolume().getMax();

                    Real64  distLength = dist.length();
                    Real64  diffLength = diff.length() / 2;
                    
                    Real64  zNearLimit, zCalcNear = 0;
                    Real64  zFar = 1.2 * (distLength + diffLength);
                    Real64  zNear = action->getCamera()->getNear();
                    if (diffLength) 
                    {
                        // Camera outside of the scene
                        if (distLength > diffLength)      
                            // Camera outside of the scene
                            zCalcNear = 0.8 * (distLength - diffLength);
                        // else camera inside of the scene
                        
                        zNear = zCalcNear;
                        zNearLimit = osgMax( 0.01, zFar / 20000 );
                        zNear = osgMax( zNear, zNearLimit );
                    }
                    
                    vLCams[i]->setNear( zNear );
                    vLCams[i]->setFar( zFar );

                    dynamic_cast<PerspectiveCamera *>(
                        vLCams[i].get())->setFov(PLangle);
                }
            }

            vLCams[i]->setBeacon(vLCamBeacons[i]);
        }
    }
}

void ShadowStage::initializeLights(RenderActionBase *action,
                                   ShadowStageData  *pData )
{
    const ShadowStageData::LightStore  &vLights      = 
        pData->getLights();      

          ShadowStageData::LightStore  &vOldLights   = 
        pData->getOldLights();

          ShadowStageData::LStateStore &vLightStates = 
        pData->getLightStates();

          ShadowStageData::TransStore  &vLCamTrans   = 
        pData->getLightCamTrans();

          ShadowStageData::NodeStore   &vLCamBeacons = 
        pData->getLightCamBeacons();

          ShadowStageData::CamStore    &vLCams       =
        pData->getLightCameras();

    pData->clearLightData();

    FDEBUG(("Initialising lights.\n"));

    vOldLights = vLights;

    //Setting up Light-Cameras, ShadowMaps and TextureChunks
    for(UInt32 i = 0;i < vLights.size();++i)
    {
        bool light_state = vLights[i].second->getOn();

        if(vLights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
        {
            light_state = true;
        }
        else if(vLights[i].second->getShadowMode() == Light::CAST_SHADOW_OFF)
        {
            light_state = false;
        }

        // Remembering initial state of Lights
        vLightStates.push_back(light_state ? 1 : 0);
        //Fill Transformation-List, so it can be used later on
        vLCamTrans.push_back(NULL);
        //Creation of Lightcam-Beacon
        vLCamBeacons.push_back(makeCoredNode<Transform>(&vLCamTrans[i]));

        //Giving new Camera Rotation and Position of the light it belongs to
        {
            //Is the Lightsource a Spotlight?
            if(vLights[i].second->getType() == SpotLight::getClassType())
            {
                //Creation of new Perspective-LightCam
                vLCams.push_back(PerspectiveCamera::create());
            }
            else if(vLights[i].second->getType() == 
                                             DirectionalLight::getClassType())
            {
                vLCams.push_back(MatrixCamera::create());
            }
            else
                // Preparation for PointLight -- In this version just a hack
            {
                vLCams.push_back(PerspectiveCamera::create());
            }
        }

#ifdef MAPS_IN_STAGE
        if(getSceneRoot() == NULL)
        {
            SFATAL << "RootNode not found!" << endLog;
        }
        else
        {
//            getSceneRoot()->addChild(_lightCamBeacons[i]);
        }

        //----------Shadowtexture-Images and Texture-Chunks-----------
        if(_lights[i].second->getType() != PointLight::getClassType())
        {
            _shadowImages.push_back(Image::create());

            // creates a image without allocating main memory.
            _shadowImages[i]->set(Image::OSG_L_PF, 
                                  getMapSize(), getMapSize(), 1, 
                                  1, 1, 0, 
                                  NULL,
                                  Image::OSG_UINT8_IMAGEDATA, 
                                  false);

            ShadowMapStore tmpStore;

            tmpStore.pTexO = TextureObjChunk::create();
            tmpStore.pTexE = TextureEnvChunk::create();
            tmpStore.pFBO  = FrameBufferObject::create();

            _vTexChunks.push_back(tmpStore);

            TextureBufferUnrecPtr pDepthTex = TextureBuffer::create();

            pDepthTex->setTexture(tmpStore.pTexO);

            tmpStore.pFBO->setDepthAttachment(pDepthTex);

            // Preparation of Texture be a Depth-Texture
            {
                _vTexChunks[i].pTexO->setImage(_shadowImages[i]);
                _vTexChunks[i].pTexO->setInternalFormat(GL_DEPTH_COMPONENT_ARB);
                _vTexChunks[i].pTexO->setExternalFormat(GL_DEPTH_COMPONENT_ARB);
                _vTexChunks[i].pTexO->setMinFilter(GL_LINEAR);
                _vTexChunks[i].pTexO->setMagFilter(GL_LINEAR);
                _vTexChunks[i].pTexO->setWrapS(GL_CLAMP_TO_EDGE);
                _vTexChunks[i].pTexO->setWrapT(GL_CLAMP_TO_EDGE);
                _vTexChunks[i].pTexE->setEnvMode(GL_MODULATE);
                _vTexChunks[i].pTexO->setTarget(GL_TEXTURE_2D);
            }
        }
        else
            //Light is a point light
        {
            //TODO: Texturgr�se anpassen, je nach Bedarf
            GLint   max_texture_size;
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size); //not active

            _shadowImages.push_back(Image::create());

            // creates a image without allocating main memory.
            if((getShadowMode() == STD_SHADOW_MAP         ||
                getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                getShadowMode() == DITHER_SHADOW_MAP      ||
                getShadowMode() == PCF_SHADOW_MAP         ||
                getShadowMode() == PCF2_SHADOW_MAP          ))
            {
                _shadowImages[i]->set(Image::OSG_L_PF, getMapSize(),
                                      getMapSize(),
                                      1, 1, 1, 0, NULL,
                                      Image::OSG_UINT8_IMAGEDATA, false);
            }
            else
            {
                _shadowImages[i]->set(Image::OSG_L_PF, getMapSize(),
                                      getMapSize(),
                                      1, 1, 1, 0, NULL,
                                      Image::OSG_UINT8_IMAGEDATA, false);
            }

            ShadowMapStore tmpStore;

            tmpStore.pTexO = TextureObjChunk::create();
            tmpStore.pTexE = TextureEnvChunk::create();
            tmpStore.pFBO  = FrameBufferObject::create();
            
            _vTexChunks.push_back(tmpStore);

            TextureBufferUnrecPtr pDepthTex = TextureBuffer::create();

            pDepthTex->setTexture(tmpStore.pTexO);

            tmpStore.pFBO->setDepthAttachment(pDepthTex);

            // Preparation of Texture be a Depth-Texture
            {
                _vTexChunks[i].pTexO->setImage(_shadowImages[i]);
                _vTexChunks[i].pTexO->setInternalFormat(GL_DEPTH_COMPONENT_ARB);
                _vTexChunks[i].pTexO->setExternalFormat(GL_DEPTH_COMPONENT_ARB);
                _vTexChunks[i].pTexO->setMinFilter(GL_LINEAR);
                _vTexChunks[i].pTexO->setMagFilter(GL_LINEAR);
                _vTexChunks[i].pTexO->setWrapS(GL_CLAMP_TO_BORDER);
                _vTexChunks[i].pTexO->setWrapT(GL_CLAMP_TO_BORDER);
                _vTexChunks[i].pTexE->setEnvMode(GL_MODULATE);
                _vTexChunks[i].pTexO->setTarget(GL_TEXTURE_2D);
            }

        }
#endif
    }

    updateLights(action, pData);
}



void ShadowStage::checkLightsOcclusion(RenderActionBase *action)
{
#if 0
    if ( !getDisableOccludedLights() )
    {
        return;
    }
    
    RenderAction *ract = dynamic_cast<RenderAction *>(action);

    if (ract == NULL)
        return;

    for(UInt32 i = 0;i < _lights.size();i++)
    {
        Node *node = _lights[i].first;

        // now make a occlusion test for all light sources.
        bool occluded = false;

        if(glGenQueriesARB != NULL) // occlusion queries supported?
        {
            Matrix view;
            if(ract->getCamera() != NULL)
            {
                ract->getCamera()->getViewing(
                    view,
                    ract->getViewport()->getPixelWidth (),
                    ract->getViewport()->getPixelHeight());
            }

            BoxVolume     vol = node->getVolume();

            Matrix m = view;
            if(node->getParent() != NULL)
                m.mult(node->getParent()->getToWorld());
            vol.transform(m);

            // ignore objects behind the camera.
            if(vol.getMax()[2] < 0.0f)
            {
                glDepthMask(GL_FALSE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    
                if(this->_occlusionQuery == 0)
                    glGenQueriesARB(1, &this->_occlusionQuery);
    
                const BoxVolume    & vol = node->getVolume();

                Pnt3f min,max;
                vol.getBounds(min, max);
    
                glBeginQueryARB(GL_SAMPLES_PASSED_ARB, 
                                this->_occlusionQuery);
                this->drawOcclusionBB(min, max);
                glEndQueryARB(GL_SAMPLES_PASSED_ARB);
    
                glDepthMask(GL_TRUE);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    
                GLuint pixels = 0;
                glGetQueryObjectuivARB(this->_occlusionQuery, //not active
                                       GL_QUERY_RESULT_ARB, &pixels);
    
                occluded = (pixels == 0);
            }
        }

        if(occluded)
        {
            _lightStates[i] = 0;
        }
        else
        {
            bool light_state = _lights[i].second->getOn();
            if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
                light_state = true;
            else if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_OFF)
                light_state = false;

            _lightStates[i] = (light_state ? 1 : 0);
        }
    }

    //updateLights();
#endif
}


void ShadowStage::drawOcclusionBB(const Pnt3f &bbmin, const Pnt3f &bbmax)
{
#if 1

#if 0
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f( bbmin[0], bbmin[1], bbmax[2]); // 0
    glVertex3f( bbmax[0], bbmin[1], bbmax[2]); // 1
    glVertex3f( bbmin[0], bbmax[1], bbmax[2]); // 2
    glVertex3f( bbmax[0], bbmax[1], bbmax[2]); // 3
    glVertex3f( bbmin[0], bbmax[1], bbmin[2]); // 4
    glVertex3f( bbmax[0], bbmax[1], bbmin[2]); // 5
    glVertex3f( bbmin[0], bbmin[1], bbmin[2]); // 6
    glVertex3f( bbmax[0], bbmin[1], bbmin[2]); // 7
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f( bbmax[0], bbmax[1], bbmin[2]); // 5
    glVertex3f( bbmax[0], bbmax[1], bbmax[2]); // 3
    glVertex3f( bbmax[0], bbmin[1], bbmin[2]); // 7
    glVertex3f( bbmax[0], bbmin[1], bbmax[2]); // 1
    glVertex3f( bbmin[0], bbmin[1], bbmin[2]); // 6
    glVertex3f( bbmin[0], bbmin[1], bbmax[2]); // 0
    glVertex3f( bbmin[0], bbmax[1], bbmin[2]); // 4
    glVertex3f( bbmin[0], bbmax[1], bbmax[2]); // 2
    glEnd();

#else

    // not sure if this is faster but it reduces the amount of
    // gl commands.
    const GLubyte indices[16] = { 0,1,2,3,4,5,6,7,  5,3,7,1,6,0,4,2 };
    Real32 vertices[24];
    vertices[0]  = bbmin[0]; vertices[1]  = bbmin[1]; vertices[2]  = bbmax[2];
    vertices[3]  = bbmax[0]; vertices[4]  = bbmin[1]; vertices[5]  = bbmax[2];
    vertices[6]  = bbmin[0]; vertices[7]  = bbmax[1]; vertices[8]  = bbmax[2];
    vertices[9]  = bbmax[0]; vertices[10] = bbmax[1]; vertices[11] = bbmax[2];
    vertices[12] = bbmin[0]; vertices[13] = bbmax[1]; vertices[14] = bbmin[2];
    vertices[15] = bbmax[0]; vertices[16] = bbmax[1]; vertices[17] = bbmin[2];
    vertices[18] = bbmin[0]; vertices[19] = bbmin[1]; vertices[20] = bbmin[2];
    vertices[21] = bbmax[0]; vertices[22] = bbmin[1]; vertices[23] = bbmin[2];

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_BYTE, &indices[0]);
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_BYTE, &indices[8]);
    glDisableClientState(GL_VERTEX_ARRAY);

#endif

#else

    if(_occ_bb_dl == 0)
    {
        // we create a display list for rendering the occlusion
        // bounding box.
        // is this faster ??? need to check it amz.
        Pnt3f min(-0.5f, -0.5f, -0.5f);
        Pnt3f max(0.5f, 0.5f, 0.5f);
        _occ_bb_dl = glGenLists(1);

        const GLubyte indices[16] = { 0,1,2,3,4,5,6,7,  5,3,7,1,6,0,4,2 };
        Real32 vertices[24];
        vertices[0]  = min[0]; vertices[1]  = min[1]; vertices[2]  = max[2];
        vertices[3]  = max[0]; vertices[4]  = min[1]; vertices[5]  = max[2];
        vertices[6]  = min[0]; vertices[7]  = max[1]; vertices[8]  = max[2];
        vertices[9]  = max[0]; vertices[10] = max[1]; vertices[11] = max[2];
        vertices[12] = min[0]; vertices[13] = max[1]; vertices[14] = min[2];
        vertices[15] = max[0]; vertices[16] = max[1]; vertices[17] = min[2];
        vertices[18] = min[0]; vertices[19] = min[1]; vertices[20] = min[2];
        vertices[21] = max[0]; vertices[22] = min[1]; vertices[23] = min[2];

        glNewList(_occ_bb_dl, GL_COMPILE);
            glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_BYTE, &indices[0]);
            glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_BYTE, &indices[8]);
            glDisableClientState(GL_VERTEX_ARRAY);
        glEndList();
    }

    Vec3f s = bbmax - bbmin;
    Vec3f t = bbmin + bbmax;
    t *= 0.5f;
    glPushMatrix();
        glTranslatef(t[0], t[1], t[2]);
        glScalef(s[0], s[1], s[2]);
        glCallList(_occ_bb_dl);
    glPopMatrix();

#endif
}
