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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGColladaNode.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaGlobal.h"
#include "OSGColladaInstanceNode.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceController.h"
#include "OSGColladaVisualScene.h"
#include "OSGTransform.h"
#include "OSGSkeletonJoint.h"
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

// ===========================================================================

ColladaInstInfoTransitPtr
ColladaNode::ColladaGeometryInstInfo::create(
    ColladaNode *colInstParent, ColladaInstanceGeometry *colInst,
    Node        *attachN                                         )
{
    return ColladaInstInfoTransitPtr(
        new ColladaGeometryInstInfo(colInstParent, colInst, attachN));
}

void
ColladaNode::ColladaGeometryInstInfo::process(void)
{
    ColladaNode *colNode = dynamic_cast<ColladaNode *>(getColInstParent());

    colNode->handleInstanceGeometry(this);
}

ColladaNode::ColladaGeometryInstInfo::ColladaGeometryInstInfo(
    ColladaNode *colInstParent, ColladaInstanceGeometry *colInst, 
    Node        *attachN                                         )

    : Inherited(colInstParent, colInst, attachN)
{
}

ColladaNode::ColladaGeometryInstInfo::~ColladaGeometryInstInfo(void)
{
}

// ===========================================================================

ColladaInstInfoTransitPtr
ColladaNode::ColladaControllerInstInfo::create(
    ColladaNode *colInstParent, ColladaInstanceController *colInst,
    Node        *attachN                                           )
{
    return ColladaInstInfoTransitPtr(
        new ColladaControllerInstInfo(colInstParent, colInst, attachN));
}

void
ColladaNode::ColladaControllerInstInfo::process(void)
{
    ColladaNode *colNode = dynamic_cast<ColladaNode *>(getColInstParent());

    colNode->handleInstanceController(this);
}

ColladaNode::ColladaControllerInstInfo::ColladaControllerInstInfo(
    ColladaNode *colInstParent, ColladaInstanceController *colInst, 
    Node        *attachN                                           )

    : Inherited(colInstParent, colInst, attachN)
{
}

ColladaNode::ColladaControllerInstInfo::~ColladaControllerInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaNode::_regHelper(
    &ColladaNode::create, "node");
Int16                            ColladaNode::_jointId(
    SkeletonJoint::INVALID_JOINT_ID);


ColladaElementTransitPtr
ColladaNode::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaNode(elem, global));
}

void
ColladaNode::read(ColladaElement *colElemParent)
{
    domNodeRef                node     = getDOMElementAs<domNode>();
    const daeElementRefArray &contents = node->getContents();

    OSG_COLLADA_LOG(("ColladaNode::read id [%s]\n",
                     (node->getId() != NULL ? node->getId() : "")));

    // read "transform" child elements in the order
    // they occur in the document
    for(UInt32 i = 0; i < contents.getCount(); ++i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            readLookAt(daeSafeCast<domLookat>(contents[i]));
            break;
            
        case COLLADA_TYPE::MATRIX:
            readMatrix(daeSafeCast<domMatrix>(contents[i]));
        break;
        
        case COLLADA_TYPE::ROTATE:
            readRotate(daeSafeCast<domRotate>(contents[i]));
        break;
        
        case COLLADA_TYPE::SCALE:
            readScale(daeSafeCast<domScale>(contents[i]));
        break;
        
        case COLLADA_TYPE::SKEW:
            readSkew(daeSafeCast<domSkew>(contents[i]));
        break;
        
        case COLLADA_TYPE::TRANSLATE:
            readTranslate(daeSafeCast<domTranslate>(contents[i]));
        break;
        }
    }

    // read <node> child elements
    const domNode_Array &nodes = node->getNode_array();
    
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        readNode(nodes[i]);
    }

    // read <instance_node> child elements
    const domInstance_node_Array &instNodes = node->getInstance_node_array();
    
    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
    {
        readInstanceNode(instNodes[i]);
    }

    // read <instance_geometry> child elements
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
    {
        readInstanceGeometry(instGeos[i]);
    }

    // read <instance_controller> child elemnts
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
    {
        readInstanceController(instControllers[i]);
    }
}

Node *
ColladaNode::createInstance(
    ColladaElement *colInstParent, ColladaInstanceElement *colInst)
{
    NodeUnrecPtr retVal = NULL;
    domNodeRef   node   = getDOMElementAs<domNode>();

#if 0 // old trunk patch
    if(_topN->getParent() != NULL)
    {
        retVal = cloneTree(_topN);
    }
#endif

    if(node->getType() == NODETYPE_JOINT)
    {
        retVal = createInstanceJoint(colInstParent, colInst, node);
    }
    else
    {
        retVal = createInstanceNode(colInstParent, colInst, node);
    }

    return retVal;
}

bool
ColladaNode::isJoint(void) const
{
    domNodeRef node = getDOMElementAs<domNode>();

    return (node->getType() == NODETYPE_JOINT);
}

Skeleton *
ColladaNode::getSkeleton(void) const
{
    return _skel;
}

Node *
ColladaNode::getTopNode(UInt32 instIdx) const
{
    OSG_ASSERT(instIdx < getInstStore().size());

    return dynamic_pointer_cast<Node>(getInstStore()[instIdx]);
}

Node *
ColladaNode::getBottomNode(UInt32 instIdx) const
{
    OSG_ASSERT(instIdx < _bottomInstStore.size());

    return dynamic_pointer_cast<Node>(_bottomInstStore[instIdx]);
}

ColladaNode::ColladaNode(daeElement *elem, ColladaGlobal *global)
    : Inherited       (elem, global)
    , _bottomInstStore()
    , _xformTopN      (NULL)
    , _xformBottomN   (NULL)
    , _skel           (NULL)
{
}

ColladaNode::~ColladaNode(void)
{
}

void
ColladaNode::readLookAt(domLookat *lookat)
{
    if(lookat == NULL)
        return;

    SWARNING << "ColladaNode::readLookAt: NIY" << std::endl;
}

void
ColladaNode::readMatrix(domMatrix *matrix)
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

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
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
ColladaNode::readRotate(domRotate *rotate)
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

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
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
ColladaNode::readScale(domScale *scale)
{
    if(scale == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setScale(scale->getValue()[0],
                                 scale->getValue()[1],
                                 scale->getValue()[2] );

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
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
ColladaNode::readSkew(domSkew *skew)
{
    if(skew == NULL)
        return;

    SWARNING << "ColladaNode::readSkew: NIY" << std::endl;
}

void
ColladaNode::readTranslate(domTranslate *translate)
{
    if(translate == NULL)
        return;

    domNodeRef        node   = getDOMElementAs<domNode>();

    TransformUnrecPtr xform  = Transform::create();
    NodeUnrecPtr      xformN = makeNodeFor(xform);

    xform->editMatrix().setTranslate(translate->getValue()[0],
                                     translate->getValue()[1],
                                     translate->getValue()[2] );

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true && 
       node->getName()                                       != NULL   )
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
ColladaNode::readNode(domNode *node)
{
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);

    if(colNode == NULL)
    {
        colNode = dynamic_pointer_cast<ColladaNode>(
            ColladaElementFactory::the()->create(node, getGlobal()));

        colNode->read(this);
    }    
}

void
ColladaNode::addNode(domNode *node, Node *attachN)
{
    ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(node);
    OSG_ASSERT(colNode != NULL);

    Node *childN = colNode->createInstance(this, NULL);

    if(childN != NULL)
        attachN->addChild(childN);
}

void
ColladaNode::readInstanceNode(domInstance_node *instNode)
{
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);

    if(colInstNode == NULL)
    {
        colInstNode = dynamic_pointer_cast<ColladaInstanceNode>(
            ColladaElementFactory::the()->create(instNode, getGlobal()));

        colInstNode->read(this);
    }
}

void
ColladaNode::addInstanceNode(domInstance_node *instNode,  Node *attachN)
{
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);
    OSG_ASSERT(colInstNode                  != NULL);
    OSG_ASSERT(colInstNode->getTargetElem() != NULL);

    Node *childN =
        colInstNode->getTargetElem()->createInstance(this, colInstNode);

    if(childN != NULL)
        attachN->addChild(childN);
}

void
ColladaNode::readInstanceGeometry(domInstance_geometry *instGeo)
{
    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    if(colInstGeo == NULL)
    {
        colInstGeo = dynamic_pointer_cast<ColladaInstanceGeometry>(
            ColladaElementFactory::the()->create(instGeo, getGlobal()));

        colInstGeo->read(this);
    }
}

void
ColladaNode::addInstanceGeometry(domInstance_geometry *instGeo, Node *attachN)
{
    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    ColladaInstInfoRefPtr geoInstInfo =
        ColladaGeometryInstInfo::create(this, colInstGeo, attachN);

    getGlobal()->editInstQueue().push_back(geoInstInfo);
}

void
ColladaNode::handleInstanceGeometry(ColladaInstInfo *instInfo)
{
    ColladaGeometryInstInfo *geoInstInfo =
        dynamic_cast<ColladaGeometryInstInfo *>(instInfo);

    OSG_ASSERT(geoInstInfo                                != NULL);
    OSG_ASSERT(geoInstInfo->getColInst()                  != NULL);
    OSG_ASSERT(geoInstInfo->getColInst()->getTargetElem() != NULL);

    Node *geoN = dynamic_cast<Node *>(
        geoInstInfo->getColInst()->getTargetElem()->createInstance(
            geoInstInfo->getColInstParent(), geoInstInfo->getColInst()));

    geoInstInfo->getAttachNode()->addChild(geoN);
}

void
ColladaNode::readInstanceController(domInstance_controller *instCtrl)
{
    ColladaInstanceControllerRefPtr colInstCtrl =
        getUserDataAs<ColladaInstanceController>(instCtrl);

    if(colInstCtrl == NULL)
    {
        colInstCtrl = dynamic_pointer_cast<ColladaInstanceController>(
            ColladaElementFactory::the()->create(instCtrl, getGlobal()));

        colInstCtrl->read(this);
    }
}

void
ColladaNode::addInstanceController(
    domInstance_controller *instCtrl, Node *attachN)
{
    ColladaInstanceControllerRefPtr colInstCtrl =
        getUserDataAs<ColladaInstanceController>(instCtrl);

    ColladaInstInfoRefPtr ctrlInstInfo =
        ColladaControllerInstInfo::create(this, colInstCtrl, attachN);

    getGlobal()->editInstQueue().push_back(ctrlInstInfo);
}

void
ColladaNode::handleInstanceController(ColladaInstInfo *instInfo)
{
    ColladaControllerInstInfo *ctrlInstInfo =
        dynamic_cast<ColladaControllerInstInfo *>(instInfo);

    OSG_ASSERT(ctrlInstInfo                                != NULL);
    OSG_ASSERT(ctrlInstInfo->getColInst()                  != NULL);
    OSG_ASSERT(ctrlInstInfo->getColInst()->getTargetElem() != NULL);

    Node *ctrlN = dynamic_cast<Node *>(
        ctrlInstInfo->getColInst()->getTargetElem()->createInstance(
            ctrlInstInfo->getColInstParent(), ctrlInstInfo->getColInst()));

    ctrlInstInfo->getAttachNode()->addChild(ctrlN);
}

/*! Add a transform node to the OpenSG tree representing
    this &lt;node&gt;.
 */
void
ColladaNode::appendXForm(Node *nodeN)
{
    if(_xformBottomN != NULL)
        _xformBottomN->addChild(nodeN);

    _xformBottomN = nodeN;

    if(_xformTopN == NULL)
        _xformTopN = _xformBottomN;
}

void
ColladaNode::cloneXForms(NodeUnrecPtr &topN, NodeUnrecPtr &bottomN)
{
    if(_xformTopN != NULL)
    {
        topN = cloneTree(_xformTopN);
    }
    else
    {
        topN = makeCoredNode<Group>();
    }

    bottomN = topN;

    while(bottomN->getNChildren() > 0)
        bottomN = bottomN->getChild(0);
}

Node *
ColladaNode::createInstanceNode(
    ColladaElement *colInstParent, ColladaInstanceElement *colInst,
    domNode        *node                                           )
{
    OSG_COLLADA_LOG(("ColladaNode::createInstanceNode id [%s]\n",
                     (node->getId() != NULL ? node->getId() : "")));

    NodeUnrecPtr retVal       = NULL;
    NodeUnrecPtr instTopN;
    NodeUnrecPtr instBottomN;

    cloneXForms(instTopN, instBottomN);

    // add <node> child elements
    const domNode_Array &nodes = node->getNode_array();
    
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        addNode(nodes[i], instBottomN);
    }

    // add <instance_node> child elements
    const domInstance_node_Array &instNodes =
        node->getInstance_node_array();
    
    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
    {
        addInstanceNode(instNodes[i], instBottomN);
    }

    // add <instance_geometry> child elements
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
    {
        addInstanceGeometry(instGeos[i], instBottomN);
    }

    // add <instance_controller> child elemnts
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
    {
        addInstanceController(instControllers[i], instBottomN);
    }

    editInstStore() .push_back(instTopN   );
    _bottomInstStore.push_back(instBottomN);
    retVal = instTopN;

    return retVal;
}

Node *
ColladaNode::createInstanceJoint(
    ColladaElement *colInstParent, ColladaInstanceElement *colInst,
    domNode        *node                                           )                          
{
    NodeUnrecPtr retVal    = NULL;
    bool         startSkel = false;

    if(colInst != NULL)
    {
        SWARNING << "ColladaNode::createInstanceJoint: <instance_node> with "
                 << "target <node> of type JOINT not supported." << std::endl;
        return retVal;
    }

    ColladaNode        *colNodeParent =
        dynamic_cast<ColladaNode *       >(colInstParent);
    ColladaVisualScene *colVSParent   =
        dynamic_cast<ColladaVisualScene *>(colInstParent);

    if(colNodeParent != NULL && colNodeParent->isJoint() == false)
    {
        domNode *nodeParent = colNodeParent->getDOMElementAs<domNode>();

        OSG_COLLADA_LOG(("ColladaNode::createInstanceJoint: id [%s] root joint of "
                         "[%s]\n",
                         (node->getId()       != NULL ?
                          node->getId()               : ""),
                         (nodeParent->getId() != NULL ? 
                          nodeParent->getId()         : "") ));

        startSkel = true;
        _skel     = Skeleton::create();
        _jointId  = 0;
    }
    else if(colNodeParent != NULL && colNodeParent->isJoint() == true)
    {
        domNode *nodeParent = colNodeParent->getDOMElementAs<domNode>();

        OSG_COLLADA_LOG(("ColladaNode::createInstanceJoint: id [%s] child joint of "
                         "[%s]\n",
                         (node->getId()       != NULL ?
                          node->getId()               : ""),
                         (nodeParent->getId() != NULL ? 
                          nodeParent->getId()         : "") ));

        _skel = colNodeParent->getSkeleton();
    }
    else if(colVSParent != NULL)
    {
        OSG_COLLADA_LOG(("ColladaNode::createInstanceJoint: id [%s] "
                         "top-level joint\n",
                         (node->getId()       != NULL ?
                          node->getId()               : "") ));

        startSkel = true;
        _skel     = Skeleton::create();
        _jointId  = 0;
    }

    NodeUnrecPtr instTopN;
    NodeUnrecPtr instBottomN;

    cloneXForms(instTopN, instBottomN);

    SkeletonJointUnrecPtr joint  = SkeletonJoint::create();
    NodeUnrecPtr          jointN = makeNodeFor(joint);
    joint->setJointId(_jointId++);

    instBottomN->addChild(jointN);
    instBottomN = jointN;

    // add <node> child elements
    const domNode_Array &nodes = node->getNode_array();
    
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        addNode(nodes[i], instBottomN);
    }

    // add <instance_node> child elements
    const domInstance_node_Array &instNodes =
        node->getInstance_node_array();
    
    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
    {
        addInstanceNode(instNodes[i], instBottomN);
    }

    if(startSkel == true)
        _skel->editMFRoots()->push_back(instTopN);

    editInstStore() .push_back(instTopN   );
    _bottomInstStore.push_back(instBottomN);
    retVal = instTopN;

    return retVal;
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
