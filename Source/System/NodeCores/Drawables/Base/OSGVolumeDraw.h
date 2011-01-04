/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGVOLUMEDRAW_H_
#define _OSGVOLUMEDRAW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"
#include "OSGBaseTypes.h"
#include "OSGNode.h"

#include "OSGAction.h"

#include "OSGVolume.h"
#include "OSGBoxVolume.h"

OSG_BEGIN_NAMESPACE

class RenderActionBase;
class RenderPartition;

/*---------------------------------------------------------------------*/
/*! \name                   Draw Functions                             */
/*! \{                                                                 */

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void drawVolume(const Volume           &volume);

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void drawVolume(const BoxVolume        &volume);

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void drawVolume(const SphereVolume     &volume);

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void drawVolume(const FrustumVolume    &volume);

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void drawVolume(const CylinderVolume   &volume);

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void dropVolume(      RenderActionBase *action, 
                                            Node             *node,
                                            Color3f           col   );
/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void dropVolume(      RenderPartition  *part, 
                                            Node             *node,
                                            Color3f           col   );

/*! \ingroup GrpSystemNodeCoreDrawablesFuncs
 */
OSG_SYSTEM_DLLMAPPING void dropVolume(      RenderActionBase *action, 
                                      const BoxVolume        &volume,
                                            Color3f           col   );

/*! \}                                                                 */
/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

#endif /* _OSGVOLUMEDRAW_H_ */
