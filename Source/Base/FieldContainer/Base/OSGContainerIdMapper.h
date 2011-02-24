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

#ifndef _OSGCONTAINERIDMAPPER_H_
#define _OSGCONTAINERIDMAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"

OSG_BEGIN_NAMESPACE

/*! \brief Helper class for mapping field container id's from one system to 
          another.
    \ingroup GrpBaseFieldContainerHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
*/

struct OSG_BASE_DLLMAPPING ContainerIdMapper
{
    virtual ~ContainerIdMapper();

    /*! Return mapping of field container id.
      \param uiId  The id to map from.
      \return Returns the mapped id. Return 0 if no mapping is found.
    */
    virtual UInt32 map(UInt32 uiId) const = 0;
};

OSG_END_NAMESPACE

#endif /* _OSGCONTAINERIDMAPPER_H_ */
