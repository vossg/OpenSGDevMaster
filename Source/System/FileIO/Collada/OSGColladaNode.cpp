/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2009 by the OpenSG Forum                     *
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

#include "OSGColladaNode.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaInstanceNode.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGTransform.h"
#include "OSGNameAttachment.h"

#include <dom/domLookat.h>
#include <dom/domMatrix.h>
#include <dom/domRotate.h>
#include <dom/domScale.h>
#include <dom/domSkew.h>
#include <dom/domTranslate.h>
#include <dom/domInstance_node.h>
#include <dom/domNode.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaNode::_regHelper(
    &ColladaNode::create, "node");


ColladaElementTransitPtr
ColladaNode::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaNode(elem, global));
}

void
ColladaNode::read(void)
{
    OSG_COLLADA_LOG(("ColladaNode::read\n"));

    domNodeRef                node     = getDOMElementAs<domNode>();
    const daeElementRefArray &contents = node->getContents();

    // handle "transform" child elements in the order
    // they occur in the document

    for(UInt32 i = 0; i < contents.getCount(); ++i)
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

    // handle <node> child elements
    const domNode_Array &nodes = node->getNode_array();
    
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        handleNode(nodes[i]);
    }

    // handle <instance_node> child elements
    const domInstance_node_Array &instNodes = node->getInstance_node_array();
    
    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
    {
        handleInstanceNode(instNodes[i]);
    }

    // handle <instance_geometry> child elements
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
    {
        handleInstanceGeometry(instGeos[i]);
    }

    // handle <instance_controller> child elemnts
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
    {
        handleInstanceController(instControllers[i]);
    }
}

Node *
ColladaNode::process(ColladaElement *parent)
{
    OSG_COLLADA_LOG(("ColladaNode::process: parent [%s]\n",
                    parent->getDOMElement()->getElementName()));

    NodeUnrecPtr retVal = NULL;

    if(getInstStore().empty() == true)
    {
        retVal = _topN;
    }
    else
    {
        retVal = cloneTree(_topN);
    }

    editInstStore().push_back(retVal);

    return retVal;
}

Node *
ColladaNode::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaNode::createInstance\n"));

    NodeUnrecPtr retVal = NULL;

    if(getInstStore().empty() == true)
    {
        retVal = _topN;
    }
    else
    {
        retVal = cloneTree(_topN);
    }

    editInstStore().push_back(retVal);

    return retVal;
}

ColladaNode::ColladaNode(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaNode::~ColladaNode(void)
{
}

void
ColladaNode::handleLookAt(domLookat *lookat)
{
    if(lookat == NULL)
        return;

    SWARNING << "ColladaNode::handleLookAt: NIY" << std::endl;
}

void
ColladaNode::handleMatrix(domMatrix *matrix)
{
    if(matrix == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

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
    
    xform->setMatrix(m);

    if(node->getName() != NULL)
    {
        std::string nodeName = node->getName();

        if(matrix->getSid() != NULL)
        {
            nodeName.append("."             );
            nodeName.append(matrix->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleRotate(domRotate *rotate)
{
    if(rotate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    Quaternion q;
    q.setValueAsAxisDeg(rotate->getValue()[0],
                        rotate->getValue()[1],
                        rotate->getValue()[2],
                        rotate->getValue()[3] );
    
    xform->editMatrix().setRotate(q);

    if(node->getName() != NULL)
    {
        std::string nodeName = node->getName();

        if(rotate->getSid() != NULL)
        {
            nodeName.append("."             );
            nodeName.append(rotate->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleScale(domScale *scale)
{
    if(scale == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setScale(scale->getValue()[0],
                                 scale->getValue()[1],
                                 scale->getValue()[2] );

    if(node->getName() != NULL)
    {
        std::string nodeName = node->getName();

        if(scale->getSid() != NULL)
        {
            nodeName.append("."            );
            nodeName.append(scale->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleSkew(domSkew *skew)
{
    if(skew == NULL)
        return;

    SWARNING << "ColladaNode::handleSkew: NIY" << std::endl;
}

void
ColladaNode::handleTranslate(domTranslate *translate)
{
    if(translate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setTranslate(translate->getValue()[0],
                                     translate->getValue()[1],
                                     translate->getValue()[2] );


    if(node->getName() != NULL)
    {
        std::string nodeName = node->getName();

        if(translate->getSid() != NULL)
        {
            nodeName.append("."                );
            nodeName.append(translate->getSid());
        }

        setName(xformN, nodeName);
    }

    appendXForm(xformN);
}

void
ColladaNode::handleNode(domNode *node)
{
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);

    if(colNode == NULL)
    {
        colNode = dynamic_pointer_cast<ColladaNode>(
            ColladaElementFactory::the()->create(node, getGlobal()));

        colNode->read();
    }

    NodeUnrecPtr childN = colNode->process(this);

    appendChild(childN);
}

void
ColladaNode::handleInstanceNode(domInstance_node *instNode)
{
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);

    if(colInstNode == NULL)
    {
        colInstNode = dynamic_pointer_cast<ColladaInstanceNode>(
            ColladaElementFactory::the()->create(instNode, getGlobal()));

        colInstNode->read();
    }

    NodeUnrecPtr childN = colInstNode->process(this);

    appendChild(childN);
}

void
ColladaNode::handleInstanceGeometry(domInstance_geometry *instGeo)
{
    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    if(colInstGeo == NULL)
    {
        colInstGeo = dynamic_pointer_cast<ColladaInstanceGeometry>(
            ColladaElementFactory::the()->create(instGeo, getGlobal()));

        colInstGeo->read();
    }

    NodeUnrecPtr geoN = colInstGeo->process(this);

    appendChild(geoN);
}

void
ColladaNode::handleInstanceController(domInstance_controller *instController)
{
    SWARNING << "ColladaNode::handleInstanceController: NIY"
             << std::endl;
}

/*! Add a transform node to the OpenSG tree representing
    this <node>.
 */
void
ColladaNode::appendXForm(Node *xformN)
{
    if(_topN == NULL)
    {
        _topN = xformN;
    }

    if(_bottomN != NULL)
    {
        _bottomN->addChild(xformN);
    }

    _bottomN = xformN;
}

/*! Add a child node to the OpenSG tree representing
    this <node>.
 */
void
ColladaNode::appendChild(Node *childN)
{
    if(_bottomN == NULL)
    {
        _bottomN = makeCoredNode<Group>();

        domNodeRef node = getDOMElementAs<domNode>();

        if(node->getName() != NULL)
        {
            setName(_bottomN, node->getName());
        }
    }

    if(_topN == NULL)
    {
        _topN = _bottomN;
    }

    _bottomN->addChild(childN);
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
