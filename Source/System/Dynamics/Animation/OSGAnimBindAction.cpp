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

// for callbacks only
#include "OSGTransform.h"
#include "OSGAnimTargetAttachment.h"

OSG_BEGIN_NAMESPACE

AnimBindAction::FunctorStore *
    AnimBindAction::_defaultEnterFunctors = NULL;

AnimBindAction::FunctorStore *
    AnimBindAction::_defaultLeaveFunctors = NULL;


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


AnimBindAction::AnimBindAction(void)
    : Inherited()
{
}

AnimBindAction::~AnimBindAction(void)
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
bindTransformEnter(NodeCore *core, Action *action)
{
    Transform      *xform   = dynamic_cast<Transform      *>(core  );
    AnimBindAction *bindAct = dynamic_cast<AnimBindAction *>(action);

    Animation          *anim     = bindAct->getAnim    ();
    const AnimTemplate *animTmpl = bindAct->getTemplate();

    std::string targetId;

    if(getTargetId(xform, targetId) == false)
        return Action::Continue;

    UInt32          srcIdx = 0;
    AnimDataSource *src    = NULL;

    while((src = animTmpl->findSource(targetId, srcIdx)) != NULL)
    {
        
    }

    return Action::Continue;
}


Action::ResultE
bindSkeletonEnter(NodeCore *core, Action *action)
{
    // XXX TODO
    SFATAL << "bindSkeletonEnter: NIY" << std::endl;

    return Action::Continue;
}

OSG_END_NAMESPACE
