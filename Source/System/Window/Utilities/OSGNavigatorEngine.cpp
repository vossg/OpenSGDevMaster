/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"

#include "OSGNavigatorEngine.h"

#include "OSGNavigator.h"
#include "OSGNode.h"
#include "OSGCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NavigatorEngine
    \ingroup GrpSystemWindowNavigators

\dev 

\enddev

*/


/*------------------------- constructors ----------------------------------*/

NavigatorEngine::NavigatorEngine(void) : 
    Inherited()
{
}

/*-------------------------- destructors ----------------------------------*/

NavigatorEngine::~NavigatorEngine()
{
}

/*------------------------------ get --------------------------------------*/

NavigatorBase::State NavigatorEngine::getState(void) const
{
    return _currentState;
}

/*------------------------------ set --------------------------------------*/


/*-------------------- navigator engine callbacks -------------------------*/

void NavigatorEngine::onViewportChanged(Navigator *nav)
{
    // nothing to do here
}

void NavigatorEngine::onActivation(Navigator *nav)
{
    // nothing to do here
}

void NavigatorEngine::onUpdateCameraTransformation(Navigator *nav)
{
    // nothing to do here
}
