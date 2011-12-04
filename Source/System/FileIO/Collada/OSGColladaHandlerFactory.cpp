/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
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

#include "OSGColladaHandlerFactory.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGBaseInitFunctions.h"
#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGSingletonHolder.ins"

#include "OSGColladaExtraHandler.h"
#include "OSGColladaDomProfileHandler.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC)
OSG_SINGLETON_INST(OSG::ColladaHandlerFactoryBase, addPostFactoryExitFunction)
#endif

template class SingletonHolder<OSG::ColladaHandlerFactoryBase>;

void ColladaHandlerFactoryBase::registerExtraHandler(
    ExtraHandlerCreator fCreator)
{
    _vExtraHandlerCreators.push_back(fCreator);
}

void ColladaHandlerFactoryBase::createExtraHandlers(
    ExtraHandlerStore &vStore)
{
    vStore.clear();

    for(UInt32 i = 0; i < _vExtraHandlerCreators.size(); ++i)
        vStore.push_back(_vExtraHandlerCreators[i]());
}


void ColladaHandlerFactoryBase::registerDomProfileHandler(
    UInt32                   uiProfileId,
    DomProfileHandlerCreator fCreator   )
{
   DomProfileHandlerMapIt hIt = _mDomProfileCreators.find(uiProfileId);

    if(hIt != _mDomProfileCreators.end())
    {
        SWARNING << "ColladaBaseFactoryBase::registerDomProfileHandler: "
                 << "profileId [" << uiProfileId << "] already registered."
                 << std::endl;
    }
    else
    {
        _mDomProfileCreators.insert(
            hIt, 
            DomProfileHandlerMap::value_type(uiProfileId, 
                                             fCreator   ));
    }
}

ColladaHandlerFactoryBase::ColladaDomProfileHandlerTPtr 
    ColladaHandlerFactoryBase::createDomProfileHandler(UInt32 uiProfileId)
{
    ColladaDomProfileHandlerTPtr returnValue(NULL);

    DomProfileHandlerMapIt hIt = _mDomProfileCreators.find(uiProfileId);

    if(hIt != _mDomProfileCreators.end())
    {
        returnValue = (*hIt).second();
    }

    return returnValue;
}

ColladaHandlerFactoryBase::ColladaHandlerFactoryBase(void) :
    _mDomProfileCreators  (),
    _vExtraHandlerCreators()
{
}

ColladaHandlerFactoryBase::~ColladaHandlerFactoryBase(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
