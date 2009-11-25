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

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaSource.h"

#include "OSGAnimKeyFrameTemplate.h"

#include <dom/domAnimation.h>

OSG_BEGIN_NAMESPACE

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

    OSG_COLLADA_LOG(("ColladaAnimation::read id [%s]\n",
                     (anim->getId() != NULL ? anim->getId() : "") ));

    readAnim(anim);

    const domAnimation_Array &subAnims = anim->getAnimation_array();

    for(UInt32 i = 0; i < subAnims.getCount(); ++i)
    {
        readAnim(subAnims[i]);
    }
}

FieldContainer *
ColladaAnimation::createInstance(
    ColladaElement *colInstParent, ColladaInstanceElement *colInst)
{
    domAnimationRef anim = getDOMElementAs<domAnimation>();

    OSG_COLLADA_LOG(("ColladaAnimation::createInstance id [%s]\n",
                     (anim->getId() != NULL ? anim->getId() : "") ));

    SWARNING << "ColladaAnimation::createInstance: NIY" << std::endl;

    AnimKeyFrameTemplateUnrecPtr animTmpl = AnimKeyFrameTemplate::create();


    createInstanceAnim(anim, colInstParent, colInst, animTmpl);
    
    const domAnimation_Array &subAnims = anim->getAnimation_array();

    for(UInt32 i = 0; i < subAnims.getCount(); ++i)
    {
        createInstanceAnim(subAnims[i], colInstParent, colInst, animTmpl);
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
    const domChannel_Array &channels = anim->getChannel_array();

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

        AnimKeyFrameDataSourceUnrecPtr dataSource = NULL;

        dataSource = handleOutput(channels[i], sampler, animTmpl);

        handleInput        (channels[i], sampler, animTmpl, dataSource);
        handleInterpolation(channels[i], sampler, animTmpl, dataSource);
    }
}

AnimKeyFrameDataSourceTransitPtr
ColladaAnimation::handleOutput(
    domChannel *channel, domSampler *sampler, AnimKeyFrameTemplate *animTmpl)
{
    domInputLocalRef input = findInput(sampler, "OUTPUT");

    if(input == NULL)
    {
        SWARNING << "ColladaAnimation::handleOutput: No <input> "
                 << "with semantic OUTPUT in <sampler> ["
                 << (sampler->getId() != NULL ? sampler->getId() : "")
                 << "]." << std::endl;
        return AnimKeyFrameDataSourceTransitPtr();
    }

    std::string      sourceId = input->getSource().id();
    SourceMapConstIt smIt     = _sourceMap.find(sourceId);

    if(smIt == _sourceMap.end())
    {
        SWARNING << "ColladaAnimation::handleOutput: No <source> "
                 << "with id [" << sourceId << "] found." << std::endl;
        return AnimKeyFrameDataSourceTransitPtr();
    }

    std::string target   (channel->getTarget()             );
    daeSidRef   targetRef(target, getGlobal()->getDocRoot());
    daeSidRef::resolveData targetResolve = targetRef.resolve();
    daeElement *targetElem = targetResolve.elt;

    if(targetElem == NULL)
    {
        SWARNING << "ColladaAnimation::handleOutput: Could not resolve ["
                 << target << "]. Ignoring." << std::endl;
        return AnimKeyFrameDataSourceTransitPtr();
    }

    OSG_COLLADA_LOG(("ColladaAnimation::handleOutput: target [%s] type [%d] "
                     "parent type [%d] - array ptr [%p] scalar ptr [%p] value [%s]\n",
                     target.c_str(), targetElem->getElementType(),
                     targetElem->getParentElement()->getElementType(),
                     targetResolve.array, targetResolve.scalar,
                     targetElem->getCharData().c_str() ));

    switch(targetElem->getElementType())
    {
    case COLLADA_TYPE::MATRIX:
    {
        OSG_COLLADA_LOG(("ColladaAnimation::handleOutput: target [%s] target MATRIX\n"));
    }
    break;

    case COLLADA_TYPE::TRANSLATE:
    {
        OSG_COLLADA_LOG(("ColladaAnimation::handleOutput: target [%s] target TRANSLATE\n"));
    }
    break;

    case COLLADA_TYPE::ROTATE:
    {
        OSG_COLLADA_LOG(("ColladaAnimation::handleOutput: target [%s] target ROTATE\n"));
    }
    break;
   
    default:
    {
        SWARNING << "ColladaAnimation::handleOutput: Target [" << target
                 << "] has unhandled type [" << targetElem->getElementType()
                 << "]. Ignoring." << std::endl;
    }
    };



//     std::string::size_type posSlash = target.find('/');
//     std::string::size_type posDot   = target.find('.');
    
//     std::string targetId  = target.substr(0,            posSlash);
//     std::string targetSid = target.substr(posSlash + 1, posDot  );
    
    
    
    // XXX TODO

    return AnimKeyFrameDataSourceTransitPtr();
}

void
ColladaAnimation::handleInterpolation(
    domChannel             *channel,  domSampler             *sampler,
    AnimKeyFrameTemplate   *animTmpl, AnimKeyFrameDataSource *dataSource)
{
    domInputLocalRef input = findInput(sampler, "INTERPOLATION");

    // XXX TODO
    if(dataSource == NULL)
        return;

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
    ColladaSource::NameStoreConstIt  iIt       = interpol.begin();
    ColladaSource::NameStoreConstIt  iEnd      = interpol.end();

    for(; iIt != iEnd; ++iIt)
    {
        if(interpol[0] != *iIt)
        {
            singleVal = false;
            break;
        }
    }

    iIt  = interpol.begin();
    iEnd = interpol.end  ();

    for(; iIt != iEnd; ++iIt)
    {
        if(*iIt == "STEP")
        {
            dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Step);
        }
        else if(*iIt == "LINEAR")
        {
            dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Linear);
        }
        else if(*iIt == "BEZIER")
        {
            dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Bezier);
        }
        else if(*iIt == "HERMITE")
        {
            dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Hermite);
        }
        else
        {
            SWARNING << "ColladdaAnimation::handleInterpolation: "
                     << "unknown interpolation mode [" << *iIt
                     << "]. Using LINEAR instead." << std::endl;

            dataSource->editMFInterpolationModes()->push_back(
                AnimKeyFrameDataSource::IM_Linear);
        }

        // stop after one value if they are all the same
        if(singleVal == true)
            break;
    }
}

void
ColladaAnimation::handleInput(
    domChannel             *channel,  domSampler             *sampler,
    AnimKeyFrameTemplate   *animTmpl, AnimKeyFrameDataSource *dataSource)
{
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
