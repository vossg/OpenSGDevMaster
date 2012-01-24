/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGASPECT_H_
#define _OSGASPECT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGContainerForwards.h"
#include "OSGThread.h"

OSG_BEGIN_NAMESPACE

namespace Aspect
{
#ifdef OSG_MT_CPTR_ASPECT
    /*! \ingroup GrpBaseFieldContainerFuncs
        \relatesalso OSG::FieldContainer
     */
    template<class ContainerPtr> inline
    ContainerPtr    convertToCurrent      (ContainerPtr     pFC);

    /*! \ingroup GrpBaseFieldContainerFuncs
        \relatesalso OSG::FieldContainer
     */
    template<class ContainerPtr> inline
    ContainerPtr    initializeFrom         (ContainerPtr    pFC);

    /*! \ingroup GrpBaseFieldContainerFuncs
        \relatesalso OSG::FieldContainer
     */
    OSG_BASE_DLLMAPPING
    FieldContainer *initializeContainerFrom(FieldContainer *src);
#endif
}

OSG_END_NAMESPACE

#include "OSGAspect.inl"

#endif /* _OSGASPECT_H_ */
