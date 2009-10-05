/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2008 by the OpenSG Forum                    *
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

#include "OSGCSMVRMLNodeHelper.h"

#include "OSGCounters.h"
#include "OSGLimitedCounters.h"

#include "OSGGroup.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Generic Helper with 1:1 mapping
//---------------------------------------------------------------------------

template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<Real32Counter>::_regHelper(
        &VRMLGenericHelper<Real32Counter>::create,
        "Real32Counter",
        NULL);

OSG_INST_GENERICVRMLHELPER(Real32Counter);


template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<Int32Counter>::_regHelper(
        &VRMLGenericHelper<Int32Counter>::create,
        "Int32Counter",
        NULL);

OSG_INST_GENERICVRMLHELPER(Int32Counter);


template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<LimitedReal32Counter>::_regHelper(
        &VRMLGenericHelper<LimitedReal32Counter>::create,
        "LimitedReal32Counter",
        NULL);

OSG_INST_GENERICVRMLHELPER(LimitedReal32Counter);


template<>
VRMLNodeHelperFactoryBase::RegisterHelper 
    VRMLGenericHelper<LimitedInt32Counter>::_regHelper(
        &VRMLGenericHelper<LimitedInt32Counter>::create,
        "LimitedInt32Counter",
        NULL);

OSG_INST_GENERICVRMLHELPER(LimitedInt32Counter);

OSG_END_NAMESPACE
