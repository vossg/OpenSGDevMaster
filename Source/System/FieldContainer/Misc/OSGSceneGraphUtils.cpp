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

#include "OSGSceneGraphUtils.h"
#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGAttachment.h"
#include "OSGAttachmentMapSFields.h"
#include "OSGNameAttachment.h"

#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <ostream>
#include <set>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  SceneGraphPrinter
//---------------------------------------------------------------------------

SceneGraphPrinter::SceneGraphPrinter(Node *root)
    : _pRoot       (root),
      _pCurrNode   (NULL),
      _pStream     (NULL),
      _indent      (0),
      _printFuncMap()
{
    // nothing to do
}

void SceneGraphPrinter::printDownTree(std::ostream &os)
{
    _pStream = &os;
    _indent  = 0;

    traverse(_pRoot,
             boost::bind(&Self::traverseEnter, this, _1    ),
             boost::bind(&Self::traverseLeave, this, _1, _2) );

    os << std::flush;
}

void SceneGraphPrinter::printUpTree(std::ostream &os)
{
    _pStream = &os;
    _indent  = 0;

    Node *node = _pRoot;

    while(node != NULL)
    {
        NodeCore *core = node->getCore();
        _pCurrNode = node;

        os <<      "[" << node
           <<    "] [" << node->getId()
           <<    "] [" << (getName(node) ? getName(node) : "<unnamed>")
           << "] -- [" << core
           <<    "] [" << core->getId()
           <<    "] [" << core->getType().getCName()
           << "]\n";

        node = node->getParent();
    }

    os << std::flush;
}

void
SceneGraphPrinter::addPrintFunc(const FieldContainerType &fcType,
                                const CorePrintFunction  &printFunc)
{
    _printFuncMap[fcType.getId()] = printFunc;
}

void
SceneGraphPrinter::subPrintFunc(const FieldContainerType &fcType)
{
    PrintFuncMapIt pfIt = _printFuncMap.find(fcType.getId());

    if(pfIt != _printFuncMap.end())
        _printFuncMap.erase(pfIt);
}

void
SceneGraphPrinter::incIndent(void)
{
    _indent += 2;
}

void
SceneGraphPrinter::decIndent(void)
{
    _indent -= 2;
}

std::ostream &
SceneGraphPrinter::indentStream(void)
{
    for(UInt32 i = 0; i < _indent; ++i)
        (*_pStream) << " ";

    return *_pStream;
}

std::ostream &
SceneGraphPrinter::getStream(void)
{
    return *_pStream;
}

Node *
SceneGraphPrinter::getCurrNode(void)
{
    return _pCurrNode;
}

Action::ResultE SceneGraphPrinter::traverseEnter(Node *node)
{
    if(node == NULL)
        return Action::Continue;

    _pCurrNode = node;

    std::ostream &os = getStream();
    incIndent();

    indentStream()
            <<   "[" << node
            << "] [" << node->getId()
            << "] [" << (getName(node) ? getName(node) : "<unnamed>")
            << "]";

    NodeCore *core = node->getCore();

    if(core == NULL)
    {
        os << "\n";
        return Action::Continue;
    }

    os << " -- [" << core
       <<   "] [" << core->getId()
       <<   "] [" << core->getType().getCName()
       <<   "]";

    os << " [" << (getName(core) ? getName(core) : "<unnamed>")
       << "]";

    NodeCore::MFParentsType::const_iterator pIt  = core->getMFParents()->begin();
    NodeCore::MFParentsType::const_iterator pEnd = core->getMFParents()->end  ();

    if(core->getMFParents()->size() > 1)
    {
        os << " # parents [" << core->getMFParents()->size() << "] #";

        for(; pIt != pEnd; ++pIt)
        {
            Node *parent = dynamic_cast<Node *>(*pIt);

            os <<  " [" << *pIt
            << "] [" << (getName(parent) ? getName(parent) : "<unnamed>")
            << "]";
        }
    }

    os << "\n";

    // if there is a print function registered for this core type call it
    PrintFuncMapConstIt pfIt = _printFuncMap.find(core->getType().getId());

    if(pfIt != _printFuncMap.end())
    {
        incIndent();
        (pfIt->second)(this, core);
        decIndent();
    }

    return Action::Continue;
}

Action::ResultE SceneGraphPrinter::traverseLeave(
    Node *node, Action::ResultE res)
{
    if(node == NULL)
        return Action::Continue;

    decIndent();

    return Action::Continue;
}

OSG_END_NAMESPACE
