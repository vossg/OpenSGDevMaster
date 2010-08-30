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


#ifndef _OSGTravMaskGraphOp_H_
#define _OSGTravMaskGraphOp_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGraphOp.h"
#include "OSGUtilDef.h"
#include "OSGAction.h"
#include <boost/xpressive/xpressive_dynamic.hpp>

OSG_BEGIN_NAMESPACE

//! \ingroup GrpSystemRenderingBackend
//! TravMaskGraphOp class

class OSG_UTIL_DLLMAPPING TravMaskGraphOp : public GraphOp
{
    /*==========================  PUBLIC  =================================*/
  public:
    enum BitComparisionOps
    {
        BIT_EQUAL     = 0,
        BIT_AND       = 1,
        BIT_OR        = 2,
        BIT_XOR       = 3,
        BIT_NOT       = 4,
        BIT_NOT_EQUAL = 5
    };

    /*---------------------------------------------------------------------*/
    /*! \name Types                                                        */
    /*! \{                                                                 */

    typedef GraphOp                                 Inherited;
    typedef TravMaskGraphOp                            Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(TravMaskGraphOp);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "TravMaskGraphOp"; };

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

	/*! Sets the string to search for in a node's name. 
	*	Only the end of the node's name is checked.
	*	@param MatchName String to look for in a node's name. 
	*
	*/
    void setMatchRegex(const std::string& MatchRegex);
    void setMatchRegex(const boost::xpressive::cregex& MatchRegex);
    void setMatchWholeName(bool value);

	/*! Sets the type of node core to search for (based on a node core's type ID)
	*	@param ClassTypeID ID of the node core type to check for.
	*/
    void setNodeCoreType(const std::string& TypeName);
    void setMatchDerivedCoreTypes(bool value);

	/*!	Sets the value which the traversal mask of nodes will be set to IF it
	*	meets the right criteria.
	*	@param NewTraversalMask The value which traversal masks will be set to.
	*/
    void setNewTravMask(UInt32 NewTraversalMask);
    void setNewTravMaskOperation(UInt8 ApplyNewMaskOperation);

	/*! Sets the value of the traversal mask to check for.
	*	@param CurrentTraversalMask Value of the traversal mask to check for.
	*/
	void setCurrentTravMaskValue(UInt32 CurrentTraversalMask);
	void setMatchMaskCondition(UInt8 MatchMaskCondition);

	/*! Sets whether or not to check a node's name for the search string.
	*	If true, and a node's name ends in the search string, the new trav mask
	*	will be set.
	*	@param MatchName If true, the name will be checked for the search string.
	*/
	void setMatchName(bool MatchName = true);

	/*! Sets whether or not to check a node core's type.
	*	If true, and a node's core type matches the type set in setNodeCoreType, 
	*	the new trav mask will be set.
	*	@param MatchCore If true, the node core type will be checked. 
	*/
	void setMatchNodeCoreType(bool MatchCore = true);

	/*! Sets whether or not to check a node current traversal mask.
	*	If true, and a node's traversal mask matches the one set by setCurrentTravMask, 
	*	the new trav mask will be set.
	*	@param MatchCore If true, the node's traversal mask will be checked. 
	*/
	void setMatchCurrentTravMask(bool MatchCurMask = true);

	/*! Sets whether or not to apply the travaersal mask to all of the decendents
    *   of a node that satisfies the selection criteria.  The trversal mask
    *   of decendents will be set even if they do not match the selection criteria.
	*	@param MatchCore If true, decendent nodes of nodes that match the selection
    *          criteria will have their traversal mask set.
	*/
	void setApplyMaskToAllDecendents(bool ApplyMaskToAllDecendents);
	void setApplyToNonMatching(bool ApplyToNonMatching);

	/*! Returns the number of nodes whose traversal masks was changed. 
	 *
	 *	@return Only accurate after the graph op has been completed.
	 */
	UInt32 getNumChanged( void );

	virtual std::string usage(void);
	virtual void setParams(const std::string params);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             TravMaskGraphOp();

    virtual ~TravMaskGraphOp(void                                );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
    //Name matching criteria
	bool mMatchName;
    boost::xpressive::cregex mMatchRegex;
    bool mMatchWholeName;

    //Type matching criteria
	bool mMatchNodeCoreType;
    const FieldContainerType* mNodeCoreType;
    bool mMatchDerivedCoreTypes;

    //Mask matching criteria
	bool mMatchCurTravMask;
	UInt32 mMatchCurTravMaskValue;
    UInt8  mMatchMaskCondition;

    //Parameters for applying new mask
    bool mApplyMaskToAllDecendents;
    bool mApplyToNonMatching;
	UInt32 mNewTravMask;
    UInt8  mApplyNewMaskOperation;

	UInt32 mNumChanged;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef TravMaskGraphOp *TravMaskGraphOpP;

OSG_GEN_MEMOBJPTR(TravMaskGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGTravMaskGraphOp_H_ */
