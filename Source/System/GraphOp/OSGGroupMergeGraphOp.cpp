/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2008 by the OpenSG Forum                  *
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

#include "OSGGroupMergeGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGGroup.h"
#include "OSGMaterialGroup.h"
#include "OSGDistanceLOD.h"
#include "OSGScreenLOD.h"
#include "OSGSwitch.h"
#include "OSGMultiCore.h"
#include "OSGMultiSwitch.h"
#include "OSGVisitSubTree.h"
#include "OSGTransform.h"

#include "OSGNameAttachment.h"

/*! \class OSG::TransformPushGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    Finds pairs of Groups that are parent/child to each other and moves all
    children of the child Group to the parent Group.
    
    If a Group is encountered the number of children it has are examined.
    - If the Group has a single child, the Group is replaced by that child.
    - If the Group has zero or more than one children, those that are Groups
      themselves have their children moved to the Group and are removed (by
      moving their children they became leafs).
*/

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = GroupMergeGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace


const char *GroupMergeGraphOp::getClassname(void)
{
    return "GroupMergeGraphOp";
}

GroupMergeGraphOp::GroupMergeGraphOp(const char* name) : 
     Inherited        (name ),
    _ignoreAttachments(false)
{
    // nothing to do
}

GroupMergeGraphOpTransitPtr GroupMergeGraphOp::create(void)
{
    return GroupMergeGraphOpTransitPtr(new GroupMergeGraphOp);
}

GraphOpTransitPtr GroupMergeGraphOp::clone(void)
{
    return GraphOpTransitPtr(new GroupMergeGraphOp);
}

void GroupMergeGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);

    ps("ignoreattachments", _ignoreAttachments);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("GroupMergeGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string GroupMergeGraphOp::usage(void)
{
    return "GroupMerge: Combine adjacent Groups into one.\n";
}


GroupMergeGraphOp::~GroupMergeGraphOp(void)
{
    // nothing to do
}

Action::ResultE GroupMergeGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;
    
    return Action::Continue;
}

Action::ResultE GroupMergeGraphOp::traverseLeave(
        Node * const node, Action::ResultE res)
{
    if(isInExcludeList(node) || isInPreserveList(node))
        return Action::Continue;
    
    NodeCore *core = node->getCore();
    
    // skip cores with a dependency on the children number/order
    // TODO: find a way to make this extendable
    if(core == NULL                                               ||
       core->getType().isDerivedFrom(DistanceLOD::getClassType()) ||
       core->getType().isDerivedFrom(ScreenLOD  ::getClassType()) ||
       core->getType().isDerivedFrom(Switch     ::getClassType()) ||
       core->getType().isDerivedFrom(MultiSwitch::getClassType()) ||
       core->getType().isDerivedFrom(MultiCore  ::getClassType())   )
    {
        return Action::Continue;
    }
    
    if(node->getMFChildren()->size() == 0)
    {
        handleNoChildren(node, core);
    }
    else
    {
        if(node->getMFChildren()->size() == 1)
        {
            handleSingleChild(node, core);
        }
        else
        {
            handleMultipleChildren(node, core);
        }
    }
    
    return Action::Continue;
}

/*! If \a node has no children, its core is derived from Group and not a
    VisitSubTree or Transformation core, it can be removed.
 */
void GroupMergeGraphOp::handleNoChildren(
    Node * const node, NodeCore * const core)
{
    if( core->getType().isDerivedFrom(Group       ::getClassType()) &&
       !core->getType().isDerivedFrom(VisitSubTree::getClassType()) &&
       !core->getType().isDerivedFrom(Transform   ::getClassType()))
    {
        Node *parent = node->getParent();
        
        if(parent != NULL)
        {
            mergeAttachments(parent, node);
            parent->subChild(node);
        }
    }
}

/*! If \a node has only a single child that can replace \a node, if node is
    a Group.
 */
void GroupMergeGraphOp::handleSingleChild(
    Node * const node, NodeCore * const core)
{
    Node *parent = node->getParent( );
    Node *child  = node->getChild (0);
    
    if(core != NULL && core->getType() == Group::getClassType())
    {
        if(parent != NULL && child != NULL)
        {
            if(!isInExcludeList(child) && !isInPreserveList(child))
            {
                mergeAttachments(parent, node);

                parent->replaceChildBy(node, child);
            }
        }
    }
    else
    {
        // try the general case
        handleMultipleChildren(node, core);
    }
}

/*! Replaces all Group children of \a node with their respective children.
 */
void GroupMergeGraphOp::handleMultipleChildren(
    Node * const node, NodeCore * const core)
{
    Node::MFChildrenType::const_iterator childIt  =
        node->getMFChildren()->begin();
    Node::MFChildrenType::const_iterator childEnd =
        node->getMFChildren()->end  ();
    
    typedef std::vector<NodeUnrecPtr> NodeStore;
    NodeStore addStore;
    NodeStore subStore;
    
    for(; childIt != childEnd; ++childIt)
    {
        // ignore children that are excluded or need to be preserved
        if(isInExcludeList(*childIt) || isInPreserveList(*childIt))
            continue;
        
        // ignore children that have a core type different from Group
        if(((*childIt)->getCore()            == NULL                 ) ||
           ((*childIt)->getCore()->getType() != Group::getClassType())   )
            continue;
        
        // mark child for removal from children list
        subStore.push_back(*childIt);
        
        // mark its children for addition to current node
        Node::MFChildrenType::const_iterator grandChildIt  =
            (*childIt)->getMFChildren()->begin();
        Node::MFChildrenType::const_iterator grandChildEnd =
            (*childIt)->getMFChildren()->end  ();
        
        for(; grandChildIt != grandChildEnd; ++grandChildIt)
            addStore.push_back(*grandChildIt);
    }
    
    // perform subtractions/additions
    NodeStore::const_iterator storeIt  = subStore.begin();
    NodeStore::const_iterator storeEnd = subStore.end  ();
    
    for(; storeIt != storeEnd; ++storeIt)
    {
        mergeAttachments(node, *storeIt);
        node->subChild(*storeIt);
    }

    storeIt  = addStore.begin();
    storeEnd = addStore.end  ();
    
    for(; storeIt != storeEnd; ++storeIt)
        node->addChild(*storeIt);

    subStore.clear();
    addStore.clear();
}

void GroupMergeGraphOp::mergeAttachments(Node * const toNode, 
                                         Node * const fromNode)
{
    if(_ignoreAttachments == true)
        return;

    const SFAttachmentPtrMap *pAttMap    = fromNode->getSFAttachments();

    AttachmentMap::const_iterator mapIt  = pAttMap->getValue().begin();
    AttachmentMap::const_iterator mapEnd = pAttMap->getValue().end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        AttachmentUnrecPtr att       = mapIt->second;
        UInt16             uiBinding = UInt16(mapIt->first &
                                              0x0000FFFF    );

        if(att != NULL)
        {
            Attachment *pDstAtt = toNode->findAttachment(att->getGroupId(),
                                                         uiBinding        );

            if(att->getType().isDerivedFrom(Name::getClassType()) == false &&
               pDstAtt                                            == NULL   )
            {
                toNode->addAttachment(att, uiBinding);
            }
        }
    }
}

OSG_END_NAMESPACE
