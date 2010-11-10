/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2009 by the OpenSG Forum                   *
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

#include "OSGAnimBindAction.h"
#include "OSGAnimTemplate.h"
#include "OSGAnimation.h"
#include "OSGAnimDataSource.h"

// for callbacks only
#include "OSGTransform.h"
#include "OSGAnimTargetAttachment.h"

#include <boost/cast.hpp>

OSG_BEGIN_NAMESPACE

AnimBindAction::FunctorStore *
    AnimBindAction::_defaultEnterFunctors = NULL;

AnimBindAction::FunctorStore *
    AnimBindAction::_defaultLeaveFunctors = NULL;


AnimBindAction::~AnimBindAction(void)
{
}

AnimBindAction *
AnimBindAction::create(void)
{
    return new AnimBindAction;
}

void
AnimBindAction::registerEnterDefault(const FieldContainerType &type,
                                     const Action::Functor    &func )
{
    if(_defaultEnterFunctors == NULL)
    {
        _defaultEnterFunctors = new FunctorStore;

        addPostFactoryExitFunction(&AnimBindAction::terminateEnter);
    }

    if(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->resize(type.getId() + 1,
                                      &AnimBindAction::_defaultEnterFunction);
    }

    (*_defaultEnterFunctors)[type.getId()] = func;
}

void
AnimBindAction::registerLeaveDefault(const FieldContainerType &type,
                                     const Action::Functor    &func )
{
    if(_defaultLeaveFunctors == NULL)
    {
        _defaultLeaveFunctors = new FunctorStore;

        addPostFactoryExitFunction(&AnimBindAction::terminateLeave);
    }

    if(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->resize(type.getId() + 1,
                                      &AnimBindAction::_defaultLeaveFunction);
    }

    (*_defaultLeaveFunctors)[type.getId()] = func;
}

AnimTemplate *
AnimBindAction::getTemplate(void) const
{
    return _animTmpl;
}

void
AnimBindAction::setTemplate(AnimTemplate *animTmpl)
{
    _animTmpl = animTmpl;
}

Animation *
AnimBindAction::getAnim(void) const
{
    return _anim;
}

void
AnimBindAction::setAnim(Animation *anim)
{
    _anim = anim;
}

Action::ResultE
AnimBindAction::bindFields(AttachmentContainer *attCon)
{
    AnimTargetAttachment *targetAtt = getTargetAtt(attCon);

    if(targetAtt == NULL)
        return Action::Continue;

    Animation       *anim  = getAnim();
    DataSourceMapIt  dsIt  = _dsMap.begin();
    DataSourceMapIt  dsEnd = _dsMap.end  ();

    while(dsIt != dsEnd)
    {
        if(dsIt->first.find(targetAtt->getTargetId()) != 0)
        {
            ++dsIt;
            continue;
        }

        std::string targetId;
        std::string subTargetId;

        splitTargetId(dsIt->first, targetId, subTargetId);

        if(targetId != targetAtt->getTargetId())
        {
            ++dsIt;
            continue;
        }

        SINFO << "AnimBindAction::bindFields: binding source '"
              << dsIt->first << "' to '" << targetId << "' - '"
              << subTargetId << "'" << std::endl;

        FieldDescriptionBase *fDesc =
            attCon->getType().getFieldDesc(subTargetId.c_str());

        if(fDesc == NULL)
        {
            SWARNING << "AnimBindAction::bindFields: no Field for "
                     << "subTargetId [" << subTargetId << "] found."
                     << std::endl;
            ++dsIt;
            continue;
        }

        // create channel
        AnimChannelUnrecPtr channel = dsIt->second->createChannel();
        anim->editMFChannels()->push_back(channel);

         // create blender
        UInt32 fId = fDesc->getFieldId();

        if(targetAtt->getMFBlenders()->size() <= fId)
            targetAtt->editMFBlenders()->resize(fId + 1, NULL);

        AnimBlenderUnrecPtr blender = targetAtt->getBlenders(fId);

        if(blender == NULL)
        {
            blender = dsIt->second->createBlender();
            targetAtt->editMFBlenders()->replace(fId, blender);
        }

        // on create all fields are marked as changed - this causes
        // the blender to write to its destination even though
        // it has no valid input data - avoid it by committing before
        // connecting the blender to its dest
        commitChanges();

        blender->addChannel(channel                 );
        blender->connectTo (attCon, fDesc->getName());

        // remove bound data source from map
        DataSourceMapIt eraseIt = dsIt;
        ++dsIt;
        _dsMap.erase(eraseIt);
    }

    if(_dsMap.empty() == true)
    {
        return Action::Quit;
    }
    else
    {
        return Action::Continue;
    }
}


void
AnimBindAction::fillSourceMap(NodeCore      *core,
                              DataSourceMap &dsMap) const
{
    AnimTargetAttachment *targetAtt = getTargetAtt(core);

    if(targetAtt == NULL)
        return;

    DataSourceMapConstIt dsIt  = _dsMap.begin();
    DataSourceMapConstIt dsEnd = _dsMap.end  ();

    for(; dsIt != dsEnd; ++dsIt)
    {
        if(dsIt->first.find(targetAtt->getTargetId()) == 0)
        {
            SLOG << "AnimBindAction::fillSourceMap: adding ["
                 << dsIt->first << "] for [" << targetAtt->getTargetId()
                 << "]" << std::endl;

            dsMap.insert(*dsIt);
        }
    }
}

void
AnimBindAction::markUsed(const std::string &targetId)
{
    DataSourceMapIt dsIt = _dsMap.find(targetId);

    if(dsIt != _dsMap.end())
    {
        _dsMap.erase(dsIt);
    }
    else
    {
        SWARNING << "AnimBindAction::markUsed: targetId [" << targetId
                 << "] not in unused sources map." << std::endl;
    }
}

void
AnimBindAction::splitTargetId(
    const std::string &targetIdFull,
          std::string &targetId,
          std::string &subTargetId  )
{
    std::string::size_type splitPos = targetIdFull.find('.');

    if(splitPos != std::string::npos)
    {
        subTargetId = targetIdFull.substr(splitPos + 1);
        targetId    = targetIdFull.substr(0, splitPos);
    }
    else
    {
        subTargetId.clear ();
        targetId   .assign(targetIdFull);
    }
}

AnimBindAction::AnimBindAction(void)
    : Inherited(    )
    , _animTmpl(NULL)
    , _anim    (NULL)
    , _dsMap   (    )
{
}

AnimBindAction::FunctorStore *
AnimBindAction::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

AnimBindAction::FunctorStore *
AnimBindAction::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}

Action::ResultE
AnimBindAction::start(void)
{
    ResultE res = Inherited::start();

    _dsMap.clear();

    if(res != Continue)
        return res;

    UInt32 sourceCount = _animTmpl->getMFSources()->size();

    for(UInt32 i = 0; i < sourceCount; ++i)
    {
        _dsMap.insert(DataSourceMap::value_type(
                          _animTmpl->getTargetIds(i),
                          _animTmpl->getSources  (i) ));
                                                
    }

    return Action::Continue;
}

Action::ResultE
AnimBindAction::stop(ResultE res)
{
    if(_dsMap.empty() == false)
    {
        SWARNING << "AnimBindAction::stop: Unbound targets/data sources:"
                 << std::endl;

        DataSourceMapConstIt dsIt  = _dsMap.begin();
        DataSourceMapConstIt dsEnd = _dsMap.end  ();

        for(; dsIt != dsEnd; ++dsIt)
            SWARNING << "  " << dsIt->first << std::endl;
    }

    return Inherited::stop(res);
}

bool
AnimBindAction::terminateEnter(void)
{
    FDEBUG(("AnimBindAction::terminateEnter\n"));

    delete _defaultEnterFunctors;
    _defaultEnterFunctors = NULL;

    return true;
}

bool
AnimBindAction::terminateLeave(void)
{
    FDEBUG(("AnimBindAction::terminateLeave\n"));

    delete _defaultLeaveFunctors;
    _defaultLeaveFunctors = NULL;

    return true;
}

/*------------------------------- callbacks -------------------------------*/

Action::ResultE
bindEnterDefault(NodeCore *core, Action *action)
{
    AnimBindAction *bindAct =
        boost::polymorphic_downcast<AnimBindAction *>(action);

    return bindAct->bindFields(core);
}

#if 0
Action::ResultE
bindEnterDefault(NodeCore *core, Action *action)
{
    AnimBindAction     *bindAct  = dynamic_cast<AnimBindAction *>(action);
    Animation          *anim     = bindAct->getAnim    ();
    const AnimTemplate *animTmpl = bindAct->getTemplate();

    AnimTargetAttachment *targetAtt = getTargetAtt(core);

    FDEBUG(("bindEnterDefault: core [%p] targetAtt [%p]\n",
            core, targetAtt));

    if(targetAtt == NULL)
        return Action::Continue;

    Int32 srcIdx = 0;

    while((srcIdx = animTmpl->findTargetId(targetAtt->getTargetId(),
                                           srcIdx                   )) != -1)
    {
        std::string targetId;
        std::string subTargetId;

        bindAct->splitTargetId(
            animTmpl->getTargetIds(srcIdx), targetId, subTargetId);

        FDEBUG(("bindEnterDefault: targetId [%s] subTargetId [%s]\n",
                targetId.c_str(), subTargetId.c_str()));

        // create the channel

        AnimDataSource      *src     = animTmpl->getSources   (srcIdx);
        AnimChannelUnrecPtr  channel = src     ->createChannel(      );
        anim->editMFChannels()->push_back(channel);

        FieldDescriptionBase *fDesc =
            core->getType().getFieldDesc(subTargetId.c_str());

        if(fDesc == NULL)
        {
            SWARNING << "bindEnterDefault: no field for subTargetId ["
                     << subTargetId << "] found." << std::endl;
            continue;
        }

        // create the blender

        UInt32              fId     = fDesc->getFieldId();
        
        if(targetAtt->getMFBlenders()->size() <= fId)
            targetAtt->editMFBlenders()->resize(fId + 1, NULL);

        AnimBlenderUnrecPtr blender = targetAtt->getBlenders(fId);

        if(blender == NULL)
        {
            blender = src->createBlender();
            (*targetAtt->editMFBlenders())[fId] = blender;
        }

        // connect

        blender->addChannel(channel               );
        blender->connectTo (core, fDesc->getName());

        ++srcIdx;
    }

    return Action::Continue;
}
#endif

OSG_END_NAMESPACE
