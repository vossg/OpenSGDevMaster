/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2008 by the OpenSG Forum                     *
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

#ifndef _OSGCOLLADAINSTANCEVISUALSCENE_H_
#define _OSGCOLLADAINSTANCEVISUALSCENE_H_
#ifdef __sgi
#pragma once
#endif

/*! \file OSGColladaInstanceElement.h
    \ingroup GrpLoader
 */

#include "OSGConfig.h"

#ifdef OSG_WITH_COLLADA

#include "OSGFileIODef.h"
#include "OSGColladaInstanceElement.h"

OSG_BEGIN_NAMESPACE

class OSG_FILEIO_DLLMAPPING ColladaInstanceVisualScene
    : public ColladaInstanceElement
{
  public:
    typedef ColladaInstanceElement                  Inherited;
    typedef ColladaInstanceVisualScene              Self;
    
    typedef RefCountPtr<Self, MemObjRefCountPolicy> ObjRefPtr;
    typedef TransitPtr <Self                      > ObjTransitPtr;
    
    static inline ObjTransitPtr create(daeElement    *elem,
                                       ColladaGlobal *global);
    
    virtual void           read          (void);
            NodeTransitPtr createInstance(void);
    
  protected:
             ColladaInstanceVisualScene(daeElement    *elem,
                                        ColladaGlobal *global);
    virtual ~ColladaInstanceVisualScene(void                 );
};

typedef ColladaInstanceVisualScene::ObjRefPtr
    ColladaInstanceVisualSceneRefPtr;
typedef ColladaInstanceVisualScene::ObjTransitPtr
    ColladaInstanceVisualSceneTransitPtr;

OSG_END_NAMESPACE

#include "OSGColladaInstanceVisualScene.inl"

#endif // OSG_WITH_COLLADA

#endif // _OSGCOLLADAINSTANCEVISUALSCENE_H_
