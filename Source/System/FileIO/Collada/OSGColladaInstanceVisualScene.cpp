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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaInstanceVisualScene.h"
#include "OSGColladaLog.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaVisualScene.h"

#include <dom/domVisual_scene.h>
#include <dom/domInstanceWithExtra.h>

OSG_BEGIN_NAMESPACE

void ColladaInstanceVisualScene::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceVisualScene::read:\n"));
    
    domInstanceWithExtraRef instVisScene =
        getDOMElementAs<domInstanceWithExtra>();
    
    daeURI                   visSceneUri = instVisScene->getUrl();
    domVisual_sceneRef       visScene    =
        daeSafeCast<domVisual_scene>(visSceneUri.getElement());
    
    setInstDOMElement(visScene);
    
    ColladaVisualSceneRefPtr colVisScene =
        getUserDataAs<ColladaVisualScene>(visScene);
    
    if(colVisScene == NULL)
    {
        colVisScene = ColladaVisualScene::create(visScene, getGlobal());
        addElement(colVisScene);
        
        colVisScene->read();
    }
}

NodeTransitPtr ColladaInstanceVisualScene::createInstance(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceVisualScene::createInstance:\n"));
    
    NodeTransitPtr           retVal;
    domVisual_sceneRef       visScene    =
        getInstDOMElementAs<domVisual_scene>();
    ColladaVisualSceneRefPtr colVisScene =
        getUserDataAs<ColladaVisualScene>(visScene);
    
    if(colVisScene->_instCount == 0)
    {
        ++colVisScene->_instCount;

        retVal = colVisScene->getNode();
    }
    else
    {
        ++colVisScene->_instCount;

        retVal = cloneTree(colVisScene->getNode());
    }
    
    return retVal;
}

ColladaInstanceVisualScene::ColladaInstanceVisualScene(
    daeElement *elem, ColladaGlobal *global)
    
    : Inherited(elem, global)
{
}

ColladaInstanceVisualScene::~ColladaInstanceVisualScene(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
