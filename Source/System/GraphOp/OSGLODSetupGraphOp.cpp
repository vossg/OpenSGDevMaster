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
#include "OSGDistanceLOD.h"

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

LODSetupGraphOp::LODSetupGraphOp( ) : _totalNumMade(0)
{
}

LODSetupGraphOp::~LODSetupGraphOp(void)
{
}

LODSetupGraphOpTransitPtr
LODSetupGraphOp::create( )
{
    return LODSetupGraphOpTransitPtr(new LODSetupGraphOp());
}

GraphOpTransitPtr LODSetupGraphOp::clone(void)
{
    return GraphOpTransitPtr(new LODSetupGraphOp());
}

bool LODSetupGraphOp::traverse(Node *root)
{
	commitChanges();
	root->updateVolume();
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
	"LOD Setup: Creates Distance Level of Detail Nodes if the children of a given node meet the criteria.\n"
	"		See OSGDistanceLOD for more information on how LODs work.\n"
    "Params: name (type, default)\n"
	"  Ranges (MFReal32, {}): Distances to use for keying between different LODs. Smallest value should be first.\n"
	"  SearchNames (MFString, {}): Name to searchs for in the node's children's names. The LOD core will only\n"
	"				be created if there more than one child with a matching string. The SearchNames\n"
	"				should be a one-to-one correspondence with the Ranges. (e.g. Ranges[0] is the range used for \n"
	"				the child with SearchNames[0] present in its name.\n";
}

UInt32 LODSetupGraphOp::getNumLODSMade( void )
{
	return _totalNumMade;
}

void LODSetupGraphOp::addLODInfo(Int32 LOD, Real32 Range, std::string SearchName)
{
	// when we add a new set, we add it in it's correct position such that
	// the highest level of detail will always be at index 0
	LODInfo newLOD(LOD,Range,SearchName);
	bool added(false);
	std::vector<LODInfo>::iterator it = _mLODs.begin(), itEnd = _mLODs.end();
	for(;it != itEnd; it++)
	{
		if(LOD == (*it).mLOD)
		{
			(*it).mTag = SearchName;
			(*it).mRange = Range;
			added = true;
			break;
		} 
		
		if(LOD < (*it).mLOD)
		{
			_mLODs.insert(it,newLOD);
			added = true;
			break;
		}
	}

	if(!added) _mLODs.push_back(newLOD);
}

LODSetupGraphOp::LODInfo::LODInfo(Int32 LOD, Real32 Range, std::string Tag ) :	mLOD(LOD),
																				mRange(Range),
																				mTag(Tag)
{

}

LODSetupGraphOp::LODInfo::LODInfo() :	mLOD(-1),
										mRange(-1.0f),
										mTag("")
{

}
/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Real32 LODSetupGraphOp::getRange(Int32 LOD)
{
	for(UInt32 i(0); i < _mLODs.size(); i++)
	{
		if(_mLODs[i].mLOD == LOD) return _mLODs[i].mRange;
	}
	
	// LOD not found, return the range for the highest LOD
	if(_mLODs.size() > 0) return _mLODs[0].mRange;
	else return 0.0f;
}

void LODSetupGraphOp::LODSet::addLODPair(Int32 LOD, Node *node)
{
	mLODPairs.push_back(std::pair<Int32,Node *>(LOD,node));
	// simple sort to make sure LODs are in order
	if(mLODPairs.size() > 1)
	{
		for(Int32 i(mLODPairs.size() - 1); i >= 1; i--)
		{
			if(mLODPairs[i] < mLODPairs[i - 1])
			{
				LODPair tmp = mLODPairs[i];
				mLODPairs[i] = mLODPairs[i-1];
				mLODPairs[i - 1] = tmp;
			}
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE LODSetupGraphOp::traverseEnter(Node * const node)
{
	if(node->getCore()->getType().isDerivedFrom(DistanceLOD::getClassType())) 
	{
		return Action::Skip;
	}

	// clear out the old sets
	_mSets.clear();
	UInt32 numChildren = node->getNChildren();
	
	// check node's children for LOD name tags.
	UInt32 i(0), j(0),found(0);	

	for(i = 0; i < numChildren; i++)
	{
		const Char8 * namePtr = OSG::getName(node->getChild(i));
		if(namePtr != NULL)
		{
			std::string curNodeName(namePtr);
			size_t nameSize(curNodeName.size());
			for(j = 0; j < _mLODs.size(); j++)
			{
				// we only check for the tags at the end of the strings
				size_t searchLoc = (nameSize > _mLODs[j].mTag.size())?(nameSize - _mLODs[j].mTag.size()):(0); 
				size_t loc = curNodeName.find(_mLODs[j].mTag,searchLoc);
				if(loc != std::string::npos)
				{ 
					std::string baseName(curNodeName);
					baseName.erase(loc,_mLODs[j].mTag.size());
				 
					bool createNewSet(true);
	
					for(UInt32 k(0); k < _mSets.size(); k++)
					{
						if(baseName.compare(_mSets[k].mBaseName) == 0)
						{
							_mSets[k].addLODPair(_mLODs[j].mLOD,node->getChild(i));
							createNewSet = false;
							break;
						}
					}
			
					if(createNewSet)
					{
						LODSet newSet;
						newSet.mBaseName = baseName;
						newSet.addLODPair(_mLODs[j].mLOD, node->getChild(i));
						_mSets.push_back(newSet);
						break;
					}

				}
			}// end for(_mLODs.size())
		} //end if(namePtr != NULL)
	} // end for(numChildren)


	// now we add as many LODs as we can
	int madeNow(0);
	if(_mSets.size() > 0)
	{
		
		for(i = 0; i < _mSets.size() ; i++)
		{
			if(_mSets[i].mLODPairs.size() > 1)
			{
				DistanceLODRecPtr TheLODCore  = DistanceLOD::create();

				MFReal32 *ranges = TheLODCore->editMFRange();

				NodeRecPtr newLODNode = Node::create();
				newLODNode->setCore(TheLODCore);
				// also set the name of the node now
				OSG::setName(newLODNode,_mSets[i].mBaseName + "_LODNode");
				node->addChild(newLODNode);

				bool centerIsSet(false);
				for(j = 0; j < _mSets[i].mLODPairs.size(); j++)
				{
					LODPair cur = _mSets[i].mLODPairs[j];
					if((cur.first != -1) && (cur.second != NULL) && (getRange(cur.first) > 0.0f))
					{
						ranges->push_back(getRange(cur.first));
						newLODNode->addChild(cur.second);

						if(!centerIsSet)
						{
							Pnt3f volCenter;
							cur.second->getVolume().getCenter(volCenter);
							TheLODCore->setCenter(volCenter);
							centerIsSet = true;
						}
						madeNow++;
					}
				}
			}
		}
		
		if(madeNow > 0)
		{
			_totalNumMade += madeNow;
			return Action::Skip; 
		}
		else
		{

		}
		   
	}

	return Action::Continue;
}

Action::ResultE LODSetupGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}





