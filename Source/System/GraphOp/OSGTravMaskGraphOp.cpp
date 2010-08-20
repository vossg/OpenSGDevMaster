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

#include "OSGTravMaskGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGNameAttachment.h"
#include <string>


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::TravMaskGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    A class used to change traversal masks of nodes meeting certain criteria.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = TravMaskGraphOp::create();

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

std::string mSearchName;
UInt32 mNewTravMask;

UInt32 mNodeCoreTypeID;
UInt32 mCurTravMask;

bool mCheckName;
bool mCheckCurTravMask;
bool mCheckNodeCoreType;


TravMaskGraphOp::TravMaskGraphOp() :
    mSearchName("_Col"),
	mNewTravMask(1),
	mNumChanged(0),
	mNodeCoreTypeID(0),
	mCurTravMask(1),
	mCheckName(true),
	mCheckCurTravMask(false),
	mCheckNodeCoreType(false)
{
}

TravMaskGraphOp::~TravMaskGraphOp(void)
{
}

TravMaskGraphOpTransitPtr
TravMaskGraphOp::create()
{
    return TravMaskGraphOpTransitPtr(new TravMaskGraphOp());
}

GraphOpTransitPtr TravMaskGraphOp::clone(void)
{
    return GraphOpTransitPtr(new TravMaskGraphOp());
}

bool TravMaskGraphOp::traverse(Node *root)
{
    return GraphOp::traverse(root);
}

void TravMaskGraphOp::setSearchString(std::string SearchName)
{
	mSearchName = SearchName;
}

void TravMaskGraphOp::setNodeCoreType(UInt32 ClassTypeID)
{
	mNodeCoreTypeID = ClassTypeID;
}


void TravMaskGraphOp::setNewTravMask(UInt32 NewTraversalMask)
{
	mNewTravMask = NewTraversalMask;
}


void TravMaskGraphOp::setCurrentTravMask(UInt32 CurrentTraversalMask)
{
	mCurTravMask = CurrentTraversalMask;
}

void TravMaskGraphOp::setCheckName(bool CheckName)
{
	mCheckName = CheckName;
}

void TravMaskGraphOp::setCheckNodeCoreType(bool CheckCore)
{
	mCheckNodeCoreType = CheckCore;
}

void TravMaskGraphOp::setCheckCurrentTravMask(bool CheckCurMask)
{
	mCheckCurTravMask = CheckCurMask;
}

void TravMaskGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("NewTraversalMask", mNewTravMask);
	ps("SearchName", mSearchName);
	ps("NodeCoreTypeID",mNodeCoreTypeID);
	ps("CurTraversalMask",mCurTravMask);
	ps("NodeCoreTypeID",mNodeCoreTypeID);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("TravMaskGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string TravMaskGraphOp::usage(void)
{
    return 
    "NodeNameTravMask: Changes traversal masks of nodes based on certain criteria.\n"
    "Params: name (type, default)\n"
    "	NewTraversalMask (UInt32, 0): Value to set the traversal mask to if it meets criteria\n"
	"	SearchName (string, \"_col\"): Name to search for in the node's name."
	"	NodeCoreTypeID (UInt32, 0): NodeCoreTypeID to check for."
	"	CurTraversalMask (UInt32, 1): Current Traversal mask to check for."
	" The default values for this class will hide all nodes whose names end in \"_Col\"";
}

UInt32 TravMaskGraphOp::getNumChanged( void )
{
	return mNumChanged;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE TravMaskGraphOp::traverseEnter(Node * const node)
{
	bool setMask(false);

	if(mCheckName)
	{
		const Char8 * namePtr = OSG::getName(node);

		if(namePtr != NULL)
		{
			std::string nodeName(namePtr);
			size_t searchPos = ( nodeName.length() > mSearchName.length() + 1 ) 
								? (nodeName.length() - mSearchName.length() - 1) 
								: (0);

			if(nodeName.find(mSearchName, searchPos) != std::string::npos)
			{
				setMask = true;
			}
		}
	}

	if(mCheckCurTravMask && 
		(node->getTravMask() == mCurTravMask)) 
			setMask = true;


	if(mCheckNodeCoreType && 
		(node->getCore()->getClassTypeId() == mNodeCoreTypeID)) 
			setMask = true;

	if(setMask)
	{
		node->setTravMask(mNewTravMask);
		mNumChanged++;
	}

    return Action::Continue;    
}

Action::ResultE TravMaskGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}




