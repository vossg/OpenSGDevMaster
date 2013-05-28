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

#include "OSGConvertInlineGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGAction.h"
#include "OSGInline.h"
#include "OSGGroup.h"
#include "OSGVisitSubTree.h"

#include <set>

#include <boost/bind.hpp>

/*! \class OSG::ConvertInlineGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    replaces inline cores by group cores and move the inline root
    node to parent node.
 */

OSG_BEGIN_NAMESPACE

namespace
{
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = ConvertInlineGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);
} // namespace

const char *ConvertInlineGraphOp::getClassname(void)
{
    return "ConvertInlineGraphOp";
}

ConvertInlineGraphOp::ConvertInlineGraphOp(const char* name) : 
     Inherited       (name ),
    _bTreeCloneShared(false)
{
    // nothing to do
}

ConvertInlineGraphOpTransitPtr ConvertInlineGraphOp::create(void)
{
    return ConvertInlineGraphOpTransitPtr(new ConvertInlineGraphOp);
}

GraphOpTransitPtr ConvertInlineGraphOp::clone(void)
{
    return GraphOpTransitPtr(new ConvertInlineGraphOp);
}

void ConvertInlineGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);

    ps("treecloneshared", _bTreeCloneShared);

    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("ConvertInlineGraphOp doesn't have parameters '%s'.\n",
                  out.c_str()));
    }
}

std::string ConvertInlineGraphOp::usage(void)
{
    return 
        "ConvertInline: replaces inline core by group/visit sub tree core.\n"
        "Params: name (type, default)\n"
        "  treeCloneShared (bool, false): clone tree if inline core is shared,"
        "    default : use VisitSubTree\n";

}


ConvertInlineGraphOp::~ConvertInlineGraphOp(void)
{
    // nothing to do
}


Action::ResultE ConvertInlineGraphOp::traverseEnter(Node * const node)
{
    if(isInExcludeList(node))
        return Action::Skip;

    Inline *pInline = dynamic_cast<Inline *>(node->getCore());
    
    if(pInline == NULL)
        return Action::Continue;

    if(pInline->getMFParents()->size() > 1)
    {
        if(_bTreeCloneShared == false)
        {
            VisitSubTreeUnrecPtr pVS = VisitSubTree::create();

            pVS->setSubTreeRoot(pInline->getRoot());

            node->setCore(pVS);
        }
        else
        {
            NodeUnrecPtr pClone = cloneTree(pInline->getRoot());

            node->addChild(pClone);

            node->setCore(Group::create());

//            fprintf(stderr, "multi parent inline not handled\n");
        }

        return Action::Continue;
    }
    else
    {
        pInline->moveRootTo(node);

        node->setCore(Group::create());
    }

    return Action::Continue;
}

Action::ResultE ConvertInlineGraphOp::traverseLeave(
    Node            * const node, 
    Action::ResultE         res )
{
    return Action::Continue;
}

OSG_END_NAMESPACE
