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
#pragma GCC diagnostic warning "-Wold-style-cast"
#endif

#include <OSGColladaInstanceNode.h>
#include <OSGColladaLog.h>

#ifdef OSG_WITH_COLLADA

#include <OSGColladaNode.h>

#include <1.4/dom/domNode.h>
#include <1.4/dom/domInstance_node.h>

OSG_BEGIN_NAMESPACE

void ColladaInstanceNode::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceNode::read:\n"));
    
    domInstance_nodeRef      instNode = getDOMElementAs<domInstance_node>();
    
    daeURI                   nodeUri  = instNode->getUrl();
    domNodeRef               node     =
        daeSafeCast<domNode>(nodeUri.getElement());
    
    setInstDOMElement(node);
    
    ColladaNodeRefPtr        colNode  = getUserDataAs<ColladaNode>(node);
    
    if(colNode == NULL)
    {
        colNode = ColladaNode::create(node, getGlobal());
        addElement(colNode);
        
        colNode->read();
    }
}

NodeTransitPtr ColladaInstanceNode::createInstance(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceNode::createInstance:\n"));
    
    NodeTransitPtr    retVal;
    domNodeRef        node    = getInstDOMElementAs<domNode>();
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);
    
    if(_instCount == 0)
    {
        ++_instCount;

        retVal = colNode->getNode();
    }
    else
    {
        ++_instCount;

        retVal = cloneTree(colNode->getNode());
    }
    
    return retVal;
}

ColladaInstanceNode::ColladaInstanceNode(
    daeElement *elem, ColladaGlobal *global)

    : Inherited(elem, global)
{
}

ColladaInstanceNode::~ColladaInstanceNode(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
