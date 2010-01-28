/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2010 by the OpenSG Forum                     *
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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaLight.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaInstanceLight.h"

#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

// ===========================================================================

ColladaInstInfoTransitPtr
ColladaLight::ColladaLightInstInfo::create(
    ColladaElement *colInstParent, ColladaInstanceLight *colInst,
    Node           *beaconN                                      )
{
    return ColladaInstInfoTransitPtr(
        new ColladaLightInstInfo(colInstParent, colInst, beaconN));
}

void
ColladaLight::ColladaLightInstInfo::process(void)
{
    Node *lightInstN = dynamic_cast<Node *>(
        getColInst()->getTargetElem()->createInstance(this));

    if(lightInstN == NULL)
        return;

    Node *rootN = getColInst()->getGlobal()->getRoot();

    while(rootN->getNChildren() > 0)
    {
        lightInstN->addChild(rootN->getChild(0));
    }

    rootN->addChild(lightInstN);
}

Node *
ColladaLight::ColladaLightInstInfo::getBeacon(void) const
{
    return _beacon;
}

ColladaLight::ColladaLightInstInfo::ColladaLightInstInfo(
    ColladaElement *colInstParent, ColladaInstanceLight *colInst,
    Node           *beaconN                                      )
    
    : Inherited(colInstParent, colInst)
    , _beacon  (beaconN               )
{
}

ColladaLight::ColladaLightInstInfo::~ColladaLightInstInfo(void)
{
}

// ===========================================================================

// Ambient light sources are a bit tricky to handle. First all ambient sources
// in the scene have to be accumulated and then an appropriate LightModelChunk
// must be inserted at the top of the scene (using a ChunkOverrideGroup).
// The first part is done by ColladaLight::createInstance(), which will also
// place an instance of ColladaLightAmbientInstInfo into the instance queue.
// That instance will then cause the insertion of the LightModelChunk.

ColladaInstInfoTransitPtr
ColladaLight::ColladaLightAmbientInstInfo::create(
    ColladaElement *colInstParent, ColladaInstanceLight *colInst)
{
    return ColladaInstInfoTransitPtr(
        new ColladaLightAmbientInstInfo(colInstParent, colInst));
}

void
ColladaLight::ColladaLightAmbientInstInfo::process(void)
{
    dynamic_cast<ColladaLight *>(
        getColInst()->getTargetElem())->createAmbientLight(this);
}

ColladaLight::ColladaLightAmbientInstInfo::ColladaLightAmbientInstInfo(
    ColladaElement *colInstParent, ColladaInstanceLight *colInst)

    : Inherited(colInstParent, colInst)
{
}

ColladaLight::ColladaLightAmbientInstInfo::~ColladaLightAmbientInstInfo(void)
{
}

// ===========================================================================

ColladaLight::LightLoaderStateTransitPtr
ColladaLight::LightLoaderState::create(void)
{
    return LightLoaderStateTransitPtr(new LightLoaderState());
}

LightModelChunk *
ColladaLight::LightLoaderState::getLightModelChunk(void) const
{
    return _lightModel;
}

void
ColladaLight::LightLoaderState::setLightModelChunk(LightModelChunk *chunk)
{
    _lightModel = chunk;
}

ColladaLight::LightLoaderState::LightLoaderState(void)
    : Inherited  ()
    , _lightModel()
{
}

ColladaLight::LightLoaderState::~LightLoaderState(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaLight::_regHelper(
    &ColladaLight::create, "light");
const std::string                ColladaLight::_loaderStateName("ColladaLight");


ColladaElementTransitPtr
ColladaLight::create(daeElement *elem, ColladaGlobal *global)
{
    if(global->getLoaderState(_loaderStateName) == NULL)
    {
        LightLoaderStateRefPtr state = LightLoaderState::create();

        global->addLoaderState(_loaderStateName, state);
    }

    return ColladaElementTransitPtr(new ColladaLight(elem, global));
}

void
ColladaLight::read(ColladaElement *colElemParent)
{
    domLightRef light = getDOMElementAs<domLight>();

    OSG_COLLADA_LOG(("ColladaLight::read id [%s]\n", light->getId()));
}

Node *
ColladaLight::createInstance(ColladaInstInfo *colInstInfo)
{
    domLightRef light = getDOMElementAs<domLight>();

    OSG_COLLADA_LOG(("ColladaLight::createInstance id [%s]\n",
                     light->getId()));

    NodeUnrecPtr                      retVal        = NULL;
    ColladaLightInstInfo             *lightInstInfo =
        dynamic_cast<ColladaLightInstInfo *>(colInstInfo);
    domLight::domTechnique_commonRef  techComm      =
        light->getTechnique_common();

    const domTechnique_Array &techs = light->getTechnique_array();

    for(UInt32 i = 0; i < techs.getCount(); ++i)
    {
        retVal = createInstanceTechnique(lightInstInfo, techs[i]);

        // stop as soon as something is created
        if(retVal != NULL)
            return retVal;
    }

    // if we get here no technique was choosen so we evaluate
    // <technique_common>
    retVal = createInstanceCommon(lightInstInfo, techComm);

    return retVal;
}

void
ColladaLight::createAmbientLight(ColladaLightAmbientInstInfo *colInstInfo)
{
    OSG_COLLADA_LOG(("ColladaLight::createAmbientLight\n"));

    LightLoaderState *state =
        getGlobal()->getLoaderStateAs<LightLoaderState>(_loaderStateName);
    OSG_ASSERT(state != NULL);

    ChunkOverrideGroupUnrecPtr coGroup  = ChunkOverrideGroup::create();
    NodeUnrecPtr               coGroupN = makeNodeFor(coGroup);

    coGroup->addChunk(state->getLightModelChunk());

    Node *rootN = getGlobal()->getRoot();

    while(rootN->getNChildren() > 0)
    {
        coGroupN->addChild(rootN->getChild(0));
    }

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true)
    {
        setName(coGroupN, "OpenSG_AmbientLight");
    }

    rootN->addChild(coGroupN);
}

ColladaLight::ColladaLight(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaLight::~ColladaLight(void)
{
}

Node *
ColladaLight::createInstanceTechnique(
    ColladaLightInstInfo *colInstInfo, domTechnique *tech)
{
    domLightRef light = getDOMElementAs<domLight>();

    OSG_COLLADA_LOG(("ColladaLight::createInstanceTechnique id [%s] "
                     "profile [%s]\n", light->getId(), tech->getProfile()));

    return NULL;
}

Node *
ColladaLight::createInstanceCommon(
    ColladaLightInstInfo *colInstInfo, domLight::domTechnique_common *tech)
{
    domLightRef light = getDOMElementAs<domLight>();

    OSG_COLLADA_LOG(("ColladaLight::createInstanceCommon id [%s]\n",
                     light->getId()));

    NodeUnrecPtr                                     lightN      = NULL;

    domLight::domTechnique_common::domAmbientRef     ambient     =
        tech->getAmbient();
    domLight::domTechnique_common::domDirectionalRef directional =
        tech->getDirectional();
    domLight::domTechnique_common::domPointRef       point       =
        tech->getPoint();
    domLight::domTechnique_common::domSpotRef        spot        =
        tech->getSpot();

    if(ambient != NULL)
    {
        Color4f lightColor(ambient->getColor()->getValue()[0],
                           ambient->getColor()->getValue()[1],
                           ambient->getColor()->getValue()[2], 1.f);

        LightLoaderState *state =
            getGlobal()->getLoaderStateAs<LightLoaderState>(_loaderStateName);
        OSG_ASSERT(state != NULL);

        LightModelChunkUnrecPtr lmChunk = state->getLightModelChunk();

        if(state->getLightModelChunk() == NULL)
        {
            lmChunk = LightModelChunk::create();
            lmChunk->setAmbient(Color4f(0.f, 0.f, 0.f, 1.f));

            state->setLightModelChunk(lmChunk);

            // only place one instance into the inst queue, it will
            // add the LightModelChunk with the accumulated ambient
            // for the scene
            ColladaInstInfoRefPtr ambientInstInfo =
                ColladaLightAmbientInstInfo::create(
                    colInstInfo->getColInstParent(),
                    dynamic_cast<ColladaInstanceLight *>(
                        colInstInfo->getColInst())        );

            getGlobal()->editInstQueue().push_back(ambientInstInfo);
        }

        lightColor[0] = 
            osgClamp(0.f, lmChunk->getAmbient()[0] + lightColor[0], 1.f);
        lightColor[1] =
            osgClamp(0.f, lmChunk->getAmbient()[1] + lightColor[1], 1.f);
        lightColor[2] =
            osgClamp(0.f, lmChunk->getAmbient()[2] + lightColor[0], 1.f);

        lmChunk->setAmbient(lightColor);
    }

    if(directional != NULL)
    {
        Color4f lightColor(directional->getColor()->getValue()[0],
                           directional->getColor()->getValue()[1],
                           directional->getColor()->getValue()[2], 1.f);

        DirectionalLightUnrecPtr dl = DirectionalLight::create();
        lightN                      = makeNodeFor(dl);

        dl->setBeacon  (colInstInfo->getBeacon());
        dl->setDiffuse (lightColor              );
        dl->setSpecular(lightColor              );
    }

    if(point != NULL)
    {
        Color4f lightColor(point->getColor()->getValue()[0],
                           point->getColor()->getValue()[1],
                           point->getColor()->getValue()[2], 1.f);

        PointLightUnrecPtr pl = PointLight::create();
        lightN                = makeNodeFor(pl);

        Real32 constAtt = 1.f;
        Real32 linAtt   = 0.f;
        Real32 quadAtt  = 0.f;

        if(point->getConstant_attenuation() != NULL)
            constAtt = point->getConstant_attenuation()->getValue();

        if(point->getLinear_attenuation() != NULL)
            linAtt   = point->getLinear_attenuation()->getValue();

        if(point->getQuadratic_attenuation() != NULL)
            quadAtt  = point->getQuadratic_attenuation()->getValue();

        pl->setBeacon              (colInstInfo->getBeacon());
        pl->setDiffuse             (lightColor              );
        pl->setSpecular            (lightColor              );
        pl->setConstantAttenuation (constAtt                );
        pl->setLinearAttenuation   (linAtt                  );
        pl->setQuadraticAttenuation(quadAtt                 );
    }

    if(spot != NULL)
    {
        Color4f lightColor(spot->getColor()->getValue()[0],
                           spot->getColor()->getValue()[1],
                           spot->getColor()->getValue()[2], 1.f);

        SpotLightUnrecPtr sl = SpotLight::create();
        lightN               = makeNodeFor(sl);

        Real32 constAtt =   1.f;
        Real32 linAtt   =   0.f;
        Real32 quadAtt  =   0.f;
        Real32 cutOff   = 180.f;
        Real32 exponent =   0.f;

        if(spot->getConstant_attenuation() != NULL)
            constAtt = spot->getConstant_attenuation()->getValue();

        if(spot->getLinear_attenuation() != NULL)
            linAtt   = spot->getLinear_attenuation()->getValue();

        if(spot->getQuadratic_attenuation() != NULL)
            quadAtt  = spot->getQuadratic_attenuation()->getValue();

        if(spot->getFalloff_angle() != NULL)
            cutOff   = spot->getFalloff_angle()->getValue();

        if(spot->getFalloff_exponent() != NULL)
            exponent = spot->getFalloff_exponent()->getValue();

        sl->setBeacon              (colInstInfo->getBeacon());
        sl->setDiffuse             (lightColor              );
        sl->setSpecular            (lightColor              );
        sl->setConstantAttenuation (constAtt                );
        sl->setLinearAttenuation   (linAtt                  );
        sl->setQuadraticAttenuation(quadAtt                 );
        sl->setSpotCutOff          (osgDegree2Rad(cutOff)   );
        sl->setSpotExponent        (exponent                );
    }

    if(lightN != NULL)
    {
        editInstStore().push_back(lightN);

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           light->getName()                                      != NULL   )
        {
            setName(lightN, light->getName());
        }
    }

    return lightN;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
