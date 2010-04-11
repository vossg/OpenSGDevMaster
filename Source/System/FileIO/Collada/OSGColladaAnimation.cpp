/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#include "OSGColladaAnimation.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaAnimationClip.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceAnimation.h"
#include "OSGColladaLog.h"
#include "OSGColladaNode.h"
#include "OSGColladaSource.h"

#include "OSGAnimMatrixDataSource.h"
#include "OSGAnimQuaternionDataSource.h"
#include "OSGAnimVec3fDataSource.h"
#include "OSGAnimTargetAttachment.h"

#include "OSGNameAttachment.h"

#include <dom/domAnimation.h>

OSG_BEGIN_NAMESPACE

ColladaInstInfoTransitPtr
ColladaAnimation::ColladaAnimationInstInfo::create(
    ColladaAnimationClip     *colInstParent,
    ColladaInstanceAnimation *colInst,
    ColladaAnimation         *colInstTarget,
    AnimKeyFrameTemplate     *animTmpl      )
{
    return ColladaInstInfoTransitPtr(
        new ColladaAnimationInstInfo(colInstParent, colInst,
                                     colInstTarget, animTmpl));
}

ColladaAnimation *
ColladaAnimation::ColladaAnimationInstInfo::getAnim(void) const
{
    return _colInstTarget;
}

AnimKeyFrameTemplate *
ColladaAnimation::ColladaAnimationInstInfo::getTemplate(void) const
{
    return _animTmpl;
}

void
ColladaAnimation::ColladaAnimationInstInfo::process(void)
{
#if !defined(OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK)
    ColladaAnimation *colAnim =
        dynamic_cast<ColladaAnimation *>(getColInst()->getTargetElem());
    OSG_ASSERT(colAnim != NULL);

    colAnim->createInstance(this);
#else
    OSG_ASSERT(getAnim() != NULL);

    getAnim()->createInstance(this);
#endif
}

ColladaAnimation::ColladaAnimationInstInfo::ColladaAnimationInstInfo(
    ColladaAnimationClip     *colInstParent,
    ColladaInstanceAnimation *colInst,
    ColladaAnimation         *colInstTarget,
    AnimKeyFrameTemplate     *animTmpl      )

    : Inherited     (colInstParent, colInst)
    , _colInstTarget(colInstTarget)
    , _animTmpl     (animTmpl)
{
}

ColladaAnimation::ColladaAnimationInstInfo::~ColladaAnimationInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaAnimation::_regHelper(
    &ColladaAnimation::create, "animation");


ColladaElementTransitPtr
ColladaAnimation::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaAnimation(elem, global));
}

void
ColladaAnimation::read(ColladaElement *colElemParent)
{
    domAnimationRef anim = getDOMElementAs<domAnimation>();

    OSG_COLLADA_LOG(("ColladaAnimation::read id [%s]\n", anim->getId()));

    readAnim(anim);

    const domAnimation_Array &subAnims = anim->getAnimation_array();

    for(UInt32 i = 0; i < subAnims.getCount(); ++i)
    {
        readAnim(subAnims[i]);
    }
}

AnimKeyFrameTemplate *
ColladaAnimation::createInstance(ColladaInstInfo *colInstInfo)
{
    domAnimationRef anim = getDOMElementAs<domAnimation>();

    OSG_COLLADA_LOG(("ColladaAnimation::createInstance id [%s]\n",
                     anim->getId()));

    ColladaAnimationInstInfo *colAnimInstInfo =
        dynamic_cast<ColladaAnimationInstInfo *>(colInstInfo);
#if 0
    ColladaAnimationClip     *colAnimClip     =
        dynamic_cast<ColladaAnimationClip *>(colInstInfo->getColInstParent());
#endif
    AnimKeyFrameTemplate     *animTmpl        =
        colAnimInstInfo->getTemplate();

    OSG_ASSERT(animTmpl != NULL);

    createInstanceAnim(anim,
                       colInstInfo->getColInstParent(),
                       colInstInfo->getColInst      (),
                       animTmpl                        );
    
    const domAnimation_Array &subAnims = anim->getAnimation_array();

    for(UInt32 i = 0; i < subAnims.getCount(); ++i)
    {
        createInstanceAnim(subAnims[i],
                           colInstInfo->getColInstParent(),
                           colInstInfo->getColInst      (),
                           animTmpl                        );
    }

    editInstStore().push_back(animTmpl);

    return animTmpl;
}

ColladaAnimation::ColladaAnimation(daeElement *elem, ColladaGlobal *global)
    : Inherited (elem, global)
    , _sourceMap()
{
}

ColladaAnimation::~ColladaAnimation(void)
{
}

void
ColladaAnimation::readAnim(domAnimation *anim)
{
    OSG_COLLADA_LOG(("ColladaAnimation::readAnim id [%s]\n",
                     (anim->getId() != NULL ? anim->getId() : "") ));

    const domSource_Array &sources = anim->getSource_array();

    for(UInt32 i = 0; i < sources.getCount(); ++i)
    {
        ColladaSourceRefPtr colSource =
            getUserDataAs<ColladaSource>(sources[i]);

        if(colSource == NULL)
        {
            colSource = dynamic_pointer_cast<ColladaSource>(
                ColladaElementFactory::the()->create(sources[i], getGlobal()));

            colSource->read(this);
        }

        _sourceMap.insert(
            SourceMap::value_type(sources[i]->getId(), colSource));
    }

    const domAnimation_Array &subAnims = anim->getAnimation_array();

    for(UInt32 i = 0; i < subAnims.getCount(); ++i)
    {
        readAnim(subAnims[i]);
    }
}

void
ColladaAnimation::createInstanceAnim(
    domAnimation           *anim,     ColladaElement       *colInstParent,
    ColladaInstanceElement *colInst,  AnimKeyFrameTemplate *animTmpl      )
{
    ColladaAnimationClip   *colAnimClip =
        dynamic_cast<ColladaAnimationClip *>(colInstParent);
    const domChannel_Array &channels    = anim->getChannel_array();

    for(UInt32 i = 0; i < channels.getCount(); ++i)
    {
        daeURI        samplerURI = channels[i]->getSource();
        domSamplerRef sampler    =
            daeSafeCast<domSampler>(samplerURI.getElement());

        if(sampler == NULL)
        {
            SWARNING << "ColladaAnimation::createInstanceAnim: Could not "
                     << "find <sampler> [" << samplerURI.str()
                     << "] for <channel> [" << i << "] in animation id ["
                     << (anim->getId() != NULL ? anim->getId() : "")
                     << std::endl;
            continue;
        }

        DataSourceInfo dsInfo;

        createDataSource(channels[i], sampler, dsInfo);

        handleInput        (channels[i], sampler, colAnimClip, animTmpl, dsInfo);
        handleOutput       (channels[i], sampler,              animTmpl, dsInfo);
        handleInterpolation(channels[i], sampler,              animTmpl, dsInfo);

        if(dsInfo._dataSource == NULL)
        {
            SWARNING << "ColladaAnimation::createInstanceAnim: Failed to "
                     << "create a data source for <channel> [" << i 
                     << "]. Ignoring." << std::endl;
            continue;
        }

        OSG_COLLADA_LOG(("ColladaAnimation::createInstanceAnim: Filled "
                         "data source for channel [%d] target [%s]\n",
                         i, channels[i]->getTarget()));

        animTmpl->editMFSources  ()->push_back(dsInfo._dataSource);
        animTmpl->editMFTargetIds()->push_back(dsInfo._target    );
    }

    domAnimation_clipRef animClip =
        colAnimClip->getDOMElementAs<domAnimation_clip>();

    animTmpl->setName(animClip->getName());
}

void
ColladaAnimation::createDataSource(
    domChannel *channel, domSampler *sampler, DataSourceInfo &dsInfo)
{
    domInputLocalRef input = findInput(sampler, "OUTPUT");

    if(input == NULL)
    {
        SWARNING << "ColladaAnimation::createDataSource: No <input> "
                 << "with semantic OUTPUT in <sampler> ["
                 << (sampler->getId() != NULL ? sampler->getId() : "")
                 << "]." << std::endl;
        return;
    }

    std::string      sourceId = input->getSource().id();
    SourceMapConstIt smIt     = _sourceMap.find(sourceId);

    if(smIt == _sourceMap.end())
    {
        SWARNING << "ColladaAnimation::createDataSource: No <source> "
                 << "with id [" << sourceId << "] found." << std::endl;
        return;
    }

    std::string fieldSuffix;
    std::string target   (channel->getTarget()             );
    daeSidRef   targetRef(target, getGlobal()->getDocRoot());
    daeElement *targetElem = targetRef.resolve().elt;

    if(targetElem == NULL)
    {
        SWARNING << "ColladaAnimation::createDataSource: Could not resolve ["
                 << target << "]. Ignoring" << std::endl;
        return;
    }

    switch(targetElem->getElementType())
    {
    case COLLADA_TYPE::MATRIX:
    {
        dsInfo._target     = channel->getTarget() + std::string(".matrix");
        dsInfo._dataSource = AnimMatrixDataSource::create();
    }
    break;

    case COLLADA_TYPE::TRANSLATE:
    {
        dsInfo._target     = channel->getTarget() + std::string(".translate");
        dsInfo._dataSource = AnimVec3fDataSource::create();
    }
    break;

    case COLLADA_TYPE::ROTATE:
    {
        dsInfo._target     = channel->getTarget() + std::string(".rotate");
        dsInfo._dataSource = AnimQuaternionDataSource::create();
    }
    break;

    default:
    {
        dsInfo._dataSource = NULL;

        SWARNING << "ColladaAnimation::createDataSource: Target [" << target
                 << "] has unhandled type [" << targetElem->getElementType()
                 << "]. Ignoring" << std::endl;
        return;
    }
    };

    // make sure the target has a AnimTargetAttachment on it
    daeElement *targetParentElem = targetElem->getParentElement();
    domNode    *parentNode       = daeSafeCast<domNode>(targetParentElem);

    if(parentNode == NULL)
    {
        SWARNING << "ColladaAnimation::createDataSource: Target [" << target
                 << "] does not have a parent <node>.\n" << std::endl;
        return;
    }
    
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(parentNode);

    if(colNode == NULL)
    {
        SWARNING << "ColladaAnimation::createDataSource: Parent <node> for "
                 << "target [" << target << "] has no ColladaNode structure."
                 << std::endl;
        return;
    }

    std::string::size_type slashPos  = target.find('/');
    std::string            targetSID = target.substr(slashPos + 1);

    Node *targetNode = colNode->getNodeBySid(0, targetSID);

    if(targetNode == NULL)
    {
        SWARNING << "ColladaAnimation::createDataSource: Could not find "
                 << "node for sid [" << targetSID << "]." << std::endl;
        return;
    }

    NodeCore *targetCore = targetNode->getCore();
    setTargetId(targetCore, target);

    OSG_COLLADA_LOG(("ColladaAnimation::createDataSource: Setting "
                     "AnimTargetAttachment targetId [%s] for core [%p] node [%p] [%s]\n",
                     target.c_str(), targetCore, targetNode,
                     (getName(targetNode) != NULL ? getName(targetNode) : "")));
}

void
ColladaAnimation::handleInput(
    domChannel           *channel,     domSampler           *sampler,
    ColladaAnimationClip *colAnimClip, AnimKeyFrameTemplate *animTmpl,
    DataSourceInfo       &dsInfo                                      )
{
    if(dsInfo._dataSource == NULL)
        return;

    domInputLocalRef input = findInput(sampler, "INPUT");

    if(input == NULL)
    {
        SWARNING << "ColladaAnimation::handleInput: No <input> "
                 << "with semantic INPUT in sampler ["
                 << (sampler->getId() != NULL ? sampler->getId() : "")
                 << "]. Ignoring." << std::endl;
        return;
    }

    Real32           startT   =
        colAnimClip->getDOMElementAs<domAnimation_clip>()->getStart();
    Real32           endT     =
        colAnimClip->getDOMElementAs<domAnimation_clip>()->getEnd  ();

    std::string      sourceId = input->getSource().id();
    SourceMapConstIt smIt     = _sourceMap.find(sourceId);

    if(smIt == _sourceMap.end())
    {
        SWARNING << "ColladaAnimation::handleInput: No <source> "
                 << "with id [" << sourceId << "] found." << std::endl;
        return;
    }

    const ColladaSource::FloatStore &inputStore = smIt->second->getFloatStore();

    ColladaSource::FloatStoreConstIt startIt =
        std::lower_bound(inputStore.begin(), inputStore.end(), startT);
    ColladaSource::FloatStoreConstIt endIt   =
        std::upper_bound(inputStore.begin(), inputStore.end(), endT  );

    dsInfo._firstKey = std::distance(inputStore.begin(), startIt);
    dsInfo._lastKey  = std::distance(inputStore.begin(), endIt  );

    OSG_COLLADA_LOG(("ColladaAnimation::handleInput: "
                     "Using key range [%d %d] [%f %f] [%f %f] of [0 %"
                     PRISize"]\n",
                     dsInfo._firstKey, dsInfo._lastKey,
                     inputStore[dsInfo._firstKey   ],
                     inputStore[dsInfo._lastKey - 1],
                     startT, endT, inputStore.size()));

    for(UInt32 i = dsInfo._firstKey; i < dsInfo._lastKey; ++i)
    {
        dsInfo._dataSource->editMFInValues()->push_back(inputStore[i]);
    }
}


void
ColladaAnimation::handleOutput(
    domChannel           *channel,  domSampler     *sampler,
    AnimKeyFrameTemplate *animTmpl, DataSourceInfo &dsInfo  )
{
    if(dsInfo._dataSource == NULL)
        return;

    domInputLocalRef input = findInput(sampler, "OUTPUT");

    if(input == NULL)
    {
        SWARNING << "ColladaAnimation::handleOutput: No <input> "
                 << "with semantic OUTPUT in <sampler> ["
                 << (sampler->getId() != NULL ? sampler->getId() : "")
                 << "]." << std::endl;
        return;
    }

    std::string      sourceId = input->getSource().id();
    SourceMapConstIt smIt     = _sourceMap.find(sourceId);

    if(smIt == _sourceMap.end())
    {
        SWARNING << "ColladaAnimation::handleOutput: No <source> "
                 << "with id [" << sourceId << "] found." << std::endl;
        return;
    }

    AnimMatrixDataSourceRefPtr     matrixDS =
        dynamic_pointer_cast<AnimMatrixDataSource>(dsInfo._dataSource);
    AnimVec3fDataSourceRefPtr      vec3fDS  =
        dynamic_pointer_cast<AnimVec3fDataSource>(dsInfo._dataSource);
    AnimQuaternionDataSourceRefPtr quatDS   =
        dynamic_pointer_cast<AnimQuaternionDataSource>(dsInfo._dataSource);

    if(matrixDS != NULL)
    {
#if defined(OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK)
        bool                              noAnim = true;
#endif

        ColladaSource::MatrixStoreConstIt matIt  =
            smIt->second->getMatrixStore().begin() + dsInfo._firstKey;
        ColladaSource::MatrixStoreConstIt matEnd =
            smIt->second->getMatrixStore().begin() + dsInfo._lastKey;

#if defined(OSG_USE_COLLADA_ANIMCLIP_INSTANCE_HACK)
        // remove animations that do not change during the clip we instantiate
        // them from

        for(; matIt != matEnd; ++matIt)
        {
            if(*matIt != smIt->second->getMatrixStore()[dsInfo._firstKey])
            {
                noAnim = false;
                break;
            }

        }

        if(noAnim == true)
        {
            OSG_COLLADA_LOG(("ColladaAnimation::handleOutput: No anim for "
                             "current clip - skipping animation\n"));

            dsInfo._dataSource = NULL;
            return;
        }

        matIt  = smIt->second->getMatrixStore().begin() + dsInfo._firstKey;
        matEnd = smIt->second->getMatrixStore().begin() + dsInfo._lastKey;
#endif

        for(; matIt != matEnd; ++matIt)
        {
            matrixDS->editMFValues()->push_back(*matIt);
        }
        
    }
    else if(vec3fDS != NULL)
    {
        SWARNING << "ColladaAnimation::handleOutput: Vec3fDataSource NIY"
                 << std::endl;
    }
    else if(quatDS != NULL)
    {
        SWARNING << "ColladaAnimation::handleOutput: QuaternionDataSource NIY"
                 << std::endl;
    }
    else
    {
        SWARNING << "ColladaAnimation::handleOutput: Unknown DataSource type."
                 << std::endl;
    }
}

void
ColladaAnimation::handleInterpolation(
    domChannel             *channel,  domSampler     *sampler,
    AnimKeyFrameTemplate   *animTmpl, DataSourceInfo &dsInfo  )
{
    if(dsInfo._dataSource == NULL)
        return;

    domInputLocalRef input = findInput(sampler, "INTERPOLATION");

    if(input == NULL)
    {
        SWARNING << "ColladaAnimation::handleInterpolation: No <input> "
                 << "with semantic INTERPOLATION in <sampler> ["
                 << (sampler->getId() != NULL ? sampler->getId() : "")
                 << "]." << std::endl;
        return;
    }

    std::string      sourceId = input->getSource().id();
    SourceMapConstIt smIt     = _sourceMap.find(sourceId);

    if(smIt == _sourceMap.end())
    {
        SWARNING << "ColladaAnimation::handleInterpolation: No <source> "
                 << "with id [" << sourceId << "] found." << std::endl;
        return;
    }

    // check if all values are the same
    bool                             singleVal = true;
    const ColladaSource::NameStore  &interpol  =
        smIt->second->getNameStore();
    ColladaSource::NameStoreConstIt  iIt  = interpol.begin() + dsInfo._firstKey;
    ColladaSource::NameStoreConstIt  iEnd = interpol.begin() + dsInfo._lastKey;

    for(; iIt != iEnd; ++iIt)
    {
        if(interpol[dsInfo._firstKey] != *iIt)
        {
            singleVal = false;
            break;
        }
    }

    iIt  = interpol.begin() + dsInfo._firstKey;
    iEnd = interpol.begin() + dsInfo._lastKey;

    for(; iIt != iEnd; ++iIt)
    {
        if(*iIt == "STEP")
        {
            dsInfo._dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Step);
        }
        else if(*iIt == "LINEAR")
        {
            dsInfo._dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Linear);
        }
        else if(*iIt == "BEZIER")
        {
            dsInfo._dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Bezier);
        }
        else if(*iIt == "HERMITE")
        {
            dsInfo._dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Hermite);
        }
        else
        {
            SWARNING << "ColladdaAnimation::handleInterpolation: "
                     << "unknown interpolation mode [" << *iIt
                     << "]. Using LINEAR instead." << std::endl;

            dsInfo._dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Linear);
        }

        // stop after one value if they are all the same
        if(singleVal == true)
            break;
    }
}

/*! Find an <input> with the given semantic in the given sampler.
 */
domInputLocal *
ColladaAnimation::findInput(domSampler *sampler, const std::string &semantic)
{
    domInputLocal             *retVal = NULL;
    const domInputLocal_Array &inputs = sampler->getInput_array();

    for(UInt32 i = 0; i < inputs.getCount(); ++i)
    {
        std::string inputSem = inputs[i]->getSemantic();

        if(semantic == inputSem)
        {
            retVal = inputs[i];
            break;
        }
    }

    return retVal;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
