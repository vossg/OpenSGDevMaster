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

#include "OSGLODSetupGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGNameAttachment.h"
#include <string>


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::LODSetupGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    A class used to optimize geometries a bit.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = LODSetupGraphOp::create();

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

LODSetupGraphOp::LODSetupGraphOp( )
{
}

LODSetupGraphOp::~LODSetupGraphOp(void)
{
}

LODSetupGraphOpTransitPtr
LODSetupGraphOp::create(std::string SearchName,
                             UInt32 NewTraversalMask )
{
    return LODSetupGraphOpTransitPtr(new LODSetupGraphOp());
}

GraphOpTransitPtr LODSetupGraphOp::clone(void)
{
    return GraphOpTransitPtr(new LODSetupGraphOp());
}

bool LODSetupGraphOp::traverse(Node *root)
{
    return GraphOp::traverse(root);
}

void LODSetupGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("LODSetupGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string LODSetupGraphOp::usage(void)
{
    return 
    "Collision Mesh: Changes traversal masks of nodes containing a given string in their name\n"
    "Params: name (type, default)\n"
    "  NewTraversalMask (UInt32, 0): Value to set the traversal mask to if it contains SearchName\n"
	"  SearchName (string, \"_col\"): Name to search for in the node's name.";
}

UInt32 LODSetupGraphOp::getNumLODSMade( void )
{
	return _numMade;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE LODSetupGraphOp::traverseEnter(Node * const node)
{
	const Char8 * namePtr = OSG::getName(node);

	if(namePtr != NULL)
	{
		// check children for nodes with the LOD search names
		
		// if (two or more/all?) of them are there, create an LOD node
		// etc etc
	}

    return Action::Continue;    
}

Action::ResultE LODSetupGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}




