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

#include "OSGColladaVisualScene.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"
#include "OSGColladaInstanceVisualScene.h"
#include "OSGColladaNode.h"
#include "OSGGroup.h"

#include <dom/domVisual_scene.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaVisualScene::_regHelper(
    &ColladaVisualScene::create,
    "visual_scene"              );


ColladaElementTransitPtr
ColladaVisualScene::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaVisualScene(elem, global));
}

void
ColladaVisualScene::read(void)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::read\n"));
}

Node *
ColladaVisualScene::process(ColladaElement *parent)
{
    SFATAL << "ColladaVisualScene::process: <visual_scene> must be "
           << "instantiated to use."
           << std::endl;

    OSG_ASSERT(false);
}

Node *
ColladaVisualScene::createInstance(ColladaInstanceElement *colInstElem)
{
    OSG_COLLADA_LOG(("ColladaVisualScene::createInstance\n"));

    ColladaInstanceVisualSceneRefPtr colInstVisScene =
        dynamic_cast<ColladaInstanceVisualScene *>(colInstElem);

    domVisual_sceneRef   visScene = getDOMElementAs<domVisual_scene>();
    const domNode_Array &nodes    = visScene->getNode_array         ();
    NodeUnrecPtr         rootN;

    for(UInt32 i = 0; i < nodes.getCount(); ++i)
    {
        ColladaNodeRefPtr colNode = getUserDataAs<ColladaNode>(nodes[i]);

        if(colNode == NULL)
        {
            colNode = dynamic_pointer_cast<ColladaNode>(
                ColladaElementFactory::the()->create(nodes[i], getGlobal()));

            colNode->read();
        }

        if(nodes.getCount() > 1)
        {
            if(rootN == NULL)
            {
                GroupUnrecPtr group = Group::create();
                rootN = makeNodeFor(group);
            }

            rootN->addChild(colNode->process(this));
        }
        else
        {
            rootN = colNode->process(this);
        }
    }

    editInstStore().push_back(rootN);

    return rootN;
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
