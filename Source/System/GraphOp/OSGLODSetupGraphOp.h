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
	typedef std::vector<std::string>				SearchNameVec;
    OSG_GEN_INTERNAL_MEMOBJPTR(LODSetupGraphOp);
	
	

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "LODSetupGraphOp"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    static  ObjTransitPtr     create(std::string SearchName = "_col",
                          UInt32 NewTraversalMask = 0);

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

    void setSearchStrings(SearchNameVec SearchName);
	void addSearchString(std::string SearchName);
    void setNewTravMask(UInt32 NewTraversalMask);

	/*! Returns the LOD nodes that were created. 
	 *
	 *	@return Only accurate after the graph op has been completed.
	 */
	UInt32 getNumLODSMade( void );

	virtual std::string usage( void );
	virtual void setParams(const std::string params);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

             LODSetupGraphOp( void );
    virtual ~LODSetupGraphOp( void );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
private:
	
	// The strings to search for in node names to determine if an LOD node 
	// should be created.
	SearchNameVec _searchNames;
	
	// The number of LOD nodes created.
	UInt32 _numMade;
	
    Action::ResultE traverseEnter(Node * const node);
    Action::ResultE traverseLeave(Node * const node, Action::ResultE res);
};

typedef LODSetupGraphOp *LODSetupGraphOpP;

OSG_GEN_MEMOBJPTR(LODSetupGraphOp);


OSG_END_NAMESPACE

#endif /* _OSGLODSETUPGRAPHOP_H_ */
