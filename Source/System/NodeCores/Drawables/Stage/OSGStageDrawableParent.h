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

#ifndef _OSGSTAGEDRAWABLEPARENT_H_
#define _OSGSTAGEDRAWABLEPARENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDrawable.h"
#include "OSGStageHandlerMixin.h"
#include "OSGStageIdPool.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpDrawablesStageObj
    \nohierarchy
 */

struct StageDrawableDesc
{
    typedef Drawable                    ParentT;
    typedef FieldContainer::TypeObject  TypeObject;
    typedef StageIdPool                 ElementIdPool;

    typedef RenderActionBase::Inherited DataSlotHandler;
};

/*! \ingroup GrpDrawablesStageObj
 */

typedef StageHandlerMixin< 
          ContainerMixinHead< 
            StageDrawableDesc > > StageDrawableParent;

OSG_END_NAMESPACE

#endif /* _OSGSTAGEDRAWABLEPARENT_H_ */
