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

#include "OSGColladaInstanceController.h"

#ifdef OSG_WITH_COLLADA

#include "OSGColladaLog.h"

#include <dom/domInstance_controller.h>
#include <dom/domNode.h>
#include <dom/domInstance_node.h>
#include <dae/daeSIDResolver.h>

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceController::_regHelper(
    &ColladaInstanceController::create, "instance_controller");


ColladaElementTransitPtr
ColladaInstanceController::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(
        new ColladaInstanceController(elem, global));
}

void
ColladaInstanceController::read(ColladaElement *colElemParent)
{
    OSG_COLLADA_LOG(("ColladaInstanceController::read\n"));

    ColladaControllerRefPtr colCtrl = getTargetElem();

    if(colCtrl == NULL)
    {
        colCtrl = dynamic_pointer_cast<ColladaController>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colCtrl->read(this);
    }

    domInstance_controllerRef instCtrl =
        getDOMElementAs<domInstance_controller>();
    domBind_materialRef       bindMat  = instCtrl->getBind_material();

    if(bindMat != NULL)
    {
        Inherited::readBindMaterial(bindMat);
    }
    else
    {

        SWARNING << "ColladaInstanceController::read: "
                 << "No <bind_material> found." << std::endl;
    }

    readSkeleton();
}

const ColladaInstanceController::SkeletonRootStore &
ColladaInstanceController::getSkeletonRoots(void)
{
    return _skelRoots;
}

domNode *
ColladaInstanceController::findJointNode(const std::string &jointSid)
{
    domNode                  *retVal = NULL;
    SkeletonRootStoreConstIt  sIt    = _skelRoots.begin();
    SkeletonRootStoreConstIt  sEnd   = _skelRoots.end  ();

    for(UInt32 i = 0; sIt != sEnd; ++sIt, ++i)
    {
        daeSidRef jointRef(jointSid, *sIt);

        retVal = daeSafeCast<domNode>(jointRef.resolve().elt);

        if(retVal != NULL)
        {
            OSG_COLLADA_LOG(("ColladaInstanceController::findJointNode: "
                             "Found joint [%s] relative to root [%d][%s]\n",
                             jointSid.c_str(), i,
                             ((*sIt)->getId() != NULL ? (*sIt)->getId() : "")));

            break;
        }
        else
        {
            OSG_COLLADA_LOG(("ColladaInstanceController::findJointNode: "
                             "joint [%s] not found below root [%d][%s]\n",
                             jointSid.c_str(), i,
                             ((*sIt)->getId() != NULL ? (*sIt)->getId() : "")));
        }
    }

    return retVal;
}

ColladaController *
ColladaInstanceController::getTargetElem(void) const
{
    ColladaController *retVal     = NULL;
    daeElementRef      targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaController>(targetElem);
    }

    return retVal;
}

daeElement *
ColladaInstanceController::getTargetDOMElem(void) const
{
    domControllerRef          retVal   = NULL;
    domInstance_controllerRef instCtrl =
        getDOMElementAs<domInstance_controller>();

    if(instCtrl->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domController>(instCtrl->getUrl().getElement());
    }

    return retVal;
}

ColladaInstanceController::ColladaInstanceController(
    daeElement *elem, ColladaGlobal *global)

    : Inherited (elem, global)
    , _skelRoots()
{
}

ColladaInstanceController::~ColladaInstanceController(void)
{
}

void
ColladaInstanceController::readSkeleton(void)
{
    domInstance_controllerRef                        instCtrl =
        getDOMElementAs<domInstance_controller>();
    const domInstance_controller::domSkeleton_Array &skels    =
        instCtrl->getSkeleton_array();

    for(UInt32 i = 0; i < skels.getCount(); ++i)
    {
        OSG_COLLADA_LOG(("ColladaInstanceController::readSkeleton: "
                         "Skeleton root node: [%s]\n",
                         skels[i]->getValue().getURI()));

        daeURI   skelURI  = skels[i]->getValue();
        domNode *skelNode = daeSafeCast<domNode>(skelURI.getElement());

        if(skelNode == NULL)
        {
            SWARNING << "ColladaInstanceController::readSkeleton: "
                     << "<skeleton> tag does not refer to a <node>, URI ["
                     << skelURI.str() << "]. Ignored." << std::endl;
            continue;
        }

        _skelRoots.push_back(skelNode);
    }
}

#if 0  // obsolete, using daeSidRef instead
domNode *
ColladaInstanceController::findJointNode(
    const std::string &jointSid, domNode *currNode)
{
    if(currNode == NULL)
        return NULL;

    domNode     *retVal  = NULL;
    std::string  currSid = currNode->getSid();

    if(jointSid == currSid)
    {
        retVal = currNode;
    }
    else
    {
        const daeElementRefArray &contents = currNode->getContents();

        for(UInt32 i = 0; i < contents.getCount(); ++i)
        {
            if(contents[i]->typeID() == domNode::ID())
            {
                retVal = findJointNode(
                    jointSid, daeSafeCast<domNode>(contents[i]));
                                         
            }
            else if(contents[i]->typeID() == domInstance_node::ID())
            {
                retVal = findJointNode(
                    jointSid, daeSafeCast<domInstance_node>(contents[i]));
            }

            if(retVal != NULL)
                break;
        }
    }

    return retVal;
}

domNode *
ColladaInstanceController::findJointNode(
    const std::string &jointSid, domInstance_node *currNode)
{
    if(currNode == NULL)
        return NULL;
   
    domNode *targetNode =
        daeSafeCast<domNode>(currNode->getUrl().getElement());

    return findJointNode(jointSid, targetNode);
}
#endif // obsolete, using daeSidRef instead

OSG_END_NAMESPACE

#endif // OSG_WITH_COLLADA
