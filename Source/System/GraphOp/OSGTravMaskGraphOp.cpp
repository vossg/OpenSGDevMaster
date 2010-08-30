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

/*! \class TravMaskGraphOp
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
    
    static StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

TravMaskGraphOp::TravMaskGraphOp() :
	mMatchName(true),
    mMatchWholeName(true),
	mMatchNodeCoreType(false),
	mNodeCoreType(NULL),
	mMatchDerivedCoreTypes(true),
	mMatchCurTravMask(false),
	mMatchMaskCondition(BIT_EQUAL),
	mMatchCurTravMaskValue(1),
    mApplyMaskToAllDecendents(false),
    mApplyToNonMatching(false),
	mNewTravMask(1),
    mApplyNewMaskOperation(BIT_EQUAL),
	mNumChanged(0)
{
	mMatchRegex = boost::xpressive::cregex::compile(".*", boost::xpressive::regex_constants::icase);
}

TravMaskGraphOp::~TravMaskGraphOp(void)
{
}

TravMaskGraphOpTransitPtr TravMaskGraphOp::create()
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

void TravMaskGraphOp::setMatchWholeName(bool value)
{
	mMatchWholeName = value;
}

void TravMaskGraphOp::setMatchDerivedCoreTypes(bool value)
{
	mMatchDerivedCoreTypes = value;
}

void TravMaskGraphOp::setNewTravMaskOperation(UInt8 ApplyNewMaskOperation)
{
	mApplyNewMaskOperation = ApplyNewMaskOperation;
}

void TravMaskGraphOp::setMatchMaskCondition(UInt8 MatchMaskCondition)
{
	mMatchMaskCondition = MatchMaskCondition;
}

void TravMaskGraphOp::setApplyMaskToAllDecendents(bool ApplyMaskToAllDecendents)
{
	mApplyMaskToAllDecendents = ApplyMaskToAllDecendents;
}

void TravMaskGraphOp::setApplyToNonMatching(bool ApplyToNonMatching)
{
	mApplyToNonMatching = ApplyToNonMatching;
}


void TravMaskGraphOp::setMatchRegex(const std::string& MatchName)
{
	mMatchRegex = boost::xpressive::cregex::compile(MatchName, boost::xpressive::regex_constants::icase);
}

void TravMaskGraphOp::setMatchRegex(const boost::xpressive::cregex& MatchRegex)
{
	mMatchRegex = MatchRegex;
}

void TravMaskGraphOp::setNodeCoreType(const std::string& TypeName)
{
	mNodeCoreType = FieldContainerFactory::the()->findType(TypeName.c_str());
}


void TravMaskGraphOp::setNewTravMask(UInt32 NewTraversalMask)
{
	mNewTravMask = NewTraversalMask;
}


void TravMaskGraphOp::setCurrentTravMaskValue(UInt32 CurrentTraversalMask)
{
	mMatchCurTravMaskValue = CurrentTraversalMask;
}

void TravMaskGraphOp::setMatchName(bool MatchName)
{
	mMatchName = MatchName;
}

void TravMaskGraphOp::setMatchNodeCoreType(bool MatchCore)
{
	mMatchNodeCoreType = MatchCore;
}

void TravMaskGraphOp::setMatchCurrentTravMask(bool MatchCurMask)
{
	mMatchCurTravMask = MatchCurMask;
}

void TravMaskGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("NewTraversalMask", mNewTravMask);
    ps("ApplyMaskToAllDecendents", mApplyMaskToAllDecendents);
    ps("ApplyToNonMatching", mApplyToNonMatching);
    //ps("ApplyNewMaskOperation", mApplyNewMaskOperation);


    //Name Matching
    ps("MatchName", mMatchName);
    std::string MatchRegex;
	ps("MatchRegex", MatchRegex);
    ps("MatchWholeName", mMatchWholeName);
	mMatchRegex = boost::xpressive::cregex::compile(MatchRegex, boost::xpressive::regex_constants::icase);

    //Type Matching
    ps("MatchNodeCoreType", mMatchNodeCoreType);
    ps("MatchDerivedCoreTypes", mMatchDerivedCoreTypes);
    std::string NodeCoreTypeName;
    ps("NodeCoreTypeName",NodeCoreTypeName);
	mNodeCoreType = FieldContainerFactory::the()->findType(NodeCoreTypeName.c_str());

    //Mask Matching
	ps("MatchCurTravMask",mMatchCurTravMask);
	ps("MatchCurTravMaskValue",mMatchCurTravMaskValue);
	//ps("MatchMaskCondition",mMatchMaskCondition);
    
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
    "	NewTraversalMask (UInt32, 0): Value to set the traversal mask to if it meets the matching criteria\n"
    "	ApplyMaskToAllDecendents (bool, false): Applies the mask operation to all decendents of a matching node\n"
    "	ApplyToNonMatching (bool, false): Applies the mask operation to all non-matching nodes\n"

    "	MatchName (string, \"\"): Name to search for in the node's name.\n"
    "	MatchWholeName (bool, true): Matches only if the entire name matches the search regex\n"

    "	NodeCoreTypeID (UInt32, 0): NodeCoreTypeID to check for.\n"
    "	MatchDerivedCoreTypes (bool, true): Will match all nodes whos type is derived from the searched NodeCore type\n"

    "	CurTraversalMask (UInt32, 1): Current Traversal mask to check for.\n";

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

    //Name Matching
	if(mMatchName)
	{
        const Char8 * namePtr = OSG::getName(node);
        if(namePtr == NULL)
        {
            namePtr = "";
        }
        if(mMatchWholeName)
        {
            setMask = boost::xpressive::regex_match( namePtr, mMatchRegex );
		}
        else
        {
            setMask = boost::xpressive::regex_search( namePtr, mMatchRegex );
        }
	}


    //Type Matching
	if(mMatchNodeCoreType && 
       mNodeCoreType != NULL)
    {
        if(mMatchDerivedCoreTypes)
        {
            if(node->getCore()->getType().isDerivedFrom(*mNodeCoreType))
            {
                setMask = true;
            }
        }
        else
        {
            if(node->getCore()->getType() == *mNodeCoreType)
            {
                setMask = true;
            }
        }
    }

    //Mask Matching
	if(mMatchCurTravMask)
    {
        bool BitTest(false);
        switch(mMatchMaskCondition)
        {
        case BIT_AND:
            BitTest = static_cast<bool>(node->getTravMask() & mMatchCurTravMaskValue);
            break;
        case BIT_OR:
            BitTest = static_cast<bool>(node->getTravMask() | mMatchCurTravMaskValue);
            break;
        case BIT_XOR:
            BitTest = static_cast<bool>(node->getTravMask() ^ mMatchCurTravMaskValue);
            break;
        case BIT_NOT:
        case BIT_NOT_EQUAL:
            BitTest = (node->getTravMask() != mNewTravMask);
            break;
        case BIT_EQUAL:
        default:
            BitTest = (node->getTravMask() == mNewTravMask);
            break;
        }

        if(BitTest)
        {
            setMask = true;
        }
    }

    //If the mask should be applied to non-matching
    //then flip setMask
    if(mApplyToNonMatching)
    {
        setMask = !setMask;
    }

	if(setMask)
	{
        if(mApplyMaskToAllDecendents)
        {
            TravMaskGraphOpRefPtr colMeshGrOp = TravMaskGraphOp::create();
            colMeshGrOp->setMatchRegex(boost::xpressive::cregex::compile(".*"));
            colMeshGrOp->setNewTravMask (mNewTravMask);
            colMeshGrOp->setNewTravMaskOperation (mApplyNewMaskOperation);
            colMeshGrOp->traverse(node);
            mNumChanged += colMeshGrOp->getNumChanged();
            return Action::Skip;
        }
        else
        {
            //Apply the new traversal mask
            UInt32 NewMask;
            switch(mApplyNewMaskOperation)
            {
            case BIT_AND:
                NewMask = node->getTravMask() & mNewTravMask;
                break;
            case BIT_OR:
                NewMask = node->getTravMask() | mNewTravMask;
                break;
            case BIT_XOR:
                NewMask = node->getTravMask() ^ mNewTravMask;
                break;
            case BIT_NOT:
                NewMask = ~node->getTravMask();
                break;
            case BIT_EQUAL:
            default:
                NewMask = mNewTravMask;
                break;
            }
		    node->setTravMask(NewMask);
		    ++mNumChanged;
        }
	}

    return Action::Continue;    
}

Action::ResultE TravMaskGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}




