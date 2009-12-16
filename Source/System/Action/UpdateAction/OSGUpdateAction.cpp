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

#include "OSGUpdateAction.h"

OSG_BEGIN_NAMESPACE

UpdateAction::FunctorStore *UpdateAction::_defaultEnterFunctors = NULL;
UpdateAction::FunctorStore *UpdateAction::_defaultLeaveFunctors = NULL;


UpdateAction::~UpdateAction(void)
{
    _partitionPool.freeAll();
}

UpdateAction *
UpdateAction::create(void)
{
    return new UpdateAction;
}

void
UpdateAction::registerEnterDefault(const FieldContainerType &type,
                                   const Action::Functor    &func )
{
    if(_defaultEnterFunctors == NULL)
    {
        _defaultEnterFunctors = new FunctorStore;
        
        addPostFactoryExitFunction(&UpdateAction::terminateEnter);
    }

    if(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->resize(type.getId() + 1,
                                      &UpdateAction::_defaultEnterFunction);
    }

    (*_defaultEnterFunctors)[type.getId()] = func;
}

void
UpdateAction::registerLeaveDefault(const FieldContainerType &type,
                                   const Action::Functor    &func )
{
    if(_defaultLeaveFunctors == NULL)
    {
        _defaultLeaveFunctors = new FunctorStore;
        
        addPostFactoryExitFunction(&UpdateAction::terminateLeave);
    }

    if(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->resize(type.getId() + 1,
                                      &UpdateAction::_defaultLeaveFunction);
    }

    (*_defaultLeaveFunctors)[type.getId()] = func;
}

Action::ResultE
UpdateAction::start(void)
{
    Inherited::start();

    
    _partitionStack.clear();

    _activePartition = _partitionPool.create();

    if(_viewport != NULL)
    {
        editDrawEnv().setWindow           (_window                     );
        editDrawEnv().setViewportDimension(_viewport->getPixelLeft  (),
                                           _viewport->getPixelBottom(),
                                           _viewport->getPixelRight (),
                                           _viewport->getPixelTop   (),
                                           _viewport->isFullWindow  () );

        if(_camera != NULL)
        {
            Matrix p;
            _camera->getProjection           (p,  _viewport->getPixelWidth (),
                                                  _viewport->getPixelHeight() );
            Matrix pt;
            _camera->getProjectionTranslation(pt, _viewport->getPixelWidth (),
                                                  _viewport->getPixelHeight() );
            _activePartition->setupProjection(p, pt);

            Matrix v;
            _camera->getViewing              (v,  _viewport->getPixelWidth (),
                                                  _viewport->getPixelHeight() );
            _activePartition->setupViewing(v);

            editDrawEnv().setCameraNear  (_camera->getNear        ());
            editDrawEnv().setCameraFar   (_camera->getFar         ());
            
            editDrawEnv().setTileFullSize(_camera->tileGetFullSize());
            editDrawEnv().setTileRegion  (_camera->tileGetRegion  ());
        }
        else
        {
            SWARNING << "UpdateAction::start: No camera set." << std::endl;
        }

        editDrawEnv().initVPMatricesFromCamera();
    }
    else
    {
        SWARNING << "UpdateAction::start: No viewport set." << std::endl;
    }

    return Action::Continue;
}

Action::ResultE
UpdateAction::stop(ResultE res)
{
    _activePartition = NULL;
    _partitionPool.freeAll();

    return Inherited::stop(res);
}

void
UpdateAction::pushPartition(UInt32 copyOnPush)
{
    _partitionStack.push_back(_activePartition);
    _activePartition = _partitionPool.create();

    _activePartition->setUpdateAction(this                              );
    _activePartition->initFrom       (_partitionStack.back(), copyOnPush);
}

void
UpdateAction::popPartition(void)
{
    _activePartition = _partitionStack.back();
    _partitionStack.pop_back();
}


UpdateAction::UpdateAction(void)
    : Inherited       ()

    , _camera         (NULL)
    , _viewport       (NULL)
    , _window         (NULL)
    , _activePartition(NULL)
    , _partitionStack ()
    , _partitionPool  ()
{
    if(_defaultEnterFunctors != NULL)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors != NULL)
        _leaveFunctors = *_defaultLeaveFunctors;
}

UpdateAction::UpdateAction(const UpdateAction &source)
    : Inherited(source)

    , _camera         (source._camera)
    , _viewport       (source._viewport)
    , _window         (source._window)
    , _activePartition(NULL)
    , _partitionStack ()
    , _partitionPool  ()
{
    if(_defaultEnterFunctors != NULL)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors != NULL)
        _leaveFunctors = *_defaultLeaveFunctors;
}

UpdateAction::FunctorStore *
UpdateAction::getDefaultEnterFunctors(void)
{
    return _defaultEnterFunctors;
}

UpdateAction::FunctorStore *
UpdateAction::getDefaultLeaveFunctors(void)
{
    return _defaultLeaveFunctors;
}

bool
UpdateAction::terminateEnter(void)
{
    FDEBUG(("UpdateAction::terminateEnter\n"));

    delete _defaultEnterFunctors;
    _defaultEnterFunctors = NULL;
}

bool
UpdateAction::terminateLeave(void)
{
    FDEBUG(("UpdateAction::terminateLeave\n"));

    delete _defaultLeaveFunctors;
    _defaultLeaveFunctors = NULL;
}

OSG_END_NAMESPACE
