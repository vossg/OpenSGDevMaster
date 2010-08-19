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


#ifndef _OSGLODSETUPGRAPHOP_H_
#define _OSGLODSETUPGRAPHOP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"
#include "OSGAction.h"

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! LODSetupGraphOp class

class OSG_UTIL_DLLMAPPING LODSetupGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */


    typedef GraphOp                                 Inherited;
    typedef LODSetupGraphOp                            Self;

	
    OSG_GEN_INTERNAL_MEMOBJPTR(LODSetupGraphOp);
	
	

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "LODSetupGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create();

    virtual GraphOpTransitPtr clone (void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */

    virtual bool traverse(Node *root);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */
 
	/*! Adds a level of detail to search for in the graph op. Will overwrite previous entries if one with the same value of LOD is preset
	* @param LOD Index corresponding to the Level of Detail this set represents. 0 = highest level of detail
	* @param Range Minimum distance at which this LOD should be used
	* @param SearchName Substring which to check for in a node's name to determine if it is the geometry that should be used for this LOD set. 
	* @return True of the set was added, false if not.
	*/
	void addLODInfo(Int32 LOD, Real32 Range, std::string SearchName);

	/*! Returns the number of LOD nodes that were created. Only accurate after the graph op has been completed.
	 *
	 *	@return Number of LOD nodes created.
	 */
	UInt32 getNumLODSMade( void );

	virtual std::string usage( void );
	virtual void setParams(const std::string params);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

	// Gets the range value for a given LOD.
	Real32 getRange(Int32 LOD);

	typedef std::pair<Int32,Node *> LODPair; // value for a level of detail and it's corresponding node

	struct LODInfo
	{
		Int32 mLOD; // value for this level of detail. 0 = highest level of detail
		Real32 mRange; // distance for which to activate this LOD
		std::string mTag; // name tag to search for in node's name

		LODInfo(Int32 LOD, Real32 Range, std::string Tag );
		LODInfo();
	};

	struct LODSet
	{
		std::string mBaseName; // common name to all nodes in this set
		std::vector<LODPair> mLODPairs;  // array of pointers to nodes for this set of LOD nodes

		void addLODPair(Int32 LOD, Node *node);
	};


	std::vector<LODInfo> _mLODs; 
	std::vector<LODSet> _mSets; 
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             LODSetupGraphOp( void );
    virtual ~LODSetupGraphOp( void );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:

	// The number of LOD nodes created.
	UInt32 _totalNumMade;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef LODSetupGraphOp *LODSetupGraphOpP;

OSG_GEN_MEMOBJPTR(LODSetupGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGLODSETUPGRAPHOP_H_ */
