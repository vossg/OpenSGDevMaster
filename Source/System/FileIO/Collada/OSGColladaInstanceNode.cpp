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

#include "OSGColladaInstanceNode.h"

#if defined(OSG_WITH_COLLADA) || defined(OSG_DO_DOC)

#include "OSGColladaLog.h"

OSG_BEGIN_NAMESPACE

ColladaElementRegistrationHelper ColladaInstanceNode::_regHelper(
    &ColladaInstanceNode::create,
    "instance_node"              );


ColladaElementTransitPtr
ColladaInstanceNode::create(daeElement *elem, ColladaGlobal *global)
{
    return ColladaElementTransitPtr(new ColladaInstanceNode(elem, global));
}

void
ColladaInstanceNode::read(void)
{
    OSG_COLLADA_LOG(("ColladaInstanceNode::read\n"));

    ColladaNodeRefPtr colNode = getTargetElem();

    if(colNode == NULL)
    {
        colNode = dynamic_pointer_cast<ColladaNode>(
            ColladaElementFactory::the()->create(
                getTargetDOMElem(), getGlobal()));

        colNode->read();
    }
}

Node *
ColladaInstanceNode::process(ColladaElement *parent)
{
    ColladaNodeRefPtr colNode = getTargetElem();

    return colNode->createInstance(this);
}

ColladaNode *
ColladaInstanceNode::getTargetElem(void) const
{
    ColladaNode   *retVal     = NULL;
    daeElementRef  targetElem = getTargetDOMElem();

    if(targetElem != NULL)
    {
        retVal = getUserDataAs<ColladaNode>(targetElem);
    }

    return retVal;
}

domNode *
ColladaInstanceNode::getTargetDOMElem(void) const
{
    domNodeRef          retVal   = NULL;
    domInstance_nodeRef instNode = getDOMElementAs<domInstance_node>();

    if(instNode->getUrl().getElement() != NULL)
    {
        retVal = daeSafeCast<domNode>(instNode->getUrl().getElement());
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
