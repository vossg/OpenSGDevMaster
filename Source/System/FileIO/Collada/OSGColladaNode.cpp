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

#include "OSGColladaNode.h"
#include "OSGColladaLog.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaInstanceNode.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceLight.h"
#include "OSGNameAttachment.h"

#include <dom/domLookat.h>
#include <dom/domMatrix.h>
#include <dom/domRotate.h>
#include <dom/domScale.h>
#include <dom/domSkew.h>
#include <dom/domTranslate.h>
#include <dom/domInstance_node.h>
#include <dom/domInstance_geometry.h>
#include <dom/domInstance_light.h>
#include <dom/domNode.h>


OSG_BEGIN_NAMESPACE

void ColladaNode::read(void)
{
    OSG_COLLADA_LOG(("ColladaNode::read:\n"));
    
    domNodeRef node = getDOMElementAs<domNode>();
    
    OSG_COLLADA_LOG(("ColladaNode::read: [%s]\n",
                     (node->getName() ? node->getName() : "")));
    
    _transNode = Node::create();
    
    if(node->getName() != NULL)
        setName(_transNode, node->getName());
    
    const daeElementRefArray &contents = node->getContents();
    for(UInt32 i = 0, contentCount = contents.getCount();
        i < contentCount; ++i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            handleLookAt(daeSafeCast<domLookat>(contents[i]));
        break;
        
        case COLLADA_TYPE::MATRIX:
            handleMatrix(daeSafeCast<domMatrix>(contents[i]));
        break;
        
        case COLLADA_TYPE::ROTATE:
            handleRotate(daeSafeCast<domRotate>(contents[i]));
        break;
        
        case COLLADA_TYPE::SCALE:
            handleScale(daeSafeCast<domScale>(contents[i]));
        break;
        
        case COLLADA_TYPE::SKEW:
            handleSkew(daeSafeCast<domSkew>(contents[i]));
        break;
        
        case COLLADA_TYPE::TRANSLATE:
            handleTranslate(daeSafeCast<domTranslate>(contents[i]));
        break;
        }
    }
    
    const domInstance_node_Array &instNodes = node->getInstance_node_array();
    for(UInt32 i = 0, instNodeCount = instNodes.getCount();
        i < instNodeCount; ++i)
    {
        handleInstanceNode(instNodes[i]);
    }
    
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();
    for(UInt32 i = 0, instGeoCount = instGeos.getCount();
        i < instGeoCount; ++i)
    {
        handleInstanceGeometry(instGeos[i]);
    }

    const domInstance_light_Array &instLights =
        node->getInstance_light_array();
    for(UInt32 i = 0, instLightCount = instLights.getCount();
        i < instLightCount; ++i)
    {
        handleInstanceLight(instLights[i]);
    }
        
    const domNode_Array &nodes = node->getNode_array();
    for(UInt32 i = 0, nodeCount = nodes.getCount(); i < nodeCount; ++i)
    {
        handleNode(nodes[i]);
    }
    
    if(_transNode->getCore() == NULL)
        _transNode->setCore(Group::create());
}


ColladaNode::ColladaNode(domNode *node, ColladaGlobal *global)
    : Inherited (node, global),
      _transNode(            ),
      _trans    (            )
{
}

ColladaNode::~ColladaNode(void)
{
}


void ColladaNode::handleLookAt(domLookat *lookat)
{
    OSG_COLLADA_LOG(("ColladaNode::handleLookAt:\n"));
    
    if(lookat == NULL)
        return;
    
    FWARNING(("ColladaNode::handleLookAt: NIY\n"));
}

void ColladaNode::handleMatrix(domMatrix *matrix)
{
    OSG_COLLADA_LOG(("ColladaNode::handleMatrix:\n"));
    
    if(matrix == NULL)
        return;
    
    if(_transNode->getCore() == NULL)
    {
        _trans = Transform::create();
        _transNode->setCore(_trans);
    }
    
    Matrix m(matrix->getValue()[0],      // rVal00
             matrix->getValue()[1],      // rVal10
             matrix->getValue()[2],      // rVal20
             matrix->getValue()[3],      // rVal30
             matrix->getValue()[4],      // rVal01
             matrix->getValue()[5],      // rVal11
             matrix->getValue()[6],      // rVal21
             matrix->getValue()[7],      // rVal31
             matrix->getValue()[8],      // rVal02
             matrix->getValue()[9],      // rVal12
             matrix->getValue()[10],     // rVal22
             matrix->getValue()[11],     // rVal32
             matrix->getValue()[12],     // rVal03
             matrix->getValue()[13],     // rVal13
             matrix->getValue()[14],     // rVal23
             matrix->getValue()[15] );   // rVal33
    
    _trans->editMatrix().mult(m);
}

void ColladaNode::handleRotate(domRotate *rotate)
{
    OSG_COLLADA_LOG(("ColladaNode::handleRotate:\n"));
    
    if(rotate == NULL)
        return;
    
    if(_transNode->getCore() == NULL)
    {
        _trans = Transform::create();
        _transNode->setCore(_trans);
    }
    
    Quaternion q;
    q.setValueAsAxisDeg(rotate->getValue()[0],
                        rotate->getValue()[1],
                        rotate->getValue()[2],
                        rotate->getValue()[3] );
    
    Matrix m;
    m.setRotate(q);
    
    _trans->editMatrix().mult(m);
}

void ColladaNode::handleScale(domScale *scale)
{
    OSG_COLLADA_LOG(("ColladaNode::handleScale:\n"));
    
    if(scale == NULL)
        return;
    
    if(_transNode->getCore() == NULL)
    {
        _trans = Transform::create();
        _transNode->setCore(_trans);
    }
    
    Matrix m;
    m.setScale(scale->getValue()[0],
               scale->getValue()[1],
               scale->getValue()[2] );
    
    _trans->editMatrix().mult(m);
}

void ColladaNode::handleSkew(domSkew *skew)
{
    OSG_COLLADA_LOG(("ColladaNode::handleSkew:\n"));
    
    if(skew == NULL)
        return;
    
    FWARNING(("ColladaNode::handleSkew: NIY\n"));
}

void ColladaNode::handleTranslate(domTranslate *translate)
{
    OSG_COLLADA_LOG(("ColladaNode::handleTranslate:\n"));
    
    if(translate == NULL)
       return;
    
    if(_transNode->getCore() == NULL)
    {
        _trans = Transform::create();
        _transNode->setCore(_trans);
    }
    
    Matrix m;
    m.setTranslate(translate->getValue()[0],
                   translate->getValue()[1],
                   translate->getValue()[2] );
    
    _trans->editMatrix().mult(m);
}

void ColladaNode::handleInstanceNode(domInstance_node *instNode)
{
    OSG_COLLADA_LOG(("ColladaNode::handleInstanceNode:\n"));
    
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);

    if(colInstNode == NULL)
    {
        colInstNode = ColladaInstanceNode::create(instNode, getGlobal());
        addElement(colInstNode);
    
        colInstNode->read();
    }
    
    _transNode->addChild(colInstNode->createInstance());
}

void ColladaNode::handleInstanceGeometry(domInstance_geometry *instGeo)
{
    OSG_COLLADA_LOG(("ColladaNode::handleInstanceGeometry:\n"));

    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    if(colInstGeo == NULL)
    {
        colInstGeo = ColladaInstanceGeometry::create(instGeo, getGlobal());
        addElement(colInstGeo);
    
        colInstGeo->read();
    }
    
    _transNode->addChild(colInstGeo->createInstance());
}

void ColladaNode::handleInstanceLight(domInstance_light *instLight)
{
    OSG_COLLADA_LOG(("ColladaNode::handleInstanceLight:\n"));

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    if(colInstLight == NULL)
    {
        colInstLight = ColladaInstanceLight::create(instLight, getGlobal());
        addElement(colInstLight);

        colInstLight->read();
    }

    LightUnrecPtr light  = colInstLight->createInstance();

    if(light != NULL)
        light->setBeacon(_transNode);
}

void ColladaNode::handleNode(domNode *node)
{
    OSG_COLLADA_LOG(("ColladaNode::handleNode:\n"));
    
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);

    if(colNode == NULL)
    {
        colNode = ColladaNode::create(node, getGlobal());
        addElement(colNode);
    
        colNode->read();
    }
    
    _transNode->addChild(colNode->getNode());
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
