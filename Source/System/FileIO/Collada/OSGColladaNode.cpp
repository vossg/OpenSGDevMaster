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
#include "OSGColladaInstanceLight.h"
#include "OSGColladaInstanceGeometry.h"
#include "OSGColladaInstanceController.h"
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
ColladaNode::ColladaNodeInstInfo::create(
    ColladaElement *colInstParent, ColladaInstanceNode *colInst,
    Node           *parentN                                     )
{
    return ColladaInstInfoTransitPtr(
        new ColladaNodeInstInfo(colInstParent, colInst,parentN));
}

void
ColladaNode::ColladaNodeInstInfo::process(void)
{
    SFATAL << "ColladaNodeInstInfo::process called!" << std::endl;
}

ColladaNode::ColladaNodeInstInfo::ColladaNodeInstInfo(
    ColladaElement *colInstParent, ColladaInstanceNode *colInst,
    Node           *parentN                                     )

    : Inherited(colInstParent, colInst)
    , _parentN (parentN)
{
}

ColladaNode::ColladaNodeInstInfo::~ColladaNodeInstInfo(void)
{
}

// ===========================================================================

ColladaNode::NodeLoaderStateTransitPtr
ColladaNode::NodeLoaderState::create(void)
{
    return NodeLoaderStateTransitPtr(new NodeLoaderState());
}

void
ColladaNode::NodeLoaderState::pushNodePath(const std::string &nodeId)
{
    _nodePath.push_back(nodeId);
}

void
ColladaNode::NodeLoaderState::popNodePath(void)
{
    OSG_ASSERT(_nodePath.empty() == false);

    _nodePath.pop_back();
}

const ColladaNode::NodePath &
ColladaNode::NodeLoaderState::getNodePath(void) const
{
    return _nodePath;
}

void
ColladaNode::NodeLoaderState::dumpNodePath(void) const
{
    NodePathConstIt npIt  = _nodePath.begin();
    NodePathConstIt npEnd = _nodePath.end  ();

    OSG_COLLADA_LOG(("node path ["));

    for(; npIt != npEnd; ++npIt)
    {
        OSG_COLLADA_PLOG((" '%s'", npIt->c_str()));
    }

    OSG_COLLADA_PLOG((" ]\n"));
}

void
ColladaNode::NodeLoaderState::pushMatrix(const Matrix &matrix)
{
    _matrixStack.push_back(_worldMatrix);
    _worldMatrix.mult(matrix);
}

void
ColladaNode::NodeLoaderState::popMatrix(void)
{
    OSG_ASSERT(_matrixStack.empty() == false);

    _worldMatrix = _matrixStack.back();
    _matrixStack.pop_back();
}

const Matrix &
ColladaNode::NodeLoaderState::getWorldMatrix(void) const
{
    return _worldMatrix;
}

Skeleton *
ColladaNode::NodeLoaderState::getSkeleton(void) const
{
    return _skel;
}

void
ColladaNode::NodeLoaderState::setSkeleton(Skeleton *skel)
{
    _skel = skel;
}

Int16
ColladaNode::NodeLoaderState::getJointId(void) const
{
    return _jointId;
}

void
ColladaNode::NodeLoaderState::setJointId(Int16 jointId)
{
    _jointId = jointId;
}

ColladaNode::NodeLoaderState::NodeLoaderState(void)
    : Inherited   ()
    , _nodePath   ()
    , _skel       ()
    , _jointId    (SkeletonJoint::INVALID_JOINT_ID)
    , _worldMatrix()
    , _matrixStack()
{
}

ColladaNode::NodeLoaderState::~NodeLoaderState(void)
{
}

// ===========================================================================

ColladaNode::InstData::InstData(void)
    : _nodePath   ()
    , _localMatrix()
    , _skel       (NULL)
    , _topN       (NULL)
    , _bottomN    (NULL)
    , _sidMap     ()
{
}

ColladaNode::InstData::~InstData(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaNode::_regHelper(
    &ColladaNode::create, "node");

const std::string                ColladaNode::_loaderStateName("ColladaNode");

ColladaElementTransitPtr
ColladaNode::create(daeElement *elem, ColladaGlobal *global)
{
    if(global->getLoaderState(_loaderStateName) == NULL)
    {
        NodeLoaderStateRefPtr state = NodeLoaderState::create();

        global->addLoaderState(_loaderStateName, state);
    }

    return ColladaElementTransitPtr(new ColladaNode(elem, global));
}

void
ColladaNode::read(ColladaElement *colElemParent)
{
    domNodeRef node = getDOMElementAs<domNode>();

    OSG_COLLADA_LOG(("ColladaNode::read id [%s]\n", node->getId()));

    // <node>
    const domNode_Array &nodes = node->getNode_array();
    for(UInt32 i = 0; i < nodes.getCount(); ++i)
        readNode(nodes[i]);

    // <instance_node>
    const domInstance_node_Array &instNodes =
        node->getInstance_node_array();

    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
        readInstanceNode(instNodes[i]);

    // <instance_light>
    const domInstance_light_Array &instLights =
        node->getInstance_light_array();

    for(UInt32 i = 0; i < instLights.getCount(); ++i)
        readInstanceLight(instLights[i]);
    // <instance_geometry>
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
        readInstanceGeometry(instGeos[i]);

    // <instance_controller>
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
        readInstanceController(instControllers[i]);
}

Node *
ColladaNode::createInstance(ColladaInstInfo *colInstInfo)
{
    Node       *retVal = NULL;
    domNodeRef  node   = getDOMElementAs<domNode>();

#if 0 // old trunk patch
    if(_topN->getParent() != NULL)
    {
        retVal = cloneTree(_topN);
    }
#endif

    if(node->getType() == NODETYPE_JOINT)
    {
        retVal = createInstanceJoint(colInstInfo, node);
    }
    else
    {
        retVal = createInstanceNode(colInstInfo, node);
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
    OSG_ASSERT(_instDataStore.empty() == false);

    if(_instDataStore.size() > 1)
    {
        domNodeRef node = getDOMElementAs<domNode>();

        SWARNING << "ColladaNode::getSkeleton: id ["
                 << (node->getId() != NULL ? node->getId() : "")
                 << "] has multiple instances, skeleton is ambiguous."
                 << std::endl;
    }

    return _instDataStore[0]._skel;
}

Node *
ColladaNode::getTopNode(UInt32 instIdx) const
{
    OSG_ASSERT(instIdx < _instDataStore.size());

    return _instDataStore[instIdx]._topN;
}

Node *
ColladaNode::getBottomNode(UInt32 instIdx) const
{
    OSG_ASSERT(instIdx < _instDataStore.size());

    return _instDataStore[instIdx]._bottomN;
}

Node *
ColladaNode::getNodeBySid(UInt32 instIdx, const std::string &sid) const
{
    OSG_ASSERT(instIdx < _instDataStore.size());

    Node              *retVal   = NULL;
    const InstData    &instData = _instDataStore[instIdx];
    SIdNodeMapConstIt  sidIt    = instData._sidMap.find(sid);
    if(sidIt != instData._sidMap.end())
    {
        retVal = sidIt->second;
    }
    else
    {
        SWARNING << "ColladaNode::getNodeBySid: Could not find a node "
                 << "for sid [" << sid << "]." << std::endl;
    }

    return retVal;
}


ColladaNode::ColladaNode(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaNode::~ColladaNode(void)
{
}

Node *
ColladaNode::createInstanceNode(ColladaInstInfo *colInstInfo, domNode *node)
{
    OSG_COLLADA_LOG(("ColladaNode::createInstanceNode id [%s]\n",
                     node->getId()));

    NodeLoaderState *state =
        getGlobal()->getLoaderStateAs<NodeLoaderState>(_loaderStateName);
    OSG_ASSERT(state != NULL);

    state->pushNodePath(node->getId() != NULL ? node->getId() : "");
    state->dumpNodePath();

    NodeUnrecPtr retVal = NULL;
    InstData     instData;

    instData._nodePath = state->getNodePath();
    const daeElementRefArray &contents = node->getContents();

    // read "transform" child elements in the order
    // they occur in the document
    for(UInt32 i = 0; i < contents.getCount(); ++i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            handleLookAt(daeSafeCast<domLookat>(contents[i]), instData);
            break;

        case COLLADA_TYPE::MATRIX:
            handleMatrix(daeSafeCast<domMatrix>(contents[i]), instData);
            break;

        case COLLADA_TYPE::ROTATE:
            handleRotate(daeSafeCast<domRotate>(contents[i]), instData);
            break;

        case COLLADA_TYPE::SCALE:
            handleScale(daeSafeCast<domScale>(contents[i]), instData);
            break;

        case COLLADA_TYPE::SKEW:
            handleSkew(daeSafeCast<domSkew>(contents[i]), instData);
            break;

        case COLLADA_TYPE::TRANSLATE:
            handleTranslate(daeSafeCast<domTranslate>(contents[i]), instData);
            break;
        }
    }

    // assert top and bottom are both set or both unset
    OSG_ASSERT((instData._topN != NULL && instData._bottomN != NULL) ||
               (instData._topN == NULL && instData._bottomN == NULL)   );

    // if no xforms were created make a group for this <node>
    if(instData._topN == NULL && instData._bottomN == NULL)
    {
        instData._topN    = makeCoredNode<Group>();
        instData._bottomN = instData._topN;

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL   )
        {
            setName(instData._topN, node->getName());
        }
    }

    // update world matrix before we instantiate child nodes, etc.
    state->pushMatrix(instData._localMatrix);

    // add <node> child elements
    const domNode_Array &nodes = node->getNode_array();

    for(UInt32 i = 0; i < nodes.getCount(); ++i)
        handleNode(nodes[i], instData);

    // add <instance_node> child elements
    const domInstance_node_Array &instNodes =
        node->getInstance_node_array();

    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
        handleInstanceNode(instNodes[i], instData);

    // add <instance_light> child elements
    const domInstance_light_Array &instLights =
        node->getInstance_light_array();

    for(UInt32 i = 0; i < instLights.getCount(); ++i)
        handleInstanceLight(instLights[i], instData);

    // add <instance_geometry> child elements
    const domInstance_geometry_Array &instGeos =
        node->getInstance_geometry_array();

    for(UInt32 i = 0; i < instGeos.getCount(); ++i)
        handleInstanceGeometry(instGeos[i], instData);

    // add <instance_controller> child elemnts
    const domInstance_controller_Array &instControllers =
        node->getInstance_controller_array();

    for(UInt32 i = 0; i < instControllers.getCount(); ++i)
        handleInstanceController(instControllers[i], instData);

    editInstStore().push_back(instData._topN);
    _instDataStore .push_back(instData      );
    retVal = instData._topN;

    state->popMatrix  ();
    state->popNodePath();

    return retVal;
}

Node *
ColladaNode::createInstanceJoint(ColladaInstInfo *colInstInfo, domNode *node)
{
    NodeUnrecPtr retVal    = NULL;
    bool         startSkel = false;

    // if there is a ColladaInstanceElement someone tried to use <instance_node>
    // with this joint as target - this is currently not supported
    if(colInstInfo->getColInst() != NULL)
    {
        SWARNING << "ColladaNode::createInstanceJoint: <instance_node> with "
                 << "target <node> of type JOINT not supported." << std::endl;
        return retVal;
    }

    NodeLoaderState *state =
        getGlobal()->getLoaderStateAs<NodeLoaderState>(_loaderStateName);
    OSG_ASSERT(state != NULL);

    state->pushNodePath(node->getId() != NULL ? node->getId() : "");
    state->dumpNodePath();

    InstData instData;
    instData._nodePath = state->getNodePath();
    instData._skel     = state->getSkeleton();

    if(instData._skel == NULL)
    {
        startSkel      = true;
        instData._skel = Skeleton::create();

        state->setSkeleton(instData._skel);
        state->setJointId (0             );

        OSG_COLLADA_LOG(("ColladaNode::createInstanceJoint: id [%s] "
                         "root joint\n", node->getId()));
    }
    else
    {
        state->setJointId(state->getJointId() + 1);

        OSG_COLLADA_LOG(("ColladaNode::createInstanceJoint: id [%s] "
                         "joint [%d]\n", node->getId(), state->getJointId()));
    }

    const daeElementRefArray &contents = node->getContents();

    for(UInt32 i = 0; i < contents.getCount(); ++i)
    {
        switch(contents[i]->getElementType())
        {
        case COLLADA_TYPE::LOOKAT:
            handleLookAt(daeSafeCast<domLookat>(contents[i]), instData);
            break;

        case COLLADA_TYPE::MATRIX:
            handleMatrix(daeSafeCast<domMatrix>(contents[i]), instData);
            break;

        case COLLADA_TYPE::ROTATE:
            handleRotate(daeSafeCast<domRotate>(contents[i]), instData);
            break;

        case COLLADA_TYPE::SCALE:
            handleScale(daeSafeCast<domScale>(contents[i]), instData);
            break;

        case COLLADA_TYPE::SKEW:
            handleSkew(daeSafeCast<domSkew>(contents[i]), instData);
            break;

        case COLLADA_TYPE::TRANSLATE:
            handleTranslate(daeSafeCast<domTranslate>(contents[i]), instData);
            break;
        }
    }

    // assert top and bottom are both set or both unset
    OSG_ASSERT((instData._topN != NULL && instData._bottomN != NULL) ||
               (instData._topN == NULL && instData._bottomN == NULL)   );

    if(instData._topN == NULL && instData._bottomN == NULL)
    {
        // no xforms were created, make a SkeletonJoint for this <node>

        SkeletonJointUnrecPtr joint = SkeletonJoint::create();

        joint->setJointId(state->getJointId());

        instData._topN    = makeNodeFor(joint);
        instData._bottomN = instData._topN;

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL   )
        {
            setName(instData._topN, node->getName());
        }
    }
    else if(getGlobal()->getOptions()->getMergeTransforms() == false)
    {
        // when not merging transforms add SkeletonJoint core now

        SkeletonJointUnrecPtr joint  = SkeletonJoint::create();
        NodeUnrecPtr          jointN = makeNodeFor(joint);

        joint->setJointId(state->getJointId());

        instData._bottomN->addChild(jointN);
        instData._bottomN = jointN;
    }

    if(startSkel == true)
    {
        // add a transform for the world matrix up to this node to put
        // the Skeleton in the correct coordinate system

        TransformUnrecPtr xform  = Transform::create();
        NodeUnrecPtr      xformN = makeNodeFor(xform);

        xform->setMatrix(state->getWorldMatrix());

        xformN->addChild(instData._topN);
        instData._topN = xformN;

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true)
            setName(xformN, "SkeletonWorldMatrix");
    }

    // update world matrix before we instantiate child nodes, etc.
    state->pushMatrix(instData._localMatrix);

    // add <node> child elements
    const domNode_Array &nodes = node->getNode_array();

    for(UInt32 i = 0; i < nodes.getCount(); ++i)
        handleNode(nodes[i], instData);

    // add <instance_node> child elements
    const domInstance_node_Array &instNodes =
        node->getInstance_node_array();

    for(UInt32 i = 0; i < instNodes.getCount(); ++i)
        handleInstanceNode(instNodes[i], instData);

    // we don't handle other <instance_*> tags here, it does not
    // make sense to have them inside a skeleton

    editInstStore().push_back(instData._topN);
    _instDataStore .push_back(instData      );
    retVal = instData._topN;

    if(startSkel == true)
    {
        instData._skel->pushToRoots(instData._topN);

        state->setSkeleton(NULL);
        state->setJointId (SkeletonJoint::INVALID_JOINT_ID);
    }

    state->popMatrix  ();
    state->popNodePath();

    return retVal;
}

void
ColladaNode::handleLookAt(domLookat *lookat, InstData &instData)
{
    if(lookat == NULL)
        return;

    SWARNING << "ColladaNode::handleLookAt: NIY" << std::endl;
}

void
ColladaNode::handleMatrix(domMatrix *matrix, InstData &instData)
{
    if(matrix == NULL)
        return;

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

    std::string xformSID;

    if(matrix->getSid() != NULL)
        xformSID.assign(matrix->getSid());

    appendXForm(m, xformSID, instData);
}

void
ColladaNode::handleRotate(domRotate *rotate, InstData &instData)
{
    if(rotate == NULL)
        return;

    Matrix     m;
    Quaternion q;
    q.setValueAsAxisDeg(rotate->getValue()[0],
                        rotate->getValue()[1],
                        rotate->getValue()[2],
                        rotate->getValue()[3] );

    m.setRotate(q);

    std::string xformSID;

    if(rotate->getSid() != NULL)
        xformSID.assign(rotate->getSid());

    appendXForm(m, xformSID, instData);
}

void
ColladaNode::handleScale(domScale *scale, InstData &instData)
{
    if(scale == NULL)
        return;

    Matrix m;
    m.setScale(scale->getValue()[0],
               scale->getValue()[1],
               scale->getValue()[2] );

    std::string xformSID;

    if(scale->getSid() != NULL)
        xformSID.assign(scale->getSid());

    appendXForm(m, xformSID, instData);
}

void
ColladaNode::handleSkew(domSkew *skew, InstData &instData)
{
    if(skew == NULL)
        return;

    SWARNING << "ColladaNode::handleSkew: NIY" << std::endl;
}

void
ColladaNode::handleTranslate(domTranslate *translate, InstData &instData)
{
    if(translate == NULL)
        return;

    Matrix m;
    m.setTranslate(translate->getValue()[0],
                   translate->getValue()[1],
                   translate->getValue()[2] );

    std::string nameSuffix;

    if(translate->getSid() != NULL)
    {
        nameSuffix.append("."                );
        nameSuffix.append(translate->getSid());
    }

    appendXForm(m, nameSuffix, instData);  
}

void
ColladaNode::appendXForm(const Matrix      &m,
                         const std::string &xformSID,
                         InstData          &instData   )
{
    domNodeRef       node  = getDOMElementAs<domNode>();
    NodeLoaderState *state =
        getGlobal()->getLoaderStateAs<NodeLoaderState>(_loaderStateName);
    OSG_ASSERT(state != NULL);

    if(getGlobal()->getOptions()->getMergeTransforms() == true)
    {
        if(instData._bottomN == NULL)
        {
            if(node->getType() == NODETYPE_JOINT)
            {
                SkeletonJointUnrecPtr joint = SkeletonJoint::create();
                instData._bottomN           = makeNodeFor(joint);

                joint->setMatrix(m);
                joint->setJointId(state->getJointId());
            }
            else
            {
                TransformUnrecPtr xform = Transform::create();
                instData._bottomN       = makeNodeFor(xform);

                xform->setMatrix(m);
            }

            instData._localMatrix = m;
        }
        else
        {
            if(node->getType() == NODETYPE_JOINT)
            {
                SkeletonJoint *joint =
                    dynamic_cast<SkeletonJoint *>(instData._bottomN->getCore());
                OSG_ASSERT(joint != NULL);

                joint->editMatrix().mult(m);
            }
            else
            {
                Transform *xform =
                    dynamic_cast<Transform *>(instData._bottomN->getCore());
                OSG_ASSERT(xform != NULL);

                xform->editMatrix().mult(m);
            }

            instData._localMatrix.mult(m);
        }

        if(instData._topN == NULL)
            instData._topN = instData._bottomN;

        if(xformSID.empty() == false)
            instData._sidMap[xformSID] = instData._bottomN;

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL &&
           getName(instData._bottomN)                            == NULL   )
        {
            std::string nodeName = node->getName();

            setName(instData._bottomN, nodeName);
        }
    }
    else
    {
        TransformUnrecPtr xform  = Transform::create();
        NodeUnrecPtr      xformN = makeNodeFor(xform);

        if(instData._bottomN != NULL)
            instData._bottomN->addChild(xformN);

        xform->setMatrix(m);
        instData._localMatrix.mult(m);

        instData._bottomN = xformN;

        if(instData._topN == NULL)
            instData._topN = instData._bottomN;

        if(xformSID.empty() == false)
            instData._sidMap[xformSID] = xformN;

        if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
           node->getName()                                       != NULL   )
        {
            std::string nodeName = node->getName();

            if(xformSID.empty() == false)
            {
                nodeName.append("."     );
                nodeName.append(xformSID);
            }

            setName(instData._bottomN, nodeName);
        }
    }
}

void
ColladaNode::appendChild(domNode  *child,
                         Node     *childN,
                         InstData &instData)
{
    domNodeRef node = getDOMElementAs<domNode>();

    // only add the child if it is not the first joint
    // in a hierarchy

    if(child->getType() != NODETYPE_JOINT ||
       node ->getType() != NODETYPE_NODE    )
    {
        OSG_ASSERT(instData._topN    != NULL);
        OSG_ASSERT(instData._bottomN != NULL);

        instData._bottomN->addChild(childN);
    }
}

void
ColladaNode::readNode(domNode *child)
{
    ColladaNodeRefPtr colNodeChild = getUserDataAs<ColladaNode>(child);

    if(colNodeChild == NULL)
    {
        colNodeChild = dynamic_pointer_cast<ColladaNode>(
            ColladaElementFactory::the()->create(child, getGlobal()));

        colNodeChild->read(this);
    }
}

void
ColladaNode::handleNode(domNode  *child,
                        InstData &instData)
{
    ColladaNodeRefPtr     colNodeChild = getUserDataAs<ColladaNode>(child);
    ColladaInstInfoRefPtr colInstInfo  =
        ColladaNodeInstInfo::create(this, NULL, instData._bottomN);

    Node *childN = colNodeChild->createInstance(colInstInfo);

    appendChild(child, childN, instData);
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
ColladaNode::handleInstanceNode(domInstance_node *instNode,
                                InstData         &instData)
{
    ColladaInstanceNodeRefPtr colInstNode =
        getUserDataAs<ColladaInstanceNode>(instNode);
    ColladaInstInfoRefPtr     colInstInfo =
        ColladaNodeInstInfo::create(this, colInstNode, instData._bottomN);

    Node *childN = colInstNode->getTargetElem()->createInstance(colInstInfo);

    appendChild(colInstNode->getTargetDOMElem(), childN, instData);
}

void
ColladaNode::readInstanceLight(domInstance_light *instLight)
{
    if(getGlobal()->getOptions()->getLoadLights() == false)
        return;

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    if(colInstLight == NULL)
    {
        colInstLight = dynamic_pointer_cast<ColladaInstanceLight>(
            ColladaElementFactory::the()->create(instLight, getGlobal()));

        colInstLight->read(this);
    }
}

void
ColladaNode::handleInstanceLight(domInstance_light *instLight,
                                 InstData          &instData  )
{
    if(getGlobal()->getOptions()->getLoadLights() == false)
        return;

    ColladaInstanceLightRefPtr colInstLight =
        getUserDataAs<ColladaInstanceLight>(instLight);

    ColladaInstInfoRefPtr lightInstInfo =
        ColladaLight::ColladaLightInstInfo::create(
            this, colInstLight, instData._bottomN);

    getGlobal()->editInstQueue().push_back(lightInstInfo);
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
ColladaNode::handleInstanceGeometry(domInstance_geometry *instGeo,
                                    InstData             &instData)
{
    ColladaInstanceGeometryRefPtr colInstGeo =
        getUserDataAs<ColladaInstanceGeometry>(instGeo);

    ColladaInstInfoRefPtr geoInstInfo =
        ColladaGeometry::ColladaGeometryInstInfo::create(
            this, colInstGeo, instData._bottomN);

    getGlobal()->editInstQueue().push_back(geoInstInfo);
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
ColladaNode::handleInstanceController(
    domInstance_controller *instCtrl,
    InstData               &instData )
{
    ColladaInstanceControllerRefPtr colInstCtrl =
        getUserDataAs<ColladaInstanceController>(instCtrl);

    ColladaInstInfoRefPtr ctrlInstInfo =
        ColladaController::ColladaControllerInstInfo::create(
            this, colInstCtrl, instData._bottomN);

    getGlobal()->editInstQueue().push_back(ctrlInstInfo);
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
