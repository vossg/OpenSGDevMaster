/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *                   contact: dan.guilliams@gmail.com                        *
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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include "OSGNodeNameTravMaskGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGNameAttachment.h"
#include <string>


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::NodeNameTravMaskGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    A class used to optimize geometries a bit.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = NodeNameTravMaskGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static OSG::StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

NodeNameTravMaskGraphOp::NodeNameTravMaskGraphOp(      std::string SearchName,
                          UInt32 NewTraversalMask ) :
    _searchName(SearchName),
	_travMaskValue(NewTraversalMask),
	_numChanged(0)
{
}

NodeNameTravMaskGraphOp::~NodeNameTravMaskGraphOp(void)
{
}

NodeNameTravMaskGraphOpTransitPtr
NodeNameTravMaskGraphOp::create(std::string SearchName,
                             UInt32 NewTraversalMask )
{
    return NodeNameTravMaskGraphOpTransitPtr(new NodeNameTravMaskGraphOp(SearchName,NewTraversalMask));
}

GraphOpTransitPtr NodeNameTravMaskGraphOp::clone(void)
{
    return GraphOpTransitPtr(new NodeNameTravMaskGraphOp());
}

bool NodeNameTravMaskGraphOp::traverse(Node *root)
{
    return GraphOp::traverse(root);
}

void NodeNameTravMaskGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("NewTraversalMask", _travMaskValue);
	ps("SearchName", _searchName);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("NodeNameTravMaskGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string NodeNameTravMaskGraphOp::usage(void)
{
    return 
    "NodeNameTravMask: Changes traversal masks of nodes containing a given string in their name\n"
    "Params: name (type, default)\n"
    "  NewTraversalMask (UInt32, 0): Value to set the traversal mask to if it contains SearchName\n"
	"  SearchName (string, \"_col\"): Name to search for in the node's name.";
}

void NodeNameTravMaskGraphOp::setSearchString(std::string SearchName)
{
	_searchName = SearchName;
}

void NodeNameTravMaskGraphOp::setNewTravMask(UInt32 NewTraversalMask)
{
	_travMaskValue = NewTraversalMask;
}


UInt32 NodeNameTravMaskGraphOp::getNumChanged( void )
{
	return _numChanged;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE NodeNameTravMaskGraphOp::traverseEnter(Node * const node)
{
	const Char8 * namePtr = OSG::getName(node);

	if(namePtr != NULL)
	{
		std::string nodeName(namePtr);
		size_t searchPos = ( nodeName.length() > _searchName.length() + 1 ) ? (nodeName.length() - _searchName.length() - 1) : (0);
		if(nodeName.find(_searchName, searchPos) != std::string::npos)
		{
			node->setTravMask(_travMaskValue);
			_numChanged++;
		}
	}

    return Action::Continue;    
}

Action::ResultE NodeNameTravMaskGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}




