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

#include "OSGColladaVisualScene.h"
#include "OSGColladaLog.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaNode.h"

#include <dom/domNode.h>
#include <dom/domVisual_scene.h>


OSG_BEGIN_NAMESPACE

void ColladaVisualScene::read(void)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::read:\n"));
    
    domVisual_sceneRef visScene = getDOMElementAs<domVisual_scene>();
    
    _groupNode = Node ::create();
    _group     = Group::create();
    
    _groupNode->setCore(_group);
    
    const domNode_Array &nodes = visScene->getNode_array();
    
    for(UInt32 i = 0, nodesCount = nodes.getCount(); i < nodesCount; ++i)
    {
        ColladaNodeRefPtr colNode = ColladaNode::create(nodes[i], getGlobal());
        addElement(colNode);
        
        colNode->read();
        
        _groupNode->addChild(colNode->getNode());
    }
}

ColladaVisualScene::ColladaVisualScene(
    domVisual_scene *visScene, ColladaGlobal *global)

    : Inherited(visScene, global)
{
    // nothing to do
}

ColladaVisualScene::~ColladaVisualScene(void)
{
    // nothing to do
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
