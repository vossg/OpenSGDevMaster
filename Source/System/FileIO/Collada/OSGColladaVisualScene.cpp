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

#include "OSGColladaVisualScene.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"
#include "OSGColladaInstanceVisualScene.h"
#include "OSGColladaNode.h"
#include "OSGColladaScene.h"
#include "OSGGroup.h"
#include "OSGNameAttachment.h"

#include <dom/domVisual_scene.h>

OSG_BEGIN_NAMESPACE

ColladaInstInfoTransitPtr
ColladaVisualScene::ColladaVisualSceneInstInfo::create(
    ColladaScene *colInstParent, ColladaInstanceVisualScene *colInst)
{
    return ColladaInstInfoTransitPtr(
        new ColladaVisualSceneInstInfo(colInstParent, colInst));
}

void
ColladaVisualScene::ColladaVisualSceneInstInfo::process(void)
{
    SFATAL << "ColladaVisualSceneInstInfo::process called!" << std::endl;
}

ColladaVisualScene::ColladaVisualSceneInstInfo::ColladaVisualSceneInstInfo(
    ColladaScene *colInstParent, ColladaInstanceVisualScene *colInst)

    : Inherited(colInstParent, colInst)
{
}

ColladaVisualScene::ColladaVisualSceneInstInfo::~ColladaVisualSceneInstInfo(void)
{
}

// ===========================================================================

ColladaElementRegistrationHelper ColladaVisualScene::_regHelper(
    &ColladaVisualScene::create,
    "visual_scene"              );

// ===========================================================================

ColladaElementTransitPtr
ColladaVisualScene::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaVisualScene(elem, global));
}

void
ColladaVisualScene::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::read\n"));

    domVisual_sceneRef   visScene = getDOMElementAs<domVisual_scene>();
    const domNode_Array &nodes    = visScene->getNode_array         ();
    NodeUnrecPtr         rootN    = makeCoredNode<Group>            ();

    if(getGlobal()->getOptions()->getCreateNameAttachments() == true &&
       visScene->getName()                                   != NULL   )
    {
        setName(rootN, visScene->getName());
    }

    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(nodes[i]);

        if(colNode == NULL)
        {
            colNode = dynamic_pointer_cast<ColladaNode>(
                ColladaElementFactory::the()->create(nodes[i], getGlobal()));

            colNode->read(this);
        }
        ColladaInstInfoRefPtr  colInstInfo =
            ColladaNode::ColladaNodeInstInfo::create(this, NULL, rootN);
        Node                  *childN      =
            colNode->createInstance(colInstInfo);

        if(childN->getParent() != NULL)
        {
            SWARNING
                << "ColladaVisualScene::read: <node> [" << i
                << "] name ["
                << (getName(childN) != NULL ? getName(childN) : "")
                << "] already has a parent ["
                << (getName(childN->getParent()) != NULL ?
                    getName(childN->getParent()) : "")
                << "]." << std::endl;
        }

        // don't add joints to the scene hierarchy

        if(colNode->isJoint() == false)
            rootN->addChild(childN);
    }

    editInstStore().push_back(rootN);
}

Node *
ColladaVisualScene::createInstance(ColladaInstInfo *colInstInfo)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::createInstance\n"));

    // can only have one <instance_visual_scene> tag
    OSG_ASSERT(getInstStore().size() == 1);

    return dynamic_pointer_cast<Node>(editInstStore().front());
}

ColladaVisualScene::ColladaVisualScene(daeElement *elem, ColladaGlobal *global)
    : Inherited(elem, global)
{
}

ColladaVisualScene::~ColladaVisualScene(void)
{
}

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
